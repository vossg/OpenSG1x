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


#ifndef _OSG_GLUT_WINDOW_H_
#define _OSG_GLUT_WINDOW_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGWindow.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class OSGGLUTWindow;
typedef OSGFCPtr <OSGWindowPtr, OSGGLUTWindow> OSGGLUTWindowPtr;
typedef OSGSField<OSGGLUTWindowPtr           > OSGSFGLUTWindowPtr;

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

class OSGGLUTWindow : public OSGWindow
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

    static const char *getClassname(void) { return "OSGGLUTWindow"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~OSGGLUTWindow(void); 

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(OSGGLUTWindowPtr)

    /*------------------------- your_category -------------------------------*/
	
	// Window-system dependent functions
	
	// init the window: create the context	
	// Nothing to do here for GLUT
	virtual void init( void );
	
	// activate the window: bind the OGL context	
	// set the active window, if needed
	virtual void activate( void );
	
	// swap buffers	for this window
	// does not set the active window!
	virtual void swap( void );

    /*------------------------- your_operators ------------------------------*/

	void     setWinID(int id) { _winid = id;   };
	OSGInt32 setWinID(void)   { return _winid; };

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
	
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGGLUTWindow(void);

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGWindow Inherited;

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
 
    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

	/// window id
	OSGInt32 _winid;
	
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    OSGGLUTWindow(const OSGGLUTWindow &source);
    void operator =(const OSGGLUTWindow &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

/** \brief class pointer
 */
typedef OSGGLUTWindow *OSGGLUTWindowP;

/** \brief OSGGLUTWindowPtr
 */
typedef OSGFCPtr<OSGWindowPtr, OSGGLUTWindow> OSGGLUTWindowPtr;

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGGLUTWindowPtr field traits 
 */

template <>
struct OSGFieldDataTraits<OSGGLUTWindowPtr> : public OSGTraits
{
    static char *getSName(void) { return "SFGLUTWindowPtr"; }
    static char *getMName(void) { return "MFGLUTWindowPtr"; }
};

/** \brief OSGSFGLUTWindowPtr
 */
typedef OSGSField<OSGGLUTWindowPtr>       OSGSFGLUTWindowPtr;

/** \brief OSGMFGLUTWindowPtr
 */
typedef OSGMField<OSGGLUTWindowPtr>       OSGMFGLUTWindowPtr;

OSG_END_NAMESPACE

#include <OSGGLUTWindow.inl>

#endif /* _OSG_GLUT_WINDOW_H_ */
