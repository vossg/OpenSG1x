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

//-----------------------------------------------------------------------------
//                                 Includes                                    
//-----------------------------------------------------------------------------


#include <memory>
#include <assert.h>

#include "OSGConfig.h"
#include <OSGLog.h>

#include "OSGExtrusionGeometry.h"

// #define DEBUG_VERTEX_NORMALS
// #define DEBUG_FACE_NORMALS


OSG_USING_NAMESPACE


/*---------------------------------------------------------------------*/
/*! \name                   Construction functions                     */
/*! \{                                                                 */

/*! \fn GeometryPtr makeExtrusion(const std::vector<Pnt2f> &crossSection,
                             const std::vector<Quaternion> &orientation,
                             const std::vector<Vec2f> &scale,
                             const std::vector<Pnt3f> &spine,
                             Real32 creaseAngle,
                             bool beginCap, 
                             bool endCap,
                             bool ccw, 
                             bool convex,
                             bool buildNormal,
                             bool buildTexCoord,
                             UInt32 numOfSubdivision)
    \ingroup GrpSystemDrawablesGeometrySimpleGeometry

    Create an extrusion Geometry, see \ref PageSystemSimpleGeometryExtrusion
    for a desription.

*/

/*! \fn GeometryPtr makeExtrusionGeo(const std::vector<Pnt2f> &crossSection,
                             const std::vector<Quaternion> &orientation,
                             const std::vector<Vec2f> &scale,
                             const std::vector<Pnt3f> &spine,
                             Real32 creaseAngle,
                             bool beginCap,
                             bool endCap, 
                             bool ccw,
                             bool convex,
                             bool buildNormal,
                             bool buildTexCoord,
                             UInt32 numOfSubdivision)
    \ingroup GrpSystemDrawablesGeometrySimpleGeometry

    Create the Geometry Core for an extrusion Geometry, see \ref
    PageSystemSimpleGeometryExtrusion for a description. 

*/

/*! \}                                                                 */



//-----------------------------------------------------------------------------
//                           Forward Declarations                              
//-----------------------------------------------------------------------------
template <class VectorTypeT>
void subdivide(const typename std::vector<VectorTypeT> &dataIn,
               typename std::vector<VectorTypeT> *dataOut,
               bool closed);

template <class VectorTypeT>
void subdivide(const typename std::vector<VectorTypeT> &dataIn,
               typename std::vector<VectorTypeT> *dataOut,
               UInt32 nTimes,
               bool close);


//-----------------------------------------------------------------------------
// Constructor
//
// Author: afischle
//-----------------------------------------------------------------------------
ExtrusionSurface::ExtrusionSurface(const std::vector<Pnt2f> &crossSection,
                                   const std::vector<Quaternion> &orientation,
                                   const std::vector<Vec2f> &scale,
                                   const std::vector<Pnt3f> &spine,
                                   Real32 creaseAngle,
                                   bool beginCap,
                                   bool endCap,
                                   bool ccw,
                                   bool convex,
                                   bool buildNormal,
                                   bool buildTexCoord) :

    _creaseAngle(creaseAngle),
    _beginCap(beginCap),
    _endCap(endCap),
    _ccw(ccw),
    _convex(convex),
    _createNormals(buildNormal),
    _createTexCoords(buildTexCoord),
    _primitiveCount(0),
    _vertexCount(0),
    _totalVertexCount(0)
{
    // initialize cross section
    if(!crossSection.empty()) 
    {
        // copy argument
        _crossSection.assign(crossSection.begin(), crossSection.end());
    }
    else
    {
        // copy default
        FDEBUG(("OSGExtrusion: Empty cross section. Using default.\n"));
        for(UInt32 i = 0; i < DEF_N_CROSS_SECTION_POINTS; i++)
            _crossSection.push_back(Pnt2f(DEF_CROSS_SECTION[i]));
    }

    // initialize orientations
    if(!orientation.empty())
    {
        // copy argument
        _orientation.assign(orientation.begin(), orientation.end());
    }
    else
    {
        // copy default
        FDEBUG(("OSGExtrusion: Empty orientation. Using default.\n"));
        for(UInt32 i = 0; i < DEF_N_ORIENTATION_PARAMS; i++)
            _orientation.push_back(Quaternion(Vec3f(DEF_ORIENTATION[i]),
                                              DEF_ORIENTATION[i][3]));
    }
    
    // initialize scale parameters
    if(!scale.empty())
    {
        // copy argument
        _scale.assign(scale.begin(), scale.end());
    }
    else
    {
        // copy default
        FDEBUG(("OSGExtrusion: Empty scale parameter. Using default.\n"));
        for(UInt32 i = 0; i < DEF_N_SCALE_PARAMS; i++)
            _scale.push_back(Vec2f(DEF_SCALE[i]));
    }


    // initialize spine
    if(!spine.empty())
    {
        // copy argument
        _spine.assign(spine.begin(), spine.end());
    }
    else
    {
        // copy default
        FDEBUG(("OSGExtrusion: Empty spine. Using default.\n"));
        for(UInt32 i = 0; i < DEF_N_SPINE_POINTS; i++)
            _spine.push_back(Pnt3f(DEF_SPINE[i]));
    }
}


//-----------------------------------------------------------------------------
// Returns true if the member fields describe a valid extrusion surface and
// false otherwise.
// 
// Author: afischle
//-----------------------------------------------------------------------------
bool ExtrusionSurface::verifyInput(void)
{
    if(_crossSection.size() < 2)
    {
        FWARNING(("OSGExtrusion:checkInput: Cross section is degenerate\n"));
        return false;
    }

    if(_spine.size() < 2)
    {
        FWARNING(("OSGExtrusion:checkInput: spine is degenerate\n"));
        return false;
    }

    return true;
}


//-----------------------------------------------------------------------------
// Determines the topology of the sweep surface and sets the topology member
// variables accordingly.
//
// Author: afischle
//-----------------------------------------------------------------------------
void ExtrusionSurface::determineTopology(void)
{
    // compute vector differences between start and end points
    Vec3f sDiff = _spine.back() - _spine.front();
    Vec2f cDiff = _crossSection.back() - _crossSection.front();

    // determine whether the curves are closed
    _spineClosed = (sDiff.length() < Eps) ? true : false;
    _crossSectionClosed = (cDiff.length() < Eps) ? true : false;
    
    FDEBUG(("OSGExtrusion:checkInput: Topology: (Spine: %s / Cross-section: %s)\n", 
            (_spineClosed ? "Closed" : "Open"),
            (_crossSectionClosed ? "Closed" : "Open")));
}


//-----------------------------------------------------------------------------
// Refines the cross-section n times using a simple subdivision scheme.
// 
// Author: afischle
//-----------------------------------------------------------------------------
void ExtrusionSurface::refineCrossSection(UInt32 nTimes)
{
    FDEBUG(("OSGExtrusion:refineCrossSection: Refinining %d times\n",nTimes));
    std::vector<Vec2f> output;

    // cast <Pnt2f> to <Vec2f> because we need the vector interface
    std::vector<Vec2f> & csVec2f ((std::vector<Vec2f>&)(_crossSection));
    subdivide(csVec2f, &output, nTimes, _crossSectionClosed);

    // swap output data into _crossSection
    output.swap(csVec2f);
}

//-----------------------------------------------------------------------------
// Refines the spine n times using a simple subdivision scheme.
// 
// Author: afischle
//-----------------------------------------------------------------------------
void ExtrusionSurface::refineSpine(UInt32 nTimes)
{
    FDEBUG(("OSGExtrusion:refineSpine: Refinining %d times\n",nTimes));

    std::vector<Vec3f> output;

    // cast <Pnt3f> to <Vec3f> because we need the vector interface    
    std::vector<Vec3f> & spVec3f ((std::vector<Vec3f>&)(_spine));
    subdivide<Vec3f>(spVec3f, &output, nTimes, _spineClosed);

    // swap output data into _spine
    output.swap(spVec3f);
}


//-----------------------------------------------------------------------------
// Refines the scale parameters n times using a simple subdivision scheme.
// 
// Author: afischle
//-----------------------------------------------------------------------------
void ExtrusionSurface::refineScale(UInt32 nTimes)
{
    FDEBUG(("OSGExtrusion:refineScale: Refinining %d times\n",nTimes));

    std::vector<Vec2f> output;
    subdivide<Vec2f>(_scale, &output, nTimes, _spineClosed);

    // swap output data into _scale
    output.swap(_scale);
}


