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

OSG_USING_OSG_NAMESPACE

/** \enum OSGVecBase::VectorSizeE
 *  \brief 
 */

/** \var OSGVecBase::VectorSizeE OSGVecBase::_iSize
 * 
 */

/** \fn const char *OSGVecBase::getClassname(void)
 *  \brief Classname
 */

/** \var OSGValueTypeT OSGVecBase::_values[iSize];
 *  \brief Value store
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSGFieldContainerFactory OSGFieldContainerFactory::_the;

map <int, OSGFieldContainerType*>       *OSGFieldContainerFactory::
    _typeIdMap = 0;
map <OSGString, OSGFieldContainerType*> *OSGFieldContainerFactory::
    _typeNameMap = 0;
map <OSGString, OSGUInt16>              *OSGFieldContainerFactory::
    _groupMap = 0;

OSGBool OSGFieldContainerFactory::_initialized = false;

/** \brief FieldContainer storage
 */

vector<OSGFieldContainerPtr> *
    OSGFieldContainerFactory::_fieldcontainerStoreV = NULL;

/** \brief FieldContainer store lock
 */

OSGLock                      *
    OSGFieldContainerFactory::_storeLock            = NULL;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

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

const vector<OSGFieldContainerPtr> *OSGFieldContainerFactory::getFieldStore(
    void)
{
    return _fieldcontainerStoreV;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

OSGFieldContainerFactory::OSGFieldContainerFactory(void)
{
	initTypeMap();

    osgAddInitFunction(&OSGFieldContainerFactory::initialize);
    osgAddInitFunction(&OSGFieldContainerPtr::initialize);

    osgAddExitFunction(&OSGFieldContainerFactory::terminate);
}

/** \brief Copy Constructor
 */

OSGFieldContainerFactory::OSGFieldContainerFactory(
    const OSGFieldContainerFactory &obj)
{
}

/** \brief Destructor
 */

OSGFieldContainerFactory::~OSGFieldContainerFactory(void)
{
}


/*------------------------------ access -----------------------------------*/


void OSGFieldContainerFactory::initTypeMap(void)
{
	if(_typeIdMap   == NULL && 
       _typeNameMap == NULL) 
    {
		_typeIdMap   = new map <int, OSGFieldContainerType*>;
		_typeNameMap = new map <OSGString, OSGFieldContainerType*>;
		_groupMap    = new map <OSGString, OSGUInt16>;
	}
}


/*---------------------------- properties ---------------------------------*/

OSGUInt16 OSGFieldContainerFactory::addGroup(const OSGChar *groupName)
{
	map< OSGString, OSGUInt16>::iterator gI;

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


OSGFieldContainerType * OSGFieldContainerFactory::findType(int Id)
{
	map <int, OSGFieldContainerType*>::iterator typeI;
	OSGFieldContainerType *type = 0;

	if(_typeIdMap) 
    {
		typeI = _typeIdMap->find(Id);
		type = (typeI == _typeIdMap->end()) ? 0 : (*typeI).second;
	}

	return type;
}


OSGFieldContainerType * OSGFieldContainerFactory::findType(const char *name)
{
	map <OSGString, OSGFieldContainerType*>::iterator typeI;
	OSGFieldContainerType *type = 0;

	if(_typeIdMap) 
    {
		typeI = _typeNameMap->find(OSGStringLink(name));
		type = (typeI == _typeNameMap->end()) ? 0 : (*typeI).second;
	}

	return type;
}


const OSGChar * OSGFieldContainerFactory::findGroupName(OSGUInt16 Id)
{
	map <OSGString, OSGUInt16>::iterator gI;

	for (gI = _groupMap->begin(); gI != _groupMap->end(); gI++) 
    {
		if ((*gI).second == Id)
			return (*gI).first.str();
	}

	return 0;
}


OSGUInt16 OSGFieldContainerFactory::findGroupId ( const OSGChar *groupName)
{
	map <OSGString, OSGUInt16>::iterator gI;

	if (_groupMap) 
    {
		gI = _groupMap->find(groupName);
		return ((gI == _groupMap->end()) ? 0 : (*gI).second);
	}

	return 0;
}


/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

OSGBool OSGFieldContainerFactory::initialize(int argc, char **argv)
{
	map <int, OSGFieldContainerType* >::iterator typeI;

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

    _storeLock = OSGThreadManager::the()->createLock(
        "OSGFieldContainerFactory::_storeLock");

    SDEBUG << "Got store lock " << _storeLock << endl;    

    _initialized = true;

	return _storeLock != NULL;
}

OSGBool OSGFieldContainerFactory::terminate(void)
{
	map <int, OSGFieldContainerType* >::iterator typeI;

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

    OSGThreadManager::the()->destroyLock(_storeLock);

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

OSGNodePtr OSGFieldContainerFactory::createNode(const char *name) 
{
    OSGNodePtr returnValue;

	OSGFieldContainerType *type = findType(name);

    if(type != NULL)
        returnValue = type->createNode();

    return returnValue;
}


OSGNodeCorePtr OSGFieldContainerFactory::createNodeCore(const char *name) 
{
    OSGNodeCorePtr returnValue;

	OSGFieldContainerType *type = findType(name);

    if(type != NULL)
        returnValue = type->createNodeCore();

    return returnValue;
}


OSGAttachmentPtr OSGFieldContainerFactory::createAttachment(
    const char *name) 
{
    OSGAttachmentPtr returnValue;

	OSGFieldContainerType *type = findType(name);

    if(type != NULL)
        returnValue = type->createAttachment();

    return returnValue;
}


/*-------------------------- comparison -----------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



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

