/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

/*! \class osg::Image 
 */


Int32 Image::_formatMap[][2] =
{
    { OSG_L_PF, 1 },
    { OSG_LA_PF, 2 },
    { OSG_RGB_PF, 3 },
    { OSG_RGBA_PF, 4 },
#ifdef OSG_HAS_BGR_PF
    { OSG_BGR_PF, 3 },
#endif
#ifdef OSG_HAS_BGRA_PF
    { OSG_BGRA_PF, 4 },
#endif
};

/* enum VecBase::VectorSizeE
 * brief 
*/

/* var VecBase::VectorSizeE VecBase::_iSize
 *
*/

/* const Char8 *VecBase::getClassName(void)
 *  brief Classname
*/

/* var ValueTypeT VecBase:: _value[Size];
 * brief value store
*/

/*****************************
 *   Types
 *****************************/

/*****************************
 *    Classvariables
 *****************************/

/********************************
 *    Class methodes
 *******************************/

/*******************************
*public
*******************************/

//----------------------------
// Function name: set
//----------------------------
//
//Parameters:
//p: PixelFormat pixelFormat, Int32 width, Int32 height, Int32 depth, Int32 mipmapCount, Int32 frameCount, Time frameDelay, const UChar8 *data
//GlobalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: set methode wich sets the image data
//SeeAlso:
//s:
//
//------------------------------
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

//----------------------------
// Function name: set
//----------------------------
//
//Parameters:
//p: PixelFormat pixelFormat, Int32 width, Int32 height, Int32 depth, Int32 mipmapCount, Int32 frameCount, Time frameDelay, const UChar8 *data
//GlobalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: set methode wich sets the image data
//SeeAlso:
//s:
//
//------------------------------
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

//----------------------------
// Function name: set
//----------------------------
//
//Parameters:
//p:obalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: set methode wich sets the image data
//SeeAlso:
//s:
//
//------------------------------
bool Image::setData(const UChar8 *da, bool doCopy)
{
    return createData(da, doCopy);
}

//----------------------------
// Function name: set
//----------------------------
//
//Parameters:
//p:obalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: set methode wich sets the image data
//SeeAlso:
//s:
//
//------------------------------
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

//----------------------------
// Function name: addValue
//----------------------------
//
//Parameters:
//p: const char *value
//GlobalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: set methode wich sets the image data
//SeeAlso:
//s:
//
//------------------------------
bool Image::addValue(const char *value)
{
    static Image    *currentImage = 0;
    static UChar8   *currentData = 0;

    Int32           width, height, pixelDepth;
    Int64           j, v;

    //    UChar8  *data;
    PixelFormat     pf;
    bool            isHead = strchr(value, ' ') ? true : false;

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

    if(isHead)
    {
        // read the head
        sscanf(value, "%d %d %d", &width, &height, &pixelDepth);

        FDEBUG(("Image::addValue() set: w/h/bpp: %d/%d/%d\n", width, height,
               pixelDepth));

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

        if(pf && (width > 0) && (height > 0))
        {
            set(pf, width, height);
            currentData = _data;
        }
        else
        {
            currentData = 0;
        }
    }
    else
    {
        if(currentData)
        {
            // add data
            // TODO; should we check the bounds, should be done by the parser ?
            v = strtoul(value, 0, strchr(value, 'x') ? 16 : 10);
            for(j = _bpp; j--;)
                *currentData++ = (v >> (8 * j)) & 255;
        }
    }

    return currentData ? true : false;
}

//----------------------------
// Function name: reformat
//----------------------------
//
//Parameters:
//p: const Char8 *pixelFormat, Image *destination = 0
//GlobalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: reformate the image to the given pixelFormat
//SeeAlso:
//s:
//
//------------------------------
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

  if ( getSize() && pixelFormat && (pixelFormat != _pixelFormat) ) 
    {
      dest->set(pixelFormat, _width, _height, _depth );
      data = dest->_data;
      destSize = dest->getSize();
      if (data) 
        switch (_pixelFormat) {
        case OSG_L_PF: // source pixelFormat == 1
          switch (pixelFormat) {
          case OSG_L_PF:
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
          }
          break;
        case OSG_LA_PF: // source pixelFormat == 2
          switch (pixelFormat) {
          case OSG_L_PF:
            for (srcI = destI = 0; destI < destSize; ) 
              {
                data[destI++] = _data[srcI++];
                srcI++;
              }
            break;
          case OSG_LA_PF:
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
          }
          break;
        case OSG_RGB_PF: // source pixelFormat == 3
          switch (pixelFormat) 
            {
            case OSG_L_PF:
              break;
            case OSG_LA_PF:
              break;
            case OSG_RGB_PF:
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
            }
          break;
        case OSG_RGBA_PF: // source pixelFormat == 4
          switch (pixelFormat) {
          case OSG_L_PF:
            break;
          case OSG_LA_PF:
            break;
          case OSG_RGB_PF:
            break;
          case OSG_RGBA_PF:
            break;
          }
          break;
        default:
          FWARNING (( "Unvalid pixeldepth (%d) in Image::reformat() !\n",
                      pixelFormat ));
        }
      if (data) {
        if (!destination) {
          *this = *dest;
          delete dest;
        }
      }
    }
  
  return (data ? true : false);
}

