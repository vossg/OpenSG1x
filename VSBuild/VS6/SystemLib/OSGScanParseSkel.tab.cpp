/* A Bison parser, made from ../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y, by GNU bison 1.75.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON	1

/* Pure parsers.  */
#define YYPURE	0

/* Using locations.  */
#define YYLSP_NEEDED 0

/* If NAME_PREFIX is specified substitute the variables and functions
   names.  */
#define yyparse OSGScanParseSkel_parse
#define yylex   OSGScanParseSkel_lex
#define yyerror OSGScanParseSkel_error
#define yylval  OSGScanParseSkel_lval
#define yychar  OSGScanParseSkel_char
#define yydebug OSGScanParseSkel_debug
#define yynerrs OSGScanParseSkel_nerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     DEF = 258,
     USE = 259,
     ROUTE = 260,
     PERIOD = 261,
     TO = 262,
     OPENBRACE = 263,
     CLOSEBRACE = 264,
     ID = 265,
     PROTO = 266,
     OPENBRACKET = 267,
     CLOSEBRACKET = 268,
     EXTERNPROTO = 269,
     IS = 270,
     EVENTIN = 271,
     EVENTOUT = 272,
     EXPOSEDFIELD = 273,
     FIELD = 274,
     SCRIPT = 275,
     SFN_NULL = 276,
     TOK_SFBOOL = 277,
     TOK_SFCOLOR = 278,
     TOK_SFFLOAT = 279,
     TOK_SFIMAGE = 280,
     TOK_SFINT32 = 281,
     TOK_SFNODE = 282,
     TOK_SFROTATION = 283,
     TOK_SFSTRING = 284,
     TOK_SFTIME = 285,
     TOK_SFVEC2F = 286,
     TOK_SFVEC3F = 287,
     TOK_MFCOLOR = 288,
     TOK_MFFLOAT = 289,
     TOK_MFINT32 = 290,
     TOK_MFNODE = 291,
     TOK_MFROTATION = 292,
     TOK_MFSTRING = 293,
     TOK_MFTIME = 294,
     TOK_MFVEC2F = 295,
     TOK_MFVEC3F = 296,
     Tok_MFColor = 297,
     Tok_MFFloat = 298,
     Tok_MFInt32 = 299,
     Tok_MFNode = 300,
     Tok_MFRotation = 301,
     Tok_MFString = 302,
     Tok_MFTime = 303,
     Tok_MFVec2f = 304,
     Tok_MFVec3f = 305,
     Tok_SFBool = 306,
     Tok_SFColor = 307,
     Tok_SFFloat = 308,
     Tok_SFImage = 309,
     Tok_SFInt32 = 310,
     Tok_SFNode = 311,
     Tok_SFRotation = 312,
     Tok_SFString = 313,
     Tok_SFTime = 314,
     Tok_SFVec2f = 315,
     Tok_SFVec3f = 316,
     TOK_MFCOLOR4F = 317,
     TOK_MFCOLOR4I = 318,
     TOK_MFCOLOR3F = 319,
     TOK_MFMATRIX = 320,
     TOK_MFPNT2F = 321,
     TOK_MFPNT3F = 322,
     TOK_MFPNT4F = 323,
     TOK_MFVEC4F = 324,
     TOK_MFPLANE = 325,
     TOK_SFCOLOR4F = 326,
     TOK_SFCOLOR4I = 327,
     TOK_SFCOLOR3F = 328,
     TOK_SFMATRIX = 329,
     TOK_SFPNT2F = 330,
     TOK_SFPNT3F = 331,
     TOK_SFPNT4F = 332,
     TOK_SFVEC4F = 333,
     TOK_SFPLANE = 334,
     TOK_SFVOLUME = 335,
     Tok_MFColor4f = 336,
     Tok_MFColor4i = 337,
     Tok_MFColor3f = 338,
     Tok_MFMatrix = 339,
     Tok_MFPnt2f = 340,
     Tok_MFPnt3f = 341,
     Tok_MFPnt4f = 342,
     Tok_MFVec4f = 343,
     Tok_MFPlane = 344,
     Tok_SFColor4f = 345,
     Tok_SFColor4i = 346,
     Tok_SFColor3f = 347,
     Tok_SFMatrix = 348,
     Tok_SFPnt2f = 349,
     Tok_SFPnt3f = 350,
     Tok_SFPnt4f = 351,
     Tok_SFVec4f = 352,
     Tok_SFPlane = 353,
     Tok_SFVolume = 354
   };
