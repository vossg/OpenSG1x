/* A Bison parser, made from ../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y
   by GNU bison 1.35.  */

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
# define	TOK_MFCOLOR4I	317
# define	TOK_MFCOLOR3F	318
# define	TOK_MFMATRIX	319
# define	TOK_MFPNT2F	320
# define	TOK_MFPNT3F	321
# define	TOK_MFPNT4F	322
# define	TOK_MFVEC4F	323
# define	TOK_MFPLANE	324
# define	TOK_SFCOLOR4F	325
# define	TOK_SFCOLOR4I	326
# define	TOK_SFCOLOR3F	327
# define	TOK_SFMATRIX	328
# define	TOK_SFPNT2F	329
# define	TOK_SFPNT3F	330
# define	TOK_SFPNT4F	331
# define	TOK_SFVEC4F	332
# define	TOK_SFPLANE	333
# define	TOK_SFVOLUME	334
# define	Tok_MFColor4f	335
# define	Tok_MFColor4i	336
# define	Tok_MFColor3f	337
# define	Tok_MFMatrix	338
# define	Tok_MFPnt2f	339
# define	Tok_MFPnt3f	340
# define	Tok_MFPnt4f	341
# define	Tok_MFVec4f	342
# define	Tok_MFPlane	343
# define	Tok_SFColor4f	344
# define	Tok_SFColor4i	345
# define	Tok_SFColor3f	346
# define	Tok_SFMatrix	347
# define	Tok_SFPnt2f	348
# define	Tok_SFPnt3f	349
# define	Tok_SFPnt4f	350
# define	Tok_SFVec4f	351
# define	Tok_SFPlane	352
# define	Tok_SFVolume	353

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