//-----------------------------------------------------------------------------
// Refines the scale parameters n times using a simple subdivision scheme.
//
// Todo: Not implemented yet
//
// Author: afischle
//-----------------------------------------------------------------------------
void ExtrusionSurface::refineOrientation(UInt32 nTimes)
{
    FFATAL(("OSGExtrusion:refineOrientation: Not Implemented\n"));
}


//-----------------------------------------------------------------------------
// Calculates the y-axes of the base transform from the cross section plane
// to the spine-aligned cross section plane (SCP). The y- and z-axes are
// expected to be already stored in the _transform vector.
//
// The computed x-axes are stored in the _transform vector.
// 
// Author: afischle
//-----------------------------------------------------------------------------
void ExtrusionSurface::calcXAxes(void)
{
    std::vector<Matrix>::iterator tIt = _transform.begin();

    // Either of the two cases below implies the cross product of
    // the y- and the z-axis vanish (and so do all x-axes)
    if(!_spineCollinear && !_revolutionSurface)
    {
        for(; tIt != _transform.end(); ++tIt)
        {
            Vec3f xAxis = calcXAxis(tIt);
            (*tIt)[0].setValue(xAxis);
        }
    }
    else
    {
        (*tIt)[0].setValue(Vec3f(0.f, 0.f, 0.f));
    }
}


//-----------------------------------------------------------------------------
// Calculates the y-axes of the base transform from the cross-section plane
// to the spine-aligned cross section plane (SCP). If no y-axis could be
// defined it sets the _revolutionSurface flag to true (and false otherwise.)
//
// The computed y-axes are stored in the _transform vector.
//
// Author: afischle
//-----------------------------------------------------------------------------
void ExtrusionSurface::calcYAxes(void)
{
    bool yAxisDefined = false;

    std::vector<Pnt3f>::const_iterator  spineIt = _spine.begin();
    std::vector<Matrix>::iterator tIt = _transform.begin();
    for(; spineIt != _spine.end(); ++spineIt, ++tIt)
    {
        Vec3f yAxis = calcNonUnitYAxis(spineIt);
        if(yAxis.length() > Eps) // we have found a valid tangent
        {
            yAxis.normalize();
            if(!yAxisDefined)
            {
                FDEBUG(("OSGExtrusion:calcYAxes: yAxis is defined\n"));
                yAxisDefined = true;

                // assign found y-axis to all transforms
                // up to and including the current one
                std::vector<Matrix>::iterator yIt;
                for(yIt = _transform.begin(); yIt != (tIt + 1); ++yIt)
                    (*yIt)[1].setValue(yAxis);
            }
            else 
            {
                // assign found y-axis to the current transform only
                (*tIt)[1].setValue(yAxis);
            }
        }
        else if(yAxisDefined)
        {
            // reuse y-axis determined during last step
            (*tIt)[1] = (*(tIt - 1))[1];
        }
    }

    // all spine points coincided => surface of revolution
    _revolutionSurface = !yAxisDefined;
}

//-----------------------------------------------------------------------------
// Calculates the z-axes of the base transform from the cross-section plane (CP)
// to the spine-aligned cross section plane (SCP). If no z-axis could be
// defined it sets the _spineCollinear flag to true (and false otherwise.)
//
// The computed z-axes are stored in the _transform vector.
//
// Author: afischle
//-----------------------------------------------------------------------------
void ExtrusionSurface::calcZAxes(void)
{
    bool zAxisDefined = false;
    
    std::vector<Pnt3f>::const_iterator  spineIt = _spine.begin();
    std::vector<Matrix>::iterator tIt = _transform.begin();
    for(; spineIt != _spine.end(); ++spineIt, ++tIt)
    {
        Vec3f zAxis = calcNonUnitZAxis(spineIt);
        if(zAxis.length() > Eps)
        {
            zAxis.normalize();
            if(!zAxisDefined)
            {
                FDEBUG(("OSGExtrusion:calcZAxes: zAxis is defined\n"));
                zAxisDefined = true;
                
                // set the current z-Axis for the current transform
                (*tIt)[2].setValue(zAxis);

                // assign found z-axis to all previous transforms
                std::vector<Matrix>::iterator zIt;
                for(zIt = _transform.begin(); zIt != tIt; ++zIt)
                {
                    (*zIt)[2].setValue(zAxis);
                }
            }
            else // assign found z-axis to this basis _only_
            {
                (*tIt)[2].setValue(zAxis);

                // as the zAxis is defined tIt - 1 contains a valid value 
                Vec3f prevZAxis((*(tIt - 1))[2][0],
                                (*(tIt - 1))[2][1],
                                (*(tIt - 1))[2][2]);

                // check whether the z-axis needs to be flipped
                if(prevZAxis.dot(zAxis) + Eps < 0.f)
                {
                    FDEBUG(("OSGExtrusion:calcZAxes: Flipping z-axis\n"));
                    zAxis.negate();
                }

                // assign zAxis to current transform
                (*tIt)[2].setValue(zAxis);
            }
        }
        else if(zAxisDefined)
        {
            // reuse previous value
            (*tIt)[2] = (*(tIt - 1))[2];
        }
    } // end for

    // All cross products vanished => spine has no non-collinear part
    // and is thus composed of collinear parts and revolutions only
    _spineCollinear = !zAxisDefined;
}

//-----------------------------------------------------------------------------
// Calculates the affine basis transformations from the cross-section plane
// (i.e. the xz-plane) to the spine-aligne cross-section plane (SCP) and
// determines whether:
//
// 1. the surface has a collinear spine,
// 2. the surface is a pure surface of revolution
// 3. the surface is not of one of the above special types.
//
// Author: afischle
//-----------------------------------------------------------------------------
void ExtrusionSurface::calcTransforms(void)
{
    _transform.clear();

    // initialize the transformations with Id
    _transform.resize(_spine.size());

    /* X3D Spec:
     * The SCP is computed by first computing its Y-axis and Z-axis, then 
     * taking the cross product of these to determine the X-axis. These three 
     * axes are then used to determine the rotation value needed to rotate the
     * Y=0 plane to the SCP. This results in a plane that is the approximate 
     * tangent of the spine at each point, as shown in Figure 13.5.
     */
    calcZAxes(); // sets bool _spineCollinear
    calcYAxes(); // sets bool _revolutionSurface

    // We need to make a difference between surfaces having at least
    // one non-trivial collinear part in their spine and surfaces created
    // by pure revolution of the crossection.
    if(_revolutionSurface)
    {
        _spineCollinear = false;
    }
    calcXAxes(); // uses _spineCollinear and _revolutionSurface

    /* X3D Spec:
     *
     * If the entire spine is collinear, the SCP is computed by finding the 
     * rotation of a vector along the positive Y-axis (v1) to the vector formed
     * by the spine points (v2). The Y=0 plane is then rotated by this value.
     *
     * If two points are coincident, they both have the same SCP. If each point
     * has a different orientation value, then the surface is constructed by 
     * connecting edges of the cross-sections as normal. This is useful in 
     * creating revolved surfaces.
     */
    Matrix rotation; // m = Id and thus ok for revolution case
    if(_spineCollinear && !_revolutionSurface)
    {
        // calculate the rotation that rotates the y unit vector to the
        // direction of the spine.
        Vec3f v1(0.f, 1.f, 0.f);
        Vec3f v2(_transform[0][1]);
            
        Quaternion q;
        q.setValue(v1, v2);
        q.getValue(rotation);
    }

    std::vector<Matrix>::iterator tIt             = _transform.begin();
    std::vector<Pnt3f>::const_iterator spineIt    = _spine.begin();
    std::vector<Vec2f>::const_iterator scaleIt    = _scale.begin(); 
    std::vector<Quaternion>::const_iterator rotIt = _orientation.begin();

    // calculate an affine transformation for the cross-section at
    // each spine point
    for(; spineIt != _spine.end(); ++spineIt, ++tIt)
    {
        // special cases
        if(_spineCollinear || _revolutionSurface)
        {
            // defines the x,y and z-axes in this case
            *tIt = rotation;
        }        

        // setup transform of the CP
        Matrix cSPlaneTransform;

        // Scale the x- and z-axes
        cSPlaneTransform[0] *= (*scaleIt)[0];
        cSPlaneTransform[2] *= (*scaleIt)[1];

        // apply orientation
        Matrix orientationMatrix;
        rotIt->getValue(orientationMatrix);
        cSPlaneTransform.multLeft(orientationMatrix);

        tIt->mult(cSPlaneTransform);

        // affine translation to the spine point
        tIt->setTranslate(*spineIt);
        
        // The affine transformation *tIt should now
        //
        //   1. scale the CP
        //   2. apply the orientation to the CP        
        //   2. translate the origin to spine[i]
        //
        // in exactly this order.

        /* X3D Spec quotation:
         *
         * If the number of scale or orientation values is greater than the
         * number of spine points, the excess values are ignored. If they 
         * contain one value, it is applied at all spine points. The 
         * results are undefined if the number of scale or orientation 
         * values is greater than one but less than the number of spine 
         * points. The scale values shall be positive.
         */
        
        // always use last available value
        if(rotIt + 1   != _orientation.end()) { ++rotIt;   }
        if(scaleIt + 1 != _scale.end())       { ++scaleIt; }
    }

    FDEBUG(("OSGExtrusion:calcTransforms: spine collinear: %s\n", 
            (_spineCollinear ? "true" : "false")));

    FDEBUG(("OSGExtrusion:calcTransforms: revolution surface: %s\n",
            (_revolutionSurface ? "true" : "false")));
}


