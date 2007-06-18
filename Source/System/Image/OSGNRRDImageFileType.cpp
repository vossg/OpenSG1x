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
//  Includes
//-------------------------------
#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <vector>
#include <string>

#include <iostream>

#include <OSGLog.h>

#include "OSGNRRDImageFileType.h"

#ifdef OSG_SGI_STL

//#include <limits>
#ifndef INT_MAX
#define INT_MAX numeric_limits<int>::max()
#endif
#else
#include <limits.h>
#endif
OSG_USING_NAMESPACE


/*! \class osg::NRRDImageFileType 
    \ingroup GrpSystemImage

Image File Type to read/write and store/restore Image objects as
NRRD data. Should work with intern/extern binary and ascii nrrd data

All the type specific code is included in the class. Does
not depend on external libs.
        
*/


/*****************************
 *   Types
 *****************************/
// Static Class Varible implementations:
static const Char8 *suffixArray[] =
{
    "nrrd"
};


NRRDImageFileType NRRDImageFileType::_the("image/x-nrrd",
                                        suffixArray, sizeof(suffixArray),
                                        OSG_READ_SUPPORTED | 
                                        OSG_WRITE_SUPPORTED);

/*****************************
 *    Classvariables
 *****************************/

enum HeadElem {
  INVALID_HE,
  MIME_HE,
  TYPE_HE,
  DIMENSION_HE,
  SIZES_HE,
  ENDIAN_HE,
  ENCODING_HE,

  UNSIGNED_HE,
  SIGNED_HE,

  LITTLE_HE,
  BIG_HE,
  
  RAW_HE,
  ASCII_HE,

  CHAR_HE,  
  SHORT_HE,
};

struct HeadStr {
  std::string str;
  HeadElem    headElem;
};

static HeadStr headStrVec[] = {
  { "NRRD0001",   MIME_HE },
  { "type",       TYPE_HE },
  { "dimension",  DIMENSION_HE },
  { "sizes",      SIZES_HE },
  { "endian",     ENDIAN_HE },
  { "encoding",   ENCODING_HE },

  { "unsigned",   UNSIGNED_HE },
  { "signed",     SIGNED_HE },

  { "char",       CHAR_HE },
  { "short",      SHORT_HE },

  { "",           INVALID_HE }
};

inline HeadElem mapElem (const std::string & str ) 
{
  unsigned i = 0;

  for ( i = 0; headStrVec[i].headElem != INVALID_HE; ++i )
    if (headStrVec[i].str == str)
      break;

  return headStrVec[i].headElem;
}

inline unsigned stringTokenizer( const std::string& str,
                                 std::vector<std::string>& tokens,
                                 const std::string& delimiters = " ")
{
    // Skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }

    return tokens.size();
}

/********************************
 *    Class methodes
 *******************************/

