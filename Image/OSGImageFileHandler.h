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

#ifndef OSGIMAGEFILEHANDLER_CLASS_DECLARATION
#define OSGIMAGEFILEHANDLER_CLASS_DECLARATION
#ifdef  __sgi
#pragma  once 
#endif 


//------------------------------
//Includes
//-------------------------------

#include <list>
#include <map>

#include<OSGBaseTypes.h>

#include <OSGStringLink.h>
#include <OSGImageFileType.h>

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


class OSG_IMAGE_DLLMAPPING ImageFileHandler {

	friend class ImageFileType;
		
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
  virtual ~ImageFileHandler (void);

  /** get file type */
  virtual ImageFileType * getFileType (const char *fileName, 
																					bool checkMagic = true);

	/** read image */
	virtual Image * read (const char *fileName);

  /**  read image */
  virtual bool read (Image &image, const char *fileName);

  /** write image  */
  virtual bool write (const Image &image, const char *fileName);

  /** print debug info to cerr */
  void print (void);

  /** get method for attribute the */
  static ImageFileHandler & the (void) { return *_the; }

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
  ImageFileHandler (void);

  /** Copy Constructor */
  ImageFileHandler (const ImageFileHandler &obj);

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
  static ImageFileHandler * _the;

  /**  */
  typedef map < Int16, ImageFileType* > MinorMap;

  /**  */
  map < Int16, MinorMap >  _magicTypeMap ;

  /**  */
  map < String, ImageFileType *>  _suffixTypeMap;

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
  static bool addImageFileType (ImageFileType &fileType);

  /**  */
  virtual ImageFileType * getFileType ( Int16 majorMagic = -1, 
																					 Int16 minorMagic = -1 );

//------------------------------
//instance functions  				  
//------------------------------


};

typedef ImageFileHandler* ImageFileHandlerP;

OSG_END_NAMESPACE

#endif // OSGIMAGEFILEHANDLER_CLASS_DECLARATION
