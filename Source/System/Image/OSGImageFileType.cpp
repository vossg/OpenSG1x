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
// System declarations
#include <OSGConfig.h>
#include <iostream>

// Application declarations
// to get ntons/ntohs
#ifdef WIN32
#include <winsock.h>
#else
#include <arpa/inet.h>
#endif

// Class declarations
#include "OSGImageFileType.h"
#include "OSGImageFileHandler.h"
#include "OSGImageGenericAtt.h"
#include "OSGLog.h"

OSG_USING_NAMESPACE


/*! \class osg::ImageFileType
    \ingroup GrpSystemImage
    
*/

//-------------------------------------------------------------------------
/*!
Helper method to convert the Head block from net to host format
*/
bool ImageFileType::Head::netToHost(void)
{
    pixelFormat    = ntohs(pixelFormat);
    width          = ntohs(width);
    height         = ntohs(height);
    depth          = ntohs(depth);
    mipmapCount    = ntohs(mipmapCount);
    frameCount     = ntohs(frameCount);
    frameDelay     = ntohs(frameDelay);
    _reserved1     = 0;
    _reserved2     = 0;
    _reserved3     = 0;
    _reserved4     = 0;
    attachmentSize = ntohs(attachmentSize);

    return true;
}


//-------------------------------------------------------------------------
/*!
Helper method to convert the Head block from host to net format
*/
bool ImageFileType::Head::hostToNet(void)
{
    pixelFormat    = htons(pixelFormat);
    width          = htons(width);
    height         = htons(height);
    depth          = htons(depth);
    mipmapCount    = htons(mipmapCount);
    frameCount     = htons(frameCount);
    frameDelay     = htons(frameDelay);
    _reserved1     = 0;
    _reserved2     = 0;
    _reserved3     = 0;
    _reserved4     = 0;
    attachmentSize = htons(attachmentSize);

    return true;
}

//-------------------------------------------------------------------------
/*!
Get method for the mime type
*/
const Char8 *ImageFileType::getMimeType(void) const
{
  return _mimeType.str();
}

//-------------------------------------------------------------------------
/*!
Get method for the suffix list container
*/
const std::list<IDString> &ImageFileType::getSuffixList(void) const
{
  return _suffixList; 
}

//-------------------------------------------------------------------------
/*!
Constructor which takes a suffix array and size to add the
ImageFileType to the Singleton ImageFileHandler
*/
ImageFileType::ImageFileType( const char *mimeType,
                              const Char8 *suffixArray[], 
                              UInt16 suffixByteCount)
{
    Int32 suffixCount = suffixByteCount / sizeof(const Char8 *);
    Int32 i = 0;
    std::list<IDString>::iterator sI;

    if (!mimeType) {
      FFATAL (("ImageFileType without valid mimeType\n"));
    }
    _mimeType.set(mimeType);

    _suffixList.resize(suffixCount);
    for(sI = _suffixList.begin(); sI != _suffixList.end(); sI++)
    {
        sI->set(suffixArray[i++]);
        SINFO << "add image suffix: " << *sI << endLog;
    }

    ImageFileHandler::addImageFileType(*this);
}

//-------------------------------------------------------------------------
/*!
Copy Constructor 
*/
ImageFileType::ImageFileType(const ImageFileType &obj) 
  : _suffixList(obj._suffixList)
{
    SWARNING << "In ImageFileType copy constructor" << std::endl;
}

//-------------------------------------------------------------------------
/*!
Destructor
*/
ImageFileType::~ImageFileType(void)
{
  return;
}

//-------------------------------------------------------------------------
/*!
Abstract restore method. Sould be overwriten by an concrete derived
class. Tries to restore the image data from the given memblock.
*/
UInt64 ImageFileType::restoreData(   ImagePtr  &, 
                                  const UChar8 *OSG_CHECK_ARG(buffer ),
                                        Int32   OSG_CHECK_ARG(memSize))
{
  FWARNING(("ImageXFileType::restoreData() not impl. for mimeType %s\n",
            getMimeType()));

  return 0;
}

