#ifndef AST_CONSTANT_NODE_HPP
#define AST_CONSTANT_NODE_HPP

#include "ast_node.hpp"

namespace ast {
class ConstantNode : public AstNode {
 public:
  enum ConstantType { UNSPECIFIED, INTEGER, CHAR, BOOLEAN, STRING };

  ConstantNode() : AstNode{Type::CONSTANT}, constantType_{UNSPECIFIED} {}
  explicit ConstantNode(ConstantType constantType) : AstNode{Type::CONSTANT}, constantType_{constantType} {}

  ConstantNode(const ConstantNode&) = delete;
  ConstantNode(ConstantNode&&) = default;

  ConstantNode& operator=(const ConstantNode&) = delete;
  ConstantNode& operator=(ConstantNode&&) = default;

  ~ConstantNode() override = default;

  [[nodiscard]] ConstantType getConstantType() const { return constantType_; }

  [[nodiscard]] std::string flat() const;
  [[nodiscard]] std::string flatType() const;

  virtual void accept(AstVisitor* visitor) const override;
  [[nodiscard]] std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;

 private:
  ConstantType constantType_;
};

template <typename T, ConstantNode::ConstantType type>
class ConstantNodeSpec : public ConstantNode {
 public:
  ConstantNodeSpec() : ConstantNode{type}, value_{} {}
  explicit ConstantNodeSpec(T value) : ConstantNode{type}, value_{value} {}

  ConstantNodeSpec(const ConstantNodeSpec&) = delete;
  ConstantNodeSpec(ConstantNodeSpec&&) noexcept = default;

  ConstantNodeSpec& operator=(const ConstantNodeSpec&) = delete;
  ConstantNodeSpec& operator=(ConstantNodeSpec&&) noexcept = default;

  ~ConstantNodeSpec() override = default;

  [[nodiscard]] T getValue() const { return value_; }

  //  virtual void accept(AstVisitor* visitor) const override { visitor->visit(this); }
  //
  //  [[nodiscard]] std::unique_ptr<AstNode> clone() const override { return std::make_unique<ConstantNodeSpec<T, type>>(value_); }
  //
  //  void print(std::ostream& out, int tab) const override {
  //    switch (type) {
  //      case ConstantNode::INTEGER:
  //        out << std::string(tab, ' ') << "ConstantInteger<" << value_ << ">\n";
  //        break;
  //      case ConstantNode::CHAR:
  //        out << std::string(tab, ' ') << "ConstantChar<" << value_ << ">\n";
  //        break;
  //      case ConstantNode::BOOLEAN:
  //        out << std::string(tab, ' ') << "ConstantBoolean<" << value_ << ">\n";
  //        break;
  //      case ConstantNode::STRING:
  //        out << std::string(tab, ' ') << "ConstantString<" << value_ << ">\n";
  //        break;
  //      default:
  //        break;
  //    }
  //  }

 private:
  T value_;
};

typedef ConstantNodeSpec<int, ConstantNode::INTEGER> IntegerConstantNode;
typedef ConstantNodeSpec<char, ConstantNode::CHAR> CharConstantNode;
typedef ConstantNodeSpec<bool, ConstantNode::BOOLEAN> BooleanConstantNode;
typedef ConstantNodeSpec<std::string, ConstantNode::STRING> StringConstantNode;
}  // namespace ast

#endif  // AST_CONSTANT_NODE_HPP
