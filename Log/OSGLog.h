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

class OSG_DLLEXPORT LogOStream : public ostream
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

class OSG_DLLEXPORT Log : public ostream 
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

    friend inline void initLog(void);

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
	class nilbuf : public streambuf {	};

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
extern LogP osgLogP;

inline OSG_DLLEXPORT void  initLog(void);
inline OSG_DLLEXPORT Log  &osgLog    (void); 
inline OSG_DLLEXPORT void  indentLog (UInt32 indent, ostream &stream);

#define SLOG \
osgLog() << __FILE__ << ':' << __LINE__ \
<< ':' << " log: " << endl << "  "

#define SFATAL \
osgLog().stream(OSG::LOG_FATAL) << __FILE__ << ':' << __LINE__ \
<< ':' << " fatal: " << endl << "  "

#define SWARNING \
osgLog().stream(OSG::LOG_WARNING) << __FILE__ << ':' << __LINE__ \
<< ':' << " warning: " << endl << "  "

#define SNOTICE \
osgLog().stream(OSG::LOG_NOTICE) << __FILE__ << ':' << __LINE__ \
<< ':' << " notice: " << endl << "  "

#define SINFO \
osgLog().stream(OSG::LOG_INFO) << __FILE__ << ':' << __LINE__ \
<< ':' << " info: " << endl << "  "

#define SDEBUG \
osgLog().stream(OSG::LOG_DEBUG) << __FILE__ << ':' << __LINE__ \
<< ':' << " debug: " << endl << "  "


#define PLOG     osgLog() 
#define PFATAL   osgLog().stream(OSG::LOG_FATAL) 
#define PWARNING osgLog().stream(OSG::LOG_WARNING) 
#define PNOTICE  osgLog().stream(OSG::LOG_NOTICE)
#define PINFO    osgLog().stream(OSG::LOG_INFO)
#define PDEBUG   osgLog().stream(OSG::LOG_DEBUG)


// C interface, because it can be compiled away
// don't use varargs macros, because they are not supported everywhere
// use the (( )) convention instead

#define FLOG( par )												\
{				                            \
   initLog();										\
   osgLogP->doLog( "%s:%d: log:\n  ",  __FILE__,  __LINE__ );		\
   osgLogP->doLog par;												\
}

#define FFATAL( par )											\
{																	\
  initLog();    \
	if ( osgLogP->getLogLevel() >= OSG::LOG_FATAL )					\
	{																\
    osgLogP->doLog( "%s:%d: fatal:\n  ",  __FILE__,  __LINE__ );	\
    osgLogP->doLog par;											\
	}																\
}

#define FWARNING( par )											\
{																	\
  initLog();         \
	if ( osgLogP->getLogLevel() >= OSG::LOG_WARNING )					\
	{																\
    osgLogP->doLog( "%s:%d: warning:\n  ",  __FILE__,  __LINE__ );\
    osgLogP->doLog par;											\
	}																\
}

#define FNOTICE( par )											\
{																	\
  initLog();         \
	if ( osgLogP->getLogLevel() >= OSG::LOG_NOTICE )					\
	{																\
		osgLogP->doLog( "%s:%d: notice:\n  ",  __FILE__,  __LINE__ );	\
		osgLogP->doLog par;											\
	}																\
}

#define FINFO( par )												\
{																	\
  initLog();         \
	if ( osgLogP->getLogLevel() >= OSG::LOG_INFO )					\
	{																\
		osgLogP->doLog( "%s:%d: info:\n  ",  __FILE__,  __LINE__ );	\
		osgLogP->doLog par;											\
	}																\
}

#define FDEBUG( par )											\
{																	\
  initLog();         \
	if ( osgLogP->getLogLevel() >= OSG::LOG_DEBUG )					\
	{																\
		osgLogP->doLog( "%s:%d: debug:\n  ",  __FILE__,  __LINE__ );	\
		osgLogP->doLog par;											\
	}																\
}

#define FASSERT( condition, doExit )   \
{        \
	if (!condition)  \
  {                \
    osgLog().stream(OSG::LOG_FATAL) \
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
    osgLog().stream(OSG::LOG_FATAL) \
      << __FILE__ << ':' << __LINE__ \
      << "FATAL ASSERT: " \
      << (doExit ? "exit system" : "try to keep running") \
      << flush << endl; \
	  osgLogP->doLog par \
	  if (doExit) \
			exit(-1); \
	} \
} \

OSG_END_NAMESPACE

#include <OSGLog.inl>

#endif /* _OSGLOG_H_ */
