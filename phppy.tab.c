/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "phppy.y"

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

#line 228 "phppy.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "phppy.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PHP_START = 3,                  /* PHP_START  */
  YYSYMBOL_PHP_END = 4,                    /* PHP_END  */
  YYSYMBOL_SEMICOLON = 5,                  /* SEMICOLON  */
  YYSYMBOL_ASSIGN = 6,                     /* ASSIGN  */
  YYSYMBOL_DEFINE = 7,                     /* DEFINE  */
  YYSYMBOL_LPAREN = 8,                     /* LPAREN  */
  YYSYMBOL_RPAREN = 9,                     /* RPAREN  */
  YYSYMBOL_LBRACE = 10,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 11,                    /* RBRACE  */
  YYSYMBOL_COMMA = 12,                     /* COMMA  */
  YYSYMBOL_ARRAY = 13,                     /* ARRAY  */
  YYSYMBOL_GT = 14,                        /* GT  */
  YYSYMBOL_LT = 15,                        /* LT  */
  YYSYMBOL_EQ = 16,                        /* EQ  */
  YYSYMBOL_COLON = 17,                     /* COLON  */
  YYSYMBOL_LE = 18,                        /* LE  */
  YYSYMBOL_NE = 19,                        /* NE  */
  YYSYMBOL_ARROW = 20,                     /* ARROW  */
  YYSYMBOL_LBRACKET = 21,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 22,                  /* RBRACKET  */
  YYSYMBOL_DOLLAR = 23,                    /* DOLLAR  */
  YYSYMBOL_IF = 24,                        /* IF  */
  YYSYMBOL_ELSEIF = 25,                    /* ELSEIF  */
  YYSYMBOL_ELSE = 26,                      /* ELSE  */
  YYSYMBOL_ECHO_TOKEN = 27,                /* ECHO_TOKEN  */
  YYSYMBOL_IS_INT = 28,                    /* IS_INT  */
  YYSYMBOL_IS_STRING = 29,                 /* IS_STRING  */
  YYSYMBOL_IS_ARRAY = 30,                  /* IS_ARRAY  */
  YYSYMBOL_IS_FLOAT = 31,                  /* IS_FLOAT  */
  YYSYMBOL_IS_BOOL = 32,                   /* IS_BOOL  */
  YYSYMBOL_WHILE = 33,                     /* WHILE  */
  YYSYMBOL_ENDWHILE = 34,                  /* ENDWHILE  */
  YYSYMBOL_INCREMENT = 35,                 /* INCREMENT  */
  YYSYMBOL_RETURN = 36,                    /* RETURN  */
  YYSYMBOL_FUNCTION = 37,                  /* FUNCTION  */
  YYSYMBOL_GLOBAL = 38,                    /* GLOBAL  */
  YYSYMBOL_PLUS = 39,                      /* PLUS  */
  YYSYMBOL_CLASS = 40,                     /* CLASS  */
  YYSYMBOL_NEW = 41,                       /* NEW  */
  YYSYMBOL_PUBLIC = 42,                    /* PUBLIC  */
  YYSYMBOL_PROTECTED = 43,                 /* PROTECTED  */
  YYSYMBOL_PRIVATE = 44,                   /* PRIVATE  */
  YYSYMBOL_ARROW_OBJ = 45,                 /* ARROW_OBJ  */
  YYSYMBOL_VARIABLE = 46,                  /* VARIABLE  */
  YYSYMBOL_INTEGER = 47,                   /* INTEGER  */
  YYSYMBOL_FLOAT = 48,                     /* FLOAT  */
  YYSYMBOL_CHAR = 49,                      /* CHAR  */
  YYSYMBOL_STRING = 50,                    /* STRING  */
  YYSYMBOL_BOOL = 51,                      /* BOOL  */
  YYSYMBOL_IDENTIFIER = 52,                /* IDENTIFIER  */
  YYSYMBOL_YYACCEPT = 53,                  /* $accept  */
  YYSYMBOL_program = 54,                   /* program  */
  YYSYMBOL_statements = 55,                /* statements  */
  YYSYMBOL_statement = 56,                 /* statement  */
  YYSYMBOL_variable_declaration = 57,      /* variable_declaration  */
  YYSYMBOL_variable_assignment = 58,       /* variable_assignment  */
  YYSYMBOL_expression = 59,                /* expression  */
  YYSYMBOL_echo_statement = 60,            /* echo_statement  */
  YYSYMBOL_global_statement = 61,          /* global_statement  */
  YYSYMBOL_variable_list = 62,             /* variable_list  */
  YYSYMBOL_constant_declaration = 63,      /* constant_declaration  */
  YYSYMBOL_if_statement = 64,              /* if_statement  */
  YYSYMBOL_elseif_clauses = 65,            /* elseif_clauses  */
  YYSYMBOL_elseif_clause = 66,             /* elseif_clause  */
  YYSYMBOL_else_clause = 67,               /* else_clause  */
  YYSYMBOL_while_statement = 68,           /* while_statement  */
  YYSYMBOL_condicion = 69,                 /* condicion  */
  YYSYMBOL_type_check_func = 70,           /* type_check_func  */
  YYSYMBOL_value = 71,                     /* value  */
  YYSYMBOL_array_value = 72,               /* array_value  */
  YYSYMBOL_key_value_list = 73,            /* key_value_list  */
  YYSYMBOL_key_value_pair = 74,            /* key_value_pair  */
  YYSYMBOL_value_list = 75,                /* value_list  */
  YYSYMBOL_function_declaration = 76,      /* function_declaration  */
  YYSYMBOL_parameter_list = 77,            /* parameter_list  */
  YYSYMBOL_function_call = 78,             /* function_call  */
  YYSYMBOL_argument_list = 79,             /* argument_list  */
  YYSYMBOL_array_declaration = 80,         /* array_declaration  */
  YYSYMBOL_array_items = 81,               /* array_items  */
  YYSYMBOL_array_item = 82,                /* array_item  */
  YYSYMBOL_class_declaration = 83,         /* class_declaration  */
  YYSYMBOL_class_body = 84,                /* class_body  */
  YYSYMBOL_class_member = 85,              /* class_member  */
  YYSYMBOL_class_property = 86,            /* class_property  */
  YYSYMBOL_class_method = 87,              /* class_method  */
  YYSYMBOL_object_creation = 88            /* object_creation  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  27
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   581

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  122
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  278

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   307


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   177,   177,   184,   185,   191,   197,   203,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   223,   230,   234,   245,   253,   260,   267,   274,   281,
     285,   291,   303,   309,   316,   323,   331,   339,   347,   353,
     362,   366,   375,   399,   423,   431,   439,   447,   456,   462,
     470,   480,   481,   489,   499,   509,   517,   525,   534,   539,
     544,   549,   554,   559,   564,   569,   574,   579,   587,   587,
     587,   587,   587,   590,   591,   592,   593,   594,   595,   596,
     602,   612,   616,   622,   628,   636,   640,   648,   656,   664,
     668,   676,   689,   692,   696,   700,   706,   714,   725,   728,
     732,   736,   740,   746,   752,   760,   766,   774,   775,   783,
     791,   801,   811,   820,   821,   829,   830,   833,   840,   847,
     856,   865,   876
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PHP_START", "PHP_END",
  "SEMICOLON", "ASSIGN", "DEFINE", "LPAREN", "RPAREN", "LBRACE", "RBRACE",
  "COMMA", "ARRAY", "GT", "LT", "EQ", "COLON", "LE", "NE", "ARROW",
  "LBRACKET", "RBRACKET", "DOLLAR", "IF", "ELSEIF", "ELSE", "ECHO_TOKEN",
  "IS_INT", "IS_STRING", "IS_ARRAY", "IS_FLOAT", "IS_BOOL", "WHILE",
  "ENDWHILE", "INCREMENT", "RETURN", "FUNCTION", "GLOBAL", "PLUS", "CLASS",
  "NEW", "PUBLIC", "PROTECTED", "PRIVATE", "ARROW_OBJ", "VARIABLE",
  "INTEGER", "FLOAT", "CHAR", "STRING", "BOOL", "IDENTIFIER", "$accept",
  "program", "statements", "statement", "variable_declaration",
  "variable_assignment", "expression", "echo_statement",
  "global_statement", "variable_list", "constant_declaration",
  "if_statement", "elseif_clauses", "elseif_clause", "else_clause",
  "while_statement", "condicion", "type_check_func", "value",
  "array_value", "key_value_list", "key_value_pair", "value_list",
  "function_declaration", "parameter_list", "function_call",
  "argument_list", "array_declaration", "array_items", "array_item",
  "class_declaration", "class_body", "class_member", "class_property",
  "class_method", "object_creation", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-40)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      21,   386,    16,    24,    -4,    30,    13,    45,   -22,    20,
      51,    12,    68,     4,   -40,   -40,   -40,   106,   -40,   -40,
     -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,    66,
     460,   -40,   105,     1,   -40,   -40,   -40,   -40,   -40,   115,
     -40,   452,   116,   -40,    63,   124,   -40,   -40,   394,   133,
      83,    97,   420,   147,   -40,   480,   -40,   -40,   151,   -40,
     -40,   -40,   -40,   -40,   139,   159,   161,    62,   403,   -40,
     491,   166,   144,   -40,   165,   -37,   -40,   129,   -10,   -40,
     170,   132,   138,    34,   179,    85,   186,   -40,   -40,   184,
     175,   -40,   -40,    95,   -40,     2,   192,   499,   505,   512,
     519,   530,   189,   154,   499,   499,   -40,   175,   181,   182,
     -40,   100,   194,   113,   183,   185,   -40,   208,   209,   211,
      60,   -40,   -40,   119,   -40,   167,   -25,   172,   174,   104,
     -40,   -40,   -40,   412,   202,    -2,   -40,   215,   -40,   -40,
     -40,   -40,   -40,   216,   221,   433,   -40,   -40,   218,   175,
     -40,   175,   -40,   175,   -40,   175,   -40,   323,   219,   -40,
     -40,   499,   499,   -40,    39,   -40,   -40,   499,   -40,   -40,
     -40,   -40,   -40,   344,   386,   222,   -27,   223,   177,   230,
     233,   236,   -40,   -40,   224,   131,    22,   132,   -40,   242,
     -40,   -40,   175,   -40,   -40,   240,   226,    47,   245,   -40,
     -40,   181,   -40,   -40,   -40,    81,   143,   386,   -40,   -40,
     246,   248,   499,   499,   499,   473,   -40,   250,   -40,   -40,
     -40,   -40,   254,   -40,   252,   136,   255,   -40,   263,    99,
     259,   261,   269,   273,   275,   -40,   -40,   132,   -40,   386,
     278,   271,   140,   -40,   -40,   256,   -40,   -40,   386,   279,
     -40,   -40,   -40,   197,   452,   365,   280,   -40,   -40,   244,
     239,   386,   -40,   286,   -40,   260,   386,   294,   -40,   281,
     291,   -40,   293,   -40,   386,   -40,   302,   -40
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     3,     9,     8,     0,    13,    16,
      10,    11,    12,    14,    15,    17,    18,     1,     7,     0,
       0,    38,     0,     0,    73,    74,    75,    76,    77,     0,
      78,     0,     0,    40,     0,     0,    22,    21,     0,     0,
       0,     0,    98,     0,     2,     0,     4,    19,     0,    68,
      69,    70,    71,    72,     0,     0,     0,     0,     0,    33,
       0,     0,     0,    32,     0,    92,    39,     0,     0,    25,
       0,     0,     0,     0,     0,     0,     0,    26,    30,     0,
     100,   101,    99,     0,    20,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    81,     0,    76,     0,
      89,     0,    85,     0,     0,     0,    34,     0,     0,     0,
       0,    93,    94,     0,    41,     0,     0,     0,     0,     0,
     113,   115,   116,     0,     0,     0,   107,     0,    24,    28,
      29,    23,    27,     0,     0,     0,     6,     5,     0,    58,
      61,    59,    62,    60,    63,    64,    65,     0,     0,    66,
      67,     0,     0,    83,     0,    84,    82,     0,    80,    79,
      35,    36,    37,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   112,   114,    76,     0,     0,     0,   106,     0,
      31,    97,   103,   104,   102,     0,    48,     0,     0,    87,
      88,     0,    86,    90,    57,     0,     0,     0,    95,    96,
       0,     0,     0,     0,     0,     0,   105,     0,   111,   110,
     109,   108,     0,    42,     0,    47,     0,    55,     0,     0,
       0,     0,     0,     0,     0,    73,    76,     0,   122,     0,
       0,     0,    45,    51,    46,     0,    56,    91,     0,     0,
     117,   118,   119,     0,     0,     0,     0,    52,    44,     0,
       0,     0,    50,     0,    49,     0,     0,     0,   121,     0,
       0,    54,     0,   120,     0,    43,     0,    53
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -40,   -40,    -1,   -12,   -40,   -40,   262,   -40,   -40,   -40,
     -40,   -40,   -40,    65,    69,   -40,   -39,   -40,    -3,   -40,
     -40,   152,   -40,   -40,   -40,   -40,   -40,   267,   241,   141,
     -40,   -40,   173,   -40,   -40,   -40
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,   265,    14,    15,    16,    17,    18,    19,    44,
      20,    21,   242,   243,   244,    22,    65,    66,    67,    40,
     111,   112,   113,    23,   123,    24,    93,   220,   185,   136,
      25,   129,   130,   131,   132,    26
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      13,    56,    74,    39,    29,    53,    69,   146,    54,   121,
     187,     4,   178,    46,    31,   122,    27,    47,    48,   208,
     188,   179,    70,    70,     1,   209,    32,   125,     5,    28,
      42,     6,   126,   127,   128,   217,    71,     7,    30,   138,
      55,     8,     9,    81,    10,    85,    72,    49,    53,    92,
      11,    50,    96,    41,     4,    70,    12,    51,   225,    33,
      34,    35,    36,    37,    38,   110,    43,   115,    76,   218,
     173,     5,   219,    50,     6,    77,    52,   174,   104,    51,
       7,   105,    53,    55,     8,     9,   140,    10,     4,   201,
     141,   109,   227,    11,   148,   150,   152,   154,   156,    12,
      53,   159,   160,    45,   144,     5,     4,   145,     6,   163,
     247,    57,   164,    68,     7,   182,    58,    55,     8,     9,
      73,    10,   166,     5,    75,   167,     6,    11,   175,    88,
     110,   176,     7,    12,    78,    55,     8,     9,    87,    10,
     216,   125,   194,   187,    53,    11,   126,   127,   128,    89,
       4,    12,    94,    98,    99,   100,   197,   101,   199,   200,
      70,   240,   241,    97,   203,   240,   256,     5,   102,   103,
       6,   116,   205,   206,   120,   124,     7,   228,   133,    55,
       8,     9,   134,    10,   139,    56,   117,   118,   119,    11,
     137,   142,   143,    56,    56,    12,    70,   147,    53,   157,
     158,   161,   162,   165,     4,   168,   229,   169,   262,   232,
     233,   234,   199,   170,   171,   263,   172,    56,   180,   177,
     181,     5,   186,   189,     6,   190,   191,   195,   198,   211,
       7,   210,   207,    55,     8,     9,   212,    10,   253,   213,
      53,    56,   214,    11,   215,   223,     4,   260,    56,    12,
     268,   222,   224,    56,   226,   230,   231,    56,   237,   238,
     269,    53,   239,     5,    56,   245,     6,     4,   246,   248,
     249,   271,     7,   276,   250,    55,     8,     9,   251,    10,
     252,   255,    53,   259,     5,    11,   254,     6,     4,   261,
     266,    12,   273,     7,   267,   270,    55,     8,     9,   272,
      10,   274,   183,    53,   275,     5,    11,   257,     6,     4,
      84,   258,    12,   277,     7,    86,   202,    55,     8,     9,
       0,    10,   135,     0,     3,     0,     5,    11,   221,     6,
       4,     0,     0,    12,   196,     7,     0,     0,    55,     8,
       9,     0,    10,     0,     0,     3,     0,     5,    11,     0,
       6,     4,     0,     0,    12,   204,     7,     0,     0,     0,
       8,     9,     0,    10,     0,     0,     3,     0,     5,    11,
       0,     6,     4,     0,     0,    12,   264,     7,     0,     0,
       0,     8,     9,     0,    10,     0,     0,     3,     0,     5,
      11,     0,     6,     4,     0,     0,    12,     0,     7,    79,
       0,     0,     8,     9,     0,    10,     0,    80,     0,     0,
       5,    11,   106,     6,     0,    81,    32,    12,     0,     7,
       0,   106,     0,     8,     9,    32,    10,     0,     0,     0,
       0,     0,    11,    32,     0,    82,     0,     0,    12,     0,
      83,    34,    35,    36,    37,    38,    32,     0,     0,   107,
      34,    35,    36,   108,    38,   109,     0,     0,   107,    34,
      35,    36,   184,    38,   109,    32,    90,    34,    35,    36,
      37,    38,    91,    32,     0,     0,     0,     0,     0,   192,
      34,    35,    36,    37,    38,   193,    80,     0,    59,    60,
      61,    62,    63,    32,    81,     0,     0,     0,    64,    34,
      35,    36,    37,    38,    32,     0,    64,    34,    35,    36,
      37,    38,    32,     0,     0,     0,     0,     0,    32,   107,
     235,    35,    36,   236,    38,    32,    95,    34,    35,    36,
      37,    38,    32,     0,     0,     0,     0,   107,    34,    35,
      36,   114,    38,    32,     0,   107,    34,    35,    36,    37,
      38,   149,    34,    35,    36,    37,    38,     0,   151,    34,
      35,    36,    37,    38,     0,   153,    34,    35,    36,    37,
      38,     0,     0,     0,     0,     0,   155,    34,    35,    36,
      37,    38
};

static const yytype_int16 yycheck[] =
{
       1,    13,    41,     6,     8,     1,     5,     5,     4,    46,
      12,     7,    37,     1,     1,    52,     0,     5,     6,    46,
      22,    46,    21,    21,     3,    52,    13,    37,    24,     5,
      52,    27,    42,    43,    44,    13,    35,    33,     8,     5,
      36,    37,    38,    21,    40,    48,    45,    35,     1,    52,
      46,    39,    55,     8,     7,    21,    52,    45,    11,    46,
      47,    48,    49,    50,    51,    68,    46,    70,     5,    47,
      10,    24,    50,    39,    27,    12,     8,    17,    16,    45,
      33,    19,     1,    36,    37,    38,     1,    40,     7,    50,
       5,    52,    11,    46,    97,    98,    99,   100,   101,    52,
       1,   104,   105,    52,     9,    24,     7,    12,    27,     9,
      11,     5,    12,     8,    33,    11,    50,    36,    37,    38,
       5,    40,     9,    24,     8,    12,    27,    46,     9,    46,
     133,    12,    33,    52,    10,    36,    37,    38,     5,    40,
       9,    37,   145,    12,     1,    46,    42,    43,    44,    52,
       7,    52,     5,    14,    15,    16,   157,    18,   161,   162,
      21,    25,    26,    12,   167,    25,    26,    24,     9,     8,
      27,     5,   173,   174,     9,    46,    33,    34,     8,    36,
      37,    38,    50,    40,     5,   197,    42,    43,    44,    46,
      52,     5,     8,   205,   206,    52,    21,     5,     1,    10,
      46,    20,    20,     9,     7,    22,   207,    22,    11,   212,
     213,   214,   215,     5,     5,   254,     5,   229,    46,    52,
      46,    24,    20,     8,    27,     9,     5,     9,     9,    52,
      33,     8,    10,    36,    37,    38,     6,    40,   239,     6,
       1,   253,     6,    46,    20,     5,     7,   248,   260,    52,
      11,     9,    26,   265,     9,     9,     8,   269,     8,     5,
     261,     1,    10,    24,   276,    10,    27,     7,     5,    10,
       9,    11,    33,   274,     5,    36,    37,    38,     5,    40,
       5,    10,     1,    27,    24,    46,     8,    27,     7,    10,
      10,    52,    11,    33,    50,     9,    36,    37,    38,     5,
      40,    10,   129,     1,    11,    24,    46,   242,    27,     7,
      48,   242,    52,    11,    33,    48,   164,    36,    37,    38,
      -1,    40,    81,    -1,     1,    -1,    24,    46,   187,    27,
       7,    -1,    -1,    52,    11,    33,    -1,    -1,    36,    37,
      38,    -1,    40,    -1,    -1,     1,    -1,    24,    46,    -1,
      27,     7,    -1,    -1,    52,    11,    33,    -1,    -1,    -1,
      37,    38,    -1,    40,    -1,    -1,     1,    -1,    24,    46,
      -1,    27,     7,    -1,    -1,    52,    11,    33,    -1,    -1,
      -1,    37,    38,    -1,    40,    -1,    -1,     1,    -1,    24,
      46,    -1,    27,     7,    -1,    -1,    52,    -1,    33,     5,
      -1,    -1,    37,    38,    -1,    40,    -1,    13,    -1,    -1,
      24,    46,     9,    27,    -1,    21,    13,    52,    -1,    33,
      -1,     9,    -1,    37,    38,    13,    40,    -1,    -1,    -1,
      -1,    -1,    46,    13,    -1,    41,    -1,    -1,    52,    -1,
      46,    47,    48,    49,    50,    51,    13,    -1,    -1,    46,
      47,    48,    49,    50,    51,    52,    -1,    -1,    46,    47,
      48,    49,    50,    51,    52,    13,    46,    47,    48,    49,
      50,    51,    52,    13,    -1,    -1,    -1,    -1,    -1,    46,
      47,    48,    49,    50,    51,    52,    13,    -1,    28,    29,
      30,    31,    32,    13,    21,    -1,    -1,    -1,    46,    47,
      48,    49,    50,    51,    13,    -1,    46,    47,    48,    49,
      50,    51,    13,    -1,    -1,    -1,    -1,    -1,    13,    46,
      47,    48,    49,    50,    51,    13,    46,    47,    48,    49,
      50,    51,    13,    -1,    -1,    -1,    -1,    46,    47,    48,
      49,    50,    51,    13,    -1,    46,    47,    48,    49,    50,
      51,    46,    47,    48,    49,    50,    51,    -1,    46,    47,
      48,    49,    50,    51,    -1,    46,    47,    48,    49,    50,
      51,    -1,    -1,    -1,    -1,    -1,    46,    47,    48,    49,
      50,    51
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    54,     1,     7,    24,    27,    33,    37,    38,
      40,    46,    52,    55,    56,    57,    58,    59,    60,    61,
      63,    64,    68,    76,    78,    83,    88,     0,     5,     8,
       8,     1,    13,    46,    47,    48,    49,    50,    51,    71,
      72,     8,    52,    46,    62,    52,     1,     5,     6,    35,
      39,    45,     8,     1,     4,    36,    56,     5,    50,    28,
      29,    30,    31,    32,    46,    69,    70,    71,     8,     5,
      21,    35,    45,     5,    69,     8,     5,    12,    10,     5,
      13,    21,    41,    46,    59,    71,    80,     5,    46,    52,
      46,    52,    71,    79,     5,    46,    71,    12,    14,    15,
      16,    18,     9,     8,    16,    19,     9,    46,    50,    52,
      71,    73,    74,    75,    50,    71,     5,    42,    43,    44,
       9,    46,    52,    77,    46,    37,    42,    43,    44,    84,
      85,    86,    87,     8,    50,    81,    82,    52,     5,     5,
       1,     5,     5,     8,     9,    12,     5,     5,    71,    46,
      71,    46,    71,    46,    71,    46,    71,    10,    46,    71,
      71,    20,    20,     9,    12,     9,     9,    12,    22,    22,
       5,     5,     5,    10,    17,     9,    12,    52,    37,    46,
      46,    46,    11,    85,    50,    81,    20,    12,    22,     8,
       9,     5,    46,    52,    71,     9,    11,    55,     9,    71,
      71,    50,    74,    71,    11,    55,    55,    10,    46,    52,
       8,    52,     6,     6,     6,    20,     9,    13,    47,    50,
      80,    82,     9,     5,    26,    11,     9,    11,    34,    55,
       9,     8,    71,    71,    71,    47,    50,     8,     5,    10,
      25,    26,    65,    66,    67,    10,     5,    11,    10,     9,
       5,     5,     5,    55,     8,    10,    26,    66,    67,    27,
      55,    10,    11,    69,    11,    55,    10,    50,    11,    55,
       9,    11,     5,    11,    10,    11,    55,    11
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    53,    54,    55,    55,    55,    55,    55,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    57,    57,    58,    58,    58,    58,    58,    58,    58,
      59,    59,    60,    60,    60,    60,    60,    60,    60,    61,
      62,    62,    63,    64,    64,    64,    64,    64,    64,    64,
      64,    65,    65,    66,    67,    68,    68,    68,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    70,    70,
      70,    70,    70,    71,    71,    71,    71,    71,    71,    71,
      71,    72,    72,    72,    72,    73,    73,    74,    74,    75,
      75,    76,    77,    77,    77,    77,    77,    78,    79,    79,
      79,    79,    79,    79,    79,    80,    80,    81,    81,    82,
      82,    82,    83,    84,    84,    85,    85,    86,    86,    86,
      87,    87,    88
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     1,     2,     4,     4,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     2,     2,     4,     4,     3,     3,     4,     4,     4,
       3,     5,     3,     3,     4,     5,     5,     5,     2,     3,
       1,     3,     7,    12,     9,     8,     8,     7,     6,    10,
      10,     1,     2,     7,     4,     7,     8,     6,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       4,     3,     4,     4,     4,     1,     3,     3,     3,     1,
       3,     8,     0,     1,     1,     3,     3,     5,     0,     1,
       1,     1,     3,     3,     3,     4,     3,     1,     3,     3,
       3,     3,     5,     1,     2,     1,     1,     5,     5,     5,
       8,     7,     7
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: PHP_START statements PHP_END  */
#line 178 "phppy.y"
{
    output = (yyvsp[-1].strval);  // Asigna las sentencias generadas a la variable global 'output'
}
#line 1551 "phppy.tab.c"
    break;

  case 4: /* statements: statements statement  */
