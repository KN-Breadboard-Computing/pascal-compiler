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
#include <utility>

#include "../src/ast/program_node.hpp"
#include "../src/context.hpp"

#undef YACC_DEBUG

Context* ctx = Context::getInstance();

ast::ProgramNode* resultAst;
std::vector<std::string> parsingErrors;
bool fatalError = false;

static void yyerror(const char *msg);
static int yyparse(void);
int yylex(void);

extern FILE* yyin;
extern uint64_t linesCounter;

bool nameAlreadyUsed(std::string name);
void saveType(ast::IdentifierNode* typeName, ast::TypeNode* typeDef);
void saveConstant(ast::IdentifierNode* constName, ast::ConstantNode* constDef);
void saveVariables(std::vector<ast::IdentifierNode*>* varNames, ast::TypeNode* typeDef);
void saveRoutine(ast::RoutineDeclarationNode* routineDef);

std::string getTypeString(ast::TypeNode* type);
std::string getTypeString(ast::ConstantNode::ConstantType type);
std::string getConstantString(ast::ConstantNode* constant);

bool isBasicType(const std::string& type);
bool isIntegerCompatible(ast::ExpressionNode* expr);
bool isCharCompatible(ast::ExpressionNode* expr);
bool isBooleanCompatible(ast::ExpressionNode* expr);
bool isStringCompatible(ast::ExpressionNode* expr);
bool isArrayIndexCompatible(ast::ExpressionNode* array, ast::ExpressionNode* index);
bool isArrayCompatible(ast::ExpressionNode* expr);
bool isRecordCompatible(ast::ExpressionNode* expr);
bool isRecordFieldCompatible(ast::ExpressionNode* record, ast::IdentifierNode* field);
bool isLeftValueCompatible(ast::ExpressionNode* expr);

#line 118 "out/parser.cpp"

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
  YYSYMBOL_IF = 33,                        /* IF  */
  YYSYMBOL_THEN = 34,                      /* THEN  */
  YYSYMBOL_ELSE = 35,                      /* ELSE  */
  YYSYMBOL_REPEAT = 36,                    /* REPEAT  */
  YYSYMBOL_UNTIL = 37,                     /* UNTIL  */
  YYSYMBOL_WHILE = 38,                     /* WHILE  */
  YYSYMBOL_DO = 39,                        /* DO  */
  YYSYMBOL_CASE = 40,                      /* CASE  */
  YYSYMBOL_TO = 41,                        /* TO  */
  YYSYMBOL_DOWNTO = 42,                    /* DOWNTO  */
  YYSYMBOL_FOR = 43,                       /* FOR  */
  YYSYMBOL_EQUAL = 44,                     /* EQUAL  */
  YYSYMBOL_UNEQUAL = 45,                   /* UNEQUAL  */
  YYSYMBOL_GE = 46,                        /* GE  */
  YYSYMBOL_GT = 47,                        /* GT  */
  YYSYMBOL_LE = 48,                        /* LE  */
  YYSYMBOL_LT = 49,                        /* LT  */
  YYSYMBOL_ASSIGN = 50,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 51,                      /* PLUS  */
  YYSYMBOL_MINUS = 52,                     /* MINUS  */
  YYSYMBOL_MUL = 53,                       /* MUL  */
  YYSYMBOL_DIV = 54,                       /* DIV  */
  YYSYMBOL_OR = 55,                        /* OR  */
  YYSYMBOL_AND = 56,                       /* AND  */
  YYSYMBOL_NOT = 57,                       /* NOT  */
  YYSYMBOL_MOD = 58,                       /* MOD  */
  YYSYMBOL_LB = 59,                        /* LB  */
  YYSYMBOL_RB = 60,                        /* RB  */
  YYSYMBOL_LP = 61,                        /* LP  */
  YYSYMBOL_RP = 62,                        /* RP  */
  YYSYMBOL_SEMICOLON = 63,                 /* SEMICOLON  */
  YYSYMBOL_DOT = 64,                       /* DOT  */
  YYSYMBOL_DOUBLEDOT = 65,                 /* DOUBLEDOT  */
  YYSYMBOL_COMMA = 66,                     /* COMMA  */
  YYSYMBOL_COLON = 67,                     /* COLON  */
  YYSYMBOL_INT_TYPE = 68,                  /* INT_TYPE  */
  YYSYMBOL_UNSIGNED_TYPE = 69,             /* UNSIGNED_TYPE  */
  YYSYMBOL_BOOL_TYPE = 70,                 /* BOOL_TYPE  */
  YYSYMBOL_CHAR_TYPE = 71,                 /* CHAR_TYPE  */
  YYSYMBOL_ARRAY = 72,                     /* ARRAY  */
  YYSYMBOL_OF = 73,                        /* OF  */
  YYSYMBOL_RECORD = 74,                    /* RECORD  */
  YYSYMBOL_GOTO = 75,                      /* GOTO  */
  YYSYMBOL_BREAK = 76,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 77,                  /* CONTINUE  */
  YYSYMBOL_OTHERWISE = 78,                 /* OTHERWISE  */
  YYSYMBOL_ERROR = 79,                     /* ERROR  */
  YYSYMBOL_YYACCEPT = 80,                  /* $accept  */
  YYSYMBOL_program = 81,                   /* program  */
  YYSYMBOL_routine = 82,                   /* routine  */
  YYSYMBOL_routine_head = 83,              /* routine_head  */
  YYSYMBOL_routine_part = 84,              /* routine_part  */
  YYSYMBOL_fun_decl = 85,                  /* fun_decl  */
  YYSYMBOL_fun_head = 86,                  /* fun_head  */
  YYSYMBOL_proc_decl = 87,                 /* proc_decl  */
  YYSYMBOL_proc_head = 88,                 /* proc_head  */
  YYSYMBOL_params = 89,                    /* params  */
  YYSYMBOL_params_decl = 90,               /* params_decl  */
  YYSYMBOL_params_type = 91,               /* params_type  */
  YYSYMBOL_var_part = 92,                  /* var_part  */
  YYSYMBOL_var_decl_list = 93,             /* var_decl_list  */
  YYSYMBOL_var_decl = 94,                  /* var_decl  */
  YYSYMBOL_const_part = 95,                /* const_part  */
  YYSYMBOL_const_expr_list = 96,           /* const_expr_list  */
  YYSYMBOL_const_expr = 97,                /* const_expr  */
  YYSYMBOL_const_value = 98,               /* const_value  */
  YYSYMBOL_type_part = 99,                 /* type_part  */
  YYSYMBOL_type_decl_list = 100,           /* type_decl_list  */
  YYSYMBOL_type_def = 101,                 /* type_def  */
  YYSYMBOL_type_decl = 102,                /* type_decl  */
  YYSYMBOL_record_type_decl = 103,         /* record_type_decl  */
  YYSYMBOL_field_decl_list = 104,          /* field_decl_list  */
  YYSYMBOL_field_decl = 105,               /* field_decl  */
  YYSYMBOL_array_type_decl = 106,          /* array_type_decl  */
  YYSYMBOL_simple_type = 107,              /* simple_type  */
  YYSYMBOL_name_list = 108,                /* name_list  */
  YYSYMBOL_identifier = 109,               /* identifier  */
  YYSYMBOL_routine_body = 110,             /* routine_body  */
  YYSYMBOL_compound_stmt = 111,            /* compound_stmt  */
  YYSYMBOL_stmt_list = 112,                /* stmt_list  */
  YYSYMBOL_stmt = 113,                     /* stmt  */
  YYSYMBOL_no_label_stmt = 114,            /* no_label_stmt  */
  YYSYMBOL_assign_stmt = 115,              /* assign_stmt  */
  YYSYMBOL_goto_stmt = 116,                /* goto_stmt  */
  YYSYMBOL_if_stmt = 117,                  /* if_stmt  */
  YYSYMBOL_else_clause = 118,              /* else_clause  */
  YYSYMBOL_repeat_stmt = 119,              /* repeat_stmt  */
  YYSYMBOL_while_stmt = 120,               /* while_stmt  */
  YYSYMBOL_case_stmt = 121,                /* case_stmt  */
  YYSYMBOL_case_expr_list = 122,           /* case_expr_list  */
  YYSYMBOL_case_expr = 123,                /* case_expr  */
  YYSYMBOL_for_stmt = 124,                 /* for_stmt  */
  YYSYMBOL_proc_stmt = 125,                /* proc_stmt  */
  YYSYMBOL_args_list = 126,                /* args_list  */
  YYSYMBOL_expression = 127,               /* expression  */
  YYSYMBOL_expr = 128,                     /* expr  */
  YYSYMBOL_term = 129,                     /* term  */
  YYSYMBOL_factor = 130                    /* factor  */
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
#define YYLAST   604

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  80
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  155
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  310

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   334


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
      75,    76,    77,    78,    79
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   197,   197,   208,   220,   232,   246,   255,   264,   271,
     282,   293,   304,   317,   329,   342,   355,   370,   385,   397,
     410,   423,   438,   451,   459,   468,   476,   486,   493,   502,
     509,   518,   526,   536,   546,   559,   566,   576,   584,   594,
     604,   617,   624,   631,   639,   650,   657,   664,   671,   680,
     687,   696,   705,   716,   726,   739,   746,   753,   762,   771,
     779,   789,   796,   806,   815,   822,   829,   836,   843,   850,
     857,   864,   873,   881,   891,   901,   910,   917,   927,   934,
     942,   953,   961,   970,   977,   984,   991,   998,  1005,  1012,
    1019,  1026,  1033,  1040,  1049,  1056,  1063,  1072,  1081,  1088,
    1098,  1105,  1114,  1121,  1129,  1138,  1147,  1155,  1165,  1172,
    1179,  1188,  1195,  1204,  1211,  1218,  1238,  1245,  1265,  1272,
    1292,  1318,  1340,  1366,  1390,  1398,  1408,  1421,  1434,  1447,
    1460,  1473,  1487,  1496,  1509,  1522,  1535,  1544,  1557,  1570,
    1583,  1596,  1605,  1612,  1619,  1626,  1633,  1646,  1661,  1679,
    1696,  1716,  1736,  1756,  1776,  1796
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
  "IF", "THEN", "ELSE", "REPEAT", "UNTIL", "WHILE", "DO", "CASE", "TO",
  "DOWNTO", "FOR", "EQUAL", "UNEQUAL", "GE", "GT", "LE", "LT", "ASSIGN",
  "PLUS", "MINUS", "MUL", "DIV", "OR", "AND", "NOT", "MOD", "LB", "RB",
  "LP", "RP", "SEMICOLON", "DOT", "DOUBLEDOT", "COMMA", "COLON",
  "INT_TYPE", "UNSIGNED_TYPE", "BOOL_TYPE", "CHAR_TYPE", "ARRAY", "OF",
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
  "case_expr_list", "case_expr", "for_stmt", "proc_stmt", "args_list",
  "expression", "expr", "term", "factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-185)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      36,    15,    45,    -1,  -185,    44,    55,     3,    64,    73,
    -185,    44,  -185,    46,    50,  -185,  -185,  -185,  -185,    44,
     117,  -185,    34,  -185,   329,    44,  -185,    65,    44,    96,
    -185,  -185,  -185,  -185,  -185,  -185,    13,    68,  -185,    70,
      81,  -185,    84,   108,   110,   124,   144,   145,   529,  -185,
     529,   529,    44,   141,  -185,  -185,    47,  -185,   119,  -185,
    -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,   456,
      44,  -185,    95,  -185,   197,   198,    96,  -185,     6,  -185,
      12,  -185,  -185,  -185,   419,   529,   529,   529,   529,   529,
     529,   529,   155,   156,   157,   158,   159,   164,   537,   529,
     529,  -185,   166,   284,     2,    76,   -51,   359,   453,   153,
     178,  -185,   529,   529,   529,    44,  -185,    44,  -185,  -185,
    -185,  -185,   170,    44,   165,   168,  -185,  -185,  -185,   169,
    -185,    44,   456,   172,   172,  -185,  -185,    55,   173,    55,
     174,  -185,     4,    -6,   267,    22,    23,    41,    51,    54,
     529,   529,   529,   529,   529,   529,  -185,  -185,   -51,   -51,
     213,   529,   389,   529,   529,   529,   529,   529,   529,   208,
     529,   529,   529,   529,   529,   529,   529,   529,    44,   529,
     389,    26,   529,   267,   219,    57,   194,    62,   468,    72,
    -185,   121,    34,  -185,    44,  -185,   182,    16,   179,  -185,
     184,  -185,   186,  -185,  -185,  -185,   529,  -185,  -185,  -185,
    -185,  -185,    77,    78,    90,    92,    98,   101,  -185,   106,
     208,     2,     2,     2,     2,     2,     2,   389,  -185,    76,
      76,    76,   -51,   -51,   -51,   -51,   298,  -185,   267,  -185,
     389,   187,   188,    18,  -185,   555,   201,  -185,   529,  -185,
     193,  -185,  -185,   456,  -185,  -185,  -185,    44,   128,  -185,
     127,   468,  -185,  -185,   267,  -185,  -185,  -185,  -185,  -185,
    -185,  -185,  -185,  -185,  -185,   206,   389,   389,  -185,  -185,
     529,   529,   529,   267,   200,   207,   137,  -185,    16,   468,
    -185,  -185,   211,   214,   465,   531,   267,   456,  -185,   468,
    -185,  -185,  -185,  -185,   389,   389,  -185,  -185,  -185,  -185
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    35,     1,     0,    35,     5,     0,    49,
      74,    36,    38,     0,     3,     4,    78,     6,    75,     0,
      29,    37,     0,     2,    77,    50,    52,     0,     0,     8,
      41,    43,    44,    45,    46,    47,     0,    40,    76,     0,
       0,   116,     0,   118,     0,     0,     0,     0,     0,    78,
       0,     0,     0,     0,    92,    93,   113,    84,    80,    82,
      83,    85,    86,    87,    88,    89,    90,    91,    51,     0,
      30,    32,     0,    73,     0,     0,     7,    11,    35,    12,
      35,    42,    48,    39,   103,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   144,   142,   103,   132,   136,   141,   103,     0,     0,
       0,    97,     0,     0,     0,     0,    79,     0,    68,    69,
      70,    71,     0,     0,     0,    54,    57,    56,    55,    64,
      31,     0,     0,    23,    23,     9,    10,    35,    16,    35,
      21,    81,     0,     0,   125,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    41,    47,   147,   146,
       0,     0,   103,     0,     0,     0,     0,     0,     0,   100,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     103,     0,     0,    94,     0,     0,     0,     0,     0,     0,
      60,     0,     0,    53,     0,    72,    34,     0,     0,    22,
      14,    15,    20,    19,   115,   117,     0,   119,   120,   121,
     122,   123,     0,     0,     0,     0,     0,     0,   145,     0,
     100,   130,   131,   126,   127,   128,   129,   103,    99,   133,
     134,   135,   137,   138,   140,   139,     0,   149,   102,   104,
     103,     0,     0,     0,   107,     0,     0,   114,     0,    65,
       0,    58,    59,     0,    66,    67,    33,     0,     0,    26,
       0,     0,    13,    18,   124,   150,   151,   152,   153,   154,
     155,   143,    98,   101,   148,     0,   103,   103,   105,   106,
       0,     0,     0,    96,     0,    62,     0,    24,     0,     0,
      17,   110,     0,     0,     0,     0,    95,     0,    61,     0,
      25,    28,   108,   109,   103,   103,    63,    27,   111,   112
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -185,  -185,    -4,  -185,  -185,   204,  -185,   205,  -185,   142,
    -185,    -3,  -185,  -185,   212,  -185,  -185,   276,   -11,  -185,
    -185,   264,  -131,  -185,  -185,   102,  -185,  -184,  -102,    -5,
    -185,   282,   248,   -81,   217,  -185,  -185,  -185,    82,  -185,
    -185,  -185,  -185,    80,  -185,  -185,    60,   -41,   223,     8,
     -82
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     7,     8,    76,    77,    78,    79,    80,   198,
     258,   259,    29,    70,    71,     9,    11,    12,   101,    20,
      25,    26,   125,   126,   189,   190,   127,   128,    72,   102,
      17,    57,    24,    58,    59,    60,    61,    62,   228,    63,
      64,    65,   243,   244,    66,    67,   143,   144,   104,   105,
     106
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      13,   196,    14,   142,   250,     5,    13,   103,   177,   108,
     109,    37,     5,   178,    27,   187,   158,   159,     5,    56,
      27,   191,   169,    73,   257,    81,     3,    10,   278,    10,
      30,    82,    31,    32,    33,    34,    35,    10,    30,     1,
      31,    32,    33,    34,    35,     4,    30,   110,    31,    32,
      33,    34,    35,   170,   171,    10,   205,   172,   124,   160,
     206,     5,     6,   177,   129,    73,   204,    15,   178,   137,
      36,   183,   184,    16,   138,   139,   140,   290,    36,    56,
      19,   220,   251,    10,   207,   208,    36,   191,   206,   206,
      22,   232,   233,   234,   235,   260,   240,   112,    56,   239,
      74,    75,    56,   209,   240,   301,   113,   206,   114,    69,
     186,   115,    73,   210,    23,   307,   211,   206,    73,   247,
     206,   124,   285,   206,   249,    28,   195,   129,   131,   173,
     174,    83,   175,   200,   176,   202,   236,    84,   238,   265,
     266,   245,    85,   206,   206,    86,   273,   145,   146,   147,
     148,   149,   267,   111,   268,   286,   206,    56,   206,   275,
     269,   131,   132,   270,   206,   264,   306,   206,   271,    87,
     241,    88,   206,   237,   185,    56,   242,   124,   229,   230,
     231,   254,   116,   129,    73,    89,   260,   131,   253,   255,
     287,   288,    73,   131,   289,   292,   293,   163,   164,   165,
     166,   167,   168,   131,   299,    90,    91,   283,   133,   134,
     212,   213,   214,   215,   216,   217,   150,   151,   152,   153,
     154,   219,    56,   308,   309,   155,   181,   161,   182,   188,
     192,   193,   241,   197,   194,    56,   201,   203,   242,   294,
     295,   296,   124,   227,   248,   256,   261,   262,   129,   263,
     124,   282,    73,   284,   276,   277,   129,   163,   164,   165,
     166,   167,   168,   163,   164,   165,   166,   167,   168,   291,
     298,    56,    56,   297,   302,   218,   199,   303,   124,   246,
     135,   136,   130,    73,   129,   300,   124,    21,   124,    68,
      18,   252,   129,    16,   129,    10,    39,   107,     0,    56,
      56,   141,   272,    40,    41,    42,    43,    44,    45,    46,
      47,   163,   164,   165,   166,   167,   168,    48,   162,     0,
      49,     0,    50,   279,    51,     0,     0,    52,   163,   164,
     165,   166,   167,   168,     0,     0,     0,     0,    16,    38,
      10,    39,   163,   164,   165,   166,   167,   168,    40,    41,
      42,    43,    44,    45,    46,    47,     0,     0,   274,    53,
      54,    55,    48,     0,     0,    49,     0,    50,    16,    51,
      10,    39,    52,     0,     0,     0,     0,     0,    40,    41,
      42,    43,    44,    45,    46,    47,   221,   222,   223,   224,
     225,   226,    48,     0,     0,    49,   179,    50,    16,    51,
      10,    39,    52,     0,    53,    54,    55,     0,    40,    41,
      42,    43,    44,    45,    46,    47,     0,     0,     0,     0,
       0,     0,    48,     0,     0,    49,     0,    50,    16,    51,
      10,     0,    52,     0,    53,    54,    55,     0,    40,    41,
      42,    43,    44,    45,    46,    47,     0,     0,     0,     0,
       0,     0,    48,     0,     0,    49,     0,    50,     0,    51,
       0,     0,    52,     0,    53,    54,    55,    10,    30,     0,
      31,    32,    33,    34,    35,     0,     0,     0,     0,    10,
      30,     0,    31,    32,    33,    34,    35,     0,     0,     0,
       0,     0,   180,     0,    53,    54,    55,   163,   164,   165,
     166,   167,   168,     0,   304,     0,     0,     0,    36,   163,
     164,   165,   166,   167,   168,     0,     0,   117,     0,     0,
      36,     0,     0,     0,   118,   119,   120,   121,   122,   117,
     123,     0,     0,     0,     0,     0,   118,   119,   120,   121,
      10,    30,     0,    31,    32,    33,    34,    35,    10,   156,
       0,    31,    32,    33,    34,   157,    92,    93,    94,    95,
      96,    97,     0,     0,    92,    93,    94,    95,    96,    97,
     305,     0,     0,     0,     0,   163,   164,   165,   166,   167,
     168,    98,     0,     0,     0,     0,    99,     0,     0,    98,
     100,     0,     0,     0,    99,     0,   280,   281,   100,   163,
     164,   165,   166,   167,   168
};

static const yytype_int16 yycheck[] =
{
       5,   132,     6,    85,   188,     6,    11,    48,    59,    50,
      51,    22,     6,    64,    19,   117,    98,    99,     6,    24,
      25,   123,   103,    28,     8,    12,    11,    11,    10,    11,
      12,    18,    14,    15,    16,    17,    18,    11,    12,     3,
      14,    15,    16,    17,    18,     0,    12,    52,    14,    15,
      16,    17,    18,    51,    52,    11,    62,    55,    69,   100,
      66,     6,    63,    59,    69,    70,    62,    64,    64,    63,
      52,   112,   113,     9,    78,    63,    80,   261,    52,    84,
       7,   162,    10,    11,    62,    62,    52,   189,    66,    66,
      44,   173,   174,   175,   176,   197,    78,    50,   103,   180,
       4,     5,   107,    62,    78,   289,    59,    66,    61,    44,
     115,    64,   117,    62,    64,   299,    62,    66,   123,    62,
      66,   132,   253,    66,    62,     8,   131,   132,    66,    53,
      54,    63,    56,   137,    58,   139,   177,    67,   179,    62,
      62,   182,    61,    66,    66,    61,   227,    87,    88,    89,
      90,    91,    62,    12,    62,   257,    66,   162,    66,   240,
      62,    66,    67,    62,    66,   206,   297,    66,    62,    61,
     181,    61,    66,   178,   114,   180,   181,   188,   170,   171,
     172,   192,    63,   188,   189,    61,   288,    66,    67,   194,
      62,    63,   197,    66,    67,   276,   277,    44,    45,    46,
      47,    48,    49,    66,    67,    61,    61,   248,    11,    11,
     150,   151,   152,   153,   154,   155,    61,    61,    61,    61,
      61,   161,   227,   304,   305,    61,    73,    61,    50,    59,
      65,    63,   243,    61,    65,   240,    63,    63,   243,   280,
     281,   282,   253,    35,    50,    63,    67,    63,   253,    63,
     261,    50,   257,    60,    67,    67,   261,    44,    45,    46,
      47,    48,    49,    44,    45,    46,    47,    48,    49,    63,
      63,   276,   277,    73,    63,    62,   134,    63,   289,    60,
      76,    76,    70,   288,   289,   288,   297,    11,   299,    25,
       8,   189,   297,     9,   299,    11,    12,    49,    -1,   304,
     305,    84,   220,    19,    20,    21,    22,    23,    24,    25,
      26,    44,    45,    46,    47,    48,    49,    33,    34,    -1,
      36,    -1,    38,   243,    40,    -1,    -1,    43,    44,    45,
      46,    47,    48,    49,    -1,    -1,    -1,    -1,     9,    10,
      11,    12,    44,    45,    46,    47,    48,    49,    19,    20,
      21,    22,    23,    24,    25,    26,    -1,    -1,    60,    75,
      76,    77,    33,    -1,    -1,    36,    -1,    38,     9,    40,
      11,    12,    43,    -1,    -1,    -1,    -1,    -1,    19,    20,
      21,    22,    23,    24,    25,    26,   163,   164,   165,   166,
     167,   168,    33,    -1,    -1,    36,    37,    38,     9,    40,
      11,    12,    43,    -1,    75,    76,    77,    -1,    19,    20,
      21,    22,    23,    24,    25,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    -1,    -1,    36,    -1,    38,     9,    40,
      11,    -1,    43,    -1,    75,    76,    77,    -1,    19,    20,
      21,    22,    23,    24,    25,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    -1,    -1,    36,    -1,    38,    -1,    40,
      -1,    -1,    43,    -1,    75,    76,    77,    11,    12,    -1,
      14,    15,    16,    17,    18,    -1,    -1,    -1,    -1,    11,
      12,    -1,    14,    15,    16,    17,    18,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    75,    76,    77,    44,    45,    46,
      47,    48,    49,    -1,    39,    -1,    -1,    -1,    52,    44,
      45,    46,    47,    48,    49,    -1,    -1,    61,    -1,    -1,
      52,    -1,    -1,    -1,    68,    69,    70,    71,    72,    61,
      74,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,
      11,    12,    -1,    14,    15,    16,    17,    18,    11,    12,
      -1,    14,    15,    16,    17,    18,    27,    28,    29,    30,
      31,    32,    -1,    -1,    27,    28,    29,    30,    31,    32,
      39,    -1,    -1,    -1,    -1,    44,    45,    46,    47,    48,
      49,    52,    -1,    -1,    -1,    -1,    57,    -1,    -1,    52,
      61,    -1,    -1,    -1,    57,    -1,    41,    42,    61,    44,
      45,    46,    47,    48,    49
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    81,    11,     0,     6,    63,    82,    83,    95,
      11,    96,    97,   109,    82,    64,     9,   110,   111,     7,
      99,    97,    44,    64,   112,   100,   101,   109,     8,    92,
      12,    14,    15,    16,    17,    18,    52,    98,    10,    12,
      19,    20,    21,    22,    23,    24,    25,    26,    33,    36,
      38,    40,    43,    75,    76,    77,   109,   111,   113,   114,
     115,   116,   117,   119,   120,   121,   124,   125,   101,    44,
      93,    94,   108,   109,     4,     5,    84,    85,    86,    87,
      88,    12,    18,    63,    67,    61,    61,    61,    61,    61,
      61,    61,    27,    28,    29,    30,    31,    32,    52,    57,
      61,    98,   109,   127,   128,   129,   130,   112,   127,   127,
     109,    12,    50,    59,    61,    64,    63,    61,    68,    69,
      70,    71,    72,    74,    98,   102,   103,   106,   107,   109,
      94,    66,    67,    11,    11,    85,    87,    63,    82,    63,
      82,   114,   130,   126,   127,   126,   126,   126,   126,   126,
      61,    61,    61,    61,    61,    61,    12,    18,   130,   130,
     127,    61,    34,    44,    45,    46,    47,    48,    49,   113,
      51,    52,    55,    53,    54,    56,    58,    59,    64,    37,
      39,    73,    50,   127,   127,   126,   109,   108,    59,   104,
     105,   108,    65,    63,    65,   109,   102,    61,    89,    89,
      82,    63,    82,    63,    62,    62,    66,    62,    62,    62,
      62,    62,   126,   126,   126,   126,   126,   126,    62,   126,
     113,   128,   128,   128,   128,   128,   128,    35,   118,   129,
     129,   129,   130,   130,   130,   130,   127,   109,   127,   113,
      78,    98,   109,   122,   123,   127,    60,    62,    50,    62,
     107,    10,   105,    67,    98,   109,    63,     8,    90,    91,
     108,    67,    63,    63,   127,    62,    62,    62,    62,    62,
      62,    62,   118,   113,    60,   113,    67,    67,    10,   123,
      41,    42,    50,   127,    60,   102,   108,    62,    63,    67,
     107,    63,   113,   113,   127,   127,   127,    73,    63,    67,
      91,   107,    63,    63,    39,    39,   102,   107,   113,   113
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    80,    81,    81,    81,    81,    82,    83,    84,    84,
      84,    84,    84,    85,    85,    85,    85,    86,    87,    87,
      87,    87,    88,    89,    89,    90,    90,    91,    91,    92,
      92,    93,    93,    94,    94,    95,    95,    96,    96,    97,
      97,    98,    98,    98,    98,    98,    98,    98,    98,    99,
      99,   100,   100,   101,   101,   102,   102,   102,   103,   104,
     104,   105,   105,   106,   107,   107,   107,   107,   107,   107,
     107,   107,   108,   108,   109,   110,   111,   111,   112,   112,
     112,   113,   113,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   115,   115,   115,   116,   117,   117,
     118,   118,   119,   119,   120,   121,   122,   122,   123,   123,
     123,   124,   124,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   126,   126,   127,   127,   127,   127,
     127,   127,   127,   128,   128,   128,   128,   129,   129,   129,
     129,   129,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130
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
       1,     1,     3,     1,     1,     1,     3,     2,     0,     3,
       2,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     6,     5,     2,     5,     4,
       0,     2,     4,     0,     4,     5,     2,     1,     4,     4,
       3,     8,     8,     1,     4,     4,     1,     4,     1,     4,
       4,     4,     4,     4,     3,     1,     3,     3,     3,     3,
       3,     3,     1,     3,     3,     3,     1,     3,     3,     3,
       3,     1,     1,     4,     1,     3,     2,     2,     4,     3,
       4,     4,     4,     4,     4,     4
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
#line 197 "src/yacc.y"
                                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse program 1: " << (*(yyvsp[-3].token).stringValue) << std::endl;
        #endif

        std::string name{*(yyvsp[-3].token).stringValue};
        (yyvsp[-1].routineNode)->setSubType(ast::RoutineNode::SubType::MAIN);
        (yyval.programNode) = new ast::ProgramNode(std::move(name), (yyvsp[-1].routineNode));
        resultAst = (yyval.programNode);
    }
