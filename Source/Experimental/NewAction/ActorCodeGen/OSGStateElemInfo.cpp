/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     * 
 *                                                                           * 
 *                                                                           * 
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                * 
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

#include <OSGConfig.h>
#include <OSGBaseTypes.h>
#include "OSGStateElemInfo.h"

#include <iostream>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::StateElemInfo

Stores all relevant information on one state element of an actor.
Currently these are: name, type, access, order.
Where name and type are strings, while access and order take values from
StateElemInfo::StateElemAccessE and StateElemInfo::StateElemOrderE
respectively.
Access allows you to make state elements protected in the generated base class
so that only your actor may use them.
Order describes wether this state element has to be save/restored on a not
depth first traversal.

*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*--------------------------- constructor ---------------------------------*/

StateElemInfo::StateElemInfo(const std::string      &name, 
                             const std::string      &type,
                             const std::string      &typeHeader,
                             const std::string      &defaultValue,
                                   StateElemAccessE  access,
                                   StateElemOrderE   order  )
  : _name        (name        ),
    _type        (type        ),
    _typeHeader  (typeHeader  ),
    _defaultValue(defaultValue),
    _access      (access      ),
    _order       (order       )
{
}

/*----------------------------- set & get ---------------------------------*/

void
StateElemInfo::setName(const std::string &name)
{
    _name = name;
}

const std::string &
StateElemInfo::getName(void) const
{
    return _name;
}

void
StateElemInfo::setType(const std::string &type)
{
    _type = type;
}

const std::string &
StateElemInfo::getType(void) const
{
    return _type;
}

void
StateElemInfo::setTypeHeader(const std::string &typeHeader)
{
    _typeHeader = typeHeader;
}

const std::string &
StateElemInfo::getTypeHeader(void) const
{
    return _typeHeader;
}

void
StateElemInfo::setDefaultValue(const std::string &defaultValue)
{
    _defaultValue = defaultValue;
}

const std::string &
StateElemInfo::getDefaultValue(void) const
{
    return _defaultValue;
}

void
StateElemInfo::setAccess(StateElemAccessE access)
{
    _access = access;
}

void
StateElemInfo::setAccess(const std::string &access)
{
    if(!mapAccessName(access, _access))
    {
        std::cerr << "StateElemInfo::setAccess: Error " << access
                  << " is not valid. Permissable values are: \"public\", "
                  << "\"protected\"." 
                  << std::endl;
    }
}

StateElemInfo::StateElemAccessE
StateElemInfo::getAccess(void) const
{
    return _access;
}

void
StateElemInfo::setOrder(StateElemOrderE order)
{
    _order = order;
}

void
StateElemInfo::setOrder(const std::string &order)
{
    if(!mapOrderName(order, _order))
    {
        std::cerr << "StateElemInfo::setOrder: Error " << order
                  << " is not valid. Permissable values are: \"true\", "
                  << "\"false\"."
                  << std::endl;
    }
}

StateElemInfo::StateElemOrderE
StateElemInfo::getOrder(void) const
{
    return _order;
}

bool
StateElemInfo::mapAccessName(const std::string      &access,
                                   StateElemAccessE &outVar )
{
    if(strcmp(access.c_str(), "public") == 0)
    {
        outVar = PublicAccess;
        
        return true;
    }
    else if(strcmp(access.c_str(), "protected") == 0)
    {
        outVar = ProtectedAccess;

        return true;
    }
    
    return false;
}

bool
StateElemInfo::mapOrderName(const std::string     &order,
                                  StateElemOrderE &outVar)
{
    if(strcmp(order.c_str(), "true") == 0)
    {
        outVar = Ordered;

        return true;
    }
    else if(strcmp(order.c_str(), "false") == 0)
    {
        outVar = Unordered;

        return true;
    }

    return false;
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp     [] = "@(#)$Id: OSGStateElemInfo.cpp,v 1.2 2003/10/10 14:27:45 neumannc Exp $";
    static Char8 cvsid_hpp     [] = OSGSTATEELEMINFO_HEADER_CVSID;
    static Char8 cvsid_inl     [] = OSGSTATEELEMINFO_INLINE_CVSID;
}


