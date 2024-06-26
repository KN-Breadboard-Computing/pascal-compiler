#ifndef AST_ROUTINE_BODY_NODE_HPP
#define AST_ROUTINE_BODY_NODE_HPP

#include <memory>
#include <vector>

#include "ast_node.hpp"
#include "statement_node.hpp"

namespace ast {
class RoutineBodyNode : public AstNode {
 public:
  RoutineBodyNode() : AstNode{Type::ROUTINE_BODY} {}
  explicit RoutineBodyNode(std::vector<StatementNode *> *statements)
	  : AstNode{Type::ROUTINE_BODY}, statements_{statements} {}

  RoutineBodyNode(const RoutineBodyNode &) = delete;
  RoutineBodyNode(RoutineBodyNode &&) = default;

  RoutineBodyNode &operator=(const RoutineBodyNode &) = delete;
  RoutineBodyNode &operator=(RoutineBodyNode &&) = default;

  ~RoutineBodyNode() override = default;

  [[nodiscard]] const std::unique_ptr<std::vector<StatementNode *>> &getStatements() const {
	return statements_;
  }

  void setStatements(std::unique_ptr<std::vector<StatementNode *>> statements) {
	statements_ = std::move(statements);
  }

 private:
  std::unique_ptr<std::vector<StatementNode *>> statements_;
};
} // namespace ast

#endif // AST_ROUTINE_BODY_NODE_HPP
