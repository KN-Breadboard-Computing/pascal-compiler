#ifndef BBLOCKS_BB_LABEL_HPP
#define BBLOCKS_BB_LABEL_HPP

#include "bb_instruction.hpp"

namespace bblocks {
class BBLabel : public BBInstruction {
 public:
  explicit BBLabel(const LabelType& label) : label_(label) {}

  BBLabel(const BBLabel&) = default;
  BBLabel(BBLabel&&) noexcept = default;

  BBLabel& operator=(const BBLabel&) = default;
  BBLabel& operator=(BBLabel&&) noexcept = default;

  ~BBLabel() override = default;

  virtual std::unique_ptr<BBInstruction> clone() const override { return std::make_unique<BBLabel>(label_); }

  virtual void print(std::ostream& out, int tab) const override { out << std::string(tab, ' ') << label_ << ":" << std::endl; }

 private:
  LabelType label_;
};
}  // namespace bblocks

#endif  // BBLOCKS_BB_LABEL_HPP