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
  YYSYMBOL_IF = 20,                        /* IF  */
  YYSYMBOL_ELSEIF = 21,                    /* ELSEIF  */
  YYSYMBOL_ELSE = 22,                      /* ELSE  */
  YYSYMBOL_ECHO_TOKEN = 23,                /* ECHO_TOKEN  */
  YYSYMBOL_IS_INT = 24,                    /* IS_INT  */
  YYSYMBOL_IS_STRING = 25,                 /* IS_STRING  */
  YYSYMBOL_IS_ARRAY = 26,                  /* IS_ARRAY  */
  YYSYMBOL_IS_FLOAT = 27,                  /* IS_FLOAT  */
  YYSYMBOL_IS_BOOL = 28,                   /* IS_BOOL  */
  YYSYMBOL_WHILE = 29,                     /* WHILE  */
  YYSYMBOL_ENDWHILE = 30,                  /* ENDWHILE  */
  YYSYMBOL_INCREMENT = 31,                 /* INCREMENT  */
  YYSYMBOL_VARIABLE = 32,                  /* VARIABLE  */
  YYSYMBOL_INTEGER = 33,                   /* INTEGER  */
  YYSYMBOL_FLOAT = 34,                     /* FLOAT  */
  YYSYMBOL_CHAR = 35,                      /* CHAR  */
  YYSYMBOL_STRING = 36,                    /* STRING  */
  YYSYMBOL_BOOL = 37,                      /* BOOL  */
  YYSYMBOL_YYACCEPT = 38,                  /* $accept  */
  YYSYMBOL_program = 39,                   /* program  */
  YYSYMBOL_statements = 40,                /* statements  */
  YYSYMBOL_statement = 41,                 /* statement  */
  YYSYMBOL_variable_declaration = 42,      /* variable_declaration  */
  YYSYMBOL_variable_assignment = 43,       /* variable_assignment  */
  YYSYMBOL_echo_statement = 44,            /* echo_statement  */
  YYSYMBOL_constant_declaration = 45,      /* constant_declaration  */
  YYSYMBOL_if_statement = 46,              /* if_statement  */
  YYSYMBOL_elseif_clauses = 47,            /* elseif_clauses  */
  YYSYMBOL_elseif_clause = 48,             /* elseif_clause  */
  YYSYMBOL_else_clause = 49,               /* else_clause  */
  YYSYMBOL_while_statement = 50,           /* while_statement  */
  YYSYMBOL_condicion = 51,                 /* condicion  */
  YYSYMBOL_type_check_func = 52,           /* type_check_func  */
  YYSYMBOL_value = 53,                     /* value  */
  YYSYMBOL_array_value = 54,               /* array_value  */
  YYSYMBOL_value_list = 55                 /* value_list  */
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
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   291

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  60
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  131

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   292


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
      35,    36,    37
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   151,   151,   157,   158,   174,   175,   176,   177,   178,
     179,   180,   183,   192,   203,   211,   218,   228,   234,   241,
     252,   275,   295,   303,   311,   319,   329,   335,   343,   354,
     355,   363,   373,   383,   393,   404,   410,   422,   427,   432,
     437,   442,   447,   452,   457,   462,   467,   475,   475,   475,
     475,   475,   478,   479,   480,   481,   482,   483,   486,   494,
     498
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
  "COMMA", "ARRAY", "GT", "LT", "EQ", "COLON", "LE", "NE", "IF", "ELSEIF",
  "ELSE", "ECHO_TOKEN", "IS_INT", "IS_STRING", "IS_ARRAY", "IS_FLOAT",
  "IS_BOOL", "WHILE", "ENDWHILE", "INCREMENT", "VARIABLE", "INTEGER",
  "FLOAT", "CHAR", "STRING", "BOOL", "$accept", "program", "statements",
  "statement", "variable_declaration", "variable_assignment",
  "echo_statement", "constant_declaration", "if_statement",
  "elseif_clauses", "elseif_clause", "else_clause", "while_statement",
  "condicion", "type_check_func", "value", "array_value", "value_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-30)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      20,   173,    12,     4,    23,    49,   188,    50,     9,    18,
     -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,    25,
     182,    54,    13,   -30,   -30,   -30,   -30,   -30,    40,   -30,
     198,   -30,     0,    58,   -30,   -30,    52,   -30,   -30,   -30,
     -30,   -30,    -8,    56,    59,     5,   254,   -30,    61,   -30,
      60,   -30,    66,    68,   -30,   254,   213,   223,   229,   238,
      62,    43,   254,   254,   -30,    37,   -30,    -6,   -30,   -30,
      70,   -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,    19,
      82,   -30,   -30,   -30,   254,    69,    67,    72,    71,   104,
      85,   -30,   -30,   105,    90,   112,   -30,    93,    -5,    97,
     -30,   -30,    95,   173,   100,    99,     6,   -30,   -30,    87,
     -30,   138,   198,   139,   107,   -30,   -30,    84,   -30,   109,
     -30,   146,   173,   116,   113,   -30,   118,   173,   -30,   153,
     -30
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       3,     6,     5,    10,     7,     8,     9,     1,    11,     0,
       0,     0,     0,    52,    53,    54,    55,    56,     0,    57,
       0,    12,     0,     0,     2,     4,     0,    47,    48,    49,
      50,    51,     0,     0,     0,     0,     0,    18,     0,    17,
       0,    15,     0,     0,    16,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    59,     0,    19,     0,    14,    13,
       0,    37,    40,    38,    41,    39,    42,    43,    44,     0,
       0,    45,    46,    58,     0,     0,     0,     0,    26,     0,
       0,    60,    35,     0,     0,     0,    20,     0,    25,     0,
      33,    36,     0,     0,     0,     0,    23,    29,    24,     0,
      34,     0,     0,     0,     0,    30,    22,     0,    28,     0,
      27,     0,     0,     0,     0,    32,     0,     0,    21,     0,
      31
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -30,   -30,    -1,    -7,   -30,   -30,   -30,   -30,   -30,   -30,
      24,    32,   -30,   -29,   -30,    -3,   -30,   -30
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,   121,    10,    11,    12,    13,    14,    15,   106,
     107,   108,    16,    43,    44,    45,    29,    65
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
       9,    50,    35,    28,    85,    51,    56,    57,    58,    18,
      59,    86,    17,    21,    31,    32,   104,   105,    47,     3,
       3,    62,    34,     1,    63,     4,     4,   104,   114,    53,
      88,    19,    52,    23,    24,    25,    26,    27,     5,     5,
      33,     6,     6,    64,    48,    49,    83,     7,     7,    84,
       8,     8,    70,    72,    74,    76,    78,    20,    30,    81,
      82,    36,    46,    54,    55,    60,    66,    61,     3,    67,
       3,    68,    79,    69,     4,    80,     4,    96,    89,    87,
      92,    91,    35,   119,    93,    95,    35,     5,    35,     5,
       6,    90,     6,    97,    99,   101,     7,    94,     7,     8,
     110,     8,   111,   103,    35,     3,     3,   109,   112,   113,
     117,     4,     4,     3,    35,    98,   100,   122,   124,     4,
     123,   126,    35,   127,     5,     5,   129,     6,     6,   128,
     115,     0,     5,     7,     7,     6,     8,     8,   116,     3,
       3,     7,   102,     0,     8,     4,     4,     3,     0,   118,
     120,     0,     0,     4,     3,     0,     0,   125,     5,     5,
       4,     6,     6,     0,   130,     0,     5,     7,     7,     6,
       8,     8,     0,     5,     3,     7,     6,     0,     8,     0,
       4,     0,     7,     0,     0,     8,     0,     0,     0,     0,
       0,     0,     0,     5,     0,    21,     6,     0,     0,     0,
       0,    21,     7,     0,     0,     8,    37,    38,    39,    40,
      41,    21,     0,     0,    42,    23,    24,    25,    26,    27,
      22,    23,    24,    25,    26,    27,    21,     0,     0,     0,
      42,    23,    24,    25,    26,    27,    21,     0,     0,     0,
       0,     0,    21,     0,     0,    71,    23,    24,    25,    26,
      27,    21,     0,     0,     0,    73,    23,    24,    25,    26,
      27,    75,    23,    24,    25,    26,    27,    21,     0,     0,
      77,    23,    24,    25,    26,    27,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    23,    24,    25,
      26,    27
};

