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

#include "OSGConfig.h"
#include "OSGGL.h"
#include "OSGGLU.h"
#include "OSGBaseFunctions.h"
#include "OSGLog.h"
#include "OSGClusterViewBuffer.h"
#include "OSGImageFileHandler.h"
#include "OSGImageFileType.h"
#include "OSGConnection.h"

OSG_USING_NAMESPACE

/*! \class osg::ClusterViewBuffer
   \ingroup GrpSystemCluster
   \brief Viewbuffer functions

   This class provides an interface to an OpenGL view buffer.
   The Buffer contents can be transfered over a Connection.
   All Image types can be used for image compression. The
   ClusterViewBuffer can access RGBA, Stencil and Z-Buffer values.

   The whole imagebuffer is divided into subtiles. Each subtile
   is read from the buffer, compressed and send over the nertwork.
   In most cases, the buffer read and the network send of the previous
   tile is done in parallel.

   todo: currently ClusterViewBuffer works on the activated window.
         Is this a good idea. Better WindowPtr as parameter and then
         call activate before send,recv? MR
*/

/*-------------------------------------------------------------------------*/
/*                            Constructors/Destructor                      */

/*! Initialize a ClusterViewBuffer. By default, no image compression
    is set and the subtile size is set to 32. The viewbuffer contents
    is send in packages. If the package size is not too large, then 
    network transmission of the last and graphics card read of the current
    package is done in parallel. 
 */
ClusterViewBuffer::ClusterViewBuffer(void) :
    _imgTransType(NULL),
    _subTileSize(32)
{
}

/*! Destructor
 */
ClusterViewBuffer::~ClusterViewBuffer(void)
{
}

/*-------------------------------------------------------------------------*/
/*                            send/recv                                    */

/*! Receive image data from all channels of a conneciton. The receive is
 *  finished, when the last channel signals a transmission end.
 */
void ClusterViewBuffer::recv(Connection &connection,UInt32 channel)
{
    UInt32  tx, ty, tw, th;
    UInt32  missing;
    BufferT data;
    BufferT imageData;
    UInt32  dataSize;
    UInt32  component;
    GLenum  glformat;
    int     componentCnt;

    if(channel == Connection::ALL_CHANNELS)
        missing = connection.getChannelCount();
    else
        missing = 1;

    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, getBufferWidth(), 0, getBufferHeight());
    glDisable(GL_DEPTH_TEST);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // we expect tiles form all connected servers
    while(missing)
    {
        connection.selectChannel(channel);
        connection.getValue(component);
        if(!component)
        {
            missing--;
            continue;
        }

        // get dimension
        connection.getValue(tx);
        connection.getValue(ty);
        connection.getValue(tw);
        connection.getValue(th);
        glRasterPos2i(tx, ty);

        // =========== recv stencil =====================================
        if(component & STENCIL)
        {
            data.resize(tw * th);
            connection.get(&data[0], tw * th);
            glDrawPixels(tw, th, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &data[0]);
            glEnable(GL_STENCIL_TEST);
        }

        // =========== recv depth =======================================
        if(component & DEPTH)
        {
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_STENCIL_TEST);
            glStencilFunc(GL_ALWAYS, 1, 1);
            glStencilOp(GL_KEEP, GL_ZERO, GL_REPLACE);
            data.resize(tw * th * sizeof(float));
            connection.get(&data[0], tw * th * sizeof(float));
            glDrawPixels(tw, th, GL_DEPTH_COMPONENT, GL_FLOAT, &data[0]);
            glDisable(GL_DEPTH_TEST);
        }

        // =========== recv RGBA ========================================
        if(component & RGBA)
        {
            if(component & (DEPTH | STENCIL))
            {
                glStencilFunc(GL_EQUAL, 1, 1);
            }

            switch(component & RGBA)
            {
            case RGB:
                glformat = GL_RGB;
                componentCnt = 3;
                break;
            case RGBA:
                glformat = GL_RGBA;
                componentCnt = 4;
                break;
            default:
                SFATAL << "Component combination not supported" << std::endl;
                return;
            }

            connection.getValue(dataSize);

            // compression ?
            if(dataSize > 0)
            {
#if 0
                pImage = new Image;

                data.resize(dataSize);
                connection.get(&data[0], dataSize);
                imageData.resize(tw * th * componentCnt);
                ImageFileType::restore(*pImage, (UChar8 *) &data[0], dataSize);
                glDrawPixels(tw, th, glformat, GL_UNSIGNED_BYTE,
                                             pImage->getData());

                subRefP(pImage);
#endif
            }
            else
            {
                data.resize(tw * th * componentCnt);
                connection.get(&data[0], tw * th * componentCnt);
                glDrawPixels(tw, th, glformat, GL_UNSIGNED_BYTE, &data[0]);
            }
        }

        if(component & (DEPTH | STENCIL))
        {
            glDisable(GL_STENCIL_TEST);
        }
    }