#line 186 "phppy.y"
    {
        char *result = malloc(strlen((yyvsp[-1].strval)) + strlen((yyvsp[0].strval)) + 1);  // Reserva memoria para el resultado concatenado
        sprintf(result, "%s%s", (yyvsp[-1].strval), (yyvsp[0].strval));  // Concatenar las dos sentencias
        (yyval.strval) = result;  // Almacena el resultado concatenado
    }
#line 1561 "phppy.tab.c"
    break;

  case 5: /* statements: statements RETURN value SEMICOLON  */
#line 192 "phppy.y"
    {
        char *result = malloc(strlen((yyvsp[-3].strval)) + strlen((yyvsp[-1].strval)) + 10);  // Reserva memoria para la sentencia de retorno
        sprintf(result, "%sreturn %s\n", (yyvsp[-3].strval), (yyvsp[-1].strval));  // Formatea la sentencia de retorno
        (yyval.strval) = result;  // Almacena la sentencia de retorno
    }
#line 1571 "phppy.tab.c"
    break;

  case 6: /* statements: statements RETURN VARIABLE SEMICOLON  */
#line 198 "phppy.y"
    {
        char *result = malloc(strlen((yyvsp[-3].strval)) + strlen((yyvsp[-1].strval)) + 10);  // Reserva memoria para la sentencia de retorno
        sprintf(result, "%sreturn %s\n", (yyvsp[-3].strval), (yyvsp[-1].strval) + 1);  // Omite el carácter '$' de la variable y formatea la sentencia de retorno
        (yyval.strval) = result;  // Almacena la sentencia de retorno
    }
