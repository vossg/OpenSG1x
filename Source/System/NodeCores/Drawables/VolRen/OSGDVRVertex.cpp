
#include <OSGVector.h>

#include "OSGDVRVertex.h"

OSG_USING_NAMESPACE

DVRVertex::DVRVertex(void)
{
    pos              = Pnt3f(0.0, 0.0, 0.0);
    transformedPos   = pos;
    behindPlane      = false;
    refPlaneDistance = 0.0; 
}

DVRVertex::DVRVertex(const DVRVertex &vertex)
{
    pos               = vertex.pos;
    transformedPos    = vertex.transformedPos;
    adjacentTriangles = vertex.adjacentTriangles;
    behindPlane       = vertex.behindPlane;
    refPlaneDistance  = vertex.refPlaneDistance; 
}

DVRVertex::~DVRVertex(void)
{
}

void DVRVertex::calculatePlaneDistance(const Plane &plane)
{
    // calculate distance to the reference plane
    refPlaneDistance = plane.distance(pos);
}

void DVRVertex::calculatePlaneDistanceTransformed(const Plane &plane)
{
    // calculate distance to the reference plane
    refPlaneDistance = plane.distance(transformedPos);
}

void DVRVertex::calculatePlaneDistance(const Plane  &plane, 
                                       const Matrix &transform)
{
    Pnt3f transPos;
    transform.multPntFullMatrix(pos, transPos);
    
    // calculate distance to the reference plane
    refPlaneDistance = plane.distance(transPos);
}

bool DVRVertex::isBehindPlane(float dist2RefPlane, bool &switched)
{
    switched = false;

    if(dist2RefPlane > refPlaneDistance)
    {
        if(!behindPlane)
            switched = true;

        behindPlane = true;

        return true;
    }

    return false;
}

bool DVRVertex::isBehindPlane(float dist2RefPlane)
{
    return (dist2RefPlane > refPlaneDistance);
}


bool DVRVertex::isCloser(float distance)
{
    if(distance < refPlaneDistance)
    {
        return false;
    }

    if(distance == refPlaneDistance)
        return false;

    return true;
}


void DVRVertex::dump() const
{
    std::cerr << "Pos=("
              << pos 
              << ") transformedPos=("
              << transformedPos 
              << ") Adj. Tris: ";

    for(UInt32 i = 0; i < adjacentTriangles.size(); i++)
    {
        std::cerr << adjacentTriangles[i] << " ";
    }
    std::cerr << std::endl;
}

