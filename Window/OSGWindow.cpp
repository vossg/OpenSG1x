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

#include <GL/gl.h>

#include <OSGDrawAction.h>
#include <OSGRenderAction.h>

#include "OSGViewport.h"
// #include "OSGPipe.h"

#include "OSGBackground.h"
#include "OSGCamera.h"
#include "OSGWindow.h"

OSG_USING_NAMESPACE

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

char Window::cvsid[] = "@(#)$Id: $";

const WindowPtr Window::NullWindow(NullFC);

/** global window list, need by static refreshGLObject */

vector<WindowPtr>         Window::_allWindows;

// GLobject handling

Lock                      *Window::_GLObjectLock;
vector<Window::GLObject*>  Window::_glObjects;
vector<UInt32>             Window::_glObjectDestroyList;

// GL extension handling

vector<IDStringLink>               Window::_registeredExtensions;
vector<IDStringLink>               Window::_registeredFunctions;

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

void Window::initMethod (void)
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

Window::Window(void) :
    Inherited()
{
    // reserve index 0, illegal for most OpenGL functions
    if ( _glObjects.empty() )
        _glObjects.push_back( NULL );   
}

/** \brief Copy Constructor
 */

Window::Window(const Window &source) :
    Inherited(source)
{
    // mark all flags as notused, i.e. have to initialize on use
    for ( vector<UInt32>::iterator it = _mfGlObjectStatus.begin();
            it != _mfGlObjectStatus.end(); ++it )
        *it = notused;
}

/** \brief Destructor
 */

Window::~Window(void)
{
    // delete the ports and the context
}


/** \brief instance initialisation
 */

void Window::onCreate( const FieldContainer & )
{
    _allWindows.push_back( WindowPtr(*this ) );
}

/** \brief instance deletion
 */

void Window::onDestroy(void)
{
    vector<WindowPtr>::iterator it;

    it = find( _allWindows.begin(), _allWindows.end(), WindowPtr( this ) );
    
    if(it == _allWindows.end()) 
    {
        FWARNING(("Window::onDestroy: couldn't find window %p!\n", this ));
    }
    else
        _allWindows.erase( it );
}

/** \brief react to field changes
 */

void Window::changed(BitVector, ChangeMode)
{
}

/*------------------------------ access -----------------------------------*/


void Window::addPort(const ViewportPtr &portP)
{
    if(portP != NullFC)
    {
        _mfPort.addValue(portP);
// CHECK CHECK
//        _mfPort.back()->setParent(FieldContainer::getPtr<WindowPtr>(*this));
        _mfPort.back()->setParent(WindowPtr(*this));
    }
}

void Window::insertPort(UInt32 portIndex, const ViewportPtr &portP)
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


void Window::replacePort(UInt32 portIndex, const ViewportPtr &portP)
{
    if(portP != NullFC)
    {
        _mfPort.getValue(portIndex)->setParent(NullWindow);
        _mfPort.getValue(portIndex) = portP;
// CHECK CHECK
//        _mfPort.getValue(portIndex)->setParent(
//            FieldContainer::getPtr<WindowPtr>(*this));
        _mfPort.getValue(portIndex)->setParent(
            WindowPtr(*this));
    }
}

void Window::replacePortBy(const ViewportPtr &portP, 
                             const ViewportPtr &newportP)
{
    MFViewportPtr::iterator portIt = _mfPort.find(portP);

    if(newportP != NullFC)
    {
        if(portIt != _mfPort.end())
        {
            (*portIt)->setParent(NullWindow);
            (*portIt) = newportP;
// CHECK CHECK
//            (*portIt)->setParent(
//                FieldContainer::getPtr<WindowPtr>(*this));
            (*portIt)->setParent(
                WindowPtr(*this));
        }
    }
}

void Window::subPort(const ViewportPtr &portP)
{
    MFViewportPtr::iterator portIt = _mfPort.find(portP);

    if(portIt != _mfPort.end())
    {
        (*portIt)->setParent(NullWindow);

        _mfPort.erase(portIt);
    }

}

