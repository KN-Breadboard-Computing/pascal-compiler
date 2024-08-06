#include "assign_node.hpp"

namespace ast {
// AssignToVariableNode
virtual void AssignToVariableNode::accept(AstVisitor& visitor) const override {
  visitor.visit(*this);
}

[[nodiscard]] virtual std::unique_ptr<AstNode> AssignToVariableNode::clone() const override {
  IdentifierNode* newVariable = dynamic_cast<IdentifierNode*>(variable_->clone().release());
  ExpressionNode* newExpression = dynamic_cast<ExpressionNode*>(expression_->clone().release());

  return std::make_unique<AssignToVariableNode>(newVariable, newExpression);
}

void AssignToVariableNode::print(std::ostream& out, int tab) const override {
  if (getLabel().has_value()) {
    out << std::string(tab, ' ') << "AssignToVariableNode with label: " << getLabel().value() << "\n";
  }
  else {
    out << std::string(tab, ' ') << "AssignToVariableNode\n";
  }

  variable_->print(out, tab + 2);
  expression_->print(out, tab + 2);
}


// AssignToArrayNode
virtual void AssignToArrayNode::accept(AstVisitor& visitor) const override {
  visitor.visit(*this);
}

[[nodiscard]] virtual std::unique_ptr<AstNode> AssignToArrayNode::clone() const override {
  IdentifierNode* newArray = dynamic_cast<IdentifierNode*>(array_->clone().release());
  ExpressionNode* newIndex = dynamic_cast<ExpressionNode*>(index_->clone().release());
  ExpressionNode* newExpression = dynamic_cast<ExpressionNode*>(expression_->clone().release());

  return std::make_unique<AssignToArrayNode>(newArray, newIndex, newExpression);
}

void AssignToArrayNode::print(std::ostream& out, int tab) const override {
  if (getLabel().has_value()) {
    out << std::string(tab, ' ') << "AssignToArrayNode with label: " << getLabel().value() << "\n";
  }
  else {
    out << std::string(tab, ' ') << "AssignToArrayNode\n";
  }

  array_->print(out, tab + 2);
  index_->print(out, tab + 2);
  expression_->print(out, tab + 2);
}


// AssignToRecordFieldNode
virtual void AssignToRecordFieldNode::accept(AstVisitor& visitor) const override {
  visitor.visit(*this);
}

[[nodiscard]] virtual std::unique_ptr<AstNode> AssignToRecordFieldNode::clone() const override {
  IdentifierNode* newRecord = dynamic_cast<IdentifierNode*>(record_->clone().release());
  IdentifierNode* newField = dynamic_cast<IdentifierNode*>(field_->clone().release());
  ExpressionNode* newExpression = dynamic_cast<ExpressionNode*>(expression_->clone().release());

  return std::make_unique<AssignToRecordFieldNode>(newRecord, newField, newExpression);
}

void AssignToRecordFieldNode::print(std::ostream& out, int tab) const override {
  if (getLabel().has_value()) {
    out << std::string(tab, ' ') << "AssignToRecordFieldNode with label: " << getLabel().value() << "\n";
  }
  else {
    out << std::string(tab, ' ') << "AssignToRecordFieldNode\n";
  }

  record_->print(out, tab + 2);
  field_->print(out, tab + 2);
  expression_->print(out, tab + 2);
}
}  // namespace ast
