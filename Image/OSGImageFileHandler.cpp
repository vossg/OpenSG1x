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

#include <OSGLog.h>
#include <OSGBaseTypes.h>

#include "OSGImageFileHandler.h"

#include "OSGMTDImageFileType.h"

OSG_USING_NAMESPACE

/* enum VecBase::VectorSizeE
 * brief 
*/


/* var VecBase::VectorSizeE VecBase::_iSize
 *
*/


/* const char *VecBase::getClassName(void)
 *  brief Classname
*/


/* var ValueTypeT VecBase:: _value[Size];
 * brief value store
*/


/*****************************
 *   Types
 *****************************/


/*****************************
 *	  Classvariables
 *****************************/


ImageFileHandler * ImageFileHandler::_the = 0;


/********************************
 *	  Class methodes
 *******************************/


/*******************************
*public
*******************************/


//----------------------------
// Function name: getFileType
//----------------------------
//
//Parameters:
//p: const char *mimeType, const char *fileName
//GlobalVars:
//g: 
//Returns:
//r:ImageFileType
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: getFileType
//SeeAlso:
//s:
//
//------------------------------
ImageFileType * ImageFileHandler::getFileType ( const char *mimeType,
                                                const char *fileName )
{
	IDString suffix;
	ImageFileType *type = 0;
	map <IDString, ImageFileType *>::iterator sI;
	const char separator = '.';
	int i, l;
	ifstream fin;

  if (mimeType && *mimeType) {

    // check mime type
    for ( sI = _suffixTypeMap.begin(); 
          sI != _suffixTypeMap.end(); ++sI ) {
      if (!strcmp(sI->second->getMimeType(),mimeType)) {
        type = sI->second;
        break;
      }
    }

  }

	if (!type && fileName && *fileName) {

		// check file suffix
		if (!type) {
			l = strlen(fileName);
			for (i = l - 1; i >= 0; i--) {
				if (fileName[i] == separator) 
					break;
			}
			if (i >= 0) {
				suffix.set(&(fileName[i+1]));
				suffix.toLower();
				sI = _suffixTypeMap.find(suffix);
				type = (sI == _suffixTypeMap.end()) ? 0 : sI->second;
			}
		}

	}
		
	return type;
}

//----------------------------
// Function name: getFileType
//----------------------------
//
//Parameters:
//p: const char *mimeType, const char *fileName
//GlobalVars:
//g: 
//Returns:
//r:ImageFileType
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: getFileType
//SeeAlso:
//s:
//
//------------------------------
ImageFileType * ImageFileHandler::getDefaultType (void)
{
  IDString dSuffix("opensg");
  map <IDString, ImageFileType *>::iterator sI = _suffixTypeMap.find(dSuffix);
  ImageFileType *type =(sI == _suffixTypeMap.end()) ? 0 : sI->second;

  if (!type) {
    FFATAL (( "Can not find any default (suffix:%s) image handler\n",
              dSuffix.str() ));
  }
  
  return type;
}

//----------------------------
// Function name: read
//----------------------------
//
//Parameters:
//p: Image &image, const char *fileName
//GlobalVars:
//g: 
//Returns:
//r:bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: 
//SeeAlso:
//s:
//
//------------------------------
Image * ImageFileHandler::read ( const char *fileName, const char *mimeType )
{
	Image *image = new Image;

	if (read(*image,fileName,mimeType) == false) {
		delete image;
		image = 0;
	}

	return image;
}

//----------------------------
// Function name: read
//----------------------------
//
//Parameters:
//p: Image &image, const char *fileName
//GlobalVars:
//g: 
//Returns:
//r:bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: 
//SeeAlso:
//s:
//
//------------------------------
bool ImageFileHandler::read (Image &image, 
                             const char *fileName, const char *mimeType)
{
	bool retCode = false;
	ImageFileType *type = getFileType(mimeType, fileName);

	if (type) {
		SINFO << "try to read " << fileName << " as " << type->getMimeType() 
          << endl;
		retCode = type->read(image,fileName);
		if (retCode) 
			SINFO << "image: " << image.getWidth() << "x" << image.getHeight()
							<< endl;
		else
			SWARNING << "could not read " << fileName << endl;
	}
	else
		SWARNING << "could not read " << fileName 
						 << "; unknown image format" << endl;

	return retCode;
}

