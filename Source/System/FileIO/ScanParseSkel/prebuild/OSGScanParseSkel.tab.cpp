/* A Bison parser, made by GNU Bison 2.6.1.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "2.6.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         OSGScanParseSkel_parse
#define yylex           OSGScanParseSkel_lex
#define yyerror         OSGScanParseSkel_error
#define yylval          OSGScanParseSkel_lval
#define yychar          OSGScanParseSkel_char
#define yydebug         OSGScanParseSkel_debug
#define yynerrs         OSGScanParseSkel_nerrs

/* Copy the first part of user declarations.  */



# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "OSGScanParseSkel_.tab.h".  */
#ifndef OSGSCANPARSESKEL_OSGSCANPARSESKEL_TAB_H
# define OSGSCANPARSESKEL_OSGSCANPARSESKEL_TAB_H
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int OSGScanParseSkel_debug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOK_HEADER = 258,
     TOK_PROFILE = 259,
     TOK_COMPONENT = 260,
     TOK_META = 261,
     TOK_PROTO = 262,
     TOK_EXTERNPROTO = 263,
     TOK_IS = 264,
     TOK_DEF = 265,
     TOK_USE = 266,
     TOK_ROUTE = 267,
     TOK_TO = 268,
     TOK_IMPORT = 269,
     TOK_EXPORT = 270,
     TOK_AS = 271,
     TOK_eventIn = 272,
     TOK_eventOut = 273,
     TOK_exposedField = 274,
     TOK_field = 275,
     TOK_MFBool = 276,
     TOK_MFColor = 277,
     TOK_MFColorRGBA = 278,
     TOK_MFDouble = 279,
     TOK_MFFloat = 280,
     TOK_MFImage = 281,
     TOK_MFInt32 = 282,
     TOK_MFMatrix3d = 283,
     TOK_MFMatrix3f = 284,
     TOK_MFMatrix4d = 285,
     TOK_MFMatrix4f = 286,
     TOK_MFNode = 287,
     TOK_MFRotation = 288,
     TOK_MFString = 289,
     TOK_MFTime = 290,
     TOK_MFVec2d = 291,
     TOK_MFVec2f = 292,
     TOK_MFVec3d = 293,
     TOK_MFVec3f = 294,
     TOK_MFVec4d = 295,
     TOK_MFVec4f = 296,
     TOK_SFBool = 297,
     TOK_SFColor = 298,
     TOK_SFColorRGBA = 299,
     TOK_SFDouble = 300,
     TOK_SFFloat = 301,
     TOK_SFImage = 302,
     TOK_SFInt32 = 303,
     TOK_SFMatrix3d = 304,
     TOK_SFMatrix3f = 305,
     TOK_SFMatrix4d = 306,
     TOK_SFMatrix4f = 307,
     TOK_SFNode = 308,
     TOK_SFRotation = 309,
     TOK_SFString = 310,
     TOK_SFTime = 311,
     TOK_SFVec2d = 312,
     TOK_SFVec2f = 313,
     TOK_SFVec3d = 314,
     TOK_SFVec3f = 315,
     TOK_SFVec4d = 316,
     TOK_SFVec4f = 317,
     TOK_MFColor4i = 318,
     TOK_MFPnt2f = 319,
     TOK_MFPnt3f = 320,
     TOK_MFPnt4f = 321,
     TOK_MFPlane = 322,
     TOK_SFColor4i = 323,
     TOK_SFPnt2f = 324,
     TOK_SFPnt3f = 325,
     TOK_SFPnt4f = 326,
     TOK_SFPlane = 327,
     TOK_SFVolume = 328,
     TOK_hex = 329,
     TOK_int32 = 330,
     TOK_double = 331,
     TOK_string = 332,
     TOK_bool = 333,
     TOK_NULL = 334,
     TOK_Id = 335,
     TOK_ImageFinished = 336,
     TOK_Error = 337
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{


    long intVal;
    double doubleVal;
    float floatVal;
    const char *stringVal;
    bool boolVal;



} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int OSGScanParseSkel_parse (void *YYPARSE_PARAM);
#else
int OSGScanParseSkel_parse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int OSGScanParseSkel_parse (void);
#else
int OSGScanParseSkel_parse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !OSGSCANPARSESKEL_OSGSCANPARSESKEL_TAB_H  */

/* Copy the second part of user declarations.  */



#define YYPARSE_PARAM pSkel
#define YYLEX_PARAM   pSkel

#define OSGScanParseSkel_error SKEL->handleError

#include <OSGConfig.h>
#include <OSGBaseFunctions.h>
#include "OSGScanParseLexer.h"
#include "OSGScanParseSkel.h"
#include <iostream>

#if defined(OSG_LINUX_ICC) || defined(OSG_WIN32_ICL)
#pragma warning( disable : 193 810 177 )
#endif

OSG_USING_NAMESPACE

int OSGScanParseSkel_lex(YYSTYPE *lvalp, void *);

#define SKEL (static_cast<ScanParseSkel *>(pSkel))

