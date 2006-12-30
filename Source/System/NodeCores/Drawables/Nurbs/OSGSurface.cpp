/*---------------------------------------------------------------------------*\
 *                           OpenSG NURBS Library                            *
 *                                                                           *
 *                                                                           *
 * Copyright (C) 2001-2006 by the University of Bonn, Computer Graphics Group*
 *                                                                           *
 *                         http://cg.cs.uni-bonn.de/                         *
 *                                                                           *
 * contact: edhellon@cs.uni-bonn.de, guthe@cs.uni-bonn.de, rk@cs.uni-bonn.de *
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

#include <OSGAction.h>
#include <OSGDrawAction.h>     
#include <OSGRenderAction.h>   
#include <OSGIntersectAction.h>
#include <OSGRenderAction.h>
#include <OSGSimpleMaterial.h>
#include "OSGFatBorderChunk.h"

#include <OSGGeometry.h>   
#include <OSGGeoProperty.h>

#include <OSGGeoFunctions.h>
#include <OSGGeoPumpFactory.h>

#include <OSGGL.h>
#include <OSGGLU.h>
#include <OSGGLEXT.h>

#include "OSGSurface.h"

/*
#ifdef OSG_USE_ATI
#  include <GL/glx.h>
#  include <GL/glext.h>
#  include <GL/glATI.h>
#endif
*/

#include <OSGBSplineTrimmedSurface.h>
#include <OSGNurbsPatchSurface.h>
#include <OSGSimplePolygon.h>

#include <OSGpredicates.h> //for exactinit()

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: OSGSurface.cpp,v 1.13 2006-11-17 17:59:30 edhellon Exp $";
    static char cvsid_hpp[] = OSGSURFACE_HEADER_CVSID;
    static char cvsid_inl[] = OSGSURFACE_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const OSG::BitVector  Surface::CurveFieldMask = 
    (Surface::NumCurvesFieldMask |
     Surface::KnotLengthsFieldMask |
     Surface::DimensionsFieldMask |
     Surface::CurveControlPointsFieldMask |
     Surface::KnotsFieldMask |
     Surface::CurvesPerLoopFieldMask );

const OSG::BitVector  Surface::SurfaceFieldMask = 
    (Surface::DimUFieldMask |
     Surface::DimVFieldMask |
     Surface::KnotsUFieldMask |
     Surface::KnotsVFieldMask |
     Surface::ControlPointsFieldMask |
     Surface::ErrorFieldMask |
     Surface::IsDelaunayFieldMask |
     Surface::TextureControlPointsFieldMask );



/*! \class osg::Surface
    \ingroup Geometries
This is the OpenSG NURBS surface node. It supports an arbitrary number of trimming curves. The interface lets you define both rational and nonrational surfaces, and you can also vary rational and nonrational trimming curves.

You can edit the surface properties directly via the usual OpenSG methods.
You are required to use beginEditCP()/endEditCP() pairs, of course.
You may use the convenience fieldmask SurfaceFieldMask.

The error field means the maximum Euclidean error the tessellation will differ
from the analytical surface in 3D space. Generally the lesser it is,
the finer the tessellation is. For most surfaces 0.1 - 0.5 are generally
good choices.
*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

Surface::Surface(void) :
    Inherited()
{
//    std::cerr<<"constructor"<<std::endl;
    _trimmedSurface = NULL;
    _surfacePatch = NULL;
}

//! Copy Constructor

Surface::Surface(const Surface &source) :
    Inherited(source)
{

    // We need these for every class and every aspect, so we have to 
    // allocate them here.
    _trimmedSurface = new BSplineTrimmedSurface;
    _surfacePatch = new CNurbsPatchSurface;
}

//! Destructor

Surface::~Surface(void)
{
    if ( _trimmedSurface != NULL )
        delete _trimmedSurface;
    if ( _surfacePatch != NULL )
        delete _surfacePatch;
}


/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void Surface::initMethod (void)
{
    DrawAction::registerEnterDefault( getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          MaterialDrawablePtr,
                                          CNodePtr,
                                          Action *>
                                          (&MaterialDrawable::drawActionHandler));
  
    RenderAction::registerEnterDefault( getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          SurfacePtr,
                                          CNodePtr,
                                          Action *>
                                          (&Geometry::renderActionHandler));
   
    IntersectAction::registerEnterDefault( getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                         SurfacePtr,
                                         CNodePtr,
                                         Action *>(&Geometry::intersect));

    // init robust predicates
    ::exactinit();
    // turn appearance preserving tessellation on
    CErrorQuadTree::m_sbNormalApproximation = true;

}

//! react to field changes

void Surface::changed(BitVector whichField, UInt32 origin)
{
    if(whichField & ControlPointsFieldMask)
    {
        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrCheckValid)
            {
                SurfacePtr thisP(*this);

                if(_sfControlPoints.getValue()                    != NullFC &&
                   _sfControlPoints.getValue()->findParent(thisP) ==     -1 )
                {
                    GeoPositionsPtr pPos = _sfControlPoints.getValue();

                    _sfControlPoints.setValue(NullFC);

                    setControlPoints(pPos);
                }
            }
            else if(origin & ChangedOrigin::AbstrIncRefCount)
            {
                addRefCP(_sfControlPoints.getValue());
            }
            else
            {
                GeoPositionsPtr pPos = _sfControlPoints.getValue();

                _sfControlPoints.setValue(NullFC);

                setControlPoints(pPos);
            }
        }
    }

    if(whichField & TextureControlPointsFieldMask)
    {
        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrCheckValid)
            {
                SurfacePtr thisP(*this);

                if(_sfTextureControlPoints.getValue()                    != NullFC &&
                   _sfTextureControlPoints.getValue()->findParent(thisP) ==     -1 )
                {
                    GeoTexCoordsPtr pTexCoord = _sfTextureControlPoints.getValue();

                    _sfTextureControlPoints.setValue(NullFC);

                    setTextureControlPoints(pTexCoord);
                }
            }
            else if(origin & ChangedOrigin::AbstrIncRefCount)
            {
                addRefCP(_sfTextureControlPoints.getValue());
            }
            else
            {
                GeoTexCoordsPtr pTexCoord = _sfTextureControlPoints.getValue();

                _sfTextureControlPoints.setValue(NullFC);

                setTextureControlPoints(pTexCoord);
            }
        }
    }

    // only Client needs to tessellate / retessellate...
//  if( ( origin & ChangedOrigin::Sync ) == 0 )
    {
        if( ( whichField & DimUFieldMask ) ||
            ( whichField & DimVFieldMask ) ||
            ( whichField & KnotsUFieldMask ) ||
            ( whichField & KnotsVFieldMask ) ||
            ( whichField & ControlPointsFieldMask ) ||
            ( whichField & NumCurvesFieldMask ) ||
            ( whichField & KnotLengthsFieldMask ) ||
            ( whichField & DimensionsFieldMask ) ||
            ( whichField & CurveControlPointsFieldMask ) ||
            ( whichField & KnotsFieldMask ) ||
            ( whichField & CurvesPerLoopFieldMask ) ||
            ( whichField & TextureControlPointsFieldMask ) )
        {
//          SLOG <<"OSGSurface::changed: have to re-tessellate..." << endLog;
            SurfacePtr tmpPtr(*this);

            beginEditCP(tmpPtr, DirtyMaskFieldMask);
            {
                getDirtyMask() |= TESSELLATE;
            }
            endEditCP  (tmpPtr, DirtyMaskFieldMask);

            Window::refreshGLObject(getSurfaceGLId());
        }
        else if( ( whichField & ErrorFieldMask ) ||
                 ( whichField & IsDelaunayFieldMask ) )
        {
//          SLOG <<"OSGSurface: only error or delaunay mask" << endLog;
//          std::cerr << origin << std::endl;
            SurfacePtr tmpPtr(*this);
            
            beginEditCP(tmpPtr, DirtyMaskFieldMask);
            {
                getDirtyMask() |= RETESSELLATE;
            }
            endEditCP  (tmpPtr, DirtyMaskFieldMask);

            Window::refreshGLObject(getSurfaceGLId());
        }
    }
        
    // you should call the parent's changed() function in case
    // it needs to update inherited fields.
    Inherited::changed( whichField, origin );       
//    std::cerr<<"Surface::changed:   texcoords ptr: " << getTexCoords() << std::endl;
//    std::cerr<<"Surface::changed:   texcoords1 ptr: " << getTexCoords1() << std::endl;
    
}


//! get desired error.
/*
 *  This should be called from the user program once per frame for every
 *  patch. This returns the patch's desired error level for the
 * dynamic LOD balancing.
 */
Real64 Surface::getDesiredError( Pnt3f viewPos, Real64 halfPixelSize )
{
    Vec3f   dist;
    Real64  distance;

    FindClosestPoint( dist, viewPos );
    distance = dist.squareLength( );

/*    if( distance < _max.dist2( _min ) )
    {
        FindClosestPointExact( dist, viewPos );
        distance = dist.squareLength( );
    }*/

    distance = sqrt( distance );
    // multiply the length of a line at distance one that projects 
    // to half a pixel with the distance of the current BB to get 
    // the maximum geometric error that is allowed for the surface 
    // within the BB
    Real64 desired_error = halfPixelSize * distance;

//  std::cerr << distance << " " << desired_error << std::endl;

    if( desired_error < _max.dist( _min ) * 0.001 ) // 0.1% of bounding box
    {
//          printf( "error below minimum => setting to minimal error %f\n", _max.dist( _min ) * 0.001 );
            desired_error = _max.dist( _min ) * 0.001;
    }

    return desired_error;
}

//! update error field according to dynamic LOD
/*
 *  This should becalled from the render() function in order
 *  to only call this for nodes that are not culled.
 *
 */
bool Surface::updateError( Pnt3f viewPos, Real64 halfPixelSize )        
{
    Real64  d_max_error = getDesiredError( viewPos, halfPixelSize );

    // FIXME: this will convert the surface data once again,
    // not very effective... should only be retessellated !!!
    // FIXME: do we have to change the error in every frame ???
    Real32  current_error = getError();
    if ( d_max_error < current_error )
    {
        std::cerr << "retessellating due to too high error: " << d_max_error
                << " " << current_error << std::endl;
        Real32 new_error = osgMin( d_max_error, current_error / 2.0 );
        SurfacePtr thisPtr =  SurfacePtr( this );    
        beginEditCP( thisPtr, Surface::ErrorFieldMask );
        {
            setError( d_max_error / 2.0 );
        }
        endEditCP( thisPtr, Surface::ErrorFieldMask );
    }
    else if ( d_max_error > current_error * 4.0 )
    {
        std::cerr << "retessellating due to too low error: " << d_max_error
                << " " << current_error << std::endl;
        SurfacePtr thisPtr =  SurfacePtr( this );    
        beginEditCP( thisPtr, Surface::ErrorFieldMask );
        {
            setError( d_max_error / 2.0 );
        }
        endEditCP( thisPtr, Surface::ErrorFieldMask );
    }
    return true;  
}


