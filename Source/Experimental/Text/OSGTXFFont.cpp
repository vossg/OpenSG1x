
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

    bool failed = file.fail();
    return !failed;
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
    bool    swapit, valid = true;
    UChar8  u_magic, *imageBuffer = NULL;
    Char8   c_magic[3];
    UInt32  ibuff, bitWidth = 0, stride;
    UInt16  sbuff;
    Int32   i, j;

    valid &= !source.fail();
    // checking sourcetype
    source >> u_magic;
    valid &= !source.fail();

    if(!(u_magic == 0xff))
        valid = false;

    source.read(c_magic, 3);
    valid &= !source.fail();

    if(strncmp(c_magic, "txf", 3))
        valid = false;

    source.read(reinterpret_cast < Char8 * > (&ibuff), 4);
    valid &= !source.fail();
    swapit = (ibuff == 0x12345678 ? false : true);

    if(swapit && (ibuff - 0x78563412))
        valid = false;
        
    valid &= sRead(source, &_txfIsBitmap, 4, swapit);
    valid &= sRead(source, &_txfFontWidth, 4, swapit);
    valid &= sRead(source, &_txfFontHeight, 4, swapit);
    valid &= sRead(source, &_txfFontMaxAscent, 4, swapit);
    valid &= sRead(source, &_txfFontMaxDescent, 4, swapit);
    valid &= sRead(source, &_txfNumGlyphs, 4, swapit);

    valid &= !(_txfIsBitmap > 1);

    _txfFontMaxDescent = 
        _txfFontMaxDescent > 0 ? _txfFontMaxDescent * -1 : _txfFontMaxDescent;

    if(!valid)
    {
        _valid = valid;
        return;
    }
    
    // read content: glyph info
    _txfGlyphs = new txfChar[256];

    for(i = 0; i < _txfNumGlyphs; i++)
    {
        valid &= sRead(source, &sbuff, 2, swapit);
        source.read((Char8 *) _txfGlyphs[(UChar8) sbuff].dimensions, 6);
        valid &= sRead(source, &_txfGlyphs[(UChar8) sbuff].x, 2, swapit);
        valid &= sRead(source, &_txfGlyphs[(UChar8) sbuff].y, 2, swapit);
        _txfGlyphs[(UChar8) sbuff].remapped = 0;

        if(!valid)
        {
            delete [] _txfGlyphs;

            _txfGlyphs = NULL;
            _valid = valid;

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

    valid &= !source.fail();

    if(!valid)
    {
        delete [] _txfGlyphs;
        delete [] imageBuffer;

        _txfGlyphs   = NULL;
         imageBuffer = NULL;
        _valid = valid;

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

    if(_fontName.empty() || _fontPath.empty())
    {
        FWARNING(("No FontName or no path specified."));
        return false;
    }

    _valid = true;

#ifdef OSG_GCC_NO_IOS_BASE
	source.open(_fontPath.data(), std::ios::in | std::ios::binary );
#else
	source.open(_fontPath.data(), std::ios_base::in | std::ios_base::binary );
#endif

    initFromStream(source);
    source.close();

    return _valid;
}

bool TXFFont::createInstance(Text *fs)
{
    bool           retVal = false;
    TXFFontStyle *fInst   = new TXFFontStyle;

    fInst->setFontName    (_fontName.c_str() );
    fInst->setMaxAscent   (Real32(_txfFontMaxAscent) );
    fInst->setMaxDescent  (Real32(_txfFontMaxDescent));
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

    fInst->setFontName    (_fontName.c_str() );
    fInst->setSize        ( size             );
    fInst->setMaxAscent   (Real32(_txfFontMaxAscent ));
    fInst->setMaxDescent  (Real32(_txfFontMaxDescent));
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