#ifndef YYSTYPE
# define YYSTYPE int
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		257
#define	YYFLAG		-32768
#define	YYNTBASE	100

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 353 ? yytranslate[x] : 172)

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
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     2,     4,     6,     9,    11,    13,    15,    17,
      19,    20,    25,    28,    30,    31,    36,    38,    40,    42,
      43,    46,    48,    50,    52,    61,    63,    65,    69,    71,
      73,    76,    78,    79,    84,    85,    90,    91,    92,    99,
     101,   102,   103,   110,   111,   112,   121,   123,   125,   128,
     130,   131,   136,   137,   142,   143,   148,   149,   154,   155,
     156,   157,   169,   171,   172,   173,   179,   180,   186,   188,
     190,   193,   195,   197,   199,   202,   204,   205,   210,   211,
     216,   219,   220,   221,   226,   229,   231,   233,   236,   239,
     240,   244,   246,   248,   251,   253,   255,   257,   259,   261,
     263,   265,   267,   269,   271,   273,   275,   277,   279,   281,
     283,   285,   287,   289,   291,   293,   295,   297,   299,   301,
     303,   305,   307,   309,   311,   313,   315,   317,   319,   321,
     323,   325,   327,   329,   331,   333,   335,   337,   339,   341,
     343,   345,   347,   349,   351,   353,   355,   358,   360,   362,
     364,   366,   368,   370,   372,   374,   377,   379,   381,   383,
     385,   387,   389,   391,   393,   395,   397,   399,   401,   403,
     405,   407,   409,   411,   413,   415,   417,   419,   421,   423,
     425,   427,   430,   432,   434,   437,   441,   443,   445,   448
};
static const short yyrhs[] =
{
     101,     0,   102,     0,   140,     0,   102,   103,     0,   103,
       0,   104,     0,   108,     0,   135,     0,   141,     0,     0,
       3,   160,   105,   141,     0,     4,   160,     0,   141,     0,
       0,     3,   160,   107,   141,     0,   112,     0,   125,     0,
     110,     0,     0,   110,   108,     0,   108,     0,   161,     0,
      20,     0,    11,   111,    12,   115,    13,     8,   113,     9,
       0,   114,     0,   140,     0,   109,   106,   101,     0,   116,
       0,   140,     0,   116,   122,     0,   122,     0,     0,    16,
     166,   118,   164,     0,     0,    17,   166,   119,   165,     0,
       0,     0,    19,   166,   120,   162,   121,   167,     0,   117,
       0,     0,     0,    18,   166,   123,   162,   124,   167,     0,
       0,     0,    14,   161,   126,    12,   128,    13,   127,   139,
       0,   129,     0,   140,     0,   129,   130,     0,   130,     0,
       0,    16,   166,   131,   164,     0,     0,    17,   166,   132,
     165,     0,     0,    19,   166,   133,   162,     0,     0,    18,
     166,   134,   162,     0,     0,     0,     0,     5,   160,   136,
       6,   165,   137,     7,   160,   138,     6,   164,     0,   167,
       0,     0,     0,   161,   142,     8,   144,     9,     0,     0,
      20,   143,     8,   146,     9,     0,   145,     0,   140,     0,
     145,   156,     0,   156,     0,   147,     0,   140,     0,   147,
     155,     0,   155,     0,     0,    16,   166,   149,   164,     0,
       0,    17,   166,   150,   165,     0,    15,   163,     0,     0,
       0,    19,   166,   153,   162,     0,    15,   162,     0,   167,
       0,   156,     0,   148,   151,     0,   152,   154,     0,     0,
     162,   157,   158,     0,   135,     0,   108,     0,    15,   159,
       0,   167,     0,    10,     0,    10,     0,    10,     0,    10,
       0,    10,     0,    10,     0,    10,     0,    42,     0,    43,
       0,    44,     0,    45,     0,    46,     0,    47,     0,    48,
       0,    49,     0,    50,     0,    51,     0,    52,     0,    53,
       0,    54,     0,    55,     0,    56,     0,    57,     0,    58,
       0,    59,     0,    60,     0,    61,     0,    81,     0,    82,
       0,    83,     0,    84,     0,    85,     0,    86,     0,    87,
       0,    88,     0,    89,     0,    90,     0,    91,     0,    92,
       0,    93,     0,    94,     0,    95,     0,    96,     0,    97,
       0,    98,     0,    99,     0,    22,     0,    23,     0,    24,
       0,    25,     0,    26,     0,    27,   168,     0,    28,     0,
      29,     0,    30,     0,    31,     0,    32,     0,    33,     0,
      34,     0,    35,     0,    36,   169,     0,    37,     0,    38,
       0,    39,     0,    40,     0,    41,     0,    62,     0,    63,
       0,    64,     0,    65,     0,    66,     0,    67,     0,    68,
       0,    70,     0,    69,     0,    71,     0,    72,     0,    73,
       0,    74,     0,    75,     0,    76,     0,    77,     0,    79,
       0,    80,     0,    78,     0,   104,     0,    15,   159,     0,
      21,     0,   104,     0,    15,   159,     0,    12,   170,    13,
       0,   171,     0,   140,     0,   171,   104,     0,   104,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   203,   206,   207,   210,   211,   214,   215,   216,   219,
     220,   220,   223,   228,   229,   229,   234,   235,   239,   240,
     243,   244,   247,   249,   253,   264,   265,   268,   271,   272,
     275,   276,   280,   280,   293,   293,   306,   306,   306,   322,
     323,   323,   323,   338,   338,   338,   357,   358,   361,   363,
     366,   366,   375,   375,   384,   384,   393,   393,   404,   404,
     404,   404,   422,   425,   428,   428,   437,   437,   448,   449,
     452,   453,   456,   457,   460,   461,   464,   464,   474,   474,
     486,   494,   503,   503,   519,   528,   545,   546,   548,   553,
     553,   575,   576,   581,   587,   593,   596,   599,   602,   605,
     608,   611,   614,   615,   616,   617,   618,   619,   620,   621,
     622,   623,   624,   625,   626,   627,   628,   629,   630,   631,
     632,   633,   634,   635,   636,   637,   638,   639,   640,   641,
     642,   643,   644,   645,   646,   647,   648,   649,   650,   651,
     652,   656,   657,   658,   659,   660,   661,   662,   663,   664,
     665,   666,   667,   668,   669,   670,   671,   672,   673,   674,
     675,   676,   677,   678,   679,   680,   681,   682,   683,   684,
     685,   686,   687,   688,   689,   690,   691,   692,   693,   694,
     698,   699,   706,   709,   710,   717,   720,   721,   724,   725
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
  "Tok_SFVec3f", "TOK_MFCOLOR4F", "TOK_MFCOLOR4I", "TOK_MFCOLOR3F", 
  "TOK_MFMATRIX", "TOK_MFPNT2F", "TOK_MFPNT3F", "TOK_MFPNT4F", 
  "TOK_MFVEC4F", "TOK_MFPLANE", "TOK_SFCOLOR4F", "TOK_SFCOLOR4I", 
  "TOK_SFCOLOR3F", "TOK_SFMATRIX", "TOK_SFPNT2F", "TOK_SFPNT3F", 
  "TOK_SFPNT4F", "TOK_SFVEC4F", "TOK_SFPLANE", "TOK_SFVOLUME", 
  "Tok_MFColor4f", "Tok_MFColor4i", "Tok_MFColor3f", "Tok_MFMatrix", 
  "Tok_MFPnt2f", "Tok_MFPnt3f", "Tok_MFPnt4f", "Tok_MFVec4f", 
  "Tok_MFPlane", "Tok_SFColor4f", "Tok_SFColor4i", "Tok_SFColor3f", 
  "Tok_SFMatrix", "Tok_SFPnt2f", "Tok_SFPnt3f", "Tok_SFPnt4f", 
  "Tok_SFVec4f", "Tok_SFPlane", "Tok_SFVolume", "vrmlScene", 
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

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,   100,   101,   101,   102,   102,   103,   103,   103,   104,
     105,   104,   104,   106,   107,   106,   108,   108,   109,   109,
     110,   110,   111,   111,   112,   113,   113,   114,   115,   115,
     116,   116,   118,   117,   119,   117,   120,   121,   117,   122,
     123,   124,   122,   126,   127,   125,   128,   128,   129,   129,
     131,   130,   132,   130,   133,   130,   134,   130,   136,   137,
     138,   135,   139,   140,   142,   141,   143,   141,   144,   144,
     145,   145,   146,   146,   147,   147,   149,   148,   150,   148,
     151,   151,   153,   152,   154,   154,   155,   155,   155,   157,
     156,   156,   156,   158,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     168,   168,   168,   169,   169,   169,   170,   170,   171,   171
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       0,     4,     2,     1,     0,     4,     1,     1,     1,     0,
       2,     1,     1,     1,     8,     1,     1,     3,     1,     1,
       2,     1,     0,     4,     0,     4,     0,     0,     6,     1,
       0,     0,     6,     0,     0,     8,     1,     1,     2,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     0,
       0,    11,     1,     0,     0,     5,     0,     5,     1,     1,
       2,     1,     1,     1,     2,     1,     0,     4,     0,     4,
       2,     0,     0,     4,     2,     1,     1,     2,     2,     0,
       3,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     2,     3,     1,     1,     2,     1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
      63,     0,     0,     0,    97,     0,     0,    66,     1,     2,
       5,     6,     7,    16,    17,     8,     3,     9,    64,    96,
      10,    12,    58,    23,     0,    22,    43,     0,     4,     0,
       0,     0,    63,     0,    63,    63,    11,     0,     0,     0,
       0,     0,     0,    28,    39,    31,    29,    63,    98,     0,
       0,     0,    92,    91,    73,     0,    72,    81,     0,    75,
      86,    89,    69,     0,    68,    71,   101,    59,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,    32,    34,    40,
      36,     0,    30,     0,     0,     0,     0,     0,    46,    49,
      47,    76,    78,    82,    67,    74,     0,    87,     0,   141,
     142,   143,   144,   145,     0,   147,   148,   149,   150,   151,
     152,   153,   154,     0,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   169,   168,   170,   171,
     172,   173,   174,   175,   176,   179,   177,   178,    88,    85,
       0,    65,    70,     0,     0,     0,     0,     0,    19,    50,
      52,    56,    54,    44,    48,     0,     0,     0,    99,    80,
      84,     0,   182,   180,   146,    63,     0,   183,   155,     0,
      90,    94,     0,   100,    33,    35,    41,    37,    21,     0,
      18,     0,    25,    26,     0,     0,     0,     0,     0,    77,
      79,    83,    95,   181,   189,   187,     0,   186,   184,    93,
      60,     0,     0,     0,    63,    13,    20,    24,    51,    53,
      57,    55,    45,    62,   185,   188,     0,    42,    38,    14,
      27,     0,     0,    61,    15,     0,     0,     0
};

