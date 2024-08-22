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

  [[nodiscard]] std::string generateBasicBlockLabel() { return "bb" + std::to_string(basicBlockCounter_++); }

  [[nodiscard]] LookupTable& getLookupTable() { return lookupTable_; }
  [[nodiscard]] MemoryLayout& getMemoryLayout() { return memoryLayout_; }

 protected:
  Context() : tempVariableCounter_{0}, basicBlockCounter_{0} {}

 private:
  static Context* instance_;

  size_t tempVariableCounter_;
  size_t basicBlockCounter_;

  LookupTable lookupTable_;
  MemoryLayout memoryLayout_;
};

#endif  // CONTEXT_HPP