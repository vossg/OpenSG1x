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

#define OSG_COMPILESYSTEMLIB

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

%}

%token DEF
%token USE
%token ROUTE
%token PERIOD
%token TO
%token OPENBRACE
%token CLOSEBRACE
%token ID
%token PROTO
%token OPENBRACKET
%token CLOSEBRACKET
%token EXTERNPROTO
%token IS

%token EVENTIN
%token EVENTOUT
%token EXPOSEDFIELD
%token FIELD

%token SCRIPT

%token SFN_NULL

%token TOK_SFBOOL
%token TOK_SFCOLOR
%token TOK_SFFLOAT
%token TOK_SFIMAGE
%token TOK_SFINT32
%token TOK_SFNODE
%token TOK_SFROTATION
%token TOK_SFSTRING
%token TOK_SFTIME
%token TOK_SFVEC2F
%token TOK_SFVEC3F
%token TOK_MFCOLOR
%token TOK_MFFLOAT
%token TOK_MFINT32
%token TOK_MFNODE 
%token TOK_MFROTATION
%token TOK_MFSTRING
%token TOK_MFTIME
%token TOK_MFVEC2F
%token TOK_MFVEC3F

%token Tok_MFColor 
%token Tok_MFFloat 
%token Tok_MFInt32 
%token Tok_MFNode 
%token Tok_MFRotation 
%token Tok_MFString 
%token Tok_MFTime 
%token Tok_MFVec2f 
%token Tok_MFVec3f 
%token Tok_SFBool 
%token Tok_SFColor 
%token Tok_SFFloat 
%token Tok_SFImage 
%token Tok_SFInt32 
%token Tok_SFNode 
%token Tok_SFRotation 
%token Tok_SFString 
%token Tok_SFTime 
%token Tok_SFVec2f 
%token Tok_SFVec3f 


%token TOK_MFCOLOR4F
%token TOK_MFMATRIX
%token TOK_MFPNT2F
%token TOK_MFPNT3F
%token TOK_MFPNT4F
%token TOK_MFVEC4F

%token TOK_SFCOLOR4F
%token TOK_SFMATRIX
%token TOK_SFPNT2F
%token TOK_SFPNT3F
%token TOK_SFPNT4F
%token TOK_SFVEC4F



%token Tok_MFColor4f
%token Tok_MFMatrix
%token Tok_MFPnt2f
%token Tok_MFPnt3f
%token Tok_MFPnt4f
%token Tok_MFVec4f

%token Tok_SFColor4f
%token Tok_SFMatrix
%token Tok_SFPnt2f
%token Tok_SFPnt3f
%token Tok_SFPnt4f
%token Tok_SFVec4f

%%

vrmlScene : statementsORempty
;

statementsORempty : statements
                  | empty 
;

statements : statements statement 
           |            statement  
;

statement : nodeStatement 
          | protoStatement 
          | routeStatement 
;

nodeStatement : node 
              | DEF 
                nodeNameId  { setName(szName1, OSGScanParseSkel_text); }
                node 
              | USE 
                nodeNameId  { if(_pSkel != NULL)
                                  _pSkel->use(OSGScanParseSkel_text); }
;

rootNodeStatement : node 
                  | DEF 
                    nodeNameId { setName(szName1, OSGScanParseSkel_text); }
                    node 
;

protoStatement : proto 
               | externproto 
;


protoStatementsORempty : protoStatements
                       |
;

protoStatements : protoStatements protoStatement
                |                 protoStatement
;

protoId : nodeTypeId { if(_pSkel != NULL) 
                        _pSkel->beginProtoInterface(OSGScanParseSkel_text); }
        | SCRIPT     { if(_pSkel != NULL) 
                        _pSkel->beginProtoInterface(OSGScanParseSkel_text); }

proto : PROTO 
        protoId 
        OPENBRACKET 
        interfaceDeclarationsORempty 
        CLOSEBRACKET { if(_pSkel != NULL) 
                        _pSkel->endProtoInterface(); }
        OPENBRACE 
        protoBodyORempty
        CLOSEBRACE