/*
    connection.putValue(sync);
    connection.flush();
*/
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
}

/*! Send parts of a view buffer to a Connection

    \a connection defines the connection to use, \a component which color
    channels (RGB/RGBA) should be transferred, \a x1, \a y1, \a x2, \a y2
    (inclusive) define the source area and \a toX and \a toY the lower left
    corner of the destination area.
*/
void ClusterViewBuffer::send(Connection &connection, 
                             UInt32 component, UInt32 x1,
                             UInt32 y1, UInt32 x2, UInt32 y2, UInt32 toX,
                             UInt32 toY)
{
    UInt32              tx, ty, tw, th;
//    Image               *pImage;
    BufferT             data;
    BufferT             imageData;
    UInt32              dataSize;
    GLenum              glformat;
//    Image::PixelFormat  imgformat;
    int                 componentCnt;
    int                 imgtranssize = 0;

    switch(component & RGBA)
    {
    case RGB:  glformat = GL_RGB;
//               imgformat = Image::OSG_RGB_PF;
               componentCnt = 3;
               break;
    case RGBA: glformat = GL_RGBA;
//               imgformat = Image::OSG_RGBA_PF;
               componentCnt = 4;
               break;
    default:   SFATAL << "Component combination not supported" << std::endl;
               return;
    }

    // resize image buffer
    imageData.resize(_subTileSize * _subTileSize * componentCnt);

    glPixelStorei(GL_PACK_ALIGNMENT, 1);

    for(ty = y1; ty <= y2; ty += _subTileSize)
    {
        for(tx = x1; tx <= x2; tx += _subTileSize)
        {
            tw = osgMin(_subTileSize, x2 + 1 - tx);
            th = osgMin(_subTileSize, y2 + 1 - ty);

            connection.putValue(component);
            connection.putValue(tx + toX);
            connection.putValue(ty + toY);
            connection.putValue(tw);
            connection.putValue(th);

            // =========== send STENCIL =======================================
            if(component & STENCIL)
            {
                // read stencil buffer
                data.resize(tw * th);
                glReadPixels(tx, ty, tw, th, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE,
                                             &data[0]);
                connection.put(&data[0], tw * th);
            }

            // =========== send DEPTH =======================================
            if(component & DEPTH)
            {
                // read stencil buffer
                data.resize(tw * th * sizeof(float));
                glReadPixels(tx, ty, tw, th, GL_DEPTH_COMPONENT, GL_FLOAT,
                                             &data[0]);
                connection.put(&data[0], tw * th * sizeof(float));
            }

            // =========== send RGBA ========================================
            if(component & RGBA)
            {
                // use compression ?
                if(_imgTransType)
                {
#if 0
                    // set image size
                    pImage = new Image;

                    pImage->set(imgformat, tw, th, 1, 1, 1, 0.0,
                                (UChar8 *) &imageData[0]);

                    // read buffer data into image
                    glReadPixels(tx, ty, tw, th, glformat, GL_UNSIGNED_BYTE,
                                 pImage->getData());

                    // bug maxsize is not big enugh
                    data.resize(_imgTransType->maxBufferSize(*pImage) + 1000);
                    dataSize = _imgTransType->store(*pImage, (UChar8 *) &data[0],
                                                                        data.size());
                    connection.putValue(dataSize);
                    connection.put(&data[0], dataSize);
                    imgtranssize += dataSize;

                    subRefP(pImage);
#endif
                }
                else
                {
                    data.resize(tw * th * componentCnt);

                    // read buffer data
                    glReadPixels(tx, ty, tw, th, glformat, GL_UNSIGNED_BYTE,
                                                     &data[0]);
                    dataSize = 0;
                    connection.putValue(dataSize);
                    connection.put(&data[0], tw * th * componentCnt);
                    imgtranssize += tw * th * componentCnt;
                }
            }

            connection.flush();
        }
    }

    component = 0;
    connection.putValue(component);
    connection.flush();

/*
    connection.selectChannel();
    connection.getValue(sync);
*/
}