static const yytype_int16 yycheck[] =
{
       1,    30,     9,     6,    10,     5,    14,    15,    16,     5,
      18,    17,     0,    13,     5,     6,    21,    22,     5,     1,
       1,    16,     4,     3,    19,     7,     7,    21,    22,    32,
      11,     8,    32,    33,    34,    35,    36,    37,    20,    20,
      31,    23,    23,    46,    31,     5,     9,    29,    29,    12,
      32,    32,    55,    56,    57,    58,    59,     8,     8,    62,
      63,    36,     8,     5,    12,     9,     5,     8,     1,     9,
       1,     5,    10,     5,     7,    32,     7,     5,    79,     9,
      11,    84,    89,   112,    85,    86,    93,    20,    95,    20,
      23,     9,    23,    22,     9,     5,    29,    30,    29,    32,
       5,    32,   103,    10,   111,     1,     1,    10,     8,    10,
      23,     7,     7,     1,   121,    11,    11,    10,     9,     7,
      36,     5,   129,    10,    20,    20,   127,    23,    23,    11,
     106,    -1,    20,    29,    29,    23,    32,    32,   106,     1,
       1,    29,    30,    -1,    32,     7,     7,     1,    -1,    11,
      11,    -1,    -1,     7,     1,    -1,    -1,    11,    20,    20,
       7,    23,    23,    -1,    11,    -1,    20,    29,    29,    23,
      32,    32,    -1,    20,     1,    29,    23,    -1,    32,    -1,
       7,    -1,    29,    -1,    -1,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    13,    23,    -1,    -1,    -1,
      -1,    13,    29,    -1,    -1,    32,    24,    25,    26,    27,
      28,    13,    -1,    -1,    32,    33,    34,    35,    36,    37,
      32,    33,    34,    35,    36,    37,    13,    -1,    -1,    -1,
      32,    33,    34,    35,    36,    37,    13,    -1,    -1,    -1,
      -1,    -1,    13,    -1,    -1,    32,    33,    34,    35,    36,
      37,    13,    -1,    -1,    -1,    32,    33,    34,    35,    36,
      37,    32,    33,    34,    35,    36,    37,    13,    -1,    -1,
      32,    33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,
      36,    37
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    39,     1,     7,    20,    23,    29,    32,    40,
      41,    42,    43,    44,    45,    46,    50,     0,     5,     8,
       8,    13,    32,    33,    34,    35,    36,    37,    53,    54,
       8,     5,     6,    31,     4,    41,    36,    24,    25,    26,
      27,    28,    32,    51,    52,    53,     8,     5,    31,     5,
      51,     5,    32,    53,     5,    12,    14,    15,    16,    18,
       9,     8,    16,    19,    53,    55,     5,     9,     5,     5,
      53,    32,    53,    32,    53,    32,    53,    32,    53,    10,
      32,    53,    53,     9,    12,    10,    17,     9,    11,    40,
       9,    53,    11,    40,    30,    40,     5,    22,    11,     9,
      11,     5,    30,    10,    21,    22,    47,    48,    49,    10,
       5,    40,     8,    10,    22,    48,    49,    23,    11,    51,
      11,    40,    10,    36,     9,    11,     5,    10,    11,    40,
      11
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    38,    39,    40,    40,    41,    41,    41,    41,    41,
      41,    41,    42,    43,    43,    43,    43,    44,    44,    44,
      45,    46,    46,    46,    46,    46,    46,    46,    46,    47,
      47,    48,    49,    50,    50,    50,    50,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    52,    52,    52,
      52,    52,    53,    53,    53,    53,    53,    53,    54,    55,
      55
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     1,     2,     1,     1,     1,     1,     1,
       1,     2,     2,     4,     4,     3,     3,     3,     3,     4,
       7,    12,     9,     8,     8,     7,     6,    10,    10,     1,
       2,     7,     4,     7,     8,     6,     7,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     4,     1,
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
#line 152 "phppy.y"
{
    output = (yyvsp[-1].strval);
}
#line 1369 "phppy.tab.c"
    break;

  case 4: /* statements: statements statement  */
#line 159 "phppy.y"
    {
        //printf("DEBUG: concatenating statements: '%s' and '%s'\n", $1, $2);
        size_t len1 = strlen((yyvsp[-1].strval));
        size_t len2 = strlen((yyvsp[0].strval));
        char *result = malloc(len1 + len2 + 1);
        if (result) {
            strcpy(result, (yyvsp[-1].strval));
            strcat(result, (yyvsp[0].strval));
        }
        (yyval.strval) = result;
        //printf("DEBUG: result of concatenation: '%s'\n", result);
    }
#line 1386 "phppy.tab.c"
    break;

  case 11: /* statement: error SEMICOLON  */
#line 180 "phppy.y"
                      { yyerrok; }
#line 1392 "phppy.tab.c"
    break;

  case 12: /* variable_declaration: VARIABLE SEMICOLON  */
#line 184 "phppy.y"
{
    char *var_name = (yyvsp[-1].strval) + 1;  // Skip the '$' character
    char *result = malloc(strlen(var_name) + 10);
    sprintf(result, "%s = None\n", var_name);
    (yyval.strval) = result;
}
#line 1403 "phppy.tab.c"
    break;

  case 13: /* variable_assignment: VARIABLE ASSIGN value SEMICOLON  */
#line 193 "phppy.y"
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
#line 1418 "phppy.tab.c"
    break;

  case 14: /* variable_assignment: VARIABLE ASSIGN VARIABLE SEMICOLON  */
#line 204 "phppy.y"
{
    char *var_name = (yyvsp[-3].strval) + 1;  // Skip the '$' character
    char *value_name = (yyvsp[-1].strval) + 1;  // Skip the '$' character
    char *result = malloc(strlen(var_name) + strlen(value_name) + 5);
    sprintf(result, "%s = %s\n", var_name, value_name);
    (yyval.strval) = result;
}
#line 1430 "phppy.tab.c"
    break;

  case 15: /* variable_assignment: VARIABLE ASSIGN SEMICOLON  */
#line 212 "phppy.y"
{
    char *var_name = (yyvsp[-2].strval) + 1;  // Skip the '$' character
    char *result = malloc(strlen(var_name) + 10);
    sprintf(result, "%s = None\n", var_name);
    (yyval.strval) = result;
}
#line 1441 "phppy.tab.c"
    break;

  case 16: /* variable_assignment: VARIABLE INCREMENT SEMICOLON  */
#line 219 "phppy.y"
{
    char *var_name = (yyvsp[-2].strval) + 1;  // Skip the '$' character
    //printf("DEBUG: variable_increment - var_name = '%s'\n", var_name);
    char *result = malloc(strlen(var_name) + 7); // Tamaño necesario para " += 1\n" y terminador nulo
    sprintf(result, "%s += 1\n", var_name);
    (yyval.strval) = result;
}
#line 1453 "phppy.tab.c"
    break;

  case 17: /* echo_statement: ECHO_TOKEN value SEMICOLON  */
#line 229 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 8);
    sprintf(result, "print(%s)\n", (yyvsp[-1].strval));
    (yyval.strval) = result;
}
#line 1463 "phppy.tab.c"
    break;

  case 18: /* echo_statement: ECHO_TOKEN VARIABLE SEMICOLON  */
