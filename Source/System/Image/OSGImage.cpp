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
//-------------------------------
//      Includes                                
//-------------------------------
#define OSG_COMPILEIMAGEINST

#include "OSGConfig.h"

#include <math.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include <OSGLog.h>

#include "OSGImage.h"
#include "OSGImageFileHandler.h"
#include "OSGSFImageTypes.h"
#include "OSGMFImageTypes.h"

/*
#include "OSGSFImageTypes.h"
#include "OSGMFImageTypes.h"
*/
OSG_USING_NAMESPACE 

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Image
    \ingroup GrpSystemImage

1D/2D/3D Image with various pixel types data, can also optional hold
mipMap and simple multi-frame data.

See \ref PageSystemImage for details.

*/

/*****************************
 *   Types
 *****************************/

/*****************************
 *    Classvariables
 *****************************/

//-------------------------------------------------------------------------
/*!

Static dictionary to map pixelData values to the bytes per pixel (bpp) value.
Internaly used in the createData() method.

*/
Int32 Image::_formatDic[][2] =
{
    { OSG_L_PF, 1 },
    { OSG_LA_PF, 2 },
    { OSG_RGB_PF, 3 },
    { OSG_RGBA_PF, 4 },
    { OSG_BGR_PF, 3 },
    { OSG_BGRA_PF, 4 },
};

/********************************
 *    Class methodes
 *******************************/

/*******************************
*public
*******************************/


//-------------------------------------------------------------------------
/*!

method to set the image data. Use the doCopy parameter to specify, whether
the method should copy or link the pixel data.

*/

bool Image::set(PixelFormat pF, Int32 w, Int32 h, Int32 d, Int32 mmS, Int32 fS,
                Time fD, const UChar8 *da, bool doCopy)
{
    _pixelFormat = pF;

    _width = w;
    _height = h;
    _depth = d;

    _mipmapCount = mmS;

    _frameCount = fS;
    _frameDelay = fD;

    return createData(da, doCopy);
}

//-------------------------------------------------------------------------
/*!

method to set the image from another image object. 
Use the doCopy parameter to specify, whether
the method should copy or link the pixel data.


*/
bool Image::set(const Image &image, bool doCopy)
{
    this->set(image._pixelFormat, image._width, image._height, image._depth,
              image._mipmapCount, image._frameCount, image._frameDelay,
              image._data, doCopy);

#ifdef OSG_DEBUG
    FDEBUG(("Running image set(image) \n"));
    this->dump();
#endif
    return true;
}

//-------------------------------------------------------------------------
/*!

method to set only the image pixel data, all parameter (e. pixelFormat
width,height and depth) stay the same
Use the doCopy parameter to specify, whether
the method should copy or link the pixel data.

*/
bool Image::setData(const UChar8 *da, bool doCopy)
{
    return createData(da, doCopy);
}

//-------------------------------------------------------------------------
/*!

The Image is not just a 2D container. The class can hold 3D (volume)
and movie data. If we have 3D/singleFrame or 2D/multiFrame data without
mipmaps we can flip between this two formats by just swapping the
_frameCount and _depth values. 

*/
bool Image::flipDepthFrameData (void)
{
  bool retCode = false;
  Int32 value;

  if ( (_mipmapCount == 1) && ((_frameCount == 1) || (_depth == 1)) ) 
  {
      value = _frameCount;
      _frameCount = _depth;
      _depth = value;
      retCode = true;
  }
  else 
  {
      FWARNING (("Cant flipDepthFrameData(); invalid data layout\n"));
  }

  return retCode;
}

