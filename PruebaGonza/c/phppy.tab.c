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

#line 210 "phppy.tab.c"

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
  YYSYMBOL_VARIABLE = 37,                  /* VARIABLE  */
  YYSYMBOL_INTEGER = 38,                   /* INTEGER  */
  YYSYMBOL_FLOAT = 39,                     /* FLOAT  */
  YYSYMBOL_CHAR = 40,                      /* CHAR  */
  YYSYMBOL_STRING = 41,                    /* STRING  */
  YYSYMBOL_BOOL = 42,                      /* BOOL  */
  YYSYMBOL_IDENTIFIER = 43,                /* IDENTIFIER  */
  YYSYMBOL_YYACCEPT = 44,                  /* $accept  */
  YYSYMBOL_program = 45,                   /* program  */
  YYSYMBOL_statements = 46,                /* statements  */
  YYSYMBOL_statement = 47,                 /* statement  */
  YYSYMBOL_variable_declaration = 48,      /* variable_declaration  */
  YYSYMBOL_variable_assignment = 49,       /* variable_assignment  */
  YYSYMBOL_echo_statement = 50,            /* echo_statement  */
  YYSYMBOL_constant_declaration = 51,      /* constant_declaration  */
  YYSYMBOL_if_statement = 52,              /* if_statement  */
  YYSYMBOL_elseif_clauses = 53,            /* elseif_clauses  */
  YYSYMBOL_elseif_clause = 54,             /* elseif_clause  */
  YYSYMBOL_else_clause = 55,               /* else_clause  */
  YYSYMBOL_while_statement = 56,           /* while_statement  */
  YYSYMBOL_condicion = 57,                 /* condicion  */
  YYSYMBOL_type_check_func = 58,           /* type_check_func  */
  YYSYMBOL_value = 59,                     /* value  */
  YYSYMBOL_array_value = 60,               /* array_value  */
  YYSYMBOL_key_value_list = 61,            /* key_value_list  */
  YYSYMBOL_key_value_pair = 62,            /* key_value_pair  */
  YYSYMBOL_value_list = 63,                /* value_list  */
  YYSYMBOL_function_declaration = 64,      /* function_declaration  */
  YYSYMBOL_parameter_list = 65,            /* parameter_list  */
  YYSYMBOL_function_call = 66,             /* function_call  */
  YYSYMBOL_argument_list = 67,             /* argument_list  */
  YYSYMBOL_array_declaration = 68,         /* array_declaration  */
  YYSYMBOL_array_items = 69,               /* array_items  */
  YYSYMBOL_array_item = 70                 /* array_item  */
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
#define YYFINAL  21
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   506

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  95
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  206

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   298


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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   151,   151,   157,   158,   166,   172,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   192,   201,   212,   220,
     227,   235,   244,   250,   257,   268,   291,   311,   319,   327,
     335,   345,   351,   359,   370,   371,   379,   389,   399,   409,
     420,   426,   438,   443,   448,   453,   458,   463,   468,   473,
     478,   483,   491,   491,   491,   491,   491,   494,   495,   496,
     497,   498,   499,   500,   506,   516,   520,   526,   532,   540,
     544,   552,   560,   568,   572,   580,   593,   596,   600,   604,
     610,   618,   629,   632,   633,   637,   641,   647,   653,   661,
     667,   675,   676,   684,   692,   702
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
  "INCREMENT", "RETURN", "FUNCTION", "VARIABLE", "INTEGER", "FLOAT",
  "CHAR", "STRING", "BOOL", "IDENTIFIER", "$accept", "program",
  "statements", "statement", "variable_declaration", "variable_assignment",
  "echo_statement", "constant_declaration", "if_statement",
  "elseif_clauses", "elseif_clause", "else_clause", "while_statement",
  "condicion", "type_check_func", "value", "array_value", "key_value_list",
  "key_value_pair", "value_list", "function_declaration", "parameter_list",
  "function_call", "argument_list", "array_declaration", "array_items",
  "array_item", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-34)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      46,   270,    11,     3,    27,    39,   392,    68,    18,    10,
      82,     5,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,   -34,    50,   361,    84,    25,   -34,   -34,   -34,
     -34,   -34,    61,   -34,   398,    85,   -34,   295,    90,   325,
     -34,   404,   -34,    86,   -34,   -34,   -34,   -34,   -34,     4,
      87,    89,    -6,   306,   -34,   413,    94,   -34,    91,   -11,
     -34,    98,    66,     0,   106,   107,   -34,    96,   -34,   -34,
      44,     2,   115,   434,   443,   449,   455,   464,   112,    95,
     434,   434,   -34,    96,   103,   111,   -34,    45,   117,    51,
     105,   118,   -34,     7,   -34,   -34,    53,   313,   113,    -8,
     -34,   -34,   -34,   -34,   136,   344,   -34,   -34,   133,    96,
     -34,    96,   -34,    96,   -34,    96,   -34,   232,   134,   -34,
     -34,   434,   434,   -34,   -14,   -34,   -34,   434,   -34,   -34,
     255,   247,   138,     8,   129,    72,    67,    66,   -34,   -34,
      96,   -34,   -34,   145,   126,    32,   143,   -34,   -34,   103,
     -34,   -34,   -34,    78,   153,   102,   270,   -34,   -34,   383,
     -34,   151,   -34,   -34,   -34,   -34,   -34,   150,    58,   152,
     -34,   -34,   156,   146,   -34,   -34,    66,   270,   155,   157,
      62,   -34,   -34,   139,   -34,   -34,   173,   398,   288,   158,
     -34,   -34,   125,   -34,   161,   -34,   191,   270,   166,   163,
     -34,   164,   270,   -34,   214,   -34
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     3,     8,     7,    12,     9,    10,    11,    13,
      14,     1,    15,     0,     0,     0,     0,    57,    58,    59,
      60,    61,     0,    62,     0,     0,    16,     0,     0,    82,
       2,     0,     4,     0,    52,    53,    54,    55,    56,     0,
       0,     0,     0,     0,    23,     0,     0,    22,     0,    76,
      19,     0,     0,     0,     0,     0,    20,    84,    85,    83,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    65,     0,    60,     0,    73,     0,    69,     0,
       0,     0,    24,     0,    77,    78,     0,     0,     0,     0,
      91,    18,    17,    21,     0,     0,     6,     5,     0,    42,
      45,    43,    46,    44,    47,    48,    49,     0,     0,    50,
      51,     0,     0,    67,     0,    68,    66,     0,    64,    63,
       0,     0,     0,     0,    60,     0,     0,     0,    90,    81,
      87,    88,    86,     0,    31,     0,     0,    71,    72,     0,
      70,    74,    40,     0,     0,     0,     0,    79,    80,     0,
      89,     0,    95,    94,    93,    92,    25,     0,    30,     0,
      38,    41,     0,     0,    57,    60,     0,     0,     0,     0,
      28,    34,    29,     0,    39,    75,     0,     0,     0,     0,
      35,    27,     0,    33,     0,    32,     0,     0,     0,     0,
      37,     0,     0,    26,     0,    36
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -34,   -34,    -1,    -9,   -34,   -34,   -34,   -34,   -34,   -34,
       6,    13,   -34,   -33,   -34,    -3,   -34,   -34,    55,   -34,
     -34,   -34,   -34,   -34,   148,   128,    54
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,   196,    12,    13,    14,    15,    16,    17,   180,
     181,   182,    18,    50,    51,    52,    33,    87,    88,    89,
      19,    96,    20,    70,   164,   135,   100
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      11,    58,    42,    32,   137,   101,     3,   106,    22,    40,
      80,    21,     4,    81,   138,    36,    37,   130,    74,    75,
      76,    55,    77,    55,   131,    55,    94,   149,     5,    85,
      54,     6,    95,     3,    64,    23,    69,     7,    72,     4,
      41,     8,     9,   168,    38,   157,    55,    24,    10,     1,
      86,   158,    91,   104,   123,     5,   105,   124,     6,    56,
     126,    35,   132,   127,     7,   133,    57,    41,     8,     9,
     108,   110,   112,   114,   116,    10,    34,   119,   120,     3,
     161,   160,   178,   179,   137,     4,   178,   189,    62,   170,
      39,    43,    53,    59,    86,    66,    78,    79,    73,    92,
      93,     5,   142,     3,     6,   162,    97,    98,   163,     4,
       7,   102,   103,    41,     8,     9,   145,    55,   147,   148,
     107,    10,   117,   121,   151,     5,   125,   128,     6,   153,
     155,   122,   118,   136,     7,   172,    42,    41,     8,     9,
     129,   139,   143,   146,    42,    10,    42,     3,   156,   159,
     166,   167,   169,     4,   194,   173,   147,   185,   171,   176,
     177,   184,   183,   187,    42,   192,   198,   188,   197,     5,
     199,   201,     6,   202,     3,   203,   186,    42,     7,   150,
       4,    41,     8,     9,   193,    65,   190,    42,     0,    10,
      99,   165,     3,   191,     0,    42,     5,     0,     4,     6,
       0,   204,   200,     0,     0,     7,     0,     0,    41,     8,
       9,     0,     0,     0,     5,     3,    10,     6,     0,     0,
       0,     4,     0,     7,     0,   205,    41,     8,     9,     0,
       0,     0,     0,     3,    10,     0,     0,     5,     0,     4,
       6,     0,     0,   144,     0,     0,     7,     0,     3,    41,
       8,     9,     0,     0,     4,     5,     3,    10,     6,     0,
       0,     0,     4,     0,     7,     0,   152,     0,     8,     9,
       5,     3,     0,     6,     0,    10,     0,     4,     5,     7,
     154,     6,     0,     8,     9,     0,     0,     7,     0,     3,
      10,     8,     9,     5,     0,     4,     6,     0,    10,   195,
      60,     0,     7,     0,     0,     0,     8,     9,    61,     0,
       0,     5,     0,    10,     6,    82,    62,     0,     0,    25,
       7,     0,    82,     0,     8,     9,    25,     0,     0,     0,
       0,    10,    63,    27,    28,    29,    30,    31,    25,     0,
       0,     0,     0,    83,    27,    28,    29,    84,    31,    85,
      83,    27,    28,    29,   134,    31,    85,    25,     0,     0,
       0,     0,    67,    27,    28,    29,    30,    31,    68,     0,
       0,     0,     0,     0,    25,     0,     0,     0,     0,     0,
       0,   140,    27,    28,    29,    30,    31,   141,    44,    45,
      46,    47,    48,     0,     0,     0,    61,     0,    49,    27,
      28,    29,    30,    31,    62,    25,     0,     0,     0,     0,
       0,    25,     0,     0,     0,     0,     0,    25,     0,     0,
      83,   174,    28,    29,   175,    31,    25,     0,     0,    26,
      27,    28,    29,    30,    31,    49,    27,    28,    29,    30,
      31,    71,    27,    28,    29,    30,    31,    25,     0,     0,
      83,    27,    28,    29,    90,    31,    25,     0,     0,     0,
       0,     0,    25,     0,     0,     0,     0,     0,    25,     0,
       0,    83,    27,    28,    29,    30,    31,    25,     0,     0,
     109,    27,    28,    29,    30,    31,   111,    27,    28,    29,
      30,    31,   113,    27,    28,    29,    30,    31,     0,     0,
       0,   115,    27,    28,    29,    30,    31
};

