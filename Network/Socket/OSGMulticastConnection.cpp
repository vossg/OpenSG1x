/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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
 *  \ingroup ClusterLib
 *  \brief Stream socket connection
 *  \author Marcus Roth
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

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

ConnectionType MulticastConnection::_type(&MulticastConnection::create,
                                          "Multicast");

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

MulticastConnection::MulticastConnection(int ) :
	Inherited(0),
    _seqNumber(1),
    _udpReadBuffers(32),
    _udpWriteBuffers(32),
    _maxWaitForAck(40),
    _waitForAck(0.04),
    _maxWaitForSync(0.5),
    _socket(),
    _aliveTime(4),
    _aliveThread(NULL),
    _stopAliveThread(false)
{
    UInt32 i;

    // create read buffers
    _udpReadBuffers.resize( MULTICAST_BUFFER_COUNT );
    for(i=0;i<(_udpReadBuffers.size()-1);i++)
    {
        _udpReadBuffers[i].resize(MULTICAST_BUFFER_SIZE);
        readBufAdd(&_udpReadBuffers[i][sizeof(UDPHeader)],
                   _udpReadBuffers[i].size()-sizeof(UDPHeader));
    }
    _udpReadBuffers[i].resize(MULTICAST_BUFFER_SIZE);

    // create write buffers
    _udpWriteBuffers.resize( MULTICAST_BUFFER_COUNT );
    for(i=0;i<(_udpWriteBuffers.size()-1);i++)
    {
        _udpWriteBuffers[i].resize(MULTICAST_BUFFER_SIZE);
        writeBufAdd(&_udpWriteBuffers[i][sizeof(UDPHeader)],
                     _udpWriteBuffers[i].size()-sizeof(UDPHeader));
    }
    _udpWriteBuffers[i].resize(MULTICAST_BUFFER_SIZE);

    _socket.open();
    _groupSocket.open();
    _aliveSocket.open();
    _aliveSocket.bind();

    startAliveThread();

}

/** \brief Destructor
 */

MulticastConnection::~MulticastConnection(void)
{
    stopAliveThread();
    try
    {
        if(_destination.getPort()!=0)
        {
            UDPHeader closed={0,CLOSED};
            SLOG << "Connection closed" << endl;
            _socket.sendTo(&closed,sizeof(closed),_destination);
        }
        _socket.close();
        _groupSocket.close();
        _aliveSocket.close();
    }
    catch(...)
    {
    }
}

/** \brief create conneciton
 */

Connection *MulticastConnection::create(void)
{
    return new MulticastConnection();
}

/** Bind connection to the givven address
 *
 * Describes, on which port the connection will accept incomming
 * connecitons. If the address string contains no id, then
 * a random id will be choosen. If group is empty, then 224.11.12.50 is used.
 *
 * \param address    string with group:Port:id
 *
 * \return port:id
 **/
string MulticastConnection::bind( const string &address )
{
    char bound[256];
    string group;
    UInt32 port;
    UInt32 member;
    
    interpreteAddress(address,group,port,member);
    if(group.empty())
        group     ="224.11.12.50";
    if(port==0)
        port =6546;

    // prepare socket
    _groupSocket.setReusePort(true);
    _groupSocket.bind(SocketAddress(SocketAddress::ANY,port));
    _groupSocket.join(SocketAddress(group.c_str()));
    _inSocket=_groupSocket;
    _socket.bind(SocketAddress(SocketAddress::ANY,0));

    if(member==0)
    {
        member=(UInt32)(getSystemTime()*(1<<30));
        member&=0x7fff0000;
        member|=_socket.getAddress().getPort();
    }
    _member=member;
    sprintf(bound,"%.120s:%d:%d",group.c_str(),port,member);
    SINFO << "Multicast bound to " << bound << endl;
    return bound;
}

/** Wait for incommint connections on the given address
 **/
