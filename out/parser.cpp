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


#line 108 "out/parser.cpp"

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
#define YYLAST   598

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
       0,   187,   187,   198,   210,   222,   236,   245,   254,   261,
     272,   283,   294,   307,   319,   332,   345,   360,   375,   387,
     400,   413,   428,   441,   449,   458,   466,   476,   483,   492,
     499,   508,   516,   526,   536,   549,   556,   566,   574,   584,
     594,   607,   614,   621,   629,   640,   647,   654,   661,   670,
     677,   686,   695,   706,   716,   729,   736,   743,   752,   761,
     769,   779,   786,   796,   805,   812,   819,   826,   833,   840,
     847,   854,   863,   871,   881,   891,   900,   907,   917,   924,
     932,   943,   951,   960,   967,   974,   981,   988,   995,  1002,
    1009,  1016,  1023,  1030,  1039,  1046,  1053,  1062,  1071,  1078,
    1088,  1095,  1104,  1111,  1119,  1128,  1137,  1145,  1155,  1162,
    1169,  1178,  1185,  1194,  1201,  1208,  1218,  1225,  1232,  1239,
    1246,  1253,  1260,  1267,  1276,  1284,  1294,  1301,  1308,  1315,
    1322,  1329,  1336,  1345,  1352,  1359,  1366,  1375,  1382,  1389,
    1396,  1403,  1412,  1419,  1426,  1433,  1440,  1447,  1454,  1461,
    1468,  1475,  1482,  1489,  1496,  1503
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

#define YYPACT_NINF (-186)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      31,    30,    17,    -4,  -186,    40,    57,    -7,    78,    87,
    -186,    40,  -186,    48,    64,  -186,  -186,  -186,  -186,    40,
      95,  -186,    28,  -186,   329,    40,  -186,    71,    40,     3,
    -186,  -186,  -186,  -186,  -186,  -186,     6,    58,  -186,    63,
      79,  -186,   127,   132,   134,   135,   144,   150,   529,  -186,
     529,   529,    40,   133,  -186,  -186,     8,  -186,    69,  -186,
    -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,   456,
      40,  -186,   -39,  -186,   137,   161,     3,  -186,     5,  -186,
      20,  -186,  -186,  -186,   419,   529,   529,   529,   529,   529,
     529,   529,   157,   158,   160,   162,   170,   172,   537,   529,
     529,  -186,    27,   284,    45,    66,  -186,   359,   181,   168,
     153,  -186,   529,   529,   529,    40,  -186,    40,  -186,  -186,
    -186,  -186,   175,    40,   171,   174,  -186,  -186,  -186,   180,
    -186,    40,   456,   178,   178,  -186,  -186,    57,   183,    57,
     184,  -186,   187,    39,   267,    51,    67,    77,    84,    85,
     529,   529,   529,   529,   529,   529,  -186,  -186,  -186,  -186,
     213,   529,   529,    40,   389,   529,   529,   529,   529,   529,
     529,   215,   529,   529,   529,   529,   529,   529,   529,   529,
     389,    38,   529,   267,   241,    91,   201,   100,   468,    50,
    -186,     4,    28,  -186,    40,  -186,   190,    14,   188,  -186,
     191,  -186,   200,  -186,  -186,  -186,   529,  -186,  -186,  -186,
    -186,  -186,   108,   111,   119,   120,   125,   128,  -186,   298,
     142,  -186,   215,    45,    45,    45,    45,    45,    45,   389,
    -186,    66,    66,    66,  -186,  -186,  -186,  -186,   267,  -186,
     389,   197,   198,    21,  -186,   530,   216,  -186,   529,  -186,
     207,  -186,  -186,   456,  -186,  -186,  -186,    40,    22,  -186,
      11,   468,  -186,  -186,   267,  -186,  -186,  -186,  -186,  -186,
    -186,  -186,  -186,  -186,  -186,   206,   389,   389,  -186,  -186,
     529,   529,   529,   267,   204,   210,    89,  -186,    14,   468,
    -186,  -186,   211,   217,   453,   465,   267,   456,  -186,   468,
    -186,  -186,  -186,  -186,   389,   389,  -186,  -186,  -186,  -186
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
       0,     0,     0,     0,   103,     0,     0,     0,     0,     0,
       0,   100,     0,     0,     0,     0,     0,     0,     0,     0,
     103,     0,     0,    94,     0,     0,     0,     0,     0,     0,
      60,     0,     0,    53,     0,    72,    34,     0,     0,    22,
      14,    15,    20,    19,   115,   117,     0,   119,   120,   121,
     122,   123,     0,     0,     0,     0,     0,     0,   145,     0,
       0,   149,   100,   130,   131,   126,   127,   128,   129,   103,
      99,   133,   134,   135,   137,   138,   140,   139,   102,   104,
     103,     0,     0,     0,   107,     0,     0,   114,     0,    65,
       0,    58,    59,     0,    66,    67,    33,     0,     0,    26,
       0,     0,    13,    18,   124,   150,   151,   152,   153,   154,
     155,   148,   143,    98,   101,     0,   103,   103,   105,   106,
       0,     0,     0,    96,     0,    62,     0,    24,     0,     0,
      17,   110,     0,     0,     0,     0,    95,     0,    61,     0,
      25,    28,   108,   109,   103,   103,    63,    27,   111,   112
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -186,  -186,    15,  -186,  -186,   194,  -186,   203,  -186,   147,
    -186,    -6,  -186,  -186,   227,  -186,  -186,   280,   -21,  -186,
    -186,   273,  -128,  -186,  -186,   113,  -186,  -185,  -108,    -5,
    -186,   311,   272,   -98,   239,  -186,  -186,  -186,   103,  -186,
    -186,  -186,  -186,    83,  -186,  -186,    47,   -38,   221,    -9,
     -69
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     7,     8,    76,    77,    78,    79,    80,   198,
     258,   259,    29,    70,    71,     9,    11,    12,   101,    20,
      25,    26,   125,   126,   189,   190,   127,   128,    72,   102,
      17,    57,    24,    58,    59,    60,    61,    62,   230,    63,
      64,    65,   243,   244,    66,    67,   143,   144,   104,   105,
     106
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      13,    37,     5,   250,   196,   171,    13,    74,    75,   187,
     103,     5,   108,   109,    27,   191,   142,     4,    81,    56,
      27,    14,   257,    73,    82,    10,     5,   131,   132,   158,
     159,   278,    10,    30,     1,    31,    32,    33,    34,    35,
      30,     3,    31,    32,    33,    34,    35,   110,   124,    10,
      30,    10,    31,    32,    33,    34,    35,    15,   112,     6,
     251,    10,   160,     5,   129,    73,   222,   113,   137,   114,
     131,   253,   115,    36,   183,   184,   290,   131,   289,    56,
      36,   191,   239,   139,   287,   288,   161,    16,   162,   260,
      36,   163,    22,   138,    19,   140,   172,   173,    56,   240,
     174,   205,    56,    28,   301,   206,   234,   235,   236,   237,
     186,   124,    73,   207,   307,    69,   240,   206,    73,   175,
     176,    83,   177,   219,   178,   285,   195,   129,    23,   208,
      84,   274,   116,   206,   145,   146,   147,   148,   149,   209,
      85,   238,   275,   206,   245,   111,   210,   211,   133,   286,
     206,   206,   200,   247,   202,   131,   299,   206,   221,    56,
     241,   185,   249,   231,   232,   233,   131,   124,   264,   306,
     265,   254,   134,   266,   206,    56,   242,   206,   292,   293,
     260,   267,   268,   129,    73,   206,   206,   269,    86,   255,
     270,   206,    73,    87,   206,    88,    89,   212,   213,   214,
     215,   216,   217,   182,   272,    90,   308,   309,   206,   220,
     283,    91,   165,   166,   167,   168,   169,   170,   150,   151,
     180,   152,   241,   153,    56,   165,   166,   167,   168,   169,
     170,   154,   124,   155,   188,    56,   192,   193,   242,   197,
     124,   181,   294,   295,   296,   194,   201,   203,   129,   204,
     229,   248,    73,   256,   262,   261,   129,   165,   166,   167,
     168,   169,   170,   263,   276,   277,   282,   284,   124,   291,
     135,    56,    56,   298,   302,   218,   124,   297,   124,   136,
     303,   199,   300,    73,   129,   165,   166,   167,   168,   169,
     170,    21,   129,    16,   129,    10,    39,   130,    68,    56,
      56,   246,   252,    40,    41,    42,    43,    44,    45,    46,
      47,   165,   166,   167,   168,   169,   170,    48,   164,    18,
      49,   107,    50,   141,    51,   273,   279,    52,   165,   166,
     167,   168,   169,   170,     0,     0,     0,     0,    16,    38,
      10,    39,   165,   166,   167,   168,   169,   170,    40,    41,
      42,    43,    44,    45,    46,    47,     0,     0,   271,    53,
      54,    55,    48,     0,     0,    49,     0,    50,    16,    51,
      10,    39,    52,     0,     0,     0,     0,     0,    40,    41,
      42,    43,    44,    45,    46,    47,   223,   224,   225,   226,
     227,   228,    48,     0,     0,    49,   179,    50,    16,    51,
      10,    39,    52,     0,    53,    54,    55,     0,    40,    41,
      42,    43,    44,    45,    46,    47,     0,     0,     0,     0,
       0,     0,    48,     0,     0,    49,     0,    50,    16,    51,
      10,     0,    52,     0,    53,    54,    55,     0,    40,    41,
      42,    43,    44,    45,    46,    47,     0,     0,     0,     0,
       0,     0,    48,     0,     0,    49,     0,    50,     0,    51,
       0,     0,    52,     0,    53,    54,    55,    10,    30,     0,
      31,    32,    33,    34,    35,     0,     0,     0,     0,    10,
      30,     0,    31,    32,    33,    34,    35,     0,     0,     0,
       0,     0,   304,     0,    53,    54,    55,   165,   166,   167,
     168,   169,   170,     0,   305,     0,     0,     0,    36,   165,
     166,   167,   168,   169,   170,     0,     0,   117,     0,     0,
      36,     0,     0,     0,   118,   119,   120,   121,   122,   117,
     123,     0,     0,     0,     0,     0,   118,   119,   120,   121,
      10,    30,     0,    31,    32,    33,    34,    35,    10,   156,
       0,    31,    32,    33,    34,   157,    92,    93,    94,    95,
      96,    97,     0,     0,    92,    93,    94,    95,    96,    97,
       0,   280,   281,     0,   165,   166,   167,   168,   169,   170,
       0,    98,     0,     0,     0,     0,    99,     0,     0,    98,
     100,     0,     0,     0,    99,     0,     0,     0,   100
};

