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




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif





