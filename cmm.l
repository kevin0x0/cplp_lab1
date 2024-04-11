%top {
#include <stdlib.h>
#include "mycc.h"
#include "cmm.tab.h"
#include "utils.h"
}

%option yylineno

INT_HEX 0x[A-Fa-f0-9]+
INT_OCT 0[0-7]*
INT_DEC [1-9][0-9]*
FLOAT   [0-9]+\.[0-9]+
FLOATE  [0-9]+(\.[0-9]+)?[Ee][+\-]?[0-9]+
TINT    int
TFLOAT  float
STRUCT  struct
RETURN  return
WHILE   while
IF      if
ELSE    else

SEMI    ;
COMMA   ,
DOT     \.

ASSIGN  =
ADD     \+
SUB     \-
MUL     \*
DIV     \/
MOD     \%
AND     &&
OR      \|\|
NOT     !

LP      \(
RP      \)
LB      \[
RB      \]
LC      \{
RC      \}

EQ      ==
NE      !=
LT      <
LE      <=
GT      >
GE      >=

ID      [A-Za-z_][A-Za-z0-9_]*

SPACE   [ \t\n\r]*
COMMENT \/\*([^\*]|\*[^\/])\*\/|\/\/[^\n\r]
ERROR   .
%%

{INT_HEX} { yylval.cst = pstate_appendcst(parser_state, cst_create_int(yylineno, strtoll(yytext + 2, NULL, 16))); return INT; }
{INT_OCT} { yylval.cst = pstate_appendcst(parser_state, cst_create_int(yylineno, strtoll(yytext, NULL, 8))); return INT; }
{INT_DEC} { yylval.cst = pstate_appendcst(parser_state, cst_create_int(yylineno, strtoll(yytext, NULL, 10))); return INT; }
{FLOAT}   { yylval.cst = pstate_appendcst(parser_state, cst_create_float(yylineno, strtof(yytext, NULL))); return FLOAT; }
{FLOATE}  { yylval.cst = pstate_appendcst(parser_state, cst_create_float(yylineno, strtof(yytext, NULL))); return FLOAT; }
{TINT}    { yylval.cst = pstate_appendcst(parser_state, cst_create_type(yylineno, TYPE_INT)); return TYPE; }
{TFLOAT}  { yylval.cst = pstate_appendcst(parser_state, cst_create_type(yylineno, TYPE_FLOAT)); return TYPE; }

{STRUCT}  { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(STRUCT))); return STRUCT; }
{RETURN}  { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(RETURN))); return RETURN; }
{WHILE}   { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(WHILE))); return WHILE; }
{IF}      { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(IF))); return IF; }
{ELSE}    { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(ELSE))); return ELSE; }

{SEMI}    { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(SEMI))); return SEMI; }
{COMMA}   { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(COMMA))); return COMMA; }
{DOT}     { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(DOT))); return DOT; }
{ASSIGN}  { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(ASSIGN))); return ASSIGN; }

{ADD}     { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(ADD))); return ADD; }
{SUB}     { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(SUB))); return SUB; }
{MUL}     { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(MUL))); return MUL; }
{DIV}     { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(DIV))); return DIV; }
{AND}     { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(AND))); return AND; }
{OR}      { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(OR))); return OR; }
{NOT}     { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(NOT))); return NOT; }

{EQ}      { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(EQ))); return EQ; }
{NE}      { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(NE))); return NE; }
{LT}      { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(LT))); return LT; }
{LE}      { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(LE))); return LE; }
{GT}      { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(GT))); return GT; }
{GE}      { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(GE))); return GE; }

{LP}      { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(LP))); return LP; }
{RP}      { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(RP))); return RP; }
{LB}      { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(LB))); return LB; }
{RB}      { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(RB))); return RB; }
{LC}      { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(LC))); return LC; }
{RC}      { yylval.cst = pstate_appendcst(parser_state, cst_create_noattrtoken(yylineno, make_cstkind(RC))); return RC; }

{ID}      { char* str = strtbl_newstring(parser_state->strtbl, yytext);
            utils_oom_ifnull(str);
            yylval.cst = pstate_appendcst(parser_state, cst_create_id(yylineno, strtbl_stringid(parser_state->strtbl, str)));
            return ID; }

{SPACE}   {}
{COMMENT} {}
{ERROR}   { mycc_error("A", yylineno, "mysterious character '%s'", yytext); }


