
#include <math.h>

#include "OSGDVRTriangle.h"

OSG_USING_NAMESPACE

DVRTriangle::DVRTriangle(void)
{
    // at least we need the vertex position and a texture coordinate
    cutPoint = (GLdouble*) malloc(6 * sizeof(GLdouble));
  
    for(UInt32 i = 0; i < 3; i++)
    {
        vertices  [i] = -1;
        neighbours[i] = -1;
        cutPnt    [i] = 0.0f;
    }
}

DVRTriangle::DVRTriangle(const DVRTriangle &tri)
{
  cutPoint = (GLdouble*) malloc(6 * sizeof(GLdouble));

  for(UInt32 i = 0; i < 3; i++)
  {
      vertices  [i] = tri.vertices  [i];
      neighbours[i] = tri.neighbours[i];
      cutPnt    [i] = 0.0f;
  }

  normal = tri.normal;
}

DVRTriangle::~DVRTriangle(void)
{
    free(cutPoint); // allocation by malloc/realloc
}

bool DVRTriangle::setNumAddPerVertexAttr(UInt32 additionalPerVertexAttributes)
{
    cutPoint = (GLdouble*) realloc(
        cutPoint,
        (6 + additionalPerVertexAttributes) * sizeof(GLdouble));

    return cutPoint != NULL;
}

void DVRTriangle::dump() const
{
    std::cerr <<"Verts: " 
              << vertices[0] << " " 
              << vertices[1] << " " 
              << vertices[2]
              <<" Neighbours: "
              << neighbours[0] << " " 
              << neighbours[1] << " " 
              << neighbours[2] << std::endl;
}

