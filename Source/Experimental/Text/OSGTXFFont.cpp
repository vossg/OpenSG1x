
#include <OSGConfig.h>

#ifdef __sgi
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#else
#include <cstdio>
#include <cstdlib>
#include <cstring>
#endif

#include <iostream>

#include <OSGLog.h>

#include "OSGTXFFontStyle.h"
#include "OSGText.h"
#include "OSGTXFGlyphInfo.h"

#include "OSGTXFFont.h"

OSG_USING_NAMESPACE 

bool sRead(std::istream &file, 
           void         *value, 
           Int32         size,
           bool          swapit)
{
    Char8 buffer[4];

    if(size > 4)
        return false;

    if(swapit)
    {
        file.read(buffer, size);

        for(Int32 i = 0; i < size; i++)
        {
            ((Char8 *) value)[i] = buffer[size - i - 1];
        }
    }
    else
    {
        file.read (static_cast<Char8 *>(value), size);
    }

    return !file.fail();
}

TXFFont::TXFFont(void) :
     Inherited        (    ),
    _txfIsBitmap      (   0),
    _txfFontMaxAscent (   0),
    _txfFontMaxDescent(   0),
    _txfFontWidth     (   0),
    _txfFontHeight    (   0),
    _txfNumGlyphs     (   0),
    _txfGlyphs        (NULL),
    _txfImageMap      (NULL)

{
}

TXFFont::TXFFont(const Char8 *name, std::string path) :
     Inherited        (name, 
                       path),
    _txfIsBitmap      (   0),
    _txfFontMaxAscent (   0),
    _txfFontMaxDescent(   0),
    _txfFontWidth     (   0),
    _txfFontHeight    (   0),
    _txfNumGlyphs     (   0),
    _txfGlyphs        (NULL),
    _txfImageMap      (NULL)
{
}

TXFFont::TXFFont(const Char8 *name, std::istream &source) :
     Inherited        (name),
    _txfIsBitmap      (   0),
    _txfFontMaxAscent (   0),
    _txfFontMaxDescent(   0),
    _txfFontWidth     (   0),
    _txfFontHeight    (   0),
    _txfNumGlyphs     (   0),
    _txfGlyphs        (NULL),
    _txfImageMap      (NULL)
{
    _valid = true;
    initFromStream(source);
}

TXFFont::~TXFFont(void)
{
    delete [] _txfGlyphs;
    delete [] _txfImageMap;
}