//----------------------------
// Function name: write
//----------------------------
//
//Parameters:
//p: const Image &image, const char *fileName
//GlobalVars:
//g: 
//Returns:
//r:bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: 
//SeeAlso:
//s:
//
//------------------------------
bool ImageFileHandler::write ( const Image &image, 
                               const char *fileName,
                               const char *mimeType )
{
	bool retCode = false;
	ImageFileType *type = getFileType(mimeType,fileName);

	if (type) {
		SINFO << "try to write " << fileName << " as " << type->getMimeType() 
          << endl;
		retCode = type->write(image,fileName);
	}
	else
		SWARNING << "can't write " << fileName << "; unknown image format" <<                         endl;

	return retCode;
}

//----------------------------
// Function name: write
//----------------------------
//
//Parameters:
//p: const Image &image, const char *fileName
//GlobalVars:
//g: 
//Returns:
//r:bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: 
//SeeAlso:
//s:
//
//------------------------------
UInt64 ImageFileHandler::restore ( Image &image, 
                                   const UChar8 *buffer, UInt32 memSize )
{
	return ImageFileType::restore (image,buffer,memSize);
}

//----------------------------
// Function name: write
//----------------------------
//
//Parameters:
//p: const Image &image, const char *fileName
//GlobalVars:
//g: 
//Returns:
//r:bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: 
//SeeAlso:
//s:
//
//------------------------------
UInt64 ImageFileHandler::store ( const Image &image, const char *mimeType,
                                 UChar8 *buffer, UInt32 memSize )
{
	ImageFileType *type;

  type = mimeType ? getFileType(mimeType) : getDefaultType();

  return type->store(image,buffer,memSize);
}

//----------------------------
// Function name: write
//----------------------------
//
//Parameters:
//p: const Image &image, const char *fileName
//GlobalVars:
//g: 
//Returns:
//r:bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: 
//SeeAlso:
//s:
//
//------------------------------
UChar8* ImageFileHandler::store ( const Image &image,
                                  UInt64 &memSize,
                                  const char *mimeType)
{
  ImageFileType *type = 0;
  UChar8 *mem = 0;
 
  type = mimeType ? getFileType(mimeType) : getDefaultType();
  memSize = type->maxBufferSize(image);
  
  if (memSize) {
    mem = new UChar8[memSize];
    memSize = type->store(image,mem,memSize);
  } 
  else {
    FFATAL (("Can not store the image as %s\n", type->getMimeType()));
  }   
    
  return mem;
}

//----------------------------
// Function name: print
//----------------------------
//
//Parameters:
//p: void
//GlobalVars:
//g: 
//Returns:
//r:void
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: print debug info to cerr
//SeeAlso:
//s:
//
//------------------------------
void ImageFileHandler::print (void )
{
	map <IDString, ImageFileType *>::iterator sI;

	for (sI = _suffixTypeMap.begin(); sI != _suffixTypeMap.end(); sI++)
		cerr << "Image suffix: " << sI->first.str() 
				 << ", mime type: " << sI->second->getMimeType()
				 << endl;
}

/******************************
*protected
******************************/


/******************************
*private	
******************************/


//----------------------------
// Function name: addImageFileType
//----------------------------
//
//Parameters:
//p: ImageFileType *fileType
//GlobalVars:
//g: 
//Returns:
//r:bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: 
//SeeAlso:
//s:
//
//------------------------------
bool ImageFileHandler::addImageFileType (ImageFileType &fileType )
{
	bool retCode = false;
	list<IDString>::iterator sI;
	map <IDString, ImageFileType *>::iterator smI;
	IDString suffix;

	if (!_the)
		_the = new ImageFileHandler;
  
  for ( sI = fileType.suffixList().begin();
        sI != fileType.suffixList().end(); ++sI) {
    suffix.set(sI->str());
    suffix.toLower();
    smI = _the->_suffixTypeMap.find(suffix);
    if (smI != _the->_suffixTypeMap.end()) {
      SWARNING << "Can't add an image file type with suffix "
               << suffix << " a second time" << endl;
    }
    else {
      _the->_suffixTypeMap[suffix] = &fileType;
      retCode = true;
    }
  }

	return retCode;
}

/***************************
*instance methodes 
***************************/


/***************************
*public
***************************/


/**constructors & destructors**/


//----------------------------
// Function name: ImageFileHandler
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
//d: Default Constructor
//SeeAlso:
//s:
//
//------------------------------
ImageFileHandler::ImageFileHandler (void )
{
	return;
}

//----------------------------
// Function name: ImageFileHandler
//----------------------------
//
//Parameters:
//p: const ImageFileHandler &obj
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
ImageFileHandler::ImageFileHandler (const ImageFileHandler &obj )
{
	SWARNING << "In copy constructor; I shouldn't be in this corner" << endl; 
}

//----------------------------
// Function name: ~ImageFileHandler
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
ImageFileHandler::~ImageFileHandler (void )
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


