/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* First part of user prologue.  */
#line 1 "src/yacc.y"

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "../ast/arguments_list_node.hpp"
#include "../ast/array_type_node.hpp"
#include "../ast/assign_node.hpp"
#include "../ast/ast_node.hpp"
#include "../ast/break_node.hpp"
#include "../ast/call_node.hpp"
#include "../ast/case_node.hpp"
#include "../ast/compound_statement_node.hpp"
#include "../ast/constant_node.hpp"
#include "../ast/continue_node.hpp"
#include "../ast/expression_node.hpp"
#include "../ast/for_node.hpp"
#include "../ast/goto_node.hpp"
#include "../ast/identifier_node.hpp"
#include "../ast/if_node.hpp"
#include "../ast/params_group_node.hpp"
#include "../ast/params_node.hpp"
#include "../ast/program_node.hpp"
#include "../ast/record_type_node.hpp"
#include "../ast/repeat_node.hpp"
#include "../ast/routine_body_node.hpp"
#include "../ast/routine_decl_head_node.hpp"
#include "../ast/simple_type_node.hpp"
#include "../ast/statement_node.hpp"
#include "../ast/type_node.hpp"
#include "../ast/while_node.hpp"

#include "../context/context.hpp"

#undef YACC_DEBUG
#undef YACC_ENABLE_GOTO

Context* ctx = Context::getInstance();

ast::ProgramNode* resultAst;
std::vector<std::string> parsingErrors;
bool fatalError{false};

static void yyerror(const char* msg);
static int yyparse(void);
int yylex(void);

extern FILE* yyin;
extern uint64_t linesCounter;

bool isChar(const std::string& expr);
bool isInteger(const std::string& expr);
bool isBoolean(const std::string& expr);

bool nameAlreadyUsed(std::string name);
bool saveType(ast::IdentifierNode* typeName, const std::string& typeDef);
bool saveConstant(ast::IdentifierNode* constName, const std::string& constValue, const std::string& typeDef);
bool saveVariables(std::vector<ast::IdentifierNode*>* varNames, const std::string& typeDef);
bool saveRoutine(ast::RoutineDeclarationNode* routineDef, bool isForward);

bool isBasicType(const std::string& type);
bool isBasicOrEnumType(const std::string& type);
bool isBasicOrEnumOrArrayOrRecordType(const std::string& type);
bool isRangeType(const std::string& type);
bool isInEnum(const std::string& enumElement, const std::string& enumType);
bool isInAnyEnum(const std::string& enumElement);
bool isEnumSubRangeType(const std::string& enumElementPos, const std::string& enumType, const std::string& begin, const std::string& end);
bool isLeftValueCompatible(ast::ExpressionNode* expr);

bool isArrayIndexCompatible(const std::string& arrayType, ast::ExpressionNode* index);
bool isRecordFieldCompatible(const std::string& recordType, ast::IdentifierNode* field);
bool isFunctionArgumentsCompatible(const std::vector<LookupTable::ArgumentInfo>& expectedArgs, const std::vector<ast::ExpressionNode*>& givenArgs);
bool hasReturnValue(ast::RoutineNode* function, const std::string& functionName);
bool variableIsReassignedS(const std::string& varName, ast::StatementNode* stmt);
bool variableIsReassignedE(const std::string& varName, ast::ExpressionNode* expr);

std::string getArrayElementType(const std::string& arrayType);
std::string getRecordFieldType(const std::string& recordType, const std::string& field);

#line 156 "src/out/parser.cpp"

