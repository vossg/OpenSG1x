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


#ifndef OSGPNMIMAGEFILETYPE_CLASS_DECLARATION
#define OSGPNMIMAGEFILETYPE_CLASS_DECLARATION
#ifdef  __sig
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


class OSGPNMImageFileType : public OSGImageFileType 
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
	virtual ~OSGPNMImageFileType (void);

  /** get method for attribute the */
  virtual OSGPNMImageFileType & the (void) { return _the; }

  /** get method for the attribute majorMagic */
  virtual OSGInt16 getMajorMagic (void);

  /** get method for the attribute minorMagic */
  virtual OSGInt16 getMinorMagic (void);

  /** read the image from the given file */
  virtual bool read (OSGImage &image, const char *fileName);

  /** write the image to the given file */
  virtual bool write (const OSGImage &image, const char *fileName);

  /** get method for the type name */
  virtual const char *getName (void) { return "PNG IMAGE"; }

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
  OSGPNMImageFileType ( const char *suffixArray[], 
												OSGUInt16 suffixByteCount, 
												OSGInt16 majorMagic, OSGInt16 minorMagic);

  /** Copy Constructor */
  OSGPNMImageFileType (const OSGPNMImageFileType &obj);

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
  static OSGPNMImageFileType _the;

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

typedef OSGPNMImageFileType* OSGPNMImageFileTypeP;

OSG_END_NAMESPACE

#endif // OSGPNMIMAGEFILETYPE_CLASS_DECLARATION