#line 235 "phppy.y"
{
    char *var_name = (yyvsp[-1].strval) + 1;  // Skip the '$' character
    char *result = malloc(strlen(var_name) + 10);
    sprintf(result, "print(%s)\n", var_name);
    (yyval.strval) = result;
}
#line 1474 "phppy.tab.c"
    break;

  case 19: /* echo_statement: ECHO_TOKEN VARIABLE INCREMENT SEMICOLON  */
#line 242 "phppy.y"
{
    char *var_name = (yyvsp[-2].strval) + 1;  // Skip the '$' character
    char *result = malloc(strlen(var_name) + 10);
    sprintf(result, "print(%s)\n%s += 1\n", var_name, var_name);
    (yyval.strval) = result;
}
#line 1485 "phppy.tab.c"
    break;

  case 20: /* constant_declaration: DEFINE LPAREN STRING COMMA value RPAREN SEMICOLON  */
#line 253 "phppy.y"
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
#line 1510 "phppy.tab.c"
    break;

  case 21: /* if_statement: IF LPAREN type_check_func LPAREN VARIABLE RPAREN RPAREN LBRACE ECHO_TOKEN STRING SEMICOLON RBRACE  */
#line 276 "phppy.y"
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
#line 1534 "phppy.tab.c"
    break;

  case 22: /* if_statement: IF LPAREN condicion RPAREN LBRACE statements RBRACE elseif_clauses else_clause  */
