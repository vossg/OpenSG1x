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

#ifndef _OSGSCENEFILEHANDLER_H_
#define _OSGSCENEFILEHANDLER_H_
#ifdef  __sgi
#pragma  once
#endif

#include <string>
#include <list>
#include <map>
#include <iostream>

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGSceneFileType.h>
#include <OSGPathHandler.h>
#include <OSGLock.h>

OSG_BEGIN_NAMESPACE

class GraphOpSeq;

/*! \ingroup GrpSystemDrawablesGeometrymetryLoaderLib
 *  \brief Brief OSGSceneFileHandler
 */

class OSG_SYSTEMLIB_DLLMAPPING SceneFileHandler
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef std::vector<FieldContainerPtr> FCPtrStore;

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Get                                  */
    /*! \{                                                                 */

    static SceneFileHandler &the(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SceneFileHandler(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Get                                        */
    /*! \{                                                                 */

    virtual SceneFileType *getFileType(const Char8 *fileNameOrExtension);

    virtual int getSuffixList(std::list<const Char8*> & suffixList,
                              UInt32 flags = SceneFileType::OSG_READ_SUPPORTED |
                                             SceneFileType::OSG_WRITE_SUPPORTED);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Progress                                   */
    /*! \{                                                                 */

    typedef void (*progresscbfp) (UInt32 p);
    void setReadProgressCB(progresscbfp fp);
    progresscbfp getReadProgressCB(void);

    static void updateReadProgress(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Read                                       */
    /*! \{                                                                 */

    virtual NodePtr    read                  (std::istream &is, const Char8* ext,
                                                     GraphOpSeq *graphOpSeq = _defaultgraphOpSeq);

    virtual FCPtrStore readTopNodes          (std::istream &is, const Char8* ext,
                                                     GraphOpSeq *graphOpSeq = _defaultgraphOpSeq);

    virtual NodePtr    read                  (const  Char8  *fileName,
                                                     GraphOpSeq *graphOpSeq = _defaultgraphOpSeq);

    virtual FCPtrStore readTopNodes          (const  Char8  *fileName,
                                                     GraphOpSeq *graphOpSeq = _defaultgraphOpSeq);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Write                                      */
    /*! \{                                                                 */

    virtual bool write(const NodePtr &node, std::ostream &os, const Char8 *ext, bool compress = false);
    virtual bool write(const NodePtr &node, const Char8 *fileName, bool compress = false);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   PathHandler                                */
    /*! \{                                                                 */

    virtual PathHandler* getPathHandler(void                    );
    virtual void         setPathHandler(PathHandler *pathHandler);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   DefaultGraphOp                             */
    /*! \{                                                                 */
    
    virtual GraphOpSeq *getDefaultGraphOp(void                  );
    virtual void        setDefaultGraphOp(GraphOpSeq *graphOpSeq);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Options                                    */
    /*! \{                                                                 */

    virtual bool               setOptions(const Char8 *suffix, const Char8 *options);
    virtual const Char8        *getOptions(const Char8 *suffix);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Debug                                      */
    /*! \{                                                                 */

    void print (void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef std::list<          SceneFileType *> FileTypeList;
    typedef std::map <IDString, FileTypeList  *> FileTypeMap;

    struct FindOverride
    {
        UInt32 uiRefPriority;

        bool operator() (SceneFileType *fileTypeP);
    };

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static SceneFileHandler *_the;

           FileTypeMap       _suffixTypeMap;


    static bool               addSceneFileType(SceneFileType &fileType);
    static bool               subSceneFileType(SceneFileType &fileType);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SceneFileHandler(void);
    SceneFileHandler(const SceneFileHandler &obj);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class OSG_SYSTEMLIB_DLLMAPPING SceneFileType;

    std::string initPathHandler(const Char8 *fileName);
    
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const SceneFileHandler &source);

    typedef struct
    {
        UInt64 length;
        std::istream *is;
    } progressS;

    void startReadProgressThread(std::istream &is);
    void stopReadProgressThread(void);
    static void readProgress(void *data);

    Lock           *_readProgressLock;
    progresscbfp    _readProgressFP;
    progressS       _progressData;
    bool            _readReady;
    UInt32          _current_progress;

    PathHandler     *_pathHandler;
    PathHandler     _defaultPathHandler;

    static GraphOpSeq      *_defaultgraphOpSeq;
    
};

typedef SceneFileHandler* SceneFileHandlerP;

OSG_END_NAMESPACE

#define OSGSCENEFILEHANDLER_HEADER_CVSID "@(#)$Id: $"

#endif // OSGIMAGEFILEHANDLER_CLASS_DECLARATION