// protected


/* given an set of arbitrary bounding volumes
 * find the vector to the point on the volume that is closest to the view pos
*/
void Surface::FindClosestPoint( Vec3f& rDist, const Pnt3f viewPos ) const
{
    const UInt32    parent_cnt = getParents( ).size( );
    UInt32          parent_idx;
    Real64          min_dist = 1e300;
    Vec3f           temp_dist;
    Real64          curr_dist;

    for( parent_idx = 0; parent_idx < parent_cnt; ++parent_idx )
    {
        switch( getParents( )[ 0 ]->getVolume( ).getType( ) )
        {
        case DynamicVolume::BOX_VOLUME:
            {
                Pnt3f   bb_min, bb_max;

                getParents( )[ 0 ]->getVolume( ).getBounds( bb_min, bb_max );

//              std::cerr << bb_min << " " << bb_max << " " << viewPos << std::endl;

                if( viewPos[0] < bb_min[0] )
                {
                    temp_dist[0] = viewPos[0] - bb_min[0];
                }
                else if( viewPos[0] > bb_max[0] )
                {
                    temp_dist[0] = viewPos[0] - bb_max[0];
                }
                else
                {
                    temp_dist[0] = 0.0;
                }

                if( viewPos[1] < bb_min[1] )
                {
                    temp_dist[1] = viewPos[1] - bb_min[1];
                }
                else if( viewPos[1] > bb_max[1] )
                {
                    temp_dist[1] = viewPos[1] - bb_max[1];
                }
                else
                {
                    temp_dist[1] = 0.0;
                }

                if( viewPos[2] < bb_min[2] )
                {
                    temp_dist[2] = viewPos[2] - bb_min[2];
                }
                else if( viewPos[2] > bb_max[2] )
                {
                    temp_dist[2] = viewPos[2] - bb_max[2];
                }
                else
                {
                    temp_dist[2] = 0.0;
                }
            }
            break;
        case DynamicVolume::SPHERE_VOLUME:
            {
                Real64  length;
                Pnt3f   center;

                getParents( )[ 0 ]->getVolume( ).getCenter( center );
                temp_dist = center - viewPos;
                length = temp_dist.length( ) - getParents( )[ 0 ]->getVolume( ).getScalarVolume( );
                if( length > 0.0 )
                {
                    temp_dist.normalize( );
                    temp_dist *= length;
                }
                else
                {
                    temp_dist[0] = temp_dist[1] = temp_dist[2] = 0.0;
                }
            }
            break;
        }
        curr_dist = temp_dist.squareLength( );
        if( curr_dist < min_dist )
        {
            min_dist = curr_dist;
            rDist = temp_dist;
        }
    }
}


void Surface::FindClosestPointExact( Vec3f& rDist, const Pnt3f viewPos ) const
{
//  const GeoPositions3fPtr cpcl_points = GeoPositions3fPtr::dcast( cpcl_geo->getPositions( ) );
    const GeoPositions3fPtr cpcl_points = GeoPositions3fPtr::dcast( getPositions() );
    const unsigned int      cui_idx_cnt = cpcl_points->getSize( );
    Pnt3f                   cl_pos;
    unsigned int            ui_idx;
    Vec3f                   cl_temp;
    double                  d_min = DBL_MAX;
    double                  d_temp;

    for( ui_idx = 0; ui_idx < cui_idx_cnt; ++ui_idx )
    {
        cl_pos = cpcl_points->getValue( ui_idx );
        cl_temp = cl_pos - viewPos;
        d_temp = cl_temp.squareLength( );
        if( d_temp <= d_min )
        {
            d_min = d_temp;
            rDist = cl_temp;
        }
    }
}


//! tessellate
void Surface::tessellate( void )
{
    // local variables for tessellation
//    BSplineTrimmedSurface _trimmedSurface;  // internal representation of surface
//    CNurbsPatchSurface cpatch;              // "tessellator" object
//    simplepolygonvector tris;               // resulting indexed triangle set
    std::vector< SimplePolygon > tris;
    std::vector< Pnt3f > gverts;            // resulting vertices
    std::vector< Vec3f > norms;             // resulting surface normals
    std::vector< Pnt2f > texturecoords;     // resulting texture coordinates
    
    Int32 err = convertSurface();
    if ( err ) 
    {
//        exit(-1);
        return;
    }
    if ( _sfTextureControlPoints.getValue() == NullFC )
    {
        err = tessellateSurface( tris, gverts, norms);
#ifdef OSG_NURBS_DEBUG
        std::cerr<<"Surface::tessellate err1: " << err << " #tris: " << tris.size() << std::endl;
#endif /* OSG_NURBS_DEBUG */
        if ( err ) return;    
        (void) buildSurface( tris, gverts, norms, texturecoords );
    }
    else
    {
/*        
        // fragment program stuff (no normals)
        err = tessellateSurface( tris, gverts, texturecoords );
        if ( err ) return;
        (void) buildSurface( tris, gverts, texturecoords );
*/        
        // classic texturemapping stuff (both normals and texcoords)
        err = tessellateSurface( tris, gverts, norms, texturecoords );
#ifdef OSG_NURBS_DEBUG
        std::cerr<<"Surface::tessellate err2: " << err << " #tris: " << tris.size() << std::endl;
#endif /* OSG_NURBS_DEBUG */
        if ( err ) return;
        (void) buildSurface( tris, gverts, norms, texturecoords );
       
    }
    
    
//        std::cerr<<"Surface::tessellate:   texcoords ptr: " << getTexCoords() << std::endl;
//        std::cerr<<"Surface::tessellate:   texcoords1 ptr: " << getTexCoords1() << std::endl;
    
//    buildPointSet();
//    SLOG << "tessellate NI" << endLog;   
}

//! retessellate
void Surface::reTessellate( void )
{
    std::vector< SimplePolygon > tris;
    std::vector< Pnt3f > gverts;            // resulting vertices
    std::vector< Vec3f > norms;             // resulting surface normals
    std::vector< Pnt2f > texturecoords;     // resulting texture coordinates

    
    //FIXMEZ0RZ:
//    _surfacePatch->setSurface( _trimmedSurface );
    if ( getError() < DCTP_EPS )
    {
//        SLOG << " Surface::tessellate: correcting negative/zero error" <<
  //              endLog;
        setError( 0.2 );
    }
    
    _surfacePatch->setError ( getError() );
    SSurface *surfdata = _surfacePatch->getSurfaceData();

    if ( _sfTextureControlPoints.getValue() == NullFC )
    {
        _surfacePatch->getTessellation( gverts, norms, tris, getIsDelaunay() );
        (void) buildSurface( tris, gverts, norms, texturecoords );
    }
    else
    {
/*        
        //normalmap stuff
        _surfacePatch->getTessellation( gverts, texturecoords, tris, getIsDelaunay() );
        (void) buildSurface( tris, gverts, texturecoords );
*/
   
       //classic texturemapped stuff
       _surfacePatch->getTessellation( gverts, norms, texturecoords, 
                                       tris, getIsDelaunay() );
       (void) buildSurface( tris, gverts, norms, texturecoords );
      
    }
    
//        std::cerr<<"Surface::reTessellate:   texcoords ptr: " << getTexCoords() << std::endl;
//        std::cerr<<"Surface::reTessellate:   texcoords1 ptr: " << getTexCoords1() << std::endl;
        
}

