/* A Bison parser, made from ../../Loader/ScanParseSkel/OSGScanParseSkel.y
   by GNU bison 1.33.  */

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

#line 38 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"


#ifdef WIN32
#include <malloc.h>
#define YYSIZE_T size_t
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
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		244
#define	YYFLAG		-32768
#define	YYNTBASE	96

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 349 ? yytranslate[x] : 163)

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

#if YYDEBUG
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
     323,   325,   327,   329,   331,   333,   335,   337,   339,   341,
     344,   346,   348,   350,   352,   354,   356,   358,   360,   363,
     365,   367,   369,   371,   373,   375,   377,   379,   381,   383,
     385,   387,   389,   391,   393,   395,   397,   399,   401,   403,
     405,   407,   409,   411,   413,   417,   419,   421,   424
};
static const short yyrhs[] =
{
      97,     0,    98,     0,   131,     0,    98,    99,     0,    99,
       0,   100,     0,   104,     0,   126,     0,   132,     0,     0,
       3,   151,   101,   132,     0,     4,   151,     0,   132,     0,
       0,     3,   151,   103,   132,     0,   108,     0,   122,     0,
     106,     0,     0,   106,   104,     0,   104,     0,   152,     0,
      20,     0,     0,    11,   107,    12,   112,    13,   109,     8,
     110,     9,     0,   111,     0,   131,     0,   105,   102,    97,
       0,   113,     0,   131,     0,   113,   119,     0,   119,     0,
       0,    16,   157,   115,   155,     0,     0,    17,   157,   116,
     156,     0,     0,     0,    19,   157,   117,   153,   118,   158,
       0,   114,     0,     0,     0,    18,   157,   120,   153,   121,
     158,     0,    14,   152,    12,   123,    13,   130,     0,   124,
       0,   131,     0,   124,   125,     0,   125,     0,    16,   157,
     155,     0,    17,   157,   156,     0,    19,   157,   153,     0,
      18,   157,   153,     0,     0,     0,     0,     5,   151,   127,
       6,   156,   128,     7,   151,   129,     6,   155,     0,   158,
       0,     0,     0,   152,   133,     8,   135,     9,     0,     0,
      20,   134,     8,   137,     9,     0,   136,     0,   131,     0,
     136,   147,     0,   147,     0,   138,     0,   131,     0,   138,
     146,     0,   146,     0,     0,    16,   157,   140,   155,     0,
       0,    17,   157,   141,   156,     0,    15,   154,     0,     0,
       0,    19,   157,   144,   153,     0,    15,   153,     0,   158,
       0,   147,     0,   139,   142,     0,   143,   145,     0,     0,
     153,   148,   149,     0,   126,     0,   104,     0,    15,   150,
       0,   158,     0,    10,     0,    10,     0,    10,     0,    10,
       0,    10,     0,    10,     0,    10,     0,    42,     0,    43,
       0,    44,     0,    45,     0,    46,     0,    47,     0,    48,
       0,    49,     0,    50,     0,    51,     0,    52,     0,    53,
       0,    54,     0,    55,     0,    56,     0,    57,     0,    58,
       0,    59,     0,    60,     0,    61,     0,    79,     0,    80,
       0,    81,     0,    82,     0,    83,     0,    84,     0,    85,
       0,    86,     0,    87,     0,    88,     0,    89,     0,    90,
       0,    91,     0,    92,     0,    93,     0,    94,     0,    95,
       0,    22,     0,    23,     0,    24,     0,    25,     0,    26,
       0,    27,   159,     0,    28,     0,    29,     0,    30,     0,
      31,     0,    32,     0,    33,     0,    34,     0,    35,     0,
      36,   160,     0,    37,     0,    38,     0,    39,     0,    40,
       0,    41,     0,    62,     0,    63,     0,    64,     0,    65,
       0,    66,     0,    67,     0,    69,     0,    68,     0,    70,
       0,    71,     0,    72,     0,    73,     0,    74,     0,    75,
       0,    77,     0,    78,     0,    76,     0,   100,     0,    21,
       0,   100,     0,    12,   161,    13,     0,   162,     0,   131,
       0,   162,   100,     0,   100,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   184,   187,   188,   191,   192,   195,   196,   197,   200,
     201,   201,   204,   209,   210,   210,   215,   216,   220,   221,
     224,   225,   228,   230,   233,   233,   244,   245,   248,   251,
     252,   255,   256,   260,   260,   268,   268,   276,   276,   276,
     292,   293,   293,   293,   308,   316,   317,   320,   322,   325,
     326,   327,   328,   331,   331,   331,   331,   349,   352,   355,
     355,   364,   364,   375,   376,   379,   380,   383,   384,   387,
     388,   391,   391,   400,   400,   411,   412,   415,   415,   431,
     441,   458,   459,   461,   466,   466,   489,   490,   495,   501,
     507,   510,   513,   516,   519,   522,   525,   528,   529,   530,
     531,   532,   533,   534,   535,   536,   537,   538,   539,   540,
     541,   542,   543,   544,   545,   546,   547,   548,   549,   550,
     551,   552,   553,   554,   555,   556,   557,   558,   559,   560,
     561,   562,   563,   564,   568,   569,   570,   571,   572,   573,
     574,   575,   576,   577,   578,   579,   580,   581,   582,   583,
     584,   585,   586,   587,   588,   589,   590,   591,   592,   593,
     594,   595,   596,   597,   598,   599,   600,   601,   602,   603,
     604,   608,   609,   612,   613,   616,   617,   620,   621
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

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
  "protoStatements", "protoId", "proto", "@3", "protoBodyORempty", 
  "protoBody", "interfaceDeclarationsORempty", "interfaceDeclarations", 
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
       0,    96,    97,    97,    98,    98,    99,    99,    99,   100,
     101,   100,   100,   102,   103,   102,   104,   104,   105,   105,
     106,   106,   107,   107,   109,   108,   110,   110,   111,   112,
     112,   113,   113,   115,   114,   116,   114,   117,   118,   114,
     119,   120,   121,   119,   122,   123,   123,   124,   124,   125,
     125,   125,   125,   127,   128,   129,   126,   130,   131,   133,
     132,   134,   132,   135,   135,   136,   136,   137,   137,   138,
     138,   140,   139,   141,   139,   142,   142,   144,   143,   145,
     145,   146,   146,   146,   148,   147,   147,   147,   149,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   159,   159,   160,   160,   161,   161,   162,   162
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     2,     1
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
     132,   133,    33,    35,    41,    37,    24,    31,     0,     0,
       0,     0,     0,    47,    71,    73,    77,    62,    69,     0,
      82,     0,   134,   135,   136,   137,   138,     0,   140,   141,
     142,   143,   144,   145,   146,   147,     0,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   161,   160,
     162,   163,   164,   165,   166,   167,   170,   168,   169,    83,
      80,     0,    60,    65,     0,     0,     0,     0,     0,     0,
      95,    49,    50,    52,    51,    44,    57,     0,     0,     0,
      94,    75,    79,   172,   171,   139,    58,   173,   148,     0,
      85,    89,     0,    34,    36,    42,    38,    19,    72,    74,
      78,   178,   176,     0,   175,    90,    88,    55,     0,     0,
      21,     0,    18,     0,    26,    27,   174,   177,     0,    43,
      39,     0,    58,    13,    20,    25,     0,    14,    28,    56,
       0,    15,     0,     0,     0
};

