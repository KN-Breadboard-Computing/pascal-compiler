#include "expression_node.hpp"

namespace ast {
// MathExpressionNode
void MathExpressionNode::accept(AstVisitor* visitor) const {
  visitor->visit(this);
}

[[nodiscard]] std::unique_ptr<AstNode> MathExpressionNode::clone() const {
  ExpressionNode* newLeft = left_ == nullptr ? nullptr : dynamic_cast<ExpressionNode*>(left_->clone().release());
  ExpressionNode* newRight = right_ == nullptr ? nullptr : dynamic_cast<ExpressionNode*>(right_->clone().release());

  return std::make_unique<MathExpressionNode>(newLeft, newRight, functionName_, getInferredType());
}

void MathExpressionNode::print(std::ostream& out, int tab) const {
  switch (functionName_) {
    case ADDITION:
      out << std::string(tab, ' ') << "MathExpressionNode: ADDITION\n";
      break;
    case SUBTRACTION:
      out << std::string(tab, ' ') << "MathExpressionNode: SUBTRACTION\n";
      break;
    case MULTIPLICATION:
      out << std::string(tab, ' ') << "MathExpressionNode: MULTIPLICATION\n";
      break;
    case DIVISION:
      out << std::string(tab, ' ') << "MathExpressionNode: DIVISION\n";
      break;
    case MODULUS:
      out << std::string(tab, ' ') << "MathExpressionNode: MODULUS\n";
      break;
    case NEGATION:
      out << std::string(tab, ' ') << "MathExpressionNode: NEGATION\n";
      break;
    case AND:
      out << std::string(tab, ' ') << "MathExpressionNode: AND\n";
      break;
    case OR:
      out << std::string(tab, ' ') << "MathExpressionNode: OR\n";
      break;
    case NOT:
      out << std::string(tab, ' ') << "MathExpressionNode: NOT\n";
      break;
    case EQUAL:
      out << std::string(tab, ' ') << "MathExpressionNode: EQUAL\n";
      break;
    case NOT_EQUAL:
      out << std::string(tab, ' ') << "MathExpressionNode: NOT_EQUAL\n";
      break;
    case LESS:
      out << std::string(tab, ' ') << "MathExpressionNode: LESS\n";
      break;
    case LESS_EQUAL:
      out << std::string(tab, ' ') << "MathExpressionNode: LESS_EQUAL\n";
      break;
    case GREATER:
      out << std::string(tab, ' ') << "MathExpressionNode: GREATER\n";
      break;
    case GREATER_EQUAL:
      out << std::string(tab, ' ') << "MathExpressionNode: GREATER_EQUAL\n";
      break;
  }

  if (left_ != nullptr) {
    left_->print(out, tab + 2);
  }
  if (right_ != nullptr) {
    right_->print(out, tab + 2);
  }
}

// SpecialExpressionNode
void SpecialExpressionNode::accept(AstVisitor* visitor) const {
  visitor->visit(this);
}

[[nodiscard]] std::unique_ptr<AstNode> SpecialExpressionNode::clone() const {
  SpecialExpressionNode* newArgument1 = argument1_ == nullptr ? nullptr : dynamic_cast<SpecialExpressionNode*>(argument1_->clone().release());
  SpecialExpressionNode* newArgument2 = argument2_ == nullptr ? nullptr : dynamic_cast<SpecialExpressionNode*>(argument2_->clone().release());

  return std::make_unique<SpecialExpressionNode>(newArgument1, newArgument2, functionName_, getInferredType());
}

void SpecialExpressionNode::print(std::ostream& out, int tab) const {
  switch (functionName_) {
    case VARIABLE:
      out << std::string(tab, ' ') << "SpecialExpressionNode: VARIABLE\n";
      break;
    case CALL:
      out << std::string(tab, ' ') << "SpecialExpressionNode: CALL\n";
      break;
    case ARRAY_ACCESS:
      out << std::string(tab, ' ') << "SpecialExpressionNode: ARRAY_ACCESS\n";
      break;
    case CONST:
      out << std::string(tab, ' ') << "SpecialExpressionNode: CONST\n";
      break;
    case PARENTHESIS:
      out << std::string(tab, ' ') << "SpecialExpressionNode: PARENTHESIS\n";
      break;
    case RECORD_ACCESS:
      out << std::string(tab, ' ') << "SpecialExpressionNode: RECORD_ACCESS\n";
      break;
    case ENUM_ELEMENT:
      out << std::string(tab, ' ') << "SpecialExpressionNode: ENUM ELEMENT\n";
      break;
    case ABS:
      out << std::string(tab, ' ') << "SpecialExpressionNode: ABS\n";
      break;
    case CHR:
      out << std::string(tab, ' ') << "SpecialExpressionNode: CHR\n";
      break;
    case ORD:
      out << std::string(tab, ' ') << "SpecialExpressionNode: ORD\n";
      break;
    case ODD:
      out << std::string(tab, ' ') << "SpecialExpressionNode: ODD\n";
      break;
    case PRED:
      out << std::string(tab, ' ') << "SpecialExpressionNode: PRED\n";
      break;
    case SUCC:
      out << std::string(tab, ' ') << "SpecialExpressionNode: SUCC\n";
      break;
    case TOINT:
      out << std::string(tab, ' ') << "SpecialExpressionNode: TOINT\n";
      break;
    case TOCHAR:
      out << std::string(tab, ' ') << "SpecialExpressionNode: TOCHAR\n";
      break;
    case TOBOOL:
      out << std::string(tab, ' ') << "SpecialExpressionNode: TOBOOL\n";
      break;
  }

  if (argument1_ != nullptr) {
    argument1_->print(out, tab + 2);
  }
  if (argument2_ != nullptr) {
    argument2_->print(out, tab + 2);
  }
}
}  // namespace ast