#line 296 "phppy.y"
{
    char *if_part = indent_code((yyvsp[-3].strval));
    char *result = malloc(strlen((yyvsp[-6].strval)) + strlen(if_part) + strlen((yyvsp[-1].strval)) + strlen((yyvsp[0].strval)) + 10);
    sprintf(result, "if (%s):\n%s%s%s", (yyvsp[-6].strval), if_part, (yyvsp[-1].strval), (yyvsp[0].strval));
    (yyval.strval) = result;
    free(if_part);
}
#line 1546 "phppy.tab.c"
    break;

  case 23: /* if_statement: IF LPAREN condicion RPAREN LBRACE statements RBRACE elseif_clauses  */
#line 304 "phppy.y"
{
    char *if_part = indent_code((yyvsp[-2].strval));
    char *result = malloc(strlen((yyvsp[-5].strval)) + strlen(if_part) + strlen((yyvsp[0].strval)) + 10);
    sprintf(result, "if (%s):\n%s%s", (yyvsp[-5].strval), if_part, (yyvsp[0].strval));
    (yyval.strval) = result;
    free(if_part);
}
#line 1558 "phppy.tab.c"
    break;

  case 24: /* if_statement: IF LPAREN condicion RPAREN LBRACE statements RBRACE else_clause  */
