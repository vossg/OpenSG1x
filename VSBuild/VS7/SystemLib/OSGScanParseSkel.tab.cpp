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
     AS = 274,
     EVENTIN = 275,
     EVENTOUT = 276,
     EXPOSEDFIELD = 277,
     FIELD = 278,
     SCRIPT = 279,
     SFN_NULL = 280,
     TOK_SFBOOL = 281,
     TOK_SFCOLOR = 282,
     TOK_SFFLOAT = 283,
     TOK_SFIMAGE = 284,
     TOK_SFINT32 = 285,
     TOK_SFNODE = 286,
     TOK_SFROTATION = 287,
     TOK_SFSTRING = 288,
     TOK_SFTIME = 289,
     TOK_SFVEC2F = 290,
     TOK_SFVEC3F = 291,
     TOK_MFCOLOR = 292,
     TOK_MFFLOAT = 293,
     TOK_MFINT32 = 294,
     TOK_MFNODE = 295,
     TOK_MFROTATION = 296,
     TOK_MFSTRING = 297,
     TOK_MFTIME = 298,
     TOK_MFVEC2F = 299,
     TOK_MFVEC3F = 300,
     Tok_MFColor = 301,
     Tok_MFFloat = 302,
     Tok_MFInt32 = 303,
     Tok_MFNode = 304,
     Tok_MFRotation = 305,
     Tok_MFString = 306,
     Tok_MFTime = 307,
     Tok_MFVec2f = 308,
     Tok_MFVec3f = 309,
     Tok_SFBool = 310,
     Tok_SFColor = 311,
     Tok_SFFloat = 312,
     Tok_SFImage = 313,
     Tok_SFInt32 = 314,
     Tok_SFNode = 315,
     Tok_SFRotation = 316,
     Tok_SFString = 317,
     Tok_SFTime = 318,
     Tok_SFVec2f = 319,
     Tok_SFVec3f = 320,
     TOK_MFCOLOR4F = 321,
     TOK_MFCOLOR4I = 322,
     TOK_MFCOLOR3F = 323,
     TOK_MFMATRIX = 324,
     TOK_MFPNT2F = 325,
     TOK_MFPNT3F = 326,
     TOK_MFPNT4F = 327,
     TOK_MFVEC4F = 328,
     TOK_MFPLANE = 329,
     TOK_SFCOLOR4F = 330,
     TOK_SFCOLOR4I = 331,
     TOK_SFCOLOR3F = 332,
     TOK_SFMATRIX = 333,
     TOK_SFPNT2F = 334,
     TOK_SFPNT3F = 335,
     TOK_SFPNT4F = 336,
     TOK_SFVEC4F = 337,
     TOK_SFPLANE = 338,
     TOK_SFVOLUME = 339,
     Tok_MFColor4f = 340,
     Tok_MFColor4i = 341,
     Tok_MFColor3f = 342,
     Tok_MFMatrix = 343,
     Tok_MFPnt2f = 344,
     Tok_MFPnt3f = 345,
     Tok_MFPnt4f = 346,
     Tok_MFVec4f = 347,
     Tok_MFPlane = 348,
     Tok_SFColor4f = 349,
     Tok_SFColor4i = 350,
     Tok_SFColor3f = 351,
     Tok_SFMatrix = 352,
     Tok_SFPnt2f = 353,
     Tok_SFPnt3f = 354,
     Tok_SFPnt4f = 355,
     Tok_SFVec4f = 356,
     Tok_SFPlane = 357,
     Tok_SFVolume = 358
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
#define AS 274
#define EVENTIN 275
#define EVENTOUT 276
#define EXPOSEDFIELD 277
#define FIELD 278
#define SCRIPT 279
#define SFN_NULL 280
#define TOK_SFBOOL 281
#define TOK_SFCOLOR 282
#define TOK_SFFLOAT 283
#define TOK_SFIMAGE 284
#define TOK_SFINT32 285
#define TOK_SFNODE 286
#define TOK_SFROTATION 287
#define TOK_SFSTRING 288
#define TOK_SFTIME 289
#define TOK_SFVEC2F 290
#define TOK_SFVEC3F 291
#define TOK_MFCOLOR 292
#define TOK_MFFLOAT 293
#define TOK_MFINT32 294
#define TOK_MFNODE 295
#define TOK_MFROTATION 296
#define TOK_MFSTRING 297
#define TOK_MFTIME 298
#define TOK_MFVEC2F 299
#define TOK_MFVEC3F 300
#define Tok_MFColor 301
#define Tok_MFFloat 302
#define Tok_MFInt32 303
#define Tok_MFNode 304
#define Tok_MFRotation 305
#define Tok_MFString 306
#define Tok_MFTime 307
#define Tok_MFVec2f 308
#define Tok_MFVec3f 309
#define Tok_SFBool 310
#define Tok_SFColor 311
#define Tok_SFFloat 312
#define Tok_SFImage 313
#define Tok_SFInt32 314
#define Tok_SFNode 315
#define Tok_SFRotation 316
#define Tok_SFString 317
#define Tok_SFTime 318
#define Tok_SFVec2f 319
#define Tok_SFVec3f 320
#define TOK_MFCOLOR4F 321
#define TOK_MFCOLOR4I 322
#define TOK_MFCOLOR3F 323
#define TOK_MFMATRIX 324
#define TOK_MFPNT2F 325
#define TOK_MFPNT3F 326
#define TOK_MFPNT4F 327
#define TOK_MFVEC4F 328
#define TOK_MFPLANE 329
#define TOK_SFCOLOR4F 330
#define TOK_SFCOLOR4I 331
#define TOK_SFCOLOR3F 332
#define TOK_SFMATRIX 333
#define TOK_SFPNT2F 334
#define TOK_SFPNT3F 335
#define TOK_SFPNT4F 336
#define TOK_SFVEC4F 337
#define TOK_SFPLANE 338
#define TOK_SFVOLUME 339
#define Tok_MFColor4f 340
#define Tok_MFColor4i 341
#define Tok_MFColor3f 342
#define Tok_MFMatrix 343
#define Tok_MFPnt2f 344
#define Tok_MFPnt3f 345
#define Tok_MFPnt4f 346
#define Tok_MFVec4f 347
#define Tok_MFPlane 348
#define Tok_SFColor4f 349
#define Tok_SFColor4i 350
#define Tok_SFColor3f 351
#define Tok_SFMatrix 352
#define Tok_SFPnt2f 353
#define Tok_SFPnt3f 354
#define Tok_SFPnt4f 355
#define Tok_SFVec4f 356
#define Tok_SFPlane 357
#define Tok_SFVolume 358




