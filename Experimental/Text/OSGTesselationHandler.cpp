
#ifndef WIN32
// System declarations

#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>
#include <assert.h>

#include <OSGLog.h>


// Application declarations
#include "OSGFontGlyphContour.h"
#include "OSGVectorFontGlyph.h"


// 'Class' declarations
#include "OSGTesselationHandler.h"




OSG_USING_NAMESPACE


VectorFontGlyph *osg::tmTesselator = 0;

void OSG_SYSTEMLIB_DLLMAPPING osg::tessBegin(GLenum OSG_CHECK_ARG(type))
{
    assert(tmTesselator);
}

void OSG_SYSTEMLIB_DLLMAPPING  osg::tessEdgeFlag(GLboolean OSG_CHECK_ARG(flag))
{
    assert(tmTesselator);
}

//  ???
void OSG_SYSTEMLIB_DLLMAPPING  osg::tessVertex(void *data)
{
    assert(tmTesselator);
    
    tmTesselator->addPoint((float *)data);
}

void OSG_SYSTEMLIB_DLLMAPPING  osg::tessEnd(void)
{
    assert(tmTesselator);
}

void OSG_SYSTEMLIB_DLLMAPPING  osg::tessError(GLenum errorNum)
{
    assert(tmTesselator);
    FWARNING(("got tesselation error %d (%s).", (int) errorNum, gluErrorString(errorNum)));
}

#endif
