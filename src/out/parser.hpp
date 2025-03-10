/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SRC_OUT_PARSER_HPP_INCLUDED
#define YY_YY_SRC_OUT_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 87 "src/yacc.y"

#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <string>

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

typedef struct Token {
  int numericalValue;
  std::string* stringValue;
} Token;

#line 88 "src/out/parser.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
#define YYTOKENTYPE
enum yytokentype {
  YYEMPTY = -2,
  YYEOF = 0,         /* "end of file"  */
  YYerror = 256,     /* error  */
  YYUNDEF = 257,     /* "invalid token"  */
  PROGRAM = 258,     /* PROGRAM  */
  FUNCTION = 259,    /* FUNCTION  */
  PROCEDURE = 260,   /* PROCEDURE  */
  CONST = 261,       /* CONST  */
  TYPE = 262,        /* TYPE  */
  VAR = 263,         /* VAR  */
  BBEGIN = 264,      /* BBEGIN  */
  END = 265,         /* END  */
  IDENT_NAME = 266,  /* IDENT_NAME  */
  INTEGER = 267,     /* INTEGER  */
  BOOLEAN = 268,     /* BOOLEAN  */
  CHAR = 269,        /* CHAR  */
  STRING = 270,      /* STRING  */
  TRUE = 271,        /* TRUE  */
  FALSE = 272,       /* FALSE  */
  MAXINT = 273,      /* MAXINT  */
  READ = 274,        /* READ  */
  READLN = 275,      /* READLN  */
  WRITE = 276,       /* WRITE  */
  WRITELN = 277,     /* WRITELN  */
  MEMORYREAD = 278,  /* MEMORYREAD  */
  MEMORYWRITE = 279, /* MEMORYWRITE  */
  STACKREAD = 280,   /* STACKREAD  */
  STACKWRITE = 281,  /* STACKWRITE  */
  ABS = 282,         /* ABS  */
  CHR = 283,         /* CHR  */
  ODD = 284,         /* ODD  */
  ORD = 285,         /* ORD  */
  PRED = 286,        /* PRED  */
  SUCC = 287,        /* SUCC  */
  TOINT = 288,       /* TOINT  */
  TOCHAR = 289,      /* TOCHAR  */
  TOBOOL = 290,      /* TOBOOL  */
  IF = 291,          /* IF  */
  THEN = 292,        /* THEN  */
  ELSE = 293,        /* ELSE  */
  REPEAT = 294,      /* REPEAT  */
  UNTIL = 295,       /* UNTIL  */
  WHILE = 296,       /* WHILE  */
  DO = 297,          /* DO  */
  CASE = 298,        /* CASE  */
  TO = 299,          /* TO  */
  DOWNTO = 300,      /* DOWNTO  */
  FOR = 301,         /* FOR  */
  EQUAL = 302,       /* EQUAL  */
  UNEQUAL = 303,     /* UNEQUAL  */
  GE = 304,          /* GE  */
  GT = 305,          /* GT  */
  LE = 306,          /* LE  */
  LT = 307,          /* LT  */
  ASSIGN = 308,      /* ASSIGN  */
  PLUS = 309,        /* PLUS  */
  MINUS = 310,       /* MINUS  */
  MUL = 311,         /* MUL  */
  DIV = 312,         /* DIV  */
  OR = 313,          /* OR  */
  AND = 314,         /* AND  */
  NOT = 315,         /* NOT  */
  MOD = 316,         /* MOD  */
  LB = 317,          /* LB  */
  RB = 318,          /* RB  */
  LP = 319,          /* LP  */
  RP = 320,          /* RP  */
  SEMICOLON = 321,   /* SEMICOLON  */
  DOT = 322,         /* DOT  */
  DOUBLEDOT = 323,   /* DOUBLEDOT  */
  COMMA = 324,       /* COMMA  */
  COLON = 325,       /* COLON  */
  INT_TYPE = 326,    /* INT_TYPE  */
  BOOL_TYPE = 327,   /* BOOL_TYPE  */
  CHAR_TYPE = 328,   /* CHAR_TYPE  */
  ARRAY = 329,       /* ARRAY  */
  OF = 330,          /* OF  */
  RECORD = 331,      /* RECORD  */
  GOTO = 332,        /* GOTO  */
  BREAK = 333,       /* BREAK  */
  CONTINUE = 334,    /* CONTINUE  */
  OTHERWISE = 335,   /* OTHERWISE  */
  ERROR = 336        /* ERROR  */
};
typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if !defined YYSTYPE && !defined YYSTYPE_IS_DECLARED
union YYSTYPE {
#line 127 "src/yacc.y"

  Token token;
  ast::ProgramNode* programNode;
  ast::RoutineNode* routineNode;
  ast::RoutineHeadNode* routineHeadNode;
  ast::RoutineDeclarationNode* routineDeclarationNode;
  std::vector<std::pair<ast::IdentifierNode*, ast::ConstantNode*>*>* constPartList;
  std::pair<ast::IdentifierNode*, ast::ConstantNode*>* constPartListElement;
  std::vector<std::pair<ast::IdentifierNode*, ast::TypeNode*>*>* typePartList;
  std::pair<ast::IdentifierNode*, ast::TypeNode*>* typePartListElement;
  std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>* varPartList;
  std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>* varPartListElement;
  std::vector<ast::RoutineDeclarationNode*>* routinePartList;
  ast::ParamsNode* paramsNode;
  std::vector<ast::ParamsGroupNode*>* paramsGroupList;
  ast::ParamsGroupNode* paramsGroupNode;
  ast::ConstantNode* constantNode;
  ast::TypeNode* typeNode;
  ast::SimpleTypeNode* simpleTypeNode;
  ast::ArrayTypeNode* arrayTypeNode;
  ast::RecordTypeNode* recordTypeNode;
  std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>* fieldDeclList;
  std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>* fieldDeclListElement;
  std::vector<ast::IdentifierNode*>* identifierList;
  ast::IdentifierNode* identifierNode;
  ast::RoutineBodyNode* routineBodyNode;
  ast::CompoundStatementNode* compoundStatementNode;
  std::vector<ast::StatementNode*>* statementNodeList;
  ast::StatementNode* statementNode;
  ast::AssignNode* assignNode;
  ast::GotoNode* gotoNode;
  ast::CaseNode* caseNode;
  ast::ForNode* forNode;
  ast::WhileNode* whileNode;
  ast::RepeatNode* repeatNode;
  ast::BreakNode* breakNode;
  ast::ContinueNode* continueNode;
  ast::IfNode* ifNode;
  ast::CallNode* callNode;
  ast::ExpressionNode* expressionNode;
  std::vector<std::pair<ast::ExpressionNode*, ast::StatementNode*>*>* caseExprList;
  std::pair<ast::ExpressionNode*, ast::StatementNode*>* caseExpr;
  ast::ArgumentsListNode* argsList;

#line 231 "src/out/parser.hpp"
};
typedef union YYSTYPE YYSTYPE;
#define YYSTYPE_IS_TRIVIAL 1
#define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

int yyparse(void);

#endif /* !YY_YY_SRC_OUT_PARSER_HPP_INCLUDED  */
