/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

%{

#ifdef OSG_WIN32_ICL
#pragma warning (disable : 111 810)
#endif

#define YY_NEVER_INTERACTIVE 1

#include <OSGScanParseSkel.tab.h>
#include <OSGScanParseSkel.h>

int iLineNum = 1;

extern "C"
{
int OSGScanParseSkel_wrap(void);
}

OSG_USING_NAMESPACE

int expectToken         = 0;
int parsing_mf          = 0;
int sfImageIntsExpected = 0;
int sfImageIntsParsed   = 0;                          

extern void OSGScanParseSkel_error (char *s);

extern ScanParseSkel *_pSkel;

#ifdef __sgi
#pragma set woff 1174,1552,1110,1209
#endif

static char *tmpChar = yy_full_match;

%}

%x NODE


%x sfboolValue     sfcolorValue  sffloatValue sfimageValue    sfint32Value 
%x sfrotationValue sfstringValue sftimeValue  sfvec2fValue    sfvec3fValue
%x mfcolorValue    mffloatValue  mfint32Value mfrotationValue mfstringValue
%x mftimeValue     mfvec2fValue  mfvec3fValue
%x IN_SFS IN_MFS IN_SFIMG


%x sfcolor4fValue sfmatrixValue sfpnt2fValue sfpnt3fValue sfpnt4fValue
%x sfvec4fValue sfcolor3fValue sfplaneValue

%x mfcolor4fValue mfmatrixValue mfpnt2fValue mfpnt3fValue mfpnt4fValue 
%x mfvec4fValue mfcolor3fValue mfplaneValue

%x EXTERROR

/* float  ::= ([+/-]?((([0-9]+(\.)?)|([0-9]*\.[0-9]+))([eE][+\-]?[0-9]+)?)) */
/* double ::= ([+/-]?((([0-9]+(\.)?)|([0-9]*\.[0-9]+))([eE][+\-]?[0-9]+)?)) */

float ((\+|-)?(([0-9]+)|([0-9]*\.?[0-9]+)([eE][+\-]?[0-9]+)?))

/* int32 ::= ([+\-]?(([0-9]+)|(0[xX][0-9a-fA-F]+))) */

int32 ((\+|-)?([0-9]+)|(0[xX][0-9a-fA-F]*))

 /* dass an der betreffenden Stelle ein Zeilentrenner auftritt. */
ws ([ \t\r\n,]|(#.*))+

 /* Gleiches Erkennungsmuster ohne Erkennung des Zeilentrenners */
wsnnl ([ \t\r,]|(#.*))

nl (\n)

/*
Id ::=
     IdFirstChar |
     IdFirstChar IdRestChars ;
IdFirstChar ::=
     Any ISO-10646 character encoded using UTF-8 except: 0x30-0x39,
     0x0-0x20, 0x22, 0x23, 0x27, 0x2b, 0x2c, 0x2d, 0x2e, 0x5b, 0x5c, 0x5d,
     0x7b, 0x7d, 0x7f ;
IdRestChars ::=
     Any number of ISO-10646 characters except: 0x0-0x20, 0x22, 0x23, 0x27,
     0x2c, 0x2e, 0x5b, 0x5c, 0x5d, 0x7b, 0x7d, 0x7f ;
*/

IdFirstChar ([^\x30-\x39\x00-\x20\x22\x23\x27\x2b-\x2e\x5b-\x5d\x7b\x7d])
IdRestChar  ([^\x00-\x20\x22\x23\x27\x2c\x2e\x5b-\x5d\x7b\x7d])

header (#[^\n]*\n)

%%

%{

 /*   In neuen Startzustand gehen, wenn der Parser */
 /*   erkannt hat, dass gerade ein Feldname gelesen */
 /*   wurde. Jetzt kann entweder der Wert eines */
 /*   Feldes oder ein "IS" gelesen werden. */

//    fprintf(stderr,"LEX--> Start State %d\n", expectToken);

    if(expectToken != 0)
    {   
        switch(expectToken)
        {
            case TOK_SFBOOL:     BEGIN sfboolValue;         break;
            case TOK_SFCOLOR:    BEGIN sfcolorValue;        break;
            case TOK_SFFLOAT:    BEGIN sffloatValue;        break;
            case TOK_SFIMAGE:    BEGIN sfimageValue;        break;
            case TOK_SFINT32:    BEGIN sfint32Value;        break;
            case TOK_SFROTATION: BEGIN sfrotationValue;     break;
            case TOK_SFSTRING:   BEGIN sfstringValue;       break;
            case TOK_SFTIME:     BEGIN sftimeValue;         break;
            case TOK_SFVEC2F:    BEGIN sfvec2fValue;        break;
            case TOK_SFVEC3F:    BEGIN sfvec3fValue;        break;
            case TOK_MFCOLOR:    BEGIN mfcolorValue;        break;
            case TOK_MFFLOAT:    BEGIN mffloatValue;        break;
            case TOK_MFINT32:    BEGIN mfint32Value;        break;
            case TOK_MFROTATION: BEGIN mfrotationValue;     break;
            case TOK_MFSTRING:   BEGIN mfstringValue;       break;
            case TOK_MFTIME:     BEGIN mftimeValue;         break;
            case TOK_MFVEC2F:    BEGIN mfvec2fValue;        break;
            case TOK_MFVEC3F:    BEGIN mfvec3fValue;        break;

                /*SFNode- und MFNode-Felder werden gesondert behandelt. */
                /*Dabei wird dem Parser vom Lexer nur sogenannte Marker- */
                /*Token zurueckgegeben, damit der Parser erkennt, um welchen */
                /*Typ Feld es sich handelt. Im Gegensatz zu anderen Feldern */
                /*werden SFNode- und MFNode-Felder im Parser behandelt. */

            case TOK_MFNODE: expectToken = 0; return TOK_MFNODE;
            case TOK_SFNODE: expectToken = 0; return TOK_SFNODE;

                /* extended Field Types */ 

            case TOK_MFCOLOR4F: BEGIN mfcolor4fValue; break;
            case TOK_MFCOLOR3F: BEGIN mfcolor3fValue; break;            
            case TOK_SFCOLOR4F: BEGIN sfcolor4fValue; break;            
            case TOK_SFCOLOR3F: BEGIN sfcolor3fValue; break;
            case TOK_MFMATRIX:  BEGIN mfmatrixValue;  break;
            case TOK_SFMATRIX:  BEGIN sfmatrixValue;  break;            
            case TOK_MFPNT2F:   BEGIN mfpnt2fValue;   break;            
            case TOK_SFPNT2F:   BEGIN sfpnt2fValue;   break;            
            case TOK_MFPNT3F:   BEGIN mfpnt3fValue;   break;            
            case TOK_SFPNT3F:   BEGIN sfpnt3fValue;   break;            
            case TOK_MFPNT4F:   BEGIN mfpnt4fValue;   break;            
            case TOK_SFPNT4F:   BEGIN sfpnt4fValue;   break;            
            case TOK_MFVEC4F:   BEGIN mfvec4fValue;   break;            
            case TOK_SFVEC4F:   BEGIN sfvec4fValue;   break;
            case TOK_MFPLANE:   BEGIN mfplaneValue;   break;
            case TOK_SFPLANE:   BEGIN sfplaneValue;   break;            

            default: 
                fprintf(stderr, "ACK: Bad expectToken"); 
                break;
        }
    }
%}

 /* Header der VRML-Datei erkennen */
<INITIAL>{header} { if(_pSkel != NULL)
                    {
                        if(_pSkel->verifyHeader(OSGScanParseSkel_text) != true)
                        {
                            BEGIN EXTERROR;
                        }
                        else
                        {
                            BEGIN NODE; 
                        }
                    }
                  }

 /* Der Lexer ist im Zustand NODE, wenn Knosten gelesen werden. */
 /* Hierbei gibt es drei Moeglichkeiten: Wurzelknoten im der */
 /* VRML-Datei, in einer Prototyp-Implementierung oder beim */
 /* Lesen des Inhaltes von SFNode- oder MFNode-Feldern. */

<NODE>PROTO         { return PROTO; }
<NODE>EXTERNPROTO   { return EXTERNPROTO; }
<NODE>DEF           { return DEF; }
<NODE>USE           { return USE; }
<NODE>TO            { return TO; }
<NODE>IS            { return IS; }
<NODE>ROUTE         { return ROUTE; }
<NODE>NULL          { return SFN_NULL; }
<NODE>Script        { return SCRIPT; }
<NODE>eventIn       { return EVENTIN; }
<NODE>eventOut      { return EVENTOUT; }
<NODE>field         { return FIELD; }
<NODE>exposedField  { return EXPOSEDFIELD; }

<NODE>MFColor       { return Tok_MFColor;    } 
<NODE>MFFloat       { return Tok_MFFloat;    } 
<NODE>MFInt32       { return Tok_MFInt32;    } 
<NODE>MFNode        { return Tok_MFNode;     } 
<NODE>MFRotation    { return Tok_MFRotation; } 
<NODE>MFString      { return Tok_MFString;   } 
<NODE>MFTime        { return Tok_MFTime;     } 
<NODE>MFVec2f       { return Tok_MFVec2f;    } 
<NODE>MFVec3f       { return Tok_MFVec3f;    } 
<NODE>SFBool        { return Tok_SFBool;     } 
<NODE>SFColor       { return Tok_SFColor;    } 
<NODE>SFFloat       { return Tok_SFFloat;    } 
<NODE>SFImage       { return Tok_SFImage;    } 
<NODE>SFInt32       { return Tok_SFInt32;    } 
<NODE>SFNode        { return Tok_SFNode;     } 
<NODE>SFRotation    { return Tok_SFRotation; } 
<NODE>SFString      { return Tok_SFString;   } 
<NODE>SFTime        { return Tok_SFTime;     } 
<NODE>SFVec2f       { return Tok_SFVec2f;    } 
<NODE>SFVec3f       { return Tok_SFVec3f;    } 

    /* extended types */

<NODE>MFColor4f     { return Tok_MFColor4f;  } 
<NODE>MFColor3f     { return Tok_MFColor3f;  }
<NODE>MFMatrix      { return Tok_MFMatrix;   }
<NODE>MFPnt2f       { return Tok_MFPnt2f;    } 
<NODE>MFPnt3f       { return Tok_MFPnt3f;    } 
<NODE>MFPnt4f       { return Tok_MFPnt4f;    } 
<NODE>MFVec4f       { return Tok_MFVec4f;    } 
<NODE>MFPlane       { return Tok_MFPlane;    }
<NODE>SFColor4f     { return Tok_SFColor4f;  } 
<NODE>SFColor3f     { return Tok_SFColor3f;  }
<NODE>SFMatrix      { return Tok_SFMatrix;   } 
<NODE>SFPnt2f       { return Tok_SFPnt2f;    } 
<NODE>SFPnt3f       { return Tok_SFPnt3f;    } 
<NODE>SFPnt4f       { return Tok_SFPnt4f;    } 
<NODE>SFVec4f       { return Tok_SFVec4f;    }
<NODE>SFPlane       { return Tok_SFPlane;    } 


<NODE>{IdFirstChar}{IdRestChar}* { //fprintf(stderr, "ID : %s\n", vrml97_text);
                                   return ID; }

<mfcolorValue,mffloatValue,mfint32Value,mfrotationValue,mfstringValue>\[ {
    if(parsing_mf)
        OSGScanParseSkel_error("Syntaxfehler: Doppelte [");

    parsing_mf = 1;
}

<mftimeValue,mfvec2fValue,mfvec3fValue>\[ {

    if(parsing_mf)
        OSGScanParseSkel_error("Syntaxfehler: Doppelte [");

    parsing_mf = 1;
}

<mfcolorValue,mffloatValue,mfint32Value,mfrotationValue,mfstringValue>\] {
  if(!parsing_mf) 
      OSGScanParseSkel_error("Ueberzaehlige ]");

  int fieldType = expectToken;

  BEGIN NODE;

  parsing_mf  = 0;
  expectToken = 0;

  return fieldType;
}

<mftimeValue,mfvec2fValue,mfvec3fValue>\] {
  if(!parsing_mf) 
      OSGScanParseSkel_error("Ueberzaehlige ]");

  int fieldType = expectToken;

  BEGIN NODE;

  parsing_mf  = 0;
  expectToken = 0;

  return fieldType;
}
         
    /* sfboolValue ::= TRUE | FALSE; */

<sfboolValue>TRUE {
    BEGIN NODE;
    expectToken = 0;

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    return TOK_SFBOOL;
}

<sfboolValue>FALSE {
    BEGIN NODE;
    expectToken = 0;

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    return TOK_SFBOOL;
}

    /* sfcolorValue ::= float float float; */

<sfcolorValue>({float}{ws}){2}{float} {
  BEGIN NODE;
  expectToken = 0;

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

  return TOK_SFCOLOR;
}

    /* mfcolorValue  ::= sfcolorValue | [ ] | [ sfcolorValues ];    */
    /* sfcolorValues ::= sfcolorValue | sfcolorValue sfcolorValues; */

<mfcolorValue>({float}{ws}){2}{float} {

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    if (parsing_mf)
    {
    }
    else 
    {
        BEGIN NODE;
        expectToken = 0;
        return TOK_MFCOLOR;
    }
}

    /* sffloatValue ::= float; */

<sffloatValue>{float} {
    BEGIN NODE;
    expectToken = 0;

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    return TOK_SFFLOAT;
}

    /* mffloatValue  ::= sffloatValue | [ ] | [ sffloatValues ];    */
    /* sffloatValues ::= sffloatValue | sffloatValue sffloatValues; */

<mffloatValue>{float} {

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    if(parsing_mf)
    {   
    }
    else
    {
        BEGIN NODE;
        expectToken = 0;
        return TOK_MFFLOAT;
    }
}

    /* sfint32Value ::= int32; */

<sfint32Value>{int32} {
    BEGIN NODE;
    expectToken = 0;

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    return TOK_SFINT32;
}

    /* mfint32Value  ::= sfint32Value | [ ] | [ sfint32Values ];    */
    /* sfint32Values ::= sfint32Value | sfint32Value sfint32Values; */

<mfint32Value>{int32} {

   if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    if (parsing_mf)
    {
    }  
    else
    {  
        BEGIN NODE; 
        expectToken = 0;
        return TOK_MFINT32;
    }
}

    /* sfimageValue ::=  int32 int32 int32 ... */

<sfimageValue>{int32}{ws}{int32}{ws}{int32} {
    int w, h, d;
    sscanf(OSGScanParseSkel_text, "%d %d %d", &w, &h, &d);

    if(_pSkel != NULL)
    {
        _pSkel->addFieldValue(OSGScanParseSkel_text);
    }

    sfImageIntsExpected = w*h;
    sfImageIntsParsed   = 0;                          

    if(sfImageIntsExpected != 0)
    {
        BEGIN IN_SFIMG;
    }
    else
    {
        expectToken = 0;
        BEGIN NODE;
        return TOK_SFIMAGE;
    }
}

<IN_SFIMG>{int32} {
    ++sfImageIntsParsed;

    /* std extention: stop pixelread neg values */

    if(*OSGScanParseSkel_text == '-')
    {
        sfImageIntsParsed = sfImageIntsExpected;
    }

    if(_pSkel != NULL)
    {
        _pSkel->addFieldValue(OSGScanParseSkel_text);
    }
        
    if (sfImageIntsParsed == sfImageIntsExpected)
    {
        BEGIN NODE;
        expectToken = 0;
        return TOK_SFIMAGE;
    }
}


    /* sfrotationValue ::= float float float float; */

<sfrotationValue>({float}{ws}){3}{float} {
    BEGIN NODE;
    expectToken = 0;

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    return TOK_SFROTATION;
}

    /* mfrotationValue  ::= sfrotationValue | [ ] | [ sfrotationValues ]; */
    /* sfrotationValues ::= 
            sfrotationValue | sfrotationValue sfrotationValues; */

<mfrotationValue>({float}{ws}){3}{float} {
    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    if(parsing_mf)
    {
    }
    else 
    {
        BEGIN NODE;
        expectToken = 0;
        return TOK_MFCOLOR;
    }
}

    /* sfstringValue ::= string;                                        */
    /* string        ::=
        ".*" ... double-quotes must be \", backslashes must be \\...    */

    /* mfstringValue  ::= sfstringValue | [ ] | [ sfstringValues ];     */
    /* sfstringValues ::= sfstringValue | sfstringValue sfstringValues; */

<sfstringValue>\"   { BEGIN IN_SFS; }
<mfstringValue>\"   { BEGIN IN_MFS; }

<sfstringValue>[^ \"\t\r\,\n]+ {
    BEGIN NODE;
    expectToken = 0;

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    return TOK_SFSTRING;
}

<mfstringValue>[^ \[\]\"\t\r\,\n]+ {
    BEGIN NODE;
    expectToken = 0;

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    return TOK_MFSTRING;
}

<IN_SFS,IN_MFS>\\\"     { yymore(); }
<IN_SFS,IN_MFS>[^\"\n]+ { yymore(); }

<IN_SFS>\" {
    BEGIN NODE;
    expectToken = 0;

    OSGScanParseSkel_leng--;
    OSGScanParseSkel_text[OSGScanParseSkel_leng] = '\0';

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    return TOK_SFSTRING;
}

<IN_MFS>\" {

    OSGScanParseSkel_leng--;
    OSGScanParseSkel_text[OSGScanParseSkel_leng] = '\0';

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    if (parsing_mf)
    {
        BEGIN mfstringValue;
    }
    else 
    {
        BEGIN NODE;
        expectToken = 0;
        return TOK_MFSTRING;
    }
}

    /* sftimeValue ::= double; */

<sftimeValue>{float} {
    BEGIN NODE;
    expectToken = 0;

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    return TOK_SFTIME;
}

    /* mftimeValue  ::= sftimeValue | [ ] | [ sftimeValues ];   */
    /* sftimeValues ::= sftimeValue | sftimeValue sftimeValues; */

<mftimeValue>{float} {

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    if(parsing_mf)
    {   
    }
    else
    {
        BEGIN NODE;
        expectToken = 0;
        return TOK_MFFLOAT;
    }
}


    /* sfvec2fValue ::= float float; */

<sfvec2fValue>{float}{ws}{float} {
    BEGIN NODE;
    expectToken = 0;

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    return TOK_SFVEC2F;
}

    /* mfvec2fValue  ::= sfvec2fValue | [ ] | [ sfvec2fValues];     */
    /* sfvec2fValues ::= sfvec2fValue | sfvec2fValue sfvec2fValues; */

<mfvec2fValue>{float}{ws}{float} {
    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    if(parsing_mf)
    {
    }
    else
    { 
        BEGIN NODE;
        expectToken = 0;
        return TOK_MFVEC2F;
    }
}

    /* sfvec3fValue ::= float float float; */

<sfvec3fValue>({float}{ws}){2}{float} { 
    BEGIN NODE; 
    expectToken = 0; 

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    return TOK_SFVEC3F; 
}

    /* mfvec3fValue  ::= sfvec3fValue | [ ] | [ sfvec3fValues ];    */
    /* sfvec3fValues ::= sfvec3fValue | sfvec3fValue sfvec3fValues; */

<mfvec3fValue>({float}{ws}){2}{float} {
    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    if(parsing_mf)
    {
    }
    else
    {
        BEGIN NODE;
        expectToken = 0;
        return TOK_MFVEC3F;
    }
}

    /* extended types */


<mfcolor3fValue,mfcolor4fValue,mfmatrixValue,mfpnt2fValue>\[ {
    if(parsing_mf)
        OSGScanParseSkel_error("Syntaxfehler: Doppelte [");

    parsing_mf = 1;
}

<mfpnt3fValue,mfpnt4fValue,mfvec4fValue,mfplaneValue>\[ {
    if(parsing_mf)
        OSGScanParseSkel_error("Syntaxfehler: Doppelte [");

    parsing_mf = 1;
}

<mfcolor3fValue,mfcolor4fValue,mfmatrixValue,mfpnt2fValue>\] {
  if(!parsing_mf) 
      OSGScanParseSkel_error("Ueberzaehlige ]");

  int fieldType = expectToken;

  BEGIN NODE;

  parsing_mf  = 0;
  expectToken = 0;

  return fieldType;
}

<mfpnt3fValue,mfpnt4fValue,mfvec4fValue,mfplaneValue>\] {
  if(!parsing_mf) 
      OSGScanParseSkel_error("Ueberzaehlige ]");

  int fieldType = expectToken;

  BEGIN NODE;

  parsing_mf  = 0;
  expectToken = 0;

  return fieldType;
}


    /* sfcolor4fValue ::= float float float float; */

<sfcolor4fValue>({float}{ws}){3}{float} {
  BEGIN NODE;
  expectToken = 0;

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

  return TOK_SFCOLOR4F;
}

    /* sfcolor3fValue ::= float float float; */

<sfcolor3fValue>({float}{ws}){2}{float} {
  BEGIN NODE;
  expectToken = 0;

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

  return TOK_SFCOLOR3F;
}

    /* sfmatrixValue ::= float float float float  */
    /*                   float float float float  */
    /*                   float float float float  */
    /*                   float float float float; */

<sfmatrixValue>({float}{ws}){15}{float} {
  BEGIN NODE;
  expectToken = 0;

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

  return TOK_SFMATRIX;
}

    /* sfpnt2fValue ::= float float; */

<sfpnt2fValue>{float}{ws}{float} {
    BEGIN NODE;
    expectToken = 0;

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    return TOK_SFPNT2F;
}

    /* sfpnt3fValue ::= float float float; */

<sfpnt3fValue>({float}{ws}){2}{float} { 
    BEGIN NODE; 
    expectToken = 0; 

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    return TOK_SFPNT3F; 
}

    /* sfplaneValue ::= float float float float; */

<sfplaneValue>({float}{ws}){3}{float} { 
    BEGIN NODE; 
    expectToken = 0; 

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    return TOK_SFPLANE; 
}

    /* sfpnt4fValue ::= float float float float; */

<sfpnt4fValue>({float}{ws}){3}{float} { 
    BEGIN NODE; 
    expectToken = 0; 

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    return TOK_SFPNT4F; 
}

    /* sfvec4fValue ::= float float float float; */

<sfvec4fValue>({float}{ws}){3}{float} { 
    BEGIN NODE; 
    expectToken = 0; 

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    return TOK_SFVEC4F; 
}

    /* mfcolor4fValue  ::= sfcolor4fValue | [ ] | [ sfcolor4fValues ];      */
    /* sfcolor4fValues ::= sfcolor4fValue | sfcolor4fValue sfcolor4fValues; */

<mfcolor4fValue>({float}{ws}){3}{float} {

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    if (parsing_mf)
    {
    }
    else 
    {
        BEGIN NODE;
        expectToken = 0;
        return TOK_MFCOLOR4F;
    }
}

    /* mfcolor3fValue  ::= sfcolor3fValue | [ ] | [ sfcolor3fValues ];      */
    /* sfcolor3fValues ::= sfcolor3fValue | sfcolor3fValue sfcolor3fValues; */

<mfcolor3fValue>({float}{ws}){2}{float} {

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    if (parsing_mf)
    {
    }
    else 
    {
        BEGIN NODE;
        expectToken = 0;
        return TOK_MFCOLOR3F;
    }
}

    /* mfmatrixValue  ::= sfmatrixValue | [ ] | [ sfmatrixValues ];      */
    /* sfmatrixValues ::= sfmatrixValue | sfmatrixValue sfmatrixfValues; */

<mfmatrixValue>({float}{ws}){15}{float} {

    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    if (parsing_mf)
    {
    }
    else 
    {
        BEGIN NODE;
        expectToken = 0;
        return TOK_MFMATRIX;
    }
}

    /* mfpnt2fValue  ::= sfpnt2fValue | [ ] | [ sfpnt2fValues];     */
    /* sfpnt2fValues ::= sfpnt2fValue | sfpntfValue sfpnt2fValues; */

<mfpnt2fValue>{float}{ws}{float} {
    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    if(parsing_mf)
    {
    }
    else
    { 
        BEGIN NODE;
        expectToken = 0;
        return TOK_MFPNT2F;
    }
}

    /* mfpnt3fValue  ::= sfpnt3fValue | [ ] | [ sfpnt3fValues ];    */
    /* sfpnt3fValues ::= sfpnt3fValue | sfpnt3fValue sfpnt3fValues; */

<mfpnt3fValue>({float}{ws}){2}{float} {
    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    if(parsing_mf)
    {
    }
    else
    {
        BEGIN NODE;
        expectToken = 0;
        return TOK_MFPNT3F;
    }
}

    /* mfplaneValue  ::= sfplaneValue | [ ] | [ sfplaneValues ];    */
    /* sfplaneValues ::= sfplaneValue | sfplaneValue sfplaneValues; */

<mfplaneValue>({float}{ws}){3}{float} {
    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    if(parsing_mf)
    {
    }
    else
    {
        BEGIN NODE;
        expectToken = 0;
        return TOK_MFPLANE;
    }
}


    /* mfpnt4fValue  ::= sfpnt4fValue | [ ] | [ sfpnt4fValues ];    */
    /* sfpnt4fValues ::= sfpnt4fValue | sfpnt4fValue sfpnt4fValues; */

<mfpnt4fValue>({float}{ws}){3}{float} {
    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    if(parsing_mf)
    {
    }
    else
    {
        BEGIN NODE;
        expectToken = 0;
        return TOK_MFPNT4F;
    }
}

    /* mfvec4fValue  ::= sfvec4fValue | [ ] | [ sfvec4fValues ];    */
    /* sfvec4fValues ::= sfvec4fValue | sfvec4fValue sfvec4fValues; */

<mfvec4fValue>({float}{ws}){3}{float} {
    if(_pSkel != NULL)
        _pSkel->addFieldValue(OSGScanParseSkel_text);

    if(parsing_mf)
    {
    }
    else
    {
        BEGIN NODE;
        expectToken = 0;
        return TOK_MFVEC4F;
    }
}

<EXTERROR>. { return 0; }
 
<*>"{" { return OPENBRACE; }
<*>"}" { return CLOSEBRACE; }
<*>"[" { return OPENBRACKET; }
<*>"]" { return CLOSEBRACKET; }
<*>"." { return PERIOD; }

 /* Diese Regel erkennt Whitespace oder ansonsten nicht */
 /* erkannte Token in allen Startzustaenden */
 /* <*>{wsnnl}+ */

 /* Diese Regel erkennt Whitespace, wobei aber Zeilentrenner */
 /* beachtet werden, damit die Zeilenangabe bei eventuellen */
 /* Fehlermeldungen richtig ist. */

<*>{wsnnl}* 

<*>{nl}     { ++iLineNum; }

<*>.    { fprintf(stderr, "%c", OSGScanParseSkel_text[0]); }

%%


extern "C"
{
int OSGScanParseSkel_wrap(void)
{
    BEGIN INITIAL; return 1;
}
}

void expectType(int iType)
{
    expectToken = iType;
}

void abortParser(void)
{
    BEGIN EXTERROR;
}

void resetScanner(void)
{
    iLineNum = 1;
    yy_flush_buffer( YY_CURRENT_BUFFER );
}

#ifdef OSG_WIN32_ICL
#pragma warning (default : 111 810)
#endif