//-------------------------------------------------------------------------
/*!
Class method to get the singleton Object
*/
NRRDImageFileType& NRRDImageFileType::the (void)
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
bool NRRDImageFileType::read(ImagePtr &image, std::istream &in, const std::string &mimetype)
{
    bool     retCode = false;
    bool     isSigned = false, littleEndian = true, rawEncoding = true;
    int      width = 1, height = 1, depth = 1, dimension = 3, channel = 1;
    HeadElem dataType = INVALID_HE;
    unsigned i, n, m;
    UChar8   *data = 0;
    std::string line;
    std::vector < std::string > tokenVec;
    bool inHead;
    osg::Image::PixelFormat pixelFormat;
    osg::Image::Type imageType;

    if (in.good()) {
      for (inHead = true; inHead;) {
        std::getline(in,line);
        tokenVec.clear();
        if ((n = stringTokenizer (line, tokenVec, ": \n"))) {
          switch (mapElem(tokenVec[0])){
          case TYPE_HE:
            switch (n) {
            case 2:
              dataType = mapElem(tokenVec[1]);
              break;
            case 3:
              isSigned = (mapElem(tokenVec[1]) == SIGNED_HE);
              dataType = mapElem(tokenVec[2]);
              break;
            default:
              FFATAL (( "Invalid %s/%d in NRRD header\n",
                        tokenVec[0].c_str(), n ));
              break;
            }
            break;
          case DIMENSION_HE:
            switch (n) {
            case 2:
              dimension = atoi(tokenVec[1].c_str());
              break;
            default:
              FFATAL (( "Invalid %s/%d in NRRD header\n",
                        tokenVec[0].c_str(), n ));
              break;
            }
            break;
          case SIZES_HE:
            switch (n) {
            case 5:
              channel = atoi(tokenVec[1].c_str());
              width   = atoi(tokenVec[2].c_str());
              height  = atoi(tokenVec[3].c_str());
              depth   = atoi(tokenVec[4].c_str());              
              break;              
            case 4:
              width  = atoi(tokenVec[1].c_str());
              height = atoi(tokenVec[2].c_str());
              depth  = atoi(tokenVec[3].c_str());              
              break;
            case 3:
              width  = atoi(tokenVec[1].c_str());
              height = atoi(tokenVec[2].c_str());
              depth  = 1;
              break;
            case 2:
              width  = atoi(tokenVec[1].c_str());
              height = 1;
              depth  = 1;
              break;
            default:
              FFATAL (( "Invalid %s/%d in NRRD header\n",
                        tokenVec[0].c_str(), n ));
              break;
            }
	    if ((n <= 4) && (width <= 4)) 
            {
               channel = width;
               width = height;
               height = depth;
               depth = 1;
            }
            break;
          case ENDIAN_HE:
            switch (n) {
            case 2:
              littleEndian = (mapElem(tokenVec[1]) == LITTLE_HE);
              break;
            default:
              FFATAL (( "Invalid %s/%d in NRRD header\n",
                        tokenVec[0].c_str(), n ));
              break;
            }
            break;
          case ENCODING_HE:
            switch (n) {
            case 2:
              rawEncoding = (mapElem(tokenVec[1]) == RAW_HE);
              break;
            default:
              FFATAL (( "Invalid %s/%d in NRRD header\n",
                        tokenVec[0].c_str(), n ));
              break;              
            }
            break;
          default:
            break;
          }
        }
        else 
          inHead = false;
      }
      
      switch (dataType) {
      case SHORT_HE:
        imageType = osg::Image::OSG_UINT16_IMAGEDATA;
        break;
      default:
        imageType = osg::Image::OSG_UINT8_IMAGEDATA;
        break;
      }

      switch (channel) {
      case 4:
        pixelFormat = osg::Image::OSG_RGBA_PF;
        break;
      case 3:
        pixelFormat = osg::Image::OSG_RGB_PF;
        break;
      case 2:
        pixelFormat = osg::Image::OSG_LA_PF;
        break;
      default:
        pixelFormat = osg::Image::OSG_L_PF;
        break;
      }

      if (isSigned) {
        FFATAL (( "Read signed data not supported\n" ));
      }

      FINFO(("NRRDImageFileType::read: got %d D %s endian %s data.\n",
                dimension, littleEndian?"little":"big",
                rawEncoding?"raw":"cooked"));
      
      image->set ( pixelFormat, width, height, depth,
                   1, 1, 0.0, 0, imageType );

      n    = image->getSize();
      data = image->getData();

      in.read ((char*)(data), n);

      retCode = true;
    }

    return retCode;
}

//-------------------------------------------------------------------------
/*!
Constructor used for the singleton object
*/
NRRDImageFileType::NRRDImageFileType(const Char8 *mimeType,
                                   const Char8 *suffixArray[],
                                   UInt16 suffixByteCount,
                                   UInt32 flags) :
    ImageFileType(mimeType, suffixArray, suffixByteCount, flags)
{}

//-------------------------------------------------------------------------
/*!
Destructor
*/
NRRDImageFileType::~NRRDImageFileType(void) {}
