#ifndef BBLOCKS_BB_HALT_HPP
#define BBLOCKS_BB_HALT_HPP

#include "bb_instruction.hpp"

namespace bblocks {
class BBHalt : public BBInstruction {
 public:
  BBHalt() = default;

  BBHalt(const BBHalt&) = default;
  BBHalt(BBHalt&&) = default;

  BBHalt& operator=(const BBHalt&) = default;
  BBHalt& operator=(BBHalt&&) = default;

  ~BBHalt() override = default;

  virtual void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ') << "HALT" << std::endl;
  }
};
}  // namespace bblocks

#endif  // BBLOCKS_BB_HALT_HPP
