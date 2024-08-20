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

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

#include "../src/ast/arguments_list_node.hpp"
#include "../src/ast/array_type_node.hpp"
#include "../src/ast/assign_node.hpp"
#include "../src/ast/ast_node.hpp"
#include "../src/ast/break_node.hpp"
#include "../src/ast/call_node.hpp"
#include "../src/ast/case_node.hpp"
#include "../src/ast/compound_statement_node.hpp"
#include "../src/ast/constant_node.hpp"
#include "../src/ast/continue_node.hpp"
#include "../src/ast/expression_node.hpp"
#include "../src/ast/for_node.hpp"
#include "../src/ast/goto_node.hpp"
#include "../src/ast/identifier_node.hpp"
#include "../src/ast/if_node.hpp"
#include "../src/ast/params_group_node.hpp"
#include "../src/ast/params_node.hpp"
#include "../src/ast/program_node.hpp"
#include "../src/ast/record_type_node.hpp"
#include "../src/ast/repeat_node.hpp"
#include "../src/ast/routine_body_node.hpp"
#include "../src/ast/routine_decl_head_node.hpp"
#include "../src/ast/simple_type_node.hpp"
#include "../src/ast/statement_node.hpp"
#include "../src/ast/type_node.hpp"
#include "../src/ast/while_node.hpp"

#include "../src/context.hpp"

#undef YACC_DEBUG

Context* ctx = Context::getInstance();

ast::ProgramNode* resultAst;
std::vector<std::string> parsingErrors;
bool fatalError{false};

static void yyerror(const char *msg);
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

std::string getTypeString(ast::TypeNode* type);
std::string getTypeString(ast::ConstantNode::ConstantType type);

std::string getConstantString(ast::ConstantNode* constant);

bool isBasicType(const std::string& type);
bool isInEnum(const std::string& enumElement, const std::string& enumType);
bool isInAnyEnum(const std::string& enumElement);
bool isEnumSubRangeType(const std::string& enumElementPos, const std::string& enumType,
         const std::string& begin, const std::string& end);
bool isLeftValueCompatible(ast::ExpressionNode* expr);

bool isArrayIndexCompatible(const std::string& arrayType, ast::ExpressionNode* index);
bool isRecordFieldCompatible(const std::string& recordType, ast::IdentifierNode* field);
bool isFunctionArgumentsCompatible(const std::vector<LookupTable::ArgumentInfo>& expectedArgs, const std::vector<ast::ExpressionNode*>& givenArgs);
bool hasReturnValue(ast::RoutineNode* function, const std::string& functionName);
bool variableIsReassignedS(const std::string& varName, ast::StatementNode* stmt);
bool variableIsReassignedE(const std::string& varName, ast::ExpressionNode* expr);

std::string getArrayElementType(const std::string& arrayType);
std::string getRecordFieldType(const std::string& recordType, const std::string& field);

#line 157 "out/parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROGRAM = 3,                    /* PROGRAM  */
  YYSYMBOL_FUNCTION = 4,                   /* FUNCTION  */
  YYSYMBOL_PROCEDURE = 5,                  /* PROCEDURE  */
  YYSYMBOL_CONST = 6,                      /* CONST  */
  YYSYMBOL_TYPE = 7,                       /* TYPE  */
  YYSYMBOL_VAR = 8,                        /* VAR  */
  YYSYMBOL_BBEGIN = 9,                     /* BBEGIN  */
  YYSYMBOL_END = 10,                       /* END  */
  YYSYMBOL_IDENT_NAME = 11,                /* IDENT_NAME  */
  YYSYMBOL_INTEGER = 12,                   /* INTEGER  */
  YYSYMBOL_BOOLEAN = 13,                   /* BOOLEAN  */
  YYSYMBOL_CHAR = 14,                      /* CHAR  */
  YYSYMBOL_STRING = 15,                    /* STRING  */
  YYSYMBOL_TRUE = 16,                      /* TRUE  */
  YYSYMBOL_FALSE = 17,                     /* FALSE  */
  YYSYMBOL_MAXINT = 18,                    /* MAXINT  */
  YYSYMBOL_READ = 19,                      /* READ  */
  YYSYMBOL_READLN = 20,                    /* READLN  */
  YYSYMBOL_WRITE = 21,                     /* WRITE  */
  YYSYMBOL_WRITELN = 22,                   /* WRITELN  */
  YYSYMBOL_MEMORYREAD = 23,                /* MEMORYREAD  */
  YYSYMBOL_MEMORYWRITE = 24,               /* MEMORYWRITE  */
  YYSYMBOL_STACKREAD = 25,                 /* STACKREAD  */
  YYSYMBOL_STACKWRITE = 26,                /* STACKWRITE  */
  YYSYMBOL_ABS = 27,                       /* ABS  */
  YYSYMBOL_CHR = 28,                       /* CHR  */
  YYSYMBOL_ODD = 29,                       /* ODD  */
  YYSYMBOL_ORD = 30,                       /* ORD  */
  YYSYMBOL_PRED = 31,                      /* PRED  */
  YYSYMBOL_SUCC = 32,                      /* SUCC  */
  YYSYMBOL_TOINT = 33,                     /* TOINT  */
  YYSYMBOL_TOCHAR = 34,                    /* TOCHAR  */
  YYSYMBOL_TOBOOL = 35,                    /* TOBOOL  */
  YYSYMBOL_IF = 36,                        /* IF  */
  YYSYMBOL_THEN = 37,                      /* THEN  */
  YYSYMBOL_ELSE = 38,                      /* ELSE  */
  YYSYMBOL_REPEAT = 39,                    /* REPEAT  */
  YYSYMBOL_UNTIL = 40,                     /* UNTIL  */
  YYSYMBOL_WHILE = 41,                     /* WHILE  */
  YYSYMBOL_DO = 42,                        /* DO  */
  YYSYMBOL_CASE = 43,                      /* CASE  */
  YYSYMBOL_TO = 44,                        /* TO  */
  YYSYMBOL_DOWNTO = 45,                    /* DOWNTO  */
  YYSYMBOL_FOR = 46,                       /* FOR  */
  YYSYMBOL_EQUAL = 47,                     /* EQUAL  */
  YYSYMBOL_UNEQUAL = 48,                   /* UNEQUAL  */
  YYSYMBOL_GE = 49,                        /* GE  */
  YYSYMBOL_GT = 50,                        /* GT  */
  YYSYMBOL_LE = 51,                        /* LE  */
  YYSYMBOL_LT = 52,                        /* LT  */
  YYSYMBOL_ASSIGN = 53,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 54,                      /* PLUS  */
  YYSYMBOL_MINUS = 55,                     /* MINUS  */
  YYSYMBOL_MUL = 56,                       /* MUL  */
  YYSYMBOL_DIV = 57,                       /* DIV  */
  YYSYMBOL_OR = 58,                        /* OR  */
  YYSYMBOL_AND = 59,                       /* AND  */
  YYSYMBOL_NOT = 60,                       /* NOT  */
  YYSYMBOL_MOD = 61,                       /* MOD  */
  YYSYMBOL_LB = 62,                        /* LB  */
  YYSYMBOL_RB = 63,                        /* RB  */
  YYSYMBOL_LP = 64,                        /* LP  */
  YYSYMBOL_RP = 65,                        /* RP  */
  YYSYMBOL_SEMICOLON = 66,                 /* SEMICOLON  */
  YYSYMBOL_DOT = 67,                       /* DOT  */
  YYSYMBOL_DOUBLEDOT = 68,                 /* DOUBLEDOT  */
  YYSYMBOL_COMMA = 69,                     /* COMMA  */
  YYSYMBOL_COLON = 70,                     /* COLON  */
  YYSYMBOL_INT_TYPE = 71,                  /* INT_TYPE  */
  YYSYMBOL_BOOL_TYPE = 72,                 /* BOOL_TYPE  */
  YYSYMBOL_CHAR_TYPE = 73,                 /* CHAR_TYPE  */
  YYSYMBOL_ARRAY = 74,                     /* ARRAY  */
  YYSYMBOL_OF = 75,                        /* OF  */
  YYSYMBOL_RECORD = 76,                    /* RECORD  */
  YYSYMBOL_GOTO = 77,                      /* GOTO  */
  YYSYMBOL_BREAK = 78,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 79,                  /* CONTINUE  */
  YYSYMBOL_OTHERWISE = 80,                 /* OTHERWISE  */
  YYSYMBOL_ERROR = 81,                     /* ERROR  */
  YYSYMBOL_YYACCEPT = 82,                  /* $accept  */
  YYSYMBOL_program = 83,                   /* program  */
  YYSYMBOL_routine = 84,                   /* routine  */
  YYSYMBOL_routine_head = 85,              /* routine_head  */
  YYSYMBOL_routine_part = 86,              /* routine_part  */
  YYSYMBOL_fun_decl = 87,                  /* fun_decl  */
  YYSYMBOL_fun_head = 88,                  /* fun_head  */
  YYSYMBOL_proc_decl = 89,                 /* proc_decl  */
  YYSYMBOL_proc_head = 90,                 /* proc_head  */
  YYSYMBOL_params = 91,                    /* params  */
  YYSYMBOL_params_decl = 92,               /* params_decl  */
  YYSYMBOL_params_type = 93,               /* params_type  */
  YYSYMBOL_var_part = 94,                  /* var_part  */
  YYSYMBOL_var_decl_list = 95,             /* var_decl_list  */
  YYSYMBOL_var_decl = 96,                  /* var_decl  */
  YYSYMBOL_const_part = 97,                /* const_part  */
  YYSYMBOL_const_expr_list = 98,           /* const_expr_list  */
  YYSYMBOL_const_expr = 99,                /* const_expr  */
  YYSYMBOL_const_value = 100,              /* const_value  */
  YYSYMBOL_type_part = 101,                /* type_part  */
  YYSYMBOL_type_decl_list = 102,           /* type_decl_list  */
  YYSYMBOL_type_def = 103,                 /* type_def  */
  YYSYMBOL_type_decl = 104,                /* type_decl  */
  YYSYMBOL_record_type_decl = 105,         /* record_type_decl  */
  YYSYMBOL_field_decl_list = 106,          /* field_decl_list  */
  YYSYMBOL_field_decl = 107,               /* field_decl  */
  YYSYMBOL_array_type_decl = 108,          /* array_type_decl  */
  YYSYMBOL_simple_type = 109,              /* simple_type  */
  YYSYMBOL_name_list = 110,                /* name_list  */
  YYSYMBOL_identifier = 111,               /* identifier  */
  YYSYMBOL_routine_body = 112,             /* routine_body  */
  YYSYMBOL_compound_stmt = 113,            /* compound_stmt  */
  YYSYMBOL_stmt_list = 114,                /* stmt_list  */
  YYSYMBOL_stmt = 115,                     /* stmt  */
  YYSYMBOL_no_label_stmt = 116,            /* no_label_stmt  */
  YYSYMBOL_assign_stmt = 117,              /* assign_stmt  */
  YYSYMBOL_goto_stmt = 118,                /* goto_stmt  */
  YYSYMBOL_if_stmt = 119,                  /* if_stmt  */
  YYSYMBOL_else_clause = 120,              /* else_clause  */
  YYSYMBOL_repeat_stmt = 121,              /* repeat_stmt  */
  YYSYMBOL_while_stmt = 122,               /* while_stmt  */
  YYSYMBOL_case_stmt = 123,                /* case_stmt  */
  YYSYMBOL_case_expr_list = 124,           /* case_expr_list  */
  YYSYMBOL_case_expr = 125,                /* case_expr  */
  YYSYMBOL_for_stmt = 126,                 /* for_stmt  */
  YYSYMBOL_for_head = 127,                 /* for_head  */
  YYSYMBOL_proc_stmt = 128,                /* proc_stmt  */
  YYSYMBOL_args_list = 129,                /* args_list  */
  YYSYMBOL_expression = 130,               /* expression  */
  YYSYMBOL_expr = 131,                     /* expr  */
  YYSYMBOL_term = 132,                     /* term  */
  YYSYMBOL_factor = 133,                   /* factor  */
  YYSYMBOL_lvalue = 134                    /* lvalue  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
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
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   697

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  82
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  158
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  315

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   336


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   239,   239,   250,   262,   274,   288,   298,   308,   316,
     329,   342,   355,   370,   388,   407,   426,   447,   485,   497,
     510,   523,   538,   566,   575,   585,   594,   605,   613,   623,
     631,   641,   650,   661,   678,   698,   706,   716,   725,   736,
     753,   773,   781,   789,   798,   809,   817,   825,   833,   843,
     851,   861,   870,   881,   898,   918,   926,   934,   944,   967,
     976,   987,   994,  1004,  1030,  1038,  1046,  1054,  1062,  1070,
    1078,  1088,  1097,  1108,  1119,  1129,  1137,  1148,  1156,  1165,
    1177,  1186,  1196,  1204,  1212,  1220,  1228,  1236,  1244,  1252,
    1260,  1268,  1276,  1286,  1308,  1318,  1333,  1351,  1359,  1369,
    1384,  1392,  1409,  1464,  1473,  1484,  1492,  1502,  1521,  1544,
    1569,  1589,  1609,  1632,  1640,  1662,  1670,  1693,  1730,  1762,
    1799,  1833,  1842,  1853,  1868,  1883,  1898,  1913,  1928,  1944,
    1953,  1968,  1983,  1998,  2008,  2023,  2038,  2053,  2068,  2078,
    2094,  2102,  2117,  2125,  2140,  2155,  2178,  2201,  2224,  2247,
    2270,  2293,  2316,  2339,  2364,  2393,  2414,  2435,  2451
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAM", "FUNCTION",
  "PROCEDURE", "CONST", "TYPE", "VAR", "BBEGIN", "END", "IDENT_NAME",
  "INTEGER", "BOOLEAN", "CHAR", "STRING", "TRUE", "FALSE", "MAXINT",
  "READ", "READLN", "WRITE", "WRITELN", "MEMORYREAD", "MEMORYWRITE",
  "STACKREAD", "STACKWRITE", "ABS", "CHR", "ODD", "ORD", "PRED", "SUCC",
  "TOINT", "TOCHAR", "TOBOOL", "IF", "THEN", "ELSE", "REPEAT", "UNTIL",
  "WHILE", "DO", "CASE", "TO", "DOWNTO", "FOR", "EQUAL", "UNEQUAL", "GE",
  "GT", "LE", "LT", "ASSIGN", "PLUS", "MINUS", "MUL", "DIV", "OR", "AND",
  "NOT", "MOD", "LB", "RB", "LP", "RP", "SEMICOLON", "DOT", "DOUBLEDOT",
  "COMMA", "COLON", "INT_TYPE", "BOOL_TYPE", "CHAR_TYPE", "ARRAY", "OF",
  "RECORD", "GOTO", "BREAK", "CONTINUE", "OTHERWISE", "ERROR", "$accept",
  "program", "routine", "routine_head", "routine_part", "fun_decl",
  "fun_head", "proc_decl", "proc_head", "params", "params_decl",
  "params_type", "var_part", "var_decl_list", "var_decl", "const_part",
  "const_expr_list", "const_expr", "const_value", "type_part",
  "type_decl_list", "type_def", "type_decl", "record_type_decl",
  "field_decl_list", "field_decl", "array_type_decl", "simple_type",
  "name_list", "identifier", "routine_body", "compound_stmt", "stmt_list",
  "stmt", "no_label_stmt", "assign_stmt", "goto_stmt", "if_stmt",
  "else_clause", "repeat_stmt", "while_stmt", "case_stmt",
  "case_expr_list", "case_expr", "for_stmt", "for_head", "proc_stmt",
  "args_list", "expression", "expr", "term", "factor", "lvalue", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-191)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-155)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       0,    19,    58,     4,  -191,    49,    67,    11,    71,    84,
    -191,    49,  -191,    36,    35,  -191,  -191,  -191,  -191,    49,
     105,  -191,    10,  -191,   137,    49,  -191,    78,    49,    64,
    -191,  -191,  -191,  -191,  -191,  -191,     3,    74,  -191,    48,
      89,  -191,   103,   113,   135,   142,   164,   169,   582,  -191,
     582,   582,    49,   200,  -191,  -191,   -10,  -191,   159,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,   433,  -191,    -3,
    -191,   531,    49,  -191,    31,  -191,   224,   233,    64,  -191,
       5,  -191,     6,  -191,  -191,  -191,   462,   582,   582,   582,
     582,   582,   582,   582,   174,   189,   194,   198,   206,   207,
     208,   218,   221,   633,   582,   582,  -191,   -22,   308,    52,
      18,  -191,   -21,   388,   521,   -14,   197,  -191,   582,   582,
      49,  -191,  -191,   582,   582,    49,    49,  -191,  -191,  -191,
     234,    49,   215,   226,  -191,  -191,  -191,   222,  -191,    49,
     531,   239,   239,  -191,  -191,    67,   238,    67,   240,  -191,
     242,    23,   314,    54,    59,    62,    76,    86,   582,   582,
     582,   582,   582,   582,   582,   582,   582,  -191,  -191,  -191,
    -191,   172,   582,   433,   582,   582,   582,   582,   582,   582,
     260,   582,   582,   582,   582,   582,   582,   582,   582,   433,
     502,   582,   139,   110,  -191,   314,   228,  -191,   127,   193,
     101,  -191,    63,    10,  -191,    49,  -191,   252,    40,   235,
    -191,   255,  -191,   257,  -191,  -191,  -191,   582,  -191,  -191,
    -191,  -191,  -191,   132,   148,   161,   162,   180,   186,   187,
     219,   230,  -191,   232,   260,    52,    52,    52,    52,    52,
      52,   433,  -191,    18,    18,    18,  -191,  -191,  -191,  -191,
     314,  -191,   433,   361,  -191,    46,   291,  -191,  -191,  -191,
    -191,   261,  -191,  -191,   531,  -191,  -191,  -191,    49,    77,
    -191,    95,   193,  -191,  -191,   314,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,   259,  -191,
    -191,   433,   582,   582,   251,   271,   191,  -191,    40,   193,
    -191,  -191,   280,   576,   627,   531,  -191,   193,  -191,  -191,
    -191,  -191,  -191,  -191,  -191
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    35,     1,     0,    35,     5,     0,    49,
      73,    36,    38,     0,     3,     4,    77,     6,    74,     0,
      29,    37,     0,     2,    76,    50,    52,     0,     0,     8,
      41,    43,    44,    45,    46,    47,     0,    40,    75,     0,
       0,   113,     0,   115,     0,     0,     0,     0,     0,    77,
       0,     0,     0,     0,    91,    92,   110,    83,    79,    81,
      82,    84,    85,    86,    87,    88,    89,   100,    90,     0,
      51,     0,    30,    32,     0,    72,     0,     0,     7,    11,
      35,    12,    35,    42,    48,    39,   100,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   141,   154,   100,   129,
     133,   138,   140,   100,     0,     0,     0,    94,     0,     0,
       0,    78,   107,     0,     0,     0,     0,    68,    69,    70,
       0,     0,     0,    54,    57,    56,    55,    64,    31,     0,
       0,    23,    23,     9,    10,    35,    16,    35,    21,    80,
       0,     0,   122,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    41,    47,   144,
     143,     0,     0,   100,     0,     0,     0,     0,     0,     0,
      97,     0,     0,     0,     0,     0,     0,     0,     0,   100,
       0,     0,     0,     0,   157,    93,     0,   158,     0,     0,
       0,    60,     0,     0,    53,     0,    71,    34,     0,     0,
      22,    14,    15,    20,    19,   112,   114,     0,   116,   117,
     118,   119,   120,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   142,     0,    97,   127,   128,   123,   124,   125,
     126,   100,    96,   130,   131,   132,   134,   135,   137,   136,
      99,   101,   100,     0,   104,     0,     0,   155,   111,   156,
      65,     0,    58,    59,     0,    66,    67,    33,     0,     0,
      26,     0,     0,    13,    18,   121,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   139,    95,    98,     0,   102,
     103,   100,     0,     0,     0,    62,     0,    24,     0,     0,
      17,   106,     0,     0,     0,     0,    61,     0,    25,    28,
     105,   108,   109,    63,    27
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -191,  -191,     7,  -191,  -191,   270,  -191,   272,  -191,   210,
    -191,    55,  -191,  -191,   295,  -191,  -191,   357,   -18,  -191,
    -191,   344,  -135,  -191,  -191,   170,  -191,  -190,  -124,    -5,
    -191,   366,   331,   -59,   296,  -191,  -191,  -191,   147,  -191,
    -191,  -191,  -191,   130,  -191,  -191,  -191,   150,   -19,   227,
    -165,   -48,   -23
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     7,     8,    78,    79,    80,    81,    82,   209,
     269,   270,    29,    72,    73,     9,    11,    12,   106,    20,
      25,    26,   133,   134,   200,   201,   135,   136,    74,   107,
      17,    57,    24,    58,    59,    60,    61,    62,   242,    63,
      64,    65,   253,   254,    66,    67,    68,   151,   152,   109,
     110,   111,   112
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      13,    69,   198,     1,    37,   207,    13,   202,   122,   261,
       5,     5,     5,    14,    27,    83,   243,   244,   245,    56,
      27,    84,    30,    75,    31,    32,    33,    34,    35,   108,
       3,   114,   115,   174,   175,   176,   177,   178,   179,   150,
     118,   124,   172,  -154,    69,   120,   125,   116,   268,   180,
     123,    10,   118,   132,   119,   169,   170,   120,     4,   124,
      10,   190,    56,    69,   125,    36,   137,    75,    76,    77,
       6,   145,   147,     5,   184,   185,   202,   186,    15,   187,
      16,    56,   300,    22,   271,    69,   171,   146,   216,   148,
      69,    19,   217,   174,   175,   176,   177,   178,   179,   192,
     139,   140,    23,    56,   195,   196,   181,   182,    56,   309,
     183,   262,    10,    28,   234,   194,   291,   314,    86,   218,
     197,    75,   132,   217,   219,    71,    75,   220,   217,   295,
     251,   217,   139,   264,   206,   137,   246,   247,   248,   249,
      85,   221,   297,   298,   296,   217,    16,    38,    10,    39,
      69,   222,   211,    87,   213,   217,    40,    41,    42,    43,
      44,    45,    46,    47,   139,   299,    69,    88,    56,   250,
     313,   255,   256,    48,   271,   258,    49,    89,    50,   217,
      51,   132,   287,    52,    56,   265,   174,   175,   176,   177,
     178,   179,   260,   288,   137,    75,   139,   276,   275,    90,
     266,   217,   257,    75,    10,    30,    91,    31,    32,    33,
      34,    35,   117,   277,    53,    54,    55,   217,    69,   174,
     175,   176,   177,   178,   179,   121,   278,   279,    92,    69,
     217,   217,   302,    93,   255,   141,    56,   232,   158,   153,
     154,   155,   156,   157,   142,   280,   132,    56,    36,   217,
     191,   281,   282,   159,   132,   217,   217,   126,   160,   137,
     139,   307,   161,    75,   127,   128,   129,   137,    69,   193,
     162,   163,   164,   303,   304,   174,   175,   176,   177,   178,
     179,   132,   165,   203,   283,   166,    56,   132,   217,   132,
     205,   259,   204,    75,   137,   284,   199,   285,   241,   217,
     137,   217,   137,   208,   212,   272,   214,   215,   223,   224,
     225,   226,   227,   228,   229,   230,   231,    16,   267,    10,
      39,   273,   233,   274,   294,   301,   305,    40,    41,    42,
      43,    44,    45,    46,    47,   292,   293,   306,   174,   175,
     176,   177,   178,   179,    48,   173,   310,    49,   143,    50,
     144,    51,   210,   308,    52,   174,   175,   176,   177,   178,
     179,   174,   175,   176,   177,   178,   179,   138,    21,    70,
     263,   289,    10,    30,    18,    31,    32,    33,    34,    35,
     113,   286,   149,   290,     0,    53,    54,    55,    94,    95,
      96,    97,    98,    99,   100,   101,   102,    16,     0,    10,
      39,   235,   236,   237,   238,   239,   240,    40,    41,    42,
      43,    44,    45,    46,    47,     0,   103,     0,     0,     0,
       0,   104,     0,     0,    48,   105,     0,    49,   188,    50,
       0,    51,     0,     0,    52,     0,     0,     0,     0,     0,
       0,   252,    16,     0,    10,    39,     0,     0,     0,     0,
       0,     0,    40,    41,    42,    43,    44,    45,    46,    47,
       0,     0,     0,     0,     0,    53,    54,    55,     0,    48,
       0,    16,    49,    10,    50,     0,    51,     0,     0,    52,
       0,    40,    41,    42,    43,    44,    45,    46,    47,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,     0,
       0,    49,     0,    50,     0,    51,     0,     0,    52,     0,
      53,    54,    55,    10,    30,     0,    31,    32,    33,    34,
      35,     0,     0,     0,     0,     0,     0,     0,     0,    94,
      95,    96,    97,    98,    99,   100,   101,   102,     0,    53,
      54,    55,    10,    30,     0,    31,    32,    33,    34,    35,
       0,     0,     0,     0,     0,     0,     0,   103,     0,     0,
       0,     0,   104,   189,     0,     0,   105,     0,   174,   175,
     176,   177,   178,   179,     0,     0,     0,     0,     0,     0,
       0,     0,   252,     0,     0,     0,    36,     0,     0,     0,
       0,     0,     0,    10,    30,   126,    31,    32,    33,    34,
      35,     0,   127,   128,   129,   130,     0,   131,     0,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   311,     0,
       0,     0,     0,   174,   175,   176,   177,   178,   179,     0,
       0,     0,     0,     0,     0,     0,     0,   103,     0,     0,
       0,     0,   104,     0,    10,   167,   105,    31,    32,    33,
      34,   168,     0,     0,     0,     0,     0,     0,     0,     0,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   312,
       0,     0,     0,     0,   174,   175,   176,   177,   178,   179,
       0,     0,     0,     0,     0,     0,     0,     0,   103,     0,
       0,     0,     0,   104,     0,     0,     0,   105
};

static const yytype_int16 yycheck[] =
{
       5,    24,   126,     3,    22,   140,    11,   131,    67,   199,
       6,     6,     6,     6,    19,    12,   181,   182,   183,    24,
      25,    18,    12,    28,    14,    15,    16,    17,    18,    48,
      11,    50,    51,    47,    48,    49,    50,    51,    52,    87,
      62,    62,    64,    53,    67,    67,    67,    52,     8,   108,
      53,    11,    62,    71,    64,   103,   104,    67,     0,    62,
      11,    75,    67,    86,    67,    55,    71,    72,     4,     5,
      66,    66,    66,     6,    56,    57,   200,    59,    67,    61,
       9,    86,   272,    47,   208,   108,   105,    80,    65,    82,
     113,     7,    69,    47,    48,    49,    50,    51,    52,   118,
      69,    70,    67,   108,   123,   124,    54,    55,   113,   299,
      58,    10,    11,     8,   173,   120,    70,   307,    70,    65,
     125,   126,   140,    69,    65,    47,   131,    65,    69,   264,
     189,    69,    69,    70,   139,   140,   184,   185,   186,   187,
      66,    65,    65,    66,   268,    69,     9,    10,    11,    12,
     173,    65,   145,    64,   147,    69,    19,    20,    21,    22,
      23,    24,    25,    26,    69,    70,   189,    64,   173,   188,
     305,   190,   191,    36,   298,    65,    39,    64,    41,    69,
      43,   199,   241,    46,   189,   203,    47,    48,    49,    50,
      51,    52,    65,   252,   199,   200,    69,    65,   217,    64,
     205,    69,    63,   208,    11,    12,    64,    14,    15,    16,
      17,    18,    12,    65,    77,    78,    79,    69,   241,    47,
      48,    49,    50,    51,    52,    66,    65,    65,    64,   252,
      69,    69,   291,    64,   253,    11,   241,    65,    64,    89,
      90,    91,    92,    93,    11,    65,   264,   252,    55,    69,
      53,    65,    65,    64,   272,    69,    69,    64,    64,   264,
      69,    70,    64,   268,    71,    72,    73,   272,   291,   119,
      64,    64,    64,   292,   293,    47,    48,    49,    50,    51,
      52,   299,    64,    68,    65,    64,   291,   305,    69,   307,
      68,    63,    66,   298,   299,    65,    62,    65,    38,    69,
     305,    69,   307,    64,    66,    70,    66,    65,   158,   159,
     160,   161,   162,   163,   164,   165,   166,     9,    66,    11,
      12,    66,   172,    66,    63,    66,    75,    19,    20,    21,
      22,    23,    24,    25,    26,    44,    45,    66,    47,    48,
      49,    50,    51,    52,    36,    37,    66,    39,    78,    41,
      78,    43,   142,   298,    46,    47,    48,    49,    50,    51,
      52,    47,    48,    49,    50,    51,    52,    72,    11,    25,
     200,    10,    11,    12,     8,    14,    15,    16,    17,    18,
      49,   234,    86,   253,    -1,    77,    78,    79,    27,    28,
      29,    30,    31,    32,    33,    34,    35,     9,    -1,    11,
      12,   174,   175,   176,   177,   178,   179,    19,    20,    21,
      22,    23,    24,    25,    26,    -1,    55,    -1,    -1,    -1,
      -1,    60,    -1,    -1,    36,    64,    -1,    39,    40,    41,
      -1,    43,    -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    80,     9,    -1,    11,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    19,    20,    21,    22,    23,    24,    25,    26,
      -1,    -1,    -1,    -1,    -1,    77,    78,    79,    -1,    36,
      -1,     9,    39,    11,    41,    -1,    43,    -1,    -1,    46,
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    39,    -1,    41,    -1,    43,    -1,    -1,    46,    -1,
      77,    78,    79,    11,    12,    -1,    14,    15,    16,    17,
      18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    -1,    77,
      78,    79,    11,    12,    -1,    14,    15,    16,    17,    18,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    60,    42,    -1,    -1,    64,    -1,    47,    48,
      49,    50,    51,    52,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    80,    -1,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    11,    12,    64,    14,    15,    16,    17,
      18,    -1,    71,    72,    73,    74,    -1,    76,    -1,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    42,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    51,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    60,    -1,    11,    12,    64,    14,    15,    16,
      17,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    42,
      -1,    -1,    -1,    -1,    47,    48,    49,    50,    51,    52,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    60,    -1,    -1,    -1,    64
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    83,    11,     0,     6,    66,    84,    85,    97,
      11,    98,    99,   111,    84,    67,     9,   112,   113,     7,
     101,    99,    47,    67,   114,   102,   103,   111,     8,    94,
      12,    14,    15,    16,    17,    18,    55,   100,    10,    12,
      19,    20,    21,    22,    23,    24,    25,    26,    36,    39,
      41,    43,    46,    77,    78,    79,   111,   113,   115,   116,
     117,   118,   119,   121,   122,   123,   126,   127,   128,   134,
     103,    47,    95,    96,   110,   111,     4,     5,    86,    87,
      88,    89,    90,    12,    18,    66,    70,    64,    64,    64,
      64,    64,    64,    64,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    55,    60,    64,   100,   111,   130,   131,
     132,   133,   134,   114,   130,   130,   111,    12,    62,    64,
      67,    66,   115,    53,    62,    67,    64,    71,    72,    73,
      74,    76,   100,   104,   105,   108,   109,   111,    96,    69,
      70,    11,    11,    87,    89,    66,    84,    66,    84,   116,
     133,   129,   130,   129,   129,   129,   129,   129,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    12,    18,   133,
     133,   130,    64,    37,    47,    48,    49,    50,    51,    52,
     115,    54,    55,    58,    56,    57,    59,    61,    40,    42,
      75,    53,   130,   129,   111,   130,   130,   111,   110,    62,
     106,   107,   110,    68,    66,    68,   111,   104,    64,    91,
      91,    84,    66,    84,    66,    65,    65,    69,    65,    65,
      65,    65,    65,   129,   129,   129,   129,   129,   129,   129,
     129,   129,    65,   129,   115,   131,   131,   131,   131,   131,
     131,    38,   120,   132,   132,   132,   133,   133,   133,   133,
     130,   115,    80,   124,   125,   130,   130,    63,    65,    63,
      65,   109,    10,   107,    70,   100,   111,    66,     8,    92,
      93,   110,    70,    66,    66,   130,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,   120,   115,   115,    10,
     125,    70,    44,    45,    63,   104,   110,    65,    66,    70,
     109,    66,   115,   130,   130,    75,    66,    70,    93,   109,
      66,    42,    42,   104,   109
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    82,    83,    83,    83,    83,    84,    85,    86,    86,
      86,    86,    86,    87,    87,    87,    87,    88,    89,    89,
      89,    89,    90,    91,    91,    92,    92,    93,    93,    94,
      94,    95,    95,    96,    96,    97,    97,    98,    98,    99,
      99,   100,   100,   100,   100,   100,   100,   100,   100,   101,
     101,   102,   102,   103,   103,   104,   104,   104,   105,   106,
     106,   107,   107,   108,   109,   109,   109,   109,   109,   109,
     109,   110,   110,   111,   112,   113,   113,   114,   114,   114,
     115,   115,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   117,   118,   119,   119,   120,   120,   121,
     121,   122,   123,   124,   124,   125,   125,   126,   127,   127,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   129,   129,   130,   130,   130,   130,   130,   130,   130,
     131,   131,   131,   131,   132,   132,   132,   132,   132,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   134,   134,   134,   134,   134
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     4,     4,     3,     2,     4,     0,     2,
       2,     1,     1,     4,     3,     3,     2,     5,     4,     3,
       3,     2,     3,     0,     3,     3,     1,     4,     3,     0,
       2,     2,     1,     4,     3,     0,     2,     2,     1,     4,
       3,     1,     2,     1,     1,     1,     1,     1,     2,     0,
       2,     2,     1,     4,     3,     1,     1,     1,     3,     2,
       1,     4,     3,     6,     1,     3,     3,     3,     1,     1,
       1,     3,     1,     1,     1,     3,     2,     0,     3,     2,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     2,     5,     4,     0,     2,     4,
       0,     4,     5,     2,     1,     4,     3,     2,     7,     7,
       1,     4,     4,     1,     4,     1,     4,     4,     4,     4,
       4,     3,     1,     3,     3,     3,     3,     3,     3,     1,
       3,     3,     3,     1,     3,     3,     3,     3,     1,     4,
       1,     1,     3,     2,     2,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     1,     4,     4,     3,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
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

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
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
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: PROGRAM IDENT_NAME SEMICOLON routine DOT  */
#line 239 "src/yacc.y"
                                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse program 1: " << (*(yyvsp[-3].token).stringValue) << std::endl;
        #endif

        std::string name{*(yyvsp[-3].token).stringValue};
        (yyvsp[-1].routineNode)->setSubType(ast::RoutineNode::SubType::MAIN);
        (yyval.programNode) = new ast::ProgramNode(std::move(name), (yyvsp[-1].routineNode));
        resultAst = (yyval.programNode);
    }
