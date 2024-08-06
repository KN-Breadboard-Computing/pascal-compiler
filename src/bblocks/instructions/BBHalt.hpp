#ifndef BBLOCKS_BB_HALT_HPP
#define BBLOCKS_BB_HALT_HPP

#include "BBInstruction.hpp"

namespace bblocks {
class BBHalt : public BBInstruction {
 public:
  BBHalt() = default;

  BBHalt(const BBHalt&) = default;
  BBHalt(BBHalt&&) = default;

  BBHalt& operator=(const BBHalt&) = default;
  BBHalt& operator=(BBHalt&&) = default;

  ~BBHalt() override = default;

  friend virtual std::ostream& operator<<(std::ostream& out, const BBHalt& instruction) override {
    out << "HALT" << std::endl;
    return out;
  }
};
}  // namespace bblocks

#endif  // BBLOCKS_BB_HALT_HPP
