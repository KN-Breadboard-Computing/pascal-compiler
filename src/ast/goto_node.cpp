#include "goto_node.hpp"

namespace ast {
virtual void GotoNode::accept(AstVisitor& visitor) const override {
  visitor.visit(*this);
}

[[nodiscard]] std::unique_ptr<AstNode> GotoNode::clone() const override {
  return std::make_unique<GotoNode>(line_);
}

void GotoNode::print(std::ostream& out, int tab) const override {
  if (getLabel().has_value()) {
    out << std::string(tab, ' ') << "GotoNode with label: " << getLabel().value() << '\n';
  }
  else {
    out << std::string(tab, ' ') << "GotoNode\n";
  }

  out << std::string(tab, ' ') << "  Line: " << line_ << '\n';
}
}  // namespace ast
