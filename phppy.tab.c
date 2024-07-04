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
        fprintf(stderr, "Symbol table full\n");
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
  YYSYMBOL_VARIABLE = 39,                  /* VARIABLE  */
  YYSYMBOL_INTEGER = 40,                   /* INTEGER  */
  YYSYMBOL_FLOAT = 41,                     /* FLOAT  */
  YYSYMBOL_CHAR = 42,                      /* CHAR  */
  YYSYMBOL_STRING = 43,                    /* STRING  */
  YYSYMBOL_BOOL = 44,                      /* BOOL  */
  YYSYMBOL_IDENTIFIER = 45,                /* IDENTIFIER  */
  YYSYMBOL_YYACCEPT = 46,                  /* $accept  */
  YYSYMBOL_program = 47,                   /* program  */
  YYSYMBOL_statements = 48,                /* statements  */
  YYSYMBOL_statement = 49,                 /* statement  */
  YYSYMBOL_variable_declaration = 50,      /* variable_declaration  */
  YYSYMBOL_variable_assignment = 51,       /* variable_assignment  */
  YYSYMBOL_expression = 52,                /* expression  */
  YYSYMBOL_echo_statement = 53,            /* echo_statement  */
  YYSYMBOL_global_statement = 54,          /* global_statement  */
  YYSYMBOL_variable_list = 55,             /* variable_list  */
  YYSYMBOL_constant_declaration = 56,      /* constant_declaration  */
  YYSYMBOL_if_statement = 57,              /* if_statement  */
  YYSYMBOL_elseif_clauses = 58,            /* elseif_clauses  */
  YYSYMBOL_elseif_clause = 59,             /* elseif_clause  */
  YYSYMBOL_else_clause = 60,               /* else_clause  */
  YYSYMBOL_while_statement = 61,           /* while_statement  */
  YYSYMBOL_condicion = 62,                 /* condicion  */
  YYSYMBOL_type_check_func = 63,           /* type_check_func  */
  YYSYMBOL_value = 64,                     /* value  */
  YYSYMBOL_array_value = 65,               /* array_value  */
  YYSYMBOL_key_value_list = 66,            /* key_value_list  */
  YYSYMBOL_key_value_pair = 67,            /* key_value_pair  */
  YYSYMBOL_value_list = 68,                /* value_list  */
  YYSYMBOL_function_declaration = 69,      /* function_declaration  */
  YYSYMBOL_parameter_list = 70,            /* parameter_list  */
  YYSYMBOL_function_call = 71,             /* function_call  */
  YYSYMBOL_argument_list = 72,             /* argument_list  */
  YYSYMBOL_array_declaration = 73,         /* array_declaration  */
  YYSYMBOL_array_items = 74,               /* array_items  */
  YYSYMBOL_array_item = 75                 /* array_item  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  23
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   506

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  100
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  215

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   300


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
      45
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   171,   171,   178,   179,   185,   191,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   213,   223,   234,
     242,   249,   256,   263,   273,   282,   288,   295,   305,   314,
     318,   327,   351,   372,   380,   388,   396,   405,   411,   419,
     429,   430,   438,   448,   458,   466,   474,   483,   488,   493,
     498,   503,   508,   513,   518,   523,   528,   536,   536,   536,
     536,   536,   539,   540,   541,   542,   543,   544,   545,   551,
     561,   565,   571,   577,   585,   589,   597,   605,   613,   617,
     625,   638,   641,   645,   649,   655,   663,   674,   677,   681,
     685,   689,   695,   701,   709,   715,   723,   724,   732,   740,
     750
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
  "INCREMENT", "RETURN", "FUNCTION", "GLOBAL", "PLUS", "VARIABLE",
  "INTEGER", "FLOAT", "CHAR", "STRING", "BOOL", "IDENTIFIER", "$accept",
  "program", "statements", "statement", "variable_declaration",
  "variable_assignment", "expression", "echo_statement",
  "global_statement", "variable_list", "constant_declaration",
  "if_statement", "elseif_clauses", "elseif_clause", "else_clause",
  "while_statement", "condicion", "type_check_func", "value",
  "array_value", "key_value_list", "key_value_pair", "value_list",
  "function_declaration", "parameter_list", "function_call",
  "argument_list", "array_declaration", "array_items", "array_item", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-35)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      26,   313,    55,    59,    52,    61,   392,    66,    31,    43,
      10,    90,    13,   -35,   -35,   -35,   -35,   -35,   -35,   -35,
     -35,   -35,   -35,   -35,   -35,    64,   386,    95,    32,   -35,
     -35,   -35,   -35,   -35,    99,   -35,   398,    98,   -35,     6,
     -35,   321,   103,   346,   -35,   405,   -35,    97,   -35,   -35,
     -35,   -35,   -35,    73,   101,   106,   -10,   331,   -35,   411,
     110,   -35,   102,   -17,   -35,    77,   -35,   109,    75,     3,
     115,   116,   117,   -35,   104,   -35,   -35,    -2,     0,   119,
     430,   443,   449,   455,   462,   120,    88,   430,   430,   -35,
     104,   111,   113,   -35,    50,   123,    56,   114,   121,   -35,
       9,   -35,   -35,    63,   -35,   338,   122,     1,   -35,   -35,
     107,   -35,   -35,   -35,   132,   353,   -35,   -35,   141,   104,
     -35,   104,   -35,   104,   -35,   104,   -35,   259,   143,   -35,
     -35,   430,   430,   -35,   -18,   -35,   -35,   430,   -35,   -35,
     279,   313,   131,    18,   136,    81,    30,    75,   -35,   -35,
     -35,   104,   -35,   -35,   153,   134,    60,   151,   -35,   -35,
     111,   -35,   -35,   -35,   112,   154,   313,   -35,   -35,    -9,
     -35,   155,   -35,   -35,   -35,   -35,   -35,   157,    22,   158,
     -35,   159,   172,   -35,   -35,    75,   313,   161,   160,    76,
     -35,   -35,   146,   -35,   -35,   205,   398,   296,   164,   -35,
     -35,   133,   -35,   166,   -35,   222,   313,   173,   171,   -35,
     177,   313,   -35,   242,   -35
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     3,     8,     7,    12,    15,     9,    10,
      11,    13,    14,     1,    16,     0,     0,     0,     0,    62,
      63,    64,    65,    66,     0,    67,     0,     0,    29,     0,
      17,     0,     0,    87,     2,     0,     4,     0,    57,    58,
      59,    60,    61,     0,     0,     0,     0,     0,    26,     0,
       0,    25,     0,    81,    28,     0,    20,     0,     0,     0,
       0,     0,     0,    21,    89,    90,    88,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    70,
       0,    65,     0,    78,     0,    74,     0,     0,     0,    27,
       0,    82,    83,     0,    30,     0,     0,     0,    96,    19,
       0,    23,    18,    22,     0,     0,     6,     5,     0,    47,
      50,    48,    51,    49,    52,    53,    54,     0,     0,    55,
      56,     0,     0,    72,     0,    73,    71,     0,    69,    68,
       0,     0,     0,     0,    65,     0,     0,     0,    95,    24,
      86,    92,    93,    91,     0,    37,     0,     0,    76,    77,
       0,    75,    79,    46,     0,     0,     0,    84,    85,     0,
      94,     0,   100,    99,    98,    97,    31,     0,    36,     0,
      44,     0,     0,    62,    65,     0,     0,     0,     0,    34,
      40,    35,     0,    45,    80,     0,     0,     0,     0,    41,
      33,     0,    39,     0,    38,     0,     0,     0,     0,    43,
       0,     0,    32,     0,    42
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -35,   -35,    -1,   -11,   -35,   -35,   -35,   -35,   -35,   -35,
     -35,   -35,   -35,    -7,     7,   -35,   -34,   -35,    -3,   -35,
     -35,    58,   -35,   -35,   -35,   -35,   -35,   156,   135,    53
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,   205,    13,    14,    15,    70,    16,    17,    39,
      18,    19,   189,   190,   191,    20,    54,    55,    56,    35,
      94,    95,    96,    21,   103,    22,    77,   174,   145,   108
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      12,    46,    62,    34,    67,   116,    87,   114,   109,    88,
     115,    64,    68,   147,     3,    40,    41,    44,    65,   140,
       4,    59,   101,   148,    59,   160,   141,    92,   102,     1,
      90,   183,    30,    31,   184,    33,     5,    58,    71,     6,
      76,   110,    79,   171,    42,     7,   187,   188,    45,     8,
       9,    68,    10,    59,    93,    23,    98,   167,    11,   133,
      25,     3,   134,   168,    24,   136,    60,     4,   137,    26,
     172,   178,   142,   173,    36,   143,    37,   118,   120,   122,
     124,   126,    38,     5,   129,   130,     6,    81,    82,    83,
     170,    84,     7,   147,    59,    45,     8,     9,    43,    10,
     187,   198,    93,    57,    61,    11,    63,    47,    73,    80,
      85,   100,   153,     3,    86,    99,   104,   105,   106,     4,
     111,   112,   113,   180,   117,    59,   156,   128,   158,   159,
     127,   131,   135,   132,   162,     5,   138,   150,     6,   164,
     165,   166,   146,   139,     7,    46,   149,    45,     8,     9,
     154,    10,   157,    46,    46,     3,   169,    11,   176,   177,
     179,     4,   203,   185,   193,   182,   158,   186,   192,   196,
     197,    46,   201,     3,   206,   208,   207,     5,   210,     4,
       6,   211,   199,   194,    46,   195,     7,   181,   212,    45,
       8,     9,   161,    10,    46,     5,   200,    72,     6,    11,
     175,     0,    46,   107,     7,     0,     3,    45,     8,     9,
     213,    10,     4,     0,     0,     0,   202,    11,     0,     0,
       0,     0,     0,     3,     0,     0,     0,     0,     5,     4,
       0,     6,     0,   209,     0,     0,     0,     7,     0,     0,
      45,     8,     9,     3,    10,     5,     0,     0,     6,     4,
      11,     0,     0,   214,     7,     0,     0,    45,     8,     9,
       3,    10,     0,     0,     0,     5,     4,    11,     6,     0,
     155,     0,     0,     0,     7,     0,     0,    45,     8,     9,
       3,    10,     5,     0,     0,     6,     4,    11,     0,     0,
     163,     7,     0,     0,     0,     8,     9,     3,    10,     0,
       0,     0,     5,     4,    11,     6,     0,   204,     0,     0,
       0,     7,     0,     0,     3,     8,     9,     0,    10,     5,
       4,     0,     6,     0,    11,     0,    66,     0,     7,     0,
       0,     0,     8,     9,    67,    10,     5,     0,     0,     6,
      89,    11,    68,     0,    27,     7,     0,    89,     0,     8,
       9,    27,    10,     0,     0,     0,     0,     0,    11,    27,
      69,    29,    30,    31,    32,    33,    27,     0,     0,     0,
      90,    29,    30,    31,    91,    33,    92,    90,    29,    30,
      31,   144,    33,    92,     0,    74,    29,    30,    31,    32,
      33,    75,   151,    29,    30,    31,    32,    33,   152,    27,
       0,     0,     0,     0,     0,    27,     0,     0,     0,     0,
       0,    27,     0,    48,    49,    50,    51,    52,    27,     0,
       0,     0,     0,     0,    27,    53,    29,    30,    31,    32,
      33,    28,    29,    30,    31,    32,    33,    53,    29,    30,
      31,    32,    33,    27,    78,    29,    30,    31,    32,    33,
      90,    29,    30,    31,    97,    33,    27,     0,     0,     0,
       0,     0,    27,     0,     0,     0,     0,     0,    27,    90,
      29,    30,    31,    32,    33,    27,     0,     0,     0,     0,
       0,     0,   119,    29,    30,    31,    32,    33,   121,    29,
      30,    31,    32,    33,   123,    29,    30,    31,    32,    33,
       0,   125,    29,    30,    31,    32,    33
};

static const yytype_int16 yycheck[] =
{
       1,    12,    36,     6,    13,     5,    16,     9,     5,    19,
      12,     5,    21,    12,     1,     5,     6,     4,    12,    10,
       7,    21,    39,    22,    21,    43,    17,    45,    45,     3,
      39,    40,    41,    42,    43,    44,    23,     5,    41,    26,
      43,    38,    45,    13,    34,    32,    24,    25,    35,    36,
      37,    21,    39,    21,    57,     0,    59,    39,    45,     9,
       8,     1,    12,    45,     5,     9,    34,     7,    12,     8,
      40,    11,     9,    43,     8,    12,    45,    80,    81,    82,
      83,    84,    39,    23,    87,    88,    26,    14,    15,    16,
       9,    18,    32,    12,    21,    35,    36,    37,     8,    39,
      24,    25,   105,     8,     5,    45,     8,    43,     5,    12,
       9,     9,   115,     1,     8,     5,    39,     8,    43,     7,
       5,     5,     5,    11,     5,    21,   127,    39,   131,   132,
      10,    20,     9,    20,   137,    23,    22,     5,    26,   140,
     141,    10,    20,    22,    32,   156,    39,    35,    36,    37,
       9,    39,     9,   164,   165,     1,    20,    45,     5,    25,
       9,     7,   196,     8,     5,   166,   169,    10,    10,     8,
      10,   182,    26,     1,    10,     9,    43,    23,     5,     7,
      26,    10,   189,    11,   195,   186,    32,    33,    11,    35,
      36,    37,   134,    39,   205,    23,   189,    41,    26,    45,
     147,    -1,   213,    68,    32,    -1,     1,    35,    36,    37,
     211,    39,     7,    -1,    -1,    -1,    11,    45,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    23,     7,
      -1,    26,    -1,    11,    -1,    -1,    -1,    32,    -1,    -1,
      35,    36,    37,     1,    39,    23,    -1,    -1,    26,     7,
      45,    -1,    -1,    11,    32,    -1,    -1,    35,    36,    37,
       1,    39,    -1,    -1,    -1,    23,     7,    45,    26,    -1,
      11,    -1,    -1,    -1,    32,    -1,    -1,    35,    36,    37,
       1,    39,    23,    -1,    -1,    26,     7,    45,    -1,    -1,
      11,    32,    -1,    -1,    -1,    36,    37,     1,    39,    -1,
      -1,    -1,    23,     7,    45,    26,    -1,    11,    -1,    -1,
      -1,    32,    -1,    -1,     1,    36,    37,    -1,    39,    23,
       7,    -1,    26,    -1,    45,    -1,     5,    -1,    32,    -1,
      -1,    -1,    36,    37,    13,    39,    23,    -1,    -1,    26,
       9,    45,    21,    -1,    13,    32,    -1,     9,    -1,    36,
      37,    13,    39,    -1,    -1,    -1,    -1,    -1,    45,    13,
      39,    40,    41,    42,    43,    44,    13,    -1,    -1,    -1,
      39,    40,    41,    42,    43,    44,    45,    39,    40,    41,
      42,    43,    44,    45,    -1,    39,    40,    41,    42,    43,
      44,    45,    39,    40,    41,    42,    43,    44,    45,    13,
      -1,    -1,    -1,    -1,    -1,    13,    -1,    -1,    -1,    -1,
      -1,    13,    -1,    27,    28,    29,    30,    31,    13,    -1,
      -1,    -1,    -1,    -1,    13,    39,    40,    41,    42,    43,
      44,    39,    40,    41,    42,    43,    44,    39,    40,    41,
      42,    43,    44,    13,    39,    40,    41,    42,    43,    44,
      39,    40,    41,    42,    43,    44,    13,    -1,    -1,    -1,
      -1,    -1,    13,    -1,    -1,    -1,    -1,    -1,    13,    39,
      40,    41,    42,    43,    44,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    40,    41,    42,    43,    44,    39,    40,
      41,    42,    43,    44,    39,    40,    41,    42,    43,    44,
      -1,    39,    40,    41,    42,    43,    44
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    47,     1,     7,    23,    26,    32,    36,    37,
      39,    45,    48,    49,    50,    51,    53,    54,    56,    57,
      61,    69,    71,     0,     5,     8,     8,    13,    39,    40,
      41,    42,    43,    44,    64,    65,     8,    45,    39,    55,
       5,     6,    34,     8,     4,    35,    49,    43,    27,    28,
      29,    30,    31,    39,    62,    63,    64,     8,     5,    21,
      34,     5,    62,     8,     5,    12,     5,    13,    21,    39,
      52,    64,    73,     5,    39,    45,    64,    72,    39,    64,
      12,    14,    15,    16,    18,     9,     8,    16,    19,     9,
      39,    43,    45,    64,    66,    67,    68,    43,    64,     5,
       9,    39,    45,    70,    39,     8,    43,    74,    75,     5,
      38,     5,     5,     5,     9,    12,     5,     5,    64,    39,
      64,    39,    64,    39,    64,    39,    64,    10,    39,    64,
      64,    20,    20,     9,    12,     9,     9,    12,    22,    22,
      10,    17,     9,    12,    43,    74,    20,    12,    22,    39,
       5,    39,    45,    64,     9,    11,    48,     9,    64,    64,
      43,    67,    64,    11,    48,    48,    10,    39,    45,    20,
       9,    13,    40,    43,    73,    75,     5,    25,    11,     9,
      11,    33,    48,    40,    43,     8,    10,    24,    25,    58,
      59,    60,    10,     5,    11,    48,     8,    10,    25,    59,
      60,    26,    11,    62,    11,    48,    10,    43,     9,    11,
       5,    10,    11,    48,    11
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    46,    47,    48,    48,    48,    48,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    50,    51,    51,
      51,    51,    51,    51,    52,    53,    53,    53,    54,    55,
      55,    56,    57,    57,    57,    57,    57,    57,    57,    57,
      58,    58,    59,    60,    61,    61,    61,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    63,    63,    63,
      63,    63,    64,    64,    64,    64,    64,    64,    64,    64,
      65,    65,    65,    65,    66,    66,    67,    67,    68,    68,
      69,    70,    70,    70,    70,    70,    71,    72,    72,    72,
      72,    72,    72,    72,    73,    73,    74,    74,    75,    75,
      75
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     1,     2,     4,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     4,     4,
       3,     3,     4,     4,     3,     3,     3,     4,     3,     1,
       3,     7,    12,     9,     8,     8,     7,     6,    10,    10,
       1,     2,     7,     4,     7,     8,     6,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     4,     4,
       3,     4,     4,     4,     1,     3,     3,     3,     1,     3,
       8,     0,     1,     1,     3,     3,     5,     0,     1,     1,
       1,     3,     3,     3,     4,     3,     1,     3,     3,     3,
       3
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
#line 172 "phppy.y"
{
    output = (yyvsp[-1].strval);  // Asigna las sentencias generadas a la variable global 'output'
}
#line 1490 "phppy.tab.c"
    break;

  case 4: /* statements: statements statement  */
