// System declarations

#ifdef FREETYPE1_LIB

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


// Application declarations
#include "freetype1/freetype/freetype.h.h"

// Class declarations
#include "OSGTTImageFontGlyph.h"




OSG_USING_NAMESPACE



// Static Class Variable implementations: 

TTImageFontGlyph::TTImageFontGlyph (void )
 : ImageFontGlyph(), TTFontGlyph()
{
	return;
}

TTImageFontGlyph::TTImageFontGlyph (const TTImageFontGlyph &obj )
{
	return;
}

TTImageFontGlyph::TTImageFontGlyph (IGlyphType type, int ascii, int unicode)
: ImageFontGlyph(type), TTFontGlyph(ascii, unicode)
{
	return;
}


TTImageFontGlyph::~TTImageFontGlyph (void )
{
	return;
}

void TTImageFontGlyph::setup (IGlyphType type, int ascii, int unicode)
{
    setupGlyph(ascii, unicode);
    setType(type);
}



bool TTImageFontGlyph::create (void )
{
    int size;
    TT_Raster_Map ttMap;
    bool retVal;

    if(_pixmapBuffer) return true;

    if(!createGlyph()) return(false);

    setSizes(_boundingBox, _advance);

    _imageSize[0] = _boundingBox[1] - _boundingBox[0];
    _imageSize[1] = _boundingBox[3] - _boundingBox[2];
    _imageSize[2]= (_imageSize[0]+3) & -4;

    size= _imageSize[2] * _imageSize[1];
    
    if( size <= 0 ) {
	glyphDone();
	return true;
    }

    _pixmapBuffer= new unsigned char [ size ];
    memset( (void*) _pixmapBuffer, 0, size );
    
    ttMap.width = _imageSize[0];
    ttMap.rows  = _imageSize[1];
    ttMap.cols  = _imageSize[2];
    ttMap.flow  = TT_Flow_Down;
    ttMap.size  = size;
    ttMap.bitmap= (void*) _pixmapBuffer;

    retVal = renderGlyph(ttMap, -_boundingBox[0], -_boundingBox[2]);

    glyphDone();

    return(retVal);
}

#endif // FREETYPE1_LIB
