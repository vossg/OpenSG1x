
#include <OSGConfig.h>
#include <iostream>

#include "OSGFont.h"

OSG_USING_NAMESPACE

Font::Font(void) :
    _fontPath     (     ),
    _fontName     (     ),
    _valid        (false),
    _fontInstances(     )
{
}

Font::Font(const Char8 *name) :
    _fontPath     (     ),
    _fontName     (name ),
    _valid        (false),
    _fontInstances(     )
{
}

Font::Font(const Char8 *name, std::string path) :
    _fontPath     (path ),
    _fontName     (name ),
    _valid        (false),
    _fontInstances(     )
{
}

Font::~Font(void)
{
}
