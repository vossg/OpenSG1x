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
#include <WS2TCPIP.h>
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
#endif
#include <errno.h>
#include <stdio.h>
#include <math.h>
#include <map>
#include <OSGBase.h>
#include <OSGSocketAddress.h>
#include <OSGDgramSocket.h>
#include <OSGNetworkMessage.h>

OSG_BEGIN_NAMESPACE

/** \class DgramSocket
 *  \ingroup Network
 *  \brief Datagramm socket handler
 *  \author Marcus Roth
 *
 * This class is a handler to packet oriented socket.
 * <EM>open</EM> will assing a udp socket and <EM>close</EM>
 * releases the socket. 
 * Messages send with DgramSockets can be lost or the order in
 * which they arrive can be changed.
 *
 * Example:
 * <PRE>
 * char buffer[100];
 * DgramSocket s;
 * SocketAddress from;
 * s.open();
 * s.sendTo(buffer,10,SocketAddress("serverhost.com",4567));
 * s.recvFrom(buffer,10,from);
 * s.close();
 * </PRE>
 **/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char DgramSocket::cvsid[] = "@(#)$Id:$";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 *
 * Use open to assign a system socket. No system socket is assigned by
 * the constructor.
 *
 * \see DgramSocket::open
 **/
DgramSocket::DgramSocket():
    Socket()
{
}

/** \brief Copy constructor
 */
DgramSocket::DgramSocket(const DgramSocket &source):
    Socket(source)
{
}

/** \brief Assign a socket
 *
 * <CODE>Open</CODE> assignes a system socket to the StreamSocket. 
 *
 * \see Socket::close 
 */
void DgramSocket::open()
{
    _sd = socket(AF_INET, SOCK_DGRAM, 0);
    if(_sd<0)
    {
        throw SocketError("socket()");
    }
    // all dgram sockets are allowed to send broadcast
    int on = 1;
    if(::setsockopt(_sd, 
                    SOL_SOCKET, SO_BROADCAST, 
                    (SocketOptT*)&on, sizeof(on)) < 0)
    {
        throw SocketError("setsockopt(,SOL_SOCKET,SO_BROADCAST)");
    }
    // by default, multicast only in local network
    setTTL(1);
}

/** \brief read the given number of bytes 
 *
 * Read size bytes into the buffer. Wait until size Bytes are available
 * data maight be lossed, if size is smaller then the incomming package.
 * This situation will not be treated as an error.
 *
 * \param buf   Pointer to the data buffer.
 * \param size  Maximum count of bytes to read.
 * \param from  Will be overwritten with the address of the sender
 *
 * \see Socket::recvAvailable Socket::recv
 */
