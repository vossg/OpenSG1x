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

#include <sys/types.h>
#ifdef WIN32
#include <windows.h>
#include <io.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#endif
#include <errno.h>
#include <stdio.h>
#include <math.h>
#include <map>
#include <OSGBase.h>
#include <OSGSocketAddress.h>
#include <OSGSocket.h>
#include <OSGSocketSelection.h>
#include <OSGNetworkMessage.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class Socket
    \ingroup Network
    \brief Abstract network socket handler
    \author Marcus Roth

Socket baseclass. The Socket class wraps a socket descriptor. This
class has no additional state variables. It is only h handle to the
underlaying descriptor. Class createion and destruction has no
influence to any descriptor. Use open to assign a descriptor and
close to remove it from the system. If this class is copied, then
there are to classes which uses the same descriptor. This is
ok until you call close for one of this classes.
One purpose of this implementation is to hide the differences between
Windows and Unix sockets. Calls to this class should behave equally
on all systems. As a result, some methods will not work as an 
experienced Windows ore Unix programmer maight expect. Please refere
to the function docu to get details about this.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

int Socket::initialized=0;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/** \brief Get last occured error
 */
int Socket::getError()
{
#ifdef WIN32
    return WSAGetLastError();
#else
    return errno;
#endif
}

/** \brief Get last host error
 */
int Socket::getHostError()
{
#ifdef WIN32
    return WSAGetLastError();
#else
    return h_errno;
#endif
}

/** \brief Get last occured error as string
 */
string Socket::getErrorStr()
{
    const char *err=NULL;

#ifdef WIN32
    switch(getError())
    {
    case WSAEINTR: err= "WSAEINTR"; break;
        case WSAEBADF: err= "WSAEBADF"; break;
        case WSAEFAULT: err= "WSAEFAULT"; break; 
        case WSAEINVAL: err= "WSAEINVAL"; break; 
        case WSAEMFILE: err= "WSAEMFILE"; break; 
        case WSAEWOULDBLOCK: err= "WSAEWOULDBLOCK"; break; 
        case WSAEINPROGRESS: err= "WSAEINPROGRESS"; break; 
        case WSAEALREADY: err= "WSAEALREADY"; break; 
        case WSAENOTSOCK: err= "WSAENOTSOCK"; break; 
        case WSAEDESTADDRREQ: err= "WSAEDESTADDRREQ"; break; 
        case WSAEMSGSIZE: err= "WSAEMSGSIZE"; break; 
        case WSAEPROTOTYPE: err= "WSAEPROTOTYPE"; break; 
        case WSAENOPROTOOPT: err= "WSAENOPROTOOPT"; break; 
        case WSAEPROTONOSUPPORT: err= "WSAEPROTONOSUPPORT"; break; 
        case WSAESOCKTNOSUPPORT: err= "WSAESOCKTNOSUPPORT"; break; 
        case WSAEOPNOTSUPP: err= "WSAEOPNOTSUPP"; break; 
        case WSAEPFNOSUPPORT: err= "WSAEPFNOSUPPORT"; break; 
        case WSAEAFNOSUPPORT: err= "WSAEAFNOSUPPORT"; break; 
        case WSAEADDRINUSE: err= "WSAEADDRINUSE"; break; 
        case WSAEADDRNOTAVAIL: err= "WSAEADDRNOTAVAIL"; break; 
        case WSAENETDOWN: err= "WSAENETDOWN"; break; 
        case WSAENETUNREACH: err= "WSAENETUNREACH"; break; 
        case WSAENETRESET: err= "WSAENETRESET"; break; 
        case WSAECONNABORTED: err= "WSAECONNABORTED"; break; 
        case WSAECONNRESET: err= "WSAECONNRESET"; break; 
        case WSAENOBUFS: err= "WSAENOBUFS"; break; 
        case WSAEISCONN: err= "WSAEISCONN"; break; 
        case WSAENOTCONN: err= "WSAENOTCONN"; break; 
        case WSAESHUTDOWN: err= "WSAESHUTDOWN"; break; 
        case WSAETOOMANYREFS: err= "WSAETOOMANYREFS"; break; 
        case WSAETIMEDOUT: err= "WSAETIMEDOUT"; break; 
        case WSAECONNREFUSED: err= "WSAECONNREFUSED"; break; 
        case WSAELOOP: err= "WSAELOOP"; break; 
        case WSAENAMETOOLONG: err= "WSAENAMETOOLONG"; break; 
        case WSAEHOSTDOWN: err= "WSAEHOSTDOWN"; break; 
        case WSAEHOSTUNREACH: err= "WSAEHOSTUNREACH"; break; 
        case WSASYSNOTREADY: err= "WSASYSNOTREADY"; break; 
        case WSAVERNOTSUPPORTED: err= "WSAVERNOTSUPPORTED"; break; 
        case WSANOTINITIALISED: err= "WSANOTINITIALISED"; break; 
        case WSAHOST_NOT_FOUND: err= "WSAHOST_NOT_FOUND"; break; 
        case WSATRY_AGAIN: err= "WSATRY_AGAIN"; break; 
        case WSANO_RECOVERY: err= "WSANO_RECOVERY"; break; 
        case WSANO_DATA: err= "WSANO_DATA"; break; 
    }
#else
    err=strerror(getError());
#endif
    if(err)
        return string(err);
    else
        return string("Unknown error");
}

