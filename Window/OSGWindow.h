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

#ifndef _OSG_WINDOW_H_
#define _OSG_WINDOW_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGFunctors.h>
#include <OSGThreadManager.h>
#include <OSGLock.h>
#include <OSGSField.h>
#include <OSGMField.h>
#include <OSGSFSysTypes.h>
#include <OSGFieldContainer.h>
#include <OSGFieldContainerPtr.h>
#include <OSGFieldDescription.h>
#include "OSGWindowBase.h" 


OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class Viewport;
typedef FCPtr <FieldContainerPtr, Viewport> ViewportPtr;
typedef MField<ViewportPtr                > MFViewportPtr;

#ifndef OSG_COMPILEVIEWPORTINST
#if defined(__sgi)

#pragma do_not_instantiate MField<ViewportPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, ViewportPtr, OSG_WINDOW_DLLTMPLMAPPING)

#endif
#endif

class Pipe;
typedef FCPtr <FieldContainerPtr, Pipe> PipePtr;

class Window;
typedef FCPtr <FieldContainerPtr, Window> WindowPtr;

class DrawAction;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief Window base class
 */

class OSG_WINDOW_DLLMAPPING Window : public FieldContainer
{
  private:

    typedef FieldContainer Inherited;

  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(WidthField)

    OSG_FC_FIELD_IDM_DECL      (HeightField,		WidthField )
    OSG_FC_FIELD_IDM_DECL      (PortsField, 		HeightField)
    OSG_FC_FIELD_IDM_DECL      (ResizePendingField, PortsField)
    OSG_FC_FIELD_IDM_DECL      (GLObjectFlagsField, ResizePendingField)

    OSG_FC_LAST_FIELD_IDM_DECL (GLObjectFlagsField)

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

	enum GLObjectFlagE { 
		notused, initialize, initialized, needrefresh, destroy, finaldestroy };

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

	typedef Functor2Base<void,GLObjectFlagE,UInt32> GLObjectFunctor;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "Window"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_ABSTR_FIELD_CONTAINER_DECL(WindowPtr)

    /*------------------------- your_category -------------------------------*/

    void addPort      (const ViewportPtr &portP);
    void insertPort   (      UInt32       portIndex, 
                       const ViewportPtr &portP);

    void replacePort  (      UInt32       portIndex, 
                       const ViewportPtr &portP);
    void replacePortBy(const ViewportPtr &portP, 
                       const ViewportPtr &newPortP);

    void subPort      (const ViewportPtr &portP);
    void subPort      (      UInt32       portIndex);


    ViewportPtr    getPort   (UInt32  portIndex);
    MFViewportPtr *getMFPorts(void);
    
    
    void      setWidth  (UInt16 width);
    UInt16    getWidth  (void) const;
    SFUInt16 *getSFWidth(void);
    

    void      setHeight  (UInt16 height);
    UInt16    getHeight  (void) const;
    SFUInt16 *getSFHeight(void);

    void setSize(UInt16 width, UInt16 height);


	static UInt32	registerGLObject ( GLObjectFunctor functor, UInt32 num );
	void			validateGLObject ( UInt32 id );	
	void			refreshGLObject ( UInt32 id );	
	static void 	destroyGLObject  ( UInt32 id, UInt32 num );
 
    virtual void draw   			(DrawAction *action);
 	virtual void drawAllViewports 	(DrawAction *action);
	virtual void frame  			(void);
   
	void		setResizePending ( Bool resizePending );
	Bool		isResizePending  ( void );
 
    virtual void resize 			(int width, int height);
 	virtual void resizeGL			(void);
	   
    // Window-system dependent functions
    
    // init the window: create the context  
    virtual void init( void ) = 0;
    
    // activate the window: bind the OGL context    
    virtual void activate( void ) = 0;
    
    // swap front and back buffers  
    virtual void swap( void ) = 0;

    /*------------------------- your_operators ------------------------------*/

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

	class GLObject {

