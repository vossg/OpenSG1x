
/*  A Bison parser, made from /e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y
    by GNU Bison version 1.28  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse OSGScanParseSkel_parse
#define yylex OSGScanParseSkel_lex
#define yyerror OSGScanParseSkel_error
#define yylval OSGScanParseSkel_lval
#define yychar OSGScanParseSkel_char
#define yydebug OSGScanParseSkel_debug
#define yynerrs OSGScanParseSkel_nerrs
#define	DEF	257
#define	USE	258
#define	ROUTE	259
#define	PERIOD	260
#define	TO	261
#define	OPENBRACE	262
#define	CLOSEBRACE	263
#define	ID	264
#define	PROTO	265
#define	OPENBRACKET	266
#define	CLOSEBRACKET	267
#define	EXTERNPROTO	268
#define	IS	269
#define	EVENTIN	270
#define	EVENTOUT	271
#define	EXPOSEDFIELD	272
#define	FIELD	273
#define	SCRIPT	274
#define	SFN_NULL	275
#define	TOK_SFBOOL	276
#define	TOK_SFCOLOR	277
#define	TOK_SFFLOAT	278
#define	TOK_SFIMAGE	279
#define	TOK_SFINT32	280
#define	TOK_SFNODE	281
#define	TOK_SFROTATION	282
#define	TOK_SFSTRING	283
#define	TOK_SFTIME	284
#define	TOK_SFVEC2F	285
#define	TOK_SFVEC3F	286
#define	TOK_MFCOLOR	287
#define	TOK_MFFLOAT	288
#define	TOK_MFINT32	289
#define	TOK_MFNODE	290
#define	TOK_MFROTATION	291
#define	TOK_MFSTRING	292
#define	TOK_MFTIME	293
#define	TOK_MFVEC2F	294
#define	TOK_MFVEC3F	295
#define	Tok_MFColor	296
#define	Tok_MFFloat	297
#define	Tok_MFInt32	298
#define	Tok_MFNode	299
#define	Tok_MFRotation	300
#define	Tok_MFString	301
#define	Tok_MFTime	302
#define	Tok_MFVec2f	303
#define	Tok_MFVec3f	304
#define	Tok_SFBool	305
#define	Tok_SFColor	306
#define	Tok_SFFloat	307
#define	Tok_SFImage	308
#define	Tok_SFInt32	309
#define	Tok_SFNode	310
#define	Tok_SFRotation	311
#define	Tok_SFString	312
#define	Tok_SFTime	313
#define	Tok_SFVec2f	314
#define	Tok_SFVec3f	315
#define	TOK_MFCOLOR4F	316
#define	TOK_MFMATRIX	317
#define	TOK_MFPNT2F	318
#define	TOK_MFPNT3F	319
#define	TOK_MFPNT4F	320
#define	TOK_MFVEC4F	321
#define	TOK_SFCOLOR4F	322
#define	TOK_SFMATRIX	323
#define	TOK_SFPNT2F	324
#define	TOK_SFPNT3F	325
#define	TOK_SFPNT4F	326
#define	TOK_SFVEC4F	327
#define	Tok_MFColor4f	328
#define	Tok_MFMatrix	329
#define	Tok_MFPnt2f	330
#define	Tok_MFPnt3f	331
#define	Tok_MFPnt4f	332
#define	Tok_MFVec4f	333
#define	Tok_SFColor4f	334
#define	Tok_SFMatrix	335
#define	Tok_SFPnt2f	336
#define	Tok_SFPnt3f	337
#define	Tok_SFPnt4f	338
#define	Tok_SFVec4f	339

#line 38 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"


#include <malloc.h>
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

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		222
#define	YYFLAG		-32768
#define	YYNTBASE	86

#define YYTRANSLATE(x) ((unsigned)(x) <= 339 ? yytranslate[x] : 142)

static const char yytranslate[] = {     0,
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
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     3,     4,     5,     6,
     7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
    17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
    27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
    37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
    47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
    57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
    67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
    77,    78,    79,    80,    81,    82,    83,    84,    85
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     4,     6,     9,    11,    13,    15,    17,    19,
    20,    25,    28,    30,    31,    36,    38,    40,    42,    43,
    46,    48,    49,    50,    61,    63,    65,    69,    71,    73,
    76,    78,    79,    84,    85,    90,    91,    92,    99,   101,
   102,   103,   110,   117,   119,   121,   124,   126,   130,   134,
   138,   142,   143,   144,   145,   157,   159,   160,   161,   167,
   172,   174,   176,   179,   181,   183,   185,   188,   190,   192,
   194,   200,   206,   212,   213,   217,   219,   221,   223,   225,
   227,   229,   231,   233,   235,   237,   239,   241,   243,   245,
   247,   249,   251,   253,   255,   257,   259,   261,   263,   265,
   267,   269,   271,   273,   275,   277,   279,   281,   283,   285,
   287,   289,   291,   293,   295,   297,   299,   301,   303,   305,
   307,   310,   312,   314,   316,   318,   320,   322,   324,   326,
   329,   331,   333,   335,   337,   339,   341,   343,   345,   347,
   349,   351,   353,   355,   357,   359,   361,   363,   365,   367,
   369,   373,   375,   377,   380
};

static const short yyrhs[] = {    87,
     0,    88,     0,   121,     0,    88,    89,     0,    89,     0,
    90,     0,    94,     0,   116,     0,   122,     0,     0,     3,
   131,    91,   122,     0,     4,   131,     0,   122,     0,     0,
     3,   131,    93,   122,     0,    97,     0,   112,     0,    96,
     0,     0,    96,    94,     0,    94,     0,     0,     0,    11,
   132,    98,    12,   102,    13,    99,     8,   100,     9,     0,
   101,     0,   121,     0,    95,    92,    87,     0,   103,     0,
   121,     0,   103,   109,     0,   109,     0,     0,    16,   136,
   105,   134,     0,     0,    17,   136,   106,   135,     0,     0,
     0,    19,   136,   107,   133,   108,   137,     0,   104,     0,
     0,     0,    18,   136,   110,   133,   111,   137,     0,    14,
   132,    12,   113,    13,   120,     0,   114,     0,   121,     0,
   114,   115,     0,   115,     0,    16,   136,   134,     0,    17,
   136,   135,     0,    19,   136,   133,     0,    18,   136,   133,
     0,     0,     0,     0,     5,   131,   117,     6,   135,   118,
     7,   131,   119,     6,   134,     0,   137,     0,     0,     0,
   132,   123,     8,   124,     9,     0,    20,     8,   126,     9,
     0,   125,     0,   121,     0,   125,   129,     0,   129,     0,
   127,     0,   121,     0,   127,   128,     0,   128,     0,   129,
     0,   104,     0,    16,   136,   134,    15,   134,     0,    17,
   136,   135,    15,   135,     0,    19,   136,   133,    15,   133,
     0,     0,   133,   130,   137,     0,   116,     0,    94,     0,
    10,     0,    10,     0,    10,     0,    10,     0,    10,     0,
    10,     0,    42,     0,    43,     0,    44,     0,    45,     0,
    46,     0,    47,     0,    48,     0,    49,     0,    50,     0,
    51,     0,    52,     0,    53,     0,    54,     0,    55,     0,
    56,     0,    57,     0,    58,     0,    59,     0,    60,     0,
    61,     0,    74,     0,    75,     0,    76,     0,    77,     0,
    78,     0,    79,     0,    80,     0,    81,     0,    82,     0,
    83,     0,    84,     0,    85,     0,    22,     0,    23,     0,
    24,     0,    25,     0,    26,     0,    27,   138,     0,    28,
     0,    29,     0,    30,     0,    31,     0,    32,     0,    33,
     0,    34,     0,    35,     0,    36,   139,     0,    37,     0,
    38,     0,    39,     0,    40,     0,    41,     0,    62,     0,
    63,     0,    64,     0,    65,     0,    66,     0,    67,     0,
    68,     0,    69,     0,    70,     0,    71,     0,    72,     0,
    73,     0,    90,     0,    21,     0,    90,     0,    12,   140,
    13,     0,   141,     0,   121,     0,   141,    90,     0,    90,
     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   173,   176,   177,   180,   181,   184,   185,   186,   189,   190,
   193,   193,   198,   199,   202,   204,   205,   209,   210,   213,
   214,   217,   221,   225,   229,   230,   233,   236,   237,   240,
   241,   245,   248,   253,   256,   261,   264,   271,   277,   278,
   281,   288,   293,   301,   302,   305,   307,   310,   311,   312,
   313,   316,   319,   321,   323,   334,   337,   340,   346,   349,
   355,   356,   359,   360,   363,   364,   367,   368,   371,   372,
   373,   374,   375,   378,   398,   401,   402,   407,   410,   413,
   416,   419,   422,   425,   426,   427,   428,   429,   430,   431,
   432,   433,   434,   435,   436,   437,   438,   439,   440,   441,
   442,   443,   444,   445,   446,   447,   448,   449,   450,   451,
   452,   453,   454,   455,   456,   460,   461,   462,   463,   464,
   465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
   475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
   485,   486,   487,   488,   489,   490,   491,   495,   496,   499,
   500,   503,   504,   507,   508
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","DEF","USE",
"ROUTE","PERIOD","TO","OPENBRACE","CLOSEBRACE","ID","PROTO","OPENBRACKET","CLOSEBRACKET",
"EXTERNPROTO","IS","EVENTIN","EVENTOUT","EXPOSEDFIELD","FIELD","SCRIPT","SFN_NULL",
"TOK_SFBOOL","TOK_SFCOLOR","TOK_SFFLOAT","TOK_SFIMAGE","TOK_SFINT32","TOK_SFNODE",
"TOK_SFROTATION","TOK_SFSTRING","TOK_SFTIME","TOK_SFVEC2F","TOK_SFVEC3F","TOK_MFCOLOR",
"TOK_MFFLOAT","TOK_MFINT32","TOK_MFNODE","TOK_MFROTATION","TOK_MFSTRING","TOK_MFTIME",
"TOK_MFVEC2F","TOK_MFVEC3F","Tok_MFColor","Tok_MFFloat","Tok_MFInt32","Tok_MFNode",
"Tok_MFRotation","Tok_MFString","Tok_MFTime","Tok_MFVec2f","Tok_MFVec3f","Tok_SFBool",
"Tok_SFColor","Tok_SFFloat","Tok_SFImage","Tok_SFInt32","Tok_SFNode","Tok_SFRotation",
"Tok_SFString","Tok_SFTime","Tok_SFVec2f","Tok_SFVec3f","TOK_MFCOLOR4F","TOK_MFMATRIX",
"TOK_MFPNT2F","TOK_MFPNT3F","TOK_MFPNT4F","TOK_MFVEC4F","TOK_SFCOLOR4F","TOK_SFMATRIX",
"TOK_SFPNT2F","TOK_SFPNT3F","TOK_SFPNT4F","TOK_SFVEC4F","Tok_MFColor4f","Tok_MFMatrix",
"Tok_MFPnt2f","Tok_MFPnt3f","Tok_MFPnt4f","Tok_MFVec4f","Tok_SFColor4f","Tok_SFMatrix",
"Tok_SFPnt2f","Tok_SFPnt3f","Tok_SFPnt4f","Tok_SFVec4f","vrmlScene","statementsORempty",
"statements","statement","nodeStatement","@1","rootNodeStatement","@2","protoStatement",
"protoStatementsORempty","protoStatements","proto","@3","@4","protoBodyORempty",
"protoBody","interfaceDeclarationsORempty","interfaceDeclarations","restrictedInterfaceDeclaration",
"@5","@6","@7","@8","interfaceDeclaration","@9","@10","externproto","externInterfaceDeclarationsORempty",
"externInterfaceDeclarations","externInterfaceDeclaration","routeStatement",
"@11","@12","@13","URLList","empty","node","@14","nodeBodyORempty","nodeBody",
"scriptBodyORempty","scriptBody","scriptBodyElement","nodeBodyElement","@15",
"nodeNameId","nodeTypeId","fieldId","eventInId","eventOutId","fieldType","fieldValue",
"sfnodeValue","mfnodeValue","nodeStatementsORempty","nodeStatements", NULL
};
#endif

static const short yyr1[] = {     0,
    86,    87,    87,    88,    88,    89,    89,    89,    90,    91,
    90,    90,    92,    93,    92,    94,    94,    95,    95,    96,
    96,    98,    99,    97,   100,   100,   101,   102,   102,   103,
   103,   105,   104,   106,   104,   107,   108,   104,   109,   110,
   111,   109,   112,   113,   113,   114,   114,   115,   115,   115,
   115,   117,   118,   119,   116,   120,   121,   123,   122,   122,
   124,   124,   125,   125,   126,   126,   127,   127,   128,   128,
   128,   128,   128,   130,   129,   129,   129,    -1,   131,   132,
   133,   134,   135,   136,   136,   136,   136,   136,   136,   136,
   136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
   136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
   136,   136,   136,   136,   136,   137,   137,   137,   137,   137,
   137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
   137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
   137,   137,   137,   137,   137,   137,   137,   138,   138,   139,
   139,   140,   140,   141,   141
};

static const short yyr2[] = {     0,
     1,     1,     1,     2,     1,     1,     1,     1,     1,     0,
     4,     2,     1,     0,     4,     1,     1,     1,     0,     2,
     1,     0,     0,    10,     1,     1,     3,     1,     1,     2,
     1,     0,     4,     0,     4,     0,     0,     6,     1,     0,
     0,     6,     6,     1,     1,     2,     1,     3,     3,     3,
     3,     0,     0,     0,    11,     1,     0,     0,     5,     4,
     1,     1,     2,     1,     1,     1,     2,     1,     1,     1,
     5,     5,     5,     0,     3,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     2,     1,     1,     1,     1,     1,     1,     1,     1,     2,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     3,     1,     1,     2,     1
};

static const short yydefact[] = {    57,
     0,     0,     0,    80,     0,     0,     0,     1,     2,     5,
     6,     7,    16,    17,     8,     3,     9,    58,    79,    10,
    12,    52,    22,     0,    57,     4,     0,     0,     0,     0,
    57,    81,     0,     0,     0,    77,    70,    76,    66,     0,
    65,    68,    69,    74,    57,    11,     0,    57,     0,     0,
     0,     0,     0,    44,    47,    45,    84,    85,    86,    87,
    88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
    98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
   108,   109,   110,   111,   112,   113,   114,   115,     0,     0,
     0,    60,    67,     0,    62,     0,    61,    64,    83,    53,
     0,     0,     0,     0,     0,    28,    39,    31,    29,     0,
     0,     0,     0,     0,    46,    82,     0,     0,     0,     0,
     0,     0,   116,   117,   118,   119,   120,     0,   122,   123,
   124,   125,   126,   127,   128,   129,     0,   131,   132,   133,
   134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
   144,   145,   146,   147,    75,    59,    63,     0,    32,    34,
    40,    36,    23,    30,    48,    49,    51,    50,    43,    56,
    33,     0,    35,     0,    37,     0,   149,   148,   121,    57,
   150,   130,     0,     0,     0,    71,    72,     0,    73,   155,
   153,     0,   152,    54,    41,    19,    38,   151,   154,     0,
     0,    21,     0,    18,     0,    25,    26,     0,    42,     0,
    57,    13,    20,    24,    55,    14,    27,     0,    15,     0,
     0,     0
};

static const short yydefgoto[] = {   220,
     8,     9,    10,    11,    28,   211,   218,    36,   203,   204,
    13,    30,   185,   205,   206,   105,   106,    37,   117,   119,
   121,   188,   108,   184,   201,    14,    53,    54,    55,    38,
    29,   158,   200,   169,    16,    17,    27,    96,    97,    40,
    41,    42,    43,    94,    20,    18,    44,   118,   100,    89,
   155,   179,   182,   192,   193
};

static const short yypact[] = {    54,
    12,    12,    12,-32768,    13,    13,    23,-32768,    54,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,    20,    84,-32768,    28,     8,    36,    49,
   119,-32768,   172,   172,   172,-32768,-32768,-32768,-32768,    38,
    84,-32768,-32768,-32768,    35,-32768,    52,   123,   172,   172,
   172,   172,    50,   119,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    65,    52,
    66,-32768,-32768,    87,-32768,    39,    35,-32768,-32768,-32768,
   172,   172,   172,   172,    68,   123,-32768,-32768,-32768,    65,
    52,    66,    66,    87,-32768,-32768,    65,    63,    52,    69,
    66,    76,-32768,-32768,-32768,-32768,-32768,    31,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,    67,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,    78,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,    65,-32768,    52,-32768,    66,-32768,-32768,-32768,    40,
-32768,-32768,    12,    66,    75,-32768,-32768,    87,-32768,-32768,
-32768,    80,    40,-32768,-32768,   120,-32768,-32768,-32768,    91,
    87,-32768,    70,     5,    95,-32768,-32768,    65,-32768,    12,
    54,-32768,-32768,-32768,-32768,-32768,-32768,     8,-32768,   130,
   132,-32768
};

static const short yypgoto[] = {-32768,
   -78,-32768,   134,  -111,-32768,-32768,-32768,     0,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,   -34,-32768,-32768,
-32768,-32768,    41,-32768,-32768,-32768,-32768,-32768,    90,     1,
-32768,-32768,-32768,-32768,   -18,   -26,-32768,-32768,-32768,-32768,
-32768,   104,   -30,-32768,     3,    15,   -88,  -106,   -82,     4,
  -102,-32768,-32768,-32768,-32768
};


#define	YYLAST		257


static const short yytable[] = {    12,
    15,    46,   122,   165,    21,    22,    39,   120,    12,    15,
   171,   170,    56,   107,    98,     5,   178,     4,     6,    23,
    24,    19,     4,   167,   168,   181,    95,     7,   166,   109,
    25,    31,   175,     1,     2,    45,   173,    90,    91,     3,
     4,    47,     1,     2,    32,     5,    92,   156,     6,     4,
     7,   177,   110,   111,   112,   113,     1,     2,     3,     7,
    48,    99,   114,     4,     5,   186,   157,     6,   190,     1,
     2,   107,   210,     7,   116,    32,     4,   172,   180,     4,
   163,   199,   196,   174,   183,   197,     7,   189,     3,     7,
   176,   187,   198,    32,     5,   195,   208,     6,   209,    33,
    34,   215,    35,   214,   159,   160,   161,   162,   123,   124,
   125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
   135,   136,   137,   138,   139,   140,   141,   142,   -57,   221,
     5,   222,   217,     6,    49,    50,    51,    52,   101,   102,
   103,   104,    26,   115,    93,     0,   164,     0,   143,   144,
   145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     0,   191,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   212,   207,     0,     0,
     0,     0,     0,     0,     0,   194,     0,     0,     0,     0,
     0,   219,     0,     0,     0,   202,     0,     0,     0,     0,
     0,     0,     0,   213,     0,     0,     0,     0,     0,     0,
    12,    15,   216,    57,    58,    59,    60,    61,    62,    63,
    64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
    74,    75,    76,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    77,    78,    79,    80,    81,
    82,    83,    84,    85,    86,    87,    88
};

static const short yycheck[] = {     0,
     0,    28,    91,   110,     2,     3,    25,    90,     9,     9,
   117,   114,    31,    48,    45,    11,   128,    10,    14,     5,
     6,    10,    10,   112,   113,   137,    45,    20,   111,    48,
     8,    12,   121,     3,     4,     8,   119,    34,    35,     5,
    10,     6,     3,     4,    10,    11,     9,     9,    14,    10,
    20,    21,    49,    50,    51,    52,     3,     4,     5,    20,
    12,    10,    13,    10,    11,   172,    97,    14,   180,     3,
     4,   106,     3,    20,    10,    10,    10,    15,    12,    10,
    13,   193,     8,    15,     7,   188,    20,   176,     5,    20,
    15,   174,    13,    10,    11,   184,     6,    14,   201,    16,
    17,   208,    19,     9,   101,   102,   103,   104,    22,    23,
    24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
    34,    35,    36,    37,    38,    39,    40,    41,     9,     0,
    11,     0,   211,    14,    16,    17,    18,    19,    16,    17,
    18,    19,     9,    54,    41,    -1,   106,    -1,    62,    63,
    64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
    -1,   180,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,   203,   196,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,   183,    -1,    -1,    -1,    -1,
    -1,   218,    -1,    -1,    -1,   196,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,   204,    -1,    -1,    -1,    -1,    -1,    -1,
   211,   211,   210,    42,    43,    44,    45,    46,    47,    48,
    49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
    59,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    74,    75,    76,    77,    78,
    79,    80,    81,    82,    83,    84,    85
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison.simple"
/* This file comes from bison-1.28.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

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

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
#ifdef alloca
#define YYSTACK_USE_ALLOCA
#else /* alloca not defined */
#ifdef __GNUC__
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#define YYSTACK_USE_ALLOCA
#include <alloca.h>
#else /* not sparc */
/* We think this test detects Watcom and Microsoft C.  */
/* This used to test MSDOS, but that is a bad idea
   since that symbol is in the user namespace.  */