#line 180 "phppy.y"
    {
        char *result = malloc(strlen((yyvsp[-1].strval)) + strlen((yyvsp[0].strval)) + 1);  // Reserva memoria para el resultado concatenado
        sprintf(result, "%s%s", (yyvsp[-1].strval), (yyvsp[0].strval));  // Concatenar las dos sentencias
        (yyval.strval) = result;  // Almacena el resultado concatenado
    }
#line 1500 "phppy.tab.c"
    break;

  case 5: /* statements: statements RETURN value SEMICOLON  */
#line 186 "phppy.y"
    {
        char *result = malloc(strlen((yyvsp[-3].strval)) + strlen((yyvsp[-1].strval)) + 10);  // Reserva memoria para la sentencia de retorno
        sprintf(result, "%sreturn %s\n", (yyvsp[-3].strval), (yyvsp[-1].strval));  // Formatea la sentencia de retorno
        (yyval.strval) = result;  // Almacena la sentencia de retorno
    }
#line 1510 "phppy.tab.c"
    break;

  case 6: /* statements: statements RETURN VARIABLE SEMICOLON  */
#line 192 "phppy.y"
    {
        char *result = malloc(strlen((yyvsp[-3].strval)) + strlen((yyvsp[-1].strval)) + 10);  // Reserva memoria para la sentencia de retorno
        sprintf(result, "%sreturn %s\n", (yyvsp[-3].strval), (yyvsp[-1].strval) + 1);  // Omite el carácter '$' de la variable y formatea la sentencia de retorno
        (yyval.strval) = result;  // Almacena la sentencia de retorno
    }
