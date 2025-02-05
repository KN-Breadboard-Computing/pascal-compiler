#include "live_ranges_generator.hpp"

namespace machine_code {
void LiveRangesGenerator::generate(const bblocks::BBControlFlowGraph& cfg,
                                   const std::map<std::string, std::pair<std::size_t, std::size_t>>& blockBounds) {
  for (const auto& block : cfg.getBasicBlocks()) {
    addDefsAndUses(block.first, block.second, blockBounds.at(block.first).first);
  }
  computeLiveInAndLiveOut(cfg);
  computeLiveRanges(cfg, blockBounds);
}

void LiveRangesGenerator::saveLiveRanges(std::ostream& output) const {
  output << "Defs in block:" << std::endl;
  for (const auto& [label, defs] : defsInBlock_) {
    output << label << ": " << std::endl;
    for (const auto& [variable, enumerators] : defs) {
      output << "  " << variable << ": ";
      for (const auto& enumerator : enumerators) {
        output << enumerator << " ";
      }
      output << std::endl;
    }
  }
  output << std::endl;

  output << "Uses in block:" << std::endl;
  for (const auto& [label, uses] : usesInBlock_) {
    output << label << ": " << std::endl;
    for (const auto& [variable, enumerators] : uses) {
      output << "  " << variable << ": ";
      for (const auto& enumerator : enumerators) {
        output << enumerator << " ";
      }
      output << std::endl;
    }
  }
  output << std::endl;

  output << "Live in:" << std::endl;
  for (const auto& [label, liveIn] : liveIn_) {
    output << label << ": ";
    for (const auto& variable : liveIn) {
      output << variable << " ";
    }
    output << std::endl;
  }
  output << std::endl;

  output << "Live out:" << std::endl;
  for (const auto& [label, liveOut] : liveOut_) {
    output << label << ": ";
    for (const auto& variable : liveOut) {
      output << variable << " ";
    }
    output << std::endl;
  }
  output << std::endl;

  output << "Live ranges:" << std::endl;
  for (const auto& [label, ranges] : liveRanges_) {
    output << label << ": " << std::endl;
    for (const auto& range : ranges) {
      output << "  " << range.first << " " << range.second << " " << std::endl;
    }
    output << std::endl;
  }
}

void LiveRangesGenerator::addDefsAndUses(const std::string& label, const bblocks::BasicBlock& block,
                                         std::size_t blockStartEnumerator) {
  std::size_t enumerator = blockStartEnumerator;
  for (const auto& instruction : block.getInstructions()) {
    defsInBlock_.insert({label, {}});

    instruction->visitDefVariables([this, &label, enumerator](const std::string& variable) {
      if (defsInBlock_[label].find(variable) == defsInBlock_[label].end()) {
        defsInBlock_[label].insert({variable, {}});
      }
      defsInBlock_[label][variable].push_back(enumerator);
    });

    usesInBlock_.insert({label, {}});
    instruction->visitUseVariables([this, &label, enumerator](const std::string& variable) {
      if (usesInBlock_[label].find(variable) == usesInBlock_[label].end()) {
        usesInBlock_[label].insert({variable, {}});
      }
      usesInBlock_[label][variable].push_back(enumerator);
    });

    enumerator++;
  }
}

void LiveRangesGenerator::computeLiveInAndLiveOut(const bblocks::BBControlFlowGraph& cfg) {
  for (const auto& block : cfg.getBasicBlocks()) {
    liveIn_.insert({block.first, {}});
    liveOut_.insert({block.first, {}});
  }

  std::set<std::string> lastLiveOut;
  std::set<std::string> lastLiveIn;
  bool changed;
  do {
    changed = false;

    for (const auto& block : cfg.getBasicBlocks()) {
      lastLiveIn = liveIn_[block.first];
      lastLiveOut = liveOut_[block.first];

      std::vector<std::string> defsInBlock;
      for (const auto& def : defsInBlock_[block.first]) {
        defsInBlock.push_back(def.first);
      }

      std::vector<std::string> usesInBlock;
      for (const auto& use : usesInBlock_[block.first]) {
        if (defsInBlock_[block.first].find(use.first) == defsInBlock_[block.first].end()) {
          usesInBlock.push_back(use.first);
        }
        else {
          std::size_t firstDef =
              *std::min_element(defsInBlock_[block.first][use.first].begin(), defsInBlock_[block.first][use.first].end());

          std::size_t firstUse = *std::min_element(use.second.begin(), use.second.end());

          if (firstDef >= firstUse) {
            usesInBlock.push_back(use.first);
          }
        }
      }

      std::set<std::string> newLiveIn;
      newLiveIn.insert(usesInBlock.begin(), usesInBlock.end());
      for (const auto& liveOut : liveOut_[block.first]) {
        if (std::find(defsInBlock.begin(), defsInBlock.end(), liveOut) == defsInBlock.end()) {
          newLiveIn.insert(liveOut);
        }
      }

      std::set<std::string> newLiveOut;
      for (const auto& successor : cfg.getOutLinks(block.first)) {
        newLiveOut.insert(liveIn_[successor].begin(), liveIn_[successor].end());
      }

      liveOut_[block.first] = newLiveOut;
      liveIn_[block.first] = newLiveIn;

      if (lastLiveIn != liveIn_[block.first] || lastLiveOut != liveOut_[block.first]) {
        changed = true;
      }
    }

  } while (changed);
}

void LiveRangesGenerator::computeLiveRanges(const bblocks::BBControlFlowGraph& cfg,
                                            const std::map<std::string, std::pair<std::size_t, std::size_t>>& blockBounds) {
  std::set<std::string> allVariables;
  for (const auto& block : cfg.getBasicBlocks()) {
    for (const auto& def : defsInBlock_[block.first]) {
      allVariables.insert(def.first);
    }
    for (const auto& use : usesInBlock_[block.first]) {
      allVariables.insert(use.first);
    }
  }

  std::map<std::string, std::map<std::string, std::vector<std::vector<std::size_t>>>> liveRanges;
  for (const auto& variable : allVariables) {
    liveRanges.insert({variable, {}});
  }

  // calculate live ranges for each variable in each block
  std::queue<std::string> blocksToProcess;
  std::set<std::string> visitedBlocks;
  blocksToProcess.push(cfg.getEntryLabel());
  visitedBlocks.insert(cfg.getEntryLabel());
  while (!blocksToProcess.empty()) {
    const std::string blockLabel = blocksToProcess.front();
    blocksToProcess.pop();

    for (const auto& variable : allVariables) {
      liveRanges[variable].insert({blockLabel, {}});
    }

    for (const auto& variable : allVariables) {
      computeLiveRangesForVariableAndBlock(variable, blockLabel, blockBounds.at(blockLabel), liveRanges[variable][blockLabel]);
    }

    for (const auto& outLink : cfg.getOutLinks(blockLabel)) {
      if (visitedBlocks.find(outLink) == visitedBlocks.end()) {
        blocksToProcess.push(outLink);
        visitedBlocks.insert(outLink);
      }
    }
  }

  // for each variable, find all paths in the CFG where the variable is live and merge them
  for (const auto& variable : allVariables) {
    // find all paths where the variable is live
    std::vector<std::vector<std::string>> allPaths;
    for (const auto& block : cfg.getBasicBlocks()) {
      if (liveIn_[block.first].find(variable) == liveIn_[block.first].end() &&
          defsInBlock_[block.first].find(variable) != defsInBlock_[block.first].end()) {
        computeAllBlockChains(cfg, variable, block.first, allPaths, {});
      }
    }

    // merge ranges
    for (auto& path : allPaths) {
      std::sort(path.begin(), path.end(), [&blockBounds](const std::string& a, const std::string& b) {
        return blockBounds.at(a).first < blockBounds.at(b).first;
      });
    }

    mergeLiveRanges(variable, allPaths, liveRanges);
  }
}

void LiveRangesGenerator::computeLiveRangesForVariableAndBlock(const std::string& variable, const std::string& label,
                                                               std::pair<std::size_t, std::size_t> blockBounds,
                                                               std::vector<std::vector<std::size_t>>& ranges) {
  bool isLiveIn = liveIn_[label].find(variable) != liveIn_[label].end();
  bool isLiveOut = liveOut_[label].find(variable) != liveOut_[label].end();

  std::vector<std::size_t> uses;
  if (usesInBlock_[label].find(variable) != usesInBlock_[label].end()) {
    uses = usesInBlock_[label][variable];
  }

  std::vector<std::size_t> defs;
  if (defsInBlock_[label].find(variable) != defsInBlock_[label].end()) {
    for (const auto& def : defsInBlock_[label][variable]) {
      if (std::find(uses.begin(), uses.end(), def) == uses.end()) {
        defs.push_back(def);
      }
    }
  }

  if ((!defs.empty() || isLiveIn) && (!uses.empty() || isLiveOut)) {
    std::size_t firstDef = isLiveIn ? blockBounds.first : *std::min_element(defs.begin(), defs.end());
    std::size_t lastUse = isLiveOut ? blockBounds.second : *std::max_element(uses.begin(), uses.end());

    std::vector<std::size_t> currentRange;
    for (std::size_t i = firstDef; i <= lastUse; i++) {
      if (std::find(defs.begin(), defs.end(), i) != defs.end()) {
        if (!currentRange.empty()) {
          ranges.push_back(currentRange);
          currentRange.clear();
        }
        currentRange.push_back(i);
      }
      else {
        currentRange.push_back(i);
      }
    }

    if (!currentRange.empty()) {
      ranges.push_back(currentRange);
    }
  }
}

void LiveRangesGenerator::computeAllBlockChains(const bblocks::BBControlFlowGraph& cfg, const std::string& variable,
                                                const std::string& startLabel, std::vector<std::vector<std::string>>& blockChains,
                                                std::vector<std::string> currentChain) {
  currentChain.push_back(startLabel);
  bool anySuccessorIsLive = false;
  for (const auto& successor : cfg.getOutLinks(startLabel)) {
    if (liveIn_[successor].find(variable) != liveIn_[successor].end()) {
      anySuccessorIsLive = true;
      if (std::find(currentChain.begin(), currentChain.end(), successor) == currentChain.end()) {
        computeAllBlockChains(cfg, variable, successor, blockChains, currentChain);
      }
      else {
        currentChain.push_back(successor);
        blockChains.push_back(currentChain);
      }
    }
  }

  if (!anySuccessorIsLive) {
    blockChains.push_back(currentChain);
  }
}

void LiveRangesGenerator::mergeLiveRanges(
    const std::string& variable, const std::vector<std::vector<std::string>>& blockChains,
    const std::map<std::string, std::map<std::string, std::vector<std::vector<std::size_t>>>>& ranges) {
  for (const auto& blockChain : blockChains) {
    std::vector<std::pair<std::size_t, std::size_t>> mergedRanges;
    for (const auto& block : blockChain) {
      if (mergedRanges.empty()) {
        for (const auto& range : ranges.at(variable).at(block)) {
          mergedRanges.push_back({range.front(), range.back()});
        }
      }
      else {
        std::vector<std::pair<std::size_t, std::size_t>> newRanges;
        for (const auto& range : ranges.at(variable).at(block)) {
          newRanges.push_back({range.front(), range.back()});
        }
        mergedRanges.back().second = newRanges.front().second;
        for (std::size_t i = 1; i < newRanges.size(); i++) {
          mergedRanges.push_back(newRanges[i]);
        }
      }
    }

    std::sort(mergedRanges.begin(), mergedRanges.end(),
              [](const std::pair<std::size_t, std::size_t>& a, const std::pair<std::size_t, std::size_t>& b) {
                return a.first < b.first;
              });

    if (liveRanges_.find(variable) == liveRanges_.end()) {
      liveRanges_.insert({variable, mergedRanges});
    }
    else {
      liveRanges_[variable].insert(liveRanges_[variable].end(), mergedRanges.begin(), mergedRanges.end());
    }
  }

  for (auto& [var, rangesForVar] : liveRanges_) {
    std::sort(rangesForVar.begin(), rangesForVar.end(),
              [](const std::pair<std::size_t, std::size_t>& a, const std::pair<std::size_t, std::size_t>& b) {
                if (a.first == b.first) {
                  return a.second < b.second;
                }
                return a.first < b.first;
              });
  }

  for (auto& [var, rangesForVar] : liveRanges_) {
    std::vector<std::pair<std::size_t, std::size_t>> newRanges;
    for (const auto& r : rangesForVar) {
      if (newRanges.empty()) {
        newRanges.push_back(r);
      }
      else {
        if (r.first <= newRanges.back().second && r.second >= newRanges.back().second) {
          newRanges.back().second = r.second;
        }
        else {
          newRanges.push_back(r);
        }
      }
    }
    rangesForVar = newRanges;
  }
}
}  // namespace machine_code