#line 1523 "out/parser.cpp"
    break;

  case 3: /* program: PROGRAM IDENT_NAME SEMICOLON routine  */
#line 208 "src/yacc.y"
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
#line 1539 "out/parser.cpp"
    break;

  case 4: /* program: PROGRAM IDENT_NAME routine DOT  */
#line 220 "src/yacc.y"
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
#line 1555 "out/parser.cpp"
    break;

  case 5: /* program: PROGRAM IDENT_NAME routine  */
#line 232 "src/yacc.y"
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
#line 1571 "out/parser.cpp"
    break;

  case 6: /* routine: routine_head routine_body  */
#line 246 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine" << std::endl;
        #endif
        (yyval.routineNode) = new ast::RoutineNode((yyvsp[-1].routineHeadNode), (yyvsp[0].routineBodyNode));
    }
#line 1582 "out/parser.cpp"
    break;

  case 7: /* routine_head: const_part type_part var_part routine_part  */
#line 255 "src/yacc.y"
                                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine head" << std::endl;
        #endif
        (yyval.routineHeadNode) = new ast::RoutineHeadNode((yyvsp[-3].constPartList), (yyvsp[-2].typePartList), (yyvsp[-1].varPartList), (yyvsp[0].routinePartList));
    }
#line 1593 "out/parser.cpp"
    break;

  case 8: /* routine_part: %empty  */
#line 264 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty routine part" << std::endl;
        #endif
        (yyval.routinePartList) = new std::vector<ast::RoutineDeclarationNode*>();
    }
#line 1604 "out/parser.cpp"
    break;

  case 9: /* routine_part: routine_part fun_decl  */
#line 271 "src/yacc.y"
                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine part with fun decl 1 " << (yyvsp[0].routineDeclarationNode)->getName() << std::endl;
        #endif

        saveRoutine((yyvsp[0].routineDeclarationNode));

        (yyval.routinePartList) = (yyvsp[-1].routinePartList);
        (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1619 "out/parser.cpp"
    break;

  case 10: /* routine_part: routine_part proc_decl  */
#line 282 "src/yacc.y"
                           {
       #ifdef YACC_DEBUG
           std::cout << "Yacc debug: Parse routine part with proc decl 1 " << (yyvsp[0].routineDeclarationNode)->getName() << std::endl;
       #endif

       saveRoutine((yyvsp[0].routineDeclarationNode));

       (yyval.routinePartList) = (yyvsp[-1].routinePartList);
       (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1634 "out/parser.cpp"
    break;

  case 11: /* routine_part: fun_decl  */
#line 293 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine part with fun decl 2 " << (yyvsp[0].routineDeclarationNode)->getName() << std::endl;
        #endif

        saveRoutine((yyvsp[0].routineDeclarationNode));

        (yyval.routinePartList) = new std::vector<ast::RoutineDeclarationNode*>();
        (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1649 "out/parser.cpp"
    break;

  case 12: /* routine_part: proc_decl  */
#line 304 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine part with proc decl 2 " << (yyvsp[0].routineDeclarationNode)->getName() << std::endl;
        #endif

        saveRoutine((yyvsp[0].routineDeclarationNode));

        (yyval.routinePartList) = new std::vector<ast::RoutineDeclarationNode*>();
        (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1664 "out/parser.cpp"
    break;

  case 13: /* fun_decl: fun_head SEMICOLON routine SEMICOLON  */
#line 317 "src/yacc.y"
                                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun decl 1" << std::endl;
        #endif

        ctx->getLookupTable().popScope();

        (yyval.routineDeclarationNode) = (yyvsp[-3].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[-1].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
    }
#line 1680 "out/parser.cpp"
    break;

  case 14: /* fun_decl: fun_head SEMICOLON routine  */
#line 329 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun decl 2" << std::endl;
        #endif

        ctx->getLookupTable().popScope();

        (yyval.routineDeclarationNode) = (yyvsp[-2].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[0].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1697 "out/parser.cpp"
    break;

  case 15: /* fun_decl: fun_head routine SEMICOLON  */
#line 342 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun decl 3" << std::endl;
        #endif

        ctx->getLookupTable().popScope();

        (yyval.routineDeclarationNode) = (yyvsp[-2].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[-1].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1714 "out/parser.cpp"
    break;

  case 16: /* fun_decl: fun_head routine  */
#line 355 "src/yacc.y"
                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun decl 4" << std::endl;
        #endif

        ctx->getLookupTable().popScope();

        (yyval.routineDeclarationNode) = (yyvsp[-1].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[0].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1731 "out/parser.cpp"
    break;

  case 17: /* fun_head: FUNCTION IDENT_NAME params COLON simple_type  */
#line 370 "src/yacc.y"
                                                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun head " << (*(yyvsp[-3].token).stringValue) << std::endl;
        #endif

        ctx->getLookupTable().pushScope(*(yyvsp[-3].token).stringValue);

        std::string name{*(yyvsp[-3].token).stringValue};
        (yyval.routineDeclarationNode) = new ast::RoutineDeclarationNode(ast::RoutineDeclarationNode::RoutineType::FUNCTION, std::move(name), (yyvsp[-2].paramsNode), (yyvsp[0].simpleTypeNode), nullptr);


    }
#line 1748 "out/parser.cpp"
    break;

  case 18: /* proc_decl: proc_head SEMICOLON routine SEMICOLON  */
#line 385 "src/yacc.y"
                                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse proc decl" << std::endl;
        #endif

        ctx->getLookupTable().popScope();

        (yyval.routineDeclarationNode) = (yyvsp[-3].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[-1].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::PROCEDURE);
    }
#line 1764 "out/parser.cpp"
    break;

  case 19: /* proc_decl: proc_head routine SEMICOLON  */
#line 397 "src/yacc.y"
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
#line 1781 "out/parser.cpp"
    break;

  case 20: /* proc_decl: proc_head SEMICOLON routine  */
#line 410 "src/yacc.y"
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
#line 1798 "out/parser.cpp"
    break;

  case 21: /* proc_decl: proc_head routine  */
#line 423 "src/yacc.y"
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
#line 1815 "out/parser.cpp"
    break;

  case 22: /* proc_head: PROCEDURE IDENT_NAME params  */
#line 438 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse proc head " << (*(yyvsp[-1].token).stringValue) << std::endl;
        #endif

        ctx->getLookupTable().pushScope(*(yyvsp[-1].token).stringValue);

        std::string name{*(yyvsp[-1].token).stringValue};
        (yyval.routineDeclarationNode) = new ast::RoutineDeclarationNode(ast::RoutineDeclarationNode::RoutineType::PROCEDURE, std::move(name), (yyvsp[0].paramsNode), nullptr, nullptr);
    }
#line 1830 "out/parser.cpp"
    break;

  case 23: /* params: %empty  */
#line 451 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty params" << std::endl;
        #endif
        std::vector<ast::ParamsGroupNode *>* emptyParamsList = new std::vector<ast::ParamsGroupNode*>();
        (yyval.paramsNode) = new ast::ParamsNode(emptyParamsList);
    }
#line 1842 "out/parser.cpp"
    break;

  case 24: /* params: LP params_decl RP  */
#line 459 "src/yacc.y"
                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params" << std::endl;
        #endif
        (yyval.paramsNode) = new ast::ParamsNode((yyvsp[-1].paramsGroupList));
    }
#line 1853 "out/parser.cpp"
    break;

  case 25: /* params_decl: params_decl SEMICOLON params_type  */
#line 468 "src/yacc.y"
                                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params decl 1" << std::endl;
        #endif
        (yyval.paramsGroupList) = (yyvsp[-2].paramsGroupList);
        (yyval.paramsGroupList)->push_back((yyvsp[0].paramsGroupNode));
    }
#line 1865 "out/parser.cpp"
    break;

  case 26: /* params_decl: params_type  */
#line 476 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params decl 2" << std::endl;
        #endif
        (yyval.paramsGroupList) = new std::vector<ast::ParamsGroupNode*>();
        (yyval.paramsGroupList)->push_back((yyvsp[0].paramsGroupNode));
    }
#line 1877 "out/parser.cpp"
    break;

  case 27: /* params_type: VAR name_list COLON simple_type  */
#line 486 "src/yacc.y"
                                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params type 1" << std::endl;
        #endif
        (yyval.paramsGroupNode) = new ast::ParamsGroupNode(ast::ParamsGroupNode::PassType::PASS_BY_REFERENCE, (yyvsp[-2].identifierList), (yyvsp[0].simpleTypeNode));
    }
