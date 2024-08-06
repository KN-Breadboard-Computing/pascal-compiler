#include "case_node.hpp"

namespace ast {
virtual void CaseNode::accept(AstVisitor& visitor) const override {
  visitor.visit(*this);
}

[[nodiscard]] virtual std::unique_ptr<AstNode> CaseNode::clone() const override {
  ExpressionNode* newExpression = dynamic_cast<ExpressionNode*>(expression_->clone().release());
  std::vector<std::pair<AstNode*, StatementNode*>*>* newStatements = new std::vector<std::pair<AstNode*, StatementNode*>*>{};
  for (auto& statement : *statements_) {
    newStatements->push_back(new std::pair<AstNode*, StatementNode*>{
        statement->first->clone().release(), dynamic_cast<StatementNode*>(statement->second->clone().release())});
  }

  return std::make_unique<CaseNode>(newExpression, newStatements);
}

virtual void CaseNode::print(std::ostream& out, int tab) const override {
  if (getLabel().has_value()) {
    out << std::string(tab, ' ') << "CaseNode with label: " << getLabel().value() << std::endl;
  }
  else {
    out << std::string(tab, ' ') << "CaseNode:" << std::endl;
  }

  expression_->print(out, tab + 2);
  size_t index{0};
  for (auto& statement : *statements_) {
    out << std::string(tab + 2, ' ') << "Case " << index++ << ":\n";
    out << std::string(tab + 4, ' ') << "Expression:\n";
    if (statement->first != nullptr) {
      statement->first->print(out, tab + 6);
    }
    else {
      out << std::string(tab + 6, ' ') << "Otherwise\n";
    }
    out << std::string(tab + 4, ' ') << "Statement:\n";
    statement->second->print(out, tab + 6);
  }
}
}  // namespace ast