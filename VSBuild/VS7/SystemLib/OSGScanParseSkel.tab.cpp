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
#line 345 "OSGScanParseSkel_.tab.c"

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
#define YYFINAL  29
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   421

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  100
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  73
/* YYNRULES -- Number of rules. */
#define YYNRULES  190
/* YYNRULES -- Number of states. */
#define YYNSTATES  257

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   354

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
     102,   104,   105,   106,   113,   114,   115,   124,   126,   128,
     131,   133,   134,   139,   140,   145,   146,   151,   152,   157,
     158,   159,   160,   172,   174,   175,   176,   182,   183,   189,
     191,   193,   196,   198,   200,   202,   205,   207,   208,   213,
     214,   219,   222,   223,   224,   229,   232,   234,   236,   239,
     242,   243,   247,   249,   251,   254,   256,   258,   260,   262,
     264,   266,   268,   270,   272,   274,   276,   278,   280,   282,
     284,   286,   288,   290,   292,   294,   296,   298,   300,   302,
     304,   306,   308,   310,   312,   314,   316,   318,   320,   322,
     324,   326,   328,   330,   332,   334,   336,   338,   340,   342,
     344,   346,   348,   350,   352,   354,   356,   358,   361,   363,
     365,   367,   369,   371,   373,   375,   377,   380,   382,   384,
     386,   388,   390,   392,   394,   396,   398,   400,   402,   404,
     406,   408,   410,   412,   414,   416,   418,   420,   422,   424,
     426,   428,   430,   433,   435,   437,   440,   444,   446,   448,
     451
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short yyrhs[] =
{
     101,     0,    -1,   102,    -1,   103,    -1,   141,    -1,   103,
     104,    -1,   104,    -1,   105,    -1,   109,    -1,   136,    -1,
     142,    -1,    -1,     3,   161,   106,   142,    -1,     4,   161,
      -1,   142,    -1,    -1,     3,   161,   108,   142,    -1,   113,
      -1,   126,    -1,   111,    -1,    -1,   111,   109,    -1,   109,
      -1,   162,    -1,    20,    -1,    11,   112,    12,   116,    13,
       8,   114,     9,    -1,   115,    -1,   141,    -1,   110,   107,
     102,    -1,   117,    -1,   141,    -1,   117,   123,    -1,   123,
      -1,    -1,    16,   167,   119,   165,    -1,    -1,    17,   167,
     120,   166,    -1,    -1,    -1,    19,   167,   121,   163,   122,
     168,    -1,   118,    -1,    -1,    -1,    18,   167,   124,   163,
     125,   168,    -1,    -1,    -1,    14,   162,   127,    12,   129,
      13,   128,   140,    -1,   130,    -1,   141,    -1,   130,   131,
      -1,   131,    -1,    -1,    16,   167,   132,   165,    -1,    -1,
      17,   167,   133,   166,    -1,    -1,    19,   167,   134,   163,
      -1,    -1,    18,   167,   135,   163,    -1,    -1,    -1,    -1,
       5,   161,   137,     6,   166,   138,     7,   161,   139,     6,
     165,    -1,   168,    -1,    -1,    -1,   162,   143,     8,   145,
       9,    -1,    -1,    20,   144,     8,   147,     9,    -1,   146,
      -1,   141,    -1,   146,   157,    -1,   157,    -1,   148,    -1,
     141,    -1,   148,   156,    -1,   156,    -1,    -1,    16,   167,
     150,   165,    -1,    -1,    17,   167,   151,   166,    -1,    15,
     164,    -1,    -1,    -1,    19,   167,   154,   163,    -1,    15,
     163,    -1,   168,    -1,   157,    -1,   149,   152,    -1,   153,
     155,    -1,    -1,   163,   158,   159,    -1,   136,    -1,   109,
      -1,    15,   160,    -1,   168,    -1,    10,    -1,    10,    -1,
      10,    -1,    10,    -1,    10,    -1,    10,    -1,    10,    -1,
      42,    -1,    43,    -1,    44,    -1,    45,    -1,    46,    -1,
      47,    -1,    48,    -1,    49,    -1,    50,    -1,    51,    -1,
      52,    -1,    53,    -1,    54,    -1,    55,    -1,    56,    -1,
      57,    -1,    58,    -1,    59,    -1,    60,    -1,    61,    -1,
      81,    -1,    82,    -1,    83,    -1,    84,    -1,    85,    -1,
      86,    -1,    87,    -1,    88,    -1,    89,    -1,    90,    -1,
      91,    -1,    92,    -1,    93,    -1,    94,    -1,    95,    -1,
      96,    -1,    97,    -1,    98,    -1,    99,    -1,    22,    -1,
      23,    -1,    24,    -1,    25,    -1,    26,    -1,    27,   169,
      -1,    28,    -1,    29,    -1,    30,    -1,    31,    -1,    32,
      -1,    33,    -1,    34,    -1,    35,    -1,    36,   170,    -1,
      37,    -1,    38,    -1,    39,    -1,    40,    -1,    41,    -1,
      62,    -1,    63,    -1,    64,    -1,    65,    -1,    66,    -1,
      67,    -1,    68,    -1,    70,    -1,    69,    -1,    71,    -1,
      72,    -1,    73,    -1,    74,    -1,    75,    -1,    76,    -1,
      77,    -1,    79,    -1,    80,    -1,    78,    -1,   105,    -1,
      15,   160,    -1,    21,    -1,   105,    -1,    15,   160,    -1,
      12,   171,    13,    -1,   172,    -1,   141,    -1,   172,   105,
      -1,   105,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   203,   203,   206,   207,   210,   211,   214,   215,   216,
     219,   221,   220,   223,   228,   230,   229,   234,   235,   239,
     240,   243,   244,   247,   249,   253,   264,   265,   268,   271,
     272,   275,   276,   281,   280,   294,   293,   307,   309,   306,
     322,   324,   326,   323,   339,   344,   338,   357,   358,   362,
     363,   367,   366,   376,   375,   385,   384,   394,   393,   405,
     407,   409,   404,   422,   425,   428,   428,   437,   437,   448,
     449,   452,   453,   456,   457,   460,   461,   465,   464,   475,
     474,   486,   495,   504,   503,   519,   528,   545,   546,   548,
     554,   553,   575,   576,   581,   587,   593,   596,   599,   602,
     605,   608,   611,   614,   615,   616,   617,   618,   619,   620,
     621,   622,   623,   624,   625,   626,   627,   628,   629,   630,
     631,   632,   633,   634,   635,   636,   637,   638,   639,   640,
     641,   642,   643,   644,   645,   646,   647,   648,   649,   650,
     651,   652,   656,   657,   658,   659,   660,   661,   662,   663,
     664,   665,   666,   667,   668,   669,   670,   671,   672,   673,
     674,   675,   676,   677,   678,   679,   680,   681,   682,   683,
     684,   685,   686,   687,   688,   689,   690,   691,   692,   693,
     694,   698,   699,   706,   709,   710,   717,   720,   721,   724,
     725
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
  "interfaceDeclaration", "@7", "@8", "externproto", "@9", "@10", 
  "externInterfaceDeclarationsORempty", "externInterfaceDeclarations", 
  "externInterfaceDeclaration", "@11", "@12", "@13", "@14", 
  "routeStatement", "@15", "@16", "@17", "URLList", "empty", "node", 
  "@18", "@19", "nodeBodyORempty", "nodeBody", "scriptBodyORempty", 
  "scriptBody", "resInterfaceDeclarationScriptEvent", "@20", "@21", 
  "resInterfaceDeclarationScriptEventEnd", 
  "resInterfaceDeclarationScriptField", "@22", 
  "resInterafceDeclarationScriptFieldEnd", "scriptBodyElement", 
  "nodeBodyElement", "@23", "fieldEnd", "generalId", "nodeNameId", 
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
     123,   124,   125,   123,   127,   128,   126,   129,   129,   130,
     130,   132,   131,   133,   131,   134,   131,   135,   131,   137,
     138,   139,   136,   140,   141,   143,   142,   144,   142,   145,
     145,   146,   146,   147,   147,   148,   148,   150,   149,   151,
     149,   152,   152,   154,   153,   155,   155,   156,   156,   156,
     158,   157,   157,   157,   159,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   168,   168,   168,   168,   168,   168,   168,   168,
     168,   168,   168,   168,   168,   168,   168,   168,   168,   168,
     168,   168,   168,   168,   168,   168,   168,   168,   168,   168,
     168,   168,   168,   168,   168,   168,   168,   168,   168,   168,
     168,   169,   169,   169,   170,   170,   170,   171,   171,   172,
     172
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     0,     4,     2,     1,     0,     4,     1,     1,     1,
       0,     2,     1,     1,     1,     8,     1,     1,     3,     1,
       1,     2,     1,     0,     4,     0,     4,     0,     0,     6,
       1,     0,     0,     6,     0,     0,     8,     1,     1,     2,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       0,     0,    11,     1,     0,     0,     5,     0,     5,     1,
       1,     2,     1,     1,     1,     2,     1,     0,     4,     0,
       4,     2,     0,     0,     4,     2,     1,     1,     2,     2,
       0,     3,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     2,     3,     1,     1,     2,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
      64,     0,     0,     0,    98,     0,     0,    67,     0,     2,
       3,     6,     7,     8,    17,    18,     9,     4,    10,    65,
      97,    11,    13,    59,    24,     0,    23,    44,     0,     1,
       5,     0,     0,     0,    64,     0,    64,    64,    12,     0,
       0,     0,     0,     0,     0,    29,    40,    32,    30,    64,
      99,     0,     0,     0,    93,    92,    74,     0,    73,    82,
       0,    76,    87,    90,    70,     0,    69,    72,   102,    60,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,    33,
      35,    41,    37,     0,    31,     0,     0,     0,     0,     0,
      47,    50,    48,    77,    79,    83,    68,    75,     0,    88,
       0,   142,   143,   144,   145,   146,     0,   148,   149,   150,
     151,   152,   153,   154,   155,     0,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   170,   169,
     171,   172,   173,   174,   175,   176,   177,   180,   178,   179,
      89,    86,     0,    66,    71,     0,     0,     0,     0,     0,
      20,    51,    53,    57,    55,    45,    49,     0,     0,     0,
     100,    81,    85,     0,   183,   181,   147,    64,     0,   184,
     156,     0,    91,    95,     0,   101,    34,    36,    42,    38,
      22,     0,    19,     0,    26,    27,     0,     0,     0,     0,
       0,    78,    80,    84,    96,   182,   190,   188,     0,   187,
     185,    94,    61,     0,     0,     0,    64,    14,    21,    25,
      52,    54,    58,    56,    46,    63,   186,   189,     0,    43,
      39,    15,    28,     0,     0,    62,    16
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     8,     9,    10,    11,    12,    32,   236,   254,    54,
     211,   212,    25,    14,   213,   214,    44,    45,    46,   176,
     177,   179,   234,    47,   178,   233,    15,    35,   220,   119,
     120,   121,   216,   217,   219,   218,    55,    33,   175,   248,
     244,    17,    18,    31,    28,    65,    66,    57,    58,    59,
     187,   188,   129,    60,   189,   170,    61,    62,   172,   202,
     225,    21,    19,    63,   191,   206,    69,   109,   171,   196,
     200,   228,   229
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -168
static const short yypact[] =
{
      34,    18,    18,    18,  -168,    12,    19,  -168,    35,  -168,
      34,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,
    -168,  -168,  -168,  -168,  -168,    45,  -168,  -168,    48,  -168,
    -168,    53,    20,    63,    77,    62,   113,   123,  -168,    65,
     322,   322,   322,   322,    67,    77,  -168,  -168,  -168,   103,
    -168,   322,   322,   322,  -168,  -168,  -168,    78,   113,    75,
     217,  -168,  -168,  -168,  -168,   116,   123,  -168,  -168,  -168,
    -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,
    -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,
    -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,
    -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,
    -168,  -168,  -168,   118,  -168,   322,   322,   322,   322,   122,
     103,  -168,  -168,  -168,  -168,  -168,  -168,  -168,   121,  -168,
     126,  -168,  -168,  -168,  -168,  -168,    21,  -168,  -168,  -168,
    -168,  -168,  -168,  -168,  -168,    56,  -168,  -168,  -168,  -168,
    -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,
    -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,
    -168,  -168,   283,  -168,  -168,   150,   149,    65,   126,   126,
      44,  -168,  -168,  -168,  -168,  -168,  -168,   149,    65,   126,
    -168,  -168,  -168,   151,  -168,  -168,  -168,    69,   151,  -168,
    -168,   151,  -168,  -168,    18,  -168,  -168,  -168,  -168,  -168,
    -168,    23,    74,   153,  -168,  -168,   149,    65,   126,   126,
      76,  -168,  -168,  -168,  -168,  -168,  -168,  -168,   147,    69,
    -168,  -168,  -168,    76,    76,    18,    34,  -168,  -168,  -168,
    -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,   157,  -168,
    -168,  -168,  -168,   149,    20,  -168,  -168
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -168,  -168,   -72,  -168,   155,  -132,  -168,  -168,  -168,     0,
    -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,  -168,
    -168,  -168,  -168,   124,  -168,  -168,  -168,  -168,  -168,  -168,
    -168,    46,  -168,  -168,  -168,  -168,     1,  -168,  -168,  -168,
    -168,   -22,   -30,  -168,  -168,  -168,  -168,  -168,  -168,  -168,
    -168,  -168,  -168,  -168,  -168,  -168,   109,   -16,  -168,  -168,
    -131,     3,    41,  -127,  -168,  -167,  -154,   -34,  -156,  -168,
    -168,  -168,  -168
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -65
static const short yytable[] =
{
      13,    16,    38,   192,   195,    22,    23,   110,   111,   112,
      13,    16,    48,   199,    56,    64,   203,   123,   124,   125,
     221,    67,     4,   207,     1,     2,   235,   122,    20,     4,
       4,     4,    24,     4,   222,    29,   193,     1,     2,     3,
       7,     7,   194,     7,     4,     5,    26,    27,     6,   240,
     174,   208,   209,   -64,     7,     5,    36,    34,     6,     1,
       2,    37,   223,   241,   245,   226,     4,   230,   197,    39,
     231,   198,     1,     2,    49,    68,     7,   249,   250,     4,
     113,   181,   182,   183,   184,     5,   255,   126,     6,     7,
     128,   242,   243,    40,    41,    42,    43,   247,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,     3,   115,
     116,   117,   118,    50,     5,   173,   180,     6,     3,    51,
      52,   190,    53,    50,     5,   185,    50,     6,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   204,   215,   205,
     246,   224,   239,   253,   252,    30,   186,   127,     0,   114,
       0,     0,     0,     0,     0,   227,     0,     0,     0,     0,
     210,   237,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   232,     0,     0,
       0,     0,   238,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   256,     0,     0,     0,     0,     0,
       0,     0,   130,     0,     0,     0,    13,    16,   251,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   201,     0,
       0,     0,     0,     0,     0,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108
};

static const short yycheck[] =
{
       0,     0,    32,   130,   136,     2,     3,    41,    42,    43,
      10,    10,    34,   145,    36,    37,   172,    51,    52,    53,
     187,    37,    10,   177,     3,     4,     3,    49,    10,    10,
      10,    10,    20,    10,   188,     0,    15,     3,     4,     5,
      20,    20,    21,    20,    10,    11,     5,     6,    14,   216,
      66,   178,   179,     9,    20,    11,     8,    12,    14,     3,
       4,     8,   189,   217,   220,   197,    10,   198,    12,     6,
     201,    15,     3,     4,    12,    10,    20,   233,   234,    10,
      13,   115,   116,   117,   118,    11,   253,     9,    14,    20,
      15,   218,   219,    16,    17,    18,    19,   229,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,     5,    16,
      17,    18,    19,    10,    11,     9,     8,    14,     5,    16,
      17,    10,    19,    10,    11,    13,    10,    14,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     7,   180,    10,
      13,    10,     9,     6,   236,    10,   120,    58,    -1,    45,
      -1,    -1,    -1,    -1,    -1,   197,    -1,    -1,    -1,    -1,
     180,   211,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   204,    -1,    -1,
      -1,    -1,   212,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   254,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    15,    -1,    -1,    -1,   236,   236,   235,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,     5,    10,    11,    14,    20,   101,   102,
     103,   104,   105,   109,   113,   126,   136,   141,   142,   162,
      10,   161,   161,   161,    20,   112,   162,   162,   144,     0,
     104,   143,   106,   137,    12,   127,     8,     8,   142,     6,
      16,    17,    18,    19,   116,   117,   118,   123,   141,    12,
      10,    16,    17,    19,   109,   136,   141,   147,   148,   149,
     153,   156,   157,   163,   141,   145,   146,   157,    10,   166,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   167,
     167,   167,   167,    13,   123,    16,    17,    18,    19,   129,
     130,   131,   141,   167,   167,   167,     9,   156,    15,   152,
      15,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
     155,   168,   158,     9,   157,   138,   119,   120,   124,   121,
       8,   167,   167,   167,   167,    13,   131,   150,   151,   154,
      10,   164,   163,    15,    21,   105,   169,    12,    15,   105,
     170,    15,   159,   168,     7,    10,   165,   166,   163,   163,
     109,   110,   111,   114,   115,   141,   132,   133,   135,   134,
     128,   165,   166,   163,    10,   160,   105,   141,   171,   172,
     160,   160,   161,   125,   122,     3,   107,   142,   109,     9,
     165,   166,   163,   163,   140,   168,    13,   105,   139,   168,
     168,   161,   102,     6,   108,   165,   142
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
        case 11:
#line 221 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, SKELTEXT); ;}
    break;

  case 13:
#line 224 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                                  SKEL->use(SKELTEXT); ;}
    break;

  case 15:
#line 230 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, SKELTEXT); ;}
    break;

  case 23:
#line 247 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL) 
                        SKEL->beginProto(SKELTEXT); ;}
    break;

  case 24:
#line 249 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL) 
                        SKEL->beginProto(SKELTEXT); ;}
    break;

  case 25:
#line 260 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL) 
			SKEL->endProto(); ;}
    break;

  case 33:
