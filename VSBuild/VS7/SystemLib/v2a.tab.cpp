
/* A Bison parser, made from ../../../Experimental/VRMLLoader/v2a.y
   by GNU bison 1.30.  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse v2a_parse
#define yylex v2a_lex
#define yyerror v2a_error
#define yylval v2a_lval
#define yychar v2a_char
#define yydebug v2a_debug
#define yynerrs v2a_nerrs
# define	POSITION	257
# define	ORIENTATION	258
# define	COORDINATE	259
# define	SCALAR	260
# define	COLOR	261
# define	NORMAL	262
# define	C_OPEN	263
# define	C_CLOSE	264
# define	E_OPEN	265
# define	E_CLOSE	266
# define	COMMA	267
# define	KEY	268
# define	KEYVALUE	269
# define	KEYSIZE	270
# define	DURATION	271
# define	STRING	272
# define	NUMBER	273

#line 1 "../../../Experimental/VRMLLoader/v2a.y"


#ifdef WIN32
#include <malloc.h>
#endif

#include <stdio.h>
//#include "vrml2anim.h"
#include "OSGAnimTest.h"
#include "OSGAnimation.h"
#include "OSGMFVecTypes.h"
#include "OSGGenericInterpolator.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* global variables */
int   v2aLineNumber = 1;
float v2aDuration;
int   v2aKeySize;

/* functions */
int v2a_error (char *s);  
extern int v2a_lex ();  


#line 30 "../../../Experimental/VRMLLoader/v2a.y"
typedef union
{
    float fval;
    char sval[1024];
} YYSTYPE;
#include <stdio.h>



#define	YYFINAL		110
#define	YYFLAG		-32768
#define	YYNTBASE	20

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 273 ? yytranslate[x] : 51)

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
      16,    17,    18,    19
};

#if YYDEBUG != 0
static const short yyprhs[] =
{
       0,     0,     1,     4,     6,     8,    10,    12,    14,    16,
      18,    21,    22,    32,    33,    44,    47,    48,    58,    59,
      69,    70,    80,    81,    92,    97,    98,   102,   103,   105,
     110,   111,   117,   122,   123,   129,   134,   135,   142,   147,
     148,   152,   157,   158,   164,   169,   170
};
static const short yyrhs[] =
{
      -1,    20,    21,     0,    23,     0,    28,     0,    25,     0,
      30,     0,    32,     0,    34,     0,    22,     0,    17,    19,
       0,     0,    18,    18,    19,     3,    24,     9,    36,    39,
      10,     0,     0,    18,    18,    19,     5,    26,     9,    27,
      36,    41,    10,     0,    16,    19,     0,     0,    18,    18,
      19,     4,    29,     9,    36,    43,    10,     0,     0,    18,
      18,    19,     6,    31,     9,    36,    45,    10,     0,     0,
      18,    18,    19,     7,    33,     9,    36,    47,    10,     0,
       0,    18,    18,    19,     8,    35,     9,    27,    36,    49,
      10,     0,    14,    11,    37,    12,     0,     0,    37,    19,
      38,     0,     0,    13,     0,    15,    11,    40,    12,     0,
       0,    40,    19,    19,    19,    38,     0,    15,    11,    42,
      12,     0,     0,    42,    19,    19,    19,    38,     0,    15,
      11,    44,    12,     0,     0,    44,    19,    19,    19,    19,
      38,     0,    15,    11,    46,    12,     0,     0,    46,    19,
      38,     0,    15,    11,    48,    12,     0,     0,    48,    19,
      19,    19,    38,     0,    15,    11,    50,    12,     0,     0,
      50,    19,    19,    19,    38,     0
};

#endif

#if YYDEBUG != 0
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,    48,    49,    53,    54,    55,    56,    57,    58,    59,
      62,    68,    74,    81,    87,    95,   101,   107,   114,   120,
     127,   133,   140,   146,   154,   157,   158,   165,   166,   170,
     173,   174,   195,   198,   199,   239,   242,   243,   271,   274,
     275,   297,   300,   301,   323,   326,   327
};
#endif


