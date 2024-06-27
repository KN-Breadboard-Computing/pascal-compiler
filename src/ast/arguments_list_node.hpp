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

  ArgumentsListNode(const ArgumentsListNode &) = delete;
  ArgumentsListNode(ArgumentsListNode &&) = default;

  ArgumentsListNode &operator=(const ArgumentsListNode &) = delete;
  ArgumentsListNode &operator=(ArgumentsListNode &&) = default;

  ~ArgumentsListNode() override = default;

  [[nodiscard]] const std::vector<ExpressionNode *> &getArguments() const { return arguments_; }

  void addArgument(ExpressionNode *argument) { arguments_.push_back(argument); }
  void setArguments(std::vector<ExpressionNode *> arguments) { arguments_ = std::move(arguments); }

 private:
  std::vector<ExpressionNode *> arguments_;
};
} // namespace ast

#endif // AST_ARGUMENTS_LIST_NODE_HPP
