#ifndef TXFGLYPH_CLASS_DECLARATION
#define TXFGLYPH_CLASS_DECLARATION

#ifndef WIN32

#include <OSGConfig.h>
#include <OSGBaseTypes.h>

#include "OSGFontGlyph.h"



OSG_BEGIN_NAMESPACE


class TXFFontGlyph : public virtual FontGlyph {
	typedef FontGlyph ParentClass;

private:

protected:

public:

  /** Default Constructor */
  TXFFontGlyph (void);

  /** Copy Constructor */
  TXFFontGlyph (const TXFFontGlyph &obj);

  /** Constructor */
  TXFFontGlyph (Int32 ascii, Int32 unicode);

  /** Destructor */
  virtual ~TXFFontGlyph (void);

  /** Constructor */
  void setupGlyph(Int32 ascii, Int32 unicode);

  /** creates desired representation */
  virtual bool createGlyph (void);

  virtual bool setSizes (Real32 *_boundingBox, Real32 & _advance);

  virtual bool setSizes (Int32 *_boundingBox, Int32 & _advance);

};

typedef TXFFontGlyph* TXFFontGlyphP;


OSG_END_NAMESPACE


#endif
#endif // TXFGLYPH_CLASS_DECLARATION

