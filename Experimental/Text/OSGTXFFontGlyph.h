#ifndef TXFGLYPH_CLASS_DECLARATION
#define TXFGLYPH_CLASS_DECLARATION

#include <OSGConfig.h>

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
  TXFFontGlyph (int ascii, int unicode);

  /** Destructor */
  virtual ~TXFFontGlyph (void);

  /** Constructor */
  void setupGlyph(int ascii, int unicode);

  /** creates desired representation */
  virtual bool createGlyph (void);

  virtual bool setSizes (float *_boundingBox, float & _advance);

  virtual bool setSizes (int *_boundingBox, int & _advance);

};

typedef TXFFontGlyph* TXFFontGlyphP;


OSG_END_NAMESPACE


#endif // TXFGLYPH_CLASS_DECLARATION

