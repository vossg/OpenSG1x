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

#include "OSGConfig.h"
#include "OSGThread.h"
#include "OSGThreadManager.h"
#include "OSGClusterServer.h"
#include "OSGConnectionFactory.h"
#include "OSGDgramSocket.h"
#include "OSGClusterWindow.h"
#include "OSGBinaryMessage.h"

OSG_USING_NAMESPACE

/** \class osg::ClusterServer
 *  \ingroup Cluster
 *  \brief Cluster rendering server
 *
 * A ClusterServer is responsible for syncronizing all client changes.
 * Each cluster renderer can offer it's service by a symbolic name.
 * So it is possible to have a server called "left" or "right".
 * The server uses a local Qt or GLUT window for rendering. 
 * <pre>
 * // create a server
 * GLUTWindowPtr window=GLUTWindow::create();
 * server = new ClusterServer(window,"server1","Multicast");
 * // wait for clients to connect
 * server->init();
 * ...
 * // render
 * server->render(ract);
 * </pre>
 **/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

/*! Constructor 
 *
 * \param window          rendering window. e.g. a Qt or GLUT window 
 * \param serviceName     wait for connections that request this name
 * \param connectionType  network type. e.g. "Multicast"
 * \param address         address to wait for connections
 * \param servicePort     port to wait for connections
 *
 */
ClusterServer::ClusterServer(           WindowPtr  window,
                             const std::string    &serviceName,
                             const std::string    &connectionType,
                             const std::string    &address,
                                        UInt32    servicePort):
    _window(window),
    _connection(NULL),
    _address(address),
    _clusterWindow(),
    _aspect(NULL),
    _serviceName(serviceName),
    _servicePort(servicePort),
    _serviceAvailable(false),
    _serverId(0),
    _connectionType(connectionType)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

/*! Destructor
 *
 * Disconnect from all connected rendering servers
 */
ClusterServer::~ClusterServer(void)
{
    try
    {
        if(_clusterWindow!=NullFC)
        {
            _clusterWindow=NullFC;
        }
        if(_connection)
            delete _connection;
        if(_aspect)
            delete _aspect;
    }
    catch(...)
    {
    }
}

/*-------------------------------------------------------------------------*/
/*                             Class specific                              */


/*! start server
 *
 * Start cluster server and wait for a client to connect. This method
 * will return after a client connection or an error situation.
 */
void ClusterServer::start()
{
    Thread                  *serviceThread;
    OSG::FieldContainerType *fct;

    // create connection
    _connection = ConnectionFactory::the().create(_connectionType);
    if(_connection == NULL)
    {
        SFATAL << "Unknown connection type " << _connectionType << std::endl;
        return;
    }

    // create aspect
    _aspect = new RemoteAspect();

    // bind connection
    _address = _connection->bind(_address);

    // start service proc
    _serviceAvailable=true;
    serviceThread=dynamic_cast<Thread*>(ThreadManager::the()->getThread(NULL));
    serviceThread->runFunction( serviceProc, 0, (void *) (this) );

    // register interrest for all changed cluster windows
    for(UInt32 i=0;i<OSG::TypeFactory::the()->getNumTypes();++i)
    {
        fct=OSG::FieldContainerFactory::the()->findType(i);
        if(fct && fct->isDerivedFrom(ClusterWindow::getClassType()))
        {
            _aspect->registerChanged(
                *fct,
                osgTypedMethodFunctor2ObjPtrCPtrRef
                <
                bool,
                ClusterServer,
                FieldContainerPtr,
                RemoteAspect     *
                >(this,&ClusterServer::windowChanged));
        }
    }
    // accept incomming connections
    try {
        UInt8                    forceNetworkOrder;
#if BYTE_ORDER == LITTLE_ENDIAN
        UInt8                    littleEndian = true;
#else
        UInt8                    littleEndian = false;
#endif
        _connection->accept();
        // determine network order
        _connection->putValue(littleEndian);
        _connection->flush();
        _connection->selectChannel();
        _connection->getValue(forceNetworkOrder);
        _connection->setNetworkOrder(forceNetworkOrder);
        _serviceAvailable=false;

        SINFO << "Connection accepted " << _address << std::endl;

        Thread::join(serviceThread);
    } 
    catch(...)
    {
        _serviceAvailable=false;
        throw;
    }
}


/*! start server
 *
 * Start cluster server and wait for a client to connect. This method
 * will return after a client connection or an error situation.
 */
void ClusterServer::stop()
{
    if(_clusterWindow!=NullFC)
    {
        _clusterWindow=NullFC;
    }
    if(_connection)
    {
        delete _connection;
        _connection=NULL;
    }
    if(_aspect)
    {
        delete _aspect;
        _aspect=NULL;
    }
}