#line 1520 "phppy.tab.c"
    break;

  case 16: /* statement: error SEMICOLON  */
#line 209 "phppy.y"
                      { yyerrok; }
#line 1526 "phppy.tab.c"
    break;

  case 17: /* variable_declaration: VARIABLE SEMICOLON  */
#line 214 "phppy.y"
{
    char *var_name = (yyvsp[-1].strval) + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + 10);  // Reserva memoria para la declaración de la variable
    sprintf(result, "%s = None\n", var_name);  // Asigna 'None' a la variable en Python
    (yyval.strval) = result;  // Almacena la declaración de la variable
}
#line 1537 "phppy.tab.c"
    break;

  case 18: /* variable_assignment: VARIABLE ASSIGN value SEMICOLON  */
#line 224 "phppy.y"
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
#line 1552 "phppy.tab.c"
    break;

  case 19: /* variable_assignment: VARIABLE ASSIGN VARIABLE SEMICOLON  */
#line 235 "phppy.y"
{
    char *var_name = (yyvsp[-3].strval) + 1;  // Omite el carácter '$' de la variable
    char *value_name = (yyvsp[-1].strval) + 1;  // Omite el carácter '$' del valor
    char *result = malloc(strlen(var_name) + strlen(value_name) + 5);  // Reserva memoria para la asignación
    sprintf(result, "%s = %s\n", var_name, value_name);  // Asigna la variable a otra variable
    (yyval.strval) = result;  // Almacena la asignación
}
#line 1564 "phppy.tab.c"
    break;

  case 20: /* variable_assignment: VARIABLE ASSIGN SEMICOLON  */