#line 1581 "phppy.tab.c"
    break;

  case 7: /* statements: error SEMICOLON  */
#line 203 "phppy.y"
                      { printf("Error in statements, skipping to next statement.\n"); yyerrok; }
#line 1587 "phppy.tab.c"
    break;

  case 20: /* statement: error SEMICOLON  */
#line 219 "phppy.y"
                      { yyerrok; }
#line 1593 "phppy.tab.c"
    break;

  case 21: /* variable_declaration: VARIABLE SEMICOLON  */
#line 224 "phppy.y"
{
    char *var_name = (yyvsp[-1].strval) + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + 10);  // Reserva memoria para la declaración de la variable
    sprintf(result, "%s = None\n", var_name);  // Asigna 'None' a la variable en Python
    (yyval.strval) = result;  // Almacena la declaración de la variable
}
#line 1604 "phppy.tab.c"
    break;

  case 22: /* variable_declaration: VARIABLE error  */
#line 230 "phppy.y"
                 { printf("Missing ';' in variable declaration.\n"); yyerrok; }
#line 1610 "phppy.tab.c"
    break;

  case 23: /* variable_assignment: VARIABLE ASSIGN value SEMICOLON  */
#line 235 "phppy.y"
{
    char *var_name = (yyvsp[-3].strval) + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + strlen((yyvsp[-1].strval)) + 5);  // Reserva memoria para la asignación
    if ((yyvsp[-1].strval) && strlen((yyvsp[-1].strval)) > 0) {
        sprintf(result, "%s = %s\n", var_name, (yyvsp[-1].strval));  // Asigna el valor a la variable
    } else {
        sprintf(result, "%s = None\n", var_name);  // Asigna 'None' si el valor está vacío
    }
    (yyval.strval) = result;  // Almacena la asignación
}
#line 1625 "phppy.tab.c"
    break;

  case 24: /* variable_assignment: VARIABLE ASSIGN VARIABLE SEMICOLON  */