#if YYDEBUG != 0 || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "POSITION", "ORIENTATION", "COORDINATE", 
  "SCALAR", "COLOR", "NORMAL", "C_OPEN", "C_CLOSE", "E_OPEN", "E_CLOSE", 
  "COMMA", "KEY", "KEYVALUE", "KEYSIZE", "DURATION", "STRING", "NUMBER", 
  "v2a", "anim_def", "duration", "posanim_def", "@1", "coordanim_def", 
  "@2", "keysize_def", "orianim_def", "@3", "scanim_def", "@4", 
  "colanim_def", "@5", "noranim_def", "@6", "key_def", "key_list", 
  "opt_comma", "posval_def", "posval_list", "coordval_def", 
  "coordval_list", "orival_def", "orival_list", "scval_def", "scval_list", 
  "colval_def", "colval_list", "norval_def", "norval_list", NULL
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    20,    20,    21,    21,    21,    21,    21,    21,    21,
      22,    24,    23,    26,    25,    27,    29,    28,    31,    30,
      33,    32,    35,    34,    36,    37,    37,    38,    38,    39,
      40,    40,    41,    42,    42,    43,    44,    44,    45,    46,
      46,    47,    48,    48,    49,    50,    50
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     2,     1,     1,     1,     1,     1,     1,     1,
       2,     0,     9,     0,    10,     2,     0,     9,     0,     9,
       0,     9,     0,    10,     4,     0,     3,     0,     1,     4,
       0,     5,     4,     0,     5,     4,     0,     6,     4,     0,
       3,     4,     0,     5,     4,     0,     5
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       1,     0,     0,     0,     2,     9,     3,     5,     4,     6,
       7,     8,    10,     0,     0,    11,    16,    13,    18,    20,
      22,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    25,     0,     0,     0,     0,    15,     0,     0,     0,
       0,     0,     0,     0,    30,    12,    36,    17,     0,     0,
      39,    19,    42,    21,     0,     0,    24,    27,     0,     0,
      33,    14,     0,     0,    45,    23,    28,    26,    29,     0,
      35,     0,     0,    38,    27,    41,     0,     0,     0,     0,
      32,     0,    40,     0,    44,     0,    27,     0,     0,    27,
       0,    31,    27,    27,    43,    27,    37,    34,    46,     0,
       0
};

static const short yydefgoto[] =
{
       1,     4,     5,     6,    21,     7,    23,    37,     8,    22,
       9,    24,    10,    25,    11,    26,    34,    53,    77,    43,
      68,    59,    82,    45,    69,    49,    72,    51,    73,    65,
      87
};

static const short yypact[] =
{
  -32768,     5,   -13,    -7,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,   -11,    33,-32768,-32768,-32768,-32768,-32768,
  -32768,     7,    20,    21,    25,    34,    35,     3,     3,    26,
       3,     3,    26,    36,    30,    31,    29,     3,    37,    38,
       3,-32768,    39,    41,    43,    45,-32768,    42,    47,    46,
      48,    50,    49,   -10,-32768,-32768,-32768,-32768,    51,    53,
  -32768,-32768,-32768,-32768,    54,    56,-32768,    55,    -5,     8,
  -32768,-32768,    12,    13,-32768,-32768,-32768,-32768,-32768,    52,
  -32768,    57,    14,-32768,    55,-32768,    58,    16,    59,    60,
  -32768,    61,-32768,    62,-32768,    63,    55,    64,    65,    55,
      66,-32768,    55,    55,-32768,    55,-32768,-32768,-32768,    67,
  -32768
};

static const short yypgoto[] =
{
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,    17,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,   -27,-32768,   -84,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768
};


#define	YYLAST		85


static const short yytable[] =
{
      92,    35,    66,    38,    39,   109,    12,    78,    14,    67,
      47,    13,   101,    52,    79,   104,    27,    33,   106,   107,
      80,   108,     2,     3,    83,    85,    90,    81,    94,    28,
      29,    84,    86,    91,    30,    95,    15,    16,    17,    18,
      19,    20,    36,    31,    32,    42,    44,    41,    46,    40,
      54,    55,    48,    50,    56,    57,    61,    58,    60,    62,
      63,     0,    70,    71,    64,    74,    75,   110,    76,     0,
       0,    88,     0,     0,     0,     0,    89,    93,    96,    97,
      98,    99,   100,   102,   103,   105
};

