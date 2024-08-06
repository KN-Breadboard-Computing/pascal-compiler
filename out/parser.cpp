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
#include "../src/LookupTable.hpp"

#define YACC_DEBUG

ast::ProgramNode* resultAst;
std::vector<std::string> parsingErrors;
bool fatalError = false;
LookupTable lookupTable;

static void yyerror(const char *msg);
static int yyparse(void);
int yylex(void);

extern FILE* yyin;
extern uint64_t linesCounter;

#line 96 "out/parser.cpp"

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
#define YYLAST   611

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  80
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  152
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  308

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
       0,   175,   175,   188,   202,   216,   232,   241,   250,   257,
     265,   273,   281,   291,   300,   310,   320,   332,   345,   356,
     369,   377,   386,   394,   404,   411,   420,   427,   436,   444,
     454,   461,   471,   478,   487,   495,   505,   512,   522,   529,
     536,   544,   555,   562,   569,   576,   585,   592,   601,   609,
     619,   626,   636,   643,   650,   659,   668,   676,   686,   693,
     703,   712,   719,   726,   733,   740,   747,   754,   761,   770,
     778,   788,   798,   807,   814,   824,   831,   839,   850,   858,
     867,   874,   881,   888,   895,   902,   909,   916,   923,   930,
     937,   946,   953,   960,   969,   978,   985,   995,  1002,  1011,
    1018,  1026,  1035,  1044,  1052,  1062,  1069,  1076,  1085,  1092,
    1101,  1108,  1115,  1125,  1132,  1139,  1146,  1153,  1160,  1167,
    1174,  1183,  1191,  1201,  1208,  1215,  1222,  1229,  1236,  1243,
    1252,  1259,  1266,  1273,  1282,  1289,  1296,  1303,  1310,  1319,
    1326,  1333,  1340,  1347,  1354,  1361,  1368,  1375,  1382,  1389,
    1396,  1403,  1410
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

#define YYPACT_NINF (-183)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       5,     6,    26,     4,  -183,    17,    45,    19,    79,    50,
    -183,    17,  -183,    70,    52,  -183,  -183,  -183,  -183,    17,
     112,  -183,    54,  -183,    20,    17,  -183,    91,    17,    85,
    -183,  -183,  -183,  -183,  -183,  -183,     9,   129,  -183,    71,
      87,  -183,   117,   126,   143,   160,   170,   183,   502,  -183,
     502,   502,    17,   217,  -183,  -183,    58,  -183,   174,  -183,
    -183,  -183,  -183,  -183,  -183,  -183,  -183,  -183,  -183,   454,
      17,  -183,   105,  -183,   234,   236,    85,  -183,    18,  -183,
     185,  -183,  -183,  -183,   387,   502,   502,   502,   502,   502,
     502,   502,   188,   190,   191,   192,   200,   201,   550,   502,
     502,  -183,    23,   282,    48,    -4,  -183,   327,   154,   -11,
     213,  -183,   502,   502,   502,    17,  -183,    17,  -183,  -183,
    -183,  -183,   205,    17,   202,   209,  -183,  -183,  -183,   203,
    -183,    17,   454,   204,   204,  -183,  -183,    45,   210,    45,
    -183,   215,   -44,   265,    -7,    14,    47,    75,    78,   502,
     502,   502,   502,   502,   502,  -183,  -183,  -183,  -183,    84,
     502,   502,    17,   357,   502,   502,   502,   502,   502,   502,
     240,   502,   502,   502,   502,   502,   502,   502,   502,   357,
     433,   502,   265,   211,    81,   228,   102,   475,   114,  -183,
     128,    54,  -183,    17,  -183,   216,    96,   222,  -183,   232,
    -183,   233,  -183,  -183,   502,  -183,  -183,  -183,  -183,  -183,
     107,   115,   118,   123,   124,   161,  -183,   239,   166,  -183,
     240,    48,    48,    48,    48,    48,    48,   357,  -183,    -4,
      -4,    -4,  -183,  -183,  -183,  -183,   265,  -183,   357,   250,
     252,   425,  -183,   164,   230,  -183,   502,  -183,   261,  -183,
    -183,   454,  -183,  -183,  -183,    17,    88,  -183,   168,   475,
    -183,  -183,   265,  -183,  -183,  -183,  -183,  -183,  -183,  -183,
    -183,  -183,  -183,   237,   357,   357,  -183,  -183,   502,   502,
     502,   265,   251,   260,   176,  -183,    96,   475,  -183,  -183,
     269,   270,   296,   434,   265,   454,  -183,   475,  -183,  -183,
    -183,  -183,   357,   357,  -183,  -183,  -183,  -183
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    32,     1,     0,    32,     5,     0,    46,
      71,    33,    35,     0,     3,     4,    75,     6,    72,     0,
      26,    34,     0,     2,    74,    47,    49,     0,     0,     8,
      38,    40,    41,    42,    43,    44,     0,    37,    73,     0,
       0,   113,     0,   115,     0,     0,     0,     0,     0,    75,
       0,     0,     0,     0,    89,    90,   110,    81,    77,    79,
      80,    82,    83,    84,    85,    86,    87,    88,    48,     0,
      27,    29,     0,    70,     0,     0,     7,    11,    32,    12,
       0,    39,    45,    36,   100,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   141,   139,   100,   129,   133,   138,   100,     0,     0,
       0,    94,     0,     0,     0,     0,    76,     0,    65,    66,
      67,    68,     0,     0,     0,    51,    54,    53,    52,    61,
      28,     0,     0,    20,    20,     9,    10,    32,    16,    32,
      78,     0,     0,   122,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    38,    44,   144,   143,     0,
       0,     0,     0,   100,     0,     0,     0,     0,     0,     0,
      97,     0,     0,     0,     0,     0,     0,     0,     0,   100,
       0,     0,    91,     0,     0,     0,     0,     0,     0,    57,
       0,     0,    50,     0,    69,    31,     0,     0,    19,    14,
      15,     0,   112,   114,     0,   116,   117,   118,   119,   120,
       0,     0,     0,     0,     0,     0,   142,     0,     0,   146,
      97,   127,   128,   123,   124,   125,   126,   100,    96,   130,
     131,   132,   134,   135,   137,   136,    99,   101,   100,     0,
       0,     0,   104,     0,     0,   111,     0,    62,     0,    55,
      56,     0,    63,    64,    30,     0,     0,    23,     0,     0,
      13,    18,   121,   147,   148,   149,   150,   151,   152,   145,
     140,    95,    98,     0,   100,   100,   102,   103,     0,     0,
       0,    93,     0,    59,     0,    21,     0,     0,    17,   107,
       0,     0,     0,     0,    92,     0,    58,     0,    22,    25,
     105,   106,   100,   100,    60,    24,   108,   109
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -183,  -183,    -3,  -183,  -183,   258,  -183,   278,  -183,   221,
    -183,    51,  -183,  -183,   286,  -183,  -183,   350,   -21,  -183,
    -183,   337,  -128,  -183,  -183,   184,  -183,  -182,  -110,    -5,
    -183,   363,   324,   -78,   290,  -183,  -183,  -183,   155,  -183,
    -183,  -183,  -183,   150,  -183,  -183,    65,   -39,   220,   -10,
     -83
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     7,     8,    76,    77,    78,    79,    80,   197,
     256,   257,    29,    70,    71,     9,    11,    12,   101,    20,
      25,    26,   125,   126,   188,   189,   127,   128,    72,   102,
      17,    57,    24,    58,    59,    60,    61,    62,   228,    63,
      64,    65,   241,   242,    66,    67,   142,   143,   104,   105,
     106
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      13,    37,   141,    14,   195,   248,    13,   186,     1,   103,
       5,   108,   109,   190,    27,   157,   158,     3,   203,    56,
      27,    81,   204,    73,     5,   170,     4,    82,    10,    16,
      38,    10,    39,   164,   165,   166,   167,   168,   169,    40,
      41,    42,    43,    44,    45,    46,    47,   110,   124,   174,
     175,     5,   176,    48,   177,   205,    49,    19,    50,   204,
      51,   159,   180,    52,   129,    73,    30,     6,    31,    32,
      33,    34,    35,   182,   183,   138,   206,   288,   190,    56,
     204,   137,   160,    15,   161,   220,   258,   162,    16,    74,
      75,   232,   233,   234,   235,    53,    54,    55,    56,   171,
     172,   237,    56,   173,   255,   299,    36,    10,   112,   207,
     185,   124,    73,   204,    22,   305,    23,   113,    73,   114,
      28,   217,   115,   283,   249,    10,   194,   129,   164,   165,
     166,   167,   168,   169,   199,    69,   201,   208,    84,   236,
     209,   204,   243,   245,   204,   284,   216,   204,    85,   272,
     285,   286,   144,   145,   146,   147,   148,   219,    56,   239,
     273,   229,   230,   231,   247,   262,   124,   304,   131,   263,
     252,   131,   132,   204,    56,   240,   258,   264,    86,   184,
     265,   204,   129,    73,   204,   266,   267,    87,   253,   204,
     204,    73,    83,   179,   131,   251,   290,   291,   164,   165,
     166,   167,   168,   169,    88,   278,   279,   281,   164,   165,
     166,   167,   168,   169,   210,   211,   212,   213,   214,   215,
     239,    89,    56,   268,   306,   307,   218,   204,   270,   111,
     124,    90,   204,    56,   131,   287,   240,   116,   124,   292,
     293,   294,   131,   297,    91,   133,   129,   134,   139,   149,
      73,   150,   151,   152,   129,   164,   165,   166,   167,   168,
     169,   153,   154,   181,   187,   196,   124,   191,   193,    56,
      56,   244,   192,   200,   124,   227,   124,   202,   246,   254,
     280,    73,   129,   164,   165,   166,   167,   168,   169,   259,
     129,    16,   129,    10,    39,   260,   261,    56,    56,   269,
     289,    40,    41,    42,    43,    44,    45,    46,    47,   164,
     165,   166,   167,   168,   169,    48,   163,   274,    49,   275,
      50,   282,    51,   296,   295,    52,   164,   165,   166,   167,
     168,   169,   300,   301,   135,   302,    16,   298,    10,    39,
     164,   165,   166,   167,   168,   169,    40,    41,    42,    43,
      44,    45,    46,    47,   136,   198,   130,    53,    54,    55,
      48,    21,    68,    49,   178,    50,    16,    51,    10,    39,
      52,    18,   250,   107,   140,   271,    40,    41,    42,    43,
      44,    45,    46,    47,   221,   222,   223,   224,   225,   226,
      48,   277,     0,    49,     0,    50,    16,    51,    10,     0,
      52,     0,    53,    54,    55,     0,    40,    41,    42,    43,
      44,    45,    46,    47,     0,     0,     0,     0,     0,     0,
      48,     0,     0,    49,     0,    50,     0,    51,     0,     0,
      52,     0,    53,    54,    55,   276,    10,    30,     0,    31,
      32,    33,    34,    35,    10,    30,     0,    31,    32,    33,
      34,    35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    53,    54,    55,    10,    30,     0,    31,    32,
      33,    34,    35,   303,     0,     0,     0,    36,   164,   165,
     166,   167,   168,   169,     0,    36,    10,    30,     0,    31,
      32,    33,    34,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   238,     0,     0,    36,     0,     0,     0,
       0,   238,     0,    10,    30,   117,    31,    32,    33,    34,
      35,     0,   118,   119,   120,   121,   122,    36,   123,    92,
      93,    94,    95,    96,    97,     0,   117,     0,     0,     0,
       0,     0,     0,   118,   119,   120,   121,     0,     0,     0,
       0,     0,     0,     0,    98,     0,     0,     0,     0,    99,
       0,    10,   155,   100,    31,    32,    33,    34,   156,     0,
       0,     0,     0,     0,     0,     0,     0,    92,    93,    94,
      95,    96,    97,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    98,     0,     0,     0,     0,    99,     0,     0,
       0,   100
};

