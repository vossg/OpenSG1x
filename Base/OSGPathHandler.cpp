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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGPathHandler.h"

#include "OSGFileSystem.h"

#ifndef WIN32
#include <pwd.h>
#endif

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGPathHandler.cpp,v 1.7 2001/10/12 11:01:05 neumannc Exp $";
    static Char8 cvsid_hpp[] = OSGPATHHANDLER_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

Char8 PathHandler::_dirSepWin32  = '\\';
Char8 PathHandler::_pathSepWin32 = ';';

Char8 PathHandler::_dirSepUnix   = '/';
Char8 PathHandler::_pathSepUnix  = ':';

#ifdef WIN32
Char8 PathHandler::_dirSep       = _dirSepWin32;
Char8 PathHandler::_pathSep      = _pathSepWin32;
Char8 PathHandler::_dirSepOther  = _dirSepUnix;
Char8 PathHandler::_pathSepOther = _pathSepUnix;
#else
Char8 PathHandler::_dirSep       = _dirSepUnix;
Char8 PathHandler::_pathSep      = _pathSepUnix;
Char8 PathHandler::_dirSepOther  = _dirSepWin32;
Char8 PathHandler::_pathSepOther = _pathSepWin32;
#endif

PathHandler::PathHandler(void) :
    _pathList    (),
    _baseFilePath()
{
}

PathHandler::PathHandler(const Char8 *initialPathList)
{
    push_backUnixPath(initialPathList);
}

PathHandler::~PathHandler(void)
{
}

string PathHandler::findFile(const Char8 *fileName)
{
    string returnValue;
    Bool   bFound      = false;

    PathList     tmpList;

    PathListIter iter    = _pathList.begin();
    PathListIter listEnd = _pathList.end();

    PathType     pType   = analysePath(fileName);

    parsePathList(fileName, tmpList);

    if(tmpList.size() != 0)
    {
        if((pType & TypeMask) == AbsPath)
        {
            PNOTICE << "Check abs : " << tmpList.front() << endl;

            if(File::tstAttr(tmpList.front().c_str(),
                             AccessFlags::IsReadable))
            {
                returnValue.assign(fileName);
            }
        }
        else
        {
            if(_baseFilePath.empty() == false)
            {
                returnValue.assign(_baseFilePath);

                returnValue.append(tmpList.front());

                PNOTICE << "Check base : " << returnValue << endl;

                if(File::tstAttr(returnValue.c_str(),
                                 AccessFlags::IsReadable) == false)
                {
                    returnValue.erase();
                }
                else
                {
                    bFound = true;
                }
            }

            if(bFound == false)
            {
                while(iter != listEnd)
                {
                    returnValue.assign(*iter);
                    returnValue.append(tmpList.front());

                    PNOTICE << "Check from pl : " << returnValue << endl;

                    if(File::tstAttr(returnValue.c_str(),
                                     AccessFlags::IsReadable) == true)
                    {
                        break;
                    }

                    ++iter;
                }

                if(iter == listEnd)
                {
                    returnValue.erase();
                }
            }
        }
    }

    return returnValue;
}

void PathHandler::push_backPath(const Char8 *pathList)
{
    PathList tmpList;

    parsePathList(pathList, tmpList);

    push_backPathList(tmpList);
}

void PathHandler::push_backCurrentDir(void)
{
    Char8 *pCurrentDir = Directory::getCurrent();

    _pathList.push_back(pCurrentDir);

    validateList();

    delete [] pCurrentDir;
}

void PathHandler::push_backUnixPath(const Char8 *pathList)
{
    PathList tmpList;

    parseUnixPathList(pathList, tmpList);

    push_backPathList(tmpList);
}

void PathHandler::push_backWin32Path(const Char8 *pathList)
{
    PathList tmpList;

    parseWin32PathList(pathList, tmpList);

    push_backPathList(tmpList);
}


void PathHandler::push_frontPath(const Char8 *pathList)
{
    PathList tmpList;

    parsePathList(pathList, tmpList);

    push_frontPathList(tmpList);
}

void PathHandler::push_frontCurrentDir(void)
{
    Char8 *pCurrentDir = Directory::getCurrent();

    _pathList.push_front(pCurrentDir);

    validateList();

    delete [] pCurrentDir;
}

void PathHandler::push_frontUnixPath(const Char8 *pathList)
{
    PathList tmpList;

    parseUnixPathList(pathList, tmpList);

    push_frontPathList(tmpList);
}

void PathHandler::push_frontWin32Path(const Char8 *pathList)
{
    PathList tmpList;

    parseWin32PathList(pathList, tmpList);

    push_frontPathList(tmpList);
}


void PathHandler::subUnixPath(const Char8 *pathList)
{
}

void PathHandler::subWin32Path(const Char8 *pathList)
{
}

void PathHandler::clearPathList(void)
{
    _pathList.clear();
}