#ifndef YY_CAST
#ifdef __cplusplus
#define YY_CAST(Type, Val) static_cast<Type>(Val)
#define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type>(Val)
#else
#define YY_CAST(Type, Val) ((Type)(Val))
#define YY_REINTERPRET_CAST(Type, Val) ((Type)(Val))
#endif
#endif
#ifndef YY_NULLPTR
#if defined __cplusplus
#if 201103L <= __cplusplus
#define YY_NULLPTR nullptr
#else
#define YY_NULLPTR 0
#endif
#else
#define YY_NULLPTR ((void*)0)
#endif
#endif

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t {
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                 /* "end of file"  */
  YYSYMBOL_YYerror = 1,               /* error  */
  YYSYMBOL_YYUNDEF = 2,               /* "invalid token"  */
  YYSYMBOL_PROGRAM = 3,               /* PROGRAM  */
  YYSYMBOL_FUNCTION = 4,              /* FUNCTION  */
  YYSYMBOL_PROCEDURE = 5,             /* PROCEDURE  */
  YYSYMBOL_CONST = 6,                 /* CONST  */
  YYSYMBOL_TYPE = 7,                  /* TYPE  */
  YYSYMBOL_VAR = 8,                   /* VAR  */
  YYSYMBOL_BBEGIN = 9,                /* BBEGIN  */
  YYSYMBOL_END = 10,                  /* END  */
  YYSYMBOL_IDENT_NAME = 11,           /* IDENT_NAME  */
  YYSYMBOL_INTEGER = 12,              /* INTEGER  */
  YYSYMBOL_BOOLEAN = 13,              /* BOOLEAN  */
  YYSYMBOL_CHAR = 14,                 /* CHAR  */
  YYSYMBOL_STRING = 15,               /* STRING  */
  YYSYMBOL_TRUE = 16,                 /* TRUE  */
  YYSYMBOL_FALSE = 17,                /* FALSE  */
  YYSYMBOL_MAXINT = 18,               /* MAXINT  */
  YYSYMBOL_READ = 19,                 /* READ  */
  YYSYMBOL_READLN = 20,               /* READLN  */
  YYSYMBOL_WRITE = 21,                /* WRITE  */
  YYSYMBOL_WRITELN = 22,              /* WRITELN  */
  YYSYMBOL_MEMORYREAD = 23,           /* MEMORYREAD  */
  YYSYMBOL_MEMORYWRITE = 24,          /* MEMORYWRITE  */
  YYSYMBOL_STACKREAD = 25,            /* STACKREAD  */
  YYSYMBOL_STACKWRITE = 26,           /* STACKWRITE  */
  YYSYMBOL_ABS = 27,                  /* ABS  */
  YYSYMBOL_CHR = 28,                  /* CHR  */
  YYSYMBOL_ODD = 29,                  /* ODD  */
  YYSYMBOL_ORD = 30,                  /* ORD  */
  YYSYMBOL_PRED = 31,                 /* PRED  */
  YYSYMBOL_SUCC = 32,                 /* SUCC  */
  YYSYMBOL_TOINT = 33,                /* TOINT  */
  YYSYMBOL_TOCHAR = 34,               /* TOCHAR  */
  YYSYMBOL_TOBOOL = 35,               /* TOBOOL  */
  YYSYMBOL_IF = 36,                   /* IF  */
  YYSYMBOL_THEN = 37,                 /* THEN  */
  YYSYMBOL_ELSE = 38,                 /* ELSE  */
  YYSYMBOL_REPEAT = 39,               /* REPEAT  */
  YYSYMBOL_UNTIL = 40,                /* UNTIL  */
  YYSYMBOL_WHILE = 41,                /* WHILE  */
  YYSYMBOL_DO = 42,                   /* DO  */
  YYSYMBOL_CASE = 43,                 /* CASE  */
  YYSYMBOL_TO = 44,                   /* TO  */
  YYSYMBOL_DOWNTO = 45,               /* DOWNTO  */
  YYSYMBOL_FOR = 46,                  /* FOR  */
  YYSYMBOL_EQUAL = 47,                /* EQUAL  */
  YYSYMBOL_UNEQUAL = 48,              /* UNEQUAL  */
  YYSYMBOL_GE = 49,                   /* GE  */
  YYSYMBOL_GT = 50,                   /* GT  */
  YYSYMBOL_LE = 51,                   /* LE  */
  YYSYMBOL_LT = 52,                   /* LT  */
  YYSYMBOL_ASSIGN = 53,               /* ASSIGN  */
  YYSYMBOL_PLUS = 54,                 /* PLUS  */
  YYSYMBOL_MINUS = 55,                /* MINUS  */
  YYSYMBOL_MUL = 56,                  /* MUL  */
  YYSYMBOL_DIV = 57,                  /* DIV  */
  YYSYMBOL_OR = 58,                   /* OR  */
  YYSYMBOL_AND = 59,                  /* AND  */
  YYSYMBOL_NOT = 60,                  /* NOT  */
  YYSYMBOL_MOD = 61,                  /* MOD  */
  YYSYMBOL_LB = 62,                   /* LB  */
  YYSYMBOL_RB = 63,                   /* RB  */
  YYSYMBOL_LP = 64,                   /* LP  */
  YYSYMBOL_RP = 65,                   /* RP  */
  YYSYMBOL_SEMICOLON = 66,            /* SEMICOLON  */
  YYSYMBOL_DOT = 67,                  /* DOT  */
  YYSYMBOL_DOUBLEDOT = 68,            /* DOUBLEDOT  */
  YYSYMBOL_COMMA = 69,                /* COMMA  */
  YYSYMBOL_COLON = 70,                /* COLON  */
  YYSYMBOL_INT_TYPE = 71,             /* INT_TYPE  */
  YYSYMBOL_BOOL_TYPE = 72,            /* BOOL_TYPE  */
  YYSYMBOL_CHAR_TYPE = 73,            /* CHAR_TYPE  */
  YYSYMBOL_ARRAY = 74,                /* ARRAY  */
  YYSYMBOL_OF = 75,                   /* OF  */
  YYSYMBOL_RECORD = 76,               /* RECORD  */
  YYSYMBOL_GOTO = 77,                 /* GOTO  */
  YYSYMBOL_BREAK = 78,                /* BREAK  */
  YYSYMBOL_CONTINUE = 79,             /* CONTINUE  */
  YYSYMBOL_OTHERWISE = 80,            /* OTHERWISE  */
  YYSYMBOL_ERROR = 81,                /* ERROR  */
  YYSYMBOL_YYACCEPT = 82,             /* $accept  */
  YYSYMBOL_program = 83,              /* program  */
  YYSYMBOL_routine = 84,              /* routine  */
  YYSYMBOL_routine_head = 85,         /* routine_head  */
  YYSYMBOL_routine_part = 86,         /* routine_part  */
  YYSYMBOL_fun_decl = 87,             /* fun_decl  */
  YYSYMBOL_fun_head = 88,             /* fun_head  */
  YYSYMBOL_proc_decl = 89,            /* proc_decl  */
  YYSYMBOL_proc_head = 90,            /* proc_head  */
  YYSYMBOL_params = 91,               /* params  */
  YYSYMBOL_params_decl = 92,          /* params_decl  */
  YYSYMBOL_params_type = 93,          /* params_type  */
  YYSYMBOL_var_part = 94,             /* var_part  */
  YYSYMBOL_var_decl_list = 95,        /* var_decl_list  */
  YYSYMBOL_var_decl = 96,             /* var_decl  */
  YYSYMBOL_const_part = 97,           /* const_part  */
  YYSYMBOL_const_expr_list = 98,      /* const_expr_list  */
  YYSYMBOL_const_expr = 99,           /* const_expr  */
  YYSYMBOL_const_value = 100,         /* const_value  */
  YYSYMBOL_type_part = 101,           /* type_part  */
  YYSYMBOL_type_decl_list = 102,      /* type_decl_list  */
  YYSYMBOL_type_def = 103,            /* type_def  */
  YYSYMBOL_type_decl = 104,           /* type_decl  */
  YYSYMBOL_record_type_decl = 105,    /* record_type_decl  */
  YYSYMBOL_field_decl_list = 106,     /* field_decl_list  */
  YYSYMBOL_field_decl = 107,          /* field_decl  */
  YYSYMBOL_array_type_decl = 108,     /* array_type_decl  */
  YYSYMBOL_simple_type = 109,         /* simple_type  */
  YYSYMBOL_name_list = 110,           /* name_list  */
  YYSYMBOL_identifier = 111,          /* identifier  */
  YYSYMBOL_routine_body = 112,        /* routine_body  */
  YYSYMBOL_compound_stmt = 113,       /* compound_stmt  */
  YYSYMBOL_compound_loop_stmt = 114,  /* compound_loop_stmt  */
  YYSYMBOL_stmt_list = 115,           /* stmt_list  */
  YYSYMBOL_loop_stmt_list = 116,      /* loop_stmt_list  */
  YYSYMBOL_stmt = 117,                /* stmt  */
  YYSYMBOL_loop_stmt = 118,           /* loop_stmt  */
  YYSYMBOL_no_label_stmt = 119,       /* no_label_stmt  */
  YYSYMBOL_no_label_loop_stmt = 120,  /* no_label_loop_stmt  */
  YYSYMBOL_assign_stmt = 121,         /* assign_stmt  */
  YYSYMBOL_goto_stmt = 122,           /* goto_stmt  */
  YYSYMBOL_if_stmt = 123,             /* if_stmt  */
  YYSYMBOL_if_loop_stmt = 124,        /* if_loop_stmt  */
  YYSYMBOL_else_clause = 125,         /* else_clause  */
  YYSYMBOL_else_loop_clause = 126,    /* else_loop_clause  */
  YYSYMBOL_repeat_stmt = 127,         /* repeat_stmt  */
  YYSYMBOL_while_stmt = 128,          /* while_stmt  */
  YYSYMBOL_case_stmt = 129,           /* case_stmt  */
  YYSYMBOL_case_loop_stmt = 130,      /* case_loop_stmt  */
  YYSYMBOL_case_expr_list = 131,      /* case_expr_list  */
  YYSYMBOL_case_loop_expr_list = 132, /* case_loop_expr_list  */
  YYSYMBOL_case_expr = 133,           /* case_expr  */
  YYSYMBOL_case_loop_expr = 134,      /* case_loop_expr  */
  YYSYMBOL_for_stmt = 135,            /* for_stmt  */
  YYSYMBOL_for_head = 136,            /* for_head  */
  YYSYMBOL_proc_stmt = 137,           /* proc_stmt  */
  YYSYMBOL_args_list = 138,           /* args_list  */
  YYSYMBOL_expression = 139,          /* expression  */
  YYSYMBOL_expr = 140,                /* expr  */
  YYSYMBOL_term = 141,                /* term  */
  YYSYMBOL_factor = 142,              /* factor  */
  YYSYMBOL_lvalue = 143               /* lvalue  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;

#ifdef short
#undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
#include <limits.h> /* INFRINGES ON USER NAME SPACE */
#if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#define YY_STDINT_H
#endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
#undef UINT_LEAST8_MAX
#undef UINT_LEAST16_MAX
#define UINT_LEAST8_MAX 255
#define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
#if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#define YYPTRDIFF_T __PTRDIFF_TYPE__
#define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
#elif defined PTRDIFF_MAX
#ifndef ptrdiff_t
#include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#endif
#define YYPTRDIFF_T ptrdiff_t
#define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
#else
#define YYPTRDIFF_T long
#define YYPTRDIFF_MAXIMUM LONG_MAX
#endif
#endif

#ifndef YYSIZE_T
#ifdef __SIZE_TYPE__
#define YYSIZE_T __SIZE_TYPE__
#elif defined size_t
#define YYSIZE_T size_t
#elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#define YYSIZE_T size_t
#else
#define YYSIZE_T unsigned
#endif
#endif

#define YYSIZE_MAXIMUM YY_CAST(YYPTRDIFF_T, (YYPTRDIFF_MAXIMUM < YY_CAST(YYSIZE_T, -1) ? YYPTRDIFF_MAXIMUM : YY_CAST(YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST(YYPTRDIFF_T, sizeof(X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
#if defined YYENABLE_NLS && YYENABLE_NLS
#if ENABLE_NLS
#include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#define YY_(Msgid) dgettext("bison-runtime", Msgid)
#endif
#endif
#ifndef YY_
#define YY_(Msgid) Msgid
#endif
#endif

#ifndef YY_ATTRIBUTE_PURE
#if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#define YY_ATTRIBUTE_PURE __attribute__((__pure__))
#else
#define YY_ATTRIBUTE_PURE
#endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
#if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#define YY_ATTRIBUTE_UNUSED __attribute__((__unused__))
#else
#define YY_ATTRIBUTE_UNUSED
#endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if !defined lint || defined __GNUC__
#define YY_USE(E) ((void)(E))
#else
#define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && !defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
#if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wuninitialized\"")
#else
#define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wuninitialized\"") _Pragma("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
#endif
#define YY_IGNORE_MAYBE_UNINITIALIZED_END _Pragma("GCC diagnostic pop")
#else
#define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
#define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
#define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
#define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && !defined __ICC && 6 <= __GNUC__
#define YY_IGNORE_USELESS_CAST_BEGIN _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wuseless-cast\"")
#define YY_IGNORE_USELESS_CAST_END _Pragma("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
#define YY_IGNORE_USELESS_CAST_BEGIN
#define YY_IGNORE_USELESS_CAST_END
#endif

#define YY_ASSERT(E) ((void)(0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

#ifdef YYSTACK_USE_ALLOCA
#if YYSTACK_USE_ALLOCA
#ifdef __GNUC__
#define YYSTACK_ALLOC __builtin_alloca
#elif defined __BUILTIN_VA_ARG_INCR
#include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#elif defined _AIX
#define YYSTACK_ALLOC __alloca
#elif defined _MSC_VER
#include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#define alloca _alloca
#else
#define YYSTACK_ALLOC alloca
#if !defined _ALLOCA_H && !defined EXIT_SUCCESS
#include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
/* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif
#endif
#endif
#endif
#endif

#ifdef YYSTACK_ALLOC
/* Pacify GCC's 'empty if-body' warning.  */
#define YYSTACK_FREE(Ptr) \
  do { /* empty */        \
    ;                     \
  } while (0)
#ifndef YYSTACK_ALLOC_MAXIMUM
/* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#endif
#else
#define YYSTACK_ALLOC YYMALLOC
#define YYSTACK_FREE YYFREE
#ifndef YYSTACK_ALLOC_MAXIMUM
#define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#endif
#if (defined __cplusplus && !defined EXIT_SUCCESS && !((defined YYMALLOC || defined malloc) && (defined YYFREE || defined free)))
#include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif
#endif
#ifndef YYMALLOC
#define YYMALLOC malloc
#if !defined malloc && !defined EXIT_SUCCESS
void* malloc(YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#endif
#endif
#ifndef YYFREE
#define YYFREE free
#if !defined free && !defined EXIT_SUCCESS
void free(void*); /* INFRINGES ON USER NAME SPACE */
#endif
#endif
#endif
#endif /* !defined yyoverflow */

#if (!defined yyoverflow && (!defined __cplusplus || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc {
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
#define YYSTACK_GAP_MAXIMUM (YYSIZEOF(union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
#define YYSTACK_BYTES(N) ((N) * (YYSIZEOF(yy_state_t) + YYSIZEOF(YYSTYPE)) + YYSTACK_GAP_MAXIMUM)

#define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
#define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
  do {                                                                 \
    YYPTRDIFF_T yynewbytes;                                            \
    YYCOPY(&yyptr->Stack_alloc, Stack, yysize);                        \
    Stack = &yyptr->Stack_alloc;                                       \
    yynewbytes = yystacksize * YYSIZEOF(*Stack) + YYSTACK_GAP_MAXIMUM; \
    yyptr += yynewbytes / YYSIZEOF(*yyptr);                            \
  } while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
#ifndef YYCOPY
#if defined __GNUC__ && 1 < __GNUC__
#define YYCOPY(Dst, Src, Count) __builtin_memcpy(Dst, Src, YY_CAST(YYSIZE_T, (Count)) * sizeof(*(Src)))
#else
#define YYCOPY(Dst, Src, Count)         \
  do {                                  \
    YYPTRDIFF_T yyi;                    \
    for (yyi = 0; yyi < (Count); yyi++) \
      (Dst)[yyi] = (Src)[yyi];          \
  } while (0)
#endif
#endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL 4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST 1013

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS 82
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS 62
/* YYNRULES -- Number of rules.  */
#define YYNRULES 183
/* YYNSTATES -- Number of states.  */
#define YYNSTATES 356

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK 336

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX) (0 <= (YYX) && (YYX) <= YYMAXUTOK ? YY_CAST(yysymbol_kind_t, yytranslate[YYX]) : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] = {0,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
                                          2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
                                          2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
                                          2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
                                          2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
                                          2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
                                          39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] = {0,    238,  238,  249,  261,  273,  287,  297,  307,  315,  328,  341,  354,  369,  388,  408,  428,  450,  507,  520,  534,  548,  564,  595,  604,  614,  623,  634,  655,  678,  686,
                                       696,  705,  716,  742,  771,  779,  789,  798,  809,  841,  876,  884,  892,  901,  912,  920,  928,  936,  946,  954,  964,  973,  984,  1004, 1027, 1035, 1043, 1053, 1076, 1085, 1096,
                                       1103, 1113, 1193, 1201, 1209, 1217, 1225, 1233, 1241, 1251, 1260, 1271, 1282, 1292, 1300, 1311, 1319, 1330, 1338, 1347, 1359, 1367, 1376, 1388, 1403, 1413, 1428, 1438, 1446, 1454, 1468,
                                       1476, 1484, 1492, 1500, 1508, 1518, 1526, 1534, 1542, 1550, 1558, 1566, 1574, 1582, 1590, 1598, 1608, 1631, 1641, 1656, 1674, 1689, 1707, 1715, 1725, 1733, 1743, 1758, 1766, 1783, 1838,
                                       1893, 1902, 1913, 1922, 1933, 1941, 1951, 1959, 1969, 1988, 2011, 2036, 2056, 2076, 2099, 2107, 2129, 2137, 2160, 2197, 2229, 2266, 2300, 2309, 2320, 2335, 2350, 2365, 2380, 2395, 2411,
                                       2420, 2435, 2450, 2465, 2475, 2490, 2505, 2520, 2535, 2545, 2562, 2570, 2580, 2588, 2603, 2618, 2641, 2664, 2687, 2710, 2733, 2756, 2779, 2802, 2827, 2857, 2878, 2899, 2915};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST(yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char* yysymbol_name(yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char* const yytname[] = {"\"end of file\"",
                                      "error",
                                      "\"invalid token\"",
                                      "PROGRAM",
                                      "FUNCTION",
                                      "PROCEDURE",
                                      "CONST",
                                      "TYPE",
                                      "VAR",
                                      "BBEGIN",
                                      "END",
                                      "IDENT_NAME",
                                      "INTEGER",
                                      "BOOLEAN",
                                      "CHAR",
                                      "STRING",
                                      "TRUE",
                                      "FALSE",
                                      "MAXINT",
                                      "READ",
                                      "READLN",
                                      "WRITE",
                                      "WRITELN",
                                      "MEMORYREAD",
                                      "MEMORYWRITE",
                                      "STACKREAD",
                                      "STACKWRITE",
                                      "ABS",
                                      "CHR",
                                      "ODD",
                                      "ORD",
                                      "PRED",
                                      "SUCC",
                                      "TOINT",
                                      "TOCHAR",
                                      "TOBOOL",
                                      "IF",
                                      "THEN",
                                      "ELSE",
                                      "REPEAT",
                                      "UNTIL",
                                      "WHILE",
                                      "DO",
                                      "CASE",
                                      "TO",
                                      "DOWNTO",
                                      "FOR",
                                      "EQUAL",
                                      "UNEQUAL",
                                      "GE",
                                      "GT",
                                      "LE",
                                      "LT",
                                      "ASSIGN",
                                      "PLUS",
                                      "MINUS",
                                      "MUL",
                                      "DIV",
                                      "OR",
                                      "AND",
                                      "NOT",
                                      "MOD",
                                      "LB",
                                      "RB",
                                      "LP",
                                      "RP",
                                      "SEMICOLON",
                                      "DOT",
                                      "DOUBLEDOT",
                                      "COMMA",
                                      "COLON",
                                      "INT_TYPE",
                                      "BOOL_TYPE",
                                      "CHAR_TYPE",
                                      "ARRAY",
                                      "OF",
                                      "RECORD",
                                      "GOTO",
                                      "BREAK",
                                      "CONTINUE",
                                      "OTHERWISE",
                                      "ERROR",
                                      "$accept",
                                      "program",
                                      "routine",
                                      "routine_head",
                                      "routine_part",
                                      "fun_decl",
                                      "fun_head",
                                      "proc_decl",
                                      "proc_head",
                                      "params",
                                      "params_decl",
                                      "params_type",
                                      "var_part",
                                      "var_decl_list",
                                      "var_decl",
                                      "const_part",
                                      "const_expr_list",
                                      "const_expr",
                                      "const_value",
                                      "type_part",
                                      "type_decl_list",
                                      "type_def",
                                      "type_decl",
                                      "record_type_decl",
                                      "field_decl_list",
                                      "field_decl",
                                      "array_type_decl",
                                      "simple_type",
                                      "name_list",
                                      "identifier",
                                      "routine_body",
                                      "compound_stmt",
                                      "compound_loop_stmt",
                                      "stmt_list",
                                      "loop_stmt_list",
                                      "stmt",
                                      "loop_stmt",
                                      "no_label_stmt",
                                      "no_label_loop_stmt",
                                      "assign_stmt",
                                      "goto_stmt",
                                      "if_stmt",
                                      "if_loop_stmt",
                                      "else_clause",
                                      "else_loop_clause",
                                      "repeat_stmt",
                                      "while_stmt",
                                      "case_stmt",
                                      "case_loop_stmt",
                                      "case_expr_list",
                                      "case_loop_expr_list",
                                      "case_expr",
                                      "case_loop_expr",
                                      "for_stmt",
                                      "for_head",
                                      "proc_stmt",
                                      "args_list",
                                      "expression",
                                      "expr",
                                      "term",
                                      "factor",
                                      "lvalue",
                                      YY_NULLPTR};

static const char* yysymbol_name(yysymbol_kind_t yysymbol) {
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-195)

#define yypact_value_is_default(Yyn) ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-180)

#define yytable_value_is_error(Yyn) 0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] = {
    2,    14,   53,   1,    -195, 59,   66,   20,   127,  131,  -195, 59,   -195, 100,  109,  -195, -195, -195, -195, 59,   170,  -195, 40,   -195, 798,  59,   -195, 112,  59,   124,  -195, -195, -195, -195, -195, -195, 33,  119,  -195, 126,
    154,  -195, 179,  189,  190,  199,  202,  216,  898,  -195, 898,  898,  59,   214,  -18,  -195, 194,  -195, -195, -195, -195, -195, -195, -195, -195, 584,  -195, 13,   -195, 847,  59,   -195, 92,   -195, 272,  274,  124, -195, 12,   -195,
    15,   -195, -195, -195, 860,  898,  898,  898,  898,  898,  898,  898,  225,  227,  232,  234,  238,  241,  245,  246,  249,  949,  898,  898,  -195, -26,  754,  19,   43,   -195, -19,  495,  407,  67,   251,  -195, 898, 898,  59,   -195,
    -195, 248,  898,  898,  -195, -195, -195, -195, -195, -195, -195, -195, -195, -195, -195, -195, -195, 898,  898,  59,   59,   -195, -195, -195, 252,  59,   254,  250,  -195, -195, -195, 255,  -195, 59,   847,  256,  256, -195, -195, 66,
    258,  66,   266,  -195, 269,  17,   296,  76,   81,   121,  132,  133,  898,  898,  898,  898,  898,  898,  898,  898,  898,  -195, -195, -195, -195, 183,  898,  831,  898,  898,  898,  898,  898,  898,  298,  898,  898, 898,  898,  898,
    898,  898,  898,  299,  584,  653,  898,  106,  146,  -195, 540,  613,  330,  311,  296,  340,  -195, 151,  688,  157,  -195, 114,  40,   -195, 59,   -195, 302,  162,  294,  -195, 304,  -195, 306,  -195, -195, -195, 898, -195, -195, -195,
    -195, -195, 152,  158,  159,  177,  196,  204,  206,  209,  212,  -195, 217,  298,  19,   19,   19,   19,   19,   19,   831,  -195, 43,   43,   43,   -195, -195, -195, -195, 296,  -195, -195, 831,  413,  -195, -20,  349, -195, -195, -195,
    -195, 584,  336,  707,  -195, -195, 312,  -195, -195, 847,  -195, -195, -195, 59,   138,  -195, 140,  688,  -195, -195, 296,  -195, -195, -195, -195, -195, -195, -195, -195, -195, -195, -195, -195, 317,  -195, -195, 831, 898,  898,  336,
    584,  -195, 584,  468,  -195, 73,   309,  319,  171,  -195, 162,  688,  -195, -195, 329,  550,  706,  -195, -195, 338,  -195, -195, 584,  847,  -195, 688,  -195, -195, -195, -195, -195, -195, 339,  -195, -195, -195};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] = {0,   0,   0,   35,  1,   0,   35,  5,   0,  49,  73,  36,  38,  0,   3,   4,   79,  6,   74,  0,   29,  37,  0,   2,   76,  50,  52,  0,   0,   8,   41,  43,  44,  45, 46,  47,  0,   40,  75,  0,
                                        0,   138, 0,   140, 0,   0,   0,   0,   0,  82,  0,   0,   0,   0,   135, 90,  81,  86,  89,  91,  92,  93,  94,  95,  96,  120, 97,  0,   51,  0,   30,  32,  0,   72, 0,   0,   7,   11,  35,  12,
                                        35,  42,  48,  39,  120, 0,   0,   0,   0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   166, 179, 120, 154, 158, 163, 165, 120, 0,   0,  0,   110, 0,   0,   0,   80,
                                        82,  0,   0,   0,   107, 108, 99,  132, 88, 98,  100, 101, 102, 103, 104, 105, 106, 0,   0,   0,   0,   68,  69,  70,  0,   0,   0,   54,  57,  56,  55,  64,  31,  0,  0,   23,  23,  9,   10,  35,
                                        16,  35,  21,  85,  0,   0,   147, 0,   0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   41,  47,  169, 168, 0,   0,   120, 0,   0,   0,   0,   0,   0,  115, 0,   0,   0,   0,   0,
                                        0,   0,   0,   84,  120, 0,   0,   0,   0,  182, 78,  120, 120, 0,   109, 0,   183, 0,   0,   0,   60,  0,   0,   53,  0,   71,  34,  0,   0,   22,  14,  15,  20,  19, 137, 139, 0,   141, 142, 143,
                                        144, 145, 0,   0,   0,   0,   0,   0,   0,  0,   0,   167, 0,   115, 152, 153, 148, 149, 150, 151, 120, 112, 155, 156, 157, 159, 160, 162, 161, 119, 83,  121, 120, 0,  125, 0,   0,   180, 136, 77,
                                        87,  120, 117, 0,   181, 65,  0,   58,  59, 0,   66,  67,  33,  0,   0,   26,  0,   0,   13,  18,  146, 170, 171, 172, 173, 174, 175, 176, 177, 178, 164, 111, 116, 0,  122, 124, 120, 0,   0,   117,
                                        120, 114, 120, 0,   127, 0,   0,   62,  0,  24,  0,   0,   17,  129, 0,   0,   0,   113, 118, 0,   123, 126, 120, 0,   61,  0,   25,  28,  128, 133, 134, 131, 0,   63, 27,  130};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] = {-195, -195, 16,   -195, -195, 326, -195, 334, -195, 265, -195, 108,  -195, -195, 341, -195, -195, 395,  -10,  -195, -195, 397, -150, -195, -195, 220, -195, -194, -130, -5,  -195,
                                       442,  -195, -195, 331,  -80,  -52, 368,  242, -22,  -21, -195, -195, 207,  142,  -16, -15,  -195, -195, -195, -195, 191,  139, -13,  -195, -8,   240, -11,  244,  -87,  -68, -23};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] = {0,  2,   7,  8,   76, 77,  78, 79,  80,  228, 294, 295, 29,  70,  71,  9,   11, 12,  104, 20,  25,  26,  147, 148, 219, 220, 149, 150, 72,  105, 17,
                                         55, 126, 24, 111, 56, 203, 57, 128, 129, 130, 60,  131, 261, 321, 132, 133, 63, 134, 273, 323, 274, 324, 135, 65,  136, 165, 166, 107, 108, 109, 110};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] = {
    13,  67,  58,  59,  226, 1,   13,  5,   61,  62,  217, 64,  37,  127, 27,  221, 66,  164, 5,   54,  27,  5,   14,  73,  286, 3,   194, 188, 189, 190, 191, 192, 193, 183, 184, -179, 116, 106, 186, 112, 113, 118, 67,  138, 116, 81,  117, 114, 139,
    118, 316, 82,  30,  4,   31,  32,  33,  34,  35,  146, 54,  67,  58,  59,  151, 73,  137, 6,   61,  62,  10,  64,  5,   195, 196, 138, 66,  197, 159, 54,  139, 161, 235, 67,  58,   59,  236, 15,  67,  221, 61,  62,  185, 64,  160, 36,  162, 296,
    66,  198, 199, 54,  200, 332, 201, 207, 54,  253, 262, 263, 264, 212, 213, 209, 188, 189, 190, 191, 192, 193, 188, 189, 190, 191, 192, 193, 214, 215, 74,  75,  265, 266, 267, 268,  216, 73,  16,  347, 19,  327, 73,  237, 205, 342, 146, 236, 238,
    22,  225, 151, 236, 354, 271, 188, 189, 190, 191, 192, 193, 69,  282, 153, 154, 328, 67,  58,  59,  287, 10,  277, 293, 61,  62,  10,  64,  230, 23,  232, 28,  66,  312, 67,  54,   153, 289, 83,  239, 67,  67,  67,  236, 269, 313, 353, 275, 276,
    84,  240, 241, 54,  296, 236, 236, 329, 330, 54,  54,  54,  146, 153, 331, 278, 290, 151, 73,  236, 285, 301, 85,  291, 153, 236, 73,  302, 303, 300, 115, 236, 236, 319, 188, 189,  190, 191, 192, 193, 334, 67,  58,  59,  153, 345, 304, 86,  61,
    62,  236, 64,  251, 67,  58,  59,  66,  87,  88,  54,  61,  62,  67,  64,  119, 305, 275, 89,  66,  236, 90,  54,  338, 306, 339, 307, 325, 236, 308, 236, 54,  309, 236, 146, 91,   236, 310, 155, 151, 156, 236, 146, 73,  172, 352, 173, 151, 67,
    58,  59,  174, 67,  175, 67,  61,  62,  176, 64,  206, 177, 335, 336, 66,  178, 179, 54,  325, 180, 218, 54,  223, 54,  211, 67,  227, 146, 222, 224, 231, 73,  151, 167, 168, 169,  170, 171, 233, 146, 234, 146, 260, 54,  151, 120, 151, 10,  121,
    188, 189, 190, 191, 192, 193, 40,  41,  42,  43,  44,  45,  46,  47,  208, 188, 189, 190, 191, 192, 193, 297, 270, 122, 281, 292, 49,  298, 50,  299, 123, 320, 326, 52,  188, 189,  190, 191, 192, 193, 333, 343, 344, 283, 188, 189, 190, 191, 192,
    193, 317, 318, 348, 188, 189, 190, 191, 192, 193, 157, 284, 351, 355, 21,  53,  124, 125, 158, 152, 242, 243, 244, 245, 246, 247, 248, 249, 250, 229, 68,  314, 10,  30,  252, 31,   32,  33,  34,  35,  254, 255, 256, 257, 258, 259, 346, 288, 92,
    93,  94,  95,  96,  97,  98,  99,  100, 204, 18,  210, 163, 280, 188, 189, 190, 191, 192, 193, 311, 337, 341, 0,   315, 0,   0,   0,   101, 0,   0,   0,   0,   102, 0,   0,   0,    103, 340, 10,  30,  0,   31,  32,  33,  34,  35,  0,   0,   0,
    0,   0,   0,   272, 0,   92,  93,  94,  95,  96,  97,  98,  99,  100, 120, 0,   10,  121, 0,   0,   0,   0,   0,   0,   40,  41,  42,  43,  44,  45,  46,  47,  0,   101, 0,   0,    0,   0,   102, 0,   0,   122, 103, 0,   49,  202, 50,  0,   123,
    0,   0,   52,  0,   0,   0,   0,   0,   0,   322, 120, 279, 10,  121, 0,   0,   0,   0,   0,   0,   40,  41,  42,  43,  44,  45,  46,  47,  0,   0,   0,   0,   0,   53,  124, 125,  0,   122, 0,   0,   49,  0,   50,  0,   123, 0,   0,   52,  0,
    0,   0,   0,   0,   349, 120, 0,   10,  121, 188, 189, 190, 191, 192, 193, 40,  41,  42,  43,  44,  45,  46,  47,  0,   0,   0,   0,   0,   0,   53,  124, 125, 122, 0,   120, 49,   10,  50,  0,   123, 0,   0,   52,  0,   40,  41,  42,  43,  44,
    45,  46,  47,  0,   0,   0,   0,   0,   0,   0,   0,   0,   122, 0,   0,   49,  0,   50,  0,   123, 0,   0,   52,  0,   53,  124, 125, 10,  30,  0,   31,  32,  33,  34,  35,  0,    0,   0,   0,   0,   0,   0,   0,   92,  93,  94,  95,  96,  97,
    98,  99,  100, 0,   53,  124, 125, 0,   0,   0,   0,   0,   0,   10,  30,  0,   31,  32,  33,  34,  35,  0,   101, 0,   0,   0,   0,   102, 0,   0,   0,   103, 10,  30,  0,   31,   32,  33,  34,  35,  0,   0,   0,   0,   0,   0,   0,   272, 92,
    93,  94,  95,  96,  97,  98,  99,  100, 36,  0,   0,   0,   0,   350, 0,   0,   0,   140, 188, 189, 190, 191, 192, 193, 141, 142, 143, 101, 16,  0,   10,  39,  102, 0,   0,   0,    103, 0,   40,  41,  42,  43,  44,  45,  46,  47,  0,   0,   0,
    0,   0,   0,   322, 0,   0,   48,  187, 0,   49,  0,   50,  0,   51,  0,   0,   52,  188, 189, 190, 191, 192, 193, 16,  38,  10,  39,  0,   0,   0,   0,   0,   0,   40,  41,  42,   43,  44,  45,  46,  47,  0,   0,   0,   0,   0,   0,   53,  0,
    0,   48,  0,   0,   49,  0,   50,  16,  51,  10,  39,  52,  0,   0,   0,   0,   0,   40,  41,  42,  43,  44,  45,  46,  47,  10,  30,  0,   31,  32,  33,  34,  35,  0,   48,  0,    16,  49,  10,  50,  0,   51,  53,  0,   52,  0,   40,  41,  42,
    43,  44,  45,  46,  47,  0,   0,   0,   0,   0,   0,   0,   0,   0,   48,  0,   0,   49,  0,   50,  36,  51,  0,   0,   52,  0,   53,  10,  30,  140, 31,  32,  33,  34,  35,  0,    141, 142, 143, 144, 0,   145, 0,   92,  93,  94,  95,  96,  97,
    98,  99,  100, 0,   0,   0,   53,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   101, 0,   0,   0,   0,   102, 0,   10,  181, 103, 31,  32,  33,  34,   182, 0,   0,   0,   0,   0,   0,   0,   0,   92,  93,  94,  95,
    96,  97,  98,  99,  100, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   101, 0,   0,   0,   0,   102, 0,   0,   0,   103};

