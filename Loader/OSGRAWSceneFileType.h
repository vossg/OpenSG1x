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


#ifndef _OSGRAWSCENEFILETYPE_H_
#define _OSGRAWSCENEFILETYPE_H_
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


class OSGRAWSceneFileType : public OSGSceneFileType 
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
	virtual ~OSGRAWSceneFileType (void);

  /** get method for attribute the */
  virtual OSGRAWSceneFileType & the (void) { return _the; }

#ifdef WIN32
  static  OSGRAWSceneFileType & staticThe (void) { return _the; }
#endif

  /** read the image from the given file */
  virtual OSGNodePtr read (const char *fileName) const;

  /** write the image to the given file */
  virtual bool write (const OSGNodePtr node, const char *fileName) const;

  /** get method for the type name */
  virtual const char *getName (void) const { return "RAW GEOMETRY"; }

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
  OSGRAWSceneFileType ( const char *suffixArray[], 
												OSGUInt16 suffixByteCount );

  /** Copy Constructor */
  OSGRAWSceneFileType (const OSGRAWSceneFileType &obj);

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


	typedef OSGSceneFileType Inherited;


  /**  */
  static OSGRAWSceneFileType _the;

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

typedef OSGRAWSceneFileType* OSGRAWSceneFileTypeP;

OSG_END_NAMESPACE

#endif // _OSGRAWSCENEFILETYPE_H_
