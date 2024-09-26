#include "linear_scan_reg_alloc.hpp"

namespace machine_code {
void LinearScanRegAlloc::allocateRegisters(size_t /*registersCount*/,
                                           std::map<std::string, std::vector<std::pair<size_t, size_t>>>& /*liveRanges*/) {}
}  // namespace machine_code