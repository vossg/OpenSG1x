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

#define OSG_COMPILEBASELIB

#include "OSGPathHandler.h"

#if 0

#include <pwd.h>

OSG_USING_NAMESPACE

#ifndef WIN32

std::list<std::string>& Win32PathParser::parsePathList( const Char8* pathList )
{
  _pathList.clear();
  expandPathes( pathList );
  splitPathList();
  return _pathList;
}

void Win32PathParser::splitPathList( void )
{
  std::string::size_type currPos=0, startPos=0;
  while( (currPos=_workString.find(':', currPos)) != std::string::npos )
    {
      if( (currPos>1) && (_workString[currPos-2]!=':') )
	{
	  _pathList.push_back( _workString.substr(startPos,currPos-startPos) );
	  startPos = currPos+1;
	}
      currPos++;
    }
  if( startPos != currPos )
    {
      _pathList.push_back( _workString.substr(startPos) );
    }
}

void Win32PathParser::expandPathes( const Char8* pathList )
{
  _workString = pathList;
  std::string::size_type currPos = 0, startPos = 0, endPos = 0;
  Char8 currChar;
  char* envVarVal;
  std::string envVarName;
  std::string username;
  std::string userHome;
  std::string currWorkDir;
  passwd* userInfo;
  Bool abort = false;
  if( _workString.empty() )
    {
      abort = true;
    }
  while( !abort )
    {
      currChar = _workString[currPos];
      if( currChar == ':' )
	{
	  if( currPos > 1 )
	    {
	      if( _workString[currPos-2] != ';' )
		{
		  _workString[currPos++] = ';';
		}
	    }
	  ++currPos;
	}
      else if( currChar == '/' )
	{
	  _workString[currPos++] = '\\';
	}
      else if( currChar == '$' )
	{
	  envVarName.erase();
	  startPos = currPos;
	  ++currPos;
	  while( (currPos < _workString.length()        )   &&
		 ((currChar=_workString[currPos]) != ':')   &&
		 ((currChar=_workString[currPos]) != ';')   &&
		 ((currChar=_workString[currPos]) != '/')   &&
		 ((currChar=_workString[currPos]) != '\\') 	 )
	    {
	      envVarName +=  currChar;
	      ++currPos;
	    }
	  endPos = currPos;
	  if( (envVarVal=getenv(envVarName.c_str())) != NULL )
	    {
	      _workString.replace( startPos, endPos-startPos, envVarVal );
	      currPos = startPos;
	    }
	  else
	    {
	      SWARNING << "Win32PathParser::expandPathes: could not find "
		       << "environment variable: " << envVarName
		       << ", ignoring. " << endl;
	      endPos = startPos;
	      while( (startPos>0)                     && 
		     (_workString[startPos] != ';')     )
		{
		  --startPos;
		}
	      while( (endPos<_workString.length())          && 
		     (currChar=_workString[endPos] != ':')  &&
		     (currChar=_workString[endPos] != ';')     )
		{
		  ++endPos;
		}
	      _workString.erase(startPos,endPos-startPos);
	      currPos=startPos-1;
	    }
	}
      else if( currChar == '.' )
	{
	  if( currPos > 0 ) //not first char in string
	    {
	      Char8 prevChar = _workString[currPos-1];
	      if( prevChar == '\\' ) // \.
		{
		  if( currPos < _workString.length()-1 )
		    {
		      Char8 nextChar = _workString[currPos+1];
		      if( nextChar == '.' ) // \..
			{
			  if( currPos < _workString.length()-2 )
			    {
			      nextChar = _workString[currPos+2];
			      if( (nextChar == '/') || (nextChar == '\\') 
				  || (nextChar == ':') || (nextChar == ';') )
				// \..\ or \..:
				{
				  startPos = currPos-2;
				  endPos   = currPos+2; 
				  while( startPos > 0 )
				    {
				      if( _workString[startPos] == '\\' )
					{
					  break;
					}
				      else if( _workString[startPos] == ';' )
					{
					  SWARNING << 
					    "Win32PathParser::expandPathes: "
						   << 
					    "invalid path in path list "
						   << _workString << endl;
					  break;
					}
				      --startPos;
				    }
				  _workString.erase( startPos, 
						     endPos-startPos );
				  currPos -= (endPos-startPos)-2;
				}
			      else
				{
				  currPos += 2;
				}
			    }
			  else  // /.."
			    {
			      startPos = currPos-2;
			      endPos   = currPos+2; 
			      while( startPos > 0 )
				{
				  if( _workString[startPos] == '\\' )
				    {
				      break;
				    }
				  else if( _workString[startPos] == ';' )
				    {
				      SWARNING << 
					"Win32PathParser::expandPathes: "
					       << 
					"invalid path in path list "
					       << _workString << endl;  
				      break;
				    }
				  --startPos;
				}
			      _workString.erase( startPos, 
						 endPos-startPos );
			      currPos -= (endPos-startPos)-2;
			    }
			}		      
		      else if( (nextChar == '/') || (nextChar == '\\') )
			/* \.\ */
			{
			  _workString.erase( currPos, 2 );
			}
		      else if( (nextChar == ':') || (nextChar == ';') )
			// \.:
			{
			  _workString.erase( currPos, 1 );
			}
		      else
			{
			  ++currPos;
			}
		    }
		  else
		    // \."
		    {
		      _workString.erase( currPos, 1 );
		    }
		}
	      else if( prevChar == ';' )
		// :.
		{
		  if( currPos < _workString.length()-1 )
		    {
		      Char8 nextChar = _workString[currPos+1];
		      if( nextChar == '.' )
			// :..
			{
			  if( currPos < _workString.length()-2 )
			    {
			      nextChar = _workString[currPos+2];
			      if( (nextChar == '/') || (nextChar == '\\') 
				  || (nextChar == ':') || (nextChar == ';') )
				// :../ or :..\ or :..; or :..:
				{
				  if( !((currWorkDir=getcwd(NULL, 
							    0)).empty()) )
				    {
				      currWorkDir.erase(currWorkDir.rfind("\\"));
				    }
				  _workString.replace(currPos,2,currWorkDir);
				}
			      else
				{
				  currPos += 2;
				}
			    }
			  else
			    // :.."
			    {
			      if( !((currWorkDir=getcwd(NULL, 0)).empty()) )
				{
				  currWorkDir.erase(currWorkDir.rfind("\\"));
				}
			      _workString.replace(currPos,1,currWorkDir);
			    }
			}
		      else if( (nextChar == '/') || (nextChar == '\\')
			       ||(nextChar == ':') || (nextChar == ';') )
			// :./ or :.\ or :.: or :.; 
			{
			  currWorkDir=getcwd(NULL, 0);
			  _workString.replace(currPos,1,currWorkDir);
			}
		      else
			{
			  ++currPos;
			}
		    }
		  else
		    // :."
		    {
		       currWorkDir=getcwd(NULL, 0);
		       _workString.replace(currPos,1,currWorkDir);
		    }
		}
	      else
		{
		  ++currPos;
		}
	    }
	  else
	    // first char in string, treat in same way as :.
	    {
	      if( currPos < _workString.length()-1 )
		{
		  Char8 nextChar = _workString[currPos+1];
		  if( nextChar == '.' )
		    // :..
		    {
		      if( currPos < _workString.length()-2 )
			{
			  nextChar = _workString[currPos+2];
			  if( (nextChar == '/') || (nextChar == '\\') 
			      || (nextChar == ':') || (nextChar == ';') )
				// :../ or :..\ or :..; or :..:
			    {
			      if( !((currWorkDir=getcwd(NULL, 
							0)).empty()) )
				{
				  currWorkDir.erase(currWorkDir.rfind("\\"));
				}
			      _workString.replace(currPos,2,currWorkDir);
			    }
			  else
			    {
			      currPos += 2;
			    }
			}
		      else
			// :.."
			{
			  if( !((currWorkDir=getcwd(NULL, 0)).empty()) )
			    {
			      currWorkDir.erase(currWorkDir.rfind("\\"));
			    }
			  _workString.replace(currPos,1,currWorkDir);
			}
		    }
		  else if( (nextChar == '/') || (nextChar == '\\')
			   ||(nextChar == ':') || (nextChar == ';') )
		    // :./ or :.\ or :.: or :.; 
		    {
		      currWorkDir=getcwd(NULL, 0);
		      _workString.replace(currPos,1,currWorkDir);
		    }
		  else
		    {
		      ++currPos;
		    }
		}
	      else
		// :."
		{
		  currWorkDir=getcwd(NULL, 0);
		  _workString.replace(currPos,1,currWorkDir);
		}
	    }
	}
      else //no special character, keep it
	{
	  currPos++;
	}

      if( currPos == _workString.length() ) //end of string?
	{
	  abort = true;
	}
    }
  SINFO << _workString << endl;
}