;

protoBodyORempty : protoBody
                 | empty
;

protoBody : protoStatementsORempty rootNodeStatement statementsORempty
;

interfaceDeclarationsORempty : interfaceDeclarations
                             | empty
;

interfaceDeclarations : interfaceDeclarations interfaceDeclaration 
                      |                       interfaceDeclaration
;


restrictedInterfaceDeclaration : EVENTIN  
                                 fieldType  { setName(szName1, 
                                                      OSGScanParseSkel_text); }
                                 eventInId  { if(_pSkel != NULL)
                                               _pSkel->addProtoEventIn(
                                                szName1,
                                                OSGScanParseSkel_text); 
                                              freeName(szName1); }
                               | EVENTOUT 
                                 fieldType  { setName(szName1, 
                                                      OSGScanParseSkel_text); }
                                 eventOutId { if(_pSkel != NULL)
                                               _pSkel->addProtoEventOut(
                                                szName1,
                                                OSGScanParseSkel_text); 
                                              freeName(szName1); }
                               | FIELD    
                                 fieldType  { setName(szName1, 
                                                      OSGScanParseSkel_text); }
                                 fieldId    { expectType(nextType); 
                                              if(_pSkel != NULL)
                                               _pSkel->beginProtoField(
                                                szName1,
                                                nextType,
                                                OSGScanParseSkel_text); 
                                              freeName(szName1); } 
                                 fieldValue { nextType = 0; 
                                              if(_pSkel != NULL)
                                               _pSkel->endProtoField();
                                             }
;

interfaceDeclaration : restrictedInterfaceDeclaration
                     | EXPOSEDFIELD 
                       fieldType    { setName(szName1, 
                                              OSGScanParseSkel_text); }
                       fieldId      { expectType(nextType);  
                                      if(_pSkel != NULL)
                                       _pSkel->beginProtoExposedField(
                                        szName1,
                                        nextType,
                                        OSGScanParseSkel_text); 
                                       freeName(szName1); }
                       fieldValue   { nextType = 0; 
                                      if(_pSkel != NULL)
                                       _pSkel->endProtoExposedField(); }
;

externproto : EXTERNPROTO 
              nodeTypeId 
              OPENBRACKET 
              externInterfaceDeclarationsORempty
              CLOSEBRACKET 
              URLList 
;

externInterfaceDeclarationsORempty : externInterfaceDeclarations
                                   | empty
;

externInterfaceDeclarations : 
        externInterfaceDeclarations externInterfaceDeclaration
    |                               externInterfaceDeclaration
;

externInterfaceDeclaration : EVENTIN      fieldType eventInId 
                           | EVENTOUT     fieldType eventOutId 
                           | FIELD        fieldType fieldId 
                           | EXPOSEDFIELD fieldType fieldId 
;

routeStatement : ROUTE 
                 nodeNameId { setName(szName1, OSGScanParseSkel_text); }
                 PERIOD     
                 eventOutId { setName(szName2, OSGScanParseSkel_text); }
                 TO 
                 nodeNameId { setName(szName3, OSGScanParseSkel_text); }
                 PERIOD 
                 eventInId  { if(_pSkel != NULL)
                                _pSkel->addRoute(szName1, 
                                                 szName2,
                                                 szName3,
                                                 OSGScanParseSkel_text);
                              freeName(szName1);
                              freeName(szName2);
                              freeName(szName3);
                            }
;

URLList : fieldValue
;

empty :
;

node : nodeTypeId { if(_pSkel != NULL)
                     _pSkel->beginNode(OSGScanParseSkel_text, szName1); 

                    freeName(szName1);
                  }
       OPENBRACE 
       nodeBodyORempty   
       CLOSEBRACE { if(_pSkel != NULL)
                     _pSkel->endNode(); }
     | SCRIPT     { if(_pSkel != NULL)
                     _pSkel->beginNode(OSGScanParseSkel_text, szName1); 

                    freeName(szName1);
                  }
       OPENBRACE
       scriptBodyORempty 
       CLOSEBRACE { if(_pSkel != NULL)
                     _pSkel->endNode(); }
;

nodeBodyORempty : nodeBody
                | empty
;

nodeBody : nodeBody nodeBodyElement 
         |          nodeBodyElement
;

scriptBodyORempty : scriptBody
                  | empty
;

scriptBody : scriptBody scriptBodyElement 
           |            scriptBodyElement
;

/*
scriptBodyElement : nodeBodyElement 
                  | restrictedInterfaceDeclaration 
                  | EVENTIN  fieldType eventInId  IS eventInId 
                  | EVENTOUT fieldType eventOutId IS eventOutId 
                  | FIELD    fieldType fieldId    IS fieldId 
;
*/

/*
rInterfaceDeclarationScript : EVENTIN  
                              fieldType  { setName(szName1, 
                                                   OSGScanParseSkel_text); }
                              eventInId  { if(_pSkel != NULL)
                                            _pSkel->addProtoEventIn(
                                             szName1,
                                             OSGScanParseSkel_text); 
                                           freeName(szName1); }
                            | EVENTOUT 
                              fieldType  { setName(szName1, 
                                                   OSGScanParseSkel_text); }
                              eventOutId { if(_pSkel != NULL)
                                            _pSkel->addProtoEventOut(
                                             szName1,
                                             OSGScanParseSkel_text); 
                                            freeName(szName1); }
                               | FIELD    
                                 fieldType  { setName(szName1, 
                                                      OSGScanParseSkel_text); }
                                 fieldId    { expectType(nextType); 
                                              if(_pSkel != NULL)
                                               _pSkel->beginProtoField(
                                                szName1,
                                                nextType,
                                                OSGScanParseSkel_text); 
                                              freeName(szName1); } 
                                 fieldValue { nextType = 0; 
                                              if(_pSkel != NULL)
                                               _pSkel->endProtoField();
                                             }
;
*/

/*
                  | EVENTIN  fieldType eventInId  IS eventInId 
                  | EVENTOUT fieldType eventOutId IS eventOutId 
*/

resInterfaceDeclarationScriptEvent : EVENTIN  
                                     fieldType  
                                     eventInId  
                                   | EVENTOUT 
                                     fieldType  
                                     eventOutId 
;

resInterfaceDeclarationScriptEventEnd : IS eventId 
                                      |
;

resInterfaceDeclarationScriptField : FIELD     { fprintf(stderr,"XX1\n"); }
                                     fieldType { fprintf(stderr,"XX2\n"); }
                                     fieldId   { fprintf(stderr,"XX3\n"); }
;

resInterafceDeclarationScriptFieldEnd : IS fieldId { fprintf(stderr,"XX4\n"); }
                                      | fieldValue { fprintf(stderr,"XX5\n"); }
;

scriptBodyElement : nodeBodyElement 
                  | resInterfaceDeclarationScriptEvent 
                    resInterfaceDeclarationScriptEventEnd
                  | resInterfaceDeclarationScriptField { fprintf(stderr,"XX6\n"); }
                    resInterafceDeclarationScriptFieldEnd
                    { fprintf(stderr,"XX7\n"); }
;


nodeBodyElement : fieldId 
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
                   }
                  fieldValue
                  { if(_pSkel != NULL)
                     _pSkel->endField();
                  }
                | routeStatement 
                | protoStatement 
;

//                | generalId IS generalId 

generalId  : ID
;

nodeNameId : ID 
;

nodeTypeId : ID
;

fieldId    : ID 
;

eventId    : ID 
;

eventInId  : ID 
;

eventOutId : ID ;


