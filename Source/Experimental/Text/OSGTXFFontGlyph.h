#ifndef TXFGLYPH_H_
#define TXFGLYPH_H_

#include <OSGConfig.h>
#include <OSGBaseTypes.h>

#include "OSGFontGlyph.h"

OSG_BEGIN_NAMESPACE 

class OSG_SYSTEMLIB_DLLMAPPING TXFFontGlyph : public virtual FontGlyph
{
    typedef FontGlyph Inherited;

  private:

    TXFFontGlyph(const TXFFontGlyph &obj);
    void operator =(const TXFFontGlyph &obj);

  protected:
  public:
    
    TXFFontGlyph(void);
    TXFFontGlyph(Int32 ascii, Int32 unicode);

    virtual ~TXFFontGlyph(void);

            void setupGlyph (Int32    ascii,       Int32    unicode);
    virtual bool createGlyph(void                                  );
    virtual bool setSizes   (Real32 *_boundingBox, Real32 &_advance);
    virtual bool setSizes   (Int32  *_boundingBox, Int32  &_advance);
};

OSG_END_NAMESPACE

#endif // TXFGLYPH_H_
