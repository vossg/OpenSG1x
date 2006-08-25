
/*  A Bison parser, made from ../../../source/system/fileio/scanparseskel/osgscanparseskel.y with Bison version GNU Bison version 1.24
  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse OSGScanParseSkel_parse
#define yylex OSGScanParseSkel_lex
#define yyerror OSGScanParseSkel_error
#define yylval OSGScanParseSkel_lval
#define yychar OSGScanParseSkel_char
#define yydebug OSGScanParseSkel_debug
#define yynerrs OSGScanParseSkel_nerrs
#define	UTF8BOM	258
#define	DEF	259
#define	USE	260
#define	ROUTE	261
#define	PERIOD	262
#define	TO	263
#define	OPENBRACE	264
#define	CLOSEBRACE	265
#define	ID	266
#define	PROTO	267
#define	OPENBRACKET	268
#define	CLOSEBRACKET	269
#define	EXTERNPROTO	270
#define	IS	271
#define	EXPORT	272
#define	IMPORT	273
#define	PROFILE	274
#define	COMPONENT	275
#define	COMPONENTID	276
#define	OSG_META	277
#define	AS	278
#define	EVENTIN	279
#define	EVENTOUT	280
#define	EXPOSEDFIELD	281
#define	FIELD	282
#define	SCRIPT	283
#define	SFN_NULL	284
#define	TOK_SFBOOL	285
#define	TOK_SFCOLOR	286
#define	TOK_SFCOLORRGBA	287
#define	TOK_SFDOUBLE	288
#define	TOK_SFFLOAT	289
#define	TOK_SFIMAGE	290
#define	TOK_SFINT32	291
#define	TOK_SFMATRIX3D	292
#define	TOK_SFMATRIX3F	293
#define	TOK_SFMATRIX4D	294
#define	TOK_SFMATRIX4F	295
#define	TOK_SFNODE	296
#define	TOK_SFROTATION	297
#define	TOK_SFSTRING	298
#define	TOK_SFTIME	299
#define	TOK_SFVEC2D	300
#define	TOK_SFVEC2F	301
#define	TOK_SFVEC3D	302
#define	TOK_SFVEC3F	303
#define	TOK_SFVEC4D	304
#define	TOK_SFVEC4F	305
#define	TOK_MFBOOL	306
#define	TOK_MFCOLOR	307
#define	TOK_MFCOLORRGBA	308
#define	TOK_MFDOUBLE	309
#define	TOK_MFFLOAT	310
#define	TOK_MFIMAGE	311
#define	TOK_MFINT32	312
#define	TOK_MFMATRIX3D	313
#define	TOK_MFMATRIX3F	314
#define	TOK_MFMATRIX4D	315
#define	TOK_MFMATRIX4F	316
#define	TOK_MFNODE	317
#define	TOK_MFROTATION	318
#define	TOK_MFSTRING	319
#define	TOK_MFTIME	320
#define	TOK_MFVEC2D	321
#define	TOK_MFVEC2F	322
#define	TOK_MFVEC3D	323
#define	TOK_MFVEC3F	324
#define	TOK_MFVEC4D	325
#define	TOK_MFVEC4F	326
#define	Tok_MFBool	327
#define	Tok_MFColor	328
#define	Tok_MFColorRGBA	329
#define	Tok_MFDouble	330
#define	Tok_MFFloat	331
#define	Tok_MFImage	332
#define	Tok_MFInt32	333
#define	Tok_MFMatrix3d	334
#define	Tok_MFMatrix3f	335
#define	Tok_MFMatrix4d	336
#define	Tok_MFMatrix4f	337
#define	Tok_MFNode	338
#define	Tok_MFRotation	339
#define	Tok_MFString	340
#define	Tok_MFTime	341
#define	Tok_MFVec2d	342
#define	Tok_MFVec2f	343
#define	Tok_MFVec3d	344
#define	Tok_MFVec3f	345
#define	Tok_MFVec4d	346
#define	Tok_MFVec4f	347
#define	Tok_SFBool	348
#define	Tok_SFColor	349
#define	Tok_SFColorRGBA	350
#define	Tok_SFDouble	351
#define	Tok_SFFloat	352
#define	Tok_SFImage	353
#define	Tok_SFInt32	354
#define	Tok_SFMatrix3d	355
#define	Tok_SFMatrix3f	356
#define	Tok_SFMatrix4d	357
#define	Tok_SFMatrix4f	358
#define	Tok_SFNode	359
#define	Tok_SFRotation	360
#define	Tok_SFString	361
#define	Tok_SFTime	362
#define	Tok_SFVec2d	363
#define	Tok_SFVec2f	364
#define	Tok_SFVec3d	365
#define	Tok_SFVec3f	366
#define	Tok_SFVec4d	367
#define	Tok_SFVec4f	368
#define	TOK_MFCOLOR4I	369
#define	TOK_MFPNT2F	370
#define	TOK_MFPNT3F	371
#define	TOK_MFPNT4F	372
#define	TOK_MFPLANE	373
#define	TOK_SFCOLOR4I	374
#define	TOK_SFPNT2F	375
#define	TOK_SFPNT3F	376
#define	TOK_SFPNT4F	377
#define	TOK_SFPLANE	378
#define	TOK_SFVOLUME	379
#define	Tok_MFColor4i	380
#define	Tok_MFPnt2f	381
#define	Tok_MFPnt3f	382
#define	Tok_MFPnt4f	383
#define	Tok_MFPlane	384
#define	Tok_SFColor4i	385
#define	Tok_SFPnt2f	386
#define	Tok_SFPnt3f	387
#define	Tok_SFPnt4f	388
#define	Tok_SFPlane	389
#define	Tok_SFVolume	390

#line 38 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"


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

#if(!defined(__GNUC__) && defined(__ICL) && __INTEL_COMPILER_VERSION >= 900)
# define alloca(size)   __builtin_alloca (size)
#endif


#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		329
#define	YYFLAG		-32768
#define	YYNTBASE	136

#define YYTRANSLATE(x) ((unsigned)(x) <= 390 ? yytranslate[x] : 224)

static const short yytranslate[] = {     0,
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
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
    46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
    56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
    66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
    76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
    86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
    96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
   106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
   116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
   126,   127,   128,   129,   130,   131,   132,   133,   134,   135
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     3,     5,     6,    11,    13,    16,    18,    21,    23,
    26,    29,    31,    34,    36,    37,    42,    44,    46,    49,
    51,    53,    55,    57,    59,    61,    63,    64,    69,    72,
    74,    75,    80,    82,    84,    86,    87,    90,    92,    94,
    96,   105,   107,   109,   113,   115,   117,   120,   122,   123,
   128,   129,   134,   135,   136,   143,   145,   146,   147,   154,
   155,   156,   165,   167,   169,   172,   174,   175,   180,   181,
   186,   187,   192,   193,   198,   199,   200,   201,   213,   214,
   219,   220,   221,   229,   232,   234,   236,   237,   238,   244,
   245,   251,   253,   255,   258,   260,   261,   266,   267,   272,
   275,   276,   277,   282,   285,   287,   288,   293,   296,   298,
   300,   303,   306,   309,   310,   314,   316,   318,   321,   323,
   325,   327,   329,   331,   333,   335,   337,   339,   341,   343,
   345,   347,   349,   351,   353,   355,   357,   359,   361,   363,
   365,   367,   369,   371,   373,   375,   377,   379,   381,   383,
   385,   387,   389,   391,   393,   395,   397,   399,   401,   403,
   405,   407,   409,   411,   413,   415,   417,   419,   421,   423,
   425,   427,   429,   431,   433,   435,   437,   439,   441,   443,
   445,   447,   449,   451,   453,   455,   457,   459,   461,   463,
   465,   468,   470,   472,   474,   476,   478,   480,   482,   484,
   486,   488,   490,   492,   494,   496,   498,   500,   502,   504,
   506,   508,   511,   513,   515,   517,   519,   521,   523,   525,
   527,   529,   531,   533,   535,   537,   539,   541,   543,   545,
   547,   549,   551,   553,   556,   558,   560,   563,   567,   569,
   571,   574
};

static const short yyrhs[] = {     3,
   137,     0,   137,     0,     0,    19,    11,   138,   139,     0,
   139,     0,   140,   142,     0,   142,     0,   140,   141,     0,
   141,     0,    20,    21,     0,   143,   146,     0,   146,     0,
   143,   144,     0,   144,     0,     0,    22,    11,   145,    11,
     0,   147,     0,   191,     0,   147,   148,     0,   148,     0,
   149,     0,   153,     0,   180,     0,   186,     0,   184,     0,
   192,     0,     0,     4,   212,   150,   192,     0,     5,   212,
     0,   192,     0,     0,     4,   212,   152,   192,     0,   157,
     0,   170,     0,   155,     0,     0,   155,   153,     0,   153,
     0,   213,     0,    28,     0,    12,   156,    13,   160,    14,
     9,   158,    10,     0,   159,     0,   191,     0,   154,   151,
   146,     0,   161,     0,   191,     0,   161,   167,     0,   167,
     0,     0,    24,   218,   163,   216,     0,     0,    25,   218,
   164,   217,     0,     0,     0,    27,   218,   165,   214,   166,
   219,     0,   162,     0,     0,     0,    26,   218,   168,   214,
   169,   219,     0,     0,     0,    15,   213,   171,    13,   173,
    14,   172,   190,     0,   174,     0,   191,     0,   174,   175,
     0,   175,     0,     0,    24,   218,   176,   216,     0,     0,
    25,   218,   177,   217,     0,     0,    27,   218,   178,   214,
     0,     0,    26,   218,   179,   214,     0,     0,     0,     0,
     6,   212,   181,     7,   217,   182,     8,   212,   183,     7,
   216,     0,     0,    17,    11,   185,   189,     0,     0,     0,
    18,    11,   187,     7,    11,   188,   189,     0,    23,    11,
     0,   191,     0,   219,     0,     0,     0,   213,   193,     9,
   195,    10,     0,     0,    28,   194,     9,   195,    10,     0,
   196,     0,   191,     0,   196,   207,     0,   207,     0,     0,
    24,   218,   198,   216,     0,     0,    25,   218,   199,   217,
     0,    16,   215,     0,     0,     0,    27,   218,   202,   214,
     0,    16,   214,     0,   219,     0,     0,    26,   218,   205,
   214,     0,    16,   214,     0,   219,     0,   208,     0,   197,
   200,     0,   201,   203,     0,   204,   206,     0,     0,   214,
   209,   210,     0,   180,     0,   153,     0,    16,   211,     0,
   219,     0,    11,     0,    11,     0,    11,     0,    11,     0,
    11,     0,    11,     0,    11,     0,    72,     0,    73,     0,
    74,     0,    75,     0,    76,     0,    77,     0,    78,     0,
    79,     0,    80,     0,    81,     0,    82,     0,    83,     0,
    84,     0,    85,     0,    86,     0,    87,     0,    88,     0,
    89,     0,    90,     0,    91,     0,    92,     0,    93,     0,
    94,     0,    95,     0,    96,     0,    97,     0,    98,     0,
    99,     0,   100,     0,   101,     0,   102,     0,   103,     0,
   104,     0,   105,     0,   106,     0,   107,     0,   108,     0,
   109,     0,   110,     0,   111,     0,   112,     0,   113,     0,
   125,     0,   126,     0,   127,     0,   128,     0,   129,     0,
   130,     0,   131,     0,   132,     0,   133,     0,   134,     0,
   135,     0,    30,     0,    31,     0,    32,     0,    33,     0,
    34,     0,    35,     0,    36,     0,    37,     0,    38,     0,
    39,     0,    40,     0,    41,   220,     0,    42,     0,    43,
     0,    44,     0,    45,     0,    46,     0,    47,     0,    48,
     0,    49,     0,    50,     0,    51,     0,    52,     0,    53,
     0,    54,     0,    55,     0,    56,     0,    57,     0,    58,
     0,    59,     0,    60,     0,    61,     0,    62,   221,     0,
    63,     0,    64,     0,    65,     0,    66,     0,    67,     0,
    68,     0,    69,     0,    70,     0,    71,     0,   114,     0,
   115,     0,   116,     0,   117,     0,   118,     0,   119,     0,
   120,     0,   121,     0,   122,     0,   123,     0,   124,     0,
   149,     0,    16,   211,     0,    29,     0,   149,     0,    16,
   211,     0,    13,   222,    14,     0,   223,     0,   191,     0,
   223,   149,     0,   149,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   237,   238,   241,   250,   250,   254,   255,   258,   259,   262,
   272,   273,   276,   277,   280,   283,   292,   293,   296,   297,
   300,   301,   302,   303,   304,   307,   308,   311,   311,   316,
   317,   320,   322,   323,   327,   328,   331,   332,   335,   337,
   341,   352,   353,   356,   359,   360,   363,   364,   368,   371,
   381,   384,   394,   397,   404,   410,   411,   414,   421,   426,
   430,   439,   445,   446,   449,   451,   454,   457,   463,   466,
   472,   475,   481,   484,   492,   495,   497,   499,   510,   516,
   527,   533,   538,   550,   554,   557,   560,   563,   572,   575,
   581,   596,   597,   600,   601,   604,   607,   614,   617,   626,
   634,   643,   647,   659,   668,   676,   680,   693,   703,   720,
   721,   723,   725,   730,   752,   752,   753,   758,   764,   771,
   774,   777,   780,   783,   786,   789,   792,   793,   794,   795,
   796,   797,   798,   799,   800,   801,   802,   803,   804,   805,
   806,   807,   808,   809,   810,   811,   812,   813,   814,   815,
   816,   817,   818,   819,   820,   821,   822,   823,   824,   825,
   826,   827,   828,   829,   830,   831,   832,   833,   834,   835,
   836,   837,   838,   839,   840,   841,   842,   843,   844,   848,
   849,   850,   851,   852,   853,   854,   855,   856,   857,   858,
   859,   860,   861,   862,   863,   864,   865,   866,   867,   868,
   869,   870,   871,   872,   873,   874,   875,   876,   877,   878,
   879,   880,   881,   882,   883,   884,   885,   886,   887,   888,
   889,   890,   891,   892,   893,   894,   895,   896,   897,   898,
   899,   900,   904,   905,   912,   915,   916,   923,   926,   927,
   930,   931
};

static const char * const yytname[] = {   "$","error","$undefined.","UTF8BOM",
"DEF","USE","ROUTE","PERIOD","TO","OPENBRACE","CLOSEBRACE","ID","PROTO","OPENBRACKET",
"CLOSEBRACKET","EXTERNPROTO","IS","EXPORT","IMPORT","PROFILE","COMPONENT","COMPONENTID",
"OSG_META","AS","EVENTIN","EVENTOUT","EXPOSEDFIELD","FIELD","SCRIPT","SFN_NULL",
"TOK_SFBOOL","TOK_SFCOLOR","TOK_SFCOLORRGBA","TOK_SFDOUBLE","TOK_SFFLOAT","TOK_SFIMAGE",
"TOK_SFINT32","TOK_SFMATRIX3D","TOK_SFMATRIX3F","TOK_SFMATRIX4D","TOK_SFMATRIX4F",
"TOK_SFNODE","TOK_SFROTATION","TOK_SFSTRING","TOK_SFTIME","TOK_SFVEC2D","TOK_SFVEC2F",
"TOK_SFVEC3D","TOK_SFVEC3F","TOK_SFVEC4D","TOK_SFVEC4F","TOK_MFBOOL","TOK_MFCOLOR",
"TOK_MFCOLORRGBA","TOK_MFDOUBLE","TOK_MFFLOAT","TOK_MFIMAGE","TOK_MFINT32","TOK_MFMATRIX3D",
"TOK_MFMATRIX3F","TOK_MFMATRIX4D","TOK_MFMATRIX4F","TOK_MFNODE","TOK_MFROTATION",
"TOK_MFSTRING","TOK_MFTIME","TOK_MFVEC2D","TOK_MFVEC2F","TOK_MFVEC3D","TOK_MFVEC3F",
"TOK_MFVEC4D","TOK_MFVEC4F","Tok_MFBool","Tok_MFColor","Tok_MFColorRGBA","Tok_MFDouble",
"Tok_MFFloat","Tok_MFImage","Tok_MFInt32","Tok_MFMatrix3d","Tok_MFMatrix3f",
"Tok_MFMatrix4d","Tok_MFMatrix4f","Tok_MFNode","Tok_MFRotation","Tok_MFString",
"Tok_MFTime","Tok_MFVec2d","Tok_MFVec2f","Tok_MFVec3d","Tok_MFVec3f","Tok_MFVec4d",
"Tok_MFVec4f","Tok_SFBool","Tok_SFColor","Tok_SFColorRGBA","Tok_SFDouble","Tok_SFFloat",
"Tok_SFImage","Tok_SFInt32","Tok_SFMatrix3d","Tok_SFMatrix3f","Tok_SFMatrix4d",
"Tok_SFMatrix4f","Tok_SFNode","Tok_SFRotation","Tok_SFString","Tok_SFTime","Tok_SFVec2d",
"Tok_SFVec2f","Tok_SFVec3d","Tok_SFVec3f","Tok_SFVec4d","Tok_SFVec4f","TOK_MFCOLOR4I",
"TOK_MFPNT2F","TOK_MFPNT3F","TOK_MFPNT4F","TOK_MFPLANE","TOK_SFCOLOR4I","TOK_SFPNT2F",
"TOK_SFPNT3F","TOK_SFPNT4F","TOK_SFPLANE","TOK_SFVOLUME","Tok_MFColor4i","Tok_MFPnt2f",
"Tok_MFPnt3f","Tok_MFPnt4f","Tok_MFPlane","Tok_SFColor4i","Tok_SFPnt2f","Tok_SFPnt3f",
"Tok_SFPnt4f","Tok_SFPlane","Tok_SFVolume","vrmlScene","profileStatement","@1",
"componentStatements","componentStatementsRec","componentStatement","metaStatements",
"metaStatementsRec","metaStatement","@2","statementsORempty","statements","statement",
"nodeStatement","@3","rootNodeStatement","@4","protoStatement","protoStatementsORempty",
"protoStatements","protoId","proto","protoBodyORempty","protoBody","interfaceDeclarationsORempty",
"interfaceDeclarations","restrictedInterfaceDeclaration","@5","@6","@7","@8",
"interfaceDeclaration","@9","@10","externproto","@11","@12","externInterfaceDeclarationsORempty",
"externInterfaceDeclarations","externInterfaceDeclaration","@13","@14","@15",
"@16","routeStatement","@17","@18","@19","exportStatement","@20","importStatement",
"@21","@22","importExportEnd","URLList","empty","node","@23","@24","scriptBodyORempty",
"scriptBody","resInterfaceDeclarationScriptEvent","@25","@26","resInterfaceDeclarationScriptEventEnd",
"resInterfaceDeclarationScriptField","@27","resInterafceDeclarationScriptFieldEnd",
"resInterfaceDeclarationScriptExpField","@28","resInterafceDeclarationScriptExpFieldEnd",
"scriptBodyElement","nodeBodyElement","@29","fieldEnd","generalId","nodeNameId",
"nodeTypeId","fieldId","eventId","eventInId","eventOutId","fieldType","fieldValue",
"sfnodeValue","mfnodeValue","nodeStatementsORempty","nodeStatements",""
};
#endif

static const short yyr1[] = {     0,
   136,   136,   138,   137,   137,   139,   139,   140,   140,   141,
   142,   142,   143,   143,   145,   144,   146,   146,   147,   147,
   148,   148,   148,   148,   148,   149,   150,   149,   149,   151,
   152,   151,   153,   153,   154,   154,   155,   155,   156,   156,
   157,   158,   158,   159,   160,   160,   161,   161,   163,   162,
   164,   162,   165,   166,   162,   167,   168,   169,   167,   171,
   172,   170,   173,   173,   174,   174,   176,   175,   177,   175,
   178,   175,   179,   175,   181,   182,   183,   180,   185,   184,
   187,   188,   186,   189,   189,   190,   191,   193,   192,   194,
   192,   195,   195,   196,   196,   198,   197,   199,   197,   200,
   200,   202,   201,   203,   203,   205,   204,   206,   206,   207,
   207,   207,   207,   209,   208,   208,   208,   210,   210,   211,
   212,   213,   214,   215,   216,   217,   218,   218,   218,   218,
   218,   218,   218,   218,   218,   218,   218,   218,   218,   218,
   218,   218,   218,   218,   218,   218,   218,   218,   218,   218,
   218,   218,   218,   218,   218,   218,   218,   218,   218,   218,
   218,   218,   218,   218,   218,   218,   218,   218,   218,   218,
   218,   218,   218,   218,   218,   218,   218,   218,   218,   219,
   219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
   219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
   219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
   219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
   219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
   219,   219,   220,   220,   220,   221,   221,   221,   222,   222,
   223,   223
};

static const short yyr2[] = {     0,
     2,     1,     0,     4,     1,     2,     1,     2,     1,     2,
     2,     1,     2,     1,     0,     4,     1,     1,     2,     1,
     1,     1,     1,     1,     1,     1,     0,     4,     2,     1,
     0,     4,     1,     1,     1,     0,     2,     1,     1,     1,
     8,     1,     1,     3,     1,     1,     2,     1,     0,     4,
     0,     4,     0,     0,     6,     1,     0,     0,     6,     0,
     0,     8,     1,     1,     2,     1,     0,     4,     0,     4,
     0,     4,     0,     4,     0,     0,     0,    11,     0,     4,
     0,     0,     7,     2,     1,     1,     0,     0,     5,     0,
     5,     1,     1,     2,     1,     0,     4,     0,     4,     2,
     0,     0,     4,     2,     1,     0,     4,     2,     1,     1,
     2,     2,     2,     0,     3,     1,     1,     2,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     2,     1,     1,     2,     3,     1,     1,
     2,     1
};

static const short yydefact[] = {    87,
    87,     0,     0,     0,   122,     0,     0,     0,     0,     0,
     0,     0,    90,     2,     5,    87,     9,     7,    87,    14,
    12,    17,    20,    21,    22,    33,    34,    23,    25,    24,
    18,    26,    88,     1,   121,    27,    29,    75,    40,     0,
    39,    60,    79,    81,     3,    10,    15,     0,     8,     6,
    13,    11,    19,     0,     0,     0,    87,     0,    87,     0,
    87,     0,    87,    87,    28,     0,     0,     0,     0,     0,
     0,    45,    56,    48,    46,    87,     0,    80,    85,     0,
     4,    16,   123,     0,     0,     0,     0,   117,   116,    93,
     0,    92,   101,     0,     0,    95,   110,   114,     0,   126,
    76,   127,   128,   129,   130,   131,   132,   133,   134,   135,
   136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
   146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
   156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
   166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
   176,   177,   178,   179,    49,    51,    57,    53,     0,    47,
     0,     0,     0,     0,     0,    63,    66,    64,    84,    82,
    96,    98,   106,   102,    91,    94,     0,   111,     0,   180,
   181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     0,   192,   193,   194,   195,   196,   197,   198,   199,   200,
   201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
   211,     0,   213,   214,   215,   216,   217,   218,   219,   220,
   221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
   231,   232,   112,   105,     0,   113,   109,     0,    89,     0,
     0,     0,     0,     0,    36,    67,    69,    73,    71,    61,
    65,    87,     0,     0,     0,     0,   124,   100,   104,     0,
   235,   233,   191,    87,     0,   236,   212,   108,     0,   115,
   119,     0,   125,    50,    52,    58,    54,    38,     0,    35,
     0,    42,    43,     0,     0,     0,     0,     0,    83,    97,
    99,   107,   103,   120,   234,   242,   240,     0,   239,   237,
   118,    77,     0,     0,     0,    87,    30,    37,    41,    68,
    70,    74,    72,    62,    86,   238,   241,     0,    59,    55,
    31,    44,     0,     0,    78,    32,     0,     0,     0
};

static const short yydefgoto[] = {   327,
    14,    61,    15,    16,    17,    18,    19,    20,    62,    21,
    22,    23,    24,    55,   306,   324,    25,   279,   280,    40,
    26,   281,   282,    71,    72,    73,   241,   242,   244,   304,
    74,   243,   303,    27,    58,   288,   165,   166,   167,   284,
   285,   287,   286,    28,    56,   240,   318,    29,    59,    30,
    60,   252,    78,   314,    31,    32,    54,    48,    91,    92,
    93,   253,   254,   178,    94,   256,   233,    95,   255,   236,
    96,    97,   238,   270,   295,    36,    33,    98,   258,   274,
   101,   155,   234,   263,   267,   298,   299
};

static const short yypact[] = {   133,
   190,     1,     1,     1,-32768,    -1,     6,     7,    14,    21,
    58,    81,-32768,-32768,-32768,   218,-32768,-32768,   237,-32768,
-32768,   161,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    82,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,    87,-32768,-32768,
-32768,-32768,-32768,    92,     2,    90,    88,    96,    79,   103,
   218,   120,   251,   251,-32768,   121,   464,   464,   464,   464,
   119,    88,-32768,-32768,-32768,   116,   124,-32768,-32768,   135,
-32768,-32768,-32768,   464,   464,   464,   464,-32768,-32768,-32768,
   144,   251,   140,     4,   274,-32768,-32768,-32768,   147,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   149,-32768,
   464,   464,   464,   464,   145,   116,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,   151,-32768,   157,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
   159,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,   240,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,   157,-32768,-32768,   369,-32768,   152,
   158,   121,   157,   157,     9,-32768,-32768,-32768,-32768,-32768,
-32768,    79,   158,   121,   157,   157,-32768,-32768,-32768,   160,
-32768,-32768,-32768,    89,   160,-32768,-32768,-32768,   160,-32768,
-32768,     1,-32768,-32768,-32768,-32768,-32768,-32768,     3,    11,
   164,-32768,-32768,   158,   121,   157,   157,   411,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,   163,    89,-32768,
-32768,-32768,   411,   411,     1,   161,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,   173,-32768,-32768,
-32768,-32768,   158,     2,-32768,-32768,   185,   191,-32768
};

static const short yypgoto[] = {-32768,
   189,-32768,   131,-32768,   177,   182,-32768,   181,-32768,   -17,
-32768,   184,  -183,-32768,-32768,-32768,   -59,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
   139,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    37,-32768,
-32768,-32768,-32768,    19,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,   -39,-32768,   -48,   -52,-32768,-32768,   153,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
   127,-32768,-32768,-32768,  -189,    -3,    78,  -157,-32768,  -176,
  -151,    20,   -89,-32768,-32768,-32768,-32768
};


#define	YYLAST		599


static const short yytable[] = {    37,
    38,    52,    65,    88,    88,   237,   305,   262,    75,     5,
    79,    35,     5,     5,    90,    90,     5,    43,   -87,   179,
     6,   259,     6,     7,    44,     7,    39,   168,   266,    13,
    13,    45,    88,   180,   181,   182,   183,   184,   185,   186,
   187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
   197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
   207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
   217,   218,   219,   220,   221,   300,   290,   268,    46,   301,
   296,    89,    89,    41,    42,   276,   277,   156,   157,   158,
   275,    47,     2,     3,    57,    63,    66,   292,   293,     5,
    64,    77,   291,   171,   172,   173,   174,   310,    76,    80,
    89,    67,    68,    69,    70,   317,    13,   222,   223,   224,
   225,   226,   227,   228,   229,   230,   231,   232,   312,   313,
    82,   100,   159,   311,   169,     1,     2,     3,     4,   161,
   162,   163,   164,     5,     6,   170,   325,     7,   271,     8,
     9,    10,    11,   175,    12,   177,   239,   245,   250,   272,
    13,   257,     2,     3,     2,     3,     4,    83,   273,     5,
   294,     5,     6,   309,   260,     7,   316,     8,     9,   323,
   246,   247,   248,   249,   328,   278,    13,   261,    13,    34,
   329,    81,    49,     2,     3,     4,   283,    50,   315,    51,
     5,     6,   251,    79,     7,    53,     8,     9,    10,    11,
   160,    12,   289,   319,   320,   297,    99,    13,   176,     0,
   308,     2,     3,     4,     0,     0,   307,     0,     5,     6,
     0,     0,     7,     0,     8,     9,     0,    11,     0,    12,
     2,     3,     4,     2,     3,    13,     0,     5,     6,     0,
     5,     7,   264,     8,     9,   265,     4,     0,    12,     0,
     0,    83,     6,     0,    13,     7,     0,    13,   302,     0,
     0,   326,     0,     0,    84,    85,    86,    87,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   322,   235,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   321,     0,   180,   181,   182,   183,   184,   185,   186,
   187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
   197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
   207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
   217,   218,   219,   220,   221,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   269,     0,     0,   222,   223,   224,
   225,   226,   227,   228,   229,   230,   231,   232,   180,   181,
   182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
   192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
   202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
   212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
   180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
   190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
   200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
   210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
   220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
   230,   231,   232,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   222,   223,   224,   225,   226,   227,
   228,   229,   230,   231,   232,   102,   103,   104,   105,   106,
   107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
   117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
   127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
   137,   138,   139,   140,   141,   142,   143,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   144,   145,
   146,   147,   148,   149,   150,   151,   152,   153,   154
};

static const short yycheck[] = {     3,
     4,    19,    55,    63,    64,    95,     4,   191,    57,    11,
    59,    11,    11,    11,    63,    64,    11,    11,    10,    16,
    12,   179,    12,    15,    11,    15,    28,    76,   212,    28,
    28,    11,    92,    30,    31,    32,    33,    34,    35,    36,
    37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
    47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
    57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
    67,    68,    69,    70,    71,   265,   253,   235,    21,   269,
   264,    63,    64,     6,     7,   243,   244,    68,    69,    70,
   242,    11,     4,     5,    13,     9,     7,   255,   256,    11,
     9,    23,   254,    84,    85,    86,    87,   284,    13,     7,
    92,    24,    25,    26,    27,   299,    28,   114,   115,   116,
   117,   118,   119,   120,   121,   122,   123,   124,   286,   287,
    11,    11,    14,   285,    11,     3,     4,     5,     6,    24,
    25,    26,    27,    11,    12,    11,   323,    15,   238,    17,
    18,    19,    20,    10,    22,    16,    10,     9,    14,     8,
    28,    11,     4,     5,     4,     5,     6,    11,    11,    11,
    11,    11,    12,    10,    16,    15,    14,    17,    18,     7,
   161,   162,   163,   164,     0,   245,    28,    29,    28,     1,
     0,    61,    16,     4,     5,     6,   245,    16,   288,    19,
    11,    12,   166,   252,    15,    22,    17,    18,    19,    20,
    72,    22,   252,   303,   304,   264,    64,    28,    92,    -1,
   280,     4,     5,     6,    -1,    -1,   279,    -1,    11,    12,
    -1,    -1,    15,    -1,    17,    18,    -1,    20,    -1,    22,
     4,     5,     6,     4,     5,    28,    -1,    11,    12,    -1,
    11,    15,    13,    17,    18,    16,     6,    -1,    22,    -1,
    -1,    11,    12,    -1,    28,    15,    -1,    28,   272,    -1,
    -1,   324,    -1,    -1,    24,    25,    26,    27,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   306,    16,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,   305,    -1,    30,    31,    32,    33,    34,    35,    36,
    37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
    47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
    57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
    67,    68,    69,    70,    71,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    16,    -1,    -1,   114,   115,   116,
   117,   118,   119,   120,   121,   122,   123,   124,    30,    31,
    32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
    42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
    52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
    62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
    30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
    40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
    50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
    60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
    70,    71,   114,   115,   116,   117,   118,   119,   120,   121,
   122,   123,   124,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,   114,   115,   116,   117,   118,   119,
   120,   121,   122,   123,   124,    72,    73,    74,    75,    76,
    77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
    87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
    97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
   107,   108,   109,   110,   111,   112,   113,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,   126,
   127,   128,   129,   130,   131,   132,   133,   134,   135
};
#define YYPURE 1

/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/local/share/bison.simple"
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

#line 217 "/usr/local/share/bison.simple"

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

case 3:
#line 243 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{
                       if(SKEL != NULL)
                       {
                           SKEL->profileElement(SKELTEXT);
                       }
                   ;
    break;}
case 10:
#line 264 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{
                         if(SKEL != NULL)
                         {
                             SKEL->componentElement(SKELTEXT);
                         }
                     ;
    break;}
case 15:
#line 281 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ setName(szName1, SKELTEXT); ;
    break;}
case 16:
#line 283 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{
                    if(SKEL != NULL)
                    {
                        SKEL->metaElement(szName1, SKELTEXT);
                    }
                    freeName(szName1);
                ;
    break;}
case 27:
#line 309 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ setName(szName1, SKELTEXT); ;
    break;}
case 29:
#line 312 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ if(SKEL != NULL)
                                  SKEL->use(SKELTEXT); ;
    break;}
case 31:
#line 318 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ setName(szName1, SKELTEXT); ;
    break;}
case 39:
#line 335 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ if(SKEL != NULL)
                        SKEL->beginProto(SKELTEXT); ;
    break;}
case 40:
#line 337 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ if(SKEL != NULL)
                        SKEL->beginProto(SKELTEXT); ;
    break;}
case 41:
#line 348 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ if(SKEL != NULL)
			SKEL->endProto(); ;
    break;}
case 49:
#line 369 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ setName(szName1,
                                                      SKELTEXT);;
    break;}
case 50:
#line 371 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
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
case 51:
#line 382 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ setName(szName1,
                                                      SKELTEXT);;
    break;}
case 52:
#line 384 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
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
case 53:
#line 395 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ setName(szName1,
                                                      SKELTEXT);;
    break;}
case 54:
#line 397 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ SKEL->expectType(nextType);
                                              if(SKEL != NULL)
                                               SKEL->beginFieldDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT);
                                              freeName(szName1); ;
    break;}
case 55:
#line 404 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = 0;
                                              if(SKEL != NULL)
                                               SKEL->endFieldDecl();
                                             ;
    break;}
case 57:
#line 412 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ setName(szName1,
                                              SKELTEXT); ;
    break;}
case 58:
#line 414 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ SKEL->expectType(nextType);
                                      if(SKEL != NULL)
                                       SKEL->beginExposedFieldDecl(
                                        szName1,
                                        nextType,
                                        SKELTEXT);
                                       freeName(szName1); ;
    break;}
case 59:
#line 421 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = 0;
                                      if(SKEL != NULL)
                                       SKEL->endExposedFieldDecl(); ;
    break;}
case 60:
#line 427 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ if(SKEL != NULL)
                             SKEL->beginExternProto(SKELTEXT); ;
    break;}
case 61:
#line 432 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{
                 if(SKEL != NULL)
                     SKEL->endExternProtoInterface();

                 SKEL->expectType(TOK_MFSTRING);
              ;
    break;}
case 62:
#line 439 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{
                 if(SKEL != NULL)
                     SKEL->endExternProto();
              ;
    break;}
case 67:
#line 455 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ setName(szName1,
                                                 SKELTEXT); ;
    break;}
case 68:
#line 457 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ if(SKEL != NULL)
                                               SKEL->addExternEventInDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT);
                                         freeName(szName1); ;
    break;}
case 69:
#line 464 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ setName(szName1,
                                                 SKELTEXT); ;
    break;}
case 70:
#line 466 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ if(SKEL != NULL)
                                               SKEL->addExternEventOutDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT);
                                          freeName(szName1); ;
    break;}
case 71:
#line 473 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ setName(szName1,
                                                 SKELTEXT); ;
    break;}
case 72:
#line 475 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ if(SKEL != NULL)
                                               SKEL->addExternFieldDecl(
                                                szName1,
                                                nextType,
                                                SKELTEXT);
                                         freeName(szName1); ;
    break;}
case 73:
#line 482 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ setName(szName1,
                                                 SKELTEXT); ;
    break;}
case 74:
#line 484 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ if(SKEL != NULL)
                                             SKEL->addExternExposedFieldDecl(
                                                 szName1,
                                                 nextType,
                                                 SKELTEXT);
                                       freeName(szName1); ;
    break;}
case 75:
#line 493 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ setName(szName1, SKELTEXT); ;
    break;}
case 76:
#line 495 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ setName(szName2, SKELTEXT); ;
    break;}
case 77:
#line 497 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ setName(szName3, SKELTEXT); ;
    break;}
case 78:
#line 499 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
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
case 79:
#line 512 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{
                      setName(szName1, SKELTEXT);
                  ;
    break;}
case 80:
#line 516 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{
                      if(SKEL != NULL)
                      {
                          SKEL->exportElement(szName1, szName2);
                      }

                      freeName(szName1);
                      freeName(szName2);
                  ;
    break;}
case 81:
#line 529 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{
                      setName(szName1, SKELTEXT);
                  ;
    break;}
case 82:
#line 534 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{
                      setName(szName3, SKELTEXT);
                  ;
    break;}
case 83:
#line 538 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{
                      if(SKEL != NULL)
                      {
                          SKEL->importElement(szName1, szName3, szName2);
                      }

                      freeName(szName1);
                      freeName(szName2);
                      freeName(szName3);
                  ;
    break;}
case 84:
#line 551 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{
                        setName(szName2, SKELTEXT);
                  ;
    break;}
case 88:
#line 563 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ if(SKEL != NULL)
                    {
                        SKEL->beginNode(SKELTEXT, szName1);
                    }

                    freeName(szName1);
                  ;
    break;}
case 89:
#line 573 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ if(SKEL != NULL)
                     SKEL->endNode(); ;
    break;}
case 90:
#line 575 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ if(SKEL != NULL)
                     SKEL->beginNode(SKELTEXT, szName1);

                    freeName(szName1);
                  ;
    break;}
case 91:
#line 582 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ if(SKEL != NULL)
                     SKEL->endNode(); ;
    break;}
case 96:
#line 605 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ setName(szName1,
                                                          SKELTEXT); ;
    break;}
case 97:
#line 607 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ if(SKEL != NULL)
                                                     SKEL->beginEventInDecl(
                                                       szName1,
                                                       nextType,
                                                       SKELTEXT);

                                                 freeName(szName1); ;
    break;}
case 98:
#line 615 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ setName(szName1,
                                                          SKELTEXT); ;
    break;}
case 99:
#line 617 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ if(SKEL != NULL)
                                                     SKEL->beginEventOutDecl(
                                                       szName1,
                                                       nextType,
                                                       SKELTEXT);

                                                  freeName(szName1); ;
    break;}
case 100:
#line 627 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{
                                          if(SKEL != NULL)
                                          {
                                             SKEL->is(SKELTEXT);
                                             SKEL->endEventDecl();
                                          }
                                        ;
    break;}
case 101:
#line 635 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{
                                            if(SKEL != NULL)
                                            {
                                                SKEL->endEventDecl();
                                            }
                                        ;
    break;}
case 102:
#line 644 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ setName(szName1,
                                                         SKELTEXT);
                                               ;
    break;}
case 103:
#line 647 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ SKEL->expectType(nextType);

                                                 if(SKEL != NULL)
                                                     SKEL->beginFieldDecl(
                                                       szName1,
                                                       nextType,
                                                       SKELTEXT);

                                                 freeName(szName1);
                                               ;
    break;}
case 104:
#line 659 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = 0;

                                                     if(SKEL != NULL)
                                                     {
                                                       SKEL->is(SKELTEXT);

                                                       SKEL->endFieldDecl();
                                                     }
                                                   ;
    break;}
case 105:
#line 668 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = 0;

                                                     if(SKEL != NULL)
                                                       SKEL->endFieldDecl();

                                                   ;
    break;}
case 106:
#line 677 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ setName(szName1,
                                                            SKELTEXT);
                                                  ;
    break;}
case 107:
#line 680 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ SKEL->expectType(nextType);

                                                    if(SKEL != NULL)
                                                        SKEL->
                                                         beginExposedFieldDecl(
                                                           szName1,
                                                           nextType,
                                                           SKELTEXT);

                                                    freeName(szName1);
                                                  ;
    break;}
case 108:
#line 693 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = 0;

                                                        if(SKEL != NULL)
                                                        {
                                                         SKEL->is(SKELTEXT);

                                                         SKEL->
                                                         endExposedFieldDecl();
                                                        }
                                                      ;
    break;}
case 109:
#line 703 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = 0;

                                                        if(SKEL != NULL)
                                                         SKEL->
                                                         endExposedFieldDecl();
                                                      ;
    break;}
case 114:
#line 731 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
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
                   ;
    break;}
case 118:
#line 758 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ if(SKEL != NULL)
                          {
                            SKEL->is(SKELTEXT);
                            SKEL->endField();
                          }
                        ;
    break;}
case 119:
#line 764 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ if(SKEL != NULL)
                            SKEL->endField();
                        ;
    break;}
case 127:
#line 792 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_MFBOOL;      ;
    break;}
case 128:
#line 793 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_MFCOLOR;     ;
    break;}
case 129:
#line 794 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_MFCOLORRGBA; ;
    break;}
case 130:
#line 795 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_MFDOUBLE;    ;
    break;}
case 131:
#line 796 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_MFFLOAT;     ;
    break;}
case 132:
#line 797 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_MFIMAGE;     ;
    break;}
case 133:
#line 798 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_MFINT32;     ;
    break;}
case 134:
#line 799 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_MFMATRIX3D;  ;
    break;}
case 135:
#line 800 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_MFMATRIX3F;  ;
    break;}
case 136:
#line 801 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_MFMATRIX4D;  ;
    break;}
case 137:
#line 802 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_MFMATRIX4F;  ;
    break;}
case 138:
#line 803 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_MFNODE;      ;
    break;}
case 139:
#line 804 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_MFROTATION;  ;
    break;}
case 140:
#line 805 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_MFSTRING;    ;
    break;}
case 141:
#line 806 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_MFTIME;      ;
    break;}
case 142:
#line 807 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_MFVEC2D;     ;
    break;}
case 143:
#line 808 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_MFVEC2F;     ;
    break;}
case 144:
#line 809 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_MFVEC3D;     ;
    break;}
case 145:
#line 810 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_MFVEC3F;     ;
    break;}
case 146:
#line 811 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_MFVEC4D;     ;
    break;}
case 147:
#line 812 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_MFVEC4F;     ;
    break;}
case 148:
#line 813 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFBOOL;      ;
    break;}
case 149:
#line 814 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFCOLOR;     ;
    break;}
case 150:
#line 815 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFCOLORRGBA; ;
    break;}
case 151:
#line 816 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFDOUBLE;    ;
    break;}
case 152:
#line 817 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFFLOAT;     ;
    break;}
case 153:
#line 818 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFIMAGE;     ;
    break;}
case 154:
#line 819 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFINT32;     ;
    break;}
case 155:
#line 820 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFMATRIX3D;  ;
    break;}
case 156:
#line 821 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFMATRIX3F;  ;
    break;}
case 157:
#line 822 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFMATRIX4D;  ;
    break;}
case 158:
#line 823 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFMATRIX4F;  ;
    break;}
case 159:
#line 824 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFNODE;      ;
    break;}
case 160:
#line 825 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFROTATION;  ;
    break;}
case 161:
#line 826 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFSTRING;    ;
    break;}
case 162:
#line 827 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFTIME;      ;
    break;}
case 163:
#line 828 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFVEC2D;     ;
    break;}
case 164:
#line 829 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFVEC2F;     ;
    break;}
case 165:
#line 830 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFVEC3D;     ;
    break;}
case 166:
#line 831 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFVEC3F;     ;
    break;}
case 167:
#line 832 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFVEC4D;     ;
    break;}
case 168:
#line 833 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFVEC4F;     ;
    break;}
case 169:
#line 834 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_MFCOLOR4I;   ;
    break;}
case 170:
#line 835 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_MFPNT2F;     ;
    break;}
case 171:
#line 836 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_MFPNT3F;     ;
    break;}
case 172:
#line 837 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_MFPNT4F;     ;
    break;}
case 173:
#line 838 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_MFPLANE;     ;
    break;}
case 174:
#line 839 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFCOLOR4I;   ;
    break;}
case 175:
#line 840 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFPNT2F;     ;
    break;}
case 176:
#line 841 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFPNT3F;     ;
    break;}
case 177:
#line 842 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFPNT4F;     ;
    break;}
case 178:
#line 843 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFPLANE;     ;
    break;}
case 179:
#line 844 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{ nextType = TOK_SFVOLUME;    ;
    break;}
case 234:
#line 906 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{
                  if(SKEL != NULL)
                  {
                      SKEL->is(SKELTEXT);
                  }
              ;
    break;}
case 237:
#line 917 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"
{
                  if(SKEL != NULL)
                  {
                      SKEL->is(SKELTEXT);
                  }
              ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 543 "/usr/local/share/bison.simple"

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
#line 935 "../../../source/system/fileio/scanparseskel/osgscanparseskel.y"


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
