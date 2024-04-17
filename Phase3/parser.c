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
    #define YYDEBUG 1
    //#define YYLEX alpha_yylex
    #include "quads.h"
    extern int yydebug;
    int yyerror (char* yaccProvidedMessage);
    int alpha_yylex(void* yylval);
    SymbolTableEntry *entry;
    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;

    SymTable_T symTable = NULL;
    int anonymousCounter = 0;
    int scope = 0;
    int called = 0;
    int doublec_flag = 0;

#line 91 "parser.c"

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
  YYSYMBOL_obj = 68,                       /* obj  */
  YYSYMBOL_indexed = 69,                   /* indexed  */
  YYSYMBOL_indexedelem = 70,               /* indexedelem  */
  YYSYMBOL_block = 71,                     /* block  */
  YYSYMBOL_72_2 = 72,                      /* $@2  */
  YYSYMBOL_blockk = 73,                    /* blockk  */
  YYSYMBOL_funcdef = 74,                   /* funcdef  */
  YYSYMBOL_75_3 = 75,                      /* $@3  */
  YYSYMBOL_76_4 = 76,                      /* $@4  */
  YYSYMBOL_77_5 = 77,                      /* $@5  */
  YYSYMBOL_78_6 = 78,                      /* $@6  */
  YYSYMBOL_const = 79,                     /* const  */
  YYSYMBOL_number = 80,                    /* number  */
  YYSYMBOL_idlist = 81,                    /* idlist  */
  YYSYMBOL_ids = 82,                       /* ids  */
  YYSYMBOL_83_7 = 83,                      /* $@7  */
  YYSYMBOL_ifstmt = 84,                    /* ifstmt  */
  YYSYMBOL_whilestmt = 85,                 /* whilestmt  */
  YYSYMBOL_forstmt = 86,                   /* forstmt  */
  YYSYMBOL_returnstmt = 87,                /* returnstmt  */
  YYSYMBOL_88_8 = 88,                      /* $@8  */
  YYSYMBOL_89_9 = 89                       /* $@9  */
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
#define YYLAST   588

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  101
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  186

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
       0,    67,    67,    69,    70,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     103,   104,   110,   116,   117,   118,   119,   120,   122,   122,
     146,   147,   148,   149,   150,   153,   167,   207,   214,   222,
     224,   229,   233,   234,   237,   238,   248,   251,   252,   254,
     256,   258,   259,   262,   263,   267,   268,   271,   272,   275,
     276,   279,   281,   281,   284,   285,   288,   317,   288,   318,
     331,   318,   334,   334,   334,   334,   334,   336,   337,   341,
     352,   355,   355,   367,   370,   371,   373,   375,   377,   377,
     378,   378
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
  "normcall", "methodcall", "elist", "exprlist", "objectdef", "obj",
  "indexed", "indexedelem", "block", "$@2", "blockk", "funcdef", "$@3",
  "$@4", "$@5", "$@6", "const", "number", "idlist", "ids", "$@7", "ifstmt",
  "whilestmt", "forstmt", "returnstmt", "$@8", "$@9", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-165)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-101)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     231,   -36,  -165,  -165,   -30,    -2,    -1,    -6,     0,     7,
       8,    93,    18,  -165,  -165,  -165,   -10,   -10,  -165,   -29,
    -165,   264,   297,  -165,    31,    93,    44,  -165,   145,     5,
    -165,  -165,  -165,    14,  -165,    25,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,  -165,    93,    93,    93,  -165,
      27,    93,    30,  -165,  -165,    69,  -165,    59,   -32,    25,
     -32,    93,    48,  -165,  -165,  -165,   188,    93,  -165,   512,
    -165,    46,    50,  -165,    61,   322,    63,   -29,  -165,  -165,
    -165,    93,    93,    93,    93,    93,    93,    93,    93,  -165,
      93,    93,    93,    93,  -165,  -165,    93,    70,  -165,    93,
      93,    71,   338,   367,    64,    72,    75,   383,  -165,    78,
      79,    82,   188,    74,   412,    93,  -165,    87,  -165,    84,
    -165,   354,   527,    42,    42,   418,    42,    42,   418,   540,
      69,    69,    69,   441,  -165,    93,   456,    91,  -165,   231,
     231,    93,    75,    94,    96,  -165,    84,  -165,    93,  -165,
    -165,    93,   512,  -165,    93,  -165,   512,  -165,  -165,   126,
    -165,   470,    98,   106,  -165,  -165,   103,   499,   105,   231,
      93,  -165,  -165,   111,  -165,  -165,  -165,  -165,   108,   111,
      94,  -165,   231,  -165,  -165,  -165
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    87,    88,     0,     0,     0,    79,    98,     0,
       0,     0,     0,    85,    86,    84,     0,     0,    83,    45,
      72,     0,     0,    14,     0,     0,     0,     2,     0,     0,
      29,    28,    37,    40,    49,    41,    42,    12,    13,    44,
      82,     6,     7,     8,     9,    15,     0,     0,    62,    76,
       0,     0,     0,    10,    11,    32,    46,     0,    33,     0,
      35,    62,     0,    55,    57,    58,     0,     0,    66,    64,
      67,    61,     0,    68,    70,     0,     0,    48,    31,     1,
       3,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       0,     0,     0,     0,    34,    36,     0,     0,    38,     0,
      62,     0,     0,     0,     0,     0,    90,     0,   101,     0,
       0,     0,     0,     0,     0,     0,    65,     0,    30,    43,
      47,    26,    27,    20,    22,    24,    21,    23,    25,    16,
      17,    18,    19,     0,    50,     0,     0,     0,    52,     0,
       0,     0,    90,    93,     0,    99,     0,    59,    62,    74,
      73,     0,    63,    69,    62,    51,    39,    53,    54,    95,
      96,     0,     0,     0,    89,    80,     0,     0,     0,     0,
      62,    77,    91,     0,    60,    71,    56,    94,     0,     0,
      93,    81,     0,    78,    92,    97
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -165,  -165,   119,   -53,   -11,  -165,  -165,  -165,  -165,     1,
    -165,     6,    89,  -165,  -165,   -45,  -165,  -165,  -165,    34,
    -165,  -164,  -165,    40,   -18,  -165,  -165,  -165,  -165,  -165,
    -165,    19,   -13,  -165,  -165,  -165,  -165,  -165,  -165,  -165
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    26,    27,    28,    29,    30,    31,   135,    32,    33,
      34,    35,    63,    64,    65,    70,    71,    36,    72,    73,
      74,    37,    66,   113,    38,   105,   179,    50,   173,    39,
      40,   144,   164,   180,    41,    42,    43,    44,    51,    52
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      55,    96,    45,   104,    76,    46,    61,    12,    97,   181,
      69,    75,    62,   112,    78,   183,   110,    58,    60,    81,
      19,    82,    59,    59,    49,    57,    83,    84,    85,    86,
      87,    88,    24,    47,    48,   102,   103,    69,  -100,   109,
     107,    94,    95,    89,    79,    53,    54,    96,    56,    90,
      69,    91,    92,    93,    97,   137,   114,    98,    99,   112,
     100,    77,   106,  -101,  -101,   101,  -101,  -101,   108,     7,
     121,   122,   123,   124,   125,   126,   127,   128,   111,   129,
     130,   131,   132,   115,   116,   133,   159,   160,   136,    69,
      83,    84,    85,    86,    87,    88,     2,     3,   117,   119,
     134,   138,   141,   166,   152,   143,   150,   142,    11,   168,
      12,    13,    14,    15,   146,   147,   177,   148,    67,   154,
      16,    17,    18,    19,   156,   178,    21,   158,    22,   185,
     161,   163,   165,   169,   171,    24,   172,    69,    25,   174,
     167,   176,    20,    69,   182,    -4,     1,    80,     2,     3,
       4,   153,   149,     5,     6,     7,     8,     9,    10,    69,
      11,   162,    12,    13,    14,    15,   120,   184,     0,     0,
       0,     0,    16,    17,    18,    19,    20,     0,    21,     0,
      22,     0,     0,    23,     0,     0,     0,    24,     0,     1,
      25,     2,     3,     4,     0,     0,     5,     6,     7,     8,
       9,    10,     0,    11,     0,    12,    13,    14,    15,     0,
       0,     0,     0,     0,     0,    16,    17,    18,    19,    20,
     -75,    21,     0,    22,     0,     0,    23,     0,     0,     0,
      24,     0,     1,    25,     2,     3,     4,     0,     0,     5,
       6,     7,     8,     9,    10,     0,    11,     0,    12,    13,
      14,    15,     0,     0,     0,     0,     0,     0,    16,    17,
      18,    19,    20,     0,    21,     0,    22,     2,     3,    23,
       0,     0,     0,    24,     0,     0,    25,     0,     0,    11,
       0,    12,    13,    14,    15,     0,     0,     0,     0,     0,
       0,    16,    17,    18,    19,    67,     0,    21,    68,    22,
       2,     3,     0,     0,     0,     0,    24,     7,     0,    25,
       0,     0,    11,     0,    12,    13,    14,    15,     0,     0,
       0,     0,     0,     0,    16,    17,    18,    19,     0,     0,
      21,     0,    22,     0,     0,     0,    81,     0,    82,    24,
       0,     0,    25,    83,    84,    85,    86,    87,    88,     0,
       0,     0,    81,     0,    82,     0,     0,     0,   118,    83,
      84,    85,    86,    87,    88,     0,    90,     0,    91,    92,
      93,     0,     0,     0,   139,    83,    84,    85,    86,    87,
      88,    81,    90,    82,    91,    92,    93,     0,    83,    84,
      85,    86,    87,    88,     0,     0,     0,    81,    90,    82,
      91,    92,    93,   140,    83,    84,    85,    86,    87,    88,
       0,    90,     0,    91,    92,    93,     0,     0,     0,     0,
       0,   145,     0,     0,     0,     0,    81,    90,    82,    91,
      92,    93,     0,    83,    84,    85,    86,    87,    88,    83,
      84,  -101,    86,    87,  -101,     0,     0,     0,     0,     0,
       0,   151,     0,     0,     0,    81,    90,    82,    91,    92,
      93,     0,    83,    84,    85,    86,    87,    88,     0,     0,
      81,     0,    82,     0,     0,   155,     0,    83,    84,    85,
      86,    87,    88,     0,    81,    90,    82,    91,    92,    93,
     157,    83,    84,    85,    86,    87,    88,     0,     0,     0,
      90,     0,    91,    92,    93,     0,     0,     0,   170,     0,
       0,     0,     0,    81,    90,    82,    91,    92,    93,     0,
      83,    84,    85,    86,    87,    88,    81,     0,    82,     0,
       0,   175,     0,    83,    84,    85,    86,    87,    88,     0,
       0,    81,     0,    90,     0,    91,    92,    93,    83,    84,
      85,    86,    87,    88,     0,     0,    90,     0,    91,    92,
      93,    83,    84,    85,    86,    87,    88,     0,     0,     0,
       0,    90,     0,    91,    92,    93,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    91,    92,    93
};

