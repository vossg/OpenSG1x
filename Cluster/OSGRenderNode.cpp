/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                *
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

#include <vector>

#include <OSGConfig.h>
#include <OSGGL.h>
#include <OSGGLU.h>
#include <OSGBaseFunctions.h>
#include <OSGTime.h>
#include <OSGLog.h>
#include <OSGMatrix.h>
#include <OSGWindow.h>

#include "OSGRenderNode.h"

OSG_USING_NAMESPACE
using namespace std;

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id:$";
    static Char8 cvsid_hpp[] = OSG_CLUSTERNODE_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSG_CLUSTERNODE_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/** \class osg::RenderNode
 *  \ingroup Cluster
 *  \brief cluster node information
 **/

RenderNode *RenderNode::_prefefined[]=
{
    // some nvidia cards 

    new RenderNode(1.0/ 14598000,          // GF 256
                   1.0/ 14597000,
                   1.0/110599000,
                   1.0/ 18896143,
                   1.0/ 26220918,
                   "NVIDIA Corporation",
                   "GeForce 256/AGP"),

    new RenderNode(1.0/ 44471000,          // GF 3
                   1.0/ 44436000,
                   1.0/635452000,
                   1.0/ 24905933,
                   1.0/ 45649003,
                   "NVIDIA Corporation",
                   "GeForce3/AGP/3DNOW!"),

    new RenderNode(1.0/ 44061655,          // GF 3
                   1.0/ 43842088,
                   1.0/635688444,
                   1.0/ 37530822,
                   1.0/ 65564810,
                   "NVIDIA Corporation",
                   "GeForce3/AGP/SSE2"),

    new RenderNode(1.0/ 24931000,          // GF 2 MX
                   1.0/ 24930000,
                   1.0/112858311,
                   1.0/ 24905933,
                   1.0/ 45649003,
                   "NVIDIA Corporation",
                   "GeForce2 MX/AGP/3DNOW!"),


    // some sgi cards 

    new RenderNode(1.0/   959500,          // O2
                   1.0/   556700,
                   1.0/ 28915540,
                   1.0/  4047028,
                   1.0/  1101353,
                   "SGI",
                   "CRIME"),

    new RenderNode(1.0/  1771522,          // IR2
                   1.0/   861486,
                   1.0/ 70556999,
                   1.0/ 38311070,
                   1.0/ 73507039,
                   "SGI",
                   "IRL/M/2/64/4"),


    NULL
};

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

/*! Constructor 
 */
RenderNode::RenderNode(Real32 invisibleFaceCost,
                       Real32 visibleFaceCost,
                       Real32 drawPixelCost,
                       Real32 readPixelCost,
                       Real32 writePixelCost,
                       const string &vendor,
                       const string &renderer):
    _visibleFaceCost(visibleFaceCost),
    _invisibleFaceCost(invisibleFaceCost),
    _drawPixelCost(drawPixelCost),
    _readPixelCost(readPixelCost),
    _writePixelCost(writePixelCost),
    _vendor(vendor),
    _renderer(renderer)
{
}

/*! copy constructor
 */
RenderNode::RenderNode(const RenderNode &source):
    _visibleFaceCost(source._visibleFaceCost),
    _invisibleFaceCost(source._invisibleFaceCost),
    _drawPixelCost(source._drawPixelCost),
    _readPixelCost(source._readPixelCost),
    _writePixelCost(source._writePixelCost),
    _vendor(source._vendor),
    _renderer(source._renderer)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

/*! Destructor documentation
 */
