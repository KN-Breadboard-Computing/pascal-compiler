#include "bb_cfg_generator.hpp"
#include "../context/context.hpp"

#include <queue>
#include <stdexcept>

namespace bblocks {
Context* ctx = Context::getInstance();

void BbCfgGenerator::visit(const ast::ArgumentsListNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::ArrayTypeNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::AssignNode* node) {
  node->getRhs()->accept(this);
  generateVariableMove(node->getLhs().get(), ctx->getLastTempVariable());
}

void BbCfgGenerator::visit(const ast::BuiltinCallNode* node) {
  const ast::BuiltinCallNode::FunctionName funName = node->getFunctionName();
  switch (funName) {
    case ast::BuiltinCallNode::READ: {
      currentBasicBlock_.addInstruction(std::make_unique<BBCall>("read", std::vector<std::string>{ctx->generateTempVariable()}));
      generateVariableMove(node->getArguments()->getArguments().front(), ctx->getLastTempVariable());
      break;
    }
    case ast::BuiltinCallNode::READLN: {
      std::make_unique<BBCall>("readln", std::vector<std::string>{});
      break;
    }
    case ast::BuiltinCallNode::WRITE:
    case ast::BuiltinCallNode::WRITELN: {
      std::vector<std::string> args{};
      for (auto* arg : node->getArguments()->getArguments()) {
        if (arg->getInferredType() == "string") {
          ast::StringConstantNode* constant = dynamic_cast<ast::StringConstantNode*>(arg);
          args.emplace_back(constant->getValue());
        }
        else {
          arg->accept(this);
          args.emplace_back(ctx->getLastTempVariable());
        }
      }
      currentBasicBlock_.addInstruction(
          std::make_unique<BBCall>(funName == ast::BuiltinCallNode::WRITE ? "write" : "writeln", args));
      break;
    }
    case ast::BuiltinCallNode::MEMORY_READ:
    case ast::BuiltinCallNode::STACK_READ: {
      node->getArguments()->getArguments().at(0)->accept(this);
      const std::string high = ctx->getLastTempVariable();
      node->getArguments()->getArguments().at(1)->accept(this);
      const std::string low = ctx->getLastTempVariable();

      currentBasicBlock_.addInstruction(
          std::make_unique<BBCall>(funName == ast::BuiltinCallNode::MEMORY_READ ? "mload" : "sload",
                                   std::vector<std::string>{high, low, ctx->generateTempVariable()}));
      generateVariableMove(node->getArguments()->getArguments().at(2), ctx->getLastTempVariable());
    }
    case ast::BuiltinCallNode::MEMORY_WRITE:
    case ast::BuiltinCallNode::STACK_WRITE: {
      node->getArguments()->getArguments().at(0)->accept(this);
      const std::string high = ctx->getLastTempVariable();
      node->getArguments()->getArguments().at(1)->accept(this);
      const std::string low = ctx->getLastTempVariable();
      node->getArguments()->getArguments().at(2)->accept(this);
      const std::string valVar = ctx->getLastTempVariable();

      currentBasicBlock_.addInstruction(std::make_unique<BBCall>(
          funName == ast::BuiltinCallNode::MEMORY_READ ? "mstore" : "sstore", std::vector<std::string>{high, low, valVar}));
    }
  }
}

void BbCfgGenerator::visit(const ast::UserDefineCallNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::CaseNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::CompoundStatementNode* node) {
  for (auto* const statement : *node->getStatements()) {
    statement->accept(this);
  }
}

void BbCfgGenerator::visit(const ast::ConstantNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::MathExpressionNode* node) {
  std::string leftOperand;
  if (node->getLeft() != nullptr) {
    node->getLeft()->accept(this);
    leftOperand = ctx->getLastTempVariable();
  }

  std::string rightOperand;
  if (node->getRight() != nullptr) {
    node->getRight()->accept(this);
    rightOperand = ctx->getLastTempVariable();
  }

  switch (node->getFunctionName()) {
    case ast::MathExpressionNode::ADDITION: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::ADD,
          BBBinaryOperationVVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::SUBTRACTION: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::SUB,
          BBBinaryOperationVVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::MULTIPLICATION: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::MUL,
          BBBinaryOperationVVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::DIVISION: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::DIV,
          BBBinaryOperationVVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::MODULUS: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::MOD,
          BBBinaryOperationVVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::NEGATION: {
      currentBasicBlock_.addInstruction(std::make_unique<BBUnaryOperationVV>(leftOperand, ctx->generateTempVariable(),
                                                                             BBUnaryOperationVV::OperationType::NEG,
                                                                             BBUnaryOperationVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::AND: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::AND,
          BBBinaryOperationVVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::OR: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::OR,
          BBBinaryOperationVVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::NOT: {
      currentBasicBlock_.addInstruction(std::make_unique<BBUnaryOperationVV>(leftOperand, ctx->generateTempVariable(),
                                                                             BBUnaryOperationVV::OperationType::NOT,
                                                                             BBUnaryOperationVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::EQUAL: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::EQ,
          BBBinaryOperationVVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::NOT_EQUAL: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::NE,
          BBBinaryOperationVVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::LESS: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::LT,
          BBBinaryOperationVVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::LESS_EQUAL: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::LE,
          BBBinaryOperationVVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::GREATER: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::GT,
          BBBinaryOperationVVV::DestinationType::VARIABLE));
      break;
    }
    case ast::MathExpressionNode::GREATER_EQUAL: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::GE,
          BBBinaryOperationVVV::DestinationType::VARIABLE));
      break;
    }
  }
}

void BbCfgGenerator::visit(const ast::SpecialExpressionNode* node) {
  std::string argument1;
  if (node->getArgument1() != nullptr) {
    node->getArgument1()->accept(this);
    argument1 = ctx->getLastTempVariable();
  }

  std::string argument2;
  if (node->getArgument2() != nullptr) {
    node->getArgument2()->accept(this);
    argument2 = ctx->getLastTempVariable();
  }

  switch (node->getFunctionName()) {
    case ast::SpecialExpressionNode::VARIABLE: {
      ast::IdentifierNode* variable = dynamic_cast<ast::IdentifierNode*>(node->getArgument1().get());
      currentBasicBlock_.addInstruction(std::make_unique<BBMoveVV>(
          variable->getName(), ctx->generateTempVariable(), BBMoveVV::SourceType::VARIABLE, BBMoveVV::DestinationType::VARIABLE));
      break;
    }
    case ast::SpecialExpressionNode::CALL: {
      ast::IdentifierNode* function = dynamic_cast<ast::IdentifierNode*>(node->getArgument1().get());
      ast::ArgumentsListNode* arguments = dynamic_cast<ast::ArgumentsListNode*>(node->getArgument2().get());

      std::vector<std::string> args{};
      for (auto* arg : arguments->getArguments()) {
        if (arg->getInferredType() == "string") {
          ast::StringConstantNode* constant = dynamic_cast<ast::StringConstantNode*>(arg);
          args.emplace_back(constant->getValue());
        }
        else {
          arg->accept(this);
          args.emplace_back(ctx->getLastTempVariable());
        }
      }
      currentBasicBlock_.addInstruction(std::make_unique<BBCall>(function->getName(), args));
      break;
    }
    case ast::SpecialExpressionNode::ARRAY_ACCESS: {
      break;
    }
    case ast::SpecialExpressionNode::CONST: {
      ast::ConstantNode* constant = dynamic_cast<ast::ConstantNode*>(node->getArgument1().get());
      switch (constant->getConstantType()) {
        case ast::ConstantNode::UNSPECIFIED:
          throw std::runtime_error("Type error");
        case ast::ConstantNode::INTEGER: {
          ast::IntegerConstantNode* integerConstant = dynamic_cast<ast::IntegerConstantNode*>(constant);
          currentBasicBlock_.addInstruction(std::make_unique<BBMoveNV>(integerConstant->getValue(), ctx->generateTempVariable(),
                                                                       BBMoveNV::SourceType::NUMERIC,
                                                                       BBMoveNV::DestinationType::VARIABLE));
          break;
        }
        case ast::ConstantNode::CHAR: {
          ast::CharConstantNode* charConstant = dynamic_cast<ast::CharConstantNode*>(constant);
          currentBasicBlock_.addInstruction(std::make_unique<BBMoveNV>(charConstant->getValue(), ctx->generateTempVariable(),
                                                                       BBMoveNV::SourceType::NUMERIC,
                                                                       BBMoveNV::DestinationType::VARIABLE));
          break;
        }
        case ast::ConstantNode::BOOLEAN: {
          ast::BooleanConstantNode* boolConstant = dynamic_cast<ast::BooleanConstantNode*>(constant);
          currentBasicBlock_.addInstruction(std::make_unique<BBMoveNV>(boolConstant->getValue(), ctx->generateTempVariable(),
                                                                       BBMoveNV::SourceType::NUMERIC,
                                                                       BBMoveNV::DestinationType::VARIABLE));
          break;
        }
        case ast::ConstantNode::STRING:
          break;
      }
      break;
    }
    case ast::SpecialExpressionNode::RECORD_ACCESS:
      break;
    case ast::SpecialExpressionNode::ENUM_ELEMENT:
      break;
    case ast::SpecialExpressionNode::ABS: {
      node->getArgument1()->accept(this);
      currentBasicBlock_.addInstruction(std::make_unique<BBUnaryOperationVV>(
          ctx->getLastTempVariable(), ctx->generateTempVariable(), BBUnaryOperationVV::OperationType::SHL,
          BBUnaryOperationVV::DestinationType::VARIABLE));
      currentBasicBlock_.addInstruction(std::make_unique<BBUnaryOperationVV>(
          ctx->getLastTempVariable(), ctx->generateTempVariable(), BBUnaryOperationVV::OperationType::SHR,
          BBUnaryOperationVV::DestinationType::VARIABLE));
    }
    case ast::SpecialExpressionNode::ODD: {
      break;
    }
    case ast::SpecialExpressionNode::PRED: {
      node->getArgument1()->accept(this);
      currentBasicBlock_.addInstruction(std::make_unique<BBUnaryOperationVV>(
          ctx->getLastTempVariable(), ctx->generateTempVariable(), BBUnaryOperationVV::OperationType::DEC,
          BBUnaryOperationVV::DestinationType::VARIABLE));
      break;
    }
    case ast::SpecialExpressionNode::SUCC: {
      node->getArgument1()->accept(this);
      currentBasicBlock_.addInstruction(std::make_unique<BBUnaryOperationVV>(
          ctx->getLastTempVariable(), ctx->generateTempVariable(), BBUnaryOperationVV::OperationType::INC,
          BBUnaryOperationVV::DestinationType::VARIABLE));
      break;
    }
    case ast::SpecialExpressionNode::PARENTHESIS:
    case ast::SpecialExpressionNode::CHR:
    case ast::SpecialExpressionNode::ORD:
    case ast::SpecialExpressionNode::TOINT:
    case ast::SpecialExpressionNode::TOCHAR:
    case ast::SpecialExpressionNode::TOBOOL: {
      node->getArgument1()->accept(this);
      break;
    }
  }
}

void BbCfgGenerator::visit(const ast::BreakNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::ContinueNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::ForNode* node) {
  const std::string statementsBeforeFor = ctx->generateBasicBlockLabel();
  saveBasicBlock(statementsBeforeFor, true, true);

  const std::string firstBeginStatement = ctx->generateBasicBlockLabel();
  const std::string lastBeginStatement = ctx->generateBasicBlockLabel();
  newControlFlowGraph(firstBeginStatement);
  node->getStart()->accept(this);
  const std::string beginVariable = ctx->getLastTempVariable();
  currentBasicBlock_.addInstruction(std::make_unique<BBMoveVV>(
      beginVariable, node->getIterator()->getName(), BBMoveVV::SourceType::VARIABLE, BBMoveVV::DestinationType::VARIABLE));
  saveBasicBlock(lastBeginStatement, true, true);
  const BBControlFlowGraph begin{std::move(controlFlowGraphs_.top())};
  controlFlowGraphs_.pop();
  controlFlowGraphs_.top().merge(begin);
  controlFlowGraphs_.top().setExitLabel(lastBeginStatement);

  const std::string firstEndStatement = ctx->generateBasicBlockLabel();
  const std::string lastEndStatement = ctx->generateBasicBlockLabel();
  newControlFlowGraph(firstEndStatement);
  node->getEnd()->accept(this);
  const std::string endVariable = ctx->getLastTempVariable();
  saveBasicBlock(lastEndStatement, true, true);
  const BBControlFlowGraph end{std::move(controlFlowGraphs_.top())};
  controlFlowGraphs_.pop();
  controlFlowGraphs_.top().merge(end);
  controlFlowGraphs_.top().setExitLabel(lastEndStatement);

  currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
      node->getIterator()->getName(), endVariable, ctx->generateTempVariable(), BBBinaryOperationVVV::OperationType::SUB,
      BBBinaryOperationVVV::DestinationType::VARIABLE));
  const std::string conditionVariable = ctx->getLastTempVariable();
  const std::string conditionStatement = ctx->generateBasicBlockLabel();
  saveBasicBlock(conditionStatement, true, true);

  const std::string firstBodyStatement = ctx->generateBasicBlockLabel();
  const std::string lastBodyStatement = ctx->generateBasicBlockLabel();
  newControlFlowGraph(firstBodyStatement);
  node->getStatements()->accept(this);
  currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVNV>(
      node->getIterator()->getName(), 1, node->getIterator()->getName(),
      node->getDirection() == ast::ForNode::INCREMENT ? BBBinaryOperationVNV::OperationType::ADD
                                                      : BBBinaryOperationVNV::OperationType::SUB,
      BBBinaryOperationVNV::DestinationType::VARIABLE));
  saveBasicBlock(lastBodyStatement, true, true);
  const BBControlFlowGraph body{std::move(controlFlowGraphs_.top())};
  controlFlowGraphs_.pop();
  controlFlowGraphs_.top().merge(body);

  controlFlowGraphs_.top().addBlocksLink(lastBodyStatement, conditionStatement);

  const std::string exitLabel = ctx->generateBasicBlockLabel();
  saveBasicBlock(exitLabel, true, true);

  controlFlowGraphs_.top()
      .getBasicBlock(conditionStatement)
      .addInstruction(std::make_unique<BBBranchV>(conditionVariable,
                                                  node->getDirection() == ast::ForNode::Direction::INCREMENT
                                                      ? BBBranchV::Condition::POSITIVE
                                                      : BBBranchV::Condition::NEGATIVE,
                                                  firstBodyStatement, exitLabel));
}

