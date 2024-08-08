#include "for_node.hpp"

namespace ast {
// ForNode
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

// BreakNode
void BreakNode::accept(const std::unique_ptr<AstVisitor>& visitor) const {
  visitor->visit(*this);
}

[[nodiscard]] std::unique_ptr<AstNode> BreakNode::clone() const {
  auto clone = std::make_unique<BreakNode>();
  return clone;
}

void BreakNode::print(std::ostream& out, int tab) const {
  if (getLabel().has_value()) {
    out << std::string(tab, ' ') << "BreakNode with label: " << getLabel().value() << std::endl;
  }
  else {
    out << std::string(tab, ' ') << "BreakNode\n";
  }
}

// ContinueNode
void ContinueNode::accept(const std::unique_ptr<AstVisitor>& visitor) const {
  visitor->visit(*this);
}

[[nodiscard]] std::unique_ptr<AstNode> ContinueNode::clone() const {
  auto clone = std::make_unique<ContinueNode>();
  return clone;
}

void ContinueNode::print(std::ostream& out, int tab) const {
  if (getLabel().has_value()) {
    out << std::string(tab, ' ') << "ContinueNode with label: " << getLabel().value() << std::endl;
  }
  else {
    out << std::string(tab, ' ') << "ContinueNode\n";
  }
}
}  // namespace ast
