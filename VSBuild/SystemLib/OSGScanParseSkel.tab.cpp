
/* A Bison parser, made from ../../Loader/ScanParseSkel/OSGScanParseSkel.y
   by GNU bison 1.30.  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse OSGScanParseSkel_parse
#define yylex OSGScanParseSkel_lex
#define yyerror OSGScanParseSkel_error
#define yylval OSGScanParseSkel_lval
#define yychar OSGScanParseSkel_char
#define yydebug OSGScanParseSkel_debug
#define yynerrs OSGScanParseSkel_nerrs
# define	DEF	257
# define	USE	258
# define	ROUTE	259
# define	PERIOD	260
# define	TO	261
# define	OPENBRACE	262
# define	CLOSEBRACE	263
# define	ID	264
# define	PROTO	265
# define	OPENBRACKET	266
# define	CLOSEBRACKET	267
# define	EXTERNPROTO	268
# define	IS	269
# define	EVENTIN	270
# define	EVENTOUT	271
# define	EXPOSEDFIELD	272
# define	FIELD	273
# define	SCRIPT	274
# define	SFN_NULL	275
# define	TOK_SFBOOL	276
# define	TOK_SFCOLOR	277
# define	TOK_SFFLOAT	278
# define	TOK_SFIMAGE	279
# define	TOK_SFINT32	280
# define	TOK_SFNODE	281
# define	TOK_SFROTATION	282
# define	TOK_SFSTRING	283
# define	TOK_SFTIME	284
# define	TOK_SFVEC2F	285
# define	TOK_SFVEC3F	286
# define	TOK_MFCOLOR	287
# define	TOK_MFFLOAT	288
# define	TOK_MFINT32	289
# define	TOK_MFNODE	290
# define	TOK_MFROTATION	291
# define	TOK_MFSTRING	292
# define	TOK_MFTIME	293
# define	TOK_MFVEC2F	294
# define	TOK_MFVEC3F	295
# define	Tok_MFColor	296
# define	Tok_MFFloat	297
# define	Tok_MFInt32	298
# define	Tok_MFNode	299
# define	Tok_MFRotation	300
# define	Tok_MFString	301
# define	Tok_MFTime	302
# define	Tok_MFVec2f	303
# define	Tok_MFVec3f	304
# define	Tok_SFBool	305
# define	Tok_SFColor	306
# define	Tok_SFFloat	307
# define	Tok_SFImage	308
# define	Tok_SFInt32	309
# define	Tok_SFNode	310
# define	Tok_SFRotation	311
# define	Tok_SFString	312
# define	Tok_SFTime	313
# define	Tok_SFVec2f	314
# define	Tok_SFVec3f	315
# define	TOK_MFCOLOR4F	316
# define	TOK_MFCOLOR3F	317
# define	TOK_MFMATRIX	318
# define	TOK_MFPNT2F	319
# define	TOK_MFPNT3F	320
# define	TOK_MFPNT4F	321
# define	TOK_MFVEC4F	322
# define	TOK_MFPLANE	323
# define	TOK_SFCOLOR4F	324
# define	TOK_SFCOLOR3F	325
# define	TOK_SFMATRIX	326
# define	TOK_SFPNT2F	327
# define	TOK_SFPNT3F	328
# define	TOK_SFPNT4F	329
# define	TOK_SFVEC4F	330
# define	TOK_SFPLANE	331
# define	Tok_MFColor4f	332
# define	Tok_MFColor3f	333
# define	Tok_MFMatrix	334
# define	Tok_MFPnt2f	335
# define	Tok_MFPnt3f	336
# define	Tok_MFPnt4f	337
# define	Tok_MFVec4f	338
# define	Tok_MFPlane	339
# define	Tok_SFColor4f	340
# define	Tok_SFColor3f	341
# define	Tok_SFMatrix	342
# define	Tok_SFPnt2f	343
# define	Tok_SFPnt3f	344
# define	Tok_SFPnt4f	345
# define	Tok_SFVec4f	346
# define	Tok_SFPlane	347

#line 38 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"


#ifdef WIN32
#include <malloc.h>
#endif
#include <OSGScanParseSkel.tab.h>
#include <OSGConfig.h>

#include <OSGBaseFunctions.h>
#include <OSGScanParseSkel.h>
#include <stack>

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

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#include <stdio.h>



#define	YYFINAL		242
#define	YYFLAG		-32768
#define	YYNTBASE	94

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 347 ? yytranslate[x] : 161)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
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
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93
};

#if YYDEBUG != 0
static const short yyprhs[] =
{
       0,     0,     2,     4,     6,     9,    11,    13,    15,    17,
      19,    20,    25,    28,    30,    31,    36,    38,    40,    42,
      43,    46,    48,    50,    52,    53,    63,    65,    67,    71,
      73,    75,    78,    80,    81,    86,    87,    92,    93,    94,
     101,   103,   104,   105,   112,   119,   121,   123,   126,   128,
     132,   136,   140,   144,   145,   146,   147,   159,   161,   162,
     163,   169,   170,   176,   178,   180,   183,   185,   187,   189,
     192,   194,   195,   200,   201,   206,   209,   210,   211,   216,
     219,   221,   223,   226,   229,   230,   234,   236,   238,   241,
     243,   245,   247,   249,   251,   253,   255,   257,   259,   261,
     263,   265,   267,   269,   271,   273,   275,   277,   279,   281,
     283,   285,   287,   289,   291,   293,   295,   297,   299,   301,
     303,   305,   307,   309,   311,   313,   315,   317,   319,   321,
     323,   325,   327,   329,   331,   333,   335,   337,   339,   342,
     344,   346,   348,   350,   352,   354,   356,   358,   361,   363,
     365,   367,   369,   371,   373,   375,   377,   379,   381,   383,
     385,   387,   389,   391,   393,   395,   397,   399,   401,   403,
     405,   407,   409,   413,   415,   417,   420
};
static const short yyrhs[] =
{
      95,     0,    96,     0,   129,     0,    96,    97,     0,    97,
       0,    98,     0,   102,     0,   124,     0,   130,     0,     0,
       3,   149,    99,   130,     0,     4,   149,     0,   130,     0,
       0,     3,   149,   101,   130,     0,   106,     0,   120,     0,
     104,     0,     0,   104,   102,     0,   102,     0,   150,     0,
      20,     0,     0,    11,   105,    12,   110,    13,   107,     8,
     108,     9,     0,   109,     0,   129,     0,   103,   100,    95,
       0,   111,     0,   129,     0,   111,   117,     0,   117,     0,
       0,    16,   155,   113,   153,     0,     0,    17,   155,   114,
     154,     0,     0,     0,    19,   155,   115,   151,   116,   156,
       0,   112,     0,     0,     0,    18,   155,   118,   151,   119,
     156,     0,    14,   150,    12,   121,    13,   128,     0,   122,
       0,   129,     0,   122,   123,     0,   123,     0,    16,   155,
     153,     0,    17,   155,   154,     0,    19,   155,   151,     0,
      18,   155,   151,     0,     0,     0,     0,     5,   149,   125,
       6,   154,   126,     7,   149,   127,     6,   153,     0,   156,
       0,     0,     0,   150,   131,     8,   133,     9,     0,     0,
      20,   132,     8,   135,     9,     0,   134,     0,   129,     0,
     134,   145,     0,   145,     0,   136,     0,   129,     0,   136,
     144,     0,   144,     0,     0,    16,   155,   138,   153,     0,
       0,    17,   155,   139,   154,     0,    15,   152,     0,     0,
       0,    19,   155,   142,   151,     0,    15,   151,     0,   156,
       0,   145,     0,   137,   140,     0,   141,   143,     0,     0,
     151,   146,   147,     0,   124,     0,   102,     0,    15,   148,
       0,   156,     0,    10,     0,    10,     0,    10,     0,    10,
       0,    10,     0,    10,     0,    10,     0,    42,     0,    43,
       0,    44,     0,    45,     0,    46,     0,    47,     0,    48,
       0,    49,     0,    50,     0,    51,     0,    52,     0,    53,
       0,    54,     0,    55,     0,    56,     0,    57,     0,    58,
       0,    59,     0,    60,     0,    61,     0,    78,     0,    79,
       0,    80,     0,    81,     0,    82,     0,    83,     0,    84,
       0,    85,     0,    86,     0,    87,     0,    88,     0,    89,
       0,    90,     0,    91,     0,    92,     0,    93,     0,    22,
       0,    23,     0,    24,     0,    25,     0,    26,     0,    27,
     157,     0,    28,     0,    29,     0,    30,     0,    31,     0,
      32,     0,    33,     0,    34,     0,    35,     0,    36,   158,
       0,    37,     0,    38,     0,    39,     0,    40,     0,    41,
       0,    62,     0,    63,     0,    64,     0,    65,     0,    66,
       0,    67,     0,    69,     0,    68,     0,    70,     0,    71,
       0,    72,     0,    73,     0,    74,     0,    75,     0,    77,
       0,    76,     0,    98,     0,    21,     0,    98,     0,    12,
     159,    13,     0,   160,     0,   129,     0,   160,    98,     0,
      98,     0
};

#endif

#if YYDEBUG != 0
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   181,   184,   185,   188,   189,   192,   193,   194,   197,
     198,   201,   201,   206,   207,   210,   212,   213,   217,   218,
     221,   222,   225,   227,   230,   237,   241,   242,   245,   248,
     249,   252,   253,   257,   260,   265,   268,   273,   276,   283,
     289,   290,   293,   300,   305,   313,   314,   317,   319,   322,
     323,   324,   325,   328,   331,   333,   335,   346,   349,   352,
     358,   361,   367,   372,   373,   376,   377,   380,   381,   384,
     385,   388,   391,   397,   400,   408,   409,   412,   416,   428,
     438,   455,   456,   458,   463,   486,   486,   487,   492,   498,
     504,   507,   510,   513,   516,   519,   522,   525,   526,   527,
     528,   529,   530,   531,   532,   533,   534,   535,   536,   537,
     538,   539,   540,   541,   542,   543,   544,   545,   546,   547,
     548,   549,   550,   551,   552,   553,   554,   555,   556,   557,
     558,   559,   560,   564,   565,   566,   567,   568,   569,   570,
     571,   572,   573,   574,   575,   576,   577,   578,   579,   580,
     581,   582,   583,   584,   585,   586,   587,   588,   589,   590,
     591,   592,   593,   594,   595,   596,   597,   598,   599,   603,
     604,   607,   608,   611,   612,   615,   616
};
#endif


#if YYDEBUG != 0 || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "DEF", "USE", "ROUTE", "PERIOD", "TO", 
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
  "Tok_SFVec3f", "TOK_MFCOLOR4F", "TOK_MFCOLOR3F", "TOK_MFMATRIX", 
  "TOK_MFPNT2F", "TOK_MFPNT3F", "TOK_MFPNT4F", "TOK_MFVEC4F", 
  "TOK_MFPLANE", "TOK_SFCOLOR4F", "TOK_SFCOLOR3F", "TOK_SFMATRIX", 
  "TOK_SFPNT2F", "TOK_SFPNT3F", "TOK_SFPNT4F", "TOK_SFVEC4F", 
  "TOK_SFPLANE", "Tok_MFColor4f", "Tok_MFColor3f", "Tok_MFMatrix", 
  "Tok_MFPnt2f", "Tok_MFPnt3f", "Tok_MFPnt4f", "Tok_MFVec4f", 
  "Tok_MFPlane", "Tok_SFColor4f", "Tok_SFColor3f", "Tok_SFMatrix", 
  "Tok_SFPnt2f", "Tok_SFPnt3f", "Tok_SFPnt4f", "Tok_SFVec4f", 
  "Tok_SFPlane", "vrmlScene", "statementsORempty", "statements", 
  "statement", "nodeStatement", "@1", "rootNodeStatement", "@2", 
  "protoStatement", "protoStatementsORempty", "protoStatements", 
  "protoId", "proto", "@3", "protoBodyORempty", "protoBody", 
  "interfaceDeclarationsORempty", "interfaceDeclarations", 
  "restrictedInterfaceDeclaration", "@4", "@5", "@6", "@7", 
  "interfaceDeclaration", "@8", "@9", "externproto", 
  "externInterfaceDeclarationsORempty", "externInterfaceDeclarations", 
  "externInterfaceDeclaration", "routeStatement", "@10", "@11", "@12", 
  "URLList", "empty", "node", "@13", "@14", "nodeBodyORempty", "nodeBody", 
  "scriptBodyORempty", "scriptBody", "resInterfaceDeclarationScriptEvent", 
  "@15", "@16", "resInterfaceDeclarationScriptEventEnd", 
  "resInterfaceDeclarationScriptField", "@17", 
  "resInterafceDeclarationScriptFieldEnd", "scriptBodyElement", 
  "nodeBodyElement", "@18", "fieldEnd", "generalId", "nodeNameId", 
  "nodeTypeId", "fieldId", "eventId", "eventInId", "eventOutId", 
  "fieldType", "fieldValue", "sfnodeValue", "mfnodeValue", 
  "nodeStatementsORempty", "nodeStatements", NULL
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    94,    95,    95,    96,    96,    97,    97,    97,    98,
      99,    98,    98,   100,   101,   100,   102,   102,   103,   103,
     104,   104,   105,   105,   107,   106,   108,   108,   109,   110,
     110,   111,   111,   113,   112,   114,   112,   115,   116,   112,
     117,   118,   119,   117,   120,   121,   121,   122,   122,   123,
     123,   123,   123,   125,   126,   127,   124,   128,   129,   131,
     130,   132,   130,   133,   133,   134,   134,   135,   135,   136,
     136,   138,   137,   139,   137,   140,   140,   142,   141,   143,
     143,   144,   144,   144,   146,   145,   145,   145,   147,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   157,
     157,   158,   158,   159,   159,   160,   160
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       0,     4,     2,     1,     0,     4,     1,     1,     1,     0,
       2,     1,     1,     1,     0,     9,     1,     1,     3,     1,
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
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     2,     1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
      58,     0,     0,     0,    92,     0,     0,    61,     1,     2,
       5,     6,     7,    16,    17,     8,     3,     9,    59,    91,
      10,    12,    53,    23,     0,    22,     0,     0,     4,     0,
       0,     0,    58,    58,    58,    58,    11,     0,     0,     0,
       0,     0,     0,    29,    40,    32,    30,     0,     0,     0,
       0,     0,    45,    48,    46,    93,     0,     0,     0,    87,
      86,    68,     0,    67,    76,     0,    70,    81,    84,    64,
       0,    63,    66,    96,    54,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,    33,    35,    41,    37,    24,    31,     0,     0,     0,
       0,     0,    47,    71,    73,    77,    62,    69,     0,    82,
       0,   133,   134,   135,   136,   137,     0,   139,   140,   141,
     142,   143,   144,   145,   146,     0,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   160,   159,   161,
     162,   163,   164,   165,   166,   168,   167,    83,    80,     0,
      60,    65,     0,     0,     0,     0,     0,     0,    95,    49,
      50,    52,    51,    44,    57,     0,     0,     0,    94,    75,
      79,   170,   169,   138,    58,   171,   147,     0,    85,    89,
       0,    34,    36,    42,    38,    19,    72,    74,    78,   176,
     174,     0,   173,    90,    88,    55,     0,     0,    21,     0,
      18,     0,    26,    27,   172,   175,     0,    43,    39,     0,
      58,    13,    20,    25,     0,    14,    28,    56,     0,    15,
       0,     0,     0
};

static const short yydefgoto[] =
{
     240,     8,     9,    10,    11,    30,   230,   238,    59,   219,
     220,    24,    13,   177,   221,   222,    42,    43,    44,   173,
     174,   176,   217,    45,   175,   216,    14,    51,    52,    53,
      60,    31,   172,   226,   183,    16,    17,    29,    27,    70,
      71,    62,    63,    64,   185,   186,   129,    65,   187,   167,
      66,    67,   169,   198,   214,    20,    18,    68,   189,   179,
      74,   111,   168,   193,   196,   211,   212
};

static const short yypact[] =
{
      42,    27,    27,    27,-32768,     5,    39,-32768,-32768,    42,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,    45,-32768,    47,    58,-32768,    59,
      14,    62,   105,   119,   115,    76,-32768,    66,   267,   267,
     267,   267,    71,   105,-32768,-32768,-32768,   267,   267,   267,
     267,    75,   119,-32768,-32768,-32768,   267,   267,   267,-32768,
  -32768,-32768,    80,   115,    77,    78,-32768,-32768,-32768,-32768,
      82,    76,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,    84,    66,    85,
      85,   231,-32768,-32768,-32768,-32768,-32768,-32768,    86,-32768,
      85,-32768,-32768,-32768,-32768,-32768,    23,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,    38,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   211,
  -32768,-32768,    90,    84,    66,    85,    85,   120,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,    84,    66,    85,-32768,-32768,
  -32768,-32768,-32768,-32768,    60,-32768,-32768,   117,-32768,-32768,
      27,-32768,-32768,-32768,-32768,    68,-32768,-32768,-32768,-32768,
  -32768,   126,    60,-32768,-32768,-32768,   231,   231,-32768,    51,
      64,   121,-32768,-32768,-32768,-32768,   127,-32768,-32768,    27,
      42,-32768,-32768,-32768,    84,-32768,-32768,-32768,    14,-32768,
     156,   157,-32768
};

static const short yypgoto[] =
{
  -32768,   -72,-32768,   150,  -129,-32768,-32768,-32768,     0,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,   118,-32768,-32768,-32768,-32768,-32768,   108,
       1,-32768,-32768,-32768,-32768,   -21,   -28,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
      99,   -16,-32768,-32768,-32768,     3,    30,  -102,-32768,  -165,
    -114,   -18,  -118,-32768,-32768,-32768,-32768
};


#define	YYLAST		360


static const short yytable[] =
{
      12,    15,    36,   184,   180,    21,    22,   192,   201,    12,
      15,    46,    54,    61,    69,     4,   195,   181,   182,    72,
     206,   112,   113,   114,     4,    23,     1,     2,   190,   117,
     118,   119,   120,     4,     7,    25,    26,    19,   123,   124,
     125,     1,     2,     7,   191,     1,     2,     3,     4,     4,
     194,   199,     4,     5,   229,   171,     6,    32,     7,    33,
     202,     4,     7,     1,     2,   209,    34,    35,    37,   237,
       4,     7,   207,   203,   204,     5,    73,   -58,     6,     5,
       7,     3,     6,   225,   115,   208,    55,     5,   121,   126,
       6,   170,   128,   130,   178,    55,   188,   200,   227,   228,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
       3,    38,    39,    40,    41,    55,     5,   213,   205,     6,
     233,    56,    57,   234,    58,    47,    48,    49,    50,   224,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   241,   242,   236,    28,
     122,   116,   127,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   210,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   223,     0,     0,     0,     0,     0,
       0,   231,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   215,     0,   218,     0,     0,     0,     0,
     239,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     232,     0,     0,     0,     0,     0,   197,     0,     0,     0,
      12,    15,   235,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,     0,
       0,     0,     0,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110
};

static const short yycheck[] =
{
       0,     0,    30,   121,   118,     2,     3,   136,   173,     9,
       9,    32,    33,    34,    35,    10,   145,   119,   120,    35,
     185,    39,    40,    41,    10,    20,     3,     4,   130,    47,
      48,    49,    50,    10,    20,     5,     6,    10,    56,    57,
      58,     3,     4,    20,    21,     3,     4,     5,    10,    10,
      12,   169,    10,    11,     3,    71,    14,    12,    20,    12,
     174,    10,    20,     3,     4,   194,     8,     8,     6,   234,
      10,    20,   186,   175,   176,    11,    10,     9,    14,    11,
      20,     5,    14,   212,    13,   187,    10,    11,    13,     9,
      14,     9,    15,    15,    10,    10,    10,     7,   216,   217,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
       5,    16,    17,    18,    19,    10,    11,    10,     8,    14,
       9,    16,    17,     6,    19,    16,    17,    18,    19,    13,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,     0,     0,   230,     9,
      52,    43,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   194,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   205,    -1,    -1,    -1,    -1,    -1,
      -1,   219,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   200,    -1,   205,    -1,    -1,    -1,    -1,
     238,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     220,    -1,    -1,    -1,    -1,    -1,    15,    -1,    -1,    -1,
     230,   230,   229,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    -1,
      -1,    -1,    -1,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,
   Copyright 1984, 1989, 1990, 2000, 2001 Free Software Foundation, Inc.

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

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
# ifdef alloca
#  define YYSTACK_USE_ALLOCA 1
# else /* alloca not defined */
#  ifdef __GNUC__
#   define YYSTACK_USE_ALLOCA 1
#   define alloca __builtin_alloca
#  else /* not GNU C.  */
#   if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#    define YYSTACK_USE_ALLOCA 1
#    include <alloca.h>
#   else /* not sparc */
     /* We think this test detects Watcom and Microsoft C.  */
     /* This used to test MSDOS, but that is a bad idea since that
	symbol is in the user namespace.  */
#    if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#     if 0
       /* No need for malloc.h, which pollutes the namespace; instead,
	  just don't use alloca.  */
#      include <malloc.h>
#     endif
#    else /* not MSDOS, or __TURBOC__ */
#     if defined(_AIX)
       /* I don't know what this was needed for, but it pollutes the
	  namespace.  So I turned it off.  rms, 2 May 1997.  */
       /* #include <malloc.h>  */
 #pragma alloca
#      define YYSTACK_USE_ALLOCA 1
#     else /* not MSDOS, or __TURBOC__, or _AIX */
#      if 0
	/* haible@ilog.fr says this works for HPUX 9.05 and up, and on
	   HPUX 10.  Eventually we can turn this on.  */
#       ifdef __hpux
#        define YYSTACK_USE_ALLOCA 1
#        define alloca __builtin_alloca
#  	endif /* __hpux */
#      endif
#     endif /* not _AIX */
#    endif /* not MSDOS, or __TURBOC__ */
#   endif /* not sparc */
#  endif /* not GNU C */
# endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#ifndef YYSTACK_USE_ALLOCA
# define YYSTACK_USE_ALLOCA 0
#endif

#if YYSTACK_USE_ALLOCA
# define YYSTACK_ALLOC alloca
#else
# define YYSTACK_ALLOC malloc
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
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
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


