#ifndef AST_COMPOUND_STATEMENT_NODE_HPP
#define AST_COMPOUND_STATEMENT_NODE_HPP

#include <memory>
#include <vector>

#include "statement_node.hpp"

namespace ast {
class CompoundStatementNode : public StatementNode {
 public:
  CompoundStatementNode() : StatementNode{Category::COMPOUND} {}
  explicit CompoundStatementNode(std::vector<StatementNode*>* statements) : StatementNode{Category::COMPOUND}, statements_{statements} {}

  CompoundStatementNode(const CompoundStatementNode&) = delete;
  CompoundStatementNode(CompoundStatementNode&&) = default;

  CompoundStatementNode& operator=(const CompoundStatementNode&) = delete;
  CompoundStatementNode& operator=(CompoundStatementNode&&) = default;

  ~CompoundStatementNode() override = default;

  [[nodiscard]] const std::unique_ptr<std::vector<StatementNode*>>& getStatements() const { return statements_; }

  void setStatements(std::unique_ptr<std::vector<StatementNode*>> statements) { statements_ = std::move(statements); }

  virtual void accept(AstVisitor* visitor) const override;
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  virtual void print(std::ostream& out, int tab) const override;

 private:
  std::unique_ptr<std::vector<StatementNode*>> statements_{};
};
}  // namespace ast

#endif  // AST_COMPOUND_STATEMENT_NODE_HPP
