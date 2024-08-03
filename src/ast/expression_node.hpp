#ifndef AST_EXPRESSION_NODE_HPP
#define AST_EXPRESSION_NODE_HPP

#include <memory>

#include "ast_node.hpp"

namespace ast {
class ExpressionNode : public AstNode {
 public:
  enum Operation {
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    MODULUS,
    NEGATION,
    AND,
    OR,
    NOT,
    EQUAL,
    NOT_EQUAL,
    LESS,
    LESS_EQUAL,
    GREATER,
    GREATER_EQUAL,
    SPECIAL,
  };

  ExpressionNode() : AstNode{Type::EXPRESSION} {}
  ExpressionNode(Operation operation) : AstNode{Type::EXPRESSION}, operation_{operation} {}
  ExpressionNode(ExpressionNode* left, Operation operation) : AstNode{Type::EXPRESSION}, operation_{operation}, left_{left} {}
  ExpressionNode(ExpressionNode* left, ExpressionNode* right, Operation operation)
      : AstNode{Type::EXPRESSION}, operation_{operation}, left_{left}, right_{right} {}

  ExpressionNode(const ExpressionNode&) = delete;
  ExpressionNode(ExpressionNode&&) = default;

  ExpressionNode& operator=(const ExpressionNode&) = delete;
  ExpressionNode& operator=(ExpressionNode&&) = default;

  ~ExpressionNode() override = default;

  Operation getOperation() const { return operation_; }
  const std::unique_ptr<ExpressionNode>& getLeft() const { return left_; }
  const std::unique_ptr<ExpressionNode>& getRight() const { return right_; }

  void setOperation(Operation operation) { operation_ = operation; }
  void setLeft(std::unique_ptr<ExpressionNode> left) { left_ = std::move(left); }
  void setRight(std::unique_ptr<ExpressionNode> right) { right_ = std::move(right); }

  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override {
    ExpressionNode* newLeft = left_ == nullptr ? nullptr : dynamic_cast<ExpressionNode*>(left_->clone().release());
    ExpressionNode* newRight = right_ == nullptr ? nullptr : dynamic_cast<ExpressionNode*>(right_->clone().release());

    return std::make_unique<ExpressionNode>(newLeft, newRight, operation_);
  }

  virtual void print(std::ostream& out, int tab) const override {
    switch (operation_) {
      case ADDITION:
        out << std::string(tab, ' ') << "ExpressionNode: ADDITION\n";
        break;
      case SUBTRACTION:
        out << std::string(tab, ' ') << "ExpressionNode: SUBTRACTION\n";
        break;
      case MULTIPLICATION:
        out << std::string(tab, ' ') << "ExpressionNode: MULTIPLICATION\n";
        break;
      case DIVISION:
        out << std::string(tab, ' ') << "ExpressionNode: DIVISION\n";
        break;
      case MODULUS:
        out << std::string(tab, ' ') << "ExpressionNode: MODULUS\n";
        break;
      case NEGATION:
        out << std::string(tab, ' ') << "ExpressionNode: NEGATION\n";
        break;
      case AND:
        out << std::string(tab, ' ') << "ExpressionNode: AND\n";
        break;
      case OR:
        out << std::string(tab, ' ') << "ExpressionNode: OR\n";
        break;
      case NOT:
        out << std::string(tab, ' ') << "ExpressionNode: NOT\n";
        break;
      case EQUAL:
        out << std::string(tab, ' ') << "ExpressionNode: EQUAL\n";
        break;
      case NOT_EQUAL:
        out << std::string(tab, ' ') << "ExpressionNode: NOT_EQUAL\n";
        break;
      case LESS:
        out << std::string(tab, ' ') << "ExpressionNode: LESS\n";
        break;
      case LESS_EQUAL:
        out << std::string(tab, ' ') << "ExpressionNode: LESS_EQUAL\n";
        break;
      case GREATER:
        out << std::string(tab, ' ') << "ExpressionNode: GREATER\n";
        break;
      case GREATER_EQUAL:
        out << std::string(tab, ' ') << "ExpressionNode: GREATER_EQUAL\n";
        break;
      case SPECIAL:
        out << std::string(tab, ' ') << "ExpressionNode: SPECIAL\n";
        break;
    }

    if (left_ != nullptr) {
      left_->print(out, tab + 2);
    }
    if (right_ != nullptr) {
      right_->print(out, tab + 2);
    }
  }

 private:
  Operation operation_;
  std::unique_ptr<ExpressionNode> left_;
  std::unique_ptr<ExpressionNode> right_;
};

class SpecialExpressionNode : public ExpressionNode {
 public:
  enum FunctionName { VARIABLE, CALL, ARRAY_ACCESS, CONST, PARENTHESIS, RECORD_ACCESS, ABS, CHR, ORD, ODD, PRED, SUCC };

  SpecialExpressionNode() : ExpressionNode{Operation::SPECIAL} {}
  SpecialExpressionNode(AstNode* argument1, FunctionName functionName)
      : ExpressionNode{Operation::SPECIAL}, functionName_{functionName}, argument1_{argument1} {}
  SpecialExpressionNode(AstNode* argument1, AstNode* argument2, FunctionName functionName)
      : ExpressionNode{Operation::SPECIAL}, functionName_{functionName}, argument1_{argument1}, argument2_{argument2} {}

  SpecialExpressionNode(const SpecialExpressionNode&) = delete;
  SpecialExpressionNode(SpecialExpressionNode&&) = default;

  SpecialExpressionNode& operator=(const SpecialExpressionNode&) = delete;
  SpecialExpressionNode& operator=(SpecialExpressionNode&&) = default;

  ~SpecialExpressionNode() override = default;

  FunctionName getFunctionName() const { return functionName_; }
  [[nodiscard]] const std::unique_ptr<AstNode>& getArgument1() const { return argument1_; }
  [[nodiscard]] const std::unique_ptr<AstNode>& getArgument2() const { return argument2_; }

  void setArgument1(std::unique_ptr<AstNode> argument1) { argument1_ = std::move(argument1); }
  void setArgument2(std::unique_ptr<AstNode> argument2) { argument2_ = std::move(argument2); }

  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override {
    AstNode* newArgument1 = argument1_ == nullptr ? nullptr : argument1_->clone().release();
    AstNode* newArgument2 = argument2_ == nullptr ? nullptr : argument2_->clone().release();

    return std::make_unique<SpecialExpressionNode>(newArgument1, newArgument2, functionName_);
  }

  virtual void print(std::ostream& out, int tab) const override {
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
    }

    if (argument1_ != nullptr) {
      argument1_->print(out, tab + 2);
    }
    if (argument2_ != nullptr) {
      argument2_->print(out, tab + 2);
    }
  }

 private:
  FunctionName functionName_;
  std::unique_ptr<AstNode> argument1_;
  std::unique_ptr<AstNode> argument2_;
};
}  // namespace ast

#endif  // AST_EXPRESSION_NODE_HPP