/* Enable debugging if requested.  */
#if YYDEBUG
# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    fprintf Args;				\
} while (0)
/* Nonzero means print parse trace. [The following comment makes no
   sense to me.  Could someone clarify it?  --akim] Since this is
   uninitialized, it does not stop multiple parsers from coexisting.
   */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).  */
#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Define __yy_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
# define __yy_memcpy(To, From, Count)	__builtin_memcpy (To, From, Count)
#else				/* not GNU C or C++ */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
# ifndef __cplusplus
__yy_memcpy (to, from, count)
     char *to;
     const char *from;
     unsigned int count;
# else /* __cplusplus */
__yy_memcpy (char *to, const char *from, unsigned int count)
# endif
{
  register const char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif

#line 216 "/usr/share/bison/bison.simple"


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# ifdef __cplusplus
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else /* !__cplusplus */
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif /* !__cplusplus */
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

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define _YY_DECL_VARIABLES				\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
_YY_DECL_VARIABLES				\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
_YY_DECL_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

  register int yystate;
  register int yyn;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yysv': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;
  int yyfree_stacks = 0;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
# if YYLSP_NEEDED
  YYLTYPE yyloc;
# endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
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
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
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
      /* Give user a chance to reallocate the stack. Use copies of
	 these so that the &'s don't force the real ones into memory.
	 */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#if YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of the
	 data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow ("parser stack overflow",
		  &yyss1, size * sizeof (*yyssp),
		  &yyvs1, size * sizeof (*yyvsp),
		  &yyls1, size * sizeof (*yylsp),
		  &yystacksize);
# else
      yyoverflow ("parser stack overflow",
		  &yyss1, size * sizeof (*yyssp),
		  &yyvs1, size * sizeof (*yyvsp),
		  &yystacksize);
# endif

      yyss = yyss1; yyvs = yyvs1;
# if YYLSP_NEEDED
      yyls = yyls1;
# endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror ("parser stack overflow");
	  if (yyfree_stacks)
	    {
	      free (yyss);
	      free (yyvs);
# if YYLSP_NEEDED
	      free (yyls);
# endif
	    }
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
# if !YYSTACK_USE_ALLOCA
      yyfree_stacks = 1;
# endif
      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1,
		   size * (unsigned int) sizeof (*yyssp));
      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
		   size * (unsigned int) sizeof (*yyvsp));
