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


OSG_USING_NAMESPACE

/*! \class osg::MultiDisplayWindow
Cluster rendering configuration for multible display
*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

MultiDisplayWindow::MultiDisplayWindow(void) :
    Inherited()
{
}

//! Copy Constructor

MultiDisplayWindow::MultiDisplayWindow(const MultiDisplayWindow &source) :
    Inherited(source)
{
}

//! Destructor

MultiDisplayWindow::~MultiDisplayWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void MultiDisplayWindow::initMethod (void)
{
}

//! react to field changes

void MultiDisplayWindow::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

//! output the instance for debug purposes

void MultiDisplayWindow::dump(      UInt32    , 
                              const BitVector ) const
{
    SLOG << "hServers:" << getHServers() << " "
         << "vServers:" << getVServers() << std::endl;
}

/*----------------------------- server methods ----------------------------*/

/*! render server window
 *  
 *  update all viewport parameters and render local viewports
 *  Width and height of the whole window are calculated by 
 *  multiplieing the local window size by hServers and vServers.
 *  
 *  !param window     server render window
 *  !param id         server id
 *  !param action     action
 */

void MultiDisplayWindow::serverRender( WindowPtr serverWindow,
                                       UInt32 id,
                                       RenderAction *action )
{
    TileCameraDecoratorPtr deco;
    StereoBufferViewportPtr serverPort;
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
    Int32 left   = column * width;
    Int32 bottom = row    * height;
    Int32 right  = left   + width  - 1;
    Int32 top    = bottom + height - 1;
    Real32 scaleCWidth  = width  * getHServers() / (float)getWidth();
    Real32 scaleCHeight = height * getVServers() / (float)getHeight();

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
            serverPort = StereoBufferViewport::create();
            deco=TileCameraDecorator::create();
            beginEditCP(serverWindow);
            serverWindow->addPort(serverPort);
            serverPort->setCamera(deco);
            endEditCP(serverWindow);
        }
        else
        {
            serverPort = StereoBufferViewportPtr::dcast(
			    serverWindow->getPort()[sv]);
            deco=TileCameraDecoratorPtr::dcast(serverPort->getCamera());
        }
        // duplicate values
        beginEditCP(serverPort);
        if(clientStereoPort!=NullFC)
        {
            serverPort->setRightBuffer( clientStereoPort->getRightBuffer() );
            serverPort->setLeftBuffer( clientStereoPort->getLeftBuffer() );
        }
        else
        {
            serverPort->setRightBuffer( true );
            serverPort->setLeftBuffer( true );
        }
        serverPort->setSize(l,b,r,t);
        // use pixel even if pixel = 1
        if(serverPort->getLeft() == 1.0)
            serverPort->setLeft(1.0001);
        if(serverPort->getRight() == 1.0)
            serverPort->setRight(1.0001);
        serverPort->setRoot      ( clientPort->getRoot()       );
        serverPort->setBackground( clientPort->getBackground() );
        serverPort->getMFForegrounds()->setValues( clientPort->getForegrounds() );        
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
    // clear command buffers
    glFinish();
    // tell client that we are finish
    getConnection()->signal();
    // wait for swap
    getConnection()->wait();
    Inherited::serverSwap(window,id);
}

/*----------------------------- client methods ----------------------------*/

/*! init client window
 */

void MultiDisplayWindow::clientInit( void )
{
    ViewportPtr cvp;
    if(getClientWindow() == NullFC ||
       getPort().size()==0)
        return;

    cvp=getPort()[0];

    // duplucate viewport for client window
    ViewportPtr vp;
    vp = Viewport::create();
    beginEditCP(vp);
    vp->setCamera( cvp->getCamera() );
    vp->setBackground( cvp->getBackground() );
    vp->setRoot( cvp->getRoot() );
    vp->setSize( 0,0, 1,1 );
    beginEditCP(getClientWindow());
    getClientWindow()->addPort(vp);
    endEditCP(getClientWindow());
    endEditCP(vp);
}

/*! render client window
 */

void MultiDisplayWindow::clientSwap( void )
{
    // wait for all servers to finish
    getConnection()->wait();
    // initiate swap
    getConnection()->signal();
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
