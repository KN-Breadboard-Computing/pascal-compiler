#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#undef CONTEXT_DEBUG

#include <algorithm>
#include <string>
#include <vector>

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

  void pushScope(const std::string& name) {
    std::string loweredName = name;
    std::transform(loweredName.begin(), loweredName.end(), loweredName.begin(), [](unsigned char c) { return std::tolower(c); });
#ifdef CONTEXT_DEBUG
    std::cout << "Push scope: " << loweredName << std::endl;
#endif
    scopes_.push_back(loweredName);
  }

  void popScope() {
#ifdef CONTEXT_DEBUG
    std::cout << "Pop top of scope: " << getCurrentScope() << std::endl;
#endif
    scopes_.pop_back();
  }

  std::string getCurrentScope() const {
    std::string currentScope;
    for (const auto& scope : scopes_) {
      currentScope += "." + scope;
    }
    return currentScope;
  }

  const std::string& getTopScope() { return scopes_.back(); }

  [[nodiscard]] std::string generateTempVariable() { return "#t" + std::to_string(tempVariableCounter_++); }
  [[nodiscard]] std::string getLastTempVariable() const { return "#t" + std::to_string(tempVariableCounter_ - 1); }

  [[nodiscard]] std::string generateBasicBlockLabel() { return "bb" + std::to_string(basicBlockCounter_++); }

  [[nodiscard]] LookupTable& getLookupTable() { return lookupTable_; }
  [[nodiscard]] MemoryLayout& getMemoryLayout() { return memoryLayout_; }

 protected:
  Context() : tempVariableCounter_{0}, basicBlockCounter_{0} {}

 private:
  static Context* instance_;

  std::vector<std::string> scopes_;

  size_t tempVariableCounter_;
  size_t basicBlockCounter_;

  LookupTable lookupTable_;
  MemoryLayout memoryLayout_;
};

#endif  // CONTEXT_HPP