#line 1587 "out/parser.cpp"
    break;

  case 3: /* program: PROGRAM IDENT_NAME SEMICOLON routine  */
#line 250 "src/yacc.y"
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
#line 1603 "out/parser.cpp"
    break;

  case 4: /* program: PROGRAM IDENT_NAME routine DOT  */
#line 262 "src/yacc.y"
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
#line 1619 "out/parser.cpp"
    break;

  case 5: /* program: PROGRAM IDENT_NAME routine  */
#line 274 "src/yacc.y"
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
#line 1635 "out/parser.cpp"
    break;

  case 6: /* routine: routine_head routine_body  */
#line 288 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine" << std::endl;
        #endif

        (yyval.routineNode) = new ast::RoutineNode((yyvsp[-1].routineHeadNode), (yyvsp[0].routineBodyNode));
    }
#line 1647 "out/parser.cpp"
    break;

  case 7: /* routine_head: const_part type_part var_part routine_part  */
#line 298 "src/yacc.y"
                                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine head" << std::endl;
        #endif

        (yyval.routineHeadNode) = new ast::RoutineHeadNode((yyvsp[-3].constPartList), (yyvsp[-2].typePartList), (yyvsp[-1].varPartList), (yyvsp[0].routinePartList));
    }
#line 1659 "out/parser.cpp"
    break;

  case 8: /* routine_part: %empty  */
#line 308 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty routine part" << std::endl;
        #endif

        (yyval.routinePartList) = new std::vector<ast::RoutineDeclarationNode*>();
    }
#line 1671 "out/parser.cpp"
    break;

  case 9: /* routine_part: routine_part fun_decl  */
#line 316 "src/yacc.y"
                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine part with fun decl 1 " << (yyvsp[0].routineDeclarationNode)->getName() << std::endl;
        #endif

        if(!saveRoutine((yyvsp[0].routineDeclarationNode), true)) {
            YYERROR;
        }

        (yyval.routinePartList) = (yyvsp[-1].routinePartList);
        (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1688 "out/parser.cpp"
    break;

  case 10: /* routine_part: routine_part proc_decl  */
#line 329 "src/yacc.y"
                           {
       #ifdef YACC_DEBUG
           std::cout << "Yacc debug: Parse routine part with proc decl 1 " << (yyvsp[0].routineDeclarationNode)->getName() << std::endl;
       #endif

       if(!saveRoutine((yyvsp[0].routineDeclarationNode), true)) {
           YYERROR;
       }

       (yyval.routinePartList) = (yyvsp[-1].routinePartList);
       (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1705 "out/parser.cpp"
    break;

  case 11: /* routine_part: fun_decl  */
#line 342 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine part with fun decl 2 " << (yyvsp[0].routineDeclarationNode)->getName() << std::endl;
        #endif

        if(!saveRoutine((yyvsp[0].routineDeclarationNode), true)) {
            YYERROR;
        }

        (yyval.routinePartList) = new std::vector<ast::RoutineDeclarationNode*>();
        (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1722 "out/parser.cpp"
    break;

  case 12: /* routine_part: proc_decl  */
#line 355 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine part with proc decl 2 " << (yyvsp[0].routineDeclarationNode)->getName() << std::endl;
        #endif

        if(!saveRoutine((yyvsp[0].routineDeclarationNode), true)) {
            YYERROR;
        }

        (yyval.routinePartList) = new std::vector<ast::RoutineDeclarationNode*>();
        (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1739 "out/parser.cpp"
    break;

  case 13: /* fun_decl: fun_head SEMICOLON routine SEMICOLON  */
#line 370 "src/yacc.y"
                                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun decl 1" << std::endl;
        #endif

        if(!hasReturnValue((yyvsp[-1].routineNode), (yyvsp[-3].routineDeclarationNode)->getName())) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", function should have one return value");
            fatalError = true;
            YYERROR;
        }

        ctx->getLookupTable().popScope();

        (yyval.routineDeclarationNode) = (yyvsp[-3].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[-1].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
    }
#line 1761 "out/parser.cpp"
    break;

  case 14: /* fun_decl: fun_head SEMICOLON routine  */
#line 388 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun decl 2" << std::endl;
        #endif

        if(!hasReturnValue((yyvsp[0].routineNode), (yyvsp[-2].routineDeclarationNode)->getName())) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", function should have one return value");
            fatalError = true;
            YYERROR;
        }

        ctx->getLookupTable().popScope();

        (yyval.routineDeclarationNode) = (yyvsp[-2].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[0].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1784 "out/parser.cpp"
    break;

  case 15: /* fun_decl: fun_head routine SEMICOLON  */
#line 407 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun decl 3" << std::endl;
        #endif

        if(!hasReturnValue((yyvsp[-1].routineNode), (yyvsp[-2].routineDeclarationNode)->getName())) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", function should have one return value");
            fatalError = true;
            YYERROR;
        }

        ctx->getLookupTable().popScope();

        (yyval.routineDeclarationNode) = (yyvsp[-2].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[-1].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1807 "out/parser.cpp"
    break;

  case 16: /* fun_decl: fun_head routine  */
#line 426 "src/yacc.y"
                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun decl 4" << std::endl;
        #endif

        if(!hasReturnValue((yyvsp[0].routineNode), (yyvsp[-1].routineDeclarationNode)->getName())) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", function should have one return value");
            fatalError = true;
            YYERROR;
        }

        ctx->getLookupTable().popScope();

        (yyval.routineDeclarationNode) = (yyvsp[-1].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[0].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1830 "out/parser.cpp"
    break;

  case 17: /* fun_head: FUNCTION IDENT_NAME params COLON simple_type  */
#line 447 "src/yacc.y"
                                                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun head " << (*(yyvsp[-3].token).stringValue) << std::endl;
        #endif

        ctx->getLookupTable().pushScope(*(yyvsp[-3].token).stringValue);

        std::string funType = getTypeString((yyvsp[0].simpleTypeNode));
        if(funType == "unspecified") {
            YYERROR;
        }

        std::vector<ast::IdentifierNode*> funNameVector{new ast::IdentifierNode(*(yyvsp[-3].token).stringValue)};
        if(!saveVariables(&funNameVector, funType)) {
            YYERROR;
        }

        for(const auto& param : *(yyvsp[-2].paramsNode)->getParams()) {
            std::string paramType = getTypeString(param->getParamsType().get());
            if(paramType == "unspecified") {
                YYERROR;
            }

            if(!saveVariables(param->getParams().get(), paramType)) {
                YYERROR;
            }
        }

        std::string name{*(yyvsp[-3].token).stringValue};
        (yyval.routineDeclarationNode) = new ast::RoutineDeclarationNode(ast::RoutineDeclarationNode::RoutineType::FUNCTION, std::move(name), (yyvsp[-2].paramsNode), (yyvsp[0].simpleTypeNode), nullptr);

        if(!saveRoutine((yyval.routineDeclarationNode), false)) {
            YYERROR;
        }
    }
#line 1870 "out/parser.cpp"
    break;

  case 18: /* proc_decl: proc_head SEMICOLON routine SEMICOLON  */
#line 485 "src/yacc.y"
                                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse proc decl" << std::endl;
        #endif

        ctx->getLookupTable().popScope();

        (yyval.routineDeclarationNode) = (yyvsp[-3].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[-1].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::PROCEDURE);
    }
#line 1886 "out/parser.cpp"
    break;

  case 19: /* proc_decl: proc_head routine SEMICOLON  */
#line 497 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse proc decl" << std::endl;
        #endif

        ctx->getLookupTable().popScope();

        (yyval.routineDeclarationNode) = (yyvsp[-2].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[-1].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::PROCEDURE);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1903 "out/parser.cpp"
    break;

  case 20: /* proc_decl: proc_head SEMICOLON routine  */
#line 510 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse proc decl" << std::endl;
        #endif

        ctx->getLookupTable().popScope();

        (yyval.routineDeclarationNode) = (yyvsp[-2].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[0].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::PROCEDURE);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1920 "out/parser.cpp"
    break;

  case 21: /* proc_decl: proc_head routine  */
#line 523 "src/yacc.y"
                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse proc decl" << std::endl;
        #endif

        ctx->getLookupTable().popScope();

        (yyval.routineDeclarationNode) = (yyvsp[-1].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[0].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::PROCEDURE);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1937 "out/parser.cpp"
    break;

  case 22: /* proc_head: PROCEDURE IDENT_NAME params  */
#line 538 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse proc head " << (*(yyvsp[-1].token).stringValue) << std::endl;
        #endif

        ctx->getLookupTable().pushScope(*(yyvsp[-1].token).stringValue);

        for(const auto& param : *(yyvsp[0].paramsNode)->getParams()) {
            std::string paramType = getTypeString(param->getParamsType().get());
            if(paramType == "unspecified") {
                YYERROR;
            }

            if(!saveVariables(param->getParams().get(), paramType)) {
                YYERROR;
            }
        }

        std::string name{*(yyvsp[-1].token).stringValue};
        (yyval.routineDeclarationNode) = new ast::RoutineDeclarationNode(ast::RoutineDeclarationNode::RoutineType::PROCEDURE, std::move(name), (yyvsp[0].paramsNode), nullptr, nullptr);

        if(!saveRoutine((yyval.routineDeclarationNode), false)) {
            YYERROR;
        }
    }
#line 1967 "out/parser.cpp"
    break;

  case 23: /* params: %empty  */
#line 566 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty params" << std::endl;
        #endif

        std::vector<ast::ParamsGroupNode *>* emptyParamsList = new std::vector<ast::ParamsGroupNode*>();
        (yyval.paramsNode) = new ast::ParamsNode(emptyParamsList);
    }
#line 1980 "out/parser.cpp"
    break;

  case 24: /* params: LP params_decl RP  */
#line 575 "src/yacc.y"
                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params" << std::endl;
        #endif

        (yyval.paramsNode) = new ast::ParamsNode((yyvsp[-1].paramsGroupList));
    }
#line 1992 "out/parser.cpp"
    break;

  case 25: /* params_decl: params_decl SEMICOLON params_type  */
#line 585 "src/yacc.y"
                                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params decl 1" << std::endl;
        #endif

        (yyval.paramsGroupList) = (yyvsp[-2].paramsGroupList);
        (yyval.paramsGroupList)->push_back((yyvsp[0].paramsGroupNode));
    }
#line 2005 "out/parser.cpp"
    break;

  case 26: /* params_decl: params_type  */
#line 594 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params decl 2" << std::endl;
        #endif

        (yyval.paramsGroupList) = new std::vector<ast::ParamsGroupNode*>();
        (yyval.paramsGroupList)->push_back((yyvsp[0].paramsGroupNode));
    }
#line 2018 "out/parser.cpp"
    break;

  case 27: /* params_type: VAR name_list COLON simple_type  */
#line 605 "src/yacc.y"
                                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params type 1" << std::endl;
        #endif

        (yyval.paramsGroupNode) = new ast::ParamsGroupNode(ast::ParamsGroupNode::PassType::PASS_BY_REFERENCE, (yyvsp[-2].identifierList), (yyvsp[0].simpleTypeNode));
    }
#line 2030 "out/parser.cpp"
    break;

  case 28: /* params_type: name_list COLON simple_type  */
#line 613 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params type 2" << std::endl;
        #endif

        (yyval.paramsGroupNode) = new ast::ParamsGroupNode(ast::ParamsGroupNode::PassType::PASS_BY_VALUE, (yyvsp[-2].identifierList), (yyvsp[0].simpleTypeNode));
    }
#line 2042 "out/parser.cpp"
    break;

  case 29: /* var_part: %empty  */
#line 623 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty var part" << std::endl;
        #endif

        (yyval.varPartList) = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
    }
#line 2054 "out/parser.cpp"
    break;

  case 30: /* var_part: VAR var_decl_list  */
#line 631 "src/yacc.y"
                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var part" << std::endl;
        #endif

        (yyval.varPartList) = (yyvsp[0].varPartList);
    }
#line 2066 "out/parser.cpp"
    break;

  case 31: /* var_decl_list: var_decl_list var_decl  */
#line 641 "src/yacc.y"
                           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl list 1" << std::endl;
        #endif

        (yyval.varPartList) = (yyvsp[-1].varPartList);
        (yyval.varPartList)->push_back((yyvsp[0].varPartListElement));
    }
#line 2079 "out/parser.cpp"
    break;

  case 32: /* var_decl_list: var_decl  */
#line 650 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl list 2" << std::endl;
        #endif

        (yyval.varPartList) = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
        (yyval.varPartList)->push_back((yyvsp[0].varPartListElement));
    }
#line 2092 "out/parser.cpp"
    break;

  case 33: /* var_decl: name_list COLON type_decl SEMICOLON  */
#line 661 "src/yacc.y"
                                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl 1" << std::endl;
        #endif

        std::string varType = getTypeString((yyvsp[-1].typeNode));
        if(varType == "unspecified") {
            YYERROR;
        }

        if(!saveVariables((yyvsp[-3].identifierList), varType)) {
            YYERROR;
        }

        (yyval.varPartListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-3].identifierList), (yyvsp[-1].typeNode));
    }
#line 2113 "out/parser.cpp"
    break;

  case 34: /* var_decl: name_list COLON type_decl  */
