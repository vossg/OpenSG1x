#ifndef GLYPH_CLASS_DECLARATION
#define GLYPH_CLASS_DECLARATION

#include <OSGConfig.h>




OSG_BEGIN_NAMESPACE


class FontGlyph {

private:

  /** if creation successful */
  bool _valid;

  /** the ASCII-Code this Glyph Represents */
  int _asciiCode;

  /** The UniCode this Glyph represents */
  int _uniCode;

protected:

  float _size;

public:

  /** Default Constructor */
  FontGlyph (void);

  /** Copy Constructor */
  FontGlyph (const FontGlyph &obj);

  /** Constructor */
  FontGlyph (int ascii, int unicode);

  /** Destructor */
  virtual ~FontGlyph (void);

  /** creates desired representation */
  virtual bool create (void) = 0;

  /** cleares stored representation */
  virtual bool clear (void) = 0;

  /** get method for attribute valid */
  virtual inline bool isValid (void)
     { return _valid; }

  /** set method for attribute valid (force recreation)*/
  virtual void setInvalid (void)
     { _valid = false; }

  /** get method for attribute asciiCode */
  virtual inline int getAsciiCode (void)
     { return _asciiCode; }


  /** set method for attribute asciiCode */
  virtual void setAsciiCode (int asciiCode)
     { _asciiCode = asciiCode; }

  /** get method for attribute uniCode */
  virtual inline int getUniCode (void)
     { return _uniCode; }

  /** set method for attribute uniCode */
  virtual void setUniCode (int uniCode)
     { _uniCode = uniCode; }


  virtual void setSize (float size)
     { _size = size; }

  virtual inline float getSize (void)
     { return _size; }

};


OSG_END_NAMESPACE

typedef osg::FontGlyph* FontGlyphP;


#endif // GLYPH_CLASS_DECLARATION
