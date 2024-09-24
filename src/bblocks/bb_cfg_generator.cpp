#include "bb_cfg_generator.hpp"
#include "../context/context.hpp"

#include <algorithm>
#include <map>
#include <queue>
#include <set>
#include <stdexcept>
#include <utility>

namespace bblocks {
Context* ctx = Context::getInstance();

void BbCfgGenerator::visit(const ast::ArgumentsListNode* /*node*/) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Arguments List Node" << std::endl;
#endif
}

void BbCfgGenerator::visit(const ast::ArrayTypeNode* node) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Array Type Node" << std::endl;
#endif
  node->getElementType()->accept(this);
  typeBytes_[node->flat()] = typeBytes_[node->getElementType()->flat()] * countIndexes(node->getRange()->flat());
}

void BbCfgGenerator::visit(const ast::AssignNode* node) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Assign Node" << std::endl;
#endif
  node->getRhs()->accept(this);
  generateVariableMove(node->getLhs().get(), ctx->getLastTempVariable());
}

void BbCfgGenerator::visit(const ast::BuiltinCallNode* node) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Builtin Call Node" << std::endl;
#endif
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

void BbCfgGenerator::visit(const ast::UserDefineCallNode* /*node*/) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: User Call Node" << std::endl;
#endif
}

void BbCfgGenerator::visit(const ast::CaseNode* /*node*/) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Case Node" << std::endl;
#endif
}

void BbCfgGenerator::visit(const ast::CompoundStatementNode* node) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Compound Statement Node" << std::endl;
#endif
  for (auto* const statement : *node->getStatements()) {
    statement->accept(this);
  }
}

void BbCfgGenerator::visit(const ast::ConstantNode* node) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Constant Node" << std::endl;
#endif
  switch (node->getConstantType()) {
    case ast::ConstantNode::UNSPECIFIED:
      throw std::runtime_error("Type error");
    case ast::ConstantNode::INTEGER: {
      const ast::IntegerConstantNode* integerConstant = dynamic_cast<const ast::IntegerConstantNode*>(node);
      currentBasicBlock_.addInstruction(std::make_unique<BBMoveNV>(integerConstant->getValue(), ctx->generateTempVariable(),
                                                                   BBInstruction::SourceType::CONSTANT,
                                                                   BBInstruction::DestinationType::REGISTER));
      break;
    }
    case ast::ConstantNode::CHAR: {
      const ast::CharConstantNode* charConstant = dynamic_cast<const ast::CharConstantNode*>(node);
      currentBasicBlock_.addInstruction(std::make_unique<BBMoveNV>(charConstant->getValue(), ctx->generateTempVariable(),
                                                                   BBInstruction::SourceType::CONSTANT,
                                                                   BBInstruction::DestinationType::REGISTER));
      break;
    }
    case ast::ConstantNode::BOOLEAN: {
      const ast::BooleanConstantNode* boolConstant = dynamic_cast<const ast::BooleanConstantNode*>(node);
      currentBasicBlock_.addInstruction(std::make_unique<BBMoveNV>(boolConstant->getValue(), ctx->generateTempVariable(),
                                                                   BBInstruction::SourceType::CONSTANT,
                                                                   BBInstruction::DestinationType::REGISTER));
      break;
    }
    case ast::ConstantNode::STRING:
      break;
  }
}