/** \brief Get last occured host error as string
 */
string Socket::getHostErrorStr()
{
    const char *err;
#if defined(WIN32) || defined(__hpux)
    err = strerror(getHostError());
#else
    err = hstrerror(getHostError());
#endif
    if(err)
        return string(err);
    else
        return string("Unknown error");
}

/** \brief Constructor
 *
 * Create a new Socket class. A valid socket descriptor will be assigned
 * by calling open on a derived Socket class e.g. StreamSocket or
 * DgramSocket. 
 * On Windows WSAStartup is called by the first socket createn.
 */
Socket::Socket():
    _sd(-1)
{
    if(!initialized)
    {
        initialized=1;
#ifdef WIN32
        WSADATA wsaData;
        
        WORD wVersionRequested = MAKEWORD( 2, 2 ); 
        if(WSAStartup( wVersionRequested, &wsaData )!=0)
        {
            throw SocketError("WSAStartup()");
        }
#endif
    }
}

/** \brief Copy constructor
 */
Socket::Socket(const Socket &source):
    _sd(source._sd)
{
}

/** \brief Destructor
 *
 * The Socket class is only a descriptor to the socket. By destruction
 * of this class, the socket remains open.
 */
Socket::~Socket()
{
}

/** \brief close socket
 */
void Socket::close()
{
#ifdef WIN32
    ::closesocket(_sd);
#else
    ::close(_sd);
#endif
}

/** \brief read date even if less then size available
 *
 * Read the data from the in buffer to a maximun length of size.
 * don't wait until size bytes are available.
 *
 * \param buf   Pointer to the data buffer.
 * \param size  Maximum count of bytes to read.
 *
 * \see recv 
 */
int Socket::recvAvailable(void *buf,int size)
{
    int len;

    len=::recv(_sd,(char*)buf,size,0);
    if(len==-1)
    {
#if defined WIN32
        if(getError()==WSAECONNRESET)
        {
            throw SocketConnReset("recvAvailable()");
        }
#endif
        throw SocketError("recv()");
    }
    return len;
}

/** \brief read the given number of bytes 
 *
 * Read size bytes into the buffer. Wait until size Bytes are available
 * On Dgram sockets data maight be lossed, if size is smaller then the
 * incomming package. This situation will not be treated as an error.
 *
 * \param buf   Pointer to the data buffer.
 * \param size  Maximum count of bytes to read.
 *
 * \see recvAvailable recvFrom
 */
int Socket::recv(void *buf,int size)
{
    int readSize;
    int pos=0;

    while(size)
    {
        readSize=::recv(_sd,((char*)buf)+pos,size,0);
        if(readSize<0)
        {
#if defined WIN32
            if(getError()==WSAECONNRESET)
            {
                throw SocketConnReset("recv");
            }
            if(getError()==WSAEMSGSIZE)
            {
                readSize=size;
            }
            else
#endif
            throw SocketError("recv()");
        }
        if(readSize==0)
        {
            return 0;
        }
        size-=readSize;
        pos +=readSize;
    }
    return pos;
}

/** \brief peek the given number of bytes 
 *
 * Read size bytes into the buffer. Wait until size Bytes are available
 * On Dgram sockets data maight be lossed, if size is smaller then the
 * incomming package. This situation will not be treated as an error.
 * The read bytes will not be removed from the in buffer. A call to
 * recv after peek will result in the same data.
 *
 * \param buf   Pointer to the data buffer.
 * \param size  Maximum count of bytes to read.
 *
 * \see recv recvAvailable
 */
