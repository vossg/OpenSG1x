/* A Bison parser, made by GNU Bison 1.875b.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

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
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

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
     EXPORT = 271,
     IMPORT = 272,
     PROFILE = 273,
     COMPONENT = 274,
     OSG_META = 275,
     AS = 276,
     EVENTIN = 277,
     EVENTOUT = 278,
     EXPOSEDFIELD = 279,
     FIELD = 280,
     SCRIPT = 281,
     SFN_NULL = 282,
     TOK_SFBOOL = 283,
     TOK_SFCOLOR = 284,
     TOK_SFFLOAT = 285,
     TOK_SFIMAGE = 286,
     TOK_SFINT32 = 287,
     TOK_SFNODE = 288,
     TOK_SFROTATION = 289,
     TOK_SFSTRING = 290,
     TOK_SFTIME = 291,
     TOK_SFVEC2F = 292,
     TOK_SFVEC3F = 293,
     TOK_MFCOLOR = 294,
     TOK_MFFLOAT = 295,
     TOK_MFINT32 = 296,
     TOK_MFNODE = 297,
     TOK_MFROTATION = 298,
     TOK_MFSTRING = 299,
     TOK_MFTIME = 300,
     TOK_MFVEC2F = 301,
     TOK_MFVEC3F = 302,
     Tok_MFColor = 303,
     Tok_MFFloat = 304,
     Tok_MFInt32 = 305,
     Tok_MFNode = 306,
     Tok_MFRotation = 307,
     Tok_MFString = 308,
     Tok_MFTime = 309,
     Tok_MFVec2f = 310,
     Tok_MFVec3f = 311,
     Tok_SFBool = 312,
     Tok_SFColor = 313,
     Tok_SFFloat = 314,
     Tok_SFImage = 315,
     Tok_SFInt32 = 316,
     Tok_SFNode = 317,
     Tok_SFRotation = 318,
     Tok_SFString = 319,
     Tok_SFTime = 320,
     Tok_SFVec2f = 321,
     Tok_SFVec3f = 322,
     TOK_MFCOLOR4F = 323,
     TOK_MFCOLOR4I = 324,
     TOK_MFCOLOR3F = 325,
     TOK_MFMATRIX = 326,
     TOK_MFPNT2F = 327,
     TOK_MFPNT3F = 328,
     TOK_MFPNT4F = 329,
     TOK_MFVEC4F = 330,
     TOK_MFPLANE = 331,
     TOK_SFCOLOR4F = 332,
     TOK_SFCOLOR4I = 333,
     TOK_SFCOLOR3F = 334,
     TOK_SFMATRIX = 335,
     TOK_SFPNT2F = 336,
     TOK_SFPNT3F = 337,
     TOK_SFPNT4F = 338,
     TOK_SFVEC4F = 339,
     TOK_SFPLANE = 340,
     TOK_SFVOLUME = 341,
     Tok_MFColor4f = 342,
     Tok_MFColor4i = 343,
     Tok_MFColor3f = 344,
     Tok_MFMatrix = 345,
     Tok_MFPnt2f = 346,
     Tok_MFPnt3f = 347,
     Tok_MFPnt4f = 348,
     Tok_MFVec4f = 349,
     Tok_MFPlane = 350,
     Tok_SFColor4f = 351,
     Tok_SFColor4i = 352,
     Tok_SFColor3f = 353,
     Tok_SFMatrix = 354,
     Tok_SFPnt2f = 355,
     Tok_SFPnt3f = 356,
     Tok_SFPnt4f = 357,
     Tok_SFVec4f = 358,
     Tok_SFPlane = 359,
     Tok_SFVolume = 360
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
#define EXPORT 271
#define IMPORT 272
#define PROFILE 273
#define COMPONENT 274
#define OSG_META 275
#define AS 276
#define EVENTIN 277
#define EVENTOUT 278
#define EXPOSEDFIELD 279
#define FIELD 280
#define SCRIPT 281
#define SFN_NULL 282
#define TOK_SFBOOL 283
#define TOK_SFCOLOR 284
#define TOK_SFFLOAT 285
#define TOK_SFIMAGE 286
#define TOK_SFINT32 287
#define TOK_SFNODE 288
#define TOK_SFROTATION 289
#define TOK_SFSTRING 290
#define TOK_SFTIME 291
#define TOK_SFVEC2F 292
#define TOK_SFVEC3F 293
#define TOK_MFCOLOR 294
#define TOK_MFFLOAT 295
#define TOK_MFINT32 296
#define TOK_MFNODE 297
#define TOK_MFROTATION 298
#define TOK_MFSTRING 299
#define TOK_MFTIME 300
#define TOK_MFVEC2F 301
#define TOK_MFVEC3F 302
#define Tok_MFColor 303
#define Tok_MFFloat 304
#define Tok_MFInt32 305
#define Tok_MFNode 306
#define Tok_MFRotation 307
#define Tok_MFString 308
#define Tok_MFTime 309
#define Tok_MFVec2f 310
#define Tok_MFVec3f 311
#define Tok_SFBool 312
#define Tok_SFColor 313
#define Tok_SFFloat 314
#define Tok_SFImage 315
#define Tok_SFInt32 316
#define Tok_SFNode 317
#define Tok_SFRotation 318
#define Tok_SFString 319
#define Tok_SFTime 320
#define Tok_SFVec2f 321
#define Tok_SFVec3f 322
#define TOK_MFCOLOR4F 323
#define TOK_MFCOLOR4I 324
#define TOK_MFCOLOR3F 325
#define TOK_MFMATRIX 326
#define TOK_MFPNT2F 327
#define TOK_MFPNT3F 328
#define TOK_MFPNT4F 329
#define TOK_MFVEC4F 330
#define TOK_MFPLANE 331
#define TOK_SFCOLOR4F 332
#define TOK_SFCOLOR4I 333
#define TOK_SFCOLOR3F 334
#define TOK_SFMATRIX 335
#define TOK_SFPNT2F 336
#define TOK_SFPNT3F 337
#define TOK_SFPNT4F 338
#define TOK_SFVEC4F 339
#define TOK_SFPLANE 340
#define TOK_SFVOLUME 341
#define Tok_MFColor4f 342
#define Tok_MFColor4i 343
#define Tok_MFColor3f 344
#define Tok_MFMatrix 345
#define Tok_MFPnt2f 346
#define Tok_MFPnt3f 347
#define Tok_MFPnt4f 348
#define Tok_MFVec4f 349
#define Tok_MFPlane 350
#define Tok_SFColor4f 351
#define Tok_SFColor4i 352
#define Tok_SFColor3f 353
#define Tok_SFMatrix 354
#define Tok_SFPnt2f 355
#define Tok_SFPnt3f 356
#define Tok_SFPnt4f 357
#define Tok_SFVec4f 358
#define Tok_SFPlane 359
#define Tok_SFVolume 360




/* Copy the first part of user declarations.  */
#line 38 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"