static const yytype_int16 yycheck[] =
{
      11,    33,    38,    48,    22,    35,    35,    17,    40,   173,
      21,    22,    41,    66,    25,   179,    61,    16,    17,    14,
      30,    16,    16,    17,    30,    35,    21,    22,    23,    24,
      25,    26,    42,    35,    35,    46,    47,    48,    38,    57,
      51,    27,    28,    38,     0,    38,    38,    33,    30,    44,
      61,    46,    47,    48,    40,   100,    67,    43,    33,   112,
      35,    30,    35,    21,    22,    40,    24,    25,    38,    10,
      81,    82,    83,    84,    85,    86,    87,    88,    30,    90,
      91,    92,    93,    37,    34,    96,   139,   140,    99,   100,
      21,    22,    23,    24,    25,    26,     3,     4,    37,    36,
      30,    30,    38,   148,   115,    30,    32,    35,    15,   154,
      17,    18,    19,    20,    36,    36,   169,    35,    31,    35,
      27,    28,    29,    30,   135,   170,    33,    36,    35,   182,
     141,    37,    36,     7,    36,    42,    30,   148,    45,    36,
     151,    36,    31,   154,    36,     0,     1,    28,     3,     4,
       5,   117,   112,     8,     9,    10,    11,    12,    13,   170,
      15,   142,    17,    18,    19,    20,    77,   180,    -1,    -1,
      -1,    -1,    27,    28,    29,    30,    31,    -1,    33,    -1,
      35,    -1,    -1,    38,    -1,    -1,    -1,    42,    -1,     1,
      45,     3,     4,     5,    -1,    -1,     8,     9,    10,    11,
      12,    13,    -1,    15,    -1,    17,    18,    19,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    27,    28,    29,    30,    31,
      32,    33,    -1,    35,    -1,    -1,    38,    -1,    -1,    -1,
      42,    -1,     1,    45,     3,     4,     5,    -1,    -1,     8,
       9,    10,    11,    12,    13,    -1,    15,    -1,    17,    18,
      19,    20,    -1,    -1,    -1,    -1,    -1,    -1,    27,    28,
      29,    30,    31,    -1,    33,    -1,    35,     3,     4,    38,
      -1,    -1,    -1,    42,    -1,    -1,    45,    -1,    -1,    15,
      -1,    17,    18,    19,    20,    -1,    -1,    -1,    -1,    -1,
      -1,    27,    28,    29,    30,    31,    -1,    33,    34,    35,
       3,     4,    -1,    -1,    -1,    -1,    42,    10,    -1,    45,
      -1,    -1,    15,    -1,    17,    18,    19,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    27,    28,    29,    30,    -1,    -1,
      33,    -1,    35,    -1,    -1,    -1,    14,    -1,    16,    42,
      -1,    -1,    45,    21,    22,    23,    24,    25,    26,    -1,
      -1,    -1,    14,    -1,    16,    -1,    -1,    -1,    36,    21,
      22,    23,    24,    25,    26,    -1,    44,    -1,    46,    47,
      48,    -1,    -1,    -1,    36,    21,    22,    23,    24,    25,
      26,    14,    44,    16,    46,    47,    48,    -1,    21,    22,
      23,    24,    25,    26,    -1,    -1,    -1,    14,    44,    16,
      46,    47,    48,    36,    21,    22,    23,    24,    25,    26,
      -1,    44,    -1,    46,    47,    48,    -1,    -1,    -1,    -1,
      -1,    38,    -1,    -1,    -1,    -1,    14,    44,    16,    46,
      47,    48,    -1,    21,    22,    23,    24,    25,    26,    21,
      22,    23,    24,    25,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    14,    44,    16,    46,    47,
      48,    -1,    21,    22,    23,    24,    25,    26,    -1,    -1,
      14,    -1,    16,    -1,    -1,    34,    -1,    21,    22,    23,
      24,    25,    26,    -1,    14,    44,    16,    46,    47,    48,
      34,    21,    22,    23,    24,    25,    26,    -1,    -1,    -1,
      44,    -1,    46,    47,    48,    -1,    -1,    -1,    38,    -1,
      -1,    -1,    -1,    14,    44,    16,    46,    47,    48,    -1,
      21,    22,    23,    24,    25,    26,    14,    -1,    16,    -1,
      -1,    32,    -1,    21,    22,    23,    24,    25,    26,    -1,
      -1,    14,    -1,    44,    -1,    46,    47,    48,    21,    22,
      23,    24,    25,    26,    -1,    -1,    44,    -1,    46,    47,
      48,    21,    22,    23,    24,    25,    26,    -1,    -1,    -1,
      -1,    44,    -1,    46,    47,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    47,    48
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,     4,     5,     8,     9,    10,    11,    12,
      13,    15,    17,    18,    19,    20,    27,    28,    29,    30,
      31,    33,    35,    38,    42,    45,    51,    52,    53,    54,
      55,    56,    58,    59,    60,    61,    67,    71,    74,    79,
      80,    84,    85,    86,    87,    38,    35,    35,    35,    30,
      77,    88,    89,    38,    38,    54,    30,    35,    59,    61,
      59,    35,    41,    62,    63,    64,    72,    31,    34,    54,
      65,    66,    68,    69,    70,    54,    74,    30,    54,     0,
      52,    14,    16,    21,    22,    23,    24,    25,    26,    38,
      44,    46,    47,    48,    27,    28,    33,    40,    43,    33,
      35,    40,    54,    54,    65,    75,    35,    54,    38,    74,
      65,    30,    53,    73,    54,    37,    34,    37,    36,    36,
      62,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    30,    57,    54,    65,    30,    36,
      36,    38,    35,    30,    81,    38,    36,    36,    35,    73,
      32,    39,    54,    69,    35,    34,    54,    34,    36,    53,
      53,    54,    81,    37,    82,    36,    65,    54,    65,     7,
      38,    36,    30,    78,    36,    32,    36,    53,    65,    76,
      83,    71,    36,    71,    82,    53
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    51,    52,    52,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      55,    55,    55,    55,    55,    55,    55,    55,    57,    56,
      58,    58,    58,    58,    58,    59,    59,    59,    59,    59,
      60,    60,    60,    60,    61,    61,    61,    62,    62,    63,
      64,    65,    65,    66,    66,    67,    67,    68,    68,    69,
      69,    70,    72,    71,    73,    73,    75,    76,    74,    77,
      78,    74,    79,    79,    79,    79,    79,    80,    80,    81,
      81,    83,    82,    82,    84,    84,    85,    86,    88,    87,
      89,    87
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     1,     1,     1,     1,
       2,     2,     1,     1,     1,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       3,     2,     2,     2,     2,     2,     2,     1,     0,     4,
       1,     1,     1,     3,     1,     1,     2,     3,     2,     1,
       3,     4,     3,     4,     4,     2,     6,     1,     1,     3,
       5,     1,     0,     3,     1,     3,     2,     1,     1,     3,
       1,     5,     0,     4,     2,     0,     0,     0,     8,     0,
       0,     7,     1,     1,     1,     1,     1,     1,     1,     2,
       0,     0,     4,     0,     7,     5,     5,     9,     0,     4,
       0,     3
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
  case 10: /* stmt: KEYWORD_BREAK SEMICOLON  */
#line 78 "parser.y"
                                              {if(scope == 0) yyerror("Use of 'break' while not in a loop\n");}
#line 1647 "parser.c"
    break;

  case 11: /* stmt: KEYWORD_CONTINUE SEMICOLON  */
#line 79 "parser.y"
                                                 {if(scope == 0) yyerror("Use of 'continue' while not in a loop\n");}
#line 1653 "parser.c"
    break;

  case 15: /* stmt: error SEMICOLON  */
#line 83 "parser.y"
                                        { yyerrok; }
#line 1659 "parser.c"
    break;

  case 31: /* term: '-' expr  */
#line 104 "parser.y"
                                             {
                                                check_arith((yyvsp[0].stringv),(const char*)"- expr");
                                                (yyval.expression) = newexpr(arithexpr_e);
                                                (yyval.expression)->sym = newtemp();
                                                emit(uminus,(yyvsp[0].stringv),NULL,(yyval.expression),0,yylineno);
                                             }
#line 1670 "parser.c"
    break;

  case 32: /* term: KEYWORD_NOT expr  */
#line 110 "parser.y"
                                       {
                                            (yyval.expression) = newexpr(boolexpr_e);
                                            (yyval.expression)->sym = newtemp();
                                            emit(not,(yyvsp[0].stringv),NULL,(yyval.expression),0,yylineno);
                                            
                                        }
#line 1681 "parser.c"
    break;

  case 33: /* term: INCREMENT lvalue  */
#line 116 "parser.y"
                                       {entry=lookup((yyvsp[0].stringv), scope); if(!entry); else if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("Cannot increment a function");}
#line 1687 "parser.c"
    break;

  case 34: /* term: lvalue INCREMENT  */
#line 117 "parser.y"
                                       {entry=lookup((yyvsp[-1].stringv), scope); if(!entry); else if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("Cannot increment a function");}
#line 1693 "parser.c"
    break;

  case 35: /* term: DECREMENT lvalue  */
#line 118 "parser.y"
                                       {entry=lookup((yyvsp[0].stringv), scope); if(!entry); else if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("Cannot decrement a function");}
#line 1699 "parser.c"
    break;

  case 36: /* term: lvalue DECREMENT  */
#line 119 "parser.y"
                                       {entry=lookup((yyvsp[-1].stringv), scope); if(!entry); else if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("Cannot decrement a function");}
#line 1705 "parser.c"
    break;

  case 38: /* $@1: %empty  */
#line 122 "parser.y"
                                {
    if( entry == NULL ){
        if(scope > 0 )
        entry = lookup_hidden((yyvsp[-1].stringv),scope);
        /* ERROR9.asc -> ACCESSING FORMAL IN ANOTHER SCOPE*/
        if(entry){
            if(entry->type == FORMAL){
                yyerror("cannot access formal argument in another scope");
            }else if(entry->type == LOCAL){
                yyerror("Cannot access local variable in another scope");
            }
        }else{
            if(scope==0){
                insert((yyvsp[-1].stringv), GLOBAL, scope, yylineno);
            }else{
                insert((yyvsp[-1].stringv), LOCAL, scope, yylineno);  
            }
        }
        
    }
    else if( entry->type == LIBFUNC || entry->type == USERFUNC) yyerror("Cannot assign to a function");
}
#line 1732 "parser.c"
    break;

  case 45: /* lvalue: IDENTIFIER  */
#line 153 "parser.y"
                                        {    
                                                
                                                entry = lookup_in_scope((yyvsp[0].stringv), scope);
                                                if(entry == NULL) {                                                
                                                }
                                                // else if(entry->type == LIBFUNC) {
                                                //     yyerror("Cannot assign to a library function");
                                                // }
                                                // else if(entry->type == USERFUNC) {
                                                //     yyerror("Cannot assign to a user function");
                                                // }
                                                
                                        }
#line 1750 "parser.c"
    break;

  case 46: /* lvalue: KEYWORD_LOCAL IDENTIFIER  */
#line 167 "parser.y"
                                               {  
                                                int flag = 0;
                                                
                                                    entry = lookup((yyvsp[0].stringv), scope);

                                                    if(entry != NULL){
                                                        if(entry->type == LIBFUNC){
                                                            yyerror("Cannot shadow a library function");
                                    
                                                        }
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
                                                            if(entry == NULL) {
                                                                entry = insert((yyvsp[0].stringv), LOCAL, scope, yylineno);
                                                            }
                                                            else {
                                                                yyerror("Cannot shadow a local variable");
                                                            }
                                                       }                                                                                    
                                                        
                                                    
                                                }
#line 1792 "parser.c"
    break;

  case 47: /* lvalue: DOUBLECOLON IDENTIFIER callsuffix  */
#line 207 "parser.y"
                                                        {
                                                            entry = lookup_in_scope((yyvsp[-1].stringv), 0); 
                                                            if(entry == NULL) yyerror("global identifier not found");
                                                            
                                                        }
#line 1802 "parser.c"
    break;

  case 48: /* lvalue: DOUBLECOLON IDENTIFIER  */
#line 214 "parser.y"
                                               {
                                                    entry = lookup_in_scope((yyvsp[0].stringv), 0); 
                                            
                                                        char error_message[256];
                                                        sprintf(error_message, "global identifier not found %s", (yyvsp[0].stringv));
                                                        if (entry == NULL || !entry->isActive) yyerror(error_message);

                                                }
#line 1815 "parser.c"
    break;

  case 50: /* member: lvalue DOT IDENTIFIER  */
#line 224 "parser.y"
                                            { 
                                            if (entry == NULL || !entry->isActive) yyerror("member error" );
                                            else if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("function member error: lvalue.id");

                                            }
#line 1825 "parser.c"
    break;

  case 51: /* member: lvalue LEFTBRACKET expr RIGHTBRACKET  */
#line 229 "parser.y"
                                                           { 
                                            if (entry == NULL || !entry->isActive) yyerror("member error");
                                            else if(entry->type == USERFUNC || entry->type == LIBFUNC) yyerror("function member error: lvalue[expr]");
                                            }
#line 1834 "parser.c"
    break;

  case 55: /* call: IDENTIFIER callsuffix  */
#line 238 "parser.y"
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
#line 1849 "parser.c"
    break;

  case 56: /* call: LEFTPARENTHESIS funcdef RIGHTPARENTHESIS LEFTPARENTHESIS elist RIGHTPARENTHESIS  */
#line 248 "parser.y"
                                                                                                      {printf("call -> (funcdef)(elist)");}
#line 1855 "parser.c"
    break;

  case 62: /* elist: %empty  */
#line 259 "parser.y"
                                        {}
#line 1861 "parser.c"
    break;

  case 72: /* $@2: %empty  */
#line 281 "parser.y"
                               { scope++; }
#line 1867 "parser.c"
    break;

  case 73: /* block: LEFTBRACE $@2 blockk RIGHTBRACE  */
#line 281 "parser.y"
                                                               { scope--; }
#line 1873 "parser.c"
    break;

  case 75: /* blockk: %empty  */
#line 285 "parser.y"
                                        {}
#line 1879 "parser.c"
    break;

  case 76: /* $@3: %empty  */
#line 288 "parser.y"
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
                    }
