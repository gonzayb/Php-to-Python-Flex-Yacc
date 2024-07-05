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

#line 225 "phppy.tab.c"

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
  YYSYMBOL_IF = 23,                        /* IF  */
  YYSYMBOL_ELSEIF = 24,                    /* ELSEIF  */
  YYSYMBOL_ELSE = 25,                      /* ELSE  */
  YYSYMBOL_ECHO_TOKEN = 26,                /* ECHO_TOKEN  */
  YYSYMBOL_IS_INT = 27,                    /* IS_INT  */
  YYSYMBOL_IS_STRING = 28,                 /* IS_STRING  */
  YYSYMBOL_IS_ARRAY = 29,                  /* IS_ARRAY  */
  YYSYMBOL_IS_FLOAT = 30,                  /* IS_FLOAT  */
  YYSYMBOL_IS_BOOL = 31,                   /* IS_BOOL  */
  YYSYMBOL_WHILE = 32,                     /* WHILE  */
  YYSYMBOL_ENDWHILE = 33,                  /* ENDWHILE  */
  YYSYMBOL_INCREMENT = 34,                 /* INCREMENT  */
  YYSYMBOL_RETURN = 35,                    /* RETURN  */
  YYSYMBOL_FUNCTION = 36,                  /* FUNCTION  */
  YYSYMBOL_GLOBAL = 37,                    /* GLOBAL  */
  YYSYMBOL_PLUS = 38,                      /* PLUS  */
  YYSYMBOL_CLASS = 39,                     /* CLASS  */
  YYSYMBOL_NEW = 40,                       /* NEW  */
  YYSYMBOL_PUBLIC = 41,                    /* PUBLIC  */
  YYSYMBOL_PROTECTED = 42,                 /* PROTECTED  */
  YYSYMBOL_PRIVATE = 43,                   /* PRIVATE  */
  YYSYMBOL_ARROW_OBJ = 44,                 /* ARROW_OBJ  */
  YYSYMBOL_VARIABLE = 45,                  /* VARIABLE  */
  YYSYMBOL_INTEGER = 46,                   /* INTEGER  */
  YYSYMBOL_FLOAT = 47,                     /* FLOAT  */
  YYSYMBOL_CHAR = 48,                      /* CHAR  */
  YYSYMBOL_STRING = 49,                    /* STRING  */
  YYSYMBOL_BOOL = 50,                      /* BOOL  */
  YYSYMBOL_IDENTIFIER = 51,                /* IDENTIFIER  */
  YYSYMBOL_YYACCEPT = 52,                  /* $accept  */
  YYSYMBOL_program = 53,                   /* program  */
  YYSYMBOL_statements = 54,                /* statements  */
  YYSYMBOL_statement = 55,                 /* statement  */
  YYSYMBOL_variable_declaration = 56,      /* variable_declaration  */
  YYSYMBOL_variable_assignment = 57,       /* variable_assignment  */
  YYSYMBOL_expression = 58,                /* expression  */
  YYSYMBOL_echo_statement = 59,            /* echo_statement  */
  YYSYMBOL_global_statement = 60,          /* global_statement  */
  YYSYMBOL_variable_list = 61,             /* variable_list  */
  YYSYMBOL_constant_declaration = 62,      /* constant_declaration  */
  YYSYMBOL_if_statement = 63,              /* if_statement  */
  YYSYMBOL_elseif_clauses = 64,            /* elseif_clauses  */
  YYSYMBOL_elseif_clause = 65,             /* elseif_clause  */
  YYSYMBOL_else_clause = 66,               /* else_clause  */
  YYSYMBOL_while_statement = 67,           /* while_statement  */
  YYSYMBOL_condicion = 68,                 /* condicion  */
  YYSYMBOL_type_check_func = 69,           /* type_check_func  */
  YYSYMBOL_value = 70,                     /* value  */
  YYSYMBOL_array_value = 71,               /* array_value  */
  YYSYMBOL_key_value_list = 72,            /* key_value_list  */
  YYSYMBOL_key_value_pair = 73,            /* key_value_pair  */
  YYSYMBOL_value_list = 74,                /* value_list  */
  YYSYMBOL_function_declaration = 75,      /* function_declaration  */
  YYSYMBOL_parameter_list = 76,            /* parameter_list  */
  YYSYMBOL_function_call = 77,             /* function_call  */
  YYSYMBOL_argument_list = 78,             /* argument_list  */
  YYSYMBOL_array_declaration = 79,         /* array_declaration  */
  YYSYMBOL_array_items = 80,               /* array_items  */
  YYSYMBOL_array_item = 81,                /* array_item  */
  YYSYMBOL_class_declaration = 82,         /* class_declaration  */
  YYSYMBOL_class_body = 83,                /* class_body  */
  YYSYMBOL_class_member = 84,              /* class_member  */
  YYSYMBOL_class_property = 85,            /* class_property  */
  YYSYMBOL_class_method = 86,              /* class_method  */
  YYSYMBOL_object_creation = 87            /* object_creation  */
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
#define YYLAST   559

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  118
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  273

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   306


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
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   174,   174,   181,   182,   188,   194,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     219,   229,   240,   248,   255,   262,   269,   279,   285,   297,
     303,   310,   317,   325,   333,   346,   355,   359,   368,   392,
     416,   424,   432,   440,   449,   455,   463,   473,   474,   482,
     492,   502,   510,   518,   527,   532,   537,   542,   547,   552,
     557,   562,   567,   572,   580,   580,   580,   580,   580,   583,
     584,   585,   586,   587,   588,   589,   595,   605,   609,   615,
     621,   629,   633,   641,   649,   657,   661,   669,   682,   685,
     689,   693,   699,   707,   718,   721,   725,   729,   733,   739,
     745,   753,   759,   767,   768,   776,   784,   794,   804,   813,
     814,   822,   823,   826,   833,   840,   849,   858,   869
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
  "LBRACKET", "RBRACKET", "IF", "ELSEIF", "ELSE", "ECHO_TOKEN", "IS_INT",
  "IS_STRING", "IS_ARRAY", "IS_FLOAT", "IS_BOOL", "WHILE", "ENDWHILE",
  "INCREMENT", "RETURN", "FUNCTION", "GLOBAL", "PLUS", "CLASS", "NEW",
  "PUBLIC", "PROTECTED", "PRIVATE", "ARROW_OBJ", "VARIABLE", "INTEGER",
  "FLOAT", "CHAR", "STRING", "BOOL", "IDENTIFIER", "$accept", "program",
  "statements", "statement", "variable_declaration", "variable_assignment",
  "expression", "echo_statement", "global_statement", "variable_list",
  "constant_declaration", "if_statement", "elseif_clauses",
  "elseif_clause", "else_clause", "while_statement", "condicion",
  "type_check_func", "value", "array_value", "key_value_list",
  "key_value_pair", "value_list", "function_declaration", "parameter_list",
  "function_call", "argument_list", "array_declaration", "array_items",
  "array_item", "class_declaration", "class_body", "class_member",
  "class_property", "class_method", "object_creation", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-39)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      24,   134,    28,    32,    53,    55,   414,    57,    18,     7,
      45,    12,    67,     3,   -39,   -39,   -39,    96,   -39,   -39,
     -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,    59,
     422,    94,     0,   -39,   -39,   -39,   -39,   -39,   126,   -39,
     442,   131,   -39,     4,   124,   -39,   170,   139,   103,    99,
     383,   -39,   452,   -39,   -39,   140,   -39,   -39,   -39,   -39,
     -39,   109,   147,   155,    14,   149,   -39,   460,   159,    78,
     -39,   156,   -32,   -39,   127,    63,   -39,   161,   125,   130,
      15,   171,   172,   173,   -39,   -39,   174,   163,   -39,   -39,
      65,     1,   181,   471,   480,   490,   498,   509,   177,   145,
     471,   471,   -39,   163,   182,   188,   -39,    73,   183,    98,
     192,   199,   -39,   217,   218,   219,    -2,   -39,   -39,   106,
     -39,   142,   -22,   184,   185,    30,   -39,   -39,   -39,   375,
     206,    46,   -39,   223,   -39,   -39,   -39,   -39,   226,   222,
     392,   -39,   -39,   235,   163,   -39,   163,   -39,   163,   -39,
     163,   -39,   330,   236,   -39,   -39,   471,   471,   -39,    89,
     -39,   -39,   471,   -39,   -39,   -39,   -39,   -39,   350,   134,
     241,   -20,   224,   198,   248,   250,   252,   -39,   -39,   240,
     120,    11,   125,   -39,   255,   -39,   -39,   163,   -39,   -39,
     261,   244,    44,   263,   -39,   -39,   182,   -39,   -39,   -39,
      77,   110,   134,   -39,   -39,   264,   253,   471,   471,   471,
     433,   -39,   262,   -39,   -39,   -39,   -39,   275,   -39,   271,
     -13,   279,   -39,   280,   202,   286,   277,   292,   298,   300,
     -39,   -39,   125,   -39,   134,   290,   296,    62,   -39,   -39,
     283,   -39,   -39,   134,   307,   -39,   -39,   -39,   239,   442,
     367,   308,   -39,   -39,   273,   256,   134,   -39,   301,   -39,
     276,   134,   318,   -39,   293,   316,   -39,   322,   -39,   134,
     -39,   313,   -39
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     3,     8,     7,     0,    12,    15,
       9,    10,    11,    13,    14,    16,    17,     1,    19,     0,
       0,     0,     0,    69,    70,    71,    72,    73,     0,    74,
       0,     0,    36,     0,     0,    20,     0,     0,     0,     0,
      94,     2,     0,     4,    18,     0,    64,    65,    66,    67,
      68,     0,     0,     0,     0,     0,    30,     0,     0,     0,
      29,     0,    88,    35,     0,     0,    23,     0,     0,     0,
       0,     0,     0,     0,    24,    27,     0,    96,    97,    95,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    77,     0,    72,     0,    85,     0,    81,     0,
       0,     0,    31,     0,     0,     0,     0,    89,    90,     0,
      37,     0,     0,     0,     0,     0,   109,   111,   112,     0,
       0,     0,   103,     0,    22,    26,    21,    25,     0,     0,
       0,     6,     5,     0,    54,    57,    55,    58,    56,    59,
      60,    61,     0,     0,    62,    63,     0,     0,    79,     0,
      80,    78,     0,    76,    75,    32,    33,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   108,   110,    72,
       0,     0,     0,   102,     0,    28,    93,    99,   100,    98,
       0,    44,     0,     0,    83,    84,     0,    82,    86,    53,
       0,     0,     0,    91,    92,     0,     0,     0,     0,     0,
       0,   101,     0,   107,   106,   105,   104,     0,    38,     0,
      43,     0,    51,     0,     0,     0,     0,     0,     0,     0,
      69,    72,     0,   118,     0,     0,     0,    41,    47,    42,
       0,    52,    87,     0,     0,   113,   114,   115,     0,     0,
       0,     0,    48,    40,     0,     0,     0,    46,     0,    45,
       0,     0,     0,   117,     0,     0,    50,     0,   116,     0,
      39,     0,    49
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -39,   -39,    -1,   -12,   -39,   -39,   288,   -39,   -39,   -39,
     -39,   -39,   -39,   105,   117,   -39,   -38,   -39,    -3,   -39,
     -39,   176,   -39,   -39,   -39,   -39,   -39,   294,   265,   164,
     -39,   -39,   230,   -39,   -39,   -39
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,   260,    14,    15,    16,    17,    18,    19,    43,
      20,    21,   237,   238,   239,    22,    62,    63,    64,    39,
     107,   108,   109,    23,   119,    24,    90,   215,   180,   132,
      25,   125,   126,   127,   128,    26
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      13,    53,    71,    38,     3,    66,   141,    51,   168,    73,
       4,   235,   236,   117,   173,   169,    74,    45,    46,   118,
     134,    67,    67,   174,   212,   203,     5,     1,    27,     6,
     100,   204,    78,   101,    68,     7,    67,    28,    52,     8,
       9,   177,    10,    82,    69,     3,    47,    89,    11,    92,
      48,     4,    42,    48,    12,   220,    49,   213,   182,    49,
     214,    29,   106,    30,   111,    40,   121,     5,   183,    41,
       6,   122,   123,   124,   139,    50,     7,   140,     3,    52,
       8,     9,   158,    10,     4,   159,   235,   251,   222,    11,
     143,   145,   147,   149,   151,    12,    44,   154,   155,   121,
       5,    54,    65,     6,   122,   123,   124,   161,    55,     7,
     162,     3,    52,     8,     9,   170,    10,     4,   171,   113,
     114,   115,    11,    94,    95,    96,   106,    97,    12,   211,
      67,    70,   182,     5,    75,     3,     6,   189,   196,    72,
     105,     4,     7,   223,    84,    52,     8,     9,    85,    10,
      86,   192,    93,   194,   195,    11,    98,     5,   102,   198,
       6,    12,    31,    99,   112,   116,     7,   200,   201,   129,
       8,     9,   120,    10,   130,    76,   135,   136,   137,    11,
      53,   133,   138,    77,    67,    12,   142,   152,    53,    53,
     153,    78,   160,   172,   103,    33,    34,    35,   104,    37,
     105,   224,   156,     3,   227,   228,   229,   194,   157,     4,
      79,   258,    53,   242,   163,    80,    33,    34,    35,    36,
      37,   164,   165,   166,   167,     5,   181,   186,     6,   175,
     176,   184,   205,   248,     7,   185,    53,    52,     8,     9,
       3,    10,   255,    53,   190,   193,     4,    11,    53,   206,
     257,   202,    53,    12,   207,   264,   208,     3,   209,    53,
     210,   226,     5,     4,   217,     6,   218,   263,   271,   219,
     232,     7,   221,   225,    52,     8,     9,     3,    10,     5,
     233,   234,     6,     4,    11,   241,   244,   266,     7,   240,
      12,    52,     8,     9,     3,    10,   243,   245,   249,     5,
       4,    11,     6,   246,   268,   247,   250,    12,     7,   254,
     265,    52,     8,     9,     3,    10,     5,   256,   261,     6,
       4,    11,   262,   267,   272,     7,   269,    12,    52,     8,
       9,     3,    10,   270,    81,   197,     5,     4,    11,     6,
      83,   191,   252,   131,    12,     7,   216,     0,    52,     8,
       9,     3,    10,     5,   253,   178,     6,     4,    11,     0,
       0,   199,     7,     0,    12,     0,     8,     9,     3,    10,
       0,     0,     0,     5,     4,    11,     6,     0,   259,     0,
       0,    12,     7,     0,   102,     0,     8,     9,    31,    10,
       5,     0,     0,     6,     0,    11,    31,     0,     0,     7,
       0,    12,     0,     8,     9,    31,    10,     0,     0,     0,
       0,     0,    11,     0,     0,     0,     0,     0,    12,     0,
     103,    33,    34,    35,   179,    37,   105,    31,    87,    33,
      34,    35,    36,    37,    88,    31,     0,   187,    33,    34,
      35,    36,    37,   188,     0,     0,    77,     0,     0,    56,
      57,    58,    59,    60,    78,    31,     0,     0,     0,    32,
      33,    34,    35,    36,    37,    31,     0,    61,    33,    34,
      35,    36,    37,    31,     0,     0,     0,     0,   103,   230,
      34,    35,   231,    37,    31,     0,     0,    61,    33,    34,
      35,    36,    37,    31,     0,     0,     0,    91,    33,    34,
      35,    36,    37,    31,     0,   103,    33,    34,    35,   110,
      37,    31,     0,     0,     0,     0,   103,    33,    34,    35,
      36,    37,    31,     0,     0,   144,    33,    34,    35,    36,
      37,     0,     0,     0,     0,   146,    33,    34,    35,    36,
      37,     0,     0,   148,    33,    34,    35,    36,    37,     0,
       0,     0,     0,     0,   150,    33,    34,    35,    36,    37
};

