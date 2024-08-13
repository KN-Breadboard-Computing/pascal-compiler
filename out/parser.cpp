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

#include "../src/ast/program_node.hpp"
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

bool nameAlreadyUsed(std::string name);
void saveType(ast::IdentifierNode* typeName, ast::TypeNode* typeDef);
void saveConstant(ast::IdentifierNode* constName, ast::ConstantNode* constDef);
void saveVariables(std::vector<ast::IdentifierNode*>* varNames, ast::TypeNode* typeDef);
void saveRoutine(ast::RoutineDeclarationNode* routineDef);

std::string getTypeString(ast::TypeNode* type);
std::string getTypeString(ast::ConstantNode::ConstantType type);

std::string getConstantString(ast::ConstantNode* constant);

bool isBasicType(const std::string& type);
bool isEnumType(const std::string& type);
bool isLeftValueCompatible(ast::ExpressionNode* expr);

bool isArrayIndexCompatible(const std::string& arrayType, ast::ExpressionNode* index);
bool isRecordFieldCompatible(const std::string& recordType, ast::IdentifierNode* field);
bool isFunctionArgumentsCompatible(const std::vector<std::pair<std::string, std::string>>& expectedArgs, const std::vector<ast::ExpressionNode*>& givenArgs);

std::string getArrayElementType(const std::string& arrayType);
std::string getRecordFieldType(const std::string& recordType, const std::string& field);

#line 120 "out/parser.cpp"

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
  YYSYMBOL_factor = 130,                   /* factor  */
  YYSYMBOL_lvalue = 131                    /* lvalue  */
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
#define YYLAST   629

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  80
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  156
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
       0,   199,   199,   210,   222,   234,   248,   258,   268,   276,
     287,   298,   309,   322,   334,   347,   360,   375,   390,   402,
     415,   428,   443,   456,   465,   475,   484,   495,   503,   513,
     521,   531,   540,   551,   561,   574,   582,   592,   601,   612,
     622,   635,   643,   651,   660,   671,   679,   687,   695,   705,
     713,   723,   732,   743,   753,   766,   774,   782,   792,   815,
     824,   835,   842,   852,   862,   870,   878,   886,   894,   902,
     910,   918,   928,   937,   948,   959,   969,   977,   988,   996,
    1005,  1017,  1026,  1036,  1044,  1052,  1060,  1068,  1076,  1084,
    1092,  1100,  1108,  1116,  1126,  1143,  1153,  1168,  1186,  1194,
    1204,  1219,  1227,  1244,  1254,  1263,  1274,  1282,  1290,  1300,
    1320,  1342,  1362,  1382,  1405,  1413,  1435,  1443,  1466,  1503,
    1535,  1572,  1606,  1615,  1626,  1641,  1656,  1671,  1686,  1701,
    1717,  1726,  1741,  1756,  1771,  1781,  1796,  1811,  1826,  1841,
    1851,  1867,  1875,  1884,  1892,  1907,  1922,  1945,  1968,  1991,
    2014,  2037,  2062,  2080,  2101,  2122,  2138
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
  "expression", "expr", "term", "factor", "lvalue", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-192)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-153)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      19,    38,    73,    -3,  -192,    66,    79,    41,    74,   132,
    -192,    66,  -192,    70,    60,  -192,  -192,  -192,  -192,    66,
      82,  -192,   190,  -192,   327,    66,  -192,   112,    66,    57,
    -192,  -192,  -192,  -192,  -192,  -192,     0,    58,  -192,    69,
      90,  -192,    98,   110,   123,   131,   133,   142,   493,  -192,
     493,   493,    66,   115,  -192,  -192,    76,  -192,   158,  -192,
    -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,    20,  -192,
     465,    66,  -192,    26,  -192,   208,   212,    57,  -192,     4,
    -192,    11,  -192,  -192,  -192,   417,   493,   493,   493,   493,
     493,   493,   493,   164,   166,   174,   175,   180,   182,   541,
     493,   493,  -192,    37,   282,    77,    99,  -192,   -34,   357,
     535,   184,   195,  -192,   493,   493,    66,  -192,   493,   493,
      66,    66,  -192,  -192,  -192,  -192,   187,    66,   183,   186,
    -192,  -192,  -192,   188,  -192,    66,   465,   198,   198,  -192,
    -192,    79,   197,    79,   199,  -192,   185,   -14,   265,     2,
      80,    83,    96,   102,   493,   493,   493,   493,   493,   493,
    -192,  -192,  -192,  -192,   440,   493,   387,   493,   493,   493,
     493,   493,   493,   216,   493,   493,   493,   493,   493,   493,
     493,   493,   387,   454,   493,   296,   103,  -192,   265,   452,
    -192,   104,    39,    92,  -192,    46,   190,  -192,    66,  -192,
     206,    13,   194,  -192,   207,  -192,   213,  -192,  -192,  -192,
     493,  -192,  -192,  -192,  -192,  -192,   114,   117,   120,   129,
     150,   151,  -192,   156,   216,    77,    77,    77,    77,    77,
      77,   387,  -192,    99,    99,    99,  -192,  -192,  -192,  -192,
     265,  -192,   387,   204,   211,    17,  -192,   580,  -192,  -192,
    -192,  -192,   215,  -192,  -192,   465,  -192,  -192,  -192,    66,
      71,  -192,   107,    39,  -192,  -192,   265,  -192,  -192,  -192,
    -192,  -192,  -192,  -192,  -192,  -192,   222,   387,   387,  -192,
    -192,   493,   493,   214,   225,   144,  -192,    13,    39,  -192,
    -192,   226,   232,   560,   571,   465,  -192,    39,  -192,  -192,
    -192,  -192,   387,   387,  -192,  -192,  -192,  -192
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
       0,   114,     0,   116,     0,     0,     0,     0,     0,    78,
       0,     0,     0,     0,    92,    93,   111,    84,    80,    82,
      83,    85,    86,    87,    88,    89,    90,    91,     0,    51,
       0,    30,    32,     0,    73,     0,     0,     7,    11,    35,
      12,    35,    42,    48,    39,   101,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   142,   152,   101,   130,   134,   139,   141,   101,
       0,     0,     0,    95,     0,     0,     0,    79,     0,     0,
       0,     0,    68,    69,    70,    71,     0,     0,     0,    54,
      57,    56,    55,    64,    31,     0,     0,    23,    23,     9,
      10,    35,    16,    35,    21,    81,     0,     0,   123,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      41,    47,   145,   144,     0,     0,   101,     0,     0,     0,
       0,     0,     0,    98,     0,     0,     0,     0,     0,     0,
       0,     0,   101,     0,     0,     0,     0,   155,    94,     0,
     156,     0,     0,     0,    60,     0,     0,    53,     0,    72,
      34,     0,     0,    22,    14,    15,    20,    19,   113,   115,
       0,   117,   118,   119,   120,   121,     0,     0,     0,     0,
       0,     0,   143,     0,    98,   128,   129,   124,   125,   126,
     127,   101,    97,   131,   132,   133,   135,   136,   138,   137,
     100,   102,   101,     0,     0,     0,   105,     0,   153,   112,
     154,    65,     0,    58,    59,     0,    66,    67,    33,     0,
       0,    26,     0,     0,    13,    18,   122,   146,   147,   148,
     149,   150,   151,   140,    96,    99,     0,   101,   101,   103,
     104,     0,     0,     0,    62,     0,    24,     0,     0,    17,
     108,     0,     0,     0,     0,     0,    61,     0,    25,    28,
     106,   107,   101,   101,    63,    27,   109,   110
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -192,  -192,     7,  -192,  -192,   202,  -192,   219,  -192,   161,
    -192,    30,  -192,  -192,   229,  -192,  -192,   308,   -11,  -192,
    -192,   298,  -132,  -192,  -192,   128,  -192,  -191,  -112,    -5,
    -192,   316,   283,   -88,   248,  -192,  -192,  -192,   111,  -192,
    -192,  -192,  -192,    89,  -192,  -192,   109,   -43,  -126,  -138,
     -60,   -22
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     7,     8,    77,    78,    79,    80,    81,   202,
     260,   261,    29,    71,    72,     9,    11,    12,   102,    20,
      25,    26,   129,   130,   193,   194,   131,   132,    73,   103,
      17,    57,    24,    58,    59,    60,    61,    62,   232,    63,
      64,    65,   245,   246,    66,    67,   147,   148,   105,   106,
     107,   108
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      13,   252,    68,     5,   200,   104,    13,   110,   111,   191,
       5,    37,    82,    14,    27,   195,   173,     5,    83,    56,
      27,   259,     1,    74,    10,   119,   146,   279,    10,    30,
     120,    31,    32,    33,    34,    35,   233,   234,   235,   162,
     163,   225,   226,   227,   228,   229,   230,   112,   209,     3,
      10,    30,   210,    31,    32,    33,    34,    35,   164,   128,
       6,    75,    76,    68,   211,   133,    74,   141,   210,    36,
     118,   185,   289,     4,   143,   188,   189,    10,   224,   119,
      56,   195,    68,    16,   120,     5,   142,    68,   144,   262,
      28,    36,   135,   136,   241,   242,   114,   299,   165,    56,
     121,   116,   253,    10,    56,    15,   305,   122,   123,   124,
     125,   187,   135,   255,    22,   190,    74,   236,   237,   238,
     239,    84,    74,   284,    23,   128,  -152,   113,   174,   175,
     199,   133,   176,   286,   287,   114,    85,   115,   240,    19,
     116,   247,   212,   275,    68,   213,   210,   285,   204,   210,
     206,    86,   177,   178,   276,   179,    70,   180,   214,    87,
      68,    56,   210,   304,   215,   249,   251,   266,   210,   210,
     135,    88,   243,   135,   288,   262,   267,    56,   244,   268,
     210,   128,   269,   210,    89,   256,   210,   133,    74,   291,
     292,   270,    90,   257,    91,   210,    74,   149,   150,   151,
     152,   153,    30,    92,    31,    32,    33,    34,    35,    68,
     135,   297,   271,   272,   306,   307,   210,   210,   273,   137,
      68,   117,   210,   138,   186,   154,    56,   155,   167,   168,
     169,   170,   171,   172,   243,   156,   157,    56,   293,   294,
     244,   158,    36,   159,   128,   184,   192,   208,   196,   197,
     133,   231,   128,   198,    74,    68,    68,   183,   133,   201,
     205,   263,   207,   216,   217,   218,   219,   220,   221,   258,
     264,   277,    56,    56,   223,   283,   265,   128,   278,   139,
      68,    68,    74,   133,   128,   290,   128,   295,   296,   300,
     133,    16,   133,    10,    39,   301,   140,    56,    56,   203,
     134,    40,    41,    42,    43,    44,    45,    46,    47,   167,
     168,   169,   170,   171,   172,    48,   166,   298,    49,    21,
      50,   254,    51,    69,    18,    52,   167,   168,   169,   170,
     171,   172,   109,   145,   280,   274,    16,    38,    10,    39,
     167,   168,   169,   170,   171,   172,    40,    41,    42,    43,
      44,    45,    46,    47,     0,     0,   248,    53,    54,    55,
      48,     0,     0,    49,     0,    50,    16,    51,    10,    39,
      52,     0,     0,     0,     0,     0,    40,    41,    42,    43,
      44,    45,    46,    47,     0,     0,     0,     0,     0,     0,
      48,     0,     0,    49,   181,    50,    16,    51,    10,    39,
      52,     0,    53,    54,    55,     0,    40,    41,    42,    43,
      44,    45,    46,    47,     0,     0,     0,     0,     0,     0,
      48,     0,     0,    49,     0,    50,    16,    51,    10,     0,
      52,     0,    53,    54,    55,     0,    40,    41,    42,    43,
      44,    45,    46,    47,     0,     0,     0,     0,     0,     0,
      48,     0,     0,    49,     0,    50,     0,    51,     0,     0,
      52,     0,    53,    54,    55,    10,    30,     0,    31,    32,
      33,    34,    35,     0,     0,     0,    10,    30,     0,    31,
      32,    33,    34,    35,   167,   168,   169,   170,   171,   172,
       0,     0,    53,    54,    55,     0,   167,   168,   169,   170,
     171,   172,   222,     0,    10,    30,    36,    31,    32,    33,
      34,    35,   250,     0,     0,     0,     0,    36,     0,     0,
      93,    94,    95,    96,    97,    98,   121,     0,     0,     0,
       0,     0,   242,   122,   123,   124,   125,   126,     0,   127,
       0,     0,     0,     0,     0,    99,     0,     0,     0,     0,
     100,     0,    10,   160,   101,    31,    32,    33,    34,   161,
       0,     0,     0,     0,     0,     0,     0,     0,    93,    94,
      95,    96,    97,    98,   182,     0,     0,     0,     0,   167,
     168,   169,   170,   171,   172,     0,     0,     0,     0,     0,
       0,     0,     0,    99,     0,     0,     0,     0,   100,   302,
       0,     0,   101,     0,   167,   168,   169,   170,   171,   172,
     303,     0,     0,     0,     0,   167,   168,   169,   170,   171,
     172,   281,   282,     0,   167,   168,   169,   170,   171,   172
};

static const yytype_int16 yycheck[] =
{
       5,   192,    24,     6,   136,    48,    11,    50,    51,   121,
       6,    22,    12,     6,    19,   127,   104,     6,    18,    24,
      25,     8,     3,    28,    11,    59,    86,    10,    11,    12,
      64,    14,    15,    16,    17,    18,   174,   175,   176,    99,
     100,   167,   168,   169,   170,   171,   172,    52,    62,    11,
      11,    12,    66,    14,    15,    16,    17,    18,   101,    70,
      63,     4,     5,    85,    62,    70,    71,    63,    66,    52,
      50,   114,   263,     0,    63,   118,   119,    11,   166,    59,
      85,   193,   104,     9,    64,     6,    79,   109,    81,   201,
       8,    52,    66,    67,   182,    78,    59,   288,    61,   104,
      61,    64,    10,    11,   109,    64,   297,    68,    69,    70,
      71,   116,    66,    67,    44,   120,   121,   177,   178,   179,
     180,    63,   127,   255,    64,   136,    50,    12,    51,    52,
     135,   136,    55,    62,    63,    59,    67,    61,   181,     7,
      64,   184,    62,   231,   166,    62,    66,   259,   141,    66,
     143,    61,    53,    54,   242,    56,    44,    58,    62,    61,
     182,   166,    66,   295,    62,    62,    62,   210,    66,    66,
      66,    61,   183,    66,    67,   287,    62,   182,   183,    62,
      66,   192,    62,    66,    61,   196,    66,   192,   193,   277,
     278,    62,    61,   198,    61,    66,   201,    88,    89,    90,
      91,    92,    12,    61,    14,    15,    16,    17,    18,   231,
      66,    67,    62,    62,   302,   303,    66,    66,    62,    11,
     242,    63,    66,    11,   115,    61,   231,    61,    44,    45,
      46,    47,    48,    49,   245,    61,    61,   242,   281,   282,
     245,    61,    52,    61,   255,    50,    59,    62,    65,    63,
     255,    35,   263,    65,   259,   277,   278,    73,   263,    61,
      63,    67,    63,   154,   155,   156,   157,   158,   159,    63,
      63,    67,   277,   278,   165,    60,    63,   288,    67,    77,
     302,   303,   287,   288,   295,    63,   297,    73,    63,    63,
     295,     9,   297,    11,    12,    63,    77,   302,   303,   138,
      71,    19,    20,    21,    22,    23,    24,    25,    26,    44,
      45,    46,    47,    48,    49,    33,    34,   287,    36,    11,
      38,   193,    40,    25,     8,    43,    44,    45,    46,    47,
      48,    49,    49,    85,   245,   224,     9,    10,    11,    12,
      44,    45,    46,    47,    48,    49,    19,    20,    21,    22,
      23,    24,    25,    26,    -1,    -1,    60,    75,    76,    77,
      33,    -1,    -1,    36,    -1,    38,     9,    40,    11,    12,
      43,    -1,    -1,    -1,    -1,    -1,    19,    20,    21,    22,
      23,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    -1,    -1,    36,    37,    38,     9,    40,    11,    12,
      43,    -1,    75,    76,    77,    -1,    19,    20,    21,    22,
      23,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    -1,    -1,    36,    -1,    38,     9,    40,    11,    -1,
      43,    -1,    75,    76,    77,    -1,    19,    20,    21,    22,
      23,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    -1,    -1,    36,    -1,    38,    -1,    40,    -1,    -1,
      43,    -1,    75,    76,    77,    11,    12,    -1,    14,    15,
      16,    17,    18,    -1,    -1,    -1,    11,    12,    -1,    14,
      15,    16,    17,    18,    44,    45,    46,    47,    48,    49,
      -1,    -1,    75,    76,    77,    -1,    44,    45,    46,    47,
      48,    49,    62,    -1,    11,    12,    52,    14,    15,    16,
      17,    18,    60,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      27,    28,    29,    30,    31,    32,    61,    -1,    -1,    -1,
      -1,    -1,    78,    68,    69,    70,    71,    72,    -1,    74,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,
      57,    -1,    11,    12,    61,    14,    15,    16,    17,    18,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    28,
      29,    30,    31,    32,    39,    -1,    -1,    -1,    -1,    44,
      45,    46,    47,    48,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    57,    39,
      -1,    -1,    61,    -1,    44,    45,    46,    47,    48,    49,
      39,    -1,    -1,    -1,    -1,    44,    45,    46,    47,    48,
      49,    41,    42,    -1,    44,    45,    46,    47,    48,    49
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
     115,   116,   117,   119,   120,   121,   124,   125,   131,   101,
      44,    93,    94,   108,   109,     4,     5,    84,    85,    86,
      87,    88,    12,    18,    63,    67,    61,    61,    61,    61,
      61,    61,    61,    27,    28,    29,    30,    31,    32,    52,
      57,    61,    98,   109,   127,   128,   129,   130,   131,   112,
     127,   127,   109,    12,    59,    61,    64,    63,    50,    59,
      64,    61,    68,    69,    70,    71,    72,    74,    98,   102,
     103,   106,   107,   109,    94,    66,    67,    11,    11,    85,
      87,    63,    82,    63,    82,   114,   130,   126,   127,   126,
     126,   126,   126,   126,    61,    61,    61,    61,    61,    61,
      12,    18,   130,   130,   127,    61,    34,    44,    45,    46,
      47,    48,    49,   113,    51,    52,    55,    53,    54,    56,
      58,    37,    39,    73,    50,   127,   126,   109,   127,   127,
     109,   108,    59,   104,   105,   108,    65,    63,    65,   109,
     102,    61,    89,    89,    82,    63,    82,    63,    62,    62,
      66,    62,    62,    62,    62,    62,   126,   126,   126,   126,
     126,   126,    62,   126,   113,   128,   128,   128,   128,   128,
     128,    35,   118,   129,   129,   129,   130,   130,   130,   130,
     127,   113,    78,    98,   109,   122,   123,   127,    60,    62,
      60,    62,   107,    10,   105,    67,    98,   109,    63,     8,
      90,    91,   108,    67,    63,    63,   127,    62,    62,    62,
      62,    62,    62,    62,   118,   113,   113,    67,    67,    10,
     123,    41,    42,    60,   102,   108,    62,    63,    67,   107,
      63,   113,   113,   127,   127,    73,    63,    67,    91,   107,
      63,    63,    39,    39,   102,   107,   113,   113
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
     114,   114,   114,   114,   115,   116,   117,   117,   118,   118,
     119,   119,   120,   121,   122,   122,   123,   123,   123,   124,
     124,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   126,   126,   127,   127,   127,   127,   127,   127,
     127,   128,   128,   128,   128,   129,   129,   129,   129,   129,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   131,   131,   131,   131,   131
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
       1,     1,     1,     1,     3,     2,     5,     4,     0,     2,
       4,     0,     4,     5,     2,     1,     4,     4,     3,     8,
       8,     1,     4,     4,     1,     4,     1,     4,     4,     4,
       4,     4,     3,     1,     3,     3,     3,     3,     3,     3,
       1,     3,     3,     3,     1,     3,     3,     3,     3,     1,
       4,     1,     1,     3,     2,     2,     4,     4,     4,     4,
       4,     4,     1,     4,     4,     3,     3
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
#line 199 "src/yacc.y"
                                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse program 1: " << (*(yyvsp[-3].token).stringValue) << std::endl;
        #endif

        std::string name{*(yyvsp[-3].token).stringValue};
        (yyvsp[-1].routineNode)->setSubType(ast::RoutineNode::SubType::MAIN);
        (yyval.programNode) = new ast::ProgramNode(std::move(name), (yyvsp[-1].routineNode));
        resultAst = (yyval.programNode);
    }
#line 1530 "out/parser.cpp"
    break;

  case 3: /* program: PROGRAM IDENT_NAME SEMICOLON routine  */
#line 210 "src/yacc.y"
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
#line 1546 "out/parser.cpp"
    break;

  case 4: /* program: PROGRAM IDENT_NAME routine DOT  */
#line 222 "src/yacc.y"
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
#line 1562 "out/parser.cpp"
    break;

  case 5: /* program: PROGRAM IDENT_NAME routine  */
#line 234 "src/yacc.y"
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
#line 1578 "out/parser.cpp"
    break;

  case 6: /* routine: routine_head routine_body  */
#line 248 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine" << std::endl;
        #endif

        (yyval.routineNode) = new ast::RoutineNode((yyvsp[-1].routineHeadNode), (yyvsp[0].routineBodyNode));
    }
#line 1590 "out/parser.cpp"
    break;

  case 7: /* routine_head: const_part type_part var_part routine_part  */
#line 258 "src/yacc.y"
                                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine head" << std::endl;
        #endif

        (yyval.routineHeadNode) = new ast::RoutineHeadNode((yyvsp[-3].constPartList), (yyvsp[-2].typePartList), (yyvsp[-1].varPartList), (yyvsp[0].routinePartList));
    }
#line 1602 "out/parser.cpp"
    break;

  case 8: /* routine_part: %empty  */
#line 268 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty routine part" << std::endl;
        #endif

        (yyval.routinePartList) = new std::vector<ast::RoutineDeclarationNode*>();
    }
#line 1614 "out/parser.cpp"
    break;

  case 9: /* routine_part: routine_part fun_decl  */
#line 276 "src/yacc.y"
                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine part with fun decl 1 " << (yyvsp[0].routineDeclarationNode)->getName() << std::endl;
        #endif

        saveRoutine((yyvsp[0].routineDeclarationNode));

        (yyval.routinePartList) = (yyvsp[-1].routinePartList);
        (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1629 "out/parser.cpp"
    break;

  case 10: /* routine_part: routine_part proc_decl  */
#line 287 "src/yacc.y"
                           {
       #ifdef YACC_DEBUG
           std::cout << "Yacc debug: Parse routine part with proc decl 1 " << (yyvsp[0].routineDeclarationNode)->getName() << std::endl;
       #endif

       saveRoutine((yyvsp[0].routineDeclarationNode));

       (yyval.routinePartList) = (yyvsp[-1].routinePartList);
       (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1644 "out/parser.cpp"
    break;

  case 11: /* routine_part: fun_decl  */
#line 298 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine part with fun decl 2 " << (yyvsp[0].routineDeclarationNode)->getName() << std::endl;
        #endif

        saveRoutine((yyvsp[0].routineDeclarationNode));

        (yyval.routinePartList) = new std::vector<ast::RoutineDeclarationNode*>();
        (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1659 "out/parser.cpp"
    break;

  case 12: /* routine_part: proc_decl  */
#line 309 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine part with proc decl 2 " << (yyvsp[0].routineDeclarationNode)->getName() << std::endl;
        #endif

        saveRoutine((yyvsp[0].routineDeclarationNode));

        (yyval.routinePartList) = new std::vector<ast::RoutineDeclarationNode*>();
        (yyval.routinePartList)->push_back((yyvsp[0].routineDeclarationNode));
    }
#line 1674 "out/parser.cpp"
    break;

  case 13: /* fun_decl: fun_head SEMICOLON routine SEMICOLON  */
#line 322 "src/yacc.y"
                                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun decl 1" << std::endl;
        #endif

        ctx->getLookupTable().popScope();

        (yyval.routineDeclarationNode) = (yyvsp[-3].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[-1].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
    }
#line 1690 "out/parser.cpp"
    break;

  case 14: /* fun_decl: fun_head SEMICOLON routine  */
#line 334 "src/yacc.y"
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
#line 1707 "out/parser.cpp"
    break;

  case 15: /* fun_decl: fun_head routine SEMICOLON  */
#line 347 "src/yacc.y"
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
#line 1724 "out/parser.cpp"
    break;

  case 16: /* fun_decl: fun_head routine  */
#line 360 "src/yacc.y"
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
#line 1741 "out/parser.cpp"
    break;

  case 17: /* fun_head: FUNCTION IDENT_NAME params COLON simple_type  */
#line 375 "src/yacc.y"
                                                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun head " << (*(yyvsp[-3].token).stringValue) << std::endl;
        #endif

        ctx->getLookupTable().pushScope(*(yyvsp[-3].token).stringValue);

        std::string name{*(yyvsp[-3].token).stringValue};
        (yyval.routineDeclarationNode) = new ast::RoutineDeclarationNode(ast::RoutineDeclarationNode::RoutineType::FUNCTION, std::move(name), (yyvsp[-2].paramsNode), (yyvsp[0].simpleTypeNode), nullptr);


    }
#line 1758 "out/parser.cpp"
    break;

  case 18: /* proc_decl: proc_head SEMICOLON routine SEMICOLON  */
#line 390 "src/yacc.y"
                                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse proc decl" << std::endl;
        #endif

        ctx->getLookupTable().popScope();

        (yyval.routineDeclarationNode) = (yyvsp[-3].routineDeclarationNode);
        (yyval.routineDeclarationNode)->setRoutine(std::unique_ptr<ast::RoutineNode>((yyvsp[-1].routineNode)));
        (yyval.routineDeclarationNode)->setRoutineType(ast::RoutineDeclarationNode::RoutineType::PROCEDURE);
    }
#line 1774 "out/parser.cpp"
    break;

  case 19: /* proc_decl: proc_head routine SEMICOLON  */
#line 402 "src/yacc.y"
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
#line 1791 "out/parser.cpp"
    break;

  case 20: /* proc_decl: proc_head SEMICOLON routine  */
#line 415 "src/yacc.y"
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
#line 1808 "out/parser.cpp"
    break;

  case 21: /* proc_decl: proc_head routine  */
#line 428 "src/yacc.y"
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
#line 1825 "out/parser.cpp"
    break;

  case 22: /* proc_head: PROCEDURE IDENT_NAME params  */
#line 443 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse proc head " << (*(yyvsp[-1].token).stringValue) << std::endl;
        #endif

        ctx->getLookupTable().pushScope(*(yyvsp[-1].token).stringValue);

        std::string name{*(yyvsp[-1].token).stringValue};
        (yyval.routineDeclarationNode) = new ast::RoutineDeclarationNode(ast::RoutineDeclarationNode::RoutineType::PROCEDURE, std::move(name), (yyvsp[0].paramsNode), nullptr, nullptr);
    }
#line 1840 "out/parser.cpp"
    break;

  case 23: /* params: %empty  */
#line 456 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty params" << std::endl;
        #endif

        std::vector<ast::ParamsGroupNode *>* emptyParamsList = new std::vector<ast::ParamsGroupNode*>();
        (yyval.paramsNode) = new ast::ParamsNode(emptyParamsList);
    }
#line 1853 "out/parser.cpp"
    break;

  case 24: /* params: LP params_decl RP  */
#line 465 "src/yacc.y"
                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params" << std::endl;
        #endif

        (yyval.paramsNode) = new ast::ParamsNode((yyvsp[-1].paramsGroupList));
    }
#line 1865 "out/parser.cpp"
    break;

  case 25: /* params_decl: params_decl SEMICOLON params_type  */
#line 475 "src/yacc.y"
                                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params decl 1" << std::endl;
        #endif

        (yyval.paramsGroupList) = (yyvsp[-2].paramsGroupList);
        (yyval.paramsGroupList)->push_back((yyvsp[0].paramsGroupNode));
    }
#line 1878 "out/parser.cpp"
    break;

  case 26: /* params_decl: params_type  */
#line 484 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params decl 2" << std::endl;
        #endif

        (yyval.paramsGroupList) = new std::vector<ast::ParamsGroupNode*>();
        (yyval.paramsGroupList)->push_back((yyvsp[0].paramsGroupNode));
    }
#line 1891 "out/parser.cpp"
    break;

  case 27: /* params_type: VAR name_list COLON simple_type  */
