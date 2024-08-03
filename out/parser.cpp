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

#include "../src/ast/program_node.hpp"
#include "../src/LookupTable.hpp"

#define YACC_DEBUG

ast::ProgramNode* resultAst;
std::vector<std::string> parsingErrors;
LookupTable lookupTable;

static void yyerror(const char *msg);
static int yyparse(void);
int yylex(void);

extern FILE* yyin;
extern uint64_t linesCounter;

#line 94 "out/parser.cpp"

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
  YYSYMBOL_ABS = 23,                       /* ABS  */
  YYSYMBOL_CHR = 24,                       /* CHR  */
  YYSYMBOL_ODD = 25,                       /* ODD  */
  YYSYMBOL_ORD = 26,                       /* ORD  */
  YYSYMBOL_PRED = 27,                      /* PRED  */
  YYSYMBOL_SUCC = 28,                      /* SUCC  */
  YYSYMBOL_IF = 29,                        /* IF  */
  YYSYMBOL_THEN = 30,                      /* THEN  */
  YYSYMBOL_ELSE = 31,                      /* ELSE  */
  YYSYMBOL_REPEAT = 32,                    /* REPEAT  */
  YYSYMBOL_UNTIL = 33,                     /* UNTIL  */
  YYSYMBOL_WHILE = 34,                     /* WHILE  */
  YYSYMBOL_DO = 35,                        /* DO  */
  YYSYMBOL_CASE = 36,                      /* CASE  */
  YYSYMBOL_TO = 37,                        /* TO  */
  YYSYMBOL_DOWNTO = 38,                    /* DOWNTO  */
  YYSYMBOL_FOR = 39,                       /* FOR  */
  YYSYMBOL_EQUAL = 40,                     /* EQUAL  */
  YYSYMBOL_UNEQUAL = 41,                   /* UNEQUAL  */
  YYSYMBOL_GE = 42,                        /* GE  */
  YYSYMBOL_GT = 43,                        /* GT  */
  YYSYMBOL_LE = 44,                        /* LE  */
  YYSYMBOL_LT = 45,                        /* LT  */
  YYSYMBOL_ASSIGN = 46,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 47,                      /* PLUS  */
  YYSYMBOL_MINUS = 48,                     /* MINUS  */
  YYSYMBOL_MUL = 49,                       /* MUL  */
  YYSYMBOL_DIV = 50,                       /* DIV  */
  YYSYMBOL_OR = 51,                        /* OR  */
  YYSYMBOL_AND = 52,                       /* AND  */
  YYSYMBOL_NOT = 53,                       /* NOT  */
  YYSYMBOL_MOD = 54,                       /* MOD  */
  YYSYMBOL_LB = 55,                        /* LB  */
  YYSYMBOL_RB = 56,                        /* RB  */
  YYSYMBOL_LP = 57,                        /* LP  */
  YYSYMBOL_RP = 58,                        /* RP  */
  YYSYMBOL_SEMICOLON = 59,                 /* SEMICOLON  */
  YYSYMBOL_DOT = 60,                       /* DOT  */
  YYSYMBOL_DOUBLEDOT = 61,                 /* DOUBLEDOT  */
  YYSYMBOL_COMMA = 62,                     /* COMMA  */
  YYSYMBOL_COLON = 63,                     /* COLON  */
  YYSYMBOL_INT_TYPE = 64,                  /* INT_TYPE  */
  YYSYMBOL_UNSIGNED_TYPE = 65,             /* UNSIGNED_TYPE  */
  YYSYMBOL_BOOL_TYPE = 66,                 /* BOOL_TYPE  */
  YYSYMBOL_CHAR_TYPE = 67,                 /* CHAR_TYPE  */
  YYSYMBOL_STRING_TYPE = 68,               /* STRING_TYPE  */
  YYSYMBOL_ARRAY = 69,                     /* ARRAY  */
  YYSYMBOL_OF = 70,                        /* OF  */
  YYSYMBOL_RECORD = 71,                    /* RECORD  */
  YYSYMBOL_GOTO = 72,                      /* GOTO  */
  YYSYMBOL_ERROR = 73,                     /* ERROR  */
  YYSYMBOL_YYACCEPT = 74,                  /* $accept  */
  YYSYMBOL_program = 75,                   /* program  */
  YYSYMBOL_routine = 76,                   /* routine  */
  YYSYMBOL_routine_head = 77,              /* routine_head  */
  YYSYMBOL_routine_part = 78,              /* routine_part  */
  YYSYMBOL_fun_decl = 79,                  /* fun_decl  */
  YYSYMBOL_fun_head = 80,                  /* fun_head  */
  YYSYMBOL_proc_decl = 81,                 /* proc_decl  */
  YYSYMBOL_proc_head = 82,                 /* proc_head  */
  YYSYMBOL_params = 83,                    /* params  */
  YYSYMBOL_params_decl = 84,               /* params_decl  */
  YYSYMBOL_params_type = 85,               /* params_type  */
  YYSYMBOL_var_part = 86,                  /* var_part  */
  YYSYMBOL_var_decl_list = 87,             /* var_decl_list  */
  YYSYMBOL_var_decl = 88,                  /* var_decl  */
  YYSYMBOL_const_part = 89,                /* const_part  */
  YYSYMBOL_const_expr_list = 90,           /* const_expr_list  */
  YYSYMBOL_const_expr = 91,                /* const_expr  */
  YYSYMBOL_const_value = 92,               /* const_value  */
  YYSYMBOL_type_part = 93,                 /* type_part  */
  YYSYMBOL_type_decl_list = 94,            /* type_decl_list  */
  YYSYMBOL_type_def = 95,                  /* type_def  */
  YYSYMBOL_type_decl = 96,                 /* type_decl  */
  YYSYMBOL_record_type_decl = 97,          /* record_type_decl  */
  YYSYMBOL_field_decl_list = 98,           /* field_decl_list  */
  YYSYMBOL_field_decl = 99,                /* field_decl  */
  YYSYMBOL_array_type_decl = 100,          /* array_type_decl  */
  YYSYMBOL_simple_type = 101,              /* simple_type  */
  YYSYMBOL_name_list = 102,                /* name_list  */
  YYSYMBOL_identifier = 103,               /* identifier  */
  YYSYMBOL_routine_body = 104,             /* routine_body  */
  YYSYMBOL_compound_stmt = 105,            /* compound_stmt  */
  YYSYMBOL_stmt_list = 106,                /* stmt_list  */
  YYSYMBOL_stmt = 107,                     /* stmt  */
  YYSYMBOL_no_label_stmt = 108,            /* no_label_stmt  */
  YYSYMBOL_assign_stmt = 109,              /* assign_stmt  */
  YYSYMBOL_goto_stmt = 110,                /* goto_stmt  */
  YYSYMBOL_if_stmt = 111,                  /* if_stmt  */
  YYSYMBOL_else_clause = 112,              /* else_clause  */
  YYSYMBOL_repeat_stmt = 113,              /* repeat_stmt  */
  YYSYMBOL_while_stmt = 114,               /* while_stmt  */
  YYSYMBOL_case_stmt = 115,                /* case_stmt  */
  YYSYMBOL_case_expr_list = 116,           /* case_expr_list  */
  YYSYMBOL_case_expr = 117,                /* case_expr  */
  YYSYMBOL_for_stmt = 118,                 /* for_stmt  */
  YYSYMBOL_proc_stmt = 119,                /* proc_stmt  */
  YYSYMBOL_args_list = 120,                /* args_list  */
  YYSYMBOL_expression = 121,               /* expression  */
  YYSYMBOL_expr = 122,                     /* expr  */
  YYSYMBOL_term = 123,                     /* term  */
  YYSYMBOL_factor = 124                    /* factor  */
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
#define YYLAST   528

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  146
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  288

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   328


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
      65,    66,    67,    68,    69,    70,    71,    72,    73
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   171,   171,   184,   198,   212,   228,   237,   246,   253,
     261,   269,   277,   287,   296,   306,   316,   328,   341,   352,
     365,   373,   382,   390,   400,   407,   416,   423,   432,   440,
     450,   457,   467,   474,   483,   491,   501,   508,   518,   525,
     532,   540,   551,   558,   565,   572,   581,   588,   597,   605,
     615,   622,   632,   639,   646,   655,   664,   672,   682,   689,
     699,   708,   715,   722,   729,   736,   743,   750,   757,   764,
     773,   781,   791,   801,   810,   817,   827,   834,   842,   853,
     861,   870,   877,   884,   891,   898,   905,   912,   919,   926,
     935,   942,   949,   958,   967,   974,   984,   991,  1000,  1007,
    1015,  1024,  1033,  1041,  1051,  1058,  1067,  1074,  1083,  1090,
    1097,  1107,  1114,  1121,  1128,  1137,  1145,  1155,  1162,  1169,
    1176,  1183,  1190,  1197,  1206,  1213,  1220,  1227,  1236,  1243,
    1250,  1257,  1264,  1273,  1280,  1287,  1294,  1301,  1308,  1315,
    1322,  1329,  1336,  1343,  1350,  1357,  1364
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
  "READ", "READLN", "WRITE", "WRITELN", "ABS", "CHR", "ODD", "ORD", "PRED",
  "SUCC", "IF", "THEN", "ELSE", "REPEAT", "UNTIL", "WHILE", "DO", "CASE",
  "TO", "DOWNTO", "FOR", "EQUAL", "UNEQUAL", "GE", "GT", "LE", "LT",
  "ASSIGN", "PLUS", "MINUS", "MUL", "DIV", "OR", "AND", "NOT", "MOD", "LB",
  "RB", "LP", "RP", "SEMICOLON", "DOT", "DOUBLEDOT", "COMMA", "COLON",
  "INT_TYPE", "UNSIGNED_TYPE", "BOOL_TYPE", "CHAR_TYPE", "STRING_TYPE",
  "ARRAY", "OF", "RECORD", "GOTO", "ERROR", "$accept", "program",
  "routine", "routine_head", "routine_part", "fun_decl", "fun_head",
  "proc_decl", "proc_head", "params", "params_decl", "params_type",
  "var_part", "var_decl_list", "var_decl", "const_part", "const_expr_list",
  "const_expr", "const_value", "type_part", "type_decl_list", "type_def",
  "type_decl", "record_type_decl", "field_decl_list", "field_decl",
  "array_type_decl", "simple_type", "name_list", "identifier",
  "routine_body", "compound_stmt", "stmt_list", "stmt", "no_label_stmt",
  "assign_stmt", "goto_stmt", "if_stmt", "else_clause", "repeat_stmt",
  "while_stmt", "case_stmt", "case_expr_list", "case_expr", "for_stmt",
  "proc_stmt", "args_list", "expression", "expr", "term", "factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-173)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       5,    34,    16,     1,  -173,    36,    46,    15,    68,    72,
    -173,    36,  -173,    58,    48,  -173,  -173,  -173,  -173,    36,
     102,  -173,   473,  -173,    17,    36,  -173,    87,    36,   127,
    -173,  -173,  -173,  -173,  -173,  -173,    30,    70,  -173,    83,
      92,  -173,    97,   103,   429,  -173,   429,   429,    36,   153,
     -25,  -173,   107,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,   358,    36,  -173,   -29,  -173,   160,   161,
     127,  -173,     4,  -173,   114,  -173,  -173,  -173,   181,   429,
     429,   429,   117,   119,   122,   123,   134,   139,   447,   429,
     429,  -173,   -42,   262,    33,    22,  -173,   299,   282,   245,
     138,  -173,   429,   429,   429,    36,  -173,    36,  -173,  -173,
    -173,  -173,  -173,   142,    36,   137,   140,  -173,  -173,  -173,
     145,  -173,    36,   358,   150,   150,  -173,  -173,    46,   149,
      46,  -173,   151,    -8,   311,    -1,   429,   429,   429,   429,
     429,   429,  -173,  -173,  -173,  -173,   301,   429,   429,    36,
     328,   429,   429,   429,   429,   429,   429,   180,   429,   429,
     429,   429,   429,   429,   429,   429,   328,   227,   429,   311,
     224,    24,   166,    29,   371,   124,  -173,    74,   473,  -173,
      36,  -173,   157,    14,   158,  -173,   164,  -173,   168,  -173,
    -173,   429,  -173,    32,    37,    39,    45,    61,    62,  -173,
     351,    63,  -173,   180,    33,    33,    33,    33,    33,    33,
     328,  -173,    22,    22,    22,  -173,  -173,  -173,  -173,   311,
    -173,   167,   170,   171,  -173,   475,   183,  -173,   429,  -173,
     175,  -173,  -173,   358,  -173,  -173,  -173,    36,    93,  -173,
      95,   371,  -173,  -173,   311,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,   328,   328,  -173,  -173,   429,
     429,   429,   311,   165,   178,   101,  -173,    14,   371,  -173,
     187,   188,   368,   466,   311,   358,  -173,   371,  -173,  -173,
    -173,  -173,   328,   328,  -173,  -173,  -173,  -173
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    32,     1,     0,    32,     5,     0,    46,
      72,    33,    35,     0,     3,     4,    76,     6,    73,     0,
      26,    34,     0,     2,    75,    47,    49,     0,     0,     8,
      38,    40,    41,    42,    43,    44,     0,    37,    74,     0,
       0,   111,     0,   113,     0,    76,     0,     0,     0,     0,
     108,    82,    78,    80,    81,    83,    84,    85,    86,    87,
      88,    89,    48,     0,    27,    29,     0,    71,     0,     0,
       7,    11,    32,    12,     0,    39,    45,    36,    99,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   135,   133,    99,   123,   127,   132,    99,     0,     0,
       0,    93,     0,     0,     0,     0,    77,     0,    65,    66,
      67,    68,    69,     0,     0,     0,    51,    54,    53,    52,
      61,    28,     0,     0,    20,    20,     9,    10,    32,    16,
      32,    79,     0,     0,   116,     0,     0,     0,     0,     0,
       0,     0,    38,    44,   138,   137,     0,     0,     0,     0,
      99,     0,     0,     0,     0,     0,     0,    96,     0,     0,
       0,     0,     0,     0,     0,     0,    99,     0,     0,    90,
       0,     0,     0,     0,     0,     0,    57,     0,     0,    50,
       0,    70,    31,     0,     0,    19,    14,    15,     0,   110,
     112,     0,   114,     0,     0,     0,     0,     0,     0,   136,
       0,     0,   140,    96,   121,   122,   117,   118,   119,   120,
      99,    95,   124,   125,   126,   128,   129,   131,   130,    98,
     100,     0,     0,     0,   103,     0,     0,   109,     0,    62,
       0,    55,    56,     0,    63,    64,    30,     0,     0,    23,
       0,     0,    13,    18,   115,   141,   142,   143,   144,   145,
     146,   139,   134,    94,    97,    99,    99,   101,   102,     0,
       0,     0,    92,     0,    59,     0,    21,     0,     0,    17,
       0,     0,     0,     0,    91,     0,    58,     0,    22,    25,
     104,   105,    99,    99,    60,    24,   106,   107
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -173,  -173,    -2,  -173,  -173,   182,  -173,   184,  -173,   109,
    -173,   -27,  -173,  -173,   191,  -173,  -173,   237,   -19,  -173,
    -173,   232,  -122,  -173,  -173,    84,  -173,  -172,   -90,    -5,
    -173,   252,   216,   -88,   198,  -173,  -173,  -173,    76,  -173,
    -173,  -173,  -173,    77,  -173,  -173,     2,   -35,   372,   -94,
     -48
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     7,     8,    70,    71,    72,    73,    74,   184,
     238,   239,    29,    64,    65,     9,    11,    12,    91,    20,
      25,    26,   116,   117,   175,   176,   118,   119,    66,    92,
      17,    51,    24,    52,    53,    54,    55,    56,   211,    57,
      58,    59,   223,   224,    60,    61,   133,   134,    94,    95,
      96
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      13,   182,   230,    37,    14,   157,    13,     5,     1,    93,
       5,    98,    99,   147,    27,   148,     4,   173,   149,    50,
      27,   102,   237,    67,   177,    10,    16,    38,    10,    39,
     103,   132,   104,   122,   123,   105,    40,    41,    42,    43,
     144,   145,    75,   100,   115,     3,    44,    10,    76,    45,
     190,    46,     5,    47,   191,   146,    48,   192,   120,    67,
       6,   191,   203,   128,   212,   213,   214,   169,   170,   269,
     129,   161,   162,    50,   163,    15,   164,    16,   220,    19,
     158,   159,   227,   135,   160,   177,   191,   229,    50,    49,
     245,   122,    50,   240,   191,   246,   279,   247,    22,   191,
     172,   191,    67,   248,   115,   285,   171,   191,    23,    67,
      28,   264,   200,   215,   216,   217,   218,   181,   120,   249,
     250,   252,   254,   191,   191,   191,   186,    63,   188,    77,
     219,    68,    69,   225,   231,    10,   122,   233,   193,   194,
     195,   196,   197,   198,   202,    50,    78,   265,   221,    79,
     201,   266,   267,   284,    80,   115,   244,   122,   268,   234,
      81,    50,   222,   122,   277,   101,   106,   270,   271,   120,
      67,   124,   125,   130,   136,   235,   137,   240,    67,   138,
     139,   257,    10,    30,   168,    31,    32,    33,    34,    35,
      16,   140,    10,   262,   286,   287,   141,   174,   178,   179,
      40,    41,    42,    43,   221,    50,   180,   183,   187,   189,
      44,   210,   228,    45,   115,    46,   236,    47,   222,    36,
      48,   241,   115,   242,   272,   273,   274,   243,   120,   261,
     255,   263,    67,   256,   185,   275,   120,   276,    10,    30,
     278,    31,    32,    33,    34,    35,   280,   281,    21,   115,
      50,    50,   126,    49,   127,   121,   115,    62,   115,   232,
      18,    97,    67,   120,   151,   152,   153,   154,   155,   156,
     120,    16,   120,    10,    39,    36,   131,    50,    50,   253,
     226,    40,    41,    42,    43,   151,   152,   153,   154,   155,
     156,    44,   150,     0,    45,     0,    46,     0,    47,     0,
     258,    48,   151,   152,   153,   154,   155,   156,    16,     0,
      10,    39,     0,     0,     0,   167,     0,   166,    40,    41,
      42,    43,   151,   152,   153,   154,   155,   156,    44,     0,
       0,    45,   165,    46,    49,    47,     0,    16,    48,    10,
      39,   151,   152,   153,   154,   155,   156,    40,    41,    42,
      43,   151,   152,   153,   154,   155,   156,    44,     0,   199,
      45,     0,    46,     0,    47,     0,     0,    48,     0,    10,
      30,    49,    31,    32,    33,    34,    35,     0,     0,     0,
       0,     0,    10,    30,     0,    31,    32,    33,    34,    35,
       0,   151,   152,   153,   154,   155,   156,     0,     0,     0,
      49,     0,     0,   282,     0,     0,    36,   251,   151,   152,
     153,   154,   155,   156,     0,   107,     0,     0,     0,    36,
       0,     0,   108,   109,   110,   111,   112,   113,   107,   114,
       0,     0,     0,     0,     0,   108,   109,   110,   111,   112,
      10,    30,     0,    31,    32,    33,    34,    35,     0,     0,
       0,     0,    82,    83,    84,    85,    86,    87,    10,   142,
       0,    31,    32,    33,    34,   143,     0,     0,     0,     0,
      82,    83,    84,    85,    86,    87,     0,    88,     0,     0,
       0,     0,    89,     0,     0,    30,    90,    31,    32,    33,
      34,    35,     0,     0,     0,    88,     0,     0,     0,     0,
      89,   283,     0,     0,    90,     0,   151,   152,   153,   154,
     155,   156,   259,   260,     0,   151,   152,   153,   154,   155,
     156,    36,     0,   204,   205,   206,   207,   208,   209
};

static const yytype_int16 yycheck[] =
{
       5,   123,   174,    22,     6,    93,    11,     6,     3,    44,
       6,    46,    47,    55,    19,    57,     0,   107,    60,    24,
      25,    46,     8,    28,   114,    11,     9,    10,    11,    12,
      55,    79,    57,    62,    63,    60,    19,    20,    21,    22,
      88,    89,    12,    48,    63,    11,    29,    11,    18,    32,
      58,    34,     6,    36,    62,    90,    39,    58,    63,    64,
      59,    62,   150,    59,   158,   159,   160,   102,   103,   241,
      72,    49,    50,    78,    52,    60,    54,     9,   166,     7,
      47,    48,    58,    81,    51,   175,    62,    58,    93,    72,
      58,    62,    97,   183,    62,    58,   268,    58,    40,    62,
     105,    62,   107,    58,   123,   277,   104,    62,    60,   114,
       8,   233,   147,   161,   162,   163,   164,   122,   123,    58,
      58,    58,   210,    62,    62,    62,   128,    40,   130,    59,
     165,     4,     5,   168,    10,    11,    62,    63,   136,   137,
     138,   139,   140,   141,   149,   150,    63,   237,   167,    57,
     148,    58,    59,   275,    57,   174,   191,    62,    63,   178,
      57,   166,   167,    62,    63,    12,    59,   255,   256,   174,
     175,    11,    11,    59,    57,   180,    57,   267,   183,    57,
      57,    10,    11,    12,    46,    14,    15,    16,    17,    18,
       9,    57,    11,   228,   282,   283,    57,    55,    61,    59,
      19,    20,    21,    22,   223,   210,    61,    57,    59,    58,
      29,    31,    46,    32,   233,    34,    59,    36,   223,    48,
      39,    63,   241,    59,   259,   260,   261,    59,   233,    46,
      63,    56,   237,    63,   125,    70,   241,    59,    11,    12,
     267,    14,    15,    16,    17,    18,    59,    59,    11,   268,
     255,   256,    70,    72,    70,    64,   275,    25,   277,   175,
       8,    45,   267,   268,    40,    41,    42,    43,    44,    45,
     275,     9,   277,    11,    12,    48,    78,   282,   283,   203,
      56,    19,    20,    21,    22,    40,    41,    42,    43,    44,
      45,    29,    30,    -1,    32,    -1,    34,    -1,    36,    -1,
     223,    39,    40,    41,    42,    43,    44,    45,     9,    -1,
      11,    12,    -1,    -1,    -1,    70,    -1,    35,    19,    20,
      21,    22,    40,    41,    42,    43,    44,    45,    29,    -1,
      -1,    32,    33,    34,    72,    36,    -1,     9,    39,    11,
      12,    40,    41,    42,    43,    44,    45,    19,    20,    21,
      22,    40,    41,    42,    43,    44,    45,    29,    -1,    58,
      32,    -1,    34,    -1,    36,    -1,    -1,    39,    -1,    11,
      12,    72,    14,    15,    16,    17,    18,    -1,    -1,    -1,
      -1,    -1,    11,    12,    -1,    14,    15,    16,    17,    18,
      -1,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      72,    -1,    -1,    35,    -1,    -1,    48,    56,    40,    41,
      42,    43,    44,    45,    -1,    57,    -1,    -1,    -1,    48,
      -1,    -1,    64,    65,    66,    67,    68,    69,    57,    71,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,
      11,    12,    -1,    14,    15,    16,    17,    18,    -1,    -1,
      -1,    -1,    23,    24,    25,    26,    27,    28,    11,    12,
      -1,    14,    15,    16,    17,    18,    -1,    -1,    -1,    -1,
      23,    24,    25,    26,    27,    28,    -1,    48,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    12,    57,    14,    15,    16,
      17,    18,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,
      53,    35,    -1,    -1,    57,    -1,    40,    41,    42,    43,
      44,    45,    37,    38,    -1,    40,    41,    42,    43,    44,
      45,    48,    -1,   151,   152,   153,   154,   155,   156
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    75,    11,     0,     6,    59,    76,    77,    89,
      11,    90,    91,   103,    76,    60,     9,   104,   105,     7,
      93,    91,    40,    60,   106,    94,    95,   103,     8,    86,
      12,    14,    15,    16,    17,    18,    48,    92,    10,    12,
      19,    20,    21,    22,    29,    32,    34,    36,    39,    72,
     103,   105,   107,   108,   109,   110,   111,   113,   114,   115,
     118,   119,    95,    40,    87,    88,   102,   103,     4,     5,
      78,    79,    80,    81,    82,    12,    18,    59,    63,    57,
      57,    57,    23,    24,    25,    26,    27,    28,    48,    53,
      57,    92,   103,   121,   122,   123,   124,   106,   121,   121,
     103,    12,    46,    55,    57,    60,    59,    57,    64,    65,
      66,    67,    68,    69,    71,    92,    96,    97,   100,   101,
     103,    88,    62,    63,    11,    11,    79,    81,    59,    76,
      59,   108,   124,   120,   121,   120,    57,    57,    57,    57,
      57,    57,    12,    18,   124,   124,   121,    55,    57,    60,
      30,    40,    41,    42,    43,    44,    45,   107,    47,    48,
      51,    49,    50,    52,    54,    33,    35,    70,    46,   121,
     121,   120,   103,   102,    55,    98,    99,   102,    61,    59,
      61,   103,    96,    57,    83,    83,    76,    59,    76,    58,
      58,    62,    58,   120,   120,   120,   120,   120,   120,    58,
     121,   120,   103,   107,   122,   122,   122,   122,   122,   122,
      31,   112,   123,   123,   123,   124,   124,   124,   124,   121,
     107,    92,   103,   116,   117,   121,    56,    58,    46,    58,
     101,    10,    99,    63,    92,   103,    59,     8,    84,    85,
     102,    63,    59,    59,   121,    58,    58,    58,    58,    58,
      58,    56,    58,   112,   107,    63,    63,    10,   117,    37,
      38,    46,   121,    56,    96,   102,    58,    59,    63,   101,
     107,   107,   121,   121,   121,    70,    59,    63,    85,   101,
      59,    59,    35,    35,    96,   101,   107,   107
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    74,    75,    75,    75,    75,    76,    77,    78,    78,
      78,    78,    78,    79,    79,    79,    79,    80,    81,    82,
      83,    83,    84,    84,    85,    85,    86,    86,    87,    87,
      88,    88,    89,    89,    90,    90,    91,    91,    92,    92,
      92,    92,    92,    92,    92,    92,    93,    93,    94,    94,
      95,    95,    96,    96,    96,    97,    98,    98,    99,    99,
     100,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     102,   102,   103,   104,   105,   105,   106,   106,   106,   107,
     107,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     109,   109,   109,   110,   111,   111,   112,   112,   113,   113,
     114,   115,   116,   116,   117,   117,   118,   118,   119,   119,
     119,   119,   119,   119,   119,   120,   120,   121,   121,   121,
     121,   121,   121,   121,   122,   122,   122,   122,   123,   123,
     123,   123,   123,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     4,     4,     3,     2,     4,     0,     2,
       2,     1,     1,     4,     3,     3,     2,     5,     4,     3,
       0,     3,     3,     1,     4,     3,     0,     2,     2,     1,
       4,     3,     0,     2,     2,     1,     4,     3,     1,     2,
       1,     1,     1,     1,     1,     2,     0,     2,     2,     1,
       4,     3,     1,     1,     1,     3,     2,     1,     4,     3,
       6,     1,     3,     3,     3,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     3,     2,     0,     3,     2,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     6,     5,     2,     5,     4,     0,     2,     4,     0,
       4,     5,     2,     1,     4,     4,     8,     8,     1,     4,
       4,     1,     4,     1,     4,     3,     1,     3,     3,     3,
       3,     3,     3,     1,     3,     3,     3,     1,     3,     3,
       3,     3,     1,     1,     4,     1,     3,     2,     2,     4,
       3,     4,     4,     4,     4,     4,     4
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
#line 171 "src/yacc.y"
                                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse program 1: " << (*(yyvsp[-3].token).stringValue) << std::endl;
        #endif

        lookupTable.pushNamespace("@program");

        std::string name{*(yyvsp[-3].token).stringValue};
        (yyvsp[-1].routineNode)->setSubType(ast::RoutineNode::SubType::MAIN);
        (yyval.programNode) = new ast::ProgramNode(std::move(name), (yyvsp[-1].routineNode));
        resultAst = (yyval.programNode);
    }
#line 1467 "out/parser.cpp"
    break;

  case 3: /* program: PROGRAM IDENT_NAME SEMICOLON routine  */
#line 184 "src/yacc.y"
                                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse program 2: " << (*(yyvsp[-2].token).stringValue) << std::endl;
        #endif

        lookupTable.pushNamespace("@program");

        std::string name{*(yyvsp[-2].token).stringValue};
        (yyvsp[0].routineNode)->setSubType(ast::RoutineNode::SubType::MAIN);
        (yyval.programNode) = new ast::ProgramNode(std::move(name), (yyvsp[0].routineNode));
        resultAst = (yyval.programNode);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of end dot");
    }
#line 1485 "out/parser.cpp"
    break;

  case 4: /* program: PROGRAM IDENT_NAME routine DOT  */
#line 198 "src/yacc.y"
                                   {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse program 3: " << (*(yyvsp[-2].token).stringValue) << std::endl;
        #endif

        lookupTable.pushNamespace("@program");

        std::string name{*(yyvsp[-2].token).stringValue};
        (yyvsp[-1].routineNode)->setSubType(ast::RoutineNode::SubType::MAIN);
        (yyval.programNode) = new ast::ProgramNode(std::move(name), (yyvsp[-1].routineNode));
        resultAst = (yyval.programNode);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1503 "out/parser.cpp"
    break;

  case 5: /* program: PROGRAM IDENT_NAME routine  */
#line 212 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse program 4: " << (*(yyvsp[-1].token).stringValue) << std::endl;
        #endif

        lookupTable.pushNamespace("@program");

        std::string name{*(yyvsp[-1].token).stringValue};
        (yyvsp[0].routineNode)->setSubType(ast::RoutineNode::SubType::MAIN);
        (yyval.programNode) = new ast::ProgramNode(std::move(name), (yyvsp[0].routineNode));
        resultAst = (yyval.programNode);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon and end dot");
    }
