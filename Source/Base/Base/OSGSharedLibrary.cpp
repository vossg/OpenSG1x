/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000-2002,2002 by the OpenSG Forum                *
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


#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#ifndef OSG_DISABLE_DEPRECATED

#include "OSGSharedLibrary.h"
#include "OSGBaseFunctions.h"

#ifndef WIN32
#include <dlfcn.h>
#endif

#define OSG_DLOPEN_LAZY

OSG_USING_NAMESPACE

Char8 SharedLibrary::_szApplicationName[] = "Application";


/*--------------------------- Constructors --------------------------------*/

SharedLibrary::SharedLibrary(void) :
    _szName (NULL   ),
    _pHandle(NULL   ),
    _type   (Invalid)
{
}

SharedLibrary::SharedLibrary(const Char8 *szName) :
    _szName (NULL   ),
    _pHandle(NULL   ),
    _type   (Invalid)
{
    if(szName == NULL)
    {
        stringDup(_szApplicationName, _szName);

        _type = Application;
    }
    else
    {
        stringDup(szName, _szName);

        _type = SharedLib;
    }    

    this->open();
}

/*---------------------------- Destructor ---------------------------------*/

SharedLibrary::~SharedLibrary(void)
{
    close();
}

/*---------------------------- Class Specific -----------------------------*/

bool SharedLibrary::open(const Char8 *szName)
{
    if(isOpen() == true)
    {
        close();
    }

    if(szName == NULL)
    {
        stringDup(_szApplicationName, _szName);

        _type = Application;
    }
    else
    {
        stringDup(szName, _szName);

        _type = SharedLib;
    }    

    return this->open();
}

bool SharedLibrary::close(void)
{
    bool returnValue = false;

    if(_pHandle != NULL)
    {
#ifndef WIN32
        returnValue = (dlclose(_pHandle) == 0);
#else
        returnValue = (FreeLibrary(_pHandle)) != FALSE;
#endif
        _pHandle    = NULL;
    }

    return returnValue;
}

AnonSymbolHandle SharedLibrary::getSymbol(const Char8 *szSymbolName)
{
    AnonSymbolHandle returnValue = NULL;

    if(isOpen() == false)
    {
        if(open() == false)
        {
            return returnValue;
        }
    }

    if(_pHandle != NULL && szSymbolName != NULL)
    {
#ifndef WIN32
        returnValue = dlsym(_pHandle, szSymbolName);
#else
        returnValue = (void*)GetProcAddress(_pHandle, szSymbolName);
#endif
    }

#ifndef WIN32
    if(returnValue == NULL)
        fprintf(stderr, "%s\n", dlerror());
#else
#endif

    fprintf(stderr, "Got Symbol : %s %p %p\n", 
            szSymbolName, 
            _pHandle, 
            returnValue);

    return returnValue;
}

bool SharedLibrary::isOpen(void)
{
    return _pHandle != NULL;
}

const Char8 *SharedLibrary::getName(void)
{
    return _szName;
}

/*------------------------------- Helper ----------------------------------*/

bool SharedLibrary::open(void)
{
    Char8 *libName = NULL;

    if(_pHandle != NULL)
    {
        return true;
    }

    if(_type == SharedLib)
    {
        libName = _szName;
    }

#ifndef WIN32
#ifdef OSG_DLOPEN_LAZY
    _pHandle = dlopen(libName, RTLD_LAZY | RTLD_GLOBAL);
#else
    _pHandle = dlopen(libName, RTLD_NOW  | RTLD_GLOBAL);
#endif

    if(_pHandle == NULL)
    {
        fprintf(stderr, "%s\n", dlerror());
    }
#else
    _pHandle = LoadLibrary(libName);
#endif

    return (_pHandle != NULL);
}

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGSHAREDLIBRARY_HEADER_CVSID;
}

#endif