//internal
Int32 Surface::convertSurface( void )
{
//    BSplineTrimmedSurface *_trimmedSurface = (BSplineTrimmedSurface*)trimsurf;

    bool israt;
    GeoPositions3fPtr pPos = GeoPositions3fPtr::dcast(
        _sfControlPoints.getValue());
    GeoPositions4fPtr pRatPos = GeoPositions4fPtr::dcast(
        _sfControlPoints.getValue());

//    std::cerr<< "pPos: " << pPos << " pRatPos: " << pRatPos << std::endl;
    if(_sfControlPoints.getValue() == NullFC)
    {
        SLOG << "Surface::tessellate: null surfacecontrol prop " << endLog;
        return -1;
    }

    if ( pPos != NullFC )
    {
        israt = false;   
    }
    else if ( pRatPos != NullFC )
    {
        israt = true;
    }
    else
    {
        SLOG << "Surface::tessellate: null surfacecontrol prop " << endLog;
        return -1;
    }
    MFPnt3f *polyControlPoints;
    MFPnt4f *ratControlPoints;
    UInt32 cpsize;
    if ( !israt )
    {
        polyControlPoints = &(pPos->getField());
        cpsize = polyControlPoints->size();
    }
    else
    {
        ratControlPoints = &(pRatPos->getField());
        cpsize = ratControlPoints->size();
    }
//    MFPnt3f &_mfControlPoints = pPos->getField();
    
    // check knots, dimensions and control points
    if( cpsize == 0 ) 
    {
        SLOG << "Surface::tessellate: null surfacecontrol points " << endLog;
        return -1;
    }
/*    if ( cpdim !=3 && cpdim !=4 )
    {
        SLOG << "Surface::tessellate: wrong control point dimensions " <<
                endLog;
    }*/
    UInt32 dimu = _sfDimU.getValue();
    UInt32 dimv = _sfDimV.getValue();
    if ( dimu == 0 || dimv == 0 )
    {
        SLOG << "Surface::tessellate: 0 dimensions " << endLog;
        return -1;
    }
    UInt32 knotusize = _mfKnotsU.size();
    UInt32 knotvsize = _mfKnotsV.size();
    if ( knotusize == 0 || knotvsize == 0 )
    {
        SLOG << "Surface::tessellate: empty knotvectors " << endLog;
        return -1;
    }
    UInt32 cpusize = knotusize - dimu - 1;
    UInt32 cpvsize = knotvsize - dimv - 1;
    if ( cpusize < 1 || cpvsize < 1 || cpusize * cpvsize != cpsize )
    {
        SLOG << cpusize << "x" << cpvsize << ":" << cpsize << endLog;
        SLOG << "Surface::tessellate: inconsistent attributes " << endLog;
        return -1;
    }
    if ( _sfNumCurves.getValue() == 0  ) // no trimming specified, add dummy trimming
    {
        Real64 umin = _mfKnotsU[ 0 ];
        Real64 vmin = _mfKnotsV[ 0 ];
        Real64 umax = _mfKnotsU[ knotusize - 1 ];
        Real64 vmax = _mfKnotsV[ knotvsize - 1 ];
        
        std::vector< Real64 > tmpknotvec(4);
        std::vector< Pnt2f > tmpcps(2);
        UInt32 dim = 1;
        tmpknotvec[ 0 ] = 0.0;
        tmpknotvec[ 1 ] = 0.0;
        tmpknotvec[ 2 ] = 1.0;
        tmpknotvec[ 3 ] = 1.0;

        // (umin, vmin) -> (umax,vmin)
        tmpcps[0][0] = umin; tmpcps[0][1] = vmin;
        tmpcps[1][0] = umax; tmpcps[1][1] = vmin;
        addCurve( dim, tmpknotvec, tmpcps );

        // (umax, vmin) -> (umax,vmax)
        tmpcps[0][0] = umax; tmpcps[0][1] = vmin;
        tmpcps[1][0] = umax; tmpcps[1][1] = vmax;
        addCurve( dim, tmpknotvec, tmpcps );

        // (umax, vmax) -> (umin,vmax)
        tmpcps[0][0] = umax; tmpcps[0][1] = vmax;
        tmpcps[1][0] = umin; tmpcps[1][1] = vmax;
        addCurve( dim, tmpknotvec, tmpcps );

        // (umin, vmax) -> (umin,vmin)
        tmpcps[0][0] = umin; tmpcps[0][1] = vmax;
        tmpcps[1][0] = umin; tmpcps[1][1] = vmin;
        addCurve( dim, tmpknotvec, tmpcps );
    }

    // now we checked everything, let's convert the surface+trimcurves
    // to the internal representation
    
    // first create surface
    BSplineTensorSurface tensor_surface;
    UInt32 i, j, k;
    DCTPVec4dmatrix qnet;
    Vec4d vec4;
    qnet.resize( cpusize );
    
    for ( i = 0; i < cpusize; ++i )
    {
        qnet[ i ].resize( cpvsize );
        for ( j = 0; j < cpvsize; ++j )
        {
            k = i * cpvsize + j;
            if ( !israt )
            {
                vec4[0] = (*polyControlPoints)[k][0];
                vec4[1] = (*polyControlPoints)[k][1];
                vec4[2] = (*polyControlPoints)[k][2];
                vec4[3] = 1.0f; //!!!!!!!!!!!!!!!!!!!!
//                SLOG << "qnet["<<i<<"]["<<j<<"]: " << vec4 << endLog;
//                SLOG << "k: " << k << endLog;
            }
            else
            {
                vec4[0] = (*ratControlPoints)[k][0];
                vec4[1] = (*ratControlPoints)[k][1];
                vec4[2] = (*ratControlPoints)[k][2];
                vec4[3] = (*ratControlPoints)[k][3];
//                SLOG << "qnet["<<i<<"]["<<j<<"]: " << vec4 << endLog;
//                SLOG << "k: " << k << endLog;
            }
            qnet[ i ][ j ] = vec4;
        }
    }
    tensor_surface.setControlPointMatrix( qnet );
    // convert knotvectors
    DCTPdvector knotuvec(knotusize);
    DCTPdvector knotvvec(knotvsize);
    for ( i = 0; i < knotusize; ++i )
    {
        knotuvec[ i ] = _mfKnotsU[ i ];
    }
    for ( i = 0; i < knotvsize; ++i )
    {
        knotvvec[ i ] = _mfKnotsV[ i ];
    }
    tensor_surface.setKnotsAndDimension( knotuvec, dimu, knotvvec, dimv );
//    std::cerr<<"0.2"<<std::endl;
//    fprintf(stderr,"%x\n", _trimmedSurface);
    _trimmedSurface->setSurface( tensor_surface );
//    std::cerr<<"0.3"<<std::endl;

    // now create/convert trimming loops
    trimmingloop trimloops;
    UInt32 cplsize = _mfCurvesPerLoop.size();
    trimloops.resize( cplsize );
    for ( i = 0; i < cplsize; ++i )
    {
        trimloops[ i ].resize( _mfCurvesPerLoop[ i ] );
    }
    UInt32 actknotoffset = 0;
    UInt32 actcpoffset = 0;
    UInt32 actloopoffset = 0;
    UInt32 actcurveno = 0;
    UInt32 acttrimcpsize = 0;
    DCTPdvector actknots;
    DCTPVec3dvector acttrimcps;
    BSplineCurve2D actcurve;
    for ( i = 0; i < trimloops.size(); ++i )
    {
        for ( j = 0; j < trimloops[i].size(); ++j )
        {
            actknots.resize( _mfKnotLengths[ actcurveno ] );
//            SLOG << "Debug: _mfKnotLengths[ actcurveno ]: " <<
//                    _mfKnotLengths[ actcurveno ] << " actcurveno: " <<
//                    actcurveno << endLog;
            acttrimcpsize = actknots.size() - _mfDimensions[ actcurveno ] - 1;
            if ( acttrimcpsize < 1 ) 
            {
                SLOG << "Surface::tessellate: wrong trimming curve attributes "
                        << endLog;
                return -1;
            }
            acttrimcps.resize( acttrimcpsize );
            for ( k = 0; k < actknots.size(); ++k )
            {
                actknots[ k ] = _mfKnots[ actknotoffset + k ];
            }
            actknotoffset += actknots.size();
            actcurve.setKnotsAndDimension( actknots, 
                                           _mfDimensions[ actcurveno ] );
//            SLOG << "Debug: actknotoffset: " << actknotoffset << endLog;
//            SLOG << "Debug: actcpoffset: " << actcpoffset << endLog;
//            SLOG << "Debug: _mfCurveControlPoints.size(): " <<
//                    _mfCurveControlPoints.size() << endLog;
//            SLOG << "Debug: _mfKnots.size(): " << _mfKnots.size() << endLog;
//            SLOG << "Debug: acttrimcps.size(): " << acttrimcps.size() << endLog;
            for ( k = 0; k < acttrimcpsize; ++k )
            {
//                SLOG <<"Debug: k: " << k << endLog;
                acttrimcps[ k ][0] = _mfCurveControlPoints[ actcpoffset + k ][0];
                acttrimcps[ k ][1] = _mfCurveControlPoints[ actcpoffset + k ][1];
                acttrimcps[ k ][2] = _mfCurveControlPoints[ actcpoffset + k ][2];
            }
            actcpoffset += acttrimcpsize;
            actcurve.setControlPointVector( acttrimcps );

            trimloops[i][j] = actcurve;
            actcurveno++;
        }
        
    }
    _trimmedSurface->setTrimmingLoops( trimloops );
    _trimmedSurface->normalize();
    
//    global_surf = *_trimmedSurface;    
    return 0;   
}


//internal
// normal, nontexturemapped
Int32 Surface::tessellateSurface( std::vector< SimplePolygon > &triangles,
                                  std::vector< Pnt3f > &gverts, 
                                  std::vector< Vec3f > &norms )
{
//    BSplineTrimmedSurface *_trimmedSurface = (BSplineTrimmedSurface*)trimsurf;
//    std::vector< SimplePolygon > *triangles = (std::vector< SimplePolygon > *)tris;
//    CNurbsPatchSurface cpatch;              // "tessellator" object
    std::vector< Pnt2f > dummy;
    _surfacePatch->setSurface( _trimmedSurface, dummy, false );
    if ( _sfError.getValue() < DCTP_EPS )
    {
//        SLOG << " Surface::tessellate: correcting negative/zero error" <<
//                endLog;
        _sfError.setValue( 0.2 );
    }
    _surfacePatch->setError ( _sfError.getValue() );
    _surfacePatch->getTessellation( gverts, norms, triangles, getIsDelaunay() );
    SSurface *surfaceData =  _surfacePatch->getSurfaceData();
    _min = Pnt3d( surfaceData->clMin[0], surfaceData->clMin[1],
                  surfaceData->clMin[2] );
    _max = Pnt3d( surfaceData->clMax[0], surfaceData->clMax[1],
                  surfaceData->clMax[2] );
#ifdef OSG_ARBITRARY_SPLIT
    _minParam = Pnt2d( surfaceData->clMinParam[0] , surfaceData->clMinParam[1] );
    _maxParam = Pnt2d( surfaceData->clMaxParam[0] , surfaceData->clMaxParam[1] );
#endif

    
//    std::cerr<< "min, max: [" << _min << "][" << _max << "]" << std::endl;
//    std::cerr<< "minparam, maxparam: [" << _minParam << "][ " << _maxParam  << "]" << std::endl;
        
    return 0;
}

//internal
// surface with texturemap, no normalmap!
Int32 Surface::tessellateSurface( std::vector< SimplePolygon > &triangles,
                                  std::vector< Pnt3f > &gverts,
                                  std::vector< Vec3f > &norms,
                                  std::vector< Pnt2f > &texcoords )
{
//    BSplineTrimmedSurface *_trimmedSurface = (BSplineTrimmedSurface*)trimsurf;
//    std::vector< SimplePolygon > *triangles = (std::vector< SimplePolygon > *)tris;
//    CNurbsPatchSurface cpatch;              // "tessellator" object
    GeoTexCoords2fPtr pTexPos = GeoTexCoords2fPtr::dcast(_sfTextureControlPoints.getValue());
    std::vector<Pnt2f > tmptexcoords;
    UInt32 i;
    UInt32 s =  pTexPos->getField().size();
    for ( i = 0; i < s; ++i )
    {
        tmptexcoords.push_back( Pnt2f( pTexPos->getField()[i][0],
                                       pTexPos->getField()[i][1]));
    }
    _surfacePatch->setSurface( _trimmedSurface,
                               tmptexcoords,
                               true);
    if ( _sfError.getValue() < DCTP_EPS )
    {
//        SLOG << " Surface::tessellate: correcting negative/zero error" <<
//                endLog;
        _sfError.setValue( 0.2 );
    }
    _surfacePatch->setError ( _sfError.getValue() );
    _surfacePatch->getTessellation( gverts, norms, texcoords, triangles, getIsDelaunay() );
        
//    std::cerr<< "norms.size(): " << norms.size() << " texcoords.size(): " <<
//            texcoords.size() << std::endl;
    SSurface *surfaceData =  _surfacePatch->getSurfaceData();
    _min = Pnt3d( surfaceData->clMin[0], surfaceData->clMin[1],
                  surfaceData->clMin[2] );
    _max = Pnt3d( surfaceData->clMax[0], surfaceData->clMax[1],
                  surfaceData->clMax[2] );
#ifdef OSG_ARBITRARY_SPLIT
    _minParam = Pnt2d( surfaceData->clMinParam[0] , surfaceData->clMinParam[1] );
    _maxParam = Pnt2d( surfaceData->clMaxParam[0] , surfaceData->clMaxParam[1] );
#endif

    
//    std::cerr<< "min, max: [" << _min << "][" << _max << "]" << std::endl;
//    std::cerr<< "minparam, maxparam: [" << _minParam << "][ " << _maxParam  << "]" << std::endl;
        
    return 0;
}

//internal
// surface with normalmaps
Int32 Surface::tessellateSurface( std::vector< SimplePolygon > &triangles,
                                  std::vector< Pnt3f > &gverts, 
                                  std::vector< Pnt2f > &texcoords )
{
//    BSplineTrimmedSurface *_trimmedSurface = (BSplineTrimmedSurface*)trimsurf;
//    std::vector< SimplePolygon > *triangles = (std::vector< SimplePolygon > *)tris;
//    CNurbsPatchSurface cpatch;              // "tessellator" object
    GeoTexCoords2fPtr pTexPos = GeoTexCoords2fPtr::dcast(_sfTextureControlPoints.getValue());
    std::vector<Pnt2f > tmptexcoords;
    UInt32 i;
    UInt32 s =  pTexPos->getField().size();
    for ( i = 0; i < s; ++i )
    {
        tmptexcoords.push_back( Pnt2f( pTexPos->getField()[i][0],
                                       pTexPos->getField()[i][1]));
    }
    _surfacePatch->setSurface( _trimmedSurface,
                               tmptexcoords,
                               true);
    if ( _sfError.getValue() < DCTP_EPS )
    {
//        SLOG << " Surface::tessellate: correcting negative/zero error" <<
//                endLog;
        _sfError.setValue( 0.2 );
    }
    _surfacePatch->setError ( _sfError.getValue() );
    std::vector< Vec3f > norms;
    _surfacePatch->getTessellation( gverts, norms, triangles, false );
    _surfacePatch->getTessellation( gverts, texcoords, triangles, getIsDelaunay() );
    
    SSurface *surfaceData =  _surfacePatch->getSurfaceData();
    _min = Pnt3d( surfaceData->clMin[0], surfaceData->clMin[1],
                  surfaceData->clMin[2] );
    _max = Pnt3d( surfaceData->clMax[0], surfaceData->clMax[1],
                  surfaceData->clMax[2] );
#ifdef OSG_ARBITRARY_SPLIT
    _minParam = Pnt2d( surfaceData->clMinParam[0] , surfaceData->clMinParam[1] );
    _maxParam = Pnt2d( surfaceData->clMaxParam[0] , surfaceData->clMaxParam[1] );
#endif

    
//    std::cerr<< "min, max: [" << _min << "][" << _max << "]" << std::endl;
//    std::cerr<< "minparam, maxparam: [" << _minParam << "][ " << _maxParam  << "]" << std::endl;
        
    return 0;
}

void Surface::calcIndexMapping(void)
{
    getIndexMapping().clear();

    UInt16 im = 0;
    if(getPositions() != NullFC)
        im |= Geometry::MapPosition;
    if(getNormals() != NullFC)
        im |= Geometry::MapNormal;
    if(getTexCoords() != NullFC)
        im |= Geometry::MapTexCoords;
    if(getTexCoords1() != NullFC)
        im |= Geometry::MapTexCoords1;

    if(im != 0)
        getIndexMapping( ).push_back(im);
}


//internal
// normal surface
Int32 Surface::buildSurface( std::vector< SimplePolygon > &triangles,
                             std::vector< Pnt3f > &gverts,
                             std::vector< Vec3f > &norms,
                             std::vector< Pnt2f > &texcoords )

