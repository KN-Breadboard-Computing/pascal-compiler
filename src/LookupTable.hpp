#ifndef LOOKUP_TABLE_HPP
#define LOOKUP_TABLE_HPP

#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

class LookupTable {
 public:
  enum TypeCategory { SIMPLE, ARRAY, RECORD };
  struct TypeInfo {
    TypeCategory category{};
    std::string name{};
    std::string type{};
  };

  struct VariableInfo {
    bool isConst{};
    bool isInitialized{};
    std::string name{};
    std::string type{};
    std::string value{};
  };

  enum RoutineCategory { FUNCTION, PROCEDURE };
  struct RoutineInfo {
    RoutineCategory category{};
    std::string name{};
    std::string type{};
  };

  LookupTable() : namespaces_{}, types_{}, variables_{}, routines_{} {}

  LookupTable(const LookupTable&) = default;
  LookupTable(LookupTable&&) = default;

  LookupTable& operator=(const LookupTable&) = default;
  LookupTable& operator=(LookupTable&&) = default;

  ~LookupTable() = default;

  void pushNamespace(const std::string& name) { namespaces_.push(name); }

  void popNamespace() { namespaces_.pop(); }

  [[nodiscard]] const std::string& getTopNamespace() const { return namespaces_.top(); }

  void addType(TypeCategory category, const std::string& name, const std::string& type) {
    types_[getTopNamespace() + name] = TypeInfo{category, name, type};
  }

  [[nodiscard]] const TypeInfo& getType(const std::string& name) const { return types_.at(getTopNamespace() + name); }

  void addVariable(bool isConst, const std::string& name, const std::string& type, const std::string& value) {
    variables_[getTopNamespace() + name] = VariableInfo{isConst, false, name, type, value};
  }

  void setVariableValue(const std::string& name, const std::string& value) {
    variables_[getTopNamespace() + name].value = value;
    variables_[getTopNamespace() + name].isInitialized = true;
  }

  [[nodiscard]] const VariableInfo& getVariable(const std::string& name) const { return variables_.at(getTopNamespace() + name); }

  void addRoutine(RoutineCategory category, const std::string& name, const std::string& type) {
    routines_[getTopNamespace() + name] = RoutineInfo{category, name, type};
  }

  [[nodiscard]] const RoutineInfo& getRoutine(const std::string& name) const { return routines_.at(getTopNamespace() + name); }

 private:
  std::stack<std::string> namespaces_;
  std::map<std::string, TypeInfo> types_;
  std::map<std::string, VariableInfo> variables_;
  std::map<std::string, RoutineInfo> routines_;
};

#endif  // LOOKUP_TABLE_HPP
