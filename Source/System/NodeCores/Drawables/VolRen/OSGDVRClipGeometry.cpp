/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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
#include <OSGTriangleIterator.h>
#include <OSGVector.h>
#include <OSGGeometry.h>


#include <OSGDVRVertex.h>
#include <OSGDVRTriangle.h>
#include <OSGDVRClipGeometry.h>

OSG_USING_NAMESPACE

/*! \class osg::DVRClipGeometry

*/

/*----------------------- constructors & destructors ----------------------*/

// Constructor
DVRClipGeometry::DVRClipGeometry(void) :
    Inherited()
{
    initialized             = false;
    maxActiveTrianglesCount = 4;
    activeTrianglesCount    = 0;
    maxSeedVerticesCount    = 4;
    seedVerticesCount       = 0;

    activeTriangles         =  
        (DVRTriangle **) malloc(maxActiveTrianglesCount * 
                                sizeof(DVRTriangle *)   );

    seedVertices = 
        (DVRVertex   **) malloc(maxSeedVerticesCount    *
                                sizeof(DVRVertex *)     );
}

// Copy Constructor
DVRClipGeometry::DVRClipGeometry(const DVRClipGeometry &source) :
    Inherited(source)
{
    initialized             = false;
    maxActiveTrianglesCount = 4;
    activeTrianglesCount    = 0;
    maxSeedVerticesCount    = 4;
    seedVerticesCount       = 0;

    activeTriangles =  
        (DVRTriangle **) malloc(maxActiveTrianglesCount * 
                                sizeof(DVRTriangle *)   );

    seedVertices = 
        (DVRVertex   **) malloc(maxSeedVerticesCount    * 
                                sizeof(DVRVertex   *)   );
}

// Destructor
DVRClipGeometry::~DVRClipGeometry(void)
{
    if(activeTriangles)
        free(activeTriangles); // allocation with malloc/realloc!!

    if(seedVertices)
        free(seedVertices); // allocation with malloc/realloc!!
}

/*----------------------------- class specific ----------------------------*/

// initialize the static features of the class, e.g. action callbacks
void DVRClipGeometry::initMethod(void)
{
}

// react to field changes
void DVRClipGeometry::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if ((whichField & GeometryNodeFieldMask))
    {
        initialized = false;
    }
}

// output the instance for debug purposes
void DVRClipGeometry::dump(      UInt32    , 
                          const BitVector ) const
{
    //    _sfGeometry.dump();
    //    _sfBeacon.dump();
    SLOG << "Dump DVRClipGeometry NI" << std::endl;
}

// create the triangled geometry data structure
Int32 DVRClipGeometry::insertVertex(Int32 idx)
{
    for(UInt32 i = 0; i < _mfVertices.size(); i++)
    {
        if(_mfVertices[i].pos == geometry->getPositions()->getValue(idx))
            return i;
    }

    DVRVertex newVertex;

    newVertex.pos = geometry->getPositions()->getValue(idx);

    _mfVertices.push_back(newVertex);

    return _mfVertices.size() - 1;
}


