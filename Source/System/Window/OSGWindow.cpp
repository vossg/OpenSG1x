/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#if defined(__sun)
#include <dlfcn.h>
#include <link.h>
#endif

#include <OSGDrawAction.h>
#include <OSGRenderActionBase.h>
#include "OSGViewport.h"

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

/*! \class osg::Window
    \ingroup GrpSystemWindow

Window is the base class for all window management classes.  See \ref
PageSystemWindowWindow for a description.

\ext

To create a new Window the methods that have to be overridden are init(void), 
activate(void), deactivate(void) and swap(void).

\endext 

*/

// Window-sytem specific virtual functions

/*! \fn void osg::Window::init(void)

    Initialize the Window and its OpenGL context. This method needs to be
    called once after the Window has been created and its Window
    System-specific parameters are set.  
    
    It leaves the OpenGL context current to simplify modifying the OpenGL
    state. 
*/

/*! \fn void osg::Window::activate(void)

    Activate the Window's OpenGL context, so that OpenGL can be called. 
*/

/*! \fn void osg::Window::deactivate(void)

    Deativate the Window's OpenGL context. OpenGL calls are no longer possible
    after this call.
*/

/*! \fn void osg::Window::swap(void)

    Swap the back and front buffers. 
    
    \warning The correct OpenGL context needs to be active for this to work!
*/

// only needed in dev docs

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

/*! \enum osg::Window::GLObjectStatusE
    Enumeration values for the status of the GL objects. This is primarily
    used to signal the object's callback functions what to do. See \ref
    PageSystemOGLObjects for a description.
*/

/*! \var osg::Window::GLObjectStatusE Window::notused
    Object is not used at all right now.
*/

/*! \var osg::Window::GLObjectStatusE Window::initialize
    The object is being initialized for the first time.
*/

/*! \var osg::Window::GLObjectStatusE Window::reinitialize
    The object is being re-initialized, i.e. it has changed significantly.
*/

/*! \var osg::Window::GLObjectStatusE Window::initialized
    The object is initialized and valid.
*/

/*! \var osg::Window::GLObjectStatusE Window::needrefresh
    The object is initialized but needs a refresh.
*/

/*! \var osg::Window::GLObjectStatusE Window::destroy
    The object is to be destroyed, i.e. removed from the current OpenGL context.
*/

/*! \var osg::Window::GLObjectStatusE Window::finaldestroy
    The object has been removed from all OpenGL contexts and used ressources
    but be freed now.
*/

/*! \enum osg::Window::invalidExtensionID
*/

/*! \enum osg::Window::invalidFunctionID
*/

/*! \enum osg::Window::statusShift
    Shift value to transform object id and status into  asingle int.
*/

/*! \enum osg::Window::statusMask
    Mask value to transform object id and status into  asingle int.
*/

/*! \class osg::Window::GLObject
    \ingroup GrpSystemWindow

The GLObject class is used to keep track of the OpenGL objects registered with 
the system. See \ref PageSystemOGLObjects for a description.

*/

#endif

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/*! The global window list, needed by Window::refreshGLObject. All Windows are 
added here at creation time and removed at deletion. 
*/
std::vector<WindowPtr              >  OSG::Window::_allWindows;
UInt32                                OSG::Window::_currentWindowId = 0;
// GLobject handling

/*! The lock used to mutex access of the GLObjects' reference count. One should 
be enough for all of them, as they are pretty rarely changed, only when they are 
used for the first time.
*/
Lock                                 *OSG::Window::_GLObjectLock;

/*! Global list of all GL Objects used in the system. See \ref
PageSystemOGLObjects for a description.
*/ 
std::vector<OSG::Window::GLObject *>  OSG::Window::_glObjects; 

/*! The objects currently being destroyed.
*/
std::list<std::pair<UInt32,UInt32> >  OSG::Window::_glObjectDestroyList;

// GL extension handling

std::vector<std::string            >  OSG::Window::_registeredExtensions;
std::vector<std::string            >  OSG::Window::_registeredFunctions;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*! initialize the static features of the class, e.g. action callbacks
*/

void OSG::Window::initMethod (void)
{
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

/*! Constructor
*/

OSG::Window::Window(void) :
     Inherited( ),
    _windowId (0)
{
    // only called for prototypes, no need to init them
}

/*! Copy Constructor
*/

OSG::Window::Window(const Window &source) :
    Inherited(source), 
    _lastValidate(source._lastValidate.size(),0),
    _extensions(),
    _availExtensions(),
    _extFunctions(),
    _windowId(0)
{       
    // mark all GL objects as not yet initialized
    doInitRegisterGLObject(1, _glObjects.size() - 1);
}

/*! Destructor
*/

OSG::Window::~Window(void)
{
    // delete the ports and the context
}


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*! Instance initialisation
*/

void OSG::Window::onCreate( const Window * )
{
    // Don't add the prototype instances to the list
    if(GlobalSystemState != Running)
        return;
        
    _allWindows.push_back(WindowPtr(this)); 

    _windowId = ++_currentWindowId;
}

void OSG::Window::onCreateAspect(const FieldContainer *source)
{
    // Don't add the prototype instances to the list
    if(GlobalSystemState != Running)
        return;

    _windowId = _currentWindowId;
}

/*! instance deletion
*/

void OSG::Window::onDestroy(void)
{
    std::vector<WindowPtr>::iterator it;

    it = std::find(_allWindows.begin(), _allWindows.end(), WindowPtr(this));
    
    // prototype windowa re not added to the list, so they might not be found.
    if(it != _allWindows.end()) 
        _allWindows.erase( it );
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*! react to field changes
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


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_EXT)

/*------------------------ GL object handling -----------------------------*/

/*! Register a number of OpenGL objects. By default the number is 1, but more
    can be necessary for things like text. It returns the first id of the
    contiguous reserved ID block.

    See \ref PageSystemOGLObjects for a description of the OpenGL object
    concept. 
*/

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

/*! Validate the given object, i.e. make sure it is up-to-date in the current
    context.

    See \ref PageSystemOGLObjects for a description of the OpenGL object
    concept. 
*/
void OSG::Window::validateGLObject(UInt32 id)
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

/*! Mark the given object for refresh. The next time it is validated the
    registered callback function will be called for a refresh action.

    See \ref PageSystemOGLObjects for a description of the OpenGL object
    concept. 
*/
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

/*! Mark the given object for reinitialisation. The next time it is validated the
    registered callback function will be called for a reinit action.

    See \ref PageSystemOGLObjects for a description of the OpenGL object
    concept. 
*/
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

/*! Initialize the GL object registration for the given objects in all
    Windows.

    See \ref PageSystemOGLObjects for a description of the OpenGL object
    concept. 
*/
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

/*! Initialize the GL object registration for the given objects in the given
    Window.

    See \ref PageSystemOGLObjects for a description of the OpenGL object
    concept. 
*/
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

/*! Mark the given objects for destruction. The actual destruction will happen
    later.

    See \ref PageSystemOGLObjects for a description of the OpenGL object
    concept. 
*/
void OSG::Window::destroyGLObject(UInt32 id, UInt32 num)
{
    _glObjectDestroyList.push_back(DestroyEntry(id,num));
}


/*----------------------- GL extension handling ---------------------------*/


/*! Register a new OpenGL extension. See \ref PageSystemOGLExt for details. 
    Ignores NULL strings. 
*/
UInt32 OSG::Window::registerExtension(const Char8 *s)
{
    if(s == NULL)
        return TypeTraits<UInt32>::getMax();
    
    std::vector<std::string>::iterator i;
    
    i = std::find(_registeredExtensions.begin(), _registeredExtensions.end(), 
                  s);
    
    if(i < _registeredExtensions.end())
        return i - _registeredExtensions.begin();
        
    UInt32 r = _registeredExtensions.size();
    _registeredExtensions.push_back(s);
    return r;
}

/*! Register a new OpenGL extension function. See \ref PageSystemOGLExt for 
    details. Ignores NULL strings.
*/
UInt32 OSG::Window::registerFunction(const Char8 *s)
{
    if(s == NULL)
        return TypeTraits<UInt32>::getMax();
    
    std::vector<std::string>::iterator i;
    
    i = std::find(_registeredFunctions.begin(), _registeredFunctions.end(), 
                  s);
    
    if(i < _registeredFunctions.end())
        return i - _registeredFunctions.begin();
        
    UInt32 r=_registeredFunctions.size();
    _registeredFunctions.push_back(s);
    return r;
}

#endif // remove the OpenGL object handling from user docs

/*! Dump all the registered extensions to std::cout.

    See \ref PageSystemOGLObjects for a description of the OpenGL object
    concept. 
*/
void OSG::Window::dumpExtensions(void)
{   
    std::vector<std::string>::iterator it;
    std::cout << "GL Extensions: ";
    for ( it = _extensions.begin(); it != _extensions.end(); it++ )
    {
        std::cout << it->c_str() << ", ";
    }
    std::cout << std::endl;       
}


/*! Do everything that needs to be done before the Window is redrawn. This
    function has to be called for every frame the Window is drawn. 
    
    The convenience functions render and draw take care of it, if they are
    used.
    
    The main task currently is checking and updating OpenGL extensions.
*/


// String tokenizer, by Daniel Andersson
// taken from http://www.codeproject.com/string/stringsplitter.asp

#include <string>
#include <iterator>

struct string_token_iterator : 
#if defined(__GNUC__) && __GNUC__ < 3
    public std::input_iterator<std::string, std::ptrdiff_t>
#else
    public std::iterator<std::input_iterator_tag, std::string>
#endif
{
  public:   
    string_token_iterator() : str(0), start(0), end(0) 
    {
    }
  
    string_token_iterator(const std::string & str_, 
                        const char *separator_ = " ") :
        separator(separator_),
        str(&str_),
        end(0)
    {
        find_next();
    }
  
    string_token_iterator(const string_token_iterator & rhs) :
        separator(rhs.separator),
        str(rhs.str),
        start(rhs.start),
        end(rhs.end)
    {
    }

    string_token_iterator & operator++()
    {
        find_next();
        return *this;
    }

    string_token_iterator operator++(int)
    {
        string_token_iterator temp(*this);
        ++(*this);
        return temp;
    }

    std::string operator*() const
    {
        return std::string(*str, start, end - start);
    }

    bool operator==(const string_token_iterator & rhs) const
    {
        return (rhs.str == str && rhs.start == start && rhs.end == end);
    }

    bool operator!=(const string_token_iterator & rhs) const
    {
        return !(rhs == *this);
    }

  private:

    void find_next(void)
    {
        start = str->find_first_not_of(separator, end);
        if(start == std::string::npos)
        {
            start = end = 0;
            str = 0;
            return;
        }

        end = str->find_first_of(separator, start);
    }

    const char * separator;
    const std::string * str;
    std::string::size_type start;
    std::string::size_type end;
};

void OSG::Window::frameInit(void)
{
    // get extensions and split them
    if(_extensions.empty())
    {
        FDEBUG(("Window %p: GL Extensions: %s\n", this, 
                glGetString(GL_EXTENSIONS) ));
        
        std::back_insert_iterator< std::vector<std::string> > 
            extension_front_inserter(_extensions);

        std::string foo(reinterpret_cast<const char*>
                        (glGetString(GL_EXTENSIONS)));


        std::copy(string_token_iterator(
                                foo,
                                ",. "),
                  string_token_iterator(),
                  extension_front_inserter);

        std::sort(_extensions.begin(), _extensions.end());
                 
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
                _registeredExtensions[_availExtensions.size()] ) );
    }

    // any new functions registered ? 
    while(_registeredFunctions.size() > _extFunctions.size())
    {   
        const Char8 *s    = _registeredFunctions[_extFunctions.size()].c_str();
        void        *func = (void*)getFunctionByName(s);

        _extFunctions.push_back(func);
    }
}

/*! Do everything that needs to be done after the Window is redrawn. This
    function has to be called for every frame the Window is drawn. 
    
    The convenience functions render and draw take care of it, if they are
    used.

    The main task currently is deleting OpenGL objects.
*/
void OSG::Window::frameExit(void)
{   
    std::list<DestroyEntry>::iterator st,en,del;

    st = _glObjectDestroyList.begin();
    en = _glObjectDestroyList.end  ();

    while(st != en)
    {
        UInt32 i = st->first, n = st->second;

        GLObject *obj = _glObjects[ i ];
        
        if(obj == NULL)
        {
            FDEBUG(("Window::frameExit: objects %d (%d) already destroyed?!?\n",
                    i, n));
            del = st;

            ++st;

            _glObjectDestroyList.erase(del);

            continue;
        }
           
        UInt32 rc = obj->getRefCounter();

        // has the object been used in this context at all?
        if(getGlObjectLastReinitialize()[i] != 0) 
        {                  
            _glObjects[i]->getFunctor().call( this, packIdStatus(i, destroy));

            if((rc = _glObjects[ i ]->decRefCounter()) <= 0)
            {           
                // call functor with the final-flag
                _glObjects[i]->getFunctor().call( this, 
                                                packIdStatus(i, finaldestroy));
            }
        }

        // if the GLObject is removed from each GL-Context, free GLObject-IDs.

        if(rc <= 0)
        {
            delete _glObjects[ i ];
            for ( UInt32 j = 0; j < n ; j++)
            {
                _glObjects[i+j] = NULL;
            }   

            del = st;

            ++st;

            _glObjectDestroyList.erase(del);
        }
        else
        {
            ++st;
        }
    }
}