void PathHandler::setBaseFile(const Char8 *fileName)
{
    if(fileName != NULL)
    {
        _baseFilePath = extractPath(fileName);
    }
}

void PathHandler::clearBaseFile(void)
{
    _baseFilePath.erase();
}

void PathHandler::dump(void)
{
    PathListIter iter = _pathList.begin();

    if(_baseFilePath.size() != 0)
    {
        SLOG << "Base file path : " << _baseFilePath << endl;
    }
    else
    {
        SLOG << "Base file path : empty" << endl;
    }

    for( ; iter != _pathList.end(); ++iter )
    {
        SLOG << "\"" << *iter << "\"" << endl;
    }
}

string PathHandler::extractPath(const Char8 *szFilename)
{
    string returnValue(szFilename);

    string::size_type pos = returnValue.find_last_of("\\/");

    if(pos != string::npos)
    {
        if(pos != returnValue.length() - 1)
        {
            returnValue.erase(pos + 1);
        }
    }
    else
    {
        returnValue.assign(".");
    }

    PathType pType = analysePathList(returnValue.c_str());

    if((pType & PlatformMask) == Win32Path)
    {
#ifndef WIN32
        convertPath(returnValue);
#endif
    }
    else
    {
#ifdef WIN32
        convertPath(returnValue);
#endif
    }

    if(returnValue[returnValue.length() - 1] != _dirSep)
    {
        returnValue += _dirSep;
    }

    return returnValue;
}


void PathHandler::validateList(void)
{
    PathListIter iter    = _pathList.begin();
    PathListIter listEnd = _pathList.end();

    while(iter != listEnd)
    {
        if(iter->empty() == true)
        {
            (*iter) += '.';
            (*iter) += _dirSep;
        }
        else
        {
            if((*iter)[iter->length() - 1] != _dirSep)
            {
                (*iter) += _dirSep;
            }
        }

        ++iter;
    }
}

void PathHandler::push_backPathList(PathList &pathList)
{
    _pathList.splice(_pathList.end(), pathList);

    validateList();
}

void PathHandler::push_frontPathList(PathList &pathList)
{
    _pathList.splice(_pathList.begin(), pathList);

    validateList();
}

void PathHandler::expandWin32Path(string &path)
{
    string envVar;

    string::size_type currPos  = 0;
    string::size_type startPos = 0;

    if(path.size() == 0)
        return;

    while(path[currPos] != '\0')
    {
        if(path[currPos] == '%')
        {
            envVar.erase();
            startPos = currPos++;

            while(path[currPos] != '%' &&
                  path[currPos] != '\0')
            {
                envVar += path[currPos++];
            }

            if(path[currPos] != '\0')
            {
                currPos++;
            }

            Char8 *szEnvVal = getenv(envVar.c_str());

            if(szEnvVal == NULL)
            {
                fprintf(stderr, "Could not find env var %s\n", envVar.c_str());
            }
            else
            {
                path.replace(startPos, currPos - startPos, szEnvVal);
            }
        }
        else
        {
            currPos++;
        }
    }
}

void PathHandler::expandUnixPath(string &path)
{
    string  envVar;
    string  userName;
    string  userHome;
    Bool    stop;
#ifndef WIN32
    passwd* userInfo;
#endif
    
    string::size_type currPos  = 0;
    string::size_type startPos = 0;

    if(path.size() == 0)
        return;

    while(path[currPos] != '\0')
    {
        if(path[currPos] == '$')
        {
            envVar.erase();
            startPos = currPos++;

            while(path[currPos] != ':' &&
                  path[currPos] != '/' &&
                  path[currPos] != '$' &&
                  path[currPos] != '\0')
            {
                envVar += path[currPos++];
            }

            Char8 *szEnvVal = getenv(envVar.c_str());

            if(szEnvVal == NULL)
            {
                fprintf(stderr, "Could not find env var %s\n", envVar.c_str());
            }
            else
            {
                path.replace(startPos, currPos - startPos, szEnvVal);
            }
        }
#ifndef WIN32
        else if(path[currPos] == '~')
        {
            userName.erase();
            startPos = currPos++;

            while(path[currPos] != ':' &&
                  path[currPos] != '/' &&
                  path[currPos] != '$' &&
                  path[currPos] != '\0')
            {
                userName += path[currPos++];
            }
            
            if( !userName.empty() )
            {
                setpwent();     //prepare access to user db
                stop = false;
                while( !stop )
                {
                    if((userInfo=getpwent()) != NULL )
                    {
                        if(strcmp(userName.c_str(), userInfo->pw_name) == 0)
                        {
                            stop = true;
                            userHome = userInfo->pw_dir;
                        }
                    }
                    else
                    {
                        stop = true;
                    }
                }
                endpwent();
            }
            else
            {
                if((userInfo=getpwuid(getuid())) != NULL)
                {
                    userHome = userInfo->pw_dir;
                }
            }
            
            if(!userHome.empty())
            {
                path.replace(startPos, currPos - startPos, userHome);
            }
            else
            {
                fprintf(stderr, "Could not find user home %s\n",
                        userHome.c_str());
            }
        }
#endif
        else
        {
            currPos++;
        }
    }
}