//-----------------------------------------------------------------------------
// Initializes the vertex grid with _spine.size() rows and _crossSection.size()
// columns.
//
// Author: afischle
//-----------------------------------------------------------------------------
void ExtrusionSurface::initGrid(void)
{
    FDEBUG(("OSGExtrusion:initGrid: Initializing vertex grid\n"));
    
    _grid.clear();
    _grid.resize(_spine.size());

    VertexGrid::iterator gridRowIt = _grid.begin();
    for(Int32 i = 0; i < _spine.size(); i++, ++gridRowIt)
    {
        gridRowIt->resize(_crossSection.size());
    }
}


//-----------------------------------------------------------------------------
// Calculates the vertex positions of the sweep surface by transforming the 
// cross-section using the _transforms member field.
//
// The calculated positions are stored in the position components of the
// vertices in the _grid.
//
// Author: afischle
//-----------------------------------------------------------------------------
void ExtrusionSurface::calcSweepSurfacePositions(void)
{
    FDEBUG(("OSGExtrusion:calcSweepSurfacePositions: Calculation vertex positions\n"));

    if(_grid.size() < _spine.size())
    {
        FFATAL(("OSGExtrusion:calcSweepSurfacePositions: Grid not initialized\n"));
        return;
    }

    _posMap.clear();

    // compute transformation matrices
    calcTransforms();

    if(_grid.size() < _spine.size()) // grid not yet or incorrectly initialized
    {
        initGrid();
    }

    std::vector<Matrix>::iterator transIt = _transform.begin();
    VertexGrid::iterator gridRowIt = _grid.begin();

    // iterate over the spine points
    for(Int32 i = 0; i < _spine.size(); i++, ++gridRowIt)
    {
        if(transIt->det3() < Eps) // degenerate transform
        {
            FWARNING(("OSGExtrusion:calcSurfacePositions: Degenerate transformation matrix\n"));
            SWARNING << "Degenerate transform[" << i << "]:\n "
                     << *transIt << std::endl;
        }

        std::vector<Vertex>::iterator gridColIt = gridRowIt->begin();
        std::vector<Pnt2f>::iterator crossIt;

        // iterate over the cross-section curve
        for(crossIt = _crossSection.begin(); crossIt != _crossSection.end();
            ++crossIt, ++gridColIt)
        {
            Pnt3f p = Pnt3f((*crossIt)[0], 0.f, (*crossIt)[1]);

            // apply "CP to SCP"-transform
            transIt->multMatrixPnt(p, gridColIt->position);
        }

        // always use last defined transformation matrix
        if(transIt + 1 != _transform.end()) { ++transIt; }
    }
}


//-----------------------------------------------------------------------------
// Calculates the texture coordinates of the sweep surface. The texture coords
// are obtained by measuring the lengths along the row- and column-curves
// of the grid and renormalizing them to the usual [0, 1]-range. The grid
// is expected to already hold the position data of the sweep surface.
//
// The calculated texture coordinates are stored in the _grid.
//
// Author: afischle
//-----------------------------------------------------------------------------
void ExtrusionSurface::calcSweepSurfaceTexCoords(void)
{
    FDEBUG(("OSGExtrusion:calcSweepSurfaceTexCoords: Calculating texture coordinates\n"));
    if(_grid.size() < _spine.size())
    {
        FFATAL(("OSGExtrusion:calcSweepSurfaceTexCoords: Grid not initialized\n"));
        return;
    }
    _texCoordMap.clear();
    
    /* X3D Spec:
     *
     *  Textures are mapped so that the coordinates range in the U direction 
     *  from 0 to 1 along the crossSection curve (with 0 corresponding to the 
     *  first point in crossSection and 1 to the last) and in the V direction
     *  from 0 to 1 along the spine curve (with 0 corresponding to the first 
     *  listed spine point and 1 to the last) 
     */

    // accumulate distances along u and v directions
    for(UInt32 i = 0; i < _spine.size(); ++i)
    {
        for(UInt32 j = 0; j < _crossSection.size(); ++j)
        {
            Real32 u,v;
            UInt32 iPrev = (i == 0) ? 0 : i - 1;
            UInt32 jPrev = (j == 0) ? 0 : j - 1;

            // contains length of i-th column curve up to the (j-1)-th point
            u = _grid[i][jPrev].texCoord[0];
            // add distance to j-th point
            u += _grid[i][j].position.dist(_grid[i][jPrev].position);

            // contains length of j-th row curve up to the (i-1)-th point
            v = _grid[iPrev][j].texCoord[1];
            // add distance to i-th point
            v += _grid[i][j].position.dist(_grid[iPrev][j].position);

            _grid[i][j].texCoord[0] = u;
            _grid[i][j].texCoord[1] = v;
        }
    }

    // renormalize distances to [0,1]x[0,1]
    for(UInt32 i = 0; i < _spine.size(); ++i)
    {
        for(UInt32 j = 0; j < _crossSection.size(); ++j)
        {
            // length is maximal in the row/column curve end points
            Real32 uMax = _grid[i][_crossSection.size() - 1].texCoord[0];
            Real32 vMax = _grid[_spine.size() - 1][j].texCoord[1];

            if(uMax > Eps)
                _grid[i][j].texCoord[0] /= uMax;

            if(vMax > Eps)
                _grid[i][j].texCoord[1] /= vMax;
        }
    }
}


void ExtrusionSurface::calcSweepSurfaceFaceNormals(void)
{
    FDEBUG(("OSGExtrusion:calcSweepSurfaceFaceNormals: Calculating sweep surface face normals\n"));

    if(_grid.size() < _spine.size())
    {
        FFATAL(("OSGExtrusion:calcSweepSurfaceFaceNormals: Grid not initialized\n"));
        return;
    }
    
    // calculate face normals
    for(UInt32 i = 0; i < _spine.size(); ++i)
    {
        UInt32 iPrev, iNext;

        // determine adjacent row indices
        if(_spineClosed)
        {
            // first point == last point
            iPrev = (i != 0) ? i - 1 : _spine.size() - 2;
            iNext = (i != _spine.size() - 1) ? i + 1 : 1;
        }
        else
        {
            iPrev = (i != 0) ? i - 1 : 0;
            iNext = (i != _spine.size() - 1) ? i + 1 : i;
        }

        for(UInt32 j = 0; j < _crossSection.size(); ++j)
        {
            Vec3f n;
            UInt32 jPrev, jNext;

            // determine adjacent column indices
            if(_crossSectionClosed)
            {
                // first point == last point
                jPrev = (j != 0) ? j - 1 : _crossSection.size() - 2;
                jNext = (j != _crossSection.size() - 1) ? j + 1 : 1;
            }
            else
            {
                jPrev = (j != 0) ? j - 1 : 0;
                jNext = (j != _crossSection.size() - 1) ? j + 1 : j;
            }

            // upper right face normal (1st quadrant)
            _grid[i][j].adjFaceNormals[0] =
                calcQuadFaceNormal(_grid[i][j].position,
                                   _grid[i][jNext].position,
                                   _grid[iNext][jNext].position,
                                   _grid[iNext][j].position);


            // upper left face normal (2nd quadrant)
            _grid[i][j].adjFaceNormals[1] = 
                calcQuadFaceNormal(_grid[i][j].position,
                                   _grid[iNext][j].position,
                                   _grid[iNext][jPrev].position,
                                   _grid[i][jPrev].position);


            // lower left face normal (3nd quadrant)
            _grid[i][j].adjFaceNormals[2] = 
                calcQuadFaceNormal(_grid[i][j].position,
                                   _grid[i][jPrev].position,
                                   _grid[iPrev][jPrev].position,
                                   _grid[iPrev][j].position);


            // lower right face normal (4th quadrant)
            _grid[i][j].adjFaceNormals[3] = 
                calcQuadFaceNormal(_grid[i][j].position,
                                   _grid[iPrev][j].position,
                                   _grid[iPrev][jNext].position,
                                   _grid[i][jNext].position);
        }
    }
}



