#ifndef BBLOCKS_BB_PUSH_HPP
#define BBLOCKS_BB_PUSH_HPP

#include "bb_instruction.hpp"

namespace bblocks {
template <typename SrcT>
concept PushArgs = requires {
  {std::is_same_v<SrcT, VariableType> || std::is_same_v<SrcT, NumericType> || std::is_same_v<SrcT, AddressType>};
};

template <typename SrcT>
requires PushArgs<SrcT> class BBPush : public BBInstruction {
 public:
  enum class SourceType { VARIABLE, ADDRESS };

  BBPush() = default;
  BBPush(SrcT source, SourceType sourceType) : source_{source}, sourceType_{sourceType} {}

  BBPush(const BBPush&) = default;
  BBPush(BBPush&&) noexcept = default;

  BBPush& operator=(const BBPush&) = default;
  BBPush& operator=(BBPush&&) noexcept = default;

  ~BBPush() override = default;

  [[nodiscard]] SrcT getSource() const { return source_; }
  [[nodiscard]] SourceType getSourceType() const { return sourceType_; }

  virtual std::unique_ptr<BBInstruction> clone() const override { return std::make_unique<BBPush<SrcT>>(source_, sourceType_); }

  virtual void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ') << "stack := ";

    switch (sourceType_) {
      case SourceType::VARIABLE:
        out << source_;
        break;
      case SourceType::ADDRESS:
        out << "[ " << source_ << " ]";
        break;
      case SourceType::NUMERIC:
        out << source_;
        break;
    }

    out << std::endl;
  }

 private:
  SrcT source_;
  SourceType sourceType_;
};

typedef BBPush<VariableType> BBPushV;
typedef BBPush<NumericType> BBPushN;
typedef BBPush<AddressType> BBPushA;

}  // namespace bblocks

#endif  // BBLOCKS_BB_PUSH_HPP
