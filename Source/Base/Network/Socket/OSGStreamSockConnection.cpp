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
#ifndef WIN32
#include <unistd.h>
#endif
#include <algorithm>

#include <OSGConfig.h>
#include <OSGLog.h>
#include <OSGStreamSockConnection.h>
#include <OSGSocketSelection.h>

OSG_USING_NAMESPACE

/** \class osg::StreamSockConnection
 *  \ingroup ClusterLib
 *  \brief Stream socket connection
 *  \author Marcus Roth
 *
 * The StreamSockConnection implements the Connection interface
 *
 * Connect: 
 * <PRE>
 * StreamSockConnection con;
 * con.connect( "dagobert:3333" );
 * con.connect( "donald:3333" );
 * con.connect( "tric:3333" );
 * con.putUInt32(1234);
 * con.flush();
 * </PRE>
 *
 * Accept: 
 * <PRE>
 * StreamSockConnection con;
 * con.bind("3333");
 * con.accept();
 * con.selectChannel();
 * UInt32 x;
 * con.getUInt32(x);
 * </PRE>
 *
 **/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char StreamSockConnection::cvsid[] = "@(#)$Id:$";
ConnectionType StreamSockConnection::_type(&StreamSockConnection::create,
                                           "StreamSock");

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 *
 * Initialize a StreamSockConnection. By default a buffer of 16000 bytes
 * is used.
 */

StreamSockConnection::StreamSockConnection():
    Inherited(16000),
    _sockets()
{
    _socketReadBuffer.resize(64000);
    _socketWriteBuffer.resize( _socketReadBuffer.size() );
    // reserve first bytes for buffer size
    readBufAdd (&_socketReadBuffer [sizeof(SocketBufferHeader)],
                _socketReadBuffer.size() -sizeof(SocketBufferHeader));
    writeBufAdd(&_socketWriteBuffer[sizeof(SocketBufferHeader)],
                _socketWriteBuffer.size()-sizeof(SocketBufferHeader));
}

/** \brief Destructor
 */

StreamSockConnection::~StreamSockConnection(void)
{
    SocketsT::iterator socket;

    // close all sockets
    for(socket =_sockets.begin();
        socket!=_sockets.end();
        socket++)
    {
        try
        {
            socket->close();
        }
        catch(...)
        {
        }
    }
    try
    {
        _acceptSocket.close();
        _readSocket.close();
    }
    catch(...)
    {
    }
}

/** Read data into given memory
 *
 * Read data form the current read socket. The read socket is that
 * socket, that was selectet in selectChannel.
 *
 **/

void StreamSockConnection::read(MemoryHandle mem,UInt32 size)
{
    int len;

    // read data
    len=_readSocket.recv(mem,size);
    if(len==0)
    {
        std::cout << size << std::endl;
        throw ReadError("read got 0 bytes!");
    }
}

/** Read next data block
 *
 * The stream connection uses only BinaryDataHandler buffer. If more
 * then one buffer is present, then this methode must be changed!
 *
 */

void StreamSockConnection::readBuffer()
{
    int size;
    int len;

    // read buffer header
    len=_readSocket.recv(&_socketReadBuffer[0],sizeof(SocketBufferHeader));
    if(len==0)
        throw ReadError("peek got 0 bytes!");
    // read remaining data
    size=ntohl(((SocketBufferHeader*)&_socketReadBuffer[0])->size);
    len=_readSocket.recv(&_socketReadBuffer[sizeof(SocketBufferHeader)],
                         size);
    if(len==0)
        throw ReadError("read got 0 bytes!");
    readBufBegin()->setDataSize(size);
}    

/** Write data to all destinations
 *
 * \param mem   Pointer to data buffer
 * \param size  Size of bytes to write
 *
 **/

void StreamSockConnection::write(MemoryHandle mem,UInt32 size)
{
    SocketsT::iterator socket;

    // write to all connected sockets
    for(socket =_sockets.begin();
        socket!=_sockets.end();
        socket++)
    {
        socket->send(mem,size);
    }
}

/** Write buffer
 *
 * Write blocksize and data.
 *
 **/
