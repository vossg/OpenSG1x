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

#ifndef OSGJPGIMAGEFILETYPE_CLASS_DECLARATION
#define OSGJPGIMAGEFILETYPE_CLASS_DECLARATION
#ifdef  __sgi
#pragma  once 
#endif 


//------------------------------
//Includes
//-------------------------------


#include <OSGBaseTypes.h>

#include "OSGImageFileType.h"


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


class OSG_DLLEXPORT JPGImageFileType : public ImageFileType
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
  virtual ~JPGImageFileType (void);

  /** get method for attribute minormagic, -1 => no minor magic code */
  virtual Int16 getMinorMagic (void);

  /** get method for attribute majormagic, -1 => no minor magic code */
  virtual Int16 getMajorMagic (void);

  /** get method for the type name */
  virtual const char *getName (void) { return "JPG IMAGE"; }

  /** read the the image from the given filename */
  virtual bool read (Image &image, const char *fileName);

  /** write the the image to the given filename */
  virtual bool write (const Image &image, const char *fileName);

  /** get method for attribute the */
  JPGImageFileType & the (void) { return _the; }


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
  JPGImageFileType ( const char *suffixArray[], UInt16 suffixByteCount,
												Int16 majorMagic, Int16 minorMagic);

  /** Copy Constructor */
  JPGImageFileType (const JPGImageFileType &obj);

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

	typedef ImageFileType Inherited;

  /**  */
  static JPGImageFileType _the;

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

typedef JPGImageFileType* JPGImageFileTypeP;

OSG_END_NAMESPACE

#endif // OSGJPGIMAGEFILETYPE_CLASS_DECLARATION
