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
#include <math.h>

#include "OSGConfig.h"
#include "OSGBaseFunctions.h"
#include "OSGFaceIterator.h"
#include "OSGTileGeometryLoad.h"

OSG_USING_NAMESPACE

/** \class osg::TileGeometryLoad
 *  \ingroup Cluster
 *  \brief TileGeometryLoad holds the load caused by geometry rendering
 *
 **/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

/*! Constructor
 */

TileGeometryLoad::TileGeometryLoad(NodePtr node,
                                   bool useFaceDistribution):
    _node(node),
    _faces(0),
    _useFaceDistribution(useFaceDistribution)
{
    _faceDistribution.resize(FACE_DISTRIBUTION_SAMPLING_COUNT);
    updateGeometry();
} 

/*! copy Constructor
 */

TileGeometryLoad::TileGeometryLoad(const TileGeometryLoad &source):
    _node(source._node),
    _useFaceDistribution(source._useFaceDistribution)
{
    _min[0]           = source._min[0];
    _min[1]           = source._min[1];
    _max[0]           = source._max[0];
    _max[1]           = source._max[1];
    _faces            = source._faces;
    _visible          = source._visible;
    _faceDistribution = source._faceDistribution;
    _areaSize         = source._areaSize;
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

/** Destructor documentation
 **/
TileGeometryLoad::~TileGeometryLoad(void)
{
}

/** Update the view dependend load parameters
 **/

void TileGeometryLoad::updateView(Matrix &viewing,
                                  Matrix &projection,
                                  Real32 rNear,
                                  UInt32 width,
                                  UInt32 height)
{
    Vec3f  vol[2];
    Pnt3f  pnt;
    Real32 minx,miny;
    Real32 maxx,maxy;
    Matrix *p;

    // get whole transformation
    Matrix m=_node->getToWorld();
    m.multLeft(viewing);
    // get transformed volume
    _node->updateVolume();
    DynamicVolume volume=_node->getVolume();
    // bug in osg base
    /*
    if(volume.isEmpty())
    {
        _visible=false;
        return;
    }
    */
    volume.transform(m);
    // get min,max
    volume.getBounds(vol[0], vol[1]);
    // min < rNear
    if(vol[0][2] > -rNear)
    {
        _visible=false;
        return;
    }
    if(vol[1][2] > -rNear)
    {
        // volume lays on the fron clipping plane
        vol[1][2] = -rNear;
        p=&projection;
    }
    else
    {
        // volume lays on the visible side of the clipping plane
        _node->getVolume().getBounds(vol[0], vol[1]);
        m.multLeft(projection);
        p=&m;
    }
    // create corners of a bounding box
    for(int i=0;i<8;++i)
    {
        p->multFullMatrixPnt(Pnt3f( vol[ (i   )&1 ][0] ,
                                    vol[ (i>>1)&1 ][1] ,
                                    vol[ (i>>2)&1 ][2]) , pnt);
        if(i>0)
        {
            if(minx > pnt[0]) minx = pnt[0];
            if(miny > pnt[1]) miny = pnt[1];
            if(maxx < pnt[0]) maxx = pnt[0];
            if(maxy < pnt[1]) maxy = pnt[1];
        }
        else
        {
            maxx = minx = pnt[0];
            maxy = miny = pnt[1];
        }
    }
    // visible ?
    if(maxx<-1 || maxy<-1 ||
       minx> 1 || miny> 1)
    {
        _visible = false;
    }
    else
    {
        minx=width  * ( minx + 1.0 ) / 2.0 - .5;
        maxx=width  * ( maxx + 1.0 ) / 2.0 + .5;
        miny=height * ( miny + 1.0 ) / 2.0 - .5;
        maxy=height * ( maxy + 1.0 ) / 2.0 + .5;
        _min[0]=(Int32)minx;
        _max[0]=(Int32)maxx;
        _min[1]=(Int32)miny;
        _max[1]=(Int32)maxy;

        _areaSize = 
            (Real32)( _max[0] - _min[0] + 1 ) *
            (Real32)( _max[1] - _min[1] + 1 );
/*
        if(_areaSize<0)
        {
            cout << "areasize " 
                 << _areaSize 
                 << " " << fabs(minx) 
                 << " " << miny 
                 << " " << maxx 
                 << " " << maxy << endl; 
        }
*/
        /* Don't clip!
        if(_min[0]<0) _min[0]=0;
        if(_min[1]<0) _min[1]=0;
        if(_max[0]>=width ) _max[0]=width-1;
        if(_max[1]>=height) _max[1]=height-1;
        */
        _visible = true;
    }
}

/** Update geometry dependend load parameters
 * 
 * This funciton should only be called when geometies have changed.
 *
 * \todo Use a simple cost estimation mechanism for rapidly changeing
 *       geometries.
 *
 **/
void TileGeometryLoad::updateGeometry()
{
    const OSG::Volume *volume = &(_node->getVolume().getInstance());
    FaceIterator       f;
    int                p,i;
    Vec3f              vmin,vmax;
    Pnt3f              pos;
    Real32             min,max;
    PrimitiveIterator  it;
    Real32             sum;
    UInt32             faceStart[FACE_DISTRIBUTION_SAMPLING_COUNT];
    UInt32             faceCount=0;
    NodeCorePtr        core;
    GeometryPtr        geo;

    _faces = 0;
    core=_node->getCore();
    if(_node->getCore() == NullFC)
        return;
    geo=GeometryPtr::dcast(core);
    if(geo == NullFC)
        return;

    // count faces
    for(f=geo->beginFaces() ; f!=geo->endFaces() ; ++f)
    {
        ++_faces;
    }

    if(_useFaceDistribution)
    {
        // get face distribution
        Plane plane[6]={
            Plane(Vec3f( 1, 0, 0)            ,Pnt3f(0,0,0)),
            Plane(Vec3f( 0, 1, 0)            ,Pnt3f(0,0,0)),
            Plane(Vec3f( 0, 0, 1)            ,Pnt3f(0,0,0)),
            Plane(Vec3f( 1, 1, 1)*(1/sqrt(3.0)),Pnt3f(0,0,0)),
            Plane(Vec3f(-1, 1, 1)*(1/sqrt(3.0)),Pnt3f(1,0,0)),
            Plane(Vec3f( 1,-1, 1)*(1/sqrt(3.0)),Pnt3f(0,1,0))
        };
        // clear tab
        for(i=0;i<FACE_DISTRIBUTION_SAMPLING_COUNT;i++)
            faceStart[i]=0;
        // get volume min,max
        volume->getBounds(vmin,vmax);
        // get distribution for x,y,z axis and the three main diagonals
        for(f=geo->beginFaces() ; f!=geo->endFaces() ; ++f)
        {
            for(i=0;i<6;i++)
            {
                for(p=0;p<f.getLength();p++)
                {
                    pos=f.getPosition(p) - vmin;
                    pos[0]/=vmax[0]-vmin[0];
                    pos[1]/=vmax[1]-vmin[1];
                    pos[2]/=vmax[2]-vmin[2];
                    if(p==0)
                    {
                        max=min=plane[i].distance(pos);
                    }
                    else
                    {
                        max=osgMax(max,plane[i].distance(pos));
                        min=osgMin(min,plane[i].distance(pos));
                    }
                }
                if(i>=3)
                {
                    min/=sqrt(3.0);
                    max/=sqrt(3.0);
                }
                faceStart[ (int)(ceil(min*
                                      (FACE_DISTRIBUTION_SAMPLING_COUNT-1)))]++;
                faceStart[ (int)(ceil((1-max)*
                                      (FACE_DISTRIBUTION_SAMPLING_COUNT-1)))]++;
                faceCount+=2;
            }
        }
        // cummulate distribution
        for(i=0,sum=0;i<FACE_DISTRIBUTION_SAMPLING_COUNT;i++)
        {
            sum+=(faceStart[i]/(float)faceCount);
            _faceDistribution[i]=sum;
            /*
            printf("%10.6f %10.6f\n",
                   ((float)i)/(FACE_DISTRIBUTION_SAMPLING_COUNT-1),
                   sum);
            */
        }
    }
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

/*! assignment
 */
TileGeometryLoad& TileGeometryLoad::operator=(const TileGeometryLoad &source)
{
    if(this == &source)
        return *this;
    _min[0]              = source._min[0];
    _min[1]              = source._min[1];
    _max[0]              = source._max[0];
    _max[1]              = source._max[1];
    _faces               = source._faces;
    _visible             = source._visible;
    _faceDistribution    = source._faceDistribution;
    _node                = source._node;
    _useFaceDistribution = source._useFaceDistribution;
    _areaSize            = source._areaSize;

    return *this;
}

/*-------------------------------------------------------------------------*/
/*                             dump                                        */

void TileGeometryLoad::dump(void)
{
    if(_visible)
    {
        SLOG << "Min/Max     :"  
             << _min[0] << " " << _min[1] << " / "
             << _max[0] << " " << _max[1] << std::endl;
    }
    else
    {
        SLOG << "invisible " << std::endl; 
    }
    SLOG << "Faces       :" << _faces << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                             get                                         */

/** Return min valuse in window coordinates
 **/
const Int32 *TileGeometryLoad::getMin()
{
    return _min;
}

/** Return max valuse in window coordinates
 **/
const Int32 *TileGeometryLoad::getMax()
{
    return _max;
}

/** Is the geometry visible in the current viewport
 **/
bool TileGeometryLoad::isVisible() const
{
    return _visible;
}

/** Get Node ptr
 **/
NodePtr TileGeometryLoad::getNode() const
{
    return _node;
}

/** Get number of faces in the geometry
 **/
UInt32 TileGeometryLoad::getFaces()
{
    return _faces;
}

/** Which part of the faces are visible
 **/
Real32 TileGeometryLoad::getVisibleFraction( const Int32 wmin[2],
                                             const Int32 wmax[2],
                                                   Int32 viswmin[2],
                                                   Int32 viswmax[2] )
{
    Real32 x,y;

    if(_visible==false)
        return 0;

    // get visible area
    if(!getVisibleArea(wmin,wmax,viswmin,viswmax))
    {
        // not in region
        return 0;
    }
    // geometry complete in region?
    if(viswmin[0] == _min[0] &&
       viswmin[1] == _min[1] &&
       viswmax[0] == _max[0] &&
       viswmax[1] == _max[1])
    {
        return 1;
    }

    if(_useFaceDistribution)
    {
        x=1.0/(_max[0]-_min[0]+1);
        y=1.0/(_max[1]-_min[1]+1);
        return
            (getFaceDistribution(1.0 - (viswmin[0] - _min[0]    ) * x) +
             getFaceDistribution(      (viswmax[0] - _min[0] + 1) * x) - 1) *
            (getFaceDistribution(1.0 - (viswmin[1] - _min[1]    ) * y) +
             getFaceDistribution(      (viswmax[1] - _min[1] + 1) * y) - 1);
    }
    else
    {
        return 
            ((Real32)(viswmax[0] - viswmin[0] + 1) *
             (Real32)(viswmax[1] - viswmin[1] + 1)) / _areaSize;
    }
}

/** Which area overlaps the given region
 **/
bool TileGeometryLoad::getVisibleArea( const Int32 wmin[2],
                                       const Int32 wmax[2],
                                             Int32 viswmin[2],
                                             Int32 viswmax[2]      )
{
    viswmin[0] = osgMax(wmin[0],_min[0]);
    viswmin[1] = osgMax(wmin[1],_min[1]);
    viswmax[0] = osgMin(wmax[0],_max[0]);
    viswmax[1] = osgMin(wmax[1],_max[1]);
    // not in region
    if(viswmin[0] > viswmax[0] ||
       viswmin[1] > viswmax[1])
        return false;
    else
        return true;
}

/** Check if one part of the geometry lays in the given region
 *
 * \param min    [ minx, miny ]
 * \param max    [ maxx, maxy ]
 *
 **/
bool TileGeometryLoad::checkRegion( Int32 min[2],
                                    Int32 max[2] )
{
    if(min[0] > _max[0] ||
       max[0] < _min[0] ||
       min[1] > _max[1] ||
       max[1] < _min[1])
        return false;
    else
        return true;
}

Real32 TileGeometryLoad::getFaceDistribution(Real32 cut)
{
    if(cut<=0)
    {
        return 0.0;
    }
    if(cut >=1.0)
    {
        return 1.0;
    }
    cut*=FACE_DISTRIBUTION_SAMPLING_COUNT-1;
    
    UInt32 a=(UInt32)(floor(cut));
    Real32 f=cut-a;

    return _faceDistribution[a] +
        (_faceDistribution[a+1] - _faceDistribution[a]) * f;
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
    static Char8 cvsid_hpp[] = OSG_TILE_GEOMETRY_LOADHEADER_CVSID;
}
