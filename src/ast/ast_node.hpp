#ifndef AST_AST_NODE_HPP
#define AST_AST_NODE_HPP

#include <memory>
#include <vector>

namespace ast {
class AstNode {
 public:
  enum Type {
	DEFAULT,
	CASE,
	CONSTANT,
	FOR,
	IDENTIFIER,
	IF,
	PARAMS_GROUP,
	PARAMS,
	PROGRAM,
	REPEAT,
	ROUTINE_BODY,
	ROUTINE_DECLARATION,
	ROUTINE_HEAD,
	ROUTINE,
	STATEMENT,
	TYPE,
	WHILE
  };

  AstNode() : type_(Type::DEFAULT) {}
  explicit AstNode(Type type) : type_(type) {}

  AstNode(const AstNode &) = delete;
  AstNode(AstNode &&) = default;

  AstNode &operator=(const AstNode &) = delete;
  AstNode &operator=(AstNode &&) = default;

  virtual ~AstNode() = default;

  [[nodiscard]] Type getType() const { return type_; }

 private:
  Type type_;
};
} // namespace ast

#endif // AST_AST_NODE_HPP
