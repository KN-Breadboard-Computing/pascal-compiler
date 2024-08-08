%{
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

bool isIntegerCompatible(ast::ExpressionNode* expr);
bool isCharCompatible(ast::ExpressionNode* expr);
bool isBooleanCompatible(ast::ExpressionNode* expr);
bool isVariableRecordFieldArrayElementCompatible(ast::ExpressionNode* expr);
%}

%code requires
{
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
}

%union
{
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
}

%start program

%token PROGRAM FUNCTION PROCEDURE CONST TYPE VAR BBEGIN END
%token IDENT_NAME INTEGER BOOLEAN CHAR STRING
%token TRUE FALSE MAXINT
%token READ READLN WRITE WRITELN MEMORYREAD MEMORYWRITE STACKREAD STACKWRITE ABS CHR ODD ORD PRED SUCC
%token IF THEN ELSE REPEAT UNTIL WHILE DO CASE TO DOWNTO FOR
%token EQUAL UNEQUAL GE GT LE LT ASSIGN PLUS MINUS MUL DIV OR AND NOT MOD
%token LB RB LP RP SEMICOLON DOT DOUBLEDOT COMMA COLON
%token INT_TYPE UNSIGNED_TYPE BOOL_TYPE CHAR_TYPE
%token ARRAY OF RECORD GOTO BREAK CONTINUE OTHERWISE
%token ERROR

%type <token> PROGRAM FUNCTION PROCEDURE CONST TYPE VAR BBEGIN END
%type <token> IDENT_NAME INTEGER BOOLEAN CHAR STRING
%type <token> TRUE FALSE MAXINT
%type <token> READ READLN WRITE WRITELN MEMORYREAD MEMORYWRITE STACKREAD STACKWRITE ABS CHR ODD ORD PRED SUCC
%type <token> IF THEN ELSE REPEAT UNTIL WHILE DO CASE TO DOWNTO FOR
%type <token> EQUAL UNEQUAL GE GT LE LT ASSIGN PLUS MINUS MUL DIV OR AND NOT MOD
%type <token> LB RB LP RP SEMICOLON DOT DOUBLEDOT COMMA COLON
%type <token> INT_TYPE UNSIGNED_TYPE BOOL_TYPE CHAR_TYPE
%type <token> ARRAY OF RECORD GOTO BREAK CONTINUE
%type <token> ERROR

%type <programNode> program
%type <routineNode> routine
%type <constPartList> const_part const_expr_list
%type <constPartListElement> const_expr
%type <constantNode> const_value
%type <typeNode> type_decl
%type <typePartList> type_part type_decl_list
%type <typePartListElement> type_def
%type <varPartList> var_part var_decl_list
%type <varPartListElement> var_decl
%type <routinePartList> routine_part
%type <routineHeadNode> routine_head
%type <routineDeclarationNode> fun_decl fun_head proc_decl proc_head
%type <paramsNode> params
%type <paramsGroupList> params_decl
%type <paramsGroupNode> params_type
%type <simpleTypeNode> simple_type
%type <arrayTypeNode> array_type_decl
%type <recordTypeNode> record_type_decl
%type <fieldDeclList> field_decl_list
%type <fieldDeclListElement> field_decl
%type <identifierList> name_list
%type <identifierNode> identifier
%type <routineBodyNode> routine_body
%type <compoundStatementNode> compound_stmt
%type <statementNodeList> stmt_list
%type <statementNode> stmt no_label_stmt
%type <assignNode> assign_stmt
%type <gotoNode> goto_stmt
%type <caseNode> case_stmt
%type <forNode> for_stmt
%type <whileNode> while_stmt
%type <repeatNode> repeat_stmt
%type <ifNode> if_stmt else_clause
%type <callNode> proc_stmt
%type <expressionNode> expression expr term factor
%type <caseExprList> case_expr_list
%type <caseExpr> case_expr
%type <argsList> args_list
%%

program :
    PROGRAM IDENT_NAME SEMICOLON routine DOT {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse program 1: " << (*$2.stringValue) << std::endl;
        #endif

        std::string name{*$2.stringValue};
        $4->setSubType(ast::RoutineNode::SubType::MAIN);
        $$ = new ast::ProgramNode(std::move(name), $4);
        resultAst = $$;
    }
|
    PROGRAM IDENT_NAME SEMICOLON routine {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse program 2: " << (*$2.stringValue) << std::endl;
        #endif

        std::string name{*$2.stringValue};
        $4->setSubType(ast::RoutineNode::SubType::MAIN);
        $$ = new ast::ProgramNode(std::move(name), $4);
        resultAst = $$;
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of end dot");
    }
