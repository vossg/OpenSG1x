/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000,2001 by the OpenSG Forum               *
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


#ifndef _OSGVRMLNODEDESCS_H_
#define _OSGVRMLNODEDESCS_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>
#include <vector>

#ifdef OSG_SGI_STL
#ifdef OSG_HASH_MAP_AS_EXT
#include <ext/hash_map>
#else
#include <hash_map>
#endif
#else
#include <map>
#endif

#include <OSGFieldContainerPtr.h>
#include <OSGField.h>
#include <OSGFieldContainer.h>
#include <OSGAttachment.h>
#include <OSGGeoProperty.h>
#include <OSGSFSysTypes.h>
#include <OSGSimpleMaterial.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class VRMLAppearanceDesc;
class VRMLMaterialDesc;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

struct GenericAttDesc
{
    typedef Attachment    Parent;
    typedef AttachmentPtr ParentPtr;

    static const char *getTypeName      (void) { return "GenericAtt"; }
    static const char *getParentTypeName(void) { return "Attachment"; }
    static const char *getGroupName     (void) { return "VRMLGenAtt"; }
};

typedef DynFieldAttachment<GenericAttDesc>  GenericAtt;
typedef GenericAtt::PtrType                 GenericAttPtr;

#ifndef OSG_COMPILEVRMLNODEDESCINST
#if defined(__sgi)

#pragma do_not_instantiate DynFieldAttachment<GenericAttDesc>::_type

#else

OSG_ABSTR_FC_DLLEXPORT_DECL(DynFieldAttachment, 
                            GenericAttDesc,
                            OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

template <>
struct FieldDataTraits<GenericAttPtr> : public Traits
{
    enum                         { StringConvertable = 0x00  };

    static Char8 *getSName(void) { return "SFGenericAttPtr"; }
    static Char8 *getMName(void) { return "MFGenericAttPtr"; }
};


typedef SField<GenericAttPtr>       SFGenericPtr;

#ifndef OSG_COMPILEVRMLNODEDESCINST
#if defined(__sgi)

#pragma do_not_instantiate SField<GenericAttPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, GenericAttPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif


/** \brief MFWindowPtr
 */

typedef MField<GenericAttPtr>       MFGenericAttPtr;


#ifndef OSG_COMPILEVRMLNODEDESCINST
#if defined(__sgi)

#pragma do_not_instantiate MField<GenericAttPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, GenericAttPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup 
 *  \brief Brief
 *
 *  detailed
 */

class OSG_SYSTEMLIB_DLLMAPPING VRMLNodeDesc 
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

    VRMLNodeDesc(const VRMLNodeDesc &source);
    void operator =(const VRMLNodeDesc &source);

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

#ifdef OSG_SGI_STL
    typedef hash_map<     const Char8 *,  UInt32, 
                     hash<const Char8 *>, EQString> FieldNameTypeHash;
#else
    typedef map     <     const Char8 *,  UInt32, 
                                          LTString> FieldNameTypeHash;
#endif

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    FieldNameTypeHash _mFieldTypes;

    GenericAttPtr     _pGenAtt;

    FieldContainerPtr _pNodeProto;
    FieldContainerPtr _pNodeCoreProto;

    Field            *_pCurrField;

    String            _szCurrentName;
    bool              _bSaveOnEnd;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSG::Field *getField(FieldContainerPtr  pFC1, 
                         FieldContainerPtr  pFC2,
                         GenericAttPtr      pGenAtt,
                         const Char8       *szFieldname);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VRMLNodeDesc (void);

    virtual ~VRMLNodeDesc (void); 

    /*------------------------- your_category -------------------------------*/

    virtual void init (const Char8 *szName);

    virtual void reset(void);

    virtual void              setOnEndSave         (const Char8 *szName);
    virtual void              clearOnEndSave       (void);
    virtual Bool              getOnEndSave         (void);
    virtual const Char8 *     getSavename          (void);
    virtual FieldContainerPtr getSaveFieldContainer(void) ;

    /*------------------------- your_operators ------------------------------*/

    /*------------------------- assignment ----------------------------------*/

    virtual OSG::Field *getField(const Char8   *szFieldname);
    
    virtual void getFieldAndDesc(      FieldContainerPtr   pFC,
                                 const Char8             * szFieldname,
                                       Field             *&pField,
                                 const FieldDescription  *&pDesc);
    

    /*-----------------------------------------------------------------------*/

    virtual Bool prototypeAddField     (const Char8  *szFieldType,
                                        const UInt32  uiFieldTypeId,
                                        const Char8  *szFieldName); 
    
    virtual void prototypeAddFieldValue(const Char8 *szFieldVal);
    
    virtual void endProtoInterface     (void);

    /*----------------------------------------------------------------------*/

    virtual FieldContainerPtr beginNode    (const Char8       *szTypename,
                                            const Char8       *szName,
                                            FieldContainerPtr  pCurrentFC);
    
    virtual void              endNode      (FieldContainerPtr);

    virtual void              addFieldValue(      Field *pField,
                                            const Char8 *szFieldVal);

    virtual Bool              use          (FieldContainerPtr);
   
    /*------------------------- comparison ----------------------------------*/
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup 
 *  \brief Brief
 *
 *  detailed
 */

class OSG_SYSTEMLIB_DLLMAPPING VRMLShapeDesc : public VRMLNodeDesc 
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

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef VRMLNodeDesc Inherited;

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

    VRMLShapeDesc(const VRMLShapeDesc &source);
    void operator =(const VRMLShapeDesc &source);

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

    VRMLAppearanceDesc *_pAppearanceDesc;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VRMLShapeDesc(void);

    virtual ~VRMLShapeDesc(void); 

    /*------------------------- your_category -------------------------------*/

    virtual void              init                 (const Char8 *szName);
    
    /*------------------------- your_operators ------------------------------*/

    virtual Bool prototypeAddField(const Char8  *szFieldType,
                                   const UInt32  uiFieldTypeId,
                                   const Char8  *szFieldName); 

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                         Field             *&pField,
                                   const FieldDescription  *&pDesc);


    /*------------------------- your_operators ------------------------------*/
    
    virtual FieldContainerPtr beginNode(const Char8       *szTypename,
                                        const Char8       *szName,
                                        FieldContainerPtr  pCurrentFC);


    virtual void              endNode      (FieldContainerPtr pFC);

    /*------------------------- assignment ----------------------------------*/

    void setAppearanceDesc(VRMLAppearanceDesc *pAppearanceDesc);

    /*------------------------- comparison ----------------------------------*/
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup 
 *  \brief Brief
 *
 *  detailed
 */

