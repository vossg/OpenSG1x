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
#include <fstream>

#include <OSGLog.h>
#include <OSGImageFileHandler.h>
#include <OSGPathHandler.h>
#include <OSGFileSystem.h>

#include "OSGDATImageFileType.h"

OSG_USING_NAMESPACE

/*! \class osg::DATImageFileType 
    \ingroup GrpSystemImage

Image File Type to read/write and store/restore Image objects as
PNM/RAW data.

All the type specific code is included in the class. Does
not depend on external libs.
    
 */

/*****************************
 *   Types
 *****************************/
// Static Class Varible implementations: 

static const Char8 *suffixArray[] = 
{
    "dat"
};

DATImageFileType DATImageFileType::_the( "dat",
                                         suffixArray, sizeof(suffixArray) );

std::map<std::string, 
         DATImageFileType::KeyType   > DATImageFileType::_keyStrMap;

std::map<std::string, 
         DATImageFileType::FormatDesc> DATImageFileType::_formatStrMap;

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
DATImageFileType& DATImageFileType::the (void)
{
  return _the;
}

/*******************************
*public
*******************************/

//-------------------------------------------------------------------------
/*!
Tries to fill the image object with the data read from
the given fileName. Returns true on success.
*/
bool DATImageFileType::read (      ImagePtr &image, 
                                   const Char8 *fileName )
{
    bool retCode = false;

    std::ifstream inDat(fileName), inVol;
    std::string keyStr, objectFileName;
    const UInt32 lineBufferSize = 1024;
    Char8 *value, *keySepPos, lineBuffer[lineBufferSize];
    const Char8 keySep = ':';
    int fileOffset, keyL, valueL;
    std::map<std::string, KeyType>::iterator keyI;
    std::map<std::string, FormatDesc>::iterator formatI;
    KeyType key;
    Image::Type formatType;
    UInt32 res[3];
    int bpv, dataSize = 0;
    Image::PixelFormat pixelFormat;
    char *dataBuffer = 0;
    bool needConversion;

    res[0] = res[1] = res[2] = 0;
    fileOffset = 0;
    formatType = Image::OSG_INVALID_IMAGEDATATYPE;
    bpv = 0;
    dataSize = 0;
    dataBuffer = 0;

    initTypeMap();

    beginEditCP(image);

    // read the data file 
    for ( lineBuffer[0] = 0; 
          inDat.getline ( lineBuffer, lineBufferSize);
          lineBuffer[0] = 0 ) 
    {        
        if ((keySepPos = strchr(lineBuffer,keySep))) 
        {
            keyL = keySepPos - lineBuffer;
            keyStr.assign( lineBuffer, keyL );        
            keyI = _keyStrMap.find(keyStr);
            key = ((keyI == _keyStrMap.end()) ? UNKNOWN_KT : keyI->second);
            value = keySepPos + 1;        
            while (value && isspace(*value))
                value++;
            valueL = strlen(value);
            while (isspace(value[valueL-1]))
                value[--valueL] = 0;
            switch (key)
            {
                case OBJECT_FILE_NAME_KT:
                    objectFileName = value;
                    image->setAttachmentField ( keyStr, value );
                    break;
                case RESOLUTION_KT:
                    sscanf ( value, "%d %d %d", 
                             &(res[0]), &(res[1]), &(res[2]));
                    image->setAttachmentField ( keyStr, value );
                    break;
                case FORMAT_KT:
                    formatI = _formatStrMap.find(value);
                    if (formatI != _formatStrMap.end())
                    {
                        formatType = formatI->second.type;
                        bpv = formatI->second.bpv;
                        pixelFormat = formatI->second.pixelFormat;
                        needConversion = formatI->second.needConversion;
                    }
                    else 
                    {
                        formatType = Image::OSG_INVALID_IMAGEDATATYPE;
                        bpv = 0;
                        pixelFormat = Image::OSG_INVALID_PF;
                        needConversion = false;
                    }
                    image->setAttachmentField ( keyStr, value ); 
                    break;
                case FILE_OFFSET_KT:
                    sscanf ( value, "%d", &fileOffset );
                    image->setAttachmentField ( keyStr, value );
                    break;
                case UNKNOWN_KT:
                    FWARNING (( "Uknown DAT file key: >%s<\n",
                                 keyStr.c_str() ));
                    image->setAttachmentField ( keyStr, value );
                    break;
                case SLICE_THICKNESS_KT:
                default:
                    image->setAttachmentField ( keyStr, value );
                    break;
            }
        }
        else 
        {        
            FINFO (("Skip DAT line\n"));
        }
    }
  
    // check the setting and read the raw vol data
    if (objectFileName.empty() == false) 
    {
        if ( (res[0] > 0) && (res[1] > 0) && (res[2] > 0) ) 
        {
            if (formatType != Image::OSG_INVALID_IMAGEDATATYPE) 
            {
                inVol.open(objectFileName.c_str(), 
                           std::ios::in | std::ios::binary );
                if (inVol.fail() && ImageFileHandler::the().getPathHandler())
                {
                    // Try to find the file in the search path
                    inVol.clear(); // reset the error state
                    PathHandler * ph = ImageFileHandler::the().getPathHandler();
                    inVol.open(ph->findFile(objectFileName.c_str()).c_str(),
                               std::ios::in | std::ios::binary );
                }
                if (inVol.good())
                {
                    image->set ( pixelFormat, res[0], res[1], res[2], 1, 1, 0.0, 0, formatType);
                    dataSize = bpv * res[0] * res[1] * res[2];
                    if (needConversion)
                        dataBuffer = new char [ dataSize ];
                    else
                        dataBuffer = ((char *)(image->getData()));

                    inVol.ignore ( fileOffset );
                    inVol.read ( dataBuffer, dataSize );
                }
                else 
                {
                    FLOG (( "Can not open %s image data\n", 
                             objectFileName.c_str() ));
                }
            }
            else 
            {
                FWARNING (( "Invalid/Missing DAT Format\n" ));
            }
        }
        else 
        {
            FWARNING (( "Invalid/Missing DAT Resolution\n" ));
        }
    }
    else 
    {
        FWARNING (( "Invalid/Missing DAT ObjectFileName\n" ));
    }

    // check/reformat vol data
    if (dataSize && dataBuffer)
    {
        if (needConversion) 
        {
            FLOG (("DAT-Data convert not impl. yet !\n"));
            {
                switch (formatType)
                {
                    case Image::OSG_UINT8_IMAGEDATA:
                        break;
                    case Image::OSG_UINT16_IMAGEDATA:
                        break;
                    case Image::OSG_UINT32_IMAGEDATA:
                        break;
                    case Image::OSG_FLOAT32_IMAGEDATA:
                        break;
                    default:
                        ;
                }
            }
        }
        else 
        {
            retCode = true;
        }
    }


    /* TODO
       std::ifstream in(fileName);
       Head head;
       void *headData = (void*)(&head);
       unsigned dataSize, headSize = sizeof(Head);

       if ( in &&        
       in.read(static_cast<char *>(headData), 
       headSize) && head.netToHost() &&
       image.set ( Image::PixelFormat(head.pixelFormat), 
       head.width, head.height, head.depth, head.mipmapCount, 
       head.frameCount, float(head.frameDelay) / 1000.0) &&
       (dataSize = image.getSize()) && 
       in.read((char *)(image.getData()), dataSize ))
       retCode = true;
       else
       retCode = false;
    */

    endEditCP(image);

    return retCode;
}

