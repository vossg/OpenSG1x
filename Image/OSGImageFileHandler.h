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

    virtual Image * read  ( const char *fileName, const char *mimeType = 0);

    virtual Bool    read  ( Image &image,
                            const char *fileName, const char *mimeType = 0);

    virtual Bool    write ( const Image &image,
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

    virtual UInt64 restore ( Image &image,
                             const UChar8 *buffer, UInt32 memSize = -1 );

    virtual UInt64 store   ( const Image &image, const char *mimeType,
                             UChar8 *buffer, UInt32 memSize = -1 );

    virtual UChar8* store  ( const Image &image, UInt64 &memSize,
                             const char *mimeType = 0);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Get Types                                  */
    /*! \{                                                                 */

    virtual ImageFileType * getFileType    ( const char *mimeType,
                                             const char *fileName = 0 );

    virtual ImageFileType * getDefaultType (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Print                                     */
    /*! \{                                                                 */

    void print (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Get Method                                  */
    /*! \{                                                                 */

    static ImageFileHandler & the (void) { return *_the; }

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name               Default Constructor                            */
    /*! \{                                                                 */

    ImageFileHandler (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Copy Constructor                              */
    /*! \{                                                                 */

    ImageFileHandler (const ImageFileHandler &obj);

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
private:

    static ImageFileHandler            *_the;

    map    <IDString, ImageFileType *>  _suffixTypeMap;

    static Bool addImageFileType (ImageFileType &fileType);
    
    PathHandler* _pPathHandler;

};

typedef ImageFileHandler* ImageFileHandlerP;

OSG_END_NAMESPACE

#endif // OSGIMAGEFILEHANDLER_CLASS_DECLARATION
