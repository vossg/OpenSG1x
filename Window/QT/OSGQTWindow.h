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

#ifndef _OSG_QT_WINDOW_H_
#define _OSG_QT_WINDOW_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#ifdef OSG_WITH_QT

#ifdef __sgi
#pragma set woff 1375
#endif

#include <qgl.h>

#ifdef __sgi
#pragma reset woff 1375
#endif

#include <OSGWindowBase.h>
#include "OSGWindow.h"

#ifdef WIN32
#include "OSGWIN32Window.h"
#else
#include "OSGXWindow.h"
#endif

#include "OSGQGLWidget_qt.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class QTWindow;

typedef FCPtr <WindowPtr, QTWindow> QTWindowPtr;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief QT window class
 */

#ifdef WIN32
class OSG_WINDOW_DLLMAPPING QTWindow : public WIN32Window
#else
class OSG_WINDOW_DLLMAPPING QTWindow : public XWindow
#endif
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

    static const char *getClassname(void) { return "QTWindow"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(QTWindowPtr)

    /*------------------------- your_category -------------------------------*/
	
	// Window-system dependent functions
	
	// init the window: create the context
	virtual void init( void );
	
	/****** derived from WIN32Window / XWindow
	
	// activate the window: bind the OGL context	
	// set the active window, if needed
	virtual void activate( void );
	
	// swap buffers	for this window
  	// does not set the active window!
	virtual void swap( void );

	*/

    /*------------------------- your_operators ------------------------------*/

	void         setGlWidget  (OSGQGLWidget *glWidget) { _glWidget = glWidget; };
	OSGQGLWidget *getGlWidget (void)                   { return _glWidget; };

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

	QTWindow(void);
	virtual ~QTWindow(void); 

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

#ifdef WIN32
	typedef WIN32Window Inherited;
#else
	typedef XWindow Inherited;
#endif

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

	/// QT Widget
	OSGQGLWidget* _glWidget;
	
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    QTWindow(const QTWindow &source);
    void operator =(const QTWindow &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

/** \brief class pointer
 */
typedef QTWindow *QTWindowP;

/** \brief QTWindowPtr
 */
typedef FCPtr<WindowPtr, QTWindow> QTWindowPtr;

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief QTWindowPtr field traits 
 */

template <>
struct FieldDataTraits<QTWindowPtr> : public Traits
{
    enum                         { StringConvertable = 0x00  };

    static Char8 *getSName(void) { return "SFQTWindowPtr"; }
    static Char8 *getMName(void) { return "MFQTWindowPtr"; }
};

/** \brief SFQTWindowPtr
 */
typedef SField<QTWindowPtr>       SFQTWindowPtr;

#ifndef OSG_COMPILEQTWINDOWINST
#if defined(__sgi)

#pragma do_not_instantiate SField<QTWindowPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, QTWindowPtr, OSG_WINDOW_DLLTMPLMAPPING)

#endif
#endif

/** \brief MFQTWindowPtr
 */
typedef MField<QTWindowPtr>       MFQTWindowPtr;

#ifndef OSG_COMPILEQTWINDOWINST
#if defined(__sgi)

#pragma do_not_instantiate MField<QTWindowPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, QTWindowPtr, OSG_WINDOW_DLLTMPLMAPPING)

#endif
#endif

OSG_END_NAMESPACE

#include <OSGQTWindow.inl>

#endif /* OSG_WITH_QT */

#endif /* _OSG_QT_WINDOW_H_ */