#line 495 "src/yacc.y"
                                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params type 1" << std::endl;
        #endif

        (yyval.paramsGroupNode) = new ast::ParamsGroupNode(ast::ParamsGroupNode::PassType::PASS_BY_REFERENCE, (yyvsp[-2].identifierList), (yyvsp[0].simpleTypeNode));
    }
#line 1903 "out/parser.cpp"
    break;

  case 28: /* params_type: name_list COLON simple_type  */
#line 503 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params type 2" << std::endl;
        #endif

        (yyval.paramsGroupNode) = new ast::ParamsGroupNode(ast::ParamsGroupNode::PassType::PASS_BY_VALUE, (yyvsp[-2].identifierList), (yyvsp[0].simpleTypeNode));
    }
#line 1915 "out/parser.cpp"
    break;

  case 29: /* var_part: %empty  */
#line 513 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty var part" << std::endl;
        #endif

        (yyval.varPartList) = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
    }
#line 1927 "out/parser.cpp"
    break;

  case 30: /* var_part: VAR var_decl_list  */
#line 521 "src/yacc.y"
                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var part" << std::endl;
        #endif

        (yyval.varPartList) = (yyvsp[0].varPartList);
    }
#line 1939 "out/parser.cpp"
    break;

  case 31: /* var_decl_list: var_decl_list var_decl  */
#line 531 "src/yacc.y"
                           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl list 1" << std::endl;
        #endif

        (yyval.varPartList) = (yyvsp[-1].varPartList);
        (yyval.varPartList)->push_back((yyvsp[0].varPartListElement));
    }
#line 1952 "out/parser.cpp"
    break;

  case 32: /* var_decl_list: var_decl  */
#line 540 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl list 2" << std::endl;
        #endif

        (yyval.varPartList) = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
        (yyval.varPartList)->push_back((yyvsp[0].varPartListElement));
    }
#line 1965 "out/parser.cpp"
    break;

  case 33: /* var_decl: name_list COLON type_decl SEMICOLON  */
#line 551 "src/yacc.y"
                                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl 1" << std::endl;
        #endif

        saveVariables((yyvsp[-3].identifierList), (yyvsp[-1].typeNode));

        (yyval.varPartListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-3].identifierList), (yyvsp[-1].typeNode));
    }
#line 1979 "out/parser.cpp"
    break;

  case 34: /* var_decl: name_list COLON type_decl  */
#line 561 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl 2" << std::endl;
        #endif

        saveVariables((yyvsp[-2].identifierList), (yyvsp[0].typeNode));

        (yyval.varPartListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-2].identifierList), (yyvsp[0].typeNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 1994 "out/parser.cpp"
    break;

  case 35: /* const_part: %empty  */
#line 574 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty const part" << std::endl;
        #endif

        (yyval.constPartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::ConstantNode*>*>();
    }
#line 2006 "out/parser.cpp"
    break;

  case 36: /* const_part: CONST const_expr_list  */
#line 582 "src/yacc.y"
                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const part" << std::endl;
        #endif

        (yyval.constPartList) = (yyvsp[0].constPartList);
    }
#line 2018 "out/parser.cpp"
    break;

  case 37: /* const_expr_list: const_expr_list const_expr  */
#line 592 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr list 1" << std::endl;
        #endif

        (yyval.constPartList) = (yyvsp[-1].constPartList);
        (yyval.constPartList)->push_back((yyvsp[0].constPartListElement));
    }
#line 2031 "out/parser.cpp"
    break;

  case 38: /* const_expr_list: const_expr  */
#line 601 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr list 2" << std::endl;
        #endif

        (yyval.constPartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::ConstantNode*>*>();
        (yyval.constPartList)->push_back((yyvsp[0].constPartListElement));
    }
#line 2044 "out/parser.cpp"
    break;

  case 39: /* const_expr: identifier EQUAL const_value SEMICOLON  */
#line 612 "src/yacc.y"
                                           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr 1" << std::endl;
        #endif

        saveConstant((yyvsp[-3].identifierNode), (yyvsp[-1].constantNode));

        (yyval.constPartListElement) = new std::pair<ast::IdentifierNode*, ast::ConstantNode*>((yyvsp[-3].identifierNode), (yyvsp[-1].constantNode));
    }
#line 2058 "out/parser.cpp"
    break;

  case 40: /* const_expr: identifier EQUAL const_value  */
#line 622 "src/yacc.y"
                                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr 2" << std::endl;
        #endif

        saveConstant((yyvsp[-2].identifierNode), (yyvsp[0].constantNode));

        (yyval.constPartListElement) = new std::pair<ast::IdentifierNode*, ast::ConstantNode*>((yyvsp[-2].identifierNode), (yyvsp[0].constantNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2073 "out/parser.cpp"
    break;

  case 41: /* const_value: INTEGER  */
#line 635 "src/yacc.y"
            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - integer `" << (yyvsp[0].token).numericalValue << "`" << std::endl;
        #endif

        (yyval.constantNode) = new ast::IntegerConstantNode((yyvsp[0].token).numericalValue);
    }
#line 2085 "out/parser.cpp"
    break;

  case 42: /* const_value: MINUS INTEGER  */
#line 643 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - signed integer `" << -(yyvsp[0].token).numericalValue << "`" << std::endl;
        #endif

        (yyval.constantNode) = new ast::IntegerConstantNode(-(yyvsp[0].token).numericalValue);
    }
#line 2097 "out/parser.cpp"
    break;

  case 43: /* const_value: CHAR  */
#line 652 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - char `" << static_cast<char>((yyvsp[0].token).numericalValue) << "`" << std::endl;
        #endif

        (yyval.constantNode) = new ast::CharConstantNode(static_cast<char>((yyvsp[0].token).numericalValue));
    }
#line 2109 "out/parser.cpp"
    break;

  case 44: /* const_value: STRING  */
#line 660 "src/yacc.y"
           {
        std::string str{*(yyvsp[0].token).stringValue};
        str = str.substr(1, str.size() - 2);

        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - string `" << str << "`" << std::endl;
        #endif

        (yyval.constantNode) = new ast::StringConstantNode(std::move(str));
    }
#line 2124 "out/parser.cpp"
    break;

  case 45: /* const_value: TRUE  */
#line 671 "src/yacc.y"
         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - true" << std::endl;
        #endif

        (yyval.constantNode) = new ast::BooleanConstantNode(true);
    }
#line 2136 "out/parser.cpp"
    break;

  case 46: /* const_value: FALSE  */
#line 679 "src/yacc.y"
          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - false" << std::endl;
        #endif

        (yyval.constantNode) = new ast::BooleanConstantNode(false);
    }
#line 2148 "out/parser.cpp"
    break;

  case 47: /* const_value: MAXINT  */
#line 687 "src/yacc.y"
           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - maxint" << std::endl;
        #endif

        (yyval.constantNode) = new ast::IntegerConstantNode(255);
    }
#line 2160 "out/parser.cpp"
    break;

  case 48: /* const_value: MINUS MAXINT  */
#line 695 "src/yacc.y"
                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - signed maxint" << std::endl;
        #endif

        (yyval.constantNode) = new ast::IntegerConstantNode(-255);
    }
#line 2172 "out/parser.cpp"
    break;

  case 49: /* type_part: %empty  */
#line 705 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty type part" << std::endl;
        #endif

        (yyval.typePartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::TypeNode*>*>();
    }
#line 2184 "out/parser.cpp"
    break;

  case 50: /* type_part: TYPE type_decl_list  */
#line 713 "src/yacc.y"
                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type part" << std::endl;
        #endif

        (yyval.typePartList) = (yyvsp[0].typePartList);
    }
#line 2196 "out/parser.cpp"
    break;

  case 51: /* type_decl_list: type_decl_list type_def  */
#line 723 "src/yacc.y"
                            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type decl list 1" << std::endl;
        #endif

        (yyval.typePartList) = (yyvsp[-1].typePartList);
        (yyval.typePartList)->push_back((yyvsp[0].typePartListElement));
    }
#line 2209 "out/parser.cpp"
    break;

  case 52: /* type_decl_list: type_def  */
#line 732 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type decl list 2" << std::endl;
        #endif

        (yyval.typePartList) = new std::vector<std::pair<ast::IdentifierNode*, ast::TypeNode*>*>();
        (yyval.typePartList)->push_back((yyvsp[0].typePartListElement));
    }
#line 2222 "out/parser.cpp"
    break;

  case 53: /* type_def: identifier EQUAL type_decl SEMICOLON  */
#line 743 "src/yacc.y"
                                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type def 1" << std::endl;
        #endif

        saveType((yyvsp[-3].identifierNode), (yyvsp[-1].typeNode));

        (yyval.typePartListElement) = new std::pair<ast::IdentifierNode*, ast::TypeNode*>((yyvsp[-3].identifierNode), (yyvsp[-1].typeNode));
    }
#line 2236 "out/parser.cpp"
    break;

  case 54: /* type_def: identifier EQUAL type_decl  */
#line 753 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type def 2" << std::endl;
        #endif

        saveType((yyvsp[-2].identifierNode), (yyvsp[0].typeNode));

        (yyval.typePartListElement) = new std::pair<ast::IdentifierNode*, ast::TypeNode*>((yyvsp[-2].identifierNode), (yyvsp[0].typeNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2251 "out/parser.cpp"
    break;

  case 55: /* type_decl: simple_type  */
#line 766 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type" << std::endl;
        #endif

        (yyval.typeNode) = (yyvsp[0].simpleTypeNode);
    }
#line 2263 "out/parser.cpp"
    break;

  case 56: /* type_decl: array_type_decl  */
#line 774 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse array type" << std::endl;
        #endif

        (yyval.typeNode) = (yyvsp[0].arrayTypeNode);
    }
