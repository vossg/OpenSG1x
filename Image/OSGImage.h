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


#ifndef OSGIMAGE_CLASS_DECLARATION
#define OSGIMAGE_CLASS_DECLARATION

#ifdef  __sgi
#pragma  once 
#endif 


//------------------------------
//Includes
//-------------------------------

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILESTATE
#       define OSG_IMAGE_DLLMAPPING     __declspec(dllexport)
#       define OSG_IMAGE_DLLTMPLMAPPING
#   else
#       define OSG_IMAGE_DLLMAPPING     __declspec(dllimport)
#       define OSG_IMAGE_DLLTMPLMAPPING __declspec(dllimport)
#   endif
#else
#define OSG_IMAGE_DLLMAPPING
#define OSG_IMAGE_DLLTMPLMAPPING
#endif

#ifdef WIN32
#include <windows.h>
#endif

extern "C" {
#include <GL/gl.h>
}

#include <OSGTime.h>
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


class OSG_IMAGE_DLLMAPPING Image {

public:

//----------------------------
//enums    		 							 
//----------------------------

	enum PixelFormat { 	OSG_INVALID_PF = 0,
											OSG_L_PF       = GL_LUMINANCE,
											OSG_LA_PF      = GL_LUMINANCE_ALPHA,
											OSG_RGB_PF     = GL_RGB,
											OSG_RGBA_PF    = GL_RGBA
	};		

//----------------------------
//types    		 						   
//----------------------------


//---------------------------
// functions 	   		   
//---------------------------


  /** Default Constructor */
  Image (void);

  /** Copy Constructor */
  Image (const Image &obj, Bool copyData);

  /** Destructor */
  virtual ~Image (void);

  /** construktor */
  Image ( PixelFormat pixelFormat, 
					Int32 width, Int32 height = 1, Int32 depth = 1, 
					Int32 mipmapCount = 1, 
					Int32 frameCount = 1, Time frameDelay = 0.0,
					UChar8 *data = 0);

  /** set methode wich sets the image data */
  Bool set ( PixelFormat pixelFormat,
						 Int32 width, Int32 height = 1, Int32 depth = 1, 
						 Int32 mipmapCount = 1, 
						 Int32 frameCount = 1, Time frameDelay = 0.0,
						 UChar8 *data = 0);

  /** reformate the image to the given pixelFormat */
  Bool reformat ( PixelFormat pixelFormat, Image *destination = 0);

  /** scale the image to the given dimension */
  Bool scale ( Int32 width, Int32 height = 1, Int32 depth = 1, 
							 Image *destination = 0);

	/** create mipmap, level == -1 will create all maipmaps until 1x1 */
	Bool createMipmap ( Int32 level );

  /** methode to write the image data to the given File */
  Bool write (const Char8 *fileName);

  /** methode to read the image data from the given File */
  Bool read (const Char8 *fileName);

  /** Equality comparison operator */
  Bool operator == (const Image &image);

  /** lower comparison operator */
  Bool operator < (const Image &image);

  /** get method for attribute dimension */
  Int32 dimension (void) const { return _dimension; }

  /** get method for attribute width */
  Int32 getWidth (void) const { return _width; }

  /** get method for attribute height */
  Int32 getHeight (void) const { return _height; }

  /** get method for attribute depth */
  Int32 getDepth (void) const { return _depth; }

  /** get method for attribute bpp */
	UChar8 getBpp (void) const { return _bpp; }

  /** get method for attribute pixelFormat */
	PixelFormat getPixelFormat (void) const { return _pixelFormat; }

  /** get the size of used mem */
  inline unsigned long getSize ( Bool withMipmap = true, 
																 Bool withFrames = true) const
		{ return  (calcMipmapSumSize((withMipmap ? _mipmapCount : 0)) *
				      (withFrames ? _frameCount : 1) * _bpp);
		}

  /** get method for attribute data */
  inline UChar8 *getData ( UInt32 mipmapNum = 0, UInt32 frameNum = 0) const
		{
			UChar8 *data = _data;

			if (frameNum) 
				data += _frameSize * _bpp;

			if (mipmapNum) 
				data += calcMipmapSumSize(mipmapNum - 1);

			return data;
		}

	/** calculate mipmap geometry */
	void calcMipmapGeometry ( Int32 mipmapNum,
														Int32 &width, Int32 &height, Int32 &depth )
		{
			width  = _width >> mipmapNum;
			height = _height >> mipmapNum;
			depth  = _depth >> mipmapNum;
		}

  /** get method for attribute data */
  inline UChar8 *getDataByTime ( Time time, UInt32 mipmapNum = 1) 
		{ 
			return _data; 
		}	

  /** clears the image (sets all pixel to pixelValue) */
  virtual void clear (UChar8 pixelValue = 0);

protected:

//------------------------------
//enums    		 								 
//------------------------------


//------------------------------
//types    		 								 
//------------------------------

	/** pixelFormat/bpp map */
	static Int32 _formatMap[][2];

  /** PixelFormat */
	PixelFormat _pixelFormat;

  /** image width */
  Int32 _width;

  /** image height */
  Int32 _height;

  /** image depth */
  Int32 _depth;

	/** number of mipmaps */
	Int32 _mipmapCount;

	/** number of frames */
	Int32 _frameCount;

	/** frame delay */
	Time _frameDelay;

  /** byte per pixel */
	UChar8 _bpp;

  /** image dimension ( 0= unvalid 1,2 or 3 is valid ) */
  Int32 _dimension;

	/** frame size with all mipmaps in pixel, not byte */
	Int32 _frameSize;
	
  /** image data, can be NULL */
	UChar8 * _data;

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

	/** calculate the mipmap Size in pixel */
	UInt32 calcMipmapSize ( UInt32 mipmapNum, 
												  UInt32 w, UInt32 h, UInt32 d) const
		{
			w >>= mipmapNum;
			h >>= mipmapNum;
			d >>= mipmapNum;
			
			return (w?w:1) * (h?h:1) * (d?d:1);
		}

	/** calculate the mipmap Size in pixel */
	UInt32 calcMipmapSize (UInt32 mipmapNum) const
		{
			return calcMipmapSize(mipmapNum,_width,_height,_depth);
		}

	/** calculate the size of all mipmaps until mipmapNum */
	UInt32 calcMipmapSumSize ( UInt32 mipmapNum, 
														 UInt32 w, UInt32 h, UInt32 d) const
		{
			Int32 sum = w * h * d;

			while (mipmapNum--) {
				w >>= 1;
				h >>= 1;
				d >>= 1;
				sum += (w?w:1) * (h?h:1) * (d?d:1);
			}

			return sum;
		}

	/** calculate the size of all mipmaps until mipmapNum */
	UInt32 calcMipmapSumSize (UInt32 mipmapNum) const
		{
			return calcMipmapSumSize(mipmapNum,_width,_height,_depth);
		}

  /** Internal method to alloc and copy the image data */
  Bool createData (const UChar8 *data);

	/** Internal medhot to copy&scale image data */
	Bool scaleData ( UChar8* srcData, Int32 srcW, Int32 srcH, Int32 srcD,
									 UChar8* destData, Int32 destW, Int32 destH, Int32 destD );
};

typedef Image* ImageP;

OSG_END_NAMESPACE

#endif // OSGIMAGE_CLASS_DECLARATION