static const short yydefgoto[] =
{
     242,     8,     9,    10,    11,    30,   232,   240,    59,   221,
     222,    24,    13,   179,   223,   224,    42,    43,    44,   175,
     176,   178,   219,    45,   177,   218,    14,    51,    52,    53,
      60,    31,   174,   228,   185,    16,    17,    29,    27,    70,
      71,    62,    63,    64,   187,   188,   130,    65,   189,   169,
      66,    67,   171,   200,   216,    20,    18,    68,   191,   181,
      74,   112,   170,   195,   198,   213,   214
};

static const short yypact[] =
{
      43,     9,     9,     9,-32768,    14,    35,-32768,-32768,    43,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,    29,-32768,    38,    50,-32768,    59,
      15,    73,    72,   106,   116,    71,-32768,    82,   270,   270,
     270,   270,    47,    72,-32768,-32768,-32768,   270,   270,   270,
     270,    80,   106,-32768,-32768,-32768,   270,   270,   270,-32768,
  -32768,-32768,    86,   116,    81,    79,-32768,-32768,-32768,-32768,
      88,    71,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   118,    82,
     119,   119,   233,-32768,-32768,-32768,-32768,-32768,-32768,   121,
  -32768,   119,-32768,-32768,-32768,-32768,-32768,    23,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,    52,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,   213,-32768,-32768,    91,   118,    82,   119,   119,   126,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,   118,    82,   119,
  -32768,-32768,-32768,-32768,-32768,-32768,    67,-32768,-32768,   127,
  -32768,-32768,     9,-32768,-32768,-32768,-32768,    69,-32768,-32768,
  -32768,-32768,-32768,   123,    67,-32768,-32768,-32768,   233,   233,
  -32768,    39,    54,   129,-32768,-32768,-32768,-32768,   133,-32768,
  -32768,     9,    43,-32768,-32768,-32768,   118,-32768,-32768,-32768,
      15,-32768,   140,   158,-32768
};

