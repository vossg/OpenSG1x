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

#ifdef WIN32
#include <windows.h>
#include <WS2TCPIP.h>
#include <io.h>
#else
#include <sys/types.h>
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
#include <OSGStreamSocket.h>

OSG_BEGIN_NAMESPACE

/** \class StreamSocket
 *  \ingroup Network
 *  \brief Stream socket handler
 *  \author Marcus Roth
 *
 * This class is a Handler to connection oriented sockets. A call to
 * <EM>open</EM> will assing a stream socket and <EM>close</EM>
 * releases the socket. 
 *
 * Client example
 * <PRE>
 * char buffer[100];
 * StreamSocket s;
 * s.open();
 * s.connect(Address("serverhost.com",4567);
 * s.send(buffer,100);
 * s.close();
 * </PRE>
 *
 * Server example
 * <PRE>
 * char buffer[100];
 * StreamSocket s;
 * s.open();
 * s.bind(AnySocketAddress(4567);
 * c=s.accept();               // accept incomming client
 * c.recv(buffer,100);         // read client message
 * c.close();
 * s.close();
 * </PRE>
 **/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char StreamSocket::cvsid[] = "@(#)$Id:$";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/** \brief Constructor
 *
 * Use open to assign a system socket. No system socket is assigned by
 * the constructor.
 *
 * \see StreamSocket::open
 */
StreamSocket::StreamSocket():
    Socket()
{
}

/** \brief Copy constructor
 */
StreamSocket::StreamSocket(const StreamSocket &source):
    Socket(source)
{
}

/** \brief Assign a socket
 *
 * <CODE>Open</CODE> assignes a system socket to the StreamSocket. 
 *
 * \see Socket::close 
 */
void StreamSocket::open()
{
    _sd = ::socket(AF_INET, SOCK_STREAM, 0);
    if(_sd<0)
    {
        throw SocketError("socket()");
    }
}

/** \brief Accept incomming connection
 *
 * Accept incomming connection. Use the returned StreamSocket to 
 * communicate over the accepted communication. If the new StreamSocket
 * is no longer used, you have to close it.
 *
 * \param address   After accepting, address contains the remote address.
 *
 * \return New StreamSocket for client communication
 *
 * \see Socket::close StreamSocket::accept
 */
StreamSocket StreamSocket::acceptFrom(SocketAddress &address)
{
    StreamSocket client;
    SocketLenT len;
    
    len=address.getSockAddrSize();
    client._sd=::accept(_sd,
                        address.getSockAddr(),
                        &len);
    if(client._sd<0)
    {
        throw SocketError("accept()");
    }
    return client;
}

/** \brief Accept incomming connection
 *
 * Accept incomming connection. Use the returned StreamSocket to 
 * communicate over the accepted communication. If the new StreamSocket
 * is no longer used, you have to close it.
 *
 * \return New StreamSocket for client communication
 *
 * \see Socket::close StreamSocket::acceptFrom
 */
StreamSocket StreamSocket::accept()
{
    SocketAddress addr;
    return acceptFrom(addr);
}

/** \brief Set delay behavior
 *
 * A Stream socket doesen't send data immediately. Only if the internal
 * buffer contains enough data, an immediate write is forced. If
 * delay is set to false, then data is written always immediately.
 *
 * \param value  true = delay, false = no delay. true is the default
 */
void StreamSocket::setDelay(bool value)
{
    int rc,on;
    on=!value;
    rc=setsockopt(_sd, IPPROTO_TCP, TCP_NODELAY, 
                  (SocketOptT*)&on, sizeof(on));
    if(rc<0)
    {
        throw SocketError("setsockopt(,SOCK_STREAM,TCP_NODELAY)");
    }
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */
const StreamSocket & StreamSocket::operator =(const StreamSocket &source)
{
    _sd=source._sd;
    return *this;
}

/*-------------------------- comparison -----------------------------------*/

OSG_END_NAMESPACE