static const yytype_int16 yycheck[] = {
    5,   24,  24,  24,  154, 3,   11,  6,   24,  24,  140, 24,  22,  65,  19,  145, 24,  85,  6,   24,  25,  6,   6,   28,  218, 11,  106, 47,  48,  49,  50,  51,  52,  101, 102, 53,  62,  48,  64, 50,  51,  67,  65,  62,  62,  12,  64,  52,  67,
    67,  70,  18,  12,  0,   14,  15,  16,  17,  18,  69,  65,  84,  84,  84,  69,  70,  53,  66,  84,  84,  11,  84,  6,   54,  55,  62,  84,  58,  66,  84,  67,  66,  65,  106, 106, 106, 69,  67, 111, 219, 106, 106, 103, 106, 78,  55,  80,  227,
    106, 56,  57,  106, 59,  297, 61,  116, 111, 187, 195, 196, 197, 122, 123, 118, 47,  48,  49,  50,  51,  52,  47,  48,  49,  50,  51,  52,  137, 138, 4,   5,   198, 199, 200, 201, 139, 140, 9,  331, 7,   289, 145, 65,  75,  70,  154, 69,  65,
    47,  153, 154, 69,  345, 204, 47,  48,  49,  50,  51,  52,  47,  212, 69,  70,  293, 187, 187, 187, 10,  11,  63,  8,   187, 187, 11,  187, 159, 67,  161, 8,   187, 260, 204, 187, 69,  70,  66, 65,  210, 211, 212, 69,  202, 272, 343, 205, 206,
    70,  65,  65,  204, 330, 69,  69,  65,  66,  210, 211, 212, 218, 69,  70,  65,  222, 218, 219, 69,  65,  65,  64,  224, 69,  69,  227, 65,  65,  236, 12,  69,  69,  281, 47,  48,  49,  50,  51, 52,  316, 260, 260, 260, 69,  70,  65,  64,  260,
    260, 69,  260, 65,  272, 272, 272, 260, 64,  64,  260, 272, 272, 281, 272, 66,  65,  273, 64,  272, 69,  64,  272, 320, 65,  322, 65,  283, 69,  65,  69,  281, 65,  69,  289, 64,  69,  65,  11, 289, 11,  69,  297, 293, 64,  342, 64,  297, 316,
    316, 316, 64,  320, 64,  322, 316, 316, 64,  316, 53,  64,  317, 318, 316, 64,  64,  316, 323, 64,  62,  320, 66,  322, 70,  342, 64,  331, 68,  68,  66,  330, 331, 87,  88,  89,  90,  91,  66, 343, 65,  345, 38,  342, 343, 9,   345, 11,  12,
    47,  48,  49,  50,  51,  52,  19,  20,  21,  22,  23,  24,  25,  26,  117, 47,  48,  49,  50,  51,  52,  70,  66,  36,  37,  66,  39,  66,  41,  66,  43,  38,  63,  46,  47,  48,  49,  50,  51, 52,  66,  75,  66,  75,  47,  48,  49,  50,  51,
    52,  44,  45,  66,  47,  48,  49,  50,  51,  52,  76,  63,  66,  66,  11,  77,  78,  79,  76,  70,  172, 173, 174, 175, 176, 177, 178, 179, 180, 156, 25,  10,  11,  12,  186, 14,  15,  16,  17, 18,  188, 189, 190, 191, 192, 193, 330, 219, 27,
    28,  29,  30,  31,  32,  33,  34,  35,  42,  8,   120, 84,  211, 47,  48,  49,  50,  51,  52,  253, 319, 323, -1,  273, -1,  -1,  -1,  55,  -1,  -1,  -1,  -1,  60,  -1,  -1,  -1,  64,  10,  11, 12,  -1,  14,  15,  16,  17,  18,  -1,  -1,  -1,
    -1,  -1,  -1,  80,  -1,  27,  28,  29,  30,  31,  32,  33,  34,  35,  9,   -1,  11,  12,  -1,  -1,  -1,  -1,  -1,  -1,  19,  20,  21,  22,  23,  24,  25,  26,  -1,  55,  -1,  -1,  -1,  -1,  60, -1,  -1,  36,  64,  -1,  39,  40,  41,  -1,  43,
    -1,  -1,  46,  -1,  -1,  -1,  -1,  -1,  -1,  80,  9,   10,  11,  12,  -1,  -1,  -1,  -1,  -1,  -1,  19,  20,  21,  22,  23,  24,  25,  26,  -1,  -1,  -1,  -1,  -1,  77,  78,  79,  -1,  36,  -1, -1,  39,  -1,  41,  -1,  43,  -1,  -1,  46,  -1,
    -1,  -1,  -1,  -1,  42,  9,   -1,  11,  12,  47,  48,  49,  50,  51,  52,  19,  20,  21,  22,  23,  24,  25,  26,  -1,  -1,  -1,  -1,  -1,  -1,  77,  78,  79,  36,  -1,  9,   39,  11,  41,  -1, 43,  -1,  -1,  46,  -1,  19,  20,  21,  22,  23,
    24,  25,  26,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  36,  -1,  -1,  39,  -1,  41,  -1,  43,  -1,  -1,  46,  -1,  77,  78,  79,  11,  12,  -1,  14,  15,  16,  17,  18,  -1,  -1,  -1,  -1, -1,  -1,  -1,  -1,  27,  28,  29,  30,  31,  32,
    33,  34,  35,  -1,  77,  78,  79,  -1,  -1,  -1,  -1,  -1,  -1,  11,  12,  -1,  14,  15,  16,  17,  18,  -1,  55,  -1,  -1,  -1,  -1,  60,  -1,  -1,  -1,  64,  11,  12,  -1,  14,  15,  16,  17, 18,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  80,  27,
    28,  29,  30,  31,  32,  33,  34,  35,  55,  -1,  -1,  -1,  -1,  42,  -1,  -1,  -1,  64,  47,  48,  49,  50,  51,  52,  71,  72,  73,  55,  9,   -1,  11,  12,  60,  -1,  -1,  -1,  64,  -1,  19, 20,  21,  22,  23,  24,  25,  26,  -1,  -1,  -1,
    -1,  -1,  -1,  80,  -1,  -1,  36,  37,  -1,  39,  -1,  41,  -1,  43,  -1,  -1,  46,  47,  48,  49,  50,  51,  52,  9,   10,  11,  12,  -1,  -1,  -1,  -1,  -1,  -1,  19,  20,  21,  22,  23,  24, 25,  26,  -1,  -1,  -1,  -1,  -1,  -1,  77,  -1,
    -1,  36,  -1,  -1,  39,  -1,  41,  9,   43,  11,  12,  46,  -1,  -1,  -1,  -1,  -1,  19,  20,  21,  22,  23,  24,  25,  26,  11,  12,  -1,  14,  15,  16,  17,  18,  -1,  36,  -1,  9,   39,  11, 41,  -1,  43,  77,  -1,  46,  -1,  19,  20,  21,
    22,  23,  24,  25,  26,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  36,  -1,  -1,  39,  -1,  41,  55,  43,  -1,  -1,  46,  -1,  77,  11,  12,  64,  14,  15,  16,  17,  18,  -1,  71,  72,  73, 74,  -1,  76,  -1,  27,  28,  29,  30,  31,  32,
    33,  34,  35,  -1,  -1,  -1,  77,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  -1,  -1,  -1,  -1,  60,  -1,  11,  12,  64,  14,  15,  16,  17,  18,  -1,  -1, -1,  -1,  -1,  -1,  -1,  -1,  27,  28,  29,  30,
    31,  32,  33,  34,  35,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  -1,  -1,  -1,  -1,  60,  -1,  -1,  -1,  64};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] = {0,   3,   83,  11,  0,   6,   66,  84,  85,  97,  11,  98,  99,  111, 84,  67,  9,   112, 113, 7,   101, 99,  47,  67,  115, 102, 103, 111, 8,   94,  12,  14,  15,  16,  17,  18,  55,  100, 10, 12,
                                      19,  20,  21,  22,  23,  24,  25,  26,  36,  39,  41,  43,  46,  77,  111, 113, 117, 119, 121, 122, 123, 127, 128, 129, 135, 136, 137, 143, 103, 47,  95,  96,  110, 111, 4,   5,   86,  87,  88, 89,
                                      90,  12,  18,  66,  70,  64,  64,  64,  64,  64,  64,  64,  27,  28,  29,  30,  31,  32,  33,  34,  35,  55,  60,  64,  100, 111, 139, 140, 141, 142, 143, 116, 139, 139, 111, 12,  62,  64,  67, 66,
                                      9,   12,  36,  43,  78,  79,  114, 118, 120, 121, 122, 124, 127, 128, 130, 135, 137, 53,  62,  67,  64,  71,  72,  73,  74,  76,  100, 104, 105, 108, 109, 111, 96,  69,  70,  11,  11,  87,  89, 66,
                                      84,  66,  84,  119, 142, 138, 139, 138, 138, 138, 138, 138, 64,  64,  64,  64,  64,  64,  64,  64,  64,  12,  18,  142, 142, 139, 64,  37,  47,  48,  49,  50,  51,  52,  117, 54,  55,  58,  56, 57,
                                      59,  61,  40,  118, 42,  75,  53,  139, 138, 111, 116, 70,  139, 139, 139, 139, 111, 110, 62,  106, 107, 110, 68,  66,  68,  111, 104, 64,  91,  91,  84,  66,  84,  66,  65,  65,  69,  65,  65, 65,
                                      65,  65,  138, 138, 138, 138, 138, 138, 138, 138, 138, 65,  138, 117, 140, 140, 140, 140, 140, 140, 38,  125, 141, 141, 141, 142, 142, 142, 142, 139, 66,  118, 80,  131, 133, 139, 139, 63,  65, 10,
                                      120, 37,  118, 75,  63,  65,  109, 10,  107, 70,  100, 111, 66,  8,   92,  93,  110, 70,  66,  66,  139, 65,  65,  65,  65,  65,  65,  65,  65,  65,  65,  125, 117, 117, 10,  133, 70,  44,  45, 118,
                                      38,  126, 80,  132, 134, 139, 63,  104, 110, 65,  66,  70,  109, 66,  117, 139, 139, 126, 118, 118, 10,  134, 70,  75,  66,  70,  93,  109, 66,  42,  42,  66,  118, 104, 109, 66};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] = {0,   82,  83,  83,  83,  83,  84,  85,  86,  86,  86,  86,  86,  87,  87,  87,  87,  88,  89,  89,  89,  89,  90,  91,  91,  92,  92,  93,  93,  94,  94,  95,  95,  96,  96,  97,  97,
                                    98,  98,  99,  99,  100, 100, 100, 100, 100, 100, 100, 100, 101, 101, 102, 102, 103, 103, 104, 104, 104, 105, 106, 106, 107, 107, 108, 109, 109, 109, 109, 109, 109, 109, 110, 110, 111,
                                    112, 113, 113, 114, 114, 115, 115, 115, 116, 116, 116, 117, 117, 118, 118, 119, 119, 119, 119, 119, 119, 119, 119, 119, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 121, 122,
                                    123, 123, 124, 124, 125, 125, 126, 126, 127, 127, 128, 129, 130, 131, 131, 132, 132, 133, 133, 134, 134, 135, 136, 136, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 138, 138,
                                    139, 139, 139, 139, 139, 139, 139, 140, 140, 140, 140, 141, 141, 141, 141, 141, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 143, 143, 143, 143, 143};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] = {0, 2, 5, 4, 4, 3, 2, 4, 0, 2, 2, 1, 1, 4, 3, 3, 2, 5, 4, 3, 3, 2, 3, 0, 3, 3, 1, 4, 3, 0, 2, 2, 1, 4, 3, 0, 2, 2, 1, 4, 3, 1, 2, 1, 1, 1, 1, 1, 2, 0, 2, 2, 1, 4, 3, 1, 1, 1, 3, 2, 1, 4,
                                   3, 6, 1, 3, 3, 3, 1, 1, 1, 3, 1, 1, 1, 3, 2, 3, 2, 0, 3, 2, 0, 3, 2, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 2, 5, 4, 5, 4, 0, 2, 0, 2, 4, 0, 4, 5, 5,
                                   2, 1, 2, 1, 4, 3, 4, 3, 2, 7, 7, 1, 4, 4, 1, 4, 1, 4, 4, 4, 4, 4, 3, 1, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 1, 3, 3, 3, 3, 1, 4, 1, 1, 3, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4, 4, 3, 3};

enum { YYENOMEM = -2 };

#define yyerrok (yyerrstatus = 0)
#define yyclearin (yychar = YYEMPTY)

#define YYACCEPT goto yyacceptlab
#define YYABORT goto yyabortlab
#define YYERROR goto yyerrorlab
#define YYNOMEM goto yyexhaustedlab

#define YYRECOVERING() (!!yyerrstatus)

#define YYBACKUP(Token, Value)                      \
  do                                                \
    if (yychar == YYEMPTY) {                        \
      yychar = (Token);                             \
      yylval = (Value);                             \
      YYPOPSTACK(yylen);                            \
      yystate = *yyssp;                             \
      goto yybackup;                                \
    }                                               \
    else {                                          \
      yyerror(YY_("syntax error: cannot back up")); \
      YYERROR;                                      \
    }                                               \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* Enable debugging if requested.  */
#if YYDEBUG

#ifndef YYFPRINTF
#include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#define YYFPRINTF fprintf
#endif

#define YYDPRINTF(Args) \
  do {                  \
    if (yydebug)        \
      YYFPRINTF Args;   \
  } while (0)

#define YY_SYMBOL_PRINT(Title, Kind, Value, Location) \
  do {                                                \
    if (yydebug) {                                    \
      YYFPRINTF(stderr, "%s ", Title);                \
      yy_symbol_print(stderr, Kind, Value);           \
      YYFPRINTF(stderr, "\n");                        \
    }                                                 \
  } while (0)

/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void yy_symbol_value_print(FILE* yyo, yysymbol_kind_t yykind, YYSTYPE const* const yyvaluep) {
  FILE* yyoutput = yyo;
  YY_USE(yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE(yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}

/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void yy_symbol_print(FILE* yyo, yysymbol_kind_t yykind, YYSTYPE const* const yyvaluep) {
  YYFPRINTF(yyo, "%s %s (", yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name(yykind));

  yy_symbol_value_print(yyo, yykind, yyvaluep);
  YYFPRINTF(yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void yy_stack_print(yy_state_t* yybottom, yy_state_t* yytop) {
  YYFPRINTF(stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++) {
    int yybot = *yybottom;
    YYFPRINTF(stderr, " %d", yybot);
  }
  YYFPRINTF(stderr, "\n");
}

#define YY_STACK_PRINT(Bottom, Top)    \
  do {                                 \
    if (yydebug)                       \
      yy_stack_print((Bottom), (Top)); \
  } while (0)

/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void yy_reduce_print(yy_state_t* yyssp, YYSTYPE* yyvsp, int yyrule) {
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF(stderr, "Reducing stack by rule %d (line %d):\n", yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++) {
    YYFPRINTF(stderr, "   $%d = ", yyi + 1);
    yy_symbol_print(stderr, YY_ACCESSING_SYMBOL(+yyssp[yyi + 1 - yynrhs]), &yyvsp[(yyi + 1) - (yynrhs)]);
    YYFPRINTF(stderr, "\n");
  }
}

#define YY_REDUCE_PRINT(Rule)              \
  do {                                     \
    if (yydebug)                           \
      yy_reduce_print(yyssp, yyvsp, Rule); \
  } while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
#define YYDPRINTF(Args) ((void)0)
#define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
#define YY_STACK_PRINT(Bottom, Top)
#define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
#define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void yydestruct(const char* yymsg, yysymbol_kind_t yykind, YYSTYPE* yyvaluep) {
  YY_USE(yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT(yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE(yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}

/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;

/*----------.
| yyparse.  |
`----------*/

int yyparse(void) {
  yy_state_fast_t yystate = 0;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus = 0;

  /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

  /* Their size.  */
  YYPTRDIFF_T yystacksize = YYINITDEPTH;

  /* The state stack: array, bottom, top.  */
  yy_state_t yyssa[YYINITDEPTH];
  yy_state_t* yyss = yyssa;
  yy_state_t* yyssp = yyss;

  /* The semantic value stack: array, bottom, top.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE* yyvs = yyvsa;
  YYSTYPE* yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#define YYPOPSTACK(N) (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF((stderr, "Entering state %d\n", yystate));
  YY_ASSERT(0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST(yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT(yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
  {
    /* Get the current used size of the three stacks, in elements.  */
    YYPTRDIFF_T yysize = yyssp - yyss + 1;

#if defined yyoverflow
    {
      /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
      yy_state_t* yyss1 = yyss;
      YYSTYPE* yyvs1 = yyvs;

      /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
      yyoverflow(YY_("memory exhausted"), &yyss1, yysize * YYSIZEOF(*yyssp), &yyvs1, yysize * YYSIZEOF(*yyvsp), &yystacksize);
      yyss = yyss1;
      yyvs = yyvs1;
    }
#else /* defined YYSTACK_RELOCATE */
    /* Extend the stack our own way.  */
    if (YYMAXDEPTH <= yystacksize)
      YYNOMEM;
    yystacksize *= 2;
    if (YYMAXDEPTH < yystacksize)
      yystacksize = YYMAXDEPTH;

    {
      yy_state_t* yyss1 = yyss;
      union yyalloc* yyptr = YY_CAST(union yyalloc*, YYSTACK_ALLOC(YY_CAST(YYSIZE_T, YYSTACK_BYTES(yystacksize))));
      if (!yyptr)
        YYNOMEM;
      YYSTACK_RELOCATE(yyss_alloc, yyss);
      YYSTACK_RELOCATE(yyvs_alloc, yyvs);
#undef YYSTACK_RELOCATE
      if (yyss1 != yyssa)
        YYSTACK_FREE(yyss1);
    }
#endif

    yyssp = yyss + yysize - 1;
    yyvsp = yyvs + yysize - 1;

    YY_IGNORE_USELESS_CAST_BEGIN
    YYDPRINTF((stderr, "Stack size increased to %ld\n", YY_CAST(long, yystacksize)));
    YY_IGNORE_USELESS_CAST_END

    if (yyss + yystacksize - 1 <= yyssp)
      YYABORT;
  }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default(yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY) {
    YYDPRINTF((stderr, "Reading a token\n"));
    yychar = yylex();
  }

  if (yychar <= YYEOF) {
    yychar = YYEOF;
    yytoken = YYSYMBOL_YYEOF;
    YYDPRINTF((stderr, "Now at end of input.\n"));
  }
  else if (yychar == YYerror) {
    /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
    yychar = YYUNDEF;
    yytoken = YYSYMBOL_YYerror;
    goto yyerrlab1;
  }
  else {
    yytoken = YYTRANSLATE(yychar);
    YY_SYMBOL_PRINT("Next token is", yytoken, &yylval, &yylloc);
  }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0) {
    if (yytable_value_is_error(yyn))
      goto yyerrlab;
    yyn = -yyn;
    goto yyreduce;
  }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;

/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;

/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1 - yylen];

  YY_REDUCE_PRINT(yyn);
  switch (yyn) {
    case 2: /* program: PROGRAM IDENT_NAME SEMICOLON routine DOT  */
#line 238 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse program 1: " << (*(yyvsp[-3].token).stringValue) << std::endl;
#endif

      std::string name{*(yyvsp[-3].token).stringValue};
      (yyvsp[-1].routineNode)->setSubType(ast::RoutineNode::SubType::MAIN);
      (yyval.programNode) = new ast::ProgramNode(std::move(name), (yyvsp[-1].routineNode));
      resultAst = (yyval.programNode);
    }
#line 1685 "src/out/parser.cpp"
    break;

    case 3: /* program: PROGRAM IDENT_NAME SEMICOLON routine  */
#line 249 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse program 2: " << (*(yyvsp[-2].token).stringValue) << std::endl;
#endif

      std::string name{*(yyvsp[-2].token).stringValue};
      (yyvsp[0].routineNode)->setSubType(ast::RoutineNode::SubType::MAIN);
      (yyval.programNode) = new ast::ProgramNode(std::move(name), (yyvsp[0].routineNode));
      resultAst = (yyval.programNode);
      parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of end dot");
    }
#line 1701 "src/out/parser.cpp"
    break;

    case 4: /* program: PROGRAM IDENT_NAME routine DOT  */
#line 261 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse program 3: " << (*(yyvsp[-2].token).stringValue) << std::endl;
#endif

      std::string name{*(yyvsp[-2].token).stringValue};
      (yyvsp[-1].routineNode)->setSubType(ast::RoutineNode::SubType::MAIN);
      (yyval.programNode) = new ast::ProgramNode(std::move(name), (yyvsp[-1].routineNode));
      resultAst = (yyval.programNode);
      parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1717 "src/out/parser.cpp"
    break;

    case 5: /* program: PROGRAM IDENT_NAME routine  */
#line 273 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse program 4: " << (*(yyvsp[-1].token).stringValue) << std::endl;
#endif

      std::string name{*(yyvsp[-1].token).stringValue};
      (yyvsp[0].routineNode)->setSubType(ast::RoutineNode::SubType::MAIN);
      (yyval.programNode) = new ast::ProgramNode(std::move(name), (yyvsp[0].routineNode));
      resultAst = (yyval.programNode);
      parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon and end dot");
    }
#line 1733 "src/out/parser.cpp"
    break;

    case 6: /* routine: routine_head routine_body  */
#line 287 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse routine" << std::endl;
#endif

      (yyval.routineNode) = new ast::RoutineNode((yyvsp[-1].routineHeadNode), (yyvsp[0].routineBodyNode));
    }
#line 1745 "src/out/parser.cpp"
    break;

    case 7: /* routine_head: const_part type_part var_part routine_part  */
#line 297 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse routine head" << std::endl;
#endif

      (yyval.routineHeadNode) = new ast::RoutineHeadNode((yyvsp[-3].constPartList), (yyvsp[-2].typePartList), (yyvsp[-1].varPartList), (yyvsp[0].routinePartList));
    }
#line 1757 "src/out/parser.cpp"
    break;

    case 8: /* routine_part: %empty  */
#line 307 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse empty routine part" << std::endl;
#endif

      (yyval.routinePartList) = new std::vector<ast::RoutineDeclarationNode*>();
    }
#line 1769 "src/out/parser.cpp"
    break;

    case 9: /* routine_part: routine_part fun_decl  */
#line 315 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse routine part with fun decl 1 " << (yyvsp[0].routineDeclarationNode)->getName() << std::endl;
#endif

      if (!saveRoutine((yyvsp[0].routineDeclarationNode), true)) {
        YYERROR;
      }

      (yyval.routinePartList) = (yyvsp[-1].routinePartList);
      (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1786 "src/out/parser.cpp"
    break;

    case 10: /* routine_part: routine_part proc_decl  */
#line 328 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse routine part with proc decl 1 " << (yyvsp[0].routineDeclarationNode)->getName() << std::endl;
#endif

      if (!saveRoutine((yyvsp[0].routineDeclarationNode), true)) {
        YYERROR;
      }

      (yyval.routinePartList) = (yyvsp[-1].routinePartList);
      (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1803 "src/out/parser.cpp"
    break;

    case 11: /* routine_part: fun_decl  */
#line 341 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse routine part with fun decl 2 " << (yyvsp[0].routineDeclarationNode)->getName() << std::endl;
#endif

      if (!saveRoutine((yyvsp[0].routineDeclarationNode), true)) {
        YYERROR;
      }

      (yyval.routinePartList) = new std::vector<ast::RoutineDeclarationNode*>();
      (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1820 "src/out/parser.cpp"
    break;

    case 12: /* routine_part: proc_decl  */
#line 354 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse routine part with proc decl 2 " << (yyvsp[0].routineDeclarationNode)->getName() << std::endl;
#endif

      if (!saveRoutine((yyvsp[0].routineDeclarationNode), true)) {
        YYERROR;
      }

      (yyval.routinePartList) = new std::vector<ast::RoutineDeclarationNode*>();
      (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1837 "src/out/parser.cpp"
    break;

    case 13: /* fun_decl: fun_head SEMICOLON routine SEMICOLON  */
#line 369 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse fun decl 1" << std::endl;
#endif

      if (!hasReturnValue((yyvsp[-1].routineNode), (yyvsp[-3].routineDeclarationNode)->getName())) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", function should have one return value");
        fatalError = true;
        YYERROR;
      }

      ctx->getLookupTable().undefineTypesVarsRoutines(ctx->getCurrentScope());
      ctx->popScope();

      (yyval.routineDeclarationNode) = (yyvsp[-3].routineDeclarationNode);
      (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[-1].routineNode)));
      (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
    }
