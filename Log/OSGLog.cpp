// System declarations

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif

#include <stdio.h>
#include <stdarg.h>

// Application declarations


// Class declarations
#include "OSGLog.h"
#include "OSGBaseTypes.h"
#include "OSGBaseFunctions.h"

OSG_USING_NAMESPACE

// Static Class Varible implementations: 

OSGLogP OSG::osgLogP = NULL;

#ifdef OSG_HAS_NILBUF
OSGLog::nilbuf *OSGLog::_nilbufP    = NULL;
#else
fstream        *OSGLog::_nilStreamP = NULL;
#endif

//----------------------------------------------------------------------
// Method: OSGLog
// Author: jbehr
// Date:   Thu Oct 21 19:25:45 1999
// Description:
//         Default Constructor
//----------------------------------------------------------------------
OSGLog::OSGLog (OSGLogType logType, OSGLogLevel logLevel ) :
#ifdef OSG_HAS_NILBUF
	ostream(_nilbufP), 
#else
	ostream(_nilStreamP->rdbuf()), 
#endif
    _logType(logType), 
    _logLevel(logLevel), 
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

	setLogLevel( logLevel );
}

//----------------------------------------------------------------------
// Method: OSGLog
// Author: jbehr
// Date:   Thu Oct 21 19:25:45 1999
// Description:
//         Default Constructor
//----------------------------------------------------------------------
OSGLog::OSGLog (const char *fileName, OSGLogLevel logLevel ) :
#ifdef OSG_HAS_NILBUF
	ostream(_nilbufP), 
#else
	ostream(_nilStreamP->rdbuf()), 
#endif
    _logType(LOG_FILE), 
    _logLevel(logLevel), 
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

	setLogFile( fileName );
	setLogLevel( logLevel );
}

//----------------------------------------------------------------------
// Method: OSGLog
// Author: jbehr
// Date:   Thu Oct 21 19:25:45 1999
// Description:
//         Copy Constructor
//----------------------------------------------------------------------
OSGLog::OSGLog (const OSGLog &obj ) :
#ifdef OSG_HAS_NILBUF
	ostream(_nilbufP), 
#else
	ostream(_nilStreamP->rdbuf()), 
#endif
    _logType(obj._logType), 
    _logLevel(obj._logLevel), 
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

	setLogLevel( _logLevel );
}

//----------------------------------------------------------------------
// Method: ~OSGLog
// Author: jbehr
// Date:   Thu Oct 21 19:25:45 1999
// Description:
//         Destructor
//----------------------------------------------------------------------
OSGLog::~OSGLog (void )
{
	setLogFile(0);
}

//----------------------------------------------------------------------
// Method: ~OSGLog
// Author: jbehr
// Date:   Thu Oct 21 19:25:45 1999
// Description:
//         Destructor
//----------------------------------------------------------------------
void OSGLog::setLogLevel (OSGLogLevel logLevel)
{ 
	char * el;
	static char *levelnames[] = { "log", "fatal", "warning", "notice", 
                                  "info", "debug", NULL };
	static OSGLogLevel levels[] = { LOG_LOG, LOG_FATAL, LOG_WARNING, 
                                    LOG_NOTICE, LOG_INFO, LOG_DEBUG };
	static int levelCount = sizeof(levels)/sizeof(OSGLogLevel);
	int ll,i;				   				

	if ( (this == osgLogP) && (el = getenv( "OSG_LOG_LEVEL" ) ) )
	{
		osgLog() << "OSGLog::setLogLevel: overriden by envvar OSG_LOG_LEVEL '" 
						 << el << "'." << endl;	
		if ( sscanf( el, "%d", &ll ) != 1 )
		{
				
			for ( i = 0; levelnames[i]; i++ )
				if ( ! osgstrcasecmp( el, levelnames[i] ) )
				{
					_logLevel = levels[i];
					break;
				}
			
			if ( ! levelnames[i] )
			{
				_logLevel = LOG_DEBUG;
				osgLog() << "OSGLog::setLogLevel: couldn't interpret envvar, "
								 << "set to LOG_DEBUG!" << endl;					   
			}
		}
		else 
		{

			if (ll < 0)
				ll = 0;
			else 
				if (ll >= levelCount)
					ll = levelCount - 1;
			_logLevel = levels[ ll ];

		}
	}
	else
		_logLevel = logLevel; 
	connect() ; 
}

//----------------------------------------------------------------------
// Method: connect
// Author: jbehr
// Date:   Thu Oct 21 19:25:45 1999
// Description:
//         method to set the log file
//----------------------------------------------------------------------
void OSGLog::connect (void)
{
	int i;

#ifndef OSG_STREAM_RDBUF_HAS_PARAM
	switch(_logType) {
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
	switch(_logType) {
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

//----------------------------------------------------------------------
// Method: setOSGLogFile
// Author: jbehr
// Date:   Thu Oct 21 19:25:45 1999
// Description:
//         method to set the log file
//----------------------------------------------------------------------
void OSGLog::setLogFile (const char * fileName )
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

	if ( (this == osgLogP) && (name = getenv( "OSG_LOG_FILE" ))) {
		osgLog() << "OSGLog::setLogFile: overriden by envvar OSG_LOG_FILE '" 
						 << name << "'." << endl;					   				
	}
	else
		name = fileName;

	if (name && *name) {
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

//----------------------------------------------------------------------
// Method: doLog
// Author: dreiners
// Description:
//         C-style log base method
//----------------------------------------------------------------------
void OSGLog::doLog ( char * format, ... )
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
