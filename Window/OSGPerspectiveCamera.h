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

#ifndef _OSG_PERSPECTIVE_CAMERA_H_
#define _OSG_PERSPECTIVE_CAMERA_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGFrustumVolume.h>
#include <OSGMatrix.h>

class Camera;

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class DrawAction;

class PerspectiveCamera;
typedef FCPtr <CameraPtr,
               PerspectiveCamera   > PerspectiveCameraPtr;
typedef MField<PerspectiveCameraPtr> MFPerspectiveCameraPtr;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup baselib
 *  \brief Brief
 *
 *  detailed
 */

class OSG_DLLEXPORT PerspectiveCamera : public Camera
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(DegreeField)

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

    /** */
    static const char *getClassname(void) { return "PerspectiveCamera"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(PerspectiveCameraPtr)

    /*------------------------- your_category -------------------------------*/

    /** draw the camera's geometry (if any). Usually there is none. */
    virtual void draw( DrawAction * action, Viewport * port );

    /** get the separate elements needed for rendering */

    virtual void getProjection( Matrix& result, Viewport * port );

    
    void      setDegrees  (Real32 degrees);
    Real32    getDegrees  (void) const;
    SFReal32 *getSFDegrees(void);
        
    /*------------------------- your_operators ------------------------------*/

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

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

    /** The vertical field of view, in degrees. */
    SFReal32 _degrees;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    PerspectiveCamera(void);
    virtual ~PerspectiveCamera(void); 
 
  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef Camera Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class FieldContainer;
    friend class FieldContainerType;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    static char cvsid[];

    static FieldContainerType _type;
 
    static FieldDescription   _desc[];

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

    PerspectiveCamera(const PerspectiveCamera &source);
    PerspectiveCamera& operator =(const PerspectiveCamera &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer


/** \brief class pointer
 */
typedef PerspectiveCamera *PerspectiveCameraP;

/** \brief PerspectiveCameraPtr
 */
typedef FCPtr<CameraPtr, PerspectiveCamera> PerspectiveCameraPtr;

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief PerspectiveCameraPtr field traits 
 */

template <>
struct FieldDataTraits<PerspectiveCameraPtr> : public Traits
{
    enum                        { StringConvertable = 0x00  };

    static char *getSName(void) { return "SFPerspectiveCameraPtr"; }
    static char *getMName(void) { return "MFPerspectiveCameraPtr"; }
};

/** \brief SFPerspectiveCameraPtr
 */
typedef SField<PerspectiveCameraPtr>       SFPerspectiveCameraPtr;

/** \brief MFPerspectiveCameraPtr
 */
typedef MField<PerspectiveCameraPtr>       MFPerspectiveCameraPtr;

OSG_END_NAMESPACE

#include "OSGPerspectiveCamera.inl"

#endif /* _OSG_PERSPECTIVE_CAMERA_H_ */
