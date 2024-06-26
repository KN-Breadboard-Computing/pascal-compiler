#ifndef AST_WHILE_NODE_HPP
#define AST_WHILE_NODE_HPP

#include "ast_node.hpp"

namespace ast {
class WhileNode : public AstNode {
 public:
  WhileNode() : AstNode(Type::WHILE) {}

  WhileNode(const WhileNode &) = delete;
  WhileNode(WhileNode &&) = default;

  WhileNode &operator=(const WhileNode &) = delete;
  WhileNode &operator=(WhileNode &&) = default;

  ~WhileNode() override = default;
};
} // namespace ast

#endif // AST_WHILE_NODE_HPP
