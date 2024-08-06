#ifndef AST_FOR_NODE_HPP
#define AST_FOR_NODE_HPP

#include <memory>

#include "expression_node.hpp"
#include "identifier_node.hpp"
#include "statement_node.hpp"

namespace ast {
class ForNode : public StatementNode {
 public:
  enum Direction { UNSPECIFIED, INCREMENT, DECREMENT };

  ForNode() : StatementNode{}, direction_{UNSPECIFIED} { type_ = Type::FOR; }
  ForNode(IdentifierNode* iterator, ExpressionNode* start, ExpressionNode* end, StatementNode* statements, Direction direction)
      : StatementNode{},
        iterator_{std::move(iterator)},
        start_{std::move(start)},
        end_{std::move(end)},
        statements_{std::move(statements)},
        direction_{direction} {
    type_ = Type::FOR;
  }

  ForNode(const ForNode&) = delete;
  ForNode(ForNode&&) = default;

  ForNode& operator=(const ForNode&) = delete;
  ForNode& operator=(ForNode&&) = default;

  ~ForNode() override = default;

  [[nodiscard]] const std::unique_ptr<IdentifierNode>& getIterator() const { return iterator_; }
  [[nodiscard]] const std::unique_ptr<ExpressionNode>& getStart() const { return start_; }
  [[nodiscard]] const std::unique_ptr<ExpressionNode>& getEnd() const { return end_; }
  [[nodiscard]] const std::unique_ptr<StatementNode>& getStatements() const { return statements_; }
  [[nodiscard]] Direction getDirection() const { return direction_; }

  void setIterator(std::unique_ptr<IdentifierNode> iterator) { iterator_ = std::move(iterator); }
  void setStart(std::unique_ptr<ExpressionNode> start) { start_ = std::move(start); }
  void setEnd(std::unique_ptr<ExpressionNode> end) { end_ = std::move(end); }
  void setStatements(std::unique_ptr<StatementNode> statements) { statements_ = std::move(statements); }
  void setDirection(Direction direction) { direction_ = direction; }

  virtual void accept(AstVisitor& visitor) const override;
  [[nodiscard]] std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;

 private:
  std::unique_ptr<IdentifierNode> iterator_;
  std::unique_ptr<ExpressionNode> start_;
  std::unique_ptr<ExpressionNode> end_;
  std::unique_ptr<StatementNode> statements_;
  Direction direction_;
};

class BreakNode : public StatementNode {
 public:
  BreakNode() : StatementNode{} { type_ = Type::BREAK; }
  BreakNode(const BreakNode&) = delete;
  BreakNode(BreakNode&&) = default;

  BreakNode& operator=(const BreakNode&) = delete;
  BreakNode& operator=(BreakNode&&) = default;

  ~BreakNode() override = default;

  virtual void accept(AstVisitor& visitor) const override;
  [[nodiscard]] std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;
};

class ContinueNode : public StatementNode {
 public:
  ContinueNode() : StatementNode{} { type_ = Type::CONTINUE; }
  ContinueNode(const ContinueNode&) = delete;
  ContinueNode(ContinueNode&&) = default;

  ContinueNode& operator=(const ContinueNode&) = delete;
  ContinueNode& operator=(ContinueNode&&) = default;

  ~ContinueNode() override = default;

  virtual void accept(AstVisitor& visitor) const override;
  [[nodiscard]] std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;
};
}  // namespace ast

#endif  // AST_FOR_NODE_HPP
