#ifndef BBLOCKS_BB_INSTRUCTION_HPP
#define BBLOCKS_BB_INSTRUCTION_HPP

#include <memory>
#include <ostream>
#include <string>
#include <type_traits>

#define BB_DEBUG

typedef std::string VariableType;
typedef int64_t NumericType;
typedef bool BooleanType;
typedef std::string LabelType;
typedef std::size_t AddressType;

namespace bblocks {
class BBInstruction {
 public:
  BBInstruction() = default;

  BBInstruction(const BBInstruction&) = default;
  BBInstruction(BBInstruction&&) noexcept = default;

  BBInstruction& operator=(const BBInstruction&) = default;
  BBInstruction& operator=(BBInstruction&&) noexcept = default;

  virtual ~BBInstruction() = default;

  [[nodiscard]] virtual std::unique_ptr<BBInstruction> clone() const = 0;
  virtual void print(std::ostream& out, int tab) const = 0;

  friend std::ostream& operator<<(std::ostream& out, const BBInstruction& instruction) {
    instruction.print(out, 0);
    return out;
  }
};

}  // namespace bblocks

#endif  // BBLOCKS_BB_INSTRUCTION_HPP