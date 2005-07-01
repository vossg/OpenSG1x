/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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
#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>
#include <OSGLog.h>
#include <OSGImage.h>
#include <OSGBaseFunctions.h>

#include "OSGImageFunctions.h"


OSG_USING_NAMESPACE

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning(disable : 383)
#endif
#ifdef __sgi
#pragma set woff 1209
#endif

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/


//---------------------------------------------------------------------------//
/*! composes multiple images to one */

OSG_SYSTEMLIB_DLLMAPPING
bool createComposedImage ( std::vector<ImagePtr> imageVec,
                           ImagePtr              image,
                           SliceDataType         sliceDataType )
{
  UInt32 dataSize, i, n = imageVec.size();
  Int32 w, h;
  UInt8 *destData, *srcData;
  Image::PixelFormat pf;
  Image::Type        dt;
  bool needColor, needAlpha, needCopy = false;
  ImagePtr copy = Image::create();
  UInt32 depth, frameCount, sideCount;

  if (n) {
    for (i = 0; i < n; i++) {
      if ( i == 0 ) {
        pf = Image::PixelFormat(imageVec[0]->getPixelFormat());
        dt = Image::Type(imageVec[0]->getDataType());
        w = imageVec[0]->getWidth();
        h = imageVec[0]->getHeight();
        needAlpha = imageVec[0]->hasAlphaChannel();
        needColor = imageVec[0]->hasColorChannel();
      }
      else {
        needAlpha |= imageVec[i]->hasAlphaChannel();
        needColor |= imageVec[i]->hasColorChannel();
        if (Image::PixelFormat(imageVec[i]->getPixelFormat()) != pf) {
          needCopy = true;          
          FWARNING (( "Image has different PF while composing\n" ));
          pf = Image::OSG_INVALID_PF;
        }
        if (Image::Type(imageVec[i]->getDataType()) != dt) {
          needCopy = true;          
          FWARNING (( "Image has different DT while composing\n" ));
          dt = Image::OSG_INVALID_IMAGEDATATYPE;
        }
        if (imageVec[i]->getWidth() != w) {
          needCopy = true;          
          FWARNING (( "Image has different width while composing\n" ));
          w = osgMax ( w, imageVec[i]->getWidth());
        }
        if (imageVec[i]->getHeight() != h) {
          needCopy = true;          
          FWARNING (( "Image has different height while composing\n" ));
          h = osgMax ( h, imageVec[i]->getHeight());
        }
      }      
    }

    if (pf == Image::OSG_INVALID_PF) {
      if (needColor)
        if (needAlpha)
          pf = OSG::Image::OSG_RGBA_PF;
        else
          pf = OSG::Image::OSG_RGB_PF;
      else
        if (needAlpha)
          pf = OSG::Image::OSG_LA_PF;
        else
          pf = OSG::Image::OSG_L_PF;
    }

    if (dt == Image::OSG_INVALID_IMAGEDATATYPE)
      dt = Image::OSG_UINT8_IMAGEDATA;

    depth = frameCount = sideCount = 1;
    switch (sliceDataType) {
    case FRAME_SDT:
      frameCount = n;
      break;
    case SIDE_SDT:
      sideCount = n;
    case INVALID_SDT:
    case DEPTH_SDT:
    default:
      depth = n;
      break;
    }
      
    image->set( pf, w, h, depth, 1, frameCount, 0.0, 
                0, dt, true, sideCount );

    destData = image->getData();
    dataSize = image->getSize() / n;

    if (needCopy) {
      FLOG (("Image data/type/size missmatch while composing\n"));
    }

    for (i = 0; i < n; i++) {
      if (needCopy) {
        copy->set(imageVec[i]);
        if ( Image::PixelFormat(copy->getPixelFormat()) != pf )
          copy->reformat(pf);
        if ( Image::Type(copy->getDataType()) != dt )
          copy->convertDataTypeTo(dt);
        if ( (w != copy->getWidth()) || (h != copy->getHeight()))
          copy->scale(w,h,copy->getDepth());
        srcData = copy->getData();
      }
      else 
        srcData = imageVec[i]->getData();
      
      memcpy ( destData, srcData, dataSize );
      destData += dataSize;
    }
  }

  subRefCP(copy);

  imageVec[0]->dump();
  image->dump();

  return true;
}