/* Copy the first part of user declarations.  */
#line 38 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"


#define YYPARSE_PARAM pSkel
#define YYLEX_PARAM   pSkel

#define YYLTYPE_IS_TRIVIAL 1
#define YYSTYPE_IS_TRIVIAL 1

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

extern int  iLineNum;
//extern char OSGScanParseSkel_l_text[];

//extern int OSGScanParseSkel_l_lex(void);
//       int OSGScanParseSkel_lex  (void);

       int OSGScanParseSkel_lex  (YYSTYPE *lvalp, void *);

extern void expectType(int iType);

int nextType;

void OSGScanParseSkel_error(char *s);

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
#line 354 "OSGScanParseSkel_.tab.c"

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
#define YYFINAL  37
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   382

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  104
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  77
/* YYNRULES -- Number of rules. */
#define YYNRULES  196
/* YYNRULES -- Number of states. */
#define YYNSTATES  269

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   358

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
      95,    96,    97,    98,    99,   100,   101,   102,   103
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     5,     6,    11,    13,    15,    18,    20,
      22,    24,    26,    28,    30,    32,    33,    38,    41,    43,
      44,    49,    51,    53,    55,    56,    59,    61,    63,    65,
      74,    76,    78,    82,    84,    86,    89,    91,    92,    97,
      98,   103,   104,   105,   112,   114,   115,   116,   123,   124,
     125,   134,   136,   138,   141,   143,   144,   149,   150,   155,
     156,   161,   162,   167,   168,   169,   170,   182,   183,   188,
     189,   194,   197,   198,   200,   201,   202,   208,   209,   215,
     217,   219,   222,   224,   225,   230,   231,   236,   239,   240,
     241,   246,   249,   251,   253,   256,   259,   260,   264,   266,
     268,   271,   273,   275,   277,   279,   281,   283,   285,   287,
     289,   291,   293,   295,   297,   299,   301,   303,   305,   307,
     309,   311,   313,   315,   317,   319,   321,   323,   325,   327,
     329,   331,   333,   335,   337,   339,   341,   343,   345,   347,
     349,   351,   353,   355,   357,   359,   361,   363,   365,   367,
     369,   371,   373,   375,   378,   380,   382,   384,   386,   388,
     390,   392,   394,   397,   399,   401,   403,   405,   407,   409,
     411,   413,   415,   417,   419,   421,   423,   425,   427,   429,
     431,   433,   435,   437,   439,   441,   443,   445,   447,   450,
     452,   454,   457,   461,   463,   465,   468
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short yyrhs[] =
{
     105,     0,    -1,   106,    -1,    -1,    18,    10,   107,   108,
      -1,   108,    -1,   151,    -1,   108,   109,    -1,   109,    -1,
     110,    -1,   114,    -1,   141,    -1,   147,    -1,   145,    -1,
     152,    -1,    -1,     3,   169,   111,   152,    -1,     4,   169,
      -1,   152,    -1,    -1,     3,   169,   113,   152,    -1,   118,
      -1,   131,    -1,   116,    -1,    -1,   116,   114,    -1,   114,
      -1,   170,    -1,    24,    -1,    11,   117,    12,   121,    13,
       8,   119,     9,    -1,   120,    -1,   151,    -1,   115,   112,
     106,    -1,   122,    -1,   151,    -1,   122,   128,    -1,   128,
      -1,    -1,    20,   175,   124,   173,    -1,    -1,    21,   175,
     125,   174,    -1,    -1,    -1,    23,   175,   126,   171,   127,
     176,    -1,   123,    -1,    -1,    -1,    22,   175,   129,   171,
     130,   176,    -1,    -1,    -1,    14,   170,   132,    12,   134,
      13,   133,   150,    -1,   135,    -1,   151,    -1,   135,   136,
      -1,   136,    -1,    -1,    20,   175,   137,   173,    -1,    -1,
      21,   175,   138,   174,    -1,    -1,    23,   175,   139,   171,
      -1,    -1,    22,   175,   140,   171,    -1,    -1,    -1,    -1,
       5,   169,   142,     6,   174,   143,     7,   169,   144,     6,
     173,    -1,    -1,    16,    10,   146,   149,    -1,    -1,    17,
      10,   148,   149,    -1,    19,    10,    -1,    -1,   176,    -1,
      -1,    -1,   170,   153,     8,   155,     9,    -1,    -1,    24,
     154,     8,   155,     9,    -1,   156,    -1,   151,    -1,   156,
     164,    -1,   164,    -1,    -1,    20,   175,   158,   173,    -1,
      -1,    21,   175,   159,   174,    -1,    15,   172,    -1,    -1,
      -1,    23,   175,   162,   171,    -1,    15,   171,    -1,   176,
      -1,   165,    -1,   157,   160,    -1,   161,   163,    -1,    -1,
     171,   166,   167,    -1,   141,    -1,   114,    -1,    15,   168,
      -1,   176,    -1,    10,    -1,    10,    -1,    10,    -1,    10,
      -1,    10,    -1,    10,    -1,    10,    -1,    46,    -1,    47,
      -1,    48,    -1,    49,    -1,    50,    -1,    51,    -1,    52,
      -1,    53,    -1,    54,    -1,    55,    -1,    56,    -1,    57,
      -1,    58,    -1,    59,    -1,    60,    -1,    61,    -1,    62,
      -1,    63,    -1,    64,    -1,    65,    -1,    85,    -1,    86,
      -1,    87,    -1,    88,    -1,    89,    -1,    90,    -1,    91,
      -1,    92,    -1,    93,    -1,    94,    -1,    95,    -1,    96,
      -1,    97,    -1,    98,    -1,    99,    -1,   100,    -1,   101,
      -1,   102,    -1,   103,    -1,    26,    -1,    27,    -1,    28,
      -1,    29,    -1,    30,    -1,    31,   177,    -1,    32,    -1,
      33,    -1,    34,    -1,    35,    -1,    36,    -1,    37,    -1,
      38,    -1,    39,    -1,    40,   178,    -1,    41,    -1,    42,
      -1,    43,    -1,    44,    -1,    45,    -1,    66,    -1,    67,
      -1,    68,    -1,    69,    -1,    70,    -1,    71,    -1,    72,
      -1,    74,    -1,    73,    -1,    75,    -1,    76,    -1,    77,
      -1,    78,    -1,    79,    -1,    80,    -1,    81,    -1,    83,
      -1,    84,    -1,    82,    -1,   110,    -1,    15,   168,    -1,
      25,    -1,   110,    -1,    15,   168,    -1,    12,   179,    13,
      -1,   180,    -1,   151,    -1,   180,   110,    -1,   110,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   208,   208,   213,   211,   220,   221,   224,   225,   228,
     229,   230,   231,   232,   235,   237,   236,   239,   244,   246,
     245,   250,   251,   255,   256,   259,   260,   263,   265,   269,
     280,   281,   284,   287,   288,   291,   292,   297,   296,   310,
     309,   323,   325,   322,   338,   340,   342,   339,   355,   360,
     354,   373,   374,   378,   379,   383,   382,   392,   391,   401,
     400,   410,   409,   421,   423,   425,   420,   440,   438,   457,
     455,   472,   476,   479,   482,   485,   485,   497,   497,   516,
     517,   520,   521,   525,   524,   535,   534,   546,   555,   564,
     563,   579,   588,   605,   606,   608,   614,   613,   635,   636,
     641,   647,   654,   657,   660,   663,   666,   669,   672,   675,
     676,   677,   678,   679,   680,   681,   682,   683,   684,   685,
     686,   687,   688,   689,   690,   691,   692,   693,   694,   695,
     696,   697,   698,   699,   700,   701,   702,   703,   704,   705,
     706,   707,   708,   709,   710,   711,   712,   713,   717,   718,
     719,   720,   721,   722,   723,   724,   725,   726,   727,   728,
     729,   730,   731,   732,   733,   734,   735,   736,   737,   738,
     739,   740,   741,   742,   743,   744,   745,   746,   747,   748,
     749,   750,   751,   752,   753,   754,   755,   759,   760,   767,
     770,   771,   778,   781,   782,   785,   786
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DEF", "USE", "ROUTE", "PERIOD", "TO", 
  "OPENBRACE", "CLOSEBRACE", "ID", "PROTO", "OPENBRACKET", "CLOSEBRACKET", 
  "EXTERNPROTO", "IS", "EXPORT", "IMPORT", "PROFILE", "AS", "EVENTIN", 
  "EVENTOUT", "EXPOSEDFIELD", "FIELD", "SCRIPT", "SFN_NULL", "TOK_SFBOOL", 
  "TOK_SFCOLOR", "TOK_SFFLOAT", "TOK_SFIMAGE", "TOK_SFINT32", 
  "TOK_SFNODE", "TOK_SFROTATION", "TOK_SFSTRING", "TOK_SFTIME", 
  "TOK_SFVEC2F", "TOK_SFVEC3F", "TOK_MFCOLOR", "TOK_MFFLOAT", 
  "TOK_MFINT32", "TOK_MFNODE", "TOK_MFROTATION", "TOK_MFSTRING", 
  "TOK_MFTIME", "TOK_MFVEC2F", "TOK_MFVEC3F", "Tok_MFColor", 
  "Tok_MFFloat", "Tok_MFInt32", "Tok_MFNode", "Tok_MFRotation", 
  "Tok_MFString", "Tok_MFTime", "Tok_MFVec2f", "Tok_MFVec3f", 
  "Tok_SFBool", "Tok_SFColor", "Tok_SFFloat", "Tok_SFImage", 
  "Tok_SFInt32", "Tok_SFNode", "Tok_SFRotation", "Tok_SFString", 
  "Tok_SFTime", "Tok_SFVec2f", "Tok_SFVec3f", "TOK_MFCOLOR4F", 
  "TOK_MFCOLOR4I", "TOK_MFCOLOR3F", "TOK_MFMATRIX", "TOK_MFPNT2F", 
  "TOK_MFPNT3F", "TOK_MFPNT4F", "TOK_MFVEC4F", "TOK_MFPLANE", 
  "TOK_SFCOLOR4F", "TOK_SFCOLOR4I", "TOK_SFCOLOR3F", "TOK_SFMATRIX", 
  "TOK_SFPNT2F", "TOK_SFPNT3F", "TOK_SFPNT4F", "TOK_SFVEC4F", 
  "TOK_SFPLANE", "TOK_SFVOLUME", "Tok_MFColor4f", "Tok_MFColor4i", 
  "Tok_MFColor3f", "Tok_MFMatrix", "Tok_MFPnt2f", "Tok_MFPnt3f", 
  "Tok_MFPnt4f", "Tok_MFVec4f", "Tok_MFPlane", "Tok_SFColor4f", 
  "Tok_SFColor4i", "Tok_SFColor3f", "Tok_SFMatrix", "Tok_SFPnt2f", 
  "Tok_SFPnt3f", "Tok_SFPnt4f", "Tok_SFVec4f", "Tok_SFPlane", 
  "Tok_SFVolume", "$accept", "vrmlScene", "statementsORempty", "@1", 
  "statements", "statement", "nodeStatement", "@2", "rootNodeStatement", 
  "@3", "protoStatement", "protoStatementsORempty", "protoStatements", 
  "protoId", "proto", "protoBodyORempty", "protoBody", 
  "interfaceDeclarationsORempty", "interfaceDeclarations", 
  "restrictedInterfaceDeclaration", "@4", "@5", "@6", "@7", 
  "interfaceDeclaration", "@8", "@9", "externproto", "@10", "@11", 
  "externInterfaceDeclarationsORempty", "externInterfaceDeclarations", 
  "externInterfaceDeclaration", "@12", "@13", "@14", "@15", 
  "routeStatement", "@16", "@17", "@18", "exportStatement", "@19", 
  "importStatement", "@20", "importExportEnd", "URLList", "empty", "node", 
  "@21", "@22", "scriptBodyORempty", "scriptBody", 
  "resInterfaceDeclarationScriptEvent", "@23", "@24", 
  "resInterfaceDeclarationScriptEventEnd", 
  "resInterfaceDeclarationScriptField", "@25", 
  "resInterafceDeclarationScriptFieldEnd", "scriptBodyElement", 
  "nodeBodyElement", "@26", "fieldEnd", "generalId", "nodeNameId", 
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
     355,   356,   357,   358
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,   104,   105,   107,   106,   106,   106,   108,   108,   109,
     109,   109,   109,   109,   110,   111,   110,   110,   112,   113,
     112,   114,   114,   115,   115,   116,   116,   117,   117,   118,
     119,   119,   120,   121,   121,   122,   122,   124,   123,   125,
     123,   126,   127,   123,   128,   129,   130,   128,   132,   133,
     131,   134,   134,   135,   135,   137,   136,   138,   136,   139,
     136,   140,   136,   142,   143,   144,   141,   146,   145,   148,
     147,   149,   149,   150,   151,   153,   152,   154,   152,   155,
     155,   156,   156,   158,   157,   159,   157,   160,   160,   162,
     161,   163,   163,   164,   164,   164,   166,   165,   165,   165,
     167,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,   175,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   177,   177,   177,
     178,   178,   178,   179,   179,   180,   180
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     0,     4,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     2,     1,     0,
       4,     1,     1,     1,     0,     2,     1,     1,     1,     8,
       1,     1,     3,     1,     1,     2,     1,     0,     4,     0,
       4,     0,     0,     6,     1,     0,     0,     6,     0,     0,
       8,     1,     1,     2,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     0,     0,    11,     0,     4,     0,
       4,     2,     0,     1,     0,     0,     5,     0,     5,     1,
       1,     2,     1,     0,     4,     0,     4,     2,     0,     0,
       4,     2,     1,     1,     2,     2,     0,     3,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     2,     3,     1,     1,     2,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
      74,     0,     0,     0,   104,     0,     0,     0,     0,     0,
      77,     0,     2,     5,     8,     9,    10,    21,    22,    11,
      13,    12,     6,    14,    75,   103,    15,    17,    63,    28,
       0,    27,    48,    67,    69,     3,     0,     1,     7,     0,
       0,     0,    74,     0,    72,    72,     0,    74,    74,    16,
       0,     0,     0,     0,     0,     0,    33,    44,    36,    34,
      74,     0,    68,    70,     4,   105,     0,     0,     0,    99,
      98,    80,     0,    79,    88,     0,    82,    93,    96,     0,
     108,    64,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,    37,    39,    45,    41,     0,    35,     0,     0,     0,
       0,     0,    51,    54,    52,    71,    83,    85,    89,    78,
      81,     0,    94,     0,   148,   149,   150,   151,   152,     0,
     154,   155,   156,   157,   158,   159,   160,   161,     0,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   176,   175,   177,   178,   179,   180,   181,   182,   183,
     186,   184,   185,    95,    92,     0,    76,     0,     0,     0,
       0,     0,    24,    55,    57,    61,    59,    49,    53,     0,
       0,     0,   106,    87,    91,     0,   189,   187,   153,    74,
       0,   190,   162,     0,    97,   101,     0,   107,    38,    40,
      46,    42,    26,     0,    23,     0,    30,    31,     0,     0,
       0,     0,     0,    84,    86,    90,   102,   188,   196,   194,
       0,   193,   191,   100,    65,     0,     0,     0,    74,    18,
      25,    29,    56,    58,    62,    60,    50,    73,   192,   195,
       0,    47,    43,    19,    32,     0,     0,    66,    20
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,    11,    12,    46,    13,    14,    15,    40,   248,   266,
      16,   223,   224,    30,    17,   225,   226,    55,    56,    57,
     188,   189,   191,   246,    58,   190,   245,    18,    43,   232,
     131,   132,   133,   228,   229,   231,   230,    19,    41,   187,
     260,    20,    44,    21,    45,    62,   256,    22,    23,    39,
      36,    72,    73,    74,   199,   200,   142,    75,   201,   183,
      76,    77,   185,   214,   237,    26,    24,    78,   203,   218,
      81,   121,   184,   208,   212,   240,   241
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -182
static const short yypact[] =
{
     123,     8,     8,     8,  -182,    10,    12,    47,    48,    52,
    -182,    51,  -182,   140,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
      80,  -182,  -182,  -182,  -182,  -182,    55,  -182,  -182,    85,
      11,    95,   109,    94,   117,   117,   140,   148,   148,  -182,
     132,   279,   279,   279,   279,   133,   109,  -182,  -182,  -182,
     153,   139,  -182,  -182,   140,  -182,   279,   279,   279,  -182,
    -182,  -182,   143,   148,   145,    41,  -182,  -182,  -182,   152,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,   155,  -182,   279,   279,   279,
     279,   154,   153,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,   156,  -182,   160,  -182,  -182,  -182,  -182,  -182,    21,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,    37,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,   220,  -182,   158,   167,   132,
     160,   160,    88,  -182,  -182,  -182,  -182,  -182,  -182,   167,
     132,   160,  -182,  -182,  -182,   168,  -182,  -182,  -182,    29,
     168,  -182,  -182,   168,  -182,  -182,     8,  -182,  -182,  -182,
    -182,  -182,  -182,    40,    89,   170,  -182,  -182,   167,   132,
     160,   160,   240,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
     169,    29,  -182,  -182,  -182,   240,   240,     8,   123,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
     175,  -182,  -182,  -182,  -182,   167,    11,  -182,  -182
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -182,  -182,   -65,  -182,   138,    -4,  -143,  -182,  -182,  -182,
     -44,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,   130,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,    56,  -182,  -182,  -182,  -182,   -31,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,   142,  -182,   -37,   -38,  -182,
    -182,   141,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
     118,  -182,  -182,  -182,   -75,    -2,    32,  -136,  -182,  -169,
    -181,   -40,  -141,  -182,  -182,  -182,  -182
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -75
static const short yytable[] =
{
      27,    28,    49,    69,    69,    59,   207,   204,   219,    38,
      71,    71,   122,   123,   124,   211,    70,    70,    25,   234,
       4,     4,     4,   134,     1,     2,   136,   137,   138,    69,
     233,     4,     1,     2,    29,    10,   205,    31,    32,     4,
       1,     2,    70,   247,   215,    10,   206,     4,   253,   209,
       4,    37,   210,    10,   220,   221,   143,    33,    34,   252,
      38,    10,    35,    47,    10,   235,   238,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   193,   194,   195,
     196,   257,    42,    48,   254,   255,   267,   -74,   259,     5,
       5,    50,     6,     6,   261,   262,    60,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,     1,     2,     3,    51,
      52,    53,    54,     4,     5,   242,    61,     6,   243,     7,
       8,     9,    80,     1,     2,     3,   125,    10,   222,   135,
       4,     5,   139,     3,     6,   227,     7,     8,    65,     5,
     141,   186,     6,   192,    10,   216,   202,   197,    66,    67,
      65,    68,   239,   127,   128,   129,   130,   217,   236,   251,
     250,   265,   258,   264,    64,   249,   126,    63,   198,    79,
       0,   140,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   244,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   268,     0,
       0,     0,     0,     0,     0,   213,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   263,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,     0,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120
};

static const short yycheck[] =
{
       2,     3,    40,    47,    48,    42,   149,   143,   189,    13,
      47,    48,    52,    53,    54,   158,    47,    48,    10,   200,
      10,    10,    10,    60,     3,     4,    66,    67,    68,    73,
     199,    10,     3,     4,    24,    24,    15,     5,     6,    10,
       3,     4,    73,     3,   185,    24,    25,    10,   229,    12,
      10,     0,    15,    24,   190,   191,    15,    10,    10,   228,
      64,    24,    10,     8,    24,   201,   209,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,   127,   128,   129,
     130,   232,    12,     8,   230,   231,   265,     9,   241,    11,
      11,     6,    14,    14,   245,   246,    12,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,     3,     4,     5,    20,
      21,    22,    23,    10,    11,   210,    19,    14,   213,    16,
      17,    18,    10,     3,     4,     5,    13,    24,   192,    10,
      10,    11,     9,     5,    14,   192,    16,    17,    10,    11,
      15,     9,    14,     8,    24,     7,    10,    13,    20,    21,
      10,    23,   209,    20,    21,    22,    23,    10,    10,     9,
     224,     6,    13,   248,    46,   223,    56,    45,   132,    48,
      -1,    73,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   216,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   266,    -1,
      -1,    -1,    -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   247,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    -1,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,     5,    10,    11,    14,    16,    17,    18,
      24,   105,   106,   108,   109,   110,   114,   118,   131,   141,
     145,   147,   151,   152,   170,    10,   169,   169,   169,    24,
     117,   170,   170,    10,    10,    10,   154,     0,   109,   153,
     111,   142,    12,   132,   146,   148,   107,     8,     8,   152,
       6,    20,    21,    22,    23,   121,   122,   123,   128,   151,
      12,    19,   149,   149,   108,    10,    20,    21,    23,   114,
     141,   151,   155,   156,   157,   161,   164,   165,   171,   155,
      10,   174,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   175,   175,   175,   175,    13,   128,    20,    21,    22,
      23,   134,   135,   136,   151,    10,   175,   175,   175,     9,
     164,    15,   160,    15,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,   163,   176,   166,     9,   143,   124,   125,
     129,   126,     8,   175,   175,   175,   175,    13,   136,   158,
     159,   162,    10,   172,   171,    15,    25,   110,   177,    12,
      15,   110,   178,    15,   167,   176,     7,    10,   173,   174,
     171,   171,   114,   115,   116,   119,   120,   151,   137,   138,
     140,   139,   133,   173,   174,   171,    10,   168,   110,   151,
     179,   180,   168,   168,   169,   130,   127,     3,   112,   152,
     114,     9,   173,   174,   171,   171,   150,   176,    13,   110,
     144,   176,   176,   169,   106,     6,   113,   173,   152
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
#line 213 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                        if(SKEL != NULL)
                        {
                            SKEL->profile(SKELTEXT);
                        }
                    ;}
    break;

  case 15:
#line 237 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, SKELTEXT); ;}
    break;

  case 17:
#line 240 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                                  SKEL->use(SKELTEXT); ;}
    break;

  case 19:
#line 246 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, SKELTEXT); ;}
    break;

  case 27:
#line 263 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL) 
                        SKEL->beginProto(SKELTEXT); ;}
    break;

  case 28:
#line 265 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL) 
                        SKEL->beginProto(SKELTEXT); ;}
    break;

  case 29:
#line 276 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL) 
			SKEL->endProto(); ;}
    break;

  case 37:
#line 297 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                      SKELTEXT);;}
    break;

  case 38:
#line 299 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
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

  case 39:
#line 310 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                      SKELTEXT);;}
    break;

  case 40:
#line 312 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
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

  case 41:
#line 323 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                      SKELTEXT);;}
    break;

  case 42:
#line 325 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { expectType(nextType); 
                                              if(SKEL != NULL)
                                               SKEL->beginFieldDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 
                                              freeName(szName1); ;}
    break;

  case 43:
#line 332 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = 0; 
                                              if(SKEL != NULL)
                                               SKEL->endFieldDecl();
                                             ;}
    break;

  case 45:
#line 340 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                              SKELTEXT); ;}
    break;

  case 46:
#line 342 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { expectType(nextType);  
                                      if(SKEL != NULL)
                                       SKEL->beginExposedFieldDecl(
                                        szName1,
                                        nextType,
                                        SKELTEXT); 
                                       freeName(szName1); ;}
    break;

  case 47:
#line 349 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = 0; 
                                      if(SKEL != NULL)
                                       SKEL->endExposedFieldDecl(); ;}
    break;

  case 48:
#line 355 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL) 
                             SKEL->beginExternProto(SKELTEXT); ;}
    break;

  case 49:
