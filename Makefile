FF := flex
FFLAGS :=
BB := bison
BFLAGS :=
CXX := clang++
CXXFLAGS := -Wall -Wextra -pedantic -std=c++17 -O3 -g

SRCS := $(wildcard src/ast/*.cpp)
OBJS := $(SRCS:.cpp=.o)

all: clean lexer parser compiler

lexer:
	$(FF) $(FFLAGS) -o out/lexer.cpp --header-file=out/lexer.hpp src/lex.l

parser:
	$(BB) $(BFLAGS) -o out/parser.cpp --defines=out/parser.hpp -v src/yacc.y

compiler:
	$(CXX) $(CXXFLAGS) out/*.cpp src/main.cpp -o compiler

clean:
	rm -f compiler