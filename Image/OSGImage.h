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


#ifndef OSGIMAGE_CLASS_DECLARATION
#define OSGIMAGE_CLASS_DECLARATION
#ifdef  __sgi
#pragma  once 
#endif 


//------------------------------
//Includes
//-------------------------------

#include <OSGString.h>
#include <OSGStringLink.h>
#include <OSGBaseTypes.h>

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


class OSGImage {

public:

//----------------------------
//enums    		 							 
//----------------------------


//----------------------------
//types    		 						   
//----------------------------


//---------------------------
// functions 	   		   
//---------------------------


  /** Default Constructor */
  OSGImage (void);

  /** Copy Constructor */
  OSGImage (const OSGImage &obj, bool copy);

  /** Destructor */
  virtual ~OSGImage (void);

  /** construktor */
  OSGImage (int width, int height, int depth, const char *pixelFormat, 
    	    	unsigned char *data = 0);

  /** construktor */
  OSGImage (int width, int height, const char *pixelFormat, 
    	    	  unsigned char *data = 0);

  /** set methode wich sets the image data */
  bool set (int width, int height, const char *pixelFormat, 
						unsigned char *data = 0);

  /** set methode wich sets the image data */
  bool set (int width, int height, int depth,
						const char *pixelFormat, unsigned char *data = 0);

  /** reformate the image to the given pixelFormat */
  bool reformat (const char *pixelFormat, OSGImage *destination = 0);

  /** scale the image to the given dimension */
  bool scale (int width, int height, int depth =1, OSGImage *destination = 0);

  /** methode to write the image data to the given File */
  bool write (const char *fileName);

  /** methode to read the image data from the given File */
  bool read (const char *fileName);

  /** Equality comparison operator */
  bool operator == (const OSGImage &image);

  /** lower comparison operator */
  bool operator < (const OSGImage &image);

  /** get method for attribute dimension */
  int dimension (void) const { return _dimension; }

  /** get method for attribute width */
  int width (void) const { return _width; }

  /** get method for attribute height */
  int height (void) const { return _height; }

  /** get method for attribute depth */
  int depth (void) const { return _depth; }

  /** get method for attribute pixelDepth */
  unsigned char pixelDepth (void) const { return _pixelDepth; }

  /** get method for attribute pixelFormat */
  const OSGString & pixelFormat (void) const { return _pixelFormat; }

 /// get the size of used mem
  inline unsigned long size(void) const
    { return _width * _height * _depth * _pixelDepth; }     

  /** get method for attribute data */
  inline unsigned char *data (void) { return _data; }

  /** get method for attribute data */
  inline const unsigned char *data (void) const { return _data; }

  /** clears the image (sets all pixel to pixelValue) */
  virtual void clear(unsigned char pixelValue = 128);

protected:

//------------------------------
//enums    		 								 
//------------------------------


//------------------------------
//types    		 								 
//------------------------------


  /** image dimension ( 0= unvalid 1,2 or 3) */
  int _dimension;

  /** image width */
  int _width;

  /** image height */
  int _height;

  /** image depth */
  int _depth;

  /** pixelDepth */
  unsigned char _pixelDepth;

  /** [RGBAL] [0-9] fprmat */
  OSGString _pixelFormat;

  /** image data, can be NULL */
  unsigned char * _data;

//---------------------------
//class Variables 			     
//---------------------------


//---------------------------
//class functions 			     
//---------------------------


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

  /** internal method to alloc and copy the image data */
  bool createData (const unsigned char *data);

};

typedef OSGImage* OSGImageP;

OSG_END_NAMESPACE

#endif // OSGIMAGE_CLASS_DECLARATION