#line 1860 "src/out/parser.cpp"
    break;

    case 14: /* fun_decl: fun_head SEMICOLON routine  */
#line 388 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse fun decl 2" << std::endl;
#endif

      if (!hasReturnValue((yyvsp[0].routineNode), (yyvsp[-2].routineDeclarationNode)->getName())) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", function should have one return value");
        fatalError = true;
        YYERROR;
      }

      ctx->getLookupTable().undefineTypesVarsRoutines(ctx->getCurrentScope());
      ctx->popScope();

      (yyval.routineDeclarationNode) = (yyvsp[-2].routineDeclarationNode);
      (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[0].routineNode)));
      (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
      parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1884 "src/out/parser.cpp"
    break;

    case 15: /* fun_decl: fun_head routine SEMICOLON  */
#line 408 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse fun decl 3" << std::endl;
#endif

      if (!hasReturnValue((yyvsp[-1].routineNode), (yyvsp[-2].routineDeclarationNode)->getName())) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", function should have one return value");
        fatalError = true;
        YYERROR;
      }

      ctx->getLookupTable().undefineTypesVarsRoutines(ctx->getCurrentScope());
      ctx->popScope();

      (yyval.routineDeclarationNode) = (yyvsp[-2].routineDeclarationNode);
      (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[-1].routineNode)));
      (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
      parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1908 "src/out/parser.cpp"
    break;

    case 16: /* fun_decl: fun_head routine  */
#line 428 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse fun decl 4" << std::endl;
#endif

      if (!hasReturnValue((yyvsp[0].routineNode), (yyvsp[-1].routineDeclarationNode)->getName())) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", function should have one return value");
        fatalError = true;
        YYERROR;
      }

      ctx->getLookupTable().undefineTypesVarsRoutines(ctx->getCurrentScope());
      ctx->popScope();

      (yyval.routineDeclarationNode) = (yyvsp[-1].routineDeclarationNode);
      (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[0].routineNode)));
      (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
      parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1932 "src/out/parser.cpp"
    break;

    case 17: /* fun_head: FUNCTION IDENT_NAME params COLON simple_type  */
#line 450 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse fun head " << (*(yyvsp[-3].token).stringValue) << std::endl;
#endif

      ctx->pushScope(*(yyvsp[-3].token).stringValue);

      try {
        if (!isBasicOrEnumOrArrayOrRecordType((yyvsp[0].simpleTypeNode)->flat())) {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", invalid return type");
          fatalError = true;
          YYERROR;
        }
      } catch (std::runtime_error& err) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
        fatalError = true;
        YYERROR;
      }

      std::string funType;
      try {
        funType = (yyvsp[0].simpleTypeNode)->flat();
      } catch (std::runtime_error& err) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
        fatalError = true;
        YYERROR;
      }

      std::vector<ast::IdentifierNode*> funNameVector{new ast::IdentifierNode(*(yyvsp[-3].token).stringValue)};
      if (!saveVariables(&funNameVector, funType)) {
        YYERROR;
      }

      for (const auto& param : *(yyvsp[-2].paramsNode)->getParams()) {
        std::string paramType;
        try {
          paramType = param->getParamsType()->flat();
        } catch (std::runtime_error& err) {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
          fatalError = true;
          YYERROR;
        }

        if (!saveVariables(param->getParams().get(), paramType)) {
          YYERROR;
        }
      }

      std::string name{*(yyvsp[-3].token).stringValue};
      (yyval.routineDeclarationNode) = new ast::RoutineDeclarationNode(ast::RoutineDeclarationNode::RoutineType::FUNCTION, std::move(name), (yyvsp[-2].paramsNode), (yyvsp[0].simpleTypeNode), nullptr);

      if (!saveRoutine((yyval.routineDeclarationNode), false)) {
        YYERROR;
      }
    }
#line 1991 "src/out/parser.cpp"
    break;

    case 18: /* proc_decl: proc_head SEMICOLON routine SEMICOLON  */
#line 507 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse proc decl" << std::endl;
#endif

      ctx->getLookupTable().undefineTypesVarsRoutines(ctx->getCurrentScope());
      ctx->popScope();

      (yyval.routineDeclarationNode) = (yyvsp[-3].routineDeclarationNode);
      (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[-1].routineNode)));
      (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::PROCEDURE);
    }
#line 2008 "src/out/parser.cpp"
    break;

    case 19: /* proc_decl: proc_head routine SEMICOLON  */
#line 520 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse proc decl" << std::endl;
#endif

      ctx->getLookupTable().undefineTypesVarsRoutines(ctx->getCurrentScope());
      ctx->popScope();

      (yyval.routineDeclarationNode) = (yyvsp[-2].routineDeclarationNode);
      (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[-1].routineNode)));
      (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::PROCEDURE);
      parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2026 "src/out/parser.cpp"
    break;

    case 20: /* proc_decl: proc_head SEMICOLON routine  */
#line 534 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse proc decl" << std::endl;
#endif

      ctx->getLookupTable().undefineTypesVarsRoutines(ctx->getCurrentScope());
      ctx->popScope();

      (yyval.routineDeclarationNode) = (yyvsp[-2].routineDeclarationNode);
      (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[0].routineNode)));
      (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::PROCEDURE);
      parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2044 "src/out/parser.cpp"
    break;

    case 21: /* proc_decl: proc_head routine  */
#line 548 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse proc decl" << std::endl;
#endif

      ctx->getLookupTable().undefineTypesVarsRoutines(ctx->getCurrentScope());
      ctx->popScope();

      (yyval.routineDeclarationNode) = (yyvsp[-1].routineDeclarationNode);
      (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[0].routineNode)));
      (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::PROCEDURE);
      parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2062 "src/out/parser.cpp"
    break;

    case 22: /* proc_head: PROCEDURE IDENT_NAME params  */
#line 564 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse proc head " << (*(yyvsp[-1].token).stringValue) << std::endl;
#endif

      ctx->pushScope(*(yyvsp[-1].token).stringValue);

      for (const auto& param : *(yyvsp[0].paramsNode)->getParams()) {
        std::string paramType;
        try {
          paramType = param->getParamsType()->flat();
        } catch (std::runtime_error& err) {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
          fatalError = true;
          YYERROR;
        }

        if (!saveVariables(param->getParams().get(), paramType)) {
          YYERROR;
        }
      }

      std::string name{*(yyvsp[-1].token).stringValue};
      (yyval.routineDeclarationNode) = new ast::RoutineDeclarationNode(ast::RoutineDeclarationNode::RoutineType::PROCEDURE, std::move(name), (yyvsp[0].paramsNode), nullptr, nullptr);

      if (!saveRoutine((yyval.routineDeclarationNode), false)) {
        YYERROR;
      }
    }
#line 2095 "src/out/parser.cpp"
    break;

    case 23: /* params: %empty  */
#line 595 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse empty params" << std::endl;
#endif

      std::vector<ast::ParamsGroupNode*>* emptyParamsList = new std::vector<ast::ParamsGroupNode*>();
      (yyval.paramsNode) = new ast::ParamsNode(emptyParamsList);
    }
#line 2108 "src/out/parser.cpp"
    break;

    case 24: /* params: LP params_decl RP  */
#line 604 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse params" << std::endl;
#endif

      (yyval.paramsNode) = new ast::ParamsNode((yyvsp[-1].paramsGroupList));
    }
#line 2120 "src/out/parser.cpp"
    break;

    case 25: /* params_decl: params_decl SEMICOLON params_type  */
#line 614 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse params decl 1" << std::endl;
#endif

      (yyval.paramsGroupList) = (yyvsp[-2].paramsGroupList);
      (yyval.paramsGroupList)->push_back((yyvsp[0].paramsGroupNode));
    }
#line 2133 "src/out/parser.cpp"
    break;

    case 26: /* params_decl: params_type  */
#line 623 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse params decl 2" << std::endl;
#endif

      (yyval.paramsGroupList) = new std::vector<ast::ParamsGroupNode*>();
      (yyval.paramsGroupList)->push_back((yyvsp[0].paramsGroupNode));
    }
#line 2146 "src/out/parser.cpp"
    break;

    case 27: /* params_type: VAR name_list COLON simple_type  */
#line 634 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse params type 1" << std::endl;
#endif

      try {
        if (!isBasicOrEnumOrArrayOrRecordType((yyvsp[0].simpleTypeNode)->flat())) {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", invalid parameter type");
          fatalError = true;
          YYERROR;
        }
      } catch (std::runtime_error& err) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", invalid parameter type");
        fatalError = true;
        YYERROR;
      }

      (yyval.paramsGroupNode) = new ast::ParamsGroupNode(ast::ParamsGroupNode::PassType::PASS_BY_REFERENCE, (yyvsp[-2].identifierList), (yyvsp[0].simpleTypeNode));
    }
#line 2171 "src/out/parser.cpp"
    break;

    case 28: /* params_type: name_list COLON simple_type  */
#line 655 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse params type 2" << std::endl;
#endif

      try {
        if (!isBasicOrEnumOrArrayOrRecordType((yyvsp[0].simpleTypeNode)->flat())) {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", invalid parameter type");
          fatalError = true;
          YYERROR;
        }
      } catch (std::runtime_error& err) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", invalid parameter type");
        fatalError = true;
        YYERROR;
      }

      (yyval.paramsGroupNode) = new ast::ParamsGroupNode(ast::ParamsGroupNode::PassType::PASS_BY_VALUE, (yyvsp[-2].identifierList), (yyvsp[0].simpleTypeNode));
    }
#line 2196 "src/out/parser.cpp"
    break;

    case 29: /* var_part: %empty  */
#line 678 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse empty var part" << std::endl;
#endif

      (yyval.varPartList) = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
    }
#line 2208 "src/out/parser.cpp"
    break;

    case 30: /* var_part: VAR var_decl_list  */
#line 686 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse var part" << std::endl;
#endif

      (yyval.varPartList) = (yyvsp[0].varPartList);
    }
#line 2220 "src/out/parser.cpp"
    break;

    case 31: /* var_decl_list: var_decl_list var_decl  */
#line 696 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse var decl list 1" << std::endl;
#endif

      (yyval.varPartList) = (yyvsp[-1].varPartList);
      (yyval.varPartList)->push_back((yyvsp[0].varPartListElement));
    }
#line 2233 "src/out/parser.cpp"
    break;

    case 32: /* var_decl_list: var_decl  */
#line 705 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse var decl list 2" << std::endl;
#endif

      (yyval.varPartList) = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
      (yyval.varPartList)->push_back((yyvsp[0].varPartListElement));
    }
#line 2246 "src/out/parser.cpp"
    break;

    case 33: /* var_decl: name_list COLON type_decl SEMICOLON  */
#line 716 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse var decl 1" << std::endl;
#endif

      std::string varType;
      try {
        varType = (yyvsp[-1].typeNode)->flat();
      } catch (std::runtime_error& err) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
        fatalError = true;
        YYERROR;
      }

      if (isRangeType(varType)) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", invalid variable type");
        fatalError = true;
        YYERROR;
      }

      if (!saveVariables((yyvsp[-3].identifierList), varType)) {
        YYERROR;
      }

      (yyval.varPartListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-3].identifierList), (yyvsp[-1].typeNode));
    }
#line 2276 "src/out/parser.cpp"
    break;

    case 34: /* var_decl: name_list COLON type_decl  */
#line 742 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse var decl 2" << std::endl;
#endif

      std::string varType;
      try {
        varType = (yyvsp[0].typeNode)->flat();
      } catch (std::runtime_error& err) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
        fatalError = true;
        YYERROR;
      }

      if (isRangeType(varType)) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", invalid variable type");
        fatalError = true;
        YYERROR;
      }

      if (!saveVariables((yyvsp[-2].identifierList), varType)) {
        YYERROR;
      }

      (yyval.varPartListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-2].identifierList), (yyvsp[0].typeNode));
      parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2307 "src/out/parser.cpp"
    break;

    case 35: /* const_part: %empty  */
#line 771 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse empty const part" << std::endl;
#endif

      (yyval.constPartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::ConstantNode*>*>();
    }
#line 2319 "src/out/parser.cpp"
    break;

    case 36: /* const_part: CONST const_expr_list  */
#line 779 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse const part" << std::endl;
#endif

      (yyval.constPartList) = (yyvsp[0].constPartList);
    }
#line 2331 "src/out/parser.cpp"
    break;

    case 37: /* const_expr_list: const_expr_list const_expr  */
#line 789 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse const expr list 1" << std::endl;
#endif

      (yyval.constPartList) = (yyvsp[-1].constPartList);
      (yyval.constPartList)->push_back((yyvsp[0].constPartListElement));
    }
#line 2344 "src/out/parser.cpp"
    break;

    case 38: /* const_expr_list: const_expr  */
#line 798 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse const expr list 2" << std::endl;
#endif

      (yyval.constPartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::ConstantNode*>*>();
      (yyval.constPartList)->push_back((yyvsp[0].constPartListElement));
    }
#line 2357 "src/out/parser.cpp"
    break;

    case 39: /* const_expr: identifier EQUAL const_value SEMICOLON  */
#line 809 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse const expr 1" << std::endl;
#endif

      try {
        if (!saveConstant((yyvsp[-3].identifierNode), (yyvsp[-1].constantNode)->flat(), (yyvsp[-1].constantNode)->flatType())) {
          YYERROR;
        }
      } catch (std::runtime_error& err) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
        fatalError = true;
        YYERROR;
      }

      try {
        if ((yyvsp[-1].constantNode)->flatType() == "string") {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", const type must be basic");
          fatalError = true;
          YYERROR;
        }
      } catch (std::runtime_error& err) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
        fatalError = true;
        YYERROR;
      }

      (yyval.constPartListElement) = new std::pair<ast::IdentifierNode*, ast::ConstantNode*>((yyvsp[-3].identifierNode), (yyvsp[-1].constantNode));
    }
#line 2393 "src/out/parser.cpp"
    break;

    case 40: /* const_expr: identifier EQUAL const_value  */
#line 841 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse const expr 2" << std::endl;
#endif

      try {
        if (!saveConstant((yyvsp[-2].identifierNode), (yyvsp[0].constantNode)->flat(), (yyvsp[0].constantNode)->flatType())) {
          YYERROR;
        }
      } catch (std::runtime_error& err) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
        fatalError = true;
        YYERROR;
      }

      try {
        if ((yyvsp[0].constantNode)->flatType() == "string") {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", const type must be basic");
          fatalError = true;
          YYERROR;
        }
      } catch (std::runtime_error& err) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
        fatalError = true;
        YYERROR;
      }

      (yyval.constPartListElement) = new std::pair<ast::IdentifierNode*, ast::ConstantNode*>((yyvsp[-2].identifierNode), (yyvsp[0].constantNode));
      parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2430 "src/out/parser.cpp"
    break;

    case 41: /* const_value: INTEGER  */
#line 876 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse const value - integer `" << (yyvsp[0].token).numericalValue << "`" << std::endl;
#endif

      (yyval.constantNode) = new ast::IntegerConstantNode((yyvsp[0].token).numericalValue);
    }
#line 2442 "src/out/parser.cpp"
    break;

    case 42: /* const_value: MINUS INTEGER  */
#line 884 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse const value - signed integer `" << -(yyvsp[0].token).numericalValue << "`" << std::endl;
#endif

      (yyval.constantNode) = new ast::IntegerConstantNode(-(yyvsp[0].token).numericalValue);
    }
#line 2454 "src/out/parser.cpp"
    break;

    case 43: /* const_value: CHAR  */
#line 893 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse const value - char `" << static_cast<char>((yyvsp[0].token).numericalValue) << "`" << std::endl;
#endif

      (yyval.constantNode) = new ast::CharConstantNode(static_cast<char>((yyvsp[0].token).numericalValue));
    }
#line 2466 "src/out/parser.cpp"
    break;

    case 44: /* const_value: STRING  */
#line 901 "src/yacc.y"
    {
      std::string str{*(yyvsp[0].token).stringValue};
      str = str.substr(1, str.size() - 2);

#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse const value - string `" << str << "`" << std::endl;
#endif

      (yyval.constantNode) = new ast::StringConstantNode(std::move(str));
    }
#line 2481 "src/out/parser.cpp"
    break;

    case 45: /* const_value: TRUE  */
#line 912 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse const value - true" << std::endl;
#endif

      (yyval.constantNode) = new ast::BooleanConstantNode(true);
    }
#line 2493 "src/out/parser.cpp"
    break;

    case 46: /* const_value: FALSE  */
#line 920 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse const value - false" << std::endl;
#endif

      (yyval.constantNode) = new ast::BooleanConstantNode(false);
    }
#line 2505 "src/out/parser.cpp"
    break;

    case 47: /* const_value: MAXINT  */
#line 928 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse const value - maxint" << std::endl;
#endif

      (yyval.constantNode) = new ast::IntegerConstantNode(255);
    }
#line 2517 "src/out/parser.cpp"
    break;

    case 48: /* const_value: MINUS MAXINT  */
#line 936 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse const value - signed maxint" << std::endl;
#endif

      (yyval.constantNode) = new ast::IntegerConstantNode(-255);
    }
#line 2529 "src/out/parser.cpp"
    break;

    case 49: /* type_part: %empty  */
#line 946 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse empty type part" << std::endl;
#endif

      (yyval.typePartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::TypeNode*>*>();
    }
#line 2541 "src/out/parser.cpp"
    break;

    case 50: /* type_part: TYPE type_decl_list  */
#line 954 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse type part" << std::endl;
#endif

      (yyval.typePartList) = (yyvsp[0].typePartList);
    }
#line 2553 "src/out/parser.cpp"
    break;

    case 51: /* type_decl_list: type_decl_list type_def  */
#line 964 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse type decl list 1" << std::endl;
#endif

      (yyval.typePartList) = (yyvsp[-1].typePartList);
      (yyval.typePartList)->push_back((yyvsp[0].typePartListElement));
    }
#line 2566 "src/out/parser.cpp"
    break;

    case 52: /* type_decl_list: type_def  */
#line 973 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse type decl list 2" << std::endl;
#endif

      (yyval.typePartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::TypeNode*>*>();
      (yyval.typePartList)->push_back((yyvsp[0].typePartListElement));
    }
#line 2579 "src/out/parser.cpp"
    break;

    case 53: /* type_def: identifier EQUAL type_decl SEMICOLON  */
#line 984 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse type def 1" << std::endl;
#endif

      std::string typeType;
      try {
        typeType = (yyvsp[-1].typeNode)->flat();
      } catch (std::runtime_error& err) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
        fatalError = true;
        YYERROR;
      }

      if (!saveType((yyvsp[-3].identifierNode), typeType)) {
        YYERROR;
      }

      (yyval.typePartListElement) = new std::pair<ast::IdentifierNode*, ast::TypeNode*>((yyvsp[-3].identifierNode), (yyvsp[-1].typeNode));
    }
#line 2603 "src/out/parser.cpp"
    break;

    case 54: /* type_def: identifier EQUAL type_decl  */
#line 1004 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse type def 2" << std::endl;
#endif

      std::string typeType;
      try {
        typeType = (yyvsp[0].typeNode)->flat();
      } catch (std::runtime_error& err) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
        fatalError = true;
        YYERROR;
      }

      if (!saveType((yyvsp[-2].identifierNode), typeType)) {
        YYERROR;
      }

      (yyval.typePartListElement) = new std::pair<ast::IdentifierNode*, ast::TypeNode*>((yyvsp[-2].identifierNode), (yyvsp[0].typeNode));
      parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2628 "src/out/parser.cpp"
    break;

    case 55: /* type_decl: simple_type  */
#line 1027 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse simple type" << std::endl;
#endif

      (yyval.typeNode) = (yyvsp[0].simpleTypeNode);
    }
#line 2640 "src/out/parser.cpp"
    break;

    case 56: /* type_decl: array_type_decl  */
#line 1035 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse array type" << std::endl;
#endif

      (yyval.typeNode) = (yyvsp[0].arrayTypeNode);
    }
#line 2652 "src/out/parser.cpp"
    break;

    case 57: /* type_decl: record_type_decl  */
#line 1043 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse record type" << std::endl;
#endif

      (yyval.typeNode) = (yyvsp[0].recordTypeNode);
    }
#line 2664 "src/out/parser.cpp"
    break;

    case 58: /* record_type_decl: RECORD field_decl_list END  */