//-----------------------------------------------------------------------------
// 
// Author: afischle
//-----------------------------------------------------------------------------
void ExtrusionSurface::storeSweepSurfaceWithoutNormals(GeoIndicesUI32Ptr  indicesPtr,
                                                       GeoPLengthsUI32Ptr lensPtr,
                                                       GeoPTypesUI8Ptr    typesPtr)
{
    assert(indicesPtr != NullFC);
    assert(lensPtr    != NullFC);
    assert(typesPtr   != NullFC);

    for(UInt32 i = 0; i < _spine.size() - 1; i++)
    {
        for(UInt32 j = 0; j < _crossSection.size(); j++)
        {
            Vertex v;
            // begin new triangle strip
            v = _grid[i+1][j];

            // store position (and texcoord if available)
            storeVertex(v, indicesPtr);

            v = _grid[i][j];
            // store position (and texcoord if available)
            storeVertex(v, indicesPtr);
        }
        // store row strip
        storePrimitive(GL_TRIANGLE_STRIP, lensPtr, typesPtr);
    }
}

void ExtrusionSurface::storeSweepSurfaceWithNormals(GeoIndicesUI32Ptr  indicesPtr,
                                                    GeoPLengthsUI32Ptr lensPtr,
                                                    GeoPTypesUI8Ptr    typesPtr)
{
    assert(indicesPtr != NullFC);
    assert(lensPtr    != NullFC);
    assert(typesPtr   != NullFC);

    // we need to calculate the face normals first
    calcSweepSurfaceFaceNormals();
 
    if(_ccw)
    {
        // The current face is the face in quadrant 1 of the vertex
        // grid[i,j]. Stripes are generated in positive j direction
        // along the cross-section.
        UInt32 spineEnd = _spine.size() - 1;
        UInt32 cSEnd = _crossSection.size() - 1;
        for(UInt32 i = 0; i < spineEnd; i++)
        {
            // upper left vertex of current quad face
            // current face is located in 4th quadrant of vertex
            calcVertexNormal(&_grid[i+1][0], 3);
            storeVertex(_grid[i+1][0], indicesPtr);

            // lower left vertex of current quad face
            // current face is located in 1st quadrant of vertex            
            calcVertexNormal(&_grid[i][0], 0);
            storeVertex(_grid[i][0], indicesPtr);

            Vec3f fN = _grid[i][0].adjFaceNormals[0];
            for(UInt32 j = 0; j < cSEnd; j++)
            {
                // The next face is the face in quadrant 1 of the vertex
                // grid[i,j+1]                
                Vec3f fNNext = _grid[i][j+1].adjFaceNormals[0];

                // if the creaseAngle is too small the strip has to be split,
                // because the normals are not shared along the common edge
                // of the current and the next face.
                // if j + 1 == csEnd the current quad is the last one
                if((fN.enclosedAngle(fNNext) + Eps > _creaseAngle - Eps)
                   || (j + 1 == cSEnd))
                {
                    // upper right vertex of current quad face
                    // current face is located in 3rd quadrant of vertex
                    calcVertexNormal(&_grid[i+1][j+1], 2);
                    storeVertex(_grid[i+1][j+1], indicesPtr);

                    // upper right vertex of current quad face
                    // current face is located in 2nd quadrant of vertex
                    calcVertexNormal(&_grid[i][j+1], 1);
                    storeVertex(_grid[i][j+1], indicesPtr);
                    
                    // terminate strip
                    storePrimitive(GL_TRIANGLE_STRIP, lensPtr, typesPtr);
                }

                // Either the strip was split above or not. In both cases
                // continue/begin new strip if there's still a quad left
                if(j + 1 < cSEnd)
                {
                    
                    // upper left vertex of _next_ quad face
                    // next face is located in 4th quadrant of vertex
                    calcVertexNormal(&_grid[i+1][j+1], 3); 
                    storeVertex(_grid[i+1][j+1], indicesPtr);
                    
                    // lower left vertex of _next_ quad face
                    // next face is located in 1st quadrant of vertex
                    calcVertexNormal(&_grid[i][j+1], 0);
                    storeVertex(_grid[i][j+1], indicesPtr);
                }

                // update face normal
                fN = fNNext;                
            }
        }
    }
    else // cw case
    {
        // The current face is the face in quadrant 1 of the vertex
        // grid[i,j-1]. Stripes are generated in negative j direction
        // along the cross-section.
        for(UInt32 i = 0; i < _spine.size() - 1; i++)
        {
            UInt32 cSEnd = _crossSection.size() - 1;

            // begin new triangle strip
            calcVertexNormal(&_grid[i+1][cSEnd], 2);
            storeVertex(_grid[i+1][cSEnd], indicesPtr);

            calcVertexNormal(&_grid[i][cSEnd], 1);
            storeVertex(_grid[i][cSEnd], indicesPtr);

            Vec3f fN = _grid[i][cSEnd].adjFaceNormals[0];            
            for(UInt32 j = cSEnd; j > 0; j--)
            {
                Vec3f fNNext = _grid[i][j - 1].adjFaceNormals[0];
                if((fN.enclosedAngle(fNNext) + Eps > _creaseAngle - Eps)
                   || (j == 1))
                {
                    calcVertexNormal(&_grid[i + 1][j - 1], 3);
                    storeVertex(_grid[i + 1][j - 1], indicesPtr);
                    
                    calcVertexNormal(&_grid[i][j - 1], 0);
                    storeVertex(_grid[i][j - 1], indicesPtr);
                    
                    // terminate strip
                    storePrimitive(GL_TRIANGLE_STRIP, lensPtr, typesPtr);
                }

                if(j > 1) // still one quad to go
                {
                    calcVertexNormal(&_grid[i + 1][j - 1], 2);
                    storeVertex(_grid[i + 1][j - 1], indicesPtr);
                
                    calcVertexNormal(&_grid[i][j - 1], 1);
                    storeVertex(_grid[i][j - 1], indicesPtr);
                }
                // update face normal
                fN = fNNext;                
            }
        }
    }
}


//----------------------------------------------------------------------
// Returns true if the origin lies in the left half plane of the
// oriented line AB.
//
// Author: afischle
//----------------------------------------------------------------------
inline bool ExtrusionSurface::isLeft(const Pnt2f &a, const Pnt2f &b)
{
    Vec2f d = b - a;
    d.normalize();
    // compute the normal pointing into the _right_ half plane of the oriented
    // line
    Vec2f n = Vec2f(d.y(), -d.x());
    // the dot product is >0 when two vectors point into the same direction
    return n.dot(a) > 0.f;
}


//-----------------------------------------------------------------------------
// Computes the minimum of the y-components of all points of the contour.
//
// Author: afischle
//-----------------------------------------------------------------------------
Real32 ExtrusionSurface::computeMinYAbs(const std::vector<Pnt2f> &contour,
                                        Real32 alpha)
{
    const Real32 sinAlpha = osgsin(alpha);
    const Real32 cosAlpha = osgcos(alpha);

    Real32 minYAbs = 1.f;
    for(std::vector<Pnt2f>::const_iterator it = contour.begin();
        it != contour.end(); ++it)
    {
        Real32 y = sinAlpha * it->x() + cosAlpha * it->y();
        if(osgabs(y) < minYAbs)
            minYAbs = y;
    }

    return minYAbs;
}

