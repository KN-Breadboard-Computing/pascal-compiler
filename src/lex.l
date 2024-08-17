%{
#define NO_YY_WRAP
#define YY_NO_UNPUT
#define YY_NO_INPUT

#undef LEX_DEBUG

#include <iostream>
#include <string>

#include "../out/parser.hpp"

uint64_t linesCounter = 1;

static int createToken(int token);
static int createVariable(int token);
static int createNumber(int token);
static int createChar(int token);
static int createString(int token);
%}

%x COMMENT1 COMMENT2

A [aA]
B [bB]
C [cC]
D [dD]
E [eE]
F [fF]
G [gG]
H [hH]
I [iI]
J [jJ]
K [kK]
L [lL]
M [mM]
N [nN]
O [oO]
P [pP]
Q [qQ]
R [rR]
S [sS]
T [tT]
U [uU]
V [vV]
W [wW]
X [xX]
Y [yY]
Z [zZ]
NQUOTE [^']

%%

"{"                  {   BEGIN(COMMENT1);                                                                              }
<COMMENT1>[^}\n]+    {                                                                                                 }
<COMMENT1>\n         {  linesCounter++;                                                                                }
<COMMENT1><<EOF>>    {  std::cerr << "Error: unexpected end of file in comment at line " << linesCounter << std::endl; }
<COMMENT1>"}"        {  BEGIN(INITIAL);                                                                                }

"(*"                 {  BEGIN(COMMENT2);                                                                               }
<COMMENT2>[^)*\n]+   {                                                                                                 }
<COMMENT2>\n         {  linesCounter++;                                                                                }
<COMMENT2><<EOF>>    {  std::cerr << "Error: unexpected end of file in comment at line " << linesCounter << std::endl; }
<COMMENT2>"*)"       {  BEGIN(INITIAL);                                                                                }
<COMMENT2>[*)]       {                                                                                                 }

{A}{N}{D}                                               {   return createToken(AND);                            }
{A}{R}{R}{A}{Y}                                         {   return createToken(ARRAY);                          }
{B}{E}{G}{I}{N}                                         {   return createToken(BBEGIN);                         }
{C}{A}{S}{E}                                            {   return createToken(CASE);                           }
{C}{O}{N}{S}{T}                                         {   return createToken(CONST);                          }
{D}{O}                                                  {   return createToken(DO);                             }
{D}{O}{W}{N}{T}{O}                                      {   return createToken(DOWNTO);                         }
{E}{L}{S}{E}                                            {   return createToken(ELSE);                           }
{E}{N}{D}                                               {   return createToken(END);                            }
{F}{O}{R}                                               {   return createToken(FOR);                            }
{F}{U}{N}{C}{T}{I}{O}{N}                                {   return createToken(FUNCTION);                       }
{I}{F}                                                  {   return createToken(IF);                             }
{N}{O}{T}                                               {   return createToken(NOT);                            }
{O}{F}                                                  {   return createToken(OF);                             }
{O}{R}                                                  {   return createToken(OR);                             }
{P}{R}{O}{C}{E}{D}{U}{R}{E}                             {   return createToken(PROCEDURE);                      }
{P}{R}{O}{G}{R}{A}{M}                                   {   return createToken(PROGRAM);                        }
{R}{E}{C}{O}{R}{D}                                      {   return createToken(RECORD);                         }
{R}{E}{P}{E}{A}{T}                                      {   return createToken(REPEAT);                         }
{T}{H}{E}{N}                                            {   return createToken(THEN);                           }
{T}{O}                                                  {   return createToken(TO);                             }
{T}{Y}{P}{E}                                            {   return createToken(TYPE);                           }
{U}{N}{T}{I}{L}                                         {   return createToken(UNTIL);                          }
{V}{A}{R}                                               {   return createToken(VAR);                            }
{W}{H}{I}{L}{E}                                         {   return createToken(WHILE);                          }
{G}{O}{T}{O}                                            {   return createToken(GOTO);                           }
{B}{R}{E}{A}{K}                                         {   return createToken(BREAK);                          }
{C}{O}{N}{T}{I}{N}{U}{E}                                {   return createToken(CONTINUE);                       }
{O}{T}{H}{E}{R}{W}{I}{S}{E}                             {   return createToken(OTHERWISE);                      }

{T}{R}{U}{E}                                            {   return createToken(TRUE);                           }
{F}{A}{L}{S}{E}                                         {   return createToken(FALSE);                          }
{M}{A}{X}{I}{N}{T}                                      {   return createToken(MAXINT);                         }

{A}{B}{S}                                               {   return createToken(ABS);                            }
{C}{H}{R}                                               {   return createToken(CHR);                            }
{O}{D}{D}                                               {   return createToken(ODD);                            }
{O}{R}{D}                                               {   return createToken(ORD);                            }
{P}{R}{E}{D}                                            {   return createToken(PRED);                           }
{S}{U}{C}{C}                                            {   return createToken(SUCC);                           }

{T}{O}{I}{N}{T}                                         {   return createToken(TOINT);                          }
{T}{O}{C}{H}{A}{R}                                      {   return createToken(TOCHAR);                         }
{T}{O}{B}{O}{O}{L}                                      {   return createToken(TOBOOL);                         }

{R}{E}{A}{D}                                            {   return createToken(READ);                           }
{R}{E}{A}{D}{L}{N}                                      {   return createToken(READLN);                         }
{W}{R}{I}{T}{E}                                         {   return createToken(WRITE);                          }
{W}{R}{I}{T}{E}{L}{N}                                   {   return createToken(WRITELN);                        }
{M}{E}{M}{O}{R}{Y}{R}{E}{A}{D}                          {   return createToken(MEMORYREAD);                     }
{M}{E}{M}{O}{R}{Y}{W}{R}{I}{T}{E}                       {   return createToken(MEMORYWRITE);                    }
{S}{T}{A}{C}{K}{R}{E}{A}{D}                             {   return createToken(STACKREAD);                      }
{S}{T}{A}{C}{K}{W}{R}{I}{T}{E}                          {   return createToken(STACKWRITE);                     }

{I}{N}{T}{E}{G}{E}{R}                                   {   return createToken(INT_TYPE);                       }
{C}{H}{A}{R}                                            {   return createToken(CHAR_TYPE);                      }
{B}{O}{O}{L}{E}{A}{N}                                   {   return createToken(BOOL_TYPE);                      }

":="                                                    {   return createToken(ASSIGN);                         }
":"                                                     {   return createToken(COLON);                          }
","                                                     {   return createToken(COMMA);                          }
"."                                                     {   return createToken(DOT);                            }
".."                                                    {   return createToken(DOUBLEDOT);                      }
"="                                                     {   return createToken(EQUAL);                          }
">="                                                    {   return createToken(GE);                             }
">"                                                     {   return createToken(GT);                             }
"["                                                     {   return createToken(LB);                             }
"<="                                                    {   return createToken(LE);                             }
"("                                                     {   return createToken(LP);                             }
"<"                                                     {   return createToken(LT);                             }
"-"                                                     {   return createToken(MINUS);                          }
"<>"                                                    {   return createToken(UNEQUAL);                        }
"+"                                                     {   return createToken(PLUS);                           }
"]"                                                     {   return createToken(RB);                             }

")"                                                     {   return createToken(RP);                             }
";"                                                     {   return createToken(SEMICOLON);                      }
"/"                                                     {   return createToken(DIV);                            }
"*"                                                     {   return createToken(MUL);                            }
"%"                                                     {   return createToken(MOD);                            }

[a-zA-Z]([a-zA-Z0-9_])*                                 {   return createVariable(IDENT_NAME);                  }
[0-9]+                                                  {   return createNumber(INTEGER);                       }
'({NQUOTE}|'')'                                         {   return createChar(CHAR);                            }
'({NQUOTE}|'')({NQUOTE}|'')+'                           {   return createString(STRING);                        }

[ \t\f]                                                 {                                                       }

"\n"                                                    {   linesCounter++;                                     }

.   {   std::cerr << "Error:  illegal character " << yytext[0] << " at line " << linesCounter << std::endl;    }

%%

static int createToken(int token) {
    #ifdef LEX_DEBUG
        std::cout << "Lex debug: general token [" << linesCounter << "] `" << yytext << "`\n";
    #endif

    yylval.token.numericalValue = 0;
    yylval.token.stringValue = nullptr;

    return token;
}

static int createVariable(int token) {
    #ifdef LEX_DEBUG
        std::cout << "Lex debug: variable token [" << linesCounter << "] `" << yytext << "`\n";
    #endif

    yylval.token.numericalValue = 0;
    yylval.token.stringValue = new std::string(yytext);

    return token;
}

static int createNumber(int token) {
    #ifdef LEX_DEBUG
        std::cout << "Lex debug: number token [" << linesCounter << "] `" << yytext << "`\n";
    #endif

    yylval.token.numericalValue = strtoull(yytext, nullptr, 10);
    yylval.token.stringValue = nullptr;

    return token;
}

static int createChar(int token) {
    #ifdef LEX_DEBUG
        std::cout << "Lex debug: char token [" << linesCounter << "] `" << yytext[1] << "`\n";
    #endif

    yylval.token.numericalValue = yytext[1];
    yylval.token.stringValue = nullptr;

    return token;
}

static int createString(int token) {
    #ifdef LEX_DEBUG
        std::cout << "Lex debug: string token [" << linesCounter << "] `" << yytext << "`\n";
    #endif

    yylval.token.numericalValue = 0;
    yylval.token.stringValue = new std::string(yytext);

    return token;
}

int yywrap(void) {
    return 1;
}
