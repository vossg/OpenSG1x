/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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


#ifndef _OSGSCANPARSESKEL_H_
#define _OSGSCANPARSESKEL_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGScanParseBase.h>
#include <OSGBaseTypes.h>
#include <OSGScanParseSkel.tab.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup 
 *  \brief Brief
 *
 *  detailed
 */

class OSG_SCANPARSE_DLLMAPPING ScanParseSkel
{
  public:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    enum BuildInFieldType
    {
        OSGsfBool     = TOK_SFBOOL,
        OSGsfColor    = TOK_SFCOLOR,
        OSGsfFloat    = TOK_SFFLOAT,
        OSGsfImage    = TOK_SFIMAGE,
        OSGsfInt32    = TOK_SFINT32,
        OSGsfNode     = TOK_SFNODE,
        OSGsfRotation = TOK_SFROTATION,
        OSGsfString   = TOK_SFSTRING,
        OSGsfTime     = TOK_SFTIME,
        OSGsfVec2f    = TOK_SFVEC2F,
        OSGsfVec3f    = TOK_SFVEC3F,
        OSGmfColor    = TOK_MFCOLOR,
        OSGmfFloat    = TOK_MFFLOAT,
        OSGmfInt32    = TOK_MFINT32,
        OSGmfNode     = TOK_MFNODE,
        OSGmfRotation = TOK_MFROTATION,
        OSGmfString   = TOK_MFSTRING,
        OSGmfTime     = TOK_MFTIME,
        OSGmfVec2f    = TOK_MFVEC2F,
        OSGmfVec3f    = TOK_MFVEC3F,
        
        OSGmfColor4f  = TOK_MFCOLOR4F,
        OSGmfMatrix   = TOK_MFMATRIX,
        OSGmfPnt2f    = TOK_MFPNT2F,
        OSGmfPnt3f    = TOK_MFPNT3F,
        OSGmfPnt4f    = TOK_MFPNT4F,
        OSGmfVec4f    = TOK_MFVEC4F,
        OSGsfColor4f  = TOK_SFCOLOR4F,
        OSGsfMatrix   = TOK_SFMATRIX,
        OSGsfPnt2f    = TOK_SFPNT2F,
        OSGsfPnt3f    = TOK_SFPNT3F,
        OSGsfPnt4f    = TOK_SFPNT4F,
        OSGsfVec4f    = TOK_SFVEC4F
    };

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    ScanParseSkel(const ScanParseSkel &source);
    void operator =(const ScanParseSkel &source);

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    Bool   _bMapTypeIds;
    Char8 *_szReferenceHeader;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    void setMapTypeIds(Bool bVal);

    void setReferenceHeader(const Char8 *szReferenceHeader);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    ScanParseSkel(void);
    virtual ~ScanParseSkel(void); 

    /*------------------------- your_category -------------------------------*/

    virtual void scanFile(const Char8 *szFilename, UInt32 uiOptions);

    /*------------------------- your_operators ------------------------------*/

    virtual Bool verifyHeader           (const Char8 *szHeader);

    virtual void beginProtoInterface    (const Char8 *szProtoname);
    virtual void endProtoInterface      (void);

    virtual void addProtoEventIn        (const Char8 *szEventType,
                                         const Char8 *szEventName); 

    virtual void addProtoEventOut       (const Char8 *szEventType,
                                         const Char8 *szEventName); 

    virtual void beginProtoField        (const Char8  *szFieldType,
                                         const UInt32  uiFieldTypeId,
                                         const Char8  *szFieldName); 

    virtual void endProtoField          (void);

    virtual void beginProtoExposedField (const Char8  *szFieldType,
                                         const UInt32  uiFieldTypeId,
                                         const Char8  *szFieldName); 

    virtual void endProtoExposedField   (void);


    virtual void beginField             (const Char8 *szFieldname,
                                         const UInt32 uiFieldTypeId);

    virtual void endField               (void);


    virtual void beginNode              (const Char8 *szNodeTypename,
                                         const Char8 *szNodename);
    
    virtual void endNode                (void);

    virtual void use                    (const Char8 *szName);

    virtual void addFieldValue          (const Char8 *szFieldVal);

    virtual void addRoute               (const Char8 *szOutNodename,
                                         const Char8 *szOutFieldname,
                                         const Char8 *szInNodename,
                                         const Char8 *szInFieldname);

    /*------------------------- assignment ----------------------------------*/

    bool              getMapFieldTypes  (void);

    virtual Int32  mapExtIntFieldType(const Int32 iFieldTypeId);

    virtual UInt32 getFieldType      (const Char8 *szFieldname);


    /*------------------------- comparison ----------------------------------*/
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef ScanParseSkel *ScanParseSkelP;

OSG_END_NAMESPACE

#endif /* _OSGSCANPARSESKEL_H_ */