#line 246 "phppy.y"
{
    char *var_name = (yyvsp[-3].strval) + 1;  // Omite el carácter '$' de la variable
    char *value_name = (yyvsp[-1].strval) + 1;  // Omite el carácter '$' del valor
    char *result = malloc(strlen(var_name) + strlen(value_name) + 5);  // Reserva memoria para la asignación
    sprintf(result, "%s = %s\n", var_name, value_name);  // Asigna la variable a otra variable
    (yyval.strval) = result;  // Almacena la asignación
}
#line 1637 "phppy.tab.c"
    break;

  case 25: /* variable_assignment: VARIABLE ASSIGN SEMICOLON  */
#line 254 "phppy.y"
{
    char *var_name = (yyvsp[-2].strval) + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + 10);  // Reserva memoria para la asignación
    sprintf(result, "%s = None\n", var_name);  // Asigna 'None' a la variable
    (yyval.strval) = result;  // Almacena la asignación
}
#line 1648 "phppy.tab.c"
    break;

  case 26: /* variable_assignment: VARIABLE INCREMENT SEMICOLON  */
#line 261 "phppy.y"
{
    char *var_name = (yyvsp[-2].strval) + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + 7);  // Reserva memoria para el incremento
    sprintf(result, "%s += 1\n", var_name);  // Incrementa la variable
    (yyval.strval) = result;  // Almacena el incremento
}
#line 1659 "phppy.tab.c"
    break;

  case 27: /* variable_assignment: VARIABLE ASSIGN array_declaration SEMICOLON  */
#line 268 "phppy.y"
{
    char *var_name = (yyvsp[-3].strval) + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + strlen((yyvsp[-1].strval)) + 5);  // Reserva memoria para la asignación
    sprintf(result, "%s = %s\n", var_name, (yyvsp[-1].strval));  // Asigna la declaración de array a la variable
    (yyval.strval) = result;  // Almacena la asignación
}
#line 1670 "phppy.tab.c"
    break;

  case 28: /* variable_assignment: VARIABLE ASSIGN expression SEMICOLON  */
#line 275 "phppy.y"
{
    char *var_name = (yyvsp[-3].strval) + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + strlen((yyvsp[-1].strval)) + 5);  // Reserva memoria para la asignación
    sprintf(result, "%s = %s\n", var_name, (yyvsp[-1].strval));  // Asigna la expresión a la variable
    (yyval.strval) = result;  // Almacena la asignación
}
#line 1681 "phppy.tab.c"
    break;

  case 29: /* variable_assignment: VARIABLE ASSIGN value error  */
#line 281 "phppy.y"
                              { printf("Missing ';' in variable assignment.\n"); yyerrok; }
#line 1687 "phppy.tab.c"
    break;

  case 30: /* expression: VARIABLE PLUS VARIABLE  */
#line 286 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);  // Reserva memoria para la suma
    sprintf(result, "%s + %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval) + 1);  // Omite el carácter '$' y suma las variables
    (yyval.strval) = result;  // Almacena la expresión
}
#line 1697 "phppy.tab.c"
    break;

  case 31: /* expression: VARIABLE ARROW_OBJ IDENTIFIER LPAREN RPAREN  */
#line 292 "phppy.y"
{
    char *var_name = (yyvsp[-4].strval) + 1;  // Omite el carácter '$'
    char *method_name = (yyvsp[-2].strval);
    char *result = malloc(strlen(var_name) + strlen(method_name) + 4);
    sprintf(result, "%s.%s()\n", var_name, method_name);
    (yyval.strval) = result;
}
#line 1709 "phppy.tab.c"
    break;

  case 32: /* echo_statement: ECHO_TOKEN value SEMICOLON  */