#line 312 "phppy.y"
{
    char *if_part = indent_code((yyvsp[-2].strval));
    char *result = malloc(strlen((yyvsp[-5].strval)) + strlen(if_part) + strlen((yyvsp[0].strval)) + 20);
    sprintf(result, "if (%s):\n%s%s", (yyvsp[-5].strval), if_part, (yyvsp[0].strval));
    (yyval.strval) = result;
    free(if_part);
}
#line 1570 "phppy.tab.c"
    break;

  case 25: /* if_statement: IF LPAREN condicion RPAREN LBRACE statements RBRACE  */
#line 320 "phppy.y"
{
    //printf("DEBUG: if_statement - statements = '%s'\n", $6);
    char *if_part = indent_code((yyvsp[-1].strval));
    char *result = malloc(strlen((yyvsp[-4].strval)) + strlen(if_part) + 10);
    sprintf(result, "if (%s):\n%s", (yyvsp[-4].strval), if_part);
    (yyval.strval) = result;
    free(if_part);
}
#line 1583 "phppy.tab.c"
    break;

  case 26: /* if_statement: IF LPAREN condicion RPAREN LBRACE RBRACE  */
#line 330 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-3].strval)) + 15);
    sprintf(result, "if (%s):\n    pass\n", (yyvsp[-3].strval));
    (yyval.strval) = result;
}
#line 1593 "phppy.tab.c"
    break;

  case 27: /* if_statement: IF LPAREN condicion RPAREN LBRACE statements RBRACE ELSE LBRACE RBRACE  */
#line 336 "phppy.y"
{
    char *indented_statements_if = indent_code((yyvsp[-4].strval));
    char *result = malloc(strlen((yyvsp[-7].strval)) + strlen(indented_statements_if) + 20);
    sprintf(result, "if (%s):\n%selse:\n    pass\n", (yyvsp[-7].strval), indented_statements_if);
    (yyval.strval) = result;
    free(indented_statements_if);
}
#line 1605 "phppy.tab.c"
    break;

  case 28: /* if_statement: IF LPAREN condicion RPAREN LBRACE RBRACE ELSE LBRACE statements RBRACE  */
#line 344 "phppy.y"
{
    char *indented_statements_else = indent_code((yyvsp[-1].strval));
    char *result = malloc(strlen((yyvsp[-7].strval)) + strlen(indented_statements_else) + 20);
    sprintf(result, "if (%s):\n    pass\nelse:\n%s", (yyvsp[-7].strval), indented_statements_else);
    (yyval.strval) = result;
    free(indented_statements_else);
}
#line 1617 "phppy.tab.c"
    break;

  case 30: /* elseif_clauses: elseif_clauses elseif_clause  */
