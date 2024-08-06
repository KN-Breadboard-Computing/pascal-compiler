#include "while_node.hpp"

namespace ast {
virtual void WhileNode::accept(AstVisitor& visitor) const override {
  visitor.visit(*this);
}

[[nodiscard]] virtual std::unique_ptr<AstNode> WhileNode::clone() const override {
  auto clone = std::make_unique<WhileNode>();
  clone->setCondition(std::unique_ptr<ExpressionNode>(dynamic_cast<ExpressionNode*>(condition_->clone().release())));
  clone->setStatements(std::unique_ptr<StatementNode>(dynamic_cast<StatementNode*>(statements_->clone().release())));

  return clone;
}

virtual void WhileNode::print(std::ostream& out, int tab) const override {
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
