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

OSG_USING_NAMESPACE

/** \defgroup Cluster OpenSG Cluster support
 * 
 * The cluster part of OpenSG includes all objects concerning with 
 * clustering and remote rendering
 **/

/** \class osg::ClusterWindow
 *  \ingroup Cluster
 *  \brief Abstract base class for cluster configurations
 *
 * A ClusterWindow describes a clustering algorithm. A ClusterWindow
 * inherits the ability to connect rendering servers and initiate
 * remote rendering. By configuring the cluster algorithm with an
 * OpenSG Window structure, it is possible to use cluster rendering
 * in the same way as rendering in a GLUT or Qt window.
 *
 **/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

ClusterWindow::ClusterWindow(void) :
    Inherited(),
    _connection(NULL),
    _remoteAspect(NULL),
    _statistics(NULL)
{
}

//! Copy Constructor

ClusterWindow::ClusterWindow(const ClusterWindow &source) :
    Inherited(source),
    _connection(NULL),
    _remoteAspect(NULL),
    _statistics(NULL)
{
}

//! Destructor

ClusterWindow::~ClusterWindow(void)
{
    if(_connection)
    {
        delete _connection;
    }
    if(_remoteAspect)
    {
        delete _remoteAspect;
    }
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void ClusterWindow::initMethod (void)
{
}

//! react to field changes

void ClusterWindow::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

//! output the instance for debug purposes

void ClusterWindow::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ClusterWindow NI" << endl;
}

void (*ClusterWindow::getFunctionByName ( const Char8 * ))()
{
    return NULL;
}

/*! init cluster window. connect to all servers
 */

void ClusterWindow::init( void )
{
    int i;
    MFString::iterator s;

    if(_connection)
    {
        SWARNING << "init called twice" << endl;
        return;
    }
    // create connection
    if(getConnectionType().empty())
    {
        setConnectionType("StreamSock");
    }
    _connection = ConnectionFactory::the().create(getConnectionType());
    if(_connection == NULL)
    {
        SFATAL << "Unknown connection type " << getConnectionType() << endl;
    }
    // create remote aspect
    _remoteAspect = new RemoteAspect();
    if(_statistics)
        _remoteAspect->setStatistics(_statistics);

    // connect to all servers
    for(s =getServers().begin();
        s!=getServers().end();
        s++)
    {
        DgramSocket      serviceSock;
        BinaryMessage    msg;
        string           respServer;
        string           respAddress;
        bool             retry=true;

        SINFO << "Connect to " << (*s) << endl;
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
                    SINFO << "Found at address " << respAddress << endl;
                    // connect to server
                    _connection->connect(respAddress);
                    retry=false;
                }
            }
            catch(exception &e)
            {
                SINFO << e.what() << endl;
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
        _connection->selectChannel();
        _connection->getValue(serverLittleEndian);
        if(serverLittleEndian != littleEndian)
        {
            forceNetworkOrder=true;
        }
    }
    _connection->putValue(forceNetworkOrder);
    _connection->flush();
    _connection->setNetworkOrder(forceNetworkOrder);
    if(forceNetworkOrder)
    {
        SLOG << "Run clustering in network order mode" << endl;
    }
    _firstFrame=true;
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
    if(_connection && _remoteAspect)
    {
        clientSwap();
    }
}

void ClusterWindow::renderAllViewports( RenderAction *action )
{
    if(_connection && _remoteAspect)
    {
        clientRender(action);
    }
}

void ClusterWindow::frameInit(void)
{
    if(_remoteAspect && _connection)
    {
        if(_firstFrame)
        {
            // send sync
            _remoteAspect->sendSync(*_connection);
            ChangeList cl;
            cl.clearAll();
            cl.merge(*Thread::getCurrentChangeList());
            Thread::getCurrentChangeList()->clearAll();
            // init client window
            clientInit();
            // last chance to modifie before sync
            clientPreSync();
            // send sync
            _remoteAspect->sendSync(*_connection);
            cl.merge(*Thread::getCurrentChangeList());
            Thread::getCurrentChangeList()->clearAll();
            Thread::getCurrentChangeList()->merge(cl);
            _firstFrame=false;
        }
        else
        {
            clientPreSync();
            _remoteAspect->sendSync(*_connection);
        }
    }
}

void ClusterWindow::frameExit(void)
{
}

/*-------------------------- statistics -----------------------------------*/

void ClusterWindow::setStatistics(StatCollector *statistics)
{
    _statistics = statistics;
    if(_remoteAspect)
        _remoteAspect->setStatistics(statistics);
}

/*----------------------------- client methods ----------------------------*/

/** init client window
 *  
 * In a derived cluster window this method is called before the first
 * sync with the rendering servers. There is no default action.
 *  
 **/

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

/*----------------------------- server methods ----------------------------*/

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

void ClusterWindow::serverSwap        ( WindowPtr window,
                                        UInt32 )
{
    window->swap();
    window->frameExit();
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
