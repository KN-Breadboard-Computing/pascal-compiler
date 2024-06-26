#ifndef AST_ROUTINE_HEAD_NODE_HPP
#define AST_ROUTINE_HEAD_NODE_HPP

#include <memory>
#include <variant>
#include <vector>
#include <utility>

#include "ast_node.hpp"
#include "constant_node.hpp"
#include "identifier_node.hpp"
#include "routine_declaration_node.hpp"
#include "type_node.hpp"

namespace ast {
class RoutineHeadNode : public AstNode {
 public:
  RoutineHeadNode() : AstNode{Type::ROUTINE_HEAD} {}
  RoutineHeadNode(std::vector<std::pair<IdentifierNode *, ConstantNode *> *> *constantsPart,
				  std::vector<std::pair<IdentifierNode *, TypeNode *> *> *typesPart,
				  std::vector<std::pair<std::vector<ast::IdentifierNode *> *, TypeNode *> *> *variablesPart,
				  std::vector<RoutineDeclarationNode> *routinePart) :
	  AstNode{Type::ROUTINE_HEAD},
	  constantsPart_{constantsPart},
	  typesPart_{typesPart},
	  variablesPart_{variablesPart},
	  routinePart_{routinePart} {}

  RoutineHeadNode(const RoutineHeadNode &) = delete;
  RoutineHeadNode(RoutineHeadNode &&) = default;

  RoutineHeadNode &operator=(const RoutineHeadNode &) = delete;
  RoutineHeadNode &operator=(RoutineHeadNode &&) = default;

  ~RoutineHeadNode() override = default;

  [[nodiscard]] const std::unique_ptr<std::vector<std::pair<IdentifierNode *,
															ConstantNode *> *>> &getConstantsPart() const {
	return constantsPart_;
  }

  [[nodiscard]] const std::unique_ptr<std::vector<std::pair<IdentifierNode *, TypeNode *> *>> &getTypesPart() const {
	return typesPart_;
  }

  [[nodiscard]] const std::unique_ptr<std::vector<std::pair<std::vector<ast::IdentifierNode *> *,
															TypeNode *> *>> &getVariablesPart() const {
	return variablesPart_;
  }

  [[nodiscard]] const std::unique_ptr<std::vector<RoutineDeclarationNode>> &getRoutinePart() const {
	return routinePart_;
  }

  void setConstantsPart(std::unique_ptr<std::vector<std::pair<IdentifierNode *, ConstantNode *> *>> &constantsPart) {
	constantsPart_ = std::move(constantsPart);
  }

  void setTypesPart(std::unique_ptr<std::vector<std::pair<IdentifierNode *, TypeNode *> *>> &typesPart) {
	typesPart_ = std::move(typesPart);
  }

  void setVariablesPart(std::unique_ptr<std::vector<std::pair<std::vector<ast::IdentifierNode *> *,
															  TypeNode *> *>> &variablesPart) {
	variablesPart_ = std::move(variablesPart);
  }

  void setRoutinePart(std::unique_ptr<std::vector<RoutineDeclarationNode>> &routinePart) {
	routinePart_ = std::move(routinePart);
  }

 private:
  std::unique_ptr<std::vector<std::pair<IdentifierNode *, ConstantNode *> *>> constantsPart_;
  std::unique_ptr<std::vector<std::pair<IdentifierNode *, TypeNode *> *>> typesPart_;
  std::unique_ptr<std::vector<std::pair<std::vector<ast::IdentifierNode *> *, TypeNode *> *>> variablesPart_;
  std::unique_ptr<std::vector<RoutineDeclarationNode>> routinePart_;
};
} // namespace ast

#endif // AST_ROUTINE_HEAD_NODE_HPP
