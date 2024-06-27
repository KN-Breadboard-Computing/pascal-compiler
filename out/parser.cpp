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

ast::ProgramNode* resultAst;
std::vector<std::string> parsingErrors;

static void yyerror(const char *msg);
static int yyparse(void);
int yylex(void);

extern FILE* yyin;
extern uint64_t linesCounter;

#line 90 "out/parser.cpp"

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
  YYSYMBOL_WRITE = 20,                     /* WRITE  */
  YYSYMBOL_WRITELN = 21,                   /* WRITELN  */
  YYSYMBOL_ABS = 22,                       /* ABS  */
  YYSYMBOL_CHR = 23,                       /* CHR  */
  YYSYMBOL_ODD = 24,                       /* ODD  */
  YYSYMBOL_ORD = 25,                       /* ORD  */
  YYSYMBOL_PRED = 26,                      /* PRED  */
  YYSYMBOL_SUCC = 27,                      /* SUCC  */
  YYSYMBOL_IF = 28,                        /* IF  */
  YYSYMBOL_THEN = 29,                      /* THEN  */
  YYSYMBOL_ELSE = 30,                      /* ELSE  */
  YYSYMBOL_REPEAT = 31,                    /* REPEAT  */
  YYSYMBOL_UNTIL = 32,                     /* UNTIL  */
  YYSYMBOL_WHILE = 33,                     /* WHILE  */
  YYSYMBOL_DO = 34,                        /* DO  */
  YYSYMBOL_CASE = 35,                      /* CASE  */
  YYSYMBOL_TO = 36,                        /* TO  */
  YYSYMBOL_DOWNTO = 37,                    /* DOWNTO  */
  YYSYMBOL_FOR = 38,                       /* FOR  */
  YYSYMBOL_EQUAL = 39,                     /* EQUAL  */
  YYSYMBOL_UNEQUAL = 40,                   /* UNEQUAL  */
  YYSYMBOL_GE = 41,                        /* GE  */
  YYSYMBOL_GT = 42,                        /* GT  */
  YYSYMBOL_LE = 43,                        /* LE  */
  YYSYMBOL_LT = 44,                        /* LT  */
  YYSYMBOL_ASSIGN = 45,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 46,                      /* PLUS  */
  YYSYMBOL_MINUS = 47,                     /* MINUS  */
  YYSYMBOL_MUL = 48,                       /* MUL  */
  YYSYMBOL_DIV = 49,                       /* DIV  */
  YYSYMBOL_OR = 50,                        /* OR  */
  YYSYMBOL_AND = 51,                       /* AND  */
  YYSYMBOL_NOT = 52,                       /* NOT  */
  YYSYMBOL_MOD = 53,                       /* MOD  */
  YYSYMBOL_LB = 54,                        /* LB  */
  YYSYMBOL_RB = 55,                        /* RB  */
  YYSYMBOL_LP = 56,                        /* LP  */
  YYSYMBOL_RP = 57,                        /* RP  */
  YYSYMBOL_SEMICOLON = 58,                 /* SEMICOLON  */
  YYSYMBOL_DOT = 59,                       /* DOT  */
  YYSYMBOL_DOUBLEDOT = 60,                 /* DOUBLEDOT  */
  YYSYMBOL_COMMA = 61,                     /* COMMA  */
  YYSYMBOL_COLON = 62,                     /* COLON  */
  YYSYMBOL_INT_TYPE = 63,                  /* INT_TYPE  */
  YYSYMBOL_BOOL_TYPE = 64,                 /* BOOL_TYPE  */
  YYSYMBOL_CHAR_TYPE = 65,                 /* CHAR_TYPE  */
  YYSYMBOL_STRING_TYPE = 66,               /* STRING_TYPE  */
  YYSYMBOL_ARRAY = 67,                     /* ARRAY  */
  YYSYMBOL_OF = 68,                        /* OF  */
  YYSYMBOL_RECORD = 69,                    /* RECORD  */
  YYSYMBOL_GOTO = 70,                      /* GOTO  */
  YYSYMBOL_ERROR = 71,                     /* ERROR  */
  YYSYMBOL_YYACCEPT = 72,                  /* $accept  */
  YYSYMBOL_program = 73,                   /* program  */
  YYSYMBOL_routine = 74,                   /* routine  */
  YYSYMBOL_routine_head = 75,              /* routine_head  */
  YYSYMBOL_routine_part = 76,              /* routine_part  */
  YYSYMBOL_fun_decl = 77,                  /* fun_decl  */
  YYSYMBOL_fun_head = 78,                  /* fun_head  */
  YYSYMBOL_proc_decl = 79,                 /* proc_decl  */
  YYSYMBOL_proc_head = 80,                 /* proc_head  */
  YYSYMBOL_params = 81,                    /* params  */
  YYSYMBOL_params_decl = 82,               /* params_decl  */
  YYSYMBOL_params_type = 83,               /* params_type  */
  YYSYMBOL_var_part = 84,                  /* var_part  */
  YYSYMBOL_var_decl_list = 85,             /* var_decl_list  */
  YYSYMBOL_var_decl = 86,                  /* var_decl  */
  YYSYMBOL_const_part = 87,                /* const_part  */
  YYSYMBOL_const_expr_list = 88,           /* const_expr_list  */
  YYSYMBOL_const_expr = 89,                /* const_expr  */
  YYSYMBOL_const_value = 90,               /* const_value  */
  YYSYMBOL_type_part = 91,                 /* type_part  */
  YYSYMBOL_type_decl_list = 92,            /* type_decl_list  */
  YYSYMBOL_type_def = 93,                  /* type_def  */
  YYSYMBOL_type_decl = 94,                 /* type_decl  */
  YYSYMBOL_record_type_decl = 95,          /* record_type_decl  */
  YYSYMBOL_field_decl_list = 96,           /* field_decl_list  */
  YYSYMBOL_field_decl = 97,                /* field_decl  */
  YYSYMBOL_array_type_decl = 98,           /* array_type_decl  */
  YYSYMBOL_simple_type = 99,               /* simple_type  */
  YYSYMBOL_name_list = 100,                /* name_list  */
  YYSYMBOL_identifier = 101,               /* identifier  */
  YYSYMBOL_routine_body = 102,             /* routine_body  */
  YYSYMBOL_compound_stmt = 103,            /* compound_stmt  */
  YYSYMBOL_stmt_list = 104,                /* stmt_list  */
  YYSYMBOL_stmt = 105,                     /* stmt  */
  YYSYMBOL_no_label_stmt = 106,            /* no_label_stmt  */
  YYSYMBOL_assign_stmt = 107,              /* assign_stmt  */
  YYSYMBOL_goto_stmt = 108,                /* goto_stmt  */
  YYSYMBOL_if_stmt = 109,                  /* if_stmt  */
  YYSYMBOL_else_clause = 110,              /* else_clause  */
  YYSYMBOL_repeat_stmt = 111,              /* repeat_stmt  */
  YYSYMBOL_while_stmt = 112,               /* while_stmt  */
  YYSYMBOL_case_stmt = 113,                /* case_stmt  */
  YYSYMBOL_case_expr_list = 114,           /* case_expr_list  */
  YYSYMBOL_case_expr = 115,                /* case_expr  */
  YYSYMBOL_for_stmt = 116,                 /* for_stmt  */
  YYSYMBOL_proc_stmt = 117,                /* proc_stmt  */
  YYSYMBOL_args_list = 118,                /* args_list  */
  YYSYMBOL_expression = 119,               /* expression  */
  YYSYMBOL_expr = 120,                     /* expr  */
  YYSYMBOL_term = 121,                     /* term  */
  YYSYMBOL_factor = 122                    /* factor  */
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
#define YYLAST   487

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  143
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  286

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   326


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
      65,    66,    67,    68,    69,    70,    71
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   169,   169,   176,   184,   192,   202,   208,   214,   218,
     223,   228,   233,   240,   246,   253,   260,   269,   276,   284,
     291,   296,   302,   307,   314,   318,   324,   328,   334,   339,
     346,   350,   357,   361,   367,   372,   379,   383,   390,   393,
     398,   403,   407,   411,   417,   421,   427,   432,   439,   443,
     450,   454,   458,   464,   470,   475,   482,   486,   493,   499,
     503,   507,   511,   515,   519,   523,   527,   531,   537,   542,
     549,   556,   562,   566,   573,   577,   582,   590,   595,   601,
     605,   609,   613,   617,   621,   625,   629,   633,   639,   643,
     647,   653,   659,   663,   670,   674,   680,   684,   689,   695,
     701,   706,   713,   717,   723,   727,   733,   737,   741,   747,
     751,   755,   761,   766,   773,   777,   781,   785,   789,   793,
     797,   803,   807,   811,   815,   821,   825,   829,   833,   837,
     843,   847,   851,   855,   859,   863,   867,   871,   875,   879,
     883,   887,   891,   895
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
  "READ", "WRITE", "WRITELN", "ABS", "CHR", "ODD", "ORD", "PRED", "SUCC",
  "IF", "THEN", "ELSE", "REPEAT", "UNTIL", "WHILE", "DO", "CASE", "TO",
  "DOWNTO", "FOR", "EQUAL", "UNEQUAL", "GE", "GT", "LE", "LT", "ASSIGN",
  "PLUS", "MINUS", "MUL", "DIV", "OR", "AND", "NOT", "MOD", "LB", "RB",
  "LP", "RP", "SEMICOLON", "DOT", "DOUBLEDOT", "COMMA", "COLON",
  "INT_TYPE", "BOOL_TYPE", "CHAR_TYPE", "STRING_TYPE", "ARRAY", "OF",
  "RECORD", "GOTO", "ERROR", "$accept", "program", "routine",
  "routine_head", "routine_part", "fun_decl", "fun_head", "proc_decl",
  "proc_head", "params", "params_decl", "params_type", "var_part",
  "var_decl_list", "var_decl", "const_part", "const_expr_list",
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

