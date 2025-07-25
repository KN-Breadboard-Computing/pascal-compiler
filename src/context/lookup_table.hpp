#ifndef LOOKUP_TABLE_HPP
#define LOOKUP_TABLE_HPP

#include <functional>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <utility>
#include <vector>

class LookupTable {
 public:
  enum class TypeCategory { SIMPLE, ARRAY, RECORD };
  struct TypeInfo {
    TypeCategory category{};
    std::string name{};
    std::string fullName{};
    std::string type{};
    bool alive{};
  };

  enum class VariableCategory { VARIABLE, CONSTANT };
  struct VariableInfo {
    VariableCategory category{};
    std::string name{};
    std::string fullName{};
    std::string type{};
    bool isInitialized{};
    bool alive;
  };

  enum class RoutineCategory { FUNCTION, PROCEDURE };
  struct ArgumentInfo {
    std::string name{};
    std::string type{};
    bool isReference{};
  };
  struct RoutineInfo {
    RoutineCategory category{};
    std::string name{};
    std::string fullName{};
    std::vector<ArgumentInfo> args{};
    std::string type{};
    bool alive{};
  };

  LookupTable() {
    types_["integer"][""] = TypeInfo{TypeCategory::SIMPLE, "integer", "integer", "integer", true};
    types_["boolean"][""] = TypeInfo{TypeCategory::SIMPLE, "boolean", "boolean", "boolean", true};
    types_["char"][""] = TypeInfo{TypeCategory::SIMPLE, "char", "char", "char", true};
    types_["string"][""] = TypeInfo{TypeCategory::SIMPLE, "string", "string", "string", true};
  }

  LookupTable(const LookupTable&) = default;
  LookupTable(LookupTable&&) = default;

  LookupTable& operator=(const LookupTable&) = default;
  LookupTable& operator=(LookupTable&&) = default;

  ~LookupTable() = default;

  void undefineTypesVarsRoutines(const std::string& currentScope) {
    for (auto& [name, scopes] : types_) {
      for (auto& [scope, typeInfo] : scopes) {
        if (currentScope == scope) {
#ifdef CONTEXT_DEBUG
          std::cout << "UnDefine type: " << scope << " " << name << std::endl;
#endif
          typeInfo.alive = false;
        }
      }
    }

    for (auto& [name, scopes] : variables_) {
      for (auto& [scope, variableInfo] : scopes) {
        if (currentScope == scope) {
#ifdef CONTEXT_DEBUG
          std::cout << "UnDefine variable: " << scope << " " << name << std::endl;
#endif
          variableInfo.alive = false;
        }
      }
    }

    for (auto& [name, scopes] : routines_) {
      for (auto& [scope, routineInfo] : scopes) {
        if (currentScope == scope) {
#ifdef CONTEXT_DEBUG
          std::cout << "UnDefine routine: " << scope << " " << name << std::endl;
#endif
          routineInfo.alive = false;
        }
      }
    }
  }

  void defineType(TypeCategory category, const std::string& name, std::string type, const std::string& currentScope) {
#ifdef CONTEXT_DEBUG
    std::cout << "Define type: " << currentScope << " " << name << " " << static_cast<int>(category) << " " << type << std::endl;
#endif
    types_[name][currentScope] = TypeInfo{category, name, currentScope + "." + name, std::move(type), true};
  }

  [[nodiscard]] bool isTypeDefined(const std::string& name, const std::string& currentScope) const {
    if (types_.find(name) != types_.end()) {
      for (const auto& [scopeName, typeInfo] : types_.at(name)) {
        if (currentScope.find(scopeName) == 0 && typeInfo.alive) {
          return true;
        }
      }
    }
    return false;
  }

  [[nodiscard]] const TypeInfo& getType(const std::string& name, const std::string& currentScope) const {
    if (types_.find(name) != types_.end()) {
      for (const auto& [scopeName, typeInfo] : types_.at(name)) {
        if (currentScope.find(scopeName) == 0) {
          return typeInfo;
        }
      }
    }
    throw std::runtime_error("Type not found");
  }

  [[nodiscard]] std::vector<TypeInfo> getTypes(const std::function<bool(const std::string&, const TypeInfo&)>& indicator, const std::string& currentScope) const {
    std::vector<TypeInfo> result;
    for (const auto& [name, scopes] : types_) {
      for (const auto& [scopeName, typeInfo] : scopes) {
        if (currentScope.find(scopeName) == 0 && indicator(name, typeInfo)) {
          result.push_back(typeInfo);
        }
      }
    }
    return result;
  }

  void unDefineType(const std::string& name, const std::string& currentScope) {
#ifdef CONTEXT_DEBUG
    std::cout << "UnDefine type: " << currentScope << " " << name << std::endl;
#endif
    if (types_.find(name) != types_.end()) {
      for (const auto& [scopeName, typeInfo] : types_.at(name)) {
        if (currentScope.find(scopeName) == 0) {
          types_[name][scopeName].alive = false;
          return;
        }
      }
    }
  }

