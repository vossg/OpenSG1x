#ifndef FONT_H_
#define FONT_H_

#include <OSGConfig.h>
#include <OSGBaseTypes.h>
#include <OSGSystemDef.h>

#include <string>
#include <list>

OSG_BEGIN_NAMESPACE 

class Text;
class FontStyle;

class OSG_SYSTEMLIB_DLLMAPPING Font
{
  private:

    Font(const Font &obj);
    void operator =(const Font &obj);

  protected:
    
    /** CompletePath To Font */
    std::string             _fontPath;
    
    /** Name of Font */
    std::string             _fontName;
    
    bool                    _valid;
    
    std::list<FontStyle *>  _fontInstances;
    
  public:
    
    Font(void);
    Font(const Char8 *name);
    Font(const Char8 *name, std::string path);

    virtual ~Font(void);

    const Char8 *getName(void);

    virtual bool       initFont      (void           ) = 0;
    virtual bool       createInstance(Text *fontStyle) = 0;
    virtual FontStyle *createInstance(Real32 size    ) = 0;
};

OSG_END_NAMESPACE 

#include <OSGFont.inl>

#endif // FONT_H_