|
    PROGRAM IDENT_NAME routine DOT {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse program 3: " << (*$2.stringValue) << std::endl;
        #endif

        std::string name{*$2.stringValue};
        $3->setSubType(ast::RoutineNode::SubType::MAIN);
        $$ = new ast::ProgramNode(std::move(name), $3);
        resultAst = $$;
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
|
    PROGRAM IDENT_NAME routine {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse program 4: " << (*$2.stringValue) << std::endl;
        #endif

        std::string name{*$2.stringValue};
        $3->setSubType(ast::RoutineNode::SubType::MAIN);
        $$ = new ast::ProgramNode(std::move(name), $3);
        resultAst = $$;
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon and end dot");
    }
;

routine :
    routine_head routine_body {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine" << std::endl;
        #endif
        $$ = new ast::RoutineNode($1, $2);
    }
;

routine_head :
    const_part type_part var_part routine_part {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine head" << std::endl;
        #endif
        $$ = new ast::RoutineHeadNode($1, $2, $3, $4);
    }
;

routine_part :
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty routine part" << std::endl;
        #endif
        $$ = new std::vector<ast::RoutineDeclarationNode*>();
    }
|
    routine_part fun_decl {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine part with fun decl 1 " << $2->getName() << std::endl;
        #endif

        saveRoutine($2);

        $$ = $1;
        $$->push_back($2);
    }
|
    routine_part proc_decl {
       #ifdef YACC_DEBUG
           std::cout << "Yacc debug: Parse routine part with proc decl 1 " << $2->getName() << std::endl;
       #endif

       saveRoutine($2);

       $$ = $1;
       $$->push_back($2);
    }
|
    fun_decl {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine part with fun decl 2 " << $1->getName() << std::endl;
        #endif

        saveRoutine($1);

        $$ = new std::vector<ast::RoutineDeclarationNode*>();
        $$->push_back($1);
    }
|
    proc_decl {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine part with proc decl 2 " << $1->getName() << std::endl;
        #endif

        saveRoutine($1);

        $$ = new std::vector<ast::RoutineDeclarationNode*>();
        $$->push_back($1);
    }
;

fun_decl :
    fun_head SEMICOLON routine SEMICOLON {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun decl 1" << std::endl;
        #endif

        ctx->getLookupTable().popScope();

        $$ = $1;
        $$->setRoutine(std::unique_ptr<ast::RoutineNode>($3));
        $$->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
    }
