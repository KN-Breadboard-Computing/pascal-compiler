#ifndef BBLOCKS_BB_MOVE_HPP
#define BBLOCKS_BB_MOVE_HPP

#include "bb_instruction.hpp"

namespace bblocks {
template <typename SrcT, typename DestT>
concept MoveArgs = requires {
  {std::is_same_v<SrcT, VariableType> || std::is_same_v<SrcT, NumericType>};
  {std::is_same_v<DestT, VariableType> || std::is_same_v<DestT, NumericType>};
};

template <typename SrcT, typename DestT>
requires MoveArgs<SrcT, DestT> class BBMove : public BBInstruction {
 public:
  BBMove() : BBInstruction(Type::MOVE) {}
  BBMove(SrcT source, DestT destination, SourceType sourceType, DestinationType destinationType)
      : BBInstruction(Type::MOVE),
        source_{source},
        destination_{destination},
        sourceType_{sourceType},
        destinationType_{destinationType} {}

  BBMove(const BBMove&) = default;
  BBMove(BBMove&&) noexcept = default;

  BBMove& operator=(const BBMove&) = default;
  BBMove& operator=(BBMove&&) noexcept = default;

  ~BBMove() override = default;

  [[nodiscard]] SrcT getSource() const { return source_; }
  [[nodiscard]] DestT getDestination() const { return destination_; }
  [[nodiscard]] SourceType getSourceType() const { return sourceType_; }
  [[nodiscard]] DestinationType getDestinationType() const { return destinationType_; }

  [[nodiscard]] TemplateArgumentType getSourceTemplateType() const {
    if constexpr (std::is_same_v<SrcT, VariableType>) {
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
    if constexpr (std::is_same_v<SrcT, VariableType>) {
      visitor(source_);
    }
  }

  virtual std::unique_ptr<BBInstruction> replaceVariable(const VariableType& from, const VariableType& to) override {
    if constexpr (std::is_same_v<SrcT, VariableType> && std::is_same_v<DestT, VariableType>) {
      return std::make_unique<BBMove<VariableType, VariableType>>(
          source_ == from ? to : source_, destination_ == from ? to : destination_, sourceType_, destinationType_);
    }
    else if constexpr (std::is_same_v<SrcT, VariableType>) {
      return std::make_unique<BBMove<VariableType, DestT>>(source_ == from ? to : source_, destination_, sourceType_,
                                                           destinationType_);
    }
    else if constexpr (std::is_same_v<DestT, VariableType>) {
      return std::make_unique<BBMove<SrcT, VariableType>>(source_, destination_ == from ? to : destination_, sourceType_,
                                                          destinationType_);
    }
    else {
      return clone();
    }
  }

  virtual std::unique_ptr<BBInstruction> replaceVariable(const VariableType& from, const NumericType& to) override {
    const SourceType newSourceType = sourceType_ == SourceType::REGISTER ? SourceType::CONSTANT : sourceType_;

    if constexpr (std::is_same_v<SrcT, VariableType> && std::is_same_v<DestT, VariableType>) {
      if (source_ == from && destination_ == from) {
        return std::make_unique<BBMove<NumericType, NumericType>>(to, to, newSourceType, destinationType_);
      }
      else if (source_ == from) {
        return std::make_unique<BBMove<NumericType, VariableType>>(to, destination_, newSourceType, destinationType_);
      }
      else if (destination_ == from) {
        return std::make_unique<BBMove<SrcT, NumericType>>(source_, to, sourceType_, destinationType_);
      }

      return clone();
    }
    else if constexpr (std::is_same_v<SrcT, VariableType>) {
      if (source_ == from) {
        return std::make_unique<BBMove<NumericType, DestT>>(to, destination_, newSourceType, destinationType_);
      }

      return clone();
    }
    else if constexpr (std::is_same_v<DestT, VariableType>) {
      if (destination_ == from) {
        return std::make_unique<BBMove<SrcT, NumericType>>(source_, to, sourceType_, destinationType_);
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
    if constexpr (std::is_same_v<SrcT, VariableType>) {
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
    return std::make_unique<BBMove<SrcT, DestT>>(source_, destination_, sourceType_, destinationType_);
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
  SrcT source_;
  DestT destination_;
  SourceType sourceType_;
  DestinationType destinationType_;
};

typedef BBMove<VariableType, VariableType> BBMoveVV;
typedef BBMove<VariableType, NumericType> BBMoveVN;
typedef BBMove<NumericType, VariableType> BBMoveNV;
typedef BBMove<NumericType, NumericType> BBMoveNN;

}  // namespace bblocks

#endif  // BBLOCKS_BB_MOVE_HPP