  bool isBasicType(const std::string& name) const { return name == "integer" || name == "boolean" || name == "char" || name.find("enum%") == 0; }

  void defineVariable(VariableCategory category, const std::string& name, std::string type, const std::string& currentScope) {
#ifdef CONTEXT_DEBUG
    std::cout << "Define variable: " << currentScope << " " << name << " " << static_cast<int>(category) << " " << type << std::endl;
#endif
    variables_[name][currentScope] = VariableInfo{category, name, currentScope + "." + name, std::move(type), false, true};
  }

  void setVariableValue(const std::string& name, const std::string& /*value*/, const std::string& currentScope) {
#ifdef CONTEXT_DEBUG
    std::cout << "Set variable value: " << currentScope << " " << name << std::endl;
#endif
    if (variables_.find(name) != variables_.end()) {
      for (auto& [scopeName, variableInfo] : variables_.at(name)) {
        if (currentScope.find(scopeName) == 0) {
          variableInfo.isInitialized = true;
          return;
        }
      }
    }
  }

  [[nodiscard]] bool isVariableDefined(const std::string& name, const std::string& currentScope) const {
    if (variables_.find(name) != variables_.end()) {
      for (const auto& [scopeName, variableInfo] : variables_.at(name)) {
        if (currentScope.find(scopeName) == 0 && variableInfo.alive) {
          return true;
        }
      }
    }
    return false;
  }

  [[nodiscard]] bool isVariableInitialized(const std::string& name, const std::string& currentScope) const {
    if (variables_.find(name) != variables_.end()) {
      for (const auto& [scopeName, variableInfo] : variables_.at(name)) {
        if (currentScope.find(scopeName) == 0) {
          return variableInfo.isInitialized;
        }
      }
    }
    return false;
  }

  [[nodiscard]] bool isVariableConst(const std::string& name, const std::string& currentScope) const {
    if (variables_.find(name) != variables_.end()) {
      for (const auto& [scopeName, variableInfo] : variables_.at(name)) {
        if (currentScope.find(scopeName) == 0) {
          return variableInfo.category == VariableCategory::CONSTANT;
        }
      }
    }
    return false;
  }

  [[nodiscard]] const VariableInfo& getVariable(const std::string& name, const std::string& currentScope) const {
    if (variables_.find(name) != variables_.end()) {
      for (const auto& [scopeName, variableInfo] : variables_.at(name)) {
        if (currentScope.find(scopeName) == 0) {
          return variableInfo;
        }
      }
    }
    throw std::runtime_error("Variable not found");
  }

  void unDefineVariable(const std::string& name, const std::string& currentScope) {
#ifdef CONTEXT_DEBUG
    std::cout << "UnDefine variable: " << currentScope << " " << name << std::endl;
#endif
    if (variables_.find(name) != variables_.end()) {
      for (auto& [scopeName, variableInfo] : variables_.at(name)) {
        if (currentScope.find(scopeName) == 0) {
          variableInfo.alive = false;
          return;
        }
      }
    }
  }

  void defineRoutine(RoutineCategory category, const std::string& name, const std::vector<ArgumentInfo>& args, std::string type, const std::string& currentScope) {
#ifdef CONTEXT_DEBUG
    std::cout << "Define routine: " << currentScope << " " << name << " " << static_cast<int>(category) << " [";
    for (const auto& arg : args) {
      std::cout << arg.name << " is " << arg.type << ",";
    }
    std::cout << "] " << type << std::endl;
#endif
    routines_[name][currentScope] = RoutineInfo{category, name, currentScope + "." + name, args, std::move(type), true};
  }

  [[nodiscard]] bool isRoutineDefined(const std::string& name, const std::string& currentScope) const {
    if (routines_.find(name) != routines_.end()) {
      for (const auto& [scopeName, routineInfo] : routines_.at(name)) {
        if (currentScope.find(scopeName) == 0 && routineInfo.alive) {
          return true;
        }
      }
    }
    return false;
  }

  [[nodiscard]] const RoutineInfo& getRoutine(const std::string& name, const std::string& currentScope) const {
    if (routines_.find(name) != routines_.end()) {
      for (const auto& [scopeName, routineInfo] : routines_.at(name)) {
        if (currentScope.find(scopeName) == 0) {
          return routineInfo;
        }
      }
    }
    throw std::runtime_error("Routine not found");
  }

  void unDefineRoutine(const std::string& name, const std::string& currentScope) {
#ifdef CONTEXT_DEBUG
    std::cout << "UnDefine routine: " << currentScope << " " << name << std::endl;
#endif
    if (routines_.find(name) != routines_.end()) {
      for (auto& [scopeName, routineInfo] : routines_.at(name)) {
        if (currentScope.find(scopeName) == 0) {
          routineInfo.alive = false;
          return;
        }
      }
    }
  }

 private:
  std::map<std::string, std::map<std::string, TypeInfo>> types_;
  std::map<std::string, std::map<std::string, VariableInfo>> variables_;
  std::map<std::string, std::map<std::string, RoutineInfo>> routines_;
};

#endif  // LOOKUP_TABLE_HPP
