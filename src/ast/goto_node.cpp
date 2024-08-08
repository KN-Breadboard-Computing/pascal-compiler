#include "goto_node.hpp"

namespace ast {
void GotoNode::accept(const std::unique_ptr<AstVisitor>& visitor) const {
  visitor->visit(*this);
}

[[nodiscard]] std::unique_ptr<AstNode> GotoNode::clone() const {
  return std::make_unique<GotoNode>(line_);
}

void GotoNode::print(std::ostream& out, int tab) const {
  if (getLabel().has_value()) {
    out << std::string(tab, ' ') << "GotoNode with label: " << getLabel().value() << '\n';
  }
  else {
    out << std::string(tab, ' ') << "GotoNode\n";
  }

  out << std::string(tab, ' ') << "  Line: " << line_ << '\n';
}
}  // namespace ast
