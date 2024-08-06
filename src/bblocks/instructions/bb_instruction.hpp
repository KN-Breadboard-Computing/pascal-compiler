#ifndef BBLOCKS_BB_INSTRUCTION_HPP
#define BBLOCKS_BB_INSTRUCTION_HPP

#include <type_traits>
#include <ostream>
#include <string>

typedef std::string VariableType;
typedef int64_t NumericType;
typedef std::size_t LabelType;
typedef std::size_t AddressType;

namespace bblocks {
class BBInstruction {
 public:
  BBInstruction() = default;

  BBInstruction(const BBInstruction&) = default;
  BBInstruction(BBInstruction&&) = default;

  BBInstruction& operator=(const BBInstruction&) = default;
  BBInstruction& operator=(BBInstruction&&) = default;

  virtual ~BBInstruction() = default;

  virtual void print(std::ostream& out, int tab) const = 0;

  friend std::ostream& operator<<(std::ostream& out, const BBInstruction& instruction) {
    instruction.print(out, 0);
    return out;
  }
};

}  // namespace bblocks

#endif  // BBLOCKS_BB_INSTRUCTION_HPP