bool DVRClipGeometry::buildTriangledGeometry(void)
{
    // create triangles 
    for(TriangleIterator triangleIt  = geometry->beginTriangles(); 
                         triangleIt != geometry->endTriangles  ();
                       ++triangleIt)
    {
        DVRTriangle newTriangle;
        
        for(UInt32 i = 0; i < 3; i++)
        {
            Int32 vertexIndex = triangleIt.getPositionIndex(i);
            
            vertexIndex = insertVertex(vertexIndex);

            newTriangle.vertices[i] = vertexIndex;
            
            _mfVertices[vertexIndex].adjacentTriangles.push_back(
                _mfTriangles.size());

            newTriangle.cutPnt  [i] = 0.0;
            newTriangle.cutPoint[i] = 0.0;
        }
        
        // compute normal and check orientation
        newTriangle.normal = 
            (_mfVertices[newTriangle.vertices[0]].pos -
             _mfVertices[newTriangle.vertices[1]].pos).cross(
                 _mfVertices[newTriangle.vertices[0]].pos -
                 _mfVertices[newTriangle.vertices[2]].pos);

        newTriangle.normal.normalize();
    
        if(newTriangle.normal.dot(triangleIt.getNormal(0)) < 0.0)
            newTriangle.normal.negate();      
    
        _mfTriangles.push_back(newTriangle);
    }

    // find neighbouring triangles
    for(UInt32 i = 0; i < _mfTriangles.size(); i++)
    {
        Int32 *vertices = _mfTriangles[i].vertices;   

        for(UInt32 l = 0; l < 3; l++)
        {
            const DVRVertex &v0 = _mfVertices[vertices[l]];
            const DVRVertex &v1 = _mfVertices[vertices[(l + 1) % 3]];
            
            for(UInt32 j = 0; j < v0.adjacentTriangles.size(); j++)
            {
                for(UInt32 k = 0; k < v1.adjacentTriangles.size(); k++)
                {
                    if(v0.adjacentTriangles[j] == v1.adjacentTriangles[k] &&
                       v0.adjacentTriangles[j] != i                       && 
                       v1.adjacentTriangles[k] != i                         )
                    {	  
                        if(_mfTriangles[i].neighbours[l] != -1)
                        {
                            SLOG << "Error: Could not build clip geometry"
                                 << std::endl
                                 << "        one triangle edge shared by more "
                                 << "than two triangles" 
                                 << std::endl;

                            return false;
                        }
                        
                        _mfTriangles[i].neighbours[l] = 
                            v1.adjacentTriangles[k];
                    }
                }
            }
        }
    }
    
    // check for non-closed geometry
    UInt32 checkCount = 0; 

    for(UInt32 i = 0; i < _mfTriangles.size(); i++)
    {
        for(UInt32 j = 0; j < 3; j++)
        {
            if(_mfTriangles[i].neighbours[j] == -1)
            {
                checkCount++;
            }
        }
    }

    if(checkCount > 0)
    {
        SLOG << "Error: Could not build clip geometry" 
             << std::endl
             << checkCount
             << "open edges found!"
             << std::endl;

        return false;
    }
    
    return true;
}

bool DVRClipGeometry::isCut(DVRTriangle *tri, 
                            Real32       dist2RefPlane, 
                            DVRVertex   *switchedVertices[3])
{
    bool v[3] = {false, false, false};

    bool vertexSwitched;
    int  countSwitchedVertices = 0;

    switchedVertices[0] = NULL;
    switchedVertices[1] = NULL;
    switchedVertices[2] = NULL;

    // for every vertex, check if it is in front of or behind the current 
    // reference plane and if it has moved behind the plane

    for(UInt32 i = 0; i < 3; i++)
    {
        v[i] = _mfVertices[tri->vertices[i]].isBehindPlane(dist2RefPlane, 
                                                           vertexSwitched);
        if(vertexSwitched)
        {
            vertexSwitched = false;

            switchedVertices[countSwitchedVertices] = 
                &_mfVertices[tri->vertices[i]];

            countSwitchedVertices++;
        }
    }

    bool cut = false;

    // remember the cut edges for faster (and correct ;-) contour tracing...
    for(UInt32 i = 0; i < 3; i++)
    {
        if(v[i] ^ v[(i + 1) % 3])
        {
            tri->edgeCut[i] = true;
            cut             = true;
        }
        else
        {
            tri->edgeCut[i] = false;
        }
    }
  
    return cut;
}


// Prepare the object for clipping a volume's slices 
void DVRClipGeometry::initialize(const Matrix &volumeToWorld)
{
    if(!initialized)
    {
        _mfVertices.clear ();
        _mfTriangles.clear();

        if(getGeometryNode() != NullFC)
        {
            if(getGeometryNode()->getCore() != NullFC)
            {                
                geometry = GeometryPtr::dcast(getGeometryNode()->getCore());

                if(geometry != NullFC)
                    initialized = buildTriangledGeometry();
            }
        }
    }

    if(!initialized) 
        return;

    Matrix old    = toVolumeSpace;

    toVolumeSpace = volumeToWorld;
    toVolumeSpace.invert();

    NodePtr beacon =  getBeacon();

    if(beacon != NullFC)
    {
        toVolumeSpace.mult(beacon->getToWorld());
    }
    else if(getGeometryNode() != NullFC)
    {    
        toVolumeSpace.mult(getGeometryNode()->getToWorld());
    }

    Matrix toVolumeSpaceInvT;

    toVolumeSpace    .inverse(toVolumeSpaceInvT);
    toVolumeSpaceInvT.transpose();

    UInt32 numVertices = _mfVertices.size();

    // transform vertices to volume's space
    for(UInt32 i = 0; i < numVertices; i++)
    {
        toVolumeSpace.multMatrixPnt(_mfVertices[i].pos, 
                                    _mfVertices[i].transformedPos);
    }

    UInt32 numTriangles = _mfTriangles.size();

    // transform triangle normals to volume's space
    for(UInt32 i = 0; i < numTriangles; i++)
    {
        toVolumeSpaceInvT.multMatrixVec(_mfTriangles[i].normal, 
                                        _mfTriangles[i].transformedNormal);

        _mfTriangles[i].transformedNormal.normalize();
    }
}

