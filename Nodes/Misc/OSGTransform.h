/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *         contact: dirk@opensg.org, vossg@igd.fhg.de, jbehr@zgdv.de         *
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

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class OSGTransform;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

/** \brief OSGTransformPtr
 */

typedef OSGFCPtr<OSGNodeCorePtr, OSGTransform> OSGTransformPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \defgroup Transform  Transform nodes
 *  Transformation nodes.
 */
/*! \ingroup FieldContainerLib Transform
 *  \brief A simple matrix transformation.
 *
 *  OSGTransform provides one matrix to transform objects.
 */

class OSGTransform : public OSGNodeCore
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------
    
    OSG_FC_FIRST_FIELD_IDM_DECL(OSGMatrixField)

    OSG_FC_LAST_FIELD_IDM_DECL

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "OSGTransform"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~OSGTransform(void); 

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(OSGTransformPtr)

    /*--------------------------- access fields ----------------------------*/

    //! Return the matrix field.
          OSGSFMatrix *getSFMatrix(void);

    /*----------------------------- access ----------------------------------*/

    //!@{ Return the matrix value.

          OSGMatrix   &getMatrix  (void);
    const OSGMatrix   &getMatrix  (void) const;

    //!@}

    /*-------------------------- transformation ----------------------------*/

    virtual void accumulateMatrix( OSGMatrix & result );

    /*------------------------------ volume -------------------------------*/

    void adjustVolume( OSGVolume & volume );

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
    OSGSFMatrix _matrix;
    
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGTransform(void);
    OSGTransform(const OSGTransform &source);
    
    /** Actions */
    
    //! DrawAction:  execute the OpenGL commands directly   
    OSGAction::ResultE drawEnter(OSGAction * action );
    OSGAction::ResultE drawLeave(OSGAction * action );

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGNodeCore Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class OSGFieldContainer;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    static char cvsid[];

    static OSGFieldDescription   _desc[];

    static OSGFieldContainerType _type;

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

    void operator =(const OSGTransform &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------


/** \brief class pointer
 */
typedef OSGTransform *OSGTransformP;

/** \ingroup FieldLib Transform
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGTransformPtr field traits 
 */

template <>
struct OSGFieldDataTraits<OSGTransformPtr> : public OSGTraits
{
    static char *getSName(void) { return "SFTransformPtr"; }
    static char *getMName(void) { return "MFTransformPtr"; }
};

/** \brief OSGSFTransformPtr
 */
typedef OSGSField<OSGTransformPtr> OSGSFTransformPtr;

/** \brief OSGMFTransformPtr
 */
typedef OSGMField<OSGTransformPtr> OSGMFTransformPtr;

OSG_END_NAMESPACE

#include <OSGTransform.inl>

#endif /* _OSGTRANSFORM_H_ */
