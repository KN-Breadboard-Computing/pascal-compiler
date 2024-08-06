#ifndef BBLOCKS_BB_POP_HPP
#define BBLOCKS_BB_POP_HPP

#include "BBInstruction.hpp"

namespace bblocks {
template <typename DestT>
concept PopArgs = (std::is_same_v<DestT, VariableType> || std::is_same_v<DestT, AddressType>);

template <typename DestT>
requires PopArgs<DestT> class BBPop : public BBInstruction {
 public:
  enum class DestinationType { VARIABLE, ADDRESS };

  BBPop() = default;
  BBPop(DestT destination, DestinationType destinationType) : destination_{destination}, destinationType_{destinationType} {}

  BBPop(const BBPop&) = default;
  BBPop(BBPop&&) = default;

  BBPop& operator=(const BBPop&) = default;
  BBPop& operator=(BBPop&&) = default;

  ~BBPop() override = default;

  [[nodiscard]] DestT getDestination() const { return destination_; }
  [[nodiscard]] DestinationType getDestinationType() const { return destinationType_; }

  friend virtual std::ostream& operator<<(std::ostream& out, const BBPop& instruction) override {
    out << "POP ";

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
  DestT destination_;
  DestinationType destinationType_;
};

typedef BBPop<VariableType> BBPopV;
typedef BBPop<AddressType> BBPopA;

}  // namespace bblocks

#endif  // BBLOCKS_BB_POP_HPP
