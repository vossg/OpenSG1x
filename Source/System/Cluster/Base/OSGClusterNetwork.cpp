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
    std::cout << "create network id :" << id << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

/*! Destructor documentation
 */
ClusterNetwork::~ClusterNetwork(void)
{
    std::cout << "delete network id:" << _id << std::endl;
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
    if(id<=_connection.size())
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
    Int32  withId)
{
    UInt32 c;
    Connection *connection;
    std::string address;
    UInt32 fromId=0,toId=servers;
    UInt32 recvId;
    bool isClient,connectThisId;
    UInt32 idCnt;

    std::cout << "start" << std::endl;
    isClient      =(thisId == servers);
    if(withId>=0)
    {
        fromId=toId=(UInt32)withId;
    }
    if(_mainConnection==NULL)
    {
        SFATAL << "main connection missing" << std::endl;
        return;
    }
    while(_connection.size()<=toId)
        _connection.push_back(NULL);
    for(c = fromId; c <= toId; ++c)
    {
        connectThisId = (c == thisId);

        connection = ConnectionFactory::the().create(connectionType);
        if(connectThisId)
            address = connection->bind(localAddress);
        if(isClient)
        {
            // send all servers a start flag
            std::cout << c << "send start flag" << std::endl;
            _mainConnection->putValue(thisId);
            _mainConnection->flush();
            std::cout << c << "get response" << std::endl;
            // receive response from all servers
            for(idCnt = 0; idCnt < servers ; ++idCnt)
            { 
                _mainConnection->selectChannel();
                _mainConnection->getValue(recvId);
                std::cout << "client got id " << recvId << std::endl;
                if(recvId == c)
                    _mainConnection->getValue(address);
            }
            std::cout << c << "send address " << address << std::endl;
            // tell all servers the current address to connect
            _mainConnection->putValue(address);
            _mainConnection->flush();
            std::cout << c << "done " << address << std::endl;
        }
        else
        {
            std::cout << c << "recv start flag" << std::endl;
            // ceceive start flag
            _mainConnection->selectChannel();
            _mainConnection->getValue(recvId);
            std::cout << c << "send response" << std::endl;
            // send response
            _mainConnection->putValue(thisId);
            if(connectThisId)
                _mainConnection->putValue(address);
            _mainConnection->flush();
            std::cout << c << "get address " << std::endl;
            // read address
            _mainConnection->selectChannel();
            _mainConnection->getValue(address);
            std::cout << c << "get address " << address << std::endl;
        }
        if(connectThisId)
        {
            for(idCnt = 0; idCnt < servers; ++idCnt)
            {
                std::cout << "accept" << std::endl;
                connection->accept();
                std::cout << "accept end" << std::endl;
            }
        }
        else
        {
            std::cout << c << "connect " << address << std::endl;
            connection->connect(address);
            std::cout << c << "connect end" << address << std::endl;
        }
        _connection[c]=connection;
    }
    std::cout << "finish" << std::endl;
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

