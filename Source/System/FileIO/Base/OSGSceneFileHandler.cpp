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

//-------------------------------
//  Includes
//-------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <fstream>

#include "OSGConfig.h"

#include <OSGLog.h>
#include <OSGBaseTypes.h>
#include <OSGPathHandler.h>
#include <OSGGraphOpSeq.h>

#include "OSGSceneFileHandler.h"

#include <OSGNode.h>
#include <OSGThread.h>
#include <OSGThreadManager.h>
#include <OSGBaseFunctions.h>

OSG_USING_NAMESPACE

/* enum VecBase::VectorSizeE
 * brief
*/


/* var VecBase::VectorSizeE VecBase::_iSize
 *
*/


/* const char *VecBase::getClassName(void)
 *  brief Classname
*/


/* var ValueTypeT VecBase:: _value[Size];
 * brief value store
*/


/*****************************
 *   Types
 *****************************/


/*****************************
 *    Classvariables
 *****************************/


SceneFileHandler * SceneFileHandler::_the = NULL;

/********************************
 *    Class methodes
 *******************************/


/*******************************
*public
*******************************/


//----------------------------
// Function name: getFileType
//----------------------------
//
//Parameters:
//p: const char *fileName
//GlobalVars:
//g:
//Returns:
//r:SceneFileType
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: getFileType
//SeeAlso:
//s:
//
//------------------------------

SceneFileType *SceneFileHandler::getFileType(const Char8 *fileName)
{
          Int32                  i;
          Int32                  l;
          IDString               suffix;
    const Char8                  separator = '.';
          SceneFileType         *type = NULL;
          FileTypeMap::iterator  sI;
          std::ifstream          fin;

    if(fileName)
    {
        l = strlen(fileName);

        if(l == 0)
            return NULL;

        for(i = l - 1; i >= 0; i--)
        {
            if(fileName[i] == separator)
                break;
        }

        if(i >= 0)
        {
            suffix.set(&(fileName[i+1]));
            suffix.toLower();

            sI = _suffixTypeMap.find(suffix);

            type = (sI == _suffixTypeMap.end()) ? 0 : sI->second->front();
        }
    }

    return type;
}

SceneFileType *SceneFileHandler::getExtType(const Char8 *ext)
{
          Int32                  i;
          Int32                  l;
          IDString               suffix;
    const Char8                  separator = '.';
          SceneFileType         *type = NULL;
          FileTypeMap::iterator  sI;
          std::ifstream          fin;

    if(ext)
    {
        l = strlen(ext);

        if(l == 0)
            return NULL;

        for(i = l - 1; i >= 0; i--)
        {
            if(ext[i] == separator)
                break;
        }

        // it is also possible to give a complete filename as extension.
        if(i >= 0)
            suffix.set(&(ext[i+1]));
        else
            suffix.set(ext);

        suffix.toLower();

        sI = _suffixTypeMap.find(suffix);

        type = (sI == _suffixTypeMap.end()) ? 0 : sI->second->front();
    }

    return type;
}

//CHECK
#ifdef OSG_WIN32_ICL
#pragma warning (disable : 383)
#endif

Int32 SceneFileHandler::getSuffixList(std::list<const char *> & suffixList)
{
    Int32                 count = 0;
    FileTypeMap::iterator sI;

    for ( sI = _suffixTypeMap.begin(); sI != _suffixTypeMap.end(); sI++)
    {

      suffixList.push_back(sI->first.str());
      count++;
    }

  return count;
}


#ifdef OSG_WIN32_ICL
#pragma warning (default : 383)
#endif


NodePtr SceneFileHandler::read(std::istream &is, const Char8* ext,
                                      GraphOpSeq *graphOpSeq)
{
    SceneFileType *type = getExtType(ext);
    NodePtr        scene = NullFC;

    if(!ext)
    {
        SWARNING << "cannot read NULL extension" << std::endl;
        return NullFC;
    }

    if (type)
    {
        SINFO << "try to read stream as " << type->getName() << std::endl;

        startReadProgressThread(is);
        scene = type->read(is);
        stopReadProgressThread();

        if(scene != NullFC)
        {
            if(graphOpSeq != NULL)
                graphOpSeq->run(scene);

            SINFO    << "read ok:"        << std::endl;
        }
        else
        {
            SWARNING << "could not read " << std::endl;
        }
    }
    else
    {
        SWARNING << "could not read unknown file format" << std::endl;
    }

    return scene;
}


