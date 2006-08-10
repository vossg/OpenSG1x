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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include <OSGLog.h>

#include "OSGMTDImageFileType.h"

OSG_USING_NAMESPACE


/*! \class osg::MTDImageFileType 
    \ingroup GrpSystemImage

Image File Type to read/write and store/restore Image objects as
MTD data.

All the type specific code is included in the class. Does
not depend on external libs.
        
*/

/*****************************
 *   Types
 *****************************/
// Static Class Varible implementations: 

static const Char8 *suffixArray[] = 
{
    "mtd","opensg","opensgImage"
};

MTDImageFileType MTDImageFileType::_the("image/x-mtd",
                                        suffixArray, sizeof(suffixArray),
                                        OSG_READ_SUPPORTED | 
                                        OSG_WRITE_SUPPORTED );

/*****************************
 *    Classvariables
 *****************************/


/********************************
 *    Class methodes
 *******************************/


//-------------------------------------------------------------------------
/*!
Class method to get the singleton Object
*/
MTDImageFileType& MTDImageFileType::the (void)
{
  return _the;
}

/*******************************
*public
*******************************/

//-------------------------------------------------------------------------
/*!
Tries to fill the image object with the data read from
the given input stream. Returns true on success.
*/
bool MTDImageFileType::read  (ImagePtr &image, std::istream &in, const std::string &mimetype)
{
  bool retCode = false;
  Head head;
  void *headData = (void*)(&head);
  unsigned dataSize, headSize = sizeof(Head);
  
  if ( in.read(static_cast<char *>(headData), 
               headSize) && head.netToHost() &&
       image->set ( Image::PixelFormat(head.pixelFormat), 
                    head.width, head.height, head.depth, head.mipmapCount, 
                    head.frameCount, float(head.frameDelay) / 1000.0, 0,
                    ( head.dataType ? Image::Type(head.dataType) :
                      Image::OSG_UINT8_IMAGEDATA ), 
                    true, head.sideCount) &&
       (dataSize = image->getSize()) && 
       in.read((char *)(image->getData()), dataSize ))
      retCode = true;
  else
      retCode = false;

  return retCode;
}

//-------------------------------------------------------------------------
/*!
Tries to write the image object to the given output stream.
Returns true on success.
*/
bool MTDImageFileType::write (const ImagePtr &image, std::ostream &out, const std::string &mimetype)
{
    bool retCode = false;

    Head head;
    const void *headData = (void*)(&head);
    unsigned dataSize = image->getSize(), headSize = sizeof(Head);

    head.pixelFormat  = image->getPixelFormat();
    head.width        = image->getWidth();
    head.height       = image->getHeight();
    head.depth        = image->getDepth();
    head.mipmapCount  = image->getMipMapCount();
    head.frameCount   = image->getFrameCount();
    head.frameDelay   = short(image->getFrameDelay() * 1000.0);
    head.sideCount    = image->getSideCount();
    head.dataType     = image->getDataType();
    head.hostToNet();
  
    if ( out.write(static_cast<const char *>(headData), headSize) && 
         dataSize && out.write((char *)(image->getData()), dataSize) )
      retCode = true;
    else
      retCode = false;    

    return retCode;
}


//-------------------------------------------------------------------------
/*!
Tries to restore the image data from the given memblock.
Returns the amount of data read.
*/
UInt64 MTDImageFileType::restoreData(      ImagePtr &image, 
                                     const UChar8   *buffer,
                                           Int32     OSG_CHECK_ARG(memSize) )
{
    image->setData(buffer);

    return image->getSize();
}

//-------------------------------------------------------------------------
/*!
Tries to store the image data to the given memblock.
Returns the amount of data written.
*/
UInt64 MTDImageFileType::storeData(const ImagePtr &image, 
                                         UChar8   *buffer,
                                         Int32     OSG_CHECK_ARG(memSize))
{
    unsigned dataSize = image->getSize();
    const UChar8 *src = image->getData();

    if ( dataSize && src && buffer )
      memcpy( buffer, src, dataSize);
  
    return dataSize;
} 


//-------------------------------------------------------------------------
/*!
Constructor used for the singleton object
*/
MTDImageFileType::MTDImageFileType ( const Char8 *mimeType,
                                     const Char8 *suffixArray[], 
                                     UInt16 suffixByteCount,
                                     UInt32 flags )
    : ImageFileType ( mimeType, suffixArray, suffixByteCount, flags )
{}

//-------------------------------------------------------------------------
/*!
Destructor
*/
MTDImageFileType::~MTDImageFileType (void ) {}
