
#include <OSGConfig.h>

#ifdef __sgi
#include <math.h>
#else
#include <cmath>
#endif

#include <iostream>

#include "OSGTXFFontGlyph.h"

OSG_USING_NAMESPACE

TXFFontGlyph::TXFFontGlyph(void) :
    Inherited()
{
}

TXFFontGlyph::TXFFontGlyph(Int32 ascii, Int32 unicode) :
    Inherited(ascii, unicode)
{
}

TXFFontGlyph::~TXFFontGlyph(void)
{
}

void TXFFontGlyph::setupGlyph(Int32 ascii, Int32 unicode)
{
    setAsciiCode(ascii  );
    setUniCode  (unicode);
}

bool TXFFontGlyph::createGlyph(void)
{
    if(!isValid())
        return false;

    // TODO
    // create image from global image map, set sizes
    return true;
}

bool TXFFontGlyph::setSizes(Real32 *OSG_CHECK_ARG(_boundingBox),
                            Real32 &OSG_CHECK_ARG(_advance    ))
{
    return true;
}

bool TXFFontGlyph::setSizes(Int32 *OSG_CHECK_ARG(_boundingBox),
                            Int32 &OSG_CHECK_ARG(_advance    ))
{
    return true;
}