#line 1053 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse record type" << std::endl;
#endif

      std::set<std::string> fields;
      for (std::size_t i = 0; i < (yyvsp[-1].fieldDeclList)->size(); i++) {
        for (std::size_t j = 0; j < (yyvsp[-1].fieldDeclList)->at(i)->first->size(); j++) {
          std::string field = (yyvsp[-1].fieldDeclList)->at(i)->first->at(j)->getName();
          if (fields.find(field) != fields.end()) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", field name `" + field + "` duplication");
            fatalError = true;
            YYERROR;
          }
          fields.insert(field);
        }
      }

      (yyval.recordTypeNode) = new ast::RecordTypeNode((yyvsp[-1].fieldDeclList));
    }
#line 2689 "src/out/parser.cpp"
    break;

    case 59: /* field_decl_list: field_decl_list field_decl  */
#line 1076 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse field decl list 1" << std::endl;
#endif

      (yyval.fieldDeclList) = (yyvsp[-1].fieldDeclList);
      (yyval.fieldDeclList)->push_back((yyvsp[0].fieldDeclListElement));
    }
#line 2702 "src/out/parser.cpp"
    break;

    case 60: /* field_decl_list: field_decl  */
#line 1085 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse field decl list 2" << std::endl;
#endif

      (yyval.fieldDeclList) = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
      (yyval.fieldDeclList)->push_back((yyvsp[0].fieldDeclListElement));
    }
#line 2715 "src/out/parser.cpp"
    break;

    case 61: /* field_decl: name_list COLON type_decl SEMICOLON  */
#line 1096 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse field decl 1" << std::endl;
#endif
      (yyval.fieldDeclListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-3].identifierList), (yyvsp[-1].typeNode));
    }
#line 2726 "src/out/parser.cpp"
    break;

    case 62: /* field_decl: name_list COLON type_decl  */
#line 1103 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse field decl 2" << std::endl;
#endif
      (yyval.fieldDeclListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-2].identifierList), (yyvsp[0].typeNode));
      parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2738 "src/out/parser.cpp"
    break;

    case 63: /* array_type_decl: ARRAY LB simple_type RB OF type_decl  */
#line 1113 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse array type" << std::endl;
#endif

      try {
        if (!isBasicOrEnumType((yyvsp[-3].simpleTypeNode)->flat()) && !isRangeType((yyvsp[-3].simpleTypeNode)->flat())) {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", invalid variable type");
          fatalError = true;
          YYERROR;
        }
      } catch (std::runtime_error& err) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
        fatalError = true;
        YYERROR;
      }

      try {
        if (!isBasicOrEnumOrArrayOrRecordType((yyvsp[0].typeNode)->flat())) {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", invalid return type");
          fatalError = true;
          YYERROR;
        }
      } catch (std::runtime_error& err) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
        fatalError = true;
        YYERROR;
      }

      if ((yyvsp[-3].simpleTypeNode)->getRepresentation() == ast::SimpleTypeNode::Representation::CONST_RANGE) {
        ast::ConstRangeTypeNode* range = dynamic_cast<ast::ConstRangeTypeNode*>((yyvsp[-3].simpleTypeNode));
        const std::string& leftType = range->getLowerBound()->flatType();
        const std::string& rightType = range->getUpperBound()->flatType();
        const std::string& leftVal = range->getLowerBound()->flat();
        const std::string& rightVal = range->getUpperBound()->flat();
        if (leftType != rightType) {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", array range bounds must have the same type");
          fatalError = true;
          YYERROR;
        }
        else if (leftType == "string" || rightType == "string") {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", array range bounds cannot be string");
          fatalError = true;
          YYERROR;
        }

        if (isInteger(leftVal)) {
          int int1 = std::atoi(leftVal.c_str());
          int int2 = std::atoi(rightVal.c_str());
          if (int2 < int1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", invalid array range bounds");
            fatalError = true;
            YYERROR;
          }
        }

        if (isChar(leftVal)) {
          int char1 = static_cast<int>(leftVal.at(0));
          int char2 = static_cast<int>(rightVal.at(0));
          if (char2 < char1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", invalid array range bounds");
            fatalError = true;
            YYERROR;
          }
        }

        if (leftVal == "true" && rightVal == "false") {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", invalid array range bounds");
          fatalError = true;
          YYERROR;
        }
      }

      (yyval.arrayTypeNode) = new ast::ArrayTypeNode((yyvsp[-3].simpleTypeNode), (yyvsp[0].typeNode));
    }
#line 2820 "src/out/parser.cpp"
    break;

    case 64: /* simple_type: identifier  */
#line 1193 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse simple type - identifier" << std::endl;
#endif

      (yyval.simpleTypeNode) = new ast::RenameTypeNode((yyvsp[0].identifierNode));
    }
#line 2832 "src/out/parser.cpp"
    break;

    case 65: /* simple_type: LP name_list RP  */
#line 1201 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse simple type - enum" << std::endl;
#endif

      (yyval.simpleTypeNode) = new ast::EnumerationTypeNode((yyvsp[-1].identifierList));
    }
#line 2844 "src/out/parser.cpp"
    break;

    case 66: /* simple_type: const_value DOUBLEDOT const_value  */
#line 1209 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse simple type - range 1" << std::endl;
#endif

      (yyval.simpleTypeNode) = new ast::ConstRangeTypeNode((yyvsp[-2].constantNode), (yyvsp[0].constantNode));
    }
#line 2856 "src/out/parser.cpp"
    break;

    case 67: /* simple_type: identifier DOUBLEDOT identifier  */
#line 1217 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse simple type - range 4" << std::endl;
#endif

      (yyval.simpleTypeNode) = new ast::VarRangeTypeNode((yyvsp[-2].identifierNode), (yyvsp[0].identifierNode));
    }
#line 2868 "src/out/parser.cpp"
    break;

    case 68: /* simple_type: INT_TYPE  */
#line 1225 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse simple type - int" << std::endl;
#endif

      (yyval.simpleTypeNode) = new ast::BasicTypeNode(ast::BasicTypeNode::BasicType::INTEGER);
    }
#line 2880 "src/out/parser.cpp"
    break;

    case 69: /* simple_type: BOOL_TYPE  */
#line 1233 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse simple type - bool" << std::endl;
#endif

      (yyval.simpleTypeNode) = new ast::BasicTypeNode(ast::BasicTypeNode::BasicType::BOOLEAN);
    }
#line 2892 "src/out/parser.cpp"
    break;

    case 70: /* simple_type: CHAR_TYPE  */
#line 1241 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse simple type - char" << std::endl;
#endif

      (yyval.simpleTypeNode) = new ast::BasicTypeNode(ast::BasicTypeNode::BasicType::CHAR);
    }
#line 2904 "src/out/parser.cpp"
    break;

    case 71: /* name_list: name_list COMMA identifier  */
#line 1251 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse name list 1" << std::endl;
#endif

      (yyval.identifierList) = (yyvsp[-2].identifierList);
      (yyval.identifierList)->push_back((yyvsp[0].identifierNode));
    }
#line 2917 "src/out/parser.cpp"
    break;

    case 72: /* name_list: identifier  */
#line 1260 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse name list 2" << std::endl;
#endif

      (yyval.identifierList) = new std::vector<ast::IdentifierNode*>();
      (yyval.identifierList)->push_back((yyvsp[0].identifierNode));
    }
#line 2930 "src/out/parser.cpp"
    break;

    case 73: /* identifier: IDENT_NAME  */
#line 1271 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse identifier `" << (*(yyvsp[0].token).stringValue) << "`" << std::endl;
#endif

      std::string name{*(yyvsp[0].token).stringValue};
      (yyval.identifierNode) = new ast::IdentifierNode(std::move(name));
    }
#line 2943 "src/out/parser.cpp"
    break;

    case 74: /* routine_body: compound_stmt  */
#line 1282 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse routine body" << std::endl;
#endif

      (yyval.routineBodyNode) = new ast::RoutineBodyNode((yyvsp[0].compoundStatementNode));
    }
#line 2955 "src/out/parser.cpp"
    break;

    case 75: /* compound_stmt: BBEGIN stmt_list END  */
#line 1292 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse compound statement 1" << std::endl;
#endif

      (yyval.compoundStatementNode) = new ast::CompoundStatementNode((yyvsp[-1].statementNodeList));
    }
#line 2967 "src/out/parser.cpp"
    break;

    case 76: /* compound_stmt: BBEGIN stmt_list  */
#line 1300 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse compound statement 2" << std::endl;
#endif

      (yyval.compoundStatementNode) = new ast::CompoundStatementNode((yyvsp[0].statementNodeList));
      parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of end");
    }
#line 2980 "src/out/parser.cpp"
    break;

    case 77: /* compound_loop_stmt: BBEGIN loop_stmt_list END  */
#line 1311 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse loop compound statement 1" << std::endl;
#endif

      (yyval.compoundStatementNode) = new ast::CompoundStatementNode((yyvsp[-1].statementNodeList));
    }
#line 2992 "src/out/parser.cpp"
    break;

    case 78: /* compound_loop_stmt: BBEGIN loop_stmt_list  */
#line 1319 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse loop compound statement 2" << std::endl;
#endif

      (yyval.compoundStatementNode) = new ast::CompoundStatementNode((yyvsp[0].statementNodeList));
      parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of end");
    }
#line 3005 "src/out/parser.cpp"
    break;

    case 79: /* stmt_list: %empty  */
#line 1330 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse empty statement list" << std::endl;
#endif

      (yyval.statementNodeList) = new std::vector<ast::StatementNode*>();
    }
#line 3017 "src/out/parser.cpp"
    break;

    case 80: /* stmt_list: stmt_list stmt SEMICOLON  */
#line 1338 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse statement list 1" << std::endl;
#endif

      (yyval.statementNodeList) = (yyvsp[-2].statementNodeList);
      (yyval.statementNodeList)->push_back((yyvsp[-1].statementNode));
    }
#line 3030 "src/out/parser.cpp"
    break;

    case 81: /* stmt_list: stmt_list stmt  */
#line 1347 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse statement list 2" << std::endl;
#endif

      (yyval.statementNodeList) = (yyvsp[-1].statementNodeList);
      (yyval.statementNodeList)->push_back((yyvsp[0].statementNode));
      parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 3044 "src/out/parser.cpp"
    break;

    case 82: /* loop_stmt_list: %empty  */
#line 1359 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse empty loop statement list" << std::endl;
#endif

      (yyval.statementNodeList) = new std::vector<ast::StatementNode*>();
    }
#line 3056 "src/out/parser.cpp"
    break;

    case 83: /* loop_stmt_list: loop_stmt_list loop_stmt SEMICOLON  */
#line 1367 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse loop statement list 1" << std::endl;
#endif

      (yyval.statementNodeList) = (yyvsp[-2].statementNodeList);
      (yyval.statementNodeList)->push_back((yyvsp[-1].statementNode));
    }
#line 3069 "src/out/parser.cpp"
    break;

    case 84: /* loop_stmt_list: loop_stmt_list loop_stmt  */
#line 1376 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse loop statement list 2" << std::endl;
#endif

      (yyval.statementNodeList) = (yyvsp[-1].statementNodeList);
      (yyval.statementNodeList)->push_back((yyvsp[0].statementNode));
      parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 3083 "src/out/parser.cpp"
    break;

    case 85: /* stmt: INTEGER COLON no_label_stmt  */
#line 1388 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse statement with label " << (yyvsp[-2].token).numericalValue << std::endl;
#endif

#ifndef YACC_ENABLE_GOTO
      parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", goto is disabled");
      fatalError = true;
      YYERROR;
#endif

      (yyval.statementNode) = (yyvsp[0].statementNode);
      (yyval.statementNode)->setLabel((yyvsp[-2].token).numericalValue);
    }
#line 3102 "src/out/parser.cpp"
    break;

    case 86: /* stmt: no_label_stmt  */
#line 1403 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse statement without label" << std::endl;
#endif

      (yyval.statementNode) = (yyvsp[0].statementNode);
    }
#line 3114 "src/out/parser.cpp"
    break;

    case 87: /* loop_stmt: INTEGER COLON no_label_loop_stmt  */
#line 1413 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse loop statement with label " << (yyvsp[-2].token).numericalValue << std::endl;
#endif

#ifndef YACC_ENABLE_GOTO
      parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", goto is disabled");
      fatalError = true;
      YYERROR;
#endif

      (yyval.statementNode) = (yyvsp[0].statementNode);
      (yyval.statementNode)->setLabel((yyvsp[-2].token).numericalValue);
    }
#line 3133 "src/out/parser.cpp"
    break;

    case 88: /* loop_stmt: no_label_loop_stmt  */
#line 1428 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse loop statement without label" << std::endl;
#endif

      (yyval.statementNode) = (yyvsp[0].statementNode);
    }
#line 3145 "src/out/parser.cpp"
    break;

    case 89: /* no_label_stmt: assign_stmt  */
#line 1438 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse no label statement - assign" << std::endl;
#endif

      (yyval.statementNode) = (yyvsp[0].assignNode);
    }
#line 3157 "src/out/parser.cpp"
    break;

    case 90: /* no_label_stmt: compound_stmt  */
#line 1446 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse no label statement - compound" << std::endl;
#endif

      (yyval.statementNode) = (yyvsp[0].compoundStatementNode);
    }
#line 3169 "src/out/parser.cpp"
    break;

    case 91: /* no_label_stmt: goto_stmt  */
#line 1454 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse no label statement - goto" << std::endl;
#endif

#ifndef YACC_ENABLE_GOTO
      parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", goto is disabled");
      fatalError = true;
      YYERROR;
#endif

      (yyval.statementNode) = (yyvsp[0].gotoNode);
    }
#line 3187 "src/out/parser.cpp"
    break;

    case 92: /* no_label_stmt: if_stmt  */
#line 1468 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse no label statement - if" << std::endl;
#endif

      (yyval.statementNode) = (yyvsp[0].ifNode);
    }
#line 3199 "src/out/parser.cpp"
    break;

    case 93: /* no_label_stmt: repeat_stmt  */
#line 1476 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse no label statement - repeat" << std::endl;
#endif

      (yyval.statementNode) = (yyvsp[0].repeatNode);
    }
#line 3211 "src/out/parser.cpp"
    break;

    case 94: /* no_label_stmt: while_stmt  */
#line 1484 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse no label statement - while" << std::endl;
#endif

      (yyval.statementNode) = (yyvsp[0].whileNode);
    }
#line 3223 "src/out/parser.cpp"
    break;

    case 95: /* no_label_stmt: case_stmt  */
#line 1492 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse no label statement - case" << std::endl;
#endif

      (yyval.statementNode) = (yyvsp[0].caseNode);
    }
#line 3235 "src/out/parser.cpp"
    break;

    case 96: /* no_label_stmt: for_stmt  */
#line 1500 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse no label statement - for" << std::endl;
#endif

      (yyval.statementNode) = (yyvsp[0].forNode);
    }
#line 3247 "src/out/parser.cpp"
    break;

    case 97: /* no_label_stmt: proc_stmt  */
#line 1508 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse no label statement - proc" << std::endl;
#endif

      (yyval.statementNode) = (yyvsp[0].callNode);
    }
#line 3259 "src/out/parser.cpp"
    break;

    case 98: /* no_label_loop_stmt: assign_stmt  */
#line 1518 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse no label loop statement - assign" << std::endl;
#endif

      (yyval.statementNode) = (yyvsp[0].assignNode);
    }
#line 3271 "src/out/parser.cpp"
    break;

    case 99: /* no_label_loop_stmt: compound_loop_stmt  */
#line 1526 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse no label loop statement - compound" << std::endl;
#endif

      (yyval.statementNode) = (yyvsp[0].compoundStatementNode);
    }
#line 3283 "src/out/parser.cpp"
    break;

    case 100: /* no_label_loop_stmt: goto_stmt  */
#line 1534 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse no label loop statement - goto" << std::endl;
#endif

      (yyval.statementNode) = (yyvsp[0].gotoNode);
    }
#line 3295 "src/out/parser.cpp"
    break;

    case 101: /* no_label_loop_stmt: if_loop_stmt  */
#line 1542 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse no label loop statement - if" << std::endl;
#endif

      (yyval.statementNode) = (yyvsp[0].ifNode);
    }
#line 3307 "src/out/parser.cpp"
    break;

    case 102: /* no_label_loop_stmt: repeat_stmt  */
#line 1550 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse no label loop statement - repeat" << std::endl;
#endif

      (yyval.statementNode) = (yyvsp[0].repeatNode);
    }
#line 3319 "src/out/parser.cpp"
    break;

    case 103: /* no_label_loop_stmt: while_stmt  */
#line 1558 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse no label loop statement - while" << std::endl;
#endif

      (yyval.statementNode) = (yyvsp[0].whileNode);
    }
#line 3331 "src/out/parser.cpp"
    break;

    case 104: /* no_label_loop_stmt: case_loop_stmt  */
#line 1566 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse no label loop statement - case" << std::endl;
#endif

      (yyval.statementNode) = (yyvsp[0].caseNode);
    }
#line 3343 "src/out/parser.cpp"
    break;

    case 105: /* no_label_loop_stmt: for_stmt  */
#line 1574 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse no label loop statement - for" << std::endl;
#endif

      (yyval.statementNode) = (yyvsp[0].forNode);
    }
#line 3355 "src/out/parser.cpp"
    break;

    case 106: /* no_label_loop_stmt: proc_stmt  */
#line 1582 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse no label loop statement - proc" << std::endl;
#endif

      (yyval.statementNode) = (yyvsp[0].callNode);
    }
#line 3367 "src/out/parser.cpp"
    break;

    case 107: /* no_label_loop_stmt: BREAK  */
#line 1590 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse no label loop statement - break" << std::endl;
#endif

      (yyval.statementNode) = new ast::BreakNode();
    }
#line 3379 "src/out/parser.cpp"
    break;

    case 108: /* no_label_loop_stmt: CONTINUE  */
#line 1598 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse no label loop statement - continue" << std::endl;
#endif

      (yyval.statementNode) = new ast::ContinueNode();
    }
#line 3391 "src/out/parser.cpp"
    break;

    case 109: /* assign_stmt: lvalue ASSIGN expression  */
#line 1608 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse assign statement" << std::endl;
#endif

      if (!isLeftValueCompatible((yyvsp[-2].expressionNode))) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", left side of assignment must be assignable");
        fatalError = true;
        YYERROR;
      }
      else if ((yyvsp[-2].expressionNode)->getInferredType() != (yyvsp[0].expressionNode)->getInferredType()) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", both sides should be equal type");
        std::cout << (yyvsp[-2].expressionNode)->getInferredType() << "  " << (yyvsp[0].expressionNode)->getInferredType() << std::endl;
        fatalError = true;
        YYERROR;
      }
      else {
        (yyval.assignNode) = new ast::AssignNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode));
      }
    }
#line 3416 "src/out/parser.cpp"
    break;

    case 110: /* goto_stmt: GOTO INTEGER  */
#line 1631 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse goto statement to " << (yyvsp[0].token).numericalValue << std::endl;
#endif

      (yyval.gotoNode) = new ast::GotoNode((yyvsp[0].token).numericalValue);
    }
#line 3428 "src/out/parser.cpp"
    break;

    case 111: /* if_stmt: IF expression THEN stmt else_clause  */
#line 1641 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse if statement 1" << std::endl;
#endif

      if ((yyvsp[-3].expressionNode)->getInferredType() == "boolean") {
        (yyval.ifNode) = new ast::IfNode((yyvsp[-3].expressionNode), (yyvsp[-1].statementNode), (yyvsp[0].ifNode));
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", if condition must be boolean expression");
        fatalError = true;
        YYERROR;
      }
    }
#line 3447 "src/out/parser.cpp"
    break;

    case 112: /* if_stmt: IF expression stmt else_clause  */
#line 1656 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse if statement 2" << std::endl;
#endif

      if ((yyvsp[-2].expressionNode)->getInferredType() == "boolean") {
        (yyval.ifNode) = new ast::IfNode((yyvsp[-2].expressionNode), (yyvsp[-1].statementNode), (yyvsp[0].ifNode));
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of then");
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", if condition must be boolean expression");
        fatalError = true;
        YYERROR;
      }
    }
#line 3467 "src/out/parser.cpp"
    break;

    case 113: /* if_loop_stmt: IF expression THEN loop_stmt else_loop_clause  */
#line 1674 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse if loop statement 1" << std::endl;
#endif

      if ((yyvsp[-3].expressionNode)->getInferredType() == "boolean") {
        (yyval.ifNode) = new ast::IfNode((yyvsp[-3].expressionNode), (yyvsp[-1].statementNode), (yyvsp[0].ifNode));
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", if condition must be boolean expression");
        fatalError = true;
        YYERROR;
      }
    }
#line 3486 "src/out/parser.cpp"
    break;

    case 114: /* if_loop_stmt: IF expression loop_stmt else_loop_clause  */
#line 1689 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse if loop statement 2" << std::endl;
#endif

      if ((yyvsp[-2].expressionNode)->getInferredType() == "boolean") {
        (yyval.ifNode) = new ast::IfNode((yyvsp[-2].expressionNode), (yyvsp[-1].statementNode), (yyvsp[0].ifNode));
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of then");
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", if condition must be boolean expression");
        fatalError = true;
        YYERROR;
      }
    }
#line 3506 "src/out/parser.cpp"
    break;

    case 115: /* else_clause: %empty  */
