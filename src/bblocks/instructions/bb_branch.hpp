#ifndef BBLOCKS_BB_BRANCH_HPP
#define BBLOCKS_BB_BRANCH_HPP

#include <utility>

#include "bb_instruction.hpp"

namespace bblocks {
template <typename ArgT>
concept BranchArgs = requires {
  {std::is_same_v<ArgT, VariableType> || std::is_same_v<ArgT, NumericType>};
};

template <typename ArgT>
requires BranchArgs<ArgT> class BBBranch : public BBInstruction {
 public:
  enum class Condition { ANY, NEGATIVE, POSITIVE, ODD, EVEN, ZERO, NONZERO, CARRY, NOCARRY, OVERFLOW, NOOVERFLOW };

  BBBranch() = default;
  BBBranch(ArgT value, Condition condition, LabelType trueLabel, LabelType falseLabel)
      : value_{value}, condition_{condition}, trueLabel_{std::move(trueLabel)}, falseLabel_{std::move(falseLabel)} {}

  BBBranch(const BBBranch&) = default;
  BBBranch(BBBranch&&) noexcept = default;

  BBBranch& operator=(const BBBranch&) = default;
  BBBranch& operator=(BBBranch&&) noexcept = default;

  ~BBBranch() = default;

  [[nodiscard]] ArgT getValue() const { return value_; }
  [[nodiscard]] Condition getCondition() const { return condition_; }
  [[nodiscard]] LabelType getTrueLabel() const { return trueLabel_; }
  [[nodiscard]] LabelType getFalseLabel() const { return falseLabel_; }

  virtual std::unique_ptr<BBInstruction> clone() const override {
    return std::make_unique<BBBranch>(value_, condition_, trueLabel_, falseLabel_);
  }

  virtual void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ') << "br ";

    switch (condition_) {
      case Condition::ANY:
        out << "any ";
        break;
      case Condition::NEGATIVE:
        out << "negative ";
        break;
      case Condition::POSITIVE:
        out << "positive ";
        break;
      case Condition::ODD:
        out << "odd ";
        break;
      case Condition::EVEN:
        out << "even ";
        break;
      case Condition::ZERO:
        out << "zero ";
        break;
      case Condition::NONZERO:
        out << "nonzero ";
        break;
      case Condition::CARRY:
        out << "carry ";
        break;
      case Condition::NOCARRY:
        out << "nocarry ";
        break;
      case Condition::OVERFLOW:
        out << "overflow ";
        break;
      case Condition::NOOVERFLOW:
        out << "nooverflow ";
        break;
    }

    out << value_ << " ? " << trueLabel_ << " : " << falseLabel_ << std::endl;
  }

 private:
  ArgT value_;
  Condition condition_;
  LabelType trueLabel_;
  LabelType falseLabel_;
};

typedef BBBranch<VariableType> BBBranchV;
typedef BBBranch<BooleanType> BBBranchB;
}  // namespace bblocks

#endif  // BBLOCKS_BB_BRANCH_HPP