#ifndef AST_COMPOUND_STATEMENT_NODE_HPP
#define AST_COMPOUND_STATEMENT_NODE_HPP

#include <memory>
#include <vector>

#include "statement_node.hpp"

namespace ast {
class CompoundStatementNode : public StatementNode {
 public:
  CompoundStatementNode() : StatementNode{} { type_ = Type::COMPOUND_STATEMENT; }
  explicit CompoundStatementNode(std::vector<StatementNode*>* statements) : StatementNode{}, statements_{statements} {
    type_ = Type::COMPOUND_STATEMENT;
  }

  CompoundStatementNode(const CompoundStatementNode&) = delete;
  CompoundStatementNode(CompoundStatementNode&&) = default;

  CompoundStatementNode& operator=(const CompoundStatementNode&) = delete;
  CompoundStatementNode& operator=(CompoundStatementNode&&) = default;

  ~CompoundStatementNode() override = default;

  [[nodiscard]] const std::unique_ptr<std::vector<StatementNode*>>& getStatements() const { return statements_; }

  void setStatements(std::unique_ptr<std::vector<StatementNode*>> statements) { statements_ = std::move(statements); }

  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override {
    std::unique_ptr<std::vector<StatementNode*>> statements{};
    for (const auto& statement : *statements_) {
      statements->push_back(dynamic_cast<StatementNode*>(statement->clone().release()));
    }
    auto clone = std::make_unique<CompoundStatementNode>();
    clone->setStatements(std::move(statements));
    return clone;
  }

  virtual void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ') << "CompoundStatementNode\n";
    for (const auto& statement : *statements_) {
      statement->print(out, tab + 2);
    }
  }

 private:
  std::unique_ptr<std::vector<StatementNode*>> statements_{};
};
}  // namespace ast

#endif  // AST_COMPOUND_STATEMENT_NODE_HPP