static const yytype_int16 yycheck[] =
{
       1,    34,    11,     6,    12,     5,     1,     5,     5,     4,
      16,     0,     7,    19,    22,     5,     6,    10,    14,    15,
      16,    21,    18,    21,    17,    21,    37,    41,    23,    43,
       5,    26,    43,     1,    37,     8,    39,    32,    41,     7,
      35,    36,    37,    11,    34,    37,    21,     8,    43,     3,
      53,    43,    55,     9,     9,    23,    12,    12,    26,    34,
       9,    43,     9,    12,    32,    12,     5,    35,    36,    37,
      73,    74,    75,    76,    77,    43,     8,    80,    81,     1,
      13,     9,    24,    25,    12,     7,    24,    25,    21,    11,
       8,    41,     8,     8,    97,     5,     9,     8,    12,     5,
       9,    23,   105,     1,    26,    38,     8,    41,    41,     7,
      32,     5,     5,    35,    36,    37,   117,    21,   121,   122,
       5,    43,    10,    20,   127,    23,     9,    22,    26,   130,
     131,    20,    37,    20,    32,    33,   145,    35,    36,    37,
      22,     5,     9,     9,   153,    43,   155,     1,    10,    20,
       5,    25,     9,     7,   187,   156,   159,    11,     5,     8,
      10,     5,    10,     8,   173,    26,    41,    10,    10,    23,
       9,     5,    26,    10,     1,    11,   177,   186,    32,   124,
       7,    35,    36,    37,    11,    37,   180,   196,    -1,    43,
      62,   137,     1,   180,    -1,   204,    23,    -1,     7,    26,
      -1,   202,    11,    -1,    -1,    32,    -1,    -1,    35,    36,
      37,    -1,    -1,    -1,    23,     1,    43,    26,    -1,    -1,
      -1,     7,    -1,    32,    -1,    11,    35,    36,    37,    -1,
      -1,    -1,    -1,     1,    43,    -1,    -1,    23,    -1,     7,
      26,    -1,    -1,    11,    -1,    -1,    32,    -1,     1,    35,
      36,    37,    -1,    -1,     7,    23,     1,    43,    26,    -1,
      -1,    -1,     7,    -1,    32,    -1,    11,    -1,    36,    37,
      23,     1,    -1,    26,    -1,    43,    -1,     7,    23,    32,
      33,    26,    -1,    36,    37,    -1,    -1,    32,    -1,     1,
      43,    36,    37,    23,    -1,     7,    26,    -1,    43,    11,
       5,    -1,    32,    -1,    -1,    -1,    36,    37,    13,    -1,
      -1,    23,    -1,    43,    26,     9,    21,    -1,    -1,    13,
      32,    -1,     9,    -1,    36,    37,    13,    -1,    -1,    -1,
      -1,    43,    37,    38,    39,    40,    41,    42,    13,    -1,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    42,    43,
      37,    38,    39,    40,    41,    42,    43,    13,    -1,    -1,
      -1,    -1,    37,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    13,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    38,    39,    40,    41,    42,    43,    27,    28,
      29,    30,    31,    -1,    -1,    -1,    13,    -1,    37,    38,
      39,    40,    41,    42,    21,    13,    -1,    -1,    -1,    -1,
      -1,    13,    -1,    -1,    -1,    -1,    -1,    13,    -1,    -1,
      37,    38,    39,    40,    41,    42,    13,    -1,    -1,    37,
      38,    39,    40,    41,    42,    37,    38,    39,    40,    41,
      42,    37,    38,    39,    40,    41,    42,    13,    -1,    -1,
      37,    38,    39,    40,    41,    42,    13,    -1,    -1,    -1,
      -1,    -1,    13,    -1,    -1,    -1,    -1,    -1,    13,    -1,
      -1,    37,    38,    39,    40,    41,    42,    13,    -1,    -1,
      37,    38,    39,    40,    41,    42,    37,    38,    39,    40,
      41,    42,    37,    38,    39,    40,    41,    42,    -1,    -1,
      -1,    37,    38,    39,    40,    41,    42
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    45,     1,     7,    23,    26,    32,    36,    37,
      43,    46,    47,    48,    49,    50,    51,    52,    56,    64,
      66,     0,     5,     8,     8,    13,    37,    38,    39,    40,
      41,    42,    59,    60,     8,    43,     5,     6,    34,     8,
       4,    35,    47,    41,    27,    28,    29,    30,    31,    37,
      57,    58,    59,     8,     5,    21,    34,     5,    57,     8,
       5,    13,    21,    37,    59,    68,     5,    37,    43,    59,
      67,    37,    59,    12,    14,    15,    16,    18,     9,     8,
      16,    19,     9,    37,    41,    43,    59,    61,    62,    63,
      41,    59,     5,     9,    37,    43,    65,     8,    41,    69,
      70,     5,     5,     5,     9,    12,     5,     5,    59,    37,
      59,    37,    59,    37,    59,    37,    59,    10,    37,    59,
      59,    20,    20,     9,    12,     9,     9,    12,    22,    22,
      10,    17,     9,    12,    41,    69,    20,    12,    22,     5,
      37,    43,    59,     9,    11,    46,     9,    59,    59,    41,
      62,    59,    11,    46,    33,    46,    10,    37,    43,    20,
       9,    13,    38,    41,    68,    70,     5,    25,    11,     9,
      11,     5,    33,    46,    38,    41,     8,    10,    24,    25,
      53,    54,    55,    10,     5,    11,    46,     8,    10,    25,
      54,    55,    26,    11,    57,    11,    46,    10,    41,     9,
      11,     5,    10,    11,    46,    11
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    44,    45,    46,    46,    46,    46,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    48,    49,    49,    49,
      49,    49,    50,    50,    50,    51,    52,    52,    52,    52,
      52,    52,    52,    52,    53,    53,    54,    55,    56,    56,
      56,    56,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    58,    58,    58,    58,    58,    59,    59,    59,
      59,    59,    59,    59,    59,    60,    60,    60,    60,    61,
      61,    62,    62,    63,    63,    64,    65,    65,    65,    65,
      65,    66,    67,    67,    67,    67,    67,    67,    67,    68,
      68,    69,    69,    70,    70,    70
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     1,     2,     4,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     4,     4,     3,
       3,     4,     3,     3,     4,     7,    12,     9,     8,     8,
       7,     6,    10,    10,     1,     2,     7,     4,     7,     8,
       6,     7,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     4,     3,     4,     4,     4,     1,
       3,     3,     3,     1,     3,     8,     0,     1,     1,     3,
       3,     5,     0,     1,     1,     1,     3,     3,     3,     4,
       3,     1,     3,     3,     3,     3
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
#line 152 "phppy.y"
{
    output = (yyvsp[-1].strval);
}
#line 1462 "phppy.tab.c"
    break;

  case 4: /* statements: statements statement  */
#line 159 "phppy.y"
    {
        //printf("DEBUG: concatenating statements: '%s' and '%s'\n", $1, $2);
        char *result = malloc(strlen((yyvsp[-1].strval)) + strlen((yyvsp[0].strval)) + 1);
        sprintf(result, "%s%s", (yyvsp[-1].strval), (yyvsp[0].strval));
        (yyval.strval) = result;
        //printf("DEBUG: result of concatenation: '%s'\n", result);
    }
#line 1474 "phppy.tab.c"
    break;

  case 5: /* statements: statements RETURN value SEMICOLON  */
#line 167 "phppy.y"
    {
        char *result = malloc(strlen((yyvsp[-3].strval)) + strlen((yyvsp[-1].strval)) + 10);
        sprintf(result, "%sreturn %s\n", (yyvsp[-3].strval), (yyvsp[-1].strval));
        (yyval.strval) = result;
    }
#line 1484 "phppy.tab.c"
    break;

  case 6: /* statements: statements RETURN VARIABLE SEMICOLON  */
#line 173 "phppy.y"
    {
        char *result = malloc(strlen((yyvsp[-3].strval)) + strlen((yyvsp[-1].strval)) + 10);
        sprintf(result, "%sreturn %s\n", (yyvsp[-3].strval), (yyvsp[-1].strval) + 1);  // Skip the '$' character
        (yyval.strval) = result;
    }
#line 1494 "phppy.tab.c"
    break;

  case 15: /* statement: error SEMICOLON  */
#line 189 "phppy.y"
                      { yyerrok; }
#line 1500 "phppy.tab.c"
    break;

  case 16: /* variable_declaration: VARIABLE SEMICOLON  */
#line 193 "phppy.y"
{
    char *var_name = (yyvsp[-1].strval) + 1;  // Skip the '$' character
    char *result = malloc(strlen(var_name) + 10);
    sprintf(result, "%s = None\n", var_name);
    (yyval.strval) = result;
}
#line 1511 "phppy.tab.c"
    break;

  case 17: /* variable_assignment: VARIABLE ASSIGN value SEMICOLON  */
#line 202 "phppy.y"
{
    char *var_name = (yyvsp[-3].strval) + 1;  // Skip the '$' character
    char *result = malloc(strlen(var_name) + strlen((yyvsp[-1].strval)) + 5);
    if ((yyvsp[-1].strval) && strlen((yyvsp[-1].strval)) > 0) {
        sprintf(result, "%s = %s\n", var_name, (yyvsp[-1].strval));
    } else {
        sprintf(result, "%s = None\n", var_name);
    }
    (yyval.strval) = result;
}
#line 1526 "phppy.tab.c"
    break;

  case 18: /* variable_assignment: VARIABLE ASSIGN VARIABLE SEMICOLON  */
#line 213 "phppy.y"
{
    char *var_name = (yyvsp[-3].strval) + 1;  // Skip the '$' character
    char *value_name = (yyvsp[-1].strval) + 1;  // Skip the '$' character
    char *result = malloc(strlen(var_name) + strlen(value_name) + 5);
    sprintf(result, "%s = %s\n", var_name, value_name);
    (yyval.strval) = result;
}
#line 1538 "phppy.tab.c"
    break;

  case 19: /* variable_assignment: VARIABLE ASSIGN SEMICOLON  */
#line 221 "phppy.y"
{
    char *var_name = (yyvsp[-2].strval) + 1;  // Skip the '$' character
    char *result = malloc(strlen(var_name) + 10);
    sprintf(result, "%s = None\n", var_name);
    (yyval.strval) = result;
}
#line 1549 "phppy.tab.c"
    break;

  case 20: /* variable_assignment: VARIABLE INCREMENT SEMICOLON  */
#line 228 "phppy.y"
{
    char *var_name = (yyvsp[-2].strval) + 1;  // Skip the '$' character
    //printf("DEBUG: variable_increment - var_name = '%s'\n", var_name);
    char *result = malloc(strlen(var_name) + 7); // Tamaño necesario para " += 1\n" y terminador nulo
    sprintf(result, "%s += 1\n", var_name);
    (yyval.strval) = result;
}
#line 1561 "phppy.tab.c"
    break;

  case 21: /* variable_assignment: VARIABLE ASSIGN array_declaration SEMICOLON  */
#line 236 "phppy.y"
{
    char *var_name = (yyvsp[-3].strval) + 1;  // Skip the '$' character
    char *result = malloc(strlen(var_name) + strlen((yyvsp[-1].strval)) + 5);
    sprintf(result, "%s = %s\n", var_name, (yyvsp[-1].strval));
    (yyval.strval) = result;
}
#line 1572 "phppy.tab.c"
    break;

  case 22: /* echo_statement: ECHO_TOKEN value SEMICOLON  */
#line 245 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 8);
    sprintf(result, "print(%s)\n", (yyvsp[-1].strval));
    (yyval.strval) = result;
}
#line 1582 "phppy.tab.c"
    break;

  case 23: /* echo_statement: ECHO_TOKEN VARIABLE SEMICOLON  */
