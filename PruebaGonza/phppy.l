%{
#include <stdio.h>
#include <string.h>
#include "phppy.tab.h"

extern void yyerror(const char *s);
%}

%%
"<?php"         { return PHP_START; }
"?>"            { return PHP_END; }
"define"        { return DEFINE; }
"array"         { return ARRAY; }
"true"          { yylval.strval = strdup("True"); return BOOL; }
"false"         { yylval.strval = strdup("False"); return BOOL; }
"$"[a-zA-Z_][a-zA-Z0-9_]* { yylval.strval = strdup(yytext + 1); return VARIABLE; }
[0-9]+          { yylval.strval = strdup(yytext); return INTEGER; }
[0-9]+\.[0-9]+  { yylval.strval = strdup(yytext); return FLOAT; }
\'[a-zA-Z]\'    { yylval.strval = strdup(yytext); return CHAR; }
\"[^\"]*\"      { yylval.strval = strdup(yytext); return STRING; }
";"             { return SEMICOLON; }
"="             { return ASSIGN; }
"("             { return LPAREN; }
")"             { return RPAREN; }
","             { return COMMA; }
[ \t\n]         ; // Ignore whitespace
"//".*          ; // Ignore single-line comments
.               { printf("Unrecognized character: %s\n", yytext); }
%%

int yywrap(void) {
    return 1;
}