#line 678 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl 2" << std::endl;
        #endif

        std::string varType = getTypeString((yyvsp[0].typeNode));
        if(varType == "unspecified") {
            YYERROR;
        }

        if(!saveVariables((yyvsp[-2].identifierList), varType)) {
            YYERROR;
        }

        (yyval.varPartListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-2].identifierList), (yyvsp[0].typeNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2135 "out/parser.cpp"
    break;

  case 35: /* const_part: %empty  */
#line 698 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty const part" << std::endl;
        #endif

        (yyval.constPartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::ConstantNode*>*>();
    }
#line 2147 "out/parser.cpp"
    break;

  case 36: /* const_part: CONST const_expr_list  */
#line 706 "src/yacc.y"
                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const part" << std::endl;
        #endif

        (yyval.constPartList) = (yyvsp[0].constPartList);
    }
#line 2159 "out/parser.cpp"
    break;

  case 37: /* const_expr_list: const_expr_list const_expr  */
#line 716 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr list 1" << std::endl;
        #endif

        (yyval.constPartList) = (yyvsp[-1].constPartList);
        (yyval.constPartList)->push_back((yyvsp[0].constPartListElement));
    }
#line 2172 "out/parser.cpp"
    break;

  case 38: /* const_expr_list: const_expr  */
#line 725 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr list 2" << std::endl;
        #endif

        (yyval.constPartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::ConstantNode*>*>();
        (yyval.constPartList)->push_back((yyvsp[0].constPartListElement));
    }
#line 2185 "out/parser.cpp"
    break;

  case 39: /* const_expr: identifier EQUAL const_value SEMICOLON  */
#line 736 "src/yacc.y"
                                           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr 1" << std::endl;
        #endif

        std::string constType = getTypeString((yyvsp[-1].constantNode)->getConstantType());
        if(constType == "unspecified") {
            YYERROR;
        }

        if(!saveConstant((yyvsp[-3].identifierNode), getConstantString((yyvsp[-1].constantNode)), constType)) {
            YYERROR;
        }

        (yyval.constPartListElement) = new std::pair<ast::IdentifierNode*, ast::ConstantNode*>((yyvsp[-3].identifierNode), (yyvsp[-1].constantNode));
    }
#line 2206 "out/parser.cpp"
    break;

  case 40: /* const_expr: identifier EQUAL const_value  */
#line 753 "src/yacc.y"
                                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr 2" << std::endl;
        #endif

        std::string constType = getTypeString((yyvsp[0].constantNode)->getConstantType());
        if(constType == "unspecified") {
            YYERROR;
        }

        if(!saveConstant((yyvsp[-2].identifierNode), getConstantString((yyvsp[0].constantNode)), constType)) {
            YYERROR;
        }

        (yyval.constPartListElement) = new std::pair<ast::IdentifierNode*, ast::ConstantNode*>((yyvsp[-2].identifierNode), (yyvsp[0].constantNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2228 "out/parser.cpp"
    break;

  case 41: /* const_value: INTEGER  */
#line 773 "src/yacc.y"
            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - integer `" << (yyvsp[0].token).numericalValue << "`" << std::endl;
        #endif

        (yyval.constantNode) = new ast::IntegerConstantNode((yyvsp[0].token).numericalValue);
    }
#line 2240 "out/parser.cpp"
    break;

  case 42: /* const_value: MINUS INTEGER  */
#line 781 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - signed integer `" << -(yyvsp[0].token).numericalValue << "`" << std::endl;
        #endif

        (yyval.constantNode) = new ast::IntegerConstantNode(-(yyvsp[0].token).numericalValue);
    }
#line 2252 "out/parser.cpp"
    break;

  case 43: /* const_value: CHAR  */
#line 790 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - char `" << static_cast<char>((yyvsp[0].token).numericalValue) << "`" << std::endl;
        #endif

        (yyval.constantNode) = new ast::CharConstantNode(static_cast<char>((yyvsp[0].token).numericalValue));
    }
#line 2264 "out/parser.cpp"
    break;

  case 44: /* const_value: STRING  */
#line 798 "src/yacc.y"
           {
        std::string str{*(yyvsp[0].token).stringValue};
        str = str.substr(1, str.size() - 2);

        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - string `" << str << "`" << std::endl;
        #endif

        (yyval.constantNode) = new ast::StringConstantNode(std::move(str));
    }
#line 2279 "out/parser.cpp"
    break;

  case 45: /* const_value: TRUE  */
#line 809 "src/yacc.y"
         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - true" << std::endl;
        #endif

        (yyval.constantNode) = new ast::BooleanConstantNode(true);
    }
#line 2291 "out/parser.cpp"
    break;

  case 46: /* const_value: FALSE  */
#line 817 "src/yacc.y"
          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - false" << std::endl;
        #endif

        (yyval.constantNode) = new ast::BooleanConstantNode(false);
    }
#line 2303 "out/parser.cpp"
    break;

  case 47: /* const_value: MAXINT  */
#line 825 "src/yacc.y"
           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - maxint" << std::endl;
        #endif

        (yyval.constantNode) = new ast::IntegerConstantNode(255);
    }
#line 2315 "out/parser.cpp"
    break;

  case 48: /* const_value: MINUS MAXINT  */
#line 833 "src/yacc.y"
                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - signed maxint" << std::endl;
        #endif

        (yyval.constantNode) = new ast::IntegerConstantNode(-255);
    }
#line 2327 "out/parser.cpp"
    break;

  case 49: /* type_part: %empty  */
#line 843 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty type part" << std::endl;
        #endif

        (yyval.typePartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::TypeNode*>*>();
    }
#line 2339 "out/parser.cpp"
    break;

  case 50: /* type_part: TYPE type_decl_list  */
#line 851 "src/yacc.y"
                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type part" << std::endl;
        #endif

        (yyval.typePartList) = (yyvsp[0].typePartList);
    }
#line 2351 "out/parser.cpp"
    break;

  case 51: /* type_decl_list: type_decl_list type_def  */
#line 861 "src/yacc.y"
                            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type decl list 1" << std::endl;
        #endif

        (yyval.typePartList) = (yyvsp[-1].typePartList);
        (yyval.typePartList)->push_back((yyvsp[0].typePartListElement));
    }
#line 2364 "out/parser.cpp"
    break;

  case 52: /* type_decl_list: type_def  */
#line 870 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type decl list 2" << std::endl;
        #endif

        (yyval.typePartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::TypeNode*>*>();
        (yyval.typePartList)->push_back((yyvsp[0].typePartListElement));
    }
#line 2377 "out/parser.cpp"
    break;

  case 53: /* type_def: identifier EQUAL type_decl SEMICOLON  */
#line 881 "src/yacc.y"
                                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type def 1" << std::endl;
        #endif

        std::string typeType = getTypeString((yyvsp[-1].typeNode));
        if(typeType == "unspecified") {
            YYERROR;
        }

        if(!saveType((yyvsp[-3].identifierNode), typeType)) {
            YYERROR;
        }

        (yyval.typePartListElement) = new std::pair<ast::IdentifierNode*, ast::TypeNode*>((yyvsp[-3].identifierNode), (yyvsp[-1].typeNode));
    }
#line 2398 "out/parser.cpp"
    break;

  case 54: /* type_def: identifier EQUAL type_decl  */
#line 898 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type def 2" << std::endl;
        #endif

        std::string typeType = getTypeString((yyvsp[0].typeNode));
        if(typeType == "unspecified") {
            YYERROR;
        }

        if(!saveType((yyvsp[-2].identifierNode), typeType)) {
            YYERROR;
        }

        (yyval.typePartListElement) = new std::pair<ast::IdentifierNode*, ast::TypeNode*>((yyvsp[-2].identifierNode), (yyvsp[0].typeNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2420 "out/parser.cpp"
    break;

  case 55: /* type_decl: simple_type  */
#line 918 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type" << std::endl;
        #endif

        (yyval.typeNode) = (yyvsp[0].simpleTypeNode);
    }
#line 2432 "out/parser.cpp"
    break;

  case 56: /* type_decl: array_type_decl  */
#line 926 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse array type" << std::endl;
        #endif

        (yyval.typeNode) = (yyvsp[0].arrayTypeNode);
    }
#line 2444 "out/parser.cpp"
    break;

  case 57: /* type_decl: record_type_decl  */
#line 934 "src/yacc.y"
                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse record type" << std::endl;
        #endif

        (yyval.typeNode) = (yyvsp[0].recordTypeNode);
    }
#line 2456 "out/parser.cpp"
    break;

  case 58: /* record_type_decl: RECORD field_decl_list END  */
#line 944 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse record type" << std::endl;
        #endif

        std::set<std::string> fields;
        for(size_t i = 0; i < (yyvsp[-1].fieldDeclList)->size(); i++) {
            for(size_t j = 0; j < (yyvsp[-1].fieldDeclList)->at(i)->first->size(); j++) {
                std::string field = (yyvsp[-1].fieldDeclList)->at(i)->first->at(j)->getName();
                if(fields.find(field) != fields.end()) {
                    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", field name `" + field + "` duplication");
                    fatalError = true;
                    YYERROR;
                }
                fields.insert(field);
            }
        }

        (yyval.recordTypeNode) = new ast::RecordTypeNode((yyvsp[-1].fieldDeclList));
    }
#line 2481 "out/parser.cpp"
    break;

  case 59: /* field_decl_list: field_decl_list field_decl  */
#line 967 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl list 1" << std::endl;
        #endif

        (yyval.fieldDeclList) = (yyvsp[-1].fieldDeclList);
        (yyval.fieldDeclList)->push_back((yyvsp[0].fieldDeclListElement));
    }
#line 2494 "out/parser.cpp"
    break;

  case 60: /* field_decl_list: field_decl  */
#line 976 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl list 2" << std::endl;
        #endif

        (yyval.fieldDeclList) = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
        (yyval.fieldDeclList)->push_back((yyvsp[0].fieldDeclListElement));
    }
#line 2507 "out/parser.cpp"
    break;

  case 61: /* field_decl: name_list COLON type_decl SEMICOLON  */
#line 987 "src/yacc.y"
                                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl 1" << std::endl;
        #endif
        (yyval.fieldDeclListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-3].identifierList), (yyvsp[-1].typeNode));
    }
#line 2518 "out/parser.cpp"
    break;

  case 62: /* field_decl: name_list COLON type_decl  */
#line 994 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl 2" << std::endl;
        #endif
        (yyval.fieldDeclListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-2].identifierList), (yyvsp[0].typeNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2530 "out/parser.cpp"
    break;

  case 63: /* array_type_decl: ARRAY LB simple_type RB OF type_decl  */
#line 1004 "src/yacc.y"
                                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse array type" << std::endl;
        #endif

        if((yyvsp[-3].simpleTypeNode)->getRepresentation() == ast::SimpleTypeNode::Representation::CONST_RANGE) {
            ast::ConstRangeTypeNode* range = dynamic_cast<ast::ConstRangeTypeNode*>((yyvsp[-3].simpleTypeNode));
            ast::ConstantNode::ConstantType leftType = range->getLowerBound()->getConstantType();
            ast::ConstantNode::ConstantType rightType = range->getUpperBound()->getConstantType();
            if(leftType != rightType) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", array range bounds must have the same type");
                fatalError = true;
                YYERROR;
            }
            else if(leftType == ast::ConstantNode::STRING || rightType == ast::ConstantNode::STRING) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", array range bounds cannot be string");
                fatalError = true;
                YYERROR;
            }
        }

        (yyval.arrayTypeNode) = new ast::ArrayTypeNode((yyvsp[-3].simpleTypeNode), (yyvsp[0].typeNode));
    }
#line 2558 "out/parser.cpp"
    break;

  case 64: /* simple_type: identifier  */
#line 1030 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - identifier" << std::endl;
        #endif

        (yyval.simpleTypeNode) = new ast::RenameTypeNode((yyvsp[0].identifierNode));
    }
#line 2570 "out/parser.cpp"
    break;

  case 65: /* simple_type: LP name_list RP  */
#line 1038 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - parentheses" << std::endl;
        #endif

        (yyval.simpleTypeNode) = new ast::EnumerationTypeNode((yyvsp[-1].identifierList));
    }
#line 2582 "out/parser.cpp"
    break;

  case 66: /* simple_type: const_value DOUBLEDOT const_value  */
#line 1046 "src/yacc.y"
                                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - range 1" << std::endl;
        #endif

        (yyval.simpleTypeNode) = new ast::ConstRangeTypeNode((yyvsp[-2].constantNode), (yyvsp[0].constantNode));
    }
#line 2594 "out/parser.cpp"
    break;

  case 67: /* simple_type: identifier DOUBLEDOT identifier  */
#line 1054 "src/yacc.y"
                                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - range 4" << std::endl;
        #endif

        (yyval.simpleTypeNode) = new ast::VarRangeTypeNode((yyvsp[-2].identifierNode), (yyvsp[0].identifierNode));
    }
#line 2606 "out/parser.cpp"
    break;

  case 68: /* simple_type: INT_TYPE  */
#line 1062 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - int" << std::endl;
        #endif

        (yyval.simpleTypeNode) = new ast::BasicTypeNode(ast::BasicTypeNode::BasicType::INTEGER);
    }
#line 2618 "out/parser.cpp"
    break;

  case 69: /* simple_type: BOOL_TYPE  */
#line 1070 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - bool" << std::endl;
        #endif

        (yyval.simpleTypeNode) = new ast::BasicTypeNode(ast::BasicTypeNode::BasicType::BOOLEAN);
    }
#line 2630 "out/parser.cpp"
    break;

  case 70: /* simple_type: CHAR_TYPE  */
#line 1078 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - char" << std::endl;
        #endif

        (yyval.simpleTypeNode) = new ast::BasicTypeNode(ast::BasicTypeNode::BasicType::CHAR);
    }
#line 2642 "out/parser.cpp"
    break;

  case 71: /* name_list: name_list COMMA identifier  */
#line 1088 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse name list 1" << std::endl;
        #endif

        (yyval.identifierList) = (yyvsp[-2].identifierList);
        (yyval.identifierList)->push_back((yyvsp[0].identifierNode));
    }
#line 2655 "out/parser.cpp"
    break;

  case 72: /* name_list: identifier  */
#line 1097 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse name list 2" << std::endl;
        #endif

        (yyval.identifierList) = new std::vector<ast::IdentifierNode*>();
        (yyval.identifierList)->push_back((yyvsp[0].identifierNode));
    }
#line 2668 "out/parser.cpp"
    break;

  case 73: /* identifier: IDENT_NAME  */
#line 1108 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse identifier `" << (*(yyvsp[0].token).stringValue) << "`" << std::endl;
        #endif

        std::string name{*(yyvsp[0].token).stringValue};
        (yyval.identifierNode) = new ast::IdentifierNode(std::move(name));
    }
#line 2681 "out/parser.cpp"
    break;

  case 74: /* routine_body: compound_stmt  */
#line 1119 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine body" << std::endl;
        #endif

        (yyval.routineBodyNode) = new ast::RoutineBodyNode((yyvsp[0].compoundStatementNode));
    }
#line 2693 "out/parser.cpp"
    break;

  case 75: /* compound_stmt: BBEGIN stmt_list END  */
#line 1129 "src/yacc.y"
                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse compound statement 1" << std::endl;
        #endif

        (yyval.compoundStatementNode) = new ast::CompoundStatementNode((yyvsp[-1].statementNodeList));
    }
#line 2705 "out/parser.cpp"
    break;

  case 76: /* compound_stmt: BBEGIN stmt_list  */
#line 1137 "src/yacc.y"
                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse compound statement 2" << std::endl;
        #endif

        (yyval.compoundStatementNode) = new ast::CompoundStatementNode((yyvsp[0].statementNodeList));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of end");
    }
#line 2718 "out/parser.cpp"
    break;

  case 77: /* stmt_list: %empty  */
#line 1148 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty statement list" << std::endl;
        #endif

        (yyval.statementNodeList) = new std::vector<ast::StatementNode*>();
    }
#line 2730 "out/parser.cpp"
    break;

  case 78: /* stmt_list: stmt_list stmt SEMICOLON  */
#line 1156 "src/yacc.y"
                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement list 1" << std::endl;
        #endif

        (yyval.statementNodeList) = (yyvsp[-2].statementNodeList);
        (yyval.statementNodeList)->push_back((yyvsp[-1].statementNode));
    }
#line 2743 "out/parser.cpp"
    break;

  case 79: /* stmt_list: stmt_list stmt  */
