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

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#define OSG_COMPILEFIELDCONTAINER

#include "OSGBaseFunctions.h"
#include "OSGFieldContainerType.h"
#include "OSGFieldContainerFactory.h"
#include "OSGFieldContainerPtr.h"
#include "OSGThreadManager.h"
#include "OSGLock.h"
#include "OSGLog.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char FieldContainerFactory::cvsid[] = "@(#)$Id: $";

FieldContainerFactory FieldContainerFactory::_the;
Bool                  FieldContainerFactory::_initialized = false;


FieldContainerFactory::TypeIdMap   *
    FieldContainerFactory::_typeIdMap   = NULL;

FieldContainerFactory::TypeNameMap *
    FieldContainerFactory::_typeNameMap = NULL;

FieldContainerFactory::GroupMap    *
    FieldContainerFactory::_groupMap    = NULL;


/** \brief FieldContainer storage
 */

FieldContainerFactory::FieldContainerStore *
    FieldContainerFactory::_fieldcontainerStoreV = NULL;

/** \brief FieldContainer store lock
 */

Lock *FieldContainerFactory::_storeLock = NULL;
Lock *FieldContainerFactory::_mapLock   = NULL;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

const FieldContainerFactory &FieldContainerFactory::the(void)
{
    return _the; 
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

void FieldContainerFactory::initTypeMap(void)
{
	if(_typeIdMap   == NULL && 
       _typeNameMap == NULL) 
    {
		_typeIdMap   = new TypeIdMap;
		_typeNameMap = new TypeNameMap;
		_groupMap    = new GroupMap;
	}
}

Bool FieldContainerFactory::initialize(int argc, char **argv)
{
	TypeIdMapIt typeIt;

    if(_initialized == true)
        return true;

    SINFO << "init singleton FieldContainerFactory" << endl;

	if(_typeIdMap != NULL) 
    {
		for(  typeIt  = _typeIdMap->begin(); 
              typeIt != _typeIdMap->end(); 
            ++typeIt) 
        {
			(*typeIt).second->initialize(); 
        }
	}

    _storeLock = ThreadManager::the()->getLock(
        "FieldContainerFactory::_storeLock");

    _mapLock = ThreadManager::the()->getLock(
        "FieldContainerFactory::_maoLock");

    SDEBUG << "Got store lock " << _storeLock << endl;    
    SDEBUG << "Got mao   lock " << _mapLock   << endl;    

    _initialized = true;

	return _storeLock != NULL && _mapLock != NULL;
}

Bool FieldContainerFactory::terminate(void)
{
	TypeIdMapIt typeIt;

    SINFO << "terminate singleton FieldContainerFactory" << endl;

    if(_initialized == false)
        return true;

	if(_typeIdMap != NULL) 
    {
		for(  typeIt  = _typeIdMap->begin(); 
              typeIt != _typeIdMap->end(); 
            ++typeIt) 
        {
			(*typeIt).second->terminate(); 
        }
	}

    ThreadManager::the()->freeLock(_storeLock);
    ThreadManager::the()->freeLock(_mapLock);

    _initialized = false;

    return true;
}

UInt32 FieldContainerFactory::registerFieldContainer(
    const FieldContainerPtr &fieldP)
{
    UInt32 returnValue = 0;

    if(_storeLock != NULL)
        _storeLock->aquire();

    if(_fieldcontainerStoreV == NULL)
        _fieldcontainerStoreV = new FieldContainerStore;

    _fieldcontainerStoreV->push_back(fieldP);
    
    returnValue = _fieldcontainerStoreV->size() - 1;

    if(_storeLock != NULL)
        _storeLock->release();

    return returnValue;
}

const FieldContainerFactory::FieldContainerStore *
    FieldContainerFactory::getFieldStore(void)
{
    return _fieldcontainerStoreV;
}

/*! \brief method to add a group, retuns the group Id 
 */
#if 0
UInt16 FieldContainerFactory::addGroup(const Char8 *groupName)
{
	map<String, UInt16>::iterator gI;

	UInt16 Id = 0;
	String str(groupName);

	initTypeMap();

	gI = _groupMap->find(str.str());
	Id = (gI == _groupMap->end()) ? 0 : (*gI).second;

	if(!Id) 
    {
		Id = _groupMap->size() + 1;
		(*_groupMap)[str] = Id;
	}

	return Id;
}
#endif

FieldContainerType *FieldContainerFactory::findTypeStatic(
    const Char8  *name)
{
	TypeNameMapCnstIt   typeIt;
	FieldContainerType *typeP = NULL;

	if(_typeIdMap) 
    {
		typeIt = _typeNameMap->find(StringLink(name));
		typeP   = (typeIt == _typeNameMap->end()) ? NULL : (*typeIt).second;
	}

	return typeP;
}

FieldContainerType *FieldContainerFactory::findTypeStatic(
    UInt32 typeId)
{
	TypeIdMapConstIt    typeIt;
	FieldContainerType *typeP = NULL;

	if(_typeIdMap) 
    {
		typeIt = _typeIdMap->find(typeId);
		typeP   = (typeIt == _typeIdMap->end()) ? NULL : (*typeIt).second;
	}

	return typeP;
}

UInt16 FieldContainerFactory::findGroupIdStatic(const Char8 *name)
{
	GroupMapConstIt gIt;

	if (_groupMap) 
    {
		gIt = _groupMap->find(StringLink(name));
		return ((gIt == _groupMap->end()) ? 0 : (*gIt).second);
	}

	return 0;
}

UInt32 FieldContainerFactory::registerType(FieldContainerType *typeP)
{
    UInt32 returnValue = 0;

    initTypeMap();

    if(typeP == NULL)
    {
		SWARNING << "No fieldContainerType given" << endl;

		return returnValue;
    }

	if(typeP->getName() == NULL || *(typeP->getName()) == '\0') 
    {
		SWARNING << "FieldContainerType without name" << endl;

		return returnValue;
	}

    if(findTypeStatic(typeP->getName()) != NULL)
    {
        SWARNING << "ERROR: Can't add a second "
                 << "type with the name" << typeP->getName() << endl;

        return returnValue;
    }

    returnValue = _typeIdMap->size() + 1;
    
    if(findTypeStatic(returnValue) != NULL)
    {
        SWARNING << "ERROR: Can't add a second "
                 << "type with the Id" << returnValue << endl;

        return 0;
    }

    (*_typeIdMap  )[returnValue                    ] = typeP;
    (*_typeNameMap)[StringLink(typeP->getName())] = typeP;

    return returnValue;
}

UInt16 FieldContainerFactory::registerGroup(const Char8 *name)
{
    UInt16 returnValue;

    initTypeMap();

    if(name == NULL || *name == '\0')
    {
        SWARNING << "Group without name" << endl;
        return 0;
    }
    
    returnValue = findGroupIdStatic(name);

    if(returnValue == 0)
    {
        returnValue        = _groupMap->size() + 1;

		(*_groupMap)[StringLink(name)] = returnValue;
    }

    return returnValue;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------------- types -------------------------------------*/

FieldContainerType * FieldContainerFactory::findType(UInt32 Id) const
{
	return findTypeStatic(Id);
}


FieldContainerType * FieldContainerFactory::findType(
    const Char8 *name) const
{
    return findTypeStatic(name);
}

UInt32 FieldContainerFactory::getTypeCount(void) const
{ 
    return _typeNameMap ? _typeNameMap->size() : 0; 
}

/*----------------------------- groups ------------------------------------*/

UInt16 FieldContainerFactory::findGroupId(
    const Char8 *groupName) const
{
    return findGroupIdStatic(groupName);
}

const Char8 * FieldContainerFactory::findGroupName(UInt16 Id) const
{
	GroupMapIt gIt;

	for(gIt = _groupMap->begin(); gIt != _groupMap->end(); gIt++) 
    {
		if((*gIt).second == Id)
			return (*gIt).first.str();
	}

	return NULL;
}

UInt16 FieldContainerFactory::getGroupCount(void) const
{
    return _groupMap ? _groupMap->size() : 0;
}

/*----------------------------- create ------------------------------------*/

FieldContainerPtr FieldContainerFactory::createFieldContainer(
    const Char8 *name) const
{
    FieldContainerPtr returnValue;

	const FieldContainerType *type = findType(name);

    if(type != NULL)
        returnValue = type->createFieldContainer();

    return returnValue;
}

NodePtr FieldContainerFactory::createNode(const Char8 *name) const
{
    NodePtr returnValue;

	const FieldContainerType *type = findType(name);

    if(type != NULL)
        returnValue = type->createNode();

    return returnValue;
}

NodeCorePtr FieldContainerFactory::createNodeCore(
    const Char8 *name) const
{
    NodeCorePtr returnValue;

	const FieldContainerType *type = findType(name);

    if(type != NULL)
        returnValue = type->createNodeCore();

    return returnValue;
}

AttachmentPtr FieldContainerFactory::createAttachment(
    const Char8 *name) const
{
    AttachmentPtr returnValue;

	const FieldContainerType *type = findType(name);

    if(type != NULL)
        returnValue = type->createAttachment();

    return returnValue;
}

/*------------------------------ get --------------------------------------*/

FieldContainerPtr FieldContainerFactory::getContainer(
    UInt32 uiContainerId) const
{
    FieldContainerPtr returnValue = NullFC;

    _storeLock->aquire();

    if(uiContainerId < _fieldcontainerStoreV->size())
    {
        returnValue = (*_fieldcontainerStoreV)[uiContainerId];
    }

    _storeLock->release();

    return returnValue;
}

/*----------------------------- dump --------------------------------------*/

void FieldContainerFactory::dump(void) const
{
    if(_fieldcontainerStoreV != NULL)
    {
        for(UInt32 i = 0; i < _fieldcontainerStoreV->size(); i++)
        {
            (*_fieldcontainerStoreV)[i].dump();
        }
    }
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

FieldContainerFactory::FieldContainerFactory(void)
{
	initTypeMap();

    osgAddInitFunction(&FieldContainerPtr::initialize);
    osgAddInitFunction(&FieldContainerFactory::initialize);

    osgAddExitFunction(&FieldContainerFactory::terminate);
    osgAddExitFunction(&FieldContainerPtr::terminate);
}

/** \brief Destructor
 */

FieldContainerFactory::~FieldContainerFactory(void)
{
}



///---------------------------------------------------------------------------
///  FUNCTION: 
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters: 
//p: 
///
//g: GlobalVars:
//g: 
///
//r: Return:
//r: 
///
//c: Caution:
//c: 
///
//a: Assumptions:
//a: 
///
//d: Description:
//d: 
///
//s: SeeAlso:
//s: 
///---------------------------------------------------------------------------