//-------------------------------------------------------------------------
/*!
Abstract restore method. Sould be overwriten by an concrete derived
class. Tries to store the given image data to the given memblock
*/
UInt64 ImageFileType::storeData(const ImagePtr &, 
                                      UChar8   *OSG_CHECK_ARG(buffer ),
                                      Int32     OSG_CHECK_ARG(memSize))
{
  FWARNING(("ImageXFileType::storeData() not impl. for mimeType %s\n",
            getMimeType()));
  
  return 0;
}

//-------------------------------------------------------------------------
/*!
Tries to restore the Imagedata from the given memblock. The buffer must
include a ImageFileType::Head data block.
*/
UInt64 ImageFileType::restore( ImagePtr &image, 
                               const UChar8 *buffer, Int32 memSize)
{
    unsigned long   imageSize, headSize = sizeof(Head);
    unsigned long   size, i, attachmentSize;
    Head            *head = (Head *) const_cast<UChar8*>((buffer));
    const UChar8    *data = buffer ? (buffer + headSize) : 0;
    char            *attData, *attKey, *attValue;
    ImageFileType   *type;
    const char      *mimeType;


    if(head && data && head->netToHost() && (mimeType = head->mimeType))
    {
        if((type = ImageFileHandler::the().getFileType(mimeType, 0)))
        {
            image->set(Image::PixelFormat(head->pixelFormat), head->width,
                       head->height, head->depth, head->mipmapCount,
                       head->frameCount, float(head->frameDelay) / 1000.0, 0);
            imageSize = type->restoreData(image, data, memSize - headSize);
            attachmentSize = 0; // head->attachmentSize;

            /*
            if ((attachmentSize = head->attachmentSize))
            {
                attData = (char*)(buffer + headSize + imageSize);
                attKey = attData;
                attValue = 0;
                for (i = 0; i < (attachmentSize-1); i++) {
                    if (attData[i] == 0) 
                        if (attKey) {
                            attValue = &(attData[i+1]);
                            image->setAttachmentField (attKey,attValue);
                            attKey = attValue = 0;
                        }
                        else
                            attKey = &(attData[i+1]);
                }
                if (attKey || attValue) {
                    FFATAL (("Attachment restore error\n"));
                }
            }
            */

            size = headSize + imageSize + attachmentSize;
      
            FDEBUG (( "Restore image data: %lu (%lu/%lu/%lu)\n",
                      size, headSize, imageSize, attachmentSize ));

        }
        else
        {
            imageSize = 0;
            FWARNING(("Can not restore image data, invalid mimeType: %s\n",
                      mimeType ? mimeType : "Unknown"));
        }

      
    }

    return size;
}

//-------------------------------------------------------------------------
/*!
Tries to store the raster data to the given mem block.
Will include a ImageFileType::Head description and the data encoded
as 'mimeType'
*/
UInt64 ImageFileType::store(const ImagePtr &image, const char *mimeType,
                            UChar8 *buffer, Int32 memSize)
{
  ImageFileType   *type = ImageFileHandler::the().getFileType(mimeType);
  
  return type ? type->store(image, buffer, memSize) : 0;
}