// Prepare the object for clipping a volume's slices 
void DVRClipGeometry::resetLocalData(void)
{
    UInt32 numVertices = _mfVertices.size();

    for(UInt32 i = 0; i < numVertices; i++)
    {
        DVRVertex &vertex  = _mfVertices[i];

        vertex.behindPlane = false;
    }

    UInt32 numTriangles = _mfTriangles.size();

    // initialize the triangles local data
    for(UInt32 i = 0; i < numTriangles; i++)
    {
        _mfTriangles[i].visited   = false;
        _mfTriangles[i].inContour = false;

        for (UInt32 j = 0; j < 3; j++)
            _mfTriangles[i].edgeCut[j] = false;
    }
}

void DVRClipGeometry::setReferencePlane(const Plane &referencePlane)
{
    UInt32 numVertices = _mfVertices.size();
    
    for(UInt32 i = 0; i < numVertices; i++)
        _mfVertices[i].calculatePlaneDistanceTransformed(referencePlane);
}

void DVRClipGeometry::computeSeedVertices(void)
{
    if(!initialized) 
        return;

    // clear seed vertex list and active triangle list
    seedVerticesCount    = 0;
    activeTrianglesCount = 0;

    UInt32 numVertices = _mfVertices.size();
  
    // compute initial seed vertex set
    for(UInt32 i = 0; i < numVertices; i++)
    {
        if(isLocalMinimum(_mfVertices[i]))
        {
            if(maxSeedVerticesCount <= seedVerticesCount)
            {
                maxSeedVerticesCount *= 2;

                seedVertices = 
                    (DVRVertex **)realloc(seedVertices,
                                          maxSeedVerticesCount *
                                          sizeof(DVRVertex *)  );
            }

            seedVertices[seedVerticesCount++] = &_mfVertices[i];
        }
    } 
}

