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


class OSGJPGImageFileType : public OSGImageFileType
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
  virtual ~OSGJPGImageFileType (void);

  /** get method for attribute minormagic, -1 => no minor magic code */
  virtual OSGInt16 getMinorMagic (void);

  /** get method for attribute majormagic, -1 => no minor magic code */
  virtual OSGInt16 getMajorMagic (void);

  /** get method for the type name */
  virtual const char *getName (void) { return "JPG IMAGE"; }

  /** read the the image from the given filename */
  virtual bool read (OSGImage &image, const char *fileName);

  /** write the the image to the given filename */
  virtual bool write (const OSGImage &image, const char *fileName);

  /** get method for attribute the */
  OSGJPGImageFileType & the (void) { return _the; }


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
  OSGJPGImageFileType ( const char *suffixArray[], OSGUInt16 suffixByteCount,
												OSGInt16 majorMagic, OSGInt16 minorMagic);

  /** Copy Constructor */
  OSGJPGImageFileType (const OSGJPGImageFileType &obj);

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

	typedef OSGImageFileType Inherited;

  /**  */
  static OSGJPGImageFileType _the;

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

typedef OSGJPGImageFileType* OSGJPGImageFileTypeP;

OSG_END_NAMESPACE

#endif // OSGJPGIMAGEFILETYPE_CLASS_DECLARATION
