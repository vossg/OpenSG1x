
/* A Bison parser, made from ../../../Loader/ScanParseSkel/OSGScanParseSkel.y
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
# define	TOK_SFVOLUME	332
# define	Tok_MFColor4f	333
# define	Tok_MFColor3f	334
# define	Tok_MFMatrix	335
# define	Tok_MFPnt2f	336
# define	Tok_MFPnt3f	337
# define	Tok_MFPnt4f	338
# define	Tok_MFVec4f	339
# define	Tok_MFPlane	340
# define	Tok_SFColor4f	341
# define	Tok_SFColor3f	342
# define	Tok_SFMatrix	343
# define	Tok_SFPnt2f	344
# define	Tok_SFPnt3f	345
# define	Tok_SFPnt4f	346
# define	Tok_SFVec4f	347
# define	Tok_SFPlane	348
# define	Tok_SFVolume	349

#line 38 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"


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

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#include <stdio.h>



#define	YYFINAL		243
#define	YYFLAG		-32768
#define	YYNTBASE	96

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 349 ? yytranslate[x] : 162)

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
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95
};

#if YYDEBUG != 0
static const short yyprhs[] =
{
       0,     0,     2,     4,     6,     9,    11,    13,    15,    17,
      19,    20,    25,    28,    30,    31,    36,    38,    40,    42,
      43,    46,    48,    50,    52,    61,    63,    65,    69,    71,
      73,    76,    78,    79,    84,    85,    90,    91,    92,    99,
     101,   102,   103,   110,   117,   119,   121,   124,   126,   130,
     134,   138,   142,   143,   144,   145,   157,   159,   160,   161,
     167,   168,   174,   176,   178,   181,   183,   185,   187,   190,
     192,   193,   198,   199,   204,   207,   208,   209,   214,   217,
     219,   221,   224,   227,   228,   232,   234,   236,   239,   241,
     243,   245,   247,   249,   251,   253,   255,   257,   259,   261,
     263,   265,   267,   269,   271,   273,   275,   277,   279,   281,
     283,   285,   287,   289,   291,   293,   295,   297,   299,   301,
     303,   305,   307,   309,   311,   313,   315,   317,   319,   321,
     323,   325,   327,   329,   331,   333,   335,   337,   339,   342,
     344,   346,   348,   350,   352,   354,   356,   358,   361,   363,
     365,   367,   369,   371,   373,   375,   377,   379,   381,   383,
     385,   387,   389,   391,   393,   395,   397,   399,   401,   403,
     405,   407,   409,   411,   415,   417,   419,   422
};
static const short yyrhs[] =
{
      97,     0,    98,     0,   130,     0,    98,    99,     0,    99,
       0,   100,     0,   104,     0,   125,     0,   131,     0,     0,
       3,   150,   101,   131,     0,     4,   150,     0,   131,     0,
       0,     3,   150,   103,   131,     0,   108,     0,   121,     0,
     106,     0,     0,   106,   104,     0,   104,     0,   151,     0,
      20,     0,    11,   107,    12,   111,    13,     8,   109,     9,
       0,   110,     0,   130,     0,   105,   102,    97,     0,   112,
       0,   130,     0,   112,   118,     0,   118,     0,     0,    16,
     156,   114,   154,     0,     0,    17,   156,   115,   155,     0,
       0,     0,    19,   156,   116,   152,   117,   157,     0,   113,
       0,     0,     0,    18,   156,   119,   152,   120,   157,     0,
      14,   151,    12,   122,    13,   129,     0,   123,     0,   130,
       0,   123,   124,     0,   124,     0,    16,   156,   154,     0,
      17,   156,   155,     0,    19,   156,   152,     0,    18,   156,
     152,     0,     0,     0,     0,     5,   150,   126,     6,   155,
     127,     7,   150,   128,     6,   154,     0,   157,     0,     0,
       0,   151,   132,     8,   134,     9,     0,     0,    20,   133,
       8,   136,     9,     0,   135,     0,   130,     0,   135,   146,
       0,   146,     0,   137,     0,   130,     0,   137,   145,     0,
     145,     0,     0,    16,   156,   139,   154,     0,     0,    17,
     156,   140,   155,     0,    15,   153,     0,     0,     0,    19,
     156,   143,   152,     0,    15,   152,     0,   157,     0,   146,
       0,   138,   141,     0,   142,   144,     0,     0,   152,   147,
     148,     0,   125,     0,   104,     0,    15,   149,     0,   157,
       0,    10,     0,    10,     0,    10,     0,    10,     0,    10,
       0,    10,     0,    10,     0,    42,     0,    43,     0,    44,
       0,    45,     0,    46,     0,    47,     0,    48,     0,    49,
       0,    50,     0,    51,     0,    52,     0,    53,     0,    54,
       0,    55,     0,    56,     0,    57,     0,    58,     0,    59,
       0,    60,     0,    61,     0,    79,     0,    80,     0,    81,
       0,    82,     0,    83,     0,    84,     0,    85,     0,    86,
       0,    87,     0,    88,     0,    89,     0,    90,     0,    91,
       0,    92,     0,    93,     0,    94,     0,    95,     0,    22,
       0,    23,     0,    24,     0,    25,     0,    26,     0,    27,
     158,     0,    28,     0,    29,     0,    30,     0,    31,     0,
      32,     0,    33,     0,    34,     0,    35,     0,    36,   159,
       0,    37,     0,    38,     0,    39,     0,    40,     0,    41,
       0,    62,     0,    63,     0,    64,     0,    65,     0,    66,
       0,    67,     0,    69,     0,    68,     0,    70,     0,    71,
       0,    72,     0,    73,     0,    74,     0,    75,     0,    77,
       0,    78,     0,    76,     0,   100,     0,    21,     0,   100,
       0,    12,   160,    13,     0,   161,     0,   130,     0,   161,
     100,     0,   100,     0
};

#endif

#if YYDEBUG != 0
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   188,   191,   192,   195,   196,   199,   200,   201,   204,
     205,   208,   208,   213,   214,   217,   219,   220,   224,   225,
     228,   229,   232,   234,   237,   248,   249,   252,   255,   256,
     259,   260,   264,   267,   272,   275,   280,   283,   290,   296,
     297,   300,   307,   312,   320,   321,   324,   326,   329,   330,
     331,   332,   335,   338,   340,   342,   353,   356,   359,   365,
     368,   374,   379,   380,   383,   384,   387,   388,   391,   392,
     395,   398,   404,   407,   415,   416,   419,   423,   435,   445,
     462,   463,   465,   470,   493,   493,   494,   499,   505,   511,
     514,   517,   520,   523,   526,   529,   532,   533,   534,   535,
     536,   537,   538,   539,   540,   541,   542,   543,   544,   545,
     546,   547,   548,   549,   550,   551,   552,   553,   554,   555,
     556,   557,   558,   559,   560,   561,   562,   563,   564,   565,
     566,   567,   568,   572,   573,   574,   575,   576,   577,   578,
     579,   580,   581,   582,   583,   584,   585,   586,   587,   588,
     589,   590,   591,   592,   593,   594,   595,   596,   597,   598,
     599,   600,   601,   602,   603,   604,   605,   606,   607,   608,
     612,   613,   616,   617,   620,   621,   624,   625
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
  "TOK_SFPLANE", "TOK_SFVOLUME", "Tok_MFColor4f", "Tok_MFColor3f", 
  "Tok_MFMatrix", "Tok_MFPnt2f", "Tok_MFPnt3f", "Tok_MFPnt4f", 
  "Tok_MFVec4f", "Tok_MFPlane", "Tok_SFColor4f", "Tok_SFColor3f", 
  "Tok_SFMatrix", "Tok_SFPnt2f", "Tok_SFPnt3f", "Tok_SFPnt4f", 
  "Tok_SFVec4f", "Tok_SFPlane", "Tok_SFVolume", "vrmlScene", 
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
  "nodeStatementsORempty", "nodeStatements", NULL
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    96,    97,    97,    98,    98,    99,    99,    99,   100,
     101,   100,   100,   102,   103,   102,   104,   104,   105,   105,
     106,   106,   107,   107,   108,   109,   109,   110,   111,   111,
     112,   112,   114,   113,   115,   113,   116,   117,   113,   118,
     119,   120,   118,   121,   122,   122,   123,   123,   124,   124,
     124,   124,   126,   127,   128,   125,   129,   130,   132,   131,
     133,   131,   134,   134,   135,   135,   136,   136,   137,   137,
     139,   138,   140,   138,   141,   141,   143,   142,   144,   144,
     145,   145,   145,   147,   146,   146,   146,   148,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     158,   158,   159,   159,   160,   160,   161,   161
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       0,     4,     2,     1,     0,     4,     1,     1,     1,     0,
       2,     1,     1,     1,     8,     1,     1,     3,     1,     1,
       2,     1,     0,     4,     0,     4,     0,     0,     6,     1,
       0,     0,     6,     6,     1,     1,     2,     1,     3,     3,
       3,     3,     0,     0,     0,    11,     1,     0,     0,     5,
       0,     5,     1,     1,     2,     1,     1,     1,     2,     1,
       0,     4,     0,     4,     2,     0,     0,     4,     2,     1,
       1,     2,     2,     0,     3,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     2,     1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
      57,     0,     0,     0,    91,     0,     0,    60,     1,     2,
       5,     6,     7,    16,    17,     8,     3,     9,    58,    90,
      10,    12,    52,    23,     0,    22,     0,     0,     4,     0,
       0,     0,    57,    57,    57,    57,    11,     0,     0,     0,
       0,     0,     0,    28,    39,    31,    29,     0,     0,     0,
       0,     0,    44,    47,    45,    92,     0,     0,     0,    86,
      85,    67,     0,    66,    75,     0,    69,    80,    83,    63,
       0,    62,    65,    95,    53,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,    32,    34,    40,    36,     0,    30,     0,     0,
       0,     0,     0,    46,    70,    72,    76,    61,    68,     0,
      81,     0,   133,   134,   135,   136,   137,     0,   139,   140,
     141,   142,   143,   144,   145,   146,     0,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   160,   159,
     161,   162,   163,   164,   165,   166,   169,   167,   168,    82,
      79,     0,    59,    64,     0,     0,     0,     0,     0,    19,
      94,    48,    49,    51,    50,    43,    56,     0,     0,     0,
      93,    74,    78,   171,   170,   138,    57,   172,   147,     0,
      84,    88,     0,    33,    35,    41,    37,    21,     0,    18,
       0,    25,    26,    71,    73,    77,   177,   175,     0,   174,
      89,    87,    54,     0,     0,     0,    57,    13,    20,    24,
     173,   176,     0,    42,    38,    14,    27,     0,     0,    55,
      15,     0,     0,     0
};

static const short yydefgoto[] =
{
     241,     8,     9,    10,    11,    30,   226,   238,    59,   208,
     209,    24,    13,   210,   211,    42,    43,    44,   175,   176,
     178,   224,    45,   177,   223,    14,    51,    52,    53,    60,
      31,   174,   232,   185,    16,    17,    29,    27,    70,    71,
      62,    63,    64,   187,   188,   130,    65,   189,   169,    66,
      67,   171,   200,   221,    20,    18,    68,   191,   181,    74,
     112,   170,   195,   198,   218,   219
};

static const short yypact[] =
{
      43,     9,     9,     9,-32768,    14,    35,-32768,-32768,    43,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,    29,-32768,    38,    50,-32768,    59,
      15,    63,    95,    99,    80,    96,-32768,    61,   328,   328,
     328,   328,    47,    95,-32768,-32768,-32768,   328,   328,   328,
     328,    65,    99,-32768,-32768,-32768,   328,   328,   328,-32768,
  -32768,-32768,    71,    80,    67,   207,-32768,-32768,-32768,-32768,
      78,    96,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,    84,-32768,    85,    61,
      88,    88,   291,-32768,-32768,-32768,-32768,-32768,-32768,    90,
  -32768,    88,-32768,-32768,-32768,-32768,-32768,    23,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,    52,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,   271,-32768,-32768,    81,    85,    61,    88,    88,    70,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,    85,    61,    88,
  -32768,-32768,-32768,-32768,-32768,-32768,    73,-32768,-32768,    92,
  -32768,-32768,     9,-32768,-32768,-32768,-32768,-32768,    39,    54,
      94,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   106,    73,
  -32768,-32768,-32768,   291,   291,     9,    43,-32768,-32768,-32768,
  -32768,-32768,   102,-32768,-32768,-32768,-32768,    85,    15,-32768,
  -32768,   109,   120,-32768
};

static const short yypgoto[] =
{
  -32768,  -105,-32768,   113,  -130,-32768,-32768,-32768,     0,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,    82,-32768,-32768,-32768,-32768,-32768,    72,     1,
  -32768,-32768,-32768,-32768,   -21,   -28,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    60,
     -20,-32768,-32768,-32768,     3,    31,  -103,-32768,  -167,  -115,
     -18,  -119,-32768,-32768,-32768,-32768
};


#define	YYLAST		423


static const short yytable[] =
{
      12,    15,    36,   186,   182,    21,    22,   194,   203,    12,
      15,    46,    54,    61,    69,    72,   197,   183,   184,    19,
     213,   113,   114,   115,     4,     4,     1,     2,   192,   118,
     119,   120,   121,     4,    23,     7,    25,    26,   124,   125,
     126,    32,   225,     7,   193,     4,     1,     2,     3,     4,
      33,   173,   201,     4,     5,     1,     2,     6,    34,     7,
     116,   204,     4,     7,   196,     5,   216,    35,     6,    37,
     239,    73,     7,   214,   205,   206,     1,     2,   122,   -57,
     127,     5,   129,     4,     6,     3,   215,   172,   202,   231,
      55,     5,   179,     7,     6,   180,    56,    57,    55,    58,
     190,     3,   220,   229,   233,   234,    55,     5,   237,   242,
       6,    38,    39,    40,    41,    47,    48,    49,    50,   230,
     243,   236,    28,   128,   123,   117,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   212,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   217,     0,     0,     0,   207,
     227,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   222,     0,     0,     0,   228,
     240,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   131,     0,     0,     0,    12,    15,   235,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   199,     0,     0,     0,
       0,     0,     0,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
       0,     0,     0,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111
};

static const short yycheck[] =
{
       0,     0,    30,   122,   119,     2,     3,   137,   175,     9,
       9,    32,    33,    34,    35,    35,   146,   120,   121,    10,
     187,    39,    40,    41,    10,    10,     3,     4,   131,    47,
      48,    49,    50,    10,    20,    20,     5,     6,    56,    57,
      58,    12,     3,    20,    21,    10,     3,     4,     5,    10,
      12,    71,   171,    10,    11,     3,     4,    14,     8,    20,
      13,   176,    10,    20,    12,    11,   196,     8,    14,     6,
     237,    10,    20,   188,   177,   178,     3,     4,    13,     9,
       9,    11,    15,    10,    14,     5,   189,     9,     7,   219,
      10,    11,     8,    20,    14,    10,    16,    17,    10,    19,
      10,     5,    10,     9,   223,   224,    10,    11,     6,     0,
      14,    16,    17,    18,    19,    16,    17,    18,    19,    13,
       0,   226,     9,    63,    52,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   179,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   196,    -1,    -1,    -1,   179,
     208,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   202,    -1,    -1,    -1,   209,
     238,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    15,    -1,    -1,    -1,   226,   226,   225,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      -1,    -1,    -1,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95
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
#line 206 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, OSGScanParseSkel_text); ;
    break;}
case 12:
#line 209 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                                  _pSkel->use(OSGScanParseSkel_text); ;
    break;}
case 14:
#line 215 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, OSGScanParseSkel_text); ;
    break;}
case 22:
#line 232 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL) 
                        _pSkel->beginProto(OSGScanParseSkel_text); ;
    break;}
case 23:
#line 234 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL) 
                        _pSkel->beginProto(OSGScanParseSkel_text); ;
    break;}
case 24:
#line 244 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL) 
			_pSkel->endProto(); ;
    break;}
case 32:
#line 265 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                      OSGScanParseSkel_text); ;
    break;}
case 33:
#line 267 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                                               _pSkel->addEventInDecl(
                                                szName1,
                                                OSGScanParseSkel_text); 
                                              freeName(szName1); ;
    break;}
case 34:
#line 273 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                      OSGScanParseSkel_text); ;
    break;}
case 35:
#line 275 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                                               _pSkel->addEventOutDecl(
                                                szName1,
                                                OSGScanParseSkel_text); 
                                              freeName(szName1); ;
    break;}
case 36:
#line 281 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                      OSGScanParseSkel_text); ;
    break;}
case 37:
#line 283 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ expectType(nextType); 
                                              if(_pSkel != NULL)
                                               _pSkel->beginFieldDecl(
                                                szName1,
                                                nextType,
                                                OSGScanParseSkel_text); 
                                              freeName(szName1); ;
    break;}
case 38:
#line 290 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = 0; 
                                              if(_pSkel != NULL)
                                               _pSkel->endFieldDecl();
                                             ;
    break;}
case 40:
#line 298 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                              OSGScanParseSkel_text); ;
    break;}
case 41:
#line 300 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ expectType(nextType);  
                                      if(_pSkel != NULL)
                                       _pSkel->beginExposedFieldDecl(
                                        szName1,
                                        nextType,
                                        OSGScanParseSkel_text); 
                                       freeName(szName1); ;
    break;}
case 42:
#line 307 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = 0; 
                                      if(_pSkel != NULL)
                                       _pSkel->endExposedFieldDecl(); ;
    break;}
case 52:
#line 336 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, OSGScanParseSkel_text); ;
    break;}
case 53:
#line 338 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName2, OSGScanParseSkel_text); ;
    break;}
case 54:
#line 340 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName3, OSGScanParseSkel_text); ;
    break;}
case 55:
#line 342 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
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
case 58:
#line 359 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                     _pSkel->beginNode(OSGScanParseSkel_text, szName1); 

                    freeName(szName1);
                  ;
    break;}
case 59:
#line 366 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                     _pSkel->endNode(); ;
    break;}
case 60:
#line 368 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                     _pSkel->beginNode(OSGScanParseSkel_text, szName1); 

                    freeName(szName1);
                  ;
    break;}
case 61:
#line 375 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                     _pSkel->endNode(); ;
    break;}
case 70:
#line 396 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                     OSGScanParseSkel_text); ;
    break;}
case 71:
#line 398 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                                                     _pSkel->addEventInDecl(
                                                       szName1,
                                                       OSGScanParseSkel_text); 

                                                 freeName(szName1); ;
    break;}
case 72:
#line 405 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                      OSGScanParseSkel_text); ;
    break;}
case 73:
#line 407 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                                                     _pSkel->addEventOutDecl(
                                                       szName1,
                                                       OSGScanParseSkel_text); 

                                                  freeName(szName1); ;
    break;}
case 76:
#line 420 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                        OSGScanParseSkel_text);
                                               ;
    break;}
case 77:
#line 423 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ expectType(nextType); 
                                              
                                                 if(_pSkel != NULL)
                                                     _pSkel->beginFieldDecl(
                                                       szName1,
                                                       nextType,
                                                       OSGScanParseSkel_text); 
                                              
                                                 freeName(szName1);
                                               ;
    break;}
case 78:
#line 435 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = 0; 

                                                     if(_pSkel != NULL)
                                                     {
                                                       _pSkel->is(
                                                        OSGScanParseSkel_text);

                                                       _pSkel->endFieldDecl();
                                                     }
                                                   ;
    break;}
case 79:
#line 445 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = 0; 

                                                     if(_pSkel != NULL)
                                                       _pSkel->endFieldDecl();

                                                   ;
    break;}
case 83:
#line 471 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
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
case 87:
#line 499 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                          {
                            _pSkel->is(OSGScanParseSkel_text);
                            _pSkel->endField();
                          }
                        ;
    break;}
case 88:
#line 505 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                            _pSkel->endField();
                        ;
    break;}
case 96:
#line 532 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFCOLOR;    ;
    break;}
case 97:
#line 533 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFFLOAT;    ;
    break;}
case 98:
#line 534 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFINT32;    ;
    break;}
case 99:
#line 535 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFNODE;     ;
    break;}
case 100:
#line 536 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFROTATION; ;
    break;}
case 101:
#line 537 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFSTRING;   ;
    break;}
case 102:
#line 538 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFTIME;     ;
    break;}
case 103:
#line 539 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFVEC2F;    ;
    break;}
case 104:
#line 540 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFVEC3F;    ;
    break;}
case 105:
#line 541 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFBOOL;     ;
    break;}
case 106:
#line 542 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFCOLOR;    ;
    break;}
case 107:
#line 543 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFFLOAT;    ;
    break;}
case 108:
#line 544 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFIMAGE;    ;
    break;}
case 109:
#line 545 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFINT32;    ;
    break;}
case 110:
#line 546 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFNODE;     ;
    break;}
case 111:
#line 547 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFROTATION; ;
    break;}
case 112:
#line 548 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFSTRING;   ;
    break;}
case 113:
#line 549 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFTIME;     ;
    break;}
case 114:
#line 550 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFVEC2F;    ;
    break;}
case 115:
#line 551 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFVEC3F;    ;
    break;}
case 116:
#line 552 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFCOLOR4F;  ;
    break;}
case 117:
#line 553 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFCOLOR3F;  ;
    break;}
case 118:
#line 554 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFMATRIX;   ;
    break;}
case 119:
#line 555 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFPNT2F;    ;
    break;}
case 120:
#line 556 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFPNT3F;    ;
    break;}
case 121:
#line 557 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFPNT4F;    ;
    break;}
case 122:
#line 558 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFVEC4F;    ;
    break;}
case 123:
#line 559 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFPLANE;    ;
    break;}
case 124:
#line 560 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFCOLOR4F;  ;
    break;}
case 125:
#line 561 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFCOLOR3F;  ;
    break;}
case 126:
#line 562 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFMATRIX;   ;
    break;}
case 127:
#line 563 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFPNT2F;    ;
    break;}
case 128:
#line 564 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFPNT3F;    ;
    break;}
case 129:
#line 565 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFPNT4F;    ;
    break;}
case 130:
#line 566 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFVEC4F;    ;
    break;}
case 131:
#line 567 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFPLANE;    ;
    break;}
case 132:
#line 568 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFVOLUME;   ;
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
#line 629 "../../../Loader/ScanParseSkel/OSGScanParseSkel.y"


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


