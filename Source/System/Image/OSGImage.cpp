/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#define OSG_COMPILEIMAGE

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>
#include <OSGLog.h>
#include <OSGImageGenericAtt.h>
#include <OSGFieldContainerFields.h>
#include <OSGFileSystem.h>

#include "OSGImageFileHandler.h"
#include "OSGPathHandler.h"
#include "OSGSceneFileHandler.h"

#include "OSGImage.h"

OSG_USING_NAMESPACE

/*! \class osg::Image
1D/2D/3D Image with various pixel types data, can also optional hold mipMap and simple multi-frame data.
*/

/*------------------------------------------------------------------------*/
/*                              static member                             */

/*! Static dictionary to map pixelData values to the bytes per pixel (bpp) value.
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

/*----------------------------- class specific ----------------------------*/

void Image::initMethod (void)
{
}

/*! Inform parents, when image was changed
 */
void Image::changed(BitVector whichField, UInt32 origin)
{
    MFFieldContainerPtr::iterator parentsIt  = _mfParents.begin();
    MFFieldContainerPtr::iterator parentsEnd = _mfParents.end();

    while(parentsIt != parentsEnd)
    {
        (*parentsIt)->changed(TypeTraits<BitVector>::One << 
                                    parentsIt->getParentFieldPos(),
                                ChangedOrigin::Child);
        ++parentsIt;
    }

    Inherited::changed(whichField, origin);
}

/*----------------------------- output ------------------------------------*/

void Image::dump(UInt32    , 
                 const BitVector ) const
{
    const char  *pfStr = "UNDEF_PIXEL_FORMAT";

    std::cout << "pixel format " << getPixelFormat() << std::endl;

    switch(getPixelFormat())
    {
    case OSG_L_PF:
        pfStr = "LUMINANCE";
        break;
    case OSG_LA_PF:
        pfStr = "LUMINANCE_ALPHA";
        break;
#if defined(GL_BGR) || defined(GL_BGR_EXT)
    case OSG_BGR_PF:
        pfStr = "BGR";
        break;
#endif
#if defined(GL_BGRA) || defined(GL_BGRA_EXT)
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
           pfStr, getWidth(), 
           getHeight(), getDepth(), 
           getMipMapCount(), getFrameCount(), 
           getFrameDelay()
              ));
}

/*------------------------------ set object data --------------------------*/

/*! method to set the image data. Use the doCopy parameter to specify, whether
    the method should copy or link the pixel data.
*/
bool Image::set(UInt32 pF, 
                Int32 w, Int32 h, 
                Int32 d, Int32 mmS, Int32 fS,
                Time fD, const UChar8 *da)
{
    ImagePtr iPtr(this);

    beginEditCP(iPtr,
                PixelFormatFieldMask |
                WidthFieldMask |
                HeightFieldMask |
                DepthFieldMask |
                MipMapCountFieldMask |
                FrameCountFieldMask |
                FrameDelayFieldMask);

    setPixelFormat(pF);

    setWidth(w);
    setHeight(h);
    setDepth(d);

    setMipMapCount(mmS);

    setFrameCount(fS);
    setFrameDelay(fD);

    endEditCP(iPtr,
              PixelFormatFieldMask |
              WidthFieldMask |
              HeightFieldMask |
              DepthFieldMask |
              MipMapCountFieldMask |
              FrameCountFieldMask |
              FrameDelayFieldMask);

    return createData(da);
}

/*! method to set the image from another image object. 
    Use the doCopy parameter to specify, whether
    the method should copy or link the pixel data.
*/
bool Image::set(ImagePtr image)
{
    this->set(image->getPixelFormat(),
              image->getWidth(),
              image->getHeight(),
              image->getDepth(),
              image->getMipMapCount(),
              image->getFrameCount(),
              image->getFrameDelay(),
              image->getData());

#ifdef OSG_DEBUG
    FDEBUG(("Running image set(image) \n"));
    this->dump();
#endif
    return true;
}

/*! method to set only the image pixel data, all parameter (e. pixelFormat
    width,height and depth) stay the same
*/
bool Image::setData(const UChar8 *da)
{  
    if(da) 
    {
        createData(da);
    }
    else 
    {
        FWARNING(("Image::setData(Null) call\n"));
    }
  
    return (da ? true : false);
}