fieldType : Tok_MFColor     { nextType = TOK_MFCOLOR;    }
          | Tok_MFFloat     { nextType = TOK_MFFLOAT;    }
          | Tok_MFInt32     { nextType = TOK_MFINT32;    }
          | Tok_MFNode      { nextType = TOK_MFNODE;     }
          | Tok_MFRotation  { nextType = TOK_MFROTATION; }
          | Tok_MFString    { nextType = TOK_MFSTRING;   }
          | Tok_MFTime      { nextType = TOK_MFTIME;     }
          | Tok_MFVec2f     { nextType = TOK_MFVEC2F;    }
          | Tok_MFVec3f     { nextType = TOK_MFVEC3F;    }
          | Tok_SFBool      { nextType = TOK_SFBOOL;     }
          | Tok_SFColor     { nextType = TOK_SFCOLOR;    }
          | Tok_SFFloat     { nextType = TOK_SFFLOAT;    }
          | Tok_SFImage     { nextType = TOK_SFIMAGE;    }
          | Tok_SFInt32     { nextType = TOK_SFINT32;    }
          | Tok_SFNode      { nextType = TOK_SFNODE;     }
          | Tok_SFRotation  { nextType = TOK_SFROTATION; }
          | Tok_SFString    { nextType = TOK_SFSTRING;   }
          | Tok_SFTime      { nextType = TOK_SFTIME;     }
          | Tok_SFVec2f     { nextType = TOK_SFVEC2F;    }
          | Tok_SFVec3f     { nextType = TOK_SFVEC3F;    }
          | Tok_MFColor4f   { nextType = TOK_MFCOLOR4F;  }
          | Tok_MFMatrix    { nextType = TOK_MFMATRIX;   }
          | Tok_MFPnt2f     { nextType = TOK_MFPNT2F;    }
          | Tok_MFPnt3f     { nextType = TOK_MFPNT3F;    }
          | Tok_MFPnt4f     { nextType = TOK_MFPNT4F;    }
          | Tok_MFVec4f     { nextType = TOK_MFVEC4F;    }
          | Tok_SFColor4f   { nextType = TOK_SFCOLOR4F;  }
          | Tok_SFMatrix    { nextType = TOK_SFMATRIX;   }
          | Tok_SFPnt2f     { nextType = TOK_SFPNT2F;    }
          | Tok_SFPnt3f     { nextType = TOK_SFPNT3F;    }
          | Tok_SFPnt4f     { nextType = TOK_SFPNT4F;    }
          | Tok_SFVec4f     { nextType = TOK_SFVEC4F;    }
;


fieldValue : TOK_SFBOOL
           | TOK_SFCOLOR
           | TOK_SFFLOAT
           | TOK_SFIMAGE
           | TOK_SFINT32
           | TOK_SFNODE     sfnodeValue
           | TOK_SFROTATION
           | TOK_SFSTRING
           | TOK_SFTIME
           | TOK_SFVEC2F
           | TOK_SFVEC3F
           | TOK_MFCOLOR
           | TOK_MFFLOAT
           | TOK_MFINT32
           | TOK_MFNODE     mfnodeValue
           | TOK_MFROTATION 
           | TOK_MFSTRING 
           | TOK_MFTIME
           | TOK_MFVEC2F
           | TOK_MFVEC3F
           | TOK_MFCOLOR4F
           | TOK_MFMATRIX
           | TOK_MFPNT2F
           | TOK_MFPNT3F
           | TOK_MFPNT4F
           | TOK_MFVEC4F
           | TOK_SFCOLOR4F
           | TOK_SFMATRIX
           | TOK_SFPNT2F
           | TOK_SFPNT3F
           | TOK_SFPNT4F
           | TOK_SFVEC4F
;


sfnodeValue : nodeStatement 
            | SFN_NULL
;

mfnodeValue : nodeStatement             
            | OPENBRACKET nodeStatementsORempty CLOSEBRACKET
;

nodeStatementsORempty : nodeStatements
                      | empty
;

nodeStatements : nodeStatements nodeStatement 
               |                nodeStatement  
;


%%

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


