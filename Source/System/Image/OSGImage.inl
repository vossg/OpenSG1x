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
inline bool   Image::isValid (void) const
{ 
  return ((_pixelFormat != OSG_INVALID_PF) && _dimension && _bpp && _data); 
}

/*-------------------------------------------------------------------------*/
inline Int32  Image::getDimension  (void) const 
{ 
  return _dimension; 
}

/*-------------------------------------------------------------------------*/
inline Int32  Image::getWidth      (void) const 
{ 
  return _width; 
}

/*-------------------------------------------------------------------------*/
inline Int32  Image::getHeight     (void) const 
{ 
  return _height; 
}

/*-------------------------------------------------------------------------*/
inline Int32  Image::getDepth      (void) const 
{ 
  return _depth; 
}

/*-------------------------------------------------------------------------*/
inline UChar8 Image::getBpp        (void) const 
{ 
  return _bpp; 
}

/*-------------------------------------------------------------------------*/
inline Int32  Image::getMipMapCount(void) const 
{ 
  return _mipmapCount; 
}

/*-------------------------------------------------------------------------*/
inline Int32  Image::getFrameCount (void) const 
{ 
  return _frameCount; 
}

/*-------------------------------------------------------------------------*/
inline Time   Image::getFrameDelay (void) const 
{ 
  return _frameDelay; 
}

/*-------------------------------------------------------------------------*/
inline Image::PixelFormat Image::getPixelFormat (void) const 
{ 
  return _pixelFormat; 
}

/*-------------------------------------------------------------------------*/
inline unsigned long Image::getSize ( bool withMipmap,
                                      bool withFrames) const
{ 
  return  ( calcMipmapSumSize((withMipmap ? (_mipmapCount-1) : 0)) *
            (withFrames ? _frameCount : 1) * _bpp);
}

/*-------------------------------------------------------------------------*/
inline UChar8 *Image::getData ( UInt32 mipmapNum, 
                                UInt32 frameNum) const
{
  UChar8 *data = _data + (frameNum * _frameSize * _bpp);
  
  if (mipmapNum)
    data += calcMipmapSumSize(mipmapNum - 1);
  
  return data;
}

/*-------------------------------------------------------------------------*/
inline bool Image::hasAttachment (void) const
{
  return (_attachmentMap.empty() ? false : true);
}

/*-------------------------------------------------------------------------*/
inline UInt32 Image::attachmentCount (void) const
{
  return _attachmentMap.size();
}

/*-------------------------------------------------------------------------*/
inline void Image::setAttachment ( const std::string &key, 
                                   const std::string &data)
{ 
  _attachmentMap[key] = data; 
}

/*-------------------------------------------------------------------------*/
inline const 
std::string * Image::findAttachment ( const std::string &key) const
{ 
  std::map<std::string,std::string>::const_iterator ssI;
  ssI = _attachmentMap.find(key);

  return (ssI == _attachmentMap.end() ? 0 : &(ssI->second));
}

/*-------------------------------------------------------------------------*/
inline  void Image::eraseAttachment ( const std::string &key) 
{
  _attachmentMap.erase(key);
}

/*-------------------------------------------------------------------------*/
inline void   Image::calcMipmapGeometry   ( UInt32 mipmapNum,
                                            UInt32 &width, 
                                            UInt32 &height, 
                                            UInt32 &depth )
{
  width  = _width >> mipmapNum;
  height = _height >> mipmapNum;
  depth  = _depth >> mipmapNum;
}

/*-------------------------------------------------------------------------*/
#ifdef __sgi
#pragma set woff 1209
#endif

inline UInt32 Image::calcMipmapLevelCount ( void )
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
inline UInt32 Image::calcMipmapSize    ( UInt32 mipmapNum,
                                         UInt32 w, UInt32 h, UInt32 d) const
{
  w >>= mipmapNum;
  h >>= mipmapNum;
  d >>= mipmapNum;
  
  return (w?w:1) * (h?h:1) * (d?d:1);
}

/*-------------------------------------------------------------------------*/
inline UInt32 Image::calcMipmapSize    ( UInt32 mipmapNum) const
{
  return calcMipmapSize(mipmapNum,_width,_height,_depth);
}

/*-------------------------------------------------------------------------*/
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
inline UInt32 Image::calcMipmapSumSize (UInt32 mipmapNum) const
{
  return calcMipmapSumSize(mipmapNum,_width,_height,_depth);
}

OSG_END_NAMESPACE