static const yytype_int16 yycheck[] =
{
       5,    22,    85,     6,   132,   187,    11,   117,     3,    48,
       6,    50,    51,   123,    19,    98,    99,    11,    62,    24,
      25,    12,    66,    28,     6,   103,     0,    18,    11,     9,
      10,    11,    12,    44,    45,    46,    47,    48,    49,    19,
      20,    21,    22,    23,    24,    25,    26,    52,    69,    53,
      54,     6,    56,    33,    58,    62,    36,     7,    38,    66,
      40,   100,    73,    43,    69,    70,    12,    63,    14,    15,
      16,    17,    18,   112,   113,    78,    62,   259,   188,    84,
      66,    63,    59,    64,    61,   163,   196,    64,     9,     4,
       5,   174,   175,   176,   177,    75,    76,    77,   103,    51,
      52,   179,   107,    55,     8,   287,    52,    11,    50,    62,
     115,   132,   117,    66,    44,   297,    64,    59,   123,    61,
       8,   160,    64,   251,    10,    11,   131,   132,    44,    45,
      46,    47,    48,    49,   137,    44,   139,    62,    67,   178,
      62,    66,   181,    62,    66,   255,    62,    66,    61,   227,
      62,    63,    87,    88,    89,    90,    91,   162,   163,   180,
     238,   171,   172,   173,    62,   204,   187,   295,    66,    62,
     191,    66,    67,    66,   179,   180,   286,    62,    61,   114,
      62,    66,   187,   188,    66,    62,    62,    61,   193,    66,
      66,   196,    63,    39,    66,    67,   274,   275,    44,    45,
      46,    47,    48,    49,    61,    41,    42,   246,    44,    45,
      46,    47,    48,    49,   149,   150,   151,   152,   153,   154,
     241,    61,   227,    62,   302,   303,   161,    66,    62,    12,
     251,    61,    66,   238,    66,    67,   241,    63,   259,   278,
     279,   280,    66,    67,    61,    11,   251,    11,    63,    61,
     255,    61,    61,    61,   259,    44,    45,    46,    47,    48,
      49,    61,    61,    50,    59,    61,   287,    65,    65,   274,
     275,    60,    63,    63,   295,    35,   297,    62,    50,    63,
      50,   286,   287,    44,    45,    46,    47,    48,    49,    67,
     295,     9,   297,    11,    12,    63,    63,   302,   303,    60,
      63,    19,    20,    21,    22,    23,    24,    25,    26,    44,
      45,    46,    47,    48,    49,    33,    34,    67,    36,    67,
      38,    60,    40,    63,    73,    43,    44,    45,    46,    47,
      48,    49,    63,    63,    76,    39,     9,   286,    11,    12,
      44,    45,    46,    47,    48,    49,    19,    20,    21,    22,
      23,    24,    25,    26,    76,   134,    70,    75,    76,    77,
      33,    11,    25,    36,    37,    38,     9,    40,    11,    12,
      43,     8,   188,    49,    84,   220,    19,    20,    21,    22,
      23,    24,    25,    26,   164,   165,   166,   167,   168,   169,
      33,   241,    -1,    36,    -1,    38,     9,    40,    11,    -1,
      43,    -1,    75,    76,    77,    -1,    19,    20,    21,    22,
      23,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    -1,    -1,    36,    -1,    38,    -1,    40,    -1,    -1,
      43,    -1,    75,    76,    77,    10,    11,    12,    -1,    14,
      15,    16,    17,    18,    11,    12,    -1,    14,    15,    16,
      17,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    76,    77,    11,    12,    -1,    14,    15,
      16,    17,    18,    39,    -1,    -1,    -1,    52,    44,    45,
      46,    47,    48,    49,    -1,    52,    11,    12,    -1,    14,
      15,    16,    17,    18,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    78,    -1,    -1,    52,    -1,    -1,    -1,
      -1,    78,    -1,    11,    12,    61,    14,    15,    16,    17,
      18,    -1,    68,    69,    70,    71,    72,    52,    74,    27,
      28,    29,    30,    31,    32,    -1,    61,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    57,
      -1,    11,    12,    61,    14,    15,    16,    17,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    28,    29,
      30,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    52,    -1,    -1,    -1,    -1,    57,    -1,    -1,
      -1,    61
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
     114,   130,   126,   127,   126,   126,   126,   126,   126,    61,
      61,    61,    61,    61,    61,    12,    18,   130,   130,   127,
      59,    61,    64,    34,    44,    45,    46,    47,    48,    49,
     113,    51,    52,    55,    53,    54,    56,    58,    37,    39,
      73,    50,   127,   127,   126,   109,   108,    59,   104,   105,
     108,    65,    63,    65,   109,   102,    61,    89,    89,    82,
      63,    82,    62,    62,    66,    62,    62,    62,    62,    62,
     126,   126,   126,   126,   126,   126,    62,   127,   126,   109,
     113,   128,   128,   128,   128,   128,   128,    35,   118,   129,
     129,   129,   130,   130,   130,   130,   127,   113,    78,    98,
     109,   122,   123,   127,    60,    62,    50,    62,   107,    10,
     105,    67,    98,   109,    63,     8,    90,    91,   108,    67,
      63,    63,   127,    62,    62,    62,    62,    62,    62,    60,
      62,   118,   113,   113,    67,    67,    10,   123,    41,    42,
      50,   127,    60,   102,   108,    62,    63,    67,   107,    63,
     113,   113,   127,   127,   127,    73,    63,    67,    91,   107,
      63,    63,    39,    39,   102,   107,   113,   113
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    80,    81,    81,    81,    81,    82,    83,    84,    84,
      84,    84,    84,    85,    85,    85,    85,    86,    87,    88,
      89,    89,    90,    90,    91,    91,    92,    92,    93,    93,
      94,    94,    95,    95,    96,    96,    97,    97,    98,    98,
      98,    98,    98,    98,    98,    98,    99,    99,   100,   100,
     101,   101,   102,   102,   102,   103,   104,   104,   105,   105,
     106,   107,   107,   107,   107,   107,   107,   107,   107,   108,
     108,   109,   110,   111,   111,   112,   112,   112,   113,   113,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   115,   115,   115,   116,   117,   117,   118,   118,   119,
     119,   120,   121,   122,   122,   123,   123,   123,   124,   124,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   126,   126,   127,   127,   127,   127,   127,   127,   127,
     128,   128,   128,   128,   129,   129,   129,   129,   129,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130
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
       6,     1,     3,     3,     3,     1,     1,     1,     1,     3,
       1,     1,     1,     3,     2,     0,     3,     2,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     6,     5,     2,     5,     4,     0,     2,     4,
       0,     4,     5,     2,     1,     4,     4,     3,     8,     8,
       1,     4,     4,     1,     4,     1,     4,     4,     4,     4,
       4,     3,     1,     3,     3,     3,     3,     3,     3,     1,
       3,     3,     3,     1,     3,     3,     3,     3,     1,     1,
       4,     1,     3,     2,     2,     4,     3,     4,     4,     4,
       4,     4,     4
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
#line 175 "src/yacc.y"
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
#line 1505 "out/parser.cpp"
    break;

  case 3: /* program: PROGRAM IDENT_NAME SEMICOLON routine  */
#line 188 "src/yacc.y"
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
#line 1523 "out/parser.cpp"
    break;

  case 4: /* program: PROGRAM IDENT_NAME routine DOT  */
#line 202 "src/yacc.y"
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
#line 1541 "out/parser.cpp"
    break;

  case 5: /* program: PROGRAM IDENT_NAME routine  */
#line 216 "src/yacc.y"
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
#line 1559 "out/parser.cpp"
    break;

  case 6: /* routine: routine_head routine_body  */
#line 232 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine" << std::endl;
        #endif
        (yyval.routineNode) = new ast::RoutineNode((yyvsp[-1].routineHeadNode), (yyvsp[0].routineBodyNode));
    }
