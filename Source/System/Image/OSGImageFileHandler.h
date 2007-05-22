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
#include <iosfwd>


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

    virtual ImagePtr read  ( std::istream &is, const std::string &mimeType);

    virtual bool     read  ( ImagePtr &image,
                             std::istream &is, const std::string &mimeType);

    virtual bool    write ( const ImagePtr &image,
                            std::ostream &os, const std::string &mimeType);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read Callback                              */
    /*! \{                                                                 */

    typedef ImagePtr (*readcbfp) (const char *fileName, const char *mimeType);
    void setReadCB(readcbfp fp);
    readcbfp getReadCB(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   PathHandler                                */
    /*! \{                                                                 */

    virtual PathHandler* getPathHandler(void                     );
    virtual void         setPathHandler(PathHandler *pPathHandler);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Options                                    */
    /*! \{                                                                 */

    virtual bool               setOptions(const Char8 *suffix, const Char8 *options);
    virtual const Char8        *getOptions(const Char8 *suffix);

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
                                     const char *fileName = 0,
                                     bool validateHeader = false);

    ImageFileType * getDefaultType (void);

    virtual int getSuffixList(std::list<const Char8*> & suffixList,
                            UInt32 flags = ImageFileType::OSG_READ_SUPPORTED |
                                           ImageFileType::OSG_WRITE_SUPPORTED);

    std::string determineMimetypeFromName(const std::string &fileName);

    std::string determineMimetypeFromSuffix(const std::string &suffix);

    std::string determineMimetypeFromStream(std::istream &is);

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

    std::map<std::string, ImageFileType *>  _suffixTypeMap;

    typedef std::map<std::string, ImageFileType*> TypeMap;

    TypeMap _typeMap;

    static bool addImageFileType (ImageFileType &fileType);

    static void normalizeMimetype(std::string &mimetype);

    static void normalizeSuffix(std::string &suffix);

    PathHandler* _pPathHandler;
    readcbfp _readFP;

    static const std::string _fileNameKey;

    static const std::string _fullFilePathKey;

    /*---------------------------------------------------------------------*/
    /*! \name               Constructor                                    */
    /*! \{                                                                 */

    ImageFileHandler (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Copy Constructor                               */
    /*! \{                                                                 */

    ImageFileHandler(const ImageFileHandler &obj);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Copy Operator                                  */
    /*! \{                                                                 */

    const ImageFileHandler & operator= (const ImageFileHandler &obj);

    /*! \}                                                                 */
};

typedef ImageFileHandler* ImageFileHandlerP;

OSG_END_NAMESPACE

#endif // OSGIMAGEFILEHANDLER_CLASS_DECLARATION