void TXFFont::initFromStream(std::istream &source)
{
    bool    swapit;
    UChar8  u_magic, *imageBuffer = NULL;
    Char8   c_magic[3];
    UInt32  ibuff, bitWidth = 0, stride;
    UInt16  sbuff;
    Int32   i, j;

    // checking filetype
    source >> u_magic;

    if(!(u_magic == 0xff))
        _valid = false;

    source.read(c_magic, 3);

    if(strncmp(c_magic, "txf", 3))
        _valid = false;

    source.read(reinterpret_cast < Char8 * > (&ibuff), 4);
    swapit = (ibuff == 0x12345678 ? false : true);

    if(swapit && (ibuff - 0x78563412))
        _valid = false;

    _valid &= sRead(source, &_txfIsBitmap, 4, swapit);
    _valid &= sRead(source, &_txfFontWidth, 4, swapit);
    _valid &= sRead(source, &_txfFontHeight, 4, swapit);
    _valid &= sRead(source, &_txfFontMaxAscent, 4, swapit);
    _valid &= sRead(source, &_txfFontMaxDescent, 4, swapit);
    _valid &= sRead(source, &_txfNumGlyphs, 4, swapit);

    _valid &= !(_txfIsBitmap > 1);

    _txfFontMaxDescent = 
        _txfFontMaxDescent > 0 ? _txfFontMaxDescent * -1 : _txfFontMaxDescent;

    if(!_valid)
        return;

    // read content: glyph info
    _txfGlyphs = new txfChar[256];

    for(i = 0; i < _txfNumGlyphs; i++)
    {
        _valid &= sRead(source, &sbuff, 2, swapit);
        source.read((Char8 *) _txfGlyphs[(UChar8) sbuff].dimensions, 6);
        _valid &= sRead(source, &_txfGlyphs[(UChar8) sbuff].x, 2, swapit);
        _valid &= sRead(source, &_txfGlyphs[(UChar8) sbuff].y, 2, swapit);
        _txfGlyphs[(UChar8) sbuff].remapped = 0;

        if(!_valid)
        {
            delete [] _txfGlyphs;

            _txfGlyphs = NULL;

            return;
        }
    }

    if(_txfIsBitmap)
    {
        bitWidth = (_txfFontWidth + 7) / 8;
        imageBuffer = new UChar8[bitWidth * _txfFontHeight];
        source.read(reinterpret_cast < Char8 * > (imageBuffer),
                            bitWidth * _txfFontHeight);
    }
    else
    {
        imageBuffer = new UChar8[_txfFontWidth * _txfFontHeight];
        source.read(reinterpret_cast < Char8 * > (imageBuffer),
                            _txfFontWidth * _txfFontHeight);
    }

    _valid &= !source.fail();

    if(!_valid)
    {
        delete [] _txfGlyphs;
        delete [] imageBuffer;

        _txfGlyphs   = NULL;
         imageBuffer = NULL;

        return;
    }

    _txfImageMap = new UChar8[_txfFontWidth * _txfFontHeight * 2];

    stride = 0;

    if(_txfIsBitmap)
    {
        for(i = 0; i < _txfFontHeight; i++)
        {
            for(j = 0; j < _txfFontWidth; j++, stride += 2)
            {
                _txfImageMap[stride] = _txfImageMap[stride + 1] = 
                    imageBuffer[i * bitWidth + (j >> 3)] & 
                    (1 << (j & 7)) ? 255 : 0;
            }
        }
    }
    else
    {
        for(i = 0; i < _txfFontHeight; i++)
        {
            for(j = 0; j < _txfFontWidth; j++, stride += 2)
            {
                _txfImageMap[stride] = 
                    _txfImageMap[stride + 1] = imageBuffer[stride >> 1];
            }
        }
    }

    delete [] imageBuffer;
}

bool TXFFont::initFont(void)
{
    std::ifstream    source;

    if(_valid)
        return true;

    if(!_fontName || _fontPath.empty())
    {
        FWARNING(("No FontName or no path specified."));
        return false;
    }

    _valid = true;

	source.open(_fontPath.data(), std::ios_base::in | std::ios_base::binary );
    initFromStream(source);
    source.close();

    return _valid;
}

bool TXFFont::createInstance(Text *fs)
{
    bool           retVal = false;
    TXFFontStyle *fInst   = new TXFFontStyle;

    fInst->setFontName    (_fontName         );
    fInst->setMaxAscent   (_txfFontMaxAscent );
    fInst->setMaxDescent  (_txfFontMaxDescent);
    fInst->setBaselineSkip(
        ((Real32)(_txfFontMaxAscent - _txfFontMaxDescent)) / fInst->getYRes());

    fInst->setSize(fs->size());

    retVal = fInst->setTXFInstance(_txfFontWidth, 
                                   _txfFontHeight, 
                                   _txfGlyphs,
                                   _txfImageMap);
    if(!retVal)
    {
        delete fInst;
        fInst = NULL;
    }
    else
    {
        fs->setFontStyle(fInst);
    }

    return retVal;
}

OSG::FontStyle *TXFFont::createInstance(Real32 size)
{
    bool          retVal = false;
    TXFFontStyle *fInst  = new TXFFontStyle;

    fInst->setFontName    (_fontName         );
    fInst->setSize        ( size             );
    fInst->setMaxAscent   (_txfFontMaxAscent );
    fInst->setMaxDescent  (_txfFontMaxDescent);
    fInst->setBaselineSkip(
        ((Real32)(_txfFontMaxAscent - _txfFontMaxDescent)) / fInst->getYRes());

    retVal = fInst->setTXFInstance(_txfFontWidth, 
                                   _txfFontHeight, 
                                   _txfGlyphs, 
                                   _txfImageMap);

    if(!retVal)
    {
        delete fInst;
        fInst = NULL;
    }

    return fInst;
}
