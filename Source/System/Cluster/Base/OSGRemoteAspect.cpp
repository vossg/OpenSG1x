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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"
#include "OSGClusterException.h"
#include "OSGFieldDescription.h"
#include "OSGRemoteAspect.h"
#include "OSGFieldContainer.h"
#include "OSGLog.h"
#include "OSGGeometry.h"
#include "OSGTextureChunk.h"
#include "OSGCubeTextureChunk.h"
#include "OSGWindow.h"
#include "OSGMaterial.h"
#include "OSGVertexProgramChunk.h"
#include "OSGFragmentProgramChunk.h"

#include <map>

OSG_USING_NAMESPACE

/** \class osg::RemoteAspect
 *  \ingroup GrpSystemCluster
 *  \brief Remote aspect controll class
 *
 * The RemoteAspecet is used to synchronize changes of FieldContainers
 * with remote hosts. All changes stored in the current change list
 * are send to a Connection.
 *
 * It is possible to send changes in both directions. 
 *
 **/

RemoteAspect::FieldFilterT RemoteAspect::_fieldFilter;

StatElemDesc<StatTimeElem> RemoteAspect::statSyncTime
    ("remoteSyncTime", "time for scenegraph distribution");

/*-------------------------------------------------------------------------*/
/*                            constructor destructor                       */

/*! Constructor
 */
RemoteAspect::RemoteAspect(UInt32 aspectId) :
    _aspectId(aspectId),

    _localFC(),
    _remoteFC(),
    _localType(),

    _sentFC(),
    _receivedFC(),
    _mappedFC(),
    _mappedType(),

    _createdFunctors(),
    _destroyedFunctors(),
    _changedFunctors(),
    _statistics(NULL)
{
    FieldContainerFactory::TypeMapIterator  typeI;

    // initialize field filter
    _fieldFilter[Geometry::getClassType().getId()] = 
        Geometry::GLIdFieldMask;
    _fieldFilter[TextureChunk::getClassType().getId()] = 
        TextureChunk::GLIdFieldMask;
    _fieldFilter[CubeTextureChunk::getClassType().getId()] = 
        CubeTextureChunk::GLIdFieldMask;
    _fieldFilter[VertexProgramChunk::getClassType().getId()] = 
        VertexProgramChunk::GLIdFieldMask;
    _fieldFilter[FragmentProgramChunk::getClassType().getId()] = 
        FragmentProgramChunk::GLIdFieldMask;

    for(typeI = FieldContainerFactory::the()->beginTypes();
            typeI != FieldContainerFactory::the()->endTypes(); ++typeI)
    {
        if(typeI->second->isDerivedFrom(Window::getClassType()))
        {
            _fieldFilter[typeI->second->getId()
                    ] = Window::GlObjectEventCounterFieldMask |
                Window::GlObjectLastRefreshFieldMask |
                Window::GlObjectLastReinitializeFieldMask;
        }
    }
}

/*! Destructor
 */
RemoteAspect::~RemoteAspect(void)
{
    FieldContainerFactory   *factory = FieldContainerFactory::the();
    IdSetT::iterator        i;
    FieldContainerPtr       fcPtr;
    NodePtr                 node;
    WindowPtr               window;

    // subRef received field container
    for(i = _receivedFC.begin(); i != _receivedFC.end(); i++)
    {
        fcPtr = factory->getContainer(*i);
        if(fcPtr != NullFC)
        {
            callDestroyed(fcPtr);

            // currently it is not save to subref all
            // containers because we don't know whether
            // they are referenced by other nodes.
            // It's only save to remove nodes without parents
            node = NodePtr::dcast(fcPtr);
            if(node != NullFC)
            {
                if(node->getParent() == NullFC)
                {
                    do
                    {
                        subRefCP(fcPtr);
                        fcPtr = factory->getContainer(*i);
                    } while(fcPtr != NullFC);
                }
            }
            window = WindowPtr::dcast(fcPtr);
            if(window != NullFC)
            {
                do
                {
                    subRefCP(fcPtr);
                    fcPtr = factory->getContainer(*i);
                } while(fcPtr != NullFC);
            }
            /*
            // subref twice because we have two addrefs on reate
            // It is not possible to subref until the node is removed
            // because if this node is referenced by another node
            // then we will have a crash if we try to subref this
            // other node.
            subRefCP(fcPtr);
            subRefCP(fcPtr);
            */
        }
    }
}

