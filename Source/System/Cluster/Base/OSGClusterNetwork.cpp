/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                *
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
#include "OSGClusterNetwork.h"
#include "OSGConnection.h"
#include "OSGConnectionFactory.h"
#include "OSGRemoteAspect.h"

OSG_USING_NAMESPACE

/*! \class osg::ClusterNetwork
    \ingroup GrpSystemCluster
    \brief Refcounted structure to hold all cluster connections

    The ClusterNetwork holds all Connections between servers and client.
    Main reason for this class is to enable cross-connections between
    servers that are neccessary to implement e.g. Hybrid sort-first
    sort-last algorithms.
    This class is a container for all connections between cluster nodes.
    The cluster network is not part of the cluster window or the cluster
    server because it is used on the client and the server side and it
    is accessable from all aspects. 
    If all connections are established, then getMainConnection provides
    the connection from client to all servers. getConnection(n) is the
    connection to the server with id n. If n is the current server id
    then this connection is connected to all other servers.
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

/*! Constructor documentation
 */
ClusterNetwork::ClusterNetwork(UInt32 id) :
    Inherited(),
    _aspect(NULL),
    _mainConnection(NULL),
    _connection(),
    _id(id)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

/*! Destructor documentation
 */
ClusterNetwork::~ClusterNetwork(void)
{
    if(_aspect)
        delete _aspect;
    _aspect=NULL;
    if(_mainConnection)
        delete _mainConnection;
    _mainConnection=NULL;
    for(ConnectionsT::iterator c = _connection.begin();
        c != _connection.end();
        ++c)
    {
        if(*c)
            delete (*c);
        (*c)=NULL;
    }
    _connection.clear();
    ConnectionInfoMapT::iterator ci=_map.find(_id);
    if(ci!=_map.end())
    {
        _map.erase(ci);
    }
}

/*-------------------------------------------------------------------------*/
/*                             Get                                         */

/*! get main connection. The main connection is used to sync
    the network aspects
 */
Connection *ClusterNetwork::getMainConnection(void)
{
    return _mainConnection;
}

/*! get main connection as group connection. If main connection
    is a point connection, then NULL is returned
 */
GroupConnection *ClusterNetwork::getMainGroupConnection(void)
{
    return dynamic_cast<GroupConnection*>(_mainConnection);
}

/*! get main connection as point connection. If main connection
    is a group connection, then NULL is returned
 */
PointConnection *ClusterNetwork::getMainPointConnection(void)
{
    return dynamic_cast<PointConnection*>(_mainConnection);
}

/*! get connection with the given id
 */
Connection *ClusterNetwork::getConnection(UInt32 id)
{
    if(id<_connection.size())
        return _connection[id];
    else
        return NULL;
}

/*! get connection as group connection. If main connection
    is a point connection, then NULL is returned
 */
GroupConnection *ClusterNetwork::getGroupConnection(UInt32 id)
{
    return dynamic_cast<GroupConnection*>(getConnection(id));
}

/*! get main connection as point connection. If main connection
    is a group connection, then NULL is returned
 */
PointConnection *ClusterNetwork::getPointConnection(UInt32 id)
{
    return dynamic_cast<PointConnection*>(getConnection(id));
}

/*! get remote aspect
 */
RemoteAspect *ClusterNetwork::getAspect(void)
{
    return _aspect;
}

ClusterNetwork::ConnectionsT &ClusterNetwork::getConnection(void)
{
    return _connection;
}

/*-------------------------------------------------------------------------*/
/*                             Set                                         */

/*! Set remote Aspect
 */
void ClusterNetwork::setAspect(RemoteAspect *aspect)
{
    _aspect=aspect;
}

/*! Set main connection. This is the connection for aspect sync 
 */
void ClusterNetwork::setMainConnection(Connection *connection)
{
    _mainConnection=connection;
}

/*! Set connection 
 */
void ClusterNetwork::setConnection(UInt32 id,Connection *connection)
{
    while(id<_connection.size())
        _connection.push_back(NULL);
    _connection[id]=connection;
}

/*-------------------------------------------------------------------------*/
/*                          establish connection                           */

/*! crossconnect servers and the client. 
 */
