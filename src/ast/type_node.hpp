#ifndef AST_TYPE_NODE_HPP
#define AST_TYPE_NODE_HPP

#include "ast_node.hpp"

namespace ast {
class TypeNode : public AstNode {
 public:
  enum TypeType { UNSPECIFIED, SIMPLE, ARRAY, RECORD };

  TypeNode() : AstNode{Type::TYPE}, typeType_{UNSPECIFIED} {}
  explicit TypeNode(TypeType typeType) : AstNode{Type::TYPE}, typeType_{typeType} {}

  TypeNode(const TypeNode&) = delete;
  TypeNode(TypeNode&&) = default;

  TypeNode& operator=(const TypeNode&) = delete;
  TypeNode& operator=(TypeNode&&) = default;

  ~TypeNode() override = default;

  [[nodiscard]] TypeType getTypeType() const { return typeType_; }

  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override { return std::make_unique<TypeNode>(typeType_); }

  virtual void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ') << "TypeNode ";
    switch (typeType_) {
      case SIMPLE:
        out << "SIMPLE";
        break;
      case ARRAY:
        out << "ARRAY";
        break;
      case RECORD:
        out << "RECORD";
        break;
      default:
        out << "UNSPECIFIED";
        break;
    }
    out << '\n';
  }

 private:
  TypeType typeType_;
};
}  // namespace ast

#endif  // AST_TYPE_NODE_HPP
