#ifndef TXFGLYPHINFO_CLASS_DECLARATION
#define TXFGLYPHINFO_CLASS_DECLARATION

#ifndef WIN32
#include <OSGConfig.h>
#include <OSGBaseTypes.h>

OSG_BEGIN_NAMESPACE class   TXFGlyphInfo
{
private:
protected:

    //  texture coordinates  (ccw)
    Real32  _tCoords[4][2];

    //  vertex coordinates  (ccw)
    Real32  _vCoords[4][2];

    Real32  _advance;

    Int8    *_dimensions;

    Int16   *_offset;

    UInt8   _remapped;
public:

    /** Default Constructor */
    TXFGlyphInfo(void)
    {
        _remapped = 0;
        _dimensions = NULL;
        _offset = 0;
    }

    /** Destructor */
    virtual~TXFGlyphInfo(void)
    { ;
    }

    void remap(UInt8 dest)
    {
        _remapped = dest;
    }

    UInt8 remapped(void)
    {
        return _remapped;
    }

    virtual bool    setTextureCoords(Int8 corner, Real32 x, Real32 y);

    virtual bool    setVertexCoords(Int8 corner, Real32 x, Real32 y);

    virtual Real32  *getTextureCoords(Int8 corner);

    virtual Real32  *getVertexCoords(Int8 corner);

    virtual void setAdvance(Real32 advance)
    {
        _advance = advance;
    }

    virtual Real32 getAdvance(void)
    {
        return _advance;
    }

    virtual void setDimensions(Int8 *dims)
    {
        _dimensions = dims;
    }

    virtual Int8 *getDimensions(void)
    {
        return _dimensions;
    }

    virtual void setOffset(Int16 *off)
    {
        _offset = off;
    }

    virtual Int16 *getOffset(void)
    {
        return _offset;
    }
};

typedef TXFGlyphInfo    *TXFGlyphInfoP;

OSG_END_NAMESPACE
#endif
#endif // TXFGLYPHINFO_CLASS_DECLARATION
