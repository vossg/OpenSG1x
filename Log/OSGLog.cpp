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

#include <stdio.h>
#include <stdarg.h>

#include "OSGLog.h"
#include "OSGBaseFunctions.h"

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Support Class
//---------------------------------------------------------------------------

void LogBuf::setCallback ( LogBuf::Callback cb, void *clientData, 
                           Bool flushData )
{
    std::list<LogBuf::Chunk*>::iterator cI;
    LogBuf::Chunk *chunk;

    if (cb) {
        if (flushData) {
            for (cI = _chunkBag.begin(); cI != _chunkBag.end(); cI++) 
                if ((chunk = *cI))
                    cb(chunk->data,chunk->size,clientData);
        }

        _callback = cb;
        _clientData = clientData;
    }
}

void LogBuf::removeCallback ( void )
{
    _callback = 0;
}

void LogBuf::write (const char *buffer, streamsize size)
{
    Chunk *chunk = 0;
    Callback cb;

    if (_enabled) {

        chunk = new Chunk;
        chunk->size = size;
        chunk->data = new char [size];
        memcpy (chunk->data, buffer, size);

        _chunkBag.push_back(chunk);

        delete chunk;
    }
    
    if ((cb = _callback))
        cb(buffer,size,_clientData);
}

int LogBuf::overflow(int c)
{
    if (!pptr())
        return EOF;
    
    if (c != EOF) {

        // Put character into write buffer
        *pptr() = c; 
        pbump(1);

        // Flush write buffer
        streamsize size = pptr() -  pbase();
        if (size > 0) {
            write(pbase(), size);
            pbump(-size);
        }
    }
  
    return 0;
}

int LogBuf::sync(void)
{
    if (!pptr())
        return EOF;

    // Flush write buffer
    streamsize size = pptr() -  pbase();
    if (size > 0) {
        write(pbase(), size);
        pbump(-size);
    }

    return 0;
}

streamsize LogBuf::xsputn(const char *buffer, streamsize size)
{
    if (size > 0) {

        if (!pptr())
            return 0;

        streamsize s = epptr() - pptr();
        if (s >= size) {
            // Put it into the write buffer
            memcpy(pptr(), buffer, size);
            pbump(size);
        }
        else {
            // Flush write buffer
            s = pptr() - pbase();
            if (s > 0) {
                write(pbase(), s);
                pbump(-s);
            }

            // Write data
            write(buffer, size);
        }
    }

    return size;
}

void LogBuf::clearChunkBag(void) 
{
    std::list<LogBuf::Chunk*>::iterator cI;

    for (cI = _chunkBag.begin(); cI != _chunkBag.end(); ++cI)
        delete *cI;

    _chunkBag.clear();
}

LogBuf::LogBuf(unsigned int bufferSize)
    : streambuf(), _enabled(true), _callback(0), _clientData(0)
{
    setg(0, 0, 0);

    if (bufferSize > 0) {
        char *buffer = new char[bufferSize];
        setp(buffer, buffer + bufferSize - 1);
    }
    else
        setp(0, 0);
}

LogBuf::LogBuf(const LogBuf &obj)
    : streambuf(obj)
{
    cerr << "ERROR: Running LogBug copy constructor\n" << endl;
    cerr << flush;
}

LogBuf::~LogBuf()
{
    delete [] pbase();
    _callback = 0;
}

/** \var LogType Log::_logType;
 *  \brief  holds the log type
 */

/** \var LogLevel Log::_logLevel;
 *  \brief holds the log level
 */

/** \var fstream Log::_fileStream;
 *  \brief file stream 
 */

/** \var LogOStream *Log::_streamVec[6];
 *  \brief stream vector
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSG_BASE_DLLMAPPING LogP OSG::osgLogP = NULL;

/*! \brief holds the nil buffer 
 */
Log::nilbuf *Log::_nilbufP    = NULL;
ostream     *Log::_nilstreamP = NULL;

char Log::cvsid[] = "@(#)$Id: $";

const char *Log::_levelName[] = {
    "LOG", "FATAL", "WARNING", "NOTICE", "INFO", "DEBUG", 0
};


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

Log::Log(LogType logType, LogLevel logLevel) :
    ostream( _nilbufP == NULL ? _nilbufP = new Log::nilbuf() : _nilbufP), 
    _logType   (logType), 
    _logLevel  (logLevel), 
    _fileStream(),
    _headerElem(0),
    _moduleHandling(LOG_MODULE_ALL)
{   

    if(_nilstreamP == NULL)
        _nilstreamP = new ostream(_nilbufP);

    for(UInt32 i = 0; i < sizeof(_streamVec)/sizeof(LogOStream *); i++)
    {
#ifdef OSG_HAS_NILBUF
        _streamVec[i] = new LogOStream(_nilbufP);
#else
        _streamVec[i] = new LogOStream(_nilStreamP->rdbuf());
#endif
    }

    setHeaderElem (LOG_TYPE_HEADER);
    _refTime = getSystemTime();

    setLogLevel(logLevel);
}

/*! \brief Constructor which takes a log file name
 */

Log::Log(const char *fileName, LogLevel logLevel) :
    ostream( _nilbufP == NULL ? _nilbufP = new Log::nilbuf() : _nilbufP), 
    _logType   (LOG_FILE), 
    _logLevel  (logLevel), 
    _fileStream(),
    _headerElem(0),
    _moduleHandling(LOG_MODULE_ALL)
{

    if(_nilstreamP == NULL)
        _nilstreamP = new ostream(_nilbufP);

    for(UInt32 i = 0; i < sizeof(_streamVec)/sizeof(LogOStream *); i++)
    {
#ifdef OSG_HAS_NILBUF
        _streamVec[i] = new LogOStream(_nilbufP);
#else
        _streamVec[i] = new LogOStream(_nilStreamP->rdbuf());
#endif
    }

    _refTime = getSystemTime();

    setHeaderElem (LOG_TYPE_HEADER);
    setLogFile (fileName);
    setLogLevel(logLevel);
}

/** \brief Destructor
 */

Log::~Log(void)
{
    setLogFile(0,true);
}

/*------------------------------ access -----------------------------------*/

/*! \brief set method for attribute _headerElem
 */
void Log::setHeaderElem(UInt32 elemMask, Bool force )
{
    char *env;

    if (!force && (this == osgLogP) && (env = getenv( "OSG_LOG_HEADER" ) ) )
    {
        osgLog() << "Log::setHeaderElem: overriden by envvar OSG_LOG_HEADER '" 
                 << env << "'." << endLog;  
        elemMask = LogHeaderElem(atoi(env));
    }

    _headerElem = elemMask;
}

/*! \brief add method for attribute _headerElem
 */
void Log::addHeaderElem(LogHeaderElem elem, Bool force )
{
    setHeaderElem((_headerElem | elem),force);
}

/*! \brief delete method for attribute _headerElem
 */
void Log::delHeaderElem(LogHeaderElem elem, Bool force )
{
    setHeaderElem((_headerElem & ~elem),force);
}

/*! \brief check for a single headerElem
 */
Bool Log::hasHeaderElem(LogHeaderElem elem) 
{
    return (_headerElem & elem);
}

void Log::addModuleHandling(LogModuleHandling handling, 
                            Bool              OSG_CHECK_ARG(force))
{
    _moduleHandling |= handling;
}

void Log::delModuleHandling(LogModuleHandling handling, 
                            Bool              OSG_CHECK_ARG(force))
{
    _moduleHandling &= ~handling;
}

void Log::addModuleName(const Char8 *module, Bool isStatic)
{
    Module m;
    int len;

    if (module && *module) {
        _moduleList.push_back(m);

        if (isStatic) {
            _moduleList.back().name = module;
            _moduleList.back().isStatic = true;
        }
        else {
            len = strlen(module);
            _moduleList.back().name = new char[len+1];
            strcpy(const_cast<char*>(_moduleList.back().name),module);
            _moduleList.back().isStatic = false;            
        }
    }
}

void Log::delModuleName(const Char8 *OSG_CHECK_ARG(module))
{
}

Bool Log::hasModule(const Char8 *module)
{
    Bool retCode = false;
    list<Module>::iterator mI;

    if (module && *module) {
        for (mI = _moduleList.begin();retCode || (mI != _moduleList.end()); ++mI) 
            retCode = (mI->isStatic) ? 
                (module == mI->name) : (!strcmp(module,mI->name));
    }

    return retCode;
}

Bool Log::checkModule(const Char8 *module)
{
    Bool retCode = false;
    list<Module>::iterator mI;

    if (_moduleHandling != LOG_MODULE_NONE) {
        if (_moduleHandling == LOG_MODULE_ALL) 
            retCode = true;
        else
            if (module && &module) {
                if (hasModule(module)) {
                    if (_moduleHandling & LOG_MODULE_KNOWN)
                        retCode = true;
                }
                else {
                    if (_moduleHandling & LOG_MODULE_UNKNOWN)
                        retCode = true;
                }
            }
            else
                if (_moduleHandling & LOG_MODULE_UNDEFINED)
                    retCode = true;
    }

    return retCode;
}


