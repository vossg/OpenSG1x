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

#ifndef OSGMTDIMAGEFILETYPE_CLASS_DECLARATION
#define OSGMTDIMAGEFILETYPE_CLASS_DECLARATION
#ifdef  __sig
#pragma  once
#endif

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGImageFileType.h>

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING MTDImageFileType : public ImageFileType
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~MTDImageFileType (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Get Methods                                 */
    /*! \{                                                                 */

    virtual MTDImageFileType & the        (void) { return _the; }

    virtual const Char8      *getMimeType (void) { return "MTD"; }

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

    MTDImageFileType ( const Char8 *suffixArray[], UInt16 suffixByteCount );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Copy Constructor                              */
    /*! \{                                                                 */

    MTDImageFileType (const MTDImageFileType &obj);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Buffer                                   */
    /*! \{                                                                 */

    virtual UInt64 restoreData ( Image &image, const UChar8 *buffer,
                                 Int32 memSize = -1 );

    virtual UInt64 storeData   ( const Image &image, UChar8 *buffer,
                                 Int32 memSize = -1 );
    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    typedef ImageFileType Inherited;

    static  MTDImageFileType _the;
};

typedef MTDImageFileType* MTDImageFileTypeP;

OSG_END_NAMESPACE

#endif // OSGMTDIMAGEFILETYPE_CLASS_DECLARATION
