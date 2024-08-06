#ifndef AST_ROUTINE_BODY_NODE_HPP
#define AST_ROUTINE_BODY_NODE_HPP

#include <memory>

#include "ast_node.hpp"
#include "compound_statement_node.hpp"

namespace ast {
class RoutineBodyNode : public AstNode {
 public:
  RoutineBodyNode() : AstNode{Type::ROUTINE_BODY} {}
  explicit RoutineBodyNode(CompoundStatementNode* statements) : AstNode{Type::ROUTINE_BODY}, statements_{statements} {}

  RoutineBodyNode(const RoutineBodyNode&) = delete;
  RoutineBodyNode(RoutineBodyNode&&) = default;

  RoutineBodyNode& operator=(const RoutineBodyNode&) = delete;
  RoutineBodyNode& operator=(RoutineBodyNode&&) = default;

  ~RoutineBodyNode() override = default;

  [[nodiscard]] const std::unique_ptr<CompoundStatementNode>& getStatements() const { return statements_; }

  void setStatements(std::unique_ptr<CompoundStatementNode> statements) { statements_ = std::move(statements); }

  virtual void accept(AstVisitor& visitor) const override;
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  virtual void print(std::ostream& out, int tab) const override;

 private:
  std::unique_ptr<CompoundStatementNode> statements_;
};
}  // namespace ast

#endif  // AST_ROUTINE_BODY_NODE_HPP