//---------------------------------------------------------------------------//
/*! convert bumpmap to normalmap */

OSG_SYSTEMLIB_DLLMAPPING
bool OSG::createNormalMapFromBump ( ImagePtr image,
                                    ImagePtr dst,
                                    Vec3f    normalMapScale)
{
    if (image == NullFC || image->getDepth() > 1 ||
        image->getPixelFormat() != Image::OSG_L_PF)
    {
        FFATAL(("No valid Normalmap given!\n"));
        return false;
    }

    bool cpImg = false;

    if (dst == NullFC)
    {
        dst = Image::create();
        cpImg = true;
    }
    
    Int32 w = image->getWidth();
    Int32 h = image->getHeight();
    
    unsigned char *srcData = image->getData();

    beginEditCP(dst);
    
    dst->set(Image::OSG_RGB_PF, w, h);

    unsigned char *dstData = dst->getData();

    Vec3f scale(normalMapScale);
    
    if (scale[0] == 0.0f || scale[1] == 0.0f || scale[2] == 0.0f)
    {
        Real32 a = Real32(w) / Real32(h);
        
        if(a < 1.0f)
        {
            scale[0] = 1.0f;
            scale[1] = 1.0f / a;
        }
        else
        {
            scale[0] = a;
            scale[1] = 1.0f;
        }
        scale[2] = 1.0f;
    }

    Int32 i, j;

    for (i=1; i<w-1; i++)
    {
        for (j=1; j<h-1; j++)
        {
            Vec3f dfdi(2.0f, 0.0f, (Real32)(srcData[(i+1) +     j*w] - srcData[(i-1) +     j*w]) / 255.0f);
            Vec3f dfdj(0.0f, 2.0f, (Real32)(srcData[    i + (j+1)*w] - srcData[    i + (j-1)*w]) / 255.0f);
            Vec3f n = dfdi.cross(dfdj);
            
            n[0] *= scale[0];
            n[1] *= scale[1];
            n[2] *= scale[2];
            n.normalize();

            dstData[(j*w+i)*3+0] = (unsigned char)((n[0]+1)*127.5);
            dstData[(j*w+i)*3+1] = (unsigned char)((n[1]+1)*127.5);
            dstData[(j*w+i)*3+2] = (unsigned char)((n[2]+1)*127.5);
        }
    }

    // handle image border
    for (i=0; i<w; i++)
    {
        dstData[i*3+0] = dstData[(w+i)*3+0];
        dstData[i*3+1] = dstData[(w+i)*3+1];
        dstData[i*3+2] = dstData[(w+i)*3+2];
        
        dstData[((h-1)*w+i)*3+0] = dstData[((h-2)*w+1)*3+0];
        dstData[((h-1)*w+i)*3+1] = dstData[((h-2)*w+1)*3+1];
        dstData[((h-1)*w+i)*3+2] = dstData[((h-2)*w+1)*3+2];
    }
    
    for (j=0; j<h; j++)
    {
        dstData[(j*w)*3+0] = dstData[(j*w+1)*3+0];
        dstData[(j*w)*3+1] = dstData[(j*w+1)*3+1];
        dstData[(j*w)*3+2] = dstData[(j*w+1)*3+2];
        
        dstData[(j*w+(w-1))*3+0] = dstData[(j*w+(w-2))*3+0];
        dstData[(j*w+(w-1))*3+1] = dstData[(j*w+(w-2))*3+1];
        dstData[(j*w+(w-1))*3+2] = dstData[(j*w+(w-2))*3+2];
    }

    endEditCP(dst);

    if (cpImg)
    {
        beginEditCP(image);
            image->set(dst);
        endEditCP(image);
    }

    //dst->dump();
    
    return true;
}


//---------------------------------------------------------------------------//
/*!  */

