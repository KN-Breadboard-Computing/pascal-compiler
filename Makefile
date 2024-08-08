FF := flex
FFLAGS :=
BB := bison
BFLAGS :=
CXX := clang++
CXXFLAGS := -Wall -Wextra -pedantic -std=c++20 -O3 -g

SRCS := $(shell find src -name '*.cpp')

TEST_DIR = tests
INPUT_DIR = $(TEST_DIR)/input
AST_DIR = $(TEST_DIR)/ast
BB_DIR = $(TEST_DIR)/bblock
ASM_DIR = $(TEST_DIR)/asm
INPUT_FILES = $(wildcard $(INPUT_DIR)/*.pas)

all: lexer parser compiler

lexer:
	$(FF) $(FFLAGS) -o out/lexer.cpp --header-file=out/lexer.hpp src/lex.l

parser:
	$(BB) $(BFLAGS) -o out/parser.cpp --defines=out/parser.hpp -v src/yacc.y

compiler:
	$(CXX) $(CXXFLAGS) out/*.cpp $(SRCS) -o compiler

test:
	@for input_file in $(INPUT_FILES); do \
		ast_file=$(AST_DIR)/`basename $$input_file .pas`.ast; \
		bblock_file=$(BB_DIR)/`basename $$input_file .pas`.bblock; \
		asm_file=$(ASM_DIR)/`basename $$input_file .pas`.asm; \
		./compiler $$input_file $$ast_file $$bblock_file $$asm_file; \
		echo ""; \
		echo ""; \
	done


clean:
	rm -f compiler