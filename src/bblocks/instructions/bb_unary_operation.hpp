#ifndef BBLOCKS_BB_UNARY_OPERATION_HPP
#define BBLOCKS_BB_UNARY_OPERATION_HPP

#include "bb_instruction.hpp"

namespace bblocks {
template <typename ArgT, typename DestT>
concept UnaryOperationArgs = requires {
  {std::is_same_v<ArgT, VariableType> || std::is_same_v<ArgT, NumericType>};
  {std::is_same_v<DestT, VariableType> || std::is_same_v<DestT, NumericType>};
};

enum class BBUnaryOperationEnum { NEG, NOT, INC, DEC, SHL, SHR, SAR };

template <typename ArgT, typename DestT>
requires UnaryOperationArgs<ArgT, DestT> class BBUnaryOperation : public BBInstruction {
 public:
  BBUnaryOperation() : BBInstruction(Type::UNARY_OPERATION, true) {}
  BBUnaryOperation(ArgT source, DestT destination, SourceType sourceType, DestinationType destinationType,
                   BBUnaryOperationEnum operation)
      : BBInstruction(Type::UNARY_OPERATION, true),
        source_{source},
        destination_{destination},
        sourceType_{sourceType},
        destinationType_{destinationType},
        operation_{operation} {}

  BBUnaryOperation(const BBUnaryOperation&) = default;
  BBUnaryOperation(BBUnaryOperation&&) noexcept = default;

  BBUnaryOperation& operator=(const BBUnaryOperation&) = default;
  BBUnaryOperation& operator=(BBUnaryOperation&&) noexcept = default;

  ~BBUnaryOperation() override = default;

  [[nodiscard]] ArgT getSource() const { return source_; }
  [[nodiscard]] DestT getDestination() const { return destination_; }
  [[nodiscard]] DestinationType getDestinationType() const { return destinationType_; }
  [[nodiscard]] SourceType getSourceType() const { return sourceType_; }
  [[nodiscard]] BBUnaryOperationEnum getOperation() const { return operation_; }

  [[nodiscard]] TemplateArgumentType getSourceTemplateType() const {
    if constexpr (std::is_same_v<ArgT, VariableType>) {
      return TemplateArgumentType::STRING;
    }
    else {
      return TemplateArgumentType::NUMBER;
    }
  }

  [[nodiscard]] TemplateArgumentType getDestinationTemplateType() const {
    if constexpr (std::is_same_v<DestT, VariableType>) {
      return TemplateArgumentType::STRING;
    }
    else {
      return TemplateArgumentType::NUMBER;
    }
  }

  virtual void visitDefVariables(std::function<void(const VariableType&)> visitor) const override {
    if constexpr (std::is_same_v<DestT, VariableType>) {
      visitor(destination_);
    }
  }

  virtual void visitUseVariables(std::function<void(const VariableType&)> visitor) const override {
    if constexpr (std::is_same_v<ArgT, VariableType>) {
      visitor(source_);
    }
  }

  virtual std::unique_ptr<BBInstruction> replaceVariable(const VariableType& from, const VariableType& to) override {
    if constexpr (std::is_same_v<ArgT, VariableType> && std::is_same_v<DestT, VariableType>) {
      return std::make_unique<BBUnaryOperation<VariableType, VariableType>>(
          source_ == from ? to : source_, destination_ == from ? to : destination_, sourceType_, destinationType_, operation_);
    }
    else if constexpr (std::is_same_v<ArgT, VariableType>) {
      return std::make_unique<BBUnaryOperation<VariableType, DestT>>(source_ == from ? to : source_, destination_, sourceType_,
                                                                     destinationType_, operation_);
    }
    else if constexpr (std::is_same_v<DestT, VariableType>) {
      return std::make_unique<BBUnaryOperation<ArgT, VariableType>>(source_, destination_ == from ? to : destination_,
                                                                    sourceType_, destinationType_, operation_);
    }
    else {
      return clone();
    }
  }

  virtual std::unique_ptr<BBInstruction> replaceVariable(const VariableType& from, const NumericType& to) override {
    const SourceType newSourceType = sourceType_ == SourceType::REGISTER ? SourceType::CONSTANT : sourceType_;

    if constexpr (std::is_same_v<ArgT, VariableType> && std::is_same_v<DestT, VariableType>) {
      if (source_ == from && destination_ == from) {
        return std::make_unique<BBUnaryOperation<NumericType, NumericType>>(to, to, newSourceType, destinationType_, operation_);
      }
      if (source_ == from) {
        return std::make_unique<BBUnaryOperation<NumericType, VariableType>>(to, destination_, newSourceType, destinationType_,
                                                                             operation_);
      }
      if (destination_ == from) {
        return std::make_unique<BBUnaryOperation<ArgT, NumericType>>(source_, to, sourceType_, destinationType_, operation_);
      }

      return clone();
    }
    else if constexpr (std::is_same_v<ArgT, VariableType>) {
      if (source_ == from) {
        return std::make_unique<BBUnaryOperation<NumericType, DestT>>(to, destination_, newSourceType, destinationType_,
                                                                      operation_);
      }

      return clone();
    }
    else if constexpr (std::is_same_v<DestT, VariableType>) {
      if (destination_ == from) {
        return std::make_unique<BBUnaryOperation<ArgT, NumericType>>(source_, to, sourceType_, destinationType_, operation_);
      }

      return clone();
    }
    else {
      return clone();
    }
  }

  virtual void replaceDefVariables(const VariableType& from, const VariableType& to) override {
    if constexpr (std::is_same_v<DestT, VariableType>) {
      if (destination_ == from) {
        destination_ = to;
      }
    }
  }

  virtual void replaceUseVariables(const VariableType& from, const VariableType& to) override {
    if constexpr (std::is_same_v<ArgT, VariableType>) {
      if (source_ == from) {
        source_ = to;
      }
    }
  }

  virtual void replaceLabel(const LabelType& /*from*/, const LabelType& /*to*/) override {}

  [[nodiscard]] virtual std::vector<TemplateArgumentType> getTemplateTypes() const override {
    return std::vector<TemplateArgumentType>{getSourceTemplateType(), getDestinationTemplateType()};
  }

  virtual std::unique_ptr<BBInstruction> clone() const override {
    return std::make_unique<BBUnaryOperation<ArgT, DestT>>(source_, destination_, sourceType_, destinationType_, operation_);
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

    switch (operation_) {
      case BBUnaryOperationEnum::NEG:
        out << "- ";
        break;
      case BBUnaryOperationEnum::NOT:
        out << "~ ";
        break;
      case BBUnaryOperationEnum::INC:
        out << "inc ";
        break;
      case BBUnaryOperationEnum::DEC:
        out << "dec ";
        break;
      case BBUnaryOperationEnum::SHL:
        out << "shl ";
        break;
      case BBUnaryOperationEnum::SHR:
        out << "shr ";
        break;
      case BBUnaryOperationEnum::SAR:
        out << "sar ";
        break;
    }

    switch (sourceType_) {
      case SourceType::CONSTANT:
      case SourceType::REGISTER:
        out << source_;
        break;
      case SourceType::MEMORY:
        out << "[ " << source_ << " ]";
        break;
    }

    out << std::endl;
  }

 private:
  ArgT source_;
  DestT destination_;
  SourceType sourceType_;
  DestinationType destinationType_;
  BBUnaryOperationEnum operation_;
};

typedef BBUnaryOperation<VariableType, VariableType> BBUnaryOperationVV;
typedef BBUnaryOperation<VariableType, NumericType> BBUnaryOperationVN;
typedef BBUnaryOperation<NumericType, VariableType> BBUnaryOperationNV;
typedef BBUnaryOperation<NumericType, NumericType> BBUnaryOperationNN;

}  // namespace bblocks

#endif  // BBLOCKS_BB_UNARY_OPERATION_HPP