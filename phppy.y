%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern int yyparse();
extern FILE *yyin;
void yyerror(const char *s);

// Variable global para almacenar la salida generada
char *output = NULL;

// Symbol table
#define MAX_SYMBOLS 100
struct symbol {
    char *name;
    char *type;
};
struct symbol symbol_table[MAX_SYMBOLS];
int symbol_count = 0;

void add_symbol(const char *name, const char *type) {
    if (symbol_count < MAX_SYMBOLS) {
        symbol_table[symbol_count].name = strdup(name);
        symbol_table[symbol_count].type = strdup(type);
        symbol_count++;
    } else {
        fprintf(stderr, "Symbol table full\n");
        exit(1);
    }
}

char* get_symbol_type(const char *name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return symbol_table[i].type;
        }
    }
    return "Unknown";
}

char* strip_quotes(const char* str) {
    int len = strlen(str);
    if (len >= 2 && str[0] == '"' && str[len-1] == '"') {
        char* new_str = malloc(len - 1);
        strncpy(new_str, str + 1, len - 2);
        new_str[len - 2] = '\0';
        
        // Replace \\n with actual newlines
        char* src = new_str;
        char* dst = new_str;
        while (*src) {
            if (*src == '\\' && *(src+1) == 'n') {
                *dst++ = '\n';
                src += 2;
            } else {
                *dst++ = *src++;
            }
        }
        *dst = '\0';
        
        return new_str;
    }
    return strdup(str);
}

char* remove_newlines(const char* str) {
    char* result = strdup(str);
    char* dst = result;
    for (const char* src = str; *src; src++) {
        if (*src != '\n') {
            *dst++ = *src;
        }
    }
    *dst = '\0';
    return result;
}

// Función auxiliar para agregar indentación a cada línea de código
char* indent_code(const char* code) {
    const char* indent = "    "; // Usar cuatro espacios para la indentación
    size_t indent_len = strlen(indent);
    size_t code_len = strlen(code);
    
    // Contar el número de líneas en el código
    size_t lines = 0;
    for (const char* p = code; *p; ++p) {
        if (*p == '\n') {
            ++lines;
        }
    }
    
    // Asignar memoria para el código con indentación
    char* result = malloc(code_len + lines * indent_len + 1);
    if (!result) {
        fprintf(stderr, "Error al asignar memoria para el código indentado\n");
        exit(1);
    }
    
    // Agregar la indentación a cada línea
    const char* src = code;
    char* dst = result;
    while (*src) {
        // Copiar la indentación
        strcpy(dst, indent);
        dst += indent_len;
        
        // Copiar la línea hasta el siguiente '\n'
        while (*src && *src != '\n') {
            *dst++ = *src++;
        }
        
        // Copiar el '\n'
        if (*src == '\n') {
            *dst++ = *src++;
        }
    }
    
    // Terminar la cadena resultante
    *dst = '\0';
    
    return result;
}

// Function to replace '$' with ''
char* replace_dollar(const char* str) {
    char *result = malloc(strlen(str));
    int j = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] != '$') {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    return result;
}
%}

%union {
    char *strval;
}

%token PHP_START PHP_END SEMICOLON ASSIGN DEFINE LPAREN RPAREN LBRACE RBRACE COMMA ARRAY GT LT EQ COLON LE NE
%token IF ELSEIF ELSE ECHO_TOKEN IS_INT IS_STRING IS_ARRAY IS_FLOAT IS_BOOL WHILE ENDWHILE INCREMENT
%token <strval> VARIABLE INTEGER FLOAT CHAR STRING BOOL
%type <strval> value array_value value_list statements statement condicion variable_assignment echo_statement if_statement variable_declaration constant_declaration elseif_clauses elseif_clause else_clause while_statement

%%

program: PHP_START statements PHP_END
{
    output = $2;
}
;

statements: statement
    | statements statement
    {
        //printf("DEBUG: concatenating statements: '%s' and '%s'\n", $1, $2);
        char *result = malloc(strlen($1) + strlen($2) + 1);
        sprintf(result, "%s%s", $1, $2);
        $$ = result;
        //printf("DEBUG: result of concatenation: '%s'\n", result);
    }
    ;


