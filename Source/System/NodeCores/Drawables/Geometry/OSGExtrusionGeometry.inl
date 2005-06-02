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

#include <sstream>

// #define DEBUG_SUBDIVISION
// #define DEBUG_VERTEX_STORE
// #define DEBUG_PROPERTY_STORE
#define DEBUG_PRIMITIVE_STORE

OSG_BEGIN_NAMESPACE


//-----------------------------------------------------------------------------
// Compare operator for vector types. Used to map properties with a
// distance (taken component-wise) of less than Eps to the same index.
//
// Author: jbehr, afischle (cut'n pasted from OSGGeoFunctions.cpp) 
//-----------------------------------------------------------------------------
template<class type>
inline bool ExtrusionSurface::vecless<type>::operator () (const type &a,
                                                          const type &b) const
{
    UInt32  i;
    bool    ret = false;
    for(i = 0; i < type::_iSize; i++)
    {
        if(osgabs(a[i] - b[i]) < Eps)
            continue;
        if(a[i] > b[i])
        {
            ret = false;
            break;
        }
        ret = true;
        break;
    }
    return ret;
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


//-----------------------------------------------------------------------------
//                            Subdivision schemes                              
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Returns an interpolated vector to be inserted between points b and c,
// obtained by applying the scheme (-1/16, 9/16, 9/16, -1/16)
//
// Author: afischle
//-----------------------------------------------------------------------------
template <class VectorTypeT> 
inline VectorTypeT 
apply4PtScheme(const typename std::vector<VectorTypeT>::const_iterator &a,
               const typename std::vector<VectorTypeT>::const_iterator &b,
               const typename std::vector<VectorTypeT>::const_iterator &c,
               const typename std::vector<VectorTypeT>::const_iterator &d)
{

#ifdef DEBUG_SUBDIVISION
     SLOG << "4ptScheme: interior: "
          << "( " << *a << " ) "
          << "(_" << *b << "_) " 
          << "( " << *c << " ) "
          << "( " << *d << " ) "
          << endl;
#endif

    // return the weighted sum of the four points (a,b,c,d)
    return (-1.f/16.f) * (*a) 
        + ( 9.f/16.f) * (*b) 
        + ( 9.f/16.f) * (*c) 
        + (-1.f/16.f) * (*d);
}


//-----------------------------------------------------------------------------
// Returns an interpolated vector to be inserted between points a and b,
// obtained by applying the scheme (3/8, 6/8, -1/8)
//
// Author: afischle
//-----------------------------------------------------------------------------
template <class VectorTypeT>
inline VectorTypeT 
apply3PtScheme(const typename std::vector<VectorTypeT>::const_iterator &a,
               const typename std::vector<VectorTypeT>::const_iterator &b,
               const typename std::vector<VectorTypeT>::const_iterator &c)
{

#ifdef DEBUG_SUBDIVISION    
     SLOG << "3PtScheme: exterior"
          << "( " << *a << " ) "
          << "(_" << *b << "_) " 
          << "( " << *c << " ) "
          << endl;
#endif

    // return the weighted sum of the three points (a,b,c)
    return ( 3.f/8.f) * (*a)
        + ( 6.f/8.f) * (*b)
        + (-1.f/8.f) * (*c);
}


//-----------------------------------------------------------------------------
//                        Normals calculation helpers                          
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Returns the right handed face normal of the triangle ABC if _ccw is true
// and the negated one if _ccw is false.
//
// Author: afischle
//-----------------------------------------------------------------------------
inline Vec3f ExtrusionSurface::calcTriangleFaceNormal(const Pnt3f &a,
                                                      const Pnt3f &b,
                                                      const Pnt3f &c)
{
    Vec3f d1 = b - a;
    Vec3f d2 = c - a;
    Vec3f faceNormal = _ccw ? d1.cross(d2) : d2.cross(d1);

    return faceNormal;
}

//-----------------------------------------------------------------------------
// Returns the right handed unit-length face normal of the quad ABCD if _ccw
// is true and the negated one if _ccw is false. If the four corners are not
// the boundary of a surface, the return value is 0.
//
// Author: afischle
//-----------------------------------------------------------------------------
inline Vec3f ExtrusionSurface::calcQuadFaceNormal(const Pnt3f &a,
                                                  const Pnt3f &b,
                                                  const Pnt3f &c,
                                                  const Pnt3f &d)
{
    Vec3f faceNormal = calcTriangleFaceNormal(a, b, d);
    if(faceNormal.length() > Eps)
    {
        faceNormal.normalize();
        return faceNormal;
    }

    faceNormal = calcTriangleFaceNormal(b, c, a);
    if(faceNormal.length() > Eps)
    {
        faceNormal.normalize();
        return faceNormal;
    }

    faceNormal = calcTriangleFaceNormal(c, d, b);
    if(faceNormal.length() > Eps)
    {
        faceNormal.normalize();
        return faceNormal;
    }

    // if we get here, the quad is completely degenerate and has no normal
    return Vec3f(0.f, 0.f, 0.f);
}


//-----------------------------------------------------------------------------
// Calculates the vertex normal of a corner of a quad face. The quadrant
// argument is used to deduce in which quadrant the quad lies from the point of
// view of the vertex. The admissible quadrant arguments are 0,1,2,3.
// The vertex normal is obtained by averaging all normals of adjacent faces
// enclosing an angle less than the _creaseAngle with the face located at
// the specified quadrant of the vertex.
//
// The result is stored in the normal component of the vertex pointed to by
// vPtr.
// 
// Author: afischle
//-----------------------------------------------------------------------------
inline void ExtrusionSurface::calcVertexNormal(Vertex *vPtr, UInt32 quadrant)
{
    assert(quadrant < 4);
    
    Vec3f refFN = vPtr->adjFaceNormals[quadrant];

    // set the vertex normal to the reference face normal
    vPtr->normal = refFN;    

    if(_creaseAngle < Eps)
    {   
        // we don't need to smooth across faces
        return;
    }

    // we need to smooth the normals
    for(UInt32 k = 0; k < 4; k++)
    {
        if(k != quadrant) // check the other 3 adjacent faces of the vertex 
        {
            Vec3f fN = vPtr->adjFaceNormals[k];
            if(refFN.enclosedAngle(fN) - Eps < _creaseAngle + Eps)
            {
                vPtr->normal += fN;
            }
        }
    }

    vPtr->normal.normalize();
}

//-----------------------------------------------------------------------------
//                          Geometry store helpers                             
//-----------------------------------------------------------------------------





//-----------------------------------------------------------------------------
// Determines indices for the position, normal and texCoord components of a
// vertex and stores them into the specified index field container. The indices
// are stored in the following order:
// 
//   1. position index
//   2. normal index (if _createNormals is true)
//   3. texCoord index (if _createTexCoords is true)
// 
// Author: afischle
//-----------------------------------------------------------------------------
inline void ExtrusionSurface::storeVertex(const Vertex &vertex, 
                                          const GeoIndicesUI32Ptr indicesPtr)
{
    assert(indicesPtr != NullFC);

#ifdef DEBUG_VERTEX_STORE
    std::ostringstream strout;
    strout << "OSGExtrusion:storeVertex:Storing:" << std::endl;
    strout << "\t[ (Pos: " << vertex.position << ")" << std::endl;
#endif
    
    // store position
    store(vertex.position, _posMap, indicesPtr);

    if(_createNormals)
    {
#ifdef DEBUG_VERTEX_STORE        
        strout << "\t  (Normal:" << vertex.normal << ")" << std::endl;
#endif
        // store normal
        store(vertex.normal, _normalMap, indicesPtr);
    }
    
    if(_createTexCoords)
    {
#ifdef DEBUG_VERTEX_STORE        
        strout << "\t  (TexCoord:" << vertex.texCoord << ")" << std::endl;
#endif
        // store texture coordinate
        store(vertex.texCoord, _texCoordMap, indicesPtr);
    }
    
    // increase the vertex count of the current primitive
    _vertexCount++;
    
#ifdef DEBUG_VERTEX_STORE        
    strout << "\t  (vc:" << _vertexCount << "/tvc:" << _totalVertexCount << ")]";
    SLOG << strout.str() << std::endl;
#endif
}


//-----------------------------------------------------------------------------
// Stores the number of vertices of the current primitive and its specified
// type into the specified field length and type field containers.
//
// Author: afischle
//-----------------------------------------------------------------------------
inline void ExtrusionSurface::storePrimitive(GLenum type, 
                                             GeoPLengthsUI32Ptr lensPtr, 
                                             GeoPTypesUI8Ptr    typesPtr)
{
    assert(lensPtr != NullFC);
    assert(typesPtr != NullFC);

#ifdef DEBUG_PRIMITIVE_STORE
    switch(type)
    {
        case GL_TRIANGLE_STRIP:
            assert(_vertexCount > 2);
            assert(_vertexCount % 2 == 0);
            break;

        case GL_TRIANGLE_FAN:
            assert(_vertexCount > 2);
            break;
            
        case GL_QUADS:
            assert(_vertexCount == 4);
            break;
            
        case GL_LINES:
            assert(_vertexCount == 2);
            break;
    };
#endif
    
    if(_vertexCount != 0)
    {
        lensPtr->push_back(_vertexCount);
        typesPtr->push_back(type);
        _totalVertexCount += _vertexCount;

        // reset vertex count
        _vertexCount = 0;

        // increment primitive count (for stats only)
        _primitiveCount++;
    }
    else
    {
        FFATAL(("OSGExtrusion::storePrimitive: Tried to store empty primitive\n"));
    }
}


//-----------------------------------------------------------------------------
// Computes a new index of type UInt32 for the specified property and
// stores the (property -> index) pair in the specified pIndexMap of type
// 'PType -> UInt32'. Two properties map to the same index iff their
// componentwise distance is less than Eps.
//
// Author: afischle
//-----------------------------------------------------------------------------
template <typename PType> 
inline UInt32 
ExtrusionSurface::store(PType property, 
                        std::map<PType, UInt32, vecless<PType> > &pIndexMap)
{
    typedef typename std::map<PType, 
                              UInt32,
                              vecless<PType> >::iterator   PTypeMapIterator;
    typedef typename std::map<PType, 
                              UInt32,
                              vecless<PType> >::value_type PTypeMapValueType;
    
    UInt32 newIndex = pIndexMap.size();
    const std::pair<PTypeMapIterator, bool>& result
        = pIndexMap.insert(PTypeMapValueType(property, newIndex));

#ifdef DEBUG_PROPERTY_STORE
    std::ostringstream strout;
    strout << "OSGExtrusion:store: Storing property:" << std::endl;
    strout << "\t"
           << result.first->first << " -> " << result.first->second
           << " (new insert: " << (result.second ? "TRUE" : "FALSE") << ")";
    SLOG << strout.str() << std::endl;
#endif

    // return index of property
    return result.first->second;
}


//-----------------------------------------------------------------------------
// Stores the index of the property argument into the specified map and index
// field container.
//
// Author: afischle
//-----------------------------------------------------------------------------
template <typename PType>
inline void
ExtrusionSurface::store(PType property, 
                        std::map<PType, UInt32, vecless<PType> > &propertyIndexMap,
                        GeoIndicesUI32Ptr indicesPtr)
{
    assert(indicesPtr != NullFC);
    indicesPtr->push_back(store(property, propertyIndexMap));
}


OSG_END_NAMESPACE


#define OSGEXTRUSIONGEOMETRY_INLINE_CVSID "@(#)$Id: OSGExtrusionGeometry.inl,v 1.2 2005/06/02 14:32:16 vossg Exp $"


#ifdef DEBUG_SUBDIVISION
#undef DEBUG_SUBDIVISION
#endif

#ifdef DEBUG_VERTEX_STORE
#undef DEBUG_VERTEX_STORE
#endif

#ifdef DEBUG_PROPERTY_STORE
#undef DEBUG_PROPERTY_STORE
#endif

#ifdef DEBUG_PRIMITIVE_STORE
#undef DEBUG_PRIMITIVE_STORE
#endif
