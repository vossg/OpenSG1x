// System declarations
#include <iostream>


// Application declarations


// Class declarations
#include "OSGFontStyle.h"
#include "OSGFontGlyph.h"

// Static Class Variable implementations: 


OSG_USING_NAMESPACE



FontStyle::FontStyle (void )
  : _xRes(72), _yRes(72), _size(1), _fontName(0), _txfImageMap(NULL)
{
    _vectorGlyphs.reserve(256);
    _imageGlyphs.reserve(256);
    return;
}

/*
FontStyle::FontStyle (const FontStyle &obj )
{
	return;
}
*/

FontStyle::~FontStyle (void )
{
	return;
}

bool FontStyle::processChange (void )
{
	return false;
}


bool FontStyle::getTXFImageSizes (int &width, int &height)
{
  width = _txfFontWidth;
  height = _txfFontHeight;

  return width*height > 0;
}