#line 243 "phppy.y"
{
    char *var_name = (yyvsp[-2].strval) + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + 10);  // Reserva memoria para la asignación
    sprintf(result, "%s = None\n", var_name);  // Asigna 'None' a la variable
    (yyval.strval) = result;  // Almacena la asignación
}
#line 1575 "phppy.tab.c"
    break;

  case 21: /* variable_assignment: VARIABLE INCREMENT SEMICOLON  */
#line 250 "phppy.y"
{
    char *var_name = (yyvsp[-2].strval) + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + 7);  // Reserva memoria para el incremento
    sprintf(result, "%s += 1\n", var_name);  // Incrementa la variable
    (yyval.strval) = result;  // Almacena el incremento
}
#line 1586 "phppy.tab.c"
    break;

  case 22: /* variable_assignment: VARIABLE ASSIGN array_declaration SEMICOLON  */
#line 257 "phppy.y"
{
    char *var_name = (yyvsp[-3].strval) + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + strlen((yyvsp[-1].strval)) + 5);  // Reserva memoria para la asignación
    sprintf(result, "%s = %s\n", var_name, (yyvsp[-1].strval));  // Asigna la declaración de array a la variable
    (yyval.strval) = result;  // Almacena la asignación
}
#line 1597 "phppy.tab.c"
    break;

  case 23: /* variable_assignment: VARIABLE ASSIGN expression SEMICOLON  */
#line 264 "phppy.y"
{
    char *var_name = (yyvsp[-3].strval) + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + strlen((yyvsp[-1].strval)) + 5);  // Reserva memoria para la asignación
    sprintf(result, "%s = %s\n", var_name, (yyvsp[-1].strval));  // Asigna la expresión a la variable
    (yyval.strval) = result;  // Almacena la asignación
}
#line 1608 "phppy.tab.c"
    break;

  case 24: /* expression: VARIABLE PLUS VARIABLE  */
#line 274 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);  // Reserva memoria para la suma
    sprintf(result, "%s + %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval) + 1);  // Omite el carácter '$' y suma las variables
    (yyval.strval) = result;  // Almacena la expresión
}
#line 1618 "phppy.tab.c"
    break;

  case 25: /* echo_statement: ECHO_TOKEN value SEMICOLON  */
#line 283 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 8);  // Reserva memoria para la sentencia 'echo'
    sprintf(result, "print(%s)\n", (yyvsp[-1].strval));  // Imprime el valor
    (yyval.strval) = result;  // Almacena la sentencia 'echo'
}
#line 1628 "phppy.tab.c"
    break;

  case 26: /* echo_statement: ECHO_TOKEN VARIABLE SEMICOLON  */
#line 289 "phppy.y"
{
    char *var_name = (yyvsp[-1].strval) + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + 10);  // Reserva memoria para la sentencia 'echo'
    sprintf(result, "print(%s)\n", var_name);  // Imprime la variable
    (yyval.strval) = result;  // Almacena la sentencia 'echo'
}
#line 1639 "phppy.tab.c"
    break;

  case 27: /* echo_statement: ECHO_TOKEN VARIABLE INCREMENT SEMICOLON  */
