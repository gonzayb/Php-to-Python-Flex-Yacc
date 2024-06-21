%{
#include "php.tab.h"
#include <stdio.h>  // Necesario para fprintf
%}

%%

"if"        { return IF; }
"else"      { return ELSE; }
"while"     { return WHILE; }
"for"       { return FOR; }
"function"  { return FUNCTION; }
"return"    { return RETURN; }
"="         { return ASSIGN; }
"("         { return LPAREN; }
")"         { return RPAREN; }
"{"         { return LBRACE; }
"}"         { return RBRACE; }
";"         { return SEMICOLON; }
[0-9]+      { yylval.intval = atoi(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.strval = strdup(yytext); return IDENTIFIER; }
[ \t\n\r]+  { /* Ignore whitespace */ }

// Comentarios de una línea
"//".*       { /* Ignorar comentarios de una línea */ }

// Comentarios de múltiples líneas (correctamente terminados)
"/*"([^*]|\*+[^*/])*\*+/  { /* Ignorar comentarios de múltiples líneas */ }

// Comentarios de múltiples líneas no terminados
"/*"([^*]|\*+[^*/])*$    {
    fprintf(stderr, "Error: comentario no terminado\n");
    exit(1);
}

// Cualquier otro carácter
.           { return yytext[0]; }

%%

int yywrap() {
    return 1;
}