#line 1570 "out/parser.cpp"
    break;

  case 7: /* routine_head: const_part type_part var_part routine_part  */
#line 241 "src/yacc.y"
                                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine head" << std::endl;
        #endif
        (yyval.routineHeadNode) = new ast::RoutineHeadNode((yyvsp[-3].constPartList), (yyvsp[-2].typePartList), (yyvsp[-1].varPartList), (yyvsp[0].routinePartList));
    }
#line 1581 "out/parser.cpp"
    break;

  case 8: /* routine_part: %empty  */
#line 250 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty routine part" << std::endl;
        #endif
        (yyval.routinePartList) = new std::vector<ast::RoutineDeclarationNode*>();
    }
#line 1592 "out/parser.cpp"
    break;

  case 9: /* routine_part: routine_part fun_decl  */
#line 257 "src/yacc.y"
                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine part with fun decl 1" << std::endl;
        #endif
        (yyval.routinePartList) = (yyvsp[-1].routinePartList);
        (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1604 "out/parser.cpp"
    break;

  case 10: /* routine_part: routine_part proc_decl  */
#line 265 "src/yacc.y"
                           {
       #ifdef YACC_DEBUG
           std::cout << "Yacc debug: Parse routine part with proc decl 1" << std::endl;
       #endif
       (yyval.routinePartList) = (yyvsp[-1].routinePartList);
       (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1616 "out/parser.cpp"
    break;

  case 11: /* routine_part: fun_decl  */
#line 273 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine part with fun decl 2" << std::endl;
        #endif
        (yyval.routinePartList) = new std::vector<ast::RoutineDeclarationNode*>();
        (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1628 "out/parser.cpp"
    break;

  case 12: /* routine_part: proc_decl  */
#line 281 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine part with proc decl 2" << std::endl;
        #endif
        (yyval.routinePartList) = new std::vector<ast::RoutineDeclarationNode*>();
        (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1640 "out/parser.cpp"
    break;

  case 13: /* fun_decl: fun_head SEMICOLON routine SEMICOLON  */
#line 291 "src/yacc.y"
                                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun decl 1" << std::endl;
        #endif
        (yyval.routineDeclarationNode) = (yyvsp[-3].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[-1].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
    }
#line 1653 "out/parser.cpp"
    break;

  case 14: /* fun_decl: fun_head SEMICOLON routine  */
#line 300 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun decl 2" << std::endl;
        #endif
        (yyval.routineDeclarationNode) = (yyvsp[-2].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[0].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1667 "out/parser.cpp"
    break;

  case 15: /* fun_decl: fun_head routine SEMICOLON  */
#line 310 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun decl 3" << std::endl;
        #endif
        (yyval.routineDeclarationNode) = (yyvsp[-2].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[-1].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1681 "out/parser.cpp"
    break;

  case 16: /* fun_decl: fun_head routine  */
#line 320 "src/yacc.y"
                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun decl 4" << std::endl;
        #endif
        (yyval.routineDeclarationNode) = (yyvsp[-1].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[0].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1695 "out/parser.cpp"
    break;

  case 17: /* fun_head: FUNCTION IDENT_NAME params COLON simple_type  */
#line 332 "src/yacc.y"
                                                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun head " << (*(yyvsp[-3].token).stringValue) << std::endl;
        #endif

        lookupTable.pushNamespace("@" + (*(yyvsp[-3].token).stringValue));

        std::string name{*(yyvsp[-3].token).stringValue};
        (yyval.routineDeclarationNode) = new ast::RoutineDeclarationNode(ast::RoutineDeclarationNode::RoutineType::FUNCTION, std::move(name), (yyvsp[-2].paramsNode), (yyvsp[0].simpleTypeNode), nullptr);
    }
#line 1710 "out/parser.cpp"
    break;

  case 18: /* proc_decl: proc_head SEMICOLON routine SEMICOLON  */
#line 345 "src/yacc.y"
                                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse proc decl" << std::endl;
        #endif
        (yyval.routineDeclarationNode) = (yyvsp[-3].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[-1].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::PROCEDURE);
    }
#line 1723 "out/parser.cpp"
    break;

  case 19: /* proc_head: PROCEDURE IDENT_NAME params  */
#line 356 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse proc head " << (*(yyvsp[-1].token).stringValue) << std::endl;
        #endif

        lookupTable.pushNamespace("@" + (*(yyvsp[-1].token).stringValue));

        std::string name{*(yyvsp[-1].token).stringValue};
        (yyval.routineDeclarationNode) = new ast::RoutineDeclarationNode(ast::RoutineDeclarationNode::RoutineType::PROCEDURE, std::move(name), (yyvsp[0].paramsNode), nullptr, nullptr);
    }
#line 1738 "out/parser.cpp"
    break;

  case 20: /* params: %empty  */
#line 369 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty params" << std::endl;
        #endif
        std::vector<ast::ParamsGroupNode *>* emptyParamsList{};
        (yyval.paramsNode) = new ast::ParamsNode(emptyParamsList);
    }
#line 1750 "out/parser.cpp"
    break;

  case 21: /* params: LP params_decl RP  */
#line 377 "src/yacc.y"
                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params" << std::endl;
        #endif  
        (yyval.paramsNode) = new ast::ParamsNode((yyvsp[-1].paramsGroupList));
    }
#line 1761 "out/parser.cpp"
    break;

  case 22: /* params_decl: params_decl SEMICOLON params_type  */
#line 386 "src/yacc.y"
                                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params decl 1" << std::endl;
        #endif
        (yyval.paramsGroupList) = (yyvsp[-2].paramsGroupList);
        (yyval.paramsGroupList)->push_back((yyvsp[0].paramsGroupNode));
    }
#line 1773 "out/parser.cpp"
    break;

  case 23: /* params_decl: params_type  */
#line 394 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params decl 2" << std::endl;
        #endif
        (yyval.paramsGroupList) = new std::vector<ast::ParamsGroupNode*>();
        (yyval.paramsGroupList)->push_back((yyvsp[0].paramsGroupNode));
    }
#line 1785 "out/parser.cpp"
    break;

  case 24: /* params_type: VAR name_list COLON simple_type  */
#line 404 "src/yacc.y"
                                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params type 1" << std::endl;
        #endif
        (yyval.paramsGroupNode) = new ast::ParamsGroupNode(ast::ParamsGroupNode::PassType::PASS_BY_REFERENCE, (yyvsp[-2].identifierList), (yyvsp[0].simpleTypeNode));
    }
