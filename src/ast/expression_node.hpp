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
    if (right_ == nullptr) {
      out << std::string(tab, ' ') << "ExpressionNode: " << operation_ << '\n';
      left_->print(out, tab + 2);
    }
    else {
      out << std::string(tab, ' ') << "ExpressionNode: " << operation_ << '\n';
      left_->print(out, tab + 2);
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
    if (argument2_ == nullptr) {
      out << std::string(tab, ' ') << "SpecialExpressionNode: " << functionName_ << '\n';
      argument1_->print(out, tab + 2);
    }
    else {
      out << std::string(tab, ' ') << "SpecialExpressionNode: " << functionName_ << '\n';
      argument1_->print(out, tab + 2);
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
