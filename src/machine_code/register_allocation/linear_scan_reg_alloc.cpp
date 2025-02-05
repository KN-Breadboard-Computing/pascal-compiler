#include "linear_scan_reg_alloc.hpp"

namespace machine_code {
void LinearScanRegAlloc::allocateRegisters(
    std::size_t /*registersCount*/, std::map<std::string, std::vector<std::pair<std::size_t, std::size_t>>>& /*liveRanges*/) {}
}  // namespace machine_code