#line 1707 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse empty else clause" << std::endl;
#endif

      (yyval.ifNode) = new ast::IfNode(nullptr, nullptr);
    }
#line 3518 "src/out/parser.cpp"
    break;

    case 116: /* else_clause: ELSE stmt  */
#line 1715 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse else clause" << std::endl;
#endif

      (yyval.ifNode) = new ast::IfNode(nullptr, nullptr, (yyvsp[0].statementNode));
    }
#line 3530 "src/out/parser.cpp"
    break;

    case 117: /* else_loop_clause: %empty  */
#line 1725 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse empty else loop clause" << std::endl;
#endif

      (yyval.ifNode) = new ast::IfNode(nullptr, nullptr);
    }
#line 3542 "src/out/parser.cpp"
    break;

    case 118: /* else_loop_clause: ELSE loop_stmt  */
#line 1733 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse else loop clause" << std::endl;
#endif

      (yyval.ifNode) = new ast::IfNode(nullptr, nullptr, (yyvsp[0].statementNode));
    }
#line 3554 "src/out/parser.cpp"
    break;

    case 119: /* repeat_stmt: REPEAT loop_stmt_list UNTIL expression  */
#line 1743 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse repeat statement" << std::endl;
#endif

      if ((yyvsp[0].expressionNode)->getInferredType() == "boolean") {
        (yyval.repeatNode) = new ast::RepeatNode((yyvsp[0].expressionNode), new ast::CompoundStatementNode((yyvsp[-2].statementNodeList)));
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", repeat condition must be boolean expression");
        fatalError = true;
        YYERROR;
      }
    }
#line 3573 "src/out/parser.cpp"
    break;

    case 120: /* repeat_stmt: %empty  */
#line 1758 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse empty repeat statement" << std::endl;
#endif
    }
#line 3583 "src/out/parser.cpp"
    break;

    case 121: /* while_stmt: WHILE expression DO loop_stmt  */
#line 1766 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse while statement" << std::endl;
#endif

      if ((yyvsp[-2].expressionNode)->getInferredType() == "boolean") {
        (yyval.whileNode) = new ast::WhileNode((yyvsp[-2].expressionNode), (yyvsp[0].statementNode));
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", while condition must be boolean expression");
        fatalError = true;
        YYERROR;
      }
    }
#line 3602 "src/out/parser.cpp"
    break;

    case 122: /* case_stmt: CASE expression OF case_expr_list END  */
#line 1783 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse case statement" << std::endl;
#endif

      if (!isBasicOrEnumType((yyvsp[-3].expressionNode)->getInferredType())) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", case expression must be integer, char, boolean or enum type");
        fatalError = true;
        YYERROR;
      }

      bool otherwiseFound{false};
      for (const auto& caseExpr : *(yyvsp[-1].caseExprList)) {
        if (caseExpr->first != nullptr) {
          if (otherwiseFound) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", otherwise must be last label");
            fatalError = true;
            YYERROR;
          }

          if (caseExpr->first->getOperation() != ast::ExpressionNode::Operation::SPECIAL) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", case value must be constant");
            fatalError = true;
            YYERROR;
          }

          ast::SpecialExpressionNode* specialExpr = dynamic_cast<ast::SpecialExpressionNode*>(caseExpr->first);
          if (specialExpr->getFunctionName() != ast::SpecialExpressionNode::FunctionName::CONST && specialExpr->getFunctionName() != ast::SpecialExpressionNode::FunctionName::ENUM_ELEMENT) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", case value must be constant");
            fatalError = true;
            YYERROR;
          }

          if (specialExpr->getInferredType() != (yyvsp[-3].expressionNode)->getInferredType()) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", case expression must be the same type as case value");
            fatalError = true;
            YYERROR;
          }
        }
        else if (otherwiseFound) {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", otherwise label can be used only once");
          fatalError = true;
          YYERROR;
        }
        else {
          otherwiseFound = true;
        }
      }

      (yyval.caseNode) = new ast::CaseNode((yyvsp[-3].expressionNode), (yyvsp[-1].caseExprList));
    }
#line 3659 "src/out/parser.cpp"
    break;

    case 123: /* case_loop_stmt: CASE expression OF case_loop_expr_list END  */
#line 1838 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse case loop statement" << std::endl;
#endif

      if (!isBasicOrEnumType((yyvsp[-3].expressionNode)->getInferredType())) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", case expression must be integer, char, boolean or enum type");
        fatalError = true;
        YYERROR;
      }

      bool otherwiseFound{false};
      for (const auto& caseExpr : *(yyvsp[-1].caseExprList)) {
        if (caseExpr->first != nullptr) {
          if (otherwiseFound) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", otherwise must be last label");
            fatalError = true;
            YYERROR;
          }

          if (caseExpr->first->getOperation() != ast::ExpressionNode::Operation::SPECIAL) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", case value must be constant");
            fatalError = true;
            YYERROR;
          }

          ast::SpecialExpressionNode* specialExpr = dynamic_cast<ast::SpecialExpressionNode*>(caseExpr->first);
          if (specialExpr->getFunctionName() != ast::SpecialExpressionNode::FunctionName::CONST && specialExpr->getFunctionName() != ast::SpecialExpressionNode::FunctionName::ENUM_ELEMENT) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", case value must be constant");
            fatalError = true;
            YYERROR;
          }

          if (specialExpr->getInferredType() != (yyvsp[-3].expressionNode)->getInferredType()) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", case expression must be the same type as case value");
            fatalError = true;
            YYERROR;
          }
        }
        else if (otherwiseFound) {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", otherwise label can be used only once");
          fatalError = true;
          YYERROR;
        }
        else {
          otherwiseFound = true;
        }
      }

      (yyval.caseNode) = new ast::CaseNode((yyvsp[-3].expressionNode), (yyvsp[-1].caseExprList));
    }
#line 3716 "src/out/parser.cpp"
    break;

    case 124: /* case_expr_list: case_expr_list case_expr  */
#line 1893 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse case expr list 1" << std::endl;
#endif

      (yyval.caseExprList) = (yyvsp[-1].caseExprList);
      (yyval.caseExprList)->push_back((yyvsp[0].caseExpr));
    }
#line 3729 "src/out/parser.cpp"
    break;

    case 125: /* case_expr_list: case_expr  */
#line 1902 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse case expr list 2" << std::endl;
#endif

      (yyval.caseExprList) = new std::vector<std::pair<ast::ExpressionNode*, ast::StatementNode*>*>();
      (yyval.caseExprList)->push_back((yyvsp[0].caseExpr));
    }
#line 3742 "src/out/parser.cpp"
    break;

    case 126: /* case_loop_expr_list: case_loop_expr_list case_loop_expr  */
#line 1913 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse case loop expr list 1" << std::endl;
#endif

      (yyval.caseExprList) = (yyvsp[-1].caseExprList);
      (yyval.caseExprList)->push_back((yyvsp[0].caseExpr));
    }
#line 3755 "src/out/parser.cpp"
    break;

    case 127: /* case_loop_expr_list: case_loop_expr  */
#line 1922 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse case loop expr list 2" << std::endl;
#endif

      (yyval.caseExprList) = new std::vector<std::pair<ast::ExpressionNode*, ast::StatementNode*>*>();
      (yyval.caseExprList)->push_back((yyvsp[0].caseExpr));
    }
#line 3768 "src/out/parser.cpp"
    break;

    case 128: /* case_expr: expression COLON stmt SEMICOLON  */
#line 1933 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse case expr 1" << std::endl;
#endif

      (yyval.caseExpr) = new std::pair<ast::ExpressionNode*, ast::StatementNode*>((yyvsp[-3].expressionNode), (yyvsp[-1].statementNode));
    }
#line 3780 "src/out/parser.cpp"
    break;

    case 129: /* case_expr: OTHERWISE stmt SEMICOLON  */
#line 1941 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse case expr 3" << std::endl;
#endif

      (yyval.caseExpr) = new std::pair<ast::ExpressionNode*, ast::StatementNode*>(nullptr, (yyvsp[-1].statementNode));
    }
#line 3792 "src/out/parser.cpp"
    break;

    case 130: /* case_loop_expr: expression COLON loop_stmt SEMICOLON  */
#line 1951 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse case loop expr 1" << std::endl;
#endif

      (yyval.caseExpr) = new std::pair<ast::ExpressionNode*, ast::StatementNode*>((yyvsp[-3].expressionNode), (yyvsp[-1].statementNode));
    }
#line 3804 "src/out/parser.cpp"
    break;

    case 131: /* case_loop_expr: OTHERWISE loop_stmt SEMICOLON  */
#line 1959 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse case loop expr 3" << std::endl;
#endif

      (yyval.caseExpr) = new std::pair<ast::ExpressionNode*, ast::StatementNode*>(nullptr, (yyvsp[-1].statementNode));
    }
#line 3816 "src/out/parser.cpp"
    break;

    case 132: /* for_stmt: for_head loop_stmt  */
#line 1969 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse for statement" << std::endl;
#endif

      if (variableIsReassignedS((yyvsp[-1].forNode)->getIterator()->getName(), (yyvsp[0].statementNode))) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", loop variable `" + (yyvsp[-1].forNode)->getIterator()->getName() + "` cannot be reassigned");
        fatalError = true;
        YYERROR;
      }

      (yyval.forNode) = (yyvsp[-1].forNode);
      (yyval.forNode)->setStatements(std::unique_ptr<ast::StatementNode>((yyvsp[0].statementNode)));

      ctx->getLookupTable().unDefineVariable((yyvsp[-1].forNode)->getIterator()->getName(), ctx->getCurrentScope());
    }
#line 3837 "src/out/parser.cpp"
    break;

    case 133: /* for_head: FOR identifier ASSIGN expression TO expression DO  */
#line 1988 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse for head 1" << std::endl;
#endif

      if ((yyvsp[-3].expressionNode)->getInferredType() != (yyvsp[-1].expressionNode)->getInferredType()) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", for begin and end values must be the same type");
        fatalError = true;
        YYERROR;
      }
      else if (!isBasicOrEnumType((yyvsp[-3].expressionNode)->getInferredType())) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", for begin and end values must be integer, char, boolean or enum type");
        fatalError = true;
        YYERROR;
      }
      else {
        if (!saveVariables(new std::vector<ast::IdentifierNode*>{(yyvsp[-5].identifierNode)}, (yyvsp[-3].expressionNode)->getInferredType())) {
          YYERROR;
        }
        (yyval.forNode) = new ast::ForNode((yyvsp[-5].identifierNode), (yyvsp[-3].expressionNode), (yyvsp[-1].expressionNode), nullptr, ast::ForNode::Direction::INCREMENT);
      }
    }
#line 3864 "src/out/parser.cpp"
    break;

    case 134: /* for_head: FOR identifier ASSIGN expression DOWNTO expression DO  */
#line 2011 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse for head 2" << std::endl;
#endif

      if ((yyvsp[-3].expressionNode)->getInferredType() != (yyvsp[-1].expressionNode)->getInferredType()) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", for begin and end values must be the same type");
        fatalError = true;
        YYERROR;
      }
      else if (!isBasicOrEnumType((yyvsp[-3].expressionNode)->getInferredType())) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", for begin and end values must be integer, char, boolean or enum type");
        fatalError = true;
        YYERROR;
      }
      else {
        if (!saveVariables(new std::vector<ast::IdentifierNode*>{(yyvsp[-5].identifierNode)}, (yyvsp[-3].expressionNode)->getInferredType())) {
          YYERROR;
        }
        (yyval.forNode) = new ast::ForNode((yyvsp[-5].identifierNode), (yyvsp[-3].expressionNode), (yyvsp[-1].expressionNode), nullptr, ast::ForNode::Direction::DECREMENT);
      }
    }
#line 3891 "src/out/parser.cpp"
    break;

    case 135: /* proc_stmt: identifier  */
#line 2036 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse procedure statement" << std::endl;
#endif

      if (!ctx->getLookupTable().isRoutineDefined((yyvsp[0].identifierNode)->getName(), ctx->getCurrentScope())) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", routine `" + (yyvsp[0].identifierNode)->getName() + "` is not defined");
        fatalError = true;
        YYERROR;
      }
      else if (!ctx->getLookupTable().getRoutine((yyvsp[0].identifierNode)->getName(), ctx->getCurrentScope()).args.empty()) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", missing arguments");
        fatalError = true;
        YYERROR;
      }
      else {
        (yyval.callNode) = new ast::UserDefineCallNode((yyvsp[0].identifierNode), nullptr);
      }
    }
#line 3915 "src/out/parser.cpp"
    break;

    case 136: /* proc_stmt: identifier LP args_list RP  */
#line 2056 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse procedure statement with args" << std::endl;
#endif

      if (!ctx->getLookupTable().isRoutineDefined((yyvsp[-3].identifierNode)->getName(), ctx->getCurrentScope())) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", routine `" + (yyvsp[-3].identifierNode)->getName() + "` is not defined");
        fatalError = true;
        YYERROR;
      }
      else if (!isFunctionArgumentsCompatible(ctx->getLookupTable().getRoutine((yyvsp[-3].identifierNode)->getName(), ctx->getCurrentScope()).args, (yyvsp[-1].argsList)->getArguments())) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", passed incompatible arguments");
        fatalError = true;
        YYERROR;
      }
      else {
        (yyval.callNode) = new ast::UserDefineCallNode((yyvsp[-3].identifierNode), (yyvsp[-1].argsList));
      }
    }
#line 3939 "src/out/parser.cpp"
    break;

    case 137: /* proc_stmt: READ LP factor RP  */
#line 2076 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse read statement" << std::endl;
#endif

      if (!isLeftValueCompatible((yyvsp[-1].expressionNode))) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for read - assignable argument expected");
        fatalError = true;
        YYERROR;
      }
      else if (!isBasicType((yyvsp[-1].expressionNode)->getInferredType())) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for read - integer, char or boolean expected");
        fatalError = true;
        YYERROR;
      }
      else {
        ast::ArgumentsListNode* args = new ast::ArgumentsListNode();
        args->addArgument((yyvsp[-1].expressionNode));
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::READ, args);
      }
    }
#line 3965 "src/out/parser.cpp"
    break;

    case 138: /* proc_stmt: READLN  */
#line 2099 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse readln statement" << std::endl;
#endif

      (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::READLN, nullptr);
    }
#line 3977 "src/out/parser.cpp"
    break;

    case 139: /* proc_stmt: WRITE LP args_list RP  */
#line 2107 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse write statement" << std::endl;
#endif

      bool allOk = true;
      for (auto arg : (yyvsp[-1].argsList)->getArguments()) {
        if (!isBasicType(arg->getInferredType()) && arg->getInferredType() != "string") {
          allOk = false;
          break;
        }
      }
      if (!allOk) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for write - integer, char, boolean or string expected");
        fatalError = true;
        YYERROR;
      }
      else {
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITE, (yyvsp[-1].argsList));
      }
    }
#line 4003 "src/out/parser.cpp"
    break;

    case 140: /* proc_stmt: WRITELN  */
#line 2129 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse writeln statement" << std::endl;
#endif

      (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITELN, nullptr);
    }
#line 4015 "src/out/parser.cpp"
    break;

    case 141: /* proc_stmt: WRITELN LP args_list RP  */
#line 2137 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse writeln statement with args" << std::endl;
#endif

      bool allOk = true;
      for (auto arg : (yyvsp[-1].argsList)->getArguments()) {
        if (!isBasicType(arg->getInferredType()) && arg->getInferredType() != "string") {
          allOk = false;
          break;
        }
      }

      if (!allOk) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for writeln - integer, char, boolean or string expected");
        fatalError = true;
        YYERROR;
      }
      else {
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITELN, (yyvsp[-1].argsList));
      }
    }
#line 4042 "src/out/parser.cpp"
    break;

    case 142: /* proc_stmt: MEMORYREAD LP args_list RP  */
#line 2160 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse memory read statement" << std::endl;
#endif

      if ((yyvsp[-1].argsList)->getArguments().size() == 3) {
        if ((yyvsp[-1].argsList)->getArguments().at(0)->getInferredType() != "integer") {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory read - first argument should be integer");
          fatalError = true;
          YYERROR;
        }
        else if ((yyvsp[-1].argsList)->getArguments().at(1)->getInferredType() != "integer") {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory read - second argument should be integer");
          fatalError = true;
          YYERROR;
        }
        else if (!isLeftValueCompatible((yyvsp[-1].argsList)->getArguments().at(2))) {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory read - assignable argument expected");
          fatalError = true;
          YYERROR;
        }
        else if (!isBasicType((yyvsp[-1].argsList)->getArguments().at(2)->getInferredType())) {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory read - integer, char or boolean expected");
          fatalError = true;
          YYERROR;
        }
        else {
          (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::MEMORY_READ, (yyvsp[-1].argsList));
        }
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for memory read - 3 arguments expected");
        fatalError = true;
        YYERROR;
      }
    }
#line 4083 "src/out/parser.cpp"
    break;

    case 143: /* proc_stmt: MEMORYWRITE LP args_list RP  */
#line 2197 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse memory write statement" << std::endl;
#endif

      if ((yyvsp[-1].argsList)->getArguments().size() == 3) {
        if ((yyvsp[-1].argsList)->getArguments().at(0)->getInferredType() != "integer") {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory write - first argument should be integer");
          fatalError = true;
          YYERROR;
        }
        else if ((yyvsp[-1].argsList)->getArguments().at(1)->getInferredType() != "integer") {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory write - second argument should be integer");
          fatalError = true;
          YYERROR;
        }
        else if (!isBasicType((yyvsp[-1].argsList)->getArguments().at(2)->getInferredType())) {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory write - integer, char or boolean expected");
          fatalError = true;
          YYERROR;
        }
        else {
          (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::MEMORY_WRITE, (yyvsp[-1].argsList));
        }
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for memory write - 3 arguments expected");
        fatalError = true;
        YYERROR;
      }
    }
#line 4119 "src/out/parser.cpp"
    break;

    case 144: /* proc_stmt: STACKREAD LP args_list RP  */
#line 2229 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse stack read statement" << std::endl;
#endif

      if ((yyvsp[-1].argsList)->getArguments().size() == 3) {
        if ((yyvsp[-1].argsList)->getArguments().at(0)->getInferredType() != "integer") {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack read - first argument should be integer");
          fatalError = true;
          YYERROR;
        }
        else if ((yyvsp[-1].argsList)->getArguments().at(1)->getInferredType() != "integer") {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack read - second argument should be integer");
          fatalError = true;
          YYERROR;
        }
        else if (!isLeftValueCompatible((yyvsp[-1].argsList)->getArguments().at(2))) {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack read - assignable argument expected");
          fatalError = true;
          YYERROR;
        }
        else if (!isBasicType((yyvsp[-1].argsList)->getArguments().at(2)->getInferredType())) {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack read - integer, char or boolean expected");
          fatalError = true;
          YYERROR;
        }
        else {
          (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::STACK_READ, (yyvsp[-1].argsList));
        }
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for stack read - 3 arguments expected");
        fatalError = true;
        YYERROR;
      }
    }
#line 4160 "src/out/parser.cpp"
    break;

    case 145: /* proc_stmt: STACKWRITE LP args_list RP  */
#line 2266 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse stack write statement" << std::endl;
#endif

      if ((yyvsp[-1].argsList)->getArguments().size() == 3) {
        if ((yyvsp[-1].argsList)->getArguments().at(0)->getInferredType() != "integer") {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack write - first argument should be integer");
          fatalError = true;
          YYERROR;
        }
        else if ((yyvsp[-1].argsList)->getArguments().at(1)->getInferredType() != "integer") {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack write - second argument should be integer");
          fatalError = true;
          YYERROR;
        }
        else if (!isBasicType((yyvsp[-1].argsList)->getArguments().at(2)->getInferredType())) {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack write - integer, char or boolean expected");
          fatalError = true;
          YYERROR;
        }
        else {
          (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::STACK_WRITE, (yyvsp[-1].argsList));
        }
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for stack write - 3 arguments expected");
        fatalError = true;
        YYERROR;
      }
    }
#line 4196 "src/out/parser.cpp"
    break;

    case 146: /* args_list: args_list COMMA expression  */
#line 2300 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse args list 1" << std::endl;
#endif

      (yyval.argsList) = (yyvsp[-2].argsList);
      (yyval.argsList)->addArgument((yyvsp[0].expressionNode));
    }
#line 4209 "src/out/parser.cpp"
    break;

    case 147: /* args_list: expression  */
#line 2309 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse args list 2" << std::endl;
#endif

      (yyval.argsList) = new ast::ArgumentsListNode();
      (yyval.argsList)->addArgument((yyvsp[0].expressionNode));
    }
#line 4222 "src/out/parser.cpp"
    break;

    case 148: /* expression: expression GE expr  */
#line 2320 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse expression with greater or equal" << std::endl;
#endif

      if ((yyvsp[-2].expressionNode)->getInferredType() == (yyvsp[0].expressionNode)->getInferredType() && isBasicType((yyvsp[-2].expressionNode)->getInferredType())) {
        (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::GREATER_EQUAL, "boolean");
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for greater or equal - matching types(integer, char, boolean) expected");
        fatalError = true;
        YYERROR;
      }
    }