static const short yydefgoto[] =
{
     255,     8,     9,    10,    11,    30,   234,   252,    52,   209,
     210,    24,    13,   211,   212,    42,    43,    44,   174,   175,
     177,   232,    45,   176,   231,    14,    33,   218,   117,   118,
     119,   214,   215,   217,   216,    53,    31,   173,   246,   242,
      16,    17,    29,    27,    63,    64,    55,    56,    57,   185,
     186,   127,    58,   187,   168,    59,    60,   170,   200,   223,
      20,    18,    61,   189,   204,    67,   107,   169,   194,   198,
     226,   227
};

static const short yypact[] =
{
      57,     8,     8,     8,-32768,    20,    38,-32768,-32768,    57,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,    34,-32768,-32768,    73,-32768,    76,
      21,    72,    86,    75,    69,    96,-32768,    79,   340,   340,
     340,   340,    77,    86,-32768,-32768,-32768,    95,-32768,   340,
     340,   340,-32768,-32768,-32768,    82,    69,    80,   215,-32768,
  -32768,-32768,-32768,    85,    96,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,   100,-32768,   340,   340,   340,   340,   102,    95,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,    99,-32768,   106,-32768,
  -32768,-32768,-32768,-32768,    17,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,    39,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
     281,-32768,-32768,   110,   108,    79,   106,   106,    36,-32768,
  -32768,-32768,-32768,-32768,-32768,   108,    79,   106,-32768,-32768,
  -32768,   109,-32768,-32768,-32768,    62,   109,-32768,-32768,   109,
  -32768,-32768,     8,-32768,-32768,-32768,-32768,-32768,-32768,    19,
       5,   111,-32768,-32768,   108,    79,   106,   106,   301,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,   112,    62,-32768,-32768,
  -32768,   301,   301,     8,    57,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,   115,-32768,-32768,-32768,
  -32768,   108,    21,-32768,-32768,   122,   123,-32768
};

