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

#ifndef _OSGOFFSCENEFILETYPE_H_
#define _OSGOFFSCENEFILETYPE_H_
#ifdef  __sig
#pragma  once 
#endif 


//------------------------------
//Includes
//-------------------------------

#include <OSGBaseTypes.h>

#include "OSGSceneFileType.h"

OSG_BEGIN_NAMESPACE

//------------------------------
//Forward References						 
//------------------------------


//------------------------------
//Types												 
//------------------------------


//------------------------------
//Class												 
//------------------------------


class OSG_SYSTEMLIB_DLLMAPPING OFFSceneFileType : public SceneFileType 
{

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
	virtual ~OFFSceneFileType (void);

    /** get method for attribute the */
    virtual OFFSceneFileType & the (void) { return _the; }

#if defined(__linux) || ( defined(WIN32) && ! defined(OSG_BUILD_DLL) )
    static  OFFSceneFileType & staticThe (void) { return _the; }
#endif

    /** read the model from the given file */
    virtual NodePtr read(const Char8 *fileName, UInt32 uiOptions) const;

    /** write the model to the given file */
    virtual Bool write (const NodePtr node, const char *fileName) const;

    /** get method for the type name */
    virtual const char *getName (void) const { return "OFF GEOMETRY"; }

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
    OFFSceneFileType ( const char *suffixArray[], 
                       UInt16 suffixByteCount );

    /** Copy Constructor */
    OFFSceneFileType (const OFFSceneFileType &obj);

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


	typedef SceneFileType Inherited;


    /**  */
    static OFFSceneFileType _the;

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


//------------------------------
//instance functions  				  
//------------------------------


};

typedef OFFSceneFileType* OFFSceneFileTypeP;

OSG_END_NAMESPACE

#endif // _OSGOFFSCENEFILETYPE_H_