#endif
#define DEF 258
#define USE 259
#define ROUTE 260
#define PERIOD 261
#define TO 262
#define OPENBRACE 263
#define CLOSEBRACE 264
#define ID 265
#define PROTO 266
#define OPENBRACKET 267
#define CLOSEBRACKET 268
#define EXTERNPROTO 269
#define IS 270
#define EVENTIN 271
#define EVENTOUT 272
#define EXPOSEDFIELD 273
#define FIELD 274
#define SCRIPT 275
#define SFN_NULL 276
#define TOK_SFBOOL 277
#define TOK_SFCOLOR 278
#define TOK_SFFLOAT 279
#define TOK_SFIMAGE 280
#define TOK_SFINT32 281
#define TOK_SFNODE 282
#define TOK_SFROTATION 283
#define TOK_SFSTRING 284
#define TOK_SFTIME 285
#define TOK_SFVEC2F 286
#define TOK_SFVEC3F 287
#define TOK_MFCOLOR 288
#define TOK_MFFLOAT 289
#define TOK_MFINT32 290
#define TOK_MFNODE 291
#define TOK_MFROTATION 292
#define TOK_MFSTRING 293
#define TOK_MFTIME 294
#define TOK_MFVEC2F 295
#define TOK_MFVEC3F 296
#define Tok_MFColor 297
#define Tok_MFFloat 298
#define Tok_MFInt32 299
#define Tok_MFNode 300
#define Tok_MFRotation 301
#define Tok_MFString 302
#define Tok_MFTime 303
#define Tok_MFVec2f 304
#define Tok_MFVec3f 305
#define Tok_SFBool 306
#define Tok_SFColor 307
#define Tok_SFFloat 308
#define Tok_SFImage 309
#define Tok_SFInt32 310
#define Tok_SFNode 311
#define Tok_SFRotation 312
#define Tok_SFString 313
#define Tok_SFTime 314
#define Tok_SFVec2f 315
#define Tok_SFVec3f 316
#define TOK_MFCOLOR4F 317
#define TOK_MFCOLOR4I 318
#define TOK_MFCOLOR3F 319
#define TOK_MFMATRIX 320
#define TOK_MFPNT2F 321
#define TOK_MFPNT3F 322
#define TOK_MFPNT4F 323
#define TOK_MFVEC4F 324
#define TOK_MFPLANE 325
#define TOK_SFCOLOR4F 326
#define TOK_SFCOLOR4I 327
#define TOK_SFCOLOR3F 328
#define TOK_SFMATRIX 329
#define TOK_SFPNT2F 330
#define TOK_SFPNT3F 331
#define TOK_SFPNT4F 332
#define TOK_SFVEC4F 333
#define TOK_SFPLANE 334
#define TOK_SFVOLUME 335
#define Tok_MFColor4f 336
#define Tok_MFColor4i 337
#define Tok_MFColor3f 338
#define Tok_MFMatrix 339
#define Tok_MFPnt2f 340
#define Tok_MFPnt3f 341
#define Tok_MFPnt4f 342
#define Tok_MFVec4f 343
#define Tok_MFPlane 344
#define Tok_SFColor4f 345
#define Tok_SFColor4i 346
#define Tok_SFColor3f 347
#define Tok_SFMatrix 348
#define Tok_SFPnt2f 349
#define Tok_SFPnt3f 350
#define Tok_SFPnt4f 351
#define Tok_SFVec4f 352
#define Tok_SFPlane 353
#define Tok_SFVolume 354




/* Copy the first part of user declarations.  */
#line 38 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"


#define YYLTYPE_IS_TRIVIAL 1

#ifdef WIN32
#include <malloc.h>
#define YYSIZE_T size_t
#endif
#include <OSGScanParseSkel.tab.h>
#include <OSGConfig.h>

#include <OSGBaseFunctions.h>
#include <OSGScanParseSkel.h>
#include <stack>

#if defined(OSG_LINUX_ICC) || defined(OSG_WIN32_ICL)
#pragma warning( disable : 193 810 177 )
#endif

OSG_USING_NAMESPACE

ScanParseSkel *_pSkel = NULL;



extern int  iLineNum;
extern char OSGScanParseSkel_text[];

extern int  yylex     (void);
extern void expectType(int iType);

int nextType;

void OSGScanParseSkel_error(char *s);

char *szName1    = NULL;
char *szName2    = NULL;
char *szName3    = NULL;

void setName (char *&szName, const char *szVal);
void freeName(char *&szName);



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#ifndef YYSTYPE
typedef int yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif

#ifndef YYLTYPE
typedef struct yyltype
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} yyltype;
# define YYLTYPE yyltype
# define YYLTYPE_IS_TRIVIAL 1
#endif

/* Copy the second part of user declarations.  */


/* Line 213 of /usr/share/bison/yacc.c.  */
#line 344 "OSGScanParseSkel_.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];	\
	}					\
      while (0)
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
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  29
#define YYLAST   437

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  100
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  67
/* YYNRULES -- Number of rules. */
#define YYNRULES  182
/* YYNRULES -- Number of states. */
#define YYNSTATES  247

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   354

#define YYTRANSLATE(X) \
  ((unsigned)(X) <= YYMAXUTOK ? yytranslate[X] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    12,    14,    16,    18,
      20,    22,    23,    28,    31,    33,    34,    39,    41,    43,
      45,    46,    49,    51,    53,    55,    64,    66,    68,    72,
      74,    76,    79,    81,    82,    87,    88,    93,    94,    95,
     102,   104,   105,   106,   113,   120,   122,   124,   127,   129,
     133,   137,   141,   145,   146,   147,   148,   160,   162,   163,
     164,   170,   171,   177,   179,   181,   184,   186,   188,   190,
     193,   195,   196,   201,   202,   207,   210,   211,   212,   217,
     220,   222,   224,   227,   230,   231,   235,   237,   239,   242,
     244,   246,   248,   250,   252,   254,   256,   258,   260,   262,
     264,   266,   268,   270,   272,   274,   276,   278,   280,   282,
     284,   286,   288,   290,   292,   294,   296,   298,   300,   302,
     304,   306,   308,   310,   312,   314,   316,   318,   320,   322,
     324,   326,   328,   330,   332,   334,   336,   338,   340,   342,
     344,   346,   349,   351,   353,   355,   357,   359,   361,   363,
     365,   368,   370,   372,   374,   376,   378,   380,   382,   384,
     386,   388,   390,   392,   394,   396,   398,   400,   402,   404,
     406,   408,   410,   412,   414,   416,   418,   420,   422,   426,
     428,   430,   433
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short yyrhs[] =
{
     101,     0,    -1,   102,    -1,   103,    -1,   135,    -1,   103,
     104,    -1,   104,    -1,   105,    -1,   109,    -1,   130,    -1,
     136,    -1,    -1,     3,   155,   106,   136,    -1,     4,   155,
      -1,   136,    -1,    -1,     3,   155,   108,   136,    -1,   113,
      -1,   126,    -1,   111,    -1,    -1,   111,   109,    -1,   109,
      -1,   156,    -1,    20,    -1,    11,   112,    12,   116,    13,
       8,   114,     9,    -1,   115,    -1,   135,    -1,   110,   107,
     102,    -1,   117,    -1,   135,    -1,   117,   123,    -1,   123,
      -1,    -1,    16,   161,   119,   159,    -1,    -1,    17,   161,
     120,   160,    -1,    -1,    -1,    19,   161,   121,   157,   122,
     162,    -1,   118,    -1,    -1,    -1,    18,   161,   124,   157,
     125,   162,    -1,    14,   156,    12,   127,    13,   134,    -1,
     128,    -1,   135,    -1,   128,   129,    -1,   129,    -1,    16,
     161,   159,    -1,    17,   161,   160,    -1,    19,   161,   157,
      -1,    18,   161,   157,    -1,    -1,    -1,    -1,     5,   155,
     131,     6,   160,   132,     7,   155,   133,     6,   159,    -1,
     162,    -1,    -1,    -1,   156,   137,     8,   139,     9,    -1,
      -1,    20,   138,     8,   141,     9,    -1,   140,    -1,   135,
      -1,   140,   151,    -1,   151,    -1,   142,    -1,   135,    -1,
     142,   150,    -1,   150,    -1,    -1,    16,   161,   144,   159,
      -1,    -1,    17,   161,   145,   160,    -1,    15,   158,    -1,
      -1,    -1,    19,   161,   148,   157,    -1,    15,   157,    -1,
     162,    -1,   151,    -1,   143,   146,    -1,   147,   149,    -1,
      -1,   157,   152,   153,    -1,   130,    -1,   109,    -1,    15,
     154,    -1,   162,    -1,    10,    -1,    10,    -1,    10,    -1,
      10,    -1,    10,    -1,    10,    -1,    10,    -1,    42,    -1,
      43,    -1,    44,    -1,    45,    -1,    46,    -1,    47,    -1,
      48,    -1,    49,    -1,    50,    -1,    51,    -1,    52,    -1,
      53,    -1,    54,    -1,    55,    -1,    56,    -1,    57,    -1,
      58,    -1,    59,    -1,    60,    -1,    61,    -1,    81,    -1,
      82,    -1,    83,    -1,    84,    -1,    85,    -1,    86,    -1,
      87,    -1,    88,    -1,    89,    -1,    90,    -1,    91,    -1,
      92,    -1,    93,    -1,    94,    -1,    95,    -1,    96,    -1,
      97,    -1,    98,    -1,    99,    -1,    22,    -1,    23,    -1,
      24,    -1,    25,    -1,    26,    -1,    27,   163,    -1,    28,
      -1,    29,    -1,    30,    -1,    31,    -1,    32,    -1,    33,
      -1,    34,    -1,    35,    -1,    36,   164,    -1,    37,    -1,
      38,    -1,    39,    -1,    40,    -1,    41,    -1,    62,    -1,
      63,    -1,    64,    -1,    65,    -1,    66,    -1,    67,    -1,
      68,    -1,    70,    -1,    69,    -1,    71,    -1,    72,    -1,
      73,    -1,    74,    -1,    75,    -1,    76,    -1,    77,    -1,
      79,    -1,    80,    -1,    78,    -1,   105,    -1,    21,    -1,
     105,    -1,    12,   165,    13,    -1,   166,    -1,   135,    -1,
     166,   105,    -1,   105,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   194,   194,   197,   198,   201,   202,   205,   206,   207,
     210,   212,   211,   214,   219,   221,   220,   225,   226,   230,
     231,   234,   235,   238,   240,   244,   255,   256,   259,   262,
     263,   266,   267,   272,   271,   280,   279,   288,   290,   287,
     303,   305,   307,   304,   319,   327,   328,   331,   333,   336,
     337,   338,   339,   343,   345,   347,   342,   360,   363,   366,
     366,   375,   375,   386,   387,   390,   391,   394,   395,   398,
     399,   403,   402,   412,   411,   422,   423,   427,   426,   442,
     452,   469,   470,   472,   478,   477,   500,   501,   506,   512,
     518,   521,   524,   527,   530,   533,   536,   539,   540,   541,
     542,   543,   544,   545,   546,   547,   548,   549,   550,   551,
     552,   553,   554,   555,   556,   557,   558,   559,   560,   561,
     562,   563,   564,   565,   566,   567,   568,   569,   570,   571,
     572,   573,   574,   575,   576,   577,   581,   582,   583,   584,
     585,   586,   587,   588,   589,   590,   591,   592,   593,   594,
     595,   596,   597,   598,   599,   600,   601,   602,   603,   604,
     605,   606,   607,   608,   609,   610,   611,   612,   613,   614,
     615,   616,   617,   618,   619,   623,   624,   627,   628,   631,
     632,   635,   636
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DEF", "USE", "ROUTE", "PERIOD", "TO", 
  "OPENBRACE", "CLOSEBRACE", "ID", "PROTO", "OPENBRACKET", "CLOSEBRACKET", 
  "EXTERNPROTO", "IS", "EVENTIN", "EVENTOUT", "EXPOSEDFIELD", "FIELD", 
  "SCRIPT", "SFN_NULL", "TOK_SFBOOL", "TOK_SFCOLOR", "TOK_SFFLOAT", 
  "TOK_SFIMAGE", "TOK_SFINT32", "TOK_SFNODE", "TOK_SFROTATION", 
  "TOK_SFSTRING", "TOK_SFTIME", "TOK_SFVEC2F", "TOK_SFVEC3F", 
  "TOK_MFCOLOR", "TOK_MFFLOAT", "TOK_MFINT32", "TOK_MFNODE", 
  "TOK_MFROTATION", "TOK_MFSTRING", "TOK_MFTIME", "TOK_MFVEC2F", 
  "TOK_MFVEC3F", "Tok_MFColor", "Tok_MFFloat", "Tok_MFInt32", 
  "Tok_MFNode", "Tok_MFRotation", "Tok_MFString", "Tok_MFTime", 
  "Tok_MFVec2f", "Tok_MFVec3f", "Tok_SFBool", "Tok_SFColor", 
  "Tok_SFFloat", "Tok_SFImage", "Tok_SFInt32", "Tok_SFNode", 
  "Tok_SFRotation", "Tok_SFString", "Tok_SFTime", "Tok_SFVec2f", 
  "Tok_SFVec3f", "TOK_MFCOLOR4F", "TOK_MFCOLOR4I", "TOK_MFCOLOR3F", 
  "TOK_MFMATRIX", "TOK_MFPNT2F", "TOK_MFPNT3F", "TOK_MFPNT4F", 
  "TOK_MFVEC4F", "TOK_MFPLANE", "TOK_SFCOLOR4F", "TOK_SFCOLOR4I", 
  "TOK_SFCOLOR3F", "TOK_SFMATRIX", "TOK_SFPNT2F", "TOK_SFPNT3F", 
  "TOK_SFPNT4F", "TOK_SFVEC4F", "TOK_SFPLANE", "TOK_SFVOLUME", 
  "Tok_MFColor4f", "Tok_MFColor4i", "Tok_MFColor3f", "Tok_MFMatrix", 
  "Tok_MFPnt2f", "Tok_MFPnt3f", "Tok_MFPnt4f", "Tok_MFVec4f", 
  "Tok_MFPlane", "Tok_SFColor4f", "Tok_SFColor4i", "Tok_SFColor3f", 
  "Tok_SFMatrix", "Tok_SFPnt2f", "Tok_SFPnt3f", "Tok_SFPnt4f", 
  "Tok_SFVec4f", "Tok_SFPlane", "Tok_SFVolume", "$accept", "vrmlScene", 
  "statementsORempty", "statements", "statement", "nodeStatement", "@1", 
  "rootNodeStatement", "@2", "protoStatement", "protoStatementsORempty", 
  "protoStatements", "protoId", "proto", "protoBodyORempty", "protoBody", 
  "interfaceDeclarationsORempty", "interfaceDeclarations", 
  "restrictedInterfaceDeclaration", "@3", "@4", "@5", "@6", 
  "interfaceDeclaration", "@7", "@8", "externproto", 
  "externInterfaceDeclarationsORempty", "externInterfaceDeclarations", 
  "externInterfaceDeclaration", "routeStatement", "@9", "@10", "@11", 
  "URLList", "empty", "node", "@12", "@13", "nodeBodyORempty", "nodeBody", 
  "scriptBodyORempty", "scriptBody", "resInterfaceDeclarationScriptEvent", 
  "@14", "@15", "resInterfaceDeclarationScriptEventEnd", 
  "resInterfaceDeclarationScriptField", "@16", 
  "resInterafceDeclarationScriptFieldEnd", "scriptBodyElement", 
  "nodeBodyElement", "@17", "fieldEnd", "generalId", "nodeNameId", 
  "nodeTypeId", "fieldId", "eventId", "eventInId", "eventOutId", 
  "fieldType", "fieldValue", "sfnodeValue", "mfnodeValue", 
  "nodeStatementsORempty", "nodeStatements", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,   100,   101,   102,   102,   103,   103,   104,   104,   104,
     105,   106,   105,   105,   107,   108,   107,   109,   109,   110,
     110,   111,   111,   112,   112,   113,   114,   114,   115,   116,
     116,   117,   117,   119,   118,   120,   118,   121,   122,   118,
     123,   124,   125,   123,   126,   127,   127,   128,   128,   129,
     129,   129,   129,   131,   132,   133,   130,   134,   135,   137,
     136,   138,   136,   139,   139,   140,   140,   141,   141,   142,
     142,   144,   143,   145,   143,   146,   146,   148,   147,   149,
     149,   150,   150,   150,   152,   151,   151,   151,   153,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   163,   163,   164,   164,   165,
     165,   166,   166
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     0,     4,     2,     1,     0,     4,     1,     1,     1,
       0,     2,     1,     1,     1,     8,     1,     1,     3,     1,
       1,     2,     1,     0,     4,     0,     4,     0,     0,     6,
       1,     0,     0,     6,     6,     1,     1,     2,     1,     3,
       3,     3,     3,     0,     0,     0,    11,     1,     0,     0,
       5,     0,     5,     1,     1,     2,     1,     1,     1,     2,
       1,     0,     4,     0,     4,     2,     0,     0,     4,     2,
       1,     1,     2,     2,     0,     3,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     2,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
      58,     0,     0,     0,    92,     0,     0,    61,     0,     2,
       3,     6,     7,     8,    17,    18,     9,     4,    10,    59,
      91,    11,    13,    53,    24,     0,    23,     0,     0,     1,
       5,     0,     0,     0,    58,    58,    58,    58,    12,     0,
       0,     0,     0,     0,     0,    29,    40,    32,    30,     0,
       0,     0,     0,     0,    45,    48,    46,    93,     0,     0,
       0,    87,    86,    68,     0,    67,    76,     0,    70,    81,
      84,    64,     0,    63,    66,    96,    54,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,    33,    35,    41,    37,
       0,    31,     0,     0,     0,     0,     0,    47,    71,    73,
      77,    62,    69,     0,    82,     0,   136,   137,   138,   139,
     140,     0,   142,   143,   144,   145,   146,   147,   148,   149,
       0,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   164,   163,   165,   166,   167,   168,   169,
     170,   171,   174,   172,   173,    83,    80,     0,    60,    65,
       0,     0,     0,     0,     0,    20,    95,    49,    50,    52,
      51,    44,    57,     0,     0,     0,    94,    75,    79,   176,
     175,   141,    58,   177,   150,     0,    85,    89,     0,    34,
      36,    42,    38,    22,     0,    19,     0,    26,    27,    72,
      74,    78,   182,   180,     0,   179,    90,    88,    55,     0,
       0,     0,    58,    14,    21,    25,   178,   181,     0,    43,
      39,    15,    28,     0,     0,    56,    16
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     8,     9,    10,    11,    12,    32,   232,   244,    61,
     214,   215,    25,    14,   216,   217,    44,    45,    46,   181,
     182,   184,   230,    47,   183,   229,    15,    53,    54,    55,
      62,    33,   180,   238,   191,    17,    18,    31,    28,    72,
      73,    64,    65,    66,   193,   194,   134,    67,   195,   175,
      68,    69,   177,   206,   227,    21,    19,    70,   197,   187,
      76,   116,   176,   201,   204,   224,   225
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -174
static const short yypact[] =
{
      45,     9,     9,     9,  -174,    26,    32,  -174,    52,  -174,
      45,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,  -174,    41,  -174,    48,    53,  -174,
    -174,    63,    27,    61,    78,    92,    73,    88,  -174,    62,
     338,   338,   338,   338,    60,    78,  -174,  -174,  -174,   338,
     338,   338,   338,    68,    92,  -174,  -174,  -174,   338,   338,
     338,  -174,  -174,  -174,    77,    73,    86,   213,  -174,  -174,
    -174,  -174,    95,    88,  -174,  -174,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
      97,  -174,   102,    62,   103,   103,   299,  -174,  -174,  -174,
    -174,  -174,  -174,   104,  -174,   103,  -174,  -174,  -174,  -174,
    -174,    23,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
      54,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,  -174,  -174,  -174,   279,  -174,  -174,
     108,   102,    62,   103,   103,    71,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,   102,    62,   103,  -174,  -174,  -174,  -174,
    -174,  -174,    31,  -174,  -174,   106,  -174,  -174,     9,  -174,
    -174,  -174,  -174,  -174,    59,    89,   109,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,   107,    31,  -174,  -174,  -174,   299,
     299,     9,    45,  -174,  -174,  -174,  -174,  -174,   111,  -174,
    -174,  -174,  -174,   102,    27,  -174,  -174
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -174,  -174,  -113,  -174,   112,  -134,  -174,  -174,  -174,     0,
    -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,    76,  -174,  -174,  -174,  -174,  -174,    69,
       1,  -174,  -174,  -174,  -174,   -22,   -30,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
      64,   -28,  -174,  -174,  -174,     3,    19,  -107,  -174,  -173,
    -119,   -20,  -123,  -174,  -174,  -174,  -174
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, parse error.  */
#define YYTABLE_NINF -59
static const short yytable[] =
{
      13,    16,    38,   192,   188,    22,    23,   200,   209,    74,
      13,    16,    48,    56,    63,    71,   203,   189,   190,    20,
     219,   117,   118,   119,    26,    27,     1,     2,   198,   122,
     123,   124,   125,     4,     1,     2,     4,     4,   128,   129,
     130,     4,     4,     7,   199,   179,    24,     7,     1,     2,
       3,     7,    29,    34,   207,     4,     5,     1,     2,     6,
      35,    36,   231,   210,     4,     7,   202,    39,   222,     4,
     245,    37,    75,   120,     7,   220,   211,   212,     3,     7,
     -58,   126,     5,    57,     5,     6,   131,     6,   221,    58,
      59,   237,    60,     3,    40,    41,    42,    43,    57,     5,
       5,   133,     6,     6,   178,   185,   239,   240,    49,    50,
      51,    52,   186,    57,   196,   208,   226,   243,   235,   242,
     236,   121,    30,   127,     0,     0,     0,     0,     0,   132,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   218,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     223,     0,     0,     0,   233,   213,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   228,     0,     0,   246,   234,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   135,     0,
       0,     0,    13,    16,   241,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   205,     0,     0,     0,     0,     0,
       0,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
       0,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115
};

static const short yycheck[] =
{
       0,     0,    32,   126,   123,     2,     3,   141,   181,    37,
      10,    10,    34,    35,    36,    37,   150,   124,   125,    10,
     193,    41,    42,    43,     5,     6,     3,     4,   135,    49,
      50,    51,    52,    10,     3,     4,    10,    10,    58,    59,
      60,    10,    10,    20,    21,    73,    20,    20,     3,     4,
       5,    20,     0,    12,   177,    10,    11,     3,     4,    14,
      12,     8,     3,   182,    10,    20,    12,     6,   202,    10,
     243,     8,    10,    13,    20,   194,   183,   184,     5,    20,
       9,    13,    11,    10,    11,    14,     9,    14,   195,    16,
      17,   225,    19,     5,    16,    17,    18,    19,    10,    11,
      11,    15,    14,    14,     9,     8,   229,   230,    16,    17,
      18,    19,    10,    10,    10,     7,    10,     6,     9,   232,
      13,    45,    10,    54,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   185,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     202,    -1,    -1,    -1,   214,   185,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   208,    -1,    -1,   244,   215,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,    -1,
      -1,    -1,   232,   232,   231,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      -1,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,     5,    10,    11,    14,    20,   101,   102,
     103,   104,   105,   109,   113,   126,   130,   135,   136,   156,
      10,   155,   155,   155,    20,   112,   156,   156,   138,     0,
     104,   137,   106,   131,    12,    12,     8,     8,   136,     6,
      16,    17,    18,    19,   116,   117,   118,   123,   135,    16,
      17,    18,    19,   127,   128,   129,   135,    10,    16,    17,
      19,   109,   130,   135,   141,   142,   143,   147,   150,   151,
     157,   135,   139,   140,   151,    10,   160,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   161,   161,   161,   161,
      13,   123,   161,   161,   161,   161,    13,   129,   161,   161,
     161,     9,   150,    15,   146,    15,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,   149,   162,   152,     9,   151,
     132,   119,   120,   124,   121,     8,    10,   159,   160,   157,
     157,   134,   162,   144,   145,   148,    10,   158,   157,    21,
     105,   163,    12,   105,   164,    15,   153,   162,     7,   159,
     160,   157,   157,   109,   110,   111,   114,   115,   135,   159,
     160,   157,   105,   135,   165,   166,    10,   154,   155,   125,
     122,     3,   107,   136,   109,     9,    13,   105,   133,   162,
     162,   155,   102,     6,   108,   159,   136
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1

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
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)           \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#define YYLEX	yylex ()

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
} while (0)
# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*-----------------------------.
| Print this symbol on YYOUT.  |
`-----------------------------*/

static void
#if defined (__STDC__) || defined (__cplusplus)
yysymprint (FILE* yyout, int yytype, YYSTYPE yyvalue)
#else
yysymprint (yyout, yytype, yyvalue)
    FILE* yyout;
    int yytype;
    YYSTYPE yyvalue;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvalue;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyout, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyout, yytoknum[yytype], yyvalue);
# endif
    }
  else
    YYFPRINTF (yyout, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyout, ")");
}
#endif /* YYDEBUG. */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
#if defined (__STDC__) || defined (__cplusplus)
yydestruct (int yytype, YYSTYPE yyvalue)
#else
yydestruct (yytype, yyvalue)
    int yytype;
    YYSTYPE yyvalue;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvalue;

  switch (yytype)
    {
      default:
        break;
    }
}



/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of parse errors so far.  */
int yynerrs;


int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

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
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
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

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with.  */

  if (yychar <= 0)		/* This means end of input.  */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more.  */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

      /* We have to keep this `#if YYDEBUG', since we use variables
	 which are defined only if `YYDEBUG' is set.  */
      YYDPRINTF ((stderr, "Next token is "));
      YYDSYMPRINT ((stderr, yychar1, yylval));
      YYDPRINTF ((stderr, "\n"));
    }

  /* If the proper action on seeing token YYCHAR1 is to reduce or to
     detect an error, take that action.  */
  yyn += yychar1;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yychar1)
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

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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



#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn - 1, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] >= 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif
  switch (yyn)
    {
        case 11:
#line 212 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, OSGScanParseSkel_text); }
    break;

  case 13:
#line 215 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(_pSkel != NULL)
                                  _pSkel->use(OSGScanParseSkel_text); }
    break;

  case 15:
#line 221 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, OSGScanParseSkel_text); }
    break;

  case 23:
#line 238 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(_pSkel != NULL) 
                        _pSkel->beginProto(OSGScanParseSkel_text); }
    break;

  case 24:
#line 240 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(_pSkel != NULL) 
                        _pSkel->beginProto(OSGScanParseSkel_text); }
    break;

  case 25:
#line 251 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(_pSkel != NULL) 
			_pSkel->endProto(); }
    break;

  case 33:
#line 272 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                      OSGScanParseSkel_text); }
    break;

  case 34:
#line 274 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(_pSkel != NULL)
                                               _pSkel->addEventInDecl(
                                                szName1,
                                                OSGScanParseSkel_text); 
                                              freeName(szName1); }
    break;

  case 35:
#line 280 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                      OSGScanParseSkel_text); }
    break;

  case 36:
#line 282 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(_pSkel != NULL)
                                               _pSkel->addEventOutDecl(
                                                szName1,
                                                OSGScanParseSkel_text); 
                                              freeName(szName1); }
    break;

  case 37:
#line 288 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                      OSGScanParseSkel_text); }
    break;

  case 38:
#line 290 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { expectType(nextType); 
                                              if(_pSkel != NULL)
                                               _pSkel->beginFieldDecl(
                                                szName1,
                                                nextType,
                                                OSGScanParseSkel_text); 
                                              freeName(szName1); }
    break;

  case 39:
#line 297 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = 0; 
                                              if(_pSkel != NULL)
                                               _pSkel->endFieldDecl();
                                             }
    break;

  case 41:
#line 305 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                              OSGScanParseSkel_text); }
    break;

  case 42:
#line 307 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { expectType(nextType);  
                                      if(_pSkel != NULL)
                                       _pSkel->beginExposedFieldDecl(
                                        szName1,
                                        nextType,
                                        OSGScanParseSkel_text); 
                                       freeName(szName1); }
    break;

  case 43:
#line 314 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = 0; 
                                      if(_pSkel != NULL)
                                       _pSkel->endExposedFieldDecl(); }
    break;

  case 53:
#line 343 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, OSGScanParseSkel_text); }
    break;

  case 54:
#line 345 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName2, OSGScanParseSkel_text); }
    break;

  case 55:
#line 347 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName3, OSGScanParseSkel_text); }
    break;

  case 56:
#line 349 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(_pSkel != NULL)
                                _pSkel->addRoute(szName1, 
                                                 szName2,
                                                 szName3,
                                                 OSGScanParseSkel_text);
                              freeName(szName1);
                              freeName(szName2);
                              freeName(szName3);
                            }
    break;

  case 59:
#line 366 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(_pSkel != NULL)
                     _pSkel->beginNode(OSGScanParseSkel_text, szName1); 

                    freeName(szName1);
                  }
    break;

  case 60:
#line 373 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(_pSkel != NULL)
                     _pSkel->endNode(); }
    break;

  case 61:
#line 375 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(_pSkel != NULL)
                     _pSkel->beginNode(OSGScanParseSkel_text, szName1); 

                    freeName(szName1);
                  }
    break;

  case 62:
#line 382 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(_pSkel != NULL)
                     _pSkel->endNode(); }
    break;

  case 71:
#line 403 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                     OSGScanParseSkel_text); }
    break;

  case 72:
#line 405 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(_pSkel != NULL)
                                                     _pSkel->addEventInDecl(
                                                       szName1,
                                                       OSGScanParseSkel_text); 

                                                 freeName(szName1); }
    break;

  case 73:
#line 412 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                      OSGScanParseSkel_text); }
    break;

  case 74:
#line 414 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(_pSkel != NULL)
                                                     _pSkel->addEventOutDecl(
                                                       szName1,
                                                       OSGScanParseSkel_text); 

                                                  freeName(szName1); }
    break;

  case 77:
#line 427 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                        OSGScanParseSkel_text);
                                               }
    break;

  case 78:
#line 430 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { expectType(nextType); 
                                              
                                                 if(_pSkel != NULL)
                                                     _pSkel->beginFieldDecl(
                                                       szName1,
                                                       nextType,
                                                       OSGScanParseSkel_text); 
                                              
                                                 freeName(szName1);
                                               }
    break;

  case 79:
#line 442 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = 0; 

                                                     if(_pSkel != NULL)
                                                     {
                                                       _pSkel->is(
                                                        OSGScanParseSkel_text);

                                                       _pSkel->endFieldDecl();
                                                     }
                                                   }
    break;

  case 80:
#line 452 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = 0; 

                                                     if(_pSkel != NULL)
                                                       _pSkel->endFieldDecl();

                                                   }
    break;

  case 84:
#line 478 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(_pSkel != NULL)
                    {
                     Int32 iFieldTypeId;

                     iFieldTypeId = _pSkel->getFieldType(
                                        OSGScanParseSkel_text);

                     if(_pSkel->getMapFieldTypes() == true)
                     {
                      iFieldTypeId = _pSkel->mapExtIntFieldType(    
                                        OSGScanParseSkel_text,
                                        iFieldTypeId);
                     }
    
                     expectType(iFieldTypeId); 

                     _pSkel->beginField(OSGScanParseSkel_text, 
                                        iFieldTypeId);
                                        
                    } 
                   }
    break;

  case 88:
#line 506 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(_pSkel != NULL)
                          {
                            _pSkel->is(OSGScanParseSkel_text);
                            _pSkel->endField();
                          }
                        }
    break;

  case 89:
#line 512 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(_pSkel != NULL)
                            _pSkel->endField();
                        }
    break;

  case 97:
#line 539 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFCOLOR;    }
    break;

  case 98:
#line 540 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFFLOAT;    }
    break;

  case 99:
#line 541 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFINT32;    }
    break;

  case 100:
#line 542 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFNODE;     }
    break;

  case 101:
#line 543 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFROTATION; }
    break;

  case 102:
#line 544 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFSTRING;   }
    break;

  case 103:
#line 545 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFTIME;     }
    break;

  case 104:
#line 546 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFVEC2F;    }
    break;

  case 105:
#line 547 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFVEC3F;    }
    break;

  case 106:
#line 548 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFBOOL;     }
    break;

  case 107:
#line 549 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFCOLOR;    }
    break;

  case 108:
#line 550 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFFLOAT;    }
    break;

  case 109:
#line 551 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFIMAGE;    }
    break;

  case 110:
#line 552 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFINT32;    }
    break;

  case 111:
#line 553 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFNODE;     }
    break;

  case 112:
#line 554 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFROTATION; }
    break;

  case 113:
#line 555 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFSTRING;   }
    break;

  case 114:
#line 556 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFTIME;     }
    break;

  case 115:
#line 557 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFVEC2F;    }
    break;

  case 116:
#line 558 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFVEC3F;    }
    break;

  case 117:
#line 559 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFCOLOR4F;  }
    break;

  case 118:
#line 560 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFCOLOR4I;  }
    break;

  case 119:
#line 561 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFCOLOR3F;  }
    break;

  case 120:
#line 562 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFMATRIX;   }
    break;

  case 121:
#line 563 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFPNT2F;    }
    break;

  case 122:
#line 564 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFPNT3F;    }
    break;

  case 123:
#line 565 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFPNT4F;    }
    break;

  case 124:
#line 566 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFVEC4F;    }
    break;

  case 125:
#line 567 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFPLANE;    }
    break;

  case 126:
#line 568 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFCOLOR4F;  }
    break;

  case 127:
#line 569 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFCOLOR4I;  }
    break;

  case 128:
#line 570 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFCOLOR3F;  }
    break;

  case 129:
#line 571 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFMATRIX;   }
    break;

  case 130:
#line 572 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFPNT2F;    }
    break;

  case 131:
#line 573 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFPNT3F;    }
    break;

  case 132:
#line 574 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFPNT4F;    }
    break;

  case 133:
#line 575 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFVEC4F;    }
    break;

  case 134:
#line 576 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFPLANE;    }
    break;

  case 135:
#line 577 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFVOLUME;   }
    break;


    }

/* Line 1016 of /usr/share/bison/yacc.c.  */
#line 1971 "OSGScanParseSkel_.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

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
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[yytype]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyssp > yyss)
	    {
	      YYDPRINTF ((stderr, "Error: popping "));
	      YYDSYMPRINT ((stderr,
			    yystos[*yyssp],
			    *yyvsp));
	      YYDPRINTF ((stderr, "\n"));
	      yydestruct (yystos[*yyssp], *yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yydestruct (yychar1, yylval);
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

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

      YYDPRINTF ((stderr, "Error: popping "));
      YYDSYMPRINT ((stderr,
		    yystos[*yyssp], *yyvsp));
      YYDPRINTF ((stderr, "\n"));

      yydestruct (yystos[yystate], *yyvsp);
      yyvsp--;
      yystate = *--yyssp;


#if YYDEBUG
      if (yydebug)
	{
	  short *yyssp1 = yyss - 1;
	  YYFPRINTF (stderr, "Error: state stack now");
	  while (yyssp1 != yyssp)
	    YYFPRINTF (stderr, " %d", *++yyssp1);
	  YYFPRINTF (stderr, "\n");
	}
#endif
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


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
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 640 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"


void OSGScanParseSkel_error (char *s)  /* Called by fhs_parse on error */
{
  printf ("-----> %s in Line %d, read %s\n", s, iLineNum, 
          OSGScanParseSkel_text);
}

void setSkel(ScanParseSkel *pSkel)
{
    _pSkel = pSkel;
}

void clearSkel(void)
{
    _pSkel = NULL;
}

void setName (char *&szName, const char *szVal)
{
    stringDup(szVal, szName);
}

void freeName(char *&szName)
{
    delete [] szName;
    
    szName = NULL;
}