int DgramSocket::recvFrom(void *buf,int size,SocketAddress &from)
{
    int len;
    SocketLenT addrLen=from.getSockAddrSize();

    len=recvfrom(_sd,
                 (char*)buf,
                 size,
                 0,
                 from.getSockAddr(),
                 &addrLen);
    if(len<0)
    {
#if defined WIN32
        if(getError()==WSAECONNRESET)
        {
            throw SocketConnReset("recvfrom");
        }
        if(getError()==WSAEMSGSIZE)
        {
            len=size;
        }
        else
#endif
        throw SocketError("recvfrom()");
    }
    return len;
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
 * \param from  Will be overwritten with the address of the sender
 *
 * \see recv Socket::recv
 */
int DgramSocket::peekFrom(void *buf,int size,SocketAddress &from)
{
    int len;
    SocketLenT addrLen=from.getSockAddrSize();

    len=recvfrom(_sd,
                 (char*)buf,
                 size,
                 MSG_PEEK,
                 from.getSockAddr(),
                 &addrLen);
    if(len==-1)
    {
#if defined WIN32
        if(getError()==WSAECONNRESET)
        {
            throw SocketConnReset("recvfrom");
        }
        if(getError()==WSAEMSGSIZE)
        {
            len=size;
        }
        else
#endif
        throw SocketError("recvfrom()");
    }
    return len;
}

/** \brief Write the given number of bytes to the socket
 *
 * Write size bytes to the socket. This method maight block, if the
 * output buffer is full.
 *
 * \param buf   Pointer to the data buffer.
 * \param size  number of bytes to write
 * \param to    destination address
 *
 * \see recv Socket::send
 */
int DgramSocket::sendTo(const void *buf,int size,const SocketAddress &to)
{
    int len;

    // send Request
    len=sendto(_sd,
               (const char*)buf,size,
               0,
               to.getSockAddr(),
               to.getSockAddrSize());
    if(len == -1)
    {
        throw SocketError("sendto()");
    }
    return len;
}

/** \brief Join to a multicast group
 *
 * The socket will receive all messages from the given multicast address
 * It is possible to join more then on goup.
 *
 * \param group   Multicast group 
 * \param interf  Which network interface to use. (Default AnySocketAddress)
 */
void DgramSocket::join(const SocketAddress &group,const SocketAddress &interf)
{
    struct ip_mreq joinAddr;
    int rc;

    // group to join
    joinAddr.imr_multiaddr.s_addr
    = ((sockaddr_in*)group.getSockAddr())->sin_addr.s_addr;
    // interface that joins. (equal to bind address)
    joinAddr.imr_interface
    = ((struct sockaddr_in*)interf.getSockAddr())->sin_addr;
    rc=setsockopt(_sd,
                  IPPROTO_IP,
                  IP_ADD_MEMBERSHIP,
                  (SocketOptT*)&joinAddr,
                  sizeof(joinAddr));
    if(rc < 0)
    {
        throw SocketError("setsockopt(IPPROTO_IP,IP_ADD_MEMBERSHIP)");
    }
}

/** \brief Leave a multicast group
 *
 * Don't receive messages from the given group.
 *
 * \param group   Multicast group 
 * \param interf  Which network interface to use. (Default AnySocketAddress)
 */
void DgramSocket::leave(const SocketAddress &group,const SocketAddress &interf)
{
    struct ip_mreq joinAddr;
    int rc;

    // group to join
    joinAddr.imr_multiaddr.s_addr
    = ((sockaddr_in*)group.getSockAddr())->sin_addr.s_addr;
    // interface that joins. (equal to bind address)
    joinAddr.imr_interface
    = ((sockaddr_in*)interf.getSockAddr())->sin_addr;
    rc=setsockopt(_sd,
                  IPPROTO_IP,
                  IP_DROP_MEMBERSHIP,
                  (SocketOptT*)&joinAddr,
                  sizeof(joinAddr));
    if(rc < 0)
    {
        throw SocketError("setsockopt(IPPROTO_IP,IP_DROP_MEMBERSHIP)");
    }
}

/** \brief Set TTL for broadcast and multicast
 *
 * Defines how many routers a package will pass until it is deleted.
 * 0 = local host, 1 = local network, ...
 *
 * \param ttl     time to live
 */
void DgramSocket::setTTL(unsigned char ttl)
{
    int rc=setsockopt(_sd, IPPROTO_IP,IP_MULTICAST_TTL,
                      (SocketOptT*)&ttl,sizeof(ttl));
    if(rc<0)
    {
        throw SocketError("setsockopt(IPPROTO_IP,IP_MULTICAST_TTL)");
    }
}

/** \brief Send a NetworkMessage to an address
 *
 * Workes like send, but buffer and size is taken from the NetworkMessage
 *
 * \param msg   Reference to the NetworkMessage
 * \param to    Destination address
 *
 * \see Socket::send
 */
int DgramSocket::sendTo(NetworkMessage &msg,const SocketAddress &to)
{
    NetworkMessage::Header &hdr=msg.getHeader();
    hdr.size=htonl(msg.getSize());
    return sendTo(msg.getBuffer(),msg.getSize(),to);
}

/** \brief Receive a NetworkMessage
 *
 * Workes like recv, but buffer and size is taken from the NetworkMessage
 *
 * \param msg   Reference to the NetworkMessage
 * \param to    Source address
 *
 * \see Socket::recv
 */
int DgramSocket::recvFrom(NetworkMessage &msg,SocketAddress &from)
{
    NetworkMessage::Header hdr;
    peek(&hdr,sizeof(hdr));
    msg.setSize(ntohl(hdr.size));
    return recvFrom(msg.getBuffer(),msg.getSize(),from);
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */
const DgramSocket & DgramSocket::operator =(const DgramSocket &source)
{
    _sd=source._sd;
    return *this;
}

OSG_END_NAMESPACE