#line 1796 "out/parser.cpp"
    break;

  case 25: /* params_type: name_list COLON simple_type  */
#line 411 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params type 2" << std::endl;
        #endif
        (yyval.paramsGroupNode) = new ast::ParamsGroupNode(ast::ParamsGroupNode::PassType::PASS_BY_VALUE, (yyvsp[-2].identifierList), (yyvsp[0].simpleTypeNode));
    }
#line 1807 "out/parser.cpp"
    break;

  case 26: /* var_part: %empty  */
#line 420 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty var part" << std::endl;
        #endif
        (yyval.varPartList) = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
    }
#line 1818 "out/parser.cpp"
    break;

  case 27: /* var_part: VAR var_decl_list  */
#line 427 "src/yacc.y"
                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var part" << std::endl;
        #endif
        (yyval.varPartList) = (yyvsp[0].varPartList);
    }
#line 1829 "out/parser.cpp"
    break;

  case 28: /* var_decl_list: var_decl_list var_decl  */
#line 436 "src/yacc.y"
                           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl list 1" << std::endl;
        #endif
        (yyval.varPartList) = (yyvsp[-1].varPartList);
        (yyval.varPartList)->push_back((yyvsp[0].varPartListElement));
    }
#line 1841 "out/parser.cpp"
    break;

  case 29: /* var_decl_list: var_decl  */
#line 444 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl list 2" << std::endl;
        #endif
        (yyval.varPartList) = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
        (yyval.varPartList)->push_back((yyvsp[0].varPartListElement));
    }
#line 1853 "out/parser.cpp"
    break;

  case 30: /* var_decl: name_list COLON type_decl SEMICOLON  */
#line 454 "src/yacc.y"
                                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl 1" << std::endl;
        #endif
        (yyval.varPartListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-3].identifierList), (yyvsp[-1].typeNode));
    }
#line 1864 "out/parser.cpp"
    break;

  case 31: /* var_decl: name_list COLON type_decl  */
#line 461 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl 2" << std::endl;
        #endif
        (yyval.varPartListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-2].identifierList), (yyvsp[0].typeNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1876 "out/parser.cpp"
    break;

  case 32: /* const_part: %empty  */
#line 471 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty const part" << std::endl;
        #endif
        (yyval.constPartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::ConstantNode*>*>();
    }
#line 1887 "out/parser.cpp"
    break;

  case 33: /* const_part: CONST const_expr_list  */
#line 478 "src/yacc.y"
                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const part" << std::endl;
        #endif
        (yyval.constPartList) = (yyvsp[0].constPartList);
    }
#line 1898 "out/parser.cpp"
    break;

  case 34: /* const_expr_list: const_expr_list const_expr  */
#line 487 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr list 1" << std::endl;
        #endif
        (yyval.constPartList) = (yyvsp[-1].constPartList);
        (yyval.constPartList)->push_back((yyvsp[0].constPartListElement));
    }
#line 1910 "out/parser.cpp"
    break;

  case 35: /* const_expr_list: const_expr  */
#line 495 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr list 2" << std::endl;
        #endif
        (yyval.constPartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::ConstantNode*>*>();
        (yyval.constPartList)->push_back((yyvsp[0].constPartListElement));
    }
#line 1922 "out/parser.cpp"
    break;

  case 36: /* const_expr: identifier EQUAL const_value SEMICOLON  */
#line 505 "src/yacc.y"
                                           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr 1" << std::endl;
        #endif
        (yyval.constPartListElement) = new std::pair<ast::IdentifierNode*, ast::ConstantNode*>((yyvsp[-3].identifierNode), (yyvsp[-1].constantNode));
    }
#line 1933 "out/parser.cpp"
    break;

  case 37: /* const_expr: identifier EQUAL const_value  */
#line 512 "src/yacc.y"
                                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr 2" << std::endl;
        #endif
        (yyval.constPartListElement) = new std::pair<ast::IdentifierNode*, ast::ConstantNode*>((yyvsp[-2].identifierNode), (yyvsp[0].constantNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1945 "out/parser.cpp"
    break;

  case 38: /* const_value: INTEGER  */
#line 522 "src/yacc.y"
            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - integer `" << (yyvsp[0].token).numericalValue << "`" << std::endl;
        #endif
        (yyval.constantNode) = new ast::IntegerConstantNode((yyvsp[0].token).numericalValue);
    }
#line 1956 "out/parser.cpp"
    break;

  case 39: /* const_value: MINUS INTEGER  */
#line 529 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - signed integer `" << -(yyvsp[0].token).numericalValue << "`" << std::endl;
        #endif
        (yyval.constantNode) = new ast::IntegerConstantNode(-(yyvsp[0].token).numericalValue);
    }