#line 296 "phppy.y"
{
    char *var_name = (yyvsp[-2].strval) + 1;  // Omite el carácter '$' de la variable
    char *result = malloc(strlen(var_name) + 10);  // Reserva memoria para la sentencia 'echo'
    sprintf(result, "print(%s)\n%s += 1\n", var_name, var_name);  // Imprime e incrementa la variable
    (yyval.strval) = result;  // Almacena la sentencia 'echo'
}
#line 1650 "phppy.tab.c"
    break;

  case 28: /* global_statement: GLOBAL variable_list SEMICOLON  */
#line 306 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 8);  // Reserva memoria para la sentencia 'global'
    sprintf(result, "global %s\n", (yyvsp[-1].strval));  // Marca las variables como globales
    (yyval.strval) = result;  // Almacena la sentencia 'global'
}
#line 1660 "phppy.tab.c"
    break;

  case 29: /* variable_list: VARIABLE  */
#line 315 "phppy.y"
{
    (yyval.strval) = (yyvsp[0].strval) + 1;  // Omite el carácter '$'
}
#line 1668 "phppy.tab.c"
    break;

  case 30: /* variable_list: variable_list COMMA VARIABLE  */
#line 319 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval) + 1) + 3);  // Reserva memoria para la lista
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval) + 1);  // Omite el carácter '$' y agrega la variable a la lista
    (yyval.strval) = result;  // Almacena la lista de variables
}
#line 1678 "phppy.tab.c"
    break;

  case 31: /* constant_declaration: DEFINE LPAREN STRING COMMA value RPAREN SEMICOLON  */
#line 328 "phppy.y"
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
#line 1704 "phppy.tab.c"
    break;

  case 32: /* if_statement: IF LPAREN type_check_func LPAREN VARIABLE RPAREN RPAREN LBRACE ECHO_TOKEN STRING SEMICOLON RBRACE  */
#line 352 "phppy.y"
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
    printf("if isinstance(%s, %s):\n    print(%s, \"\\%s\")\n", (yyvsp[-7].strval) + 1, py_type, (yyvsp[-7].strval) + 1, formatted_message);  // Imprime la sentencia 'if' en Python
    free(unquoted);  // Libera la memoria de 'unquoted'
    free(message);  // Libera la memoria de 'message'
    free(formatted_message);  // Libera la memoria de 'formatted_message'
}
#line 1729 "phppy.tab.c"
    break;

  case 33: /* if_statement: IF LPAREN condicion RPAREN LBRACE statements RBRACE elseif_clauses else_clause  */
#line 373 "phppy.y"
{
    char *if_part = indent_code((yyvsp[-3].strval));  // Indenta el código del bloque 'if'
    char *result = malloc(strlen((yyvsp[-6].strval)) + strlen(if_part) + strlen((yyvsp[-1].strval)) + strlen((yyvsp[0].strval)) + 10);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n%s%s%s", (yyvsp[-6].strval), if_part, (yyvsp[-1].strval), (yyvsp[0].strval));  // Formatea la sentencia 'if' con sus bloques 'elseif' y 'else'
    (yyval.strval) = result;  // Almacena el resultado
    free(if_part);  // Libera la memoria de 'if_part'
}
#line 1741 "phppy.tab.c"
    break;

  case 34: /* if_statement: IF LPAREN condicion RPAREN LBRACE statements RBRACE elseif_clauses  */
#line 381 "phppy.y"
{
    char *if_part = indent_code((yyvsp[-2].strval));  // Indenta el código del bloque 'if'
    char *result = malloc(strlen((yyvsp[-5].strval)) + strlen(if_part) + strlen((yyvsp[0].strval)) + 10);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n%s%s", (yyvsp[-5].strval), if_part, (yyvsp[0].strval));  // Formatea la sentencia 'if' con sus bloques 'elseif'
    (yyval.strval) = result;  // Almacena el resultado
    free(if_part);  // Libera la memoria de 'if_part'
}
#line 1753 "phppy.tab.c"
    break;

  case 35: /* if_statement: IF LPAREN condicion RPAREN LBRACE statements RBRACE else_clause  */
#line 389 "phppy.y"
{
    char *if_part = indent_code((yyvsp[-2].strval));  // Indenta el código del bloque 'if'
    char *result = malloc(strlen((yyvsp[-5].strval)) + strlen(if_part) + strlen((yyvsp[0].strval)) + 20);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n%s%s", (yyvsp[-5].strval), if_part, (yyvsp[0].strval));  // Formatea la sentencia 'if' con su bloque 'else'
    (yyval.strval) = result;  // Almacena el resultado
    free(if_part);  // Libera la memoria de 'if_part'
}
#line 1765 "phppy.tab.c"
    break;

  case 36: /* if_statement: IF LPAREN condicion RPAREN LBRACE statements RBRACE  */
#line 397 "phppy.y"
{
    char *if_part = indent_code((yyvsp[-1].strval));  // Indenta el código del bloque 'if'
    char *result = malloc(strlen((yyvsp[-4].strval)) + strlen(if_part) + 10);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n%s", (yyvsp[-4].strval), if_part);  // Formatea la sentencia 'if'
    (yyval.strval) = result;  // Almacena el resultado
    free(if_part);  // Libera la memoria de 'if_part'
}
#line 1777 "phppy.tab.c"
    break;

  case 37: /* if_statement: IF LPAREN condicion RPAREN LBRACE RBRACE  */
#line 406 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-3].strval)) + 15);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n    pass\n", (yyvsp[-3].strval));  // Formatea la sentencia 'if' con un bloque vacío
    (yyval.strval) = result;  // Almacena el resultado
}
#line 1787 "phppy.tab.c"
    break;

  case 38: /* if_statement: IF LPAREN condicion RPAREN LBRACE statements RBRACE ELSE LBRACE RBRACE  */