# if YYLSP_NEEDED
      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1,
		   size * (unsigned int) sizeof (*yylsp));
# endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#if YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %d\n", yystacksize));

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
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

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

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 10:
#line 199 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, OSGScanParseSkel_text); ;
    break;}
case 12:
#line 202 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                                  _pSkel->use(OSGScanParseSkel_text); ;
    break;}
case 14:
#line 208 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, OSGScanParseSkel_text); ;
    break;}
case 22:
#line 225 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL) 
                        _pSkel->beginProto(OSGScanParseSkel_text); ;
    break;}
case 23:
#line 227 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL) 
                        _pSkel->beginProto(OSGScanParseSkel_text); ;
    break;}
case 24:
#line 234 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL) 
                        _pSkel->endProto(); ;
    break;}
case 33:
#line 258 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                      OSGScanParseSkel_text); ;
    break;}
case 34:
#line 260 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                                               _pSkel->addEventInDecl(
                                                szName1,
                                                OSGScanParseSkel_text); 
                                              freeName(szName1); ;
    break;}
case 35:
#line 266 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                      OSGScanParseSkel_text); ;
    break;}
case 36:
#line 268 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                                               _pSkel->addEventOutDecl(
                                                szName1,
                                                OSGScanParseSkel_text); 
                                              freeName(szName1); ;
    break;}