/*-------------------------------------------------------------------------*/
/*                          Remote aspect functionaliy                     */

/*! <EM>receiveSync</EM> reads changes from the given connection and
 *  applies them to the current thread aspect.
 *  Functors for registered types are called, if they occure in the
 *  sync stream.
 * 
 *  \see registerCreated registerChanged registerDeleted
 */
void RemoteAspect::receiveSync(Connection &connection, bool applyToChangelist)
{
    bool                                finish = false;
    UInt8                               cmd;
    UInt32                              remoteTypeId;
    UInt32                              localTypeId;
    UInt32                              remoteId;
    UInt32                              localId;
    UInt32                              localAspect;
    std::string                         name;
    FieldContainerFactory               *factory = FieldContainerFactory::the();
    FieldContainerType                  *fcType;
    FieldContainerPtr                   fcPtr;
    BitVector                           mask;
    RemoteAspectFieldContainerMapper    mapper;
    UInt64                              fullRemoteId;
    LocalTypeMapT::iterator             localTypeI;
    LocalFCMapT::iterator               localFCI;

    // hack. No materialchange after image chagne
    std::vector<MaterialPtr>            materials;

    if(_statistics)
    {
        _statistics->getElem(statSyncTime)->start();
    }

    connection.selectChannel();
    connection.getValue(_remoteAspectId);

    // register mapper into factory
    mapper._remoteAspect = this;
    factory->setMapper(&mapper);
    do
    {
        connection.getValue(cmd);
        switch(cmd)
        {
        case NEWTYPE:
            {
                connection.getValue(remoteTypeId);
                connection.getValue(name);

                // find local type
                fcType = FieldContainerFactory::the()->findType(name.c_str());
                if(!fcType)
                {
                    SWARNING << "Unknown Type: " << name << std::endl;
                }
                else
                {
                    localTypeId = FieldContainerFactory::the()->findType(name.c_str())->getId();

                    // insert remote type id into map
                    _localType[remoteTypeId] = localTypeId;
                }
                break;
            }

        case CREATED:
            {
                connection.getValue(remoteTypeId);
                connection.getValue(remoteId);
                localTypeI = _localType.find(remoteTypeId);
                if(localTypeI == _localType.end())
                {
                    SWARNING <<
                        "Unknown TypeID: " <<
                        remoteTypeId <<
                        std::endl;
                }
                else
                {
                    UInt64 fullRemoteId=getFullRemoteId(remoteId);
                    if(_localFC.find(fullRemoteId) == _localFC.end())
                    {
                        localTypeId = localTypeI->second;
                        fcType = factory->findType(localTypeId);
                        fcPtr = fcType->createFieldContainer();
                        
                        // remove this node, when aspect is removed
                        _receivedFC.insert(fcPtr.getFieldContainerId());
                        
                        // local <-> remote mapping
                        _localFC[fullRemoteId] = fcPtr.getFieldContainerId();
                        _remoteFC[fcPtr.getFieldContainerId()] = fullRemoteId;
                        
                        // make shure, client will not subref to zero
                        addRefCP(fcPtr);
                        addRefCP(fcPtr);
                        callCreated(fcPtr);
                    }
                    else
                    {
                        FDEBUG(("FC already created %d",remoteId));
                    }
                }
                break;
            }

        case DESTROYED:
            {
                connection.getValue(remoteId);
                if(getLocalId(remoteId,localId))
                {
                    clearFCMapping(localId,remoteId);
                    fcPtr = factory->getContainer(localId);
                    if(fcPtr != NullFC)
                    {
                        callDestroyed(fcPtr);

                        // first subref because if on the client side
                        // the refcount gets zero, then no subref is
                        // added to the changelist
                        // then refcount is 0 or 1
                        // 0 if addRef never was called for this fc
                        // 1 if one or more times addRef was called
                        do
                        {
                            subRefCP(fcPtr);
                            fcPtr = factory->getContainer(localId);
                        } while(fcPtr != NullFC);
                    }
                }
                else
                {
                    SWARNING <<
                        "Can't destroy unknown FC:" <<
                        remoteId << " " <<
                        std::endl;
                }
                break;
            }

        case CHANGED:
            {
                connection.getValue(remoteId);
                connection.getValue(mask);

                if(getLocalId(remoteId,localId))
                {
                    fcPtr = factory->getContainer(localId);
                    if(applyToChangelist)
                    {
                        beginEditCP(fcPtr, mask);
                    }

                    /*
                    for(int i=0;i<fcPtr->getType().getNumFieldDescs();i++)
                    {
                        FieldDescription *desc=fcPtr->getType().getFieldDescription(i+1);
                        if(desc->getFieldMask() & mask)
                            cout<< "changed field: " << desc->getName() << std::endl;
                    }
                    */
                    fcPtr->copyFromBin(connection, mask);
                    if(applyToChangelist)
                    {
                        endEditCP(fcPtr, mask);
                    }
                    else
                    {
                        // do we need to call this?
                        changedCP(fcPtr, mask);
                    }
                    MaterialPtr mat=MaterialPtr::dcast(fcPtr);
                    if(mat != NullFC)
                        materials.push_back(mat);
                    callChanged(fcPtr);
                }
                else
                {
                    SFATAL <<
                        "Can't change unknown FC:" <<
                        remoteId << 
                        std::endl;
                    throw RemoteSyncError();
                }
                break;
            }

        case SYNCENDED:
            {
                finish = true;
                break;
            }

        case ADDREFED:
            {
                connection.getValue(remoteId);
                if(getLocalId(remoteId,localId))
                {
                    fcPtr = factory->getContainer(localId);
                    FDEBUG(("AddRef: %s ID:%d\n", 
                            fcPtr->getType().getName().str(),
                            fcPtr.getFieldContainerId())) 
                    addRefCP(fcPtr);
                }
                else
                {
                    FDEBUG(("Can't addref unknown FC:%d\n", remoteId));
                }
                break;
            }

        case SUBREFED:
            {
                connection.getValue(remoteId);
                if(getLocalId(remoteId,localId))
                {
                    fcPtr = factory->getContainer(localId);
                    FDEBUG(("SubRef: %s ID:%d\n", 
                            fcPtr->getType().getName().str(),
                            fcPtr.getFieldContainerId()))
#if 0
                    //ignore until solution is found for subrefs in destructors
                    subRefCP(fcPtr);
#endif
                }
                else
                {
                    FDEBUG(("Can't subref unknown FC:%d\n", remoteId));
                }
                break;
            }
        case IDMAPPING:
            {
                connection.getValue(remoteId);
                connection.getValue(localAspect);
                connection.getValue(localId);
                if(localAspect != _aspectId)
                {
                    SFATAL << "ID mapping for wrong aspect" << std::endl;
                }

                // local <-> remote mapping
                fullRemoteId = getFullRemoteId(remoteId);
                _localFC[fullRemoteId] = localId;
                break;
            }
        default:
            {
                SFATAL << "Unknown tag:" << (int) cmd << std::endl;
                throw RemoteSyncError();
            }
        }
    } 
    while(!finish);

    // chunks don't tell the material if they where changed.
    // This causes problems if textures are loaded after
    // the first matieral change. The Material is not aware
    // of a trasnparency. 
    // Force rebuildState.
    for(std::vector<MaterialPtr>::iterator mI=materials.begin();
        mI != materials.end();
        ++mI) 
    {
        changedCP(*mI);
    }

    // unregister mapper into factory
    factory->setMapper(NULL);

    if(_statistics)
    {
        _statistics->getElem(statSyncTime)->stop();
    }
}

