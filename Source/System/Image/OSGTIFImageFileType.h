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

#ifndef OSGTIFIMAGEFILETYPE_CLASS_DECLARATION
#define OSGTIFIMAGEFILETYPE_CLASS_DECLARATION
#ifdef  __sig
#pragma  once
#endif

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGImageFileType.h>

OSG_BEGIN_NAMESPACE

/*! \brief TIFF File Handler. Used to read/write TIFF files.
See \ref PageSystemImage for a detailed description.
*/

class OSG_SYSTEMLIB_DLLMAPPING TIFImageFileType : public ImageFileType
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~TIFImageFileType (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Get Method                                  */
    /*! \{                                                                 */

    virtual TIFImageFileType the          (void) { return _the; }

    virtual const Char8      *getMimeType (void) { return "TIFF"; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    virtual bool read  (Image &image, const Char8 *fileName);

    virtual bool write (const Image &image, const Char8 *fileName);

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name               Default Constructor                            */
    /*! \{                                                                 */

    TIFImageFileType (const Char8 *suffixArray[], UInt16 suffixByteCount );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Copy Constructor                              */
    /*! \{                                                                 */

    TIFImageFileType (const TIFImageFileType &obj);

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    typedef ImageFileType Inherited;

    static TIFImageFileType _the;

};

typedef TIFImageFileType* TIFImageFileTypeP;

OSG_END_NAMESPACE

#endif // OSGTIFIMAGEFILETYPE_CLASS_DECLARATION
