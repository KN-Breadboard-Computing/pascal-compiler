#ifndef AST_STATEMENT_NODE_HPP
#define AST_STATEMENT_NODE_HPP

#include <optional>

#include "ast_node.hpp"

namespace ast {
class StatementNode : public AstNode {
 public:
  StatementNode() : AstNode{Type::STATEMENT}, label{std::nullopt} {}

  StatementNode(const StatementNode &) = delete;
  StatementNode(StatementNode &&) = default;

  StatementNode &operator=(const StatementNode &) = delete;
  StatementNode &operator=(StatementNode &&) = default;

  ~StatementNode() override = default;

  [[nodiscard]] std::optional<uint64_t> getLabel() const {
	return label;
  }

  void setLabel(uint64_t newLabel) {
	label = newLabel;
  }

 private:
  std::optional<uint64_t> label;
};
} // namespace ast

#endif // AST_STATEMENT_NODE_HPP