#line 304 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 8);  // Reserva memoria para la sentencia 'echo'
    sprintf(result, "print(%s)\n", (yyvsp[-1].strval));  // Imprime el valor
    (yyval.strval) = result;  // Almacena la sentencia 'echo'
}
#line 1719 "phppy.tab.c"
    break;

  case 33: /* echo_statement: ECHO_TOKEN VARIABLE SEMICOLON  */
#line 310 "phppy.y"
{
    char *var_name = (yyvsp[-1].strval) + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + 10);  // Reserva memoria para la sentencia 'echo'
    sprintf(result, "print(%s)\n", var_name);  // Imprime la variable
    (yyval.strval) = result;  // Almacena la sentencia 'echo'
}
#line 1730 "phppy.tab.c"
    break;

  case 34: /* echo_statement: ECHO_TOKEN VARIABLE INCREMENT SEMICOLON  */
#line 317 "phppy.y"
{
    char *var_name = (yyvsp[-2].strval) + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + 10);  // Reserva memoria para la sentencia 'echo'
    sprintf(result, "print(%s)\n%s += 1\n", var_name, var_name);  // Imprime e incrementa la variable
    (yyval.strval) = result;  // Almacena la sentencia 'echo'
}
#line 1741 "phppy.tab.c"
    break;

  case 35: /* echo_statement: ECHO_TOKEN VARIABLE ARROW_OBJ PUBLIC SEMICOLON  */
#line 324 "phppy.y"
{
    char *var_name = (yyvsp[-3].strval) + 1;  // Omite el carácter '$'
    char *property_name = "public";
    char *result = malloc(strlen(var_name) + strlen(property_name) + 10);
    sprintf(result, "print(self.%s)\n", property_name);
    (yyval.strval) = result;
}
#line 1753 "phppy.tab.c"
    break;

  case 36: /* echo_statement: ECHO_TOKEN VARIABLE ARROW_OBJ PROTECTED SEMICOLON  */
#line 332 "phppy.y"
{
    char *var_name = (yyvsp[-3].strval) + 1;  // Omite el carácter '$'
    char *property_name = "_protected";
    char *result = malloc(strlen(var_name) + strlen(property_name) + 10);
    sprintf(result, "print(self.%s)\n", property_name);
    (yyval.strval) = result;
}
#line 1765 "phppy.tab.c"
    break;

  case 37: /* echo_statement: ECHO_TOKEN VARIABLE ARROW_OBJ PRIVATE SEMICOLON  */
#line 340 "phppy.y"
{
    char *var_name = (yyvsp[-3].strval) + 1;  // Omite el carácter '$'
    char *property_name = "__private";
    char *result = malloc(strlen(var_name) + strlen(property_name) + 10);
    sprintf(result, "print(self.%s)\n", property_name);
    (yyval.strval) = result;
}
#line 1777 "phppy.tab.c"
    break;

  case 38: /* echo_statement: ECHO_TOKEN error  */
#line 347 "phppy.y"
                   { printf("Missing ';' in echo statement.\n"); yyerrok; }
#line 1783 "phppy.tab.c"
    break;

  case 39: /* global_statement: GLOBAL variable_list SEMICOLON  */
#line 354 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 8);  // Reserva memoria para la sentencia 'global'
    sprintf(result, "global %s\n", (yyvsp[-1].strval));  // Marca las variables como globales
    (yyval.strval) = result;  // Almacena la sentencia 'global'
}
#line 1793 "phppy.tab.c"
    break;

  case 40: /* variable_list: VARIABLE  */
#line 363 "phppy.y"
{
    (yyval.strval) = (yyvsp[0].strval) + 1;  // Omite el carácter '$'
}
#line 1801 "phppy.tab.c"
    break;

  case 41: /* variable_list: variable_list COMMA VARIABLE  */
#line 367 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval) + 1) + 3);  // Reserva memoria para la lista
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval) + 1);  // Omite el carácter '$' y agrega la variable a la lista
    (yyval.strval) = result;  // Almacena la lista de variables
}
#line 1811 "phppy.tab.c"
    break;

  case 42: /* constant_declaration: DEFINE LPAREN STRING COMMA value RPAREN SEMICOLON  */
#line 376 "phppy.y"
{
    char* constant_name = strip_quotes((yyvsp[-4].strval));  // Elimina las comillas del nombre de la constante
    char *type;  // Tipo de la constante
    // Determina el tipo de la constante
    if (strchr((yyvsp[-2].strval), '"') != NULL) {
        type = "str";  // Tipo cadena de texto
    } else if (strchr((yyvsp[-2].strval), '.') != NULL) {
        type = "float";  // Tipo flotante
    } else if (strcmp((yyvsp[-2].strval), "True") == 0 || strcmp((yyvsp[-2].strval), "False") == 0) {
        type = "bool";  // Tipo booleano
    } else if ((yyvsp[-2].strval)[0] == '[') {
        type = "List[Any]";  // Tipo lista
    } else {
        type = "int";  // Tipo entero
    }
    add_symbol(constant_name, type);  // Agrega la constante a la tabla de símbolos
    char *result = malloc(strlen(constant_name) + strlen(type) + strlen((yyvsp[-2].strval)) + 10);  // Reserva memoria para la declaración de la constante
    sprintf(result, "%s: %s = %s\n", constant_name, type, (yyvsp[-2].strval));  // Define la constante en Python
    free(constant_name);  // Libera la memoria del nombre de la constante
    (yyval.strval) = result;  // Almacena la declaración de la constante
}
#line 1837 "phppy.tab.c"
    break;

  case 43: /* if_statement: IF LPAREN type_check_func LPAREN VARIABLE RPAREN RPAREN LBRACE ECHO_TOKEN STRING SEMICOLON RBRACE  */
#line 400 "phppy.y"
{
    char *type = get_symbol_type((yyvsp[-7].strval) + 1);  // Obtiene el tipo de la variable, omitiendo el carácter '$'
    char *py_type;  // Declara un puntero para el tipo en Python

    // Compara el tipo y asigna el tipo correspondiente en Python
    if (strcmp(type, "int") == 0) py_type = "int";
    else if (strcmp(type, "str") == 0) py_type = "str";
    else if (strcmp(type, "list") == 0) py_type = "list";
    else if (strcmp(type, "float") == 0) py_type = "float";
    else if (strcmp(type, "bool") == 0) py_type = "bool";
    else py_type = "object";  // Tipo genérico en caso de que no coincida con los anteriores
    
    char *unquoted = strip_quotes((yyvsp[-2].strval));  // Elimina las comillas de la cadena
    char *message = replace_dollar(unquoted);  // Reemplaza los caracteres '$' en la cadena
    char *formatted_message = remove_newlines(message);  // Elimina los saltos de línea y formatea el mensaje
    char *result = malloc(strlen((yyvsp[-7].strval) + 1) + strlen(py_type) + strlen(formatted_message) + 50); // Asegura suficiente espacio para el resultado
    sprintf(result, "if isinstance(%s, %s):\n    print(\"%s\")\n", (yyvsp[-7].strval) + 1, py_type, formatted_message);  // Imprime la sentencia 'if' en Python
    (yyval.strval) = result;  // Asigna el resultado a la regla
    
    free(unquoted);  // Libera la memoria de 'unquoted'
    free(message);  // Libera la memoria de 'message'
    free(formatted_message);  // Libera la memoria de 'formatted_message'
}
#line 1865 "phppy.tab.c"
    break;

  case 44: /* if_statement: IF LPAREN condicion RPAREN LBRACE statements RBRACE elseif_clauses else_clause  */
#line 424 "phppy.y"
{
    char *if_part = indent_code((yyvsp[-3].strval));  // Indenta el código del bloque 'if'
    char *result = malloc(strlen((yyvsp[-6].strval)) + strlen(if_part) + strlen((yyvsp[-1].strval)) + strlen((yyvsp[0].strval)) + 10);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n%s%s%s", (yyvsp[-6].strval), if_part, (yyvsp[-1].strval), (yyvsp[0].strval));  // Formatea la sentencia 'if' con sus bloques 'elseif' y 'else'
    (yyval.strval) = result;  // Almacena el resultado
    free(if_part);  // Libera la memoria de 'if_part'
}
#line 1877 "phppy.tab.c"
    break;

  case 45: /* if_statement: IF LPAREN condicion RPAREN LBRACE statements RBRACE elseif_clauses  */
