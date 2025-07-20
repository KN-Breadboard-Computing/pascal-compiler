#ifndef BBLOCKS_BB_CALL_HPP
#define BBLOCKS_BB_CALL_HPP

#include "bb_instruction.hpp"

namespace bblocks {
class BBCall : public BBInstruction {
 public:
  struct Argument {
    enum class Type { VARIABLE_USE, VARIABLE_DEF, CONSTANT };

    Type type;
    VariableType name;
    NumericType value;
  };

  BBCall() : BBInstruction(Type::CALL, true) {}
  BBCall(std::string name, std::vector<Argument> args, bool canBeOptimizedOut) : BBInstruction(Type::CALL, canBeOptimizedOut), name_{std::move(name)}, args_{std::move(args)} {}

  BBCall(const BBCall&) = default;
  BBCall(BBCall&&) noexcept = default;

  BBCall& operator=(const BBCall&) = default;
  BBCall& operator=(BBCall&&) noexcept = default;

  ~BBCall() override = default;

  [[nodiscard]] const std::string& getName() const { return name_; }

  [[nodiscard]] const std::vector<Argument>& getArgs() const { return args_; }

  virtual void visitDefVariables(std::function<void(const VariableType&)> visitor) const override {
    for (const auto& arg : args_) {
      if (arg.type == Argument::Type::VARIABLE_DEF) {
        visitor(arg.name);
      }
    }
  }

  virtual void visitUseVariables(std::function<void(const VariableType&)> visitor) const override {
    for (const auto& arg : args_) {
      if (arg.type == Argument::Type::VARIABLE_USE) {
        visitor(arg.name);
      }
    }
  }

  virtual std::unique_ptr<BBInstruction> replaceVariable(const VariableType& from, const VariableType& to) override {
    std::vector<Argument> newArgs;
    for (const auto& arg : args_) {
      if ((arg.type == Argument::Type::VARIABLE_USE || arg.type == Argument::Type::VARIABLE_DEF) && arg.name == from) {
        newArgs.push_back({arg.type, to, 0});
      }
      else {
        newArgs.push_back(arg);
      }
    }

    return std::make_unique<BBCall>(name_, newArgs, canBeOptimizedOut_);
  }

  virtual std::unique_ptr<BBInstruction> replaceVariable(const VariableType& from, const NumericType& to) override {
    std::vector<Argument> newArgs;
    for (const auto& arg : args_) {
      if ((arg.type == Argument::Type::VARIABLE_USE || arg.type == Argument::Type::VARIABLE_DEF) && arg.name == from) {
        newArgs.push_back({Argument::Type::CONSTANT, "", to});
      }
      else {
        newArgs.push_back(arg);
      }
    }

    return std::make_unique<BBCall>(name_, newArgs, canBeOptimizedOut_);
  }

  virtual void replaceDefVariables(const VariableType& from, const VariableType& to) override {
    for (auto& arg : args_) {
      if (arg.type == Argument::Type::VARIABLE_DEF && arg.name == from) {
        arg.name = to;
      }
    }
  }

  virtual void replaceUseVariables(const VariableType& from, const VariableType& to) override {
    for (auto& arg : args_) {
      if (arg.type == Argument::Type::VARIABLE_USE && arg.name == from) {
        arg.name = to;
      }
    }
  }

  virtual void replaceLabel(const LabelType& /*from*/, const LabelType& /*to*/) override {}

  [[nodiscard]] virtual std::vector<TemplateArgumentType> getTemplateTypes() const override { return std::vector<TemplateArgumentType>{}; }

  virtual std::unique_ptr<BBInstruction> clone() const override { return std::make_unique<BBCall>(name_, args_, canBeOptimizedOut_); }

  virtual void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ') << "call " << name_ << "( ";
    for (const auto& arg : args_) {
      if (arg.type == Argument::Type::VARIABLE_USE) {
        out << arg.name << " ";
      }
      else if (arg.type == Argument::Type::VARIABLE_DEF) {
        out << "&" << arg.name << " ";
      }
      else {
        out << arg.value << " ";
      }
    }
    out << ")" << std::endl;
  }

 private:
  std::string name_;
  std::vector<Argument> args_;
};
}  // namespace bblocks

#endif  // BBLOCKS_BB_CALL_HPP
