FF := flex
FFLAGS :=
BB := bison
BFLAGS :=
CXX := clang++
CXXFLAGS := -Wall -Wextra -pedantic -std=c++20 -O3 -g
FORMATTER = clang-format -i --style=file

SRCS := $(shell find src -name '*.cpp' | grep -v 'src/main.cpp')

ALL_PROJECT_FILES := $(shell find . -type f \( -name "*.cpp" -o -name "*.hpp" \) ! -path "src/out/*" ! -path "*/tests/json.hpp")

COMPILER_CORE_OBJECTS_DIR = core-objects
COMPILATION_EXAMPLE_DIR = compilation-process

all: lexer parser core compiler format

test: clean-ast-test clean-bb-test clean-ssa-test clean-mc-test core test-ast test-bb test-ssa test-mc run-ast-test run-bb-test run-ssa-test run-mc-test

clean: clean-compiler clean-ast-test clean-bb-test clean-ssa-test clean-mc-test

lexer:
	$(FF) $(FFLAGS) -o src/out/lexer.cpp --header-file=src/out/lexer.hpp src/lex.l

parser:
	$(BB) $(BFLAGS) -o src/out/parser.cpp --defines=src/out/parser.hpp -v src/yacc.y

core:
	rm -f *.o
	$(CXX) $(CXXFLAGS) -c $(SRCS)
	rm -rf $(COMPILER_CORE_OBJECTS_DIR)
	mkdir -p $(COMPILER_CORE_OBJECTS_DIR)
	mv *.o $(COMPILER_CORE_OBJECTS_DIR)

compiler:
	$(CXX) $(CXXFLAGS) $(COMPILER_CORE_OBJECTS_DIR)/*.o src/main.cpp -o compiler

generate-example:
	./compiler $(COMPILATION_EXAMPLE_DIR)/test.pas $(COMPILATION_EXAMPLE_DIR)/test.ast $(COMPILATION_EXAMPLE_DIR)/test.bb $(COMPILATION_EXAMPLE_DIR)/test.ssa $(COMPILATION_EXAMPLE_DIR)/test.mc $(COMPILATION_EXAMPLE_DIR)/test.lr $(COMPILATION_EXAMPLE_DIR)/test.asm $(COMPILATION_EXAMPLE_DIR)/test.bin

debug-example:
	valgrind ./compiler $(COMPILATION_EXAMPLE_DIR)/test.pas $(COMPILATION_EXAMPLE_DIR)/test.ast $(COMPILATION_EXAMPLE_DIR)/test.bb $(COMPILATION_EXAMPLE_DIR)/test.ssa $(COMPILATION_EXAMPLE_DIR)/test.mc $(COMPILATION_EXAMPLE_DIR)/test.lr $(COMPILATION_EXAMPLE_DIR)/test.asm $(COMPILATION_EXAMPLE_DIR)/test.bin

test-ast:
	$(CXX) $(CXXFLAGS) $(COMPILER_CORE_OBJECTS_DIR)/*.o tests/ast_test.cpp tests/main.cpp -lgtest -o ast-test
	./ast-test

test-bb:
	$(CXX) $(CXXFLAGS) $(COMPILER_CORE_OBJECTS_DIR)/*.o tests/bb_test.cpp tests/main.cpp -lgtest -o bb-test
	./bb-test

test-ssa:
	$(CXX) $(CXXFLAGS) $(COMPILER_CORE_OBJECTS_DIR)/*.o tests/ssa_test.cpp tests/main.cpp -lgtest -o ssa-test
	./ssa-test

test-mc:
	$(CXX) $(CXXFLAGS) $(COMPILER_CORE_OBJECTS_DIR)/*.o tests/mc_test.cpp tests/main.cpp -lgtest -o mc-test
	./mc-test

test-ssa-end-to-end:
	$(CXX) $(CXXFLAGS) $(COMPILER_CORE_OBJECTS_DIR)/*.o tests/ssa_end_to_end_test.cpp ../emulator/src/emulator.c ../emulator/src/config.c ../emulator/src/cJSON.c tests/main.cpp -lgtest -o ssa-end-to-end-test
	./ssa-end-to-end-test

test-program-end-to-end:
	$(CXX) $(CXXFLAGS) $(COMPILER_CORE_OBJECTS_DIR)/*.o tests/program_end_to_end_test.cpp ../emulator/src/emulator.c ../emulator/src/config.c ../emulator/src/cJSON.c tests/main.cpp -lgtest -o program-end-to-end-test
	./program-end-to-end-test

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

run-ssa-end-to-end-test:
	@echo "=== Running SSA End-to-End Tests ==="
	@./ssa-end-to-end-test | \
	tee >(grep '^Total' | awk '{print $$0}' >&2) | \
	grep -c 'OK' | \
  	awk '{print "Passed count:", $$1}'

run-program-end-to-end-test:
	@echo "=== Running Program End-to-End Tests ==="
	@./program-end-to-end-test | \
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

clean-ssa-end-to-end-test:
	rm -f ssa-end-to-end-test

clean-program-end-to-end-test:
	rm -f program-end-to-end-test

format:
	$(FORMATTER) $(ALL_PROJECT_FILES)

playground:
	$(CXX) $(CXXFLAGS) $(COMPILER_CORE_OBJECTS_DIR)/*.o tests/playground.cpp -o playground
	./playground

debug-playground:
	$(CXX) $(CXXFLAGS) $(COMPILER_CORE_OBJECTS_DIR)/*.o tests/playground.cpp -o playground
	valgrind ./playground

clean-playground:
	rm -f playground


.PHONY: core playground debug-playground format