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

OSGFieldContainerFactory OSGFieldContainerFactory::_the;
OSGBool                  OSGFieldContainerFactory::_initialized = false;


map<OSGUInt32, OSGFieldContainerType *> *OSGFieldContainerFactory::
    _typeIdMap   = NULL;

map<OSGString, OSGFieldContainerType *> *OSGFieldContainerFactory::
    _typeNameMap = NULL;

map<OSGString, OSGUInt16>               *OSGFieldContainerFactory::
    _groupMap    = NULL;


/** \brief FieldContainer storage
 */

vector<OSGFieldContainerPtr> *
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

OSGFieldContainerFactory &OSGFieldContainerFactory::the(void)
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
		_typeIdMap   = new map <OSGUInt32, OSGFieldContainerType *>;
		_typeNameMap = new map <OSGString, OSGFieldContainerType *>;
		_groupMap    = new map <OSGString, OSGUInt16>;
	}
}

OSGBool OSGFieldContainerFactory::initialize(int argc, char **argv)
{
	map<OSGUInt32, OSGFieldContainerType *>::iterator typeI;

    if(_initialized == true)
        return true;

    SINFO << "init singleton OSGFieldContainerFactory" << endl;

	if(_the._typeIdMap != NULL) 
    {
		for(  typeI  = _the._typeIdMap->begin(); 
              typeI != _the._typeIdMap->end(); 
            ++typeI) 
        {
			(*typeI).second->initialize(); 
            (*typeI).second->print();
        }
	}

    _storeLock = OSGThreadManager::the()->getLock(
        "OSGFieldContainerFactory::_storeLock");

    _mapLock = OSGThreadManager::the()->getLock(
        "OSGFieldContainerFactory::_maoLock");

    SDEBUG << "Got store lock " << _storeLock << endl;    
    SDEBUG << "Got mao   lock " << _mapLock   << endl;    

    _initialized = true;

	return _storeLock != NULL;
}

OSGBool OSGFieldContainerFactory::terminate(void)
{
	map<OSGUInt32, OSGFieldContainerType *>::iterator typeI;

    SINFO << "terminate singleton OSGFieldContainerFactory" << endl;

    if(_initialized == false)
        return true;

	if(_the._typeIdMap != NULL) 
    {
		for(  typeI  = _the._typeIdMap->begin(); 
              typeI != _the._typeIdMap->end(); 
            ++typeI) 
        {
			(*typeI).second->terminate(); 
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
        _fieldcontainerStoreV = new vector<OSGFieldContainerPtr>;

    _fieldcontainerStoreV->push_back(fieldP);
    
    returnValue = _fieldcontainerStoreV->size() - 1;

    if(_storeLock != NULL)
        _storeLock->release();

    return returnValue;
}

const vector<OSGFieldContainerPtr> *OSGFieldContainerFactory::getFieldStore(
    void)
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
	map <OSGString, OSGFieldContainerType*>::const_iterator typeI;
	OSGFieldContainerType *type = NULL;

	if(_typeIdMap) 
    {
		typeI = _typeNameMap->find(OSGStringLink(name));
		type  = (typeI == _typeNameMap->end()) ? NULL : (*typeI).second;
	}

	return type;
}

OSGFieldContainerType *OSGFieldContainerFactory::findTypeStatic(
    OSGUInt32 typeId)
{
	map <OSGUInt32, OSGFieldContainerType*>::const_iterator typeI;
	OSGFieldContainerType *type = 0;

	if(_typeIdMap) 
    {
		typeI = _typeIdMap->find(typeId);
		type  = (typeI == _typeIdMap->end()) ? NULL : (*typeI).second;
	}

	return type;
}

OSGUInt16 OSGFieldContainerFactory::findGroupIdStatic(const OSGChar8 *name)
{
	map <OSGString, OSGUInt16>::const_iterator gI;

	if (_groupMap) 
    {
		gI = _groupMap->find(name);
		return ((gI == _groupMap->end()) ? 0 : (*gI).second);
	}

	return 0;
}

OSGUInt32 OSGFieldContainerFactory::registerType(
    const OSGChar8              *name,
          OSGFieldContainerType *typeP)
{
    OSGUInt32 returnValue = 0;

    initTypeMap();

	if(name == NULL || *name == '\0') 
    {
		SWARNING << "FieldContainerType without name" << endl;

		return returnValue;
	}

    if(findTypeStatic(name) != NULL)
    {
        SWARNING << "ERROR: Can't add a second "
                 << "type with the name" << name << endl;

        return returnValue;
    }

    returnValue = _typeIdMap->size() + 1;
    
    if(findTypeStatic(returnValue) != NULL)
    {
        SWARNING << "ERROR: Can't add a second "
                 << "type with the Id" << returnValue << endl;

        return 0;
    }

    (*_typeIdMap  )[returnValue] = typeP;
    (*_typeNameMap)[name       ] = typeP;

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

		(*_groupMap)[name] = returnValue;
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
	map <OSGUInt32, OSGFieldContainerType*>::const_iterator typeI;
	OSGFieldContainerType *type = 0;

	if(_typeIdMap) 
    {
		typeI = _typeIdMap->find(Id);
		type  = (typeI == _typeIdMap->end()) ? NULL : (*typeI).second;
	}

	return type;
}


OSGFieldContainerType * OSGFieldContainerFactory::findType(
    const OSGChar8 *name) const
{
	map <OSGString, OSGFieldContainerType*>::const_iterator typeI;
	OSGFieldContainerType *type = 0;

	if(_typeIdMap) 
    {
		typeI = _typeNameMap->find(OSGStringLink(name));
		type  = (typeI == _typeNameMap->end()) ? NULL : (*typeI).second;
	}

	return type;
}

OSGUInt32 OSGFieldContainerFactory::getTypeCount(void) const
{ 
    return _typeNameMap ? _typeNameMap->size() : 0; 
}

/*----------------------------- groups ------------------------------------*/

OSGUInt16 OSGFieldContainerFactory::findGroupId(
    const OSGChar8 *groupName) const
{
	map <OSGString, OSGUInt16>::const_iterator gI;

	if (_groupMap) 
    {
		gI = _groupMap->find(groupName);
		return ((gI == _groupMap->end()) ? 0 : (*gI).second);
	}

	return 0;
}

const OSGChar8 * OSGFieldContainerFactory::findGroupName(OSGUInt16 Id) const
{
	map <OSGString, OSGUInt16>::const_iterator gI;

	for (gI = _groupMap->begin(); gI != _groupMap->end(); gI++) 
    {
		if ((*gI).second == Id)
			return (*gI).first.str();
	}

	return NULL;
}

OSGUInt16 OSGFieldContainerFactory::getGroupCount(void) const
{
    return _groupMap ? _groupMap->size() : 0;
}

/*----------------------------- create ------------------------------------*/

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

void OSGFieldContainerFactory::dump(void)
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