static const short yypgoto[] =
{
  -32768,  -110,-32768,   117,  -131,-32768,-32768,-32768,     0,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,    84,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
      10,-32768,-32768,-32768,-32768,     1,-32768,-32768,-32768,-32768,
     -21,   -28,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,    74,   -20,-32768,-32768,  -141,
       3,    70,  -124,-32768,  -178,  -158,   -16,  -162,-32768,-32768,
  -32768,-32768
};


#define	YYLAST		439


static const short yytable[] =
{
      12,    15,    36,   193,   190,    21,    22,   219,   201,    12,
      15,    46,   197,    54,    62,    65,     5,   205,    19,     6,
       1,     2,   233,   108,   109,   110,   120,     4,   220,     4,
       4,     4,   191,   121,   122,   123,   238,     7,   192,     7,
      23,     7,     1,     2,   172,   -63,    32,     5,     4,     4,
       6,   195,   206,   207,   196,   228,   243,   239,   229,     7,
       1,     2,     3,   221,   224,     1,     2,     4,     5,   247,
     248,     6,     4,   253,     3,    25,    26,     7,    37,    48,
       5,    34,     7,     6,    35,    49,    50,    47,    51,    66,
     111,   124,   240,   241,   171,   126,   245,   179,   180,   181,
     182,     3,    38,    39,    40,    41,    48,     5,   178,   188,
       6,   113,   114,   115,   116,   183,    48,   202,   203,   222,
     237,   251,   256,   257,   250,   244,    28,   112,   184,     0,
     125,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   213,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   225,     0,     0,     0,   208,     0,
       0,   235,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   230,     0,     0,     0,     0,
     236,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   254,     0,     0,     0,     0,     0,
     128,     0,     0,     0,    12,    15,   249,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   199,     0,     0,     0,
       0,     0,     0,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,     0,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106
};