#line 1967 "out/parser.cpp"
    break;

  case 40: /* const_value: CHAR  */
#line 537 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - char `" << static_cast<char>((yyvsp[0].token).numericalValue) << "`" << std::endl;
        #endif
        (yyval.constantNode) = new ast::CharConstantNode(static_cast<char>((yyvsp[0].token).numericalValue));
    }
#line 1978 "out/parser.cpp"
    break;

  case 41: /* const_value: STRING  */
#line 544 "src/yacc.y"
           {
        std::string str{*(yyvsp[0].token).stringValue};
        str = str.substr(1, str.size() - 2);

        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - string `" << str << "`" << std::endl;
        #endif

        (yyval.constantNode) = new ast::StringConstantNode(std::move(str));
    }
#line 1993 "out/parser.cpp"
    break;

  case 42: /* const_value: TRUE  */
#line 555 "src/yacc.y"
         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - true" << std::endl;
        #endif
        (yyval.constantNode) = new ast::BooleanConstantNode(true);
    }
#line 2004 "out/parser.cpp"
    break;

  case 43: /* const_value: FALSE  */
#line 562 "src/yacc.y"
          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - false" << std::endl;
        #endif
        (yyval.constantNode) = new ast::BooleanConstantNode(false);
    }
#line 2015 "out/parser.cpp"
    break;

  case 44: /* const_value: MAXINT  */
#line 569 "src/yacc.y"
           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - maxint" << std::endl;
        #endif
        (yyval.constantNode) = new ast::IntegerConstantNode(255);
    }
#line 2026 "out/parser.cpp"
    break;

  case 45: /* const_value: MINUS MAXINT  */
#line 576 "src/yacc.y"
                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - signed maxint" << std::endl;
        #endif
        (yyval.constantNode) = new ast::IntegerConstantNode(-255);
    }
#line 2037 "out/parser.cpp"
    break;

  case 46: /* type_part: %empty  */
#line 585 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty type part" << std::endl;
        #endif
        (yyval.typePartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::TypeNode*>*>();
    }
#line 2048 "out/parser.cpp"
    break;

  case 47: /* type_part: TYPE type_decl_list  */
#line 592 "src/yacc.y"
                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type part" << std::endl;
        #endif
        (yyval.typePartList) = (yyvsp[0].typePartList);
    }
#line 2059 "out/parser.cpp"
    break;

  case 48: /* type_decl_list: type_decl_list type_def  */
#line 601 "src/yacc.y"
                            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type decl list 1" << std::endl;
        #endif
        (yyval.typePartList) = (yyvsp[-1].typePartList);
        (yyval.typePartList)->push_back((yyvsp[0].typePartListElement));
    }
#line 2071 "out/parser.cpp"
    break;

  case 49: /* type_decl_list: type_def  */
#line 609 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type decl list 2" << std::endl;
        #endif
        (yyval.typePartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::TypeNode*>*>();
        (yyval.typePartList)->push_back((yyvsp[0].typePartListElement));
    }
#line 2083 "out/parser.cpp"
    break;

  case 50: /* type_def: identifier EQUAL type_decl SEMICOLON  */
#line 619 "src/yacc.y"
                                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type def 1" << std::endl;
        #endif
        (yyval.typePartListElement) = new std::pair<ast::IdentifierNode*, ast::TypeNode*>((yyvsp[-3].identifierNode), (yyvsp[-1].typeNode));
    }
#line 2094 "out/parser.cpp"
    break;

  case 51: /* type_def: identifier EQUAL type_decl  */
#line 626 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type def 2" << std::endl;
        #endif
        (yyval.typePartListElement) = new std::pair<ast::IdentifierNode*, ast::TypeNode*>((yyvsp[-2].identifierNode), (yyvsp[0].typeNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2106 "out/parser.cpp"
    break;

  case 52: /* type_decl: simple_type  */
#line 636 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type" << std::endl;
        #endif
        (yyval.typeNode) = (yyvsp[0].simpleTypeNode);
    }
#line 2117 "out/parser.cpp"
    break;

  case 53: /* type_decl: array_type_decl  */
#line 643 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse array type" << std::endl;
        #endif
        (yyval.typeNode) = (yyvsp[0].arrayTypeNode);
    }
#line 2128 "out/parser.cpp"
    break;

  case 54: /* type_decl: record_type_decl  */
#line 650 "src/yacc.y"
                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse record type" << std::endl;
        #endif
        (yyval.typeNode) = (yyvsp[0].recordTypeNode);
    }
#line 2139 "out/parser.cpp"
    break;

  case 55: /* record_type_decl: RECORD field_decl_list END  */
#line 659 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse record type" << std::endl;
        #endif
        (yyval.recordTypeNode) = new ast::RecordTypeNode((yyvsp[-1].fieldDeclList));
    }
#line 2150 "out/parser.cpp"
    break;

  case 56: /* field_decl_list: field_decl_list field_decl  */
#line 668 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl list 1" << std::endl;
        #endif
        (yyval.fieldDeclList) = (yyvsp[-1].fieldDeclList);
        (yyval.fieldDeclList)->push_back((yyvsp[0].fieldDeclListElement));
    }
#line 2162 "out/parser.cpp"
    break;

  case 57: /* field_decl_list: field_decl  */
#line 676 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl list 2" << std::endl;
        #endif
        (yyval.fieldDeclList) = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
        (yyval.fieldDeclList)->push_back((yyvsp[0].fieldDeclListElement));
    }
#line 2174 "out/parser.cpp"
    break;

  case 58: /* field_decl: name_list COLON type_decl SEMICOLON  */
#line 686 "src/yacc.y"
                                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl 1" << std::endl;
        #endif
        (yyval.fieldDeclListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-3].identifierList), (yyvsp[-1].typeNode));
    }
#line 2185 "out/parser.cpp"
    break;

  case 59: /* field_decl: name_list COLON type_decl  */
#line 693 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl 2" << std::endl;
        #endif
        (yyval.fieldDeclListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-2].identifierList), (yyvsp[0].typeNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2197 "out/parser.cpp"
    break;

  case 60: /* array_type_decl: ARRAY LB simple_type RB OF type_decl  */
#line 703 "src/yacc.y"
                                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse array type" << std::endl;
        #endif
        (yyval.arrayTypeNode) = new ast::ArrayTypeNode((yyvsp[-3].simpleTypeNode), (yyvsp[0].typeNode));
    }
#line 2208 "out/parser.cpp"
    break;

  case 61: /* simple_type: identifier  */
#line 712 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - identifier" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::RenameTypeNode((yyvsp[0].identifierNode));
    }
#line 2219 "out/parser.cpp"
    break;

  case 62: /* simple_type: LP name_list RP  */
#line 719 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - parentheses" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::EnumerationTypeNode((yyvsp[-1].identifierList));
    }
#line 2230 "out/parser.cpp"
    break;

  case 63: /* simple_type: const_value DOUBLEDOT const_value  */
#line 726 "src/yacc.y"
                                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - range 1" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::ConstRangeTypeNode((yyvsp[-2].constantNode), (yyvsp[0].constantNode));
    }
#line 2241 "out/parser.cpp"
    break;

  case 64: /* simple_type: identifier DOUBLEDOT identifier  */
#line 733 "src/yacc.y"
                                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - range 4" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::VarRangeTypeNode((yyvsp[-2].identifierNode), (yyvsp[0].identifierNode));
    }
#line 2252 "out/parser.cpp"
    break;

  case 65: /* simple_type: INT_TYPE  */
