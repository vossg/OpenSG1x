#ifndef WIN32

// System declarations
#ifdef __sgi
#include <math.h>
#else
#include <cmath>
#endif
#include <iostream>

// Application declarations
// Class declarations
#include "OSGTXFFontGlyph.h"

/* */
OSG_USING_NAMESPACE

// Static Class Variable implementations:
TXFFontGlyph::TXFFontGlyph(void) :
    FontGlyph()
{
    return;
}

/*
TXFFontGlyph::TXFFontGlyph (const TXFFontGlyph &obj )
{
	return;
}
*/
TXFFontGlyph::TXFFontGlyph(Int32 ascii, Int32 unicode) :
    FontGlyph(ascii, unicode)
{
    return;
}

/* */
TXFFontGlyph::~TXFFontGlyph(void)
{
    return;
}

/* */
void TXFFontGlyph::setupGlyph(Int32 ascii, Int32 unicode)
{
    setAsciiCode(ascii);
    setUniCode(unicode);
}

/* */
bool TXFFontGlyph::createGlyph(void)
{
    if(!isValid())
        return false;

    // TODO
    // create image from global image map, set sizes
    return true;
}

/* */
bool TXFFontGlyph::setSizes(Real32 *OSG_CHECK_ARG(_boundingBox),
                            Real32 &OSG_CHECK_ARG(_advance))
{
    return true;
}

/* */
bool TXFFontGlyph::setSizes(Int32 *OSG_CHECK_ARG(_boundingBox),
                            Int32 &OSG_CHECK_ARG(_advance))
{
    return true;
}
#endif
