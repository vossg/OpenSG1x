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

#include <OSGConfig.h>
#include <OSGSystemDef.h>
#include "OSGClusterWindow.h"
#include "OSGDgramSocket.h"
#include "OSGStreamSocket.h"
#include "OSGRemoteAspect.h"
#include "OSGConnection.h"
#include "OSGBinaryMessage.h"
#include "OSGRemoteAspect.h"
#include "OSGConnectionFactory.h"
#include "OSGClusterNetwork.h"

OSG_USING_NAMESPACE

/** \class osg::ClusterWindow
 *  \ingroup GrpSystemCluster
 *  \brief Abstract base class for cluster configurations
 *
 * A ClusterWindow describes a clustering algorithm. A ClusterWindow
 * inherits the ability to connect rendering servers and initiate
 * remote rendering. By configuring the cluster algorithm with an
 * OpenSG Window structure, it is possible to use cluster rendering
 * in the same way as rendering in a GLUT or Qt window.
 *
 **/

/*-------------------------------------------------------------------------*/
/*                          window functions                               */

//! react to field changes

void ClusterWindow::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

//! output the instance for debug purposes

void ClusterWindow::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ClusterWindow NI" << std::endl;
}

void (*ClusterWindow::getFunctionByName ( const Char8 * ))()
{
    return NULL;
}

/*! init cluster window. connect to all servers
 */

void ClusterWindow::init( void )
{
    Connection   *connection;
    RemoteAspect *remoteAspect;
    int i;
    MFString::iterator s;

    if(getNetwork()->getMainConnection())
    {
        SWARNING << "init called twice" << std::endl;
        return;
    }
    // create connection
    if(getConnectionType().empty())
    {
        setConnectionType("StreamSock");
    }
    connection=ConnectionFactory::the().create(getConnectionType());
    if(connection == NULL)
    {
        SFATAL << "Unknown connection type " 
               << getConnectionType() 
               << std::endl;
    }
    getNetwork()->setMainConnection(connection);
    // create remote aspect
    remoteAspect = new RemoteAspect();
    getNetwork()->setAspect(remoteAspect);
    if(_statistics)
        remoteAspect->setStatistics(_statistics);

    // connect to all servers
    for(s =getServers().begin();
        s!=getServers().end();
        s++)
    {
        DgramSocket      serviceSock;
        BinaryMessage    msg;
        std::string      respServer;
        std::string      respAddress;
        bool             retry=true;

        SINFO << "Connect to " << (*s) << std::endl;
        serviceSock.open();
        while(retry)
        {
            try
            {
                // find server
                do
                {
                    msg.clear();
                    msg.putString(*s);
                    msg.putString(getConnectionType());
                    
                    if(_sfServiceAddress.getValue().size() != 0)
                    {
                        SINFO << "send request to:" << 
                            _sfServiceAddress.getValue()
                              << std::endl;
                        serviceSock.sendTo(
                            msg,SocketAddress(
                                _sfServiceAddress.getValue().c_str(),
                                getServicePort()));
                    }
                    SINFO << "send request to:" 
                          << SocketAddress(SocketAddress::BROADCAST,
                                           getServicePort()).getHost().c_str()
                          << std::endl;
                    serviceSock.sendTo(
                        msg,SocketAddress(SocketAddress::BROADCAST,
                                          getServicePort()));
                }
                while(serviceSock.waitReadable(2)==false);
                serviceSock.recv(msg);
                msg.getString(respServer);
                msg.getString(respAddress);
                if(respServer == *s)
                {
                    SINFO << "Found at address " << respAddress << std::endl;
                    // connect to server
                    connection->connect(respAddress);
                    retry=false;
                }
            }
            catch(OSG_STDEXCEPTION_NAMESPACE::exception &e)
            {
                SINFO << e.what() << std::endl;
            }
        }
        serviceSock.close();
    }
    // determine byte order
    UInt8 serverLittleEndian;
    UInt8 forceNetworkOrder=false;
#if BYTE_ORDER == LITTLE_ENDIAN
    UInt8 littleEndian = true;
#else
    UInt8 littleEndian = false;
#endif
    for(i=0;i<getServers().size();++i)
    {
        connection->selectChannel();
        connection->getValue(serverLittleEndian);
        if(serverLittleEndian != littleEndian)
        {
            forceNetworkOrder=true;
        }
    }
    connection->putValue(forceNetworkOrder);
    connection->flush();
    connection->setNetworkOrder(forceNetworkOrder);
    if(forceNetworkOrder)
    {
        SLOG << "Run clustering in network order mode" << std::endl;
    }
    // send alive all 2 seconds
    connection->setSendAliveInterval(2);
    // never request alive
    connection->setReadAliveTimeout(-1);
}

void ClusterWindow::render( RenderAction *action )
{
    activate();
    frameInit();
    renderAllViewports( action );
    swap();
    frameExit();
}

void ClusterWindow::activate( void )
{
}

void ClusterWindow::deactivate( void )
{
}

void ClusterWindow::swap( void )
{
    if(getNetwork()->getMainConnection() && getNetwork()->getAspect())
    {
        clientSwap();
    }
}

void ClusterWindow::renderAllViewports( RenderAction *action )
{
    if(getNetwork()->getMainConnection() && getNetwork()->getAspect())
    {
        clientRender(action);
    }
}