static const yytype_int16 yycheck[] =
{
       1,    13,    40,     6,     1,     5,     5,     4,    10,     5,
       7,    24,    25,    45,    36,    17,    12,     5,     6,    51,
       5,    21,    21,    45,    13,    45,    23,     3,     0,    26,
      16,    51,    21,    19,    34,    32,    21,     5,    35,    36,
      37,    11,    39,    46,    44,     1,    34,    50,    45,    52,
      38,     7,    45,    38,    51,    11,    44,    46,    12,    44,
      49,     8,    65,     8,    67,     8,    36,    23,    22,    51,
      26,    41,    42,    43,     9,     8,    32,    12,     1,    35,
      36,    37,     9,    39,     7,    12,    24,    25,    11,    45,
      93,    94,    95,    96,    97,    51,    51,   100,   101,    36,
      23,     5,     8,    26,    41,    42,    43,     9,    49,    32,
      12,     1,    35,    36,    37,     9,    39,     7,    12,    41,
      42,    43,    45,    14,    15,    16,   129,    18,    51,     9,
      21,     5,    12,    23,    10,     1,    26,   140,    49,     8,
      51,     7,    32,    33,     5,    35,    36,    37,    45,    39,
      51,   152,    12,   156,   157,    45,     9,    23,     9,   162,
      26,    51,    13,     8,     5,     9,    32,   168,   169,     8,
      36,    37,    45,    39,    49,     5,     5,     5,     5,    45,
     192,    51,     8,    13,    21,    51,     5,    10,   200,   201,
      45,    21,     9,    51,    45,    46,    47,    48,    49,    50,
      51,   202,    20,     1,   207,   208,   209,   210,    20,     7,
      40,   249,   224,    11,    22,    45,    46,    47,    48,    49,
      50,    22,     5,     5,     5,    23,    20,     5,    26,    45,
      45,     8,     8,   234,    32,     9,   248,    35,    36,    37,
       1,    39,   243,   255,     9,     9,     7,    45,   260,    51,
      11,    10,   264,    51,     6,   256,     6,     1,     6,   271,
      20,     8,    23,     7,     9,    26,     5,    11,   269,    25,
       8,    32,     9,     9,    35,    36,    37,     1,    39,    23,
       5,    10,    26,     7,    45,     5,     9,    11,    32,    10,
      51,    35,    36,    37,     1,    39,    10,     5,     8,    23,
       7,    45,    26,     5,    11,     5,    10,    51,    32,    26,
       9,    35,    36,    37,     1,    39,    23,    10,    10,    26,
       7,    45,    49,     5,    11,    32,    10,    51,    35,    36,
      37,     1,    39,    11,    46,   159,    23,     7,    45,    26,
      46,    11,   237,    78,    51,    32,   182,    -1,    35,    36,
      37,     1,    39,    23,   237,   125,    26,     7,    45,    -1,
      -1,    11,    32,    -1,    51,    -1,    36,    37,     1,    39,
      -1,    -1,    -1,    23,     7,    45,    26,    -1,    11,    -1,
      -1,    51,    32,    -1,     9,    -1,    36,    37,    13,    39,
      23,    -1,    -1,    26,    -1,    45,    13,    -1,    -1,    32,
      -1,    51,    -1,    36,    37,    13,    39,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    51,    -1,
      45,    46,    47,    48,    49,    50,    51,    13,    45,    46,
      47,    48,    49,    50,    51,    13,    -1,    45,    46,    47,
      48,    49,    50,    51,    -1,    -1,    13,    -1,    -1,    27,
      28,    29,    30,    31,    21,    13,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    50,    13,    -1,    45,    46,    47,
      48,    49,    50,    13,    -1,    -1,    -1,    -1,    45,    46,
      47,    48,    49,    50,    13,    -1,    -1,    45,    46,    47,
      48,    49,    50,    13,    -1,    -1,    -1,    45,    46,    47,
      48,    49,    50,    13,    -1,    45,    46,    47,    48,    49,
      50,    13,    -1,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    50,    13,    -1,    -1,    45,    46,    47,    48,    49,
      50,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    -1,    -1,    45,    46,    47,    48,    49,    50,    -1,
      -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    53,     1,     7,    23,    26,    32,    36,    37,
      39,    45,    51,    54,    55,    56,    57,    58,    59,    60,
      62,    63,    67,    75,    77,    82,    87,     0,     5,     8,
       8,    13,    45,    46,    47,    48,    49,    50,    70,    71,
       8,    51,    45,    61,    51,     5,     6,    34,    38,    44,
       8,     4,    35,    55,     5,    49,    27,    28,    29,    30,
      31,    45,    68,    69,    70,     8,     5,    21,    34,    44,
       5,    68,     8,     5,    12,    10,     5,    13,    21,    40,
      45,    58,    70,    79,     5,    45,    51,    45,    51,    70,
      78,    45,    70,    12,    14,    15,    16,    18,     9,     8,
      16,    19,     9,    45,    49,    51,    70,    72,    73,    74,
      49,    70,     5,    41,    42,    43,     9,    45,    51,    76,
      45,    36,    41,    42,    43,    83,    84,    85,    86,     8,
      49,    80,    81,    51,     5,     5,     5,     5,     8,     9,
      12,     5,     5,    70,    45,    70,    45,    70,    45,    70,
      45,    70,    10,    45,    70,    70,    20,    20,     9,    12,
       9,     9,    12,    22,    22,     5,     5,     5,    10,    17,
       9,    12,    51,    36,    45,    45,    45,    11,    84,    49,
      80,    20,    12,    22,     8,     9,     5,    45,    51,    70,
       9,    11,    54,     9,    70,    70,    49,    73,    70,    11,
      54,    54,    10,    45,    51,     8,    51,     6,     6,     6,
      20,     9,    13,    46,    49,    79,    81,     9,     5,    25,
      11,     9,    11,    33,    54,     9,     8,    70,    70,    70,
      46,    49,     8,     5,    10,    24,    25,    64,    65,    66,
      10,     5,    11,    10,     9,     5,     5,     5,    54,     8,
      10,    25,    65,    66,    26,    54,    10,    11,    68,    11,
      54,    10,    49,    11,    54,     9,    11,     5,    11,    10,
      11,    54,    11
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    52,    53,    54,    54,    54,    54,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      56,    57,    57,    57,    57,    57,    57,    58,    58,    59,
      59,    59,    59,    59,    59,    60,    61,    61,    62,    63,
      63,    63,    63,    63,    63,    63,    63,    64,    64,    65,
      66,    67,    67,    67,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    69,    69,    69,    69,    69,    70,
      70,    70,    70,    70,    70,    70,    70,    71,    71,    71,
      71,    72,    72,    73,    73,    74,    74,    75,    76,    76,
      76,    76,    76,    77,    78,    78,    78,    78,    78,    78,
      78,    79,    79,    80,    80,    81,    81,    81,    82,    83,
      83,    84,    84,    85,    85,    85,    86,    86,    87
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     1,     2,     4,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       2,     4,     4,     3,     3,     4,     4,     3,     5,     3,
       3,     4,     5,     5,     5,     3,     1,     3,     7,    12,
       9,     8,     8,     7,     6,    10,    10,     1,     2,     7,
       4,     7,     8,     6,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     4,     3,     4,     4,
       4,     1,     3,     3,     3,     1,     3,     8,     0,     1,
       1,     3,     3,     5,     0,     1,     1,     1,     3,     3,
       3,     4,     3,     1,     3,     3,     3,     3,     5,     1,
       2,     1,     1,     5,     5,     5,     8,     7,     7
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
#line 175 "phppy.y"
{
    output = (yyvsp[-1].strval);  // Asigna las sentencias generadas a la variable global 'output'
}
#line 1537 "phppy.tab.c"
    break;

  case 4: /* statements: statements statement  */
#line 183 "phppy.y"
    {
        char *result = malloc(strlen((yyvsp[-1].strval)) + strlen((yyvsp[0].strval)) + 1);  // Reserva memoria para el resultado concatenado
        sprintf(result, "%s%s", (yyvsp[-1].strval), (yyvsp[0].strval));  // Concatenar las dos sentencias
        (yyval.strval) = result;  // Almacena el resultado concatenado
    }
#line 1547 "phppy.tab.c"
    break;

  case 5: /* statements: statements RETURN value SEMICOLON  */
#line 189 "phppy.y"
    {
        char *result = malloc(strlen((yyvsp[-3].strval)) + strlen((yyvsp[-1].strval)) + 10);  // Reserva memoria para la sentencia de retorno
        sprintf(result, "%sreturn %s\n", (yyvsp[-3].strval), (yyvsp[-1].strval));  // Formatea la sentencia de retorno
        (yyval.strval) = result;  // Almacena la sentencia de retorno
    }
#line 1557 "phppy.tab.c"
    break;

  case 6: /* statements: statements RETURN VARIABLE SEMICOLON  */
#line 195 "phppy.y"
    {
        char *result = malloc(strlen((yyvsp[-3].strval)) + strlen((yyvsp[-1].strval)) + 10);  // Reserva memoria para la sentencia de retorno
        sprintf(result, "%sreturn %s\n", (yyvsp[-3].strval), (yyvsp[-1].strval) + 1);  // Omite el carácter '$' de la variable y formatea la sentencia de retorno
        (yyval.strval) = result;  // Almacena la sentencia de retorno
    }
#line 1567 "phppy.tab.c"
    break;

  case 19: /* statement: error SEMICOLON  */
#line 215 "phppy.y"
                      { yyerrok; }
#line 1573 "phppy.tab.c"
    break;

  case 20: /* variable_declaration: VARIABLE SEMICOLON  */
#line 220 "phppy.y"
{
    char *var_name = (yyvsp[-1].strval) + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + 10);  // Reserva memoria para la declaración de la variable
    sprintf(result, "%s = None\n", var_name);  // Asigna 'None' a la variable en Python
    (yyval.strval) = result;  // Almacena la declaración de la variable
}
#line 1584 "phppy.tab.c"
    break;

  case 21: /* variable_assignment: VARIABLE ASSIGN value SEMICOLON  */
