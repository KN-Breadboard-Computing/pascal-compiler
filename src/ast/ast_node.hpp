#ifndef AST_AST_NODE_HPP
#define AST_AST_NODE_HPP

#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

namespace ast {
class AstNode {
 public:
  enum Type {
    DEFAULT,
    ARGUMENTS_LIST,
    ARRAY,
    ASSIGN,
    CALL,
    CASE,
    COMPOUND_STATEMENT,
    CONSTANT,
    EXPRESSION,
    FOR,
    GO_TO,
    IDENTIFIER,
    IF,
    PARAMS_GROUP,
    PARAMS,
    PROGRAM,
    RECORD,
    REPEAT,
    ROUTINE_BODY,
    ROUTINE_DECLARATION,
    ROUTINE_HEAD,
    ROUTINE,
    SIMPLE_TYPE,
    STATEMENT,
    TYPE,
    WHILE
  };

  AstNode() : type_{Type::DEFAULT} {}
  explicit AstNode(Type type) : type_{type} {}

  AstNode(const AstNode&) = delete;
  AstNode(AstNode&&) = default;

  AstNode& operator=(const AstNode&) = delete;
  AstNode& operator=(AstNode&&) = default;

  virtual ~AstNode() = default;

  [[nodiscard]] Type getType() const { return type_; }

  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const = 0;
  virtual void print(std::ostream& out, int tab) const = 0;

 protected:
  Type type_;
};
}  // namespace ast

#endif  // AST_AST_NODE_HPP
