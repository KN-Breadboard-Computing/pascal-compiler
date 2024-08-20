#include <fstream>
#include <iostream>

#include "gtest/gtest.h"

#include "../../src/ast/program_node.hpp"

bool parse(const std::string& inputFileName, std::vector<std::string>& errors, std::unique_ptr<ast::ProgramNode>& program);