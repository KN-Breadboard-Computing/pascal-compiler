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

#ifndef YY_YY_OUT_PARSER_HPP_INCLUDED
# define YY_YY_OUT_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 51 "src/yacc.y"

    #include <iostream>
    #include <stdlib.h>
    #include <string>

    #include "../src/ast/arguments_list_node.hpp"
    #include "../src/ast/array_type_node.hpp"
    #include "../src/ast/assign_node.hpp"
    #include "../src/ast/ast_node.hpp"
    #include "../src/ast/call_node.hpp"
    #include "../src/ast/case_node.hpp"
    #include "../src/ast/compound_statement_node.hpp"
    #include "../src/ast/constant_node.hpp"
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

    typedef struct Token {
        int numericalValue;
        std::string* stringValue;
    } Token;

#line 85 "out/parser.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    PROGRAM = 258,                 /* PROGRAM  */
    FUNCTION = 259,                /* FUNCTION  */
    PROCEDURE = 260,               /* PROCEDURE  */
    CONST = 261,                   /* CONST  */
    TYPE = 262,                    /* TYPE  */
    VAR = 263,                     /* VAR  */
    BBEGIN = 264,                  /* BBEGIN  */
    END = 265,                     /* END  */
    IDENT_NAME = 266,              /* IDENT_NAME  */
    INTEGER = 267,                 /* INTEGER  */
    BOOLEAN = 268,                 /* BOOLEAN  */
    CHAR = 269,                    /* CHAR  */
    STRING = 270,                  /* STRING  */
    TRUE = 271,                    /* TRUE  */
    FALSE = 272,                   /* FALSE  */
    MAXINT = 273,                  /* MAXINT  */
    READ = 274,                    /* READ  */
    READLN = 275,                  /* READLN  */
    WRITE = 276,                   /* WRITE  */
    WRITELN = 277,                 /* WRITELN  */
    MEMORYREAD = 278,              /* MEMORYREAD  */
    MEMORYWRITE = 279,             /* MEMORYWRITE  */
    STACKREAD = 280,               /* STACKREAD  */
    STACKWRITE = 281,              /* STACKWRITE  */
    ABS = 282,                     /* ABS  */
    CHR = 283,                     /* CHR  */
    ODD = 284,                     /* ODD  */
    ORD = 285,                     /* ORD  */
    PRED = 286,                    /* PRED  */
    SUCC = 287,                    /* SUCC  */
    IF = 288,                      /* IF  */
    THEN = 289,                    /* THEN  */
    ELSE = 290,                    /* ELSE  */
    REPEAT = 291,                  /* REPEAT  */
    UNTIL = 292,                   /* UNTIL  */
    WHILE = 293,                   /* WHILE  */
    DO = 294,                      /* DO  */
    CASE = 295,                    /* CASE  */
    TO = 296,                      /* TO  */
    DOWNTO = 297,                  /* DOWNTO  */
    FOR = 298,                     /* FOR  */
    EQUAL = 299,                   /* EQUAL  */
    UNEQUAL = 300,                 /* UNEQUAL  */
    GE = 301,                      /* GE  */
    GT = 302,                      /* GT  */
    LE = 303,                      /* LE  */
    LT = 304,                      /* LT  */
    ASSIGN = 305,                  /* ASSIGN  */
    PLUS = 306,                    /* PLUS  */
    MINUS = 307,                   /* MINUS  */
    MUL = 308,                     /* MUL  */
    DIV = 309,                     /* DIV  */
    OR = 310,                      /* OR  */
    AND = 311,                     /* AND  */
    NOT = 312,                     /* NOT  */
    MOD = 313,                     /* MOD  */
    LB = 314,                      /* LB  */
    RB = 315,                      /* RB  */
    LP = 316,                      /* LP  */
    RP = 317,                      /* RP  */
    SEMICOLON = 318,               /* SEMICOLON  */
    DOT = 319,                     /* DOT  */
    DOUBLEDOT = 320,               /* DOUBLEDOT  */
    COMMA = 321,                   /* COMMA  */
    COLON = 322,                   /* COLON  */
    INT_TYPE = 323,                /* INT_TYPE  */
    UNSIGNED_TYPE = 324,           /* UNSIGNED_TYPE  */
    BOOL_TYPE = 325,               /* BOOL_TYPE  */
    CHAR_TYPE = 326,               /* CHAR_TYPE  */
    ARRAY = 327,                   /* ARRAY  */
    OF = 328,                      /* OF  */
    RECORD = 329,                  /* RECORD  */
    GOTO = 330,                    /* GOTO  */
    BREAK = 331,                   /* BREAK  */
    CONTINUE = 332,                /* CONTINUE  */
    OTHERWISE = 333,               /* OTHERWISE  */
    ERROR = 334                    /* ERROR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 88 "src/yacc.y"

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
    std::vector<std::pair<ast::AstNode*, ast::StatementNode*>*>* caseExprList;
    std::pair<ast::AstNode*, ast::StatementNode*>* caseExpr;
    ast::ArgumentsListNode* argsList;

#line 226 "out/parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_OUT_PARSER_HPP_INCLUDED  */
