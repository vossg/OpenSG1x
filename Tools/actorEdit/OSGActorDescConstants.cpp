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

#include "OSGActorDescConstants.h"
#include <OpenSG/OSGBaseFunctions.h>

OSG_USING_NAMESPACE

/*------------------------------------------------------------------------*/
/*    To / From String                                                    */

bool
ActorDescConstants::strToBool(const std::string &strIn, bool &success)
{
    bool retValue = false;

    if(stringcasecmp(strIn.c_str(), "true") == 0)
    {
        success  = true;
        retValue = true;
    }
    else if(stringcasecmp(strIn.c_str(), "false") == 0)
    {
        success  = true;
        retValue = false;
    }
    else
    {
        success = false;
    }

    return retValue;
}

std::string
ActorDescConstants::boolToStr(bool value)
{
    if(value == true)
    {
        return "true";
    }
    else
    {
        return "false";
    }
}

ActorDescConstants::FunctorStoreE
ActorDescConstants::strToFunctorStore(const std::string &strIn, bool &success)
{
    FunctorStoreE retValue = Empty;

    if(stringcasecmp(strIn.c_str(), "empty") == 0)
    {
        success  = true;
        retValue = Empty;
    }
    else if(stringcasecmp(strIn.c_str(), "simple") == 0)
    {
        success  = true;
        retValue = Simple;
    }
    else if(stringcasecmp(strIn.c_str(), "single") == 0)
    {
        success  = true;
        retValue = Single;
    }
    else if(stringcasecmp(strIn.c_str(), "multi") == 0)
    {
        success  = true;
        retValue = Multi;
    }
    else
    {
        success = false;
    }

    return retValue;
}

std::string
ActorDescConstants::functorStoreToStr(FunctorStoreE value)
{
    std::string retValue;

    switch(value)
    {
    case ActorDescConstants::Empty:
        retValue = "Empty";
        break;

    case ActorDescConstants::Simple:
        retValue = "Simple";
        break;

    case ActorDescConstants::Single:
        retValue = "Single";
        break;

    case ActorDescConstants::Multi:
        retValue = "Multi";
        break;
    };

    return retValue;
}

ActorDescConstants::AccessE
ActorDescConstants::strToAccess(const std::string &strIn, bool &success)
{
    AccessE retValue = Public;

    if(stringcasecmp(strIn.c_str(), "public") == 0)
    {
        success  = true;
        retValue = Public;
    }
    else if(stringcasecmp(strIn.c_str(), "protected") == 0)
    {
        success  = true;
        retValue = Protected;
    }
    else
    {
        success  = false;
    }

    return retValue;
}

std::string
ActorDescConstants::accessToStr(AccessE access)
{
    std::string retValue;

    switch(access)
    {
    case ActorDescConstants::Public:
        retValue = "public";
        break;

    case ActorDescConstants::Protected:
        retValue = "protected";
        break;
    };

    return retValue;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGActorDescConstants.cpp,v 1.1 2004/04/20 13:06:50 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGACTORDESCCONSTANTS_HEADER_CVSID;
//    static Char8 cvsid_inl       [] = OSGACTORDESCCONSTANTS_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
