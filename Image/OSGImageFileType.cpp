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
#include "OSGLog.h"

OSG_USING_NAMESPACE

// Static Class Varible implementations: 

bool ImageFileType::Head::netToHost(void)
{
    pixelFormat  = ntohs(pixelFormat);
    width        = ntohs(width);
    height       = ntohs(height);
    depth        = ntohs(depth);
    mipmapCount  = ntohs(mipmapCount);
    frameCount   = ntohs(frameCount);
    frameDelay   = ntohs(frameDelay);

    return true;
}

bool ImageFileType::Head::hostToNet(void)
{
    pixelFormat  = htons(pixelFormat);
    width        = htons(width);
    height       = htons(height);
    depth        = htons(depth);
    mipmapCount  = htons(mipmapCount);
    frameCount   = htons(frameCount);
    frameDelay   = htons(frameDelay);

    return true;
}

//----------------------------------------------------------------------
// Method: ImageFileType
// Author: jbehr
// Date:   Tue Apr 11 15:32:43 2000
// Description:
//         Default Constructor
//----------------------------------------------------------------------
ImageFileType::ImageFileType(const Char8 *suffixArray[], UInt16 suffixByteCount)
{
    Int32              suffixCount = suffixByteCount / sizeof(const Char8 *);
    Int32              i = 0;
    list<IDString>::iterator sI;

    _suffixList.resize(suffixCount);
    for(sI = _suffixList.begin(); sI != _suffixList.end(); sI++)
    {
        sI->set(suffixArray[i++]);
        SINFO << "add image suffix: " << *sI << endLog;
    }

    ImageFileHandler::addImageFileType(*this);
}

//----------------------------------------------------------------------
// Method: ImageFileType
// Author: jbehr
// Date:   Tue Apr 11 15:32:43 2000
// Description:
//         Copy Constructor
//----------------------------------------------------------------------
ImageFileType::ImageFileType(const ImageFileType &obj) :
    _suffixList(obj._suffixList)
{
    SWARNING << "In ImageFileType copy constructor" << endl;
}

//----------------------------------------------------------------------
// Method: ~ImageFileType
// Author: jbehr
// Date:   Tue Apr 11 15:32:43 2000
// Description:
//         Destructor
//----------------------------------------------------------------------
ImageFileType::~ImageFileType(void)
{
    return;
}

/** fill the given image with the content of the mem 'buffer' */
UInt64 ImageFileType::restoreData(      Image  &OSG_CHECK_ARG(image  ), 
                                  const UChar8 *OSG_CHECK_ARG(buffer ),
                                        Int32   OSG_CHECK_ARG(memSize))
{
    FWARNING(("ImageXFileType::restoreData() not impl. for mimeType %s\n",
             getMimeType()));

    return 0;
}

/** store the given image to the mem 'buffer' */
UInt64 ImageFileType::storeData(const Image  &OSG_CHECK_ARG(image  ), 
                                      UChar8 *OSG_CHECK_ARG(buffer ),
                                      Int32   OSG_CHECK_ARG(memSize))
{
    FWARNING(("ImageXFileType::storeData() not impl. for mimeType %s\n",
             getMimeType()));

    return 0;
}

//----------------------------------------------------------------------
// Method: print
// Author: jbehr
// Date:   Tue Apr 11 15:32:43 2000
// Description:
//         Destructor
//----------------------------------------------------------------------
UInt64 ImageFileType::restore(Image &image, const UChar8 *buffer, Int32 memSize)
{
    UInt32          headSize = sizeof(Head);
    Head            *head = (Head *) const_cast<UChar8*>((buffer));
    const UChar8    *data = buffer ? (buffer + headSize) : 0;
    ImageFileType   *type;
    const char      *mimeType;

    if(head && data && head->netToHost() && (mimeType = head->mimeType))
    {
        if((type = ImageFileHandler::the().getFileType(mimeType, 0)))
        {
            image.set(Image::PixelFormat(head->pixelFormat), head->width,
                      head->height, head->depth, head->mipmapCount,
                      head->frameCount, float(head->frameDelay) / 1000.0, 0);
            type->restoreData(image, data, memSize - headSize);
        }
        else
        {
            FWARNING(("Can not restore image data, invalid mimeType: %s\n",
                     mimeType ? mimeType : "Unknown"));
        }
    }

    return headSize + image.getSize();
}

//----------------------------------------------------------------------
// Method: store
// Author: jbehr
// Date:   Tue Apr 11 15:32:43 2000
// Description:
//         Destructor
//----------------------------------------------------------------------
UInt64 ImageFileType::store(const Image &image, const char *mimeType,
                            UChar8 *buffer, Int32 memSize)
{
    ImageFileType   *type = ImageFileHandler::the().getFileType(mimeType);

    return type ? type->store(image, buffer, memSize) : 0;
}

//----------------------------------------------------------------------
// Method: print
// Author: jbehr
// Date:   Tue Apr 11 15:32:43 2000
// Description:
//         Destructor
//----------------------------------------------------------------------
UInt64 ImageFileType::store(const Image &image, UChar8 *buffer, Int32 memSize)
{
    Head            *head = (Head *) (buffer);
    unsigned        dataSize = 0, headSize = sizeof(Head);
    UChar8          *dest = (UChar8 *) (buffer ? (buffer + headSize) : 0);
    const UChar8    *src = image.getData();

  head->pixelFormat  = image.getPixelFormat();
  head->width        = image.getWidth();
  head->height       = image.getHeight();
  head->depth        = image.getDepth();
  head->mipmapCount  = image.getMipMapCount();
  head->frameCount   = image.getFrameCount();
  head->frameDelay   = short(image.getFrameDelay() * 1000.0);
  head->hostToNet();

    strcpy(head->mimeType, getMimeType());

    if(src && dest)
    {
        dataSize = storeData(image, dest, memSize - headSize);
    }

    return headSize + dataSize;
}

//----------------------------------------------------------------------
// Method: print
// Author: jbehr
// Date:   Tue Apr 11 15:32:43 2000
// Description:
//         Destructor
//----------------------------------------------------------------------
UInt64 ImageFileType::maxBufferSize(const Image &image)
{
    UInt64  size = sizeof(Head) + image.getSize();

    FDEBUG(("ImageFileType::maxBufferSize(): %d\n", size));

    return size;
}

//----------------------------------------------------------------------
// Method: print
// Author: jbehr
// Date:   Tue Apr 11 15:32:43 2000
// Description:
//         Destructor
//----------------------------------------------------------------------
void ImageFileType::print(void)
{
    list<IDString>::iterator    sI;

    SLOG << getMimeType();

    if(_suffixList.empty())
    {
        SLOG << ": Suffix: ";
        for(sI = _suffixList.begin(); sI != _suffixList.end(); sI++)
        {
            Log().stream(OSG::LOG_DEBUG) << sI->str() << " ";
        }
    }

    cerr << endl;
}