#line 740 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - int" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::INTEGER);
    }
#line 2263 "out/parser.cpp"
    break;

  case 66: /* simple_type: UNSIGNED_TYPE  */
#line 747 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - unsigned" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::UNSIGNED);
    }
#line 2274 "out/parser.cpp"
    break;

  case 67: /* simple_type: BOOL_TYPE  */
#line 754 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - bool" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::BOOLEAN);
    }
#line 2285 "out/parser.cpp"
    break;

  case 68: /* simple_type: CHAR_TYPE  */
#line 761 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - char" << std::endl;
        #endif
        (yyval.simpleTypeNode) = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::CHAR);
    }
#line 2296 "out/parser.cpp"
    break;

  case 69: /* name_list: name_list COMMA identifier  */
#line 770 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse name list 1" << std::endl;
        #endif
        (yyval.identifierList) = (yyvsp[-2].identifierList);
        (yyval.identifierList)->push_back((yyvsp[0].identifierNode));
    }
#line 2308 "out/parser.cpp"
    break;

  case 70: /* name_list: identifier  */
#line 778 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse name list 2" << std::endl;
        #endif
        (yyval.identifierList) = new std::vector<ast::IdentifierNode*>();
        (yyval.identifierList)->push_back((yyvsp[0].identifierNode));
    }
#line 2320 "out/parser.cpp"
    break;

  case 71: /* identifier: IDENT_NAME  */
#line 788 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse identifier `" << (*(yyvsp[0].token).stringValue) << "`" << std::endl;
        #endif
        std::string name{*(yyvsp[0].token).stringValue};
        (yyval.identifierNode) = new ast::IdentifierNode(std::move(name));
    }
#line 2332 "out/parser.cpp"
    break;

  case 72: /* routine_body: compound_stmt  */
#line 798 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine body" << std::endl;
        #endif
        (yyval.routineBodyNode) = new ast::RoutineBodyNode((yyvsp[0].compoundStatementNode));
    }
#line 2343 "out/parser.cpp"
    break;

  case 73: /* compound_stmt: BBEGIN stmt_list END  */
#line 807 "src/yacc.y"
                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse compound statement 1" << std::endl;
        #endif
        (yyval.compoundStatementNode) = new ast::CompoundStatementNode((yyvsp[-1].statementNodeList));
    }
#line 2354 "out/parser.cpp"
    break;

  case 74: /* compound_stmt: BBEGIN stmt_list  */
#line 814 "src/yacc.y"
                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse compound statement 2" << std::endl;
        #endif
        (yyval.compoundStatementNode) = new ast::CompoundStatementNode((yyvsp[0].statementNodeList));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of end");
    }
#line 2366 "out/parser.cpp"
    break;

  case 75: /* stmt_list: %empty  */
#line 824 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty statement list" << std::endl;
        #endif
        (yyval.statementNodeList) = new std::vector<ast::StatementNode*>();
    }
#line 2377 "out/parser.cpp"
    break;

  case 76: /* stmt_list: stmt_list stmt SEMICOLON  */
#line 831 "src/yacc.y"
                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement list 1" << std::endl;
        #endif
        (yyval.statementNodeList) = (yyvsp[-2].statementNodeList);
        (yyval.statementNodeList)->push_back((yyvsp[-1].statementNode));
    }
#line 2389 "out/parser.cpp"
    break;

  case 77: /* stmt_list: stmt_list stmt  */
#line 839 "src/yacc.y"
                   {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement list 2" << std::endl;
        #endif
        (yyval.statementNodeList) = (yyvsp[-1].statementNodeList);
        (yyval.statementNodeList)->push_back((yyvsp[0].statementNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2402 "out/parser.cpp"
    break;

  case 78: /* stmt: INTEGER COLON no_label_stmt  */
#line 850 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement with label " << (yyvsp[-2].token).numericalValue << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].statementNode);
        (yyval.statementNode)->setLabel((yyvsp[-2].token).numericalValue);
    }
#line 2414 "out/parser.cpp"
    break;

  case 79: /* stmt: no_label_stmt  */
#line 858 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement without label" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].statementNode);
    }
#line 2425 "out/parser.cpp"
    break;

  case 80: /* no_label_stmt: assign_stmt  */
#line 867 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - assign" << std::endl;
        #endif
        (yyval.statementNode)=(yyvsp[0].assignNode);
    }
#line 2436 "out/parser.cpp"
    break;

  case 81: /* no_label_stmt: compound_stmt  */
#line 874 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - compound" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].compoundStatementNode);
    }
#line 2447 "out/parser.cpp"
    break;

  case 82: /* no_label_stmt: goto_stmt  */
#line 881 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - goto" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].gotoNode);
    }
#line 2458 "out/parser.cpp"
    break;

  case 83: /* no_label_stmt: if_stmt  */
#line 888 "src/yacc.y"
            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - if" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].ifNode);
    }
#line 2469 "out/parser.cpp"
    break;

  case 84: /* no_label_stmt: repeat_stmt  */
#line 895 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - repeat" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].repeatNode);
    }
#line 2480 "out/parser.cpp"
    break;

  case 85: /* no_label_stmt: while_stmt  */
#line 902 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - while" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].whileNode);
    }
#line 2491 "out/parser.cpp"
    break;

  case 86: /* no_label_stmt: case_stmt  */
#line 909 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - case" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].caseNode);
    }
#line 2502 "out/parser.cpp"
    break;

  case 87: /* no_label_stmt: for_stmt  */
#line 916 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - for" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].forNode);
    }
#line 2513 "out/parser.cpp"
    break;

  case 88: /* no_label_stmt: proc_stmt  */
#line 923 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - proc" << std::endl;
        #endif
        (yyval.statementNode) = (yyvsp[0].callNode);
    }
#line 2524 "out/parser.cpp"
    break;

  case 89: /* no_label_stmt: BREAK  */
#line 930 "src/yacc.y"
          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - break" << std::endl;
        #endif
        (yyval.statementNode) = new ast::BreakNode();
    }
#line 2535 "out/parser.cpp"
    break;

  case 90: /* no_label_stmt: CONTINUE  */
#line 937 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - continue" << std::endl;
        #endif
        (yyval.statementNode) = new ast::ContinueNode();
    }
#line 2546 "out/parser.cpp"
    break;

  case 91: /* assign_stmt: identifier ASSIGN expression  */
#line 946 "src/yacc.y"
                                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple assign statement" << std::endl;
        #endif
        (yyval.assignNode) = new ast::AssignToVariableNode((yyvsp[-2].identifierNode), (yyvsp[0].expressionNode));
    }
#line 2557 "out/parser.cpp"
    break;

  case 92: /* assign_stmt: identifier LB expression RB ASSIGN expression  */
#line 953 "src/yacc.y"
                                                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse array assign statement" << std::endl;
        #endif
        (yyval.assignNode) = new ast::AssignToArrayNode((yyvsp[-5].identifierNode), (yyvsp[-3].expressionNode), (yyvsp[0].expressionNode));
    }
#line 2568 "out/parser.cpp"
    break;

  case 93: /* assign_stmt: identifier DOT identifier ASSIGN expression  */
#line 960 "src/yacc.y"
                                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse record assign statement" << std::endl;
        #endif
        (yyval.assignNode) = new ast::AssignToRecordFieldNode((yyvsp[-4].identifierNode), (yyvsp[-2].identifierNode), (yyvsp[0].expressionNode));
    }
#line 2579 "out/parser.cpp"
    break;

  case 94: /* goto_stmt: GOTO INTEGER  */
#line 969 "src/yacc.y"
                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse goto statement to " << (yyvsp[0].token).numericalValue << std::endl;
        #endif
        (yyval.gotoNode) = new ast::GotoNode((yyvsp[0].token).numericalValue);
    }
