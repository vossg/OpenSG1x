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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGTypeBase.h"
#include <OSGTypeFactory.h>

OSG_USING_NAMESPACE

/*! \class osg::TypeBase
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

TypeBase::TypeBase(const Char8 *szName,
                   const Char8 *szParentName,
                   const UInt32             ) :

    _uiTypeId    (0           ),
    _uiTypeRootId(0           ),
    _pParent     (NULL        ),
    _szName      (szName      ),
    _szParentName(szParentName)
{
    _uiTypeId = TypeFactory::the()->registerType(this);
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

TypeBase::~TypeBase(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

UInt32 TypeBase::getId(void) const 
{
    return _uiTypeId; 
}


const IDString &TypeBase::getName(void) const
{
    return _szName;
}


const Char8 *TypeBase::getCName(void) const 
{
    return _szName.str(); 
}


const IDString &TypeBase::getParentName(void) const
{
    return _szParentName;
}


const Char8  *TypeBase::getCParentName(void) const
{
    return _szParentName.str();
}


UInt32 TypeBase::getNameSpace(void) const
{
    return 0;
}


/*-------------------------------------------------------------------------*/
/*                                Is                                       */

bool TypeBase::isDerivedFrom(const TypeBase &OSG_CHECK_ARG(other)) const
{
    return false;
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

bool TypeBase::operator ==(const TypeBase &other) const
{
    return _uiTypeId == other._uiTypeId;
}


bool TypeBase::operator !=(const TypeBase &other) const
{
    return ! (*this == other);
}


/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

TypeBase::TypeBase(const TypeBase &source) :
    _uiTypeId    (source._uiTypeId),
    _uiTypeRootId(source._uiTypeRootId),
    _pParent     (source._pParent),
    _szName      (source._szName),
    _szParentName(source._szParentName)
{
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
    static Char8 cvsid_hpp[] = OSGTYPEBASE_HEADER_CVSID;
}
