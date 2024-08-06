#include "statement_node.hpp"

namespace ast {
virtual void StatementNode::accept(AstVisitor& visitor) const override {
  visitor.visit(*this);
}

[[nodiscard]] virtual std::unique_ptr<AstNode> StatementNode::clone() const override {
  auto clone = std::make_unique<StatementNode>();
  if (label_.has_value()) {
    clone->setLabel(label_.value());
  }
  return clone;
}

virtual void StatementNode::print(std::ostream& out, int tab) const override {
  if (label_.has_value()) {
    out << std::string(tab, ' ') << "StatementNode with label: " << label_.value() << '\n';
  }
  else {
    out << std::string(tab, ' ') << "StatementNode\n";
  }
}
}  // namespace ast
