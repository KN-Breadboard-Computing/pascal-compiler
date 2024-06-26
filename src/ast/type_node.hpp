#ifndef AST_TYPE_NODE_HPP
#define AST_TYPE_NODE_HPP

#include "ast_node.hpp"

namespace ast {
class TypeNode : public AstNode {
 public:
  enum TypeType { UNSPECIFIED, SIMPLE, ARRAY, RECORD };

  TypeNode() : AstNode{Type::TYPE}, typeType_{UNSPECIFIED} {}
  explicit TypeNode(TypeType typeType) : AstNode{Type::TYPE}, typeType_{typeType} {}

  TypeNode(const TypeNode &) = delete;
  TypeNode(TypeNode &&) = default;

  TypeNode &operator=(const TypeNode &) = delete;
  TypeNode &operator=(TypeNode &&) = default;

  ~TypeNode() override = default;

  [[nodiscard]] TypeType getTypeType() const { return typeType_; }

 private:
  TypeType typeType_;
};
} // namespace ast

#endif // AST_TYPE_NODE_HPP
