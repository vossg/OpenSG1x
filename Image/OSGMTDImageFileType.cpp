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
// 	Includes 					 			    
//-------------------------------

#define OSG_COMPILESYSTEMLIB

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>
#include <fstream>

#include <OSGLog.h>

#include "OSGMTDImageFileType.h"

// to get ntons/ntohs
#ifdef WIN32
#include <winsock.h>
#else
#include <arpa/inet.h>
#endif

OSG_USING_NAMESPACE

/*****************************
 *   Types
 *****************************/
// Static Class Varible implementations: 
static const Char8 *suffixArray[] = 
{
	"mtd","opensg","opensgImage"
};

MTDImageFileType MTDImageFileType::_the ( 	suffixArray,
																						sizeof(suffixArray) );

Bool MTDImageFileType::Head::netToHost(void)
{
  magic        = ntohs(magic);
  pixelFormat  = ntohs(pixelFormat);
  width        = ntohs(width);
  height       = ntohs(height);
  depth        = ntohs(depth);
  mipmapCount  = ntohs(mipmapCount);
  frameCount   = ntohs(frameCount);
  frameDelay   = ntohs(frameDelay);

  return true;
}

Bool MTDImageFileType::Head::hostToNet(void)
{
  magic        = htons(magic);
  pixelFormat  = htons(pixelFormat);
  width        = htons(width);
  height       = htons(height);
  depth        = htons(depth);
  mipmapCount  = htons(mipmapCount);
  frameCount   = htons(frameCount);
  frameDelay   = htons(frameDelay);

  return true;
}

/*****************************
 *	  Classvariables
 *****************************/


/********************************
 *	  Class methodes
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
bool MTDImageFileType::read (Image &image, const Char8 *fileName )
{
  bool retCode = false;
  ifstream in(fileName);
  Head head;
  void *headData = (void*)(&head);
  unsigned n, dataSize, headSize = sizeof(Head);

  if ( in && in.read(headData, headSize) && head.netToHost() &&
       image.set ( Image::PixelFormat(head.pixelFormat), 
                   head.width, head.height, head.depth, head.mipmapCount, 
                   head.frameCount, float(head.frameDelay) / 1000.0) &&
       (dataSize = image.getSize()) && in.read(image.getData(), dataSize ))
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
bool MTDImageFileType::write ( const Image &image, const Char8 *fileName )
{	
  bool retCode = false;
  ofstream out(fileName);
  Head head;
  void *headData = (void*)(&head);
  unsigned n, dataSize = image.getSize(), headSize = sizeof(Head);

  head.pixelFormat  = image.getPixelFormat();
  head.width        = image.getWidth();
  head.height       = image.getHeight();
  head.depth        = image.getDepth();
  head.mipmapCount  = image.getMipMapCount();
  head.frameCount   = image.getFrameCount();
  head.frameDelay   = short(image.getFrameDelay() * 1000.0);
  head.hostToNet();
  
  if ( out && out.write(headData, headSize) && dataSize &&
       out.write(image.getData(), dataSize) )
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
UInt64 MTDImageFileType::restore (Image &image, const UChar8 *buffer,
                                  Int32 memSize )
{
  UInt32 headSize = sizeof(Head);
  Head *head = (Head*)(buffer);
  const UChar8 *data = buffer ? (buffer + headSize) : 0;

  if ( head && data && head->netToHost() )  
    image.set ( Image::PixelFormat(head->pixelFormat), 
                head->width, head->height, head->depth, head->mipmapCount, 
                head->frameCount, float(head->frameDelay) / 1000.0, data );

  return (headSize + image.getSize());
}

//----------------------------------------------------------------------
// Method: print
// Author: jbehr
// Date:   Tue Apr 11 15:32:43 2000
// Description:
//         Destructor
//----------------------------------------------------------------------
UInt64 MTDImageFileType::store ( const Image &image, UChar8 *buffer,
                                 Int32 memSize )
{
  bool retCode = false;
  Head *head = (Head*)(buffer);
  unsigned n, dataSize = image.getSize(), headSize = sizeof(Head);
  UChar8 *dest = (UChar8*)(buffer ? (buffer + headSize) : 0);
  const UChar8 *src = image.getData();

  head->pixelFormat  = image.getPixelFormat();
  head->width        = image.getWidth();
  head->height       = image.getHeight();
  head->depth        = image.getDepth();
  head->mipmapCount  = image.getMipMapCount();
  head->frameCount   = image.getFrameCount();
  head->frameDelay   = short(image.getFrameDelay() * 1000.0);
  head->hostToNet();
  
  if ( dataSize && src && dest )
    memcpy( dest, src, dataSize);

  return (headSize + dataSize);
} 

//----------------------------------------------------------------------
// Method: print
// Author: jbehr
// Date:   Tue Apr 11 15:32:43 2000
// Description:
//         Destructor
//----------------------------------------------------------------------
UInt64 MTDImageFileType::maxBufferSize(const Image &image )
{
  return (sizeof(Head) + image.getSize());
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