#define YYPACT_NINF (-166)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      12,     6,    24,    -4,  -166,    22,    32,     7,   100,    94,
    -166,    22,  -166,    72,    58,  -166,  -166,  -166,  -166,    22,
     117,  -166,   463,  -166,   288,    22,  -166,    91,    22,    47,
    -166,  -166,  -166,  -166,  -166,  -166,    82,  -166,    88,   112,
     130,   134,   389,  -166,   389,   389,    22,   148,    -6,  -166,
     115,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,
    -166,   379,    22,  -166,    11,  -166,   192,   195,    47,  -166,
       5,  -166,   152,  -166,   350,   389,   389,   389,   155,   157,
     158,   160,   164,   165,   389,   389,   389,  -166,   -22,   252,
      18,    67,  -166,   316,    36,    51,   180,  -166,   389,   389,
     389,    22,  -166,   463,    22,  -166,  -166,  -166,   168,    22,
     166,   170,  -166,  -166,  -166,   169,  -166,    22,   379,   174,
     174,  -166,  -166,    32,   176,    32,  -166,   175,   -39,   271,
      -2,   389,   389,   389,   389,   389,   389,  -166,  -166,    92,
     389,   389,    22,   322,   389,   389,   389,   389,   389,   389,
     205,   389,   389,   389,   389,   389,   389,   389,   389,   322,
     456,   389,   271,     3,    41,   191,   178,    65,   177,   132,
    -166,   122,   463,  -166,    22,  -166,   181,     1,   185,  -166,
     190,  -166,   193,  -166,  -166,   389,  -166,    84,    95,    96,
     101,   104,   109,  -166,   262,   110,  -166,   205,    18,    18,
      18,    18,    18,    18,   322,  -166,    67,    67,    67,  -166,
    -166,  -166,  -166,   271,  -166,   187,   188,   439,  -166,   422,
     198,  -166,   389,    13,  -166,   200,  -166,  -166,   379,  -166,
    -166,  -166,    22,   140,  -166,   139,   177,  -166,  -166,   271,
    -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,
     322,   322,  -166,  -166,   389,   389,   389,   271,   463,  -166,
     189,   204,   147,  -166,     1,   177,  -166,   207,   208,   333,
     388,   271,  -166,   379,  -166,   177,  -166,  -166,  -166,  -166,
     322,   322,  -166,  -166,  -166,  -166
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    32,     1,     0,    32,     5,     0,    44,
      70,    33,    35,     0,     3,     4,    74,     6,    71,     0,
      26,    34,     0,     2,    73,    45,    47,     0,     0,     8,
      38,    39,    40,    41,    42,    43,    37,    72,     0,     0,
       0,   110,     0,    74,     0,     0,     0,     0,   106,    80,
      76,    78,    79,    81,    82,    83,    84,    85,    86,    87,
      46,     0,    27,    29,     0,    69,     0,     0,     7,    11,
      32,    12,     0,    36,    97,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   132,   130,    97,
     120,   124,   129,    97,     0,     0,     0,    91,     0,     0,
       0,     0,    75,     0,     0,    65,    66,    67,     0,     0,
       0,    49,    52,    51,    50,    59,    28,     0,     0,    20,
      20,     9,    10,    32,    16,    32,    77,     0,     0,   113,
       0,     0,     0,     0,     0,     0,     0,   135,   134,     0,
       0,     0,     0,    97,     0,     0,     0,     0,     0,     0,
      94,     0,     0,     0,     0,     0,     0,     0,     0,    97,
       0,     0,    88,     0,     0,     0,     0,     0,     0,     0,
      55,     0,     0,    48,     0,    68,    31,     0,     0,    19,
      14,    15,     0,   108,   109,     0,   111,     0,     0,     0,
       0,     0,     0,   133,     0,     0,   137,    94,   118,   119,
     114,   115,   116,   117,    97,    93,   121,   122,   123,   125,
     126,   128,   127,    96,    98,     0,     0,     0,   101,     0,
       0,   107,     0,     0,    60,     0,    53,    54,     0,    61,
      64,    30,     0,     0,    23,     0,     0,    13,    18,   112,
     138,   139,   140,   141,   142,   143,   136,   131,    92,    95,
      97,    97,    99,   100,     0,     0,     0,    90,     0,    62,
       0,    57,     0,    21,     0,     0,    17,     0,     0,     0,
       0,    89,    63,     0,    56,     0,    22,    25,   102,   103,
      97,    97,    58,    24,   104,   105
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -166,  -166,     4,  -166,  -166,   199,  -166,   201,  -166,   133,
    -166,    -8,  -166,  -166,   196,  -166,  -166,   263,   -21,  -166,
    -166,   253,  -114,  -166,  -166,   108,  -166,  -165,   -88,    -5,
    -166,   274,   236,   -76,   210,  -166,  -166,  -166,    89,  -166,
    -166,  -166,  -166,    71,  -166,  -166,    46,   -37,   338,   -66,
     -49
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     7,     8,    68,    69,    70,    71,    72,   178,
     233,   234,    29,    62,    63,     9,    11,    12,    87,    20,
      25,    26,   111,   112,   169,   170,   113,   114,    64,    88,
      17,    49,    24,    50,    51,    52,    53,    54,   205,    55,
      56,    57,   217,   218,    58,    59,   128,   129,    90,    91,
      92
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      13,    36,     5,   225,   176,    89,    13,    94,    95,   232,
      14,     5,    10,   150,    27,     1,   167,     3,   184,    48,
      27,   171,   185,    65,     4,    30,   127,    31,    32,    33,
      34,    35,   140,    10,   141,   137,   138,   142,     5,    98,
     110,    96,   144,   145,   146,   147,   148,   149,    99,   139,
     100,    66,    67,   101,     6,   186,   115,    65,   220,   185,
     258,   162,   163,   123,   151,   152,    15,   197,   153,    48,
     159,   266,   117,   118,   124,   144,   145,   146,   147,   148,
     149,   171,   166,   214,    48,   206,   207,   208,    48,   235,
     144,   145,   146,   147,   148,   149,   165,   110,   221,    65,
     277,    19,   185,   194,    65,   209,   210,   211,   212,    16,
     283,    22,   175,   115,   261,   154,   155,    23,   156,   160,
     157,   213,   224,   130,   219,    28,   117,   180,   249,   182,
      61,   144,   145,   146,   147,   148,   149,   196,    48,   215,
      73,   240,   226,    10,   262,   185,   164,   110,   239,   193,
      74,   229,   241,   242,    48,   216,   185,   185,   243,   282,
      97,   244,   185,   115,    65,   185,   245,   247,    75,   230,
     185,   185,    65,   102,   267,   268,   235,   187,   188,   189,
     190,   191,   192,   117,   228,   257,    76,   195,    10,    30,
      77,    31,    32,    33,    34,    35,   215,   263,   264,    48,
     117,   265,   259,   119,   284,   285,   120,   110,   117,   275,
     125,   131,   216,   132,   133,   110,   134,   269,   270,   271,
     135,   136,   168,   115,   103,   161,   172,    65,   173,   174,
     177,   115,   183,   104,   181,   204,   222,   272,   223,   231,
     105,   106,   107,   256,   110,    48,    48,   236,   237,   250,
     251,   238,   110,   179,   110,   260,   276,   273,   116,    65,
     115,    16,   274,    10,    38,   278,   279,   121,   115,   122,
     115,    39,    40,    41,    21,    48,    48,   227,    60,    93,
      42,   143,    18,    43,   126,    44,   248,    45,   253,     0,
      46,   144,   145,   146,   147,   148,   149,    16,    37,    10,
      38,   144,   145,   146,   147,   148,   149,    39,    40,    41,
     144,   145,   146,   147,   148,   149,    42,   246,     0,    43,
       0,    44,    47,    45,     0,    16,    46,    10,    38,     0,
       0,    16,     0,    10,    38,    39,    40,    41,     0,     0,
       0,    39,    40,    41,    42,     0,     0,    43,   158,    44,
      42,    45,     0,    43,    46,    44,     0,    45,    47,    16,
      46,    10,     0,     0,     0,     0,     0,   280,     0,    39,
      40,    41,   144,   145,   146,   147,   148,   149,    42,     0,
       0,    43,     0,    44,     0,    45,    47,     0,    46,     0,
      10,    30,    47,    31,    32,    33,    34,    35,     0,     0,
      10,    30,     0,    31,    32,    33,    34,    35,     0,     0,
       0,    78,    79,    80,    81,    82,    83,     0,     0,     0,
      47,     0,   281,     0,     0,     0,   103,   144,   145,   146,
     147,   148,   149,     0,     0,   104,    84,     0,     0,     0,
       0,    85,   105,   106,   107,    86,   108,     0,   109,   252,
      10,    30,     0,    31,    32,    33,    34,    35,   254,   255,
       0,   144,   145,   146,   147,   148,   149,    10,    30,     0,
      31,    32,    33,    34,    35,    30,     0,    31,    32,    33,
      34,    35,   198,   199,   200,   201,   202,   203
};

