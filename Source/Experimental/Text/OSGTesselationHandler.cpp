#ifndef WIN32

// System declarations
#include <OSGGL.h>
#include <OSGGLU.h>

#include <iostream>
#include <assert.h>

#include <OSGLog.h>

// Application declarations
#include "OSGFontGlyphContour.h"
#include "OSGVectorFontGlyph.h"

// 'Class' declarations
#include "OSGTesselationHandler.h"


OSG_USING_NAMESPACE 

OSG_BEGIN_NAMESPACE
VectorFontGlyph *tmTesselator = 0;
OSG_END_NAMESPACE

/* */
void OSG_SYSTEMLIB_DLLMAPPING OSG::tessBegin(GLenum OSG_CHECK_ARG(type))
{
    assert(tmTesselator);
}

/* */
void OSG_SYSTEMLIB_DLLMAPPING OSG::tessEdgeFlag(GLboolean OSG_CHECK_ARG(flag))
{
    assert(tmTesselator);
}

//  ???
void OSG_SYSTEMLIB_DLLMAPPING OSG::tessVertex(void *data)
{
    assert(tmTesselator);

    tmTesselator->addPoint((float *) data);
}

/* */
void OSG_SYSTEMLIB_DLLMAPPING OSG::tessEnd(void)
{
    assert(tmTesselator);
}

void OSG_SYSTEMLIB_DLLMAPPING  OSG::tessError(GLenum errorNum)
{
    assert(tmTesselator);
    FWARNING(("got tesselation error %d (%s).", (int) errorNum, gluErrorString(errorNum)));
}
#endif
