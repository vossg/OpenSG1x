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

#ifndef _OSGSCENEFILEHANDLER_H_
#define _OSGSCENEFILEHANDLER_H_
#ifdef  __sgi
#pragma  once 
#endif 


//------------------------------
//Includes
//-------------------------------

#include <list>
#include <map>

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGStringLink.h>
#include <OSGSceneFileType.h>

//------------------------------
//Forward References						 
//------------------------------


//------------------------------
//Types												 
//------------------------------


//------------------------------
//Class												 
//------------------------------

OSG_BEGIN_NAMESPACE


class OSG_SYSTEMLIB_DLLMAPPING SceneFileHandler {

	friend class OSG_SYSTEMLIB_DLLMAPPING SceneFileType;
		
public:

//----------------------------
//enums    		 							 
//----------------------------


//----------------------------
//types    		 						   
//----------------------------


//---------------------------
//class functions 	   		   
//---------------------------


  /** Destructor */
  virtual ~SceneFileHandler (void);

  /** get file type */
  virtual SceneFileType * getFileType ( const char *fileName );

  /**  read image*/
  virtual NodePtr read (const Char8 *fileName, UInt32 uiOptions);

  /** write image  */
  virtual Bool write (const NodePtr node, const char *fileName);

  /** print debug info to cerr */
  void print (void);

  /** get method for attribute the */
  static SceneFileHandler & the (void) { return *_the; }

protected:

//------------------------------
//enums    		 								 
//------------------------------


//------------------------------
//types    		 								 
//------------------------------


//---------------------------
//class Variables 			     
//---------------------------


//---------------------------
//class functions 			     
//---------------------------


  /** Default Constructor */
  SceneFileHandler (void);

  /** Copy Constructor */
  SceneFileHandler (const SceneFileHandler &obj);

//-----------------------------
//instance Variables  		     
//-----------------------------


//-----------------------------
//instance functions  	       
//-----------------------------


private:

//----------------------------------
//enums    		 										 
//----------------------------------


//----------------------------------
//types    		 										 
//----------------------------------


  /**  */
  static SceneFileHandler * _the;

  /**  */
  map < String, SceneFileType *>  _suffixTypeMap;

//-------------------------------
//friend Classes      	  	     
//-------------------------------


//-------------------------------
//friend functions 	   			     
//-------------------------------


//-------------------------------
//class Variables	   				     
//-------------------------------


//-------------------------------
//class functions 	   		       
//-------------------------------

//------------------------------
//instance Variables  				  
//------------------------------

  /**  */
  static Bool addSceneFileType (SceneFileType &fileType);


//------------------------------
//instance functions  				  
//------------------------------


};

typedef SceneFileHandler* SceneFileHandlerP;

OSG_END_NAMESPACE

#endif // OSGIMAGEFILEHANDLER_CLASS_DECLARATION
