/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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


#ifndef _OSGLOG_H_
#define _OSGLOG_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <fstream>
#else
#include <fstream.h>
#endif

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILELOG
#       define OSG_LOG_DLLMAPPING __declspec(dllexport)
#   else
#       define OSG_LOG_DLLMAPPING __declspec(dllimport)
#   endif
#else
#define OSG_LOG_DLLMAPPING
#endif

/*! \defgroup LogLib OpenSG Log Library
    OpenSG Log Library 
 */

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Enums
//---------------------------------------------------------------------------

/*! \ingroup LogLib
 *  \brief Log types
 */

enum LogType  
{ 
    LOG_NONE = 0, 
    LOG_STDOUT, 
    LOG_STDERR, 
    LOG_FILE 
};

/*! \ingroup LogLib
 *  \brief Log Levels
 */

enum LogLevel 
{
    LOG_LOG  = 0, 
    LOG_FATAL, 
    LOG_WARNING, 
    LOG_NOTICE,
    LOG_INFO, 
    LOG_DEBUG 
};

//---------------------------------------------------------------------------
//  Support Class
//---------------------------------------------------------------------------

/*! \ingroup LogLib
 *  \brief Logger ostream, required to fix some problems between the different
 *         plattforms
 */

class OSG_LOG_DLLMAPPING LogOStream : public ostream
{
  public:

    LogOStream(streambuf *buf) : ostream(buf) {};
    virtual ~LogOStream(void) {};

#ifdef OSG_STREAM_RDBUF_HAS_PARAM
    void setrdbuf(streambuf *buf) { rdbuf(buf); };
#else
    void setrdbuf(streambuf *buf) { bp = buf; };
#endif
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup LogLib
 *  \brief Message logger class, handles info,warning and error messages
 */



class OSG_LOG_DLLMAPPING Log : public ostream 
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "Log"; }
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    Log(LogType  logType  = LOG_STDERR, 
        LogLevel logLevel = LOG_NOTICE);

    Log(const char *fileName, LogLevel logLevel = LOG_NOTICE );

    virtual ~Log(void); 

    /*------------------------- your_category -------------------------------*/

    virtual LogType getLogType(void);
    virtual void       setLogType(LogType logType);

    virtual LogLevel getLogLevel(void);
    virtual void        setLogLevel(LogLevel logLevel); 

	virtual void        setLogFile (const Char8 *fileName);

	ostream &stream(LogLevel level);

	void     doLog (char * format, ...);

    /*------------------------- your_operators ------------------------------*/

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	void connect(void );

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef ostream Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    friend OSG_LOG_DLLMAPPING inline void initLog(void);

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

	/** defines a nil buffer */
	class OSG_LOG_DLLMAPPING nilbuf : public streambuf {	};

#ifdef OSG_HAS_NILBUF
	static nilbuf  *_nilbufP;
#else
    static fstream *_nilstreamP;
