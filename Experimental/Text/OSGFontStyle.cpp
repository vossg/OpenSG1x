#ifndef WIN32

// System declarations
#include <iostream>


// Application declarations


// Class declarations
#include "OSGFontStyle.h"
#include "OSGFontGlyph.h"

// Static Class Variable implementations: 


OSG_USING_NAMESPACE



FontStyle::FontStyle(void)
  : _xRes(72), _yRes(72), _size(1), _fontName(0), _txfImageMap(NULL)
{
    _vectorGlyphs.reserve(256);
    _imageGlyphs.reserve(256);
    return;
}


FontStyle::FontStyle(const FontStyle &obj) :
    _xRes        (obj._xRes),
    _yRes        (obj._yRes),
    _size        (obj._size),
    _depth       (obj._depth),
    _maxDescent  (obj._maxDescent),
    _maxAscent   (obj._maxAscent),
    _baselineSkip(obj._baselineSkip),
    _fontName    (obj._fontName)
{
	return;
}


FontStyle::~FontStyle(void)
{
	return;
}

bool FontStyle::processChange(void)
{
	return false;
}


bool FontStyle::getTXFImageSizes (int &width, int &height)
{
  width = _txfFontWidth;
  height = _txfFontHeight;

  return width*height > 0;
}

#endif
