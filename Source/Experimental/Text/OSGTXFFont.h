#ifndef TXFFONT_H_
#define TXFFONT_H_

#include <OSGConfig.h>
#include <OSGBaseTypes.h>

#include "OSGFont.h"

#include <iostream>

OSG_BEGIN_NAMESPACE 

class OSG_SYSTEMLIB_DLLMAPPING TXFFont : public virtual Font
{
    typedef Font Inherited;

  public:

    struct txfChar
    {
        Int8    dimensions[6];
        Int16   x;
        Int16   y;
        UChar8  remapped;

        txfChar(void);
    };

  private:

    TXFFont(const TXFFont &obj);

  protected:

    Int32    _txfIsBitmap;
    Int32    _txfFontMaxAscent;
    Int32    _txfFontMaxDescent;
    Int32    _txfFontWidth;
    Int32    _txfFontHeight;
    Int32    _txfNumGlyphs;
    txfChar *_txfGlyphs;
    UChar8  *_txfImageMap;

    void initFromStream(std::istream &source);

  public:

    TXFFont(void);
    TXFFont(const Char8 *name, std::string path);
    TXFFont(const Char8 *name, std::istream &source);

    virtual ~TXFFont(void);

    virtual bool       initFont      (void        );
    virtual bool       createInstance(Text   *text);
    virtual FontStyle *createInstance(Real32  size);
};

OSG_END_NAMESPACE 

#include <OSGTXFFont.inl>

#endif // TXFFONT_H_
