//---------------------------------------------------------------------------

// Der Ursprungscode fuer das skalieren kommt von irgendsoeiner code seite.
// Eine schnellere modifizierte version gibt es unter 
// http://www.paintlib.de/paintlib/

//----------------------------------------------------------------------------
//  Includes
//----------------------------------------------------------------------------

#include <assert.h>
#include <string.h>

#include "OSGImageScaler.h"

OSG_USING_NAMESPACE

// double precision pi
#define OSG_FILTER_PI  OSG::Real64 (3.1415926535897932384626433832795)
#define OSG_FILTER_2PI OSG::Real64 (2.0 * 3.1415926535897932384626433832795)
#define OSG_FILTER_4PI OSG::Real64 (4.0 * 3.1415926535897932384626433832795)

//----------------------------------------------------------------------------
//  Namespaces
//----------------------------------------------------------------------------

using namespace osg;
using namespace std;

//----------------------------------------------------------------------------

ImageGenericFilter::ImageGenericFilter(Real64 dWidth) :
    m_dWidth(dWidth)
{
}

ImageGenericFilter::~ImageGenericFilter(void)
{
}

Real64 ImageGenericFilter::getWidth(void) const
{
    return m_dWidth;
}

void ImageGenericFilter::setWidth(Real64 dWidth)
{
    m_dWidth = dWidth;
}

//----------------------------------------------------------------------------

ImageBoxFilter::ImageBoxFilter(Real64 dWidth) :
    ImageGenericFilter(dWidth)
{
}

ImageBoxFilter::~ImageBoxFilter(void)
{
}

Real64 ImageBoxFilter::filter (Real64 dVal) const
{
    return (fabs(dVal) <= m_dWidth ? 1.0 : 0.0);
}

//----------------------------------------------------------------------------

ImageLinearFilter::ImageLinearFilter(Real64 dWidth) :
    ImageGenericFilter(dWidth)
{
}

ImageLinearFilter::~ImageLinearFilter(void)
{
}

Real64 ImageLinearFilter::filter(Real64 dVal) const
{
    dVal = fabs(dVal);
    return (dVal < m_dWidth ? m_dWidth - dVal : 0.0);
}

//----------------------------------------------------------------------------

ImageGaussianFilter::ImageGaussianFilter (Real64 dWidth) :
    ImageGenericFilter(dWidth)
{
}

ImageGaussianFilter::~ImageGaussianFilter(void)
{
}

Real64 ImageGaussianFilter::filter(Real64 dVal) const
{
    if (fabs (dVal) > m_dWidth)
        return 0.0;

    return exp (-dVal * dVal / 2.0) / sqrt (OSG_FILTER_2PI);
}

//----------------------------------------------------------------------------

ImageHammingFilter::ImageHammingFilter(Real64 dWidth) :
    ImageGenericFilter(dWidth)
{
}

ImageHammingFilter::~ImageHammingFilter(void)
{
}

Real64 ImageHammingFilter::filter(Real64 dVal) const
{
    if (fabs (dVal) > m_dWidth)
        return 0.0;

    Real64 dWindow = 0.54 + 0.46 * cos (OSG_FILTER_2PI * dVal);
    Real64 dSinc = (dVal == 0) ? 1.0 : sin (OSG_FILTER_PI * dVal) / (OSG_FILTER_PI * dVal);
    return dWindow * dSinc;
}

//----------------------------------------------------------------------------

ImageBlackmanFilter::ImageBlackmanFilter (Real64 dWidth) :
    ImageGenericFilter(dWidth)
{
}

ImageBlackmanFilter::~ImageBlackmanFilter(void)
{
}

Real64 ImageBlackmanFilter::filter(Real64 dVal) const
{
    if (fabs (dVal) > m_dWidth)
        return 0.0;

    Real64 dN = 2.0 * m_dWidth + 1.0;
    return 0.42 + 0.5 * cos (OSG_FILTER_2PI * dVal / ( dN - 1.0 )) +
        0.08 * cos (OSG_FILTER_4PI * dVal / ( dN - 1.0 ));
}

//----------------------------------------------------------------------------

ImageLanczos3Filter::ImageLanczos3Filter(Real64 dWidth) :
    ImageGenericFilter(dWidth)
{
}

ImageLanczos3Filter::~ImageLanczos3Filter(void)
{
}

Real64 ImageLanczos3Filter::sinc(Real64 x) const
{
    x *= OSG_FILTER_PI;
    if(x != 0.0)
        return(sin(x) / x);
    return 1.0;
}

Real64 ImageLanczos3Filter::filter(Real64 dVal) const
{
    if(dVal < 0)
        dVal = -dVal;
    if(dVal < 3.0)
        return(sinc(dVal) * sinc(dVal / 3.0));
    return 0.0;
}

//----------------------------------------------------------------------------
/*! Dynamic handling of different image data types */
//----------------------------------------------------------------------------