case 37:
#line 274 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                      OSGScanParseSkel_text); ;
    break;}
case 38:
#line 276 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ expectType(nextType); 
                                              if(_pSkel != NULL)
                                               _pSkel->beginFieldDecl(
                                                szName1,
                                                nextType,
                                                OSGScanParseSkel_text); 
                                              freeName(szName1); ;
    break;}
case 39:
#line 283 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = 0; 
                                              if(_pSkel != NULL)
                                               _pSkel->endFieldDecl();
                                             ;
    break;}
case 41:
#line 291 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                              OSGScanParseSkel_text); ;
    break;}
case 42:
#line 293 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ expectType(nextType);  
                                      if(_pSkel != NULL)
                                       _pSkel->beginExposedFieldDecl(
                                        szName1,
                                        nextType,
                                        OSGScanParseSkel_text); 
                                       freeName(szName1); ;
    break;}
case 43:
#line 300 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = 0; 
                                      if(_pSkel != NULL)
                                       _pSkel->endExposedFieldDecl(); ;
    break;}
case 53:
#line 329 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, OSGScanParseSkel_text); ;
    break;}
case 54:
#line 331 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName2, OSGScanParseSkel_text); ;
    break;}
case 55:
#line 333 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName3, OSGScanParseSkel_text); ;
    break;}
