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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------
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

OSG_USING_NAMESPACE

/** \class osg::RemoteAspect
 *  \ingroup GrpSystemCluster
 *  \brief Remote aspect controll class
 *
 * The RemoteAspecet is used to synchronize changes of FieldContainers
 * with remote hosts. All changes stored in the current change list
 * are send to a Connection.
 **/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/** cvsid **/
char RemoteAspect::cvsid[] = "@(#)$Id: OSGRemoteAspect.cpp,v 1.1 2001/08/12 20:34:25 dirk Exp $";

StatElemDesc<StatTimeElem>  
RemoteAspect::statSyncTime ("remoteSyncTime", 
                            "time for scenegraph distribution");

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

RemoteAspect::RemoteAspect():
    _receivedFC(),
    _receivedType(),
    _sentType(),
    _fieldFilter(),
    _createdFunctors(),
    _destroyedFunctors(),
    _changedFunctors(),
    _statistics(NULL)
{
    // initialize field filter
    _fieldFilter[Geometry::getClassType().getId()] 
    = Geometry::GLIdFieldMask;
    _fieldFilter[TextureChunk::getClassType().getId()] 
    = TextureChunk::GLIdFieldMask;
}

/** \brief Destructor
 */

RemoteAspect::~RemoteAspect(void)
{
    FieldContainerFactory *factory=FieldContainerFactory::the();
    ReceivedFCT::iterator i;
    FieldContainerPtr fcPtr;

    // subRef received field container
    for(i =_receivedFC.begin();
        i!=_receivedFC.end();
        i++)
    {
        fcPtr=factory->getContainer(i->second);
        
        callDestroyed(fcPtr);
        // subref all Fealdcontainers
        subRefCP(fcPtr);
    }
}

/** \brief Receive changes from a connection
 *
 * <EM>receiveSync</EM> reads changes from the given connection and
 * applies them to the current thread aspect.
 * Functors for registered types are called, if they occure in the
 * sync stream.
 * 
 * \param connection   Read from this Connection
 * 
 * \see registerCreated registerChanged registerDeleted
 */
void RemoteAspect::receiveSync(Connection &connection,
                               bool applyToChangelist)
{
    bool finish=false;
    UInt8  cmd;
    UInt32 remoteTypeId;
    UInt32 localTypeId;
    UInt32 remoteId;
    std::string name;
    FieldContainerFactory *factory=FieldContainerFactory::the();
    FieldContainerType *fcType;
    FieldContainerPtr fcPtr;
    BitVector mask;
    RemoteAspectFieldContainerMapper mapper;
    ReceivedTypeT::iterator receivedTypeI;
    ReceivedFCT::iterator receivedFCI;

    if(_statistics)
        _statistics->getElem(statSyncTime)->start();

    connection.selectChannel();
    // register mapper into factory
    mapper._remoteAspect=this;
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
                fcType=FieldContainerFactory::the()->findType(name.c_str());
                if(!fcType)
                {
                    SWARNING << "Unknown Type: " << name << std::endl; 
                }
                else
                {
                    localTypeId=FieldContainerFactory::the()->
                        findType(name.c_str())->getId();
                    // insert remote type id into map
                    _receivedType[remoteTypeId]=localTypeId;
                }
                break;
            }
            case CREATED:
            {
                connection.getValue(remoteTypeId);
                connection.getValue(remoteId);
                receivedTypeI=_receivedType.find(remoteTypeId);
                if(receivedTypeI == _receivedType.end())
                {
                    SWARNING << "Unknown TypeID: " 
                             << remoteTypeId 
                             << std::endl; 
                }
                else
                {
                    localTypeId=receivedTypeI->second;
                    fcType=factory->findType(localTypeId);
                    fcPtr=fcType->createFieldContainer();
                    _receivedFC[remoteId]=fcPtr.getFieldContainerId();
                    addRefCP(fcPtr);
                    callCreated(fcPtr);
                }
                break;
            }
            case DESTROYED:
            {
                connection.getValue(remoteId);
                receivedFCI=_receivedFC.find(remoteId);
                if(receivedFCI == _receivedFC.end())
                {
                    SWARNING << "Can't destroy unknown FC:" 
                             << remoteId 
                             << std::endl; 
                }
                else
                {
                    fcPtr=factory->getContainer(receivedFCI->second);
                    callDestroyed(fcPtr);
                    subRefCP(fcPtr);
                }
                break;
            }
            case CHANGED:
            {
                UInt32 maskUInt32;
                connection.getValue(remoteId);
                connection.getValue(maskUInt32);
                mask=maskUInt32;
                receivedFCI=_receivedFC.find(remoteId);
                if(receivedFCI == _receivedFC.end())
                {
                    SFATAL << "Can't change unknown FC:" 
                           << remoteId 
                           << std::endl; 
                    throw RemoteSyncError();
                }
                else
                {
                    fcPtr=factory->getContainer(receivedFCI->second);
                    if(applyToChangelist)
                    {
                        beginEditCP(fcPtr,mask);
                    }
                    /*
                    for(int i=0;i<fcPtr->getType().getNumFieldDescs();i++)
                    {
                        FieldDescription *desc=fcPtr->getType().getFieldDescription(i+1);
                        if(desc->getFieldMask() & mask)
                            cout<< "changed field: " << desc->getName() << std::endl;
                    }
                    */
                    fcPtr->copyFromBin(connection,mask);
                    if(applyToChangelist)
                    {
                        endEditCP(fcPtr,mask);
                    }
                    else
                    {
                        // do we need to call this?
                        changedCP(fcPtr,mask);
                    }
                    callChanged(fcPtr);
                }
                break;
            }
            case SYNCENDED:
            {
                finish=true;
                break;
            }
            case ADDREFED:
            {
                connection.getValue(remoteId);
                receivedFCI=_receivedFC.find(remoteId);
                if(receivedFCI == _receivedFC.end())
                {
                    FDEBUG(("Can't addref unknown FC:%d\n", remoteId)); 
                }
                else
                {
                    fcPtr=factory->getContainer(receivedFCI->second);
                    FDEBUG (( "AddRef: %s ID:%d\n",
                              fcPtr->getType().getName().str(),
                              fcPtr.getFieldContainerId() ))
                    addRefCP(fcPtr);
                }
                break;
            }
            case SUBREFED:
            {
                connection.getValue(remoteId);
                receivedFCI=_receivedFC.find(remoteId);
                if(receivedFCI == _receivedFC.end())
                {
                    FDEBUG(("Can't subref unknown FC:%d\n", remoteId)); 
                }
                else
                {
                    fcPtr=factory->getContainer(receivedFCI->second);
                    FDEBUG (( "SubRef: %s ID:%d\n",
                              fcPtr->getType().getName().str(),
                              fcPtr.getFieldContainerId() ))
                    subRefCP(fcPtr);
                }
                break;
            }
            default:
            {
                SFATAL << "Unknown tag:" << (int)cmd << std::endl;
                throw RemoteSyncError();
            }
        }
    } while(!finish);
    // unregister mapper into factory
    factory->setMapper(NULL);

    if(_statistics)
        _statistics->getElem(statSyncTime)->stop();
}

/** \brief Write all changes from the given ChangeList to the connection.
 *
 * All changes are send to the connecteion except the fields which are
 * filtered. Filters are used to avoid transmission of local states 
 * e.g. GL variables.
 *
 * \param connection   Write to this Connection
 * \param changeList   Read changes from this list. Default is current list
 */
