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

#ifndef _OSGSCENEFILEHANDLER_H_
#define _OSGSCENEFILEHANDLER_H_
#ifdef  __sgi
#pragma  once
#endif

#include <list>
#include <map>

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGSceneFileType.h>

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING SceneFileHandler
{

    friend class OSG_SYSTEMLIB_DLLMAPPING SceneFileType;

    /*==========================  PUBLIC  =================================*/
  public:

    typedef vector<FieldContainerPtr> FCPtrStore;

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SceneFileHandler (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Get                                        */
    /*! \{                                                                 */

    static  SceneFileHandler &the        (void                 ) 
    {
        return *_the;
    }

    virtual SceneFileType    *getFileType(const Char8 *fileName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read                                       */
    /*! \{                                                                 */

    virtual NodePtr    read        (const  Char8  *fileName,
                                           UInt32  uiOptions = 0);
    virtual FCPtrStore readTopNodes(const  Char8  *fileName,
                                           UInt32  uiOptions = 0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Write                                      */
    /*! \{                                                                 */

    virtual Bool write(const NodePtr node, const Char8 *fileName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Debug                                      */
    /*! \{                                                                 */

    void print (void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SceneFileHandler (void);
    SceneFileHandler (const SceneFileHandler &obj);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef list<          SceneFileType *> FileTypeList;
    typedef map <IDString, FileTypeList  *> FileTypeMap;

    struct FindOverride
    {
        UInt32 uiRefPriority;

        Bool operator() (SceneFileType *fileTypeP);
    };

    static SceneFileHandler *_the;

    FileTypeMap _suffixTypeMap;

    static Bool addSceneFileType(SceneFileType &fileType);
};

typedef SceneFileHandler* SceneFileHandlerP;

OSG_END_NAMESPACE

#define OSGSCENEFILEHANDLER_HEADER_CVSID "@(#)$Id: $"

#endif // OSGIMAGEFILEHANDLER_CLASS_DECLARATION
