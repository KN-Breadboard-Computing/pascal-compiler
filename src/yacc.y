%{
#include <string>
#include <vector>

#include "../src/ast/program_node.hpp"

ast::ProgramNode* resultAst;
std::vector<std::string> parsingErrors;

static void yyerror(const char *msg);
static int yyparse(void);
int yylex(void);

extern uint64_t linesCounter;
%}

%code requires
{
    #include <iostream>
    #include <stdlib.h>
    #include <string>

    #include "../src/ast/array_type_node.hpp"
    #include "../src/ast/ast_node.hpp"
    #include "../src/ast/case_node.hpp"
    #include "../src/ast/constant_node.hpp"
    #include "../src/ast/for_node.hpp"
    #include "../src/ast/identifier_node.hpp"
    #include "../src/ast/if_node.hpp"
    #include "../src/ast/params_group_node.hpp"
    #include "../src/ast/params_node.hpp"
    #include "../src/ast/program_node.hpp"
    #include "../src/ast/record_type_node.hpp"
    #include "../src/ast/repeat_node.hpp"
    #include "../src/ast/routine_body_node.hpp"
    #include "../src/ast/routine_declaration_node.hpp"
    #include "../src/ast/routine_head_node.hpp"
    #include "../src/ast/routine_node.hpp"
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
    std::vector<ast::RoutineDeclarationNode>* routinePartList;
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
    std::vector<ast::StatementNode*>* statementNodeList;
    ast::StatementNode* statementNode;
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
%type <statementNodeList> compound_stmt stmt_list
%type <statementNode> stmt no_label_stmt

%type <token> assign_stmt goto_stmt if_stmt
%type <token> else_clause repeat_stmt case_stmt case_expr_list case_expr for_stmt proc_stmt args_list expr
%type <token> term factor
%type <token> while_stmt expression

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
        $$ = new std::vector<ast::RoutineDeclarationNode>();
    }
|
    routine_part fun_decl {
        $$ = $1;
        $$->push_back(*$2);
    }
|
    routine_part proc_decl {
       $$ = $1;
       $$->push_back(*$2);
    }
|
    fun_decl {
        $$ = new std::vector<ast::RoutineDeclarationNode>();
        $$->push_back(*$1);
    }
|
    proc_decl {
        $$ = new std::vector<ast::RoutineDeclarationNode>();
        $$->push_back(*$1);
    }
;

fun_decl :
    fun_head SEMICOLON routine SEMICOLON {
        $$ = $1;
        $$->setRoutine(std::make_unique<ast::RoutineNode>($3));
        $$->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
    }
