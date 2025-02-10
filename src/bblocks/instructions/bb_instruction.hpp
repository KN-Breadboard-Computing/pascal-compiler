#ifndef BBLOCKS_BB_INSTRUCTION_HPP
#define BBLOCKS_BB_INSTRUCTION_HPP

#include <functional>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <type_traits>

#undef BB_DEBUG

typedef std::string VariableType;
typedef int16_t NumericType;
typedef std::string LabelType;

namespace bblocks {
class BBInstruction {
 public:
  enum class Type { UNSPECIFIED, BINARY_OPERATION, BRANCH, CALL, HALT, MOVE, PHI, RET, UNARY_OPERATION };
  enum class SourceType { CONSTANT, REGISTER, MEMORY };
  enum class DestinationType { REGISTER, MEMORY };
  enum class TemplateArgumentType { STRING, NUMBER };

  BBInstruction() : type_{Type::UNSPECIFIED}, canBeOptimizedOut_{true} {}
  BBInstruction(Type type, bool canBeOptimizedOut) : type_{type}, canBeOptimizedOut_{canBeOptimizedOut} {}

  BBInstruction(const BBInstruction&) = default;
  BBInstruction(BBInstruction&&) noexcept = default;

  BBInstruction& operator=(const BBInstruction&) = default;
  BBInstruction& operator=(BBInstruction&&) noexcept = default;

  virtual ~BBInstruction() = default;

  Type getType() const { return type_; }
  bool canBeOptimizedOut() const { return canBeOptimizedOut_; }

  // visit all variables that are defined by this instruction
  virtual void visitDefVariables(std::function<void(const VariableType&)> visitor) const = 0;

  // visit all variables that are used by this instruction
  virtual void visitUseVariables(std::function<void(const VariableType&)> visitor) const = 0;

  // changes all variables from to the variable to
  [[nodiscard]] virtual std::unique_ptr<BBInstruction> replaceVariable(const VariableType& from, const VariableType& to) = 0;

  // changes all variables from to the numeric to
  [[nodiscard]] virtual std::unique_ptr<BBInstruction> replaceVariable(const VariableType& from, const NumericType& to) = 0;

  virtual void replaceDefVariables(const VariableType& from, const VariableType& to) = 0;

  virtual void replaceUseVariables(const VariableType& from, const VariableType& to) = 0;

  // change all labels from to labels to
  virtual void replaceLabel(const LabelType& from, const LabelType& to) = 0;

  [[nodiscard]] virtual std::vector<TemplateArgumentType> getTemplateTypes() const = 0;
  [[nodiscard]] virtual std::unique_ptr<BBInstruction> clone() const = 0;
  virtual void print(std::ostream& out, int tab) const = 0;

  friend std::ostream& operator<<(std::ostream& out, const BBInstruction& instruction) {
    instruction.print(out, 0);
    return out;
  }

 protected:
  Type type_;
  bool canBeOptimizedOut_;
};

}  // namespace bblocks

#endif  // BBLOCKS_BB_INSTRUCTION_HPP