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
#include <OSGIDString.h>
#include <OSGImage.h>

OSG_BEGIN_NAMESPACE

/** .
*
*
* @author jbehr, Tue Apr 11 15:32:43 2000
*/


class OSG_SYSTEMLIB_DLLMAPPING ImageFileType {

    /*==========================  PRIVATE  ================================*/
  private:

    list<IDString> _suffixList;

    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   MTD Header                                 */
    /*! \{                                                                 */

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

    bool netToHost (void);
    bool hostToNet (void);

    };

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                Default Constructor                           */
    /*! \{                                                                 */

    ImageFileType ( const Char8 * suffixArray[], UInt16 suffixByteCount );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Copy Constructor                              */
    /*! \{                                                                 */

    ImageFileType ( const ImageFileType &obj);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Buffer                                   */
    /*! \{                                                                 */

    virtual UInt64 restoreData ( Image &image, const UChar8 *buffer,
                                 Int32 memSize = -1 );

    virtual UInt64 storeData   ( const Image &image, UChar8 *buffer,
                                 Int32 memSize = -1 );

    /*! \}                                                                 */

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ImageFileType (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Get  Methods                              */
    /*! \{                                                                 */

    virtual const Char8  *getMimeType (void) = 0;

    virtual list<IDString> & suffixList (void) { return _suffixList; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    virtual bool read  (Image &image, const Char8 *fileName )       = 0;

    virtual bool write (const Image &image, const Char8 *fileName ) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Buffer                                   */
    /*! \{                                                                 */

    static  UInt64 restore       ( Image &image, const UChar8 *buffer,
                                   Int32 memSize = -1 );

    static  UInt64 store         ( const Image &image, const char *mimeType,
                                   UChar8 *buffer, Int32 memSize = -1 );

            UInt64  store        ( const Image &image, UChar8 *buffer,
                                   Int32 memSize = -1 );

    virtual UInt64 maxBufferSize (const Image &image );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Print                                  */
    /*! \{                                                                 */

    void print(void);

    /*! \}                                                                 */

};

typedef ImageFileType* ImageFileTypeP;

OSG_END_NAMESPACE

#endif // OSGIMAGEFILETYPE_CLASS_DECLARATION