void BbCfgGenerator::visit(const ast::MathExpressionNode* node) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Math Expression Node" << std::endl;
#endif
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
          leftOperand, rightOperand, ctx->generateTempVariable(), BBInstruction::SourceType::REGISTER,
          BBInstruction::SourceType::REGISTER, BBInstruction::DestinationType::REGISTER, BBBinaryOperationEnum::ADD));
      break;
    }
    case ast::MathExpressionNode::SUBTRACTION: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBInstruction::SourceType::REGISTER,
          BBInstruction::SourceType::REGISTER, BBInstruction::DestinationType::REGISTER, BBBinaryOperationEnum::SUB));
      break;
    }
    case ast::MathExpressionNode::MULTIPLICATION: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBInstruction::SourceType::REGISTER,
          BBInstruction::SourceType::REGISTER, BBInstruction::DestinationType::REGISTER, BBBinaryOperationEnum::MUL));
      break;
    }
    case ast::MathExpressionNode::DIVISION: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBInstruction::SourceType::REGISTER,
          BBInstruction::SourceType::REGISTER, BBInstruction::DestinationType::REGISTER, BBBinaryOperationEnum::DIV));
      break;
    }
    case ast::MathExpressionNode::MODULUS: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBInstruction::SourceType::REGISTER,
          BBInstruction::SourceType::REGISTER, BBInstruction::DestinationType::REGISTER, BBBinaryOperationEnum::MOD));
      break;
    }
    case ast::MathExpressionNode::NEGATION: {
      currentBasicBlock_.addInstruction(
          std::make_unique<BBUnaryOperationVV>(leftOperand, ctx->generateTempVariable(), BBInstruction::SourceType::REGISTER,
                                               BBInstruction::DestinationType::REGISTER, BBUnaryOperationEnum::NEG));
      break;
    }
    case ast::MathExpressionNode::AND: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBInstruction::SourceType::REGISTER,
          BBInstruction::SourceType::REGISTER, BBInstruction::DestinationType::REGISTER, BBBinaryOperationEnum::AND));
      break;
    }
    case ast::MathExpressionNode::OR: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBInstruction::SourceType::REGISTER,
          BBInstruction::SourceType::REGISTER, BBInstruction::DestinationType::REGISTER, BBBinaryOperationEnum::OR));
      break;
    }
    case ast::MathExpressionNode::NOT: {
      currentBasicBlock_.addInstruction(
          std::make_unique<BBUnaryOperationVV>(leftOperand, ctx->generateTempVariable(), BBInstruction::SourceType::REGISTER,
                                               BBInstruction::DestinationType::REGISTER, BBUnaryOperationEnum::NOT));
      break;
    }
    case ast::MathExpressionNode::EQUAL: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBInstruction::SourceType::REGISTER,
          BBInstruction::SourceType::REGISTER, BBInstruction::DestinationType::REGISTER, BBBinaryOperationEnum::SUB));
      break;
    }
    case ast::MathExpressionNode::NOT_EQUAL: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBInstruction::SourceType::REGISTER,
          BBInstruction::SourceType::REGISTER, BBInstruction::DestinationType::REGISTER, BBBinaryOperationEnum::SUB));
      break;
    }
    case ast::MathExpressionNode::LESS: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBInstruction::SourceType::REGISTER,
          BBInstruction::SourceType::REGISTER, BBInstruction::DestinationType::REGISTER, BBBinaryOperationEnum::SUB));
      break;
    }
    case ast::MathExpressionNode::LESS_EQUAL: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBInstruction::SourceType::REGISTER,
          BBInstruction::SourceType::REGISTER, BBInstruction::DestinationType::REGISTER, BBBinaryOperationEnum::SUB));
      break;
    }
    case ast::MathExpressionNode::GREATER: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBInstruction::SourceType::REGISTER,
          BBInstruction::SourceType::REGISTER, BBInstruction::DestinationType::REGISTER, BBBinaryOperationEnum::SUB));
      break;
    }
    case ast::MathExpressionNode::GREATER_EQUAL: {
      currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVVV>(
          leftOperand, rightOperand, ctx->generateTempVariable(), BBInstruction::SourceType::REGISTER,
          BBInstruction::SourceType::REGISTER, BBInstruction::DestinationType::REGISTER, BBBinaryOperationEnum::SUB));
      break;
    }
  }
}

void BbCfgGenerator::visit(const ast::SpecialExpressionNode* node) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Special Expression Node" << std::endl;
#endif
  switch (node->getFunctionName()) {
    case ast::SpecialExpressionNode::VARIABLE: {
      const ast::IdentifierNode* var = dynamic_cast<const ast::IdentifierNode*>(node->getArgument1().get());
      currentBasicBlock_.addInstruction(std::make_unique<BBMoveVV>(var->getName(), ctx->generateTempVariable(),
                                                                   BBInstruction::SourceType::REGISTER,
                                                                   BBInstruction::DestinationType::REGISTER));
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

      const std::string fullName = ctx->getLookupTable().getRoutine(function->getName(), ctx->getCurrentScope()).fullName;
      currentBasicBlock_.addInstruction(std::make_unique<BBCall>(fullName, args));
      break;
    }
    case ast::SpecialExpressionNode::ARRAY_ACCESS: {
      break;
    }
    case ast::SpecialExpressionNode::CONST: {
      const ast::ConstantNode* constant = dynamic_cast<const ast::ConstantNode*>(node->getArgument1().get());
      constant->accept(this);
      break;
    }
    case ast::SpecialExpressionNode::RECORD_ACCESS:
      break;
    case ast::SpecialExpressionNode::ENUM_ELEMENT:
      break;
    case ast::SpecialExpressionNode::ABS: {
      node->getArgument1()->accept(this);
      currentBasicBlock_.addInstruction(std::make_unique<BBUnaryOperationVV>(
          ctx->getLastTempVariable(), ctx->generateTempVariable(), BBInstruction::SourceType::REGISTER,
          BBInstruction::DestinationType::REGISTER, BBUnaryOperationEnum::SHL));
      currentBasicBlock_.addInstruction(std::make_unique<BBUnaryOperationVV>(
          ctx->getLastTempVariable(), ctx->generateTempVariable(), BBInstruction::SourceType::REGISTER,
          BBInstruction::DestinationType::REGISTER, BBUnaryOperationEnum::SHR));
    }
    case ast::SpecialExpressionNode::ODD: {
      break;
    }
    case ast::SpecialExpressionNode::PRED: {
      node->getArgument1()->accept(this);
      currentBasicBlock_.addInstruction(std::make_unique<BBUnaryOperationVV>(
          ctx->getLastTempVariable(), ctx->generateTempVariable(), BBInstruction::SourceType::REGISTER,
          BBInstruction::DestinationType::REGISTER, BBUnaryOperationEnum::DEC));
      break;
    }
    case ast::SpecialExpressionNode::SUCC: {
      node->getArgument1()->accept(this);
      currentBasicBlock_.addInstruction(std::make_unique<BBUnaryOperationVV>(
          ctx->getLastTempVariable(), ctx->generateTempVariable(), BBInstruction::SourceType::REGISTER,
          BBInstruction::DestinationType::REGISTER, BBUnaryOperationEnum::INC));
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

void BbCfgGenerator::visit(const ast::BreakNode* /*node*/) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Break Node" << std::endl;
#endif
}

void BbCfgGenerator::visit(const ast::ContinueNode* /*node*/) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Continue Node" << std::endl;
#endif
}

void BbCfgGenerator::visit(const ast::ForNode* node) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: For Node" << std::endl;
#endif
  const std::string statementsBeforeFor = ctx->generateBasicBlockLabel();
  saveBasicBlock(statementsBeforeFor, true, true);

  const std::string firstBeginStatement = ctx->generateBasicBlockLabel();
  const std::string lastBeginStatement = ctx->generateBasicBlockLabel();
  newControlFlowGraph(firstBeginStatement);
  node->getStart()->accept(this);
  const std::string beginVariable = ctx->getLastTempVariable();
  currentBasicBlock_.addInstruction(std::make_unique<BBMoveVV>(beginVariable, node->getIterator()->getName(),
                                                               BBInstruction::SourceType::REGISTER,
                                                               BBInstruction::DestinationType::REGISTER));
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
      node->getIterator()->getName(), endVariable, ctx->generateTempVariable(), BBInstruction::SourceType::REGISTER,
      BBInstruction::SourceType::REGISTER, BBInstruction::DestinationType::REGISTER, BBBinaryOperationEnum::SUB));
  const std::string conditionVariable = ctx->getLastTempVariable();
  const std::string conditionStatement = ctx->generateBasicBlockLabel();
  saveBasicBlock(conditionStatement, true, true);

  const std::string firstBodyStatement = ctx->generateBasicBlockLabel();
  const std::string lastBodyStatement = ctx->generateBasicBlockLabel();
  newControlFlowGraph(firstBodyStatement);
  node->getStatements()->accept(this);
  currentBasicBlock_.addInstruction(std::make_unique<BBBinaryOperationVNV>(
      node->getIterator()->getName(), 1, node->getIterator()->getName(), BBInstruction::SourceType::REGISTER,
      BBInstruction::SourceType::CONSTANT, BBInstruction::DestinationType::REGISTER,
      node->getDirection() == ast::ForNode::INCREMENT ? BBBinaryOperationEnum::ADD : BBBinaryOperationEnum::SUB));
  saveBasicBlock(lastBodyStatement, true, true);
  const BBControlFlowGraph body{std::move(controlFlowGraphs_.top())};
  controlFlowGraphs_.pop();
  controlFlowGraphs_.top().merge(body);

  controlFlowGraphs_.top().addBlocksLink(lastBodyStatement, conditionStatement);

  const std::string exitLabel = ctx->generateBasicBlockLabel();
  saveBasicBlock(exitLabel, true, true);

  controlFlowGraphs_.top()
      .basicBlock(conditionStatement)
      .addInstruction(std::make_unique<BBBranchV>(
          conditionVariable, BBInstruction::SourceType::REGISTER,
          node->getDirection() == ast::ForNode::Direction::INCREMENT ? BBBranchCondition::POSITIVE : BBBranchCondition::NEGATIVE,
          firstBodyStatement, exitLabel));
}

void BbCfgGenerator::visit(const ast::GotoNode* /*node*/) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Goto Node" << std::endl;
#endif
}

void BbCfgGenerator::visit(const ast::IdentifierNode* /*node*/) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Identifier Node" << std::endl;
#endif
}

void BbCfgGenerator::visit(const ast::IfNode* node) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: If Node" << std::endl;
#endif
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
        .basicBlock(lastConditionStatement)
        .addInstruction(std::make_unique<BBBranchV>(conditionVariable, BBInstruction::SourceType::REGISTER,
                                                    BBBranchCondition::NONZERO, firstTrueStatement, firstFalseStatement));
  }
  else {
    controlFlowGraphs_.top().addBlocksLink(lastConditionStatement, exitLabel);
    controlFlowGraphs_.top()
        .basicBlock(lastConditionStatement)
        .addInstruction(std::make_unique<BBBranchV>(conditionVariable, BBInstruction::SourceType::REGISTER,
                                                    BBBranchCondition::NONZERO, firstTrueStatement, exitLabel));
  }
}

void BbCfgGenerator::visit(const ast::ParamsGroupNode* /*node*/) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Params Group Node" << std::endl;
#endif
}

void BbCfgGenerator::visit(const ast::ParamsNode* /*node*/) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Params Node" << std::endl;
#endif
}

void BbCfgGenerator::visit(const ast::ProgramNode* node) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Program Node" << std::endl;
  std::cout << "Cfg debug: next scope: program" << std::endl;
#endif
  ctx->pushScope("program");

  newControlFlowGraph(ctx->getCurrentScope() + ".entry");
  node->getRoutine()->accept(this);

  ctx->popScope();

  functionControlFlowGraphs_.insert({"program", controlFlowGraphs_.top()});
}

void BbCfgGenerator::visit(const ast::RecordTypeNode* node) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Record Type Node" << std::endl;
#endif
  size_t recordSize{0};
  for (const auto* field : *node->getFields()) {
    field->second->accept(this);
    recordSize += typeBytes_[field->second->flat()] * field->first->size();
  }
  typeBytes_[node->flat()] = recordSize;
}

