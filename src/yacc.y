%{
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

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

#include "../context/context.hpp"

#undef YACC_DEBUG
#undef YACC_ENABLE_GOTO

Context* ctx = Context::getInstance();

ast::ProgramNode* resultAst;
std::vector<std::string> parsingErrors;
bool fatalError{false};

static void yyerror(const char *msg);
static int yyparse(void);
int yylex(void);

extern FILE* yyin;
extern uint64_t linesCounter;

bool isChar(const std::string& expr);
bool isInteger(const std::string& expr);
bool isBoolean(const std::string& expr);

bool nameAlreadyUsed(std::string name);
bool saveType(ast::IdentifierNode* typeName, const std::string& typeDef);
bool saveConstant(ast::IdentifierNode* constName, const std::string& constValue, const std::string& typeDef);
bool saveVariables(std::vector<ast::IdentifierNode*>* varNames, const std::string& typeDef);
bool saveRoutine(ast::RoutineDeclarationNode* routineDef, bool isForward);

bool isBasicType(const std::string& type);
bool isBasicOrEnumType(const std::string& type);
bool isBasicOrEnumOrArrayOrRecordType(const std::string& type);
bool isRangeType(const std::string& type);
bool isInEnum(const std::string& enumElement, const std::string& enumType);
bool isInAnyEnum(const std::string& enumElement);
bool isEnumSubRangeType(const std::string& enumElementPos, const std::string& enumType,
         const std::string& begin, const std::string& end);
bool isLeftValueCompatible(ast::ExpressionNode* expr);

bool isArrayIndexCompatible(const std::string& arrayType, ast::ExpressionNode* index);
bool isRecordFieldCompatible(const std::string& recordType, ast::IdentifierNode* field);
bool isFunctionArgumentsCompatible(const std::vector<LookupTable::ArgumentInfo>& expectedArgs, const std::vector<ast::ExpressionNode*>& givenArgs);
bool hasReturnValue(ast::RoutineNode* function, const std::string& functionName);
bool variableIsReassignedS(const std::string& varName, ast::StatementNode* stmt);
bool variableIsReassignedE(const std::string& varName, ast::ExpressionNode* expr);

std::string getArrayElementType(const std::string& arrayType);
std::string getRecordFieldType(const std::string& recordType, const std::string& field);
%}

%code requires
{
    #include <iostream>
    #include <stdlib.h>
    #include <string>
    #include <algorithm>

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
    std::vector<std::pair<ast::ExpressionNode*, ast::StatementNode*>*>* caseExprList;
    std::pair<ast::ExpressionNode*, ast::StatementNode*>* caseExpr;
    ast::ArgumentsListNode* argsList;
}

%start program

%token PROGRAM FUNCTION PROCEDURE CONST TYPE VAR BBEGIN END
%token IDENT_NAME INTEGER BOOLEAN CHAR STRING
%token TRUE FALSE MAXINT
%token READ READLN WRITE WRITELN MEMORYREAD MEMORYWRITE STACKREAD STACKWRITE ABS CHR ODD ORD PRED SUCC TOINT TOCHAR TOBOOL
%token IF THEN ELSE REPEAT UNTIL WHILE DO CASE TO DOWNTO FOR
%token EQUAL UNEQUAL GE GT LE LT ASSIGN PLUS MINUS MUL DIV OR AND NOT MOD
%token LB RB LP RP SEMICOLON DOT DOUBLEDOT COMMA COLON
%token INT_TYPE BOOL_TYPE CHAR_TYPE
%token ARRAY OF RECORD GOTO BREAK CONTINUE OTHERWISE
%token ERROR

%type <token> PROGRAM FUNCTION PROCEDURE CONST TYPE VAR BBEGIN END
%type <token> IDENT_NAME INTEGER BOOLEAN CHAR STRING
%type <token> TRUE FALSE MAXINT
%type <token> READ READLN WRITE WRITELN MEMORYREAD MEMORYWRITE STACKREAD STACKWRITE ABS CHR ODD ORD PRED SUCC TOINT TOCHAR TOBOOL
%type <token> IF THEN ELSE REPEAT UNTIL WHILE DO CASE TO DOWNTO FOR
%type <token> EQUAL UNEQUAL GE GT LE LT ASSIGN PLUS MINUS MUL DIV OR AND NOT MOD
%type <token> LB RB LP RP SEMICOLON DOT DOUBLEDOT COMMA COLON
%type <token> INT_TYPE BOOL_TYPE CHAR_TYPE
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
%type <compoundStatementNode> compound_stmt compound_loop_stmt
%type <statementNodeList> stmt_list loop_stmt_list
%type <statementNode> stmt loop_stmt no_label_stmt no_label_loop_stmt
%type <assignNode> assign_stmt
%type <gotoNode> goto_stmt
%type <caseNode> case_stmt case_loop_stmt
%type <forNode> for_head for_stmt
%type <whileNode> while_stmt
%type <repeatNode> repeat_stmt
%type <ifNode> if_stmt if_loop_stmt else_clause else_loop_clause
%type <callNode> proc_stmt
%type <expressionNode> expression expr term factor lvalue
%type <caseExprList> case_expr_list case_loop_expr_list
%type <caseExpr> case_expr case_loop_expr
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

        if(!saveRoutine($2, true)) {
            YYERROR;
        }

        $$ = $1;
        $$->push_back($2);
    }
|
    routine_part proc_decl {
       #ifdef YACC_DEBUG
           std::cout << "Yacc debug: Parse routine part with proc decl 1 " << $2->getName() << std::endl;
       #endif

       if(!saveRoutine($2, true)) {
           YYERROR;
       }

       $$ = $1;
       $$->push_back($2);
    }
|
    fun_decl {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine part with fun decl 2 " << $1->getName() << std::endl;
        #endif

        if(!saveRoutine($1, true)) {
            YYERROR;
        }

        $$ = new std::vector<ast::RoutineDeclarationNode*>();
        $$->push_back($1);
    }
|
    proc_decl {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse routine part with proc decl 2 " << $1->getName() << std::endl;
        #endif

        if(!saveRoutine($1, true)) {
            YYERROR;
        }

        $$ = new std::vector<ast::RoutineDeclarationNode*>();
        $$->push_back($1);
    }
;

fun_decl :
    fun_head SEMICOLON routine SEMICOLON {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun decl 1" << std::endl;
        #endif

        if(!hasReturnValue($3, $1->getName())) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", function should have one return value");
            fatalError = true;
            YYERROR;
        }

        ctx->getLookupTable().undefineTypesVarsRoutines(ctx->getCurrentScope());
        ctx->popScope();

        $$ = $1;
        $$->setRoutine(std::unique_ptr<ast::RoutineNode>($3));
        $$->setRoutineType(ast::RoutineDeclarationNode::RoutineType::FUNCTION);
    }
|
    fun_head SEMICOLON routine {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse fun decl 2" << std::endl;
        #endif

        if(!hasReturnValue($3, $1->getName())) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", function should have one return value");
            fatalError = true;
            YYERROR;
        }

        ctx->getLookupTable().undefineTypesVarsRoutines(ctx->getCurrentScope());
        ctx->popScope();

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

        if(!hasReturnValue($2, $1->getName())) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", function should have one return value");
            fatalError = true;
            YYERROR;
        }

        ctx->getLookupTable().undefineTypesVarsRoutines(ctx->getCurrentScope());
        ctx->popScope();

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

        if(!hasReturnValue($2, $1->getName())) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", function should have one return value");
            fatalError = true;
            YYERROR;
        }

        ctx->getLookupTable().undefineTypesVarsRoutines(ctx->getCurrentScope());
        ctx->popScope();

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

        ctx->pushScope(*$2.stringValue);

        try {
            if(!isBasicOrEnumOrArrayOrRecordType($5->flat())) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", invalid return type");
                fatalError = true;
                YYERROR;
            }
        }
        catch(std::runtime_error& err) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
            fatalError = true;
            YYERROR;
        }

        std::string funType;
        try { funType = $5->flat(); }
        catch(std::runtime_error& err) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
            fatalError = true;
            YYERROR;
        }

        std::vector<ast::IdentifierNode*> funNameVector{new ast::IdentifierNode(*$2.stringValue)};
        if(!saveVariables(&funNameVector, funType)) {
            YYERROR;
        }

        for(const auto& param : *$3->getParams()) {
            std::string paramType;
            try { paramType = param->getParamsType()->flat(); }
            catch(std::runtime_error& err) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
                fatalError = true;
                YYERROR;
            }

            if(!saveVariables(param->getParams().get(), paramType)) {
                YYERROR;
            }
        }

        std::string name{*$2.stringValue};
        $$ = new ast::RoutineDeclarationNode(ast::RoutineDeclarationNode::RoutineType::FUNCTION, std::move(name), $3, $5, nullptr);

        if(!saveRoutine($$, false)) {
            YYERROR;
        }
    }