#line 432 "phppy.y"
{
    char *if_part = indent_code((yyvsp[-2].strval));  // Indenta el código del bloque 'if'
    char *result = malloc(strlen((yyvsp[-5].strval)) + strlen(if_part) + strlen((yyvsp[0].strval)) + 10);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n%s%s", (yyvsp[-5].strval), if_part, (yyvsp[0].strval));  // Formatea la sentencia 'if' con sus bloques 'elseif'
    (yyval.strval) = result;  // Almacena el resultado
    free(if_part);  // Libera la memoria de 'if_part'
}
#line 1889 "phppy.tab.c"
    break;

  case 46: /* if_statement: IF LPAREN condicion RPAREN LBRACE statements RBRACE else_clause  */
#line 440 "phppy.y"
{
    char *if_part = indent_code((yyvsp[-2].strval));  // Indenta el código del bloque 'if'
    char *result = malloc(strlen((yyvsp[-5].strval)) + strlen(if_part) + strlen((yyvsp[0].strval)) + 20);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n%s%s", (yyvsp[-5].strval), if_part, (yyvsp[0].strval));  // Formatea la sentencia 'if' con su bloque 'else'
    (yyval.strval) = result;  // Almacena el resultado
    free(if_part);  // Libera la memoria de 'if_part'
}
#line 1901 "phppy.tab.c"
    break;

  case 47: /* if_statement: IF LPAREN condicion RPAREN LBRACE statements RBRACE  */
#line 448 "phppy.y"
{
    char *if_part = indent_code((yyvsp[-1].strval));  // Indenta el código del bloque 'if'
    char *result = malloc(strlen((yyvsp[-4].strval)) + strlen(if_part) + 10);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n%s", (yyvsp[-4].strval), if_part);  // Formatea la sentencia 'if'
    (yyval.strval) = result;  // Almacena el resultado
    free(if_part);  // Libera la memoria de 'if_part'
}
#line 1913 "phppy.tab.c"
    break;

  case 48: /* if_statement: IF LPAREN condicion RPAREN LBRACE RBRACE  */
#line 457 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-3].strval)) + 15);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n    pass\n", (yyvsp[-3].strval));  // Formatea la sentencia 'if' con un bloque vacío
    (yyval.strval) = result;  // Almacena el resultado
}
#line 1923 "phppy.tab.c"
    break;

  case 49: /* if_statement: IF LPAREN condicion RPAREN LBRACE statements RBRACE ELSE LBRACE RBRACE  */
#line 463 "phppy.y"
{
    char *indented_statements_if = indent_code((yyvsp[-4].strval));  // Indenta el código del bloque 'if'
    char *result = malloc(strlen((yyvsp[-7].strval)) + strlen(indented_statements_if) + 20);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n%selse:\n    pass\n", (yyvsp[-7].strval), indented_statements_if);  // Formatea la sentencia 'if' con un bloque 'else' vacío
    (yyval.strval) = result;  // Almacena el resultado
    free(indented_statements_if);  // Libera la memoria de 'indented_statements_if'
}
#line 1935 "phppy.tab.c"
    break;

  case 50: /* if_statement: IF LPAREN condicion RPAREN LBRACE RBRACE ELSE LBRACE statements RBRACE  */
#line 471 "phppy.y"
{
    char *indented_statements_else = indent_code((yyvsp[-1].strval));  // Indenta el código del bloque 'else'
    char *result = malloc(strlen((yyvsp[-7].strval)) + strlen(indented_statements_else) + 20);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n    pass\nelse:\n%s", (yyvsp[-7].strval), indented_statements_else);  // Formatea la sentencia 'if' con un bloque 'else'
    (yyval.strval) = result;  // Almacena el resultado
    free(indented_statements_else);  // Libera la memoria de 'indented_statements_else'
}
#line 1947 "phppy.tab.c"
    break;

  case 52: /* elseif_clauses: elseif_clauses elseif_clause  */
#line 482 "phppy.y"
    {
        char *result = malloc(strlen((yyvsp[-1].strval)) + strlen((yyvsp[0].strval)) + 1);  // Reserva memoria para el resultado
        sprintf(result, "%s%s", (yyvsp[-1].strval), (yyvsp[0].strval));  // Concatenar las cláusulas 'elseif'
        (yyval.strval) = result;  // Almacena el resultado
    }
#line 1957 "phppy.tab.c"
    break;

  case 53: /* elseif_clause: ELSEIF LPAREN condicion RPAREN LBRACE statements RBRACE  */
#line 490 "phppy.y"
{
    char *elseif_part = indent_code((yyvsp[-1].strval));  // Indenta el código del bloque 'elseif'
    char *result = malloc(strlen((yyvsp[-4].strval)) + strlen(elseif_part) + 10);  // Reserva memoria para el resultado
    sprintf(result, "elif (%s):\n%s", (yyvsp[-4].strval), elseif_part);  // Formatea la cláusula 'elseif'
    (yyval.strval) = result;  // Almacena el resultado
    free(elseif_part);  // Libera la memoria de 'elseif_part'
}
#line 1969 "phppy.tab.c"
    break;

  case 54: /* else_clause: ELSE LBRACE statements RBRACE  */
#line 500 "phppy.y"
{
    char *else_part = indent_code((yyvsp[-1].strval));  // Indenta el código del bloque 'else'
    char *result = malloc(strlen(else_part) + 20);  // Reserva memoria para el resultado
    sprintf(result, "else:\n%s", else_part);  // Formatea la cláusula 'else'
    (yyval.strval) = result;  // Almacena el resultado
    free(else_part);  // Libera la memoria de 'else_part'
}
#line 1981 "phppy.tab.c"
    break;

  case 55: /* while_statement: WHILE LPAREN condicion RPAREN LBRACE statements RBRACE  */
#line 510 "phppy.y"
{
    char *indented_statements = indent_code((yyvsp[-1].strval));  // Indenta el código del bloque 'while'
    char *result = malloc(strlen((yyvsp[-4].strval)) + strlen(indented_statements) + 15);  // Reserva memoria para el resultado
    sprintf(result, "while (%s):\n%s", (yyvsp[-4].strval), indented_statements);  // Formatea la sentencia 'while'
    (yyval.strval) = result;  // Almacena el resultado
    free(indented_statements);  // Libera la memoria de 'indented_statements'
}
#line 1993 "phppy.tab.c"
    break;

  case 56: /* while_statement: WHILE LPAREN condicion RPAREN COLON statements ENDWHILE SEMICOLON  */
#line 518 "phppy.y"
{
    char *indented_statements = indent_code((yyvsp[-2].strval));  // Indenta el código del bloque 'while'
    char *result = malloc(strlen((yyvsp[-5].strval)) + strlen(indented_statements) + 15);  // Reserva memoria para el resultado
    sprintf(result, "while (%s):\n%s", (yyvsp[-5].strval), indented_statements);  // Formatea la sentencia 'while'
    (yyval.strval) = result;  // Almacena el resultado
    free(indented_statements);  // Libera la memoria de 'indented_statements'
}
#line 2005 "phppy.tab.c"
    break;

  case 57: /* while_statement: WHILE LPAREN condicion RPAREN LBRACE RBRACE  */
#line 526 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-3].strval)) + 15);  // Reserva memoria para el resultado
    sprintf(result, "while (%s):\n    pass\n", (yyvsp[-3].strval));  // Formatea la sentencia 'while' con un bloque vacío
    (yyval.strval) = result;  // Almacena el resultado
}
#line 2015 "phppy.tab.c"
    break;

  case 58: /* condicion: VARIABLE GT VARIABLE  */
#line 535 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4); // 4: para espacio, operador, espacio, y terminador nulo
        sprintf((yyval.strval), "%s > %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval) + 1); // Omitimos el carácter '$'
    }
#line 2024 "phppy.tab.c"
    break;

  case 59: /* condicion: VARIABLE LT VARIABLE  */
#line 540 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
        sprintf((yyval.strval), "%s < %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval) + 1); // Omitimos el carácter '$'
    }
#line 2033 "phppy.tab.c"
    break;

  case 60: /* condicion: VARIABLE EQ VARIABLE  */
#line 545 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
        sprintf((yyval.strval), "%s == %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval) + 1); // En Python se usa '==' para la igualdad
    }
#line 2042 "phppy.tab.c"
    break;

  case 61: /* condicion: VARIABLE GT value  */
#line 550 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4); // 4: para espacio, operador, espacio, y terminador nulo
        sprintf((yyval.strval), "%s > %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval)); // Omitimos el carácter '$'
    }
#line 2051 "phppy.tab.c"
    break;

  case 62: /* condicion: VARIABLE LT value  */