#define YYPARSE_PARAM pSkel
#define YYLEX_PARAM   pSkel

#define YYLTYPE_IS_TRIVIAL 1
#define YYSTYPE_IS_TRIVIAL 1

#define OSGScanParseSkel_error SKEL->handleError

#ifdef WIN32
#include <malloc.h>
#define YYSIZE_T size_t
#endif
#include <OSGScanParseSkel.tab.h>
#include <OSGConfig.h>
#include <OSGLog.h>

#include <OSGBaseFunctions.h>
#include <OSGScanParseSkel.h>
#include <stack>

#if defined(OSG_LINUX_ICC) || defined(OSG_WIN32_ICL)
#pragma warning( disable : 193 810 177 )
#endif

OSG_USING_NAMESPACE

int OSGScanParseSkel_lex(YYSTYPE *lvalp, void *);

int nextType;

char *szName1    = NULL;
char *szName2    = NULL;
char *szName3    = NULL;

void setName (char *&szName, const char *szVal);
void freeName(char *&szName);

#define SKEL ((ScanParseSkel *) pSkel)
#define SKELTEXT (SKEL->getText())



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

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 350 "OSGScanParseSkel_.tab.c"

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
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

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
	    (To)[yyi] = (From)[yyi];		\
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
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
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
#define YYFINAL  48
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   556

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  106
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  89
/* YYNRULES -- Number of rules. */
#define YYNRULES  214
/* YYNRULES -- Number of states. */
#define YYNSTATES  299

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   360

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     5,     6,    11,    13,    16,    18,    21,
      23,    26,    29,    31,    34,    36,    37,    42,    44,    46,
      49,    51,    53,    55,    57,    59,    61,    63,    64,    69,
      72,    74,    75,    80,    82,    84,    86,    87,    90,    92,
      94,    96,   105,   107,   109,   113,   115,   117,   120,   122,
     123,   128,   129,   134,   135,   136,   143,   145,   146,   147,
     154,   155,   156,   165,   167,   169,   172,   174,   175,   180,
     181,   186,   187,   192,   193,   198,   199,   200,   201,   213,
     214,   219,   220,   221,   229,   232,   234,   236,   237,   238,
     244,   245,   251,   253,   255,   258,   260,   261,   266,   267,
     272,   275,   276,   277,   282,   285,   287,   288,   293,   296,
     298,   300,   303,   306,   309,   310,   314,   316,   318,   321,
     323,   325,   327,   329,   331,   333,   335,   337,   339,   341,
     343,   345,   347,   349,   351,   353,   355,   357,   359,   361,
     363,   365,   367,   369,   371,   373,   375,   377,   379,   381,
     383,   385,   387,   389,   391,   393,   395,   397,   399,   401,
     403,   405,   407,   409,   411,   413,   415,   417,   419,   421,
     423,   425,   428,   430,   432,   434,   436,   438,   440,   442,
     444,   447,   449,   451,   453,   455,   457,   459,   461,   463,
     465,   467,   469,   471,   473,   475,   477,   479,   481,   483,
     485,   487,   489,   491,   493,   495,   497,   500,   502,   504,
     507,   511,   513,   515,   518
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short yyrhs[] =
{
     107,     0,    -1,   108,    -1,    -1,    18,    10,   109,   110,
      -1,   110,    -1,   111,   113,    -1,   113,    -1,   111,   112,
      -1,   112,    -1,    19,    10,    -1,   114,   117,    -1,   117,
      -1,   114,   115,    -1,   115,    -1,    -1,    20,    10,   116,
      10,    -1,   118,    -1,   162,    -1,   118,   119,    -1,   119,
      -1,   120,    -1,   124,    -1,   151,    -1,   157,    -1,   155,
      -1,   163,    -1,    -1,     3,   183,   121,   163,    -1,     4,
     183,    -1,   163,    -1,    -1,     3,   183,   123,   163,    -1,
     128,    -1,   141,    -1,   126,    -1,    -1,   126,   124,    -1,
     124,    -1,   184,    -1,    26,    -1,    11,   127,    12,   131,
      13,     8,   129,     9,    -1,   130,    -1,   162,    -1,   125,
     122,   117,    -1,   132,    -1,   162,    -1,   132,   138,    -1,
     138,    -1,    -1,    22,   189,   134,   187,    -1,    -1,    23,
     189,   135,   188,    -1,    -1,    -1,    25,   189,   136,   185,
     137,   190,    -1,   133,    -1,    -1,    -1,    24,   189,   139,
     185,   140,   190,    -1,    -1,    -1,    14,   184,   142,    12,
     144,    13,   143,   161,    -1,   145,    -1,   162,    -1,   145,
     146,    -1,   146,    -1,    -1,    22,   189,   147,   187,    -1,
      -1,    23,   189,   148,   188,    -1,    -1,    25,   189,   149,
     185,    -1,    -1,    24,   189,   150,   185,    -1,    -1,    -1,
      -1,     5,   183,   152,     6,   188,   153,     7,   183,   154,
       6,   187,    -1,    -1,    16,    10,   156,   160,    -1,    -1,
      -1,    17,    10,   158,     6,    10,   159,   160,    -1,    21,
      10,    -1,   162,    -1,   190,    -1,    -1,    -1,   184,   164,
       8,   166,     9,    -1,    -1,    26,   165,     8,   166,     9,
      -1,   167,    -1,   162,    -1,   167,   178,    -1,   178,    -1,
      -1,    22,   189,   169,   187,    -1,    -1,    23,   189,   170,
     188,    -1,    15,   186,    -1,    -1,    -1,    25,   189,   173,
     185,    -1,    15,   185,    -1,   190,    -1,    -1,    24,   189,
     176,   185,    -1,    15,   185,    -1,   190,    -1,   179,    -1,
     168,   171,    -1,   172,   174,    -1,   175,   177,    -1,    -1,
     185,   180,   181,    -1,   151,    -1,   124,    -1,    15,   182,
      -1,   190,    -1,    10,    -1,    10,    -1,    10,    -1,    10,
      -1,    10,    -1,    10,    -1,    10,    -1,    48,    -1,    49,
      -1,    50,    -1,    51,    -1,    52,    -1,    53,    -1,    54,
      -1,    55,    -1,    56,    -1,    57,    -1,    58,    -1,    59,
      -1,    60,    -1,    61,    -1,    62,    -1,    63,    -1,    64,
      -1,    65,    -1,    66,    -1,    67,    -1,    87,    -1,    88,
      -1,    89,    -1,    90,    -1,    91,    -1,    92,    -1,    93,
      -1,    94,    -1,    95,    -1,    96,    -1,    97,    -1,    98,
      -1,    99,    -1,   100,    -1,   101,    -1,   102,    -1,   103,
      -1,   104,    -1,   105,    -1,    28,    -1,    29,    -1,    30,
      -1,    31,    -1,    32,    -1,    33,   191,    -1,    34,    -1,
      35,    -1,    36,    -1,    37,    -1,    38,    -1,    39,    -1,
      40,    -1,    41,    -1,    42,   192,    -1,    43,    -1,    44,
      -1,    45,    -1,    46,    -1,    47,    -1,    68,    -1,    69,
      -1,    70,    -1,    71,    -1,    72,    -1,    73,    -1,    74,
      -1,    76,    -1,    75,    -1,    77,    -1,    78,    -1,    79,
      -1,    80,    -1,    81,    -1,    82,    -1,    83,    -1,    85,
      -1,    86,    -1,    84,    -1,   120,    -1,    15,   182,    -1,
      27,    -1,   120,    -1,    15,   182,    -1,    12,   193,    13,
      -1,   194,    -1,   162,    -1,   194,   120,    -1,   120,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   202,   202,   207,   205,   214,   218,   219,   222,   223,
     226,   236,   237,   240,   241,   245,   244,   256,   257,   260,
     261,   264,   265,   266,   267,   268,   271,   273,   272,   275,
     280,   282,   281,   286,   287,   291,   292,   295,   296,   299,
     301,   305,   316,   317,   320,   323,   324,   327,   328,   333,
     332,   346,   345,   359,   361,   358,   374,   376,   378,   375,
     391,   396,   390,   409,   410,   414,   415,   419,   418,   428,
     427,   437,   436,   446,   445,   457,   459,   461,   456,   476,
     474,   493,   498,   491,   514,   518,   521,   524,   527,   527,
     539,   539,   560,   561,   564,   565,   569,   568,   579,   578,
     590,   599,   608,   607,   623,   632,   641,   640,   657,   667,
     684,   685,   687,   689,   695,   694,   716,   717,   722,   728,
     735,   738,   741,   744,   747,   750,   753,   756,   757,   758,
     759,   760,   761,   762,   763,   764,   765,   766,   767,   768,
     769,   770,   771,   772,   773,   774,   775,   776,   777,   778,
     779,   780,   781,   782,   783,   784,   785,   786,   787,   788,
     789,   790,   791,   792,   793,   794,   798,   799,   800,   801,
     802,   803,   804,   805,   806,   807,   808,   809,   810,   811,
     812,   813,   814,   815,   816,   817,   818,   819,   820,   821,
     822,   823,   824,   825,   826,   827,   828,   829,   830,   831,
     832,   833,   834,   835,   836,   840,   841,   848,   851,   852,
     859,   862,   863,   866,   867
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DEF", "USE", "ROUTE", "PERIOD", "TO", 
  "OPENBRACE", "CLOSEBRACE", "ID", "PROTO", "OPENBRACKET", "CLOSEBRACKET", 
  "EXTERNPROTO", "IS", "EXPORT", "IMPORT", "PROFILE", "COMPONENT", 
  "OSG_META", "AS", "EVENTIN", "EVENTOUT", "EXPOSEDFIELD", "FIELD", 
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
  "profileStatement", "@1", "componentStatements", 
  "componentStatementsRec", "componentStatement", "metaStatements", 
  "metaStatementsRec", "metaStatement", "@2", "statementsORempty", 
  "statements", "statement", "nodeStatement", "@3", "rootNodeStatement", 
  "@4", "protoStatement", "protoStatementsORempty", "protoStatements", 
  "protoId", "proto", "protoBodyORempty", "protoBody", 
  "interfaceDeclarationsORempty", "interfaceDeclarations", 
  "restrictedInterfaceDeclaration", "@5", "@6", "@7", "@8", 
  "interfaceDeclaration", "@9", "@10", "externproto", "@11", "@12", 
  "externInterfaceDeclarationsORempty", "externInterfaceDeclarations", 
  "externInterfaceDeclaration", "@13", "@14", "@15", "@16", 
  "routeStatement", "@17", "@18", "@19", "exportStatement", "@20", 
  "importStatement", "@21", "@22", "importExportEnd", "URLList", "empty", 
  "node", "@23", "@24", "scriptBodyORempty", "scriptBody", 
  "resInterfaceDeclarationScriptEvent", "@25", "@26", 
  "resInterfaceDeclarationScriptEventEnd", 
  "resInterfaceDeclarationScriptField", "@27", 
  "resInterafceDeclarationScriptFieldEnd", 
  "resInterfaceDeclarationScriptExpField", "@28", 
  "resInterafceDeclarationScriptExpFieldEnd", "scriptBodyElement", 
  "nodeBodyElement", "@29", "fieldEnd", "generalId", "nodeNameId", 
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
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,   106,   107,   109,   108,   108,   110,   110,   111,   111,
     112,   113,   113,   114,   114,   116,   115,   117,   117,   118,
     118,   119,   119,   119,   119,   119,   120,   121,   120,   120,
     122,   123,   122,   124,   124,   125,   125,   126,   126,   127,
     127,   128,   129,   129,   130,   131,   131,   132,   132,   134,
     133,   135,   133,   136,   137,   133,   138,   139,   140,   138,
     142,   143,   141,   144,   144,   145,   145,   147,   146,   148,
     146,   149,   146,   150,   146,   152,   153,   154,   151,   156,
     155,   158,   159,   157,   160,   160,   161,   162,   164,   163,
     165,   163,   166,   166,   167,   167,   169,   168,   170,   168,
     171,   171,   173,   172,   174,   174,   176,   175,   177,   177,
     178,   178,   178,   178,   180,   179,   179,   179,   181,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   190,   190,   190,   190,
     190,   190,   190,   190,   190,   190,   190,   190,   190,   190,
     190,   190,   190,   190,   190,   190,   190,   190,   190,   190,
     190,   190,   190,   190,   190,   190,   190,   190,   190,   190,
     190,   190,   190,   190,   190,   191,   191,   191,   192,   192,
     192,   193,   193,   194,   194
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     0,     4,     1,     2,     1,     2,     1,
       2,     2,     1,     2,     1,     0,     4,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     2,
       1,     0,     4,     1,     1,     1,     0,     2,     1,     1,
       1,     8,     1,     1,     3,     1,     1,     2,     1,     0,
       4,     0,     4,     0,     0,     6,     1,     0,     0,     6,
       0,     0,     8,     1,     1,     2,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     0,     0,    11,     0,
       4,     0,     0,     7,     2,     1,     1,     0,     0,     5,
       0,     5,     1,     1,     2,     1,     0,     4,     0,     4,
       2,     0,     0,     4,     2,     1,     0,     4,     2,     1,
       1,     2,     2,     2,     0,     3,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     2,
       3,     1,     1,     2,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
      87,     0,     0,     0,   122,     0,     0,     0,     0,     0,
       0,     0,    90,     0,     2,     5,    87,     9,     7,    87,
      14,    12,    17,    20,    21,    22,    33,    34,    23,    25,
      24,    18,    26,    88,   121,    27,    29,    75,    40,     0,
      39,    60,    79,    81,     3,    10,    15,     0,     1,     8,
       6,    13,    11,    19,     0,     0,     0,    87,     0,    87,
       0,    87,     0,    87,    87,    28,     0,     0,     0,     0,
       0,     0,    45,    56,    48,    46,    87,     0,    80,    85,
       0,     4,    16,   123,     0,     0,     0,     0,   117,   116,
      93,     0,    92,   101,     0,     0,    95,   110,   114,     0,
     126,    76,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,    49,    51,    57,    53,     0,    47,     0,     0,     0,
       0,     0,    63,    66,    64,    84,    82,    96,    98,   106,
     102,    91,    94,     0,   111,     0,   166,   167,   168,   169,
     170,     0,   172,   173,   174,   175,   176,   177,   178,   179,
       0,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   194,   193,   195,   196,   197,   198,   199,
     200,   201,   204,   202,   203,   112,   105,     0,   113,   109,
       0,    89,     0,     0,     0,     0,     0,    36,    67,    69,
      73,    71,    61,    65,    87,     0,     0,     0,     0,   124,
     100,   104,     0,   207,   205,   171,    87,     0,   208,   180,
     108,     0,   115,   119,     0,   125,    50,    52,    58,    54,
      38,     0,    35,     0,    42,    43,     0,     0,     0,     0,
       0,    83,    97,    99,   107,   103,   120,   206,   214,   212,
       0,   211,   209,   118,    77,     0,     0,     0,    87,    30,
      37,    41,    68,    70,    74,    72,    62,    86,   210,   213,
       0,    59,    55,    31,    44,     0,     0,    78,    32
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,    13,    14,    61,    15,    16,    17,    18,    19,    20,
      62,    21,    22,    23,    24,    55,   278,   296,    25,   251,
     252,    39,    26,   253,   254,    71,    72,    73,   213,   214,
     216,   276,    74,   215,   275,    27,    58,   260,   151,   152,
     153,   256,   257,   259,   258,    28,    56,   212,   290,    29,
      59,    30,    60,   224,    78,   286,    31,    32,    54,    47,
      91,    92,    93,   225,   226,   164,    94,   228,   205,    95,
     227,   208,    96,    97,   210,   242,   267,    35,    33,    98,
     230,   246,   101,   141,   206,   235,   239,   270,   271
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -214
static const short yypact[] =
{
      61,     3,     3,     3,  -214,     8,    16,    17,    22,    53,
      64,    66,  -214,    86,  -214,  -214,   106,  -214,  -214,   124,
    -214,  -214,    80,  -214,  -214,  -214,  -214,  -214,  -214,  -214,
    -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,    76,
    -214,  -214,  -214,  -214,  -214,  -214,  -214,    81,  -214,  -214,
    -214,  -214,  -214,  -214,    91,    21,   101,    37,   107,    71,
     112,   106,   114,   138,   138,  -214,   123,   451,   451,   451,
     451,   132,    37,  -214,  -214,  -214,    90,   126,  -214,  -214,
     136,  -214,  -214,  -214,   451,   451,   451,   451,  -214,  -214,
    -214,   142,   138,   139,   248,   320,  -214,  -214,  -214,   146,
    -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,
    -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,
    -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,
    -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,
    -214,  -214,  -214,  -214,  -214,   148,  -214,   451,   451,   451,
     451,   134,    90,  -214,  -214,  -214,  -214,  -214,  -214,  -214,
    -214,  -214,  -214,   147,  -214,   149,  -214,  -214,  -214,  -214,
    -214,    41,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,
     127,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,
    -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,
    -214,  -214,  -214,  -214,  -214,  -214,  -214,   149,  -214,  -214,
     392,  -214,   157,   155,   123,   149,   149,    84,  -214,  -214,
    -214,  -214,  -214,  -214,    71,   155,   123,   149,   149,  -214,
    -214,  -214,   156,  -214,  -214,  -214,    26,   156,  -214,  -214,
    -214,   156,  -214,  -214,     3,  -214,  -214,  -214,  -214,  -214,
    -214,    11,    24,   158,  -214,  -214,   155,   123,   149,   149,
     412,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,
     159,    26,  -214,  -214,  -214,   412,   412,     3,    80,  -214,
    -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,
     162,  -214,  -214,  -214,  -214,   155,    21,  -214,  -214
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -214,  -214,  -214,  -214,   109,  -214,   161,   163,  -214,   154,
    -214,   -17,  -214,   152,  -163,  -214,  -214,  -214,   -59,  -214,
    -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,
    -214,  -214,   103,  -214,  -214,  -214,  -214,  -214,  -214,  -214,
      28,  -214,  -214,  -214,  -214,   -44,  -214,  -214,  -214,  -214,
    -214,  -214,  -214,  -214,   -46,  -214,   -48,   -52,  -214,  -214,
     117,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,
    -214,  -214,    92,  -214,  -214,  -214,  -191,    -2,    49,  -158,
    -214,  -213,  -204,   -45,   -89,  -214,  -214,  -214,  -214
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -88
static const short yytable[] =
{
      36,    37,    52,    65,    88,    88,   209,   231,   234,    75,
     247,    79,   262,    34,   277,    90,    90,   238,     4,    89,
      89,     4,   263,   142,   143,   144,     4,    42,   154,     1,
       2,     4,    43,    88,    38,     5,     4,    12,     6,   157,
     158,   159,   160,   282,     1,     2,   272,    12,    89,   240,
     273,     4,    12,   283,    40,    41,   232,   248,   249,    67,
      68,    69,    70,    44,     1,     2,     3,    12,   233,   264,
     265,     4,     5,   268,    45,     6,    46,     7,     8,     9,
      10,    11,   297,     1,     2,     3,    48,    12,    57,    63,
       4,     5,    77,   -87,     6,     5,     7,     8,     6,    64,
     284,   285,   218,   219,   220,   221,    12,    66,   289,     1,
       2,     3,   147,   148,   149,   150,     4,     5,    80,    76,
       6,   243,     7,     8,    82,    10,    11,     1,     2,     3,
       1,     2,    12,   100,     4,     5,   155,     4,     6,   236,
       7,     8,   237,     3,    11,   145,   156,   222,    83,     5,
      12,   161,     6,    12,   163,   211,   217,   229,   250,    83,
      84,    85,    86,    87,   244,   245,   266,   281,   295,   255,
      81,   287,   288,    51,    53,   146,    79,    49,   261,    50,
     223,    99,     0,     0,   162,     0,   291,   292,   269,     0,
       0,     0,     0,   280,     0,     0,     0,     0,     0,   279,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   274,     0,   298,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   294,     0,   165,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   293,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   207,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   241,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,     0,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140
};

static const short yycheck[] =
{
       2,     3,    19,    55,    63,    64,    95,   165,   171,    57,
     214,    59,   225,    10,     3,    63,    64,   180,    10,    63,
      64,    10,   226,    68,    69,    70,    10,    10,    76,     3,
       4,    10,    10,    92,    26,    11,    10,    26,    14,    84,
      85,    86,    87,   256,     3,     4,   237,    26,    92,   207,
     241,    10,    26,   257,     5,     6,    15,   215,   216,    22,
      23,    24,    25,    10,     3,     4,     5,    26,    27,   227,
     228,    10,    11,   236,    10,    14,    10,    16,    17,    18,
      19,    20,   295,     3,     4,     5,     0,    26,    12,     8,
      10,    11,    21,     9,    14,    11,    16,    17,    14,     8,
     258,   259,   147,   148,   149,   150,    26,     6,   271,     3,
       4,     5,    22,    23,    24,    25,    10,    11,     6,    12,
      14,   210,    16,    17,    10,    19,    20,     3,     4,     5,
       3,     4,    26,    10,    10,    11,    10,    10,    14,    12,
      16,    17,    15,     5,    20,    13,    10,    13,    10,    11,
      26,     9,    14,    26,    15,     9,     8,    10,   217,    10,
      22,    23,    24,    25,     7,    10,    10,     9,     6,   217,
      61,   260,    13,    19,    22,    72,   224,    16,   224,    16,
     152,    64,    -1,    -1,    92,    -1,   275,   276,   236,    -1,
      -1,    -1,    -1,   252,    -1,    -1,    -1,    -1,    -1,   251,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   244,    -1,   296,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   278,    -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   277,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    -1,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,     5,    10,    11,    14,    16,    17,    18,
      19,    20,    26,   107,   108,   110,   111,   112,   113,   114,
     115,   117,   118,   119,   120,   124,   128,   141,   151,   155,
     157,   162,   163,   184,    10,   183,   183,   183,    26,   127,
     184,   184,    10,    10,    10,    10,    10,   165,     0,   112,
     113,   115,   117,   119,   164,   121,   152,    12,   142,   156,
     158,   109,   116,     8,     8,   163,     6,    22,    23,    24,
      25,   131,   132,   133,   138,   162,    12,    21,   160,   162,
       6,   110,    10,    10,    22,    23,    24,    25,   124,   151,
     162,   166,   167,   168,   172,   175,   178,   179,   185,   166,
      10,   188,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   189,   189,   189,   189,    13,   138,    22,    23,    24,
      25,   144,   145,   146,   162,    10,    10,   189,   189,   189,
     189,     9,   178,    15,   171,    15,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,   174,   190,    15,   177,   190,
     180,     9,   153,   134,   135,   139,   136,     8,   189,   189,
     189,   189,    13,   146,   159,   169,   170,   176,   173,    10,
     186,   185,    15,    27,   120,   191,    12,    15,   120,   192,
     185,    15,   181,   190,     7,    10,   187,   188,   185,   185,
     124,   125,   126,   129,   130,   162,   147,   148,   150,   149,
     143,   160,   187,   188,   185,   185,    10,   182,   120,   162,
     193,   194,   182,   182,   183,   140,   137,     3,   122,   163,
     124,     9,   187,   188,   185,   185,   161,   190,    13,   120,
     154,   190,   190,   183,   117,     6,   123,   187,   163
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
#define YYEMPTY		(-2)
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
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
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
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
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
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
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

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

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

  if (yyss + yystacksize - 1 <= yyssp)
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
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
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

      if (yyss + yystacksize - 1 <= yyssp)
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
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
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

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 207 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                       if(SKEL != NULL)
                       {
                           SKEL->profileElement(SKELTEXT);
                       }
                   ;}
    break;

  case 10:
#line 228 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                         if(SKEL != NULL)
                         {
                             SKEL->componentElement(SKELTEXT);
                         }
                     ;}
    break;

  case 15:
#line 245 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, SKELTEXT); ;}
    break;

  case 16:
#line 247 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                    if(SKEL != NULL)
                    {
                        SKEL->metaElement(szName1, SKELTEXT);
                    }
                    freeName(szName1);
                ;}
    break;

  case 27:
#line 273 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, SKELTEXT); ;}
    break;

  case 29:
#line 276 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                                  SKEL->use(SKELTEXT); ;}
    break;

  case 31:
#line 282 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, SKELTEXT); ;}
    break;

  case 39:
#line 299 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL) 
                        SKEL->beginProto(SKELTEXT); ;}
    break;

  case 40:
#line 301 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL) 
                        SKEL->beginProto(SKELTEXT); ;}
    break;

  case 41:
#line 312 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL) 
			SKEL->endProto(); ;}
    break;

  case 49:
#line 333 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                      SKELTEXT);;}
    break;

  case 50:
#line 335 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                                              {
                                               SKEL->beginEventInDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 

                                               SKEL->endEventDecl();
                                              }
                                              freeName(szName1); ;}
    break;

  case 51:
#line 346 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                      SKELTEXT);;}
    break;

  case 52:
#line 348 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                                              {
                                               SKEL->beginEventOutDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 

                                               SKEL->endEventDecl();
                                              }
                                              freeName(szName1); ;}
    break;

  case 53:
#line 359 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                      SKELTEXT);;}
    break;

  case 54:
#line 361 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { SKEL->expectType(nextType); 
                                              if(SKEL != NULL)
                                               SKEL->beginFieldDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 
                                              freeName(szName1); ;}
    break;

  case 55:
