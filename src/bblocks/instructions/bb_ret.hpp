#ifndef BBLOCKS_BB_RET_HPP
#define BBLOCKS_BB_RET_HPP

#include "bb_instruction.hpp"

namespace bblocks {
class BBRet : public BBInstruction {
 public:
  BBRet() = default;

  BBRet(const BBRet&) = default;
  BBRet(BBRet&&) noexcept = default;

  BBRet& operator=(const BBRet&) = default;
  BBRet& operator=(BBRet&&) noexcept = default;

  ~BBRet() override = default;

  virtual std::unique_ptr<BBInstruction> clone() const override { return std::make_unique<BBRet>(); }

  virtual void print(std::ostream& out, int tab) const override { out << std::string(tab, ' ') << "ret" << std::endl; }
};
}  // namespace bblocks

#endif  // BBLOCKS_BB_RET_HPP
