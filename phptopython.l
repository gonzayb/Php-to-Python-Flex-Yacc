%{
#include "php.tab.h"  // Incluye el archivo de cabecera generado por Bison.
%}

%%

"if"        { return IF; }   // Detecta la palabra clave "if" y devuelve el token IF.
"else"      { return ELSE; } // Detecta la palabra clave "else" y devuelve el token ELSE.
"while"     { return WHILE; }// Detecta la palabra clave "while" y devuelve el token WHILE.
"for"       { return FOR; }  // Detecta la palabra clave "for" y devuelve el token FOR.
"function"  { return FUNCTION; } // Detecta la palabra clave "function" y devuelve el token FUNCTION.
"return"    { return RETURN; }   // Detecta la palabra clave "return" y devuelve el token RETURN.
"="         { return ASSIGN; }   // Detecta el símbolo "=" y devuelve el token ASSIGN.
"("         { return LPAREN; }   // Detecta el símbolo "(" y devuelve el token LPAREN.
")"         { return RPAREN; }   // Detecta el símbolo ")" y devuelve el token RPAREN.
"{"         { return LBRACE; }   // Detecta el símbolo "{" y devuelve el token LBRACE.
"}"         { return RBRACE; }   // Detecta el símbolo "}" y devuelve el token RBRACE.
";"         { return SEMICOLON; }// Detecta el símbolo ";" y devuelve el token SEMICOLON.
[0-9]+      { yylval.intval = atoi(yytext); return NUMBER; } // Detecta números y los convierte a entero.
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.strval = strdup(yytext); return IDENTIFIER; } // Detecta identificadores (nombres de variables).
[ \t\n\r]+  { /* Ignora los espacios en blanco */ } // Ignora espacios, tabulaciones y nuevas líneas.
.           { return yytext[0]; } // Retorna cualquier otro carácter como su propio token.

%%

int yywrap() {
    return 1; // Función necesaria para Flex, indica el final del análisis.
}