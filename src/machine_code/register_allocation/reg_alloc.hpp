#ifndef REG_ALLOC_HPP
#define REG_ALLOC_HPP

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

#include "../live_range.hpp"

namespace machine_code {
class RegAlloc {
 public:
  RegAlloc() = default;
  RegAlloc(int registersCount) : registersCount_{registersCount} {}

  RegAlloc(const RegAlloc&) = delete;
  RegAlloc(RegAlloc&&) = default;

  RegAlloc& operator=(const RegAlloc&) = delete;
  RegAlloc& operator=(RegAlloc&&) = default;

  virtual ~RegAlloc() = default;

  virtual void allocateRegisters(const std::map<std::string, std::vector<LiveRange>>& liveRanges) = 0;

  int getRegistersCount() const { return registersCount_; }

  const std::map<std::string, int>& getAllocatedRegisters() const { return allocatedRegisters_; }
  const std::map<std::string, std::vector<std::size_t>>& getLoadInstructions() const { return loadInstructions_; }
  const std::map<std::string, std::vector<std::size_t>>& getStoreInstructions() const { return storeInstructions_; }

  void saveAllocatedRegisters(std::ostream& output) const {
    for (const auto& [name, registerNumber] : allocatedRegisters_) {
      output << name << " -> " << registerNumber << std::endl;
    }
  }

 protected:
  int registersCount_;
  std::map<std::string, int> allocatedRegisters_;
  std::map<std::string, std::vector<std::size_t>> loadInstructions_;
  std::map<std::string, std::vector<std::size_t>> storeInstructions_;
};
}  // namespace machine_code

#endif  // REG_ALLOC_HPP