void BbCfgGenerator::visit(const ast::RepeatNode* node) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Repeat Node" << std::endl;
#endif
  const std::string statementsBeforeRepeat = ctx->generateBasicBlockLabel();
  saveBasicBlock(statementsBeforeRepeat, true, true);

  const std::string firstBodyStatement = ctx->generateBasicBlockLabel();
  const std::string lastBodyStatement = ctx->generateBasicBlockLabel();
  newControlFlowGraph(firstBodyStatement);
  node->getStatements()->accept(this);
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
      .basicBlock(lastConditionStatement)
      .addInstruction(std::make_unique<BBBranchV>(conditionVariable, BBInstruction::SourceType::REGISTER,
                                                  BBBranchCondition::NONZERO, firstBodyStatement, exitLabel));
}

void BbCfgGenerator::visit(const ast::RoutineBodyNode* node) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Routine Body Node" << std::endl;
#endif
  node->getStatements()->accept(this);

  if (ctx->getTopScope() == "program") {
    currentBasicBlock_.addInstruction(std::make_unique<BBHalt>());
  }
  else {
    currentBasicBlock_.addInstruction(std::make_unique<BBRet>());
  }
  const std::string endLabel = ctx->generateBasicBlockLabel();
  saveBasicBlock(endLabel, true, true);
}

void BbCfgGenerator::visit(const ast::RoutineDeclarationNode* node) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Routine Declaration Node" << std::endl;
#endif
  node->getRoutine()->accept(this);
}

void BbCfgGenerator::visit(const ast::RoutineHeadNode* node) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Routine Head Node" << std::endl;
#endif
  for (const auto* constant : *node->getConstantsPart()) {
    constant->second->accept(this);
    currentBasicBlock_.addInstruction(std::make_unique<BBMoveVV>(ctx->getLastTempVariable(), constant->first->getName(),
                                                                 BBInstruction::SourceType::REGISTER,
                                                                 BBInstruction::DestinationType::REGISTER));
  }

  for (const auto* type : *node->getTypesPart()) {
    type->second->accept(this);
  }

  size_t procedureOffset{0};
  for (const auto* var : *node->getVariablesPart()) {
    var->second->accept(this);
    procedureOffset += typeBytes_[var->second->flat()] * var->first->size();
  }
  procedureOffsets_[ctx->getCurrentScope()] = procedureOffset;

  for (const auto* routine : *node->getRoutinePart()) {
#ifdef CFG_DEBUG
    std::cout << "Cfg debug: next scope: " << routine->getName() << std::endl;
#endif
    ctx->pushScope(routine->getName());
    newControlFlowGraph(ctx->getCurrentScope() + ".entry");
    routine->accept(this);

    const std::string fullName = ctx->getLookupTable().getRoutine(routine->getName(), ctx->getCurrentScope()).fullName;
    functionControlFlowGraphs_[fullName] = controlFlowGraphs_.top();

    if (ctx->getTopScope() != "program") {
      controlFlowGraphs_.pop();
    }

    ctx->popScope();
  }
}

void BbCfgGenerator::visit(const ast::RoutineNode* node) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Routine Node" << std::endl;
#endif
  node->getHead()->accept(this);
  node->getBody()->accept(this);
}

void BbCfgGenerator::visit(const ast::ConstRangeTypeNode* /*node*/) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Const Range Type Node" << std::endl;
#endif
}

void BbCfgGenerator::visit(const ast::EnumerationTypeNode* node) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Enumeration Type Node" << std::endl;
#endif
  for (size_t i = 0; i < node->getIdentifiers()->size(); ++i) {
    enumTranslator_[node->getIdentifiers()->at(i)->getName()] = i;
  }
  typeBytes_[node->flat()] = 1;
}

void BbCfgGenerator::visit(const ast::RenameTypeNode* node) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Rename Type Node" << std::endl;
#endif
  typeBytes_[node->flat()] =
      typeBytes_[ctx->getLookupTable().getType(node->getIdentifier()->getName(), ctx->getCurrentScope()).type];
}

void BbCfgGenerator::visit(const ast::BasicTypeNode* node) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Basic Type Node" << std::endl;
#endif
  typeBytes_[node->flat()] = 1;
}