case 56:
#line 335 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                                _pSkel->addRoute(szName1, 
                                                 szName2,
                                                 szName3,
                                                 OSGScanParseSkel_text);
                              freeName(szName1);
                              freeName(szName2);
                              freeName(szName3);
                            ;
    break;}
case 59:
#line 352 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                     _pSkel->beginNode(OSGScanParseSkel_text, szName1); 

                    freeName(szName1);
                  ;
    break;}
case 60:
#line 359 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                     _pSkel->endNode(); ;
    break;}
case 61:
#line 361 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                     _pSkel->beginNode(OSGScanParseSkel_text, szName1); 

                    freeName(szName1);
                  ;
    break;}
case 62:
#line 368 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                     _pSkel->endNode(); ;
    break;}
case 71:
#line 389 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                     OSGScanParseSkel_text); ;
    break;}
case 72:
#line 391 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                                                     _pSkel->addEventInDecl(
                                                       szName1,
                                                       OSGScanParseSkel_text); 

                                                 freeName(szName1); ;
    break;}
case 73:
#line 398 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                      OSGScanParseSkel_text); ;
    break;}
case 74:
#line 400 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                                                     _pSkel->addEventOutDecl(
                                                       szName1,
                                                       OSGScanParseSkel_text); 

                                                  freeName(szName1); ;
    break;}