#line 356 "phppy.y"
    {
        char *result = malloc(strlen((yyvsp[-1].strval)) + strlen((yyvsp[0].strval)) + 1);
        sprintf(result, "%s%s", (yyvsp[-1].strval), (yyvsp[0].strval));
        (yyval.strval) = result;
    }
#line 1627 "phppy.tab.c"
    break;

  case 31: /* elseif_clause: ELSEIF LPAREN condicion RPAREN LBRACE statements RBRACE  */
#line 364 "phppy.y"
{
    char *elseif_part = indent_code((yyvsp[-1].strval));
    char *result = malloc(strlen((yyvsp[-4].strval)) + strlen(elseif_part) + 10);
    sprintf(result, "elif (%s):\n%s", (yyvsp[-4].strval), elseif_part);
    (yyval.strval) = result;
    free(elseif_part);
}
#line 1639 "phppy.tab.c"
    break;

  case 32: /* else_clause: ELSE LBRACE statements RBRACE  */
#line 374 "phppy.y"
{
    char *else_part = indent_code((yyvsp[-1].strval));
    char *result = malloc(strlen(else_part) + 20);
    sprintf(result, "else:\n%s", else_part);
    (yyval.strval) = result;
    free(else_part);
}
#line 1651 "phppy.tab.c"
    break;

  case 33: /* while_statement: WHILE LPAREN condicion RPAREN LBRACE statements RBRACE  */
#line 384 "phppy.y"
{
    //printf("DEBUG: condicion = '%s'\n", $3);
    //printf("DEBUG: statements = '%s'\n", $6);
    char *indented_statements = indent_code((yyvsp[-1].strval));
    char *result = malloc(strlen((yyvsp[-4].strval)) + strlen(indented_statements) + 15);
    sprintf(result, "while (%s):\n%s", (yyvsp[-4].strval), indented_statements);
    (yyval.strval) = result;
    free(indented_statements);
}
#line 1665 "phppy.tab.c"
    break;

  case 34: /* while_statement: WHILE LPAREN condicion RPAREN COLON statements ENDWHILE SEMICOLON  */
#line 394 "phppy.y"
{
    //printf("DEBUG: condicion = '%s'\n", $3);
    //printf("DEBUG: statements = '%s'\n", $6);
    char *indented_statements = indent_code((yyvsp[-2].strval));
    char *result = malloc(strlen((yyvsp[-5].strval)) + strlen(indented_statements) + 15);
    sprintf(result, "while (%s):\n%s", (yyvsp[-5].strval), indented_statements);
    (yyval.strval) = result;
    free(indented_statements);
}
#line 1679 "phppy.tab.c"
    break;

  case 35: /* while_statement: WHILE LPAREN condicion RPAREN LBRACE RBRACE  */
#line 405 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-3].strval)) + 15);
    sprintf(result, "while (%s):\n    pass\n", (yyvsp[-3].strval));
    (yyval.strval) = result;
}
#line 1689 "phppy.tab.c"
    break;

  case 36: /* while_statement: WHILE LPAREN condicion RPAREN COLON ENDWHILE SEMICOLON  */
#line 411 "phppy.y"
{
    printf("DEBUG: while_statement - condicion = '%s' (empty block)\n", (yyvsp[-4].strval));
    char *result = malloc(strlen((yyvsp[-4].strval)) + 15);
    sprintf(result, "while (%s):\n    pass\n", (yyvsp[-4].strval));
    (yyval.strval) = result;
}
#line 1700 "phppy.tab.c"
    break;

  case 37: /* condicion: VARIABLE GT VARIABLE  */
#line 423 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4); // 4: para espacio, operador, espacio, y terminador nulo
        sprintf((yyval.strval), "%s > %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval) + 1); // Omitimos el carácter '$'
    }
#line 1709 "phppy.tab.c"
    break;

  case 38: /* condicion: VARIABLE LT VARIABLE  */
#line 428 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
        sprintf((yyval.strval), "%s < %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval) + 1); // Omitimos el carácter '$'
    }
#line 1718 "phppy.tab.c"
    break;

  case 39: /* condicion: VARIABLE EQ VARIABLE  */