#endif

	LogType     _logType;
	LogLevel    _logLevel;

	fstream        _fileStream;

	LogOStream *_streamVec[6];

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    Log(const Log &source);
    void operator =(const Log &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef Log *LogP;

/** appLog */
#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILELOG
        extern OSG_LOG_DLLMAPPING LogP osgLogP;
#   else
        OSG_LOG_DLLMAPPING LogP osgLogP;
#   endif 
#else
extern LogP osgLogP;
#endif

inline OSG_LOG_DLLMAPPING void  initLog   (void);
inline OSG_LOG_DLLMAPPING Log  &osgLog    (void); 
inline OSG_LOG_DLLMAPPING void  indentLog (UInt32 indent, ostream &stream);

#define SLOG \
OSG::osgLog() << __FILE__ << ':' << __LINE__ \
<< ':' << " log: " << endl << "  "

#define SFATAL \
OSG::osgLog().stream(OSG::LOG_FATAL) << __FILE__ << ':' << __LINE__ \
<< ':' << " fatal: " << endl << "  "

#define SWARNING \
OSG::osgLog().stream(OSG::LOG_WARNING) << __FILE__ << ':' << __LINE__ \
<< ':' << " warning: " << endl << "  "

#define SNOTICE \
OSG::osgLog().stream(OSG::LOG_NOTICE) << __FILE__ << ':' << __LINE__ \
<< ':' << " notice: " << endl << "  "

#define SINFO \
OSG::osgLog().stream(OSG::LOG_INFO) << __FILE__ << ':' << __LINE__ \
<< ':' << " info: " << endl << "  "

#define SDEBUG \
OSG::osgLog().stream(OSG::LOG_DEBUG) << __FILE__ << ':' << __LINE__ \
<< ':' << " debug: " << endl << "  "


#define PLOG     OSG::osgLog() 
#define PFATAL   OSG::osgLog().stream(OSG::LOG_FATAL) 
#define PWARNING OSG::osgLog().stream(OSG::LOG_WARNING) 
#define PNOTICE  OSG::osgLog().stream(OSG::LOG_NOTICE)
#define PINFO    OSG::osgLog().stream(OSG::LOG_INFO)
#define PDEBUG   OSG::osgLog().stream(OSG::LOG_DEBUG)


// C interface, because it can be compiled away
// don't use varargs macros, because they are not supported everywhere
// use the (( )) convention instead

#define FLOG( par )												\
{				                            \
   OSG::initLog();										\
   OSG::osgLogP->doLog( "%s:%d: log:\n  ",  __FILE__,  __LINE__ );		\
   OSG::osgLogP->doLog par;												\
}

#define FFATAL( par )											\
{																	\
    OSG::initLog();    \
	if ( OSG::osgLogP->getLogLevel() >= OSG::LOG_FATAL )					\
	{																\
    OSG::osgLogP->doLog( "%s:%d: fatal:\n  ",  __FILE__,  __LINE__ );	\
    OSG::osgLogP->doLog par;											\
	}																\
}

#define FWARNING( par )											\
{																	\
    OSG::initLog();         \
	if ( OSG::osgLogP->getLogLevel() >= OSG::LOG_WARNING )					\
	{																\
    OSG::osgLogP->doLog( "%s:%d: warning:\n  ",  __FILE__,  __LINE__ );\
    OSG::osgLogP->doLog par;											\
	}																\
}

#define FNOTICE( par )											\
{																	\
    OSG::initLog();         \
	if ( OSG::osgLogP->getLogLevel() >= OSG::LOG_NOTICE )					\
	{																\
		OSG::osgLogP->doLog( "%s:%d: notice:\n  ",  __FILE__,  __LINE__ );	\
		OSG::osgLogP->doLog par;											\
	}																\
}

#define FINFO( par )												\
{																	\
    OSG::initLog();         \
	if ( OSG::osgLogP->getLogLevel() >= OSG::LOG_INFO )					\
	{																\
		OSG::osgLogP->doLog( "%s:%d: info:\n  ",  __FILE__,  __LINE__ );	\
		OSG::osgLogP->doLog par;											\
	}																\
}

#define FDEBUG( par )											\
{																	\
    OSG::initLog();         \
	if ( OSG::osgLogP->getLogLevel() >= OSG::LOG_DEBUG )					\
	{																\
		OSG::osgLogP->doLog( "%s:%d: debug:\n  ",  __FILE__,  __LINE__ );	\
		OSG::osgLogP->doLog par;											\
	}																\
}

#define FASSERT( condition, doExit )   \
{        \
	if (!condition)  \
  {                \
    OSG::osgLog().stream(OSG::LOG_FATAL) \
      << __FILE__ << ':' << __LINE__ \
      << "FATAL ASSERT: " \
      << (doExit ? "exit system" : "try to keep running") \
      << flush << endl; \
	  if (doExit) \
			exit(-1); \
	} \
} \

#define FFASSERT( condition, doExit, par )   \
{        \
	if (!condition)  \
  {                \
    OSG::osgLog().stream(OSG::LOG_FATAL) \
      << __FILE__ << ':' << __LINE__ \
      << "FATAL ASSERT: " \
      << (doExit ? "exit system" : "try to keep running") \
      << flush << endl; \
	  OSG::osgLogP->doLog par \
	  if (doExit) \
			exit(-1); \
	} \
} \

OSG_END_NAMESPACE

#include <OSGLog.inl>

#endif /* _OSGLOG_H_ */