#line 2275 "out/parser.cpp"
    break;

  case 57: /* type_decl: record_type_decl  */
#line 782 "src/yacc.y"
                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse record type" << std::endl;
        #endif

        (yyval.typeNode) = (yyvsp[0].recordTypeNode);
    }
#line 2287 "out/parser.cpp"
    break;

  case 58: /* record_type_decl: RECORD field_decl_list END  */
#line 792 "src/yacc.y"
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
#line 2312 "out/parser.cpp"
    break;

  case 59: /* field_decl_list: field_decl_list field_decl  */
#line 815 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl list 1" << std::endl;
        #endif

        (yyval.fieldDeclList) = (yyvsp[-1].fieldDeclList);
        (yyval.fieldDeclList)->push_back((yyvsp[0].fieldDeclListElement));
    }
#line 2325 "out/parser.cpp"
    break;

  case 60: /* field_decl_list: field_decl  */
#line 824 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl list 2" << std::endl;
        #endif

        (yyval.fieldDeclList) = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
        (yyval.fieldDeclList)->push_back((yyvsp[0].fieldDeclListElement));
    }
#line 2338 "out/parser.cpp"
    break;

  case 61: /* field_decl: name_list COLON type_decl SEMICOLON  */
#line 835 "src/yacc.y"
                                        {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl 1" << std::endl;
        #endif
        (yyval.fieldDeclListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-3].identifierList), (yyvsp[-1].typeNode));
    }
#line 2349 "out/parser.cpp"
    break;

  case 62: /* field_decl: name_list COLON type_decl  */
#line 842 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl 2" << std::endl;
        #endif
        (yyval.fieldDeclListElement) = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>((yyvsp[-2].identifierList), (yyvsp[0].typeNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2361 "out/parser.cpp"
    break;

  case 63: /* array_type_decl: ARRAY LB simple_type RB OF type_decl  */
#line 852 "src/yacc.y"
                                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse array type" << std::endl;
        #endif

        (yyval.arrayTypeNode) = new ast::ArrayTypeNode((yyvsp[-3].simpleTypeNode), (yyvsp[0].typeNode));
    }
#line 2373 "out/parser.cpp"
    break;

  case 64: /* simple_type: identifier  */
#line 862 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - identifier" << std::endl;
        #endif

        (yyval.simpleTypeNode) = new ast::RenameTypeNode((yyvsp[0].identifierNode));
    }
#line 2385 "out/parser.cpp"
    break;

  case 65: /* simple_type: LP name_list RP  */
#line 870 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - parentheses" << std::endl;
        #endif

        (yyval.simpleTypeNode) = new ast::EnumerationTypeNode((yyvsp[-1].identifierList));
    }
#line 2397 "out/parser.cpp"
    break;

  case 66: /* simple_type: const_value DOUBLEDOT const_value  */
#line 878 "src/yacc.y"
                                      {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - range 1" << std::endl;
        #endif

        (yyval.simpleTypeNode) = new ast::ConstRangeTypeNode((yyvsp[-2].constantNode), (yyvsp[0].constantNode));
    }
#line 2409 "out/parser.cpp"
    break;

  case 67: /* simple_type: identifier DOUBLEDOT identifier  */
#line 886 "src/yacc.y"
                                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - range 4" << std::endl;
        #endif

        (yyval.simpleTypeNode) = new ast::VarRangeTypeNode((yyvsp[-2].identifierNode), (yyvsp[0].identifierNode));
    }
#line 2421 "out/parser.cpp"
    break;

  case 68: /* simple_type: INT_TYPE  */
#line 894 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - int" << std::endl;
        #endif

        (yyval.simpleTypeNode) = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::INTEGER);
    }
#line 2433 "out/parser.cpp"
    break;

  case 69: /* simple_type: UNSIGNED_TYPE  */
#line 902 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - unsigned" << std::endl;
        #endif

        (yyval.simpleTypeNode) = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::UNSIGNED);
    }
#line 2445 "out/parser.cpp"
    break;

  case 70: /* simple_type: BOOL_TYPE  */
#line 910 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - bool" << std::endl;
        #endif

        (yyval.simpleTypeNode) = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::BOOLEAN);
    }
#line 2457 "out/parser.cpp"
    break;

  case 71: /* simple_type: CHAR_TYPE  */
#line 918 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - char" << std::endl;
        #endif

        (yyval.simpleTypeNode) = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::CHAR);
    }
#line 2469 "out/parser.cpp"
    break;

  case 72: /* name_list: name_list COMMA identifier  */
#line 928 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse name list 1" << std::endl;
        #endif

        (yyval.identifierList) = (yyvsp[-2].identifierList);
        (yyval.identifierList)->push_back((yyvsp[0].identifierNode));
    }
#line 2482 "out/parser.cpp"
    break;

  case 73: /* name_list: identifier  */
#line 937 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse name list 2" << std::endl;
        #endif

        (yyval.identifierList) = new std::vector<ast::IdentifierNode*>();
        (yyval.identifierList)->push_back((yyvsp[0].identifierNode));
    }
#line 2495 "out/parser.cpp"
    break;

  case 74: /* identifier: IDENT_NAME  */
#line 948 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse identifier `" << (*(yyvsp[0].token).stringValue) << "`" << std::endl;
        #endif

        std::string name{*(yyvsp[0].token).stringValue};
        (yyval.identifierNode) = new ast::IdentifierNode(std::move(name));
    }
#line 2508 "out/parser.cpp"
    break;

  case 75: /* routine_body: compound_stmt  */
#line 959 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine body" << std::endl;
        #endif

        (yyval.routineBodyNode) = new ast::RoutineBodyNode((yyvsp[0].compoundStatementNode));
    }
#line 2520 "out/parser.cpp"
    break;

  case 76: /* compound_stmt: BBEGIN stmt_list END  */
#line 969 "src/yacc.y"
                         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse compound statement 1" << std::endl;
        #endif

        (yyval.compoundStatementNode) = new ast::CompoundStatementNode((yyvsp[-1].statementNodeList));
    }
#line 2532 "out/parser.cpp"
    break;

  case 77: /* compound_stmt: BBEGIN stmt_list  */
#line 977 "src/yacc.y"
                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse compound statement 2" << std::endl;
        #endif

        (yyval.compoundStatementNode) = new ast::CompoundStatementNode((yyvsp[0].statementNodeList));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of end");
    }
#line 2545 "out/parser.cpp"
    break;

  case 78: /* stmt_list: %empty  */
#line 988 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty statement list" << std::endl;
        #endif

        (yyval.statementNodeList) = new std::vector<ast::StatementNode*>();
    }
#line 2557 "out/parser.cpp"
    break;

  case 79: /* stmt_list: stmt_list stmt SEMICOLON  */
#line 996 "src/yacc.y"
                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement list 1" << std::endl;
        #endif

        (yyval.statementNodeList) = (yyvsp[-2].statementNodeList);
        (yyval.statementNodeList)->push_back((yyvsp[-1].statementNode));
    }
#line 2570 "out/parser.cpp"
    break;

  case 80: /* stmt_list: stmt_list stmt  */
#line 1005 "src/yacc.y"
                   {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement list 2" << std::endl;
        #endif

        (yyval.statementNodeList) = (yyvsp[-1].statementNodeList);
        (yyval.statementNodeList)->push_back((yyvsp[0].statementNode));
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
#line 2584 "out/parser.cpp"
    break;

  case 81: /* stmt: INTEGER COLON no_label_stmt  */
#line 1017 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement with label " << (yyvsp[-2].token).numericalValue << std::endl;
        #endif

        (yyval.statementNode) = (yyvsp[0].statementNode);
        (yyval.statementNode)->setLabel((yyvsp[-2].token).numericalValue);
    }
#line 2597 "out/parser.cpp"
    break;

  case 82: /* stmt: no_label_stmt  */
#line 1026 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement without label" << std::endl;
        #endif

        (yyval.statementNode) = (yyvsp[0].statementNode);
    }
#line 2609 "out/parser.cpp"
    break;

  case 83: /* no_label_stmt: assign_stmt  */
#line 1036 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - assign" << std::endl;
        #endif

        (yyval.statementNode)=(yyvsp[0].assignNode);
    }
#line 2621 "out/parser.cpp"
    break;

  case 84: /* no_label_stmt: compound_stmt  */
#line 1044 "src/yacc.y"
                  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - compound" << std::endl;
        #endif

        (yyval.statementNode) = (yyvsp[0].compoundStatementNode);
    }
#line 2633 "out/parser.cpp"
    break;

  case 85: /* no_label_stmt: goto_stmt  */
#line 1052 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - goto" << std::endl;
        #endif

        (yyval.statementNode) = (yyvsp[0].gotoNode);
    }
#line 2645 "out/parser.cpp"
    break;

  case 86: /* no_label_stmt: if_stmt  */
#line 1060 "src/yacc.y"
            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - if" << std::endl;
        #endif

        (yyval.statementNode) = (yyvsp[0].ifNode);
    }
#line 2657 "out/parser.cpp"
    break;

  case 87: /* no_label_stmt: repeat_stmt  */
#line 1068 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - repeat" << std::endl;
        #endif

        (yyval.statementNode) = (yyvsp[0].repeatNode);
    }
#line 2669 "out/parser.cpp"
    break;

  case 88: /* no_label_stmt: while_stmt  */
#line 1076 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - while" << std::endl;
        #endif

        (yyval.statementNode) = (yyvsp[0].whileNode);
    }
#line 2681 "out/parser.cpp"
    break;

  case 89: /* no_label_stmt: case_stmt  */
#line 1084 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - case" << std::endl;
        #endif

        (yyval.statementNode) = (yyvsp[0].caseNode);
    }
