/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     * 
 *                                                                           * 
 *                                                                           * 
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                * 
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

#include <OSGConfig.h>
#include "OSGNFIOImage.h"
#include "OSGNFIOFactory.h"

#include <vector>

#include <OSGLog.h>
#include <OSGImageFileHandler.h>
#include <OSGJPGImageFileType.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::NFIOImage
           reads and writes a image.
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

NFIOImage NFIOImage::_the;

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*----------------------------- constructors  -----------------------------*/

NFIOImage::NFIOImage(void) :
    NFIOBase("Image"),
    _imageTypeInitialized(false),
    _imageTypes()
{
    _version = 100;
}

/*------------------------------ destructor -------------------------------*/

NFIOImage::~NFIOImage(void)
{
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

FieldContainerPtr NFIOImage::readFC(const std::string &/*typeName*/)
{
    FDEBUG(("NFIOImage::readFC\n"));
    
    ImagePtr img = Image::create();
    
    UInt16 version;
    _in->getValue(version);
    
    std::string fieldName = readFCFields(img, "", "'cpixel'");
    
    // compressed pixel
    if(fieldName == "cpixel")
    {
        readCompressedPixel(img);
        _in->getValue(fieldName); // read end marker
    }
    
    if(img->getPixel().getSize() == 0)
    {
        // read texture
        beginEditCP(img);
            img->read(img->getName().c_str());
        endEditCP(img);
    }
    
    return img;
}

void NFIOImage::writeFC(const FieldContainerPtr &fc)
{
    FDEBUG(("NFIOImage::witeFC\n"));

    ImagePtr img = ImagePtr::dcast(fc);
    
    _out->putValue(_version);
    
    bool compressTextures = false;
    std::string exclude;
    if(!getOptions().inlineTextures() && !img->getName().empty())
    {
        // only write the name field.
        exclude = "'dimension' 'width' 'height' 'depth' 'bpp' 'mipMapCount' "
                  "'frameCount' 'frameDelay' 'pixelFormat' 'pixel' 'frameSize'"
                  "'dataType' 'componentSize' 'sideCount'";
    }
    else
    {
        if(getOptions().compressTextures())
        {
            std::string imageType = getOptions().texturesImageType();
            if(isImageTypeSupported(imageType))
            {
                if(img->getDataType() == Image::OSG_UINT8_IMAGEDATA &&
                   img->hasCompressedData() == false &&
                   img->getDepth() == 1 &&
                   img->getMipMapCount() == 1 &&
                   img->getFrameCount() == 1 &&
                   img->getSideCount() == 1)
                {
                    if(imageType == "jpeg" &&
                       (img->getBpp() == 1 || img->getBpp() == 3))
                    {
                        // jpeg supports only 1 and 3 byte per pixel images :-(
                        compressTextures = true;
                    }
                    else if(imageType == "png")
                    {
                        compressTextures = true;
                    }
                }
            }
            else
            {
                FWARNING(("NFIOImage::witeFC : Image type '%s' not supported!\n", imageType.c_str()));
            }
        }
    }

    if(compressTextures)
        exclude += " 'pixel'";

    writeFCFields(img, exclude, false);
    
    if(compressTextures)
        writeCompressedPixel(img);

    writeEndMarker();
}

void NFIOImage::readCompressedPixel(ImagePtr &img)
{
    std::string fieldType;
    _in->getValue(fieldType);
    
    UInt32 size;
    UInt32 noe;
    
    _in->getValue(size);
    _in->getValue(noe);
    
    std::vector<UInt8> buffer;
    buffer.reserve(noe);
    UInt8 p;
    for(UInt32 i=0;i<noe;++i)
    {
        _in->getValue(p);
        buffer.push_back(p);
    }
    
    beginEditCP(img);
    UInt64 msize = img->restore(&buffer[0], buffer.size());
    endEditCP(img);
}

void NFIOImage::writeCompressedPixel(const ImagePtr &img)
{
    _out->putValue(std::string("cpixel"));
    _out->putValue(std::string("MFUInt8"));

    std::string imageType = getOptions().texturesImageType();

    std::vector<UInt8> buffer;

    int factor = 1;
    // ok jpeg's are always encoded in RGB so we have to allocate
    // some more memory for one channel images.
    if(imageType == "jpeg" && img->getBpp() == 1)
        factor = 3;

    // we need to add some extra bytes for the png, jpeg, ... header
    buffer.resize(OSG::ImageFileHandler::the().getDefaultType()->maxBufferSize(img) * factor + 16384);
    JPGImageFileType::the().setQuality(getOptions().texturesCompressionQuality());
    UInt64 msize = img->store(imageType.c_str(), &buffer[0]);

    UInt32 noe = (UInt32) msize;
    UInt32 size = sizeof(UInt32) + sizeof(UInt8) * noe;

    _out->putValue(size);
    _out->putValue(noe);
    
    for(UInt32 i=0;i<noe;++i)
        _out->putValue(buffer[i]);
}

bool NFIOImage::isImageTypeSupported(const std::string &imageType)
{
    if(!_imageTypeInitialized)
    {
        std::list<const Char8*> sl;
        if(ImageFileHandler::the().getSuffixList(sl) > 0)
        {
            for(std::list<const Char8*>::iterator i=sl.begin();i!=sl.end();++i)
            {
                _imageTypes.insert(std::string(*i));
            }
        }
        _imageTypeInitialized = true;
    }
    return (_imageTypes.count(imageType) > 0);
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGNFIOImage.cpp,v 1.9 2006/11/07 16:09:10 mroth Exp $";
    static Char8 cvsid_hpp       [] = OSGNFIOIMAGE_HEADER_CVSID;
}