#line 555 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
        sprintf((yyval.strval), "%s < %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval)); // Omitimos el carácter '$'
    }
#line 2060 "phppy.tab.c"
    break;

  case 63: /* condicion: VARIABLE EQ value  */
#line 560 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
        sprintf((yyval.strval), "%s == %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval)); // En Python se usa '==' para la igualdad
    }
#line 2069 "phppy.tab.c"
    break;

  case 64: /* condicion: VARIABLE LE VARIABLE  */
#line 565 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 5);
        sprintf((yyval.strval), "%s <= %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval) + 1); // Omitimos el carácter '$'
    }
#line 2078 "phppy.tab.c"
    break;

  case 65: /* condicion: VARIABLE LE value  */
#line 570 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 5);
        sprintf((yyval.strval), "%s <= %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval)); // Omitimos el carácter '$'
    }
#line 2087 "phppy.tab.c"
    break;

  case 66: /* condicion: value EQ value  */
#line 575 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
        sprintf((yyval.strval), "%s == %s", (yyvsp[-2].strval), (yyvsp[0].strval)); // En Python se usa '==' para la igualdad
    }
#line 2096 "phppy.tab.c"
    break;

  case 67: /* condicion: value NE value  */
#line 580 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 5);
        sprintf((yyval.strval), "%s != %s", (yyvsp[-2].strval), (yyvsp[0].strval)); // En Python se usa '!=' para desigualdad
    }
#line 2105 "phppy.tab.c"
    break;

  case 73: /* value: INTEGER  */
#line 590 "phppy.y"
               { (yyval.strval) = (yyvsp[0].strval); }
#line 2111 "phppy.tab.c"
    break;

  case 74: /* value: FLOAT  */
#line 591 "phppy.y"
            { (yyval.strval) = (yyvsp[0].strval); }
#line 2117 "phppy.tab.c"
    break;

  case 75: /* value: CHAR  */
#line 592 "phppy.y"
           { (yyval.strval) = (yyvsp[0].strval); }
#line 2123 "phppy.tab.c"
    break;

  case 76: /* value: STRING  */
#line 593 "phppy.y"
             { (yyval.strval) = (yyvsp[0].strval); }
#line 2129 "phppy.tab.c"
    break;

  case 77: /* value: BOOL  */
#line 594 "phppy.y"
           { (yyval.strval) = (yyvsp[0].strval); }
#line 2135 "phppy.tab.c"
    break;

  case 78: /* value: array_value  */
#line 595 "phppy.y"
                  { (yyval.strval) = (yyvsp[0].strval); }
#line 2141 "phppy.tab.c"
    break;

  case 79: /* value: VARIABLE LBRACKET value RBRACKET  */
#line 597 "phppy.y"
    {
        char *result = malloc(strlen((yyvsp[-3].strval)) + strlen((yyvsp[-1].strval)) + 4);
        sprintf(result, "%s[%s]", (yyvsp[-3].strval) + 1, (yyvsp[-1].strval));  // Omite el carácter '$' y formatea la variable con el índice
        (yyval.strval) = result;  // Asigna el resultado formateado
    }
#line 2151 "phppy.tab.c"
    break;

  case 80: /* value: VARIABLE LBRACKET STRING RBRACKET  */
#line 603 "phppy.y"
    {
        char *key = strip_quotes((yyvsp[-1].strval));  // Elimina las comillas de la cadena
        char *result = malloc(strlen((yyvsp[-3].strval)) + strlen(key) + 4);
        sprintf(result, "%s[%s]", (yyvsp[-3].strval) + 1, key);  // Omite el carácter '$' y formatea la variable con la clave
        free(key);  // Libera la memoria de la clave
        (yyval.strval) = result;  // Asigna el resultado formateado
    }
#line 2163 "phppy.tab.c"
    break;

  case 81: /* array_value: ARRAY LPAREN RPAREN  */
#line 613 "phppy.y"
{
    (yyval.strval) = strdup("{}");  // Representa un array vacío
}
#line 2171 "phppy.tab.c"
    break;

  case 82: /* array_value: ARRAY LPAREN value_list RPAREN  */
#line 617 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 3);
    sprintf(result, "[%s]", (yyvsp[-1].strval));  // Formatea la lista de valores como un array en Python
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2181 "phppy.tab.c"
    break;

  case 83: /* array_value: ARRAY LPAREN key_value_list RPAREN  */
#line 623 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 3);
    sprintf(result, "{%s}", (yyvsp[-1].strval));  // Formatea la lista de pares clave-valor como un diccionario en Python
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2191 "phppy.tab.c"
    break;

  case 84: /* array_value: ARRAY LPAREN key_value_pair RPAREN  */
#line 629 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 3);
    sprintf(result, "{%s}", (yyvsp[-1].strval));  // Formatea un único par clave-valor como un diccionario en Python
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2201 "phppy.tab.c"
    break;

  case 85: /* key_value_list: key_value_pair  */
#line 637 "phppy.y"
{
    (yyval.strval) = (yyvsp[0].strval);  // Asigna el único par clave-valor a `$$`
}
#line 2209 "phppy.tab.c"
    break;

  case 86: /* key_value_list: key_value_list COMMA key_value_pair  */
#line 641 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval));  // Concadena pares clave-valor con coma
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2219 "phppy.tab.c"
    break;

  case 87: /* key_value_pair: STRING ARROW value  */
