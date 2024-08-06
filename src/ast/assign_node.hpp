#ifndef AST_ASSIGN_NODE_HPP
#define AST_ASSIGN_NODE_HPP

#include <memory>

#include "expression_node.hpp"
#include "identifier_node.hpp"
#include "statement_node.hpp"

namespace ast {
class AssignNode : public StatementNode {
 public:
  enum DestinationType { UNSPECIFIED, VARIABLE, ARRAY, RECORD_FIELD };

  AssignNode() : StatementNode{}, destinationType_{UNSPECIFIED} { type_ = Type::ASSIGN; }
  explicit AssignNode(DestinationType destinationType) : StatementNode{}, destinationType_{destinationType} {
    type_ = Type::ASSIGN;
  }

  AssignNode(const AssignNode&) = delete;
  AssignNode(AssignNode&&) = default;

  AssignNode& operator=(const AssignNode&) = delete;
  AssignNode& operator=(AssignNode&&) = default;

  ~AssignNode() override = default;

  [[nodiscard]] DestinationType getDestinationType() const { return destinationType_; }

  void setDestinationType(DestinationType destinationType) { destinationType_ = destinationType; }

 private:
  DestinationType destinationType_;
};

class AssignToVariableNode : public AssignNode {
 public:
  AssignToVariableNode() : AssignNode{VARIABLE} {}
  AssignToVariableNode(IdentifierNode* identifier, ExpressionNode* expression)
      : AssignNode{VARIABLE}, variable_{identifier}, expression_{expression} {}

  AssignToVariableNode(const AssignToVariableNode&) = delete;
  AssignToVariableNode(AssignToVariableNode&&) = default;

  AssignToVariableNode& operator=(const AssignToVariableNode&) = delete;
  AssignToVariableNode& operator=(AssignToVariableNode&&) = default;

  ~AssignToVariableNode() override = default;

  [[nodiscard]] const std::unique_ptr<IdentifierNode>& getVariable() const { return variable_; }
  [[nodiscard]] const std::unique_ptr<ExpressionNode>& getExpression() const { return expression_; }

  void setVariable(std::unique_ptr<IdentifierNode> variable) { variable_ = std::move(variable); }
  void setExpression(std::unique_ptr<ExpressionNode> expression) { expression_ = std::move(expression); }

  virtual void accept(AstVisitor& visitor) const override;
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;

 private:
  std::unique_ptr<IdentifierNode> variable_;
  std::unique_ptr<ExpressionNode> expression_;
};

class AssignToArrayNode : public AssignNode {
 public:
  AssignToArrayNode() : AssignNode{ARRAY} {}
  AssignToArrayNode(IdentifierNode* identifier, ExpressionNode* index, ExpressionNode* expression)
      : AssignNode{ARRAY}, array_{identifier}, index_{index}, expression_{expression} {}

  AssignToArrayNode(const AssignToArrayNode&) = delete;
  AssignToArrayNode(AssignToArrayNode&&) = default;

  AssignToArrayNode& operator=(const AssignToArrayNode&) = delete;
  AssignToArrayNode& operator=(AssignToArrayNode&&) = default;

  ~AssignToArrayNode() override = default;

  [[nodiscard]] const std::unique_ptr<IdentifierNode>& getArray() const { return array_; }
  [[nodiscard]] const std::unique_ptr<ExpressionNode>& getIndex() const { return index_; }
  [[nodiscard]] const std::unique_ptr<ExpressionNode>& getExpression() const { return expression_; }

  void setArray(std::unique_ptr<IdentifierNode> array) { array_ = std::move(array); }
  void setIndex(std::unique_ptr<ExpressionNode> index) { index_ = std::move(index); }
  void setExpression(std::unique_ptr<ExpressionNode> expression) { expression_ = std::move(expression); }

  virtual void accept(AstVisitor& visitor) const override;
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;

 private:
  std::unique_ptr<IdentifierNode> array_;
  std::unique_ptr<ExpressionNode> index_;
  std::unique_ptr<ExpressionNode> expression_;
};

class AssignToRecordFieldNode : public AssignNode {
 public:
  AssignToRecordFieldNode() : AssignNode{RECORD_FIELD} {}
  AssignToRecordFieldNode(IdentifierNode* record, IdentifierNode* field, ExpressionNode* expression)
      : AssignNode{RECORD_FIELD}, record_{record}, field_{field}, expression_{expression} {}

  AssignToRecordFieldNode(const AssignToRecordFieldNode&) = delete;
  AssignToRecordFieldNode(AssignToRecordFieldNode&&) = default;

  AssignToRecordFieldNode& operator=(const AssignToRecordFieldNode&) = delete;
  AssignToRecordFieldNode& operator=(AssignToRecordFieldNode&&) = default;

  ~AssignToRecordFieldNode() override = default;

  [[nodiscard]] const std::unique_ptr<IdentifierNode>& getRecord() const { return record_; }
  [[nodiscard]] const std::unique_ptr<IdentifierNode>& getField() const { return field_; }
  [[nodiscard]] const std::unique_ptr<ExpressionNode>& getExpression() const { return expression_; }

  void setRecord(std::unique_ptr<IdentifierNode> record) { record_ = std::move(record); }
  void setField(std::unique_ptr<IdentifierNode> field) { field_ = std::move(field); }
  void setExpression(std::unique_ptr<ExpressionNode> expression) { expression_ = std::move(expression); }

  virtual void accept(AstVisitor& visitor) const override;
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;

 private:
  std::unique_ptr<IdentifierNode> record_;
  std::unique_ptr<IdentifierNode> field_;
  std::unique_ptr<ExpressionNode> expression_;
};
}  // namespace ast

#endif  // AST_ASSIGN_NODE_HPP
