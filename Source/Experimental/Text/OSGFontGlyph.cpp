
#include <OSGConfig.h>

#include <iostream>

#include "OSGFontGlyph.h"

OSG_USING_NAMESPACE 

FontGlyph::FontGlyph(void) :
    _valid    (true),
    _asciiCode(-1  ),
    _uniCode  (-1  ),
    _size     (1.f )
{
}

FontGlyph::FontGlyph(Int32 ascii, Int32 unicode) :
    _valid    (true   ),
    _asciiCode(ascii  ),
    _uniCode  (unicode),
    _size     (1.f    ) 
{
}

FontGlyph::~FontGlyph(void)
{
}

bool FontGlyph::isValid(void)
{
    return _valid;
}

void FontGlyph::setInvalid(void)
{
    _valid = false;
}

Int32 FontGlyph::getAsciiCode(void)
{
    return _asciiCode;
}

void FontGlyph::setAsciiCode(Int32 asciiCode)
{
    _asciiCode = asciiCode;
}

Int32 FontGlyph::getUniCode(void)
{
    return _uniCode;
}

void FontGlyph::setUniCode(Int32 uniCode)
{
    _uniCode = uniCode;
}

void FontGlyph::setSize(Real32 size)
{
    _size = size;
}

Real32 FontGlyph::getSize(void)
{
    return _size;
}


