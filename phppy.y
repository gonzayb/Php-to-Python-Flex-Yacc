%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaración de funciones externas
extern int yylex();  // Función para realizar el análisis léxico
extern int yyparse();  // Función para realizar el análisis sintáctico
extern FILE *yyin;  // Puntero al archivo de entrada para el análisis

// Función para manejar errores de análisis
void yyerror(const char *s);

char *error_messages[100];
int error_count = 0;

// Variable global para almacenar la salida generada
char *output = NULL;

// Definición de la tabla de símbolos
#define MAX_SYMBOLS 100  // Máximo número de símbolos en la tabla

// Estructura para representar un símbolo en la tabla
struct symbol {
    char *name;  // Nombre del símbolo
    char *type;  // Tipo del símbolo
};

// Declaración de la tabla de símbolos y el contador de símbolos
struct symbol symbol_table[MAX_SYMBOLS];
int symbol_count = 0;

// Función para agregar un símbolo a la tabla
void add_symbol(const char *name, const char *type) {
    if (symbol_count < MAX_SYMBOLS) {
        // Copia el nombre y tipo del símbolo a la tabla
        symbol_table[symbol_count].name = strdup(name);
        symbol_table[symbol_count].type = strdup(type);
        symbol_count++;  // Incrementa el contador de símbolos
    } else {
        // Error si la tabla está llena
        fprintf(stderr, "Tabla de simbolos llena\n");
        exit(1);
    }
}

// Función para obtener el tipo de un símbolo dado su nombre
char* get_symbol_type(const char *name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return symbol_table[i].type;
        }
    }
    return "Unknown";  // Devuelve "Unknown" si el símbolo no está en la tabla
}

// Función para eliminar las comillas de una cadena
char* strip_quotes(const char* str) {
    int len = strlen(str);
    if (len >= 2 && str[0] == '"' && str[len-1] == '"') {
        char* new_str = malloc(len - 1);  // Asigna memoria para la nueva cadena
        strncpy(new_str, str + 1, len - 2);  // Copia la cadena sin las comillas
        new_str[len - 2] = '\0';
        
        // Reemplaza \\n con saltos de línea reales
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
    return strdup(str);  // Devuelve la cadena original si no tiene comillas
}

// Función para eliminar los saltos de línea de una cadena
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
    const char* indent = "    ";  // Usar cuatro espacios para la indentación
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

// Función para reemplazar '$' con ''
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

// Declaración del parser Bison
%}

%union {
    char *strval;
}

// Declaración de tokens
%token PHP_START PHP_END SEMICOLON ASSIGN DEFINE LPAREN RPAREN LBRACE RBRACE COMMA ARRAY GT LT EQ COLON LE NE ARROW LBRACKET RBRACKET DOLLAR
%token IF ELSEIF ELSE ECHO_TOKEN IS_INT IS_STRING IS_ARRAY IS_FLOAT IS_BOOL WHILE ENDWHILE INCREMENT RETURN FUNCTION GLOBAL PLUS CLASS NEW PUBLIC PROTECTED PRIVATE ARROW_OBJ
%token <strval> VARIABLE INTEGER FLOAT CHAR STRING BOOL IDENTIFIER

// Declaración de tipos para las producciones
%type <strval> value array_value value_list statements statement condicion variable_assignment echo_statement if_statement variable_declaration 
constant_declaration elseif_clauses elseif_clause else_clause while_statement function_declaration parameter_list function_call argument_list 
key_value_list key_value_pair array_declaration array_item array_items global_statement variable_list expression class_declaration class_body 
class_method class_member class_property object_creation


%%

// Definición de la regla principal del programa
program: PHP_START statements PHP_END
{
    output = $2;  // Asigna las sentencias generadas a la variable global 'output'
}
;