class OSG_SYSTEMLIB_DLLMAPPING VRMLGeometryDesc : public VRMLNodeDesc
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

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef VRMLNodeDesc Inherited;

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

    VRMLGeometryDesc(const VRMLGeometryDesc &source);
    void operator =(const VRMLGeometryDesc &source);

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

    Bool            _bInIndex;
    UInt32          _uiNumVertices;

    GeoPTypePtr   _pTypeField;
    GeoPLengthPtr _pLengthField;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VRMLGeometryDesc(void);

    virtual ~VRMLGeometryDesc(void); 

    /*------------------------- your_category -------------------------------*/

    virtual void init           (const Char8 *szName);

    /*------------------------- your_category -------------------------------*/

    virtual Bool prototypeAddField(const Char8  *szFieldType,
                                   const UInt32  uiFieldTypeId,
                                   const Char8  *szFieldName); 

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                         Field             *&pField,
                                   const FieldDescription  *&pDesc);


    /*------------------------- your_category -------------------------------*/

    virtual FieldContainerPtr beginNode    (const Char8       *szTypename,
                                            const Char8       *szName,
                                            FieldContainerPtr  pCurrentFC);

    virtual void              endNode      (FieldContainerPtr pFC);

    virtual void              addFieldValue(      Field *pField,
                                            const Char8 *szFieldVal);

    /*------------------------- your_operators ------------------------------*/

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup 
 *  \brief Brief
 *
 *  detailed
 */

class OSG_SYSTEMLIB_DLLMAPPING VRMLGeometryPartDesc : public VRMLNodeDesc
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

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef VRMLNodeDesc Inherited;

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

    VRMLGeometryPartDesc(const VRMLGeometryPartDesc &source);
    void operator =(const VRMLGeometryPartDesc &source);

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

    Char8 *_szVRMLPartname;
    Char8 *_szOSGPartname;
    Char8 *_szOSGProtoname;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VRMLGeometryPartDesc(Char8 *szVRMLPartname,
                         Char8 *szOSGPartname,
                         Char8 *szOSGProtoname);

    virtual ~VRMLGeometryPartDesc(void); 

    /*------------------------- your_category -------------------------------*/

    virtual void init           (const Char8 *szName);

    /*------------------------- your_category -------------------------------*/

    virtual Bool prototypeAddField(const Char8  *szFieldType,
                                   const UInt32  uiFieldTypeId,
                                   const Char8  *szFieldName); 

    virtual void getFieldAndDesc  (      OSG::FieldContainerPtr   pFC,
                                   const Char8                  * szFieldname,
                                         OSG::Field             *&pField,
                                   const OSG::FieldDescription  *&pDesc);

    /*------------------------- your_category -------------------------------*/

    virtual FieldContainerPtr beginNode(const Char8       *szTypename,
                                        const Char8       *szName,
                                        FieldContainerPtr  pCurrentFC);

    /*------------------------- your_operators ------------------------------*/

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup 
 *  \brief Brief
 *
 *  detailed
 */