static const short yycheck[] =
{
       0,     0,    30,   134,   128,     2,     3,   185,   170,     9,
       9,    32,   143,    34,    35,    35,    11,   175,    10,    14,
       3,     4,     3,    39,    40,    41,    47,    10,   186,    10,
      10,    10,    15,    49,    50,    51,   214,    20,    21,    20,
      20,    20,     3,     4,    64,     9,    12,    11,    10,    10,
      14,    12,   176,   177,    15,   196,   218,   215,   199,    20,
       3,     4,     5,   187,   195,     3,     4,    10,    11,   231,
     232,    14,    10,   251,     5,     5,     6,    20,     6,    10,
      11,     8,    20,    14,     8,    16,    17,    12,    19,    10,
      13,     9,   216,   217,     9,    15,   227,   113,   114,   115,
     116,     5,    16,    17,    18,    19,    10,    11,     8,    10,
      14,    16,    17,    18,    19,    13,    10,     7,    10,    10,
       9,     6,     0,     0,   234,    13,     9,    43,   118,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   178,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   195,    -1,    -1,    -1,   178,    -1,
      -1,   209,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   202,    -1,    -1,    -1,    -1,
     210,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   252,    -1,    -1,    -1,    -1,    -1,
      15,    -1,    -1,    -1,   234,   234,   233,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    -1,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99
};
#define YYPURE 1

/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "D:/Development/GNUWin32/share/bison/bison.simple"

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
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

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
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif


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
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
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

#line 315 "D:/Development/GNUWin32/share/bison/bison.simple"


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
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
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
#line 221 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, SKELTEXT); ;
    break;}
case 12:
#line 224 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ if(SKEL != NULL)
                                  SKEL->use(SKELTEXT); ;
    break;}
case 14:
#line 230 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, SKELTEXT); ;
    break;}
case 22:
#line 247 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ if(SKEL != NULL) 
                        SKEL->beginProto(SKELTEXT); ;
    break;}
case 23:
#line 249 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ if(SKEL != NULL) 
                        SKEL->beginProto(SKELTEXT); ;
    break;}
case 24:
#line 260 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ if(SKEL != NULL) 
			SKEL->endProto(); ;
    break;}
case 32:
#line 281 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                      SKELTEXT);;
    break;}
case 33:
#line 283 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ if(SKEL != NULL)
                                              {
                                               SKEL->beginEventInDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 

                                               SKEL->endEventDecl();
                                              }
                                              freeName(szName1); ;
    break;}
case 34:
#line 294 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                      SKELTEXT);;
    break;}
case 35:
#line 296 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ if(SKEL != NULL)
                                              {
                                               SKEL->beginEventOutDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 

                                               SKEL->endEventDecl();
                                              }
                                              freeName(szName1); ;
    break;}
case 36:
#line 307 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                      SKELTEXT);;
    break;}
case 37:
#line 309 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ expectType(nextType); 
                                              if(SKEL != NULL)
                                               SKEL->beginFieldDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 
                                              freeName(szName1); ;
    break;}
case 38:
#line 316 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = 0; 
                                              if(SKEL != NULL)
                                               SKEL->endFieldDecl();
                                             ;
    break;}
case 40:
#line 324 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                              SKELTEXT); ;
    break;}
case 41:
#line 326 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ expectType(nextType);  
                                      if(SKEL != NULL)
                                       SKEL->beginExposedFieldDecl(
                                        szName1,
                                        nextType,
                                        SKELTEXT); 
                                       freeName(szName1); ;
    break;}