;

proc_decl :
    proc_head SEMICOLON routine SEMICOLON {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse proc decl" << std::endl;
        #endif

        ctx->getLookupTable().undefineTypesVarsRoutines(ctx->getCurrentScope());
        ctx->popScope();

        $$ = $1;
        $$->setRoutine(std::unique_ptr<ast::RoutineNode>($3));
        $$->setRoutineType(ast::RoutineDeclarationNode::RoutineType::PROCEDURE);
    }
|
    proc_head routine SEMICOLON {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse proc decl" << std::endl;
        #endif

        ctx->getLookupTable().undefineTypesVarsRoutines(ctx->getCurrentScope());
        ctx->popScope();

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

        ctx->getLookupTable().undefineTypesVarsRoutines(ctx->getCurrentScope());
        ctx->popScope();

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

        ctx->getLookupTable().undefineTypesVarsRoutines(ctx->getCurrentScope());
        ctx->popScope();

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

        ctx->pushScope(*$2.stringValue);

        for(const auto& param : *$3->getParams()) {
            std::string paramType;
            try { paramType = param->getParamsType()->flat(); }
            catch(std::runtime_error& err) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
                fatalError = true;
                YYERROR;
            }

            if(!saveVariables(param->getParams().get(), paramType)) {
                YYERROR;
            }
        }

        std::string name{*$2.stringValue};
        $$ = new ast::RoutineDeclarationNode(ast::RoutineDeclarationNode::RoutineType::PROCEDURE, std::move(name), $3, nullptr, nullptr);

        if(!saveRoutine($$, false)) {
            YYERROR;
        }
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

        try {
            if(!isBasicOrEnumOrArrayOrRecordType($4->flat())) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", invalid parameter type");
                fatalError = true;
                YYERROR;
            }
        }
        catch(std::runtime_error& err) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", invalid parameter type");
            fatalError = true;
            YYERROR;
        }

        $$ = new ast::ParamsGroupNode(ast::ParamsGroupNode::PassType::PASS_BY_REFERENCE, $2, $4);
    }
|
    name_list COLON simple_type {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse params type 2" << std::endl;
        #endif

        try {
            if(!isBasicOrEnumOrArrayOrRecordType($3->flat())) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", invalid parameter type");
                fatalError = true;
                YYERROR;
            }
        }
        catch(std::runtime_error& err) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", invalid parameter type");
            fatalError = true;
            YYERROR;
        }

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

        std::string varType;
        try { varType = $3->flat(); }
        catch(std::runtime_error& err) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
            fatalError = true;
            YYERROR;
        }

        if(isRangeType(varType)) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", invalid variable type");
            fatalError = true;
            YYERROR;
        }

        if(!saveVariables($1, varType)) {
            YYERROR;
        }

        $$ = new std::pair<std::vector<ast::IdentifierNode*>*, ast::TypeNode*>($1, $3);
    }
|
    name_list COLON type_decl {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse var decl 2" << std::endl;
        #endif

        std::string varType;
        try { varType = $3->flat(); }
        catch(std::runtime_error& err) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
            fatalError = true;
            YYERROR;
        }

        if(isRangeType(varType)) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", invalid variable type");
            fatalError = true;
            YYERROR;
        }

        if(!saveVariables($1, varType)) {
            YYERROR;
        }

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

        try {
            if(!saveConstant($1, $3->flat(), $3->flatType())) {
                YYERROR;
            }
        }
        catch(std::runtime_error& err) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
            fatalError = true;
            YYERROR;
        }

        try {
            if($3->flatType() == "string") {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", const type must be basic");
                fatalError = true;
                YYERROR;
            }
        }
        catch(std::runtime_error& err) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
            fatalError = true;
            YYERROR;
        }

        $$ = new std::pair<ast::IdentifierNode*, ast::ConstantNode*>($1, $3);
    }
|
    identifier EQUAL const_value {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse const expr 2" << std::endl;
        #endif

        try {
            if(!saveConstant($1, $3->flat(), $3->flatType())) {
                YYERROR;
            }
        }
        catch(std::runtime_error& err) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
            fatalError = true;
            YYERROR;
        }

        try {
            if($3->flatType() == "string") {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", const type must be basic");
                fatalError = true;
                YYERROR;
            }
        }
        catch(std::runtime_error& err) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
            fatalError = true;
            YYERROR;
        }

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

        std::string typeType;
        try { typeType = $3->flat(); }
        catch(std::runtime_error& err) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
            fatalError = true;
            YYERROR;
        }

        if(!saveType($1, typeType)) {
            YYERROR;
        }

        $$ = new std::pair<ast::IdentifierNode*, ast::TypeNode*>($1, $3);
    }
|
    identifier EQUAL type_decl {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse type def 2" << std::endl;
        #endif

        std::string typeType;
        try { typeType = $3->flat(); }
        catch(std::runtime_error& err) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
            fatalError = true;
            YYERROR;
        }

        if(!saveType($1, typeType)) {
            YYERROR;
        }

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

        std::set<std::string> fields;
        for(std::size_t i = 0; i < $2->size(); i++) {
            for(std::size_t j = 0; j < $2->at(i)->first->size(); j++) {
                std::string field = $2->at(i)->first->at(j)->getName();
                if(fields.find(field) != fields.end()) {
                    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", field name `" + field + "` duplication");
                    fatalError = true;
                    YYERROR;
                }
                fields.insert(field);
            }
        }

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

        try {
            if(!isBasicOrEnumType($3->flat()) && !isRangeType($3->flat())) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", invalid variable type");
                fatalError = true;
                YYERROR;
            }
        }
        catch(std::runtime_error& err) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
            fatalError = true;
            YYERROR;
        }

        try {
            if(!isBasicOrEnumOrArrayOrRecordType($6->flat())) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", invalid return type");
                fatalError = true;
                YYERROR;
            }
        }
        catch(std::runtime_error& err) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
            fatalError = true;
            YYERROR;
        }

        if($3->getRepresentation() == ast::SimpleTypeNode::Representation::CONST_RANGE) {
            ast::ConstRangeTypeNode* range = dynamic_cast<ast::ConstRangeTypeNode*>($3);
            const std::string& leftType = range->getLowerBound()->flatType();
            const std::string& rightType = range->getUpperBound()->flatType();
            const std::string& leftVal = range->getLowerBound()->flat();
            const std::string& rightVal = range->getUpperBound()->flat();
            if(leftType != rightType) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", array range bounds must have the same type");
                fatalError = true;
                YYERROR;
            }
            else if(leftType == "string" || rightType == "string") {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", array range bounds cannot be string");
                fatalError = true;
                YYERROR;
            }

            if(isInteger(leftVal)) {
                int int1 = std::atoi(leftVal.c_str());
                int int2 = std::atoi(rightVal.c_str());
                if(int2 < int1) {
                    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", invalid array range bounds");
                    fatalError = true;
                    YYERROR;
                }
            }

            if(isChar(leftVal)) {
                int char1 = static_cast<int>(leftVal.at(0));
                int char2 = static_cast<int>(rightVal.at(0));
                if(char2 < char1) {
                    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", invalid array range bounds");
                    fatalError = true;
                    YYERROR;
                }
            }

            if(leftVal == "true" && rightVal == "false") {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", invalid array range bounds");
                fatalError = true;
                YYERROR;
            }
        }

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
            std::cout << "Yacc debug: Parse simple type - enum" << std::endl;
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

        $$ = new ast::BasicTypeNode(ast::BasicTypeNode::BasicType::INTEGER);
    }
|
    BOOL_TYPE {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - bool" << std::endl;
        #endif

        $$ = new ast::BasicTypeNode(ast::BasicTypeNode::BasicType::BOOLEAN);
    }
|
    CHAR_TYPE {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse simple type - char" << std::endl;
        #endif

        $$ = new ast::BasicTypeNode(ast::BasicTypeNode::BasicType::CHAR);
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

compound_loop_stmt :
    BBEGIN loop_stmt_list END {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse loop compound statement 1" << std::endl;
        #endif

        $$ = new ast::CompoundStatementNode($2);
    }
|
    BBEGIN loop_stmt_list {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse loop compound statement 2" << std::endl;
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

loop_stmt_list :
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty loop statement list" << std::endl;
        #endif

        $$ = new std::vector<ast::StatementNode*>();
    }
|
    loop_stmt_list loop_stmt SEMICOLON {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse loop statement list 1" << std::endl;
        #endif

        $$ = $1;
        $$->push_back($2);
    }
|
    loop_stmt_list loop_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse loop statement list 2" << std::endl;
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

        #ifndef YACC_ENABLE_GOTO
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", goto is disabled");
            fatalError = true;
            YYERROR;
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

