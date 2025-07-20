#ifndef AST_ROUTINE_DECL_HEAD_NODE_HPP
#define AST_ROUTINE_DECL_HEAD_NODE_HPP

#include <memory>
#include <utility>
#include <variant>
#include <vector>

#include "ast_node.hpp"
#include "constant_node.hpp"
#include "identifier_node.hpp"
#include "params_node.hpp"
#include "routine_body_node.hpp"
#include "type_node.hpp"

namespace ast {
// Forward declarations
class RoutineDeclarationNode;
class RoutineHeadNode;
class RoutineNode;

// Declarations and partial definitions
class RoutineHeadNode : public AstNode {
 public:
  RoutineHeadNode() : AstNode{Type::ROUTINE_HEAD} {}
  RoutineHeadNode(std::vector<std::pair<IdentifierNode*, ConstantNode*>*>* constantsPart, std::vector<std::pair<IdentifierNode*, TypeNode*>*>* typesPart, std::vector<std::pair<std::vector<IdentifierNode*>*, TypeNode*>*>* variablesPart,
                  std::vector<RoutineDeclarationNode*>* routinePart)
      : AstNode{Type::ROUTINE_HEAD}, constantsPart_{constantsPart}, typesPart_{typesPart}, variablesPart_{variablesPart}, routinePart_{routinePart} {}

  RoutineHeadNode(const RoutineHeadNode&) = delete;
  RoutineHeadNode(RoutineHeadNode&&) = default;

  RoutineHeadNode& operator=(const RoutineHeadNode&) = delete;
  RoutineHeadNode& operator=(RoutineHeadNode&&) = default;

  ~RoutineHeadNode() override = default;

  [[nodiscard]] const std::unique_ptr<std::vector<std::pair<IdentifierNode*, ConstantNode*>*>>& getConstantsPart() const { return constantsPart_; }

  [[nodiscard]] const std::unique_ptr<std::vector<std::pair<IdentifierNode*, TypeNode*>*>>& getTypesPart() const { return typesPart_; }

  [[nodiscard]] const std::unique_ptr<std::vector<std::pair<std::vector<IdentifierNode*>*, TypeNode*>*>>& getVariablesPart() const { return variablesPart_; }

  [[nodiscard]] const std::unique_ptr<std::vector<RoutineDeclarationNode*>>& getRoutinePart() const { return routinePart_; }

  void setConstantsPart(std::unique_ptr<std::vector<std::pair<IdentifierNode*, ConstantNode*>*>>& constantsPart) { constantsPart_ = std::move(constantsPart); }

  void setTypesPart(std::unique_ptr<std::vector<std::pair<IdentifierNode*, TypeNode*>*>>& typesPart) { typesPart_ = std::move(typesPart); }

  void setVariablesPart(std::unique_ptr<std::vector<std::pair<std::vector<IdentifierNode*>*, TypeNode*>*>>& variablesPart) { variablesPart_ = std::move(variablesPart); }

  void setRoutinePart(std::unique_ptr<std::vector<RoutineDeclarationNode*>>& routinePart) { routinePart_ = std::move(routinePart); }

  virtual void accept(AstVisitor* visitor) const override;
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  virtual void print(std::ostream& out, int tab) const override;

 private:
  std::unique_ptr<std::vector<std::pair<IdentifierNode*, ConstantNode*>*>> constantsPart_;
  std::unique_ptr<std::vector<std::pair<IdentifierNode*, TypeNode*>*>> typesPart_;
  std::unique_ptr<std::vector<std::pair<std::vector<IdentifierNode*>*, TypeNode*>*>> variablesPart_;
  std::unique_ptr<std::vector<RoutineDeclarationNode*>> routinePart_;
};

class RoutineDeclarationNode : public AstNode {
 public:
  enum RoutineType { UNSPECIFIED, FUNCTION, PROCEDURE };

