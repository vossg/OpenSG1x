#ifndef VECTORGLYPH_CLASS_DECLARATION
#define VECTORGLYPH_CLASS_DECLARATION

#ifndef WIN32
enum VGlyphType
{
    VGLYPH_NONE     = 0,
    VGLYPH_FACE,
    VGLYPH_OUTLINE
};

#include <OSGConfig.h>
#include <OSGBaseTypes.h>

#include <list>
#include <vector>
#include "OSGFontGlyph.h"

/** Vector Representation of a Glyph.
*
* Defines the 3D-Data-Interface to Glyphs and implements GLU-Tesselation
*
*/
OSG_BEGIN_NAMESPACE class   FontGlyphContour;
OSG_END_NAMESPACE OSG_BEGIN_NAMESPACE class VectorFontGlyph :
    public virtual FontGlyph
{
    typedef FontGlyph           ParentClass;
private:

    /** wether its outline or face (different number of indices) */
    VGlyphType                  _type;

    /** adding Points is done with this */
    void                        addPoint(Real32 *point, bool lower = false);

    /** look if given point already exist and return its index */
    Int32                       findPoint(Real32 *point, Int32 lower, Int32 upper);

    void                        extrude(void);
protected:

    /** desired Z-depth of glyph */
    Real32                      _depth;

    Real32                      _precision;

    /** All Points that Make up the Glyph */
    std::vector<Real32 *>       _points;

    std::vector<Real32 *>       _normals;

    Int32                       _numPoints;

    Int32                       _numNormals;

    Int32                       _pointBufferSize;

    /** The indices defining the order of points */
    std::vector<Int32>          _indices;

    std::vector<Int32>          _normalIndices;

    Int32                       _numIndices, _numBad;

    bool                        _bad;

    Int32                       _numFrontFaces;

    Int32                       _indexBufferSize;

    Int32                       _contourStart;

    std::vector<FontGlyphContour *>  _contours;

    class                       FloatBuffer
    {
private:

        Real32  **_fBuffer;

        Int32   _fBuffSize, _fBuffNext, _fWhichBuffer;

        void    fBuffAlloc(Int32 size);
public:

        FloatBuffer (void);

        Real32  *allocFloat(Int32 num);

        Int32   getBufferForPointer(Real32 *pointer);

        Real32 *getBuffer(Int32 which)
        {
            return which <= _fWhichBuffer ? _fBuffer[which] : 0;
        }
    };

    FloatBuffer _vertexBuffer, _normalBuffer;

    Real32      _boundingBox[6];

    Real32      _advance;

    /** creates triangle-list */
    bool        createTriangles(void);

    friend void tessVertex(void *);

    void        pushIt(Real32 ** &stack, Int32 &num, Real32 * &elem);

    void        calcNormal(Real32 ** &stack, Int32 num, Real32 *result);

    bool        checkAngle(Real32 **joint);
public:

    /** Default Constructor */
    VectorFontGlyph(void);

    /** Copy Constructor */
    VectorFontGlyph(const VectorFontGlyph &obj);

    /** Constructor */
    VectorFontGlyph(VGlyphType type);

    /** Destructor */
    virtual     ~VectorFontGlyph(void);

    /** get method for attribute points */
    virtual std::vector<Real32 *> &getPoints(void)
    {
        return _points;
    }

    /** get method for attribute normals */
    virtual std::vector<Real32 *> &getNormals(void)
    {
        return _normals;
    }

    /** get method for attribute indices */
    virtual std::vector<Int32> &getIndices(void)
    {
        return _indices;
    }

    /** get method for attribute indices */
    virtual std::vector<Int32> &getNormalIndices(void)
    {
        return _normalIndices;
    }

    /** get method for attribute numPoints */
    virtual Int32 getNumPoints(void)
    {
        return _numPoints;
    }

    /** get method for attribute numNormals */
    virtual Int32 getNumNormals(void)
    {
        return _numNormals;
    }

    /** get method for attribute numIndices */
    virtual Int32 getNumIndices(void)
    {
        return _numIndices;
    }

    virtual Int32 getNumFrontFaces(void)
    {
        return _numFrontFaces;
    }

    /** clears 3D-data */
    virtual bool    clear(void);

    const Real32 *getBoundingBox(void)
    {
        return _boundingBox;
    }

    Real32 getAdvance(void)
    {
        return _advance;
    }

    /** set method for attribute depth */
    virtual void setDepth(Real32 size)
    {
        _depth = size;
    }

    /** get method for attribute depth */
    virtual Real32 getDepth(void)
    {
        return _depth;
    }

    /** set method for attribute depth */
    virtual void setPrecision(Real32 precision)
    {
        _precision = precision;
    }

    /** get method for attribute type */
    virtual VGlyphType getType(void)
    {
        return _type;
    }

    /** set method for attribute type */
    virtual void setType(VGlyphType type)
    {
        _type = type;
    }
};

OSG_END_NAMESPACE typedef OSG::VectorFontGlyph * VectorFontGlyphP;
#endif
#endif // VECTORGLYPH_CLASS_DECLARATION
