// System declarations

#ifdef FREETYPE1_LIB

#ifdef __sgi
# include <math.h>
#else
# include <cmath>
#endif
#include <iostream>


// Application declarations
#include "freetype1/freetype/freetype.h.h"

// Class declarations
#include "OSGTTFontGlyph.h"




OSG_USING_NAMESPACE



// Static Class Variable implementations: 

TTFontGlyph::TTFontGlyph (void )
 : FontGlyph()
{
	return;
}

TTFontGlyph::TTFontGlyph (const TTFontGlyph &obj )
{
	return;
}

TTFontGlyph::TTFontGlyph (int ascii, int unicode)
: FontGlyph(ascii, unicode)
{
	return;
}


TTFontGlyph::~TTFontGlyph (void )
{
	return;
}

void TTFontGlyph::setupGlyph (int ascii, int unicode)
{
    setAsciiCode(ascii);
    setUniCode(unicode);
}



bool TTFontGlyph::createGlyph (void )
{
    if(!isValid()) return false;

    _ttError= TT_New_Glyph(*_ttFace, &_ttGlyph );
    if(_ttError) {
	cout << "ERROR: Create TT_New_Glyph failed"
	     << " with TT_Error=" << _ttError << endl;
	setInvalid();
	return false;
    }

    _ttError= TT_Load_Glyph(*_ttInstance,_ttGlyph, getUniCode(),
			    TTLOAD_DEFAULT );
    if(_ttError) {
	cout << "ERROR: Create TT_Load_Glyph failed"
	     << " with TT_Error=" << _ttError << endl;
	setInvalid();
	return false;
    }

    return true;
}




bool TTFontGlyph::getOutline(TT_Outline & ttOutline)
{
    _ttError= TT_Get_Glyph_Outline(_ttGlyph, &ttOutline );
    if(_ttError) {
	cout << "ERROR: Create TT_Get_Glyph_Outline failed"
	     << " with TT_Error=" << _ttError << endl;
	setInvalid();
	return false;
    }

    return true;
}




bool TTFontGlyph::setSizes (float *_boundingBox, float & _advance)
{
    TT_Get_Glyph_Metrics(_ttGlyph, &_ttGlyphMetrics );

    _advance = (_ttGlyphMetrics.advance/64);

    _boundingBox[0]= _ttGlyphMetrics.bbox.xMin/64;
    _boundingBox[1]= _ttGlyphMetrics.bbox.xMax/64;
    _boundingBox[2]= _ttGlyphMetrics.bbox.yMin/64;
    _boundingBox[3]= _ttGlyphMetrics.bbox.yMax/64;

    return true;
}



bool TTFontGlyph::setSizes (int *_boundingBox, int & _advance)
{
    TT_Get_Glyph_Metrics(_ttGlyph, &_ttGlyphMetrics );
    TT_BBox& bbox= _ttGlyphMetrics.bbox;

    bbox.xMin= bbox.xMin & -64;
    bbox.yMin= bbox.yMin & -64;
    bbox.xMax= (bbox.xMax+63) & -64;
    bbox.yMax= (bbox.yMax+63) & -64;

    _advance = ((_ttGlyphMetrics.advance+63) & - 64) / 64;

    _boundingBox[0]= bbox.xMin/64;
    _boundingBox[1]= bbox.xMax/64;
    _boundingBox[2]= bbox.yMin/64;
    _boundingBox[3]= bbox.yMax/64;

    return true;
}


bool TTFontGlyph::renderGlyph (TT_Raster_Map map, int xOff, int yOff)
{
    _ttError= TT_Get_Glyph_Pixmap(_ttGlyph, &map, xOff*64, yOff*64);

    if(_ttError) {
	cout << "ERROR: Create TT_Get_Glyph_Pixmap failed"
	     << " with TT_Error=" << _ttError << endl;
	setInvalid();
	return false;
    }

    return true;
}

#endif // FREETYPE1_LIB