#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#if 0 /* No need for malloc.h, which pollutes the namespace;
	 instead, just don't use alloca.  */
#include <malloc.h>
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
/* I don't know what this was needed for, but it pollutes the namespace.
   So I turned it off.   rms, 2 May 1997.  */
/* #include <malloc.h>  */
 #pragma alloca
#define YYSTACK_USE_ALLOCA
#else /* not MSDOS, or __TURBOC__, or _AIX */
#if 0
#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
		 and on HPUX 10.  Eventually we can turn this on.  */
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#endif /* __hpux */
#endif
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc */
#endif /* not GNU C */
#endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#ifdef YYSTACK_USE_ALLOCA
#define YYSTACK_ALLOC alloca
#else
#define YYSTACK_ALLOC malloc
#endif

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Define __yy_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     unsigned int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, unsigned int count)
{
  register char *t = to;
  register char *f = from;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 217 "/usr/share/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
#ifdef YYPARSE_PARAM
int yyparse (void *);
#else
int yyparse (void);
#endif
#endif

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;
  int yyfree_stacks = 0;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  if (yyfree_stacks)
	    {
	      free (yyss);
	      free (yyvs);
#ifdef YYLSP_NEEDED
	      free (yyls);
#endif
	    }
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
#ifndef YYSTACK_USE_ALLOCA
      yyfree_stacks = 1;
#endif
      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1,
		   size * (unsigned int) sizeof (*yyssp));
      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
		   size * (unsigned int) sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1,
		   size * (unsigned int) sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
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
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
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

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
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
#line 191 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, OSGScanParseSkel_text); ;
    break;}
