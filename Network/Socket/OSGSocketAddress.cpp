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
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#endif
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "OSGBase.h"
#include "OSGSocketAddress.h"
#include "OSGSocketException.h"

OSG_BEGIN_NAMESPACE

using namespace std;

/** \class SocketAddress
 *  \ingroup Network
 *  \brief Network address
 *  \author Marcus Roth
 *
 * The class SocketAddress holds an ip-address and a socket port number.
 * It is used to connect, and sendTo Sockets.
 * 
 * Usage:
 * <PRE>
 * SocketAddress a("colossus.world.com",3334);
 * socket.bind(a);
 * cout << a.getHost() << endl;
 * cout << a.getPort() << endl;
 * </PRE>
 **/

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: $";
    static Char8 cvsid_hpp       [] = OSG_SOCKET_ADDRESS_HEADER_CVSID;
}

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 *
 * Create a socket address for the given port and host.
 *
 * \param host  Host as hostname or as number 111.222.333.444.
 * \param port  Port id
 */
SocketAddress::SocketAddress(const char *host,int port)
{
    memset(&_sockaddr,0,sizeof(_sockaddr));
    _sockaddr.sin_family = AF_INET;
    if(host)
        setHost(string(host));
    setPort(port);
}

/** \brief Constructor
 *
 * Create a socket with predefined type. E.g. ANY is used to bind
 * a socket to all interfaces. BROADCAST chreates a broadcast
 * address
 *
 * \param type  ANY or BROADCAST
 * \param port  Port id
 */
SocketAddress::SocketAddress(SocketAddress::Type type,int port)
{
    _sockaddr.sin_family = AF_INET;
    switch(type)
    {
        case ANY:
            _sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
            break;
        case BROADCAST:
            _sockaddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
            break;
        default:
            _sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    setPort(port);
}

/** \brief copy Constructor
 */
SocketAddress::SocketAddress(const SocketAddress &source)
{
    _sockaddr = source._sockaddr;
}

/** \brief Destructor
 */
SocketAddress::~SocketAddress()
{
}

/** \brief set the port number
 *
 * \param port  Port number as an int
 */
void SocketAddress::setPort(int port)
{
    _sockaddr.sin_port = htons( port );
}

/** \brief set host name
 *
 * \param host   Host as name or number
 */
void SocketAddress::setHost(const string &host)
{
    struct hostent *hent;
    char const *c;

    // number or name ?
    for(c=host.c_str();
        *c!='\0' && (isdigit(*c) || *c == '.');
        c++);
    if(! *c )
    {
        // inet_aton(const char *cp, struct in_addr *pin);

        // ip number was given
        _sockaddr.sin_addr.s_addr = inet_addr(host.c_str());
    }
    else
    {
        // get address of host by name
        hent = gethostbyname(host.c_str());
        if(hent == NULL)
        {
            throw SocketHostError("gethostbyname()");
        }
        // set address
        _sockaddr.sin_addr = *(struct in_addr *) hent->h_addr;
    }
}

/** \brief Get host as number string
 *
 * \result   Host as number e.g. 133.33.44.55
 */
string SocketAddress::getHost() const
{
    return string(inet_ntoa(_sockaddr.sin_addr));
}

/** \brief Get host as name
 *
 * \result   Hostname if found. Otherwise number string.
 */
string SocketAddress::getHostByName() const
{
    struct hostent *hent;
    string result;

    hent=gethostbyaddr((SocketAddrT*)getSockAddr(),
                       getSockAddrSize(),AF_INET);
    if(hent == NULL)
    {
        // if no host assigned or host unknown
        // then return ip address
        result=inet_ntoa(_sockaddr.sin_addr);
    }
    else
    {
        result=hent->h_name;
    }
    return result;
}

/** \brief Get a pointer to the sockaddr struct
 *
 * \result   sockaddr struct
 */
sockaddr *SocketAddress::getSockAddr() const
{
    return const_cast<struct sockaddr *>(
        reinterpret_cast<const struct sockaddr *>(&_sockaddr));
}

/** \brief Get the size of the sockaddr struct
 *
 * \result   size of sockaddr
 */
int SocketAddress::getSockAddrSize() const
{
    return sizeof(struct sockaddr_in);
}

/** \brief Get port number
 *
 * \result   port as int
 */
int SocketAddress::getPort() const
{
    return ntohs(_sockaddr.sin_port);
}

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/** \brief compare equal
 */
bool SocketAddress::operator == (const SocketAddress &other) const
{
    return _sockaddr.sin_addr.s_addr == other._sockaddr.sin_addr.s_addr &&
           _sockaddr.sin_port        == other._sockaddr.sin_port;
}

/** \brief compare not equal
 */
bool SocketAddress::operator != (const SocketAddress &other) const
{
    return ! (*this == other);
}

/** \brief compare less
 */
bool SocketAddress::operator < (const SocketAddress &other) const
{
    return _sockaddr.sin_addr.s_addr < other._sockaddr.sin_addr.s_addr ||
    (
        _sockaddr.sin_addr.s_addr == other._sockaddr.sin_addr.s_addr &&
        _sockaddr.sin_port        <  other._sockaddr.sin_port
    );
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSG_END_NAMESPACE