#line 251 "phppy.y"
{
    char *var_name = (yyvsp[-1].strval) + 1;  // Skip the '$' character
    char *result = malloc(strlen(var_name) + 10);
    sprintf(result, "print(%s)\n", var_name);
    (yyval.strval) = result;
}
#line 1593 "phppy.tab.c"
    break;

  case 24: /* echo_statement: ECHO_TOKEN VARIABLE INCREMENT SEMICOLON  */
#line 258 "phppy.y"
{
    char *var_name = (yyvsp[-2].strval) + 1;  // Skip the '$' character
    char *result = malloc(strlen(var_name) + 10);
    sprintf(result, "print(%s)\n%s += 1\n", var_name, var_name);
    (yyval.strval) = result;
}
#line 1604 "phppy.tab.c"
    break;

  case 25: /* constant_declaration: DEFINE LPAREN STRING COMMA value RPAREN SEMICOLON  */
#line 269 "phppy.y"
{
    char* constant_name = strip_quotes((yyvsp[-4].strval));
    char *type;
    if (strchr((yyvsp[-2].strval), '"') != NULL) {
        type = "str";
    } else if (strchr((yyvsp[-2].strval), '.') != NULL) {
        type = "float";
    } else if (strcmp((yyvsp[-2].strval), "True") == 0 || strcmp((yyvsp[-2].strval), "False") == 0) {
        type = "bool";
    } else if ((yyvsp[-2].strval)[0] == '[') {
        type = "List[Any]";
    } else {
        type = "int";
    }
    add_symbol(constant_name, type);
    char *result = malloc(strlen(constant_name) + strlen(type) + strlen((yyvsp[-2].strval)) + 10);
    sprintf(result, "%s: %s = %s\n", constant_name, type, (yyvsp[-2].strval));
    free(constant_name);
    (yyval.strval) = result;
}
#line 1629 "phppy.tab.c"
    break;

  case 26: /* if_statement: IF LPAREN type_check_func LPAREN VARIABLE RPAREN RPAREN LBRACE ECHO_TOKEN STRING SEMICOLON RBRACE  */