statement: variable_assignment
    | variable_declaration
    | constant_declaration
    | if_statement
    | while_statement
    | echo_statement
    | error SEMICOLON { yyerrok; }
    ;

variable_declaration: VARIABLE SEMICOLON
{
    char *var_name = $1 + 1;  // Skip the '$' character
    char *result = malloc(strlen(var_name) + 10);
    sprintf(result, "%s = None\n", var_name);
    $$ = result;
}
;

variable_assignment: VARIABLE ASSIGN value SEMICOLON
{
    char *var_name = $1 + 1;  // Skip the '$' character
    char *result = malloc(strlen(var_name) + strlen($3) + 5);
    if ($3 && strlen($3) > 0) {
        sprintf(result, "%s = %s\n", var_name, $3);
    } else {
        sprintf(result, "%s = None\n", var_name);
    }
    $$ = result;
}
| VARIABLE ASSIGN VARIABLE SEMICOLON
{
    char *var_name = $1 + 1;  // Skip the '$' character
    char *value_name = $3 + 1;  // Skip the '$' character
    char *result = malloc(strlen(var_name) + strlen(value_name) + 5);
    sprintf(result, "%s = %s\n", var_name, value_name);
    $$ = result;
}
| VARIABLE ASSIGN SEMICOLON
{
    char *var_name = $1 + 1;  // Skip the '$' character
    char *result = malloc(strlen(var_name) + 10);
    sprintf(result, "%s = None\n", var_name);
    $$ = result;
}
| VARIABLE INCREMENT SEMICOLON
{
    char *var_name = $1 + 1;  // Skip the '$' character
    //printf("DEBUG: variable_increment - var_name = '%s'\n", var_name);
    char *result = malloc(strlen(var_name) + 7); // Tamaño necesario para " += 1\n" y terminador nulo
    sprintf(result, "%s += 1\n", var_name);
    $$ = result;
}
;

echo_statement: ECHO_TOKEN value SEMICOLON
{
    char *result = malloc(strlen($2) + 8);
    sprintf(result, "print(%s)\n", $2);
    $$ = result;
}
| ECHO_TOKEN VARIABLE SEMICOLON
{
    char *var_name = $2 + 1;  // Skip the '$' character
    char *result = malloc(strlen(var_name) + 10);
    sprintf(result, "print(%s)\n", var_name);
    $$ = result;
}
| ECHO_TOKEN VARIABLE INCREMENT SEMICOLON
{
    char *var_name = $2 + 1;  // Skip the '$' character
    char *result = malloc(strlen(var_name) + 10);
    sprintf(result, "print(%s)\n%s += 1\n", var_name, var_name);
    $$ = result;
}
;



constant_declaration: DEFINE LPAREN STRING COMMA value RPAREN SEMICOLON
{
    char* constant_name = strip_quotes($3);
    char *type;
    if (strchr($5, '"') != NULL) {
        type = "str";
    } else if (strchr($5, '.') != NULL) {
        type = "float";
    } else if (strcmp($5, "True") == 0 || strcmp($5, "False") == 0) {
        type = "bool";
    } else if ($5[0] == '[') {
        type = "List[Any]";
    } else {
        type = "int";
    }
    add_symbol(constant_name, type);
    char *result = malloc(strlen(constant_name) + strlen(type) + strlen($5) + 10);
    sprintf(result, "%s: %s = %s\n", constant_name, type, $5);
    free(constant_name);
    $$ = result;
}
;