//-------------------------------------------------------------------------
/*!
Tries to store the raster data to the given mem block.
Will include a ImageFileType::Head description for the derived
concreate mimeType.
*/
UInt64 ImageFileType::store(const ImagePtr &image,
                            UChar8 *buffer, Int32 memSize)
{
    Head            *head;
    unsigned long   dataSize = 0, headSize = sizeof(Head);
    unsigned long   attachmentSize;
    UChar8          *dest;
    const UChar8    *src = image->getData();
    std::map<std::string, std::string>::const_iterator aI;
    UInt32          l;
    Int32           i;
    std::string     value;

    attachmentSize = 0;

    // get attachment size
    /*
    ImageGenericAttPtr att=ImageGenericAttPtr::dcast(
        const_cast<Image*>(image.getCPtr())->findAttachment(
            ImageGenericAtt::getClassType().getGroupId()));
    if(att != NullFC)
    {
        for(i = 0; i < (att->getType().getNumFieldDescs()-1); ++i)
        {
            FieldDescription *fieldDesc=att->getType().getFieldDescription(i);
            Field *field=att->getField(i);
            if (fieldDesc && field) 
            {
                field->getValueByStr(value);
                attachmentSize += strlen( fieldDesc->getName().str() ) + 1;
                attachmentSize += value.length() + 1;
              
                std::cout << fieldDesc->getName().str() << std::endl; 
                std::cout << value << std::endl; 
            }
            else 
            {
                FFATAL (("Invalid Attachment in ImageFileType::store()\n"));
            }
        }
    }
    */

    if (buffer) 
    {
        head = (Head *)buffer;

        head->pixelFormat    = image->getPixelFormat();
        head->width          = image->getWidth();
        head->height         = image->getHeight();
        head->depth          = image->getDepth();
        head->mipmapCount    = image->getMipMapCount();
        head->frameCount     = image->getFrameCount();
        head->frameDelay     = short(image->getFrameDelay() * 1000.0);
        head->attachmentSize = attachmentSize;
        head->hostToNet();
      
        strcpy(head->mimeType, getMimeType());
      
        dest = (UChar8 *) (buffer + headSize);

        if (src) 
            dataSize = storeData(image, dest, memSize - headSize);

        dest = (UChar8 *) (buffer + headSize + dataSize);

        /*
        if(att != NullFC)
        {
            for(i = 0; i < (att->getType().getNumFieldDescs()-1); ++i)
            {
                FieldDescription *fieldDesc=att->getType().getFieldDescription(i);
                Field *field=att->getField(i);
                if (field && fieldDesc) 
                {
                    field->getValueByStr(value);

                    l = strlen( fieldDesc->getName().str() );
                    for (i = 0; i < l; i++)
                      *dest++ = fieldDesc->getName().str()[i];
                    *dest++ = 0;
                    l = value.length();
                    for (i = 0; i < l; i++)
                      *dest++ = value[i];
                    *dest++ = 0;
                }
                else
                {
                    FFATAL (("Invalid Attachment in ImageFileType::store()\n"));
                }
            }
        }
        */

        FDEBUG (( "Store image data: %lu (%lu/%lu/%lu)\n",
                  headSize + dataSize + attachmentSize, headSize, dataSize, 
                  attachmentSize ));
    }
    else {
        FFATAL (("Invalid buffer in ImageFileType::store()\n"));
    }
  
    return (headSize + dataSize + attachmentSize);

}

//-------------------------------------------------------------------------
/*!
Returns the max buffer size needed to store the Image (Head + mimeType
specific data block)
*/
UInt64 ImageFileType::maxBufferSize(const ImagePtr &image)
{
    UInt32 i;
    std::string value;
    unsigned long size, attachmentSize;
    unsigned long imageSize = image->getSize(), headSize = sizeof(Head);

    std::map<std::string, std::string>::const_iterator aI;

    attachmentSize = 0;

    // get attachment size
		/*
    ImageGenericAttPtr att=ImageGenericAttPtr::dcast(
        const_cast<Image*>(image.getCPtr())->findAttachment(
            ImageGenericAtt::getClassType().getGroupId()));
    if(att != NullFC)
    {
        for(i = 0; i < (att->getType().getNumFieldDescs()-1); ++i)
        {
            FieldDescription *fieldDesc=att->getType().getFieldDescription(i);
            Field *field=att->getField(i);
            if (field && fieldDesc) 
            {
                field->getValueByStr(value);
                attachmentSize += strlen( fieldDesc->getName().str() ) + 1;
                attachmentSize += value.length() + 1;
            }
            else 
            {
                FFATAL (("Invalid Attachment in ImageFileType::maxBufferSize()\n"));
            }
        }
    }
		*/

    size = headSize + imageSize + attachmentSize;
  
    FINFO (( "ImageFileType::maxBufferSize(): %lu (%lu/%lu/%lu)\n", 
             size, headSize, imageSize, attachmentSize ));
  
    return size;
}

//-------------------------------------------------------------------------
/*!
The dump method just writes some object debugging info to the LOG stream
*/
void ImageFileType::dump(void)
{
    std::list<IDString>::iterator    sI;

    SLOG << getMimeType();

    if(_suffixList.empty())
    {
        SLOG << ": Suffix: ";
        for(sI = _suffixList.begin(); sI != _suffixList.end(); sI++)
        {
            Log().stream(OSG::LOG_DEBUG) << sI->str() << " ";
        }
    }

    std::cerr << std::endl;
}
