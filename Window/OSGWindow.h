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


#ifndef _OSG_WINDOW_H_
#define _OSG_WINDOW_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGSField.h>
#include <OSGMField.h>
#include <OSGSFSysTypes.h>
#include <OSGFieldContainer.h>
#include <OSGFieldContainerPtr.h>
#include <OSGFieldDescription.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class OSGViewport;
typedef OSGFCPtr <OSGFieldContainerPtr, OSGViewport> OSGViewportPtr;
typedef OSGMField<OSGViewportPtr                   > OSGMFViewportPtr;

class OSGPipe;
typedef OSGFCPtr <OSGFieldContainerPtr, OSGPipe> OSGPipePtr;
typedef OSGSField<OSGPipePtr                   > OSGSFPipePtr;

class OSGWindow;
typedef OSGFCPtr <OSGFieldContainerPtr, OSGWindow> OSGWindowPtr;
typedef OSGSField<OSGWindowPtr                   > OSGSFWindowPtr;

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

class OSGWindow : public OSGFieldContainer
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(OSGWidthField )

    OSG_FC_FIELD_IDM_DECL      (OSGHeightField)
    OSG_FC_FIELD_IDM_DECL      (OSGPortsField )

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

    static const char *getClassname(void) { return "OSGWindow"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_ABSTR_FIELD_CONTAINER_DECL(OSGWindowPtr)

    /*------------------------- your_category -------------------------------*/

    void addPort      (const OSGViewportPtr &portP);
    void insertPort   (      OSGUInt32       portIndex, 
                       const OSGViewportPtr &portP);

    void replacePort  (      OSGUInt32       portIndex, 
                       const OSGViewportPtr &portP);
    void replacePortBy(const OSGViewportPtr &portP, 
                       const OSGViewportPtr &newPortP);

    void subPort      (const OSGViewportPtr &portP);
    void subPort      (      OSGUInt32       portIndex);


    OSGViewportPtr    getPort   (OSGUInt32  portIndex);
    OSGMFViewportPtr *getMFPorts(void);
    
    
    void         setWidth  (OSGUInt16 width);
    OSGUInt16    getWidth  (void);
    OSGSFUInt16 *getSFWidth(void);
    

    void         setHeight  (OSGUInt16 height);
    OSGUInt16    getHeight  (void);
    OSGSFUInt16 *getSFHeight(void);
   

    void setSize(OSGUInt16 width, OSGUInt16 height);

    
    virtual void draw  (OSGDrawAction *action);
    virtual void resize(int width, int height);
    
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

    /** The width of the window. */
    OSGSFUInt16      _width;

    /** The height of the window. */
    OSGSFUInt16      _height;

    /** The viewports used by the window. */
    OSGMFViewportPtr _ports;

    /** The pipe this window is on. */
    // OSGSFPipePtr _parent;

    /** NYI: dlist sharing brothers */
    
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGWindow(void);
    virtual ~OSGWindow(void); 

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

    OSGWindow(const OSGWindow &source);
    OSGWindow& operator =(const OSGWindow &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

/** \brief class pointer
 */
typedef OSGWindow *OSGWindowP;

/** \brief OSGWindowPtr
 */
typedef OSGFCPtr<OSGFieldContainerPtr, OSGWindow> OSGWindowPtr;

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OSGWindowPtr field traits 
 */

template <>
struct OSGFieldDataTraits<OSGWindowPtr> : public OSGTraits
{
    static char    *getSName(void) { return "SFWindowPtr"; }
    static char    *getMName(void) { return "MFWindowPtr"; }

    static OSGBool  getFromString(OSGWindowPtr &,
                                  const char  *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void     putToString(const OSGWindowPtr &,
                                      OSGString    &)
    {
        // TO_BE_DONE
    }
};

/** \brief OSGSFWindowPtr
 */
typedef OSGSField<OSGWindowPtr>       OSGSFWindowPtr;

/** \brief OSGMFWindowPtr
 */
typedef OSGMField<OSGWindowPtr>       OSGMFWindowPtr;

OSG_END_NAMESPACE

#include "OSGWindow.inl"

#endif /* _OSG_WINDOW_H_ */

