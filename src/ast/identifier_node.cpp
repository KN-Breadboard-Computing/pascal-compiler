#include "identifier_node.hpp"

namespace ast {
void IdentifierNode::accept(AstVisitor* visitor) const {
  visitor->visit(this);
}

[[nodiscard]] std::unique_ptr<AstNode> IdentifierNode::clone() const {
  return std::make_unique<IdentifierNode>(name_);
}

void IdentifierNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "IdentifierNode: " << name_ << '\n';
}
}  // namespace ast
