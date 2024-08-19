#include "break_node.hpp"

namespace ast {
void BreakNode::accept(AstVisitor* visitor) const {
  visitor->visit(this);
}

[[nodiscard]] std::unique_ptr<AstNode> BreakNode::clone() const {
  auto clone = std::make_unique<BreakNode>();
  return clone;
}

void BreakNode::print(std::ostream &out, int tab) const {
  if (getLabel().has_value()) {
	out << std::string(tab, ' ') << "BreakNode with label: " << getLabel().value() << std::endl;
  } else {
	out << std::string(tab, ' ') << "BreakNode\n";
  }
}

}  // namespace ast
