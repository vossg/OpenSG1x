/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000,2001 by OpenSG Forum                   *
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
inline void Window::setSize( UInt16 width, UInt16 height )
{
    setHeight( height );
    setWidth( width );
}

inline Bool Window::isResizePending ( void )
{
    return _sfResizePending.getValue();
}

/** GL extension stuff **/
inline UInt32 Window::registerExtension( const Char8 *s )
{
    if(s == NULL)
        return TypeConstants<UInt32>::getMax();
    UInt32 r = _registeredExtensions.size();
    _registeredExtensions.push_back( IDStringLink(s) );
    return ( r );
}

inline UInt32 Window::registerFunction( const Char8 *s )
{
    if(s == NULL)
        return TypeConstants<UInt32>::getMax();
    UInt32 r = _registeredFunctions.size();
    _registeredFunctions.push_back( IDStringLink(s) );
    return r;
}

/** check if the window has the indicated extension
\warning No error checks are done on the passed index!
*/
inline Bool Window::hasExtension( UInt32 id )
{
    return _availExtensions[ id ];
}

/** get the indicated extension function
The id and the returned functions are checked for sanity and a warning is
issued if there are problems. Use getFunctionNoCheck if you're sure
you don't need them.
*/
inline void* Window::getFunction ( UInt32 id )
{
    if(id >= _extFunctions.size())
    {
        FWARNING(("Window::getFunction: illegal id %d!\n", id));
        return NULL;
    }
    if(_extFunctions[id] == NULL)
    {
        FWARNING(("Window::getFunction: function \"%s\" is NULL!\n", 
                    _registeredFunctions[id].str()));
        return NULL;       
    }
    return _extFunctions[id];
}

/** get the indicated extension function
\warning No error checks are done on the passed index nor on the returned 
function!
*/
inline void* Window::getFunctionNoCheck( UInt32 id )
{
    return _extFunctions[ id ];
}

/** check the status of the indicated object 
\warning No error checks are done on the passed index!
*/
inline Window::GLObjectStatusE Window::getGLObjectStatus ( UInt32 id )
{
    return (GLObjectStatusE)_mfGlObjectStatus[ id ];
}


OSG_END_NAMESPACE

