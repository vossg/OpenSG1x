#ifndef WIN32

// System declarations
#ifdef __sgi
# include <math.h>
#else
# include <cmath>
#endif
#include <iostream>


// Application declarations
#include "OSGTXFImageFontGlyph.h"

// Class declarations
#include "OSGTXFFontStyle.h"



OSG_USING_NAMESPACE



// Static Class Variable implementations: 


TXFFontStyle::TXFFontStyle (void )
  : FontStyle ()
{
	return;
}

TXFFontStyle::TXFFontStyle (const TXFFontStyle &obj )
  : FontStyle(obj)
{
	return;
}

TXFFontStyle::~TXFFontStyle (void )
{
	return;
}

ImageFontGlyph * TXFFontStyle::getImageGlyph (UInt8 ascii)
{
    return _imageGlyphs[ascii];
}


TXFGlyphInfo * TXFFontStyle::getTXFGlyphInfo (UInt8 which)
{
  if(which >= _txfGlyphInfos.size())
    return _txfGlyphInfos[_txfGlyphInfos[0]->remapped()];

  if(_txfGlyphInfos[which]->remapped()) 
    return _txfGlyphInfos[_txfGlyphInfos[which]->remapped()];

  return _txfGlyphInfos[which];
}


bool TXFFontStyle::processChange (void)
{
	return false;
}



bool TXFFontStyle::buildGlyphInfos (TXFFont::txfChar *txfGlyphs)
{
  Real32 x, y, xstep, ystep;
  TXFGlyphInfo *glyph;
  TXFFont::txfChar *current;
  Int32 i;

  xstep = 0.5 / _txfFontWidth;
  ystep = 0.5 / _txfFontHeight;

  for(i=0; i < 256; i++) {
    glyph = new TXFGlyphInfo();
    _txfGlyphInfos.push_back(glyph);
    current = &txfGlyphs[i];

    if(current->remapped) {
      glyph->remap(current->remapped);
      continue;
    }

// 		cerr << (char) i << endl;


    x = (Real32)current->x / (Real32)_txfFontWidth + xstep;
    y = (Real32)current->y / (Real32)_txfFontHeight + ystep;
    glyph->setTextureCoords(0, x, y);

    x += (Real32)(current->dimensions[0]) / (Real32)_txfFontWidth;
    glyph->setTextureCoords(1, x, y);

    y += (Real32)(current->dimensions[1]) / (Real32)_txfFontHeight;
    glyph->setTextureCoords(2, x, y);

    x = (Real32)current->x / (Real32)_txfFontWidth + xstep;
    glyph->setTextureCoords(3, x, y);


    x = (Real32)current->dimensions[2];
    y = (Real32)current->dimensions[3];
    glyph->setVertexCoords(0, x, y);

// 		cerr << x << ", " << y << endl;

    x += (Real32)current->dimensions[0];
    glyph->setVertexCoords(1, x, y);

// 		cerr << x << ", " << y << endl;

    y += (Real32)current->dimensions[1];
    glyph->setVertexCoords(2, x, y);

// 		cerr << x << ", " << y << endl;

    x = (Real32)current->dimensions[2];
    glyph->setVertexCoords(3, x, y);

// 		cerr << x << ", " << y << endl;


    glyph->setAdvance(current->dimensions[4]);
  }

  return true;
}



bool TXFFontStyle::setTXFInstance (Int32 width, Int32 height,
				   TXFFont::txfChar *glyphList,
				   UChar8 *imageMap)
{
    TXFFont::txfChar *current;

    TXFImageFontGlyph *iGlyphs = new TXFImageFontGlyph[256];
    for(Int32 i= 0; i < 256; i++) {
      current = glyphList[i].remapped ? 
	&(glyphList[glyphList[i].remapped]) : &(glyphList[i]);

      iGlyphs[i].setup(IGLYPH_PIXMAP, i, i);
      iGlyphs[i].setFontDefs(current->x, current->y, current->dimensions);
      iGlyphs[i].setFontSource(imageMap, width, height);
      iGlyphs[i].setSize(getSize());
      _imageGlyphs.push_back(&iGlyphs[i]);
    }

    _txfFontWidth = width;
    _txfFontHeight = height;

    setTXFImageMap(imageMap);

    buildGlyphInfos(glyphList);

    return true;
}

#endif