//-------------------------------------------------------------------------
/*!

This method is used by the parser to fill the image with
string pixel data. It expects the data in VRML PixelTexture Format.

*/
bool Image::addValue(const char *value)
{
    static Image       *currentImage = 0;
    static UChar8      *currentData  = 0;

           Int64        j;
           Int64        v;

           bool         isHead = strchr(value, ' ') ? true : false;

    // make sure we only read one image at a time
    if(currentImage == this)
    {
        if(isHead)
        {
            FDEBUG(("Start new read cycle in image::addValue()\n"));
        }
    }
    else
    {
        if(!isHead)
        {
            FFATAL(("Additional image date for different image\n"));
        }
    }

    currentImage = this;

    if(isHead == true)
    {
        Int32        width;
        Int32        height;
        Int32        pixelDepth;
        PixelFormat  pf;

        // read the head
        sscanf(value, "%d %d %d", &width, &height, &pixelDepth);

        FDEBUG(("Image::addValue() set: w/h/bpp: %d/%d/%d\n", 
                width, height, pixelDepth));

        switch(pixelDepth)
        {
            case 1:
                pf = osg::Image::OSG_L_PF;
                break;
            case 2:
                pf = osg::Image::OSG_LA_PF;
                break;
            case 3:
                pf = osg::Image::OSG_RGB_PF;
                break;
            case 4:
                pf = osg::Image::OSG_RGBA_PF;
                break;
            default:
                pf = osg::Image::OSG_INVALID_PF;
                FFATAL(("Invalid pixel depth: %d\n", pixelDepth));
                break;
        }

        if(pf != 0 && (width > 0) && (height > 0))
        {
            set(pf, width, height);

            currentData = _data;
        }
        else
        {
            currentData = NULL;
        }
    }
    else
    {
        if(currentData != NULL)
        {
            // add data
            // TODO; should we check the bounds, should be done by the parser ?

            v = strtoul(value, 0, strchr(value, 'x') ? 16 : 10);

            for(j = _bpp; j--;)
            {
                *currentData++ = UChar8( (v >> (8 * j)) & 255 );
            }

        }
    }

    return currentData ? true : false;
}

