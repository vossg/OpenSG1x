#ifndef WIN32

// System declarations
#ifdef __sgi
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
#else
# include <cstdio>
# include <cstdlib>
# include <cstring>
#endif
#include <iostream>


// Application declarations
#include "OSGTXFFontStyle.h"
#include "OSGText.h"
#include "OSGTXFGlyphInfo.h"

// Class declarations
#include "OSGTXFFont.h"



bool sRead(istream &file, void *value, int size, bool swapit)
{
  char buffer[4];

  if(size>4) return false;

  if(swapit) {
    file.read(buffer, size);

    for(int i=0;i<size;i++)
      ((char *)value)[i] = buffer[size-i-1];
  }
  else
    file.read(static_cast<char*>(value), size);

  return !file.fail();
}


OSG_USING_NAMESPACE



// Static Class Variable implementations: 


TXFFont::TXFFont (void )
: Font ( )
{
	return;
}

/*
TXFFont::TXFFont (const TXFFont &obj )
{
    return;
}
*/

TXFFont::TXFFont (const char *name, string path )
: Font (name, path )
{
    return;
}


TXFFont::TXFFont (const char *name, istream & source )
: Font (name)
{
  _valid = true;
  initFromStream(source);
  return;
}


TXFFont::~TXFFont (void )
{
    if(_valid) {
      delete _txfGlyphs;
      delete _txfImageMap;
    }

    return;
}


void TXFFont::initFromStream (istream & source)
{
  bool swapit;
  unsigned char u_magic, *imageBuffer=NULL;
  char  c_magic[3];
  unsigned int ibuff, bitWidth, stride;
  unsigned short sbuff;
  int i, j;

  // checking filetype

  source >> u_magic;
  if(!(u_magic==0xff)) _valid = false;

  source.read(c_magic, 3);
  if(strncmp(c_magic, "txf", 3)) _valid = false;

  source.read(reinterpret_cast<char*>(&ibuff), 4);
  swapit = (ibuff == 0x12345678 ? false : true);

  if(swapit && (ibuff - 0x78563412)) _valid = false;

  _valid &= sRead(source, &_txfIsBitmap, 4, swapit);
  _valid &= sRead(source, &_txfFontWidth, 4, swapit);
  _valid &= sRead(source, &_txfFontHeight, 4, swapit);
  _valid &= sRead(source, &_txfFontMaxAscent, 4, swapit);
  _valid &= sRead(source, &_txfFontMaxDescent, 4, swapit);
  _valid &= sRead(source, &_txfNumGlyphs, 4, swapit);

  _valid &= !(_txfIsBitmap > 1);

  _txfFontMaxDescent = _txfFontMaxDescent > 0 ?
    _txfFontMaxDescent * -1 : _txfFontMaxDescent;

  if(!_valid) return;

  // read content: glyph info

  _txfGlyphs = new txfChar[256];
  for(i = 0; i < _txfNumGlyphs; i++) {
    _valid &= sRead(source, &sbuff, 2, swapit);
    source.read(_txfGlyphs[(unsigned char)sbuff].dimensions, 6);
    _valid &= sRead(source, &_txfGlyphs[(unsigned char)sbuff].x,
		     2, swapit);
    _valid &= sRead(source, &_txfGlyphs[(unsigned char)sbuff].y,
		     2, swapit);
    _txfGlyphs[(unsigned char)sbuff].remapped = 0;

    if(!_valid) {
      delete _txfGlyphs;
      return;
    }
  }


  if(_txfIsBitmap) {
    bitWidth = (_txfFontWidth + 7)/8;
    imageBuffer = new unsigned char [bitWidth*_txfFontHeight];
    source.read(reinterpret_cast<char*>(imageBuffer), bitWidth*_txfFontHeight);
  }
  else {
    imageBuffer = new unsigned char [_txfFontWidth*_txfFontHeight];
    source.read(reinterpret_cast<char*>(imageBuffer), _txfFontWidth*_txfFontHeight);
  }
  _valid &= !source.fail();

  if(!_valid) {
    delete _txfGlyphs;
    delete imageBuffer;
    return;
  }

  _txfImageMap = new unsigned char [_txfFontWidth*_txfFontHeight*2];

  stride = 0;
  if(_txfIsBitmap)
    for (i = 0; i < _txfFontHeight; i++)
      for (j = 0; j < _txfFontWidth; j++, stride+=2)
	_txfImageMap[stride] = _txfImageMap[stride+1] = 
	  imageBuffer[i * bitWidth + (j >> 3)] & (1 << (j & 7)) ? 255 : 0;
  else
    for (i = 0; i < _txfFontHeight; i++)
      for (j = 0; j < _txfFontWidth; j++, stride+=2)
	_txfImageMap[stride] = _txfImageMap[stride+1] = imageBuffer[stride >> 1];

  delete imageBuffer;

}


bool TXFFont::initFont (void)
{
    ifstream source;

    if(_valid) return(true);

    if(!_fontName || _fontPath.empty()) {
      cout << "ERROR: No FontName or no path specified!"  << endl;
      return(false);
    }

    _valid = true;

    source.open(_fontPath.data());
    initFromStream(source);
    source.close();

    return _valid;
}






bool TXFFont::createInstance (Text *fs)
{
    bool retVal=false;
    TXFFontStyle *fInst = new TXFFontStyle;

    fInst->setFontName(_fontName);
    fInst->setMaxAscent(_txfFontMaxAscent);
    fInst->setMaxDescent(_txfFontMaxDescent);
    fInst->setBaselineSkip(((float)(_txfFontMaxAscent - _txfFontMaxDescent))/fInst->getYRes());
    fInst->setSize(fs->size());

    retVal = fInst->setTXFInstance (_txfFontWidth, _txfFontHeight,
				    _txfGlyphs, _txfImageMap);
    if(!retVal) {
	delete fInst;
	fInst = 0;
    }
    else
	fs->setFontStyle(fInst);

    return retVal;
}




osg::FontStyle *TXFFont::createInstance(float size)
{
    bool retVal=false;
    TXFFontStyle *fInst = new TXFFontStyle;

    fInst->setFontName(_fontName);
    fInst->setSize(size);
    fInst->setMaxAscent(_txfFontMaxAscent);
    fInst->setMaxDescent(_txfFontMaxDescent);
    fInst->setBaselineSkip(((float)(_txfFontMaxAscent - _txfFontMaxDescent))/fInst->getYRes());

    retVal = fInst->setTXFInstance (_txfFontWidth, _txfFontHeight,
				    _txfGlyphs, _txfImageMap);

    if(!retVal) {
	delete fInst;
	fInst = 0;
    }

    return fInst;
}



#endif
