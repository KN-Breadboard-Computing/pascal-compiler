#ifndef AST_IF_NODE_HPP
#define AST_IF_NODE_HPP

#include "ast_node.hpp"

namespace ast {
class IfNode : public AstNode {
 public:
  IfNode() : AstNode{Type::IF} {}

  IfNode(const IfNode &) = delete;
  IfNode(IfNode &&) = default;

  IfNode &operator=(const IfNode &) = delete;
  IfNode &operator=(IfNode &&) = default;

  ~IfNode() override = default;
};
} // namespace ast

#endif // AST_IF_NODE_HPP