static const yytype_int16 yycheck[] =
{
       5,    22,     6,   188,   132,   103,    11,     4,     5,   117,
      48,     6,    50,    51,    19,   123,    85,     0,    12,    24,
      25,     6,     8,    28,    18,    11,     6,    66,    67,    98,
      99,    10,    11,    12,     3,    14,    15,    16,    17,    18,
      12,    11,    14,    15,    16,    17,    18,    52,    69,    11,
      12,    11,    14,    15,    16,    17,    18,    64,    50,    63,
      10,    11,   100,     6,    69,    70,   164,    59,    63,    61,
      66,    67,    64,    52,   112,   113,   261,    66,    67,    84,
      52,   189,   180,    63,    62,    63,    59,     9,    61,   197,
      52,    64,    44,    78,     7,    80,    51,    52,   103,    78,
      55,    62,   107,     8,   289,    66,   175,   176,   177,   178,
     115,   132,   117,    62,   299,    44,    78,    66,   123,    53,
      54,    63,    56,   161,    58,   253,   131,   132,    64,    62,
      67,   229,    63,    66,    87,    88,    89,    90,    91,    62,
      61,   179,   240,    66,   182,    12,    62,    62,    11,   257,
      66,    66,   137,    62,   139,    66,    67,    66,   163,   164,
     181,   114,    62,   172,   173,   174,    66,   188,   206,   297,
      62,   192,    11,    62,    66,   180,   181,    66,   276,   277,
     288,    62,    62,   188,   189,    66,    66,    62,    61,   194,
      62,    66,   197,    61,    66,    61,    61,   150,   151,   152,
     153,   154,   155,    50,    62,    61,   304,   305,    66,   162,
     248,    61,    44,    45,    46,    47,    48,    49,    61,    61,
      39,    61,   243,    61,   229,    44,    45,    46,    47,    48,
      49,    61,   253,    61,    59,   240,    65,    63,   243,    61,
     261,    73,   280,   281,   282,    65,    63,    63,   253,    62,
      35,    50,   257,    63,    63,    67,   261,    44,    45,    46,
      47,    48,    49,    63,    67,    67,    50,    60,   289,    63,
      76,   276,   277,    63,    63,    62,   297,    73,   299,    76,
      63,   134,   288,   288,   289,    44,    45,    46,    47,    48,
      49,    11,   297,     9,   299,    11,    12,    70,    25,   304,
     305,    60,   189,    19,    20,    21,    22,    23,    24,    25,
      26,    44,    45,    46,    47,    48,    49,    33,    34,     8,
      36,    49,    38,    84,    40,   222,   243,    43,    44,    45,
      46,    47,    48,    49,    -1,    -1,    -1,    -1,     9,    10,
      11,    12,    44,    45,    46,    47,    48,    49,    19,    20,
      21,    22,    23,    24,    25,    26,    -1,    -1,    60,    75,
      76,    77,    33,    -1,    -1,    36,    -1,    38,     9,    40,
      11,    12,    43,    -1,    -1,    -1,    -1,    -1,    19,    20,
      21,    22,    23,    24,    25,    26,   165,   166,   167,   168,
     169,   170,    33,    -1,    -1,    36,    37,    38,     9,    40,
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
      -1,    41,    42,    -1,    44,    45,    46,    47,    48,    49,
      -1,    52,    -1,    -1,    -1,    -1,    57,    -1,    -1,    52,
      61,    -1,    -1,    -1,    57,    -1,    -1,    -1,    61
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
     127,    59,    61,    64,    34,    44,    45,    46,    47,    48,
      49,   113,    51,    52,    55,    53,    54,    56,    58,    37,
      39,    73,    50,   127,   127,   126,   109,   108,    59,   104,
     105,   108,    65,    63,    65,   109,   102,    61,    89,    89,
      82,    63,    82,    63,    62,    62,    66,    62,    62,    62,
      62,    62,   126,   126,   126,   126,   126,   126,    62,   127,
     126,   109,   113,   128,   128,   128,   128,   128,   128,    35,
     118,   129,   129,   129,   130,   130,   130,   130,   127,   113,
      78,    98,   109,   122,   123,   127,    60,    62,    50,    62,
     107,    10,   105,    67,    98,   109,    63,     8,    90,    91,
     108,    67,    63,    63,   127,    62,    62,    62,    62,    62,
      62,    60,    62,   118,   113,   113,    67,    67,    10,   123,
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
#line 187 "src/yacc.y"
                                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse program 1: " << (*(yyvsp[-3].token).stringValue) << std::endl;
        #endif

        std::string name{*(yyvsp[-3].token).stringValue};
        (yyvsp[-1].routineNode)->setSubType(ast::RoutineNode::SubType::MAIN);
        (yyval.programNode) = new ast::ProgramNode(std::move(name), (yyvsp[-1].routineNode));
        resultAst = (yyval.programNode);
    }