//-----------------------------------------------------------------------------
// Computes a rotation of the curve such that the minimum of the y-components
// of all of its points is the maximal for alpha = n * (2 * Pi / nAngles),
// where 0 <= n <= nAngles.
//
// Author: afischle
//-----------------------------------------------------------------------------
Real32 ExtrusionSurface::calcBetterRotationAngle(const std::vector<Pnt2f> &contour,
                                                 UInt32 nAngles)
{
    Real32 maxMinY = 0.f;
    Real32 bestAlpha = 0.f;

    Real32 alphaInc = 2 * Pi / nAngles;
    for(Real32 alpha = 0.f; alpha < 2 * Pi; alpha += alphaInc)
    {
        Real32 minYAlpha = computeMinYAbs(contour, alpha);
        if(minYAlpha > maxMinY)
        {
            maxMinY = minYAlpha;
            bestAlpha = alpha;
        }
    }

    return bestAlpha;
}


//-----------------------------------------------------------------------------
// Translates the given curve such that the specified reference point is
// translated to the origin and rescales it to the unit square.
//
// Author: afischle
//-----------------------------------------------------------------------------
bool ExtrusionSurface::calcOptimizedContour(const std::vector<Pnt2f> &contour,
                                            const Pnt2f &point,
                                            std::vector<Pnt2f> *optimizedContour)
{
    // copy the input
    std::vector<Pnt2f> coords(contour);

    // translate the reference point to the origin
    // and compute a scale factor
    Real32 maxLen = std::numeric_limits<Real32>::min();
    Real32 minLen = std::numeric_limits<Real32>::max();

    for(std::vector<Pnt2f>::iterator it = coords.begin();
            it != coords.end(); ++it)
    {
        // translate the problem to the origin
        *it -= Vec2f(point);
        Real32 len = Vec2f(*it).length();

        if(len > maxLen)  maxLen = len;
        if(len < minLen)  minLen = len;
    }

    if(maxLen < Eps)
    {
        FWARNING(("OSGExtrusion:calcOptimizedContour: Contour completely degenerate\n"));
        return false;
    }

    if(minLen < Eps)
    {
        FWARNING(("OSGExtrusion:calcOptimizedContour: Reference point on curve\n"));
        return false;
    }

    // rescale the contour to the unit disk and determine the minimal
    // absolute y coordinate
    Real32 minAbsY = 1.f;
    for(std::vector<Pnt2f>::iterator it = coords.begin();
            it != coords.end(); ++it)
    {
        *it /= maxLen;
        // osgabs(it->y()) <= 1.f after rescale
        if(osgabs(it->y()) < minAbsY)
            minAbsY = osgabs(it->y());
    }

    optimizedContour->clear();
    optimizedContour->reserve(coords.size());
    
    if(minAbsY > Eps) // we can probably determine all crossings
    {
        optimizedContour->assign(coords.begin(), coords.end());
    }
    else // try to rotate the contour
    {
        // we need to rotate the contour to get a reasonable result
        FDEBUG(("OSGExtrusion:calcOptimizedContour: Contour needs rotation\n"));
        // compute the best rotation angle for 64 equal partitions 
        // of the circle
        Real32 alpha = calcBetterRotationAngle(contour, 64);
        FDEBUG(("OSGExtrusion:calcOptimizedContour: Rotation angle is: %f\n",
                alpha));

        Real32 sinAlpha = osgsin(alpha);
        Real32 cosAlpha = osgcos(alpha);

        // rotate the contour and copy it into the output vector
        for(std::vector<Pnt2f>::iterator it = coords.begin();
            it != coords.end(); ++it)
        {
            Pnt2f p;
            p[0] = cosAlpha * it->x() - sinAlpha * it->y();
            p[1] = sinAlpha * it->x() + cosAlpha * it->y();

            optimizedContour->push_back(p);
        }
    }

    // optimization successful
    return true;
}


//----------------------------------------------------------------------
// Returns the winding number of the given contour with respect to the
// specified point by counting how often the infinite line f(x) = point.y
// was crossed by the curve.
// 
// Author: afischle
//----------------------------------------------------------------------
Int32 ExtrusionSurface::calcWindingNumber(const std::vector<Pnt2f> &contour, 
                                          const Pnt2f &point)
{
    Int32 windingNumber = 0;
    std::vector<Pnt2f> coords;

    // translate contour to origin and rotate it to a better position
    calcOptimizedContour(contour, point, &coords);

    const Pnt2f *prevPoint = &(coords[coords.size() - 1]);
    for(UInt32 i = 0; i < coords.size(); ++i)
    {
        const Pnt2f *curPoint = &(coords[i]);
        if(prevPoint->y() < 0.f)
        {
            // upward crossing
            if(curPoint->y() > 0.f)
            {
                if(isLeft(*prevPoint, *curPoint) == true)
                    windingNumber++;
            }
        }
        else // prevPoint->y() > 0.f
        {
            // downward crossing
            if(curPoint->y() < 0.f)
            {
                if(isLeft(*prevPoint, *curPoint) == false)
                    windingNumber--;
            }
        }
        prevPoint = curPoint;
    }

    return windingNumber;
}


