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


class OSG_SYSTEMLIB_DLLMAPPING ImageFileType {

private:

  /** MTD Header */
  struct Head {
    Char8          mimeType[8];
    unsigned short pixelFormat;
    unsigned short width;
    unsigned short height;
    unsigned short depth;
    unsigned short mipmapCount;
    unsigned short frameCount;
    unsigned short frameDelay;
    unsigned short _reserved1;
    unsigned short _reserved2;
    unsigned short _reserved3;
    unsigned short _reserved4;

    Bool netToHost (void);
    Bool hostToNet (void);

  };     

  /**  */
  list<String> _suffixList;

protected:

  /** Default Constructor */
  ImageFileType ( const Char8 * suffixArray[], UInt16 suffixByteCount );

  /** Copy Constructor */
  ImageFileType ( const ImageFileType &obj);

  /** fill the given image with the content of the mem 'buffer' */
  virtual UInt64 restoreData ( Image &image, const UChar8 *buffer, 
                               Int32 memSize = -1 );

  /** store the given image to the mem 'buffer' */
  virtual UInt64 storeData ( const Image &image, UChar8 *buffer,
                             Int32 memSize = -1 );

public:

  /** Destructor */
  virtual ~ImageFileType (void);

	/** get mathod for the type mimeType */
	virtual const Char8 *getMimeType (void) = 0;

  /** get method for attribute suffixList */
  virtual list<String> & suffixList (void) { return _suffixList; }

  /** fill the given image with the content of the file 'fileName' */
  virtual Bool read (Image &image, const Char8 *fileName ) = 0;

  /** write the given image to 'fileName' */
  virtual Bool write (const Image &image, const Char8 *fileName ) = 0;

  /** fill the given image with the content of the mem 'buffer' */
  static UInt64 restore ( Image &image, const UChar8 *buffer, 
                          Int32 memSize = -1 );

  /** store the given image to the mem 'buffer' */
  static UInt64 store ( const Image &image, const char *mimeType,
                        UChar8 *buffer, Int32 memSize = -1 );

  /** store the given image to the mem 'buffer' */
  UInt64 store ( const Image &image, UChar8 *buffer, Int32 memSize = -1 );

  /** returns the max needed buffer size */ 
  virtual UInt64 maxBufferSize(const Image &image );

	/** print debug info to cerr */
	void print(void);

};

typedef ImageFileType* ImageFileTypeP;

OSG_END_NAMESPACE

#endif // OSGIMAGEFILETYPE_CLASS_DECLARATION