void MulticastConnection::accept( void )
{
    UDPBuffer connect;
    SocketAddress destination;
    UInt32 size;
    SocketSelection selection;

    for(;;)
    {
        // wait for connection request
        do
        {
            size=_inSocket.recvFrom(&connect,sizeof(connect),destination);
        }
        while(connect.header.type != CONNECT ||
              connect.member      != htonl(_member));
        // send connection response
        _socket.sendTo(&connect,size,destination);
        // wait max 4 sec for response acknolage
        selection.setRead(_socket);
        selection.setRead(_inSocket);
        if(selection.select(4))
        {
            if(selection.isSetRead(_socket))
            {
                size=_socket.recvFrom(&connect,sizeof(connect),destination);
                if(connect.header.type == CONNECT &&
                   connect.member      == htonl(_member))
                {
                    break;
                }
            }
        }
        else
        {
            // response ack lost. Doesn't matter. Because we haven't
            // got a new connection request either.
            break;
        }
    }
    _destination=destination;
    _channelAddress.push_back(destination);
    _channelSeqNumber.push_back(1);
    SLOG << "Connection accepted from " << destination.getHost()
         << ":" << destination.getPort() << endl;
}

/** connect a connection at the given address
 *
 * \param address    Host:Port:Id
 *
 **/
