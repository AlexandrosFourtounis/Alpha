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
#line 1 "parser.y"

    #include <stdio.h>
    #include "quads.h"
    #include "stack.h"

    #define YYDEBUG 1
    #define BOLD_RED "\033[1;31m"
    #define RESET "\033[0m"

    Stack *scopeoffsetstack;

    extern int yydebug;
    int yyerror (char* yaccProvidedMessage);
    int alpha_yylex(void* yylval);
    SymbolTableEntry *entry;
    SymbolTableEntry *sym;

    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;

    SymTable_T symTable = NULL;
    int anonymousCounter = 0;
    int scope = 0;
    int called = 0;
    int doublec_flag = 0;

#line 99 "parser.c"

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

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INTEGER = 3,                    /* "integer constant"  */
  YYSYMBOL_REAL = 4,                       /* "real contstant"  */
  YYSYMBOL_KEYWORD_IF = 5,                 /* KEYWORD_IF  */
  YYSYMBOL_KEYWORD_THEN = 6,               /* KEYWORD_THEN  */
  YYSYMBOL_KEYWORD_ELSE = 7,               /* KEYWORD_ELSE  */
  YYSYMBOL_KEYWORD_WHILE = 8,              /* KEYWORD_WHILE  */
  YYSYMBOL_KEYWORD_FOR = 9,                /* KEYWORD_FOR  */
  YYSYMBOL_KEYWORD_FUNCTION = 10,          /* KEYWORD_FUNCTION  */
  YYSYMBOL_KEYWORD_RETURN = 11,            /* KEYWORD_RETURN  */
  YYSYMBOL_KEYWORD_BREAK = 12,             /* KEYWORD_BREAK  */
  YYSYMBOL_KEYWORD_CONTINUE = 13,          /* KEYWORD_CONTINUE  */
  YYSYMBOL_KEYWORD_AND = 14,               /* KEYWORD_AND  */
  YYSYMBOL_KEYWORD_NOT = 15,               /* KEYWORD_NOT  */
  YYSYMBOL_KEYWORD_OR = 16,                /* KEYWORD_OR  */
  YYSYMBOL_KEYWORD_LOCAL = 17,             /* KEYWORD_LOCAL  */
  YYSYMBOL_KEYWORD_TRUE = 18,              /* KEYWORD_TRUE  */
  YYSYMBOL_KEYWORD_FALSE = 19,             /* KEYWORD_FALSE  */
  YYSYMBOL_KEYWORD_NIL = 20,               /* KEYWORD_NIL  */
  YYSYMBOL_GREATER = 21,                   /* GREATER  */
  YYSYMBOL_LESS = 22,                      /* LESS  */
  YYSYMBOL_EQUALS = 23,                    /* EQUALS  */
  YYSYMBOL_GREATER_EQUAL = 24,             /* GREATER_EQUAL  */
  YYSYMBOL_LESS_EQUAL = 25,                /* LESS_EQUAL  */
  YYSYMBOL_NOT_EQUAL = 26,                 /* NOT_EQUAL  */
  YYSYMBOL_INCREMENT = 27,                 /* INCREMENT  */
  YYSYMBOL_DECREMENT = 28,                 /* DECREMENT  */
  YYSYMBOL_STRING = 29,                    /* STRING  */
  YYSYMBOL_IDENTIFIER = 30,                /* IDENTIFIER  */
  YYSYMBOL_LEFTBRACE = 31,                 /* LEFTBRACE  */
  YYSYMBOL_RIGHTBRACE = 32,                /* RIGHTBRACE  */
  YYSYMBOL_LEFTBRACKET = 33,               /* LEFTBRACKET  */
  YYSYMBOL_RIGHTBRACKET = 34,              /* RIGHTBRACKET  */
  YYSYMBOL_LEFTPARENTHESIS = 35,           /* LEFTPARENTHESIS  */
  YYSYMBOL_RIGHTPARENTHESIS = 36,          /* RIGHTPARENTHESIS  */
  YYSYMBOL_COMMA = 37,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 38,                 /* SEMICOLON  */
  YYSYMBOL_COLON = 39,                     /* COLON  */
  YYSYMBOL_DOT = 40,                       /* DOT  */
  YYSYMBOL_DOUBLEDOT = 41,                 /* DOUBLEDOT  */
  YYSYMBOL_DOUBLECOLON = 42,               /* DOUBLECOLON  */
  YYSYMBOL_43_ = 43,                       /* '='  */
  YYSYMBOL_44_ = 44,                       /* '+'  */
  YYSYMBOL_45_ = 45,                       /* '-'  */
  YYSYMBOL_46_ = 46,                       /* '*'  */
  YYSYMBOL_47_ = 47,                       /* '/'  */
  YYSYMBOL_48_ = 48,                       /* '%'  */
  YYSYMBOL_UMINUS = 49,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 50,                  /* $accept  */
  YYSYMBOL_program = 51,                   /* program  */
  YYSYMBOL_parsing = 52,                   /* parsing  */
  YYSYMBOL_stmt = 53,                      /* stmt  */
  YYSYMBOL_expr = 54,                      /* expr  */
  YYSYMBOL_term = 55,                      /* term  */
  YYSYMBOL_assignexpr = 56,                /* assignexpr  */
  YYSYMBOL_57_1 = 57,                      /* $@1  */
  YYSYMBOL_primary = 58,                   /* primary  */
  YYSYMBOL_lvalue = 59,                    /* lvalue  */
  YYSYMBOL_member = 60,                    /* member  */
  YYSYMBOL_call = 61,                      /* call  */
  YYSYMBOL_callsuffix = 62,                /* callsuffix  */
  YYSYMBOL_normcall = 63,                  /* normcall  */
  YYSYMBOL_methodcall = 64,                /* methodcall  */
  YYSYMBOL_elist = 65,                     /* elist  */
  YYSYMBOL_exprlist = 66,                  /* exprlist  */
  YYSYMBOL_objectdef = 67,                 /* objectdef  */
  YYSYMBOL_indexed = 68,                   /* indexed  */
  YYSYMBOL_indexedelem = 69,               /* indexedelem  */
  YYSYMBOL_block = 70,                     /* block  */
  YYSYMBOL_71_2 = 71,                      /* $@2  */
  YYSYMBOL_blockk = 72,                    /* blockk  */
  YYSYMBOL_funcname = 73,                  /* funcname  */
  YYSYMBOL_funcprefix = 74,                /* funcprefix  */
  YYSYMBOL_funcargs = 75,                  /* funcargs  */
  YYSYMBOL_funcbody = 76,                  /* funcbody  */
  YYSYMBOL_funcdef = 77,                   /* funcdef  */
  YYSYMBOL_const = 78,                     /* const  */
  YYSYMBOL_number = 79,                    /* number  */
  YYSYMBOL_idlist = 80,                    /* idlist  */
  YYSYMBOL_ids = 81,                       /* ids  */
  YYSYMBOL_82_3 = 82,                      /* $@3  */
  YYSYMBOL_ifstmt = 83,                    /* ifstmt  */
  YYSYMBOL_whilestmt = 84,                 /* whilestmt  */
  YYSYMBOL_forstmt = 85,                   /* forstmt  */
  YYSYMBOL_returnstmt = 86                 /* returnstmt  */
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

