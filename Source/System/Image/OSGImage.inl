/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
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

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*!
Check if the pixelFormat, dimension, bpp and data are valid (not null)
with a single call.    
*/
inline bool   Image::isValid (void) const
{ 
  return ((_pixelFormat != OSG_INVALID_PF) && _dimension && _bpp && _data); 
}

/*-------------------------------------------------------------------------*/
/*!
returns the image dimension, 0 for invalid, 1 for 1D, 2 for 2D and
3 for 3D data.
*/
inline Int32  Image::getDimension  (void) const 
{ 
  return _dimension; 
}

/*-------------------------------------------------------------------------*/
/*!
returns the image pixel width, can be 0 for invalid data.
*/
inline Int32  Image::getWidth      (void) const 
{ 
  return _width; 
}

/*-------------------------------------------------------------------------*/
/*!
returns the image pixel height, can be 0 for invalid data.
*/
inline Int32 Image::getHeight      (void) const
{ 
  return _height; 
}

/*-------------------------------------------------------------------------*/
/*!
returns the image pixel depth, can be 0 for invalid data.
*/
inline Int32  Image::getDepth      (void) const 
{ 
  return _depth; 
}

/*-------------------------------------------------------------------------*/
/*!
returns the image bytes per pixel, can be 0 for invalid data
*/
inline UChar8 Image::getBpp        (void) const 
{ 
  return _bpp; 
}

/*-------------------------------------------------------------------------*/
/*!
returns the number of mipMap levels. Can be 0 for invalid data,
is 1 for simple images.
*/
inline Int32  Image::getMipMapCount(void) const 
{ 
  return _mipmapCount; 
}

/*-------------------------------------------------------------------------*/
/*!
returns the number of frames. Can be 0 for invalid data,
is 1 for simple images.
*/
inline Int32  Image::getFrameCount (void) const 
{ 
  return _frameCount; 
}

/*-------------------------------------------------------------------------*/
/*!
returns the frame delay. The default value is 0.0
*/
inline Time   Image::getFrameDelay (void) const 
{ 
  return _frameDelay; 
}

/*-------------------------------------------------------------------------*/
/*!
returns the pixelFormat, uset getBpp the get the bytes per pixel.
*/
inline Image::PixelFormat Image::getPixelFormat (void) const 
{ 
  return _pixelFormat; 
}

/*-------------------------------------------------------------------------*/
/*!
returns the data size in bytes. 
*/
inline unsigned long Image::getSize ( bool withMipmap,
                                      bool withFrames) const
{ 
  return  ( calcMipmapSumSize((withMipmap ? (_mipmapCount-1) : 0)) *
            (withFrames ? _frameCount : 1) * _bpp);
}

/*-------------------------------------------------------------------------*/
/*!
returns a data pointer for a single frame/mipmap chunk
*/
inline UChar8 *Image::getData ( UInt32 mipmapNum, 
                                UInt32 frameNum) const
{
  UChar8 *data = _data + (frameNum * _frameSize * _bpp);
  
  if (mipmapNum)
  {
    data += calcMipmapSumSize(mipmapNum - 1);
  }
  
  return data;
}

/*-------------------------------------------------------------------------*/
/*!
returns true if the image has any attachments
*/
inline bool Image::hasAttachment (void) const
{
  return (_attachmentMap.empty() ? false : true);
}

/*-------------------------------------------------------------------------*/
/*!
returns the number of attachments
*/
inline UInt32 Image::attachmentCount (void) const
{
  return _attachmentMap.size();
}

/*-------------------------------------------------------------------------*/
/*!
set a single string attachment for the given key/data pair
*/
inline void Image::setAttachment ( const std::string &key, 
                                   const std::string &data)
{ 
  _attachmentMap[key] = data; 
}

/*-------------------------------------------------------------------------*/
/*!
returns the string attachment for the given key or Null
*/
inline const 
std::string * Image::findAttachment ( const std::string &key) const
{ 
  std::map<std::string,std::string>::const_iterator ssI;
  ssI = _attachmentMap.find(key);

  return (ssI == _attachmentMap.end() ? 0 : &(ssI->second));
}

/*-------------------------------------------------------------------------*/
/*!
erases the string attachment for the given key.
*/
inline  void Image::eraseAttachment ( const std::string &key) 
{
  _attachmentMap.erase(key);
}

/*-------------------------------------------------------------------------*/
/*!
Internal used method to calculate the next mipmap geo for the given level
*/
inline void   Image::calcMipmapGeometry   ( UInt32 mipmapNum,
                                            UInt32 &width, 
                                            UInt32 &height, 
                                            UInt32 &depth ) const
{
  width  = _width >> mipmapNum;
  height = _height >> mipmapNum;
  depth  = _depth >> mipmapNum;
}

/*-------------------------------------------------------------------------*/
#ifdef __sgi
#pragma set woff 1209
#endif

/*!
Internal used method to calculate the number of mipmaps levels
*/
inline UInt32 Image::calcMipmapLevelCount ( void ) const
{
  UInt32  w = _width, h = _height, d = _depth;
  UInt32 level;
  
  for (level = 1; true; level++)
    {
      if ((w == 1) && (h == 1) && (d == 1))
        break;
      else
        {
          w = (w >>= 1) ? w : 1;
          h = (h >>= 1) ? h : 1;
          d = (d >>= 1) ? d : 1;
        }
    }
  return level;
}

#ifdef __sgi
#pragma reset woff 1209
#endif

/*-------------------------------------------------------------------------*/
/*!
Internal used method to calculate the size in bpp of a single mipmap level
*/
inline UInt32 Image::calcMipmapSize    ( UInt32 mipmapNum,
                                         UInt32 w, UInt32 h, UInt32 d) const
{
  w >>= mipmapNum;
  h >>= mipmapNum;
  d >>= mipmapNum;
  
  return (w?w:1) * (h?h:1) * (d?d:1);
}

/*-------------------------------------------------------------------------*/
/*!
Internal used method to calculate the size in bpp of a single mipmap level
for the current image settings
*/
inline UInt32 Image::calcMipmapSize    ( UInt32 mipmapNum) const
{
  return calcMipmapSize(mipmapNum,_width,_height,_depth);
}

/*-------------------------------------------------------------------------*/
/*!
Internal used method to calculate the mem sum of all mipmap levels in bpp
*/
inline UInt32 Image::calcMipmapSumSize ( UInt32 mipmapNum,
                                         UInt32 w, UInt32 h, UInt32 d) const
{
  Int32 sum = w * h * d;
  
  while (mipmapNum--) 
    {
      w >>= 1;
      h >>= 1;
      d >>= 1;
      sum += (w?w:1) * (h?h:1) * (d?d:1);
    }
  
  return sum;
}

/*-------------------------------------------------------------------------*/
/*!
Internal used method to calculate the mem sum of all mipmap levels in bpp
for the current Image paramter
*/
inline UInt32 Image::calcMipmapSumSize (UInt32 mipmapNum) const
{
  return calcMipmapSumSize(mipmapNum,_width,_height,_depth);
}

OSG_END_NAMESPACE