{
    // FIXME:
    //
    // At least on Linux/ATI with the current OpenGL drivers
    // TextureCoordinate1 doesn't get passed to the vertex program
    // unless there's TextureCoordinate0 present.
    // Might even crash older drivers, and might also be a problem
    // on Windows with some driver versions.
    //
    // Therefore the Surface uses TextureCoordinate0 to pass tangent
    // coordinates to the FatBorderChunk, thus texturing an OSGSurface
    // that uses FBs should begin in TextureCoordinate1. 
    // 
    // Currently only 1 texture is supported (copied to the fragment
    // program for further processing, and built by this function)
    // more can be easily added if it's a problem.
    //
    // FIXME END
    
    GeoPTypesPtr            pcl_type = getTypes();
    GeoPLengthsPtr          pcl_size = getLengths();
    GeoPositionsPtr         pcl_points = getPositions();
    GeoNormalsPtr           pcl_norms = getNormals();
    GeoIndicesPtr           pcl_indices = getIndices( );
    GeoTexCoordsPtr         pcl_texcoords = getTexCoords1();
    //FatBorderChunk parameters are always passed in TextureCoordinate.
    GeoTexCoords3fPtr       pcl_tangents = GeoTexCoords3fPtr::dcast( getTexCoords( ) );
    SimpleMaterialPtr       pcl_mat = SimpleMaterialPtr::dcast( getMaterial( ) );
    SurfacePtr              thisPtr = SurfacePtr( this );
//  GeometryPtr         pcl_geo = Geometry::create( );
    SimplePolygon           *pcl_face;
    const UInt32            cui_faces = triangles.size();
    UInt32                  ui_face;
    BSplineTensorSurface    cl_surf = _trimmedSurface->getSurface();
    int                     i_err;
    Vec3d                   cl_norm;
    const UInt32            cui_verts = gverts.size( );
    UInt32                  ui_vert;
    SSurface                *pt_surfdata = _surfacePatch->getSurfaceData( );
    const UInt32            cui_loop_cnt = pt_surfdata->vvclEdgeLoops.size( );
    UInt32                  ui_loop;
    UInt32                  ui_vertex_cnt;
    UInt32                  ui_idx;
    UInt32                  ui_used;
    Vec3d                   *pcl_actn;
    Vec3d                   *pcl_actv;
    Vec3d                   *pcl_nextv;
    Vec3d                   *pcl_prevv;
    Vec3f                   cl_v1, cl_v2, cl_tangent;
    std::vector< Int32 >    vi_new_idx( cui_verts );
    bool                    b_show_trimming = false;
   
    // check if material has the fat border chunk
    if( pcl_mat != NullFC )
    {
        const UInt32    cui_chunk_cnt = pcl_mat->getChunks( ).size( );
        UInt32          ui_chunk;

        for( ui_chunk = 0; ui_chunk < cui_chunk_cnt; ++ui_chunk )
        {
            if( FatBorderChunkPtr::dcast( pcl_mat->getChunks( ui_chunk ) ) != NullFC )
//            if( VertexProgramChunkPtr::dcast( pcl_mat->getChunks( ui_chunk ) ) != NullFC )
            {
                b_show_trimming = true;
                break;
            }
        }
    }

//    std::cerr<<"show_trimming: " << b_show_trimming << std::endl;
    if ( pcl_type == NullFC )
    {
        pcl_type = GeoPTypesUI8::create();
    }
    if ( pcl_size == NullFC )
    {
        pcl_size = GeoPLengthsUI32::create();
    }
    if ( pcl_points == NullFC )
    {
        pcl_points = GeoPositions3f::create();
    }
    if ( ( norms.size( ) > 0 ) && ( pcl_norms == NullFC ) )
    {
        pcl_norms = GeoNormals3f::create();
    }
    if ( pcl_indices == NullFC )
    {
        pcl_indices = GeoIndicesUI32::create();
    }
    if ( ( texcoords.size( ) > 0 ) && ( pcl_texcoords == NullFC ) )
    {
        pcl_texcoords = GeoTexCoords2f::create();
    }
    if( b_show_trimming )
    {
        if( pcl_tangents == NullFC )
        {
            pcl_tangents = GeoTexCoords3f::create( );
        }
    }
    else
    {
        if( pcl_tangents != NullFC )
        {
            beginEditCP( thisPtr, Geometry::TexCoordsFieldMask );
            {
                setTexCoords( NullFC );
            }
            endEditCP( thisPtr, Geometry::TexCoordsFieldMask );
        }
    }
    
    // check for unused points
    for( ui_vert = 0; ui_vert < cui_verts; ++ui_vert )
    {
        vi_new_idx[ ui_vert ] = -1;
    }
    for( ui_face = 0; ui_face < cui_faces; ++ui_face )
    {
        pcl_face = &triangles[ ui_face ];
        vi_new_idx[ pcl_face->vertices[ 0 ] ] = 0;
        vi_new_idx[ pcl_face->vertices[ 1 ] ] = 0;
        vi_new_idx[ pcl_face->vertices[ 2 ] ] = 0;
    }

    // calculate new indices
    ui_used = 0;
    for( ui_vert = 0; ui_vert < cui_verts; ++ui_vert )
    {
        if( vi_new_idx[ ui_vert ] >= 0 )
        {
            vi_new_idx[ ui_vert ] = ui_used;
            ++ui_used;
        }
    }

//  m_vtSurfaces[ uiSurface ].uiTriangleCnt = cui_faces;
//  m_vclNormal.resize( m_vclParameterVertices.size( ) );

    beginEditCP( pcl_type, GeoPTypesUI8::GeoPropDataFieldMask );
    {
//        std::cerr<<"fuck3"<<std::endl; 
        pcl_type->clear();
//        std::cerr<<"fuck4"<<std::endl; 
        pcl_type->push_back( GL_TRIANGLES );
//        std::cerr<<"fuck5"<<std::endl;
        if( b_show_trimming )
        {
            for( ui_loop = 0; ui_loop < cui_loop_cnt; ++ui_loop )
            {
                pcl_type->push_back( GL_TRIANGLE_STRIP );
            }
        } // b_show_trimming
    }
    endEditCP( pcl_type, GeoPTypesUI8::GeoPropDataFieldMask );
//    std::cerr<<"types"<<std::endl;
    beginEditCP( pcl_size, GeoPLengthsUI32::GeoPropDataFieldMask );
    {
        pcl_size->clear();
        pcl_size->push_back( 3 * cui_faces );
        ui_idx = 3 * cui_faces;
        if ( b_show_trimming )
        {
            for( ui_loop = 0; ui_loop < cui_loop_cnt; ++ui_loop )
            {
                pcl_size->push_back( 2 + 2 * pt_surfdata->vvclEdgeLoops[ ui_loop ].size( ) );
                ui_idx += 2 + 2 * pt_surfdata->vvclEdgeLoops[ ui_loop ].size( );
            }
        }
//      std::cerr << ui_idx << " indices" << std::endl;
    }
    endEditCP( pcl_size, GeoPLengthsUI32::GeoPropDataFieldMask );
//    std::cerr<<"size"<<std::endl;

    beginEditCP( pcl_points, GeoPositions3f::GeoPropDataFieldMask );
    {
        pcl_points->clear();
        for( ui_vert = 0; ui_vert < cui_verts; ++ui_vert )
        {
            if( vi_new_idx[ ui_vert ] >= 0 )
            {
                pcl_points->push_back( gverts[ ui_vert ] );
            }
        }
        if( b_show_trimming )
        {
            for( ui_loop = 0; ui_loop < cui_loop_cnt; ++ui_loop )
            {
                ui_vertex_cnt = pt_surfdata->vvclEdgeLoops[ ui_loop ].size( );
                for( ui_vert = 0; ui_vert < ui_vertex_cnt; ++ui_vert )
                {
                    pcl_points->push_back( Pnt3f( pt_surfdata->vvclEdgeLoops3D[ ui_loop ][ ui_vert ][0],
                                                  pt_surfdata->vvclEdgeLoops3D[ ui_loop ][ ui_vert ][1],
                                                  pt_surfdata->vvclEdgeLoops3D[ ui_loop ][ ui_vert ][2] ) );
                    pcl_points->push_back( Pnt3f( pt_surfdata->vvclEdgeLoops3D[ ui_loop ][ ui_vert ][0],
                                                  pt_surfdata->vvclEdgeLoops3D[ ui_loop ][ ui_vert ][1],
                                                  pt_surfdata->vvclEdgeLoops3D[ ui_loop ][ ui_vert ][2] ) );
                }
            }
        } // b_show_trimming
    }
    endEditCP( pcl_points, GeoPositions3f::GeoPropDataFieldMask );
//    std::cerr<<"points"<<std::endl;
    
    if( norms.size( ) > 0 )
    {
        beginEditCP( pcl_norms, GeoNormals3f::GeoPropDataFieldMask );
        {
            pcl_norms->clear();
            for( ui_vert = 0; ui_vert < cui_verts; ++ui_vert )
            {
                if( vi_new_idx[ ui_vert ] >= 0 )
                {
                    pcl_norms->push_back( norms[ ui_vert ] );
                }
            }
            if( b_show_trimming )
            {
                for( ui_loop = 0; ui_loop < cui_loop_cnt; ++ui_loop )
                {
                    ui_vertex_cnt = pt_surfdata->vvclEdgeLoops[ ui_loop ].size( );
                    for( ui_vert = 0; ui_vert < ui_vertex_cnt; ++ui_vert )
                    {
                        pcl_norms->push_back( Vec3f( pt_surfdata->vvclEdgeLoopsNorm[ ui_loop ][ ui_vert ][0],
                                                     pt_surfdata->vvclEdgeLoopsNorm[ ui_loop ][ ui_vert ][1],
                                                     pt_surfdata->vvclEdgeLoopsNorm[ ui_loop ][ ui_vert ][2] ) );
                        pcl_norms->push_back( Vec3f( pt_surfdata->vvclEdgeLoopsNorm[ ui_loop ][ ui_vert ][0],
                                                     pt_surfdata->vvclEdgeLoopsNorm[ ui_loop ][ ui_vert ][1],
                                                     pt_surfdata->vvclEdgeLoopsNorm[ ui_loop ][ ui_vert ][2] ) );
                    }
                }
            } // b_show_trimming
        }
        endEditCP( pcl_norms, GeoNormals3f::GeoPropDataFieldMask );
//      std::cerr<<"norms"<<std::endl;
    }
    
    if( texcoords.size( ) > 0 )
    {
        beginEditCP( pcl_texcoords, GeoTexCoords2f::GeoPropDataFieldMask );
        {
            pcl_texcoords->clear();
            for( ui_vert = 0; ui_vert < cui_verts; ++ui_vert )
            {
                if( vi_new_idx[ ui_vert ] >= 0 )
                {
                    pcl_texcoords->push_back( Vec2f( texcoords[ ui_vert ][ 0 ], 
                                                     texcoords[ ui_vert ][ 1 ] ) );
//                    std::cerr<<"texcoords: " << texcoords[ ui_vert ][ 0 ] << 
//                               " " << texcoords[ ui_vert ][ 1 ] << std::endl;
                }
            }
            if ( b_show_trimming )
            {
                for( ui_loop = 0; ui_loop < cui_loop_cnt; ++ui_loop )
                {
                    ui_vertex_cnt = pt_surfdata->vvclEdgeLoops[ ui_loop ].size( );
                    for( ui_vert = 0; ui_vert < ui_vertex_cnt; ++ui_vert )
                    {
                        pcl_texcoords->push_back( Vec2f( pt_surfdata->vvclEdgeLoopsTex[ ui_loop ][ ui_vert ][0],
                                                         pt_surfdata->vvclEdgeLoopsTex[ ui_loop ][ ui_vert ][1] ) );
                        pcl_texcoords->push_back( Vec2f( pt_surfdata->vvclEdgeLoopsTex[ ui_loop ][ ui_vert ][0],
                                                         pt_surfdata->vvclEdgeLoopsTex[ ui_loop ][ ui_vert ][1] ) );
                    }
                }
            } // b_show_trimming
        }
        endEditCP( pcl_texcoords, GeoTexCoords2f::GeoPropDataFieldMask );
    }

    if( b_show_trimming )
    {
        beginEditCP( pcl_tangents, GeoTexCoords3f::GeoPropDataFieldMask );
        {
            pcl_tangents->clear();
            for( ui_vert = 0; ui_vert < cui_verts; ++ui_vert )
            {
                if( vi_new_idx[ ui_vert ] >= 0 )
                {
                    pcl_tangents->getFieldPtr( )->push_back( Vec3f( 0.0, 0.0, 0.0 ) );
                }
            }
            for( ui_loop = 0; ui_loop < cui_loop_cnt; ++ui_loop )
            {
                ui_vertex_cnt = pt_surfdata->vvclEdgeLoops[ ui_loop ].size( );
                for( ui_vert = 0; ui_vert < ui_vertex_cnt; ++ui_vert )
                {
                    if( ui_vert == 0 ) 
                    {
                        pcl_prevv = &pt_surfdata->vvclEdgeLoops3D[ ui_loop ][ ui_vertex_cnt - 1 ];
                        pcl_nextv = &pt_surfdata->vvclEdgeLoops3D[ ui_loop ][ 1 ];
                    }
                    else if ( ui_vert == ui_vertex_cnt - 1 )
                    {
                        pcl_prevv = &pt_surfdata->vvclEdgeLoops3D[ ui_loop ][ ui_vert - 1 ];
                        pcl_nextv = &pt_surfdata->vvclEdgeLoops3D[ ui_loop ][ 0 ];
                    }
                    else
                    {
                        pcl_prevv = &pt_surfdata->vvclEdgeLoops3D[ ui_loop ][ ui_vert - 1 ];
                        pcl_nextv = &pt_surfdata->vvclEdgeLoops3D[ ui_loop ][ ui_vert + 1 ];
                    }
                    pcl_actv = &pt_surfdata->vvclEdgeLoops3D[ ui_loop ][ ui_vert ];
                    // calculate the tangents of the trimming polyloops:
                    // (nextv - actv).normalize() plus
                    // (actv - prevv).normalize()  -> and normalize it again
                    cl_v1[0] = (*pcl_nextv)[0] - (*pcl_actv)[0];
                    cl_v1[1] = (*pcl_nextv)[1] - (*pcl_actv)[1];
                    cl_v1[2] = (*pcl_nextv)[2] - (*pcl_actv)[2];
                    cl_v1.normalize();
                    cl_v2[0] = (*pcl_actv)[0] - (*pcl_prevv)[0];
                    cl_v2[1] = (*pcl_actv)[1] - (*pcl_prevv)[1];
                    cl_v2[2] = (*pcl_actv)[2] - (*pcl_prevv)[2];
                    cl_v2.normalize();
                    cl_tangent = cl_v1 + cl_v2;
                    cl_tangent.normalize( );

                    cl_tangent *= sqrt( getError( ) );

                    pcl_tangents->getFieldPtr( )->push_back( -cl_tangent );
                    pcl_tangents->getFieldPtr( )->push_back( cl_tangent );
                }
            }
        }
        endEditCP( pcl_tangents, GeoTexCoords3f::GeoPropDataFieldMask );
//      std::cerr<<"tangents"<<std::endl;
    } // b_show_trimming
    
    beginEditCP( pcl_indices, GeoIndicesUI32::GeoPropDataFieldMask );
    {
        pcl_indices->clear();
        for( ui_face = 0; ui_face < cui_faces; ++ui_face )
        {
            pcl_face = &triangles[ ui_face ];
            if( ( norms.size( ) == 0 ) ||
                ( checkOrient( pcl_face->vertices[ 0 ], 
                               pcl_face->vertices[ 1 ],
                               pcl_face->vertices[ 2 ], gverts, norms ) ) )
            {
                pcl_indices->push_back( vi_new_idx[ pcl_face->vertices[ 0 ] ] );
                pcl_indices->push_back( vi_new_idx[ pcl_face->vertices[ 1 ] ] );
                pcl_indices->push_back( vi_new_idx[ pcl_face->vertices[ 2 ] ] );
            }
            else
            {
                pcl_indices->push_back( vi_new_idx[ pcl_face->vertices[ 0 ] ] );
                pcl_indices->push_back( vi_new_idx[ pcl_face->vertices[ 2 ] ] );
                pcl_indices->push_back( vi_new_idx[ pcl_face->vertices[ 1 ] ] );
            }
        }
        ui_idx = ui_used;
        if( b_show_trimming )
        {
            for( ui_loop = 0; ui_loop < cui_loop_cnt; ++ui_loop )
            {
                ui_vertex_cnt = pt_surfdata->vvclEdgeLoops[ ui_loop ].size( );
                for( ui_vert = 0; ui_vert < ui_vertex_cnt; ++ui_vert )
                {
                    pcl_indices->push_back( ui_idx++ );
                    pcl_indices->push_back( ui_idx++ );
                }
                pcl_indices->push_back( ui_idx - 2 * ui_vertex_cnt );
                pcl_indices->push_back( ui_idx - 2 * ui_vertex_cnt + 1 );
            }
//          std::cerr << ui_idx + 2 * cui_loop_cnt << " indices used" << std::endl;
        } // b_show_trimming
    }
    endEditCP( pcl_indices, GeoIndicesUI32::GeoPropDataFieldMask );
//    std::cerr<<"indices"<<std::endl;

    if( b_show_trimming )
    {
        if( norms.size( ) > 0 )
        {
            if( texcoords.size( ) > 0 ) // fatborders, normals and standard textures
            {
                beginEditCP( thisPtr, Geometry::TypesFieldMask |
                                      Geometry::LengthsFieldMask |
                                      Geometry::IndicesFieldMask |
                                      Geometry::PositionsFieldMask |
                                      Geometry::NormalsFieldMask |
                                      Geometry::TexCoordsFieldMask |
                                      Geometry::IndexMappingFieldMask |
                                      Geometry::TexCoords1FieldMask );
                {
                    setTypes( pcl_type );
                    setLengths( pcl_size );
                    setIndices( pcl_indices );

                    setPositions( pcl_points );
                    setNormals( pcl_norms );
                    setTexCoords( pcl_tangents );
                    setTexCoords1( pcl_texcoords );

                    calcIndexMapping();
                    //                   std::cerr<<"setting stuph3 "<<std::endl;
                }
                endEditCP( thisPtr, Geometry::TypesFieldMask |
                                    Geometry::LengthsFieldMask |
                                    Geometry::IndicesFieldMask |
                                    Geometry::PositionsFieldMask |
                                    Geometry::NormalsFieldMask |
                                    Geometry::TexCoordsFieldMask |
                                    Geometry::IndexMappingFieldMask |
                                    Geometry::TexCoords1FieldMask );
            }
            else // fatborders, normals but no standard textures (most used case)
            {
                beginEditCP( thisPtr, Geometry::TypesFieldMask |
                                      Geometry::LengthsFieldMask |
                                      Geometry::IndicesFieldMask |
                                      Geometry::PositionsFieldMask |
                                      Geometry::NormalsFieldMask |
                                      Geometry::IndexMappingFieldMask |
                                      Geometry::TexCoordsFieldMask |
                                      Geometry::TexCoords1FieldMask );
                {
                   setTypes( pcl_type );
                   setLengths( pcl_size );
                   setIndices( pcl_indices );

                   setPositions( pcl_points );
                   setNormals( pcl_norms );
                   setTexCoords( pcl_tangents );

                    calcIndexMapping();
//                   std::cerr<<"setting stuph!"<<std::endl;
                }
                endEditCP( thisPtr, Geometry::TypesFieldMask |
                                    Geometry::LengthsFieldMask |
                                    Geometry::IndicesFieldMask |
                                    Geometry::PositionsFieldMask |
                                    Geometry::NormalsFieldMask |
                                    Geometry::IndexMappingFieldMask |
                                    Geometry::TexCoordsFieldMask |
                                    Geometry::TexCoords1FieldMask );
            }
        }
        else
        {
            if( texcoords.size( ) > 0 ) //fatborders and normalmaps and no textures
            {
                beginEditCP( thisPtr, Geometry::TypesFieldMask |
                                      Geometry::LengthsFieldMask |
                                      Geometry::IndicesFieldMask |
                                      Geometry::PositionsFieldMask |
                                      Geometry::TexCoordsFieldMask |
                                      Geometry::IndexMappingFieldMask |
                                      Geometry::TexCoords1FieldMask );
                {
                   setTypes( pcl_type );
                   setLengths( pcl_size );
                   setIndices( pcl_indices );

                   setPositions( pcl_points );
                   setTexCoords( pcl_tangents );
                   setTexCoords1( pcl_texcoords );

                    calcIndexMapping();

                }
                endEditCP( thisPtr, Geometry::TypesFieldMask |
                                    Geometry::LengthsFieldMask |
                                    Geometry::IndicesFieldMask |
                                    Geometry::PositionsFieldMask |
                                    Geometry::TexCoordsFieldMask |
                                    Geometry::IndexMappingFieldMask |
                                    Geometry::TexCoords1FieldMask );
            }
            else // fatborders, no normals, no textures -- makes no sense??? NPR?
                 // essentially flat-shading
            {
                beginEditCP( thisPtr, Geometry::TypesFieldMask |
                                      Geometry::LengthsFieldMask |
                                      Geometry::IndicesFieldMask |
                                      Geometry::PositionsFieldMask |
                                      Geometry::IndexMappingFieldMask |
                                      Geometry::TexCoordsFieldMask |
                                      Geometry::TexCoords1FieldMask );
                {
                   setTypes( pcl_type );
                   setLengths( pcl_size );
                   setIndices( pcl_indices );

                   setPositions( pcl_points );
                   setTexCoords( pcl_tangents );

                    calcIndexMapping();

//                   std::cerr<<"setting stuph2"<<std::endl;
                }
                endEditCP( thisPtr, Geometry::TypesFieldMask |
                                    Geometry::LengthsFieldMask |
                                    Geometry::IndicesFieldMask |
                                    Geometry::PositionsFieldMask |
                                    Geometry::IndexMappingFieldMask |
                                    Geometry::TexCoordsFieldMask |
                                    Geometry::TexCoords1FieldMask );
            }
        }
    }
    else
    {
        if( norms.size( ) > 0 )
        {
            if( texcoords.size( ) > 0 )  // no fatborders, normals and standard textures
            {
                beginEditCP( thisPtr, Geometry::TypesFieldMask |
                                      Geometry::LengthsFieldMask |
                                      Geometry::IndicesFieldMask |
                                      Geometry::PositionsFieldMask |
                                      Geometry::NormalsFieldMask |
                                      Geometry::TexCoordsFieldMask |
                                      Geometry::IndexMappingFieldMask );
                {
                   setTypes( pcl_type );
                   setLengths( pcl_size );
                   setIndices( pcl_indices );

                   setPositions( pcl_points );
                   setNormals( pcl_norms );
                   setTexCoords( pcl_texcoords );

                    calcIndexMapping();

//                   std::cerr<<"setting stuph4"<<std::endl;
                }
                endEditCP( thisPtr, Geometry::TypesFieldMask |
                                    Geometry::LengthsFieldMask |
                                    Geometry::IndicesFieldMask |
                                    Geometry::PositionsFieldMask |
                                    Geometry::NormalsFieldMask |
                                    Geometry::TexCoordsFieldMask |
                                    Geometry::IndexMappingFieldMask );
            }
            else // no fatborders, normals but no standard textures
            {
                beginEditCP( thisPtr, Geometry::TypesFieldMask |
                                      Geometry::LengthsFieldMask |
                                      Geometry::IndicesFieldMask |
                                      Geometry::PositionsFieldMask |
                                      Geometry::NormalsFieldMask |
                                      Geometry::IndexMappingFieldMask );
                {
                   setTypes( pcl_type );
                   setLengths( pcl_size );
                   setIndices( pcl_indices );

                   setPositions( pcl_points );
                   setNormals( pcl_norms );

                    calcIndexMapping();
                }
                endEditCP( thisPtr, Geometry::TypesFieldMask |
                                    Geometry::LengthsFieldMask |
                                    Geometry::IndicesFieldMask |
                                    Geometry::PositionsFieldMask |
                                    Geometry::NormalsFieldMask |
                                    Geometry::IndexMappingFieldMask );
            }
        }
        else
        {
            if( texcoords.size( ) > 0 ) // no fatborders, normalmaps
            {
                beginEditCP( thisPtr, Geometry::TypesFieldMask |
                                      Geometry::LengthsFieldMask |
                                      Geometry::IndicesFieldMask |
                                      Geometry::PositionsFieldMask |
                                      Geometry::TexCoordsFieldMask |
                                      Geometry::IndexMappingFieldMask );
                {
                   setTypes( pcl_type );
                   setLengths( pcl_size );
                   setIndices( pcl_indices );

                   setPositions( pcl_points );
                   setTexCoords( pcl_texcoords );

                    calcIndexMapping();
                }
                endEditCP( thisPtr, Geometry::TypesFieldMask |
                                    Geometry::LengthsFieldMask |
                                    Geometry::IndicesFieldMask |
                                    Geometry::PositionsFieldMask |
                                    Geometry::TexCoordsFieldMask |
                                    Geometry::IndexMappingFieldMask  );
            }
            else // no fatborders, no normals, no textures
            {
                beginEditCP( thisPtr, Geometry::TypesFieldMask |
                                      Geometry::LengthsFieldMask |
                                      Geometry::IndicesFieldMask |
                                      Geometry::PositionsFieldMask |
                                      Geometry::IndexMappingFieldMask  );
                {
                   setTypes( pcl_type );
                   setLengths( pcl_size );
                   setIndices( pcl_indices );

                   setPositions( pcl_points );

                   calcIndexMapping();
                }
                endEditCP( thisPtr, Geometry::TypesFieldMask |
                                    Geometry::LengthsFieldMask |
                                    Geometry::IndicesFieldMask |
                                    Geometry::PositionsFieldMask |
                                    Geometry::IndexMappingFieldMask  );
            }
        }
    }

//        std::cerr<<"Surface::buildSurface:   texcoords ptr: " << getTexCoords() << std::endl;
//        std::cerr<<"Surface::buildSurface:   texcoords1 ptr: " << getTexCoords1() << std::endl;
        

    // build new display list if used
//  invalidateDlistCache( );

    return 0;
}