loop_stmt :
    INTEGER COLON no_label_loop_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse loop statement with label " << $1.numericalValue << std::endl;
        #endif

        #ifndef YACC_ENABLE_GOTO
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", goto is disabled");
            fatalError = true;
            YYERROR;
        #endif

        $$ = $3;
        $$->setLabel($1.numericalValue);
    }
|
    no_label_loop_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse loop statement without label" << std::endl;
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

        #ifndef YACC_ENABLE_GOTO
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", goto is disabled");
            fatalError = true;
            YYERROR;
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
;

no_label_loop_stmt :
    assign_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label loop statement - assign" << std::endl;
        #endif

        $$=$1;
    }
|
    compound_loop_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label loop statement - compound" << std::endl;
        #endif

        $$ = $1;
    }
|
    goto_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label loop statement - goto" << std::endl;
        #endif

        $$ = $1;
    }
|
    if_loop_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label loop statement - if" << std::endl;
        #endif

        $$ = $1;
    }
|
    repeat_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label loop statement - repeat" << std::endl;
        #endif

        $$ = $1;
    }
|
    while_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label loop statement - while" << std::endl;
        #endif

        $$ = $1;
    }
|
    case_loop_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label loop statement - case" << std::endl;
        #endif

        $$ = $1;
    }
|
    for_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label loop statement - for" << std::endl;
        #endif

        $$ = $1;
    }
|
    proc_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label loop statement - proc" << std::endl;
        #endif

        $$ = $1;
    }
|
    BREAK {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label loop statement - break" << std::endl;
        #endif

        $$ = new ast::BreakNode();
    }
|
    CONTINUE {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse no label loop statement - continue" << std::endl;
        #endif

        $$ = new ast::ContinueNode();
    }
;

assign_stmt :
    lvalue ASSIGN expression {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse assign statement" << std::endl;
        #endif

        if(!isLeftValueCompatible($1)) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", left side of assignment must be assignable");
            fatalError = true;
            YYERROR;
        }
        else if($1->getInferredType() != $3->getInferredType()) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", both sides should be equal type");
            std::cout << $1->getInferredType() << "  " << $3->getInferredType() << std::endl;
            fatalError = true;
            YYERROR;
        }
        else {
            $$ = new ast::AssignNode($1, $3);
        }
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

        if($2->getInferredType() == "boolean") {
            $$ = new ast::IfNode($2, $4, $5);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", if condition must be boolean expression");
            fatalError = true;
            YYERROR;
        }
    }
|
    IF expression stmt else_clause {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse if statement 2" << std::endl;
        #endif

        if($2->getInferredType() == "boolean") {
            $$ = new ast::IfNode($2, $3, $4);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of then");
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", if condition must be boolean expression");
            fatalError = true;
            YYERROR;
        }
    }
;

if_loop_stmt :
    IF expression THEN loop_stmt else_loop_clause {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse if loop statement 1" << std::endl;
        #endif

        if($2->getInferredType() == "boolean") {
            $$ = new ast::IfNode($2, $4, $5);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", if condition must be boolean expression");
            fatalError = true;
            YYERROR;
        }
    }
|
    IF expression loop_stmt else_loop_clause {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse if loop statement 2" << std::endl;
        #endif

        if($2->getInferredType() == "boolean") {
            $$ = new ast::IfNode($2, $3, $4);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", lack of then");
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", if condition must be boolean expression");
            fatalError = true;
            YYERROR;
        }
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

else_loop_clause :
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty else loop clause" << std::endl;
        #endif

        $$ = new ast::IfNode(nullptr, nullptr);
    }
|
    ELSE loop_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse else loop clause" << std::endl;
        #endif

        $$ = new ast::IfNode(nullptr, nullptr, $2);
    }
;

repeat_stmt :
    REPEAT loop_stmt_list UNTIL expression {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse repeat statement" << std::endl;
        #endif

        if($4->getInferredType() == "boolean") {
            $$ = new ast::RepeatNode($4, new ast::CompoundStatementNode($2));
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", repeat condition must be boolean expression");
            fatalError = true;
            YYERROR;
        }
    }
|
    {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse empty repeat statement" << std::endl;
        #endif
    }
;

while_stmt :
    WHILE expression DO loop_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse while statement" << std::endl;
        #endif

        if($2->getInferredType() == "boolean") {
            $$ = new ast::WhileNode($2, $4);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", while condition must be boolean expression");
            fatalError = true;
            YYERROR;
        }
    }
;

case_stmt :
    CASE expression OF case_expr_list END {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case statement" << std::endl;
        #endif

        if(!isBasicOrEnumType($2->getInferredType())) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", case expression must be integer, char, boolean or enum type");
            fatalError = true;
            YYERROR;
        }

        bool otherwiseFound{false};
        for(const auto& caseExpr : *$4) {
            if(caseExpr->first != nullptr) {
                if(otherwiseFound) {
                    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", otherwise must be last label");
                    fatalError = true;
                    YYERROR;
                }

                if(caseExpr->first->getOperation() != ast::ExpressionNode::Operation::SPECIAL) {
                    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", case value must be constant");
                    fatalError = true;
                    YYERROR;
                }

                ast::SpecialExpressionNode* specialExpr = dynamic_cast<ast::SpecialExpressionNode*>(caseExpr->first);
                if(specialExpr->getFunctionName() != ast::SpecialExpressionNode::FunctionName::CONST &&
                    specialExpr->getFunctionName() != ast::SpecialExpressionNode::FunctionName::ENUM_ELEMENT) {
                    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", case value must be constant");
                    fatalError = true;
                    YYERROR;
                }

                if(specialExpr->getInferredType() != $2->getInferredType()) {
                    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", case expression must be the same type as case value");
                    fatalError = true;
                    YYERROR;
                }
            }
            else if(otherwiseFound) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", otherwise label can be used only once");
                fatalError = true;
                YYERROR;
            }
            else {
                otherwiseFound = true;
            }
        }

        $$ = new ast::CaseNode($2, $4);
    }
;

case_loop_stmt :
    CASE expression OF case_loop_expr_list END {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case loop statement" << std::endl;
        #endif

        if(!isBasicOrEnumType($2->getInferredType())) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", case expression must be integer, char, boolean or enum type");
            fatalError = true;
            YYERROR;
        }

        bool otherwiseFound{false};
        for(const auto& caseExpr : *$4) {
            if(caseExpr->first != nullptr) {
                if(otherwiseFound) {
                    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", otherwise must be last label");
                    fatalError = true;
                    YYERROR;
                }

                if(caseExpr->first->getOperation() != ast::ExpressionNode::Operation::SPECIAL) {
                    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", case value must be constant");
                    fatalError = true;
                    YYERROR;
                }

                ast::SpecialExpressionNode* specialExpr = dynamic_cast<ast::SpecialExpressionNode*>(caseExpr->first);
                if(specialExpr->getFunctionName() != ast::SpecialExpressionNode::FunctionName::CONST &&
                    specialExpr->getFunctionName() != ast::SpecialExpressionNode::FunctionName::ENUM_ELEMENT) {
                    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", case value must be constant");
                    fatalError = true;
                    YYERROR;
                }

                if(specialExpr->getInferredType() != $2->getInferredType()) {
                    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", case expression must be the same type as case value");
                    fatalError = true;
                    YYERROR;
                }
            }
            else if(otherwiseFound) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", otherwise label can be used only once");
                fatalError = true;
                YYERROR;
            }
            else {
                otherwiseFound = true;
            }
        }

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

        $$ = new std::vector<std::pair<ast::ExpressionNode*, ast::StatementNode*>*>();
        $$->push_back($1);
    }
;

case_loop_expr_list :
    case_loop_expr_list case_loop_expr {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case loop expr list 1" << std::endl;
        #endif

        $$ = $1;
        $$->push_back($2);
    }
|
    case_loop_expr {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case loop expr list 2" << std::endl;
        #endif

        $$ = new std::vector<std::pair<ast::ExpressionNode*, ast::StatementNode*>*>();
        $$->push_back($1);
    }
;

case_expr :
    expression COLON stmt SEMICOLON {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr 1" << std::endl;
        #endif

        $$ = new std::pair<ast::ExpressionNode*, ast::StatementNode*>($1, $3);
    }