if_statement: IF LPAREN type_check_func LPAREN VARIABLE RPAREN RPAREN LBRACE ECHO_TOKEN STRING SEMICOLON RBRACE
{
    char *type = get_symbol_type($5 + 1);  // Skip the '$' character
    char *py_type;
    if (strcmp(type, "int") == 0) py_type = "int";
    else if (strcmp(type, "str") == 0) py_type = "str";
    else if (strcmp(type, "list") == 0) py_type = "list";
    else if (strcmp(type, "float") == 0) py_type = "float";
    else if (strcmp(type, "bool") == 0) py_type = "bool";
    else py_type = "object";
    
    char *unquoted = strip_quotes($10);
    char *message = replace_dollar(unquoted);
    // Remove newlines and format the print statement
    char *formatted_message = remove_newlines(message);
    printf("if isinstance(%s, %s):\n    print(%s, \"\\%s\")\n", $5 + 1, py_type, $5 + 1, formatted_message);
    free(unquoted);
    free(message);
    free(formatted_message);
}
| IF LPAREN condicion RPAREN LBRACE statements RBRACE elseif_clauses else_clause
{
    char *if_part = indent_code($6);
    char *result = malloc(strlen($3) + strlen(if_part) + strlen($8) + strlen($9) + 10);
    sprintf(result, "if (%s):\n%s%s%s", $3, if_part, $8, $9);
    $$ = result;
    free(if_part);
}
| IF LPAREN condicion RPAREN LBRACE statements RBRACE elseif_clauses
{
    char *if_part = indent_code($6);
    char *result = malloc(strlen($3) + strlen(if_part) + strlen($8) + 10);
    sprintf(result, "if (%s):\n%s%s", $3, if_part, $8);
    $$ = result;
    free(if_part);
}
| IF LPAREN condicion RPAREN LBRACE statements RBRACE else_clause
{
    char *if_part = indent_code($6);
    char *result = malloc(strlen($3) + strlen(if_part) + strlen($8) + 20);
    sprintf(result, "if (%s):\n%s%s", $3, if_part, $8);
    $$ = result;
    free(if_part);
}
| IF LPAREN condicion RPAREN LBRACE statements RBRACE
{
    //printf("DEBUG: if_statement - statements = '%s'\n", $6);
    char *if_part = indent_code($6);
    char *result = malloc(strlen($3) + strlen(if_part) + 10);
    sprintf(result, "if (%s):\n%s", $3, if_part);
    $$ = result;
    free(if_part);
}
// PARA AGREGAR PASS
| IF LPAREN condicion RPAREN LBRACE RBRACE
{
    char *result = malloc(strlen($3) + 15);
    sprintf(result, "if (%s):\n    pass\n", $3);
    $$ = result;
}
| IF LPAREN condicion RPAREN LBRACE statements RBRACE ELSE LBRACE RBRACE
{
    char *indented_statements_if = indent_code($6);
    char *result = malloc(strlen($3) + strlen(indented_statements_if) + 20);
    sprintf(result, "if (%s):\n%selse:\n    pass\n", $3, indented_statements_if);
    $$ = result;
    free(indented_statements_if);
}
| IF LPAREN condicion RPAREN LBRACE RBRACE ELSE LBRACE statements RBRACE
{
    char *indented_statements_else = indent_code($9);
    char *result = malloc(strlen($3) + strlen(indented_statements_else) + 20);
    sprintf(result, "if (%s):\n    pass\nelse:\n%s", $3, indented_statements_else);
    $$ = result;
    free(indented_statements_else);
}
;


elseif_clauses: elseif_clause
    | elseif_clauses elseif_clause
    {
        char *result = malloc(strlen($1) + strlen($2) + 1);
        sprintf(result, "%s%s", $1, $2);
        $$ = result;
    }
    ;

elseif_clause: ELSEIF LPAREN condicion RPAREN LBRACE statements RBRACE
{
    char *elseif_part = indent_code($6);
    char *result = malloc(strlen($3) + strlen(elseif_part) + 10);
    sprintf(result, "elif (%s):\n%s", $3, elseif_part);
    $$ = result;
    free(elseif_part);
}
;

else_clause: ELSE LBRACE statements RBRACE
{
    char *else_part = indent_code($3);
    char *result = malloc(strlen(else_part) + 20);
    sprintf(result, "else:\n%s", else_part);
    $$ = result;
    free(else_part);
}
;

