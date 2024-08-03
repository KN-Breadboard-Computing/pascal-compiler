FF := flex
FFLAGS :=
BB := bison
BFLAGS :=
CXX := clang++
CXXFLAGS := -Wall -Wextra -pedantic -std=c++17 -O3 -g

TEST_DIR = tests
INPUT_DIR = $(TEST_DIR)/input
AST_DIR = $(TEST_DIR)/ast
ASM_DIR = $(TEST_DIR)/asm
INPUT_FILES = $(wildcard $(INPUT_DIR)/*.pas)

all: lexer parser compiler

lexer:
	$(FF) $(FFLAGS) -o out/lexer.cpp --header-file=out/lexer.hpp src/lex.l

parser:
	$(BB) $(BFLAGS) -o out/parser.cpp --defines=out/parser.hpp -v src/yacc.y

compiler:
	$(CXX) $(CXXFLAGS) out/*.cpp src/main.cpp src/ast/routine_decl_head_node.cpp -o compiler

test:
	@for input_file in $(INPUT_FILES); do \
		ast_file=$(AST_DIR)/`basename $$input_file .pas`.ast; \
		asm_file=$(ASM_DIR)/`basename $$input_file .pas`.asm; \
		./compiler $$input_file $$asm_file $$ast_file; \
		echo ""; \
		echo ""; \
	done


clean:
	rm -f compiler