void StreamSockConnection::writeBuffer(void)
{
    UInt32 size = writeBufBegin()->getDataSize();
    // write size to header
    ((SocketBufferHeader*)&_socketWriteBuffer[0])->size=htonl(size);
    // write data to all sockets
    for(SocketsT::iterator socket =_sockets.begin();
        socket!=_sockets.end();
        ++socket)
    {
        // write whole block
        socket->send(&_socketWriteBuffer[0],size+sizeof(SocketBufferHeader));
    }
}

/** Bind connection to the givven address
 *
 * \param address    Port number
 *
 **/
std::string StreamSockConnection::bind(const std::string &address)
{
    char        localhost   [256];
    char        boundAddress[270];
    std::string host;
    UInt32      port = 0;

    if(!address.empty())
    {
        interpreteAddress(address,host,port);
    }
    _acceptSocket.open();
    _acceptSocket.setReusePort(true);
    _acceptSocket.bind(SocketAddress(SocketAddress::ANY,port));
    _acceptSocket.listen();
    gethostname(localhost,255);
    sprintf(boundAddress,"%s:%5d",
            localhost,
            _acceptSocket.getAddress().getPort());
    return boundAddress;
}

/** Wait for incommint connections on the bound port
 *
 **/
void StreamSockConnection::accept( void )
{
    StreamSocket from;

    from=_acceptSocket.accept();
    from.setDelay(false);
    _sockets.push_back(from);
}

/** connect a connection at the given address
 *
 * @param address    Host:Port
 *
 **/
void StreamSockConnection::connect(const std::string &address)
{
    std::string  host;
    UInt32       port;
    StreamSocket socket;

    interpreteAddress(address,host,port);
    socket.open();
    socket.setDelay(false);
    socket.connect(SocketAddress(host.c_str(),port));
    _sockets.push_back(socket);
}

/** get number of links
 **/
UInt32 StreamSockConnection::getChannelCount(void)
{
    return _sockets.size();
}

/** select channel for read
 *
 * A connection can have n links from which data can be read. So we
 * need to select one channel for exclusive read. 
 **/
void StreamSockConnection::selectChannel(void)
{
    Int32 maxnread=0,nread;
    SocketsT::iterator socket;
    SocketSelection selection,result;

    // only one socket?
    if(_sockets.size()==1)
    {
        _readSocket=_sockets[0];
        return;
    }

    // select socket with most data
    for(socket=_sockets.begin();
        socket!=_sockets.end();
        socket++)
    {
        nread=socket->getAvailable();
        if(maxnread < nread)
        {
            maxnread = nread;
            _readSocket=*socket;
        }
    }
    if(maxnread)
    {
        return;
    }

    // wait for first socket to deliver data
    for(socket=_sockets.begin();
        socket!=_sockets.end();
        socket++)
        selection.setRead(*socket);

    // select ok ?
    if(!selection.select(-1,result))
    {
        throw ReadError("no socket readable");
    }

    // find readable socket
    for(socket=_sockets.begin();!result.isSetRead(*socket);socket++);
    _readSocket=*socket;
    return;
}

/** \brief Get type of connection
 *
 * \return ConnectionType pointer
 **/
const ConnectionType *StreamSockConnection::getType()
{
    return &_type;
}

/*-------------------------- create ---------------------------------------*/

/** \brief create conneciton
 */

Connection *StreamSockConnection::create(void)
{
    return new StreamSockConnection();
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/** \brief Interprete an address std::string
 *
 * Hoststring syntax is host:port or :port or port
 *
 * \param address  Address string
 * \param host     Hostname
 * \param port     Port number
 **/
void StreamSockConnection::interpreteAddress(const std::string &address,
                                                   std::string &host,
                                                   UInt32      &port)
{
    UInt32 pos=address.find(':',0);
    
    if(pos>0)
    {
        host = address.substr(0,pos);
        port = atoi(address.substr(pos+1).c_str());
    }
    else
    {
        std::string::const_iterator i;
        for(i =address.begin();
            i!=address.end() && isdigit(*i);
            i++);
        if(i==address.end())
        {
            host="";
            port=atoi(address.c_str());
        }
        else
        {
            host=address;
            port=0;
        }
    }
}










