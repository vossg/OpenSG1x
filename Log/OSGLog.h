#ifndef OSGLOG_CLASS_DECLARATION
#define OSGLOG_CLASS_DECLARATION

#include <OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <fstream>
#else
#include <fstream.h>
#endif

OSG_BEGIN_NAMESPACE

enum OSGLogType  { LOG_NONE = 0, LOG_STDOUT, LOG_STDERR, LOG_FILE };
enum OSGLogLevel { LOG_LOG  = 0, LOG_FATAL, LOG_WARNING, LOG_NOTICE,
									 LOG_INFO, LOG_DEBUG };

/** Message logger class.
*
* handles info,warning and error messages
*
* @author jbehr, Thu Oct 21 19:25:45 1999
*/

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

class OSGLog : public ostream {

private:

    friend inline void initOSGLog(void);

	/** defines a nil buffer */
	class nilbuf : public streambuf {	};

#ifdef OSG_HAS_NILBUF
	/** holds the nil buffer */
	static nilbuf  *_nilbufP;
#else
    static fstream *_nilstreamP;
#endif

  /** holds the log type */
	OSGLogType _logType;

	/** hosts the log level */
	OSGLogLevel _logLevel;

	/** file stream */
	fstream _fileStream;

	/** stream vector */
	OSGLogOStream *_streamVec[6];

protected:

	/** reconnects the streams for the current settings */
	void connect(void );

public:

  /** Default Constructor */
  OSGLog (OSGLogType logType = LOG_STDERR, OSGLogLevel logLevel = LOG_NOTICE );

  /** Constructor which takes a log file name*/
  OSGLog (const char *fileName, OSGLogLevel logLevel = LOG_NOTICE );

  /** Copy Constructor */
  OSGLog (const OSGLog &obj);

  /** Destructor */
  virtual ~OSGLog (void);

  /** get method for attribute logType */
  virtual OSGLogType getLogType (void) { return _logType; }

  /** set method for attribute logType */
  virtual void setLogType (OSGLogType logType) 
		{ _logType = logType; connect() ; }

  /** get method for attribute logLevel */
  virtual OSGLogLevel getLogLevel (void) { return _logLevel; }

  /** set method for attribute logLevel */
  virtual void setLogLevel (OSGLogLevel logLevel); 

	/** method to set and activate the log file */
	virtual void setLogFile (const char *fileName);

	/** returns the error stream */
	ostream &stream(OSGLogLevel level) { return *(_streamVec[level]); }

	/** print for C-interface helper method */
	void doLog( char * format, ... );
	
};

typedef OSGLog* OSGLogP;

/** appOSGLog */
extern OSGLogP osgLogP;

inline void initOSGLog(void)
{
#ifdef OSG_HAS_NILBUF
    if(OSGLog::_nilbufP == NULL)
        OSGLog::_nilbufP = new OSGLog::nilbuf();
#else
    if(OSGLog::_nilStreamP == NULL)
        OSGLog::_nilStreamP = new fstream("/dev/null", ios::out);
#endif

	if(osgLogP == NULL)
		osgLogP = new OSGLog ( LOG_STDERR, LOG_NOTICE );
}

inline OSGLog & osgLog() 
{
	initOSGLog();
	return *osgLogP;
}

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

#endif // OSGLOG_CLASS_DECLARATION
