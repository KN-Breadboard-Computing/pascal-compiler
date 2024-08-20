#ifndef BBLOCKS_BB_UNARY_OPERATION_HPP
#define BBLOCKS_BB_UNARY_OPERATION_HPP

#include "bb_instruction.hpp"

namespace bblocks {
template <typename ArgT, typename DestT>
concept UnaryOperationArgs = requires {
  {std::is_same_v<ArgT, VariableType> || std::is_same_v<ArgT, NumericType>};
  {std::is_same_v<DestT, VariableType> || std::is_same_v<DestT, AddressType>};
};

template <typename ArgT, typename DestT>
requires UnaryOperationArgs<ArgT, DestT> class BBUnaryOperation : public BBInstruction {
 public:
  enum class OperationType { NEG, NOT, INC, DEC, SHL, SHR, SAR };
  enum class DestinationType { VARIABLE, ADDRESS };

  BBUnaryOperation() = default;
  BBUnaryOperation(ArgT source, DestT destination, OperationType operationType, DestinationType destinationType)
      : source_{source}, destination_{destination}, operationType_{operationType}, destinationType_{destinationType} {}

  BBUnaryOperation(const BBUnaryOperation&) = default;
  BBUnaryOperation(BBUnaryOperation&&) noexcept = default;

  BBUnaryOperation& operator=(const BBUnaryOperation&) = default;
  BBUnaryOperation& operator=(BBUnaryOperation&&) noexcept = default;

  ~BBUnaryOperation() override = default;

  [[nodiscard]] ArgT getSource() const { return source_; }
  [[nodiscard]] DestT getDestination() const { return destination_; }
  [[nodiscard]] OperationType getOperation() const { return operationType_; }
  [[nodiscard]] DestinationType getDestinationType() const { return destinationType_; }

  virtual std::unique_ptr<BBInstruction> clone() const override {
    return std::make_unique<BBUnaryOperation<ArgT, DestT>>(source_, destination_, operationType_, destinationType_);
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

    switch (operationType_) {
      case OperationType::NEG:
        out << "- ";
        break;
      case OperationType::NOT:
        out << "~ ";
        break;
      case OperationType::INC:
        out << "inc ";
        break;
      case OperationType::DEC:
        out << "dec ";
        break;
      case OperationType::SHL:
        out << "shl ";
        break;
      case OperationType::SHR:
        out << "shr ";
        break;
      case OperationType::SAR:
        out << "sar ";
        break;
    }

    out << source_ << std::endl;
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