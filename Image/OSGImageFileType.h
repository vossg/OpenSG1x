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

#ifndef OSGIMAGEFILETYPE_CLASS_DECLARATION
#define OSGIMAGEFILETYPE_CLASS_DECLARATION

#include <list>

#include <OSGBaseTypes.h>
#include <OSGString.h>
#include <OSGImage.h>

OSG_BEGIN_NAMESPACE

/** .
*
*
* @author jbehr, Tue Apr 11 15:32:43 2000
*/


class OSG_IMAGE_DLLMAPPING ImageFileType {

private:

  /**  */
  list<String> _suffixList;

	/**  */
	Int16 _majorMagic;

	/**  */
	Int16 _minorMagic;

protected:

  /** Default Constructor */
  ImageFileType ( const char * suffixArray[], UInt16 suffixByteCount, 
										 Int16 majorMagic, Int16 minorMagic );

  /** Copy Constructor */
  ImageFileType (const ImageFileType &obj);

public:

  /** Destructor */
  virtual ~ImageFileType (void);

  /** get method for attribute majorMagic, -1 => no major magic code */
  virtual Int16 getMajorMagic (void) { return _majorMagic; }

  /** get method for attribute minorMagic, -1 => no minor magic code */
  virtual Int16 getMinorMagic (void) { return _minorMagic; }

	/** get mathod for the type name */
	virtual const char *getName (void) = 0;

  /** get method for attribute suffixList */
  virtual list<String> & suffixList (void) { return _suffixList; }

  /** fill the given image with the content of the file 'fileName' */
  virtual bool read (Image &image, const char *fileName ) = 0;

  /** write the given image to 'fileName' */
  virtual bool write (const Image &image, const char *fileName ) = 0;

	/** print debug info to cerr */
	void print(void);

};

typedef ImageFileType* ImageFileTypeP;

OSG_END_NAMESPACE

#endif // OSGIMAGEFILETYPE_CLASS_DECLARATION
