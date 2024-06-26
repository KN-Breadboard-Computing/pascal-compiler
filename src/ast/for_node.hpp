#ifndef AST_FOR_NODE_HPP
#define AST_FOR_NODE_HPP

#include "ast_node.hpp"

namespace ast {
class ForNode : public AstNode {
 public:
  ForNode() : AstNode(Type::FOR) {}

  ForNode(const ForNode &) = delete;
  ForNode(ForNode &&) = default;

  ForNode &operator=(const ForNode &) = delete;
  ForNode &operator=(ForNode &&) = default;

  ~ForNode() override = default;
};
} // namespace ast

#endif // AST_FOR_NODE_HPP
