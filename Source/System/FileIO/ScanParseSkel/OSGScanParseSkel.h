/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGScanParseSkel.tab.h>

OSG_BEGIN_NAMESPACE

//! Parser / Scanner Skeleton for VRML97 syntax based file formats 
//! \ingroup GrpSystemDrawablesGeometrymetryLoaderLib 

class OSG_SYSTEMLIB_DLLMAPPING ScanParseSkel
{
    /*==========================  PUBLIC  =================================*/
  public:

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
        OSGmfColor4i  = TOK_MFCOLOR4I,
        OSGmfColor3f  = TOK_MFCOLOR3F,
        OSGmfMatrix   = TOK_MFMATRIX,
        OSGmfPnt2f    = TOK_MFPNT2F,
        OSGmfPnt3f    = TOK_MFPNT3F,
        OSGmfPnt4f    = TOK_MFPNT4F,
        OSGmfVec4f    = TOK_MFVEC4F,
        OSGmfPlane    = TOK_MFPLANE,
        OSGsfColor4f  = TOK_SFCOLOR4F,
        OSGsfColor4i  = TOK_SFCOLOR4I,
        OSGsfColor3f  = TOK_SFCOLOR3F,
        OSGsfMatrix   = TOK_SFMATRIX,
        OSGsfPnt2f    = TOK_SFPNT2F,
        OSGsfPnt3f    = TOK_SFPNT3F,
        OSGsfPnt4f    = TOK_SFPNT4F,
        OSGsfVec4f    = TOK_SFVEC4F,
        OSGsfPlane    = TOK_SFPLANE,
        OSGsfVolume   = TOK_SFVOLUME
    };

    enum 
    {
        LastOption = 0x0001
    };

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ScanParseSkel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ScanParseSkel(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Scan                                    */
    /*! \{                                                                 */

    virtual void scanFile         (const Char8  *szFilename, 
                                         UInt32  uiReplaceOptions);

    virtual void scanFile         (const Char8  *szFilename, 
                                         UInt32  uiAddOptions, 
                                         UInt32  uiSubOptions);

    virtual void setDefaultOptions(      UInt32  uiOptions   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Prototypes                               */
    /*! \{                                                                 */

    virtual bool verifyHeader          (const Char8 *szHeader);

    virtual void beginProto            (const Char8 *szProtoname);
    virtual void endProto              (void);

    virtual void beginScript           (const Char8 *szProtoname);
    virtual void endScript             (void);

    virtual void addEventInDecl        (const Char8 *szEventType,
                                        const Char8 *szEventName); 

    virtual void addEventOutDecl       (const Char8 *szEventType,
                                        const Char8 *szEventName); 

    virtual void beginFieldDecl        (const Char8  *szFieldType,
                                        const UInt32  uiFieldTypeId,
                                        const Char8  *szFieldName); 

    virtual void endFieldDecl          (void);

    virtual void beginExposedFieldDecl (const Char8  *szFieldType,
                                        const UInt32  uiFieldTypeId,
                                        const Char8  *szFieldName); 

    virtual void endExposedFieldDecl   (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Fields                                   */
    /*! \{                                                                 */

    virtual void beginField(const Char8  *szFieldname,
                            const UInt32  uiFieldTypeId);

    virtual void endField  (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Nodes                                    */
    /*! \{                                                                 */

    virtual void beginNode(const Char8 *szNodeTypename,
                           const Char8 *szNodename);
    
    virtual void endNode  (void);

    virtual void use      (const Char8 *szName);
    virtual void is       (const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Misc                                     */
    /*! \{                                                                 */

    virtual void addFieldValue(const Char8 *szFieldVal);

    virtual void addRoute     (const Char8 *szOutNodename,
                               const Char8 *szOutFieldname,
                               const Char8 *szInNodename,
                               const Char8 *szInFieldname);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Type Information                             */
    /*! \{                                                                 */

    bool           getMapFieldTypes  (void);

    virtual Int32  mapExtIntFieldType(const Char8 *szFieldname,
                                      const Int32  iFieldTypeId);

    virtual UInt32 getFieldType      (const Char8 *szFieldname);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    UInt32  _uiCurrOptions;
    UInt32  _uiDefOptions;
    bool    _bMapTypeIds;
    Char8  *_szReferenceHeader;


    void reset             (      void);

    void setMapTypeIds     (      bool   bVal);

    void setReferenceHeader(const Char8 *szReferenceHeader);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    ScanParseSkel(const ScanParseSkel &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ScanParseSkel &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_END_NAMESPACE

#define OSGSCANPARSESKEL_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGSCANPARSESKEL_H_ */

