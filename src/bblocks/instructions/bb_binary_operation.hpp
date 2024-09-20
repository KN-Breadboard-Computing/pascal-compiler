#ifndef BBLOCKS_BB_BINARY_OPERATION_HPP
#define BBLOCKS_BB_BINARY_OPERATION_HPP

#include "bb_instruction.hpp"

namespace bblocks {
template <typename Arg1T, typename Arg2T, typename DestT>
concept BinaryOperationArgs = requires {
  {std::is_same_v<Arg1T, VariableType> || std::is_same_v<Arg1T, NumericType>};
  {std::is_same_v<Arg2T, VariableType> || std::is_same_v<Arg2T, NumericType>};
  {std::is_same_v<DestT, VariableType> || std::is_same_v<DestT, NumericType>};
};

enum BBBinaryOperationEnum { ADD, SUB, MUL, DIV, MOD, AND, OR, XOR, EQ, NE, LT, LE, GT, GE };

template <typename Arg1T, typename Arg2T, typename DestT>
requires BinaryOperationArgs<Arg1T, Arg2T, DestT> class BBBinaryOperation : public BBInstruction {
 public:
  BBBinaryOperation() : BBInstruction(Type::BINARY_OPERATION) {}
  BBBinaryOperation(Arg1T source1, Arg2T source2, DestT destination, SourceType source1Type, SourceType source2Type,
                    DestinationType destination_type, BBBinaryOperationEnum Operation)
      : BBInstruction(Type::BINARY_OPERATION),
        source1_{source1},
        source2_{source2},
        destination_{destination},
        source1Type_{source1Type},
        source2Type_{source2Type},
        destinationType_{destination_type},
        operation_{Operation} {}

  BBBinaryOperation(const BBBinaryOperation&) = default;
  BBBinaryOperation(BBBinaryOperation&&) noexcept = default;

  BBBinaryOperation& operator=(const BBBinaryOperation&) = default;
  BBBinaryOperation& operator=(BBBinaryOperation&&) noexcept = default;

  ~BBBinaryOperation() override = default;

  [[nodiscard]] Arg1T getSource1() const { return source1_; }
  [[nodiscard]] Arg2T getSource2() const { return source2_; }
  [[nodiscard]] DestT getDestination() const { return destination_; }
  [[nodiscard]] SourceType getSource1Type() const { return source1Type_; }
  [[nodiscard]] SourceType getSource2Type() const { return source2Type_; }
  [[nodiscard]] DestinationType getDestinationType() const { return destinationType_; }
  [[nodiscard]] BBBinaryOperationEnum getOperation() const { return operation_; }

  virtual void visitDefVariables(std::function<void(const VariableType&)> visitor) const override {
    if constexpr (std::is_same_v<DestT, VariableType>) {
      visitor(destination_);
    }
  }

  virtual void visitUseVariables(std::function<void(const VariableType&)> visitor) const override {
    if constexpr (std::is_same_v<Arg1T, VariableType>) {
      visitor(source1_);
    }
    if constexpr (std::is_same_v<Arg2T, VariableType>) {
      visitor(source2_);
    }
  }

  virtual std::unique_ptr<BBInstruction> replaceVariable(const VariableType& from, const VariableType& to) override {
    if constexpr (std::is_same_v<Arg1T, VariableType> && std::is_same_v<Arg2T, VariableType> &&
                  std::is_same_v<DestT, VariableType>) {
      return std::make_unique<BBBinaryOperation<VariableType, VariableType, VariableType>>(
          source1_ == from ? to : source1_, source2_ == from ? to : source2_, destination_ == from ? to : destination_,
          source1Type_, source2Type_, destinationType_, operation_);
    }
    else if constexpr (std::is_same_v<Arg1T, VariableType> && std::is_same_v<Arg2T, VariableType>) {
      return std::make_unique<BBBinaryOperation<VariableType, VariableType, DestT>>(
          source1_ == from ? to : source1_, source2_ == from ? to : source2_, destination_, source1Type_, source2Type_,
          destinationType_, operation_);
    }
    else if constexpr (std::is_same_v<Arg1T, VariableType> && std::is_same_v<DestT, VariableType>) {
      return std::make_unique<BBBinaryOperation<VariableType, Arg2T, VariableType>>(
          source1_ == from ? to : source1_, source2_, destination_ == from ? to : destination_, source1Type_, source2Type_,
          destinationType_, operation_);
    }
    else if constexpr (std::is_same_v<Arg2T, VariableType> && std::is_same_v<DestT, VariableType>) {
      return std::make_unique<BBBinaryOperation<Arg1T, VariableType, VariableType>>(
          source1_, source2_ == from ? to : source2_, destination_ == from ? to : destination_, source1Type_, source2Type_,
          destinationType_, operation_);
    }
    else if constexpr (std::is_same_v<Arg1T, VariableType>) {
      return std::make_unique<BBBinaryOperation<VariableType, Arg2T, DestT>>(
          source1_ == from ? to : source1_, source2_, destination_, source1Type_, source2Type_, destinationType_, operation_);
    }
    else if constexpr (std::is_same_v<Arg2T, VariableType>) {
      return std::make_unique<BBBinaryOperation<Arg1T, VariableType, DestT>>(
          source1_, source2_ == from ? to : source2_, destination_, source1Type_, source2Type_, destinationType_, operation_);
    }
    else if constexpr (std::is_same_v<DestT, VariableType>) {
      return std::make_unique<BBBinaryOperation<Arg1T, Arg2T, VariableType>>(
          source1_, source2_, destination_ == from ? to : destination_, source1Type_, source2Type_, destinationType_, operation_);
    }
    else {
      return clone();
    }
  }

  virtual std::unique_ptr<BBInstruction> replaceVariable(const VariableType& from, const NumericType& to) override {
    if constexpr (std::is_same_v<Arg1T, VariableType> && std::is_same_v<Arg2T, VariableType> &&
                  std::is_same_v<DestT, VariableType>) {
      if (source1_ == from && source2_ == from && destination_ == from) {
        return std::make_unique<BBBinaryOperation<NumericType, NumericType, NumericType>>(to, to, to, source1Type_, source2Type_,
                                                                                          destinationType_, operation_);
      }
      else if (source1_ == from && source2_ == from) {
        return std::make_unique<BBBinaryOperation<NumericType, NumericType, VariableType>>(
            to, to, destination_, source1Type_, source2Type_, destinationType_, operation_);
      }
      else if (source1_ == from && destination_ == from) {
        return std::make_unique<BBBinaryOperation<NumericType, Arg2T, NumericType>>(to, source2_, to, source1Type_, source2Type_,
                                                                                    destinationType_, operation_);
      }
      else if (source2_ == from && destination_ == from) {
        return std::make_unique<BBBinaryOperation<Arg1T, NumericType, NumericType>>(source1_, to, to, source1Type_, source2Type_,
                                                                                    destinationType_, operation_);
      }
      else if (source1_ == from) {
        return std::make_unique<BBBinaryOperation<NumericType, Arg2T, DestT>>(to, source2_, destination_, source1Type_,
                                                                              source2Type_, destinationType_, operation_);
      }
      else if (source2_ == from) {
        return std::make_unique<BBBinaryOperation<Arg1T, NumericType, DestT>>(source1_, to, destination_, source1Type_,
                                                                              source2Type_, destinationType_, operation_);
      }
      else if (destination_ == from) {
        return std::make_unique<BBBinaryOperation<Arg1T, Arg2T, NumericType>>(source1_, source2_, to, source1Type_, source2Type_,
                                                                              destinationType_, operation_);
      }
      return clone();
    }
    else if constexpr (std::is_same_v<Arg1T, VariableType> && std::is_same_v<Arg2T, VariableType>) {
      if (source1_ == from && source2_ == from) {
        return std::make_unique<BBBinaryOperation<NumericType, NumericType, DestT>>(
            to, to, destination_, source1Type_, source2Type_, destinationType_, operation_);
      }
      else if (source1_ == from) {
        return std::make_unique<BBBinaryOperation<NumericType, Arg2T, DestT>>(to, source2_, destination_, source1Type_,
                                                                                    source2Type_, destinationType_, operation_);
      }
      else if (source2_ == from) {
        return std::make_unique<BBBinaryOperation<Arg1T, NumericType, NumericType>>(source1_, to, destination_, source1Type_,
                                                                                    source2Type_, destinationType_, operation_);
      }
      return clone();
    }
    else if constexpr (std::is_same_v<Arg1T, VariableType> && std::is_same_v<DestT, VariableType>) {
      if (source1_ == from && destination_ == from) {
        return std::make_unique<BBBinaryOperation<NumericType, Arg2T, NumericType>>(to, source2_, to, source1Type_, source2Type_,
                                                                                    destinationType_, operation_);
      }
      else if (source1_ == from) {
        return std::make_unique<BBBinaryOperation<NumericType, Arg2T, DestT>>(to, source2_, destination_, source1Type_,
                                                                              source2Type_, destinationType_, operation_);
      }
      else if (destination_ == from) {
        return std::make_unique<BBBinaryOperation<Arg1T, Arg2T, NumericType>>(source1_, source2_, to, source1Type_, source2Type_,
                                                                              destinationType_, operation_);
      }
      return clone();
    }
    else if constexpr (std::is_same_v<Arg2T, VariableType> && std::is_same_v<DestT, VariableType>) {
      if (source2_ == from && destination_ == from) {
        return std::make_unique<BBBinaryOperation<Arg1T, NumericType, NumericType>>(source1_, to, to, source1Type_, source2Type_,
                                                                                    destinationType_, operation_);
      }
      else if (source2_ == from) {
        return std::make_unique<BBBinaryOperation<Arg1T, NumericType, DestT>>(source1_, to, destination_, source1Type_,
                                                                              source2Type_, destinationType_, operation_);
      }
      else if (destination_ == from) {
        return std::make_unique<BBBinaryOperation<Arg1T, Arg2T, NumericType>>(source1_, source2_, to, source1Type_, source2Type_,
                                                                              destinationType_, operation_);
      }
      return clone();
    }
    else if constexpr (std::is_same_v<Arg1T, VariableType>) {
      if (source1_ == from) {
        return std::make_unique<BBBinaryOperation<NumericType, Arg2T, DestT>>(to, source2_, destination_, source1Type_,
                                                                              source2Type_, destinationType_, operation_);
      }
      return clone();
    }
    else if constexpr (std::is_same_v<Arg2T, VariableType>) {
      if (source2_ == from) {
        return std::make_unique<BBBinaryOperation<Arg1T, NumericType, DestT>>(source1_, to, destination_, source1Type_,
                                                                              source2Type_, destinationType_, operation_);
      }
      return clone();
    }
    else if constexpr (std::is_same_v<DestT, VariableType>) {
      if (destination_ == from) {
        return std::make_unique<BBBinaryOperation<Arg1T, Arg2T, NumericType>>(source1_, source2_, to, source1Type_, source2Type_,
                                                                              destinationType_, operation_);
      }
      return clone();
    }
    else {
      return clone();
    }
  }

  virtual std::unique_ptr<BBInstruction> clone() const override {
    return std::make_unique<BBBinaryOperation<Arg1T, Arg2T, DestT>>(source1_, source2_, destination_, source1Type_, source2Type_,
                                                                    destinationType_, operation_);
  }

  virtual void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ');

    switch (destinationType_) {
      case DestinationType::REGISTER:
        out << destination_;
        break;
      case DestinationType::MEMORY:
        out << "[ " << destination_ << " ]";
        break;
    }

    out << " := ";

    switch (source1Type_) {
      case SourceType::CONSTANT:
      case SourceType::REGISTER:
        out << source1_;
        break;
      case SourceType::MEMORY:
        out << "[ " << source1_ << " ]";
        break;
    }

    out << " ";

    switch (operation_) {
      case BBBinaryOperationEnum::ADD:
        out << "+";
        break;
      case BBBinaryOperationEnum::SUB:
        out << "-";
        break;
      case BBBinaryOperationEnum::MUL:
        out << "*";
        break;
      case BBBinaryOperationEnum::DIV:
        out << "/";
        break;
      case BBBinaryOperationEnum::MOD:
        out << "%";
        break;
      case BBBinaryOperationEnum::AND:
        out << "&";
        break;
      case BBBinaryOperationEnum::OR:
        out << "|";
        break;
      case BBBinaryOperationEnum::XOR:
        out << "^";
        break;
      case BBBinaryOperationEnum::EQ:
        out << "==";
        break;
      case BBBinaryOperationEnum::NE:
        out << "!=";
        break;
      case BBBinaryOperationEnum::LT:
        out << "<";
        break;
      case BBBinaryOperationEnum::LE:
        out << "<=";
        break;
      case BBBinaryOperationEnum::GT:
        out << ">";
        break;
      case BBBinaryOperationEnum::GE:
        out << ">=";
        break;
    }

    out << " ";

    switch (source2Type_) {
      case SourceType::CONSTANT:
      case SourceType::REGISTER:
        out << source2_;
        break;
      case SourceType::MEMORY:
        out << "[ " << source2_ << " ]";
        break;
    }

    out << std::endl;
  }

 private:
  Arg1T source1_;
  Arg2T source2_;
  DestT destination_;
  SourceType source1Type_;
  SourceType source2Type_;
  DestinationType destinationType_;
  BBBinaryOperationEnum operation_;
};

typedef BBBinaryOperation<VariableType, VariableType, VariableType> BBBinaryOperationVVV;
typedef BBBinaryOperation<VariableType, VariableType, NumericType> BBBinaryOperationVVN;
typedef BBBinaryOperation<VariableType, NumericType, VariableType> BBBinaryOperationVNV;
typedef BBBinaryOperation<VariableType, NumericType, NumericType> BBBinaryOperationVNN;
typedef BBBinaryOperation<NumericType, VariableType, VariableType> BBBinaryOperationNVV;
typedef BBBinaryOperation<NumericType, VariableType, NumericType> BBBinaryOperationNVN;
typedef BBBinaryOperation<NumericType, NumericType, VariableType> BBBinaryOperationNNV;
typedef BBBinaryOperation<NumericType, NumericType, NumericType> BBBinaryOperationNNN;

}  // namespace bblocks

#endif  // BBLOCKS_BB_BINARY_OPERATION_HPP