#if(!defined(__GNUC__) && defined(__ICL) && __INTEL_COMPILER_VERSION >= 900)
# define alloca(size)   __builtin_alloca (size)
#endif




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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   947

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  88
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  252
/* YYNRULES -- Number of rules.  */
#define YYNRULES  451
/* YYNRULES -- Number of states.  */
#define YYNSTATES  737

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   337

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    87,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    83,     2,    84,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    85,     2,    86,     2,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     9,    11,    12,    15,    16,    18,    21,
      22,    25,    27,    30,    31,    32,    37,    39,    41,    44,
      45,    47,    49,    51,    53,    55,    56,    60,    61,    62,
      69,    72,    74,    76,    77,    78,    89,    92,    93,    94,
      99,   100,   105,   106,   107,   114,   115,   116,   123,   124,
     125,   134,   137,   138,   139,   144,   145,   150,   151,   156,
     157,   162,   163,   164,   165,   177,   178,   179,   187,   188,
     193,   196,   197,   199,   203,   206,   207,   209,   211,   213,
     215,   217,   219,   220,   221,   228,   229,   230,   237,   238,
     241,   242,   243,   250,   251,   252,   259,   261,   265,   266,
     270,   272,   274,   276,   278,   280,   284,   286,   288,   290,
     292,   294,   296,   298,   300,   302,   304,   306,   308,   310,
     312,   314,   316,   318,   320,   322,   324,   326,   328,   330,
     332,   334,   336,   338,   340,   342,   344,   346,   348,   350,
     352,   354,   356,   358,   360,   362,   364,   366,   368,   370,
     372,   374,   376,   378,   380,   382,   384,   386,   388,   390,
     392,   394,   396,   398,   400,   403,   406,   409,   412,   415,
     418,   421,   424,   427,   430,   433,   436,   439,   442,   445,
     448,   451,   454,   457,   460,   463,   466,   469,   472,   475,
     478,   481,   484,   487,   490,   493,   496,   499,   502,   505,
     508,   511,   514,   517,   520,   523,   526,   529,   532,   535,
     538,   541,   544,   547,   550,   553,   556,   559,   561,   563,
     565,   567,   569,   571,   573,   575,   576,   577,   583,   584,
     585,   586,   594,   596,   598,   599,   600,   601,   610,   613,
     614,   616,   617,   618,   619,   620,   621,   622,   623,   624,
     642,   643,   644,   645,   646,   647,   648,   649,   650,   668,
     669,   670,   671,   672,   673,   674,   675,   676,   677,   678,
     679,   680,   681,   682,   683,   715,   716,   717,   718,   719,
     720,   721,   722,   723,   724,   725,   726,   727,   728,   729,
     730,   762,   764,   766,   767,   768,   769,   777,   779,   781,
     783,   784,   788,   789,   793,   794,   795,   796,   803,   804,
     805,   806,   813,   814,   815,   816,   817,   826,   827,   828,
     829,   830,   839,   841,   845,   848,   849,   851,   855,   858,
     859,   861,   865,   868,   869,   871,   875,   878,   879,   881,
     885,   888,   889,   891,   895,   898,   899,   901,   905,   908,
     909,   911,   915,   918,   919,   921,   925,   928,   929,   931,
     935,   938,   939,   941,   945,   948,   949,   951,   955,   958,
     961,   962,   964,   968,   971,   972,   974,   978,   981,   982,
     984,   988,   991,   992,   994,   998,  1001,  1002,  1004,  1008,
    1011,  1012,  1014,  1018,  1021,  1022,  1024,  1028,  1031,  1032,
    1034,  1038,  1041,  1042,  1044,  1048,  1051,  1052,  1053,  1054,
    1055,  1063,  1064,  1068,  1069,  1070,  1076,  1077,  1078,  1079,
    1087,  1088,  1089,  1090,  1098,  1099,  1100,  1101,  1102,  1112,
    1113,  1117,  1118,  1120,  1124,  1127,  1128,  1130,  1134,  1137,
    1138,  1140,  1144,  1147,  1148,  1150,  1154,  1157,  1158,  1160,
    1164,  1167
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      89,     0,    -1,    90,    91,    93,    96,   101,    -1,     3,
      -1,    -1,     4,    92,    -1,    -1,    80,    -1,    93,    94,
      -1,    -1,     5,    95,    -1,    80,    -1,    96,    97,    -1,
      -1,    -1,     6,    99,    98,   100,    -1,    77,    -1,    77,
      -1,   101,   102,    -1,    -1,   103,    -1,   107,    -1,   128,
      -1,   132,    -1,   135,    -1,    -1,   160,   104,   139,    -1,
      -1,    -1,    10,   159,   105,   160,   106,   139,    -1,    11,
     159,    -1,   108,    -1,   119,    -1,    -1,    -1,     7,   160,
     109,    83,   111,    84,   110,    85,   101,    86,    -1,   111,
     112,    -1,    -1,    -1,    17,   164,   113,   162,    -1,    -1,
      18,   164,   114,   163,    -1,    -1,    -1,    20,   164,   115,
     161,   116,   165,    -1,    -1,    -1,    19,   164,   117,   161,
     118,   165,    -1,    -1,    -1,     8,   160,   120,    83,   122,
      84,   121,   138,    -1,   122,   123,    -1,    -1,    -1,    17,
     164,   124,   162,    -1,    -1,    18,   164,   125,   163,    -1,
      -1,    20,   164,   126,   161,    -1,    -1,    19,   164,   127,
     161,    -1,    -1,    -1,    -1,    12,   159,   129,    87,   163,
     130,    13,   159,   131,    87,   162,    -1,    -1,    -1,    14,
     159,   133,    87,   159,   134,   137,    -1,    -1,    15,   159,
     136,   137,    -1,    16,   159,    -1,    -1,   290,    -1,    85,
     140,    86,    -1,   140,   141,    -1,    -1,   156,    -1,   142,
      -1,   145,    -1,   149,    -1,   152,    -1,     1,    -1,    -1,
      -1,    17,   164,   143,   162,   144,   148,    -1,    -1,    -1,
      18,   164,   146,   163,   147,   148,    -1,    -1,     9,   161,
      -1,    -1,    -1,    20,   164,   150,   161,   151,   155,    -1,
      -1,    -1,    19,   164,   153,   161,   154,   155,    -1,   165,
      -1,   164,     9,   161,    -1,    -1,   161,   157,   158,    -1,
     128,    -1,   107,    -1,   132,    -1,   135,    -1,   165,    -1,
     164,     9,   161,    -1,    80,    -1,    80,    -1,    80,    -1,
      80,    -1,    80,    -1,    21,    -1,    22,    -1,    23,    -1,
      24,    -1,    25,    -1,    26,    -1,    27,    -1,    28,    -1,
      29,    -1,    30,    -1,    31,    -1,    32,    -1,    33,    -1,
      34,    -1,    35,    -1,    36,    -1,    37,    -1,    38,    -1,
      39,    -1,    40,    -1,    41,    -1,    42,    -1,    43,    -1,
      44,    -1,    45,    -1,    46,    -1,    47,    -1,    48,    -1,
      49,    -1,    50,    -1,    51,    -1,    52,    -1,    53,    -1,
      54,    -1,    55,    -1,    56,    -1,    57,    -1,    58,    -1,
      59,    -1,    60,    -1,    61,    -1,    62,    -1,    63,    -1,
      64,    -1,    65,    -1,    66,    -1,    67,    -1,    68,    -1,
      69,    -1,    70,    -1,    71,    -1,    72,    -1,    73,    -1,
      21,   264,    -1,    22,   266,    -1,    23,   268,    -1,    24,
     270,    -1,    25,   272,    -1,    26,   274,    -1,    27,   276,
      -1,    28,   278,    -1,    29,   280,    -1,    30,   282,    -1,
      31,   284,    -1,    32,   286,    -1,    33,   288,    -1,    34,
     290,    -1,    35,   292,    -1,    36,   294,    -1,    37,   296,
      -1,    38,   298,    -1,    39,   300,    -1,    40,   302,    -1,
      41,   304,    -1,    42,   169,    -1,    43,   170,    -1,    44,
     173,    -1,    45,   177,    -1,    46,   178,    -1,    47,   179,
      -1,    48,   184,    -1,    49,   185,    -1,    50,   194,    -1,
      51,   203,    -1,    52,   219,    -1,    53,   235,    -1,    54,
     236,    -1,    55,   240,    -1,    56,   241,    -1,    57,   242,
      -1,    58,   244,    -1,    59,   246,    -1,    60,   250,    -1,
      61,   254,    -1,    62,   259,    -1,    63,   330,    -1,    64,
     332,    -1,    65,   334,    -1,    66,   336,    -1,    67,   338,
      -1,    68,   306,    -1,    69,   310,    -1,    70,   312,    -1,
      71,   315,    -1,    72,   319,    -1,    73,   323,    -1,    74,
      -1,    75,    -1,    75,    -1,    76,    -1,    75,    -1,    76,
      -1,    78,    -1,    80,    -1,    -1,    -1,   168,   171,   168,
     172,   168,    -1,    -1,    -1,    -1,   168,   174,   168,   175,
     168,   176,   168,    -1,   167,    -1,   168,    -1,    -1,    -1,
      -1,   166,   180,   166,   181,   166,   182,   183,    81,    -1,
     183,   166,    -1,    -1,   166,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   167,   186,   167,   187,   167,   188,
     167,   189,   167,   190,   167,   191,   167,   192,   167,   193,
     167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     168,   195,   168,   196,   168,   197,   168,   198,   168,   199,
     168,   200,   168,   201,   168,   202,   168,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   167,   204,   167,   205,   167,   206,   167,
     207,   167,   208,   167,   209,   167,   210,   167,   211,   167,
     212,   167,   213,   167,   214,   167,   215,   167,   216,   167,
     217,   167,   218,   167,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     168,   220,   168,   221,   168,   222,   168,   223,   168,   224,
     168,   225,   168,   226,   168,   227,   168,   228,   168,   229,
     168,   230,   168,   231,   168,   232,   168,   233,   168,   234,
     168,    -1,   103,    -1,    79,    -1,    -1,    -1,    -1,   168,
     237,   168,   238,   168,   239,   168,    -1,    77,    -1,    80,
      -1,   167,    -1,    -1,   167,   243,   167,    -1,    -1,   168,
     245,   168,    -1,    -1,    -1,    -1,   167,   247,   167,   248,
     167,   249,    -1,    -1,    -1,    -1,   168,   251,   168,   252,
     168,   253,    -1,    -1,    -1,    -1,    -1,   167,   255,   167,
     256,   167,   257,   167,   258,    -1,    -1,    -1,    -1,    -1,
     168,   260,   168,   261,   168,   262,   168,   263,    -1,   169,
      -1,    83,   265,    84,    -1,   265,   169,    -1,    -1,   170,
      -1,    83,   267,    84,    -1,   267,   170,    -1,    -1,   173,
      -1,    83,   269,    84,    -1,   269,   173,    -1,    -1,   177,
      -1,    83,   271,    84,    -1,   271,   177,    -1,    -1,   178,
      -1,    83,   273,    84,    -1,   273,   178,    -1,    -1,   179,
      -1,    83,   275,    84,    -1,   275,   179,    -1,    -1,   184,
      -1,    83,   277,    84,    -1,   277,   184,    -1,    -1,   185,
      -1,    83,   279,    84,    -1,   279,   185,    -1,    -1,   194,
      -1,    83,   281,    84,    -1,   281,   194,    -1,    -1,   203,
      -1,    83,   283,    84,    -1,   283,   203,    -1,    -1,   219,
      -1,    83,   285,    84,    -1,   285,   219,    -1,    -1,   235,
      -1,    83,   287,    84,    -1,   287,   102,    -1,   287,    79,
      -1,    -1,   236,    -1,    83,   289,    84,    -1,   289,   236,
      -1,    -1,   240,    -1,    83,   291,    84,    -1,   291,   240,
      -1,    -1,   241,    -1,    83,   293,    84,    -1,   293,   241,
      -1,    -1,   242,    -1,    83,   295,    84,    -1,   295,   242,
      -1,    -1,   244,    -1,    83,   297,    84,    -1,   297,   244,
      -1,    -1,   246,    -1,    83,   299,    84,    -1,   299,   246,
      -1,    -1,   250,    -1,    83,   301,    84,    -1,   301,   250,
      -1,    -1,   254,    -1,    83,   303,    84,    -1,   303,   254,
      -1,    -1,   259,    -1,    83,   305,    84,    -1,   305,   259,
      -1,    -1,    -1,    -1,    -1,   166,   307,   166,   308,   166,
     309,   166,    -1,    -1,   168,   311,   168,    -1,    -1,    -1,
     168,   313,   168,   314,   168,    -1,    -1,    -1,    -1,   168,
     316,   168,   317,   168,   318,   168,    -1,    -1,    -1,    -1,
     168,   320,   168,   321,   168,   322,   168,    -1,    -1,    -1,
      -1,    -1,   168,   324,   168,   325,   168,   326,   168,   327,
     328,    -1,    -1,   168,   329,   168,    -1,    -1,   306,    -1,
      83,   331,    84,    -1,   331,   306,    -1,    -1,   310,    -1,
      83,   333,    84,    -1,   333,   310,    -1,    -1,   312,    -1,
      83,   335,    84,    -1,   335,   312,    -1,    -1,   315,    -1,
      83,   337,    84,    -1,   337,   315,    -1,    -1,   319,    -1,
      83,   339,    84,    -1,   339,   319,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   195,   195,   202,   203,   206,   207,   210,   213,   214,
     217,   236,   242,   243,   248,   246,   253,   256,   259,   260,
     263,   264,   265,   266,   267,   270,   270,   273,   274,   272,
     276,   280,   281,   288,   289,   288,   293,   294,   298,   297,
     301,   300,   304,   305,   303,   308,   309,   307,   313,   314,
     313,   318,   319,   323,   322,   326,   325,   329,   328,   332,
     331,   337,   339,   341,   336,   348,   350,   347,   361,   360,
     371,   373,   376,   379,   382,   383,   386,   387,   388,   389,
     390,   391,   395,   396,   394,   401,   402,   400,   405,   407,
     411,   412,   410,   417,   418,   416,   422,   423,   427,   426,
     435,   436,   437,   438,   441,   442,   445,   448,   451,   454,
     457,   460,   461,   462,   463,   464,   465,   466,   467,   468,
     469,   470,   471,   472,   473,   474,   475,   476,   477,   478,
     479,   480,   481,   482,   483,   484,   485,   486,   487,   488,
     489,   490,   491,   492,   493,   494,   495,   496,   497,   498,
     499,   500,   501,   503,   504,   505,   506,   507,   508,   509,
     510,   511,   512,   513,   516,   517,   518,   519,   520,   521,
     522,   523,   524,   525,   526,   527,   528,   529,   530,   531,
     532,   533,   534,   535,   536,   537,   538,   539,   540,   541,
     542,   543,   544,   545,   546,   547,   548,   549,   550,   551,
     552,   553,   554,   555,   556,   557,   559,   560,   561,   562,
     563,   564,   565,   566,   567,   568,   569,   572,   573,   576,
     577,   580,   581,   584,   588,   591,   592,   591,   600,   601,
     602,   600,   610,   616,   622,   623,   625,   622,   635,   639,
     642,   648,   649,   650,   651,   652,   653,   654,   655,   648,
     666,   667,   668,   669,   670,   671,   672,   673,   666,   684,
     685,   686,   687,   688,   689,   690,   691,   692,   693,   694,
     695,   696,   697,   698,   684,   710,   711,   712,   713,   714,
     715,   716,   717,   718,   719,   720,   721,   722,   723,   724,
     710,   736,   737,   740,   741,   742,   740,   750,   754,   760,
     766,   766,   774,   774,   782,   783,   784,   782,   791,   792,
     793,   791,   800,   801,   802,   803,   800,   810,   811,   812,
     813,   810,   820,   821,   824,   825,   828,   829,   832,   833,
     836,   837,   840,   841,   844,   845,   848,   849,   852,   853,
     856,   857,   860,   861,   864,   865,   868,   869,   872,   873,
     876,   877,   880,   881,   884,   885,   888,   889,   892,   893,
     896,   897,   900,   901,   904,   905,   908,   909,   912,   913,
     914,   917,   918,   921,   922,   925,   926,   929,   930,   933,
     934,   937,   938,   941,   942,   945,   946,   949,   950,   953,
     954,   957,   958,   961,   962,   965,   966,   969,   970,   973,
     974,   977,   978,   981,   982,   985,   986,   991,   992,   993,
     991,  1002,  1002,  1010,  1011,  1010,  1019,  1020,  1021,  1019,
    1029,  1030,  1031,  1029,  1039,  1040,  1041,  1043,  1039,  1051,
    1051,  1067,  1079,  1080,  1083,  1084,  1087,  1088,  1091,  1092,
    1095,  1096,  1099,  1100,  1103,  1104,  1107,  1108,  1111,  1112,
    1115,  1116
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_HEADER", "TOK_PROFILE",
  "TOK_COMPONENT", "TOK_META", "TOK_PROTO", "TOK_EXTERNPROTO", "TOK_IS",
  "TOK_DEF", "TOK_USE", "TOK_ROUTE", "TOK_TO", "TOK_IMPORT", "TOK_EXPORT",
  "TOK_AS", "TOK_eventIn", "TOK_eventOut", "TOK_exposedField", "TOK_field",
  "TOK_MFBool", "TOK_MFColor", "TOK_MFColorRGBA", "TOK_MFDouble",
  "TOK_MFFloat", "TOK_MFImage", "TOK_MFInt32", "TOK_MFMatrix3d",
  "TOK_MFMatrix3f", "TOK_MFMatrix4d", "TOK_MFMatrix4f", "TOK_MFNode",
  "TOK_MFRotation", "TOK_MFString", "TOK_MFTime", "TOK_MFVec2d",
  "TOK_MFVec2f", "TOK_MFVec3d", "TOK_MFVec3f", "TOK_MFVec4d",
  "TOK_MFVec4f", "TOK_SFBool", "TOK_SFColor", "TOK_SFColorRGBA",
  "TOK_SFDouble", "TOK_SFFloat", "TOK_SFImage", "TOK_SFInt32",
  "TOK_SFMatrix3d", "TOK_SFMatrix3f", "TOK_SFMatrix4d", "TOK_SFMatrix4f",
  "TOK_SFNode", "TOK_SFRotation", "TOK_SFString", "TOK_SFTime",
  "TOK_SFVec2d", "TOK_SFVec2f", "TOK_SFVec3d", "TOK_SFVec3f",
  "TOK_SFVec4d", "TOK_SFVec4f", "TOK_MFColor4i", "TOK_MFPnt2f",
  "TOK_MFPnt3f", "TOK_MFPnt4f", "TOK_MFPlane", "TOK_SFColor4i",
  "TOK_SFPnt2f", "TOK_SFPnt3f", "TOK_SFPnt4f", "TOK_SFPlane",
  "TOK_SFVolume", "TOK_hex", "TOK_int32", "TOK_double", "TOK_string",
  "TOK_bool", "TOK_NULL", "TOK_Id", "TOK_ImageFinished", "TOK_Error",
  "'['", "']'", "'{'", "'}'", "'.'", "$accept", "x3dScene",
  "headerStatement", "profileStatement", "profileNameId",
  "componentStatements", "componentStatement", "componentNameId",
  "metaStatements", "metaStatement", "$@1", "metakey", "metavalue",
  "statements", "statement", "nodeStatement", "$@2", "$@3", "$@4",
  "protoStatement", "proto", "$@5", "$@6", "interfaceDeclarations",
  "interfaceDeclaration", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "externproto", "$@13", "$@14", "externInterfaceDeclarations",
  "externInterfaceDeclaration", "$@15", "$@16", "$@17", "$@18",
  "routeStatement", "$@19", "$@20", "$@21", "importStatement", "$@22",
  "$@23", "exportStatement", "$@24", "asStatement", "URLList", "node",
  "scriptBody", "scriptBodyElement", "eventInDeclaration", "$@25", "$@26",
  "eventOutDeclaration", "$@27", "$@28", "eventDeclarationEnd",
  "fieldDeclaration", "$@29", "$@30", "exposedFieldDeclaration", "$@31",
  "$@32", "fieldDeclarationEnd", "nodeBodyElement", "$@33", "fieldEnd",
  "nodeNameId", "nodeTypeId", "fieldId", "eventInId", "eventOutId",
  "fieldType", "fieldValue", "int32", "double", "float", "sfboolValue",
  "sfcolorValue", "$@34", "$@35", "sfcolorRGBAValue", "$@36", "$@37",
  "$@38", "sfdoubleValue", "sffloatValue", "sfimageValue", "$@39", "$@40",
  "$@41", "pixels", "sfint32Value", "sfmatrix3dValue", "$@42", "$@43",
  "$@44", "$@45", "$@46", "$@47", "$@48", "$@49", "sfmatrix3fValue",
  "$@50", "$@51", "$@52", "$@53", "$@54", "$@55", "$@56", "$@57",
  "sfmatrix4dValue", "$@58", "$@59", "$@60", "$@61", "$@62", "$@63",
  "$@64", "$@65", "$@66", "$@67", "$@68", "$@69", "$@70", "$@71", "$@72",
  "sfmatrix4fValue", "$@73", "$@74", "$@75", "$@76", "$@77", "$@78",
  "$@79", "$@80", "$@81", "$@82", "$@83", "$@84", "$@85", "$@86", "$@87",
  "sfnodeValue", "sfrotationValue", "$@88", "$@89", "$@90",
  "sfstringValue", "sftimeValue", "sfvec2dValue", "$@91", "sfvec2fValue",
  "$@92", "sfvec3dValue", "$@93", "$@94", "$@95", "sfvec3fValue", "$@96",
  "$@97", "$@98", "sfvec4dValue", "$@99", "$@100", "$@101", "$@102",
  "sfvec4fValue", "$@103", "$@104", "$@105", "$@106", "mfboolValue",
  "sfboolValues", "mfcolorValue", "sfcolorValues", "mfcolorRGBAValue",
  "sfcolorRGBAValues", "mfdoubleValue", "sfdoubleValues", "mffloatValue",
  "sffloatValues", "mfimageValue", "sfimageValues", "mfint32Value",
  "sfint32Values", "mfmatrix3dValue", "sfmatrix3dValues",
  "mfmatrix3fValue", "sfmatrix3fValues", "mfmatrix4dValue",
  "sfmatrix4dValues", "mfmatrix4fValue", "sfmatrix4fValues", "mfnodeValue",
  "sfnodeValues", "mfrotationValue", "sfrotationValues", "mfstringValue",
  "sfstringValues", "mftimeValue", "sftimeValues", "mfvec2dValue",
  "sfvec2dValues", "mfvec2fValue", "sfvec2fValues", "mfvec3dValue",
  "sfvec3dValues", "mfvec3fValue", "sfvec3fValues", "mfvec4dValue",
  "sfvec4dValues", "mfvec4fValue", "sfvec4fValues", "sfcolor4iValue",
  "$@107", "$@108", "$@109", "sfpnt2fValue", "$@110", "sfpnt3fValue",
  "$@111", "$@112", "sfpnt4fValue", "$@113", "$@114", "$@115",
  "sfplaneValue", "$@116", "$@117", "$@118", "sfVolumeValue", "$@119",
  "$@120", "$@121", "$@122", "sfVolumeValueEnd", "$@123", "mfcolor4iValue",
  "sfcolor4iValues", "mfpnt2fValue", "sfpnt2fValues", "mfpnt3fValue",
  "sfpnt3fValues", "mfpnt4fValue", "sfpnt4fValues", "mfplaneValue",
  "sfplaneValues", YY_NULL
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
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,    91,    93,   123,   125,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,    88,    89,    90,    90,    91,    91,    92,    93,    93,
      94,    95,    96,    96,    98,    97,    99,   100,   101,   101,
     102,   102,   102,   102,   102,   104,   103,   105,   106,   103,
     103,   107,   107,   109,   110,   108,   111,   111,   113,   112,
     114,   112,   115,   116,   112,   117,   118,   112,   120,   121,
     119,   122,   122,   124,   123,   125,   123,   126,   123,   127,
     123,   129,   130,   131,   128,   133,   134,   132,   136,   135,
     137,   137,   138,   139,   140,   140,   141,   141,   141,   141,
     141,   141,   143,   144,   142,   146,   147,   145,   148,   148,
     150,   151,   149,   153,   154,   152,   155,   155,   157,   156,
     156,   156,   156,   156,   158,   158,   159,   160,   161,   162,
     163,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   166,   166,   167,
     167,   168,   168,   169,   169,   171,   172,   170,   174,   175,
     176,   173,   177,   178,   180,   181,   182,   179,   183,   183,
     184,   186,   187,   188,   189,   190,   191,   192,   193,   185,
     195,   196,   197,   198,   199,   200,   201,   202,   194,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   203,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     219,   235,   235,   237,   238,   239,   236,   240,   240,   241,
     243,   242,   245,   244,   247,   248,   249,   246,   251,   252,
     253,   250,   255,   256,   257,   258,   254,   260,   261,   262,
     263,   259,   264,   264,   265,   265,   266,   266,   267,   267,
     268,   268,   269,   269,   270,   270,   271,   271,   272,   272,
     273,   273,   274,   274,   275,   275,   276,   276,   277,   277,
     278,   278,   279,   279,   280,   280,   281,   281,   282,   282,
     283,   283,   284,   284,   285,   285,   286,   286,   287,   287,
     287,   288,   288,   289,   289,   290,   290,   291,   291,   292,
     292,   293,   293,   294,   294,   295,   295,   296,   296,   297,
     297,   298,   298,   299,   299,   300,   300,   301,   301,   302,
     302,   303,   303,   304,   304,   305,   305,   307,   308,   309,
     306,   311,   310,   313,   314,   312,   316,   317,   318,   315,
     320,   321,   322,   319,   324,   325,   326,   327,   323,   329,
     328,   328,   330,   330,   331,   331,   332,   332,   333,   333,
     334,   334,   335,   335,   336,   336,   337,   337,   338,   338,
     339,   339
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     1,     0,     2,     0,     1,     2,     0,
       2,     1,     2,     0,     0,     4,     1,     1,     2,     0,
       1,     1,     1,     1,     1,     0,     3,     0,     0,     6,
       2,     1,     1,     0,     0,    10,     2,     0,     0,     4,
       0,     4,     0,     0,     6,     0,     0,     6,     0,     0,
       8,     2,     0,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     0,     0,    11,     0,     0,     7,     0,     4,
       2,     0,     1,     3,     2,     0,     1,     1,     1,     1,
       1,     1,     0,     0,     6,     0,     0,     6,     0,     2,
       0,     0,     6,     0,     0,     6,     1,     3,     0,     3,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     0,     5,     0,     0,
       0,     7,     1,     1,     0,     0,     0,     8,     2,     0,
       1,     0,     0,     0,     0,     0,     0,     0,     0,    17,
       0,     0,     0,     0,     0,     0,     0,     0,    17,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    31,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      31,     1,     1,     0,     0,     0,     7,     1,     1,     1,
       0,     3,     0,     3,     0,     0,     0,     6,     0,     0,
       0,     6,     0,     0,     0,     0,     8,     0,     0,     0,
       0,     8,     1,     3,     2,     0,     1,     3,     2,     0,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     0,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0,     1,     3,     2,     0,     1,     3,     2,     2,
       0,     1,     3,     2,     0,     1,     3,     2,     0,     1,
       3,     2,     0,     1,     3,     2,     0,     1,     3,     2,
       0,     1,     3,     2,     0,     1,     3,     2,     0,     1,
       3,     2,     0,     1,     3,     2,     0,     0,     0,     0,
       7,     0,     3,     0,     0,     5,     0,     0,     0,     7,
       0,     0,     0,     7,     0,     0,     0,     0,     9,     0,
       3,     0,     1,     3,     2,     0,     1,     3,     2,     0,
       1,     3,     2,     0,     1,     3,     2,     0,     1,     3,
       2,     0
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     3,     0,     6,     1,     0,     9,     7,     5,    13,
       0,     8,    19,    11,    10,     0,    12,     2,    16,    14,
       0,     0,     0,     0,     0,     0,     0,   107,    18,    20,
      21,    31,    32,    22,    23,    24,    25,     0,    33,    48,
     106,    27,    30,    61,    65,    68,     0,    17,    15,     0,
       0,     0,     0,     0,    71,    75,    26,    37,    52,    28,
       0,     0,     0,    69,     0,     0,     0,     0,   110,    62,
      66,    70,    81,     0,     0,     0,     0,   108,    73,   101,
     100,   102,   103,    74,    77,    78,    79,    80,    76,    98,
       0,     0,     0,     0,    34,    36,     0,     0,     0,     0,
      49,    51,    29,     0,    71,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,    82,    85,
      93,    90,     0,    38,    40,    45,    42,     0,    53,    55,
      59,    57,     0,     0,    67,     0,     0,     0,     0,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,    99,     0,   104,     0,     0,     0,     0,    19,
       0,     0,     0,     0,   297,   298,   378,    50,   375,    72,
      63,   109,    83,    86,    94,    91,   223,   224,   325,   322,
     164,   221,   222,   329,   225,   326,   165,   333,   228,   330,
     166,   219,   220,   337,   232,   334,   167,   341,   233,   338,
     168,   217,   218,   345,   234,   342,   169,   349,   240,   346,
     170,   353,   241,   350,   171,   357,   250,   354,   172,   361,
     259,   358,   173,   365,   275,   362,   174,   292,   370,   291,
     366,   175,   374,   293,   371,   176,   177,   382,   299,   379,
     178,   386,   300,   383,   179,   390,   302,   387,   180,   394,
     304,   391,   181,   398,   308,   395,   182,   402,   312,   399,
     183,   406,   317,   403,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   435,   407,   432,   206,
     439,   411,   436,   207,   443,   413,   440,   208,   447,   416,
     444,   209,   451,   420,   448,   210,   211,   212,   213,   214,
     215,   424,   216,     0,    39,    41,    46,    43,     0,    54,
      56,    60,    58,     0,     0,    88,    88,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   105,     0,     0,    35,   376,   377,
       0,     0,    84,    87,    95,     0,    96,    92,   323,   324,
     327,   328,   226,   331,   332,   229,   335,   336,   339,   340,
     343,   344,   235,   347,   348,   351,   352,   242,   355,   356,
     251,   359,   360,   260,   363,   364,   276,   369,   367,   368,
     372,   373,   294,   380,   381,   384,   385,   301,   388,   389,
     303,   392,   393,   305,   396,   397,   309,   400,   401,   313,
     404,   405,   318,   433,   434,   408,   437,   438,   412,   441,
     442,   414,   445,   446,   417,   449,   450,   421,   425,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    47,    44,    64,    89,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    97,   227,   230,   236,   243,   252,
     261,   277,   295,   306,   310,   314,   319,   409,   415,   418,
     422,   426,     0,   239,     0,     0,     0,     0,     0,   307,
     311,     0,     0,     0,     0,     0,     0,   231,     0,   244,
     253,   262,   278,   296,   315,   320,   410,   419,   423,   427,
     237,   238,     0,     0,     0,     0,   316,   321,   431,   245,
     254,   263,   279,   429,   428,     0,     0,     0,     0,     0,
     246,   255,   264,   280,   430,     0,     0,     0,     0,   247,
     256,   265,   281,     0,     0,     0,     0,   248,   257,   266,
     282,     0,     0,     0,     0,   249,   258,   267,   283,     0,
       0,   268,   284,     0,     0,   269,   285,     0,     0,   270,
     286,     0,     0,   271,   287,     0,     0,   272,   288,     0,
       0,   273,   289,     0,     0,   274,   290
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     6,     8,     9,    11,    14,    12,    16,
      37,    19,    48,    17,    28,   309,    46,    51,    67,    30,
      31,    49,   167,    65,    95,   235,   236,   238,   456,   237,
     455,    32,    50,   172,    66,   101,   240,   241,   243,   242,
      33,    52,   103,   404,    34,    53,   104,    35,    54,    63,
     247,    56,    64,    83,    84,   175,   405,    85,   176,   406,
     462,    86,   178,   408,    87,   177,   407,   464,    88,   162,
     232,    41,    36,    89,   252,    69,   465,   466,   284,   274,
     264,   259,   265,   411,   597,   269,   413,   598,   632,   275,
     279,   285,   417,   599,   633,   648,   289,   293,   420,   600,
     634,   662,   675,   685,   693,   701,   297,   422,   601,   635,
     663,   676,   686,   694,   702,   301,   424,   602,   636,   664,
     677,   687,   695,   703,   709,   713,   717,   721,   725,   729,
     733,   305,   426,   603,   637,   665,   678,   688,   696,   704,
     710,   714,   718,   722,   726,   730,   734,   310,   314,   429,
     604,   638,   248,   319,   323,   432,   327,   434,   331,   436,
     605,   639,   335,   438,   606,   640,   339,   440,   607,   641,
     666,   343,   442,   608,   642,   667,   260,   409,   266,   410,
     270,   412,   276,   414,   280,   415,   286,   416,   290,   418,
     294,   419,   298,   421,   302,   423,   306,   425,   311,   427,
     315,   428,   316,   403,   320,   430,   324,   431,   328,   433,
     332,   435,   336,   437,   340,   439,   344,   441,   368,   444,
     609,   643,   372,   446,   376,   448,   610,   380,   450,   611,
     644,   384,   452,   612,   645,   392,   453,   613,   646,   668,
     674,   679,   369,   443,   373,   445,   377,   447,   381,   449,
     385,   451
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -202
static const yytype_int16 yypact[] =
{
      19,  -202,    33,    47,  -202,   -24,  -202,  -202,  -202,    60,
      -8,  -202,    70,  -202,  -202,     5,  -202,   139,  -202,  -202,
      16,    16,    35,    35,    35,    35,    35,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,    52,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,    48,  -202,  -202,    55,
      65,    16,    71,    87,   167,  -202,  -202,  -202,  -202,  -202,
      99,    35,    35,  -202,   106,   123,   149,    48,  -202,  -202,
    -202,  -202,  -202,   533,   533,   533,   533,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
     533,   533,   533,   533,  -202,  -202,   533,   533,   533,   533,
    -202,  -202,  -202,   183,   167,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,   821,  -202,  -202,  -202,  -202,   133,  -202,  -202,
    -202,  -202,   143,    35,  -202,   128,    99,   131,   131,    39,
      61,   115,   126,   130,    82,   110,   222,   397,   400,   410,
      81,   413,   143,   416,   425,   427,   443,   459,   532,   534,
       3,    26,    26,   163,    26,   280,   280,   163,    26,   163,
      26,    83,    26,    20,   163,   163,    26,   163,    26,   163,
      26,   114,   536,   538,   547,   549,   280,    26,    26,    26,
      26,    26,  -202,   216,  -202,   128,    99,   131,   131,  -202,
     128,    99,   131,   131,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,   131,  -202,  -202,  -202,  -202,    59,  -202,
    -202,  -202,  -202,    75,   142,   233,   233,   821,   821,   261,
     119,    26,   204,    26,   208,   215,    96,   280,    98,   232,
     163,   234,    26,   244,   163,   256,    26,   120,   258,    26,
     260,   262,   163,   272,    26,   274,   163,   277,    26,   358,
     163,   361,    26,   103,   280,   364,    26,   368,    26,   383,
      26,   395,    26,    26,  -202,   874,   874,  -202,  -202,  -202,
     128,   131,  -202,  -202,  -202,   240,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,    39,
      61,   115,   126,   130,    82,   110,   222,   397,   400,   410,
      81,   413,   143,   416,   425,   427,   443,   459,   532,   534,
       3,    26,    26,   163,    26,   280,   280,   163,    26,   163,
      26,    83,    26,    20,   163,   163,    26,   163,    26,   163,
      26,   114,   536,   538,   547,   549,   280,    26,    26,    26,
      26,    26,  -202,  -202,  -202,  -202,   131,    26,    26,   280,
     163,    26,   163,    26,    26,   163,    26,   163,    26,   280,
      26,    26,    26,    26,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,    26,  -202,   163,    26,   163,    26,    26,  -202,
    -202,   163,    26,   280,    26,    26,    26,  -202,   372,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,   163,    26,   163,    26,  -202,  -202,    26,  -202,
    -202,  -202,  -202,  -202,  -202,   163,    26,   163,    26,    26,
    -202,  -202,  -202,  -202,  -202,   163,    26,   163,    26,  -202,
    -202,  -202,  -202,   163,    26,   163,    26,  -202,  -202,  -202,
    -202,   163,    26,   163,    26,  -202,  -202,  -202,  -202,   163,
      26,  -202,  -202,   163,    26,  -202,  -202,   163,    26,  -202,
    -202,   163,    26,  -202,  -202,   163,    26,  -202,  -202,   163,
      26,  -202,  -202,   163,    26,  -202,  -202
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,    15,  -169,   -16,  -202,  -202,  -202,   198,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
     214,  -202,  -202,  -202,   217,  -202,  -202,   221,  -202,   189,
    -202,   228,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -106,  -202,  -202,  -202,  -202,  -202,  -202,   -97,  -202,  -202,
    -202,    37,    57,  -158,  -183,   -60,    13,  -126,  -131,   108,
    -181,  -197,  -196,  -202,  -202,  -195,  -202,  -202,  -202,  -199,
    -193,  -192,  -202,  -202,  -202,  -202,  -191,  -198,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -184,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -177,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -182,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -186,  -200,  -202,
    -202,  -202,  -187,  -180,  -157,  -202,  -178,  -202,  -172,  -202,
    -202,  -202,  -201,  -202,  -202,  -202,  -166,  -202,  -202,  -202,
    -202,  -190,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,   152,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -167,  -202,
    -202,  -202,  -163,  -202,  -188,  -202,  -202,  -174,  -202,  -202,
    -202,  -162,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     268,    29,   278,   345,   348,   346,   296,   347,   304,   352,
     313,   349,   357,   350,   326,   351,   334,   363,   342,   254,
     255,   268,     1,   278,   353,   356,   358,   296,   355,   304,
     365,   313,   354,     4,   359,   326,   234,   334,   361,   342,
     388,   371,   375,   379,   383,   362,   371,   375,   379,   383,
     391,     5,   394,   364,   288,   389,     7,   399,   360,   386,
      42,    43,    44,    45,   387,    10,    20,    21,   390,    22,
      23,    24,    13,    25,    26,   288,    15,    38,    39,   396,
     397,   256,    18,   257,   401,   402,   158,   159,   160,   161,
     367,    22,    23,    22,    23,   367,    27,   244,    70,    71,
     245,   261,   262,   163,   164,   165,   166,    72,    59,   168,
     169,   170,   171,    20,    21,    40,   253,   256,    24,   257,
      25,    26,   258,    73,    74,    75,    76,    20,    21,    47,
      22,    23,    24,    55,    25,    26,   261,   262,    57,    27,
      90,    91,    92,    93,   263,   457,    20,    21,    58,    22,
      23,    24,   244,    25,    26,   245,   281,   282,    60,   458,
     307,    27,   307,    27,   308,   283,    96,    97,    98,    99,
     281,   282,   281,   282,    61,   233,   395,   281,   282,    68,
     480,   400,   483,    62,   281,   282,    77,   523,   281,   282,
     261,   262,    78,   287,   261,   262,   173,   366,   267,   497,
      27,   271,   272,   470,   498,   261,   262,    94,   251,   273,
     250,    77,   469,   277,   471,   477,   459,   474,   239,    27,
     244,   486,   479,   245,   481,   393,   246,   484,   501,   460,
     472,   268,   475,   100,   278,   454,   515,   489,   271,   272,
     296,   490,   461,   495,   304,   496,   492,   313,   502,   596,
     504,   521,   326,   510,   398,   509,   334,   516,   499,   530,
     342,   522,    79,   512,   371,   528,   375,   531,   379,   534,
     383,   537,   538,   518,   506,   533,   524,   594,    80,   261,
     262,    81,   527,   271,   272,    82,   482,   288,   473,   536,
     261,   262,   476,   174,   292,   102,   300,   271,   272,   478,
     463,   318,   322,   595,   330,   291,   338,   271,   272,   261,
     262,   467,   367,   525,     0,   292,   485,   300,   488,   271,
     272,     0,   318,   322,   249,   330,     0,   338,   491,   592,
     593,   261,   262,   261,   262,   271,   272,   271,   272,   256,
     494,   257,   500,     0,   503,   468,   505,   261,   262,   271,
     272,     0,   261,   262,   281,   282,   508,     0,   511,     0,
     268,   514,   278,   345,   348,   346,   296,   347,   304,   352,
     313,   349,   357,   350,   326,   351,   334,   363,   342,     0,
       0,   268,    29,   278,   353,   356,   358,   296,   355,   304,
     365,   313,   354,     0,   359,   326,     0,   334,   361,   342,
     388,   371,   375,   379,   383,   362,   371,   375,   379,   383,
     391,    29,     0,   364,   288,   389,   615,   616,   360,   386,
     619,     0,   621,   622,   387,   624,     0,   626,   390,   628,
     629,   630,   631,   271,   272,   288,   261,   262,   614,   261,
     262,     0,   517,   261,   262,   520,   281,   282,   526,     0,
     367,   647,   529,   660,   650,   367,   652,   653,   261,   262,
       0,   655,     0,   657,   658,   659,     0,   532,   617,     0,
     261,   262,   261,   262,     0,   271,   272,     0,   627,   535,
     295,     0,   670,   299,   672,   261,   262,   673,   261,   262,
       0,   271,   272,   303,     0,   681,   312,   683,   684,   317,
     271,   272,   261,   262,     0,   690,     0,   692,   321,     0,
     325,     0,   656,   698,     0,   700,     0,   661,   271,   272,
       0,   706,     0,   708,     0,     0,   329,   292,   487,   712,
       0,   300,   493,   716,   261,   262,     0,   720,   318,   322,
     507,   724,   333,   330,   513,   728,     0,   338,   519,   732,
       0,     0,     0,   736,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   271,   272,   261,
     262,   261,   262,   261,   262,   337,     0,   341,     0,   370,
       0,   374,   261,   262,   261,   262,     0,     0,     0,     0,
     378,     0,   382,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   292,     0,   300,     0,     0,     0,
       0,   318,   322,     0,   330,     0,   338,     0,     0,     0,
       0,     0,     0,     0,     0,   292,     0,   300,     0,     0,
       0,     0,   318,   322,     0,   330,     0,   338,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   618,     0,
     620,     0,     0,   623,     0,   625,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   649,     0,   651,     0,     0,     0,     0,   654,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     669,     0,   671,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   680,     0,   682,     0,     0,     0,     0,
       0,     0,     0,   689,     0,   691,     0,     0,     0,     0,
       0,   697,     0,   699,     0,     0,     0,     0,     0,   705,
       0,   707,     0,     0,     0,     0,     0,   711,     0,     0,
       0,   715,     0,     0,     0,   719,     0,     0,     0,   723,
       0,     0,     0,   727,     0,     0,     0,   731,     0,     0,
       0,   735,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   539,   540,   541,   542,   543,
     544,   545,   546,   547,   548,   549,   550,   551,   552,   553,
     554,   555,   556,   557,   558,   559,   560,   561,   562,   563,
     564,   565,   566,   567,   568,   569,   570,   571,   572,   573,
     574,   575,   576,   577,   578,   579,   580,   581,   582,   583,
     584,   585,   586,   587,   588,   589,   590,   591
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-202))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
     181,    17,   183,   200,   203,   201,   187,   202,   189,   207,
     191,   204,   212,   205,   195,   206,   197,   218,   199,   177,
     178,   202,     3,   204,   208,   211,   213,   208,   210,   210,
     220,   212,   209,     0,   214,   216,   162,   218,   216,   220,
     228,   222,   223,   224,   225,   217,   227,   228,   229,   230,
     231,     4,   235,   219,   185,   229,    80,   240,   215,   226,
      23,    24,    25,    26,   227,     5,     7,     8,   230,    10,
      11,    12,    80,    14,    15,   206,     6,    20,    21,   237,
     238,    78,    77,    80,   242,   243,    73,    74,    75,    76,
     221,    10,    11,    10,    11,   226,    80,    77,    61,    62,
      80,    75,    76,    90,    91,    92,    93,     1,    51,    96,
      97,    98,    99,     7,     8,    80,   176,    78,    12,    80,
      14,    15,    83,    17,    18,    19,    20,     7,     8,    77,
      10,    11,    12,    85,    14,    15,    75,    76,    83,    80,
      17,    18,    19,    20,    83,    86,     7,     8,    83,    10,
      11,    12,    77,    14,    15,    80,    74,    75,    87,    84,
      79,    80,    79,    80,    83,    83,    17,    18,    19,    20,
      74,    75,    74,    75,    87,   162,   236,    74,    75,    80,
      84,   241,    84,    16,    74,    75,    80,    84,    74,    75,
      75,    76,    86,    83,    75,    76,    13,    83,    83,    79,
      80,    75,    76,    84,    84,    75,    76,    84,    80,    83,
     173,    80,   409,    83,   410,   414,   403,   412,    85,    80,
      77,   419,   415,    80,   416,     9,    83,   418,   428,    87,
     411,   412,   413,    84,   415,   393,   437,   421,    75,    76,
     421,   422,     9,   425,   425,   426,   423,   428,   429,     9,
     430,   441,   433,   434,   239,   433,   437,   438,   427,   447,
     441,   442,    64,   435,   445,   446,   447,   448,   449,   450,
     451,   452,   453,   439,   431,   449,   443,   460,    64,    75,
      76,    64,   445,    75,    76,    64,   417,   418,    84,   451,
      75,    76,    84,   104,   186,    67,   188,    75,    76,    84,
     406,   193,   194,   461,   196,    83,   198,    75,    76,    75,
      76,   408,   443,   444,    -1,   207,    84,   209,    84,    75,
      76,    -1,   214,   215,   172,   217,    -1,   219,    84,   455,
     456,    75,    76,    75,    76,    75,    76,    75,    76,    78,
      84,    80,    84,    -1,    84,    84,    84,    75,    76,    75,
      76,    -1,    75,    76,    74,    75,    84,    -1,    84,    -1,
     541,    84,   543,   560,   563,   561,   547,   562,   549,   567,
     551,   564,   572,   565,   555,   566,   557,   578,   559,    -1,
      -1,   562,   398,   564,   568,   571,   573,   568,   570,   570,
     580,   572,   569,    -1,   574,   576,    -1,   578,   576,   580,
     588,   582,   583,   584,   585,   577,   587,   588,   589,   590,
     591,   427,    -1,   579,   545,   589,   597,   598,   575,   586,
     601,    -1,   603,   604,   587,   606,    -1,   608,   590,   610,
     611,   612,   613,    75,    76,   566,    75,    76,   596,    75,
      76,    -1,    84,    75,    76,    84,    74,    75,    84,    -1,
     581,   632,    84,    81,   635,   586,   637,   638,    75,    76,
      -1,   642,    -1,   644,   645,   646,    -1,    84,   599,    -1,
      75,    76,    75,    76,    -1,    75,    76,    -1,   609,    84,
      83,    -1,   663,    83,   665,    75,    76,   668,    75,    76,
      -1,    75,    76,    83,    -1,   676,    83,   678,   679,    83,
      75,    76,    75,    76,    -1,   686,    -1,   688,    83,    -1,
      83,    -1,   643,   694,    -1,   696,    -1,   648,    75,    76,
      -1,   702,    -1,   704,    -1,    -1,    83,   419,   420,   710,
      -1,   423,   424,   714,    75,    76,    -1,   718,   430,   431,
     432,   722,    83,   435,   436,   726,    -1,   439,   440,   730,
      -1,    -1,    -1,   734,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    75,    76,    75,
      76,    75,    76,    75,    76,    83,    -1,    83,    -1,    83,
      -1,    83,    75,    76,    75,    76,    -1,    -1,    -1,    -1,
      83,    -1,    83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   546,    -1,   548,    -1,    -1,    -1,
      -1,   553,   554,    -1,   556,    -1,   558,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   567,    -1,   569,    -1,    -1,
      -1,    -1,   574,   575,    -1,   577,    -1,   579,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   600,    -1,
     602,    -1,    -1,   605,    -1,   607,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   634,    -1,   636,    -1,    -1,    -1,    -1,   641,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     662,    -1,   664,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   675,    -1,   677,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   685,    -1,   687,    -1,    -1,    -1,    -1,
      -1,   693,    -1,   695,    -1,    -1,    -1,    -1,    -1,   701,
      -1,   703,    -1,    -1,    -1,    -1,    -1,   709,    -1,    -1,
      -1,   713,    -1,    -1,    -1,   717,    -1,    -1,    -1,   721,
      -1,    -1,    -1,   725,    -1,    -1,    -1,   729,    -1,    -1,
      -1,   733,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     3,    89,    90,     0,     4,    91,    80,    92,    93,
       5,    94,    96,    80,    95,     6,    97,   101,    77,    99,
       7,     8,    10,    11,    12,    14,    15,    80,   102,   103,
     107,   108,   119,   128,   132,   135,   160,    98,   160,   160,
      80,   159,   159,   159,   159,   159,   104,    77,   100,   109,
     120,   105,   129,   133,   136,    85,   139,    83,    83,   160,
      87,    87,    16,   137,   140,   111,   122,   106,    80,   163,
     159,   159,     1,    17,    18,    19,    20,    80,    86,   107,
     128,   132,   135,   141,   142,   145,   149,   152,   156,   161,
      17,    18,    19,    20,    84,   112,    17,    18,    19,    20,
      84,   123,   139,   130,   134,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,   164,   164,
     164,   164,   157,   164,   164,   164,   164,   110,   164,   164,
     164,   164,   121,    13,   137,   143,   146,   153,   150,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,   158,   164,   165,   113,   114,   117,   115,    85,
     124,   125,   127,   126,    77,    80,    83,   138,   240,   290,
     159,    80,   162,   163,   161,   161,    78,    80,    83,   169,
     264,    75,    76,    83,   168,   170,   266,    83,   168,   173,
     268,    75,    76,    83,   167,   177,   270,    83,   168,   178,
     272,    74,    75,    83,   166,   179,   274,    83,   166,   184,
     276,    83,   167,   185,   278,    83,   168,   194,   280,    83,
     167,   203,   282,    83,   168,   219,   284,    79,    83,   103,
     235,   286,    83,   168,   236,   288,   290,    83,   167,   241,
     292,    83,   167,   242,   294,    83,   168,   244,   296,    83,
     167,   246,   298,    83,   168,   250,   300,    83,   167,   254,
     302,    83,   168,   259,   304,   169,   170,   173,   177,   178,
     179,   184,   185,   194,   203,   219,   235,   236,   240,   241,
     242,   244,   246,   250,   254,   259,    83,   166,   306,   330,
      83,   168,   310,   332,    83,   168,   312,   334,    83,   168,
     315,   336,    83,   168,   319,   338,   306,   310,   312,   315,
     319,   168,   323,     9,   162,   163,   161,   161,   101,   162,
     163,   161,   161,   291,   131,   144,   147,   154,   151,   265,
     267,   171,   269,   174,   271,   273,   275,   180,   277,   279,
     186,   281,   195,   283,   204,   285,   220,   287,   289,   237,
     293,   295,   243,   297,   245,   299,   247,   301,   251,   303,
     255,   305,   260,   331,   307,   333,   311,   335,   313,   337,
     316,   339,   320,   324,   161,   118,   116,    86,    84,   240,
      87,     9,   148,   148,   155,   164,   165,   155,    84,   169,
      84,   170,   168,    84,   173,   168,    84,   177,    84,   178,
      84,   179,   166,    84,   184,    84,   185,   167,    84,   194,
     168,    84,   203,   167,    84,   219,   168,    79,    84,   102,
      84,   236,   168,    84,   241,    84,   242,   167,    84,   244,
     168,    84,   246,   167,    84,   250,   168,    84,   254,   167,
      84,   259,   168,    84,   306,   166,    84,   310,   168,    84,
     312,   168,    84,   315,   168,    84,   319,   168,   168,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,   165,   165,   162,   161,     9,   172,   175,   181,
     187,   196,   205,   221,   238,   248,   252,   256,   261,   308,
     314,   317,   321,   325,   161,   168,   168,   166,   167,   168,
     167,   168,   168,   167,   168,   167,   168,   166,   168,   168,
     168,   168,   176,   182,   188,   197,   206,   222,   239,   249,
     253,   257,   262,   309,   318,   322,   326,   168,   183,   167,
     168,   167,   168,   168,   167,   168,   166,   168,   168,   168,
      81,   166,   189,   198,   207,   223,   258,   263,   327,   167,
     168,   167,   168,   168,   328,   190,   199,   208,   224,   329,
     167,   168,   167,   168,   168,   191,   200,   209,   225,   167,
     168,   167,   168,   192,   201,   210,   226,   167,   168,   167,
     168,   193,   202,   211,   227,   167,   168,   167,   168,   212,
     228,   167,   168,   213,   229,   167,   168,   214,   230,   167,
     168,   215,   231,   167,   168,   216,   232,   167,   168,   217,
     233,   167,   168,   218,   234,   167,   168
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (YYID (N))                                                     \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (YYID (0))
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])



