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

#include <vector>
#include <algorithm>
#include <set>

#include "OSGConfig.h"
#include "OSGBaseThread.h"
#include "OSGThreadManager.h"
#include "OSGSocketSelection.h"
#include "OSGMulticastConnection.h"
#include "OSGStreamSocket.h"

OSG_USING_NAMESPACE

/** \class osg::MulticastConnection
 *  \ingroup GrpBaseNetwork
 *  \brief Stream socket connection
 *
 * The StreamSockConnection implements the Connection interface. It
 * uses UDP to establish a reliable multicast connection.
 *
 * Multicast address syntax: group:port:id. The id is used to distinguish
 * two clients at the same host, using the same port. Bind is able
 * to generate a unique id if no id is given.
 *
 * Connect: 
 * <PRE>
 * UInt32 intv=1234;
 * MulticastConnection con;
 * con.connect( "224.100.100.100:3333:1" );
 * con.connect( "224.100.100.100:3333:2" );
 * con.connect( "224.100.100.100:3333:3" );
 * con.putValue(intv);
 * con.flush();
 * </PRE>
 *
 * Accept: 
 * <PRE>
 * MulticastConnection con;
 * con.bind("224.100.100.100:3333:1");
 * con.accept();
 * con.selectChannel();
 * UInt32 x;
 * con.getValue(x);
 * </PRE>
 *
 **/

/*-------------------------------------------------------------------------*/
/*                            constructor destructor                       */

/*! Constructor
 */

MulticastConnection::MulticastConnection(int ) :
	Inherited(0),
    _seqNumber(1),
    _maxWaitForAck(40),
    _waitForAck(0.04),
    _maxWaitForSync(0.5),
    _socket(),
    _aliveThread(NULL),
    _stopAliveThread(false),
    _multicastGroupAddress()
{
    // set read buffer
    readBufAdd(_readBuffer.data,MULTICAST_BUFFER_SIZE);
    // set write buffer
    writeBufAdd(_writeBuffer.data,MULTICAST_BUFFER_SIZE);

    _socket.open();
    _groupSocket.open();
    _aliveSocket.open();
    _aliveSocket.bind();

    int readSize  = MULTICAST_BUFFER_SIZE*2;
    int writeSize = MULTICAST_BUFFER_SIZE*2;
    if(_socket.getWriteBufferSize() < writeSize)
        _socket.setWriteBufferSize(writeSize);
    if(_groupSocket.getWriteBufferSize() < writeSize)
        _groupSocket.setWriteBufferSize(writeSize);

    if(_socket.getReadBufferSize() < readSize)
        _socket.setReadBufferSize(readSize);
    if(_groupSocket.getReadBufferSize() < readSize)
        _groupSocket.setReadBufferSize(readSize);

    startAliveThread();
}

/*! Destructor
 */
MulticastConnection::~MulticastConnection(void)
{
    stopAliveThread();
    try
    {
        if(_destination.getPort()!=0)
        {
            UDPHeader closed={0,CLOSED};
            SLOG << "Connection closed" << std::endl;
            _socket.sendTo(&closed,sizeof(closed),_destination);
        }
        subUsedGroup(_multicastGroupAddress);
    }
    catch(...)
    {
    }
    try { _socket.close();      } catch (...) {}
    try { _groupSocket.close(); } catch (...) {}
    try { _aliveSocket.close(); } catch (...) {}
}

/*-------------------------------------------------------------------------*/
/*                           communication functions                       */

/*! Create conneciton
 */
Connection *MulticastConnection::create(void)
{
    return new MulticastConnection();
}

/*! Bind connection to the givven address. Describes, on which port the
    connection will accept incomming connecitons. If the address string
    contains no id, then a random id will be choosen. If group is empty,
    then 224.11.12.50 is used.
 **/