case 42:
#line 333 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = 0; 
                                      if(SKEL != NULL)
                                       SKEL->endExposedFieldDecl(); ;
    break;}
case 43:
#line 339 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ if(SKEL != NULL) 
                             SKEL->beginExternProto(SKELTEXT); ;
    break;}
case 44:
#line 344 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{
                 if(SKEL != NULL) 
                     SKEL->endExternProtoInterface(); 

                 expectType(TOK_MFSTRING); 
              ;
    break;}
case 45:
#line 351 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{
                 if(SKEL != NULL) 
                     SKEL->endExternProto(); 
              ;
    break;}
case 50:
#line 367 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                 SKELTEXT); ;
    break;}
case 51:
#line 369 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ if(SKEL != NULL)
                                               SKEL->addExternEventInDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 
                                         freeName(szName1); ;
    break;}
case 52:
#line 376 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                 SKELTEXT); ;
    break;}
case 53:
#line 378 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ if(SKEL != NULL)
                                               SKEL->addExternEventOutDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 
                                          freeName(szName1); ;
    break;}
case 54:
#line 385 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                 SKELTEXT); ;
    break;}
case 55:
#line 387 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ if(SKEL != NULL)
                                               SKEL->addExternFieldDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT); 
                                         freeName(szName1); ;
    break;}
case 56:
#line 394 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                 SKELTEXT); ;
    break;}
case 57:
#line 396 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ if(SKEL != NULL)
                                             SKEL->addExternExposedFieldDecl(
                                                 szName1,
                                                 nextType,
                                                 SKELTEXT); 
                                       freeName(szName1); ;
    break;}
case 58:
#line 405 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, SKELTEXT); ;
    break;}
case 59:
#line 407 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName2, SKELTEXT); ;
    break;}
case 60:
#line 409 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName3, SKELTEXT); ;
    break;}
case 61:
#line 411 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ if(SKEL != NULL)
                                SKEL->addRoute(szName1, 
                                                 szName2,
                                                 szName3,
                                                 SKELTEXT);
                              freeName(szName1);
                              freeName(szName2);
                              freeName(szName3);
                            ;
    break;}
case 64:
#line 428 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ if(SKEL != NULL)
                     SKEL->beginNode(SKELTEXT, szName1); 

                    freeName(szName1);
                  ;
    break;}
case 65:
#line 435 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ if(SKEL != NULL)
                     SKEL->endNode(); ;
    break;}
case 66:
#line 437 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ if(SKEL != NULL)
                     SKEL->beginNode(SKELTEXT, szName1); 

                    freeName(szName1);
                  ;
    break;}
case 67:
#line 444 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ if(SKEL != NULL)
                     SKEL->endNode(); ;
    break;}
case 76:
#line 465 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                          SKELTEXT); ;
    break;}
case 77:
#line 467 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ if(SKEL != NULL)
                                                     SKEL->beginEventInDecl(
                                                       szName1,
                                                       nextType,
                                                       SKELTEXT); 

                                                 freeName(szName1); ;
    break;}
case 78:
#line 475 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                          SKELTEXT); ;
    break;}
case 79:
#line 477 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ if(SKEL != NULL)
                                                     SKEL->beginEventOutDecl(
                                                       szName1,
                                                       nextType,
                                                       SKELTEXT); 

                                                  freeName(szName1); ;
    break;}
case 80:
#line 487 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ 
                                          if(SKEL != NULL)
                                          {
                                             SKEL->is(SKELTEXT);
                                             SKEL->endEventDecl(); 
                                          }
                                        ;
    break;}
case 81:
#line 495 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ 
                                            if(SKEL != NULL)
                                            {
                                                SKEL->endEventDecl(); 
                                            }
                                        ;
    break;}
case 82:
#line 504 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                         SKELTEXT);
                                               ;
    break;}
