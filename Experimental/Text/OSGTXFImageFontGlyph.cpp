// System declarations
#ifdef __sgi
# include <stdlib.h>
# include <stdio.h>
# include <stdio.h>
# include <string.h>
#else
# include <cstdlib>
# include <cstdio>
# include <cstring>
#endif
#include <iostream>


// Class declarations
#include "OSGTXFImageFontGlyph.h"




OSG_USING_NAMESPACE



TXFImageFontGlyph::TXFImageFontGlyph (void )
 : ImageFontGlyph(), TXFFontGlyph()
{
	return;
}

/*
TXFImageFontGlyph::TXFImageFontGlyph (const TXFImageFontGlyph &obj )
{
	return;
}
*/

TXFImageFontGlyph::TXFImageFontGlyph (IGlyphType type, int ascii, int unicode)
: ImageFontGlyph(type), TXFFontGlyph(ascii, unicode)
{
	return;
}

TXFImageFontGlyph::~TXFImageFontGlyph (void )
{
	return;
}

void TXFImageFontGlyph::setup (IGlyphType type, int ascii, int unicode)
{
    setupGlyph(ascii, unicode);
    setType(type);
}



void TXFImageFontGlyph::setFontDefs(short x, short y, char *dimensions)
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



void TXFImageFontGlyph::setFontSource(unsigned char *srcImage, int width, int height)
{
  _srcImage = srcImage;
  _srcWidth = width;
  _srcHeight = height;
}




bool TXFImageFontGlyph::create (void )
{
  if(_pixmapBuffer) return true;
    
  _pixmapBuffer = new unsigned char[_imageSize[0]*_imageSize[1]];

  for(int i=_yOff, k=0; i< _yOff+_imageSize[1]; i++, k++)
    for(int j=_xOff*2, l=0; j< _xOff*2+_imageSize[0]*2; j+=2, l++)
      _pixmapBuffer[(_imageSize[1]-k-1)*_imageSize[0]+l] =
	(_srcImage[i*_srcWidth*2+j])/64;

    return(true);
}