#line 1521 "out/parser.cpp"
    break;

  case 6: /* routine: routine_head routine_body  */
#line 228 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine" << std::endl;
        #endif
        (yyval.routineNode) = new ast::RoutineNode((yyvsp[-1].routineHeadNode), (yyvsp[0].routineBodyNode));
    }
#line 1532 "out/parser.cpp"
    break;

  case 7: /* routine_head: const_part type_part var_part routine_part  */
#line 237 "src/yacc.y"
                                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine head" << std::endl;
        #endif
        (yyval.routineHeadNode) = new ast::RoutineHeadNode((yyvsp[-3].constPartList), (yyvsp[-2].typePartList), (yyvsp[-1].varPartList), (yyvsp[0].routinePartList));
    }
#line 1543 "out/parser.cpp"
    break;

  case 8: /* routine_part: %empty  */
#line 246 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty routine part" << std::endl;
        #endif
        (yyval.routinePartList) = new std::vector<ast::RoutineDeclarationNode*>();
    }
#line 1554 "out/parser.cpp"
    break;

  case 9: /* routine_part: routine_part fun_decl  */
#line 253 "src/yacc.y"
                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine part with fun decl 1" << std::endl;
        #endif
        (yyval.routinePartList) = (yyvsp[-1].routinePartList);
        (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1566 "out/parser.cpp"
    break;

  case 10: /* routine_part: routine_part proc_decl  */
#line 261 "src/yacc.y"
                           {
       #ifdef YACC_DEBUG
           std::cout << "Yacc debug: Parse routine part with proc decl 1" << std::endl;
       #endif
       (yyval.routinePartList) = (yyvsp[-1].routinePartList);
       (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1578 "out/parser.cpp"
    break;

  case 11: /* routine_part: fun_decl  */
#line 269 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine part with fun decl 2" << std::endl;
        #endif
        (yyval.routinePartList) = new std::vector<ast::RoutineDeclarationNode*>();
        (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1590 "out/parser.cpp"
    break;

  case 12: /* routine_part: proc_decl  */
#line 277 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine part with proc decl 2" << std::endl;
        #endif
        (yyval.routinePartList) = new std::vector<ast::RoutineDeclarationNode*>();
        (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1602 "out/parser.cpp"
    break;

  case 13: /* fun_decl: fun_head SEMICOLON routine SEMICOLON  */
#line 287 "src/yacc.y"
                                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun decl 1" << std::endl;
        #endif
        (yyval.routineDeclarationNode) = (yyvsp[-3].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[-1].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
    }
#line 1615 "out/parser.cpp"
    break;

  case 14: /* fun_decl: fun_head SEMICOLON routine  */
#line 296 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun decl 2" << std::endl;
        #endif
        (yyval.routineDeclarationNode) = (yyvsp[-2].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[0].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1629 "out/parser.cpp"
    break;

  case 15: /* fun_decl: fun_head routine SEMICOLON  */
#line 306 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun decl 3" << std::endl;
        #endif
        (yyval.routineDeclarationNode) = (yyvsp[-2].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[-1].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1643 "out/parser.cpp"
    break;

  case 16: /* fun_decl: fun_head routine  */
#line 316 "src/yacc.y"
                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun decl 4" << std::endl;
        #endif
        (yyval.routineDeclarationNode) = (yyvsp[-1].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[0].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1657 "out/parser.cpp"
    break;

  case 17: /* fun_head: FUNCTION IDENT_NAME params COLON simple_type  */
#line 328 "src/yacc.y"
                                                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun head " << (*(yyvsp[-3].token).stringValue) << std::endl;
        #endif

        lookupTable.pushNamespace("@" + (*(yyvsp[-3].token).stringValue));

        std::string name{*(yyvsp[-3].token).stringValue};
        (yyval.routineDeclarationNode) = new ast::RoutineDeclarationNode(ast::RoutineDeclarationNode::RoutineType::FUNCTION, std::move(name), (yyvsp[-2].paramsNode), (yyvsp[0].simpleTypeNode), nullptr);
    }
#line 1672 "out/parser.cpp"
    break;

  case 18: /* proc_decl: proc_head SEMICOLON routine SEMICOLON  */
#line 341 "src/yacc.y"
                                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse proc decl" << std::endl;
        #endif
        (yyval.routineDeclarationNode) = (yyvsp[-3].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[-1].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::PROCEDURE);
    }
#line 1685 "out/parser.cpp"
    break;

  case 19: /* proc_head: PROCEDURE IDENT_NAME params  */
#line 352 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse proc head " << (*(yyvsp[-1].token).stringValue) << std::endl;
        #endif

        lookupTable.pushNamespace("@" + (*(yyvsp[-1].token).stringValue));

        std::string name{*(yyvsp[-1].token).stringValue};
        (yyval.routineDeclarationNode) = new ast::RoutineDeclarationNode(ast::RoutineDeclarationNode::RoutineType::PROCEDURE, std::move(name), (yyvsp[0].paramsNode), nullptr, nullptr);
    }
#line 1700 "out/parser.cpp"
    break;

  case 20: /* params: %empty  */
#line 365 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty params" << std::endl;
        #endif
        std::vector<ast::ParamsGroupNode *>* emptyParamsList{};
        (yyval.paramsNode) = new ast::ParamsNode(emptyParamsList);
    }
#line 1712 "out/parser.cpp"
    break;

  case 21: /* params: LP params_decl RP  */
#line 373 "src/yacc.y"
                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params" << std::endl;
        #endif  
        (yyval.paramsNode) = new ast::ParamsNode((yyvsp[-1].paramsGroupList));
    }
#line 1723 "out/parser.cpp"
    break;

  case 22: /* params_decl: params_decl SEMICOLON params_type  */
#line 382 "src/yacc.y"
                                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params decl 1" << std::endl;
        #endif
        (yyval.paramsGroupList) = (yyvsp[-2].paramsGroupList);
        (yyval.paramsGroupList)->push_back((yyvsp[0].paramsGroupNode));
    }
#line 1735 "out/parser.cpp"
    break;

  case 23: /* params_decl: params_type  */
#line 390 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params decl 2" << std::endl;
        #endif
        (yyval.paramsGroupList) = new std::vector<ast::ParamsGroupNode*>();
        (yyval.paramsGroupList)->push_back((yyvsp[0].paramsGroupNode));
    }
#line 1747 "out/parser.cpp"
    break;

  case 24: /* params_type: VAR name_list COLON simple_type  */
#line 400 "src/yacc.y"
                                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params type 1" << std::endl;
        #endif
        (yyval.paramsGroupNode) = new ast::ParamsGroupNode(ast::ParamsGroupNode::PassType::PASS_BY_REFERENCE, (yyvsp[-2].identifierList), (yyvsp[0].simpleTypeNode));
    }
