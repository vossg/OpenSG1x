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

#ifndef _OSG_GLUT_WINDOW_H_
#define _OSG_GLUT_WINDOW_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#ifdef OSG_WITH_GLUT

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILEGLUTWINDOWLIB
#       define OSG_GLUTWINDOWLIB_DLLMAPPING     __declspec(dllexport)
#       define OSG_GLUTWINDOWLIB_DLLTMPLMAPPING __declspec(dllexport)
#   else
#       define OSG_GLUTWINDOWLIB_DLLMAPPING     __declspec(dllimport)
#       define OSG_GLUTWINDOWLIB_DLLTMPLMAPPING __declspec(dllimport)
#   endif
#else
#define OSG_GLUTWINDOWLIB_DLLMAPPING
#define OSG_GLUTWINDOWLIB_DLLTMPLMAPPING
#endif

#include "OSGWindowBase.h"
#include "OSGWindow.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class GLUTWindow;
typedef FCPtr <WindowPtr, GLUTWindow> GLUTWindowPtr;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief GLUT window class
 */

class OSG_GLUTWINDOWLIB_DLLMAPPING GLUTWindow : public Window
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

    static const char *getClassname(void) { return "GLUTWindow"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(GLUTWindowPtr)

    /*------------------------- your_category -------------------------------*/

	/** GL implementation dependent function **/
	
	// query the system for a GL function
	virtual void (*getFunctionByName( const Char8 *s ))();
	
	// Window-system dependent functions
	
	// init the window: create the context	
	// Nothing to do here for GLUT
	virtual void init( void );
	
	// activate the window: bind the OGL context	
	// set the active window, if needed
	virtual void activate( void );
	
	virtual void deactivate ( void ) {}
	
	// swap buffers	for this window
	// does not set the active window!
	virtual void swap( void );

    /*------------------------- your_operators ------------------------------*/

	void     setWinID(int id) { _winid = id;   };
	Int32 setWinID(void)   { return _winid; };

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

    GLUTWindow(void);
    virtual ~GLUTWindow(void); 

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

	/// window id
	Int32 _winid;
	
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    GLUTWindow(const GLUTWindow &source);
    void operator =(const GLUTWindow &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

/** \brief class pointer
 */
typedef GLUTWindow *GLUTWindowP;

/** \brief GLUTWindowPtr
 */
typedef FCPtr<WindowPtr, GLUTWindow> GLUTWindowPtr;

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief GLUTWindowPtr field traits 
 */

template <>
struct FieldDataTraits<GLUTWindowPtr> : public Traits
{
    static DataType                 _type;
    enum                            { StringConvertable = 0x00  };

    static DataType &getType (void) { return _type;             }
    static Char8    *getSName(void) { return "SFGLUTWindowPtr"; }
    static Char8    *getMName(void) { return "MFGLUTWindowPtr"; }
};

/** \brief SFGLUTWindowPtr
 */

typedef SField<GLUTWindowPtr>       SFGLUTWindowPtr;

#ifndef OSG_COMPILEGLUTWINDOWINST
#if defined(__sgi)

#pragma do_not_instantiate SField<GLUTWindowPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, GLUTWindowPtr, OSG_GLUTWINDOWLIB_DLLTMPLMAPPING)

#endif
#endif

/** \brief MFGLUTWindowPtr
 */

typedef MField<GLUTWindowPtr>       MFGLUTWindowPtr;

#ifndef OSG_COMPILEGLUTWINDOWINST
#if defined(__sgi)

#pragma do_not_instantiate MField<GLUTWindowPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, GLUTWindowPtr, OSG_GLUTWINDOWLIB_DLLTMPLMAPPING)

#endif
#endif

OSG_END_NAMESPACE

#include "OSGGLUTWindow.inl"

#endif /* OSG_WITH_GLUT */

#endif /* _OSG_GLUT_WINDOW_H_ */
