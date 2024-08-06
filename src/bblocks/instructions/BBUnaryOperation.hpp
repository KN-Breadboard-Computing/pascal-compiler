#ifndef BBLOCKS_BB_UNARY_OPERATION_HPP
#define BBLOCKS_BB_UNARY_OPERATION_HPP

#include "BBInstruction.hpp"

namespace bblocks {
template <typename ArgT, typename DestT>
concept UnaryOperationArgs = (((std::is_same_v<DestT, VariableType> || std::is_same_v<DestT, AddressType>)) &&
                              ((std::is_same_v<ArgT, VariableType> || std::is_same_v<ArgT, NumericType>)));

template <typename ArgT, typename DestT>
requires UnaryOperationArgs<ArgT, DestT> class BBUnaryOperation : public BBInstruction {
 public:
  enum class OperationType { NEG, NOT, INC, DEC };
  enum class DestinationType { VARIABLE, ADDRESS };

  BBUnaryOperation() = default;
  BBUnaryOperation(ArgT source, DestT destination, OperationType operationType, DestinationType destinationType)
      : source_{source}, destination_{destination}, operationType_{operationType}, destinationType_{destinationType} {}

  BBUnaryOperation(const BBUnaryOperation&) = default;
  BBUnaryOperation(BBUnaryOperation&&) = default;

  BBUnaryOperation& operator=(const BBUnaryOperation&) = default;
  BBUnaryOperation& operator=(BBUnaryOperation&&) = default;

  ~BBUnaryOperation() override = default;

  [[nodiscard]] ArgT getSource() const { return source_; }
  [[nodiscard]] DestT getDestination() const { return destination_; }
  [[nodiscard]] OperationType getOperation() const { return operationType_; }
  [[nodiscard]] DestinationType getDestinationType() const { return destinationType_; }

  friend virtual std::ostream& operator<<(std::ostream& out, const BBUnaryOperation& instruction) override {
    out << "MOV ";

    switch (operationType_) {
      case OperationType::NEG:
        out << "NEG ";
        break;
      case OperationType::NOT:
        out << "NOT ";
        break;
      case OperationType::INC:
        out << "INC ";
        break;
      case OperationType::DEC:
        out << "DEC ";
        break;
    }

    out << source_;

    switch (destinationType_) {
      case DestinationType::VARIABLE:
        out << " TO " << destination_;
        break;
      case DestinationType::ADDRESS:
        out << " TO [ " << destination_ << " ]";
        break;
    }

    return out;
  }

 private:
  ArgT source_;
  DestT destination_;
  OperationType operationType_;
  DestinationType destinationType_;
};

typedef BBUnaryOperation<VariableType, VariableType> BBUnaryOperationVV;
typedef BBUnaryOperation<VariableType, AddressType> BBUnaryOperationVA;
typedef BBUnaryOperation<NumericType, VariableType> BBUnaryOperationNV;
typedef BBUnaryOperation<NumericType, AddressType> BBUnaryOperationNA;

}  // namespace bblocks

#endif  // BBLOCKS_BB_UNARY_OPERATION_HPP