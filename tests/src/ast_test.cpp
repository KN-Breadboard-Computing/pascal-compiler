#include <fstream>
#include <iostream>
#include <sstream>

#include "gtest/gtest.h"

#include "../../src/ast/program_node.hpp"

bool parse(const std::string& inputFileName, std::vector<std::string>& errors, std::unique_ptr<ast::ProgramNode>& program);

void compareFiles(const char *resultFileName, const char *expectedFileName) {
  std::ifstream result(resultFileName);
  std::ifstream expected(expectedFileName);

  std::stringstream resultStream;
  std::stringstream expectedStream;
  resultStream << result.rdbuf();
  expectedStream << expected.rdbuf();

  ASSERT_EQ(resultStream.str(), expectedStream.str());

  result.close();
  expected.close();
}

TEST(toAstConversion, inputFileNotFound) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;

  const auto result = parse("no-existing-file.txt", errors, program);

  std::fstream resultFile{"output.txt"};
  for(const auto& error: errors) {
	resultFile << error << std::endl;
  }
}