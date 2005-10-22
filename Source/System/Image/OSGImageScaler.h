#ifndef _OSGIMAGESCALER_H_
#define _OSGIMAGESCALER_H_


//----------------------------------------------------------------------------
//  Includes
//----------------------------------------------------------------------------
#include <OSGSystemDef.h>
#include <OSGImage.h>

OSG_BEGIN_NAMESPACE

/*! base class for image filters
 */
class OSG_SYSTEMLIB_DLLMAPPING ImageGenericFilter
{
public:

    ImageGenericFilter(OSG::Real64 dWidth);
    virtual ~ImageGenericFilter(void);

    OSG::Real64 getWidth(void) const;
    void   setWidth(OSG::Real64 dWidth);

    virtual OSG::Real64 filter(OSG::Real64 dVal) const = 0;

protected:

    OSG::Real64  m_dWidth;
};

/*! box filter
 */
class OSG_SYSTEMLIB_DLLMAPPING ImageBoxFilter : public ImageGenericFilter
{
public:

    ImageBoxFilter(OSG::Real64 dWidth = OSG::Real64(0.5));
    virtual ~ImageBoxFilter(void);

    virtual OSG::Real64 filter(OSG::Real64 dVal) const;
};

/*! linear filter
 */
class OSG_SYSTEMLIB_DLLMAPPING ImageLinearFilter : public ImageGenericFilter
{
public:

    ImageLinearFilter(OSG::Real64 dWidth = OSG::Real64(1.0));
    virtual ~ImageLinearFilter(void);

    virtual OSG::Real64 filter(OSG::Real64 dVal) const;
};

/*! gaussian filter
 */
class OSG_SYSTEMLIB_DLLMAPPING ImageGaussianFilter : public ImageGenericFilter
{
public:

    ImageGaussianFilter(OSG::Real64 dWidth = OSG::Real64(1.0));
    virtual ~ImageGaussianFilter(void);

    virtual OSG::Real64 filter(OSG::Real64 dVal) const;
};

/*! hamming filter
 */
class OSG_SYSTEMLIB_DLLMAPPING ImageHammingFilter : public ImageGenericFilter
{
public:

    ImageHammingFilter(OSG::Real64 dWidth = OSG::Real64(0.5));
    virtual ~ImageHammingFilter(void);

    virtual OSG::Real64 filter(OSG::Real64 dVal) const;
};

/*! blackman filter
 */
class OSG_SYSTEMLIB_DLLMAPPING ImageBlackmanFilter : public ImageGenericFilter
{
public:

    ImageBlackmanFilter(OSG::Real64 dWidth = OSG::Real64(0.5));
    virtual ~ImageBlackmanFilter(void);

    virtual OSG::Real64 filter(OSG::Real64 dVal) const;
};

/*! lanczos3 filter
 */
class OSG_SYSTEMLIB_DLLMAPPING ImageLanczos3Filter : public ImageGenericFilter
{
public:

    ImageLanczos3Filter(OSG::Real64 dWidth = OSG::Real64(1.0));
    virtual ~ImageLanczos3Filter(void);

    virtual OSG::Real64 filter(OSG::Real64 dVal) const;

private:

    OSG::Real64 sinc(OSG::Real64 x) const;

};

//---------------------------------------------------------------------------

/*! Image scaler
 */
class OSG_SYSTEMLIB_DLLMAPPING ImageScaler
{
public:

    static bool scale(ImagePtr &srcImg,
                      ImagePtr &dstImg,
                      OSG::Int32 width,
                      OSG::Int32 height,
                      OSG::Int32 depth,
                      const ImageGenericFilter &filter);

private:

    ImageScaler(void);
    ~ImageScaler(void);

    /*! weights for the value contribution.
      Only symmetric kernels are supported */
    struct Contribution
    {
        // Normalized weights of neighboring pixels
        std::vector<Real64> weights; 
        // Bounds of source pixels window
        Int32 left,right;
    };

    static void calcContributions(UInt32 axis,
                                  Int32 uResSize,
                                  Int32 uSrcSize,
                                  const ImageGenericFilter &filter,
                                  std::vector<Contribution> contrib[3]);
};

//---------------------------------------------------------------------------

OSG_END_NAMESPACE

#endif // _OSGIMAGESCALER_H_
