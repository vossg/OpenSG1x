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

#include <list>

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILELOG
#       define OSG_LOG_DLLMAPPING __declspec(dllexport)
#   else
#       if defined(OSG_NEW_DLLS) && (defined(OSG_COMPILEBASE))
#           define OSG_LOG_DLLMAPPING __declspec(dllexport)
#       else
#           define OSG_LOG_DLLMAPPING __declspec(dllimport)
#       endif
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

enum LogHeaderElem 
{
	  LOG_NONE_HEADER          = 0,
		LOG_BEGIN_NEWLINE_HEADER = 1,
		LOG_TYPE_HEADER          = 2,
	  LOG_TIMESTAMP_HEADER     = 4,
		LOG_MODULE_HEADER        = 8,
		LOG_FILE_HEADER          = 16,
		LOG_LINE_HEADER          = 32,
		LOG_END_NEWLINE_HEADER   = 64,
		LOG_ALL_HEADER           = 127
};
			
enum LogModuleHandling 
{
	  LOG_MODULE_NONE           = 0,
		LOG_MODULE_KNOWN          = 1,
		LOG_MODULE_UNKNOWN        = 2,
		LOG_MODULE_UNDEFINED      = 4,
		LOG_MODULE_ALL            = 7,	
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

		void lock(void) {;}   // TODO: implement

		void unlock(void) {;} // TODO: implement

		virtual void addHeaderElem(LogHeaderElem elem);

		virtual void delHeaderElem(LogHeaderElem elem);

		virtual void addModuleHandling  (LogModuleHandling handling);

		virtual void delModuleHandling  (LogModuleHandling handling);

		virtual void addModuleName(const char *module, bool isStatic = false);

		virtual void delModuleName(const char *module);

		bool hasModule(const char *module);

		bool checkModule(const char *module);

		LogType getLogType(void);
		void       setLogType(LogType logType);

		LogLevel getLogLevel(void);
		void        setLogLevel(LogLevel logLevel); 
		bool checkLevel(LogLevel logLevel);

		void        setLogFile (const Char8 *fileName);

		inline
		ostream &stream(LogLevel level);

		inline
		ostream &nilstream(void);

	  inline 
		ostream &doHeader ( LogLevel level, const char *module, 
												const char *file, int line );

  	void  doLog (char * format, ...);
									
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

	static nilbuf  *_nilbufP;
	static ostream *_nilstreamP;

		static const char *_levelName[];

	LogType     _logType;
	LogLevel    _logLevel;

	fstream        _fileStream;

	LogOStream *_streamVec[6];

	int _headerElem;

	int _moduleHandling;

	struct Module {
		const char *name;
		bool isStatic;
		Module() :name(0),isStatic(true) {;}
	};
			