int Socket::peek(void *buf,int size)
{
    int readSize;
    int pos=0;

    do
    {
        readSize=::recv(_sd,((char*)buf)+pos,size,MSG_PEEK);
        if(readSize<0)
        {
#if defined WIN32
            if(getError()==WSAECONNRESET)
            {
                throw SocketConnReset("peek");
            }
            if(getError()==WSAEMSGSIZE)
            {
                readSize=size;
            }
            else
#endif
            throw SocketError("peek");
        }
        if(readSize==0)
        {
            return 0;
        }
    }
    while(readSize!=size);
    return readSize;
}

/** \brief Write the given number of bytes to the socket
 *
 * Write size bytes to the socket. This method maight block, if the
 * output buffer is full.
 *
 * \param buf   Pointer to the data buffer.
 * \param size  number of bytes to write
 */
int Socket::send(const void *buf,int size)
{
    int writeSize;
    int pos=0;
    while(size)
    {
        writeSize=::send(_sd,((const char*)buf)+pos,size,0);
        if(writeSize==-1)
        {
            throw SocketError("send()");
        }
        if(writeSize==0)
        {
            return 0;
        }
        size-=writeSize;
        pos+=writeSize;
    }
    return pos;
}

/** \brief Send a NetworkMessage
 *
 * Workes like send, but buffer and size is taken from the NetworkMessage
 *
 * \param msg   Reference to the NetworkMessage
 *
 * \see send
 */
int Socket::send(NetworkMessage &msg)
{
    NetworkMessage::Header &hdr=msg.getHeader();
    hdr.size=htonl(msg.getSize());
    return send(msg.getBuffer(),msg.getSize());
}

/** \brief Receive a NetworkMessage
 *
 * Workes like recv, but buffer and size is taken from the NetworkMessage
 *
 * \param msg   Reference to the NetworkMessage
 *
 * \see recv
 */
int Socket::recv(NetworkMessage &msg)
{
    NetworkMessage::Header hdr;
    peek(&hdr,sizeof(hdr));
    msg.setSize(ntohl(hdr.size));
    return recv(msg.getBuffer(),msg.getSize());
}

/** \brief Bind a socket to a given SocketAddress
 *
 * It is possible to <br> bind a Socket to a special network interface ore
 * to all availabel interfaces.
 * <PRE>
 * sock.bind(AnySocketAddress(23344));           Bind Socket to port 23344 
 * sock.bind(Address("123.223.112.33",0);  Bind to the given adapter
 * sock.bind(AnySocketAddress(0));               Bind to a free port      
 * port = sock.getAddress().getPort();     Get bound port
 * </PRE>
 *
 * \param address   SocketAddress to which the socket should be bound
 *
 * \see recv
 */
void Socket::bind(const SocketAddress &address)
{
    SocketAddress result=address;
    
    if( ::bind(_sd,
               result.getSockAddr(),
               result.getSockAddrSize()) < 0)
    {
        if(getError()==
#if defined WIN32
            WSAEADDRINUSE 
#else
			EADDRINUSE
#endif
		)
        {
            throw SocketInUse("bind()");
        }
        else
        {
            throw SocketError("bind()");
        }
    }
}

/** \brief set queue length for incomming connection requests
 *
 * \param maxPending   queue length, default is 5
 */
void Socket::listen(int maxPending)
{
    if(::listen(_sd,maxPending)<0)
    {
        throw SocketError("listen()");
    }
}

/** \brief connect to the given address
 *
 * After connect, all send data will be transfered to the address. 
 *
 * \param address   destination SocketAddress
 */
void Socket::connect(const SocketAddress &address)
{
    if( ::connect(_sd,
                  address.getSockAddr(),
                  address.getSockAddrSize()) )
    {
        throw SocketError("connect()");
    }
}

/** \brief Enable, disable reuse port behavior
 *
 * If reuse port is true, then more then on process or thread is able
 * to bind to the same port. This makes sense for multicast or braodcast
 * sockets. For StreamSockets this feature can be used to avoid
 * the <EM>Socket in use</EM> message on not propperly closed ports.
 *
 * \param value   true, enables and false disables socket reusage
 */
void Socket::setReusePort(bool value)
{
    int v=(int)value;
#ifdef SO_REUSEPORT
    ::setsockopt(_sd,SOL_SOCKET,SO_REUSEPORT,(SocketOptT*)&v,sizeof(v));
#endif
    ::setsockopt(_sd,SOL_SOCKET,SO_REUSEADDR,(SocketOptT*)&v,sizeof(v));
}