// Definición de la regla para las sentencias
statements: statement  // Una sola sentencia
    | statements statement  // Concatenación de dos sentencias
    {
        char *result = malloc(strlen($1) + strlen($2) + 1);  // Reserva memoria para el resultado concatenado
        sprintf(result, "%s%s", $1, $2);  // Concatenar las dos sentencias
        $$ = result;  // Almacena el resultado concatenado
    }
    | statements RETURN value SEMICOLON  // Sentencia de retorno de un valor
    {
        char *result = malloc(strlen($1) + strlen($3) + 10);  // Reserva memoria para la sentencia de retorno
        sprintf(result, "%sreturn %s\n", $1, $3);  // Formatea la sentencia de retorno
        $$ = result;  // Almacena la sentencia de retorno
    }
    | statements RETURN VARIABLE SEMICOLON  // Sentencia de retorno de una variable
    {
        char *result = malloc(strlen($1) + strlen($3) + 10);  // Reserva memoria para la sentencia de retorno
        sprintf(result, "%sreturn %s\n", $1, $3 + 1);  // Omite el carácter '$' de la variable y formatea la sentencia de retorno
        $$ = result;  // Almacena la sentencia de retorno
    }
    | error SEMICOLON { printf("Error in statements, skipping to next statement.\n"); yyerrok; }
    ;

// Definición de la regla para una sentencia
statement: variable_assignment  // Asignación de una variable
    | variable_declaration  // Declaración de una variable
    | constant_declaration  // Declaración de una constante
    | if_statement  // Sentencia condicional 'if'
    | while_statement  // Sentencia de bucle 'while'
    | echo_statement  // Sentencia 'echo' para imprimir
    | function_declaration  // Declaración de una función
    | function_call  // Llamada a una función
    | global_statement  // Declaración de variables globales
    | class_declaration // Declaracion de una clase
    | object_creation // Creacion de objeto
    | expression SEMICOLON // Expresion sola
    | error SEMICOLON { yyerrok; }  // Manejo de errores
    ;

// Declaración de una variable
variable_declaration: VARIABLE SEMICOLON
{
    char *var_name = $1 + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + 10);  // Reserva memoria para la declaración de la variable
    sprintf(result, "%s = None\n", var_name);  // Asigna 'None' a la variable en Python
    $$ = result;  // Almacena la declaración de la variable
}
| VARIABLE error { printf("Missing ';' in variable declaration.\n"); yyerrok; }
;

// Asignación de una variable
variable_assignment: VARIABLE ASSIGN value SEMICOLON  // Asignación de un valor a una variable
{
    char *var_name = $1 + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + strlen($3) + 5);  // Reserva memoria para la asignación
    if ($3 && strlen($3) > 0) {
        sprintf(result, "%s = %s\n", var_name, $3);  // Asigna el valor a la variable
    } else {
        sprintf(result, "%s = None\n", var_name);  // Asigna 'None' si el valor está vacío
    }
    $$ = result;  // Almacena la asignación
}
| VARIABLE ASSIGN VARIABLE SEMICOLON  // Asignación de una variable a otra variable
{
    char *var_name = $1 + 1;  // Omite el carácter '$' de la variable
    char *value_name = $3 + 1;  // Omite el carácter '$' del valor
    char *result = malloc(strlen(var_name) + strlen(value_name) + 5);  // Reserva memoria para la asignación
    sprintf(result, "%s = %s\n", var_name, value_name);  // Asigna la variable a otra variable
    $$ = result;  // Almacena la asignación
}
| VARIABLE ASSIGN SEMICOLON  // Asignación de 'None' a una variable
{
    char *var_name = $1 + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + 10);  // Reserva memoria para la asignación
    sprintf(result, "%s = None\n", var_name);  // Asigna 'None' a la variable
    $$ = result;  // Almacena la asignación
}
| VARIABLE INCREMENT SEMICOLON  // Incremento de una variable
{
    char *var_name = $1 + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + 7);  // Reserva memoria para el incremento
    sprintf(result, "%s += 1\n", var_name);  // Incrementa la variable
    $$ = result;  // Almacena el incremento
}
| VARIABLE ASSIGN array_declaration SEMICOLON  // Asignación de una declaración de array a una variable
{
    char *var_name = $1 + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + strlen($3) + 5);  // Reserva memoria para la asignación
    sprintf(result, "%s = %s\n", var_name, $3);  // Asigna la declaración de array a la variable
    $$ = result;  // Almacena la asignación
}
| VARIABLE ASSIGN expression SEMICOLON  // Asignación de una expresión a una variable
{
    char *var_name = $1 + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + strlen($3) + 5);  // Reserva memoria para la asignación
    sprintf(result, "%s = %s\n", var_name, $3);  // Asigna la expresión a la variable
    $$ = result;  // Almacena la asignación
}
| VARIABLE ASSIGN value error { printf("Missing ';' in variable assignment.\n"); yyerrok; }
;

