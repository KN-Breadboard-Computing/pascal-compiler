#ifndef AST_ARGUMENTS_LIST_NODE_HPP
#define AST_ARGUMENTS_LIST_NODE_HPP

#include <memory>
#include <vector>

#include "ast_node.hpp"
#include "expression_node.hpp"

namespace ast {
class ArgumentsListNode : public AstNode {
 public:
  ArgumentsListNode() : AstNode{Type::ARGUMENTS_LIST} {}

  ArgumentsListNode(const ArgumentsListNode&) = delete;
  ArgumentsListNode(ArgumentsListNode&&) = default;

  ArgumentsListNode& operator=(const ArgumentsListNode&) = delete;
  ArgumentsListNode& operator=(ArgumentsListNode&&) = default;

  ~ArgumentsListNode() override = default;

  [[nodiscard]] const std::vector<ExpressionNode*>& getArguments() const { return arguments_; }

  void addArgument(ExpressionNode* argument) { arguments_.push_back(argument); }
  void setArguments(std::vector<ExpressionNode*> arguments) { arguments_ = std::move(arguments); }

  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override {
    std::vector<ExpressionNode*> arguments;
    for (const auto& argument : arguments_) {
      arguments.push_back(dynamic_cast<ExpressionNode*>(argument->clone().release()));
    }

    auto clone = std::make_unique<ArgumentsListNode>();
    clone->setArguments(std::move(arguments));

    return clone;
  }

  virtual void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ') << "ArgumentsListNode:\n";
    for (const auto& argument : arguments_) {
      argument->print(out, tab + 2);
    }
  }

 private:
  std::vector<ExpressionNode*> arguments_;
};
}  // namespace ast

#endif  // AST_ARGUMENTS_LIST_NODE_HPP