#if 1

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
#endif /* 1 */

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
#define YYFINAL  79
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   707

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  182

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
       2,     2,     2,     2,     2,     2,     2,    48,     2,     2,
       2,     2,    46,    44,     2,    45,     2,    47,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    43,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    49
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    80,    80,    82,    83,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   117,   118,   125,   131,   132,   133,   134,   135,   138,
     137,   181,   182,   183,   184,   185,   188,   209,   252,   259,
     267,   269,   274,   284,   285,   288,   289,   299,   302,   303,
     305,   307,   309,   310,   313,   314,   318,   319,   320,   327,
     328,   331,   333,   333,   336,   337,   340,   371,   388,   403,
     409,   415,   431,   432,   433,   434,   439,   441,   442,   446,
     458,   461,   461,   475,   478,   479,   481,   483,   485,   492
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "\"integer constant\"",
  "\"real contstant\"", "KEYWORD_IF", "KEYWORD_THEN", "KEYWORD_ELSE",
  "KEYWORD_WHILE", "KEYWORD_FOR", "KEYWORD_FUNCTION", "KEYWORD_RETURN",
  "KEYWORD_BREAK", "KEYWORD_CONTINUE", "KEYWORD_AND", "KEYWORD_NOT",
  "KEYWORD_OR", "KEYWORD_LOCAL", "KEYWORD_TRUE", "KEYWORD_FALSE",
  "KEYWORD_NIL", "GREATER", "LESS", "EQUALS", "GREATER_EQUAL",
  "LESS_EQUAL", "NOT_EQUAL", "INCREMENT", "DECREMENT", "STRING",
  "IDENTIFIER", "LEFTBRACE", "RIGHTBRACE", "LEFTBRACKET", "RIGHTBRACKET",
  "LEFTPARENTHESIS", "RIGHTPARENTHESIS", "COMMA", "SEMICOLON", "COLON",
  "DOT", "DOUBLEDOT", "DOUBLECOLON", "'='", "'+'", "'-'", "'*'", "'/'",
  "'%'", "UMINUS", "$accept", "program", "parsing", "stmt", "expr", "term",
  "assignexpr", "$@1", "primary", "lvalue", "member", "call", "callsuffix",
  "normcall", "methodcall", "elist", "exprlist", "objectdef", "indexed",
  "indexedelem", "block", "$@2", "blockk", "funcname", "funcprefix",
  "funcargs", "funcbody", "funcdef", "const", "number", "idlist", "ids",
  "$@3", "ifstmt", "whilestmt", "forstmt", "returnstmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-52)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-76)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     150,   -31,   -52,   -52,   -23,   -19,   -11,    -2,   269,    -5,
       4,   321,    23,   -52,   -52,   -52,    26,    26,   -52,   -12,
     -52,    17,   302,   -52,    25,   321,    49,   -52,   150,   346,
     -52,   -52,   -52,   -18,   -52,   -29,   -52,   -52,    28,   -52,
     -52,   -52,   -52,   -52,   -52,   -52,   -52,   321,   321,   321,
     -52,   -52,   -52,   381,   -52,   -52,   -52,   -52,    48,   -32,
     -29,   -32,   321,    39,   -52,   -52,   -52,   193,   321,   -52,
     616,    36,    34,    38,    44,   416,    51,   -12,   -52,   -52,
     -52,   321,   321,   321,   321,   321,   321,   321,   321,   -52,
     321,   321,   321,   321,   321,   -52,   -52,   321,    58,   -52,
     321,   321,    60,    61,    63,   432,   467,    57,   -52,    64,
      65,    67,   193,    71,   483,   -52,   321,   -52,    68,   -52,
      69,   -52,   644,   631,    89,    89,   659,    89,    89,   659,
      19,    19,   -52,   -52,   -52,   518,   -52,   321,   533,    73,
     -52,    59,    79,   -52,   -52,   236,   236,   321,    69,   -52,
     321,   -52,   -52,   321,   616,   -52,   321,   -52,   616,   -52,
     -52,    75,   -52,   -52,   100,   -52,   568,    80,   603,    81,
     -52,   236,   321,   -52,   -52,   -52,    59,   -52,    82,   -52,
     236,   -52
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    87,    88,     0,     0,     0,    77,     0,     0,
       0,     0,     0,    85,    86,    84,     0,     0,    83,    46,
      72,     0,     0,    14,     0,     0,     0,     2,     0,     0,
      30,    29,    38,    41,    50,    42,    43,    12,     0,    13,
      45,    82,     6,     7,     8,     9,    15,     0,     0,    63,
      76,    78,    99,     0,    10,    11,    33,    47,     0,    34,
       0,    36,    63,     0,    56,    58,    59,     0,     0,    68,
      65,     0,    62,     0,    69,     0,     0,    49,    32,     1,
       3,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       0,     0,     0,     0,     0,    35,    37,     0,     0,    39,
       0,    63,     0,    90,     0,     0,     0,     0,    98,     0,
       0,     0,     0,     0,     0,    66,     0,    67,     0,    31,
      44,    48,    27,    28,    21,    23,    25,    22,    24,    26,
      16,    18,    17,    19,    20,     0,    51,     0,     0,     0,
      53,    93,     0,    80,    81,     0,     0,     0,     0,    60,
      63,    74,    73,     0,    64,    70,    63,    52,    40,    54,
      55,     0,    89,    79,    95,    96,     0,     0,     0,     0,
      91,     0,    63,    61,    71,    57,    93,    94,     0,    92,
       0,    97
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -52,   -52,    91,   -48,    -8,   -52,   -52,   -52,   -52,    10,
     -52,    14,    43,   -52,   -52,   -44,   -52,   -52,     3,   -52,
      18,   -52,    12,   -52,   -52,   -52,   -52,   -20,   -52,   -52,
     -52,   -51,   -52,   -52,   -52,   -52,   -52
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    26,    27,    28,    29,    30,    31,   137,    32,    33,
      34,    35,    64,    65,    66,    71,    72,    36,    73,    74,
      37,    67,   113,    51,    38,   104,   144,    39,    40,    41,
     142,   162,   176,    42,    43,    44,    45
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      53,    97,    76,    56,   100,   107,   101,    46,    98,    95,
      96,   102,    47,    70,    75,    97,    48,    78,   110,   112,
       2,     3,    98,    62,    49,    99,    59,    61,    50,    63,
      60,    60,    11,    54,    12,    13,    14,    15,   109,   105,
     106,    70,    55,    12,    16,    17,    18,    19,    68,    79,
      21,    69,    22,    57,    70,    77,    19,   139,     7,    24,
     114,    58,    25,   103,   112,    92,    93,    94,    24,   111,
     115,   116,   117,   122,   123,   124,   125,   126,   127,   128,
     129,   118,   130,   131,   132,   133,   134,   120,   136,   135,
     140,   141,   138,    70,    20,   147,   161,   164,   165,    68,
     148,   149,   150,   152,   156,   170,   167,   171,   154,   160,
     -76,   -76,   169,   -76,   -76,   163,   173,   175,   180,    80,
     121,   155,   143,   177,   151,   179,     0,     0,   178,   158,
       0,     0,   181,    90,    91,    92,    93,    94,     0,   166,
       0,     0,    70,     0,     0,   168,     0,     0,    70,     0,
      -4,     1,     0,     2,     3,     4,     0,     0,     5,     6,
       7,     8,     9,    10,    70,    11,     0,    12,    13,    14,
      15,     0,     0,     0,     0,     0,     0,    16,    17,    18,
      19,    20,     0,    21,     0,    22,     0,     0,    23,     0,
       0,     0,    24,     0,     1,    25,     2,     3,     4,     0,
       0,     5,     6,     7,     8,     9,    10,     0,    11,     0,
      12,    13,    14,    15,     0,     0,     0,     0,     0,     0,
      16,    17,    18,    19,    20,   -75,    21,     0,    22,     0,
       0,    23,     0,     0,     0,    24,     0,     1,    25,     2,
       3,     4,     0,     0,     5,     6,     7,     8,     9,    10,
       0,    11,     0,    12,    13,    14,    15,     0,     0,     0,
       0,     0,     0,    16,    17,    18,    19,    20,     0,    21,
       0,    22,     2,     3,    23,     0,     0,     0,    24,     0,
       0,    25,     0,     0,    11,     0,    12,    13,    14,    15,
       0,     0,     0,     0,     0,     0,    16,    17,    18,    19,
       0,     0,    21,     0,    22,     2,     3,    52,     0,     0,
       0,    24,     7,     0,    25,     0,     0,    11,     0,    12,
      13,    14,    15,     0,     2,     3,     0,     0,     0,    16,
      17,    18,    19,     0,     0,    21,    11,    22,    12,    13,
      14,    15,     0,     0,    24,     0,     0,    25,    16,    17,
      18,    19,     0,     0,    21,     0,    22,     0,     0,     0,
      81,     0,    82,    24,     0,     0,    25,    83,    84,    85,
      86,    87,    88,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    89,     0,     0,     0,     0,     0,
      90,    91,    92,    93,    94,    81,     0,    82,     0,     0,
       0,     0,    83,    84,    85,    86,    87,    88,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   108,
       0,     0,     0,     0,     0,    90,    91,    92,    93,    94,
      81,     0,    82,     0,     0,     0,     0,    83,    84,    85,
      86,    87,    88,     0,     0,     0,    81,     0,    82,     0,
       0,     0,   119,    83,    84,    85,    86,    87,    88,     0,
      90,    91,    92,    93,    94,     0,     0,     0,   145,     0,
       0,     0,     0,     0,     0,     0,    90,    91,    92,    93,
      94,    81,     0,    82,     0,     0,     0,     0,    83,    84,
      85,    86,    87,    88,     0,     0,     0,    81,     0,    82,
       0,     0,     0,   146,    83,    84,    85,    86,    87,    88,
       0,    90,    91,    92,    93,    94,     0,     0,     0,     0,
       0,     0,   153,     0,     0,     0,     0,    90,    91,    92,
      93,    94,    81,     0,    82,     0,     0,     0,     0,    83,
      84,    85,    86,    87,    88,     0,     0,    81,     0,    82,
       0,     0,   157,     0,    83,    84,    85,    86,    87,    88,
       0,     0,    90,    91,    92,    93,    94,   159,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    90,    91,    92,
      93,    94,    81,     0,    82,     0,     0,     0,     0,    83,
      84,    85,    86,    87,    88,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   172,     0,     0,     0,
       0,     0,    90,    91,    92,    93,    94,    81,     0,    82,
       0,     0,     0,     0,    83,    84,    85,    86,    87,    88,
      81,     0,    82,     0,     0,   174,     0,    83,    84,    85,
      86,    87,    88,     0,     0,    81,     0,    90,    91,    92,
      93,    94,    83,    84,    85,    86,    87,    88,     0,     0,
      90,    91,    92,    93,    94,    83,    84,    85,    86,    87,
      88,     0,     0,     0,     0,    90,    91,    92,    93,    94,
      83,    84,   -76,    86,    87,   -76,     0,     0,    90,    91,
      92,    93,    94,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    90,    91,    92,    93,    94
};