#line 1888 "out/parser.cpp"
    break;

  case 28: /* params_type: name_list COLON simple_type  */
#line 493 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params type 2" << std::endl;
        #endif
        (yyval.paramsGroupNode) = new ast::ParamsGroupNode(ast::ParamsGroupNode::PassType::PASS_BY_VALUE, (yyvsp[-2].identifierList), (yyvsp[0].simpleTypeNode));
    }
#line 1899 "out/parser.cpp"
    break;

  case 29: /* var_part: %empty  */
#line 502 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty var part" << std::endl;
        #endif
        (yyval.varPartList) = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
    }
#line 1910 "out/parser.cpp"
    break;

  case 30: /* var_part: VAR var_decl_list  */
#line 509 "src/yacc.y"
                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var part" << std::endl;
        #endif
        (yyval.varPartList) = (yyvsp[0].varPartList);
    }
#line 1921 "out/parser.cpp"
    break;

  case 31: /* var_decl_list: var_decl_list var_decl  */
#line 518 "src/yacc.y"
                           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl list 1" << std::endl;
        #endif
        (yyval.varPartList) = (yyvsp[-1].varPartList);
        (yyval.varPartList)->push_back((yyvsp[0].varPartListElement));
    }
#line 1933 "out/parser.cpp"
    break;

  case 32: /* var_decl_list: var_decl  */
#line 526 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl list 2" << std::endl;
        #endif
        (yyval.varPartList) = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
        (yyval.varPartList)->push_back((yyvsp[0].varPartListElement));
    }
#line 1945 "out/parser.cpp"
    break;

  case 33: /* var_decl: name_list COLON type_decl SEMICOLON  */
#line 536 "src/yacc.y"
                                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl 1" << std::endl;
        #endif

        saveVariables((yyvsp[-3].identifierList), (yyvsp[-1].typeNode));

        (yyval.varPartListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-3].identifierList), (yyvsp[-1].typeNode));
    }
#line 1959 "out/parser.cpp"
    break;

  case 34: /* var_decl: name_list COLON type_decl  */
#line 546 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl 2" << std::endl;
        #endif

        saveVariables((yyvsp[-2].identifierList), (yyvsp[0].typeNode));

        (yyval.varPartListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-2].identifierList), (yyvsp[0].typeNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1974 "out/parser.cpp"
    break;

  case 35: /* const_part: %empty  */
#line 559 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty const part" << std::endl;
        #endif
        (yyval.constPartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::ConstantNode*>*>();
    }
#line 1985 "out/parser.cpp"
    break;

  case 36: /* const_part: CONST const_expr_list  */
#line 566 "src/yacc.y"
                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const part" << std::endl;
        #endif

        (yyval.constPartList) = (yyvsp[0].constPartList);
    }
#line 1997 "out/parser.cpp"
    break;

  case 37: /* const_expr_list: const_expr_list const_expr  */
#line 576 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr list 1" << std::endl;
        #endif
        (yyval.constPartList) = (yyvsp[-1].constPartList);
        (yyval.constPartList)->push_back((yyvsp[0].constPartListElement));
    }
#line 2009 "out/parser.cpp"
    break;

  case 38: /* const_expr_list: const_expr  */
#line 584 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr list 2" << std::endl;
        #endif
        (yyval.constPartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::ConstantNode*>*>();
        (yyval.constPartList)->push_back((yyvsp[0].constPartListElement));
    }
#line 2021 "out/parser.cpp"
    break;

  case 39: /* const_expr: identifier EQUAL const_value SEMICOLON  */
#line 594 "src/yacc.y"
                                           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr 1" << std::endl;
        #endif

        saveConstant((yyvsp[-3].identifierNode), (yyvsp[-1].constantNode));

        (yyval.constPartListElement) = new std::pair<ast::IdentifierNode*, ast::ConstantNode*>((yyvsp[-3].identifierNode), (yyvsp[-1].constantNode));
    }
#line 2035 "out/parser.cpp"
    break;

  case 40: /* const_expr: identifier EQUAL const_value  */
#line 604 "src/yacc.y"
                                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr 2" << std::endl;
        #endif

        saveConstant((yyvsp[-2].identifierNode), (yyvsp[0].constantNode));

        (yyval.constPartListElement) = new std::pair<ast::IdentifierNode*, ast::ConstantNode*>((yyvsp[-2].identifierNode), (yyvsp[0].constantNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2050 "out/parser.cpp"
    break;

  case 41: /* const_value: INTEGER  */
#line 617 "src/yacc.y"
            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - integer `" << (yyvsp[0].token).numericalValue << "`" << std::endl;
        #endif
        (yyval.constantNode) = new ast::IntegerConstantNode((yyvsp[0].token).numericalValue);
    }
#line 2061 "out/parser.cpp"
    break;

  case 42: /* const_value: MINUS INTEGER  */
#line 624 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - signed integer `" << -(yyvsp[0].token).numericalValue << "`" << std::endl;
        #endif
        (yyval.constantNode) = new ast::IntegerConstantNode(-(yyvsp[0].token).numericalValue);
    }
#line 2072 "out/parser.cpp"
    break;

  case 43: /* const_value: CHAR  */
#line 632 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - char `" << static_cast<char>((yyvsp[0].token).numericalValue) << "`" << std::endl;
        #endif
        (yyval.constantNode) = new ast::CharConstantNode(static_cast<char>((yyvsp[0].token).numericalValue));
    }
#line 2083 "out/parser.cpp"
    break;

  case 44: /* const_value: STRING  */
#line 639 "src/yacc.y"
           {
        std::string str{*(yyvsp[0].token).stringValue};
        str = str.substr(1, str.size() - 2);

        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - string `" << str << "`" << std::endl;
        #endif

        (yyval.constantNode) = new ast::StringConstantNode(std::move(str));
    }
#line 2098 "out/parser.cpp"
    break;

  case 45: /* const_value: TRUE  */
#line 650 "src/yacc.y"
         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - true" << std::endl;
        #endif
        (yyval.constantNode) = new ast::BooleanConstantNode(true);
    }
#line 2109 "out/parser.cpp"
    break;

  case 46: /* const_value: FALSE  */
#line 657 "src/yacc.y"
          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - false" << std::endl;
        #endif
        (yyval.constantNode) = new ast::BooleanConstantNode(false);
    }
#line 2120 "out/parser.cpp"
    break;

  case 47: /* const_value: MAXINT  */
#line 664 "src/yacc.y"
           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - maxint" << std::endl;
        #endif
        (yyval.constantNode) = new ast::IntegerConstantNode(255);
    }
#line 2131 "out/parser.cpp"
    break;

  case 48: /* const_value: MINUS MAXINT  */
#line 671 "src/yacc.y"
                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - signed maxint" << std::endl;
        #endif
        (yyval.constantNode) = new ast::IntegerConstantNode(-255);
    }
#line 2142 "out/parser.cpp"
    break;

  case 49: /* type_part: %empty  */
#line 680 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty type part" << std::endl;
        #endif
        (yyval.typePartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::TypeNode*>*>();
    }
#line 2153 "out/parser.cpp"
    break;

  case 50: /* type_part: TYPE type_decl_list  */
#line 687 "src/yacc.y"
                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type part" << std::endl;
        #endif
        (yyval.typePartList) = (yyvsp[0].typePartList);
    }
#line 2164 "out/parser.cpp"
    break;

  case 51: /* type_decl_list: type_decl_list type_def  */
#line 696 "src/yacc.y"
                            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type decl list 1" << std::endl;
        #endif

        (yyval.typePartList) = (yyvsp[-1].typePartList);
        (yyval.typePartList)->push_back((yyvsp[0].typePartListElement));
    }
#line 2177 "out/parser.cpp"
    break;

  case 52: /* type_decl_list: type_def  */
#line 705 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type decl list 2" << std::endl;
        #endif

        (yyval.typePartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::TypeNode*>*>();
        (yyval.typePartList)->push_back((yyvsp[0].typePartListElement));
    }
#line 2190 "out/parser.cpp"
    break;

  case 53: /* type_def: identifier EQUAL type_decl SEMICOLON  */
#line 716 "src/yacc.y"
                                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type def 1" << std::endl;
        #endif

        saveType((yyvsp[-3].identifierNode), (yyvsp[-1].typeNode));

        (yyval.typePartListElement) = new std::pair<ast::IdentifierNode*, ast::TypeNode*>((yyvsp[-3].identifierNode), (yyvsp[-1].typeNode));
    }
#line 2204 "out/parser.cpp"
    break;

  case 54: /* type_def: identifier EQUAL type_decl  */
#line 726 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type def 2" << std::endl;
        #endif

        saveType((yyvsp[-2].identifierNode), (yyvsp[0].typeNode));

        (yyval.typePartListElement) = new std::pair<ast::IdentifierNode*, ast::TypeNode*>((yyvsp[-2].identifierNode), (yyvsp[0].typeNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2219 "out/parser.cpp"
    break;

  case 55: /* type_decl: simple_type  */
#line 739 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type" << std::endl;
        #endif
        (yyval.typeNode) = (yyvsp[0].simpleTypeNode);
    }
#line 2230 "out/parser.cpp"
    break;

  case 56: /* type_decl: array_type_decl  */
#line 746 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse array type" << std::endl;
        #endif
        (yyval.typeNode) = (yyvsp[0].arrayTypeNode);
    }