//----------------------------
// Function name: clear
//----------------------------
//
//Parameters:
//p: UChar8 pixelValue
//GlobalVars:
//g:
//Returns:
//r:void
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: method to load the image data from the given file
//SeeAlso:
//s:
//----------------------------------------------------------------------
void Image::clear(UChar8 pixelValue)
{
    unsigned long   n = getSize();
    UChar8          *d = _data;

    if(n && d)
        while(n--)
            *d++ = pixelValue;
}

//----------------------------
// Function name: dump
//----------------------------
//
//Parameters:
//p:
//GlobalVars:
//g:
//Returns:
//r:void
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: method to load the image data from the given file
//SeeAlso:
//s:
//----------------------------------------------------------------------
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

    FLOG(("ImageDump: %s; %d/%d/%d; #mm: %d, #frame: %d, frameDelay %g\n",
         pfStr, _width, _height, _depth, _mipmapCount, _frameCount, _frameDelay
         ));

    if (!_attachmentMap.empty()) {
      FLOG(("ImageDump: Attachments:\n"));
      for (std::map<std::string,std::string>::iterator iter = _attachmentMap.begin();
	 iter != _attachmentMap.end();
	 iter++) {
	FLOG(("%s \t\t >%s<\n", iter->first.c_str(), iter->second.c_str()));
      }
    }
}

