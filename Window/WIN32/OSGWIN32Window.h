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

#ifndef _OSG_WIN32_WINDOW_H_
#define _OSG_WIN32_WINDOW_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGConfig.h>

// Forget everything if we're not doing a windows compile
#ifdef WIN32

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILEWIN32WINDOWLIB
#       define OSG_WIN32WINDOWLIB_DLLMAPPING     __declspec(dllexport)
#       define OSG_WIN32WINDOWLIB_DLLTMPLMAPPING __declspec(dllexport)
#   else
#       define OSG_WIN32WINDOWLIB_DLLMAPPING     __declspec(dllimport)
#       define OSG_WIN32WINDOWLIB_DLLTMPLMAPPING __declspec(dllimport)
#   endif
#else
#define OSG_WIN32WINDOWLIB_DLLMAPPING
#define OSG_WIN32WINDOWLIB_DLLTMPLMAPPING
#endif


#include <windows.h>

#include "OSGWindow.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class WIN32Window;
typedef FCPtr <WindowPtr, WIN32Window> WIN32WindowPtr;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief WIN32 window class
 */

class OSG_WIN32WINDOWLIB_DLLMAPPING WIN32Window : public Window
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

    static const char *getClassname(void) { return "WIN32Window"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(WIN32WindowPtr)

    /*------------------------- your_category -------------------------------*/

    /** GL implementation dependent function **/

    // query the system for a GL function
    virtual void (*getFunctionByName( const Char8 *s ))();
    
    // Window-system dependent functions
    
    // init the window: create the context  
    virtual void init( void );
    
    // activate the window: bind the OGL context    
    // set the active window, if needed
    virtual void activate( void );
    
    // deactivate the window: release the OGL context
    // release the hardware device context
    virtual void deactivate ( void );
    
    // swap buffers     for this window
    // does not set the active window!
    virtual void swap( void );

    /*------------------------- your_operators ------------------------------*/

    void  setWindow (HWND hwin)         { _hwin = hwin; };
    HWND  getWindow (void)          { return _hwin; };

    void  setHDC (HDC hdc)          { _hdc = hdc; };
    HDC       getHDC (void)                 { return _hdc; };
    
    void  setPaintStruct (PAINTSTRUCT ps) { _ps = ps; };
    PAINTSTRUCT getPaintStruct (void)    { return _ps; };

    void  setGLContext (HGLRC glcx)     { _glcx = glcx; };
    HGLRC getGLContext (void)       { return _glcx; };


    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

    /*------------------------------ dump -----------------------------------*/

    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;

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

    WIN32Window (void);
    WIN32Window(const WIN32Window &source);

    virtual ~WIN32Window (void);        

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

    // WIN32 stuff 
    HWND   _hwin;
    HDC        _hdc;
    HGLRC  _glcx;   
    PAINTSTRUCT _ps;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------   

    // prohibit default functions (move to 'public' if you need one)    
    void operator =(const WIN32Window &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

/** \brief class pointer
 */
typedef WIN32Window *WIN32WindowP;

/** \brief WIN32WindowPtr
 */
typedef FCPtr<WindowPtr, WIN32Window> WIN32WindowPtr;

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief WIN32WindowPtr field traits 
 */

template <>
struct FieldDataTraits<WIN32WindowPtr> : public Traits
{
    static char *getSName(void) { return "SFWIN32WindowPtr"; }
    static char *getMName(void) { return "MFWIN32WindowPtr"; }
};

/** \brief SFWIN32WindowPtr
 */
typedef SField<WIN32WindowPtr>       SFWIN32WindowPtr;

#ifndef OSG_COMPILEWINDOWWIN32INST
#if defined(__sgi)

#pragma do_not_instantiate SField<WIN32WindowPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, WIN32WindowPtr, OSG_WIN32WINDOWLIB_DLLTMPLMAPPING)

#endif
#endif

/** \brief MFWIN32WindowPtr
 */
typedef MField<WIN32WindowPtr>       MFWIN32WindowPtr;


#ifndef OSG_COMPILEWINDOWWIN32INST
#if defined(__sgi)

#pragma do_not_instantiate MField<WIN32WindowPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, WIN32WindowPtr, OSG_WIN32WINDOWLIB_DLLTMPLMAPPING)

#endif
#endif

OSG_END_NAMESPACE

#include "OSGWIN32Window.inl"

#endif // Windows compile ?

#endif /* _OSG_WIN32_WINDOW_H_ */
