#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#undef CONTEXT_DEBUG

#include <string>

#include "lookup_table.hpp"
#include "memory_layout.hpp"

class Context {
 public:
  Context(const Context&) = delete;
  Context(Context&&) = delete;

  Context& operator=(const Context&) = delete;
  Context& operator=(Context&&) = delete;

  ~Context() = default;

  static Context* getInstance() {
    if (instance_ == nullptr) {
      instance_ = new Context();
    }
    return instance_;
  }

  [[nodiscard]] std::string generateTempVariable() { return "#t" + std::to_string(tempVariableCounter_++); }
  [[nodiscard]] std::string getLastTempVariable() const { return "#t" + std::to_string(tempVariableCounter_ - 1); }

  [[nodiscard]] std::string generateBBlockLabel() { return "Block " + std::to_string(bblocksCounter_++); }
  [[nodiscard]] std::string getLastBBlockLabel() const { return "Block " + std::to_string(bblocksCounter_ - 1); }
  [[nodiscard]] std::vector<std::string> getNextBBlockLabels(size_t num) const {
    std::vector<std::string> labels;
    for (size_t i = 0; i < num; ++i) {
      labels.emplace_back("Block " + std::to_string(bblocksCounter_ + i));
    }
    return labels;
  }
  void resetBBlockLabel() { bblocksCounter_ = 0; }

  [[nodiscard]] LookupTable& getLookupTable() { return lookupTable_; }
  [[nodiscard]] MemoryLayout& getMemoryLayout() { return memoryLayout_; }

 protected:
  Context() : tempVariableCounter_{0}, bblocksCounter_{0} {}

 private:
  static Context* instance_;

  size_t tempVariableCounter_;
  size_t bblocksCounter_;

  LookupTable lookupTable_;
  MemoryLayout memoryLayout_;
};

#endif  // CONTEXT_HPP