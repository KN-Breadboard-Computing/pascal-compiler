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
        std::set_intersection(newDominators.begin(), newDominators.end(), dominators[predLabel].begin(), dominators[predLabel].end(), std::inserter(tempSet, tempSet.begin()));
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

    std::vector<std::pair<std::string, std::size_t>> distances;
    for (const auto& domLabel : dominators[label]) {
      distances.push_back({domLabel, ssaGraph.distance(domLabel, label)});
    }
    std::sort(distances.begin(), distances.end(), [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });

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
    if (ssaGraph.getInLinks(label).size() < 2) {
      continue;
    }
    for (const auto& predLabel : ssaGraph.getInLinks(label)) {
      std::string runner = predLabel;
      while (runner != immediateDominators[label]) {
        dominanceFrontiers[runner].insert(label);
        runner = immediateDominators[runner];
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

  std::map<std::string, std::set<std::string>> varDefs;
  for (const auto& label : allBlockLabels) {
    for (const auto& instruction : ssaGraph.getBasicBlock(label).getInstructions()) {
      instruction->visitDefVariables([&varDefs, &label](const VariableType& var) {
        if (varDefs.find(var) == varDefs.end()) {
          varDefs.insert({var, std::set<std::string>()});
        }
        varDefs[var].insert(label);
      });
    }
  }

  std::map<std::string, std::vector<std::string>> phis;
  for (const auto& [var, labels] : varDefs) {
    if (labels.size() < 2) {
      continue;
    }

    std::set<std::string> hasAlready;
    std::set<std::string> everOnWorklist;
    std::set<std::string> worklist;

    everOnWorklist.insert(labels.begin(), labels.end());
    worklist.insert(labels.begin(), labels.end());

    while (!worklist.empty()) {
      const std::string label = *worklist.begin();
      worklist.erase(worklist.begin());

      for (const auto& dfLabel : dominanceFrontiers[label]) {
        if (hasAlready.find(dfLabel) == hasAlready.end()) {
          if (phis.find(dfLabel) == phis.end()) {
            phis.insert({dfLabel, std::vector<std::string>()});
          }
          if (std::find(phis[dfLabel].begin(), phis[dfLabel].end(), var) == phis[dfLabel].end()) {
            phis[dfLabel].push_back(var);
          }
          hasAlready.insert(dfLabel);

          if (everOnWorklist.find(dfLabel) == everOnWorklist.end()) {
            everOnWorklist.insert(dfLabel);
            worklist.insert(dfLabel);
          }
        }
      }
    }
  }

  for (const auto& [label, vars] : phis) {
    for (const auto& var : vars) {
      ssaGraph.basicBlocks().at(label).addInstructionToStart(std::make_unique<BBPhi>(var, std::vector<std::string>{}));
    }
  }

  std::map<std::string, std::size_t> variableCounters;
  std::map<std::string, std::stack<std::size_t>> variableStacks;
  phiCompletions_.insert({name, std::map<std::string, std::map<std::string, std::map<std::string, std::size_t>>>()});
  for (const auto& [var, defs] : varDefs) {
    variableCounters.insert({var, 0});
    variableStacks.insert({var, std::stack<std::size_t>{}});
  }

  renameVariables(ssaGraph.getEntryLabel(), ssaGraph, dominanceTree, variableCounters, variableStacks, phiCompletions_[name]);

  for (const auto& [label, block] : ssaGraph.basicBlocks()) {
    for (const auto& instruction : block.getInstructions()) {
      if (instruction->getType() == BBInstruction::Type::PHI) {
        BBPhi* phi = dynamic_cast<BBPhi*>(instruction.get());
        const std::string var = removeVariableCounter(phi->getName());
        std::vector<std::string> args;
        for (const auto& [predLabel, predIndex] : phiCompletions_[name][label][var]) {
          args.push_back(appendVariableCounter(var, predIndex));
        }
        phi->setArgs(args);
      }
    }
  }

  functionControlFlowGraphs_.insert({name, ssaGraph});
}

void BbSsaGenerator::fromSsa() {
  for (auto& [name, cfg] : functionControlFlowGraphs_) {
    // iterate over block in bfs order
    std::queue<std::string> bfsQueue;
    std::set<std::string> visited;
    bfsQueue.push(cfg.getEntryLabel());
    visited.insert(cfg.getEntryLabel());

    while (!bfsQueue.empty()) {
      const std::string label = bfsQueue.front();
      bfsQueue.pop();

      for (const auto& childLabel : cfg.getOutLinks(label)) {
        if (visited.find(childLabel) == visited.end()) {
          bfsQueue.push(childLabel);
          visited.insert(childLabel);
        }
      }

      BasicBlock newBlock;
      for (const auto& instruction : cfg.basicBlocks().at(label).getInstructions()) {
        if (instruction->getType() == BBInstruction::Type::PHI) {
          BBPhi* phi = dynamic_cast<BBPhi*>(instruction.get());
          const std::string var = phi->getName();
          for (const auto& pred : phiCompletions_[name][label][removeVariableCounter(var)]) {
            cfg.basicBlocks().at(pred.first).addInstruction(std::make_unique<BBMoveVV>(appendVariableCounter(removeVariableCounter(var), pred.second), var, BBInstruction::SourceType::REGISTER, BBInstruction::DestinationType::REGISTER));
          }
        }
        else {
          newBlock.addInstruction(instruction->clone());
        }
      }

      cfg.basicBlocks().at(label) = newBlock;
    }

    cfg.removeSingleUseAssignments(false);
    cfg.removeEmptyBasicBlocks();
  }
}

void BbSsaGenerator::optimize() {
  removeRedundantAssignments();
  //  propagateConstants();

  for (auto& [name, cfg] : functionControlFlowGraphs_) {
    cfg.removeEmptyBasicBlocks();
  }
}

void BbSsaGenerator::removeRedundantAssignments() {
  for (auto& [name, cfg] : functionControlFlowGraphs_) {
    bool changed = true;
    while (changed) {
      changed = false;
      std::set<std::string> defs;
      std::set<std::string> uses;
      for (const auto& block : cfg.basicBlocks()) {
        for (const auto& instruction : block.second.getInstructions()) {
          instruction->visitDefVariables([&defs](const VariableType& var) { defs.insert(var); });
          instruction->visitUseVariables([&uses](const VariableType& var) { uses.insert(var); });
        }
      }

      std::vector<std::string> redundantDefs;
      std::set_difference(defs.begin(), defs.end(), uses.begin(), uses.end(), std::inserter(redundantDefs, redundantDefs.begin()));

      for (auto& block : cfg.basicBlocks()) {
        BasicBlock newBlock;

        for (const auto& instruction : block.second.getInstructions()) {
          bool isRedundant = false;
          instruction->visitDefVariables([&redundantDefs, &isRedundant, &instruction](const VariableType& var) {
            if (std::find(redundantDefs.begin(), redundantDefs.end(), var) != redundantDefs.end()) {
              isRedundant = instruction->canBeOptimizedOut();
            }
          });

          if (!isRedundant) {
            newBlock.addInstruction(instruction->clone());
          }
          else {
            changed = true;
          }
        }

        block.second = newBlock;
      }
    }
  }
}

void BbSsaGenerator::propagateConstants() {
  //  for (auto& [name, cfg] : functionControlFlowGraphs_) {}
}

std::string BbSsaGenerator::appendVariableCounter(const std::string& var, std::size_t index) {
  return var + "." + std::to_string(index);
}
std::string BbSsaGenerator::removeVariableCounter(const std::string& var) {
  std::string newVar;
  for (const char character : var) {
    if (character == '.') {
      break;
    }
    newVar += character;
  }
  return newVar;
}

void BbSsaGenerator::renameVariables(const std::string& blockLabel, BBControlFlowGraph& cfg, const std::map<std::string, std::vector<std::string>>& dominanceTree, std::map<std::string, std::size_t>& variableCounters,
                                     std::map<std::string, std::stack<std::size_t>>& variableStacks, std::map<std::string, std::map<std::string, std::map<std::string, std::size_t>>>& phiCompletions) {
  for (auto& instruction : cfg.basicBlocks().at(blockLabel).instructions()) {
    if (instruction->getType() == BBInstruction::Type::PHI) {
      BBPhi* phi = dynamic_cast<BBPhi*>(instruction.get());
      const std::string var = phi->getName();

      const std::size_t index = variableCounters[var];
      phi->setName(appendVariableCounter(var, index));

      variableStacks[var].push(index);
      variableCounters[var]++;
    }
    else {
      std::set<std::string> rhsVars;
      instruction->visitUseVariables([&rhsVars](const VariableType& var) { rhsVars.insert(var); });
      for (const auto& rhsVar : rhsVars) {
        instruction->replaceUseVariables(rhsVar, appendVariableCounter(rhsVar, variableStacks[rhsVar].top()));
      }

      std::set<std::string> lhsVars;
      instruction->visitDefVariables([&lhsVars](const VariableType& var) { lhsVars.insert(var); });
      for (const auto& lhsVar : lhsVars) {
        const std::size_t index = variableCounters[lhsVar];
        instruction->replaceDefVariables(lhsVar, appendVariableCounter(lhsVar, index));

        variableStacks[lhsVar].push(index);
        variableCounters[lhsVar]++;
      }
    }
  }

  for (const auto& childLabel : cfg.getOutLinks(blockLabel)) {
    for (const auto& instruction : cfg.basicBlocks().at(childLabel).instructions()) {
      if (instruction->getType() == BBInstruction::Type::PHI) {
        BBPhi* phi = dynamic_cast<BBPhi*>(instruction.get());
        const std::string var = removeVariableCounter(phi->getName());

        if (phiCompletions.find(childLabel) == phiCompletions.end()) {
          phiCompletions.insert({childLabel, std::map<std::string, std::map<std::string, std::size_t>>()});
        }
        if (phiCompletions[childLabel].find(var) == phiCompletions[childLabel].end()) {
          phiCompletions[childLabel].insert({var, std::map<std::string, std::size_t>()});
        }

        if (phiCompletions[childLabel][var].find(blockLabel) == phiCompletions[childLabel][var].end()) {
          if (!variableStacks[var].empty()) {
            phiCompletions[childLabel][var].insert({blockLabel, variableStacks[var].top()});
          }
        }
        else {
          if (!variableStacks[var].empty()) {
            phiCompletions[childLabel][var][blockLabel] = variableStacks[var].top();
          }
        }
      }
      else {
        break;  // All phi functions are at the beginning of the block
      }
    }
  }

  for (const auto& childLabel : dominanceTree.at(blockLabel)) {
    if (childLabel != "") {
      renameVariables(childLabel, cfg, dominanceTree, variableCounters, variableStacks, phiCompletions);
    }
  }

  for (auto& instruction : cfg.basicBlocks().at(blockLabel).instructions()) {
    std::set<std::string> lhsVars;
    instruction->visitDefVariables([&lhsVars](const VariableType& var) { lhsVars.insert(var); });
    for (const auto& lhsVar : lhsVars) {
      variableStacks[removeVariableCounter(lhsVar)].pop();
    }
  }
}
}  // namespace bblocks