/*! method to update just a subregion of the image data
  all paramter (e. pixelFormat,width,height,depth) stay the same
*/
bool Image::setSubData ( Int32 offX, Int32 offY, Int32 offZ,
                         Int32 srcW, Int32 srcH, Int32 srcD,
                         const UInt8 *src )
{
    UChar8 *dest = getData();
    UInt64 lineSize;

    FDEBUG(( "Image::setSubData (%d %d %d) - (%d %d %d) - src %p\n",
             offX, offY, offZ, srcW, srcH, srcD, src ));

    if(!src || !dest) 
    {
        FFATAL(("Invalid data pointer in Image::setSubData\n"));
        return false;
    }

    // determine the area to actually copy
    UInt32 xMin = osgMax(0,offX);
    UInt32 yMin = osgMax(0,offY);
    UInt32 zMin = osgMax(0,offZ);

    UInt32 xMax = osgMin(getWidth(),  offX + srcW);
    UInt32 yMax = osgMin(getHeight(), offY + srcH);
    UInt32 zMax = osgMin(getDepth(),  offZ + srcD);

    // fill the destination buffer with the subdata
    UInt32 destIdx, srcIdx = 0;

    for(UInt32 z = zMin; z < zMax; z++) 
    {
        for(UInt32 y = yMin; y < yMax; y++) 
        {
            lineSize = (xMax - xMin) * getBpp();
            destIdx = ( (z * getHeight() + y) * getWidth() + xMin) * getBpp();
            memcpy (&dest[destIdx], &src[srcIdx], lineSize);
            srcIdx += (srcW - (xMax - xMin)) * getBpp() + lineSize;
        }
        srcIdx += (srcH - (yMax - yMin)) * srcW * getBpp();
    }

    return true;
}

/*! The Image is not just a 2D container. The class can hold 3D (volume)
    and movie data. If we have 3D/singleFrame or 2D/multiFrame data without
    mipmaps we can flip between this two formats by just swapping the
    getFrameCount() and getDepth() values. 
*/
bool Image::flipDepthFrameData (void)
{
  bool retCode = false;
  Int32 value;

  if((getMipMapCount() == 1)&&((getFrameCount() == 1)||(getDepth() == 1))) 
  {
      value = getFrameCount();
      setFrameCount(getDepth());
      setDepth(value);
      retCode = true;
  }
  else 
  {
      FWARNING (("Cant flipDepthFrameData(); invalid data layout\n"));
  }

  return retCode;
}