struct ValueHandler
{
    virtual Real64 getValue(const UInt8 *data,
                            UInt32 channels,
                            UInt32 width,UInt32 height,
                            UInt32 c,
                            UInt32 x1,UInt32 y1,UInt32 z1,
                            UInt32 x2,UInt32 y2,UInt32 z2,
                            Real64 *weightX,
                            Real64 *weightY,
                            Real64 *weightZ)=0;
    virtual void setValue(Real64 value,UInt8 *data,
                          UInt32 channels,UInt32 width,UInt32 height,
                          UInt32 c,UInt32 x,UInt32 y,UInt32 z)=0;
};

template <class ValueT> 
struct ValueHandlerTempl : public ValueHandler
{
    virtual Real64 getValue(const UInt8 *data,
                            UInt32 channels,
                            UInt32 width,UInt32 height,
                            UInt32 c,
                            UInt32 x1,UInt32 y1,UInt32 z1,
                            UInt32 x2,UInt32 y2,UInt32 z2,
                            Real64 *weightX,
                            Real64 *weightY,
                            Real64 *weightZ)
    {
        Real64 result = 0;
        UInt32 x,y,z;

        for(z = 0 ; z <= (z2-z1) ; ++z)
        {
            for(y = 0 ; y <= (y2-y1) ; ++y)
            {
                ValueT *valueP = (ValueT*)(data) +
                    (z1 + z) * (height*width*channels) +
                    (y1 + y) * (width*channels) +
                    (x1)     * (channels) + c;
                for(x = 0 ; x <= (x2-x1) ; ++x)
                {
                    result += (Real64)*(valueP) *
                        (weightX[x] * weightY[y] * weightZ[z]);
                    valueP += channels;
                }
            }
        }
        return result;
    }
    virtual void setValue(Real64 value,UInt8 *data,
                          UInt32 channels,UInt32 width,UInt32 height,
                          UInt32 c,UInt32 x,UInt32 y,UInt32 z)
    {
        // clamp value.
        Real64 maxValue = (Real64)TypeTraits<ValueT>::getMax();
        if(value > maxValue)
        {
            value = maxValue;
        }
        else
        {
            if(value < 0.0)
                value = 0.0;
        }

        ValueT *valueP = (ValueT*)(data);
        valueP = valueP + 
            z * (width*height*channels) +
            y * (width*channels) +
            x * (channels) +
            c;

        *valueP = (ValueT)value;
    }
};

//----------------------------------------------------------------------------
/*! constructor */
//----------------------------------------------------------------------------
ImageScaler::ImageScaler(void)
{
}

//----------------------------------------------------------------------------
/*! destructor */
//----------------------------------------------------------------------------
ImageScaler::~ImageScaler(void)
{
}

//----------------------------------------------------------------------------
/*! calculation contribution values from filter object */
//----------------------------------------------------------------------------
void ImageScaler::calcContributions(UInt32 axis,
                                    Int32  uResSize,
                                    Int32  uSrcSize,
                                    const ImageGenericFilter &filter,
                                    std::vector<Contribution> contrib[3])
{
    Real64 dWidth;
    Real64 dFScale = 1.0;
    Real64 dFilterWidth = filter.getWidth();

    Real64 dScale = (Real64)uResSize / (Real64)uSrcSize;

    // resize arrays
    contrib[axis].resize(uResSize);

    if (dScale < 1.0)
    {    // Minification
        dWidth = dFilterWidth / dScale;
        dFScale = dScale;
    }
    else
    {    // Magnification
        dWidth= dFilterWidth;
    }

    // Window size is the number of sampled pixels
    Int32 iWindowSize = 2 * (Int32)ceil(dWidth) + 1;

    for (Int32 u = 0; u < uResSize; u++)
    {   
        // Scan through line of contributions
        Real64 dCenter = (Real64)u / dScale;   // Reverse mapping
        // Find the significant edge points that affect the pixel
        Int32 iLeft = osgMax (0, (Int32)floor (dCenter - dWidth));
        //res->ContribRow[u].Left = iLeft;
        Int32 iRight = osgMin ((Int32)ceil (dCenter + dWidth), Int32(uSrcSize) - 1);
        //res->ContribRow[u].Right = iRight;

        // Cut edge points to fit in filter window in case of spill-off
        if (iRight - iLeft + 1 > iWindowSize)
        {
            if (iLeft < (Int32(uSrcSize) - 1 / 2))
            {
                iLeft++;
            }
            else
            {
                iRight--;
            }
        }
        // amz store the modified values!
        contrib[axis][u].left = iLeft;
        contrib[axis][u].right = iRight;

        Real64 dTotalWeight = 0.0;  // Zero sum of weights
        contrib[axis][u].weights.resize(iRight - iLeft + 1);
        for (Int32 iSrc = iLeft; iSrc <= iRight; iSrc++)
        { 
            // calculate weight
            Real64 weight = dFScale * 
                filter.filter(dFScale * (dCenter - (Real64)iSrc));
            contrib[axis][u].weights[iSrc-iLeft] = weight;
            // sum weights
            dTotalWeight += weight;
        }
        if (dTotalWeight > 0.0)
        {
            // Normalize weight of neighbouring points
            for (Int32 iSrc = iLeft; iSrc <= iRight; iSrc++)
            {
                // Normalize point
                contrib[axis][u].weights[iSrc-iLeft] /= dTotalWeight;
            }
            // optimize kernel size
            while(contrib[axis][u].weights.front() == 0)
            {
                contrib[axis][u].left++;
                contrib[axis][u].weights.erase(contrib[axis][u].weights.begin());
            }
            while(contrib[axis][u].weights.back() == 0)
            {
                contrib[axis][u].right--;
                contrib[axis][u].weights.erase(contrib[axis][u].weights.end() - 1);
            }
#if 0
            printf("%d %d  %d,%d\n",axis,u,contrib[axis][u].left,contrib[axis][u].right);
            for (Int32 iSrc = 0; iSrc < contrib[axis][u].weights.size(); iSrc++)
            {
                printf("%lf ",contrib[axis][u].weights[iSrc]);
            }
            printf("\n");
#endif
        }
    }
}

//----------------------------------------------------------------------------
/*! rescale image */
//----------------------------------------------------------------------------
bool ImageScaler::scale(ImagePtr &srcImg,
                        ImagePtr &dstImg,
                        Int32 width,
                        Int32 height,
                        Int32 depth,
                        const ImageGenericFilter &filter)
{
    ValueHandler             *valueHandler = NULL;
    Int32                     channels = srcImg->getComponents();
    std::vector<Contribution> contrib[3]; 

    beginEditCP(dstImg);

    switch(srcImg->getDataType())
    {
        case Image::OSG_UINT8_IMAGEDATA:
            valueHandler = new ValueHandlerTempl<UInt8>();
            break;
        case Image::OSG_UINT16_IMAGEDATA:
            valueHandler = new ValueHandlerTempl<UInt16>();
            break;
        case Image::OSG_UINT32_IMAGEDATA:
            valueHandler = new ValueHandlerTempl<UInt32>();
            break;
        case Image::OSG_FLOAT16_IMAGEDATA:
            valueHandler = new ValueHandlerTempl<Real16>();
            break;
        case Image::OSG_FLOAT32_IMAGEDATA:
            valueHandler = new ValueHandlerTempl<Real32>();
            break;
        default:
            SWARNING << "PixelType not scalable" << std::endl;
            return false;
    };

    // create kernel
    calcContributions(0,width, srcImg->getWidth() ,filter,contrib);
    calcContributions(1,height,srcImg->getHeight(),filter,contrib);
    calcContributions(2,depth, srcImg->getDepth() ,filter,contrib);

    if(!dstImg->set((Image::PixelFormat)srcImg->getPixelFormat(),
                    width,
                    height,
                    depth,
                    // create mipmaps from rescaled image
                    1,
                    srcImg->getFrameCount(),
                    srcImg->getFrameDelay(),
                    NULL,
                    srcImg->getDataType(),
                    true,
                    srcImg->getSideCount()))
    {
        SWARNING << "Unable to set image format" << std::endl;
        return false;
    }

    UInt32 srcImgWidth  = srcImg->getWidth();
    UInt32 srcImgHeight = srcImg->getHeight();
    Real64 *weightX;
    Real64 *weightY;
    Real64 *weightZ;
    UInt32 frames = srcImg->getFrameCount();
    UInt32 sides = srcImg->getSideCount();

    // it makes no sense to rescale the mipmap levels, so
    // we simply scale the main image and then rebuild the
    // mipmaps
    Real64 value;
    UInt32 x,y,z,c,f,s;
    UInt32 x1,x2,y1,y2,z1,z2;
    for(s = 0 ; s < sides ; ++s)
    {
        for(f = 0 ; f < frames ; ++f)
        {
            UInt8 *dstImgData   = dstImg->getData(0,f,s);
            UInt8 *srcImgData   = srcImg->getData(0,f,s);
            for(z = 0 ; z < depth ; ++z)
            {
                z1 = contrib[2][z].left;
                z2 = contrib[2][z].right;
                weightZ = &contrib[2][z].weights[0];
                for(y = 0 ; y < height ; ++y)
                {
                    y1 = contrib[1][y].left;
                    y2 = contrib[1][y].right;
                    weightY = &contrib[1][y].weights[0];
                    for(x = 0 ; x < width ; ++x)
                    {
                        x1 = contrib[0][x].left;
                        x2 = contrib[0][x].right;

                        weightX = &contrib[0][x].weights[0];
                        for(c = 0 ; c < channels ; ++c)
                        {
                            value = valueHandler->getValue(srcImgData,
                                                           channels,
                                                           srcImgWidth,
                                                           srcImgHeight,
                                                           c,
                                                           x1,y1,z1,
                                                           x2,y2,z2,
                                                           weightX,weightY,weightZ);

                            valueHandler->setValue(value,
                                                   dstImgData,
                                                   channels,width,height,
                                                   c,x,y,z);
                        }
                    }
                }
            }
        }
    }

    if(valueHandler != NULL)
        delete valueHandler;

    // rebuild mipmaps
    if(srcImg->getMipMapCount() > 1)
        dstImg->createMipmap(-1);

    endEditCP(dstImg);

    return true;
}
