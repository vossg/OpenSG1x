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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <OSGGL.h>

#if !defined(WIN32) && !defined(darwin)
#include <GL/glx.h>
#endif

#if defined(__sgi) || defined(darwin) || defined(__hpux)
#include <dlfcn.h>
#endif

#include <OSGDrawAction.h>
#include <OSGRenderAction.h>

#include "OSGViewport.h"
// #include "OSGPipe.h"

#include "OSGBackground.h"
#include "OSGCamera.h"
#include "OSGWindow.h"

#if defined(__sgi) || defined(darwin) || defined(__hpux)   
#include <dlfcn.h>
#endif 

#if !defined(WIN32) && !defined(darwin)   
#include <GL/glx.h>   
#endif

OSG_BEGIN_NAMESPACE

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable)
#endif

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \defgroup WindowLib OpenSG Window Lib

The WindowLib include all objects concerned with opening, managing and
drawing into windows.

*/


/*! \defgroup Windows OpenSG Windows
    \ingroup WindowLib

The Windows group include all the general and window-system specific
Window objects.

*/

/*! \class osg::Window
    \ingroup Windows

The Window base class.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSG::Window::cvsid[] = "@(#)$Id: $";

/** global window list, need by static refreshGLObject */
/* I've had trouble with interferences with the X Window type, thus I'm using
   the fully qualified name here. */
   
std::vector<WindowPtr         >  OSG::Window::_allWindows;

// GLobject handling

Lock                            *OSG::Window::_GLObjectLock;
std::vector<Window::GLObject *>  OSG::Window::_glObjects;
std::vector<UInt32            >  OSG::Window::_glObjectDestroyList;

// GL extension handling

std::vector<IDStringLink      >  OSG::Window::_registeredExtensions;
std::vector<IDStringLink      >  OSG::Window::_registeredFunctions;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/** \brief initialize the static features of the class, e.g. action callbacks
 */

