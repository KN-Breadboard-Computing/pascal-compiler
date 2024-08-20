#ifndef BBLOCKS_BB_BINARY_OPERATION_HPP
#define BBLOCKS_BB_BINARY_OPERATION_HPP

#include "bb_instruction.hpp"

namespace bblocks {
template <typename Arg1T, typename Arg2T, typename DestT>
concept BinaryOperationArgs = requires {
  {std::is_same_v<Arg1T, VariableType> || std::is_same_v<Arg1T, NumericType>};
  {std::is_same_v<Arg2T, VariableType> || std::is_same_v<Arg2T, NumericType>};
  {std::is_same_v<DestT, VariableType> || std::is_same_v<DestT, AddressType>};
};

template <typename Arg1T, typename Arg2T, typename DestT>
requires BinaryOperationArgs<Arg1T, Arg2T, DestT> class BBBinaryOperation : public BBInstruction {
 public:
  enum class OperationType { ADD, SUB, MUL, DIV, MOD, AND, OR, XOR, EQ, NE, LT, LE, GT, GE };
  enum class DestinationType { VARIABLE, ADDRESS };

  BBBinaryOperation() = default;
  BBBinaryOperation(Arg1T source1, Arg2T source2, DestT destination, OperationType operationType, DestinationType destinationType)
      : source1_{source1},
        source2_{source2},
        destination_{destination},
        operationType_{operationType},
        destinationType_{destinationType} {}

  BBBinaryOperation(const BBBinaryOperation&) = default;
  BBBinaryOperation(BBBinaryOperation&&) noexcept = default;

  BBBinaryOperation& operator=(const BBBinaryOperation&) = default;
  BBBinaryOperation& operator=(BBBinaryOperation&&) noexcept = default;

  ~BBBinaryOperation() override = default;

  [[nodiscard]] Arg1T getSource1() const { return source1_; }
  [[nodiscard]] Arg2T getSource2() const { return source2_; }
  [[nodiscard]] DestT getDestination() const { return destination_; }
  [[nodiscard]] OperationType getOperation() const { return operationType_; }
  [[nodiscard]] DestinationType getDestinationType() const { return destinationType_; }

  virtual std::unique_ptr<BBInstruction> clone() const override {
    return std::make_unique<BBBinaryOperation<Arg1T, Arg2T, DestT>>(source1_, source2_, destination_, operationType_,
                                                                    destinationType_);
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

    out << " := " << source1_ << " ";

    switch (operationType_) {
      case OperationType::ADD:
        out << "+";
        break;
      case OperationType::SUB:
        out << "-";
        break;
      case OperationType::MUL:
        out << "*";
        break;
      case OperationType::DIV:
        out << "/";
        break;
      case OperationType::MOD:
        out << "%";
        break;
      case OperationType::AND:
        out << "&";
        break;
      case OperationType::OR:
        out << "|";
        break;
      case OperationType::XOR:
        out << "^";
        break;
      case OperationType::EQ:
        out << "==";
        break;
      case OperationType::NE:
        out << "!=";
        break;
      case OperationType::LT:
        out << "<";
        break;
      case OperationType::LE:
        out << "<=";
        break;
      case OperationType::GT:
        out << ">";
        break;
      case OperationType::GE:
        out << ">=";
        break;
    }

    out << " " << source2_ << std::endl;
  }

 private:
  Arg1T source1_;
  Arg2T source2_;
  DestT destination_;
  OperationType operationType_;
  DestinationType destinationType_;
};

typedef BBBinaryOperation<VariableType, VariableType, VariableType> BBBinaryOperationVVV;
typedef BBBinaryOperation<VariableType, VariableType, AddressType> BBBinaryOperationVVA;
typedef BBBinaryOperation<VariableType, NumericType, VariableType> BBBinaryOperationVNV;
typedef BBBinaryOperation<VariableType, NumericType, AddressType> BBBinaryOperationVNA;
typedef BBBinaryOperation<NumericType, VariableType, VariableType> BBBinaryOperationNVV;
typedef BBBinaryOperation<NumericType, VariableType, AddressType> BBBinaryOperationNVA;
typedef BBBinaryOperation<NumericType, NumericType, VariableType> BBBinaryOperationNNV;
typedef BBBinaryOperation<NumericType, NumericType, AddressType> BBBinaryOperationNNA;

}  // namespace bblocks

#endif  // BBLOCKS_BB_BINARY_OPERATION_HPP