#line 1758 "out/parser.cpp"
    break;

  case 25: /* params_type: name_list COLON simple_type  */
#line 407 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params type 2" << std::endl;
        #endif
        (yyval.paramsGroupNode) = new ast::ParamsGroupNode(ast::ParamsGroupNode::PassType::PASS_BY_VALUE, (yyvsp[-2].identifierList), (yyvsp[0].simpleTypeNode));
    }
#line 1769 "out/parser.cpp"
    break;

  case 26: /* var_part: %empty  */
#line 416 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty var part" << std::endl;
        #endif
        (yyval.varPartList) = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
    }
#line 1780 "out/parser.cpp"
    break;

  case 27: /* var_part: VAR var_decl_list  */
#line 423 "src/yacc.y"
                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var part" << std::endl;
        #endif
        (yyval.varPartList) = (yyvsp[0].varPartList);
    }
#line 1791 "out/parser.cpp"
    break;

  case 28: /* var_decl_list: var_decl_list var_decl  */
#line 432 "src/yacc.y"
                           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl list 1" << std::endl;
        #endif
        (yyval.varPartList) = (yyvsp[-1].varPartList);
        (yyval.varPartList)->push_back((yyvsp[0].varPartListElement));
    }
#line 1803 "out/parser.cpp"
    break;

  case 29: /* var_decl_list: var_decl  */
#line 440 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl list 2" << std::endl;
        #endif
        (yyval.varPartList) = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
        (yyval.varPartList)->push_back((yyvsp[0].varPartListElement));
    }
#line 1815 "out/parser.cpp"
    break;

  case 30: /* var_decl: name_list COLON type_decl SEMICOLON  */
#line 450 "src/yacc.y"
                                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl 1" << std::endl;
        #endif
        (yyval.varPartListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-3].identifierList), (yyvsp[-1].typeNode));
    }
#line 1826 "out/parser.cpp"
    break;

  case 31: /* var_decl: name_list COLON type_decl  */
#line 457 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl 2" << std::endl;
        #endif
        (yyval.varPartListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-2].identifierList), (yyvsp[0].typeNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1838 "out/parser.cpp"
    break;

  case 32: /* const_part: %empty  */
#line 467 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty const part" << std::endl;
        #endif
        (yyval.constPartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::ConstantNode*>*>();
    }
#line 1849 "out/parser.cpp"
    break;

  case 33: /* const_part: CONST const_expr_list  */
#line 474 "src/yacc.y"
                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const part" << std::endl;
        #endif
        (yyval.constPartList) = (yyvsp[0].constPartList);
    }
#line 1860 "out/parser.cpp"
    break;

  case 34: /* const_expr_list: const_expr_list const_expr  */
#line 483 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr list 1" << std::endl;
        #endif
        (yyval.constPartList) = (yyvsp[-1].constPartList);
        (yyval.constPartList)->push_back((yyvsp[0].constPartListElement));
    }
#line 1872 "out/parser.cpp"
    break;

  case 35: /* const_expr_list: const_expr  */
#line 491 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr list 2" << std::endl;
        #endif
        (yyval.constPartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::ConstantNode*>*>();
        (yyval.constPartList)->push_back((yyvsp[0].constPartListElement));
    }
#line 1884 "out/parser.cpp"
    break;

  case 36: /* const_expr: identifier EQUAL const_value SEMICOLON  */
#line 501 "src/yacc.y"
                                           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr 1" << std::endl;
        #endif
        (yyval.constPartListElement) = new std::pair<ast::IdentifierNode*, ast::ConstantNode*>((yyvsp[-3].identifierNode), (yyvsp[-1].constantNode));
    }
#line 1895 "out/parser.cpp"
    break;

  case 37: /* const_expr: identifier EQUAL const_value  */
#line 508 "src/yacc.y"
                                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr 2" << std::endl;
        #endif
        (yyval.constPartListElement) = new std::pair<ast::IdentifierNode*, ast::ConstantNode*>((yyvsp[-2].identifierNode), (yyvsp[0].constantNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1907 "out/parser.cpp"
    break;

  case 38: /* const_value: INTEGER  */
#line 518 "src/yacc.y"
            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - integer `" << (yyvsp[0].token).numericalValue << "`" << std::endl;
        #endif
        (yyval.constantNode) = new ast::IntegerConstantNode((yyvsp[0].token).numericalValue);
    }
#line 1918 "out/parser.cpp"
    break;

  case 39: /* const_value: MINUS INTEGER  */
#line 525 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - signed integer `" << -(yyvsp[0].token).numericalValue << "`" << std::endl;
        #endif
        (yyval.constantNode) = new ast::IntegerConstantNode(-(yyvsp[0].token).numericalValue);
    }
#line 1929 "out/parser.cpp"
    break;

  case 40: /* const_value: CHAR  */
#line 533 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - char `" << static_cast<char>((yyvsp[0].token).numericalValue) << "`" << std::endl;
        #endif
        (yyval.constantNode) = new ast::CharConstantNode(static_cast<char>((yyvsp[0].token).numericalValue));
    }
#line 1940 "out/parser.cpp"
    break;

  case 41: /* const_value: STRING  */
#line 540 "src/yacc.y"
           {
        std::string str{*(yyvsp[0].token).stringValue};
        str = str.substr(1, str.size() - 2);

        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - string `" << str << "`" << std::endl;
        #endif

        (yyval.constantNode) = new ast::StringConstantNode(std::move(str));
    }
#line 1955 "out/parser.cpp"
    break;

  case 42: /* const_value: TRUE  */
#line 551 "src/yacc.y"
         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - true" << std::endl;
        #endif
        (yyval.constantNode) = new ast::BooleanConstantNode(true);
    }
#line 1966 "out/parser.cpp"
    break;

  case 43: /* const_value: FALSE  */
#line 558 "src/yacc.y"
          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - false" << std::endl;
        #endif
        (yyval.constantNode) = new ast::BooleanConstantNode(false);
    }
#line 1977 "out/parser.cpp"
    break;

  case 44: /* const_value: MAXINT  */
#line 565 "src/yacc.y"
           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - maxint" << std::endl;
        #endif
        (yyval.constantNode) = new ast::IntegerConstantNode(255);
    }
#line 1988 "out/parser.cpp"
    break;

  case 45: /* const_value: MINUS MAXINT  */
#line 572 "src/yacc.y"
                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - signed maxint" << std::endl;
        #endif
        (yyval.constantNode) = new ast::IntegerConstantNode(-255);
    }
#line 1999 "out/parser.cpp"
    break;

  case 46: /* type_part: %empty  */
#line 581 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty type part" << std::endl;
        #endif
        (yyval.typePartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::TypeNode*>*>();
    }
#line 2010 "out/parser.cpp"
    break;

  case 47: /* type_part: TYPE type_decl_list  */
#line 588 "src/yacc.y"
                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type part" << std::endl;
        #endif
        (yyval.typePartList) = (yyvsp[0].typePartList);
    }
#line 2021 "out/parser.cpp"
    break;

  case 48: /* type_decl_list: type_decl_list type_def  */