void MulticastConnection::connect( const string &address )
{
    SocketAddress from;
    UDPBuffer connectRequest;
    UDPBuffer connectResponse;
    string group;
    UInt32 port;
    UInt32 member;
    UInt32 size;

    interpreteAddress(address,group,port,member);
    _destination=SocketAddress(group.c_str(),port);
    if(member==0)
    {
        SFATAL << "Connect to member and no member is given" << endl;
        return;
    }
    if(group.empty())
    {
        SFATAL << "No group given to connect" << endl;
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
         << ":" << member << endl;
}

/** wait for sync
 *
 **/
void MulticastConnection::wait(void)
{
    UInt32 tag;

    // read sync tag;
    selectChannel();
    getValue(tag);
}

/** send sync
 *
 **/
void MulticastConnection::signal(void)
{
    UInt32 tag=0;

    // send signal
    putValue(tag);
    flush();
}

/** get number of links
 *
 **/
UInt32 MulticastConnection::getChannelCount(void)
{
    return _channelAddress.size();
}

/** select channel for read
 *
 * A connection can have n links from which data can be read. So we
 * need to select one channel for exclusive read. 
 *
 **/
void MulticastConnection::selectChannel()
{
    UDPHeader header;
    SocketAddress from;
    SocketSelection selection;
    UInt32 size;

    for(;;)
    {
        if(!_inSocket.waitReadable(_aliveTime+1))
        {
            throw ReadError("Timeout");
        }
        size=_inSocket.peekFrom(&header,sizeof(header),from);
        // wait for data or ack request of unread data
        if(size>=sizeof(header))
        {
            if(header.type == CLOSED)
            {
                throw ReadError("Connection closed");
            }
            for(UInt32 i=0;i<_channelAddress.size();i++)
            {
                if(_channelAddress[i]==from &&
                   ( header.type == DATA ||
                     (header.type == ACK_REQUEST && 
                      ntohl(header.seqNumber) > _channelSeqNumber[i])))
                {
                    _channel=i;
                    return;
                }
            }
        }
        _inSocket.recv(&header,sizeof(header));
    }
}

/** \brief Get type of connection
 *
 * \return ConnectionType pointer
 **/
const ConnectionType *MulticastConnection::getType()
{
    return &_type;
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/** \brief Write buffer
 * 
 * A simple reliable UDP package protocoll is used.
 * 
 * - write all packages as fast as possible
 * - wait some time for acknolages
 * - if unacknolaged packages, then retransmit and go to 2
 **/
void MulticastConnection::readBuffer()
{
    UDPBuffersT::iterator currentBuffer=_udpReadBuffers.begin(); 
    BuffersT::iterator    buffer;
    UDPHeader            *header;
    UDPBuffer             responseAck;
    UInt32                pos;
    SocketAddress         from;
    SocketSelection       selection;
    UInt32                dataSize;
    UInt32                nacks;
    UInt32                seqNumber;

    // clear read buffers
    for(buffer=readBufBegin();buffer!=readBufEnd();++buffer)
        buffer->setDataSize(0);

    for(;;)
    {
        selection.setRead(_inSocket);
        if(selection.select(_aliveTime+1)<=0)
        {
            throw ReadError("Timeout");
        }
        dataSize = _inSocket.recvFrom(&(*currentBuffer)[0],
                                      currentBuffer->size(),
                                      from);
        if(from != _channelAddress[_channel])
            continue;
        header    = (UDPHeader*)&(*currentBuffer)[0];
        seqNumber = ntohl(header->seqNumber);

        if(header->type == ACK_REQUEST)
        {
            responseAck.header.type      = ACK;
            responseAck.header.seqNumber = header->seqNumber;
            nacks                        = 0;
            if(seqNumber > _channelSeqNumber[_channel])
            {
                for(pos = 0 , buffer=readBufBegin();
                    pos < (seqNumber - _channelSeqNumber[_channel]);
                    pos++   , buffer++)
                {
                    if(buffer->getDataSize()==0)
                    {
                        SINFO << "missing" << pos << " " 
                              << _channelSeqNumber[_channel] << " "
                              << seqNumber << endl;
                        responseAck.nack.missing[nacks++]=htonl(pos);
                    }
                }
            }
            responseAck.nack.size        = htonl(nacks);
            // send ack
            _socket.sendTo(&responseAck,
                             (MemoryHandle)(&responseAck.nack.missing
                                            [nacks])-
                             (MemoryHandle)(&responseAck),
                             from);
            if(nacks==0 && 
               _channelSeqNumber[_channel] < seqNumber)
            {
                // ok we got all packages
                _channelSeqNumber[_channel] = seqNumber+1;
                break;
            }
        }
        if(header->type == DATA)
        {
            // ignore old packages
            if(seqNumber < _channelSeqNumber[_channel])
            {
                continue;
            }
            buffer=readBufBegin() + (seqNumber -
                                     _channelSeqNumber[_channel]);
            // ignore retransmitted packages
            if(buffer->getDataSize()>0)
            {
                continue;
            }
            buffer->setMem ( (MemoryHandle)&(*currentBuffer)
                             [sizeof(UDPHeader)] );
            buffer->setDataSize ( dataSize - sizeof(UDPHeader) );
            buffer->setSize ( currentBuffer->size() );
            currentBuffer++;
        }
    }
}    

/** \brief Write buffer
 *
 * A simple reliable UDP package protocoll is used.
 * - read data
 * - if acknolage request, the acknolage already read data 
 *
 * \see writeBuffer
 **/
void MulticastConnection::writeBuffer(void)
{
    vector<int>            send;
    vector<int>::iterator  sendI;
    BuffersT::iterator     bufferI;
    UDPHeader              ackRequest;
    set<SocketAddress>     receivers(_channelAddress.begin(),
                                     _channelAddress.end());
    set<SocketAddress>     missingAcks;
    SocketSelection        selection;
    UDPBuffer              responseAck;
    Time                   waitTime,t0,t1;
    SocketAddress          from;
    UDPHeader             *header;
    UInt32                 nacks;

    for(bufferI=writeBufBegin() ; 
        bufferI!=writeBufEnd() && bufferI->getDataSize()>0 ;
        bufferI++)
    {
        header = (UDPHeader*)(
            bufferI->getMem()-sizeof(UDPHeader));
        header->type      = DATA;
        header->seqNumber = htonl(_seqNumber++);
        send.push_back(true);
    }

    // prepate ackRequest
    ackRequest.seqNumber       = htonl(_seqNumber++);
    ackRequest.type            = ACK_REQUEST;

    // loop as long as one receiver needs some data
    while(!receivers.empty())
    {   
        // send packages as fast as possible
        for(sendI =  send.begin()       , bufferI=writeBufBegin();
            sendI != send.end();
            sendI++                     , bufferI++)
        {
            if(*sendI == true)
            {
                _socket.sendTo(
                    bufferI->getMem()      - sizeof(UDPHeader),
                    bufferI->getDataSize() + sizeof(UDPHeader),
                    _destination);
                *sendI=false;
            }
        }
        missingAcks=receivers;
        // cancle transmission if maxWaitForAck reached
        t0=OSG::getSystemTime();
        while((!missingAcks.empty()) && 
              (_maxWaitForAck-(OSG::getSystemTime()-t0))>0.001)
        {
            // send acknolage request
            _socket.sendTo(&ackRequest,
                           sizeof(UDPHeader),
                           _destination);
            // wait for acknolages. Max _waitForAck seconds.
            for(waitTime=_waitForAck,t1=OSG::getSystemTime();
                waitTime>0.001 && (!missingAcks.empty());
                waitTime=_waitForAck-(OSG::getSystemTime()-t1))
            {
                selection.setRead(_socket);
                if(selection.select(waitTime)>0)
                {
                    _socket.recvFrom(&responseAck,sizeof(responseAck),from);
                    // ignore if we are not waiting for this ack
                    if(missingAcks.find(from)==missingAcks.end())
                    {
                        continue;
                    }
                    // ignore if no ack or old package
                    if(responseAck.header.type != ACK ||
                       responseAck.header.seqNumber != 
                       ackRequest.seqNumber)
                    {
                        continue;
                    }
                    // we got it, so we do not longer wait for this
                    missingAcks.erase(from);
                    nacks=ntohl(responseAck.nack.size);
                    if(nacks==0)
                    {
                        // receiver has got all packages, so we can remove 
                        // from list of receivers for this transmission
                        receivers.erase(from);
                    }
                    else
                    {
                        // mark packages for retransmission
                        for(UInt32 i=0;i<nacks;i++) 
                        {
                            SINFO << "Missing package "
                                  << responseAck.nack.missing[i] << " "
                                  << from.getHost().c_str() << ":"
                                  << from.getPort() << endl;
                            send[ntohl(responseAck.nack.missing[i])]=true;
                        }
                    }
                }
            }
        }
        // not all acks received after maxWaitForAck seconds
        if(!missingAcks.empty())
        {
            throw WriteError("ACK Timeout");
        }
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/** \brief Start alive thread
 *
 * To enable the receiver to detect a canceled sender, we need an 
 * alive signal avery n seconds. Then the receiver is able to set 
 * it's timeout to n+1 
 **/
void MulticastConnection::startAliveThread()
{
    stopAliveThread();
    _stopAliveThread=false;
    _aliveThread=BaseThread::get(NULL);
    _aliveThread->runFunction( aliveProc, (void *) (this) );
}

/** \brief Stop alive thread
 **/
void MulticastConnection::stopAliveThread()
{
    char tag;
    if(_aliveThread)
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
}

/** \brief Start alive thread
 *
 * Send an alive package after _aliveTime 
 **/
void *MulticastConnection::aliveProc(void *arg) 
{ 
    MulticastConnection *connection=static_cast<MulticastConnection *>(arg);
    UDPBuffer alive;

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
        if(connection->_aliveSocket.waitReadable(connection->_aliveTime))
        {
            char tag;
            connection->_aliveSocket.recv(&tag,sizeof(tag));
        }
    }
    return NULL;
}

/** nterprete address
 *
 *  multicastgroup:port:client
 *
 **/

void MulticastConnection::interpreteAddress(const string &address,
                                                  string &group,
                                                  UInt32 &port,
                                                  UInt32 &member)
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
        string::const_iterator i;
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