/*! This method is used by the parser to fill the image with
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

            currentData = getData();
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
            // TODO; should we check the bounds, should be done by the parser 

            v = strtoul(value, 0, strchr(value, 'x') ? 16 : 10);

            for(j = getBpp(); j--;)
            {
                *currentData++ = UChar8( (v >> (8 * j)) & 255 );
            }

        }
    }

    return currentData ? true : false;
}

/*! It is a simple method to reformat the image pixelFormat (not the size).
    So you can for example convert a RGBA to RGB or RGB to Grey image.
*/
bool Image::reformat ( const Image::PixelFormat pixelFormat, 
                       ImagePtr destination )
{  
    UChar8 *data = 0;
    UInt32 srcI, destI, destSize = 0;
    UInt32 sum;
    ImagePtr dest = destination;

    if(destination == NullFC)
    {
        dest = Image::create();
        addRefCP(dest);
    }

    FINFO (( "Try to reformat image from pixelDepth %d to %d\n",
             getPixelFormat(), pixelFormat ));

    // TODO !!! code all the cases !!!

    if ( getSize() && pixelFormat && 
         (destination != NullFC || (pixelFormat != getPixelFormat()) ) )
    {
        dest->set(pixelFormat, getWidth(), getHeight(), getDepth() );
        data = dest->getData();
        destSize = dest->getSize();
        if (data)
        { 
            switch (getPixelFormat()) 
            {
                //-----------------------------------------------------
                case OSG_L_PF: 
                    switch (pixelFormat) {
                        case OSG_L_PF:
                            memcpy (getData(),data,destSize);
                            break;
                        case OSG_LA_PF:
                            for (srcI = destI = 0; destI < destSize; ) 
                            {
                                data[destI++] = getData()[srcI];
                                data[destI++] = getData()[srcI++];
                            }
                            break;
                        case OSG_RGB_PF:
                            for (srcI = destI = 0; destI < destSize; ) 
                            {
                                data[destI++] = getData()[srcI];
                                data[destI++] = getData()[srcI];
                                data[destI++] = getData()[srcI++];
                            }
                            break;
                        case OSG_RGBA_PF:
                            for (srcI = destI = 0; destI < destSize; ) 
                            {
                                data[destI++] = getData()[srcI];
                                data[destI++] = getData()[srcI];
                                data[destI++] = getData()[srcI];
                                data[destI++] = getData()[srcI++];
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
                                data[destI++] = getData()[srcI++];
                                srcI++;
                            }
                            break;
                        case OSG_LA_PF:
                            memcpy (getData(),data,destSize);
                            break;
                        case OSG_RGB_PF:
                            for (srcI = destI = 0; destI < destSize; ) 
                            {
                                data[destI++] = getData()[srcI];
                                data[destI++] = getData()[srcI];
                                data[destI++] = getData()[srcI++];
                                srcI++;
                            }
                            break;
                        case OSG_RGBA_PF:
                            for (srcI = destI = 0; destI < destSize; ) 
                            {
                                data[destI++] = getData()[srcI];
                                data[destI++] = getData()[srcI];
                                data[destI++] = getData()[srcI++];
                                data[destI++] = getData()[srcI++];
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
                                data[destI++] = static_cast<UInt32>
                                                (getData()[srcI++] * 0.263 +
                                                 getData()[srcI++] * 0.655 +
                                                 getData()[srcI++] * 0.082  );                                
                            }               
                            break;
                        case OSG_LA_PF:
                            for (srcI = destI = 0; destI < destSize; ) 
                            {
                                sum = static_cast<UInt32>
                                                (getData()[srcI++] * 0.263 +
                                                 getData()[srcI++] * 0.655 +
                                                 getData()[srcI++] * 0.082  );                                
                                data[destI++] = sum;
                                data[destI++] = sum;
                            }               
                            break;
                        case OSG_RGB_PF:
                            memcpy (getData(),data,destSize);
                            break;
                        case OSG_RGBA_PF:
                            for (srcI = destI = 0; destI < destSize; ) 
                            {
                                sum = 0;
                                sum += data[destI++] = getData()[srcI++];
                                sum += data[destI++] = getData()[srcI++];
                                sum += data[destI++] = getData()[srcI++];
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
                                data[destI++] = static_cast<UInt32>
                                                (getData()[srcI++] * 0.263 +
                                                 getData()[srcI++] * 0.655 +
                                                 getData()[srcI++] * 0.082  );                                
                                srcI++;
                            }               
                            break;
                        case OSG_LA_PF:
                            for (srcI = destI = 0; destI < destSize; ) 
                            {
                                data[destI++] = static_cast<UInt32>
                                                (getData()[srcI++] * 0.263 +
                                                 getData()[srcI++] * 0.655 +
                                                 getData()[srcI++] * 0.082  );                                
                                data[destI++] =  getData()[srcI++];
                            }               
                            break;
                        case OSG_RGB_PF:
                            for (srcI = destI = 0; destI < destSize; ) 
                            {
                                data[destI++] = getData()[srcI++];
                                data[destI++] = getData()[srcI++];
                                data[destI++] = getData()[srcI++];
                                srcI++;
                            }               
                            break;
                        case OSG_RGBA_PF:
                            memcpy (getData(),data,destSize);
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    FWARNING (( "Unvalid pixeldepth (%d) in reformat() !\n",
                                pixelFormat ));
            }
        }
        if (data) 
        {
            // rip the data from the local destImage if necessary
            if(destination == NullFC)
            {
                this->set(dest);
                subRefCP(dest);
            }
        }
    }
  
    return (data ? true : false);
}

/*! It just fills the whole image data with the given pixel value. It is 
    mainly used to initialize the image data.
*/
void Image::clear(UChar8 pixelValue)
{
    unsigned long   n = getSize();
    UChar8          *d = getData();

    if(n && d)
        while(n--)
            *d++ = pixelValue;
}

/*-------------------------------------------------------------------------*/
/*                             attachment handling                         */

/*! returns true if the image has any attachments
 */
bool Image::hasAttachment (void) const
{
    Image *img=const_cast<Image*>(this);
    ImageGenericAttPtr att=ImageGenericAttPtr::dcast(
        img->Inherited::findAttachment(
            ImageGenericAtt::getClassType().getGroupId()));
    if(att != NullFC && att->getType().getNumFieldDescs() > 1)
        return true;
    else
        return false;
}

/*! returns the number of attachments
 */
UInt32 Image::attachmentCount (void) const
{
    Image *img=const_cast<Image*>(this);
    ImageGenericAttPtr att=ImageGenericAttPtr::dcast(
        img->Inherited::findAttachment(
            ImageGenericAtt::getClassType().getGroupId()));
    if(att != NullFC)
        return att->getType().getNumFieldDescs() -1;
    else
        return 0;
}

/*! set a single string attachment for the given key/data pair
 */
void Image::setAttachmentField ( const std::string &key, 
                                 const std::string &data)
{ 
    ImageGenericAttPtr att=ImageGenericAttPtr::dcast(
        findAttachment(
            ImageGenericAtt::getClassType().getGroupId()));
    if(att==NullFC)
    {
        att=ImageGenericAtt::create();
        addAttachment(att);
    }
    Field *field=att->getField(key.c_str());
    if(field == NULL)
    {
        FieldDescription *pDesc;
        pDesc = new FieldDescription(
            SFString::getClassType(),
            key.c_str(),
            0, 0,
            true,
            (FieldIndexAccessMethod) &ImageGenericAtt::getDynamicField);
        UInt32 fieldId = att->addField(*pDesc);
        field=att->getField(fieldId);
    }
    SFString *strField=dynamic_cast<SFString*>(field);
    if(strField)
        strField->setValue(data);
}

/*! returns the string attachment for the given key or Null
 */
const std::string * Image::findAttachmentField( const std::string &key) const
{ 
    Image *img=const_cast<Image*>(this);
    ImageGenericAttPtr att=ImageGenericAttPtr::dcast(
        img->findAttachment(
            ImageGenericAtt::getClassType().getGroupId()));
    if(att!=NullFC)
    {
        Field *field=att->getField(key.c_str());
        if(field != NULL)
        {
            SFString *strField=dynamic_cast<SFString*>(field);
            if(strField != NULL)
                return &strField->getValue();
        }
    }
    return NULL;
}

/*! Method to scale the image. It just does a very simple but fast
    'nearest' scale. Should handle mipmap and frame data correct.
    The method can operate on the object or stores the result in 
    the optional destination Image.
*/
bool Image::scale(Int32 width, Int32 height, Int32 depth, 
                  ImagePtr destination)
{
    ImagePtr destImage;
    UInt32  sw, sh, sd, dw, dh, dd;
    Int32   frame, mipmap;
    UChar8  *src, *dest;
    Int32   oldWidth =getWidth();
    Int32   oldHeight=getHeight();
    Int32   oldDepth =getDepth();
    MFUInt8 srcPixel;

    if(destination != NullFC)
        destImage=destination;
    else
        destImage=ImagePtr(this);

    // get pixel
    srcPixel=getPixel();
    // set image data
    destImage->set((PixelFormat)getPixelFormat(),
                   width, height, depth, getMipMapCount(),
                   getFrameCount(), getFrameDelay(), 0);

    beginEditCP(destImage,PixelFieldMask);

    // copy every mipmap in every frame
    for(frame = 0; frame < getFrameCount(); frame++)
    {
        for(mipmap = 0; mipmap < getMipMapCount(); mipmap++)
        {
            // get the memory pointer
            src = (&srcPixel[0]) + 
                (frame * getFrameSize() * getBpp());
            if(mipmap)
                src+=calcMipmapSumSize(
                    mipmap - 1,
                    oldWidth, oldHeight, oldDepth) * getBpp();
            dest=destImage->getData(mipmap,frame);
            
            // calc the mipmap size
            sw = oldWidth  >> mipmap;
            sh = oldHeight >> mipmap;
            sd = oldDepth  >> mipmap;
            destImage->calcMipmapGeometry(mipmap, dw, dh, dd);

            // copy and scale the data
            scaleData(src, sw, sh, sd, dest, dw, dh, dd);
        }
    }

    endEditCP(destImage,PixelFieldMask);

    return true;
}

/*! Scale the image to the next power of 2 dimensions
    The method can operate on the object or stores the result in 
    the optional destination Image.
*/
bool Image::scaleNextPower2(ImagePtr destination)
{
  return scale ( osgnextpower2(getWidth()), 
                 osgnextpower2(getHeight()),
                 osgnextpower2(getDepth()),
                 destination );
}

/*! Crop the image to the given bounding box. 
    The method can operate on the object or stores the result in 
    the optional destination Image.
*/
bool Image::subImage ( Int32 offX, Int32 offY, Int32 offZ,
                       Int32 destW, Int32 destH, Int32 destD,
                       ImagePtr destination)
{
    ImagePtr destImage = destination;
    bool     retCode   = true;

    if(destination == NullFC)
    {
        destImage = Image::create();
        addRefCP(destImage);
    }
    
    destImage->set((PixelFormat)getPixelFormat(),
                   destW, destH, destD);
    
    UChar8  *src = getData();
    UChar8 *dest = destImage->getData();
    
    FDEBUG(("Image::subImage (%d %d %d) - (%d %d %d) - destPtr %p\n",
            offX, offY, offZ, destW, destH, destD, dest));
    
    // ensure destination data is zero
    memset(dest, 0, destImage->getSize());

    // determine the area to actually copy
    UInt32 xMin = offX;
    UInt32 yMin = offY;
    UInt32 zMin = offZ;

    UInt32 xMax = osgMin(getWidth(),  offX + destW);
    UInt32 yMax = osgMin(getHeight(), offY + destH);
    UInt32 zMax = osgMin(getDepth(),  offZ + destD);

    // fill the destination buffer with the subdata
    UInt32 destIdx = 0;
    
    for(UInt32 z = zMin; z < zMax; z++) 
    {
        for(UInt32 y = yMin; y < yMax; y++) 
        {
            for(UInt32 x = xMin; x < xMax; x++) 
            {
                for(UInt32 i = 0; i < getBpp(); i++) 
                {
                    dest[destIdx] = src[((z * getHeight() + y) * 
											getWidth() + x) * getBpp() + i];
                    destIdx++;
                }
            }
            destIdx += (destW - (xMax - xMin)) * getBpp();
        }
        destIdx += (destH - (yMax - yMin)) * destW * getBpp();
    }

    // rip the data from the local destImage if necessary
    if(destination == NullFC)
    {
        this->set(destImage);
        subRefCP(destImage);
    }

    return retCode;
}

/*! Crop a slice.
    The method can operate on the object or stores the result in 
    the optional destination Image.
*/
bool Image::slice ( Int32 offX, Int32 offY, Int32 offZ,
                    ImagePtr destination)
{
    ImagePtr destImage = destination;
    bool     retCode   = true;
    UInt32   counter   = 0;

    if(destination == NullFC)
    {
        destImage = Image::create();
        addRefCP(destImage);
    }
    
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
        retCode = subImage( 0, 0, offZ, getWidth(), getHeight(), 1, 
                            destImage );
    }

    if (offY >= 0) {
        // XZ slice
        destImage->set((PixelFormat)getPixelFormat(), 
                       getWidth(), getDepth(), 1);
    
        UChar8  *src  = getData();
        UChar8  *dest = destImage->getData();

        // ensure destination data is zero
        memset(dest, 0, destImage->getSize());
        
        for(UInt32 z = 0; z < getDepth(); z++) 
        { 
          for(UInt32 x = 0; x < getWidth(); x++) 
          { 
            for(UInt32 i = 0; i < getBpp(); i++) 
            { 
              dest[(z * getWidth() + x) * getBpp() + i] = src[((z * getHeight() + offY) * 
                                                       getWidth() + x) * 
                                                     getBpp() + i]; 
            }
          }
        } 
    } 
    
    if (offX >= 0) {
        // YZ slice
        destImage->set((PixelFormat)getPixelFormat(), getHeight(), getDepth(), 1);
      
        UChar8  *src  = getData();
        UChar8  *dest = destImage->getData();
        
        // ensure destination data is zero
        memset(dest, 0, destImage->getSize());
        
        for(UInt32 z = 0; z < getDepth(); z++) 
        { 
          for(UInt32 y = 0; y < getHeight(); y++) 
          { 
            for(UInt32 i = 0; i < getBpp(); i++) 
            { 
              dest[(z * getHeight() + y) * getBpp() + i] = src[((z * getHeight() + y) * 
                                                        getWidth() + offX) * 
                                                      getBpp() + i]; 
            } 
          } 
        }
    }

    // rip the data from the local destImage if necessary
    if(destination == NullFC)
    {
        this->set(destImage);
        subRefCP(destImage);
    }

    return retCode;
}

