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

#ifndef _OSGVRMLFILE_H_
#define _OSGVRMLFILE_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGSystemDef.h>

#include <map>
#include <stack>
#include <vector>

#include <OSGBaseTypes.h>
#include <OSGScanParseSkel.h>
#include <OSGScanParseFieldTypeMapper.h>

#include <OSGFieldContainerPtr.h>
#include <OSGField.h>
#include <OSGFieldContainer.h>

#include <OSGVRMLNodeFactory.h>

OSG_BEGIN_NAMESPACE

typedef VRMLNodeFactory<ScanParseFieldTypeMapper<ScanParseSkel> > Parent;

#ifndef OSG_COMPILEVRMLLOADERINST
#ifndef __sgi
extern
template OSG_SYSTEMLIB_DLLMAPPING
VRMLNodeFactory<ScanParseFieldTypeMapper<ScanParseSkel> >;
#endif
#endif

/*! \ingroup GeometryLoaderLib
 *  \brief VRML97 Loader (Geometry only)
 */

class OSG_SYSTEMLIB_DLLMAPPING VRMLFile : public Parent
{
  protected:

    typedef Parent Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    enum 
    {
        CreateNormals       = Inherited::LastOption << 1,
        StripeGeometry      = CreateNormals         << 1,
        LogProtoGeneration  = StripeGeometry        << 1,
        LogObjectGeneration = LogProtoGeneration    << 1,

        LastOption          = LogObjectGeneration
    };

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLFile(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLFile(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Skel replacements                          */
    /*! \{                                                                 */

    virtual void   scanFile     (const Char8  *szFilename, 
                                       UInt32  uiOptions);


    virtual void   beginNode    (const Char8 *szNodeTypename,
                                 const Char8 *szNodename);
    
    virtual void   endNode      (void);


    virtual void   beginField   (const Char8  *szFieldname,
                                 const UInt32  uiFieldTypeId);

    virtual void   endField     (void);


    virtual void   addFieldValue(const Char8 *szFieldVal);


    virtual UInt32 getFieldType (const Char8 *szFieldname);


    virtual void   use          (const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Helper                                  */
    /*! \{                                                                 */
    
    void    scanStandardPrototypes  (const Char8  *szFilename, 
                                           UInt32  uiOptions);
    
    void    createStandardPrototypes(void);
    
    NodePtr getRoot                 (void);
    
    NodePtr cloneTree               (NodePtr pRootNode);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef map<IDString, FieldContainerPtr> NameContainerMap;
    typedef map<IDString, VRMLNodeDesc    *> NameDescriptionMap;
 
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

          NodePtr                    _pRootNode;

          VRMLNodeDesc *             _pCurrNodeDesc;
    stack<VRMLNodeDesc *>            _sNodeDescs;

          FieldContainerPtr          _pCurrentFC;
          Field                     *_pCurrentField;
    const FieldDescription          *_pCurrentFieldDesc;

    stack<      FieldContainerPtr >  _fcStack;
    stack<      Field            *>  _fStack;
    stack<const FieldDescription *>  _fdStack;

         NameContainerMap            _nameFCMap;
         NameDescriptionMap          _nameDescMap;


    void              initIntExtFieldTypeMapper(void);
    void              initExtIntFieldTypeMapper(void);

    FieldContainerPtr findFCByName             (const Char8  *szName,
                                                      NodePtr pNode);

    void              setContainerFieldValue   (const FieldContainerPtr &pFC);

    FieldContainerPtr findReference            (const Char8 *szName);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLFile(const VRMLFile &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLFile &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef VRMLFile *VRMLFileP;

OSG_END_NAMESPACE

#define OSGVRMLFILE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGVRMLFILE_H_ */