/*! All changes from changeList are send to the connecteion except 
 *  the fields which are filtered. Filters are used to avoid transmission
 *  of local states. e.g. GL variables. 
 */
void RemoteAspect::sendSync(Connection &connection, ChangeList *changeList)
{
    ChangeList::changed_const_iterator  changedI;
    ChangeList::idrefd_const_iterator   createdI;
    ChangeList::idrefd_const_iterator   destroyedI;
    ChangeList::refd_const_iterator     addRefedI;
    ChangeList::refd_const_iterator     subRefedI;
    FieldFilterT::iterator              filterI;
    FieldContainerFactory               *fcFactory = FieldContainerFactory::the();
    FieldContainerPtr                   fcPtr;
    UInt32                              typeId;
    BitVector                           mask;
    UInt8                               cmd;
    std::string                         typeName;
    FieldMaskMapT::iterator             sentFCI;
    FieldMaskMapT                       changedMap;
    FieldMaskMapT::iterator             changedMapI;

    if(_statistics)
    {
        _statistics->getElem(statSyncTime)->start();
    }

    if(!changeList)
    {
        changeList = OSG::Thread::getCurrentChangeList();
    }

    // tell my aspect id
    connection.putValue(_aspectId);

    handleFCMapping(connection);

    // created fct
    for(createdI = changeList->beginCreated();
        createdI != changeList->endCreated(); createdI++)
    {
        fcPtr = fcFactory->getContainer(*createdI);
        if(fcPtr == NullFC)
        {
            continue;
        }

        typeId = fcPtr->getTypeId();

        // type unknown by remote context ?
        if(_mappedType.count(typeId) == 0)
        {
            // mark type as known
            _mappedType.insert(typeId);

            // send new type
            cmd = NEWTYPE;
            typeName = fcPtr->getType().getName().str();
            connection.putValue(cmd);
            connection.putValue(typeId);
            connection.putValue(typeName);
        }

        cmd = CREATED;
        connection.putValue(cmd);
        connection.putValue(typeId);
        connection.putValue(*createdI);

        // sent container to create
        _sentFC.insert(*createdI);
        // fc is known by remote
        _mappedFC.insert(*createdI);

    }

    // destroy fct
    for(destroyedI = changeList->beginDestroyed();
        destroyedI != changeList->endDestroyed(); destroyedI++)
    {
        UInt32  id = (*destroyedI);

        // is it a known container
        if(_mappedFC.count(id))
        {
            clearFCMapping(id,0);
            cmd = DESTROYED;
            connection.putValue(cmd);
            connection.putValue(id);
        }
    }

    // changed fields
    // first create a condensed map, where each container is stored
    // only once
    for(changedI = changeList->beginChanged();
        changedI != changeList->endChanged(); 
        changedI++)
    {
        changedMapI = changedMap.find(changedI->first);
        if(changedMapI == changedMap.end())
        {
            changedMap.insert(std::pair < UInt32,
                                          BitVector > (changedI->first, changedI->second));
        }
        else
        {
            changedMapI->second |= changedI->second;
        }
    }

    for(FieldMaskMapT::iterator condensedI = changedMap.begin();
        condensedI != changedMap.end();
        ++condensedI)
    {
        if(_mappedFC.count(condensedI->first)==0)
            continue;

        FieldContainerPtr fcPtr = 
            FieldContainerFactory::the()->getContainer(condensedI->first);

        // ignore removed containers
        if(fcPtr == NullFC)
            continue;
        mask = condensedI->second;

        // apply field filter
        filterI = _fieldFilter.find(fcPtr->getType().getId());
        if(filterI != _fieldFilter.end())
        {
            FDEBUG(("SyncFieldFilter: :%s \n", 
                    fcPtr->getType().getName().str() )) 
            mask &= TypeTraits<BitVector>::BitsSet ^ filterI->second;
        }

        if(mask)
        {
            // send changes
            condensedI->second |= mask;
            cmd = CHANGED;
            connection.putValue(cmd);
            connection.putValue(condensedI->first); // id
            connection.putValue(mask);              // mask
            fcPtr->copyToBin(connection, mask);
            FDEBUG(("Changed: %s ID:%d Mask:%lld\n", 
                    fcPtr->getType().getName().str(),
                    fcPtr.getFieldContainerId(), 
                    mask))
        }
    }

    // addref
    for(addRefedI = changeList->beginAddRefd();
        addRefedI != changeList->endAddRefd();
        ++addRefedI)
    {
        UInt32  id = (*addRefedI);

        if(_mappedFC.count(id)==0)
            continue;
        cmd = ADDREFED;
        connection.putValue(cmd);
        connection.putValue(id);
    }

    // subref
    for(subRefedI = changeList->beginSubRefd();
        subRefedI != changeList->endSubRefd();
        ++subRefedI)
    {
        UInt32  id = (*subRefedI);

        // ignore addrefs for unknown fcs
        if(_mappedFC.count(id)==0)
            continue;
        cmd = SUBREFED;
        connection.putValue(cmd);
        connection.putValue(id);
    }

    cmd = SYNCENDED;
    connection.putValue(cmd);

    // write buffer
    connection.flush();

    if(_statistics)
    {
        _statistics->getElem(statSyncTime)->stop();
    }
}

/*! The given functor is called when a create of the specified type
 *  is received.
 *
 *  \see receiveSync
 */
void RemoteAspect::registerCreated(const FieldContainerType &type,
                                   const Functor &func)
{
    while(type.getId() >= _createdFunctors.size())
    {
        _createdFunctors.push_back(
            osgTypedFunctionFunctor2CPtrRef
            <bool,FieldContainerPtr,RemoteAspect * >
            (&_defaultCreatedFunction));
    }

    _createdFunctors[type.getId()] = func;
}

/*! The given functor is called when a destroy of the specified type
 *  is received.
 *
 *  \see receiveSync
 */
void RemoteAspect::registerDestroyed(const FieldContainerType &type,
                                     const Functor &func)
{
    while(type.getId() >= _destroyedFunctors.size())
    {
        _destroyedFunctors.push_back(osgTypedFunctionFunctor2CPtrRef < bool,
                                             FieldContainerPtr, RemoteAspect * > (&_defaultDestroyedFunction));
    }

    _destroyedFunctors[type.getId()] = func;
}

/*! The given functor is called when a change of the specified type
 *  is received.
 *
 *  \see receiveSync
 */
void RemoteAspect::registerChanged(const FieldContainerType &type,
                                   const Functor &func)
{
    while(type.getId() >= _changedFunctors.size())
    {
        _changedFunctors.push_back(osgTypedFunctionFunctor2CPtrRef < bool,
                                           FieldContainerPtr,
                                           RemoteAspect * > (&_defaultChangedFunction));
    }

    _changedFunctors[type.getId()] = func;
}

