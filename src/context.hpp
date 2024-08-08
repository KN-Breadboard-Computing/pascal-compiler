#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#define CONTEXT_DEBUG

#include <string>

#include "lookup_table.hpp"

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

  std::string generateBBVariable() { return "bbv#" + std::to_string(bbVariableCounter_++); }

  [[nodiscard]] LookupTable& getLookupTable() { return lookupTable_; }

 protected:
  Context() : lookupTable_{} {}

 private:
  static Context* instance_;
  size_t bbVariableCounter_{0};
  LookupTable lookupTable_;
};

#endif  // CONTEXT_HPP