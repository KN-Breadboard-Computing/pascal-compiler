#ifndef AST_ARRAY_TYPE_NODE_HPP
#define AST_ARRAY_TYPE_NODE_HPP

#include <memory>

#include "simple_type_node.hpp"
#include "type_node.hpp"

namespace ast {
class ArrayTypeNode : public TypeNode {
 public:
  ArrayTypeNode() : TypeNode{TypeType::ARRAY} {}
  ArrayTypeNode(SimpleTypeNode* range, TypeNode* elementType)
      : TypeNode{TypeType::ARRAY}, range_{range}, elementType_{elementType} {}

  ArrayTypeNode(const ArrayTypeNode&) = delete;
  ArrayTypeNode(ArrayTypeNode&&) = default;

  ArrayTypeNode& operator=(const ArrayTypeNode&) = delete;
  ArrayTypeNode& operator=(ArrayTypeNode&&) = default;

  ~ArrayTypeNode() override = default;

  [[nodiscard]] const std::unique_ptr<SimpleTypeNode>& getRange() const { return range_; }
  [[nodiscard]] const std::unique_ptr<TypeNode>& getElementType() const { return elementType_; }

  [[nodiscard]] virtual std::string flat() const override;

  virtual void accept(AstVisitor* visitor) const override;
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  virtual void print(std::ostream& out, int tab) const override;

 private:
  std::unique_ptr<SimpleTypeNode> range_;
  std::unique_ptr<TypeNode> elementType_;
};
}  // namespace ast

#endif  // AST_ARRAY_TYPE_NODE_HPP