static const short yypgoto[] =
{
  -32768,   -73,-32768,   151,  -130,-32768,-32768,-32768,     0,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,   120,-32768,-32768,-32768,-32768,-32768,   109,
       1,-32768,-32768,-32768,-32768,   -21,   -28,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
      99,   -20,-32768,-32768,-32768,     3,    31,  -103,-32768,  -167,
    -115,   -18,  -119,-32768,-32768,-32768,-32768
};


#define	YYLAST		365


static const short yytable[] =
{
      12,    15,    36,   186,   182,    21,    22,   194,   203,    12,
      15,    46,    54,    61,    69,    72,   197,   183,   184,    19,
     208,   113,   114,   115,     4,     4,     1,     2,   192,   118,
     119,   120,   121,     4,    23,     7,    25,    26,   124,   125,
     126,    32,   231,     7,   193,     4,     1,     2,     3,     4,
      33,   173,   201,     4,     5,     1,     2,     6,    34,     7,
     116,   204,     4,     7,   196,     5,   211,    35,     6,   239,
       1,     2,     7,   209,   205,   206,     3,     4,   -58,    37,
       5,    55,     5,     6,   227,     6,   210,     7,    38,    39,
      40,    41,    73,   122,   131,   127,   129,   172,   202,   229,
     230,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,     3,    47,    48,    49,    50,    55,     5,   180,    55,
       6,   190,    56,    57,   207,    58,   226,   215,   235,   236,
     243,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   244,   238,
      28,   123,   128,   117,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   212,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   225,     0,     0,     0,
       0,     0,     0,   233,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   217,     0,   220,     0,     0,
       0,     0,   241,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   234,     0,     0,     0,     0,     0,   199,     0,
       0,     0,    12,    15,   237,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,     0,     0,     0,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111
};

