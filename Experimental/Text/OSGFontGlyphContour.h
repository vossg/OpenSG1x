#ifndef GLYPHCONTOUR_CLASS_DECLARATION
#define GLYPHCONTOUR_CLASS_DECLARATION

#ifndef WIN32
#include <OSGConfig.h>
#include <OSGBaseTypes.h>

#include <vector>

OSG_BEGIN_NAMESPACE class   FontGlyphContour
{
private:

    /** Point List of this contour */
    std::vector<Real32 *> _points;

    std::vector<Real32 *> _normals;

    Int32                 _numPoints;

    Int32                 _numNormals;

    /** ordering of points for outer or inner contours */
    bool                  _isClockwise;

    Real32                _orderingBuffer;

    Int32                 _startContour;
protected:

    Real32                _bb[4];

    Int32                 _contour;
public:

    /** Default Constructor */
    FontGlyphContour(void);

    /** Copy Constructor */
    FontGlyphContour(const FontGlyphContour &obj);

    /** Destructor */
    virtual             ~FontGlyphContour(void);

    /** get method for attribute points */
    virtual Real32 *getPoint(Int32 which)
    {
        return _points[which];
    }

    /** get method for attribute points */
    virtual std::vector<Real32 *> &getPoints(void)
    {
        return _points;
    }

    /** get method for attribute points */
    virtual Int32 getNumPoints(void)
    {
        return _numPoints;
    }

    /** get method for attribute points */
    virtual Real32 *getNormal(Int32 which)
    {
        return _normals[which];
    }

    /** get method for attribute normals */
    virtual std::vector<Real32 *>    &getNormals(void);

    /** get method for attribute normals */
    virtual Int32 getNumNormals(void)
    {
        return _numNormals;
    }

    /** set method for attribute points */
    virtual void    addPoint(Real32 *point, Real32 *normal, bool copy = false);

    /** get method for attribute isClockwise */
    virtual bool isClockwise(void)
    {
        return _isClockwise;
    }

    virtual Real32 getArea(void)
    {
        return _orderingBuffer;
    }

    virtual void setOrdering(Real32 ordering)
    {
        _orderingBuffer = ordering;
    }

    virtual void setBB(Real32 *bb)
    {
        _bb[0] = bb[0];
        _bb[1] = bb[1];
        _bb[2] = bb[2];
        _bb[3] = bb[3];
    }

    virtual Real32 *getBB(void)
    {
        return _bb;
    }

    void setWhichTTContour(Int32 which)
    {
        _contour = which;
    }

    Int32 getWhichTTContour(void)
    {
        return _contour;
    }

    virtual Int32 getStart(void)
    {
        return _startContour;
    }

    virtual void setStart(Int32 start)
    {
        _startContour = start;
    }

    bool    inside(FontGlyphContour *contour);

    /** set method for attribute isClockwise */
    virtual void setIsClockwise(void)
    {
        _isClockwise = true;
    }

    /** set method for attribute isClockwise */
    virtual void setIsNotClockwise(void)
    {
        _isClockwise = false;
    }

    virtual void setNumPoints(Int32 num)
    {
        _points.resize(num);
        _normals.resize(num);
    }

    virtual Int32 getNumPointsExpected(void)
    {
        return _points.size();
    }
};

typedef FontGlyphContour    *FontGlyphContourP;

OSG_END_NAMESPACE
#endif
#endif // GLYPHCONTOUR_CLASS_DECLARATION
