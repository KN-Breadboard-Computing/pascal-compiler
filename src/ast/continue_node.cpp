#include "continue_node.hpp"

namespace ast {
void ContinueNode::accept(AstVisitor* visitor) const {
  visitor->visit(this);
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