// Definición de una expresión
expression: VARIABLE PLUS VARIABLE  // Suma de dos variables
{
    char *result = malloc(strlen($1) + strlen($3) + 4);  // Reserva memoria para la suma
    sprintf(result, "%s + %s", $1 + 1, $3 + 1);  // Omite el carácter '$' y suma las variables
    $$ = result;  // Almacena la expresión
}
| VARIABLE ARROW_OBJ IDENTIFIER LPAREN RPAREN
{
    char *var_name = $1 + 1;  // Omite el carácter '$'
    char *method_name = $3;
    char *result = malloc(strlen(var_name) + strlen(method_name) + 4);
    sprintf(result, "%s.%s()\n", var_name, method_name);
    $$ = result;
}
;


// Definición de la sentencia 'echo'
echo_statement: ECHO_TOKEN value SEMICOLON  // Sentencia 'echo' con un valor
{
    char *result = malloc(strlen($2) + 8);  // Reserva memoria para la sentencia 'echo'
    sprintf(result, "print(%s)\n", $2);  // Imprime el valor
    $$ = result;  // Almacena la sentencia 'echo'
}
| ECHO_TOKEN VARIABLE SEMICOLON  // Sentencia 'echo' con una variable
{
    char *var_name = $2 + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + 10);  // Reserva memoria para la sentencia 'echo'
    sprintf(result, "print(%s)\n", var_name);  // Imprime la variable
    $$ = result;  // Almacena la sentencia 'echo'
}
| ECHO_TOKEN VARIABLE INCREMENT SEMICOLON  // Sentencia 'echo' con una variable incrementada
{
    char *var_name = $2 + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + 10);  // Reserva memoria para la sentencia 'echo'
    sprintf(result, "print(%s)\n%s += 1\n", var_name, var_name);  // Imprime e incrementa la variable
    $$ = result;  // Almacena la sentencia 'echo'
}
| ECHO_TOKEN VARIABLE ARROW_OBJ PUBLIC SEMICOLON
{
    char *var_name = $2 + 1;  // Omite el carácter '$'
    char *property_name = "public";
    char *result = malloc(strlen(var_name) + strlen(property_name) + 10);
    sprintf(result, "print(self.%s)\n", property_name);
    $$ = result;
}
| ECHO_TOKEN VARIABLE ARROW_OBJ PROTECTED SEMICOLON
{
    char *var_name = $2 + 1;  // Omite el carácter '$'
    char *property_name = "_protected";
    char *result = malloc(strlen(var_name) + strlen(property_name) + 10);
    sprintf(result, "print(self.%s)\n", property_name);
    $$ = result;
}
| ECHO_TOKEN VARIABLE ARROW_OBJ PRIVATE SEMICOLON
{
    char *var_name = $2 + 1;  // Omite el carácter '$'
    char *property_name = "__private";
    char *result = malloc(strlen(var_name) + strlen(property_name) + 10);
    sprintf(result, "print(self.%s)\n", property_name);
    $$ = result;
}
| ECHO_TOKEN error { printf("Missing ';' in echo statement.\n"); yyerrok; }
;



// Definición de la sentencia 'global'
global_statement: GLOBAL variable_list SEMICOLON  // Sentencia 'global' con una lista de variables
{
    char *result = malloc(strlen($2) + 8);  // Reserva memoria para la sentencia 'global'
    sprintf(result, "global %s\n", $2);  // Marca las variables como globales
    $$ = result;  // Almacena la sentencia 'global'
}
;

// Lista de variables
variable_list: VARIABLE  // Una sola variable
{
    $$ = $1 + 1;  // Omite el carácter '$'
}
| variable_list COMMA VARIABLE  // Lista de variables separadas por comas
{
    char *result = malloc(strlen($1) + strlen($3 + 1) + 3);  // Reserva memoria para la lista
    sprintf(result, "%s, %s", $1, $3 + 1);  // Omite el carácter '$' y agrega la variable a la lista
    $$ = result;  // Almacena la lista de variables
}
;

