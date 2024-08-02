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

  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override {
    SimpleTypeNode* newRange = dynamic_cast<SimpleTypeNode*>(range_->clone().release());
    TypeNode* newElementType = dynamic_cast<TypeNode*>(elementType_->clone().release());

    return std::make_unique<ArrayTypeNode>(newRange, newElementType);
  }

  virtual void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ') << "ArrayTypeNode:\n";
    out << std::string(tab + 2, ' ') << "Range:\n";
    range_->print(out, tab + 4);
    out << std::string(tab + 2, ' ') << "Element type:\n";
    elementType_->print(out, tab + 4);
  }

 private:
  std::unique_ptr<SimpleTypeNode> range_;
  std::unique_ptr<TypeNode> elementType_;
};
}  // namespace ast

#endif  // AST_ARRAY_TYPE_NODE_HPP