std::string MulticastConnection::bind(const std::string &address)
{
    char          bound[256];
    std::string   group;
    UInt32        port;
    UInt32        member;
    
    interpreteAddress(address,group,port,member);
    _multicastGroupAddress = SocketAddress(group.c_str(),port);
    if(group.empty())
    {
        _multicastGroupAddress = findFreeGroup();
        group = _multicastGroupAddress.getHost();
        port  = _multicastGroupAddress.getPort();
    }

    // prepare socket
    _groupSocket.setReusePort(true);
    _groupSocket.bind(SocketAddress(SocketAddress::ANY,port));
    port=_groupSocket.getAddress().getPort();
    _multicastGroupAddress.setPort(port);
    addUsedGroup(_multicastGroupAddress);
    _groupSocket.join(_multicastGroupAddress);
    _inSocket=_groupSocket;
    _socket.bind(SocketAddress(SocketAddress::ANY,0));

    if(member == 0)
    {
        member=(UInt32)(getSystemTime()*(1<<30));
        member&=0x7fff0000;
        member|=_socket.getAddress().getPort();
    }
    _member=member;
    sprintf(bound,"%.120s:%d:%d",group.c_str(),port,member);
    SINFO << "Multicast bound to " << bound << std::endl;
    return bound;
}

/*! Wait for incommint connections on the given address
 */
void MulticastConnection::accept(void)
{
    UDPBuffer connect;
    SocketAddress destination;
    UInt32 size;
    SocketSelection selection;
    UInt32 firstRequestPort=0;
    Time waitForAck=4;
    Time stopWaitForAck=0;

    for(;;)
    {
        // wait max 4 sec for response acknolage
        selection.setRead(_socket);
        selection.setRead(_inSocket);
        if(selection.select(waitForAck))
        {
            // are we waiting for an ack?
            if(firstRequestPort)
            {
                waitForAck=stopWaitForAck-getSystemTime();
                if(waitForAck<=0)
                    break;
            }
            // request ?
            if(selection.isSetRead(_inSocket))
            {
                size=_inSocket.recvFrom(&connect,sizeof(connect),destination);
                // request for me?
                if(connect.header.type != CONNECT        ||
                   connect.member      != htonl(_member))
                    continue;
                // we can only answer the question from the first socket
                // otherwise more then one connection is accepted
                if(firstRequestPort != 0 && 
                   firstRequestPort != destination.getPort())
                    continue;
                // if already connected
                if(std::find(_channelAddress.begin(),
                             _channelAddress.end(),
                             destination) != _channelAddress.end())
                    continue;
                // respond
                firstRequestPort = destination.getPort();
                stopWaitForAck   = getSystemTime()+4;
                // send connection response
                _socket.sendTo(&connect,size,destination);
            }

            // ack?
            if(selection.isSetRead(_socket))
            {
                size=_socket.recvFrom(&connect,sizeof(connect),destination);
                if(connect.header.type == CONNECT &&
                   connect.member      == htonl(_member))
                    break;
            }
        }
        else
        {
            // ack got lost
            if(firstRequestPort)
                break;
        }
    }
    _destination=destination;
    _channelAddress.push_back(destination);
    _channelSeqNumber.push_back(1);
    SLOG << "Connection accepted from " << destination.getHost()
         << ":" << destination.getPort() << std::endl;
}

/*! Connect to a connection at the given address
 **/