case 77:
#line 413 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                        OSGScanParseSkel_text);
                                               ;
    break;}
case 78:
#line 416 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ expectType(nextType); 
                                              
                                                 if(_pSkel != NULL)
                                                     _pSkel->beginFieldDecl(
                                                       szName1,
                                                       nextType,
                                                       OSGScanParseSkel_text); 
                                              
                                                 freeName(szName1);
                                               ;
    break;}
case 79:
#line 428 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = 0; 

                                                     if(_pSkel != NULL)
                                                     {
                                                       _pSkel->is(
                                                        OSGScanParseSkel_text);

                                                       _pSkel->endFieldDecl();
                                                     }
                                                   ;
    break;}
case 80:
#line 438 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = 0; 

                                                     if(_pSkel != NULL)
                                                       _pSkel->endFieldDecl();

                                                   ;
    break;}
case 84:
#line 464 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
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
                   ;
    break;}
case 88:
#line 492 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                          {
                            _pSkel->is(OSGScanParseSkel_text);
                            _pSkel->endField();
                          }
                        ;
    break;}
case 89:
#line 498 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                            _pSkel->endField();
                        ;
    break;}
case 97:
#line 525 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFCOLOR;    ;
    break;}
case 98:
#line 526 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFFLOAT;    ;
    break;}