// Definición de una constante
constant_declaration: DEFINE LPAREN STRING COMMA value RPAREN SEMICOLON  // Declaración de una constante
{
    char* constant_name = strip_quotes($3);  // Elimina las comillas del nombre de la constante
    char *type;  // Tipo de la constante
    // Determina el tipo de la constante
    if (strchr($5, '"') != NULL) {
        type = "str";  // Tipo cadena de texto
    } else if (strchr($5, '.') != NULL) {
        type = "float";  // Tipo flotante
    } else if (strcmp($5, "True") == 0 || strcmp($5, "False") == 0) {
        type = "bool";  // Tipo booleano
    } else if ($5[0] == '[') {
        type = "List[Any]";  // Tipo lista
    } else {
        type = "int";  // Tipo entero
    }
    add_symbol(constant_name, type);  // Agrega la constante a la tabla de símbolos
    char *result = malloc(strlen(constant_name) + strlen(type) + strlen($5) + 10);  // Reserva memoria para la declaración de la constante
    sprintf(result, "%s: %s = %s\n", constant_name, type, $5);  // Define la constante en Python
    free(constant_name);  // Libera la memoria del nombre de la constante
    $$ = result;  // Almacena la declaración de la constante
}
;

if_statement: IF LPAREN type_check_func LPAREN VARIABLE RPAREN RPAREN LBRACE ECHO_TOKEN STRING SEMICOLON RBRACE
{
    char *type = get_symbol_type($5 + 1);  // Obtiene el tipo de la variable, omitiendo el carácter '$'
    char *py_type;  // Declara un puntero para el tipo en Python

    // Compara el tipo y asigna el tipo correspondiente en Python
    if (strcmp(type, "int") == 0) py_type = "int";
    else if (strcmp(type, "str") == 0) py_type = "str";
    else if (strcmp(type, "list") == 0) py_type = "list";
    else if (strcmp(type, "float") == 0) py_type = "float";
    else if (strcmp(type, "bool") == 0) py_type = "bool";
    else py_type = "object";  // Tipo genérico en caso de que no coincida con los anteriores
    
    char *unquoted = strip_quotes($10);  // Elimina las comillas de la cadena
    char *message = replace_dollar(unquoted);  // Reemplaza los caracteres '$' en la cadena
    char *formatted_message = remove_newlines(message);  // Elimina los saltos de línea y formatea el mensaje
    char *result = malloc(strlen($5 + 1) + strlen(py_type) + strlen(formatted_message) + 50); // Asegura suficiente espacio para el resultado
    sprintf(result, "if isinstance(%s, %s):\n    print(\"%s\")\n", $5 + 1, py_type, formatted_message);  // Imprime la sentencia 'if' en Python
    $$ = result;  // Asigna el resultado a la regla
    
    free(unquoted);  // Libera la memoria de 'unquoted'
    free(message);  // Libera la memoria de 'message'
    free(formatted_message);  // Libera la memoria de 'formatted_message'
}
| IF LPAREN condicion RPAREN LBRACE statements RBRACE elseif_clauses else_clause
{
    char *if_part = indent_code($6);  // Indenta el código del bloque 'if'
    char *result = malloc(strlen($3) + strlen(if_part) + strlen($8) + strlen($9) + 10);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n%s%s%s", $3, if_part, $8, $9);  // Formatea la sentencia 'if' con sus bloques 'elseif' y 'else'
    $$ = result;  // Almacena el resultado
    free(if_part);  // Libera la memoria de 'if_part'
}
| IF LPAREN condicion RPAREN LBRACE statements RBRACE elseif_clauses
{
    char *if_part = indent_code($6);  // Indenta el código del bloque 'if'
    char *result = malloc(strlen($3) + strlen(if_part) + strlen($8) + 10);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n%s%s", $3, if_part, $8);  // Formatea la sentencia 'if' con sus bloques 'elseif'
    $$ = result;  // Almacena el resultado
    free(if_part);  // Libera la memoria de 'if_part'
}
| IF LPAREN condicion RPAREN LBRACE statements RBRACE else_clause
{
    char *if_part = indent_code($6);  // Indenta el código del bloque 'if'
    char *result = malloc(strlen($3) + strlen(if_part) + strlen($8) + 20);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n%s%s", $3, if_part, $8);  // Formatea la sentencia 'if' con su bloque 'else'
    $$ = result;  // Almacena el resultado
    free(if_part);  // Libera la memoria de 'if_part'
}
| IF LPAREN condicion RPAREN LBRACE statements RBRACE
{
    char *if_part = indent_code($6);  // Indenta el código del bloque 'if'
    char *result = malloc(strlen($3) + strlen(if_part) + 10);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n%s", $3, if_part);  // Formatea la sentencia 'if'
    $$ = result;  // Almacena el resultado
    free(if_part);  // Libera la memoria de 'if_part'
}
//Para agregar PASS
| IF LPAREN condicion RPAREN LBRACE RBRACE
{
    char *result = malloc(strlen($3) + 15);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n    pass\n", $3);  // Formatea la sentencia 'if' con un bloque vacío
    $$ = result;  // Almacena el resultado
}
| IF LPAREN condicion RPAREN LBRACE statements RBRACE ELSE LBRACE RBRACE
{
    char *indented_statements_if = indent_code($6);  // Indenta el código del bloque 'if'
    char *result = malloc(strlen($3) + strlen(indented_statements_if) + 20);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n%selse:\n    pass\n", $3, indented_statements_if);  // Formatea la sentencia 'if' con un bloque 'else' vacío
    $$ = result;  // Almacena el resultado
    free(indented_statements_if);  // Libera la memoria de 'indented_statements_if'
}
| IF LPAREN condicion RPAREN LBRACE RBRACE ELSE LBRACE statements RBRACE
{
    char *indented_statements_else = indent_code($9);  // Indenta el código del bloque 'else'
    char *result = malloc(strlen($3) + strlen(indented_statements_else) + 20);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n    pass\nelse:\n%s", $3, indented_statements_else);  // Formatea la sentencia 'if' con un bloque 'else'
    $$ = result;  // Almacena el resultado
    free(indented_statements_else);  // Libera la memoria de 'indented_statements_else'
}
;

