#include "assign_node.hpp"

namespace ast {
void AssignNode::accept(const std::unique_ptr<AstVisitor> &visitor) const {
  visitor->visit(*this);
}

[[nodiscard]] std::unique_ptr<AstNode> AssignNode::clone() const {
  ExpressionNode *newLhs = dynamic_cast<ExpressionNode *>(lhs_->clone().release());
  ExpressionNode *newRhs = dynamic_cast<ExpressionNode *>(rhs_->clone().release());

  return std::make_unique<AssignNode>(newLhs, newRhs);
}

void AssignNode::print(std::ostream &out, int tab) const {
  if (getLabel().has_value()) {
	out << std::string(tab, ' ') << "AssignNode with label: " << getLabel().value() << "\n";
  } else {
	out << std::string(tab, ' ') << "AssignNode\n";
  }

  lhs_->print(out, tab + 2);
  rhs_->print(out, tab + 2);
}

// AssignToVariableNode
//void AssignToVariableNode::accept(const std::unique_ptr<AstVisitor>& visitor) const {
//  visitor->visit(*this);
//}
//
//[[nodiscard]] std::unique_ptr<AstNode> AssignToVariableNode::clone() const {
//  IdentifierNode* newVariable = dynamic_cast<IdentifierNode*>(variable_->clone().release());
//  ExpressionNode* newExpression = dynamic_cast<ExpressionNode*>(expression_->clone().release());
//
//  return std::make_unique<AssignToVariableNode>(newVariable, newExpression);
//}
//
//void AssignToVariableNode::print(std::ostream& out, int tab) const {
//  if (getLabel().has_value()) {
//    out << std::string(tab, ' ') << "AssignToVariableNode with label: " << getLabel().value() << "\n";
//  }
//  else {
//    out << std::string(tab, ' ') << "AssignToVariableNode\n";
//  }
//
//  variable_->print(out, tab + 2);
//  expression_->print(out, tab + 2);
//}
//
//
// AssignToArrayNode
//void AssignToArrayNode::accept(const std::unique_ptr<AstVisitor>& visitor) const {
//  visitor->visit(*this);
//}
//
//[[nodiscard]] std::unique_ptr<AstNode> AssignToArrayNode::clone() const {
//  IdentifierNode* newArray = dynamic_cast<IdentifierNode*>(array_->clone().release());
//  ExpressionNode* newIndex = dynamic_cast<ExpressionNode*>(index_->clone().release());
//  ExpressionNode* newExpression = dynamic_cast<ExpressionNode*>(expression_->clone().release());
//
//  return std::make_unique<AssignToArrayNode>(newArray, newIndex, newExpression);
//}
//
//void AssignToArrayNode::print(std::ostream& out, int tab) const {
//  if (getLabel().has_value()) {
//    out << std::string(tab, ' ') << "AssignToArrayNode with label: " << getLabel().value() << "\n";
//  }
//  else {
//    out << std::string(tab, ' ') << "AssignToArrayNode\n";
//  }
//
//  array_->print(out, tab + 2);
//  index_->print(out, tab + 2);
//  expression_->print(out, tab + 2);
//}
//
//
// AssignToRecordFieldNode
//void AssignToRecordFieldNode::accept(const std::unique_ptr<AstVisitor>& visitor) const {
//  visitor->visit(*this);
//}
//
//[[nodiscard]] std::unique_ptr<AstNode> AssignToRecordFieldNode::clone() const {
//  IdentifierNode* newRecord = dynamic_cast<IdentifierNode*>(record_->clone().release());
//  IdentifierNode* newField = dynamic_cast<IdentifierNode*>(field_->clone().release());
//  ExpressionNode* newExpression = dynamic_cast<ExpressionNode*>(expression_->clone().release());
//
//  return std::make_unique<AssignToRecordFieldNode>(newRecord, newField, newExpression);
//}
//
//void AssignToRecordFieldNode::print(std::ostream& out, int tab) const {
//  if (getLabel().has_value()) {
//    out << std::string(tab, ' ') << "AssignToRecordFieldNode with label: " << getLabel().value() << "\n";
//  }
//  else {
//    out << std::string(tab, ' ') << "AssignToRecordFieldNode\n";
//  }
//
//  record_->print(out, tab + 2);
//  field_->print(out, tab + 2);
//  expression_->print(out, tab + 2);
//}
}  // namespace ast
