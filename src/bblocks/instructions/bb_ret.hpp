#ifndef BBLOCKS_BB_RET_HPP
#define BBLOCKS_BB_RET_HPP

#include "bb_instruction.hpp"

namespace bblocks {
class BBRet : public BBInstruction {
 public:
  BBRet() : BBInstruction(Type::RET, false) {}

  BBRet(const BBRet&) = default;
  BBRet(BBRet&&) noexcept = default;

  BBRet& operator=(const BBRet&) = default;
  BBRet& operator=(BBRet&&) noexcept = default;

  ~BBRet() override = default;

  virtual void visitDefVariables(std::function<void(const VariableType&)> /*visitor*/) const override {}

  virtual void visitUseVariables(std::function<void(const VariableType&)> /*visitor*/) const override {}

  virtual std::unique_ptr<BBInstruction> replaceVariable(const VariableType& /*from*/, const VariableType& /*to*/) override { return clone(); }

  virtual std::unique_ptr<BBInstruction> replaceVariable(const VariableType& /*from*/, const NumericType& /*to*/) override { return clone(); }

  virtual void replaceDefVariables(const VariableType& /*from*/, const VariableType& /*to*/) override {}

  virtual void replaceUseVariables(const VariableType& /*from*/, const VariableType& /*to*/) override {}

  virtual void replaceLabel(const LabelType& /*from*/, const LabelType& /*to*/) override {}

  [[nodiscard]] virtual std::vector<TemplateArgumentType> getTemplateTypes() const override { return std::vector<TemplateArgumentType>{}; }

  virtual std::unique_ptr<BBInstruction> clone() const override { return std::make_unique<BBRet>(); }

  virtual void print(std::ostream& out, int tab) const override { out << std::string(tab, ' ') << "ret" << std::endl; }
};
}  // namespace bblocks

#endif  // BBLOCKS_BB_RET_HPP