//-------------------------------------------------------------------------
/*!

It is a simple method to reformat the image pixelFormat (not the size).
So you can for example convert a RGBA to RGB or RGB to Grey image.

*/
bool Image::reformat ( const Image::PixelFormat pixelFormat, 
                       Image *destination )
{  
  UChar8 *data = 0;
  UInt32 srcI, destI, destSize = 0;
  UInt32 sum;
  Image *dest = destination ? destination : new Image;

  FINFO (( "Try to reformat image from pixelDepth %d to %d\n",
           _pixelFormat, pixelFormat ));

  // TODO !!! code all the cases !!!

  if ( getSize() && pixelFormat && 
       (destination || (pixelFormat != _pixelFormat) ) )
  {
      dest->set(pixelFormat, _width, _height, _depth );
      data = dest->_data;
      destSize = dest->getSize();
      if (data) 
        switch (_pixelFormat) {
          //-----------------------------------------------------
        case OSG_L_PF: 
          switch (pixelFormat) {
          case OSG_L_PF:
            memcpy (_data,data,destSize);
            break;
          case OSG_LA_PF:
            for (srcI = destI = 0; destI < destSize; ) 
              {
                data[destI++] = _data[srcI];
                data[destI++] = _data[srcI++];
              }
            break;
          case OSG_RGB_PF:
            for (srcI = destI = 0; destI < destSize; ) 
              {
                data[destI++] = _data[srcI];
                data[destI++] = _data[srcI];
                data[destI++] = _data[srcI++];
              }
            break;
          case OSG_RGBA_PF:
            for (srcI = destI = 0; destI < destSize; ) 
              {
                data[destI++] = _data[srcI];
                data[destI++] = _data[srcI];
                data[destI++] = _data[srcI];
                data[destI++] = _data[srcI++];
              }
            break;
          default:
            break;
          }
          break;
          //-----------------------------------------------------
        case OSG_LA_PF: 
          switch (pixelFormat) {
          case OSG_L_PF:
            for (srcI = destI = 0; destI < destSize; ) 
              {
                data[destI++] = _data[srcI++];
                srcI++;
              }
            break;
          case OSG_LA_PF:
            memcpy (_data,data,destSize);
            break;
          case OSG_RGB_PF:
            for (srcI = destI = 0; destI < destSize; ) 
              {
                data[destI++] = _data[srcI];
                data[destI++] = _data[srcI];
                data[destI++] = _data[srcI++];
                srcI++;
              }
            break;
          case OSG_RGBA_PF:
            for (srcI = destI = 0; destI < destSize; ) 
              {
                data[destI++] = _data[srcI];
                data[destI++] = _data[srcI];
                data[destI++] = _data[srcI++];
                data[destI++] = _data[srcI++];
              }
            break;
          default:
            break;
          }
          break;
          //-----------------------------------------------------
        case OSG_RGB_PF: 
          switch (pixelFormat) 
            {
            case OSG_L_PF:
              for (srcI = destI = 0; destI < destSize; ) 
                {
                  sum = 0;
                  sum += _data[srcI++];
                  sum += _data[srcI++];
                  sum += _data[srcI++];
                  data[destI++] = sum / 3;
                }               
              break;
            case OSG_LA_PF:
              for (srcI = destI = 0; destI < destSize; ) 
                {
                  sum = 0;
                  sum += _data[srcI++];
                  sum += _data[srcI++];
                  sum += _data[srcI++];
                  data[destI++] = sum / 3;
                  data[destI++] = sum / 3;
                }               
              break;
            case OSG_RGB_PF:
              memcpy (_data,data,destSize);
              break;
            case OSG_RGBA_PF:
              for (srcI = destI = 0; destI < destSize; ) 
                {
                  sum = 0;
                  sum += data[destI++] = _data[srcI++];
                  sum += data[destI++] = _data[srcI++];
                  sum += data[destI++] = _data[srcI++];
                  data[destI++] = sum / 3;
                }
              break;
            default:
              break;
            }
          break;
          //-----------------------------------------------------
        case OSG_RGBA_PF: 
          switch (pixelFormat) {
          case OSG_L_PF:
            for (srcI = destI = 0; destI < destSize; ) 
              {
                sum = 0;
                sum += _data[srcI++];
                sum += _data[srcI++];
                sum += _data[srcI++];
                data[destI++] = sum / 3;
                srcI++;
              }               
            break;
          case OSG_LA_PF:
            for (srcI = destI = 0; destI < destSize; ) 
              {
                sum = 0;
                sum += _data[srcI++];
                sum += _data[srcI++];
                sum += _data[srcI++];
                data[destI++] = sum / 3;
                data[destI++] = _data[srcI++];
              }               
            break;
          case OSG_RGB_PF:
            for (srcI = destI = 0; destI < destSize; ) 
              {
                data[destI++] = _data[srcI++];
                data[destI++] = _data[srcI++];
                data[destI++] = _data[srcI++];
                srcI++;
              }               
            break;
          case OSG_RGBA_PF:
            memcpy (_data,data,destSize);
            break;
          default:
            break;
          }
          break;
        default:
          FWARNING (( "Unvalid pixeldepth (%d) in Image::reformat() !\n",
                      pixelFormat ));
        }
      if (data) 
      {
        if (!destination) 
        {
          *this = *dest;
          delete dest;
        }
      }
    }
  
  return (data ? true : false);
}

//-------------------------------------------------------------------------
/*!

It just fills the hole image data with the given pixel value. It is 
mainly used to initialize the image data.

*/
void Image::clear(UChar8 pixelValue)
{
    unsigned long   n = getSize();
    UChar8          *d = _data;

    if(n && d)
        while(n--)
            *d++ = pixelValue;
}