void PathHandler::convertPath(string &path)
{
    string::iterator stringIt  = path.begin();
    string::iterator stringEnd = path.end  ();

    while(stringIt != stringEnd)
    {
        if(*stringIt == _dirSepOther)
        {
            *stringIt = _dirSep;
        }

        stringIt++;
    };
}

void PathHandler::convertWin32PathList(PathList &result)
{
    PathListIter iter    = result.begin();
    PathListIter endList = result.end();

    while(iter != endList)
    {
        expandWin32Path(*iter);

#ifndef WIN32
        convertPath    (*iter);
#endif

        iter++;
    };
}

void PathHandler::convertUnixPathList(PathList &result)
{
    PathListIter iter    = result.begin();
    PathListIter endList = result.end();

    while(iter != endList)
    {
        expandUnixPath(*iter);

#ifdef WIN32
        convertPath   (*iter);
#endif

        iter++;
    };
}

void PathHandler::splitPathList(const Char8    *pathList,
                                const Char8     pathSep,
                                      PathList &result)
{
    string::size_type currPos    = 0;
    string::size_type startPos   = 0;
    string            workString(pathList);

    currPos = workString.find(pathSep);

    if(currPos == string::npos)
    {
        result.push_back(workString);
    }
    else
    {
        while(currPos != string::npos)
        {
            result.push_back(workString.substr(startPos,
                                               currPos - startPos));

            startPos = currPos + 1;

            currPos = workString.find(pathSep, startPos);
        }

        if(startPos != 0)
        {
            result.push_back(workString.substr(startPos));
        }
    }
}

PathHandler::PathType PathHandler::analysePathList(const Char8 *pathList)
{
          PathType  returnValue = UnixPath;
    const Char8    *pCurr       = pathList;

    if(pathList == NULL)
        return returnValue;

    while(*pCurr != '\0')
    {
        if(*pCurr == '\\')
        {
            returnValue = Win32Path;
            break;
        }
        else if(*pCurr == ';')
        {
            returnValue = Win32Path;
            break;
        }
        else if(*pCurr == '%')
        {
            returnValue = Win32Path;
            break;
        }
        else if(*pCurr == '/')
        {
            returnValue = UnixPath;
            break;
        }
        else if(*pCurr == '$')
        {
            returnValue = UnixPath;
            break;
        }
        else if(*pCurr == ':')
        {
            if(*(pCurr + 1) == '\\')
            {
                returnValue = Win32Path;
                break;
            }
        }

        pCurr++;
    }

    return returnValue;
}

PathHandler::PathType PathHandler::analysePath(const Char8 *path)
{
          PathType  returnValue = UnixPath;
          UInt32    uiSize      = 0;
    const Char8    *pCurr       = path;

    if(path == NULL)
        return returnValue;

    while(*pCurr != '\0')
    {
        if(*pCurr == '\\')
        {
            returnValue = Win32Path;
            break;
        }
        else if(*pCurr == ';')
        {
            returnValue = Win32Path;
            break;
        }
        else if(*pCurr == '%')
        {
            returnValue = Win32Path;
            break;
        }
        else if(*pCurr == '/')
        {
            returnValue = UnixPath;
            break;
        }
        else if(*pCurr == '$')
        {
            returnValue = UnixPath;
            break;
        }
        else if(*pCurr == ':')
        {
            if(*(pCurr + 1) == '\\')
            {
                returnValue = Win32Path;
                uiSize++;
                break;
            }
        }

        pCurr++;
        uiSize++;
    }

    if(returnValue == Win32Path)
    {
        fprintf(stderr, "xx%d\n", uiSize);

        if(uiSize >= 2)
        {
            if(path[1] == ':')
                returnValue = (PathType) (returnValue | AbsPath);
        }
    }
    else
    {
        if(path[0] == '/')
            returnValue = (PathType) (returnValue | AbsPath);
    }

    return returnValue;
}

void PathHandler::parsePathList(const Char8 *pathList, PathList &result)
{
    PathType pType = analysePathList(pathList);

    if((pType & PlatformMask) == Win32Path)
    {
        parseWin32PathList(pathList, result);
    }
    else
    {
        parseUnixPathList (pathList, result);
    }
}

void PathHandler::parseUnixPathList(const Char8 *pathList, PathList &result)
{
    if(pathList == NULL)
        return;

    splitPathList      (pathList, _pathSepUnix, result);

    convertUnixPathList(result);
}

void PathHandler::parseWin32PathList(const Char8 *pathList, PathList &result)
{
    if(pathList == NULL)
        return;

    splitPathList     (pathList, _pathSepWin32, result);

    convertWin32PathList(result);
}









