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


//---------------------------------------------------------
// 	Includes  
//---------------------------------------------------------


#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#define OSG_COMPILELOADER

#include <OSGLog.h>

#include "OSGSceneFileType.h"
#include "OSGSceneFileHandler.h"

OSG_USING_NAMESPACE

/********************************************************
 *   Types
\********************************************************/


/********************************************************
 *	  Classvariables
\********************************************************/




/********************************************************
 *	  Class methodes
\********************************************************/


/********************************************************
*instance methodes 
\*********************************************************/


/********************************************************
*public
\********************************************************/


/********************************************************
*protected
\*********************************************************/


/*********************************************************
*private	
\**********************************************************/


/*********************************************************
*public
\**********************************************************/


/**constructors & destructors**/


//--------------------------------------------------------
// Function name: SceneFileType
//--------------------------------------------------------
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
//---------------------------------------------------------
SceneFileType::SceneFileType ( const char * suffixArray[], 
																		 UInt16 suffixByteCount )
{
    fprintf(stderr, "Init Scene File Type %d\n", this);

	int count = (suffixByteCount / sizeof(const char *)), i = 0;
	list<String>::iterator sI;

	_suffixList.resize(count);
	for (sI = _suffixList.begin(); sI != _suffixList.end(); sI++)
		sI->set(suffixArray[i++]);

	SceneFileHandler::addSceneFileType(*this);
}

//--------------------------------------------------------
// Function name: SceneFileType
//--------------------------------------------------------
//
//Parameters:
//p: const SceneFileType &obj
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
//---------------------------------------------------------
SceneFileType::SceneFileType (const SceneFileType &obj )
	: _suffixList(obj._suffixList)
{
	SWARNING << "In SceneFileType copy constructor" << endl;
}

//--------------------------------------------------------
// Function name: ~SceneFileType
//--------------------------------------------------------
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
//---------------------------------------------------------
SceneFileType::~SceneFileType (void )
{
	return;
}


//--------------------------------------------------------
// Function name: print
//--------------------------------------------------------
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
//---------------------------------------------------------
void SceneFileType::print(void)
{
	list<String>::iterator sI;

	SDEBUG << getName();

	if (_suffixList.empty())
		osgLog() << "NONE";
	else
		for (sI = _suffixList.begin(); sI != _suffixList.end(); sI++) 
			osgLog().stream(::LOG_DEBUG) << sI->str() << " ";

	osgLog() << endl;
}



/*----------------------access----------------------------*/

/*----------------------properies-------------------------*/

/*----------------------your Category---------------------*/

/*----------------------Operators-------------------------*/



/**********************************************************
*protected	
\**********************************************************/


/*********************************************************
*private
\***********************************************************/


