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

#include "OSGSceneFileHandler.h"

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


OSGSceneFileHandler * OSGSceneFileHandler::_the = 0;


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
//p: const char *fileName
//GlobalVars:
//g: 
//Returns:
//r:OSGSceneFileType
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
OSGSceneFileType * OSGSceneFileHandler::getFileType ( const char *fileName )
{
	OSGString suffix;
	OSGSceneFileType *type = 0;
	map <OSGString, OSGSceneFileType *>::iterator sI;
	const char separator = '.';
	int i, l;
	ifstream fin;

	if (fileName) {

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
//p: OSGScene &image, const char *fileName
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
OSGNodePtr OSGSceneFileHandler::read (const char *fileName )
{
	OSGSceneFileType *type = getFileType(fileName);
	OSGNodePtr node;

	if (type) {
		SINFO << "try to read " << fileName << " as " << type->getName() << endl;
		node = type->read(fileName);
		if (node != OSGNullNode)
			SINFO << "read ok:" << endl;
		else
			SWARNING << "could not read " << endl;
	}
	else
		SWARNING << "could not read " << fileName 
						 << "; unknown image format" << endl;

	return node;
}

//----------------------------
// Function name: write
//----------------------------
//
//Parameters:
//p: const OSGScene &image, const char *fileName
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
bool OSGSceneFileHandler::write ( const OSGNodePtr node, const char *fileName )
{
	bool retCode = false;
	OSGSceneFileType *type = getFileType(fileName);

	if (type) {
		SINFO << "try to write " << fileName << " as " << type->getName() << endl;
		retCode = type->write(node,fileName);
	}
	else
		SWARNING << "can't write " << fileName << "; unknown scene format" 
						 << endl;

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
void OSGSceneFileHandler::print (void )
{
	map <OSGString, OSGSceneFileType *>::iterator sI;

	for (sI = _suffixTypeMap.begin(); sI != _suffixTypeMap.end(); sI++)
		cerr << "suffix: " << sI->first.str() 
				 << ", type: " << sI->second->getName()
				 << endl;
}

/******************************
*protected
******************************/


/******************************
*private	
******************************/


//----------------------------
// Function name: addSceneFileType
//----------------------------
//
//Parameters:
//p: OSGSceneFileType *fileType
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
bool OSGSceneFileHandler::addSceneFileType (OSGSceneFileType &fileType )
{
	bool retCode = false;
	list<OSGString>::iterator sI;
	map <OSGString, OSGSceneFileType *>::iterator smI;
	OSGString suffix;

	if (!_the)
		_the = new OSGSceneFileHandler;

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
// Function name: OSGSceneFileHandler
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
OSGSceneFileHandler::OSGSceneFileHandler (void )
{
	return;
}

//----------------------------
// Function name: OSGSceneFileHandler
//----------------------------
//
//Parameters:
//p: const OSGSceneFileHandler &obj
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
OSGSceneFileHandler::OSGSceneFileHandler (const OSGSceneFileHandler & )
{
	SWARNING << "In copy constructor; I shouldn't be in this corner" << endl; 
}

//----------------------------
// Function name: ~OSGSceneFileHandler
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
OSGSceneFileHandler::~OSGSceneFileHandler (void )
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