#line 368 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = 0; 
                                              if(SKEL != NULL)
                                               SKEL->endFieldDecl();
                                             ;}
    break;

  case 57:
#line 376 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                              SKELTEXT); ;}
    break;

  case 58:
#line 378 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { SKEL->expectType(nextType);  
                                      if(SKEL != NULL)
                                       SKEL->beginExposedFieldDecl(
                                        szName1,
                                        nextType,
                                        SKELTEXT); 
                                       freeName(szName1); ;}
    break;

  case 59:
#line 385 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = 0; 
                                      if(SKEL != NULL)
                                       SKEL->endExposedFieldDecl(); ;}
    break;

  case 60:
#line 391 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL) 
                             SKEL->beginExternProto(SKELTEXT); ;}
    break;

  case 61:
#line 396 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                 if(SKEL != NULL) 
                     SKEL->endExternProtoInterface(); 

                 SKEL->expectType(TOK_MFSTRING); 
              ;}
    break;

  case 62:
#line 403 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                 if(SKEL != NULL) 
                     SKEL->endExternProto(); 
              ;}
    break;

  case 67:
#line 419 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                 SKELTEXT); ;}
    break;

  case 68:
#line 421 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                                               SKEL->addExternEventInDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 
                                         freeName(szName1); ;}
    break;

  case 69:
#line 428 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                 SKELTEXT); ;}
    break;

  case 70:
#line 430 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                                               SKEL->addExternEventOutDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 
                                          freeName(szName1); ;}
    break;

  case 71:
#line 437 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                 SKELTEXT); ;}
    break;

  case 72:
#line 439 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                                               SKEL->addExternFieldDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 
                                         freeName(szName1); ;}
    break;

  case 73:
#line 446 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                 SKELTEXT); ;}
    break;

  case 74:
#line 448 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                                             SKEL->addExternExposedFieldDecl(
                                                 szName1,
                                                 nextType,
                                                 SKELTEXT); 
                                       freeName(szName1); ;}
    break;

  case 75:
#line 457 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, SKELTEXT); ;}
    break;

  case 76:
#line 459 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName2, SKELTEXT); ;}
    break;

  case 77:
#line 461 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName3, SKELTEXT); ;}
    break;

  case 78:
#line 463 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                                SKEL->addRoute(szName1, 
                                               szName2,
                                               szName3,
                                               SKELTEXT);
                              freeName(szName1);
                              freeName(szName2);
                              freeName(szName3);
                            ;}
    break;

  case 79:
#line 476 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                      setName(szName1, SKELTEXT);
                  ;}
    break;

  case 80:
#line 480 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                      if(SKEL != NULL)
                      {
                          SKEL->exportElement(szName1, szName2);
                      }

                      freeName(szName1);
                      freeName(szName2);
                  ;}
    break;

  case 81:
#line 493 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                      setName(szName1, SKELTEXT);
                  ;}
    break;

  case 82:
#line 498 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                      setName(szName3, SKELTEXT);
                  ;}
    break;

  case 83:
#line 502 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                      if(SKEL != NULL)
                      {
                          SKEL->importElement(szName1, szName3, szName2);
                      }
                    
                      freeName(szName1);
                      freeName(szName2);
                      freeName(szName3);
                  ;}
    break;

  case 84:
#line 515 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                        setName(szName2, SKELTEXT);
                  ;}
    break;

  case 88:
#line 527 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                    {
                        SKEL->beginNode(SKELTEXT, szName1); 
                    }

                    freeName(szName1);
                  ;}
    break;

  case 89:
#line 537 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                     SKEL->endNode(); ;}
    break;

  case 90:
#line 539 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                     SKEL->beginNode(SKELTEXT, szName1); 

                    freeName(szName1);
                  ;}
    break;

  case 91:
#line 546 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                     SKEL->endNode(); ;}
    break;

  case 96:
#line 569 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                          SKELTEXT); ;}
    break;

  case 97:
#line 571 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                                                     SKEL->beginEventInDecl(
                                                       szName1,
                                                       nextType,
                                                       SKELTEXT); 

                                                 freeName(szName1); ;}
    break;

  case 98:
#line 579 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                          SKELTEXT); ;}
    break;

  case 99:
#line 581 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                                                     SKEL->beginEventOutDecl(
                                                       szName1,
                                                       nextType,
                                                       SKELTEXT); 

                                                  freeName(szName1); ;}
    break;

  case 100:
#line 591 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { 
                                          if(SKEL != NULL)
                                          {
                                             SKEL->is(SKELTEXT);
                                             SKEL->endEventDecl(); 
                                          }
                                        ;}
    break;

  case 101:
#line 599 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { 
                                            if(SKEL != NULL)
                                            {
                                                SKEL->endEventDecl(); 
                                            }
                                        ;}
    break;

  case 102:
#line 608 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                         SKELTEXT);
                                               ;}
    break;

  case 103:
#line 611 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { SKEL->expectType(nextType); 
                                              
                                                 if(SKEL != NULL)
                                                     SKEL->beginFieldDecl(
                                                       szName1,
                                                       nextType,
                                                       SKELTEXT); 
                                              
                                                 freeName(szName1);
                                               ;}
    break;

  case 104:
#line 623 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = 0; 

                                                     if(SKEL != NULL)
                                                     {
                                                       SKEL->is(SKELTEXT);

                                                       SKEL->endFieldDecl();
                                                     }
                                                   ;}
    break;

  case 105:
#line 632 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = 0; 

                                                     if(SKEL != NULL)
                                                       SKEL->endFieldDecl();

                                                   ;}
    break;

  case 106:
#line 641 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                            SKELTEXT);
                                                  ;}
    break;

  case 107:
#line 644 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { SKEL->expectType(nextType);
                                                
                                                    if(SKEL != NULL)
                                                        SKEL->
                                                         beginExposedFieldDecl(
                                                           szName1,
                                                           nextType,
                                                           SKELTEXT); 
                                              
                                                    freeName(szName1);
                                                  ;}
    break;

  case 108:
#line 657 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = 0; 

                                                        if(SKEL != NULL)
                                                        {
                                                         SKEL->is(SKELTEXT);

                                                         SKEL->
                                                         endExposedFieldDecl();
                                                        }
                                                      ;}
    break;

  case 109:
#line 667 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = 0; 
   
                                                        if(SKEL != NULL)
                                                         SKEL->
                                                         endExposedFieldDecl();
                                                      ;}
    break;

  case 114:
#line 695 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                    {
                     Int32 iFieldTypeId;

                     iFieldTypeId = SKEL->getFieldType(SKELTEXT);

                     if(SKEL->getMapFieldTypes() == true)
                     {
                      iFieldTypeId = SKEL->mapExtIntFieldType(    
                                        SKELTEXT,
                                        iFieldTypeId);
                     }
    
                     SKEL->expectType(iFieldTypeId); 

                     SKEL->beginField(SKELTEXT, 
                                        iFieldTypeId);
                                        
                    } 
                   ;}
    break;

  case 118:
#line 722 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                          {
                            SKEL->is(SKELTEXT);
                            SKEL->endField();
                          }
                        ;}
    break;

  case 119:
#line 728 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                            SKEL->endField();
                        ;}
    break;

  case 127:
#line 756 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFCOLOR;    ;}
    break;

  case 128:
#line 757 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFFLOAT;    ;}
    break;

  case 129:
#line 758 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFINT32;    ;}
    break;

  case 130:
#line 759 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFNODE;     ;}
    break;

  case 131:
#line 760 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFROTATION; ;}
    break;

  case 132:
#line 761 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFSTRING;   ;}
    break;

  case 133:
#line 762 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFTIME;     ;}
    break;

  case 134:
#line 763 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFVEC2F;    ;}
    break;

  case 135:
#line 764 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFVEC3F;    ;}
    break;

  case 136:
#line 765 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFBOOL;     ;}
    break;

  case 137:
#line 766 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFCOLOR;    ;}
    break;

  case 138:
#line 767 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFFLOAT;    ;}
    break;

  case 139:
#line 768 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFIMAGE;    ;}
    break;

  case 140:
#line 769 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFINT32;    ;}
    break;

  case 141:
#line 770 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFNODE;     ;}
    break;

  case 142:
#line 771 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFROTATION; ;}
    break;

  case 143:
#line 772 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFSTRING;   ;}
    break;

  case 144:
#line 773 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFTIME;     ;}
    break;

  case 145:
#line 774 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFVEC2F;    ;}
    break;

  case 146:
#line 775 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFVEC3F;    ;}
    break;

  case 147:
#line 776 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFCOLOR4F;  ;}
    break;

  case 148:
#line 777 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFCOLOR4I;  ;}
    break;

  case 149:
#line 778 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFCOLOR3F;  ;}
    break;

  case 150:
#line 779 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFMATRIX;   ;}
    break;

  case 151:
#line 780 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFPNT2F;    ;}
    break;

  case 152:
#line 781 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFPNT3F;    ;}
    break;

  case 153:
#line 782 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFPNT4F;    ;}
    break;

  case 154:
#line 783 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFVEC4F;    ;}
    break;

  case 155:
#line 784 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFPLANE;    ;}
    break;

  case 156:
#line 785 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFCOLOR4F;  ;}
    break;

  case 157:
#line 786 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFCOLOR4I;  ;}
    break;

  case 158:
#line 787 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFCOLOR3F;  ;}
    break;

  case 159:
#line 788 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFMATRIX;   ;}
    break;

  case 160:
#line 789 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFPNT2F;    ;}
    break;

  case 161:
#line 790 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFPNT3F;    ;}
    break;

  case 162:
#line 791 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFPNT4F;    ;}
    break;

  case 163:
#line 792 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFVEC4F;    ;}
    break;

  case 164:
#line 793 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFPLANE;    ;}
    break;

  case 165:
#line 794 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFVOLUME;   ;}
    break;

  case 206:
#line 842 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                  if(SKEL != NULL)
                  {
                      SKEL->is(SKELTEXT);
                  }
              ;}
    break;

  case 209:
#line 853 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                  if(SKEL != NULL)
                  {
                      SKEL->is(SKELTEXT);
                  }
              ;}
    break;


    }

/* Line 999 of yacc.c.  */
#line 2389 "OSGScanParseSkel_.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


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
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



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
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
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


#line 871 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"


void setName (char *&szName, const char *szVal)
{
    stringDup(szVal, szName);
}

void freeName(char *&szName)
{
    delete [] szName;
    
    szName = NULL;
}

int OSGScanParseSkel_lex(YYSTYPE *, void *pSkel)
{
    return SKEL->lex();
}

