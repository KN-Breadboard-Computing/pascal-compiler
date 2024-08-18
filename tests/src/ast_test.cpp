#include <fstream>
#include <iostream>

#include "gtest/gtest.h"

#include "../../src/ast/program_node.hpp"

bool parse(const std::string &inputFileName,
		   std::vector<std::string> &errors,
		   std::unique_ptr<ast::ProgramNode> &program);

void validateAst(const std::unique_ptr<ast::ProgramNode> &program, const std::string &expectedAstFilename) {
  std::stringstream astStream;
  astStream << *program;

  std::ifstream expectedAst{expectedAstFilename};
  std::stringstream expectedAstStream;
  expectedAstStream << expectedAst.rdbuf();

  ASSERT_EQ(astStream.str(), expectedAstStream.str());
}

TEST(toAstConversion, inputFileNotFound) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("no-existing-filename.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, (std::vector<std::string>{"Cannot open file `no-existing-filename.pas`"}));
}

TEST(toAstConversion, emptyProgram) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/empty-program.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/internal/expected_ast/empty-program.ast");
}

TEST(toAstConversion, constTypeVarDefs) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/const-type-var-defs.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/internal/expected_ast/const-type-var-defs.ast");
}


TEST(toAstConversion, constTypeVarDefs1) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/const-type-var-defs1.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, (std::vector<std::string>{
	  "Error at line 12, name `c3` already used"
  }));
}

TEST(toAstConversion, constTypeVarDefs2) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/const-type-var-defs2.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, (std::vector<std::string>{
	  "Error at line 26, Mon and Fri are in more than one enum"
  }));
}

TEST(toAstConversion, constTypeVarDefs3) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/const-type-var-defs3.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, (std::vector<std::string>{
	  "Error at line 26, Sat and Sum are not in any enum"
  }));
}

TEST(toAstConversion, lValuesCorrect) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/lvalues.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
}

TEST(toAstConversion, recordFieldRedeclaration) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/record-field-redeclaration.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, (std::vector<std::string>{"Error at line 7, field name `a` duplication"}));
}

TEST(toAstConversion, arrayDeclaration) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/array-declaration.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/internal/expected_ast/array-declaration.ast");
}

TEST(toAstConversion, arrayStringIndex) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/array-string-index.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 4, array range bounds cannot be string"});
}

TEST(toAstConversion, arrayVariousIndexRangeTypes) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/array-various-index-range-types.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 4, array range bounds must have the same type"});
}

TEST(toAstConversion, predSuccOddAbs) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/pred-succ-odd-abs.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/internal/expected_ast/pred-succ-odd-abs.ast");
}

TEST(toAstConversion, chrOrd) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/chr-ord.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/internal/expected_ast/chr-ord.ast");
}

TEST(toAStConversion, succInvalidArgsNumber) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/succ-invalid-args-number.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 8, wrong number of arguments for succ"});
}

TEST(toAstConversion, succInvalidArgType) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/succ-invalid-arg-type.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 8, wrong argument type for succ - integer or char expected"});
}

TEST(toAstConversion, succInvalidReturnType) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/succ-invalid-return-type.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 9, both sides should be equal type"});
}

TEST(toAstCOnversion, expressions) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/expressions.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/internal/expected_ast/expressions.ast");
}

TEST(toAstConversion, mathExpressionDifferentTypes) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/math-expression-different-types.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 12, wrong argument type for addition - integer expected"});
}

TEST(toAstConversion, boolExpressionDifferentTypes) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/bool-expression-different-types.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 12, wrong argument type for greater or equal - matching types(integer, char, boolean) expected"});
}

TEST(toAstConversion, io) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/io.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/internal/expected_ast/io.ast");
}

TEST(toAstConversion, ioComplexType) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/io-complex-type.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 12, wrong argument type for read - integer, char or boolean expected"});
}

TEST(toAstConversion, ioInvalidArguments) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/io-invalid-arguments.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 9, wrong argument type for memory write - second argument should be integer"});
}

TEST(toAstConversion, procFunDefs) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/proc-fun-defs.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/internal/expected_ast/proc-fun-defs.ast");
}

TEST(toAstConversion, routineScoping) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/routine-scoping.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/internal/expected_ast/routine-scoping.ast");
}

TEST(toAstConversion, recursion) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/recursion.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/internal/expected_ast/recursion.ast");
}

TEST(toAstConversion, funMultipleReturn) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/fun-multiple-return.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 10, function should have one return value"});
}

TEST(toAstConversion, funNoReturn) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/fun-no-return.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 8, function should have one return value"});
}

TEST(toAstConversion, funNoReturnType) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/fun-no-return-type.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 2, syntax error"});
}

TEST(toAstConversion, typeCast) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/type-cast.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/internal/expected_ast/type-cast.ast");
}

TEST(toAstConversion, ifs) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/ifs.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/internal/expected_ast/ifs.ast");
}

TEST(toAstConversion, repeats) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/repeats.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/internal/expected_ast/repeats.ast");
}

TEST(toAstConversion, whiles) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/whiles.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/internal/expected_ast/whiles.ast");
}

TEST(toAstConversion, fors) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/fors.pas", errors, program);

  ASSERT_TRUE(result);
  ASSERT_NE(program.get(), nullptr);
  ASSERT_EQ(errors.size(), 0);
  validateAst(program, "tests/internal/expected_ast/fors.ast");
}

TEST(toAstConversion, forIteratorRedeclaration) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/for-iterator-redeclaration.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 6, name `i` already used"});
}

TEST(toAstConversion, forIndexReassignment1) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/for-index-reassignment1.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 14, loop variable `i` cannot be reassigned"});
}

TEST(toAstConversion, forIndexReassignment2) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/for-index-reassignment2.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 23, loop variable `i` cannot be reassigned"});
}

TEST(toAstConversion, forIndexReassignment3) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/for-index-reassignment3.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 14, loop variable `i` cannot be reassigned"});
}

TEST(toAstConversion, passConstantAsReferenceArgument) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("tests/internal/input/pass-constant-as-reference-argument.pas", errors, program);

  ASSERT_FALSE(result);
  ASSERT_EQ(program.get(), nullptr);
  ASSERT_EQ(errors, std::vector<std::string>{"Error at line 20, passed incompatible arguments"});
}