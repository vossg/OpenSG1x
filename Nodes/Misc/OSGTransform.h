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


#ifndef _OSGTRANSFORM_H_
#define _OSGTRANSFORM_H_
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
#include <OSGFieldContainerPtr.h>
#include <OSGFieldDescription.h>
#include <OSGAction.h>
#include <OSGMiscBase.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class Transform;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

/** \brief TransformPtr
 */

typedef FCPtr<NodeCorePtr, Transform> TransformPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \defgroup Transform  Transform nodes
 *  Transformation nodes.
 */
/*! \ingroup FieldContainerLib Transform
 *  \brief A simple matrix transformation.
 *
 *  Transform provides one matrix to transform objects.
 */

class OSG_MISC_DLLMAPPING Transform : public NodeCore
{
  private:

    typedef NodeCore Inherited;

  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------
    
    OSG_FC_FIRST_FIELD_IDM_DECL(MatrixField)

    OSG_FC_LAST_FIELD_IDM_DECL (MatrixField)

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "Transform"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(TransformPtr)

    /*--------------------------- access fields ----------------------------*/

    //! Return the matrix field.
          SFMatrix *getSFMatrix(void);

    /*----------------------------- access ----------------------------------*/

    //!@{ Return the matrix value.

          Matrix   &getMatrix  (void);
    const Matrix   &getMatrix  (void) const;

    //!@}

    /*-------------------------- transformation ----------------------------*/

    virtual void accumulateMatrix( Matrix & result );

    /*------------------------------ volume -------------------------------*/

    void adjustVolume( Volume & volume );

    /*------------------------------ dump -----------------------------------*/

    virtual void dump(void) const;

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
    SFMatrix _matrix;
    
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    Transform(void);
    Transform(const Transform &source);
    virtual ~Transform(void); 
    
    /** Actions */
    
    //! DrawAction:  execute the OpenGL commands directly   
    Action::ResultE drawEnter(Action * action );
    Action::ResultE drawLeave(Action * action );
    
    //! IntersectAction:  test a ray against the scene   
    Action::ResultE intersectEnter(Action * action );
    Action::ResultE intersectLeave(Action * action );

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

    void operator =(const Transform &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------


/** \brief class pointer
 */
typedef Transform *TransformP;

/** \ingroup FieldLib Transform
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief TransformPtr field traits 
 */

template <>
struct FieldDataTraits<TransformPtr> : public Traits
{
    enum                        { StringConvertable = 0x00      };

    static char *getSName(void) { return "SFTransformPtr"; }
    static char *getMName(void) { return "MFTransformPtr"; }
};

/** \brief SFTransformPtr
 */
typedef SField<TransformPtr> SFTransformPtr;

#ifndef OSG_COMPILETRANSFORMINST
#if defined(__sgi)

#pragma do_not_instantiate SField<TransformPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, TransformPtr, OSG_MISC_DLLTMPLMAPPING)

#endif
#endif


/** \brief MFTransformPtr
 */
typedef MField<TransformPtr> MFTransformPtr;

#ifndef OSG_COMPILETRANSFORMINST
#if defined(__sgi)

#pragma do_not_instantiate MField<TransformPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, TransformPtr, OSG_MISC_DLLTMPLMAPPING)

#endif
#endif

OSG_END_NAMESPACE

#include <OSGTransform.inl>

#endif /* _OSGTRANSFORM_H_ */
