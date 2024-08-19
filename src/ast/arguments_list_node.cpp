#include "arguments_list_node.hpp"

namespace ast {
void ArgumentsListNode::accept(AstVisitor* visitor) const {
  visitor->visit(this);
}

[[nodiscard]] std::unique_ptr<AstNode> ArgumentsListNode::clone() const {
  std::vector<ExpressionNode*> arguments;
  for (const auto& argument : arguments_) {
    arguments.push_back(dynamic_cast<ExpressionNode*>(argument->clone().release()));
  }

  auto clone = std::make_unique<ArgumentsListNode>();
  clone->setArguments(std::move(arguments));

  return clone;
}

void ArgumentsListNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "ArgumentsListNode:\n";
  for (const auto& argument : arguments_) {
    argument->print(out, tab + 2);
  }
}
}  // namespace ast
