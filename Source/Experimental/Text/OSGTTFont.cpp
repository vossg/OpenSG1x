
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

#ifdef OSG_WITH_FREETYPE1

#include "OSGTTFontStyle.h"
#include "OSGText.h"

#include "OSGTTFont.h"

OSG_USING_NAMESPACE

TTFont::TTFont(void) :
     Inherited(    ),
    _ttEngine (    ),
    _ttFace   (    ),
    _ttError  (0L  )
{
    _ttEngine.z = NULL;
    _ttFace  .z = NULL;
}

TTFont::TTFont(const Char8 *name, std::string path) :
     Inherited(name, 
               path),
    _ttEngine (    ),
    _ttFace   (    ),
    _ttError  (0L  )
{
    _ttFace.z = NULL;

    _ttError = TT_Init_FreeType(&_ttEngine);

    if(_ttError)
    {
        FWARNING(("Create TT_Engine failed with TT_Error=%d.", _ttError));
    }
}

TTFont::~TTFont(void)
{
    TT_Done_FreeType(_ttEngine);
}

bool TTFont::initFont(void)
{
    if(_valid)
        return true;

    if(_fontName.empty() || _fontPath.empty())
    {
        FWARNING(("No FontName or no path specified."));
        return false;
    }

    _valid = true;

    _ttError = TT_Open_Face(_ttEngine, _fontPath.data(), &_ttFace);

    if(_ttError)
    {
        FWARNING(("Create TT_Face failed for font %s with TT_Error=%d.",
                             _fontPath.c_str(), _ttError));
        _valid = false;
    }

    return _valid;
}

bool TTFont::createInstance(Text *fs)
{
    bool         retVal = false;
    TT_Instance *inst   = new TT_Instance;
    TTFontStyle *fInst  = new TTFontStyle;

    fInst->setFontName(_fontName.c_str());
    fInst->setSize    (fs->size()       );

    retVal = fInst->set_ttInstance(inst, &_ttFace);

    if(!retVal)
    {
        delete inst;
        delete fInst;
    }
    else
    {
        fs->setFontStyle(fInst);
    }

    return retVal;
}

OSG::FontStyle *TTFont::createInstance(Real32 size)
{
    bool         retVal = false;
    TT_Instance *inst   = new TT_Instance;
    TTFontStyle *fInst  = new TTFontStyle;

    fInst->setFontName(_fontName.c_str());
    fInst->setSize    (size             );

    retVal = fInst->set_ttInstance(inst, &_ttFace);

    if(!retVal)
    {
        delete inst;
        delete fInst;

        fInst = NULL;
    }
    return fInst;
}

#endif // OSG_WITH_FREETYPE1
