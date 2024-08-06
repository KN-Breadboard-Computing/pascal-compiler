#ifndef BBLOCKS_BB_MOVE_HPP
#define BBLOCKS_BB_MOVE_HPP

#include "BBInstruction.hpp"

namespace bblocks {
template <typename SrcT, typename DestT>
concept MoveArgs =
    (((std::is_same_v<DestT, VariableType> || std::is_same_v<DestT, AddressType>)) &&
     ((std::is_same_v<SrcT, VariableType> || std::is_same_v<SrcT, NumericType> || std::is_same_v<SrcT, AddressType>)));

template <typename SrcT, typename DestT>
requires MoveArgs<SrcT, DestT> class BBMove : public BBInstruction {
 public:
  enum class SourceType { VARIABLE, NUMERIC, ADDRESS };
  enum class DestinationType { VARIABLE, ADDRESS };

  BBMove() = default;
  BBMove(Arg1T source, Arg2T destination, SourceType sourceType, DestinationType destinationType)
      : source_{source}, destination_{destination}, sourceType_{sourceType}, destinationType_{destinationType} {}

  BBMove(const BBMove&) = default;
  BBMove(BBMove&&) = default;

  BBMove& operator=(const BBMove&) = default;
  BBMove& operator=(BBMove&&) = default;

  ~BBMove() override = default;

  [[nodiscard]] Arg1T getSource() const { return source_; }
  [[nodiscard]] Arg2T getDestination() const { return destination_; }
  [[nodiscard]] SourceType getSourceType() const { return sourceType_; }
  [[nodiscard]] DestinationType getDestinationType() const { return destinationType_; }

  friend virtual std::ostream& operator<<(std::ostream& out, const BBMove& instruction) override {
    out << "MOVE ";
    switch (sourceType_) {
      case SourceType::VARIABLE:
        out << source_;
        break;
      case SourceType::NUMERIC:
        out << source_;
        break;
      case SourceType::ADDRESS:
        out << source_ << " ]";
        break;
    }

    switch (destinationType_) {
      case DestinationType::VARIABLE:
        out << " TO " << destination_;
        break;
      case DestinationType::ADDRESS:
        out << " TO [ " << destination_ << " ]";
        break;
    }

    out << std::endl;

    return out;
  }

 private:
  SrcT source_;
  DestT destination_;
  SourceType sourceType_;
  DestinationType destinationType_;
};

typedef BBMove<VariableType, VariableType> BBMoveVV;
typedef BBMove<VariableType, AddressType> BBMoveVA;
typedef BBMove<VariableType, NumericType> BBMoveVN;
typedef BBMove<AddressType, VariableType> BBMoveAV;
typedef BBMove<AddressType, AddressType> BBMoveAA;
typedef BBMove<AddressType, NumericType> BBMoveAN;

}  // namespace bblocks

#endif  // BBLOCKS_BB_MOVE_HPP
