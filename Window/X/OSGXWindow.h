/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#ifndef _OSG_X_WINDOW_H_
#define _OSG_X_WINDOW_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGConfig.h>

// Forget everything if we're doing a windows compile
#ifndef WIN32

#include <GL/glx.h>
#undef Bool

#include <OSGXWindowDef.h>
#include "OSGWindow.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class XWindow;
typedef FCPtr <WindowPtr, XWindow> XWindowPtr;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief X11 window class
 */

class OSG_XWINDOWLIB_DLLMAPPING XWindow : public Window
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "XWindow"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(XWindowPtr)

    /*------------------------- your_category -------------------------------*/
    
    /** GL implementation dependent function **/
    
    // query the system for a GL function
    virtual void (*getFunctionByName( const Char8 *s ))();
    
    /** Window-system dependent functions **/
    
    // init the window: create the context  
    virtual void init( void );
    
    // activate the window: bind the OGL context    
    // set the active window, if needed
    virtual void activate( void );
    
    virtual void deactivate ( void ) {}
    
    // swap buffers     for this window
    // does not set the active window!
    virtual void swap( void );

    
    /*------------------------- your_operators ------------------------------*/

    void        setDisplay   (Display *dpy)    { _dpy = dpy; };
    Display     *getDisplay  (void)            { return _dpy; };

    void        setWindow    (::Window hwin)   { _hwin = hwin; };
    ::Window    getWindow    (void)            { return _hwin; };

    void        setGlContext (GLXContext glcx) { _glcx = glcx; };
    GLXContext  getGlContext (void)            { return _glcx; };

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

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
    
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    XWindow(void);
    virtual ~XWindow(void); 

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef Window Inherited;

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
 
    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    // GLX stuff
    Display      *_dpy;
    ::Window     _hwin;
    GLXContext   _glcx;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    // prohibit default functions (move to 'public' if you need one)

    XWindow(const XWindow &source);
    void operator =(const XWindow &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

/** \brief class pointer
 */
typedef XWindow *XWindowP;

/** \brief XWindowPtr
 */
typedef FCPtr<WindowPtr, XWindow> XWindowPtr;

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief XWindowPtr field traits 
 */

template <>
struct FieldDataTraits<XWindowPtr> : public Traits
{
    enum                         { StringConvertable = 0x00  };

    static Char8 *getSName(void) { return "SFXWindowPtr"; }
    static Char8 *getMName(void) { return "MFXWindowPtr"; }
};

/** \brief SFXWindowPtr
 */
typedef SField<XWindowPtr>       SFXWindowPtr;

#if defined(__sgi)

#pragma do_not_instantiate SField<XWindowPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, XWindowPtr, OSG_XWINDOWLIB_DLLTMPLMAPPING)

#endif

/** \brief MFXWindowPtr
 */
typedef MField<XWindowPtr>       MFXWindowPtr;

#if defined(__sgi)

#pragma do_not_instantiate MField<XWindowPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, XWindowPtr, OSG_XWINDOWLIB_DLLTMPLMAPPING)

#endif

OSG_END_NAMESPACE

#include <OSGXWindow.inl>

#endif // Windows compile ?

#endif /* _OSG_X_WINDOW_H_ */