void BbCfgGenerator::visit(const ast::VarRangeTypeNode* /*node*/) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Var Range Type Node" << std::endl;
#endif
}

void BbCfgGenerator::visit(const ast::WhileNode* node) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: While Node" << std::endl;
#endif
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
      .basicBlock(lastConditionStatement)
      .addInstruction(std::make_unique<BBBranchV>(conditionVariable, BBInstruction::SourceType::REGISTER,
                                                  BBBranchCondition::NONZERO, firstBodyStatement, exitLabel));
}

void BbCfgGenerator::generate(const std::unique_ptr<ast::ProgramNode>& program) {
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Generating started" << std::endl;
#endif
  visit(program.get());
#ifdef CFG_DEBUG
  std::cout << "Cfg debug: Generating done" << std::endl;
#endif
}

void BbCfgGenerator::removeEmptyBasicBlocks() {
  for (auto& [funName, fun] : functionControlFlowGraphs_) {
    std::map<std::string, std::string> labelsTranslation;
    for (const auto& [blockLabel, block] : fun.getBasicBlocks()) {
      std::string label{blockLabel};
      std::vector<std::string> renames;
      while (fun.getBasicBlock(label).empty()) {
        renames.push_back(label);
        // assert fun.getOutLinks(label).size() == 1
        label = fun.getOutLinks(label).front();
      }

      for (const auto& rename : renames) {
        labelsTranslation[rename] = label;
      }
    }

    std::map<std::string, std::vector<std::string>> updatedSrcDest;
    for (auto srcDest = fun.getSrcDestLinks().cbegin(); srcDest != fun.getSrcDestLinks().cend(); ++srcDest) {
      const std::string source =
          labelsTranslation.find(srcDest->first) != labelsTranslation.end() ? labelsTranslation[srcDest->first] : srcDest->first;
      updatedSrcDest.insert({source, {}});
      for (auto dest = srcDest->second.cbegin(); dest != srcDest->second.cend(); ++dest) {
        const std::string destination =
            labelsTranslation.find(*dest) != labelsTranslation.end() ? labelsTranslation[*dest] : *dest;
        if (std::find(updatedSrcDest[source].begin(), updatedSrcDest[source].end(), destination) ==
                updatedSrcDest[source].end() &&
            source != destination) {
          updatedSrcDest[source].push_back(destination);
        }
      }
    }

    std::map<std::string, std::vector<std::string>> updatedDestSrc;
    for (auto destSrc = fun.getDestSrcLinks().cbegin(); destSrc != fun.getDestSrcLinks().cend(); ++destSrc) {
      const std::string destination =
          labelsTranslation.find(destSrc->first) != labelsTranslation.end() ? labelsTranslation[destSrc->first] : destSrc->first;
      updatedDestSrc.insert({destination, {}});

      for (auto src = destSrc->second.begin(); src != destSrc->second.end(); ++src) {
        const std::string source = labelsTranslation.find(*src) != labelsTranslation.end() ? labelsTranslation[*src] : *src;
        if (std::find(updatedDestSrc[destination].begin(), updatedDestSrc[destination].end(), source) ==
                updatedDestSrc[destination].end() &&
            destination != source) {
          updatedDestSrc[destination].push_back(source);
        }
      }
    }

    std::map<std::string, BasicBlock> updatedBlocks;
    for (const auto& [blockLabel, block] : fun.getBasicBlocks()) {
      if (!block.empty()) {
        const std::string newLabel =
            labelsTranslation.find(blockLabel) != labelsTranslation.end() ? labelsTranslation[blockLabel] : blockLabel;
        updatedBlocks.insert({newLabel, block});
      }
    }

    fun.update(updatedSrcDest, updatedDestSrc, updatedBlocks);

    if (labelsTranslation.find(fun.getEntryLabel()) != labelsTranslation.end()) {
      fun.setEntryLabel(labelsTranslation[fun.getEntryLabel()]);
    }

    if (labelsTranslation.find(fun.getExitLabel()) != labelsTranslation.end()) {
      fun.setExitLabel(labelsTranslation[fun.getExitLabel()]);
    }

    for (auto& block : fun.basicBlocks()) {
      for (auto& instruction : block.second.instructions()) {
        for (const auto& labelTranslation : labelsTranslation) {
          instruction->replaceLabel(labelTranslation.first, labelTranslation.second);
        }
      }
    }
  }
}