#line 4241 "src/out/parser.cpp"
    break;

    case 149: /* expression: expression GT expr  */
#line 2335 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse expression with greater" << std::endl;
#endif

      if ((yyvsp[-2].expressionNode)->getInferredType() == (yyvsp[0].expressionNode)->getInferredType() && isBasicType((yyvsp[-2].expressionNode)->getInferredType())) {
        (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::GREATER, "boolean");
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for greater - matching types(integer, char, boolean) expected");
        fatalError = true;
        YYERROR;
      }
    }
#line 4260 "src/out/parser.cpp"
    break;

    case 150: /* expression: expression LE expr  */
#line 2350 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse expression with less or equal" << std::endl;
#endif

      if ((yyvsp[-2].expressionNode)->getInferredType() == (yyvsp[0].expressionNode)->getInferredType() && isBasicType((yyvsp[-2].expressionNode)->getInferredType())) {
        (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::LESS_EQUAL, "boolean");
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for less or equal - matching types(integer, char, boolean) expected");
        fatalError = true;
        YYERROR;
      }
    }
#line 4279 "src/out/parser.cpp"
    break;

    case 151: /* expression: expression LT expr  */
#line 2365 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse expression with less" << std::endl;
#endif

      if ((yyvsp[-2].expressionNode)->getInferredType() == (yyvsp[0].expressionNode)->getInferredType() && isBasicType((yyvsp[-2].expressionNode)->getInferredType())) {
        (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::LESS, "boolean");
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for less - matching types(integer, char, boolean) expected");
        fatalError = true;
        YYERROR;
      }
    }
#line 4298 "src/out/parser.cpp"
    break;

    case 152: /* expression: expression EQUAL expr  */
#line 2380 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse expression with equal" << std::endl;
#endif

      if ((yyvsp[-2].expressionNode)->getInferredType() == (yyvsp[0].expressionNode)->getInferredType() && isBasicType((yyvsp[-2].expressionNode)->getInferredType())) {
        (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::EQUAL, "boolean");
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for equal - matching types(integer, char, boolean) expected");
        fatalError = true;
        YYERROR;
      }
    }
#line 4317 "src/out/parser.cpp"
    break;

    case 153: /* expression: expression UNEQUAL expr  */
#line 2395 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse expression with not equal" << std::endl;
#endif

      if ((yyvsp[-2].expressionNode)->getInferredType() == (yyvsp[0].expressionNode)->getInferredType() && isBasicType((yyvsp[-2].expressionNode)->getInferredType())) {
        (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::NOT_EQUAL, "boolean");
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for not equal - matching types(integer, char, boolean) expected");
        fatalError = true;
        YYERROR;
      }

    }
#line 4337 "src/out/parser.cpp"
    break;

    case 154: /* expression: expr  */
#line 2411 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse simple expression" << std::endl;
#endif
      (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 4348 "src/out/parser.cpp"
    break;

    case 155: /* expr: expr PLUS term  */
#line 2420 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse expression with addition" << std::endl;
#endif

      if ((yyvsp[-2].expressionNode)->getInferredType() == "integer" && (yyvsp[0].expressionNode)->getInferredType() == "integer") {
        (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::ADDITION, (yyvsp[-2].expressionNode)->getInferredType());
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for addition - integer expected");
        fatalError = true;
        YYERROR;
      }
    }
#line 4367 "src/out/parser.cpp"
    break;

    case 156: /* expr: expr MINUS term  */
#line 2435 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse expression with subtraction" << std::endl;
#endif

      if ((yyvsp[-2].expressionNode)->getInferredType() == "integer" && (yyvsp[0].expressionNode)->getInferredType() == "integer") {
        (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::SUBTRACTION, (yyvsp[-2].expressionNode)->getInferredType());
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for subtraction - integer expected");
        fatalError = true;
        YYERROR;
      }
    }
#line 4386 "src/out/parser.cpp"
    break;

    case 157: /* expr: expr OR term  */
#line 2450 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse expression with or" << std::endl;
#endif

      if ((yyvsp[-2].expressionNode)->getInferredType() == "boolean" && (yyvsp[0].expressionNode)->getInferredType() == "boolean") {
        (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::OR, "boolean");
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for or - boolean expected");
        fatalError = true;
        YYERROR;
      }
    }
#line 4405 "src/out/parser.cpp"
    break;

    case 158: /* expr: term  */
#line 2465 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse simple term" << std::endl;
#endif

      (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 4417 "src/out/parser.cpp"
    break;

    case 159: /* term: term MUL factor  */
#line 2475 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse term with multiplication" << std::endl;
#endif

      if ((yyvsp[-2].expressionNode)->getInferredType() == "integer" && (yyvsp[0].expressionNode)->getInferredType() == "integer") {
        (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::MULTIPLICATION, (yyvsp[-2].expressionNode)->getInferredType());
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for mul - integer expected");
        fatalError = true;
        YYERROR;
      }
    }
#line 4436 "src/out/parser.cpp"
    break;

    case 160: /* term: term DIV factor  */
#line 2490 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse term with division" << std::endl;
#endif

      if ((yyvsp[-2].expressionNode)->getInferredType() == "integer" && (yyvsp[0].expressionNode)->getInferredType() == "integer") {
        (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::DIVISION, (yyvsp[-2].expressionNode)->getInferredType());
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for div - integer expected");
        fatalError = true;
        YYERROR;
      }
    }
#line 4455 "src/out/parser.cpp"
    break;

    case 161: /* term: term MOD factor  */
#line 2505 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse term with modulus" << std::endl;
#endif

      if ((yyvsp[-2].expressionNode)->getInferredType() == "integer" && (yyvsp[0].expressionNode)->getInferredType() == "integer") {
        (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::MODULUS, (yyvsp[-2].expressionNode)->getInferredType());
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for mod - integer expected");
        fatalError = true;
        YYERROR;
      }
    }
#line 4474 "src/out/parser.cpp"
    break;

    case 162: /* term: term AND factor  */
#line 2520 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse term with and" << std::endl;
#endif

      if ((yyvsp[-2].expressionNode)->getInferredType() == "boolean" && (yyvsp[0].expressionNode)->getInferredType() == "boolean") {
        (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::AND, "boolean");
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for and - boolean expected");
        fatalError = true;
        YYERROR;
      }
    }
#line 4493 "src/out/parser.cpp"
    break;

    case 163: /* term: factor  */
#line 2535 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse simple factor" << std::endl;
#endif

      (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 4505 "src/out/parser.cpp"
    break;

    case 164: /* factor: identifier LP args_list RP  */
#line 2545 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse factor - function call" << std::endl;
#endif

      if (!ctx->getLookupTable().isRoutineDefined((yyvsp[-3].identifierNode)->getName(), ctx->getCurrentScope())) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", routine " + (yyvsp[-3].identifierNode)->getName() + " is not defined");
        fatalError = true;
        YYERROR;
      }
      else {
        (yyval.expressionNode) =
            new ast::SpecialExpressionNode((yyvsp[-3].identifierNode), (yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::CALL, ctx->getLookupTable().getRoutine((yyvsp[-3].identifierNode)->getName(), ctx->getCurrentScope()).type);
      }
    }
#line 4525 "src/out/parser.cpp"
    break;

    case 165: /* factor: lvalue  */
#line 2562 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse factor - lvalue" << std::endl;
#endif

      (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 4537 "src/out/parser.cpp"
    break;

    case 166: /* factor: const_value  */
#line 2570 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse factor - const value" << std::endl;
#endif

      ast::ConstantNode* constant = dynamic_cast<ast::ConstantNode*>((yyvsp[0].constantNode));

      (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[0].constantNode), ast::SpecialExpressionNode::FunctionName::CONST, constant->flatType());
    }
#line 4551 "src/out/parser.cpp"
    break;

    case 167: /* factor: LP expression RP  */
#line 2580 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse factor - parentheses" << std::endl;
#endif

      (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].expressionNode), ast::SpecialExpressionNode::FunctionName::PARENTHESIS, (yyvsp[-1].expressionNode)->getInferredType());
    }
#line 4563 "src/out/parser.cpp"
    break;

    case 168: /* factor: NOT factor  */
#line 2588 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse factor - not" << std::endl;
#endif

      if ((yyvsp[0].expressionNode)->getInferredType() == "boolean") {
        (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::NEGATION, (yyvsp[0].expressionNode)->getInferredType());
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for not - boolean expected");
        fatalError = true;
        YYERROR;
      }
    }
#line 4582 "src/out/parser.cpp"
    break;

    case 169: /* factor: MINUS factor  */
#line 2603 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse factor - negation" << std::endl;
#endif

      if ((yyvsp[0].expressionNode)->getInferredType() == "integer") {
        (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::NEGATION, (yyvsp[0].expressionNode)->getInferredType());
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for negation - integer expected");
        fatalError = true;
        YYERROR;
      }
    }
#line 4601 "src/out/parser.cpp"
    break;

    case 170: /* factor: ABS LP args_list RP  */
#line 2618 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse factor - abs" << std::endl;
#endif

      if ((yyvsp[-1].argsList)->getArguments().size() != 1) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for abs");
        fatalError = true;
        YYERROR;
      }
      else {
        ast::ExpressionNode* arg = (yyvsp[-1].argsList)->getArguments().front();
        if (arg->getInferredType() == "integer") {
          (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::ABS, "integer");
        }
        else {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for abs - integer expected");
          fatalError = true;
          YYERROR;
        }
      }
    }
#line 4628 "src/out/parser.cpp"
    break;

    case 171: /* factor: CHR LP args_list RP  */
#line 2641 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse factor - chr" << std::endl;
#endif

      if ((yyvsp[-1].argsList)->getArguments().size() != 1) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for chr");
        fatalError = true;
        YYERROR;
      }
      else {
        ast::ExpressionNode* arg = (yyvsp[-1].argsList)->getArguments().front();
        if (arg->getInferredType() == "integer") {
          (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::CHR, "char");
        }
        else {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for chr - integer expected");
          fatalError = true;
          YYERROR;
        }
      }
    }
#line 4655 "src/out/parser.cpp"
    break;

    case 172: /* factor: ODD LP args_list RP  */
#line 2664 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse factor - odd" << std::endl;
#endif

      if ((yyvsp[-1].argsList)->getArguments().size() != 1) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for odd");
        fatalError = true;
        YYERROR;
      }
      else {
        ast::ExpressionNode* arg = (yyvsp[-1].argsList)->getArguments().front();
        if (arg->getInferredType() == "integer") {
          (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::ODD, "boolean");
        }
        else {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for odd - integer expected");
          fatalError = true;
          YYERROR;
        }
      }
    }
#line 4682 "src/out/parser.cpp"
    break;

    case 173: /* factor: ORD LP args_list RP  */
#line 2687 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse factor - ord" << std::endl;
#endif

      if ((yyvsp[-1].argsList)->getArguments().size() != 1) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for ord");
        fatalError = true;
        YYERROR;
      }
      else {
        ast::ExpressionNode* arg = (yyvsp[-1].argsList)->getArguments().front();
        if (arg->getInferredType() == "char") {
          (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::ORD, "integer");
        }
        else {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for ord - char expected");
          fatalError = true;
          YYERROR;
        }
      }
    }
#line 4709 "src/out/parser.cpp"
    break;

    case 174: /* factor: PRED LP args_list RP  */
#line 2710 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse factor - pred" << std::endl;
#endif

      if ((yyvsp[-1].argsList)->getArguments().size() != 1) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for pred");
        fatalError = true;
        YYERROR;
      }
      else {
        ast::ExpressionNode* arg = (yyvsp[-1].argsList)->getArguments().front();
        if (arg->getInferredType() == "integer" || arg->getInferredType() == "char") {
          (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::PRED, arg->getInferredType());
        }
        else {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for pred - integer or char expected");
          fatalError = true;
          YYERROR;
        }
      }
    }
#line 4736 "src/out/parser.cpp"
    break;

    case 175: /* factor: SUCC LP args_list RP  */
#line 2733 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse factor - succ" << std::endl;
#endif

      if ((yyvsp[-1].argsList)->getArguments().size() != 1) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for succ");
        fatalError = true;
        YYERROR;
      }
      else {
        ast::ExpressionNode* arg = (yyvsp[-1].argsList)->getArguments().front();
        if (arg->getInferredType() == "integer" || arg->getInferredType() == "char") {
          (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::SUCC, arg->getInferredType());
        }
        else {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for succ - integer or char expected");
          fatalError = true;
          YYERROR;
        }
      }
    }
#line 4763 "src/out/parser.cpp"
    break;

    case 176: /* factor: TOINT LP args_list RP  */
#line 2756 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse factor - toint" << std::endl;
#endif

      if ((yyvsp[-1].argsList)->getArguments().size() != 1) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for toint");
        fatalError = true;
        YYERROR;
      }
      else {
        ast::ExpressionNode* arg = (yyvsp[-1].argsList)->getArguments().front();
        if (isBasicType(arg->getInferredType())) {
          (yyval.expressionNode) = new ast::SpecialExpressionNode(arg, ast::SpecialExpressionNode::FunctionName::TOINT, "integer");
        }
        else {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for toint - basic type expected");
          fatalError = true;
          YYERROR;
        }
      }
    }
#line 4790 "src/out/parser.cpp"
    break;

    case 177: /* factor: TOCHAR LP args_list RP  */
#line 2779 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse factor - tochar" << std::endl;
#endif

      if ((yyvsp[-1].argsList)->getArguments().size() != 1) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for tochar");
        fatalError = true;
        YYERROR;
      }
      else {
        ast::ExpressionNode* arg = (yyvsp[-1].argsList)->getArguments().front();
        if (isBasicType(arg->getInferredType())) {
          (yyval.expressionNode) = new ast::SpecialExpressionNode(arg, ast::SpecialExpressionNode::FunctionName::TOCHAR, "char");
        }
        else {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for tochar - basic type expected");
          fatalError = true;
          YYERROR;
        }
      }
    }
#line 4817 "src/out/parser.cpp"
    break;

    case 178: /* factor: TOBOOL LP args_list RP  */
#line 2802 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse factor - tobool" << std::endl;
#endif

      if ((yyvsp[-1].argsList)->getArguments().size() != 1) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for tobool");
        fatalError = true;
        YYERROR;
      }
      else {
        ast::ExpressionNode* arg = (yyvsp[-1].argsList)->getArguments().front();
        if (isBasicType(arg->getInferredType())) {
          (yyval.expressionNode) = new ast::SpecialExpressionNode(arg, ast::SpecialExpressionNode::FunctionName::TOBOOL, "boolean");
        }
        else {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for tobool - basic type expected");
          fatalError = true;
          YYERROR;
        }
      }
    }
#line 4844 "src/out/parser.cpp"
    break;

    case 179: /* lvalue: identifier  */
#line 2827 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse lvalue - variable" << std::endl;
#endif

      if (ctx->getLookupTable().isVariableDefined((yyvsp[0].identifierNode)->getName(), ctx->getCurrentScope())) {
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[0].identifierNode), ast::SpecialExpressionNode::FunctionName::VARIABLE, ctx->getLookupTable().getVariable((yyvsp[0].identifierNode)->getName(), ctx->getCurrentScope()).type);
      }
      else if (isInAnyEnum((yyvsp[0].identifierNode)->getName())) {
        auto properEnums = ctx->getLookupTable().getTypes(
            [&](const std::string&, const LookupTable::TypeInfo& tf) { return tf.alive && tf.type.find("enum%") == 0 && tf.type.find("%" + (yyvsp[0].identifierNode)->getName() + "%") != std::string::npos; }, ctx->getCurrentScope());

        if (properEnums.size() != 1) {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", variable " + (yyvsp[0].identifierNode)->getName() + " is in more than one enum");
          fatalError = true;
          YYERROR;
        }

        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[0].identifierNode), ast::SpecialExpressionNode::FunctionName::ENUM_ELEMENT, properEnums.front().type);
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", variable " + (yyvsp[0].identifierNode)->getName() + " is not defined");
        fatalError = true;
        YYERROR;
      }
    }
#line 4878 "src/out/parser.cpp"
    break;

    case 180: /* lvalue: identifier LB expression RB  */
#line 2857 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse lvalue - simple array access" << std::endl;
#endif

      if (!ctx->getLookupTable().isVariableDefined((yyvsp[-3].identifierNode)->getName(), ctx->getCurrentScope())) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", variable " + (yyvsp[-3].identifierNode)->getName() + " is not defined");
        fatalError = true;
        YYERROR;
      }
      else if (!isArrayIndexCompatible(ctx->getLookupTable().getVariable((yyvsp[-3].identifierNode)->getName(), ctx->getCurrentScope()).type, (yyvsp[-1].expressionNode))) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", incorrect index type");
        fatalError = true;
        YYERROR;
      }
      else {
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-3].identifierNode), ast::SpecialExpressionNode::FunctionName::ARRAY_ACCESS,
                                                                getArrayElementType(ctx->getLookupTable().getVariable((yyvsp[-3].identifierNode)->getName(), ctx->getCurrentScope()).type));
      }
    }
#line 4903 "src/out/parser.cpp"
    break;

    case 181: /* lvalue: lvalue LB expression RB  */
#line 2878 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse lvalue - complex array access" << std::endl;
#endif

      if ((yyvsp[-3].expressionNode)->getInferredType().substr(0, 5) != "array") {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", array type expected");
        fatalError = true;
        YYERROR;
      }
      else if (!isArrayIndexCompatible((yyvsp[-3].expressionNode)->getInferredType(), (yyvsp[-1].expressionNode))) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", incorrect index type");
        fatalError = true;
        YYERROR;
      }
      else {
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-3].expressionNode), (yyvsp[-1].expressionNode), ast::SpecialExpressionNode::FunctionName::ARRAY_ACCESS, getArrayElementType((yyvsp[-3].expressionNode)->getInferredType()));
      }
    }
#line 4928 "src/out/parser.cpp"
    break;

    case 182: /* lvalue: identifier DOT identifier  */
#line 2899 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse lvalue - simple record field" << std::endl;
#endif

      if (ctx->getLookupTable().isVariableDefined((yyvsp[-2].identifierNode)->getName(), ctx->getCurrentScope()) &&
          isRecordFieldCompatible(ctx->getLookupTable().getVariable((yyvsp[-2].identifierNode)->getName(), ctx->getCurrentScope()).type, (yyvsp[0].identifierNode))) {
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-2].identifierNode), ast::SpecialExpressionNode::FunctionName::RECORD_ACCESS,
                                                                getRecordFieldType(ctx->getLookupTable().getVariable((yyvsp[-2].identifierNode)->getName(), ctx->getCurrentScope()).type, (yyvsp[0].identifierNode)->getName()));
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", variable " + (yyvsp[-2].identifierNode)->getName() + " is not defined");
        fatalError = true;
        YYERROR;
      }
    }
#line 4948 "src/out/parser.cpp"
    break;

    case 183: /* lvalue: lvalue DOT identifier  */
#line 2915 "src/yacc.y"
    {
#ifdef YACC_DEBUG
      std::cout << "Yacc debug: Parse lvalue - complex record field" << std::endl;
#endif

      if ((yyvsp[-2].expressionNode)->getInferredType().substr(0, 6) == "record" && isRecordFieldCompatible((yyvsp[-2].expressionNode)->getInferredType(), (yyvsp[0].identifierNode))) {
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].identifierNode), ast::SpecialExpressionNode::FunctionName::RECORD_ACCESS,
                                                                getRecordFieldType((yyvsp[-2].expressionNode)->getInferredType(), (yyvsp[0].identifierNode)->getName()));
      }
      else {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", record type expected");
        fatalError = true;
        YYERROR;
      }
    }
#line 4968 "src/out/parser.cpp"
    break;

#line 4972 "src/out/parser.cpp"

    default:
      break;
  }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT("-> $$ =", YY_CAST(yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK(yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp ? yytable[yyi] : yydefgoto[yylhs]);
  }

  goto yynewstate;

/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE(yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus) {
    ++yynerrs;
    yyerror(YY_("syntax error"));
  }

  if (yyerrstatus == 3) {
    /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

    if (yychar <= YYEOF) {
      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        YYABORT;
    }
    else {
      yydestruct("Error: discarding", yytoken, &yylval);
      yychar = YYEMPTY;
    }
  }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;

/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK(yylen);
  yylen = 0;
  YY_STACK_PRINT(yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;

/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3; /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;) {
    yyn = yypact[yystate];
    if (!yypact_value_is_default(yyn)) {
      yyn += YYSYMBOL_YYerror;
      if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror) {
        yyn = yytable[yyn];
        if (0 < yyn)
          break;
      }
    }

    /* Pop the current state because it cannot handle the error token.  */
    if (yyssp == yyss)
      YYABORT;

    yydestruct("Error: popping", YY_ACCESSING_SYMBOL(yystate), yyvsp);
    YYPOPSTACK(1);
    yystate = *yyssp;
    YY_STACK_PRINT(yyss, yyssp);
  }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Shift the error token.  */
  YY_SYMBOL_PRINT("Shifting", YY_ACCESSING_SYMBOL(yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;

/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;

/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror(YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;

/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY) {
    /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
    yytoken = YYTRANSLATE(yychar);
    yydestruct("Cleanup: discarding lookahead", yytoken, &yylval);
  }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK(yylen);
  YY_STACK_PRINT(yyss, yyssp);
  while (yyssp != yyss) {
    yydestruct("Cleanup: popping", YY_ACCESSING_SYMBOL(+*yyssp), yyvsp);
    YYPOPSTACK(1);
  }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE(yyss);
#endif

  return yyresult;
}

#line 2931 "src/yacc.y"

void yyerror(const char* s) {
  parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + s);
  fatalError = true;
  resultAst = nullptr;
}

