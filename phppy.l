%{
#include <stdio.h>
#include <string.h>
#include "phppy.tab.h"
extern void yyerror(const char *s);
%}

%x ML_COMMENT

%%
"<?php"                     { return PHP_START; }
"?>"                        { return PHP_END; }
"define"                    { return DEFINE; }
"array"                     { return ARRAY; }
"true"                      { yylval.strval = strdup("True"); return BOOL; }
"false"                     { yylval.strval = strdup("False"); return BOOL; }
"is_int"                    { return IS_INT; }
"is_string"                 { return IS_STRING; }
"is_array"                  { return IS_ARRAY; }
"is_float"                  { return IS_FLOAT; }
"is_bool"                   { return IS_BOOL; }
"if"                        { return IF; }
"else"                      { return ELSE; }
"elseif"                    { return ELSEIF; }
"while"                     { return WHILE; }
"endwhile"                  { return ENDWHILE; }
"echo"                      { return ECHO_TOKEN; }
"global"                    { return GLOBAL; }
"function"                  { return FUNCTION; }
"class"                     { return CLASS; }
"new"                       { return NEW; }
"public"                    { return PUBLIC; }
"protected"                 { return PROTECTED; }
"private"                   { return PRIVATE; }
"return"                    { return RETURN; }
"$"[a-zA-Z_][a-zA-Z0-9_]*   { yylval.strval = strdup(yytext); return VARIABLE; }
[0-9]+                      { yylval.strval = strdup(yytext); return INTEGER; }
[0-9]+\.[0-9]+              { yylval.strval = strdup(yytext); return FLOAT; }
\'[^\']\'                   { yylval.strval = strdup(yytext); return CHAR; }
\"([^\"\n\\]|\\.)*\"        { yylval.strval = strdup(yytext); return STRING; }
[a-zA-Z_][a-zA-Z0-9_]*      { yylval.strval = strdup(yytext); return IDENTIFIER; }
\$[0-9][a-zA-Z0-9_]*        { printf("Error: Invalid variable name '%s'\n", yytext); }
"+"                         { return PLUS; }
";"                         { return SEMICOLON; }
"="                         { return ASSIGN; }
"("                         { return LPAREN; }
")"                         { return RPAREN; }
"{"                         { return LBRACE; }
"}"                         { return RBRACE; }
"=>"                        { return ARROW; }
"->"                        { return ARROW_OBJ; }
"["                         { return LBRACKET; }
"]"                         { return RBRACKET; }
">"                         { return GT; }
"<"                         { return LT; }
"<="                        { return LE; }
"=="                        { return EQ; }
"!="                        { return NE; }
"++"                        { return INCREMENT; }
":"                         { return COLON; }
","                         { return COMMA; }
"$"                         { return DOLLAR; }
[ \t\n]                     ; // Ignore whitespace
"//".*                      ; // Ignore single-line comments
"/*"                        { BEGIN(ML_COMMENT); }
<ML_COMMENT>"*/"            { BEGIN(INITIAL); }
<ML_COMMENT>.|\n            ; // Ignore everything in multi-line comments
.                           { printf("Unrecognized character: %s\n", yytext); }
%%

int yywrap(void) {
    return 1;
}