/*! render server window
 *
 * Synchronize all field containers with the client and call 
 * <code>serverInit</code>, <code>serverRender</code> and
 * <code>serverSwap</code> for the cluster window.
 * The cluster server uses the first synced ClusterWindow that 
 * contains the name of this server. <code>serverInit</code> is
 * called after the first ClusterWindow sync. 
 *
 * \param action   RenderAction to use for rendering
 *
 * \todo Sync RenderAciton contents
 */
void ClusterServer::render(RenderAction *action)
{
    // do we have a cluster window?
    if(_clusterWindow==NullFC)
    {
        do
        {
            // recive 
            _aspect->receiveSync(*_connection);
        }
        while(_clusterWindow==NullFC);
        // get server id
        for(_serverId=0;
            _clusterWindow->getServers()[_serverId] != _serviceName &&
                _serverId<_clusterWindow->getServers().size();
            _serverId++);
        // server connected and cluster window found
        SINFO << "Start server " << _serviceName 
              << " with id "     << _serverId 
              << std::endl;
        // initialize server window 
        _clusterWindow->setConnection(_connection);
        _clusterWindow->setRemoteAspect(_aspect);
        _clusterWindow->serverInit(_window,_serverId);
    }
    // sync with render clinet
    _aspect->receiveSync(*_connection);
    _clusterWindow->serverRender( _window,_serverId,action );
    _clusterWindow->serverSwap  ( _window,_serverId );
}

/*! clusterWindow changed callback
 *
 * this is a callback functor. It is called for each change of 
 * a ClusterWindow.
 */

bool ClusterServer::windowChanged(FieldContainerPtr& fcp,
                                  RemoteAspect *)
{
    ClusterWindowPtr window=ClusterWindowPtr::dcast(fcp);

    if(window->getServers().size())
    {
        if(window->getServers().find(_serviceName) == 
           window->getServers().end())
        {
            SWARNING << "wrong window" << std::endl;
        }
        else
        {
            _clusterWindow=window;
        }
    }
    return true;
}

/*! tell address of server requested over broadcast
 *
 * serviceProc is a static class function that is processed in a
 * seperate thread. It tells all requesting clients on which
 * network address this server is waiting for connecitons.
 *
 * We do this in a thread because not all network types are
 * able to set a timeout for accept. The service thread tells
 * clients the address on wich the accept is expected.
 * After a successful connection the service thread will be
 * termnated.
 *
 * \param arg   Pointer to the ClusterServer
 */

void *ClusterServer::serviceProc(void *arg)
{
    ClusterServer *server = static_cast<ClusterServer *>(arg);
    BinaryMessage  msg;
    DgramSocket    serviceSock;
    SocketAddress  addr;
    std::string    service;
    std::string    connectionType;
    UInt32         readable;

    SINFO << "Waiting for request of "
          << server->_serviceName
          << " "
          << server->_connection->getType()->getName()
          << std::endl;

    try
    {
        serviceSock.open();
        serviceSock.setReusePort(true);
        serviceSock.bind(SocketAddress(SocketAddress::ANY,
                                       server->_servicePort));

        while(server->_serviceAvailable)
        {        
            try
            {
                do
                {
                    readable = serviceSock.waitReadable(.1);
                }
                while((readable                  == false) && 
                      (server->_serviceAvailable == true )  );

                if(readable)
                {
                    serviceSock.recvFrom(msg,addr);

                    service        = msg.getString();
                    connectionType = msg.getString();

                    SINFO << "Request for " 
                          << service << " " 
                          << connectionType 
                          << std::endl;

                    if(service        == 
                                     server->_serviceName                    &&
                       connectionType == 
                                     server->_connection->getType()->getName())
                    {
                        msg.clear    (                );
                        msg.putString(service         );
                        msg.putString(server->_address);

                        serviceSock.sendTo(msg, addr);

                        SINFO << "Response " 
                              << server->_address 
                              << std::endl;
                    }
                }
            }
            catch(OSG_STDEXCEPTION_NAMESPACE::exception &e)
            {
                SWARNING << e.what() << std::endl;
            }
        }

        serviceSock.close();
    }
    catch(OSG_STDEXCEPTION_NAMESPACE::exception &e)
    {
        SFATAL << e.what() << ": Server is now unknown" << std::endl;
    }

    SINFO << "Stop service thread" << std::endl;

    return NULL;
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
    static Char8 cvsid_hpp[] = OSG_CLUSTERSERVERHEADER_CVSID;
}
