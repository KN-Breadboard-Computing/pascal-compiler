#ifndef AST_ROUTINE_NODE_HPP
#define AST_ROUTINE_NODE_HPP

#include <memory>

#include "ast_node.hpp"
#include "routine_body_node.hpp"
#include "routine_head_node.hpp"

namespace ast {
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
  RoutineNode(RoutineHeadNode *head, RoutineBodyNode *body)
	  : AstNode{Type::ROUTINE}, subType_{UNSPECIFIED}, head_{head}, body_{body} {}
  RoutineNode(SubType subType, RoutineHeadNode *head, RoutineBodyNode *body)
	  : AstNode{Type::ROUTINE}, subType_{subType}, head_{head}, body_{body} {}

  RoutineNode(const RoutineNode &) = delete;
  RoutineNode(RoutineNode &&) = default;

  RoutineNode &operator=(const RoutineNode &) = delete;
  RoutineNode &operator=(RoutineNode &&) = default;

  ~RoutineNode() override = default;

  [[nodiscard]] SubType getSubType() const { return subType_; }
  [[nodiscard]] const std::unique_ptr<RoutineHeadNode> &getHead() const { return head_; }
  [[nodiscard]] const std::unique_ptr<RoutineBodyNode> &getBody() const { return body_; }

  void setSubType(SubType subType) { subType_ = subType; }
  void setHead(std::unique_ptr<RoutineHeadNode> head) { head_ = std::move(head); }
  void setBody(std::unique_ptr<RoutineBodyNode> body) { body_ = std::move(body); }

 private:
  SubType subType_;
  std::unique_ptr<RoutineHeadNode> head_;
  std::unique_ptr<RoutineBodyNode> body_;
};
} // namespace ast

#endif // AST_ROUTINE_NODE_HPP