case 12:
#line 194 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                                  _pSkel->use(OSGScanParseSkel_text); ;
    break;}
case 14:
#line 200 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, OSGScanParseSkel_text); ;
    break;}
case 22:
#line 218 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL) 
                        _pSkel->beginProtoInterface(OSGScanParseSkel_text); ;
    break;}
case 23:
#line 222 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL) 
                        _pSkel->endProtoInterface(); ;
    break;}
case 32:
#line 246 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                      OSGScanParseSkel_text); ;
    break;}
case 33:
#line 248 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                                               _pSkel->addProtoEventIn(
                                                szName1,
                                                OSGScanParseSkel_text); 
                                              freeName(szName1); ;
    break;}
case 34:
#line 254 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                      OSGScanParseSkel_text); ;
    break;}
case 35:
#line 256 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                                               _pSkel->addProtoEventOut(
                                                szName1,
                                                OSGScanParseSkel_text); 
                                              freeName(szName1); ;
    break;}
case 36:
#line 262 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                                      OSGScanParseSkel_text); ;
    break;}
case 37:
#line 264 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ expectType(nextType); 
                                              if(_pSkel != NULL)
                                               _pSkel->beginProtoField(
                                                szName1,
                                                nextType,
                                                OSGScanParseSkel_text); 
                                              freeName(szName1); ;
    break;}
