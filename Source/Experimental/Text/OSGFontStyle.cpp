
#include <OSGConfig.h>

#include <iostream>

#include "OSGFontStyle.h"

OSG_USING_NAMESPACE 

bool FontStyle::processChange(void)
{
    return false;
}

FontStyle::FontStyle(void) :
    _xRes         (72  ),
    _yRes         (72  ),
    _size         (1.f ),
    _depth        (0.f ),
    _maxDescent   (0.f ),
    _maxAscent    (0.f ),
    _baselineSkip (0.f ),
    _fontName     (    ),

    _vectorGlyphs (    ),
    _imageGlyphs  (    ),
    _txfGlyphInfos(    ),

    _txfImageMap  (NULL),

    _txfFontWidth (0   ),
    _txfFontHeight(0   )
{
    _vectorGlyphs.reserve(256);
    _imageGlyphs .reserve(256);
}

#ifdef DELETE_ME
FontStyle::FontStyle(const FontStyle &obj) :
    _xRes(obj._xRes),
    _yRes(obj._yRes),
    _size(obj._size),
    _depth(obj._depth),
    _maxDescent(obj._maxDescent),
    _maxAscent(obj._maxAscent),
    _baselineSkip(obj._baselineSkip),
    _fontName(obj._fontName)
{
}
#endif

FontStyle::~FontStyle(void)
{
}

void FontStyle::setTXFImageMap(UChar8 *image)
{
    _txfImageMap = image;
}

UChar8 *FontStyle::getTXFImageMap(void)
{
    return _txfImageMap;
}

bool FontStyle::getTXFImageSizes(Int32 &width, Int32 &height)
{
    width  = _txfFontWidth;
    height = _txfFontHeight;

    return width * height > 0;
}


Int32 FontStyle::getXRes(void)
{
    return _xRes;
}

void FontStyle::setXRes(Int32 xRes)
{
    _xRes = xRes;
}

Int32 FontStyle::getYRes(void)
{
    return _yRes;
}

void FontStyle::setYRes(Int32 yRes)
{
    _yRes = yRes;
}

Real32 FontStyle::getSize(void)
{
    return _size;
}

void FontStyle::setSize(Real32 size)
{
    _size = size;
}

void FontStyle::setMaxDescent(Real32 maxDescent)
{
    _maxDescent = maxDescent;
}

Real32 FontStyle::getMaxDescent(void)
{
    return _maxDescent;
}

void FontStyle::setMaxAscent(Real32 maxAscent)
{
    _maxAscent = maxAscent;
}

Real32 FontStyle::getMaxAscent(void)
{
    return _maxAscent;
}

void FontStyle::setBaselineSkip(Real32 baselineSkip)
{
    _baselineSkip = baselineSkip;
}

Real32 FontStyle::getBaselineSkip(void)
{
    return _baselineSkip;
}

const Char8 *FontStyle::getFontName(void)
{
    return _fontName.c_str();
}

void FontStyle::setFontName(const Char8 *name)
{
    _fontName = name;
}

bool FontStyle::dump(std::ostream &OSG_CHECK_ARG(out))
{
    return false;
}
