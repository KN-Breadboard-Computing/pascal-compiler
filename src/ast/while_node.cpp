#include "while_node.hpp"

namespace ast {
void WhileNode::accept(const std::unique_ptr<AstVisitor>& visitor) const {
  visitor->visit(*this);
}

[[nodiscard]] std::unique_ptr<AstNode> WhileNode::clone() const {
  auto clone = std::make_unique<WhileNode>();
  clone->setCondition(std::unique_ptr<ExpressionNode>(dynamic_cast<ExpressionNode*>(condition_->clone().release())));
  clone->setStatements(std::unique_ptr<StatementNode>(dynamic_cast<StatementNode*>(statements_->clone().release())));

  return clone;
}

void WhileNode::print(std::ostream& out, int tab) const {
  if (getLabel().has_value()) {
    out << std::string(tab, ' ') << "WhileNode with label: " << getLabel().value() << std::endl;
  }
  else {
    out << std::string(tab, ' ') << "WhileNode:\n";
  }

  condition_->print(out, tab + 2);
  statements_->print(out, tab + 2);
}
}  // namespace ast