#line 433 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
        sprintf((yyval.strval), "%s == %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval) + 1); // En Python se usa '==' para la igualdad
    }
#line 1727 "phppy.tab.c"
    break;

  case 40: /* condicion: VARIABLE GT value  */
#line 438 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4); // 4: para espacio, operador, espacio, y terminador nulo
        sprintf((yyval.strval), "%s > %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval)); // Omitimos el carácter '$'
    }
#line 1736 "phppy.tab.c"
    break;

  case 41: /* condicion: VARIABLE LT value  */
#line 443 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
        sprintf((yyval.strval), "%s < %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval)); // Omitimos el carácter '$'
    }
#line 1745 "phppy.tab.c"
    break;

  case 42: /* condicion: VARIABLE EQ value  */
#line 448 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
        sprintf((yyval.strval), "%s == %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval)); // En Python se usa '==' para la igualdad
    }
#line 1754 "phppy.tab.c"
    break;

  case 43: /* condicion: VARIABLE LE VARIABLE  */
#line 453 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 5);
        sprintf((yyval.strval), "%s <= %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval) + 1); // Omitimos el carácter '$'
    }
#line 1763 "phppy.tab.c"
    break;

  case 44: /* condicion: VARIABLE LE value  */
#line 458 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 5);
        sprintf((yyval.strval), "%s <= %s", (yyvsp[-2].strval) + 1, (yyvsp[0].strval)); // Omitimos el carácter '$'
    }
#line 1772 "phppy.tab.c"
    break;

  case 45: /* condicion: value EQ value  */
#line 463 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 4);
        sprintf((yyval.strval), "%s == %s", (yyvsp[-2].strval), (yyvsp[0].strval)); // En Python se usa '==' para la igualdad
    }
#line 1781 "phppy.tab.c"
    break;

  case 46: /* condicion: value NE value  */
#line 468 "phppy.y"
    {
        (yyval.strval) = (char *) malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 5);
        sprintf((yyval.strval), "%s != %s", (yyvsp[-2].strval), (yyvsp[0].strval)); // En Python se usa '!=' para desigualdad
    }
#line 1790 "phppy.tab.c"
    break;

  case 52: /* value: INTEGER  */
#line 478 "phppy.y"
               { (yyval.strval) = (yyvsp[0].strval); }
#line 1796 "phppy.tab.c"
    break;

  case 53: /* value: FLOAT  */
#line 479 "phppy.y"
            { (yyval.strval) = (yyvsp[0].strval); }
#line 1802 "phppy.tab.c"
    break;

  case 54: /* value: CHAR  */
#line 480 "phppy.y"
           { (yyval.strval) = (yyvsp[0].strval); }
#line 1808 "phppy.tab.c"
    break;

  case 55: /* value: STRING  */
#line 481 "phppy.y"
             { (yyval.strval) = (yyvsp[0].strval); }
#line 1814 "phppy.tab.c"
    break;

  case 56: /* value: BOOL  */
#line 482 "phppy.y"
           { (yyval.strval) = (yyvsp[0].strval); }
#line 1820 "phppy.tab.c"
    break;

  case 57: /* value: array_value  */
#line 483 "phppy.y"
                  { (yyval.strval) = (yyvsp[0].strval); }
#line 1826 "phppy.tab.c"
    break;

  case 58: /* array_value: ARRAY LPAREN value_list RPAREN  */
#line 487 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-1].strval)) + 3);
    sprintf(result, "[%s]", (yyvsp[-1].strval));
    (yyval.strval) = result;
}
#line 1836 "phppy.tab.c"
    break;

  case 59: /* value_list: value  */
#line 495 "phppy.y"
{
    (yyval.strval) = (yyvsp[0].strval);
}
#line 1844 "phppy.tab.c"
    break;

  case 60: /* value_list: value_list COMMA value  */
#line 499 "phppy.y"
{
    char *result = malloc(strlen((yyvsp[-2].strval)) + strlen((yyvsp[0].strval)) + 2);
    sprintf(result, "%s, %s", (yyvsp[-2].strval), (yyvsp[0].strval));
    (yyval.strval) = result;
}
#line 1854 "phppy.tab.c"
    break;


#line 1858 "phppy.tab.c"

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

#line 506 "phppy.y"


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
