#ifndef MACHINE_CODE_LINEAR_SCAN_REG_ALLOC_HPP
#define MACHINE_CODE_LINEAR_SCAN_REG_ALLOC_HPP

#include "reg_alloc.hpp"

namespace machine_code {
class LinearScanRegAlloc : public RegAlloc {
 public:
  LinearScanRegAlloc() = default;
  LinearScanRegAlloc(int registersCount);

  LinearScanRegAlloc(const LinearScanRegAlloc&) = delete;
  LinearScanRegAlloc(LinearScanRegAlloc&&) = default;

  LinearScanRegAlloc& operator=(const LinearScanRegAlloc&) = delete;
  LinearScanRegAlloc& operator=(LinearScanRegAlloc&&) = default;

  ~LinearScanRegAlloc() = default;

  void allocateRegisters(const std::map<std::string, std::vector<LiveRange>>& liveRanges) override;

 private:
  void expireOldIntervals(const LiveRange& interval);
  void spillAtInterval(LiveRange& interval);

  std::vector<int> freeRegisters_;
  std::vector<LiveRange> activeIntervals_;
};
}  // namespace machine_code

#endif  // MACHINE_CODE_LINEAR_SCAN_REG_ALLOC_HPP