void BbCfgGenerator::visit(const ast::GotoNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::IdentifierNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::IfNode* node) {
  const std::string statementsBeforeIf = ctx->generateBasicBlockLabel();
  saveBasicBlock(statementsBeforeIf, true, true);

  const std::string firstConditionStatement = ctx->generateBasicBlockLabel();
  const std::string lastConditionStatement = ctx->generateBasicBlockLabel();
  newControlFlowGraph(firstConditionStatement);
  node->getCondition()->accept(this);
  const std::string conditionVariable = ctx->getLastTempVariable();
  saveBasicBlock(lastConditionStatement, true, true);
  const BBControlFlowGraph condition{std::move(controlFlowGraphs_.top())};
  controlFlowGraphs_.pop();
  controlFlowGraphs_.top().merge(condition);
  controlFlowGraphs_.top().setExitLabel(lastConditionStatement);

  const std::string firstTrueStatement = ctx->generateBasicBlockLabel();
  const std::string lastTrueStatement = ctx->generateBasicBlockLabel();
  newControlFlowGraph(firstTrueStatement);
  node->getThenStatement()->accept(this);
  saveBasicBlock(lastTrueStatement, true, false);
  const BBControlFlowGraph trueStatement{std::move(controlFlowGraphs_.top())};
  controlFlowGraphs_.pop();
  controlFlowGraphs_.top().merge(trueStatement, lastConditionStatement);
  controlFlowGraphs_.top().setExitLabel(lastTrueStatement);

  std::string firstFalseStatement;
  std::string lastFalseStatement;
  if (node->getElseStatement() != nullptr) {
    firstFalseStatement = ctx->generateBasicBlockLabel();
    lastFalseStatement = ctx->generateBasicBlockLabel();
    newControlFlowGraph(firstFalseStatement);
    node->getElseStatement()->accept(this);
    saveBasicBlock(lastFalseStatement, true, false);
    const BBControlFlowGraph falseStatement{std::move(controlFlowGraphs_.top())};
    controlFlowGraphs_.pop();
    controlFlowGraphs_.top().merge(falseStatement, lastConditionStatement);
    controlFlowGraphs_.top().setExitLabel(lastFalseStatement);
  }

  const std::string exitLabel = ctx->generateBasicBlockLabel();
  saveBasicBlock(exitLabel, false, true);

  controlFlowGraphs_.top().addBlocksLink(lastTrueStatement, exitLabel);

  if (node->getElseStatement() != nullptr) {
    controlFlowGraphs_.top().addBlocksLink(lastFalseStatement, exitLabel);
    controlFlowGraphs_.top()
        .getBasicBlock(lastConditionStatement)
        .addInstruction(std::make_unique<BBBranchV>(conditionVariable, BBBranchV::Condition::NONZERO, firstTrueStatement,
                                                    firstFalseStatement));
  }
  else {
    controlFlowGraphs_.top().addBlocksLink(lastConditionStatement, exitLabel);
    controlFlowGraphs_.top()
        .getBasicBlock(lastConditionStatement)
        .addInstruction(
            std::make_unique<BBBranchV>(conditionVariable, BBBranchV::Condition::NONZERO, firstTrueStatement, exitLabel));
  }
}