|
    OTHERWISE stmt SEMICOLON {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case expr 3" << std::endl;
        #endif

        $$ = new std::pair<ast::ExpressionNode*, ast::StatementNode*>(nullptr, $2);
    }
;

case_loop_expr:
    expression COLON loop_stmt SEMICOLON {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case loop expr 1" << std::endl;
        #endif

        $$ = new std::pair<ast::ExpressionNode*, ast::StatementNode*>($1, $3);
    }
|
    OTHERWISE loop_stmt SEMICOLON {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse case loop expr 3" << std::endl;
        #endif

        $$ = new std::pair<ast::ExpressionNode*, ast::StatementNode*>(nullptr, $2);
    }
;

for_stmt :
    for_head loop_stmt {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse for statement" << std::endl;
        #endif

        if(variableIsReassignedS($1->getIterator()->getName(), $2)) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", loop variable `" + $1->getIterator()->getName() + "` cannot be reassigned");
            fatalError = true;
            YYERROR;
        }

        $$ = $1;
        $$->setStatements(std::unique_ptr<ast::StatementNode>($2));

        ctx->getLookupTable().unDefineVariable($1->getIterator()->getName(), ctx->getCurrentScope());
    }
;

for_head :
    FOR identifier ASSIGN expression TO expression DO {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse for head 1" << std::endl;
        #endif

        if($4->getInferredType() != $6->getInferredType()) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", for begin and end values must be the same type");
            fatalError = true;
            YYERROR;
        }
        else if(!isBasicOrEnumType($4->getInferredType())) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", for begin and end values must be integer, char, boolean or enum type");
            fatalError = true;
            YYERROR;
        }
        else {
            if(!saveVariables(new std::vector<ast::IdentifierNode*>{$2}, $4->getInferredType())) {
                YYERROR;
            }
            $$ = new ast::ForNode($2, $4, $6, nullptr, ast::ForNode::Direction::INCREMENT);
        }
    }
|
    FOR identifier ASSIGN expression DOWNTO expression DO {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse for head 2" << std::endl;
        #endif

        if($4->getInferredType() != $6->getInferredType()) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", for begin and end values must be the same type");
            fatalError = true;
            YYERROR;
        }
        else if(!isBasicOrEnumType($4->getInferredType())) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", for begin and end values must be integer, char, boolean or enum type");
            fatalError = true;
            YYERROR;
        }
        else {
            if(!saveVariables(new std::vector<ast::IdentifierNode*>{$2}, $4->getInferredType())) {
                YYERROR;
            }
            $$ = new ast::ForNode($2, $4, $6, nullptr, ast::ForNode::Direction::DECREMENT);
        }
    }
;

proc_stmt :
    identifier {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse procedure statement" << std::endl;
        #endif

        if(!ctx->getLookupTable().isRoutineDefined($1->getName(), ctx->getCurrentScope())) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", routine `" + $1->getName() + "` is not defined");
            fatalError = true;
            YYERROR;
        }
        else if(!ctx->getLookupTable().getRoutine($1->getName(), ctx->getCurrentScope()).args.empty()) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", missing arguments");
            fatalError = true;
            YYERROR;
        }
        else {
            $$ = new ast::UserDefineCallNode($1, nullptr);
        }
    }
|
    identifier LP args_list RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse procedure statement with args" << std::endl;
        #endif

        if(!ctx->getLookupTable().isRoutineDefined($1->getName(), ctx->getCurrentScope())) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", routine `" + $1->getName() + "` is not defined");
            fatalError = true;
            YYERROR;
        }
        else if(!isFunctionArgumentsCompatible(ctx->getLookupTable().getRoutine($1->getName(), ctx->getCurrentScope()).args, $3->getArguments())) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", passed incompatible arguments");
            fatalError = true;
            YYERROR;
        }
        else {
            $$ = new ast::UserDefineCallNode($1, $3);
        }
    }
|
    READ LP factor RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse read statement" << std::endl;
        #endif

        if(!isLeftValueCompatible($3)) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for read - assignable argument expected");
            fatalError = true;
            YYERROR;
        }
        else if(!isBasicType($3->getInferredType())) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for read - integer, char or boolean expected");
            fatalError = true;
            YYERROR;
        }
        else {
            ast::ArgumentsListNode* args = new ast::ArgumentsListNode();
            args->addArgument($3);
            $$ = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::READ, args);
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

        bool allOk = true;
        for(auto arg : $3->getArguments()) {
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
            $$ = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITE, $3);
        }
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

        bool allOk = true;
        for(auto arg : $3->getArguments()) {
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
            $$ = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::WRITELN, $3);
        }
    }
|
    MEMORYREAD LP args_list RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse memory read statement" << std::endl;
        #endif

        if($3->getArguments().size() == 3) {
            if($3->getArguments().at(0)->getInferredType() != "integer") {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory read - first argument should be integer");
                fatalError = true;
                YYERROR;
            }
            else if($3->getArguments().at(1)->getInferredType() != "integer") {
                 parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory read - second argument should be integer");
                 fatalError = true;
                 YYERROR;
            }
            else if(!isLeftValueCompatible($3->getArguments().at(2))) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory read - assignable argument expected");
                fatalError = true;
                YYERROR;
            }
            else if(!isBasicType($3->getArguments().at(2)->getInferredType())) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory read - integer, char or boolean expected");
                fatalError = true;
                YYERROR;
            }
            else {
                $$ = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::MEMORY_READ, $3);
            }
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for memory read - 3 arguments expected");
            fatalError = true;
            YYERROR;
        }
    }
|
    MEMORYWRITE LP args_list RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse memory write statement" << std::endl;
        #endif

        if($3->getArguments().size() == 3) {
            if($3->getArguments().at(0)->getInferredType() != "integer") {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory write - first argument should be integer");
                fatalError = true;
                YYERROR;
            }
            else if($3->getArguments().at(1)->getInferredType() != "integer") {
                 parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory write - second argument should be integer");
                 fatalError = true;
                 YYERROR;
            }
            else if(!isBasicType($3->getArguments().at(2)->getInferredType())) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for memory write - integer, char or boolean expected");
                fatalError = true;
                YYERROR;
            }
            else {
                $$ = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::MEMORY_WRITE, $3);
            }
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for memory write - 3 arguments expected");
            fatalError = true;
            YYERROR;
        }
    }
|
    STACKREAD LP args_list RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse stack read statement" << std::endl;
        #endif

        if($3->getArguments().size() == 3) {
            if($3->getArguments().at(0)->getInferredType() != "integer") {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack read - first argument should be integer");
                fatalError = true;
                YYERROR;
            }
            else if($3->getArguments().at(1)->getInferredType() != "integer") {
                 parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack read - second argument should be integer");
                 fatalError = true;
                 YYERROR;
            }
            else if(!isLeftValueCompatible($3->getArguments().at(2))) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack read - assignable argument expected");
                fatalError = true;
                YYERROR;
            }
            else if(!isBasicType($3->getArguments().at(2)->getInferredType())) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack read - integer, char or boolean expected");
                fatalError = true;
                YYERROR;
            }
            else {
                $$ = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::STACK_READ, $3);
            }
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for stack read - 3 arguments expected");
            fatalError = true;
            YYERROR;
        }
    }
|
    STACKWRITE LP args_list RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse stack write statement" << std::endl;
        #endif

        if($3->getArguments().size() == 3) {
            if($3->getArguments().at(0)->getInferredType() != "integer") {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack write - first argument should be integer");
                fatalError = true;
                YYERROR;
            }
            else if($3->getArguments().at(1)->getInferredType() != "integer") {
                 parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack write - second argument should be integer");
                 fatalError = true;
                 YYERROR;
            }
            else if(!isBasicType($3->getArguments().at(2)->getInferredType())) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for stack write - integer, char or boolean expected");
                fatalError = true;
                YYERROR;
            }
            else {
                $$ = new ast::BuiltinCallNode(ast::BuiltinCallNode::FunctionName::STACK_WRITE, $3);
            }
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for stack write - 3 arguments expected");
            fatalError = true;
            YYERROR;
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

        if($1->getInferredType() == $3->getInferredType() && isBasicType($1->getInferredType())) {
            $$ = new ast::MathExpressionNode($1, $3, ast::MathExpressionNode::FunctionName::GREATER_EQUAL, "boolean");
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for greater or equal - matching types(integer, char, boolean) expected");
            fatalError = true;
            YYERROR;
        }
    }
