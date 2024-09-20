#ifndef BBLOCKS_BB_INSTRUCTION_HPP
#define BBLOCKS_BB_INSTRUCTION_HPP

#include <functional>
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
  enum class Type { UNSPECIFIED, BINARY_OPERATION, BRANCH, CALL, HALT, MOVE, RET, UNARY_OPERATION };
  enum class SourceType { CONSTANT, REGISTER, MEMORY };
  enum class DestinationType { REGISTER, MEMORY };

  BBInstruction() : type_{Type::UNSPECIFIED} {}
  BBInstruction(Type type) : type_{type} {}

  BBInstruction(const BBInstruction&) = default;
  BBInstruction(BBInstruction&&) noexcept = default;

  BBInstruction& operator=(const BBInstruction&) = default;
  BBInstruction& operator=(BBInstruction&&) noexcept = default;

  virtual ~BBInstruction() = default;

  Type getType() const { return type_; }

  // visit all variables that are defined by this instruction
  virtual void visitDefVariables(std::function<void(const VariableType&)> visitor) const = 0;

  // visit all variables that are used by this instruction
  virtual void visitUseVariables(std::function<void(const VariableType&)> visitor) const = 0;

  // changes all variables from to the variable to
  [[nodiscard]] virtual std::unique_ptr<BBInstruction> replaceVariable(const VariableType& from, const VariableType& to) = 0;

  // changes all variables from to the numeric to
  [[nodiscard]] virtual std::unique_ptr<BBInstruction> replaceVariable(const VariableType& from, const NumericType& to) = 0;

  [[nodiscard]] virtual std::unique_ptr<BBInstruction> clone() const = 0;
  virtual void print(std::ostream& out, int tab) const = 0;

  friend std::ostream& operator<<(std::ostream& out, const BBInstruction& instruction) {
    instruction.print(out, 0);
    return out;
  }

 private:
  Type type_;
};

}  // namespace bblocks

#endif  // BBLOCKS_BB_INSTRUCTION_HPP