/*! Send parts of a view buffer to a Connection
 */
void ClusterViewBuffer::send(Connection &connection, UInt32 component,
                             UInt32 toX, UInt32 toY)
{
    send(connection, component, 0, 0, getBufferWidth(), getBufferHeight(), toX,
         toY);
}


/*! Send parts of a view buffer to a Connection
 */
void ClusterViewBuffer::pipe(Connection *srcConnection,
                             Connection *dstConnection,
                             UInt32 dstComponent,
                             UInt32 vpx1,UInt32 vpy1,
                             UInt32 vpx2,UInt32 vpy2,
                             UInt32 x1  ,UInt32 y1,
                             UInt32 x2  ,UInt32 y2,
                             UInt32 dstMaxDepth,
                             UInt32 srcChannel)
{
    UInt32              tx, ty, tw, th;
    BufferT             stencilData;
    BufferT             zData;
    BufferT             colorData;
    UInt32              srcComponent;
    UInt32              sendComponent;
    UInt32              colorRemoved=0;
    UInt32              depthRemoved=0;
    UInt32              colorSent=0;
    UInt32              depthSent=0;
    UInt32              colorCliped=0;
    UInt32              depthCliped=0;
    UInt32              colorBBoxCliped=0;
    UInt32              depthBBoxCliped=0;
    Real64              readTime=0;
    Real64              composeTime=0;
    Real64              sendTime=0;
    UInt32              maxSend=0;

//    dstComponent=RGBA|DEPTH;

    // resize buffers
    stencilData.resize(_subTileSize * _subTileSize * 1);
    zData      .resize(_subTileSize * _subTileSize * 4);
    colorData  .resize(_subTileSize * _subTileSize * 4);

    glPixelStorei(GL_PACK_ALIGNMENT, 1);

    if(srcConnection)
        srcConnection->selectChannel(srcChannel);

    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, getBufferWidth(), 0, getBufferHeight(),-1,1);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glClear(GL_STENCIL_BUFFER_BIT);
    glDisable(GL_BLEND);
    glDepthFunc(GL_LEQUAL);

    // bug in getPixelLeft... when win size=0;
    if(vpx2==0xffffffff ||
       vpy2==0xffffffff)
        vpx2=vpy2=0;

    for(ty = vpy1; ty <= vpy2; ty += _subTileSize)
    {
        for(tx = vpx1; tx <= vpx2; tx += _subTileSize)
        {
            tw = osgMin(_subTileSize, vpx2 - tx + 1);
            th = osgMin(_subTileSize, vpy2 - ty + 1);

            readTime-=getSystemTime();
            srcComponent=0;
            if(srcConnection)
            {
                srcConnection->getValue(srcComponent);
            }
            sendComponent=0;
            if(dstConnection)
                sendComponent=srcComponent;

            // start reading the components
            
            // read depth
            if(srcComponent & DEPTH)
            {
                srcConnection->get(&zData[0], tw * th * 4);
            }

            // read color
            if((srcComponent & RGBA) == RGBA)
            {
                srcConnection->get(&colorData[0], tw * th * 4);
            }
            if((srcComponent & RGBA) == RGB)
            {
                srcConnection->get(&colorData[0], tw * th * 3);
            }

            readTime+=getSystemTime();

            // if the received buffer overlaps 
            if( tx      <= x2             &&
                tx+tw-1 >= x1             &&
                ty      <= y2             &&
                ty+th-1 >= y1 )
            {
                if(dstConnection)
                    sendComponent=dstComponent;

                // set raster pos

                composeTime-=getSystemTime();
                glRasterPos3f(GLfloat(tx), GLfloat(ty), -0.999997);

                // write depth buffer. Result of comparision in stencil buf.
                if(srcComponent & DEPTH)
                {
                    glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
                    glEnable(GL_STENCIL_TEST);
                    glStencilFunc(GL_ALWAYS, 1, 1);
                    glStencilOp(GL_KEEP, GL_ZERO, GL_REPLACE);
                    glDrawPixels(tw, th, 
                                 GL_DEPTH_COMPONENT, 
                                 GL_UNSIGNED_INT, &zData[0]);
                    glDisable(GL_DEPTH_TEST);
                    glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
                    glStencilFunc(GL_EQUAL, 1, 1);
                }

                // write color buffer
                if((srcComponent & RGBA) == RGBA)
                {
                    glDrawPixels(tw, th, GL_RGBA,
                                 GL_UNSIGNED_BYTE, &colorData[0]);
                }
                if((srcComponent & RGBA) == RGB)
                {
                    glDrawPixels(tw, th, GL_RGB,
                                 GL_UNSIGNED_BYTE, &colorData[0]);
                }

                if(srcComponent & DEPTH)
                {
                    glDisable(GL_STENCIL_TEST);
                    glEnable(GL_DEPTH_TEST);
                }

                // read depth buffer
                if(sendComponent & DEPTH)
                {
                    glReadPixels(tx, ty, tw, th, 
                                 GL_DEPTH_COMPONENT, GL_UNSIGNED_INT,
                                 &zData[0]);
                }
                
                // read color buffer
                if((sendComponent & RGBA) == RGBA)
                {
                    glReadPixels(tx, ty, tw, th, 
                                 GL_RGBA, GL_UNSIGNED_BYTE,
                                 &colorData[0]);

                }
                if((sendComponent & RGBA) == RGB)
                {
                    glReadPixels(tx, ty, tw, th, 
                                 GL_RGB, GL_UNSIGNED_BYTE,
                                 &colorData[0]);
                }

//                glFinish();
                composeTime+=getSystemTime();
            }

//            if(dstConnection && dstMinDepth != 0xffffffff)
            if(dstConnection)
            {
                if((dstComponent & DEPTH)  == 0 &&
                   (sendComponent & DEPTH) == 0)
                    depthRemoved+=tw*th*4;
                else
                    if((sendComponent & DEPTH) == 0)
                        depthBBoxCliped+=tw*th*4;

                if((sendComponent & RGBA) == 0)
                    colorBBoxCliped+=tw*th*3;
/*
                if((sendComponent & RGBA) == 0)
                {
                    sendComponent|=RGBA;
                    for(int i=0;i<tw*th;++i)
                    {
                        colorData[i*4+0]=255;
                        colorData[i*4+1]=255;
                        colorData[i*4+2]=0;
                        colorData[i*4+3]=255;
                    }
                }
*/
            }

            sendTime-=getSystemTime();
#if 1
            // check if DEPTH is needed
            if(dstMaxDepth != 0xffffffff)
            {
                if(sendComponent & DEPTH)
                {
                    UInt32 *depth=(UInt32*)(&zData[0]);
                    UInt32 *depthEnd=depth + tw * th;
                    UInt32  depthMin=*depth;
                    while(++depth != depthEnd)
                    {
                        if(depthMin>*depth)
                            depthMin=*depth;
                    }
                    if(depthMin==0xffffffff)             // nothing rendered
                    {
                        depthCliped+=tw*th*4;
                        if((sendComponent & RGBA)==RGB) 
                            colorCliped+=tw*th*3;
                        if((sendComponent & RGBA)==RGBA)
                            colorCliped+=tw*th*4;
                        sendComponent &= 0xffff^(RGBA | DEPTH);
/*
                        for(int i=0;i<tw*th;++i)
                            colorData[i*4+0]=255;
*/
                    }
                    else
                    {
                        if(depthMin>dstMaxDepth)
                        {
                            sendComponent &= 0xffff^DEPTH;
                            depthRemoved+=tw*th*4;
                        }
                    }
                }
            }

#endif
            // send components
            if(dstConnection)
            {
                dstConnection->putValue(sendComponent);
            }

            // send depth buffer
            if(sendComponent & DEPTH)
            {
                dstConnection->put(&zData[0], tw * th * 4);
//                if(dstMaxDepth != 0xffffffff)
                    depthSent+=tw*th*4;
            }

            // send color buffer
            if((sendComponent & RGBA) == RGBA)
            {
                dstConnection->put(&colorData[0], tw * th * 4);
                colorSent+=tw*th*4;
            }
            if((sendComponent & RGBA) == RGB)
            {
                dstConnection->put(&colorData[0], tw * th * 3);
                colorSent+=tw*th*3;
            }
/*
            if(dstConnection)
                dstConnection->flush();
*/
            sendTime+=getSystemTime();
        }
    }
            if(dstConnection)
                dstConnection->flush();
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glDisable(GL_BLEND);
    glDepthFunc(GL_LESS);

    maxSend=depthSent+colorSent;
    if(srcConnection)
    {
        UInt32 dr,cr,ds,cs,dc,cc,db,cb;
        Real64 readT,composeT,sendT;
        UInt32 maxS;
        srcConnection->getValue(dr);
        srcConnection->getValue(cr);
        srcConnection->getValue(ds);
        srcConnection->getValue(cs);
        srcConnection->getValue(dc);
        srcConnection->getValue(cc);
        srcConnection->getValue(db);
        srcConnection->getValue(cb);
        srcConnection->getValue(readT);
        srcConnection->getValue(composeT);
        srcConnection->getValue(sendT);
        srcConnection->getValue(maxS);
        depthRemoved+=dr;
        colorRemoved+=cr;
        depthSent+=ds;
        colorSent+=cs;
        depthCliped+=dc;
        colorCliped+=cc;
        depthBBoxCliped+=db;
        colorBBoxCliped+=cb;
        maxSend=osgMax(maxS,maxSend);
        if(readT+composeT+sendT > readTime+composeTime+sendTime)
        {
            readTime   =readT;
            composeTime=composeT;
            sendTime   =sendT;
        }
    }
    if(dstConnection)
    {
        dstConnection->putValue(depthRemoved);
        dstConnection->putValue(colorRemoved);
        dstConnection->putValue(depthSent);
        dstConnection->putValue(colorSent);
        dstConnection->putValue(depthCliped);
        dstConnection->putValue(colorCliped);
        dstConnection->putValue(depthBBoxCliped);
        dstConnection->putValue(colorBBoxCliped);
        dstConnection->putValue(readTime);
        dstConnection->putValue(composeTime);
        dstConnection->putValue(sendTime);
        dstConnection->putValue(maxSend);
        dstConnection->flush();
    }
    if(!dstConnection)
    {
        printf("Statistics:\n"
               "send    : d %10d c %10d sum %10d\n"
               "pipesort: d %10d\n"
               "clip    : d %10d c %10d\n"
               "bbox    : d %10d c %10d\n"
               "Sum     : d %10d c %10d\n"
               "WholeSum: d %10d\n"
               "MaxTime : r%0.5f c%0.5f s%0.5f\n"
               "MaxSend : %d\n",
               depthSent   ,colorSent, depthSent+colorSent,
               depthRemoved,
               depthCliped ,colorCliped,
               depthBBoxCliped ,colorBBoxCliped,
               
               depthSent+depthRemoved+depthCliped+depthBBoxCliped,
               colorSent+colorRemoved+colorCliped+colorBBoxCliped,

               depthSent+depthRemoved+depthCliped+depthBBoxCliped+
               colorSent+colorRemoved+colorCliped+colorBBoxCliped,

               readTime,composeTime,sendTime,
               maxSend);
    }
}