#line 360 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                 if(SKEL != NULL) 
                     SKEL->endExternProtoInterface(); 

                 expectType(TOK_MFSTRING); 
              ;}
    break;

  case 50:
#line 367 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                 if(SKEL != NULL) 
                     SKEL->endExternProto(); 
              ;}
    break;

  case 55:
#line 383 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                 SKELTEXT); ;}
    break;

  case 56:
#line 385 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                                               SKEL->addExternEventInDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 
                                         freeName(szName1); ;}
    break;

  case 57:
#line 392 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                 SKELTEXT); ;}
    break;

  case 58:
#line 394 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                                               SKEL->addExternEventOutDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 
                                          freeName(szName1); ;}
    break;

  case 59:
#line 401 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                 SKELTEXT); ;}
    break;

  case 60:
#line 403 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                                               SKEL->addExternFieldDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 
                                         freeName(szName1); ;}
    break;

  case 61:
#line 410 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                 SKELTEXT); ;}
    break;

  case 62:
#line 412 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                                             SKEL->addExternExposedFieldDecl(
                                                 szName1,
                                                 nextType,
                                                 SKELTEXT); 
                                       freeName(szName1); ;}
    break;

  case 63:
#line 421 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, SKELTEXT); ;}
    break;

  case 64:
#line 423 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName2, SKELTEXT); ;}
    break;

  case 65:
#line 425 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName3, SKELTEXT); ;}
    break;

  case 66:
#line 427 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
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

  case 67:
#line 440 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                      setName(szName1, SKELTEXT);
                  ;}
    break;

  case 68:
#line 444 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                      if(SKEL != NULL)
                      {
                          SKEL->exportElement(szName1, szName2);
                      }

                      freeName(szName1);
                      freeName(szName2);
                  ;}
    break;

  case 69:
#line 457 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                      setName(szName1, SKELTEXT);
                  ;}
    break;

  case 70:
#line 461 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                      if(SKEL != NULL)
                      {
                          SKEL->importElement(szName1, szName2);
                      }
                    
                      freeName(szName1);
                      freeName(szName2);
                  ;}
    break;

  case 71:
#line 473 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                        setName(szName2, SKELTEXT);
                  ;}
    break;

  case 75:
#line 485 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                    {
                        SKEL->beginNode(SKELTEXT, szName1); 
                    }

                    freeName(szName1);
                  ;}
    break;

  case 76:
#line 495 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                     SKEL->endNode(); ;}
    break;

  case 77:
#line 497 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                     SKEL->beginNode(SKELTEXT, szName1); 

                    freeName(szName1);
                  ;}
    break;

  case 78:
#line 504 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                     SKEL->endNode(); ;}
    break;

  case 83:
