#ifndef BBLOCKS_BB_BRANCH_HPP
#define BBLOCKS_BB_BRANCH_HPP

#include <utility>

#include "bb_instruction.hpp"

namespace bblocks {
template <typename ArgT>
concept BranchArgs = requires {
  {std::is_same_v<ArgT, VariableType> || std::is_same_v<ArgT, NumericType>};
};

enum class BBBranchCondition { ANY, NEGATIVE, POSITIVE, ODD, EVEN, ZERO, NONZERO, CARRY, NOCARRY, OVERFLOW, NOOVERFLOW };

template <typename ArgT>
requires BranchArgs<ArgT> class BBBranch : public BBInstruction {
 public:
  BBBranch() : BBInstruction(Type::BRANCH) {}
  BBBranch(ArgT value, SourceType valueType, BBBranchCondition condition, LabelType trueLabel, LabelType falseLabel)
      : BBInstruction(Type::BRANCH),
        value_{value},
        valueType_{valueType},
        condition_{condition},
        trueLabel_{std::move(trueLabel)},
        falseLabel_{std::move(falseLabel)} {}

  BBBranch(const BBBranch&) = default;
  BBBranch(BBBranch&&) noexcept = default;

  BBBranch& operator=(const BBBranch&) = default;
  BBBranch& operator=(BBBranch&&) noexcept = default;

  ~BBBranch() = default;

  [[nodiscard]] ArgT getValue() const { return value_; }
  [[nodiscard]] SourceType getValueType() const { return valueType_; }
  [[nodiscard]] BBBranchCondition getCondition() const { return condition_; }
  [[nodiscard]] LabelType getTrueLabel() const { return trueLabel_; }
  [[nodiscard]] LabelType getFalseLabel() const { return falseLabel_; }

  [[nodiscard]] TemplateArgumentType getValueTemplateType() const {
    if constexpr (std::is_same_v<ArgT, VariableType>) {
      return TemplateArgumentType::STRING;
    }
    else {
      return TemplateArgumentType::NUMBER;
    }
  }

  virtual void visitDefVariables(std::function<void(const VariableType&)> /*visitor*/) const override {}

  virtual void visitUseVariables(std::function<void(const VariableType&)> visitor) const override {
    if constexpr (std::is_same_v<ArgT, VariableType>) {
      visitor(value_);
    }
  }

  virtual std::unique_ptr<BBInstruction> replaceVariable(const VariableType& from, const VariableType& to) override {
    if constexpr (std::is_same_v<ArgT, VariableType>) {
      return std::make_unique<BBBranch<VariableType>>(value_ == from ? to : value_, valueType_, condition_, trueLabel_,
                                                      falseLabel_);
    }
    else {
      return clone();
    }
  }

  virtual std::unique_ptr<BBInstruction> replaceVariable(const VariableType& from, const NumericType& to) override {
    if constexpr (std::is_same_v<ArgT, VariableType>) {
      if (value_ == from) {
        return std::make_unique<BBBranch<NumericType>>(to, BBInstruction::SourceType::CONSTANT, condition_, trueLabel_,
                                                       falseLabel_);
      }
      return clone();
    }
    else {
      return clone();
    }
  }

  virtual void replaceDefVariables(const VariableType& /*from*/, const VariableType& /*to*/) override {}

  virtual void replaceUseVariables(const VariableType& from, const VariableType& to) override {
    if constexpr (std::is_same_v<ArgT, VariableType>) {
      if (value_ == from) {
        value_ = to;
      }
    }
  }

  virtual void replaceLabel(const LabelType& from, const LabelType& to) override {
    if (trueLabel_ == from) {
      trueLabel_ = to;
    }
    if (falseLabel_ == from) {
      falseLabel_ = to;
    }
  }

  [[nodiscard]] virtual std::vector<TemplateArgumentType> getTemplateTypes() const override {
    return std::vector<TemplateArgumentType>{getValueTemplateType()};
  }

  virtual std::unique_ptr<BBInstruction> clone() const override {
    return std::make_unique<BBBranch>(value_, valueType_, condition_, trueLabel_, falseLabel_);
  }

  virtual void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ') << "br ";

    switch (condition_) {
      case BBBranchCondition::ANY:
        out << "any ";
        break;
      case BBBranchCondition::NEGATIVE:
        out << "negative ";
        break;
      case BBBranchCondition::POSITIVE:
        out << "positive ";
        break;
      case BBBranchCondition::ODD:
        out << "odd ";
        break;
      case BBBranchCondition::EVEN:
        out << "even ";
        break;
      case BBBranchCondition::ZERO:
        out << "zero ";
        break;
      case BBBranchCondition::NONZERO:
        out << "nonzero ";
        break;
      case BBBranchCondition::CARRY:
        out << "carry ";
        break;
      case BBBranchCondition::NOCARRY:
        out << "nocarry ";
        break;
      case BBBranchCondition::OVERFLOW:
        out << "overflow ";
        break;
      case BBBranchCondition::NOOVERFLOW:
        out << "nooverflow ";
        break;
    }

    switch (valueType_) {
      case SourceType::CONSTANT:
      case SourceType::REGISTER:
        out << value_;
        break;
      case SourceType::MEMORY:
        out << "[" << value_ << "]";
        break;
    }

    out << " ? " << trueLabel_ << " : " << falseLabel_ << std::endl;
  }

 private:
  ArgT value_;
  SourceType valueType_;
  BBBranchCondition condition_;
  LabelType trueLabel_;
  LabelType falseLabel_;
};

typedef BBBranch<VariableType> BBBranchV;
typedef BBBranch<NumericType> BBBranchN;
}  // namespace bblocks

#endif  // BBLOCKS_BB_BRANCH_HPP