void BbCfgGenerator::visit(const ast::ParamsGroupNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::ParamsNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::ProgramNode* node) {
  currentScope_ += ".program";
  node->getRoutine()->accept(this);
}

void BbCfgGenerator::visit(const ast::RecordTypeNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::RepeatNode* node) {
  const std::string statementsBeforeRepeat = ctx->generateBasicBlockLabel();
  saveBasicBlock(statementsBeforeRepeat, true, true);

  const std::string firstBodyStatement = ctx->generateBasicBlockLabel();
  const std::string lastBodyStatement = ctx->generateBasicBlockLabel();
  newControlFlowGraph(firstBodyStatement);
  for (const auto* statement : *node->getStatements()) {
    statement->accept(this);
  }
  saveBasicBlock(lastBodyStatement, true, true);
  const BBControlFlowGraph body{std::move(controlFlowGraphs_.top())};
  controlFlowGraphs_.pop();
  controlFlowGraphs_.top().merge(body);
  controlFlowGraphs_.top().setExitLabel(lastBodyStatement);

  const std::string firstConditionStatement = ctx->generateBasicBlockLabel();
  const std::string lastConditionStatement = ctx->generateBasicBlockLabel();
  newControlFlowGraph(firstConditionStatement);
  node->getCondition()->accept(this);
  const std::string conditionVariable = ctx->getLastTempVariable();
  saveBasicBlock(lastConditionStatement, true, true);
  const BBControlFlowGraph condition{std::move(controlFlowGraphs_.top())};
  controlFlowGraphs_.pop();
  controlFlowGraphs_.top().merge(condition);
  controlFlowGraphs_.top().setExitLabel(lastConditionStatement);

  controlFlowGraphs_.top().addBlocksLink(lastConditionStatement, firstBodyStatement);

  const std::string exitLabel = ctx->generateBasicBlockLabel();
  saveBasicBlock(exitLabel, true, true);

  controlFlowGraphs_.top()
      .getBasicBlock(lastConditionStatement)
      .addInstruction(
          std::make_unique<BBBranchV>(conditionVariable, BBBranchV::Condition::NONZERO, firstBodyStatement, exitLabel));
}

