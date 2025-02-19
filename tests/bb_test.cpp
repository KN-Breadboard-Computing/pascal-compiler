#include <fstream>
#include <iostream>

#include "gtest/gtest.h"

#include "../src/ast/program_node.hpp"
#include "../src/bblocks/bb_cfg_generator.hpp"

using namespace bblocks;

bool parse(const std::string& inputFileName, std::vector<std::string>& errors, std::unique_ptr<ast::ProgramNode>& program);

void validateBasicBlocks(const std::map<std::string, BBControlFlowGraph> controlFlowGraphs,
                         const std::string& expectedBbFilename) {
  std::stringstream bbStream;
  for (const auto& [name, cfg] : controlFlowGraphs) {
    bbStream << name << ":\n" << cfg << std::endl;
  }

  std::ifstream expectedBb{expectedBbFilename};
  std::stringstream expectedBbStream;
  expectedBbStream << expectedBb.rdbuf();

  ASSERT_EQ(bbStream.str(), expectedBbStream.str());
}

TEST(toBbConversion, constants) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  parse("tests/input_bb/constants.pas", errors, program);

  BbCfgGenerator cfgGenerator;
  cfgGenerator.generate(program);
  validateBasicBlocks(cfgGenerator.getControlFlowGraphs(), "tests/expected_bb/constants.bb");

  cfgGenerator.optimize();
  validateBasicBlocks(cfgGenerator.getControlFlowGraphs(), "tests/expected_bb/constants.bb.opt");
}

TEST(toBbConversion, while1) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  parse("tests/input_bb/while1.pas", errors, program);

  BbCfgGenerator cfgGenerator;
  cfgGenerator.generate(program);
  validateBasicBlocks(cfgGenerator.getControlFlowGraphs(), "tests/expected_bb/while1.bb");

  cfgGenerator.optimize();
  validateBasicBlocks(cfgGenerator.getControlFlowGraphs(), "tests/expected_bb/while1.bb.opt");
}

TEST(toBbConversion, while2) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  parse("tests/input_bb/while2.pas", errors, program);

  BbCfgGenerator cfgGenerator;
  cfgGenerator.generate(program);
  validateBasicBlocks(cfgGenerator.getControlFlowGraphs(), "tests/expected_bb/while2.bb");

  cfgGenerator.optimize();
  validateBasicBlocks(cfgGenerator.getControlFlowGraphs(), "tests/expected_bb/while2.bb.opt");
}

TEST(toBbConversion, while3) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  parse("tests/input_bb/while3.pas", errors, program);

  BbCfgGenerator cfgGenerator;
  cfgGenerator.generate(program);
  validateBasicBlocks(cfgGenerator.getControlFlowGraphs(), "tests/expected_bb/while3.bb");

  cfgGenerator.optimize();
  validateBasicBlocks(cfgGenerator.getControlFlowGraphs(), "tests/expected_bb/while3.bb.opt");
}

TEST(toBbConversion, repeat1) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  parse("tests/input_bb/repeat1.pas", errors, program);

  BbCfgGenerator cfgGenerator;
  cfgGenerator.generate(program);
  validateBasicBlocks(cfgGenerator.getControlFlowGraphs(), "tests/expected_bb/repeat1.bb");

  cfgGenerator.optimize();
  validateBasicBlocks(cfgGenerator.getControlFlowGraphs(), "tests/expected_bb/repeat1.bb.opt");
}

TEST(toBbConversion, repeat2) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  parse("tests/input_bb/repeat2.pas", errors, program);

  BbCfgGenerator cfgGenerator;
  cfgGenerator.generate(program);
  validateBasicBlocks(cfgGenerator.getControlFlowGraphs(), "tests/expected_bb/repeat2.bb");

  cfgGenerator.optimize();
  validateBasicBlocks(cfgGenerator.getControlFlowGraphs(), "tests/expected_bb/repeat2.bb.opt");
}

TEST(toBbConversion, repeat3) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  parse("tests/input_bb/repeat3.pas", errors, program);

  BbCfgGenerator cfgGenerator;
  cfgGenerator.generate(program);
  validateBasicBlocks(cfgGenerator.getControlFlowGraphs(), "tests/expected_bb/repeat3.bb");

  cfgGenerator.optimize();
  validateBasicBlocks(cfgGenerator.getControlFlowGraphs(), "tests/expected_bb/repeat3.bb.opt");
}

TEST(toBbConversion, for1) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  parse("tests/input_bb/for1.pas", errors, program);

  BbCfgGenerator cfgGenerator;
  cfgGenerator.generate(program);
  validateBasicBlocks(cfgGenerator.getControlFlowGraphs(), "tests/expected_bb/for1.bb");

  cfgGenerator.optimize();
  validateBasicBlocks(cfgGenerator.getControlFlowGraphs(), "tests/expected_bb/for1.bb.opt");
}

TEST(toBbConversion, for2) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  parse("tests/input_bb/for2.pas", errors, program);

  BbCfgGenerator cfgGenerator;
  cfgGenerator.generate(program);
  validateBasicBlocks(cfgGenerator.getControlFlowGraphs(), "tests/expected_bb/for2.bb");

  cfgGenerator.optimize();
  validateBasicBlocks(cfgGenerator.getControlFlowGraphs(), "tests/expected_bb/for2.bb.opt");
}