/*! add a new field filter. The given fieldmaks will not be transfered
 */
void RemoteAspect::addFieldFilter( UInt32 typeId,BitVector mask)
{
    _fieldFilter[typeId] |= mask;
}

/*! remove the filter for the given type and mask
 */
void RemoteAspect::subFieldFilter( UInt32 typeId,BitVector mask)
{
    _fieldFilter[typeId] &= ~mask;
}

/*-------------------------------------------------------------------------*/
/*                          statistics                                     */

/*! Set statistics collector
 */
void RemoteAspect::setStatistics(StatCollector *statistics)
{
    _statistics = statistics;
}

/*-------------------------------------------------------------------------*/
/*                        protected helpers                                */

/*! Call created functor for a given FieldContainer
 *
 *  \see registerCreated
 */
bool RemoteAspect::callCreated(FieldContainerPtr &fcp)
{
    bool    result;
    UInt32  uiFunctorIndex = fcp->getType().getId();

    if(uiFunctorIndex < _createdFunctors.size())
    {
        result = _createdFunctors[uiFunctorIndex].call(fcp, this);
    }
    else
    {
        result = _defaultCreatedFunction(fcp, this);
    }

    return result;
}

/*! Call destroyed functor for a given FieldContainer
 *
 *  \see registerDestroyed
 */
bool RemoteAspect::callDestroyed(FieldContainerPtr &fcp)
{
    bool    result;
    UInt32  uiFunctorIndex = fcp->getType().getId();

    if(uiFunctorIndex < _destroyedFunctors.size())
    {
        result = _destroyedFunctors[uiFunctorIndex].call(fcp, this);
    }
    else
    {
        result = _defaultDestroyedFunction(fcp, this);
    }

    return result;
}

/*! Call changed functor for a given FieldContainer
 *
 *  \see registerChanged
 */
bool RemoteAspect::callChanged(FieldContainerPtr &fcp)
{
    bool    result;
    UInt32  uiFunctorIndex = fcp->getType().getId();

    if(uiFunctorIndex < _changedFunctors.size())
    {
        result = _changedFunctors[uiFunctorIndex].call(fcp, this);
    }
    else
    {
        result = _defaultChangedFunction(fcp, this);
    }

    return result;
}

/*! This is called if a fc was edited that was created by another
    aspect 
 */
