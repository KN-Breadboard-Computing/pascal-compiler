#include "compound_statement_node.hpp"

namespace ast {
void CompoundStatementNode::accept(AstVisitor* visitor) const {
  visitor->visit(this);
}

[[nodiscard]] std::unique_ptr<AstNode> CompoundStatementNode::clone() const {
  std::unique_ptr<std::vector<StatementNode*>> statements{};
  for (const auto& statement : *statements_) {
    statements->push_back(dynamic_cast<StatementNode*>(statement->clone().release()));
  }
  auto clone = std::make_unique<CompoundStatementNode>();
  clone->setStatements(std::move(statements));
  return clone;
}

void CompoundStatementNode::print(std::ostream& out, int tab) const {
  if (getLabel().has_value()) {
    out << std::string(tab, ' ') << "CompoundStatementNode with label: " << getLabel().value() << "\n";
  }
  else {
    out << std::string(tab, ' ') << "CompoundStatementNode:\n";
  }

  for (const auto& statement : *statements_) {
    statement->print(out, tab + 2);
  }
}
}  // namespace ast
