/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#define OSG_COMPILEIMAGE

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <OSGLog.h>
#include <OSGBaseTypes.h>

#include "OSGImageFileHandler.h"

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
//p: const char *fileName, bool checkMagic = true
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
ImageFileType * ImageFileHandler::getFileType ( const char *fileName, 
																											bool checkMagic )
{
	UInt8 majorMagic, minorMagic;
	String suffix;
	ImageFileType *type = 0;
	map <String, ImageFileType *>::iterator sI;
	const char separator = '.';
	int i, l;
	ifstream fin;

	if (fileName) {

		// check magic code;
		if (checkMagic) {
			fin.open(fileName);
			if (fin.rdbuf()->is_open()) {
				fin >> majorMagic >> minorMagic;
				type = getFileType(majorMagic, minorMagic);
				if (!type) {
					type = getFileType(majorMagic, -1);
					if (!type) {
						type = getFileType(-1, minorMagic);
						if (!type) 
							type = getFileType(-1,-1);
					}
				}
				fin.close();
			}
		}

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
Image * ImageFileHandler::read (const char *fileName )
{
	Image *image = new Image;

	if (read(*image,fileName) == false) {
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
bool ImageFileHandler::read (Image &image, const char *fileName )
{
	bool retCode = false;
	ImageFileType *type = getFileType(fileName);

	if (type) {
		SINFO << "try to read " << fileName << " as " << type->getName() << endl;
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
bool ImageFileHandler::write (const Image &image, const char *fileName )
{
	bool retCode = false;
	ImageFileType *type = getFileType(fileName,false);

	if (type) {
		SINFO << "try to write " << fileName << " as " << type->getName() << endl;
		retCode = type->write(image,fileName);
	}
	else
		SWARNING << "can't write " << fileName << "; unknown image format" <<                         endl;

	return retCode;
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
	map <String, ImageFileType *>::iterator sI;

	for (sI = _suffixTypeMap.begin(); sI != _suffixTypeMap.end(); sI++)
		cerr << "suffix: " << sI->first.str() 
				 << ", type: " << sI->second->getName()
				 << ", magic: " << sI->second->getMajorMagic() 
				 << ", " << sI->second->getMinorMagic()
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
	list<String>::iterator sI;
	map <String, ImageFileType *>::iterator smI;
	String suffix;
	Int16 major = fileType.getMajorMagic(), minor = fileType.getMinorMagic();

	if (!_the)
		_the = new ImageFileHandler;

	if (_the->getFileType(major,minor)) {
		SINFO << "Can't add an image file type with magic "
						 << major << ", " << minor << " a second time" << endl;
	}
	else {
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
				_the->_magicTypeMap[major][minor] = &fileType;
				retCode = true;
			}
		}
	}

	return retCode;
}

//----------------------------
// Function name: getFileType
//----------------------------
//
//Parameters:
//p: Init16 majorMagic = -1, Init16 minorMagic = -1,
//GlobalVars:
//g: 
//Returns:
//r:ImageFileType
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
ImageFileType * ImageFileHandler::getFileType ( Int16 majorMagic, 
																											Int16 minorMagic )
{
	ImageFileType *type = 0;
	map <Int16, MinorMap>::iterator magicI;
	MinorMap::iterator minorI;

	magicI = _magicTypeMap.find(majorMagic);
	if (magicI != _magicTypeMap.end()) {
		minorI = magicI->second.find(minorMagic);
		type = ((minorI == magicI->second.end()) ? 0 : minorI->second);
	}

	return type;
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


