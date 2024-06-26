#ifndef AST_ROUTINE_DECLARATION_NODE_HPP
#define AST_ROUTINE_DECLARATION_NODE_HPP

#include <memory>
#include <string>

#include "ast_node.hpp"
#include "params_node.hpp"
#include "routine_node.hpp"
#include "simple_type_node.hpp"

namespace ast {
class RoutineNode;

class RoutineDeclarationNode : public AstNode {
 public:
  enum RoutineType {
	UNSPECIFIED,
	FUNCTION,
	PROCEDURE
  };

  RoutineDeclarationNode() : AstNode{Type::ROUTINE_DECLARATION}, routineType_{RoutineType::UNSPECIFIED} {}
  explicit RoutineDeclarationNode(RoutineType type) : AstNode{Type::ROUTINE_DECLARATION}, routineType_{type} {}
  RoutineDeclarationNode(RoutineType type,
						 std::string name,
						 ParamsNode *params,
						 SimpleTypeNode *returnType,
						 RoutineNode *routine)
	  : AstNode{Type::ROUTINE_DECLARATION},
		routineType_{type},
		name_{std::move(name)},
		params_{params},
		returnType_{returnType},
		routine_{routine} {}

  RoutineDeclarationNode(const RoutineDeclarationNode &) = delete;
  RoutineDeclarationNode(RoutineDeclarationNode &&) = default;

  RoutineDeclarationNode &operator=(const RoutineDeclarationNode &) = delete;
  RoutineDeclarationNode &operator=(RoutineDeclarationNode &&) = default;

  ~RoutineDeclarationNode() override = default;

  [[nodiscard]] RoutineType getRoutineType() const { return routineType_; }
  [[nodiscard]] const std::string &getName() const { return name_; }
  [[nodiscard]] const std::unique_ptr<ParamsNode> &getParams() const { return params_; }
  [[nodiscard]] const std::unique_ptr<SimpleTypeNode> &getReturnType() const { return returnType_; }
  [[nodiscard]] const std::unique_ptr<RoutineNode> &getRoutine() const { return routine_; }

  void setRoutineType(RoutineType type) { routineType_ = type; }
  void setName(std::string name) { name_ = std::move(name); }
  void setParams(std::unique_ptr<ParamsNode> params) { params_ = std::move(params); }
  void setReturnType(std::unique_ptr<SimpleTypeNode> returnType) { returnType_ = std::move(returnType); }
  void setRoutine(std::unique_ptr<RoutineNode> routine) { routine_ = std::move(routine); }

 private:
  RoutineType routineType_;
  std::string name_;
  std::unique_ptr<ParamsNode> params_;
  std::unique_ptr<SimpleTypeNode> returnType_;
  std::unique_ptr<RoutineNode> routine_;
};
} // namespace ast

#endif // AST_ROUTINE_DECLARATION_NODE_HPP