|
    fun_head SEMICOLON routine {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun decl 2" << std::endl;
        #endif

        ctx->getLookupTable().popScope();

        $$ = $1;
        $$->setRoutine(std::unique_ptr<ast::RoutineNode>($3));
        $$->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
|
    fun_head routine SEMICOLON {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun decl 3" << std::endl;
        #endif

        ctx->getLookupTable().popScope();

        $$ = $1;
        $$->setRoutine(std::unique_ptr<ast::RoutineNode>($2));
        $$->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
|
    fun_head routine {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun decl 4" << std::endl;
        #endif

        ctx->getLookupTable().popScope();

        $$ = $1;
        $$->setRoutine(std::unique_ptr<ast::RoutineNode>($2));
        $$->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
;

fun_head :
    FUNCTION IDENT_NAME params COLON simple_type {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun head " << (*$2.stringValue) << std::endl;
        #endif

        ctx->getLookupTable().pushScope(*$2.stringValue);

        std::string name{*$2.stringValue};
        $$ = new ast::RoutineDeclarationNode(ast::RoutineDeclarationNode::RoutineType::FUNCTION, std::move(name), $3, $5, nullptr);


    }
;

proc_decl :
    proc_head SEMICOLON routine SEMICOLON {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse proc decl" << std::endl;
        #endif

        ctx->getLookupTable().popScope();

        $$ = $1;
        $$->setRoutine(std::unique_ptr<ast::RoutineNode>($3));
        $$->setRoutineType(ast::RoutineDeclarationNode::RoutineType::PROCEDURE);
    }
|
    proc_head routine SEMICOLON {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse proc decl" << std::endl;
        #endif

        ctx->getLookupTable().popScope();

        $$ = $1;
        $$->setRoutine(std::unique_ptr<ast::RoutineNode>($2));
        $$->setRoutineType(ast::RoutineDeclarationNode::RoutineType::PROCEDURE);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
|
    proc_head SEMICOLON routine {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse proc decl" << std::endl;
        #endif

        ctx->getLookupTable().popScope();

        $$ = $1;
        $$->setRoutine(std::unique_ptr<ast::RoutineNode>($3));
        $$->setRoutineType(ast::RoutineDeclarationNode::RoutineType::PROCEDURE);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
|
    proc_head routine {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse proc decl" << std::endl;
        #endif

        ctx->getLookupTable().popScope();

        $$ = $1;
        $$->setRoutine(std::unique_ptr<ast::RoutineNode>($2));
        $$->setRoutineType(ast::RoutineDeclarationNode::RoutineType::PROCEDURE);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
;

proc_head :
    PROCEDURE IDENT_NAME params {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse proc head " << (*$2.stringValue) << std::endl;
        #endif

        ctx->getLookupTable().pushScope(*$2.stringValue);

        std::string name{*$2.stringValue};
        $$ = new ast::RoutineDeclarationNode(ast::RoutineDeclarationNode::RoutineType::PROCEDURE, std::move(name), $3, nullptr, nullptr);
    }
;

params :
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty params" << std::endl;
        #endif
        std::vector<ast::ParamsGroupNode *>* emptyParamsList = new std::vector<ast::ParamsGroupNode*>();
        $$ = new ast::ParamsNode(emptyParamsList);
    }
|
    LP params_decl RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params" << std::endl;
        #endif
        $$ = new ast::ParamsNode($2);
    }
;

params_decl :
    params_decl SEMICOLON params_type {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params decl 1" << std::endl;
        #endif
        $$ = $1;
        $$->push_back($3);
    }
|
    params_type {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params decl 2" << std::endl;
        #endif
        $$ = new std::vector<ast::ParamsGroupNode*>();
        $$->push_back($1);
    }
;

params_type :
    VAR name_list COLON simple_type {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params type 1" << std::endl;
        #endif
        $$ = new ast::ParamsGroupNode(ast::ParamsGroupNode::PassType::PASS_BY_REFERENCE, $2, $4);
    }
|
    name_list COLON simple_type {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params type 2" << std::endl;
        #endif
        $$ = new ast::ParamsGroupNode(ast::ParamsGroupNode::PassType::PASS_BY_VALUE, $1, $3);
    }
;

var_part :
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty var part" << std::endl;
        #endif
        $$ = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
    }
|
    VAR var_decl_list {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var part" << std::endl;
        #endif
        $$ = $2;
    }
;

var_decl_list :
    var_decl_list var_decl {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl list 1" << std::endl;
        #endif
        $$ = $1;
        $$->push_back($2);
    }
|
    var_decl {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl list 2" << std::endl;
        #endif
        $$ = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
        $$->push_back($1);
    }
;

var_decl :
    name_list COLON type_decl SEMICOLON {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl 1" << std::endl;
        #endif

        saveVariables($1, $3);

        $$ = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>($1, $3);
    }
|
    name_list COLON type_decl {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl 2" << std::endl;
        #endif

        saveVariables($1, $3);

        $$ = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>($1, $3);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
;

const_part :
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty const part" << std::endl;
        #endif
        $$ = new std::vector<std::pair<ast::IdentifierNode*, ast::ConstantNode*>*>();
    }
|
    CONST const_expr_list {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const part" << std::endl;
        #endif

        $$ = $2;
    }
;

const_expr_list :
    const_expr_list const_expr {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr list 1" << std::endl;
        #endif
        $$ = $1;
        $$->push_back($2);
    }
|
    const_expr {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr list 2" << std::endl;
        #endif
        $$ = new std::vector<std::pair<ast::IdentifierNode*, ast::ConstantNode*>*>();
        $$->push_back($1);
    }
;

const_expr :
    identifier EQUAL const_value SEMICOLON {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr 1" << std::endl;
        #endif

        saveConstant($1, $3);

        $$ = new std::pair<ast::IdentifierNode*, ast::ConstantNode*>($1, $3);
    }
|
    identifier EQUAL const_value {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr 2" << std::endl;
        #endif

        saveConstant($1, $3);

        $$ = new std::pair<ast::IdentifierNode*, ast::ConstantNode*>($1, $3);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
;

const_value :
    INTEGER {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - integer `" << $1.numericalValue << "`" << std::endl;
        #endif
        $$ = new ast::IntegerConstantNode($1.numericalValue);
    }
|
    MINUS INTEGER {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - signed integer `" << -$2.numericalValue << "`" << std::endl;
        #endif
        $$ = new ast::IntegerConstantNode(-$2.numericalValue);
    }

|   CHAR
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - char `" << static_cast<char>($1.numericalValue) << "`" << std::endl;
        #endif
        $$ = new ast::CharConstantNode(static_cast<char>($1.numericalValue));
    }
|
    STRING {
        std::string str{*$1.stringValue};
        str = str.substr(1, str.size() - 2);

        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - string `" << str << "`" << std::endl;
        #endif

        $$ = new ast::StringConstantNode(std::move(str));
    }
|
    TRUE {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - true" << std::endl;
        #endif
        $$ = new ast::BooleanConstantNode(true);
    }
|
    FALSE {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - false" << std::endl;
        #endif
        $$ = new ast::BooleanConstantNode(false);
    }
|
    MAXINT {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - maxint" << std::endl;
        #endif
        $$ = new ast::IntegerConstantNode(255);
    }
|
    MINUS MAXINT {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const value - signed maxint" << std::endl;
        #endif
        $$ = new ast::IntegerConstantNode(-255);
    }
;

type_part :
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty type part" << std::endl;
        #endif
        $$ = new std::vector<std::pair<ast::IdentifierNode*, ast::TypeNode*>*>();
    }
|
    TYPE type_decl_list {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type part" << std::endl;
        #endif
        $$ = $2;
    }
;

type_decl_list :
    type_decl_list type_def {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type decl list 1" << std::endl;
        #endif

        $$ = $1;
        $$->push_back($2);
    }
|
    type_def {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type decl list 2" << std::endl;
        #endif

        $$ = new std::vector<std::pair<ast::IdentifierNode*, ast::TypeNode*>*>();
        $$->push_back($1);
    }
;

type_def :
    identifier EQUAL type_decl SEMICOLON {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type def 1" << std::endl;
        #endif

        saveType($1, $3);

        $$ = new std::pair<ast::IdentifierNode*, ast::TypeNode*>($1, $3);
    }
|
    identifier EQUAL type_decl {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type def 2" << std::endl;
        #endif

        saveType($1, $3);

        $$ = new std::pair<ast::IdentifierNode*, ast::TypeNode*>($1, $3);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
;

type_decl :
    simple_type {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type" << std::endl;
        #endif
        $$ = $1;
    }
|
    array_type_decl {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse array type" << std::endl;
        #endif
        $$ = $1;
    }
|
    record_type_decl {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse record type" << std::endl;
        #endif
        $$ = $1;
    }
;

record_type_decl :
    RECORD field_decl_list END {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse record type" << std::endl;
        #endif
        $$ = new ast::RecordTypeNode($2);
    }
;

field_decl_list :
    field_decl_list field_decl {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl list 1" << std::endl;
        #endif
        $$ = $1;
        $$->push_back($2);
    }
|
    field_decl {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl list 2" << std::endl;
        #endif
        $$ = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
        $$->push_back($1);
    }
;

field_decl :
    name_list COLON type_decl SEMICOLON {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl 1" << std::endl;
        #endif
        $$ = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>($1, $3);
    }
|
    name_list COLON type_decl {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse field decl 2" << std::endl;
        #endif
        $$ = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>($1, $3);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
;

array_type_decl :
    ARRAY LB simple_type RB OF type_decl {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse array type" << std::endl;
        #endif
        $$ = new ast::ArrayTypeNode($3, $6);
    }
;

simple_type :
    identifier {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - identifier" << std::endl;
        #endif
        $$ = new ast::RenameTypeNode($1);
    }
|
    LP name_list RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - parentheses" << std::endl;
        #endif
        $$ = new ast::EnumerationTypeNode($2);
    }
|
    const_value DOUBLEDOT const_value {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - range 1" << std::endl;
        #endif
        $$ = new ast::ConstRangeTypeNode($1, $3);
    }
|
    identifier DOUBLEDOT identifier {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - range 4" << std::endl;
        #endif
        $$ = new ast::VarRangeTypeNode($1, $3);
    }
|
    INT_TYPE {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - int" << std::endl;
        #endif
        $$ = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::INTEGER);
    }
|
    UNSIGNED_TYPE {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - unsigned" << std::endl;
        #endif
        $$ = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::UNSIGNED);
    }
|
    BOOL_TYPE {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - bool" << std::endl;
        #endif
        $$ = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::BOOLEAN);
    }
|
    CHAR_TYPE {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - char" << std::endl;
        #endif
        $$ = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::CHAR);
    }
;

name_list :
    name_list COMMA identifier {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse name list 1" << std::endl;
        #endif
        $$ = $1;
        $$->push_back($3);
    }
|
    identifier {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse name list 2" << std::endl;
        #endif
        $$ = new std::vector<ast::IdentifierNode*>();
        $$->push_back($1);
    }
;

identifier :
    IDENT_NAME {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse identifier `" << (*$1.stringValue) << "`" << std::endl;
        #endif
        std::string name{*$1.stringValue};
        $$ = new ast::IdentifierNode(std::move(name));
    }
;

routine_body :
    compound_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine body" << std::endl;
        #endif
        $$ = new ast::RoutineBodyNode($1);
    }
;

compound_stmt :
    BBEGIN stmt_list END {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse compound statement 1" << std::endl;
        #endif
        $$ = new ast::CompoundStatementNode($2);
    }
|
    BBEGIN stmt_list {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse compound statement 2" << std::endl;
        #endif
        $$ = new ast::CompoundStatementNode($2);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of end");
    }
;

stmt_list :
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty statement list" << std::endl;
        #endif
        $$ = new std::vector<ast::StatementNode*>();
    }
|
    stmt_list stmt SEMICOLON {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement list 1" << std::endl;
        #endif
        $$ = $1;
        $$->push_back($2);
    }
|
    stmt_list stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement list 2" << std::endl;
        #endif
        $$ = $1;
        $$->push_back($2);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
