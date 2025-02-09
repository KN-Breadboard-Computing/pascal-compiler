#ifndef MACHINE_CODE_INTERFERENCE_GRAPH_REG_ALLOC_HPP
#define MACHINE_CODE_INTERFERENCE_GRAPH_REG_ALLOC_HPP

#include <set>
#include <stack>

#include "graph.hpp"
#include "interval_tree.hpp"
#include "reg_alloc.hpp"

namespace machine_code {
class InterferenceGraphRegAlloc : public RegAlloc {
 public:
  InterferenceGraphRegAlloc() = default;
  InterferenceGraphRegAlloc(int registersCount) : RegAlloc{registersCount} {}

  InterferenceGraphRegAlloc(const InterferenceGraphRegAlloc&) = delete;
  InterferenceGraphRegAlloc(InterferenceGraphRegAlloc&&) = default;

  InterferenceGraphRegAlloc& operator=(const InterferenceGraphRegAlloc&) = delete;
  InterferenceGraphRegAlloc& operator=(InterferenceGraphRegAlloc&&) = default;

  ~InterferenceGraphRegAlloc() = default;

  void allocateRegisters(const std::map<std::string, std::vector<LiveRange>>& liveRanges) override;

 private:
  void findColoring(Graph interferenceGraph);
};
}  // namespace machine_code

#endif  // MACHINE_CODE_INTERFERENCE_GRAPH_REG_ALLOC_HPP