#line 1511 "out/parser.cpp"
    break;

  case 3: /* program: PROGRAM IDENT_NAME SEMICOLON routine  */
#line 198 "src/yacc.y"
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
#line 1527 "out/parser.cpp"
    break;

  case 4: /* program: PROGRAM IDENT_NAME routine DOT  */
#line 210 "src/yacc.y"
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
#line 1543 "out/parser.cpp"
    break;

  case 5: /* program: PROGRAM IDENT_NAME routine  */
#line 222 "src/yacc.y"
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
#line 1559 "out/parser.cpp"
    break;

  case 6: /* routine: routine_head routine_body  */
#line 236 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine" << std::endl;
        #endif
        (yyval.routineNode) = new ast::RoutineNode((yyvsp[-1].routineHeadNode), (yyvsp[0].routineBodyNode));
    }
#line 1570 "out/parser.cpp"
    break;

  case 7: /* routine_head: const_part type_part var_part routine_part  */
#line 245 "src/yacc.y"
                                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine head" << std::endl;
        #endif
        (yyval.routineHeadNode) = new ast::RoutineHeadNode((yyvsp[-3].constPartList), (yyvsp[-2].typePartList), (yyvsp[-1].varPartList), (yyvsp[0].routinePartList));
    }
#line 1581 "out/parser.cpp"
    break;

  case 8: /* routine_part: %empty  */
#line 254 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty routine part" << std::endl;
        #endif
        (yyval.routinePartList) = new std::vector<ast::RoutineDeclarationNode*>();
    }
#line 1592 "out/parser.cpp"
    break;

  case 9: /* routine_part: routine_part fun_decl  */
#line 261 "src/yacc.y"
                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine part with fun decl 1 " << (yyvsp[0].routineDeclarationNode)->getName() << std::endl;
        #endif

        saveRoutine((yyvsp[0].routineDeclarationNode));

        (yyval.routinePartList) = (yyvsp[-1].routinePartList);
        (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1607 "out/parser.cpp"
    break;

  case 10: /* routine_part: routine_part proc_decl  */
#line 272 "src/yacc.y"
                           {
       #ifdef YACC_DEBUG
           std::cout << "Yacc debug: Parse routine part with proc decl 1 " << (yyvsp[0].routineDeclarationNode)->getName() << std::endl;
       #endif

       saveRoutine((yyvsp[0].routineDeclarationNode));

       (yyval.routinePartList) = (yyvsp[-1].routinePartList);
       (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1622 "out/parser.cpp"
    break;

  case 11: /* routine_part: fun_decl  */
#line 283 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine part with fun decl 2 " << (yyvsp[0].routineDeclarationNode)->getName() << std::endl;
        #endif

        saveRoutine((yyvsp[0].routineDeclarationNode));

        (yyval.routinePartList) = new std::vector<ast::RoutineDeclarationNode*>();
        (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1637 "out/parser.cpp"
    break;

  case 12: /* routine_part: proc_decl  */
#line 294 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine part with proc decl 2 " << (yyvsp[0].routineDeclarationNode)->getName() << std::endl;
        #endif

        saveRoutine((yyvsp[0].routineDeclarationNode));

        (yyval.routinePartList) = new std::vector<ast::RoutineDeclarationNode*>();
        (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1652 "out/parser.cpp"
    break;

  case 13: /* fun_decl: fun_head SEMICOLON routine SEMICOLON  */
#line 307 "src/yacc.y"
                                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun decl 1" << std::endl;
        #endif

        ctx->getLookupTable().popScope();

        (yyval.routineDeclarationNode) = (yyvsp[-3].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[-1].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
    }
#line 1668 "out/parser.cpp"
    break;

  case 14: /* fun_decl: fun_head SEMICOLON routine  */
#line 319 "src/yacc.y"
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
#line 1685 "out/parser.cpp"
    break;

  case 15: /* fun_decl: fun_head routine SEMICOLON  */
#line 332 "src/yacc.y"
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
#line 1702 "out/parser.cpp"
    break;

  case 16: /* fun_decl: fun_head routine  */
#line 345 "src/yacc.y"
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
#line 1719 "out/parser.cpp"
    break;

  case 17: /* fun_head: FUNCTION IDENT_NAME params COLON simple_type  */
#line 360 "src/yacc.y"
                                                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun head " << (*(yyvsp[-3].token).stringValue) << std::endl;
        #endif

        ctx->getLookupTable().pushScope(*(yyvsp[-3].token).stringValue);

        std::string name{*(yyvsp[-3].token).stringValue};
        (yyval.routineDeclarationNode) = new ast::RoutineDeclarationNode(ast::RoutineDeclarationNode::RoutineType::FUNCTION, std::move(name), (yyvsp[-2].paramsNode), (yyvsp[0].simpleTypeNode), nullptr);


    }
#line 1736 "out/parser.cpp"
    break;

  case 18: /* proc_decl: proc_head SEMICOLON routine SEMICOLON  */
#line 375 "src/yacc.y"
                                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse proc decl" << std::endl;
        #endif

        ctx->getLookupTable().popScope();

        (yyval.routineDeclarationNode) = (yyvsp[-3].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[-1].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::PROCEDURE);
    }
#line 1752 "out/parser.cpp"
    break;

  case 19: /* proc_decl: proc_head routine SEMICOLON  */
#line 387 "src/yacc.y"
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
#line 1769 "out/parser.cpp"
    break;

  case 20: /* proc_decl: proc_head SEMICOLON routine  */
#line 400 "src/yacc.y"
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
#line 1786 "out/parser.cpp"
    break;

  case 21: /* proc_decl: proc_head routine  */
#line 413 "src/yacc.y"
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
#line 1803 "out/parser.cpp"
    break;

  case 22: /* proc_head: PROCEDURE IDENT_NAME params  */
#line 428 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse proc head " << (*(yyvsp[-1].token).stringValue) << std::endl;
        #endif

        ctx->getLookupTable().pushScope(*(yyvsp[-1].token).stringValue);

        std::string name{*(yyvsp[-1].token).stringValue};
        (yyval.routineDeclarationNode) = new ast::RoutineDeclarationNode(ast::RoutineDeclarationNode::RoutineType::PROCEDURE, std::move(name), (yyvsp[0].paramsNode), nullptr, nullptr);
    }
#line 1818 "out/parser.cpp"
    break;

  case 23: /* params: %empty  */
#line 441 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty params" << std::endl;
        #endif
        std::vector<ast::ParamsGroupNode *>* emptyParamsList = new std::vector<ast::ParamsGroupNode*>();
        (yyval.paramsNode) = new ast::ParamsNode(emptyParamsList);
    }
#line 1830 "out/parser.cpp"
    break;

  case 24: /* params: LP params_decl RP  */
#line 449 "src/yacc.y"
                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params" << std::endl;
        #endif
        (yyval.paramsNode) = new ast::ParamsNode((yyvsp[-1].paramsGroupList));
    }
