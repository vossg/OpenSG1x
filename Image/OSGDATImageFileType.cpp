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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>
#include <fstream>

#include <OSGLog.h>

#include "OSGDATImageFileType.h"

OSG_USING_NAMESPACE

/*****************************
 *   Types
 *****************************/
// Static Class Varible implementations: 

static const Char8 *suffixArray[] = 
{
    "dat"
};

DATImageFileType DATImageFileType::_the(suffixArray, sizeof(suffixArray) );

map<std::string, DATImageFileType::KeyType> 
DATImageFileType::_keyStrMap;

map<std::string, DATImageFileType::FormatDesc> 
DATImageFileType::_formatStrMap;

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
// Function name: read
//----------------------------
//
//Parameters:
//p: Image &image, const Char8 *fileName
//GlobalVars:
//g: c
//Returns:
//r:Bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: read the image from the given file
//SeeAlso:
//s:
//
//------------------------------
Bool DATImageFileType::read (      Image &image, 
                                   const Char8 *fileName )
{
  Bool retCode = false;

  ifstream inDat(fileName), inVol;
  std::string keyStr, objectFileName;
  const UInt32 lineBufferSize = 1024;
  Char8 *value, *keySepPos, lineBuffer[lineBufferSize];
  const Char8 keySep = ':';
  int fileOffset, keyL, valueL;
  std::map<std::string, KeyType>::iterator keyI;
  std::map<std::string, FormatDesc>::iterator formatI;
  KeyType key;
  FormatType formatType;
  UInt32 res[3];
  int bpv, dataSize;
  Image::PixelFormat pixelFormat;
  char *dataBuffer;
  Bool needConversion;

  res[0] = res[1] = res[2] = 0;
  fileOffset = 0;
  formatType = UNKNOWN_FT;
  bpv = 0;
  dataSize = 0;
  dataBuffer = 0;

  initTypeMap();

  for ( keyI = _keyStrMap.begin();
        keyI != _keyStrMap.end(); ++keyI )
    cerr << ">" << keyI->first << "< is " << keyI->second << endl;

  // read the data file 
  for ( lineBuffer[0] = 0; 
        ( inDat.get ( lineBuffer, lineBufferSize) && 
          (keySepPos = strchr(lineBuffer,keySep)) );
        lineBuffer[0] = 0 ) 
    {        
      keyL = keySepPos - lineBuffer;
      keyStr.assign( lineBuffer, keyL + 1);
      keyStr[keyL] = 0;
      cerr << "find: >" << keyStr << "<" << endl;

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
          break;
        case RESOLUTION_KT:
          sscanf ( value, "%d %d %d", &(res[0]), &(res[1]), &(res[2]));
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
              formatType = UNKNOWN_FT;
              bpv = 0;
              pixelFormat = Image::OSG_INVALID_PF;
              needConversion = false;
            }
          break;
        case FILE_OFFSET_KT:
          sscanf ( value, "%d", &fileOffset );
          break;
        case SLICE_THICKNESS_KT:
        default:
          image.setAttachment ( keyStr, value );
          break;
        case UNKNOWN_KT:
          FWARNING (( "Uknown DAT file key: >%s<\n", keyStr.c_str() ));
          image.setAttachment ( keyStr, value );
          break;
        }
    }
  
  // check the setting and read the raw vol data
  if (objectFileName.empty() == false) 
    {
      if ( (res[0] > 0) && (res[1] > 0) && (res[2] > 0) ) 
        {
          if (formatType != UNKNOWN_FT) 
            {
              inVol.open(objectFileName.c_str(), ios::in | ios::binary );
              if (inVol)
                {
                  image.set ( pixelFormat, res[0], res[1], res[2]);
                  dataSize = bpv * res[0] * res[1] * res[2];
                  if (needConversion)
                    dataBuffer = new char [ dataSize ];
                  else
                    dataBuffer = ((char *)(image.getData()));

                  inVol.ignore ( fileOffset );
                  inVol.read ( dataBuffer, dataSize );
                }
              else 
                {
                  FWARNING (( "Can not open %s image data\n", 
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

  // vol data
  if (dataSize && dataBuffer && needConversion)
    {
      switch (formatType)
        {
        case UCHAR_FT:
          break;
        case USHORT_FT:
          break;
        case UINT_FT:
          break;
        case ULONG_FT:
          break;
        case FLOAT_FT:
          break;
        case DOUBLE_FT:
          break;
        }
    }


  /* TODO
  ifstream in(fileName);
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

  return retCode;
}

//----------------------------
// Function name: write
//----------------------------
//
//Parameters:
//p: Image &image, const Char8 *fileName
//GlobalVars:
//g: 
//Returns:
//r:Bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: write the image to the given file
//SeeAlso:
//s:
//
//------------------------------
Bool DATImageFileType::write(const Image &OSG_CHECK_ARG(image   ), 
                             const Char8 *OSG_CHECK_ARG(fileName))
{
    Bool retCode = false;

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

//----------------------------------------------------------------------
// Method: print
// Author: jbehr
// Date:   Tue Apr 11 15:32:43 2000
// Description:
//         Destructor
//----------------------------------------------------------------------
UInt64 DATImageFileType::restoreData(      Image  &image, 
                                     const UChar8 *buffer,
                                           Int32   OSG_CHECK_ARG(memSize) )
{
    image.setData(buffer);

    return true;
}

//----------------------------------------------------------------------
// Method: print
// Author: jbehr
// Date:   Tue Apr 11 15:32:43 2000
// Description:
//         Destructor
//----------------------------------------------------------------------
UInt64 DATImageFileType::storeData(const Image  &image, 
                                         UChar8 *buffer,
                                         Int32   OSG_CHECK_ARG(memSize))
{
    unsigned dataSize = image.getSize();
    const UChar8 *src = image.getData();

    if ( dataSize && src && buffer )
        memcpy( buffer, src, dataSize);
  
    return dataSize;
} 

/******************************
*protected
******************************/


/******************************
*private    
******************************/


/***************************
*instance methodes 
***************************/


/***************************
*public
***************************/


/**constructors & destructors**/


//----------------------------
// Function name: DATImageFileType
//----------------------------
//
//Parameters:
//p: const Char8 *suffixArray[], UInit16 suffixByteCount
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
DATImageFileType::DATImageFileType ( const Char8 *suffixArray[], 
                                     UInt16 suffixByteCount )
    : ImageFileType ( suffixArray, suffixByteCount )
{
    return;
}

//----------------------------
// Function name: DATImageFileType
//----------------------------
//
//Parameters:
//p: const DATImageFileType &obj
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
DATImageFileType::DATImageFileType (const DATImageFileType &obj )
    : ImageFileType(obj)
{
    return;
}

//----------------------------
// Function name: ~DATImageFileType
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
DATImageFileType::~DATImageFileType (void )
{
    return;
}

/*------------access----------------*/

/*------------properies-------------*/

/*------------your Category---------*/

/*------------Operators-------------*/



/****************************
*protected  
****************************/


/****************************
*private
****************************/

void DATImageFileType::initTypeMap(void)
{
  FormatDesc *desc;

  if (_keyStrMap.empty())
    {
      _keyStrMap["ObjectFileName"]  = OBJECT_FILE_NAME_KT;
      _keyStrMap["Resolution"]      = RESOLUTION_KT;
      _keyStrMap["SliceThickness"]  = SLICE_THICKNESS_KT;
      _keyStrMap["Format"]          = FORMAT_KT;
      _keyStrMap["FielOffset"]      = FILE_OFFSET_KT;
     }

  if (_formatStrMap.empty())
    {
      desc = &(_formatStrMap["UCHAR"]);
      desc->type = UCHAR_FT;
      desc->bpv  = 1;
      desc->pixelFormat = Image::OSG_L_PF;
      desc->needConversion = false;

      desc = &(_formatStrMap["USHORT"]);
      desc->type = USHORT_FT;
      desc->bpv  = 2;
      desc->pixelFormat = Image::OSG_L_PF;
      desc->needConversion = false;

      desc = &(_formatStrMap["UINT"]);
      desc->type = UINT_FT;
      desc->bpv  = 4; // TODO; is this right ?
      desc->pixelFormat = Image::OSG_L_PF;
      desc->needConversion = false;

      desc = &(_formatStrMap["ULONG"]);
      desc->type = ULONG_FT;
      desc->bpv  = 4;
      desc->pixelFormat = Image::OSG_L_PF;
      desc->needConversion = false;

      desc = &(_formatStrMap["FLOAT"]);
      desc->type = FLOAT_FT;
      desc->bpv  = 4;
      desc->pixelFormat = Image::OSG_L_PF;
      desc->needConversion = false;

      desc = &(_formatStrMap["DOUBLE"]);
      desc->type = DOUBLE_FT;
      desc->bpv  = 8;
      desc->pixelFormat = Image::OSG_L_PF;
      desc->needConversion = false;
    }

}

