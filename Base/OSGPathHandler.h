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

#ifndef _OSGPATHHANDLER_H
#define _OSGPATHHANDLER_H
#ifdef __sgi
#pragma once
#endif

#include <stdlib.h>
#include <fcntl.h>
#include <list>
#include <string>

#ifndef WIN32
#include <unistd.h>
#endif

#include <OSGBaseTypes.h>
#include <OSGConfig.h>
#include <OSGLog.h>

OSG_BEGIN_NAMESPACE

//! Pathhandler
//! \ingroup baselib

class OSG_BASE_DLLMAPPING PathHandler
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
 
    PathHandler(void);
    PathHandler(const Char8 *initialPathList);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~PathHandler(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    string findFile(const Char8 *fileName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void push_backPath       (const Char8 *pathList);
    void push_backCurrentDir (void                 );

    void push_backUnixPath   (const Char8 *pathList);
    void push_backWin32Path  (const Char8 *pathList);

    void push_frontPath      (const Char8 *pathList);
    void push_frontCurrentDir(void                 );

    void push_frontUnixPath  (const Char8 *pathList);
    void push_frontWin32Path (const Char8 *pathList);

    void subUnixPath  (const Char8 *pathList);
    void subWin32Path (const Char8 *pathList);

    void clearPathList(void);

    void setBaseFile  (const Char8 *fileName);
    void clearBaseFile(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    void dump(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    enum PathType
    {
        Win32Path     = 0x0001,
        UnixPath      = 0x0002,

        AbsPath       = 0x0100,

        PlatformMask  = 0x00FF,
        TypeMask      = 0xFF00
    };
    
    typedef list<string>           PathList;
    typedef list<string>::iterator PathListIter;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static Char8 _dirSepWin32;
    static Char8 _pathSepWin32;

    static Char8 _dirSepUnix;
    static Char8 _pathSepUnix;

    static Char8 _dirSep;
    static Char8 _pathSep;

    static Char8 _dirSepOther;
    static Char8 _pathSepOther;


    PathList _pathList;
    string   _baseFilePath;

    void     validateList        (void                     );

    string   extractPath         (const Char8   *szFilename);
    
    PathType analysePathList     (const Char8   *pathList  );
    PathType analysePath         (const Char8   *path      );

    void     expandWin32Path     (      string   &path     );
    void     expandUnixPath      (      string   &path     );
    
    void     push_backPathList   (      PathList &pathList );
    void     push_frontPathList  (      PathList &pathList );

    void     convertPath         (      string   &path     );

    void     convertWin32PathList(      PathList &result   );
    void     convertUnixPathList (      PathList &result   );

    void     splitPathList       (const Char8    *pathList, 
                                  const Char8     pathSep,
                                        PathList &result   );
    void     parsePathList       (const Char8    *pathList, 
                                        PathList &result   );
    void     parseUnixPathList   (const Char8    *pathList, 
                                        PathList &result   );
    void     parseWin32PathList  (const Char8    *pathList, 
                                        PathList &result   );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    PathHandler(const PathHandler &source);
    void operator =(const PathHandler &source);
};

OSG_END_NAMESPACE

#endif /* _OSGPATHHANDLER_H */

#define OSGPATHHANDLER_HEADER_CVSID "@(#)$Id: OSGPathHandler.h,v 1.5 2002/02/11 03:46:26 vossg Exp $"