void DVRClipGeometry::linkContour(      DVRTriangle *startTriangle,
                                        Real32       dist2RefPlane,
                                  const Vec3f       &viewDir, 
                                        bool         positiveWinding)
{
    FDEBUG(("DVRClipGeometry - linkcontour dist = %f\n", dist2RefPlane));
  
    bool closed = false;

    // first, we have to check for the correct winding direction.

    Pnt3f vertex[2];
    bool firstEdge;
    int  first = 0, second = 0;

    if(startTriangle->edgeCut[0] && startTriangle->edgeCut[1])
    {
        vertex[0] = interpolate(startTriangle, 1, 0, dist2RefPlane); 
        vertex[1] = interpolate(startTriangle, 1, 2, dist2RefPlane);

        first = 0; second = 1;
    }
    else if (startTriangle->edgeCut[1] && startTriangle->edgeCut[2])
    {
        vertex[0] = interpolate(startTriangle, 2, 1, dist2RefPlane);
        vertex[1] = interpolate(startTriangle, 2, 0, dist2RefPlane);

        first = 1; second = 2;
    }
    else if (startTriangle->edgeCut[0] && startTriangle->edgeCut[2])
    {
        vertex[0] = interpolate(startTriangle, 0, 1, dist2RefPlane);
        vertex[1] = interpolate(startTriangle, 0, 2, dist2RefPlane);

        first = 0; second = 2;
    }

    // Now we should have both cut points on our edges.

    // If the cross product of the normal of this triangle with the 
    // vector between the two cut points (cutPoint[1] - cutPoint[0]) 
    // has a positive dot product with the viewing direction, then 
    // the edge with cutPoint[0] on it is the right direction, otherwise
    // we would have to choose the other direction.

    Vec3f tmp = vertex[1] - vertex[0];

    tmp = tmp.cross(startTriangle->transformedNormal);

    if(tmp.dot(viewDir) <= 0.0)
    {
        firstEdge = false;
    }else
    {
        firstEdge = true;
    }

    if(!positiveWinding)
        firstEdge = !firstEdge;

    DVRTriangle *current = startTriangle;

    current->inContour = true;

    if(firstEdge)
    {
        current->cutPnt      = vertex[0];
        current->cutPoint[0] = vertex[0][0];
        current->cutPoint[1] = vertex[0][1];
        current->cutPoint[2] = vertex[0][2];

        current->contourNeighbour = &_mfTriangles[current->neighbours[first]];

        //      // debugging -> remove
        //      if(!current->contourNeighbour){
        //        std::cerr<<"contour neighbour is NULL\n";
        //        exit(0);
        //      }

        current = current->contourNeighbour;
    }
    else
    {
        current->cutPnt      = vertex[1];
        current->cutPoint[0] = vertex[1][0];
        current->cutPoint[1] = vertex[1][1];
        current->cutPoint[2] = vertex[1][2];    

        current->contourNeighbour = &_mfTriangles[current->neighbours[second]];
        //      // debugging -> remove
        //      if(!current->contourNeighbour){
        //        std::cerr<<"contour neighbour is NULL\n";
        //        exit(0);
        //      }

        current = current->contourNeighbour;    
    }

    //check neighbours
    while(!closed)
    {
        closed             = true;
        current->inContour = true;

        for(UInt32 i = 0; i < 3; i++)
        {
            // if a neighbour triangle is in the active triangle list and 
            // not yet in a contour it is our new contour neighbour.
            if( current->edgeCut[i] && 
               !_mfTriangles[current->neighbours[i]].inContour)
            {
                // calculate cut point 	
                current->cutPnt = interpolate(current, 
                                              i, 
                                              (i + 1) % 3, 
                                              dist2RefPlane);

                current->cutPoint[0] = current->cutPnt[0];
                current->cutPoint[1] = current->cutPnt[1];
                current->cutPoint[2] = current->cutPnt[2];

                current->contourNeighbour = 
                    &_mfTriangles[current->neighbours[i]];

                //  	// debugging -> remove
                //  	if(!current->contourNeighbour){
                //  	  std::cerr<<"contour neighbour is NULL\n";
                //  	  exit(0);
                //  	}

                current = current->contourNeighbour;
                closed  = false;

                break;
            }// !inContour
        } // end for neighbours
    } // end while !closed

    for(UInt32 i = 0; i < 3; i++)
    {
        if(&_mfTriangles[current->neighbours[i]] == startTriangle)
        {
            current->cutPnt = interpolate(current, 
                                          i, 
                                          (i + 1) % 3, 
                                          dist2RefPlane);

            current->cutPoint[0] = current->cutPnt[0];
            current->cutPoint[1] = current->cutPnt[1];
            current->cutPoint[2] = current->cutPnt[2];

            // now the ring is closed.

            current->contourNeighbour = startTriangle;
            //        // debugging -> remove
            //        if(!current->contourNeighbour){
            //  	std::cerr<<"contour neighbour is NULL\n";
            //  	exit(0);
            //        }
            break;
        }
    } // end for neighbours

    //    // debugging -> remove
    //    if(!current->contourNeighbour){
    //      std::cerr <<"contour could not closed\n";
    //      std::cerr <<current->edgeCut[0]<<current->edgeCut[1]
    //                <<current->edgeCut[2]<<std::endl;
    //      exit(0);
    //    }
}

void DVRClipGeometry::buildContours(      Real32  dist2RefPlane, 
                                          bool    positiveWinding, 
                                    const Vec3f  &sliceNormal    )
{
    contours.clear();

    for(UInt32 i = 0; i < activeTrianglesCount; i++)
    { 
        DVRTriangle* currentTriangle = activeTriangles[i];

        // if the triangle is already in a contour we can skip it    
        if(!currentTriangle->inContour)
        {
            contours.push_back(currentTriangle);
            
            linkContour(currentTriangle, 
                        dist2RefPlane, 
                        sliceNormal, 
                        positiveWinding);
        }
    }
}

const DVRTriangleList &DVRClipGeometry::getContours(
          Real32  dist2RefPlane, 
          bool    positiveWinding, 
    const Vec3f  &sliceNormal    )
{  
    if(!initialized) 
        return contours;

    // compute new active triangle set and for this slice 
    // and update seed vertex set
    updateActiveTriangles(dist2RefPlane, sliceNormal);

    // build contours from active triangle set
    buildContours(dist2RefPlane, positiveWinding, sliceNormal);

    return contours;
}