#line 1841 "out/parser.cpp"
    break;

  case 25: /* params_decl: params_decl SEMICOLON params_type  */
#line 458 "src/yacc.y"
                                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params decl 1" << std::endl;
        #endif
        (yyval.paramsGroupList) = (yyvsp[-2].paramsGroupList);
        (yyval.paramsGroupList)->push_back((yyvsp[0].paramsGroupNode));
    }
#line 1853 "out/parser.cpp"
    break;

  case 26: /* params_decl: params_type  */
#line 466 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params decl 2" << std::endl;
        #endif
        (yyval.paramsGroupList) = new std::vector<ast::ParamsGroupNode*>();
        (yyval.paramsGroupList)->push_back((yyvsp[0].paramsGroupNode));
    }
#line 1865 "out/parser.cpp"
    break;

  case 27: /* params_type: VAR name_list COLON simple_type  */
#line 476 "src/yacc.y"
                                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params type 1" << std::endl;
        #endif
        (yyval.paramsGroupNode) = new ast::ParamsGroupNode(ast::ParamsGroupNode::PassType::PASS_BY_REFERENCE, (yyvsp[-2].identifierList), (yyvsp[0].simpleTypeNode));
    }
#line 1876 "out/parser.cpp"
    break;

  case 28: /* params_type: name_list COLON simple_type  */
#line 483 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params type 2" << std::endl;
        #endif
        (yyval.paramsGroupNode) = new ast::ParamsGroupNode(ast::ParamsGroupNode::PassType::PASS_BY_VALUE, (yyvsp[-2].identifierList), (yyvsp[0].simpleTypeNode));
    }
#line 1887 "out/parser.cpp"
    break;

  case 29: /* var_part: %empty  */
#line 492 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty var part" << std::endl;
        #endif
        (yyval.varPartList) = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
    }
#line 1898 "out/parser.cpp"
    break;

  case 30: /* var_part: VAR var_decl_list  */
#line 499 "src/yacc.y"
                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var part" << std::endl;
        #endif
        (yyval.varPartList) = (yyvsp[0].varPartList);
    }
#line 1909 "out/parser.cpp"
    break;

  case 31: /* var_decl_list: var_decl_list var_decl  */
#line 508 "src/yacc.y"
                           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl list 1" << std::endl;
        #endif
        (yyval.varPartList) = (yyvsp[-1].varPartList);
        (yyval.varPartList)->push_back((yyvsp[0].varPartListElement));
    }
#line 1921 "out/parser.cpp"
    break;

  case 32: /* var_decl_list: var_decl  */
#line 516 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl list 2" << std::endl;
        #endif
        (yyval.varPartList) = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
        (yyval.varPartList)->push_back((yyvsp[0].varPartListElement));
    }
#line 1933 "out/parser.cpp"
    break;

  case 33: /* var_decl: name_list COLON type_decl SEMICOLON  */
#line 526 "src/yacc.y"
                                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl 1" << std::endl;
        #endif

        saveVariables((yyvsp[-3].identifierList), (yyvsp[-1].typeNode));

        (yyval.varPartListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-3].identifierList), (yyvsp[-1].typeNode));
    }
#line 1947 "out/parser.cpp"
    break;

  case 34: /* var_decl: name_list COLON type_decl  */
#line 536 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl 2" << std::endl;
        #endif

        saveVariables((yyvsp[-2].identifierList), (yyvsp[0].typeNode));

        (yyval.varPartListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-2].identifierList), (yyvsp[0].typeNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1962 "out/parser.cpp"
    break;

  case 35: /* const_part: %empty  */
#line 549 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty const part" << std::endl;
        #endif
        (yyval.constPartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::ConstantNode*>*>();
    }
#line 1973 "out/parser.cpp"
    break;

  case 36: /* const_part: CONST const_expr_list  */
#line 556 "src/yacc.y"
                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const part" << std::endl;
        #endif

        (yyval.constPartList) = (yyvsp[0].constPartList);
    }
#line 1985 "out/parser.cpp"
    break;

  case 37: /* const_expr_list: const_expr_list const_expr  */
#line 566 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr list 1" << std::endl;
        #endif
        (yyval.constPartList) = (yyvsp[-1].constPartList);
        (yyval.constPartList)->push_back((yyvsp[0].constPartListElement));
    }
#line 1997 "out/parser.cpp"
    break;

  case 38: /* const_expr_list: const_expr  */
#line 574 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr list 2" << std::endl;
        #endif
        (yyval.constPartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::ConstantNode*>*>();
        (yyval.constPartList)->push_back((yyvsp[0].constPartListElement));
    }
#line 2009 "out/parser.cpp"
    break;

  case 39: /* const_expr: identifier EQUAL const_value SEMICOLON  */
#line 584 "src/yacc.y"
                                           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr 1" << std::endl;
        #endif

        saveConstant((yyvsp[-3].identifierNode), (yyvsp[-1].constantNode));

        (yyval.constPartListElement) = new std::pair<ast::IdentifierNode*, ast::ConstantNode*>((yyvsp[-3].identifierNode), (yyvsp[-1].constantNode));
    }
#line 2023 "out/parser.cpp"
    break;

  case 40: /* const_expr: identifier EQUAL const_value  */
#line 594 "src/yacc.y"
                                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr 2" << std::endl;
        #endif

        saveConstant((yyvsp[-2].identifierNode), (yyvsp[0].constantNode));

        (yyval.constPartListElement) = new std::pair<ast::IdentifierNode*, ast::ConstantNode*>((yyvsp[-2].identifierNode), (yyvsp[0].constantNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2038 "out/parser.cpp"
    break;

  case 41: /* const_value: INTEGER  */
#line 607 "src/yacc.y"
            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - integer `" << (yyvsp[0].token).numericalValue << "`" << std::endl;
        #endif
        (yyval.constantNode) = new ast::IntegerConstantNode((yyvsp[0].token).numericalValue);
    }
#line 2049 "out/parser.cpp"
    break;

  case 42: /* const_value: MINUS INTEGER  */
#line 614 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - signed integer `" << -(yyvsp[0].token).numericalValue << "`" << std::endl;
        #endif
        (yyval.constantNode) = new ast::IntegerConstantNode(-(yyvsp[0].token).numericalValue);
    }
#line 2060 "out/parser.cpp"
    break;

  case 43: /* const_value: CHAR  */
#line 622 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - char `" << static_cast<char>((yyvsp[0].token).numericalValue) << "`" << std::endl;
        #endif
        (yyval.constantNode) = new ast::CharConstantNode(static_cast<char>((yyvsp[0].token).numericalValue));
    }
#line 2071 "out/parser.cpp"
    break;

  case 44: /* const_value: STRING  */
#line 629 "src/yacc.y"
           {
        std::string str{*(yyvsp[0].token).stringValue};
        str = str.substr(1, str.size() - 2);

        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - string `" << str << "`" << std::endl;
        #endif

        (yyval.constantNode) = new ast::StringConstantNode(std::move(str));
    }
#line 2086 "out/parser.cpp"
    break;

  case 45: /* const_value: TRUE  */
#line 640 "src/yacc.y"
         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - true" << std::endl;
        #endif
        (yyval.constantNode) = new ast::BooleanConstantNode(true);
    }