SceneFileHandler::FCPtrStore SceneFileHandler::readTopNodes(
    std::istream &is, const Char8 *ext,
           GraphOpSeq *graphOpSeq)
{
    std::vector<FieldContainerPtr> nodeVec;
    NodePtr scene = read(is, ext);
    if(scene == NullFC)
        return nodeVec;

    while(scene->getNChildren() > 0)
    {
        NodePtr child = scene->getChild(0);
        NodePtr newChild = Node::create();
        while(child->getNChildren() > 0)
            newChild->addChild(child->getChild(0));
        newChild->setCore(child->getCore());
        if(graphOpSeq != NULL)
                graphOpSeq->run(newChild);
        nodeVec.push_back(newChild);
        scene->subChild(child);
    }

    return nodeVec;
}

NodePtr SceneFileHandler::read(const  Char8  *fileName,
                                      GraphOpSeq *graphOpSeq)
{
    if(!fileName)
    {
        SWARNING << "cannot read NULL file" << std::endl;
        return NullFC;
    }

    std::string fullFilePath;
    if(_pathHandler != NULL)
        fullFilePath = _pathHandler->findFile(fileName);
    else
        fullFilePath = fileName;

    SceneFileType *type = getFileType(fullFilePath.c_str());
    NodePtr scene = NullFC;

    if (type)
    {
        SINFO << "try to read " << fullFilePath
              << " as "         << type->getName() << std::endl;

        std::ifstream in(fullFilePath.c_str(), std::ios::binary);

        if(in)
        {
            scene = read(in, fullFilePath.c_str(), graphOpSeq);
            in.close();

            if(scene != NullFC)
                return scene;
        }
        else
        {
            SWARNING << "Couldn't open input stream for file " << fullFilePath << std::endl;
        }

        // Ok stream interface didn't work try via filename
        if(scene == NullFC)
            scene = type->read(fullFilePath.c_str());

        if (scene != NullFC)
        {
            if(graphOpSeq != NULL)
                graphOpSeq->run(scene);

            SINFO    << "read ok:"        << std::endl;
        }
        else
        {
            SWARNING << "could not read " << std::endl;
        }
    }
    else
    {
        SWARNING << "could not read "       << fullFilePath
                 << "; unknown file format" << std::endl;
    }

    return scene;
}

SceneFileHandler::FCPtrStore SceneFileHandler::readTopNodes(
    const  Char8  *fileName,
           GraphOpSeq *graphOpSeq)
{
    std::vector<FieldContainerPtr> nodeVec;

    if(!fileName)
    {
        SWARNING << "cannot read NULL file" << std::endl;
        return nodeVec;
    }

    std::string fullFilePath;
    if(_pathHandler != NULL)
        fullFilePath = _pathHandler->findFile(fileName);
    else
        fullFilePath = fileName;

    std::ifstream in(fullFilePath.c_str(), std::ios::binary);

    if(in)
    {
        nodeVec = readTopNodes(in, fullFilePath.c_str(), graphOpSeq);
        in.close();
    }
    else
    {
        SWARNING << "Couldn't open input stream for file " << fullFilePath << std::endl;
    }

    // Ok stream interface didn't work try via filename
    if(nodeVec.empty())
    {
        NodePtr scene = read(fullFilePath.c_str());
        if(scene == NullFC)
            return nodeVec;

        while(scene->getNChildren() > 0)
        {
            NodePtr child = scene->getChild(0);
            NodePtr newChild = Node::create();
            while(child->getNChildren() > 0)
                newChild->addChild(child->getChild(0));
            newChild->setCore(child->getCore());
            if(graphOpSeq != NULL)
                graphOpSeq->run(newChild);
            nodeVec.push_back(newChild);
            scene->subChild(child);
        }
    }

    return nodeVec;
}

