
#include <OSGConfig.h>
#include <iostream>

#ifdef OSG_WITH_FREETYPE1
#include "OSGTTFont.h"
#endif

#include "OSGTXFFont.h"

#include "OSGFontFactory.h"

OSG_USING_NAMESPACE

OSG::FontFactory OSG::FontFactory:: _the;

FontFactory::FontFactory(void) :
    _knownFonts()
{
}

FontFactory::~FontFactory(void)
{
}

Font *FontFactory::queryFont(PathHandler &paths, const Char8 *fontName)
{
    std::list<Font *>::iterator  fIter;
    std::string                  fontFile;
    Font                        *tmpFont = 0;

    if(fontName && *fontName)
    {
        for(fIter = _knownFonts.begin(); fIter != _knownFonts.end(); fIter++)
        {
            if(!strcmp(fontName, (*fIter)->getName()))
                return *fIter;
        }

        fontFile = paths.findFile(fontName);

        if(fontFile.empty() == false)
        {
            switch(*(fontName + strlen(fontName) - 2))
            {
#ifdef OSG_WITH_FREETYPE1
            case 't':
            case 'T':
                tmpFont = new TTFont(fontName, fontFile);
                break;
#endif // OSG_WITH_FREETYPE1
            case 'x':
            case 'X':
                tmpFont = new TXFFont(fontName, fontFile);
                break;
            default:
                tmpFont = NULL;
            }

            _knownFonts.push_back(tmpFont);
        }
    }

    return tmpFont;
}