#line 412 "phppy.y"
{
    char *indented_statements_if = indent_code((yyvsp[-4].strval));  // Indenta el código del bloque 'if'
    char *result = malloc(strlen((yyvsp[-7].strval)) + strlen(indented_statements_if) + 20);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n%selse:\n    pass\n", (yyvsp[-7].strval), indented_statements_if);  // Formatea la sentencia 'if' con un bloque 'else' vacío
    (yyval.strval) = result;  // Almacena el resultado
    free(indented_statements_if);  // Libera la memoria de 'indented_statements_if'
}
#line 1799 "phppy.tab.c"
    break;

  case 39: /* if_statement: IF LPAREN condicion RPAREN LBRACE RBRACE ELSE LBRACE statements RBRACE  */
#line 420 "phppy.y"
{
    char *indented_statements_else = indent_code((yyvsp[-1].strval));  // Indenta el código del bloque 'else'
    char *result = malloc(strlen((yyvsp[-7].strval)) + strlen(indented_statements_else) + 20);  // Reserva memoria para el resultado
    sprintf(result, "if (%s):\n    pass\nelse:\n%s", (yyvsp[-7].strval), indented_statements_else);  // Formatea la sentencia 'if' con un bloque 'else'
    (yyval.strval) = result;  // Almacena el resultado
    free(indented_statements_else);  // Libera la memoria de 'indented_statements_else'
}
#line 1811 "phppy.tab.c"
    break;

  case 41: /* elseif_clauses: elseif_clauses elseif_clause  */
#line 431 "phppy.y"
    {
        char *result = malloc(strlen((yyvsp[-1].strval)) + strlen((yyvsp[0].strval)) + 1);  // Reserva memoria para el resultado
        sprintf(result, "%s%s", (yyvsp[-1].strval), (yyvsp[0].strval));  // Concatenar las cláusulas 'elseif'
        (yyval.strval) = result;  // Almacena el resultado
    }
#line 1821 "phppy.tab.c"
    break;

  case 42: /* elseif_clause: ELSEIF LPAREN condicion RPAREN LBRACE statements RBRACE  */
#line 439 "phppy.y"
{
    char *elseif_part = indent_code((yyvsp[-1].strval));  // Indenta el código del bloque 'elseif'
    char *result = malloc(strlen((yyvsp[-4].strval)) + strlen(elseif_part) + 10);  // Reserva memoria para el resultado
    sprintf(result, "elif (%s):\n%s", (yyvsp[-4].strval), elseif_part);  // Formatea la cláusula 'elseif'
    (yyval.strval) = result;  // Almacena el resultado
    free(elseif_part);  // Libera la memoria de 'elseif_part'
}
#line 1833 "phppy.tab.c"
    break;

  case 43: /* else_clause: ELSE LBRACE statements RBRACE  */
#line 449 "phppy.y"
{
    char *else_part = indent_code((yyvsp[-1].strval));  // Indenta el código del bloque 'else'
    char *result = malloc(strlen(else_part) + 20);  // Reserva memoria para el resultado
    sprintf(result, "else:\n%s", else_part);  // Formatea la cláusula 'else'
    (yyval.strval) = result;  // Almacena el resultado
    free(else_part);  // Libera la memoria de 'else_part'
}
#line 1845 "phppy.tab.c"
    break;

  case 44: /* while_statement: WHILE LPAREN condicion RPAREN LBRACE statements RBRACE  */
#line 459 "phppy.y"
{
    char *indented_statements = indent_code((yyvsp[-1].strval));  // Indenta el código del bloque 'while'
    char *result = malloc(strlen((yyvsp[-4].strval)) + strlen(indented_statements) + 15);  // Reserva memoria para el resultado
    sprintf(result, "while (%s):\n%s", (yyvsp[-4].strval), indented_statements);  // Formatea la sentencia 'while'
    (yyval.strval) = result;  // Almacena el resultado
    free(indented_statements);  // Libera la memoria de 'indented_statements'
}
#line 1857 "phppy.tab.c"
    break;

  case 45: /* while_statement: WHILE LPAREN condicion RPAREN COLON statements ENDWHILE SEMICOLON  */
#line 467 "phppy.y"
{
    char *indented_statements = indent_code((yyvsp[-2].strval));  // Indenta el código del bloque 'while'
    char *result = malloc(strlen((yyvsp[-5].strval)) + strlen(indented_statements) + 15);  // Reserva memoria para el resultado
    sprintf(result, "while (%s):\n%s", (yyvsp[-5].strval), indented_statements);  // Formatea la sentencia 'while'
    (yyval.strval) = result;  // Almacena el resultado
    free(indented_statements);  // Libera la memoria de 'indented_statements'
}
#line 1869 "phppy.tab.c"
    break;

  case 46: /* while_statement: WHILE LPAREN condicion RPAREN LBRACE RBRACE  */
#line 475 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-3].strval)) + 15);  // Reserva memoria para el resultado
    sprintf(result, "while (%s):\n    pass\n", (yyvsp[-3].strval));  // Formatea la sentencia 'while' con un bloque vacío
    (yyval.strval) = result;  // Almacena el resultado
}
#line 1879 "phppy.tab.c"
    break;

  case 47: /* condicion: VARIABLE GT VARIABLE  */
#line 484 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4); // 4: para espacio, operador, espacio, y terminador nulo
        sprintf((yyval.strval), "%s > %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval) + 1); // Omitimos el carácter '$'
    }
#line 1888 "phppy.tab.c"
    break;

  case 48: /* condicion: VARIABLE LT VARIABLE  */
#line 489 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
        sprintf((yyval.strval), "%s < %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval) + 1); // Omitimos el carácter '$'
    }
#line 1897 "phppy.tab.c"
    break;

  case 49: /* condicion: VARIABLE EQ VARIABLE  */
#line 494 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
        sprintf((yyval.strval), "%s == %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval) + 1); // En Python se usa '==' para la igualdad
    }
#line 1906 "phppy.tab.c"
    break;

  case 50: /* condicion: VARIABLE GT value  */
#line 499 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4); // 4: para espacio, operador, espacio, y terminador nulo
        sprintf((yyval.strval), "%s > %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval)); // Omitimos el carácter '$'
    }
#line 1915 "phppy.tab.c"
    break;

  case 51: /* condicion: VARIABLE LT value  */
#line 504 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
        sprintf((yyval.strval), "%s < %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval)); // Omitimos el carácter '$'
    }
#line 1924 "phppy.tab.c"
    break;

  case 52: /* condicion: VARIABLE EQ value  */
#line 509 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
        sprintf((yyval.strval), "%s == %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval)); // En Python se usa '==' para la igualdad
    }