elseif_clauses: elseif_clause
    | elseif_clauses elseif_clause
    {
        char *result = malloc(strlen($1) + strlen($2) + 1);  // Reserva memoria para el resultado
        sprintf(result, "%s%s", $1, $2);  // Concatenar las cláusulas 'elseif'
        $$ = result;  // Almacena el resultado
    }
    ;

elseif_clause: ELSEIF LPAREN condicion RPAREN LBRACE statements RBRACE
{
    char *elseif_part = indent_code($6);  // Indenta el código del bloque 'elseif'
    char *result = malloc(strlen($3) + strlen(elseif_part) + 10);  // Reserva memoria para el resultado
    sprintf(result, "elif (%s):\n%s", $3, elseif_part);  // Formatea la cláusula 'elseif'
    $$ = result;  // Almacena el resultado
    free(elseif_part);  // Libera la memoria de 'elseif_part'
}
;

else_clause: ELSE LBRACE statements RBRACE
{
    char *else_part = indent_code($3);  // Indenta el código del bloque 'else'
    char *result = malloc(strlen(else_part) + 20);  // Reserva memoria para el resultado
    sprintf(result, "else:\n%s", else_part);  // Formatea la cláusula 'else'
    $$ = result;  // Almacena el resultado
    free(else_part);  // Libera la memoria de 'else_part'
}
;

