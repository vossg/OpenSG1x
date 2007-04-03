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
#include <OSGGL.h>
#include <OSGNodePtr.h>
#include <OSGTileCameraDecorator.h>
#include <OSGViewport.h>
#include <OSGGeometry.h>
#include <OSGStereoBufferViewport.h>
#include <OSGRenderAction.h>
#include "OSGSortFirstWindow.h"
#include "OSGClusterViewBuffer.h"
#include "OSGConnection.h"
#include "OSGRenderNode.h"
#include "OSGTileGeometryLoad.h"

OSG_USING_NAMESPACE

ClusterViewBuffer SortFirstWindow::_bufferHandler;

// #define USE_VPORT_SLICES

/*! \class osg::SortFirstWindow
    \ingroup GrpSystemCluster
    Cluster rendering configuration for sort first image composition
*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

SortFirstWindow::SortFirstWindow(void) :
    Inherited(),
    _tileLoadBalancer(NULL),
    _renderNode(NULL)
{
}

//! Copy Constructor

SortFirstWindow::SortFirstWindow(const SortFirstWindow &source) :
    Inherited(source),
    _tileLoadBalancer(NULL),
    _renderNode(NULL)
{
}

//! Destructor

SortFirstWindow::~SortFirstWindow(void)
{
    if(_tileLoadBalancer)
        delete _tileLoadBalancer;
    if(_renderNode)
        delete _renderNode;
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void SortFirstWindow::initMethod (void)
{
}

//! react to field changes

void SortFirstWindow::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

//! output the instance for debug purposes

void SortFirstWindow::dump(      UInt32    , 
                           const BitVector ) const
{
    SLOG << "Dump SortFirstWindow NI" << std::endl;
}

/*----------------------------- server methods ----------------------------*/

/** transfer server cababilities to the client
 *
 **/
void SortFirstWindow::serverInit( WindowPtr serverWindow,
                                  UInt32 id)
{
#if USE_VPORT_SLICES

#else
    UInt32 sync;
    RenderNode renderNode;
    Connection *connection=getNetwork()->getMainConnection();

    // create cluster node information
    // get performance
    renderNode.determinePerformance(serverWindow);
    renderNode.dump();
    // transfer to client for load balancing
    connection->putValue(id);
    renderNode.copyToBin(*connection);
    connection->flush();
    connection->selectChannel();
    connection->getValue(sync);
#endif
}

/** update server window
 *
 * todo: enamble frustum culling if error is removed
 **/
void SortFirstWindow::serverRender( WindowPtr serverWindow,
                                    UInt32 id,
                                    RenderActionBase *action )
{
    TileCameraDecoratorPtr deco;
    ViewportPtr serverPort;
    ViewportPtr clientPort;
    UInt32 sv,cv,regionStart;
    UInt32 vpWidth;
    UInt32 vpHeight;

    // duplicate viewports
    for(cv=0,sv=0;cv<getPort().size();cv++)
    {
        clientPort = getPort()[cv];
        if(serverWindow->getPort().size() <= sv)
        {
            // create new port
            //serverPort = StereoBufferViewport::create();
            serverPort = ViewportPtr::dcast(clientPort->shallowCopy());
            deco=TileCameraDecorator::create();
            beginEditCP(serverWindow);
            serverWindow->addPort(serverPort);
            serverPort->setCamera(deco);
            endEditCP(serverWindow);
        }
        else
        {
            serverPort = serverWindow->getPort()[sv];
            deco=TileCameraDecoratorPtr::dcast(serverPort->getCamera());
            if(serverWindow->getPort()[sv]->getType() != 
               clientPort->getType())
            {
                // there is a viewport with the wrong type
                subRefCP(serverWindow->getPort()[sv]);
                serverPort = ViewportPtr::dcast(clientPort->shallowCopy());
                beginEditCP(serverWindow);
                serverWindow->getPort()[sv] = serverPort;
                serverPort->setCamera(deco);
                endEditCP(serverWindow);
            }
            else
            {
                deco=TileCameraDecoratorPtr::dcast(serverPort->getCamera());
            }
            //serverPort = serverWindow->getPort()[sv];
            //deco=TileCameraDecoratorPtr::dcast(serverPort->getCamera());
        }

        // duplicate values
        beginEditCP(serverPort);
        regionStart=cv * getServers().size() * 4 + id * 4;
        serverPort->setSize( 
            Real32(getRegion()[regionStart+0] + clientPort->getPixelLeft()),
            Real32(getRegion()[regionStart+1] + clientPort->getPixelBottom()),
            Real32(getRegion()[regionStart+2] + clientPort->getPixelLeft()),
            Real32(getRegion()[regionStart+3] + clientPort->getPixelBottom()));

        serverPort->setRoot      ( clientPort->getRoot()       );
        serverPort->setBackground( clientPort->getBackground() );
        serverPort->getMFForegrounds()->setValues( clientPort->getForegrounds() );
        serverPort->setTravMask  ( clientPort->getTravMask()   );
        endEditCP(serverPort);

        // calculate tile parameters
        vpWidth =clientPort->getPixelWidth();
        vpHeight=clientPort->getPixelHeight();
        beginEditCP(deco);
        deco->setFullWidth ( vpWidth );
        deco->setFullHeight( vpHeight );
        deco->setSize( getRegion()[ regionStart+0 ]/(float)vpWidth,
                       getRegion()[ regionStart+1 ]/(float)vpHeight,
                       getRegion()[ regionStart+2 ]/(float)vpWidth,
                       getRegion()[ regionStart+3 ]/(float)vpHeight );
        deco->setDecoratee( clientPort->getCamera() );
        endEditCP(deco);
        sv++;
    }
    // remove unused ports
    while(serverWindow->getPort().size()>sv)
    {
        serverWindow->subPort(sv);
    }

    Inherited::serverRender(serverWindow,id,action);

    // compression type
    if(getCompose())
    {
        if(getCompression().empty())
        {
            _bufferHandler.setImgTransType(NULL);
        }
        else
        {
            _bufferHandler.setImgTransType(getCompression().c_str());
        }
        if(getSubtileSize())
        {
            _bufferHandler.setSubtileSize(getSubtileSize());
        }
    }

#if 1
    glDisable(GL_SCISSOR_TEST);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
#endif

    // render the viewports
    serverWindow->activate();
    serverWindow->frameInit();
    action->setWindow( serverWindow.getCPtr() );
    for(sv=0;sv<serverWindow->getPort().size();++sv)
    {
        ViewportPtr vp=serverWindow->getPort()[sv];
        vp->render( action );

        // send resulting image
        if(getCompose())
        {
            // activate the appropriate viewport to retrieve image
            vp->activate();

            // send image
            _bufferHandler.send(
                *getNetwork()->getMainPointConnection(),
                ClusterViewBuffer::RGB,
                vp->getPixelLeft(),
                vp->getPixelBottom(),
                vp->getPixelRight(),
                vp->getPixelTop(),
                0,0);

            // deactivate the viewport
            vp->deactivate();
        }
    }
}

/*! send image to client
 */
void SortFirstWindow::serverSwap( WindowPtr window,
                                  UInt32 )
{
    if(!getCompose())
    {
        Connection *connection=getNetwork()->getMainConnection();
        connection->signal();
        connection->wait();
    }
    window->swap();
}

/*----------------------------- client methods ----------------------------*/

/*! read server cababilities
 */

void SortFirstWindow::clientInit( void )
{
#if USE_VPORT_SLICES

#else
    UInt32               id;
    RenderNode           renderNode;
    GroupConnection     *connection = getNetwork()->getMainGroupConnection();
    Connection::Channel  channel;

    _tileLoadBalancer=new TileLoadBalancer(getUseFaceDistribution());
    // read all node infos
    for(UInt32 i=0;i<connection->getChannelCount();++i)
    {
        printf("%d\n",i);
        channel = connection->selectChannel();
        connection->subSelection(channel);
        connection->getValue(id);
        renderNode.copyFromBin(*connection);
        renderNode.dump();
        _tileLoadBalancer->addRenderNode(renderNode,id);    
    }
    connection->resetSelection();
    printf("end\n");
    // sync servers
    connection->putValue(id);
    connection->flush();
#endif

    Inherited::clientInit();
}

/*! client frame init
 */

void SortFirstWindow::clientPreSync( void )
{
    SortFirstWindowPtr ptr=SortFirstWindowPtr(this);
    if(getCompose())
    {
        // get window size from client window
        if(getClientWindow() != NullFC)
        {
            if(getWidth()  != getClientWindow()->getWidth() ||
               getHeight() != getClientWindow()->getHeight())
            {
                beginEditCP(ptr,
                            Window::WidthFieldMask|
                            Window::HeightFieldMask);
                {
                    setSize(getClientWindow()->getWidth(),
                            getClientWindow()->getHeight());
                }
                endEditCP(ptr,
                          Window::WidthFieldMask|
                          Window::HeightFieldMask);
            }
        }
    }
#if 0
    else
    {
        beginEditCP(ptr,
                    Window::WidthFieldMask|
                    Window::HeightFieldMask);
        {
            setSize(1280,
                    1024);
        }
        endEditCP(ptr,
                  Window::WidthFieldMask|
                  Window::HeightFieldMask);
    }
#endif
    UInt32 i;
    UInt32 cv;
    TileLoadBalancer::ResultT region;
    
    beginEditCP(ptr,SortFirstWindow::RegionFieldMask);
    getRegion().clear();
#if USE_VPORT_SLICES
    for(cv=0;cv<getPort().size();cv++)
    {
        int s=getServers().size();
        for(i=0;i<s;i++)
        {
            getRegion().push_back(i/float(s)*getWidth());
            getRegion().push_back(0);
            getRegion().push_back((i+1)/float(s)*getWidth());
            getRegion().push_back(1*getHeight());
        }
    }
#else
    for(cv=0;cv<getPort().size();cv++)
    {
        _tileLoadBalancer->update( getPort()[cv]->getRoot() );
        _tileLoadBalancer->balance(getPort()[cv],
                              false,
                              region);
        for(i=0;i<getServers().size();i++)
        {
            getRegion().push_back(region[i].x1);
            getRegion().push_back(region[i].y1);
            getRegion().push_back(region[i].x2);
            getRegion().push_back(region[i].y2);
        }
    }
#endif

    endEditCP(ptr,SortFirstWindow::RegionFieldMask);

    Inherited::clientPreSync();
}

/*! client rendering
 *  
 *  one tile is rendered by the client
 */

void SortFirstWindow::clientRender( RenderActionBase *  /* action */ )
{
//    Inherited::clientRender(action);
}

/*! show data
 */

void SortFirstWindow::clientSwap( void )
{
    UInt32 cv;
    GroupConnection *connection=getNetwork()->getMainGroupConnection();
    if(getCompose())
    {
        if(getClientWindow()!=NullFC)
        {
            // receive all viewports
            for(cv=0;cv<getPort().size();++cv)
            {
                ViewportPtr vp=getPort()[cv];

                // activate the appropriate viewport to receive image
                vp->activate();

                // receive image
                _bufferHandler.recv(*connection);

                // deactivate the viewport
                vp->deactivate();
            }
            Inherited::clientSwap();
        }
    }
    else
    {
        connection->wait();
        connection->signal();
    }
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
    static char cvsid_cpp[] = "@(#)$Id:$";
    static char cvsid_hpp[] = OSGSORTFIRSTWINDOW_HEADER_CVSID;
    static char cvsid_inl[] = OSGSORTFIRSTWINDOW_INLINE_CVSID;
}