#line 230 "phppy.y"
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
#line 1599 "phppy.tab.c"
    break;

  case 22: /* variable_assignment: VARIABLE ASSIGN VARIABLE SEMICOLON  */
#line 241 "phppy.y"
{
    char *var_name = (yyvsp[-3].strval) + 1;  // Omite el carácter '$' de la variable
    char *value_name = (yyvsp[-1].strval) + 1;  // Omite el carácter '$' del valor
    char *result = malloc(strlen(var_name) + strlen(value_name) + 5);  // Reserva memoria para la asignación
    sprintf(result, "%s = %s\n", var_name, value_name);  // Asigna la variable a otra variable
    (yyval.strval) = result;  // Almacena la asignación
}
#line 1611 "phppy.tab.c"
    break;

  case 23: /* variable_assignment: VARIABLE ASSIGN SEMICOLON  */
#line 249 "phppy.y"
{
    char *var_name = (yyvsp[-2].strval) + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + 10);  // Reserva memoria para la asignación
    sprintf(result, "%s = None\n", var_name);  // Asigna 'None' a la variable
    (yyval.strval) = result;  // Almacena la asignación
}
#line 1622 "phppy.tab.c"
    break;

  case 24: /* variable_assignment: VARIABLE INCREMENT SEMICOLON  */
