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

#ifndef _MULTICASTCONNECTION_H_
#define _MULTICASTCONNECTION_H_
#ifdef __sgi
#pragma once
#endif

#include <set>

#include <OSGBaseTypes.h>
#include <OSGTime.h>
#include <OSGBase.h>
#include <OSGConnection.h>
#include <OSGDgramSocket.h>
#include <OSGSocketAddress.h>
#include <OSGConnectionType.h>

OSG_BEGIN_NAMESPACE

class BaseThread;

//#define MULTICAST_BUFFER_COUNT 31
//#define MULTICAST_BUFFER_SIZE  8192

#define MULTICAST_BUFFER_SIZE  65000

class OSG_BASE_DLLMAPPING MulticastConnection : public Connection
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
 
    MulticastConnection(int port=0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~MulticastConnection(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               communication functions                        */
    /*! \{                                                                 */

          std::string     bind           (const std::string &address);
          void            accept         (void                      );
          void            connect        (const std::string &address);
          UInt32          getChannelCount(void                      );
          void            selectChannel  (           UInt32  channel);
    const ConnectionType *getType        (void                      );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   create                                     */
    /*! \{                                                                 */

    static Connection *create(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    enum UDPHeaderType {
        ACK_REQUEST,
        ACK,
        NAK,
        DATA,
        ALIVE,
        CONNECT,
        CLOSED
    };

    struct UDPHeader
    {
        UInt32 seqNumber;
        UInt8  type;
    };
    struct UDPBuffer
    {
        UDPHeader header;
        union 
        {
            UInt8 data[MULTICAST_BUFFER_SIZE];
            UInt32 member;
        };
    };

    /*---------------------------------------------------------------------*/
    /*! \name                  read/write                                  */
    /*! \{                                                                 */

    virtual void readBuffer (void);
    virtual void writeBuffer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  address handling                            */
    /*! \{                                                                 */
 
    void          interpreteAddress(const std::string &address,
                                          std::string &group,
                                               UInt32 &port,
                                               UInt32 &member  );
    SocketAddress findFreeGroup    (void                       );
    void          addUsedGroup     (const SocketAddress &group );
    void          subUsedGroup     (const SocketAddress &group );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    std::vector<SocketAddress>        _channelAddress;
    std::vector<UInt32>               _channelSeqNumber;
    UInt32                            _channel;
    UInt32                            _seqNumber;
    UDPBuffer                         _readBuffer;
    UDPBuffer                         _writeBuffer;
    Time                              _maxWaitForAck;
    Time                              _waitForAck;
    Time                              _maxWaitForSync;
    DgramSocket                       _socket;
    DgramSocket                       _inSocket;
    DgramSocket                       _groupSocket;
    DgramSocket                       _aliveSocket;
    SocketAddress                     _destination;
    UInt32                            _member;
    SocketAddress                     _multicastGroupAddress;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    /*---------------------------------------------------------------------*/
    /*! \name                   Private members                            */
    /*! \{                                                                 */

    BaseThread           *_aliveThread;
    bool                 _stopAliveThread;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Alive thread handling                        */
    /*! \{                                                                 */

           void startAliveThread(void     );
           void stopAliveThread (void     );
    static void aliveProc       (void *arg);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Variable                             */
    /*! \{                                                                 */

    static ConnectionType             _type;
    static std::set<std::string>      _usedGroup;
    static std::string                _defaultGroup;
    static UInt32                     _defaultPort;

    /*! \}                                                                 */

    typedef Connection Inherited;

	/*!\brief prohibit default function (move to 'public' if needed) */
    MulticastConnection(const MulticastConnection &source);
    void operator =(const MulticastConnection &source);
};

// class pointer
typedef MulticastConnection *MulticastConnectionP;

OSG_END_NAMESPACE

#define OSG_MULTICASTCONNECTIONHEADER_CVSID "@(#)$Id:$"

#endif /* _MULTICASTCONNECTION_H_ */
