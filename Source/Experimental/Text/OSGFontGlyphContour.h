#ifndef GLYPHCONTOUR_H_
#define GLYPHCONTOUR_H_

#include <OSGConfig.h>
#include <OSGBaseTypes.h>
#include <OSGSystemDef.h>

#include <vector>

OSG_BEGIN_NAMESPACE 

class OSG_SYSTEMLIB_DLLMAPPING FontGlyphContour
{
  private:

    FontGlyphContour(const FontGlyphContour &obj);
    void operator =(const FontGlyphContour &obj);

  protected:

    std::vector<Real32 *> _points;
    std::vector<Real32 *> _normals;

    Int32                 _numPoints;
    Int32                 _numNormals;

    bool                  _isClockwise;
    Real32                _orderingBuffer;
    Int32                 _startContour;
    Real32                _bb[4];
    Int32                 _contour;

  public:

    FontGlyphContour(void);

    virtual ~FontGlyphContour(void);

    virtual Real32                *getPoint         (Int32   which       );
    virtual std::vector<Real32 *> &getPoints        (void                );
    virtual Int32                  getNumPoints     (void                );
    virtual Real32                *getNormal        (Int32   which       );
    virtual std::vector<Real32 *> &getNormals       (void                );
    virtual Int32                  getNumNormals    (void                );
    virtual void                   addPoint         (Real32 *point, 
                                                     Real32 *normal, 
                                                     bool    copy = false);
    virtual bool                   isClockwise      (void                );
    virtual Real32                 getArea          (void                );
    virtual void                   setOrdering      (Real32  ordering    );
    virtual void                   setBB            (Real32 *bb          );
    virtual Real32                *getBB            (void                );
    
            void                   setWhichTTContour(Int32   which       );
            Int32                  getWhichTTContour(void                );

    virtual Int32                  getStart(void                         );
    virtual void                   setStart(Int32             start      );

            bool                   inside  (FontGlyphContour *contour    );

    virtual void                   setIsClockwise      (void             );
    virtual void                   setIsNotClockwise   (void             );

    virtual void                   setNumPoints        (Int32 num        );
    virtual Int32                  getNumPointsExpected(void             );
};

OSG_END_NAMESPACE
#endif // GLYPHCONTOUR_H_
