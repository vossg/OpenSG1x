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

#include "OSGActorStateElemDesc.h"

#include <OpenSG/OSGLog.h>

OSG_USING_NAMESPACE

/*------------------------------------------------------------------------*/
/*    Constructors                                                        */

ActorStateElemDesc::ActorStateElemDesc(void)
    : _name        (""                        ),
      _type        (""                        ),
      _header      (""                        ),
      _defaultValue(""                        ),
      _access      (ActorDescConstants::Public),
      _hierarchical(false                     )
{
}

ActorStateElemDesc::ActorStateElemDesc(const std::string &name,
                                       const std::string &type,
                                             AccessE      access,
                                             bool         hierarchical,
                                       const std::string &header,
                                       const std::string &defaultValue  )
    : _name        (name        ),
      _type        (type        ),
      _header      (header      ),
      _defaultValue(defaultValue),
      _access      (access      ),
      _hierarchical(hierarchical)
{
}

/*------------------------------------------------------------------------*/
/*    Destructor                                                          */

ActorStateElemDesc::~ActorStateElemDesc(void)
{
}

/*------------------------------------------------------------------------*/
/*    Get / Set                                                           */

void
ActorStateElemDesc::dump(void)
{
    SINFO << "ActorStateElemDesc dump:\n";
    PINFO << "    " << _name << "\n";
    PINFO << "    " << _type << "\n";
    PINFO << "    " << _header << "\n";
    PINFO << "    " << _defaultValue << "\n";
    PINFO << "    " << getAccessStr() << "\n";
    PINFO << "    " << _hierarchical << "\n" << endLog;
}

const std::string &
ActorStateElemDesc::getName(void) const
{
    return _name;
}

void
ActorStateElemDesc::setName(const std::string &name)
{
    _name = name;
}

const std::string &
ActorStateElemDesc::getType(void) const
{
    return _type;
}

void
ActorStateElemDesc::setType(const std::string &type)
{
    _type = type;
}

ActorStateElemDesc::AccessE
ActorStateElemDesc::getAccess(void) const
{
    return _access;
}

std::string
ActorStateElemDesc::getAccessStr(void) const
{
    return ActorDescConstants::accessToStr(_access);
}

void
ActorStateElemDesc::setAccess(AccessE access)
{
    _access = access;
}

void
ActorStateElemDesc::setAccess(const std::string &access)
{
    bool    success = false;
    AccessE value   = ActorDescConstants::strToAccess(access, success);

    if(success == true)
    {
        _access = value;
    }
    else
    {
        SWARNING << "ActorStateElemDesc::setAccess: unknown value: "
                 << access << ". "
                 << "expecting \"public\" or \"protected\"."
                 << endLog;
    }
}

bool
ActorStateElemDesc::getHierarchical(void) const
{
    return _hierarchical;
}

std::string
ActorStateElemDesc::getHierarchicalStr(void) const
{
    return ActorDescConstants::boolToStr(_hierarchical);
}

void
ActorStateElemDesc::setHierarchical(bool hierarchical)
{
    _hierarchical = hierarchical;
}

void
ActorStateElemDesc::setHierarchical(const std::string &hierarchical)
{
    bool success = false;
    bool value   = ActorDescConstants::strToBool(hierarchical, success);

    if(success == true)
    {
        _hierarchical = value;
    }
    else
    {
        SWARNING << "ActorStateElemDesc::setHierarchical: unknown value: "
                 << hierarchical << ". "
                 << "expecting \"true\" or \"false\"."
                 << endLog;
    }
}

const std::string &
ActorStateElemDesc::getHeader(void) const
{
    return _header;
}

void
ActorStateElemDesc::setHeader(const std::string &header)
{
    _header = header;
}

const std::string &
ActorStateElemDesc::getDefaultValue(void) const
{
    return _defaultValue;
}

void
ActorStateElemDesc::setDefaultValue(const std::string &defaultValue)
{
    _defaultValue = defaultValue;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGActorStateElemDesc.cpp,v 1.1 2004/04/20 13:06:50 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGACTORSTATEELEMDESC_HEADER_CVSID;
//    static Char8 cvsid_inl       [] = OSGACTORSTATEELEMDESC_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