OSG_SYSTEMLIB_DLLMAPPING
void OSG::createNormalVolume ( ImagePtr inImage,
                               ImagePtr outImage,
                               AlphaValue alphaValue )
{
  UInt8 *data = 0, *ds;
  Int32 w, h, d, x, y, z, ld, hd, md, xs, ys, zs, ps, ls, ss, os;
  Real32 g;
  const Real32 gMax = 441.67295593, gF = 255.0/gMax;
  Image::PixelFormat pf;
  ImagePtr copy;

  if ( (inImage->getPixelFormat() != Image::OSG_L_PF) ||
       (inImage->getDataType()    != Image::OSG_UINT8_IMAGEDATA) ) {

    copy = Image::create();
    FLOG (("Create copy to reformat/convert Image\n"));

    if (inImage->getPixelFormat() != Image::OSG_L_PF) 
      inImage->reformat(Image::OSG_L_PF,copy);      
    else 
      copy->set(inImage);    
    inImage = copy;
    
    if (inImage->getDataType() != Image::OSG_UINT8_IMAGEDATA) 
      inImage->convertDataTypeTo(Image::OSG_UINT8_IMAGEDATA);
  }

  pf   = (alphaValue == NONE_AVT) ? Image::OSG_RGB_PF : Image::OSG_RGBA_PF;
  w    = inImage->getWidth();
  h    = inImage->getHeight();
  d    = inImage->getDepth();
  data = inImage->getData();
  ps   = inImage->getBpp();
  ls   = ps * w;
  ss   = ls * h;
  os   = 0;

  beginEditCP(outImage);

  outImage->set( pf, w, h, d );
                      
  ds = outImage->getData();

  for (z = 0; z < d; z++) {
    for (y = 0; y < h; y++) {
      for (x = 0; x < w; x++) {
        md = data[(x*ps) + (y*ls) + (z*ss) + os];

        ld = (x > 0)     ? data[((x-1)*ps) + (y*ls) + (z*ss) + os] : 0;
        hd = (x < (w-1)) ? data[((x+1)*ps) + (y*ls) + (z*ss) + os] : 0;
        xs = (ld - hd);

        ld = (y > 0)     ? data[(x*ps) + ((y-1)*ls) + (z*ss) + os] : 0;
        hd = (y < (h-1)) ? data[(x*ps) + ((y+1)*ls) + (z*ss) + os] : 0;
        ys = (ld - hd);

        ld = (z > 0)     ? data[(x*ps) + (y*ls) + ((z-1)*ss) + os] : 0;
        hd = (z < (d-1)) ? data[(x*ps) + (y*ls) + ((z+1)*ss) + os] : 0;
        zs = (ld - hd);

        *ds++ = xs / 2 + 127;
        *ds++ = ys / 2 + 127;
        *ds++ = zs / 2 + 127;

        switch (alphaValue) {
        case NONE_AVT:
          break;
        case SOURCE_AVT:
          *ds++ = md;
          break;
        case GRADIENT_AVT:
          *ds++ = osgMax ( int(osgsqrt ( xs * xs + ys * ys + zs * zs ) * gF),
                           255 );        
          break;
        }

      }
    }
  }

  endEditCP(outImage);

  if (copy != osg::NullFC)
    subRefCP(copy);

  return;
}


//---------------------------------------------------------------------------//
/*! create pre-integrated lookup table 
    code based on the "Truly Volumetric Effects" (Martin Kraus)
    example in the ShaderX book (www.shaderx.com)
*/

OSG_SYSTEMLIB_DLLMAPPING
bool OSG::create2DPreIntegrationLUT ( ImagePtr dst,
                                      ImagePtr src,
                                      Real32   thickness)
{
    if (src == NullFC || dst == NullFC ||
        src->getHeight() > 1 || src->getDepth() > 1 ||
        src->getPixelFormat() != Image::OSG_RGBA_PF)
    {
        FFATAL(("No appropriate image given!\n"));
        return false;
    }

    unsigned char *dataSrc = src->getData();
    UInt32 width = src->getWidth();

    beginEditCP( dst );
    {
        dst->set(Image::OSG_RGBA_PF, width, width);

        unsigned char *dataDst = dst->getData();

        for (Int32 x = 0; x < (Int32)width; x++)
        {
            for (Int32 y = 0; y < (Int32)width; y++)
            {
                Int32 n = 10 + 2 * abs(x-y);
                Real64 step = thickness / n;
                
                Real64 dr = 0.0,
                       dg = 0.0,
                       db = 0.0,
                       dtau = 0.0;
                
                for (Int32 i = 0; i < n; i++)
                { 
                    Real64 w = x + (y-x) * (Real64)i/n;
                    
                    if ((Int32)(w + 1) >= (Int32)width)
                        w = (Real64)(width - 1) - 0.5/n;

                    Int32 pos = ((Int32)w) * 4;
                        
                    Real64 e = exp(-dtau), scale = step * (1.0 / 255.0),
                           f = w - floor(w), invF = 1 - f;
                        
                    Real64 tau =   scale * (dataSrc[pos + 3] * f + dataSrc[pos+4 + 3] * invF);
                    Real64 r = e * scale * (dataSrc[pos + 0] * f + dataSrc[pos+4 + 0] * invF);
                    Real64 g = e * scale * (dataSrc[pos + 1] * f + dataSrc[pos+4 + 1] * invF);
                    Real64 b = e * scale * (dataSrc[pos + 2] * f + dataSrc[pos+4 + 2] * invF);

                    dr += r; 
                    dg += g; 
                    db += b; 
                    dtau += tau;
                }
                
                dataDst[(x*width+y)*4+0] = (unsigned char)((dr > 1.0 ? 1.0 : dr)*255);
                dataDst[(x*width+y)*4+1] = (unsigned char)((dg > 1.0 ? 1.0 : dg)*255);
                dataDst[(x*width+y)*4+2] = (unsigned char)((db > 1.0 ? 1.0 : db)*255);
                dataDst[(x*width+y)*4+3] = (unsigned char)((1.0 - exp(-dtau))*255);
            }
        }
    }
    endEditCP( dst );

    //dst->dump();
    
    return true;
}


//---------------------------------------------------------------------------//
/*! split RGBA images into RGB and A */

OSG_SYSTEMLIB_DLLMAPPING
bool OSG::splitRGBA(ImagePtr rgba,
                    ImagePtr rgb,
                    ImagePtr alpha)
{
    if (rgba == NullFC || rgba->getDepth() > 1 ||
        rgba->getPixelFormat() != Image::OSG_RGBA_PF)
    {
        FFATAL(("No appropriate image given!\n"));
        return false;
    }

    if (rgb == NullFC)
        rgb = Image::create();
    if (alpha == NullFC)
        alpha = Image::create();

    Int32 w = rgba->getWidth();
    Int32 h = rgba->getHeight();

    beginEditCP( rgb );
    beginEditCP( alpha );
    {
        rgb->set(Image::OSG_RGB_PF, w, h);
        alpha->set(Image::OSG_L_PF, w, h);
        
        unsigned char *data = rgb->getData();
        unsigned char *dataRgba = rgba->getData();
        unsigned char *dataAlpha = alpha->getData();
        
        for (Int32 i=0; i<(w * h); i++)
        {    
            data[0] = dataRgba[0];
            data[1] = dataRgba[1];
            data[2] = dataRgba[2];
            dataAlpha[0] = dataRgba[3];

            data += 3;
            dataRgba += 4;
            dataAlpha++;
        }
    }
    endEditCP( alpha );
    endEditCP( rgb );

    //rgb->dump();
    //alpha->dump();

    return true;
}

//---------------------------------------------------------------------------//
/*! merge RGB and A images into RGBA */

OSG_SYSTEMLIB_DLLMAPPING
bool OSG::mergeRGBA(ImagePtr rgb,
                    ImagePtr alpha,
                    ImagePtr rgba)
{
    if (rgb == NullFC || alpha == NullFC ||
        rgb->getDepth() > 1 || alpha->getDepth() > 1 || 
        rgb->getPixelFormat() != Image::OSG_RGB_PF ||
        alpha->getPixelFormat() != Image::OSG_L_PF)
    {
        FFATAL(("No appropriate images given!\n"));
        return false;
    }

    Int32 w = rgb->getWidth();
    Int32 h = rgb->getHeight();

    if (w != alpha->getWidth() || h != alpha->getHeight())
    {
        FFATAL(("Colour and Alpha Images must be of same size!\n"));
        return false;
    }

    if (rgba == NullFC)
        rgba = Image::create();
    
    beginEditCP( rgba );
    {
        rgba->set(Image::OSG_RGBA_PF, w, h);
        
        unsigned char *data = rgba->getData();
        unsigned char *dataRgb = rgb->getData();
        unsigned char *dataAlpha = alpha->getData();
        
        for (Int32 i=0; i<(w * h); i++)
        {
            data[0] = dataRgb[0];
            data[1] = dataRgb[1];
            data[2] = dataRgb[2];
            data[3] = *dataAlpha;
            data += 4;
            dataRgb += 3;
            dataAlpha++;
        }
    }    
    endEditCP( rgba );
 
    //rgba->dump();

    return true;
}

//---------------------------------------------------------------------------//
/*! create phong texture */

OSG_SYSTEMLIB_DLLMAPPING
bool OSG::createPhongTexture(ImagePtr image,
                             UInt32   size,
                             Real32   specular_exponent,
                             Real32   ka,
                             Real32   kd,
                             Real32   ks)
{
    if (image == NullFC)
        image = Image::create();
    
    beginEditCP( image );
    {
        image->set(Image::OSG_L_PF, size, size);
        unsigned char *textureMap = image->getData();
        
        UInt32 i, j, index = 0;
        Real32 x = 0, y = 0;
        
        Real32 specular_factor, diffuse_factor;
        Real32 textureRadius = 0.95f;
        Real32 textureStep = (2.0 * textureRadius) / Real32(size-1);
    
        y = - textureRadius;
        for (j=0; j<size; j++)
        {
            x = -textureRadius;
            for (i=0; i<size; i++)
            {
                diffuse_factor  = sqrt(1.0 - x * x);
                specular_factor = pow( diffuse_factor * sqrt (1.0f - y * y) - x * y,
                                       specular_exponent );               
                textureMap[index++] = (unsigned char)((ka + kd * diffuse_factor + ks * specular_factor) * 255);
                x += textureStep;
            }
            y += textureStep;
        }
    }
    endEditCP( image );

    //image->dump();

    return true;
}


//---------------------------------------------------------------------------//
/*! create normalization cube map */