//internal
bool Surface::checkOrient( UInt32 ui_v1, UInt32 ui_v2, UInt32 ui_v3, 
                           std::vector< Pnt3f > &m_vclGlobalVertices,
                           std::vector< Vec3f > &m_vclNormal )
{
    const Vec3f ccl_norm_p = m_vclNormal[ ui_v1 ] + m_vclNormal[ ui_v2 ] + m_vclNormal[ ui_v3 ];
    const Vec3f ccl_vec1 = m_vclGlobalVertices[ ui_v2 ] - m_vclGlobalVertices[ ui_v1 ];
    const Vec3f ccl_vec2 = m_vclGlobalVertices[ ui_v3 ] - m_vclGlobalVertices[ ui_v1 ];
    const Vec3f ccl_norm_t = ccl_vec1.cross( ccl_vec2 );

    // FIXME: is 0.0 really better than -DCTP_EPS ?
    return( ccl_norm_p.dot( ccl_norm_t ) > 0.0 );
}


//! Add a (polynomial) trimming curve to the surface.
/*!
 *
 *  This function allows you to add a new trimming curve to
 *  the Surface.
 *
 *  \param dim the dimension of the curve
 *  \param knots the knotvector of the curve
 *  \param controlpoints the (rational) control points for the curve
 *  \param newloop false: this curve continues the current curveloop <BR>
 *                 true: starts a new loop
 *
 *  If it's the first curve added to the surface, it always starts
 *  a new loop, regardless of the value of \param newloop.
 *
 *  You are expected to call this function between corresponding
 *  beginEditCP()/endEditCP() pairs with the mask CurveFieldMask.
 *  You are responsible that when calling endEditCP() the 
 *  trimming curves are in a consistend state (they form closed
 *  loops and the like).
 *
 */     