case 83:
#line 507 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ expectType(nextType); 
                                              
                                                 if(SKEL != NULL)
                                                     SKEL->beginFieldDecl(
                                                       szName1,
                                                       nextType,
                                                       SKELTEXT); 
                                              
                                                 freeName(szName1);
                                               ;
    break;}
case 84:
#line 519 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = 0; 

                                                     if(SKEL != NULL)
                                                     {
                                                       SKEL->is(SKELTEXT);

                                                       SKEL->endFieldDecl();
                                                     }
                                                   ;
    break;}
case 85:
#line 528 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = 0; 

                                                     if(SKEL != NULL)
                                                       SKEL->endFieldDecl();

                                                   ;
    break;}
case 89:
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
                   ;
    break;}
case 93:
#line 581 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ if(SKEL != NULL)
                          {
                            SKEL->is(SKELTEXT);
                            SKEL->endField();
                          }
                        ;
    break;}
case 94:
#line 587 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ if(SKEL != NULL)
                            SKEL->endField();
                        ;
    break;}
case 102:
#line 614 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFCOLOR;    ;
    break;}
case 103:
#line 615 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFFLOAT;    ;
    break;}
case 104:
#line 616 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFINT32;    ;
    break;}
case 105:
#line 617 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFNODE;     ;
    break;}
case 106:
#line 618 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFROTATION; ;
    break;}
case 107:
#line 619 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFSTRING;   ;
    break;}
case 108:
#line 620 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFTIME;     ;
    break;}
case 109:
#line 621 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFVEC2F;    ;
    break;}
case 110:
#line 622 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFVEC3F;    ;
    break;}
case 111:
#line 623 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFBOOL;     ;
    break;}
case 112:
#line 624 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFCOLOR;    ;
    break;}
case 113:
#line 625 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFFLOAT;    ;
    break;}
case 114:
#line 626 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFIMAGE;    ;
    break;}
case 115:
#line 627 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFINT32;    ;
    break;}
case 116:
#line 628 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFNODE;     ;
    break;}
case 117:
#line 629 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFROTATION; ;
    break;}
case 118:
#line 630 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFSTRING;   ;
    break;}
case 119:
#line 631 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFTIME;     ;
    break;}
case 120:
#line 632 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFVEC2F;    ;
    break;}
case 121:
#line 633 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFVEC3F;    ;
    break;}
case 122:
#line 634 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFCOLOR4F;  ;
    break;}
case 123:
#line 635 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFCOLOR4I;  ;
    break;}
case 124:
#line 636 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFCOLOR3F;  ;
    break;}
case 125:
#line 637 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFMATRIX;   ;
    break;}
case 126:
#line 638 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFPNT2F;    ;
    break;}
case 127:
#line 639 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFPNT3F;    ;
    break;}
case 128:
#line 640 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFPNT4F;    ;
    break;}
case 129:
#line 641 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFVEC4F;    ;
    break;}
case 130:
#line 642 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFPLANE;    ;
    break;}
case 131:
#line 643 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFCOLOR4F;  ;
    break;}
case 132:
#line 644 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFCOLOR4I;  ;
    break;}
case 133:
#line 645 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFCOLOR3F;  ;
    break;}
case 134:
#line 646 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFMATRIX;   ;
    break;}
case 135:
#line 647 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFPNT2F;    ;
    break;}
case 136:
#line 648 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFPNT3F;    ;
    break;}
case 137:
#line 649 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFPNT4F;    ;
    break;}
case 138:
#line 650 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFVEC4F;    ;
    break;}
case 139:
#line 651 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFPLANE;    ;
    break;}
case 140:
#line 652 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFVOLUME;   ;
    break;}
case 181:
#line 700 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{
                  if(SKEL != NULL)
                  {
                      SKEL->is(SKELTEXT);
                  }
              ;
    break;}
case 184:
#line 711 "../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y"
{
                  if(SKEL != NULL)
                  {
                      SKEL->is(SKELTEXT);
                  }
              ;
    break;}
}

#line 705 "D:/Development/GNUWin32/share/bison/bison.simple"


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
