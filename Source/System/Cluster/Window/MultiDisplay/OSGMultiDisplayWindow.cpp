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
#include <OSGViewport.h>
#include <OSGTileCameraDecorator.h>
#include <OSGBaseFunctions.h>
#include <OSGStereoBufferViewport.h>
#include "OSGMultiDisplayWindow.h"
#include "OSGConnection.h"
#include "OSGNode.h"

#define FAST_SYNC 0

OSG_USING_NAMESPACE

/*! \class osg::MultiDisplayWindow
 *  \ingroup GrpSystemCluster
 */

/*----------------------- constructors & destructors ----------------------*/

/*! Constructor
 */
MultiDisplayWindow::MultiDisplayWindow(void) :
    Inherited()
{
}

/*! Copy Constructor
 */
MultiDisplayWindow::MultiDisplayWindow(const MultiDisplayWindow &source) :
    Inherited(source)
{
}

/*! Destructor
 */
MultiDisplayWindow::~MultiDisplayWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

/*! initialize the static features of the class, e.g. action callbacks
 */
void MultiDisplayWindow::initMethod (void)
{
}

/*! react to field changes
 */
void MultiDisplayWindow::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*! output the instance for debug purposes
 */
void MultiDisplayWindow::dump(      UInt32    , 
                              const BitVector ) const
{
    SLOG << "hServers:" << getHServers() << " "
         << "vServers:" << getVServers() << std::endl;
}

/*----------------------------- server methods ----------------------------*/

/*! initialise the cluster window on the server side. This method is
     called after the first sync.
 */
void MultiDisplayWindow::serverInit( WindowPtr ,
                                     UInt32 )
{
}

/*! render server window
 *  
 *  update all viewport parameters and render local viewports
 *  Width and height of the whole window are calculated by 
 *  multiplieing the local window size by hServers and vServers.
 */
void MultiDisplayWindow::serverRender( WindowPtr serverWindow,
                                       UInt32 id,
                                       RenderActionBase *action )
{
    TileCameraDecoratorPtr deco;
    ViewportPtr serverPort;
    ViewportPtr clientPort;
    StereoBufferViewportPtr clientStereoPort;
    UInt32 sv,cv;
    Int32 l,r,t,b;
    Int32 cleft,cright,ctop,cbottom;

    if(!getHServers())
    {
        setHServers(getServers().size());
    }
    if(!getVServers())
    {
        setVServers(1);
    }
    UInt32 row   =id/getHServers();
    UInt32 column=id%getHServers();
    // calculate width and height from local width and height
    UInt32 width  = serverWindow->getWidth() ;
    UInt32 height = serverWindow->getHeight();
    if(getWidth()==0)
    {
        setWidth( width*getHServers() );
    }
    if(getHeight()==0)
    {
        setHeight( height*getVServers() );
    }
    Int32 left   = column * width  - column * getXOverlap();
    Int32 bottom = row    * height - row    * getYOverlap();
    Int32 right  = left   + width  - 1;
    Int32 top    = bottom + height - 1;
    Real32 scaleCWidth  = ((width - getXOverlap()) * (getHServers() - 1) + width) / (float)getWidth();
    Real32 scaleCHeight = ((height - getYOverlap())* (getVServers() - 1) + height)/ (float)getHeight();

    // duplicate viewports
    for(cv=0,sv=0;cv<getPort().size();cv++)
    {
        clientPort = getPort()[cv];
        clientStereoPort = StereoBufferViewportPtr::dcast(clientPort);
        cleft   = (Int32)(clientPort->getPixelLeft()      * scaleCWidth)   ;
        cbottom = (Int32)(clientPort->getPixelBottom()    * scaleCHeight)  ;
        cright  = (Int32)((clientPort->getPixelRight()+1) * scaleCWidth) -1;
        ctop    = (Int32)((clientPort->getPixelTop()+1)   * scaleCHeight)-1;
        if(cright  < left   ||
           cleft   > right  ||
           ctop    < bottom ||
           cbottom > top      )
        {
            // invisible on this server screen
            continue;
        }
        // calculate overlapping viewport
        l = osgMax(cleft  ,left  ) - left;
        b = osgMax(cbottom,bottom) - bottom;
        r = osgMin(cright ,right ) - left;
        t = osgMin(ctop   ,top   ) - bottom;
        if(serverWindow->getPort().size() <= sv)
        {
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
        }
        // duplicate values
        beginEditCP(serverPort);
        serverPort->setSize(Real32(l),Real32(b),Real32(r),Real32(t));
        // use pixel even if pixel = 1
        if(serverPort->getLeft() == 1.0)
            serverPort->setLeft(1.0001);
        if(serverPort->getRight() == 1.0)
            serverPort->setRight(1.0001);
        if(serverPort->getTop() == 1.0)
            serverPort->setTop(1.0001);
        if(serverPort->getBottom() == 1.0)
            serverPort->setBottom(1.0001);
        serverPort->setRoot      ( clientPort->getRoot()       );
        serverPort->setBackground( clientPort->getBackground() );
        serverPort->getMFForegrounds()->setValues( clientPort->getForegrounds() );        
        serverPort->setTravMask  ( clientPort->getTravMask()   );
        endEditCP(serverPort);

        // calculate tile parameters
        beginEditCP(deco);
        deco->setFullWidth ( cright-cleft );
        deco->setFullHeight( ctop-cbottom );
        deco->setSize( ( l+left-cleft     ) / (float)( cright-cleft ),
                       ( b+bottom-cbottom ) / (float)( ctop-cbottom ),
                       ( r+left-cleft     ) / (float)( cright-cleft ),
                       ( t+bottom-cbottom ) / (float)( ctop-cbottom ) );
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
}

/*! swap server window
 */
void MultiDisplayWindow::serverSwap( WindowPtr window,UInt32 id )
{
    Connection *connection;

    // clear command buffers
    UInt8 pixel[3];
    glReadPixels(0,0,
                 1,1,
                 GL_RGB,GL_UNSIGNED_BYTE,
                 pixel);
    glFinish();

#if !FAST_SYNC
    connection=getNetwork()->getMainConnection();
    if(!getInterleave())
    {
        // tell client that we are finish
        connection->signal();
        // wait for swap
        connection->wait();
    }
#endif
    Inherited::serverSwap(window,id);
}

/*----------------------------- client methods ----------------------------*/

/*! init client window
 *  
 *  If manageClientViewports is set, then all viewports from the
 *  cluster window are duplcated to the client window. 
 */
void MultiDisplayWindow::clientInit( void )
{
    bool             changed = false;
    ViewportPtr      vp,cvp;

    if(getManageClientViewports() == false ||
       getClientWindow() == NullFC)
        return;

    // check if something changed
    if(getPort().size() == getClientWindow()->getPort().size())
    {
        for(UInt32 v = 0 ; v < getPort().size() && !changed ; v++)
        {
            vp  = getPort(v);
            cvp = getClientWindow()->getPort(v);
            if( vp->getRoot() != cvp->getRoot() ||
                vp->getLeft() != cvp->getLeft() ||
                vp->getRight() != cvp->getRight() ||
                vp->getBottom() != cvp->getBottom() ||
                vp->getTop() != cvp->getTop() ||
                vp->getBackground() != cvp->getBackground() ||
                vp->getForegrounds().size() != cvp->getForegrounds().size() )
                changed = true;
        }
    }
    else
    {
        changed = true;
    }

    if(changed)
    {
        beginEditCP(getClientWindow());
        // remove all viewports
        while(getClientWindow()->getPort().size())
        {
            vp = getClientWindow()->getPort(0);
            getClientWindow()->subPort(0);
            subRefCP(vp);
        }
        // duplicate viewports
        for(UInt32 v=0 ; v<getPort().size() ;v++)
        {
            getClientWindow()->addPort(ViewportPtr::dcast(getPort(v)->shallowCopy()));
        }
        endEditCP(getClientWindow());
    }
}
    
/*! render client window
 */
void MultiDisplayWindow::clientSwap( void )
{
    Connection *connection=getNetwork()->getMainConnection();

#if FAST_SYNC
    connection->selectChannel();
#else
    if(!getInterleave())
    {
        // wait for all servers to finish
        connection->wait();
        // initiate swap
        connection->signal();
    }
#endif

    // show client window 
    Inherited::clientSwap();
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
    static char cvsid_hpp[] = OSGMULTIDISPLAYCONFIG_HEADER_CVSID;
    static char cvsid_inl[] = OSGMULTIDISPLAYCONFIG_INLINE_CVSID;
}