/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
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
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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

  /* Discard the shifted token.  */
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
        case 3:

    { SKEL->verifyHeader((yyvsp[(1) - (1)].stringVal)); }
    break;

  case 5:

    { SKEL->profileElement((yyvsp[(2) - (2)].stringVal)); }
    break;

  case 10:

    {{
        long level;
        const char *colon = strchr((yyvsp[(2) - (2)].stringVal), ':');
        if (colon != 0)
        {
            SKEL->_tmpString1.assign((yyvsp[(2) - (2)].stringVal), colon - (yyvsp[(2) - (2)].stringVal));
            level = strtol(colon + 1, 0, 10);
        }
        else
        {
            SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal);
            level = 0;
        }
        SKEL->componentElement(SKEL->_tmpString1.c_str(), level);
    }}
    break;

  case 14:

    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); }
    break;

  case 15:

    { SKEL->metaElement(SKEL->_tmpString1.c_str(), (yyvsp[(4) - (4)].stringVal)); }
    break;

  case 25:

    { SKEL->beginNode((yyvsp[(1) - (1)].stringVal), 0); }
    break;

  case 27:

    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); }
    break;

  case 28:

    { SKEL->beginNode((yyvsp[(4) - (4)].stringVal), SKEL->_tmpString1.c_str()); }
    break;

  case 30:

    { SKEL->use((yyvsp[(2) - (2)].stringVal)); }
    break;

  case 33:

    { SKEL->beginProto((yyvsp[(2) - (2)].stringVal)); }
    break;

  case 34:

    { SKEL->endProtoInterface(); }
    break;

  case 35:

    { SKEL->endProto(); }
    break;

  case 38:

    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    break;

  case 39:

    { SKEL->beginEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->endEventDecl(); }
    break;

  case 40:

    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    break;

  case 41:

    { SKEL->beginEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->endEventDecl(); }
    break;

  case 42:

    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    break;

  case 43:

    { SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); }
    break;

  case 44:

    { SKEL->endFieldDecl(); }
    break;

  case 45:

    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    break;

  case 46:

    { SKEL->beginExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); }
    break;

  case 47:

    { SKEL->endExposedFieldDecl(); }
    break;

  case 48:

    { SKEL->beginExternProto((yyvsp[(2) - (2)].stringVal)); }
    break;

  case 49:

    { SKEL->endExternProtoInterface(); }
    break;

  case 50:

    { SKEL->endExternProto(); }
    break;

  case 53:

    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    break;

  case 54:

    { SKEL->addExternEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); }
    break;

  case 55:

    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    break;

  case 56:

    { SKEL->addExternEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); }
    break;

  case 57:

    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    break;

  case 58:

    { SKEL->addExternFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); }
    break;

  case 59:

    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    break;

  case 60:

    { SKEL->addExternExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); }
    break;

  case 61:

    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); }
    break;

  case 62:

    { SKEL->_tmpString2 = (yyvsp[(5) - (5)].stringVal); }
    break;

  case 63:

    { SKEL->_tmpString3 = (yyvsp[(8) - (8)].stringVal); }
    break;

  case 64:

    { SKEL->addRoute(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), SKEL->_tmpString3.c_str(), (yyvsp[(11) - (11)].stringVal)); }
    break;

  case 65:

    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); }
    break;

  case 66:

    { SKEL->_tmpString2 = (yyvsp[(5) - (5)].stringVal); }
    break;

  case 67:

    {
        if ((yyvsp[(7) - (7)].stringVal) != 0)
            SKEL->importElement(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), (yyvsp[(7) - (7)].stringVal));
        else
            SKEL->importElement(SKEL->_tmpString1.c_str(), SKEL->_tmpString2.c_str(), 0);
    }
    break;

  case 68:

    { SKEL->_tmpString1 = (yyvsp[(2) - (2)].stringVal); }
    break;

  case 69:

    {
        if ((yyvsp[(4) - (4)].stringVal) != 0)
            SKEL->exportElement(SKEL->_tmpString1.c_str(), (yyvsp[(4) - (4)].stringVal));
        else
            SKEL->exportElement(SKEL->_tmpString1.c_str(), 0);
    }
    break;

  case 70:

    { (yyval.stringVal) = (yyvsp[(2) - (2)].stringVal); }
    break;

  case 71:

    { (yyval.stringVal) = 0; }
    break;

  case 73:

    { SKEL->endNode(); }
    break;

  case 82:

    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    break;

  case 83:

    { SKEL->beginEventInDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); }
    break;

  case 84:

    { SKEL->endEventDecl(); }
    break;

  case 85:

    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    break;

  case 86:

    { SKEL->beginEventOutDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); }
    break;

  case 87:

    { SKEL->endEventDecl(); }
    break;

  case 89:

    { SKEL->is((yyvsp[(2) - (2)].stringVal)); }
    break;

  case 90:

    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    break;

  case 91:

    { SKEL->beginFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); }
    break;

  case 92:

    { SKEL->endFieldDecl(); }
    break;

  case 93:

    { SKEL->_tmpString1 = SKEL->getLexer()->YYText(); }
    break;

  case 94:

    { SKEL->beginExposedFieldDecl(SKEL->_tmpString1.c_str(), (yyvsp[(2) - (4)].intVal), (yyvsp[(4) - (4)].stringVal)); SKEL->getLexer()->expectType((yyvsp[(2) - (4)].intVal)); }
    break;

  case 95:

    { SKEL->endExposedFieldDecl(); }
    break;

  case 97:

    { SKEL->is((yyvsp[(3) - (3)].stringVal)); }
    break;

  case 98:

    {
        Int32 iFieldTypeId = SKEL->getFieldType((yyvsp[(1) - (1)].stringVal));
        if (SKEL->getMapFieldTypes() == true)
            iFieldTypeId = SKEL->mapExtIntFieldType((yyvsp[(1) - (1)].stringVal), iFieldTypeId);
        SKEL->getLexer()->expectType(iFieldTypeId);
        SKEL->beginField((yyvsp[(1) - (1)].stringVal), iFieldTypeId);
    }
    break;

  case 99:

    { SKEL->endField(); }
    break;

  case 105:

    { SKEL->is((yyvsp[(3) - (3)].stringVal)); }
    break;

  case 217:

    { (yyval.intVal) = (yyvsp[(1) - (1)].intVal); }
    break;

  case 218:

    { (yyval.intVal) = (yyvsp[(1) - (1)].intVal); }
    break;

  case 219:

    { (yyval.doubleVal) = (yyvsp[(1) - (1)].intVal); }
    break;

  case 220:

    { (yyval.doubleVal) = (yyvsp[(1) - (1)].doubleVal); }
    break;

  case 221:

    { (yyval.floatVal) = static_cast<float>((yyvsp[(1) - (1)].intVal)); }
    break;

  case 222:

    { (yyval.floatVal) = static_cast<float>((yyvsp[(1) - (1)].doubleVal)); }
    break;

  case 223:

    {
        SKEL->addBoolValue((yyvsp[(1) - (1)].boolVal));
    }
    break;

  case 224:

    { SKEL->addFieldValue((yyvsp[(1) - (1)].stringVal)); }
    break;

  case 225:

    { SKEL->beginValue(); }
    break;

  case 226:

    { SKEL->appendValue(); }
    break;

  case 227:

    {
        SKEL->appendValue();
        SKEL->addColorValue(Color3f((yyvsp[(1) - (5)].floatVal), (yyvsp[(3) - (5)].floatVal), (yyvsp[(5) - (5)].floatVal)));
    }
    break;

  case 228:

    { SKEL->beginValue(); }
    break;

  case 229:

    { SKEL->appendValue(); }
    break;

  case 230:

    { SKEL->appendValue(); }
    break;

  case 231:

    {
        SKEL->appendValue();
        SKEL->addColorRGBAValue(Color4f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal), (yyvsp[(7) - (7)].floatVal)));
    }
    break;

  case 232:

    {
        SKEL->addDoubleValue((yyvsp[(1) - (1)].doubleVal));
    }
    break;

  case 233:

    {
        SKEL->addFloatValue((yyvsp[(1) - (1)].floatVal));
    }
    break;

  case 234:

    { SKEL->beginValue(); }
    break;

  case 235:

    { SKEL->appendValue(); }
    break;

  case 236:

    {
        SKEL->appendValue();
        SKEL->beginImage((yyvsp[(1) - (5)].intVal), (yyvsp[(3) - (5)].intVal), (yyvsp[(5) - (5)].intVal));
    }
    break;

  case 237:

    {
        SKEL->endImage();
    }
    break;

  case 238:

    {
        SKEL->addImagePixel((yyvsp[(2) - (2)].intVal));
    }
    break;

  case 240:

    {
        SKEL->addInt32Value((yyvsp[(1) - (1)].intVal));
    }
    break;

  case 241:

    { SKEL->beginValue(); }
    break;

  case 242:

    { SKEL->appendValue(); }
    break;

  case 243:

    { SKEL->appendValue(); }
    break;

  case 244:

    { SKEL->appendValue(); }
    break;

  case 245:

    { SKEL->appendValue(); }
    break;

  case 246:

    { SKEL->appendValue(); }
    break;

  case 247:

    { SKEL->appendValue(); }
    break;

  case 248:

    { SKEL->appendValue(); }
    break;

  case 249:

    {
        SKEL->appendValue();
        SKEL->addMatrix3dValue(
            (yyvsp[(1) - (17)].doubleVal),  (yyvsp[(7) - (17)].doubleVal), (yyvsp[(13) - (17)].doubleVal),
            (yyvsp[(3) - (17)].doubleVal),  (yyvsp[(9) - (17)].doubleVal), (yyvsp[(15) - (17)].doubleVal),
            (yyvsp[(5) - (17)].doubleVal), (yyvsp[(11) - (17)].doubleVal), (yyvsp[(17) - (17)].doubleVal));
    }
    break;

  case 250:

    { SKEL->beginValue(); }
    break;

  case 251:

    { SKEL->appendValue(); }
    break;

  case 252:

    { SKEL->appendValue(); }
    break;

  case 253:

    { SKEL->appendValue(); }
    break;

  case 254:

    { SKEL->appendValue(); }
    break;

  case 255:

    { SKEL->appendValue(); }
    break;

  case 256:

    { SKEL->appendValue(); }
    break;

  case 257:

    { SKEL->appendValue(); }
    break;

  case 258:

    {
        SKEL->appendValue();
        SKEL->addMatrix3fValue(
            (yyvsp[(1) - (17)].floatVal),  (yyvsp[(7) - (17)].floatVal), (yyvsp[(13) - (17)].floatVal),
            (yyvsp[(3) - (17)].floatVal),  (yyvsp[(9) - (17)].floatVal), (yyvsp[(15) - (17)].floatVal),
            (yyvsp[(5) - (17)].floatVal), (yyvsp[(11) - (17)].floatVal), (yyvsp[(17) - (17)].floatVal));
    }
    break;

  case 259:

    { SKEL->beginValue(); }
    break;

  case 260:

    { SKEL->appendValue(); }
    break;

  case 261:

    { SKEL->appendValue(); }
    break;

  case 262:

    { SKEL->appendValue(); }
    break;

  case 263:

    { SKEL->appendValue(); }
    break;

  case 264:

    { SKEL->appendValue(); }
    break;

  case 265:

    { SKEL->appendValue(); }
    break;

  case 266:

    { SKEL->appendValue(); }
    break;

  case 267:

    { SKEL->appendValue(); }
    break;

  case 268:

    { SKEL->appendValue(); }
    break;

  case 269:

    { SKEL->appendValue(); }
    break;

  case 270:

    { SKEL->appendValue(); }
    break;

  case 271:

    { SKEL->appendValue(); }
    break;

  case 272:

    { SKEL->appendValue(); }
    break;

  case 273:

    { SKEL->appendValue(); }
    break;

  case 274:

    {
        SKEL->appendValue();
        SKEL->addMatrix4dValue(Matrix4d(
            (yyvsp[(1) - (31)].doubleVal),  (yyvsp[(9) - (31)].doubleVal), (yyvsp[(17) - (31)].doubleVal), (yyvsp[(25) - (31)].doubleVal),
            (yyvsp[(3) - (31)].doubleVal), (yyvsp[(11) - (31)].doubleVal), (yyvsp[(19) - (31)].doubleVal), (yyvsp[(27) - (31)].doubleVal),
            (yyvsp[(5) - (31)].doubleVal), (yyvsp[(13) - (31)].doubleVal), (yyvsp[(21) - (31)].doubleVal), (yyvsp[(29) - (31)].doubleVal),
            (yyvsp[(7) - (31)].doubleVal), (yyvsp[(15) - (31)].doubleVal), (yyvsp[(23) - (31)].doubleVal), (yyvsp[(31) - (31)].doubleVal)));
    }
    break;

  case 275:

    { SKEL->beginValue(); }
    break;

  case 276:

    { SKEL->appendValue(); }
    break;

  case 277:

    { SKEL->appendValue(); }
    break;

  case 278:

    { SKEL->appendValue(); }
    break;

  case 279:

    { SKEL->appendValue(); }
    break;

  case 280:

    { SKEL->appendValue(); }
    break;

  case 281:

    { SKEL->appendValue(); }
    break;

  case 282:

    { SKEL->appendValue(); }
    break;

  case 283:

    { SKEL->appendValue(); }
    break;

  case 284:

    { SKEL->appendValue(); }
    break;

  case 285:

    { SKEL->appendValue(); }
    break;

  case 286:

    { SKEL->appendValue(); }
    break;

  case 287:

    { SKEL->appendValue(); }
    break;

  case 288:

    { SKEL->appendValue(); }
    break;

  case 289:

    { SKEL->appendValue(); }
    break;

  case 290:

    {
        SKEL->appendValue();
        SKEL->addMatrix4fValue(Matrix4f(
            (yyvsp[(1) - (31)].floatVal),  (yyvsp[(9) - (31)].floatVal), (yyvsp[(17) - (31)].floatVal), (yyvsp[(25) - (31)].floatVal),
            (yyvsp[(3) - (31)].floatVal), (yyvsp[(11) - (31)].floatVal), (yyvsp[(19) - (31)].floatVal), (yyvsp[(27) - (31)].floatVal),
            (yyvsp[(5) - (31)].floatVal), (yyvsp[(13) - (31)].floatVal), (yyvsp[(21) - (31)].floatVal), (yyvsp[(29) - (31)].floatVal),
            (yyvsp[(7) - (31)].floatVal), (yyvsp[(15) - (31)].floatVal), (yyvsp[(23) - (31)].floatVal), (yyvsp[(31) - (31)].floatVal)));
    }
    break;

  case 293:

    { SKEL->beginValue(); }
    break;

  case 294:

    { SKEL->appendValue(); }
    break;

  case 295:

    { SKEL->appendValue(); }
    break;

  case 296:

    {
        SKEL->appendValue();
        SKEL->addRotationValue(Vec3f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal)), (yyvsp[(7) - (7)].floatVal));
    }
    break;

  case 297:

    {
        SKEL->addStringValue((yyvsp[(1) - (1)].stringVal));
    }
    break;

  case 298:

    { /* Not VRML conformant */
        SKEL->addStringValue((yyvsp[(1) - (1)].stringVal));
    }
    break;

  case 299:

    {
        SKEL->addTimeValue((yyvsp[(1) - (1)].doubleVal));
    }
    break;

  case 300:

    { SKEL->beginValue(); }
    break;

  case 301:

    {
        SKEL->appendValue();
        SKEL->addVec2dValue(Vec2d((yyvsp[(1) - (3)].doubleVal), (yyvsp[(3) - (3)].doubleVal)));
    }
    break;

  case 302:

    { SKEL->beginValue(); }
    break;

  case 303:

    {
        SKEL->appendValue();
        SKEL->addVec2fValue(Vec2f((yyvsp[(1) - (3)].floatVal), (yyvsp[(3) - (3)].floatVal)));
    }
    break;

  case 304:

    { SKEL->beginValue(); }
    break;

  case 305:

    { SKEL->appendValue(); }
    break;

  case 306:

    { SKEL->appendValue(); }
    break;

  case 307:

    {
        SKEL->appendValue();
        SKEL->addVec3dValue(Vec3d((yyvsp[(1) - (6)].doubleVal), (yyvsp[(3) - (6)].doubleVal), (yyvsp[(5) - (6)].doubleVal)));
    }
    break;

  case 308:

    { SKEL->beginValue(); }
    break;

  case 309:

    { SKEL->appendValue(); }
    break;

  case 310:

    { SKEL->appendValue(); }
    break;

  case 311:

    {
        SKEL->appendValue();
        SKEL->addVec3fValue(Vec3f((yyvsp[(1) - (6)].floatVal), (yyvsp[(3) - (6)].floatVal), (yyvsp[(5) - (6)].floatVal)));
    }
    break;

  case 312:

    { SKEL->beginValue(); }
    break;

  case 313:

    { SKEL->appendValue(); }
    break;

  case 314:

    { SKEL->appendValue(); }
    break;

  case 315:

    { SKEL->appendValue(); }
    break;

  case 316:

    {
        SKEL->appendValue();
        SKEL->addVec4dValue(Vec4d((yyvsp[(1) - (8)].doubleVal), (yyvsp[(3) - (8)].doubleVal), (yyvsp[(5) - (8)].doubleVal), (yyvsp[(7) - (8)].doubleVal)));
    }
    break;

  case 317:

    { SKEL->beginValue(); }
    break;

  case 318:

    { SKEL->appendValue(); }
    break;

  case 319:

    { SKEL->appendValue(); }
    break;

  case 320:

    { SKEL->appendValue(); }
    break;

  case 321:

    {
        SKEL->appendValue();
        SKEL->addVec4fValue(Vec4f((yyvsp[(1) - (8)].floatVal), (yyvsp[(3) - (8)].floatVal), (yyvsp[(5) - (8)].floatVal), (yyvsp[(7) - (8)].floatVal)));
    }
    break;

  case 407:

    { SKEL->beginValue(); }
    break;

  case 408:

    { SKEL->appendValue(); }
    break;

  case 409:

    { SKEL->appendValue(); }
    break;

  case 410:

    {
        SKEL->appendValue();
        SKEL->addColor4iValue(Color4ub(static_cast<UInt8>((yyvsp[(1) - (7)].intVal)), static_cast<UInt8>((yyvsp[(3) - (7)].intVal)),
                                       static_cast<UInt8>((yyvsp[(5) - (7)].intVal)), static_cast<UInt8>((yyvsp[(7) - (7)].intVal))));
    }
    break;

  case 411:

    { SKEL->beginValue(); }
    break;

  case 412:

    {
        SKEL->appendValue();
        SKEL->addPnt2fValue(Pnt2f((yyvsp[(1) - (3)].floatVal), (yyvsp[(3) - (3)].floatVal)));
    }
    break;

  case 413:

    { SKEL->beginValue(); }
    break;

  case 414:

    { SKEL->appendValue(); }
    break;

  case 415:

    {
        SKEL->appendValue();
        SKEL->addPnt3fValue(Pnt3f((yyvsp[(1) - (5)].floatVal), (yyvsp[(3) - (5)].floatVal), (yyvsp[(5) - (5)].floatVal)));
    }
    break;

  case 416:

    { SKEL->beginValue(); }
    break;

  case 417:

    { SKEL->appendValue(); }
    break;

  case 418:

    { SKEL->appendValue(); }
    break;

  case 419:

    {
        SKEL->appendValue();
        SKEL->addPnt4fValue(Pnt4f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal), (yyvsp[(7) - (7)].floatVal)));
    }
    break;

  case 420:

    { SKEL->beginValue(); }
    break;

  case 421:

    { SKEL->appendValue(); }
    break;

  case 422:

    { SKEL->appendValue(); }
    break;

  case 423:

    {
        SKEL->appendValue();
        SKEL->addPlaneValue(Plane(Vec3f((yyvsp[(1) - (7)].floatVal), (yyvsp[(3) - (7)].floatVal), (yyvsp[(5) - (7)].floatVal)), (yyvsp[(7) - (7)].floatVal)));
    }
    break;

  case 424:

    { SKEL->beginValue(); }
    break;

  case 425:

    { SKEL->appendValue(); }
    break;

  case 426:

    { SKEL->appendValue(); }
    break;

  case 427:

    {
        SKEL->appendValue();
        SKEL->_tmpFloat1 = (yyvsp[(1) - (7)].floatVal); SKEL->_tmpFloat2 = (yyvsp[(3) - (7)].floatVal);
        SKEL->_tmpFloat3 = (yyvsp[(5) - (7)].floatVal); SKEL->_tmpFloat4 = (yyvsp[(7) - (7)].floatVal);
    }
    break;

  case 429:

    { SKEL->appendValue(); }
    break;

  case 430:

    {
        SKEL->appendValue();
#ifndef OSG_2_PREP
        DynamicVolume dv(DynamicVolume::BOX_VOLUME);
        BoxVolume &bv = dynamic_cast<BoxVolume&>(dv.getInstance());
        bv.setBounds(SKEL->_tmpFloat1, SKEL->_tmpFloat2, SKEL->_tmpFloat3, SKEL->_tmpFloat4, (yyvsp[(1) - (3)].floatVal), (yyvsp[(3) - (3)].floatVal));
        SKEL->addVolumeValue(dv);
#else
        BoxVolume  bv;
        bv.setBounds(SKEL->_tmpFloat1, SKEL->_tmpFloat2, SKEL->_tmpFloat3, SKEL->_tmpFloat4, (yyvsp[(1) - (3)].floatVal), (yyvsp[(3) - (3)].floatVal));
        SKEL->addVolumeValue(bv);
#endif
    }
    break;

  case 431:

    {
#ifndef OSG_2_PREP
        DynamicVolume dv(DynamicVolume::SPHERE_VOLUME);
        SphereVolume &sv = dynamic_cast<SphereVolume&>(dv.getInstance());
        sv.setValue(Pnt3f(SKEL->_tmpFloat1, SKEL->_tmpFloat2, SKEL->_tmpFloat3), SKEL->_tmpFloat4);
        SKEL->addVolumeValue(dv);
#else
        FFASSERT(false, 0, ("ScanParseSkel::sfVolumeValueEnd: Can not parse sphere volume.\n");)
#endif
    }
    break;



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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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
      if (!yypact_value_is_default (yyn))
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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
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





int OSGScanParseSkel_lex(YYSTYPE *lvalp, void *pSkel)
{
    return SKEL->lex(lvalp);
}

