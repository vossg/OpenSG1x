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


#include "OSGConfig.h"
#include "OSGLog.h"
#include "OSGExtrusionGeometry.h"


OSG_BEGIN_NAMESPACE


//-----------------------------------------------------------------------------
// Sets the cross section.
//-----------------------------------------------------------------------------
inline void ExtrusionSurface::setCrossSection(const std::vector<Pnt2f> &crossSection)
{
    editCrossSection() = crossSection;
}


//-----------------------------------------------------------------------------
// Returns the cross section.
//-----------------------------------------------------------------------------
inline const std::vector<Pnt2f> &ExtrusionSurface::getCrossSection() const
{
    return _crossSection;
}


//-----------------------------------------------------------------------------
// Sets the orientation.
//-----------------------------------------------------------------------------
inline void ExtrusionSurface::setOrientation(const std::vector<Quaternion> &orientation)
{
    editOrientation() = orientation;
}


//-----------------------------------------------------------------------------
// Returns the orientation.
//-----------------------------------------------------------------------------
inline const std::vector<Quaternion> &ExtrusionSurface::getOrientation() const
{
    return _orientation;
}


//-----------------------------------------------------------------------------
// Sets the scale.
//-----------------------------------------------------------------------------
inline void ExtrusionSurface::setScale(const std::vector<Vec2f> &scale)
{
    editScale() = scale;
}


//-----------------------------------------------------------------------------
// Returns the scale.
//-----------------------------------------------------------------------------
inline const std::vector<Vec2f> &ExtrusionSurface::getScale() const
{
    return _scale;
}


//-----------------------------------------------------------------------------
// Sets the spine.
//-----------------------------------------------------------------------------
inline void ExtrusionSurface::setSpine(const std::vector<Pnt3f> &spine)
{
    editSpine() = spine;
}


//-----------------------------------------------------------------------------
// Returns the spine.
//-----------------------------------------------------------------------------
inline const std::vector<Pnt3f> &ExtrusionSurface::getSpine() const
{
    return _spine;
}


//-----------------------------------------------------------------------------
// Sets the crease angle.
//-----------------------------------------------------------------------------
inline void ExtrusionSurface::setCreaseAngle(Real32 creaseAngle)
{
    _creaseAngle = creaseAngle;
    _cosCreaseAngle = osgcos(creaseAngle);
}


//-----------------------------------------------------------------------------
// Returns the crease angle.
//-----------------------------------------------------------------------------
inline Real32 ExtrusionSurface::getCreaseAngle() const
{
    return _creaseAngle;
}


//-----------------------------------------------------------------------------
// Switches the cap at the beginning on or off.
//-----------------------------------------------------------------------------
inline void ExtrusionSurface::setBeginCap(bool beginCap)
{
    _beginCap = beginCap;
}


//-----------------------------------------------------------------------------
// Returns whether to draw a cap at the beginning.
//-----------------------------------------------------------------------------
inline bool ExtrusionSurface::getBeginCap() const
{
    return _beginCap;
}


//-----------------------------------------------------------------------------
// Switches the cap at the end on or off.
//-----------------------------------------------------------------------------
inline void ExtrusionSurface::setEndCap(bool endCap)
{
    _endCap = endCap;
}


//-----------------------------------------------------------------------------
// Returns whether to draw a cap at the end.
//-----------------------------------------------------------------------------
inline bool ExtrusionSurface::getEndCap() const
{
    return _endCap;
}


//-----------------------------------------------------------------------------
// Sets the vertex order of faces.
//-----------------------------------------------------------------------------
inline void ExtrusionSurface::setCcw(bool ccw)
{
    _ccw = ccw;
}


//-----------------------------------------------------------------------------
// Returns the vertex order of faces.
//-----------------------------------------------------------------------------
inline bool ExtrusionSurface::getCcw() const
{
    return _ccw;
}


//-----------------------------------------------------------------------------
// Sets whether the cross section is convex.
//-----------------------------------------------------------------------------
inline void ExtrusionSurface::setConvex(bool convex)
{
    _convex = convex;
}


//-----------------------------------------------------------------------------
// Returns whether the cross section is convex.
//-----------------------------------------------------------------------------
inline bool ExtrusionSurface::getConvex() const
{
    return _convex;
}


//-----------------------------------------------------------------------------
// Switches normal generation on or off.
//-----------------------------------------------------------------------------
inline void ExtrusionSurface::setBuildNormal(bool buildNormal)
{
    _createNormals = buildNormal;
}


//-----------------------------------------------------------------------------
// Returns whether normals should be generated.
//-----------------------------------------------------------------------------
inline bool ExtrusionSurface::getBuildNormal() const
{
    return _createNormals;
}


//-----------------------------------------------------------------------------
// Switches texture coordinate generation on or off.
//-----------------------------------------------------------------------------
inline void ExtrusionSurface::setBuildTexCoord(bool buildTexCoord)
{
    _createTexCoords = buildTexCoord;
}


//-----------------------------------------------------------------------------
// Returns whether texture coordinates should be generated.
//-----------------------------------------------------------------------------
inline bool ExtrusionSurface::getBuildTexCoord() const
{
    return _createTexCoords;
}


//-----------------------------------------------------------------------------
//                     CP to SCP Transformation Helpers                        
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Returns a pair of iterators pointing to spine[i-1] and spine[i+1] depending
// on the topology of the spine. If the spine is closed, iterators are wrapped
// around at the ends. If the spine is open, iterators are saturated at the
// ends, i.e. the -1-th spine element is equal to the 0-th and the n-th is
// equal to the (n-1)-th.
//
// Author: afischle
//-----------------------------------------------------------------------------
inline ExtrusionSurface::Pnt3fConstItPair 
ExtrusionSurface::getPrevAndNextIt(const Pnt3fConstIt &pIt)
{
    Pnt3fConstIt prevIt, nextIt;
    bool firstPoint = (pIt == _spine.begin()) ? true : false;
    bool lastPoint  = (pIt == _spine.end() - 1) ? true : false;

    if(!firstPoint && !lastPoint)   // it's an interior point
    {
        prevIt = pIt - 1;
        nextIt = pIt + 1;
    }
    else // either it's the first or the last point
    {
        if(_spineClosed)
        {
            prevIt = _spine.end() - 2;
            nextIt = _spine.begin() + 1;
        }
        else // spine is open
        {
            if(firstPoint)
            {
                prevIt = _spine.begin();
                nextIt = _spine.begin() + 1;
            }
            else // last point
            {
                prevIt = _spine.end() - 2;
                nextIt = _spine.end() - 1;
            }
        }
    }
    return Pnt3fConstItPair(prevIt, nextIt);
}


//-----------------------------------------------------------------------------
// Returns the non-normalized y-axis of a CP to SCP transform at pIt
// Author: afischle
//-----------------------------------------------------------------------------
inline Vec3f ExtrusionSurface::calcNonUnitYAxis(const Pnt3fConstIt &pIt)
{
    /* X3D Spec:
     *
     * a. For all points other than the first or last: The Y-axis for spine[i]
     *    is found by normalizing the vector defined by
     *    (spine[i+1] - spine[i-1]). 
     * b. If the spine curve is closed: The SCP for the first and last points
     *    is the same and is found using (spine[1] - spine[n-2]) to compute
     *    the Y-axis.
     * c. If the spine curve is not closed: The Y-axis used for the first point
     *    is the vector from spine[0] to spine[1], and for the last it is the 
     *    vector from spine[n-2] to spine[n-1].
     */

    Pnt3fConstItPair prevAndNextIt = getPrevAndNextIt(pIt);
    Vec3f yAxis = *(prevAndNextIt.second) - *(prevAndNextIt.first);
    return yAxis;
}


//-----------------------------------------------------------------------------
// Returns the non-normalized z-axis of a CP to SCP transform at pIt
// Author: afischle
//-----------------------------------------------------------------------------
inline Vec3f ExtrusionSurface::calcNonUnitZAxis(const Pnt3fConstIt &pIt)
{
    /* X3D Spec:
     *
     * The Z-axis is determined as follows:
     *
     * d.  For all points other than the first or last: Take the following 
     *     cross-product: Z = (spine[i+1] - spine[i]) x (spine[i-1] - spine[i])
     * e.  If the spine curve is closed: The SCP for the first and last points 
     *     is the same and is found by taking the following cross-product: 
     *     Z = (spine[1] - spine[0]) x (spine[n-2] - spine[0]) 
     * f.  If the spine curve is not closed: The Z-axis used for the first
     *     spine point is the same as the Z-axis for spine[1]. The Z-axis
     *     used for the last spine point is the same as the Z-axis for
     *     spine[n-2].
     * g.  After determining the Z-axis, its dot product with the Z-axis of
     *     the previous spine point is computed. If this value is negative,
     *     the Z-axis is flipped (multiplied by -1). In most cases,
     *     this prevents small changes in the spine segment angles from
     *     flipping the cross-section 180 degrees.
     */

    Pnt3fConstItPair prevAndNextIt = getPrevAndNextIt(pIt);
    Vec3f pToNext, pToPrev;
    pToNext = *(prevAndNextIt.second) - *pIt;
    pToPrev = *(prevAndNextIt.first) - *pIt;

    // If pIt points to the first or the last point the cross-product below
    // is zero because either pToNext or pToPrev is zero in this case.
    Vec3f zAxis = pToNext.cross(pToPrev);
    return zAxis;
}


//-----------------------------------------------------------------------------
// Returns the unit length x-axis of a CP to SCP transform as the cross product
// of the y- and z-axis stored in the matrix pointed to by mIt.
//
// Author: afischle
//-----------------------------------------------------------------------------
inline Vec3f ExtrusionSurface::calcXAxis(const MatrixConstIt &mIt)
{
    Vec3f yAxis((*mIt)[1]);
    Vec3f zAxis((*mIt)[2]);

    Vec3f xAxis = yAxis.cross(zAxis);
    xAxis.normalize();

    return xAxis;
}


OSG_END_NAMESPACE


#define OSGEXTRUSIONGEOMETRY_INLINE_CVSID "@(#)$Id: OSGExtrusionGeometry.inl,v 1.4 2009/02/23 18:59:22 pdaehne Exp $"