void BbCfgGenerator::visit(const ast::RoutineBodyNode* node) {
  node->getStatements()->accept(this);
}

void BbCfgGenerator::visit(const ast::RoutineDeclarationNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::RoutineHeadNode* node) {
  for (const auto* routine : *node->getRoutinePart()) {
    currentScope_ += routine->getName();
    routine->accept(this);
    currentScope_.resize(currentScope_.size() - routine->getName().size());
  }
}

void BbCfgGenerator::visit(const ast::RoutineNode* node) {
  newControlFlowGraph(currentScope_ + ".entry");
  node->getHead()->accept(this);
  node->getBody()->accept(this);

  currentBasicBlock_.addInstruction(std::make_unique<BBHalt>());
  const std::string haltLabel = ctx->generateBasicBlockLabel();
  saveBasicBlock(haltLabel, true, true);

  functionControlFlowGraphs_.insert({"program", controlFlowGraphs_.top()});
}

void BbCfgGenerator::visit(const ast::ConstRangeTypeNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::EnumerationTypeNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::RenameTypeNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::BasicTypeNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::VarRangeTypeNode* /*node*/) {}

void BbCfgGenerator::visit(const ast::WhileNode* node) {
  const std::string statementsBeforeWhile = ctx->generateBasicBlockLabel();
  saveBasicBlock(statementsBeforeWhile, true, true);

  const std::string firstConditionStatement = ctx->generateBasicBlockLabel();
  const std::string lastConditionStatement = ctx->generateBasicBlockLabel();
  newControlFlowGraph(firstConditionStatement);
  node->getCondition()->accept(this);
  const std::string conditionVariable = ctx->getLastTempVariable();
  saveBasicBlock(lastConditionStatement, true, true);
  const BBControlFlowGraph condition{std::move(controlFlowGraphs_.top())};
  controlFlowGraphs_.pop();
  controlFlowGraphs_.top().merge(condition);
  controlFlowGraphs_.top().setExitLabel(lastConditionStatement);

  const std::string firstBodyStatement = ctx->generateBasicBlockLabel();
  const std::string lastBodyStatement = ctx->generateBasicBlockLabel();
  newControlFlowGraph(firstBodyStatement);
  node->getStatements()->accept(this);
  saveBasicBlock(lastBodyStatement, true, true);
  const BBControlFlowGraph body{std::move(controlFlowGraphs_.top())};
  controlFlowGraphs_.pop();
  controlFlowGraphs_.top().merge(body);

  controlFlowGraphs_.top().addBlocksLink(lastBodyStatement, firstConditionStatement);
  controlFlowGraphs_.top().setExitLabel(lastConditionStatement);

  const std::string exitLabel = ctx->generateBasicBlockLabel();
  saveBasicBlock(exitLabel, true, true);

  controlFlowGraphs_.top()
      .getBasicBlock(lastConditionStatement)
      .addInstruction(
          std::make_unique<BBBranchV>(conditionVariable, BBBranchV::Condition::NONZERO, firstBodyStatement, exitLabel));
}

