/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *         contact: dirk@opensg.org, vossg@igd.fhg.de, jbehr@zgdv.de         *
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

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <stdio.h>
#include <stdarg.h>

#include "OSGLog.h"
#include "OSGBaseFunctions.h"

OSG_USING_NAMESPACE

/** \enum OSGVecBase::VectorSizeE
 *  \brief 
 */

/** \var OSGVecBase::VectorSizeE OSGVecBase::_iSize
 * 
 */

/** \fn const char *OSGVecBase::getClassname(void)
 *  \brief Classname
 */

/** \var OSGValueTypeT OSGVecBase::_values[iSize];
 *  \brief Value store
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSGLogP OSG::osgLogP = NULL;

#ifdef OSG_HAS_NILBUF
OSGLog::nilbuf *OSGLog::_nilbufP    = NULL;
#else
fstream        *OSGLog::_nilStreamP = NULL;
#endif

char OSGLog::cvsid[] = "@(#)$Id: $";

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

/** \brief Constructor
 */

OSGLog::OSGLog(OSGLogType logType, OSGLogLevel logLevel) :
#ifdef OSG_HAS_NILBUF
	ostream(_nilbufP), 
#else
	ostream(_nilStreamP->rdbuf()), 
#endif
    _logType   (logType), 
    _logLevel  (logLevel), 
    _fileStream()
{	
	for(OSGUInt32 i = 0; i < sizeof(_streamVec)/sizeof(OSGLogOStream *); i++)
    {
#ifdef OSG_HAS_NILBUF
		_streamVec[i] = new OSGLogOStream(_nilbufP);
#else
		_streamVec[i] = new OSGLogOStream(_nilStreamP->rdbuf());
#endif
    }

	setLogLevel(logLevel);
}

OSGLog::OSGLog(const char *fileName, OSGLogLevel logLevel) :
#ifdef OSG_HAS_NILBUF
	ostream(_nilbufP), 
#else
	ostream(_nilStreamP->rdbuf()), 
#endif
    _logType   (LOG_FILE), 
    _logLevel  (logLevel), 
    _fileStream()
{
	for(OSGUInt32 i = 0; i < sizeof(_streamVec)/sizeof(OSGLogOStream *); i++)
    {
#ifdef OSG_HAS_NILBUF
		_streamVec[i] = new OSGLogOStream(_nilbufP);
#else
		_streamVec[i] = new OSGLogOStream(_nilStreamP->rdbuf());
#endif
    }

	setLogFile (fileName);
	setLogLevel(logLevel);
}

/** \brief Destructor
 */

OSGLog::~OSGLog(void)
{
	setLogFile(0);
}

/*------------------------------ access -----------------------------------*/

void OSGLog::setLogType(OSGLogType logType) 
{
	char * et;
	static char *typenames[]    = 
    {
        "none", 
        "-",
        "stdout", 
        "stderr", 
        "file",
        NULL
    };

	static OSGLogType types[] = 
    {
        LOG_NONE, 
        LOG_STDOUT, 
        LOG_STDOUT, 
        LOG_STDERR, 
        LOG_FILE 
    };

	static int typeCount = sizeof(types)/sizeof(OSGLogType);
	int lt,i;				   				

	if((this == osgLogP) && (et = getenv( "OSG_LOG_TYPE" ) ) )
	{
		osgLog() << "OSGLog::setLogType: overriden by envvar OSG_LOG_TYPE '" 
                 << et << "'." << endl;	

		if(sscanf(et, "%d", &lt) != 1)
		{				
			for(i = 0; typenames[i]; i++)
            {
				if( ! osgstrcasecmp(et, typenames[i] ))
				{
					_logType = types[i];
					break;
				}
			}

			if(! typenames[i])
			{
				_logType = LOG_STDERR;
				osgLog() << "OSGLog::setLogType: couldn't interpret envvar, "
                         << "set to LOG_STDERR!" << endl;					   
			}
		}
		else 
		{
			if(lt < 0)
            {
				lt = 0;
            }
			else 
            {
				if(lt >= typeCount)
					lt = typeCount - 1;
            }

			_logType = types[lt];
		}
	}
	else
    {
		_logType = logType; 
    }

    connect(); 
}

OSGLogType OSGLog::getLogType(void)
{ 
    return _logType; 
}