static const yytype_int16 yycheck[] =
{
       5,    22,     6,   168,   118,    42,    11,    44,    45,     8,
       6,     6,    11,    89,    19,     3,   104,    11,    57,    24,
      25,   109,    61,    28,     0,    12,    75,    14,    15,    16,
      17,    18,    54,    11,    56,    84,    85,    59,     6,    45,
      61,    46,    39,    40,    41,    42,    43,    44,    54,    86,
      56,     4,     5,    59,    58,    57,    61,    62,    55,    61,
      47,    98,    99,    58,    46,    47,    59,   143,    50,    74,
      34,   236,    61,    62,    70,    39,    40,    41,    42,    43,
      44,   169,   103,   159,    89,   151,   152,   153,    93,   177,
      39,    40,    41,    42,    43,    44,   101,   118,    57,   104,
     265,     7,    61,   140,   109,   154,   155,   156,   157,     9,
     275,    39,   117,   118,   228,    48,    49,    59,    51,    68,
      53,   158,    57,    77,   161,     8,    61,   123,   204,   125,
      39,    39,    40,    41,    42,    43,    44,   142,   143,   160,
      58,    57,    10,    11,   232,    61,   100,   168,   185,    57,
      62,   172,    57,    57,   159,   160,    61,    61,    57,   273,
      12,    57,    61,   168,   169,    61,    57,    57,    56,   174,
      61,    61,   177,    58,   250,   251,   264,   131,   132,   133,
     134,   135,   136,    61,    62,   222,    56,   141,    11,    12,
      56,    14,    15,    16,    17,    18,   217,    57,    58,   204,
      61,    62,   223,    11,   280,   281,    11,   228,    61,    62,
      58,    56,   217,    56,    56,   236,    56,   254,   255,   256,
      56,    56,    54,   228,    47,    45,    60,   232,    58,    60,
      56,   236,    57,    56,    58,    30,    45,   258,    60,    58,
      63,    64,    65,    45,   265,   250,   251,    62,    58,    62,
      62,    58,   273,   120,   275,    55,   264,    68,    62,   264,
     265,     9,    58,    11,    12,    58,    58,    68,   273,    68,
     275,    19,    20,    21,    11,   280,   281,   169,    25,    43,
      28,    29,     8,    31,    74,    33,   197,    35,   217,    -1,
      38,    39,    40,    41,    42,    43,    44,     9,    10,    11,
      12,    39,    40,    41,    42,    43,    44,    19,    20,    21,
      39,    40,    41,    42,    43,    44,    28,    55,    -1,    31,
      -1,    33,    70,    35,    -1,     9,    38,    11,    12,    -1,
      -1,     9,    -1,    11,    12,    19,    20,    21,    -1,    -1,
      -1,    19,    20,    21,    28,    -1,    -1,    31,    32,    33,
      28,    35,    -1,    31,    38,    33,    -1,    35,    70,     9,
      38,    11,    -1,    -1,    -1,    -1,    -1,    34,    -1,    19,
      20,    21,    39,    40,    41,    42,    43,    44,    28,    -1,
      -1,    31,    -1,    33,    -1,    35,    70,    -1,    38,    -1,
      11,    12,    70,    14,    15,    16,    17,    18,    -1,    -1,
      11,    12,    -1,    14,    15,    16,    17,    18,    -1,    -1,
      -1,    22,    23,    24,    25,    26,    27,    -1,    -1,    -1,
      70,    -1,    34,    -1,    -1,    -1,    47,    39,    40,    41,
      42,    43,    44,    -1,    -1,    56,    47,    -1,    -1,    -1,
      -1,    52,    63,    64,    65,    56,    67,    -1,    69,    10,
      11,    12,    -1,    14,    15,    16,    17,    18,    36,    37,
      -1,    39,    40,    41,    42,    43,    44,    11,    12,    -1,
      14,    15,    16,    17,    18,    12,    -1,    14,    15,    16,
      17,    18,   144,   145,   146,   147,   148,   149
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    73,    11,     0,     6,    58,    74,    75,    87,
      11,    88,    89,   101,    74,    59,     9,   102,   103,     7,
      91,    89,    39,    59,   104,    92,    93,   101,     8,    84,
      12,    14,    15,    16,    17,    18,    90,    10,    12,    19,
      20,    21,    28,    31,    33,    35,    38,    70,   101,   103,
     105,   106,   107,   108,   109,   111,   112,   113,   116,   117,
      93,    39,    85,    86,   100,   101,     4,     5,    76,    77,
      78,    79,    80,    58,    62,    56,    56,    56,    22,    23,
      24,    25,    26,    27,    47,    52,    56,    90,   101,   119,
     120,   121,   122,   104,   119,   119,   101,    12,    45,    54,
      56,    59,    58,    47,    56,    63,    64,    65,    67,    69,
      90,    94,    95,    98,    99,   101,    86,    61,    62,    11,
      11,    77,    79,    58,    74,    58,   106,   122,   118,   119,
     118,    56,    56,    56,    56,    56,    56,   122,   122,   119,
      54,    56,    59,    29,    39,    40,    41,    42,    43,    44,
     105,    46,    47,    50,    48,    49,    51,    53,    32,    34,
      68,    45,   119,   119,   118,   101,    90,   100,    54,    96,
      97,   100,    60,    58,    60,   101,    94,    56,    81,    81,
      74,    58,    74,    57,    57,    61,    57,   118,   118,   118,
     118,   118,   118,    57,   119,   118,   101,   105,   120,   120,
     120,   120,   120,   120,    30,   110,   121,   121,   121,   122,
     122,   122,   122,   119,   105,    90,   101,   114,   115,   119,
      55,    57,    45,    60,    57,    99,    10,    97,    62,    90,
     101,    58,     8,    82,    83,   100,    62,    58,    58,   119,
      57,    57,    57,    57,    57,    57,    55,    57,   110,   105,
      62,    62,    10,   115,    36,    37,    45,   119,    47,    90,
      55,    94,   100,    57,    58,    62,    99,   105,   105,   119,
     119,   119,    90,    68,    58,    62,    83,    99,    58,    58,
      34,    34,    94,    99,   105,   105
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    72,    73,    73,    73,    73,    74,    75,    76,    76,
      76,    76,    76,    77,    77,    77,    77,    78,    79,    80,
      81,    81,    82,    82,    83,    83,    84,    84,    85,    85,
      86,    86,    87,    87,    88,    88,    89,    89,    90,    90,
      90,    90,    90,    90,    91,    91,    92,    92,    93,    93,
      94,    94,    94,    95,    96,    96,    97,    97,    98,    99,
      99,    99,    99,    99,    99,    99,    99,    99,   100,   100,
     101,   102,   103,   103,   104,   104,   104,   105,   105,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   107,   107,
     107,   108,   109,   109,   110,   110,   111,   111,   112,   113,
     114,   114,   115,   115,   116,   116,   117,   117,   117,   117,
     117,   117,   118,   118,   119,   119,   119,   119,   119,   119,
     119,   120,   120,   120,   120,   121,   121,   121,   121,   121,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     4,     4,     3,     2,     4,     0,     2,
       2,     1,     1,     4,     3,     3,     2,     5,     4,     3,
       0,     3,     3,     1,     4,     3,     0,     2,     2,     1,
       4,     3,     0,     2,     2,     1,     4,     3,     1,     1,
       1,     1,     1,     1,     0,     2,     2,     1,     4,     3,
       1,     1,     1,     3,     2,     1,     4,     3,     6,     1,
       3,     3,     4,     5,     3,     1,     1,     1,     3,     1,
       1,     1,     3,     2,     0,     3,     2,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     6,
       5,     2,     5,     4,     0,     2,     4,     0,     4,     5,
       2,     1,     4,     4,     8,     8,     1,     4,     4,     4,
       1,     4,     3,     1,     3,     3,     3,     3,     3,     3,
       1,     3,     3,     3,     1,     3,     3,     3,     3,     1,
       1,     4,     1,     3,     2,     2,     4,     3,     4,     4,
       4,     4,     4,     4
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
#line 169 "src/yacc.y"
                                             {
        std::string name{(yyvsp[-3].token).stringValue};
        (yyvsp[-1].routineNode)->setSubType(ast::RoutineNode::SubType::MAIN);
        (yyval.programNode) = new ast::ProgramNode(std::move(name), (yyvsp[-1].routineNode));
        resultAst = (yyval.programNode);
    }
#line 1447 "out/parser.cpp"
    break;

  case 3: /* program: PROGRAM IDENT_NAME SEMICOLON routine  */
#line 176 "src/yacc.y"
                                         {
        std::string name{(yyvsp[-2].token).stringValue};
        (yyvsp[0].routineNode)->setSubType(ast::RoutineNode::SubType::MAIN);
        (yyval.programNode) = new ast::ProgramNode(std::move(name), (yyvsp[0].routineNode));
        resultAst = (yyval.programNode);
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of end dot");
    }
#line 1459 "out/parser.cpp"
    break;

  case 4: /* program: PROGRAM IDENT_NAME routine DOT  */
#line 184 "src/yacc.y"
                                   {
        std::string name{(yyvsp[-2].token).stringValue};
        (yyvsp[-1].routineNode)->setSubType(ast::RoutineNode::SubType::MAIN);
        (yyval.programNode) = new ast::ProgramNode(std::move(name), (yyvsp[-1].routineNode));
        resultAst = (yyval.programNode);
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1471 "out/parser.cpp"
    break;

  case 5: /* program: PROGRAM IDENT_NAME routine  */
#line 192 "src/yacc.y"
                               {
        std::string name{(yyvsp[-1].token).stringValue};
        (yyvsp[0].routineNode)->setSubType(ast::RoutineNode::SubType::MAIN);
        (yyval.programNode) = new ast::ProgramNode(std::move(name), (yyvsp[0].routineNode));
        resultAst = (yyval.programNode);
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of semicolon and end dot");
    }
#line 1483 "out/parser.cpp"
    break;

  case 6: /* routine: routine_head routine_body  */
#line 202 "src/yacc.y"
                              {
        (yyval.routineNode) = new ast::RoutineNode((yyvsp[-1].routineHeadNode), (yyvsp[0].routineBodyNode));
    }
#line 1491 "out/parser.cpp"
    break;

  case 7: /* routine_head: const_part type_part var_part routine_part  */
#line 208 "src/yacc.y"
                                               {
        (yyval.routineHeadNode) = new ast::RoutineHeadNode((yyvsp[-3].constPartList), (yyvsp[-2].typePartList), (yyvsp[-1].varPartList), (yyvsp[0].routinePartList));
    }
#line 1499 "out/parser.cpp"
    break;

  case 8: /* routine_part: %empty  */
#line 214 "src/yacc.y"
    {
        (yyval.routinePartList) = new std::vector<ast::RoutineDeclarationNode*>();
    }
#line 1507 "out/parser.cpp"
    break;

  case 9: /* routine_part: routine_part fun_decl  */
#line 218 "src/yacc.y"
                          {
        (yyval.routinePartList) = (yyvsp[-1].routinePartList);
        (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1516 "out/parser.cpp"
    break;

  case 10: /* routine_part: routine_part proc_decl  */
#line 223 "src/yacc.y"
                           {
       (yyval.routinePartList) = (yyvsp[-1].routinePartList);
       (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1525 "out/parser.cpp"
    break;

  case 11: /* routine_part: fun_decl  */
#line 228 "src/yacc.y"
             {
        (yyval.routinePartList) = new std::vector<ast::RoutineDeclarationNode*>();
        (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1534 "out/parser.cpp"
    break;

  case 12: /* routine_part: proc_decl  */
#line 233 "src/yacc.y"
              {
        (yyval.routinePartList) = new std::vector<ast::RoutineDeclarationNode*>();
        (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1543 "out/parser.cpp"
    break;

  case 13: /* fun_decl: fun_head SEMICOLON routine SEMICOLON  */
#line 240 "src/yacc.y"
                                         {
        (yyval.routineDeclarationNode) = (yyvsp[-3].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[-1].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
    }
#line 1553 "out/parser.cpp"
    break;

  case 14: /* fun_decl: fun_head SEMICOLON routine  */
#line 246 "src/yacc.y"
                               {
        (yyval.routineDeclarationNode) = (yyvsp[-2].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[0].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1564 "out/parser.cpp"
    break;

  case 15: /* fun_decl: fun_head routine SEMICOLON  */
#line 253 "src/yacc.y"
                               {
        (yyval.routineDeclarationNode) = (yyvsp[-2].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[-1].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1575 "out/parser.cpp"
    break;

  case 16: /* fun_decl: fun_head routine  */
#line 260 "src/yacc.y"
                     {
        (yyval.routineDeclarationNode) = (yyvsp[-1].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[0].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1586 "out/parser.cpp"
    break;

  case 17: /* fun_head: FUNCTION IDENT_NAME params COLON simple_type  */
#line 269 "src/yacc.y"
                                                 {
        std::string name{(yyvsp[-3].token).stringValue};
        (yyval.routineDeclarationNode) = new ast::RoutineDeclarationNode(ast::RoutineDeclarationNode::RoutineType::FUNCTION, std::move(name), (yyvsp[-2].paramsNode), (yyvsp[0].simpleTypeNode), nullptr);
    }
#line 1595 "out/parser.cpp"
    break;

  case 18: /* proc_decl: proc_head SEMICOLON routine SEMICOLON  */
#line 276 "src/yacc.y"
                                          {
        (yyval.routineDeclarationNode) = (yyvsp[-3].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[-1].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::PROCEDURE);
    }
#line 1605 "out/parser.cpp"
    break;

  case 19: /* proc_head: PROCEDURE IDENT_NAME params  */
#line 284 "src/yacc.y"
                                {
        std::string name{(yyvsp[-1].token).stringValue};
        (yyval.routineDeclarationNode) = new ast::RoutineDeclarationNode(ast::RoutineDeclarationNode::RoutineType::PROCEDURE, std::move(name), (yyvsp[0].paramsNode), nullptr, nullptr);
    }
#line 1614 "out/parser.cpp"
    break;

  case 20: /* params: %empty  */
#line 291 "src/yacc.y"
    {
        std::vector<ast::ParamsGroupNode *>* emptyParamsList{};
        (yyval.paramsNode) = new ast::ParamsNode(emptyParamsList);
    }
#line 1623 "out/parser.cpp"
    break;

  case 21: /* params: LP params_decl RP  */
#line 296 "src/yacc.y"
                      {
        (yyval.paramsNode) = new ast::ParamsNode((yyvsp[-1].paramsGroupList));
    }
#line 1631 "out/parser.cpp"
    break;

  case 22: /* params_decl: params_decl SEMICOLON params_type  */
#line 302 "src/yacc.y"
                                      {
       (yyval.paramsGroupList) = (yyvsp[-2].paramsGroupList);
       (yyval.paramsGroupList)->push_back((yyvsp[0].paramsGroupNode));
    }
#line 1640 "out/parser.cpp"
    break;

  case 23: /* params_decl: params_type  */
#line 307 "src/yacc.y"
                {
        (yyval.paramsGroupList) = new std::vector<ast::ParamsGroupNode*>();
        (yyval.paramsGroupList)->push_back((yyvsp[0].paramsGroupNode));
    }
#line 1649 "out/parser.cpp"
    break;

  case 24: /* params_type: VAR name_list COLON simple_type  */
#line 314 "src/yacc.y"
                                    {
        (yyval.paramsGroupNode) = new ast::ParamsGroupNode(ast::ParamsGroupNode::PassType::PASS_BY_REFERENCE, (yyvsp[-2].identifierList), (yyvsp[0].simpleTypeNode));
    }
#line 1657 "out/parser.cpp"
    break;

  case 25: /* params_type: name_list COLON simple_type  */
#line 318 "src/yacc.y"
                                {
        (yyval.paramsGroupNode) = new ast::ParamsGroupNode(ast::ParamsGroupNode::PassType::PASS_BY_VALUE, (yyvsp[-2].identifierList), (yyvsp[0].simpleTypeNode));
    }
#line 1665 "out/parser.cpp"
    break;

  case 26: /* var_part: %empty  */
#line 324 "src/yacc.y"
    {
        (yyval.varPartList) = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
    }
#line 1673 "out/parser.cpp"
    break;

  case 27: /* var_part: VAR var_decl_list  */
#line 328 "src/yacc.y"
                      {
        (yyval.varPartList) = (yyvsp[0].varPartList);
    }
#line 1681 "out/parser.cpp"
    break;

  case 28: /* var_decl_list: var_decl_list var_decl  */
#line 334 "src/yacc.y"
                           {
        (yyval.varPartList) = (yyvsp[-1].varPartList);
        (yyval.varPartList)->push_back((yyvsp[0].varPartListElement));
    }
#line 1690 "out/parser.cpp"
    break;

  case 29: /* var_decl_list: var_decl  */
#line 339 "src/yacc.y"
             {
        (yyval.varPartList) = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
        (yyval.varPartList)->push_back((yyvsp[0].varPartListElement));
    }
#line 1699 "out/parser.cpp"
    break;

  case 30: /* var_decl: name_list COLON type_decl SEMICOLON  */
#line 346 "src/yacc.y"
                                        {
        (yyval.varPartListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-3].identifierList), (yyvsp[-1].typeNode));
    }
#line 1707 "out/parser.cpp"
    break;

  case 31: /* var_decl: name_list COLON type_decl  */
#line 350 "src/yacc.y"
                              {
        (yyval.varPartListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-2].identifierList), (yyvsp[0].typeNode));
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1716 "out/parser.cpp"
    break;

  case 32: /* const_part: %empty  */
#line 357 "src/yacc.y"
    {
        (yyval.constPartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::ConstantNode*>*>();
    }
#line 1724 "out/parser.cpp"
    break;

  case 33: /* const_part: CONST const_expr_list  */
#line 361 "src/yacc.y"
                          {
        (yyval.constPartList) = (yyvsp[0].constPartList);
    }
#line 1732 "out/parser.cpp"
    break;

  case 34: /* const_expr_list: const_expr_list const_expr  */
#line 367 "src/yacc.y"
                               {
        (yyval.constPartList) = (yyvsp[-1].constPartList);
        (yyval.constPartList)->push_back((yyvsp[0].constPartListElement));
    }
#line 1741 "out/parser.cpp"
    break;

  case 35: /* const_expr_list: const_expr  */
#line 372 "src/yacc.y"
               {
        (yyval.constPartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::ConstantNode*>*>();
        (yyval.constPartList)->push_back((yyvsp[0].constPartListElement));
    }
#line 1750 "out/parser.cpp"
    break;

  case 36: /* const_expr: identifier EQUAL const_value SEMICOLON  */
#line 379 "src/yacc.y"
                                           {
        (yyval.constPartListElement) = new std::pair<ast::IdentifierNode*, ast::ConstantNode*>((yyvsp[-3].identifierNode), (yyvsp[-1].constantNode));
    }
#line 1758 "out/parser.cpp"
    break;

  case 37: /* const_expr: identifier EQUAL const_value  */
#line 383 "src/yacc.y"
                                 {
        (yyval.constPartListElement) = new std::pair<ast::IdentifierNode*, ast::ConstantNode*>((yyvsp[-2].identifierNode), (yyvsp[0].constantNode));
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1767 "out/parser.cpp"
    break;

  case 38: /* const_value: INTEGER  */
#line 390 "src/yacc.y"
            {
        (yyval.constantNode) = new ast::IntegerConstantNode((yyvsp[0].token).numericalValue);
    }
#line 1775 "out/parser.cpp"
    break;

  case 39: /* const_value: CHAR  */
#line 394 "src/yacc.y"
    {
        (yyval.constantNode) = new ast::CharConstantNode((yyvsp[0].token).stringValue[0]);
    }
#line 1783 "out/parser.cpp"
    break;

  case 40: /* const_value: STRING  */
#line 398 "src/yacc.y"
           {
        std::string str{(yyvsp[0].token).stringValue};
        (yyval.constantNode) = new ast::StringConstantNode(std::move(str));
    }
#line 1792 "out/parser.cpp"
    break;

  case 41: /* const_value: TRUE  */
#line 403 "src/yacc.y"
         {
        (yyval.constantNode) = new ast::BooleanConstantNode(true);
    }
#line 1800 "out/parser.cpp"
    break;

  case 42: /* const_value: FALSE  */
#line 407 "src/yacc.y"
          {
        (yyval.constantNode) = new ast::BooleanConstantNode(false);
    }
#line 1808 "out/parser.cpp"
    break;

  case 43: /* const_value: MAXINT  */
#line 411 "src/yacc.y"
           {
        (yyval.constantNode) = new ast::IntegerConstantNode(255);
    }
#line 1816 "out/parser.cpp"
    break;

  case 44: /* type_part: %empty  */
#line 417 "src/yacc.y"
    {
        (yyval.typePartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::TypeNode*>*>();
    }
#line 1824 "out/parser.cpp"
    break;

  case 45: /* type_part: TYPE type_decl_list  */
#line 421 "src/yacc.y"
                        {
        (yyval.typePartList) = (yyvsp[0].typePartList);
    }
#line 1832 "out/parser.cpp"
    break;

  case 46: /* type_decl_list: type_decl_list type_def  */
#line 427 "src/yacc.y"
                            {
        (yyval.typePartList) = (yyvsp[-1].typePartList);
        (yyval.typePartList)->push_back((yyvsp[0].typePartListElement));
    }
#line 1841 "out/parser.cpp"
    break;

  case 47: /* type_decl_list: type_def  */
#line 432 "src/yacc.y"
             {
        (yyval.typePartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::TypeNode*>*>();
        (yyval.typePartList)->push_back((yyvsp[0].typePartListElement));
    }
#line 1850 "out/parser.cpp"
    break;

  case 48: /* type_def: identifier EQUAL type_decl SEMICOLON  */
#line 439 "src/yacc.y"
                                         {
        (yyval.typePartListElement) = new std::pair<ast::IdentifierNode*, ast::TypeNode*>((yyvsp[-3].identifierNode), (yyvsp[-1].typeNode));
    }
#line 1858 "out/parser.cpp"
    break;

  case 49: /* type_def: identifier EQUAL type_decl  */
#line 443 "src/yacc.y"
                               {
        (yyval.typePartListElement) = new std::pair<ast::IdentifierNode*, ast::TypeNode*>((yyvsp[-2].identifierNode), (yyvsp[0].typeNode));
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1867 "out/parser.cpp"
    break;

  case 50: /* type_decl: simple_type  */
#line 450 "src/yacc.y"
                {
        (yyval.typeNode) = (yyvsp[0].simpleTypeNode);
    }
#line 1875 "out/parser.cpp"
    break;

  case 51: /* type_decl: array_type_decl  */
#line 454 "src/yacc.y"
                    {
        (yyval.typeNode) = (yyvsp[0].arrayTypeNode);
    }
#line 1883 "out/parser.cpp"
    break;

  case 52: /* type_decl: record_type_decl  */
#line 458 "src/yacc.y"
                     {
        (yyval.typeNode) = (yyvsp[0].recordTypeNode);
    }
#line 1891 "out/parser.cpp"
    break;

  case 53: /* record_type_decl: RECORD field_decl_list END  */
#line 464 "src/yacc.y"
                               {
        (yyval.recordTypeNode) = new ast::RecordTypeNode((yyvsp[-1].fieldDeclList));
    }
#line 1899 "out/parser.cpp"
    break;

  case 54: /* field_decl_list: field_decl_list field_decl  */
#line 470 "src/yacc.y"
                               {
        (yyval.fieldDeclList) = (yyvsp[-1].fieldDeclList);
        (yyval.fieldDeclList)->push_back((yyvsp[0].fieldDeclListElement));
    }
#line 1908 "out/parser.cpp"
    break;

  case 55: /* field_decl_list: field_decl  */
#line 475 "src/yacc.y"
               {
        (yyval.fieldDeclList) = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
        (yyval.fieldDeclList)->push_back((yyvsp[0].fieldDeclListElement));
    }
#line 1917 "out/parser.cpp"
    break;

  case 56: /* field_decl: name_list COLON type_decl SEMICOLON  */
#line 482 "src/yacc.y"
                                        {
        (yyval.fieldDeclListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-3].identifierList), (yyvsp[-1].typeNode));
    }
#line 1925 "out/parser.cpp"
    break;

  case 57: /* field_decl: name_list COLON type_decl  */
#line 486 "src/yacc.y"
                              {
        (yyval.fieldDeclListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-2].identifierList), (yyvsp[0].typeNode));
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1934 "out/parser.cpp"
    break;

  case 58: /* array_type_decl: ARRAY LB simple_type RB OF type_decl  */
#line 493 "src/yacc.y"
                                         {
        (yyval.arrayTypeNode) = new ast::ArrayTypeNode((yyvsp[-3].simpleTypeNode), (yyvsp[0].typeNode));
    }
#line 1942 "out/parser.cpp"
    break;

  case 59: /* simple_type: identifier  */
#line 499 "src/yacc.y"
               {
        (yyval.simpleTypeNode) = new ast::RenameTypeNode((yyvsp[0].identifierNode));
    }
#line 1950 "out/parser.cpp"
    break;

  case 60: /* simple_type: LP name_list RP  */
#line 503 "src/yacc.y"
                    {
        (yyval.simpleTypeNode) = new ast::EnumerationTypeNode((yyvsp[-1].identifierList));
    }
#line 1958 "out/parser.cpp"
    break;

  case 61: /* simple_type: const_value DOUBLEDOT const_value  */
#line 507 "src/yacc.y"
                                      {
        (yyval.simpleTypeNode) = new ast::ConstRangeTypeNode((yyvsp[-2].constantNode), (yyvsp[0].constantNode));
    }
#line 1966 "out/parser.cpp"
    break;

  case 62: /* simple_type: MINUS const_value DOUBLEDOT const_value  */
#line 511 "src/yacc.y"
                                            {
        (yyval.simpleTypeNode) = new ast::ConstRangeTypeNode((yyvsp[-2].constantNode), (yyvsp[0].constantNode));
    }
#line 1974 "out/parser.cpp"
    break;

  case 63: /* simple_type: MINUS const_value DOUBLEDOT MINUS const_value  */
#line 515 "src/yacc.y"
                                                  {
        (yyval.simpleTypeNode) = new ast::ConstRangeTypeNode((yyvsp[-3].constantNode), (yyvsp[0].constantNode));
    }
#line 1982 "out/parser.cpp"
    break;

  case 64: /* simple_type: identifier DOUBLEDOT identifier  */
#line 519 "src/yacc.y"
                                    {
        (yyval.simpleTypeNode) = new ast::VarRangeTypeNode((yyvsp[-2].identifierNode), (yyvsp[0].identifierNode));
    }
#line 1990 "out/parser.cpp"
    break;

  case 65: /* simple_type: INT_TYPE  */
#line 523 "src/yacc.y"
             {
        (yyval.simpleTypeNode) = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::INTEGER);
    }
#line 1998 "out/parser.cpp"
    break;

  case 66: /* simple_type: BOOL_TYPE  */
#line 527 "src/yacc.y"
              {
        (yyval.simpleTypeNode) = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::BOOLEAN);
    }
#line 2006 "out/parser.cpp"
    break;

  case 67: /* simple_type: CHAR_TYPE  */
#line 531 "src/yacc.y"
              {
        (yyval.simpleTypeNode) = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::CHAR);
    }
#line 2014 "out/parser.cpp"
    break;

  case 68: /* name_list: name_list COMMA identifier  */
#line 537 "src/yacc.y"
                               {
        (yyval.identifierList) = (yyvsp[-2].identifierList);
        (yyval.identifierList)->push_back((yyvsp[0].identifierNode));
    }
#line 2023 "out/parser.cpp"
    break;

  case 69: /* name_list: identifier  */
#line 542 "src/yacc.y"
               {
        (yyval.identifierList) = new std::vector<ast::IdentifierNode*>();
        (yyval.identifierList)->push_back((yyvsp[0].identifierNode));
    }
#line 2032 "out/parser.cpp"
    break;

  case 70: /* identifier: IDENT_NAME  */
#line 549 "src/yacc.y"
               {
        std::string name{(yyvsp[0].token).stringValue};
        (yyval.identifierNode) = new ast::IdentifierNode(std::move(name));
    }
#line 2041 "out/parser.cpp"
    break;

  case 71: /* routine_body: compound_stmt  */
#line 556 "src/yacc.y"
                  {
        (yyval.routineBodyNode) = new ast::RoutineBodyNode((yyvsp[0].compoundStatementNode));
    }
#line 2049 "out/parser.cpp"
    break;

  case 72: /* compound_stmt: BBEGIN stmt_list END  */
#line 562 "src/yacc.y"
                         {
        (yyval.compoundStatementNode) = new ast::CompoundStatementNode((yyvsp[-1].statementNodeList));
    }
#line 2057 "out/parser.cpp"
    break;

  case 73: /* compound_stmt: BBEGIN stmt_list  */
#line 566 "src/yacc.y"
                     {
        (yyval.compoundStatementNode) = new ast::CompoundStatementNode((yyvsp[0].statementNodeList));
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of end");
    }
#line 2066 "out/parser.cpp"
    break;

  case 74: /* stmt_list: %empty  */
#line 573 "src/yacc.y"
    {
        (yyval.statementNodeList) = new std::vector<ast::StatementNode*>();
    }
#line 2074 "out/parser.cpp"
    break;

  case 75: /* stmt_list: stmt_list stmt SEMICOLON  */
#line 577 "src/yacc.y"
                             {
        (yyval.statementNodeList) = (yyvsp[-2].statementNodeList);
        (yyval.statementNodeList)->push_back((yyvsp[-1].statementNode));
    }
#line 2083 "out/parser.cpp"
    break;

  case 76: /* stmt_list: stmt_list stmt  */
#line 582 "src/yacc.y"
                   {
        (yyval.statementNodeList) = (yyvsp[-1].statementNodeList);
        (yyval.statementNodeList)->push_back((yyvsp[0].statementNode));
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2093 "out/parser.cpp"
    break;

  case 77: /* stmt: INTEGER COLON no_label_stmt  */
#line 590 "src/yacc.y"
                                {
        (yyval.statementNode) = (yyvsp[0].statementNode);
        (yyval.statementNode)->setLabel((yyvsp[-2].token).numericalValue);
    }
#line 2102 "out/parser.cpp"
    break;

  case 78: /* stmt: no_label_stmt  */
#line 595 "src/yacc.y"
                  {
        (yyval.statementNode) = (yyvsp[0].statementNode);
    }
#line 2110 "out/parser.cpp"
    break;

  case 79: /* no_label_stmt: assign_stmt  */
#line 601 "src/yacc.y"
                {
        (yyval.statementNode)=(yyvsp[0].assignNode);
    }
#line 2118 "out/parser.cpp"
    break;

  case 80: /* no_label_stmt: compound_stmt  */
#line 605 "src/yacc.y"
                  {
        (yyval.statementNode) = (yyvsp[0].compoundStatementNode);
    }
#line 2126 "out/parser.cpp"
    break;

  case 81: /* no_label_stmt: goto_stmt  */
#line 609 "src/yacc.y"
              {
        (yyval.statementNode) = (yyvsp[0].gotoNode);
    }
#line 2134 "out/parser.cpp"
    break;

  case 82: /* no_label_stmt: if_stmt  */
#line 613 "src/yacc.y"
            {
        (yyval.statementNode) = (yyvsp[0].ifNode);
    }
#line 2142 "out/parser.cpp"
    break;

  case 83: /* no_label_stmt: repeat_stmt  */
#line 617 "src/yacc.y"
                {
        (yyval.statementNode) = (yyvsp[0].repeatNode);
    }
#line 2150 "out/parser.cpp"
    break;

  case 84: /* no_label_stmt: while_stmt  */
#line 621 "src/yacc.y"
               {
        (yyval.statementNode) = (yyvsp[0].whileNode);
    }
#line 2158 "out/parser.cpp"
    break;

  case 85: /* no_label_stmt: case_stmt  */
#line 625 "src/yacc.y"
              {
        (yyval.statementNode) = (yyvsp[0].caseNode);
    }
#line 2166 "out/parser.cpp"
    break;

  case 86: /* no_label_stmt: for_stmt  */
#line 629 "src/yacc.y"
             {
        (yyval.statementNode) = (yyvsp[0].forNode);
    }
#line 2174 "out/parser.cpp"
    break;

  case 87: /* no_label_stmt: proc_stmt  */
#line 633 "src/yacc.y"
              {
        (yyval.statementNode) = (yyvsp[0].callNode);
    }
#line 2182 "out/parser.cpp"
    break;

  case 88: /* assign_stmt: identifier ASSIGN expression  */
#line 639 "src/yacc.y"
                                 {
        (yyval.assignNode) = new ast::AssignToVariableNode((yyvsp[-2].identifierNode), (yyvsp[0].expressionNode));
    }
#line 2190 "out/parser.cpp"
    break;

  case 89: /* assign_stmt: identifier LB expression RB ASSIGN expression  */
#line 643 "src/yacc.y"
                                                  {
        (yyval.assignNode) = new ast::AssignToArrayNode((yyvsp[-5].identifierNode), (yyvsp[-3].expressionNode), (yyvsp[0].expressionNode));
    }
#line 2198 "out/parser.cpp"
    break;

  case 90: /* assign_stmt: identifier DOT identifier ASSIGN expression  */
#line 647 "src/yacc.y"
                                                {
        (yyval.assignNode) = new ast::AssignToRecordFieldNode((yyvsp[-4].identifierNode), (yyvsp[-2].identifierNode), (yyvsp[0].expressionNode));
    }
#line 2206 "out/parser.cpp"
    break;

  case 91: /* goto_stmt: GOTO INTEGER  */
#line 653 "src/yacc.y"
                 {
        (yyval.gotoNode) = new ast::GotoNode((yyvsp[0].token).numericalValue);
    }
#line 2214 "out/parser.cpp"
    break;

  case 92: /* if_stmt: IF expression THEN stmt else_clause  */
#line 659 "src/yacc.y"
                                        {
        (yyval.ifNode) = new ast::IfNode((yyvsp[-3].expressionNode), (yyvsp[-1].statementNode), (yyvsp[0].ifNode));
    }
#line 2222 "out/parser.cpp"
    break;

  case 93: /* if_stmt: IF expression stmt else_clause  */
#line 663 "src/yacc.y"
                                   {
        (yyval.ifNode) = new ast::IfNode((yyvsp[-2].expressionNode), (yyvsp[-1].statementNode), (yyvsp[0].ifNode));
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of then");
    }
#line 2231 "out/parser.cpp"
    break;

  case 94: /* else_clause: %empty  */
#line 670 "src/yacc.y"
    {
        (yyval.ifNode) = new ast::IfNode(nullptr, nullptr);
    }
#line 2239 "out/parser.cpp"
    break;

  case 95: /* else_clause: ELSE stmt  */
#line 674 "src/yacc.y"
              {
        (yyval.ifNode) = new ast::IfNode(nullptr, nullptr, (yyvsp[0].statementNode));
    }
#line 2247 "out/parser.cpp"
    break;

  case 96: /* repeat_stmt: REPEAT stmt_list UNTIL expression  */
#line 680 "src/yacc.y"
                                      {
        (yyval.repeatNode) = new ast::RepeatNode((yyvsp[0].expressionNode), (yyvsp[-2].statementNodeList));
    }
#line 2255 "out/parser.cpp"
    break;

  case 97: /* repeat_stmt: %empty  */
#line 684 "src/yacc.y"
    {
    }
#line 2262 "out/parser.cpp"
    break;

  case 98: /* while_stmt: WHILE expression DO stmt  */
#line 689 "src/yacc.y"
                             {
        (yyval.whileNode) = new ast::WhileNode((yyvsp[-2].expressionNode), (yyvsp[0].statementNode));
    }
#line 2270 "out/parser.cpp"
    break;

  case 99: /* case_stmt: CASE expression OF case_expr_list END  */
#line 695 "src/yacc.y"
                                          {
        (yyval.caseNode) = new ast::CaseNode((yyvsp[-3].expressionNode), (yyvsp[-1].caseExprList));
    }
#line 2278 "out/parser.cpp"
    break;

  case 100: /* case_expr_list: case_expr_list case_expr  */
#line 701 "src/yacc.y"
                             {
        (yyval.caseExprList) = (yyvsp[-1].caseExprList);
        (yyval.caseExprList)->push_back((yyvsp[0].caseExpr));
    }
#line 2287 "out/parser.cpp"
    break;

  case 101: /* case_expr_list: case_expr  */
#line 706 "src/yacc.y"
              {
        (yyval.caseExprList) = new std::vector<std::pair<ast::AstNode*, ast::StatementNode*>*>();
        (yyval.caseExprList)->push_back((yyvsp[0].caseExpr));
    }
#line 2296 "out/parser.cpp"
    break;

  case 102: /* case_expr: const_value COLON stmt SEMICOLON  */
#line 713 "src/yacc.y"
                                     {
        (yyval.caseExpr) = new std::pair<ast::AstNode*, ast::StatementNode*>((yyvsp[-3].constantNode), (yyvsp[-1].statementNode));
    }
#line 2304 "out/parser.cpp"
    break;

  case 103: /* case_expr: identifier COLON stmt SEMICOLON  */
#line 717 "src/yacc.y"
                                    {
        (yyval.caseExpr) = new std::pair<ast::AstNode*, ast::StatementNode*>((yyvsp[-3].identifierNode), (yyvsp[-1].statementNode));
    }
#line 2312 "out/parser.cpp"
    break;

  case 104: /* for_stmt: FOR identifier ASSIGN expression TO expression DO stmt  */
#line 723 "src/yacc.y"
                                                           {
        (yyval.forNode) = new ast::ForNode((yyvsp[-6].identifierNode), (yyvsp[-4].expressionNode), (yyvsp[-2].expressionNode), (yyvsp[0].statementNode), ast::ForNode::Direction::INCREMENT);
    }
#line 2320 "out/parser.cpp"
    break;

  case 105: /* for_stmt: FOR identifier ASSIGN expression DOWNTO expression DO stmt  */
#line 727 "src/yacc.y"
                                                               {
        (yyval.forNode) = new ast::ForNode((yyvsp[-6].identifierNode), (yyvsp[-4].expressionNode), (yyvsp[-2].expressionNode), (yyvsp[0].statementNode), ast::ForNode::Direction::DECREMENT);
    }
#line 2328 "out/parser.cpp"
    break;

  case 106: /* proc_stmt: identifier  */
#line 733 "src/yacc.y"
               {
        (yyval.callNode) = new ast::UserDefineCallNode((yyvsp[0].identifierNode), nullptr);
    }
#line 2336 "out/parser.cpp"
    break;

  case 107: /* proc_stmt: identifier LP args_list RP  */
#line 737 "src/yacc.y"
                               {
        (yyval.callNode) = new ast::UserDefineCallNode((yyvsp[-3].identifierNode), (yyvsp[-1].argsList));
    }
#line 2344 "out/parser.cpp"
    break;

  case 108: /* proc_stmt: READ LP factor RP  */
#line 741 "src/yacc.y"
                      {
        ast::ArgumentsListNode* args = new ast::ArgumentsListNode();
        args->addArgument((yyvsp[-1].expressionNode));
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::READ, args);
    }
#line 2354 "out/parser.cpp"
    break;

  case 109: /* proc_stmt: WRITE LP args_list RP  */
#line 747 "src/yacc.y"
                          {
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITE, (yyvsp[-1].argsList));
    }
#line 2362 "out/parser.cpp"
    break;

  case 110: /* proc_stmt: WRITELN  */
#line 751 "src/yacc.y"
            {
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITELN, nullptr);
    }
#line 2370 "out/parser.cpp"
    break;

  case 111: /* proc_stmt: WRITELN LP args_list RP  */
#line 755 "src/yacc.y"
                            {
        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITELN, (yyvsp[-1].argsList));
    }
#line 2378 "out/parser.cpp"
    break;

  case 112: /* args_list: args_list COMMA expression  */
#line 761 "src/yacc.y"
                               {
        (yyval.argsList) = (yyvsp[-2].argsList);
        (yyval.argsList)->addArgument((yyvsp[0].expressionNode));
    }
#line 2387 "out/parser.cpp"
    break;

  case 113: /* args_list: expression  */
#line 766 "src/yacc.y"
                {
        (yyval.argsList) = new ast::ArgumentsListNode();
        (yyval.argsList)->addArgument((yyvsp[0].expressionNode));
    }
#line 2396 "out/parser.cpp"
    break;

  case 114: /* expression: expression GE expr  */
#line 773 "src/yacc.y"
                       {
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::GREATER_EQUAL);
    }
#line 2404 "out/parser.cpp"
    break;

  case 115: /* expression: expression GT expr  */
#line 777 "src/yacc.y"
                       {
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::GREATER);
    }
#line 2412 "out/parser.cpp"
    break;

  case 116: /* expression: expression LE expr  */
#line 781 "src/yacc.y"
                       {
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::LESS_EQUAL);
    }
#line 2420 "out/parser.cpp"
    break;

  case 117: /* expression: expression LT expr  */
#line 785 "src/yacc.y"
                       {
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::LESS);
    }
#line 2428 "out/parser.cpp"
    break;

  case 118: /* expression: expression EQUAL expr  */
#line 789 "src/yacc.y"
                          {
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::EQUAL);
    }
#line 2436 "out/parser.cpp"
    break;

  case 119: /* expression: expression UNEQUAL expr  */
#line 793 "src/yacc.y"
                            {
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::NOT_EQUAL);
    }
#line 2444 "out/parser.cpp"
    break;

  case 120: /* expression: expr  */
#line 797 "src/yacc.y"
         {
        (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 2452 "out/parser.cpp"
    break;

  case 121: /* expr: expr PLUS term  */
#line 803 "src/yacc.y"
                   {
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::ADDITION);
    }
#line 2460 "out/parser.cpp"
    break;

  case 122: /* expr: expr MINUS term  */
#line 807 "src/yacc.y"
                    {
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::SUBTRACTION);
    }
#line 2468 "out/parser.cpp"
    break;

  case 123: /* expr: expr OR term  */
#line 811 "src/yacc.y"
                 {
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::OR);
    }
#line 2476 "out/parser.cpp"
    break;

  case 124: /* expr: term  */
#line 815 "src/yacc.y"
         {
        (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 2484 "out/parser.cpp"
    break;

  case 125: /* term: term MUL factor  */
#line 821 "src/yacc.y"
                    {
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::MULTIPLICATION);
    }
#line 2492 "out/parser.cpp"
    break;

  case 126: /* term: term DIV factor  */
#line 825 "src/yacc.y"
                    {
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::DIVISION);
    }
#line 2500 "out/parser.cpp"
    break;

  case 127: /* term: term MOD factor  */
#line 829 "src/yacc.y"
                    {
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::MODULUS);
    }
#line 2508 "out/parser.cpp"
    break;

  case 128: /* term: term AND factor  */
#line 833 "src/yacc.y"
                    {
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::AND);
    }
#line 2516 "out/parser.cpp"
    break;

  case 129: /* term: factor  */
#line 837 "src/yacc.y"
           {
        (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 2524 "out/parser.cpp"
    break;

  case 130: /* factor: identifier  */
#line 843 "src/yacc.y"
               {
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[0].identifierNode), ast::SpecialExpressionNode::FunctionName::VARIABLE);
    }
#line 2532 "out/parser.cpp"
    break;

  case 131: /* factor: identifier LP args_list RP  */
#line 847 "src/yacc.y"
                               {
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-3].identifierNode), (yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::CALL);
    }
#line 2540 "out/parser.cpp"
    break;

  case 132: /* factor: const_value  */
#line 851 "src/yacc.y"
                {
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[0].constantNode), ast::SpecialExpressionNode::FunctionName::CONST);
    }
#line 2548 "out/parser.cpp"
    break;

  case 133: /* factor: LP expression RP  */
#line 855 "src/yacc.y"
                     {
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].expressionNode), ast::SpecialExpressionNode::FunctionName::PARENTHESIS);
    }
#line 2556 "out/parser.cpp"
    break;

  case 134: /* factor: NOT factor  */
#line 859 "src/yacc.y"
               {
       (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[0].expressionNode), ast::ExpressionNode::Operation::NOT);
    }
#line 2564 "out/parser.cpp"
    break;

  case 135: /* factor: MINUS factor  */
#line 863 "src/yacc.y"
                 {
        (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[0].expressionNode), ast::ExpressionNode::Operation::NEGATION);
    }
#line 2572 "out/parser.cpp"
    break;

  case 136: /* factor: identifier LB expression RB  */
#line 867 "src/yacc.y"
                                {
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-3].identifierNode), (yyvsp[-1].expressionNode), ast::SpecialExpressionNode::FunctionName::ARRAY_ACCESS);
    }
#line 2580 "out/parser.cpp"
    break;

  case 137: /* factor: identifier DOT identifier  */