#line 256 "phppy.y"
{
    char *var_name = (yyvsp[-2].strval) + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + 7);  // Reserva memoria para el incremento
    sprintf(result, "%s += 1\n", var_name);  // Incrementa la variable
    (yyval.strval) = result;  // Almacena el incremento
}
#line 1633 "phppy.tab.c"
    break;

  case 25: /* variable_assignment: VARIABLE ASSIGN array_declaration SEMICOLON  */
#line 263 "phppy.y"
{
    char *var_name = (yyvsp[-3].strval) + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + strlen((yyvsp[-1].strval)) + 5);  // Reserva memoria para la asignación
    sprintf(result, "%s = %s\n", var_name, (yyvsp[-1].strval));  // Asigna la declaración de array a la variable
    (yyval.strval) = result;  // Almacena la asignación
}
#line 1644 "phppy.tab.c"
    break;

  case 26: /* variable_assignment: VARIABLE ASSIGN expression SEMICOLON  */
#line 270 "phppy.y"
{
    char *var_name = (yyvsp[-3].strval) + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + strlen((yyvsp[-1].strval)) + 5);  // Reserva memoria para la asignación
    sprintf(result, "%s = %s\n", var_name, (yyvsp[-1].strval));  // Asigna la expresión a la variable
    (yyval.strval) = result;  // Almacena la asignación
}
#line 1655 "phppy.tab.c"
    break;

  case 27: /* expression: VARIABLE PLUS VARIABLE  */
#line 280 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);  // Reserva memoria para la suma
    sprintf(result, "%s + %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval) + 1);  // Omite el carácter '$' y suma las variables
    (yyval.strval) = result;  // Almacena la expresión
}
#line 1665 "phppy.tab.c"
    break;

  case 28: /* expression: VARIABLE ARROW_OBJ IDENTIFIER LPAREN RPAREN  */
#line 286 "phppy.y"
{
    char *var_name = (yyvsp[-4].strval) + 1;  // Omite el carácter '$'
    char *method_name = (yyvsp[-2].strval);
    char *result = malloc(strlen(var_name) + strlen(method_name) + 4);
    sprintf(result, "%s.%s()\n", var_name, method_name);
    (yyval.strval) = result;
}
#line 1677 "phppy.tab.c"
    break;

  case 29: /* echo_statement: ECHO_TOKEN value SEMICOLON  */
#line 298 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 8);  // Reserva memoria para la sentencia 'echo'
    sprintf(result, "print(%s)\n", (yyvsp[-1].strval));  // Imprime el valor
    (yyval.strval) = result;  // Almacena la sentencia 'echo'
}
#line 1687 "phppy.tab.c"
    break;

  case 30: /* echo_statement: ECHO_TOKEN VARIABLE SEMICOLON  */
#line 304 "phppy.y"
{
    char *var_name = (yyvsp[-1].strval) + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + 10);  // Reserva memoria para la sentencia 'echo'
    sprintf(result, "print(%s)\n", var_name);  // Imprime la variable
    (yyval.strval) = result;  // Almacena la sentencia 'echo'
}
#line 1698 "phppy.tab.c"
    break;

  case 31: /* echo_statement: ECHO_TOKEN VARIABLE INCREMENT SEMICOLON  */
#line 311 "phppy.y"
{
    char *var_name = (yyvsp[-2].strval) + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + 10);  // Reserva memoria para la sentencia 'echo'
    sprintf(result, "print(%s)\n%s += 1\n", var_name, var_name);  // Imprime e incrementa la variable
    (yyval.strval) = result;  // Almacena la sentencia 'echo'
}
#line 1709 "phppy.tab.c"
    break;

  case 32: /* echo_statement: ECHO_TOKEN VARIABLE ARROW_OBJ PUBLIC SEMICOLON  */
#line 318 "phppy.y"
{
    char *var_name = (yyvsp[-3].strval) + 1;  // Omite el carácter '$'
    char *property_name = "public";
    char *result = malloc(strlen(var_name) + strlen(property_name) + 10);
    sprintf(result, "print(self.%s)\n", property_name);
    (yyval.strval) = result;
}
#line 1721 "phppy.tab.c"
    break;

  case 33: /* echo_statement: ECHO_TOKEN VARIABLE ARROW_OBJ PROTECTED SEMICOLON  */
#line 326 "phppy.y"
{
    char *var_name = (yyvsp[-3].strval) + 1;  // Omite el carácter '$'
    char *property_name = "_protected";
    char *result = malloc(strlen(var_name) + strlen(property_name) + 10);
    sprintf(result, "print(self.%s)\n", property_name);
    (yyval.strval) = result;
}
#line 1733 "phppy.tab.c"
    break;

  case 34: /* echo_statement: ECHO_TOKEN VARIABLE ARROW_OBJ PRIVATE SEMICOLON  */
#line 334 "phppy.y"
{
    char *var_name = (yyvsp[-3].strval) + 1;  // Omite el carácter '$'
    char *property_name = "__private";
    char *result = malloc(strlen(var_name) + strlen(property_name) + 10);
    sprintf(result, "print(self.%s)\n", property_name);
    (yyval.strval) = result;
}
#line 1745 "phppy.tab.c"
    break;

  case 35: /* global_statement: GLOBAL variable_list SEMICOLON  */
#line 347 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 8);  // Reserva memoria para la sentencia 'global'
    sprintf(result, "global %s\n", (yyvsp[-1].strval));  // Marca las variables como globales
    (yyval.strval) = result;  // Almacena la sentencia 'global'
}
#line 1755 "phppy.tab.c"
    break;

  case 36: /* variable_list: VARIABLE  */
#line 356 "phppy.y"
{
    (yyval.strval) = (yyvsp[0].strval) + 1;  // Omite el carácter '$'
}
#line 1763 "phppy.tab.c"
    break;

  case 37: /* variable_list: variable_list COMMA VARIABLE  */
#line 360 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval) + 1) + 3);  // Reserva memoria para la lista
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval) + 1);  // Omite el carácter '$' y agrega la variable a la lista
    (yyval.strval) = result;  // Almacena la lista de variables
}
#line 1773 "phppy.tab.c"
    break;

  case 38: /* constant_declaration: DEFINE LPAREN STRING COMMA value RPAREN SEMICOLON  */
#line 369 "phppy.y"
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
#line 1799 "phppy.tab.c"
    break;

  case 39: /* if_statement: IF LPAREN type_check_func LPAREN VARIABLE RPAREN RPAREN LBRACE ECHO_TOKEN STRING SEMICOLON RBRACE  */
#line 393 "phppy.y"
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
#line 1827 "phppy.tab.c"
    break;

  case 40: /* if_statement: IF LPAREN condicion RPAREN LBRACE statements RBRACE elseif_clauses else_clause  */
#line 417 "phppy.y"
{
    char *if_part = indent_code((yyvsp[-3].strval));  // Indenta el código del bloque 'if'
    char *result = malloc(strlen((yyvsp[-6].strval)) + strlen(if_part) + strlen((yyvsp[-1].strval)) + strlen((yyvsp[0].strval)) + 10);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n%s%s%s", (yyvsp[-6].strval), if_part, (yyvsp[-1].strval), (yyvsp[0].strval));  // Formatea la sentencia 'if' con sus bloques 'elseif' y 'else'
    (yyval.strval) = result;  // Almacena el resultado
    free(if_part);  // Libera la memoria de 'if_part'
}
#line 1839 "phppy.tab.c"
    break;

  case 41: /* if_statement: IF LPAREN condicion RPAREN LBRACE statements RBRACE elseif_clauses  */
#line 425 "phppy.y"
{
    char *if_part = indent_code((yyvsp[-2].strval));  // Indenta el código del bloque 'if'
    char *result = malloc(strlen((yyvsp[-5].strval)) + strlen(if_part) + strlen((yyvsp[0].strval)) + 10);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n%s%s", (yyvsp[-5].strval), if_part, (yyvsp[0].strval));  // Formatea la sentencia 'if' con sus bloques 'elseif'
    (yyval.strval) = result;  // Almacena el resultado
    free(if_part);  // Libera la memoria de 'if_part'
}
#line 1851 "phppy.tab.c"
    break;

  case 42: /* if_statement: IF LPAREN condicion RPAREN LBRACE statements RBRACE else_clause  */
#line 433 "phppy.y"
{
    char *if_part = indent_code((yyvsp[-2].strval));  // Indenta el código del bloque 'if'
    char *result = malloc(strlen((yyvsp[-5].strval)) + strlen(if_part) + strlen((yyvsp[0].strval)) + 20);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n%s%s", (yyvsp[-5].strval), if_part, (yyvsp[0].strval));  // Formatea la sentencia 'if' con su bloque 'else'
    (yyval.strval) = result;  // Almacena el resultado
    free(if_part);  // Libera la memoria de 'if_part'
}
#line 1863 "phppy.tab.c"
    break;

  case 43: /* if_statement: IF LPAREN condicion RPAREN LBRACE statements RBRACE  */
#line 441 "phppy.y"
{
    char *if_part = indent_code((yyvsp[-1].strval));  // Indenta el código del bloque 'if'
    char *result = malloc(strlen((yyvsp[-4].strval)) + strlen(if_part) + 10);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n%s", (yyvsp[-4].strval), if_part);  // Formatea la sentencia 'if'
    (yyval.strval) = result;  // Almacena el resultado
    free(if_part);  // Libera la memoria de 'if_part'
}
#line 1875 "phppy.tab.c"
    break;

  case 44: /* if_statement: IF LPAREN condicion RPAREN LBRACE RBRACE  */
#line 450 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-3].strval)) + 15);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n    pass\n", (yyvsp[-3].strval));  // Formatea la sentencia 'if' con un bloque vacío
    (yyval.strval) = result;  // Almacena el resultado
}
#line 1885 "phppy.tab.c"
    break;

  case 45: /* if_statement: IF LPAREN condicion RPAREN LBRACE statements RBRACE ELSE LBRACE RBRACE  */
#line 456 "phppy.y"
{
    char *indented_statements_if = indent_code((yyvsp[-4].strval));  // Indenta el código del bloque 'if'
    char *result = malloc(strlen((yyvsp[-7].strval)) + strlen(indented_statements_if) + 20);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n%selse:\n    pass\n", (yyvsp[-7].strval), indented_statements_if);  // Formatea la sentencia 'if' con un bloque 'else' vacío
    (yyval.strval) = result;  // Almacena el resultado
    free(indented_statements_if);  // Libera la memoria de 'indented_statements_if'
}
#line 1897 "phppy.tab.c"
    break;

  case 46: /* if_statement: IF LPAREN condicion RPAREN LBRACE RBRACE ELSE LBRACE statements RBRACE  */
#line 464 "phppy.y"
{
    char *indented_statements_else = indent_code((yyvsp[-1].strval));  // Indenta el código del bloque 'else'
    char *result = malloc(strlen((yyvsp[-7].strval)) + strlen(indented_statements_else) + 20);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n    pass\nelse:\n%s", (yyvsp[-7].strval), indented_statements_else);  // Formatea la sentencia 'if' con un bloque 'else'
    (yyval.strval) = result;  // Almacena el resultado
    free(indented_statements_else);  // Libera la memoria de 'indented_statements_else'
}
#line 1909 "phppy.tab.c"
    break;

  case 48: /* elseif_clauses: elseif_clauses elseif_clause  */
#line 475 "phppy.y"
    {
        char *result = malloc(strlen((yyvsp[-1].strval)) + strlen((yyvsp[0].strval)) + 1);  // Reserva memoria para el resultado
        sprintf(result, "%s%s", (yyvsp[-1].strval), (yyvsp[0].strval));  // Concatenar las cláusulas 'elseif'
        (yyval.strval) = result;  // Almacena el resultado
    }
#line 1919 "phppy.tab.c"
    break;

  case 49: /* elseif_clause: ELSEIF LPAREN condicion RPAREN LBRACE statements RBRACE  */
#line 483 "phppy.y"
{
    char *elseif_part = indent_code((yyvsp[-1].strval));  // Indenta el código del bloque 'elseif'
    char *result = malloc(strlen((yyvsp[-4].strval)) + strlen(elseif_part) + 10);  // Reserva memoria para el resultado
    sprintf(result, "elif (%s):\n%s", (yyvsp[-4].strval), elseif_part);  // Formatea la cláusula 'elseif'
    (yyval.strval) = result;  // Almacena el resultado
    free(elseif_part);  // Libera la memoria de 'elseif_part'
}
#line 1931 "phppy.tab.c"
    break;

  case 50: /* else_clause: ELSE LBRACE statements RBRACE  */
#line 493 "phppy.y"
{
    char *else_part = indent_code((yyvsp[-1].strval));  // Indenta el código del bloque 'else'
    char *result = malloc(strlen(else_part) + 20);  // Reserva memoria para el resultado
    sprintf(result, "else:\n%s", else_part);  // Formatea la cláusula 'else'
    (yyval.strval) = result;  // Almacena el resultado
    free(else_part);  // Libera la memoria de 'else_part'
}
#line 1943 "phppy.tab.c"
    break;

  case 51: /* while_statement: WHILE LPAREN condicion RPAREN LBRACE statements RBRACE  */
#line 503 "phppy.y"
{
    char *indented_statements = indent_code((yyvsp[-1].strval));  // Indenta el código del bloque 'while'
    char *result = malloc(strlen((yyvsp[-4].strval)) + strlen(indented_statements) + 15);  // Reserva memoria para el resultado
    sprintf(result, "while (%s):\n%s", (yyvsp[-4].strval), indented_statements);  // Formatea la sentencia 'while'
    (yyval.strval) = result;  // Almacena el resultado
    free(indented_statements);  // Libera la memoria de 'indented_statements'
}
#line 1955 "phppy.tab.c"
    break;

  case 52: /* while_statement: WHILE LPAREN condicion RPAREN COLON statements ENDWHILE SEMICOLON  */
#line 511 "phppy.y"
{
    char *indented_statements = indent_code((yyvsp[-2].strval));  // Indenta el código del bloque 'while'
    char *result = malloc(strlen((yyvsp[-5].strval)) + strlen(indented_statements) + 15);  // Reserva memoria para el resultado
    sprintf(result, "while (%s):\n%s", (yyvsp[-5].strval), indented_statements);  // Formatea la sentencia 'while'
    (yyval.strval) = result;  // Almacena el resultado
    free(indented_statements);  // Libera la memoria de 'indented_statements'
}
#line 1967 "phppy.tab.c"
    break;

  case 53: /* while_statement: WHILE LPAREN condicion RPAREN LBRACE RBRACE  */
#line 519 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-3].strval)) + 15);  // Reserva memoria para el resultado
    sprintf(result, "while (%s):\n    pass\n", (yyvsp[-3].strval));  // Formatea la sentencia 'while' con un bloque vacío
    (yyval.strval) = result;  // Almacena el resultado
}
#line 1977 "phppy.tab.c"
    break;

  case 54: /* condicion: VARIABLE GT VARIABLE  */
#line 528 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4); // 4: para espacio, operador, espacio, y terminador nulo
        sprintf((yyval.strval), "%s > %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval) + 1); // Omitimos el carácter '$'
    }
#line 1986 "phppy.tab.c"
    break;

  case 55: /* condicion: VARIABLE LT VARIABLE  */
#line 533 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
        sprintf((yyval.strval), "%s < %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval) + 1); // Omitimos el carácter '$'
    }
#line 1995 "phppy.tab.c"
    break;

  case 56: /* condicion: VARIABLE EQ VARIABLE  */
#line 538 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
        sprintf((yyval.strval), "%s == %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval) + 1); // En Python se usa '==' para la igualdad
    }
#line 2004 "phppy.tab.c"
    break;

  case 57: /* condicion: VARIABLE GT value  */
#line 543 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4); // 4: para espacio, operador, espacio, y terminador nulo
        sprintf((yyval.strval), "%s > %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval)); // Omitimos el carácter '$'
    }
#line 2013 "phppy.tab.c"
    break;

  case 58: /* condicion: VARIABLE LT value  */
#line 548 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
        sprintf((yyval.strval), "%s < %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval)); // Omitimos el carácter '$'
    }
#line 2022 "phppy.tab.c"
    break;

  case 59: /* condicion: VARIABLE EQ value  */
#line 553 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
        sprintf((yyval.strval), "%s == %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval)); // En Python se usa '==' para la igualdad
    }
#line 2031 "phppy.tab.c"
    break;

  case 60: /* condicion: VARIABLE LE VARIABLE  */
#line 558 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 5);
        sprintf((yyval.strval), "%s <= %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval) + 1); // Omitimos el carácter '$'
    }
#line 2040 "phppy.tab.c"
    break;

  case 61: /* condicion: VARIABLE LE value  */
#line 563 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 5);
        sprintf((yyval.strval), "%s <= %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval)); // Omitimos el carácter '$'
    }
#line 2049 "phppy.tab.c"
    break;

  case 62: /* condicion: value EQ value  */
#line 568 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
        sprintf((yyval.strval), "%s == %s", (yyvsp[-2].strval), (yyvsp[0].strval)); // En Python se usa '==' para la igualdad
    }
#line 2058 "phppy.tab.c"
    break;

  case 63: /* condicion: value NE value  */
#line 573 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 5);
        sprintf((yyval.strval), "%s != %s", (yyvsp[-2].strval), (yyvsp[0].strval)); // En Python se usa '!=' para desigualdad
    }
#line 2067 "phppy.tab.c"
    break;

  case 69: /* value: INTEGER  */
#line 583 "phppy.y"
               { (yyval.strval) = (yyvsp[0].strval); }
#line 2073 "phppy.tab.c"
    break;

  case 70: /* value: FLOAT  */
#line 584 "phppy.y"
            { (yyval.strval) = (yyvsp[0].strval); }
