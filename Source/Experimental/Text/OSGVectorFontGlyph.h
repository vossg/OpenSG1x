#ifndef VECTORGLYPH_H_
#define VECTORGLYPH_H_

#include <OSGConfig.h>
#include <OSGBaseTypes.h>

#include <list>
#include <vector>

#include "OSGFontGlyph.h"

enum VGlyphType
{
    VGLYPH_NONE     = 0x0000,
    VGLYPH_FACE     = 0x0001,
    VGLYPH_OUTLINE  = 0x0002
};


OSG_BEGIN_NAMESPACE 

class OSG_SYSTEMLIB_DLLMAPPING FontGlyphContour;

class VectorFontGlyph : public virtual FontGlyph
{
    typedef FontGlyph Inherited;

  private:

    VectorFontGlyph(const VectorFontGlyph &obj);
    void operator =(const VectorFontGlyph &obj);

  protected:

    friend void OSG_APIENTRY tessVertex(void *);

    class FloatBuffer
    {
      protected:

        Real32  **_fBuffer;
        Int32     _fBuffSize;
        Int32     _fBuffNext;
        Int32     _fWhichBuffer;
        
        void fBuffAlloc(Int32 size);

      public:

        FloatBuffer(void);
        ~FloatBuffer(void);

        Real32 *allocFloat         (Int32   num    );
        Int32   getBufferForPointer(Real32 *pointer);
        Real32 *getBuffer          (Int32   which  );
    };


    VGlyphType                      _type;
    Real32                          _depth;
    Real32                          _precision;

    std::vector<Real32 *>           _points;
    std::vector<Real32 *>           _normals;

    Int32                           _numPoints;
    Int32                           _numNormals;
    Int32                           _pointBufferSize;

    std::vector<Int32>              _indices;
    std::vector<Int32>              _normalIndices;

    Int32                           _numIndices;
    Int32                           _numBad;
    bool                            _bad;
    Int32                           _numFrontFaces;
    Int32                           _indexBufferSize;
    Int32                           _contourStart;

    std::vector<FontGlyphContour *> _contours;

    FloatBuffer                     _vertexBuffer;
    FloatBuffer                     _normalBuffer;

    Real32                          _boundingBox[6];

    Real32                          _advance;


    void  addPoint       (Real32 *  point, bool   lower = false         );
    Int32 findPoint      (Real32 *  point, Int32  lower, Int32    upper );

    void  extrude        (void                                          );
    bool  createTriangles(void                                          );
    void  pushIt         (Real32 **&stack, Int32 &num,   Real32 *&elem  );
    void  calcNormal     (Real32 **&stack, Int32  num,   Real32 * result);
    bool  checkAngle     (Real32 ** joint                               );

  public:

    VectorFontGlyph(void);
    VectorFontGlyph(VGlyphType type);

    virtual ~VectorFontGlyph(void);

    virtual std::vector<Real32 *> &getPoints       (void);
    virtual std::vector<Real32 *> &getNormals      (void);
    virtual std::vector<Int32   > &getIndices      (void);
    virtual std::vector<Int32   > &getNormalIndices(void);

    virtual Int32 getNumPoints    (void);
    virtual Int32 getNumNormals   (void);
    virtual Int32 getNumIndices   (void);
    virtual Int32 getNumFrontFaces(void);

    virtual bool        clear         (void                );

    const   Real32     *getBoundingBox(void                );

    Real32              getAdvance    (void                );

    virtual void        setDepth      (Real32 size         );
    virtual Real32      getDepth      (void                );

    virtual void        setPrecision  (Real32     precision);

    virtual VGlyphType  getType       (void                );
    virtual void        setType       (VGlyphType type     );
};

OSG_END_NAMESPACE 

#endif // VECTORGLYPH_H_