#line 871 "src/yacc.y"
                              {
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-2].identifierNode), (yyvsp[0].identifierNode), ast::SpecialExpressionNode::FunctionName::RECORD_ACCESS);
    }
#line 2588 "out/parser.cpp"
    break;

  case 138: /* factor: ABS LP args_list RP  */
#line 875 "src/yacc.y"
                        {
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::ABS);
    }
#line 2596 "out/parser.cpp"
    break;

  case 139: /* factor: CHR LP args_list RP  */
#line 879 "src/yacc.y"
                        {
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::CHR);
    }
#line 2604 "out/parser.cpp"
    break;

  case 140: /* factor: ODD LP args_list RP  */
#line 883 "src/yacc.y"
                        {
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::ODD);
    }
#line 2612 "out/parser.cpp"
    break;

  case 141: /* factor: ORD LP args_list RP  */
#line 887 "src/yacc.y"
                        {
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::ORD);
    }
#line 2620 "out/parser.cpp"
    break;

  case 142: /* factor: PRED LP args_list RP  */
#line 891 "src/yacc.y"
                         {
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::PRED);
    }
#line 2628 "out/parser.cpp"
    break;

  case 143: /* factor: SUCC LP args_list RP  */
#line 895 "src/yacc.y"
                         {
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::SUCC);
    }
#line 2636 "out/parser.cpp"
    break;


#line 2640 "out/parser.cpp"

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

#line 899 "src/yacc.y"


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
