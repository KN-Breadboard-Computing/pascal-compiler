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
EMULATOR_CORE_OBJECTS_DIR = emulator-objects
COMPILATION_EXAMPLE_DIR = compilation-process

all: lexer parser core compiler format

test: clean-ast-test clean-bb-test clean-ssa-test clean-mc-test clean-ssa-end-to-end-test clean-program-end-to-end-test core test-ast test-bb test-ssa test-mc test-ssa-end-to-end test-program-end-to-end run-ast-test run-bb-test run-ssa-test run-mc-test run-ssa-end-to-end-test run-program-end-to-end-test

clean: clean-compiler clean-ast-test clean-bb-test clean-ssa-test clean-mc-test clean-ssa-end-to-end-test clean-program-end-to-end-test clean-playground

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

emulator-core:
	rm -f *.o
	$(CXX) $(CXXFLAGS) -c ../emulator/src/emulator.c ../emulator/src/config.c ../emulator/src/cJSON.c
	rm -rf $(EMULATOR_CORE_OBJECTS_DIR)
	mkdir -p $(EMULATOR_CORE_OBJECTS_DIR)
	mv *.o $(EMULATOR_CORE_OBJECTS_DIR)

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
	$(CXX) $(CXXFLAGS) $(COMPILER_CORE_OBJECTS_DIR)/*.o tests/mc_mov_test.cpp tests/main.cpp -lgtest -o mc-mov-test
	$(CXX) $(CXXFLAGS) $(COMPILER_CORE_OBJECTS_DIR)/*.o tests/mc_unary_test.cpp tests/main.cpp -lgtest -o mc-unary-test
	./mc-mov-test
	./mc-unary-test

test-ssa-end-to-end:
	$(CXX) $(CXXFLAGS) $(COMPILER_CORE_OBJECTS_DIR)/*.o $(EMULATOR_CORE_OBJECTS_DIR)/*.o tests/ssa_mov_end_to_end_test.cpp tests/main.cpp -lgtest -o ssa-mov-end-to-end-test
	$(CXX) $(CXXFLAGS) $(COMPILER_CORE_OBJECTS_DIR)/*.o $(EMULATOR_CORE_OBJECTS_DIR)/*.o tests/ssa_unary_end_to_end_test.cpp tests/main.cpp -lgtest -o ssa-unary-end-to-end-test
	./ssa-mov-end-to-end-test
	./ssa-unary-end-to-end-test

test-program-end-to-end:
	$(CXX) $(CXXFLAGS) $(COMPILER_CORE_OBJECTS_DIR)/*.o $(EMULATOR_CORE_OBJECTS_DIR)/*.o tests/program_end_to_end_test.cpp tests/main.cpp -lgtest -o program-end-to-end-test
	./program-end-to-end-test

run-ast-test:
	@echo "=== Running AST Tests ==="
	@./ast-test | tee >(grep '^Total' >&2) | grep -c 'OK' | awk '{print "Passed count:", $$1}'

run-bb-test:
	@echo "=== Running BB Tests  ==="
	@./bb-test | tee >(grep '^Total' >&2) | grep -c 'OK' | awk '{print "Passed count:", $$1}'

run-ssa-test:
	@echo "=== Running SSA Tests ==="
	@./ssa-test | tee >(grep '^Total' >&2) | grep -c 'OK' | awk '{print "Passed count:", $$1}'

run-mc-test:
	@echo "=== Running MC MOV Tests  ==="
	@./mc-mov-test | tee >(grep '^Total' >&2) | grep -c 'OK' | awk '{print "Passed count:", $$1}'
	@echo -e "\n=== Running MC UNARY Tests  ==="
	@./mc-unary-test | tee >(grep '^Total' >&2) | grep -c 'OK' | awk '{print "Passed count:", $$1}'

run-ssa-end-to-end-test:
	@echo "=== Running SSA MOV End-to-End Tests ==="
	@./ssa-mov-end-to-end-test | tee >(grep '^Total' >&2) | grep -c 'OK' | awk '{print "Passed count:", $$1}'
	@echo -e "\n=== Running SSA UNARY End-to-End Tests ==="
	@./ssa-unary-end-to-end-test | tee >(grep '^Total' >&2) | grep -c 'OK' | awk '{print "Passed count:", $$1}'

run-program-end-to-end-test:
	@echo "=== Running Program End-to-End Tests ==="
	@./program-end-to-end-test | tee >(grep '^Total' >&2) | grep -c 'OK' | awk '{print "Passed count:", $$1}'

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
	rm -f mc-mov-test
	rm -f mc-unary-test

clean-ssa-end-to-end-test:
	rm -f ssa-mov-end-to-end-test
	rm -f ssa-unary-end-to-end-test

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