void BbCfgGenerator::removeTemporaryVariables() {
  for (auto& [funName, fun] : functionControlFlowGraphs_) {
    std::map<std::string, size_t> variableDefs;
    std::map<std::string, size_t> variableDefsInMove;
    std::map<std::string, size_t> variableDefsInOperations;
    for (const auto& [blockLabel, block] : fun.basicBlocks()) {
      for (const auto& instruction : block.getInstructions()) {
        const BBInstruction::Type instructionType = instruction->getType();
        instruction->visitDefVariables(
            [&variableDefs, &variableDefsInMove, &variableDefsInOperations, instructionType](const std::string& var) {
              if (variableDefs.find(var) == variableDefs.end()) {
                variableDefs[var] = 0;
                variableDefsInMove[var] = 0;
                variableDefsInOperations[var] = 0;
              }

              variableDefs[var]++;
              if (instructionType == BBInstruction::Type::MOVE) {
                variableDefsInMove[var]++;
              }
              else if (instructionType == BBInstruction::Type::UNARY_OPERATION ||
                       instructionType == BBInstruction::Type::BINARY_OPERATION) {
                variableDefsInOperations[var]++;
              }
            });
      }
    }

    std::map<std::string, VariableReassignment> reassignments;

    std::queue<std::string> blocksToProcess;
    std::set<std::string> visitedBlocks;
    blocksToProcess.push(fun.getEntryLabel());
    visitedBlocks.insert(fun.getEntryLabel());
    while (!blocksToProcess.empty()) {
      const std::string blockLabel = blocksToProcess.front();
      blocksToProcess.pop();
      BasicBlock blockAfterFirstPass;
      for (auto& instruction : fun.basicBlock(blockLabel).instructions()) {
        const std::vector<BBInstruction::TemplateArgumentType> templateTypes = instruction->getTemplateTypes();
        if (instruction->getType() == BBInstruction::Type::MOVE) {
          if (templateTypes[1] == BBInstruction::TemplateArgumentType::STRING) {
            if (templateTypes[0] == BBInstruction::TemplateArgumentType::STRING) {
              BBMoveVV* move = dynamic_cast<BBMoveVV*>(instruction.get());
              const VariableType dst = move->getDestination();
              const VariableType src = move->getSource();
              if (Context::isTempVariable(dst) && variableDefs[dst] == 1 && variableDefsInMove[dst] == 1) {
                reassignments.insert({dst, {BBInstruction::TemplateArgumentType::STRING, 0, src}});
              }
              else if (Context::isTempVariable(src) && variableDefs[src] == 1 && variableDefsInOperations[src] == 1) {
                reassignments.insert({src, {BBInstruction::TemplateArgumentType::STRING, 0, dst}});
              }
              else {
                blockAfterFirstPass.addInstruction(instruction->clone());
              }
            }
            else {  // (templateTypes[0] == BBInstruction::TemplateArgumentType::NUMBER)
              BBMoveNV* move = dynamic_cast<BBMoveNV*>(instruction.get());
              const VariableType dst = move->getDestination();
              const NumericType src = move->getSource();
              if (Context::isTempVariable(dst) && variableDefs[dst] == 1 && variableDefsInMove[dst] == 1) {
                reassignments.insert({dst, {BBInstruction::TemplateArgumentType::NUMBER, src, ""}});
              }
              else {
                blockAfterFirstPass.addInstruction(instruction->clone());
              }
            }
          }
        }
        else {
          blockAfterFirstPass.addInstruction(instruction->clone());
        }
      }

      BasicBlock blockAfterSecondPass;
      for (auto& instruction : blockAfterFirstPass.instructions()) {
        std::unique_ptr<BBInstruction> newInstruction = instruction->clone();
        for (const auto& reassignment : reassignments) {
          if (reassignment.second.type == BBInstruction::TemplateArgumentType::STRING) {
            newInstruction = newInstruction->replaceVariable(reassignment.first, reassignment.second.variable);
          }
          else {
            newInstruction = newInstruction->replaceVariable(reassignment.first, reassignment.second.number);
          }
        }
        blockAfterSecondPass.addInstruction(std::move(newInstruction));
      }

      fun.setBasicBlock(blockLabel, blockAfterSecondPass);

      for (const auto& outLink : fun.getOutLinks(blockLabel)) {
        if (visitedBlocks.find(outLink) == visitedBlocks.end()) {
          blocksToProcess.push(outLink);
          visitedBlocks.insert(outLink);
        }
      }
    }
  }
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
    const ast::IdentifierNode* var = dynamic_cast<const ast::IdentifierNode*>(varArrRec->getArgument1().get());
    currentBasicBlock_.addInstruction(std::make_unique<BBMoveVV>(src, var->getName(), BBInstruction::SourceType::REGISTER,
                                                                 BBInstruction::DestinationType::REGISTER));
  }
  else if (varArrRec->getFunctionName() == ast::SpecialExpressionNode::FunctionName::ARRAY_ACCESS) {}
  else if (varArrRec->getFunctionName() == ast::SpecialExpressionNode::FunctionName::RECORD_ACCESS) {}
  else {
    throw std::runtime_error("Type error");
  }
}

