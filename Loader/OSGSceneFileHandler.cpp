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

#include "OSGSceneFileHandler.h"
#include "OSGNode.h"

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


SceneFileHandler * SceneFileHandler::_the = 0;


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
//r:SceneFileType
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
SceneFileType * SceneFileHandler::getFileType ( const char *fileName )
{
	String suffix;
	SceneFileType *type = 0;
	map <String, SceneFileType *>::iterator sI;
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
//p: Scene &image, const char *fileName
//GlobalVars:
//g: 
//Returns:
//r:Bool
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
NodePtr SceneFileHandler::read (const char *fileName )
{
	SceneFileType *type = getFileType(fileName);
	NodePtr node = NullNode;

	if ( ! fileName )
	{
		SWARNING << "cannot read NULL file" << endl;
		return node;
	}
	
	if (type) {
		SINFO << "try to read " << fileName << " as " << type->getName() << endl;
		node = type->read(fileName);
		if (node != NullNode)
			SINFO << "read ok:" << endl;
		else
			SWARNING << "could not read " << endl;
	}
	else
		SWARNING << "could not read " << fileName 
						 << "; unknown file format" << endl;

	return node;
}

//----------------------------
// Function name: write
//----------------------------
//
//Parameters:
//p: const Scene &image, const char *fileName
//GlobalVars:
//g: 
//Returns:
//r:Bool
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
Bool SceneFileHandler::write ( const NodePtr node, const char *fileName )
{
	Bool retCode = false;
	SceneFileType *type = getFileType(fileName);

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
void SceneFileHandler::print (void )
{
	map <String, SceneFileType *>::iterator sI;

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
//p: SceneFileType *fileType
//GlobalVars:
//g: 
//Returns:
//r:Bool
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
Bool SceneFileHandler::addSceneFileType (SceneFileType &fileType )
{
	Bool retCode = false;
	list<String>::iterator sI;
	map <String, SceneFileType *>::iterator smI;
	String suffix;

	if (!_the)
		_the = new SceneFileHandler;

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
// Function name: SceneFileHandler
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
SceneFileHandler::SceneFileHandler (void )
{
	return;
}

//----------------------------
// Function name: SceneFileHandler
//----------------------------
//
//Parameters:
//p: const SceneFileHandler &obj
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
SceneFileHandler::SceneFileHandler (const SceneFileHandler & )
{
	SWARNING << "In copy constructor; I shouldn't be in this corner" << endl; 
}

//----------------------------
// Function name: ~SceneFileHandler
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
SceneFileHandler::~SceneFileHandler (void )
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