  RoutineDeclarationNode() : AstNode{Type::ROUTINE_DECLARATION}, routineType_{RoutineType::UNSPECIFIED} {}
  explicit RoutineDeclarationNode(RoutineType type) : AstNode{Type::ROUTINE_DECLARATION}, routineType_{type} {}
  RoutineDeclarationNode(RoutineType type, std::string name, ParamsNode* params, SimpleTypeNode* returnType, RoutineNode* routine)
      : AstNode{Type::ROUTINE_DECLARATION}, routineType_{type}, name_{std::move(name)}, params_{params}, returnType_{returnType}, routine_{routine} {}

  RoutineDeclarationNode(const RoutineDeclarationNode&) = delete;
  RoutineDeclarationNode(RoutineDeclarationNode&&) = default;

  RoutineDeclarationNode& operator=(const RoutineDeclarationNode&) = delete;
  RoutineDeclarationNode& operator=(RoutineDeclarationNode&&) = default;

  ~RoutineDeclarationNode() override = default;

  [[nodiscard]] RoutineType getRoutineType() const { return routineType_; }
  [[nodiscard]] const std::string& getName() const { return name_; }
  [[nodiscard]] const std::unique_ptr<ParamsNode>& getParams() const { return params_; }
  [[nodiscard]] const std::unique_ptr<SimpleTypeNode>& getReturnType() const { return returnType_; }
  [[nodiscard]] const std::unique_ptr<RoutineNode>& getRoutine() const { return routine_; }

  void setRoutineType(RoutineType type) { routineType_ = type; }
  void setName(std::string name) { name_ = std::move(name); }
  void setParams(std::unique_ptr<ParamsNode> params) { params_ = std::move(params); }
  void setReturnType(std::unique_ptr<SimpleTypeNode> returnType) { returnType_ = std::move(returnType); }
  void setRoutine(std::unique_ptr<RoutineNode> routine) { routine_ = std::move(routine); }

  virtual void accept(AstVisitor* visitor) const override;
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  virtual void print(std::ostream& out, int tab) const override;

 private:
  RoutineType routineType_;
  std::string name_;
  std::unique_ptr<ParamsNode> params_;
  std::unique_ptr<SimpleTypeNode> returnType_;
  std::unique_ptr<RoutineNode> routine_;
};

class RoutineNode : public AstNode {
 public:
  enum SubType {
    UNSPECIFIED,
    MAIN,
    FUNCTION,
    PROCEDURE,
  };

  RoutineNode() : AstNode(Type::ROUTINE), subType_(UNSPECIFIED) {}
  explicit RoutineNode(SubType subType) : AstNode{Type::ROUTINE}, subType_{subType} {}
  RoutineNode(RoutineHeadNode* head, RoutineBodyNode* body) : AstNode{Type::ROUTINE}, subType_{UNSPECIFIED}, head_{head}, body_{body} {}
  RoutineNode(SubType subType, RoutineHeadNode* head, RoutineBodyNode* body) : AstNode{Type::ROUTINE}, subType_{subType}, head_{head}, body_{body} {}

  RoutineNode(const RoutineNode&) = delete;
  RoutineNode(RoutineNode&&) = default;

  RoutineNode& operator=(const RoutineNode&) = delete;
  RoutineNode& operator=(RoutineNode&&) = default;

  ~RoutineNode() override = default;

  [[nodiscard]] SubType getSubType() const { return subType_; }
  [[nodiscard]] const std::unique_ptr<RoutineHeadNode>& getHead() const { return head_; }
  [[nodiscard]] const std::unique_ptr<RoutineBodyNode>& getBody() const { return body_; }

  void setSubType(SubType subType) { subType_ = subType; }
  void setHead(std::unique_ptr<RoutineHeadNode> head) { head_ = std::move(head); }
  void setBody(std::unique_ptr<RoutineBodyNode> body) { body_ = std::move(body); }

  virtual void accept(AstVisitor* visitor) const override;
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  virtual void print(std::ostream& out, int tab) const override;

 private:
  SubType subType_;
  std::unique_ptr<RoutineHeadNode> head_;
  std::unique_ptr<RoutineBodyNode> body_;
};
}  // namespace ast

#endif  // AST_ROUTINE_DECL_HEAD_NODE_HPP