void Window::subPort(UInt32  portIndex)
{
    MFViewportPtr::iterator portIt = _mfPort.begin();

    portIt += portIndex;

    if(portIt != _mfPort.end())
    {
        (*portIt)->setParent(NullWindow);

        _mfPort.erase(portIt);
    }
}

UInt32 Window::registerGLObject ( GLObjectFunctor functor, UInt32 num )
{
    UInt32    id, i; 
    GLObject *pGLObject;

    id        = _glObjects.size();
    i         = 0;
    pGLObject = new GLObject( functor );
    
    // does the requested block fit into the capacity?
    
    if (  ( _glObjects.capacity() >= id+num ) || ( !id )  )
    {
        while ( i < num ) 
        {
            _glObjects.push_back( pGLObject );

            i = i + 1;
        }       
        return( id );
    }
    
    // doesn't fit, try to find a block in the middle
    
    UInt32 cnt = 0;        

    // start searching at 1, id 0 is reserved for GL
    for ( i = 1; i < _glObjects.size(); i++ )
    {       
        if ( !_glObjects[i] ) 
        {
            if ( cnt == 0 )
            {
                id = i;
                cnt = cnt + 1;
            }

            if ( cnt == num ) 
            {
                // block of unused entries found ...
                        
                while ( i >= id ) 
                {
                    _glObjects[i] = pGLObject;
                    i = i - 1;
                } 
                            
                return ( id );
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
    
    return ( id );
}

void Window::validateGLObject ( UInt32 id )
{
    UInt32 s;

    if ( id == 0 )
    {
        SWARNING << "Window::validateGLObject: id is 0!" << endl;
            return;
    }
    
    s = _mfGlObjectStatus.size();
    while ( s <= id ) 
    {
        _mfGlObjectStatus.push_back( notused );
        s = s + 1;
    }
    
    GLObject *obj = _glObjects[id];
    
    if(_mfGlObjectLastReinitialize.size() > id &&
       _mfGlObjectLastReinitialize[id] > obj->getLastValidate())
    {
        _mfGlObjectStatus[id] = reinitialize;
        obj->getFunctor().call( this, id );
        _mfGlObjectStatus[id] = initialized;
        obj->setLastValidate(getGlObjectInvalidateCounter());
    }
    else if(_mfGlObjectLastRefresh.size() > id &&
            _mfGlObjectLastRefresh[id] > obj->getLastValidate())
    {
        _mfGlObjectStatus[id] = needrefresh;
        obj->getFunctor().call( this, id );
        _mfGlObjectStatus[id] = initialized;
        obj->setLastValidate(getGlObjectInvalidateCounter());
    }
    else if(obj->getLastValidate() == 0)
    {
        _mfGlObjectStatus[id] = initialize;
        obj->incRefCounter();
        obj->getFunctor().call( this, id );
        _mfGlObjectStatus[id] = initialized;
        obj->setLastValidate(getGlObjectInvalidateCounter());
    }
}

void Window::refreshGLObject( UInt32 id )
{
    vector<WindowPtr>::iterator it;

    for ( it = _allWindows.begin(); it != _allWindows.end(); it++ )
    {
        (*it)->doRefreshGLObject( id );
    }
}

void Window::doRefreshGLObject( UInt32 id )
{
    if ( id == 0 )
    {
        SWARNING << "Window::refreshGLObject: id is 0!" << endl;
            return;
    }
    
    if ( id >= _mfGlObjectStatus.size() )
    {
        // this can happen if an object is refreshed before it is rendered.

        for(UInt32 s = _mfGlObjectStatus.size(); s <= id; s++)
            _mfGlObjectStatus.push_back( notused );
    }
    
    switch ( _mfGlObjectStatus[id] ) 
    {
    case notused:    // not used yet, no need to refresh
    case destroy:
    case finaldestroy:  // object is being destroyed, ignore refresh
    case reinitialize:  // object is being reinitialized, ignore refresh
        break;
    case initialize:    // can't happen, internal temporal state
        SWARNING << "Window::refreshGLObject: id " << id
                 << " in state initialize ?!?!" << endl;
        return;
    case needrefresh:// already needing refresh
    case initialized:
        {
        WindowPtr win = WindowPtr(*this);
        beginEditCP(win, GlObjectStatusFieldMask|
                         GlObjectLastRefreshFieldMask);
                         
        _mfGlObjectStatus[id] = needrefresh;
        
        UInt32 s = _mfGlObjectLastRefresh.size();
        while ( s <= id ) 
        {
            _mfGlObjectLastRefresh.push_back(0);
            s = s + 1;
        }

        UInt32 lastinv = getGlObjectInvalidateCounter() + 1;
        _mfGlObjectLastRefresh[id] = lastinv;
        setGlObjectInvalidateCounter(lastinv);
        
        endEditCP  (win, GlObjectStatusFieldMask|
                         GlObjectLastRefreshFieldMask);
        }
        break;
    default:
        SWARNING << "Window::refreshGLObject: id " << id
                 << " in state " << _mfGlObjectStatus[id] << "?!?!" << endl;
        return;
    }
}

void Window::reinitializeGLObject( UInt32 id )
{
    vector<WindowPtr>::iterator it;

    for ( it = _allWindows.begin(); it != _allWindows.end(); it++ )
    {
        (*it)->doReinitializeGLObject( id );
    }
}

void Window::doReinitializeGLObject( UInt32 id )
{
    if ( id == 0 )
    {
        SWARNING << "Window::reinitializeGLObject: id is 0!" << endl;
            return;
    }
    
    if ( id >= _mfGlObjectStatus.size() )
    {
        // this can happen if an object is reinitialized before it is rendered.

        for(UInt32 s = _mfGlObjectStatus.size(); s <= id; s++)
            _mfGlObjectStatus.push_back( notused );
    }
    
    switch ( _mfGlObjectStatus[id] ) 
    {
    case notused:    // not used yet, no need to refresh
    case destroy:
    case finaldestroy:  // object is being destroyed, ignore refresh
        break;
    case initialize:    // can't happen, internal temporal state
        SWARNING << "Window::reinitializeGLObject: id " << id
                 << " in state initialize ?!?!" << endl;
        return;
    case needrefresh: // already needing refresh, switch to reinitialize
    case reinitialize:// already needing reinitialize
    case initialized:
        {
        WindowPtr win = WindowPtr(*this);
        beginEditCP(win, GlObjectStatusFieldMask|
                         GlObjectLastReinitializeFieldMask);
                         
        _mfGlObjectStatus[id] = reinitialize;
        
        UInt32 s = _mfGlObjectLastReinitialize.size();
        while ( s <= id ) 
        {
            _mfGlObjectLastReinitialize.push_back(0);
            s = s + 1;
        }
        
        UInt32 lastinv = getGlObjectInvalidateCounter() + 1;
        _mfGlObjectLastReinitialize[id] = lastinv;
        setGlObjectInvalidateCounter(lastinv);
        
        endEditCP  (win, GlObjectStatusFieldMask|
                         GlObjectLastReinitializeFieldMask);
        }
        break;
    default:
        SWARNING << "Window::reinitializeGLObject: id " << id
                 << " in state " << _mfGlObjectStatus[id] << "?!?!" << endl;
        return;
    }
}

void Window::destroyGLObject ( UInt32 id, UInt32 num )
{
    _glObjectDestroyList.push_back( id );
    _glObjectDestroyList.push_back( num );
}

void Window::dumpExtensions ( void )
{   
    vector<IDString>::iterator it;
    cout << "GL Extensions: ";
    for ( it = _extensions.begin(); it != _extensions.end(); it++ )
    {
        cout << it->str() << ", ";
    }
    cout << endl;       
}

void Window::frameInit( void )
{
    // any new extension registered ? 
    while ( _registeredExtensions.size() > _availExtensions.size() )
    {                           
        /* perform a binary search over the retrieved extension strings.
           Push back the result as an availability flag for the extension
           requested by the application */         
        _availExtensions.push_back( binary_search( 
                       _extensions.begin(),
                       _extensions.end(),
                       IDString(_registeredExtensions[_availExtensions.size()]) ) );
    }
    
    while ( _registeredFunctions.size() > _extFunctions.size() )
    {   
        const Char8 *s = _registeredFunctions[_extFunctions.size()].str();
        void *func     = (void*)getFunctionByName(s);
                        
        _extFunctions.push_back(func);
    }

}

void Window::frameExit( void )
{   
    if ( _glObjectDestroyList.size() > 0 )
    {
        UInt32 i;
        i = _glObjectDestroyList[ _glObjectDestroyList.size()-2 ] ;

        UInt32 rc = _glObjects[ i ]->getRefCounter();

        if ( _mfGlObjectStatus[ i ] == initialized ) 
        {           
        
            _mfGlObjectStatus[ i ] = destroy;
            _glObjects[ i ]->getFunctor().call( this, i );          

            if ( ! ( rc = _glObjects[ i ]->decRefCounter() )  )
            {           
                // call functor with the final-flag
                _mfGlObjectStatus[ i ] = finaldestroy;
                _glObjects[ i ]->getFunctor().call( this, i );
            }

            _mfGlObjectStatus[ i ] = notused;           
        }

        // if the GLObject is removed from each GL-Context, free GLObject-IDs.

        if ( ! rc )
        {
            delete _glObjects[ i ];
            for ( UInt32 j = 0; j < (*(_glObjectDestroyList.end()-1)) ; j++)
            {
                _glObjects[i+j] = NULL;
            }   
            _glObjectDestroyList.pop_back(); 
            _glObjectDestroyList.pop_back();
        }
    }
}

void Window::setupGL ( void )
{   
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
    glPixelStorei( GL_PACK_ALIGNMENT, 1 );
    
    glDepthFunc( GL_LEQUAL );
    glEnable( GL_DEPTH_TEST );

    // get extensions and split it
    IDString s((const Char8 *) glGetString(GL_EXTENSIONS));
    s.tokenize( _extensions );
    sort( _extensions.begin(), _extensions.end() );
}

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

    
void Window::draw( DrawAction * action )
{
    activate();
    frameInit();    // query recently registered GL extensions
    
    resizeGL();

    drawAllViewports( action );

    swap();
    frameExit();    // after frame cleanup: delete GL objects, if needed
}

void Window::drawAllViewports( DrawAction * action )
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
        SWARNING << "Window::drawAllViewports: no action!" << endl;
    }
}
    
void Window::render( RenderAction * action )
{
    activate();
    frameInit();    // query recently registered GL extensions
    
//  resizeGL();

    renderAllViewports( action );

    swap();
    frameExit();    // after frame cleanup: delete GL objects, if needed
}
    
void Window::renderAllViewports( RenderAction * action )
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
        SWARNING << "Window::renderAllViewports: no action!" << endl;
    }
}
    
void Window::resize( int width, int height )
{
    WindowPtr win(*this);
    beginEditCP(win, WidthFieldMask|HeightFieldMask|ResizePendingFieldMask);
    setWidth( width );
    setHeight( height );
    setResizePending( true );
    endEditCP  (win, WidthFieldMask|HeightFieldMask|ResizePendingFieldMask);
}
    
void Window::resizeGL( void )
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

Window& Window::operator = (const Window &source)
{
    if (this == &source)
        return *this;

    // copy 

    setWidth( source.getWidth() );
    setHeight( source.getHeight() );
    _mfPort.setValues( source._mfPort.getValues() );
    _mfGlObjectStatus.setValues( source._mfGlObjectStatus.getValues() );
    
    // mark all flags as notused, i.e. have to initialize on use
    for ( vector<UInt32>::iterator it = _mfGlObjectStatus.begin();
            it != _mfGlObjectStatus.end(); ++it )
        *it = notused;
    
    return *this;
}


/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void Window::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                  const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump Window NI" << endl;
}

    

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