#line 292 "phppy.y"
{
    char *type = get_symbol_type((yyvsp[-7].strval) + 1);  // Skip the '$' character
    char *py_type;
    if (strcmp(type, "int") == 0) py_type = "int";
    else if (strcmp(type, "str") == 0) py_type = "str";
    else if (strcmp(type, "list") == 0) py_type = "list";
    else if (strcmp(type, "float") == 0) py_type = "float";
    else if (strcmp(type, "bool") == 0) py_type = "bool";
    else py_type = "object";
    
    char *unquoted = strip_quotes((yyvsp[-2].strval));
    char *message = replace_dollar(unquoted);
    // Remove newlines and format the print statement
    char *formatted_message = remove_newlines(message);
    printf("if isinstance(%s, %s):\n    print(%s, \"\\%s\")\n", (yyvsp[-7].strval) + 1, py_type, (yyvsp[-7].strval) + 1, formatted_message);
    free(unquoted);
    free(message);
    free(formatted_message);
}
#line 1653 "phppy.tab.c"
    break;

  case 27: /* if_statement: IF LPAREN condicion RPAREN LBRACE statements RBRACE elseif_clauses else_clause  */
#line 312 "phppy.y"
{
    char *if_part = indent_code((yyvsp[-3].strval));
    char *result = malloc(strlen((yyvsp[-6].strval)) + strlen(if_part) + strlen((yyvsp[-1].strval)) + strlen((yyvsp[0].strval)) + 10);
    sprintf(result, "if (%s):\n%s%s%s", (yyvsp[-6].strval), if_part, (yyvsp[-1].strval), (yyvsp[0].strval));
    (yyval.strval) = result;
    free(if_part);
}
#line 1665 "phppy.tab.c"
    break;

  case 28: /* if_statement: IF LPAREN condicion RPAREN LBRACE statements RBRACE elseif_clauses  */
