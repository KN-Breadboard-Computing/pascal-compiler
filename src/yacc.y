%{
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
        char* stringValue;
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
%token READ WRITE WRITELN ABS CHR ODD ORD PRED SUCC
%token IF THEN ELSE REPEAT UNTIL WHILE DO CASE TO DOWNTO FOR
%token EQUAL UNEQUAL GE GT LE LT ASSIGN PLUS MINUS MUL DIV OR AND NOT MOD
%token LB RB LP RP SEMICOLON DOT DOUBLEDOT COMMA COLON
%token INT_TYPE BOOL_TYPE CHAR_TYPE STRING_TYPE
%token ARRAY OF RECORD GOTO
%token ERROR

%type <token> PROGRAM FUNCTION PROCEDURE CONST TYPE VAR BBEGIN END
%type <token> IDENT_NAME INTEGER BOOLEAN CHAR STRING
%type <token> TRUE FALSE MAXINT
%type <token> READ WRITE WRITELN ABS CHR ODD ORD PRED SUCC
%type <token> IF THEN ELSE REPEAT UNTIL WHILE DO CASE TO DOWNTO FOR
%type <token> EQUAL UNEQUAL GE GT LE LT ASSIGN PLUS MINUS MUL DIV OR AND NOT MOD
%type <token> LB RB LP RP SEMICOLON DOT DOUBLEDOT COMMA COLON
%type <token> INT_TYPE BOOL_TYPE CHAR_TYPE STRING_TYPE
%type <token> ARRAY OF RECORD GOTO
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
        std::string name{$2.stringValue};
        $4->setSubType(ast::RoutineNode::SubType::MAIN);
        $$ = new ast::ProgramNode(std::move(name), $4);
        resultAst = $$;
    }
|
    PROGRAM IDENT_NAME SEMICOLON routine {
        std::string name{$2.stringValue};
        $4->setSubType(ast::RoutineNode::SubType::MAIN);
        $$ = new ast::ProgramNode(std::move(name), $4);
        resultAst = $$;
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of end dot");
    }
