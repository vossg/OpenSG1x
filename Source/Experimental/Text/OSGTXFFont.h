#ifndef TXFFONT_CLASS_DECLARATION
#define TXFFONT_CLASS_DECLARATION

#ifndef WIN32
#include <OSGConfig.h>
#include <OSGBaseTypes.h>

#include "OSGFont.h"
#include "OSGTXFGlyphInfo.h"

#include <iostream>

OSG_BEGIN_NAMESPACE class TXFFont :
    public virtual Font
{
    typedef Font    ParentClass;
public:

    struct txfChar
    {
        Int8    dimensions[6];
        Int16   x, y;
        UChar8  remapped;
        txfChar (void)
        :
        remapped(' ')
        { ;
        }
    };
private:

    Int32               _txfIsBitmap;
    Int32               _txfFontMaxAscent;
    Int32               _txfFontMaxDescent;
    Int32               _txfFontWidth;
    Int32               _txfFontHeight;
    Int32               _txfNumGlyphs;
    txfChar             *_txfGlyphs;
    UChar8              *_txfImageMap;
protected:

    void                initFromStream(std::istream &source);
public:

    /** Default Constructor */
    TXFFont(void);

    /** Copy Constructor */
    TXFFont(const TXFFont &obj);

    /** Constructor */
    TXFFont(const Char8 *name, std::string path);

    /** Constructor */
    TXFFont(const Char8 *name, std::istream &source);

    /** Destructor */
    virtual             ~TXFFont(void);

    /** loading and storing of font-contents */
    bool                initFont(void);

    /** creates FontStyle aka FontStyle */
    virtual bool        createInstance(Text *text);

    /** creates FontStyle */
    virtual FontStyle   *createInstance(Real32 size);
};

OSG_END_NAMESPACE typedef osg::TXFFont * TXFFontP;
#endif
#endif // TXFFONT_CLASS_DECLARATION