#line 2590 "out/parser.cpp"
    break;

  case 95: /* if_stmt: IF expression THEN stmt else_clause  */
#line 978 "src/yacc.y"
                                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse if statement 1" << std::endl;
        #endif
        (yyval.ifNode) = new ast::IfNode((yyvsp[-3].expressionNode), (yyvsp[-1].statementNode), (yyvsp[0].ifNode));
    }
#line 2601 "out/parser.cpp"
    break;

  case 96: /* if_stmt: IF expression stmt else_clause  */
#line 985 "src/yacc.y"
                                   {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse if statement 2" << std::endl;
        #endif
        (yyval.ifNode) = new ast::IfNode((yyvsp[-2].expressionNode), (yyvsp[-1].statementNode), (yyvsp[0].ifNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of then");
    }
#line 2613 "out/parser.cpp"
    break;

  case 97: /* else_clause: %empty  */
#line 995 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty else clause" << std::endl;
        #endif
        (yyval.ifNode) = new ast::IfNode(nullptr, nullptr);
    }
#line 2624 "out/parser.cpp"
    break;

  case 98: /* else_clause: ELSE stmt  */
#line 1002 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse else clause" << std::endl;
        #endif
        (yyval.ifNode) = new ast::IfNode(nullptr, nullptr, (yyvsp[0].statementNode));
    }
#line 2635 "out/parser.cpp"
    break;

  case 99: /* repeat_stmt: REPEAT stmt_list UNTIL expression  */
#line 1011 "src/yacc.y"
                                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse repeat statement" << std::endl;
        #endif
        (yyval.repeatNode) = new ast::RepeatNode((yyvsp[0].expressionNode), (yyvsp[-2].statementNodeList));
    }
#line 2646 "out/parser.cpp"
    break;

  case 100: /* repeat_stmt: %empty  */
#line 1018 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty repeat statement" << std::endl;
        #endif
    }
#line 2656 "out/parser.cpp"
    break;

  case 101: /* while_stmt: WHILE expression DO stmt  */
#line 1026 "src/yacc.y"
                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse while statement" << std::endl;
        #endif
        (yyval.whileNode) = new ast::WhileNode((yyvsp[-2].expressionNode), (yyvsp[0].statementNode));
    }
#line 2667 "out/parser.cpp"
    break;

  case 102: /* case_stmt: CASE expression OF case_expr_list END  */
#line 1035 "src/yacc.y"
                                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case statement" << std::endl;
        #endif
        (yyval.caseNode) = new ast::CaseNode((yyvsp[-3].expressionNode), (yyvsp[-1].caseExprList));
    }
#line 2678 "out/parser.cpp"
    break;

  case 103: /* case_expr_list: case_expr_list case_expr  */
#line 1044 "src/yacc.y"
                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr list 1" << std::endl;
        #endif
        (yyval.caseExprList) = (yyvsp[-1].caseExprList);
        (yyval.caseExprList)->push_back((yyvsp[0].caseExpr));
    }
#line 2690 "out/parser.cpp"
    break;

  case 104: /* case_expr_list: case_expr  */
#line 1052 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr list 2" << std::endl;
        #endif
        (yyval.caseExprList) = new std::vector<std::pair<ast::AstNode*, ast::StatementNode*>*>();
        (yyval.caseExprList)->push_back((yyvsp[0].caseExpr));
    }
#line 2702 "out/parser.cpp"
    break;

  case 105: /* case_expr: const_value COLON stmt SEMICOLON  */
#line 1062 "src/yacc.y"
                                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr 1" << std::endl;
        #endif
        (yyval.caseExpr) = new std::pair<ast::AstNode*, ast::StatementNode*>((yyvsp[-3].constantNode), (yyvsp[-1].statementNode));
    }
#line 2713 "out/parser.cpp"
    break;

  case 106: /* case_expr: identifier COLON stmt SEMICOLON  */
#line 1069 "src/yacc.y"
                                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr 2" << std::endl;
        #endif
        (yyval.caseExpr) = new std::pair<ast::AstNode*, ast::StatementNode*>((yyvsp[-3].identifierNode), (yyvsp[-1].statementNode));
    }
#line 2724 "out/parser.cpp"
    break;

  case 107: /* case_expr: OTHERWISE stmt SEMICOLON  */
#line 1076 "src/yacc.y"
                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr 3" << std::endl;
        #endif
        (yyval.caseExpr) = new std::pair<ast::AstNode*, ast::StatementNode*>(nullptr, (yyvsp[-1].statementNode));
    }
#line 2735 "out/parser.cpp"
    break;

  case 108: /* for_stmt: FOR identifier ASSIGN expression TO expression DO stmt  */
#line 1085 "src/yacc.y"
                                                           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse for statement 1" << std::endl;
        #endif
        (yyval.forNode) = new ast::ForNode((yyvsp[-6].identifierNode), (yyvsp[-4].expressionNode), (yyvsp[-2].expressionNode), (yyvsp[0].statementNode), ast::ForNode::Direction::INCREMENT);
    }
#line 2746 "out/parser.cpp"
    break;

  case 109: /* for_stmt: FOR identifier ASSIGN expression DOWNTO expression DO stmt  */
#line 1092 "src/yacc.y"
                                                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse for statement 2" << std::endl;
        #endif
        (yyval.forNode) = new ast::ForNode((yyvsp[-6].identifierNode), (yyvsp[-4].expressionNode), (yyvsp[-2].expressionNode), (yyvsp[0].statementNode), ast::ForNode::Direction::DECREMENT);
    }
#line 2757 "out/parser.cpp"
    break;

  case 110: /* proc_stmt: identifier  */
#line 1101 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse procedure statement" << std::endl;
        #endif
        (yyval.callNode) = new ast::UserDefineCallNode((yyvsp[0].identifierNode), nullptr);
    }
#line 2768 "out/parser.cpp"
    break;

  case 111: /* proc_stmt: identifier LP args_list RP  */
#line 1108 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse procedure statement with args" << std::endl;
        #endif
        (yyval.callNode) = new ast::UserDefineCallNode((yyvsp[-3].identifierNode), (yyvsp[-1].argsList));
    }
#line 2779 "out/parser.cpp"
    break;

  case 112: /* proc_stmt: READ LP factor RP  */
#line 1115 "src/yacc.y"
                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse read statement" << std::endl;
        #endif
        ast::ArgumentsListNode* args = new ast::ArgumentsListNode();
        args->addArgument((yyvsp[-1].expressionNode));
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::READ, args);
    }
#line 2792 "out/parser.cpp"
    break;

  case 113: /* proc_stmt: READLN  */
#line 1125 "src/yacc.y"
           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse readln statement" << std::endl;
        #endif
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::READLN, nullptr);
    }
#line 2803 "out/parser.cpp"
    break;

  case 114: /* proc_stmt: WRITE LP args_list RP  */
#line 1132 "src/yacc.y"
                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse write statement" << std::endl;
        #endif
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITE, (yyvsp[-1].argsList));
    }
#line 2814 "out/parser.cpp"
    break;

  case 115: /* proc_stmt: WRITELN  */
#line 1139 "src/yacc.y"
            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse writeln statement" << std::endl;
        #endif
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITELN, nullptr);
    }
#line 2825 "out/parser.cpp"
    break;

  case 116: /* proc_stmt: WRITELN LP args_list RP  */
#line 1146 "src/yacc.y"
                            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse writeln statement with args" << std::endl;
        #endif
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITELN, (yyvsp[-1].argsList));
    }
#line 2836 "out/parser.cpp"
    break;

  case 117: /* proc_stmt: MEMORYREAD LP args_list RP  */
