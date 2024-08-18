#include "for_node.hpp"

namespace ast {
void ForNode::accept(const std::unique_ptr<AstVisitor>& visitor) const {
  visitor->visit(*this);
}

[[nodiscard]] std::unique_ptr<AstNode> ForNode::clone() const {
  auto clone = std::make_unique<ForNode>();
  clone->setIterator(std::unique_ptr<IdentifierNode>(dynamic_cast<IdentifierNode*>(iterator_->clone().release())));
  clone->setStart(std::unique_ptr<ExpressionNode>(dynamic_cast<ExpressionNode*>(start_->clone().release())));
  clone->setEnd(std::unique_ptr<ExpressionNode>(dynamic_cast<ExpressionNode*>(end_->clone().release())));
  clone->setStatements(std::unique_ptr<StatementNode>(dynamic_cast<StatementNode*>(statements_->clone().release())));
  clone->setDirection(direction_);
  return clone;
}

void ForNode::print(std::ostream& out, int tab) const {
  if (getLabel().has_value()) {
    out << std::string(tab, ' ') << "ForNode with label: " << getLabel().value() << std::endl;
  }
  else {
    out << std::string(tab, ' ') << "ForNode\n";
  }

  iterator_->print(out, tab + 2);
  start_->print(out, tab + 2);
  end_->print(out, tab + 2);
  statements_->print(out, tab + 2);
}
}  // namespace ast