static const short yycheck[] =
{
      84,    28,    12,    30,    31,     0,    19,    12,    19,    19,
      37,    18,    96,    40,    19,    99,     9,    14,   102,   103,
      12,   105,    17,    18,    12,    12,    12,    19,    12,     9,
       9,    19,    19,    19,     9,    19,     3,     4,     5,     6,
       7,     8,    16,     9,     9,    15,    15,    11,    19,    32,
      11,    10,    15,    15,    11,    10,    10,    15,    11,    11,
      10,    -1,    11,    10,    15,    11,    10,     0,    13,    -1,
      -1,    19,    -1,    -1,    -1,    -1,    19,    19,    19,    19,
      19,    19,    19,    19,    19,    19
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
#line 63 "../../../Experimental/VRMLLoader/v2a.y"
{
                    v2aDuration = yyvsp[0].fval;
                ;
    break;}
case 11:
#line 69 "../../../Experimental/VRMLLoader/v2a.y"
{
                    OSG::addAnim( OSG::InterpolatorBase::Position, yyvsp[-3].sval, yyvsp[-2].sval, (int)yyvsp[-1].fval,
                                     v2aDuration );
                ;
    break;}
case 12:
#line 77 "../../../Experimental/VRMLLoader/v2a.y"
{
                ;
    break;}
case 13:
#line 82 "../../../Experimental/VRMLLoader/v2a.y"
{
                    OSG::addAnim( OSG::InterpolatorBase::Position, yyvsp[-3].sval, yyvsp[-2].sval, (int)yyvsp[-1].fval,
                                     v2aDuration );
                ;
    break;}
case 14:
#line 91 "../../../Experimental/VRMLLoader/v2a.y"
{
                ;
    break;}
case 15:
#line 96 "../../../Experimental/VRMLLoader/v2a.y"
{
                    v2aKeySize=(int) yyvsp[0].fval;
                ;
    break;}
case 16:
#line 102 "../../../Experimental/VRMLLoader/v2a.y"
{
                    OSG::addAnim( OSG::InterpolatorBase::Orientation, yyvsp[-3].sval, yyvsp[-2].sval, (int)yyvsp[-1].fval,
                                     v2aDuration );
                ;
    break;}
case 17:
#line 110 "../../../Experimental/VRMLLoader/v2a.y"
{
                ;
    break;}
case 18:
#line 115 "../../../Experimental/VRMLLoader/v2a.y"
{
                    OSG::addAnim( OSG::InterpolatorBase::Other, yyvsp[-3].sval, yyvsp[-2].sval, (int)yyvsp[-1].fval,
                                     v2aDuration );
                ;
    break;}
case 19:
#line 123 "../../../Experimental/VRMLLoader/v2a.y"
{
                ;
    break;}
case 20:
#line 128 "../../../Experimental/VRMLLoader/v2a.y"
{
                    OSG::addAnim( OSG::InterpolatorBase::Other, yyvsp[-3].sval, yyvsp[-2].sval, (int)yyvsp[-1].fval,
                                     v2aDuration );
                ;
    break;}
case 21:
#line 136 "../../../Experimental/VRMLLoader/v2a.y"
{
                ;
    break;}
case 22:
#line 141 "../../../Experimental/VRMLLoader/v2a.y"
{
                    OSG::addAnim( OSG::InterpolatorBase::Other, yyvsp[-3].sval, yyvsp[-2].sval, (int)yyvsp[-1].fval,
                                     v2aDuration );
                ;
    break;}
case 23:
#line 150 "../../../Experimental/VRMLLoader/v2a.y"
{
                ;
    break;}
case 26:
#line 159 "../../../Experimental/VRMLLoader/v2a.y"
{
                if ( OSG::Animation::getAnim() )
                    OSG::Animation::getAnim()->currentInterpolator()->addKey( yyvsp[-1].fval );
            ;
    break;}
case 31:
#line 175 "../../../Experimental/VRMLLoader/v2a.y"
{
                if ((OSG::Animation::getAnim()) && (OSG::Animation::getAnim()->currentInterpolator()))
                {                   
                    OSG::Vec3f   value;
                    OSG::PositionInterpolatorPtr currInterpol;
                    
                    currInterpol = dynamic_cast<OSG::PositionInterpolatorPtr>
                                        ( OSG::Animation::getAnim()->currentInterpolator() );
                                        
                    if( currInterpol->nrOfKeyValues() <= currInterpol->nrOfKeys() )
                    {
                        value.setValues( yyvsp[-3].fval, yyvsp[-2].fval, yyvsp[-1].fval );
                        currInterpol->addKeyValue( value );
                    }
                    else
                        fprintf(stderr, "v2a_parse(): not enough keys for position!\n");
                }
            ;
    break;}
case 34:
#line 200 "../../../Experimental/VRMLLoader/v2a.y"
{
                /*
                if ((OSG::Animation::getAnim()) && (OSG::Animation::getAnim()->interpolator()))
                {
                    static v2aCoordinateField *coordField=NULL;
                    static int index=0;
                    
                    if (index==v2aKeySize) index=0; // loop the index
                    
                    if (index==0)       // start of a new keyValue
                    {
                        float key;
                        int pos=OSG::Animation::getAnim()->interpolator()->getSize();
                        if (pos<OSG::Animation::getAnim()->getKeys()->size())
                        {
                            key=(*OSG::Animation::getAnim()->getKeys())[pos];
                            coordField=new v2aCoordinateField();
                            OSG::Animation::getAnim()->addListItem(
                                        new v2aListItem( key, coordField ) );
                        }
                        else
                        {
                            fprintf(stderr, "v2a_parse(): not enough keys!\n");
                            coordField=NULL;
                        }
                    }
                    
                    // add the new coordinate
                    if (coordField)
                    {
                        coordField->addCoord( $2, $3, $4 );
                        index++;
                    }
                }
                */
                cerr << "v2a_parse.y::ignoring coordinate-interpolator (temporarly)\n";
            ;
    break;}
case 37:
#line 244 "../../../Experimental/VRMLLoader/v2a.y"
{
                
                if ((OSG::Animation::getAnim()) && (OSG::Animation::getAnim()->currentInterpolator()))
                {
                    OSG::Quaternion     value;
                    OSG::OrientationInterpolatorPtr currInterpol;
                    OSG::Real32         x,y,z,w;

                    currInterpol = dynamic_cast<OSG::OrientationInterpolatorPtr>
                                        ( OSG::Animation::getAnim()->currentInterpolator() );   
                    
                    if( currInterpol->nrOfKeyValues() <= currInterpol->nrOfKeys() )
                    {

                        //cerr << $2 << ", " << $3 << ", " << $4 << ", " << $5 << endl;
                        value.setValueAsAxisRad( OSG::Vec3f(yyvsp[-4].fval, yyvsp[-3].fval, yyvsp[-2].fval), yyvsp[-1].fval );
                        //cerr << "#" << value << endl;
                        value.getValueAsAxisRad( x,y,z,w );
                        //cerr << "#" << x << ", " << y << ", " << z << ", " << w << endl;
                        currInterpol->addKeyValue( value );
                    }
                    else
                        fprintf(stderr, "v2a_parse(): not enough keys for orientation!\n");
                }
            ;
    break;}
case 40:
#line 276 "../../../Experimental/VRMLLoader/v2a.y"
{
                /*
                if ((OSG::Animation::getAnim()) && (OSG::Animation::getAnim()->interpolator()))
                {
                    float key;
                    v2aScalarField *field;
                    int pos=OSG::Animation::getAnim()->interpolator()->getSize();
                    if (pos<OSG::Animation::getAnim()->getKeys()->size())
                    {
                        key=(*OSG::Animation::getAnim()->getKeys())[pos];
                        field=new v2aScalarField( $2 );
                        OSG::Animation::getAnim()->addListItem( new v2aListItem(key, field) );
                    }
                    else
                        fprintf(stderr, "v2a_parse(): not enough keys!\n");
                }
                */
                cerr << "v2a_parse.y::ignoring scalar-interpolators\n";
            ;
    break;}
case 43:
#line 302 "../../../Experimental/VRMLLoader/v2a.y"
{
                /*
                if ((OSG::Animation::getAnim()) && (OSG::Animation::getAnim()->interpolator()))
                {
                    float key;
                    v2aColorField *field;
                    int pos=OSG::Animation::getAnim()->interpolator()->getSize();
                    if (pos<OSG::Animation::getAnim()->getKeys()->size())
                    {
                        key=(*OSG::Animation::getAnim()->getKeys())[pos];
                        field=new v2aColorField( $2, $3, $4 );
                        OSG::Animation::getAnim()->addListItem( new v2aListItem( key, field ) );
                    }
                    else
                        fprintf(stderr, "v2a_parse(): not enough keys!\n");
                }
                */
                cerr << "v2a_parse.y::ignoring color-interpolators\n";              
            ;
    break;}
case 46:
#line 328 "../../../Experimental/VRMLLoader/v2a.y"
{
                /*
                if ((OSG::Animation::getAnim()) && (OSG::Animation::getAnim()->interpolator()))
                {
                    static v2aNormalField *normalField=NULL;
                    static int index=0;
                    
                    if (index==v2aKeySize) index=0; // loop the index
                    
                    if (index==0)       // start of a new keyValue
                    {
                        float key;
                        int pos=OSG::Animation::getAnim()->interpolator()->getSize();
                        if (pos<OSG::Animation::getAnim()->getKeys()->size())
                        {
                            key=(*OSG::Animation::getAnim()->getKeys())[pos];
                            normalField=new v2aNormalField();
                            OSG::Animation::getAnim()->addListItem(
                                        new v2aListItem( key, normalField ) );
                        }
                        else
                        {
                            fprintf(stderr, "v2a_parse(): not enough keys!\n");
                            normalField=NULL;
                        }
                    }
                    
                    // add the new coordinate
                    if (normalField)
                    {
                        normalField->addNormal( $2, $3, $4 );
                        index++;
                    }
                }
                */
                cerr << "v2a_parse.y::ignoring normal-interpolators\n";             
            ;
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
#line 368 "../../../Experimental/VRMLLoader/v2a.y"



int v2a_error (char *s)  /* Called by v2a_parse on error */
{
  printf ("-----> %s in Line %d \n", s, v2aLineNumber);
  return v2aLineNumber;
}

#ifdef __cplusplus
}
#endif