static const short yycheck[] =
{
       0,     0,    30,   122,   119,     2,     3,   137,   175,     9,
       9,    32,    33,    34,    35,    35,   146,   120,   121,    10,
     187,    39,    40,    41,    10,    10,     3,     4,   131,    47,
      48,    49,    50,    10,    20,    20,     5,     6,    56,    57,
      58,    12,     3,    20,    21,    10,     3,     4,     5,    10,
      12,    71,   171,    10,    11,     3,     4,    14,     8,    20,
      13,   176,    10,    20,    12,    11,   196,     8,    14,   236,
       3,     4,    20,   188,   177,   178,     5,    10,     9,     6,
      11,    10,    11,    14,   214,    14,   189,    20,    16,    17,
      18,    19,    10,    13,    15,     9,    15,     9,     7,   218,
     219,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,     5,    16,    17,    18,    19,    10,    11,    10,    10,
      14,    10,    16,    17,     8,    19,    13,    10,     9,     6,
       0,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,     0,   232,
       9,    52,    63,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   196,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   207,    -1,    -1,    -1,
      -1,    -1,    -1,   221,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   202,    -1,   207,    -1,    -1,
      -1,    -1,   240,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   222,    -1,    -1,    -1,    -1,    -1,    15,    -1,
      -1,    -1,   232,   232,   231,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software
   Foundation, Inc.

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#ifdef __cplusplus
# define YYSTD(x) std::x
#else
# define YYSTD(x) x
#endif

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

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
#  ifdef __cplusplus
#   include <cstdlib> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T std::size_t
#  else
#   ifdef __STDC__
#    include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#    define YYSIZE_T size_t
#   endif
#  endif
#  define YYSTACK_ALLOC YYSTD (malloc)
#  define YYSTACK_FREE YYSTD (free)
# endif

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

/* Relocate the TYPE STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Type, Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	yymemcpy ((char *) yyptr, (char *) (Stack),			\
		  yysize * (YYSIZE_T) sizeof (Type));			\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (Type) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# ifdef __cplusplus
#  include <cstddef> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T std::size_t
# else
#  ifdef __STDC__
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
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

# ifndef YYFPRINTF
#  ifdef __cplusplus
#   include <cstdio>  /* INFRINGES ON USER NAME SPACE */
#  else
#   include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYFPRINTF YYSTD (fprintf)
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
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

#if ! defined (yyoverflow) && ! defined (yymemcpy)
# if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#  define yymemcpy __builtin_memcpy
# else				/* not GNU C or C++ */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
#  if defined (__STDC__) || defined (__cplusplus)
yymemcpy (char *yyto, const char *yyfrom, YYSIZE_T yycount)
#  else
yymemcpy (yyto, yyfrom, yycount)
     char *yyto;
     const char *yyfrom;
     YYSIZE_T yycount;
#  endif
{
  register const char *yyf = yyfrom;
  register char *yyt = yyto;
  register YYSIZE_T yyi = yycount;

  while (yyi-- != 0)
    *yyt++ = *yyf++;
}
# endif
#endif

#ifdef YYERROR_VERBOSE

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
#endif

#line 341 "/usr/share/bison/bison.simple"


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

#define YY_DECL_NON_LSP_VARIABLES			\
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
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
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

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

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
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
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
	YYSTACK_RELOCATE (short, yyss);
	YYSTACK_RELOCATE (YYSTYPE, yyvs);
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (YYLTYPE, yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

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
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
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
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

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
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 10:
#line 202 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, OSGScanParseSkel_text); ;
    break;}
case 12:
#line 205 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                                  _pSkel->use(OSGScanParseSkel_text); ;
    break;}
case 14:
#line 211 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, OSGScanParseSkel_text); ;
    break;}
case 22:
#line 228 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL) 
                        _pSkel->beginProto(OSGScanParseSkel_text); ;
    break;}
case 23:
#line 230 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL) 
                        _pSkel->beginProto(OSGScanParseSkel_text); ;
    break;}
case 24:
#line 237 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL) 
                        _pSkel->endProto(); ;
    break;}
case 33:
#line 261 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                      OSGScanParseSkel_text); ;
    break;}
case 34:
#line 263 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                                               _pSkel->addEventInDecl(
                                                szName1,
                                                OSGScanParseSkel_text); 
                                              freeName(szName1); ;
    break;}
case 35:
#line 269 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                      OSGScanParseSkel_text); ;
    break;}
case 36:
#line 271 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                                               _pSkel->addEventOutDecl(
                                                szName1,
                                                OSGScanParseSkel_text); 
                                              freeName(szName1); ;
    break;}
case 37:
#line 277 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                      OSGScanParseSkel_text); ;
    break;}
case 38:
#line 279 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ expectType(nextType); 
                                              if(_pSkel != NULL)
                                               _pSkel->beginFieldDecl(
                                                szName1,
                                                nextType,
                                                OSGScanParseSkel_text); 
                                              freeName(szName1); ;
    break;}
case 39:
#line 286 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = 0; 
                                              if(_pSkel != NULL)
                                               _pSkel->endFieldDecl();
                                             ;
    break;}
case 41:
#line 294 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                              OSGScanParseSkel_text); ;
    break;}
case 42:
#line 296 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ expectType(nextType);  
                                      if(_pSkel != NULL)
                                       _pSkel->beginExposedFieldDecl(
                                        szName1,
                                        nextType,
                                        OSGScanParseSkel_text); 
                                       freeName(szName1); ;
    break;}
case 43:
#line 303 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = 0; 
                                      if(_pSkel != NULL)
                                       _pSkel->endExposedFieldDecl(); ;
    break;}
case 53:
#line 332 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, OSGScanParseSkel_text); ;
    break;}
case 54:
#line 334 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName2, OSGScanParseSkel_text); ;
    break;}
case 55:
#line 336 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName3, OSGScanParseSkel_text); ;
    break;}
