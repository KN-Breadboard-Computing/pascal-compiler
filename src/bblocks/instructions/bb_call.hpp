#ifndef BBLOCKS_BB_CALL_HPP
#define BBLOCKS_BB_CALL_HPP

namespace bblocks {
class BBCall : public BBInstruction {
 public:
  BBCall() = default;
  BBCall(std::string name) : name_(std::move(name)) {}

  BBCall(const BBCall&) = default;
  BBCall(BBCall&&) = default;

  BBCall& operator=(const BBCall&) = default;
  BBCall& operator=(BBCall&&) = default;

  ~BBCall() override = default;

  [[nodiscard]] const std::string& getName() const { return name_; }

  virtual void print(std::ostream& out, int tab) const override { out << std::string(tab, ' ') << "CALL" << name_ << std::endl; }

 private:
  std::string name_;
};
}  // namespace bblocks

#endif  // BBLOCKS_BB_CALL_HPP