#line 1165 "src/yacc.y"
                   {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement list 2" << std::endl;
        #endif

        (yyval.statementNodeList) = (yyvsp[-1].statementNodeList);
        (yyval.statementNodeList)->push_back((yyvsp[0].statementNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2757 "out/parser.cpp"
    break;

  case 80: /* stmt: INTEGER COLON no_label_stmt  */
#line 1177 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement with label " << (yyvsp[-2].token).numericalValue << std::endl;
        #endif

        (yyval.statementNode) = (yyvsp[0].statementNode);
        (yyval.statementNode)->setLabel((yyvsp[-2].token).numericalValue);
    }
#line 2770 "out/parser.cpp"
    break;

  case 81: /* stmt: no_label_stmt  */
#line 1186 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement without label" << std::endl;
        #endif

        (yyval.statementNode) = (yyvsp[0].statementNode);
    }
#line 2782 "out/parser.cpp"
    break;

  case 82: /* no_label_stmt: assign_stmt  */
#line 1196 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - assign" << std::endl;
        #endif

        (yyval.statementNode)=(yyvsp[0].assignNode);
    }
#line 2794 "out/parser.cpp"
    break;

  case 83: /* no_label_stmt: compound_stmt  */
#line 1204 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - compound" << std::endl;
        #endif

        (yyval.statementNode) = (yyvsp[0].compoundStatementNode);
    }
#line 2806 "out/parser.cpp"
    break;

  case 84: /* no_label_stmt: goto_stmt  */
#line 1212 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - goto" << std::endl;
        #endif

        (yyval.statementNode) = (yyvsp[0].gotoNode);
    }
#line 2818 "out/parser.cpp"
    break;

  case 85: /* no_label_stmt: if_stmt  */
#line 1220 "src/yacc.y"
            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - if" << std::endl;
        #endif

        (yyval.statementNode) = (yyvsp[0].ifNode);
    }
#line 2830 "out/parser.cpp"
    break;

  case 86: /* no_label_stmt: repeat_stmt  */
#line 1228 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - repeat" << std::endl;
        #endif

        (yyval.statementNode) = (yyvsp[0].repeatNode);
    }
#line 2842 "out/parser.cpp"
    break;

  case 87: /* no_label_stmt: while_stmt  */
#line 1236 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - while" << std::endl;
        #endif

        (yyval.statementNode) = (yyvsp[0].whileNode);
    }
#line 2854 "out/parser.cpp"
    break;

  case 88: /* no_label_stmt: case_stmt  */
#line 1244 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - case" << std::endl;
        #endif

        (yyval.statementNode) = (yyvsp[0].caseNode);
    }
#line 2866 "out/parser.cpp"
    break;

  case 89: /* no_label_stmt: for_stmt  */
#line 1252 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - for" << std::endl;
        #endif

        (yyval.statementNode) = (yyvsp[0].forNode);
    }
#line 2878 "out/parser.cpp"
    break;

  case 90: /* no_label_stmt: proc_stmt  */
#line 1260 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - proc" << std::endl;
        #endif

        (yyval.statementNode) = (yyvsp[0].callNode);
    }
#line 2890 "out/parser.cpp"
    break;

  case 91: /* no_label_stmt: BREAK  */
#line 1268 "src/yacc.y"
          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - break" << std::endl;
        #endif

        (yyval.statementNode) = new ast::BreakNode();
    }
#line 2902 "out/parser.cpp"
    break;

  case 92: /* no_label_stmt: CONTINUE  */
#line 1276 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - continue" << std::endl;
        #endif

        (yyval.statementNode) = new ast::ContinueNode();
    }
#line 2914 "out/parser.cpp"
    break;

  case 93: /* assign_stmt: lvalue ASSIGN expression  */
#line 1286 "src/yacc.y"
                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse assign statement" << std::endl;
        #endif

        if(!isLeftValueCompatible((yyvsp[-2].expressionNode))) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", left side of assignment must be assignable");
            fatalError = true;
            YYERROR;
        }
        else if((yyvsp[-2].expressionNode)->getInferredType() != (yyvsp[0].expressionNode)->getInferredType()) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", both sides should be equal type");
            fatalError = true;
            YYERROR;
        }
        else {
            (yyval.assignNode) = new ast::AssignNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode));
        }
    }
#line 2938 "out/parser.cpp"
    break;

  case 94: /* goto_stmt: GOTO INTEGER  */
#line 1308 "src/yacc.y"
                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse goto statement to " << (yyvsp[0].token).numericalValue << std::endl;
        #endif

        (yyval.gotoNode) = new ast::GotoNode((yyvsp[0].token).numericalValue);
    }
#line 2950 "out/parser.cpp"
    break;

  case 95: /* if_stmt: IF expression THEN stmt else_clause  */
#line 1318 "src/yacc.y"
                                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse if statement 1" << std::endl;
        #endif

        if((yyvsp[-3].expressionNode)->getInferredType() == "boolean") {
            (yyval.ifNode) = new ast::IfNode((yyvsp[-3].expressionNode), (yyvsp[-1].statementNode), (yyvsp[0].ifNode));
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", if condition must be boolean expression");
            fatalError = true;
            YYERROR;
        }
    }
#line 2969 "out/parser.cpp"
    break;

  case 96: /* if_stmt: IF expression stmt else_clause  */
#line 1333 "src/yacc.y"
                                   {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse if statement 2" << std::endl;
        #endif

        if((yyvsp[-2].expressionNode)->getInferredType() == "boolean") {
            (yyval.ifNode) = new ast::IfNode((yyvsp[-2].expressionNode), (yyvsp[-1].statementNode), (yyvsp[0].ifNode));
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of then");
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", if condition must be boolean expression");
            fatalError = true;
            YYERROR;
        }
    }
#line 2989 "out/parser.cpp"
    break;

  case 97: /* else_clause: %empty  */
#line 1351 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty else clause" << std::endl;
        #endif

        (yyval.ifNode) = new ast::IfNode(nullptr, nullptr);
    }
#line 3001 "out/parser.cpp"
    break;

  case 98: /* else_clause: ELSE stmt  */
#line 1359 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse else clause" << std::endl;
        #endif

        (yyval.ifNode) = new ast::IfNode(nullptr, nullptr, (yyvsp[0].statementNode));
    }
#line 3013 "out/parser.cpp"
    break;

  case 99: /* repeat_stmt: REPEAT stmt_list UNTIL expression  */
#line 1369 "src/yacc.y"
                                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse repeat statement" << std::endl;
        #endif

        if((yyvsp[0].expressionNode)->getInferredType() == "boolean") {
            (yyval.repeatNode) = new ast::RepeatNode((yyvsp[0].expressionNode), (yyvsp[-2].statementNodeList));
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", repeat condition must be boolean expression");
            fatalError = true;
            YYERROR;
        }
    }
#line 3032 "out/parser.cpp"
    break;

  case 100: /* repeat_stmt: %empty  */
#line 1384 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty repeat statement" << std::endl;
        #endif
    }
#line 3042 "out/parser.cpp"
    break;

  case 101: /* while_stmt: WHILE expression DO stmt  */
#line 1392 "src/yacc.y"
                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse while statement" << std::endl;
        #endif

        if((yyvsp[-2].expressionNode)->getInferredType() == "boolean") {
            (yyval.whileNode) = new ast::WhileNode((yyvsp[-2].expressionNode), (yyvsp[0].statementNode));
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", while condition must be boolean expression");
            fatalError = true;
            YYERROR;
        }
    }
#line 3061 "out/parser.cpp"
    break;

  case 102: /* case_stmt: CASE expression OF case_expr_list END  */
#line 1409 "src/yacc.y"
                                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case statement" << std::endl;
        #endif

        if(!isBasicType((yyvsp[-3].expressionNode)->getInferredType()) && (yyvsp[-3].expressionNode)->getInferredType().substr(0, 5) != "enum%") {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", case expression must be integer, char, boolean or enum type");
            fatalError = true;
            YYERROR;
        }

        bool otherwiseFound{false};
        for(const auto& caseExpr : *(yyvsp[-1].caseExprList)) {
            if(caseExpr->first != nullptr) {
                if(otherwiseFound) {
                    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", otherwise must be last label");
                    fatalError = true;
                    YYERROR;
                }

                if(caseExpr->first->getOperation() != ast::ExpressionNode::Operation::SPECIAL) {
                    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", case value must be constant");
                    fatalError = true;
                    YYERROR;
                }

                ast::SpecialExpressionNode* specialExpr = dynamic_cast<ast::SpecialExpressionNode*>(caseExpr->first);
                if(specialExpr->getFunctionName() != ast::SpecialExpressionNode::FunctionName::CONST &&
                    specialExpr->getFunctionName() != ast::SpecialExpressionNode::FunctionName::ENUM_ELEMENT) {
                    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", case value must be constant");
                    fatalError = true;
                    YYERROR;
                }

                if(specialExpr->getInferredType() != (yyvsp[-3].expressionNode)->getInferredType()) {
                    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", case expression must be the same type as case value");
                    fatalError = true;
                    YYERROR;
                }
            }
            else if(otherwiseFound) {
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
#line 3118 "out/parser.cpp"
    break;

  case 103: /* case_expr_list: case_expr_list case_expr  */
#line 1464 "src/yacc.y"
                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr list 1" << std::endl;
        #endif

        (yyval.caseExprList) = (yyvsp[-1].caseExprList);
        (yyval.caseExprList)->push_back((yyvsp[0].caseExpr));
    }
#line 3131 "out/parser.cpp"
    break;

  case 104: /* case_expr_list: case_expr  */
#line 1473 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr list 2" << std::endl;
        #endif

        (yyval.caseExprList) = new std::vector<std::pair<ast::ExpressionNode*, ast::StatementNode*>*>();
        (yyval.caseExprList)->push_back((yyvsp[0].caseExpr));
    }
#line 3144 "out/parser.cpp"
    break;

  case 105: /* case_expr: expression COLON stmt SEMICOLON  */
#line 1484 "src/yacc.y"
                                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr 1" << std::endl;
        #endif

        (yyval.caseExpr) = new std::pair<ast::ExpressionNode*, ast::StatementNode*>((yyvsp[-3].expressionNode), (yyvsp[-1].statementNode));
    }
#line 3156 "out/parser.cpp"
    break;

  case 106: /* case_expr: OTHERWISE stmt SEMICOLON  */
#line 1492 "src/yacc.y"
                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr 3" << std::endl;
        #endif

        (yyval.caseExpr) = new std::pair<ast::ExpressionNode*, ast::StatementNode*>(nullptr, (yyvsp[-1].statementNode));
    }
#line 3168 "out/parser.cpp"
    break;

  case 107: /* for_stmt: for_head stmt  */
#line 1502 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse for statement" << std::endl;
        #endif

        if(variableIsReassignedS((yyvsp[-1].forNode)->getIterator()->getName(), (yyvsp[0].statementNode))) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", loop variable `" + (yyvsp[-1].forNode)->getIterator()->getName() + "` cannot be reassigned");
            fatalError = true;
            YYERROR;
        }

        (yyval.forNode) = (yyvsp[-1].forNode);
        (yyval.forNode)->setStatements(std::unique_ptr<ast::StatementNode>((yyvsp[0].statementNode)));

        ctx->getLookupTable().unDefineVariable((yyvsp[-1].forNode)->getIterator()->getName());
    }
#line 3189 "out/parser.cpp"
    break;

  case 108: /* for_head: FOR identifier ASSIGN expression TO expression DO  */
#line 1521 "src/yacc.y"
                                                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse for head 1" << std::endl;
        #endif

        if((yyvsp[-3].expressionNode)->getInferredType() != (yyvsp[-1].expressionNode)->getInferredType()) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", for begin and end values must be the same type");
            fatalError = true;
            YYERROR;
        }
        else if(!isBasicType((yyvsp[-3].expressionNode)->getInferredType()) && (yyvsp[-3].expressionNode)->getInferredType().substr(0, 5) != "enum%") {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", for begin and end values must be integer, char, boolean or enum type");
            fatalError = true;
            YYERROR;
        }
        else {
            if(!saveVariables(new std::vector<ast::IdentifierNode*>{(yyvsp[-5].identifierNode)}, (yyvsp[-3].expressionNode)->getInferredType())) {
                YYERROR;
            }
            (yyval.forNode) = new ast::ForNode((yyvsp[-5].identifierNode), (yyvsp[-3].expressionNode), (yyvsp[-1].expressionNode), nullptr, ast::ForNode::Direction::INCREMENT);
        }
    }
#line 3216 "out/parser.cpp"
    break;

  case 109: /* for_head: FOR identifier ASSIGN expression DOWNTO expression DO  */
#line 1544 "src/yacc.y"
                                                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse for head 2" << std::endl;
        #endif

        if((yyvsp[-3].expressionNode)->getInferredType() != (yyvsp[-1].expressionNode)->getInferredType()) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", for begin and end values must be the same type");
            fatalError = true;
            YYERROR;
        }
        else if(!isBasicType((yyvsp[-3].expressionNode)->getInferredType()) && (yyvsp[-3].expressionNode)->getInferredType().substr(0, 5) != "enum%") {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", for begin and end values must be integer, char, boolean or enum type");
            fatalError = true;
            YYERROR;
        }
        else {
            if(!saveVariables(new std::vector<ast::IdentifierNode*>{(yyvsp[-5].identifierNode)}, (yyvsp[-3].expressionNode)->getInferredType())) {
                YYERROR;
            }
            (yyval.forNode) = new ast::ForNode((yyvsp[-5].identifierNode), (yyvsp[-3].expressionNode), (yyvsp[-1].expressionNode), nullptr, ast::ForNode::Direction::DECREMENT);
        }
    }
#line 3243 "out/parser.cpp"
    break;

  case 110: /* proc_stmt: identifier  */
#line 1569 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse procedure statement" << std::endl;
        #endif

        if(!ctx->getLookupTable().isRoutineDefined((yyvsp[0].identifierNode)->getName(), "")) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", routine `" + (yyvsp[0].identifierNode)->getName() + "` is not defined");
            fatalError = true;
            YYERROR;
        }
        else if(!ctx->getLookupTable().getRoutine((yyvsp[0].identifierNode)->getName(), "").args.empty()) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", missing arguments");
            fatalError = true;
            YYERROR;
        }
        else {
            (yyval.callNode) = new ast::UserDefineCallNode((yyvsp[0].identifierNode), nullptr);
        }
    }
#line 3267 "out/parser.cpp"
    break;

  case 111: /* proc_stmt: identifier LP args_list RP  */
#line 1589 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse procedure statement with args" << std::endl;
        #endif

        if(!ctx->getLookupTable().isRoutineDefined((yyvsp[-3].identifierNode)->getName(), "")) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", routine `" + (yyvsp[-3].identifierNode)->getName() + "` is not defined");
            fatalError = true;
            YYERROR;
        }
        else if(!isFunctionArgumentsCompatible(ctx->getLookupTable().getRoutine((yyvsp[-3].identifierNode)->getName(), "").args, (yyvsp[-1].argsList)->getArguments())) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", passed incompatible arguments");
            fatalError = true;
            YYERROR;
        }
        else {
            (yyval.callNode) = new ast::UserDefineCallNode((yyvsp[-3].identifierNode), (yyvsp[-1].argsList));
        }
    }
#line 3291 "out/parser.cpp"
    break;

  case 112: /* proc_stmt: READ LP factor RP  */
#line 1609 "src/yacc.y"
                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse read statement" << std::endl;
        #endif

        if(!isLeftValueCompatible((yyvsp[-1].expressionNode))) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for read - assignable argument expected");
            fatalError = true;
            YYERROR;
        }
        else if(!isBasicType((yyvsp[-1].expressionNode)->getInferredType())) {
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
#line 3317 "out/parser.cpp"
    break;

  case 113: /* proc_stmt: READLN  */
#line 1632 "src/yacc.y"
           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse readln statement" << std::endl;
        #endif

        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::READLN, nullptr);
    }
#line 3329 "out/parser.cpp"
    break;

  case 114: /* proc_stmt: WRITE LP args_list RP  */