std::string Win32PathParser::extractFileName( const Char8* file )
{
  std::string fileName( file );
  std::string::size_type pos = fileName.find_last_of("\\/");
  if( pos != std::string::npos )
    {
      if( pos < fileName.length() )
	{
	  fileName.erase( 0, pos+1);
	  return fileName;
	}
      else
	{
	  return std::string();
	}
    }
  else
    {
      return fileName;
    }
}

std::string Win32PathParser::extractPathName( const Char8* file )
{
  std::string pathName( file );
  std::string::size_type pos = pathName.find_last_of("\\/");
  if( pos != std::string::npos )
    {
      if( pos == pathName.length()-1 )
	{
	  return pathName;
	}
      else
	{
	  pathName.erase( pos+1 );
	  return pathName;
	}
    }
  else
    {
      return pathName;
    }
}


#else


std::list<std::string>& UnixPathParser::parsePathList( const Char8* pathList )
{
	_pathList.clear();
	expandPathes( pathList );
	splitPathList();
	return _pathList;
}

void UnixPathParser::expandPathes( const Char8* pathList )
{
  _workString = pathList;
  std::string::size_type currPos = 0, startPos = 0, endPos = 0;
  Char8 currChar;
  char* envVarVal;
  std::string envVarName;
  std::string username;
  std::string userHome;
  std::string currWorkDir;
  passwd* userInfo;
  Bool abort = false;
  while( !abort )
    {
      currChar = _workString[currPos];
      if( currChar == ';' )
	{
	  _workString[currPos++] = ':';
	}
      else if( currChar == '\\' )
	{
	  _workString[currPos++] = '/';
	}
      else if( currChar == '$' )
	{
	  envVarName.erase();
	  startPos = currPos;
	  ++currPos;
	  while(  (currPos < _workString.length()       )  &&
		 ((currChar=_workString[currPos]) != ':')   &&
		 ((currChar=_workString[currPos]) != ';')   &&
		 ((currChar=_workString[currPos]) != '/')   &&
		 ((currChar=_workString[currPos]) != '\\') 	 )
	    {
	      envVarName +=  currChar;
	      ++currPos;
	    }
	  endPos = currPos;
	  if( (envVarVal=getenv(envVarName.c_str())) != NULL )
	    {
	      _workString.replace( startPos, endPos-startPos, envVarVal );
	      currPos = startPos;
	    }
	  else
	    {
	      SWARNING << "UnixPathParser::expandPathes: could not find "
		       << "environment variable: " << envVarName
		       << ", ignoring. " << endl;
	      endPos = startPos;
	      while( (startPos>0)                     && 
		     (_workString[startPos] != ':')     )
		{
		  --startPos;
		}
	      while( (endPos<_workString.length())          && 
		     (currChar=_workString[endPos] != ':')  &&
		     (currChar=_workString[endPos] != ';')     )
		{
		  ++endPos;
		}
	      _workString.erase(startPos,endPos-startPos);
	      currPos=startPos-1;
	    }	  
	}
      else if( currChar == '~' )
	{
	  username.erase();
	  startPos = currPos;
	  ++currPos;
	  while(  (currPos<_workString.length()         )   &&
		 ((currChar=_workString[currPos]) != ':')   &&
		 ((currChar=_workString[currPos]) != ';')   &&
		 ((currChar=_workString[currPos]) != '/')   &&
		 ((currChar=_workString[currPos]) != '\\') 	 )
	    {
	      username += currChar;
	      ++currPos;
	    }
	  endPos = currPos;
	  if( !username.empty() )  // ~username
	    {
	      setpwent();
	      for( Bool stop=false; !stop; )
		{
		  if( (userInfo=getpwent()) != NULL )
		    {
		      if( strcmp(username.c_str(), userInfo->pw_name) == 0)
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
	  else  // just ~ , i.e. user's own homedir
	    {
	      if( (userInfo=getpwuid(getuid())) != NULL )
		{
		  userHome = userInfo->pw_dir;
		}
	    }
	  if( !userHome.empty() )
	    {
	      _workString.replace( startPos, endPos-startPos, userHome );
	      currPos = startPos;
	    }
	  else
	    {
	      SWARNING << "UnixPathParser::expandPathes: could not find "
		       << "home directory of user: " << username
		       << ", ignoring. " << endl;
	      endPos = startPos;
	      while( (startPos>0)                     && 
		     (_workString[startPos] != ':')     )
		{
		  --startPos;
		}
	      while( (endPos<_workString.length())          && 
		     (currChar=_workString[endPos] != ':')  &&
		     (currChar=_workString[endPos] != ';')     )
		{
		  ++endPos;
		}
	      _workString.erase(startPos,endPos-startPos);
	      currPos=startPos-1;
	    }
	}
      else if( currChar == '.' )
	{
	  if( currPos > 0 ) //not first char in string
	    {
	      Char8 prevChar = _workString[currPos-1];
	      if( prevChar == '/' ) // /.
		{
		  if( currPos < _workString.length()-1 )
		    {
		      Char8 nextChar = _workString[currPos+1];
		      if( nextChar == '.' ) // /..
			{
			  if( currPos < _workString.length()-2 )
			    {
			      nextChar = _workString[currPos+2];
			      if( (nextChar == '/') || (nextChar == '\\') 
				  || (nextChar == ':') || (nextChar == ';') )
				// /../ or /..:
				{
				  startPos = currPos-2;
				  endPos   = currPos+2; 
				  while( startPos > 0 )
				    {
				      if( _workString[startPos] == '/' )
					{
					  break;
					}
				      else if( _workString[startPos] == ':' )
					{
					  SWARNING << 
					    "UnixPathParser::expandPathes: "
						   << 
					    "invalid path in path list "
						   << _workString << endl;
					  break;
					}
				      --startPos;
				    }
				  _workString.erase( startPos, 
						     endPos-startPos );
				  currPos -= (endPos-startPos)-2;
				}
			      else
				{
				  currPos += 2;
				}
			    }
			  else  // /.."
			    {
			      startPos = currPos-2;
			      endPos   = currPos+2; 
			      while( startPos > 0 )
				{
				  if( _workString[startPos] == '/' )
				    {
				      break;
				    }
				  else if( _workString[startPos] == ':' )
				    {
				      SWARNING << 
					"UnixPathParser::expandPathes: "
					       << 
					"invalid path in path list "
					       << _workString << endl;
				      break;
				    }
				  --startPos;
				}
			      _workString.erase( startPos, 
						 endPos-startPos );
			      currPos -= (endPos-startPos)-2;
			    }
			}		      
		      else if( (nextChar == '/') || (nextChar == '\\') )
			// /./
			{
			  _workString.erase( currPos, 2 );
			}
		      else if( (nextChar == ':') || (nextChar == ';') )
			// /.:
			{
			  _workString.erase( currPos, 1 );
			}
		      else
			{
			  ++currPos;
			}
		    }
		  else
		    // /."
		    {
		      _workString.erase( currPos, 1 );
		    }
		}
	      else if( prevChar == ':' )
		// :.
		{
		  if( currPos < _workString.length()-1 )
		    {
		      Char8 nextChar = _workString[currPos+1];
		      if( nextChar == '.' )
			// :..
			{
			  if( currPos < _workString.length()-2 )
			    {
			      nextChar = _workString[currPos+2];
			      if( (nextChar == '/') || (nextChar == '\\') 
				  || (nextChar == ':') || (nextChar == ';') )
				// :../ or :..\ or :..; or :..:
				{
				  if( !((currWorkDir=getcwd(NULL, 
							    0)).empty()) )
				    {
				      currWorkDir.erase(currWorkDir.rfind("/"));
				    }
				  _workString.replace(currPos,2,currWorkDir);
				}
			      else
				{
				  currPos += 2;
				}
			    }
			  else
			    // :.."
			    {
			      if( !((currWorkDir=getcwd(NULL, 0)).empty()) )
				{
				  currWorkDir.erase(currWorkDir.rfind("/"));
				}
			      _workString.replace(currPos,1,currWorkDir);
			    }
			}
		      else if( (nextChar == '/') || (nextChar == '\\')
			       ||(nextChar == ':') || (nextChar == ';') )
			// :./ or :.\ or :.: or :.; 
			{
			  currWorkDir=getcwd(NULL, 0);
			  _workString.replace(currPos,1,currWorkDir);
			}
		      else
			{
			  ++currPos;
			}
		    }
		  else
		    // :."
		    {
		       currWorkDir=getcwd(NULL, 0);
		       _workString.replace(currPos,1,currWorkDir);
		    }
		}
	      else
		{
		  ++currPos;
		}
	    }
	  else
	    // first char in string, treat in same way as :.
	    {
	      if( currPos < _workString.length()-1 )
		{
		  Char8 nextChar = _workString[currPos+1];
		  if( nextChar == '.' )
		    // :..
		    {
		      if( currPos < _workString.length()-2 )
			{
			  nextChar = _workString[currPos+2];
			  if( (nextChar == '/') || (nextChar == '\\') 
			      || (nextChar == ':') || (nextChar == ';') )
				// :../ or :..\ or :..; or :..:
			    {
			      if( !((currWorkDir=getcwd(NULL, 
							0)).empty()) )
				{
				  currWorkDir.erase(currWorkDir.rfind("/"));
				}
			      _workString.replace(currPos,2,currWorkDir);
			    }
			  else
			    {
			      currPos += 2;
			    }
			}
		      else
			// :.."
			{
			  if( !((currWorkDir=getcwd(NULL, 0)).empty()) )
			    {
			      currWorkDir.erase(currWorkDir.rfind("/"));
			    }
			  _workString.replace(currPos,1,currWorkDir);
			}
		    }
		  else if( (nextChar == '/') || (nextChar == '\\')
			   ||(nextChar == ':') || (nextChar == ';') )
		    // :./ or :.\ or :.: or :.; 
		    {
		      currWorkDir=getcwd(NULL, 0);
		      _workString.replace(currPos,1,currWorkDir);
		    }
		  else
		    {
		      ++currPos;
		    }
		}
	      else
		// :."
		{
		  currWorkDir=getcwd(NULL, 0);
		  _workString.replace(currPos,1,currWorkDir);
		}
	    }
	}
      else //no special character, keep it
	{
	  currPos++;
	}

      if( currPos == _workString.length() ) //end of string?
	{
	  abort = true;
	}
    }
}

void UnixPathParser::splitPathList( void )
{
  std::string::size_type currPos=0, startPos=0;
  while( (currPos=_workString.find(':', currPos)) != std::string::npos )
    {
      _pathList.push_back( _workString.substr(startPos,currPos-startPos) );
      startPos = currPos+1;
      currPos++;
    }
  if( startPos != currPos )
    {
      _pathList.push_back( _workString.substr(startPos) );
    }
}

std::string UnixPathParser::extractFileName( const Char8* file )
{
  std::string fileName( file );
  std::string::size_type pos = fileName.find_last_of("\\/");
  if( pos != std::string::npos )
    {
      if( pos < fileName.length() )
	{
	  fileName.erase( 0, pos+1);
	  return fileName;
	}
      else
	{
	  return std::string();
	}
    }
  else
    {
      return fileName;
    }
}

std::string UnixPathParser::extractPathName( const Char8* file )
{
  std::string pathName( file );
  std::string::size_type pos = pathName.find_last_of("\\/");
  if( pos != std::string::npos )
    {
      if( pos == pathName.length() )
	{
	  return pathName;
	}
      else
	{
	  pathName.erase( pos+1 );
	  return pathName;
	}
    }
  else
    {
      return pathName;
    }
}

#endif




void PathHandler::dump(void)
{
  std::list<std::string>::iterator iter = _pathList.begin();
  for( ; iter != _pathList.end(); ++iter )
    {
      SLOG << "\"" << *iter << "\"" << endl;
    }
}

PathHandler::PathHandler( const Char8* initialPathList )
{
  addPath( initialPathList );
}

void PathHandler::addPath( const Char8* pathList )
{
  char currDir[256];
  std::list<std::string>& pathes = _parser.parsePathList( pathList );
	
  _pathList.splice( _pathList.begin(), pathes );
  _pathList.sort();
  _pathList.unique(); 
  std::list<std::string>::iterator iter = _pathList.begin();
  getcwd(currDir, 256);
  while( iter != _pathList.end() )
    {
      if( ((*iter).empty()) || (chdir((*iter).c_str()) != 0) )
	{
	  SLOG << "PathHandler::addPath: Invalid Directory: "
	       <<  (*iter).c_str() << " Not added."
	       << endl;
	  iter = _pathList.erase( iter );
	}
      else
	{
	  if( ((*iter)[(*iter).length()-1] != '/' )  &&
	      ((*iter)[(*iter).length()-1] != '\\')    )
	    {
#ifdef WIN32
	      (*iter).append( "\\" );
#else
	      (*iter).append( "/"  );
#endif
	    }
	  ++iter; 
	} 
    }
  chdir(currDir);
}

void PathHandler::subPath( const Char8* pathList )
{
  std::list<std::string>& pathes = _parser.parsePathList( pathList );
  std::list<std::string>::iterator iter = pathes.begin();
  while( iter != pathes.end() )
    {
      if( !(*iter).empty() )
	{
	  if( ((*iter)[(*iter).length()-1] != '/' )  &&
	      ((*iter)[(*iter).length()-1] != '\\')    )
	    {
#ifdef WIN32
	      (*iter).append( "\\" );
#else
	      (*iter).append( "/"  );
#endif
	    }
	  _pathList.remove( *iter );
	}
      ++iter;
    }
}

void PathHandler::setBaseFile( const Char8* fileName )
{
  std::list<std::string>& path = _parser.parsePathList( fileName );
  _baseFilePath = _parser.extractPathName( path.front().c_str() );
  if( (_baseFilePath[_baseFilePath.length()-1] != '/' )  &&
      (_baseFilePath[_baseFilePath.length()-1] != '\\')    )
    {
#ifdef WIN32
      _baseFilePath.append( "\\" );
#else
      _baseFilePath.append( "/"  );
#endif
    } 
}

void PathHandler::clearBaseFile( void )
{
  _baseFilePath.erase();
}

std::string PathHandler::findFile( const Char8* fileName )
{
  std::list<std::string>::iterator iter = _pathList.begin();
  std::string fullName;
  int fileHandle;
  if( !_baseFilePath.empty() )
    {
      fullName.assign( _baseFilePath );
      fullName.append( _parser.extractFileName(fileName) );
      if( (fileHandle=open(fullName.c_str(), O_RDONLY)) > 0 )
	{
	  close(fileHandle);
	  return fullName;
	}
    }
  for( ; iter != _pathList.end(); ++iter )
    {
      fullName.assign( *iter );
      fullName.append( _parser.extractFileName(fileName) );
      if( (fileHandle=open(fullName.c_str(), O_RDONLY)) > 0 )
	{
	  close(fileHandle);
	  return fullName;
	}
    }
  return std::string();
}

void PathHandler::clearPathList(void)
{
  _pathList.clear();
}




#endif









