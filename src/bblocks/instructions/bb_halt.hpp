#ifndef BBLOCKS_BB_HALT_HPP
#define BBLOCKS_BB_HALT_HPP

#include "bb_instruction.hpp"

namespace bblocks {
class BBHalt : public BBInstruction {
 public:
  BBHalt() = default;

  BBHalt(const BBHalt&) = default;
  BBHalt(BBHalt&&) noexcept = default;

  BBHalt& operator=(const BBHalt&) = default;
  BBHalt& operator=(BBHalt&&) noexcept = default;

  ~BBHalt() override = default;

  virtual std::unique_ptr<BBInstruction> clone() const override { return std::make_unique<BBHalt>(); }

  virtual void print(std::ostream& out, int tab) const override { out << std::string(tab, ' ') << "halt" << std::endl; }
};
}  // namespace bblocks

#endif  // BBLOCKS_BB_HALT_HPP
