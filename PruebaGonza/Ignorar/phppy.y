%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern int yyparse();
extern FILE *yyin;
void yyerror(const char *s);

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
        char* new_str = strdup(str + 1);
        new_str[len - 2] = '\0';
        return new_str;
    }
    return strdup(str);
}

char* replace_dollar(const char* str) {
    char* result = malloc(strlen(str) + 1);
    char* dst = result;
    for (const char* src = str; *src; src++) {
        if (*src == '$') {
            *dst++ = ' ';
        } else {
            *dst++ = *src;
        }
    }
    *dst = '\0';
    return result;
}
%}

%union {
    char *strval;
}

%token PHP_START PHP_END SEMICOLON ASSIGN DEFINE LPAREN RPAREN LBRACE RBRACE COMMA ARRAY
%token IF ECHO_TOKEN IS_INT IS_STRING IS_ARRAY IS_FLOAT IS_BOOL
%token <strval> VARIABLE INTEGER FLOAT CHAR STRING BOOL
%type <strval> value array_value value_list

%%

program: PHP_START statements PHP_END
    ;

statements: statement
    | statements statement
    ;

statement: variable_assignment
    | constant_declaration
    | if_statement
    | error SEMICOLON { yyerrok; }
    ;

variable_assignment: VARIABLE ASSIGN value SEMICOLON
    {
        char *type;
        if (strchr($3, '"') != NULL) {
            type = "str";
        } else if (strchr($3, '.') != NULL) {
            type = "float";
        } else if (strcmp($3, "True") == 0 || strcmp($3, "False") == 0) {
            type = "bool";
        } else if ($3[0] == '[') {
            type = "List[Any]";
        } else {
            type = "int";
        }
        add_symbol($1, type);
        printf("%s: %s = %s\n", $1, type, $3);
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
        printf("%s: %s = %s\n", constant_name, type, $5);
        free(constant_name);
    }
    ;

if_statement: IF LPAREN type_check_func LPAREN VARIABLE RPAREN RPAREN LBRACE ECHO_TOKEN STRING SEMICOLON RBRACE
    {
        char *type = get_symbol_type($5);
        char *py_type;
        if (strcmp(type, "int") == 0) py_type = "int";
        else if (strcmp(type, "str") == 0) py_type = "str";
        else if (strcmp(type, "List[Any]") == 0) py_type = "list";
        else if (strcmp(type, "float") == 0) py_type = "float";
        else if (strcmp(type, "bool") == 0) py_type = "bool";
        else py_type = "object";
        
        char *message = replace_dollar($10);
        printf("if isinstance(%s, %s):\n    print(f\"%s\")\n", $5, py_type, message);
        free(message);
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
    return 0;
}