#ifndef TXFFONTINSTANCE_H_
#define TXFFONTINSTANCE_H_

#include <OSGConfig.h>
#include <OSGBaseTypes.h>

#include "OSGFontStyle.h"
#include "OSGTXFFont.h"

OSG_BEGIN_NAMESPACE 

class OSG_SYSTEMLIB_DLLMAPPING TXFFontStyle : public FontStyle
{

    typedef FontStyle Inherited;

  private:

    TXFFontStyle(const TXFFontStyle &obj);
    void operator =(const TXFFontStyle &obj);

  protected:
    
    virtual bool processChange  (void                       );
    virtual bool buildGlyphInfos(TXFFont::txfChar *txfGlyphs);

  public:

    TXFFontStyle(void);

    virtual ~TXFFontStyle(void);

    virtual bool            setTXFInstance(Int32             width, 
                                           Int32             height,
                                           TXFFont::txfChar *glyphList,
                                           UChar8           *imageMap );
    virtual TXFGlyphInfo    *getTXFGlyphInfo(UInt8           which    );

    virtual VectorFontGlyph *getVectorGlyph(UInt8            which    );
    virtual ImageFontGlyph  *getImageGlyph (UInt8            which    );
};

OSG_END_NAMESPACE 

#endif // TXFFONTINSTANCE_H_
