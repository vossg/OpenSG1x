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

#ifndef _OSG_CAMERA_H_
#define _OSG_CAMERA_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGMatrix.h>
#include <OSGVolume.h>
#include <OSGFrustumVolume.h>
#include <OSGMField.h>
#include <OSGFieldDescription.h>
#include <OSGSFSysTypes.h>
#include <OSGSFFieldContainerTypes.h>
#include <OSGFieldContainer.h>
#include <OSGWindowBase.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class Camera;

typedef FCPtr <FieldContainerPtr, Camera> CameraPtr;
typedef MField<CameraPtr                > MFCameraPtr;

class Viewport;
class DrawAction;

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

class OSG_WINDOW_DLLMAPPING Camera : public FieldContainer
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(BeaconField)

    OSG_FC_FIELD_IDM_DECL      (NearField  )
    OSG_FC_FIELD_IDM_DECL      (FarField   )

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
    static const char *getClassname(void) { return "Camera"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(CameraPtr)

    /*------------------------- your_category -------------------------------*/

    /** setup the GL for rendering and tell the Action what it needs to know */
    virtual void setup(DrawAction *action, Viewport *port);

    /** draw the camera's geometry (if any). Usually there is none. */
    virtual void draw (DrawAction *action, Viewport *port);

    /** get the separate elements needed for rendering */

    virtual void getProjection           (Matrix        &result, 
                                          Viewport      *port);

    virtual void getProjectionTranslation(Matrix        &result, 
                                          Viewport      *port);

    virtual void getViewing              (Matrix        &result, 
                                          Viewport      *port);

    virtual void getFrustum              (FrustumVolume &result,
                                          Viewport      *port);
    
   
    void       setBeacon  (NodePtr beacon);
    NodePtr    getBeacon  (void) const;
    SFNodePtr *getSFBeacon(void);
    
    
    void      setNear  (Real32 rNear);
    Real32    getNear  (void) const;
    SFReal32 *getSFNear(void);
    
    
    void      setFar  (Real32 rFar);
    Real32    getFar  (void) const;
    SFReal32 *getSFFar(void);
    
    /*------------------------- your_operators ------------------------------*/

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

    Bool operator < (const Camera &other) const;
    
    //Bool operator == (const Camera &other) const;
    //Bool operator != (const Camera &other) const;

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
    
    /** The beacon to define the position/orientation. */
    SFNodePtr _beacon;
    
    /** The near distance. */
    SFReal32  _near;
    
    /** The far distance. */
    SFReal32  _far;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    Camera(void);
    virtual ~Camera(void); 

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef FieldContainer Inherited;

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

    Camera(const Camera &source);
    Camera& operator =(const Camera &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

/** \brief class pointer
 */
typedef Camera *CameraP;

/** \brief CameraPtr
 */
typedef FCPtr<FieldContainerPtr, Camera> CameraPtr;

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief CameraPtr field traits 
 */

template <>
struct FieldDataTraits<CameraPtr> : public Traits
{
    enum                         { StringConvertable = 0x00  };

    static Char8 *getSName(void) { return "SFCameraPtr"; }
    static Char8 *getMName(void) { return "MFCameraPtr"; }
};

/** \brief SFCameraPtr
 */
typedef SField<CameraPtr>       SFCameraPtr;

/** \brief MFCameraPtr
 */
typedef MField<CameraPtr>       MFCameraPtr;

OSG_END_NAMESPACE

#include "OSGCamera.inl"

#endif /* _OSG_CAMERA_H_ */