static const yytype_int16 yycheck[] =
{
       8,    33,    22,    11,    33,    49,    35,    38,    40,    27,
      28,    40,    35,    21,    22,    33,    35,    25,    62,    67,
       3,     4,    40,    35,    35,    43,    16,    17,    30,    41,
      16,    17,    15,    38,    17,    18,    19,    20,    58,    47,
      48,    49,    38,    17,    27,    28,    29,    30,    31,     0,
      33,    34,    35,    30,    62,    30,    30,   101,    10,    42,
      68,    35,    45,    35,   112,    46,    47,    48,    42,    30,
      34,    37,    34,    81,    82,    83,    84,    85,    86,    87,
      88,    37,    90,    91,    92,    93,    94,    36,    30,    97,
      30,    30,   100,   101,    31,    38,    37,   145,   146,    31,
      36,    36,    35,    32,    35,    30,   150,     7,   116,    36,
      21,    22,   156,    24,    25,    36,    36,    36,    36,    28,
      77,   118,   104,   171,   112,   176,    -1,    -1,   172,   137,
      -1,    -1,   180,    44,    45,    46,    47,    48,    -1,   147,
      -1,    -1,   150,    -1,    -1,   153,    -1,    -1,   156,    -1,
       0,     1,    -1,     3,     4,     5,    -1,    -1,     8,     9,
      10,    11,    12,    13,   172,    15,    -1,    17,    18,    19,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    27,    28,    29,
      30,    31,    -1,    33,    -1,    35,    -1,    -1,    38,    -1,
      -1,    -1,    42,    -1,     1,    45,     3,     4,     5,    -1,
      -1,     8,     9,    10,    11,    12,    13,    -1,    15,    -1,
      17,    18,    19,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      27,    28,    29,    30,    31,    32,    33,    -1,    35,    -1,
      -1,    38,    -1,    -1,    -1,    42,    -1,     1,    45,     3,
       4,     5,    -1,    -1,     8,     9,    10,    11,    12,    13,
      -1,    15,    -1,    17,    18,    19,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    27,    28,    29,    30,    31,    -1,    33,
      -1,    35,     3,     4,    38,    -1,    -1,    -1,    42,    -1,
      -1,    45,    -1,    -1,    15,    -1,    17,    18,    19,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    27,    28,    29,    30,
      -1,    -1,    33,    -1,    35,     3,     4,    38,    -1,    -1,
      -1,    42,    10,    -1,    45,    -1,    -1,    15,    -1,    17,
      18,    19,    20,    -1,     3,     4,    -1,    -1,    -1,    27,
      28,    29,    30,    -1,    -1,    33,    15,    35,    17,    18,
      19,    20,    -1,    -1,    42,    -1,    -1,    45,    27,    28,
      29,    30,    -1,    -1,    33,    -1,    35,    -1,    -1,    -1,
      14,    -1,    16,    42,    -1,    -1,    45,    21,    22,    23,
      24,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,
      44,    45,    46,    47,    48,    14,    -1,    16,    -1,    -1,
      -1,    -1,    21,    22,    23,    24,    25,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      -1,    -1,    -1,    -1,    -1,    44,    45,    46,    47,    48,
      14,    -1,    16,    -1,    -1,    -1,    -1,    21,    22,    23,
      24,    25,    26,    -1,    -1,    -1,    14,    -1,    16,    -1,
      -1,    -1,    36,    21,    22,    23,    24,    25,    26,    -1,
      44,    45,    46,    47,    48,    -1,    -1,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    46,    47,
      48,    14,    -1,    16,    -1,    -1,    -1,    -1,    21,    22,
      23,    24,    25,    26,    -1,    -1,    -1,    14,    -1,    16,
      -1,    -1,    -1,    36,    21,    22,    23,    24,    25,    26,
      -1,    44,    45,    46,    47,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    44,    45,    46,
      47,    48,    14,    -1,    16,    -1,    -1,    -1,    -1,    21,
      22,    23,    24,    25,    26,    -1,    -1,    14,    -1,    16,
      -1,    -1,    34,    -1,    21,    22,    23,    24,    25,    26,
      -1,    -1,    44,    45,    46,    47,    48,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    46,
      47,    48,    14,    -1,    16,    -1,    -1,    -1,    -1,    21,
      22,    23,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,    -1,
      -1,    -1,    44,    45,    46,    47,    48,    14,    -1,    16,
      -1,    -1,    -1,    -1,    21,    22,    23,    24,    25,    26,
      14,    -1,    16,    -1,    -1,    32,    -1,    21,    22,    23,
      24,    25,    26,    -1,    -1,    14,    -1,    44,    45,    46,
      47,    48,    21,    22,    23,    24,    25,    26,    -1,    -1,
      44,    45,    46,    47,    48,    21,    22,    23,    24,    25,
      26,    -1,    -1,    -1,    -1,    44,    45,    46,    47,    48,
      21,    22,    23,    24,    25,    26,    -1,    -1,    44,    45,
      46,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    44,    45,    46,    47,    48
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,     4,     5,     8,     9,    10,    11,    12,
      13,    15,    17,    18,    19,    20,    27,    28,    29,    30,
      31,    33,    35,    38,    42,    45,    51,    52,    53,    54,
      55,    56,    58,    59,    60,    61,    67,    70,    74,    77,
      78,    79,    83,    84,    85,    86,    38,    35,    35,    35,
      30,    73,    38,    54,    38,    38,    54,    30,    35,    59,
      61,    59,    35,    41,    62,    63,    64,    71,    31,    34,
      54,    65,    66,    68,    69,    54,    77,    30,    54,     0,
      52,    14,    16,    21,    22,    23,    24,    25,    26,    38,
      44,    45,    46,    47,    48,    27,    28,    33,    40,    43,
      33,    35,    40,    35,    75,    54,    54,    65,    38,    77,
      65,    30,    53,    72,    54,    34,    37,    34,    37,    36,
      36,    62,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    30,    57,    54,    65,
      30,    30,    80,    70,    76,    36,    36,    38,    36,    36,
      35,    72,    32,    39,    54,    68,    35,    34,    54,    34,
      36,    37,    81,    36,    53,    53,    54,    65,    54,    65,
      30,     7,    38,    36,    32,    36,    82,    53,    65,    81,
      36,    53
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    51,    52,    52,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    55,    55,    55,    55,    55,    55,    55,    55,    57,
      56,    58,    58,    58,    58,    58,    59,    59,    59,    59,
      59,    60,    60,    60,    60,    61,    61,    61,    62,    62,
      63,    64,    65,    65,    66,    66,    67,    67,    67,    68,
      68,    69,    71,    70,    72,    72,    73,    73,    74,    75,
      76,    77,    78,    78,    78,    78,    78,    79,    79,    80,
      80,    82,    81,    81,    83,    83,    84,    85,    86,    86
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     1,     1,     1,     1,
       2,     2,     1,     1,     1,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     3,     2,     2,     2,     2,     2,     2,     1,     0,
       4,     1,     1,     1,     3,     1,     1,     2,     3,     2,
       1,     3,     4,     3,     4,     4,     2,     6,     1,     1,
       3,     5,     1,     0,     3,     1,     3,     3,     2,     1,
       3,     5,     0,     4,     2,     0,     1,     0,     2,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     2,
       0,     0,     4,     0,     7,     5,     5,     9,     3,     2
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


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

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

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
  case 4: /* parsing: %empty  */
#line 83 "parser.y"
                                        {}
#line 1673 "parser.c"
    break;

  case 5: /* stmt: expr SEMICOLON  */
#line 86 "parser.y"
                                    {printf("reset\n");resettemp();}
#line 1679 "parser.c"
    break;

  case 6: /* stmt: ifstmt  */
#line 87 "parser.y"
                                    {resettemp();}
#line 1685 "parser.c"
    break;

  case 7: /* stmt: whilestmt  */
#line 88 "parser.y"
                                    {resettemp();}
#line 1691 "parser.c"
    break;

  case 8: /* stmt: forstmt  */
#line 89 "parser.y"
                                    {resettemp();}
#line 1697 "parser.c"
    break;

  case 9: /* stmt: returnstmt  */
#line 90 "parser.y"
                                    {resettemp();}
#line 1703 "parser.c"
    break;

  case 10: /* stmt: KEYWORD_BREAK SEMICOLON  */
#line 91 "parser.y"
                                              {if(scope == 0) yyerror("Use of 'break' while not in a loop\n");resettemp();}
#line 1709 "parser.c"
    break;

  case 11: /* stmt: KEYWORD_CONTINUE SEMICOLON  */
#line 92 "parser.y"
                                                 {if(scope == 0) yyerror("Use of 'continue' while not in a loop\n");resettemp();}
#line 1715 "parser.c"
    break;

  case 12: /* stmt: block  */
#line 93 "parser.y"
                            { (yyval.stringv) = (yyvsp[0].unsignedv);   resettemp();}
#line 1721 "parser.c"
    break;

  case 13: /* stmt: funcdef  */
#line 94 "parser.y"
                              { resettemp();}
#line 1727 "parser.c"
    break;

  case 14: /* stmt: SEMICOLON  */
#line 95 "parser.y"
                                {}
#line 1733 "parser.c"
    break;

  case 15: /* stmt: error SEMICOLON  */
#line 96 "parser.y"
                                        { yyerrok; }
#line 1739 "parser.c"
    break;

  case 16: /* expr: expr '+' expr  */
#line 99 "parser.y"
                                      {(yyval.expression) = Manage_operations((yyvsp[-2].expression),add,(yyvsp[0].expression));}
#line 1745 "parser.c"
    break;

  case 17: /* expr: expr '*' expr  */
#line 100 "parser.y"
                                      {(yyval.expression) = Manage_operations((yyvsp[-2].expression),mul,(yyvsp[0].expression));}
#line 1751 "parser.c"
    break;

  case 18: /* expr: expr '-' expr  */
#line 101 "parser.y"
                                      {(yyval.expression) = Manage_operations((yyvsp[-2].expression),sub,(yyvsp[0].expression));}
#line 1757 "parser.c"
    break;

  case 19: /* expr: expr '/' expr  */
#line 102 "parser.y"
                                      {(yyval.expression) = Manage_operations((yyvsp[-2].expression),divv,(yyvsp[0].expression));}
#line 1763 "parser.c"
    break;

  case 20: /* expr: expr '%' expr  */
#line 103 "parser.y"
                                      {(yyval.expression) = Manage_operations((yyvsp[-2].expression),mod,(yyvsp[0].expression));}
#line 1769 "parser.c"
    break;

  case 21: /* expr: expr GREATER expr  */
#line 104 "parser.y"
                                          {(yyval.expression) = Manage_comparisonopers((yyvsp[-2].expression), ">",(yyvsp[0].expression));}
#line 1775 "parser.c"
    break;

  case 22: /* expr: expr GREATER_EQUAL expr  */
#line 105 "parser.y"
                                              {(yyval.expression) = Manage_comparisonopers((yyvsp[-2].expression), ">=",(yyvsp[0].expression));}
#line 1781 "parser.c"
    break;

  case 23: /* expr: expr LESS expr  */
#line 106 "parser.y"
                                      {(yyval.expression) = Manage_comparisonopers((yyvsp[-2].expression), "<",(yyvsp[0].expression));}
#line 1787 "parser.c"
    break;

  case 24: /* expr: expr LESS_EQUAL expr  */
#line 107 "parser.y"
                                             {(yyval.expression) = Manage_comparisonopers((yyvsp[-2].expression), "<=",(yyvsp[0].expression));}
#line 1793 "parser.c"
    break;

  case 25: /* expr: expr EQUALS expr  */
#line 108 "parser.y"
                                        {(yyval.expression) = Manage_comparisonopers((yyvsp[-2].expression), "==",(yyvsp[0].expression));}
#line 1799 "parser.c"
    break;

  case 26: /* expr: expr NOT_EQUAL expr  */
#line 109 "parser.y"
                                          {(yyval.expression) = Manage_comparisonopers((yyvsp[-2].expression), "!=",(yyvsp[0].expression));}
#line 1805 "parser.c"
    break;

  case 29: /* expr: assignexpr  */
#line 112 "parser.y"
                                 { (yyval.expression) = (yyvsp[0].expression);}
#line 1811 "parser.c"
    break;

  case 30: /* expr: term  */
#line 113 "parser.y"
                            { (yyval.expression) = emit_iftableitem((yyvsp[0].expression));}
#line 1817 "parser.c"
    break;

  case 31: /* term: LEFTPARENTHESIS expr RIGHTPARENTHESIS  */
#line 117 "parser.y"
                                                            {(yyval.expression) = (yyvsp[-1].expression);}
#line 1823 "parser.c"
    break;

  case 32: /* term: '-' expr  */
#line 118 "parser.y"
                                             {
                                                check_arith((yyvsp[0].expression),(const char*)"- expr");
                                                (yyval.expression) = newexpr(arithexpr_e);
                                                (yyval.expression)->sym = newtemp();
                                    
                                                emit(uminus,(yyvsp[0].expression),NULL,(yyval.expression),0,yylineno);
                                             }
#line 1835 "parser.c"
    break;

  case 33: /* term: KEYWORD_NOT expr  */
#line 125 "parser.y"
                                       {
                                            (yyval.expression) = newexpr(boolexpr_e);
                                            (yyval.expression)->sym = newtemp();
                                            emit(not,(yyvsp[0].expression),NULL,(yyval.expression),0,yylineno);
                                            
                                        }
#line 1846 "parser.c"
    break;

  case 34: /* term: INCREMENT lvalue  */
#line 131 "parser.y"
                                       {entry=lookup((yyvsp[0].expression), scope); if(!entry); else if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("Cannot increment a function");}
#line 1852 "parser.c"
    break;

  case 35: /* term: lvalue INCREMENT  */
#line 132 "parser.y"
                                       {entry=lookup((yyvsp[-1].expression), scope); if(!entry); else if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("Cannot increment a function");}
#line 1858 "parser.c"
    break;

  case 36: /* term: DECREMENT lvalue  */
#line 133 "parser.y"
                                       {entry=lookup((yyvsp[0].expression), scope); if(!entry); else if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("Cannot decrement a function");}
#line 1864 "parser.c"
    break;

  case 37: /* term: lvalue DECREMENT  */
#line 134 "parser.y"
                                       {entry=lookup((yyvsp[-1].expression), scope); if(!entry); else if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("Cannot decrement a function");}
#line 1870 "parser.c"
    break;

  case 38: /* term: primary  */
#line 135 "parser.y"
                              { (yyval.expression) = (yyvsp[0].expression); }
#line 1876 "parser.c"
    break;

  case 39: /* $@1: %empty  */
#line 138 "parser.y"
 {
    if( entry == NULL ){
        if(scope > 0 )
        entry = lookup_hidden((yyvsp[-1].expression),scope);
        /* ERROR9.asc -> ACCESSING FORMAL IN ANOTHER SCOPE*/
        if(entry){
            if(entry->type == FORMAL){
                yyerror("cannot access formal argument in another scope");
            }else if(entry->type == LOCAL){
                yyerror("Cannot access local variable in another scope");
            }
        }else{
            if(scope==0){
                insert((yyvsp[-1].expression), GLOBAL, scope, yylineno);
            }else{
                insert((yyvsp[-1].expression), LOCAL, scope, yylineno);  
            }
        }
        
    }
    else if( entry->type == LIBFUNC || entry->type == USERFUNC) yyerror("Cannot assign to a function");

}
#line 1904 "parser.c"
    break;

  case 40: /* assignexpr: lvalue '=' $@1 expr  */
#line 161 "parser.y"
     {
    if((yyvsp[-3].expression)->type == tableitem_e){
        emit(tablesetelem, (yyvsp[-3].expression), (yyvsp[-3].expression)->index, (yyvsp[0].expression), 0U, yylineno);
        (yyval.expression) = emit_iftableitem((yyvsp[-3].expression));
        (yyval.expression)->type = assignexpr_e;
    }
    else{
        expr *temp = (yyvsp[0].expression);
        emit(assign, (yyvsp[0].expression), NULL, (yyvsp[-3].expression), 0U, yylineno);
        (yyval.expression) = newexpr(assignexpr_e);
        (yyval.expression)->sym = newtemp();
        emit(assign, (yyvsp[-3].expression), NULL,(yyval.expression), 0U, yylineno);
        
    }
}
#line 1924 "parser.c"
    break;

  case 41: /* primary: lvalue  */
#line 181 "parser.y"
                            {(yyval.expression) = emit_iftableitem((yyvsp[0].expression));}
#line 1930 "parser.c"
    break;

  case 45: /* primary: const  */
#line 185 "parser.y"
                            {(yyval.expression) = (yyvsp[0].expression);}
#line 1936 "parser.c"
    break;

  case 46: /* lvalue: IDENTIFIER  */
#line 188 "parser.y"
                                        {    
                                                entry = lookup_in_scope((yyvsp[0].stringv), scope);                                                                                                // else if(entry->type == LIBFUNC) {
                                                //     yyerror("Cannot assign to a library function");
                                                // }
                                                // else if(entry->type == USERFUNC) {
                                                //     yyerror("Cannot assign to a user function");
                                                // }

                                                //phase3                                               
                                                //sym = lookup($1, scope);
                                                if(entry == NULL) {
                                                    entry = (scope == 0) ? insert((yyvsp[0].stringv), GLOBAL, 0, yylineno) : insert((yyvsp[0].stringv), LOCAL, scope, yylineno); 
                                                    entry->space = currscopespace();
                                                    entry->offset = currscopeoffset();
                                                    inccurrscopeoffset();
                                                }
                                                (yyval.expression) = lvalue_expr(entry);
                                                (yyval.expression)->sym = entry;

                                        }
#line 1961 "parser.c"
    break;

  case 47: /* lvalue: KEYWORD_LOCAL IDENTIFIER  */
#line 209 "parser.y"
                                               {  
                                                    int flag = 0;                                               
                                                    entry = lookup((yyvsp[0].stringv), scope);
                                                    if(entry != NULL){
                                                        if(entry->type == LIBFUNC) yyerror("Cannot shadow a library function");                                                                      
                                                        // else if(scope == 0){
                                                        //     yyerror("Cannot shadow a global variable");
                                                        // }
                                                        else flag =1;
                                                        goto end;
                                                    }
                                                    else {
                                                        //if(scope==0) yyerror("Cannot shadow a global variable");
                                                        flag = 1;
                                                        goto end;
                                                    }
                                                
                                                    end:
                                                    if(flag == 1) {
                                                        entry = lookup_in_scope((yyvsp[0].stringv), scope);
                                                        if(entry == NULL) entry = insert((yyvsp[0].stringv), LOCAL, scope, yylineno);                                                   
                                                        else yyerror("Cannot shadow a local variable"); 
                                                    }

                                                    //phase 3
                                                    sym = lookup_in_scope((yyvsp[0].stringv), scope);
                                                    if (sym == NULL){
                                                        sym = (scope == 0) ? insert((yyvsp[0].stringv), GLOBAL, 0, yylineno) : insert((yyvsp[0].stringv), LOCAL, scope, yylineno); 
                                                        sym->space = currscopespace();
                                                        sym->offset = currscopeoffset();
                                                        inccurrscopeoffset();
                                                    } else {
                                                        if(sym->type == USERFUNC || sym->type == LIBFUNC ){
                                                            printf(BOLD_RED"sym is a function\n"RESET);
                                                        }

                                                    }
                                                    (yyval.expression) = lvalue_expr(sym);                                                                                                                                      
                                                    
                                                }
#line 2006 "parser.c"
    break;

  case 48: /* lvalue: DOUBLECOLON IDENTIFIER callsuffix  */
#line 252 "parser.y"
                                                        {
                                                            entry = lookup_in_scope((yyvsp[-1].stringv), 0); 
                                                            if(entry == NULL) yyerror("global identifier not found");
                                                            
                                                        }
#line 2016 "parser.c"
    break;

  case 49: /* lvalue: DOUBLECOLON IDENTIFIER  */
#line 259 "parser.y"
                                               {
                                                    entry = lookup_in_scope((yyvsp[0].stringv), 0); 
                                            
                                                        char error_message[256];
                                                        sprintf(error_message, "global identifier not found %s", (yyvsp[0].stringv));
                                                        if (entry == NULL || !entry->isActive) yyerror(error_message);

                                                }
#line 2029 "parser.c"
    break;

  case 50: /* lvalue: member  */
#line 267 "parser.y"
                             {(yyval.expression) = (yyvsp[0].expression);}
#line 2035 "parser.c"
    break;

  case 51: /* member: lvalue DOT IDENTIFIER  */
#line 269 "parser.y"
                                            { 
                                            if (entry == NULL || !entry->isActive) yyerror("member error" );
                                            else if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("function member error: lvalue.id");
                                            (yyval.expression) = member_item((yyvsp[-2].expression), (yyvsp[0].stringv));
                                            }
#line 2045 "parser.c"
    break;

  case 52: /* member: lvalue LEFTBRACKET expr RIGHTBRACKET  */
#line 274 "parser.y"
                                                           { 
                                            expr* tmp;
                                            if (entry == NULL || !entry->isActive) yyerror("member error");
                                            else if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("function member error: lvalue[expr]");
                                            (yyvsp[-3].expression) = emit_iftableitem((yyvsp[-3].expression));
                                            tmp = newexpr(tableitem_e);
                                            tmp->sym = (yyvsp[-3].expression)->sym;
                                            tmp->index = (yyvsp[-1].expression);
                                            (yyval.expression) = tmp;
                                            }
#line 2060 "parser.c"
    break;

  case 56: /* call: IDENTIFIER callsuffix  */
#line 289 "parser.y"
                                            {
                                                // int temp = scope-1;
                                                // while(temp >= 0){
                                                //     entry = lookup_in_scope($1, temp);
                                                //     if(entry != NULL) break;
                                                //     temp--;
                                                // }
                                                // if(entry == NULL) yyerror("Cannot call function");
                                                // else if(entry->type != LIBFUNC || entry->type != USERFUNC) yyerror("not a function");
                    }
#line 2075 "parser.c"
    break;

  case 57: /* call: LEFTPARENTHESIS funcdef RIGHTPARENTHESIS LEFTPARENTHESIS elist RIGHTPARENTHESIS  */
#line 299 "parser.y"
                                                                                                      {printf("call -> (funcdef)(elist)");}
#line 2081 "parser.c"
    break;

  case 63: /* elist: %empty  */
#line 310 "parser.y"
                                        {}
#line 2087 "parser.c"
    break;

  case 72: /* $@2: %empty  */
#line 333 "parser.y"
                               { scope++; }
#line 2093 "parser.c"
    break;

  case 73: /* block: LEFTBRACE $@2 blockk RIGHTBRACE  */
#line 333 "parser.y"
                                                               { scope--; }
#line 2099 "parser.c"
    break;

  case 75: /* blockk: %empty  */
#line 337 "parser.y"
                                        {}
#line 2105 "parser.c"
    break;

  case 76: /* funcname: IDENTIFIER  */
#line 340 "parser.y"
                     {
                        
                        if(scope < 0) scope = 0;
                        entry = lookup_in_scope((yyvsp[0].stringv), scope); 

                        int temp = scope;
                        while(temp >= 0){
                            hide_scope(temp);
                            temp--;
                        }
                     
                       //libfuncs
                        if (entry != NULL) {
                            //check collision with library/user functions or formals
                            if (entry->type == LIBFUNC) yyerror("library function collision");
                            else if (entry->type == USERFUNC) yyerror("user function collision");
                            else if (entry->type == FORMAL) yyerror("function name already defined as formal");
                            
                        }
                        else {
                            //entry = lookup_in_scope_hidden($<stringv>2, scope);
                            //if(!entry) yyerror("variable already defined"); 
                            //else{ 
                                entry = insert((yyvsp[0].stringv), USERFUNC, scope, yylineno);
                                scope++;
                            //} 
                        }
                        (yyval.sym) = entry;
                        (yyval.sym)->value.funcVal->name = entry->value.funcVal->name;
                    }
#line 2140 "parser.c"
    break;

  case 77: /* funcname: %empty  */
#line 371 "parser.y"
                  { 
                        int temp = scope;
                        while(temp != 0){
                        hide_scope(temp);
                        temp--;
                        }

                        char str[20]; 
                        sprintf(str, "_%d", anonymousCounter++); 
                        entry = insert(str, USERFUNC, scope, yylineno); 
                        scope++; // increment scope here

                        (yyval.sym) = entry;
                        (yyval.sym)->value.funcVal->name = entry->value.funcVal->name;

                    }
#line 2161 "parser.c"
    break;

  case 78: /* funcprefix: KEYWORD_FUNCTION funcname  */
#line 388 "parser.y"
                                      {
                                        (yyval.sym) = (yyvsp[0].sym);
                                        (yyval.sym)->iaddress = nextquadlabel();

                                        emit(jump, NULL, NULL, NULL, 0, yylineno);
                                        emit(funcstart, lvalue_expr((yyval.sym)), NULL, NULL,0, yylineno);
                                        push(scopeoffsetstack, currscopeoffset());
                                        print(scopeoffsetstack);
                                        enterscopespace();
                                        resetformalargsoffset();
                                       }
#line 2177 "parser.c"
    break;

  case 79: /* funcargs: LEFTPARENTHESIS idlist RIGHTPARENTHESIS  */
#line 403 "parser.y"
                                                  {
                                                     scope--;
                                                     enterscopespace();
                                                     resetfunctionlocalsoffset();
                                                     (yyval.sym) = (yyvsp[-1].sym);
                                                  }
#line 2188 "parser.c"
    break;

  case 80: /* funcbody: block  */
#line 409 "parser.y"
                {
                 (yyval.unsignedv) = currscopeoffset();
                 exitscopespace();
                 //slide 6 mathima 10
                }
#line 2198 "parser.c"
    break;

  case 81: /* funcdef: funcprefix funcargs funcbody  */
#line 415 "parser.y"
                                         {
                                            exitscopespace();
                                            (yyval.sym)->totalLocals = (yyvsp[0].unsignedv);
                                            print(scopeoffsetstack);
                                            int offset = pop(scopeoffsetstack);
                                            restorecurrscopeoffset(offset);
                                            (yyval.sym) = (yyvsp[-2].sym);
                                            SymbolTableEntry *temp = (yyvsp[-2].sym);

                                            emit(funcend, lvalue_expr((yyvsp[-2].sym)), NULL, NULL, 0U, yylineno);
                                            patchlabel((yyvsp[-2].sym)->iaddress, nextquadlabel()+1);


}
#line 2217 "parser.c"
    break;

  case 83: /* const: STRING  */
#line 432 "parser.y"
                                            { (yyval.expression) = newexpr_conststring(yylval.stringv); }
#line 2223 "parser.c"
    break;

  case 84: /* const: KEYWORD_NIL  */
#line 433 "parser.y"
                                            { (yyval.expression) = newexpr_nil(yylval.stringv);  }
#line 2229 "parser.c"
    break;

  case 85: /* const: KEYWORD_TRUE  */
#line 434 "parser.y"
                                            { 
                                              expr *temp = newexpr_bool(yylval.stringv);
                                              (yyval.expression) = temp;
                    
                                            }
#line 2239 "parser.c"
    break;

  case 86: /* const: KEYWORD_FALSE  */
#line 439 "parser.y"
                                            { (yyval.expression) = newexpr_bool(yylval.stringv); }
#line 2245 "parser.c"
    break;

  case 87: /* number: "integer constant"  */
#line 441 "parser.y"
                                            { (yyval.stringv) = newexpr_constnum(yylval.intv); }
#line 2251 "parser.c"
    break;

  case 88: /* number: "real contstant"  */
#line 442 "parser.y"
                                            { (yyval.stringv) = newexpr_constnum(yylval.floatv); }
#line 2257 "parser.c"
    break;

  case 89: /* idlist: IDENTIFIER ids  */
#line 446 "parser.y"
                                     {  
                                    entry = lookup((yyvsp[-1].stringv), scope); //lookup in function scope
                                    if(entry != NULL) {
                                        if (entry->type == LIBFUNC) {
                                            yyerror("library function collision");
                                        }
                                    } else {  
                                        entry = insert((yyvsp[-1].stringv),FORMAL,scope,yylineno);     
                                    }
                                    (yyval.sym) = (yyvsp[-1].stringv);

                                }
#line 2274 "parser.c"
    break;

  case 90: /* idlist: %empty  */
#line 458 "parser.y"
                                             {}
#line 2280 "parser.c"
    break;

  case 91: /* $@3: %empty  */
#line 461 "parser.y"
                                      {  
                                    printf("scope is %d\n", scope);

                                    entry = lookup(yylval.stringv, scope); //lookup in function scope
                                    if(entry != NULL) {
                                        if (entry->type == LIBFUNC) {
                                            yyerror("library function collision");
                                        }else if(strcmp((yyvsp[-1].stringv), entry->value.varVal->name) == 0) {
                                            yyerror("formal collision");
                                        }
                                    } else {
                                        entry = insert((yyvsp[0].stringv),FORMAL,scope,yylineno);     
                                    }
                                }
#line 2299 "parser.c"
    break;

  case 93: /* ids: %empty  */
#line 475 "parser.y"
                                             {}
#line 2305 "parser.c"
    break;

  case 98: /* returnstmt: KEYWORD_RETURN expr SEMICOLON  */
#line 485 "parser.y"
                                                   {
                                                    if(scope == 0) yyerror("Use of 'return' while not in a function\n");
                                                    emit(ret, NULL, NULL, (yyvsp[-1].expression), 0, yylineno);
                                                    (yyval.stringv) = currQuad;
                                                    emit(jump, NULL, NULL, NULL, (yyval.stringv)->iaddress, yylineno);
                                                  
                                                    }
#line 2317 "parser.c"
    break;

  case 99: /* returnstmt: KEYWORD_RETURN SEMICOLON  */
#line 492 "parser.y"
                                               {
                                                if(scope == 0) yyerror("Use of 'return' while not in a fucntion\n");
                                                emit(ret, NULL, NULL, NULL, 0, yylineno);
                                                emit(jump, NULL, NULL, NULL, (yyvsp[-1].stringv)->iaddress, yylineno);

                                                }
#line 2328 "parser.c"
    break;


#line 2332 "parser.c"

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 499 "parser.y"

int yyerror (char* yaccProvidedMessage) {
    fprintf(stderr, "%s: at line %d, before token: %s\n",yaccProvidedMessage,yylineno,yytext);
    fprintf(stderr,"INPUT NOT VALID\n");
    return 1;
}

//**************************************************************

int main(int argc,char **argv){
    //yydebug = 1;
    symTable = SymTable_new();
    initialize_scope_links();
    insert_libfuncs();
    char *libfuncs[12] = {"print", "input", "objectmemberkeys", "objecttotalmembers", "objectcopy", "totalarguments", "argument", "typeof", "strtonum", "sqrt", "cos", "sin"};
    
    scopeoffsetstack = malloc(sizeof(Stack));
    if (scopeoffsetstack == NULL) {
        fprintf(stderr, "Failed to allocate memory for scopeoffsetstack\n");
        return 1;
    }
    initialize(scopeoffsetstack);

    if(argc > 1){
        if(!(yyin = fopen(argv[1],"r"))){
            fprintf(stderr,"Cannot open file\n");
            return 1;
        }
    }else{
        yyin = stdin;
    }
    yyparse();

    printf("PRINTING SYMBOL TABLE \n");
    print_scope_links();

    printf("PRINTING QUADS\n");
    print_quads();

    SymTable_free(symTable);
    free_scope_links();
    return 0;
}