#line 2097 "out/parser.cpp"
    break;

  case 46: /* const_value: FALSE  */
#line 647 "src/yacc.y"
          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - false" << std::endl;
        #endif
        (yyval.constantNode) = new ast::BooleanConstantNode(false);
    }
#line 2108 "out/parser.cpp"
    break;

  case 47: /* const_value: MAXINT  */
#line 654 "src/yacc.y"
           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - maxint" << std::endl;
        #endif
        (yyval.constantNode) = new ast::IntegerConstantNode(255);
    }
#line 2119 "out/parser.cpp"
    break;

  case 48: /* const_value: MINUS MAXINT  */
#line 661 "src/yacc.y"
                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - signed maxint" << std::endl;
        #endif
        (yyval.constantNode) = new ast::IntegerConstantNode(-255);
    }
#line 2130 "out/parser.cpp"
    break;

  case 49: /* type_part: %empty  */
#line 670 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty type part" << std::endl;
        #endif
        (yyval.typePartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::TypeNode*>*>();
    }
#line 2141 "out/parser.cpp"
    break;

  case 50: /* type_part: TYPE type_decl_list  */
#line 677 "src/yacc.y"
                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type part" << std::endl;
        #endif
        (yyval.typePartList) = (yyvsp[0].typePartList);
    }
#line 2152 "out/parser.cpp"
    break;

  case 51: /* type_decl_list: type_decl_list type_def  */
#line 686 "src/yacc.y"
                            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type decl list 1" << std::endl;
        #endif

        (yyval.typePartList) = (yyvsp[-1].typePartList);
        (yyval.typePartList)->push_back((yyvsp[0].typePartListElement));
    }
#line 2165 "out/parser.cpp"
    break;

  case 52: /* type_decl_list: type_def  */
#line 695 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type decl list 2" << std::endl;
        #endif

        (yyval.typePartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::TypeNode*>*>();
        (yyval.typePartList)->push_back((yyvsp[0].typePartListElement));
    }
#line 2178 "out/parser.cpp"
    break;

  case 53: /* type_def: identifier EQUAL type_decl SEMICOLON  */
#line 706 "src/yacc.y"
                                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type def 1" << std::endl;
        #endif

        saveType((yyvsp[-3].identifierNode), (yyvsp[-1].typeNode));

        (yyval.typePartListElement) = new std::pair<ast::IdentifierNode*, ast::TypeNode*>((yyvsp[-3].identifierNode), (yyvsp[-1].typeNode));
    }
#line 2192 "out/parser.cpp"
    break;

  case 54: /* type_def: identifier EQUAL type_decl  */
#line 716 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type def 2" << std::endl;
        #endif

        saveType((yyvsp[-2].identifierNode), (yyvsp[0].typeNode));

        (yyval.typePartListElement) = new std::pair<ast::IdentifierNode*, ast::TypeNode*>((yyvsp[-2].identifierNode), (yyvsp[0].typeNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2207 "out/parser.cpp"
    break;

  case 55: /* type_decl: simple_type  */
#line 729 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type" << std::endl;
        #endif
        (yyval.typeNode) = (yyvsp[0].simpleTypeNode);
    }
#line 2218 "out/parser.cpp"
    break;

  case 56: /* type_decl: array_type_decl  */
#line 736 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse array type" << std::endl;
        #endif
        (yyval.typeNode) = (yyvsp[0].arrayTypeNode);
    }
#line 2229 "out/parser.cpp"
    break;

  case 57: /* type_decl: record_type_decl  */
#line 743 "src/yacc.y"
                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse record type" << std::endl;
        #endif
        (yyval.typeNode) = (yyvsp[0].recordTypeNode);
    }
#line 2240 "out/parser.cpp"
    break;

  case 58: /* record_type_decl: RECORD field_decl_list END  */
#line 752 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse record type" << std::endl;
        #endif
        (yyval.recordTypeNode) = new ast::RecordTypeNode((yyvsp[-1].fieldDeclList));
    }
#line 2251 "out/parser.cpp"
    break;

  case 59: /* field_decl_list: field_decl_list field_decl  */
#line 761 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl list 1" << std::endl;
        #endif
        (yyval.fieldDeclList) = (yyvsp[-1].fieldDeclList);
        (yyval.fieldDeclList)->push_back((yyvsp[0].fieldDeclListElement));
    }
#line 2263 "out/parser.cpp"
    break;

  case 60: /* field_decl_list: field_decl  */
#line 769 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl list 2" << std::endl;
        #endif
        (yyval.fieldDeclList) = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
        (yyval.fieldDeclList)->push_back((yyvsp[0].fieldDeclListElement));
    }
#line 2275 "out/parser.cpp"
    break;

  case 61: /* field_decl: name_list COLON type_decl SEMICOLON  */
#line 779 "src/yacc.y"
                                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl 1" << std::endl;
        #endif
        (yyval.fieldDeclListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-3].identifierList), (yyvsp[-1].typeNode));
    }
#line 2286 "out/parser.cpp"
    break;

  case 62: /* field_decl: name_list COLON type_decl  */
#line 786 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl 2" << std::endl;
        #endif
        (yyval.fieldDeclListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-2].identifierList), (yyvsp[0].typeNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2298 "out/parser.cpp"
    break;

  case 63: /* array_type_decl: ARRAY LB simple_type RB OF type_decl  */
#line 796 "src/yacc.y"
                                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse array type" << std::endl;
        #endif
        (yyval.arrayTypeNode) = new ast::ArrayTypeNode((yyvsp[-3].simpleTypeNode), (yyvsp[0].typeNode));
    }
#line 2309 "out/parser.cpp"
    break;

  case 64: /* simple_type: identifier  */
#line 805 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - identifier" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::RenameTypeNode((yyvsp[0].identifierNode));
    }
#line 2320 "out/parser.cpp"
    break;

  case 65: /* simple_type: LP name_list RP  */
#line 812 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - parentheses" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::EnumerationTypeNode((yyvsp[-1].identifierList));
    }
#line 2331 "out/parser.cpp"
    break;

  case 66: /* simple_type: const_value DOUBLEDOT const_value  */
#line 819 "src/yacc.y"
                                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - range 1" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::ConstRangeTypeNode((yyvsp[-2].constantNode), (yyvsp[0].constantNode));
    }
#line 2342 "out/parser.cpp"
    break;

  case 67: /* simple_type: identifier DOUBLEDOT identifier  */
#line 826 "src/yacc.y"
                                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - range 4" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::VarRangeTypeNode((yyvsp[-2].identifierNode), (yyvsp[0].identifierNode));
    }
#line 2353 "out/parser.cpp"
    break;

  case 68: /* simple_type: INT_TYPE  */
#line 833 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - int" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::INTEGER);
    }
#line 2364 "out/parser.cpp"
    break;

  case 69: /* simple_type: UNSIGNED_TYPE  */
#line 840 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - unsigned" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::UNSIGNED);
    }
#line 2375 "out/parser.cpp"
    break;

  case 70: /* simple_type: BOOL_TYPE  */
#line 847 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - bool" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::BOOLEAN);
    }
#line 2386 "out/parser.cpp"
    break;

  case 71: /* simple_type: CHAR_TYPE  */
#line 854 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - char" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::CHAR);
    }
#line 2397 "out/parser.cpp"
    break;

  case 72: /* name_list: name_list COMMA identifier  */
