#ifndef GLYPH_CLASS_DECLARATION
#define GLYPH_CLASS_DECLARATION

#ifndef WIN32
#include <OSGConfig.h>
#include <OSGBaseTypes.h>

OSG_BEGIN_NAMESPACE class   FontGlyph
{
private:

    /** if creation successful */
    bool            _valid;

    /** the ASCII-Code this Glyph Represents */
    Int32           _asciiCode;

    /** The UniCode this Glyph represents */
    Int32           _uniCode;
protected:

    Real32          _size;
public:

    /** Default Constructor */
    FontGlyph(void);

    /** Copy Constructor */
    FontGlyph(const FontGlyph &obj);

    /** Constructor */
    FontGlyph(Int32 ascii, Int32 unicode);

    /** Destructor */
    virtual         ~FontGlyph(void);

    /** creates desired representation */
    virtual bool    create(void) = 0;

    /** cleares stored representation */
    virtual bool    clear(void) = 0;

    /** get method for attribute valid */
    virtual inline bool isValid(void)
    {
        return _valid;
    }

    /** set method for attribute valid (force recreation)*/
    virtual void setInvalid(void)
    {
        _valid = false;
    }

    /** get method for attribute asciiCode */
    virtual inline Int32 getAsciiCode(void)
    {
        return _asciiCode;
    }

    /** set method for attribute asciiCode */
    virtual void setAsciiCode(Int32 asciiCode)
    {
        _asciiCode = asciiCode;
    }

    /** get method for attribute uniCode */
    virtual inline Int32 getUniCode(void)
    {
        return _uniCode;
    }

    /** set method for attribute uniCode */
    virtual void setUniCode(Int32 uniCode)
    {
        _uniCode = uniCode;
    }

    virtual void setSize(Real32 size)
    {
        _size = size;
    }

    virtual inline Real32 getSize(void)
    {
        return _size;
    }
};

OSG_END_NAMESPACE typedef OSG::FontGlyph * FontGlyphP;
#endif
#endif // GLYPH_CLASS_DECLARATION
