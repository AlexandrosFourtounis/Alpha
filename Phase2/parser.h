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

#ifndef YY_YY_PHASE2_PARSER_H_INCLUDED
# define YY_YY_PHASE2_PARSER_H_INCLUDED
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
    ID = 258,                      /* ID  */
    INTEGER = 259,                 /* INTEGER  */
    KEYWORD_IF = 260,              /* KEYWORD_IF  */
    KEYWORD_THEN = 261,            /* KEYWORD_THEN  */
    KEYWORD_ELSE = 262,            /* KEYWORD_ELSE  */
    KEYWORD_WHILE = 263,           /* KEYWORD_WHILE  */
    KEYWORD_FOR = 264,             /* KEYWORD_FOR  */
    KEYWORD_FUNCTION = 265,        /* KEYWORD_FUNCTION  */
    KEYWORD_RETURN = 266,          /* KEYWORD_RETURN  */
    KEYWORD_BREAK = 267,           /* KEYWORD_BREAK  */
    KEYWORD_CONTINUE = 268,        /* KEYWORD_CONTINUE  */
    KEYWORD_AND = 269,             /* KEYWORD_AND  */
    KEYWORD_NOT = 270,             /* KEYWORD_NOT  */
    KEYWORD_OR = 271,              /* KEYWORD_OR  */
    KEYWORD_LOCAL = 272,           /* KEYWORD_LOCAL  */
    KEYWORD_TRUE = 273,            /* KEYWORD_TRUE  */
    KEYWORD_FALSE = 274,           /* KEYWORD_FALSE  */
    KEYWORD_NIL = 275,             /* KEYWORD_NIL  */
    GREATER = 276,                 /* GREATER  */
    LESS = 277,                    /* LESS  */
    EQUALS = 278,                  /* EQUALS  */
    GREATER_EQUAL = 279,           /* GREATER_EQUAL  */
    LESS_EQUAL = 280,              /* LESS_EQUAL  */
    NOT_EQUAL = 281,               /* NOT_EQUAL  */
    INCREMENT = 282,               /* INCREMENT  */
    DECREMENT = 283,               /* DECREMENT  */
    STRING = 284,                  /* STRING  */
    REAL = 285,                    /* REAL  */
    IDENTIFIER = 286,              /* IDENTIFIER  */
    LEFTBRACE = 287,               /* LEFTBRACE  */
    RIGHTBRACE = 288,              /* RIGHTBRACE  */
    LEFTBRACKET = 289,             /* LEFTBRACKET  */
    RIGHTBRACKET = 290,            /* RIGHTBRACKET  */
    LEFTPARENTHESIS = 291,         /* LEFTPARENTHESIS  */
    RIGHTPARENTHESIS = 292,        /* RIGHTPARENTHESIS  */
    COMMA = 293,                   /* COMMA  */
    SEMICOLON = 294,               /* SEMICOLON  */
    COLON = 295,                   /* COLON  */
    DOT = 296,                     /* DOT  */
    DOUBLEDOT = 297,               /* DOUBLEDOT  */
    DOUBLECOLON = 298,             /* DOUBLECOLON  */
    COMMENT = 299,                 /* COMMENT  */
    UMINUS = 300                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ID 258
#define INTEGER 259
#define KEYWORD_IF 260
#define KEYWORD_THEN 261
#define KEYWORD_ELSE 262
#define KEYWORD_WHILE 263
#define KEYWORD_FOR 264
#define KEYWORD_FUNCTION 265
#define KEYWORD_RETURN 266
#define KEYWORD_BREAK 267
#define KEYWORD_CONTINUE 268
#define KEYWORD_AND 269
#define KEYWORD_NOT 270
#define KEYWORD_OR 271
#define KEYWORD_LOCAL 272
#define KEYWORD_TRUE 273
#define KEYWORD_FALSE 274
#define KEYWORD_NIL 275
#define GREATER 276
#define LESS 277
#define EQUALS 278
#define GREATER_EQUAL 279
#define LESS_EQUAL 280
#define NOT_EQUAL 281
#define INCREMENT 282
#define DECREMENT 283
#define STRING 284
#define REAL 285
#define IDENTIFIER 286
#define LEFTBRACE 287
#define RIGHTBRACE 288
#define LEFTBRACKET 289
#define RIGHTBRACKET 290
#define LEFTPARENTHESIS 291
#define RIGHTPARENTHESIS 292
#define COMMA 293
#define SEMICOLON 294
#define COLON 295
#define DOT 296
#define DOUBLEDOT 297
#define DOUBLECOLON 298
#define COMMENT 299
#define UMINUS 300

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PHASE2_PARSER_H_INCLUDED  */
