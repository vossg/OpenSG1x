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

#include "OSGActorDesc.h"

#include <OpenSG/OSGLog.h>
#include "OSGActorStateElemDesc.h"

OSG_USING_NAMESPACE

/*------------------------------------------------------------------------*/
/*    Constructors                                                        */

ActorDesc::ActorDesc(void)
    : _actorName            (""                       ),
      _parentName           (""                       ),
      _libraryName          (""                       ),
      _useLocalIncludes     (false                    ),
      _systemComponent      (true                     ),
      _parentSystemComponent(true                     ),
      _enterFunctorStore    (ActorDescConstants::Empty),
      _leaveFunctorStore    (ActorDescConstants::Empty),
      _stateElems           (                         )
{
}

ActorDesc::ActorDesc(const std::string   &actorName,
                     const std::string   &parentName,
                     const std::string   &libraryName,
                           FunctorStoreE  enterFunctorStore,
                           FunctorStoreE  leaveFunctorStore,
                           bool           useLocalIncludes,
                           bool           systemComponent,
                           bool           parentSystemComponent)
    : _actorName            (actorName            ),
      _parentName           (parentName           ),
      _libraryName          (libraryName          ),
      _useLocalIncludes     (useLocalIncludes     ),
      _systemComponent      (systemComponent      ),
      _parentSystemComponent(parentSystemComponent),
      _enterFunctorStore    (enterFunctorStore    ),
      _leaveFunctorStore    (leaveFunctorStore    ),
      _stateElems           (                     )
{
}

/*------------------------------------------------------------------------*/
/*    Clear                                                               */

void
ActorDesc::clear(void)
{
    _actorName             = "";
    _parentName            = "";
    _libraryName           = "";
    _useLocalIncludes      = false;
    _systemComponent       = true;
    _parentSystemComponent = true;
    _enterFunctorStore     = ActorDescConstants::Empty;
    _leaveFunctorStore     = ActorDescConstants::Empty;

    _stateElems.clear();
}

void
ActorDesc::dump(void)
{
    SINFO << "ActorDesc Dunp:\n";
    PINFO << "  " << _actorName << "\n";
    PINFO << "  " << _parentName << "\n";
    PINFO << "  " << _libraryName << "\n";
    PINFO << "  " << _useLocalIncludes << "\n";
    PINFO << "  " << _systemComponent << "\n";
    PINFO << "  " << _parentSystemComponent << "\n";
    PINFO << "  " << getEnterFunctorStoreStr() << "\n";
    PINFO << "  " << getLeaveFunctorStoreStr() << "\n" << endLog;

    StateElemListIt itSE  = beginStateElems();
    StateElemListIt endSE = endStateElems  ();

    for(; itSE != endSE; ++itSE)
    {
        itSE->dump();
    }
}

/*------------------------------------------------------------------------*/
/*    Destructor                                                          */

ActorDesc::~ActorDesc(void)
{
}

/*------------------------------------------------------------------------*/
/*    Set / Get                                                           */

const std::string &
ActorDesc::getActorName(void) const
{
    return _actorName;
}

void
ActorDesc::setActorName(const std::string &actorName)
{
    _actorName = actorName;
}

const std::string &
ActorDesc::getParentName(void) const
{
    return _parentName;
}

void
ActorDesc::setParentName(const std::string &parentName)
{
    _parentName = parentName;
}

const std::string &
ActorDesc::getLibraryName(void) const
{
    return _libraryName;
}

void
ActorDesc::setLibraryName(const std::string &libraryName)
{
    _libraryName = libraryName;
}

bool
ActorDesc::getUseLocalIncludes(void) const
{
    return _useLocalIncludes;
}

std::string
ActorDesc::getUseLocalIncludesStr(void) const
{
    return ActorDescConstants::boolToStr(_useLocalIncludes);
}

void
ActorDesc::setUseLocalIncludes(bool useLocalIncludes)
{
    _useLocalIncludes = useLocalIncludes;
}

void
ActorDesc::setUseLocalIncludes(const std::string &useLocalIncludes)
{
    bool success = false;
    bool value   = ActorDescConstants::strToBool(useLocalIncludes, success);

    if(success == true)
    {
        _useLocalIncludes = value;
    }
    else
    {
        SWARNING << "ActorDesc::setUseLocalIncludes: unknown value: "
                 << useLocalIncludes << ". "
                 << "expecting \"true\" or \"false\"."
                 << endLog;
    }
}

bool
ActorDesc::getSystemComponent(void) const
{
    return _systemComponent;
}

std::string
ActorDesc::getSystemComponentStr(void) const
{
    return ActorDescConstants::boolToStr(_systemComponent);
}

void
ActorDesc::setSystemComponent(bool systemComponent)
{
    _systemComponent = systemComponent;
}

void
ActorDesc::setSystemComponent(const std::string &systemComponent)
{
    bool success = false;
    bool value   = ActorDescConstants::strToBool(systemComponent, success);

    if(success == true)
    {
        _systemComponent = value;
    }
    else
    {
        SWARNING << "ActorDesc::setSystemComponent: unknown value: "
                 << systemComponent << ". "
                 << "expecting \"true\" or \"false\"."
                 << endLog;
    }
}

bool
ActorDesc::getParentSystemComponent(void) const
{
    return _parentSystemComponent;
}

std::string
ActorDesc::getParentSystemComponentStr(void) const
{
    return ActorDescConstants::boolToStr(_parentSystemComponent);
}

void
ActorDesc::setParentSystemComponent(bool parentSystemComponent)
{
    _parentSystemComponent = parentSystemComponent;
}

void
ActorDesc::setParentSystemComponent(const std::string &parentSystemComponent)
{
    bool success = false;
    bool value   = ActorDescConstants::strToBool(parentSystemComponent, success);

    if(success == true)
    {
        _parentSystemComponent = value;
    }
    else
    {
        SWARNING << "ActorDesc::setSystemComponent: unknown value: "
                 << parentSystemComponent << ". "
                 << "expecting \"true\" or \"false\"."
                 << endLog;
    }
}


ActorDesc::FunctorStoreE
ActorDesc::getEnterFunctorStore(void) const
{
    return _enterFunctorStore;
}

std::string
ActorDesc::getEnterFunctorStoreStr(void) const
{
    return ActorDescConstants::functorStoreToStr(_enterFunctorStore);
}

void
ActorDesc::setEnterFunctorStore(FunctorStoreE enterFunctorStore)
{
    _enterFunctorStore = enterFunctorStore;
}

void
ActorDesc::setEnterFunctorStore(const std::string &enterFunctorStore)
{
    bool          success = false;
    FunctorStoreE value   = ActorDescConstants::strToFunctorStore(
                                enterFunctorStore, success);

    if(success == true)
    {
        _enterFunctorStore = value;
    }
    else
    {
        SWARNING << "ActorDesc::setEnterFunctorStore: unknown value: "
                 << enterFunctorStore << ". "
                 << "expecting \"Empty\", \"Simple\", \"Single\" or \"Multi\"."
                 << endLog;
    }
}

ActorDesc::FunctorStoreE
ActorDesc::getLeaveFunctorStore(void) const
{
    return _leaveFunctorStore;
}

std::string
ActorDesc::getLeaveFunctorStoreStr(void) const
{
    return ActorDescConstants::functorStoreToStr(_leaveFunctorStore);
}

void
ActorDesc::setLeaveFunctorStore(FunctorStoreE leaveFunctorStore)
{
    _leaveFunctorStore = leaveFunctorStore;
}

void
ActorDesc::setLeaveFunctorStore(const std::string &leaveFunctorStore)
{
    bool          success = false;
    FunctorStoreE value   = ActorDescConstants::strToFunctorStore(
                                leaveFunctorStore, success);

    if(success == true)
    {
        _leaveFunctorStore = value;
    }
    else
    {
        SWARNING << "ActorDesc::setLeaveFunctorStore: unknown value: "
                 << leaveFunctorStore << ". "
                 << "expecting \"Empty\", \"Simple\", \"Single\" or \"Multi\"."
                 << endLog;
    }
}

/*------------------------------------------------------------------------*/
/*    State Element Access                                                */

ActorDesc::StateElemListConstIt
ActorDesc::beginStateElems(void) const
{
    return _stateElems.begin();
}

ActorDesc::StateElemListIt
ActorDesc::beginStateElems(void)
{
    return _stateElems.begin();
}

ActorDesc::StateElemListConstIt
ActorDesc::endStateElems(void) const
{
    return _stateElems.end();
}

ActorDesc::StateElemListIt
ActorDesc::endStateElems(void)
{
    return _stateElems.end();
}

const ActorDesc::StateElemList &
ActorDesc::getStateElemList(void) const
{
    return _stateElems;
}

ActorDesc::StateElemList &
ActorDesc::getStateElemList(void)
{
    return _stateElems;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGActorDesc.cpp,v 1.1 2004/04/20 13:06:50 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGACTORDESC_HEADER_CVSID;
//    static Char8 cvsid_inl       [] = OSGACTORDESC_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