class OSG_SYSTEMLIB_DLLMAPPING VRMLAppearanceDesc : public VRMLNodeDesc
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

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef VRMLNodeDesc Inherited;

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

    VRMLAppearanceDesc(const VRMLAppearanceDesc &source);
    void operator =(const VRMLAppearanceDesc &source);

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

    VRMLMaterialDesc *_pMaterialDesc;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VRMLAppearanceDesc();

    virtual ~VRMLAppearanceDesc(void); 

    /*------------------------- your_category -------------------------------*/

    virtual void init                  (const Char8 *szName);

    virtual void        resetMat       (void);
    virtual MaterialPtr getMat         (void);

    virtual void        setMaterialDesc(VRMLMaterialDesc *pMaterialDesc);

    virtual FieldContainerPtr getSaveFieldContainer(void);

    /*------------------------- your_category -------------------------------*/

    virtual Bool prototypeAddField(const Char8  *szFieldType,
                                   const UInt32  uiFieldTypeId,
                                   const Char8  *szFieldName); 

    virtual void getFieldAndDesc  (      OSG::FieldContainerPtr   pFC,
                                   const Char8                  * szFieldname,
                                         OSG::Field             *&pField,
                                   const OSG::FieldDescription  *&pDesc);

    /*------------------------- your_category -------------------------------*/

    virtual FieldContainerPtr beginNode(const Char8       *szTypename,
                                        const Char8       *szName,
                                        FieldContainerPtr  pCurrentFC);

    virtual Bool              use      (FieldContainerPtr pFC);

    /*------------------------- your_operators ------------------------------*/

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup 
 *  \brief Brief
 *
 *  detailed
 */

class OSG_SYSTEMLIB_DLLMAPPING VRMLMaterialDesc : public VRMLNodeDesc
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

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef VRMLNodeDesc Inherited;

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

    VRMLMaterialDesc(const VRMLMaterialDesc &source);
    void operator =(const VRMLMaterialDesc &source);

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

    SFReal32          _defaultAmbientIntensity;
    SFColor3f         _defaultDiffuseColor;
    SFColor3f         _defaultEmissiveColor;
    SFReal32          _defaultShininess;
    SFColor3f         _defaultSpecularColor;
    SFReal32          _defaultTransparency;

    SFReal32          _ambientIntensity;
    SFColor3f         _diffuseColor;
    SFColor3f         _emissiveColor;
    SFReal32          _shininess;
    SFColor3f         _specularColor;
    SFReal32          _transparency;

    SimpleMaterialPtr _pDefMat;
    SimpleMaterialPtr _pMat;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VRMLMaterialDesc();

    virtual ~VRMLMaterialDesc(void); 

    /*------------------------- your_category -------------------------------*/

    virtual void        init (const Char8 *szName);

    virtual void        reset(void);

    virtual MaterialPtr getDefaultMaterial(void);

    /*------------------------- your_category -------------------------------*/

    virtual Bool prototypeAddField(const Char8  *szFieldType,
                                   const UInt32  uiFieldTypeId,
                                   const Char8  *szFieldName); 

    virtual void endProtoInterface(void);

    virtual void getFieldAndDesc  (      OSG::FieldContainerPtr   pFC,
                                   const Char8                  * szFieldname,
                                         OSG::Field             *&pField,
                                   const OSG::FieldDescription  *&pDesc);

    /*------------------------- your_category -------------------------------*/

    virtual FieldContainerPtr beginNode(const Char8       *szTypename,
                                        const Char8       *szName,
                                        FieldContainerPtr  pCurrentFC);

    virtual void              endNode      (FieldContainerPtr);

    /*------------------------- your_operators ------------------------------*/

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_END_NAMESPACE

#endif /* _OSGVRMLNODEDESCS_H_ */


