#ifndef MACHINE_CODE_INTERFERENCE_GRAPH_REG_ALLOC_HPP
#define MACHINE_CODE_INTERFERENCE_GRAPH_REG_ALLOC_HPP

#include <map>
#include <string>
#include <vector>

namespace machine_code {
class InterferenceGraphRegAlloc {
 public:
  InterferenceGraphRegAlloc() = default;

  InterferenceGraphRegAlloc(const InterferenceGraphRegAlloc&) = delete;
  InterferenceGraphRegAlloc(InterferenceGraphRegAlloc&&) = default;

  InterferenceGraphRegAlloc& operator=(const InterferenceGraphRegAlloc&) = delete;
  InterferenceGraphRegAlloc& operator=(InterferenceGraphRegAlloc&&) = default;

  ~InterferenceGraphRegAlloc() = default;

  void allocateRegisters(std::size_t registersCount, std::map<std::string, std::vector<std::string>>& interferenceGraph);
};
}  // namespace machine_code

#endif  // MACHINE_CODE_INTERFERENCE_GRAPH_REG_ALLOC_HPP