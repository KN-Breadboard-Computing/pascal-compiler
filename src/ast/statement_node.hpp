#ifndef AST_STATEMENT_NODE_HPP
#define AST_STATEMENT_NODE_HPP

#include <optional>

#include "ast_node.hpp"

namespace ast {
class StatementNode : public AstNode {
 public:
  StatementNode() : AstNode{Type::STATEMENT}, label_{std::nullopt} {}

  StatementNode(const StatementNode&) = delete;
  StatementNode(StatementNode&&) = default;

  StatementNode& operator=(const StatementNode&) = delete;
  StatementNode& operator=(StatementNode&&) = default;

  ~StatementNode() override = default;

  [[nodiscard]] std::optional<uint64_t> getLabel() const { return label_; }

  void setLabel(uint64_t newLabel) { label_ = newLabel; }

  void removeLabel() { label_ = std::nullopt; }

  virtual void accept(AstVisitor& visitor) const override;
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  virtual void print(std::ostream& out, int tab) const override;

 private:
  std::optional<uint64_t> label_;
};
}  // namespace ast

#endif  // AST_STATEMENT_NODE_HPP