#line 863 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse name list 1" << std::endl;
        #endif
        (yyval.identifierList) = (yyvsp[-2].identifierList);
        (yyval.identifierList)->push_back((yyvsp[0].identifierNode));
    }
#line 2409 "out/parser.cpp"
    break;

  case 73: /* name_list: identifier  */
#line 871 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse name list 2" << std::endl;
        #endif
        (yyval.identifierList) = new std::vector<ast::IdentifierNode*>();
        (yyval.identifierList)->push_back((yyvsp[0].identifierNode));
    }
#line 2421 "out/parser.cpp"
    break;

  case 74: /* identifier: IDENT_NAME  */
#line 881 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse identifier `" << (*(yyvsp[0].token).stringValue) << "`" << std::endl;
        #endif
        std::string name{*(yyvsp[0].token).stringValue};
        (yyval.identifierNode) = new ast::IdentifierNode(std::move(name));
    }
#line 2433 "out/parser.cpp"
    break;

  case 75: /* routine_body: compound_stmt  */
#line 891 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine body" << std::endl;
        #endif
        (yyval.routineBodyNode) = new ast::RoutineBodyNode((yyvsp[0].compoundStatementNode));
    }
#line 2444 "out/parser.cpp"
    break;

  case 76: /* compound_stmt: BBEGIN stmt_list END  */
#line 900 "src/yacc.y"
                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse compound statement 1" << std::endl;
        #endif
        (yyval.compoundStatementNode) = new ast::CompoundStatementNode((yyvsp[-1].statementNodeList));
    }
#line 2455 "out/parser.cpp"
    break;

  case 77: /* compound_stmt: BBEGIN stmt_list  */
#line 907 "src/yacc.y"
                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse compound statement 2" << std::endl;
        #endif
        (yyval.compoundStatementNode) = new ast::CompoundStatementNode((yyvsp[0].statementNodeList));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of end");
    }
#line 2467 "out/parser.cpp"
    break;

  case 78: /* stmt_list: %empty  */
#line 917 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty statement list" << std::endl;
        #endif
        (yyval.statementNodeList) = new std::vector<ast::StatementNode*>();
    }
#line 2478 "out/parser.cpp"
    break;

  case 79: /* stmt_list: stmt_list stmt SEMICOLON  */
#line 924 "src/yacc.y"
                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement list 1" << std::endl;
        #endif
        (yyval.statementNodeList) = (yyvsp[-2].statementNodeList);
        (yyval.statementNodeList)->push_back((yyvsp[-1].statementNode));
    }
#line 2490 "out/parser.cpp"
    break;

  case 80: /* stmt_list: stmt_list stmt  */
#line 932 "src/yacc.y"
                   {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement list 2" << std::endl;
        #endif
        (yyval.statementNodeList) = (yyvsp[-1].statementNodeList);
        (yyval.statementNodeList)->push_back((yyvsp[0].statementNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2503 "out/parser.cpp"
    break;

  case 81: /* stmt: INTEGER COLON no_label_stmt  */
#line 943 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement with label " << (yyvsp[-2].token).numericalValue << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].statementNode);
        (yyval.statementNode)->setLabel((yyvsp[-2].token).numericalValue);
    }
#line 2515 "out/parser.cpp"
    break;

  case 82: /* stmt: no_label_stmt  */
#line 951 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement without label" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].statementNode);
    }
#line 2526 "out/parser.cpp"
    break;

  case 83: /* no_label_stmt: assign_stmt  */
#line 960 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - assign" << std::endl;
        #endif
        (yyval.statementNode)=(yyvsp[0].assignNode);
    }
#line 2537 "out/parser.cpp"
    break;

  case 84: /* no_label_stmt: compound_stmt  */
#line 967 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - compound" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].compoundStatementNode);
    }
#line 2548 "out/parser.cpp"
    break;

  case 85: /* no_label_stmt: goto_stmt  */
#line 974 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - goto" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].gotoNode);
    }
#line 2559 "out/parser.cpp"
    break;

  case 86: /* no_label_stmt: if_stmt  */
#line 981 "src/yacc.y"
            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - if" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].ifNode);
    }
#line 2570 "out/parser.cpp"
    break;

  case 87: /* no_label_stmt: repeat_stmt  */
#line 988 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - repeat" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].repeatNode);
    }
#line 2581 "out/parser.cpp"
    break;

  case 88: /* no_label_stmt: while_stmt  */
#line 995 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - while" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].whileNode);
    }
#line 2592 "out/parser.cpp"
    break;

  case 89: /* no_label_stmt: case_stmt  */
#line 1002 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - case" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].caseNode);
    }
#line 2603 "out/parser.cpp"
    break;

  case 90: /* no_label_stmt: for_stmt  */
#line 1009 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - for" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].forNode);
    }
#line 2614 "out/parser.cpp"
    break;

  case 91: /* no_label_stmt: proc_stmt  */
#line 1016 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - proc" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].callNode);
    }
#line 2625 "out/parser.cpp"
    break;

  case 92: /* no_label_stmt: BREAK  */
#line 1023 "src/yacc.y"
          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - break" << std::endl;
        #endif
        (yyval.statementNode) = new ast::BreakNode();
    }
#line 2636 "out/parser.cpp"
    break;

  case 93: /* no_label_stmt: CONTINUE  */
#line 1030 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - continue" << std::endl;
        #endif
        (yyval.statementNode) = new ast::ContinueNode();
    }
#line 2647 "out/parser.cpp"
    break;

  case 94: /* assign_stmt: identifier ASSIGN expression  */
#line 1039 "src/yacc.y"
                                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple assign statement" << std::endl;
        #endif
        (yyval.assignNode) = new ast::AssignToVariableNode((yyvsp[-2].identifierNode), (yyvsp[0].expressionNode));
    }
#line 2658 "out/parser.cpp"
    break;

  case 95: /* assign_stmt: identifier LB expression RB ASSIGN expression  */
#line 1046 "src/yacc.y"
                                                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse array assign statement" << std::endl;
        #endif
        (yyval.assignNode) = new ast::AssignToArrayNode((yyvsp[-5].identifierNode), (yyvsp[-3].expressionNode), (yyvsp[0].expressionNode));
    }
#line 2669 "out/parser.cpp"
    break;

  case 96: /* assign_stmt: identifier DOT identifier ASSIGN expression  */
#line 1053 "src/yacc.y"
                                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse record assign statement" << std::endl;
        #endif
        (yyval.assignNode) = new ast::AssignToRecordFieldNode((yyvsp[-4].identifierNode), (yyvsp[-2].identifierNode), (yyvsp[0].expressionNode));
    }
#line 2680 "out/parser.cpp"
    break;

  case 97: /* goto_stmt: GOTO INTEGER  */
#line 1062 "src/yacc.y"
                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse goto statement to " << (yyvsp[0].token).numericalValue << std::endl;
        #endif
        (yyval.gotoNode) = new ast::GotoNode((yyvsp[0].token).numericalValue);
    }
#line 2691 "out/parser.cpp"
    break;

  case 98: /* if_stmt: IF expression THEN stmt else_clause  */
#line 1071 "src/yacc.y"
                                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse if statement 1" << std::endl;
        #endif
        (yyval.ifNode) = new ast::IfNode((yyvsp[-3].expressionNode), (yyvsp[-1].statementNode), (yyvsp[0].ifNode));
    }
#line 2702 "out/parser.cpp"
    break;

  case 99: /* if_stmt: IF expression stmt else_clause  */
#line 1078 "src/yacc.y"
                                   {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse if statement 2" << std::endl;
        #endif
        (yyval.ifNode) = new ast::IfNode((yyvsp[-2].expressionNode), (yyvsp[-1].statementNode), (yyvsp[0].ifNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of then");
    }
#line 2714 "out/parser.cpp"
    break;

  case 100: /* else_clause: %empty  */
#line 1088 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty else clause" << std::endl;
        #endif
        (yyval.ifNode) = new ast::IfNode(nullptr, nullptr);
    }
#line 2725 "out/parser.cpp"
    break;

  case 101: /* else_clause: ELSE stmt  */
#line 1095 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse else clause" << std::endl;
        #endif
        (yyval.ifNode) = new ast::IfNode(nullptr, nullptr, (yyvsp[0].statementNode));
    }
#line 2736 "out/parser.cpp"
    break;

  case 102: /* repeat_stmt: REPEAT stmt_list UNTIL expression  */
#line 1104 "src/yacc.y"
                                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse repeat statement" << std::endl;
        #endif
        (yyval.repeatNode) = new ast::RepeatNode((yyvsp[0].expressionNode), (yyvsp[-2].statementNodeList));
    }
#line 2747 "out/parser.cpp"
    break;

  case 103: /* repeat_stmt: %empty  */
#line 1111 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty repeat statement" << std::endl;
        #endif
    }
#line 2757 "out/parser.cpp"
    break;

  case 104: /* while_stmt: WHILE expression DO stmt  */
#line 1119 "src/yacc.y"
                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse while statement" << std::endl;
        #endif
        (yyval.whileNode) = new ast::WhileNode((yyvsp[-2].expressionNode), (yyvsp[0].statementNode));
    }
#line 2768 "out/parser.cpp"
    break;

  case 105: /* case_stmt: CASE expression OF case_expr_list END  */
#line 1128 "src/yacc.y"
                                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case statement" << std::endl;
        #endif
        (yyval.caseNode) = new ast::CaseNode((yyvsp[-3].expressionNode), (yyvsp[-1].caseExprList));
    }
#line 2779 "out/parser.cpp"
    break;

  case 106: /* case_expr_list: case_expr_list case_expr  */
#line 1137 "src/yacc.y"
                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr list 1" << std::endl;
        #endif
        (yyval.caseExprList) = (yyvsp[-1].caseExprList);
        (yyval.caseExprList)->push_back((yyvsp[0].caseExpr));
    }
#line 2791 "out/parser.cpp"
    break;

  case 107: /* case_expr_list: case_expr  */
#line 1145 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr list 2" << std::endl;
        #endif
        (yyval.caseExprList) = new std::vector<std::pair<ast::AstNode*, ast::StatementNode*>*>();
        (yyval.caseExprList)->push_back((yyvsp[0].caseExpr));
    }
#line 2803 "out/parser.cpp"
    break;

  case 108: /* case_expr: const_value COLON stmt SEMICOLON  */
#line 1155 "src/yacc.y"
                                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr 1" << std::endl;
        #endif
        (yyval.caseExpr) = new std::pair<ast::AstNode*, ast::StatementNode*>((yyvsp[-3].constantNode), (yyvsp[-1].statementNode));
    }
#line 2814 "out/parser.cpp"
    break;

  case 109: /* case_expr: identifier COLON stmt SEMICOLON  */
#line 1162 "src/yacc.y"
                                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr 2" << std::endl;
        #endif
        (yyval.caseExpr) = new std::pair<ast::AstNode*, ast::StatementNode*>((yyvsp[-3].identifierNode), (yyvsp[-1].statementNode));
    }
#line 2825 "out/parser.cpp"
    break;

  case 110: /* case_expr: OTHERWISE stmt SEMICOLON  */
#line 1169 "src/yacc.y"
                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr 3" << std::endl;
        #endif
        (yyval.caseExpr) = new std::pair<ast::AstNode*, ast::StatementNode*>(nullptr, (yyvsp[-1].statementNode));
    }
#line 2836 "out/parser.cpp"
    break;

  case 111: /* for_stmt: FOR identifier ASSIGN expression TO expression DO stmt  */
#line 1178 "src/yacc.y"
                                                           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse for statement 1" << std::endl;
        #endif
        (yyval.forNode) = new ast::ForNode((yyvsp[-6].identifierNode), (yyvsp[-4].expressionNode), (yyvsp[-2].expressionNode), (yyvsp[0].statementNode), ast::ForNode::Direction::INCREMENT);
    }
#line 2847 "out/parser.cpp"
    break;

  case 112: /* for_stmt: FOR identifier ASSIGN expression DOWNTO expression DO stmt  */
#line 1185 "src/yacc.y"
                                                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse for statement 2" << std::endl;
        #endif
        (yyval.forNode) = new ast::ForNode((yyvsp[-6].identifierNode), (yyvsp[-4].expressionNode), (yyvsp[-2].expressionNode), (yyvsp[0].statementNode), ast::ForNode::Direction::DECREMENT);
    }
#line 2858 "out/parser.cpp"
    break;

  case 113: /* proc_stmt: identifier  */
#line 1194 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse procedure statement" << std::endl;
        #endif
        (yyval.callNode) = new ast::UserDefineCallNode((yyvsp[0].identifierNode), nullptr);
    }
#line 2869 "out/parser.cpp"
    break;

  case 114: /* proc_stmt: identifier LP args_list RP  */
#line 1201 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse procedure statement with args" << std::endl;
        #endif
        (yyval.callNode) = new ast::UserDefineCallNode((yyvsp[-3].identifierNode), (yyvsp[-1].argsList));
    }
#line 2880 "out/parser.cpp"
    break;

  case 115: /* proc_stmt: READ LP factor RP  */
#line 1208 "src/yacc.y"
                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse read statement" << std::endl;
        #endif
        ast::ArgumentsListNode* args = new ast::ArgumentsListNode();
        args->addArgument((yyvsp[-1].expressionNode));
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::READ, args);
    }
#line 2893 "out/parser.cpp"
    break;

  case 116: /* proc_stmt: READLN  */
#line 1218 "src/yacc.y"
           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse readln statement" << std::endl;
        #endif
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::READLN, nullptr);
    }
#line 2904 "out/parser.cpp"
    break;

  case 117: /* proc_stmt: WRITE LP args_list RP  */
#line 1225 "src/yacc.y"
                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse write statement" << std::endl;
        #endif
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITE, (yyvsp[-1].argsList));
    }
#line 2915 "out/parser.cpp"
    break;

  case 118: /* proc_stmt: WRITELN  */
#line 1232 "src/yacc.y"
            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse writeln statement" << std::endl;
        #endif
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITELN, nullptr);
    }
#line 2926 "out/parser.cpp"
    break;

  case 119: /* proc_stmt: WRITELN LP args_list RP  */
#line 1239 "src/yacc.y"
                            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse writeln statement with args" << std::endl;
        #endif
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITELN, (yyvsp[-1].argsList));
    }
#line 2937 "out/parser.cpp"
    break;

  case 120: /* proc_stmt: MEMORYREAD LP args_list RP  */
#line 1246 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse memory read statement" << std::endl;
        #endif
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::MEMORY_READ, (yyvsp[-1].argsList));
    }
#line 2948 "out/parser.cpp"
    break;

  case 121: /* proc_stmt: MEMORYWRITE LP args_list RP  */
