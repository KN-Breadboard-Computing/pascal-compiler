#include "arguments_list_node.hpp"

namespace ast {
virtual void ArgumentsListNode::accept(AstVisitor& visitor) const override {
  visitor.visit(*this);
}

[[nodiscard]] virtual std::unique_ptr<AstNode> ArgumentsListNode::clone() const override {
  std::vector<ExpressionNode*> arguments;
  for (const auto& argument : arguments_) {
    arguments.push_back(dynamic_cast<ExpressionNode*>(argument->clone().release()));
  }

  auto clone = std::make_unique<ArgumentsListNode>();
  clone->setArguments(std::move(arguments));

  return clone;
}

virtual void ArgumentsListNode::print(std::ostream& out, int tab) const override {
  out << std::string(tab, ' ') << "ArgumentsListNode:\n";
  for (const auto& argument : arguments_) {
    argument->print(out, tab + 2);
  }
}
}  // namespace ast
