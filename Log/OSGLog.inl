/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *         contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de    *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------


#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



//---------------------------------------------------------------------------
//  FUNCTION: 
//---------------------------------------------------------------------------
//:  Example for the head comment of a function
//---------------------------------------------------------------------------
//
//p: Paramaters: 
//p: 
//
//g: GlobalVars:
//g: 
//
//r: Return:
//r: 
//
//c: Caution:
//c: 
//
//a: Assumptions:
//a: 
//
//d: Description:
//d: 
//
//s: SeeAlso:
//s: 
//---------------------------------------------------------------------------

OSG_BEGIN_NAMESPACE

inline 
Log &osgLog() 
{
    initLog();

    return *osgLogP;
}

inline 
void indentLog(UInt32 indent, ostream &stream)
{
    for(UInt32 i = 0; i < indent; i++)
    {
        stream << " ";
    }
}

inline 
ostream &osgStartLog(      Bool      logHeader,
                           LogLevel  level, 
                           const Char8    *module,
                           const Char8    *file, 
                           UInt32    line)
{
    initLog();

    osgLogP->lock();

    if(osgLogP->checkModule(module)) 
    {
        if(logHeader)
            osgLogP->doHeader(level,module,file,line);

        return osgLogP->stream(level);
    }
    else
        return osgLogP->nilstream();
}

inline 
Bool Log::checkLevel(LogLevel level)
{
    return (_logLevel >= level) ? true : false;
}

inline
Time Log::getRefTime(void)
{
    return _refTime;
}

inline
void Log::setRefTime(Time refTime)
{
    _refTime = refTime;
}

inline
void Log::resetRefTime(void)
{
    _refTime = osg::getSystemTime();
}

inline
LogBuf & Log::getLogBuf(void)
{
  return _logBuf;
}

inline
ostream &Log::stream(LogLevel level)
{
    return *(_streamVec[level]); 
}

inline
ostream &Log::nilstream(void)
{
    return *_nilstreamP;
}

inline 
ostream &Log::doHeader(      LogLevel  level, 
                             const Char8    *module, 
                             const Char8    *file, 
                             UInt32    line)
{
    LogOStream & sout = *(_streamVec[level]);

    if (_headerElem) 
    {
        if (_headerElem & LOG_BEGIN_NEWLINE_HEADER)
            sout << endl;   
        
        if (_headerElem & LOG_TYPE_HEADER)
            sout << _levelName[level] << ":";

        if (_headerElem & LOG_TIMESTAMP_HEADER) 
            sout << " ts: " << (osg::getSystemTime() - _refTime);

        if (module && *module && (_headerElem & LOG_MODULE_HEADER))
            sout << " mod: " << module;

        if ( file && *file && (_headerElem & LOG_FILE_HEADER)) {
            sout << " file: " << file;
            if (_headerElem & LOG_LINE_HEADER)
                sout << ':' << line;
        }
        else
            if (_headerElem & LOG_LINE_HEADER)
                sout << " line:" << line;

        if (_headerElem & LOG_END_NEWLINE_HEADER)
            sout << endl;   
        else
            sout << ' ';
    }

    return sout;
}

inline  
ostream &endLog(ostream &strm)
{
    osg::initLog();

    osg::osgLogP->unlock();
    
    strm << endl;
    return strm;
}

OSG_END_NAMESPACE