//-----------------------------------------------------------------------------
// Calculates a convex cap surface bounded by the row-curve with index
// spineIndex in the grid. If it is a begin cap its normal is reversed.
//
// The positions, normals and texture coordinates of the generated primitives
// are inserted into maps which map the respective properties to an integer
// index. The indices so obtained are stored in the indices field container.
// The lengths and types of the generated primitives are directly stored in
// the respective field containers.
//
// Author: afischle
//-----------------------------------------------------------------------------
void ExtrusionSurface::storeConvexCap(UInt32 spineIndex, 
                                      bool isBeginCap, 
                                      GeoIndicesUI32Ptr  indicesPtr,
                                      GeoPLengthsUI32Ptr lensPtr,
                                      GeoPTypesUI8Ptr    typesPtr)
{
    assert(indicesPtr != NullFC);
    assert(lensPtr    != NullFC);
    assert(typesPtr   != NullFC);

    if(!_convex)
    {
        FFATAL(("OSGExtrusion:storeCap: Non-convex caps not yet implemented\n"));
        return;
    }
    
    std::vector<Pnt3f> capBorderCurveInSection;
    std::vector<Pnt2f> capBorderCurveInXZPlane(_crossSection);
    capBorderCurveInSection.reserve(_grid[spineIndex].size());

    std::vector<Vertex>::const_iterator gIt = _grid[spineIndex].begin();
    while(gIt != _grid[spineIndex].end())
    {
        capBorderCurveInSection.push_back(gIt->position);
        ++gIt;
    }

    if(!_crossSectionClosed)
    {
        capBorderCurveInSection.push_back(_grid[spineIndex].front().position);
        capBorderCurveInXZPlane.push_back(_crossSection.front());
    }

    FDEBUG(("OSGExtrusion:storeCap: Generating cap[%d], type=%s, _ccw=%s\n", 
            spineIndex,
            (isBeginCap ? "begin cap" : "end cap"),
            (_ccw ? "TRUE" : "FALSE")));
           
    Pnt3f baryCenterInSection;
    Pnt2f baryCenterInXZPlane;

    std::vector<Pnt3f>::iterator sIt = capBorderCurveInSection.begin();
    std::vector<Pnt2f>::iterator cIt = capBorderCurveInXZPlane.begin();

    // compute barycenters
    UInt32 nBorderPoints = capBorderCurveInSection.size() - 1;
    // calculate the mean of all points with the exception of the last
    // (which is equal to the first)
    for(UInt32 i = 0; i < nBorderPoints; ++i, ++sIt, ++cIt)
    {
        baryCenterInSection += Vec3f(*sIt);
        baryCenterInXZPlane += Vec2f(*cIt);
    }
    baryCenterInSection /= nBorderPoints;
    baryCenterInXZPlane /= nBorderPoints;

   /* X3D Spec:
    *
    * Normals for the caps are generated along the Y-axis of the SCP,
    * with the ordering determined by viewing the cross-section from
    * above (looking along the negative Y-axis of the SCP). By default, a
    * beginCap with a counterclockwise ordering shall have a normal along
    * the negative Y-axis. An endCap with a counterclockwise ordering
    * shall have a normal along the positive Y-axis.
    *
    */

    // compute winding number
    Int32 windNum = calcWindingNumber(capBorderCurveInXZPlane,
                                      baryCenterInXZPlane);
    
    FDEBUG(("OSGExtrusion:storeCap: Cross-section has winding number: %d\n",
            windNum));

    bool isCCWOrderedCap = true;
    if(windNum != 0)
    {
        isCCWOrderedCap = (windNum > 0) ? true : false;
    }
    else
    {
        FWARNING(("OSGExtrusion:storeCap: Winding number = 0. Culling might be incorrect\n"));
        // hope isCCWCrossSection == true ist correct
    }

    Vertex v;
    v.position = baryCenterInSection;

    // compute cap normal
    bool negateNormal = false;
    if(_createNormals)
    {
        // Take the Y-axis at the given spine index as the cap normal
        Vec3f capNormal = Vec3f(_transform[spineIndex][1]);

        if(isBeginCap) 
        {
            if(!isCCWOrderedCap)
            {
                negateNormal = true;
            }
        }
        else // end cap
        {
            if(isCCWOrderedCap)
            {
                negateNormal = true;
            }
        }

        if(!_ccw)
            negateNormal = !negateNormal;

        v.normal = negateNormal ? -capNormal : capNormal;

        FDEBUG(("OSGExtrusion:storeCap: Cap normal: (%f, %f, %f)\n",
                v.normal[0], v.normal[1], v.normal[2]));
    }
     
    // calculate texture coordinates
    // compute 2D bounding box for cross section
    Real32 xMin,xMax,zMin,zMax;
    xMin = xMax = capBorderCurveInXZPlane[0][0];
    zMin = zMax = capBorderCurveInXZPlane[0][1];
    for(cIt = capBorderCurveInXZPlane.begin(); 
        cIt != capBorderCurveInXZPlane.end(); ++cIt)
    {
        if(xMin > (*cIt)[0]) xMin = (*cIt)[0];
        if(xMax < (*cIt)[0]) xMax = (*cIt)[0];
        if(zMin > (*cIt)[1]) zMin = (*cIt)[1];
        if(zMax < (*cIt)[1]) zMax = (*cIt)[1];
    }
    Real32 xWidth = xMax - xMin;
    Real32 zWidth = zMax - zMin;
    Real32 maxWidth = (xWidth > zWidth) ? xWidth : zWidth;
    Real32 scale = (maxWidth > Eps) ? 1.f / maxWidth : 1.f;

    v.texCoord[0] = (baryCenterInXZPlane[0] - xMin) * scale;
    v.texCoord[1] = (baryCenterInXZPlane[1] - zMin) * scale;

    // store barycenter vertex
    storeVertex(v, indicesPtr);

    bool reverseInsert = false;
    
    if(isCCWOrderedCap)
    {
        if(!negateNormal)
            reverseInsert = true;
    }
    else
    {
        if(negateNormal)
            reverseInsert = true;
    }

    if(reverseInsert)
    {
        FDEBUG(("OSGExtrusion:storeCap: storing cap border vertices reversed\n")); 
        std::vector<Pnt3f>::reverse_iterator sRevIt 
            = capBorderCurveInSection.rbegin();
        std::vector<Pnt2f>::reverse_iterator  cRevIt
            = capBorderCurveInXZPlane.rbegin();

        // store cross section image vertices
        for(; sRevIt != capBorderCurveInSection.rend(); ++cRevIt, ++sRevIt)
        {
            v.position = *sRevIt;
            v.texCoord[0] = ((*cRevIt)[0] - xMin) * scale;
            v.texCoord[1] = ((*cRevIt)[1] - zMin) * scale;

            storeVertex(v, indicesPtr);
        }
    }
    else // don't reverse insert
    {
        FDEBUG(("OSGExtrusion:storeCap: storing cap border vertices\n")); 
        sIt = capBorderCurveInSection.begin();
        cIt = capBorderCurveInXZPlane.begin();
        // store cross section image vertices
        for(; sIt != capBorderCurveInSection.end(); ++cIt, ++sIt)
        {
            v.position = *sIt;
            v.texCoord[0] = ((*cIt)[0] - xMin) * scale;
            v.texCoord[1] = ((*cIt)[1] - zMin) * scale;

            storeVertex(v, indicesPtr);
        }
    }

    storePrimitive(GL_TRIANGLE_FAN, lensPtr, typesPtr);
}


//-----------------------------------------------------------------------------
// Stores the contents of the maps containing the positions, normals and
// texture coordinates into the specified field containers, where the
// map entries 'property -> index' are stored s.th. ctnr[index] = property.
//
// Normals and texture coordinates are only stored if their create flags
// (i.e _createNormals and _createTexCoords) are set to true.
//
// Author: afischle
//-----------------------------------------------------------------------------
void ExtrusionSurface::storeMaps(GeoPositions3fPtr posPtr,
                                 GeoNormals3fPtr   normalsPtr,
                                 GeoTexCoords2fPtr texPtr)
{
    assert(posPtr != NullFC);

    FDEBUG(("OSGExtrusion:storeMaps: position map size:    %d\n", _posMap.size()));
    FDEBUG(("OSGExtrusion:storeMaps: normal map size:      %d\n", _normalMap.size()));
    FDEBUG(("OSGExtrusion:storeMaps: tex coord map size:   %d\n", _texCoordMap.size()));

    // write shared positions
    beginEditCP(posPtr, GeoPositions3f::GeoPropDataFieldMask);

    posPtr->resize(_posMap.size());
    for(PositionMap::iterator pMIt = _posMap.begin();
        pMIt != _posMap.end(); ++pMIt)
    {
        posPtr->setValue(pMIt->first, pMIt->second);
    }

    endEditCP(posPtr, GeoPositions3f::GeoPropDataFieldMask);

    // write shared vertex normals
    if(_createNormals)
    {
        assert(normalsPtr != NullFC);
        beginEditCP(normalsPtr, GeoNormals3f::GeoPropDataFieldMask);

        normalsPtr->resize(_normalMap.size());
        for(NormalMap::iterator nMIt = _normalMap.begin();
            nMIt != _normalMap.end(); ++nMIt)
        {
            normalsPtr->setValue(nMIt->first, nMIt->second);
        }

        endEditCP(normalsPtr, GeoNormals3f::GeoPropDataFieldMask);
    }

    // write shared texture coordinates
    if(_createTexCoords)
    {
        assert(texPtr != NullFC);
        beginEditCP(texPtr, GeoTexCoords2f::GeoPropDataFieldMask);

        texPtr->resize(_texCoordMap.size());
        for(TexCoordMap::iterator tMIt = _texCoordMap.begin();
            tMIt != _texCoordMap.end(); ++tMIt)
        {
            texPtr->setValue(tMIt->first, tMIt->second);
        }

        endEditCP(texPtr, GeoTexCoords2f::GeoPropDataFieldMask);
    }
}


