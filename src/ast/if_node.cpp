#include "if_node.hpp"

namespace ast {
virtual void IfNode::accept(AstVisitor& visitor) const override {
  visitor.visit(*this);
}

[[nodiscard]] virtual std::unique_ptr<AstNode> IfNode::clone() const override {
  auto clone = std::make_unique<IfNode>();
  clone->setCondition(std::unique_ptr<ExpressionNode>(dynamic_cast<ExpressionNode*>(condition_->clone().release())));
  clone->setThenStatement(std::unique_ptr<StatementNode>(dynamic_cast<StatementNode*>(thenStatement_->clone().release())));
  if (elseStatement_) {
    clone->setElseStatement(std::unique_ptr<StatementNode>(dynamic_cast<StatementNode*>(elseStatement_->clone().release())));
  }

  return clone;
}

virtual void IfNode::print(std::ostream& out, int tab) const override {
  if (getLabel().has_value()) {
    out << std::string(tab, ' ') << "IfNode with label: " << getLabel().value() << std::endl;
  }
  else {
    out << std::string(tab, ' ') << "IfNode:\n";
  }

  out << std::string(tab + 2, ' ') << "Condition:\n";
  condition_->print(out, tab + 4);
  out << std::string(tab + 2, ' ') << "ThenStatement:\n";
  thenStatement_->print(out, tab + 4);
  if (elseStatement_) {
    out << std::string(tab + 2, ' ') << "ElseStatement:\n";
    elseStatement_->print(out, tab + 4);
  }
}
}  // namespace ast