|
    expression GT expr {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with greater" << std::endl;
        #endif

        if($1->getInferredType() == $3->getInferredType() && isBasicType($1->getInferredType())) {
            $$ = new ast::MathExpressionNode($1, $3, ast::MathExpressionNode::FunctionName::GREATER, "boolean");
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for greater - matching types(integer, char, boolean) expected");
            fatalError = true;
            YYERROR;
        }
    }
|
    expression LE expr {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with less or equal" << std::endl;
        #endif

        if($1->getInferredType() == $3->getInferredType() && isBasicType($1->getInferredType())) {
            $$ = new ast::MathExpressionNode($1, $3, ast::MathExpressionNode::FunctionName::LESS_EQUAL, "boolean");
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for less or equal - matching types(integer, char, boolean) expected");
            fatalError = true;
            YYERROR;
        }
    }
|
    expression LT expr {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with less" << std::endl;
        #endif

        if($1->getInferredType() == $3->getInferredType() && isBasicType($1->getInferredType())) {
            $$ = new ast::MathExpressionNode($1, $3, ast::MathExpressionNode::FunctionName::LESS, "boolean");
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for less - matching types(integer, char, boolean) expected");
            fatalError = true;
            YYERROR;
        }
    }
|
    expression EQUAL expr {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with equal" << std::endl;
        #endif

        if($1->getInferredType() == $3->getInferredType() && isBasicType($1->getInferredType())) {
            $$ = new ast::MathExpressionNode($1, $3, ast::MathExpressionNode::FunctionName::EQUAL, "boolean");
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for equal - matching types(integer, char, boolean) expected");
            fatalError = true;
            YYERROR;
        }
    }
|
    expression UNEQUAL expr {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with not equal" << std::endl;
        #endif

        if($1->getInferredType() == $3->getInferredType() && isBasicType($1->getInferredType())) {
            $$ = new ast::MathExpressionNode($1, $3, ast::MathExpressionNode::FunctionName::NOT_EQUAL, "boolean");
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for not equal - matching types(integer, char, boolean) expected");
            fatalError = true;
            YYERROR;
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

        if($1->getInferredType() == "integer" && $3->getInferredType() == "integer") {
            $$ = new ast::MathExpressionNode($1, $3, ast::MathExpressionNode::FunctionName::ADDITION, $1->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for addition - integer expected");
            fatalError = true;
            YYERROR;
        }
    }
|
    expr MINUS term {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with subtraction" << std::endl;
        #endif

        if($1->getInferredType() == "integer" && $3->getInferredType() == "integer") {
            $$ = new ast::MathExpressionNode($1, $3, ast::MathExpressionNode::FunctionName::SUBTRACTION, $1->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for subtraction - integer expected");
            fatalError = true;
            YYERROR;
        }
    }
|
    expr OR term {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse expression with or" << std::endl;
        #endif

        if($1->getInferredType() == "boolean" && $3->getInferredType() == "boolean") {
            $$ = new ast::MathExpressionNode($1, $3, ast::MathExpressionNode::FunctionName::OR, "boolean");
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for or - boolean expected");
            fatalError = true;
            YYERROR;
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

        if($1->getInferredType() == "integer" && $3->getInferredType() == "integer") {
            $$ = new ast::MathExpressionNode($1, $3, ast::MathExpressionNode::FunctionName::MULTIPLICATION, $1->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for mul - integer expected");
            fatalError = true;
            YYERROR;
        }
    }
|
    term DIV factor {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with division" << std::endl;
        #endif

        if($1->getInferredType() == "integer" && $3->getInferredType() == "integer") {
            $$ = new ast::MathExpressionNode($1, $3, ast::MathExpressionNode::FunctionName::DIVISION, $1->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for div - integer expected");
            fatalError = true;
            YYERROR;
        }
    }
|
    term MOD factor {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with modulus" << std::endl;
        #endif

        if($1->getInferredType() == "integer" && $3->getInferredType() == "integer") {
            $$ = new ast::MathExpressionNode($1, $3, ast::MathExpressionNode::FunctionName::MODULUS, $1->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for mod - integer expected");
            fatalError = true;
            YYERROR;
        }
    }
|
    term AND factor {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse term with and" << std::endl;
        #endif

        if($1->getInferredType() == "boolean" && $3->getInferredType() == "boolean") {
            $$ = new ast::MathExpressionNode($1, $3, ast::MathExpressionNode::FunctionName::AND, "boolean");
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for and - boolean expected");
            fatalError = true;
            YYERROR;
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
    identifier LP args_list RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - function call" << std::endl;
        #endif

        if(!ctx->getLookupTable().isRoutineDefined($1->getName(), ctx->getCurrentScope())) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", routine " + $1->getName() + " is not defined");
            fatalError = true;
            YYERROR;
        }
        else {
            $$ = new ast::SpecialExpressionNode($1, $3, ast::SpecialExpressionNode::FunctionName::CALL,
                ctx->getLookupTable().getRoutine($1->getName(), ctx->getCurrentScope()).type);
        }
    }

|
    lvalue {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - lvalue" << std::endl;
        #endif

        $$ = $1;
    }
|
    const_value {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - const value" << std::endl;
        #endif

        ast::ConstantNode* constant = dynamic_cast<ast::ConstantNode*>($1);

        $$ = new ast::SpecialExpressionNode($1, ast::SpecialExpressionNode::FunctionName::CONST, constant->flatType());
    }
|
    LP expression RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - parentheses" << std::endl;
        #endif

        $$ = new ast::SpecialExpressionNode($2, ast::SpecialExpressionNode::FunctionName::PARENTHESIS, $2->getInferredType());
    }
|
    NOT factor {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - not" << std::endl;
        #endif

        if($2->getInferredType() == "boolean") {
            $$ = new ast::MathExpressionNode($2, ast::MathExpressionNode::FunctionName::NEGATION, $2->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for not - boolean expected");
            fatalError = true;
            YYERROR;
        }
    }
|
    MINUS factor {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - negation" << std::endl;
        #endif

        if($2->getInferredType() == "integer") {
            $$ = new ast::MathExpressionNode($2, ast::MathExpressionNode::FunctionName::NEGATION, $2->getInferredType());
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for negation - integer expected");
            fatalError = true;
            YYERROR;
        }
    }
|
    ABS LP args_list RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - abs" << std::endl;
        #endif

        if($3->getArguments().size() != 1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for abs");
            fatalError = true;
            YYERROR;
        }
        else {
            ast::ExpressionNode* arg = $3->getArguments().front();
            if(arg->getInferredType() == "integer") {
                $$ = new ast::SpecialExpressionNode($3, ast::SpecialExpressionNode::FunctionName::ABS, "integer");
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for abs - integer expected");
                fatalError = true;
                YYERROR;
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
            YYERROR;
        }
        else {
            ast::ExpressionNode* arg = $3->getArguments().front();
            if(arg->getInferredType() == "integer") {
                $$ = new ast::SpecialExpressionNode($3, ast::SpecialExpressionNode::FunctionName::CHR, "char");
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for chr - integer expected");
                fatalError = true;
                YYERROR;
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
            YYERROR;
        }
        else {
            ast::ExpressionNode* arg = $3->getArguments().front();
            if(arg->getInferredType() == "integer") {
                $$ = new ast::SpecialExpressionNode($3, ast::SpecialExpressionNode::FunctionName::ODD, "boolean");
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for odd - integer expected");
                fatalError = true;
                YYERROR;
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
            YYERROR;
        }
        else {
            ast::ExpressionNode* arg = $3->getArguments().front();
            if(arg->getInferredType() == "char") {
                $$ = new ast::SpecialExpressionNode($3, ast::SpecialExpressionNode::FunctionName::ORD, "integer");
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for ord - char expected");
                fatalError = true;
                YYERROR;
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
            YYERROR;
        }
        else {
            ast::ExpressionNode* arg = $3->getArguments().front();
            if(arg->getInferredType() == "integer" || arg->getInferredType() == "char") {
                $$ = new ast::SpecialExpressionNode($3, ast::SpecialExpressionNode::FunctionName::PRED, arg->getInferredType());
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for pred - integer or char expected");
                fatalError = true;
                YYERROR;
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
            YYERROR;
        }
        else {
            ast::ExpressionNode* arg = $3->getArguments().front();
            if(arg->getInferredType() == "integer" || arg->getInferredType() == "char") {
                $$ = new ast::SpecialExpressionNode($3, ast::SpecialExpressionNode::FunctionName::SUCC, arg->getInferredType());
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for succ - integer or char expected");
                fatalError = true;
                YYERROR;
            }
        }
    }
|
    TOINT LP args_list RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - toint" << std::endl;
        #endif

        if($3->getArguments().size() != 1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for toint");
            fatalError = true;
            YYERROR;
        }
        else {
            ast::ExpressionNode* arg = $3->getArguments().front();
            if(isBasicType(arg->getInferredType())) {
                $$ = new ast::SpecialExpressionNode(arg, ast::SpecialExpressionNode::FunctionName::TOINT, "integer");
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for toint - basic type expected");
                fatalError = true;
                YYERROR;
            }
        }
    }
|
    TOCHAR LP args_list RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - tochar" << std::endl;
        #endif

        if($3->getArguments().size() != 1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for tochar");
            fatalError = true;
            YYERROR;
        }
        else {
            ast::ExpressionNode* arg = $3->getArguments().front();
            if(isBasicType(arg->getInferredType())) {
                $$ = new ast::SpecialExpressionNode(arg, ast::SpecialExpressionNode::FunctionName::TOCHAR, "char");
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for tochar - basic type expected");
                fatalError = true;
                YYERROR;
            }
        }
    }
|
    TOBOOL LP args_list RP {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse factor - tobool" << std::endl;
        #endif

        if($3->getArguments().size() != 1) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong number of arguments for tobool");
            fatalError = true;
            YYERROR;
        }
        else {
            ast::ExpressionNode* arg = $3->getArguments().front();
            if(isBasicType(arg->getInferredType())) {
                $$ = new ast::SpecialExpressionNode(arg, ast::SpecialExpressionNode::FunctionName::TOBOOL, "boolean");
            }
            else {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", wrong argument type for tobool - basic type expected");
                fatalError = true;
                YYERROR;
            }
        }
    }
;

lvalue :
    identifier {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse lvalue - variable" << std::endl;
        #endif

        if(ctx->getLookupTable().isVariableDefined($1->getName(), ctx->getCurrentScope())) {
            $$ = new ast::SpecialExpressionNode($1, ast::SpecialExpressionNode::FunctionName::VARIABLE,
                ctx->getLookupTable().getVariable($1->getName(), ctx->getCurrentScope()).type);
        }
        else if(isInAnyEnum($1->getName())) {
            auto properEnums = ctx->getLookupTable().getTypes(
            [&](const std::string&, const LookupTable::TypeInfo& tf) {
                return tf.alive && tf.type.find("enum%") == 0 && tf.type.find("%" + $1->getName() + "%") != std::string::npos;
            }, ctx->getCurrentScope());

            if(properEnums.size() != 1) {
                parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", variable " + $1->getName() + " is in more than one enum");
                fatalError = true;
                YYERROR;
            }

            $$ = new ast::SpecialExpressionNode($1, ast::SpecialExpressionNode::FunctionName::ENUM_ELEMENT, properEnums.front().type);
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", variable " + $1->getName() + " is not defined");
            fatalError = true;
            YYERROR;
        }
    }
|
    identifier LB expression RB {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse lvalue - simple array access" << std::endl;
        #endif

        if(!ctx->getLookupTable().isVariableDefined($1->getName(), ctx->getCurrentScope())) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", variable " + $1->getName() + " is not defined");
            fatalError = true;
            YYERROR;
        }
        else if(!isArrayIndexCompatible(ctx->getLookupTable().getVariable($1->getName(), ctx->getCurrentScope()).type, $3)) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", incorrect index type");
            fatalError = true;
            YYERROR;
        }
        else {
            $$ = new ast::SpecialExpressionNode($1, ast::SpecialExpressionNode::FunctionName::ARRAY_ACCESS,
                getArrayElementType(ctx->getLookupTable().getVariable($1->getName(), ctx->getCurrentScope()).type));
        }
    }
