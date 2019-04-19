/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENT = 258,
     CHARLIT = 259,
     STRING = 260,
     NUMBER = 261,
     INDSEL = 262,
     PLUSPLUS = 263,
     MINUSMINUS = 264,
     SHL = 265,
     SHR = 266,
     LTEQ = 267,
     GTEQ = 268,
     EQEQ = 269,
     NOTEQ = 270,
     LOGAND = 271,
     LOGOR = 272,
     ELLIPSIS = 273,
     TIMESEQ = 274,
     DIVEQ = 275,
     MODEQ = 276,
     PLUSEQ = 277,
     MINUSEQ = 278,
     SHLEQ = 279,
     SHREQ = 280,
     ANDEQ = 281,
     OREQ = 282,
     XOREQ = 283,
     AUTO = 284,
     BREAK = 285,
     CASE = 286,
     CHAR = 287,
     CONST = 288,
     CONTINUE = 289,
     DEFAULT = 290,
     DO = 291,
     DOUBLE = 292,
     ELSE = 293,
     ENUM = 294,
     EXTERN = 295,
     FLOAT = 296,
     FOR = 297,
     GOTO = 298,
     IF = 299,
     INLINE = 300,
     INT = 301,
     LONG = 302,
     REGISTER = 303,
     RESTRICT = 304,
     RETURN = 305,
     SHORT = 306,
     SIGNED = 307,
     SIZEOF = 308,
     STATIC = 309,
     STRUCT = 310,
     SWITCH = 311,
     TYPEDEF = 312,
     UNION = 313,
     UNSIGNED = 314,
     VOID = 315,
     VOLATILE = 316,
     WHILE = 317,
     _BOOL = 318,
     _COMPLEX = 319,
     _IMAGINARY = 320
   };
#endif
/* Tokens.  */
#define IDENT 258
#define CHARLIT 259
#define STRING 260
#define NUMBER 261
#define INDSEL 262
#define PLUSPLUS 263
#define MINUSMINUS 264
#define SHL 265
#define SHR 266
#define LTEQ 267
#define GTEQ 268
#define EQEQ 269
#define NOTEQ 270
#define LOGAND 271
#define LOGOR 272
#define ELLIPSIS 273
#define TIMESEQ 274
#define DIVEQ 275
#define MODEQ 276
#define PLUSEQ 277
#define MINUSEQ 278
#define SHLEQ 279
#define SHREQ 280
#define ANDEQ 281
#define OREQ 282
#define XOREQ 283
#define AUTO 284
#define BREAK 285
#define CASE 286
#define CHAR 287
#define CONST 288
#define CONTINUE 289
#define DEFAULT 290
#define DO 291
#define DOUBLE 292
#define ELSE 293
#define ENUM 294
#define EXTERN 295
#define FLOAT 296
#define FOR 297
#define GOTO 298
#define IF 299
#define INLINE 300
#define INT 301
#define LONG 302
#define REGISTER 303
#define RESTRICT 304
#define RETURN 305
#define SHORT 306
#define SIGNED 307
#define SIZEOF 308
#define STATIC 309
#define STRUCT 310
#define SWITCH 311
#define TYPEDEF 312
#define UNION 313
#define UNSIGNED 314
#define VOID 315
#define VOLATILE 316
#define WHILE 317
#define _BOOL 318
#define _COMPLEX 319
#define _IMAGINARY 320




/* Copy the first part of user declarations.  */
#line 2 "parser.y"
	/* Parser */
#include "ast.h"
#include "sym_tab.h"
#include <stdio.h>
#include <stdlib.h>