while_statement: WHILE LPAREN condicion RPAREN LBRACE statements RBRACE
{
    char *indented_statements = indent_code($6);  // Indenta el código del bloque 'while'
    char *result = malloc(strlen($3) + strlen(indented_statements) + 15);  // Reserva memoria para el resultado
    sprintf(result, "while (%s):\n%s", $3, indented_statements);  // Formatea la sentencia 'while'
    $$ = result;  // Almacena el resultado
    free(indented_statements);  // Libera la memoria de 'indented_statements'
}
| WHILE LPAREN condicion RPAREN COLON statements ENDWHILE SEMICOLON
{
    char *indented_statements = indent_code($6);  // Indenta el código del bloque 'while'
    char *result = malloc(strlen($3) + strlen(indented_statements) + 15);  // Reserva memoria para el resultado
    sprintf(result, "while (%s):\n%s", $3, indented_statements);  // Formatea la sentencia 'while'
    $$ = result;  // Almacena el resultado
    free(indented_statements);  // Libera la memoria de 'indented_statements'
}
| WHILE LPAREN condicion RPAREN LBRACE RBRACE
{
    char *result = malloc(strlen($3) + 15);  // Reserva memoria para el resultado
    sprintf(result, "while (%s):\n    pass\n", $3);  // Formatea la sentencia 'while' con un bloque vacío
    $$ = result;  // Almacena el resultado
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

//Define los tipos de funciones para comprobar el tipo de datos
type_check_func: IS_INT | IS_STRING | IS_ARRAY | IS_FLOAT | IS_BOOL
;

value: INTEGER { $$ = $1; }
    | FLOAT { $$ = $1; }
    | CHAR { $$ = $1; }
    | STRING { $$ = $1; }
    | BOOL { $$ = $1; }
    | array_value { $$ = $1; }
    | VARIABLE LBRACKET value RBRACKET
    {
        char *result = malloc(strlen($1) + strlen($3) + 4);
        sprintf(result, "%s[%s]", $1 + 1, $3);  // Omite el carácter '$' y formatea la variable con el índice
        $$ = result;  // Asigna el resultado formateado
    }
    | VARIABLE LBRACKET STRING RBRACKET
    {
        char *key = strip_quotes($3);  // Elimina las comillas de la cadena
        char *result = malloc(strlen($1) + strlen(key) + 4);
        sprintf(result, "%s[%s]", $1 + 1, key);  // Omite el carácter '$' y formatea la variable con la clave
        free(key);  // Libera la memoria de la clave
        $$ = result;  // Asigna el resultado formateado
    }
;

array_value: ARRAY LPAREN RPAREN
{
    $$ = strdup("{}");  // Representa un array vacío
}
| ARRAY LPAREN value_list RPAREN
{
    char *result = malloc(strlen($3) + 3);
    sprintf(result, "[%s]", $3);  // Formatea la lista de valores como un array en Python
    $$ = result;  // Asigna el resultado formateado
}
| ARRAY LPAREN key_value_list RPAREN
{
    char *result = malloc(strlen($3) + 3);
    sprintf(result, "{%s}", $3);  // Formatea la lista de pares clave-valor como un diccionario en Python
    $$ = result;  // Asigna el resultado formateado
}
| ARRAY LPAREN key_value_pair RPAREN
{
    char *result = malloc(strlen($3) + 3);
    sprintf(result, "{%s}", $3);  // Formatea un único par clave-valor como un diccionario en Python
    $$ = result;  // Asigna el resultado formateado
}
;

key_value_list: key_value_pair
{
    $$ = $1;  // Asigna el único par clave-valor a `$$`
}
| key_value_list COMMA key_value_pair
{
    char *result = malloc(strlen($1) + strlen($3) + 2);
    sprintf(result, "%s, %s", $1, $3);  // Concadena pares clave-valor con coma
    $$ = result;  // Asigna el resultado formateado
}
;

key_value_pair: STRING ARROW value
{
    char *key = $1;  // Asigna la clave
    char *result = malloc(strlen(key) + strlen($3) + 4);
    sprintf(result, "%s: %s", key, $3);  // Formatea el par clave-valor
    free(key);  // Libera la memoria de la clave
    $$ = result;  // Asigna el resultado formateado
}
| IDENTIFIER ARROW value
{
    char *result = malloc(strlen($1) + strlen($3) + 4);
    sprintf(result, "\"%s\": %s", $1, $3);  // Formatea el par clave-valor con identificador como clave
    $$ = result;  // Asigna el resultado formateado
}
;

value_list: value
{
    $$ = $1;  // Asigna un único valor a `$$`
}
| value_list COMMA value
{
    char *result = malloc(strlen($1) + strlen($3) + 2);
    sprintf(result, "%s, %s", $1, $3);  // Concadena valores con coma
    $$ = result;  // Asigna el resultado formateado
}
;

function_declaration: FUNCTION IDENTIFIER LPAREN parameter_list RPAREN LBRACE statements RBRACE
{
    char *func_name = $2;  // Asigna el nombre de la función
    char *params = $4;  // Asigna los parámetros de la función
    char *body = indent_code($7);  // Indenta el cuerpo de la función
    char *result = malloc(strlen(func_name) + strlen(params) + strlen(body) + 20);
    sprintf(result, "def %s(%s):\n%s", func_name, params, body);  // Formatea la declaración de la función
    $$ = result;  // Asigna el resultado formateado
    free(body);  // Libera la memoria del cuerpo de la función
}
;

parameter_list: /* empty */
{
    $$ = strdup("");  // Representa una lista de parámetros vacía
}
| VARIABLE
{
    $$ = strdup($1 + 1);  // Omite el carácter '$' y representa una variable como parámetro
}
| IDENTIFIER
{
    $$ = strdup($1);  // Representa un identificador como parámetro
}
| parameter_list COMMA VARIABLE
{
    char *result = malloc(strlen($1) + strlen($3) + 2);
    sprintf(result, "%s, %s", $1, $3 + 1);  // Omite el carácter '$' y concatena variables como parámetros
    $$ = result;  // Asigna el resultado formateado
}
| parameter_list COMMA IDENTIFIER
{
    char *result = malloc(strlen($1) + strlen($3) + 2);
    sprintf(result, "%s, %s", $1, $3);  // Concatena identificadores como parámetros
    $$ = result;  // Asigna el resultado formateado
}
;

function_call: IDENTIFIER LPAREN argument_list RPAREN SEMICOLON
{
    char *func_name = $1;  // Asigna el nombre de la función
    char *args = $3;  // Asigna los argumentos de la función
    char *result = malloc(strlen(func_name) + strlen(args) + 5);
    sprintf(result, "%s(%s)\n", func_name, args);  // Formatea la llamada a la función
    $$ = result;  // Asigna el resultado formateado
}
;

argument_list: /* empty */
{
    $$ = strdup("");  // Representa una lista de argumentos vacía
}
| value
{
    $$ = strdup($1);  // Representa un único valor como argumento
}
| VARIABLE
{
    $$ = strdup($1 + 1);  // Omite el carácter '$' y representa una variable como argumento
}
| IDENTIFIER
{
    $$ = strdup($1);  // Representa un identificador como argumento
}
| argument_list COMMA value
{
    char *result = malloc(strlen($1) + strlen($3) + 2);
    sprintf(result, "%s, %s", $1, $3);  // Concatena valores como argumentos
    $$ = result;  // Asigna el resultado formateado
}
| argument_list COMMA VARIABLE
{
    char *result = malloc(strlen($1) + strlen($3) + 2);
    sprintf(result, "%s, %s", $1, $3 + 1);  // Omite el carácter '$' y concatena variables como argumentos
    $$ = result;  // Asigna el resultado formateado
}
| argument_list COMMA IDENTIFIER
{
    char *result = malloc(strlen($1) + strlen($3) + 2);
    sprintf(result, "%s, %s", $1, $3);  // Concatena identificadores como argumentos
    $$ = result;  // Asigna el resultado formateado
}
;

array_declaration: ARRAY LPAREN array_items RPAREN
{
    char *result = malloc(strlen($3) + 3);
    sprintf(result, "{%s}", $3);  // Formatea los ítems del array como un diccionario en Python
    $$ = result;  // Asigna el resultado formateado
}
| LBRACKET array_items RBRACKET
{
    char *result = malloc(strlen($2) + 3);
    sprintf(result, "{%s}", $2);  // Formatea los ítems del array como un diccionario en Python
    $$ = result;  // Asigna el resultado formateado
}
;

array_items: array_item
| array_items COMMA array_item
{
    char *result = malloc(strlen($1) + strlen($3) + 3);
    sprintf(result, "%s, %s", $1, $3);  // Concatena ítems del array con coma
    $$ = result;  // Asigna el resultado formateado
}
;

array_item: STRING ARROW array_declaration
{
    char *key = strip_quotes($1);  // Elimina las comillas de la clave
    char *result = malloc(strlen(key) + strlen($3) + 5);
    sprintf(result, "\"%s\": %s", key, $3);  // Formatea el ítem del array con clave y declaración de array
    free(key);  // Libera la memoria de la clave
    $$ = result;  // Asigna el resultado formateado
}
| STRING ARROW STRING
{
    char *key = strip_quotes($1);  // Elimina las comillas de la clave
    char *value = strip_quotes($3);  // Elimina las comillas del valor
    char *result = malloc(strlen(key) + strlen(value) + 5);
    sprintf(result, "\"%s\": \"%s\"", key, value);  // Formatea el ítem del array con clave y valor
    free(key);  // Libera la memoria de la clave
    free(value);  // Libera la memoria del valor
    $$ = result;  // Asigna el resultado formateado
}
| STRING ARROW INTEGER
{
    char *key = strip_quotes($1);  // Elimina las comillas de la clave
    char *result = malloc(strlen(key) + strlen($3) + 5);
    sprintf(result, "\"%s\": %s", key, $3);  // Formatea el ítem del array con clave y entero
    free(key);  // Libera la memoria de la clave
    $$ = result;  // Asigna el resultado formateado
}
;

class_declaration: CLASS IDENTIFIER LBRACE class_body RBRACE
{
    char *class_name = $2;  
    char *result = malloc(strlen(class_name) + strlen($4) + 20);
    sprintf(result, "class %s:\n%s", class_name, $4);
    $$ = result;
}
;

class_body: class_member
    | class_body class_member
{
    char *result = malloc(strlen($1) + strlen($2) + 1);
    sprintf(result, "%s%s", $1, $2);
    $$ = result;
}
;

class_member: class_property
    | class_method
;

class_property: PUBLIC VARIABLE ASSIGN value SEMICOLON
{
    char *property_name = $2 + 1;  // Omite el carácter '$'
    char *result = malloc(strlen(property_name) + strlen($4) + 30);
    sprintf(result, "    def __init__(self):\n        self.%s = %s\n", property_name, $4);
    $$ = result;
}
| PROTECTED VARIABLE ASSIGN value SEMICOLON
{
    char *property_name = $2 + 1;  // Omite el carácter '$' y añade un guion bajo
    char *result = malloc(strlen(property_name) + strlen($4) + 31);
    sprintf(result, "        self._%s = %s\n", property_name, $4);
    $$ = result;
}
| PRIVATE VARIABLE ASSIGN value SEMICOLON
{
    char *property_name = $2 + 1;  // Omite el carácter '$' y añade dos guiones bajos
    char *result = malloc(strlen(property_name) + strlen($4) + 32);
    sprintf(result, "        self.__%s = %s\n", property_name, $4);
    $$ = result;
}
;

class_method: PUBLIC FUNCTION IDENTIFIER LPAREN RPAREN LBRACE statements RBRACE
{
    char *method_name = $3;  
    char *indented_statements = indent_code(indent_code($7));
    char *result = malloc(strlen(method_name) + strlen(indented_statements) + 20);
    sprintf(result, "    def %s(self):\n%s", method_name, indented_statements);
    $$ = result;
    free(indented_statements);
}
| FUNCTION IDENTIFIER LPAREN RPAREN LBRACE statements RBRACE
{
    char *method_name = $2;  
    char *indented_statements = indent_code(indent_code($6));
    char *result = malloc(strlen(method_name) + strlen(indented_statements) + 20);
    sprintf(result, "    def %s(self):\n%s", method_name, indented_statements);
    $$ = result;
    free(indented_statements);
}
;

object_creation: VARIABLE ASSIGN NEW IDENTIFIER LPAREN RPAREN SEMICOLON
{
    char *var_name = $1 + 1;  // Omite el carácter '$'
    char *class_name = $4;
    char *result = malloc(strlen(var_name) + strlen(class_name) + 10);
    sprintf(result, "%s = %s()\n", var_name, class_name);
    $$ = result;
}
;


%%

void yyerror(const char *s) {  //Función de manejo de errores que se llama cuando ocurre un error de análisis
    fprintf(stderr, "Parse error: %s\n", s);  //Imprime un mensaje de error en la salida de error estándar
}

int main() {
    yyin = stdin; //Asigna la entrada estándar (stdin) a yyin, que es el archivo de entrada para el analizador generado por Bison
    do { 
        yyparse();  //Analizar la entrada
    } while (!feof(yyin));  //Bucle termina cuando se detecta el final del archivo
    
    if (output) {  //Verifica si output no es NULL
        printf("%s", output);  //Imprime su contenido en la salida estándar
        free(output);  //Libera la memoria asignada a output
    }
    return 0;  //Final exitoso
}