case 56:
#line 338 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
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
#line 355 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                     _pSkel->beginNode(OSGScanParseSkel_text, szName1); 

                    freeName(szName1);
                  ;
    break;}
case 60:
#line 362 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                     _pSkel->endNode(); ;
    break;}
case 61:
#line 364 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                     _pSkel->beginNode(OSGScanParseSkel_text, szName1); 

                    freeName(szName1);
                  ;
    break;}
case 62:
#line 371 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                     _pSkel->endNode(); ;
    break;}
case 71:
#line 392 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                     OSGScanParseSkel_text); ;
    break;}
case 72:
#line 394 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                                                     _pSkel->addEventInDecl(
                                                       szName1,
                                                       OSGScanParseSkel_text); 

                                                 freeName(szName1); ;
    break;}
case 73:
#line 401 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                      OSGScanParseSkel_text); ;
    break;}
case 74:
#line 403 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                                                     _pSkel->addEventOutDecl(
                                                       szName1,
                                                       OSGScanParseSkel_text); 

                                                  freeName(szName1); ;
    break;}
case 77:
#line 416 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                        OSGScanParseSkel_text);
                                               ;
    break;}
case 78:
#line 419 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
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
#line 431 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
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
#line 441 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = 0; 

                                                     if(_pSkel != NULL)
                                                       _pSkel->endFieldDecl();

                                                   ;
    break;}
case 84:
#line 467 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
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
#line 495 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                          {
                            _pSkel->is(OSGScanParseSkel_text);
                            _pSkel->endField();
                          }
                        ;
    break;}
case 89:
#line 501 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                            _pSkel->endField();
                        ;
    break;}
case 97:
#line 528 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFCOLOR;    ;
    break;}
case 98:
#line 529 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFFLOAT;    ;
    break;}
case 99:
#line 530 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFINT32;    ;
    break;}
case 100:
#line 531 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFNODE;     ;
    break;}
case 101:
#line 532 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFROTATION; ;
    break;}
case 102:
#line 533 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFSTRING;   ;
    break;}
case 103:
#line 534 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFTIME;     ;
    break;}
case 104:
#line 535 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFVEC2F;    ;
    break;}
case 105:
#line 536 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFVEC3F;    ;
    break;}
case 106:
#line 537 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFBOOL;     ;
    break;}
case 107:
#line 538 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFCOLOR;    ;
    break;}
case 108:
#line 539 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFFLOAT;    ;
    break;}
case 109:
#line 540 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFIMAGE;    ;
    break;}
case 110:
#line 541 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFINT32;    ;
    break;}
case 111:
#line 542 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFNODE;     ;
    break;}
case 112:
#line 543 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFROTATION; ;
    break;}
case 113:
#line 544 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFSTRING;   ;
    break;}
case 114:
#line 545 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFTIME;     ;
    break;}
case 115:
#line 546 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFVEC2F;    ;
    break;}
case 116:
#line 547 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFVEC3F;    ;
    break;}
case 117:
#line 548 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFCOLOR4F;  ;
    break;}
case 118:
#line 549 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFCOLOR3F;  ;
    break;}
case 119:
#line 550 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFMATRIX;   ;
    break;}
case 120:
#line 551 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFPNT2F;    ;
    break;}
case 121:
#line 552 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFPNT3F;    ;
    break;}
case 122:
#line 553 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFPNT4F;    ;
    break;}
case 123:
#line 554 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFVEC4F;    ;
    break;}
case 124:
#line 555 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFPLANE;    ;
    break;}
case 125:
#line 556 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFCOLOR4F;  ;
    break;}
case 126:
#line 557 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFCOLOR3F;  ;
    break;}
case 127:
#line 558 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFMATRIX;   ;
    break;}
case 128:
#line 559 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFPNT2F;    ;
    break;}
case 129:
#line 560 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFPNT3F;    ;
    break;}
case 130:
#line 561 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFPNT4F;    ;
    break;}
case 131:
#line 562 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFVEC4F;    ;
    break;}
case 132:
#line 563 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFPLANE;    ;
    break;}
case 133:
#line 564 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFVOLUME;   ;
    break;}
}

#line 727 "/usr/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

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
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
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
#endif /* defined (YYERROR_VERBOSE) */
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
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "Error: state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
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
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 625 "../../Loader/ScanParseSkel/OSGScanParseSkel.y"


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


