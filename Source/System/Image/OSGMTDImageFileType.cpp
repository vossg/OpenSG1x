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

#include "OSGMTDImageFileType.h"

OSG_USING_NAMESPACE


/*! \class osg::MTDImageFileType 
    \ingroup GrpSystemImage
    
*/

/*****************************
 *   Types
 *****************************/
// Static Class Varible implementations: 

static const Char8 *suffixArray[] = 
{
    "mtd","opensg","opensgImage"
};

MTDImageFileType MTDImageFileType::_the(suffixArray, sizeof(suffixArray) );

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
//r:bool
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
bool MTDImageFileType::read (      Image &image   , 
                             const Char8 *fileName)
{
  bool retCode = false;
  std::ifstream in(fileName, std::ios::in | std::ios::binary);
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
//r:bool
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
bool MTDImageFileType::write(const Image &image   , 
                             const Char8 *fileName)
{
    bool retCode = false;

    std::ofstream out(fileName, std::ios::out | std::ios::binary);

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
         dataSize && out.write((char *)(image.getData()), dataSize) )
      retCode = true;
    else
      retCode = false;    

    return retCode;
}

//----------------------------------------------------------------------
// Method: print
// Author: jbehr
// Date:   Tue Apr 11 15:32:43 2000
// Description:
//         Destructor
//----------------------------------------------------------------------
UInt64 MTDImageFileType::restoreData(      Image  &image, 
                                     const UChar8 *buffer,
                                           Int32   OSG_CHECK_ARG(memSize) )
{
    image.setData(buffer);

    return image.getSize();
}

//----------------------------------------------------------------------
// Method: print
// Author: jbehr
// Date:   Tue Apr 11 15:32:43 2000
// Description:
//         Destructor
//----------------------------------------------------------------------
UInt64 MTDImageFileType::storeData(const Image  &image, 
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
// Function name: MTDImageFileType
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
MTDImageFileType::MTDImageFileType ( const Char8 *suffixArray[], 
                                     UInt16 suffixByteCount )
    : ImageFileType ( suffixArray, suffixByteCount )
{
    return;
}

//----------------------------
// Function name: MTDImageFileType
//----------------------------
//
//Parameters:
//p: const MTDImageFileType &obj
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
MTDImageFileType::MTDImageFileType (const MTDImageFileType &obj )
    : ImageFileType(obj)
{
    return;
}

//----------------------------
// Function name: ~MTDImageFileType
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
MTDImageFileType::~MTDImageFileType (void )
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


