/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

char OSGFieldContainerFactory::cvsid[] = "@(#)$Id: $";

OSGFieldContainerFactory OSGFieldContainerFactory::_the;
OSGBool                  OSGFieldContainerFactory::_initialized = false;


OSGFieldContainerFactory::OSGTypeIdMap   *
    OSGFieldContainerFactory::_typeIdMap   = NULL;

OSGFieldContainerFactory::OSGTypeNameMap *
    OSGFieldContainerFactory::_typeNameMap = NULL;

OSGFieldContainerFactory::OSGGroupMap    *
    OSGFieldContainerFactory::_groupMap    = NULL;


/** \brief FieldContainer storage
 */

OSGFieldContainerFactory::OSGFieldContainerStore *
    OSGFieldContainerFactory::_fieldcontainerStoreV = NULL;

/** \brief FieldContainer store lock
 */

OSGLock *OSGFieldContainerFactory::_storeLock = NULL;
OSGLock *OSGFieldContainerFactory::_mapLock   = NULL;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

const OSGFieldContainerFactory &OSGFieldContainerFactory::the(void)
{
    return _the; 
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

void OSGFieldContainerFactory::initTypeMap(void)
{
	if(_typeIdMap   == NULL && 
       _typeNameMap == NULL) 
    {
		_typeIdMap   = new OSGTypeIdMap;
		_typeNameMap = new OSGTypeNameMap;
		_groupMap    = new OSGGroupMap;
	}
}

OSGBool OSGFieldContainerFactory::initialize(int argc, char **argv)
{
	OSGTypeIdMapIt typeIt;

    if(_initialized == true)
        return true;

    SINFO << "init singleton OSGFieldContainerFactory" << endl;

	if(_typeIdMap != NULL) 
    {
		for(  typeIt  = _typeIdMap->begin(); 
              typeIt != _typeIdMap->end(); 
            ++typeIt) 
        {
			(*typeIt).second->initialize(); 
        }
	}

    _storeLock = OSGThreadManager::the()->getLock(
        "OSGFieldContainerFactory::_storeLock");

    _mapLock = OSGThreadManager::the()->getLock(
        "OSGFieldContainerFactory::_maoLock");

    SDEBUG << "Got store lock " << _storeLock << endl;    
    SDEBUG << "Got mao   lock " << _mapLock   << endl;    

    _initialized = true;

	return _storeLock != NULL && _mapLock != NULL;
}

OSGBool OSGFieldContainerFactory::terminate(void)
{
	OSGTypeIdMapIt typeIt;

    SINFO << "terminate singleton OSGFieldContainerFactory" << endl;

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

    OSGThreadManager::the()->freeLock(_storeLock);
    OSGThreadManager::the()->freeLock(_mapLock);

    _initialized = false;
}

OSGUInt32 OSGFieldContainerFactory::registerFieldContainer(
    const OSGFieldContainerPtr &fieldP)
{
    OSGUInt32 returnValue = 0;

    if(_storeLock != NULL)
        _storeLock->aquire();

    if(_fieldcontainerStoreV == NULL)
        _fieldcontainerStoreV = new OSGFieldContainerStore;

    _fieldcontainerStoreV->push_back(fieldP);
    
    returnValue = _fieldcontainerStoreV->size() - 1;

    if(_storeLock != NULL)
        _storeLock->release();

    return returnValue;
}

const OSGFieldContainerFactory::OSGFieldContainerStore *
    OSGFieldContainerFactory::getFieldStore(void)
{
    return _fieldcontainerStoreV;
}

/*! \brief method to add a group, retuns the group Id 
 */
#if 0
OSGUInt16 OSGFieldContainerFactory::addGroup(const OSGChar8 *groupName)
{
	map<OSGString, OSGUInt16>::iterator gI;

	OSGUInt16 Id = 0;
	OSGString str(groupName);

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

OSGFieldContainerType *OSGFieldContainerFactory::findTypeStatic(
    const OSGChar8  *name)
{
	OSGTypeNameMapCnstIt   typeIt;
	OSGFieldContainerType *typeP = NULL;

	if(_typeIdMap) 
    {
		typeIt = _typeNameMap->find(OSGStringLink(name));
		typeP   = (typeIt == _typeNameMap->end()) ? NULL : (*typeIt).second;
	}

	return typeP;
}

OSGFieldContainerType *OSGFieldContainerFactory::findTypeStatic(
    OSGUInt32 typeId)
{
	OSGTypeIdMapConstIt    typeIt;
	OSGFieldContainerType *typeP = NULL;

	if(_typeIdMap) 
    {
		typeIt = _typeIdMap->find(typeId);
		typeP   = (typeIt == _typeIdMap->end()) ? NULL : (*typeIt).second;
	}

	return typeP;
}

OSGUInt16 OSGFieldContainerFactory::findGroupIdStatic(const OSGChar8 *name)
{
	OSGGroupMapConstIt gIt;

	if (_groupMap) 
    {
		gIt = _groupMap->find(OSGStringLink(name));
		return ((gIt == _groupMap->end()) ? 0 : (*gIt).second);
	}

	return 0;
}

OSGUInt32 OSGFieldContainerFactory::registerType(OSGFieldContainerType *typeP)
{
    OSGUInt32 returnValue = 0;

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
    (*_typeNameMap)[OSGStringLink(typeP->getName())] = typeP;

    return returnValue;
}

OSGUInt16 OSGFieldContainerFactory::registerGroup(const OSGChar8 *name)
{
    OSGUInt16 returnValue;

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

		(*_groupMap)[OSGStringLink(name)] = returnValue;
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

OSGFieldContainerType * OSGFieldContainerFactory::findType(OSGUInt32 Id) const
{
	return findTypeStatic(Id);
}


OSGFieldContainerType * OSGFieldContainerFactory::findType(
    const OSGChar8 *name) const
{
    return findTypeStatic(name);
}

OSGUInt32 OSGFieldContainerFactory::getTypeCount(void) const
{ 
    return _typeNameMap ? _typeNameMap->size() : 0; 
}

/*----------------------------- groups ------------------------------------*/

OSGUInt16 OSGFieldContainerFactory::findGroupId(
    const OSGChar8 *groupName) const
{
    return findGroupIdStatic(groupName);
}

const OSGChar8 * OSGFieldContainerFactory::findGroupName(OSGUInt16 Id) const
{
	OSGGroupMapIt gIt;

	for(gIt = _groupMap->begin(); gIt != _groupMap->end(); gIt++) 
    {
		if((*gIt).second == Id)
			return (*gIt).first.str();
	}

	return NULL;
}

OSGUInt16 OSGFieldContainerFactory::getGroupCount(void) const
{
    return _groupMap ? _groupMap->size() : 0;
}

/*----------------------------- create ------------------------------------*/

OSGFieldContainerPtr OSGFieldContainerFactory::createFieldContainer(
    const OSGChar8 *name) const
{
    OSGFieldContainerPtr returnValue;

	const OSGFieldContainerType *type = findType(name);

    if(type != NULL)
        returnValue = type->createFieldContainer();

    return returnValue;
}

OSGNodePtr OSGFieldContainerFactory::createNode(const OSGChar8 *name) const
{
    OSGNodePtr returnValue;

	const OSGFieldContainerType *type = findType(name);

    if(type != NULL)
        returnValue = type->createNode();

    return returnValue;
}

OSGNodeCorePtr OSGFieldContainerFactory::createNodeCore(
    const OSGChar8 *name) const
{
    OSGNodeCorePtr returnValue;

	const OSGFieldContainerType *type = findType(name);

    if(type != NULL)
        returnValue = type->createNodeCore();

    return returnValue;
}

OSGAttachmentPtr OSGFieldContainerFactory::createAttachment(
    const OSGChar8 *name) const
{
    OSGAttachmentPtr returnValue;

	const OSGFieldContainerType *type = findType(name);

    if(type != NULL)
        returnValue = type->createAttachment();

    return returnValue;
}

/*------------------------------ get --------------------------------------*/

OSGFieldContainerPtr OSGFieldContainerFactory::getContainer(
    OSGUInt32 uiContainerId) const
{
    OSGFieldContainerPtr returnValue = OSGNullFC;

    _storeLock->aquire();

    if(uiContainerId < _fieldcontainerStoreV->size())
    {
        returnValue = (*_fieldcontainerStoreV)[uiContainerId];
    }

    _storeLock->release();

    return returnValue;
}

/*----------------------------- dump --------------------------------------*/

void OSGFieldContainerFactory::dump(void) const
{
    if(_fieldcontainerStoreV != NULL)
    {
        for(OSGUInt32 i = 0; i < _fieldcontainerStoreV->size(); i++)
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

OSGFieldContainerFactory::OSGFieldContainerFactory(void)
{
	initTypeMap();

    osgAddInitFunction(&OSGFieldContainerPtr::initialize);
    osgAddInitFunction(&OSGFieldContainerFactory::initialize);

    osgAddExitFunction(&OSGFieldContainerFactory::terminate);
    osgAddExitFunction(&OSGFieldContainerPtr::terminate);
}

/** \brief Destructor
 */

OSGFieldContainerFactory::~OSGFieldContainerFactory(void)
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