#line 1153 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse memory read statement" << std::endl;
        #endif
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::MEMORY_READ, (yyvsp[-1].argsList));
    }
#line 2847 "out/parser.cpp"
    break;

  case 118: /* proc_stmt: MEMORYWRITE LP args_list RP  */
#line 1160 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse memory write statement" << std::endl;
        #endif
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::MEMORY_WRITE, (yyvsp[-1].argsList));
    }
#line 2858 "out/parser.cpp"
    break;

  case 119: /* proc_stmt: STACKREAD LP args_list RP  */
#line 1167 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse stack read statement" << std::endl;
        #endif
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::STACK_READ, (yyvsp[-1].argsList));
    }
#line 2869 "out/parser.cpp"
    break;

  case 120: /* proc_stmt: STACKWRITE LP args_list RP  */
#line 1174 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse stack write statement" << std::endl;
        #endif
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::STACK_WRITE, (yyvsp[-1].argsList));
    }
#line 2880 "out/parser.cpp"
    break;

  case 121: /* args_list: args_list COMMA expression  */
#line 1183 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse args list 1" << std::endl;
        #endif
        (yyval.argsList) = (yyvsp[-2].argsList);
        (yyval.argsList)->addArgument((yyvsp[0].expressionNode));
    }
#line 2892 "out/parser.cpp"
    break;

  case 122: /* args_list: expression  */
#line 1191 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse args list 2" << std::endl;
        #endif
        (yyval.argsList) = new ast::ArgumentsListNode();
        (yyval.argsList)->addArgument((yyvsp[0].expressionNode));
    }
#line 2904 "out/parser.cpp"
    break;

  case 123: /* expression: expression GE expr  */
#line 1201 "src/yacc.y"
                       {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with greater or equal" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::GREATER_EQUAL);
    }
#line 2915 "out/parser.cpp"
    break;

  case 124: /* expression: expression GT expr  */
#line 1208 "src/yacc.y"
                       {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with greater" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::GREATER);
    }
#line 2926 "out/parser.cpp"
    break;

  case 125: /* expression: expression LE expr  */
#line 1215 "src/yacc.y"
                       {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with less or equal" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::LESS_EQUAL);
    }
#line 2937 "out/parser.cpp"
    break;

  case 126: /* expression: expression LT expr  */
#line 1222 "src/yacc.y"
                       {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with less" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::LESS);
    }
#line 2948 "out/parser.cpp"
    break;

  case 127: /* expression: expression EQUAL expr  */
#line 1229 "src/yacc.y"
                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with equal" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::EQUAL);
    }
#line 2959 "out/parser.cpp"
    break;

  case 128: /* expression: expression UNEQUAL expr  */
#line 1236 "src/yacc.y"
                            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with not equal" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::NOT_EQUAL);
    }
#line 2970 "out/parser.cpp"
    break;

  case 129: /* expression: expr  */
#line 1243 "src/yacc.y"
         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple expression" << std::endl;
        #endif
        (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 2981 "out/parser.cpp"
    break;

  case 130: /* expr: expr PLUS term  */
#line 1252 "src/yacc.y"
                   {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with addition" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::ADDITION);
    }
#line 2992 "out/parser.cpp"
    break;

  case 131: /* expr: expr MINUS term  */
#line 1259 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with subtraction" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::SUBTRACTION);
    }
#line 3003 "out/parser.cpp"
    break;

  case 132: /* expr: expr OR term  */
#line 1266 "src/yacc.y"
                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with or" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::OR);
    }
#line 3014 "out/parser.cpp"
    break;

  case 133: /* expr: term  */
#line 1273 "src/yacc.y"
         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple term" << std::endl;
        #endif
        (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 3025 "out/parser.cpp"
    break;

  case 134: /* term: term MUL factor  */
#line 1282 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with multiplication" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::MULTIPLICATION);
    }
#line 3036 "out/parser.cpp"
    break;

  case 135: /* term: term DIV factor  */
#line 1289 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with division" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::DIVISION);
    }
#line 3047 "out/parser.cpp"
    break;

  case 136: /* term: term MOD factor  */
#line 1296 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with modulus" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::MODULUS);
    }
#line 3058 "out/parser.cpp"
    break;

  case 137: /* term: term AND factor  */
#line 1303 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with and" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::AND);
    }
#line 3069 "out/parser.cpp"
    break;

  case 138: /* term: factor  */
#line 1310 "src/yacc.y"
           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple factor" << std::endl;
        #endif
        (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 3080 "out/parser.cpp"
    break;

  case 139: /* factor: identifier  */
#line 1319 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - identifier" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[0].identifierNode), ast::SpecialExpressionNode::FunctionName::VARIABLE);
    }
#line 3091 "out/parser.cpp"
    break;

  case 140: /* factor: identifier LP args_list RP  */
#line 1326 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - function call" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-3].identifierNode), (yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::CALL);
    }
#line 3102 "out/parser.cpp"
    break;

  case 141: /* factor: const_value  */
#line 1333 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - const value" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[0].constantNode), ast::SpecialExpressionNode::FunctionName::CONST);
    }
#line 3113 "out/parser.cpp"
    break;

  case 142: /* factor: LP expression RP  */
#line 1340 "src/yacc.y"
                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - parentheses" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].expressionNode), ast::SpecialExpressionNode::FunctionName::PARENTHESIS);
    }
#line 3124 "out/parser.cpp"
    break;

  case 143: /* factor: NOT factor  */
#line 1347 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - not" << std::endl;
        #endif
       (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[0].expressionNode), ast::ExpressionNode::Operation::NOT);
    }
#line 3135 "out/parser.cpp"
    break;

  case 144: /* factor: MINUS factor  */
#line 1354 "src/yacc.y"
                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - negation" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[0].expressionNode), ast::ExpressionNode::Operation::NEGATION);
    }
#line 3146 "out/parser.cpp"
    break;

  case 145: /* factor: identifier LB expression RB  */
#line 1361 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - array access" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-3].identifierNode), (yyvsp[-1].expressionNode), ast::SpecialExpressionNode::FunctionName::ARRAY_ACCESS);
    }
#line 3157 "out/parser.cpp"
    break;

  case 146: /* factor: identifier DOT identifier  */
#line 1368 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - record access" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-2].identifierNode), (yyvsp[0].identifierNode), ast::SpecialExpressionNode::FunctionName::RECORD_ACCESS);
    }
#line 3168 "out/parser.cpp"
    break;

  case 147: /* factor: ABS LP args_list RP  */
#line 1375 "src/yacc.y"
                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - abs" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::ABS);
    }
#line 3179 "out/parser.cpp"
    break;

  case 148: /* factor: CHR LP args_list RP  */
#line 1382 "src/yacc.y"
                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - chr" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::CHR);
    }
#line 3190 "out/parser.cpp"
    break;

  case 149: /* factor: ODD LP args_list RP  */
#line 1389 "src/yacc.y"
                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - odd" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::ODD);
    }
#line 3201 "out/parser.cpp"
    break;

  case 150: /* factor: ORD LP args_list RP  */
#line 1396 "src/yacc.y"
                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - ord" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::ORD);
    }
#line 3212 "out/parser.cpp"
    break;

  case 151: /* factor: PRED LP args_list RP  */
#line 1403 "src/yacc.y"
                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - pred" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::PRED);
    }
#line 3223 "out/parser.cpp"
    break;

  case 152: /* factor: SUCC LP args_list RP  */
#line 1410 "src/yacc.y"
                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - succ" << std::endl;
        #endif
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::SUCC);
    }
#line 3234 "out/parser.cpp"
    break;


#line 3238 "out/parser.cpp"

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

#line 1417 "src/yacc.y"


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
