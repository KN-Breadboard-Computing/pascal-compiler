#ifndef AST_EXPRESSION_NODE_HPP
#define AST_EXPRESSION_NODE_HPP

#include <memory>

#include "ast_node.hpp"

namespace ast {
class ExpressionNode : public AstNode {
 public:
  enum Operation { MATH, SPECIAL };

  ExpressionNode() : AstNode{Type::EXPRESSION} {}
  ExpressionNode(Operation operation, const std::string& inferredType) : AstNode{Type::EXPRESSION}, operation_{operation}, inferredType_{inferredType} {}

  ExpressionNode(const ExpressionNode&) = delete;
  ExpressionNode(ExpressionNode&&) = default;

  ExpressionNode& operator=(const ExpressionNode&) = delete;
  ExpressionNode& operator=(ExpressionNode&&) = default;

  ~ExpressionNode() override = default;

  Operation getOperation() const { return operation_; }
  const std::string& getInferredType() const { return inferredType_; }

  void setOperation(Operation operation) { operation_ = operation; }
  void setInferredType(const std::string& inferredType) { inferredType_ = inferredType; }

 private:
  Operation operation_;
  std::string inferredType_;
};

class MathExpressionNode : public ExpressionNode {
 public:
  enum FunctionName { ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION, MODULUS, NEGATION, AND, OR, NOT, EQUAL, NOT_EQUAL, LESS, LESS_EQUAL, GREATER, GREATER_EQUAL };

  MathExpressionNode() : ExpressionNode{Operation::MATH, ""} {}
  MathExpressionNode(ExpressionNode* left, FunctionName functionName, const std::string& inferredType) : ExpressionNode{Operation::MATH, inferredType}, functionName_{functionName}, left_{left}, right_{nullptr} {}
  MathExpressionNode(ExpressionNode* left, ExpressionNode* right, FunctionName functionName, const std::string& inferredType) : ExpressionNode{Operation::MATH, inferredType}, functionName_{functionName}, left_{left}, right_{right} {}

  FunctionName getFunctionName() const { return functionName_; }
  const std::unique_ptr<ExpressionNode>& getLeft() const { return left_; }
  const std::unique_ptr<ExpressionNode>& getRight() const { return right_; }

  void setFunctionName(FunctionName functionName) { functionName_ = functionName; }
  void setLeft(std::unique_ptr<ExpressionNode> left) { left_ = std::move(left); }
  void setRight(std::unique_ptr<ExpressionNode> right) { right_ = std::move(right); }

  virtual void accept(AstVisitor* visitor) const override;
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  virtual void print(std::ostream& out, int tab) const override;

 private:
  FunctionName functionName_;
  std::unique_ptr<ExpressionNode> left_;
  std::unique_ptr<ExpressionNode> right_;
};

class SpecialExpressionNode : public ExpressionNode {
 public:
  enum FunctionName { VARIABLE, CALL, ARRAY_ACCESS, CONST, PARENTHESIS, RECORD_ACCESS, ENUM_ELEMENT, ABS, CHR, ORD, ODD, PRED, SUCC, TOINT, TOCHAR, TOBOOL };

  SpecialExpressionNode() : ExpressionNode{Operation::SPECIAL, ""} {}
  SpecialExpressionNode(AstNode* argument1, FunctionName functionName, const std::string& inferredType) : ExpressionNode{Operation::SPECIAL, inferredType}, functionName_{functionName}, argument1_{argument1} {}
  SpecialExpressionNode(AstNode* argument1, AstNode* argument2, FunctionName functionName, const std::string& inferredType)
      : ExpressionNode{Operation::SPECIAL, inferredType}, functionName_{functionName}, argument1_{argument1}, argument2_{argument2} {}

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

  virtual void accept(AstVisitor* visitor) const override;
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  virtual void print(std::ostream& out, int tab) const override;

 private:
  FunctionName functionName_;
  std::unique_ptr<AstNode> argument1_;
  std::unique_ptr<AstNode> argument2_;
};
}  // namespace ast

#endif  // AST_EXPRESSION_NODE_HPP
