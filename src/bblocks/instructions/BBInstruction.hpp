#ifndef BBLOCKS_BB_INSTRUCTION_HPP
#define BBLOCKS_BB_INSTRUCTION_HPP

#include <ostream>
#include <string>
#include <type_traits>

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

  friend virtual std::ostream& operator<<(std::ostream& out, const BBInstruction& instruction) = 0;
};

}  // namespace bblocks

#endif  // BBLOCKS_BB_INSTRUCTION_HPP