case 38:
#line 271 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = 0; 
                                              if(_pSkel != NULL)
                                               _pSkel->endProtoField();
                                             ;
    break;}
case 40:
#line 279 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, 
                                              OSGScanParseSkel_text); ;
    break;}
case 41:
#line 281 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ expectType(nextType);  
                                      if(_pSkel != NULL)
                                       _pSkel->beginProtoExposedField(
                                        szName1,
                                        nextType,
                                        OSGScanParseSkel_text); 
                                       freeName(szName1); ;
    break;}
case 42:
#line 288 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = 0; 
                                      if(_pSkel != NULL)
                                       _pSkel->endProtoExposedField(); ;
    break;}
case 52:
#line 317 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName1, OSGScanParseSkel_text); ;
    break;}
case 53:
#line 319 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName2, OSGScanParseSkel_text); ;
    break;}
case 54:
#line 321 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ setName(szName3, OSGScanParseSkel_text); ;
    break;}
case 55:
#line 323 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
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
#line 340 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                     _pSkel->beginNode(OSGScanParseSkel_text, szName1); 

                    freeName(szName1);
                  ;
    break;}
case 59:
#line 347 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                     _pSkel->endNode(); ;
    break;}
case 74:
#line 379 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                    {
                     Int32 iFieldTypeId;

                     iFieldTypeId = _pSkel->getFieldType(
                                        OSGScanParseSkel_text);

                     if(_pSkel->getMapFieldTypes() == true)
                     {
                      iFieldTypeId = _pSkel->mapExtIntFieldType(iFieldTypeId);
                     }
    
                     expectType(iFieldTypeId); 

                     _pSkel->beginField(OSGScanParseSkel_text, 
                                        iFieldTypeId);
                    } 
                   ;
    break;}
