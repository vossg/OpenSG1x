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
#include "OSGThreadManager.h"
#include "OSGFactoryController.h"
#include "OSGReflexiveContainer.h"
#include "OSGLog.h"

#include <iostream>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template <class FactoryDescT>
typename ContainerFactoryMixin<FactoryDescT>::Factory *
    ContainerFactoryMixin<FactoryDescT>::_the   = NULL;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

template <class FactoryDescT> inline
typename ContainerFactoryMixin<FactoryDescT>::Factory *
    ContainerFactoryMixin<FactoryDescT>::the(void)
{
    if(_the == NULL)
        _the = new Factory(Desc::getName());

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

template <class FactoryDescT> inline
ContainerFactoryMixin<FactoryDescT>::ContainerFactoryMixin(
    const Char8 *szName) :

     Inherited      (szName),

    _bInitialized   (false ),
    _mTypeIdMap     (      ),
    _mTypeNameMap   (      ),

    _vUnitTypesStore(      ),

    _pVecLock       (NULL  )
{
    FactoryController::the()->registerFactory(this);
}


template <class FactoryDescT> inline
ContainerFactoryMixin<FactoryDescT>::~ContainerFactoryMixin(void)
{
}

template <class FactoryDescT> inline
bool ContainerFactoryMixin<FactoryDescT>::initialize(void)
{
    if(_bInitialized == true)
        return true;

    PINFO << "init singleton " << _szName.str() << std::endl;

    _pVecLock   = ThreadManager::the()->getLock(Desc::getMapLockName());
    
    addRefP(_pVecLock);

    PINFO << "Got map   lock " << _pVecLock   << std::endl;    

    _bInitialized = (_pVecLock != NULL);

    if(_bInitialized == true)
    {
        onLoadInitialize();
    }

	return _bInitialized;
}

template <class FactoryDescT> inline
bool ContainerFactoryMixin<FactoryDescT>::terminate(void)
{
    PINFO << "terminate singleton " << _szName.str() << std::endl;

    if(_bInitialized == false)
        return true;

    subRefP(_pVecLock);

    _bInitialized = false;

    return true;
}


template <class FactoryDescT> inline
bool ContainerFactoryMixin<FactoryDescT>::onLoadInitialize(void)
{
    bool           returnValue = true;
    ContainerType *pType       = NULL;

    Inherited::onLoadInitialize();

    if(_bInitialized == false)
        return false;

    PINFO << _szName.str() << " init pending types" << std::endl;

    if(_pVecLock != NULL)
        _pVecLock->aquire();
    
    UninitTypeStoreIt uninitIt  = _vUnitTypesStore.begin();
        
    while(uninitIt != _vUnitTypesStore.end())
    {
        pType = *uninitIt;
        
        if(pType->isInitialized() == true)
        {
            uninitIt = _vUnitTypesStore.erase(uninitIt);
            
            _mTypeIdMap  [pType->getId()                  ] = pType;
            _mTypeNameMap[IDStringLink(pType->getCName()) ] = pType;
        }
        else
        {
            if(pType->initialize() == true)
            {
                uninitIt = _vUnitTypesStore.erase(uninitIt);
                
                _mTypeIdMap  [pType->getId()                  ] = pType;
                _mTypeNameMap[IDStringLink(pType->getCName()) ] = pType;
            }
            else
            {
                returnValue = false;
                
                uninitIt++;
            }
        }
    }
    
    if(_pVecLock != NULL)
        _pVecLock->release();
    
    PINFO << "(" 
             << returnValue 
             << "|" 
             << _vUnitTypesStore.size() 
             << "|"
             << _mTypeIdMap.size()
             << ")" 
             << std::endl;

    return returnValue;
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------------------------ access -----------------------------------*/

template <class FactoryDescT> inline
UInt32 ContainerFactoryMixin<FactoryDescT>::registerType(
    ContainerType *pType)
{
    if(pType == NULL)
        return 0;

    if(_pVecLock != NULL)
        _pVecLock->aquire();

    _vUnitTypesStore.push_back(pType);

    if(_pVecLock != NULL)
        _pVecLock->release();

    return pType->getId();
}

/*------------------------------ access -----------------------------------*/

template <class FactoryDescT> inline
typename ContainerFactoryMixin<FactoryDescT>::ContainerType *
    ContainerFactoryMixin<FactoryDescT>::findType(
        UInt32 uiTypeId) const
{
	TypeIdMapConstIt  typeIt;
	ContainerType    *pType = NULL;

    typeIt = _mTypeIdMap.find(uiTypeId);

    pType   = (typeIt == _mTypeIdMap.end()) ? NULL : (*typeIt).second;

    if(pType == NULL)
    {
        
    }

	return pType;
}

template <class FactoryDescT> inline
typename ContainerFactoryMixin<FactoryDescT>::ContainerType *
    ContainerFactoryMixin<FactoryDescT>::findType(
        const Char8 *szName) const
{
	TypeNameMapCnstIt  typeIt;
	ContainerType     *pType = NULL;

    typeIt = _mTypeNameMap.find(IDStringLink(szName));
    
    pType  = (typeIt == _mTypeNameMap.end()) ? NULL : (*typeIt).second;

	return pType;
}

template <class FactoryDescT> inline
UInt32 ContainerFactoryMixin<FactoryDescT>::getNumTypes(void) const
{
    return _mTypeNameMap.size(); 
}

template <class FactoryDescT> inline
typename ContainerFactoryMixin<FactoryDescT>::ContainerType *
    ContainerFactoryMixin<FactoryDescT>::findUninitializedType(
        const Char8 *szName) const
{
    ContainerType *returnValue = NULL;

    if(szName == NULL)
        return returnValue;

    for(UInt32 i = 0; i < _vUnitTypesStore.size(); i++)
    {
        if(strcmp(szName, _vUnitTypesStore[i]->getCName()) == 0)
        {
            returnValue = _vUnitTypesStore[i];
            break;
        }
    }

    return returnValue;
}




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

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

template <class ParentT> inline
PrototypeFactoryMixin<ParentT>::PrototypeFactoryMixin(
    const Char8 *szName) :

    Inherited      (szName)
{
}


template <class ParentT> inline
PrototypeFactoryMixin<ParentT>::~PrototypeFactoryMixin(void)
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------------------------ access -----------------------------------*/

template <class ParentT> inline
typename PrototypeFactoryMixin<ParentT>::ContainerPtr 
    PrototypeFactoryMixin<ParentT>::createContainer(
        const Char8 *name) const
{
    ContainerPtr returnValue = Desc::getNullPtr();

	const ContainerType *pType = Inherited::findType(name);

    if(pType != NULL)
    {    
        returnValue = Desc::createContainer(pType);
    }

    return returnValue;
}




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

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

template <class ParentT> inline
ContainerStoreFactoryMixin<ParentT>::ContainerStoreFactoryMixin(
    const Char8 *szName) :

     Inherited      (szName),
    _bInitialized   (false ),
    _vContainerStore(      ),
    _pStoreLock     (NULL  )
{
}

template <class ParentT> inline
ContainerStoreFactoryMixin<ParentT>::~ContainerStoreFactoryMixin(void)
{
}

template <class ParentT> inline
bool ContainerStoreFactoryMixin<ParentT>::initialize(void)
{
    bool returnValue = Inherited::initialize();

    if(returnValue == false)
    {
        _bInitialized = false;
        
        return returnValue;
    }

    if(_bInitialized == true)
        return true;

    _pStoreLock = 
        ThreadManager::the()->getLock(Desc::getStoreLockName());
        
    addRefP(_pStoreLock);

    PINFO << "Got store lock " << _pStoreLock << std::endl;    

    _bInitialized = (_pStoreLock != NULL);

	return _bInitialized;
}

template <class ParentT> inline
bool ContainerStoreFactoryMixin<ParentT>::terminate(void)
{
    bool returnValue = Inherited::terminate();

    subRefP(_pStoreLock);

    _bInitialized = false;

    return returnValue;
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------------------------ access -----------------------------------*/

template <class ParentT> inline
UInt32 ContainerStoreFactoryMixin<ParentT>::registerContainer(
    const ContainerPtr &pContainer)
{
    UInt32 returnValue = 0;

    if(_pStoreLock != NULL)
        _pStoreLock->aquire();

    _vContainerStore.push_back(pContainer);
    
    returnValue = _vContainerStore.size() - 1;

    if(_pStoreLock != NULL)
        _pStoreLock->release();

    return returnValue;
}


template <class ParentT> inline
typename ContainerStoreFactoryMixin<ParentT>::ContainerPtr 
    ContainerStoreFactoryMixin<ParentT>::getContainer(
        UInt32 uiContainerId)const
{
    ContainerPtr returnValue = Desc::getNullPtr();

    if(_pStoreLock != NULL)
        _pStoreLock->aquire();

    if(uiContainerId < _vContainerStore.size())
    {
        returnValue = _vContainerStore[uiContainerId];
    }

    if(_pStoreLock != NULL)
        _pStoreLock->release();

    return returnValue;
}

template <class ParentT> inline
const typename ContainerStoreFactoryMixin<ParentT>::ContainerStore &
    ContainerStoreFactoryMixin<ParentT>::getContainerStore(void)
{
    return _vContainerStore;
}




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

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

template <class ParentT> inline
ChangeListFactoryMixin<ParentT>::ChangeListFactoryMixin(
    const Char8 *szName) :

     Inherited  (szName),

    _oChangeList(      )
{
}

template <class ParentT> inline
ChangeListFactoryMixin<ParentT>::~ChangeListFactoryMixin(void)
{
}

template <class ParentT> inline
bool ChangeListFactoryMixin<ParentT>::initialize(void)
{
    return Inherited::initialize();
}

template <class ParentT> inline
bool ChangeListFactoryMixin<ParentT>::terminate(void)
{
    return Inherited::terminate();
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------------------------ access -----------------------------------*/

template <class ParentT> inline
void ChangeListFactoryMixin<ParentT>::beginEdit(
    ContainerPtr , BitVector )
{
}

template <class ParentT> inline
void ChangeListFactoryMixin<ParentT>::endEdit(
    ContainerPtr pContainer, BitVector bWhichField)
{
    _oChangeList.addChanged(Desc::getChangedId(pContainer), bWhichField);
}


template <class ParentT> inline
typename ChangeListFactoryMixin<ParentT>::ChangeList &
    ChangeListFactoryMixin<ParentT>::getChangeList(void)
{
    return _oChangeList;
}

OSG_END_NAMESPACE

#define OSGCONTAINERFACTORYMIXIN_INLINE_CVSID "@(#)$Id: $"






