
#include <OSGConfig.h>

#ifdef __sgi
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#else
#include <cstdlib>
#include <cstdio>
#include <cstring>
#endif

#include <iostream>

#include "OSGTXFImageFontGlyph.h"

OSG_USING_NAMESPACE 

TXFImageFontGlyph::TXFImageFontGlyph(void) :
     ImageFontGlyph(    ),
     TXFFontGlyph  (    ),
    _srcImage      (NULL),
    _srcWidth      (0   ),
    _srcHeight     (0   ),
    _xOff          (0   ),
    _yOff          (0   )
{
}

TXFImageFontGlyph::TXFImageFontGlyph(IGlyphType type, 
                                     Int32      ascii, 
                                     Int32      unicode) :
     ImageFontGlyph(type   ),
     TXFFontGlyph  (ascii, 
                    unicode),
    _srcImage      (NULL   ),
    _srcWidth      (0      ),
    _srcHeight     (0      ),
    _xOff          (0      ),
    _yOff          (0      )

{
}

TXFImageFontGlyph::~TXFImageFontGlyph(void)
{
}

void TXFImageFontGlyph::setup(IGlyphType type, Int32 ascii, Int32 unicode)
{
    setupGlyph(ascii, unicode);
    setType(type);
}

void TXFImageFontGlyph::setFontDefs(Int16 x, Int16 y, Int8 *dimensions)
{
    _xOff = x;
    _yOff = y;

    _boundingBox[0] = dimensions[2];
    _boundingBox[1] = dimensions[2] + dimensions[0];
    _boundingBox[2] = dimensions[3];
    _boundingBox[3] = dimensions[3] + dimensions[1];

    _imageSize[0] = dimensions[0];
    _imageSize[1] = dimensions[1];
    _imageSize[2] = dimensions[0];

    _advance = dimensions[4];
}

void TXFImageFontGlyph::setFontSource(UChar8 *srcImage, 
                                      Int32   width, 
                                      Int32   height)
{
    _srcImage = srcImage;
    _srcWidth = width;
    _srcHeight = height;
}

bool TXFImageFontGlyph::create(void)
{
    if(_pixmapBuffer)
        return true;

    _pixmapBuffer = new UChar8[_imageSize[0] * _imageSize[1]];

    for(Int32 i = _yOff, k = 0; i < _yOff + _imageSize[1]; i++, k++)
    {
        for(Int32 j = _xOff * 2, l = 0; j < _xOff * 2 + _imageSize[0] * 2;
                    j += 2, l++)
        {
            _pixmapBuffer[(_imageSize[1] - k - 1) * _imageSize[0] + l] =
                (_srcImage[i * _srcWidth * 2 + j]) /
                64;
        }
    }

    return true;
}
