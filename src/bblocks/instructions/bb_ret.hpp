#ifndef BBLOCKS_BB_RET_HPP
#define BBLOCKS_BB_RET_HPP

namespace bblocks {
class BBRet : public BBInstruction {
 public:
  BBRet() = default;

  BBRet(const BBRet&) = default;
  BBRet(BBRet&&) = default;

  BBRet& operator=(const BBRet&) = default;
  BBRet& operator=(BBRet&&) = default;

  ~BBRet() override = default;

  virtual void print(std::ostream& out, int tab) const override { out << std::string(tab, ' ') << "RET" << std::endl; }
};
}  // namespace bblocks

#endif  // BBLOCKS_BB_RET_HPP
