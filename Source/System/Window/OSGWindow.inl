/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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


#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

OSG_BEGIN_NAMESPACE


/*------------------------------- size ----------------------------------*/
/*! Set the width and height of the Window. Only use if you really know what
    you're doing. In most cases resize() is a better choice.
*/
inline void Window::setSize(UInt16 width, UInt16 height)
{
    setHeight(height);
    setWidth(width);
}

inline bool Window::isResizePending(void)
{
    return _sfResizePending.getValue();
}

/*! Check if the window has the indicated extension.
    \warning No error checks are done on the passed index!
*/
inline bool Window::hasExtension(UInt32 id)
{
    return _availExtensions[id];
}

/*! Get the indicated extension function.
    The id and the returned functions are checked for sanity and a warning is
    issued if there are problems. Use getFunctionNoCheck if you're sure you
    don't need them.
*/
inline void* Window::getFunction(UInt32 id)
{
    if(id >= _extFunctions.size())
    {
        FINFO(("Window::getFunction: illegal id %d!\n", id));
        return NULL;
    }
    if(_extFunctions[id] == NULL)
    {
        FINFO(("Window::getFunction: function \"%s\" is NULL!\n", 
                    _registeredFunctions[id].c_str()));
        return NULL;       
    }
    return _extFunctions[id];
}

/*! Get the indicated extension function.
    \warning No error checks are done on the passed index nor on the returned 
    function!
*/
inline void* Window::getFunctionNoCheck(UInt32 id)
{
    return _extFunctions[ id ];
}

/*! Pack the id and the status into one UInt32. Used to pass the id and status 
    to the actual implementation functions.

\dev

This packing is not really necessary and just done because I didn't want to 
change all the prototypes and implementations everywhere. Do it for 1.3.

\enddev 
*/
inline UInt32 Window::packIdStatus(UInt32 id, GLObjectStatusE status)
{
    return (id << statusShift) | status;
}

/*! Unpack the id and the status from one UInt32 packed by packIdStatus
*/
inline void Window::unpackIdStatus(UInt32 idstatus, UInt32 &id, 
                                   GLObjectStatusE &status)
{
    id = idstatus >> statusShift;
    status = static_cast<GLObjectStatusE>(idstatus & statusMask);
}


/* GLObject helper class */
                                                               
inline Window::GLObject::GLObject( GLObjectFunctor funct ) :
            _functor(funct), 
            _refCounter(0), 
            _lastValidate(0)
{
}

inline Window::GLObjectFunctor& Window::GLObject::getFunctor(void) 
{ 
    return _functor; 
};

inline void Window::GLObject::setFunctor(GLObjectFunctor funct)
{
    _functor = funct;
};

inline UInt32 Window::GLObject::getLastValidate(void)
{
    return _lastValidate;
}

inline void Window::GLObject::setLastValidate(UInt32 val)
{
    _lastValidate = val;
}

inline UInt32 Window::GLObject::getRefCounter(void)
{
    return _refCounter;
}

inline UInt32 Window::GLObject::incRefCounter(void)
{
    UInt32 val;

    if ( ! _GLObjectLock )
    {
        _GLObjectLock = ThreadManager::the()->getLock(NULL);
    }

    _GLObjectLock->aquire();
    val = _refCounter = _refCounter + 1;
    _GLObjectLock->release();

    return val;
}

inline UInt32 Window::GLObject::decRefCounter(void)
{
    UInt32 val;

    if(! _GLObjectLock)
    {
        _GLObjectLock = ThreadManager::the()->getLock(NULL);
    }

    _GLObjectLock->aquire();
    if(_refCounter)
        val = _refCounter = _refCounter - 1;
    else
        val = 0;
    _GLObjectLock->release();

    return val; 
}

OSG_END_NAMESPACE


#define OSGWINDOW_INLINE_CVSID "@(#)$Id:$"
