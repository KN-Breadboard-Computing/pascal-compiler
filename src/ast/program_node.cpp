#include "program_node.hpp"

namespace ast {
virtual void ProgramNode::accept(AstVisitor& visitor) const override {
  visitor.visit(*this);
}

[[nodiscard]] virtual std::unique_ptr<AstNode> ProgramNode::clone() const override {
  auto clone = std::make_unique<ProgramNode>();
  clone->setName(name_);
  clone->setRoutine(std::unique_ptr<RoutineNode>(dynamic_cast<RoutineNode*>(routine_->clone().release())));
  return clone;
}

virtual void ProgramNode::print(std::ostream& out, int tab) const override {
  out << std::string(tab, ' ') << "ProgramNode " << name_ << ":\n";
  routine_->print(out, tab + 2);
}
}  // namespace ast