void ClusterWindow::frameInit(void)
{
    ClusterWindowPtr ptr(this);
    Connection   *connection  =getNetwork()->getMainConnection();
    RemoteAspect *remoteAspect=getNetwork()->getAspect();

    if(remoteAspect && connection)
    {
        if(_firstFrame)
        {
            beginEditCP(ptr,ClusterWindow::FrameCountFieldMask);
            setFrameCount(0);
            endEditCP(ptr,ClusterWindow::FrameCountFieldMask);
            // send sync
            remoteAspect->sendSync(*connection);
            ChangeList cl;
            cl.clearAll();
            cl.merge(*Thread::getCurrentChangeList());
            Thread::getCurrentChangeList()->clearAll();
            // init client window
            clientInit();
            // last chance to modifie before sync
            clientPreSync();
            // send sync
            remoteAspect->sendSync(*connection);
            cl.merge(*Thread::getCurrentChangeList());
            Thread::getCurrentChangeList()->clearAll();
            Thread::getCurrentChangeList()->merge(cl);
            _firstFrame=false;
        }
        else
        {
            beginEditCP(ptr,ClusterWindow::FrameCountFieldMask);
            getFrameCount()++;
            endEditCP(ptr,ClusterWindow::FrameCountFieldMask);
            clientPreSync();
            remoteAspect->sendSync(*connection);
        }
    }
}

void ClusterWindow::frameExit(void)
{
}

/*-------------------------------------------------------------------------*/
/*                          statistics                                     */

void ClusterWindow::setStatistics(StatCollector *statistics)
{
    _statistics = statistics;
    if(getNetwork()->getAspect())
        getNetwork()->getAspect()->setStatistics(statistics);
}

/*-------------------------------------------------------------------------*/
/*                         client methods                                  */

/*! init client window. In a derived cluster window this method is called
 *  before the first sync with the rendering servers. There is no default 
 *  action.
 */
void ClusterWindow::clientInit( void )
{
}

/** client frame before sync
 *  
 * In a derived cluster window this method is called before 
 * sync with the rendering servers. Default aciton is to activate
 * and init the client window.
 **/

void ClusterWindow::clientPreSync( void )
{
    if(getClientWindow() != NullFC)
    {
        getClientWindow()->activate();
        getClientWindow()->frameInit();
    }
}

/** initiate client rendering
 *  
 * In a derived cluster window this method is called after the 
 * sync with all rendering servers. Default aciton is to render all
 * viewports of the client window.
 **/

void ClusterWindow::clientRender( RenderAction *action )
{
    if(getClientWindow() != NullFC)
    {
        getClientWindow()->renderAllViewports( action );
    }
}

/** swap client window
 *  
 * In a derived cluster window this method is called after rendering
 * Default aciton is to swap the local client window.
 **/

void ClusterWindow::clientSwap( void )
{
    if(getClientWindow() != NullFC)
    {
        getClientWindow()->swap( );
        getClientWindow()->frameExit();
    }
}

/*-------------------------------------------------------------------------*/
/*                         server methods                                  */

/** initialise the cluster window on the server side
 *  
 * This method is called after the first sync.
 *  
 * \param window     server render window
 * \param id         server id
 **/

void ClusterWindow::serverInit( WindowPtr ,
                                UInt32 )
{
}

/** render server window
 *  
 * This method is called after synchronisation of all changes with the
 * rendering client. Default action is to render all viewports with the
 * given action
 *  
 * !param window     server render window
 * !param id         server id
 * !param action     action
 **/

void ClusterWindow::serverRender( WindowPtr window,
                                  UInt32 ,
                                  RenderAction *action )
{
    window->activate();
    window->frameInit();
    window->renderAllViewports( action );
}

/** swap server window
 *  
 * <code>serverSwap</code> is called after rendering. Default action is
 * to swap the rendering window. 
 *  
 * !param window     server render window
 * !param id         server id
 * !param connection connection to client
 **/
void ClusterWindow::serverSwap( WindowPtr window,
                                UInt32 )
{
    window->swap();
    window->frameExit();
}

/*-------------------------------------------------------------------------*/
/*                         constructor / destructor                        */

//! Constructor

ClusterWindow::ClusterWindow(void) :
     Inherited(),
    _firstFrame(true),
     _statistics(NULL),
    _network(NULL)
{
}

//! Copy Constructor

ClusterWindow::ClusterWindow(const ClusterWindow &source) :
    Inherited(source),
    _firstFrame(true),
    _statistics(NULL),
    _network(NULL)
{
}

//! Destructor

ClusterWindow::~ClusterWindow(void)
{
    if(_network)
        subRefP(_network);
    _network=NULL;
}

/*-------------------------------------------------------------------------*/
/*                           connection pool                               */

/*! Get connection pool
 */
ClusterNetwork *ClusterWindow::getNetwork(void)
{
    if(!_network)
    {
        ClusterWindowPtr ptr(this);
        _network=ClusterNetwork::getInstance(ptr.getFieldContainerId());
        addRefP(_network);
    }
    return _network;
}

/*! initialize the static features of the class, e.g. action callbacks
 */
void ClusterWindow::initMethod (void)
{
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
    static char cvsid_cpp[] = "@(#)$Id: $";
    static char cvsid_hpp[] = OSGCLUSTERWINDOW_HEADER_CVSID;
    static char cvsid_inl[] = OSGCLUSTERWINDOW_INLINE_CVSID;
}