#line 2241 "out/parser.cpp"
    break;

  case 57: /* type_decl: record_type_decl  */
#line 753 "src/yacc.y"
                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse record type" << std::endl;
        #endif
        (yyval.typeNode) = (yyvsp[0].recordTypeNode);
    }
#line 2252 "out/parser.cpp"
    break;

  case 58: /* record_type_decl: RECORD field_decl_list END  */
#line 762 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse record type" << std::endl;
        #endif
        (yyval.recordTypeNode) = new ast::RecordTypeNode((yyvsp[-1].fieldDeclList));
    }
#line 2263 "out/parser.cpp"
    break;

  case 59: /* field_decl_list: field_decl_list field_decl  */
#line 771 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl list 1" << std::endl;
        #endif
        (yyval.fieldDeclList) = (yyvsp[-1].fieldDeclList);
        (yyval.fieldDeclList)->push_back((yyvsp[0].fieldDeclListElement));
    }
#line 2275 "out/parser.cpp"
    break;

  case 60: /* field_decl_list: field_decl  */
#line 779 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl list 2" << std::endl;
        #endif
        (yyval.fieldDeclList) = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
        (yyval.fieldDeclList)->push_back((yyvsp[0].fieldDeclListElement));
    }
#line 2287 "out/parser.cpp"
    break;

  case 61: /* field_decl: name_list COLON type_decl SEMICOLON  */
#line 789 "src/yacc.y"
                                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl 1" << std::endl;
        #endif
        (yyval.fieldDeclListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-3].identifierList), (yyvsp[-1].typeNode));
    }
#line 2298 "out/parser.cpp"
    break;

  case 62: /* field_decl: name_list COLON type_decl  */
#line 796 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl 2" << std::endl;
        #endif
        (yyval.fieldDeclListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-2].identifierList), (yyvsp[0].typeNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2310 "out/parser.cpp"
    break;

  case 63: /* array_type_decl: ARRAY LB simple_type RB OF type_decl  */
#line 806 "src/yacc.y"
                                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse array type" << std::endl;
        #endif
        (yyval.arrayTypeNode) = new ast::ArrayTypeNode((yyvsp[-3].simpleTypeNode), (yyvsp[0].typeNode));
    }
#line 2321 "out/parser.cpp"
    break;

  case 64: /* simple_type: identifier  */
#line 815 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - identifier" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::RenameTypeNode((yyvsp[0].identifierNode));
    }
#line 2332 "out/parser.cpp"
    break;

  case 65: /* simple_type: LP name_list RP  */
#line 822 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - parentheses" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::EnumerationTypeNode((yyvsp[-1].identifierList));
    }
#line 2343 "out/parser.cpp"
    break;

  case 66: /* simple_type: const_value DOUBLEDOT const_value  */
#line 829 "src/yacc.y"
                                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - range 1" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::ConstRangeTypeNode((yyvsp[-2].constantNode), (yyvsp[0].constantNode));
    }
#line 2354 "out/parser.cpp"
    break;

  case 67: /* simple_type: identifier DOUBLEDOT identifier  */
#line 836 "src/yacc.y"
                                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - range 4" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::VarRangeTypeNode((yyvsp[-2].identifierNode), (yyvsp[0].identifierNode));
    }
#line 2365 "out/parser.cpp"
    break;

  case 68: /* simple_type: INT_TYPE  */
#line 843 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - int" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::INTEGER);
    }
#line 2376 "out/parser.cpp"
    break;

  case 69: /* simple_type: UNSIGNED_TYPE  */
#line 850 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - unsigned" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::UNSIGNED);
    }
#line 2387 "out/parser.cpp"
    break;

  case 70: /* simple_type: BOOL_TYPE  */
#line 857 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - bool" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::BOOLEAN);
    }
#line 2398 "out/parser.cpp"
    break;

  case 71: /* simple_type: CHAR_TYPE  */
#line 864 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - char" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::CHAR);
    }
#line 2409 "out/parser.cpp"
    break;

  case 72: /* name_list: name_list COMMA identifier  */
#line 873 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse name list 1" << std::endl;
        #endif
        (yyval.identifierList) = (yyvsp[-2].identifierList);
        (yyval.identifierList)->push_back((yyvsp[0].identifierNode));
    }
#line 2421 "out/parser.cpp"
    break;

  case 73: /* name_list: identifier  */
#line 881 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse name list 2" << std::endl;
        #endif
        (yyval.identifierList) = new std::vector<ast::IdentifierNode*>();
        (yyval.identifierList)->push_back((yyvsp[0].identifierNode));
    }
#line 2433 "out/parser.cpp"
    break;

  case 74: /* identifier: IDENT_NAME  */
#line 891 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse identifier `" << (*(yyvsp[0].token).stringValue) << "`" << std::endl;
        #endif
        std::string name{*(yyvsp[0].token).stringValue};
        (yyval.identifierNode) = new ast::IdentifierNode(std::move(name));
    }
#line 2445 "out/parser.cpp"
    break;

  case 75: /* routine_body: compound_stmt  */
#line 901 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine body" << std::endl;
        #endif
        (yyval.routineBodyNode) = new ast::RoutineBodyNode((yyvsp[0].compoundStatementNode));
    }
#line 2456 "out/parser.cpp"
    break;

  case 76: /* compound_stmt: BBEGIN stmt_list END  */
#line 910 "src/yacc.y"
                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse compound statement 1" << std::endl;
        #endif
        (yyval.compoundStatementNode) = new ast::CompoundStatementNode((yyvsp[-1].statementNodeList));
    }
#line 2467 "out/parser.cpp"
    break;

  case 77: /* compound_stmt: BBEGIN stmt_list  */
#line 917 "src/yacc.y"
                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse compound statement 2" << std::endl;
        #endif
        (yyval.compoundStatementNode) = new ast::CompoundStatementNode((yyvsp[0].statementNodeList));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of end");
    }
#line 2479 "out/parser.cpp"
    break;

  case 78: /* stmt_list: %empty  */
#line 927 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty statement list" << std::endl;
        #endif
        (yyval.statementNodeList) = new std::vector<ast::StatementNode*>();
    }
#line 2490 "out/parser.cpp"
    break;

  case 79: /* stmt_list: stmt_list stmt SEMICOLON  */
#line 934 "src/yacc.y"
                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement list 1" << std::endl;
        #endif
        (yyval.statementNodeList) = (yyvsp[-2].statementNodeList);
        (yyval.statementNodeList)->push_back((yyvsp[-1].statementNode));
    }
#line 2502 "out/parser.cpp"
    break;

  case 80: /* stmt_list: stmt_list stmt  */
#line 942 "src/yacc.y"
                   {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement list 2" << std::endl;
        #endif
        (yyval.statementNodeList) = (yyvsp[-1].statementNodeList);
        (yyval.statementNodeList)->push_back((yyvsp[0].statementNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2515 "out/parser.cpp"
    break;

  case 81: /* stmt: INTEGER COLON no_label_stmt  */
#line 953 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement with label " << (yyvsp[-2].token).numericalValue << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].statementNode);
        (yyval.statementNode)->setLabel((yyvsp[-2].token).numericalValue);
    }
#line 2527 "out/parser.cpp"
    break;

  case 82: /* stmt: no_label_stmt  */
#line 961 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement without label" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].statementNode);
    }
#line 2538 "out/parser.cpp"
    break;

  case 83: /* no_label_stmt: assign_stmt  */
#line 970 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - assign" << std::endl;
        #endif
        (yyval.statementNode)=(yyvsp[0].assignNode);
    }
#line 2549 "out/parser.cpp"
    break;

  case 84: /* no_label_stmt: compound_stmt  */
#line 977 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - compound" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].compoundStatementNode);
    }
#line 2560 "out/parser.cpp"
    break;

  case 85: /* no_label_stmt: goto_stmt  */
#line 984 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - goto" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].gotoNode);
    }
#line 2571 "out/parser.cpp"
    break;

  case 86: /* no_label_stmt: if_stmt  */
#line 991 "src/yacc.y"
            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - if" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].ifNode);
    }
#line 2582 "out/parser.cpp"
    break;

  case 87: /* no_label_stmt: repeat_stmt  */
#line 998 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - repeat" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].repeatNode);
    }
#line 2593 "out/parser.cpp"
    break;

  case 88: /* no_label_stmt: while_stmt  */
#line 1005 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - while" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].whileNode);
    }
#line 2604 "out/parser.cpp"
    break;

  case 89: /* no_label_stmt: case_stmt  */
#line 1012 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - case" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].caseNode);
    }
#line 2615 "out/parser.cpp"
    break;

  case 90: /* no_label_stmt: for_stmt  */
#line 1019 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - for" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].forNode);
    }
#line 2626 "out/parser.cpp"
    break;

  case 91: /* no_label_stmt: proc_stmt  */
#line 1026 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - proc" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].callNode);
    }
#line 2637 "out/parser.cpp"
    break;

  case 92: /* no_label_stmt: BREAK  */
#line 1033 "src/yacc.y"
          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - break" << std::endl;
        #endif
        (yyval.statementNode) = new ast::BreakNode();
    }
#line 2648 "out/parser.cpp"
    break;

  case 93: /* no_label_stmt: CONTINUE  */
#line 1040 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - continue" << std::endl;
        #endif
        (yyval.statementNode) = new ast::ContinueNode();
    }
#line 2659 "out/parser.cpp"
    break;

  case 94: /* assign_stmt: identifier ASSIGN expression  */
#line 1049 "src/yacc.y"
                                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple assign statement" << std::endl;
        #endif
        (yyval.assignNode) = new ast::AssignToVariableNode((yyvsp[-2].identifierNode), (yyvsp[0].expressionNode));
    }
#line 2670 "out/parser.cpp"
    break;

  case 95: /* assign_stmt: identifier LB expression RB ASSIGN expression  */
#line 1056 "src/yacc.y"
                                                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse array assign statement" << std::endl;
        #endif
        (yyval.assignNode) = new ast::AssignToArrayNode((yyvsp[-5].identifierNode), (yyvsp[-3].expressionNode), (yyvsp[0].expressionNode));
    }
#line 2681 "out/parser.cpp"
    break;

  case 96: /* assign_stmt: identifier DOT identifier ASSIGN expression  */
#line 1063 "src/yacc.y"
                                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse record assign statement" << std::endl;
        #endif
        (yyval.assignNode) = new ast::AssignToRecordFieldNode((yyvsp[-4].identifierNode), (yyvsp[-2].identifierNode), (yyvsp[0].expressionNode));
    }
#line 2692 "out/parser.cpp"
    break;

  case 97: /* goto_stmt: GOTO INTEGER  */
#line 1072 "src/yacc.y"
                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse goto statement to " << (yyvsp[0].token).numericalValue << std::endl;
        #endif
        (yyval.gotoNode) = new ast::GotoNode((yyvsp[0].token).numericalValue);
    }
#line 2703 "out/parser.cpp"
    break;

  case 98: /* if_stmt: IF expression THEN stmt else_clause  */
#line 1081 "src/yacc.y"
                                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse if statement 1" << std::endl;
        #endif
        (yyval.ifNode) = new ast::IfNode((yyvsp[-3].expressionNode), (yyvsp[-1].statementNode), (yyvsp[0].ifNode));
    }
#line 2714 "out/parser.cpp"
    break;

  case 99: /* if_stmt: IF expression stmt else_clause  */
