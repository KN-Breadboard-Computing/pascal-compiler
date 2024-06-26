#ifndef AST_CONSTANT_NODE_HPP
#define AST_CONSTANT_NODE_HPP

#include "ast_node.hpp"

namespace ast {
class ConstantNode : public AstNode {
 public:
  enum ConstantType { UNSPECIFIED, INTEGER, CHAR, BOOLEAN, STRING };

  ConstantNode() : AstNode{Type::CONSTANT}, constantType_{UNSPECIFIED} {}
  explicit ConstantNode(ConstantType constantType) : AstNode{Type::CONSTANT}, constantType_{constantType} {}

  ConstantNode(const ConstantNode &) = delete;
  ConstantNode(ConstantNode &&) = default;

  ConstantNode &operator=(const ConstantNode &) = delete;
  ConstantNode &operator=(ConstantNode &&) = default;

  ~ConstantNode() override = default;

  [[nodiscard]] ConstantType getConstantType() const { return constantType_; }

 private:
  ConstantType constantType_;
};

template<typename T, ConstantNode::ConstantType type>
class ConstantNodeSpec : public ConstantNode {
 public:
  ConstantNodeSpec() : ConstantNode{type}, value_{} {}
  explicit ConstantNodeSpec(T value) : ConstantNode{type}, value_{value} {}

  ConstantNodeSpec(const ConstantNodeSpec &) = delete;
  ConstantNodeSpec(ConstantNodeSpec &&) noexcept = default;

  ConstantNodeSpec &operator=(const ConstantNodeSpec &) = delete;
  ConstantNodeSpec &operator=(ConstantNodeSpec &&) noexcept = default;

  ~ConstantNodeSpec() override = default;

  [[nodiscard]] T getValue() const { return value_; }

 private:
  T value_;
};

typedef ConstantNodeSpec<int, ConstantNode::INTEGER> IntegerConstantNode;
typedef ConstantNodeSpec<char, ConstantNode::CHAR> CharConstantNode;
typedef ConstantNodeSpec<bool, ConstantNode::BOOLEAN> BooleanConstantNode;
typedef ConstantNodeSpec<std::string, ConstantNode::STRING> StringConstantNode;
} // namespace ast

#endif // AST_CONSTANT_NODE_HPP
