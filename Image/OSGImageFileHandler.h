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


class OSGImageFileHandler {

	friend class OSGImageFileType;
		
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
  virtual ~OSGImageFileHandler (void);

  /** get file type */
  virtual OSGImageFileType * getFileType (const char *fileName, 
																					bool checkMagic = true);

	/** read image */
	virtual OSGImage * read (const char *fileName);

  /**  read image */
  virtual bool read (OSGImage &image, const char *fileName);

  /** write image  */
  virtual bool write (const OSGImage &image, const char *fileName);

  /** print debug info to cerr */
  void print (void);

  /** get method for attribute the */
  static OSGImageFileHandler & the (void) { return *_the; }

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
  OSGImageFileHandler (void);

  /** Copy Constructor */
  OSGImageFileHandler (const OSGImageFileHandler &obj);

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
  static OSGImageFileHandler * _the;

  /**  */
  typedef map < OSGInt16, OSGImageFileType* > MinorMap;

  /**  */
  map < OSGInt16, MinorMap >  _magicTypeMap ;

  /**  */
  map < OSGString, OSGImageFileType *>  _suffixTypeMap;

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
  static bool addImageFileType (OSGImageFileType &fileType);

  /**  */
  virtual OSGImageFileType * getFileType ( OSGInt16 majorMagic = -1, 
																					 OSGInt16 minorMagic = -1 );

//------------------------------
//instance functions  				  
//------------------------------


};

typedef OSGImageFileHandler* OSGImageFileHandlerP;

OSG_END_NAMESPACE

#endif // OSGIMAGEFILEHANDLER_CLASS_DECLARATION