//-----------------------------------------------------------------------------
// Creates an extrusion surface consisting of a sweep surface and two optional
// cap surfaces. The positions, normal and texture coordinates are shared where
// possible.
//
// Todo:
//  * Support non-convex cap surfaces
//  * Refine orientations
//
// Author: afischle
//-----------------------------------------------------------------------------
GeometryPtr ExtrusionSurface::createGeometry(UInt32 nSubdivs)
{
    // do some sanity checks on and determines the topology
    // of the _spine and _crossSection member fields
    if(!verifyInput())
    {
        FWARNING(("OSGExtrusion:createGeometry: Invalid input. Returning NullFC\n"));
        return NullFC;
    }

    // initialize topology flags (i.e spine/_crossSection closure)
    determineTopology();
    
    // optionally subdivide input data
    if(nSubdivs > 0)
    {
        refineCrossSection(nSubdivs);

        if(_orientation.size() == 1)
        {
            refineSpine(nSubdivs);
            refineScale(nSubdivs);
        }
        else // more than 1 orientation
        {
            // It'd be necessary to refine the orientations in order to get
            // a consistent result, but this is not implemented yet.
            FINFO(("OSGExtrusion:createGeometry: Too many orientations. Not refining along spine\n"));
        }
    }

    // allocate vertex grid structure
    initGrid();
    calcSweepSurfacePositions();

    if(_createTexCoords)
    {
        calcSweepSurfaceTexCoords();
    }

    // create opensg geometry field containers
    GeoPositions3fPtr  posPtr     = GeoPositions3f::create();
    GeoPLengthsUI32Ptr lensPtr    = GeoPLengthsUI32::create();
    GeoIndicesUI32Ptr  indicesPtr = GeoIndicesUI32::create();
    GeoPTypesUI8Ptr    typesPtr   = GeoPTypesUI8::create();
    GeoNormals3fPtr    normalsPtr = NullFC;
    GeoTexCoords2fPtr  texPtr     = NullFC;

    if(_createNormals)
        normalsPtr = GeoNormals3f::create();

    if(_createTexCoords)
        texPtr = GeoTexCoords2f::create();

    beginEditCP(indicesPtr, GeoIndicesUI32::GeoPropDataFieldMask);
    beginEditCP(lensPtr,    GeoPLengthsUI32::GeoPropDataFieldMask);
    beginEditCP(typesPtr,   GeoPTypesUI8::GeoPropDataFieldMask);

    if(_createNormals)
    {
        // store sweep surface as triangle strips with vertex normals
        storeSweepSurfaceWithNormals(indicesPtr, lensPtr, typesPtr);
    }
    else
    {
        // store sweep surface as triangle strips without vertex normals
        storeSweepSurfaceWithoutNormals(indicesPtr, lensPtr, typesPtr);
    }

    if(_convex)
    {
        // calculate and store caps as triangle fans
        if(_beginCap)
        {
            FDEBUG(("OSGExtrusion:createGeometry: Creating begin cap\n"));
            storeConvexCap(0,           // spine section 0 
                           true,        // flip normal
                           indicesPtr, 
                           lensPtr, 
                           typesPtr);
        }
        
        if(_endCap)
        {
            FDEBUG(("OSGExtrusion:createGeometry: Creating end cap\n"));
            storeConvexCap(_spine.size() - 1,  // last spine section
                           false,              // don't flip normal
                           indicesPtr,
                           lensPtr, 
                           typesPtr);
        }
    }
    else // non-convex case
    {
        FFATAL(("OSGExtrusion:createGeometry: Support for non-convex caps not implemented\n"));
    }
    
#ifdef DEBUG_VERTEX_NORMALS
    // add surface normals for debugging purposes
    storeVertexNormalGeo(indicesPtr, lensPtr, typesPtr);
#endif

#ifdef DEBUG_FACE_NORMALS
    // add sweep surface face normals for debugging purposes
    storeFaceNormalGeo(indicesPtr, lensPtr, typesPtr);
#endif    

    endEditCP(indicesPtr, GeoIndicesUI32::GeoPropDataFieldMask);
    endEditCP(lensPtr,    GeoPLengthsUI32::GeoPropDataFieldMask);
    endEditCP(typesPtr,   GeoPTypesUI8::GeoPropDataFieldMask);

    // store the shared vertex data into the vertex data field containers
    storeMaps(posPtr, normalsPtr, texPtr);

    // create a new OpenSG geometry
    GeometryPtr geoPtr = Geometry::create();

    beginEditCP(geoPtr, Geometry::TypesFieldMask  |
                Geometry::LengthsFieldMask        |
                Geometry::IndicesFieldMask        |
                Geometry::IndexMappingFieldMask   |
                Geometry::PositionsFieldMask      |
                Geometry::NormalsFieldMask        |
                Geometry::TexCoordsFieldMask      );

    // The interleaved multi-index blocks have one of the following 
    // layouts (depending on _createNormals and _createTexCoords):
    //
    // 1. (Position)                  
    // 2. (Position, Normal)
    // 3. (Position, TexCoord)        
    // 4. (Position, Normal, TexCoord)
    geoPtr->getIndexMapping().push_back(Geometry::MapPosition);
    if(_createNormals)
        geoPtr->getIndexMapping().push_back(Geometry::MapNormal);
    if(_createTexCoords)
        geoPtr->getIndexMapping().push_back(Geometry::MapTexCoords);

    // set primitive data field containers
    geoPtr->setLengths(lensPtr);
    geoPtr->setIndices(indicesPtr);
    geoPtr->setTypes(typesPtr);
   
    // set vertex data field containers
    geoPtr->setPositions(posPtr);
    geoPtr->setNormals(normalsPtr);
    geoPtr->setTexCoords(texPtr);
   
    endEditCP(geoPtr, Geometry::TypesFieldMask  |
              Geometry::LengthsFieldMask        |
              Geometry::IndicesFieldMask        |
              Geometry::IndexMappingFieldMask   |
              Geometry::PositionsFieldMask      |
              Geometry::NormalsFieldMask        |
              Geometry::TexCoordsFieldMask      );


    SINFO << "OSGExtrusion:createGeometry: Stats: ("
          << _primitiveCount     << '/'
          << _totalVertexCount   << '/'
          << _posMap.size() << '/'
          << _normalMap.size()   << '/'
          << _texCoordMap.size() << ')'
          << "(Prims/Verts/Pos/Norms/TexCoords)"
          << std::endl; 
        
    return geoPtr;
}


NodePtr OSG::makeExtrusion(const std::vector<Pnt2f> &crossSection,
                           const std::vector<Quaternion> &orientation,
                           const std::vector<Vec2f> &scale,
                           const std::vector<Pnt3f> &spine,
                           Real32 creaseAngle,
                           bool beginCap,
                           bool endCap, 
                           bool ccw, 
                           bool convex, 
                           bool buildNormal,
                           bool buildTexCoord, 
                           UInt32 numOfSubdivision)
{
    GeometryPtr pGeo = makeExtrusionGeo(crossSection, 
                                        orientation,
                                        scale, 
                                        spine,
                                        creaseAngle,
                                        beginCap, 
                                        endCap, 
                                        ccw, 
                                        convex,
                                        buildNormal, 
                                        buildTexCoord,
                                        numOfSubdivision);
    if(pGeo == NullFC)
    {
        return NullFC;
    }
    
    NodePtr node = Node::create();
    beginEditCP(node);
    node->setCore(pGeo);
    endEditCP(node);
    return node;
}


GeometryPtr OSG::makeExtrusionGeo(const std::vector<Pnt2f> &crossSection,
                                  const std::vector<Quaternion> &orientation,
                                  const std::vector<Vec2f> &scale,
                                  const std::vector<Pnt3f> &spine,
                                  Real32 creaseAngle,
                                  bool beginCap,
                                  bool endCap, 
                                  bool ccw, 
                                  bool convex,
                                  bool buildNormal,
                                  bool buildTexCoord, 
                                  UInt32 numSubdivs)
{
    // debug dump of parameters
    const char* prefix = "OSGExtrusion:makeExtrusionGeo";
    FDEBUG(("%s: crossSection.size() == %d\n", prefix, crossSection.size()));
    FDEBUG(("%s: orientation.size()  == %d\n", prefix, orientation.size()));
    FDEBUG(("%s: scale.size()        == %d\n", prefix, scale.size()));
    FDEBUG(("%s: spine.size()        == %d\n", prefix, spine.size()));
    FDEBUG(("%s: creaseAngle         == %f\n", prefix, creaseAngle));
    FDEBUG(("%s: beginCap            == %s\n", 
            prefix, (beginCap ? "TRUE" : "FALSE")));
    FDEBUG(("%s: endCap              == %s\n", 
            prefix, (endCap ? "TRUE" : "FALSE")));
    FDEBUG(("%s: ccw                 == %s\n", 
            prefix, (ccw ? "TRUE" : "FALSE")));
    FDEBUG(("%s: convex              == %s\n", 
            prefix, (convex ? "TRUE" : "FALSE")));
    FDEBUG(("%s: buildNormal         == %s\n", 
            prefix, (buildNormal ? "TRUE" : "FALSE")));
    FDEBUG(("%s: buildTexCoord       == %s\n", 
            prefix, (buildTexCoord ? "TRUE" : "FALSE")));
    FDEBUG(("%s: nSubdivs            == %d\n", prefix, numSubdivs));

    if(crossSection.size() == 1)
    {
        FWARNING(("OSGExtrusion: Encountered 1 point cross section\n"));
        return NullFC;
    }

    // instantiate an ExtrusionSurface object and initialize it
    ExtrusionSurface surf(crossSection,
                          orientation,
                          scale,
                          spine,
                          creaseAngle,
                          beginCap,
                          endCap,
                          ccw,   
                          convex,
                          buildNormal,
                          buildTexCoord);

    // create and export geometry from extrusion surface object
    GeometryPtr geoPtr = surf.createGeometry(numSubdivs);

    return geoPtr;
}

