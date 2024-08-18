#ifndef AST_STATEMENT_NODE_HPP
#define AST_STATEMENT_NODE_HPP

#include <optional>

#include "ast_node.hpp"

namespace ast {
class StatementNode : public AstNode {
 public:
  enum Category {
	UNSPECIFIED,
	ASSIGN,
	BREAK,
	CALL,
	CASE,
	COMPOUND,
	CONTINUE,
	FOR,
	GOTO,
	IF,
	REPEAT,
	WHILE
  };

  StatementNode() : AstNode{Type::STATEMENT}, label_{std::nullopt}, category_{Category::UNSPECIFIED} {}
  explicit StatementNode(Category category) : AstNode{Type::STATEMENT}, label_{std::nullopt}, category_{category} {}

  StatementNode(const StatementNode &) = delete;
  StatementNode(StatementNode &&) = default;

  StatementNode &operator=(const StatementNode &) = delete;
  StatementNode &operator=(StatementNode &&) = default;

  ~StatementNode() override = default;

  [[nodiscard]] std::optional<uint64_t> getLabel() const { return label_; }
  void setLabel(uint64_t newLabel) { label_ = newLabel; }
  void removeLabel() { label_ = std::nullopt; }

  void setCategory(Category newCategory) { category_ = newCategory; }
  [[nodiscard]] Category getCategory() const { return category_; }

 private:
  std::optional<uint64_t> label_;
  Category category_;
};
}  // namespace ast

#endif  // AST_STATEMENT_NODE_HPP
