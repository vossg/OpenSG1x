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

#ifndef OSGDATIMAGEFILETYPE_CLASS_DECLARATION
#define OSGDATIMAGEFILETYPE_CLASS_DECLARATION
#ifdef  __sgi
#pragma  once
#endif

#include "OSGSystemDef.h"
#include "OSGBaseTypes.h"
#include "OSGImageFileType.h"

OSG_BEGIN_NAMESPACE

/*! \brief DAT File Handler. Used to read/write DAT/RAW files.
See \ref PageSystemImage for a detailed description.
*/

class OSG_SYSTEMLIB_DLLMAPPING DATImageFileType : public ImageFileType
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~DATImageFileType (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Get Methods                                 */
    /*! \{                                                                 */

    static DATImageFileType& the (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    virtual bool read  (ImagePtr &image, const Char8 *fileName);

    virtual bool write (const ImagePtr &image, const Char8 *fileName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Buffer                                   */
    /*! \{                                                                 */

    virtual UInt64 restoreData ( ImagePtr &image, const UChar8 *buffer,
                                 Int32 memSize = -1 );

    virtual UInt64 storeData   ( const ImagePtr &image, UChar8 *buffer,
                                 Int32 memSize = -1 );
    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name               Default Constructor                            */
    /*! \{                                                                 */

    DATImageFileType ( const Char8 *mimeType,
                       const Char8 *suffixArray[], UInt16 suffixByteCount );

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    /*---------------------------------------------------------------------*/
    /*! \name                Copy Constructor                              */
    /*! \{                                                                 */

    DATImageFileType (const DATImageFileType &obj);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Copy Operator                                 */
    /*! \{                                                                 */

    const DATImageFileType & operator= (const DATImageFileType &obj);

    /*! \}                                                                 */

    static DATImageFileType _the;

    enum KeyType 
    { 
      UNKNOWN_KT = 0,

      OBJECT_FILE_NAME_KT,
      RESOLUTION_KT,
      SLICE_THICKNESS_KT,
      FORMAT_KT,
      FILE_OFFSET_KT,
      CHANNEL_KT,
      ENDIAN_KT
    };

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
          
    /*! \hideinhierarchy */

    struct FormatDesc 
    {
      bool               needConversion;
      //FormatType         type;
      Image::Type        type;
      UInt32             bpv;
      Image::PixelFormat pixelFormat;
    };
    
#endif
        
    static std::map<std::string, KeyType>    _keyStrMap;
    static std::map<std::string, FormatDesc> _formatStrMap;

    static void initTypeMap(void);
};

typedef DATImageFileType* DATImageFileTypeP;

OSG_END_NAMESPACE

#endif // OSGDATIMAGEFILETYPE_CLASS_DECLARATION
