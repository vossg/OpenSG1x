#ifndef OSGDVRRENDERSLICE_H
#define  OSGDVRRENDERSLICE_H

#include <vector>
//#include <list>

#include <OSGGL.h>
#include <OSGVector.h>

OSG_BEGIN_NAMESPACE

/*
  A data structure that represents an OpenGL primitive with 
  its assocciated vertex data for a clipped slice
*/

class DVRRenderSlicePrimitive
{
  public:
    
    // render this primitive
    void render(void) const;
  
    // the type of the primitive
    GLenum type;
    
    // the list of the primitive's vertices
    std::vector<GLdouble *> vertices;
};


/*
  A structure that holds the data for a complete clipped slice
*/

#ifdef __sgi
#pragma set woff 1375
#endif

class DVRRenderSlice : public std::vector<DVRRenderSlicePrimitive *>
{
  public:
    
    enum Orientation 
    {
        UNDEFINED, 
        XY, 
        XZ, 
        YZ
    };

  public:

    DVRRenderSlice(void);
    ~DVRRenderSlice(void);
    
    // render all primitives of this slice
    void render(void) const;

    // empty the list of primitives
    void clear (void);

    // track dynamically allocated data (vertexCombine) during 
    // tesselation with gluTesselator

    GLdouble     *vertexCombineData;
    UInt32        numVertexCombineData;
    UInt32        maxVertexCombineData;

    // if true, render primitives directly instead of building the primitives 
    // list; usefull for shaders  without a slice render callback

    bool         directRender;

    // number of additional (GLdouble) attributes per vertex
    UInt32       numPerVertexData;

    // orientation of this slice
    Orientation  orientation;

};

#ifdef __sgi
#pragma reset woff 1375
#endif

OSG_END_NAMESPACE

#endif
