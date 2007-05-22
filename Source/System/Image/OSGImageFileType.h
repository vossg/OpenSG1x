/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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
#include <iosfwd>

OSG_BEGIN_NAMESPACE

/*! \brief Abstract Base ImageFileType. Defines the Interface for
all concrete ImageFileTypes. See \ref PageSystemImage for detailed description.
*/

class OSG_SYSTEMLIB_DLLMAPPING ImageFileType {


  /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                     Flags                                    */
    /*! \{                                                                 */
  
    enum
    {
        OSG_READ_SUPPORTED = 1,
        OSG_WRITE_SUPPORTED = 2
    };
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ImageFileType (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Set                                        */
    /*! \{                                                                 */
    
    void setOptions(const Char8 *options);

    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Get  Methods                              */
    /*! \{                                                                 */
    
    const Char8  *getMimeType (void) const;

    const std::list<IDString> &getSuffixList(void) const;
    
    virtual UInt32 getFlags(void) const;

    const Char8         *getOptions         (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    virtual bool read  (ImagePtr &image, const Char8 *fileName );

    virtual bool write (const ImagePtr &image, const Char8 *fileName );

    virtual bool validateHeader( const Char8 *fileName, bool &implemented );

    virtual bool read  (ImagePtr &image, std::istream &is, const std::string &mimetype);

    virtual bool write (const ImagePtr &image, std::ostream &os, const std::string &mimetype);

    virtual std::string determineMimetypeFromStream(std::istream &is);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Safe Store/Restore                           */
    /*! \{                                                                 */

    static  UInt64 restore       ( ImagePtr &image, const UChar8 *buffer,
                                   Int32 memSize = -1 );

    static  UInt64 store         ( const ImagePtr &image,
                                   const char *mimeType,
                                   UChar8 *buffer, Int32 memSize = -1 );

    UInt64 store                 ( const ImagePtr &image, UChar8 *buffer,
                                   Int32 memSize = -1 );
    
    virtual UInt64 maxBufferSize ( const ImagePtr &image );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Raw Store/Restore                             */
    /*! \{                                                                 */

    virtual UInt64 restoreData ( ImagePtr &image, const UChar8 *buffer,
                                 Int32 memSize = -1 );

    virtual UInt64 storeData   ( const ImagePtr &image, UChar8 *buffer,
                                 Int32 memSize = -1 );


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       dump                                   */
    /*! \{                                                                 */

    void dump(void);

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   MTD Header                                 */
    /*! \{                                                                 */

    struct Head {
      Char8          suffix[8];
      unsigned short pixelFormat;
      unsigned short width;
      unsigned short height;
      unsigned short depth;
      unsigned short mipmapCount;
      unsigned short frameCount;
      unsigned short frameDelay;
      unsigned short sideCount;
      unsigned short dataType;
      unsigned short _reserved3;
      unsigned short _reserved4;
      unsigned short attachmentSize;

      bool netToHost (void);
      bool hostToNet (void);

    };

    std::string         _options;

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                Default Constructor                           */
    /*! \{                                                                 */

    ImageFileType ( const Char8  *mimeType,
                    const Char8  *suffixArray[], 
                          UInt16  suffixByteCount,
                          UInt32  flags = OSG_READ_SUPPORTED );

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    /*---------------------------------------------------------------------*/
    /*! \name                Copy Constructor                              */
    /*! \{                                                                 */

    ImageFileType (const ImageFileType &obj);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Copy Operator                                 */
    /*! \{                                                                 */

    const ImageFileType & operator= (const ImageFileType &obj);

    /*! \}                                                                 */

    std::list<IDString> _suffixList;

    IDString _mimeType;

    UInt32              _flags;
};

typedef ImageFileType* ImageFileTypeP;

OSG_END_NAMESPACE

#endif // OSGIMAGEFILETYPE_CLASS_DECLARATION
