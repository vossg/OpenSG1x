
#include <OSGConfig.h>

#ifdef OSG_WITH_FREETYPE1
#ifdef __sgi
#include <math.h>
#else
#include <cmath>
#endif

#include <iostream>

#include <OSGBaseTypes.h>
#include <OSGLog.h>

#include "OSGTTFontGlyph.h"

#include <assert.h>

OSG_USING_NAMESPACE

TTFontGlyph::TTFontGlyph(void) :
     Inherited     (    ),
    _ttError       (0L  ),
    _ttGlyphMetrics(    ),
    _ttFace        (NULL),
    _ttInstance    (NULL)
{
    _ttGlyph.z        = NULL;
}

TTFontGlyph::TTFontGlyph(Int32 ascii, Int32 unicode) :
     Inherited     (ascii, 
                    unicode),
    _ttError       (0L     ),
    _ttGlyphMetrics(    ),
    _ttFace        (NULL   ),
    _ttInstance    (NULL   )
{
    _ttGlyph.z        = NULL;
}

TTFontGlyph::~TTFontGlyph(void)
{
}

void TTFontGlyph::setupGlyph(Int32 ascii, Int32 unicode)
{
    setAsciiCode(ascii);
    setUniCode(unicode);
}

void TTFontGlyph::setFontDefs(TT_Face *ttFacte, TT_Instance *ttInstance)
{
    _ttFace     = ttFacte;
    _ttInstance = ttInstance;
}

bool TTFontGlyph::createGlyph(void)
{
    if(!isValid())
        return false;

    _ttError = TT_New_Glyph(*_ttFace, &_ttGlyph);

    if(_ttError)
    {
        FWARNING(("Create TT_New_Glyph failed with TT_Error= %d", _ttError));
        setInvalid();
        return false;
    }

    _ttError = TT_Load_Glyph(*_ttInstance, _ttGlyph, getUniCode(),
                                 TTLOAD_DEFAULT);
    if(_ttError)
    {
        FWARNING(("Create TT_Load_Glyph failed with TT_Error= %d", _ttError));
        setInvalid();
        return false;
    }

    return true;
}

bool TTFontGlyph::getOutline(TT_Outline &ttOutline)
{
    _ttError = TT_Get_Glyph_Outline(_ttGlyph, &ttOutline);
    if(_ttError)
    {
        FWARNING(("Create TT_Get_Glyph_Outline failed with TT_Error= %d",
                             _ttError));
        setInvalid();
        return false;
    }

    return true;
}

bool TTFontGlyph::setSizes(float *_boundingBox, float &_advance)
{
    TT_Get_Glyph_Metrics(_ttGlyph, &_ttGlyphMetrics);

    _advance = (static_cast<Real32>(_ttGlyphMetrics.advance) / 64);

    _boundingBox[0] = static_cast<Real32>(_ttGlyphMetrics.bbox.xMin) / 64;
    _boundingBox[1] = static_cast<Real32>(_ttGlyphMetrics.bbox.xMax) / 64;
    _boundingBox[2] = static_cast<Real32>(_ttGlyphMetrics.bbox.yMin) / 64;
    _boundingBox[3] = static_cast<Real32>(_ttGlyphMetrics.bbox.yMax) / 64;

    return true;
}

bool TTFontGlyph::setSizes(Int32 *_boundingBox, Int32 &_advance)
{
    TT_Get_Glyph_Metrics(_ttGlyph, &_ttGlyphMetrics);

    TT_BBox &bbox = _ttGlyphMetrics.bbox;

    bbox.xMin = bbox.xMin & -64;
    bbox.yMin = bbox.yMin & -64;
    bbox.xMax = (bbox.xMax + 63) & -64;
    bbox.yMax = (bbox.yMax + 63) & -64;

    _advance = ((_ttGlyphMetrics.advance + 63) & -64) / 64;

    _boundingBox[0] = bbox.xMin / 64;
    _boundingBox[1] = bbox.xMax / 64;
    _boundingBox[2] = bbox.yMin / 64;
    _boundingBox[3] = bbox.yMax / 64;

    return true;
}

void TTFontGlyph::glyphDone(void)
{
    TT_Done_Glyph(_ttGlyph);
}

bool TTFontGlyph::renderGlyph(TT_Raster_Map map, Int32 xOff, Int32 yOff)
{
    _ttError = TT_Get_Glyph_Pixmap(_ttGlyph, &map, xOff * 64, yOff * 64);

    if(_ttError)
    {
        FWARNING(("Create TT_Get_Glyph_Pixmap failed with TT_Error= %d",
                             _ttError));
        setInvalid();
        return false;
    }

    return true;
}
#endif // OSG_WITH_FREETYPE1
