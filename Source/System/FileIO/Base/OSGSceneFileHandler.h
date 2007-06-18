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
    typedef void (*filenamecbfp) (const Char8 *fname);
    
    void setReadProgressCB(progresscbfp fp, bool use_thread = true);
    progresscbfp getReadProgressCB(void);

    void setReadBeginCB(filenamecbfp fp);
    filenamecbfp getReadBeginCB(void);

    void setReadEndCB(filenamecbfp fp);
    filenamecbfp getReadEndCB(void);

    void updateReadProgress(void);
    void updateReadProgress(UInt32 p);

    void triggerReadBegin(const Char8 *fname);
    void triggerReadEnd  (const Char8 *fname);

    void setWriteProgressCB(progresscbfp fp);
    progresscbfp getWriteProgressCB(void);

    void setWriteBeginCB(filenamecbfp fp);
    filenamecbfp getWriteBeginCB(void);

    void setWriteEndCB(filenamecbfp fp);
    filenamecbfp getWriteEndCB(void);

    void updateWriteProgress(UInt32 p);

    void triggerWriteBegin(const Char8 *fname);
    void triggerWriteEnd  (const Char8 *fname);

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

    typedef NodePtr (*fileioreadcbfp) (SceneFileType *type,
                                       std::istream &is, const Char8* ext);
    void setReadCB(fileioreadcbfp fp);
    fileioreadcbfp getReadCB(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Write                                      */
    /*! \{                                                                 */

    virtual bool write(const NodePtr &node, std::ostream &os, const Char8 *ext, bool compress = false);
    virtual bool write(const NodePtr &node, const Char8 *fileName, bool compress = false);

    typedef bool (*fileiowritecbfp) (SceneFileType *type,
                                     const NodePtr &node, std::ostream &os,
                                     const Char8 *ext, bool compress);
    void setWriteCB(fileiowritecbfp fp);
    fileiowritecbfp getWriteCB(void);

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

    static GraphOpSeq      *_defaultgraphOpSeq;

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

    void initReadProgress(std::istream &is);
    void terminateReadProgress(void);
    static void readProgress(void *data);

    progresscbfp    _readProgressFP;
    filenamecbfp    _readBeginFP;
    filenamecbfp    _readEndFP;

    progressS       _progressData;
    bool            _readReady;
    bool            _useProgressThread;

    progresscbfp    _writeProgressFP;
    filenamecbfp    _writeBeginFP;
    filenamecbfp    _writeEndFP;

    PathHandler     *_pathHandler;
    PathHandler     _defaultPathHandler;

    fileioreadcbfp  _readFP;
    fileiowritecbfp _writeFP;
    
};

typedef SceneFileHandler* SceneFileHandlerP;

OSG_END_NAMESPACE

#define OSGSCENEFILEHANDLER_HEADER_CVSID "@(#)$Id: $"

#endif // OSGIMAGEFILEHANDLER_CLASS_DECLARATION
