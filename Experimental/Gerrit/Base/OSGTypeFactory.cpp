/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#include <iostream>

#include "OSGTypeFactory.h"
#include <OSGFactoryController.h>

#include <OSGLog.h>
#include <OSGTypeBase.h>

#include <algorithm>
#include <functional>

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

TypeFactory *TypeFactory::_the = NULL;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

void TypeFactory::writeTypeDot(FILE     *pOut,
                               TypeBase *pTypeBase)
{
    fprintf(pOut, "    %s [shape=box]\n", pTypeBase->getCName());

    if(pTypeBase->getCParentName() != NULL)
    {
        fprintf(pOut, 
                "    %s -> %s\n", 
                pTypeBase->getCParentName(), 
                pTypeBase->getCName());
    }
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


TypeFactory *TypeFactory::the(void)
{
    if(_the == NULL)
        _the = new TypeFactory("TypeFactory");

    return _the;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

TypeFactory::TypeFactory(const Char8 *szName) :
     Inherited    (szName),
    _vTypeNameMaps(),
    _vTypeStore   ()
{
    _vTypeStore.reserve  (512 );
    _vTypeStore.push_back(NULL);

    _vTypeNameMaps.push_back(new TypeNameMap);

    FactoryController::the()->registerTypeFactory(this);
}


TypeFactory::~TypeFactory(void)
{
}

bool TypeFactory::initialize(void)
{
    return true;
}

bool TypeFactory::terminate(void)
{
    return true;
}

bool TypeFactory::onLoadInitialize(void)
{
    return true;
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

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
		SWARNING << "DataElementType without name" << endl;

		return returnValue;
	}

    UInt32 uiTypeId = findTypeId(pType->getCName    (), 
                                 pType->getNameSpace());

    if(uiTypeId != 0)
    {
        if(pType != findType(uiTypeId))
        {
            SWARNING << "ERROR: Can't add a second "
                     << "type with the name " << pType->getCName() 
                     << "(" << pType << ")"
                     << endl;
        }
        else
        {
            SWARNING << "Do not run ctr twice "
                     << "type with the name " << pType->getCName() 
                     << "(" << pType << ")"
                     << endl;


            findType(uiTypeId)->dump();

            returnValue = uiTypeId;
        }

        return returnValue;
    }

    returnValue = _vTypeStore.size();

    _vTypeStore.push_back(pType);

    while(_vTypeNameMaps.size() <= pType->getNameSpace())
    {
        _vTypeNameMaps.push_back(new TypeNameMap);

        PINFO << "Added namespace : " << _vTypeNameMaps.size() << endl;
    }

    (*(_vTypeNameMaps[pType->getNameSpace()]))
        [IDStringLink(pType->getCName())] = returnValue;

    PINFO << "Registered type " << pType->getCName() 
          << " | "              << returnValue 
          << "("                << pType 
          << ")"
          << endl;

    return returnValue;
}

UInt32 TypeFactory::findTypeId(const Char8 *szName,
                               const UInt32 uiNameSpace)
{
	TypeNameMapConstIt typeIt;
	UInt32             uiTypeId = 0;

    if(szName == NULL)
        return uiTypeId;

    if(_vTypeNameMaps.size() <= uiNameSpace)
        return uiTypeId;

    TypeNameMap *pMap = _vTypeNameMaps[uiNameSpace];

    typeIt   = pMap->find(IDStringLink(szName));

    uiTypeId = (typeIt == pMap->end()) ? 0 : (*typeIt).second;

	return uiTypeId;
}

TypeBase *TypeFactory::findType(UInt32 uiTypeId)
{
    if(uiTypeId < _vTypeStore.size())
    {
        return _vTypeStore[uiTypeId];
    }
    else
    {
        return NULL;
    }
}

TypeBase *TypeFactory::findType(const Char8    *szName,
                                const UInt32    uiNameSpace)
{
    UInt32 uiTypeId = findTypeId(szName, uiNameSpace);

    return findType(uiTypeId);
}

UInt32 TypeFactory::getNumTypes(void)
{
    return _vTypeStore.size();
}

void TypeFactory::writeDot(FILE *pOut)
{
    if(pOut == NULL)
        return;

    fprintf(pOut, "digraph TypeGraph\n{\n");

/* CHECK
    for_each(_vTypeStore.begin(), 
             _vTypeStore.end(),
             bind1st(ptr_fun(writeTypeDot), pOut));
 */

    for(UInt32 i = 1; i < _vTypeStore.size(); i++)
    {
        writeTypeDot(pOut, _vTypeStore[i]);
    }

    fprintf(pOut, "}\n");
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
    static Char8 cvsid_hpp[] = OSGTYPEFACTORY_HEADER_CVSID;
}