bool BbCfgGenerator::isChar(const std::string& expr) {
  return expr.size() == 1;
}

bool BbCfgGenerator::isInteger(const std::string& expr) {
  return std::all_of(expr.begin(), expr.end(), ::isdigit) ||
         (expr.size() > 1 && expr[0] == '-' && std::all_of(expr.begin() + 1, expr.end(), ::isdigit));
}

bool BbCfgGenerator::isBoolean(const std::string& expr) {
  return expr == "true" || expr == "false";
}

size_t BbCfgGenerator::countIndexes(const std::string type) {
  if (type == "integer" || type == "char") {
    return 256;
  }

  if (type == "boolean") {
    return 2;
  }

  if (type.find("enum%") == 0) {
    return std::ranges::count(type, '%') - 1;
  }

  if (type.find("constrange%") == 0) {
    std::string begin{};
    std::string end{};
    size_t pos;
    for (pos = 11; pos < type.size(); pos++) {
      if (type[pos] == '.') {
        break;
      }
      begin += type[pos];
    }

    for (pos += 2; pos < type.size(); pos++) {
      end += type[pos];
    }

    if (isInteger(begin) && isInteger(end)) {
      int int1 = std::atoi(begin.c_str());
      int int2 = std::atoi(end.c_str());
      return int2 - int1 + 1;
    }

    if (isChar(begin) && isInteger(end)) {
      int char1 = static_cast<int>(begin.at(0));
      int char2 = static_cast<int>(end.at(0));
      return char2 - char1 + 1;
    }

    if (isBoolean(begin) && isBoolean(end)) {
      int bool1 = begin == "true" ? 1 : 0;
      int bool2 = end == "true" ? 1 : 0;
      return bool2 - bool1 + 1;
    }

    throw std::runtime_error("type error");
  }

  if (type.find("enumrange%") == 0) {
    std::string enumName, beginEnum, endEnum;
    size_t pos{10};
    for (; pos < type.size(); pos++) {
      if (type[pos] == '%') {
        break;
      }
      enumName += type[pos];
    }

    pos++;
    while (type[pos] != '.') {
      beginEnum += type[pos];
      pos++;
    }

    pos += 2;
    for (; pos < type.size(); pos++) {
      endEnum += type[pos];
    }

    return enumTranslator_[endEnum] - enumTranslator_[beginEnum] + 1;
  }

  throw std::runtime_error("type error");
}

}  // namespace bblocks
