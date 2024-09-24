#ifndef BBLOCKS_BB_CALL_HPP
#define BBLOCKS_BB_CALL_HPP

#include "bb_instruction.hpp"

namespace bblocks {
class BBCall : public BBInstruction {
 public:
  BBCall() : BBInstruction(Type::CALL) {}
  BBCall(std::string name, std::vector<std::string> args)
      : BBInstruction(Type::CALL), name_{std::move(name)}, args_{std::move(args)} {}

  BBCall(const BBCall&) = default;
  BBCall(BBCall&&) noexcept = default;

  BBCall& operator=(const BBCall&) = default;
  BBCall& operator=(BBCall&&) noexcept = default;

  ~BBCall() override = default;

  [[nodiscard]] const std::string& getName() const { return name_; }

  [[nodiscard]] const std::vector<std::string>& getArgs() const { return args_; }

  virtual void visitDefVariables(std::function<void(const VariableType&)> /*visitor*/) const override {}

  virtual void visitUseVariables(std::function<void(const VariableType&)> /*visitor*/) const override {}

  virtual std::unique_ptr<BBInstruction> replaceVariable(const VariableType& /*from*/, const VariableType& /*to*/) override {
    return clone();
  }

  virtual std::unique_ptr<BBInstruction> replaceVariable(const VariableType& /*from*/, const NumericType& /*to*/) override {
    return clone();
  }

  virtual void replaceDefVariables(const VariableType& /*from*/, const VariableType& /*to*/) override {}

  virtual void replaceUseVariables(const VariableType& /*from*/, const VariableType& /*to*/) override {}

  virtual void replaceLabel(const LabelType& /*from*/, const LabelType& /*to*/) override {}

  [[nodiscard]] virtual std::vector<TemplateArgumentType> getTemplateTypes() const override {
    return std::vector<TemplateArgumentType>{};
  }

  virtual std::unique_ptr<BBInstruction> clone() const override { return std::make_unique<BBCall>(name_, args_); }

  virtual void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ') << "call " << name_ << "( ";
    for (const auto& arg : args_) {
      out << arg << " ";
    }
    out << ")" << std::endl;
  }

 private:
  std::string name_;
  std::vector<std::string> args_;
};
}  // namespace bblocks

#endif  // BBLOCKS_BB_CALL_HPP