	list<Module> _moduleList;
	
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

#ifndef OSG_LOG_MODULE
#define OSG_LOG_MODULE "UNKNOWN MODUL"
#endif

extern OSG_LOG_DLLMAPPING LogP osgLogP;


inline OSG_LOG_DLLMAPPING void    initLog   (void);
inline OSG_LOG_DLLMAPPING Log     &osgLog    (void);
inline OSG_LOG_DLLMAPPING ostream &osgStartLog ( bool logHeader,
																								 LogLevel level, 
																								 const char *module,
																								 const char *file, 
																								 int line);

inline OSG_LOG_DLLMAPPING void  indentLog (UInt32 indent, ostream &stream);

#define SLOG \
osgStartLog(true,OSG::LOG_LOG,OSG_LOG_MODULE, __FILE__, __LINE__)

#define SFATAL \
osgStartLog(true,OSG::LOG_FATAL,OSG_LOG_MODULE, __FILE__, __LINE__)

#define SWARNING \
osgStartLog(true,OSG::LOG_WARNING,OSG_LOG_MODULE, __FILE__, __LINE__)

#define SNOTICE \
osgStartLog(true,OSG::LOG_NOTICE,OSG_LOG_MODULE, __FILE__, __LINE__)

#define SINFO \
osgStartLog(true,OSG::LOG_INFO,OSG_LOG_MODULE, __FILE__, __LINE__)



#define PLOG \
osgStartLog(false,OSG::LOG_LOG,OSG_LOG_MODULE, __FILE__, __LINE__)

#define PFATAL \
osgStartLog(false,OSG::LOG_FATAL,OSG_LOG_MODULE, __FILE__, __LINE__)

#define PWARNING \
osgStartLog(false,OSG::LOG_WARNING,OSG_LOG_MODULE, __FILE__, __LINE__)

#define PNOTICE \
osgStartLog(false,OSG::LOG_NOTICE,OSG_LOG_MODULE, __FILE__, __LINE__)

#define PINFO \
osgStartLog(false,OSG::LOG_INFO,OSG_LOG_MODULE, __FILE__, __LINE__)


// C interface, because it can be compiled away
// don't use varargs macros, because they are not supported everywhere
// use the (( )) convention instead

#define FLOG( par ) \
{	\
		osg::initLog(); \
	 osgStartLog(true,OSG::LOG_LOG,OSG_LOG_MODULE,__FILE__,__LINE__); \
   osg::osgLogP->doLog par;	\
   osg::osgLogP->unlock(); \
}

#define FFATAL( par )											\
{																	\
  osg::initLog(); \
  if (osgLogP->checkLevel(osg::LOG_FATAL)) { \
    osgStartLog(true,osg::LOG_FATAL,OSG_LOG_MODULE,__FILE__,__LINE__); \
    osg::osgLogP->doLog par;	\
    osg::osgLogP->unlock(); \
  } \
}

#define FWARNING( par )											\
{																	\
  osg::initLog(); \
  if (osgLogP->checkLevel(osg::LOG_WARNING)) { \
    osgStartLog(true,osg::LOG_WARNING,OSG_LOG_MODULE,__FILE__,__LINE__); \
    osg::osgLogP->doLog par;	\
    osg::osgLogP->unlock(); \
  } \
}

#define FNOTICE( par )											\
{																	\
  osg::initLog(); \
  if (osgLogP->checkLevel(osg::LOG_NOTICE)) { \
    osgStartLog(true,osg::LOG_NOTICE,OSG_LOG_MODULE,__FILE__,__LINE__); \
    osg::osgLogP->doLog par;	\
    osg::osgLogP->unlock(); \
  } \
}

#define FINFO( par )												\
{																	\
  osg::initLog(); \
  if (osgLogP->checkLevel(osg::LOG_INFO)) { \
    osgStartLog(true,osg::LOG_INFO,OSG_LOG_MODULE,__FILE__,__LINE__); \
    osg::osgLogP->doLog par;	\
    osg::osgLogP->unlock(); \
  } \
}

#ifdef OSG_DEBUG
#define FDEBUG( par )											\
{																	\
  osg::initLog(); \
  if (osgLogP->checkLevel(osg::LOG_DEBUG)) { \
    osgStartLog(true,osg::LOG_DEBUG,OSG_LOG_MODUL,__FILE__,__LINE__) \
    osg::osgLogP->doLog par;	\
    osg::osgLogP->unlock(); \
  } \
}
#else
#define FDEBUG( par )
#endif

#define FASSERT( condition, doExit )   \
{        \
	if (!condition)  \
  {                \
    osg::osgLog().lock(); \
    osg::osgLog().stream(osg::LOG_FATAL) \
      << OSG_LOG_MODULE << ':' << __FILE__ << ':' << __LINE__ \
      << "FATAL ASSERT: " \
      << (doExit ? "exit system" : "try to keep running") \
      << flush << endl; \
    osg::osgLog().unlock(); \
	  if (doExit) \
			exit(-1); \
	} \
} \

#define FFASSERT( condition, doExit, par )   \
{        \
	if (!condition)  \
  {                \
    OSG::osgLog().lock(); \
    OSG::osgLog().stream(OSG::LOG_FATAL) \
      << OSG_LOG_MODULE << ':' << __FILE__ << ':' << __LINE__ \
      << "FATAL ASSERT: " \
      << (doExit ? "exit system" : "try to keep running") \
      << flush << endl; \
	  OSG::osgLogP->doLog par \
    OSG::osgLog().unlock(); \
	  if (doExit) \
			exit(-1); \
	} \
} \

OSG_END_NAMESPACE

inline OSG_LOG_DLLMAPPING ostream &endLog(ostream &strm);

#include <OSGLog.inl>

#endif /* _OSGLOG_H_ */
