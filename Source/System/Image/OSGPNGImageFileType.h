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

#ifndef OSGPNGIMAGEFILETYPE_CLASS_DECLARATION
#define OSGPNGIMAGEFILETYPE_CLASS_DECLARATION
#ifdef  __sgi
#pragma  once
#endif

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGImageFileType.h>
#include <iosfwd>

OSG_BEGIN_NAMESPACE

/*! \brief PNG File Handler. See \ref PageSystemImage for a detailed description.
*/


class OSG_SYSTEMLIB_DLLMAPPING PNGImageFileType : public ImageFileType
{

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~PNGImageFileType (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    virtual bool validateHeader( const Char8 *fileName, bool &implemented);

    virtual bool read (ImagePtr &image, std::istream &is, const std::string &mimetype);

    virtual bool write (const ImagePtr &image, std::ostream &os, const std::string &mimetype);

    virtual std::string determineMimetypeFromStream(std::istream &is);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Buffer                                   */
    /*! \{                                                                 */

    virtual UInt64 restoreData ( ImagePtr &image, const UChar8 *buffer,
                                 Int32 memSize = -1 );

    virtual UInt64 storeData   ( const ImagePtr &image, UChar8 *buffer,
                                 Int32 memSize = -1 );
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Get Method                                  */
    /*! \{                                                                 */

    static PNGImageFileType & the (void);

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name               Default Constructor                            */
    /*! \{                                                                 */

    PNGImageFileType ( const Char8 *mimeType,
                       const Char8 *suffixArray[], UInt16 suffixByteCount,
                       UInt32 flags );

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    /*---------------------------------------------------------------------*/
    /*! \name                Copy Constructor                              */
    /*! \{                                                                 */

    PNGImageFileType (const PNGImageFileType &obj);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Copy Operator                                 */
    /*! \{                                                                 */

    const PNGImageFileType & operator= (const PNGImageFileType &obj);

    /*! \}                                                                 */

    static PNGImageFileType _the;

};

typedef PNGImageFileType* PNGImageFileTypeP;

OSG_END_NAMESPACE

#endif // OSGPNGIMAGEFILETYPE_CLASS_DECLARATION