//-------------------------------------------------------------------------
/*!
Tries to write the image object to the given fileName.
Returns true on success.
*/
bool DATImageFileType::write(const ImagePtr &, 
                             const Char8 *OSG_CHECK_ARG(fileName))
{
    bool retCode = false;

    /*
    ofstream out(fileName);
    Head head;
    const void *headData = (void*)(&head);
    unsigned dataSize = image.getSize(), headSize = sizeof(Head);

    head.pixelFormat  = image.getPixelFormat();
    head.width        = image.getWidth();
    head.height       = image.getHeight();
    head.depth        = image.getDepth();
    head.mipmapCount  = image.getMipMapCount();
    head.frameCount   = image.getFrameCount();
    head.frameDelay   = short(image.getFrameDelay() * 1000.0);
    head.hostToNet();
  
    if ( out && out.write(static_cast<const char *>(headData), headSize) && 
         dataSize &&
             out.write((char *)(image.getData()), dataSize) )
            retCode = true;
    else
        retCode = false;    
    */

    return retCode;
}


//-------------------------------------------------------------------------
/*!
Tries to restore the image data from the given memblock.
Returns the amount of data read.
*/
UInt64 DATImageFileType::restoreData(      ImagePtr &image, 
                                     const UChar8   *buffer,
                                           Int32   OSG_CHECK_ARG(memSize) )
{
    image->setData(buffer);

    return image->getSize();
}

