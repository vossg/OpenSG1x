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

#include<OSGBaseTypes.h>

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


class OSGSceneFileHandler {

	friend class OSGSceneFileType;
		
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
  virtual ~OSGSceneFileHandler (void);

  /** get file type */
  virtual OSGSceneFileType * getFileType ( const char *fileName );

  /**  read image*/
  virtual OSGNodePtr read (const char *fileName);

  /** write image  */
  virtual bool write (const OSGNodePtr node, const char *fileName);

  /** print debug info to cerr */
  void print (void);

  /** get method for attribute the */
  static OSGSceneFileHandler & the (void) { return *_the; }

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
  OSGSceneFileHandler (void);

  /** Copy Constructor */
  OSGSceneFileHandler (const OSGSceneFileHandler &obj);

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
  static OSGSceneFileHandler * _the;

  /**  */
  map < OSGString, OSGSceneFileType *>  _suffixTypeMap;

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
  static bool addSceneFileType (OSGSceneFileType &fileType);


//------------------------------
//instance functions  				  
//------------------------------


};

typedef OSGSceneFileHandler* OSGSceneFileHandlerP;

OSG_END_NAMESPACE

#endif // OSGIMAGEFILEHANDLER_CLASS_DECLARATION