std::map<std::string, BBControlFlowGraph> BbCfgGenerator::generate(const std::unique_ptr<ast::ProgramNode>& program) {
  currentScope_ = "";
  visit(program.get());

  return functionControlFlowGraphs_;
}

void BbCfgGenerator::newControlFlowGraph(const std::string& label) {
  controlFlowGraphs_.push(BBControlFlowGraph{label});
}

void BbCfgGenerator::saveBasicBlock(const std::string& label, bool connectToLastBlock, bool setAsExit) {
  controlFlowGraphs_.top().addBBlock(label, std::move(currentBasicBlock_));

  if (connectToLastBlock) {
    controlFlowGraphs_.top().addBlocksLink(controlFlowGraphs_.top().getExitLabel(), label);
  }

  if (setAsExit) {
    controlFlowGraphs_.top().setExitLabel(label);
  }

  currentBasicBlock_ = BasicBlock{};
}

void BbCfgGenerator::generateVariableMove(ast::ExpressionNode* dest, const std::string& src) {
  if (dest->getOperation() != ast::ExpressionNode::Operation::SPECIAL) {
    throw std::runtime_error("Type error");
  }

  ast::SpecialExpressionNode* varArrRec = dynamic_cast<ast::SpecialExpressionNode*>(dest);
  if (varArrRec->getFunctionName() == ast::SpecialExpressionNode::FunctionName::VARIABLE) {
    ast::IdentifierNode* var = dynamic_cast<ast::IdentifierNode*>(varArrRec->getArgument1().get());
    currentBasicBlock_.addInstruction(
        std::make_unique<BBMoveVV>(src, var->getName(), BBMoveVV::SourceType::VARIABLE, BBMoveVV::DestinationType::VARIABLE));
  }
  else if (varArrRec->getFunctionName() == ast::SpecialExpressionNode::FunctionName::ARRAY_ACCESS) {}
  else if (varArrRec->getFunctionName() == ast::SpecialExpressionNode::FunctionName::RECORD_ACCESS) {}
  else {
    throw std::runtime_error("Type error");
  }
}
}  // namespace bblocks
