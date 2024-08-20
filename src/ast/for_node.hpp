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

  ForNode() : StatementNode{Category::FOR}, direction_{UNSPECIFIED} {}
  ForNode(IdentifierNode* iterator, ExpressionNode* start, ExpressionNode* end, StatementNode* statements, Direction direction)
      : StatementNode{Category::FOR},
        iterator_{iterator},
        start_{start},
        end_{end},
        statements_{statements},
        direction_{direction} {}

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

  virtual void accept(AstVisitor* visitor) const override;
  [[nodiscard]] std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;

 private:
  std::unique_ptr<IdentifierNode> iterator_;
  std::unique_ptr<ExpressionNode> start_;
  std::unique_ptr<ExpressionNode> end_;
  std::unique_ptr<StatementNode> statements_;
  Direction direction_;
};
}  // namespace ast

#endif  // AST_FOR_NODE_HPP
