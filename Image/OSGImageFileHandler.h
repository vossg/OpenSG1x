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

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
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


class OSG_SYSTEMLIB_DLLMAPPING ImageFileHandler {

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

	/** read image */
	virtual Image * read ( const char *fileName, const char *mimeType = 0);

  /**  read image */
  virtual bool read ( Image &image, 
                      const char *fileName, const char *mimeType = 0);

  /** write image  */
  virtual bool write (const Image &image, 
                      const char *fileName, const char *mimeType = 0
                      );

  /** fill the given image with the content of the mem 'buffer' */
  virtual UInt64 restore ( Image &image,
                           const UChar8 *buffer, UInt32 memSize = -1 );

  /** store the given image to the mem 'buffer' */
  virtual UInt64 store ( const Image &image, const char *mimeType,
                         UChar8 *buffer, UInt32 memSize = -1 );

  /** store the given image, mem is automatic allocated, the user has
      to 'delete' the mem, returns the size of the data in 'memSize'  */
  virtual UChar8* store ( const Image &image, UInt64 &memSize,
                          const char *mimeType = 0);

  /** get file type */
  virtual ImageFileType * getFileType ( const char *mimeType,
                                        const char *fileName = 0 );
                      
  /** get the system default type */
  virtual ImageFileType *getDefaultType (void);
                                        
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

//------------------------------
//instance functions  				  
//------------------------------


};

typedef ImageFileHandler* ImageFileHandlerP;

OSG_END_NAMESPACE

#endif // OSGIMAGEFILEHANDLER_CLASS_DECLARATION
