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
// Default Constructor
//-----------------------------------------------------------------------------
ExtrusionSurface::ExtrusionSurface():
    _creaseAngle(0),
    _cosCreaseAngle(1),
    _beginCap(true),
    _endCap(true),
    _ccw(true),
    _convex(true),
    _createNormals(true),
    _createTexCoords(true),
    _tess(0)
{}


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
    _cosCreaseAngle(osgcos(creaseAngle)),
    _beginCap(beginCap),
    _endCap(endCap),
    _ccw(ccw),
    _convex(convex),
    _createNormals(buildNormal),
    _createTexCoords(buildTexCoord),
    _tess(0)
{
    setCrossSection(crossSection);
    setOrientation(orientation);
    setScale(scale);
    setSpine(spine);
}


//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
ExtrusionSurface::~ExtrusionSurface()
{
    if(_tess != 0)
        gluDeleteTess(_tess);
}


//-----------------------------------------------------------------------------
// Calculates the y-axes of the base transform from the cross section plane
// to the spine-aligned cross section plane (SCP). The y- and z-axes are
// expected to be already stored in the _cp2scp vector.
//
// The computed x-axes are stored in the _cp2scp vector.
// 
// Author: afischle
//-----------------------------------------------------------------------------
void ExtrusionSurface::calcXAxes(void)
{
    std::vector<Matrix>::iterator tIt = _cp2scp.begin();

    // Either of the two cases below implies the cross product of
    // the y- and the z-axis vanish (and so do all x-axes)
    if(!_spineCollinear && !_revolutionSurface)
    {
        for(; tIt != _cp2scp.end(); ++tIt)
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
// The computed y-axes are stored in the _cp2scp vector.
//
// Author: afischle
//-----------------------------------------------------------------------------
void ExtrusionSurface::calcYAxes(void)
{
    bool yAxisDefined = false;

    std::vector<Pnt3f>::const_iterator  spineIt = _spine.begin();
    std::vector<Matrix>::iterator tIt = _cp2scp.begin();
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
                for(yIt = _cp2scp.begin(); yIt != (tIt + 1); ++yIt)
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
// The computed z-axes are stored in the _cp2scp vector.
//
// Author: afischle
//-----------------------------------------------------------------------------
void ExtrusionSurface::calcZAxes(void)
{
    bool zAxisDefined = false;

    std::vector<Pnt3f>::const_iterator  spineIt = _spine.begin();
    std::vector<Matrix>::iterator tIt = _cp2scp.begin();
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
                for(zIt = _cp2scp.begin(); zIt != tIt; ++zIt)
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
    // initialize the transformations with Id
    _cp2scp.resize(_spine.size());

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
        Vec3f v2(_cp2scp[0][1]);

        Quaternion q;
        q.setValue(v1, v2);
        q.getValue(rotation);
    }

    std::vector<Matrix>::iterator tIt             = _cp2scp.begin();
    std::vector<Pnt3f>::const_iterator spineIt    = _spine.begin();

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

        // affine translation to the spine point
        tIt->setTranslate(*spineIt);
    }

    FDEBUG(("OSGExtrusion:calcTransforms: spine collinear: %s\n", 
            (_spineCollinear ? "true" : "false")));

    FDEBUG(("OSGExtrusion:calcTransforms: revolution surface: %s\n",
            (_revolutionSurface ? "true" : "false")));
}


//-----------------------------------------------------------------------------
// Returns the cross section for editing
//-----------------------------------------------------------------------------
std::vector<Pnt2f> &ExtrusionSurface::editCrossSection()
{
    // Invalidate any previous triangulation
    _crossSectionLengths.clear();
    _crossSectionIndices.clear();
    _crossSectionTypes.clear();

    return _crossSection;
}


//-----------------------------------------------------------------------------
// Returns the orientation for editing
//-----------------------------------------------------------------------------
std::vector<Quaternion> &ExtrusionSurface::editOrientation()
{
    // Enforce recalculation of transformations
    _transform.clear();

    return _orientation;
}


//-----------------------------------------------------------------------------
// Returns the scale for editing
//-----------------------------------------------------------------------------
std::vector<Vec2f> &ExtrusionSurface::editScale()
{
    // Enforce recalculation of transformations
    _transform.clear();

    return _scale;
}


//-----------------------------------------------------------------------------
// Returns the spine for editing
//-----------------------------------------------------------------------------
std::vector<Pnt3f> &ExtrusionSurface::editSpine()
{
    // Enforce recalculation of transformations
    _cp2scp.clear();
    _transform.clear();

    return _spine;
}


//-----------------------------------------------------------------------------
// Helper function that creates a new geometry and fills it with the extrusion
//-----------------------------------------------------------------------------
GeometryPtr ExtrusionSurface::createGeometry(UInt32 nSubdivs)
{
    GeometryPtr geoPtr = Geometry::create();
    fillGeometry(geoPtr);
    return geoPtr;
}


//----------------------------------------------------------------------
// Tesselation callback function - Called at the beginning of a primitive
// Author: pdaehne
//----------------------------------------------------------------------
void OSG_APIENTRY ExtrusionSurface::gluTessBeginDataCB(GLenum type, void *polygonData)
{
    ExtrusionSurface *extrusionSurface = reinterpret_cast<ExtrusionSurface*>(polygonData);
    assert(extrusionSurface != 0);
    extrusionSurface->_crossSectionTypes.push_back(type);
}


//----------------------------------------------------------------------
// Tesselation callback function - Called at the end of a primitive
// Author: pdaehne
//----------------------------------------------------------------------
void OSG_APIENTRY ExtrusionSurface::gluTessEndDataCB(void *polygonData)
{
    ExtrusionSurface *extrusionSurface = reinterpret_cast<ExtrusionSurface*>(polygonData);
    assert(extrusionSurface != 0);
    extrusionSurface->_crossSectionLengths.push_back(extrusionSurface->_crossSectionIndices.size());
}


//----------------------------------------------------------------------
// Vertex data handler: Receives the triangle vertex indices from the
//                      GLU Tesselator
// Author: pdaehne
//----------------------------------------------------------------------
void OSG_APIENTRY ExtrusionSurface::gluTessVertexDataCB(void *vertexData, void *polygonData)
{
    // Go via 64 bit int to avoid problems on 64 bit machines
    UInt64 coordIndexHelp = UInt64(vertexData);
    UInt32 coordIndex = static_cast<UInt32>(coordIndexHelp);

    ExtrusionSurface *extrusionSurface = reinterpret_cast<ExtrusionSurface*>(polygonData);
    assert(extrusionSurface != 0);
    extrusionSurface->_crossSectionIndices.push_back(coordIndex);
}


//-----------------------------------------------------------------------------
// Creates an extrusion surface consisting of a sweep surface and two optional
// cap surfaces.
// Author: pdaehne
//-----------------------------------------------------------------------------
void ExtrusionSurface::fillGeometry(GeometryPtr &geoPtr)
{
    // Initialise and clear the geometry
    beginEditCP(geoPtr);
    geoPtr->editMFIndexMapping()->clear();
    // Initialise and clear coordinates
    GeoPositions3fPtr posPtr = GeoPositions3fPtr::dcast(geoPtr->getPositions());
    if(posPtr == NullFC)
    {
        posPtr = GeoPositions3f::create();
        geoPtr->setPositions(posPtr);
    }
    beginEditCP(posPtr, GeoPositions3f::GeoPropDataFieldMask);
    posPtr->clear();
    geoPtr->editMFIndexMapping()->push_back(Geometry::MapPosition);
    // Initialise and clear texture coordinates
    GeoTexCoords2fPtr texPtr = NullFC;
    if(_createTexCoords == true)
    {
        texPtr = GeoTexCoords2fPtr::dcast(geoPtr->getTexCoords());
        if(texPtr == NullFC)
        {
            texPtr = GeoTexCoords2f::create();
            geoPtr->setTexCoords(texPtr);
        }
        beginEditCP(texPtr, GeoTexCoords2f::GeoPropDataFieldMask);
        texPtr->clear();
        geoPtr->editMFIndexMapping()->push_back(Geometry::MapTexCoords);
    }
    else
        geoPtr->setTexCoords(NullFC);
    // Initialise and clear normals
    GeoNormals3fPtr normalsPtr = NullFC;
    if(_createNormals == true)
    {
        normalsPtr = GeoNormals3fPtr::dcast(geoPtr->getNormals());
        if(normalsPtr == NullFC)
        {
            normalsPtr = GeoNormals3f::create();
            geoPtr->setNormals(normalsPtr);
        }
        beginEditCP(normalsPtr, GeoNormals3f::GeoPropDataFieldMask);
        normalsPtr->clear();
        geoPtr->editMFIndexMapping()->push_back(Geometry::MapNormal);
    }
    else
        geoPtr->setNormals(NullFC);
	// Initialise and clear indices
    GeoPLengthsUI32Ptr lensPtr = GeoPLengthsUI32Ptr::dcast(geoPtr->getLengths());
    if(lensPtr == NullFC)
    {
        lensPtr = GeoPLengthsUI32::create();
        geoPtr->setLengths(lensPtr);
    }
    beginEditCP(lensPtr, GeoPLengthsUI32::GeoPropDataFieldMask);
    lensPtr->clear();
    GeoIndicesUI32Ptr indicesPtr = GeoIndicesUI32Ptr::dcast(geoPtr->getIndices());
    if(indicesPtr == NullFC)
    {
        indicesPtr = GeoIndicesUI32::create();
        geoPtr->setIndices(indicesPtr);
    }
    beginEditCP(indicesPtr, GeoIndicesUI32::GeoPropDataFieldMask);
    indicesPtr->clear();
    GeoPTypesUI8Ptr typesPtr = GeoPTypesUI8Ptr::dcast(geoPtr->getTypes());
    if(typesPtr == NullFC)
    {
        typesPtr = GeoPTypesUI8::create();
        geoPtr->setTypes(typesPtr);
    }
    beginEditCP(typesPtr, GeoPTypesUI8::GeoPropDataFieldMask);
    typesPtr->clear();
    // Clear unused properties
    geoPtr->setColors(NullFC);
    geoPtr->setSecondaryColors(NullFC);
    geoPtr->setTexCoords1(NullFC);
    geoPtr->setTexCoords2(NullFC);
    geoPtr->setTexCoords3(NullFC);
    geoPtr->setTexCoords4(NullFC);
    geoPtr->setTexCoords5(NullFC);
    geoPtr->setTexCoords6(NullFC);
    geoPtr->setTexCoords7(NullFC);

    // determine whether the spine is closed
    _spineClosed = _spine.back() == _spine.front();
    UInt32 spineSize = _spine.size();
    UInt32 height = spineSize;
    if(_spineClosed == true)
        --height;
    // determine whether the cross section is closed
    _crossSectionClosed = _crossSection.back() == _crossSection.front();
    UInt32 crossSectionSize = _crossSection.size();
    UInt32 width = crossSectionSize;
    if(_crossSectionClosed == true)
        --width;

    // do some sanity checks on the _spine and _crossSection member fields
    if((width < 2) || (height < 1))
    {
        endEditCP(posPtr, GeoPositions3f::GeoPropDataFieldMask);
        if(_createTexCoords == true)
            endEditCP(texPtr, GeoTexCoords2f::GeoPropDataFieldMask);
        if(_createNormals == true)
            endEditCP(normalsPtr, GeoNormals3f::GeoPropDataFieldMask);
        endEditCP(indicesPtr, GeoIndicesUI32::GeoPropDataFieldMask);
        endEditCP(lensPtr, GeoPLengthsUI32::GeoPropDataFieldMask);
        endEditCP(typesPtr, GeoPTypesUI8::GeoPropDataFieldMask);
        endEditCP(geoPtr);
        return;
    }

    // compute transformation matrices
    if(_cp2scp.empty() == true)
    {
        calcTransforms();
    }
    if(_transform.empty() == true)
    {
        _transform.reserve(spineSize);
        UInt32 orientationSize = _orientation.size();
        UInt32 scaleSize = _scale.size();
        for(UInt32 i = 0; i < spineSize; ++i)
        {
            // Get the CP to SCP transformation
            Matrix m = _cp2scp[i];

            // Apply the orientation
            if(i >= orientationSize)
            {
                if(orientationSize > 0)
                {
                    Matrix rotation;
                    rotation.setRotate(_orientation.back());
                    m.mult(rotation);
                }
            }
            else
            {
                Matrix rotation;
                rotation.setRotate(_orientation[i]);
                m.mult(rotation);
            }

            // Scale cross section
            if(i >= scaleSize)
            {
                if(scaleSize > 0)
                {
                    const Vec2f &scale = _scale.back();
                    Matrix scaleMat;
                    scaleMat.setScale(scale.x(), 1, scale.y());
                    m.mult(scaleMat);
                }
            }
            else
            {
                const Vec2f &scale = _scale[i];
                Matrix scaleMat;
                scaleMat.setScale(scale.x(), 1, scale.y());
                m.mult(scaleMat);
            }

            _transform.push_back(m);
        }
    }

    // Create the geometry for the begin and the end cap
    if(((_beginCap == true) || (_endCap == true)) && (_crossSectionTypes.empty() == true))
    {
        // Determine whether the orientation of the cross section is clockwise
        // or counterclockwise. Do this, we calculate the area of the polygon.
        // The sign of the area determines the orientation.
        Real32 area = 0;
        for(UInt32 i = 1; i < width; ++i)
        {
            const Pnt2f &p1 = _crossSection[i - 1];
            const Pnt2f &p2 = _crossSection[i];
            area += (p1.x() - p2.x()) * (p1.y() + p2.y());
        }
        const Pnt2f &p1 = _crossSection[width - 1];
        const Pnt2f &p2 = _crossSection[0];
        area += (p1.x() - p2.x()) * (p1.y() + p2.y());
        _crossSectionCcw = area < 0;

        // Triangulate cross section when it is concave
        if(_convex == false)
        {
            if(_tess == 0)
            {
                // Create a new GLU tesselator object
                _tess = gluNewTess();
                // hint to the GLU tesselator that all points lie in the xz-plane
                gluTessNormal(_tess, 0.0, 1.0, 0.0);
                // set the winding rule
                gluTessProperty(_tess, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_ODD);

                // register GLU Tesselator callback methods
                gluTessCallback(_tess,
                                GLU_TESS_BEGIN_DATA,
                                reinterpret_cast<OSGGLUfuncptr>(gluTessBeginDataCB));
                gluTessCallback(_tess,
                                GLU_TESS_END_DATA,
                                reinterpret_cast<OSGGLUfuncptr>(gluTessEndDataCB));
                gluTessCallback(_tess,
                                GLU_TESS_VERTEX_DATA,
                                reinterpret_cast<OSGGLUfuncptr>(gluTessVertexDataCB));
            }
            if(_tess != 0)
            {
                // make shared data structure available to callbacks */
                gluTessBeginPolygon(_tess, this);
                // begin new contour
                gluTessBeginContour(_tess);

                for(UInt32 i = 0; i < width; ++i)
                {
                    const Pnt2f &p = _crossSection[i];
                    GLdouble coords[3];
                    coords[0] = p.x();
                    coords[1] = 0.f;
                    coords[2] = p.y();
                    gluTessVertex(_tess, coords, reinterpret_cast<void*>(i));
                }

                // end of contour
                gluTessEndContour(_tess);
                // trigger tesselator action
                gluTessEndPolygon(_tess);

                // Adjust lengths
                for(UInt32 i = _crossSectionLengths.size() - 1; i > 0; --i)
                    _crossSectionLengths[i] -= _crossSectionLengths[i - 1];
            }
        }
        // Fallback - when the cross section is convex or when the triangulation
        // fails, simply create a polygon
        if(_crossSectionTypes.empty() == true)
        {
            _crossSectionTypes.push_back(GL_POLYGON);
            _crossSectionLengths.push_back(width);
            if(_crossSectionCcw == true)
                for(UInt32 i = 0; i < width; ++i)
                    _crossSectionIndices.push_back(i);
            else
                for(Int32 i = width - 1; i >= 0; --i)
                    _crossSectionIndices.push_back(i);
        }
    }

    // Calculate points
    UInt32 numPoints = height * crossSectionSize;
    MFPnt3f &posField = posPtr->editField();
    posField.reserve(numPoints);
    // iterate over the spine points
    for(UInt32 i = 0; i < height; ++i)
    {
        const Matrix &m = _transform[i];
        // iterate over the cross-section curve
        for(UInt32 j = 0; j < crossSectionSize; ++j)
        {
            // Transform 2d cross section point to 3d point on
            // the y=0 plane
            const Pnt2f &p2d = _crossSection[j];
            Pnt3f p3d(p2d.x(), 0.f, p2d.y());

            // apply transformation
            m.mult(p3d, p3d);

            posField.push_back(p3d);
        }
    }

    // Create texture coordinates
    if(_createTexCoords == true)
    {
        UInt32 numTexCoords = height < 2 ? 0 : numPoints;
        if((_beginCap == true) || (_endCap == true))
            numTexCoords += crossSectionSize;
        MFVec2f &texField = texPtr->editField();
        texField.reserve(numTexCoords);
        if(height >= 2)
        {
            // Calculate distances in u and v directions
            UInt32 index = 0, prevIndexX = (UInt32)-1, prevIndexY = -crossSectionSize;
            for(UInt32 i = 0; i < spineSize; ++i)
            {
                if(i >= height)
                {
                    index = 0;
                    prevIndexX = (UInt32)-1;
                }
                for(UInt32 j = 0; j < crossSectionSize; ++j)
                {
                    const Pnt3f &currentPos = posField[index++];
                    Real32 u = j == 0 ? 0.f : texField[prevIndexX].x() + posField[prevIndexX].dist(currentPos);
                    Real32 v = i == 0 ? 0.f : texField[prevIndexY].y() + posField[prevIndexY].dist(currentPos);
                    texField.push_back(Vec2f(u, v));
                    ++prevIndexX; ++prevIndexY;
                }
            }
            // Normalise texture coordinates
            index = 0;
            UInt32 lastIndexX = crossSectionSize - 1;
            for(UInt32 i = 0; i < spineSize; ++i)
            {
                UInt32 lastIndexY = crossSectionSize * (spineSize - 1);
                for(UInt32 j = 0; j < crossSectionSize; ++j)
                {
                    Vec2f &v = texField[index];
                    Real32 uMax = texField[lastIndexX].x();
                    if(uMax > Eps)
                        v[0] /= uMax;
                    Real32 vMax = texField[lastIndexY].y();
                    if(vMax > Eps)
                        v[1] /= vMax;
                    ++index;
                    ++lastIndexY;
                }
                lastIndexX += crossSectionSize;
            }
        }
        if((_beginCap == true) || (_endCap == true))
        {
            // Calculate bounding box of the cross section
            Pnt2f bbmin = _crossSection[0];
            Pnt2f bbmax = bbmin;
            for(UInt32 i = 1; i < width; ++i)
            {
                const Pnt2f &p = _crossSection[i];
                if(p[0] < bbmin[0])
                    bbmin[0] = p[0];
                if(p[1] < bbmin[1])
                    bbmin[1] = p[1];
                if(p[0] > bbmax[0])
                    bbmax[0] = p[0];
                if(p[1] > bbmax[1])
                    bbmax[1] = p[1];
            }
            Vec2f size = bbmax - bbmin;
            Real32 texScale = osgMax(size.x(), size.y());
            // Calculate texture coordinates for the caps
            for(UInt32 i = 0; i < width; ++i)
            {
                Pnt2f p = _crossSection[i];
                p -= bbmin;
                p /= texScale;
                texField.push_back(p);
            }
        }
    }

    // Create normals
    UInt32 numFacesPerCrossSection = (crossSectionSize - 1) * 2;
    if((_createNormals == true) && (height >= 2))
    {
        // Calculate face normals
        Vec3f v1, v2, n;
        UInt32 numFaces = (spineSize - 1) * numFacesPerCrossSection;
        _faceNormals.clear();
        _faceNormals.reserve(numFaces);
        UInt32 index = crossSectionSize, prevIndex = 0;
        for(UInt32 i = 1; i < spineSize; ++i)
        {
            if(i >= height)
                index = 0;
            v1 = posField[index] - posField[prevIndex];
            for(UInt32 j = 1; j < crossSectionSize; ++j)
            {
                ++index;
                v2 = posField[index] - posField[prevIndex];
                n = v2.cross(v1); n.normalize();
                _faceNormals.push_back(n);

                ++prevIndex;
                v1 = posField[index] - posField[prevIndex];
                n = v2.cross(v1); n.normalize();
                _faceNormals.push_back(n);
            }
            ++index; ++prevIndex;
        }

        // Sum up normals
        MFVec3f &normalsField = normalsPtr->editField();
        UInt32 faceIndex = 0, normalIndex = 0;
        UInt32 numNormals = numFaces * 3;
        normalsField.resize(numNormals);
        UInt32 numNormalsPerCrossSection = numFacesPerCrossSection * 3;
        for(UInt32 i = 1; i < spineSize; ++i)
        {
            for(UInt32 j = 1; j < crossSectionSize; ++j)
            {
                UInt32 faceIndexRight = faceIndex + 2;
                UInt32 normalIndexRight = normalIndex + 6;
                UInt32 faceIndexUp = faceIndex + numFacesPerCrossSection;
                UInt32 normalIndexUp = normalIndex + numNormalsPerCrossSection;
                UInt32 faceIndexUpRight = faceIndex + numFacesPerCrossSection + 2;
                UInt32 normalIndexUpRight = normalIndex + numNormalsPerCrossSection + 6;
                if(j >= crossSectionSize - 1)
                {
                    faceIndexRight -= numFacesPerCrossSection;
                    normalIndexRight -= numNormalsPerCrossSection;
                    faceIndexUpRight -= numFacesPerCrossSection;
                    normalIndexUpRight -= numNormalsPerCrossSection;
                }
                if(i >= spineSize - 1)
                {
                    faceIndexUp -= numFaces;
                    normalIndexUp -= numNormals;
                    faceIndexUpRight -= numFaces;
                    normalIndexUpRight -= numNormals;
                }

                // First (lower left) quadrant
                normalsField[normalIndex    ] += _faceNormals[faceIndex];
                normalsField[normalIndex + 1] += _faceNormals[faceIndex];
                normalsField[normalIndex + 2] += _faceNormals[faceIndex];
                normalsField[normalIndex + 3] += _faceNormals[faceIndex + 1];
                normalsField[normalIndex + 4] += _faceNormals[faceIndex + 1];
                normalsField[normalIndex + 5] += _faceNormals[faceIndex + 1];
                if(_faceNormals[faceIndex].dot(_faceNormals[faceIndex + 1]) > _cosCreaseAngle)
                {
                    normalsField[normalIndex + 1] += _faceNormals[faceIndex + 1];
                    normalsField[normalIndex + 2] += _faceNormals[faceIndex + 1];
                    normalsField[normalIndex + 3] += _faceNormals[faceIndex];
                    normalsField[normalIndex + 5] += _faceNormals[faceIndex];
                }

                // Second (lower right) quadrant
                if((j < crossSectionSize - 1) || (_crossSectionClosed == true))
                {
                    if(_faceNormals[faceIndex].dot(_faceNormals[faceIndexRight]) > _cosCreaseAngle)
                    {
                        normalsField[normalIndex + 2] += _faceNormals[faceIndexRight];
                        normalsField[normalIndexRight] += _faceNormals[faceIndex];
                    }
                    if(_faceNormals[faceIndex + 1].dot(_faceNormals[faceIndexRight]) > _cosCreaseAngle)
                    {
                        normalsField[normalIndex + 4] += _faceNormals[faceIndexRight];
                        normalsField[normalIndex + 5] += _faceNormals[faceIndexRight];
                        normalsField[normalIndexRight] += _faceNormals[faceIndex + 1];
                        normalsField[normalIndexRight + 1] += _faceNormals[faceIndex + 1];
                    }
                    if(_faceNormals[faceIndex + 1].dot(_faceNormals[faceIndexRight + 1]) > _cosCreaseAngle)
                    {
                        normalsField[normalIndex + 4] += _faceNormals[faceIndexRight + 1];
                        normalsField[normalIndexRight + 3] += _faceNormals[faceIndex + 1];
                    }
                }

                // Third (upper left) quadrant
                if((i < spineSize - 1) || (_spineClosed == true))
                {
                    if(_faceNormals[faceIndex].dot(_faceNormals[faceIndexUp]) > _cosCreaseAngle)
                    {
                        normalsField[normalIndex] += _faceNormals[faceIndexUp];
                        normalsField[normalIndexUp + 1] += _faceNormals[faceIndex];
                    }
                    if(_faceNormals[faceIndex].dot(_faceNormals[faceIndexUp + 1]) > _cosCreaseAngle)
                    {
                        normalsField[normalIndex] += _faceNormals[faceIndexUp + 1];
                        normalsField[normalIndex + 2] += _faceNormals[faceIndexUp + 1];
                        normalsField[normalIndexUp + 3] += _faceNormals[faceIndex];
                        normalsField[normalIndexUp + 4] += _faceNormals[faceIndex];
                    }
                    if(_faceNormals[faceIndex + 1].dot(_faceNormals[faceIndexUp + 1]) > _cosCreaseAngle)
                    {
                        normalsField[normalIndex + 5] += _faceNormals[faceIndexUp + 1];
                        normalsField[normalIndexUp + 4] += _faceNormals[faceIndex + 1];
                    }
                }

                // Fourth (upper right) quadrant
                if(((j < crossSectionSize - 1) || (_crossSectionClosed == true)) && ((i < spineSize - 1) || (_spineClosed == true)))
                {
                    if(_faceNormals[faceIndex].dot(_faceNormals[faceIndexUpRight]) > _cosCreaseAngle)
                    {
                        normalsField[normalIndex + 2] += _faceNormals[faceIndexUpRight];
                        normalsField[normalIndexUpRight + 1] += _faceNormals[faceIndex];
                    }
                    if(_faceNormals[faceIndex].dot(_faceNormals[faceIndexUpRight + 1]) > _cosCreaseAngle)
                    {
                        normalsField[normalIndex + 2] += _faceNormals[faceIndexUpRight + 1];
                        normalsField[normalIndexUpRight + 3] += _faceNormals[faceIndex];
                    }
                    if(_faceNormals[faceIndex + 1].dot(_faceNormals[faceIndexUpRight]) > _cosCreaseAngle)
                    {
                        normalsField[normalIndex + 5] += _faceNormals[faceIndexUpRight];
                        normalsField[normalIndexUpRight + 1] += _faceNormals[faceIndex + 1];
                    }
                    if(_faceNormals[faceIndex + 1].dot(_faceNormals[faceIndexUpRight + 1]) > _cosCreaseAngle)
                    {
                        normalsField[normalIndex + 5] += _faceNormals[faceIndexUpRight + 1];
                        normalsField[normalIndexUpRight + 3] += _faceNormals[faceIndex + 1];
                    }


                    if(_faceNormals[faceIndexRight].dot(_faceNormals[faceIndexUp + 1]) > _cosCreaseAngle)
                    {
                        normalsField[normalIndexRight] += _faceNormals[faceIndexUp + 1];
                        normalsField[normalIndexUp + 4] += _faceNormals[faceIndexRight];
                    }
                }

                faceIndex += 2;
                normalIndex += 6;
            }
        }

        // Normalize normals
        for(UInt32 i = 0; i < numNormals; ++i)
            normalsField[i].normalize();
    }

    // Create types, lengths and indices
    MFVec3f *normalsField = 0;
    if(_createNormals == true)
        normalsField = &(normalsPtr->editField());
    MFUInt8 &typesField = typesPtr->editField();
    MFUInt32 &lensField = lensPtr->editField();
    UInt32 index = crossSectionSize, prevIndex = 0;
    UInt32 texCoordIndex = crossSectionSize, prevTexCoordIndex = 0;
    UInt32 normalIndex = 0;
    if(height >= 2)
    {
        for(UInt32 i = 1; i < spineSize; ++i)
        {
            if(i >= height)
                index = 0;
            UInt32 len = 0;
            for(UInt32 j = 0; j < numFacesPerCrossSection; )
            {
                // First of all, check how many consecutive triangles share their normals
                len = 1;
                UInt32 normalIndex2 = normalIndex;
                for(UInt32 k = j + 1; k < numFacesPerCrossSection; ++k)
                {
                    if((k & 1) == 0)
                    {
                        if(((*normalsField)[normalIndex2 + 1] != (*normalsField)[normalIndex2 + 4]) ||
                            ((*normalsField)[normalIndex2 + 2] != (*normalsField)[normalIndex2 + 3]))
                            break;
                    }
                    else
                    {
                        if(((*normalsField)[normalIndex2 + 1] != (*normalsField)[normalIndex2 + 3]) ||
                            ((*normalsField)[normalIndex2 + 2] != (*normalsField)[normalIndex2 + 5]))
                            break;
                    }
                    ++len;
                    normalIndex2 += 3;
                }
                if(len > 1)
                {
                    // At least two consecutive triangles share their normals, therefore
                    // we create a triangle strip
                    typesField.push_back(GL_TRIANGLE_STRIP);
                    if((j & 1) != 0)
                    {
                        indicesPtr->push_back(prevIndex);
                        if(_createTexCoords == true)
                            indicesPtr->push_back(prevTexCoordIndex);
                        if(_createNormals == true)
                            indicesPtr->push_back(normalIndex);
                        indicesPtr->push_back(prevIndex);
                        if(_createTexCoords == true)
                            indicesPtr->push_back(prevTexCoordIndex);
                        if(_createNormals == true)
                            indicesPtr->push_back(normalIndex);
                        indicesPtr->push_back(index);
                        if(_createTexCoords == true)
                            indicesPtr->push_back(texCoordIndex);
                        if(_createNormals == true)
                            indicesPtr->push_back(normalIndex + 2);
                        lensField.push_back(len + 3);
                    }
                    else
                    {
                        indicesPtr->push_back(index);
                        if(_createTexCoords == true)
                            indicesPtr->push_back(texCoordIndex);
                        if(_createNormals == true)
                            indicesPtr->push_back(normalIndex);
                        indicesPtr->push_back(prevIndex);
                        if(_createTexCoords == true)
                            indicesPtr->push_back(prevTexCoordIndex);
                        if(_createNormals == true)
                            indicesPtr->push_back(normalIndex + 1);
                        lensField.push_back(len + 2);
                    }
                    for(; len > 0; --len)
                    {
                        if((j & 1) == 0)
                        {
                            ++index; ++texCoordIndex;
                            indicesPtr->push_back(index);
                            if(_createTexCoords == true)
                                indicesPtr->push_back(texCoordIndex);
                            if(_createNormals == true)
                                indicesPtr->push_back(normalIndex + 2);
                        }
                        else
                        {
                            ++prevIndex; ++prevTexCoordIndex;
                            indicesPtr->push_back(prevIndex);
                            if(_createTexCoords == true)
                                indicesPtr->push_back(prevTexCoordIndex);
                            if(_createNormals == true)
                                indicesPtr->push_back(normalIndex + 1);
                        }
                        normalIndex += 3;
                        ++j;
                    }
                }
                else
                {
                    // The next triangle does not share normals with the following triangle,
                    // therefore we have to add a single triangle. When the previous triangle
                    // also is a single triangle, we can combine both into the same GL
                    // primitive.
                    if((typesField.empty() == false) && (typesField.back() == GL_TRIANGLES))
                    {
                        lensField.back() += 3;
                    }
                    else
                    {
                        typesField.push_back(GL_TRIANGLES);
                        lensField.push_back(3);
                    }
                    if((j & 1) == 0)
                    {
                        indicesPtr->push_back(index);
                        if(_createTexCoords == true)
                            indicesPtr->push_back(texCoordIndex);
                        if(_createNormals == true)
                            indicesPtr->push_back(normalIndex++);
                        indicesPtr->push_back(prevIndex);
                        if(_createTexCoords == true)
                            indicesPtr->push_back(prevTexCoordIndex);
                        if(_createNormals == true)
                            indicesPtr->push_back(normalIndex++);
                        ++index; ++texCoordIndex;
                        indicesPtr->push_back(index);
                        if(_createTexCoords == true)
                            indicesPtr->push_back(texCoordIndex);
                        if(_createNormals == true)
                            indicesPtr->push_back(normalIndex++);
                    }
                    else
                    {
                        indicesPtr->push_back(prevIndex);
                        if(_createTexCoords == true)
                            indicesPtr->push_back(prevTexCoordIndex);
                        if(_createNormals == true)
                            indicesPtr->push_back(normalIndex++);
                        ++prevIndex; ++prevTexCoordIndex;
                        indicesPtr->push_back(prevIndex);
                        if(_createTexCoords == true)
                            indicesPtr->push_back(prevTexCoordIndex);
                        if(_createNormals == true)
                            indicesPtr->push_back(normalIndex++);
                        indicesPtr->push_back(index);
                        if(_createTexCoords == true)
                            indicesPtr->push_back(texCoordIndex);
                        if(_createNormals == true)
                            indicesPtr->push_back(normalIndex++);
                    }
                    ++j;
                }
            }
            ++index; ++prevIndex;
            ++texCoordIndex; ++prevTexCoordIndex;
        }
    }
    bool flippedBeginCap = (_beginCap == true) && (_crossSectionCcw == true);
    bool flippedEndCap = (_endCap == true) && (_crossSectionCcw == false);
    if((flippedBeginCap == true) || (flippedEndCap == true))
    {
        if(_createNormals == true)
        {
            Vec3f capNormal = _transform[flippedBeginCap == true ? 0 : spineSize - 1][1];
            capNormal.negate();
            normalIndex = normalsPtr->size();
            normalsPtr->push_back(capNormal);
        }
        // We have to flip all triangles to enable correct backface culling.
        // For GL_TRIANGLES, we simply flip the vertices.
        // For GL_TRIANGLE_FANs, we leave the first vertex at its place and flip the
        // remaining vertices.
        // For GL_TRIANGLE_STRIPs, things are more complicated. When the number of
        // vertices is uneven, we simply flip the vertices. When the number of
        // vertices is even, we have to add an additional vertex before we flip the
        // vertices.
        UInt32 indexOffset = (flippedBeginCap == true) || (_spineClosed == true) ? 0 : numPoints - crossSectionSize;
        UInt32 texCoordIndexOffset = height < 2 ? 0 : numPoints;
        UInt32 indexBegin = 0, indexEnd;
        for(UInt32 i = 0; i < _crossSectionTypes.size(); ++i)
        {
            UInt8 type = _crossSectionTypes[i];
            typesField.push_back(type);
            UInt32 len = _crossSectionLengths[i];
            indexEnd = indexBegin + len;
            UInt32 index = indexEnd;
            if(type == GL_TRIANGLE_FAN)
            {
                index = indexBegin;
                ++indexBegin;
            }
            if((type == GL_TRIANGLE_STRIP) && ((len & 1) == 0))
            {
                assert((indexEnd >= 2) && (indexEnd - 2 >= indexBegin));
                index = indexEnd - 2;
                ++len;
            }
            if(index != indexEnd)
            {
                indicesPtr->push_back(_crossSectionIndices[index] + indexOffset);
                if(_createTexCoords == true)
                    indicesPtr->push_back(_crossSectionIndices[index] + texCoordIndexOffset);
                if(_createNormals == true)
                    indicesPtr->push_back(normalIndex);
                index = indexEnd;
            }
            lensField.push_back(len);
            while (true)
            {
                if(index <= indexBegin)
                    break;
                --index;
                indicesPtr->push_back(_crossSectionIndices[index] + indexOffset);
                if(_createTexCoords == true)
                    indicesPtr->push_back(_crossSectionIndices[index] + texCoordIndexOffset);
                if(_createNormals == true)
                    indicesPtr->push_back(normalIndex);
            }
            indexBegin = indexEnd;
        }
    }
    bool unflippedBeginCap = (_beginCap == true) && (_crossSectionCcw == false);
    bool unflippedEndCap = (_endCap == true) && (_crossSectionCcw == true);
    if((unflippedBeginCap == true) || (unflippedEndCap == true))
    {
        if(_createNormals == true)
        {
            Vec3f capNormal = _transform[flippedBeginCap == true ? 0 : spineSize - 1][1];
            normalIndex = normalsPtr->size();
            normalsPtr->push_back(capNormal);
        }
        typesField.getValues().insert(typesField.end(), _crossSectionTypes.begin(), _crossSectionTypes.end());
        lensField.getValues().insert(lensField.end(), _crossSectionLengths.begin(), _crossSectionLengths.end());
        UInt32 indexOffset = (unflippedBeginCap == true) || (_spineClosed == true) ? 0 : numPoints - crossSectionSize;
        UInt32 texCoordIndexOffset = height < 2 ? 0 : numPoints;
        for(UInt32 i = 0; i < _crossSectionIndices.size(); ++i)
        {
            indicesPtr->push_back(_crossSectionIndices[i] + indexOffset);
            if(_createTexCoords == true)
                indicesPtr->push_back(_crossSectionIndices[i] + texCoordIndexOffset);
            if(_createNormals == true)
                indicesPtr->push_back(normalIndex);
        }
    }

// Disabled for now because it is too expensive.
#if 0
    // Squeeze unused normals out of the normal vec
    if(_createNormals == true)
    {
        UInt32 stride = 2;
        if(_createTexCoords == true)
            ++stride;
        MFUInt32 &indicesField = indicesPtr->editField();
        MFVec3f &normalsField = normalsPtr->editField();
        UInt32 numNormals = 0;
        for(UInt32 i = stride - 1; i < indicesField.size(); i += stride)
        {
            UInt32 index = indicesField[i];
            if(index >= numNormals)
            {
                if(index > numNormals)
                {
                    Vec3f n = normalsField[numNormals];
                    normalsField[numNormals] = normalsField[index];
                    normalsField[index] = n;
                    for(UInt32 j = i; j < indicesField.size(); j += stride)
                    {
                        if(indicesField[j] == numNormals)
                            indicesField[j] = index;
                        else if(indicesField[j] == index)
                            indicesField[j] = numNormals;
                    }
                }
                ++numNormals;
            }
        }
        normalsField.resize(numNormals);
    }
#endif

    endEditCP(posPtr, GeoPositions3f::GeoPropDataFieldMask);
    if(_createTexCoords == true)
        endEditCP(texPtr, GeoTexCoords2f::GeoPropDataFieldMask);
    if(_createNormals == true)
        endEditCP(normalsPtr, GeoNormals3f::GeoPropDataFieldMask);
    endEditCP(indicesPtr, GeoIndicesUI32::GeoPropDataFieldMask);
    endEditCP(lensPtr, GeoPLengthsUI32::GeoPropDataFieldMask);
    endEditCP(typesPtr, GeoPTypesUI8::GeoPropDataFieldMask);
    endEditCP(geoPtr);
}


//-----------------------------------------------------------------------------
// Helper function that creates a node ptr with an extrusion geometry
//-----------------------------------------------------------------------------
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


//-----------------------------------------------------------------------------
// Helper function that creates an extrusion geometry
//-----------------------------------------------------------------------------
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