OSG_SYSTEMLIB_DLLMAPPING
bool OSG::createNormalizationCubeMap(std::vector<ImagePtr> imageVec,
                                     UInt32 size)
{
    int i, j;
    
    if (imageVec.size() < 6)
    {
        FFATAL(("Only %d images given - need six\n", imageVec.size()));
        return false;
    }

    for (i=0; i<6; i++)
    {
        if (imageVec[i] == NullFC)
        {
            FFATAL(("Image[%d] is Null\n", i));
            return false;
        }
    }
    
    unsigned char *data = NULL;
    Vec3f n;
    
    size = osgnextpower2(size);
    
    float size2 = size / 2.0f;
    float offset = 0.5f;

    ImagePtr imagePosX = imageVec[0];
    
    // pos x  
    beginEditCP( imagePosX );
        imagePosX->set(Image::OSG_RGB_PF, size, size);
        data = imagePosX->getData();
                        
        for (j=0; j<size; j++) {        
            for (i=0; i<size; i++) {
                
                n[0] =  size2;  
                n[1] = -((float)j + offset - size2);
                n[2] = -((float)i + offset - size2);
                n.normalize();
    
                data[0] = (UInt8)(((n.x() + 1.f) / 2.f) * 255.f);
                data[1] = (UInt8)(((n.y() + 1.f) / 2.f) * 255.f);
                data[2] = (UInt8)(((n.z() + 1.f) / 2.f) * 255.f);
                data += 3;
            }
        }
    endEditCP( imagePosX );

    ImagePtr imageNegX = imageVec[1];
    
    // neg x
    beginEditCP( imageNegX );
        imageNegX->set(Image::OSG_RGB_PF, size, size);
        data = imageNegX->getData();
                        
        for (j=0; j<size; j++) {        
            for (i=0; i<size; i++) {
                    
                n[0] = -size2;
                n[1] = -((float)j + offset - size2);
                n[2] =  ((float)i + offset - size2);
                n.normalize();
    
                data[0]= (UInt8)(((n.x() + 1.f) / 2.f) * 255.f);
                data[1]= (UInt8)(((n.y() + 1.f) / 2.f) * 255.f);
                data[2]= (UInt8)(((n.z() + 1.f) / 2.f) * 255.f);
                data += 3;
            }
        }
    endEditCP( imageNegX );

    ImagePtr imagePosY = imageVec[2];
            
    // pos y
    beginEditCP( imagePosY );
        imagePosY->set(Image::OSG_RGB_PF, size, size);
        data = imagePosY->getData();
                
        for (j=0; j<size; j++) {        
            for (i=0; i<size; i++) {
                
                n[0] =  ((float)i + offset - size2);
                n[1] =  size2;
                n[2] =  ((float)j + offset - size2);
                n.normalize();
    
                data[0]= (UInt8)(((n.x() + 1.f) / 2.f) * 255.f);
                data[1]= (UInt8)(((n.y() + 1.f) / 2.f) * 255.f);
                data[2]= (UInt8)(((n.z() + 1.f) / 2.f) * 255.f);
                data += 3;
            }
        }
    endEditCP( imagePosY );

    ImagePtr imageNegY = imageVec[3];
    
    // neg y
    beginEditCP( imageNegY );
        imageNegY->set(Image::OSG_RGB_PF, size, size);
        data = imageNegY->getData();
            
        for (j=0; j<size; j++) {        
            for (i=0; i<size; i++) {
                
                n[0]=  ((float)i + offset - size2);
                n[1]= -size2;
                n[2]= -((float)j + offset - size2);
                n.normalize();
    
                data[0] = (UInt8)(((n.x() + 1.f) / 2.f) * 255.f);
                data[1] = (UInt8)(((n.y() + 1.f) / 2.f) * 255.f);
                data[2] = (UInt8)(((n.z() + 1.f) / 2.f) * 255.f);
                data += 3;
            }
        }
    endEditCP( imageNegY );

    ImagePtr imagePosZ = imageVec[4];
    
    // pos z    
    beginEditCP( imagePosZ );
        imagePosZ->set(Image::OSG_RGB_PF, size, size);
        data = imagePosZ->getData();
            
        for (j=0; j<size; j++) {        
            for (i=0; i<size; i++) {
                
                n[0] =  ((float)i + offset - size2);
                n[1] = -((float)j + offset - size2);
                n[2] =  size2;
                n.normalize();
    
                data[0] = (UInt8)(((n.x() + 1.f) / 2.f) * 255.f);
                data[1] = (UInt8)(((n.y() + 1.f) / 2.f) * 255.f);
                data[2] = (UInt8)(((n.z() + 1.f) / 2.f) * 255.f);
                data += 3;
            }
        }
    endEditCP( imagePosZ );

    ImagePtr imageNegZ = imageVec[5];
    
    //negz
    beginEditCP( imageNegZ );
        imageNegZ->set(Image::OSG_RGB_PF, size, size);
        data = imageNegZ->getData();
        
        for (j=0; j<size; j++) {        
            for (i=0; i<size; i++) {
            
                n[0] = -((float)i + offset - size2);
                n[1] = -((float)j + offset - size2);
                n[2] = -size2;
                n.normalize();
    
                data[0] = (UInt8)(((n.x() + 1.f) / 2.f) * 255.f);
                data[1] = (UInt8)(((n.y() + 1.f) / 2.f) * 255.f);
                data[2] = (UInt8)(((n.z() + 1.f) / 2.f) * 255.f);
                data += 3;
            }
        }
    endEditCP( imageNegZ );

    return true;
}


//---------------------------------------------------------------------------//
/*! noice; first some helpers */

