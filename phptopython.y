%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s); // Declaración de la función de manejo de errores.
extern int yylex(); // Declaración de la función de análisis léxico generada por Flex.

// Definición de la estructura y funciones de la tabla de símbolos.
typedef struct SymbolTable {
    char *name; // Nombre de la variable.
    int value; // Valor de la variable.
    struct SymbolTable *next; // Puntero al siguiente elemento en la tabla.
} SymbolTable;

SymbolTable *symbol_table = NULL; // Inicialización de la tabla de símbolos a NULL.

// Función para agregar un símbolo a la tabla de símbolos.
void add_symbol(char *name, int value) {
    SymbolTable *symbol = malloc(sizeof(SymbolTable)); // Reserva memoria para un nuevo símbolo.
    symbol->name = strdup(name); // Copia el nombre del símbolo.
    symbol->value = value; // Asigna el valor del símbolo.
    symbol->next = symbol_table; // Enlaza el nuevo símbolo al inicio de la tabla.
    symbol_table = symbol; // Actualiza la tabla de símbolos para que apunte al nuevo símbolo.
}

// Función para obtener el valor de un símbolo de la tabla de símbolos.
int get_symbol_value(char *name) {
    SymbolTable *current = symbol_table; // Apunta al inicio de la tabla de símbolos.
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) { // Compara los nombres de los símbolos.
            return current->value; // Devuelve el valor del símbolo si hay coincidencia.
        }
        current = current->next; // Avanza al siguiente símbolo en la tabla.
    }
    return 0; // Valor por defecto si el símbolo no se encuentra.
}

// Definición de la estructura Node y función para crear nodos.
typedef struct Node {
    char *code; // Código asociado al nodo.
} Node;

// Función para crear un nuevo nodo.
Node *new_node(char *code) {
    Node *node = malloc(sizeof(Node)); // Reserva memoria para un nuevo nodo.
    node->code = strdup(code); // Copia el código en el nodo.
    return node; // Devuelve el nuevo nodo.
}
%}

%union {
    int intval; // Para números enteros.
    char *strval; // Para identificadores (nombres de variables).
    Node *node; // Para nodos que contienen código.
}

%token IF ELSE WHILE FOR FUNCTION RETURN ASSIGN
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON
%token NUMBER IDENTIFIER

%type <node> statement expression
%type <strval> identifier
%type <node> assignment_statement if_statement while_statement function_declaration return_statement for_statement// Declaración de tipos semánticos

%%

program:
    program statement // Un programa es una secuencia de declaraciones.
    |
    ;

statement:
    assignment_statement // Una declaración puede ser una asignación.
    | if_statement // O una declaración if.
    | while_statement // O una declaración while.
    | for_statement // O una declaración for.
    | function_declaration // O una declaración de función.
    | return_statement // O una declaración de retorno.
    ;

assignment_statement:
    identifier ASSIGN expression SEMICOLON {
        add_symbol($1, $3->intval); // Agregar la variable a la tabla de símbolos.
        $$ = new_node($1); // Crear un nuevo nodo con el identificador.
        printf("%s = %s\n", $1, $3->code); // Imprimir la asignación en formato Python.
    }
    ;

if_statement:
    IF LPAREN expression RPAREN statement {
        $$ = new_node("if"); // Crear un nuevo nodo para la declaración if.
        printf("if (%s)\n", $3->code); // Imprimir la declaración if en formato Python.
    }
    | IF LPAREN expression RPAREN statement ELSE statement {
        $$ = new_node("if-else"); // Crear un nuevo nodo para la declaración if-else.
        printf("if (%s)\n", $3->code); // Imprimir la declaración if en formato Python.
    }
    ;

while_statement:
    WHILE LPAREN expression RPAREN statement {
        $$ = new_node("while"); // Crear un nuevo nodo para la declaración while.
        printf("while (%s)\n", $3->code); // Imprimir la declaración while en formato Python.
    }
    ;

for_statement:
    FOR LPAREN assignment_statement SEMICOLON expression SEMICOLON assignment_statement RPAREN statement {
        $$ = new_node("for"); // Crear un nuevo nodo para la declaración for.
        printf("for (%s; %s; %s)\n", $3->code, $5->code, $7->code); // Imprimir la declaración for en formato Python.
    }
    ;

function_declaration:
    FUNCTION identifier LPAREN RPAREN LBRACE program RBRACE {
        $$ = new_node($2); // Crear un nuevo nodo para la declaración de función.
        printf("def %s():\n", $2); // Imprimir la declaración de función en formato Python.
    }
    ;

return_statement:
    RETURN expression SEMICOLON {
        $$ = new_node("return"); // Crear un nuevo nodo para la declaración de retorno.
        printf("return %s\n", $2->code); // Imprimir la declaración de retorno en formato Python.
    }
    ;

expression:
    NUMBER {
        $$ = new_node(yytext); // Crear un nuevo nodo con el número.
        $$.intval = atoi(yytext); // Convertir el texto a entero.
        printf("%d", $1); // Imprimir el número.
    }
    | IDENTIFIER {
        $$ = new_node(yytext); // Crear un nuevo nodo con el identificador.
        $$.intval = get_symbol_value(yytext); // Obtener el valor de la variable.
        printf("%s", $1); // Imprimir el identificador.
    }
    ;

identifier:
    IDENTIFIER {
        $$ = strdup($1); // Duplicar el identificador.
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s); // Imprimir mensaje de error.
}

int main() {
    yyparse(); // Iniciar el análisis sintáctico.
    return 0;
}