//-------------------------------------------------------------------------
/*!
Tries to store the image data to the given memblock.
Returns the amount of data written.
*/
UInt64 DATImageFileType::storeData(const ImagePtr &image, 
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
DATImageFileType::DATImageFileType ( const Char8 *mimeType,
                                     const Char8 *suffixArray[], 
                                     UInt16 suffixByteCount )
    : ImageFileType ( mimeType, suffixArray, suffixByteCount )
{
    return;
}

//-------------------------------------------------------------------------
/*!
Dummy Copy Constructor
*/
DATImageFileType::DATImageFileType (const DATImageFileType &obj )
    : ImageFileType(obj)
{
    return;
}

//-------------------------------------------------------------------------
/*!
Destructor
*/
DATImageFileType::~DATImageFileType (void )
{
    return;
}

//-------------------------------------------------------------------------
/*!
Helper to initialize the type map;
*/
void DATImageFileType::initTypeMap(void)
{
  FormatDesc *desc;

  if (_keyStrMap.empty())
    {
      _keyStrMap["ObjectFileName"]  = OBJECT_FILE_NAME_KT;
      _keyStrMap["Resolution"]      = RESOLUTION_KT;
      _keyStrMap["SliceThickness"]  = SLICE_THICKNESS_KT;
      _keyStrMap["Format"]          = FORMAT_KT;
      _keyStrMap["FileOffset"]      = FILE_OFFSET_KT;
     }

  if (_formatStrMap.empty())
    {
      desc = &(_formatStrMap["UCHAR"]);
      desc->type = Image::OSG_UINT8_IMAGEDATA;
      desc->bpv  = 1;
      desc->pixelFormat = Image::OSG_L_PF;
      desc->needConversion = false;

      desc = &(_formatStrMap["USHORT"]);
      desc->type = Image::OSG_UINT16_IMAGEDATA;
      desc->bpv  = 2;
      desc->pixelFormat = Image::OSG_L_PF;
      desc->needConversion = false;

      desc = &(_formatStrMap["UINT"]);
      desc->type = Image::OSG_UINT32_IMAGEDATA;
      desc->bpv  = 4; // TODO; is this right ?
      desc->pixelFormat = Image::OSG_L_PF;
      desc->needConversion = false;

      desc = &(_formatStrMap["ULONG"]);
      desc->type = Image::OSG_UINT32_IMAGEDATA;
      desc->bpv  = 4;
      desc->pixelFormat = Image::OSG_L_PF;
      desc->needConversion = false;

      desc = &(_formatStrMap["FLOAT"]);
      desc->type = Image::OSG_FLOAT32_IMAGEDATA;
      desc->bpv  = 4;
      desc->pixelFormat = Image::OSG_L_PF;
      desc->needConversion = false;

      desc = &(_formatStrMap["DOUBLE"]);
      desc->type = Image::OSG_FLOAT32_IMAGEDATA; // we have no OSG_FLOAT64_IMAGEDATA
      desc->bpv  = 8;
      desc->pixelFormat = Image::OSG_L_PF;
      desc->needConversion = false;
    }

}