#line 2693 "out/parser.cpp"
    break;

  case 90: /* no_label_stmt: for_stmt  */
#line 1092 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - for" << std::endl;
        #endif

        (yyval.statementNode) = (yyvsp[0].forNode);
    }
#line 2705 "out/parser.cpp"
    break;

  case 91: /* no_label_stmt: proc_stmt  */
#line 1100 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - proc" << std::endl;
        #endif

        (yyval.statementNode) = (yyvsp[0].callNode);
    }
#line 2717 "out/parser.cpp"
    break;

  case 92: /* no_label_stmt: BREAK  */
#line 1108 "src/yacc.y"
          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - break" << std::endl;
        #endif

        (yyval.statementNode) = new ast::BreakNode();
    }
#line 2729 "out/parser.cpp"
    break;

  case 93: /* no_label_stmt: CONTINUE  */
#line 1116 "src/yacc.y"
             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - continue" << std::endl;
        #endif

        (yyval.statementNode) = new ast::ContinueNode();
    }
#line 2741 "out/parser.cpp"
    break;

  case 94: /* assign_stmt: lvalue ASSIGN expression  */
#line 1126 "src/yacc.y"
                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse assign statement" << std::endl;
        #endif

        if((yyvsp[-2].expressionNode)->getInferredType() != (yyvsp[0].expressionNode)->getInferredType()) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", both sides should be equal type");
            fatalError = true;
            YYERROR;
        }
        else {
            (yyval.assignNode) = new ast::AssignNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode));
        }
    }
#line 2760 "out/parser.cpp"
    break;

  case 95: /* goto_stmt: GOTO INTEGER  */
#line 1143 "src/yacc.y"
                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse goto statement to " << (yyvsp[0].token).numericalValue << std::endl;
        #endif

        (yyval.gotoNode) = new ast::GotoNode((yyvsp[0].token).numericalValue);
    }
#line 2772 "out/parser.cpp"
    break;

  case 96: /* if_stmt: IF expression THEN stmt else_clause  */
#line 1153 "src/yacc.y"
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
#line 2791 "out/parser.cpp"
    break;

  case 97: /* if_stmt: IF expression stmt else_clause  */
#line 1168 "src/yacc.y"
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
#line 2811 "out/parser.cpp"
    break;

  case 98: /* else_clause: %empty  */
#line 1186 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty else clause" << std::endl;
        #endif

        (yyval.ifNode) = new ast::IfNode(nullptr, nullptr);
    }
#line 2823 "out/parser.cpp"
    break;

  case 99: /* else_clause: ELSE stmt  */
#line 1194 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse else clause" << std::endl;
        #endif

        (yyval.ifNode) = new ast::IfNode(nullptr, nullptr, (yyvsp[0].statementNode));
    }
#line 2835 "out/parser.cpp"
    break;

  case 100: /* repeat_stmt: REPEAT stmt_list UNTIL expression  */
#line 1204 "src/yacc.y"
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
#line 2854 "out/parser.cpp"
    break;

  case 101: /* repeat_stmt: %empty  */
#line 1219 "src/yacc.y"
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty repeat statement" << std::endl;
        #endif
    }
#line 2864 "out/parser.cpp"
    break;

  case 102: /* while_stmt: WHILE expression DO stmt  */
#line 1227 "src/yacc.y"
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
#line 2883 "out/parser.cpp"
    break;

  case 103: /* case_stmt: CASE expression OF case_expr_list END  */
#line 1244 "src/yacc.y"
                                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case statement" << std::endl;
        #endif

        (yyval.caseNode) = new ast::CaseNode((yyvsp[-3].expressionNode), (yyvsp[-1].caseExprList));
    }
#line 2895 "out/parser.cpp"
    break;

  case 104: /* case_expr_list: case_expr_list case_expr  */
#line 1254 "src/yacc.y"
                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr list 1" << std::endl;
        #endif

        (yyval.caseExprList) = (yyvsp[-1].caseExprList);
        (yyval.caseExprList)->push_back((yyvsp[0].caseExpr));
    }
#line 2908 "out/parser.cpp"
    break;

  case 105: /* case_expr_list: case_expr  */
#line 1263 "src/yacc.y"
              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr list 2" << std::endl;
        #endif

        (yyval.caseExprList) = new std::vector<std::pair<ast::AstNode*, ast::StatementNode*>*>();
        (yyval.caseExprList)->push_back((yyvsp[0].caseExpr));
    }
#line 2921 "out/parser.cpp"
    break;

  case 106: /* case_expr: const_value COLON stmt SEMICOLON  */
#line 1274 "src/yacc.y"
                                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr 1" << std::endl;
        #endif

        (yyval.caseExpr) = new std::pair<ast::AstNode*, ast::StatementNode*>((yyvsp[-3].constantNode), (yyvsp[-1].statementNode));
    }
#line 2933 "out/parser.cpp"
    break;

  case 107: /* case_expr: identifier COLON stmt SEMICOLON  */
#line 1282 "src/yacc.y"
                                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr 2" << std::endl;
        #endif

        (yyval.caseExpr) = new std::pair<ast::AstNode*, ast::StatementNode*>((yyvsp[-3].identifierNode), (yyvsp[-1].statementNode));
    }
#line 2945 "out/parser.cpp"
    break;

  case 108: /* case_expr: OTHERWISE stmt SEMICOLON  */
#line 1290 "src/yacc.y"
                             {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr 3" << std::endl;
        #endif

        (yyval.caseExpr) = new std::pair<ast::AstNode*, ast::StatementNode*>(nullptr, (yyvsp[-1].statementNode));
    }
#line 2957 "out/parser.cpp"
    break;

  case 109: /* for_stmt: FOR identifier ASSIGN expression TO expression DO stmt  */
#line 1300 "src/yacc.y"
                                                           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse for statement 1" << std::endl;
        #endif

        if((yyvsp[-4].expressionNode)->getInferredType() != (yyvsp[-2].expressionNode)->getInferredType()) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", for begin and end values must be the same type");
            fatalError = true;
            YYERROR;
        }
        else if(!isBasicType((yyvsp[-4].expressionNode)->getInferredType()) && !isEnumType((yyvsp[-4].expressionNode)->getInferredType())) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", for begin and end values must be integer, char, boolean or enum type");
            fatalError = true;
            YYERROR;
        }
        else {
            (yyval.forNode) = new ast::ForNode((yyvsp[-6].identifierNode), (yyvsp[-4].expressionNode), (yyvsp[-2].expressionNode), (yyvsp[0].statementNode), ast::ForNode::Direction::INCREMENT);
        }
    }
#line 2981 "out/parser.cpp"
    break;

  case 110: /* for_stmt: FOR identifier ASSIGN expression DOWNTO expression DO stmt  */
#line 1320 "src/yacc.y"
                                                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse for statement 2" << std::endl;
        #endif

        if((yyvsp[-4].expressionNode)->getInferredType() != (yyvsp[-2].expressionNode)->getInferredType()) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", for begin and end values must be the same type");
            fatalError = true;
            YYERROR;
        }
        else if(!isBasicType((yyvsp[-4].expressionNode)->getInferredType()) && !isEnumType((yyvsp[-4].expressionNode)->getInferredType())) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", for begin and end values must be integer, char, boolean or enum type");
            fatalError = true;
            YYERROR;
        }
        else {
            (yyval.forNode) = new ast::ForNode((yyvsp[-6].identifierNode), (yyvsp[-4].expressionNode), (yyvsp[-2].expressionNode), (yyvsp[0].statementNode), ast::ForNode::Direction::DECREMENT);
        }
    }
#line 3005 "out/parser.cpp"
    break;

  case 111: /* proc_stmt: identifier  */
#line 1342 "src/yacc.y"
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
#line 3029 "out/parser.cpp"
    break;

  case 112: /* proc_stmt: identifier LP args_list RP  */
#line 1362 "src/yacc.y"
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
#line 3053 "out/parser.cpp"
    break;

  case 113: /* proc_stmt: READ LP factor RP  */
#line 1382 "src/yacc.y"
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
#line 3079 "out/parser.cpp"
    break;

  case 114: /* proc_stmt: READLN  */
#line 1405 "src/yacc.y"
           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse readln statement" << std::endl;
        #endif

        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::READLN, nullptr);
    }
#line 3091 "out/parser.cpp"
    break;

  case 115: /* proc_stmt: WRITE LP args_list RP  */
#line 1413 "src/yacc.y"
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
#line 3117 "out/parser.cpp"
    break;

  case 116: /* proc_stmt: WRITELN  */
#line 1435 "src/yacc.y"
            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse writeln statement" << std::endl;
        #endif

        (yyval.callNode) = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITELN, nullptr);
    }
#line 3129 "out/parser.cpp"
    break;

  case 117: /* proc_stmt: WRITELN LP args_list RP  */
#line 1443 "src/yacc.y"
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
#line 3156 "out/parser.cpp"
    break;

  case 118: /* proc_stmt: MEMORYREAD LP args_list RP  */
