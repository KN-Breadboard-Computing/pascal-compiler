#ifndef MACHINE_CODE_LINEAR_SCAN_REG_ALLOC_HPP
#define MACHINE_CODE_LINEAR_SCAN_REG_ALLOC_HPP

#include <map>
#include <string>
#include <vector>

namespace machine_code {
class LinearScanRegAlloc {
 public:
  LinearScanRegAlloc() = default;

  LinearScanRegAlloc(const LinearScanRegAlloc&) = delete;
  LinearScanRegAlloc(LinearScanRegAlloc&&) = default;

  LinearScanRegAlloc& operator=(const LinearScanRegAlloc&) = delete;
  LinearScanRegAlloc& operator=(LinearScanRegAlloc&&) = default;

  ~LinearScanRegAlloc() = default;

  void allocateRegisters(std::size_t registersCount,
                         std::map<std::string, std::vector<std::pair<std::size_t, std::size_t>>>& liveRanges);
};
}  // namespace machine_code

#endif  // MACHINE_CODE_LINEAR_SCAN_REG_ALLOC_HPP