#line 2079 "phppy.tab.c"
    break;

  case 71: /* value: CHAR  */
#line 585 "phppy.y"
           { (yyval.strval) = (yyvsp[0].strval); }
#line 2085 "phppy.tab.c"
    break;

  case 72: /* value: STRING  */
#line 586 "phppy.y"
             { (yyval.strval) = (yyvsp[0].strval); }
#line 2091 "phppy.tab.c"
    break;

  case 73: /* value: BOOL  */
#line 587 "phppy.y"
           { (yyval.strval) = (yyvsp[0].strval); }
#line 2097 "phppy.tab.c"
    break;

  case 74: /* value: array_value  */
#line 588 "phppy.y"
                  { (yyval.strval) = (yyvsp[0].strval); }
#line 2103 "phppy.tab.c"
    break;

  case 75: /* value: VARIABLE LBRACKET value RBRACKET  */
#line 590 "phppy.y"
    {
        char *result = malloc(strlen((yyvsp[-3].strval)) + strlen((yyvsp[-1].strval)) + 4);
        sprintf(result, "%s[%s]", (yyvsp[-3].strval) + 1, (yyvsp[-1].strval));  // Omite el carácter '$' y formatea la variable con el índice
        (yyval.strval) = result;  // Asigna el resultado formateado
    }
#line 2113 "phppy.tab.c"
    break;

  case 76: /* value: VARIABLE LBRACKET STRING RBRACKET  */
#line 596 "phppy.y"
    {
        char *key = strip_quotes((yyvsp[-1].strval));  // Elimina las comillas de la cadena
        char *result = malloc(strlen((yyvsp[-3].strval)) + strlen(key) + 4);
        sprintf(result, "%s[%s]", (yyvsp[-3].strval) + 1, key);  // Omite el carácter '$' y formatea la variable con la clave
        free(key);  // Libera la memoria de la clave
        (yyval.strval) = result;  // Asigna el resultado formateado
    }
#line 2125 "phppy.tab.c"
    break;

  case 77: /* array_value: ARRAY LPAREN RPAREN  */
#line 606 "phppy.y"
{
    (yyval.strval) = strdup("{}");  // Representa un array vacío
}
#line 2133 "phppy.tab.c"
    break;

  case 78: /* array_value: ARRAY LPAREN value_list RPAREN  */
#line 610 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 3);
    sprintf(result, "[%s]", (yyvsp[-1].strval));  // Formatea la lista de valores como un array en Python
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2143 "phppy.tab.c"
    break;

  case 79: /* array_value: ARRAY LPAREN key_value_list RPAREN  */
#line 616 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 3);
    sprintf(result, "{%s}", (yyvsp[-1].strval));  // Formatea la lista de pares clave-valor como un diccionario en Python
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2153 "phppy.tab.c"
    break;

  case 80: /* array_value: ARRAY LPAREN key_value_pair RPAREN  */
#line 622 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 3);
    sprintf(result, "{%s}", (yyvsp[-1].strval));  // Formatea un único par clave-valor como un diccionario en Python
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2163 "phppy.tab.c"
    break;

  case 81: /* key_value_list: key_value_pair  */
#line 630 "phppy.y"
{
    (yyval.strval) = (yyvsp[0].strval);  // Asigna el único par clave-valor a `$$`
}
#line 2171 "phppy.tab.c"
    break;

  case 82: /* key_value_list: key_value_list COMMA key_value_pair  */
#line 634 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval));  // Concadena pares clave-valor con coma
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2181 "phppy.tab.c"
    break;

  case 83: /* key_value_pair: STRING ARROW value  */
