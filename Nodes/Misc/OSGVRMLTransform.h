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


#ifndef _OSGVRMLTRANSFORM_H_
#define _OSGVRMLTRANSFORM_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGConfig.h>

#include <GL/gl.h>
#include <OSGBaseTypes.h>
#include <OSGNodeCore.h>
#include <OSGSFMathTypes.h>
#include <OSGFieldContainer.h>
#include <OSGFieldContainerPtr.h>
#include <OSGFieldDescription.h>
#include <OSGAction.h>
#include <OSGMiscBase.h>
#include <OSGTransform.h>
#include <OSGSFVecTypes.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class VRMLTransform;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

/** \brief VRMLTransformPtr
 */

typedef FCPtr<TransformPtr, VRMLTransform> VRMLTransformPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! VRMLTransform provides a vrml style transformation.
 *	\ingroup NodesLib
 */

class OSG_MISC_DLLMAPPING VRMLTransform : public Transform
{
  private:

    typedef Transform Inherited;

  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------
    
    OSG_FC_FIRST_FIELD_IDM_DECL(CenterField)

    OSG_FC_FIELD_IDM_DECL      (RotationField,         CenterField)
    OSG_FC_FIELD_IDM_DECL      (ScaleField,            RotationField)
    OSG_FC_FIELD_IDM_DECL      (ScaleOrientationField, ScaleField)
    OSG_FC_FIELD_IDM_DECL      (TranslationField,      ScaleOrientationField)

    OSG_FC_LAST_FIELD_IDM_DECL (TranslationField)

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "VRMLTransform"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(VRMLTransformPtr)

    /*--------------------------- access fields ----------------------------*/

    //! Return the matrix field.

    SFVec3f      *getSFCenter          (void);
    SFQuaternion *getSFRotation        (void);
    SFVec3f      *getSFScale           (void);
    SFQuaternion *getSFScaleOrientation(void);
    SFVec3f      *getSFTranslation     (void);

    /*----------------------------- access ----------------------------------*/

    //!@{ Return the matrix value.

          Vec3f      &getCenter          (void);
    const Vec3f      &getCenter          (void) const;

          Quaternion &getRotation        (void);
    const Quaternion &getRotation        (void) const;

          Vec3f      &getScale           (void);
    const Vec3f      &getScale           (void) const;

          Quaternion &getScaleOrientation(void);
    const Quaternion &getScaleOrientation(void) const;

          Vec3f      &getTranslation     (void);
    const Vec3f      &getTranslation     (void) const;

    //!@}

    /*-------------------------- transformation ----------------------------*/

    virtual void changed(BitVector  whichField, 
                         ChangeMode from);
 
    /*------------------------------ volume -------------------------------*/

    /*------------------------------ dump -----------------------------------*/

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector &bvFlags  = 0) const;

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

    //! The field storing the transform matrix.

    SFVec3f      _center;
    SFQuaternion _rotation;
    SFVec3f      _scale;
    SFQuaternion _scaleOrientation;
    SFVec3f      _translation;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VRMLTransform(void);
    VRMLTransform(const VRMLTransform &source);
    virtual ~VRMLTransform(void); 
    
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

    friend class FieldContainer;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    static char cvsid[];

    static FieldDescription   _desc[];

    static FieldContainerType _type;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static void initMethod( void );
    
    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const VRMLTransform &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------


/** \brief class pointer
 */
typedef VRMLTransform *VRMLTransformP;

/** \ingroup FieldLib VRMLTransform
 *  \ingroup VRMLSingleFields
 *  \ingroup VRMLMultiFields
 *  \brief VRMLTransformPtr field traits 
 */

template <>
struct FieldDataTraits<VRMLTransformPtr> : public Traits
{
    enum                        { StringConvertable = 0x00      };

    static char *getSName(void) { return "SFVRMLTransformPtr"; }
    static char *getMName(void) { return "MFVRMLTransformPtr"; }
};

/** \brief SFVRMLTransformPtr
 */
typedef SField<VRMLTransformPtr> SFVRMLTransformPtr;

#ifndef OSG_COMPILEVRMLTRANSFORMINST
#if defined(__sgi)

#pragma do_not_instantiate SField<VRMLTransformPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, VRMLTransformPtr, OSG_MISC_DLLTMPLMAPPING)

#endif
#endif


/** \brief MFVRMLTransformPtr
 */
typedef MField<VRMLTransformPtr> MFVRMLTransformPtr;

#ifndef OSG_COMPILEVRMLTRANSFORMINST
#if defined(__sgi)

#pragma do_not_instantiate MField<VRMLTransformPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, VRMLTransformPtr, OSG_MISC_DLLTMPLMAPPING)

#endif
#endif

OSG_END_NAMESPACE

#include <OSGVRMLTransform.inl>

#endif /* _OSGVRMLTRANSFORM_H_ */
