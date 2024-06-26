#ifndef AST_REPEAT_NODE_HPP
#define AST_REPEAT_NODE_HPP

#include "ast_node.hpp"

namespace ast {
class RepeatNode : public AstNode {
 public:
  RepeatNode() : AstNode(Type::REPEAT) {}

  RepeatNode(const RepeatNode &) = delete;
  RepeatNode(RepeatNode &&) = default;

  RepeatNode &operator=(const RepeatNode &) = delete;
  RepeatNode &operator=(RepeatNode &&) = default;

  ~RepeatNode() override = default;
};
} // namespace ast

#endif // AST_REPEAT_NODE_HPP