#line 525 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                          SKELTEXT); ;}
    break;

  case 84:
#line 527 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                                                     SKEL->beginEventInDecl(
                                                       szName1,
                                                       nextType,
                                                       SKELTEXT); 

                                                 freeName(szName1); ;}
    break;

  case 85:
#line 535 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                          SKELTEXT); ;}
    break;

  case 86:
#line 537 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                                                     SKEL->beginEventOutDecl(
                                                       szName1,
                                                       nextType,
                                                       SKELTEXT); 

                                                  freeName(szName1); ;}
    break;

  case 87:
#line 547 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { 
                                          if(SKEL != NULL)
                                          {
                                             SKEL->is(SKELTEXT);
                                             SKEL->endEventDecl(); 
                                          }
                                        ;}
    break;

  case 88:
#line 555 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { 
                                            if(SKEL != NULL)
                                            {
                                                SKEL->endEventDecl(); 
                                            }
                                        ;}
    break;

  case 89:
#line 564 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                         SKELTEXT);
                                               ;}
    break;

  case 90:
#line 567 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { expectType(nextType); 
                                              
                                                 if(SKEL != NULL)
                                                     SKEL->beginFieldDecl(
                                                       szName1,
                                                       nextType,
                                                       SKELTEXT); 
                                              
                                                 freeName(szName1);
                                               ;}
    break;

  case 91:
#line 579 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = 0; 

                                                     if(SKEL != NULL)
                                                     {
                                                       SKEL->is(SKELTEXT);

                                                       SKEL->endFieldDecl();
                                                     }
                                                   ;}
    break;

  case 92:
#line 588 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = 0; 

                                                     if(SKEL != NULL)
                                                       SKEL->endFieldDecl();

                                                   ;}
    break;

  case 96:
#line 614 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
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
    
                     expectType(iFieldTypeId); 

                     SKEL->beginField(SKELTEXT, 
                                        iFieldTypeId);
                                        
                    } 
                   ;}
    break;

  case 100:
#line 641 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                          {
                            SKEL->is(SKELTEXT);
                            SKEL->endField();
                          }
                        ;}
    break;

  case 101:
#line 647 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                            SKEL->endField();
                        ;}
    break;

  case 109:
#line 675 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFCOLOR;    ;}
    break;

  case 110:
#line 676 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFFLOAT;    ;}
    break;

  case 111:
#line 677 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFINT32;    ;}
    break;

  case 112:
#line 678 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFNODE;     ;}
    break;

  case 113:
#line 679 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFROTATION; ;}
    break;

  case 114:
#line 680 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFSTRING;   ;}
    break;

  case 115:
#line 681 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFTIME;     ;}
    break;

  case 116:
#line 682 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFVEC2F;    ;}
    break;

  case 117:
#line 683 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFVEC3F;    ;}
    break;

  case 118:
#line 684 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFBOOL;     ;}
    break;

  case 119:
#line 685 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFCOLOR;    ;}
    break;

  case 120:
#line 686 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFFLOAT;    ;}
    break;

  case 121:
#line 687 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFIMAGE;    ;}
    break;

  case 122:
#line 688 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFINT32;    ;}
    break;

  case 123:
#line 689 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFNODE;     ;}
    break;

  case 124:
#line 690 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFROTATION; ;}
    break;

  case 125:
#line 691 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFSTRING;   ;}
    break;

  case 126:
#line 692 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFTIME;     ;}
    break;

  case 127:
#line 693 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFVEC2F;    ;}
    break;

  case 128:
#line 694 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFVEC3F;    ;}
    break;

  case 129:
#line 695 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFCOLOR4F;  ;}
    break;

  case 130:
#line 696 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFCOLOR4I;  ;}
    break;

  case 131:
#line 697 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFCOLOR3F;  ;}
    break;

  case 132:
#line 698 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFMATRIX;   ;}
    break;

  case 133:
#line 699 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFPNT2F;    ;}
    break;

  case 134:
#line 700 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFPNT3F;    ;}
    break;

  case 135:
#line 701 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFPNT4F;    ;}
    break;

  case 136:
#line 702 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFVEC4F;    ;}
    break;

  case 137:
#line 703 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFPLANE;    ;}
    break;

  case 138:
#line 704 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFCOLOR4F;  ;}
    break;

  case 139:
#line 705 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFCOLOR4I;  ;}
    break;

  case 140:
#line 706 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFCOLOR3F;  ;}
    break;

  case 141:
#line 707 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFMATRIX;   ;}
    break;

  case 142:
#line 708 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFPNT2F;    ;}
    break;

  case 143:
#line 709 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFPNT3F;    ;}
    break;

  case 144:
#line 710 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFPNT4F;    ;}
    break;

  case 145:
#line 711 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFVEC4F;    ;}
    break;

  case 146:
#line 712 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFPLANE;    ;}
    break;

  case 147:
#line 713 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFVOLUME;   ;}
    break;

  case 188:
#line 761 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                  if(SKEL != NULL)
                  {
                      SKEL->is(SKELTEXT);
                  }
              ;}
    break;

  case 191:
#line 772 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                  if(SKEL != NULL)
                  {
                      SKEL->is(SKELTEXT);
                  }
              ;}
    break;


    }

/* Line 999 of yacc.c.  */
#line 2249 "OSGScanParseSkel_.tab.c"

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


#line 790 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"


extern void setSkel    (ScanParseSkel *pSkel);
extern void clearSkel  (void);

void OSGScanParseSkel_error (char *s)  /* Called by fhs_parse on error */
{
  FWARNING(("-----> %s in Line %d\n", s, iLineNum));
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


int OSGScanParseSkel_lex(YYSTYPE *, void *pSkel)
{
    setSkel(SKEL);

    int returnValue = SKEL->lex();

    clearSkel();
 
    return returnValue;
}

