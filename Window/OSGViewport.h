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


#ifndef _OSG_VIEWPORT_H_
#define _OSG_VIEWPORT_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGSField.h>
#include <OSGMField.h>
#include <OSGFieldContainer.h>
#include <OSGFieldContainerPtr.h>
#include <OSGSFSysTypes.h>
#include <OSGSFFieldContainerTypes.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class OSGCamera;
typedef OSGFCPtr <OSGFieldContainerPtr, OSGCamera> OSGCameraPtr;
typedef OSGSField<OSGCameraPtr                   > OSGSFCameraPtr;

class OSGWindow;
typedef OSGFCPtr <OSGFieldContainerPtr, OSGWindow> OSGWindowPtr;
typedef OSGSField<OSGWindowPtr                   > OSGSFWindowPtr;

class OSGBackground;
typedef OSGFCPtr <OSGFieldContainerPtr, OSGBackground> OSGBackgroundPtr;
typedef OSGSField<OSGBackgroundPtr                   > OSGSFBackgroundPtr;

class OSGViewport;
typedef OSGFCPtr <OSGFieldContainerPtr, OSGViewport> OSGViewportPtr;
typedef OSGSField<OSGViewportPtr                   > OSGSFViewportPtr;

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

class OSGViewport : public OSGFieldContainer
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(OSGLeftField      )

    OSG_FC_FIELD_IDM_DECL      (OSGRightField     )
    OSG_FC_FIELD_IDM_DECL      (OSGBottomField    )
    OSG_FC_FIELD_IDM_DECL      (OSGTopField       )
    OSG_FC_FIELD_IDM_DECL      (OSGParentField    )
    OSG_FC_FIELD_IDM_DECL      (OSGCameraField    )
    OSG_FC_FIELD_IDM_DECL      (OSGRootField      )
    OSG_FC_FIELD_IDM_DECL      (OSGBackgroundField)

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
    static const char *getClassname(void) { return "OSGViewport"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(OSGViewportPtr)

    /*------------------------- your_category -------------------------------*/

    virtual void draw( OSGDrawAction * action );

    
    void setParent    (OSGWindowPtr     parent);
    void setBackground(OSGBackgroundPtr bkgnd); 
    void setRoot      (OSGNodePtr       root);
    void setCamera    (OSGCameraPtr     cam);
    

    OSGWindowPtr        getParent  (void) const;
    OSGSFWindowPtr     *getSFParent(void);
    
    OSGBackgroundPtr    getBackground  (void) const;
    OSGSFBackgroundPtr *getSFBackground(void);
    
    OSGNodePtr          getRoot  (void) const;
    OSGSFNodePtr       *getSFRoot(void);
    
    OSGCameraPtr        getCamera  (void) const;
    OSGSFCameraPtr     *getSFCamera(void);

    
    void setSize(OSGReal32 left,  OSGReal32 bottom, 
                 OSGReal32 right, OSGReal32 top);
    

    void         setLeft  (OSGReal32 left);
    OSGReal32    getLeft  (void) const;
    OSGSFReal32 *getSFLeft(void);

    
    void         setRight  (OSGReal32 right);
    OSGReal32    getRight  (void) const;
    OSGSFReal32 *getSFRight(void);
    

    void         setBottom  (OSGReal32 bottom);
    OSGReal32    getBottom  (void) const;
    OSGSFReal32 *getSFBottom(void);
    

    void         setTop  (OSGReal32 top);
    OSGReal32    getTop  (void) const;
    OSGSFReal32 *getSFTop(void);

    
    OSGInt32 getPixelLeft  (void);
    OSGInt32 getPixelRight (void);
    OSGInt32 getPixelBottom(void);
    OSGInt32 getPixelTop   (void);
    OSGInt32 getPixelWidth (void);
    OSGInt32 getPixelHeight(void);
    
    OSGBool isFullWindow( void );
    
    /*------------------------- your_operators ------------------------------*/

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

    OSGBool operator < (const OSGViewport &other) const;
    
    //OSGBool operator == (const OSGViewport &other) const;
    //OSGBool operator != (const OSGViewport &other) const;

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

    /** Position of the viewport within the window. For 0 <= pos <= 1 it's a
        part of the window, for pos > 1 it's in pixel, and it's from the lower 
        left corner (OpenGL style). For part positioning the rightmost/topmost 
        pixel is not used, to allow tight packing.
    */  
    
    OSGSFReal32      _left;
    OSGSFReal32      _right;
    OSGSFReal32      _bottom;
    OSGSFReal32      _top;
    
    /** The window this viewport is assigned to. */
    OSGSFWindowPtr     _parent;
    
    /** The camera used by this viewport, or NULL. 
     *  If NULL, the static _defaultCamera is used. 
     */

    OSGSFCameraPtr     _camera;
    
    /** The root node of this viewport, or NULL. 
     *  If NULL, the static _defaultRoot is used. 
     */

    OSGSFNodePtr       _root;
    
    /** The background for this viewport, or NULL. 
     *  If NULL, the static _defaultBackground is used. 
     */

    OSGSFBackgroundPtr _background;
    
    /** NYI: properties, callbacks  */  
    
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGViewport(void);
    virtual ~OSGViewport(void); 

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

    OSGViewport(const OSGViewport &source);
    OSGViewport& operator =(const OSGViewport &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------


/** \brief class pointer
 */
typedef OSGViewport *OSGViewportP;

/** \brief OSGViewportPtr
 */
typedef OSGFCPtr<OSGFieldContainerPtr, OSGViewport> OSGViewportPtr;

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGViewportPtr field traits 
 */

template <>
struct OSGFieldDataTraits<OSGViewportPtr> : public OSGTraits
{
    static char    *getSName(void) { return "SFViewportPtr"; }
    static char    *getMName(void) { return "MFViewportPtr"; }

    static OSGBool  getFromString(OSGViewportPtr  &,
                                  const char     *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void     putToString(const OSGViewportPtr &,
                                      OSGString      &)
    {
        // TO_BE_DONE
    }
};

/** \brief OSGSFViewportPtr
 */
typedef OSGSField<OSGViewportPtr>       OSGSFViewportPtr;

/** \brief OSGMFViewportPtr
 */
typedef OSGMField<OSGViewportPtr>       OSGMFViewportPtr;

OSG_END_NAMESPACE

#include "OSGViewport.inl"

#endif /* _OSGVIEWPORT_H_ */
