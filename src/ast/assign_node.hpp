#ifndef AST_ASSIGN_NODE_HPP
#define AST_ASSIGN_NODE_HPP

#include <memory>

#include "expression_node.hpp"
#include "identifier_node.hpp"
#include "statement_node.hpp"

namespace ast {
class AssignNode : public StatementNode {
 public:
  AssignNode() : StatementNode{Category::ASSIGN} {}
  explicit AssignNode(ExpressionNode* lhs, ExpressionNode* rhs) : StatementNode{Category::ASSIGN}, lhs_{lhs}, rhs_{rhs} {}

  AssignNode(const AssignNode&) = delete;
  AssignNode(AssignNode&&) = default;

  AssignNode& operator=(const AssignNode&) = delete;
  AssignNode& operator=(AssignNode&&) = default;

  ~AssignNode() override = default;

  [[nodiscard]] const std::unique_ptr<ExpressionNode>& getLhs() const { return lhs_; }
  [[nodiscard]] const std::unique_ptr<ExpressionNode>& getRhs() const { return rhs_; }

  void setLhs(std::unique_ptr<ExpressionNode> lhs) { lhs_ = std::move(lhs); }
  void setRhs(std::unique_ptr<ExpressionNode> rhs) { rhs_ = std::move(rhs); }

  virtual void accept(AstVisitor* visitor) const override;
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;

 private:
  std::unique_ptr<ExpressionNode> lhs_;
  std::unique_ptr<ExpressionNode> rhs_;
};

//class AssignToVariableNode : public AssignNode {
// public:
//  AssignToVariableNode() : AssignNode{VARIABLE} {}
//  AssignToVariableNode(IdentifierNode* identifier, ExpressionNode* expression)
//      : AssignNode{VARIABLE}, variable_{identifier}, expression_{expression} {}
//
//  AssignToVariableNode(const AssignToVariableNode&) = delete;
//  AssignToVariableNode(AssignToVariableNode&&) = default;
//
//  AssignToVariableNode& operator=(const AssignToVariableNode&) = delete;
//  AssignToVariableNode& operator=(AssignToVariableNode&&) = default;
//
//  ~AssignToVariableNode() override = default;
//
//  [[nodiscard]] const std::unique_ptr<IdentifierNode>& getVariable() const { return variable_; }
//  [[nodiscard]] const std::unique_ptr<ExpressionNode>& getExpression() const { return expression_; }
//
//  void setVariable(std::unique_ptr<IdentifierNode> variable) { variable_ = std::move(variable); }
//  void setExpression(std::unique_ptr<ExpressionNode> expression) { expression_ = std::move(expression); }
//
//  virtual void accept(AstVisitor* visitor) const override;
//  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
//  void print(std::ostream& out, int tab) const override;
//
// private:
//  std::unique_ptr<IdentifierNode> variable_;
//  std::unique_ptr<ExpressionNode> expression_;
//};
//
//class AssignToArrayNode : public AssignNode {
// public:
//  AssignToArrayNode() : AssignNode{ARRAY} {}
//  AssignToArrayNode(ExpressionNode* array, ExpressionNode* index, ExpressionNode* expression)
//      : AssignNode{ARRAY}, array_{array}, index_{index}, expression_{expression} {}
//
//  AssignToArrayNode(const AssignToArrayNode&) = delete;
//  AssignToArrayNode(AssignToArrayNode&&) = default;
//
//  AssignToArrayNode& operator=(const AssignToArrayNode&) = delete;
//  AssignToArrayNode& operator=(AssignToArrayNode&&) = default;
//
//  ~AssignToArrayNode() override = default;
//
//  [[nodiscard]] const std::unique_ptr<ExpressionNode>& getArray() const { return array_; }
//  [[nodiscard]] const std::unique_ptr<ExpressionNode>& getIndex() const { return index_; }
//  [[nodiscard]] const std::unique_ptr<ExpressionNode>& getExpression() const { return expression_; }
//
//  void setArray(std::unique_ptr<ExpressionNode> array) { array_ = std::move(array); }
//  void setIndex(std::unique_ptr<ExpressionNode> index) { index_ = std::move(index); }
//  void setExpression(std::unique_ptr<ExpressionNode> expression) { expression_ = std::move(expression); }
//
//  virtual void accept(AstVisitor* visitor) const override;
//  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
//  void print(std::ostream& out, int tab) const override;
//
// private:
//  std::unique_ptr<ExpressionNode> array_;
//  std::unique_ptr<ExpressionNode> index_;
//  std::unique_ptr<ExpressionNode> expression_;
//};
//
//class AssignToRecordFieldNode : public AssignNode {
// public:
//  AssignToRecordFieldNode() : AssignNode{RECORD_FIELD} {}
//  AssignToRecordFieldNode(ExpressionNode* record, IdentifierNode* field, ExpressionNode* expression)
//      : AssignNode{RECORD_FIELD}, record_{record}, field_{field}, expression_{expression} {}
//
//  AssignToRecordFieldNode(const AssignToRecordFieldNode&) = delete;
//  AssignToRecordFieldNode(AssignToRecordFieldNode&&) = default;
//
//  AssignToRecordFieldNode& operator=(const AssignToRecordFieldNode&) = delete;
//  AssignToRecordFieldNode& operator=(AssignToRecordFieldNode&&) = default;
//
//  ~AssignToRecordFieldNode() override = default;
//
//  [[nodiscard]] const std::unique_ptr<ExpressionNode>& getRecord() const { return record_; }
//  [[nodiscard]] const std::unique_ptr<IdentifierNode>& getField() const { return field_; }
//  [[nodiscard]] const std::unique_ptr<ExpressionNode>& getExpression() const { return expression_; }
//
//  void setRecord(std::unique_ptr<ExpressionNode> record) { record_ = std::move(record); }
//  void setField(std::unique_ptr<IdentifierNode> field) { field_ = std::move(field); }
//  void setExpression(std::unique_ptr<ExpressionNode> expression) { expression_ = std::move(expression); }
//
//  virtual void accept(AstVisitor* visitor) const override;
//  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
//  void print(std::ostream& out, int tab) const override;
//
// private:
//  std::unique_ptr<ExpressionNode> record_;
//  std::unique_ptr<IdentifierNode> field_;
//  std::unique_ptr<ExpressionNode> expression_;
//};
}  // namespace ast

#endif  // AST_ASSIGN_NODE_HPP
