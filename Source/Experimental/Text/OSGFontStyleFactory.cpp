
#include <OSGConfig.h>

#include <iostream>

#ifdef __sgi
#include <assert.h>
#else
#include <cassert>
#endif
#include <OSGLog.h>

#include "OSGFontStyle.h"
#include "OSGFont.h"
#include "OSGFontFactory.h"

#include "OSGFontStyleFactory.h"

OSG_USING_NAMESPACE

FontStyleFactory FontStyleFactory:: _the;

FontStyleFactory::FontStyleFactory(void) :
    _instances()
{
}

FontStyleFactory &FontStyleFactory::the(void)
{
    return _the;
}

FontStyleFactory::~FontStyleFactory(void)
{
}

OSG::FontStyle *FontStyleFactory::create(      PathHandler &paths, 
                                         const Char8       *fontName, 
                                               Real32       size    )
{
    std::list<FontStyle *>::const_iterator pos;

    for(pos = _instances.begin(); pos != _instances.end(); ++pos)
    {
        if(((*pos)->getSize() == size) &&
           !strcmp((*pos)->getFontName(), fontName))
        {
            return *pos;
        }
    }

    Font *font = FontFactory::the().queryFont(paths, fontName);

    if(!font)
    {
        FWARNING(("Font named %s unknown.", fontName));
        return 0;
    }

    if(!font->initFont())
    {
        FWARNING(("Initialization failed for font %s.", fontName));
        return 0;
    }

    FontStyle *fi = font->createInstance(size);

    if(fi == 0)
    {
        FWARNING(("Instancing failed for font %s.", fontName));
        return 0;
    }

    _instances.push_back(fi);

    return fi;
}

bool FontStyleFactory::discard(FontStyle *)
{
    return false;
}