//-----------------------------------------------------------------------------
//                       Subdivision Helper Functions                          
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Subdivides the input data by applying the subdivision scheme
// (-1/16, 9/16, 9/16, -1/16) at interior and (3/8, 6/8, -1/8) at boundary
// points. Whether an input vector is to be interpreted as a closed curve is
// determined by the closed flag. For closed curves the first and the last point
// are expected to be the same.
//
// The subdivided result is stored in the user supplied vector pointed to by
// dataOut.
//
// Author: afischle
//-----------------------------------------------------------------------------
template <class VectorTypeT>
static void subdivide(const typename std::vector<VectorTypeT>& dataIn,
                            typename std::vector<VectorTypeT>* dataOut,
                            bool closed)
{
    typename std::vector<VectorTypeT>::const_iterator inputIt;

    // just copy the data if we can't interpolate
    if(dataIn.size() <= 2)
    {
        // copy and bail out
        dataOut->assign(dataIn.begin(), dataIn.end());
        return;
    }

    // reset vector
    dataOut->clear();
    dataOut->reserve((2 * dataIn.size()) + 1);

    inputIt = dataIn.begin();
    dataOut->push_back(*inputIt);  // copy first vertex
    
    // If closed apply the 4pt scheme (-1/16, 9/16, 9/16, -1/16) to the first
    // point. In order to do this we need to wrap around in the first argument.
    if(closed)
    {
        //dataIn[0] = dataIn[n-1], so we need to subtract one more
        dataOut->push_back(apply4PtScheme<VectorTypeT>(dataIn.end() - 2,
                                                       inputIt,
                                                       inputIt + 1,
                                                       inputIt + 2));
    }
    // Apply 3pt scheme (3/8, 6/8, -1/8) to the first point.
    else
    {
        dataOut->push_back(apply3PtScheme<VectorTypeT>(inputIt,
                                                       inputIt + 1,
                                                       inputIt + 2));        
    }
    inputIt++;  // advance to next vertex
    
    
    // if there are more than 3 points available, we can apply the 4 point 
    // scheme (-1/16, 9/16, 9/16, -1/16) to all points with the exception 
    // of the first and the last point.
    if(dataIn.size() > 3)
    {
        //insert the interpolated points between inputIt and inputIt + 1
        for(; (inputIt + 2) != dataIn.end(); ++inputIt)
        {
            dataOut->push_back(*inputIt);
            dataOut->push_back(apply4PtScheme<VectorTypeT>(inputIt - 1,
                                                           inputIt,
                                                           inputIt + 1,
                                                           inputIt + 2));
        }
    }
    
    dataOut->push_back(*inputIt);
    
    // If closed apply the 4pt scheme (-1/16, 9/16, 9/16, -1/16) to the
    // points with indices (n-3, n-2, n-1, 1) (equivalent to (n-3,n-2,0,1))
    if(closed)
    {
        dataOut->push_back(apply4PtScheme<VectorTypeT>(dataIn.end() - 3,
                                                      dataIn.end() - 2,
                                                      dataIn.begin(),
                                                      dataIn.begin() + 1));
    }
    else
    {
        // Apply 3pt scheme (-1, 6, 3) by reversing the order of the 
        // points for the boundary and applying (3, 6, -1) 
        dataOut->push_back(apply3PtScheme<VectorTypeT>(dataIn.end() - 1,
                                                       dataIn.end() - 2,
                                                       dataIn.end() - 3));
    }

    // push back last input vertex
    dataOut->push_back(dataIn.back());
}

//-----------------------------------------------------------------------------
// Subdivides the input data nTimes and stores the result in a user supplied
// vector pointed to by dataOut. The closed flag determines whether iterators
// are wrapped around at the ends or not.
//
// Author: afischle
//-----------------------------------------------------------------------------
template <class VectorTypeT>
static void subdivide(const typename std::vector<VectorTypeT>& dataIn,
                      typename std::vector<VectorTypeT>* dataOut,
                      UInt32 nTimes,
                      bool closed)
{
    std::vector<VectorTypeT> in(dataIn), out;
    for(UInt32 i = 0; i < nTimes; i++)
    {
        if(i + 1 < nTimes) // still one round to go
        {
            out.clear();
            out.reserve(2 * (in.size() + 1));
            subdivide<VectorTypeT>(in, &out, closed);

            // swap buffers
            in.swap(out);
        }
        else  // final subdivision step
        {
            dataOut->clear();
            dataOut->reserve(2 * (in.size() + 1));

            // subdivide and write result directly into dataOut
            subdivide<VectorTypeT>(in, dataOut, closed);
        }
    }
}

//-----------------------------------------------------------------------------
//                             Debugging helpers                               
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Adds vertex normals to the created geometry
//
// Author: afischle
//-----------------------------------------------------------------------------
void ExtrusionSurface::storeVertexNormalGeo(GeoIndicesUI32Ptr  indicesPtr,
                                            GeoPLengthsUI32Ptr lensPtr,
                                            GeoPTypesUI8Ptr    typesPtr)
{
    if(!_createNormals || !_createTexCoords)
        return;

    std::vector<Vec3f> nRevTable(_normalMap.size());
    std::vector<Pnt3f> pRevTable(_posMap.size());

    NormalMap::iterator   nIt = _normalMap.begin();
    PositionMap::iterator pIt = _posMap.begin();

    // build a lookup table of normal indices to vertex normals
    for(; nIt != _normalMap.end(); ++nIt)
        nRevTable[nIt->second] = nIt->first;

    // build a lookup table of position indices to vertex positions
    for(; pIt != _posMap.end(); ++pIt)
        pRevTable[pIt->second] = pIt->first;

    UInt32 prevN = indicesPtr->size();
    UInt32 i = 0;

    Vertex v;

    v.normal = Vec3f(0.f, 0.f, 0.f);
    v.texCoord = Vec2f(0.f, 0.f);

    while(i < prevN)
    {
        v.position = pRevTable[indicesPtr->getValue(i)];
        storeVertex(v, indicesPtr);
        
        v.position += 0.3f * nRevTable[indicesPtr->getValue(i+1)];
        storeVertex(v, indicesPtr);
        storePrimitive(GL_LINES, lensPtr, typesPtr);

        i+=3;
    }
}

//-----------------------------------------------------------------------------
// Adds face normals to the created geometry
//
// Author: afischle
//-----------------------------------------------------------------------------
void ExtrusionSurface::storeFaceNormalGeo(GeoIndicesUI32Ptr  indicesPtr,
                                          GeoPLengthsUI32Ptr lensPtr,
                                          GeoPTypesUI8Ptr    typesPtr)
{
    if(!_createNormals || !_createTexCoords)
        return;

    for(UInt32 i = 0; i < _grid.size(); i++)
    {
        for(UInt32 j = 0; j < _grid[i].size(); j++)
        {
            Vertex a = _grid[i][j];
            a.normal = Vec3f();

            for(UInt32 k = 0; k < 4; k++)
            {
                Vertex b_k =_grid[i][j];
                b_k.normal = Vec3f();
                b_k.position += 0.3f * a.adjFaceNormals[k];

                storeVertex(a, indicesPtr);
                storeVertex(b_k, indicesPtr);

                storePrimitive(GL_LINES, lensPtr, typesPtr);
            }
        }
    }
}


#ifdef DEBUG_VERTEX_NORMALS 
#undef DEBUG_VERTEX_NORMALS
#endif

#ifdef DEBUG_FACE_NORMALS 
#undef DEBUG_FACE_NORMALS
#endif

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
    static OSG::Char8 cvsid_cpp [] = "@(#)$Id: $";
    static OSG::Char8 cvsid_hpp [] = OSGEXTRUSIONGEOMETRY_HEADER_CVSID;
    static OSG::Char8 cvsid_inl [] = OSGEXTRUSIONGEOMETRY_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