|
    lvalue LB expression RB {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse lvalue - complex array access" << std::endl;
        #endif

        if($1->getInferredType().substr(0,5) != "array") {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", array type expected");
            fatalError = true;
            YYERROR;
        }
        else if(!isArrayIndexCompatible($1->getInferredType(), $3)) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", incorrect index type");
            fatalError = true;
            YYERROR;
        }
        else {
            $$ = new ast::SpecialExpressionNode($1, $3, ast::SpecialExpressionNode::FunctionName::ARRAY_ACCESS,
                getArrayElementType($1->getInferredType()));
        }
    }
|
    identifier DOT identifier {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse lvalue - simple record field" << std::endl;
        #endif

        if(ctx->getLookupTable().isVariableDefined($1->getName(), ctx->getCurrentScope()) && isRecordFieldCompatible(ctx->getLookupTable().getVariable($1->getName(), ctx->getCurrentScope()).type, $3)) {
            $$ = new ast::SpecialExpressionNode($1, ast::SpecialExpressionNode::FunctionName::RECORD_ACCESS,
                getRecordFieldType(ctx->getLookupTable().getVariable($1->getName(), ctx->getCurrentScope()).type, $3->getName()));
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", variable " + $1->getName() + " is not defined");
            fatalError = true;
            YYERROR;
        }
    }
|
    lvalue DOT identifier {
        #ifdef YACC_DEBUG
            std::cout << "Yacc debug: Parse lvalue - complex record field" << std::endl;
        #endif

        if($1->getInferredType().substr(0,6) == "record" && isRecordFieldCompatible($1->getInferredType(), $3)) {
            $$ = new ast::SpecialExpressionNode($1, $3, ast::SpecialExpressionNode::FunctionName::RECORD_ACCESS,
            getRecordFieldType($1->getInferredType(), $3->getName()));
        }
        else {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", record type expected");
            fatalError = true;
            YYERROR;
        }
    }
;
%%

void yyerror(const char *s) {
    parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + s);
    fatalError = true;
    resultAst = nullptr;
}

bool parse(const std::string& inputFileName, std::vector<std::string>& errors, std::unique_ptr<ast::ProgramNode>& program) {
    yyin = fopen(inputFileName.c_str(), "r");

    if(yyin == nullptr) {
        errors.push_back("Cannot open file `" + inputFileName + "`");
        return false;
    }

    ctx->pushScope("program");

    yyparse();
    fclose(yyin);

    ctx->popScope();

    errors = std::move(parsingErrors);
    program = std::unique_ptr<ast::ProgramNode>(resultAst);
    return !fatalError;
}

bool isChar(const std::string& expr) {
    return expr.size() == 1;
}

bool isInteger(const std::string& expr) {
    return std::all_of(expr.begin(), expr.end(), ::isdigit) ||
        (expr.size() > 1 && expr[0] == '-' && std::all_of(expr.begin() + 1, expr.end(), ::isdigit));
}

bool isBoolean(const std::string& expr) {
    return expr == "true" || expr == "false";
}

bool nameAlreadyUsed(std::string name) {
    if(ctx->getLookupTable().isVariableDefined(name, ctx->getCurrentScope()) ||
       ctx->getLookupTable().isRoutineDefined(name, ctx->getCurrentScope()) ||
       ctx->getLookupTable().isTypeDefined(name, ctx->getCurrentScope())) {
        return true;
    }

    if(isInAnyEnum(name)) {
        return true;
    }

    return false;
}

bool saveType(ast::IdentifierNode* typeName, const std::string& typeDef) {
    if(nameAlreadyUsed(typeName->getName())) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", name `" + typeName->getName() + "` already used");
        fatalError = true;
        return false;
    } else {
        ctx->getLookupTable().defineType(LookupTable::TypeCategory::SIMPLE, typeName->getName(), typeDef, ctx->getCurrentScope());
        return true;
    }
}

bool saveConstant(ast::IdentifierNode* constName, const std::string& constValue, const std::string& typeDef) {
    if(nameAlreadyUsed(constName->getName())) {
        parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", name `" + constName->getName() + "` already used");
        fatalError = true;
        return false;
    } else {
        ctx->getLookupTable().defineVariable(LookupTable::VariableCategory::CONSTANT, constName->getName(), typeDef, ctx->getCurrentScope());
        ctx->getLookupTable().setVariableValue(constName->getName(), constValue, ctx->getCurrentScope());
        return true;
    }
}

bool saveVariables(std::vector<ast::IdentifierNode*>* varNames, const std::string& typeDef) {
    for(auto& varName : *varNames) {
        if(nameAlreadyUsed(varName->getName())) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", name `" + varName->getName() + "` already used");
            fatalError = true;
            return false;
        } else {
            ctx->getLookupTable().defineVariable(LookupTable::VariableCategory::VARIABLE, varName->getName(), typeDef, ctx->getCurrentScope());
        }
    }

    return true;
}