RenderNode::~RenderNode(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

/*! assignment
 */
RenderNode& RenderNode::operator = (const RenderNode &source)
{
    if(this == &source)
        return *this;

    _visibleFaceCost    = source._visibleFaceCost;
    _invisibleFaceCost  = source._invisibleFaceCost;
    _drawPixelCost      = source._drawPixelCost;
    _readPixelCost      = source._readPixelCost;
    _writePixelCost     = source._writePixelCost;
    _vendor             = source._vendor;
    _renderer           = source._renderer;
    return *this;
}

/*-------------------------------------------------------------------------*/
/*                             Performance analysis                        */


/** get graphics performance
 * 
 * This is a rough estimation of rendering costst for visible faces,
 * faces outside of the viewport and size dependent rendering costs.
 * <pre>
 * // face cost calculation
 * cost = invisible * invisibleFaceCost +
 *        max( visible * visibleFaceCost + 
 *             pixel * pixelCost)
 * </pre>
 *
 **/
void RenderNode::determinePerformance( WindowPtr &window )
{
    int c;
    double faces=0;
    double A,B,C;
    double t;

    setVendor((const char*)glGetString(GL_VENDOR));
    setRenderer((const char*)glGetString(GL_RENDERER));

    // try to find precalculated values
    for(c=0;_prefefined[c]!=NULL;++c)
    {
        if(_prefefined[c]->getVendor()   == getVendor()  &&
           _prefefined[c]->getRenderer() == getRenderer())
        {
            SLOG << "Predefined performance values used." << endl;
            *this=*_prefefined[c];
            return;
        }
    }

    SLOG << "Start rendering benchmark" << endl;
    window->activate();
    // create display list
    GLuint dList1 = glGenLists(1);
    glNewList(dList1, GL_COMPILE);
    float step = .1;
    int count  = 400;
    for(float y=0;y<(1-step/2);y+=step)
    {        
        glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(0,y     ,-1);
        glVertex3f(0,y+step,-1);
        for(float x=step;x<(1+step/2);x+=step)
        {
            glVertex3f(x,y     ,-1);
            glVertex3f(x,y+step,-1);
            faces+=2;
        }
        glEnd();
    }
    glEndList();
    glFinish();
    GLuint dList2 = glGenLists(1);
    glNewList(dList2, GL_COMPILE);
    for(c=0;c<count;++c)
    {
        glCallList(dList1);
    }        
    glEndList();
    glFlush();
    t=runFaceBench(dList2,128,128,1.0);
    count=(int)(count/t);
    glNewList(dList2, GL_COMPILE);
    for(c=0;c<count;++c)
    {
        glCallList(dList1);
    }
    glEndList();
    runFaceBench(dList2,1,1,1.0);
    glFinish();

    Real32 aSize=2;
    Real32 bSize=2;
    Real32 cSize=128;
    do
    {
        for(A=0,c=0;A<1.0;++c)
        {
            A += runFaceBench(dList2,aSize,aSize,1.000);
        }
        A/=c*count;
        for(B=0,c=0;B<1.0;++c)
        {
            B += runFaceBench(dList2,bSize,bSize,0.001);
        }
        B/=c*count;
        C = runFaceBench(dList2,cSize,cSize,1.000)/count;
    } while(A>C);

    _visibleFaceCost     =A/faces;
    _invisibleFaceCost   =B/faces;
    _drawPixelCost       =C/(cSize*cSize);

    glViewport(0, 0, window->getWidth(), window->getHeight());
    UInt32 width,height;

    // test write performance
    glPixelStorei(GL_PACK_ALIGNMENT,1); 
    glPixelStorei(GL_UNPACK_ALIGNMENT,1); 
    vector<UInt8> pixels;
    width =window->getWidth();
    height=window->getHeight();
    pixels.resize(width*height*4);
    glFlush();
    t=-getSystemTime();
    for(c=0;c<2;++c)
        glReadPixels(0,0,width,height,GL_RGB,GL_UNSIGNED_BYTE,&pixels[0]);
    glFlush();
    t+=getSystemTime();
    _readPixelCost=t/(c*width*height);

    // test write performance
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0,width,0,height);
    glRasterPos2i(0,0);
    glDisable(GL_DEPTH_TEST);
    glFlush();
    t=-getSystemTime();
    for(c=0;c<2;++c)
        glDrawPixels(width,height,GL_RGB,GL_UNSIGNED_BYTE,&pixels[0]);
    glFlush();
    t+=getSystemTime();
    _writePixelCost=t/(c*width*height);
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    SLOG << "End rendering benchmark" << endl;
    
    glDeleteLists(dList2,1);
    glDeleteLists(dList1,1);
}

