#include "routine_body_node.hpp"

namespace ast {
void RoutineBodyNode::accept(const std::unique_ptr<AstVisitor>& visitor) const {
  visitor->visit(*this);
}

[[nodiscard]] std::unique_ptr<AstNode> RoutineBodyNode::clone() const {
  auto clone = std::make_unique<RoutineBodyNode>();
  clone->setStatements(
      std::unique_ptr<CompoundStatementNode>(dynamic_cast<CompoundStatementNode*>(statements_->clone().release())));

  return clone;
}

void RoutineBodyNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "RoutineBodyNode:\n";
  statements_->print(out, tab + 2);
}
}  // namespace ast
