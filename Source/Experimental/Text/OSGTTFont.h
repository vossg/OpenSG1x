#ifndef TTFONT_H_
#define TTFONT_H_

#include <OSGConfig.h>
#include <OSGBaseTypes.h>

#ifdef OSG_WITH_FREETYPE1
#include "OSGFont.h"

#include "freetype.h"

OSG_BEGIN_NAMESPACE 

class OSG_SYSTEMLIB_DLLMAPPING TTFont : public virtual Font
{
    typedef Font Inherited;

  private:

    TTFont(const TTFont &obj);
    void operator =(const TTFont &obj);
    
  protected:

    TT_Engine _ttEngine;
    TT_Face   _ttFace;
    TT_Error  _ttError;

  public:

    TTFont(void);
    TTFont(const Char8 *name, std::string path);

    virtual ~TTFont(void);

    virtual bool       initFont      (void        );
    virtual bool       createInstance(Text   *text);
    virtual FontStyle *createInstance(Real32  size);
};

OSG_END_NAMESPACE 

#endif // OSG_WITH_FREETYPE1
#endif // TTFONT_H_