/** Write class contents to the given data stream
 *
 **/

void RenderNode::copyToBin(BinaryDataHandler &handle)
{
    handle.putReal32( _invisibleFaceCost );
    handle.putReal32( _visibleFaceCost );
    handle.putReal32( _drawPixelCost );
    handle.putReal32( _readPixelCost );
    handle.putReal32( _writePixelCost );
}

/** Read class contents from the given data stream
 *
 **/

void RenderNode::copyFromBin(BinaryDataHandler &handle)
{
    UInt32 count;
    
    handle.getReal32(_invisibleFaceCost);
    handle.getReal32(_visibleFaceCost);
    handle.getReal32(_drawPixelCost);
    handle.getReal32(_readPixelCost);
    handle.getReal32(_writePixelCost);
}

/** Set render performance values for a group of render nodes
 **/
void RenderNode::setGroup(const RenderNode *begin,const RenderNode *end)
{
    const RenderNode *i;
    Real32 invisibleFaces=0;
    Real32 visibleFaces=0;
    Real32 drawPixels=0;
    Real32 readPixels=0;
    Real32 writePixels=0;

    for(i=begin;i!=end;++i)
    {
        invisibleFaces+=1.0/i->_invisibleFaceCost;
        visibleFaces  +=1.0/i->_visibleFaceCost;
        drawPixels    +=1.0/i->_drawPixelCost;
        readPixels    +=1.0/i->_readPixelCost;
        writePixels   +=1.0/i->_writePixelCost;
    }
    _invisibleFaceCost=(1.0/invisibleFaces);
    _visibleFaceCost  =(1.0/visibleFaces);
    _drawPixelCost    =(1.0/drawPixels);
    _readPixelCost    =(1.0/readPixels);
    _writePixelCost   =(1.0/writePixels);
}

/** Dump class contents
 **/

void RenderNode::dump(void) const
{
    FLOG(("Vendor           : %s\n",_vendor.c_str()));
    FLOG(("Rnderer          : %s\n",_renderer.c_str()));
    FLOG(("Clipped Faces/s  : %20.5f\n",1.0/_invisibleFaceCost));
    FLOG(("Faces/s          : %20.5f\n",1.0/_visibleFaceCost));
    FLOG(("Pixel/s          : %20.5f\n",1.0/_drawPixelCost));
    FLOG(("Read pixel/s     : %20.5f\n",1.0/_readPixelCost));
    FLOG(("Write pixel/s    : %20.5f\n",1.0/_writePixelCost));
}

/** check face rendering performance
 * 
 * This method will render a display list with vertices in x,y range [0.1].
 * size specifies the viewport size. The vertices will be scaled to fit
 * exactly in to the viewport. The parameter visible defines which share
 * of the geometry should be visible. 1: all is visible, 0.5 half of the
 * geometry is visible.
 *
 * \param dlist     display list
 * \param size      viewport size
 * \param visible   visible portion of the geometry
 *
 **/
double RenderNode::runFaceBench(UInt32 dlist,
                                UInt32 width,
                                UInt32 height,
                                Real32 visible)
{
    GLint depthFunc;

    glGetIntegerv( GL_DEPTH_FUNC,&depthFunc );
    glDepthFunc  ( GL_LEQUAL );
    glViewport(0, 0, width, height);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glScalef(1.0/visible,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0,1,0,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glFinish();
    // start bench
    Time t=-getSystemTime();
    glCallList(dlist);
    glFinish();
    t+=getSystemTime();
    // end bench
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glDepthFunc  ( depthFunc );
    return t;
}

