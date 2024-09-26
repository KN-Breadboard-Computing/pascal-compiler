#include "live_ranges_generator.hpp"

namespace machine_code {
void LiveRangesGenerator::generate(const bblocks::BBControlFlowGraph& cfg,
                                   const std::map<std::string, std::pair<size_t, size_t>>& blockBounds) {
  for (const auto& blockLabel : blockBounds) {
    std::cout << blockLabel.first << " from " << blockLabel.second.first << " to " << blockLabel.second.second << std::endl;
  }
  std::cout << std::endl;

  for (const auto& block : cfg.getBasicBlocks()) {
    addDefsAndUses(block.first, block.second, blockBounds.at(block.first).first);
  }
  computeLiveInAndLiveOut(cfg);
  computeLiveRanges(cfg, blockBounds);
}

void LiveRangesGenerator::saveLiveRanges(const std::string& filename) {
  std::fstream file;
  file.open(filename, std::ios::out);

  file << "Defs in block:" << std::endl;
  for (const auto& [label, defs] : defsInBlock_) {
    file << label << ": " << std::endl;
    for (const auto& [variable, enumerators] : defs) {
      file << "  " << variable << ": ";
      for (const auto& enumerator : enumerators) {
        file << enumerator << " ";
      }
      file << std::endl;
    }
  }
  file << std::endl;

  file << "Uses in block:" << std::endl;
  for (const auto& [label, uses] : usesInBlock_) {
    file << label << ": " << std::endl;
    for (const auto& [variable, enumerators] : uses) {
      file << "  " << variable << ": ";
      for (const auto& enumerator : enumerators) {
        file << enumerator << " ";
      }
      file << std::endl;
    }
  }
  file << std::endl;

  file << "Live in:" << std::endl;
  for (const auto& [label, liveIn] : liveIn_) {
    file << label << ": ";
    for (const auto& variable : liveIn) {
      file << variable << " ";
    }
    file << std::endl;
  }
  file << std::endl;

  file << "Live out:" << std::endl;
  for (const auto& [label, liveOut] : liveOut_) {
    file << label << ": ";
    for (const auto& variable : liveOut) {
      file << variable << " ";
    }
    file << std::endl;
  }
  file << std::endl;

  file << "Live ranges:" << std::endl;
  for (const auto& [label, ranges] : liveRanges_) {
    file << label << ": " << std::endl;
    for (const auto& range : ranges) {
      file << "  " << range.first << " " << range.second << " " << std::endl;
    }
    file << std::endl;
  }

  file.close();
}

void LiveRangesGenerator::addDefsAndUses(const std::string& label, const bblocks::BasicBlock& block,
                                         size_t blockStartEnumerator) {
  size_t enumerator = blockStartEnumerator;
  for (const auto& instruction : block.getInstructions()) {
    defsInBlock_.insert({label, {}});

    std::cout << enumerator << ": " << *instruction;

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
          size_t firstDef =
              *std::min_element(defsInBlock_[block.first][use.first].begin(), defsInBlock_[block.first][use.first].end());

          size_t firstUse = *std::min_element(use.second.begin(), use.second.end());

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
                                            const std::map<std::string, std::pair<size_t, size_t>>& blockBounds) {
  std::set<std::string> allVariables;
  for (const auto& block : cfg.getBasicBlocks()) {
    for (const auto& def : defsInBlock_[block.first]) {
      allVariables.insert(def.first);
    }
    for (const auto& use : usesInBlock_[block.first]) {
      allVariables.insert(use.first);
    }
  }

  std::map<std::string, std::map<std::string, std::vector<std::vector<size_t>>>> liveRanges;
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
                                                               std::pair<size_t, size_t> blockBounds,
                                                               std::vector<std::vector<size_t>>& ranges) {
  bool isLiveIn = liveIn_[label].find(variable) != liveIn_[label].end();
  bool isLiveOut = liveOut_[label].find(variable) != liveOut_[label].end();

  std::vector<size_t> uses;
  if (usesInBlock_[label].find(variable) != usesInBlock_[label].end()) {
    uses = usesInBlock_[label][variable];
  }

  std::vector<size_t> defs;
  if (defsInBlock_[label].find(variable) != defsInBlock_[label].end()) {
    for (const auto& def : defsInBlock_[label][variable]) {
      if (std::find(uses.begin(), uses.end(), def) == uses.end()) {
        defs.push_back(def);
      }
    }
  }

  if ((!defs.empty() || isLiveIn) && (!uses.empty() || isLiveOut)) {
    size_t firstDef = isLiveIn ? blockBounds.first : *std::min_element(defs.begin(), defs.end());
    size_t lastUse = isLiveOut ? blockBounds.second : *std::max_element(uses.begin(), uses.end());

    std::vector<size_t> currentRange;
    for (size_t i = firstDef; i <= lastUse; i++) {
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
    const std::map<std::string, std::map<std::string, std::vector<std::vector<size_t>>>>& ranges) {
  for (const auto& blockChain : blockChains) {
    std::vector<std::pair<size_t, size_t>> mergedRanges;
    for (const auto& block : blockChain) {
      if (mergedRanges.empty()) {
        for (const auto& range : ranges.at(variable).at(block)) {
          mergedRanges.push_back({range.front(), range.back()});
        }
      }
      else {
        std::vector<std::pair<size_t, size_t>> newRanges;
        for (const auto& range : ranges.at(variable).at(block)) {
          newRanges.push_back({range.front(), range.back()});
        }
        mergedRanges.back().second = newRanges.front().second;
        for (size_t i = 1; i < newRanges.size(); i++) {
          mergedRanges.push_back(newRanges[i]);
        }
      }
    }

    std::sort(mergedRanges.begin(), mergedRanges.end(),
              [](const std::pair<size_t, size_t>& a, const std::pair<size_t, size_t>& b) { return a.first < b.first; });

    if (liveRanges_.find(variable) == liveRanges_.end()) {
      liveRanges_.insert({variable, mergedRanges});
    }
    else {
      liveRanges_[variable].insert(liveRanges_[variable].end(), mergedRanges.begin(), mergedRanges.end());
    }
  }

  for (auto& [var, rangesForVar] : liveRanges_) {
    std::sort(rangesForVar.begin(), rangesForVar.end(),
              [](const std::pair<size_t, size_t>& a, const std::pair<size_t, size_t>& b) {
                if (a.first == b.first) {
                  return a.second < b.second;
                }
                return a.first < b.first;
              });
  }

  for (auto& [var, rangesForVar] : liveRanges_) {
    std::vector<std::pair<size_t, size_t>> newRanges;
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