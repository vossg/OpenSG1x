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
#include <unistd.h>
#include <fcntl.h>
#include <list>
#include <string>
#include <OSGBaseTypes.h>
#include <OSGConfig.h>
#include <OSGLog.h>

OSG_BEGIN_NAMESPACE

#ifndef WIN32

class Win32PathParser
{
 private:
  Win32PathParser(){;}
  std::list<std::string>& parsePathList( const Char8* pathList );
  
  void expandPathes( const Char8* pathList );
  void splitPathList( void );
  std::string extractFileName( const Char8* file );
  std::string extractPathName( const Char8* file );
  	
  std::list<std::string> _pathList;
  std::string _workString;
	
  friend class PathHandler;
};

typedef Win32PathParser PathParser;

#else

class UnixPathParser
{
 private:
  UnixPathParser(){;}
  std::list<std::string>& parsePathList( const Char8* pathList );
  
  void expandPathes( const Char8* pathList );
  void splitPathList( void );
  std::string extractFileName( const Char8* file );
  std::string extractPathName( const Char8* file );
  
  std::list<std::string> _pathList;
  std::string _workString;
  
  friend class PathHandler;
};

typedef UnixPathParser PathParser;

#endif

class PathHandler
{
 public:
  PathHandler(){;}
  PathHandler( const Char8* initialPathList );
  void addPath( const Char8* pathList );
  void subPath( const Char8* pathList );
  void clearPathList(void);
  void setBaseFile( const Char8* fileName );
  void clearBaseFile( void );
  std::string findFile( const Char8* fileName );
  
  void dump( void );
	
 private:
  std::list<std::string> _pathList;
  std::string _baseFilePath;
  PathParser _parser;
    
};

OSG_END_NAMESPACE

#endif /* _OSGPATHHANDLER_H */










