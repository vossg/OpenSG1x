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




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif





