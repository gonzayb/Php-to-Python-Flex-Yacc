/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PHPPY_TAB_H_INCLUDED
# define YY_YY_PHPPY_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    PHP_START = 258,               /* PHP_START  */
    PHP_END = 259,                 /* PHP_END  */
    SEMICOLON = 260,               /* SEMICOLON  */
    ASSIGN = 261,                  /* ASSIGN  */
    DEFINE = 262,                  /* DEFINE  */
    LPAREN = 263,                  /* LPAREN  */
    RPAREN = 264,                  /* RPAREN  */
    LBRACE = 265,                  /* LBRACE  */
    RBRACE = 266,                  /* RBRACE  */
    COMMA = 267,                   /* COMMA  */
    ARRAY = 268,                   /* ARRAY  */
    GT = 269,                      /* GT  */
    LT = 270,                      /* LT  */
    EQ = 271,                      /* EQ  */
    COLON = 272,                   /* COLON  */
    LE = 273,                      /* LE  */
    NE = 274,                      /* NE  */
    ARROW = 275,                   /* ARROW  */
    LBRACKET = 276,                /* LBRACKET  */
    RBRACKET = 277,                /* RBRACKET  */
    IF = 278,                      /* IF  */
    ELSEIF = 279,                  /* ELSEIF  */
    ELSE = 280,                    /* ELSE  */
    ECHO_TOKEN = 281,              /* ECHO_TOKEN  */
    IS_INT = 282,                  /* IS_INT  */
    IS_STRING = 283,               /* IS_STRING  */
    IS_ARRAY = 284,                /* IS_ARRAY  */
    IS_FLOAT = 285,                /* IS_FLOAT  */
    IS_BOOL = 286,                 /* IS_BOOL  */
    WHILE = 287,                   /* WHILE  */
    ENDWHILE = 288,                /* ENDWHILE  */
    INCREMENT = 289,               /* INCREMENT  */
    RETURN = 290,                  /* RETURN  */
    FUNCTION = 291,                /* FUNCTION  */
    GLOBAL = 292,                  /* GLOBAL  */
    PLUS = 293,                    /* PLUS  */
    VARIABLE = 294,                /* VARIABLE  */
    INTEGER = 295,                 /* INTEGER  */
    FLOAT = 296,                   /* FLOAT  */
    CHAR = 297,                    /* CHAR  */
    STRING = 298,                  /* STRING  */
    BOOL = 299,                    /* BOOL  */
    IDENTIFIER = 300               /* IDENTIFIER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 155 "phppy.y"

    char *strval;

#line 113 "phppy.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PHPPY_TAB_H_INCLUDED  */