void OSG::Window::initMethod (void)
{
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

OSG::Window::Window(void) :
    Inherited()
{
    // only called for prototypes, no need to init them
}

/** \brief Copy Constructor
 */

OSG::Window::Window(const Window &source) :
    Inherited(source), 
    _lastValidate(source._lastValidate.size(),0),
    _extensions(),
    _availExtensions(),
    _extFunctions()
{       
    // mark all GL objects as not yet initialized
    doInitRegisterGLObject(1, _glObjects.size() - 1);
}

/** \brief Destructor
 */

OSG::Window::~Window(void)
{
    // delete the ports and the context
}


/** \brief instance initialisation
 */

void OSG::Window::onCreate( const Window * )
{
    // Don't add the prototype instances to the list
    if (GlobalSystemState != Running)
        return;
        
    _allWindows.push_back(WindowPtr(this)); 
}

/** \brief instance deletion
 */

void OSG::Window::onDestroy(void)
{
    std::vector<WindowPtr>::iterator it;

    it = std::find(_allWindows.begin(), _allWindows.end(), WindowPtr(this));
    
    // prototype windowa re not added to the list, so they might not be found.
    if(it != _allWindows.end()) 
        _allWindows.erase( it );
}

/** \brief react to field changes
 */

void OSG::Window::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*------------------------------ access -----------------------------------*/


void OSG::Window::addPort(const ViewportPtr &portP)
{
    if(portP != NullFC)
    {
        _mfPort.push_back(portP);
// CHECK CHECK
//        _mfPort.back()->setParent(FieldContainer::getPtr<WindowPtr>(*this));
        _mfPort.back()->setParent(WindowPtr(*this));
    }
}

void OSG::Window::insertPort(UInt32 portIndex, const ViewportPtr &portP)
{    
    MFViewportPtr::iterator portIt = _mfPort.begin();

    if(portP != NullFC)
    {
        portIt += portIndex;
  
// CHECK CHECK      
//        (*(_mfPort.insert(portIt, portP)))->setParent(
//            FieldContainer::getPtr<WindowPtr>(*this));
        (*(_mfPort.insert(portIt, portP)))->setParent(
            WindowPtr(*this));
    }
}


void OSG::Window::replacePort(UInt32 portIndex, const ViewportPtr &portP)
{
    if(portP != NullFC)
    {
        _mfPort[portIndex]->setParent(NullFC);
        _mfPort[portIndex] = portP;
// CHECK CHECK
//        _mfPort.getValue(portIndex)->setParent(
//            FieldContainer::getPtr<WindowPtr>(*this));
        _mfPort[portIndex]->setParent(
            WindowPtr(*this));
    }
}

void OSG::Window::replacePortBy(const ViewportPtr &portP, 
                             const ViewportPtr &newportP)
{
    MFViewportPtr::iterator portIt = _mfPort.find(portP);

    if(newportP != NullFC)
    {
        if(portIt != _mfPort.end())
        {
            (*portIt)->setParent(NullFC);
            (*portIt) = newportP;
// CHECK CHECK
//            (*portIt)->setParent(
//                FieldContainer::getPtr<WindowPtr>(*this));
            (*portIt)->setParent(
                WindowPtr(*this));
        }
    }
}

void OSG::Window::subPort(const ViewportPtr &portP)
{
    MFViewportPtr::iterator portIt = _mfPort.find(portP);

    if(portIt != _mfPort.end())
    {
        (*portIt)->setParent(NullFC);

        _mfPort.erase(portIt);
    }

}

void OSG::Window::subPort(UInt32  portIndex)
{
    MFViewportPtr::iterator portIt = _mfPort.begin();

    portIt += portIndex;

    if(portIt != _mfPort.end())
    {
        (*portIt)->setParent(NullFC);

        _mfPort.erase(portIt);
    }
}


// GL object handling

UInt32 OSG::Window::registerGLObject(GLObjectFunctor functor, UInt32 num)
{
    UInt32    id, i; 
    GLObject *pGLObject;

    // reserve index 0, illegal for most OpenGL functions
    if(_glObjects.empty())
        _glObjects.push_back( NULL );   

    id        = _glObjects.size();
    pGLObject = new GLObject(functor);
    
    // does the requested block fit into the capacity?
    
    if(_glObjects.capacity() >= id + num)
    {
        _glObjects.insert(_glObjects.end(), num, pGLObject );
        
        initRegisterGLObject(id, num);
       
        return id;
    }
    
    // doesn't fit, try to find a block in the middle
    
    UInt32 cnt = 0;        

    // start searching at 1, id 0 is reserved for GL
    for(i = 1; i < _glObjects.size(); ++i)
    {       
        if(!_glObjects[i]) 
        {
            if(cnt == 0)
            {
                id = i;
            }

            ++cnt;

            if(cnt == num) 
            {
                // block of unused entries found ...
                        
                while(i >= id) 
                {
                    _glObjects[i] = pGLObject;
                    i = i - 1;
                } 
                
                initRegisterGLObject(id, num);
                   
                return id;
            }
        }
        else
        {
            cnt = 0;
        }
    }
    
    // no block found, add at the end
    
    // fill the empty slots at the end 
    i = id + cnt - 1;
    while ( i >= id )
    {
        _glObjects[i] = pGLObject;
        i = i - 1;
    }
    
    // expand the vector for the rest 
    for ( i = 1; i <= num - cnt; i++ ) 
    {       
        _glObjects.push_back( pGLObject );
    }
                
     initRegisterGLObject(id, num);
    
    return id;
}

void OSG::Window::validateGLObject ( UInt32 id )
{
    if ( id == 0 )
    {
        SWARNING << "Window::validateGLObject: id is 0!" << std::endl;
            return;
    }
    
    GLObject *obj = _glObjects[id];
    
    if(id >= _lastValidate.size()) // can happen if multi-threading
    {
        _lastValidate.insert(_lastValidate.end(), 
                             id + 1 - _lastValidate.size(),
                             0);
    }
    
    FDEBUG(("Window 0x%p (event %d,ri:%d,rf:%d): "
            "Validating object %d: last reinit:%d, last validate:"
            "%d last refresh: %d => %s\n", 
            this, getGlObjectEventCounter(), 
            _mfGlObjectLastReinitialize.size(),
            _mfGlObjectLastRefresh.size(),
            id, 
            (_mfGlObjectLastReinitialize.size() > id)?
                _mfGlObjectLastReinitialize[id]:0xffffffff,
            _lastValidate[id],
            (_mfGlObjectLastRefresh.size() > id)?
                _mfGlObjectLastRefresh[id]:0xffffffff,
            (_mfGlObjectLastReinitialize[id] == 0)?"init":
            ((_mfGlObjectLastReinitialize[id] > _lastValidate[id])?"reinit":
            ((_mfGlObjectLastRefresh[id] > _lastValidate[id])?"refresh":
            "up-to-date"))
          ));
    
    if(_mfGlObjectLastReinitialize[id] == 0)
    {
        obj->incRefCounter();
        obj->getFunctor().call(this, packIdStatus(id, initialize));
        _mfGlObjectLastReinitialize[id] = 1;
        _lastValidate[id] = getGlObjectEventCounter();
    }
    else if(_mfGlObjectLastReinitialize[id] > _lastValidate[id])
    {
        obj->getFunctor().call(this, packIdStatus(id, reinitialize));
        _lastValidate[id] = getGlObjectEventCounter();
    }
    else if(_mfGlObjectLastRefresh[id] > _lastValidate[id])
    {
        obj->getFunctor().call(this, packIdStatus(id, needrefresh));
        _lastValidate[id] = getGlObjectEventCounter();
    }
}

void OSG::Window::refreshGLObject( UInt32 id )
{
    if ( id == 0 )
    {
        SWARNING << "Window::refreshGLObject: id is 0!" << std::endl;
        return;
    }

    std::vector<WindowPtr>::iterator it;

    for ( it = _allWindows.begin(); it != _allWindows.end(); ++it)
    {
        beginEditCP(*it, GlObjectEventCounterFieldMask|
                         GlObjectLastRefreshFieldMask);

        UInt32 lastinv = (*it)->getGlObjectEventCounter() + 1;
        MFUInt32 &field = (*it)->_mfGlObjectLastRefresh;
        if(field.size() < id)
            field.getValues().insert(field.end(), id - field.size() + 1, 0 );
        field[id] = lastinv;
        (*it)->setGlObjectEventCounter(lastinv);

        endEditCP  (*it, GlObjectEventCounterFieldMask|
                         GlObjectLastRefreshFieldMask);
    }
}

void OSG::Window::reinitializeGLObject(UInt32 id)
{
    if ( id == 0 )
    {
        SWARNING << "Window::reinitializeGLObject: id is 0!" << std::endl;
        return;
    }

    std::vector<WindowPtr>::iterator it;

    for(it = _allWindows.begin(); it != _allWindows.end(); ++it)
    {
        beginEditCP(*it, GlObjectEventCounterFieldMask|
                         GlObjectLastReinitializeFieldMask);

        UInt32 lastinv = (*it)->getGlObjectEventCounter() + 1;
        MFUInt32 &field = (*it)->_mfGlObjectLastReinitialize;
        if(field.size() < id)
            field.getValues().insert(field.end(), id - field.size() + 1, 0 );
        field[id] = lastinv;
        (*it)->setGlObjectEventCounter(lastinv);

        endEditCP  (*it, GlObjectEventCounterFieldMask|
                         GlObjectLastReinitializeFieldMask);
    }
}


void OSG::Window::initRegisterGLObject(UInt32 id, UInt32 num)
{
    if ( id == 0 )
    {
        SWARNING << "Window::initRegisterGLObject: id is 0!" << std::endl;
        return;
    }

    std::vector<WindowPtr>::iterator it;

    for(it = _allWindows.begin(); it != _allWindows.end(); ++it)
    {
        (*it)->doInitRegisterGLObject(id, num);
    }
}

void OSG::Window::doInitRegisterGLObject(UInt32 id, UInt32 num)
{
    WindowPtr win(this);
    
    beginEditCP(win, GlObjectLastReinitializeFieldMask|
                     GlObjectLastRefreshFieldMask);

    if(_mfGlObjectLastReinitialize.size() < id + num)
    {
        _mfGlObjectLastReinitialize.resize(id + num);
        _mfGlObjectLastRefresh.resize(id + num);
        _lastValidate.resize(id + num);
    }

    for(UInt32 i = id; i < id + num; ++i)
    {
        _mfGlObjectLastReinitialize[i] = 0;
        _mfGlObjectLastRefresh     [i] = 0;
        _lastValidate[i] = 0;
   }

    endEditCP  (win, GlObjectLastReinitializeFieldMask|
                     GlObjectLastRefreshFieldMask);
}

void OSG::Window::destroyGLObject(UInt32 id, UInt32 num)
{
    _glObjectDestroyList.push_back( id );
    _glObjectDestroyList.push_back( num );
}

void OSG::Window::dumpExtensions ( void )
{   
    std::vector<IDString>::iterator it;
    std::cout << "GL Extensions: ";
    for ( it = _extensions.begin(); it != _extensions.end(); it++ )
    {
        std::cout << it->str() << ", ";
    }
    std::cout << std::endl;       
}

void OSG::Window::frameInit( void )
{
    // get extensions and split them
    if(_extensions.empty())
    {
        IDString s((const Char8 *) glGetString(GL_EXTENSIONS));
        s.tokenize( _extensions );
        std::sort( _extensions.begin(), _extensions.end() );
        
        // if we don't have any extensions, add something anyway
        if(_extensions.empty())
            _availExtensions.resize(_registeredExtensions.size(), false);
    }
    
    // any new extension registered ? 
    while(_registeredExtensions.size() > _availExtensions.size())
    {                           
        /* perform a binary search over the retrieved extension strings.
           Push back the result as an availability flag for the extension
           requested by the application */         
        _availExtensions.push_back( 
            std::binary_search( 
                _extensions.begin(),
                _extensions.end(),
                IDString(_registeredExtensions[_availExtensions.size()]) ) );
    }

    // any new functions registered ? 
    while(_registeredFunctions.size() > _extFunctions.size())
    {   
        const Char8 *s    = _registeredFunctions[_extFunctions.size()].str();
        void        *func = (void*)getFunctionByName(s);

        _extFunctions.push_back(func);
    }
}

// NOTE: this is not quite threadsafe and doesn't work in a cluster environment
// FIXME!!!

void OSG::Window::frameExit(void)
{   
    if(_glObjectDestroyList.size() > 0)
    {
        UInt32 i, n;
        i = _glObjectDestroyList[ _glObjectDestroyList.size()-2 ] ;
        n = _glObjectDestroyList[ _glObjectDestroyList.size()-1 ] ;

        UInt32 rc = _glObjects[ i ]->getRefCounter();

        if(getGlObjectLastReinitialize()[i] != 0) 
        {                  
            _glObjects[i]->getFunctor().call( this, packIdStatus(i, destroy));

            if ( ! ( rc = _glObjects[ i ]->decRefCounter() )  )
            {           
                // call functor with the final-flag
                _glObjects[i]->getFunctor().call( this, 
                                                packIdStatus(i, finaldestroy));
            }
        }

        // if the GLObject is removed from each GL-Context, free GLObject-IDs.

        if ( ! rc )
        {
            delete _glObjects[ i ];
            for ( UInt32 j = 0; j < n ; j++)
            {
                _glObjects[i+j] = NULL;
            }   
            _glObjectDestroyList.pop_back(); 
            _glObjectDestroyList.pop_back();
        }
    }
}


// Query for a GL extension function
// Yes, this is system dependent, but the system dependent parts are 
// #ifdefed anyway, and very similar code would show up in a number of places,
// making maintaining it unnecessarily hard

void (*Window::getFunctionByName(const Char8 *s))(void)
{
#if defined(GLX_VERSION_1_4)

    return glXGetProcAddress((const GLubyte *) s);

// UGLY HACK: SGI/NVidia header don't define GLX_ARB_get_proc_address,
// but they use __GLX_glx_h__ instead of GLX_H as an include guard.
#elif defined(GLX_ARB_get_proc_address) // || defined(__GLX_glx_h__)

    return glXGetProcAddressARB((const GLubyte *) s);

#elif defined(__hpux) || defined (__sgi)

    static void *libHandle = NULL;

    if(libHandle == NULL)
    {
        // HACK, but if we get here we link against libGL anyway
        libHandle = dlopen(NULL, RTLD_GLOBAL);
    }

    return (void (*)(void)) dlsym(libHandle, s);

#elif defined(darwin)

    static void *libHandle = NULL;

    if(libHandle == NULL)
    {
        libHandle = dlopen("libGL.dylib", RTLD_NOW);
    }

    return (void (*)(void)) dlsym(libHandle, s);

#elif defined(WIN32)

    return (void(__cdecl*)(void)) wglGetProcAddress(s);

#else

    return NULL;

#endif
}


void OSG::Window::setupGL( void )
{   
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
    glPixelStorei( GL_PACK_ALIGNMENT, 1 );
    
    glDepthFunc( GL_LEQUAL );
    glEnable( GL_DEPTH_TEST );
}

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

    
void OSG::Window::draw( DrawAction * action )
{
    activate();
    frameInit();    // query recently registered GL extensions
    
    resizeGL();

    drawAllViewports( action );

    swap();
    frameExit();    // after frame cleanup: delete GL objects, if needed
}

void OSG::Window::drawAllViewports( DrawAction * action )
{
    MFViewportPtr::iterator       portIt  = _mfPort.begin();
    MFViewportPtr::const_iterator portEnd = _mfPort.end();

    if(action != NULL)
    {
        action->setWindow( this );
        
        while ( portIt != portEnd )
        {
            (*portIt)->draw( action );

            ++portIt;
        }
    }
    else
    {
        SWARNING << "Window::drawAllViewports: no action!" << std::endl;
    }
}
    
void OSG::Window::render( RenderAction * action )
{
    activate();
    frameInit();    // query recently registered GL extensions
    
//  resizeGL();

    renderAllViewports( action );

    swap();
    frameExit();    // after frame cleanup: delete GL objects, if needed
}
    
void OSG::Window::renderAllViewports( RenderAction * action )
{
    MFViewportPtr::iterator       portIt  = _mfPort.begin();
    MFViewportPtr::const_iterator portEnd = _mfPort.end();

    if(action != NULL)
    {
        action->setWindow( this );
        
        while ( portIt != portEnd )
        {
            (*portIt)->render( action );
            ++portIt;
        }
    }
    else
    {
        SWARNING << "Window::renderAllViewports: no action!" << std::endl;
    }
}
    
void OSG::Window::resize( int width, int height )
{
    WindowPtr win(*this);
    beginEditCP(win, WidthFieldMask|HeightFieldMask|ResizePendingFieldMask);
    setWidth( width );
    setHeight( height );
    setResizePending( true );
    endEditCP  (win, WidthFieldMask|HeightFieldMask|ResizePendingFieldMask);
}
    
void OSG::Window::resizeGL( void )
{
    if ( isResizePending () )
    {
        glViewport( 0, 0, getWidth(), getHeight() );
        WindowPtr win(*this);
        beginEditCP(win, ResizePendingFieldMask);
        setResizePending( false );
        endEditCP  (win, ResizePendingFieldMask);
    }
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

OSG::Window& Window::operator = (const Window &source)
{
    if (this == &source)
        return *this;

    // copy 

    setWidth( source.getWidth() );
    setHeight( source.getHeight() );
    _mfPort.setValues( source._mfPort.getValues() );
    
    // mark all GL objects as not yet initialized
    doInitRegisterGLObject(1, _glObjects.size() - 1);
    
    return *this;
}


/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void OSG::Window::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                  const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump Window NI" << std::endl;
}

    
OSG_END_NAMESPACE

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

