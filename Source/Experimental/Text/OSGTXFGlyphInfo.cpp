
#include <OSGConfig.h>

#ifdef __sgi
#include <stdlib.h>
#else
#include <cstdlib>
#endif

#include "OSGTXFGlyphInfo.h"

OSG_USING_NAMESPACE 

TXFGlyphInfo::TXFGlyphInfo(void) :
    _advance   (0.f ),
    _dimensions(NULL),
    _offset    (NULL),
    _remapped  (0   )
{
    for(UInt32 i = 0; i < 4; ++i)
    {
        _tCoords[i][0] = 0.f;
        _tCoords[i][1] = 0.f;

        _vCoords[i][0] = 0.f;
        _vCoords[i][1] = 0.f;
    }
}

TXFGlyphInfo::~TXFGlyphInfo(void)
{
}

void TXFGlyphInfo::remap(UInt8 dest)
{
    _remapped = dest;
}

UInt8 TXFGlyphInfo::remapped(void)
{
    return _remapped;
}

bool TXFGlyphInfo::setTextureCoords(Int8   corner, 
                                    Real32 x,
                                    Real32 y)
{
    bool    retCode;

    if((corner < 0) || (corner > 3))
    {
        retCode = false;
    }
    else
    {
        _tCoords[corner][0] = x;
        _tCoords[corner][1] = y;

        retCode = true;
    }

    return retCode;
}

Real32 *TXFGlyphInfo::getTextureCoords(Int8 corner)
{
    if(corner > 3)
        return NULL;

    return _tCoords[corner];
}

bool TXFGlyphInfo::setVertexCoords(Int8 corner, Real32 x, Real32 y)
{
    bool    retCode;

    if((corner < 0) || (corner > 3))
    {
        retCode = false;
    }
    else
    {
        _vCoords[corner][0] = x;
        _vCoords[corner][1] = y;
        retCode = true;
    }

    return retCode;
}

Real32 *TXFGlyphInfo::getVertexCoords(Int8 corner)
{
    if(corner > 3)
        return NULL;

    return _vCoords[corner];
}

void TXFGlyphInfo::setAdvance(Real32 advance)
{
    _advance = advance;
}

Real32 TXFGlyphInfo::getAdvance(void)
{
    return _advance;
}

void TXFGlyphInfo::setDimensions(Int8 *dims)
{
    _dimensions = dims;
}

Int8 *TXFGlyphInfo::getDimensions(void)
{
    return _dimensions;
}

void TXFGlyphInfo::setOffset(Int16 *off)
{
    _offset = off;
}

Int16 *TXFGlyphInfo::getOffset(void)
{
    return _offset;
}