void MulticastConnection::connect(const std::string &address)
{
    SocketAddress from;
    UDPBuffer     connectRequest;
    UDPBuffer     connectResponse;
    std::string   group;
    UInt32        port;
    UInt32        member;
    UInt32        size;

    interpreteAddress(address,group,port,member);
    _multicastGroupAddress=_destination=SocketAddress(group.c_str(),port);
    addUsedGroup(_multicastGroupAddress);
    if(member == 0)
    {
        SFATAL << "Connect to member and no member is given" << std::endl;
        return;
    }
    if(group.empty())
    {
        SFATAL << "No group given to connect" << std::endl;
        return;
    }
    // prepare connection request
    connectRequest.header.type      = CONNECT;
    connectRequest.header.seqNumber = htonl(0);
    connectRequest.member           = htonl(member);
    size=sizeof(connectRequest.header) + sizeof(connectRequest.member);
    for(;;)
    {
        _socket.sendTo(&connectRequest,size,_destination);
        if(_socket.waitReadable(.1))
        {
            _socket.recvFrom(&connectResponse,sizeof(connectResponse),from);
            if(connectResponse.header.type == connectRequest.header.type &&
               connectResponse.member      == connectRequest.member)
            {
                // send ack
                _socket.sendTo(&connectRequest,size,from);
                break;
            }
        }
    }
    _channelAddress.push_back(from);
    _channelSeqNumber.push_back(1);
    _inSocket=_socket;
    SLOG << "Connected to " << from.getHost() 
         << ":" << from.getPort()
         << ":" << member << std::endl;
}

/*! get number of links
 **/
UInt32 MulticastConnection::getChannelCount(void)
{
    return _channelAddress.size();
}

/*! Select channel for read. A connection can have n links from which
    data can be read. So we need to select one channel for exclusive
    read. 
 */
void MulticastConnection::selectChannel(UInt32 channel)
{
    UDPHeader header;
    SocketAddress from;
    SocketSelection selection;
    UInt32 size;

    if(channel != ALL_CHANNELS &&
       channel < _channelAddress.size())
    {
        _channel=channel;
        return;
    }
    for(;;)
    {
        if(!_inSocket.waitReadable(_readAliveTimeout))
        {
            throw ReadError("Timeout in Select");
        }
        size=_inSocket.peekFrom(&header,sizeof(header),from);
        // wait for data or ack request of unread data
        if(size >= sizeof(header))
        {
            if(header.type == CLOSED)
            {
                throw ReadError("Connection closed");
            }
            for(UInt32 i=0 ; i<_channelAddress.size() ; i++)
            {
                if(_channelAddress[i]==from &&
                   ( header.type == DATA ||
                     (header.type == ACK_REQUEST && 
                      ntohl(header.seqNumber) == _channelSeqNumber[i])))
                {
                    _channel=i;
                    return;
                }
            }
        }
        _inSocket.recvAvailable(&header,sizeof(header));
    }
}

/*! Get type of connection
 */
const ConnectionType *MulticastConnection::getType()
{
    return &_type;
}

/*-------------------------------------------------------------------------*/
/*                        protected read, write                            */

/*! Write buffer. A simple reliable UDP package protocoll is used.
    1. write all packages as fast as possible, 2. wait some time for
    acknolages. If unacknolaged packages, then retransmit and go to 2
 */
void MulticastConnection::readBuffer()
{
    UDPHeader             response;
    SocketAddress         from;
    UInt32                dataSize;
    UInt32                seqNumber;

    for(;;)
    {
        if(_inSocket.waitReadable(_readAliveTimeout) == false)
        {
            throw ReadError("Timeout");
        }
        dataSize = _inSocket.recvFrom(&_readBuffer,
                                      sizeof(_readBuffer),
                                      from);
        if(from != _channelAddress[_channel])
            continue;
        seqNumber = ntohl(_readBuffer.header.seqNumber);

        // got a response request
        if(_readBuffer.header.type == ACK_REQUEST)
        {
            if(seqNumber >= _channelSeqNumber[_channel])
                response.type      = NAK;
            else
                response.type      = ACK;
            response.seqNumber = htonl(seqNumber);
            // send response
            _socket.sendTo(&response,sizeof(response),from);
            continue;
        }
        
        if(_readBuffer.header.type == DATA)
        {
            // ignore old packages
            if(seqNumber != _channelSeqNumber[_channel])
                continue;
            _channelSeqNumber[_channel] = seqNumber+1;
            // send ack response
            response.type      = ACK;
            response.seqNumber = htonl(seqNumber);
            _socket.sendTo(&response,sizeof(response),from);
            // set data size
            readBufBegin()->setDataSize ( dataSize - sizeof(UDPHeader) );
            break;
        }
        
    }
}    

/*! Write buffer. A simple reliable UDP package protocoll is used.
    read data, if acknolage request, the acknolage already read data 
 */
void MulticastConnection::writeBuffer(void)
{
    std::set<SocketAddress>     receivers(_channelAddress.begin(),
                                          _channelAddress.end());
    UDPHeader                   response;
    UDPHeader                   request;
    Time                        waitTime,t0,t1;
    SocketAddress               from;
    UInt32                      datasize;

    // send package
    _writeBuffer.header.type      = DATA;
    _writeBuffer.header.seqNumber = htonl(_seqNumber++);
    datasize = writeBufBegin()->getDataSize()+sizeof(UDPHeader);
    _socket.sendTo(&_writeBuffer,datasize,_destination);

    // cancle transmission if maxWaitForAck reached
    t0=OSG::getSystemTime();
    while((!receivers.empty()) && 
          (_maxWaitForAck-(OSG::getSystemTime()-t0))>0.001)
    {

        // wait for acknolages. Max _waitForAck seconds.
        for(waitTime=_waitForAck,t1=OSG::getSystemTime();
            waitTime>0.001 && (!receivers.empty());
            waitTime=_waitForAck-(OSG::getSystemTime()-t1))
        {
            if(_socket.waitReadable(waitTime) == true)
            {
                _socket.recvFrom(&response,sizeof(response),from);
                
                // ignore if we are not waiting for this ack
                if(receivers.find(from)==receivers.end())
                    continue;
                // ignore if wrong seq number
                if(response.seqNumber != _writeBuffer.header.seqNumber)
                    continue;
                // ok
                if(response.type == ACK)
                    receivers.erase(from);
                // not ok, retransmit
                if(response.type == NAK)
                {
                    FDEBUG(("Got NAK: %d\n",ntohl(response.seqNumber)))
                    _socket.sendTo(&_writeBuffer,datasize,_destination);
                }
            }
        }

        // request ack
        if(!receivers.empty())
        {
            request.type      = ACK_REQUEST;
            request.seqNumber = _writeBuffer.header.seqNumber;
            _socket.sendTo(&request,sizeof(request),
                           _destination);
            FDEBUG(( "No response, request ACK: %d\n",ntohl(request.seqNumber)))
        }
            
    }
    // not all acks received after maxWaitForAck seconds
    if(!receivers.empty())
    {
        throw WriteError("ACK Timeout");
    }
}

/*-------------------------------------------------------------------------*/
/*                        Alive thread handling                            */

/*! Start alive thread. To enable the receiver to detect a canceled sender,
    we need an alive signal avery n seconds. Then the receiver is able to
    set it's timeout to n+1 
 */
void MulticastConnection::startAliveThread()
{
    stopAliveThread();
    _stopAliveThread=false;
    _aliveThread=BaseThread::get(NULL);
    _aliveThread->runFunction( aliveProc, (void *) (this) );
}

/*! Stop alive thread
 */
void MulticastConnection::stopAliveThread()
{
    char tag;
    if(_aliveThread)
    {
        try
        {
            _stopAliveThread=true;
            DgramSocket s;
            s.open();
            s.sendTo(&tag,
                     sizeof(tag),
                     SocketAddress(_aliveSocket.getAddress()));
            BaseThread::join( _aliveThread );
//!!        ThreadManager::the()->removeThread(_aliveThread);
            _aliveThread=0;
            if(_aliveSocket.waitReadable(0))
                _aliveSocket.recv(&tag,sizeof(tag));
            s.close();
        }
        catch(...)
        {
            if(_aliveThread->exists())
                _aliveThread->kill();
            FDEBUG(("Stop aliveThread failed\n"))
        }
    }
}

/*! Start alive thread. Send an alive package after _localAliveTimeout 
 */
void MulticastConnection::aliveProc(void *arg) 
{ 
    MulticastConnection *connection=static_cast<MulticastConnection *>(arg);
    UDPBuffer alive;
    Time      waitTime;

    try
    {
        while(!connection->_stopAliveThread)
        {
            if(connection->_destination.getPort()!=0)
            {
                // send ALIVE package
                // receivers should ignore this
                alive.header.seqNumber = htonl(0);
                alive.header.type      = ALIVE;
                alive.member           = htonl(connection->_member);
                connection->_socket.sendTo(
                    &alive,
                    sizeof(UDPHeader)+sizeof(alive.member),
                    connection->_destination);
            }
            waitTime=connection->_sendAliveInterval;
            if(connection->_aliveSocket.waitReadable(waitTime))
            {
                char tag;
                connection->_aliveSocket.recv(&tag,sizeof(tag));
            }
        }
    }
    catch(...)
    {
        FDEBUG(("AliveProc stopped by an exception"));
    }
}

/*! Interprete address. Format is multicastgroup:port:client. Client
    is unique / host.
 */
void MulticastConnection::interpreteAddress(const std::string &address,
                                                  std::string &group,
                                                  UInt32      &port,
                                                  UInt32      &member)
{
    Int32 pos1=address.find(':',0);
    Int32 pos2;
    
    group.erase();
    port=0;
    member=0;
    if(address.empty())
    {
        return;
    }
    if(pos1>0)
    {
        group = address.substr(0,pos1);
        pos2=address.find(':',pos1+1);
        if(pos2>0)
        {
            port = atoi(address.substr(pos1+1,pos2).c_str());
            member = atoi(address.substr(pos2+1).c_str());
        }
        else
        {
            port = atoi(address.substr(pos1+1).c_str());
        }
    }
    else
    {
        std::string::const_iterator i;
        for(i =address.begin();
            i!=address.end() && isdigit(*i);
            i++);
        if(i==address.end())
        {
            port=atoi(address.c_str());
        }
        else
        {
            group=address;
            port=0;
        }
    }
}

/*! Get the next free multicast group
 */
SocketAddress MulticastConnection::findFreeGroup(void)
{
    if(_usedGroup.size()==0)
        return SocketAddress(_defaultGroup.c_str(),_defaultPort);
    std::string address=*_usedGroup.rbegin();
    
    char newAddress[16];
    UInt32 a,b,c,d;

    sscanf(address.c_str(),"%d.%d.%d.%d",&a,&b,&c,&d);
    do
    {
        ++d;
        if(d>254)
        {
            d=254;
            ++c;
            if(c>254)
            {
                c=254;
                ++b;
                if(b>254)
                {
                    SFATAL << "Unable to find free multicast group" 
                           << std::endl;
                    return SocketAddress(_defaultGroup.c_str(),
                                         _defaultPort);
                }                
            }
        }
        sprintf(newAddress,"%d.%d.%d.%d",224,b&255,c&255,d&255);
    }
    while(_usedGroup.find(newAddress) != _usedGroup.end());
    return SocketAddress(newAddress,0);
}

/*! add group address to used list
 */
void MulticastConnection::addUsedGroup(const SocketAddress &group )
{
    _usedGroup.insert(group.getHost());
}

/*! sub group address from used list
 */
void MulticastConnection::subUsedGroup(const SocketAddress &group )
{
    _usedGroup.erase(group.getHost());
}

/*-------------------------------------------------------------------------*/
/*                              class vatiables                            */

ConnectionType MulticastConnection::_type(&MulticastConnection::create,
                                          "Multicast");

std::set<std::string> MulticastConnection::_usedGroup=std::set<std::string>();

std::string MulticastConnection::_defaultGroup="224.11.11.10";
UInt32      MulticastConnection::_defaultPort =17523;

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
    static Char8 cvsid_hpp[] = OSG_MULTICASTCONNECTIONHEADER_CVSID;
}