#line 320 "phppy.y"
{
    char *if_part = indent_code((yyvsp[-2].strval));
    char *result = malloc(strlen((yyvsp[-5].strval)) + strlen(if_part) + strlen((yyvsp[0].strval)) + 10);
    sprintf(result, "if (%s):\n%s%s", (yyvsp[-5].strval), if_part, (yyvsp[0].strval));
    (yyval.strval) = result;
    free(if_part);
}
#line 1677 "phppy.tab.c"
    break;

  case 29: /* if_statement: IF LPAREN condicion RPAREN LBRACE statements RBRACE else_clause  */
#line 328 "phppy.y"
{
    char *if_part = indent_code((yyvsp[-2].strval));
    char *result = malloc(strlen((yyvsp[-5].strval)) + strlen(if_part) + strlen((yyvsp[0].strval)) + 20);
    sprintf(result, "if (%s):\n%s%s", (yyvsp[-5].strval), if_part, (yyvsp[0].strval));
    (yyval.strval) = result;
    free(if_part);
}
#line 1689 "phppy.tab.c"
    break;

  case 30: /* if_statement: IF LPAREN condicion RPAREN LBRACE statements RBRACE  */
#line 336 "phppy.y"
{
    //printf("DEBUG: if_statement - statements = '%s'\n", $6);
    char *if_part = indent_code((yyvsp[-1].strval));
    char *result = malloc(strlen((yyvsp[-4].strval)) + strlen(if_part) + 10);
    sprintf(result, "if (%s):\n%s", (yyvsp[-4].strval), if_part);
    (yyval.strval) = result;
    free(if_part);
}
#line 1702 "phppy.tab.c"
    break;

  case 31: /* if_statement: IF LPAREN condicion RPAREN LBRACE RBRACE  */
#line 346 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-3].strval)) + 15);
    sprintf(result, "if (%s):\n    pass\n", (yyvsp[-3].strval));
    (yyval.strval) = result;
}
#line 1712 "phppy.tab.c"
    break;

  case 32: /* if_statement: IF LPAREN condicion RPAREN LBRACE statements RBRACE ELSE LBRACE RBRACE  */
