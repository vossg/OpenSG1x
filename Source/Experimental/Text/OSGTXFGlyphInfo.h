#ifndef TXFGLYPHINFO_H_
#define TXFGLYPHINFO_H_

#include <OSGConfig.h>
#include <OSGBaseTypes.h>
#include <OSGSystemDef.h>

OSG_BEGIN_NAMESPACE 

class OSG_SYSTEMLIB_DLLMAPPING TXFGlyphInfo
{
  private:

    TXFGlyphInfo(const TXFGlyphInfo &source);
    void operator =(const TXFGlyphInfo &source);

  protected:
    
    Real32   _tCoords[4][2];
    Real32   _vCoords[4][2];
    Real32   _advance;

    Int8    *_dimensions;
    Int16   *_offset;
    UInt8    _remapped;

  public:

    TXFGlyphInfo(void);

    virtual ~TXFGlyphInfo(void);

            void    remap           (UInt8   dest   );
            UInt8   remapped        (void           );

    virtual bool    setTextureCoords(Int8    corner, 
                                     Real32  x, 
                                     Real32  y      );
    virtual Real32 *getTextureCoords(Int8    corner );

    virtual bool    setVertexCoords (Int8    corner, 
                                     Real32  x, 
                                     Real32  y      );
    virtual Real32 *getVertexCoords (Int8    corner );

    virtual void    setAdvance      (Real32  advance);
    virtual Real32  getAdvance      (void           );

    virtual void    setDimensions   (Int8   *dims   );
    virtual Int8   *getDimensions   (void           );

    virtual void    setOffset       (Int16  *off    );
    virtual Int16  *getOffset       (void           );
};

OSG_END_NAMESPACE

#endif // TXFGLYPHINFO_H_
