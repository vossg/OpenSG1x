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

Connection *ClusterNetwork::getMainConnection(void)
{
    return _mainConnection;
}

Connection *ClusterNetwork::getConnection(UInt32 id)
{
    if(id<_connection.size())
        return _connection[id];
    else
        return NULL;
}

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

/*! crossconnect servers and the client. If thisId is equal to servers
 *  then this is the server. if withId >=0 then only connections from 
 *  all to withId are created. E.g. connect(...,n) if n=servers then
 *  all servers are connected with the client.
 */
void ClusterNetwork::connect(
    UInt32 thisId,
    UInt32 servers,
    const std::string &connectionType,
    const std::string &localAddress,
    UInt32 withId)
{
    UInt32 id,a;
    UInt32 fromId=0,toId=servers;
    std::vector<std::string> address;

    _connection.resize(servers+1);
    address.resize(servers+1);
    
    if(withId != ALL_NODES)
        fromId = toId = withId;

    for(id = fromId; id <= toId; ++id)
        _connection[id]=ConnectionFactory::the().create(connectionType);
    
    // transmit address to client;
    if(thisId == servers)
    {
        // this is the client
        for(id = fromId; id <= toId; ++id)
        {
            if(id == thisId)
                address[id] = _connection[id]->bind(localAddress);
            else
            {
                _mainConnection->selectChannel(id);
                _mainConnection->getValue(address[id]);
            }
        }
    }
    else
    {
        // this is a server
        _mainConnection->putValue(_connection[thisId]->bind(localAddress));
        _mainConnection->flush();
    }

    // transmit address to all servers;
    for(id = fromId; id <= toId; ++id)
    {
        if(thisId == servers)
        {
            // this is the client
            _mainConnection->putValue(address[id]);
            _mainConnection->flush();
        }
        else
        {
            // this is a server
            _mainConnection->selectChannel();
            _mainConnection->getValue(address[id]);
        }
    }

    // establish connection
    for(id = fromId; id <= toId; ++id)
    {
        if(id == thisId)
        {
            for(a = fromId ; a <= toId ; ++a)
            {
                if(a != id)
                {
                    _connection[a]->connect(address[a]);
                }
            }
        }
        else
        {
            _connection[thisId]->accept();
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

