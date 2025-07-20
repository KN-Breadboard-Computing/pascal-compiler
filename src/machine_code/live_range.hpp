#ifndef LIVE_RANGE_HPP
#define LIVE_RANGE_HPP

#include <string>

namespace machine_code {
class LiveRange {
 public:
  struct Action {
    enum class Type { DEF, USE, HOLD };

    Type type;
    std::size_t instructionEnumerator;
    std::string blockLabel;

    bool operator<(const Action& other) const {
      if (instructionEnumerator != other.instructionEnumerator) {
        return instructionEnumerator < other.instructionEnumerator;
      }

      if (blockLabel != other.blockLabel) {
        return blockLabel < other.blockLabel;
      }

      return type < other.type;
    }
  };

  LiveRange() : allocatedRegister_{-1} {}
  LiveRange(std::string variable) : allocatedRegister_{-1}, variable_(std::move(variable)) {}
  LiveRange(std::string variable, std::vector<Action> actions) : allocatedRegister_{-1}, variable_(std::move(variable)), actions_(std::move(actions)) {}
  LiveRange(const LiveRange&) = default;
  LiveRange(LiveRange&&) = default;

  LiveRange& operator=(const LiveRange&) = default;
  LiveRange& operator=(LiveRange&&) = default;

  ~LiveRange() = default;

  bool empty() const { return actions_.empty(); }

  const Action& front() const { return actions_.front(); }
  const Action& back() const { return actions_.back(); }

  void clear() { actions_.clear(); }
  void pushBack(const Action& action) { actions_.push_back(action); }

  void setAllocatedRegister(int allocatedRegister) { allocatedRegister_ = allocatedRegister; }

  [[nodiscard]] int getAllocatedRegister() const { return allocatedRegister_; }
  [[nodiscard]] const std::string& getVariable() const { return variable_; }
  [[nodiscard]] const std::vector<Action>& getActions() const { return actions_; }

  friend std::ostream& operator<<(std::ostream& out, const LiveRange& liveRange) {
    out << "[ ";
    for (const auto& action : liveRange.actions_) {
      out << action.instructionEnumerator;
      switch (action.type) {
        case Action::Type::DEF:
          out << "(D) ";
          break;
        case Action::Type::USE:
          out << "(U) ";
          break;
        case Action::Type::HOLD:
          out << "(H) ";
          break;
      }
    }
    out << "]";
    return out;
  }

 private:
  int allocatedRegister_;
  std::string variable_;
  std::vector<Action> actions_;
};
}  // namespace machine_code

#endif  // LIVE_RANGE_HPP