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


#ifndef _OSGLog_H_
#define _OSGLog_H_
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

enum OSGLogType  
{ 
    LOG_NONE = 0, 
    LOG_STDOUT, 
    LOG_STDERR, 
    LOG_FILE 
};

enum OSGLogLevel 
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

class OSGLogOStream : public ostream
{
  public:

    OSGLogOStream(streambuf *buf) : ostream(buf) {};
    virtual ~OSGLogOStream(void) {};

#ifdef OSG_STREAM_RDBUF_HAS_PARAM
    void setrdbuf(streambuf *buf) { rdbuf(buf); };
#else
    void setrdbuf(streambuf *buf) { bp = buf; };
#endif
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup baselib
 *  \brief Brief
 *
 *  detailed
 */

class OSGLog : public ostream 
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

    static const char *getClassname(void) { return "OSGLog"; }
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /** Default Constructor */
    OSGLog(OSGLogType  logType  = LOG_STDERR, 
           OSGLogLevel logLevel = LOG_NOTICE);

    /** Constructor which takes a log file name*/
    OSGLog(const char *fileName, OSGLogLevel logLevel = LOG_NOTICE );

    virtual ~OSGLog(void); 

    /*------------------------- your_category -------------------------------*/

    /** get method for attribute logType */
    virtual OSGLogType getLogType(void);

    /** set method for attribute logType */
    virtual void setLogType(OSGLogType logType);

    /** get method for attribute logLevel */
    virtual OSGLogLevel getLogLevel(void);

    /** set method for attribute logLevel */
    virtual void setLogLevel(OSGLogLevel logLevel); 

	/** method to set and activate the log file */
	virtual void setLogFile(const char *fileName);

	/** returns the error stream */
	ostream &stream(OSGLogLevel level) { return *(_streamVec[level]); }

	/** print for C-interface helper method */
	void doLog( char * format, ... );

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

	/** reconnects the streams for the current settings */
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

    friend inline void initOSGLog(void);

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
	/** holds the nil buffer */
	static nilbuf  *_nilbufP;
#else
    static fstream *_nilstreamP;
#endif

    /** holds the log type */
	OSGLogType      _logType;

	/** hosts the log level */
	OSGLogLevel     _logLevel;

	/** file stream */
	fstream         _fileStream;

	/** stream vector */
	OSGLogOStream *_streamVec[6];

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    OSGLog(const OSGLog &source);
    void operator =(const OSGLog &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef OSGLog *OSGLogP;

/** appOSGLog */
extern OSGLogP osgLogP;

inline void    initOSGLog(void);
inline OSGLog &osgLog    (void); 


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
   initOSGLog();										\
   osgLogP->doLog( "%s:%d: log:\n  ",  __FILE__,  __LINE__ );		\
   osgLogP->doLog par;												\
}

#define FFATAL( par )											\
{																	\
  initOSGLog();    \
	if ( osgLogP->getLogLevel() >= OSG::LOG_FATAL )					\
	{																\
    osgLogP->doLog( "%s:%d: fatal:\n  ",  __FILE__,  __LINE__ );	\
    osgLogP->doLog par;											\
	}																\
}

#define FWARNING( par )											\
{																	\
  initOSGLog();         \
	if ( osgLogP->getLogLevel() >= OSG::LOG_WARNING )					\
	{																\
    osgLogP->doLog( "%s:%d: warning:\n  ",  __FILE__,  __LINE__ );\
    osgLogP->doLog par;											\
	}																\
}

#define FNOTICE( par )											\
{																	\
  initOSGLog();         \
	if ( osgLogP->getLogLevel() >= OSG::LOG_NOTICE )					\
	{																\
		osgLogP->doLog( "%s:%d: notice:\n  ",  __FILE__,  __LINE__ );	\
		osgLogP->doLog par;											\
	}																\
}

#define FINFO( par )												\
{																	\
  initOSGLog();         \
	if ( osgLogP->getLogLevel() >= OSG::LOG_INFO )					\
	{																\
		osgLogP->doLog( "%s:%d: info:\n  ",  __FILE__,  __LINE__ );	\
		osgLogP->doLog par;											\
	}																\
}

#define FDEBUG( par )											\
{																	\
  initOSGLog();         \
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