TEST(toBbConversion, for3) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  parse("tests/input_bb/for3.pas", errors, program);

  BbCfgGenerator cfgGenerator;
  cfgGenerator.generate(program);
  validateBasicBlocks(cfgGenerator.getControlFlowGraphs(), "tests/expected_bb/for3.bb");

  cfgGenerator.optimize();
  validateBasicBlocks(cfgGenerator.getControlFlowGraphs(), "tests/expected_bb/for3.bb.opt");
}

TEST(toBbConversion, if1) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  parse("tests/input_bb/if1.pas", errors, program);

  BbCfgGenerator cfgGenerator;
  cfgGenerator.generate(program);
  validateBasicBlocks(cfgGenerator.getControlFlowGraphs(), "tests/expected_bb/if1.bb");

  cfgGenerator.optimize();
  validateBasicBlocks(cfgGenerator.getControlFlowGraphs(), "tests/expected_bb/if1.bb.opt");
}

TEST(toBbConversion, if2) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  parse("tests/input_bb/if2.pas", errors, program);

  BbCfgGenerator cfgGenerator;
  cfgGenerator.generate(program);
  validateBasicBlocks(cfgGenerator.getControlFlowGraphs(), "tests/expected_bb/if2.bb");

  cfgGenerator.optimize();
  validateBasicBlocks(cfgGenerator.getControlFlowGraphs(), "tests/expected_bb/if2.bb.opt");
}

TEST(toBbConversion, if3) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  parse("tests/input_bb/if3.pas", errors, program);

  BbCfgGenerator cfgGenerator;
  cfgGenerator.generate(program);
  validateBasicBlocks(cfgGenerator.getControlFlowGraphs(), "tests/expected_bb/if3.bb");

  cfgGenerator.optimize();
  validateBasicBlocks(cfgGenerator.getControlFlowGraphs(), "tests/expected_bb/if3.bb.opt");
}

TEST(toBBConversion, types) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  parse("tests/input_bb/types.pas", errors, program);
  BbCfgGenerator cfgGenerator;
  cfgGenerator.generate(program);

  const std::map<std::string, std::size_t> expectedEnums{{"Mon", 0}, {"Tue", 1}, {"Wed", 2}, {"Thu", 3},
                                                         {"Fri", 4}, {"Sat", 5}, {"Sun", 6}};
  ASSERT_EQ(cfgGenerator.getEnumTranslator(), expectedEnums);

  const std::map<std::string, std::size_t> expectedTypeBytes{
      {"integer", 1},
      {"char", 1},
      {"boolean", 1},
      {"enum%Mon%Tue%Wed%Thu%Fri%Sat%Sun%", 1},
      {"record$$Name#(char)$Surname#(char)$Age#(integer)$IsHired#(boolean)$WorkHours#(array@@enum%Mon%Tue%Wed%Thu%Fri%Sat%Sun%@"
       "integer@@)$$",
       11},
      {"record$$Father#(record$$Name#(char)$Surname#(char)$Age#(integer)$IsHired#(boolean)$WorkHours#(array@@enum%Mon%Tue%Wed%"
       "Thu%Fri%Sat%Sun%@integer@@)$$)$Mother#(record$$Name#(char)$Surname#(char)$Age#(integer)$IsHired#(boolean)$WorkHours#("
       "array@@enum%Mon%Tue%Wed%Thu%Fri%Sat%Sun%@integer@@)$$)$Children#(array@@constrange%1..10@record$$Name#(char)$Surname#("
       "char)$Age#(integer)$IsHired#(boolean)$WorkHours#(array@@enum%Mon%Tue%Wed%Thu%Fri%Sat%Sun%@integer@@)$$@@)$$",
       132},
      {"array@@enum%Mon%Tue%Wed%Thu%Fri%Sat%Sun%@integer@@", 7},
      {"array@@constrange%1..10@record$$Name#(char)$Surname#(char)$Age#(integer)$IsHired#(boolean)$WorkHours#(array@@enum%Mon%"
       "Tue%Wed%Thu%Fri%Sat%Sun%@integer@@)$$@@",
       110},
      {"array@@enumrange%TDay%Wed..Sun@enum%Mon%Tue%Wed%Thu%Fri%Sat%Sun%@@", 5},
      {"array@@enum%Mon%Tue%Wed%Thu%Fri%Sat%Sun%@record$$Father#(record$$Name#(char)$Surname#(char)$Age#(integer)$IsHired#("
       "boolean)$WorkHours#(array@@enum%Mon%Tue%Wed%Thu%Fri%Sat%Sun%@integer@@)$$)$Mother#(record$$Name#(char)$Surname#(char)$"
       "Age#(integer)$IsHired#(boolean)$WorkHours#(array@@enum%Mon%Tue%Wed%Thu%Fri%Sat%Sun%@integer@@)$$)$Children#(array@@"
       "constrange%1..10@record$$Name#(char)$Surname#(char)$Age#(integer)$IsHired#(boolean)$WorkHours#(array@@enum%Mon%Tue%Wed%"
       "Thu%Fri%Sat%Sun%@integer@@)$$@@)$$@@",
       924},
      {"array@@integer@integer@@", 256},
      {"array@@char@integer@@", 256},
      {"array@@boolean@integer@@", 2},
      {"array@@constrange%false..true@integer@@", 2}};
  ASSERT_EQ(cfgGenerator.getTypeBytes(), expectedTypeBytes);

  const std::map<std::string, std::size_t> expectedProcedureOffsets{{"main", 0}, {"foo", 1}, {"bar", 2}};
}