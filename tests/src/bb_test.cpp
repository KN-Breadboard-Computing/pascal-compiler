#include <fstream>
#include <iostream>

#include "gtest/gtest.h"

#include "../../src/ast/program_node.hpp"
#include "../../src/bblocks/bb_cfg_generator.hpp"

bool parse(const std::string& inputFileName, std::vector<std::string>& errors, std::unique_ptr<ast::ProgramNode>& program);

void validateBasicBlocks(const std::map<std::string, bblocks::BBControlFlowGraph> controlFlowGraphs,
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

TEST(toBbConversion, while1) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  parse("tests/internal/input_bb/while1.pas", errors, program);

  bblocks::BbCfgGenerator cfgGenerator;
  const std::map<std::string, bblocks::BBControlFlowGraph> cfg{cfgGenerator.generate(program)};
  validateBasicBlocks(cfg, "tests/internal/expected_bb/while1.bb");
}

TEST(toBbConversion, while2) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  parse("tests/internal/input_bb/while2.pas", errors, program);

  bblocks::BbCfgGenerator cfgGenerator;
  const std::map<std::string, bblocks::BBControlFlowGraph> cfg{cfgGenerator.generate(program)};
  validateBasicBlocks(cfg, "tests/internal/expected_bb/while2.bb");
}

TEST(toBbConversion, while3) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  parse("tests/internal/input_bb/while3.pas", errors, program);

  bblocks::BbCfgGenerator cfgGenerator;
  const std::map<std::string, bblocks::BBControlFlowGraph> cfg{cfgGenerator.generate(program)};
  validateBasicBlocks(cfg, "tests/internal/expected_bb/while3.bb");
}

TEST(toBbConversion, repeat1) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  parse("tests/internal/input_bb/repeat1.pas", errors, program);

  bblocks::BbCfgGenerator cfgGenerator;
  const std::map<std::string, bblocks::BBControlFlowGraph> cfg{cfgGenerator.generate(program)};
  validateBasicBlocks(cfg, "tests/internal/expected_bb/repeat1.bb");
}

TEST(toBbConversion, repeat2) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  parse("tests/internal/input_bb/repeat2.pas", errors, program);

  bblocks::BbCfgGenerator cfgGenerator;
  const std::map<std::string, bblocks::BBControlFlowGraph> cfg{cfgGenerator.generate(program)};
  validateBasicBlocks(cfg, "tests/internal/expected_bb/repeat2.bb");
}

TEST(toBbConversion, repeat3) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  parse("tests/internal/input_bb/repeat3.pas", errors, program);

  bblocks::BbCfgGenerator cfgGenerator;
  const std::map<std::string, bblocks::BBControlFlowGraph> cfg{cfgGenerator.generate(program)};
  validateBasicBlocks(cfg, "tests/internal/expected_bb/repeat3.bb");
}

TEST(toBbConversion, for1) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  parse("tests/internal/input_bb/for1.pas", errors, program);

  bblocks::BbCfgGenerator cfgGenerator;
  const std::map<std::string, bblocks::BBControlFlowGraph> cfg{cfgGenerator.generate(program)};
  validateBasicBlocks(cfg, "tests/internal/expected_bb/for1.bb");
}

TEST(toBbConversion, for2) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  parse("tests/internal/input_bb/for2.pas", errors, program);

  bblocks::BbCfgGenerator cfgGenerator;
  const std::map<std::string, bblocks::BBControlFlowGraph> cfg{cfgGenerator.generate(program)};
  validateBasicBlocks(cfg, "tests/internal/expected_bb/for2.bb");
}

TEST(toBbConversion, for3) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  parse("tests/internal/input_bb/for3.pas", errors, program);

  bblocks::BbCfgGenerator cfgGenerator;
  const std::map<std::string, bblocks::BBControlFlowGraph> cfg{cfgGenerator.generate(program)};
  validateBasicBlocks(cfg, "tests/internal/expected_bb/for3.bb");
}

TEST(toBbConversion, if1) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  parse("tests/internal/input_bb/if1.pas", errors, program);

  bblocks::BbCfgGenerator cfgGenerator;
  const std::map<std::string, bblocks::BBControlFlowGraph> cfg{cfgGenerator.generate(program)};
  validateBasicBlocks(cfg, "tests/internal/expected_bb/if1.bb");
}

TEST(toBbConversion, if2) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  parse("tests/internal/input_bb/if2.pas", errors, program);

  bblocks::BbCfgGenerator cfgGenerator;
  const std::map<std::string, bblocks::BBControlFlowGraph> cfg{cfgGenerator.generate(program)};
  validateBasicBlocks(cfg, "tests/internal/expected_bb/if2.bb");
}

TEST(toBbConversion, if3) {
  std::vector<std::string> errors;
  std::unique_ptr<ast::ProgramNode> program;
  parse("tests/internal/input_bb/if3.pas", errors, program);

  bblocks::BbCfgGenerator cfgGenerator;
  const std::map<std::string, bblocks::BBControlFlowGraph> cfg{cfgGenerator.generate(program)};
  validateBasicBlocks(cfg, "tests/internal/expected_bb/if3.bb");
}