namespace
{

// globals
#define MAXB 0x100

Int32  p[MAXB + MAXB + 2];
Real32 g3[MAXB + MAXB + 2][3];
Real32 g2[MAXB + MAXB + 2][2];
Real32 g1[MAXB + MAXB + 2];
Int32  start = 1;
Int32  B = 0x100;
Int32  BM = 0xff;


void setNoiseFrequency(Int32 frequency)
{
    start = 1;
    B = frequency;
    BM = B-1;
}

Real32 lerp(Real32 t, Real32 a, Real32 b)
{
    return (1 - t) * a + t * b;
}

Real32 sCurve(Real32 t)
{
    return t * t * (3.0f - 2.0f * t);
}

Real32 at2(Real32 *q, Real32 rx, Real32 ry)
{
    return rx * q[0] + ry * q[1];
}

Real32 at3(Real32 *q, Real32 rx, Real32 ry, Real32 rz)
{
    return rx * q[0] + ry * q[1] + rz * q[2];
}

void setup(Real32 *vec, UInt8 i,
           Real32 &t,
           Int32 &b0, Int32 &b1,
           Real32 &r0, Real32 &r1)
{
    t  = vec[i] + 0x1000;
    b0 = ((Int32)t) & BM;
    b1 = (b0 + 1) & BM;
    r0 = t - (Int32)t;
    r1 = r0 - 1.0f;
}

void normalize2(Real32 v[2])
{
    Real32 s = sqrt(v[0] * v[0] + v[1] * v[1]);
    v[0] = v[0] / s;
    v[1] = v[1] / s;
}

void normalize3(Real32 v[3])
{
    Real32 s = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    v[0] = v[0] / s;
    v[1] = v[1] / s;
    v[2] = v[2] / s;
}

void init(void)
{
    Int32 i, j, k;

    srand(30757);
    for (i = 0 ; i < B ; i++)
    {
        p[i] = i;
        g1[i] = (Real32)((rand() % (B + B)) - B) / B;

        for (j = 0 ; j < 2 ; j++)
            g2[i][j] = (Real32)((rand() % (B + B)) - B) / B;
        normalize2(g2[i]);

        for (j = 0 ; j < 3 ; j++)
            g3[i][j] = (Real32)((rand() % (B + B)) - B) / B;
        normalize3(g3[i]);
    }

    while (--i)
    {
        k = p[i];
        p[i] = p[j = rand() % B];
        p[j] = k;
    }

    for (i = 0 ; i < B + 2 ; i++)
    {
        p[B + i] = p[i];
        g1[B + i] = g1[i];
        for (j = 0 ; j < 2 ; j++)
            g2[B + i][j] = g2[i][j];
        for (j = 0 ; j < 3 ; j++)
            g3[B + i][j] = g3[i][j];
    }
}
    
Real32 noise1(Real32 vec[1])
{
    Int32 bx0, bx1;
    Real32 rx0, rx1, sx, t, u, v;

    if (start)
    {
        start = 0;
        init();
    }

    setup(vec, 0, t, bx0, bx1, rx0, rx1);

    sx = sCurve(rx0);

    u = rx0 * g1[ p[ bx0 ] ];
    v = rx1 * g1[ p[ bx1 ] ];

    return lerp(sx, u, v);
}

Real32 noise2(Real32 vec[2])
{
    Int32 bx0, bx1, by0, by1, b00, b10, b01, b11;
    Real32 rx0, rx1, ry0, ry1, *q, sx, sy, a, b, t, u, v;
    Int32 i, j;

    if (start)
    {
        start = 0;
        init();
    }

    setup(vec, 0, t, bx0, bx1, rx0, rx1);
    setup(vec, 1, t, by0, by1, ry0, ry1);

    i = p[ bx0 ];
    j = p[ bx1 ];

    b00 = p[ i + by0 ];
    b10 = p[ j + by0 ];
    b01 = p[ i + by1 ];
    b11 = p[ j + by1 ];

    sx = sCurve(rx0);
    sy = sCurve(ry0);

    q = g2[ b00 ] ; u = at2(q, rx0,ry0);
    q = g2[ b10 ] ; v = at2(q, rx1,ry0);
    a = lerp(sx, u, v);

    q = g2[ b01 ] ; u = at2(q, rx0,ry1);
    q = g2[ b11 ] ; v = at2(q, rx1,ry1);
    b = lerp(sx, u, v);

    return lerp(sy, a, b);
}

Real32 noise3(Real32 vec[3])
{
    Int32 bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11;
    Real32 rx0, rx1, ry0, ry1, rz0, rz1, *q, sy, sz, a, b, c, d, t, u, v;
    Int32 i, j;

    if (start)
    {
        start = 0;
        init();
    }

    setup(vec, 0, t, bx0, bx1, rx0, rx1);
    setup(vec, 1, t, by0, by1, ry0, ry1);
    setup(vec, 2, t, bz0, bz1, rz0, rz1);

    i = p[ bx0 ];
    j = p[ bx1 ];

    b00 = p[ i + by0 ];
    b10 = p[ j + by0 ];
    b01 = p[ i + by1 ];
    b11 = p[ j + by1 ];

    t  = sCurve(rx0);
    sy = sCurve(ry0);
    sz = sCurve(rz0);

    q = g3[ b00 + bz0 ] ; u = at3(q, rx0,ry0,rz0);
    q = g3[ b10 + bz0 ] ; v = at3(q, rx1,ry0,rz0);
    a = lerp(t, u, v);

    q = g3[ b01 + bz0 ] ; u = at3(q, rx0,ry1,rz0);
    q = g3[ b11 + bz0 ] ; v = at3(q, rx1,ry1,rz0);
    b = lerp(t, u, v);

    c = lerp(sy, a, b);

    q = g3[ b00 + bz1 ] ; u = at3(q, rx0,ry0,rz1);
    q = g3[ b10 + bz1 ] ; v = at3(q, rx1,ry0,rz1);
    a = lerp(t, u, v);

    q = g3[ b01 + bz1 ] ; u = at3(q, rx0,ry1,rz1);
    q = g3[ b11 + bz1 ] ; v = at3(q, rx1,ry1,rz1);
    b = lerp(t, u, v);

    d = lerp(sy, a, b);

    return lerp(sz, c, d);
}

Real32 noise(Real32 vec[], Int32 len)
{
    // noise functions over 1, 2, and 3 dimensions 
    switch (len)
    {
      case 1: return noise1(vec);
      case 2: return noise2(vec);
      case 3: return noise3(vec);
      case 0:
      default: return 0.0f;
    }
}

};