/** \brief Enable, disable blocking
 *
 * By default all recv, send, accept calls will block until the executeion
 * is finished. This behavior can be swithed off bei setting blocking to
 * false. This will lead to a more difficult programming. An easier 
 * way to get non blocking behavior is to use SocketSelections or
 * waitReadable, waitWritable. These methods provide a timeout
 * for waiting.
 *
 * \param value   true, enables and false disables blocking
 *
 * \see Socket::waitReadable Socket::waitWritable SocketSelection
 */
void Socket::setBlocking(bool value)
{
#ifndef WIN32
    int val=0;
    
    if(value==false)
        val=O_NDELAY;
    if (fcntl(_sd, F_GETFL, &val) < 0) 
    {
        throw SocketError("fcntl()");
    }    
    val|=O_NDELAY;
    if(value)
    {
        val^=O_NDELAY;
    }
    if (fcntl(_sd, F_SETFL, val) < 0) 
    {
        throw SocketError("fcntl()");
    }    
#else
    u_long ulVal = !value;
    if( (ioctlsocket(_sd, FIONBIO, &ulVal)) != 0) 
    {
        throw SocketError("ioctlsocket()");
    }    
#endif
}

/** \brief Get bound SocketAddress
 *
 * \return SocketAddress to which the Socket is bound
 *
 * \see SocketAddress 
 */
SocketAddress Socket::getAddress()
{
    SocketAddress result;
    SocketLenT len;

    len=result.getSockAddrSize();
    if( ::getsockname(_sd,result.getSockAddr(),&len) < 0)
    {
        throw SocketError("getsockname()");
    }
    return result;
}

/** \brief Set the internal read buffer size
 *
 * \param size   Size in bytes of the internal read buffer
 *
 * \see Socket::getReadBufferSize
 */
void Socket::setReadBufferSize(int size)
{
    int v=(int)size;
    ::setsockopt(_sd,SOL_SOCKET,SO_RCVBUF,(SocketOptT*)&v,sizeof(v));
}

/** \brief Set the internal write buffer size
 *
 * \param size    Size in bytes of the internal write buffer
 *
 * \see Socket::getWriteBufferSize
 */
void Socket::setWriteBufferSize(int size)
{
    int v=(int)size;
    ::setsockopt(_sd,SOL_SOCKET,SO_SNDBUF,(SocketOptT*)&v,sizeof(v));
}

/** \brief Get internal read buffer size
 *
 * \return Size in bytes of the internal read buffer
 *
 * \see Socket::setReadBufferSize
 */
int Socket::getReadBufferSize() 
{
    int v;
    SocketLenT len=sizeof(v);
    ::getsockopt(_sd,SOL_SOCKET,SO_RCVBUF,(SocketOptT*)&v,&len);
    return v;
}

/** \brief Get internal write buffer size
 *
 * \return Size in bytes of the internal write buffer
 *
 * \see Socket::setWriteBufferSize
 */
int Socket::getWriteBufferSize() 
{
    int v;
    SocketLenT len=sizeof(v);
    ::getsockopt(_sd,SOL_SOCKET,SO_SNDBUF,(SocketOptT*)&v,&len);
    return v;
}

/** \brief Get number of bytes in the internal read buffer
 *
 * \return Number of bytes in the internal read buffer
 */
int Socket::getAvailable(void)
{
#ifndef WIN32
    int value;
    if(::ioctl(_sd, FIONREAD, &value)<0)
    {    
        throw SocketError("ioctl()");
    }
    return value;
#else
    u_long ulVal;
    if( (ioctlsocket(_sd, FIONREAD, &ulVal)) != 0) 
    {    
        throw SocketError("ioctlsocket()");
    }
    return (int)ulVal;
#endif
}

/** \brief Wait until recv or accept will not block
 *
 * \param duration   Maximum number of secons to wait. -1: wait unlimited.
 *
 * \return true, if data is abailable
 */
bool Socket::waitReadable(double duration)
{
    SocketSelection selection;
    selection.setRead(*this);
    if(selection.select(duration)==1)
        return true;
    else
        return false;
}

/** \brief Wait until send will not block
 *
 * \param duration   Maximum number of secons to wait. -1: wait unlimited.
 *
 * \return true, if send will not block
 */
bool Socket::waitWritable(double duration)
{
    SocketSelection selection;
    selection.setWrite(*this);
    if(selection.select(duration)==1)
        return true;
    else
        return false;
}

/** \brief assignment
 */

const Socket & Socket::operator =(const Socket &source)
{
    _sd=source._sd;
    return *this;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: $";
    static Char8 cvsid_hpp       [] = OSG_SOCKET_HEADER_CVSID;
}

