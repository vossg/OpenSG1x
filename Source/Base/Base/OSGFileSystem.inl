/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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

#include <iostream>

#include <OSGBaseFunctions.h>

OSG_BEGIN_NAMESPACE


#if defined(__sgi)

const UInt32 OSGDIRFLAG   = IFDIR;
const UInt32 OSGREADFLAG  = IREAD;
const UInt32 OSGWRITEFLAG = IWRITE;

#elif defined(__linux) || defined(darwin) || defined(__hpux) || defined(__sun)

const UInt32 OSGDIRFLAG   = S_IFDIR;
const UInt32 OSGREADFLAG  = S_IRUSR;
const UInt32 OSGWRITEFLAG = S_IWUSR;

#elif defined(WIN32)

const UInt32 OSGDIRFLAG   = _S_IFDIR;
const UInt32 OSGREADFLAG  = _S_IREAD;
const UInt32 OSGWRITEFLAG = _S_IWRITE;

#else
#error "Could not find your system, check your system/compiler combination"
#endif

/*!  File Functions
     \ingroup GrpBaseBaseFileSystem
 */

namespace File
{
    /*! \name File Functions           
        \ingroup GrpBaseBaseFileSystem 
        @{                             */

    inline
    bool tstAttr(const Char8  *szFilename,
                       UInt32  uiAccessFlags)
    {
        bool  returnValue = false;
        Int32 rc          = 0;
        
#ifdef WIN32
        struct _stat statBuffer;
#else
        struct  stat statBuffer;
#endif
        
        if(szFilename != NULL)
        {
#ifdef WIN32
            rc = _stat(szFilename, &statBuffer);
#else
            rc =  stat(szFilename, &statBuffer);
#endif
            if(rc == 0 && ! (statBuffer.st_mode & OSGDIRFLAG))
            {
                if(uiAccessFlags & AccessFlags::IsReadable)
                {
                    if(statBuffer.st_mode & OSGREADFLAG)
                    {
                        returnValue = true;
                    }
                }
                
                if(uiAccessFlags & AccessFlags::IsWriteable)
                {
                    if(statBuffer.st_mode & OSGWRITEFLAG)
                    {
                        returnValue = true;
                    }
                }
            }
        }
        
        return returnValue;
    }

    /*! @} */
}

/*!  Directory Functions
     \ingroup GrpBaseBaseFileSystem
 */

namespace Directory
{
    /*! \name Directory Functions      
        \ingroup GrpBaseBaseFileSystem 
        @{                             
     */

    inline
    bool tstAttr(const Char8  *szDirname,
                       UInt32  uiAccessFlags)
    {
        bool  returnValue = false;
        Int32 rc          = 0;
        
#ifdef WIN32
        struct _stat statBuffer;
#else
        struct  stat statBuffer;
#endif
        
        if(szDirname != NULL)
        {
#ifdef WIN32
            rc = _stat(szDirname, &statBuffer);
#else
            rc = stat(szDirname, &statBuffer);
#endif
            
            if(rc == 0 && (statBuffer.st_mode & OSGDIRFLAG))
            {
                if(uiAccessFlags & AccessFlags::IsReadable)
                {
                    if(statBuffer.st_mode & OSGREADFLAG)
                    {
                        returnValue = true;
                    }
                    else
                    {
                        returnValue = false;
                    }
                }
                
                if(uiAccessFlags & AccessFlags::IsWriteable)
                {
                    if(statBuffer.st_mode & OSGWRITEFLAG)
                    {
                        returnValue = true;
                    }
                    else
                    {
                        returnValue = false;
                    }
                }
            }
        }
        
        return returnValue;
    }

#ifdef __sgi
#pragma set woff 1209
#endif

    /*! \ingroup GrpBaseBaseFileSystem
     */

    inline
    Char8 *getCurrent(void)
    {
        UInt32 uiCurrentNameSize = 256;
        
        Char8 *returnValue = new Char8[uiCurrentNameSize];
        Char8 *szTmpBuf;
        
        while(1)
        {
#ifndef WIN32
            szTmpBuf =  getcwd(returnValue, uiCurrentNameSize);
#else
            szTmpBuf = _getcwd(returnValue, uiCurrentNameSize);
#endif
            if(szTmpBuf != NULL)
                break;
            
            uiCurrentNameSize *= 2;
            delete [] returnValue;
            
            returnValue = new Char8[uiCurrentNameSize];
        }
        
        return returnValue;
    }
    
#ifdef __sgi
#pragma reset woff 1209
#endif
    
