#include "repeat_node.hpp"

namespace ast {
void RepeatNode::accept(AstVisitor* visitor) const {
  visitor->visit(this);
}

std::unique_ptr<AstNode> RepeatNode::clone() const {
  auto clone = std::make_unique<RepeatNode>();

  clone->setCondition(std::unique_ptr<ExpressionNode>(dynamic_cast<ExpressionNode*>(condition_->clone().release())));
  clone->setStatements(std::unique_ptr<StatementNode>(dynamic_cast<StatementNode*>(statements_->clone().release())));

  return clone;
}

void RepeatNode::print(std::ostream& out, int tab) const {
  if (getLabel().has_value()) {
    out << std::string(tab, ' ') << "RepeatNode with label: " << getLabel().value() << std::endl;
  }
  else {
    out << std::string(tab, ' ') << "RepeatNode:\n";
  }

  condition_->print(out, tab + 2);
  statements_->print(out, tab + 2);
}
}  // namespace ast