//----------------------------
// Function name: write
//----------------------------
//
//Parameters:
//p: const Scene &image, const char *fileName
//GlobalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d:
//SeeAlso:
//s:
//
//------------------------------
bool SceneFileHandler::write(const NodePtr &node, std::ostream &os, const Char8 *ext)
{
    bool retCode = false;
    SceneFileType *type = getExtType(ext);

    if(type)
    {
        SINFO << "try to write stream as " << type->getName() << std::endl;
        retCode = type->write(node, os);
    }
    else
        SWARNING << "can't write stream unknown scene format" << std::endl;

    return retCode;
}

//----------------------------
// Function name: write
//----------------------------
//
//Parameters:
//p: const Scene &image, const char *fileName
//GlobalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d:
//SeeAlso:
//s:
//
//------------------------------
bool SceneFileHandler::write (const NodePtr &node, const Char8 *fileName)
{
    bool retCode = false;
    SceneFileType *type = getFileType(fileName);

    if (type)
    {
        SINFO << "try to write " << fileName << " as " << type->getName() << std::endl;

        std::ofstream out(fileName, std::ios::binary);
        if(out)
        {
            retCode = write(node, out, fileName);
            out.close();
        }
        else
        {
            SWARNING << "Can not open output stream for file '" << fileName << "'!" << std::endl;
        }

        if(!retCode)
            retCode = type->write(node, fileName);

        if(!retCode)
            SWARNING << "Couldn't write " << fileName << std::endl;
    }
    else
        SWARNING << "can't write " << fileName << "; unknown scene format"
                         << std::endl;

    return retCode;
}

/*!
Returns the path handler used
*/
PathHandler *SceneFileHandler::getPathHandler(void)
{
    return _pathHandler;
}

//-------------------------------------------------------------------------
/*!
Method to set the path handler.
*/
void SceneFileHandler::setPathHandler(PathHandler *pathHandler)
{
    _pathHandler = pathHandler;
}


//----------------------------
// Function name: print
//----------------------------
//
//Parameters:
//p: void
//GlobalVars:
//g:
//Returns:
//r:void
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: print debug info to cerr
//SeeAlso:
//s:
//
//------------------------------
void SceneFileHandler::print (void )
{
    FileTypeMap::iterator sI;

    for(sI = _suffixTypeMap.begin(); sI != _suffixTypeMap.end(); sI++)
    {
        std::cerr << "suffix: " << sI->first.str()
                  << ", type: " << sI->second->front()->getName()
                  << std::endl;
    }
}

/******************************
*protected
******************************/


/******************************
*private
******************************/


//----------------------------
// Function name: addSceneFileType
//----------------------------
//
//Parameters:
//p: SceneFileType *fileType
//GlobalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d:
//SeeAlso:
//s:
//
//------------------------------

bool SceneFileHandler::FindOverride::operator() (SceneFileType *fileTypeP)
{
    if(fileTypeP == NULL)
        return false;

    if(fileTypeP->doOverride() == false)
        return true;

    if(fileTypeP->getOverridePriority() <= uiRefPriority)
        return true;

    return false;
}

//CHECK
#ifdef OSG_WIN32_ICL
#pragma warning (disable : 383)
#endif

bool SceneFileHandler::addSceneFileType(SceneFileType &fileType)
{
    bool retCode = false;

    std::list<IDString>::iterator sI;
         FileTypeMap   ::iterator smI;

    IDString suffix;

    if(_the == NULL)
    {
        _the = new SceneFileHandler;
    }

    for(  sI  = fileType.suffixList().begin();
          sI != fileType.suffixList().end();
        ++sI)
    {
        suffix.set(sI->str());
        suffix.toLower();

        smI = _the->_suffixTypeMap.find(suffix);

        if (smI != _the->_suffixTypeMap.end())
        {
            if(fileType.doOverride() == true)
            {
                FindOverride           overrideFinder;
                FileTypeList::iterator lIt;

                overrideFinder.uiRefPriority = fileType.getOverridePriority();

                lIt = std::find_if(_the->_suffixTypeMap[suffix]->begin(),
                                   _the->_suffixTypeMap[suffix]->end(),
                                   overrideFinder);

                _the->_suffixTypeMap[suffix]->insert(lIt, &fileType);

                SWARNING << "Added an file type with suffix "
                         << suffix
                         << " overriding "
                         << std::endl;
            }
            else
            {
                _the->_suffixTypeMap[suffix]->push_back(&fileType);

                SWARNING << "Added an file type with suffix "
                         << suffix
                         << " non overriding at the end of the list"
                         << std::endl;
            }
        }
        else
        {
            FileTypeList *pTmpList = new FileTypeList;

            pTmpList->push_back(&fileType);

            _the->_suffixTypeMap[suffix] = pTmpList;

            retCode = true;
        }
    }

    return retCode;
}