#line 1640 "src/yacc.y"
                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse write statement" << std::endl;
        #endif

        bool allOk = true;
        for(auto arg : (yyvsp[-1].argsList)->getArguments()) {
            if(!isBasicType(arg->getInferredType()) && arg->getInferredType() != "string") {
                allOk = false;
                break;
            }
        }
        if(!allOk) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for write - integer, char, boolean or string expected");
            fatalError = true;
            YYERROR;
        }
        else {
            (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITE, (yyvsp[-1].argsList));
        }
    }
#line 3355 "out/parser.cpp"
    break;

  case 115: /* proc_stmt: WRITELN  */
#line 1662 "src/yacc.y"
            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse writeln statement" << std::endl;
        #endif

        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITELN, nullptr);
    }
#line 3367 "out/parser.cpp"
    break;

  case 116: /* proc_stmt: WRITELN LP args_list RP  */
#line 1670 "src/yacc.y"
                            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse writeln statement with args" << std::endl;
        #endif

        bool allOk = true;
        for(auto arg : (yyvsp[-1].argsList)->getArguments()) {
            if(!isBasicType(arg->getInferredType()) && arg->getInferredType() != "string") {
                allOk = false;
                break;
            }
        }

        if(!allOk) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for writeln - integer, char, boolean or string expected");
            fatalError = true;
            YYERROR;
        }
        else {
            (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITELN, (yyvsp[-1].argsList));
        }
    }
#line 3394 "out/parser.cpp"
    break;

  case 117: /* proc_stmt: MEMORYREAD LP args_list RP  */
#line 1693 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse memory read statement" << std::endl;
        #endif

        if((yyvsp[-1].argsList)->getArguments().size() == 3) {
            if((yyvsp[-1].argsList)->getArguments().at(0)->getInferredType() != "integer") {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory read - first argument should be integer");
                fatalError = true;
                YYERROR;
            }
            else if((yyvsp[-1].argsList)->getArguments().at(1)->getInferredType() != "integer") {
                 parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory read - second argument should be integer");
                 fatalError = true;
                 YYERROR;
            }
            else if(!isLeftValueCompatible((yyvsp[-1].argsList)->getArguments().at(2))) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory read - assignable argument expected");
                fatalError = true;
                YYERROR;
            }
            else if(!isBasicType((yyvsp[-1].argsList)->getArguments().at(2)->getInferredType())) {
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
#line 3435 "out/parser.cpp"
    break;

  case 118: /* proc_stmt: MEMORYWRITE LP args_list RP  */
#line 1730 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse memory write statement" << std::endl;
        #endif

        if((yyvsp[-1].argsList)->getArguments().size() == 3) {
            if((yyvsp[-1].argsList)->getArguments().at(0)->getInferredType() != "integer") {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory write - first argument should be integer");
                fatalError = true;
                YYERROR;
            }
            else if((yyvsp[-1].argsList)->getArguments().at(1)->getInferredType() != "integer") {
                 parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory write - second argument should be integer");
                 fatalError = true;
                 YYERROR;
            }
            else if(!isBasicType((yyvsp[-1].argsList)->getArguments().at(2)->getInferredType())) {
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
#line 3471 "out/parser.cpp"
    break;

  case 119: /* proc_stmt: STACKREAD LP args_list RP  */
#line 1762 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse stack read statement" << std::endl;
        #endif

        if((yyvsp[-1].argsList)->getArguments().size() == 3) {
            if((yyvsp[-1].argsList)->getArguments().at(0)->getInferredType() != "integer") {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack read - first argument should be integer");
                fatalError = true;
                YYERROR;
            }
            else if((yyvsp[-1].argsList)->getArguments().at(1)->getInferredType() != "integer") {
                 parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack read - second argument should be integer");
                 fatalError = true;
                 YYERROR;
            }
            else if(!isLeftValueCompatible((yyvsp[-1].argsList)->getArguments().at(2))) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack read - assignable argument expected");
                fatalError = true;
                YYERROR;
            }
            else if(!isBasicType((yyvsp[-1].argsList)->getArguments().at(2)->getInferredType())) {
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
#line 3512 "out/parser.cpp"
    break;

  case 120: /* proc_stmt: STACKWRITE LP args_list RP  */
#line 1799 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse stack write statement" << std::endl;
        #endif

        if((yyvsp[-1].argsList)->getArguments().size() == 3) {
            if((yyvsp[-1].argsList)->getArguments().at(0)->getInferredType() != "integer") {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack write - first argument should be integer");
                fatalError = true;
                YYERROR;
            }
            else if((yyvsp[-1].argsList)->getArguments().at(1)->getInferredType() != "integer") {
                 parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack write - second argument should be integer");
                 fatalError = true;
                 YYERROR;
            }
            else if(!isBasicType((yyvsp[-1].argsList)->getArguments().at(2)->getInferredType())) {
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
#line 3548 "out/parser.cpp"
    break;

  case 121: /* args_list: args_list COMMA expression  */
#line 1833 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse args list 1" << std::endl;
        #endif

        (yyval.argsList) = (yyvsp[-2].argsList);
        (yyval.argsList)->addArgument((yyvsp[0].expressionNode));
    }
#line 3561 "out/parser.cpp"
    break;

  case 122: /* args_list: expression  */
#line 1842 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse args list 2" << std::endl;
        #endif

        (yyval.argsList) = new ast::ArgumentsListNode();
        (yyval.argsList)->addArgument((yyvsp[0].expressionNode));
    }
#line 3574 "out/parser.cpp"
    break;

  case 123: /* expression: expression GE expr  */
#line 1853 "src/yacc.y"
                       {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with greater or equal" << std::endl;
        #endif

        if((yyvsp[-2].expressionNode)->getInferredType() == (yyvsp[0].expressionNode)->getInferredType() && isBasicType((yyvsp[-2].expressionNode)->getInferredType())) {
            (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::GREATER_EQUAL, "boolean");
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for greater or equal - matching types(integer, char, boolean) expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3593 "out/parser.cpp"
    break;

  case 124: /* expression: expression GT expr  */
#line 1868 "src/yacc.y"
                       {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with greater" << std::endl;
        #endif

        if((yyvsp[-2].expressionNode)->getInferredType() == (yyvsp[0].expressionNode)->getInferredType() && isBasicType((yyvsp[-2].expressionNode)->getInferredType())) {
            (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::GREATER, "boolean");
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for greater - matching types(integer, char, boolean) expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3612 "out/parser.cpp"
    break;

  case 125: /* expression: expression LE expr  */
#line 1883 "src/yacc.y"
                       {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with less or equal" << std::endl;
        #endif

        if((yyvsp[-2].expressionNode)->getInferredType() == (yyvsp[0].expressionNode)->getInferredType() && isBasicType((yyvsp[-2].expressionNode)->getInferredType())) {
            (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::LESS_EQUAL, "boolean");
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for less or equal - matching types(integer, char, boolean) expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3631 "out/parser.cpp"
    break;

  case 126: /* expression: expression LT expr  */
#line 1898 "src/yacc.y"
                       {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with less" << std::endl;
        #endif

        if((yyvsp[-2].expressionNode)->getInferredType() == (yyvsp[0].expressionNode)->getInferredType() && isBasicType((yyvsp[-2].expressionNode)->getInferredType())) {
            (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::LESS, "boolean");
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for less - matching types(integer, char, boolean) expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3650 "out/parser.cpp"
    break;

  case 127: /* expression: expression EQUAL expr  */
#line 1913 "src/yacc.y"
                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with equal" << std::endl;
        #endif

        if((yyvsp[-2].expressionNode)->getInferredType() == (yyvsp[0].expressionNode)->getInferredType() && isBasicType((yyvsp[-2].expressionNode)->getInferredType())) {
            (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::EQUAL, "boolean");
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for equal - matching types(integer, char, boolean) expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3669 "out/parser.cpp"
    break;

  case 128: /* expression: expression UNEQUAL expr  */
#line 1928 "src/yacc.y"
                            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with not equal" << std::endl;
        #endif

        if((yyvsp[-2].expressionNode)->getInferredType() == (yyvsp[0].expressionNode)->getInferredType() && isBasicType((yyvsp[-2].expressionNode)->getInferredType())) {
            (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::NOT_EQUAL, "boolean");
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for not equal - matching types(integer, char, boolean) expected");
            fatalError = true;
            YYERROR;
        }

    }
#line 3689 "out/parser.cpp"
    break;

  case 129: /* expression: expr  */
#line 1944 "src/yacc.y"
         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple expression" << std::endl;
        #endif
        (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 3700 "out/parser.cpp"
    break;

  case 130: /* expr: expr PLUS term  */
#line 1953 "src/yacc.y"
                   {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with addition" << std::endl;
        #endif

        if((yyvsp[-2].expressionNode)->getInferredType() == "integer" && (yyvsp[0].expressionNode)->getInferredType() == "integer") {
            (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::ADDITION, (yyvsp[-2].expressionNode)->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for addition - integer expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3719 "out/parser.cpp"
    break;

  case 131: /* expr: expr MINUS term  */
#line 1968 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with subtraction" << std::endl;
        #endif

        if((yyvsp[-2].expressionNode)->getInferredType() == "integer" && (yyvsp[0].expressionNode)->getInferredType() == "integer") {
            (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::SUBTRACTION, (yyvsp[-2].expressionNode)->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for subtraction - integer expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3738 "out/parser.cpp"
    break;

  case 132: /* expr: expr OR term  */
#line 1983 "src/yacc.y"
                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with or" << std::endl;
        #endif

        if((yyvsp[-2].expressionNode)->getInferredType() == "boolean" && (yyvsp[0].expressionNode)->getInferredType() == "boolean") {
            (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::OR, "boolean");
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for or - boolean expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3757 "out/parser.cpp"
    break;

  case 133: /* expr: term  */
#line 1998 "src/yacc.y"
         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple term" << std::endl;
        #endif

        (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 3769 "out/parser.cpp"
    break;

  case 134: /* term: term MUL factor  */
#line 2008 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with multiplication" << std::endl;
        #endif

        if((yyvsp[-2].expressionNode)->getInferredType() == "integer" && (yyvsp[0].expressionNode)->getInferredType() == "integer") {
            (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::MULTIPLICATION, (yyvsp[-2].expressionNode)->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for mul - integer expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3788 "out/parser.cpp"
    break;

  case 135: /* term: term DIV factor  */
#line 2023 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with division" << std::endl;
        #endif

        if((yyvsp[-2].expressionNode)->getInferredType() == "integer" && (yyvsp[0].expressionNode)->getInferredType() == "integer") {
            (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::DIVISION, (yyvsp[-2].expressionNode)->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for div - integer expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3807 "out/parser.cpp"
    break;

  case 136: /* term: term MOD factor  */
#line 2038 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with modulus" << std::endl;
        #endif

        if((yyvsp[-2].expressionNode)->getInferredType() == "integer" && (yyvsp[0].expressionNode)->getInferredType() == "integer") {
            (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::MODULUS, (yyvsp[-2].expressionNode)->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for mod - integer expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3826 "out/parser.cpp"
    break;

  case 137: /* term: term AND factor  */
#line 2053 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with and" << std::endl;
        #endif

        if((yyvsp[-2].expressionNode)->getInferredType() == "boolean" && (yyvsp[0].expressionNode)->getInferredType() == "boolean") {
            (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::AND, "boolean");
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for and - boolean expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3845 "out/parser.cpp"
    break;

  case 138: /* term: factor  */
#line 2068 "src/yacc.y"
           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple factor" << std::endl;
        #endif

        (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 3857 "out/parser.cpp"
    break;

  case 139: /* factor: identifier LP args_list RP  */
#line 2078 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - function call" << std::endl;
        #endif

        if(!ctx->getLookupTable().isRoutineDefined((yyvsp[-3].identifierNode)->getName(), "")) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", routine " + (yyvsp[-3].identifierNode)->getName() + " is not defined");
            fatalError = true;
            YYERROR;
        }
        else {
            (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-3].identifierNode), (yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::CALL, ctx->getLookupTable().getRoutine((yyvsp[-3].identifierNode)->getName(), "").type);
        }
    }
#line 3876 "out/parser.cpp"
    break;

  case 140: /* factor: lvalue  */
#line 2094 "src/yacc.y"
           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - lvalue" << std::endl;
        #endif

        (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 3888 "out/parser.cpp"
    break;

  case 141: /* factor: const_value  */
#line 2102 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - const value" << std::endl;
        #endif

        ast::ConstantNode* constant = dynamic_cast<ast::ConstantNode*>((yyvsp[0].constantNode));

        std::string constantType = getTypeString(constant->getConstantType());
        if(constantType == "undefined") {
            YYERROR;
        }

        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[0].constantNode), ast::SpecialExpressionNode::FunctionName::CONST, constantType);
    }
#line 3907 "out/parser.cpp"
    break;

  case 142: /* factor: LP expression RP  */
#line 2117 "src/yacc.y"
                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - parentheses" << std::endl;
        #endif

        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].expressionNode), ast::SpecialExpressionNode::FunctionName::PARENTHESIS, (yyvsp[-1].expressionNode)->getInferredType());
    }
#line 3919 "out/parser.cpp"
    break;

  case 143: /* factor: NOT factor  */
#line 2125 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - not" << std::endl;
        #endif

        if((yyvsp[0].expressionNode)->getInferredType() == "boolean") {
            (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::NEGATION, (yyvsp[0].expressionNode)->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for not - boolean expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3938 "out/parser.cpp"
    break;

  case 144: /* factor: MINUS factor  */
#line 2140 "src/yacc.y"
                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - negation" << std::endl;
        #endif

        if((yyvsp[0].expressionNode)->getInferredType() == "integer") {
            (yyval.expressionNode) = new ast::MathExpressionNode((yyvsp[0].expressionNode), ast::MathExpressionNode::FunctionName::NEGATION, (yyvsp[0].expressionNode)->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for negation - integer expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3957 "out/parser.cpp"
    break;

  case 145: /* factor: ABS LP args_list RP  */
#line 2155 "src/yacc.y"
                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - abs" << std::endl;
        #endif

        if((yyvsp[-1].argsList)->getArguments().size() != 1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for abs");
            fatalError = true;
            YYERROR;
        }
        else {
            ast::ExpressionNode* arg = (yyvsp[-1].argsList)->getArguments().front();
            if(arg->getInferredType() == "integer") {
                (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::ABS, "integer");
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for abs - integer expected");
                fatalError = true;
                YYERROR;
            }
        }
    }
#line 3984 "out/parser.cpp"
    break;

  case 146: /* factor: CHR LP args_list RP  */
#line 2178 "src/yacc.y"
                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - chr" << std::endl;
        #endif

        if((yyvsp[-1].argsList)->getArguments().size() != 1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for chr");
            fatalError = true;
            YYERROR;
        }
        else {
            ast::ExpressionNode* arg = (yyvsp[-1].argsList)->getArguments().front();
            if(arg->getInferredType() == "integer") {
                (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::CHR, "char");
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for chr - integer expected");
                fatalError = true;
                YYERROR;
            }
        }
    }
#line 4011 "out/parser.cpp"
    break;

  case 147: /* factor: ODD LP args_list RP  */
#line 2201 "src/yacc.y"
                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - odd" << std::endl;
        #endif

        if((yyvsp[-1].argsList)->getArguments().size() != 1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for odd");
            fatalError = true;
            YYERROR;
        }
        else {
            ast::ExpressionNode* arg = (yyvsp[-1].argsList)->getArguments().front();
            if(arg->getInferredType() == "integer") {
                (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::ODD, "boolean");
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for odd - integer expected");
                fatalError = true;
                YYERROR;
            }
        }
    }
#line 4038 "out/parser.cpp"
    break;

  case 148: /* factor: ORD LP args_list RP  */
#line 2224 "src/yacc.y"
                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - ord" << std::endl;
        #endif

        if((yyvsp[-1].argsList)->getArguments().size() != 1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for ord");
            fatalError = true;
            YYERROR;
        }
        else {
            ast::ExpressionNode* arg = (yyvsp[-1].argsList)->getArguments().front();
            if(arg->getInferredType() == "char") {
                (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::ORD, "integer");
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for ord - char expected");
                fatalError = true;
                YYERROR;
            }
        }
    }
#line 4065 "out/parser.cpp"
    break;

  case 149: /* factor: PRED LP args_list RP  */
#line 2247 "src/yacc.y"
                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - pred" << std::endl;
        #endif

        if((yyvsp[-1].argsList)->getArguments().size() != 1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for pred");
            fatalError = true;
            YYERROR;
        }
        else {
            ast::ExpressionNode* arg = (yyvsp[-1].argsList)->getArguments().front();
            if(arg->getInferredType() == "integer" || arg->getInferredType() == "char") {
                (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::PRED, arg->getInferredType());
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for pred - integer or char expected");
                fatalError = true;
                YYERROR;
            }
        }
    }
#line 4092 "out/parser.cpp"
    break;

  case 150: /* factor: SUCC LP args_list RP  */
#line 2270 "src/yacc.y"
                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - succ" << std::endl;
        #endif

        if((yyvsp[-1].argsList)->getArguments().size() != 1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for succ");
            fatalError = true;
            YYERROR;
        }
        else {
            ast::ExpressionNode* arg = (yyvsp[-1].argsList)->getArguments().front();
            if(arg->getInferredType() == "integer" || arg->getInferredType() == "char") {
                (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::SUCC, arg->getInferredType());
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for succ - integer or char expected");
                fatalError = true;
                YYERROR;
            }
        }
    }
#line 4119 "out/parser.cpp"
    break;

  case 151: /* factor: TOINT LP args_list RP  */
#line 2293 "src/yacc.y"
                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - toint" << std::endl;
        #endif

        if((yyvsp[-1].argsList)->getArguments().size() != 1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for toint");
            fatalError = true;
            YYERROR;
        }
        else {
            ast::ExpressionNode* arg = (yyvsp[-1].argsList)->getArguments().front();
            if(isBasicType(arg->getInferredType())) {
                (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::TOINT, "integer");
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for toint - basic type expected");
                fatalError = true;
                YYERROR;
            }
        }
    }
#line 4146 "out/parser.cpp"
    break;

  case 152: /* factor: TOCHAR LP args_list RP  */
#line 2316 "src/yacc.y"
                           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - tochar" << std::endl;
        #endif

        if((yyvsp[-1].argsList)->getArguments().size() != 1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for tochar");
            fatalError = true;
            YYERROR;
        }
        else {
            ast::ExpressionNode* arg = (yyvsp[-1].argsList)->getArguments().front();
            if(isBasicType(arg->getInferredType())) {
                (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::TOCHAR, "char");
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for tochar - basic type expected");
                fatalError = true;
                YYERROR;
            }
        }
    }
#line 4173 "out/parser.cpp"
    break;

  case 153: /* factor: TOBOOL LP args_list RP  */
#line 2339 "src/yacc.y"
                           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - tobool" << std::endl;
        #endif

        if((yyvsp[-1].argsList)->getArguments().size() != 1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for tobool");
            fatalError = true;
            YYERROR;
        }
        else {
            ast::ExpressionNode* arg = (yyvsp[-1].argsList)->getArguments().front();
            if(isBasicType(arg->getInferredType())) {
                (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::TOBOOL, "boolean");
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for tobool - basic type expected");
                fatalError = true;
                YYERROR;
            }
        }
    }
#line 4200 "out/parser.cpp"
    break;

  case 154: /* lvalue: identifier  */
#line 2364 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse lvalue - variable" << std::endl;
        #endif

        if(ctx->getLookupTable().isVariableDefined((yyvsp[0].identifierNode)->getName(), "")) {
            (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[0].identifierNode), ast::SpecialExpressionNode::FunctionName::VARIABLE, ctx->getLookupTable().getVariable((yyvsp[0].identifierNode)->getName(), "").type);
        }
        else if(isInAnyEnum((yyvsp[0].identifierNode)->getName())) {
            auto properEnums = ctx->getLookupTable().getTypes(
            [&](const std::string&, const LookupTable::TypeInfo& tf) {
                return tf.alive && tf.type.find("enum%") == 0 && tf.type.find("%" + (yyvsp[0].identifierNode)->getName() + "%") != std::string::npos;
            });

            if(properEnums.size() != 1) {
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
#line 4233 "out/parser.cpp"
    break;

  case 155: /* lvalue: identifier LB expression RB  */
#line 2393 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse lvalue - simple array access" << std::endl;
        #endif

        if(!ctx->getLookupTable().isVariableDefined((yyvsp[-3].identifierNode)->getName(), "")) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", variable " + (yyvsp[-3].identifierNode)->getName() + " is not defined");
            fatalError = true;
            YYERROR;
        }
        else if(!isArrayIndexCompatible(ctx->getLookupTable().getVariable((yyvsp[-3].identifierNode)->getName(), "").type, (yyvsp[-1].expressionNode))) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", incorrect index type");
            fatalError = true;
            YYERROR;
        }
        else {
            (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-3].identifierNode), ast::SpecialExpressionNode::FunctionName::ARRAY_ACCESS,
                getArrayElementType(ctx->getLookupTable().getVariable((yyvsp[-3].identifierNode)->getName(), "").type));
        }
    }
#line 4258 "out/parser.cpp"
    break;

  case 156: /* lvalue: lvalue LB expression RB  */
#line 2414 "src/yacc.y"
                            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse lvalue - complex array access" << std::endl;
        #endif

        if((yyvsp[-3].expressionNode)->getInferredType().substr(0,5) != "array") {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", array type expected");
            fatalError = true;
            YYERROR;
        }
        else if(!isArrayIndexCompatible((yyvsp[-3].expressionNode)->getInferredType(), (yyvsp[-1].expressionNode))) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", incorrect index type");
            fatalError = true;
            YYERROR;
        }
        else {
            (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-3].expressionNode), (yyvsp[-1].expressionNode), ast::SpecialExpressionNode::FunctionName::ARRAY_ACCESS,
                getArrayElementType((yyvsp[-3].expressionNode)->getInferredType()));
        }
    }
#line 4283 "out/parser.cpp"
    break;

  case 157: /* lvalue: identifier DOT identifier  */
#line 2435 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse lvalue - simple record field" << std::endl;
        #endif

        if(ctx->getLookupTable().isVariableDefined((yyvsp[-2].identifierNode)->getName(), "") && isRecordFieldCompatible(ctx->getLookupTable().getVariable((yyvsp[-2].identifierNode)->getName(), "").type, (yyvsp[0].identifierNode))) {
            (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-2].identifierNode), ast::SpecialExpressionNode::FunctionName::RECORD_ACCESS,
                getRecordFieldType(ctx->getLookupTable().getVariable((yyvsp[-2].identifierNode)->getName(), "").type, (yyvsp[0].identifierNode)->getName()));
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", variable " + (yyvsp[-2].identifierNode)->getName() + " is not defined");
            fatalError = true;
            YYERROR;
        }
    }
