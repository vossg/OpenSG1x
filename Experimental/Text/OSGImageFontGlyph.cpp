#ifndef WIN32

// System declarations
#include <iostream>

// Class declarations
#include "OSGImageFontGlyph.h"

// Static Class Variable implementations: 


OSG_USING_NAMESPACE



ImageFontGlyph::ImageFontGlyph (void )
: _type(IGLYPH_NONE), _bitmapBuffer(0), _pixmapBuffer(0)
{
    return;
}

/*
ImageFontGlyph::ImageFontGlyph (const ImageFontGlyph &obj )
{
	return;
}
*/


ImageFontGlyph::ImageFontGlyph (IGlyphType type)
: _type(type), _bitmapBuffer(0), _pixmapBuffer(0)
{
    return;
}


ImageFontGlyph::~ImageFontGlyph (void )
{
    clear();

    if(_bitmapBuffer) delete _bitmapBuffer;
    if(_pixmapBuffer) delete _pixmapBuffer;

    return;
}

bool ImageFontGlyph::clear (void )
{
    return true;
}

#endif