bool saveRoutine(ast::RoutineDeclarationNode* routineDef, bool isForward) {
    if(isForward) {
      if(nameAlreadyUsed(routineDef->getName())) {
          parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", name `" + routineDef->getName() + "` already used");
          fatalError = true;
          return false;
      }

      for(const auto& paramGroup : *routineDef->getParams()->getParams()) {
          for(const auto& param : *paramGroup->getParams()) {
              if(nameAlreadyUsed(param->getName())) {
                  parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", name `" + param->getName() + "` already used");
                  fatalError = true;
                  return false;
              }
          }
      }
    }

    std::vector<LookupTable::ArgumentInfo> arguments;
    for(const auto& paramGroup : *routineDef->getParams()->getParams()) {
        std::string typeString;
        try { typeString = paramGroup->getParamsType()->flat(); }
        catch(std::runtime_error& err) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
            fatalError = true;
            return false;
        }

        for(const auto& param : *paramGroup->getParams()) {
            arguments.emplace_back(param->getName(), typeString, paramGroup->getPassType() == ast::ParamsGroupNode::PassType::PASS_BY_REFERENCE ? true : false);
        }
    }

    if(routineDef->getRoutineType() == ast::RoutineDeclarationNode::RoutineType::PROCEDURE) {
        ctx->getLookupTable().defineRoutine(LookupTable::RoutineCategory::PROCEDURE, routineDef->getName(),
            arguments, "void", ctx->getCurrentScope());
    }
    else {
        std::string returnType;
        try { returnType = routineDef->getReturnType()->flat(); }
        catch(std::runtime_error& err) {
            parsingErrors.push_back("Error at line " + std::to_string(linesCounter) + ", " + err.what());
            fatalError = true;
            return false;
        }

        ctx->getLookupTable().defineRoutine(LookupTable::RoutineCategory::FUNCTION, routineDef->getName(),
            arguments, returnType, ctx->getCurrentScope());
    }

    return true;
}

bool isBasicType(const std::string& type) {
    return type == "integer" || type == "boolean" || type == "char";
}

bool isBasicOrEnumType(const std::string& type) {
    return isBasicType(type) || type.find("enum%") == 0;
}

bool isBasicOrEnumOrArrayOrRecordType(const std::string& type) {
    return isBasicOrEnumType(type) || type.find("array@@") == 0 || type.find("record$$") == 0;
}

bool isRangeType(const std::string& type) {
    return type.find("constrange%") == 0 || type.find("enumrange%") == 0;
}

bool isInEnum(const std::string& enumElement, const std::string& enumType) {
    return enumType.find(enumElement) != std::string::npos;
}

bool isInAnyEnum(const std::string& enumElement) {
    const std::vector<LookupTable::TypeInfo>& types = ctx->getLookupTable().getTypes(
        [&](const std::string&, const LookupTable::TypeInfo& tf) {
        return tf.alive && tf.type.find("enum%") == 0 && tf.type.find("%" + enumElement + "%") != std::string::npos;
    }, ctx->getCurrentScope());

    return !types.empty();
}

bool isEnumSubRangeType(const std::string& enumElement, const std::string& enumType,
    const std::string& begin, const std::string& end) {
    std::size_t beginPos = enumType.find("%" + begin + "%");
    std::size_t endPos = enumType.find("%" + end + "%");
    std::size_t enumElementPos = enumType.find("%" + enumElement + "%");

    return beginPos != std::string::npos && endPos != std::string::npos && enumElementPos != std::string::npos &&
        beginPos <= enumElementPos && enumElementPos <= endPos;
}

bool isLeftValueCompatible(ast::ExpressionNode* expr) {
    if(expr->getOperation() != ast::ExpressionNode::Operation::SPECIAL) {
        return false;
    }

    ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(expr);
    if(special->getFunctionName() == ast::SpecialExpressionNode::ARRAY_ACCESS ||
       special->getFunctionName() == ast::SpecialExpressionNode::RECORD_ACCESS) {
        return true;
    }

    if(special->getFunctionName() == ast::SpecialExpressionNode::VARIABLE) {
        ast::IdentifierNode* var = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
        return !ctx->getLookupTable().isVariableConst(var->getName(), ctx->getCurrentScope());
    }

    return false;
}

