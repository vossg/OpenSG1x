/*---------------------------------------------------------*
 *              OpenSG                                     *
 *                                                         *
 *     	  Copyright 2000 by OpenSG Forum                   *
 *                                                         *
 *         contact: {reiners|vossg}@igd.fhg.de,            *
 *        jbehr@zgdv.de                                    *
 *                                                         *
 \*--------------------------------------------------------*/
/*---------------------------------------------------------*\
 *              Licence                                    *
 *                                                         *
 *                                                         *
 *                                                         *
 *                                                         *
 *                                                         *
 *                                                         *
 \*--------------------------------------------------------*/
/*---------------------------------------------------------*\
 *              Changes                                    *
 *                                                         *
 *                                                         *
 *                                                         *
 *                                                         *
 *                                                         *
 *                                                         *
\*---------------------------------------------------------*/


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
// Function name: OSGSceneFileType
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
OSGSceneFileType::OSGSceneFileType ( const char * suffixArray[], 
																		 OSGUInt16 suffixByteCount )
{
	int count = (suffixByteCount / sizeof(const char *)), i = 0;
	list<OSGString>::iterator sI;

	_suffixList.resize(count);
	for (sI = _suffixList.begin(); sI != _suffixList.end(); sI++)
		sI->set(suffixArray[i++]);

	OSGSceneFileHandler::addSceneFileType(*this);
}

//--------------------------------------------------------
// Function name: OSGSceneFileType
//--------------------------------------------------------
//
//Parameters:
//p: const OSGSceneFileType &obj
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
OSGSceneFileType::OSGSceneFileType (const OSGSceneFileType &obj )
	: _suffixList(obj._suffixList)
{
	SWARNING << "In OSGSceneFileType copy constructor" << endl;
}

//--------------------------------------------------------
// Function name: ~OSGSceneFileType
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
OSGSceneFileType::~OSGSceneFileType (void )
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
void OSGSceneFileType::print(void)
{
	list<OSGString>::iterator sI;

	SDEBUG << getName();

	if (_suffixList.empty())
		osgLog() << "NONE";
	else
		for (sI = _suffixList.begin(); sI != _suffixList.end(); sI++) 
			osgLog().stream(OSG::LOG_DEBUG) << sI->str() << " ";

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