/*-------------------------------------------------------------------------*/
/*                            set parameters                               */

/*! Set compression type. By default, no compression is used for image transmission. 
 *  The given mime type identifies an ImageType e.g. "JPEG".
 *  This image type is used for compression. 
 */
void ClusterViewBuffer::setImgTransType(const char *mimeType)
{
    if(mimeType == NULL)
    {
        _imgTransType = NULL;
    }
    else
    {
        _imgTransType = ImageFileHandler::the().getFileType(mimeType);
    }
}

/*! Set subtile size. The whole buffer is transfered as small subtiles.
    Increasing or decreasing the subtile size will result in changes to the
    performance. The best size depends on network package size and the
    ration between network performance and buffer read/write performance.
 */
void ClusterViewBuffer::setSubtileSize(UInt32 size)
{
    _subTileSize = size;
}

/*-------------------------------------------------------------------------*/
/*                            get                                          */

/*! Get buffer width
 */
UInt32 ClusterViewBuffer::getBufferWidth(void)
{
    GLint   view[4];
    glGetIntegerv(GL_VIEWPORT, view);
    return view[2];
}

/*! Get buffer width
 */
UInt32 ClusterViewBuffer::getBufferHeight(void)
{
    GLint   view[4];
    glGetIntegerv(GL_VIEWPORT, view);
    return view[3];
}

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif
#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8    cvsid_cpp[] = "@(#)$Id:$";
    static Char8    cvsid_hpp[] = OSG_VIEWBUFFERHANDLER_HEADER_CVSID;
}