void ClusterNetwork::connect(
    UInt32 thisId,
    const std::string &connectionType)
{
    bool                                   isClient;
    UInt32                                 servers;
    Connection                            *addressSource;
    UInt32                                 id,c;
    std::map<UInt32,std::string>           address;
    std::vector<UInt32>                    fromId;
    std::vector<UInt32>                    toId;
    std::vector<std::string>               toAddr;
    UInt32                                 addrCount;
    Connection::Channel                    channel;
    std::string                            clientAddress;

    // determine if this is a server 
    if(dynamic_cast<GroupConnection*>(_mainConnection))
        isClient = true;
    else
        isClient = false;
    // communicate server count
    if(isClient)
    {
        servers = getMainGroupConnection()->getChannelCount();
        _mainConnection->putValue(servers);
        _mainConnection->flush();
    }
    else
    {
        _mainConnection->getValue(servers);
    }

    addrCount = (servers+1) * servers / 2;
    fromId.resize(addrCount);
    toId.resize  (addrCount);
    toAddr.resize(addrCount);

    _connection.resize(servers+1);
    // send all addresses
    for(id = 0; id <= servers; ++id)
    {
        if(isClient && id == thisId)
            _connection[id] = 
                ConnectionFactory::the().createGroup(connectionType);
        else
            _connection[id] = 
                ConnectionFactory::the().createPoint(connectionType);
        if(id > thisId)
        {
            _mainConnection->putValue(id);
            _mainConnection->putValue(thisId);
            _mainConnection->putValue(_connection[id]->bind());
            _mainConnection->flush();
        }
    }
    // read and retransmit all addresses
    if(isClient)
    {
        for(c = 0 ; c < addrCount ; ++c)
        {
            channel = getMainGroupConnection()->selectChannel();
            getMainGroupConnection()->getValue(fromId[c]);
            getMainGroupConnection()->getValue(toId[c]);
            getMainGroupConnection()->getValue(toAddr[c]);
            // remember client to server
            if(fromId[c] == thisId)
            {
                address[toId[c]] = toAddr[c];
                getMainGroupConnection()->subSelection(channel);
            }
        }
        getMainGroupConnection()->resetSelection();
        for(c = 0 ; c < addrCount ; ++c)
        {
            _mainConnection->putValue(fromId[c]);
            _mainConnection->putValue(toId[c]);
            _mainConnection->putValue(toAddr[c]);
        }
        _mainConnection->flush();
    }
    // receive all addresses
    if(!isClient)
    {
        _mainConnection->selectChannel();
        for(c = 0 ; c < (servers+1) * servers / 2 ; ++c)
        {
            _mainConnection->getValue(fromId[c]);
            _mainConnection->getValue(toId[c]);
            _mainConnection->getValue(toAddr[c]);
            if(fromId[c] == thisId)
                address[toId[c]] = toAddr[c];
        }
    }
    // connect to all
    for(id = 0; id <= servers; ++id)
    {
        if(id > thisId)
        {
            _connection[id]->acceptPoint();
        }
        if(id < thisId)
        {
            for(;;)
                try
                {
                    _connection[id]->connectPoint(address[id]);
                    break;
                }
                catch(...)
                {
                }
        }
    }

    // connect all servers with the client.
    if(isClient)
    {
        _mainConnection->putValue(_connection[thisId]->bind());
        _mainConnection->flush();
        for(id=0 ; id < servers ; ++id)
        {
            getGroupConnection(thisId)->acceptPoint();
        }
    }
    else
    {
        _mainConnection->getValue(clientAddress);
        for(;;)
            try
            {
                getPointConnection(thisId)->connectGroup(clientAddress);
                break;
            }
            catch(...)
            {
            }
    }
}

/*-------------------------------------------------------------------------*/
/*                              static access                              */

/*! Get an instance of the ClusterNetwork with the given container id
 */
ClusterNetwork *ClusterNetwork::getInstance(UInt32 clusterWindowId)
{
    ConnectionInfoMapT::iterator ci=_map.find(clusterWindowId);
    if(ci==_map.end())
    {
        ClusterNetwork *ciP=new ClusterNetwork(clusterWindowId);
        _map[clusterWindowId]=ciP;
        return ciP;
    }
    else
    {
        return ci->second;
    }
}

/*-------------------------------------------------------------------------*/
/*                              static elements                            */

ClusterNetwork::ConnectionInfoMapT ClusterNetwork::_map;

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
    static Char8 cvsid_cpp[] = "@(#)$Id:$";
    static Char8 cvsid_hpp[] = OSG_CLUSTERCONNECTINFOHEADER_CVSID;
}

