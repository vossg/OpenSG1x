// System declarations

#include <GL/gl.h>
#include <GL/glu.h>

#include <assert.h>

// Application declarations
#include "OSGFontGlyphContour.h"
#include "OSGVectorFontGlyph.h"


// 'Class' declarations
#include "OSGtesselationHandler.h"




OSG_USING_NAMESPACE




VectorFontGlyph *tmTesselator = 0;

void CALLINGCONV osg::tessBegin(GLenum type)
{
    assert(tmTesselator);
}

void CALLINGCONV  osg::tessEdgeFlag(GLboolean flag)
{
    assert(tmTesselator);
}

//  ???
void CALLINGCONV  osg::tessVertex(void *data)
{
    assert(tmTesselator);
    
    tmTesselator->addPoint((float *)data);
}

void CALLINGCONV  osg::tessEnd(void)
{
    assert(tmTesselator);
}

void CALLINGCONV  osg::tessError(GLenum errno)
{
    assert(tmTesselator);
    cout << "got tesselation error : " << (int) errno << "(" 
	 << gluErrorString(errno) << ")" << endl;
}