#line 1088 "src/yacc.y"
                                   {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse if statement 2" << std::endl;
        #endif
        (yyval.ifNode) = new ast::IfNode((yyvsp[-2].expressionNode), (yyvsp[-1].statementNode), (yyvsp[0].ifNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of then");
    }
#line 2726 "out/parser.cpp"
    break;

  case 100: /* else_clause: %empty  */
#line 1098 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty else clause" << std::endl;
        #endif
        (yyval.ifNode) = new ast::IfNode(nullptr, nullptr);
    }
#line 2737 "out/parser.cpp"
    break;

  case 101: /* else_clause: ELSE stmt  */
#line 1105 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse else clause" << std::endl;
        #endif
        (yyval.ifNode) = new ast::IfNode(nullptr, nullptr, (yyvsp[0].statementNode));
    }
#line 2748 "out/parser.cpp"
    break;

  case 102: /* repeat_stmt: REPEAT stmt_list UNTIL expression  */
#line 1114 "src/yacc.y"
                                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse repeat statement" << std::endl;
        #endif
        (yyval.repeatNode) = new ast::RepeatNode((yyvsp[0].expressionNode), (yyvsp[-2].statementNodeList));
    }
#line 2759 "out/parser.cpp"
    break;

  case 103: /* repeat_stmt: %empty  */
#line 1121 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty repeat statement" << std::endl;
        #endif
    }
#line 2769 "out/parser.cpp"
    break;

  case 104: /* while_stmt: WHILE expression DO stmt  */
#line 1129 "src/yacc.y"
                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse while statement" << std::endl;
        #endif
        (yyval.whileNode) = new ast::WhileNode((yyvsp[-2].expressionNode), (yyvsp[0].statementNode));
    }
#line 2780 "out/parser.cpp"
    break;

  case 105: /* case_stmt: CASE expression OF case_expr_list END  */
#line 1138 "src/yacc.y"
                                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case statement" << std::endl;
        #endif
        (yyval.caseNode) = new ast::CaseNode((yyvsp[-3].expressionNode), (yyvsp[-1].caseExprList));
    }
#line 2791 "out/parser.cpp"
    break;

  case 106: /* case_expr_list: case_expr_list case_expr  */
#line 1147 "src/yacc.y"
                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr list 1" << std::endl;
        #endif
        (yyval.caseExprList) = (yyvsp[-1].caseExprList);
        (yyval.caseExprList)->push_back((yyvsp[0].caseExpr));
    }
#line 2803 "out/parser.cpp"
    break;

  case 107: /* case_expr_list: case_expr  */
#line 1155 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr list 2" << std::endl;
        #endif
        (yyval.caseExprList) = new std::vector<std::pair<ast::AstNode*, ast::StatementNode*>*>();
        (yyval.caseExprList)->push_back((yyvsp[0].caseExpr));
    }
#line 2815 "out/parser.cpp"
    break;

  case 108: /* case_expr: const_value COLON stmt SEMICOLON  */
#line 1165 "src/yacc.y"
                                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr 1" << std::endl;
        #endif
        (yyval.caseExpr) = new std::pair<ast::AstNode*, ast::StatementNode*>((yyvsp[-3].constantNode), (yyvsp[-1].statementNode));
    }
#line 2826 "out/parser.cpp"
    break;

  case 109: /* case_expr: identifier COLON stmt SEMICOLON  */
#line 1172 "src/yacc.y"
                                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr 2" << std::endl;
        #endif
        (yyval.caseExpr) = new std::pair<ast::AstNode*, ast::StatementNode*>((yyvsp[-3].identifierNode), (yyvsp[-1].statementNode));
    }
#line 2837 "out/parser.cpp"
    break;

  case 110: /* case_expr: OTHERWISE stmt SEMICOLON  */
#line 1179 "src/yacc.y"
                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr 3" << std::endl;
        #endif
        (yyval.caseExpr) = new std::pair<ast::AstNode*, ast::StatementNode*>(nullptr, (yyvsp[-1].statementNode));
    }
#line 2848 "out/parser.cpp"
    break;

  case 111: /* for_stmt: FOR identifier ASSIGN expression TO expression DO stmt  */
#line 1188 "src/yacc.y"
                                                           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse for statement 1" << std::endl;
        #endif
        (yyval.forNode) = new ast::ForNode((yyvsp[-6].identifierNode), (yyvsp[-4].expressionNode), (yyvsp[-2].expressionNode), (yyvsp[0].statementNode), ast::ForNode::Direction::INCREMENT);
    }
#line 2859 "out/parser.cpp"
    break;

  case 112: /* for_stmt: FOR identifier ASSIGN expression DOWNTO expression DO stmt  */
#line 1195 "src/yacc.y"
                                                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse for statement 2" << std::endl;
        #endif
        (yyval.forNode) = new ast::ForNode((yyvsp[-6].identifierNode), (yyvsp[-4].expressionNode), (yyvsp[-2].expressionNode), (yyvsp[0].statementNode), ast::ForNode::Direction::DECREMENT);
    }
#line 2870 "out/parser.cpp"
    break;

  case 113: /* proc_stmt: identifier  */
#line 1204 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse procedure statement" << std::endl;
        #endif
        (yyval.callNode) = new ast::UserDefineCallNode((yyvsp[0].identifierNode), nullptr);
    }
#line 2881 "out/parser.cpp"
    break;

  case 114: /* proc_stmt: identifier LP args_list RP  */
#line 1211 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse procedure statement with args" << std::endl;
        #endif
        (yyval.callNode) = new ast::UserDefineCallNode((yyvsp[-3].identifierNode), (yyvsp[-1].argsList));
    }
#line 2892 "out/parser.cpp"
    break;

  case 115: /* proc_stmt: READ LP factor RP  */
#line 1218 "src/yacc.y"
                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse read statement" << std::endl;
        #endif
        if(!isLeftValueCompatible((yyvsp[-1].expressionNode))) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for read - assignable argument expected");
            fatalError = true;
        }
        else if(!isIntegerCompatible((yyvsp[-1].expressionNode)) && !isCharCompatible((yyvsp[-1].expressionNode)) && !isBooleanCompatible((yyvsp[-1].expressionNode))) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for read - integer, char or boolean expected");
            fatalError = true;
        }
        else {
            ast::ArgumentsListNode* args = new ast::ArgumentsListNode();
            args->addArgument((yyvsp[-1].expressionNode));
            (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::READ, args);
        }
    }
#line 2915 "out/parser.cpp"
    break;

  case 116: /* proc_stmt: READLN  */
#line 1238 "src/yacc.y"
           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse readln statement" << std::endl;
        #endif
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::READLN, nullptr);
    }
#line 2926 "out/parser.cpp"
    break;

  case 117: /* proc_stmt: WRITE LP args_list RP  */
#line 1245 "src/yacc.y"
                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse write statement" << std::endl;
        #endif
        bool allOk = true;
        for(auto arg : (yyvsp[-1].argsList)->getArguments()) {
            if(!isIntegerCompatible(arg) && !isCharCompatible(arg) && !isBooleanCompatible(arg) && !isStringCompatible(arg)) {
                allOk = false;
                break;
            }
        }

        if(!allOk) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for write - integer, char, boolean or string expected");
        }
        else {
            (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITE, (yyvsp[-1].argsList));
        }
    }
#line 2950 "out/parser.cpp"
    break;

  case 118: /* proc_stmt: WRITELN  */
#line 1265 "src/yacc.y"
            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse writeln statement" << std::endl;
        #endif
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITELN, nullptr);
    }
#line 2961 "out/parser.cpp"
    break;

  case 119: /* proc_stmt: WRITELN LP args_list RP  */
#line 1272 "src/yacc.y"
                            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse writeln statement with args" << std::endl;
        #endif
        bool allOk = true;
        for(auto arg : (yyvsp[-1].argsList)->getArguments()) {
            if(!isIntegerCompatible(arg) && !isCharCompatible(arg) && !isBooleanCompatible(arg) && !isStringCompatible(arg)) {
                allOk = false;
                break;
            }
        }

        if(!allOk) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for writeln - integer, char, boolean or string expected");
        }
        else {
            (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITELN, (yyvsp[-1].argsList));
        }
    }
#line 2985 "out/parser.cpp"
    break;

  case 120: /* proc_stmt: MEMORYREAD LP args_list RP  */
#line 1292 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse memory read statement" << std::endl;
        #endif
        if((yyvsp[-1].argsList)->getArguments().size() == 3) {
            if(!isIntegerCompatible((yyvsp[-1].argsList)->getArguments().at(0)) || !isIntegerCompatible((yyvsp[-1].argsList)->getArguments().at(1))) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory read - first two arguments should be integers");
                fatalError = true;
            }
            else if(!isLeftValueCompatible((yyvsp[-1].argsList)->getArguments().at(2))) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory read - assignable argument expected");
                fatalError = true;
            }
            else if(!isIntegerCompatible((yyvsp[-1].argsList)->getArguments().at(2)) && !isCharCompatible((yyvsp[-1].argsList)->getArguments().at(2)) && !isBooleanCompatible((yyvsp[-1].argsList)->getArguments().at(2))) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory read - integer, char or boolean expected");
                fatalError = true;
            }
            else {
                (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::MEMORY_READ, (yyvsp[-1].argsList));
            }
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for memory read - 3 arguments expected");
        }
    }
#line 3015 "out/parser.cpp"
    break;

  case 121: /* proc_stmt: MEMORYWRITE LP args_list RP  */
#line 1318 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse memory write statement" << std::endl;
        #endif
        if((yyvsp[-1].argsList)->getArguments().size() == 3) {
            if(!isIntegerCompatible((yyvsp[-1].argsList)->getArguments().at(0)) || !isIntegerCompatible((yyvsp[-1].argsList)->getArguments().at(1))) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory write - first two arguments should be integers");
                fatalError = true;
            }
            else if(!isIntegerCompatible((yyvsp[-1].argsList)->getArguments().at(2)) && !isCharCompatible((yyvsp[-1].argsList)->getArguments().at(2)) && !isBooleanCompatible((yyvsp[-1].argsList)->getArguments().at(2))) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory write - third argument should be integer, char or boolean");
                fatalError = true;
            }
            else {
                (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::MEMORY_WRITE, (yyvsp[-1].argsList));
            }
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for memory write - 3 arguments expected");
        }
    }
#line 3041 "out/parser.cpp"
    break;

  case 122: /* proc_stmt: STACKREAD LP args_list RP  */
#line 1340 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse stack read statement" << std::endl;
        #endif
        if((yyvsp[-1].argsList)->getArguments().size() == 3) {
            if(!isIntegerCompatible((yyvsp[-1].argsList)->getArguments().at(0)) || !isIntegerCompatible((yyvsp[-1].argsList)->getArguments().at(1))) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack read - first two arguments should be integers");
                fatalError = true;
            }
            else if(!isLeftValueCompatible((yyvsp[-1].argsList)->getArguments().at(2))) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack read - assignable argument expected");
                fatalError = true;
            }
            else if(!isIntegerCompatible((yyvsp[-1].argsList)->getArguments().at(2)) && !isCharCompatible((yyvsp[-1].argsList)->getArguments().at(2)) && !isBooleanCompatible((yyvsp[-1].argsList)->getArguments().at(2))) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack read - integer, char or boolean expected");
                fatalError = true;
            }
            else {
                (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::STACK_READ, (yyvsp[-1].argsList));
            }
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for stack read - 3 arguments expected");
        }
    }
#line 3071 "out/parser.cpp"
    break;

  case 123: /* proc_stmt: STACKWRITE LP args_list RP  */