;

stmt :
    INTEGER COLON no_label_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement with label " << $1.numericalValue << std::endl;
        #endif
        $$ = $3;
        $$->setLabel($1.numericalValue);
    }
|
    no_label_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse statement without label" << std::endl;
        #endif
        $$ = $1;
    }
;

no_label_stmt :
    assign_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - assign" << std::endl;
        #endif
        $$=$1;
    }
|
    compound_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - compound" << std::endl;
        #endif
        $$ = $1;
    }
|
    goto_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - goto" << std::endl;
        #endif
        $$ = $1;
    }
|
    if_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - if" << std::endl;
        #endif
        $$ = $1;
    }
|
    repeat_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - repeat" << std::endl;
        #endif
        $$ = $1;
    }
|
    while_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - while" << std::endl;
        #endif
        $$ = $1;
    }
|
    case_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - case" << std::endl;
        #endif
        $$ = $1;
    }
|
    for_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - for" << std::endl;
        #endif
        $$ = $1;
    }
|
    proc_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - proc" << std::endl;
        #endif
        $$ = $1;
    }
|
    BREAK {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - break" << std::endl;
        #endif
        $$ = new ast::BreakNode();
    }
|
    CONTINUE {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label statement - continue" << std::endl;
        #endif
        $$ = new ast::ContinueNode();
    }
;

assign_stmt :
    identifier ASSIGN expression {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple assign statement" << std::endl;
        #endif
        $$ = new ast::AssignToVariableNode($1, $3);
    }
|
    identifier LB expression RB ASSIGN expression {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse array assign statement" << std::endl;
        #endif
        $$ = new ast::AssignToArrayNode($1, $3, $6);
    }
|
    identifier DOT identifier ASSIGN expression {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse record assign statement" << std::endl;
        #endif
        $$ = new ast::AssignToRecordFieldNode($1, $3, $5);
    }
;

goto_stmt :
    GOTO INTEGER {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse goto statement to " << $2.numericalValue << std::endl;
        #endif
        $$ = new ast::GotoNode($2.numericalValue);
    }
;

if_stmt :
    IF expression THEN stmt else_clause {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse if statement 1" << std::endl;
        #endif
        $$ = new ast::IfNode($2, $4, $5);
    }
|
    IF expression stmt else_clause {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse if statement 2" << std::endl;
        #endif
        $$ = new ast::IfNode($2, $3, $4);
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of then");
    }
;

else_clause :
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty else clause" << std::endl;
        #endif
        $$ = new ast::IfNode(nullptr, nullptr);
    }
|
    ELSE stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse else clause" << std::endl;
        #endif
        $$ = new ast::IfNode(nullptr, nullptr, $2);
    }
;

repeat_stmt :
    REPEAT stmt_list UNTIL expression {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse repeat statement" << std::endl;
        #endif
        $$ = new ast::RepeatNode($4, $2);
    }
|
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty repeat statement" << std::endl;
        #endif
    }
;

while_stmt :
    WHILE expression DO stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse while statement" << std::endl;
        #endif
        $$ = new ast::WhileNode($2, $4);
    }
;

case_stmt :
    CASE expression OF case_expr_list END {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case statement" << std::endl;
        #endif
        $$ = new ast::CaseNode($2, $4);
    }
;

case_expr_list :
    case_expr_list case_expr {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr list 1" << std::endl;
        #endif
        $$ = $1;
        $$->push_back($2);
    }
|
    case_expr {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr list 2" << std::endl;
        #endif
        $$ = new std::vector<std::pair<ast::AstNode*, ast::StatementNode*>*>();
        $$->push_back($1);
    }
;

case_expr :
    const_value COLON stmt SEMICOLON {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr 1" << std::endl;
        #endif
        $$ = new std::pair<ast::AstNode*, ast::StatementNode*>($1, $3);
    }
|
    identifier COLON stmt SEMICOLON {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr 2" << std::endl;
        #endif
        $$ = new std::pair<ast::AstNode*, ast::StatementNode*>($1, $3);
    }
|
    OTHERWISE stmt SEMICOLON {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr 3" << std::endl;
        #endif
        $$ = new std::pair<ast::AstNode*, ast::StatementNode*>(nullptr, $2);
    }
;

for_stmt :
    FOR identifier ASSIGN expression TO expression DO stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse for statement 1" << std::endl;
        #endif
        $$ = new ast::ForNode($2, $4, $6, $8, ast::ForNode::Direction::INCREMENT);
    }
|
    FOR identifier ASSIGN expression DOWNTO expression DO stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse for statement 2" << std::endl;
        #endif
        $$ = new ast::ForNode($2, $4, $6, $8, ast::ForNode::Direction::DECREMENT);
    }
;

proc_stmt :
    identifier {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse procedure statement" << std::endl;
        #endif
        $$ = new ast::UserDefineCallNode($1, nullptr);
    }
|
    identifier LP args_list RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse procedure statement with args" << std::endl;
        #endif
        $$ = new ast::UserDefineCallNode($1, $3);
    }
|
    READ LP factor RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse read statement" << std::endl;
        #endif
        if(isVariableRecordFieldArrayElementCompatible($3)) {
            ast::ArgumentsListNode* args = new ast::ArgumentsListNode();
            args->addArgument($3);
            $$ = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::READ, args);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for read - variable, record field or array element expected");
            fatalError = true;
        }
    }

|
    READLN {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse readln statement" << std::endl;
        #endif
        $$ = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::READLN, nullptr);
    }
|
    WRITE LP args_list RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse write statement" << std::endl;
        #endif
        $$ = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITE, $3);
    }
|
    WRITELN {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse writeln statement" << std::endl;
        #endif
        $$ = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITELN, nullptr);
    }
|
    WRITELN LP args_list RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse writeln statement with args" << std::endl;
        #endif
        $$ = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITELN, $3);
    }
|
    MEMORYREAD LP args_list RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse memory read statement" << std::endl;
        #endif
        if($3->getArguments().size() == 3) {
            if(!isIntegerCompatibile($3->getArguments().at(0)) || !isIntegerCompatibile($3->getArguments().at(1)))) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory read - first two arguments should be integers");
                fatalError = true;
            }
            else if(!isIntegerCompatibile($3->getArguments().at(2)) && !isCharCompatibile($3->getArguments().at(2))) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory read - third argument should be integer or char");
                fatalError = true;
            }
            else {
                $$ = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::MEMORY_READ, $3);
            }
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for memory read - 3 arguments expected");
        }
    }
|
    MEMORYWRITE LP args_list RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse memory write statement" << std::endl;
        #endif
        if($3->getArguments().size() == 3) {
            if(!isIntegerCompatibile($3->getArguments().at(0)) || !isIntegerCompatibile($3->getArguments().at(1))) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory write - first two arguments should be integers");
                fatalError = true;
            }
            else if(!isIntegerCompatibile($3->getArguments().at(2)) && !isCharCompatibile($3->getArguments().at(2))) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory write - third argument should be integer or char");
                fatalError = true;
            }
            else {
                $$ = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::MEMORY_WRITE, $3);
            }
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for memory write - 3 arguments expected");
        }
    }
|
    STACKREAD LP args_list RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse stack read statement" << std::endl;
        #endif
        if($3->getArguments().size() == 3) {
            if(!isIntegerCompatibile($3->getArguments().at(0)) || !isIntegerCompatibile($3->getArguments().at(1))) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack read - first two arguments should be integers");
                fatalError = true;
            }
            else if(!isIntegerCompatibile($3->getArguments().at(2)) && !isCharCompatibile($3->getArguments().at(2))) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack read - third argument should be integer or char");
                fatalError = true;
            }
            else {
                $$ = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::STACK_READ, $3);
            }
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for stack read - 3 arguments expected");
        }
    }
|
    STACKWRITE LP args_list RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse stack write statement" << std::endl;
        #endif
        if($3->getArguments().size() == 3) {
            if(!isIntegerCompatibile($3->getArguments().at(0)) || !isIntegerCompatibile($3->getArguments().at(1))) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack write - first two arguments should be integers");
                fatalError = true;
            }
            else if(!isIntegerCompatibile($3->getArguments().at(2)) && !isCharCompatibile($3->getArguments().at(2))) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack write - third argument should be integer or char");
                fatalError = true;
            }
            else {
                $$ = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::STACK_WRITE, $3);
            }
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for stack write - 3 arguments expected");
        }
    }
;

args_list :
    args_list COMMA expression {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse args list 1" << std::endl;
        #endif
        $$ = $1;
        $$->addArgument($3);
    }
|
    expression  {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse args list 2" << std::endl;
        #endif
        $$ = new ast::ArgumentsListNode();
        $$->addArgument($1);
    }
;

expression :
    expression GE expr {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with greater or equal" << std::endl;
        #endif
        if(isIntegerCompatibile($1) && isIntegerCompatibile($3) || isBooleanCompatibile($1) && isBooleanCompatibile($3) || isCharCompatibile($1) && isCharCompatibile($3)) {
            $$ = new ast::ExpressionNode($1, $3, ast::ExpressionNode::Operation::GREATER_EQUAL);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for greater or equal - matching types expected");
            fatalError = true;
        }
    }
|
    expression GT expr {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with greater" << std::endl;
        #endif
        if(isIntegerCompatibile($1) && isIntegerCompatibile($3) || isBooleanCompatibile($1) && isBooleanCompatibile($3) || isCharCompatibile($1) && isCharCompatibile($3)) {
            $$ = new ast::ExpressionNode($1, $3, ast::ExpressionNode::Operation::GREATER);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for greater - matching types expected");
            fatalError = true;
        }
    }
|
    expression LE expr {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with less or equal" << std::endl;
        #endif
        if(isIntegerCompatibile($1) && isIntegerCompatibile($3) || isBooleanCompatibile($1) && isBooleanCompatibile($3) || isCharCompatibile($1) && isCharCompatibile($3)) {
            $$ = new ast::ExpressionNode($1, $3, ast::ExpressionNode::Operation::LESS_EQUAL);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for less or equal - matching types expected");
            fatalError = true;
        }
    }
|
    expression LT expr {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with less" << std::endl;
        #endif
        if(isIntegerCompatibile($1) && isIntegerCompatibile($3) || isBooleanCompatibile($1) && isBooleanCompatibile($3) || isCharCompatibile($1) && isCharCompatibile($3)) {
            $$ = new ast::ExpressionNode($1, $3, ast::ExpressionNode::Operation::LESS);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for less - matching types expected");
            fatalError = true;
        }
    }
|
    expression EQUAL expr {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with equal" << std::endl;
        #endif
        if(isIntegerCompatibile($1) && isIntegerCompatibile($3) || isBooleanCompatibile($1) && isBooleanCompatibile($3) || isCharCompatibile($1) && isCharCompatibile($3)) {
            $$ = new ast::ExpressionNode($1, $3, ast::ExpressionNode::Operation::EQUAL);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for equal - matching types expected");
            fatalError = true;
        }
    }
|
    expression UNEQUAL expr {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with not equal" << std::endl;
        #endif
        if(isIntegerCompatibile($1) && isIntegerCompatibile($3) || isBooleanCompatibile($1) && isBooleanCompatibile($3) || isCharCompatibile($1) && isCharCompatibile($3)) {
            $$ = new ast::ExpressionNode($1, $3, ast::ExpressionNode::Operation::UNEQUAL);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for not equal - matching types expected");
            fatalError = true;
        }

    }
|
    expr {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple expression" << std::endl;
        #endif
        $$ = $1;
    }
;

expr :
    expr PLUS term {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with addition" << std::endl;
        #endif
        if(isIntegerCompatibile($1) && isIntegerCompatibile($3)) {
            $$ = new ast::ExpressionNode($1, $3, ast::ExpressionNode::Operation::ADDITION);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for addition - integer expected");
            fatalError = true;
        }
    }
|
    expr MINUS term {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with subtraction" << std::endl;
        #endif
        if(isIntegerCompatibile($1) && isIntegerCompatibile($3)) {
            $$ = new ast::ExpressionNode($1, $3, ast::ExpressionNode::Operation::SUBTRACTION);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for subtraction - integer expected");
            fatalError = true;
        }
    }
|
    expr OR term {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with or" << std::endl;
        #endif
        if(isBooleanCompatibile($1) && isBooleanCompatibile($3)) {
            $$ = new ast::ExpressionNode($1, $3, ast::ExpressionNode::Operation::OR);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for or - boolean expected");
            fatalError = true;
        }
    }
|
    term {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple term" << std::endl;
        #endif
        $$ = $1;
    }
;

term :
    term MUL factor {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with multiplication" << std::endl;
        #endif
        if(isIntegerCompatibile($1) && isIntegerCompatibile($3)) {
            $$ = new ast::ExpressionNode($1, $3, ast::ExpressionNode::Operation::MULTIPLICATION);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for mul - integer expected");
            fatalError = true;
        }
    }
|
    term DIV factor {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with division" << std::endl;
        #endif
        if(isIntegerCompatibile($1) && isIntegerCompatibile($3)) {
            $$ = new ast::ExpressionNode($1, $3, ast::ExpressionNode::Operation::DIVISION);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for div - integer expected");
            fatalError = true;
        }
    }
|
    term MOD factor {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with modulus" << std::endl;
        #endif
        if(isIntegerCompatibile($1) && isIntegerCompatibile($3)) {
            $$ = new ast::ExpressionNode($1, $3, ast::ExpressionNode::Operation::MODULUS);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for mod - integer expected");
            fatalError = true;
        }
    }
|
    term AND factor {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with and" << std::endl;
        #endif
        if(isBooleanCompatibile($1) && isBooleanCompatibile($3)) {
            $$ = new ast::ExpressionNode($1, $3, ast::ExpressionNode::Operation::AND);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for and - boolean expected");
            fatalError = true;
        }
    }
|
    factor {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple factor" << std::endl;
        #endif
        $$ = $1;
    }
;

factor :
    identifier {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - identifier" << std::endl;
        #endif
        $$ = new ast::SpecialExpressionNode($1, ast::SpecialExpressionNode::FunctionName::VARIABLE);
    }
