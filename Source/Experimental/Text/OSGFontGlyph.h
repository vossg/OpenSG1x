#ifndef GLYPH_H_
#define GLYPH_H_

#include <OSGConfig.h>
#include <OSGBaseTypes.h>
#include <OSGSystemDef.h>

OSG_BEGIN_NAMESPACE 

class OSG_SYSTEMLIB_DLLMAPPING FontGlyph
{
  private:

    FontGlyph(const FontGlyph &obj);
    void operator =(const FontGlyph &obj);

  protected:

    bool            _valid;
    Int32           _asciiCode;
    Int32           _uniCode;
    Real32          _size;
  
  public:

    FontGlyph(void);
    FontGlyph(Int32 ascii, Int32 unicode);

    virtual ~FontGlyph(void);

    virtual bool   create(void) = 0;
    virtual bool   clear(void) = 0;

    virtual bool   isValid     (void            );
    virtual void   setInvalid  (void            );

    virtual Int32  getAsciiCode(void            );
    virtual void   setAsciiCode(Int32  asciiCode);

    virtual Int32  getUniCode  (void            );
    virtual void   setUniCode  (Int32  uniCode  );

    virtual void   setSize     (Real32 size     );
    virtual Real32 getSize     (void            );
};

OSG_END_NAMESPACE 

#endif // GLYPH_H_