#line 1933 "phppy.tab.c"
    break;

  case 53: /* condicion: VARIABLE LE VARIABLE  */
#line 514 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 5);
        sprintf((yyval.strval), "%s <= %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval) + 1); // Omitimos el carácter '$'
    }
#line 1942 "phppy.tab.c"
    break;

  case 54: /* condicion: VARIABLE LE value  */
#line 519 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 5);
        sprintf((yyval.strval), "%s <= %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval)); // Omitimos el carácter '$'
    }
#line 1951 "phppy.tab.c"
    break;

  case 55: /* condicion: value EQ value  */
#line 524 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
        sprintf((yyval.strval), "%s == %s", (yyvsp[-2].strval), (yyvsp[0].strval)); // En Python se usa '==' para la igualdad
    }
#line 1960 "phppy.tab.c"
    break;

  case 56: /* condicion: value NE value  */
#line 529 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 5);
        sprintf((yyval.strval), "%s != %s", (yyvsp[-2].strval), (yyvsp[0].strval)); // En Python se usa '!=' para desigualdad
    }
#line 1969 "phppy.tab.c"
    break;

  case 62: /* value: INTEGER  */
#line 539 "phppy.y"
               { (yyval.strval) = (yyvsp[0].strval); }
#line 1975 "phppy.tab.c"
    break;

  case 63: /* value: FLOAT  */
#line 540 "phppy.y"
            { (yyval.strval) = (yyvsp[0].strval); }
#line 1981 "phppy.tab.c"
    break;

  case 64: /* value: CHAR  */
#line 541 "phppy.y"
           { (yyval.strval) = (yyvsp[0].strval); }
#line 1987 "phppy.tab.c"
    break;

  case 65: /* value: STRING  */
#line 542 "phppy.y"
             { (yyval.strval) = (yyvsp[0].strval); }
#line 1993 "phppy.tab.c"
    break;

  case 66: /* value: BOOL  */
#line 543 "phppy.y"
           { (yyval.strval) = (yyvsp[0].strval); }
#line 1999 "phppy.tab.c"
    break;

  case 67: /* value: array_value  */
#line 544 "phppy.y"
                  { (yyval.strval) = (yyvsp[0].strval); }
#line 2005 "phppy.tab.c"
    break;

  case 68: /* value: VARIABLE LBRACKET value RBRACKET  */
#line 546 "phppy.y"
    {
        char *result = malloc(strlen((yyvsp[-3].strval)) + strlen((yyvsp[-1].strval)) + 4);
        sprintf(result, "%s[%s]", (yyvsp[-3].strval) + 1, (yyvsp[-1].strval));  // Omite el carácter '$' y formatea la variable con el índice
        (yyval.strval) = result;  // Asigna el resultado formateado
    }
#line 2015 "phppy.tab.c"
    break;

  case 69: /* value: VARIABLE LBRACKET STRING RBRACKET  */
#line 552 "phppy.y"
    {
        char *key = strip_quotes((yyvsp[-1].strval));  // Elimina las comillas de la cadena
        char *result = malloc(strlen((yyvsp[-3].strval)) + strlen(key) + 4);
        sprintf(result, "%s[%s]", (yyvsp[-3].strval) + 1, key);  // Omite el carácter '$' y formatea la variable con la clave
        free(key);  // Libera la memoria de la clave
        (yyval.strval) = result;  // Asigna el resultado formateado
    }
#line 2027 "phppy.tab.c"
    break;

  case 70: /* array_value: ARRAY LPAREN RPAREN  */
#line 562 "phppy.y"
{
    (yyval.strval) = strdup("{}");  // Representa un array vacío
}
#line 2035 "phppy.tab.c"
    break;

  case 71: /* array_value: ARRAY LPAREN value_list RPAREN  */
#line 566 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 3);
    sprintf(result, "[%s]", (yyvsp[-1].strval));  // Formatea la lista de valores como un array en Python
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2045 "phppy.tab.c"
    break;

  case 72: /* array_value: ARRAY LPAREN key_value_list RPAREN  */
#line 572 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 3);
    sprintf(result, "{%s}", (yyvsp[-1].strval));  // Formatea la lista de pares clave-valor como un diccionario en Python
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2055 "phppy.tab.c"
    break;

  case 73: /* array_value: ARRAY LPAREN key_value_pair RPAREN  */
#line 578 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 3);
    sprintf(result, "{%s}", (yyvsp[-1].strval));  // Formatea un único par clave-valor como un diccionario en Python
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2065 "phppy.tab.c"
    break;

  case 74: /* key_value_list: key_value_pair  */
#line 586 "phppy.y"
{
    (yyval.strval) = (yyvsp[0].strval);  // Asigna el único par clave-valor a `$$`
}
#line 2073 "phppy.tab.c"
    break;

  case 75: /* key_value_list: key_value_list COMMA key_value_pair  */
#line 590 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval));  // Concadena pares clave-valor con coma
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2083 "phppy.tab.c"
    break;

  case 76: /* key_value_pair: STRING ARROW value  */