#line 1366 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse stack write statement" << std::endl;
        #endif
        if((yyvsp[-1].argsList)->getArguments().size() == 3) {
            if(!isIntegerCompatible((yyvsp[-1].argsList)->getArguments().at(0)) || !isIntegerCompatible((yyvsp[-1].argsList)->getArguments().at(1))) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack write - first two arguments should be integers");
                fatalError = true;
            }
            else if(!isIntegerCompatible((yyvsp[-1].argsList)->getArguments().at(2)) && !isCharCompatible((yyvsp[-1].argsList)->getArguments().at(2)) && !isBooleanCompatible((yyvsp[-1].argsList)->getArguments().at(2))) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack write - third argument should be integer, char or boolean");
                fatalError = true;
            }
            else {
                (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::STACK_WRITE, (yyvsp[-1].argsList));
            }
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for stack write - 3 arguments expected");
        }
    }
#line 3097 "out/parser.cpp"
    break;

  case 124: /* args_list: args_list COMMA expression  */
#line 1390 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse args list 1" << std::endl;
        #endif
        (yyval.argsList) = (yyvsp[-2].argsList);
        (yyval.argsList)->addArgument((yyvsp[0].expressionNode));
    }
#line 3109 "out/parser.cpp"
    break;

  case 125: /* args_list: expression  */
#line 1398 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse args list 2" << std::endl;
        #endif
        (yyval.argsList) = new ast::ArgumentsListNode();
        (yyval.argsList)->addArgument((yyvsp[0].expressionNode));
    }
#line 3121 "out/parser.cpp"
    break;

  case 126: /* expression: expression GE expr  */
#line 1408 "src/yacc.y"
                       {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with greater or equal" << std::endl;
        #endif
        if((isIntegerCompatible((yyvsp[-2].expressionNode)) && isIntegerCompatible((yyvsp[0].expressionNode))) || (isBooleanCompatible((yyvsp[-2].expressionNode)) && isBooleanCompatible((yyvsp[0].expressionNode))) || (isCharCompatible((yyvsp[-2].expressionNode)) && isCharCompatible((yyvsp[0].expressionNode)))) {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::GREATER_EQUAL);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for greater or equal - matching types expected");
            fatalError = true;
        }
    }
#line 3138 "out/parser.cpp"
    break;

  case 127: /* expression: expression GT expr  */
#line 1421 "src/yacc.y"
                       {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with greater" << std::endl;
        #endif
        if((isIntegerCompatible((yyvsp[-2].expressionNode)) && isIntegerCompatible((yyvsp[0].expressionNode))) || (isBooleanCompatible((yyvsp[-2].expressionNode)) && isBooleanCompatible((yyvsp[0].expressionNode))) || (isCharCompatible((yyvsp[-2].expressionNode)) && isCharCompatible((yyvsp[0].expressionNode)))) {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::GREATER);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for greater - matching types expected");
            fatalError = true;
        }
    }
#line 3155 "out/parser.cpp"
    break;

  case 128: /* expression: expression LE expr  */
#line 1434 "src/yacc.y"
                       {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with less or equal" << std::endl;
        #endif
        if((isIntegerCompatible((yyvsp[-2].expressionNode)) && isIntegerCompatible((yyvsp[0].expressionNode))) || (isBooleanCompatible((yyvsp[-2].expressionNode)) && isBooleanCompatible((yyvsp[0].expressionNode))) || (isCharCompatible((yyvsp[-2].expressionNode)) && isCharCompatible((yyvsp[0].expressionNode)))) {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::LESS_EQUAL);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for less or equal - matching types expected");
            fatalError = true;
        }
    }
#line 3172 "out/parser.cpp"
    break;

  case 129: /* expression: expression LT expr  */
#line 1447 "src/yacc.y"
                       {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with less" << std::endl;
        #endif
        if((isIntegerCompatible((yyvsp[-2].expressionNode)) && isIntegerCompatible((yyvsp[0].expressionNode))) || (isBooleanCompatible((yyvsp[-2].expressionNode)) && isBooleanCompatible((yyvsp[0].expressionNode))) || (isCharCompatible((yyvsp[-2].expressionNode)) && isCharCompatible((yyvsp[0].expressionNode)))) {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::LESS);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for less - matching types expected");
            fatalError = true;
        }
    }
#line 3189 "out/parser.cpp"
    break;

  case 130: /* expression: expression EQUAL expr  */
#line 1460 "src/yacc.y"
                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with equal" << std::endl;
        #endif
        if((isIntegerCompatible((yyvsp[-2].expressionNode)) && isIntegerCompatible((yyvsp[0].expressionNode))) || (isBooleanCompatible((yyvsp[-2].expressionNode)) && isBooleanCompatible((yyvsp[0].expressionNode))) || (isCharCompatible((yyvsp[-2].expressionNode)) && isCharCompatible((yyvsp[0].expressionNode)))) {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::EQUAL);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for equal - matching types expected");
            fatalError = true;
        }
    }
#line 3206 "out/parser.cpp"
    break;

  case 131: /* expression: expression UNEQUAL expr  */
#line 1473 "src/yacc.y"
                            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with not equal" << std::endl;
        #endif
        if((isIntegerCompatible((yyvsp[-2].expressionNode)) && isIntegerCompatible((yyvsp[0].expressionNode))) || (isBooleanCompatible((yyvsp[-2].expressionNode)) && isBooleanCompatible((yyvsp[0].expressionNode))) || (isCharCompatible((yyvsp[-2].expressionNode)) && isCharCompatible((yyvsp[0].expressionNode)))) {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::NOT_EQUAL);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for not equal - matching types expected");
            fatalError = true;
        }

    }
#line 3224 "out/parser.cpp"
    break;

  case 132: /* expression: expr  */
#line 1487 "src/yacc.y"
         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple expression" << std::endl;
        #endif
        (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 3235 "out/parser.cpp"
    break;

  case 133: /* expr: expr PLUS term  */
#line 1496 "src/yacc.y"
                   {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with addition" << std::endl;
        #endif
        if(isIntegerCompatible((yyvsp[-2].expressionNode)) && isIntegerCompatible((yyvsp[0].expressionNode))) {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::ADDITION);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for addition - integer expected");
            fatalError = true;
        }
    }
#line 3252 "out/parser.cpp"
    break;

  case 134: /* expr: expr MINUS term  */
#line 1509 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with subtraction" << std::endl;
        #endif
        if(isIntegerCompatible((yyvsp[-2].expressionNode)) && isIntegerCompatible((yyvsp[0].expressionNode))) {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::SUBTRACTION);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for subtraction - integer expected");
            fatalError = true;
        }
    }
#line 3269 "out/parser.cpp"
    break;

  case 135: /* expr: expr OR term  */
#line 1522 "src/yacc.y"
                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with or" << std::endl;
        #endif
        if(isBooleanCompatible((yyvsp[-2].expressionNode)) && isBooleanCompatible((yyvsp[0].expressionNode))) {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::OR);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for or - boolean expected");
            fatalError = true;
        }
    }
#line 3286 "out/parser.cpp"
    break;

  case 136: /* expr: term  */
#line 1535 "src/yacc.y"
         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple term" << std::endl;
        #endif
        (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 3297 "out/parser.cpp"
    break;

  case 137: /* term: term MUL factor  */
#line 1544 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with multiplication" << std::endl;
        #endif
        if(isIntegerCompatible((yyvsp[-2].expressionNode)) && isIntegerCompatible((yyvsp[0].expressionNode))) {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::MULTIPLICATION);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for mul - integer expected");
            fatalError = true;
        }
    }
#line 3314 "out/parser.cpp"
    break;

  case 138: /* term: term DIV factor  */
#line 1557 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with division" << std::endl;
        #endif
        if(isIntegerCompatible((yyvsp[-2].expressionNode)) && isIntegerCompatible((yyvsp[0].expressionNode))) {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::DIVISION);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for div - integer expected");
            fatalError = true;
        }
    }
#line 3331 "out/parser.cpp"
    break;

  case 139: /* term: term MOD factor  */
#line 1570 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with modulus" << std::endl;
        #endif
        if(isIntegerCompatible((yyvsp[-2].expressionNode)) && isIntegerCompatible((yyvsp[0].expressionNode))) {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::MODULUS);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for mod - integer expected");
            fatalError = true;
        }
    }
#line 3348 "out/parser.cpp"
    break;

  case 140: /* term: term AND factor  */
#line 1583 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with and" << std::endl;
        #endif
        if(isBooleanCompatible((yyvsp[-2].expressionNode)) && isBooleanCompatible((yyvsp[0].expressionNode))) {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::AND);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for and - boolean expected");
            fatalError = true;
        }
    }
#line 3365 "out/parser.cpp"
    break;

  case 141: /* term: factor  */
#line 1596 "src/yacc.y"
           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple factor" << std::endl;
        #endif
        (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 3376 "out/parser.cpp"
    break;

  case 142: /* factor: identifier  */
#line 1605 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - identifier" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[0].identifierNode), ast::SpecialExpressionNode::FunctionName::VARIABLE);
    }
#line 3387 "out/parser.cpp"
    break;

  case 143: /* factor: identifier LP args_list RP  */
#line 1612 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - function call" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-3].identifierNode), (yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::CALL);
    }
#line 3398 "out/parser.cpp"
    break;

  case 144: /* factor: const_value  */
#line 1619 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - const value" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[0].constantNode), ast::SpecialExpressionNode::FunctionName::CONST);
    }
#line 3409 "out/parser.cpp"
    break;

  case 145: /* factor: LP expression RP  */
#line 1626 "src/yacc.y"
                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - parentheses" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].expressionNode), ast::SpecialExpressionNode::FunctionName::PARENTHESIS);
    }
#line 3420 "out/parser.cpp"
    break;

  case 146: /* factor: NOT factor  */
#line 1633 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - not" << std::endl;
        #endif
       if(isBooleanCompatible((yyvsp[0].expressionNode))) {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[0].expressionNode), ast::ExpressionNode::Operation::NEGATION);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for not - boolean expected");
            fatalError = true;
        }
    }
#line 3437 "out/parser.cpp"
    break;

  case 147: /* factor: MINUS factor  */
#line 1646 "src/yacc.y"
                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - negation" << std::endl;
        #endif
        if(isIntegerCompatible((yyvsp[0].expressionNode))) {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[0].expressionNode), ast::ExpressionNode::Operation::NEGATION);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for negation - integer expected");
            fatalError = true;
        }

    }
#line 3455 "out/parser.cpp"
    break;

  case 148: /* factor: factor LB expression RB  */
#line 1661 "src/yacc.y"
                            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - array access" << std::endl;
        #endif
        if(!isArrayCompatible((yyvsp[-3].expressionNode))) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for array access - array expected");
            fatalError = true;
        }
        else if(!isArrayIndexCompatible((yyvsp[-3].expressionNode), (yyvsp[-1].expressionNode))) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for array index");
            fatalError = true;
        }
        else {
            (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-3].expressionNode), (yyvsp[-1].expressionNode), ast::SpecialExpressionNode::FunctionName::ARRAY_ACCESS);
        }
    }
#line 3476 "out/parser.cpp"
    break;

  case 149: /* factor: factor DOT identifier  */
#line 1679 "src/yacc.y"
                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - record access" << std::endl;
        #endif
        if(!isRecordCompatible((yyvsp[-2].expressionNode))) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for record access - record expected");
            fatalError = true;
        }
        else if(!isRecordFieldCompatible((yyvsp[-2].expressionNode), (yyvsp[0].identifierNode))) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for record field");
            fatalError = true;
        }
        else {
            (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].identifierNode), ast::SpecialExpressionNode::FunctionName::RECORD_ACCESS);
        }
    }
#line 3497 "out/parser.cpp"
    break;

  case 150: /* factor: ABS LP args_list RP  */
#line 1696 "src/yacc.y"
                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - abs" << std::endl;
        #endif
        if((yyvsp[-1].argsList)->getArguments().size() != 1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for abs");
            fatalError = true;
        }
        else {
            ast::ExpressionNode* arg = (yyvsp[-1].argsList)->getArguments().front();
            if(isIntegerCompatible(arg)) {
                (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::ABS);
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for abs - integer expected");
                fatalError = true;
            }
        }
    }