/*! Create mipmaps data, level defines the number of level
    The method can operate on the object or stores the result in 
    the optional destination Image.
*/
bool Image::createMipmap(Int32 level, ImagePtr destination)
{
    struct Offset
    {
      Int32   d;
      Int32   h;
      Int32   w;
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
        {   // 011
            { 0, 0, 0 }, { 0, 0, 1 }, { 0, 1, 0 }, { 0, 1, 1 }, 
            { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
        {   // 111
            { 0, 0, 0 }, { 1, 0, 0 }, { 0, 1, 0 }, { 1, 1, 0 }, 
            { 0, 0, 1 }, { 1, 0, 1 }, { 0, 1, 1 }, { 1, 1, 1 } }
    };
    Int32   offsetSize[] = { 0, 2, 2, 4, 2, 4, 4, 8 };
    ImagePtr destImage = destination;
    Int32   w = getWidth(), h = getHeight(), d = getDepth();
    Int32   wm, hm, dm, wi, hi, di;
    UChar8  *src, *dest;

    if(destImage == NullFC)
    {
        destImage = Image::create();
        addRefCP(destImage);
    }

    /* ,*pixel; */
    Int32   value, i, elem, dim, frame, size, mipmap;
    Int32   channel, lineSize, sliceSize;

    // calc the level count
    if(level < 0)
    {
        level = calcMipmapLevelCount() - 1;
    }

    // create destination image
    destImage->set(getPixelFormat(),
                   getWidth(), getHeight(), getDepth(),
                   level, getFrameCount(),
                   getFrameDelay(), 0);

    // copy the data;
    for(frame = 0; frame < getFrameCount(); frame++)
    {
        src = this->getData(0, frame);
        dest = destImage->getData(0, frame);
        size = getWidth() * getHeight() * getDepth() * getBpp();
        memcpy(dest,src, size);
        src = dest;
        dest = src + size;
        w = getWidth();
        h = getHeight();
        d = getDepth();
        for(mipmap = 1; mipmap < level; mipmap++)
        {
            lineSize = w * getBpp();
            sliceSize = w * h * getBpp();
            wm = (w == 1) ? w : (w >> 1);
            hm = (h == 1) ? h : (h >> 1);
            dm = (d == 1) ? d : (d >> 1);

            dim = (d > dm) * 1 + (h > hm) * 2 + (w > wm) * 4;
            elem = offsetSize[dim];

            for(di = 0; di < dm; di++)
            {
                for(hi = 0; hi < hm; hi++)
                {
                    for(wi = 0; wi < wm; wi++)
                    {
                        for(channel = 0; channel < getBpp(); channel++)
                        {
                            value = 0;
                            for(i = 0; i < elem; i++)
                            {
                                value += src[
                                    ((wi * 2) + offset[dim][i].w) * getBpp() +
                                    ((hi * 2) + offset[dim][i].h) * lineSize +
                                    ((di * 2) + offset[dim][i].d) * sliceSize +
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
    if(destination == NullFC)
    {
        this->set(destImage);
        subRefCP(destImage);
    }

    return true;
}

/*! Write the image to the a file. The mimetype will be set automatically
    from the fileName suffix. Returns true on success.
*/
bool Image::write(const Char8 *fileName)
{
    return ImageFileHandler::the().write(ImagePtr(this), fileName);
}

/*! Read the image data from a file. Returns true on success.
 */
bool Image::read(const Char8 *fileName)
{
    ImagePtr iPtr(this);
    bool ok = ImageFileHandler::the().read(iPtr, fileName);

    if(ok)
    {
        // converting the path to a absolute path.
        std::string abspath;
        if(fileName[0] != '/' && fileName[0] != '\\' && fileName[1] != ':')
        {
            std::string base = SceneFileHandler::the().getPathHandler()->getBaseFile();
            if(base[0] != '/' && base[0] != '\\' && base[1] != ':')
            {
                const char *cdir = Directory::getCurrent();
                abspath = cdir;
#ifdef WIN32
                abspath += '\\';
#else
                abspath += '/';
#endif
                delete [] cdir;
            }
            
            abspath += base;
            abspath += fileName;
        }
        else
        {
            abspath = fileName;
        }
        
        beginEditCP(iPtr, NameFieldMask);
            setName(abspath);
        endEditCP(iPtr, NameFieldMask);
    }
    return ok;
}

/*! Store the image to the given mem block as 'mimeType'. 
    mimeType can be 0, in which case the method will store the
    object as uncompressed mtd data.
    Returns the number of bytes used.
*/
UInt64 Image::store(Char8 *mimeType, UChar8 *mem, Int32 memSize)
{
    ImagePtr iPtr(this);
    return ImageFileHandler::the().store(iPtr,
                                         mimeType, mem, memSize);
}

/*! Restore the image from the given mem block. Returns the
    number of bytes used. 
*/
UInt64 Image::restore(const UChar8 *mem, Int32 memSize)
{
    ImagePtr iPtr(this);
    return ImageFileHandler::the().restore(iPtr, mem, memSize);;
}

/*-------------------------------------------------------------------------*/
/*                               Constructor / Destructor                  */

/*! Default Constructor. Creates a invalid Image of the size 0x0x0
 */
Image::Image(void) :
    Inherited()
{
    setPixelFormat(OSG_INVALID_PF);
    return;
}

/*! Copy Constructor. Creates a copy of the given image
 */
Image::Image(const Image &obj) :
    Inherited(obj)
{
}

/*! Destructor.
 */
Image::~Image(void)
{
}

/*! Method to check, whether the object data defines a alpha channel or not
 */
bool Image::hasAlphaChannel(void)
{
    return getPixelFormat() == OSG_RGBA_PF
#ifdef OSG_HAS_BGRA_PF
    || getPixelFormat() == OSG_BGRA_PF
#endif
    || getPixelFormat() == OSG_LA_PF;
}

/*! Method returns the right frame data for the given time.
 */
UInt8 *Image::getDataByTime(Time   time, UInt32) 
{
    UInt32 frameNum = calcFrameNum(time, true);
  
    return getData(0, frameNum);
}

/*! Method which returns the frame number for the given time
 */
UInt32 Image::calcFrameNum(Time time, bool OSG_CHECK_ARG(loop)) const
{
  UInt64 frameNum = ((getFrameDelay() > 0) && (getFrameCount() > 0)) ?
        (UInt64(time / getFrameDelay()) % getFrameCount()) : 0;
    
    return ((frameNum > 0) ? frameNum : 0);
}

/*! Internal used method to calculate the next mipmap geo for the given level
 */
void Image::calcMipmapGeometry   ( UInt32 mipmapNum,
                                   UInt32 &width, 
                                   UInt32 &height, 
                                   UInt32 &depth ) const
{
  width  = getWidth() >> mipmapNum;
  height = getHeight() >> mipmapNum;
  depth  = getDepth() >> mipmapNum;
}

#ifdef __sgi
#pragma set woff 1209
#endif

/*! Internal used method to calculate the number of mipmaps levels
 */
UInt32 Image::calcMipmapLevelCount ( void ) const
{
  UInt32  w = getWidth(), h = getHeight(), d = getDepth();
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

/*! Internal used method to calculate the size in bpp of a single mipmap level
 */
UInt32 Image::calcMipmapSize    ( UInt32 mipmapNum,
                                  UInt32 w, UInt32 h, UInt32 d) const
{
  w >>= mipmapNum;
  h >>= mipmapNum;
  d >>= mipmapNum;
  
  return (w?w:1) * (h?h:1) * (d?d:1);
}

/*-------------------------------------------------------------------------*/
/*                            Calculate Mipmap Size                        */

/*! Internal used method to calculate the size in bpp of a single mipmap
    level for the current image settings
*/
UInt32 Image::calcMipmapSize(UInt32 mipmapNum) const
{
    return calcMipmapSize(mipmapNum,getWidth(),getHeight(),getDepth());
}

/*! Internal used method to calculate the mem sum of all mipmap levels in bpp
 */
UInt32 Image::calcMipmapSumSize ( UInt32 mipmapNum,
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

/*! Internal used method to calculate the mem sum of all mipmap levels in bpp
    for the current Image paramter
*/
UInt32 Image::calcMipmapSumSize (UInt32 mipmapNum) const
{
    return calcMipmapSumSize(mipmapNum,getWidth(),getHeight(),getDepth());
}

/*-------------------------------------------------------------------------*/
/*                            Image data                                   */

/*! Internal method to set the data and update related properties.
 */
bool Image::createData(const UInt8 *data)
{
    Int32   i, mapSize = sizeof(_formatDic) / sizeof(UInt32[2]);
    UInt32 byteCount = 0;
    ImagePtr iPtr(this);

    beginEditCP(iPtr,
                BppFieldMask |
                DimensionFieldMask |
                FrameSizeFieldMask |
                PixelFieldMask);

    // set bbp
    for(i = 0; i < mapSize; i++)
    {
        if(_formatDic[i][0] == getPixelFormat())
            setBpp(_formatDic[i][1]);
    }

    // set dimension
    setDimension(0);
    if(getDepth() == 1)
    {
        if(getHeight() == 1)
        {
            setDimension(1);
        }
        else
        {
            setDimension(2);
        }
    }
    else
        setDimension(3);

    // set frameSize
    setFrameSize(calcMipmapSumSize(getMipMapCount() - 1));

    FINFO(("FrameSize: %d\n", getFrameSize()));

    // copy the data
    if((byteCount = getSize()))
    {
        if(getPixel().getSize() != byteCount)
            getPixel().resize(byteCount);
        if(data)
            memcpy(getData(), data, byteCount);
    }
    else
    {
        getPixel().clear();
    }

    endEditCP(iPtr,
              BppFieldMask |
              DimensionFieldMask |
              FrameSizeFieldMask |
              PixelFieldMask);

    return getData();
}

/*! Internal method to scale image data blocks
 */
bool Image::scaleData(UInt8 *srcData, Int32 srcW, Int32 srcH, Int32 srcD,
                      UInt8 *destData, Int32 destW, Int32 destH, Int32 destD)
{
    Real32  sx = Real32(srcW) / Real32(destW);
    Real32  sy = Real32(srcH) / Real32(destH);
    Real32  sz = Real32(srcD) / Real32(destD);
    Int32   srcSize = srcW * srcH * srcD;

    //  Int32 destDize = destW * destH * destD;
    Int32   x, y, z, p;
    UInt8  *slice, *line, *pixel;

    if(destW == srcW && destH == srcH && destD == srcD)
    {
        // same size, just copy
        memcpy(destData, srcData, srcSize);
    }
    else
    {       // different size, to 'nearest' copy
        for(z = 0; z < destD; z++)
        {
            slice = srcData + int(sz * z + 0.5) * getBpp() * srcW * srcH;
            for(y = 0; y < destH; y++)
            {
                line = slice + int(sy * y + 0.5) * getBpp() * srcW;
                for(x = 0; x < destW; x++)
                {
                    pixel = line + int(sx * x + 0.5) * getBpp();
                    p = getBpp();
                    while(p--)
                        *destData++ = *pixel++;
                }
            }
        }
    }

    return true;
}

/*! Assign operator. Does a copy of the given Image object.
 */
Image &Image::operator=(const Image &image)
{
    this->set((PixelFormat)image.getPixelFormat(), image.getWidth(), 
              image.getHeight(), image.getDepth(),
              image.getMipMapCount(), image.getFrameCount(), 
              image.getFrameDelay(),
              image.getData());

#ifdef OSG_DEBUG
    FDEBUG(("Running image assign operator\n"));
    this->dump();
#endif
    return *this;
}

/*! Less operator; compares the data sizes of the two images
*/
bool Image::operator<(const Image &image)
{
    return (getSize() < image.getSize()) ? true : false;
}

/*! Method to compare the object to another Image instance; 
    Checks first all parameter and afterwards the Image data;
*/
bool Image::operator==(const Image &image)
{
    unsigned long   i, s = getSize();

    if((getWidth() == image.getWidth()) &&
       (getHeight() == image.getHeight()) &&
       (getDepth() == image.getDepth()) &&
       (getMipMapCount() == image.getMipMapCount()) &&
       (getFrameCount() == image.getFrameCount()) &&
       (getFrameDelay() == image.getFrameDelay()) &&
       (getPixelFormat() == image.getPixelFormat()))
    {
        for(i = 0; i < s; ++i)
        {
            if(image.getData()[i] != getData()[i])
                return false;
        }
        return true;
    }
    return false;
}

/*! Method to compare the object to another Image instance; 
    Checks first all parameter and afterwards the Image data;
*/
bool Image::operator!=(const Image &image)
{
  return !(*this == image);
}



/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: $";
    static Char8 cvsid_hpp       [] = OSGIMAGEBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGIMAGEBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGIMAGEFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