#line 597 "src/yacc.y"
                            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type decl list 1" << std::endl;
        #endif
        (yyval.typePartList) = (yyvsp[-1].typePartList);
        (yyval.typePartList)->push_back((yyvsp[0].typePartListElement));
    }
#line 2033 "out/parser.cpp"
    break;

  case 49: /* type_decl_list: type_def  */
#line 605 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type decl list 2" << std::endl;
        #endif
        (yyval.typePartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::TypeNode*>*>();
        (yyval.typePartList)->push_back((yyvsp[0].typePartListElement));
    }
#line 2045 "out/parser.cpp"
    break;

  case 50: /* type_def: identifier EQUAL type_decl SEMICOLON  */
#line 615 "src/yacc.y"
                                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type def 1" << std::endl;
        #endif
        (yyval.typePartListElement) = new std::pair<ast::IdentifierNode*, ast::TypeNode*>((yyvsp[-3].identifierNode), (yyvsp[-1].typeNode));
    }
#line 2056 "out/parser.cpp"
    break;

  case 51: /* type_def: identifier EQUAL type_decl  */
#line 622 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type def 2" << std::endl;
        #endif
        (yyval.typePartListElement) = new std::pair<ast::IdentifierNode*, ast::TypeNode*>((yyvsp[-2].identifierNode), (yyvsp[0].typeNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2068 "out/parser.cpp"
    break;

  case 52: /* type_decl: simple_type  */
#line 632 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type" << std::endl;
        #endif
        (yyval.typeNode) = (yyvsp[0].simpleTypeNode);
    }
#line 2079 "out/parser.cpp"
    break;

  case 53: /* type_decl: array_type_decl  */
#line 639 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse array type" << std::endl;
        #endif
        (yyval.typeNode) = (yyvsp[0].arrayTypeNode);
    }
#line 2090 "out/parser.cpp"
    break;

  case 54: /* type_decl: record_type_decl  */
#line 646 "src/yacc.y"
                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse record type" << std::endl;
        #endif
        (yyval.typeNode) = (yyvsp[0].recordTypeNode);
    }
#line 2101 "out/parser.cpp"
    break;

  case 55: /* record_type_decl: RECORD field_decl_list END  */
#line 655 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse record type" << std::endl;
        #endif
        (yyval.recordTypeNode) = new ast::RecordTypeNode((yyvsp[-1].fieldDeclList));
    }
#line 2112 "out/parser.cpp"
    break;

  case 56: /* field_decl_list: field_decl_list field_decl  */
#line 664 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl list 1" << std::endl;
        #endif
        (yyval.fieldDeclList) = (yyvsp[-1].fieldDeclList);
        (yyval.fieldDeclList)->push_back((yyvsp[0].fieldDeclListElement));
    }
#line 2124 "out/parser.cpp"
    break;

  case 57: /* field_decl_list: field_decl  */
#line 672 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl list 2" << std::endl;
        #endif
        (yyval.fieldDeclList) = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
        (yyval.fieldDeclList)->push_back((yyvsp[0].fieldDeclListElement));
    }
#line 2136 "out/parser.cpp"
    break;

  case 58: /* field_decl: name_list COLON type_decl SEMICOLON  */
#line 682 "src/yacc.y"
                                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl 1" << std::endl;
        #endif
        (yyval.fieldDeclListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-3].identifierList), (yyvsp[-1].typeNode));
    }
#line 2147 "out/parser.cpp"
    break;

  case 59: /* field_decl: name_list COLON type_decl  */
#line 689 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl 2" << std::endl;
        #endif
        (yyval.fieldDeclListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-2].identifierList), (yyvsp[0].typeNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2159 "out/parser.cpp"
    break;

  case 60: /* array_type_decl: ARRAY LB simple_type RB OF type_decl  */
#line 699 "src/yacc.y"
                                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse array type" << std::endl;
        #endif
        (yyval.arrayTypeNode) = new ast::ArrayTypeNode((yyvsp[-3].simpleTypeNode), (yyvsp[0].typeNode));
    }
#line 2170 "out/parser.cpp"
    break;

  case 61: /* simple_type: identifier  */
#line 708 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - identifier" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::RenameTypeNode((yyvsp[0].identifierNode));
    }
#line 2181 "out/parser.cpp"
    break;

  case 62: /* simple_type: LP name_list RP  */
#line 715 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - parentheses" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::EnumerationTypeNode((yyvsp[-1].identifierList));
    }
#line 2192 "out/parser.cpp"
    break;

  case 63: /* simple_type: const_value DOUBLEDOT const_value  */
#line 722 "src/yacc.y"
                                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - range 1" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::ConstRangeTypeNode((yyvsp[-2].constantNode), (yyvsp[0].constantNode));
    }
#line 2203 "out/parser.cpp"
    break;

  case 64: /* simple_type: identifier DOUBLEDOT identifier  */
#line 729 "src/yacc.y"
                                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - range 4" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::VarRangeTypeNode((yyvsp[-2].identifierNode), (yyvsp[0].identifierNode));
    }
#line 2214 "out/parser.cpp"
    break;

  case 65: /* simple_type: INT_TYPE  */
#line 736 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - int" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::INTEGER);
    }
#line 2225 "out/parser.cpp"
    break;

  case 66: /* simple_type: UNSIGNED_TYPE  */
#line 743 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - unsigned" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::UNSIGNED);
    }
#line 2236 "out/parser.cpp"
    break;

  case 67: /* simple_type: BOOL_TYPE  */
#line 750 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - bool" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::BOOLEAN);
    }
#line 2247 "out/parser.cpp"
    break;

  case 68: /* simple_type: CHAR_TYPE  */
#line 757 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - char" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::CHAR);
    }
#line 2258 "out/parser.cpp"
    break;

  case 69: /* simple_type: STRING_TYPE  */
#line 764 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - string" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::STRING);
    }
#line 2269 "out/parser.cpp"
    break;

  case 70: /* name_list: name_list COMMA identifier  */
#line 773 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse name list 1" << std::endl;
        #endif
        (yyval.identifierList) = (yyvsp[-2].identifierList);
        (yyval.identifierList)->push_back((yyvsp[0].identifierNode));
    }
#line 2281 "out/parser.cpp"
    break;

  case 71: /* name_list: identifier  */
#line 781 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse name list 2" << std::endl;
        #endif
        (yyval.identifierList) = new std::vector<ast::IdentifierNode*>();
        (yyval.identifierList)->push_back((yyvsp[0].identifierNode));
    }
#line 2293 "out/parser.cpp"
    break;

  case 72: /* identifier: IDENT_NAME  */
#line 791 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse identifier `" << (*(yyvsp[0].token).stringValue) << "`" << std::endl;
        #endif
        std::string name{*(yyvsp[0].token).stringValue};
        (yyval.identifierNode) = new ast::IdentifierNode(std::move(name));
    }
#line 2305 "out/parser.cpp"
    break;

  case 73: /* routine_body: compound_stmt  */
#line 801 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine body" << std::endl;
        #endif
        (yyval.routineBodyNode) = new ast::RoutineBodyNode((yyvsp[0].compoundStatementNode));
    }
#line 2316 "out/parser.cpp"
    break;

  case 74: /* compound_stmt: BBEGIN stmt_list END  */
#line 810 "src/yacc.y"
                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse compound statement 1" << std::endl;
        #endif
        (yyval.compoundStatementNode) = new ast::CompoundStatementNode((yyvsp[-1].statementNodeList));
    }
#line 2327 "out/parser.cpp"
    break;

  case 75: /* compound_stmt: BBEGIN stmt_list  */
#line 817 "src/yacc.y"
                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse compound statement 2" << std::endl;
        #endif
        (yyval.compoundStatementNode) = new ast::CompoundStatementNode((yyvsp[0].statementNodeList));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of end");
    }
#line 2339 "out/parser.cpp"
    break;

  case 76: /* stmt_list: %empty  */
#line 827 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty statement list" << std::endl;
        #endif
        (yyval.statementNodeList) = new std::vector<ast::StatementNode*>();
    }
#line 2350 "out/parser.cpp"
    break;

  case 77: /* stmt_list: stmt_list stmt SEMICOLON  */
#line 834 "src/yacc.y"
                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement list 1" << std::endl;
        #endif
        (yyval.statementNodeList) = (yyvsp[-2].statementNodeList);
        (yyval.statementNodeList)->push_back((yyvsp[-1].statementNode));
    }
#line 2362 "out/parser.cpp"
    break;

  case 78: /* stmt_list: stmt_list stmt  */
#line 842 "src/yacc.y"
                   {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement list 2" << std::endl;
        #endif
        (yyval.statementNodeList) = (yyvsp[-1].statementNodeList);
        (yyval.statementNodeList)->push_back((yyvsp[0].statementNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2375 "out/parser.cpp"
    break;

  case 79: /* stmt: INTEGER COLON no_label_stmt  */
#line 853 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement with label " << (yyvsp[-2].token).numericalValue << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].statementNode);
        (yyval.statementNode)->setLabel((yyvsp[-2].token).numericalValue);
    }
#line 2387 "out/parser.cpp"
    break;

  case 80: /* stmt: no_label_stmt  */
#line 861 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement without label" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].statementNode);
    }
#line 2398 "out/parser.cpp"
    break;

  case 81: /* no_label_stmt: assign_stmt  */
#line 870 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - assign" << std::endl;
        #endif
        (yyval.statementNode)=(yyvsp[0].assignNode);
    }
#line 2409 "out/parser.cpp"
    break;

  case 82: /* no_label_stmt: compound_stmt  */
#line 877 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - compound" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].compoundStatementNode);
    }
#line 2420 "out/parser.cpp"
    break;

  case 83: /* no_label_stmt: goto_stmt  */
#line 884 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - goto" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].gotoNode);
    }
#line 2431 "out/parser.cpp"
    break;

  case 84: /* no_label_stmt: if_stmt  */
#line 891 "src/yacc.y"
            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - if" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].ifNode);
    }
#line 2442 "out/parser.cpp"
    break;

  case 85: /* no_label_stmt: repeat_stmt  */
#line 898 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - repeat" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].repeatNode);
    }
#line 2453 "out/parser.cpp"
    break;

  case 86: /* no_label_stmt: while_stmt  */
#line 905 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - while" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].whileNode);
    }
#line 2464 "out/parser.cpp"
    break;

  case 87: /* no_label_stmt: case_stmt  */
#line 912 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - case" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].caseNode);
    }
#line 2475 "out/parser.cpp"
    break;

  case 88: /* no_label_stmt: for_stmt  */
#line 919 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - for" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].forNode);
    }
#line 2486 "out/parser.cpp"
    break;

  case 89: /* no_label_stmt: proc_stmt  */
#line 926 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - proc" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].callNode);
    }
#line 2497 "out/parser.cpp"
    break;

  case 90: /* assign_stmt: identifier ASSIGN expression  */
#line 935 "src/yacc.y"
                                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple assign statement" << std::endl;
        #endif
        (yyval.assignNode) = new ast::AssignToVariableNode((yyvsp[-2].identifierNode), (yyvsp[0].expressionNode));
    }
#line 2508 "out/parser.cpp"
    break;

  case 91: /* assign_stmt: identifier LB expression RB ASSIGN expression  */
#line 942 "src/yacc.y"
                                                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse array assign statement" << std::endl;
        #endif
        (yyval.assignNode) = new ast::AssignToArrayNode((yyvsp[-5].identifierNode), (yyvsp[-3].expressionNode), (yyvsp[0].expressionNode));
    }
#line 2519 "out/parser.cpp"
    break;

  case 92: /* assign_stmt: identifier DOT identifier ASSIGN expression  */
#line 949 "src/yacc.y"
                                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse record assign statement" << std::endl;
        #endif
        (yyval.assignNode) = new ast::AssignToRecordFieldNode((yyvsp[-4].identifierNode), (yyvsp[-2].identifierNode), (yyvsp[0].expressionNode));
    }
#line 2530 "out/parser.cpp"
    break;

  case 93: /* goto_stmt: GOTO INTEGER  */
#line 958 "src/yacc.y"
                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse goto statement to " << (yyvsp[0].token).numericalValue << std::endl;
        #endif
        (yyval.gotoNode) = new ast::GotoNode((yyvsp[0].token).numericalValue);
    }
#line 2541 "out/parser.cpp"
    break;

  case 94: /* if_stmt: IF expression THEN stmt else_clause  */
#line 967 "src/yacc.y"
                                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse if statement 1" << std::endl;
        #endif
        (yyval.ifNode) = new ast::IfNode((yyvsp[-3].expressionNode), (yyvsp[-1].statementNode), (yyvsp[0].ifNode));
    }
#line 2552 "out/parser.cpp"
    break;

  case 95: /* if_stmt: IF expression stmt else_clause  */
#line 974 "src/yacc.y"
                                   {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse if statement 2" << std::endl;
        #endif
        (yyval.ifNode) = new ast::IfNode((yyvsp[-2].expressionNode), (yyvsp[-1].statementNode), (yyvsp[0].ifNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of then");
    }
#line 2564 "out/parser.cpp"
    break;

  case 96: /* else_clause: %empty  */
#line 984 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty else clause" << std::endl;
        #endif
        (yyval.ifNode) = new ast::IfNode(nullptr, nullptr);
    }
#line 2575 "out/parser.cpp"
    break;

  case 97: /* else_clause: ELSE stmt  */
#line 991 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse else clause" << std::endl;
        #endif
        (yyval.ifNode) = new ast::IfNode(nullptr, nullptr, (yyvsp[0].statementNode));
    }
#line 2586 "out/parser.cpp"
    break;

  case 98: /* repeat_stmt: REPEAT stmt_list UNTIL expression  */
#line 1000 "src/yacc.y"
                                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse repeat statement" << std::endl;
        #endif
        (yyval.repeatNode) = new ast::RepeatNode((yyvsp[0].expressionNode), (yyvsp[-2].statementNodeList));
    }
#line 2597 "out/parser.cpp"
    break;

  case 99: /* repeat_stmt: %empty  */
#line 1007 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty repeat statement" << std::endl;
        #endif
    }
#line 2607 "out/parser.cpp"
    break;

  case 100: /* while_stmt: WHILE expression DO stmt  */
#line 1015 "src/yacc.y"
                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse while statement" << std::endl;
        #endif
        (yyval.whileNode) = new ast::WhileNode((yyvsp[-2].expressionNode), (yyvsp[0].statementNode));
    }
#line 2618 "out/parser.cpp"
    break;

  case 101: /* case_stmt: CASE expression OF case_expr_list END  */
#line 1024 "src/yacc.y"
                                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case statement" << std::endl;
        #endif
        (yyval.caseNode) = new ast::CaseNode((yyvsp[-3].expressionNode), (yyvsp[-1].caseExprList));
    }
#line 2629 "out/parser.cpp"
    break;

  case 102: /* case_expr_list: case_expr_list case_expr  */
#line 1033 "src/yacc.y"
                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr list 1" << std::endl;
        #endif
        (yyval.caseExprList) = (yyvsp[-1].caseExprList);
        (yyval.caseExprList)->push_back((yyvsp[0].caseExpr));
    }
#line 2641 "out/parser.cpp"
    break;

  case 103: /* case_expr_list: case_expr  */
#line 1041 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr list 2" << std::endl;
        #endif
        (yyval.caseExprList) = new std::vector<std::pair<ast::AstNode*, ast::StatementNode*>*>();
        (yyval.caseExprList)->push_back((yyvsp[0].caseExpr));
    }
#line 2653 "out/parser.cpp"
    break;

  case 104: /* case_expr: const_value COLON stmt SEMICOLON  */
#line 1051 "src/yacc.y"
                                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr 1" << std::endl;
        #endif
        (yyval.caseExpr) = new std::pair<ast::AstNode*, ast::StatementNode*>((yyvsp[-3].constantNode), (yyvsp[-1].statementNode));
    }
#line 2664 "out/parser.cpp"
    break;

  case 105: /* case_expr: identifier COLON stmt SEMICOLON  */
#line 1058 "src/yacc.y"
                                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr 2" << std::endl;
        #endif
        (yyval.caseExpr) = new std::pair<ast::AstNode*, ast::StatementNode*>((yyvsp[-3].identifierNode), (yyvsp[-1].statementNode));
    }
#line 2675 "out/parser.cpp"
    break;

  case 106: /* for_stmt: FOR identifier ASSIGN expression TO expression DO stmt  */
#line 1067 "src/yacc.y"
                                                           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse for statement 1" << std::endl;
        #endif
        (yyval.forNode) = new ast::ForNode((yyvsp[-6].identifierNode), (yyvsp[-4].expressionNode), (yyvsp[-2].expressionNode), (yyvsp[0].statementNode), ast::ForNode::Direction::INCREMENT);
    }
#line 2686 "out/parser.cpp"
    break;

  case 107: /* for_stmt: FOR identifier ASSIGN expression DOWNTO expression DO stmt  */
#line 1074 "src/yacc.y"
                                                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse for statement 2" << std::endl;
        #endif
        (yyval.forNode) = new ast::ForNode((yyvsp[-6].identifierNode), (yyvsp[-4].expressionNode), (yyvsp[-2].expressionNode), (yyvsp[0].statementNode), ast::ForNode::Direction::DECREMENT);
    }
#line 2697 "out/parser.cpp"
    break;

  case 108: /* proc_stmt: identifier  */
#line 1083 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse procedure statement" << std::endl;
        #endif
        (yyval.callNode) = new ast::UserDefineCallNode((yyvsp[0].identifierNode), nullptr);
    }
#line 2708 "out/parser.cpp"
    break;

  case 109: /* proc_stmt: identifier LP args_list RP  */
#line 1090 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse procedure statement with args" << std::endl;
        #endif
        (yyval.callNode) = new ast::UserDefineCallNode((yyvsp[-3].identifierNode), (yyvsp[-1].argsList));
    }
#line 2719 "out/parser.cpp"
    break;

  case 110: /* proc_stmt: READ LP factor RP  */
#line 1097 "src/yacc.y"
                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse read statement" << std::endl;
        #endif
        ast::ArgumentsListNode* args = new ast::ArgumentsListNode();
        args->addArgument((yyvsp[-1].expressionNode));
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::READ, args);
    }
#line 2732 "out/parser.cpp"
    break;

  case 111: /* proc_stmt: READLN  */
#line 1107 "src/yacc.y"
           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse readln statement" << std::endl;
        #endif
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::READLN, nullptr);
    }
#line 2743 "out/parser.cpp"
    break;

  case 112: /* proc_stmt: WRITE LP args_list RP  */
#line 1114 "src/yacc.y"
                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse write statement" << std::endl;
        #endif
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITE, (yyvsp[-1].argsList));
    }
#line 2754 "out/parser.cpp"
    break;

  case 113: /* proc_stmt: WRITELN  */
#line 1121 "src/yacc.y"
            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse writeln statement" << std::endl;
        #endif
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITELN, nullptr);
    }
#line 2765 "out/parser.cpp"
    break;

  case 114: /* proc_stmt: WRITELN LP args_list RP  */
#line 1128 "src/yacc.y"
                            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse writeln statement with args" << std::endl;
        #endif
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITELN, (yyvsp[-1].argsList));
    }
#line 2776 "out/parser.cpp"
    break;

  case 115: /* args_list: args_list COMMA expression  */
#line 1137 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse args list 1" << std::endl;
        #endif
        (yyval.argsList) = (yyvsp[-2].argsList);
        (yyval.argsList)->addArgument((yyvsp[0].expressionNode));
    }
#line 2788 "out/parser.cpp"
    break;

  case 116: /* args_list: expression  */
#line 1145 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse args list 2" << std::endl;
        #endif
        (yyval.argsList) = new ast::ArgumentsListNode();
        (yyval.argsList)->addArgument((yyvsp[0].expressionNode));
    }
#line 2800 "out/parser.cpp"
    break;

  case 117: /* expression: expression GE expr  */
#line 1155 "src/yacc.y"
                       {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with greater or equal" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::GREATER_EQUAL);
    }
#line 2811 "out/parser.cpp"
    break;

  case 118: /* expression: expression GT expr  */
#line 1162 "src/yacc.y"
                       {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with greater" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::GREATER);
    }
#line 2822 "out/parser.cpp"
    break;

  case 119: /* expression: expression LE expr  */
#line 1169 "src/yacc.y"
                       {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with less or equal" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::LESS_EQUAL);
    }
#line 2833 "out/parser.cpp"
    break;

  case 120: /* expression: expression LT expr  */
#line 1176 "src/yacc.y"
                       {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with less" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::LESS);
    }
#line 2844 "out/parser.cpp"
    break;

  case 121: /* expression: expression EQUAL expr  */
#line 1183 "src/yacc.y"
                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with equal" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::EQUAL);
    }
#line 2855 "out/parser.cpp"
    break;

  case 122: /* expression: expression UNEQUAL expr  */
#line 1190 "src/yacc.y"
                            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with not equal" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::NOT_EQUAL);
    }
#line 2866 "out/parser.cpp"
    break;

  case 123: /* expression: expr  */
#line 1197 "src/yacc.y"
         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple expression" << std::endl;
        #endif
        (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 2877 "out/parser.cpp"
    break;

  case 124: /* expr: expr PLUS term  */
#line 1206 "src/yacc.y"
                   {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with addition" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::ADDITION);
    }
#line 2888 "out/parser.cpp"
    break;

  case 125: /* expr: expr MINUS term  */
#line 1213 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with subtraction" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::SUBTRACTION);
    }
#line 2899 "out/parser.cpp"
    break;

  case 126: /* expr: expr OR term  */
#line 1220 "src/yacc.y"
                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with or" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::OR);
    }
#line 2910 "out/parser.cpp"
    break;

  case 127: /* expr: term  */
#line 1227 "src/yacc.y"
         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple term" << std::endl;
        #endif
        (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 2921 "out/parser.cpp"
    break;

  case 128: /* term: term MUL factor  */
#line 1236 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with multiplication" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::MULTIPLICATION);
    }
#line 2932 "out/parser.cpp"
    break;

  case 129: /* term: term DIV factor  */
#line 1243 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with division" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::DIVISION);
    }
#line 2943 "out/parser.cpp"
    break;

  case 130: /* term: term MOD factor  */
#line 1250 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with modulus" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::MODULUS);
    }
#line 2954 "out/parser.cpp"
    break;

  case 131: /* term: term AND factor  */
#line 1257 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with and" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::AND);
    }
#line 2965 "out/parser.cpp"
    break;

  case 132: /* term: factor  */
#line 1264 "src/yacc.y"
           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple factor" << std::endl;
        #endif
        (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 2976 "out/parser.cpp"
    break;

  case 133: /* factor: identifier  */
#line 1273 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - identifier" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[0].identifierNode), ast::SpecialExpressionNode::FunctionName::VARIABLE);
    }
#line 2987 "out/parser.cpp"
    break;

  case 134: /* factor: identifier LP args_list RP  */
#line 1280 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - function call" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-3].identifierNode), (yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::CALL);
    }
#line 2998 "out/parser.cpp"
    break;

  case 135: /* factor: const_value  */
#line 1287 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - const value" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[0].constantNode), ast::SpecialExpressionNode::FunctionName::CONST);
    }
#line 3009 "out/parser.cpp"
    break;

  case 136: /* factor: LP expression RP  */
#line 1294 "src/yacc.y"
                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - parentheses" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].expressionNode), ast::SpecialExpressionNode::FunctionName::PARENTHESIS);
    }
#line 3020 "out/parser.cpp"
    break;

  case 137: /* factor: NOT factor  */
#line 1301 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - not" << std::endl;
        #endif
       (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[0].expressionNode), ast::ExpressionNode::Operation::NOT);
    }
#line 3031 "out/parser.cpp"
    break;

  case 138: /* factor: MINUS factor  */
#line 1308 "src/yacc.y"
                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - negation" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[0].expressionNode), ast::ExpressionNode::Operation::NEGATION);
    }
#line 3042 "out/parser.cpp"
    break;

  case 139: /* factor: identifier LB expression RB  */
#line 1315 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - array access" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-3].identifierNode), (yyvsp[-1].expressionNode), ast::SpecialExpressionNode::FunctionName::ARRAY_ACCESS);
    }
#line 3053 "out/parser.cpp"
    break;

  case 140: /* factor: identifier DOT identifier  */
#line 1322 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - record access" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-2].identifierNode), (yyvsp[0].identifierNode), ast::SpecialExpressionNode::FunctionName::RECORD_ACCESS);
    }
#line 3064 "out/parser.cpp"
    break;

  case 141: /* factor: ABS LP args_list RP  */
#line 1329 "src/yacc.y"
                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - abs" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::ABS);
    }
#line 3075 "out/parser.cpp"
    break;

  case 142: /* factor: CHR LP args_list RP  */
#line 1336 "src/yacc.y"
                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - chr" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::CHR);
    }
#line 3086 "out/parser.cpp"
    break;

  case 143: /* factor: ODD LP args_list RP  */
#line 1343 "src/yacc.y"
                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - odd" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::ODD);
    }
#line 3097 "out/parser.cpp"
    break;

  case 144: /* factor: ORD LP args_list RP  */
#line 1350 "src/yacc.y"
                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - ord" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::ORD);
    }
#line 3108 "out/parser.cpp"
    break;

  case 145: /* factor: PRED LP args_list RP  */
#line 1357 "src/yacc.y"
                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - pred" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::PRED);
    }
#line 3119 "out/parser.cpp"
    break;

  case 146: /* factor: SUCC LP args_list RP  */
#line 1364 "src/yacc.y"
                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - succ" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::SUCC);
    }
#line 3130 "out/parser.cpp"
    break;


#line 3134 "out/parser.cpp"

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

#line 1371 "src/yacc.y"


void yyerror(const char *s) {
    std::cerr << "Error: " << s << " at line " << linesCounter << std::endl;
}

std::unique_ptr<ast::ProgramNode> parse(const std::string& inputFileName, std::vector<std::string>& errors) {
    yyin = fopen(inputFileName.c_str(), "r");

    if(yyin == nullptr) {
        std::cerr << "Cannot open file " << inputFileName << std::endl;
    }

    yyparse();
    fclose(yyin);

    errors = std::move(parsingErrors);
    return std::unique_ptr<ast::ProgramNode>(resultAst);
}
