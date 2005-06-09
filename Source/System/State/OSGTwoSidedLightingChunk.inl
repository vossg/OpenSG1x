/*!
 * \class TwoSidedLightingChunk
 * \brief
 * \author Andreas Zieringer AMZ GmbH
 */

#include <OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
UInt32 TwoSidedLightingChunk::getStaticClassId(void)
{
    return getStaticClass()->getId();
}

inline
const StateChunkClass *TwoSidedLightingChunk::getStaticClass(void)
{
    return &TwoSidedLightingChunk::_class;
}


//----------------------------------------------------------------------------

OSG_END_NAMESPACE

#define OSGTWOSIDEDLIGHTINGCHUNK_INLINE_CVSID "@(#)$Id: OSGTwoSidedLightingChunk.inl,v 1.1 2005/06/09 08:39:27 a-m-z Exp $"