void Surface::addCurve( UInt32 dim,
               std::vector<Real64>& knots,
               std::vector<Pnt2f>& controlpoints,
               bool newloop)
{
    UInt32 cpsize = controlpoints.size();
    std::vector<Pnt3f> ratcontrolpoints;

    ratcontrolpoints.reserve( cpsize );
    for (UInt32 i = 0; i < cpsize; ++i )
    {
        ratcontrolpoints.push_back( Pnt3f(controlpoints[i][0], 
                                          controlpoints[i][1],
                                          1.0f) );
    }    
    addCurve(dim, knots, ratcontrolpoints, newloop);
}

//! Add a (rational) trimming curve to the surface.
/*!
 *
 *  This function allows you to add a new trimming curve to
 *  the Surface.
 *
 *  \param dim the dimension of the curve
 *  \param knots the knotvector of the curve
 *  \param controlpoints the (nonrational) control points for the curve
 *  \param newloop false: this curve continues the current curveloop <BR>
 *                 true: starts a new loop
 *
 *  If it's the first curve added to the surface, it always starts
 *  a new loop, regardless of the value of \param newloop.
 *
 *  You are expected to call this function between corresponding
 *  beginEditCP()/endEditCP() pairs with the mask CurveFieldMask.
 *  You are responsible that when calling endEditCP() the 
 *  trimming curves are in a consistend state (they form closed
 *  loops and the like).
 *
 */
void Surface::addCurve( UInt32 dim,
               std::vector<Real64>& knots,
               std::vector<Pnt3f>& controlpoints,
               bool newloop)
{
    UInt32 cpsize = controlpoints.size();
    UInt32 knotsize = knots.size();
  
    if ( dim + cpsize + 1 != knotsize ) 
    {
//        SWARNING <<"Surface::addCurve: inconsistent curve attributes..." << endLog;
        return;
    }
//    SLOG <<"addCurve NI " << std::endl;    

    if ( _sfNumCurves.getValue() == 0 )
    {
        //this is the first curve -> it starts a new loop
//        SLOG <<"addcurve first curve"<<endLog;
        newloop = true;
    }
    _mfDimensions.push_back( dim );
    if ( newloop ) 
    {
        _mfCurvesPerLoop.push_back( 1 ); //1 curve in a new loop
//        SLOG <<"addcurve newloop"<<endLog;
    }
    else
    {
//        SLOG <<"addcurve NOT newloop"<<endLog;
        UInt32 cplsize = _mfCurvesPerLoop.size();
//        _mfCurvesPerLoop.setValue( _mfCurvesPerLoop.getValue( cplsize - 1 ) + 1, 
//                                   cplsize - 1 );
        _mfCurvesPerLoop[ cplsize - 1 ] = _mfCurvesPerLoop[ cplsize - 1 ] + 1;
    }
    _mfKnotLengths.push_back( knotsize );
    UInt32 i;
    for ( i = 0; i < knotsize; ++i )
    {
        _mfKnots.push_back( (Real32) knots[ i ] );
    }
    for ( i = 0; i < cpsize; ++i )
    {
        _mfCurveControlPoints.push_back( controlpoints[ i ] );
    }  
    _sfNumCurves.setValue( _sfNumCurves.getValue() + 1 );
}

    //! Remove all trimming curves from the surface.
    /*!
     * 
     *  This function removes all trimming curves from the surface.
     *
     *  You are expected to call this function between corresponding
     *  beginEditCP()/endEditCP() pairs with the mask CurveFieldMask.
     *
     */
void Surface::removeCurves( void )
{
    if ( _sfNumCurves.getValue() == 0 ) //we have no curves
    {
        return;
    }

    _sfNumCurves.setValue(0);
    _mfKnotLengths.clear();
    _mfDimensions.clear();
    _mfCurveControlPoints.clear();
    _mfKnots.clear();
    _mfCurvesPerLoop.clear();
}


//! Clone the Surface.
SurfacePtr Surface::clone( void )
{
    SurfacePtr surf = Surface::create();
    
    SWARNING << "Surface::clone not completely implemented!"<<endLog;
    //  create copies of the attributes
    beginEditCP(surf);
    {
        if (getMFKnotsU() != NULL)
        {
            surf->getMFKnotsU()->setValues(*getMFKnotsU());
        }
        if (getMFKnotsV() != NULL)
        {
            surf->getMFKnotsV()->setValues(*getMFKnotsV());
        }
        if (getMFKnotLengths() != NULL)
        {
            surf->getMFKnotLengths()->setValues(*getMFKnotLengths());
        }
        if (getMFDimensions() != NULL)
        {
            surf->getMFDimensions()->setValues(*getMFDimensions());
        }
        if (getMFCurveControlPoints() != NULL)
        {
            surf->getMFCurveControlPoints()->setValues(*getMFCurveControlPoints());
        }
        if (getMFKnots() != NULL)
        {
            surf->getMFKnots()->setValues(*getMFKnots());
        }
        if (getMFCurvesPerLoop() != NULL)
        {
            surf->getMFCurvesPerLoop()->setValues(*getMFCurvesPerLoop());
        }
        surf->setMaterial  (getMaterial  ());
        surf->setDimU(getDimU());
        surf->setDimV(getDimV());
        surf->setNumCurves(getNumCurves());
        surf->setError(getError());
        surf->setIsDelaunay(getIsDelaunay());
        surf->setControlPoints(getControlPoints());
        surf->setTextureControlPoints(getTextureControlPoints());
    }
    endEditCP  (surf);

    return surf;
}


//! Read from a .tso file. Temporary function
/*!
 *  Read surface (and trimming) information from
 *  a file in .tso format. This is mainly used
 *  for debugging the code (with complicated models), 
 *  it's not meant to be a general user-loader function!
 *
 *  This function may or may not be removed/changed/etc. later, 
 *  you have been warned...
 *
 *  Does not perform too many checks on the input data...
 *
 *  You are expected to call this function between corresponding
 *  beginEditCP()/endEditCP() pairs with the mask
 *  CurveFieldMask|SurfaceFieldMask.
 *
 *  \param infile istream to read surface data from.
 */
//#pragma optimize("",off)
void Surface::readfromtso( std::istream &infile, bool useTextures )
{
    Int32 err = 0;
    BSplineTrimmedSurface *cl_trimmed_surface = new BSplineTrimmedSurface;
    BSplineTensorSurface  tensor_surface;
    trimmingloop          trimloop;

    // this is actually rather inefficient: first we convert the data to the
    // OpenSG representation, and then we convert back
    // to the BSplineTrimmedSurface representation later
    // during the tessellation...
    // but it's somewhat simpler to extract the info from            
    // the BSplineTrimmedSurface class than to read from the file
    // I might rewrite it later, though...
         
    err = cl_trimmed_surface->read( infile );
    if ( err )
    {
        SLOG << "Couldn't read surface, exiting... " << err << endLog;        
        delete cl_trimmed_surface;
        return;
    }
    
    tensor_surface = cl_trimmed_surface->getSurface();
    trimloop = cl_trimmed_surface->getTrimmingLoops();
    
    // OK, first do surface business
    DCTPVec4dmatrix v4cps =  tensor_surface.getControlPointMatrix();

    UInt32 cpusize = v4cps.size();
    UInt32 cpvsize = v4cps[0].size();
    UInt32 k,u,v;
    Vec4d  vec4;

    GeoPositions4fPtr pPos;

    if(_sfControlPoints.getValue() == NullFC)
    {
        pPos = GeoPositions4f::create();

        SurfacePtr tmpPtr(*this);
            
        beginEditCP(tmpPtr, ControlPointsFieldMask);
            setControlPoints(pPos);
        endEditCP  (tmpPtr, ControlPointsFieldMask);
    }
    else
    {
        pPos = GeoPositions4fPtr::dcast(_sfControlPoints.getValue());
    }

    beginEditCP(pPos, GeoPositions4f::GeoPropDataFieldMask);

    MFPnt4f &_mfControlPoints = pPos->getField();
//    MFPnt3f &_mfControlPoints = pPos->getField();
      
//    _mfControlPoints.resize( cpusize * cpvsize );
    _mfControlPoints.clear( );
    for ( u = 0; u < cpusize; ++u )
    {
        for ( v = 0; v < cpvsize; ++v )
        {
//            k = u * cpvsize + v;
            vec4 = v4cps[ u ][ v ];
            _mfControlPoints.push_back(Pnt4f(vec4[0], vec4[1], vec4[2], vec4[3]));
//            _mfControlPoints.push_back(Pnt3f(vec4[0], vec4[1], vec4[2]));
        }
    }

    endEditCP(pPos, GeoPositions4f::GeoPropDataFieldMask);

    _sfDimU.setValue( tensor_surface.getDimension_U() );
    _sfDimV.setValue( tensor_surface.getDimension_V() );

    DCTPdvector knots;
    
    knots = tensor_surface.getKnotVector_U();
    _mfKnotsU.clear();
    for ( u = 0; u < knots.size(); ++u )
    {
        _mfKnotsU.push_back( (Real32) knots[ u ] );
    }
    knots = tensor_surface.getKnotVector_V();
    _mfKnotsV.clear();
    for ( v = 0; v < knots.size(); ++v )
    {
        _mfKnotsV.push_back( (Real32) knots[ v ] );
    }

    // now deal with the trimming curves
    removeCurves();    
    
    bool isnewloop;
    UInt32 actdim;
    std::vector<Real64> actknots;
    std::vector<Pnt3f> actcontrolpoints;
    DCTPVec3dvector v3actcps;
    for ( UInt32 i = 0; i < trimloop.size(); ++i )
    {
        isnewloop = true;
        for ( UInt32 j = 0; j < trimloop[i].size(); ++j )
        {
            actknots = trimloop[i][j].getKnotVector();
            actdim = trimloop[i][j].getDimension();
            v3actcps = trimloop[i][j].getControlPointVector();
            actcontrolpoints.clear();
            for ( UInt32 kk = 0; kk < v3actcps.size(); ++kk )
            {
                actcontrolpoints.push_back(Pnt3f(v3actcps[ kk ][0], 
                                                 v3actcps[ kk ][1],
                                                 v3actcps[ kk ][2]));
            }
            addCurve( actdim, actknots, actcontrolpoints, isnewloop );                   
            isnewloop = false;
        }
    }    
    
    // trimming curves...
    delete cl_trimmed_surface;
    
    if ( useTextures )
    {
//        std::cerr<<"read in texture coordinates..."<<std::endl;
        char buffer[1024];
        infile >> buffer >> std::ws;
//        std::cerr <<"buffer: " << buffer <<std::endl;
        UInt32 numoftexcps = cpusize * cpvsize;
//        _mfTextureControlPoints.clear();

        GeoTexCoords2fPtr pTexPos;

        if(_sfTextureControlPoints.getValue() == NullFC)
        {
            pTexPos = GeoTexCoords2f::create();

            SurfacePtr tmpPtr(*this);
            
            beginEditCP(tmpPtr, TextureControlPointsFieldMask);
                setTextureControlPoints(pTexPos);
            endEditCP  (tmpPtr, TextureControlPointsFieldMask);
        }
        else
        {
            pTexPos = GeoTexCoords2fPtr::dcast(_sfTextureControlPoints.getValue());
        }

        beginEditCP(pTexPos, GeoTexCoords2f::GeoPropDataFieldMask);

        MFVec2f &_mfTextureControlPoints = pTexPos->getField();
        _mfTextureControlPoints.clear();

        Vec2f temp;
        for ( UInt32 ti = 0; ti < numoftexcps; ++ti )
        {
            infile >> std::ws >> temp[0] >> std::ws >> temp[1] >> std::ws;
            _mfTextureControlPoints.push_back( temp );
        }
        endEditCP(pTexPos, GeoTexCoords2f::GeoPropDataFieldMask);
//        std::cerr<<"read " << _mfTextureControlPoints.size() << " cps."<<std::endl;
    }
}
//#pragma optimize("",on)


