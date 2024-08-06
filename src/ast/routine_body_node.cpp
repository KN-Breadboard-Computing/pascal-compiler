#include "routine_body_node.hpp"

namespace ast {
virtual void RoutineBodyNode::accept(AstVisitor& visitor) const override {
  visitor.visit(*this);
}

[[nodiscard]] virtual std::unique_ptr<AstNode> RoutineBodyNode::clone() const override {
  auto clone = std::make_unique<RoutineBodyNode>();
  clone->setStatements(
      std::unique_ptr<CompoundStatementNode>(dynamic_cast<CompoundStatementNode*>(statements_->clone().release())));

  return clone;
}

virtual void RoutineBodyNode::print(std::ostream& out, int tab) const override {
  out << std::string(tab, ' ') << "RoutineBodyNode:\n";
  statements_->print(out, tab + 2);
}
}  // namespace ast