//-------------------------------------------------------------------------
/*!

The dump method just writes some object debugging info to the LOG stream

*/
void Image::dump(void)
{
    const char  *pfStr = "UNDEF_PIXEL_FORMAT";

    switch(_pixelFormat)
    {
    case OSG_L_PF:
        pfStr = "LUMINANCE";
        break;
    case OSG_LA_PF:
        pfStr = "LUMINANCE_ALPHA";
        break;
#ifdef OSG_HAS_BGR_PF
    case OSG_BGR_PF:
        pfStr = "BGR";
        break;
#endif
#ifdef OSG_HAS_BGRA_PF
    case OSG_BGRA_PF:
        pfStr = "BGRA";
        break;
#endif
    case OSG_RGB_PF:
        pfStr = "RGB";
        break;
    case OSG_RGBA_PF:
        pfStr = "RGBA";
        break;
    default:
        pfStr = "UNKNOWN_PIXEL_FORMAT";
        break;
    };

    FLOG (("ImageDump: %s; %d/%d/%d; #mm: %d, #frame: %d, frameDelay %g\n",
         pfStr, _width, _height, _depth, _mipmapCount, _frameCount, _frameDelay
         ));

    if (!_attachmentMap.empty()) {
      FLOG (("ImageDump: Attachments:\n"));
      for (std::map<std::string,std::string>::iterator iter = _attachmentMap.begin();
	 iter != _attachmentMap.end();
	 iter++) {
        FLOG (("%s \t\t >%s<\n", iter->first.c_str(), iter->second.c_str()));
      }
    }
}

//-------------------------------------------------------------------------
/*!

Method to scale the image. It just does a very simple but fast
'nearest' scale. Should handle mipmap and frame data correct.
The method can operate on the object or stores the result in 
the optional destination Image.

*/
bool Image::scale(Int32 width, Int32 height, Int32 depth, Image *destination)
{
    Image   *destImage = destination ? destination : new Image;
    bool    retCode = true;
    UInt32  sw, sh, sd, dw, dh, dd;
    Int32   frame, mipmap;
    UChar8  *src, *dest;

    if(width != _width || height != _height || depth != _depth)
    {
        // set image data
        destImage->set(_pixelFormat, width, height, depth, _mipmapCount,
                       _frameCount, _frameDelay, 0);

        // copy every mipmap in every frame
        for(frame = 0; frame < _frameCount; frame++)
        {
            for(mipmap = 0; mipmap < _mipmapCount; mipmap++)
            {
                // get the memory pointer
                src = this->getData(mipmap, frame);
                dest = destImage->getData(mipmap, frame);

                // calc the mipmap size
                this->calcMipmapGeometry(mipmap, sw, sh, sd);
                destImage->calcMipmapGeometry(mipmap, dw, dh, dd);

                // copy and scale the data
                scaleData(src, sw, sh, sd, dest, dw, dh, dd);
            }
        }

        // rip the data from the local destImage if necessary
        if(!destination)
        {
            this->set(*destImage,false);
            destImage->_data = 0;
            delete destImage;
        }
    }
    else
    {       // same size; just copy the data necessary
        if(destination)
            *destination = *this;
    }

    return retCode;
}

//-------------------------------------------------------------------------
/*!

Scale the image to the next power of 2 dimensions
The method can operate on the object or stores the result in 
the optional destination Image.

*/
bool Image::scaleNextPower2(Image *destination)
{
  return scale ( osgnextpower2(_width), 
                 osgnextpower2(_height),
                 osgnextpower2(_depth),
                 destination );
}

//-------------------------------------------------------------------------
/*!

Crop the image to the given bounding box. 
The method can operate on the object or stores the result in 
the optional destination Image.

*/
bool Image::subImage ( Int32 offX, Int32 offY, Int32 offZ,
                       Int32 destW, Int32 destH, Int32 destD,
                       Image *destination)
{
    Image   *destImage = destination ? destination : new Image;
    bool    retCode = true;
    
    destImage->set(_pixelFormat, destW, destH, destD);
    
    UChar8  *src  = getData();
    UChar8  *dest = destImage->getData();

    FDEBUG(("Image::subImage (%d %d %d) - (%d %d %d) - destPtr %p\n",
            offX, offY, offZ, destW, destH, destD, dest));
    
    // ensure destination data is zero
    memset(dest, 0, destImage->getSize());

    // determine the area to actually copy
    UInt32 xMin = offX;
    UInt32 yMin = offY;
    UInt32 zMin = offZ;

    UInt32 xMax = osgMin(_width,  offX + destW);
    UInt32 yMax = osgMin(_height, offY + destH);
    UInt32 zMax = osgMin(_depth,  offZ + destD);

    // fill the destination buffer with the subdata
    UInt32 destIdx = 0;
    
    for(UInt32 z = zMin; z < zMax; z++) 
    {
      for(UInt32 y = yMin; y < yMax; y++) 
      {
        for(UInt32 x = xMin; x < xMax; x++) 
        {
          for(UInt32 i = 0; i < _bpp; i++) 
          {
            dest[destIdx] = src[((z * _height + y) * _width + x) * _bpp + i];
            destIdx++;
          }
        }
        destIdx += (destW - (xMax - xMin)) * _bpp;
      }
      destIdx += (destH - (yMax - yMin)) * destW * _bpp;
    }

    
    // rip the data from the local destImage if necessary
    if(!destination)
    {
      delete[] _data;
      _data = destImage->_data;
      destImage->_data = 0;
      delete destImage;
    }

    return retCode;
}

