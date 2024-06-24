%{
#include <stdio.h>
#include <string.h>
#include "phppy.tab.h"

extern void yyerror(const char *s);
%}

%x ML_STRING

%%
"<?php"         { return PHP_START; }
"?>"            { return PHP_END; }
"define"        { return DEFINE; }
"array"         { return ARRAY; }
"true"          { yylval.strval = strdup("True"); return BOOL; }
"false"         { yylval.strval = strdup("False"); return BOOL; }
"is_int"        { return IS_INT; }
"is_string"     { return IS_STRING; }
"is_array"      { return IS_ARRAY; }
"is_float"      { return IS_FLOAT; }
"is_bool"       { return IS_BOOL; }
"if"            { return IF; }
"echo"          { return ECHO_TOKEN; }
"$"[a-zA-Z_][a-zA-Z0-9_]* { yylval.strval = strdup(yytext + 1); return VARIABLE; }
[0-9]+          { yylval.strval = strdup(yytext); return INTEGER; }
[0-9]+\.[0-9]+  { yylval.strval = strdup(yytext); return FLOAT; }
\'[a-zA-Z]\'    { yylval.strval = strdup(yytext); return CHAR; }
\"              { BEGIN(ML_STRING); yylval.strval = strdup(""); }
<ML_STRING>[^"\\]*  { yylval.strval = realloc(yylval.strval, strlen(yylval.strval) + strlen(yytext) + 1); strcat(yylval.strval, yytext); }
<ML_STRING>\\. { char c = yytext[1]; if (c == 'n') c = '\n'; yylval.strval = realloc(yylval.strval, strlen(yylval.strval) + 2); strncat(yylval.strval, &c, 1); }
<ML_STRING>\"   { BEGIN(INITIAL); return STRING; }
";"             { return SEMICOLON; }
"="             { return ASSIGN; }
"("             { return LPAREN; }
")"             { return RPAREN; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }
","             { return COMMA; }
[ \t\n]         ; // Ignore whitespace
"//".*          ; // Ignore single-line comments
.               { printf("Unrecognized character: %s\n", yytext); }
%%

int yywrap(void) {
    return 1;
}