
#include <OSGConfig.h>
#include <OSGVector.h>

#include "OSGDVRSlice.h"

OSG_USING_NAMESPACE

DVRSlice::DVRSlice(void)
{
    // initialize member variables
    numberOfVertices = 0;
    normal           = Vec3f(0.0,0.0,0.0);
    vertexData       = new Pnt3f[12];
}

DVRSlice::~DVRSlice(void)
{
    // cleanup
    delete [] vertexData;
}

Pnt3f DVRSlice::getVertex(UInt32 number)
{
    return vertexData[number];
}

UInt32 DVRSlice::getVertexCount()
{
    return numberOfVertices;
}

void DVRSlice::setVertex(Pnt3f vertex)
{
    vertexData[numberOfVertices] = vertex;
    numberOfVertices++;
}

void DVRSlice::setNormal(Vec3f n)
{
    normal = n;
}

Vec3f DVRSlice::getNormal()
{
  // if no normal is set, we can compute it, if we have at least
  // three vertices. Otherwise the currently set normal is returned.
    if(normal == Vec3f(0.0, 0.0, 0.0) && numberOfVertices >= 3)
    {
        normal = (vertexData[0] - vertexData[1]).cross(
            vertexData[0] - vertexData[2]);

        normal.normalize();
    }

    return normal;
}

void DVRSlice::resetSlice()
{
    numberOfVertices = 0;
    normal           = Vec3f(0.0, 0.0, 0.0);
}

void DVRSlice::setTextureTransform(const Vec3f &scale, const Vec3f &translate)
{
    texScale     = scale;
    texTranslate = translate;
}

Vec3f DVRSlice::getTextureScale(void) const
{
    return texScale;
}

Vec3f DVRSlice::getTextureTranslate(void) const
{
    return texTranslate;
}

void DVRSlice::output(void)
{
    for(UInt32 i = 0; i < numberOfVertices; i++)
    {
        std::cerr << "Vertex Number " 
                  << i
                  << ": " 
                  << vertexData[i][0] 
                  << ", "
                  << vertexData[i][1] 
                  << ", "
                  << vertexData[i][2] 
                  << std::endl;
    }

    Vec3f n = getNormal();

    std::cerr << "Normal: " 
              << n[0] 
              << ", " 
              << n[1] 
              << ", " 
              << n[2] 
              << std::endl;
}
