
#include <OSGConfig.h>

#include <iostream>

#include "OSGImageFontGlyph.h"

OSG_USING_NAMESPACE ImageFontGlyph::ImageFontGlyph(void) :
     Inherited   (           ),
    _type        (IGLYPH_NONE),
    _bitmapBuffer(NULL       ),
    _pixmapBuffer(NULL       )
{
}

ImageFontGlyph::ImageFontGlyph(IGlyphType type) :
     Inherited   (    ),
    _type        (type),
    _bitmapBuffer(NULL),
    _pixmapBuffer(NULL)
{
}

ImageFontGlyph::~ImageFontGlyph(void)
{
    clear();

    delete _bitmapBuffer;
    delete _pixmapBuffer;
}

bool ImageFontGlyph::clear(void)
{
    return true;
}

const Int32 *ImageFontGlyph::getBoundingBox(void)
{
    return _boundingBox;
}

const Int32 *ImageFontGlyph::getImageSize(void)
{
    return _imageSize;
}

Int32 ImageFontGlyph::getAdvance(void)
{
    return _advance;
}

UChar8 *ImageFontGlyph::getImage(void)
{
    return _type == IGLYPH_BIAP ? _bitmapBuffer : _pixmapBuffer;
}

IGlyphType ImageFontGlyph::getType(void)
{
    return _type;
}

void ImageFontGlyph::setType(IGlyphType type)
{
    _type = type;
}


