#ifndef MEMORY_LAYOUT_HPP
#define MEMORY_LAYOUT_HPP

#include <map>
#include <string>

class MemoryLayout {
 public:
  MemoryLayout() = default;

  MemoryLayout(const MemoryLayout&) = default;
  MemoryLayout(MemoryLayout&&) = default;

  MemoryLayout& operator=(const MemoryLayout&) = default;
  MemoryLayout& operator=(MemoryLayout&&) = default;

  ~MemoryLayout() = default;


 private:
  std::map<std::string, size_t> memoryAddresses_;
  std::map<std::string, size_t> stackOffsets_;
};

#endif  // MEMORY_LAYOUT_HPP