#line 352 "phppy.y"
{
    char *indented_statements_if = indent_code((yyvsp[-4].strval));
    char *result = malloc(strlen((yyvsp[-7].strval)) + strlen(indented_statements_if) + 20);
    sprintf(result, "if (%s):\n%selse:\n    pass\n", (yyvsp[-7].strval), indented_statements_if);
    (yyval.strval) = result;
    free(indented_statements_if);
}
#line 1724 "phppy.tab.c"
    break;

  case 33: /* if_statement: IF LPAREN condicion RPAREN LBRACE RBRACE ELSE LBRACE statements RBRACE  */
#line 360 "phppy.y"
{
    char *indented_statements_else = indent_code((yyvsp[-1].strval));
    char *result = malloc(strlen((yyvsp[-7].strval)) + strlen(indented_statements_else) + 20);
    sprintf(result, "if (%s):\n    pass\nelse:\n%s", (yyvsp[-7].strval), indented_statements_else);
    (yyval.strval) = result;
    free(indented_statements_else);
}
#line 1736 "phppy.tab.c"
    break;

  case 35: /* elseif_clauses: elseif_clauses elseif_clause  */
#line 372 "phppy.y"
    {
        char *result = malloc(strlen((yyvsp[-1].strval)) + strlen((yyvsp[0].strval)) + 1);
        sprintf(result, "%s%s", (yyvsp[-1].strval), (yyvsp[0].strval));
        (yyval.strval) = result;
    }
#line 1746 "phppy.tab.c"
    break;

  case 36: /* elseif_clause: ELSEIF LPAREN condicion RPAREN LBRACE statements RBRACE  */
#line 380 "phppy.y"
{
    char *elseif_part = indent_code((yyvsp[-1].strval));
    char *result = malloc(strlen((yyvsp[-4].strval)) + strlen(elseif_part) + 10);
    sprintf(result, "elif (%s):\n%s", (yyvsp[-4].strval), elseif_part);
    (yyval.strval) = result;
    free(elseif_part);
}
#line 1758 "phppy.tab.c"
    break;

  case 37: /* else_clause: ELSE LBRACE statements RBRACE  */
#line 390 "phppy.y"
{
    char *else_part = indent_code((yyvsp[-1].strval));
    char *result = malloc(strlen(else_part) + 20);
    sprintf(result, "else:\n%s", else_part);
    (yyval.strval) = result;
    free(else_part);
}
#line 1770 "phppy.tab.c"
    break;

  case 38: /* while_statement: WHILE LPAREN condicion RPAREN LBRACE statements RBRACE  */
#line 400 "phppy.y"
{
    //printf("DEBUG: condicion = '%s'\n", $3);
    //printf("DEBUG: statements = '%s'\n", $6);
    char *indented_statements = indent_code((yyvsp[-1].strval));
    char *result = malloc(strlen((yyvsp[-4].strval)) + strlen(indented_statements) + 15);
    sprintf(result, "while (%s):\n%s", (yyvsp[-4].strval), indented_statements);
    (yyval.strval) = result;
    free(indented_statements);
}
#line 1784 "phppy.tab.c"
    break;

  case 39: /* while_statement: WHILE LPAREN condicion RPAREN COLON statements ENDWHILE SEMICOLON  */
#line 410 "phppy.y"
{
    //printf("DEBUG: condicion = '%s'\n", $3);
    //printf("DEBUG: statements = '%s'\n", $6);
    char *indented_statements = indent_code((yyvsp[-2].strval));
    char *result = malloc(strlen((yyvsp[-5].strval)) + strlen(indented_statements) + 15);
    sprintf(result, "while (%s):\n%s", (yyvsp[-5].strval), indented_statements);
    (yyval.strval) = result;
    free(indented_statements);
}
#line 1798 "phppy.tab.c"
    break;

  case 40: /* while_statement: WHILE LPAREN condicion RPAREN LBRACE RBRACE  */
#line 421 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-3].strval)) + 15);
    sprintf(result, "while (%s):\n    pass\n", (yyvsp[-3].strval));
    (yyval.strval) = result;
}
#line 1808 "phppy.tab.c"
    break;

  case 41: /* while_statement: WHILE LPAREN condicion RPAREN COLON ENDWHILE SEMICOLON  */
#line 427 "phppy.y"
{
    printf("DEBUG: while_statement - condicion = '%s' (empty block)\n", (yyvsp[-4].strval));
    char *result = malloc(strlen((yyvsp[-4].strval)) + 15);
    sprintf(result, "while (%s):\n    pass\n", (yyvsp[-4].strval));
    (yyval.strval) = result;
}
#line 1819 "phppy.tab.c"
    break;

  case 42: /* condicion: VARIABLE GT VARIABLE  */
#line 439 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4); // 4: para espacio, operador, espacio, y terminador nulo
        sprintf((yyval.strval), "%s > %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval) + 1); // Omitimos el carácter '$'
    }
#line 1828 "phppy.tab.c"
    break;

  case 43: /* condicion: VARIABLE LT VARIABLE  */
#line 444 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
        sprintf((yyval.strval), "%s < %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval) + 1); // Omitimos el carácter '$'
    }
#line 1837 "phppy.tab.c"
    break;

  case 44: /* condicion: VARIABLE EQ VARIABLE  */
#line 449 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
        sprintf((yyval.strval), "%s == %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval) + 1); // En Python se usa '==' para la igualdad
    }
#line 1846 "phppy.tab.c"
    break;

  case 45: /* condicion: VARIABLE GT value  */
#line 454 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4); // 4: para espacio, operador, espacio, y terminador nulo
        sprintf((yyval.strval), "%s > %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval)); // Omitimos el carácter '$'
    }