//-------------------------------------------------------------------------
/*!

Crop a slice.
The method can operate on the object or stores the result in 
the optional destination Image.

*/
bool Image::slice ( Int32 offX, Int32 offY, Int32 offZ,
                    Image *destination)
{
    Image   *destImage = destination ? destination : new Image;
    bool    retCode = true;
    UInt32  counter = 0;
    
    FDEBUG(("Image::slice (%d %d %d)\n",
	    offX, offY, offZ));

    if (offX >= 0) counter++;
    if (offY >= 0) counter++;
    if (offZ >= 0) counter++;

    if (counter != 1) {
        FWARNING(("Image::slice - more/less than one non negative value\n"));
        return false;
    }
    
	
    if (offZ >= 0) {
        // XY slice
        retCode = subImage( 0, 0, offZ, _width, _height, 1, destImage );
    }


    if (offY >= 0) {
        // XZ slice
        destImage->set(_pixelFormat, _width, _depth, 1);
    
        UChar8  *src  = getData();
        UChar8  *dest = destImage->getData();

        // ensure destination data is zero
        memset(dest, 0, destImage->getSize());
        
        for(UInt32 z = 0; z < _depth; z++) 
        { 
          for(UInt32 x = 0; x < _width; x++) 
          { 
            for(UInt32 i = 0; i < _bpp; i++) 
            { 
              dest[(z * _width + x) * _bpp + i] = src[((z * _height + offY) * 
                                                       _width + x) * 
                                                     _bpp + i]; 
            }
          }
        } 
    } 

    
    if (offX >= 0) {
        // YZ slice
        destImage->set(_pixelFormat, _height, _depth, 1);
      
        UChar8  *src  = getData();
        UChar8  *dest = destImage->getData();
        
        // ensure destination data is zero
        memset(dest, 0, destImage->getSize());
        
        for(UInt32 z = 0; z < _depth; z++) 
        { 
          for(UInt32 y = 0; y < _height; y++) 
          { 
            for(UInt32 i = 0; i < _bpp; i++) 
            { 
              dest[(z * _height + y) * _bpp + i] = src[((z * _height + y) * 
                                                        _width + offX) * 
                                                      _bpp + i]; 
            } 
          } 
        }
    }
  

    // rip the data from the local destImage if necessary
    if(!destination)
    {
        delete[] _data;
        _data = destImage->_data;
        destImage->_data = 0;
        delete destImage;
    }

    return retCode;
}