#line 642 "phppy.y"
{
    char *key = (yyvsp[-2].strval);  // Asigna la clave
    char *result = malloc(strlen(key) + strlen((yyvsp[0].strval)) + 4);
    sprintf(result, "%s: %s", key, (yyvsp[0].strval));  // Formatea el par clave-valor
    free(key);  // Libera la memoria de la clave
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2193 "phppy.tab.c"
    break;

  case 84: /* key_value_pair: IDENTIFIER ARROW value  */
#line 650 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
    sprintf(result, "\"%s\": %s", (yyvsp[-2].strval), (yyvsp[0].strval));  // Formatea el par clave-valor con identificador como clave
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2203 "phppy.tab.c"
    break;

  case 85: /* value_list: value  */
#line 658 "phppy.y"
{
    (yyval.strval) = (yyvsp[0].strval);  // Asigna un único valor a `$$`
}
#line 2211 "phppy.tab.c"
    break;

  case 86: /* value_list: value_list COMMA value  */
#line 662 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval));  // Concadena valores con coma
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2221 "phppy.tab.c"
    break;

  case 87: /* function_declaration: FUNCTION IDENTIFIER LPAREN parameter_list RPAREN LBRACE statements RBRACE  */
#line 670 "phppy.y"
{
    char *func_name = (yyvsp[-6].strval);  // Asigna el nombre de la función
    char *params = (yyvsp[-4].strval);  // Asigna los parámetros de la función
    char *body = indent_code((yyvsp[-1].strval));  // Indenta el cuerpo de la función
    char *result = malloc(strlen(func_name) + strlen(params) + strlen(body) + 20);
    sprintf(result, "def %s(%s):\n%s", func_name, params, body);  // Formatea la declaración de la función
    (yyval.strval) = result;  // Asigna el resultado formateado
    free(body);  // Libera la memoria del cuerpo de la función
}
#line 2235 "phppy.tab.c"
    break;

  case 88: /* parameter_list: %empty  */
#line 682 "phppy.y"
{
    (yyval.strval) = strdup("");  // Representa una lista de parámetros vacía
}
#line 2243 "phppy.tab.c"
    break;

  case 89: /* parameter_list: VARIABLE  */
#line 686 "phppy.y"
{
    (yyval.strval) = strdup((yyvsp[0].strval) + 1);  // Omite el carácter '$' y representa una variable como parámetro
}
#line 2251 "phppy.tab.c"
    break;

  case 90: /* parameter_list: IDENTIFIER  */
#line 690 "phppy.y"
{
    (yyval.strval) = strdup((yyvsp[0].strval));  // Representa un identificador como parámetro
}
#line 2259 "phppy.tab.c"
    break;

  case 91: /* parameter_list: parameter_list COMMA VARIABLE  */
#line 694 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval) + 1);  // Omite el carácter '$' y concatena variables como parámetros
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2269 "phppy.tab.c"
    break;

  case 92: /* parameter_list: parameter_list COMMA IDENTIFIER  */
#line 700 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval));  // Concatena identificadores como parámetros
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2279 "phppy.tab.c"
    break;

  case 93: /* function_call: IDENTIFIER LPAREN argument_list RPAREN SEMICOLON  */
#line 708 "phppy.y"
{
    char *func_name = (yyvsp[-4].strval);  // Asigna el nombre de la función
    char *args = (yyvsp[-2].strval);  // Asigna los argumentos de la función
    char *result = malloc(strlen(func_name) + strlen(args) + 5);
    sprintf(result, "%s(%s)\n", func_name, args);  // Formatea la llamada a la función
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2291 "phppy.tab.c"
    break;

  case 94: /* argument_list: %empty  */
#line 718 "phppy.y"
{
    (yyval.strval) = strdup("");  // Representa una lista de argumentos vacía
}
#line 2299 "phppy.tab.c"
    break;

  case 95: /* argument_list: value  */
#line 722 "phppy.y"
{
    (yyval.strval) = strdup((yyvsp[0].strval));  // Representa un único valor como argumento
}
#line 2307 "phppy.tab.c"
    break;

  case 96: /* argument_list: VARIABLE  */
#line 726 "phppy.y"
{
    (yyval.strval) = strdup((yyvsp[0].strval) + 1);  // Omite el carácter '$' y representa una variable como argumento
}
#line 2315 "phppy.tab.c"
    break;

  case 97: /* argument_list: IDENTIFIER  */
#line 730 "phppy.y"
{
    (yyval.strval) = strdup((yyvsp[0].strval));  // Representa un identificador como argumento
}
#line 2323 "phppy.tab.c"
    break;

  case 98: /* argument_list: argument_list COMMA value  */
#line 734 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval));  // Concatena valores como argumentos
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2333 "phppy.tab.c"
    break;

  case 99: /* argument_list: argument_list COMMA VARIABLE  */
#line 740 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval) + 1);  // Omite el carácter '$' y concatena variables como argumentos
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2343 "phppy.tab.c"
    break;

  case 100: /* argument_list: argument_list COMMA IDENTIFIER  */
#line 746 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval));  // Concatena identificadores como argumentos
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2353 "phppy.tab.c"
    break;

  case 101: /* array_declaration: ARRAY LPAREN array_items RPAREN  */
#line 754 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 3);
    sprintf(result, "{%s}", (yyvsp[-1].strval));  // Formatea los ítems del array como un diccionario en Python
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2363 "phppy.tab.c"
    break;

  case 102: /* array_declaration: LBRACKET array_items RBRACKET  */
#line 760 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 3);
    sprintf(result, "{%s}", (yyvsp[-1].strval));  // Formatea los ítems del array como un diccionario en Python
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2373 "phppy.tab.c"
    break;

  case 104: /* array_items: array_items COMMA array_item  */
#line 769 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 3);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval));  // Concatena ítems del array con coma
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2383 "phppy.tab.c"
    break;

  case 105: /* array_item: STRING ARROW array_declaration  */
#line 777 "phppy.y"
{
    char *key = strip_quotes((yyvsp[-2].strval));  // Elimina las comillas de la clave
    char *result = malloc(strlen(key) + strlen((yyvsp[0].strval)) + 5);
    sprintf(result, "\"%s\": %s", key, (yyvsp[0].strval));  // Formatea el ítem del array con clave y declaración de array
    free(key);  // Libera la memoria de la clave
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2395 "phppy.tab.c"
    break;

  case 106: /* array_item: STRING ARROW STRING  */
#line 785 "phppy.y"
{
    char *key = strip_quotes((yyvsp[-2].strval));  // Elimina las comillas de la clave
    char *value = strip_quotes((yyvsp[0].strval));  // Elimina las comillas del valor
    char *result = malloc(strlen(key) + strlen(value) + 5);
    sprintf(result, "\"%s\": \"%s\"", key, value);  // Formatea el ítem del array con clave y valor
    free(key);  // Libera la memoria de la clave
    free(value);  // Libera la memoria del valor
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2409 "phppy.tab.c"
    break;

  case 107: /* array_item: STRING ARROW INTEGER  */
#line 795 "phppy.y"
{
    char *key = strip_quotes((yyvsp[-2].strval));  // Elimina las comillas de la clave
    char *result = malloc(strlen(key) + strlen((yyvsp[0].strval)) + 5);
    sprintf(result, "\"%s\": %s", key, (yyvsp[0].strval));  // Formatea el ítem del array con clave y entero
    free(key);  // Libera la memoria de la clave
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2421 "phppy.tab.c"
    break;

  case 108: /* class_declaration: CLASS IDENTIFIER LBRACE class_body RBRACE  */
#line 805 "phppy.y"
{
    char *class_name = (yyvsp[-3].strval);  
    char *result = malloc(strlen(class_name) + strlen((yyvsp[-1].strval)) + 20);
    sprintf(result, "class %s:\n%s", class_name, (yyvsp[-1].strval));
    (yyval.strval) = result;
}
#line 2432 "phppy.tab.c"
    break;

  case 110: /* class_body: class_body class_member  */
#line 815 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + strlen((yyvsp[0].strval)) + 1);
    sprintf(result, "%s%s", (yyvsp[-1].strval), (yyvsp[0].strval));
    (yyval.strval) = result;
}
#line 2442 "phppy.tab.c"
    break;

  case 113: /* class_property: PUBLIC VARIABLE ASSIGN value SEMICOLON  */
#line 827 "phppy.y"
{
    char *property_name = (yyvsp[-3].strval) + 1;  // Omite el carácter '$'
    char *result = malloc(strlen(property_name) + strlen((yyvsp[-1].strval)) + 30);
    sprintf(result, "    def __init__(self):\n        self.%s = %s\n", property_name, (yyvsp[-1].strval));
    (yyval.strval) = result;
}
#line 2453 "phppy.tab.c"
    break;

  case 114: /* class_property: PROTECTED VARIABLE ASSIGN value SEMICOLON  */
#line 834 "phppy.y"
{
    char *property_name = (yyvsp[-3].strval) + 1;  // Omite el carácter '$' y añade un guion bajo
    char *result = malloc(strlen(property_name) + strlen((yyvsp[-1].strval)) + 31);
    sprintf(result, "        self._%s = %s\n", property_name, (yyvsp[-1].strval));
    (yyval.strval) = result;
}
#line 2464 "phppy.tab.c"
    break;

  case 115: /* class_property: PRIVATE VARIABLE ASSIGN value SEMICOLON  */
#line 841 "phppy.y"
{
    char *property_name = (yyvsp[-3].strval) + 1;  // Omite el carácter '$' y añade dos guiones bajos
    char *result = malloc(strlen(property_name) + strlen((yyvsp[-1].strval)) + 32);
    sprintf(result, "        self.__%s = %s\n", property_name, (yyvsp[-1].strval));
    (yyval.strval) = result;
}
#line 2475 "phppy.tab.c"
    break;

  case 116: /* class_method: PUBLIC FUNCTION IDENTIFIER LPAREN RPAREN LBRACE statements RBRACE  */
#line 850 "phppy.y"
{
    char *method_name = (yyvsp[-5].strval);  
    char *indented_statements = indent_code(indent_code((yyvsp[-1].strval)));
    char *result = malloc(strlen(method_name) + strlen(indented_statements) + 20);
    sprintf(result, "    def %s(self):\n%s", method_name, indented_statements);
    (yyval.strval) = result;
    free(indented_statements);
}
#line 2488 "phppy.tab.c"
    break;

  case 117: /* class_method: FUNCTION IDENTIFIER LPAREN RPAREN LBRACE statements RBRACE  */
#line 859 "phppy.y"
{
    char *method_name = (yyvsp[-5].strval);  
    char *indented_statements = indent_code(indent_code((yyvsp[-1].strval)));
    char *result = malloc(strlen(method_name) + strlen(indented_statements) + 20);
    sprintf(result, "    def %s(self):\n%s", method_name, indented_statements);
    (yyval.strval) = result;
    free(indented_statements);
}
#line 2501 "phppy.tab.c"
    break;

  case 118: /* object_creation: VARIABLE ASSIGN NEW IDENTIFIER LPAREN RPAREN SEMICOLON  */
#line 870 "phppy.y"
{
    char *var_name = (yyvsp[-6].strval) + 1;  // Omite el carácter '$'
    char *class_name = (yyvsp[-3].strval);
    char *result = malloc(strlen(var_name) + strlen(class_name) + 10);
    sprintf(result, "%s = %s()\n", var_name, class_name);
    (yyval.strval) = result;
}
#line 2513 "phppy.tab.c"
    break;


#line 2517 "phppy.tab.c"

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

#line 880 "phppy.y"


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
