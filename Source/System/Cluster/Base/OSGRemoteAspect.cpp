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
#include "OSGWindow.h"

#include <map>

OSG_USING_NAMESPACE

/** \class osg::RemoteAspect
 *  \ingroup GrpSystemCluster
 *  \brief Remote aspect controll class
 *
 * The RemoteAspecet is used to synchronize changes of FieldContainers
 * with remote hosts. All changes stored in the current change list
 * are send to a Connection.
 **/

StatElemDesc<StatTimeElem> RemoteAspect::statSyncTime
    ("remoteSyncTime", "time for scenegraph distribution");

/*-------------------------------------------------------------------------*/
/*                            constructor destructor                       */

/*! Constructor
 */
RemoteAspect::RemoteAspect(void) :
    _receivedFC(),
    _receivedType(),
    _sentType(),
    _fieldFilter(),
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
    ReceivedFCT::iterator   i;
    FieldContainerPtr       fcPtr;
    NodePtr                 node;

    // subRef received field container
    for(i = _receivedFC.begin(); i != _receivedFC.end(); i++)
    {
        fcPtr = factory->getContainer(i->second);
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
                        fcPtr = factory->getContainer(i->second);
                    } while(fcPtr != NullFC);
                }
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
    std::string                         name;
    FieldContainerFactory               *factory = FieldContainerFactory::the();
    FieldContainerType                  *fcType;
    FieldContainerPtr                   fcPtr;
    BitVector                           mask;
    RemoteAspectFieldContainerMapper    mapper;
    ReceivedTypeT::iterator             receivedTypeI;
    ReceivedFCT::iterator               receivedFCI;

    if(_statistics)
    {
        _statistics->getElem(statSyncTime)->start();
    }

    connection.selectChannel();

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
                    _receivedType[remoteTypeId] = localTypeId;
                }
                break;
            }

        case CREATED:
            {
                connection.getValue(remoteTypeId);
                connection.getValue(remoteId);
                receivedTypeI = _receivedType.find(remoteTypeId);
                if(receivedTypeI == _receivedType.end())
                {
                    SWARNING <<
                        "Unknown TypeID: " <<
                        remoteTypeId <<
                        std::endl;
                }
                else
                {
                    localTypeId = receivedTypeI->second;
                    fcType = factory->findType(localTypeId);
                    fcPtr = fcType->createFieldContainer();
                    _receivedFC[remoteId] = fcPtr.getFieldContainerId();

                    // make shure, client will not subref to zero
                    addRefCP(fcPtr);
                    addRefCP(fcPtr);
                    callCreated(fcPtr);
                }
                break;
            }

        case DESTROYED:
            {
                connection.getValue(remoteId);
                receivedFCI = _receivedFC.find(remoteId);
                if(receivedFCI == _receivedFC.end())
                {
                    SWARNING <<
                        "Can't destroy unknown FC:" <<
                        remoteId <<
                        std::endl;
                }
                else
                {
                    UInt32  id = receivedFCI->second;
                    _receivedFC.erase(receivedFCI);
                    fcPtr = factory->getContainer(id);
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
                            fcPtr = factory->getContainer(id);
                        } while(fcPtr != NullFC);
                    }
                }
                break;
            }

        case CHANGED:
            {
                connection.getValue(remoteId);
                connection.getValue(mask);
                receivedFCI = _receivedFC.find(remoteId);
                if(receivedFCI == _receivedFC.end())
                {
                    SFATAL <<
                        "Can't change unknown FC:" <<
                        remoteId <<
                        std::endl;
                    throw RemoteSyncError();
                }
                else
                {
                    fcPtr = factory->getContainer(receivedFCI->second);
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

                    callChanged(fcPtr);
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
                receivedFCI = _receivedFC.find(remoteId);
                if(receivedFCI == _receivedFC.end())
                {
                    FDEBUG(("Can't addref unknown FC:%d\n", remoteId));
                }
                else
                {
                    fcPtr = factory->getContainer(receivedFCI->second);
                    FDEBUG(("AddRef: %s ID:%d\n", 
                            fcPtr->getType().getName().str(),
                            fcPtr.getFieldContainerId())) 
                    addRefCP(fcPtr);
                }
                break;
            }

        case SUBREFED:
            {
                connection.getValue(remoteId);
                receivedFCI = _receivedFC.find(remoteId);
                if(receivedFCI == _receivedFC.end())
                {
                    FDEBUG(("Can't subref unknown FC:%d\n", remoteId));
                }
                else
                {
                    fcPtr = factory->getContainer(receivedFCI->second);
                    FDEBUG(("SubRef: %s ID:%d\n", 
                            fcPtr->getType().getName().str(),
                            fcPtr.getFieldContainerId()))
#if 0
                    //ignore until solution is found for subrefs in destructors
                    subRefCP(fcPtr);
#endif
                }
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
        if(_sentType.count(typeId) == 0)
        {
            // mark type as known
            _sentType.insert(typeId);

            // send new type
            cmd = NEWTYPE;
            typeName = fcPtr->getType().getName().str();
            connection.putValue(cmd);
            connection.putValue(typeId);
            connection.putValue(typeName);
        }

        // send container to create
        _sentFC[*createdI] = 0;
        cmd = CREATED;
        connection.putValue(cmd);
        connection.putValue(typeId);
        connection.putValue(*createdI);
    }

    // destroy fct
    for(destroyedI = changeList->beginDestroyed();
            destroyedI != changeList->endDestroyed(); destroyedI++)
    {
        UInt32  id = (*destroyedI);

        // is it a known container
        sentFCI = _sentFC.find(id);
        if(sentFCI != _sentFC.end())
        {
            // remove from known containers
            _sentFC.erase(sentFCI);
            cmd = DESTROYED;
            connection.putValue(cmd);
            connection.putValue(id);
        }
    }

    // changed fields
    // first create a condensed map, where each container is stored
    // only once
    for(changedI = changeList->beginChanged();
            changedI != changeList->endChanged(); changedI++)
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
        sentFCI = _sentFC.find(condensedI->first);

        // ignore changes for not transmitted fieldcontainers
        if(sentFCI == _sentFC.end())
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
            mask &= 0xFFFFFFFFFFFFFFFFL ^ filterI->second;
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

        // ignore subrefs for unknown fcs
        if(_sentFC.find(id) == _sentFC.end())
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
        if(_sentFC.find(id) == _sentFC.end())
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
    std::map<UInt32, UInt32>::iterator i;

    i = _remoteAspect->_receivedFC.find(uiId);
    if(i == _remoteAspect->_receivedFC.end())
    {
        SWARNING << "Can't find container id:\n" << uiId << std::endl;
        mappedId = 0;
    }
    else
    {
        mappedId = i->second;
    }

    FDEBUG(("Map: %d to %d\n", uiId, mappedId)) return mappedId;
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
