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

#ifndef OSGIMAGEFILEHANDLER_CLASS_DECLARATION
#define OSGIMAGEFILEHANDLER_CLASS_DECLARATION
#ifdef  __sgi
#pragma  once
#endif

#include <list>
#include <map>

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGIDStringLink.h>
#include <OSGImageFileType.h>


OSG_BEGIN_NAMESPACE

class PathHandler;

/*! \brief Image file Handler. Used to read/write and store/restore image data.
See \ref PageSystemImage for a detailed description.
*/

class OSG_SYSTEMLIB_DLLMAPPING ImageFileHandler {

    friend class ImageFileType;

    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ImageFileHandler (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read/Write                                 */
    /*! \{                                                                 */

    virtual ImagePtr read  ( const char *fileName, const char *mimeType = 0);

    virtual bool     read  ( ImagePtr &image,
                             const char *fileName, const char *mimeType = 0);

    virtual bool    write ( const ImagePtr &image,
                            const char *fileName, const char *mimeType = 0);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   PathHandler                                */
    /*! \{                                                                 */

    virtual PathHandler* getPathHandler(void                     );
    virtual void         setPathHandler(PathHandler *pPathHandler);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Storage                                  */
    /*! \{                                                                 */

    virtual UInt64 restore ( ImagePtr &image,
                             const UChar8 *buffer, Int32 memSize = -1 );

    virtual UInt64 store   ( const ImagePtr &image, const char *mimeType,
                             UChar8 *buffer, Int32 memSize = -1 );

    virtual UChar8* store  ( const ImagePtr &image, UInt64 &memSize,
                             const char *mimeType = 0);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Get Types                                  */
    /*! \{                                                                 */

    ImageFileType * getFileType    ( const char *mimeType,
                                     const char *fileName = 0 );

    ImageFileType * getDefaultType (void);

    virtual int getSuffixList(std::list<const Char8*> & suffixList,
                            UInt32 flags = ImageFileType::OSG_READ_SUPPORTED |
                                           ImageFileType::OSG_WRITE_SUPPORTED);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Print                                     */
    /*! \{                                                                 */

    void dump (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Get Method                                  */
    /*! \{                                                                 */

    static ImageFileHandler & the (void);

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:

    /*==========================  PRIVATE  ================================*/
private:

    static ImageFileHandler             *_the;

    std::map<IDString, ImageFileType *>  _suffixTypeMap;

    static bool addImageFileType (ImageFileType &fileType);

    PathHandler* _pPathHandler;

    static const std::string _fileNameKey;

    static const std::string _fullFilePathKey;

    /*---------------------------------------------------------------------*/
    /*! \name               Constructor                                    */
    /*! \{                                                                 */

    ImageFileHandler (void);
    ImageFileHandler(const ImageFileHandler &obj);

    /*! \}                                                                 */
};

typedef ImageFileHandler* ImageFileHandlerP;

OSG_END_NAMESPACE

#endif // OSGIMAGEFILEHANDLER_CLASS_DECLARATION