case 75:
#line 398 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ if(_pSkel != NULL)
                     _pSkel->endField();
                  ;
    break;}
case 84:
#line 425 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFCOLOR;    ;
    break;}
case 85:
#line 426 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFFLOAT;    ;
    break;}
case 86:
#line 427 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFINT32;    ;
    break;}
case 87:
#line 428 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFNODE;     ;
    break;}
case 88:
#line 429 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFROTATION; ;
    break;}
case 89:
#line 430 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFSTRING;   ;
    break;}
case 90:
#line 431 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFTIME;     ;
    break;}
case 91:
#line 432 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFVEC2F;    ;
    break;}
case 92:
#line 433 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFVEC3F;    ;
    break;}
case 93:
#line 434 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFBOOL;     ;
    break;}
case 94:
#line 435 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFCOLOR;    ;
    break;}
case 95:
#line 436 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFFLOAT;    ;
    break;}
case 96:
#line 437 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFIMAGE;    ;
    break;}
case 97:
#line 438 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFINT32;    ;
    break;}
case 98:
#line 439 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFNODE;     ;
    break;}
case 99:
#line 440 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFROTATION; ;
    break;}
case 100:
#line 441 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFSTRING;   ;
    break;}
case 101:
#line 442 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFTIME;     ;
    break;}
