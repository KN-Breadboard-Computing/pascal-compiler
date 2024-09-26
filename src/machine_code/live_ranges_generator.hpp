#ifndef MACHINE_CODE_LIVE_RANGES_GENERATOR_HPP
#define MACHINE_CODE_LIVE_RANGES_GENERATOR_HPP

#include <algorithm>
#include <fstream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#include "../bblocks/bb_control_flow_graph.hpp"
#include "machine_instruction.hpp"

namespace machine_code {
class LiveRangesGenerator {
 public:
  LiveRangesGenerator() = default;

  LiveRangesGenerator(const LiveRangesGenerator&) = delete;
  LiveRangesGenerator(LiveRangesGenerator&&) = default;

  LiveRangesGenerator& operator=(const LiveRangesGenerator&) = delete;
  LiveRangesGenerator& operator=(LiveRangesGenerator&&) = default;

  ~LiveRangesGenerator() = default;

  void generate(const bblocks::BBControlFlowGraph& cfg, const std::map<std::string, std::pair<size_t, size_t>>& blockBounds);

  [[nodiscard]] const std::map<std::string, std::set<std::string>>& getLiveIn() const { return liveIn_; }
  [[nodiscard]] const std::map<std::string, std::set<std::string>>& getLiveOut() const { return liveOut_; }
  [[nodiscard]] const std::map<std::string, std::vector<std::pair<size_t, size_t>>>& getLiveRanges() const { return liveRanges_; }

  void saveLiveRanges(const std::string& filename);

 private:
  void addDefsAndUses(const std::string& label, const bblocks::BasicBlock& block, size_t blockStartEnumerator);
  void computeLiveInAndLiveOut(const bblocks::BBControlFlowGraph& cfg);
  void computeLiveRanges(const bblocks::BBControlFlowGraph& cfg,
                         const std::map<std::string, std::pair<size_t, size_t>>& blockBounds);
  void computeLiveRangesForVariableAndBlock(const std::string& variable, const std::string& label,
                                            std::pair<size_t, size_t> blockBounds, std::vector<std::vector<size_t>>& ranges);
  void computeAllBlockChains(const bblocks::BBControlFlowGraph& cfg, const std::string& variable, const std::string& startLabel,
                             std::vector<std::vector<std::string>>& blockChains, std::vector<std::string> currentChain);
  void mergeLiveRanges(const std::string& variable, const std::vector<std::vector<std::string>>& blockChains,
                       const std::map<std::string, std::map<std::string, std::vector<std::vector<size_t>>>>& ranges);

  std::map<std::string, std::map<std::string, std::vector<size_t>>> defsInBlock_;
  std::map<std::string, std::map<std::string, std::vector<size_t>>> usesInBlock_;
  std::map<std::string, std::set<std::string>> liveIn_;
  std::map<std::string, std::set<std::string>> liveOut_;
  std::map<std::string, std::vector<std::pair<size_t, size_t>>> liveRanges_;
};
}  // namespace machine_code

#endif  // MACHINE_CODE_LIVE_RANGES_GENERATOR_HPP