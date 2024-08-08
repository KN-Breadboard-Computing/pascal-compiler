#include "repeat_node.hpp"

namespace ast {
void RepeatNode::accept(const std::unique_ptr<AstVisitor>& visitor) const { visitor->visit(*this); }

std::unique_ptr<AstNode> RepeatNode::clone() const {
  auto clone = std::make_unique<RepeatNode>();

  clone->setCondition(std::unique_ptr<ExpressionNode>(dynamic_cast<ExpressionNode*>(condition_->clone().release())));
  std::vector<StatementNode*> statements;
  for (const auto& statement : *statements_) {
    statements.push_back(dynamic_cast<StatementNode*>(statement->clone().release()));
  }
  clone->setStatements(std::make_unique<std::vector<StatementNode*>>(std::move(statements)));

  return clone;
}

void RepeatNode::print(std::ostream& out, int tab) const {
  if(getLabel().has_value()) {
    out << std::string(tab, ' ') << "RepeatNode with label: " << getLabel().value() << std::endl;
  } else {
    out << std::string(tab, ' ') << "RepeatNode:\n";
  }

  condition_->print(out, tab + 2);
  for (const auto& statement : *statements_) {
    statement->print(out, tab + 2);
  }
}
} // namespace ast