//----------------------------
// Function name: scale
//----------------------------
//
//Parameters:
//p: int width, int height, int depth =1, Image *destination = 0
//GlobalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: scale the image to the given dimension
//SeeAlso:
//s:
//
//------------------------------
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
    }
    else
    {       // same size; just copy the data necessary
        if(destination)
            *destination = *this;
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


//----------------------------
// Function name: subImage
//----------------------------
//
//Parameters:
//p: Int32 offX, Int32 offY, Int32 offZ, Int32 destW, Int32 destH, Ind32 destD, Image *destination = 0
//GlobalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: create a subImage according to given offset and size
//SeeAlso:
//s:
//
//------------------------------
bool Image::subImage ( Int32 offX, Int32 offY, Int32 offZ,
		       Int32 destW, Int32 destH, Int32 destD,
		       Image *destination)
{
    Image   *destImage = destination ? destination : new Image;
    bool    retCode = true;
    
    destImage->set(_pixelFormat, destW, destH, destD);
    
    UChar8  *src  = getData();
    UChar8  *dest = destImage->getData();

    FDEBUG(("Image::subImage (%d %d %d) - (%d %d %d)\n",
	    offX, offY, offZ, destW, destH, destD));
    
    // ensure destination data is zero
    memset(dest, 0, _bpp);

    // determine the area to actually copy
    UInt32 xMin = offX;
    UInt32 yMin = offY;
    UInt32 zMin = offZ;

    UInt32 xMax = osgMin(_width,  offX + destW);
    UInt32 yMax = osgMin(_height, offY + destH);
    UInt32 zMax = osgMin(_depth,  offZ + destD);

    
    // fill the destination buffer with the subdata
    UInt32 destIdx = 0;
    
    for(UInt32 z = zMin; z < zMax; z++) {
      for(UInt32 y = yMin; y < yMax; y++) {
	for(UInt32 x = xMin; x < xMax; x++) {
	  for(UInt32 i = 0; i < _bpp; i++) {
	    dest[destIdx] = src[((z * _height + y) * _width + x) * _bpp + i];
	    destIdx++;
	  }
	}
	destIdx += destW - (xMax - xMin) * _bpp;
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


//----------------------------
// Function name: scale
//----------------------------
//
//Parameters:
//p: int width, int height, int depth =1, Image *destination = 0
//GlobalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: scale the image to the given dimension
//SeeAlso:
//s:
//
//------------------------------
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

//----------------------------
// Function name: write
//----------------------------
//
//Parameters:
//p: const Char8 *fileName
//GlobalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: methode to write the image data to the given File
//SeeAlso:
//s:
//
//------------------------------
bool Image::write(const Char8 *fileName)
{
    return ImageFileHandler::the().write(*this, fileName);
}

//----------------------------
// Function name: read
//----------------------------
//
//Parameters:
//p: const Char8 *fileName
//GlobalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: methode to read the image data from the given File
//SeeAlso:
//s:
//
//------------------------------
bool Image::read(const Char8 *fileName)
{
    return ImageFileHandler::the().read(*this, fileName);
}

//----------------------------
// Function name: store
//----------------------------
//
//Parameters:
//p: const Char8 *fileName
//GlobalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d:
//SeeAlso:
//s:
//
//------------------------------
UInt64 Image::store(Char8 *mimeType, UChar8 *mem, Int32 memSize)
{
    return ImageFileHandler::the().store(*this, mimeType, mem, memSize);
}

//----------------------------
// Function name: restore
//----------------------------
//
//Parameters:
//p: const Char8 *fileName
//GlobalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d:
//SeeAlso:
//s:
//
//------------------------------
UInt64 Image::restore(const UChar8 *mem, Int32 memSize)
{
    return ImageFileHandler::the().restore(*this, mem, memSize);;
}

/******************************
*protected
******************************/

/******************************
*private    
******************************/

//----------------------------
// Function name: createData
//----------------------------
//
//Parameters:
//p: const UChar8 *data, bool doCopy
//GlobalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: internal method to alloc and copy the image data
//SeeAlso:
//s:
//
//------------------------------
bool Image::createData(const UChar8 *data, bool doCopy)
{
    Int32   i, mapSize = sizeof(_formatMap) / sizeof(UInt32[2]);
    UInt32 byteCount = 0;

    // set bbp
    for(i = 0; i < mapSize; i++)
    {
        if(_formatMap[i][0] == _pixelFormat)
            _bpp = _formatMap[i][1];
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

//----------------------------
// Function name: scaleData
//----------------------------
//
//Parameters:
//p: UChar8* srcData, Int32 srcW, Int32 srcH, Int32 srcD, UChar8* destData, Int32 destW, Int32 destH, Int32 destD
//GlobalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: Internal medhot to copy&scale image data
//SeeAlso:
//s:
//
//------------------------------
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


/***************************
*instance methodes 
***************************/

/***************************
*public
***************************/

/**constructors & destructors**/

//----------------------------
// Function name: Image
//----------------------------
//
//Parameters:
//p: void
//GlobalVars:
//g:
//Returns:
//r:
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: Default Constructor
//SeeAlso:
//s:
//
//------------------------------
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

//----------------------------
// Function name: Image
//----------------------------
//
//Parameters:
//p: const wrw &obj
//GlobalVars:
//g:
//Returns:
//r:
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: Copy Constructor
//SeeAlso:
//s:
//
//------------------------------
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

//----------------------------
// Function name: ~Image
//----------------------------
//
//Parameters:
//p: void
//GlobalVars:
//g:
//Returns:
//r:
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: Destructor
//SeeAlso:
//s:
//
//------------------------------
Image::~Image(void)
{
    if(_isCopy && _data)
    {
        delete[] _data;
        _data = 0;
    }
}

//----------------------------
// Function name: Image
//----------------------------
//
//Parameters:
//p: int width, int height, int depth, const Char8 *pixelFormat, UChar8 *data = 0
//GlobalVars:
//g:
//Returns:
//r:
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: construktor
//SeeAlso:
//s:
//
//------------------------------
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

/*------------access----------------*/
bool Image::hasAlphaChannel(void)
{
    return _pixelFormat == OSG_RGBA_PF
#ifdef OSG_HAS_BGRA_PF
    || _pixelFormat == OSG_BGRA_PF
#endif
    || _pixelFormat == OSG_LA_PF;
}

UChar8 *Image::getDataByTime (Time   OSG_CHECK_ARG(time     ), 
                              UInt32 OSG_CHECK_ARG(mipmapNum))
{
    return _data;
}

UInt32 Image::calcFrameNum(Time time, bool OSG_CHECK_ARG(loop))
{
    int frameNum = ((_frameDelay > 0) && (_frameCount > 0)) ?
        (int(time / _frameDelay) % _frameCount) : 0;
    
    return ((frameNum > 0) ? frameNum : 0);
}

/*------------properies-------------*/

/*------------your Category---------*/

/*------------Operators-------------*/

//----------------------------
// Function name: operator ==
//----------------------------
//
//Parameters:
//p: const Image &image
//GlobalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: equal comparison operator
//SeeAlso:
//s:
//
//------------------------------
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

//----------------------------
// Function name: operator =
//----------------------------
//
//Parameters:
//p: const Image &image
//GlobalVars:
//g:
//Returns:
//r: Image &image
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: assign operator
//SeeAlso:
//s:
//
//------------------------------
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

//----------------------------
// Function name: operator <
//----------------------------
//
//Parameters:
//p: const Image &image
//GlobalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: lower comparison operator
//SeeAlso:
//s:
//
//------------------------------
bool Image::operator<(const Image &image)
{
    return (getSize() < image.getSize()) ? true : false;
}

/****************************
*protected  
****************************/
/****************************
*private
****************************/

OSG_BEGIN_NAMESPACE 

DataType FieldDataTraits<ImageP>::  _type("ImageP", NULL);

#if defined(__sgi)
#   pragma instantiate SField < ImageP >::_fieldType
#   pragma instantiate MField < ImageP >::_fieldType
#else
OSG_DLLEXPORT_DEF1(SField, ImageP, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, ImageP, OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE
