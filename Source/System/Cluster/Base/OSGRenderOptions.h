/*!
 * \class OSGRenderOptions
 * \brief
 * \author Andreas Zieringer AMZ GmbH
 */

#ifndef _OSGRENDEROPTIONS_H_
#define _OSGRENDEROPTIONS_H_

#include <OSGConfig.h>

#include <OSGRenderOptionsBase.h>

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING RenderOptions : public RenderOptionsBase
{
  private:

    typedef RenderOptionsBase Inherited;

  public:

    virtual void changed(BitVector whichField, UInt32 origin);

  protected:

    RenderOptions(void);
    RenderOptions(const RenderOptions &source);

    virtual ~RenderOptions(void);

  private:

    friend class FieldContainer;
    friend class RenderOptionsBase;

    static void initMethod(void);

    void operator =(const RenderOptions &source);
};

typedef RenderOptions *RenderOptionsP;

OSG_END_NAMESPACE

#include <OSGRenderOptionsBase.inl>

#endif /* _OSGRENDEROPTIONS_H_ */
