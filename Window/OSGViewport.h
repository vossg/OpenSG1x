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

class Camera;
typedef FCPtr <FieldContainerPtr, Camera> CameraPtr;
typedef SField<CameraPtr                   > SFCameraPtr;

class Window;
typedef FCPtr <FieldContainerPtr, Window> WindowPtr;
typedef SField<WindowPtr                   > SFWindowPtr;

class Background;
typedef FCPtr <FieldContainerPtr, Background> BackgroundPtr;
typedef SField<BackgroundPtr                   > SFBackgroundPtr;

class Viewport;
typedef FCPtr <FieldContainerPtr, Viewport> ViewportPtr;
typedef SField<ViewportPtr                   > SFViewportPtr;

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

class OSG_DLLEXPORT Viewport : public FieldContainer
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(LeftField      )

    OSG_FC_FIELD_IDM_DECL      (RightField     )
    OSG_FC_FIELD_IDM_DECL      (BottomField    )
    OSG_FC_FIELD_IDM_DECL      (TopField       )
    OSG_FC_FIELD_IDM_DECL      (ParentField    )
    OSG_FC_FIELD_IDM_DECL      (CameraField    )
    OSG_FC_FIELD_IDM_DECL      (RootField      )
    OSG_FC_FIELD_IDM_DECL      (BackgroundField)

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
    static const char *getClassname(void) { return "Viewport"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(ViewportPtr)

    /*------------------------- your_category -------------------------------*/

    virtual void draw( DrawAction * action );

    
    void setParent    (WindowPtr     parent);
    void setBackground(BackgroundPtr bkgnd); 
    void setRoot      (NodePtr       root);
    void setCamera    (CameraPtr     cam);
    

    WindowPtr        getParent  (void) const;
    SFWindowPtr     *getSFParent(void);
    
    BackgroundPtr    getBackground  (void) const;
    SFBackgroundPtr *getSFBackground(void);
    
    NodePtr          getRoot  (void) const;
    SFNodePtr       *getSFRoot(void);
    
    CameraPtr        getCamera  (void) const;
    SFCameraPtr     *getSFCamera(void);

    
    void setSize(Real32 left,  Real32 bottom, 
                 Real32 right, Real32 top);
    

    void         setLeft  (Real32 left);
    Real32    getLeft  (void) const;
    SFReal32 *getSFLeft(void);

    
    void         setRight  (Real32 right);
    Real32    getRight  (void) const;
    SFReal32 *getSFRight(void);
    

    void         setBottom  (Real32 bottom);
    Real32    getBottom  (void) const;
    SFReal32 *getSFBottom(void);
    

    void         setTop  (Real32 top);
    Real32    getTop  (void) const;
    SFReal32 *getSFTop(void);

    
    Int32 getPixelLeft  (void);
    Int32 getPixelRight (void);
    Int32 getPixelBottom(void);
    Int32 getPixelTop   (void);
    Int32 getPixelWidth (void);
    Int32 getPixelHeight(void);
    
    Bool isFullWindow( void );
    
    /*------------------------- your_operators ------------------------------*/

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

    Bool operator < (const Viewport &other) const;
    
    //Bool operator == (const Viewport &other) const;
    //Bool operator != (const Viewport &other) const;

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
    
    SFReal32      _left;
    SFReal32      _right;
    SFReal32      _bottom;
    SFReal32      _top;
    
    /** The window this viewport is assigned to. */
    SFWindowPtr     _parent;
    
    /** The camera used by this viewport, or NULL. 
     *  If NULL, the static _defaultCamera is used. 
     */

    SFCameraPtr     _camera;
    
    /** The root node of this viewport, or NULL. 
     *  If NULL, the static _defaultRoot is used. 
     */

    SFNodePtr       _root;
    
    /** The background for this viewport, or NULL. 
     *  If NULL, the static _defaultBackground is used. 
     */

    SFBackgroundPtr _background;
    
    /** NYI: properties, callbacks  */  
    
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    Viewport(void);
    virtual ~Viewport(void); 

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

    Viewport(const Viewport &source);
    Viewport& operator =(const Viewport &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------


/** \brief class pointer
 */
typedef Viewport *ViewportP;

/** \brief ViewportPtr
 */
typedef FCPtr<FieldContainerPtr, Viewport> ViewportPtr;

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief ViewportPtr field traits 
 */

template <>
struct FieldDataTraits<ViewportPtr> : public Traits
{
    enum                         { StringConvertable = 0x00  };

    static Char8 *getSName(void) { return "SFViewportPtr"; }
    static Char8 *getMName(void) { return "MFViewportPtr"; }
};

/** \brief SFViewportPtr
 */
typedef SField<ViewportPtr>       SFViewportPtr;

/** \brief MFViewportPtr
 */
typedef MField<ViewportPtr>       MFViewportPtr;

OSG_END_NAMESPACE

#include "OSGViewport.inl"

#endif /* _OSGVIEWPORT_H_ */