void RemoteAspect::handleFCMapping(Connection &connection)
{
    UInt8  cmd;
    UInt32 remoteId;
    UInt32 remoteAspect;
    RemoteFCMapT::iterator remoteFCI;

    for(remoteFCI = _remoteFC.begin() ;
        remoteFCI != _remoteFC.end() ;
        ++remoteFCI)
    {
        remoteId     = (UInt32)(remoteFCI->second);
        remoteAspect = (UInt32)(remoteFCI->second>>32);

        cmd = IDMAPPING;
        connection.putValue(cmd);
        connection.putValue(remoteFCI->first);
        connection.putValue(remoteAspect);
        connection.putValue(remoteId);

        _mappedFC.insert(remoteFCI->first);
    }
    _remoteFC.clear();
}

/*! clear maps from local id
 */
void RemoteAspect::clearFCMapping(UInt32 localId,UInt32 remoteId)
{
    _mappedFC.erase(localId);
    _sentFC.erase(localId);
    _receivedFC.erase(localId);

    if(!remoteId)
    {
        RemoteFCMapT::iterator remoteFCI=_remoteFC.find(localId);
        if(remoteFCI != _remoteFC.end())
            remoteId=remoteFCI->second;
    }
    
    RemoteFCMapT::iterator remoteFCI=_remoteFC.find(localId);
    if(remoteFCI != _remoteFC.end())
        _remoteFC.erase(remoteFCI);

    LocalFCMapT::iterator localFCI=_localFC.find(remoteId);
    if(localFCI != _localFC.end())
        _localFC.erase(localFCI);
    
}

/*! get local id mapped from remote id
 */
bool RemoteAspect::getLocalId(UInt32  remoteId,
                              UInt32 &localId)
{
    UInt64 fullRemoteId = getFullRemoteId(remoteId);
    LocalFCMapT::iterator localFCI=_localFC.find(fullRemoteId);

    if( localFCI != _localFC.end() )
    {
        localId=localFCI->second;
        return true;
    }
    else
    {
        return false;
    }
}

UInt64 RemoteAspect::getFullRemoteId(UInt32 fcId)
{
    UInt64 remoteId=_remoteAspectId;
    remoteId<<=32;
    remoteId|=fcId;
    return remoteId;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/
#ifdef __sgi
/* fcp is used only if the FDEBUG macro is not removed by the
   proprocessor. Switch off error for unused fcp parameter. */
#pragma set woff 3201
#endif

/*! Default create functor
 */
bool RemoteAspect::_defaultCreatedFunction(FieldContainerPtr &fcp, RemoteAspect *)
{
    FDEBUG(("Created:%s %d\n", 
            fcp->getType().getName().str(),
            fcp.getFieldContainerId()))
    return true;
}

/*! Default destroyed functor
 */
bool RemoteAspect::_defaultDestroyedFunction(FieldContainerPtr &fcp,
                                             RemoteAspect *)
{
    FDEBUG(("Destroyed:%s %d\n\n",
            fcp->getType().getName().str(),
            fcp.getFieldContainerId()))
    return true;
}

/*! Default changed functor
 */
bool RemoteAspect::_defaultChangedFunction(FieldContainerPtr &fcp, RemoteAspect *)
{
    FDEBUG(("Changed:%s %d\n", 
            fcp->getType().getName().str(),
            fcp.getFieldContainerId()))
    return true;
}

#ifdef __sgi
#pragma reset woff 3201
#endif

/*! Field container id mapper. This mapper mappes remote field 
 *  container id to local ids.
 */
UInt32 RemoteAspectFieldContainerMapper::map(UInt32 uiId)
{
    UInt32  mappedId;
    RemoteAspect::LocalFCMapT::iterator i;

    i = _remoteAspect->_localFC.find(
        _remoteAspect->getFullRemoteId(uiId));
    if(i == _remoteAspect->_localFC.end())
    {
        SWARNING << "Can't find container id:\n" << uiId << std::endl;
        mappedId = 0;
    }
    else
    {
        mappedId = i->second;
    }

    FDEBUG(("Map: %d to %d\n", uiId, mappedId)) 

    return mappedId;
}

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif
#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8    cvsid_cpp[] = "@(#)$Id:$";
    static Char8    cvsid_hpp[] = OSGREMOTEASPECT_HEADER_CVSID;
}
