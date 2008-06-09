/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline bool Image::isValid (void) const
{
    return !getMFPixel()->empty();
}

/*! returns the data size in bytes. 
 */
inline unsigned long Image::getSize ( bool withMipmap,
                                      bool withFrames,
                                      bool withSides ) const
{ 
    return  ( calcMipmapSumSize((withMipmap ? getMipMapCount() : 1)) *
              (withSides  ? getSideCount() : 1) *
              (withFrames ? getFrameCount() : 1) ); 
}

/*! returns a data pointer for a single frame/mipmap chunk
 */
inline UInt8 *Image::editData(UInt32 mipmapNum, 
                              UInt32 frameNum,
                              UInt32 sideNum )
{
    if(getMFPixel()->empty())
        return NULL;

    UInt8 *data = (&(*editMFPixel())[0]) + 
      (sideNum * getSideSize()) +
      (frameNum * getFrameSize());
    
    if (mipmapNum)
    {
        data += calcMipmapSumSize(mipmapNum);
    }
  
    return data;
}

#ifndef OSG_2_PREP
/*! returns a data pointer for a single frame/mipmap chunk
 */
inline UInt8 *Image::getData( UInt32 mipmapNum, 
                              UInt32 frameNum,
                              UInt32 sideNum )
{
    if(getMFPixel()->empty())
        return NULL;

    UInt8 *data = (&(*getMFPixel())[0]) + 
      (sideNum * getSideSize()) +
      (frameNum * getFrameSize());
    
    if (mipmapNum)
    {
        data += calcMipmapSumSize(mipmapNum);
    }
  
    return data;
}
#endif

/*! returns a data pointer for a single frame/mipmap chunk
 */
inline const UInt8 *Image::getData( UInt32 mipmapNum, 
                                    UInt32 frameNum,
                                    UInt32 sideNum ) const
{
    if(getMFPixel()->empty())
        return NULL;

    const UInt8 *data = (&(*getMFPixel())[0]) + 
        (sideNum * getSideSize()) +
        (frameNum * getFrameSize());
    
    if (mipmapNum)
    {
        data += calcMipmapSumSize(mipmapNum);
    }
  
    return data;
}

/*! returns a data pointer for a single frame/mipmap chunk
 */
inline UInt8 *Image::editDataFast(UInt32 mipmapNum, 
                                  UInt32 frameNum,
                                  UInt32 sideNum )
{
    UInt8 *data = (&(*editMFPixel())[0]) +  (sideNum * getSideSize()) +
        (frameNum * getFrameSize());

    data += _mipmapOffset[mipmapNum];

    return data;
}

#ifndef OSG_2_PREP
/*! returns a data pointer for a single frame/mipmap chunk
 */
inline UInt8 *Image::getDataFast( UInt32 mipmapNum, 
                                  UInt32 frameNum,
                                  UInt32 sideNum )
{
    UInt8 *data = (&(*getMFPixel())[0]) +  (sideNum * getSideSize()) +
                  (frameNum * getFrameSize());

    data += _mipmapOffset[mipmapNum];

    return data;
}
#endif

/*! returns a data pointer for a single frame/mipmap chunk
 */
inline const UInt8 *Image::getDataFast( UInt32 mipmapNum,
                                        UInt32 frameNum,
                                        UInt32 sideNum ) const
{
    const UInt8 *data = (&(*getMFPixel())[0]) + (sideNum * getSideSize()) +
                        (frameNum * getFrameSize());

    data += _mipmapOffset[mipmapNum];

    return data;
}

/*! Add a field container as a parent of this Image.
    
    You should not have to call this method yourself.
 */
inline void
Image::addParent(const FieldContainerPtr &parent)
{
    _mfParents.push_back(parent);
}

/*! Remove a field container as a parent of this Image.
    
    You should not have to call this method yourself.
 */
inline void
Image::subParent(const FieldContainerPtr &parent)
{
    MFFieldContainerPtr::iterator parentIt = _mfParents.find(parent);
    
    if(parentIt != _mfParents.end())
    {
        _mfParents.erase(parentIt);
    }
}

// Specialization for Image we need this to support VRML PixelTextures.
template <> inline
void SFImagePtr::pushValueByStr(const Char8 *str)
{
    if(getValue() != NullFC)
        getValue()->addValue(str);
}

OSG_END_NAMESPACE

#define OSGIMAGE_INLINE_CVSID "@(#)$Id: $"

