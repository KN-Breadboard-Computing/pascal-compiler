#include <fstream>
#include <iostream>

#include "gtest/gtest.h"

#include "../src/ast/program_node.hpp"
#include "../src/bblocks/bb_cfg_generator.hpp"
#include "../src/bblocks/bb_ssa_generator.hpp"

using namespace ast;
using namespace bblocks;

bool parse(const std::string& inputFileName, std::vector<std::string>& errors, std::unique_ptr<ProgramNode>& program);

void validateSsaBlocks(const std::map<std::string, BBControlFlowGraph> controlFlowGraphs,
                       const std::string& expectedSsaFilename) {
  std::stringstream ssaStream;
  for (const auto& [name, cfg] : controlFlowGraphs) {
    ssaStream << name << ":\n" << cfg << std::endl;
  }

  std::ifstream expectedSsa{expectedSsaFilename};
  std::stringstream expectedSsaStream;
  expectedSsaStream << expectedSsa.rdbuf();

  ASSERT_EQ(ssaStream.str(), expectedSsaStream.str());
}

TEST(toSsaConversion, whileLoop) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;
  ASSERT_TRUE(parse("tests/input_ssa/while.pas", errors, program));

  BbCfgGenerator cfgGenerator;
  cfgGenerator.generate(program);
  cfgGenerator.optimize();

  BbSsaGenerator ssaGenerator;
  for (const auto& [name, cfg] : cfgGenerator.getControlFlowGraphs()) {
    ssaGenerator.toSsa(name, cfg);
  }

  validateSsaBlocks(ssaGenerator.getControlFlowGraphs(), "tests/expected_ssa/while.ssa");

  ssaGenerator.optimize();

  validateSsaBlocks(ssaGenerator.getControlFlowGraphs(), "tests/expected_ssa/while.ssa.opt");

  ssaGenerator.fromSsa();

  validateSsaBlocks(ssaGenerator.getControlFlowGraphs(), "tests/expected_ssa/while.ssa.merged");
}

TEST(toSsaConversion, forLoop) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;
  ASSERT_TRUE(parse("tests/input_ssa/for.pas", errors, program));

  BbCfgGenerator cfgGenerator;
  cfgGenerator.generate(program);
  cfgGenerator.optimize();

  BbSsaGenerator ssaGenerator;
  for (const auto& [name, cfg] : cfgGenerator.getControlFlowGraphs()) {
    ssaGenerator.toSsa(name, cfg);
  }

  validateSsaBlocks(ssaGenerator.getControlFlowGraphs(), "tests/expected_ssa/for.ssa");

  ssaGenerator.optimize();

  validateSsaBlocks(ssaGenerator.getControlFlowGraphs(), "tests/expected_ssa/for.ssa.opt");

  ssaGenerator.fromSsa();

  validateSsaBlocks(ssaGenerator.getControlFlowGraphs(), "tests/expected_ssa/for.ssa.merged");
}

TEST(toSsaConversion, ifCondition) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;
  ASSERT_TRUE(parse("tests/input_ssa/if.pas", errors, program));

  BbCfgGenerator cfgGenerator;
  cfgGenerator.generate(program);
  cfgGenerator.optimize();

  BbSsaGenerator ssaGenerator;
  for (const auto& [name, cfg] : cfgGenerator.getControlFlowGraphs()) {
    ssaGenerator.toSsa(name, cfg);
  }

  validateSsaBlocks(ssaGenerator.getControlFlowGraphs(), "tests/expected_ssa/if.ssa");

  ssaGenerator.optimize();

  validateSsaBlocks(ssaGenerator.getControlFlowGraphs(), "tests/expected_ssa/if.ssa.opt");

  ssaGenerator.fromSsa();

  validateSsaBlocks(ssaGenerator.getControlFlowGraphs(), "tests/expected_ssa/if.ssa.merged");
}

TEST(toSsaConversion, repeatLoop) {
  std::vector<std::string> errors;
  std::unique_ptr<ProgramNode> program;
  ASSERT_TRUE(parse("tests/input_ssa/repeat.pas", errors, program));

  BbCfgGenerator cfgGenerator;
  cfgGenerator.generate(program);
  cfgGenerator.optimize();

  BbSsaGenerator ssaGenerator;
  for (const auto& [name, cfg] : cfgGenerator.getControlFlowGraphs()) {
    ssaGenerator.toSsa(name, cfg);
  }

  validateSsaBlocks(ssaGenerator.getControlFlowGraphs(), "tests/expected_ssa/repeat.ssa");

  ssaGenerator.optimize();

  validateSsaBlocks(ssaGenerator.getControlFlowGraphs(), "tests/expected_ssa/repeat.ssa.opt");

  ssaGenerator.fromSsa();

  validateSsaBlocks(ssaGenerator.getControlFlowGraphs(), "tests/expected_ssa/repeat.ssa.merged");
}