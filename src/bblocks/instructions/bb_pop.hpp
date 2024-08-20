#ifndef BBLOCKS_BB_POP_HPP
#define BBLOCKS_BB_POP_HPP

#include "bb_instruction.hpp"

namespace bblocks {
template <typename DestT>
concept PopArgs = requires {
  {std::is_same_v<DestT, VariableType> || std::is_same_v<DestT, AddressType>};
};

template <typename DestT>
requires PopArgs<DestT> class BBPop : public BBInstruction {
 public:
  enum class DestinationType { VARIABLE, ADDRESS };

  BBPop() = default;
  BBPop(DestT destination, DestinationType destinationType) : destination_{destination}, destinationType_{destinationType} {}

  BBPop(const BBPop&) = default;
  BBPop(BBPop&&) noexcept = default;

  BBPop& operator=(const BBPop&) = default;
  BBPop& operator=(BBPop&&) noexcept = default;

  ~BBPop() override = default;

  [[nodiscard]] DestT getDestination() const { return destination_; }
  [[nodiscard]] DestinationType getDestinationType() const { return destinationType_; }

  virtual std::unique_ptr<BBInstruction> clone() const override {
    return std::make_unique<BBPop<DestT>>(destination_, destinationType_);
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

    out << " := stack";
  }

 private:
  DestT destination_;
  DestinationType destinationType_;
};

typedef BBPop<VariableType> BBPopV;
typedef BBPop<AddressType> BBPopA;

}  // namespace bblocks

#endif  // BBLOCKS_BB_POP_HPP
