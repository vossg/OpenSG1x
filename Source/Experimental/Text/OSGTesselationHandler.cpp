
#include <OSGConfig.h>

#include <OSGGL.h>
#include <OSGGLU.h>

#include <iostream>
#include <assert.h>

#include <OSGLog.h>

#include "OSGFontGlyphContour.h"
#include "OSGVectorFontGlyph.h"

#include "OSGTesselationHandler.h"

OSG_BEGIN_NAMESPACE

VectorFontGlyph *tmTesselator = NULL;

void OSG_APIENTRY tessBegin(GLenum OSG_CHECK_ARG(type))
{
    assert(tmTesselator);
}

void OSG_APIENTRY tessEdgeFlag(GLboolean OSG_CHECK_ARG(flag))
{
    assert(tmTesselator);
}

void OSG_APIENTRY tessVertex(void *data)
{
    assert(tmTesselator);

    tmTesselator->addPoint((float *) data);
}

void OSG_APIENTRY tessEnd(void)
{
    assert(tmTesselator);
}

void OSG_APIENTRY  tessError(GLenum errorNum)
{
    assert(tmTesselator);
    FWARNING(("got tesselation error %d (%s).", 
              (int) errorNum, gluErrorString(errorNum)));
}

OSG_END_NAMESPACE
