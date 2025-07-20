#include "linear_scan_reg_alloc.hpp"

namespace machine_code {
LinearScanRegAlloc::LinearScanRegAlloc(int registersCount) : RegAlloc{registersCount} {
  freeRegisters_.resize(registersCount);
  std::iota(freeRegisters_.begin(), freeRegisters_.end(), 1);
}

void LinearScanRegAlloc::allocateRegisters(const std::map<std::string, std::vector<LiveRange>>& liveRanges) {
  std::vector<LiveRange> ranges;
  for (auto& [name, rangesForName] : liveRanges) {
    ranges.insert(ranges.end(), rangesForName.begin(), rangesForName.end());
  }

  std::sort(ranges.begin(), ranges.end(), [](const LiveRange& a, const LiveRange& b) { return a.front().instructionEnumerator < b.front().instructionEnumerator; });

  for (auto& range : ranges) {
    expireOldIntervals(range);
    if (static_cast<int>(activeIntervals_.size()) == registersCount_) {
      spillAtInterval(range);
    }
    else {
      range.setAllocatedRegister(freeRegisters_.back());
      freeRegisters_.pop_back();

      activeIntervals_.push_back(range);
      std::sort(activeIntervals_.begin(), activeIntervals_.end(), [](const LiveRange& a, const LiveRange& b) { return a.back().instructionEnumerator < b.back().instructionEnumerator; });
    }
  }

  for (const auto& range : ranges) {
    allocatedRegisters_[range.getVariable()] = range.getAllocatedRegister();
  }
}

void LinearScanRegAlloc::expireOldIntervals(const LiveRange& interval) {
  auto it = activeIntervals_.begin();
  while (it != activeIntervals_.end()) {
    if (it->back().instructionEnumerator >= interval.front().instructionEnumerator) {
      break;
    }
    freeRegisters_.push_back(it->getAllocatedRegister());
    it = activeIntervals_.erase(it);
  }
}

void LinearScanRegAlloc::spillAtInterval(LiveRange& interval) {
  LiveRange& spill = activeIntervals_.back();
  if (spill.back().instructionEnumerator > interval.back().instructionEnumerator) {
    interval.setAllocatedRegister(spill.getAllocatedRegister());
    spill.setAllocatedRegister(-1);
    activeIntervals_.pop_back();
    activeIntervals_.push_back(interval);
    std::sort(activeIntervals_.begin(), activeIntervals_.end(), [](const LiveRange& a, const LiveRange& b) { return a.back().instructionEnumerator < b.back().instructionEnumerator; });
  }
  else {
    interval.setAllocatedRegister(-1);
  }
}
}  // namespace machine_code