#line 649 "phppy.y"
{
    char *key = (yyvsp[-2].strval);  // Asigna la clave
    char *result = malloc(strlen(key) + strlen((yyvsp[0].strval)) + 4);
    sprintf(result, "%s: %s", key, (yyvsp[0].strval));  // Formatea el par clave-valor
    free(key);  // Libera la memoria de la clave
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2231 "phppy.tab.c"
    break;

  case 88: /* key_value_pair: IDENTIFIER ARROW value  */
#line 657 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
    sprintf(result, "\"%s\": %s", (yyvsp[-2].strval), (yyvsp[0].strval));  // Formatea el par clave-valor con identificador como clave
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2241 "phppy.tab.c"
    break;

  case 89: /* value_list: value  */
#line 665 "phppy.y"
{
    (yyval.strval) = (yyvsp[0].strval);  // Asigna un único valor a `$$`
}
#line 2249 "phppy.tab.c"
    break;

  case 90: /* value_list: value_list COMMA value  */
#line 669 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval));  // Concadena valores con coma
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2259 "phppy.tab.c"
    break;

  case 91: /* function_declaration: FUNCTION IDENTIFIER LPAREN parameter_list RPAREN LBRACE statements RBRACE  */
#line 677 "phppy.y"
{
    char *func_name = (yyvsp[-6].strval);  // Asigna el nombre de la función
    char *params = (yyvsp[-4].strval);  // Asigna los parámetros de la función
    char *body = indent_code((yyvsp[-1].strval));  // Indenta el cuerpo de la función
    char *result = malloc(strlen(func_name) + strlen(params) + strlen(body) + 20);
    sprintf(result, "def %s(%s):\n%s", func_name, params, body);  // Formatea la declaración de la función
    (yyval.strval) = result;  // Asigna el resultado formateado
    free(body);  // Libera la memoria del cuerpo de la función
}
#line 2273 "phppy.tab.c"
    break;

  case 92: /* parameter_list: %empty  */
#line 689 "phppy.y"
{
    (yyval.strval) = strdup("");  // Representa una lista de parámetros vacía
}
#line 2281 "phppy.tab.c"
    break;

  case 93: /* parameter_list: VARIABLE  */
#line 693 "phppy.y"
{
    (yyval.strval) = strdup((yyvsp[0].strval) + 1);  // Omite el carácter '$' y representa una variable como parámetro
}
#line 2289 "phppy.tab.c"
    break;

  case 94: /* parameter_list: IDENTIFIER  */
#line 697 "phppy.y"
{
    (yyval.strval) = strdup((yyvsp[0].strval));  // Representa un identificador como parámetro
}
#line 2297 "phppy.tab.c"
    break;

  case 95: /* parameter_list: parameter_list COMMA VARIABLE  */
#line 701 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval) + 1);  // Omite el carácter '$' y concatena variables como parámetros
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2307 "phppy.tab.c"
    break;

  case 96: /* parameter_list: parameter_list COMMA IDENTIFIER  */
#line 707 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval));  // Concatena identificadores como parámetros
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2317 "phppy.tab.c"
    break;

  case 97: /* function_call: IDENTIFIER LPAREN argument_list RPAREN SEMICOLON  */
#line 715 "phppy.y"
{
    char *func_name = (yyvsp[-4].strval);  // Asigna el nombre de la función
    char *args = (yyvsp[-2].strval);  // Asigna los argumentos de la función
    char *result = malloc(strlen(func_name) + strlen(args) + 5);
    sprintf(result, "%s(%s)\n", func_name, args);  // Formatea la llamada a la función
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2329 "phppy.tab.c"
    break;

  case 98: /* argument_list: %empty  */
#line 725 "phppy.y"
{
    (yyval.strval) = strdup("");  // Representa una lista de argumentos vacía
}
#line 2337 "phppy.tab.c"
    break;

  case 99: /* argument_list: value  */
#line 729 "phppy.y"
{
    (yyval.strval) = strdup((yyvsp[0].strval));  // Representa un único valor como argumento
}
#line 2345 "phppy.tab.c"
    break;

  case 100: /* argument_list: VARIABLE  */
#line 733 "phppy.y"
{
    (yyval.strval) = strdup((yyvsp[0].strval) + 1);  // Omite el carácter '$' y representa una variable como argumento
}
#line 2353 "phppy.tab.c"
    break;

  case 101: /* argument_list: IDENTIFIER  */
#line 737 "phppy.y"
{
    (yyval.strval) = strdup((yyvsp[0].strval));  // Representa un identificador como argumento
}
#line 2361 "phppy.tab.c"
    break;

  case 102: /* argument_list: argument_list COMMA value  */
#line 741 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval));  // Concatena valores como argumentos
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2371 "phppy.tab.c"
    break;

  case 103: /* argument_list: argument_list COMMA VARIABLE  */
#line 747 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval) + 1);  // Omite el carácter '$' y concatena variables como argumentos
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2381 "phppy.tab.c"
    break;

  case 104: /* argument_list: argument_list COMMA IDENTIFIER  */
#line 753 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval));  // Concatena identificadores como argumentos
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2391 "phppy.tab.c"
    break;

  case 105: /* array_declaration: ARRAY LPAREN array_items RPAREN  */
#line 761 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 3);
    sprintf(result, "{%s}", (yyvsp[-1].strval));  // Formatea los ítems del array como un diccionario en Python
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2401 "phppy.tab.c"
    break;

  case 106: /* array_declaration: LBRACKET array_items RBRACKET  */
#line 767 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 3);
    sprintf(result, "{%s}", (yyvsp[-1].strval));  // Formatea los ítems del array como un diccionario en Python
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2411 "phppy.tab.c"
    break;

  case 108: /* array_items: array_items COMMA array_item  */
#line 776 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 3);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval));  // Concatena ítems del array con coma
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2421 "phppy.tab.c"
    break;

  case 109: /* array_item: STRING ARROW array_declaration  */
#line 784 "phppy.y"
{
    char *key = strip_quotes((yyvsp[-2].strval));  // Elimina las comillas de la clave
    char *result = malloc(strlen(key) + strlen((yyvsp[0].strval)) + 5);
    sprintf(result, "\"%s\": %s", key, (yyvsp[0].strval));  // Formatea el ítem del array con clave y declaración de array
    free(key);  // Libera la memoria de la clave
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2433 "phppy.tab.c"
    break;

  case 110: /* array_item: STRING ARROW STRING  */
#line 792 "phppy.y"
{
    char *key = strip_quotes((yyvsp[-2].strval));  // Elimina las comillas de la clave
    char *value = strip_quotes((yyvsp[0].strval));  // Elimina las comillas del valor
    char *result = malloc(strlen(key) + strlen(value) + 5);
    sprintf(result, "\"%s\": \"%s\"", key, value);  // Formatea el ítem del array con clave y valor
    free(key);  // Libera la memoria de la clave
    free(value);  // Libera la memoria del valor
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2447 "phppy.tab.c"
    break;

  case 111: /* array_item: STRING ARROW INTEGER  */
#line 802 "phppy.y"
{
    char *key = strip_quotes((yyvsp[-2].strval));  // Elimina las comillas de la clave
    char *result = malloc(strlen(key) + strlen((yyvsp[0].strval)) + 5);
    sprintf(result, "\"%s\": %s", key, (yyvsp[0].strval));  // Formatea el ítem del array con clave y entero
    free(key);  // Libera la memoria de la clave
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2459 "phppy.tab.c"
    break;

  case 112: /* class_declaration: CLASS IDENTIFIER LBRACE class_body RBRACE  */
#line 812 "phppy.y"
{
    char *class_name = (yyvsp[-3].strval);  
    char *result = malloc(strlen(class_name) + strlen((yyvsp[-1].strval)) + 20);
    sprintf(result, "class %s:\n%s", class_name, (yyvsp[-1].strval));
    (yyval.strval) = result;
}
#line 2470 "phppy.tab.c"
    break;

  case 114: /* class_body: class_body class_member  */
#line 822 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + strlen((yyvsp[0].strval)) + 1);
    sprintf(result, "%s%s", (yyvsp[-1].strval), (yyvsp[0].strval));
    (yyval.strval) = result;
}
#line 2480 "phppy.tab.c"
    break;

  case 117: /* class_property: PUBLIC VARIABLE ASSIGN value SEMICOLON  */
#line 834 "phppy.y"
{
    char *property_name = (yyvsp[-3].strval) + 1;  // Omite el carácter '$'
    char *result = malloc(strlen(property_name) + strlen((yyvsp[-1].strval)) + 30);
    sprintf(result, "    def __init__(self):\n        self.%s = %s\n", property_name, (yyvsp[-1].strval));
    (yyval.strval) = result;
}
#line 2491 "phppy.tab.c"
    break;

  case 118: /* class_property: PROTECTED VARIABLE ASSIGN value SEMICOLON  */
#line 841 "phppy.y"
{
    char *property_name = (yyvsp[-3].strval) + 1;  // Omite el carácter '$' y añade un guion bajo
    char *result = malloc(strlen(property_name) + strlen((yyvsp[-1].strval)) + 31);
    sprintf(result, "        self._%s = %s\n", property_name, (yyvsp[-1].strval));
    (yyval.strval) = result;
}
#line 2502 "phppy.tab.c"
    break;

  case 119: /* class_property: PRIVATE VARIABLE ASSIGN value SEMICOLON  */
#line 848 "phppy.y"
{
    char *property_name = (yyvsp[-3].strval) + 1;  // Omite el carácter '$' y añade dos guiones bajos
    char *result = malloc(strlen(property_name) + strlen((yyvsp[-1].strval)) + 32);
    sprintf(result, "        self.__%s = %s\n", property_name, (yyvsp[-1].strval));
    (yyval.strval) = result;
}
#line 2513 "phppy.tab.c"
    break;

  case 120: /* class_method: PUBLIC FUNCTION IDENTIFIER LPAREN RPAREN LBRACE statements RBRACE  */
#line 857 "phppy.y"
{
    char *method_name = (yyvsp[-5].strval);  
    char *indented_statements = indent_code(indent_code((yyvsp[-1].strval)));
    char *result = malloc(strlen(method_name) + strlen(indented_statements) + 20);
    sprintf(result, "    def %s(self):\n%s", method_name, indented_statements);
    (yyval.strval) = result;
    free(indented_statements);
}
#line 2526 "phppy.tab.c"
    break;

  case 121: /* class_method: FUNCTION IDENTIFIER LPAREN RPAREN LBRACE statements RBRACE  */
#line 866 "phppy.y"
{
    char *method_name = (yyvsp[-5].strval);  
    char *indented_statements = indent_code(indent_code((yyvsp[-1].strval)));
    char *result = malloc(strlen(method_name) + strlen(indented_statements) + 20);
    sprintf(result, "    def %s(self):\n%s", method_name, indented_statements);
    (yyval.strval) = result;
    free(indented_statements);
}
#line 2539 "phppy.tab.c"
    break;

  case 122: /* object_creation: VARIABLE ASSIGN NEW IDENTIFIER LPAREN RPAREN SEMICOLON  */
#line 877 "phppy.y"
{
    char *var_name = (yyvsp[-6].strval) + 1;  // Omite el carácter '$'
    char *class_name = (yyvsp[-3].strval);
    char *result = malloc(strlen(var_name) + strlen(class_name) + 10);
    sprintf(result, "%s = %s()\n", var_name, class_name);
    (yyval.strval) = result;
}
#line 2551 "phppy.tab.c"
    break;


#line 2555 "phppy.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 887 "phppy.y"


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
