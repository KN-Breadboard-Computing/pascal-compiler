#include "bb_control_flow_graph.hpp"

#include <queue>
#include <set>

namespace bblocks {
void BBControlFlowGraph::addBBlock(const std::string& label, BasicBlock basicBlock) {
#ifdef BB_DEBUG
  std::cout << "New basic block with label: " << label << std::endl;
#endif
  basicBlocks_.insert({label, std::move(basicBlock)});
  srcDest_.insert({label, {}});
  destSrc_.insert({label, {}});
}

void BBControlFlowGraph::addBlocksLink(const std::string& fromLabel, const std::string& toLabel) {
#ifdef BB_DEBUG
  std::cout << "New basic block link: " << fromLabel << " -> " << toLabel << std::endl;
#endif
  if (srcDest_.find(fromLabel) == srcDest_.end()) {
    srcDest_.insert({fromLabel, {toLabel}});
  }
  else {
    srcDest_[fromLabel].emplace_back(toLabel);
  }

  if (destSrc_.find(toLabel) == destSrc_.end()) {
    destSrc_.insert({toLabel, {fromLabel}});
  }
  else {
    destSrc_[toLabel].emplace_back(fromLabel);
  }
}

void BBControlFlowGraph::merge(const BBControlFlowGraph& cfg, const std::string& attachPoint, const std::string& cfgAttachPoint) {
  for (const auto& [label, basicBlock] : cfg.getBasicBlocks()) {
    addBBlock(label, basicBlock);
  }

  for (const auto& [src, dests] : cfg.srcDest_) {
    for (const auto& dest : dests) {
      addBlocksLink(src, dest);
    }
  }

#ifdef BB_DEBUG
  std::cout << "Merge " << cfgAttachPoint << " to " << attachPoint << std::endl;
#endif
  addBlocksLink(attachPoint, cfgAttachPoint);
}

void BBControlFlowGraph::merge(const BBControlFlowGraph& cfg, const std::string& attachPoint) {
  merge(cfg, attachPoint, cfg.getEntryLabel());
}

void BBControlFlowGraph::merge(const BBControlFlowGraph& cfg) {
  merge(cfg, exitLabel_, cfg.getEntryLabel());
}

std::size_t BBControlFlowGraph::distance(const std::string& from, const std::string& to) const {
  std::queue<std::string> labels;
  std::map<std::string, std::size_t> distances;

  labels.push(from);
  distances.insert({from, 0});

  while (!labels.empty()) {
    const auto label = labels.front();
    labels.pop();
    for (const auto& neighbour : srcDest_.at(label)) {
      if (distances.find(neighbour) == distances.end()) {
        labels.push(neighbour);
        distances.insert({neighbour, distances.at(label) + 1});
      }
    }
  }

  return distances.at(to);
}

void BBControlFlowGraph::removeEmptyBasicBlocks() {
  std::map<std::string, std::string> labelsTranslation;
  for (const auto& [blockLabel, block] : getBasicBlocks()) {
    std::string label{blockLabel};
    std::vector<std::string> renames;
    while (getBasicBlock(label).empty() && label != getExitLabel()) {
      renames.push_back(label);
      label = getOutLinks(label).front();
    }

    for (const auto& rename : renames) {
      labelsTranslation[rename] = label;
    }
  }

  std::map<std::string, std::vector<std::string>> updatedSrcDest;
  for (auto srcDest = getSrcDestLinks().cbegin(); srcDest != getSrcDestLinks().cend(); ++srcDest) {
    const std::string source =
        labelsTranslation.find(srcDest->first) != labelsTranslation.end() ? labelsTranslation[srcDest->first] : srcDest->first;
    updatedSrcDest.insert({source, {}});
    for (auto dest = srcDest->second.cbegin(); dest != srcDest->second.cend(); ++dest) {
      const std::string destination = labelsTranslation.find(*dest) != labelsTranslation.end() ? labelsTranslation[*dest] : *dest;
      if (std::find(updatedSrcDest[source].begin(), updatedSrcDest[source].end(), destination) == updatedSrcDest[source].end() &&
          source != destination) {
        updatedSrcDest[source].push_back(destination);
      }
    }
  }

  std::map<std::string, std::vector<std::string>> updatedDestSrc;
  for (auto destSrc = getDestSrcLinks().cbegin(); destSrc != getDestSrcLinks().cend(); ++destSrc) {
    const std::string destination =
        labelsTranslation.find(destSrc->first) != labelsTranslation.end() ? labelsTranslation[destSrc->first] : destSrc->first;
    updatedDestSrc.insert({destination, {}});

    for (auto src = destSrc->second.begin(); src != destSrc->second.end(); ++src) {
      const std::string source = labelsTranslation.find(*src) != labelsTranslation.end() ? labelsTranslation[*src] : *src;
      if (std::find(updatedDestSrc[destination].begin(), updatedDestSrc[destination].end(), source) ==
              updatedDestSrc[destination].end() &&
          destination != source) {
        updatedDestSrc[destination].push_back(source);
      }
    }
  }

  std::map<std::string, BasicBlock> updatedBlocks;
  for (const auto& [blockLabel, block] : getBasicBlocks()) {
    if (!block.empty()) {
      const std::string newLabel =
          labelsTranslation.find(blockLabel) != labelsTranslation.end() ? labelsTranslation[blockLabel] : blockLabel;
      updatedBlocks.insert({newLabel, block});
    }
  }

  update(updatedSrcDest, updatedDestSrc, updatedBlocks);

  if (labelsTranslation.find(getEntryLabel()) != labelsTranslation.end()) {
    setEntryLabel(labelsTranslation[getEntryLabel()]);
  }

  if (labelsTranslation.find(getExitLabel()) != labelsTranslation.end()) {
    setExitLabel(labelsTranslation[getExitLabel()]);
  }

  for (auto& block : basicBlocks()) {
    for (auto& instruction : block.second.instructions()) {
      for (const auto& labelTranslation : labelsTranslation) {
        instruction->replaceLabel(labelTranslation.first, labelTranslation.second);
      }
    }
  }
}

void BBControlFlowGraph::removeSingleUseAssignments(bool onlyTemporaries) {
  std::map<std::string, std::size_t> variableDefs;
  std::map<std::string, std::size_t> variableDefsInMove;
  std::map<std::string, std::size_t> variableDefsInOperations;
  std::map<std::string, std::size_t> variableUses;
  std::map<std::string, std::size_t> variableUsesInMove;
  for (const auto& [blockLabel, block] : basicBlocks()) {
    for (const auto& instruction : block.getInstructions()) {
      const BBInstruction::Type instructionType = instruction->getType();
      instruction->visitDefVariables(
          [&variableDefs, &variableDefsInMove, &variableDefsInOperations, instructionType](const std::string& var) {
            if (variableDefs.find(var) == variableDefs.end()) {
              variableDefs[var] = 0;
              variableDefsInMove[var] = 0;
              variableDefsInOperations[var] = 0;
            }

            variableDefs[var]++;
            if (instructionType == BBInstruction::Type::MOVE) {
              variableDefsInMove[var]++;
            }
            else if (instructionType == BBInstruction::Type::UNARY_OPERATION ||
                     instructionType == BBInstruction::Type::BINARY_OPERATION) {
              variableDefsInOperations[var]++;
            }
          });

      instruction->visitUseVariables([&variableUses, &variableUsesInMove, instructionType](const std::string& var) {
        if (variableUses.find(var) == variableUses.end()) {
          variableUses[var] = 0;
        }

        variableUses[var]++;
        if (instructionType == BBInstruction::Type::MOVE) {
          variableUsesInMove[var]++;
        }
      });
    }
  }

  std::set<std::string> onlyDefinedVariables;
  for (const auto& [var, def] : variableDefs) {
    if (variableUses.find(var) == variableUses.end() || variableUses[var] == 0) {
      onlyDefinedVariables.insert(var);
    }
  }

  std::map<std::string, VariableReassignment> reassignments;

  std::queue<std::string> blocksToProcess;
  std::set<std::string> visitedBlocks;
  blocksToProcess.push(getEntryLabel());
  visitedBlocks.insert(getEntryLabel());
  while (!blocksToProcess.empty()) {
    const std::string blockLabel = blocksToProcess.front();
    blocksToProcess.pop();
    BasicBlock blockAfterFirstPass;
    for (auto& instruction : basicBlock(blockLabel).instructions()) {
      std::set<std::string> definedVariables;
      instruction->visitDefVariables([&definedVariables](const std::string& var) { definedVariables.insert(var); });
      if (definedVariables.size() == 1 && onlyDefinedVariables.find(*definedVariables.begin()) != onlyDefinedVariables.end()) {
        if (instruction->canBeOptimizedOut()) {
          continue;
        }
        else {
          onlyDefinedVariables.erase(*definedVariables.begin());
        }
      }

      const std::vector<BBInstruction::TemplateArgumentType> templateTypes = instruction->getTemplateTypes();
      if (instruction->getType() == BBInstruction::Type::MOVE) {
        if (templateTypes[1] == BBInstruction::TemplateArgumentType::STRING) {
          if (templateTypes[0] == BBInstruction::TemplateArgumentType::STRING) {
            BBMoveVV* move = dynamic_cast<BBMoveVV*>(instruction.get());
            const VariableType dst = move->getDestination();
            const VariableType src = move->getSource();
            if (variableDefs[dst] == 1 && variableDefsInMove[dst] == 1 && (Context::isTempVariable(dst) || !onlyTemporaries)) {
              reassignments.insert({dst, {BBInstruction::TemplateArgumentType::STRING, 0, src}});
            }
            else if (variableDefs[src] == 1 && variableDefsInOperations[src] == 1 && variableUses[src] == 1 &&
                     variableUses[src] == variableUsesInMove[src] && (Context::isTempVariable(src) || !onlyTemporaries)) {
              reassignments.insert({src, {BBInstruction::TemplateArgumentType::STRING, 0, dst}});
            }
            else {
              blockAfterFirstPass.addInstruction(instruction->clone());
            }
          }
          else {  // (templateTypes[0] == BBInstruction::TemplateArgumentType::NUMBER)
            BBMoveNV* move = dynamic_cast<BBMoveNV*>(instruction.get());
            const VariableType dst = move->getDestination();
            const NumericType src = move->getSource();
            if (variableDefs[dst] == 1 && variableDefsInMove[dst] == 1 && (Context::isTempVariable(dst) || !onlyTemporaries)) {
              reassignments.insert({dst, {BBInstruction::TemplateArgumentType::NUMBER, src, ""}});
            }
            else {
              blockAfterFirstPass.addInstruction(instruction->clone());
            }
          }
        }
      }
      else {
        blockAfterFirstPass.addInstruction(instruction->clone());
      }
    }

    BasicBlock blockAfterSecondPass;
    for (auto& instruction : blockAfterFirstPass.instructions()) {
      std::unique_ptr<BBInstruction> newInstruction = instruction->clone();
      for (const auto& reassignment : reassignments) {
        if (reassignment.second.type == BBInstruction::TemplateArgumentType::STRING) {
          newInstruction = newInstruction->replaceVariable(reassignment.first, reassignment.second.variable);
        }
        else {
          newInstruction = newInstruction->replaceVariable(reassignment.first, reassignment.second.number);
        }
      }
      blockAfterSecondPass.addInstruction(std::move(newInstruction));
    }

    setBasicBlock(blockLabel, blockAfterSecondPass);

    for (const auto& outLink : getOutLinks(blockLabel)) {
      if (visitedBlocks.find(outLink) == visitedBlocks.end()) {
        blocksToProcess.push(outLink);
        visitedBlocks.insert(outLink);
      }
    }
  }

  if (!reassignments.empty() || !onlyDefinedVariables.empty()) {
    removeSingleUseAssignments(onlyTemporaries);
  }
}

std::ostream& operator<<(std::ostream& out, const BBControlFlowGraph& cfg) {
  std::queue<std::string> labels;
  std::set<std::string> visited;

  labels.push(cfg.getEntryLabel());
  visited.insert(cfg.getEntryLabel());

  while (!labels.empty()) {
    const auto label = labels.front();
    labels.pop();
    if (cfg.destSrc_.find(label) != cfg.destSrc_.end()) {
      for (const auto& neighbour : cfg.destSrc_.at(label)) {
        out << neighbour << " ";
      }
      out << "-> ";
    }
    out << label;
    if (cfg.srcDest_.find(label) != cfg.srcDest_.end()) {
      out << " -> ";
      for (const auto& neighbour : cfg.srcDest_.at(label)) {
        out << neighbour << " ";
        if (visited.find(neighbour) == visited.end()) {
          labels.push(neighbour);
          visited.insert(neighbour);
        }
      }
    }
    out << "{" << std::endl << cfg.basicBlocks_.at(label) << "}" << std::endl << std::endl;
  }

  return out;
}
}  // namespace bblocks
