/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

class OSGCamera;

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class OSGDrawAction;

class OSGPerspectiveCamera;
typedef OSGFCPtr <OSGCameraPtr,
                  OSGPerspectiveCamera   > OSGPerspectiveCameraPtr;
typedef OSGMField<OSGPerspectiveCameraPtr> OSGMFPerspectiveCameraPtr;

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

class OSGPerspectiveCamera : public OSGCamera
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(OSGDegreeField)

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
    static const char *getClassname(void) { return "OSGPerspectiveCamera"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(OSGPerspectiveCameraPtr)

    /*------------------------- your_category -------------------------------*/

    /** draw the camera's geometry (if any). Usually there is none. */
    virtual void draw( OSGDrawAction * action, OSGViewport * port );

    /** get the separate elements needed for rendering */

    virtual void getProjection( OSGMatrix& result, OSGViewport * port );

    
    void         setDegrees  (OSGReal32 degrees);
    OSGReal32    getDegrees  (void) const;
    OSGSFReal32 *getSFDegrees(void);
        
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
    OSGSFReal32 _degrees;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGPerspectiveCamera(void);
    virtual ~OSGPerspectiveCamera(void); 
 
  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGCamera Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class OSGFieldContainer;
    friend class OSGFieldContainerType;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    static char cvsid[];

    static OSGFieldContainerType _type;
 
    static OSGFieldDescription   _desc[];

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

    OSGPerspectiveCamera(const OSGPerspectiveCamera &source);
    OSGPerspectiveCamera& operator =(const OSGPerspectiveCamera &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer


/** \brief class pointer
 */
typedef OSGPerspectiveCamera *OSGPerspectiveCameraP;

/** \brief OSGPerspectiveCameraPtr
 */
typedef OSGFCPtr<OSGCameraPtr, OSGPerspectiveCamera> OSGPerspectiveCameraPtr;

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGPerspectiveCameraPtr field traits 
 */

template <>
struct OSGFieldDataTraits<OSGPerspectiveCameraPtr> : public OSGTraits
{
    static char *getSName(void) { return "SFPerspectiveCameraPtr"; }
    static char *getMName(void) { return "MFPerspectiveCameraPtr"; }
};

/** \brief OSGSFPerspectiveCameraPtr
 */
typedef OSGSField<OSGPerspectiveCameraPtr>       OSGSFPerspectiveCameraPtr;

/** \brief OSGMFPerspectiveCameraPtr
 */
typedef OSGMField<OSGPerspectiveCameraPtr>       OSGMFPerspectiveCameraPtr;

OSG_END_NAMESPACE

#include "OSGPerspectiveCamera.inl"

#endif /* _OSG_PERSPECTIVE_CAMERA_H_ */