/*! create a noise texture */

OSG_SYSTEMLIB_DLLMAPPING
bool OSG::createNoise(ImagePtr image,
                      Image::PixelFormat useNumOctaves,
                      UInt16 size,
                      UInt8 dim,
                      bool addValues)
{
  Int32 f, i, j, k, w, h, mult = 1, numOctaves = 4, frequency = 4;
  Real32 ni[3], amp = 0.5, inci, incj, inck;
  unsigned char  *data, *ptr = NULL;
  bool ok = true;

  if (image == NullFC)
  {
    FFATAL (("No output image given\n"));
    return false;
  }

  switch (useNumOctaves)
  {
    case Image::OSG_L_PF: numOctaves = 1; break;
    case Image::OSG_LA_PF: numOctaves = 2; break;
    case Image::OSG_RGB_PF: numOctaves = 3; break;
    case Image::OSG_RGBA_PF: numOctaves = 4; break;
    default: FWARNING(("Use [L|LA|RGB|RGBA] for 1..4 octaves\n")); break;
  }
  
  switch (dim)
  {
    case 1:
        ok = image->set(useNumOctaves, size);
        w = h = 1;
        break;
    case 2:
        ok = image->set(useNumOctaves, size, size);
        w = size; h = 1;
        break;
    case 3:
        ok = image->set(useNumOctaves, size, size, size);
        w = h = size;
        break;
    default:
        dim = 2; ok = image->set(useNumOctaves, size, size); w = size; h = 1;
        FWARNING(("Use [1|2|3] for image dimension (default 2)\n"));
        break;
  }

  if ( ! (ok && (data = image->getData())) )
  { 
      FFATAL(("Could not create image\n"));
      return false;
  }
  
  if (addValues && numOctaves == 1)
    mult = 4;
  
  for (f=0; f<numOctaves*mult; ++f, frequency*=2, amp*=0.5)
  {
    ptr = data;
    
    setNoiseFrequency(frequency);
    ni[0] = ni[1] = ni[2] = 0;
    inci = 1.0 / (size / (Real32)frequency);
    incj = 1.0 / (size / (Real32)frequency);
    inck = 1.0 / (size / (Real32)frequency);
    
    for (i=0; i<size; ++i, ni[0]+=inci)
    {
        for (j=0; j<w; ++j, ni[1]+=incj)
        {
            for (k=0; k<h; ++k, ni[2]+=inck, ptr+=numOctaves)
            {
                // calculate numOctaves of noise and scale to range [0;1]
                if ( !(addValues && numOctaves == 1) )
                    *(ptr+f) = (unsigned char)(((noise(ni, dim) + 1) * amp) * 128.0);
                else 
                    (*ptr)  += (unsigned char)(((noise(ni, dim) + 1) * amp) * 128.0);
            }
        }
    }
    FNOTICE(("Generated %dD noise: octave %d/%d...\n", dim, f+1, numOctaves));
  }

  return true;
}