|
    identifier LP args_list RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - function call" << std::endl;
        #endif
        $$ = new ast::SpecialExpressionNode($1, $3, ast::SpecialExpressionNode::FunctionName::CALL);
    }
|
    const_value {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - const value" << std::endl;
        #endif
        $$ = new ast::SpecialExpressionNode($1, ast::SpecialExpressionNode::FunctionName::CONST);
    }
|
    LP expression RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - parentheses" << std::endl;
        #endif
        $$ = new ast::SpecialExpressionNode($2, ast::SpecialExpressionNode::FunctionName::PARENTHESIS);
    }
|
    NOT factor {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - not" << std::endl;
        #endif
       if(isBooleanCompatibile($2)) {
            $$ = new ast::ExpressionNode($2, ast::ExpressionNode::Operation::NEGATION);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for not - boolean expected");
            fatalError = true;
        }
    }
|
    MINUS factor {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - negation" << std::endl;
        #endif
        if(isIntegerCompatibile($2)) {
            $$ = new ast::ExpressionNode($2, ast::ExpressionNode::Operation::NEGATION);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for negation - integer expected");
            fatalError = true;
        }

    }
|
    identifier LB expression RB {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - array access" << std::endl;
        #endif
        $$ = new ast::SpecialExpressionNode($1, $3, ast::SpecialExpressionNode::FunctionName::ARRAY_ACCESS);
    }
|
    identifier DOT identifier {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - record access" << std::endl;
        #endif
        $$ = new ast::SpecialExpressionNode($1, $3, ast::SpecialExpressionNode::FunctionName::RECORD_ACCESS);
    }
|
    ABS LP args_list RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - abs" << std::endl;
        #endif
        if($3->getArguments().size() != 1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for abs");
            fatalError = true;
        }
        else {
            ExpressionNode* arg = $3->getArguments().front();
            if(isIntegerCompatibile(arg)) {
                $$ = new ast::SpecialExpressionNode($3, ast::SpecialExpressionNode::FunctionName::ABS);
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for abs - integer expected");
                fatalError = true;
            }
        }
    }
|
    CHR LP args_list RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - chr" << std::endl;
        #endif
        if($3->getArguments().size() != 1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for chr");
            fatalError = true;
        }
        else {
            ExpressionNode* arg = $3->getArguments().front();
            if(isIntegerCompatibile(arg)) {
                $$ = new ast::SpecialExpressionNode($3, ast::SpecialExpressionNode::FunctionName::CHR);
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for chr - integer expected");
                fatalError = true;
            }
        }
    }
|
    ODD LP args_list RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - odd" << std::endl;
        #endif
        if($3->getArguments().size() != 1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for odd");
            fatalError = true;
        }
        else {
            ExpressionNode* arg = $3->getArguments().front();
            if(isIntegerCompatibile(arg)) {
                $$ = new ast::SpecialExpressionNode($3, ast::SpecialExpressionNode::FunctionName::ODD);
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for odd - integer expected");
                fatalError = true;
            }
        }
    }
|
    ORD LP args_list RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - ord" << std::endl;
        #endif
        if($3->getArguments().size() != 1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for ord");
            fatalError = true;
        }
        else {
            ExpressionNode* arg = $3->getArguments().front();
            if(isCharCompatibile(arg)) {
                $$ = new ast::SpecialExpressionNode($3, ast::SpecialExpressionNode::FunctionName::ORD);
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for ord - char expected");
                fatalError = true;
            }
        }
    }
|
    PRED LP args_list RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - pred" << std::endl;
        #endif
        if($3->getArguments().size() != 1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for pred");
            fatalError = true;
        }
        else {
            ExpressionNode* arg = $3->getArguments().front();
            if(isIntegerCompatibile(arg) || isCharCompatibile(arg)) {
                $$ = new ast::SpecialExpressionNode($3, ast::SpecialExpressionNode::FunctionName::PRED);
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for pred - integer or char expected");
                fatalError = true;
            }
        }
    }
|
    SUCC LP args_list RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - succ" << std::endl;
        #endif
        if($3->getArguments().size() != 1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for succ");
            fatalError = true;
        }
        else {
            ExpressionNode* arg = $3->getArguments().front();
            if(isIntegerCompatibile(arg) || isCharCompatibile(arg)) {
                $$ = new ast::SpecialExpressionNode($3, ast::SpecialExpressionNode::FunctionName::SUCC);
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for succ - integer or char expected");
                fatalError = true;
            }
        }
    }
;
%%

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

bool isIntegerCompatible(ast::ExpressionNode* expr) {
    return true;
}

bool isCharCompatible(ast::ExpressionNode* expr) {
    return true;
}

bool isBooleanCompatible(ast::ExpressionNode* expr) {
    return true;
}

bool bool isVariableRecordFieldArrayElementCompatible(ast::ExpressionNode* expr) {
    return true;
}