//-------------------------------------------------------------------------
/*!

Create mipmaps data, level defines the number of level
The method can operate on the object or stores the result in 
the optional destination Image.

*/
bool Image::createMipmap(Int32 level, Image *destination)
{
    struct Offset
    {
      Int32   w;
      Int32   h;
      Int32   d;
    };
  
    Offset  offset[][8] =
    {
        {   // 000
            { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 
            { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
        {   // 100
            { 0, 0, 0 }, { 1, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 
            { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
        {   // 010
            { 0, 0, 0 }, { 0, 1, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 
            { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
        {   // 110
            { 0, 0, 0 }, { 0, 1, 0 }, { 1, 0, 0 }, { 1, 1, 0 }, 
            { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
        {   // 001
            { 0, 0, 0 }, { 0, 0, 1 }, { 0, 0, 0 }, { 0, 0, 0 }, 
            { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
        {   // 101
            { 0, 0, 0 }, { 1, 0, 0 }, { 0, 0, 1 }, { 1, 0, 1 }, 
            { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
        {   // 110
            { 0, 0, 0 }, { 1, 0, 0 }, { 0, 1, 0 }, { 0, 1, 1 }, 
            { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
        {   // 111
            { 0, 0, 0 }, { 1, 0, 0 }, { 0, 1, 0 }, { 1, 1, 0 }, 
            { 0, 0, 1 }, { 1, 0, 1 }, { 0, 1, 1 }, { 1, 1, 1 } }
    };
    Int32   offsetSize[] = { 0, 2, 2, 4, 2, 4, 4, 8 };
    Image   *destImage = destination ? destination : new Image;
    Int32   w = _width, h = _height, d = _depth;
    Int32   wm, hm, dm, wi, hi, di;
    UChar8  *src, *dest;

    /* ,*pixel; */
    Int32   value, i, elem, dim, frame, size, mipmap;
    Int32   channel, lineSize, sliceSize;

    // calc the level count
    if(level < 0)
    {
        level = calcMipmapLevelCount() - 1;
    }

    // create destination image
    destImage->set(_pixelFormat, _width, _height, _depth, level, _frameCount,
                   _frameDelay, 0);

    // copy the data;
    for(frame = 0; frame < _frameCount; frame++)
    {
        src = this->getData(0, frame);
        dest = destImage->getData(0, frame);
        size = _width * _height * _depth * _bpp;
        memcpy(src, dest, size);
        src = dest;
        dest = src + size;
        w = _width;
        h = _height;
        d = _depth;
        for(mipmap = 1; mipmap < level; mipmap++)
        {
            dim = (d > dm) * 1 + (h > hm) * 2 + (w > wm) * 4;
            elem = offsetSize[dim];
            lineSize = w * _bpp;
            sliceSize = w * h * _bpp;
            wm = (w == 1) ? w : (w >> 1);
            hm = (h == 1) ? h : (h >> 1);
            dm = (d == 1) ? d : (d >> 1);
            for(di = 0; di < dm; di++)
            {
                for(hi = 0; hi < hm; hi++)
                {
                    for(wi = 0; wi < wm; wm++)
                    {
                        for(channel = _bpp; channel < _bpp; channel++)
                        {
                            value = 0;
                            for(i = 0; i < elem; i++)
                            {
                                value += src[
                                    ((wi * 2) + offset[dim][i].w) * _bpp +
                                        (
                                            (hi * 2) +
                                            offset[dim][i].h
                                        ) *
                                                lineSize +
                                                ((di * 2) + offset[dim][i].d) *
                                                sliceSize +
                                                channel];
                            }

                            *dest++ = value / elem;
                        }
                    }
                }
            }

            src += sliceSize;
            w = wm;
            h = hm;
            d = dm;
        }
    }

    // rip the data from the local destImage if necessary
    if(!destination)
    {
        delete[] _data;
        _data = destImage->_data;
        destImage->_data = 0;
        delete destImage;
    }

    return true;
}

//-------------------------------------------------------------------------
/*!

Write the image to the a file. The mimetype will be set automatically
from the fileName suffix. Returns true on success.

*/
bool Image::write(const Char8 *fileName)
{
    return ImageFileHandler::the().write(*this, fileName);
}

//-------------------------------------------------------------------------
/*!

Read the image data from a file. Returns true on success.

*/
bool Image::read(const Char8 *fileName)
{
    return ImageFileHandler::the().read(*this, fileName);
}

//-------------------------------------------------------------------------
/*!

Store the image to the given mem block as 'mimeType'. 
mimeType can be 0, in which case the method will store the
object as uncompressed mtd data.
Returns the number of bytes used.

*/
UInt64 Image::store(Char8 *mimeType, UChar8 *mem, Int32 memSize)
{
    return ImageFileHandler::the().store(*this, mimeType, mem, memSize);
}

//-------------------------------------------------------------------------
/*!

Restore the image from the given mem block. Returns the
number of bytes used. 

*/
UInt64 Image::restore(const UChar8 *mem, Int32 memSize)
{
    return ImageFileHandler::the().restore(*this, mem, memSize);;
}

//-------------------------------------------------------------------------
/*!

Internal method to set the data and update related properties.

*/
bool Image::createData(const UChar8 *data, bool doCopy)
{
    Int32   i, mapSize = sizeof(_formatDic) / sizeof(UInt32[2]);
    UInt32 byteCount = 0;

    // set bbp
    for(i = 0; i < mapSize; i++)
    {
        if(_formatDic[i][0] == _pixelFormat)
            _bpp = _formatDic[i][1];
    }

    // set dimension
    _dimension = 0;
    if(_depth == 1)
    {
        if(_height == 1)
            _dimension = 1;
        else
            _dimension = 2;
    }
    else
        _dimension = 3;

    // set frameSize
    _frameSize = calcMipmapSumSize(_mipmapCount - 1);

    FINFO(("FrameSize: %d\n", _frameSize));

    // delete old data
    if(_isCopy && _data)
        delete[] _data;

    // copy/link the data
    if((_isCopy = doCopy))
    {
        if((byteCount = getSize()))
        {
            _data = new UChar8[byteCount];
            if(_data)
            {
                if(data)
                    memcpy(_data, data, byteCount);
            }
            else
            {
                FFATAL(("Can not alloc mem for image data\n"));
            }
        }
        else
        {
            _data = 0;
        }
    }
    else
    {
        _data = const_cast < UChar8 * > (data);
    }

    return _data;
}

//-------------------------------------------------------------------------
/*!

Internal method to scale image data blocks

*/
bool Image::scaleData(UChar8 *srcData, Int32 srcW, Int32 srcH, Int32 srcD,
                      UChar8 *destData, Int32 destW, Int32 destH, Int32 destD)
{
    Real32  sx = Real32(srcW) / Real32(destW);
    Real32  sy = Real32(srcH) / Real32(destH);
    Real32  sz = Real32(srcD) / Real32(destD);
    Int32   srcSize = srcW * srcH * srcD;

    //  Int32 destDize = destW * destH * destD;
    Int32   x, y, z, p;
    UChar8  *slice, *line, *pixel;

    if(destW == srcW && destH == srcH && destD == srcD)
    {
        // same size, just copy
        memcpy(destData, srcData, srcSize);
    }
    else
    {       // different size, to 'nearest' copy
        for(z = 0; z < destD; z++)
        {
            slice = srcData + int(sz * z + 0.5) * _bpp * srcW * srcH;
            for(y = 0; y < destH; y++)
            {
                line = slice + int(sy * y + 0.5) * _bpp * srcW;
                for(x = 0; x < destW; x++)
                {
                    pixel = line + int(sx * x + 0.5) * _bpp;
                    p = _bpp;
                    while(p--)
                        *destData++ = *pixel++;
                }
            }
        }
    }

    return true;
}

//-------------------------------------------------------------------------
/*! Default Constructor. 

Creates a invalid Image of the size 0x0x0

*/
Image::Image(void) :
    _pixelFormat(OSG_INVALID_PF),
    _width(0),
    _height(0),
    _depth(0),
    _mipmapCount(0),
    _frameCount(0),
    _frameDelay(0),
    _bpp(0),
    _dimension(0),
    _isCopy(true),
    _data(0)
{
    return;
}

//-------------------------------------------------------------------------
/*! Copy Constructor. 

Creates a copy of the given image

*/
Image::Image(const Image &obj) :
    _pixelFormat(obj._pixelFormat),
    _width(obj._width),
    _height(obj._height),
    _depth(obj._depth),
    _mipmapCount(obj._mipmapCount),
    _frameCount(obj._frameCount),
    _frameDelay(obj._frameDelay),
    _bpp(0),
    _dimension(0),
    _isCopy(true),
    _data(0)
{
    createData(obj._data, true);

#ifdef OSG_DEBUG
    FDEBUG(("Running OSGImage copy constructor\n"));
    this->dump();
#endif
}

//-------------------------------------------------------------------------
/*! Destructor

Destructor will delete the pixeldata if not linked;

*/
Image::~Image(void)
{
    if(_isCopy && _data)
    {
        delete[] _data;
        _data = 0;
    }
}

//-------------------------------------------------------------------------
/*! Constructor

Full Constructor. Takes all necessary image parameter to 
construct a valid image.

*/
Image::Image(PixelFormat pixelFormat, Int32 width, Int32 height, Int32 depth,
             Int32 mipmapCount, Int32 frameCount, Time frameDelay,
             const UChar8 *data, bool doCopy) :
    _pixelFormat(pixelFormat),
    _width(width),
    _height(height),
    _depth(depth),
    _mipmapCount(mipmapCount),
    _frameCount(frameCount),
    _frameDelay(frameDelay),
    _bpp(0),
    _dimension(0),
    _isCopy(true),
    _data(0)
{
    createData(data, doCopy);
}

//-------------------------------------------------------------------------
/*!

Method to check, whether the object data defines a alpha channel or not

*/
bool Image::hasAlphaChannel(void)
{
    return _pixelFormat == OSG_RGBA_PF
#ifdef OSG_HAS_BGRA_PF
    || _pixelFormat == OSG_BGRA_PF
#endif
    || _pixelFormat == OSG_LA_PF;
}

//-------------------------------------------------------------------------
/*!

Method returns the right frame data for the given time.

*/
UChar8 *Image::getDataByTime (Time   time, UInt32 mipmapNum) const
{
  UInt32 frameNum = calcFrameNum(time,true);
  
  return getData(0,frameNum);
}

//-------------------------------------------------------------------------
/*!

Method which returns the frame number for the given time

*/
UInt32 Image::calcFrameNum(Time time, bool OSG_CHECK_ARG(loop)) const
{
    int frameNum = ((_frameDelay > 0) && (_frameCount > 0)) ?
        (int(time / _frameDelay) % _frameCount) : 0;
    
    return ((frameNum > 0) ? frameNum : 0);
}

//-------------------------------------------------------------------------
/*!

Assign operator. Does a copy of the given Image object.

*/
Image &Image::operator=(const Image &image)
{
    this->set(image._pixelFormat, image._width, image._height, image._depth,
              image._mipmapCount, image._frameCount, image._frameDelay,
              image._data);

#ifdef OSG_DEBUG
    FDEBUG(("Running image assign operator\n"));
    this->dump();
#endif
    return *this;
}

//-------------------------------------------------------------------------
/*!

Less operator; compares the data sizes of the two images

*/
bool Image::operator<(const Image &image)
{
    return (getSize() < image.getSize()) ? true : false;
}

#include <OSGSFieldTypeDef.inl>
#include <OSGMFieldTypeDef.inl>

OSG_BEGIN_NAMESPACE 

DataType FieldDataTraits<ImageP>::  _type("ImageP", NULL);

OSG_DLLEXPORT_SFIELD_DEF1(ImageP, OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(ImageP, OSG_SYSTEMLIB_DLLTMPLMAPPING);

OSG_END_NAMESPACE

//-------------------------------------------------------------------------
/*!

Method to compare the object to another Image instance; 
Checks first all parameter and afterwards the Image data;

*/
bool Image::operator==(const Image &image)
{
    unsigned long   i, s = getSize();

    if((_width == image._width) &&
       (_height == image._height) &&
       (_depth == image._depth) &&
       (_mipmapCount == image._mipmapCount) &&
       (_frameCount == image._frameCount) &&
       (_frameDelay == image._frameDelay) &&
       (_pixelFormat == image._pixelFormat))
    {
        for(i = 0; i < s; ++i)
        {
            if(image._data[i] != _data[i])
                return false;
        }

        return true;
    }

    return false;
}

//-------------------------------------------------------------------------
/*!

Method to compare the object to another Image instance; 
Checks first all parameter and afterwards the Image data;

*/
bool Image::operator!=(const Image &image)
{
  return !(*this == image);
}
