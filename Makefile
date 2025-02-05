FF := flex
FFLAGS :=
BB := bison
BFLAGS :=
CXX := clang++
CXXFLAGS := -Wall -Wextra -pedantic -std=c++20 -O3 -g
FORMATTER = clang-format -i --style=file

SRCS := $(shell find src -name '*.cpp' | grep -v 'src/main.cpp')
ALL_PROJECT_FILES := $(shell find . -type f \( -name "*.cpp" -o -name "*.hpp" \) ! -path "src/out/*")

COMPILATION_EXAMPLE_DIR = compilation-process

all: lexer parser compiler format

test-all: clean-ast-test clean-bb-test clean-ssa-test clean-mc-test test-ast test-bb test-ssa test-mc run-ast-test run-bb-test run-ssa-test run-mc-test

clean: clean-compiler clean-ast-test clean-bb-test clean-ssa-test clean-mc-test

lexer:
	$(FF) $(FFLAGS) -o src/out/lexer.cpp --header-file=src/out/lexer.hpp src/lex.l

parser:
	$(BB) $(BFLAGS) -o src/out/parser.cpp --defines=src/out/parser.hpp -v src/yacc.y

compiler:
	$(CXX) $(CXXFLAGS) $(SRCS) src/main.cpp -o compiler

generate-example:
	./compiler $(COMPILATION_EXAMPLE_DIR)/test.pas $(COMPILATION_EXAMPLE_DIR)/test.ast $(COMPILATION_EXAMPLE_DIR)/test.bb $(COMPILATION_EXAMPLE_DIR)/test.ssa $(COMPILATION_EXAMPLE_DIR)/test.mc $(COMPILATION_EXAMPLE_DIR)/test.lr $(COMPILATION_EXAMPLE_DIR)/test.asm $(COMPILATION_EXAMPLE_DIR)/test.bin

test-ast:
	$(CXX) $(CXXFLAGS) $(SRCS) tests/ast_test.cpp tests/main.cpp -lgtest -o ast-test

test-bb:
	$(CXX) $(CXXFLAGS) $(SRCS) tests/bb_test.cpp tests/main.cpp -lgtest -o bb-test

test-ssa:
	$(CXX) $(CXXFLAGS) $(SRCS) tests/ssa_test.cpp tests/main.cpp -lgtest -o ssa-test

test-mc:
	$(CXX) $(CXXFLAGS) $(SRCS) tests/mc_test.cpp tests/main.cpp -lgtest -o mc-test

run-ast-test:
	@echo "=== Running AST Tests ==="
	@./ast-test | \
    tee >(grep '^Total' | awk '{print $$0}' >&2) | \
    grep -c 'OK' | \
  	awk '{print "Passed count:", $$1}'

run-bb-test:
	@echo "=== Running BB Tests  ==="
	@./bb-test | \
    tee >(grep '^Total' | awk '{print $$0}' >&2) | \
    grep -c 'OK' | \
  	awk '{print "Passed count:", $$1}'

run-ssa-test:
	@echo "=== Running SSA Tests ==="
	@./ssa-test | \
	tee >(grep '^Total' | awk '{print $$0}' >&2) | \
	grep -c 'OK' | \
  	awk '{print "Passed count:", $$1}'

run-mc-test:
	@echo "=== Running MC Tests  ==="
	@./mc-test | \
	tee >(grep '^Total' | awk '{print $$0}' >&2) | \
	grep -c 'OK' | \
  	awk '{print "Passed count:", $$1}'

test-end-to-end:
	./compiler $(COMPILATION_EXAMPLE_DIR)/test.pas $(COMPILATION_EXAMPLE_DIR)/test.ast $(COMPILATION_EXAMPLE_DIR)/test.bb $(COMPILATION_EXAMPLE_DIR)/test.ssa $(COMPILATION_EXAMPLE_DIR)/test.mc $(COMPILATION_EXAMPLE_DIR)/test.lr $(COMPILATION_EXAMPLE_DIR)/test.asm $(COMPILATION_EXAMPLE_DIR)/test.bin
	../emulator/build/cli_app/EmulatorCliApp -i ../computer/config/instructions.json -f $(COMPILATION_EXAMPLE_DIR)/test.bin

clean-compiler:
	rm -f compiler

clean-ast-test:
	rm -f ast-test

clean-bb-test:
	rm -f bb-test

clean-ssa-test:
	rm -f ssa-test

clean-mc-test:
	rm -f mc-test

format:
	$(FORMATTER) $(ALL_PROJECT_FILES)