    inline
    bool setCurrent(const Char8 *szDirname)
    {
        bool returnValue = false;
        
        if(szDirname != NULL)
        {
#ifndef WIN32
            if(chdir(szDirname) == 0)
                returnValue = true;
#else
            if(_chdir(szDirname) == 0)
                returnValue = true;
#endif
        }
        
        return returnValue;
    }

    /*! \ingroup GrpBaseBaseFileSystem
     */

    inline
    std::vector<Char8 *> *getEntries(const Char8 *szDirname,
                                     const Char8 *szPattern)
    {
        std::vector<Char8 *> *returnValue = NULL;
        
        if(szDirname != NULL)
        {
            if(tstAttr(szDirname, AccessFlags::IsReadable) == true)
            {
#ifndef WIN32
                DIR    *pDir        = opendir(szDirname);
                dirent *pDirEntry   = NULL;
                Char8  *szEntryName = NULL;
                
                if(pDir != NULL)
                {
                    returnValue = new std::vector<Char8 *>;

                    do
                    {
                        pDirEntry = readdir(pDir);
                        
                        if(pDirEntry != NULL)
                        {
                            stringDup(pDirEntry->d_name, szEntryName);
                            
                            if(szPattern != NULL)
                            {
                                if(fnmatch(szPattern, szEntryName, 0) == 0)
                                {
                                    returnValue->push_back(szEntryName);
                                }
                                else
                                {
                                    delete [] szEntryName;
                                }
                            }
                            else
                            {
                                returnValue->push_back(szEntryName);
                            }

                            szEntryName = NULL;
                        }
                    }
                    while(pDirEntry != NULL);
                    
                    closedir(pDir);
                }
#else
                Char8           *szTmpDirname = NULL;
                
                bool             bVal;
                WIN32_FIND_DATA  pDirEntry;
                HANDLE           pDir;
                Char8           *szEntryName = NULL;
                
                if(szPattern == NULL)
                {
                    szTmpDirname = new Char8[stringlen(szDirname) + 5];
                    
                    sprintf(szTmpDirname, "%s\\*", szDirname);
                }
                else
                {
                    szTmpDirname = new Char8[stringlen(szDirname) +
                                             stringlen(szPattern) + 
                                             5];
                    
                    sprintf(szTmpDirname, "%s\\%s", szDirname, szPattern);
                }
                
                pDir = FindFirstFile(szTmpDirname, &pDirEntry);
                
#ifdef OSG_WIN32_ICL
#pragma warning (disable : 171)
#endif
                
                if(INVALID_HANDLE_VALUE != pDir)
                {
                    returnValue = new std::vector<Char8 *>;
                    
                    do
                    {
                        stringDup(pDirEntry.cFileName, szEntryName);
                        
                        returnValue->push_back(szEntryName);
                        szEntryName = NULL;
                        
                        bVal = (FindNextFile(pDir, &pDirEntry) != FALSE);
                    }
                    while(bVal == true);
                    
                    FindClose(pDir);
                }
                
#ifdef OSG_WIN32_ICL
#pragma warning (error : 171)
#endif
                
                delete szTmpDirname;
#endif
            }
        }
        
        return returnValue;
    }

    /*! @} */
}

namespace Path
{
    inline
    static void fixWinNetworkPath(std::string &path)
    {
#ifdef WIN32
        // HACK but on windows network paths like \\Server\bla doesn't work, 
        // but //Server/bla works ...

        if((path.length() >  2   ) &&
           (path[0]       == '\\') &&
           (path[1]       == '\\')  )
        {
            for(Int32 i = 0; i < path.length(); ++i)
            {
                if(path[i] == '\\')
                {
                    path[i] = '/';
                }
            }
        }
#endif
    }
}

#define OSGFILESYSTEM_INLINE_CVSID "@(#)$Id: $"

OSG_END_NAMESPACE