void RemoteAspect::sendSync(Connection &connection,
                            ChangeList *changeList)
{
    ChangeList::changed_const_iterator changedI;
    ChangeList::idrefd_const_iterator  createdI;
    ChangeList::idrefd_const_iterator  destroyedI;
    ChangeList::refd_const_iterator    addRefedI;
    ChangeList::refd_const_iterator    subRefedI;
    FieldFilterT::iterator filterI;
    FieldContainerFactory *fcFactory = FieldContainerFactory::the();
    FieldContainerPtr fcPtr;
    UInt32 typeId;
    BitVector mask;
    UInt32 maskUInt32;
    UInt8 cmd;
    std::string typeName;

    if(_statistics)
        _statistics->getElem(statSyncTime)->start();

    if(!changeList)
    {
        changeList=OSG::Thread::getCurrentChangeList();
    }

    // created fct
    for(createdI =changeList->beginCreated() ;
        createdI!=changeList->endCreated() ;
        createdI++)
    {
        fcPtr=fcFactory->getContainer(*createdI);
        
        if(fcPtr == NullFC)
            continue;

        typeId = fcPtr->getTypeId();
        // type unknown by remote context ?
        if(_sentType.count(typeId)==0)
        {
            // mark type as known
            _sentType.insert(typeId);
            // send new type
            cmd=NEWTYPE;
            typeName=fcPtr->getType().getName().str();
            connection.putValue(cmd);
            connection.putValue(typeId);
            connection.putValue(typeName);
        }
        // send container to create
        cmd=CREATED;
        connection.putValue(cmd);
        connection.putValue(typeId);
        connection.putValue(*createdI);
    }

    // changed fields
    for(changedI =changeList->beginChanged() ;
        changedI!=changeList->endChanged() ;
        changedI++)
    {
        FieldContainerPtr fcPtr = 
            FieldContainerFactory::the()->getContainer(changedI->first);
        if(fcPtr == NullFC)
            continue;
        mask = changedI->second;
        filterI=_fieldFilter.find(fcPtr->getType().getId());
        // apply field filter
        if(filterI != _fieldFilter.end())
        {
            FDEBUG (( "SyncFieldFilter: :%s \n",
                      fcPtr->getType().getName().str() ))
            mask &= 0xFFFFFFFF ^ filterI->second;
        }
        // send changes
        maskUInt32=mask;
        cmd=CHANGED;
        connection.putValue(cmd);
        connection.putValue(fcPtr.getFieldContainerId());   // id
        connection.putValue(maskUInt32);                  // mask
        fcPtr->copyToBin(connection,mask);
        FDEBUG (( "Changed: %s ID:%d Mask:%d\n",
                  fcPtr->getType().getName().str(),
                  fcPtr.getFieldContainerId(),
                  mask ))
    }

    // destroy fct
    for(destroyedI =changeList->beginDestroyed() ;
        destroyedI!=changeList->endDestroyed() ;
        destroyedI++)
    {
        cmd=DESTROYED;
        connection.putValue(cmd);
        connection.putValue(*destroyedI);
    }

    // destroy
    for(addRefedI =changeList->beginAddRefd();
        addRefedI!=changeList->endAddRefd();
        addRefedI++)
    {
        cmd=ADDREFED;
        connection.putValue(cmd);
        connection.putValue(*addRefedI);
    }
    
    // subref
    for(subRefedI =changeList->beginSubRefd();
        subRefedI!=changeList->endSubRefd();
        subRefedI++)
    {
        cmd=SUBREFED;
        connection.putValue(cmd);
        connection.putValue(*subRefedI);
    }
    cmd=SYNCENDED;
    connection.putValue(cmd);
    // write buffer 
    connection.flush();

    if(_statistics)
        _statistics->getElem(statSyncTime)->stop();
}

/** \brief Register functor for create
 *
 * The given functor is called when a create of the specified type
 * is received.
 *
 * \param type  FiieldContainerType 
 * \param func  Functor
 *
 * \see receiveSync
 */
void RemoteAspect::registerCreated(const FieldContainerType &type, 
                                   const Functor &func)
{
    while ( type.getId() >= _createdFunctors.size() )
    {
        _createdFunctors.push_back(
            osgTypedFunctionFunctor2CPtrRef<bool,
                                             FieldContainerPtr,
                                             RemoteAspect     *>(
                                                 &_defaultCreatedFunction));
    }
    _createdFunctors[ type.getId() ] = func;
}

/** \brief Register functor for destroy
 *
 * The given functor is called when a destroy of the specified type
 * is received.
 *
 * \param type  FiieldContainerType 
 * \param func  Functor
 *
 * \see receiveSync
 */
void RemoteAspect::registerDestroyed(const FieldContainerType &type, 
                                     const Functor &func)
{
    while ( type.getId() >= _destroyedFunctors.size() )
    {
        _destroyedFunctors.push_back(
            osgTypedFunctionFunctor2CPtrRef<bool,
                                            FieldContainerPtr,
                                            RemoteAspect     *>(
                                                &_defaultDestroyedFunction));
    }
    _destroyedFunctors[ type.getId() ] = func;
}