#line 3521 "out/parser.cpp"
    break;

  case 151: /* factor: CHR LP args_list RP  */
#line 1716 "src/yacc.y"
                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - chr" << std::endl;
        #endif
        if((yyvsp[-1].argsList)->getArguments().size() != 1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for chr");
            fatalError = true;
        }
        else {
            ast::ExpressionNode* arg = (yyvsp[-1].argsList)->getArguments().front();
            if(isIntegerCompatible(arg)) {
                (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::CHR);
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for chr - integer expected");
                fatalError = true;
            }
        }
    }
#line 3545 "out/parser.cpp"
    break;

  case 152: /* factor: ODD LP args_list RP  */
#line 1736 "src/yacc.y"
                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - odd" << std::endl;
        #endif
        if((yyvsp[-1].argsList)->getArguments().size() != 1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for odd");
            fatalError = true;
        }
        else {
            ast::ExpressionNode* arg = (yyvsp[-1].argsList)->getArguments().front();
            if(isIntegerCompatible(arg)) {
                (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::ODD);
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for odd - integer expected");
                fatalError = true;
            }
        }
    }
#line 3569 "out/parser.cpp"
    break;

  case 153: /* factor: ORD LP args_list RP  */
#line 1756 "src/yacc.y"
                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - ord" << std::endl;
        #endif
        if((yyvsp[-1].argsList)->getArguments().size() != 1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for ord");
            fatalError = true;
        }
        else {
            ast::ExpressionNode* arg = (yyvsp[-1].argsList)->getArguments().front();
            if(isCharCompatible(arg)) {
                (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::ORD);
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for ord - char expected");
                fatalError = true;
            }
        }
    }
#line 3593 "out/parser.cpp"
    break;

  case 154: /* factor: PRED LP args_list RP  */
#line 1776 "src/yacc.y"
                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - pred" << std::endl;
        #endif
        if((yyvsp[-1].argsList)->getArguments().size() != 1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for pred");
            fatalError = true;
        }
        else {
            ast::ExpressionNode* arg = (yyvsp[-1].argsList)->getArguments().front();
            if(isIntegerCompatible(arg) || isCharCompatible(arg)) {
                (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::PRED);
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for pred - integer or char expected");
                fatalError = true;
            }
        }
    }
#line 3617 "out/parser.cpp"
    break;

  case 155: /* factor: SUCC LP args_list RP  */
#line 1796 "src/yacc.y"
                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - succ" << std::endl;
        #endif
        if((yyvsp[-1].argsList)->getArguments().size() != 1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for succ");
            fatalError = true;
        }
        else {
            ast::ExpressionNode* arg = (yyvsp[-1].argsList)->getArguments().front();
            if(isIntegerCompatible(arg) || isCharCompatible(arg)) {
                (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::SUCC);
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for succ - integer or char expected");
                fatalError = true;
            }
        }
    }
#line 3641 "out/parser.cpp"
    break;


#line 3645 "out/parser.cpp"

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

#line 1816 "src/yacc.y"


void yyerror(const char *s) {
    std::cerr << "Error: " << s << " at line " << linesCounter << std::endl;
    fatalError = true;
}

bool parse(const std::string& inputFileName, std::vector<std::string>& errors, std::unique_ptr<ast::ProgramNode>& program) {
    yyin = fopen(inputFileName.c_str(), "r");

    if(yyin == nullptr) {
        std::cerr << "Cannot open file " << inputFileName << std::endl;
    }

    yyparse();
    fclose(yyin);

    errors = std::move(parsingErrors);
    program = std::unique_ptr<ast::ProgramNode>(resultAst);
    return !fatalError;
}

bool nameAlreadyUsed(std::string name) {
    return ctx->getLookupTable().isVariableDefined(name, "") || ctx->getLookupTable().isRoutineDefined(name, "") || ctx->getLookupTable().isTypeDefined(name, "");
}

void saveType(ast::IdentifierNode* typeName, ast::TypeNode* typeDef) {
    if(nameAlreadyUsed(typeName->getName())) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", name `" + typeName->getName() + "` already used");
    } else {
        ctx->getLookupTable().defineType(LookupTable::TypeCategory::SIMPLE, typeName->getName(), getTypeString(typeDef));
    }
}

void saveConstant(ast::IdentifierNode* constName, ast::ConstantNode* constDef) {
    if(nameAlreadyUsed(constName->getName())) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", name `" + constName->getName() + "` already used");
    } else {
        ctx->getLookupTable().defineVariable(LookupTable::VariableCategory::CONSTANT, constName->getName(), getTypeString(constDef->getConstantType()));
        ctx->getLookupTable().setVariableValue(constName->getName(), getConstantString(constDef));
    }
}

void saveVariables(std::vector<ast::IdentifierNode*>* varNames, ast::TypeNode* typeDef) {
    for(auto& varName : *varNames) {
        if(nameAlreadyUsed(varName->getName())) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", name `" + varName->getName() + "` already used");
        } else {
            ctx->getLookupTable().defineVariable(LookupTable::VariableCategory::VARIABLE, varName->getName(), getTypeString(typeDef));
        }
    }
}

void saveRoutine(ast::RoutineDeclarationNode* routineDef) {
    if(nameAlreadyUsed(routineDef->getName())) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", name `" + routineDef->getName() + "` already used");
    } else {
        std::vector<std::pair<std::string, std::string>> arguments;
        for(const auto& paramGroup : *routineDef->getParams()->getParams()) {
            std::string typeString = getTypeString(paramGroup->getParamsType().get());
            for(const auto& param : *paramGroup->getParams()) {
                arguments.emplace_back(param->getName(), typeString);
            }
        }

        if(routineDef->getRoutineType() == ast::RoutineDeclarationNode::RoutineType::PROCEDURE) {
            ctx->getLookupTable().defineRoutine(LookupTable::RoutineCategory::PROCEDURE, routineDef->getName(),
                arguments, "void", "");
        }
        else {
            ctx->getLookupTable().defineRoutine(LookupTable::RoutineCategory::FUNCTION, routineDef->getName(),
                arguments, getTypeString(routineDef->getReturnType().get()), "");
        }
    }
}

std::string getTypeString(ast::TypeNode* type) {
    if(type->getTypeType() == ast::TypeNode::TypeType::SIMPLE) {
        auto* simpleType = dynamic_cast<ast::SimpleTypeNode*>(type);
        switch(simpleType->getRepresentation()) {
            case ast::SimpleTypeNode::Representation::INTEGER:
                return "integer";
            case ast::SimpleTypeNode::Representation::UNSIGNED:
                return "unsigned";
            case ast::SimpleTypeNode::Representation::BOOLEAN:
                return "boolean";
            case ast::SimpleTypeNode::Representation::CHAR:
                return "char";
            case ast::SimpleTypeNode::Representation::STRING:
                return "string";
            case ast::SimpleTypeNode::Representation::RENAMING: {
                auto* renamingType = dynamic_cast<ast::RenameTypeNode*>(type);
                if(!ctx->getLookupTable().isTypeDefined(renamingType->getIdentifier()->getName(), "")) {
                    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", unknown type `" + renamingType->getIdentifier()->getName() + "`");
                    return "unspecified";
                }
                return ctx->getLookupTable().getType(renamingType->getIdentifier()->getName(), "").type;
             }
            case ast::SimpleTypeNode::Representation::ENUMERATION: {
                auto* enumType = dynamic_cast<ast::EnumerationTypeNode*>(type);
                std::string mergedEnum = "enum@";
                for(auto& identifier : *enumType->getIdentifiers()) {
                    mergedEnum += identifier->getName() + "@";
                }
                return mergedEnum;
            }
            case ast::SimpleTypeNode::Representation::CONST_RANGE: {
                auto* rangeType = dynamic_cast<ast::ConstRangeTypeNode*>(type);
                return "constrange@" + getConstantString(rangeType->getLowerBound().get()) + ".." + getConstantString(rangeType->getUpperBound().get());
            }
            case ast::SimpleTypeNode::Representation::VAR_RANGE: {
                auto* rangeType = dynamic_cast<ast::VarRangeTypeNode*>(type);
                std::string lb = rangeType->getLowerBound()->getName();
                std::string ub = rangeType->getUpperBound()->getName();

                auto properEnums = ctx->getLookupTable().getTypes(
                [&](const std::string&, const LookupTable::TypeInfo& tf) {
                    return tf.alive && tf.type.find("enum@") == 0 && tf.type.find("@" + lb + "@") != std::string::npos && tf.type.find("@" + ub + "@") != std::string::npos;
                });

                if(properEnums.empty()) {
                    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + lb + " and " + ub + " are not in any enum");
                    return "unspecified";
                }
                else if(properEnums.size() > 1) {
                    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + lb + " and " + ub + " are in more than one enum");
                    return "unspecified";
                }

                return "enumrange@" + properEnums.front().name + "@"  + lb + ".." + ub;
            }
            default:
                return "unspecified";
        }
    }
    else if(type->getTypeType() == ast::TypeNode::TypeType::ARRAY) {
        auto* arrayType = dynamic_cast<ast::ArrayTypeNode*>(type);

        std::string elementTypeName = getTypeString(arrayType->getElementType().get());
        std::string rangeTypeName = getTypeString(arrayType->getRange().get());

        return "array@@" + rangeTypeName + "@" + elementTypeName + "@@";
    }
    else if(type->getTypeType() == ast::TypeNode::TypeType::RECORD) {
        auto* recordType = dynamic_cast<ast::RecordTypeNode*>(type);

        std::string mergedRecord = "record@@";
        for(auto& field : *recordType->getFields()) {
            for(auto& identifier : *field->first) {
                mergedRecord += identifier->getName() + "#" + getTypeString(field->second) + "@";
            }
        }

        return mergedRecord + "@@";
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
    return type == "integer" || type == "unsigned" || type == "boolean" || type == "char";
}

bool isIntegerCompatible(ast::ExpressionNode* expr) {
    return true;
}

bool isCharCompatible(ast::ExpressionNode* expr) {
    return true;
}

bool isStringCompatible(ast::ExpressionNode* expr) {
    return true;
}

bool isBooleanCompatible(ast::ExpressionNode* expr) {
    return true;
}

bool isArrayIndexCompatible(ast::ExpressionNode* array, ast::ExpressionNode* index) {
    return true;
}

bool isArrayCompatible(ast::ExpressionNode* expr) {
    return true;
}

bool isRecordCompatible(ast::ExpressionNode* expr) {
    return true;
}

bool isRecordFieldCompatible(ast::ExpressionNode* record, ast::IdentifierNode* field) {
    return true;
}

bool isLeftValueCompatible(ast::ExpressionNode* expr) {
    if(expr->getOperation() != ast::ExpressionNode::Operation::SPECIAL) {
        return false;
    }

    auto* special = dynamic_cast<ast::SpecialExpressionNode*>(expr);

    if(special->getFunctionName() == ast::SpecialExpressionNode::FunctionName::VARIABLE) {
        auto* var = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
        return ctx->getLookupTable().isVariableDefined(var->getName(), "");
    }
    else if(special->getFunctionName() == ast::SpecialExpressionNode::FunctionName::RECORD_ACCESS) {
        //auto* record = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
        //auto* field = dynamic_cast<ast::IdentifierNode*>(special->getArgument2().get());
        //return ctx->getLookupTable().isTypeDefined(record->getName(), "");
        return true;
    }
    else if(special->getFunctionName() == ast::SpecialExpressionNode::FunctionName::ARRAY_ACCESS) {
        //auto* array = dynamic_cast<ast::ExpressionNode*>(special->getArgument1().get());
        //auto* index = dynamic_cast<ast::ExpressionNode*>(special->getArgument2().get());
        //return ctx->getLookupTable().isVariableDefined(array->getName(), "");
        return true;
    }
    else {
        return false;
    }
}