bool parse(const std::string& inputFileName, std::vector<std::string>& errors, std::unique_ptr<ast::ProgramNode>& program) {
  yyin = fopen(inputFileName.c_str(), "r");

  if (yyin == nullptr) {
    errors.push_back("Cannot open file `" + inputFileName + "`");
    return false;
  }

  ctx->pushScope("program");

  yyparse();
  fclose(yyin);

  ctx->popScope();

  errors = std::move(parsingErrors);
  program = std::unique_ptr<ast::ProgramNode>(resultAst);
  return !fatalError;
}

bool isChar(const std::string& expr) {
  return expr.size() == 1;
}

bool isInteger(const std::string& expr) {
  return std::all_of(expr.begin(), expr.end(), ::isdigit) || (expr.size() > 1 && expr[0] == '-' && std::all_of(expr.begin() + 1, expr.end(), ::isdigit));
}

bool isBoolean(const std::string& expr) {
  return expr == "true" || expr == "false";
}

bool nameAlreadyUsed(std::string name) {
  if (ctx->getLookupTable().isVariableDefined(name, ctx->getCurrentScope()) || ctx->getLookupTable().isRoutineDefined(name, ctx->getCurrentScope()) || ctx->getLookupTable().isTypeDefined(name, ctx->getCurrentScope())) {
    return true;
  }

  if (isInAnyEnum(name)) {
    return true;
  }

  return false;
}

bool saveType(ast::IdentifierNode* typeName, const std::string& typeDef) {
  if (nameAlreadyUsed(typeName->getName())) {
    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", name `" + typeName->getName() + "` already used");
    fatalError = true;
    return false;
  }
  else {
    ctx->getLookupTable().defineType(LookupTable::TypeCategory::SIMPLE, typeName->getName(), typeDef, ctx->getCurrentScope());
    return true;
  }
}

bool saveConstant(ast::IdentifierNode* constName, const std::string& constValue, const std::string& typeDef) {
  if (nameAlreadyUsed(constName->getName())) {
    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", name `" + constName->getName() + "` already used");
    fatalError = true;
    return false;
  }
  else {
    ctx->getLookupTable().defineVariable(LookupTable::VariableCategory::CONSTANT, constName->getName(), typeDef, ctx->getCurrentScope());
    ctx->getLookupTable().setVariableValue(constName->getName(), constValue, ctx->getCurrentScope());
    return true;
  }
}

bool saveVariables(std::vector<ast::IdentifierNode*>* varNames, const std::string& typeDef) {
  for (auto& varName : *varNames) {
    if (nameAlreadyUsed(varName->getName())) {
      parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", name `" + varName->getName() + "` already used");
      fatalError = true;
      return false;
    }
    else {
      ctx->getLookupTable().defineVariable(LookupTable::VariableCategory::VARIABLE, varName->getName(), typeDef, ctx->getCurrentScope());
    }
  }

  return true;
}

bool saveRoutine(ast::RoutineDeclarationNode* routineDef, bool isForward) {
  if (isForward) {
    if (nameAlreadyUsed(routineDef->getName())) {
      parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", name `" + routineDef->getName() + "` already used");
      fatalError = true;
      return false;
    }

    for (const auto& paramGroup : *routineDef->getParams()->getParams()) {
      for (const auto& param : *paramGroup->getParams()) {
        if (nameAlreadyUsed(param->getName())) {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", name `" + param->getName() + "` already used");
          fatalError = true;
          return false;
        }
      }
    }
  }

  std::vector<LookupTable::ArgumentInfo> arguments;
  for (const auto& paramGroup : *routineDef->getParams()->getParams()) {
    std::string typeString;
    try {
      typeString = paramGroup->getParamsType()->flat();
    } catch (std::runtime_error& err) {
      parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
      fatalError = true;
      return false;
    }

    for (const auto& param : *paramGroup->getParams()) {
      arguments.emplace_back(param->getName(), typeString, paramGroup->getPassType() == ast::ParamsGroupNode::PassType::PASS_BY_REFERENCE ? true : false);
    }
  }

  if (routineDef->getRoutineType() == ast::RoutineDeclarationNode::RoutineType::PROCEDURE) {
    ctx->getLookupTable().defineRoutine(LookupTable::RoutineCategory::PROCEDURE, routineDef->getName(), arguments, "void", ctx->getCurrentScope());
  }
  else {
    std::string returnType;
    try {
      returnType = routineDef->getReturnType()->flat();
    } catch (std::runtime_error& err) {
      parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
      fatalError = true;
      return false;
    }

    ctx->getLookupTable().defineRoutine(LookupTable::RoutineCategory::FUNCTION, routineDef->getName(), arguments, returnType, ctx->getCurrentScope());
  }

  return true;
}

bool isBasicType(const std::string& type) {
  return type == "integer" || type == "boolean" || type == "char";
}

bool isBasicOrEnumType(const std::string& type) {
  return isBasicType(type) || type.find("enum%") == 0;
}

bool isBasicOrEnumOrArrayOrRecordType(const std::string& type) {
  return isBasicOrEnumType(type) || type.find("array@@") == 0 || type.find("record$$") == 0;
}

bool isRangeType(const std::string& type) {
  return type.find("constrange%") == 0 || type.find("enumrange%") == 0;
}

bool isInEnum(const std::string& enumElement, const std::string& enumType) {
  return enumType.find(enumElement) != std::string::npos;
}

bool isInAnyEnum(const std::string& enumElement) {
  const std::vector<LookupTable::TypeInfo>& types =
      ctx->getLookupTable().getTypes([&](const std::string&, const LookupTable::TypeInfo& tf) { return tf.alive && tf.type.find("enum%") == 0 && tf.type.find("%" + enumElement + "%") != std::string::npos; }, ctx->getCurrentScope());

  return !types.empty();
}

bool isEnumSubRangeType(const std::string& enumElement, const std::string& enumType, const std::string& begin, const std::string& end) {
  std::size_t beginPos = enumType.find("%" + begin + "%");
  std::size_t endPos = enumType.find("%" + end + "%");
  std::size_t enumElementPos = enumType.find("%" + enumElement + "%");

  return beginPos != std::string::npos && endPos != std::string::npos && enumElementPos != std::string::npos && beginPos <= enumElementPos && enumElementPos <= endPos;
}

bool isLeftValueCompatible(ast::ExpressionNode* expr) {
  if (expr->getOperation() != ast::ExpressionNode::Operation::SPECIAL) {
    return false;
  }

  ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(expr);
  if (special->getFunctionName() == ast::SpecialExpressionNode::ARRAY_ACCESS || special->getFunctionName() == ast::SpecialExpressionNode::RECORD_ACCESS) {
    return true;
  }

  if (special->getFunctionName() == ast::SpecialExpressionNode::VARIABLE) {
    ast::IdentifierNode* var = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
    return !ctx->getLookupTable().isVariableConst(var->getName(), ctx->getCurrentScope());
  }

  return false;
}

bool isArrayIndexCompatible(const std::string& arrayType, ast::ExpressionNode* index) {
  std::string arrayElementType{};
  std::size_t it{7};
  while (arrayType[it] != '@' && it < arrayType.size()) {
    arrayElementType += arrayType[it];
    it++;
  }

  if (arrayElementType == "integer") {
    if (index->getInferredType() == "integer") {
      return true;
    }
    return false;
  }
  else if (arrayElementType == "char") {
    if (index->getInferredType() == "char") {
      return true;
    }
    return false;
  }
  else if (arrayElementType == "boolean") {
    if (index->getInferredType() == "boolean") {
      return true;
    }
    return false;
  }
  else if (arrayElementType.substr(0, 10) == "constrange") {
    std::string begin{};
    std::string end{};
    std::size_t pos;
    for (pos = 11; pos < arrayElementType.size(); pos++) {
      if (arrayElementType[pos] == '.') {
        break;
      }
      begin += arrayElementType[pos];
    }

    for (pos += 2; pos < arrayElementType.size(); pos++) {
      end += arrayElementType[pos];
    }

    if (isInteger(begin) && isInteger(end)) {
      if (index->getInferredType() == "integer") {
        return true;
      }
    }
    else if (isChar(begin) && isChar(end)) {
      if (index->getInferredType() == "char") {
        return true;
      }
    }
    else if (isBoolean(begin) && isBoolean(end)) {
      if (index->getInferredType() == "boolean") {
        return true;
      }
    }

    return false;
  }
  else if (arrayElementType.substr(0, 9) == "enumrange") {
    std::string enumName, beginEnum, endEnum;
    std::size_t pos{10};
    for (; pos < arrayElementType.size(); pos++) {
      if (arrayElementType[pos] == '%') {
        break;
      }
      enumName += arrayElementType[pos];
    }

    pos++;
    while (arrayElementType[pos] != '.') {
      beginEnum += arrayElementType[pos];
      pos++;
    }

    pos += 2;
    for (; pos < arrayElementType.size(); pos++) {
      endEnum += arrayElementType[pos];
    }

    if (index->getOperation() == ast::ExpressionNode::Operation::SPECIAL) {
      ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(index);
      if (special->getFunctionName() == ast::SpecialExpressionNode::ENUM_ELEMENT) {
        ast::IdentifierNode* enumElement = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
        return isEnumSubRangeType(enumElement->getName(), ctx->getLookupTable().getType(enumName, ctx->getCurrentScope()).type, beginEnum, endEnum);
      }
    }

    return false;
  }
  else if (arrayElementType.substr(0, 4) == "enum") {
    if (index->getOperation() == ast::ExpressionNode::Operation::SPECIAL) {
      ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(index);
      if (special->getFunctionName() == ast::SpecialExpressionNode::ENUM_ELEMENT) {
        ast::IdentifierNode* enumElement = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
        return isInEnum(enumElement->getName(), arrayElementType);
      }
    }
    return false;
  }
  else {
    return false;
  }
}

bool isRecordFieldCompatible(const std::string& recordType, ast::IdentifierNode* field) {
  const std::string& fieldName = "$" + field->getName() + "#";
  std::size_t parenthesisCounter{};
  for (std::size_t i = 0; i < recordType.size(); i++) {
    if (recordType[i] == '(') {
      parenthesisCounter++;
    }
    else if (recordType[i] == ')') {
      parenthesisCounter--;
    }
    if (parenthesisCounter == 0) {
      if (recordType.substr(i, fieldName.size()) == fieldName) {
        return true;
      }
    }
  }
  return false;
}

bool isFunctionArgumentsCompatible(const std::vector<LookupTable::ArgumentInfo>& expectedArgs, const std::vector<ast::ExpressionNode*>& givenArgs) {
  if (expectedArgs.size() != givenArgs.size()) {
    return false;
  }

  for (std::size_t i = 0; i < expectedArgs.size(); i++) {
    if (expectedArgs[i].type != givenArgs[i]->getInferredType()) {
      return false;
    }
    if (expectedArgs[i].isReference && !isLeftValueCompatible(givenArgs[i])) {
      return false;
    }
  }

  return true;
}

bool hasReturnValue(ast::RoutineNode* function, const std::string& functionName) {
  std::vector<ast::StatementNode*>* statements = function->getBody()->getStatements()->getStatements().get();
  if (statements->empty()) {
    std::cout << "Empty function body\n";
    return false;
  }

  std::size_t returnCounter{0};
  std::size_t lastStatementIndex{0};
  for (std::size_t i = 0; i < statements->size(); i++) {
    if (statements->at(i)->getCategory() != ast::StatementNode::Category::ASSIGN) {
      continue;
    }

    ast::ExpressionNode* lhs = dynamic_cast<ast::AssignNode*>(statements->at(i))->getLhs().get();
    if (lhs->getOperation() != ast::ExpressionNode::Operation::SPECIAL) {
      continue;
    }

    ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(lhs);
    if (special->getFunctionName() != ast::SpecialExpressionNode::VARIABLE) {
      continue;
    }

    ast::IdentifierNode* variable = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
    if (variable->getName() == functionName) {
      returnCounter++;
      lastStatementIndex = i;
    }
  }

  if (returnCounter != 1) {
    return false;
  }

  return lastStatementIndex == statements->size() - 1;
}

bool variableIsReassignedS(const std::string& varName, ast::StatementNode* stmt) {
  switch (stmt->getCategory()) {
    case ast::StatementNode::Category::BREAK:
    case ast::StatementNode::Category::CONTINUE:
    case ast::StatementNode::Category::GOTO:
      return false;
    case ast::StatementNode::Category::ASSIGN: {
      ast::ExpressionNode* rhs = dynamic_cast<ast::AssignNode*>(stmt)->getRhs().get();
      if (variableIsReassignedE(varName, rhs)) {
        return true;
      }

      ast::ExpressionNode* lhs = dynamic_cast<ast::AssignNode*>(stmt)->getLhs().get();
      if (lhs->getOperation() != ast::ExpressionNode::Operation::SPECIAL) {
        return false;
      }

      ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(lhs);
      if (special->getFunctionName() != ast::SpecialExpressionNode::VARIABLE) {
        return false;
      }

      ast::IdentifierNode* variable = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
      return variable->getName() == varName;
    }
    case ast::StatementNode::Category::CALL: {
      ast::CallNode* call = dynamic_cast<ast::CallNode*>(stmt);

      if (call->getCallObjectType() == ast::CallNode::CallObjectType::USER_DEFINED) {
        ast::UserDefineCallNode* userCall = dynamic_cast<ast::UserDefineCallNode*>(call);
        const std::vector<LookupTable::ArgumentInfo>& callArgs = ctx->getLookupTable().getRoutine(userCall->getName()->getName(), ctx->getCurrentScope()).args;
        std::vector<bool> passByReference;
        for (std::size_t i = 0; i < callArgs.size(); i++) {
          passByReference.push_back(callArgs[i].isReference);
        }

        std::size_t index{0};
        for (auto arg : userCall->getArguments()->getArguments()) {
          if (arg->getOperation() == ast::ExpressionNode::Operation::SPECIAL) {
            ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(arg);
            if (special->getFunctionName() == ast::SpecialExpressionNode::VARIABLE) {
              ast::IdentifierNode* variable = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
              if (variable->getName() == varName && passByReference[index]) {
                return true;
              }
            }
            else if (variableIsReassignedE(varName, arg)) {
              return true;
            }
          }
          else if (variableIsReassignedE(varName, arg)) {
            return true;
          }
          index++;
        }
        return false;
      }
      else {
        ast::BuiltinCallNode* builtinCall = dynamic_cast<ast::BuiltinCallNode*>(call);
        if (builtinCall->getArguments() == nullptr) {
          return false;
        }
        auto args = builtinCall->getArguments()->getArguments();

        if (builtinCall->getFunctionName() == ast::BuiltinCallNode::FunctionName::READ) {
          if (args.front()->getOperation() == ast::ExpressionNode::Operation::SPECIAL) {
            ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(args.front());
            if (special->getFunctionName() == ast::SpecialExpressionNode::VARIABLE) {
              ast::IdentifierNode* variable = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
              return variable->getName() == varName;
            }
          }
        }
        if (builtinCall->getFunctionName() == ast::BuiltinCallNode::FunctionName::MEMORY_READ) {
          if (args.back()->getOperation() == ast::ExpressionNode::Operation::SPECIAL) {
            ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(args.back());
            if (special->getFunctionName() == ast::SpecialExpressionNode::VARIABLE) {
              ast::IdentifierNode* variable = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
              return variable->getName() == varName;
            }
          }
        }
        if (builtinCall->getFunctionName() == ast::BuiltinCallNode::FunctionName::STACK_READ) {
          if (args.back()->getOperation() == ast::ExpressionNode::Operation::SPECIAL) {
            ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(args.back());
            if (special->getFunctionName() == ast::SpecialExpressionNode::VARIABLE) {
              ast::IdentifierNode* variable = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
              return variable->getName() == varName;
            }
          }
        }

        return false;
      }
    }
    case ast::StatementNode::Category::CASE: {
      for (auto caseStatement : *dynamic_cast<ast::CaseNode*>(stmt)->getStatements()) {
        if (caseStatement->first != nullptr && caseStatement->first->getType() == ast::AstNode::Type::EXPRESSION) {
          if (variableIsReassignedE(varName, dynamic_cast<ast::ExpressionNode*>(caseStatement->first))) {
            return true;
          }
        }

        if (variableIsReassignedS(varName, caseStatement->second)) {
          return true;
        }
      }
      return false;
    }
    case ast::StatementNode::Category::COMPOUND: {
      for (auto statement : *dynamic_cast<ast::CompoundStatementNode*>(stmt)->getStatements()) {
        if (variableIsReassignedS(varName, statement)) {
          return true;
        }
      }
      return false;
    }
    case ast::StatementNode::Category::FOR: {
      if (variableIsReassignedE(varName, dynamic_cast<ast::ForNode*>(stmt)->getStart().get())) {
        return true;
      }
      if (variableIsReassignedE(varName, dynamic_cast<ast::ForNode*>(stmt)->getEnd().get())) {
        return true;
      }
      if (variableIsReassignedS(varName, dynamic_cast<ast::ForNode*>(stmt)->getStatements().get())) {
        return true;
      }

      return false;
    }
    case ast::StatementNode::Category::IF: {
      if (variableIsReassignedE(varName, dynamic_cast<ast::IfNode*>(stmt)->getCondition().get())) {
        return true;
      }
      if (variableIsReassignedS(varName, dynamic_cast<ast::IfNode*>(stmt)->getThenStatement().get())) {
        return true;
      }
      if (dynamic_cast<ast::IfNode*>(stmt)->getElseStatement().get() != nullptr && variableIsReassignedS(varName, dynamic_cast<ast::IfNode*>(stmt)->getElseStatement().get())) {
        return true;
      }

      return false;
    }
    case ast::StatementNode::Category::REPEAT: {
      if (variableIsReassignedE(varName, dynamic_cast<ast::RepeatNode*>(stmt)->getCondition().get())) {
        return true;
      }

      if (variableIsReassignedS(varName, dynamic_cast<ast::RepeatNode*>(stmt)->getStatements().get())) {
        return true;
      }

      return false;
    }
    case ast::StatementNode::Category::WHILE: {
      if (variableIsReassignedE(varName, dynamic_cast<ast::WhileNode*>(stmt)->getCondition().get())) {
        return true;
      }

      if (variableIsReassignedS(varName, dynamic_cast<ast::WhileNode*>(stmt)->getStatements().get())) {
        return true;
      }

      return false;
    }
    default:
      return false;
  }
}

bool variableIsReassignedE(const std::string& varName, ast::ExpressionNode* expr) {
  if (expr->getOperation() != ast::ExpressionNode::Operation::SPECIAL) {
    return false;
  }

  ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(expr);
  if (special->getFunctionName() == ast::SpecialExpressionNode::CALL) {
    auto routineName = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get())->getName();
    auto args = dynamic_cast<ast::ArgumentsListNode*>(special->getArgument2().get())->getArguments();

    const std::vector<LookupTable::ArgumentInfo>& callArgs = ctx->getLookupTable().getRoutine(routineName, ctx->getCurrentScope()).args;
    std::vector<bool> passByReference;
    for (std::size_t i = 0; i < callArgs.size(); i++) {
      passByReference.push_back(callArgs[i].isReference);
    }

    std::size_t index{0};
    for (auto arg : args) {
      if (arg->getOperation() == ast::ExpressionNode::Operation::SPECIAL) {
        ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(arg);
        if (special->getFunctionName() == ast::SpecialExpressionNode::VARIABLE) {
          ast::IdentifierNode* variable = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
          if (variable->getName() == varName && passByReference[index]) {
            return true;
          }
        }
        else if (variableIsReassignedE(varName, arg)) {
          return true;
        }
      }
      else if (variableIsReassignedE(varName, arg)) {
        return true;
      }
      index++;
    }
  }

  return false;
}

std::string getArrayElementType(const std::string& arrayType) {
  std::string elementType{};
  std::size_t counter{0};
  for (auto it = arrayType.begin(); it != (arrayType.end() - 2); ++it) {
    if (counter >= 3) {
      elementType += (*it);
    }
    else if (*it == '@') {
      counter++;
    }
  }
  return elementType;
}

std::string getRecordFieldType(const std::string& recordType, const std::string& field) {
  std::size_t it = recordType.find("$" + field + "#") + field.size() + 3;
  std::string fieldType{};
  std::size_t parenthesisCounter{1};
  while (parenthesisCounter != 0) {
    if (recordType[it] == '(') {
      parenthesisCounter++;
    }
    else if (recordType[it] == ')') {
      parenthesisCounter--;
    }
    fieldType += recordType[it];
    it++;
  }

  return fieldType.substr(0, fieldType.size() - 1);
}
