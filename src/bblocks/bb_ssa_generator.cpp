#include "bb_ssa_generator.hpp"

namespace bblocks {
void BbSsaGenerator::toSsa(const std::string& name, const BBControlFlowGraph& graph) {
  BBControlFlowGraph ssaGraph = graph;

  std::vector<std::string> allBlockLabels;
  for (const auto& basicBlock : ssaGraph.getBasicBlocks()) {
    allBlockLabels.push_back(basicBlock.first);
  }

  std::map<std::string, std::set<std::string>> dominators;
  for (const auto& label : allBlockLabels) {
    if (label == ssaGraph.getEntryLabel()) {
      dominators.insert({label, std::set<std::string>{label}});
    }
    else {
      dominators.insert({label, std::set<std::string>(allBlockLabels.begin(), allBlockLabels.end())});
    }
  }

  bool changed = true;
  while (changed) {
    changed = false;
    for (const auto& label : allBlockLabels) {
      if (label == ssaGraph.getEntryLabel()) {
        continue;
      }

      std::set<std::string> newDominators(allBlockLabels.begin(), allBlockLabels.end());
      for (const auto& predLabel : ssaGraph.getInLinks(label)) {
        std::set<std::string> tempSet;
        std::set_intersection(newDominators.begin(), newDominators.end(), dominators[predLabel].begin(),
                              dominators[predLabel].end(), std::inserter(tempSet, tempSet.begin()));
        newDominators = tempSet;
      }
      newDominators.insert(label);

      if (newDominators != dominators[label]) {
        dominators[label] = newDominators;
        changed = true;
      }
    }
  }

  std::map<std::string, std::set<std::string>> strictDominators;
  for (const auto& label : allBlockLabels) {
    strictDominators.insert({label, std::set<std::string>()});
  }
  for (const auto& [label, doms] : dominators) {
    for (const auto& dom : doms) {
      if (dom != label) {
        strictDominators[label].insert(dom);
      }
    }
  }

  std::map<std::string, std::string> immediateDominators;
  immediateDominators.insert({ssaGraph.getEntryLabel(), ssaGraph.getEntryLabel()});
  for (const auto& label : allBlockLabels) {
    if (label == ssaGraph.getEntryLabel()) {
      continue;
    }

    std::vector<std::pair<std::string, size_t>> distances;
    for (const auto& domLabel : dominators[label]) {
      distances.push_back({domLabel, ssaGraph.distance(domLabel, label)});
    }
    std::sort(distances.begin(), distances.end(), [](const auto& a, const auto& b) { return a.second < b.second; });

    if (distances.size() == 1) {
      immediateDominators.insert({label, distances[0].first});
    }
    else {
      immediateDominators.insert({label, distances[1].first});
    }
  }

  std::map<std::string, std::set<std::string>> dominanceFrontiers;
  for (const auto& label : allBlockLabels) {
    dominanceFrontiers.insert({label, std::set<std::string>()});
  }

  for (const auto& label : allBlockLabels) {
    for (const auto& predLabel : ssaGraph.getInLinks(label)) {
      std::string runner = predLabel;
      while (std::find(strictDominators[label].begin(), strictDominators[label].end(), runner) == strictDominators[label].end()) {
        dominanceFrontiers[runner].insert(label);
        runner = immediateDominators[runner];
      }
    }
  }

  std::set<std::string> vars;
  std::map<std::string, std::set<std::string>> origDefs;
  std::map<std::string, std::set<std::string>> defSites;
  for (const auto& label : allBlockLabels) {
    origDefs.insert({label, std::set<std::string>()});
    for (const auto& instruction : ssaGraph.getBasicBlock(label).getInstructions()) {
      instruction->visitDefVariables([&vars, &origDefs, &defSites, &label](const VariableType& var) {
        vars.insert(var);
        origDefs[label].insert(var);
        defSites[var].insert(label);
      });
    }
  }

  std::map<std::string, std::vector<std::string>> phis;
  for (const auto& var : vars) {
    std::set<std::string> worklist;
    for (const auto& defSite : defSites[var]) {
      worklist.insert(defSite);
    }

    while (!worklist.empty()) {
      const std::string label = *worklist.begin();
      worklist.erase(worklist.begin());

      for (const auto& df : dominanceFrontiers[label]) {
        if (std::find(phis[var].begin(), phis[var].end(), df) == phis[var].end()) {
          phis[var].push_back(df);
          if (std::find(origDefs[df].begin(), origDefs[df].end(), var) == origDefs[df].end()) {
            worklist.insert(df);
          }
        }
      }
    }
  }

  std::map<std::string, std::vector<std::string>> dominanceTree;
  for (const auto& label : allBlockLabels) {
    dominanceTree.insert({label, std::vector<std::string>()});
  }

  for (const auto& [label, idom] : immediateDominators) {
    if (label != ssaGraph.getEntryLabel()) {
      dominanceTree[idom].push_back(label);
    }
  }

  std::map<std::string, std::vector<std::string>> translatedPhis;
  for (const auto& [var, phiBlocks] : phis) {
    for (const auto& block : phiBlocks) {
      if (translatedPhis.find(block) == translatedPhis.end()) {
        translatedPhis.insert({block, std::vector<std::string>{}});
      }
      translatedPhis[block].push_back(var);
    }
  }

  std::map<std::string, size_t> variablesCounter;
  std::map<std::string, std::stack<std::string>> variableRenames;

  renameVariables(ssaGraph, dominanceTree, ssaGraph.getEntryLabel(), variablesCounter, variableRenames, translatedPhis);

  functionControlFlowGraphs_.insert({name, ssaGraph});
}

void BbSsaGenerator::fromSsa() {
  for (auto& [name, cfg] : functionControlFlowGraphs_) {
    for (auto& block : cfg.basicBlocks()) {
      block.second.instructions().erase(std::remove_if(block.second.instructions().begin(), block.second.instructions().end(),
                                                       [](const std::unique_ptr<BBInstruction>& instruction) {
                                                         return instruction->getType() == BBInstruction::Type::PHI;
                                                       }),
                                        block.second.instructions().end());
      for (auto& instruction : block.second.instructions()) {
        std::set<VariableType> vars;
        instruction->visitDefVariables([&vars](const VariableType& var) { vars.insert(var); });
        instruction->visitUseVariables([&vars](const VariableType& var) { vars.insert(var); });

        for (const auto& var : vars) {
          instruction = instruction->replaceVariable(var, removeVariableCounter(var));
        }
      }
    }
  }
}

void BbSsaGenerator::optimize() {}

std::string BbSsaGenerator::appendVariableCounter(const std::string& var, size_t index) {
  return var + "." + std::to_string(index);
}
std::string BbSsaGenerator::removeVariableCounter(const std::string& var) {
  std::string newVar = "";
  for (char c : var) {
    if (c == '.') {
      break;
    }
    newVar += c;
  }
  return newVar;
}

void BbSsaGenerator::renameVariables(BBControlFlowGraph& cfg,
                                     const std::map<std::string, std::vector<std::string>>& dominanceTree,
                                     const std::string& blockLabel, std::map<std::string, size_t>& variablesCounter,
                                     std::map<std::string, std::stack<std::string>>& variableRenames,
                                     std::map<std::string, std::vector<std::string>>& phis) {

  for (const auto& phiVar : phis[blockLabel]) {
    if (variablesCounter.find(phiVar) == variablesCounter.end()) {
      variablesCounter.insert({phiVar, 0});
      std::stack<std::string> stack;
      stack.push(appendVariableCounter(phiVar, 0));
      variableRenames.insert({phiVar, stack});
    }
    variablesCounter[phiVar]++;
    variableRenames[phiVar].push(appendVariableCounter(phiVar, variablesCounter[phiVar]));

    cfg.basicBlocks()
        .at(blockLabel)
        .addInstructionToStart(std::make_unique<BBPhi>(variableRenames[phiVar].top(), std::vector<std::string>{phiVar}));
  }

  std::vector<std::string> definedVariables;
  std::vector<std::string> usedVariables;

  for (auto& instruction : cfg.basicBlocks().at(blockLabel).instructions()) {
    std::set<std::string> defs;
    instruction->visitDefVariables([&defs](const VariableType& var) { defs.insert(var); });
    definedVariables.insert(definedVariables.end(), defs.begin(), defs.end());

    std::set<std::string> uses;
    instruction->visitUseVariables([&uses](const VariableType& var) { uses.insert(var); });
    usedVariables.insert(usedVariables.end(), uses.begin(), uses.end());

    for (const auto& use : uses) {
      if (variableRenames.find(use) == variableRenames.end() || variableRenames[use].empty()) {
        continue;
      }
      instruction->replaceUseVariables(use, variableRenames[use].top());
    }

    for (const auto& def : defs) {
      if (variablesCounter.find(def) == variablesCounter.end()) {
        variablesCounter.insert({def, 0});
        std::stack<std::string> stack;
        stack.push(appendVariableCounter(def, 0));
        variableRenames.insert({def, stack});
      }
      variablesCounter[def]++;
      variableRenames[def].push(appendVariableCounter(def, variablesCounter[def]));

      instruction->replaceDefVariables(def, variableRenames[def].top());
    }
  }

  for (const auto& child : dominanceTree.at(blockLabel)) {
    renameVariables(cfg, dominanceTree, child, variablesCounter, variableRenames, phis);
  }

  for (const auto& def : definedVariables) {
    variableRenames[def].pop();
  }
}

}  // namespace bblocks