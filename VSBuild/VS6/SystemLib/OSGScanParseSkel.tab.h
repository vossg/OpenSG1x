/* A Bison parser, made from ../../../Source/System/FileIO/ScanParseSkel/OSGScanParseSkel.y, by GNU bison 1.75.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

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

#ifndef BISON_OSGSCANPARSESKEL__TAB_H
# define BISON_OSGSCANPARSESKEL__TAB_H

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




#ifndef YYSTYPE
typedef int yystype;
# define YYSTYPE yystype
#endif

extern YYSTYPE OSGScanParseSkel_lval;


#endif /* not BISON_OSGSCANPARSESKEL__TAB_H */

