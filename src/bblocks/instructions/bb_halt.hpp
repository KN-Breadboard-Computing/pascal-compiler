#ifndef BBLOCKS_BB_HALT_HPP
#define BBLOCKS_BB_HALT_HPP

#include "bb_instruction.hpp"

namespace bblocks {
class BBHalt : public BBInstruction {
 public:
  BBHalt() : BBInstruction(Type::HALT, false) {}

  BBHalt(const BBHalt&) = default;
  BBHalt(BBHalt&&) noexcept = default;

  BBHalt& operator=(const BBHalt&) = default;
  BBHalt& operator=(BBHalt&&) noexcept = default;

  ~BBHalt() override = default;

  virtual void visitDefVariables(std::function<void(const VariableType&)> /*visitor*/) const override {}

  virtual void visitUseVariables(std::function<void(const VariableType&)> /*visitor*/) const override {}

  virtual std::unique_ptr<BBInstruction> replaceVariable(const VariableType& /*from*/, const VariableType& /*to*/) override { return clone(); }

  virtual std::unique_ptr<BBInstruction> replaceVariable(const VariableType& /*from*/, const NumericType& /*to*/) override { return clone(); }

  virtual void replaceDefVariables(const VariableType& /*from*/, const VariableType& /*to*/) override {}

  virtual void replaceUseVariables(const VariableType& /*from*/, const VariableType& /*to*/) override {}

  virtual void replaceLabel(const LabelType& /*from*/, const LabelType& /*to*/) override {}

  [[nodiscard]] virtual std::vector<TemplateArgumentType> getTemplateTypes() const override { return std::vector<TemplateArgumentType>{}; }

  virtual std::unique_ptr<BBInstruction> clone() const override { return std::make_unique<BBHalt>(); }

  virtual void print(std::ostream& out, int tab) const override { out << std::string(tab, ' ') << "halt" << std::endl; }
};
}  // namespace bblocks

#endif  // BBLOCKS_BB_HALT_HPP
