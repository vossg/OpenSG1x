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

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>
#include <vector>
#include <string>

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
#include <OSGSFImageTypes.h>
#include <OSGSFVecTypes.h>
#include <OSGSFFieldContainerPtr.h>
#include <OSGComponentTransform.h>
#include <OSGPathHandler.h>

OSG_BEGIN_NAMESPACE

class VRMLAppearanceDesc;
class VRMLMaterialDesc;
class VRMLImageTextureDesc;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

struct GenericAttDesc
{
    typedef Attachment    Parent;
    typedef AttachmentPtr ParentPtr;

    static const Char8 *getTypeName      (void) { return "GenericAtt"; }
    static const Char8 *getParentTypeName(void) { return "Attachment"; }
    static const Char8 *getGroupName     (void) { return "VRMLGenAtt"; }
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
struct FieldDataTraits<GenericAttPtr> : 
    public FieldTraitsRecurseBase<GenericAttPtr>
{
    static DataType                 _type;
    enum                            { StringConvertable = 0x00  };
    enum                            { bHasParent        = 0x01  };

    static DataType &getType (void) { return _type;             }
    static Char8    *getSName(void) { return "SFGenericAttPtr"; }
    static Char8    *getMName(void) { return "MFGenericAttPtr"; }
};


typedef SField<GenericAttPtr>       SFGenericPtr;

#ifndef OSG_COMPILEVRMLNODEDESCINST
#if defined(__sgi)

#pragma do_not_instantiate SField<GenericAttPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, GenericAttPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif


/** \brief MFGenericAttrPtr
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

/*! \ingroup GeometryLoaderLib
 *  \brief General VRML Node Desc
 */

class OSG_SYSTEMLIB_DLLMAPPING VRMLNodeDesc 
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    static UInt32 getIndent  (void);
    static void   incIndent  (void);
    static void   decIndent  (void);
    static void   resetIndent(void);

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLNodeDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLNodeDesc (void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual       void              init                 (const Char8 *szName);

    virtual       void              reset                (void);

    virtual       void              setOnEndSave         (const Char8 *szName);
    virtual       void              clearOnEndSave       (void);
    virtual       Bool              getOnEndSave         (void);
    virtual const Char8            *getSavename          (void);
    virtual       FieldContainerPtr getSaveFieldContainer(void);


                  void              setOptions    (      UInt32 uiOpt );
                  void              setPathHandler(PathHandler *pPathHandler);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual Field *getField       (const Char8             * szFieldname);
    
    virtual void   getFieldAndDesc(      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                         Field             *&pField,
                                   const FieldDescription  *&pDesc);
    

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Prototypes                                 */
    /*! \{                                                                 */

    virtual Bool prototypeAddField     (const Char8  *szFieldType,
                                        const UInt32  uiFieldTypeId,
                                        const Char8  *szFieldName); 
    
    virtual void prototypeAddFieldValue(const Char8 *szFieldVal);
    
    virtual void endProtoInterface     (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);
    
    virtual void              endNode  (      FieldContainerPtr            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      FieldValue                              */
    /*! \{                                                                 */

    virtual void addFieldValue(      Field             *pField,
                               const Char8             *szFieldVal);

    virtual Bool use          (      FieldContainerPtr            );
   
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

#ifdef OSG_SGI_STL
    typedef hash_map<     const Char8 *,  UInt32, 
                     hash<const Char8 *>, EQString> FieldNameTypeHash;
#else
    typedef map     <     const Char8 *,  UInt32, 
                                          LTString> FieldNameTypeHash;
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static UInt32             _uiIndent;

           FieldNameTypeHash  _mFieldTypes;

           GenericAttPtr      _pGenAtt;

           FieldContainerPtr  _pNodeProto;
           FieldContainerPtr  _pNodeCoreProto;

           Field             *_pCurrField;

           string             _szCurrentName;
           Bool               _bSaveOnEnd;

           UInt32             _uiOptions;
           PathHandler       *_pPathHandler;


    Field *getField(      FieldContainerPtr  pFC1, 
                          FieldContainerPtr  pFC2,
                          GenericAttPtr      pGenAtt,
                    const Char8             *szFieldname);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLNodeDesc(const VRMLNodeDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLNodeDesc &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GeometryLoaderLib
 *  \brief VRML Shape Desc
 */

class OSG_SYSTEMLIB_DLLMAPPING VRMLShapeDesc : public VRMLNodeDesc 
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLShapeDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLShapeDesc(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init           (const Char8            *szName);

            void setMaterialDesc(      VRMLMaterialDesc *pMaterialDesc);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    virtual Bool prototypeAddField(const Char8  *szFieldType,
                                   const UInt32  uiFieldTypeId,
                                   const Char8  *szFieldName); 

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                         Field             *&pField,
                                   const FieldDescription  *&pDesc);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */
    
    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (FieldContainerPtr        pFC);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    VRMLMaterialDesc *_pMaterialDesc;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLShapeDesc(const VRMLShapeDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLShapeDesc &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GeometryLoaderLib
 *  \brief VRML Gemometry Desc
 */

class OSG_SYSTEMLIB_DLLMAPPING VRMLGeometryDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLGeometryDesc(Bool bIsFaceSet);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLGeometryDesc(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    virtual Bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName); 

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                         Field             *&pField,
                                   const FieldDescription  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr  pFC);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Field Value                                 */
    /*! \{                                                                 */

    virtual void addFieldValue(      Field *pField,
                               const Char8 *szFieldVal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    Bool          _bIsFaceSet;

    Bool          _bInIndex;
    UInt32        _uiNumVertices;

    GeoPTypesPtr   _pTypeField;
    GeoPLengthsPtr _pLengthField;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLGeometryDesc(const VRMLGeometryDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLGeometryDesc &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GeometryLoaderLib
 *  \brief VRML Gemetry Part Desc 
 */

class OSG_SYSTEMLIB_DLLMAPPING VRMLGeometryPartDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLGeometryPartDesc(Char8 *szVRMLPartname,
                         Char8 *szOSGPartname,
                         Char8 *szOSGProtoname);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLGeometryPartDesc(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual Bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                         Field             *&pField,
                                   const FieldDescription  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Node                                     */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    Char8 *_szVRMLPartname;
    Char8 *_szOSGPartname;
    Char8 *_szOSGProtoname;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLGeometryPartDesc(const VRMLGeometryPartDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLGeometryPartDesc &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GeometryLoaderLib
 *  \brief VRML Geometry Object Desc 
 */

class OSG_SYSTEMLIB_DLLMAPPING VRMLGeometryObjectDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
 
    VRMLGeometryObjectDesc(Char8 *szVRMLObjectname);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLGeometryObjectDesc(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual Bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName); 

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                         Field             *&pField,
                                   const FieldDescription  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    Char8 *_szVRMLObjectname;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLGeometryObjectDesc(const VRMLGeometryObjectDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLGeometryObjectDesc &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GeometryLoaderLib
 *  \brief VRML Appearance Desc 
 */

class OSG_SYSTEMLIB_DLLMAPPING VRMLAppearanceDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLAppearanceDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLAppearanceDesc(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init           (const Char8            *szName);

    virtual void setMaterialDesc(      VRMLMaterialDesc *pMaterialDesc);


    virtual FieldContainerPtr getSaveFieldContainer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Field                                   */
    /*! \{                                                                 */

    virtual Bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName); 

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                         Field             *&pField,
                                   const FieldDescription  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Field                                   */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Field Value                                */
    /*! \{                                                                 */

    virtual Bool use(FieldContainerPtr pFC);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    VRMLMaterialDesc    *_pMaterialDesc;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLAppearanceDesc(const VRMLAppearanceDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLAppearanceDesc &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GeometryLoaderLib
 *  \brief VRML Material Desc 
 */

class OSG_SYSTEMLIB_DLLMAPPING VRMLMaterialDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLMaterialDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLMaterialDesc(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void        init              (const Char8 *szName);

    virtual void        reset             (      void);

    virtual MaterialPtr getDefaultMaterial(      void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual Bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName); 

    virtual void endProtoInterface(      void);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                         Field             *&pField,
                                   const FieldDescription  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

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

    ChunkMaterialPtr _pDefMat;
    MaterialChunkPtr _pMat;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLMaterialDesc(const VRMLMaterialDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLMaterialDesc &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GeometryLoaderLib
 *  \brief VRML ImageTexture Desc 
 */

class OSG_SYSTEMLIB_DLLMAPPING VRMLImageTextureDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLImageTextureDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLImageTextureDesc(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init (const Char8 *szName);

    virtual void reset(      void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual Bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName); 

    virtual void endProtoInterface(void);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                         Field             *&pField,
                                   const FieldDescription  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    SFString _defaultURL;
    SFBool   _defaultRepeatS;
    SFBool   _defaultRepeatT;

    MFString _url;
    SFBool   _repeatS;
    SFBool   _repeatT;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLImageTextureDesc(const VRMLImageTextureDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLImageTextureDesc &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GeometryLoaderLib
 *  \brief VRML PixelTexture Desc 
 */

class OSG_SYSTEMLIB_DLLMAPPING VRMLPixelTextureDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLPixelTextureDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLPixelTextureDesc(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init (const Char8 *szName);

    virtual void reset(      void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field                                     */
    /*! \{                                                                 */

    virtual Bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName); 

    virtual void endProtoInterface(      void);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                         Field             *&pField,
                                   const FieldDescription  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Node                                      */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Field Value                                 */
    /*! \{                                                                 */

    virtual void addFieldValue(      Field *pField,
                               const Char8 *szFieldVal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    SFImageP _defaultImage;
    SFBool   _defaultRepeatS;
    SFBool   _defaultRepeatT;

    SFImageP _image;
    SFBool   _repeatS;
    SFBool   _repeatT;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLPixelTextureDesc(const VRMLPixelTextureDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLPixelTextureDesc &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GeometryLoaderLib
 *  \brief VRML LOD Desc 
 */

class OSG_SYSTEMLIB_DLLMAPPING VRMLLODDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLLODDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLLODDesc(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Field                                   */
    /*! \{                                                                 */

    virtual Bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName); 

    virtual void endProtoInterface(void);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                         Field             *&pField,
                                   const FieldDescription  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLLODDesc(const VRMLLODDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLLODDesc &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GeometryLoaderLib
 *  \brief VRML Switch Desc 
 */

class OSG_SYSTEMLIB_DLLMAPPING VRMLSwitchDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLSwitchDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLSwitchDesc(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Field                                   */
    /*! \{                                                                 */

    virtual Bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName); 

    virtual void endProtoInterface(      void);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                         Field             *&pField,
                                   const FieldDescription  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLSwitchDesc(const VRMLSwitchDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLSwitchDesc &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GeometryLoaderLib
 *  \brief VRML Group Desc 
 */

class OSG_SYSTEMLIB_DLLMAPPING VRMLGroupDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLGroupDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLGroupDesc(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Field                                    */
    /*! \{                                                                 */

    virtual Bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName); 

    virtual void endProtoInterface(      void);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                         Field             *&pField,
                                   const FieldDescription  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Node                                     */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    SFVec3f _defaultBoxCenter;
    SFVec3f _defaultBoxSize;

    SFVec3f _boxCenter;
    SFVec3f _boxSize;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLGroupDesc(const VRMLGroupDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLGroupDesc &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GeometryLoaderLib
 *  \brief VRML Inline Desc 
 */

class OSG_SYSTEMLIB_DLLMAPPING VRMLInlineDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLInlineDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLInlineDesc(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void init(const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Field                                   */
    /*! \{                                                                 */

    virtual Bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName); 

    virtual void endProtoInterface(      void);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                         Field             *&pField,
                                   const FieldDescription  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8       *szTypename,
                                        const Char8       *szName,
                                        FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (FieldContainerPtr);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    SFVec3f _defaultBoxCenter;
    SFVec3f _defaultBoxSize;
    
    SFVec3f _boxCenter;
    SFVec3f _boxSize;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLInlineDesc(const VRMLInlineDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLInlineDesc &source);
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GeometryLoaderLib
 *  \brief VRML Viewpoint Desc 
 */

class OSG_SYSTEMLIB_DLLMAPPING VRMLViewpointDesc : public VRMLNodeDesc
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VRMLViewpointDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~VRMLViewpointDesc(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    virtual void                  init            (const Char8 *szName);

    virtual void                  reset           (      void         );

    virtual ComponentTransformPtr getDefaultBeacon(      void         );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Field                                   */
    /*! \{                                                                 */

    virtual Bool prototypeAddField(const Char8             * szFieldType,
                                   const UInt32              uiFieldTypeId,
                                   const Char8             * szFieldName); 

    virtual void endProtoInterface(      void);

    virtual void getFieldAndDesc  (      FieldContainerPtr   pFC,
                                   const Char8             * szFieldname,
                                         Field             *&pField,
                                   const FieldDescription  *&pDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Node                                    */
    /*! \{                                                                 */

    virtual FieldContainerPtr beginNode(const Char8             *szTypename,
                                        const Char8             *szName,
                                              FieldContainerPtr  pCurrentFC);

    virtual void              endNode  (      FieldContainerPtr            );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(const Char8 *szNodeName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*==========================  PRIVATE  ================================*/
  private:

    typedef VRMLNodeDesc Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    VRMLViewpointDesc(const VRMLViewpointDesc &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VRMLViewpointDesc &source);
};

OSG_END_NAMESPACE

#define OSGVRMLNODEDESCS_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGVRMLNODEDESCS_H_ */