	  public:		  
	    GLObject( GLObjectFunctor funct ) : 
			functor( funct ), refCounter( 0 ) 
		{}

		GLObjectFunctor& getFunctor ( void ) 
		{
		    return ( functor );
		};
		  
	    void setFunctor ( GLObjectFunctor funct )
		{
			functor = funct;
		};

		UInt32 getRefCounter ( void ) 
		{
  		    return ( refCounter );
		}

		UInt32 incRefCounter ( void )
		{
			UInt32 val;
			
			if ( ! _GLObjectLock )
			{
				_GLObjectLock = ThreadManager::the()->getLock(NULL);
			}
			
			_GLObjectLock->aquire();
			val = refCounter = refCounter + 1;
			_GLObjectLock->release();
			
			return val;
		}

		UInt32 decRefCounter ( void )
		{
			UInt32 val;
			
			if ( ! _GLObjectLock )
			{
				_GLObjectLock = ThreadManager::the()->getLock(NULL);
			}
			
			_GLObjectLock->aquire();
			if ( refCounter )
				val = refCounter = refCounter - 1;
			else
				val = 0;
			_GLObjectLock->release();
			
			return val;
		}

	  protected:		
		GLObjectFunctor functor;
		volatile UInt32 refCounter;
	};

	typedef MField<GLObjectFlagE> MFGLObjectFlagE;
	

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    /** The width of the window. */
    SFUInt16		_width;

    /** The height of the window. */
    SFUInt16		_height;

    /** The viewports used by the window. */
    MFViewportPtr	_ports;

    /** Flag a pending resize. */
    SFBool  		_resizePending;

    /** The GLObject flags for this window. */
	// This should be global through all aspects
    MFGLObjectFlagE _glObjectFlags;

    /** NYI: dlist sharing brothers */
 
	/** GLObject stuff **/

	static Lock                       *_GLObjectLock;

	static vector<Window::GLObject*>  _glObjects;

	static vector<UInt32>			  _glObjectDestroyList;
   
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------
   
    SFBool  		*getSFResizePending(void);
    MFGLObjectFlagE *getMFGLObjectFlags(void);

    Window(void);
    Window(const Window &source);
    virtual ~Window(void); 
	
	// called when the context is created, to setup general OpenGL options
	virtual void setupGL( void );

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

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

    Window& operator =(const Window &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

/** \brief class pointer
 */
typedef Window *WindowP;

/** \brief WindowPtr
 */
typedef FCPtr<FieldContainerPtr, Window> WindowPtr;

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief WindowPtr field traits 
 */

template <>
struct FieldDataTraits<WindowPtr> : public Traits
{
    enum                         { StringConvertable = 0x00  };

    static Char8 *getSName(void) { return "SFWindowPtr"; }
    static Char8 *getMName(void) { return "MFWindowPtr"; }
};

/** \brief SFWindowPtr
 */

typedef SField<WindowPtr>       SFWindowPtr;



template <>
struct FieldDataTraits<Window::GLObjectFlagE> : public Traits
{
    enum                           { StringConvertable = 0x00  };

    static Char8 *getSName(void)   { return "SFGLObjectFlagE"; }
    static Char8 *getMName(void)   { return "MFGLObjectFlagE"; }
};

#ifndef OSG_COMPILEWINDOWINST
#if defined(__sgi)

#pragma do_not_instantiate SField<WindowPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, WindowPtr, OSG_WINDOW_DLLTMPLMAPPING)

#endif
#endif


/** \brief MFWindowPtr
 */

typedef MField<WindowPtr>       MFWindowPtr;


#ifndef OSG_COMPILEWINDOWINST
#if defined(__sgi)

#pragma do_not_instantiate MField<WindowPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, WindowPtr, OSG_WINDOW_DLLTMPLMAPPING)

#endif
#endif

OSG_END_NAMESPACE

#include "OSGWindow.inl"

#endif /* _OSG_WINDOW_H_ */