void OSGLog::setLogLevel(OSGLogLevel logLevel)
{ 
	char * el;
	static char *levelnames[] = { "log", "fatal", "warning", "notice", 
                                  "info", "debug", NULL };
	static OSGLogLevel levels[] = { LOG_LOG, LOG_FATAL, LOG_WARNING, 
                                    LOG_NOTICE, LOG_INFO, LOG_DEBUG };
	static int levelCount = sizeof(levels)/sizeof(OSGLogLevel);
	int ll,i;				   				

	if((this == osgLogP) && (el = getenv( "OSG_LOG_LEVEL" ) ) )
	{
		osgLog() << "OSGLog::setLogLevel: overriden by envvar OSG_LOG_LEVEL '" 
                 << el << "'." << endl;	

		if(sscanf(el, "%d", &ll) != 1)
		{
				
			for(i = 0; levelnames[i]; i++)
            {
				if( ! osgstrcasecmp(el, levelnames[i] ))
				{
					_logLevel = levels[i];
					break;
				}
			}

			if(! levelnames[i])
			{
				_logLevel = LOG_DEBUG;
				osgLog() << "OSGLog::setLogLevel: couldn't interpret envvar, "
                         << "set to LOG_DEBUG!" << endl;					   
			}
		}
		else 
		{

			if (ll < 0)
            {
				ll = 0;
            }
			else 
            {
				if (ll >= levelCount)
					ll = levelCount - 1;
            }

			_logLevel = levels[ll];
		}
	}
	else
    {
		_logLevel = logLevel; 
    }    

	connect() ; 
}

OSGLogLevel OSGLog::getLogLevel(void) 
{
    return _logLevel; 
}

void OSGLog::setLogFile(const char * fileName)
{
	const char *name;

#ifdef OSG_STREAM_HAS_ISOPEN
	if (_fileStream.is_open())
#else
    if (_fileStream.rdbuf()->is_open())
#endif
    {
        _fileStream.close();
    }

	if( (this == osgLogP) && (name = getenv( "OSG_LOG_FILE" ))) 
    {
		osgLog() << "OSGLog::setLogFile: overriden by envvar OSG_LOG_FILE '" 
                 << name << "'." << endl;					   				
	}
	else
    {
		name = fileName;
    }

	if(name && *name) 
    {
		_fileStream.open(name, ios::out);

#ifdef OSG_STREAM_HAS_ISOPEN
		if (_fileStream.is_open()) 
#else
        if (_fileStream.rdbuf()->is_open())
#endif
        {
            _logType = LOG_FILE;
            connect();
        }
	}
}

void OSGLog::doLog(char * format, ...)
{
	char buffer[1000];
	va_list args;
	
	va_start( args, format );

#ifdef OSG_HAS_VSNPRINTF
	vsnprintf( buffer, sizeof(buffer)-1, format, args );
#else
	vsprintf( buffer, format, args );
#endif

	*this << buffer;

	va_end( args );
}

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

void OSGLog::connect(void)
{
	int i;

#ifndef OSG_STREAM_RDBUF_HAS_PARAM
	switch(_logType) 
    {
        case LOG_STDOUT:
            this->bp = cout.rdbuf();
            break;
        case LOG_STDERR:
            this->bp = cerr.rdbuf();
            break;
        case LOG_FILE:
            this->bp = _fileStream.rdbuf();
            break;
        case LOG_NONE:
        default:
            this->bp = _nilStreamP->rdbuf();
            break;
	}
#else
	switch(_logType) 
    {
        case LOG_STDOUT:
            this->rdbuf(cout.rdbuf());
            break;
        case LOG_STDERR:
            this->rdbuf(cerr.rdbuf());
            break;
        case LOG_FILE:
            this->rdbuf(_fileStream.rdbuf());
            break;
        case LOG_NONE:
        default:
            this->rdbuf(_nilbufP);
            break;
	}
#endif

	for (i = 0; i < int(sizeof(_streamVec)/sizeof(ostream*)); ++i) 
    {
		if (i <= _logLevel)
        {
			_streamVec[i]->setrdbuf(this->rdbuf());
        }
        else
        {
#ifdef OSG_HAS_NILBUF
			_streamVec[i]->setrdbuf(_nilbufP);
#else
			_streamVec[i]->setrdbuf(_nilStreamP->rdbuf());
#endif
        }
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



///---------------------------------------------------------------------------
///  FUNCTION: 
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters: 
//p: 
///
//g: GlobalVars:
//g: 
///
//r: Return:
//r: 
///
//c: Caution:
//c: 
///
//a: Assumptions:
//a: 
///
//d: Description:
//d: 
///
//s: SeeAlso:
//s: 
///---------------------------------------------------------------------------