void DVRClipGeometry::addNewActiveTriangles(DVRVertex *vertex, 
                                            Real32     dist2RefPlane)
{
    // iterate over triangles
    DVRVertex *switchedVertices[3];
  
    std::vector<Int32> &adjacentTriangles = vertex->adjacentTriangles; 

    UInt32 numAdjacenTriangles =  adjacentTriangles.size();

    for(UInt32 j = 0; j < numAdjacenTriangles; j++)
    {
        DVRTriangle *triangle = &_mfTriangles[adjacentTriangles[j]];

        if(!triangle->visited)
        {
            // insert triangle if it is cut and it was not visited so far...
            if(isCut(triangle,dist2RefPlane, switchedVertices)) 
            {
                triangle->visited   = true;
                triangle->inContour = false;

                addActiveTriangle(triangle);
            }
            else
            { 
                // neighbour triangle is not visited and not cut -> 
                // check neighbours

                triangle->visited   = true;
                triangle->inContour = false;
            } 
      
            // check neighbours
            for(UInt32 i = 0; i < 3; i++)
            {
                if(switchedVertices[i])
                {
                    addNewActiveTriangles(switchedVertices[i],
                                          dist2RefPlane      );
                }
            }       
        }
    }
}

void DVRClipGeometry::updateActiveTriangles(      Real32  dist2RefPlane,  
                                            const Vec3f  &             )
{
    // first, we check the active triangles.

    DVRVertex *switchedVertices[3];
  
    for(Int32 triIt = activeTrianglesCount-1; triIt >= 0; triIt--)
    {
        DVRTriangle *tri = activeTriangles[triIt];

        tri->inContour        = false;
        tri->contourNeighbour = NULL;

        // if an active triangle is cut by the plane it simply stays in 
        // the list.otherwise we have to remove it and check the neighbour
        // triangles.

        if(!(isCut(tri,dist2RefPlane, switchedVertices)))
        {
            //remove triangle
            activeTrianglesCount--;
            activeTriangles[triIt] = activeTriangles[activeTrianglesCount];
        }
        
        // check triangles adjacent to the vertices that moved behind 
        // the active slice

        for(UInt32 i = 0; i < 3; i++)
        {
            if(switchedVertices[i])
                addNewActiveTriangles(switchedVertices[i], dist2RefPlane);
        }
    }

    // now we have to check our seed set, if new triangles have to be added.
  
    // run over our seed set
    for(Int32 vertIt = seedVerticesCount-1; vertIt >= 0; vertIt--)
    {
        DVRVertex *sv = seedVertices[vertIt];

        // check if seed vertex has been hit by the plane
        if (sv->isBehindPlane(dist2RefPlane))
        {
            // add triangles to active triangle list      
            addNewActiveTriangles(sv,dist2RefPlane);
            
            // we will never need this seed vertex again, we can erase it 
            // from the list.
            seedVertices[vertIt] = seedVertices[--seedVerticesCount];
        }    
    }
}

//
void DVRClipGeometry::addActiveTriangle(DVRTriangle *tri)
{
    if(maxActiveTrianglesCount <= activeTrianglesCount)
    {
        FDEBUG(("realloc active tri list\n"));
        // allocate additional mem (TODO: better prediction for needed mem)

        maxActiveTrianglesCount *= 2;
        activeTriangles          = 
            (DVRTriangle **) realloc(activeTriangles, 
                                     sizeof(DVRTriangle *) * 
                                     maxActiveTrianglesCount);
    }
    
    activeTriangles[activeTrianglesCount] = tri;    

    activeTrianglesCount++;
}

bool DVRClipGeometry::setNumAddPerVertexAttr(
    UInt32 additionalPerVertexAttributes)
{
    UInt32 numTriangles = _mfTriangles.size();

    // update triangles
    for(UInt32 i = 0; i < numTriangles; i++)
    {
        if(!_mfTriangles[i].setNumAddPerVertexAttr(
               additionalPerVertexAttributes))
        {
            return false;
        }
    }

    return true;
}

//  // debugging -> remove
//  void DVRClipGeometry::correct()
//  {
//    for(UInt32 i = 0; i < _mfTriangles.size(); i++){  
//      _mfTriangles[i].correct();    
//    }
//    for(UInt32 i = 0; i < _mfVertices.size(); i++){
//      _mfVertices[i].correct();
//    }
//  }



/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: $";
    static Char8 cvsid_hpp       [] = OSGDVRCLIPGEOMETRYBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDVRCLIPGEOMETRYBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDVRCLIPGEOMETRYFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

