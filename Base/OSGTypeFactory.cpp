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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGTypeFactory.h"

#include <OSGLog.h>
#include <OSGTypeBase.h>

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGTYPEFACTORY_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*! \class osg::TypeFactory
 */

TypeFactory *TypeFactory::_the = NULL;

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

TypeFactory *TypeFactory::the(void)
{
    if(_the == NULL)
        _the = new TypeFactory;

    return _the;
}

/*-------------------------------------------------------------------------*/
/*                              Type Info                                  */

UInt32 TypeFactory::findTypeStatic(const Char8 *szName)
{
    TypeNameMapCnstIt  typeIt;
    UInt32             uiTypeId = 0;

    typeIt   = _mTypeNameMap.find(IDStringLink(szName));
    uiTypeId = (typeIt == _mTypeNameMap.end()) ? 0 : (*typeIt).second;

    return uiTypeId;
}

UInt32 TypeFactory::registerType(TypeBase *pType)
{
    UInt32 returnValue = 0;

    if(pType == NULL)
    {
        SWARNING << "no data store given" << endl;

        return returnValue;
    }

    if(pType->getName().isEmpty() == true)
    {
        SWARNING << "OSGDataElementType without name" << endl;

        return returnValue;
    }

    if(findTypeStatic(pType->getCName()) != 0)
    {
        SWARNING << "ERROR: Can't add a second "
                 << "type with the name " << pType->getCName() << endl;

        return returnValue;
    }

    returnValue = _mTypeNameMap.size() + 1;

    _mTypeNameMap[IDStringLink(pType->getCName())] = returnValue;

    FDEBUG (("Registered type %s | %d\n", pType->getCName(), returnValue));

    return returnValue;
}

UInt32 TypeFactory::getNumTypes(void)
{
    return _mTypeNameMap.size() + 1;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

TypeFactory::TypeFactory(void) :
    _mTypeNameMap()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

TypeFactory::~TypeFactory(void)
{
}