#line 1855 "phppy.tab.c"
    break;

  case 46: /* condicion: VARIABLE LT value  */
#line 459 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
        sprintf((yyval.strval), "%s < %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval)); // Omitimos el carácter '$'
    }
#line 1864 "phppy.tab.c"
    break;

  case 47: /* condicion: VARIABLE EQ value  */
#line 464 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
        sprintf((yyval.strval), "%s == %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval)); // En Python se usa '==' para la igualdad
    }
#line 1873 "phppy.tab.c"
    break;

  case 48: /* condicion: VARIABLE LE VARIABLE  */
#line 469 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 5);
        sprintf((yyval.strval), "%s <= %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval) + 1); // Omitimos el carácter '$'
    }
#line 1882 "phppy.tab.c"
    break;

  case 49: /* condicion: VARIABLE LE value  */
#line 474 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 5);
        sprintf((yyval.strval), "%s <= %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval)); // Omitimos el carácter '$'
    }
#line 1891 "phppy.tab.c"
    break;

  case 50: /* condicion: value EQ value  */
#line 479 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
        sprintf((yyval.strval), "%s == %s", (yyvsp[-2].strval), (yyvsp[0].strval)); // En Python se usa '==' para la igualdad
    }
#line 1900 "phppy.tab.c"
    break;

  case 51: /* condicion: value NE value  */
#line 484 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 5);
        sprintf((yyval.strval), "%s != %s", (yyvsp[-2].strval), (yyvsp[0].strval)); // En Python se usa '!=' para desigualdad
    }
#line 1909 "phppy.tab.c"
    break;

  case 57: /* value: INTEGER  */
#line 494 "phppy.y"
               { (yyval.strval) = (yyvsp[0].strval); }
#line 1915 "phppy.tab.c"
    break;

  case 58: /* value: FLOAT  */
#line 495 "phppy.y"
            { (yyval.strval) = (yyvsp[0].strval); }
#line 1921 "phppy.tab.c"
    break;

  case 59: /* value: CHAR  */
#line 496 "phppy.y"
           { (yyval.strval) = (yyvsp[0].strval); }
#line 1927 "phppy.tab.c"
    break;

  case 60: /* value: STRING  */
#line 497 "phppy.y"
             { (yyval.strval) = (yyvsp[0].strval); }
#line 1933 "phppy.tab.c"
    break;

  case 61: /* value: BOOL  */
#line 498 "phppy.y"
           { (yyval.strval) = (yyvsp[0].strval); }
#line 1939 "phppy.tab.c"
    break;

  case 62: /* value: array_value  */
#line 499 "phppy.y"
                  { (yyval.strval) = (yyvsp[0].strval); }
#line 1945 "phppy.tab.c"
    break;

  case 63: /* value: VARIABLE LBRACKET value RBRACKET  */
#line 501 "phppy.y"
    {
        char *result = malloc(strlen((yyvsp[-3].strval)) + strlen((yyvsp[-1].strval)) + 4);
        sprintf(result, "%s[%s]", (yyvsp[-3].strval) + 1, (yyvsp[-1].strval));  // Skip the '$' character
        (yyval.strval) = result;
    }
#line 1955 "phppy.tab.c"
    break;

  case 64: /* value: VARIABLE LBRACKET STRING RBRACKET  */
#line 507 "phppy.y"
    {
        char *key = strip_quotes((yyvsp[-1].strval));
        char *result = malloc(strlen((yyvsp[-3].strval)) + strlen(key) + 4);
        sprintf(result, "%s[%s]", (yyvsp[-3].strval) + 1, key);  // Skip the '$' character
        free(key);
        (yyval.strval) = result;
    }
#line 1967 "phppy.tab.c"
    break;

  case 65: /* array_value: ARRAY LPAREN RPAREN  */
#line 517 "phppy.y"
{
    (yyval.strval) = strdup("{}");
}
#line 1975 "phppy.tab.c"
    break;

  case 66: /* array_value: ARRAY LPAREN value_list RPAREN  */
#line 521 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 3);
    sprintf(result, "[%s]", (yyvsp[-1].strval));
    (yyval.strval) = result;
}
#line 1985 "phppy.tab.c"
    break;

  case 67: /* array_value: ARRAY LPAREN key_value_list RPAREN  */
#line 527 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 3);
    sprintf(result, "{%s}", (yyvsp[-1].strval));
    (yyval.strval) = result;
}
#line 1995 "phppy.tab.c"
    break;

  case 68: /* array_value: ARRAY LPAREN key_value_pair RPAREN  */
#line 533 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 3);
    sprintf(result, "{%s}", (yyvsp[-1].strval));
    (yyval.strval) = result;
}
#line 2005 "phppy.tab.c"
    break;

  case 69: /* key_value_list: key_value_pair  */
#line 541 "phppy.y"
{
    (yyval.strval) = (yyvsp[0].strval);
}
#line 2013 "phppy.tab.c"
    break;

  case 70: /* key_value_list: key_value_list COMMA key_value_pair  */
#line 545 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval));
    (yyval.strval) = result;
}
#line 2023 "phppy.tab.c"
    break;

  case 71: /* key_value_pair: STRING ARROW value  */
#line 553 "phppy.y"
{
    char *key = (yyvsp[-2].strval);
    char *result = malloc(strlen(key) + strlen((yyvsp[0].strval)) + 4);
    sprintf(result, "%s: %s", key, (yyvsp[0].strval));
    free(key);
    (yyval.strval) = result;
}
#line 2035 "phppy.tab.c"
    break;

  case 72: /* key_value_pair: IDENTIFIER ARROW value  */
#line 561 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
    sprintf(result, "\"%s\": %s", (yyvsp[-2].strval), (yyvsp[0].strval));
    (yyval.strval) = result;
}
#line 2045 "phppy.tab.c"
    break;

  case 73: /* value_list: value  */
#line 569 "phppy.y"
{
    (yyval.strval) = (yyvsp[0].strval);
}
#line 2053 "phppy.tab.c"
    break;

  case 74: /* value_list: value_list COMMA value  */
#line 573 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval));
    (yyval.strval) = result;
}
#line 2063 "phppy.tab.c"
    break;

  case 75: /* function_declaration: FUNCTION IDENTIFIER LPAREN parameter_list RPAREN LBRACE statements RBRACE  */
#line 581 "phppy.y"
{
    char *func_name = (yyvsp[-6].strval);
    char *params = (yyvsp[-4].strval);
    char *body = indent_code((yyvsp[-1].strval));
    char *result = malloc(strlen(func_name) + strlen(params) + strlen(body) + 20);
    sprintf(result, "def %s(%s):\n%s", func_name, params, body);
    (yyval.strval) = result;
    free(body);
}
#line 2077 "phppy.tab.c"
    break;

  case 76: /* parameter_list: %empty  */
#line 593 "phppy.y"
{
    (yyval.strval) = strdup("");
}
#line 2085 "phppy.tab.c"
    break;

  case 77: /* parameter_list: VARIABLE  */
#line 597 "phppy.y"
{
    (yyval.strval) = strdup((yyvsp[0].strval) + 1);  // Skip the '$' character
}
#line 2093 "phppy.tab.c"
    break;

  case 78: /* parameter_list: IDENTIFIER  */
#line 601 "phppy.y"
{
    (yyval.strval) = strdup((yyvsp[0].strval));
}
#line 2101 "phppy.tab.c"
    break;

  case 79: /* parameter_list: parameter_list COMMA VARIABLE  */
#line 605 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval) + 1);  // Skip the '$' character
    (yyval.strval) = result;
}
#line 2111 "phppy.tab.c"
    break;

  case 80: /* parameter_list: parameter_list COMMA IDENTIFIER  */
#line 611 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval));
    (yyval.strval) = result;
}
#line 2121 "phppy.tab.c"
    break;

  case 81: /* function_call: IDENTIFIER LPAREN argument_list RPAREN SEMICOLON  */
#line 619 "phppy.y"
{
    char *func_name = (yyvsp[-4].strval);  // Skip the '$' character
    char *args = (yyvsp[-2].strval);
    char *result = malloc(strlen(func_name) + strlen(args) + 5);
    sprintf(result, "%s(%s)\n", func_name, args);
    (yyval.strval) = result;
}
#line 2133 "phppy.tab.c"
    break;

  case 82: /* argument_list: %empty  */
#line 629 "phppy.y"
{
    (yyval.strval) = strdup("");
}
#line 2141 "phppy.tab.c"
    break;

  case 84: /* argument_list: VARIABLE  */
#line 634 "phppy.y"
{
    (yyval.strval) = strdup((yyvsp[0].strval) + 1);  // Skip the '$' character
}
#line 2149 "phppy.tab.c"
    break;

  case 85: /* argument_list: IDENTIFIER  */
#line 638 "phppy.y"
{
    (yyval.strval) = strdup((yyvsp[0].strval));
}
#line 2157 "phppy.tab.c"
    break;

  case 86: /* argument_list: argument_list COMMA value  */
#line 642 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval));
    (yyval.strval) = result;
}
#line 2167 "phppy.tab.c"
    break;

  case 87: /* argument_list: argument_list COMMA VARIABLE  */
#line 648 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval) + 1);  // Skip the '$' character
    (yyval.strval) = result;
}
#line 2177 "phppy.tab.c"
    break;

  case 88: /* argument_list: argument_list COMMA IDENTIFIER  */
#line 654 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval));
    (yyval.strval) = result;
}
#line 2187 "phppy.tab.c"
    break;

  case 89: /* array_declaration: ARRAY LPAREN array_items RPAREN  */
#line 662 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 3);
    sprintf(result, "{%s}", (yyvsp[-1].strval));
    (yyval.strval) = result;
}
#line 2197 "phppy.tab.c"
    break;

  case 90: /* array_declaration: LBRACKET array_items RBRACKET  */
#line 668 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 3);
    sprintf(result, "{%s}", (yyvsp[-1].strval));
    (yyval.strval) = result;
}
#line 2207 "phppy.tab.c"
    break;

  case 92: /* array_items: array_items COMMA array_item  */
#line 677 "phppy.y"
    {
        char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 3);
        sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval));
        (yyval.strval) = result;
    }
#line 2217 "phppy.tab.c"
    break;

  case 93: /* array_item: STRING ARROW array_declaration  */
#line 685 "phppy.y"
{
    char *key = strip_quotes((yyvsp[-2].strval));
    char *result = malloc(strlen(key) + strlen((yyvsp[0].strval)) + 5);
    sprintf(result, "\"%s\": %s", key, (yyvsp[0].strval));
    free(key);
    (yyval.strval) = result;
}
#line 2229 "phppy.tab.c"
    break;

  case 94: /* array_item: STRING ARROW STRING  */
#line 693 "phppy.y"
{
    char *key = strip_quotes((yyvsp[-2].strval));
    char *value = strip_quotes((yyvsp[0].strval));
    char *result = malloc(strlen(key) + strlen(value) + 5);
    sprintf(result, "\"%s\": \"%s\"", key, value);
    free(key);
    free(value);
    (yyval.strval) = result;
}
#line 2243 "phppy.tab.c"
    break;

  case 95: /* array_item: STRING ARROW INTEGER  */
#line 703 "phppy.y"
{
    char *key = strip_quotes((yyvsp[-2].strval));
    char *result = malloc(strlen(key) + strlen((yyvsp[0].strval)) + 5);
    sprintf(result, "\"%s\": %s", key, (yyvsp[0].strval));
    free(key);
    (yyval.strval) = result;
}
#line 2255 "phppy.tab.c"
    break;


#line 2259 "phppy.tab.c"

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

#line 712 "phppy.y"


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