/** \brief Register functor for destroy
 *
 * The given functor is called when a change of the specified type
 * is received.
 *
 * \param type  FiieldContainerType 
 * \param func  Functor
 *
 * \see receiveSync
 */
void RemoteAspect::registerChanged(const FieldContainerType &type, 
                                   const Functor &func)
{
    while ( type.getId() >= _changedFunctors.size() )
    {
        _changedFunctors.push_back(
            osgTypedFunctionFunctor2CPtrRef<bool,
                                            FieldContainerPtr,
                                            RemoteAspect     *>(
                                                &_defaultChangedFunction));
    }
    _changedFunctors[ type.getId() ] = func;
}

/** \brief Set statistics collector
 *
 */

void RemoteAspect::setStatistics(StatCollector *statistics)
{
    _statistics = statistics;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/** \brief Call created functor for a given FieldContainer
 *
 * \see registerCreated
 */
bool RemoteAspect::callCreated( FieldContainerPtr &fcp )
{
    bool result;
    UInt32 uiFunctorIndex = fcp->getType().getId();

    if ( uiFunctorIndex < _createdFunctors.size() )
        result = _createdFunctors[uiFunctorIndex].call(fcp,this);
    else 
        result = _defaultCreatedFunction(fcp,this);

    return result;
}

/** \brief Call destroyed functor for a given FieldContainer
 *
 * \see registerDestroyed
 */
bool RemoteAspect::callDestroyed( FieldContainerPtr &fcp )
{
    bool result;
    UInt32 uiFunctorIndex = fcp->getType().getId();

    if ( uiFunctorIndex < _destroyedFunctors.size() )
        result = _destroyedFunctors[uiFunctorIndex].call(fcp,this);
    else 
        result = _defaultDestroyedFunction(fcp,this);

    return result;
}

/** \brief Call changed functor for a given FieldContainer
 *
 * \see registerChanged
 */
bool RemoteAspect::callChanged( FieldContainerPtr &fcp )
{
    bool result;
    UInt32 uiFunctorIndex = fcp->getType().getId();

    if ( uiFunctorIndex < _changedFunctors.size() )
        result = _changedFunctors[uiFunctorIndex].call(fcp,this);
    else 
        result = _defaultChangedFunction(fcp,this);

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

/** \brief Default create functor
 */
bool RemoteAspect::_defaultCreatedFunction(FieldContainerPtr& fcp,
                                           RemoteAspect *)
{
    FDEBUG (( "Created:%s %d\n",
              fcp->getType().getName().str(),
              fcp.getFieldContainerId() ))
    return true;
}

/** \brief Default destroyed functor
 */
bool RemoteAspect::_defaultDestroyedFunction(FieldContainerPtr& fcp,
                                           RemoteAspect *)
{
    FDEBUG (( "Destroyed:%s %d\n\n",
              fcp->getType().getName().str(), 
              fcp.getFieldContainerId() ))
    return true;
}

/** \brief Default changed functor
 */
bool RemoteAspect::_defaultChangedFunction(FieldContainerPtr& fcp,
                                           RemoteAspect *)
{
    FDEBUG (( "Changed:%s %d\n",
              fcp->getType().getName().str(), 
              fcp.getFieldContainerId() ))
    return true;
}

#ifdef __sgi
#pragma reset woff 3201
#endif

/** \brief Field contayner id mapper
 *
 * This mapper mappes remote field container id to local ids
 *
 * \param uiId  remote id
 *
 * \return local id
 */

UInt32 RemoteAspectFieldContainerMapper::map(UInt32 uiId)
{
    UInt32 mappedId;
    std::map<UInt32,UInt32>::iterator i;

    i=_remoteAspect->_receivedFC.find(uiId);
    if(i==_remoteAspect->_receivedFC.end())
    {
        SWARNING << "Can't find container id:\n" << uiId << std::endl;
        mappedId=0;
    }
    else
    {
        mappedId=i->second;
    }
    FDEBUG (( "Map: %d to %d\n",uiId,mappedId ))
    return mappedId;
}