while_statement: WHILE LPAREN condicion RPAREN LBRACE statements RBRACE
{
    //printf("DEBUG: condicion = '%s'\n", $3);
    //printf("DEBUG: statements = '%s'\n", $6);
    char *indented_statements = indent_code($6);
    char *result = malloc(strlen($3) + strlen(indented_statements) + 15);
    sprintf(result, "while (%s):\n%s", $3, indented_statements);
    $$ = result;
    free(indented_statements);
}
| WHILE LPAREN condicion RPAREN COLON statements ENDWHILE SEMICOLON
{
    //printf("DEBUG: condicion = '%s'\n", $3);
    //printf("DEBUG: statements = '%s'\n", $6);
    char *indented_statements = indent_code($6);
    char *result = malloc(strlen($3) + strlen(indented_statements) + 15);
    sprintf(result, "while (%s):\n%s", $3, indented_statements);
    $$ = result;
    free(indented_statements);
}
//PARA AGREGAR PASS
| WHILE LPAREN condicion RPAREN LBRACE RBRACE
{
    char *result = malloc(strlen($3) + 15);
    sprintf(result, "while (%s):\n    pass\n", $3);
    $$ = result;
}
| WHILE LPAREN condicion RPAREN COLON ENDWHILE SEMICOLON
{
    printf("DEBUG: while_statement - condicion = '%s' (empty block)\n", $3);
    char *result = malloc(strlen($3) + 15);
    sprintf(result, "while (%s):\n    pass\n", $3);
    $$ = result;
}
;



condicion: 
    VARIABLE GT VARIABLE
    {
        $$ = (char *) malloc(strlen($1) + strlen($3) + 4); // 4: para espacio, operador, espacio, y terminador nulo
        sprintf($$, "%s > %s", $1 + 1, $3 + 1); // Omitimos el carácter '$'
    }
    | VARIABLE LT VARIABLE
    {
        $$ = (char *) malloc(strlen($1) + strlen($3) + 4);
        sprintf($$, "%s < %s", $1 + 1, $3 + 1); // Omitimos el carácter '$'
    }
    | VARIABLE EQ VARIABLE
    {
        $$ = (char *) malloc(strlen($1) + strlen($3) + 4);
        sprintf($$, "%s == %s", $1 + 1, $3 + 1); // En Python se usa '==' para la igualdad
    }
    | VARIABLE GT value 
    {
        $$ = (char *) malloc(strlen($1) + strlen($3) + 4); // 4: para espacio, operador, espacio, y terminador nulo
        sprintf($$, "%s > %s", $1 + 1, $3); // Omitimos el carácter '$'
    }
    | VARIABLE LT value
    {
        $$ = (char *) malloc(strlen($1) + strlen($3) + 4);
        sprintf($$, "%s < %s", $1 + 1, $3); // Omitimos el carácter '$'
    }
    | VARIABLE EQ value
    {
        $$ = (char *) malloc(strlen($1) + strlen($3) + 4);
        sprintf($$, "%s == %s", $1 + 1, $3); // En Python se usa '==' para la igualdad
    }
    | VARIABLE LE VARIABLE
    {
        $$ = (char *) malloc(strlen($1) + strlen($3) + 5);
        sprintf($$, "%s <= %s", $1 + 1, $3 + 1); // Omitimos el carácter '$'
    }
    | VARIABLE LE value
    {
        $$ = (char *) malloc(strlen($1) + strlen($3) + 5);
        sprintf($$, "%s <= %s", $1 + 1, $3); // Omitimos el carácter '$'
    }
    | value EQ value
    {
        $$ = (char *) malloc(strlen($1) + strlen($3) + 4);
        sprintf($$, "%s == %s", $1, $3); // En Python se usa '==' para la igualdad
    }
    | value NE value
    {
        $$ = (char *) malloc(strlen($1) + strlen($3) + 5);
        sprintf($$, "%s != %s", $1, $3); // En Python se usa '!=' para desigualdad
    }
;


type_check_func: IS_INT | IS_STRING | IS_ARRAY | IS_FLOAT | IS_BOOL
;

value: INTEGER { $$ = $1; }
    | FLOAT { $$ = $1; }
    | CHAR { $$ = $1; }
    | STRING { $$ = $1; }
    | BOOL { $$ = $1; }
    | array_value { $$ = $1; }
;

array_value: ARRAY LPAREN value_list RPAREN
{
    char *result = malloc(strlen($3) + 3);
    sprintf(result, "[%s]", $3);
    $$ = result;
}
;

value_list: value
{
    $$ = $1;
}
| value_list COMMA value
{
    char *result = malloc(strlen($1) + strlen($3) + 2);
    sprintf(result, "%s, %s", $1, $3);
    $$ = result;
}
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}

int main() {
    yyin = stdin;
    do {
        yyparse();
    } while (!feof(yyin));
    
    if (output) {
        printf("%s", output);
        free(output);
    }
    return 0;
}