|
    PROGRAM IDENT_NAME routine DOT {
        std::string name{$2.stringValue};
        $3->setSubType(ast::RoutineNode::SubType::MAIN);
        $$ = new ast::ProgramNode(std::move(name), $3);
        resultAst = $$;
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
|
    PROGRAM IDENT_NAME routine {
        std::string name{$2.stringValue};
        $3->setSubType(ast::RoutineNode::SubType::MAIN);
        $$ = new ast::ProgramNode(std::move(name), $3);
        resultAst = $$;
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of semicolon and end dot");
    }
;

routine :
    routine_head routine_body {
        $$ = new ast::RoutineNode($1, $2);
    }
;

routine_head :
    const_part type_part var_part routine_part {
        $$ = new ast::RoutineHeadNode($1, $2, $3, $4);
    }
;

routine_part :
    {
        $$ = new std::vector<ast::RoutineDeclarationNode*>();
    }
|
    routine_part fun_decl {
        $$ = $1;
        $$->push_back($2);
    }
|
    routine_part proc_decl {
       $$ = $1;
       $$->push_back($2);
    }
|
    fun_decl {
        $$ = new std::vector<ast::RoutineDeclarationNode*>();
        $$->push_back($1);
    }
|
    proc_decl {
        $$ = new std::vector<ast::RoutineDeclarationNode*>();
        $$->push_back($1);
    }
;

fun_decl :
    fun_head SEMICOLON routine SEMICOLON {
        $$ = $1;
        $$->setRoutine(std::unique_ptr<ast::RoutineNode>($3));
        $$->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
    }
|
    fun_head SEMICOLON routine {
        $$ = $1;
        $$->setRoutine(std::unique_ptr<ast::RoutineNode>($3));
        $$->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
|
    fun_head routine SEMICOLON {
        $$ = $1;
        $$->setRoutine(std::unique_ptr<ast::RoutineNode>($2));
        $$->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
|
    fun_head routine {
        $$ = $1;
        $$->setRoutine(std::unique_ptr<ast::RoutineNode>($2));
        $$->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
;

fun_head :
    FUNCTION IDENT_NAME params COLON simple_type {
        std::string name{$2.stringValue};
        $$ = new ast::RoutineDeclarationNode(ast::RoutineDeclarationNode::RoutineType::FUNCTION, std::move(name), $3, $5, nullptr);
    }
;

proc_decl :
    proc_head SEMICOLON routine SEMICOLON {
        $$ = $1;
        $$->setRoutine(std::unique_ptr<ast::RoutineNode>($3));
        $$->setRoutineType(ast::RoutineDeclarationNode::RoutineType::PROCEDURE);
    }
;

proc_head :
    PROCEDURE IDENT_NAME params {
        std::string name{$2.stringValue};
        $$ = new ast::RoutineDeclarationNode(ast::RoutineDeclarationNode::RoutineType::PROCEDURE, std::move(name), $3, nullptr, nullptr);
    }
;

params :
    {
        std::vector<ast::ParamsGroupNode *>* emptyParamsList{};
        $$ = new ast::ParamsNode(emptyParamsList);
    }
|
    LP params_decl RP {
        $$ = new ast::ParamsNode($2);
    }
;

params_decl :
    params_decl SEMICOLON params_type {
       $$ = $1;
       $$->push_back($3);
    }
|
    params_type {
        $$ = new std::vector<ast::ParamsGroupNode*>();
        $$->push_back($1);
    }
;

params_type :
    VAR name_list COLON simple_type {
        $$ = new ast::ParamsGroupNode(ast::ParamsGroupNode::PassType::PASS_BY_REFERENCE, $2, $4);
    }
|
    name_list COLON simple_type {
        $$ = new ast::ParamsGroupNode(ast::ParamsGroupNode::PassType::PASS_BY_VALUE, $1, $3);
    }
;

var_part :
    {
        $$ = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
    }
|
    VAR var_decl_list {
        $$ = $2;
    }
;

var_decl_list :
    var_decl_list var_decl {
        $$ = $1;
        $$->push_back($2);
    }
|
    var_decl {
        $$ = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
        $$->push_back($1);
    }
;

var_decl :
    name_list COLON type_decl SEMICOLON {
        $$ = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>($1, $3);
    }
|
    name_list COLON type_decl {
        $$ = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>($1, $3);
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
;

const_part :
    {
        $$ = new std::vector<std::pair<ast::IdentifierNode*, ast::ConstantNode*>*>();
    }
|
    CONST const_expr_list {
        $$ = $2;
    }
;

const_expr_list :
    const_expr_list const_expr {
        $$ = $1;
        $$->push_back($2);
    }
|
    const_expr {
        $$ = new std::vector<std::pair<ast::IdentifierNode*, ast::ConstantNode*>*>();
        $$->push_back($1);
    }
;

const_expr :
    identifier EQUAL const_value SEMICOLON {
        $$ = new std::pair<ast::IdentifierNode*, ast::ConstantNode*>($1, $3);
    }
|
    identifier EQUAL const_value {
        $$ = new std::pair<ast::IdentifierNode*, ast::ConstantNode*>($1, $3);
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
;

const_value :
    INTEGER {
        $$ = new ast::IntegerConstantNode($1.numericalValue);
    }
|   CHAR
    {
        $$ = new ast::CharConstantNode($1.stringValue[0]);
    }
|
    STRING {
        std::string str{$1.stringValue};
        $$ = new ast::StringConstantNode(std::move(str));
    }
|
    TRUE {
        $$ = new ast::BooleanConstantNode(true);
    }
|
    FALSE {
        $$ = new ast::BooleanConstantNode(false);
    }
|
    MAXINT {
        $$ = new ast::IntegerConstantNode(255);
    }
;

type_part :
    {
        $$ = new std::vector<std::pair<ast::IdentifierNode*, ast::TypeNode*>*>();
    }
|
    TYPE type_decl_list {
        $$ = $2;
    }
;

type_decl_list :
    type_decl_list type_def {
        $$ = $1;
        $$->push_back($2);
    }
|
    type_def {
        $$ = new std::vector<std::pair<ast::IdentifierNode*, ast::TypeNode*>*>();
        $$->push_back($1);
    }
;

type_def :
    identifier EQUAL type_decl SEMICOLON {
        $$ = new std::pair<ast::IdentifierNode*, ast::TypeNode*>($1, $3);
    }
|
    identifier EQUAL type_decl {
        $$ = new std::pair<ast::IdentifierNode*, ast::TypeNode*>($1, $3);
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
;

type_decl :
    simple_type {
        $$ = $1;
    }
|
    array_type_decl {
        $$ = $1;
    }
|
    record_type_decl {
        $$ = $1;
    }
;

record_type_decl :
    RECORD field_decl_list END {
        $$ = new ast::RecordTypeNode($2);
    }
;

field_decl_list :
    field_decl_list field_decl {
        $$ = $1;
        $$->push_back($2);
    }
|
    field_decl {
        $$ = new std::vector<std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>*>();
        $$->push_back($1);
    }
;

field_decl :
    name_list COLON type_decl SEMICOLON {
        $$ = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>($1, $3);
    }
|
    name_list COLON type_decl {
        $$ = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>($1, $3);
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
;

array_type_decl :
    ARRAY LB simple_type RB OF type_decl {
        $$ = new ast::ArrayTypeNode($3, $6);
    }
;

simple_type :
    identifier {
        $$ = new ast::RenameTypeNode($1);
    }
|
    LP name_list RP {
        $$ = new ast::EnumerationTypeNode($2);
    }
|
    const_value DOUBLEDOT const_value {
        $$ = new ast::ConstRangeTypeNode($1, $3);
    }
|
    MINUS const_value DOUBLEDOT const_value {
        $$ = new ast::ConstRangeTypeNode($2, $4);
    }
|
    MINUS const_value DOUBLEDOT MINUS const_value {
        $$ = new ast::ConstRangeTypeNode($2, $5);
    }
|
    identifier DOUBLEDOT identifier {
        $$ = new ast::VarRangeTypeNode($1, $3);
    }
|
    INT_TYPE {
        $$ = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::INTEGER);
    }
|
    BOOL_TYPE {
        $$ = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::BOOLEAN);
    }
|
    CHAR_TYPE {
        $$ = new ast::SimpleTypeNode(ast::SimpleTypeNode::Representation::CHAR);
    }
;

name_list :
    name_list COMMA identifier {
        $$ = $1;
        $$->push_back($3);
    }
|
    identifier {
        $$ = new std::vector<ast::IdentifierNode*>();
        $$->push_back($1);
    }
;

identifier :
    IDENT_NAME {
        std::string name{$1.stringValue};
        $$ = new ast::IdentifierNode(std::move(name));
    }
;

routine_body :
    compound_stmt {
        $$ = new ast::RoutineBodyNode($1);
    }
;

compound_stmt :
    BBEGIN stmt_list END {
        $$ = new ast::CompoundStatementNode($2);
    }
|
    BBEGIN stmt_list {
        $$ = new ast::CompoundStatementNode($2);
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of end");
    }
;

stmt_list :
    {
        $$ = new std::vector<ast::StatementNode*>();
    }
|
    stmt_list stmt SEMICOLON {
        $$ = $1;
        $$->push_back($2);
    }
|
    stmt_list stmt {
        $$ = $1;
        $$->push_back($2);
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
;

stmt :
    INTEGER COLON no_label_stmt {
        $$ = $3;
        $$->setLabel($1.numericalValue);
    }
|
    no_label_stmt {
        $$ = $1;
    }
;

no_label_stmt :
    assign_stmt {
        $$=$1;
    }
|
    compound_stmt {
        $$ = $1;
    }
|
    goto_stmt {
        $$ = $1;
    }
|
    if_stmt {
        $$ = $1;
    }
|
    repeat_stmt {
        $$ = $1;
    }
|
    while_stmt {
        $$ = $1;
    }
|
    case_stmt {
        $$ = $1;
    }
|
    for_stmt {
        $$ = $1;
    }
|
    proc_stmt {
        $$ = $1;
    }
;

assign_stmt :
    identifier ASSIGN expression {
        $$ = new ast::AssignToVariableNode($1, $3);
    }
|
    identifier LB expression RB ASSIGN expression {
        $$ = new ast::AssignToArrayNode($1, $3, $6);
    }
|
    identifier DOT identifier ASSIGN expression {
        $$ = new ast::AssignToRecordFieldNode($1, $3, $5);
    }
;

goto_stmt :
    GOTO INTEGER {
        $$ = new ast::GotoNode($2.numericalValue);
    }
;

if_stmt :
    IF expression THEN stmt else_clause {
        $$ = new ast::IfNode($2, $4, $5);
    }
|
    IF expression stmt else_clause {
        $$ = new ast::IfNode($2, $3, $4);
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of then");
    }
;

else_clause :
    {
        $$ = new ast::IfNode(nullptr, nullptr);
    }
|
    ELSE stmt {
        $$ = new ast::IfNode(nullptr, nullptr, $2);
    }
;

repeat_stmt :
    REPEAT stmt_list UNTIL expression {
        $$ = new ast::RepeatNode($4, $2);
    }
|
    {
    }
;

while_stmt :
    WHILE expression DO stmt {
        $$ = new ast::WhileNode($2, $4);
    }
;

case_stmt :
    CASE expression OF case_expr_list END {
        $$ = new ast::CaseNode($2, $4);
    }
;

case_expr_list :
    case_expr_list case_expr {
        $$ = $1;
        $$->push_back($2);
    }
|
    case_expr {
        $$ = new std::vector<std::pair<ast::AstNode*, ast::StatementNode*>*>();
        $$->push_back($1);
    }
;

case_expr :
    const_value COLON stmt SEMICOLON {
        $$ = new std::pair<ast::AstNode*, ast::StatementNode*>($1, $3);
    }
|
    identifier COLON stmt SEMICOLON {
        $$ = new std::pair<ast::AstNode*, ast::StatementNode*>($1, $3);
    }
;

for_stmt :
    FOR identifier ASSIGN expression TO expression DO stmt {
        $$ = new ast::ForNode($2, $4, $6, $8, ast::ForNode::Direction::INCREMENT);
    }
|
    FOR identifier ASSIGN expression DOWNTO expression DO stmt {
        $$ = new ast::ForNode($2, $4, $6, $8, ast::ForNode::Direction::DECREMENT);
    }
;

proc_stmt :
    identifier {
        $$ = new ast::UserDefineCallNode($1, nullptr);
    }
|
    identifier LP args_list RP {
        $$ = new ast::UserDefineCallNode($1, $3);
    }
|
    READ LP factor RP {
        ast::ArgumentsListNode* args = new ast::ArgumentsListNode();
        args->addArgument($3);
        $$ = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::READ, args);
    }
|
    WRITE LP args_list RP {
        $$ = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITE, $3);
    }
|
    WRITELN {
        $$ = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITELN, nullptr);
    }
|
    WRITELN LP args_list RP {
        $$ = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITELN, $3);
    }
;

args_list :
    args_list COMMA expression {
        $$ = $1;
        $$->addArgument($3);
    }
|
    expression  {
        $$ = new ast::ArgumentsListNode();
        $$->addArgument($1);
    }
;

expression :
    expression GE expr {
        $$ = new ast::ExpressionNode($1, $3, ast::ExpressionNode::Operation::GREATER_EQUAL);
    }
|
    expression GT expr {
        $$ = new ast::ExpressionNode($1, $3, ast::ExpressionNode::Operation::GREATER);
    }
|
    expression LE expr {
        $$ = new ast::ExpressionNode($1, $3, ast::ExpressionNode::Operation::LESS_EQUAL);
    }
|
    expression LT expr {
        $$ = new ast::ExpressionNode($1, $3, ast::ExpressionNode::Operation::LESS);
    }
|
    expression EQUAL expr {
        $$ = new ast::ExpressionNode($1, $3, ast::ExpressionNode::Operation::EQUAL);
    }
|
    expression UNEQUAL expr {
        $$ = new ast::ExpressionNode($1, $3, ast::ExpressionNode::Operation::NOT_EQUAL);
    }
|
    expr {
        $$ = $1;
    }
;

expr :
    expr PLUS term {
        $$ = new ast::ExpressionNode($1, $3, ast::ExpressionNode::Operation::ADDITION);
    }
|
    expr MINUS term {
        $$ = new ast::ExpressionNode($1, $3, ast::ExpressionNode::Operation::SUBTRACTION);
    }
|
    expr OR term {
        $$ = new ast::ExpressionNode($1, $3, ast::ExpressionNode::Operation::OR);
    }
|
    term {
        $$ = $1;
    }
;

term :
    term MUL factor {
        $$ = new ast::ExpressionNode($1, $3, ast::ExpressionNode::Operation::MULTIPLICATION);
    }
|
    term DIV factor {
        $$ = new ast::ExpressionNode($1, $3, ast::ExpressionNode::Operation::DIVISION);
    }
|
    term MOD factor {
        $$ = new ast::ExpressionNode($1, $3, ast::ExpressionNode::Operation::MODULUS);
    }
|
    term AND factor {
        $$ = new ast::ExpressionNode($1, $3, ast::ExpressionNode::Operation::AND);
    }
|
    factor {
        $$ = $1;
    }
;

factor :
    identifier {
        $$ = new ast::SpecialExpressionNode($1, ast::SpecialExpressionNode::FunctionName::VARIABLE);
    }
|
    identifier LP args_list RP {
        $$ = new ast::SpecialExpressionNode($1, $3, ast::SpecialExpressionNode::FunctionName::CALL);
    }
|
    const_value {
        $$ = new ast::SpecialExpressionNode($1, ast::SpecialExpressionNode::FunctionName::CONST);
    }
|
    LP expression RP {
        $$ = new ast::SpecialExpressionNode($2, ast::SpecialExpressionNode::FunctionName::PARENTHESIS);
    }
|
    NOT factor {
       $$ = new ast::ExpressionNode($2, ast::ExpressionNode::Operation::NOT);
    }
|
    MINUS factor {
        $$ = new ast::ExpressionNode($2, ast::ExpressionNode::Operation::NEGATION);
    }
|
    identifier LB expression RB {
        $$ = new ast::SpecialExpressionNode($1, $3, ast::SpecialExpressionNode::FunctionName::ARRAY_ACCESS);
    }
|
    identifier DOT identifier {
        $$ = new ast::SpecialExpressionNode($1, $3, ast::SpecialExpressionNode::FunctionName::RECORD_ACCESS);
    }
|
    ABS LP args_list RP {
        $$ = new ast::SpecialExpressionNode($3, ast::SpecialExpressionNode::FunctionName::ABS);
    }
|
    CHR LP args_list RP {
        $$ = new ast::SpecialExpressionNode($3, ast::SpecialExpressionNode::FunctionName::CHR);
    }
|
    ODD LP args_list RP {
        $$ = new ast::SpecialExpressionNode($3, ast::SpecialExpressionNode::FunctionName::ODD);
    }
|
    ORD LP args_list RP {
        $$ = new ast::SpecialExpressionNode($3, ast::SpecialExpressionNode::FunctionName::ORD);
    }
|
    PRED LP args_list RP {
        $$ = new ast::SpecialExpressionNode($3, ast::SpecialExpressionNode::FunctionName::PRED);
    }
|
    SUCC LP args_list RP {
        $$ = new ast::SpecialExpressionNode($3, ast::SpecialExpressionNode::FunctionName::SUCC);
    }
;
%%

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