int yylex();
extern int lineno;
extern char file[256];
void yyerror(const char* msg) {fprintf(stderr, "%s:%d: %s\n", file, lineno, msg);}
char* print_kw(int token);
struct symbol_table *curr_scope;
struct symbol *curr_symbol;
int symbol_exists;



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 19 "parser.y"
{ /* Definition of yylval union */
		
		struct identifier {
			char *name;
		} ident;

		struct string_literal {
			char word[4096];
			int length;
		} string;

		struct number {
			unsigned long long int_value;
			long double float_value;
			int sign;
			int type;
		} num;

		char char_lit;

		union astnode *astnode_p;
		struct symbol *temp;

}
/* Line 193 of yacc.c.  */
#line 268 "parser.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 281 "parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  95
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1910

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  90
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  128
/* YYNRULES -- Number of rules.  */
#define YYNRULES  316
/* YYNRULES -- Number of states.  */
#define YYNSTATES  484

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   320

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    80,     2,     2,     2,    84,    82,     2,
      69,    70,    71,    79,    67,    78,    76,    83,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    77,    66,
      85,    68,    86,    89,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    72,     2,    73,    88,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    74,    87,    75,    81,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,     9,    12,    14,    17,    19,    22,
      24,    28,    30,    34,    36,    38,    40,    42,    44,    46,
      48,    50,    52,    54,    56,    58,    60,    62,    64,    68,
      70,    72,    74,    77,    79,    82,    85,    89,    91,    94,
      98,   103,   108,   112,   117,   119,   123,   125,   129,   132,
     134,   137,   139,   143,   145,   149,   154,   156,   160,   163,
     168,   171,   173,   176,   180,   183,   185,   187,   189,   191,
     193,   196,   199,   203,   205,   208,   210,   212,   215,   218,
     222,   225,   229,   233,   238,   241,   245,   247,   250,   253,
     257,   261,   266,   268,   271,   274,   276,   278,   280,   283,
     285,   288,   291,   295,   297,   299,   304,   310,   316,   323,
     326,   328,   330,   334,   336,   340,   342,   344,   346,   347,
     353,   354,   361,   364,   366,   368,   371,   375,   377,   381,
     383,   385,   387,   390,   394,   396,   398,   400,   405,   411,
     414,   416,   418,   420,   423,   425,   427,   430,   434,   437,
     441,   445,   450,   454,   459,   463,   468,   471,   475,   479,
     484,   486,   488,   490,   492,   494,   496,   500,   502,   504,
     506,   508,   510,   512,   514,   519,   523,   527,   531,   536,
     538,   542,   545,   548,   555,   563,   565,   570,   572,   574,
     576,   578,   580,   582,   584,   586,   588,   590,   595,   598,
     601,   604,   607,   610,   613,   616,   619,   622,   624,   628,
     632,   636,   638,   642,   646,   648,   652,   656,   658,   662,
     666,   670,   674,   676,   680,   684,   686,   690,   692,   696,
     698,   702,   704,   708,   710,   714,   716,   722,   724,   728,
     730,   732,   734,   736,   738,   740,   742,   744,   746,   748,
     750,   752,   756,   758,   760,   762,   764,   766,   768,   770,
     772,   774,   776,   778,   780,   782,   784,   786,   788,   791,
     795,   797,   799,   801,   804,   805,   810,   812,   815,   817,
     819,   825,   833,   839,   847,   851,   856,   862,   868,   875,
     881,   888,   895,   903,   905,   907,   913,   916,   918,   921,
     924,   927,   931,   935,   937,   939,   941,   944,   946,   948,
     949,   955,   957,   960,   963,   967,   969
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     212,     0,    -1,    92,    93,    66,    -1,    95,    -1,    95,
      92,    -1,    96,    -1,    96,    92,    -1,    97,    -1,    97,
      92,    -1,    94,    -1,    93,    67,    94,    -1,    98,    -1,
      98,    68,   110,    -1,    29,    -1,    40,    -1,    54,    -1,
     122,    -1,   120,    -1,   115,    -1,   129,    -1,   142,    -1,
     146,    -1,    33,    -1,    61,    -1,    49,    -1,   101,    -1,
      99,    -1,   100,    -1,    69,    98,    70,    -1,   105,    -1,
     104,    -1,     3,    -1,   102,    99,    -1,    71,    -1,    71,
     103,    -1,    71,   102,    -1,    71,   103,   102,    -1,    97,
      -1,   103,    97,    -1,    99,    72,    73,    -1,    99,    72,
     182,    73,    -1,    99,    69,   106,    70,    -1,    99,    69,
      70,    -1,    99,    69,   109,    70,    -1,   107,    -1,   107,
      67,    18,    -1,   108,    -1,   107,    67,   108,    -1,    92,
      98,    -1,    92,    -1,    92,   148,    -1,     3,    -1,   107,
      67,     3,    -1,   183,    -1,    74,   111,    75,    -1,    74,
     111,    67,    75,    -1,   110,    -1,   111,    67,   110,    -1,
     112,   110,    -1,   111,    67,   112,   110,    -1,   113,    68,
      -1,   114,    -1,   113,   114,    -1,    72,   182,    73,    -1,
      76,     3,    -1,   116,    -1,   117,    -1,   118,    -1,   119,
      -1,    51,    -1,    51,    46,    -1,    52,    51,    -1,    52,
      51,    46,    -1,    46,    -1,    52,    46,    -1,    52,    -1,
      47,    -1,    47,    46,    -1,    52,    47,    -1,    52,    47,
      46,    -1,    47,    47,    -1,    47,    47,    46,    -1,    52,
      47,    47,    -1,    52,    47,    47,    46,    -1,    59,    51,
      -1,    59,    51,    46,    -1,    59,    -1,    59,    46,    -1,
      59,    47,    -1,    59,    47,    46,    -1,    59,    47,    47,
      -1,    59,    47,    47,    46,    -1,    32,    -1,    52,    32,
      -1,    59,    32,    -1,    63,    -1,    41,    -1,    37,    -1,
      47,    37,    -1,   121,    -1,    41,    64,    -1,    37,    64,
      -1,    47,    37,    64,    -1,   123,    -1,   124,    -1,    39,
      74,   126,    75,    -1,    39,    74,   126,    67,    75,    -1,
      39,   125,    74,   126,    75,    -1,    39,   125,    74,   126,
      67,    75,    -1,    39,   125,    -1,     3,    -1,   127,    -1,
     126,    67,   127,    -1,   128,    -1,   128,    68,   185,    -1,
       3,    -1,   130,    -1,   133,    -1,    -1,    55,    74,   131,
     135,    75,    -1,    -1,    55,   134,    74,   132,   135,    75,
      -1,    55,   134,    -1,     3,    -1,   136,    -1,   135,   136,
      -1,    96,   137,    66,    -1,   138,    -1,   137,    67,   138,
      -1,   139,    -1,   140,    -1,    98,    -1,    77,   141,    -1,
      98,    77,   141,    -1,   182,    -1,   143,    -1,   144,    -1,
      58,    74,   135,    75,    -1,    58,   145,    74,   135,    75,
      -1,    58,   145,    -1,     3,    -1,    60,    -1,    92,    -1,
      92,   148,    -1,   102,    -1,   149,    -1,   102,   149,    -1,
      69,   148,    70,    -1,    72,    73,    -1,    72,   182,    73,
      -1,   149,    72,    73,    -1,   149,    72,   182,    73,    -1,
      72,   185,    73,    -1,   149,    72,   185,    73,    -1,    72,
      71,    73,    -1,   149,    72,    71,    73,    -1,    69,    70,
      -1,    69,   106,    70,    -1,   149,    69,    70,    -1,   149,
      69,   106,    70,    -1,     3,    -1,   151,    -1,   152,    -1,
       6,    -1,     4,    -1,     5,    -1,    69,   185,    70,    -1,
     150,    -1,   154,    -1,   155,    -1,   156,    -1,   158,    -1,
     159,    -1,   160,    -1,   153,    72,   185,    73,    -1,   153,
      76,     3,    -1,   153,     7,     3,    -1,   153,    69,    70,
      -1,   153,    69,   157,    70,    -1,   183,    -1,   157,    67,
     183,    -1,   153,     8,    -1,   153,     9,    -1,    69,   147,
      70,    74,   111,    75,    -1,    69,   147,    70,    74,   111,
      67,    75,    -1,   162,    -1,    69,   147,    70,   161,    -1,
     153,    -1,   163,    -1,   164,    -1,   165,    -1,   166,    -1,
     167,    -1,   168,    -1,   169,    -1,   170,    -1,   171,    -1,
      53,    69,   147,    70,    -1,    53,   162,    -1,    78,   161,
      -1,    79,   161,    -1,    80,   161,    -1,    81,   161,    -1,
      82,   161,    -1,    71,   161,    -1,     8,   162,    -1,     9,
     162,    -1,   161,    -1,   172,    71,   161,    -1,   172,    83,
     161,    -1,   172,    84,   161,    -1,   172,    -1,   173,    79,
     172,    -1,   173,    78,   172,    -1,   173,    -1,   174,    10,
     173,    -1,   174,    11,   173,    -1,   174,    -1,   175,    85,
     174,    -1,   175,    12,   174,    -1,   175,    86,   174,    -1,
     175,    13,   174,    -1,   175,    -1,   176,    14,   175,    -1,
     176,    15,   175,    -1,   178,    -1,   177,    87,   178,    -1,
     179,    -1,   178,    88,   179,    -1,   176,    -1,   179,    82,
     176,    -1,   181,    -1,   180,    17,   181,    -1,   177,    -1,
     181,    16,   177,    -1,   180,    -1,   180,    89,   185,    77,
     182,    -1,   182,    -1,   162,   184,   183,    -1,    68,    -1,
      22,    -1,    23,    -1,    19,    -1,    20,    -1,    21,    -1,
      24,    -1,    25,    -1,    26,    -1,    28,    -1,    27,    -1,
     183,    -1,   185,    67,   183,    -1,   189,    -1,   190,    -1,
     192,    -1,   187,    -1,   188,    -1,   203,    -1,   206,    -1,
     207,    -1,   208,    -1,   209,    -1,   211,    -1,   196,    -1,
     197,    -1,   199,    -1,   198,    -1,   200,    -1,   185,    66,
      -1,   191,    77,   186,    -1,   210,    -1,   204,    -1,   205,
      -1,    74,    75,    -1,    -1,    74,   193,   194,    75,    -1,
     195,    -1,   194,   195,    -1,    91,    -1,   186,    -1,    44,
      69,   185,    70,   186,    -1,    44,    69,   185,    70,   186,
      38,   186,    -1,    62,    69,   185,    70,   186,    -1,    36,
     186,    62,    69,   185,    70,    66,    -1,    42,   201,   186,
      -1,    69,    66,    66,    70,    -1,    69,    66,    66,   185,
      70,    -1,    69,    66,   185,    66,    70,    -1,    69,    66,
     185,    66,   185,    70,    -1,    69,   202,    66,    66,    70,
      -1,    69,   202,    66,    66,   185,    70,    -1,    69,   202,
      66,   185,    66,    70,    -1,    69,   202,    66,   185,    66,
     185,    70,    -1,   185,    -1,    91,    -1,    56,    69,   185,
      70,   186,    -1,    31,   182,    -1,    35,    -1,    30,    66,
      -1,    34,    66,    -1,    50,    66,    -1,    50,   185,    66,
      -1,    43,   210,    66,    -1,     3,    -1,    66,    -1,   213,
      -1,   212,   213,    -1,    91,    -1,   214,    -1,    -1,   216,
      74,   215,   194,    75,    -1,    98,    -1,    98,   217,    -1,
      92,    98,    -1,    92,    98,   217,    -1,    91,    -1,   217,
      91,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   118,   118,   289,   291,   294,   295,   298,   299,   304,
     305,   310,   311,   314,   318,   322,   328,   329,   330,   331,
     333,   334,   337,   338,   339,   342,   343,   346,   347,   348,
     349,   352,   374,   379,   383,   387,   391,   397,   398,   401,
     408,   426,   427,   433,   436,   437,   440,   441,   444,   445,
     446,   449,   450,   453,   454,   455,   458,   459,   460,   461,
     464,   467,   468,   472,   473,   478,   483,   488,   493,   496,
     497,   498,   499,   500,   501,   502,   503,   504,   505,   506,
     507,   508,   509,   510,   513,   514,   515,   516,   517,   518,
     519,   520,   523,   524,   525,   528,   531,   536,   541,   546,
     549,   550,   551,   554,   555,   558,   559,   560,   561,   564,
     567,   570,   571,   574,   575,   578,   581,   582,   585,   585,
     592,   592,   605,   608,   632,   633,   636,   715,   716,   719,
     720,   723,   726,   727,   731,   734,   735,   738,   739,   742,
     745,   748,   758,   761,   764,   765,   766,   769,   770,   771,
     772,   773,   774,   775,   776,   777,   778,   779,   780,   781,
     786,   790,   791,   794,   801,   805,   812,   815,   816,   817,
     818,   819,   820,   821,   824,   835,   841,   854,   859,   866,
     867,   877,   884,   891,   892,   895,   896,   899,   900,   901,
     902,   903,   904,   905,   906,   907,   908,   911,   915,   921,
     928,   935,   942,   949,   956,   963,   982,  1001,  1002,  1008,
    1014,  1022,  1023,  1029,  1037,  1038,  1044,  1052,  1053,  1059,
    1065,  1071,  1079,  1080,  1086,  1094,  1095,  1103,  1104,  1112,
    1113,  1121,  1122,  1130,  1131,  1139,  1140,  1148,  1149,  1183,
    1184,  1185,  1186,  1187,  1188,  1189,  1190,  1191,  1192,  1193,
    1196,  1197,  1208,  1209,  1210,  1211,  1212,  1213,  1214,  1215,
    1216,  1217,  1218,  1221,  1222,  1225,  1226,  1227,  1230,  1252,
    1259,  1260,  1261,  1264,  1265,  1265,  1273,  1274,  1277,  1278,
    1281,  1290,  1298,  1306,  1313,  1319,  1320,  1321,  1322,  1323,
    1324,  1325,  1326,  1329,  1330,  1333,  1340,  1346,  1349,  1352,
    1355,  1359,  1365,  1372,  1384,  1389,  1390,  1393,  1394,  1397,
    1397,  1419,  1422,  1423,  1500,  1503,  1504
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENT", "CHARLIT", "STRING", "NUMBER",
  "INDSEL", "PLUSPLUS", "MINUSMINUS", "SHL", "SHR", "LTEQ", "GTEQ", "EQEQ",
  "NOTEQ", "LOGAND", "LOGOR", "ELLIPSIS", "TIMESEQ", "DIVEQ", "MODEQ",
  "PLUSEQ", "MINUSEQ", "SHLEQ", "SHREQ", "ANDEQ", "OREQ", "XOREQ", "AUTO",
  "BREAK", "CASE", "CHAR", "CONST", "CONTINUE", "DEFAULT", "DO", "DOUBLE",
  "ELSE", "ENUM", "EXTERN", "FLOAT", "FOR", "GOTO", "IF", "INLINE", "INT",
  "LONG", "REGISTER", "RESTRICT", "RETURN", "SHORT", "SIGNED", "SIZEOF",
  "STATIC", "STRUCT", "SWITCH", "TYPEDEF", "UNION", "UNSIGNED", "VOID",
  "VOLATILE", "WHILE", "_BOOL", "_COMPLEX", "_IMAGINARY", "';'", "','",
  "'='", "'('", "')'", "'*'", "'['", "']'", "'{'", "'}'", "'.'", "':'",
  "'-'", "'+'", "'!'", "'~'", "'&'", "'/'", "'%'", "'<'", "'>'", "'|'",
  "'^'", "'?'", "$accept", "declaration", "declaration_specifiers",
  "initialized_declarator_list", "initialized_declarator",
  "storage_class_specifier", "type_specifier", "type_qualifier",
  "declarator", "direct_declarator", "simple_declarator",
  "pointer_declarator", "pointer", "type_qualifier_list",
  "array_declarator", "function_declarator", "parameter_type_list",
  "parameter_list", "parameter_declaration", "identifier_list",
  "initializer", "initializer_list", "designation", "designator_list",
  "designator", "integer_type_specifier", "signed_type_specifier",
  "unsigned_type_specifier", "character_type_specifier",
  "bool_type_specifier", "floating_point_type_specifier",
  "complex_type_specifier", "enum_type_specifier", "enum_type_definition",
  "enum_type_reference", "enum_tag", "enum_definition_list",
  "enum_constant_definition", "enum_constant", "structure_type_specifier",
  "structure_type_definition", "@1", "@2", "structure_type_reference",
  "structure_tag", "field_list", "component_declaration",
  "component_declarator_list", "component_declarator", "simple_component",
  "bit_field", "width", "union_type_specifier", "union_type_definition",
  "union_type_reference", "union_tag", "void_type_specifier", "type_name",
  "abstract_declarator", "direct_abstract_declarator",
  "primary_expression", "constant", "parenthesized_expression",
  "postfix_expression", "subscript_expression",
  "component_selection_expression", "function_call", "expression_list",
  "postincrement_expression", "postdecrement_expression",
  "compound_literal", "cast_expression", "unary_expression",
  "sizeof_expression", "unary_minus_expression", "unary_plus_expression",
  "logical_negation_expression", "bitwise_negation_expression",
  "address_expression", "indirection_expression",
  "preincrement_expression", "predecrement_expression",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "bitwise_or_expression",
  "bitwise_xor_expression", "bitwise_and_expression",
  "logical_or_expression", "logical_and_expression",
  "conditional_expression", "assignment_expression", "assignment_op",
  "expression", "statement", "conditional_statement",
  "iterative_statement", "expression_statement", "labeled_statement",
  "label", "compound_statement", "@3", "declaration_or_statement_list",
  "declaration_or_statement", "if_statement", "if_else_statement",
  "while_statement", "do_statement", "for_statement", "for_expressions",
  "initial_clause", "switch_statement", "case_label", "default_label",
  "break_statement", "continue_statement", "return_statement",
  "goto_statement", "named_label", "null_statement", "translation_unit",
  "top_level_declaration", "function_definition", "@4",
  "function_def_specifier", "declaration_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,    59,    44,    61,    40,
      41,    42,    91,    93,   123,   125,    46,    58,    45,    43,
      33,   126,    38,    47,    37,    60,    62,   124,    94,    63
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    90,    91,    92,    92,    92,    92,    92,    92,    93,
      93,    94,    94,    95,    95,    95,    96,    96,    96,    96,
      96,    96,    97,    97,    97,    98,    98,    99,    99,    99,
      99,   100,   101,   102,   102,   102,   102,   103,   103,   104,
     104,   105,   105,   105,   106,   106,   107,   107,   108,   108,
     108,   109,   109,   110,   110,   110,   111,   111,   111,   111,
     112,   113,   113,   114,   114,   115,   115,   115,   115,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   117,   117,   117,   117,   117,   117,
     117,   117,   118,   118,   118,   119,   120,   120,   120,   120,
     121,   121,   121,   122,   122,   123,   123,   123,   123,   124,
     125,   126,   126,   127,   127,   128,   129,   129,   131,   130,
     132,   130,   133,   134,   135,   135,   136,   137,   137,   138,
     138,   139,   140,   140,   141,   142,   142,   143,   143,   144,
     145,   146,   147,   147,   148,   148,   148,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     150,   150,   150,   151,   151,   151,   152,   153,   153,   153,
     153,   153,   153,   153,   154,   155,   155,   156,   156,   157,
     157,   158,   159,   160,   160,   161,   161,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   163,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   172,   172,
     172,   173,   173,   173,   174,   174,   174,   175,   175,   175,
     175,   175,   176,   176,   176,   177,   177,   178,   178,   179,
     179,   180,   180,   181,   181,   182,   182,   183,   183,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     185,   185,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   187,   187,   188,   188,   188,   189,   190,
     191,   191,   191,   192,   193,   192,   194,   194,   195,   195,
     196,   197,   198,   199,   200,   201,   201,   201,   201,   201,
     201,   201,   201,   202,   202,   203,   204,   205,   206,   207,
     208,   208,   209,   210,   211,   212,   212,   213,   213,   215,
     214,   216,   216,   216,   216,   217,   217
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     1,     2,     1,     2,     1,     2,     1,
       3,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     2,     1,     2,     2,     3,     1,     2,     3,
       4,     4,     3,     4,     1,     3,     1,     3,     2,     1,
       2,     1,     3,     1,     3,     4,     1,     3,     2,     4,
       2,     1,     2,     3,     2,     1,     1,     1,     1,     1,
       2,     2,     3,     1,     2,     1,     1,     2,     2,     3,
       2,     3,     3,     4,     2,     3,     1,     2,     2,     3,
       3,     4,     1,     2,     2,     1,     1,     1,     2,     1,
       2,     2,     3,     1,     1,     4,     5,     5,     6,     2,
       1,     1,     3,     1,     3,     1,     1,     1,     0,     5,
       0,     6,     2,     1,     1,     2,     3,     1,     3,     1,
       1,     1,     2,     3,     1,     1,     1,     4,     5,     2,
       1,     1,     1,     2,     1,     1,     2,     3,     2,     3,
       3,     4,     3,     4,     3,     4,     2,     3,     3,     4,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     4,     3,     3,     3,     4,     1,
       3,     2,     2,     6,     7,     1,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     1,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     5,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     3,
       1,     1,     1,     2,     0,     4,     1,     2,     1,     1,
       5,     7,     5,     7,     3,     4,     5,     5,     6,     5,
       6,     6,     7,     1,     1,     5,     2,     1,     2,     2,
       2,     3,     3,     1,     1,     1,     2,     1,     1,     0,
       5,     1,     2,     2,     3,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,    31,    13,    92,    22,    97,     0,    14,    96,    73,
      76,    24,    69,    75,    15,     0,     0,    86,   141,    23,
      95,     0,    33,   307,     0,     3,     5,     7,   311,    26,
      27,    25,     0,    30,    29,    18,    65,    66,    67,    68,
      17,    99,    16,   103,   104,    19,   116,   117,    20,   135,
     136,    21,     0,   305,   308,     0,   101,   110,     0,   109,
     100,    98,    77,    80,    70,    93,    74,    78,    71,   123,
     118,   122,   140,     0,   139,    94,    87,    88,    84,     0,
      37,    35,    34,     0,     9,    11,     4,     6,     8,   315,
       0,   312,     0,     0,    32,     1,   306,   309,   115,     0,
     111,   113,     0,   102,    81,    79,    82,    72,     0,   120,
       0,     0,   124,     0,    89,    90,    85,    28,    38,    36,
       2,     0,     0,   314,    11,   316,    51,    42,    49,     0,
      44,    46,     0,   160,   164,   165,   163,     0,     0,     0,
       0,     0,    39,     0,     0,     0,     0,     0,   167,   161,
     162,   187,   168,   169,   170,   171,   172,   173,   207,   185,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   211,
     214,   217,   222,   229,   233,   225,   227,   235,   231,     0,
       0,     0,   105,     0,     0,    83,     0,     0,     0,   131,
       0,   127,   129,   130,   137,   125,     0,    91,    10,     0,
      12,   185,   237,    53,     0,     0,    48,   144,    50,   145,
      41,     0,    43,     0,   205,   206,     0,   198,   142,     0,
     250,     0,   204,   199,   200,   201,   202,   203,     0,   181,
     182,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    40,   160,     0,     0,     0,   297,     0,
       0,     0,     0,     0,     0,     0,   304,   274,   278,     0,
     279,   255,   256,   252,   253,     0,   254,     0,   276,   263,
     264,   266,   265,   267,   257,   271,   272,   258,   259,   260,
     261,   270,   262,   106,   112,   114,     0,   107,   119,     0,
     132,   134,     0,   126,     0,   138,     0,     0,    56,     0,
       0,     0,    61,   242,   243,   244,   240,   241,   245,   246,
     247,   249,   248,   239,     0,   156,     0,    44,     0,     0,
     148,   237,     0,   146,     0,     0,    52,    45,    47,     0,
       0,     0,   144,   143,     0,     0,   166,   176,   177,     0,
     179,     0,   175,   208,   209,   210,   213,   212,   215,   216,
     219,   221,   218,   220,   223,   224,   226,   228,   230,   232,
       0,   234,   298,   296,   299,     0,     0,     0,   303,     0,
       0,   300,     0,     0,     0,   273,     0,   268,     0,   310,
     277,   108,   121,   133,   128,     0,    64,     0,    54,    58,
      60,    62,   238,   157,     0,   147,   154,   149,   152,   158,
       0,     0,   150,   237,     0,     0,   197,     0,   186,   251,
       0,   178,   174,     0,     0,     0,   294,   293,     0,   284,
     302,     0,   301,     0,     0,     0,   269,    63,    55,    57,
       0,   159,   155,   151,   153,     0,   180,   236,     0,     0,
       0,     0,     0,     0,     0,   275,    59,     0,   183,     0,
     285,     0,     0,     0,     0,   280,   295,   282,   184,     0,
     286,   287,     0,   289,     0,     0,     0,   283,   288,   290,
     291,     0,   281,   292
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   268,    90,    83,    84,    25,    26,    27,    28,    29,
      30,    31,    32,    82,    33,    34,   326,   327,   131,   132,
     308,   309,   310,   311,   312,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    59,    99,   100,   101,    45,
      46,   108,   187,    47,    71,   111,   112,   190,   191,   192,
     193,   300,    48,    49,    50,    74,    51,   219,   328,   209,
     148,   149,   150,   151,   152,   153,   154,   349,   155,   156,
     157,   158,   201,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   202,   220,   324,   269,   270,   271,   272,   273,
     274,   275,   276,   386,   277,   278,   279,   280,   281,   282,
     283,   377,   428,   284,   285,   286,   287,   288,   289,   290,
     291,   292,    52,    53,    54,   180,    55,    91
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -361
static const yytype_int16 yypact[] =
{
    1468,  -361,  -361,  -361,  -361,   -28,    28,  -361,   -24,  -361,
      43,  -361,    14,   189,  -361,    32,    59,   269,  -361,  -361,
    -361,    74,   139,  -361,    74,  1822,  1822,  1822,  1822,   121,
    -361,  -361,    63,  -361,  -361,  -361,  -361,  -361,  -361,  -361,
    -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,
    -361,  -361,   231,  -361,  -361,    50,  -361,  -361,    85,    54,
    -361,    34,  -361,    98,  -361,  -361,  -361,    18,   123,  -361,
    -361,    97,  -361,  1847,   109,  -361,  -361,   135,   166,   150,
    -361,  -361,   139,   171,  -361,  1573,  -361,  -361,  -361,  -361,
      74,  1822,  1501,   820,   121,  -361,  -361,  -361,  -361,     8,
    -361,   154,    85,  -361,  -361,  -361,   198,  -361,  1847,  -361,
      58,  1680,  -361,  1847,  -361,   203,  -361,  -361,  -361,  -361,
    -361,    74,   834,  1822,   193,  -361,  -361,  -361,   115,   187,
     200,  -361,   205,  -361,  -361,  -361,  -361,  1313,  1313,  1343,
     660,  1364,  -361,  1364,  1364,  1364,  1364,  1364,  -361,  -361,
    -361,    65,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,
    -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,    94,
     195,   287,    31,   315,   178,   221,   211,    15,   271,   208,
     500,    36,  -361,  1364,    24,  -361,  1705,  1847,  1364,   240,
     265,  -361,  -361,  -361,  -361,  -361,  1730,  -361,  -361,   783,
    -361,   337,  -361,  -361,  1423,   866,  -361,    67,  -361,   125,
    -361,  1540,  -361,   660,  -361,  -361,   660,  -361,    13,   254,
    -361,   162,  -361,  -361,  -361,  -361,  -361,  -361,   324,  -361,
    -361,   917,  1364,   330,  1364,  1364,  1364,  1364,  1364,  1364,
    1364,  1364,  1364,  1364,  1364,  1364,  1364,  1364,  1364,  1364,
    1364,  1364,  1364,  -361,   260,   276,  1364,   281,  -361,   740,
     299,   382,   319,   947,   328,   341,  -361,   352,  -361,   284,
    -361,  -361,  -361,  -361,  -361,   353,  -361,   340,  -361,  -361,
    -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,
    -361,  -361,  -361,  -361,  -361,   364,    38,  -361,  -361,  1755,
    -361,  -361,  1364,  -361,    58,  -361,  1364,   429,  -361,    99,
     834,    -5,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,
    -361,  -361,  -361,  -361,  1364,  -361,   363,   367,   365,   968,
    -361,   366,   103,   125,  1787,   998,  -361,  -361,  -361,   368,
     370,  1644,   173,  -361,  1049,  1364,  -361,  -361,  -361,   183,
    -361,   112,  -361,  -361,  -361,  -361,    94,    94,   195,   195,
     287,   287,   287,   287,    31,    31,   221,   211,   315,   271,
     -29,   178,  -361,  -361,  -361,   374,   580,   740,  -361,   371,
    1364,  -361,   286,  1364,  1364,  -361,   500,  -361,   740,  -361,
    -361,  -361,  -361,  -361,  -361,   369,  -361,   602,  -361,  -361,
    -361,  -361,  -361,  -361,  1611,  -361,  -361,  -361,  -361,  -361,
     373,  1079,  -361,   372,   142,   384,   384,   783,  -361,  -361,
    1364,  -361,  -361,  1364,   375,  1100,  -361,   364,   380,  -361,
    -361,   184,  -361,   188,   192,   420,  -361,  -361,  -361,  -361,
     834,  -361,  -361,  -361,  -361,   100,  -361,  -361,  1364,  1130,
     288,  1181,   740,   740,   740,  -361,  -361,   682,  -361,   199,
    -361,   236,  1211,  1232,   300,   403,  -361,  -361,  -361,   381,
    -361,  -361,   237,  -361,   238,  1262,   740,  -361,  -361,  -361,
    -361,   243,  -361,  -361
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -361,     2,     0,  -361,   327,  -361,   -66,    12,    -9,   -11,
    -361,  -361,   -13,  -361,  -361,  -361,   -86,   376,  -203,  -361,
    -118,    48,  -360,  -361,   174,  -361,  -361,  -361,  -361,  -361,
    -361,  -361,  -361,  -361,  -361,  -361,   385,  -158,  -361,  -361,
    -361,  -361,  -361,  -361,  -361,   -84,  -100,  -361,   180,  -361,
    -361,   175,  -361,  -361,  -361,  -361,  -361,   105,   -95,  -179,
    -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,
    -361,  -127,   -88,  -361,  -361,  -361,  -361,  -361,  -361,  -361,
    -361,  -361,   170,   177,   -16,   167,   239,   241,   245,   242,
    -361,   246,   -83,  -121,  -361,  -137,  -246,  -361,  -361,  -361,
    -361,  -361,  -361,  -361,   111,  -255,  -361,  -361,  -361,  -361,
    -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,  -361,
     249,  -361,  -361,   455,  -361,  -361,  -361,   426
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -314
static const yytype_int16 yytable[] =
{
      24,   203,    23,   221,   200,   159,   129,   110,   338,    81,
     179,   195,    79,   375,   222,    85,   223,   224,   225,   226,
     227,    94,   390,   294,   186,    86,    87,    88,   333,   196,
      89,    57,   250,   208,    80,    69,    56,   440,   345,    98,
      60,    98,   110,   241,   242,   110,   295,   110,   423,   214,
     215,   217,    24,   159,    23,   159,   159,   159,   159,   159,
      64,     1,    72,   400,   105,   106,     1,   306,   332,   119,
       1,   307,   228,   229,   230,   181,   221,     1,   203,   221,
      61,   124,   341,   182,    22,   205,   195,    89,    98,    62,
      63,   296,   128,   125,   118,   351,   195,   440,   103,   297,
     159,   189,    58,   299,   251,   301,    70,   353,   354,   355,
     350,   293,   124,   391,   370,   207,   243,   244,     1,   206,
     110,   110,   331,   343,    97,   125,   382,    21,   102,    22,
     110,   429,    21,    73,   231,   188,   204,   232,   294,   205,
     218,   233,   436,    21,   104,    22,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   333,   159,   234,   397,   457,   159,   107,
     345,   109,     4,   373,   398,   458,   408,   235,   236,   345,
     390,   114,   115,   113,   204,   422,    22,   205,    11,   203,
      92,   207,   399,    93,   334,    79,    94,   335,   414,   195,
      19,   338,   222,   402,   128,   342,   465,   466,   467,   345,
      22,   128,   116,   218,   159,   444,   218,   418,   159,   301,
     117,    65,   183,   395,   419,   360,   361,   362,   363,   345,
     482,    95,   346,   110,     1,    66,    67,   120,   121,   427,
      68,   159,   341,   431,   185,   205,   433,   434,   410,   197,
     420,   345,   413,   421,   452,   345,   159,   210,   453,   345,
       2,   122,   454,     3,     4,   247,   345,   211,     5,   469,
       6,     7,     8,   237,   238,   212,   203,     9,    10,   439,
      11,   253,    12,    13,   222,    14,    15,   252,   450,    16,
      17,    18,    19,   249,    20,   189,   203,   239,   240,   446,
      21,    75,    22,   345,   345,   345,   470,   478,   479,   248,
     345,   459,   461,   483,   464,    76,    77,   302,   339,   203,
      78,   340,   456,   159,   344,   472,   474,   347,   342,   245,
     246,   303,   304,   352,   128,   159,   203,  -303,   481,   439,
     447,   128,   372,   254,   134,   135,   136,   374,   137,   138,
     387,   345,   432,   345,   462,   345,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   475,   345,   376,     2,
     255,   256,     3,     4,   257,   258,   259,     5,   426,     6,
       7,     8,   260,   261,   262,   378,     9,    10,   380,    11,
     263,    12,    13,   139,    14,    15,   264,   383,    16,    17,
      18,    19,   265,    20,   128,   323,   266,   356,   357,   140,
     384,   141,   364,   365,   267,   389,   358,   359,   143,   144,
     145,   146,   147,   254,   134,   135,   136,   385,   137,   138,
     388,   345,   396,   403,   404,   405,   424,   430,   415,   407,
     416,   476,   437,   441,   448,   443,   451,   477,   198,     2,
     255,   256,     3,     4,   257,   258,   259,     5,   417,     6,
       7,     8,   260,   261,   262,   445,     9,    10,   130,    11,
     263,    12,    13,   139,    14,    15,   264,   393,    16,    17,
      18,    19,   265,    20,   394,   401,   266,   184,   368,   140,
     367,   141,   366,   371,   267,   455,   369,   435,   143,   144,
     145,   146,   147,   254,   134,   135,   136,    96,   137,   138,
     379,   123,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     2,
     255,   256,     3,     4,   257,   258,   259,     5,     0,     6,
       7,     8,   260,   261,   262,     0,     9,    10,     0,    11,
     263,    12,    13,   139,    14,    15,   264,     0,    16,    17,
      18,    19,   265,    20,     0,     0,   266,     0,     0,   140,
       0,   141,     0,     0,   267,     0,     0,     0,   143,   144,
     145,   146,   147,   133,   134,   135,   136,     0,   137,   138,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   133,   134,   135,   136,     2,
     137,   138,     3,     4,     0,     0,     0,     5,     0,     6,
       7,     8,     0,     0,     0,     0,     9,    10,     0,    11,
       0,    12,    13,   139,    14,    15,     0,     0,    16,    17,
      18,    19,     0,    20,     0,     0,   425,     0,     0,   140,
       0,   141,     0,     0,     0,   139,     0,     0,   143,   144,
     145,   146,   147,   133,   134,   135,   136,     0,   137,   138,
       0,   140,     0,   141,   306,     0,   199,   438,   307,     0,
     143,   144,   145,   146,   147,   133,   134,   135,   136,     2,
     137,   138,     3,     4,     0,     0,     0,     5,     0,     6,
       7,     8,     0,     0,     0,     0,     9,    10,     0,    11,
       0,    12,    13,   139,    14,    15,     0,     0,    16,    17,
      18,    19,     0,    20,     0,     0,     0,     0,     0,   140,
       0,   141,     0,     0,     0,   139,     0,     0,   143,   144,
     145,   146,   147,   254,   134,   135,   136,     0,   137,   138,
       0,   140,     0,   141,   306,     0,   199,   468,   307,     0,
     143,   144,   145,   146,   147,     0,     0,     0,     0,     0,
     255,   256,     0,     0,   257,   258,   259,     0,     0,     0,
       0,     0,   260,   261,   262,     0,   133,   134,   135,   136,
     263,   137,   138,   139,     0,     0,   264,     0,     0,     0,
       0,     0,   265,     0,     0,     0,   266,     0,     0,   140,
       0,   141,     0,     0,   267,     0,     0,     0,   143,   144,
     145,   146,   147,   133,   134,   135,   136,     0,   137,   138,
       0,     0,     0,     0,     0,     0,   139,   133,   134,   135,
     136,     0,   137,   138,     0,     0,     0,     0,     0,     0,
       0,     0,   140,     0,   141,   306,     0,   199,     0,   307,
       0,   143,   144,   145,   146,   147,     0,     0,     0,   133,
     134,   135,   136,   139,   137,   138,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   139,     0,   140,
       0,   141,     0,   142,     0,     0,     0,     0,   143,   144,
     145,   146,   147,   140,     0,   141,     0,     0,   199,     0,
       0,     0,   143,   144,   145,   146,   147,     0,     0,   139,
     133,   134,   135,   136,     0,   137,   138,     0,     0,     0,
       0,     0,     0,     0,     0,   140,     0,   329,     0,   330,
       0,     0,     0,     0,   143,   144,   145,   146,   147,     0,
     133,   134,   135,   136,     0,   137,   138,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     139,   133,   134,   135,   136,     0,   137,   138,     0,     0,
       0,     0,     0,     0,     0,     0,   140,   348,   141,     0,
       0,     0,     0,     0,     0,   143,   144,   145,   146,   147,
     139,   133,   134,   135,   136,     0,   137,   138,     0,     0,
       0,     0,     0,   381,     0,     0,   140,     0,   141,     0,
       0,   139,     0,     0,     0,   143,   144,   145,   146,   147,
       0,     0,     0,     0,     0,     0,     0,   140,     0,   141,
       0,   406,     0,     0,     0,     0,   143,   144,   145,   146,
     147,   139,   133,   134,   135,   136,     0,   137,   138,     0,
       0,     0,     0,     0,     0,     0,     0,   140,     0,   411,
       0,   412,     0,     0,     0,     0,   143,   144,   145,   146,
     147,     0,   133,   134,   135,   136,     0,   137,   138,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   139,   133,   134,   135,   136,     0,   137,   138,
       0,     0,     0,     0,     0,     0,     0,     0,   140,     0,
     141,     0,     0,   417,     0,     0,     0,   143,   144,   145,
     146,   147,   139,   133,   134,   135,   136,     0,   137,   138,
       0,     0,     0,     0,     0,     0,     0,     0,   140,     0,
     141,     0,   442,   139,     0,     0,     0,   143,   144,   145,
     146,   147,     0,     0,     0,     0,   449,     0,     0,   140,
       0,   141,     0,     0,     0,     0,     0,     0,   143,   144,
     145,   146,   147,   139,   133,   134,   135,   136,     0,   137,
     138,     0,     0,     0,     0,     0,     0,     0,     0,   140,
     460,   141,     0,     0,     0,     0,     0,     0,   143,   144,
     145,   146,   147,     0,   133,   134,   135,   136,     0,   137,
     138,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   139,   133,   134,   135,   136,     0,
     137,   138,     0,     0,     0,     0,     0,   463,     0,     0,
     140,     0,   141,     0,     0,     0,     0,     0,     0,   143,
     144,   145,   146,   147,   139,   133,   134,   135,   136,     0,
     137,   138,     0,     0,     0,     0,     0,     0,     0,     0,
     140,   471,   141,     0,     0,   139,     0,     0,     0,   143,
     144,   145,   146,   147,     0,     0,     0,     0,     0,     0,
       0,   140,   473,   141,     0,     0,     0,     0,     0,     0,
     143,   144,   145,   146,   147,   139,   133,   134,   135,   136,
       0,   137,   138,     0,     0,     0,     0,     0,     0,     0,
       0,   140,   480,   141,     0,     0,     0,     0,     0,     0,
     143,   144,   145,   146,   147,     0,   133,   134,   135,   136,
       0,   137,   138,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   139,   133,   134,   135,
     136,     0,   137,   138,     0,     0,     0,     0,     0,     0,
       0,     0,   213,     0,   141,     0,     0,     0,     0,     0,
       0,   143,   144,   145,   146,   147,   139,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   216,     0,   141,     0,     0,   139,     0,     0,
       0,   143,   144,   145,   146,   147,     1,     0,     0,     0,
       0,     0,     0,   140,     0,   141,     0,     0,     0,     0,
       0,     0,   143,   144,   145,   146,   147,     0,     0,     0,
       0,     0,     2,     0,     0,     3,     4,     0,     0,     0,
       5,     0,     6,     7,     8,     0,     0,     0,     0,     9,
      10,     1,    11,     0,    12,    13,     0,    14,    15,     0,
       0,    16,    17,    18,    19,     0,    20,     0,     0,     0,
       0,     0,   204,   325,    22,   205,     0,     2,     0,     0,
       3,     4,     0,     0,   126,     5,     0,     6,     7,     8,
       0,     0,     0,     0,     9,    10,     0,    11,     0,    12,
      13,     0,    14,    15,     0,     0,    16,    17,    18,    19,
       2,    20,     0,     3,     4,     0,     0,    21,     5,    22,
       6,     7,     8,   336,     0,     0,     0,     9,    10,     0,
      11,     0,    12,    13,     0,    14,    15,     0,   337,    16,
      17,    18,    19,     0,    20,     0,     0,     0,     0,     2,
       0,   127,     3,     4,     0,     0,     0,     5,     0,     6,
       7,     8,     0,     0,     0,     0,     9,    10,     0,    11,
       0,    12,    13,     0,    14,    15,     0,     0,    16,    17,
      18,    19,     2,    20,     0,     3,     4,     0,     0,     0,
       5,     0,     6,     7,     8,     0,     0,     0,     0,     9,
      10,     0,    11,     0,    12,    13,     0,    14,    15,   337,
       0,    16,    17,    18,    19,     0,    20,     0,     0,     0,
       2,   122,     0,     3,     4,     0,     0,  -313,     5,     0,
       6,     7,     8,     0,     0,     0,     0,     9,    10,     0,
      11,     0,    12,    13,     0,    14,    15,     0,     0,    16,
      17,    18,    19,     2,    20,     0,     3,     4,     0,     0,
       0,     5,     0,     6,     7,     8,     0,     0,     0,     0,
       9,    10,     0,    11,     0,    12,    13,     0,    14,    15,
       0,     0,    16,    17,    18,    19,     0,    20,     0,     0,
       0,     0,     3,   341,   325,    22,   205,     5,     0,     6,
       0,     8,     0,     0,     0,     0,     9,    10,     0,     0,
       0,    12,    13,     0,     0,    15,     0,     3,    16,    17,
      18,     0,     5,    20,     6,     0,     8,     0,     0,     0,
       0,     9,    10,     0,     0,   194,    12,    13,     0,     0,
      15,     0,     3,    16,    17,    18,     0,     5,    20,     6,
       0,     8,     0,     0,     0,     0,     9,    10,     0,     0,
     298,    12,    13,     0,     0,    15,     0,     3,    16,    17,
      18,     0,     5,    20,     6,     0,     8,     0,     0,     0,
       0,     9,    10,     0,     0,   305,    12,    13,     0,     0,
      15,     0,     0,    16,    17,    18,     2,     0,    20,     3,
       4,     0,     0,     0,     5,     0,     6,     7,     8,     0,
     392,     0,     0,     9,    10,     0,    11,     0,    12,    13,
       0,    14,    15,     0,     0,    16,    17,    18,    19,     0,
      20,     2,     0,     0,     3,     4,     0,   409,     0,     5,
       0,     6,     7,     8,     0,     0,     0,     0,     9,    10,
       0,    11,     0,    12,    13,     0,    14,    15,     0,     3,
      16,    17,    18,    19,     5,    20,     6,     0,     8,     0,
       0,     0,     0,     9,    10,     0,     0,     0,    12,    13,
       0,     0,    15,     0,     0,    16,    17,    18,     0,     0,
      20
};

static const yytype_int16 yycheck[] =
{
       0,   122,     0,   140,   122,    93,    92,    73,   211,    22,
      93,   111,    21,   259,   141,    24,   143,   144,   145,   146,
     147,    32,   277,   181,   108,    25,    26,    27,   207,   113,
      28,     3,    17,   128,    22,     3,    64,   397,    67,     3,
      64,     3,   108,    12,    13,   111,   183,   113,    77,   137,
     138,   139,    52,   141,    52,   143,   144,   145,   146,   147,
      46,     3,     3,    68,    46,    47,     3,    72,   205,    82,
       3,    76,     7,     8,     9,    67,   213,     3,   199,   216,
      37,    90,    69,    75,    71,    72,   186,    85,     3,    46,
      47,    67,    92,    91,    82,   232,   196,   457,    64,    75,
     188,   110,    74,   187,    89,   188,    74,   234,   235,   236,
     231,    75,   121,    75,   251,   128,    85,    86,     3,   128,
     186,   187,   205,   218,    74,   123,   263,    69,    74,    71,
     196,   377,    69,    74,    69,    77,    69,    72,   296,    72,
     140,    76,   388,    69,    46,    71,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   342,   252,    71,    67,    67,   256,    46,
      67,    74,    33,   256,    75,    75,    73,    83,    84,    67,
     435,    46,    47,    74,    69,    73,    71,    72,    49,   310,
      69,   204,   310,    72,    69,   204,   207,    72,   335,   299,
      61,   404,   329,   324,   204,   218,   452,   453,   454,    67,
      71,   211,    46,   213,   302,    73,   216,   344,   306,   302,
      70,    32,    68,   306,   345,   241,   242,   243,   244,    67,
     476,     0,    70,   299,     3,    46,    47,    66,    67,   376,
      51,   329,    69,   380,    46,    72,   383,   384,   334,    46,
      67,    67,   335,    70,    70,    67,   344,    70,    70,    67,
      29,    68,    70,    32,    33,    87,    67,    67,    37,    70,
      39,    40,    41,    78,    79,    70,   397,    46,    47,   397,
      49,    73,    51,    52,   411,    54,    55,    16,   425,    58,
      59,    60,    61,    82,    63,   304,   417,    10,    11,   420,
      69,    32,    71,    67,    67,    67,    70,    70,    70,    88,
      67,   448,   449,    70,   451,    46,    47,    77,   213,   440,
      51,   216,   440,   411,    70,   462,   463,     3,   341,    14,
      15,    66,    67,     3,   334,   423,   457,    77,   475,   457,
     423,   341,    66,     3,     4,     5,     6,    66,     8,     9,
      66,    67,    66,    67,    66,    67,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    66,    67,    69,    29,
      30,    31,    32,    33,    34,    35,    36,    37,   376,    39,
      40,    41,    42,    43,    44,     3,    46,    47,    69,    49,
      50,    51,    52,    53,    54,    55,    56,    69,    58,    59,
      60,    61,    62,    63,   404,    68,    66,   237,   238,    69,
      69,    71,   245,   246,    74,    75,   239,   240,    78,    79,
      80,    81,    82,     3,     4,     5,     6,    75,     8,     9,
      77,    67,     3,    70,    67,    70,    62,    66,    70,    73,
      70,    38,    73,    70,    69,    73,    66,    66,   121,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    74,    39,
      40,    41,    42,    43,    44,   417,    46,    47,    92,    49,
      50,    51,    52,    53,    54,    55,    56,   302,    58,    59,
      60,    61,    62,    63,   304,   311,    66,   102,   249,    69,
     248,    71,   247,   252,    74,    75,   250,   386,    78,    79,
      80,    81,    82,     3,     4,     5,     6,    52,     8,     9,
     261,    85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    -1,    39,
      40,    41,    42,    43,    44,    -1,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    -1,    58,    59,
      60,    61,    62,    63,    -1,    -1,    66,    -1,    -1,    69,
      -1,    71,    -1,    -1,    74,    -1,    -1,    -1,    78,    79,
      80,    81,    82,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,    29,
       8,     9,    32,    33,    -1,    -1,    -1,    37,    -1,    39,
      40,    41,    -1,    -1,    -1,    -1,    46,    47,    -1,    49,
      -1,    51,    52,    53,    54,    55,    -1,    -1,    58,    59,
      60,    61,    -1,    63,    -1,    -1,    66,    -1,    -1,    69,
      -1,    71,    -1,    -1,    -1,    53,    -1,    -1,    78,    79,
      80,    81,    82,     3,     4,     5,     6,    -1,     8,     9,
      -1,    69,    -1,    71,    72,    -1,    74,    75,    76,    -1,
      78,    79,    80,    81,    82,     3,     4,     5,     6,    29,
       8,     9,    32,    33,    -1,    -1,    -1,    37,    -1,    39,
      40,    41,    -1,    -1,    -1,    -1,    46,    47,    -1,    49,
      -1,    51,    52,    53,    54,    55,    -1,    -1,    58,    59,
      60,    61,    -1,    63,    -1,    -1,    -1,    -1,    -1,    69,
      -1,    71,    -1,    -1,    -1,    53,    -1,    -1,    78,    79,
      80,    81,    82,     3,     4,     5,     6,    -1,     8,     9,
      -1,    69,    -1,    71,    72,    -1,    74,    75,    76,    -1,
      78,    79,    80,    81,    82,    -1,    -1,    -1,    -1,    -1,
      30,    31,    -1,    -1,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    42,    43,    44,    -1,     3,     4,     5,     6,
      50,     8,     9,    53,    -1,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    62,    -1,    -1,    -1,    66,    -1,    -1,    69,
      -1,    71,    -1,    -1,    74,    -1,    -1,    -1,    78,    79,
      80,    81,    82,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    53,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    69,    -1,    71,    72,    -1,    74,    -1,    76,
      -1,    78,    79,    80,    81,    82,    -1,    -1,    -1,     3,
       4,     5,     6,    53,     8,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    69,
      -1,    71,    -1,    73,    -1,    -1,    -1,    -1,    78,    79,
      80,    81,    82,    69,    -1,    71,    -1,    -1,    74,    -1,
      -1,    -1,    78,    79,    80,    81,    82,    -1,    -1,    53,
       3,     4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    69,    -1,    71,    -1,    73,
      -1,    -1,    -1,    -1,    78,    79,    80,    81,    82,    -1,
       3,     4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,     3,     4,     5,     6,    -1,     8,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    69,    70,    71,    -1,
      -1,    -1,    -1,    -1,    -1,    78,    79,    80,    81,    82,
      53,     3,     4,     5,     6,    -1,     8,     9,    -1,    -1,
      -1,    -1,    -1,    66,    -1,    -1,    69,    -1,    71,    -1,
      -1,    53,    -1,    -1,    -1,    78,    79,    80,    81,    82,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    -1,    71,
      -1,    73,    -1,    -1,    -1,    -1,    78,    79,    80,    81,
      82,    53,     3,     4,     5,     6,    -1,     8,     9,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    -1,    71,
      -1,    73,    -1,    -1,    -1,    -1,    78,    79,    80,    81,
      82,    -1,     3,     4,     5,     6,    -1,     8,     9,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    -1,
      71,    -1,    -1,    74,    -1,    -1,    -1,    78,    79,    80,
      81,    82,    53,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    -1,
      71,    -1,    73,    53,    -1,    -1,    -1,    78,    79,    80,
      81,    82,    -1,    -1,    -1,    -1,    66,    -1,    -1,    69,
      -1,    71,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,
      80,    81,    82,    53,     3,     4,     5,     6,    -1,     8,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,
      80,    81,    82,    -1,     3,     4,     5,     6,    -1,     8,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,     3,     4,     5,     6,    -1,
       8,     9,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      69,    -1,    71,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      79,    80,    81,    82,    53,     3,     4,     5,     6,    -1,
       8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      69,    70,    71,    -1,    -1,    53,    -1,    -1,    -1,    78,
      79,    80,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    69,    70,    71,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    79,    80,    81,    82,    53,     3,     4,     5,     6,
      -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    69,    70,    71,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    79,    80,    81,    82,    -1,     3,     4,     5,     6,
      -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    69,    -1,    71,    -1,    -1,    -1,    -1,    -1,
      -1,    78,    79,    80,    81,    82,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    69,    -1,    71,    -1,    -1,    53,    -1,    -1,
      -1,    78,    79,    80,    81,    82,     3,    -1,    -1,    -1,
      -1,    -1,    -1,    69,    -1,    71,    -1,    -1,    -1,    -1,
      -1,    -1,    78,    79,    80,    81,    82,    -1,    -1,    -1,
      -1,    -1,    29,    -1,    -1,    32,    33,    -1,    -1,    -1,
      37,    -1,    39,    40,    41,    -1,    -1,    -1,    -1,    46,
      47,     3,    49,    -1,    51,    52,    -1,    54,    55,    -1,
      -1,    58,    59,    60,    61,    -1,    63,    -1,    -1,    -1,
      -1,    -1,    69,    70,    71,    72,    -1,    29,    -1,    -1,
      32,    33,    -1,    -1,     3,    37,    -1,    39,    40,    41,
      -1,    -1,    -1,    -1,    46,    47,    -1,    49,    -1,    51,
      52,    -1,    54,    55,    -1,    -1,    58,    59,    60,    61,
      29,    63,    -1,    32,    33,    -1,    -1,    69,    37,    71,
      39,    40,    41,     3,    -1,    -1,    -1,    46,    47,    -1,
      49,    -1,    51,    52,    -1,    54,    55,    -1,    18,    58,
      59,    60,    61,    -1,    63,    -1,    -1,    -1,    -1,    29,
      -1,    70,    32,    33,    -1,    -1,    -1,    37,    -1,    39,
      40,    41,    -1,    -1,    -1,    -1,    46,    47,    -1,    49,
      -1,    51,    52,    -1,    54,    55,    -1,    -1,    58,    59,
      60,    61,    29,    63,    -1,    32,    33,    -1,    -1,    -1,
      37,    -1,    39,    40,    41,    -1,    -1,    -1,    -1,    46,
      47,    -1,    49,    -1,    51,    52,    -1,    54,    55,    18,
      -1,    58,    59,    60,    61,    -1,    63,    -1,    -1,    -1,
      29,    68,    -1,    32,    33,    -1,    -1,    74,    37,    -1,
      39,    40,    41,    -1,    -1,    -1,    -1,    46,    47,    -1,
      49,    -1,    51,    52,    -1,    54,    55,    -1,    -1,    58,
      59,    60,    61,    29,    63,    -1,    32,    33,    -1,    -1,
      -1,    37,    -1,    39,    40,    41,    -1,    -1,    -1,    -1,
      46,    47,    -1,    49,    -1,    51,    52,    -1,    54,    55,
      -1,    -1,    58,    59,    60,    61,    -1,    63,    -1,    -1,
      -1,    -1,    32,    69,    70,    71,    72,    37,    -1,    39,
      -1,    41,    -1,    -1,    -1,    -1,    46,    47,    -1,    -1,
      -1,    51,    52,    -1,    -1,    55,    -1,    32,    58,    59,
      60,    -1,    37,    63,    39,    -1,    41,    -1,    -1,    -1,
      -1,    46,    47,    -1,    -1,    75,    51,    52,    -1,    -1,
      55,    -1,    32,    58,    59,    60,    -1,    37,    63,    39,
      -1,    41,    -1,    -1,    -1,    -1,    46,    47,    -1,    -1,
      75,    51,    52,    -1,    -1,    55,    -1,    32,    58,    59,
      60,    -1,    37,    63,    39,    -1,    41,    -1,    -1,    -1,
      -1,    46,    47,    -1,    -1,    75,    51,    52,    -1,    -1,
      55,    -1,    -1,    58,    59,    60,    29,    -1,    63,    32,
      33,    -1,    -1,    -1,    37,    -1,    39,    40,    41,    -1,
      75,    -1,    -1,    46,    47,    -1,    49,    -1,    51,    52,
      -1,    54,    55,    -1,    -1,    58,    59,    60,    61,    -1,
      63,    29,    -1,    -1,    32,    33,    -1,    70,    -1,    37,
      -1,    39,    40,    41,    -1,    -1,    -1,    -1,    46,    47,
      -1,    49,    -1,    51,    52,    -1,    54,    55,    -1,    32,
      58,    59,    60,    61,    37,    63,    39,    -1,    41,    -1,
      -1,    -1,    -1,    46,    47,    -1,    -1,    -1,    51,    52,
      -1,    -1,    55,    -1,    -1,    58,    59,    60,    -1,    -1,
      63
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    29,    32,    33,    37,    39,    40,    41,    46,
      47,    49,    51,    52,    54,    55,    58,    59,    60,    61,
      63,    69,    71,    91,    92,    95,    96,    97,    98,    99,
     100,   101,   102,   104,   105,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   129,   130,   133,   142,   143,
     144,   146,   212,   213,   214,   216,    64,     3,    74,   125,
      64,    37,    46,    47,    46,    32,    46,    47,    51,     3,
      74,   134,     3,    74,   145,    32,    46,    47,    51,    98,
      97,   102,   103,    93,    94,    98,    92,    92,    92,    91,
      92,   217,    69,    72,    99,     0,   213,    74,     3,   126,
     127,   128,    74,    64,    46,    46,    47,    46,   131,    74,
      96,   135,   136,    74,    46,    47,    46,    70,    97,   102,
      66,    67,    68,   217,    98,    91,     3,    70,    92,   106,
     107,   108,   109,     3,     4,     5,     6,     8,     9,    53,
      69,    71,    73,    78,    79,    80,    81,    82,   150,   151,
     152,   153,   154,   155,   156,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     215,    67,    75,    68,   126,    46,   135,   132,    77,    98,
     137,   138,   139,   140,    75,   136,   135,    46,    94,    74,
     110,   162,   182,   183,    69,    72,    98,   102,   148,   149,
      70,    67,    70,    69,   162,   162,    69,   162,    92,   147,
     183,   185,   161,   161,   161,   161,   161,   161,     7,     8,
       9,    69,    72,    76,    71,    83,    84,    78,    79,    10,
      11,    12,    13,    85,    86,    14,    15,    87,    88,    82,
      17,    89,    16,    73,     3,    30,    31,    34,    35,    36,
      42,    43,    44,    50,    56,    62,    66,    74,    91,   185,
     186,   187,   188,   189,   190,   191,   192,   194,   195,   196,
     197,   198,   199,   200,   203,   204,   205,   206,   207,   208,
     209,   210,   211,    75,   127,   185,    67,    75,    75,   135,
     141,   182,    77,    66,    67,    75,    72,    76,   110,   111,
     112,   113,   114,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    68,   184,    70,   106,   107,   148,    71,
      73,   182,   185,   149,    69,    72,     3,    18,   108,   147,
     147,    69,   102,   148,    70,    67,    70,     3,    70,   157,
     183,   185,     3,   161,   161,   161,   172,   172,   173,   173,
     174,   174,   174,   174,   175,   175,   178,   179,   176,   181,
     185,   177,    66,   182,    66,   186,    69,   201,     3,   210,
      69,    66,   185,    69,    69,    75,   193,    66,    77,    75,
     195,    75,    75,   141,   138,   182,     3,    67,    75,   110,
      68,   114,   183,    70,    67,    70,    73,    73,    73,    70,
     106,    71,    73,   182,   185,    70,    70,    74,   161,   183,
      67,    70,    73,    77,    62,    66,    91,   185,   202,   186,
      66,   185,    66,   185,   185,   194,   186,    73,    75,   110,
     112,    70,    73,    73,    73,   111,   183,   182,    69,    66,
     185,    66,    70,    70,    70,    75,   110,    67,    75,   185,
      70,   185,    66,    66,   185,   186,   186,   186,    75,    70,
      70,    70,   185,    70,   185,    66,    38,    66,    70,    70,
      70,   185,   186,    70
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 118 "parser.y"
    { 
																				union astnode *top = (yyvsp[(2) - (3)].astnode_p);
																				
																				/* Get proper order of symbols by reversing their order */		
																				struct symbol *new_symbol_list = NULL;
																				while (curr_symbol != NULL)
																				{
																					struct symbol *temp = curr_symbol->list;
																					curr_symbol->list = new_symbol_list;
																					new_symbol_list = curr_symbol;
																					curr_symbol = temp;
																				}
																				curr_symbol = new_symbol_list;

																				while ((yyvsp[(2) - (3)].astnode_p) != NULL)
																				{
																					union astnode *n = (yyvsp[(1) - (3)].astnode_p);

																					/* Walk along node trail */
																					while ( (n != NULL) && (n->gen.node_type == AST_STORAGE) )
																						n = n->gen.prev;

																					/* Append the list */
																					n = astnode_append(n, (yyvsp[(2) - (3)].astnode_p), PREV);
																					/*
																					union astnode *k = n;
				  																	int o = 0;
					  																while (k != NULL)
												  									{
												  										o++;
												  										printf("Node %d with type %d\n", o, k->gen.node_type);
												  										k = k->gen.prev;
												  									}*/																				

																					(yyval.astnode_p) = astnode_reverse(n, PREV);
																					//union astnode *temp = $$;
																					#if 0
																					printf("Now reverse\n");
																					union astnode *l = (yyval.astnode_p);
					  																int b = 0;
					  																while (l != NULL)
												  									{
												  										b++;
												  										printf("Node %d with type %d\n", b, l->gen.node_type);
												  										l= l->gen.prev;
												  									}
												  									#endif

																					if ((yyvsp[(1) - (3)].astnode_p)->gen.node_type == AST_STORAGE)
																					{
																						union astnode *t1 = (yyval.astnode_p)->gen.prev;
																						union astnode *t2 = (yyvsp[(1) - (3)].astnode_p);

																						/* Walk along node trail again */
																						while ( (t2->gen.prev != NULL) && (t2->gen.prev->gen.node_type == AST_STORAGE) )
																							t2 = t2->gen.prev;

																						t2->gen.prev = t1;
																						(yyval.astnode_p)->gen.prev = (yyvsp[(1) - (3)].astnode_p);
																					}
																					

																					(yyvsp[(2) - (3)].astnode_p) = (yyvsp[(2) - (3)].astnode_p)->gen.next;


																					union astnode *temp = (yyval.astnode_p);
																					union astnode *temp1 = (yyval.astnode_p);
																					int type_flag = AST_SCALAR;
												  									while (temp != NULL)
												  									{
												  										if(temp->gen.node_type == AST_FN)
												  										{
												  											type_flag = AST_FN;
												  											temp->fn.ret_value = find_ret_value(temp);
												  											break;
												  										}
												  										else if (temp->gen.node_type == AST_ARRAY)
												  										{
												  											temp->array.type = find_ret_value(temp);
												  										}
												  										//else if (temp->gen.node_type == )
												  											
												  										temp = temp->gen.prev;
												  									}


											  										(yyval.astnode_p) = temp1;

											  										
											  										union astnode *symbol_node = (yyval.astnode_p);
											  										union astnode *hak = astnode_alloc(type_flag);

														  							/* Since the union is laid out consistently, scalar.filename should work for fn.filename -- if not, use switch case*/
														  							hak->scalar.filename = strdup(file);
														  							hak->scalar.lineno = lineno;
														  							hak->scalar.name = strdup(curr_symbol->name);
														  							hak->scalar.node = (yyval.astnode_p);
														  							
														  							curr_symbol->ast_node = hak;

														  							curr_symbol->storage_class = sym_class_fn(curr_symbol);

														  							/*
														  							printf("SYMBOL NODE\n");
																					union astnode *l = curr_symbol->ast_node->scalar.node;
					  																int b = 0;
					  																while (l != NULL)
												  									{
												  										b++;
												  										printf("Node %d with type %d\n", b, l->gen.node_type);
												  										l= l->gen.prev;
												  									}*/

														  							/* Check for valid redeclaration here */
														  							if (is_valid_redeclaration(curr_scope, curr_symbol, curr_symbol->name_space))
														  								/* Do Nothing */;
														  							else
														  							{
														  								struct symbol *existing = symbol_table_get_info(curr_scope, curr_symbol->name, curr_symbol->name_space);
														  								fprintf(stderr, "ERROR: Invalid redeclaration of symbol %s, previous declaration at %s:%d\n", curr_symbol->name, existing->filename, existing->lineno);
														  								exit(-1);
														  							}



																					curr_symbol = curr_symbol->list;


																				}
																				curr_symbol = NULL;

																				//$$ = top;
																				/*
																				union astnode *q = $$;
																				printf("end\n");
				  																int o = 0;
				  																while (q != NULL)
											  									{
											  										o++;
											  										printf("Node %d with type %d\n", o, q->gen.node_type);
											  										q = q->gen.prev;
											  									}*/
																				/*
											  									union astnode *temp = $$;
											  									while (temp != NULL)
											  									{
											  										if(temp->gen.node_type == AST_FN)
											  										{
											  											temp->fn.ret_value = find_ret_value(temp);
											  											break;
											  										}
											  										else if (temp->gen.node_type == AST_ARRAY)
											  										{
											  											temp->array.type = find_ret_value(temp);
											  										}
											  										temp = temp->gen.prev;
											  									}

											  									$$ = temp;*/
											  									/*
																				if ($$->gen.node_type == AST_FN)
																				{
																					printf("here\n");
																					$$->fn.ret_value = find_ret_value($$);
																				}*/



																			;}
    break;

  case 4:
#line 291 "parser.y"
    { /* Append to list */
																				(yyval.astnode_p) = astnode_append((yyvsp[(1) - (2)].astnode_p), (yyvsp[(2) - (2)].astnode_p), PREV);
																			;}
    break;

  case 6:
#line 295 "parser.y"
    { /* Append to list */
					   															(yyval.astnode_p) = astnode_append((yyvsp[(1) - (2)].astnode_p), (yyvsp[(2) - (2)].astnode_p), PREV);
					   														;}
    break;

  case 7:
#line 298 "parser.y"
    { /* Ignore for now */ ;}
    break;

  case 8:
#line 299 "parser.y"
    { (yyval.astnode_p) = (yyvsp[(2) - (2)].astnode_p);;}
    break;

  case 10:
#line 305 "parser.y"
    { /* Append to list */
																							(yyval.astnode_p) = astnode_append((yyvsp[(1) - (3)].astnode_p), (yyvsp[(3) - (3)].astnode_p), NEXT)
																						;}
    break;

  case 12:
#line 311 "parser.y"
    {(yyval.astnode_p) = (yyvsp[(1) - (3)].astnode_p);;}
    break;

  case 13:
#line 314 "parser.y"
    { /* AUTO storage class */
										(yyval.astnode_p) = astnode_alloc(AST_STORAGE);
										(yyval.astnode_p)->storage.storage_class = AUTO_T;
									;}
    break;

  case 14:
#line 318 "parser.y"
    { /* EXTERN storage class */
										(yyval.astnode_p) = astnode_alloc(AST_STORAGE);
										(yyval.astnode_p)->storage.storage_class = EXTERN_T;
									;}
    break;

  case 15:
#line 322 "parser.y"
    { /* STATIC storage class */
										(yyval.astnode_p) = astnode_alloc(AST_STORAGE);
										(yyval.astnode_p)->storage.storage_class = STATIC_T;
									;}
    break;

  case 16:
#line 328 "parser.y"
    { /* Ignore for now */;}
    break;

  case 19:
#line 332 "parser.y"
    { /* Ignore for now */;}
    break;

  case 28:
#line 347 "parser.y"
    {(yyval.astnode_p) = (yyvsp[(2) - (3)].astnode_p);;}
    break;

  case 31:
#line 352 "parser.y"
    { /* Declaring an identifier */
				  					/*
				  					$$ = astnode_alloc(AST_IDENT);
				  					$$->ident.name = yylval.ident.name;
				  					if (symbol_table_insert(curr_scope, $$->ident.name, lineno, file, OTHER_NS, $$) == 0)
				  						//fprintf(stderr, "Redeclaration of ident %s at %s:%d\n", $$->ident.name, file, lineno);
				  						symbol_exists = 1;
				  					else
				  						symbol_exists = 0;*/

				  					(yyval.astnode_p) = astnode_alloc(AST_IDENT);
				  					(yyval.astnode_p)->ident.name = yylval.ident.name;

				  					/* If we are inserting a member of a struct/union, we have insert with MEMBER_NS, other than that we go for OTHER_NS */
				  					if (curr_scope->scope_type == MINI)
				  						curr_symbol = symbol_table_insert(curr_scope, (yyval.astnode_p)->ident.name, lineno, file, MEMBER_NS, (yyval.astnode_p), curr_symbol);
				  					else
				  						curr_symbol = symbol_table_insert(curr_scope, (yyval.astnode_p)->ident.name, lineno, file, OTHER_NS, (yyval.astnode_p), curr_symbol);

								;}
    break;

  case 32:
#line 374 "parser.y"
    { /* Declaration of pointer */
				  									(yyval.astnode_p) = astnode_append((yyvsp[(1) - (2)].astnode_p), (yyvsp[(2) - (2)].astnode_p), PREV);
												;}
    break;

  case 33:
#line 379 "parser.y"
    { /* Simple Pointer */
				   								(yyval.astnode_p) = astnode_alloc(AST_POINTER);
				   								//$$->pointer.left = NULL;
											;}
    break;

  case 34:
#line 383 "parser.y"
    { /* Pointer with type qualifier */ 
												(yyval.astnode_p) = astnode_alloc(AST_POINTER);
												//$$->pointer.left = NULL;
											;}
    break;

  case 35:
#line 387 "parser.y"
    { /* Pointer to Pointer */
												(yyval.astnode_p) = astnode_alloc(AST_POINTER);
												(yyval.astnode_p)->pointer.prev = (yyvsp[(2) - (2)].astnode_p);
											;}
    break;

  case 36:
#line 391 "parser.y"
    { /* Pointer to Pointer */
												(yyval.astnode_p) = astnode_alloc(AST_POINTER);
												(yyval.astnode_p)->pointer.prev = (yyvsp[(3) - (3)].astnode_p);
											;}
    break;

  case 39:
#line 401 "parser.y"
    { /* Array of unknown size */
													(yyval.astnode_p) = astnode_alloc(AST_ARRAY);
													(yyval.astnode_p)->array.size = -1;
													(yyval.astnode_p)->array.prev = (yyvsp[(1) - (3)].astnode_p);

												;}
    break;

  case 40:
#line 408 "parser.y"
    { /* Array with constant size */
																		if ((yyvsp[(3) - (4)].astnode_p)->gen.node_type == AST_NUMBER)
																		{
																			(yyval.astnode_p) = astnode_alloc(AST_ARRAY);
																			(yyval.astnode_p)->array.size = (yyvsp[(3) - (4)].astnode_p)->num.int_value;
																			(yyval.astnode_p)->array.prev = (yyvsp[(1) - (4)].astnode_p);
																		}
																		else
																		{
																			yyerror("Non-constant array size declarator");
																			(yyval.astnode_p) = NULL;
																		}
				 													;}
    break;

  case 41:
#line 426 "parser.y"
    { yyerror("Function prototype");;}
    break;

  case 42:
#line 427 "parser.y"
    { /* Function Declarator */
																			(yyval.astnode_p) = astnode_alloc(AST_FN);
																			(yyval.astnode_p)->fn.lineno = lineno;
																			(yyval.astnode_p)->fn.filename = strdup(file);
																			astnode_append((yyval.astnode_p), (yyvsp[(1) - (3)].astnode_p), PREV);
																		;}
    break;

  case 43:
#line 433 "parser.y"
    {yyerror("ident list");;}
    break;

  case 65:
#line 478 "parser.y"
    { /* Signed Type Specifier */
														(yyval.astnode_p) = astnode_alloc(AST_SCALAR);
														(yyval.astnode_p)->scalar.type = (yyvsp[(1) - (1)].num.int_value);
														(yyval.astnode_p)->scalar.sign = SIGNED_T;
													;}
    break;

  case 66:
#line 483 "parser.y"
    { /* Unsigned Type Specifier */
														(yyval.astnode_p) = astnode_alloc(AST_SCALAR);
														(yyval.astnode_p)->scalar.type = (yyvsp[(1) - (1)].num.int_value);
														(yyval.astnode_p)->scalar.sign = UNSIGNED_T;
					   								;}
    break;

  case 67:
#line 488 "parser.y"
    { /* Character Type Specifier */
					   									(yyval.astnode_p) = astnode_alloc(AST_SCALAR);
					   									(yyval.astnode_p)->scalar.type = CHAR_T;
					   									(yyval.astnode_p)->scalar.sign = (yyvsp[(1) - (1)].num.int_value);
					   								;}
    break;

  case 69:
#line 496 "parser.y"
    {(yyval.num.int_value) = INT_T;;}
    break;

  case 70:
#line 497 "parser.y"
    {(yyval.num.int_value) = INT_T;;}
    break;

  case 71:
#line 498 "parser.y"
    {(yyval.num.int_value) = INT_T;;}
    break;

  case 72:
#line 499 "parser.y"
    {(yyval.num.int_value) = INT_T;;}
    break;

  case 73:
#line 500 "parser.y"
    {(yyval.num.int_value) = INT_T;;}
    break;

  case 74:
#line 501 "parser.y"
    {(yyval.num.int_value) = INT_T;;}
    break;

  case 75:
#line 502 "parser.y"
    {(yyval.num.int_value) = INT_T;;}
    break;

  case 76:
#line 503 "parser.y"
    {(yyval.num.int_value) = LONG_T;;}
    break;

  case 77:
#line 504 "parser.y"
    {(yyval.num.int_value) = LONG_T;;}
    break;

  case 78:
#line 505 "parser.y"
    {(yyval.num.int_value) = LONG_T;;}
    break;

  case 79:
#line 506 "parser.y"
    {(yyval.num.int_value) = LONG_T;;}
    break;

  case 80:
#line 507 "parser.y"
    {(yyval.num.int_value) = LONGLONG_T;;}
    break;

  case 81:
#line 508 "parser.y"
    {(yyval.num.int_value) = LONGLONG_T;;}
    break;

  case 82:
#line 509 "parser.y"
    {(yyval.num.int_value) = LONGLONG_T;;}
    break;

  case 83:
#line 510 "parser.y"
    {(yyval.num.int_value) = LONGLONG_T;;}
    break;

  case 84:
#line 513 "parser.y"
    {(yyval.num.int_value) = INT_T;;}
    break;

  case 85:
#line 514 "parser.y"
    {(yyval.num.int_value) = INT_T;;}
    break;

  case 86:
#line 515 "parser.y"
    {(yyval.num.int_value) = INT_T;;}
    break;

  case 87:
#line 516 "parser.y"
    {(yyval.num.int_value) = INT_T;;}
    break;

  case 88:
#line 517 "parser.y"
    {(yyval.num.int_value) = LONG_T;;}
    break;

  case 89:
#line 518 "parser.y"
    {(yyval.num.int_value) = LONG_T;;}
    break;

  case 90:
#line 519 "parser.y"
    {(yyval.num.int_value) = LONGLONG_T;;}
    break;

  case 91:
#line 520 "parser.y"
    {(yyval.num.int_value) = LONGLONG_T;;}
    break;

  case 92:
#line 523 "parser.y"
    {(yyval.num.int_value) = SIGNED_T;;}
    break;

  case 93:
#line 524 "parser.y"
    {(yyval.num.int_value) = SIGNED_T;;}
    break;

  case 94:
#line 525 "parser.y"
    {(yyval.num.int_value) = SIGNED_T;;}
    break;

  case 95:
#line 528 "parser.y"
    {(yyval.astnode_p) = NULL;;}
    break;

  case 96:
#line 531 "parser.y"
    {
															(yyval.astnode_p) = astnode_alloc(AST_SCALAR);
															(yyval.astnode_p)->scalar.type = FLOAT_T;
															(yyval.astnode_p)->scalar.sign = SIGNED_T;
														;}
    break;

  case 97:
#line 536 "parser.y"
    {
							  								(yyval.astnode_p) = astnode_alloc(AST_SCALAR);
															(yyval.astnode_p)->scalar.type = DOUBLE_T;
															(yyval.astnode_p)->scalar.sign = SIGNED_T;
														;}
    break;

  case 98:
#line 541 "parser.y"
    {	
							  								(yyval.astnode_p) = astnode_alloc(AST_SCALAR);
															(yyval.astnode_p)->scalar.type = LONGDOUBLE_T;
															(yyval.astnode_p)->scalar.sign = SIGNED_T;
							  							;}
    break;

  case 99:
#line 546 "parser.y"
    {fprintf(stderr, "complex float at %s:%d\n", file, lineno); (yyval.astnode_p) = NULL;;}
    break;

  case 100:
#line 549 "parser.y"
    {(yyval.astnode_p) = NULL;;}
    break;

  case 101:
#line 550 "parser.y"
    {(yyval.astnode_p) = NULL;;}
    break;

  case 102:
#line 551 "parser.y"
    {(yyval.astnode_p) = NULL;;}
    break;

  case 103:
#line 554 "parser.y"
    {fprintf(stderr, "enum at %s:%d\n", file, lineno); (yyval.astnode_p) = NULL;;}
    break;

  case 104:
#line 555 "parser.y"
    {fprintf(stderr, "enum at %s:%d\n", file, lineno); (yyval.astnode_p) = NULL;;}
    break;

  case 105:
#line 558 "parser.y"
    {(yyval.astnode_p) = NULL;;}
    break;

  case 106:
#line 559 "parser.y"
    {(yyval.astnode_p) = NULL;;}
    break;

  case 107:
#line 560 "parser.y"
    {(yyval.astnode_p) = NULL;;}
    break;

  case 108:
#line 561 "parser.y"
    {(yyval.astnode_p) = NULL;;}
    break;

  case 109:
#line 564 "parser.y"
    {(yyval.astnode_p) = NULL;;}
    break;

  case 110:
#line 567 "parser.y"
    {(yyval.astnode_p) = NULL;;}
    break;

  case 115:
#line 578 "parser.y"
    {(yyval.astnode_p) = NULL;;}
    break;

  case 118:
#line 585 "parser.y"
    {union astnode *n_s = astnode_alloc(AST_STRUCT); n_s->struct_n.mini = symbol_table_alloc(MINI, lineno, file, curr_scope); curr_scope = n_s->struct_n.mini;}
    break;

  case 119:
#line 585 "parser.y"
    { /* Structures */

						 																																																	curr_scope = symbol_table_pop(curr_scope);																												

						 																																								

																																																						;}
    break;

  case 120:
#line 592 "parser.y"
    {curr_scope = symbol_table_alloc(MINI, lineno, file, curr_scope); curr_symbol->ast_node->struct_n.mini = curr_scope; curr_symbol->ast_node->struct_n.complete = 0; ;}
    break;

  case 121:
#line 592 "parser.y"
    {
						  																																																							curr_symbol->ast_node->struct_n.complete = 1;
						  																																																							(yyval.astnode_p) = curr_symbol->ast_node;
						  																																																																																									
						  																																																							//printf("Node 1 with type %d\n", $$->gen.node_type);
						  																																																							//printf("Node 2 with type %d\n", $$->struct_n.node->gen.node_type);
																																																																																															
						  																																																							print_sym_tab(curr_scope);
						  																																																							curr_scope = symbol_table_pop(curr_scope);
																																					  																								//$2->struct_n.complete = 1;
																																					  																							;}
    break;

  case 123:
#line 608 "parser.y"
    { /* Tag is IDENT */
						 		(yyval.astnode_p) = astnode_alloc(AST_IDENT);
						 		(yyval.astnode_p)->ident.name = yylval.ident.name;
						 		union astnode *n = astnode_alloc(AST_STRUCT);
						 		n->struct_n.node = (yyval.astnode_p);
						 		n->struct_n.filename = strdup(file);
						 		n->struct_n.lineno = lineno;
						 		n->struct_n.name = yylval.ident.name;
						 		curr_symbol = symbol_table_insert(curr_scope, (yyval.astnode_p)->ident.name, lineno, file, TAG_NS, n, curr_symbol);

						 		/* Check for valid redeclaration here */
								if (is_valid_redeclaration(curr_scope, curr_symbol, curr_symbol->name_space))
									/* Do Nothing */;
								else
								{
									struct symbol *existing = symbol_table_get_info(curr_scope, curr_symbol->name, curr_symbol->name_space);
									fprintf(stderr, "ERROR: Invalid redeclaration of symbol %s, previous declaration at %s:%d\n", curr_symbol->name, existing->filename, existing->lineno);
									exit(-1);
								}
						 		

							;}
    break;

  case 125:
#line 633 "parser.y"
    {(yyval.astnode_p) = astnode_append((yyvsp[(1) - (2)].astnode_p), (yyvsp[(2) - (2)].astnode_p), PREV);;}
    break;

  case 126:
#line 636 "parser.y"
    {
																							union astnode *n = (yyvsp[(1) - (3)].astnode_p);

																							/* Walk along node trail */
																							while (n->gen.node_type == AST_STORAGE)
																								n = n->gen.prev;

																							/* Append the list */
																							n = astnode_append(n, (yyvsp[(2) - (3)].astnode_p), PREV);

																							(yyval.astnode_p) = astnode_reverse(n, PREV);

																							if ((yyvsp[(1) - (3)].astnode_p)->gen.node_type == AST_STORAGE)
																							{
																								union astnode *t1 = (yyval.astnode_p)->gen.prev;
																								union astnode *t2 = (yyvsp[(1) - (3)].astnode_p);

																								/* Walk along node trail again */
																								while ( (t2->gen.prev != NULL) && (t2->gen.prev->gen.node_type == AST_STORAGE) )
																									t2 = t2->gen.prev;

																								t2->gen.prev = t1;
																								(yyval.astnode_p)->gen.prev = (yyvsp[(1) - (3)].astnode_p);
																							}

																							#if 0
																							printf("Now reverse\n");
																							union astnode *l = (yyval.astnode_p);
							  																int b = 0;
							  																while (l != NULL)
														  									{
														  										b++;
														  										printf("Node %d with type %d\n", b, l->gen.node_type);
														  										l= l->gen.prev;
														  									}
														  									#endif

																							union astnode *temp = (yyval.astnode_p);
														  									while (temp != NULL)
														  									{
														  										if(temp->gen.node_type == AST_FN)
														  										{
														  											temp->fn.ret_value = find_ret_value(temp);
														  											break;
														  										}
														  										else if (temp->gen.node_type == AST_ARRAY)
														  										{
														  											temp->array.type = find_ret_value(temp);
														  										}
														  										temp = temp->gen.prev;
														  									}

														  									//$$ = temp;

														  									union astnode *symbol_node = (yyval.astnode_p);
													  										union astnode *hak = astnode_alloc(AST_FN);
													  										  							
																  							hak->fn.filename = strdup(file);
																  							hak->fn.lineno = lineno;
																  							hak->fn.name = strdup(curr_symbol->name);
																  							hak->fn.ret_value = (yyval.astnode_p);
																  							curr_symbol->ast_node = hak;
																  							curr_symbol->storage_class = sym_class_fn(curr_symbol);

																  							/* Check for valid redeclaration */
																  							if (is_valid_redeclaration(curr_scope, curr_symbol, curr_symbol->name_space))
																  								/* Do Nothing */;
																  							else
																  							{
																  								struct symbol *existing = symbol_table_get_info(curr_scope, curr_symbol->name, curr_symbol->name_space);
																  								fprintf(stderr, "ERROR: Invalid redeclaration of symbol %s, previous declaration at %s:%d\n", curr_symbol->name, existing->filename, existing->lineno);
																  								exit(-1);
																  							}

														  									curr_symbol = curr_symbol->list; 

																						;}
    break;

  case 128:
#line 716 "parser.y"
    {(yyval.astnode_p) = astnode_reverse((yyvsp[(1) - (3)].astnode_p), PREV);;}
    break;

  case 131:
#line 723 "parser.y"
    {;}
    break;

  case 141:
#line 748 "parser.y"
    { /* VOID specifier, treat as scalar */
									(yyval.astnode_p) = astnode_alloc(AST_SCALAR);
									(yyval.astnode_p)->scalar.type = VOID_T;
									(yyval.astnode_p)->scalar.sign = VOID_SIGN;
								;}
    break;

  case 142:
#line 758 "parser.y"
    { 

														;}
    break;

  case 160:
#line 786 "parser.y"
    {  /* Identifiers */
													(yyval.astnode_p) = astnode_alloc(AST_IDENT);
													(yyval.astnode_p)->ident.name = yylval.ident.name;
												;}
    break;

  case 163:
#line 794 "parser.y"
    { /* Various Numbers */
			   			(yyval.astnode_p) = astnode_alloc(AST_NUMBER);
			   			(yyval.astnode_p)->num.int_value = yylval.num.int_value;
			   			(yyval.astnode_p)->num.float_value = yylval.num.float_value;
			   			(yyval.astnode_p)->num.sign = yylval.num.sign;
			   			(yyval.astnode_p)->num.type = yylval.num.type;
					;}
    break;

  case 164:
#line 801 "parser.y"
    { /* Character Literals */
						(yyval.astnode_p) = astnode_alloc(AST_CHARLIT);
						(yyval.astnode_p)->charlit.c = yylval.char_lit;
					;}
    break;

  case 165:
#line 805 "parser.y"
    { /* Strings */
						(yyval.astnode_p) = astnode_alloc(AST_STRING);
						strncpy((yyval.astnode_p)->string.word, yylval.string.word, yylval.string.length);
						(yyval.astnode_p)->string.length = yylval.string.length;
					;}
    break;

  case 166:
#line 812 "parser.y"
    {(yyval.astnode_p) = (yyvsp[(2) - (3)].astnode_p);;}
    break;

  case 174:
#line 824 "parser.y"
    { /* Convert a[b] to *(a + b) */
				   													(yyval.astnode_p) = astnode_alloc(AST_UNOP);
				   													(yyval.astnode_p)->unop.operator = '*';
				   													union astnode *next = astnode_alloc(AST_BINOP);
				   													(yyval.astnode_p)->unop.left = next;
				   													next->binop.operator = '+';
				   													next->binop.left = (yyvsp[(1) - (4)].astnode_p);
				   													next->binop.right = (yyvsp[(3) - (4)].astnode_p); 
																;}
    break;

  case 175:
#line 835 "parser.y"
    { /* Direct Component Selection */	
					 													(yyval.astnode_p) = astnode_alloc(AST_COMP_SELECT);
					 													(yyval.astnode_p)->comp_select.left = (yyvsp[(1) - (3)].astnode_p);
					 													(yyval.astnode_p)->comp_select.right = astnode_alloc(AST_IDENT);
																		(yyval.astnode_p)->comp_select.right->ident.name = yylval.ident.name;
																	;}
    break;

  case 176:
#line 841 "parser.y"
    { /* Indirect Component Selection -- Convert to Direct */
																		(yyval.astnode_p) = astnode_alloc(AST_COMP_SELECT);
																		(yyval.astnode_p)->comp_select.right = astnode_alloc(AST_IDENT);
																		(yyval.astnode_p)->comp_select.right->ident.name = yylval.ident.name;

																		union astnode *p = astnode_alloc(AST_UNOP);
																		p->unop.operator = '*';
																		p->unop.left = (yyvsp[(1) - (3)].astnode_p);

																		(yyval.astnode_p)->comp_select.left = p;
							   										;}
    break;

  case 177:
#line 854 "parser.y"
    { /* Function with no arguments */
																	(yyval.astnode_p) = astnode_alloc(AST_FNCALL);
																	(yyval.astnode_p)->fncall.left = (yyvsp[(1) - (3)].astnode_p);
																	(yyval.astnode_p)->fncall.right = NULL;
																;}
    break;

  case 178:
#line 859 "parser.y"
    { /* Function with arguments */
			  														(yyval.astnode_p) = astnode_alloc(AST_FNCALL);
																	(yyval.astnode_p)->fncall.left = (yyvsp[(1) - (4)].astnode_p);
																	(yyval.astnode_p)->fncall.right = (yyvsp[(3) - (4)].astnode_p);
			  													;}
    break;

  case 180:
#line 867 "parser.y"
    { /* List of Expressions */
																	//$$ = astnode_alloc(AST_EXPR_LIST);
																	//$$->expr_list.left = $1;
																	//$$->expr_list.right = $3;  
																	//$$->expr_list.next = astnode_append($1, $3, NEXT);
																	(yyval.astnode_p) = astnode_append((yyvsp[(1) - (3)].astnode_p), (yyvsp[(3) - (3)].astnode_p), NEXT);
																	
																;}
    break;

  case 181:
#line 877 "parser.y"
    { /* a++ */
																(yyval.astnode_p) = astnode_alloc(AST_UNOP);
																(yyval.astnode_p)->unop.operator = PLUSPLUS;
																(yyval.astnode_p)->unop.left = (yyvsp[(1) - (2)].astnode_p);
															;}
    break;

  case 182:
#line 884 "parser.y"
    { /* a-- */
																(yyval.astnode_p) = astnode_alloc(AST_UNOP);
																(yyval.astnode_p)->unop.operator = MINUSMINUS;
																(yyval.astnode_p)->unop.left = (yyvsp[(1) - (2)].astnode_p);
															;}
    break;

  case 183:
#line 891 "parser.y"
    {(yyval.astnode_p) = NULL;;}
    break;

  case 184:
#line 892 "parser.y"
    {(yyval.astnode_p) = NULL;;}
    break;

  case 186:
#line 896 "parser.y"
    {(yyval.astnode_p) = NULL;;}
    break;

  case 197:
#line 911 "parser.y"
    {  /* sizeof a type */
														(yyval.astnode_p) = astnode_alloc(AST_SIZEOF);
														(yyval.astnode_p)->size_of.left = (yyvsp[(3) - (4)].astnode_p); 
													;}
    break;

  case 198:
#line 915 "parser.y"
    { /* sizeof a unary expression */
				  										(yyval.astnode_p) = astnode_alloc(AST_SIZEOF);
				  										(yyval.astnode_p)->size_of.left = (yyvsp[(2) - (2)].astnode_p);
				  									;}
    break;

  case 199:
#line 921 "parser.y"
    { /* Unary Minus */
				  										(yyval.astnode_p) = astnode_alloc(AST_UNOP);
				  										(yyval.astnode_p)->unop.operator = '-';
				  										(yyval.astnode_p)->unop.left = (yyvsp[(2) - (2)].astnode_p);
													;}
    break;

  case 200:
#line 928 "parser.y"
    { /* Unary Plus */
					   									(yyval.astnode_p) = astnode_alloc(AST_UNOP);
				  										(yyval.astnode_p)->unop.operator = '+';
				  										(yyval.astnode_p)->unop.left = (yyvsp[(2) - (2)].astnode_p);
													;}
    break;

  case 201:
#line 935 "parser.y"
    { /* Unary Negation (Logical) */
					   									(yyval.astnode_p) = astnode_alloc(AST_UNOP);
				  										(yyval.astnode_p)->unop.operator = '!';
				  										(yyval.astnode_p)->unop.left = (yyvsp[(2) - (2)].astnode_p);
													;}
    break;

  case 202:
#line 942 "parser.y"
    { /* Unary Negation (Bitwise) */
														(yyval.astnode_p) = astnode_alloc(AST_UNOP);
				  										(yyval.astnode_p)->unop.operator = '~';
				  										(yyval.astnode_p)->unop.left = (yyvsp[(2) - (2)].astnode_p);
													;}
    break;

  case 203:
#line 949 "parser.y"
    { /* Unary Address */
														(yyval.astnode_p) = astnode_alloc(AST_UNOP);
				  										(yyval.astnode_p)->unop.operator = '&';
				  										(yyval.astnode_p)->unop.left = (yyvsp[(2) - (2)].astnode_p);
													;}
    break;

  case 204:
#line 956 "parser.y"
    { /* Unary Indirection */
				   										(yyval.astnode_p) = astnode_alloc(AST_UNOP);
				  										(yyval.astnode_p)->unop.operator = '*';
				  										(yyval.astnode_p)->unop.left = (yyvsp[(2) - (2)].astnode_p);
													;}
    break;

  case 205:
#line 963 "parser.y"
    { /* Convert ++a to a=a+1 */
					   										(yyval.astnode_p) = astnode_alloc(AST_ASSIGN);
					   										(yyval.astnode_p)->assign.left = (yyvsp[(2) - (2)].astnode_p);

					   										/* Create binop of RHS */
					   										union astnode *b_op = astnode_alloc(AST_BINOP);
					   										b_op->binop.operator = '+';
					   										b_op->binop.left = (yyvsp[(2) - (2)].astnode_p);

					   										/* Create the constant 1 */
					   										union astnode *one = astnode_alloc(AST_NUMBER);
					   										one->num.type = INT_T;
					   										one->num.int_value = 1;

					   										b_op->binop.right = one;
					   										(yyval.astnode_p)->assign.right = b_op;
														;}
    break;

  case 206:
#line 982 "parser.y"
    { /* Convert --a to a=a-1 */
															(yyval.astnode_p) = astnode_alloc(AST_ASSIGN);
					   										(yyval.astnode_p)->assign.left = (yyvsp[(2) - (2)].astnode_p);

					   										/* Create binop of RHS */
					   										union astnode *b_op = astnode_alloc(AST_BINOP);
					   										b_op->binop.operator = '-';
					   										b_op->binop.left = (yyvsp[(2) - (2)].astnode_p);

					   										/* Create the constant 1 */
					   										union astnode *one = astnode_alloc(AST_NUMBER);
					   										one->num.type = INT_T;
					   										one->num.int_value = 1;

					   										b_op->binop.right = one;
					   										(yyval.astnode_p)->assign.right = b_op;
														;}
    break;

  case 208:
#line 1002 "parser.y"
    { /* Multiplication */
						  														(yyval.astnode_p) = astnode_alloc(AST_BINOP);
						  														(yyval.astnode_p)->binop.operator = '*';
						  														(yyval.astnode_p)->binop.left = (yyvsp[(1) - (3)].astnode_p);
						  														(yyval.astnode_p)->binop.right = (yyvsp[(3) - (3)].astnode_p);
						  													;}
    break;

  case 209:
#line 1008 "parser.y"
    { /* Division */
						  														(yyval.astnode_p) = astnode_alloc(AST_BINOP);
						  														(yyval.astnode_p)->binop.operator = '/';
						  														(yyval.astnode_p)->binop.left = (yyvsp[(1) - (3)].astnode_p);
						  														(yyval.astnode_p)->binop.right = (yyvsp[(3) - (3)].astnode_p);
																			;}
    break;

  case 210:
#line 1014 "parser.y"
    { /* Modulo */
						  														(yyval.astnode_p) = astnode_alloc(AST_BINOP);
						  														(yyval.astnode_p)->binop.operator = '%';
						  														(yyval.astnode_p)->binop.left = (yyvsp[(1) - (3)].astnode_p);
						  														(yyval.astnode_p)->binop.right = (yyvsp[(3) - (3)].astnode_p);
						  													;}
    break;

  case 212:
#line 1023 "parser.y"
    { /* Addition */
																				(yyval.astnode_p) = astnode_alloc(AST_BINOP);
						  														(yyval.astnode_p)->binop.operator = '+';
						  														(yyval.astnode_p)->binop.left = (yyvsp[(1) - (3)].astnode_p);
						  														(yyval.astnode_p)->binop.right = (yyvsp[(3) - (3)].astnode_p);
																			;}
    break;

  case 213:
#line 1029 "parser.y"
    { /* Subtraction */
																				(yyval.astnode_p) = astnode_alloc(AST_BINOP);
						  														(yyval.astnode_p)->binop.operator = '-';
						  														(yyval.astnode_p)->binop.left = (yyvsp[(1) - (3)].astnode_p);
						  														(yyval.astnode_p)->binop.right = (yyvsp[(3) - (3)].astnode_p);
																			;}
    break;

  case 215:
#line 1038 "parser.y"
    { /* Shift Left */
				 													(yyval.astnode_p) = astnode_alloc(AST_BINOP);
						  											(yyval.astnode_p)->binop.operator = SHL;
						  											(yyval.astnode_p)->binop.left = (yyvsp[(1) - (3)].astnode_p);
						  											(yyval.astnode_p)->binop.right = (yyvsp[(3) - (3)].astnode_p);
				 												;}
    break;

  case 216:
#line 1044 "parser.y"
    { /* Shift Right */
				 													(yyval.astnode_p) = astnode_alloc(AST_BINOP);
						  											(yyval.astnode_p)->binop.operator = SHR;
						  											(yyval.astnode_p)->binop.left = (yyvsp[(1) - (3)].astnode_p);
						  											(yyval.astnode_p)->binop.right = (yyvsp[(3) - (3)].astnode_p);
				 												;}
    break;

  case 218:
#line 1053 "parser.y"
    { /* Less Than */
					  														(yyval.astnode_p) = astnode_alloc(AST_BINOP);
								  											(yyval.astnode_p)->binop.operator = '<';
								  											(yyval.astnode_p)->binop.left = (yyvsp[(1) - (3)].astnode_p);
								  											(yyval.astnode_p)->binop.right = (yyvsp[(3) - (3)].astnode_p);
					  													;}
    break;

  case 219:
#line 1059 "parser.y"
    { /* Less Than or Equal To */
					  														(yyval.astnode_p) = astnode_alloc(AST_BINOP);
								  											(yyval.astnode_p)->binop.operator = LTEQ;
								  											(yyval.astnode_p)->binop.left = (yyvsp[(1) - (3)].astnode_p);
								  											(yyval.astnode_p)->binop.right = (yyvsp[(3) - (3)].astnode_p);
					  													;}
    break;

  case 220:
#line 1065 "parser.y"
    { /* Greater Than */
					  														(yyval.astnode_p) = astnode_alloc(AST_BINOP);
								  											(yyval.astnode_p)->binop.operator = '>';
								  											(yyval.astnode_p)->binop.left = (yyvsp[(1) - (3)].astnode_p);
								  											(yyval.astnode_p)->binop.right = (yyvsp[(3) - (3)].astnode_p);
					  													;}
    break;

  case 221:
#line 1071 "parser.y"
    { /* Greater Than or Equal To */
					  														(yyval.astnode_p) = astnode_alloc(AST_BINOP);
								  											(yyval.astnode_p)->binop.operator = GTEQ;
								  											(yyval.astnode_p)->binop.left = (yyvsp[(1) - (3)].astnode_p);
								  											(yyval.astnode_p)->binop.right = (yyvsp[(3) - (3)].astnode_p);
					  													;}
    break;

  case 223:
#line 1080 "parser.y"
    { /* == */
																			(yyval.astnode_p) = astnode_alloc(AST_BINOP);
								  											(yyval.astnode_p)->binop.operator = EQEQ;
								  											(yyval.astnode_p)->binop.left = (yyvsp[(1) - (3)].astnode_p);
								  											(yyval.astnode_p)->binop.right = (yyvsp[(3) - (3)].astnode_p);
																		;}
    break;

  case 224:
#line 1086 "parser.y"
    { /* != */
																			(yyval.astnode_p) = astnode_alloc(AST_BINOP);
								  											(yyval.astnode_p)->binop.operator = NOTEQ;
								  											(yyval.astnode_p)->binop.left = (yyvsp[(1) - (3)].astnode_p);
								  											(yyval.astnode_p)->binop.right = (yyvsp[(3) - (3)].astnode_p);
																		;}
    break;

  case 226:
#line 1095 "parser.y"
    { /* Bitwise OR */
																				(yyval.astnode_p) = astnode_alloc(AST_BINOP);
									  											(yyval.astnode_p)->binop.operator = '|';
									  											(yyval.astnode_p)->binop.left = (yyvsp[(1) - (3)].astnode_p);
									  											(yyval.astnode_p)->binop.right = (yyvsp[(3) - (3)].astnode_p);
					  														;}
    break;

  case 228:
#line 1104 "parser.y"
    { /* Bitwise XOR */
					   															(yyval.astnode_p) = astnode_alloc(AST_BINOP);
									  											(yyval.astnode_p)->binop.operator = '^';
									  											(yyval.astnode_p)->binop.left = (yyvsp[(1) - (3)].astnode_p);
									  											(yyval.astnode_p)->binop.right = (yyvsp[(3) - (3)].astnode_p);	
					   														;}
    break;

  case 230:
#line 1113 "parser.y"
    { /* Bitwise AND */
					   															(yyval.astnode_p) = astnode_alloc(AST_BINOP);
									  											(yyval.astnode_p)->binop.operator = '&';
									  											(yyval.astnode_p)->binop.left = (yyvsp[(1) - (3)].astnode_p);
									  											(yyval.astnode_p)->binop.right = (yyvsp[(3) - (3)].astnode_p);
					   														;}
    break;

  case 232:
#line 1122 "parser.y"
    { /* Logical OR (||) */
																				(yyval.astnode_p) = astnode_alloc(AST_BINOP);
						  														(yyval.astnode_p)->binop.operator = LOGOR;
						  														(yyval.astnode_p)->binop.left = (yyvsp[(1) - (3)].astnode_p);
						  														(yyval.astnode_p)->binop.right = (yyvsp[(3) - (3)].astnode_p);
					  														;}
    break;

  case 234:
#line 1131 "parser.y"
    { /* Logical AND (&&) */
																					(yyval.astnode_p) = astnode_alloc(AST_BINOP);
										  											(yyval.astnode_p)->binop.operator = LOGAND;
										  											(yyval.astnode_p)->binop.left = (yyvsp[(1) - (3)].astnode_p);
										  											(yyval.astnode_p)->binop.right = (yyvsp[(3) - (3)].astnode_p);
					   															;}
    break;

  case 236:
#line 1140 "parser.y"
    {
					   																			(yyval.astnode_p) = astnode_alloc(AST_TERNARY);
					   																			(yyval.astnode_p)->ternary.cond = (yyvsp[(1) - (5)].astnode_p);
					   																			(yyval.astnode_p)->ternary.if_true = (yyvsp[(3) - (5)].astnode_p);
					   																			(yyval.astnode_p)->ternary.if_false = (yyvsp[(5) - (5)].astnode_p);
					   																		;}
    break;

  case 238:
#line 1149 "parser.y"
    { /* Recognize assignment, treat as binary operation */
					  																(yyval.astnode_p) = astnode_alloc(AST_ASSIGN);
											   										(yyval.astnode_p)->assign.left = (yyvsp[(1) - (3)].astnode_p);

											   										/* No additional work if just '=' */
											   										if((yyvsp[(2) - (3)].num.int_value) == '=')
											   											(yyval.astnode_p)->assign.right = (yyvsp[(3) - (3)].astnode_p);										
											   										else
												   									{	/* Create binop of RHS */
												   										union astnode *b_op = astnode_alloc(AST_BINOP);
												   										b_op->binop.left = (yyvsp[(1) - (3)].astnode_p);

						  																switch((yyvsp[(2) - (3)].num.int_value))
						  																{						  															
						  																	case PLUSEQ:	b_op->binop.operator = '+'; break;
						  																	case MINUSEQ:	b_op->binop.operator = '-'; break;
						  																	case TIMESEQ:	b_op->binop.operator = '*'; break;
						  																	case DIVEQ:		b_op->binop.operator = '/'; break;
						  																	case MODEQ:		b_op->binop.operator = '%'; break;
						  																	case SHLEQ:		b_op->binop.operator = SHL; break;
						  																	case SHREQ:		b_op->binop.operator = SHR; break;
						  																	case ANDEQ:		b_op->binop.operator = '&'; break;
						  																	case XOREQ:		b_op->binop.operator = '^'; break;
						  																	case OREQ:		b_op->binop.operator = '|'; break;
						  																}

						  																b_op->binop.right = (yyvsp[(3) - (3)].astnode_p);

						  																(yyval.astnode_p)->assign.right = b_op;
						  															}
						  															
					  															;}
    break;

  case 239:
#line 1183 "parser.y"
    {(yyval.num.int_value) = '=';;}
    break;

  case 240:
#line 1184 "parser.y"
    {(yyval.num.int_value) = PLUSEQ;;}
    break;

  case 241:
#line 1185 "parser.y"
    {(yyval.num.int_value) = MINUSEQ;;}
    break;

  case 242:
#line 1186 "parser.y"
    {(yyval.num.int_value) = TIMESEQ;;}
    break;

  case 243:
#line 1187 "parser.y"
    {(yyval.num.int_value) = DIVEQ;;}
    break;

  case 244:
#line 1188 "parser.y"
    {(yyval.num.int_value) = MODEQ;;}
    break;

  case 245:
#line 1189 "parser.y"
    {(yyval.num.int_value) = SHLEQ;;}
    break;

  case 246:
#line 1190 "parser.y"
    {(yyval.num.int_value) = SHREQ;;}
    break;

  case 247:
#line 1191 "parser.y"
    {(yyval.num.int_value) = ANDEQ;;}
    break;

  case 248:
#line 1192 "parser.y"
    {(yyval.num.int_value) = XOREQ;;}
    break;

  case 249:
#line 1193 "parser.y"
    {(yyval.num.int_value) = OREQ;;}
    break;

  case 251:
#line 1197 "parser.y"
    { /* List of expressions in a single line */
		   												(yyval.astnode_p) = astnode_alloc(AST_BINOP);
		   												(yyval.astnode_p)->binop.operator = ',';
		   												(yyval.astnode_p)->binop.left = (yyvsp[(1) - (3)].astnode_p);
		   												(yyval.astnode_p)->binop.right = (yyvsp[(3) - (3)].astnode_p);		 
		   											;}
    break;

  case 268:
#line 1230 "parser.y"
    {	
																						(yyval.astnode_p) = (yyvsp[(1) - (2)].astnode_p);

																						//$$ = astnode_alloc(AST_EXPR_LIST);
                                                                    					//$$->expr_list.right = $1;
																						//$$->expr_list.next = $1;

                                                                    					//fprintf(stdout, "\n\n---------- BEGIN LINE %d ----------\n", lineno);
                                                                    					//print_ast($$, 0);
                                                                   						//fprintf(stdout, "\n---------- END LINE %d ----------\n", lineno);
                                                                					;}
    break;

  case 269:
#line 1252 "parser.y"
    { /* If a named label is defined, mark it as defined -- need to fix*/
					 								(yyval.astnode_p) = astnode_alloc(AST_LABELED_ST);
					 								(yyval.astnode_p)->labeled_st.label = (yyvsp[(1) - (3)].astnode_p);
					 								(yyval.astnode_p)->labeled_st.body = (yyvsp[(3) - (3)].astnode_p);
												;}
    break;

  case 273:
#line 1264 "parser.y"
    {(yyval.astnode_p) = NULL;;}
    break;

  case 274:
#line 1265 "parser.y"
    {curr_scope = symbol_table_alloc(BLOCK_SCOPE, lineno, file, curr_scope);;}
    break;

  case 275:
#line 1265 "parser.y"
    { /* Block Scope */
																																			(yyval.astnode_p) = astnode_alloc(AST_COMPOUND_ST);
																																			(yyval.astnode_p)->compound_st.body = (yyvsp[(3) - (4)].astnode_p);
																																			//ast_dump(curr_scope,$3,NULL);
																																			curr_scope = symbol_table_pop(curr_scope);
				   																														;}
    break;

  case 277:
#line 1274 "parser.y"
    {(yyval.astnode_p) = astnode_append((yyvsp[(1) - (2)].astnode_p), (yyvsp[(2) - (2)].astnode_p), NEXT);;}
    break;

  case 280:
#line 1281 "parser.y"
    { /* IF Statement */
						 								(yyval.astnode_p) = astnode_alloc(AST_IF_ST);
						 								(yyval.astnode_p)->if_st.cond = (yyvsp[(3) - (5)].astnode_p);
						 								(yyval.astnode_p)->if_st.if_true = (yyvsp[(5) - (5)].astnode_p);
						 								(yyval.astnode_p)->if_st.next = NULL;

													;}
    break;

  case 281:
#line 1290 "parser.y"
    { /* IF-ELSE Statement */
																			(yyval.astnode_p) = astnode_alloc(AST_IF_ELSE_ST);
																			(yyval.astnode_p)->if_else_st.cond = (yyvsp[(3) - (7)].astnode_p);
																			(yyval.astnode_p)->if_else_st.if_true = (yyvsp[(5) - (7)].astnode_p);
																			(yyval.astnode_p)->if_else_st.next = (yyvsp[(7) - (7)].astnode_p);
																		;}
    break;

  case 282:
#line 1298 "parser.y"
    { /* WHILE Statement */
				  											(yyval.astnode_p) = astnode_alloc(AST_WHILE_ST);
				  											(yyval.astnode_p)->while_st.cond = (yyvsp[(3) - (5)].astnode_p);
				  											(yyval.astnode_p)->while_st.body = (yyvsp[(5) - (5)].astnode_p);

														;}
    break;

  case 283:
#line 1306 "parser.y"
    { /* DO-WHILE Statement */
																(yyval.astnode_p) = astnode_alloc(AST_DO_WHILE_ST);
																(yyval.astnode_p)->do_while_st.cond = (yyvsp[(5) - (7)].astnode_p);
																(yyval.astnode_p)->do_while_st.body = (yyvsp[(2) - (7)].astnode_p);
															;}
    break;

  case 284:
#line 1313 "parser.y"
    { /* FOR Statement */
			 										(yyval.astnode_p) = (yyvsp[(2) - (3)].astnode_p);
			 										(yyval.astnode_p)->for_st.body = (yyvsp[(3) - (3)].astnode_p);
												;}
    break;

  case 285:
#line 1319 "parser.y"
    {(yyval.astnode_p) = astnode_alloc(AST_FOR_ST); (yyval.astnode_p)->for_st.left = NULL; (yyval.astnode_p)->for_st.cond = NULL; (yyval.astnode_p)->for_st.right = NULL;;}
    break;

  case 286:
#line 1320 "parser.y"
    {(yyval.astnode_p) = astnode_alloc(AST_FOR_ST); (yyval.astnode_p)->for_st.left = NULL; (yyval.astnode_p)->for_st.cond = NULL; (yyval.astnode_p)->for_st.right = (yyvsp[(4) - (5)].astnode_p);;}
    break;

  case 287:
#line 1321 "parser.y"
    {(yyval.astnode_p) = astnode_alloc(AST_FOR_ST); (yyval.astnode_p)->for_st.left = NULL; (yyval.astnode_p)->for_st.cond = (yyvsp[(3) - (5)].astnode_p); (yyval.astnode_p)->for_st.right = NULL;;}
    break;

  case 288:
#line 1322 "parser.y"
    {(yyval.astnode_p) = astnode_alloc(AST_FOR_ST); (yyval.astnode_p)->for_st.left = NULL; (yyval.astnode_p)->for_st.cond = (yyvsp[(3) - (6)].astnode_p); (yyval.astnode_p)->for_st.right = (yyvsp[(5) - (6)].astnode_p);;}
    break;

  case 289:
#line 1323 "parser.y"
    {(yyval.astnode_p) = astnode_alloc(AST_FOR_ST); (yyval.astnode_p)->for_st.left = (yyvsp[(2) - (5)].astnode_p); (yyval.astnode_p)->for_st.cond = NULL; (yyval.astnode_p)->for_st.right = NULL;;}
    break;

  case 290:
#line 1324 "parser.y"
    {(yyval.astnode_p) = astnode_alloc(AST_FOR_ST); (yyval.astnode_p)->for_st.left = (yyvsp[(2) - (6)].astnode_p); (yyval.astnode_p)->for_st.cond = NULL; (yyval.astnode_p)->for_st.right = (yyvsp[(5) - (6)].astnode_p);;}
    break;

  case 291:
#line 1325 "parser.y"
    {(yyval.astnode_p) = astnode_alloc(AST_FOR_ST); (yyval.astnode_p)->for_st.left = (yyvsp[(2) - (6)].astnode_p); (yyval.astnode_p)->for_st.cond = (yyvsp[(4) - (6)].astnode_p); (yyval.astnode_p)->for_st.right = NULL;;}
    break;

  case 292:
#line 1326 "parser.y"
    {(yyval.astnode_p) = astnode_alloc(AST_FOR_ST); (yyval.astnode_p)->for_st.left = (yyvsp[(2) - (7)].astnode_p); (yyval.astnode_p)->for_st.cond = (yyvsp[(4) - (7)].astnode_p); (yyval.astnode_p)->for_st.right = (yyvsp[(6) - (7)].astnode_p);;}
    break;

  case 295:
#line 1333 "parser.y"
    { /* SWITCH Statement */
			   												(yyval.astnode_p) = astnode_alloc(AST_SWITCH_ST);
			   												(yyval.astnode_p)->switch_st.cond = (yyvsp[(3) - (5)].astnode_p);
			   												(yyval.astnode_p)->switch_st.body = (yyvsp[(5) - (5)].astnode_p);
														;}
    break;

  case 296:
#line 1340 "parser.y"
    { /* CASE Label */
				 							(yyval.astnode_p) = astnode_alloc(AST_CASE_LABEL);
				 							(yyval.astnode_p)->case_label.expr = (yyvsp[(2) - (2)].astnode_p);
										;}
    break;

  case 297:
#line 1346 "parser.y"
    {(yyval.astnode_p) = astnode_alloc(AST_DEF_LABEL);;}
    break;

  case 298:
#line 1349 "parser.y"
    {(yyval.astnode_p) = astnode_alloc(AST_BREAK_ST);;}
    break;

  case 299:
#line 1352 "parser.y"
    {(yyval.astnode_p) = astnode_alloc(AST_CONT_ST);;}
    break;

  case 300:
#line 1355 "parser.y"
    { /* RETURN NULL */
				   								(yyval.astnode_p) = astnode_alloc(AST_RETURN_ST);
				   								(yyval.astnode_p)->return_st.ret = NULL;
											;}
    break;

  case 301:
#line 1359 "parser.y"
    { /* RETURN something */
												(yyval.astnode_p) = astnode_alloc(AST_RETURN_ST);
												(yyval.astnode_p)->return_st.ret = (yyvsp[(2) - (3)].astnode_p);
				 							;}
    break;

  case 302:
#line 1365 "parser.y"
    { /* GOTO Statement */
				 								(yyval.astnode_p) = astnode_alloc(AST_GOTO_ST);
				 								(yyvsp[(2) - (3)].astnode_p)->named_label.call = 1; 	/* Indicates that this is a "call" to the label, not a definition */
				 								(yyval.astnode_p)->goto_st.label = (yyvsp[(2) - (3)].astnode_p);
											;}
    break;

  case 303:
#line 1372 "parser.y"
    { /* Named Label */
			   					(yyval.astnode_p) = astnode_alloc(AST_NAMED_LABEL);
			   					(yyval.astnode_p)->named_label.name = yylval.ident.name;
			   					struct symbol *s = symbol_table_get_info(curr_scope, (yyval.astnode_p)->named_label.name, LABEL_NS);
			   					if (s == NULL)
									curr_symbol = symbol_table_insert(curr_scope, (yyval.astnode_p)->ident.name, lineno, file, LABEL_NS, (yyval.astnode_p), curr_symbol);
								else
									curr_symbol = s;

							;}
    break;

  case 304:
#line 1384 "parser.y"
    {(yyval.astnode_p) = NULL;;}
    break;

  case 309:
#line 1397 "parser.y"
    {curr_scope = symbol_table_alloc(FN_T, lineno, file, curr_scope);;}
    break;

  case 310:
#line 1397 "parser.y"
    {
																																								
																																								/* Print symbol table for function */
																																								print_sym_tab(curr_scope);
																																								ast_dump(curr_scope, (yyvsp[(4) - (5)].astnode_p), (yyvsp[(1) - (5)].astnode_p)->ident.name);

																																								curr_scope = symbol_table_pop(curr_scope);

																																								//$1->fn.body = $4; - older	

																																								/* the below works */
																																								//$1->gen.prev->fn.body = $4;
																																								//ast_dump($4, $1->ident.name);

																																								//printf("Printing table for function:\n");
																																								//print_sym_tab(curr_scope);
																																								
																																							;}
    break;

  case 311:
#line 1419 "parser.y"
    { /* Reverse in order to get proper order */
																					(yyval.astnode_p) = astnode_reverse((yyvsp[(1) - (1)].astnode_p), PREV);
																				;}
    break;

  case 313:
#line 1423 "parser.y"
    { /* Similar work as in declaration rule */
					   																union astnode *n = (yyvsp[(1) - (2)].astnode_p);

																					/* Walk along node trail */
																					while (n->gen.node_type == AST_STORAGE)
																						n = n->gen.prev;

																					/* Append the list */
																					n = astnode_append(n, (yyvsp[(2) - (2)].astnode_p), PREV);

																					(yyval.astnode_p) = astnode_reverse(n, PREV);

																					if ((yyvsp[(1) - (2)].astnode_p)->gen.node_type == AST_STORAGE)
																					{
																						union astnode *t1 = (yyval.astnode_p)->gen.prev;
																						union astnode *t2 = (yyvsp[(1) - (2)].astnode_p);

																						/* Walk along node trail again */
																						while ( (t2->gen.prev != NULL) && (t2->gen.prev->gen.node_type == AST_STORAGE) )
																							t2 = t2->gen.prev;

																						t2->gen.prev = t1;
																						(yyval.astnode_p)->gen.prev = (yyvsp[(1) - (2)].astnode_p);
																					}

																					#if 0
																					printf("Now reverse\n");
																					union astnode *l = (yyval.astnode_p);
					  																int b = 0;
					  																while (l != NULL)
												  									{
												  										b++;
												  										printf("Node %d with type %d\n", b, l->gen.node_type);
												  										l= l->gen.prev;
												  									}
												  									#endif

																					union astnode *temp = (yyval.astnode_p);
												  									while (temp != NULL)
												  									{
												  										if(temp->gen.node_type == AST_FN)
												  										{
												  											temp->fn.ret_value = find_ret_value(temp);
												  											break;
												  										}
												  										else if (temp->gen.node_type == AST_ARRAY)
												  										{
												  											temp->array.type = find_ret_value(temp);
												  										}
												  										temp = temp->gen.prev;
												  									}

												  									//$$ = temp;

												  									union astnode *symbol_node = (yyval.astnode_p);
											  										union astnode *hak = astnode_alloc(AST_FN);
											  										  							
														  							hak->fn.filename = strdup(file);
														  							hak->fn.lineno = lineno;
														  							hak->fn.name = strdup(curr_symbol->name);
														  							hak->fn.ret_value = (yyval.astnode_p);
														  							curr_symbol->ast_node = hak;
														  							curr_symbol->storage_class = sym_class_fn(curr_symbol);

														  							/* Check for valid redeclaration */
														  							if (is_valid_redeclaration(curr_scope, curr_symbol, curr_symbol->name_space))
														  								/* Do Nothing */;
														  							else
														  							{
														  								struct symbol *existing = symbol_table_get_info(curr_scope, curr_symbol->name, curr_symbol->name_space);
														  								fprintf(stderr, "ERROR: Invalid redeclaration of symbol %s, previous declaration at %s:%d\n", curr_symbol->name, existing->filename, existing->lineno);
														  								exit(-1);
														  							}

												  									curr_symbol = curr_symbol->list; 	/* Makes sure that the current symbol refers to the first symbol in the function body */

					   															;}
    break;


/* Line 1267 of yacc.c.  */
#line 3958 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 1507 "parser.y"
 

/* C Stuff */

int main(int argc, char **argv)
{	
	curr_scope = symbol_table_alloc(GLOBAL_SCOPE, 1, file, NULL);
	yyparse();
	print_sym_tab(curr_scope);
	return 0;
}