#line 598 "phppy.y"
{
    char *key = (yyvsp[-2].strval);  // Asigna la clave
    char *result = malloc(strlen(key) + strlen((yyvsp[0].strval)) + 4);
    sprintf(result, "%s: %s", key, (yyvsp[0].strval));  // Formatea el par clave-valor
    free(key);  // Libera la memoria de la clave
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2095 "phppy.tab.c"
    break;

  case 77: /* key_value_pair: IDENTIFIER ARROW value  */
#line 606 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
    sprintf(result, "\"%s\": %s", (yyvsp[-2].strval), (yyvsp[0].strval));  // Formatea el par clave-valor con identificador como clave
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2105 "phppy.tab.c"
    break;

  case 78: /* value_list: value  */
#line 614 "phppy.y"
{
    (yyval.strval) = (yyvsp[0].strval);  // Asigna un único valor a `$$`
}
#line 2113 "phppy.tab.c"
    break;

  case 79: /* value_list: value_list COMMA value  */
#line 618 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval));  // Concadena valores con coma
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2123 "phppy.tab.c"
    break;

  case 80: /* function_declaration: FUNCTION IDENTIFIER LPAREN parameter_list RPAREN LBRACE statements RBRACE  */
#line 626 "phppy.y"
{
    char *func_name = (yyvsp[-6].strval);  // Asigna el nombre de la función
    char *params = (yyvsp[-4].strval);  // Asigna los parámetros de la función
    char *body = indent_code((yyvsp[-1].strval));  // Indenta el cuerpo de la función
    char *result = malloc(strlen(func_name) + strlen(params) + strlen(body) + 20);
    sprintf(result, "def %s(%s):\n%s", func_name, params, body);  // Formatea la declaración de la función
    (yyval.strval) = result;  // Asigna el resultado formateado
    free(body);  // Libera la memoria del cuerpo de la función
}
#line 2137 "phppy.tab.c"
    break;

  case 81: /* parameter_list: %empty  */
#line 638 "phppy.y"
{
    (yyval.strval) = strdup("");  // Representa una lista de parámetros vacía
}
#line 2145 "phppy.tab.c"
    break;

  case 82: /* parameter_list: VARIABLE  */
#line 642 "phppy.y"
{
    (yyval.strval) = strdup((yyvsp[0].strval) + 1);  // Omite el carácter '$' y representa una variable como parámetro
}
#line 2153 "phppy.tab.c"
    break;

  case 83: /* parameter_list: IDENTIFIER  */
#line 646 "phppy.y"
{
    (yyval.strval) = strdup((yyvsp[0].strval));  // Representa un identificador como parámetro
}
#line 2161 "phppy.tab.c"
    break;

  case 84: /* parameter_list: parameter_list COMMA VARIABLE  */
#line 650 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval) + 1);  // Omite el carácter '$' y concatena variables como parámetros
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2171 "phppy.tab.c"
    break;

  case 85: /* parameter_list: parameter_list COMMA IDENTIFIER  */
#line 656 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval));  // Concatena identificadores como parámetros
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2181 "phppy.tab.c"
    break;

  case 86: /* function_call: IDENTIFIER LPAREN argument_list RPAREN SEMICOLON  */
#line 664 "phppy.y"
{
    char *func_name = (yyvsp[-4].strval);  // Asigna el nombre de la función
    char *args = (yyvsp[-2].strval);  // Asigna los argumentos de la función
    char *result = malloc(strlen(func_name) + strlen(args) + 5);
    sprintf(result, "%s(%s)\n", func_name, args);  // Formatea la llamada a la función
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2193 "phppy.tab.c"
    break;

  case 87: /* argument_list: %empty  */
#line 674 "phppy.y"
{
    (yyval.strval) = strdup("");  // Representa una lista de argumentos vacía
}
#line 2201 "phppy.tab.c"
    break;

  case 88: /* argument_list: value  */
#line 678 "phppy.y"
{
    (yyval.strval) = strdup((yyvsp[0].strval));  // Representa un único valor como argumento
}
#line 2209 "phppy.tab.c"
    break;

  case 89: /* argument_list: VARIABLE  */
#line 682 "phppy.y"
{
    (yyval.strval) = strdup((yyvsp[0].strval) + 1);  // Omite el carácter '$' y representa una variable como argumento
}
#line 2217 "phppy.tab.c"
    break;

  case 90: /* argument_list: IDENTIFIER  */
#line 686 "phppy.y"
{
    (yyval.strval) = strdup((yyvsp[0].strval));  // Representa un identificador como argumento
}
#line 2225 "phppy.tab.c"
    break;

  case 91: /* argument_list: argument_list COMMA value  */
#line 690 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval));  // Concatena valores como argumentos
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2235 "phppy.tab.c"
    break;

  case 92: /* argument_list: argument_list COMMA VARIABLE  */
#line 696 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval) + 1);  // Omite el carácter '$' y concatena variables como argumentos
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2245 "phppy.tab.c"
    break;

  case 93: /* argument_list: argument_list COMMA IDENTIFIER  */
#line 702 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval));  // Concatena identificadores como argumentos
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2255 "phppy.tab.c"
    break;

  case 94: /* array_declaration: ARRAY LPAREN array_items RPAREN  */
#line 710 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 3);
    sprintf(result, "{%s}", (yyvsp[-1].strval));  // Formatea los ítems del array como un diccionario en Python
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2265 "phppy.tab.c"
    break;

  case 95: /* array_declaration: LBRACKET array_items RBRACKET  */
#line 716 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 3);
    sprintf(result, "{%s}", (yyvsp[-1].strval));  // Formatea los ítems del array como un diccionario en Python
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2275 "phppy.tab.c"
    break;

  case 97: /* array_items: array_items COMMA array_item  */
#line 725 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 3);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval));  // Concatena ítems del array con coma
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2285 "phppy.tab.c"
    break;

  case 98: /* array_item: STRING ARROW array_declaration  */
#line 733 "phppy.y"
{
    char *key = strip_quotes((yyvsp[-2].strval));  // Elimina las comillas de la clave
    char *result = malloc(strlen(key) + strlen((yyvsp[0].strval)) + 5);
    sprintf(result, "\"%s\": %s", key, (yyvsp[0].strval));  // Formatea el ítem del array con clave y declaración de array
    free(key);  // Libera la memoria de la clave
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2297 "phppy.tab.c"
    break;

  case 99: /* array_item: STRING ARROW STRING  */
#line 741 "phppy.y"
{
    char *key = strip_quotes((yyvsp[-2].strval));  // Elimina las comillas de la clave
    char *value = strip_quotes((yyvsp[0].strval));  // Elimina las comillas del valor
    char *result = malloc(strlen(key) + strlen(value) + 5);
    sprintf(result, "\"%s\": \"%s\"", key, value);  // Formatea el ítem del array con clave y valor
    free(key);  // Libera la memoria de la clave
    free(value);  // Libera la memoria del valor
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2311 "phppy.tab.c"
    break;

  case 100: /* array_item: STRING ARROW INTEGER  */
#line 751 "phppy.y"
{
    char *key = strip_quotes((yyvsp[-2].strval));  // Elimina las comillas de la clave
    char *result = malloc(strlen(key) + strlen((yyvsp[0].strval)) + 5);
    sprintf(result, "\"%s\": %s", key, (yyvsp[0].strval));  // Formatea el ítem del array con clave y entero
    free(key);  // Libera la memoria de la clave
    (yyval.strval) = result;  // Asigna el resultado formateado
}
#line 2323 "phppy.tab.c"
    break;


#line 2327 "phppy.tab.c"

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

#line 760 "phppy.y"


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
