#include "identifier_node.hpp"

namespace ast {
virtual void IdentifierNode::accept(AstVisitor& visitor) const override {
  visitor.visit(*this);
}

[[nodiscard]] virtual std::unique_ptr<AstNode> IdentifierNode::clone() const override {
  return std::make_unique<IdentifierNode>(name_);
}

virtual void IdentifierNode::print(std::ostream& out, int tab) const override {
  out << std::string(tab, ' ') << "IdentifierNode: " << name_ << '\n';
}
}  // namespace ast