/*! \brief set method for attribute logType 
 */

void Log::setLogType(LogType logType, Bool force) 
{
    char * et;
    static char *typenames[]    = 
    {
        "none", 
        "-",
        "stdout", 
        "stderr", 
        "file",
        "buffer",
        NULL
    };

    static LogType types[] = 
    {
        LOG_NONE, 
        LOG_STDOUT, 
        LOG_STDOUT, 
        LOG_STDERR, 
        LOG_FILE,
        LOG_BUFFER
    };

    static int typeCount = sizeof(types)/sizeof(LogType);
    int lt,i;                               

    if(!force && (this == osgLogP) && (et = getenv( "OSG_LOG_TYPE" ) ) )
    {
        osgLog() << "Log::setLogType: overriden by envvar OSG_LOG_TYPE '" 
                 << et << "'." << endl; 

        if(sscanf(et, "%d", &lt) != 1)
        {               
            for(i = 0; typenames[i]; i++)
            {
                if( ! stringcasecmp(et, typenames[i] ))
                {
                    _logType = types[i];
                    break;
                }
            }

            if(! typenames[i])
            {
                _logType = LOG_STDERR;
                osgLog() << "Log::setLogType: couldn't interpret envvar, "
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

/*! \brief get method for attribute logType 
 */

LogType Log::getLogType(void)
{ 
    return _logType; 
}

/*! \brief set method for attribute logLevel 
 */

void Log::setLogLevel(LogLevel logLevel, Bool force)
{ 
    char * el;
    static char *levelnames[] = { "log", "fatal", "warning", "notice", 
                                  "info", "debug", NULL };
    static LogLevel levels[] = { LOG_LOG, LOG_FATAL, LOG_WARNING, 
                                 LOG_NOTICE, LOG_INFO, LOG_DEBUG };
    static int levelCount = sizeof(levels)/sizeof(LogLevel);
    int ll,i;                               

    if(!force && (this == osgLogP) && (el = getenv( "OSG_LOG_LEVEL" ) ) )
    {
        osgLog() << "OSGLog::setLogLevel: overriden by envvar OSG_LOG_LEVEL '" 
                 << el << "'." << endl; 

        if(sscanf(el, "%d", &ll) != 1)
        {
                
            for(i = 0; levelnames[i]; i++)
            {
                if( ! stringcasecmp(el, levelnames[i] ))
                {
                    _logLevel = levels[i];
                    break;
                }
            }

            if(! levelnames[i])
            {
                _logLevel = LOG_DEBUG;
                osgLog() << "Log::setLogLevel: couldn't interpret envvar, "
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

/*! \brief get method for attribute logLevel 
 */

LogLevel Log::getLogLevel(void) 
{
    return _logLevel; 
}

/*! \brief method to set and activate the log file 
 */

void Log::setLogFile(const Char8 *fileName, Bool force)
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

    if( !force && (this == osgLogP) && (name = getenv( "OSG_LOG_FILE" ))) 
    {
        osgLog() << "Log::setLogFile: overriden by envvar OSG_LOG_FILE '" 
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


/*! \brief print for C-interface helper method 
 */

void Log::doLog(char * format, ...)
{
    char buffer[1000];
    va_list args;
    
    va_start( args, format );

#ifdef OSG_HAS_VSNPRINTF
    vsnprintf( buffer, sizeof(buffer)-1, format, args );
#else
    vsprintf( buffer, format, args );
#endif

    lock();
	*this << buffer;
	*this << std::flush;
    unlock();

    va_end( args );
}

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*! \brief reconnects the streams for the current settings 
 */

void Log::connect(void)  
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
        case LOG_BUFFER:
            this->bp = _logBuf;
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
        case LOG_BUFFER:
            this->rdbuf(&_logBuf);
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


void OSG::initLog(void)
{
#ifdef OSG_HAS_NILBUF
    if(Log::_nilbufP == NULL)
        Log::_nilbufP = new Log::nilbuf();
#else
    if(Log::_nilstreamP == NULL)
        Log::_nilstreamP = new fstream("/dev/null", ios::out);
#endif

    if(osgLogP == NULL)
    {
        osgLogP = new Log();

        osgLogP->setLogLevel(OSG_DEFAULT_LOG_LEVEL);
        osgLogP->setLogFile (NULL                 );
        osgLogP->setLogType (OSG_DEFAULT_LOG_TYPE );
    }
}
