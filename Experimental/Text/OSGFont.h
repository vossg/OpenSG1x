#ifndef FONT_CLASS_DECLARATION
#define FONT_CLASS_DECLARATION

#include <OSGConfig.h>
#include <string>


#include <list>




OSG_BEGIN_NAMESPACE class Text; OSG_END_NAMESPACE
OSG_BEGIN_NAMESPACE class FontStyle; OSG_END_NAMESPACE

OSG_BEGIN_NAMESPACE

class Font {

private:

  /** CompletePath To Font */

protected:

  /** CompletePath To Font */
  string _fontPath;

  /** Name of Font */
  const char * _fontName;

  bool _valid;

  list<FontStyle *> _fontInstances;

public:

  /** Default Constructor */
  Font (void);

  /** Copy Constructor */
  Font (const Font &obj);

  /** Constructor */
  Font (const char *name);

  /** Constructor */
  Font (const char *name, string path);

  /** Destructor */
  virtual ~Font (void);

  /**  **/
  virtual inline const char *getName(void) {return _fontName;}

  /** loading and storing of font-contents */
  virtual bool initFont (void) = 0;

  /** creates FontStyle aka Text */
  virtual bool createInstance (Text *fontStyle) = 0;

  /** creates FontStyle */
  virtual FontStyle *createInstance (float size) = 0;

};



OSG_END_NAMESPACE


typedef osg::Font* FontP;


#endif // FONT_CLASS_DECLARATION