|
    fun_head SEMICOLON routine {
        $$ = $1;
        $$->setRoutine(std::make_unique<ast::RoutineNode>($3));
        $$->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
|
    fun_head routine SEMICOLON {
        $$ = $1;
        $$->setRoutine(std::make_unique<ast::RoutineNode>($2));
        $$->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
        parsingErrors.push_back("error at line " + std::to_string(linesCounter) + ", lack of semicolon");
    }
|
    fun_head routine {
        $$ = $1;
        $$->setRoutine(std::make_unique<ast::RoutineNode>($2));
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
        $$->setRoutine(std::make_unique<ast::RoutineNode>($3));
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
        $$ = $2;
    } 
|	
    BBEGIN stmt_list {
        $$ = $2;
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

assign_stmt         :   identifier ASSIGN expression
                        {   $$=new TreeDefine(ASSIGN,line_no);
                            $$->addChild($1);
                            $$->addChild($3);
                            $$->setAttribute(OK_ID,4);
                        }
                    |   identifier LB expression RB ASSIGN expression
                        {   $$=new TreeDefine(ASSIGN,line_no);
                            $$->addChild($1);
                            ($$->getChildren().at(0))->addChild($3);
                            $$->addChild($6);
                            $$->setAttribute(OK_ARRAY,4);
                        }
                    |
                        identifier DOT identifier ASSIGN expression
                        {   $$=new TreeDefine(ASSIGN,line_no);
                            $$->addChild($1);
                            ($$->getChildren().at(0))->addChild($3);
                            $$->addChild($5);
                            $$->setAttribute(OK_RECORD,4);
                        }
                    ;
goto_stmt           :   GOTO  INTEGER
                        {   $$=new TreeDefine(GOTO,line_no);
                            $$->setAttribute($2);
                        }
                    ;
if_stmt             :   IF expression THEN stmt  else_clause
                        {   $$=new TreeDefine(IF,line_no);
                            $$->addChild($2);
                            $$->addChild($4);
                            $$->addChild($5);
                        }
                    |	IF expression  stmt  else_clause
                        {   $$=new TreeDefine(IF,line_no);
                            $$->addChild($2);
                            $$->addChild($3);
                            $$->addChild($4);
                             parsingErrors.push_back("error at line " + std::to_string(line_no) + ", lack of then");
                        }
                    ;
else_clause         :   {$$=nullptr;}
                    |   ELSE  stmt    {$$=$2;}
                    ;
repeat_stmt         :   REPEAT stmt_list UNTIL expression
                        {
                            $$=new TreeDefine(REPEAT,line_no);
                            $$->addChild($2);
                            $$->addChild($4);
                        }
                    |	{}
                    ;
while_stmt          :   WHILE expression DO stmt
                        {   $$=new TreeDefine(WHILE,line_no);
                            $$->addChild($2);
                            $$->addChild($4);
                        };
case_stmt           :   CASE expression OF case_expr_list END
                        {   $$=new TreeDefine(SK_CASE,line_no);
                            $$->addChild($2);
                            $$->addChild($4);
                        };
case_expr_list      :   case_expr_list  case_expr
                        {   TreeNode t=$1;
                            if(t!=nullptr){
                                while(t->getSibling()!=nullptr)
                                  t=t->getSibling();
                                t->setSibling($2);
                                $$=$1;
                            }
                            else
                                $$=$2;
                        }
                    |   case_expr   {$$=$1;};
case_expr           :   const_value COLON stmt SEMICOLON
                        {
                            $$=new TreeDefine(EK_CASE,line_no);
                            $$->addChild($1);
                            $$->addChild($3);
                        }
                    |   identifier  COLON stmt SEMICOLON
                        {
                            $$=new TreeDefine(EK_CASE,line_no);
                            $$->addChild($1);
                            $$->addChild($3);
                        };
for_stmt            :   FOR identifier ASSIGN expression TO expression DO stmt
                        {
                            $$=new TreeDefine(FOR,line_no);
                            $$->addChild($2);
                            $$->addChild($4);
                            $$->addChild($6);
                            $$->addChild($8);
                            $$->setAttribute(TO,4);
                        }
                    |   FOR identifier ASSIGN expression DOWNTO expression DO stmt
                        {
                            $$=new TreeDefine(FOR,line_no);
                            $$->addChild($2);
                            $$->addChild($4);
                            $$->addChild($6);
                            $$->addChild($8);
                            $$->setAttribute(DOWNTO,4);
                        };
proc_stmt           :   identifier
                        {   $$=new TreeDefine(PROC_ID,line_no);
                            $$->setAttribute($1->getAttribute());
                        }
                    |   identifier LP args_list RP
                        {   $$=new TreeDefine(PROC_ID,line_no);
                            $$->setAttribute($1->getAttribute());
                            $$->addChild($3);
                        }
                    |   READ LP factor RP
                        {
                            $$=new TreeDefine(PROC_SYS,line_no);
                            $$->setAttribute(READ,4);
                            $$->addChild($3);
                        }
                    |   WRITE LP args_list RP
                        {   $$=new TreeDefine(PROC_SYS,line_no);
                            $$->setAttribute(WRITE,4);
                            $$->addChild($3);
                        }
                    |   WRITELN
                        {   $$=new TreeDefine(PROC_SYS,line_no);
                            $$->setAttribute(WRITELN,4);
                        }
                    |   WRITELN LP args_list RP
                        {   $$=new TreeDefine(PROC_SYS,line_no);
                            $$->setAttribute(WRITELN,4);
                            $$->addChild($3);
                        };
args_list           :   args_list COMMA expression
                        {   TreeNode t=$1;
                            if(t!=nullptr){
                                while(t->getSibling()!=nullptr)
                                  t=t->getSibling();
                                t->setSibling($3);
                                $$=$1;
                            }
                            else
                                $$=$3;
                        }
                    |   expression  {$$=$1;};

expression          :   expression GE expr {   $$=new TreeDefine($1,$3,GE,line_no); }
                    |   expression GT expr {   $$=new TreeDefine($1,$3,GT,line_no); }
                    |   expression LE expr {   $$=new TreeDefine($1,$3,LE,line_no); }
                    |   expression LT expr {   $$=new TreeDefine($1,$3,LT,line_no); }
                    |   expression EQUAL expr {   $$=new TreeDefine($1,$3,EQUAL,line_no); }
                    |   expression UNEQUAL expr {  $$=new TreeDefine($1,$3,UNEQUAL,line_no); }
                    |   expr {   $$=$1;} ;

expr                :   expr PLUS term  {   $$=new TreeDefine($1,$3,PLUS,line_no); }
                    |   expr MINUS term  {  $$=new TreeDefine($1,$3,MINUS,line_no); }
                    |   expr OR term  {     $$=new TreeDefine($1,$3,OR,line_no); }
                    |   term {   $$=$1;} ;

term                :   term MUL factor {   $$=new TreeDefine($1,$3,MUL,line_no); }
                    |   term DIV factor {   $$=new TreeDefine($1,$3,DIV,line_no); }
                    |   term MOD factor {   $$=new TreeDefine($1,$3,MOD,line_no); }
                    |   term AND factor {   $$=new TreeDefine($1,$3,AND,line_no); }
                    |   factor {$$=$1;} ;

factor              :   identifier
                        {$$=$1;}
                    |   identifier LP args_list RP
                        {
                            $$=new TreeDefine(FUNC_ID,line_no);
                            $$->setAttribute($1->getAttribute());
                            $$->addChild($3);
                        }
                    |   const_value {$$=$1;}
                    |   LP expression RP    {$$=$2;}
                    |   NOT factor
                        {
                           $$=new TreeDefine($2,nullptr,NOT,line_no);
                        }
                    |   MINUS factor
                        {   $$=new TreeDefine($2, nullptr, MINUS, line_no);
                        }
                    |   identifier LB expression RB
                        {   $$=$1;
                            $$->addChild($3);
                            $$->setExpType(EARRAY);
                        }
                    |   identifier DOT identifier
                        {   $$=$1;
                            $$->addChild($3);
                            $$->setExpType(ERECORD);
                        }
                    |   ABS LP args_list RP
                        {
                            $$=new TreeDefine(ABS, $3,line_no);
                        }
                    |   CHR LP args_list RP
                        {
                            $$=new TreeDefine(CHR, $3,line_no);
                        }
                    |   ODD LP args_list RP
                        {
                            $$=new TreeDefine(ODD, $3,line_no);
                        }
                    |   ORD LP args_list RP
                        {

                            $$=new TreeDefine(ORD, $3,line_no);
                        }
                    |   PRED LP args_list RP
                        {
                            $$=new TreeDefine(PRED, $3,line_no);
                        }

                    |   SUCC LP args_list RP
                        {   $$=new TreeDefine(SUCC, $3,line_no);
                        }
                    ;
%%

void yyerror(const char *s) {
    std::cerr << "Error: " << s << " at line " << linesCounter << std::endl;
}

void parse(const std::string& inputFileName, ast::ProgramNode& ast, std::vector<std::string>& errors) {
    yyin = fopen(inputFileName, "r");

    if(yyin == nullptr) {
        std::cerr << "Cannot open file " << inputFileName << std::endl;
    }

    yyparse();
    fclose(yyin);

    ast = *resultAst;
    errors = parsingErrors;
}