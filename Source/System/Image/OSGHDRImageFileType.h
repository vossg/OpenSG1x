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

#ifndef OSGHDRIMAGEFILETYPE
#define OSGHDRIMAGEFILETYPE
#ifdef  __sig
#pragma  once
#endif

#include "OSGSystemDef.h"

#include "OSGBaseTypes.h"
#include "OSGImageFileType.h"

OSG_BEGIN_NAMESPACE

/*! \brief DAT File Handler. Used to read/write DAT/RAW files.
See \ref PageSystemImage for a detailed description.
*/

class OSG_SYSTEMLIB_DLLMAPPING HDRImageFileType : public ImageFileType
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~HDRImageFileType (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Get Methods                                 */
    /*! \{                                                                 */

    static HDRImageFileType& the (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    virtual bool read  (ImagePtr &image, const Char8 *fileName);

    virtual bool write (const ImagePtr &image, const Char8 *fileName);

    virtual bool read  ( ImagePtr &image,
                         std::istream &is, const std::string &mimeType);

    virtual bool write ( const ImagePtr &image,
                         std::ostream &os, const std::string &mimeType);

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name               Default Constructor                            */
    /*! \{                                                                 */

    HDRImageFileType ( const Char8 *mimeType,
                       const Char8 *suffixArray[], UInt16 suffixByteCount,
                       UInt32 flags );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Buffer                                   */
    /*! \{                                                                 */

    virtual UInt64 restoreData ( ImagePtr &image, const UChar8 *buffer,
                                 Int32 memSize = -1 );

    virtual UInt64 storeData   ( const ImagePtr &image, UChar8 *buffer,
                                 Int32 memSize = -1 );
    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    HDRImageFileType (const HDRImageFileType &obj);

    typedef unsigned char RGBE[4];

    bool checkHDR(FILE *file, int &width, int &height);
    bool checkHDR(std::istream &is, int &width, int &height);

    bool radiance2fp(FILE *file, Real32 *data, int width, int height);
    bool radiance2fp(std::istream &is, Real32 *data, int width, int height);

    bool radiance2fp(FILE *file, Real16 *data, int width, int height);
    bool radiance2fp(std::istream &is, Real16 *data, int width, int height);

    bool freadcolrs(FILE *file, RGBE *scan, int width);
    bool freadcolrs(std::istream &is, RGBE *scan, int width);
    
    bool oldreadcolrs(FILE *file, RGBE *scan, int width);
    
    void RGBE2Float(RGBE rgbe, Real32 *fcol);
    void RGBE2Half( RGBE rgbe, Real16 *fcol);
    
    int fwritecolrs(FILE *file, const Real32 *scan, RGBE *rgbe_scan, int width, int height);
    int fwritecolrs(FILE *file, const Real16 *scan, RGBE *rgbe_scan, int width, int height);

    int fwritecolrs(std::ostream &os, const Real32 *scan, RGBE *rgbe_scan, int width, int height);
    int fwritecolrs(std::ostream &os, const Real16 *scan, RGBE *rgbe_scan, int width, int height);

    int fwriteRGBE( FILE *file, RGBE *rgbe_scan, int width, int height);
    int fwriteRGBE( std::ostream &os, RGBE *rgbe_scan, int width, int height);
    
    void half2RGBE(const Real16 *fcol, RGBE rgbe);
    void float2RGBE(const Real32 *fcol, RGBE rgbe);

    typedef ImageFileType Inherited;

    static  HDRImageFileType _the;

};

typedef HDRImageFileType* HDRImageFileTypeP;

OSG_END_NAMESPACE

#endif // OSGHDRIMAGEFILETYPE