#line 281 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                      SKELTEXT);;}
    break;

  case 34:
#line 283 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
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

  case 35:
#line 294 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                      SKELTEXT);;}
    break;

  case 36:
#line 296 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
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

  case 37:
#line 307 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                      SKELTEXT);;}
    break;

  case 38:
#line 309 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { expectType(nextType); 
                                              if(SKEL != NULL)
                                               SKEL->beginFieldDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 
                                              freeName(szName1); ;}
    break;

  case 39:
#line 316 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = 0; 
                                              if(SKEL != NULL)
                                               SKEL->endFieldDecl();
                                             ;}
    break;

  case 41:
#line 324 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                              SKELTEXT); ;}
    break;

  case 42:
#line 326 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { expectType(nextType);  
                                      if(SKEL != NULL)
                                       SKEL->beginExposedFieldDecl(
                                        szName1,
                                        nextType,
                                        SKELTEXT); 
                                       freeName(szName1); ;}
    break;

  case 43:
#line 333 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = 0; 
                                      if(SKEL != NULL)
                                       SKEL->endExposedFieldDecl(); ;}
    break;

  case 44:
#line 339 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL) 
                             SKEL->beginExternProto(SKELTEXT); ;}
    break;

  case 45:
#line 344 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                 if(SKEL != NULL) 
                     SKEL->endExternProtoInterface(); 

                 expectType(TOK_MFSTRING); 
              ;}
    break;

  case 46:
#line 351 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                 if(SKEL != NULL) 
                     SKEL->endExternProto(); 
              ;}
    break;

  case 51:
#line 367 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                 SKELTEXT); ;}
    break;

  case 52:
#line 369 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                                               SKEL->addExternEventInDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 
                                         freeName(szName1); ;}
    break;

  case 53:
#line 376 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                 SKELTEXT); ;}
    break;

  case 54:
#line 378 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                                               SKEL->addExternEventOutDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 
                                          freeName(szName1); ;}
    break;

  case 55:
#line 385 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                 SKELTEXT); ;}
    break;

  case 56:
#line 387 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                                               SKEL->addExternFieldDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 
                                         freeName(szName1); ;}
    break;

  case 57:
#line 394 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                 SKELTEXT); ;}
    break;

  case 58:
#line 396 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                                             SKEL->addExternExposedFieldDecl(
                                                 szName1,
                                                 nextType,
                                                 SKELTEXT); 
                                       freeName(szName1); ;}
    break;

  case 59:
#line 405 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, SKELTEXT); ;}
    break;

  case 60:
#line 407 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName2, SKELTEXT); ;}
    break;

  case 61:
#line 409 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName3, SKELTEXT); ;}
    break;

  case 62:
#line 411 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
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

  case 65:
#line 428 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                     SKEL->beginNode(SKELTEXT, szName1); 

                    freeName(szName1);
                  ;}
    break;

  case 66:
#line 435 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                     SKEL->endNode(); ;}
    break;

  case 67:
#line 437 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                     SKEL->beginNode(SKELTEXT, szName1); 

                    freeName(szName1);
                  ;}
    break;

  case 68:
#line 444 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                     SKEL->endNode(); ;}
    break;

  case 77:
#line 465 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                          SKELTEXT); ;}
    break;

  case 78:
#line 467 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                                                     SKEL->beginEventInDecl(
                                                       szName1,
                                                       nextType,
                                                       SKELTEXT); 

                                                 freeName(szName1); ;}
    break;

  case 79:
#line 475 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                          SKELTEXT); ;}
    break;

  case 80:
#line 477 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                                                     SKEL->beginEventOutDecl(
                                                       szName1,
                                                       nextType,
                                                       SKELTEXT); 

                                                  freeName(szName1); ;}
    break;

  case 81:
#line 487 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { 
                                          if(SKEL != NULL)
                                          {
                                             SKEL->is(SKELTEXT);
                                             SKEL->endEventDecl(); 
                                          }
                                        ;}
    break;

  case 82:
#line 495 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { 
                                            if(SKEL != NULL)
                                            {
                                                SKEL->endEventDecl(); 
                                            }
                                        ;}
    break;

  case 83:
#line 504 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { setName(szName1, 
                                                         SKELTEXT);
                                               ;}
    break;

  case 84:
#line 507 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { expectType(nextType); 
                                              
                                                 if(SKEL != NULL)
                                                     SKEL->beginFieldDecl(
                                                       szName1,
                                                       nextType,
                                                       SKELTEXT); 
                                              
                                                 freeName(szName1);
                                               ;}
    break;

  case 85:
#line 519 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = 0; 

                                                     if(SKEL != NULL)
                                                     {
                                                       SKEL->is(SKELTEXT);

                                                       SKEL->endFieldDecl();
                                                     }
                                                   ;}
    break;

  case 86:
#line 528 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = 0; 

                                                     if(SKEL != NULL)
                                                       SKEL->endFieldDecl();

                                                   ;}
    break;

  case 90:
#line 554 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
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

  case 94:
#line 581 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                          {
                            SKEL->is(SKELTEXT);
                            SKEL->endField();
                          }
                        ;}
    break;

  case 95:
#line 587 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { if(SKEL != NULL)
                            SKEL->endField();
                        ;}
    break;

  case 103:
#line 614 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFCOLOR;    ;}
    break;

  case 104:
#line 615 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFFLOAT;    ;}
    break;

  case 105:
#line 616 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFINT32;    ;}
    break;

  case 106:
#line 617 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFNODE;     ;}
    break;

  case 107:
#line 618 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFROTATION; ;}
    break;

  case 108:
#line 619 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFSTRING;   ;}
    break;

  case 109:
#line 620 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFTIME;     ;}
    break;

  case 110:
#line 621 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFVEC2F;    ;}
    break;

  case 111:
#line 622 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFVEC3F;    ;}
    break;

  case 112:
#line 623 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFBOOL;     ;}
    break;

  case 113:
#line 624 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFCOLOR;    ;}
    break;

  case 114:
#line 625 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFFLOAT;    ;}
    break;

  case 115:
#line 626 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFIMAGE;    ;}
    break;

  case 116:
#line 627 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFINT32;    ;}
    break;

  case 117:
#line 628 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFNODE;     ;}
    break;

  case 118:
#line 629 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFROTATION; ;}
    break;

  case 119:
#line 630 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFSTRING;   ;}
    break;

  case 120:
#line 631 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFTIME;     ;}
    break;

  case 121:
#line 632 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFVEC2F;    ;}
    break;

  case 122:
#line 633 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFVEC3F;    ;}
    break;

  case 123:
#line 634 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFCOLOR4F;  ;}
    break;

  case 124:
#line 635 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFCOLOR4I;  ;}
    break;

  case 125:
#line 636 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFCOLOR3F;  ;}
    break;

  case 126:
#line 637 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFMATRIX;   ;}
    break;

  case 127:
#line 638 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFPNT2F;    ;}
    break;

  case 128:
#line 639 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFPNT3F;    ;}
    break;

  case 129:
#line 640 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFPNT4F;    ;}
    break;

  case 130:
#line 641 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFVEC4F;    ;}
    break;

  case 131:
#line 642 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_MFPLANE;    ;}
    break;

  case 132:
#line 643 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFCOLOR4F;  ;}
    break;

  case 133:
#line 644 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFCOLOR4I;  ;}
    break;

  case 134:
#line 645 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFCOLOR3F;  ;}
    break;

  case 135:
#line 646 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFMATRIX;   ;}
    break;

  case 136:
#line 647 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFPNT2F;    ;}
    break;

  case 137:
#line 648 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFPNT3F;    ;}
    break;

  case 138:
#line 649 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFPNT4F;    ;}
    break;

  case 139:
#line 650 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFVEC4F;    ;}
    break;

  case 140:
#line 651 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFPLANE;    ;}
    break;

  case 141:
#line 652 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    { nextType = TOK_SFVOLUME;   ;}
    break;

  case 182:
#line 700 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                  if(SKEL != NULL)
                  {
                      SKEL->is(SKELTEXT);
                  }
              ;}
    break;

  case 185:
#line 711 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
    {
                  if(SKEL != NULL)
                  {
                      SKEL->is(SKELTEXT);
                  }
              ;}
    break;


    }

/* Line 999 of yacc.c.  */
#line 2182 "OSGScanParseSkel_.tab.c"

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


#line 729 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"


extern void setSkel    (ScanParseSkel *pSkel);
extern void clearSkel  (void);

void OSGScanParseSkel_error (char *s)  /* Called by fhs_parse on error */
{
  printf ("-----> %s in Line %d\n", s, iLineNum);
//, 
//          SKELTEXT);
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

