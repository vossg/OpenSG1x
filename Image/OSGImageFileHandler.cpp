/*------------------------------------------*
*              OpenSG                       *
*                                           *
*                                           *
*     Copyright 2000 by OpenSG Forum        *
*                                           *
* contact: {reiners|vossg}@igd.fhg.de,      *
*           jbehr@zgdv.de                   *
*-------------------------------------------*/
/*------------------------------------------*
*              Licence                      *
*                                           *
*                                           *
*                                           *
*                                           *
*                                           *
*-------------------------------------------*/
/*------------------------------------------*
*              Changes                      *
*                                           *
*                                           *
*                                           *
*                                           *
*                                           *
*-------------------------------------------*/


//-------------------------------
// 	Includes 					 			    
//-------------------------------


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

/* enum OSGVecBase::VectorSizeE
 * brief 
*/


/* var OSGVecBase::VectorSizeE OSGVecBase::_iSize
 *
*/


/* const char *OSGVecBase::getClassName(void)
 *  brief Classname
*/


/* var OSGValueTypeT OSGVecBase:: _value[Size];
 * brief value store
*/


/*****************************
 *   Types
 *****************************/


/*****************************
 *	  Classvariables
 *****************************/


OSGImageFileHandler * OSGImageFileHandler::_the = 0;


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
//r:OSGImageFileType
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
OSGImageFileType * OSGImageFileHandler::getFileType ( const char *fileName, 
																											bool checkMagic )
{
	OSGUInt8 majorMagic, minorMagic;
	OSGString suffix;
	OSGImageFileType *type = 0;
	map <OSGString, OSGImageFileType *>::iterator sI;
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
				suffix.tolower();
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
//p: OSGImage &image, const char *fileName
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
OSGImage * OSGImageFileHandler::read (const char *fileName )
{
	OSGImage *image = new OSGImage;

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
//p: OSGImage &image, const char *fileName
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
bool OSGImageFileHandler::read (OSGImage &image, const char *fileName )
{
	bool retCode = false;
	OSGImageFileType *type = getFileType(fileName);

	if (type) {
		SINFO << "try to read " << fileName << " as " << type->getName() << endl;
		retCode = type->read(image,fileName);
		if (retCode) 
			SINFO << "image: " << image.width() << "x" << image.height()
							<< " " << image.pixelFormat() << endl;
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
//p: const OSGImage &image, const char *fileName
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
bool OSGImageFileHandler::write (const OSGImage &image, const char *fileName )
{
	bool retCode = false;
	OSGImageFileType *type = getFileType(fileName,false);

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
void OSGImageFileHandler::print (void )
{
	map <OSGString, OSGImageFileType *>::iterator sI;

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
//p: OSGImageFileType *fileType
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
bool OSGImageFileHandler::addImageFileType (OSGImageFileType &fileType )
{
	bool retCode = false;
	list<OSGString>::iterator sI;
	map <OSGString, OSGImageFileType *>::iterator smI;
	OSGString suffix;
	OSGInt16 major = fileType.getMajorMagic(), minor = fileType.getMinorMagic();

	if (!_the)
		_the = new OSGImageFileHandler;

	if (_the->getFileType(major,minor)) {
		SINFO << "Can't add an image file type with magic "
						 << major << ", " << minor << " a second time" << endl;
	}
	else {
		for ( sI = fileType.suffixList().begin();
					sI != fileType.suffixList().end(); ++sI) {
			suffix.set(sI->str());
			suffix.tolower();
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
//p: OSGInit16 majorMagic = -1, OSGInit16 minorMagic = -1,
//GlobalVars:
//g: 
//Returns:
//r:OSGImageFileType
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
OSGImageFileType * OSGImageFileHandler::getFileType ( OSGInt16 majorMagic, 
																											OSGInt16 minorMagic )
{
	OSGImageFileType *type = 0;
	map <OSGInt16, MinorMap>::iterator magicI;
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
// Function name: OSGImageFileHandler
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
OSGImageFileHandler::OSGImageFileHandler (void )
{
	return;
}

//----------------------------
// Function name: OSGImageFileHandler
//----------------------------
//
//Parameters:
//p: const OSGImageFileHandler &obj
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
OSGImageFileHandler::OSGImageFileHandler (const OSGImageFileHandler &obj )
{
	SWARNING << "In copy constructor; I shouldn't be in this corner" << endl; 
}

//----------------------------
// Function name: ~OSGImageFileHandler
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
OSGImageFileHandler::~OSGImageFileHandler (void )
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