case 99:
#line 527 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFINT32;    ;
    break;}
case 100:
#line 528 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFNODE;     ;
    break;}
case 101:
#line 529 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFROTATION; ;
    break;}
case 102:
#line 530 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFSTRING;   ;
    break;}
case 103:
#line 531 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFTIME;     ;
    break;}
case 104:
#line 532 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFVEC2F;    ;
    break;}
case 105:
#line 533 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFVEC3F;    ;
    break;}
case 106:
#line 534 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFBOOL;     ;
    break;}
case 107:
#line 535 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFCOLOR;    ;
    break;}
case 108:
#line 536 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFFLOAT;    ;
    break;}
case 109:
#line 537 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFIMAGE;    ;
    break;}
case 110:
#line 538 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFINT32;    ;
    break;}
case 111:
#line 539 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFNODE;     ;
    break;}
case 112:
#line 540 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFROTATION; ;
    break;}
case 113:
#line 541 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFSTRING;   ;
    break;}
case 114:
#line 542 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFTIME;     ;
    break;}
case 115:
#line 543 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFVEC2F;    ;
    break;}
case 116:
#line 544 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFVEC3F;    ;
    break;}
case 117:
#line 545 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFCOLOR4F;  ;
    break;}
case 118:
#line 546 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFCOLOR3F;  ;
    break;}
case 119:
#line 547 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFMATRIX;   ;
    break;}
case 120:
#line 548 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFPNT2F;    ;
    break;}
case 121:
#line 549 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFPNT3F;    ;
    break;}
case 122:
#line 550 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFPNT4F;    ;
    break;}
case 123:
#line 551 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFVEC4F;    ;
    break;}
case 124:
#line 552 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFPLANE;    ;
    break;}
case 125:
#line 553 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFCOLOR4F;  ;
    break;}
case 126:
#line 554 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFCOLOR3F;  ;
    break;}
case 127:
#line 555 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFMATRIX;   ;
    break;}
case 128:
#line 556 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFPNT2F;    ;
    break;}
case 129:
#line 557 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFPNT3F;    ;
    break;}
case 130:
#line 558 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFPNT4F;    ;
    break;}
case 131:
#line 559 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFVEC4F;    ;
    break;}
case 132:
#line 560 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFPLANE;    ;
    break;}
}

#line 610 "/usr/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (int) (sizeof (yytname) / sizeof (char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen (yytname[x]) + 15, count++;
	  size += strlen ("parse error, unexpected `") + 1;
	  size += strlen (yytname[YYTRANSLATE (yychar)]);
	  msg = (char *) malloc (size);
	  if (msg != 0)
	    {
	      strcpy (msg, "parse error, unexpected `");
	      strcat (msg, yytname[YYTRANSLATE (yychar)]);
	      strcat (msg, "'");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (int) (sizeof (yytname) / sizeof (char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat (msg, count == 0 ? ", expecting `" : " or `");
			strcat (msg, yytname[x]);
			strcat (msg, "'");
			count++;
		      }
		}
	      yyerror (msg);
	      free (msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

/*--------------.
| yyerrhandle.  |
`--------------*/
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#if YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 0;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#if YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 1;
}
#line 620 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"


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