void Surface::writetotso( std::ostream &outfile )
{
    _trimmedSurface->write( outfile );
}


//! Write tessellated geometry to an .obj file. Absolutely temporary function
/*!
 *
 *  \param outfile istream to read surface data from.
 */
UInt32 Surface::writetoobj( std::ostream &outfile, UInt32 offset )
{
    unsigned int uicnt;
//     std::cerr << "current offset:" << g_current_obj_offset << std::endl;
    outfile << "g obj " << std::endl;
    GeoPositionsPtr pcl_points = getPositions();
    GeoNormalsPtr   pcl_norms = getNormals();
    GeoIndicesPtr   pcl_indices = getIndices();
    GeoTexCoordsPtr pcl_texcoords = getTexCoords();
    std::cerr << " indices size: " << pcl_indices->size() << std::endl;
    std::cerr << " points size: " << pcl_points->size() << std::endl;
    UInt32 ui_faces = pcl_indices->size() / 3;
    UInt32 uivertsize = pcl_points->size( );
    outfile << "# vertices " << uivertsize << std::endl;

    //write out vertices
    for ( uicnt = 0; uicnt < uivertsize; uicnt++) 
    {
        Pnt3f ppp = pcl_points->getValue( uicnt );
        
        outfile << "v " << ppp.x() << " " << 
                           ppp.y() << " " <<
                           ppp.z() << std::endl;
                               
    }
    //write out normals
    for ( uicnt = 0; uicnt < uivertsize; uicnt++) 
    {
        Pnt3f ppp = pcl_norms->getValue( uicnt );
            
        outfile << "vn " << ppp.x() << " " << 
                            ppp.y() << " " <<
                            ppp.z() << std::endl;
                               
    }
    //write out texture coordinates
    for ( uicnt = 0; uicnt < uivertsize; uicnt++) 
    {
        Pnt2f ppp = pcl_texcoords->getValue( uicnt );
            
        outfile << "vt " << ppp.x() << " " << 
                            ppp.y() << " " << std::endl;                          
    }
    
    outfile << "# faces " << ui_faces << std::endl;
    //write out triangles
    for ( unsigned int uitricnt = 0; uitricnt < ui_faces; uitricnt++)
    {
        UInt32 ind1 = pcl_indices->getValue( uitricnt * 3 );
        UInt32 ind2 = pcl_indices->getValue( uitricnt * 3 + 1 );
        UInt32 ind3 = pcl_indices->getValue( uitricnt * 3 + 2 );
        UInt32 i1 = ind1 + offset + 1;
        UInt32 i2 = ind2 + offset + 1;
        UInt32 i3 = ind3 + offset + 1;
            
        outfile << "f ";
        outfile << i1 << "/" << i1 << "/" << i1 << " " <<
                   i2 << "/" << i2 << "/" << i2 << " " <<
                   i3 << "/" << i3 << "/" << i3 << std::endl;
    }

    return offset + uivertsize;
}

//! output the instance for debug purposes

void Surface::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Surface NI" << endLog;
}

void Surface::onCreate(const Surface *source)
{
    // if we're in startup this is the prototype, which shouldn't have an id
    if(GlobalSystemState == Startup)
        return;

    // !!! this temporary is needed to work around compiler problems(sgi)
    // CHECK CHECK
    //  TextureChunkPtr tmpPtr = FieldContainer::getPtr<TextureChunkPtr>(*this);
    if(Thread::getAspect() != _sfIgnoreGLForAspect.getValue())
    {
        SurfacePtr tmpPtr(*this);
    
        beginEditCP(tmpPtr, Surface::SurfaceGLIdFieldMask);
    
        setSurfaceGLId(
            Window::registerGLObject(
                osgTypedMethodVoidFunctor2ObjCPtrPtr<SurfacePtr, 
                                                     Window , 
                                                     UInt32>(tmpPtr, 
                                                             &Surface::handleGL),
                1));
    
        endEditCP(tmpPtr, Surface::SurfaceGLIdFieldMask);
    }

    Inherited::onCreate(source);
}

void Surface::onDestroy(void)
{
    Inherited::onDestroy();

    SurfacePtr thisP(*this);

    if(_sfControlPoints.getValue() != NullFC)
    {
        beginEditCP(_sfControlPoints.getValue(), Attachment::ParentsFieldMask);
        {
            _sfControlPoints.getValue()->subParent(thisP);
        }
        endEditCP(_sfControlPoints.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfControlPoints.getValue());
    }

    if(_sfTextureControlPoints.getValue() != NullFC)
    {
        beginEditCP(_sfTextureControlPoints.getValue(), Attachment::ParentsFieldMask);
        {
            _sfTextureControlPoints.getValue()->subParent(thisP);
        }
        endEditCP(_sfTextureControlPoints.getValue(), Attachment::ParentsFieldMask);

        subRefCP(_sfTextureControlPoints.getValue());
    }

    if(getSurfaceGLId() > 0)
    {
        Window::destroyGLObject(getSurfaceGLId(), 1);
    }
}

void Surface::handleGL(Window*, UInt32 idstatus)
{
    Window::GLObjectStatusE mode;
    UInt32 id;

    Window::unpackIdStatus(idstatus, id, mode);

    if(mode == Window::initialize  || 
       mode == Window::needrefresh ||
       mode == Window::reinitialize )
    {       
        if((getDirtyMask() & DONTTESSELLATE) == 0x0000)
        {
            if((getDirtyMask() & TESSELLATE) != 0x0000)
            {
                tessellate( );
            }
            else if((getDirtyMask() & RETESSELLATE) != 0x0000)
            {
                reTessellate( );
            }

            SurfacePtr tmpPtr(*this);
            beginEditCP(tmpPtr, DirtyMaskFieldMask);
            {
                getDirtyMask() &= ~(TESSELLATE | RETESSELLATE);
            }
            endEditCP  (tmpPtr, DirtyMaskFieldMask);
        }
    }
}

// Calculate the volume based on bounding box of the control points.
// If any of the control points have 0 weight, also take into
// account the tessellated geometry, otherwise the volume will be 
// too small. 
// FIXME: a better solution might be to do de Casteljau steps
// FIXME: until there are no control points w/ 0 weights and
// FIXME: redo the calculation...
void Surface::adjustVolume(Volume & volume)
{
    GeoPositionsPtr pos = getControlPoints();
    bool has_zeroweights = false;
    
    volume.setValid();
    volume.setEmpty();

    GeoPositions3fPtr pPos = GeoPositions3fPtr::dcast(
        _sfControlPoints.getValue());
    GeoPositions4fPtr pRatPos = GeoPositions4fPtr::dcast(
        _sfControlPoints.getValue());

    if(pos == NullFC)
        return;                  // Node has no points, no volume

    if( pPos != NullFC )
    {
        for(UInt32 i = 0; i < pPos->size(); ++i)
        {
            volume.extendBy(pPos->getValue(i));
        }
    }
    else if( pRatPos != NullFC )
    {
        for(UInt32 i = 0; i < pRatPos->size(); ++i)
        {
            Pnt3f   pnt;

            if( osgabs( pRatPos->getFieldPtr()->getValue(i)[3] ) > DCTP_EPS )
            {
                pnt[0] = pRatPos->getFieldPtr()->getValue(i)[0] / pRatPos->getFieldPtr()->getValue(i)[3];
                pnt[1] = pRatPos->getFieldPtr()->getValue(i)[1] / pRatPos->getFieldPtr()->getValue(i)[3];
                pnt[2] = pRatPos->getFieldPtr()->getValue(i)[2] / pRatPos->getFieldPtr()->getValue(i)[3];
                volume.extendBy(pnt);
            }
            else
            {
                has_zeroweights = true;
            }
        }
    }
    if (has_zeroweights)
    {
        GeoPositionsPtr points = getPositions();
        if (points != NullFC)
        {
            for(UInt32 i = 0; i < points->size(); ++i)
            {
                volume.extendBy(points->getValue(i));
            }
        }
        // FIXME: a warning should be printed here since the calculated
        // FIXME: volume will not be exact if there was no tessellated 
        // FIXME: geometry, but in that case there's nothing to render 
        // FIXME: anyway so we skip the warning (which would be  
        // FIXME: unnecessarily (and annoyingly) printed at startup 
        // FIXME: e.g. when the SSM::showall() method is called).
        // FIXME: Better suggestions are welcome.
    }
}

void Surface::forceTessellate(void)
{
    SurfacePtr tmpPtr(*this);

    beginEditCP(tmpPtr, DirtyMaskFieldMask);
    {
        getDirtyMask() |= DONTTESSELLATE;

        if((getDirtyMask() & TESSELLATE) != 0x0000)
        {
            tessellate( );
        }
        else if((getDirtyMask() & RETESSELLATE) != 0x0000)
        {
            reTessellate( );
        }
        
        getDirtyMask() &= ~(TESSELLATE | RETESSELLATE);
    }
    endEditCP  (tmpPtr, DirtyMaskFieldMask);
}

void Surface::flip(void)
{
    if(_trimmedSurface != NULL)
        _trimmedSurface->flip();
}

Action::ResultE Surface::drawPrimitives(DrawActionBase *action)
{
    action->getWindow()->validateGLObject(getSurfaceGLId());

    return Inherited::drawPrimitives(action);
}