#line 1913 "parser.c"
    break;

  case 77: /* $@4: %empty  */
#line 317 "parser.y"
                                                            { scope--; }
#line 1919 "parser.c"
    break;

  case 79: /* $@5: %empty  */
#line 318 "parser.y"
                                        { 
                        int temp = scope;
                        printf("scope %d\n", scope);
                        while(temp != 0){
                        hide_scope(temp);
                        temp--;
                        }

                        char str[20]; 
                        sprintf(str, "_%d", anonymousCounter++); 
                        entry = insert(str, USERFUNC, scope, yylineno); 
                        scope++; // increment scope here
                    }
#line 1937 "parser.c"
    break;

  case 80: /* $@6: %empty  */
#line 331 "parser.y"
                                                            { scope--; }
#line 1943 "parser.c"
    break;

  case 89: /* idlist: IDENTIFIER ids  */
#line 341 "parser.y"
                                     {  
                                    
                                    entry = lookup((yyvsp[-1].stringv), scope); //lookup in function scope
                                    if(entry != NULL) {
                                        if (entry->type == LIBFUNC) {
                                            yyerror("library function collision");
                                        }
                                    } else {  
                                        entry = insert((yyvsp[-1].stringv),FORMAL,scope,yylineno);     
                                    }
                                }
#line 1959 "parser.c"
    break;

  case 90: /* idlist: %empty  */
#line 352 "parser.y"
                                             {}
#line 1965 "parser.c"
    break;

  case 91: /* $@7: %empty  */
#line 355 "parser.y"
                                      {  
                                    entry = lookup((yyvsp[0].stringv), scope); //lookup in function scope
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
#line 1982 "parser.c"
    break;

  case 93: /* ids: %empty  */
#line 367 "parser.y"
                                             {}
#line 1988 "parser.c"
    break;

  case 98: /* $@8: %empty  */
#line 377 "parser.y"
                                   {if(scope == 0) yyerror("Use of 'return' while not in a loop\n");}
#line 1994 "parser.c"
    break;

  case 100: /* $@9: %empty  */
#line 378 "parser.y"
                                     {if(scope == 0) yyerror("Use of 'return' while not in a loop\n");}
#line 2000 "parser.c"
    break;


#line 2004 "parser.c"

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

#line 380 "parser.y"

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
    SymTable_free(symTable);
    free_scope_links();
    return 0;
}