// Query for a GL extension function
// Yes, this is system dependent, but the system dependent parts are 
// #ifdefed anyway, and very similar code would show up in a number of places,
// making maintaining it unnecessarily hard
// Note: the order of the cases is important, do not change it!

/*! Query OpenGL for the pointer to an extension function. 

    This is called internally when extension functions are first cached. 
*/

OSG::Window::GLExtensionFunction OSG::Window::getFunctionByName(
    const Char8 *s)
{
    GLExtensionFunction retval = NULL;

#if defined(GLX_VERSION_1_4)

    retval = glXGetProcAddress((const GLubyte *) s);

#elif defined(__hpux) || defined (__sgi) || defined(__sun)

    static void *libHandle = NULL;

    if(libHandle == NULL)
    {
        // HACK, but if we get here we link against libGL anyway
        libHandle = dlopen(NULL, RTLD_NOW | RTLD_GLOBAL);
        
        if(!libHandle)
        {
            FWARNING(("Error in dlopen: %s\n",dlerror()));
            abort();
        }
    }

    retval = reinterpret_cast<GLExtensionFunction>(dlsym(libHandle, s));

// UGLY HACK: SGI/NVidia header don't define GLX_ARB_get_proc_address,
// but they use __GLX_glx_h__ instead of GLX_H as an include guard.
// Grmbl. In the 40.x drivers the define is the standard now,
// but they still don't define GLX_ARB_get_proc_address... Test for an 
// NV-specific symbol instead...
#elif defined(GLX_ARB_get_proc_address) || defined(__GLX_glx_h__) || \
      defined(GLX_FLOAT_COMPONENTS_NV)

    retval = glXGetProcAddressARB((const GLubyte *) s);

#elif defined(darwin)

    static void *libHandle = NULL;

    if(libHandle == NULL)
    {
        libHandle = dlopen("libGL.dylib", RTLD_NOW);
    }

    retval = reinterpret_cast<GLExtensionFunction>(dlsym(libHandle, s));

#elif defined(WIN32)

    retval = (void(__cdecl*)(void)) wglGetProcAddress(s);

#else

    FWARNING(("Window::getFunctionByName: couldn't find implementation!\n"
              "Please contact the developers at info@opensg.org.\n");
    retval = NULL;

#endif

    if(retval == NULL)
    {
        FNOTICE(("Window::getFunctionByName: Couldn't get function '%s' for "
                 "Window %p.\n", s, this));
    }
    else
    {
        FDEBUG(("Window::getFunctionByName: got function '%s' for "
                 "Window %p at %p.\n", s, this, retval));
    }

    return retval;
}

/*! Initialize the OpenGL state OpenSG expects. This should be called once
    whenever a new Window is opened.
    
    Don't call it directly, call the Window System-specific init() method
    instead.
*/
void OSG::Window::setupGL( void )
{   
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
    glPixelStorei( GL_PACK_ALIGNMENT, 1 );
    
    glDepthFunc( GL_LEQUAL );
    glEnable( GL_DEPTH_TEST );
    
    glEnable( GL_NORMALIZE );
    
    // switch off default light
    GLfloat nul[4]={0,0,0,0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, nul);
    glLightfv(GL_LIGHT0, GL_SPECULAR, nul);
}

/*-------------------------- your_category---------------------------------*/

/*! Draw the Window using the given DrawAction. 

    It takes care of all initialisation and cleanup functions and contains just
    6 lines of code. If you know that the correct context is active or you want
    to delay swaps you can just copy and manipulate it.
*/   
void OSG::Window::draw(DrawAction * action)
{
    activate();
    frameInit();    // query recently registered GL extensions
    
    resizeGL();

    drawAllViewports(action);

    swap();
    frameExit();    // after frame cleanup: delete GL objects, if needed
}

/*! Draw all the Viewports of the Window using the given DrawAction. 

    A simple convenience function that loops all Viewports and call their draw
    method.
*/   
void OSG::Window::drawAllViewports(DrawAction * action)
{
    MFViewportPtr::iterator       portIt  = _mfPort.begin();
    MFViewportPtr::const_iterator portEnd = _mfPort.end();

    if(action != NULL)
    {
        action->setWindow(this);
        
        while(portIt != portEnd)
        {
            (*portIt)->draw(action);

            ++portIt;
        }
    }
    else
    {
        SWARNING << "Window::drawAllViewports: no action!" << std::endl;
    }
}
    
/*! Render the Window using the given RenderAction. 

    It takes care of all initialisation and cleanup functions and contains just
    5 lines of code. If you know that the correct context is active or you want
    to delay swaps you can just copy and manipulate it.
*/   
void OSG::Window::render(RenderActionBase *action)
{
    activate();
    frameInit();    // query recently registered GL extensions
    
//  resizeGL();

    renderAllViewports(action);

    swap();
    frameExit();    // after frame cleanup: delete GL objects, if needed
}
    

/*! Render all the Viewports of the Window using the given RenderAction. 

    A simple convenience function that loops all Viewports and call their draw
    method.
*/   
void OSG::Window::renderAllViewports(RenderActionBase *action)
{
    MFViewportPtr::iterator       portIt  = _mfPort.begin();
    MFViewportPtr::const_iterator portEnd = _mfPort.end();

    if(action != NULL)
    {
        action->setWindow(this);
        
        while(portIt != portEnd)
        {
            (*portIt)->render(action);
            ++portIt;
        }
    }
    else
    {
        SWARNING << "Window::renderAllViewports: no action!" << std::endl;
    }
}
    

/*! Resize notifier function. 

    As OpenSG does not do Window System event management it needs to be
    notified whenever the size of a Window changes. 
*/   
void OSG::Window::resize( int width, int height )
{
    WindowPtr win(*this);
    beginEditCP(win, WidthFieldMask|HeightFieldMask|ResizePendingFieldMask);
    setWidth( width );
    setHeight( height );
    setResizePending( true );
    endEditCP  (win, WidthFieldMask|HeightFieldMask|ResizePendingFieldMask);
}
    

/*! Resize function. 

    This function needs to be called before a Window's Viewports are rendered,
    to ensure that eventual pending resizes are handled correctly. 
*/   
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

/*! Assignment
*/

OSG::Window& OSG::Window::operator = (const OSG::Window &source)
{
    if(this == &source)
        return *this;

    // copy 

    setWidth(source.getWidth());
    setHeight(source.getHeight());
    _mfPort.setValues( source._mfPort.getValues() );
    
    // mark all GL objects as not yet initialized
    doInitRegisterGLObject(1, _glObjects.size() - 1);
    
    return *this;
}


/*------------------------------- dump ----------------------------------*/

/*! output the instance for debug purposes
*/
void OSG::Window::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                  const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump Window NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.13 2002/06/01 10:37:25 vossg Exp $";
    static Char8 cvsid_hpp       [] = OSGWINDOW_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGWINDOW_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGWINDOWFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