#line 4303 "out/parser.cpp"
    break;

  case 158: /* lvalue: lvalue DOT identifier  */
#line 2451 "src/yacc.y"
                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse lvalue - complex record field" << std::endl;
        #endif

        if((yyvsp[-2].expressionNode)->getInferredType().substr(0,6) == "record" && isRecordFieldCompatible((yyvsp[-2].expressionNode)->getInferredType(), (yyvsp[0].identifierNode))) {
            (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].identifierNode), ast::SpecialExpressionNode::FunctionName::RECORD_ACCESS,
            getRecordFieldType((yyvsp[-2].expressionNode)->getInferredType(), (yyvsp[0].identifierNode)->getName()));
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", record type expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 4323 "out/parser.cpp"
    break;


#line 4327 "out/parser.cpp"

      default: break;
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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
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
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

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
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 2467 "src/yacc.y"


void yyerror(const char *s) {
    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + s);
    fatalError = true;
}

bool parse(const std::string& inputFileName, std::vector<std::string>& errors, std::unique_ptr<ast::ProgramNode>& program) {
    yyin = fopen(inputFileName.c_str(), "r");

    if(yyin == nullptr) {
        errors.push_back("Cannot open file `" + inputFileName + "`");
        return false;
    }

    yyparse();
    fclose(yyin);

    errors = std::move(parsingErrors);
    program = std::unique_ptr<ast::ProgramNode>(resultAst);
    return !fatalError;
}

bool isChar(const std::string& expr) {
    return expr.size() == 1;
}

bool isInteger(const std::string& expr) {
    return std::all_of(expr.begin(), expr.end(), ::isdigit) ||
        (expr.size() > 1 && expr[0] == '-' && std::all_of(expr.begin() + 1, expr.end(), ::isdigit));
}

bool isBoolean(const std::string& expr) {
    return expr == "true" || expr == "false";
}

bool nameAlreadyUsed(std::string name) {
    if(ctx->getLookupTable().isVariableDefined(name, "") || ctx->getLookupTable().isRoutineDefined(name, "") || ctx->getLookupTable().isTypeDefined(name, "")) {
        return true;
    }

    if(isInAnyEnum(name)) {
        return true;
    }

    return false;
}

bool saveType(ast::IdentifierNode* typeName, const std::string& typeDef) {
    if(nameAlreadyUsed(typeName->getName())) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", name `" + typeName->getName() + "` already used");
        fatalError = true;
        return false;
    } else {
        ctx->getLookupTable().defineType(LookupTable::TypeCategory::SIMPLE, typeName->getName(), typeDef);
        return true;
    }
}

bool saveConstant(ast::IdentifierNode* constName, const std::string& constValue, const std::string& typeDef) {
    if(nameAlreadyUsed(constName->getName())) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", name `" + constName->getName() + "` already used");
        fatalError = true;
        return false;
    } else {
        ctx->getLookupTable().defineVariable(LookupTable::VariableCategory::CONSTANT, constName->getName(), typeDef);
        ctx->getLookupTable().setVariableValue(constName->getName(), constValue);
        return true;
    }
}

bool saveVariables(std::vector<ast::IdentifierNode*>* varNames, const std::string& typeDef) {
    for(auto& varName : *varNames) {
        if(nameAlreadyUsed(varName->getName())) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", name `" + varName->getName() + "` already used");
            fatalError = true;
            return false;
        } else {
            ctx->getLookupTable().defineVariable(LookupTable::VariableCategory::VARIABLE, varName->getName(), typeDef);
        }
    }

    return true;
}

bool saveRoutine(ast::RoutineDeclarationNode* routineDef, bool isForward) {
    if(isForward) {
      if(nameAlreadyUsed(routineDef->getName())) {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", name `" + routineDef->getName() + "` already used");
          fatalError = true;
          return false;
      }

      for(const auto& paramGroup : *routineDef->getParams()->getParams()) {
          for(const auto& param : *paramGroup->getParams()) {
              if(nameAlreadyUsed(param->getName())) {
                  parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", name `" + param->getName() + "` already used");
                  fatalError = true;
                  return false;
              }
          }
      }
    }

    std::vector<LookupTable::ArgumentInfo> arguments;
    for(const auto& paramGroup : *routineDef->getParams()->getParams()) {
        std::string typeString = getTypeString(paramGroup->getParamsType().get());
        if(typeString == "unspecified") {
            return false;
        }

        for(const auto& param : *paramGroup->getParams()) {
            arguments.emplace_back(param->getName(), typeString, paramGroup->getPassType() == ast::ParamsGroupNode::PassType::PASS_BY_REFERENCE ? true : false);
        }
    }

    if(routineDef->getRoutineType() == ast::RoutineDeclarationNode::RoutineType::PROCEDURE) {
        ctx->getLookupTable().defineRoutine(LookupTable::RoutineCategory::PROCEDURE, routineDef->getName(),
            arguments, "void", "");
    }
    else {
        std::string returnType = getTypeString(routineDef->getReturnType().get());
        if(returnType == "unspecified") {
            return false;
        }

        ctx->getLookupTable().defineRoutine(LookupTable::RoutineCategory::FUNCTION, routineDef->getName(),
            arguments, returnType, "");
    }

    return true;
}

std::string getTypeString(ast::TypeNode* type) {
    if(type->getTypeType() == ast::TypeNode::TypeType::SIMPLE) {
        auto* simpleType = dynamic_cast<ast::SimpleTypeNode*>(type);
        switch(simpleType->getRepresentation()) {
            case ast::SimpleTypeNode::Representation::BASIC: {
                auto* basicType = dynamic_cast<ast::BasicTypeNode*>(simpleType);
                switch(basicType->getBasicType()) {
                    case ast::BasicTypeNode::BasicType::INTEGER:
                        return "integer";
                    case ast::BasicTypeNode::BasicType::BOOLEAN:
                        return "boolean";
                    case ast::BasicTypeNode::BasicType::CHAR:
                        return "char";
                    case ast::BasicTypeNode::BasicType::STRING:
                        return "string";
                }
            }
            case ast::SimpleTypeNode::Representation::RENAMING: {
                auto* renamingType = dynamic_cast<ast::RenameTypeNode*>(type);
                if(!ctx->getLookupTable().isTypeDefined(renamingType->getIdentifier()->getName(), "")) {
                    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", unknown type `" + renamingType->getIdentifier()->getName() + "`");
                    fatalError = true;
                    return "unspecified";
                }
                return ctx->getLookupTable().getType(renamingType->getIdentifier()->getName(), "").type;
             }
            case ast::SimpleTypeNode::Representation::ENUMERATION: {
                auto* enumType = dynamic_cast<ast::EnumerationTypeNode*>(type);
                std::string mergedEnum = "enum%";
                for(auto& identifier : *enumType->getIdentifiers()) {
                    mergedEnum += identifier->getName() + "%";
                }
                return mergedEnum;
            }
            case ast::SimpleTypeNode::Representation::CONST_RANGE: {
                auto* rangeType = dynamic_cast<ast::ConstRangeTypeNode*>(type);
                return "constrange%" + getConstantString(rangeType->getLowerBound().get()) + ".." + getConstantString(rangeType->getUpperBound().get());
            }
            case ast::SimpleTypeNode::Representation::VAR_RANGE: {
                auto* rangeType = dynamic_cast<ast::VarRangeTypeNode*>(type);
                std::string lb = rangeType->getLowerBound()->getName();
                std::string ub = rangeType->getUpperBound()->getName();

                auto properEnums = ctx->getLookupTable().getTypes(
                [&](const std::string&, const LookupTable::TypeInfo& tf) {
                    return tf.alive && tf.type.find("enum%") == 0 && tf.type.find("%" + lb + "%") != std::string::npos && tf.type.find("%" + ub + "%") != std::string::npos;
                });

                if(properEnums.empty()) {
                    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + lb + " and " + ub + " are not in any enum");
                    fatalError = true;
                    return "unspecified";
                }
                else if(properEnums.size() > 1) {
                    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + lb + " and " + ub + " are in more than one enum");
                    fatalError = true;
                    return "unspecified";
                }

                return "enumrange%" + properEnums.front().name + "%"  + lb + ".." + ub;
            }
            default:
                return "unspecified";
        }
    }
    else if(type->getTypeType() == ast::TypeNode::TypeType::ARRAY) {
        auto* arrayType = dynamic_cast<ast::ArrayTypeNode*>(type);

        std::string elementTypeName = getTypeString(arrayType->getElementType().get());
        std::string rangeTypeName = getTypeString(arrayType->getRange().get());

        if(elementTypeName == "unspecified" || rangeTypeName == "unspecified") {
            return "unspecified";
        }

        return "array@@" + rangeTypeName + "@" + elementTypeName + "@@";
    }
    else if(type->getTypeType() == ast::TypeNode::TypeType::RECORD) {
        auto* recordType = dynamic_cast<ast::RecordTypeNode*>(type);

        std::string mergedRecord = "record"  "$$";
        for(auto& field : *recordType->getFields()) {
            for(auto& identifier : *field->first) {
                if(getTypeString(field->second) == "unspecified") {
                    return "unspecified";
                }

                mergedRecord += identifier->getName() + "#(" + getTypeString(field->second) + ")$";
            }
        }

        return mergedRecord + "$";
    }
    else {
        return "unspecified";
    }
}

std::string getTypeString(ast::ConstantNode::ConstantType type) {
    switch(type) {
        case ast::ConstantNode::ConstantType::INTEGER:
            return "integer";
        case ast::ConstantNode::ConstantType::BOOLEAN:
            return "boolean";
        case ast::ConstantNode::ConstantType::CHAR:
            return "char";
        case ast::ConstantNode::ConstantType::STRING:
            return "string";
        default:
            return "unspecified";
    }
}

std::string getConstantString(ast::ConstantNode* constant) {
    if(constant->getConstantType() == ast::ConstantNode::ConstantType::INTEGER) {
        auto* intConst = dynamic_cast<ast::IntegerConstantNode*>(constant);
        return std::to_string(intConst->getValue());
    } else if(constant->getConstantType() == ast::ConstantNode::ConstantType::BOOLEAN) {
        auto* boolConst = dynamic_cast<ast::BooleanConstantNode*>(constant);
        return boolConst->getValue() ? "true" : "false";
    } else if(constant->getConstantType() == ast::ConstantNode::ConstantType::CHAR) {
        auto* charConst = dynamic_cast<ast::CharConstantNode*>(constant);
        return std::string(1, charConst->getValue());
    }
    else if(constant->getConstantType() == ast::ConstantNode::ConstantType::STRING) {
        auto* stringConst = dynamic_cast<ast::StringConstantNode*>(constant);
        return stringConst->getValue();
    }
    else {
        return "unspecified";
    }
}

bool isBasicType(const std::string& type) {
    return type == "integer" || type == "boolean" || type == "char";
}

bool isInEnum(const std::string& enumElement, const std::string& enumType) {
    return enumType.find(enumElement) != std::string::npos;
}

bool isInAnyEnum(const std::string& enumElement) {
    const std::vector<LookupTable::TypeInfo>& types = ctx->getLookupTable().getTypes(
        [&](const std::string&, const LookupTable::TypeInfo& tf) {
        return tf.alive && tf.type.find("enum%") == 0 && tf.type.find("%" + enumElement + "%") != std::string::npos;
    });

    return !types.empty();
}

bool isEnumSubRangeType(const std::string& enumElement, const std::string& enumType,
    const std::string& begin, const std::string& end) {
    size_t beginPos = enumType.find("%" + begin + "%");
    size_t endPos = enumType.find("%" + end + "%");
    size_t enumElementPos = enumType.find("%" + enumElement + "%");

    return beginPos != std::string::npos && endPos != std::string::npos && enumElementPos != std::string::npos &&
        beginPos <= enumElementPos && enumElementPos <= endPos;
}

bool isLeftValueCompatible(ast::ExpressionNode* expr) {
    if(expr->getOperation() != ast::ExpressionNode::Operation::SPECIAL) {
        return false;
    }

    ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(expr);
    if(special->getFunctionName() == ast::SpecialExpressionNode::VARIABLE ||
       special->getFunctionName() == ast::SpecialExpressionNode::ARRAY_ACCESS ||
       special->getFunctionName() == ast::SpecialExpressionNode::RECORD_ACCESS) {
        return true;
    }

    return false;
}

bool isArrayIndexCompatible(const std::string& arrayType, ast::ExpressionNode* index) {
    std::string arrayElementType{};
    size_t it{7};
    while(arrayType[it] != '@' && it < arrayType.size()) {
        arrayElementType += arrayType[it];
        it++;
    }

    if(arrayElementType == "integer") {
        if(index->getInferredType() == "integer") {
            return true;
        }
        return false;
    }
    else if(arrayElementType == "char") {
        if(index->getInferredType() == "char") {
            return true;
        }
        return false;
    }
    else if(arrayElementType == "boolean") {
        if(index->getInferredType() == "boolean") {
            return true;
        }
        return false;
    }
    else if(arrayElementType.substr(0, 10) == "constrange") {
        std::string begin{};
        std::string end{};
        size_t pos;
        for(pos = 11; pos < arrayElementType.size(); pos++) {
            if(arrayElementType[pos] == '.') {
                break;
            }
            begin += arrayElementType[pos];
        }

        for(pos += 2; pos < arrayElementType.size(); pos++) {
            end += arrayElementType[pos];
        }

        if(isInteger(begin) && isInteger(end)) {
            if(index->getInferredType() == "integer") {
                return true;
            }
        }
        else if(isChar(begin) && isChar(end)) {
            if(index->getInferredType() == "char") {
                return true;
            }
        }
        else if(isBoolean(begin) && isBoolean(end)) {
            if(index->getInferredType() == "boolean") {
                return true;
            }
        }

        return false;
    }
    else if(arrayElementType.substr(0, 9) == "enumrange") {
        std::string enumName, beginEnum, endEnum;
        size_t pos{10};
        for(; pos < arrayElementType.size(); pos++) {
            if(arrayElementType[pos] == '%') {
                break;
            }
            enumName += arrayElementType[pos];
        }

        pos++;
        while(arrayElementType[pos] != '.') {
            beginEnum += arrayElementType[pos];
            pos++;
        }

        pos += 2;
        for(; pos < arrayElementType.size(); pos++) {
            endEnum += arrayElementType[pos];
        }

        if(index->getOperation() == ast::ExpressionNode::Operation::SPECIAL) {
            ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(index);
            if(special->getFunctionName() == ast::SpecialExpressionNode::ENUM_ELEMENT) {
                ast::IdentifierNode* enumElement = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
                return isEnumSubRangeType(enumElement->getName(), ctx->getLookupTable().getType(enumName, "").type, beginEnum, endEnum);
            }
        }

        return false;
    }
    else if(arrayElementType.substr(0, 4) == "enum") {
        if(index->getOperation() == ast::ExpressionNode::Operation::SPECIAL) {
            ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(index);
            if(special->getFunctionName() == ast::SpecialExpressionNode::ENUM_ELEMENT) {
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
    size_t parenthesisCounter{};
    for(size_t i = 0; i < recordType.size(); i++) {
        if(recordType[i] == '(') {
            parenthesisCounter++;
        }
        else if(recordType[i] == ')') {
            parenthesisCounter--;
        }
        if(parenthesisCounter == 0) {
            if(recordType.substr(i, fieldName.size()) == fieldName) {
                return true;
            }
        }
    }
    return false;
}

bool isFunctionArgumentsCompatible(const std::vector<LookupTable::ArgumentInfo>& expectedArgs, const std::vector<ast::ExpressionNode*>& givenArgs) {
    if(expectedArgs.size() != givenArgs.size()) {
        return false;
    }

    for(size_t i = 0; i < expectedArgs.size(); i++) {
        if(expectedArgs[i].type != givenArgs[i]->getInferredType()) {
            return false;
        }
        if(expectedArgs[i].isReference && !isLeftValueCompatible(givenArgs[i])) {
            return false;
        }
    }

    return true;
}

bool hasReturnValue(ast::RoutineNode* function, const std::string& functionName) {
    std::vector<ast::StatementNode*>* statements = function->getBody()->getStatements()->getStatements().get();
    if(statements->empty()) {
        std::cout << "Empty function body\n";
        return false;
    }

    size_t returnCounter{0};
    size_t lastStatementIndex{0};
    for(size_t i = 0; i < statements->size(); i++) {
        if(statements->at(i)->getCategory() != ast::StatementNode::Category::ASSIGN) {
            continue;
        }

        ast::ExpressionNode* lhs = dynamic_cast<ast::AssignNode*>(statements->at(i))->getLhs().get();
        if(lhs->getOperation() != ast::ExpressionNode::Operation::SPECIAL) {
            continue;
        }

        ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(lhs);
        if(special->getFunctionName() != ast::SpecialExpressionNode::VARIABLE) {
            continue;
        }

        ast::IdentifierNode* variable = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
        if(variable->getName() == functionName) {
            returnCounter++;
            lastStatementIndex = i;
        }
    }

    if(returnCounter != 1) {
        return false;
    }

    return lastStatementIndex == statements->size() - 1;
}

bool variableIsReassignedS(const std::string& varName, ast::StatementNode* stmt) {
    switch(stmt->getCategory()) {
        case ast::StatementNode::Category::BREAK:
        case ast::StatementNode::Category::CONTINUE:
        case ast::StatementNode::Category::GOTO:
            return false;
        case ast::StatementNode::Category::ASSIGN: {
            ast::ExpressionNode* rhs = dynamic_cast<ast::AssignNode*>(stmt)->getRhs().get();
            if(variableIsReassignedE(varName, rhs)) {
                return true;
            }

            ast::ExpressionNode* lhs = dynamic_cast<ast::AssignNode*>(stmt)->getLhs().get();
            if(lhs->getOperation() != ast::ExpressionNode::Operation::SPECIAL) {
                return false;
            }

            ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(lhs);
            if(special->getFunctionName() != ast::SpecialExpressionNode::VARIABLE) {
                return false;
            }

            ast::IdentifierNode* variable = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
            return variable->getName() == varName;
        }
        case ast::StatementNode::Category::CALL: {
            ast::CallNode* call = dynamic_cast<ast::CallNode*>(stmt);

            if(call->getCallObjectType() == ast::CallNode::CallObjectType::USER_DEFINED) {
                ast::UserDefineCallNode* userCall = dynamic_cast<ast::UserDefineCallNode*>(call);
                const std::vector<LookupTable::ArgumentInfo>& callArgs = ctx->getLookupTable().getRoutine(userCall->getName()->getName(), "").args;
                std::vector<bool> passByReference;
                for(size_t i = 0; i < callArgs.size(); i++) {
                    passByReference.push_back(callArgs[i].isReference);
                }

                size_t index{0};
                for(auto arg : userCall->getArguments()->getArguments()) {
                    if(arg->getOperation() == ast::ExpressionNode::Operation::SPECIAL) {
                        ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(arg);
                        if(special->getFunctionName() == ast::SpecialExpressionNode::VARIABLE) {
                            ast::IdentifierNode* variable = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
                            if(variable->getName() == varName && passByReference[index]) {
                                return true;
                            }
                        }
                        else if(variableIsReassignedE(varName, arg)) {
                            return true;
                        }
                    }
                    else if(variableIsReassignedE(varName, arg)) {
                        return true;
                    }
                    index++;
                }
                return false;
            }
            else {
                ast::BuiltinCallNode* builtinCall = dynamic_cast<ast::BuiltinCallNode*>(call);
                if(builtinCall->getArguments() == nullptr) {
                    return false;
                }
                auto args = builtinCall->getArguments()->getArguments();

                if(builtinCall->getFunctionName() == ast::BuiltinCallNode::FunctionName::READ) {
                    if(args.front()->getOperation() == ast::ExpressionNode::Operation::SPECIAL) {
                        ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(args.front());
                        if(special->getFunctionName() == ast::SpecialExpressionNode::VARIABLE) {
                            ast::IdentifierNode* variable = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
                            return variable->getName() == varName;
                        }
                    }
                }
                if(builtinCall->getFunctionName() == ast::BuiltinCallNode::FunctionName::MEMORY_READ) {
                    if(args.back()->getOperation() == ast::ExpressionNode::Operation::SPECIAL) {
                        ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(args.back());
                        if(special->getFunctionName() == ast::SpecialExpressionNode::VARIABLE) {
                            ast::IdentifierNode* variable = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
                            return variable->getName() == varName;
                        }
                    }
                }
                if(builtinCall->getFunctionName() == ast::BuiltinCallNode::FunctionName::STACK_READ) {
                    if(args.back()->getOperation() == ast::ExpressionNode::Operation::SPECIAL) {
                        ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(args.back());
                        if(special->getFunctionName() == ast::SpecialExpressionNode::VARIABLE) {
                            ast::IdentifierNode* variable = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
                            return variable->getName() == varName;
                        }
                    }
                }

                return false;
            }
        }
        case ast::StatementNode::Category::CASE: {
            for(auto caseStatement: *dynamic_cast<ast::CaseNode*>(stmt)->getStatements()) {
                if(caseStatement->first->getType() == ast::AstNode::Type::EXPRESSION) {
                    if(variableIsReassignedE(varName, dynamic_cast<ast::ExpressionNode*>(caseStatement->first))) {
                        return true;
                    }
                }

                if(variableIsReassignedS(varName, caseStatement->second)) {
                    return true;
                }
            }
            return false;
        }
        case ast::StatementNode::Category::COMPOUND: {
            for(auto statement : *dynamic_cast<ast::CompoundStatementNode*>(stmt)->getStatements()) {
                if(variableIsReassignedS(varName, statement)) {
                    return true;
                }
            }
            return false;
        }
        case ast::StatementNode::Category::FOR: {
            if(variableIsReassignedE(varName, dynamic_cast<ast::ForNode*>(stmt)->getStart().get())) {
                return true;
            }
            if(variableIsReassignedE(varName, dynamic_cast<ast::ForNode*>(stmt)->getEnd().get())) {
                return true;
            }
            if(variableIsReassignedS(varName, dynamic_cast<ast::ForNode*>(stmt)->getStatements().get())) {
                return true;
            }

            return false;
        }
        case ast::StatementNode::Category::IF: {
            if(variableIsReassignedE(varName, dynamic_cast<ast::IfNode*>(stmt)->getCondition().get())) {
                return true;
            }
            if(variableIsReassignedS(varName, dynamic_cast<ast::IfNode*>(stmt)->getThenStatement().get())) {
                return true;
            }
            if(dynamic_cast<ast::IfNode*>(stmt)->getElseStatement().get() != nullptr
                && variableIsReassignedS(varName, dynamic_cast<ast::IfNode*>(stmt)->getElseStatement().get())) {
                return true;
            }

            return false;
        }
        case ast::StatementNode::Category::REPEAT: {
            if(variableIsReassignedE(varName, dynamic_cast<ast::RepeatNode*>(stmt)->getCondition().get())) {
                return true;
            }

            for(auto& statement : *dynamic_cast<ast::RepeatNode*>(stmt)->getStatements()) {
                if(variableIsReassignedS(varName, statement)) {
                    return true;
                }
            }

            return false;
        }
        case ast::StatementNode::Category::WHILE: {
            if(variableIsReassignedE(varName, dynamic_cast<ast::WhileNode*>(stmt)->getCondition().get())) {
                return true;
            }

            if(variableIsReassignedS(varName, dynamic_cast<ast::WhileNode*>(stmt)->getStatements().get())) {
                return true;
            }

            return false;
        }
        default:
            return false;
    }
}

bool variableIsReassignedE(const std::string& varName, ast::ExpressionNode* expr) {
    if(expr->getOperation() != ast::ExpressionNode::Operation::SPECIAL) {
        return false;
    }

    ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(expr);
    if(special->getFunctionName() == ast::SpecialExpressionNode::CALL) {
        auto routineName = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get())->getName();
        auto args = dynamic_cast<ast::ArgumentsListNode*>(special->getArgument2().get())->getArguments();

        const std::vector<LookupTable::ArgumentInfo>& callArgs = ctx->getLookupTable().getRoutine(routineName, "").args;
        std::vector<bool> passByReference;
        for(size_t i = 0; i < callArgs.size(); i++) {
            passByReference.push_back(callArgs[i].isReference);
        }

        size_t index{0};
        for(auto arg : args) {
            if(arg->getOperation() == ast::ExpressionNode::Operation::SPECIAL) {
                ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(arg);
                if(special->getFunctionName() == ast::SpecialExpressionNode::VARIABLE) {
                    ast::IdentifierNode* variable = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
                    if(variable->getName() == varName && passByReference[index]) {
                        return true;
                    }
                }
                else if(variableIsReassignedE(varName, arg)) {
                    return true;
                }
            }
            else if(variableIsReassignedE(varName, arg)) {
                return true;
            }
            index++;
        }
    }

    return false;
}

std::string getArrayElementType(const std::string& arrayType) {
    std::string elementType{};
    size_t counter{0};
    for(auto it = arrayType.begin(); it != (arrayType.end() - 2); ++it) {
        if(counter >= 3) {
            elementType += (*it);
        }
        else if(*it == '@') {
            counter++;
        }
    }
    return elementType;
}

std::string getRecordFieldType(const std::string& recordType, const std::string& field) {
    std::size_t it = recordType.find("$" + field + "#") + field.size() + 3;
    std::string fieldType{};
    size_t parenthesisCounter{1};
    while(parenthesisCounter != 0) {
        if(recordType[it] == '(') {
            parenthesisCounter++;
        }
        else if(recordType[it] == ')') {
            parenthesisCounter--;
        }
        fieldType += recordType[it];
        it++;
    }

    return fieldType.substr(0, fieldType.size()-1);
}
