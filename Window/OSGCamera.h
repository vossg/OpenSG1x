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


OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class OSGCamera;

typedef OSGFCPtr <OSGFieldContainerPtr, OSGCamera> OSGCameraPtr;
typedef OSGMField<OSGCameraPtr                   > OSGMFCameraPtr;

class OSGViewport;
class OSGDrawAction;

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

class OSGCamera : public OSGFieldContainer
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(OSGBeaconField)

    OSG_FC_FIELD_IDM_DECL      (OSGNearField  )
    OSG_FC_FIELD_IDM_DECL      (OSGFarField   )

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
    static const char *getClassname(void) { return "OSGCamera"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(OSGCameraPtr)

    /*------------------------- your_category -------------------------------*/

    /** setup the GL for rendering and tell the Action what it needs to know */
    virtual void setup(OSGDrawAction *action, OSGViewport *port);

    /** draw the camera's geometry (if any). Usually there is none. */
    virtual void draw (OSGDrawAction *action, OSGViewport *port);

    /** get the separate elements needed for rendering */

    virtual void getProjection           (OSGMatrix        &result, 
                                          OSGViewport      *port);

    virtual void getProjectionTranslation(OSGMatrix        &result, 
                                          OSGViewport      *port);

    virtual void getViewing              (OSGMatrix        &result, 
                                          OSGViewport      *port);

    virtual void getFrustum              (OSGFrustumVolume &result,
                                          OSGViewport      *port);
    
   
    void          setBeacon  (OSGNodePtr beacon);
    OSGNodePtr    getBeacon  (void) const;
    OSGSFNodePtr *getSFBeacon(void);
    
    
    void         setNear  (OSGReal32 rNear);
    OSGReal32    getNear  (void) const;
    OSGSFReal32 *getSFNear(void);
    
    
    void         setFar  (OSGReal32 rFar);
    OSGReal32    getFar  (void) const;
    OSGSFReal32 *getSFFar(void);
    
    /*------------------------- your_operators ------------------------------*/

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

    OSGBool operator < (const OSGCamera &other) const;
    
    //OSGBool operator == (const OSGCamera &other) const;
    //OSGBool operator != (const OSGCamera &other) const;

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
    OSGSFNodePtr _beacon;
    
    /** The near distance. */
    OSGSFReal32  _near;
    
    /** The far distance. */
    OSGSFReal32  _far;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGCamera(void);
    virtual ~OSGCamera(void); 

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGFieldContainer Inherited;

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

    OSGCamera(const OSGCamera &source);
    OSGCamera& operator =(const OSGCamera &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

/** \brief class pointer
 */
typedef OSGCamera *OSGCameraP;

/** \brief OSGCameraPtr
 */
typedef OSGFCPtr<OSGFieldContainerPtr, OSGCamera> OSGCameraPtr;

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGCameraPtr field traits 
 */

template <>
struct OSGFieldDataTraits<OSGCameraPtr> : public OSGTraits
{
    static char    *getSName(void) { return "SFCameraPtr"; }
    static char    *getMName(void) { return "MFCameraPtr"; }

    static OSGBool  getFromString(OSGCameraPtr &,
                                  const char  *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void     putToString(const OSGCameraPtr &,
                                      OSGString    &)
    {
        // TO_BE_DONE
    }
};

/** \brief OSGSFCameraPtr
 */
typedef OSGSField<OSGCameraPtr>       OSGSFCameraPtr;

/** \brief OSGMFCameraPtr
 */
typedef OSGMField<OSGCameraPtr>       OSGMFCameraPtr;

OSG_END_NAMESPACE

#include "OSGCamera.inl"

#endif /* _OSG_CAMERA_H_ */


