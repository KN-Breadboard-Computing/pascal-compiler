#ifndef BBLOCKS_BB_MOVE_HPP
#define BBLOCKS_BB_MOVE_HPP

#include "bb_instruction.hpp"

namespace bblocks {
template <typename SrcT, typename DestT>
concept MoveArgs = requires {
  {std::is_same_v<SrcT, VariableType> || std::is_same_v<SrcT, NumericType> || std::is_same_v<SrcT, AddressType>};
  {std::is_same_v<DestT, VariableType> || std::is_same_v<DestT, AddressType>};
};

template <typename SrcT, typename DestT>
requires MoveArgs<SrcT, DestT> class BBMove : public BBInstruction {
 public:
  enum class SourceType { VARIABLE, NUMERIC, ADDRESS };
  enum class DestinationType { VARIABLE, ADDRESS };

  BBMove() = default;
  BBMove(SrcT source, DestT destination, SourceType sourceType, DestinationType destinationType)
      : source_{source}, destination_{destination}, sourceType_{sourceType}, destinationType_{destinationType} {}

  BBMove(const BBMove&) = default;
  BBMove(BBMove&&) noexcept = default;

  BBMove& operator=(const BBMove&) = default;
  BBMove& operator=(BBMove&&) noexcept = default;

  ~BBMove() override = default;

  [[nodiscard]] SrcT getSource() const { return source_; }
  [[nodiscard]] DestT getDestination() const { return destination_; }
  [[nodiscard]] SourceType getSourceType() const { return sourceType_; }
  [[nodiscard]] DestinationType getDestinationType() const { return destinationType_; }

  virtual std::unique_ptr<BBInstruction> clone() const override {
    return std::make_unique<BBMove<SrcT, DestT>>(source_, destination_, sourceType_, destinationType_);
  }

  virtual void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ');

    switch (destinationType_) {
      case DestinationType::VARIABLE:
        out << destination_;
        break;
      case DestinationType::ADDRESS:
        out << "[ " << destination_ << " ]";
        break;
    }

    out << " := ";

    switch (sourceType_) {
      case SourceType::VARIABLE:
        out << source_;
        break;
      case SourceType::NUMERIC:
        out << source_;
        break;
      case SourceType::ADDRESS:
        out << "[ " << source_ << " ]";
        break;
    }

    out << std::endl;
  }

 private:
  SrcT source_;
  DestT destination_;
  SourceType sourceType_;
  DestinationType destinationType_;
};

typedef BBMove<VariableType, VariableType> BBMoveVV;
typedef BBMove<VariableType, AddressType> BBMoveVA;
typedef BBMove<NumericType, VariableType> BBMoveNV;
typedef BBMove<AddressType, VariableType> BBMoveAV;
typedef BBMove<AddressType, AddressType> BBMoveAA;
typedef BBMove<NumericType, AddressType> BBMoveNA;

}  // namespace bblocks

#endif  // BBLOCKS_BB_MOVE_HPP
