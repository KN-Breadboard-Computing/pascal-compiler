#ifndef BBLOCKS_BB_PHI_HPP
#define BBLOCKS_BB_PHI_HPP

#include "bb_instruction.hpp"

namespace bblocks {
class BBPhi : public BBInstruction {
 public:
  BBPhi() : BBInstruction(Type::PHI) {}
  BBPhi(std::string name, std::vector<std::string> args)
      : BBInstruction(Type::PHI), name_{std::move(name)}, args_{std::move(args)} {}

  BBPhi(const BBPhi&) = default;
  BBPhi(BBPhi&&) noexcept = default;

  BBPhi& operator=(const BBPhi&) = default;
  BBPhi& operator=(BBPhi&&) noexcept = default;

  ~BBPhi() override = default;

  [[nodiscard]] const std::string& getName() const { return name_; }

  [[nodiscard]] const std::vector<std::string>& getArgs() const { return args_; }

  void setName(const std::string& name) { name_ = name; }

  void setArgs(const std::vector<std::string>& args) { args_ = args; }

  void addArg(const std::string& arg) { args_.push_back(arg); }

  virtual void visitDefVariables(std::function<void(const VariableType&)> visitor) const override { visitor(name_); }

  virtual void visitUseVariables(std::function<void(const VariableType&)> visitor) const override {
    for (const auto& arg : args_) {
      visitor(arg);
    }
  }

  virtual std::unique_ptr<BBInstruction> replaceVariable(const VariableType& from, const VariableType& to) override {
    const std::string newName = name_ == from ? to : name_;
    std::vector<std::string> newArgs;
    for (const auto& arg : args_) {
      newArgs.push_back(arg == from ? to : arg);
    }

    return std::make_unique<BBPhi>(newName, newArgs);
  }

  virtual std::unique_ptr<BBInstruction> replaceVariable(const VariableType& /*from*/, const NumericType& /*to*/) override {
    return clone();
  }

  virtual void replaceDefVariables(const VariableType& from, const VariableType& to) override {
    if (name_ == from) {
      name_ = to;
    }
  }

  virtual void replaceUseVariables(const VariableType& from, const VariableType& to) override {
    for (auto& arg : args_) {
      if (arg == from) {
        arg = to;
      }
    }
  }

  virtual void replaceLabel(const LabelType& /*from*/, const LabelType& /*to*/) override {}

  [[nodiscard]] virtual std::vector<TemplateArgumentType> getTemplateTypes() const override {
    return std::vector<TemplateArgumentType>{};
  }

  virtual std::unique_ptr<BBInstruction> clone() const override { return std::make_unique<BBPhi>(name_, args_); }

  virtual void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ') << name_ << " := phi( ";
    for (const auto& arg : args_) {
      out << arg << " ";
    }
    out << ")" << std::endl;
  }

 private:
  std::string name_;
  std::vector<std::string> args_;
};
}  // namespace bblocks

#endif  // BBLOCKS_BB_PHI_HPP