#line 1253 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse memory write statement" << std::endl;
        #endif
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::MEMORY_WRITE, (yyvsp[-1].argsList));
    }
#line 2959 "out/parser.cpp"
    break;

  case 122: /* proc_stmt: STACKREAD LP args_list RP  */
#line 1260 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse stack read statement" << std::endl;
        #endif
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::STACK_READ, (yyvsp[-1].argsList));
    }
#line 2970 "out/parser.cpp"
    break;

  case 123: /* proc_stmt: STACKWRITE LP args_list RP  */
#line 1267 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse stack write statement" << std::endl;
        #endif
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::STACK_WRITE, (yyvsp[-1].argsList));
    }
#line 2981 "out/parser.cpp"
    break;

  case 124: /* args_list: args_list COMMA expression  */
#line 1276 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse args list 1" << std::endl;
        #endif
        (yyval.argsList) = (yyvsp[-2].argsList);
        (yyval.argsList)->addArgument((yyvsp[0].expressionNode));
    }
#line 2993 "out/parser.cpp"
    break;

  case 125: /* args_list: expression  */
#line 1284 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse args list 2" << std::endl;
        #endif
        (yyval.argsList) = new ast::ArgumentsListNode();
        (yyval.argsList)->addArgument((yyvsp[0].expressionNode));
    }
#line 3005 "out/parser.cpp"
    break;

  case 126: /* expression: expression GE expr  */
#line 1294 "src/yacc.y"
                       {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with greater or equal" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::GREATER_EQUAL);
    }
#line 3016 "out/parser.cpp"
    break;

  case 127: /* expression: expression GT expr  */
#line 1301 "src/yacc.y"
                       {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with greater" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::GREATER);
    }
#line 3027 "out/parser.cpp"
    break;

  case 128: /* expression: expression LE expr  */
#line 1308 "src/yacc.y"
                       {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with less or equal" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::LESS_EQUAL);
    }
#line 3038 "out/parser.cpp"
    break;

  case 129: /* expression: expression LT expr  */
#line 1315 "src/yacc.y"
                       {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with less" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::LESS);
    }
#line 3049 "out/parser.cpp"
    break;

  case 130: /* expression: expression EQUAL expr  */
#line 1322 "src/yacc.y"
                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with equal" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::EQUAL);
    }
#line 3060 "out/parser.cpp"
    break;

  case 131: /* expression: expression UNEQUAL expr  */
#line 1329 "src/yacc.y"
                            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with not equal" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::NOT_EQUAL);
    }
#line 3071 "out/parser.cpp"
    break;

  case 132: /* expression: expr  */
#line 1336 "src/yacc.y"
         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple expression" << std::endl;
        #endif
        (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 3082 "out/parser.cpp"
    break;

  case 133: /* expr: expr PLUS term  */
#line 1345 "src/yacc.y"
                   {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with addition" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::ADDITION);
    }
#line 3093 "out/parser.cpp"
    break;

  case 134: /* expr: expr MINUS term  */
#line 1352 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with subtraction" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::SUBTRACTION);
    }
#line 3104 "out/parser.cpp"
    break;

  case 135: /* expr: expr OR term  */
#line 1359 "src/yacc.y"
                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with or" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::OR);
    }
#line 3115 "out/parser.cpp"
    break;

  case 136: /* expr: term  */
#line 1366 "src/yacc.y"
         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple term" << std::endl;
        #endif
        (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 3126 "out/parser.cpp"
    break;

  case 137: /* term: term MUL factor  */
#line 1375 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with multiplication" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::MULTIPLICATION);
    }
#line 3137 "out/parser.cpp"
    break;

  case 138: /* term: term DIV factor  */
#line 1382 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with division" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::DIVISION);
    }
#line 3148 "out/parser.cpp"
    break;

  case 139: /* term: term MOD factor  */
#line 1389 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with modulus" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::MODULUS);
    }
#line 3159 "out/parser.cpp"
    break;

  case 140: /* term: term AND factor  */
#line 1396 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with and" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::AND);
    }
#line 3170 "out/parser.cpp"
    break;

  case 141: /* term: factor  */
#line 1403 "src/yacc.y"
           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple factor" << std::endl;
        #endif
        (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 3181 "out/parser.cpp"
    break;

  case 142: /* factor: identifier  */
#line 1412 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - identifier" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[0].identifierNode), ast::SpecialExpressionNode::FunctionName::VARIABLE);
    }
#line 3192 "out/parser.cpp"
    break;

  case 143: /* factor: identifier LP args_list RP  */
#line 1419 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - function call" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-3].identifierNode), (yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::CALL);
    }
#line 3203 "out/parser.cpp"
    break;

  case 144: /* factor: const_value  */
#line 1426 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - const value" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[0].constantNode), ast::SpecialExpressionNode::FunctionName::CONST);
    }
#line 3214 "out/parser.cpp"
    break;

  case 145: /* factor: LP expression RP  */
#line 1433 "src/yacc.y"
                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - parentheses" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].expressionNode), ast::SpecialExpressionNode::FunctionName::PARENTHESIS);
    }
#line 3225 "out/parser.cpp"
    break;

  case 146: /* factor: NOT factor  */
#line 1440 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - not" << std::endl;
        #endif
       (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[0].expressionNode), ast::ExpressionNode::Operation::NOT);
    }
#line 3236 "out/parser.cpp"
    break;

  case 147: /* factor: MINUS factor  */
#line 1447 "src/yacc.y"
                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - negation" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[0].expressionNode), ast::ExpressionNode::Operation::NEGATION);
    }
#line 3247 "out/parser.cpp"
    break;

  case 148: /* factor: identifier LB expression RB  */
#line 1454 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - array access" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-3].identifierNode), (yyvsp[-1].expressionNode), ast::SpecialExpressionNode::FunctionName::ARRAY_ACCESS);
    }
#line 3258 "out/parser.cpp"
    break;

  case 149: /* factor: identifier DOT identifier  */
#line 1461 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - record access" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-2].identifierNode), (yyvsp[0].identifierNode), ast::SpecialExpressionNode::FunctionName::RECORD_ACCESS);
    }
#line 3269 "out/parser.cpp"
    break;

  case 150: /* factor: ABS LP args_list RP  */
#line 1468 "src/yacc.y"
                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - abs" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::ABS);
    }
#line 3280 "out/parser.cpp"
    break;

  case 151: /* factor: CHR LP args_list RP  */
#line 1475 "src/yacc.y"
                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - chr" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::CHR);
    }
#line 3291 "out/parser.cpp"
    break;

  case 152: /* factor: ODD LP args_list RP  */
#line 1482 "src/yacc.y"
                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - odd" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::ODD);
    }
#line 3302 "out/parser.cpp"
    break;

  case 153: /* factor: ORD LP args_list RP  */
#line 1489 "src/yacc.y"
                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - ord" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::ORD);
    }
#line 3313 "out/parser.cpp"
    break;

  case 154: /* factor: PRED LP args_list RP  */
#line 1496 "src/yacc.y"
                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - pred" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::PRED);
    }
#line 3324 "out/parser.cpp"
    break;

  case 155: /* factor: SUCC LP args_list RP  */
#line 1503 "src/yacc.y"
                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - succ" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::SUCC);
    }
#line 3335 "out/parser.cpp"
    break;


#line 3339 "out/parser.cpp"

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

#line 1510 "src/yacc.y"


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
