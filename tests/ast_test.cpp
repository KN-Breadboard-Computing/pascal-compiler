#include <fstream>
#include <iostream>

#include "gtest/gtest.h"

#include "../src/ast/program_node.hpp"

#undef YACC_ENABLE_GOTO

using namespace ast;

bool parse(const std::string& inputFileName, std::vector<std::string>& errors, std::unique_ptr<ProgramNode>& program);

void validateAst(const std::unique_ptr<ProgramNode>& program, const std::string& expectedAstFilename) {
  std::stringstream astStream;
  astStream << *program;

  std::ifstream expectedAst{expectedAstFilename};
  std::stringstream expectedAstStream;
  expectedAstStream << expectedAst.rdbuf();

  ASSERT_EQ(astStream.str(), expectedAstStream.str());
}

TEST(toAstConversion, inputFileNotFound) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("no-existing-filename.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, (std::vector<std::string>{"Cannot open file `no-existing-filename.pas`"}));
}

TEST(toAstConversion, emptyProgram) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/empty-program.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/expected_ast/empty-program.ast");
}

TEST(toAstConversion, constTypeVarDefs) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/const-type-var-defs.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/expected_ast/const-type-var-defs.ast");
}

TEST(toAstConversion, constTypeVarDefs1) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/const-type-var-defs1.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, (std::vector<std::string>{"Error at line 12, name `c3` already used"}));
}

TEST(toAstConversion, constTypeVarDefs2) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/const-type-var-defs2.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, (std::vector<std::string>{"Error at line 26, Mon and Fri are in more than one enum"}));
}

TEST(toAstConversion, constTypeVarDefs3) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/const-type-var-defs3.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, (std::vector<std::string>{"Error at line 26, Sat and Sum are not in any enum"}));
}

TEST(toAstConversion, lValues) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/lvalues.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
}

TEST(toAstConversion, recordFieldRedeclaration) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/record-field-redeclaration.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, (std::vector<std::string>{"Error at line 7, field name `a` duplication"}));
}

TEST(toAstConversion, arrayDeclaration) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/array-declaration.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/expected_ast/array-declaration.ast");
}

TEST(toAstConversion, arrayStringIndex) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/array-string-index.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 4, array range bounds cannot be string"});
}

TEST(toAstConversion, arrayVariousIndexRangeTypes) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/array-various-index-range-types.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 4, array range bounds must have the same type"});
}

TEST(toAstConversion, predSuccOddAbs) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/pred-succ-odd-abs.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/expected_ast/pred-succ-odd-abs.ast");
}

TEST(toAstConversion, chrOrd) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/chr-ord.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/expected_ast/chr-ord.ast");
}

TEST(toAStConversion, succInvalidArgsNumber) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/succ-invalid-args-number.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 8, wrong number of arguments for succ"});
}

TEST(toAstConversion, succInvalidArgType) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/succ-invalid-arg-type.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 8, wrong argument type for succ - integer or char expected"});
}

TEST(toAstConversion, succInvalidReturnType) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/succ-invalid-return-type.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 9, both sides should be equal type"});
}

TEST(toAstCOnversion, expressions) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/expressions.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/expected_ast/expressions.ast");
}

TEST(toAstConversion, mathExpressionDifferentTypes) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/math-expression-different-types.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 12, wrong argument type for addition - integer expected"});
}

TEST(toAstConversion, boolExpressionDifferentTypes) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/bool-expression-different-types.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 12, wrong argument type for greater or equal - matching types(integer, char, boolean) expected"});
}

TEST(toAstConversion, io) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/io.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/expected_ast/io.ast");
}

TEST(toAstConversion, ioComplexType) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/io-complex-type.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 12, wrong argument type for read - integer, char or boolean expected"});
}

TEST(toAstConversion, ioInvalidArguments) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/io-invalid-arguments.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 9, wrong argument type for memory write - second argument should be integer"});
}

TEST(toAstConversion, procFunDefs) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/proc-fun-defs.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/expected_ast/proc-fun-defs.ast");
}

TEST(toAstConversion, routineScoping) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/routine-scoping.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/expected_ast/routine-scoping.ast");
}

TEST(toAstConversion, recursion) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/recursion.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/expected_ast/recursion.ast");
}

TEST(toAstConversion, funMultipleReturn) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/fun-multiple-return.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 10, function should have one return value"});
}

TEST(toAstConversion, funNoReturn) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/fun-no-return.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 8, function should have one return value"});
}

TEST(toAstConversion, funNoReturnType) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/fun-no-return-type.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 2, syntax error"});
}

TEST(toAstConversion, typeCast) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/type-cast.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/expected_ast/type-cast.ast");
}

TEST(toAstConversion, ifs) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/ifs.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/expected_ast/ifs.ast");
}

TEST(toAstConversion, repeats) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/repeats.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/expected_ast/repeats.ast");
}

TEST(toAstConversion, whiles) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/whiles.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/expected_ast/whiles.ast");
}

TEST(toAstConversion, fors) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/fors.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/expected_ast/fors.ast");
}

TEST(toAstConversion, forIteratorRedeclaration) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/for-iterator-redeclaration.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 6, name `i` already used"});
}

TEST(toAstConversion, forIndexReassignment1) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/for-index-reassignment1.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 14, loop variable `i` cannot be reassigned"});
}

TEST(toAstConversion, forIndexReassignment2) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/for-index-reassignment2.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 23, loop variable `i` cannot be reassigned"});
}

TEST(toAstConversion, forIndexReassignment3) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/for-index-reassignment3.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 14, loop variable `i` cannot be reassigned"});
}

TEST(toAstConversion, passConstantAsReferenceArgument) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/pass-constant-as-reference-argument.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 20, passed incompatible arguments"});
}

TEST(toAstConversion, gotos) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/gotos.pas", errors, program);

#ifdef YACC_ENABLE_GOTO
  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/expected_ast/gotos.ast");
#else
  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 4, goto is disabled"});
#endif
}

TEST(toAstConversion, gotoStrLabel) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/goto-str-label.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 4, syntax error"});
}

TEST(astConversion, cases) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/cases.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/expected_ast/cases.ast");
}

TEST(astConversion, caseMultipleOtherwise) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/case-multiple-otherwise.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 16, otherwise label can be used only once"});
}

TEST(astConversion, caseOtherwiseNoLast) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/case-otherwise-no-last.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 15, otherwise must be last label"});
}

TEST(toAstConversion, caseInvalidExpressionType) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/case-invalid-expression-type.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 10, case expression must be integer, char, boolean or enum type"});
}

TEST(toAstConversion, variableEnumNameCollision) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/variable-enum-name-collision.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 6, name `a` already used"});
}

TEST(toAstConversion, breakOutOfLoop) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/break-out-of-loop.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, (std::vector<std::string>{"Error at line 29, lack of end", "Error at line 29, lack of end dot", "Error at line 29, syntax error"}));
}

TEST(toAstConversion, continueOutOfLoop) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/continue-out-of-loop.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, (std::vector<std::string>{"Error at line 31, lack of end", "Error at line 31, lack of end dot", "Error at line 31, syntax error"}));
}

TEST(toAstConversion, assignToConst) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/assign-to-const.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 7, left side of assignment must be assignable"});
}

TEST(toAstConversion, stringConstant) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;

  const auto result = parse("tests/input_ast/string-constant.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 4, const type must be basic"});
}
