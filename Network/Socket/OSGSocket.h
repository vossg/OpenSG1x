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

#ifndef _SOCKET_H_
#define _SOCKET_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGBase.h"
#include "OSGSocketException.h"
#include "OSGSocketAddress.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------
class NetworkMessage;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

class OSG_BASE_DLLMAPPING Socket
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Socket();
    Socket(const Socket &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~Socket();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Socket access                                */
    /*! \{                                                                 */

    virtual void  open              (                                   )=0;
    void          close             (      void                         );
    int           recv              (      void *buf,int size           );
    int           recvAvailable     (      void *buf,int size           );
    int           peek              (      void *buf,int size           );
    int           send              (const void *buf,int size           );
    void          bind              (const SocketAddress &address=
                                     SocketAddress(SocketAddress::ANY)  );
    void          listen            (int maxPending=10                  );
    void          connect           (const SocketAddress &address       );
    void          setReusePort      (bool value                         );
    void          setBlocking       (bool value                         );
    SocketAddress getAddress        (void                               );
    void          setReadBufferSize (int size                           );
    void          setWriteBufferSize(int size                           );
    int           getReadBufferSize (void                               );
    int           getWriteBufferSize(void                               );
    int           getAvailable      (void                               );
    bool          waitReadable      (double duration                    );
    bool          waitWritable      (double duration                    );
    int           send              (NetworkMessage &msg                 );
    int           recv              (NetworkMessage &msg                 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Assignment                              */
    /*! \{                                                                 */

	const Socket & operator =(const Socket &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Error information                       */
    /*! \{                                                                 */

    static int         getError();
    static int         getHostError();
    static string      getErrorStr();
    static string      getHostErrorStr();

    /*! \}                                                                 */
  protected:

    /** Socket option type 
     *  Used to hide the different interface implementations
     **/
#if defined WIN32
    typedef char FAR  SocketOptT;
#else
    typedef void      SocketOptT;
#endif

    /** Socket length type 
     *  Used to hide the different interface implementations
     **/
#if defined __linux
    typedef socklen_t SocketLenT;
#else
    typedef int       SocketLenT;
#endif

    int _sd;

  private:

    friend class SocketSelection;

    static int  initialized;

};

OSG_END_NAMESPACE

#define OSG_SOCKET_HEADER_CVSID "@(#)$Id: $"

#endif