#line 1466 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse memory read statement" << std::endl;
        #endif

        if((yyvsp[-1].argsList)->getArguments().size() == 3) {
            if((yyvsp[-1].argsList)->getArguments().at(0)->getInferredType() != "integer" && (yyvsp[-1].argsList)->getArguments().at(0)->getInferredType() != "unsigned") {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory read - first argument should be integer");
                fatalError = true;
                YYERROR;
            }
            else if((yyvsp[-1].argsList)->getArguments().at(1)->getInferredType() != "integer" && (yyvsp[-1].argsList)->getArguments().at(1)->getInferredType() != "unsigned") {
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
#line 3197 "out/parser.cpp"
    break;

  case 119: /* proc_stmt: MEMORYWRITE LP args_list RP  */
#line 1503 "src/yacc.y"
                                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse memory write statement" << std::endl;
        #endif

        if((yyvsp[-1].argsList)->getArguments().size() == 3) {
            if((yyvsp[-1].argsList)->getArguments().at(0)->getInferredType() != "integer" && (yyvsp[-1].argsList)->getArguments().at(0)->getInferredType() != "unsigned") {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory write - first argument should be integer");
                fatalError = true;
                YYERROR;
            }
            else if((yyvsp[-1].argsList)->getArguments().at(1)->getInferredType() != "integer" && (yyvsp[-1].argsList)->getArguments().at(1)->getInferredType() != "unsigned") {
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
#line 3233 "out/parser.cpp"
    break;

  case 120: /* proc_stmt: STACKREAD LP args_list RP  */
#line 1535 "src/yacc.y"
                              {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse stack read statement" << std::endl;
        #endif

        if((yyvsp[-1].argsList)->getArguments().size() == 3) {
            if((yyvsp[-1].argsList)->getArguments().at(0)->getInferredType() != "integer" && (yyvsp[-1].argsList)->getArguments().at(0)->getInferredType() != "unsigned") {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack read - first argument should be integer");
                fatalError = true;
                YYERROR;
            }
            else if((yyvsp[-1].argsList)->getArguments().at(1)->getInferredType() != "integer" && (yyvsp[-1].argsList)->getArguments().at(1)->getInferredType() != "unsigned") {
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
#line 3274 "out/parser.cpp"
    break;

  case 121: /* proc_stmt: STACKWRITE LP args_list RP  */
#line 1572 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse stack write statement" << std::endl;
        #endif

        if((yyvsp[-1].argsList)->getArguments().size() == 3) {
            if((yyvsp[-1].argsList)->getArguments().at(0)->getInferredType() != "integer" && (yyvsp[-1].argsList)->getArguments().at(0)->getInferredType() != "unsigned") {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack write - first argument should be integer");
                fatalError = true;
                YYERROR;
            }
            else if((yyvsp[-1].argsList)->getArguments().at(1)->getInferredType() != "integer" && (yyvsp[-1].argsList)->getArguments().at(1)->getInferredType() != "unsigned") {
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
#line 3310 "out/parser.cpp"
    break;

  case 122: /* args_list: args_list COMMA expression  */
#line 1606 "src/yacc.y"
                               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse args list 1" << std::endl;
        #endif

        (yyval.argsList) = (yyvsp[-2].argsList);
        (yyval.argsList)->addArgument((yyvsp[0].expressionNode));
    }
#line 3323 "out/parser.cpp"
    break;

  case 123: /* args_list: expression  */
#line 1615 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse args list 2" << std::endl;
        #endif

        (yyval.argsList) = new ast::ArgumentsListNode();
        (yyval.argsList)->addArgument((yyvsp[0].expressionNode));
    }
#line 3336 "out/parser.cpp"
    break;

  case 124: /* expression: expression GE expr  */
#line 1626 "src/yacc.y"
                       {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with greater or equal" << std::endl;
        #endif

        if((yyvsp[-2].expressionNode)->getInferredType() == (yyvsp[0].expressionNode)->getInferredType() && isBasicType((yyvsp[-2].expressionNode)->getInferredType())) {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::GREATER_EQUAL, (yyvsp[-2].expressionNode)->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for greater or equal - matching types(integer, char, boolean) expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3355 "out/parser.cpp"
    break;

  case 125: /* expression: expression GT expr  */
#line 1641 "src/yacc.y"
                       {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with greater" << std::endl;
        #endif

        if((yyvsp[-2].expressionNode)->getInferredType() == (yyvsp[0].expressionNode)->getInferredType() && isBasicType((yyvsp[-2].expressionNode)->getInferredType())) {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::GREATER, (yyvsp[-2].expressionNode)->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for greater - matching types(integer, char, boolean) expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3374 "out/parser.cpp"
    break;

  case 126: /* expression: expression LE expr  */
#line 1656 "src/yacc.y"
                       {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with less or equal" << std::endl;
        #endif

        if((yyvsp[-2].expressionNode)->getInferredType() == (yyvsp[0].expressionNode)->getInferredType() && isBasicType((yyvsp[-2].expressionNode)->getInferredType())) {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::LESS_EQUAL, (yyvsp[-2].expressionNode)->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for less or equal - matching types(integer, char, boolean) expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3393 "out/parser.cpp"
    break;

  case 127: /* expression: expression LT expr  */
#line 1671 "src/yacc.y"
                       {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with less" << std::endl;
        #endif

        if((yyvsp[-2].expressionNode)->getInferredType() == (yyvsp[0].expressionNode)->getInferredType() && isBasicType((yyvsp[-2].expressionNode)->getInferredType())) {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::LESS, (yyvsp[-2].expressionNode)->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for less - matching types(integer, char, boolean) expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3412 "out/parser.cpp"
    break;

  case 128: /* expression: expression EQUAL expr  */
#line 1686 "src/yacc.y"
                          {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with equal" << std::endl;
        #endif

        if((yyvsp[-2].expressionNode)->getInferredType() == (yyvsp[0].expressionNode)->getInferredType() && isBasicType((yyvsp[-2].expressionNode)->getInferredType())) {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::EQUAL, (yyvsp[-2].expressionNode)->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for equal - matching types(integer, char, boolean) expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3431 "out/parser.cpp"
    break;

  case 129: /* expression: expression UNEQUAL expr  */
#line 1701 "src/yacc.y"
                            {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with not equal" << std::endl;
        #endif

        if((yyvsp[-2].expressionNode)->getInferredType() == (yyvsp[0].expressionNode)->getInferredType() && isBasicType((yyvsp[-2].expressionNode)->getInferredType())) {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::NOT_EQUAL, (yyvsp[-2].expressionNode)->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for not equal - matching types(integer, char, boolean) expected");
            fatalError = true;
            YYERROR;
        }

    }
#line 3451 "out/parser.cpp"
    break;

  case 130: /* expression: expr  */
#line 1717 "src/yacc.y"
         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple expression" << std::endl;
        #endif
        (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 3462 "out/parser.cpp"
    break;

  case 131: /* expr: expr PLUS term  */
#line 1726 "src/yacc.y"
                   {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with addition" << std::endl;
        #endif

        if(((yyvsp[-2].expressionNode)->getInferredType() == "integer" || (yyvsp[-2].expressionNode)->getInferredType() == "unsigned") && ((yyvsp[0].expressionNode)->getInferredType() == "integer" || (yyvsp[0].expressionNode)->getInferredType() == "unsigned")) {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::ADDITION, (yyvsp[-2].expressionNode)->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for addition - integer expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3481 "out/parser.cpp"
    break;

  case 132: /* expr: expr MINUS term  */
#line 1741 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with subtraction" << std::endl;
        #endif

        if(((yyvsp[-2].expressionNode)->getInferredType() == "integer" || (yyvsp[-2].expressionNode)->getInferredType() == "unsigned") && ((yyvsp[0].expressionNode)->getInferredType() == "integer" || (yyvsp[0].expressionNode)->getInferredType() == "unsigned")) {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::SUBTRACTION, (yyvsp[-2].expressionNode)->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for subtraction - integer expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3500 "out/parser.cpp"
    break;

  case 133: /* expr: expr OR term  */
#line 1756 "src/yacc.y"
                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with or" << std::endl;
        #endif

        if((yyvsp[-2].expressionNode)->getInferredType() == "boolean" && (yyvsp[0].expressionNode)->getInferredType() == "boolean") {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::OR, (yyvsp[-2].expressionNode)->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for or - boolean expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3519 "out/parser.cpp"
    break;

  case 134: /* expr: term  */
#line 1771 "src/yacc.y"
         {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple term" << std::endl;
        #endif

        (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 3531 "out/parser.cpp"
    break;

  case 135: /* term: term MUL factor  */
#line 1781 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with multiplication" << std::endl;
        #endif

        if(((yyvsp[-2].expressionNode)->getInferredType() == "integer" || (yyvsp[-2].expressionNode)->getInferredType() == "unsigned") && ((yyvsp[0].expressionNode)->getInferredType() == "integer" || (yyvsp[0].expressionNode)->getInferredType() == "unsigned")) {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::MULTIPLICATION, (yyvsp[-2].expressionNode)->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for mul - integer expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3550 "out/parser.cpp"
    break;

  case 136: /* term: term DIV factor  */
#line 1796 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with division" << std::endl;
        #endif

        if(((yyvsp[-2].expressionNode)->getInferredType() == "integer" || (yyvsp[-2].expressionNode)->getInferredType() == "unsigned") && ((yyvsp[0].expressionNode)->getInferredType() == "integer" || (yyvsp[0].expressionNode)->getInferredType() == "unsigned")) {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::DIVISION, (yyvsp[-2].expressionNode)->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for div - integer expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3569 "out/parser.cpp"
    break;

  case 137: /* term: term MOD factor  */
#line 1811 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with modulus" << std::endl;
        #endif

        if(((yyvsp[-2].expressionNode)->getInferredType() == "integer" || (yyvsp[-2].expressionNode)->getInferredType() == "unsigned") && ((yyvsp[0].expressionNode)->getInferredType() == "integer" || (yyvsp[0].expressionNode)->getInferredType() == "unsigned")) {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::MODULUS, (yyvsp[-2].expressionNode)->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for mod - integer expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3588 "out/parser.cpp"
    break;

  case 138: /* term: term AND factor  */
#line 1826 "src/yacc.y"
                    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with and" << std::endl;
        #endif

        if((yyvsp[-2].expressionNode)->getInferredType() == "boolean" && (yyvsp[0].expressionNode)->getInferredType() == "boolean") {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[-2].expressionNode), (yyvsp[0].expressionNode), ast::ExpressionNode::Operation::AND, (yyvsp[-2].expressionNode)->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for and - boolean expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3607 "out/parser.cpp"
    break;

  case 139: /* term: factor  */
#line 1841 "src/yacc.y"
           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple factor" << std::endl;
        #endif

        (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 3619 "out/parser.cpp"
    break;

  case 140: /* factor: identifier LP args_list RP  */
#line 1851 "src/yacc.y"
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
#line 3638 "out/parser.cpp"
    break;

  case 141: /* factor: lvalue  */
#line 1867 "src/yacc.y"
           {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - lvalue" << std::endl;
        #endif

        (yyval.expressionNode) = (yyvsp[0].expressionNode);
    }
#line 3650 "out/parser.cpp"
    break;

  case 142: /* factor: const_value  */
#line 1875 "src/yacc.y"
                {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - const value" << std::endl;
        #endif

        ast::ConstantNode* constant = dynamic_cast<ast::ConstantNode*>((yyvsp[0].constantNode));
        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[0].constantNode), ast::SpecialExpressionNode::FunctionName::CONST, getTypeString(constant->getConstantType()));
    }
#line 3663 "out/parser.cpp"
    break;

  case 143: /* factor: LP expression RP  */
#line 1884 "src/yacc.y"
                     {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - parentheses" << std::endl;
        #endif

        (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].expressionNode), ast::SpecialExpressionNode::FunctionName::PARENTHESIS, (yyvsp[-1].expressionNode)->getInferredType());
    }
#line 3675 "out/parser.cpp"
    break;

  case 144: /* factor: NOT factor  */
#line 1892 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - not" << std::endl;
        #endif

        if((yyvsp[0].expressionNode)->getInferredType() == "boolean") {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[0].expressionNode), ast::ExpressionNode::Operation::NEGATION, (yyvsp[0].expressionNode)->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for not - boolean expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3694 "out/parser.cpp"
    break;

  case 145: /* factor: MINUS factor  */
#line 1907 "src/yacc.y"
                 {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - negation" << std::endl;
        #endif

        if((yyvsp[0].expressionNode)->getInferredType() == "integer" || (yyvsp[0].expressionNode)->getInferredType() == "unsigned") {
            (yyval.expressionNode) = new ast::ExpressionNode((yyvsp[0].expressionNode), ast::ExpressionNode::Operation::NEGATION, (yyvsp[0].expressionNode)->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for negation - integer expected");
            fatalError = true;
            YYERROR;
        }
    }
#line 3713 "out/parser.cpp"
    break;

  case 146: /* factor: ABS LP args_list RP  */
#line 1922 "src/yacc.y"
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
            if(arg->getInferredType() == "integer" || arg->getInferredType() == "unsigned") {
                (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::ABS, "unsigned");
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for abs - integer expected");
                fatalError = true;
                YYERROR;
            }
        }
    }
#line 3740 "out/parser.cpp"
    break;

  case 147: /* factor: CHR LP args_list RP  */
#line 1945 "src/yacc.y"
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
            if(arg->getInferredType() == "integer" || arg->getInferredType() == "unsigned") {
                (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::CHR, "char");
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for chr - integer expected");
                fatalError = true;
                YYERROR;
            }
        }
    }
#line 3767 "out/parser.cpp"
    break;

  case 148: /* factor: ODD LP args_list RP  */
#line 1968 "src/yacc.y"
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
            if(arg->getInferredType() == "integer" || arg->getInferredType() == "unsigned") {
                (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::ODD, "boolean");
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for odd - integer expected");
                fatalError = true;
                YYERROR;
            }
        }
    }
#line 3794 "out/parser.cpp"
    break;

  case 149: /* factor: ORD LP args_list RP  */
#line 1991 "src/yacc.y"
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
                (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::ORD, "unsigned");
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for ord - char expected");
                fatalError = true;
                YYERROR;
            }
        }
    }
#line 3821 "out/parser.cpp"
    break;

  case 150: /* factor: PRED LP args_list RP  */
#line 2014 "src/yacc.y"
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
            if(arg->getInferredType() == "integer" || arg->getInferredType() == "unsigned" || arg->getInferredType() == "char") {
                (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::PRED, arg->getInferredType());
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for pred - integer or char expected");
                fatalError = true;
                YYERROR;
            }
        }
    }
#line 3848 "out/parser.cpp"
    break;

  case 151: /* factor: SUCC LP args_list RP  */
#line 2037 "src/yacc.y"
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
            if(arg->getInferredType() == "integer" || arg->getInferredType() == "unsigned" || arg->getInferredType() == "char") {
                (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[-1].argsList), ast::SpecialExpressionNode::FunctionName::SUCC, arg->getInferredType());
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for succ - integer or char expected");
                fatalError = true;
                YYERROR;
            }
        }
    }
#line 3875 "out/parser.cpp"
    break;

  case 152: /* lvalue: identifier  */
#line 2062 "src/yacc.y"
               {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse lvalue - variable" << std::endl;
        #endif

        if(ctx->getLookupTable().isVariableDefined((yyvsp[0].identifierNode)->getName(), "")) {
            (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[0].identifierNode), ast::SpecialExpressionNode::FunctionName::VARIABLE, ctx->getLookupTable().getVariable((yyvsp[0].identifierNode)->getName(), "").type);
        }
        else if(isEnumType((yyvsp[0].identifierNode)->getName())) {
            (yyval.expressionNode) = new ast::SpecialExpressionNode((yyvsp[0].identifierNode), ast::SpecialExpressionNode::FunctionName::ENUM_ELEMENT, (yyvsp[0].identifierNode)->getName());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", variable " + (yyvsp[0].identifierNode)->getName() + " is not defined");
            fatalError = true;
            YYERROR;
        }
    }
#line 3897 "out/parser.cpp"
    break;

  case 153: /* lvalue: identifier LB expression RB  */
#line 2080 "src/yacc.y"
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
#line 3922 "out/parser.cpp"
    break;

  case 154: /* lvalue: lvalue LB expression RB  */
#line 2101 "src/yacc.y"
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
#line 3947 "out/parser.cpp"
    break;

  case 155: /* lvalue: identifier DOT identifier  */
#line 2122 "src/yacc.y"
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
#line 3967 "out/parser.cpp"
    break;

  case 156: /* lvalue: lvalue DOT identifier  */
#line 2138 "src/yacc.y"
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
#line 3987 "out/parser.cpp"
    break;


#line 3991 "out/parser.cpp"

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

#line 2153 "src/yacc.y"


void yyerror(const char *s) {
    std::cerr << "Error: " << s << " at line " << linesCounter << std::endl;
    fatalError = true;
}

bool parse(const std::string& inputFileName, std::vector<std::string>& errors, std::unique_ptr<ast::ProgramNode>& program) {
    yyin = fopen(inputFileName.c_str(), "r");

    if(yyin == nullptr) {
        errors.push_back("Cannot open file " + inputFileName);
        return false;
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
                    return "unspecified";
                }
                else if(properEnums.size() > 1) {
                    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + lb + " and " + ub + " are in more than one enum");
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

        return "array@@" + rangeTypeName + "@" + elementTypeName + "@@";
    }
    else if(type->getTypeType() == ast::TypeNode::TypeType::RECORD) {
        auto* recordType = dynamic_cast<ast::RecordTypeNode*>(type);

        std::string mergedRecord = "record"  "$$";
        for(auto& field : *recordType->getFields()) {
            for(auto& identifier : *field->first) {
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
    return type == "integer" || type == "unsigned" || type == "boolean" || type == "char";
}

bool isEnumType(const std::string& type) {
    const std::vector<LookupTable::TypeInfo>& types = ctx->getLookupTable().getTypes(
        [&](const std::string&, const LookupTable::TypeInfo& tf) {
        return tf.alive && tf.type.find("enum%") == 0 && tf.type.find("%" + type + "%") != std::string::npos;
    });

    return !types.empty();
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

    if(arrayElementType == "integer" || arrayElementType == "unsigned") {
        if(index->getInferredType() == "integer" || index->getInferredType() == "unsigned") {
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
        size_t index;
        for(index = 11; index < arrayElementType.size(); index++) {
            if(arrayElementType[index] == '.') {
                break;
            }
            begin += arrayElementType[index];
        }

        for(index+=2; index < arrayElementType.size(); index++) {
            end += arrayElementType[index];
        }

        std::cout << "Begin: " << begin << std::endl;
        std::cout << "End: " << end << std::endl;
        return false;
    }
    else if(arrayElementType.substr(0, 9) == "enumrange") {
        std::string enumName;
        size_t index;
        for(index = 10; index < arrayElementType.size(); index++) {
            if(arrayElementType[index] == '%') {
                break;
            }
            enumName += arrayElementType[index];
        }

        std::cout << "Enum: " << enumName << std::endl;

        return false;
    }
    else if(arrayElementType.substr(0, 4) == "enum") {
        return false;
    }
    else {
        return false;
    }
}

bool isRecordFieldCompatible(const std::string& recordType, ast::IdentifierNode* field) {
    const std::string& fieldName = field->getName();
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

bool isFunctionArgumentsCompatible(const std::vector<std::pair<std::string, std::string>>& expectedArgs, const std::vector<ast::ExpressionNode*>& givenArgs) {
    if(expectedArgs.size() != givenArgs.size()) {
        return false;
    }

    for(size_t i = 0; i < expectedArgs.size(); i++) {
        if(expectedArgs[i].second != givenArgs[i]->getInferredType()) {
            return false;
        }
    }

    return true;
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
    std::size_t it = recordType.find(field) + field.size() + 2;
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