bool isArrayIndexCompatible(const std::string& arrayType, ast::ExpressionNode* index) {
    std::string arrayElementType{};
    std::size_t it{7};
    while(arrayType[it] != '@' && it < arrayType.size()) {
        arrayElementType += arrayType[it];
        it++;
    }

    if(arrayElementType == "integer") {
        if(index->getInferredType() == "integer") {
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
        std::size_t pos;
        for(pos = 11; pos < arrayElementType.size(); pos++) {
            if(arrayElementType[pos] == '.') {
                break;
            }
            begin += arrayElementType[pos];
        }

        for(pos += 2; pos < arrayElementType.size(); pos++) {
            end += arrayElementType[pos];
        }

        if(isInteger(begin) && isInteger(end)) {
            if(index->getInferredType() == "integer") {
                return true;
            }
        }
        else if(isChar(begin) && isChar(end)) {
            if(index->getInferredType() == "char") {
                return true;
            }
        }
        else if(isBoolean(begin) && isBoolean(end)) {
            if(index->getInferredType() == "boolean") {
                return true;
            }
        }

        return false;
    }
    else if(arrayElementType.substr(0, 9) == "enumrange") {
        std::string enumName, beginEnum, endEnum;
        std::size_t pos{10};
        for(; pos < arrayElementType.size(); pos++) {
            if(arrayElementType[pos] == '%') {
                break;
            }
            enumName += arrayElementType[pos];
        }

        pos++;
        while(arrayElementType[pos] != '.') {
            beginEnum += arrayElementType[pos];
            pos++;
        }

        pos += 2;
        for(; pos < arrayElementType.size(); pos++) {
            endEnum += arrayElementType[pos];
        }

        if(index->getOperation() == ast::ExpressionNode::Operation::SPECIAL) {
            ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(index);
            if(special->getFunctionName() == ast::SpecialExpressionNode::ENUM_ELEMENT) {
                ast::IdentifierNode* enumElement = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
                return isEnumSubRangeType(enumElement->getName(), ctx->getLookupTable().getType(enumName, ctx->getCurrentScope()).type, beginEnum, endEnum);
            }
        }

        return false;
    }
    else if(arrayElementType.substr(0, 4) == "enum") {
        if(index->getOperation() == ast::ExpressionNode::Operation::SPECIAL) {
            ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(index);
            if(special->getFunctionName() == ast::SpecialExpressionNode::ENUM_ELEMENT) {
                ast::IdentifierNode* enumElement = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
                return isInEnum(enumElement->getName(), arrayElementType);
            }
        }
        return false;
    }
    else {
        return false;
    }
}

bool isRecordFieldCompatible(const std::string& recordType, ast::IdentifierNode* field) {
    const std::string& fieldName = "$" + field->getName() + "#";
    std::size_t parenthesisCounter{};
    for(std::size_t i = 0; i < recordType.size(); i++) {
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

bool isFunctionArgumentsCompatible(const std::vector<LookupTable::ArgumentInfo>& expectedArgs, const std::vector<ast::ExpressionNode*>& givenArgs) {
    if(expectedArgs.size() != givenArgs.size()) {
        return false;
    }

    for(std::size_t i = 0; i < expectedArgs.size(); i++) {
        if(expectedArgs[i].type != givenArgs[i]->getInferredType()) {
            return false;
        }
        if(expectedArgs[i].isReference && !isLeftValueCompatible(givenArgs[i])) {
            return false;
        }
    }

    return true;
}

bool hasReturnValue(ast::RoutineNode* function, const std::string& functionName) {
    std::vector<ast::StatementNode*>* statements = function->getBody()->getStatements()->getStatements().get();
    if(statements->empty()) {
        std::cout << "Empty function body\n";
        return false;
    }

    std::size_t returnCounter{0};
    std::size_t lastStatementIndex{0};
    for(std::size_t i = 0; i < statements->size(); i++) {
        if(statements->at(i)->getCategory() != ast::StatementNode::Category::ASSIGN) {
            continue;
        }

        ast::ExpressionNode* lhs = dynamic_cast<ast::AssignNode*>(statements->at(i))->getLhs().get();
        if(lhs->getOperation() != ast::ExpressionNode::Operation::SPECIAL) {
            continue;
        }

        ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(lhs);
        if(special->getFunctionName() != ast::SpecialExpressionNode::VARIABLE) {
            continue;
        }

        ast::IdentifierNode* variable = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
        if(variable->getName() == functionName) {
            returnCounter++;
            lastStatementIndex = i;
        }
    }

    if(returnCounter != 1) {
        return false;
    }

    return lastStatementIndex == statements->size() - 1;
}

bool variableIsReassignedS(const std::string& varName, ast::StatementNode* stmt) {
    switch(stmt->getCategory()) {
        case ast::StatementNode::Category::BREAK:
        case ast::StatementNode::Category::CONTINUE:
        case ast::StatementNode::Category::GOTO:
            return false;
        case ast::StatementNode::Category::ASSIGN: {
            ast::ExpressionNode* rhs = dynamic_cast<ast::AssignNode*>(stmt)->getRhs().get();
            if(variableIsReassignedE(varName, rhs)) {
                return true;
            }

            ast::ExpressionNode* lhs = dynamic_cast<ast::AssignNode*>(stmt)->getLhs().get();
            if(lhs->getOperation() != ast::ExpressionNode::Operation::SPECIAL) {
                return false;
            }

            ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(lhs);
            if(special->getFunctionName() != ast::SpecialExpressionNode::VARIABLE) {
                return false;
            }

            ast::IdentifierNode* variable = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
            return variable->getName() == varName;
        }
        case ast::StatementNode::Category::CALL: {
            ast::CallNode* call = dynamic_cast<ast::CallNode*>(stmt);

            if(call->getCallObjectType() == ast::CallNode::CallObjectType::USER_DEFINED) {
                ast::UserDefineCallNode* userCall = dynamic_cast<ast::UserDefineCallNode*>(call);
                const std::vector<LookupTable::ArgumentInfo>& callArgs = ctx->getLookupTable().getRoutine(userCall->getName()->getName(), ctx->getCurrentScope()).args;
                std::vector<bool> passByReference;
                for(std::size_t i = 0; i < callArgs.size(); i++) {
                    passByReference.push_back(callArgs[i].isReference);
                }

                std::size_t index{0};
                for(auto arg : userCall->getArguments()->getArguments()) {
                    if(arg->getOperation() == ast::ExpressionNode::Operation::SPECIAL) {
                        ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(arg);
                        if(special->getFunctionName() == ast::SpecialExpressionNode::VARIABLE) {
                            ast::IdentifierNode* variable = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
                            if(variable->getName() == varName && passByReference[index]) {
                                return true;
                            }
                        }
                        else if(variableIsReassignedE(varName, arg)) {
                            return true;
                        }
                    }
                    else if(variableIsReassignedE(varName, arg)) {
                        return true;
                    }
                    index++;
                }
                return false;
            }
            else {
                ast::BuiltinCallNode* builtinCall = dynamic_cast<ast::BuiltinCallNode*>(call);
                if(builtinCall->getArguments() == nullptr) {
                    return false;
                }
                auto args = builtinCall->getArguments()->getArguments();

                if(builtinCall->getFunctionName() == ast::BuiltinCallNode::FunctionName::READ) {
                    if(args.front()->getOperation() == ast::ExpressionNode::Operation::SPECIAL) {
                        ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(args.front());
                        if(special->getFunctionName() == ast::SpecialExpressionNode::VARIABLE) {
                            ast::IdentifierNode* variable = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
                            return variable->getName() == varName;
                        }
                    }
                }
                if(builtinCall->getFunctionName() == ast::BuiltinCallNode::FunctionName::MEMORY_READ) {
                    if(args.back()->getOperation() == ast::ExpressionNode::Operation::SPECIAL) {
                        ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(args.back());
                        if(special->getFunctionName() == ast::SpecialExpressionNode::VARIABLE) {
                            ast::IdentifierNode* variable = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
                            return variable->getName() == varName;
                        }
                    }
                }
                if(builtinCall->getFunctionName() == ast::BuiltinCallNode::FunctionName::STACK_READ) {
                    if(args.back()->getOperation() == ast::ExpressionNode::Operation::SPECIAL) {
                        ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(args.back());
                        if(special->getFunctionName() == ast::SpecialExpressionNode::VARIABLE) {
                            ast::IdentifierNode* variable = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
                            return variable->getName() == varName;
                        }
                    }
                }

                return false;
            }
        }
        case ast::StatementNode::Category::CASE: {
            for(auto caseStatement: *dynamic_cast<ast::CaseNode*>(stmt)->getStatements()) {
                if(caseStatement->first != nullptr && caseStatement->first->getType() == ast::AstNode::Type::EXPRESSION) {
                    if(variableIsReassignedE(varName, dynamic_cast<ast::ExpressionNode*>(caseStatement->first))) {
                        return true;
                    }
                }

                if(variableIsReassignedS(varName, caseStatement->second)) {
                    return true;
                }
            }
            return false;
        }
        case ast::StatementNode::Category::COMPOUND: {
            for(auto statement : *dynamic_cast<ast::CompoundStatementNode*>(stmt)->getStatements()) {
                if(variableIsReassignedS(varName, statement)) {
                    return true;
                }
            }
            return false;
        }
        case ast::StatementNode::Category::FOR: {
            if(variableIsReassignedE(varName, dynamic_cast<ast::ForNode*>(stmt)->getStart().get())) {
                return true;
            }
            if(variableIsReassignedE(varName, dynamic_cast<ast::ForNode*>(stmt)->getEnd().get())) {
                return true;
            }
            if(variableIsReassignedS(varName, dynamic_cast<ast::ForNode*>(stmt)->getStatements().get())) {
                return true;
            }

            return false;
        }
        case ast::StatementNode::Category::IF: {
            if(variableIsReassignedE(varName, dynamic_cast<ast::IfNode*>(stmt)->getCondition().get())) {
                return true;
            }
            if(variableIsReassignedS(varName, dynamic_cast<ast::IfNode*>(stmt)->getThenStatement().get())) {
                return true;
            }
            if(dynamic_cast<ast::IfNode*>(stmt)->getElseStatement().get() != nullptr
                && variableIsReassignedS(varName, dynamic_cast<ast::IfNode*>(stmt)->getElseStatement().get())) {
                return true;
            }

            return false;
        }
        case ast::StatementNode::Category::REPEAT: {
            if(variableIsReassignedE(varName, dynamic_cast<ast::RepeatNode*>(stmt)->getCondition().get())) {
                return true;
            }

            if(variableIsReassignedS(varName, dynamic_cast<ast::RepeatNode*>(stmt)->getStatements().get())) {
                return true;
            }

            return false;
        }
        case ast::StatementNode::Category::WHILE: {
            if(variableIsReassignedE(varName, dynamic_cast<ast::WhileNode*>(stmt)->getCondition().get())) {
                return true;
            }

            if(variableIsReassignedS(varName, dynamic_cast<ast::WhileNode*>(stmt)->getStatements().get())) {
                return true;
            }

            return false;
        }
        default:
            return false;
    }
}

bool variableIsReassignedE(const std::string& varName, ast::ExpressionNode* expr) {
    if(expr->getOperation() != ast::ExpressionNode::Operation::SPECIAL) {
        return false;
    }

    ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(expr);
    if(special->getFunctionName() == ast::SpecialExpressionNode::CALL) {
        auto routineName = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get())->getName();
        auto args = dynamic_cast<ast::ArgumentsListNode*>(special->getArgument2().get())->getArguments();

        const std::vector<LookupTable::ArgumentInfo>& callArgs = ctx->getLookupTable().getRoutine(routineName, ctx->getCurrentScope()).args;
        std::vector<bool> passByReference;
        for(std::size_t i = 0; i < callArgs.size(); i++) {
            passByReference.push_back(callArgs[i].isReference);
        }

        std::size_t index{0};
        for(auto arg : args) {
            if(arg->getOperation() == ast::ExpressionNode::Operation::SPECIAL) {
                ast::SpecialExpressionNode* special = dynamic_cast<ast::SpecialExpressionNode*>(arg);
                if(special->getFunctionName() == ast::SpecialExpressionNode::VARIABLE) {
                    ast::IdentifierNode* variable = dynamic_cast<ast::IdentifierNode*>(special->getArgument1().get());
                    if(variable->getName() == varName && passByReference[index]) {
                        return true;
                    }
                }
                else if(variableIsReassignedE(varName, arg)) {
                    return true;
                }
            }
            else if(variableIsReassignedE(varName, arg)) {
                return true;
            }
            index++;
        }
    }

    return false;
}

std::string getArrayElementType(const std::string& arrayType) {
    std::string elementType{};
    std::size_t counter{0};
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
    std::size_t it = recordType.find("$" + field + "#") + field.size() + 3;
    std::string fieldType{};
    std::size_t parenthesisCounter{1};
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