case 102:
#line 443 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFVEC2F;    ;
    break;}
case 103:
#line 444 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFVEC3F;    ;
    break;}
case 104:
#line 445 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFCOLOR4F;  ;
    break;}
case 105:
#line 446 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFMATRIX;   ;
    break;}
case 106:
#line 447 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFPNT2F;    ;
    break;}
case 107:
#line 448 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFPNT3F;    ;
    break;}
case 108:
#line 449 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFPNT4F;    ;
    break;}
case 109:
#line 450 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_MFVEC4F;    ;
    break;}
case 110:
#line 451 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFCOLOR4F;  ;
    break;}
case 111:
#line 452 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFMATRIX;   ;
    break;}
case 112:
#line 453 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFPNT2F;    ;
    break;}
case 113:
#line 454 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFPNT3F;    ;
    break;}
case 114:
#line 455 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFPNT4F;    ;
    break;}
case 115:
#line 456 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"
{ nextType = TOK_SFVEC4F;    ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 543 "/usr/share/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
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

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
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
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

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

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;

 yyacceptlab:
  /* YYACCEPT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 0;

 yyabortlab:
  /* YYABORT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 1;
}
#line 512 "/e/user/gerrit/Projects/OpenSG/OpenSG/Experimental/ScanParseSkel/OSGScanParseSkel.y"


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