bool SceneFileHandler::subSceneFileType(SceneFileType &fileType)
{
	bool retCode = false;

    std::list<IDString>::iterator sI;
         FileTypeMap   ::iterator smI;

    IDString suffix;

    if(_the == NULL)
    {
        _the = new SceneFileHandler;
    }

    for(  sI  = fileType.suffixList().begin();
          sI != fileType.suffixList().end();
        ++sI)
    {
        suffix.set(sI->str());
        suffix.toLower();

        smI = _the->_suffixTypeMap.find(suffix);
		if (smI != _the->_suffixTypeMap.end())
        {
            _the->_suffixTypeMap.erase(smI);
            retCode = true;
        }
    }
    return retCode;
}

#ifdef OSG_WIN32_ICL
#pragma warning (default : 383)
#endif

/***************************
*instance methodes
***************************/


/***************************
*public
***************************/


/**constructors & destructors**/


//----------------------------
// Function name: SceneFileHandler
//----------------------------
//
//Parameters:
//p: void
//GlobalVars:
//g:
//Returns:
//r:
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: Default Constructor
//SeeAlso:
//s:
//
//------------------------------
SceneFileHandler::SceneFileHandler (void) :
    _readProgressFP(NULL),
    _progressData(),
    _readReady(false),
    _pathHandler(NULL)
{
    return;
}

//----------------------------
// Function name: SceneFileHandler
//----------------------------
//
//Parameters:
//p: const SceneFileHandler &obj
//GlobalVars:
//g:
//Returns:
//r:
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: Copy Constructor
//SeeAlso:
//s:
//
//------------------------------
SceneFileHandler::SceneFileHandler (const SceneFileHandler & )
{
    SWARNING << "In copy constructor; I shouldn't be in this corner" << std::endl;
}

//----------------------------
// Function name: ~SceneFileHandler
//----------------------------
//
//Parameters:
//p: void
//GlobalVars:
//g:
//Returns:
//r:
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: Destructor
//SeeAlso:
//s:
//
//------------------------------

SceneFileHandler &SceneFileHandler::the(void)
{
    return *_the;
}

void SceneFileHandler::setReadProgressCB(progresscbfp fp)
{
    _readProgressFP = fp;
}

void SceneFileHandler::startReadProgressThread(std::istream &is)
{
    if(_readProgressFP == NULL)
        return;

    // get length of the stream.
    _progressData.is = &is;
    is.seekg(0, std::ios::end);
    _progressData.length = is.tellg();
    is.seekg(0, std::ios::beg);

    Thread *pt = Thread::find("osg::FileIOReadProgressThread");
    if(pt == NULL)
        pt = OSG::Thread::get("osg::FileIOReadProgressThread");

    _readReady = false;
    if(pt != NULL)
        pt->runFunction(readProgress, 0, NULL);
    else
        SWARNING << "Couldn't create read progress thread!" << std::endl;
}

void SceneFileHandler::stopReadProgressThread(void)
{
    if(_readProgressFP == NULL)
        return;

    Thread *pt = Thread::find("osg::FileIOReadProgressThread");

    if(pt != NULL)
    {
        // terminate thread
        _readReady = true;
        Thread::join(pt);
    }
}

void SceneFileHandler::readProgress(void * OSG_CHECK_ARG(data))
{
    UInt32 p = 0;
    while(p < 100 && !the()._readReady)
    {
        if(!the()._progressData.is->eof() &&
           !the()._progressData.is->bad())
        {
            UInt64 pos = the()._progressData.is->tellg();
            p = (pos * 100) / the()._progressData.length;
            if(p > 100)
                p = 100;
        }
        else
        {
            p = 100;
        }

        the()._readProgressFP(p);
        osgsleep(100);
    }
    if(p < 100)
        the()._readProgressFP(100);
}

SceneFileHandler::~SceneFileHandler(void)
{
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGSCENEFILEHANDLER_HEADER_CVSID;
}
