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

#ifndef _OSGLOG_H_
#define _OSGLOG_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBaseTypes.h>
#include <OSGTime.h>

#include <fstream>
#include <list>

/*! \defgroup LogLib OpenSG Log Library
    OpenSG Log Library
 */

OSG_BEGIN_NAMESPACE

/*! \ingroup LogLib
 *  \brief Log types
 */

enum LogType
{
    LOG_NONE = 0,
    LOG_STDOUT,
    LOG_STDERR,
    LOG_FILE,
    LOG_BUFFER
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
    LOG_MODULE_ALL            = 7
};

/*! \ingroup LogLib
 *  \brief Logger ostream, required to fix some problems between the different
 *         plattforms
 */

class OSG_BASE_DLLMAPPING LogOStream : public ostream
{
  public:

    LogOStream(streambuf *buf) : ostream(buf) {};
    virtual ~LogOStream(void) {};

#ifdef OSG_STREAM_RDBUF_HAS_PARAM
    void setrdbuf(streambuf *buf) { ostream::rdbuf(buf); };
#else
    void setrdbuf(streambuf *buf) { bp = buf; };
#endif
};

/*! \ingroup LogLib
 *  \brief stream buf helper class; creates a chunk buffer of all messages
 *         which can ge fetched by a application (e.g. gui)
 */

class OSG_BASE_DLLMAPPING LogBuf : public streambuf
{

public:

  /// only temporary until the functors work with all compiler
  typedef void (*Callback)( const char *data, int size,
                            void *clientData );
 
  /// output chunk
  struct Chunk {
    char *data;
    int size;
    Chunk (void) : data(0), size(0) {;}
    ~Chunk (void) { delete data; }
  };

  /*---------------------------------------------------------------------*/
  /*! \name                   Constructors                               */
  /*! \{                                                                 */    
  
  LogBuf (unsigned int bufferSize = 1024);
  LogBuf(const LogBuf &);
    
  /*! \}                                                                 */
  /*---------------------------------------------------------------------*/
  /*! \name                   Destructors                                */
  /*! \{                                                                 */
  virtual ~LogBuf();

  /*! \}                                                                 */
  /*---------------------------------------------------------------------*/
  /*! \name                   Class Specific                             */
  /*! \{                                                                 */    
  /// clear the chunk bag
  void clearChunkBag(void);
    
  /// get the enabled value  
  inline
    bool getEnabled (void) { return _enabled; }

  /// set the enabled value
  inline
    void setEnabled (bool value = true) { _enabled = value; }
    
  /*! \}                                                                 */
  /*---------------------------------------------------------------------*/
  /*! \name                   Callback handling                          */
  /*! \{                                                                 */    
  void setCallback ( Callback cb, void *clientData = 0,
                     bool flushData = false );
  void removeCallback ( void );

private:

  bool _enabled;
 
  list<Chunk*> _chunkBag;
  
  Callback _callback;
  void* _clientData; 

  const LogBuf &operator=(const LogBuf &);
  void write (const char *buffer, std::streamsize size);

  /*! \}                                                                 */
  /*---------------------------------------------------------------------*/
  /*! \name                   Callback handling                          */
  /*! \{                                                                 */   
  virtual int overflow(int c);
  virtual int sync(void);
  virtual std::streamsize xsputn(const char *buffer, std::streamsize size);

};

/*! \ingroup LogLib
 *  \brief Message logger class, handles info,warning and error messages
 */

class OSG_BASE_DLLMAPPING Log : public ostream
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "Log"; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Log(LogType  logType  = LOG_STDERR,
        LogLevel logLevel = LOG_NOTICE);

    Log(const char *fileName, LogLevel logLevel = LOG_NOTICE );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Log(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    void lock(void) {;}   // TODO: implement

    void unlock(void) {;} // TODO: implement

    virtual void setHeaderElem(UInt32 elemMask, bool force = false);
    virtual void addHeaderElem(LogHeaderElem elem, bool force = false);
    virtual void delHeaderElem(LogHeaderElem elem, bool force = false);
    virtual bool hasHeaderElem(LogHeaderElem elem);

    virtual void addModuleHandling(LogModuleHandling handling, bool force = false);
    virtual void delModuleHandling(LogModuleHandling handling, bool force = false);

    virtual void addModuleName(const Char8 *module, bool isStatic = false);
    virtual void delModuleName(const Char8 *module);

    bool hasModule  (const Char8 *module);
    bool checkModule(const Char8 *module);

    LogType getLogType(void);
    void    setLogType(LogType logType, bool force = false );

    LogLevel getLogLevel(void);
    void     setLogLevel(LogLevel logLevel, bool force = false );
    bool     checkLevel (LogLevel logLevel);

    void     setLogFile (const Char8 *fileName, bool force = false );

    inline Time getRefTime(void);
    inline void setRefTime(Time refTime);
    inline void resetRefTime(void);

    inline LogBuf & getLogBuf(void);

    inline ostream &stream   (LogLevel level);
    inline ostream &nilstream(void);

    inline ostream &doHeader (LogLevel  level,
                              const Char8    *module,
                              const Char8    *file,
                                    UInt32    line);

    void  doLog (const char * format, ...);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */
          
    void connect(void );

    /*! \}                                                                 */
  private:

    typedef ostream Inherited;

    friend OSG_BASE_DLLMAPPING void doInitLog(void);

    static char cvsid[];

    /*---------------------------------------------------------------------*/
    /*! \name                     Fields                                   */
    /*! \{                                                                 */
    
    class OSG_BASE_DLLMAPPING nilbuf : public streambuf {};

    static nilbuf  *_nilbufP;
    static ostream *_nilstreamP;

    static const char *_levelName[];

    LogType     _logType;
    LogLevel    _logLevel;

    fstream     _fileStream;

    LogBuf      _logBuf;

    LogOStream *_streamVec[6];

    UInt32      _headerElem;

    UInt32      _moduleHandling;

    struct Module
    {
        const Char8 *name;
              bool   isStatic;

        Module() : name(NULL), isStatic(true) {}
    };

    list<Module> _moduleList;

    Time _refTime;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Log(const Log &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Operators                                  */
    /*! \{                                                                 */
    
    void operator =(const Log &source);
    
    /*! \}                                                                 */    
};
typedef Log *LogP;

#ifndef OSG_LOG_MODULE
#define OSG_LOG_MODULE "UNKNOWN MODULE"
#endif

extern OSG_BASE_DLLMAPPING LogP osgLogP;


       OSG_BASE_DLLMAPPING void     doInitLog  (void);
inline OSG_BASE_DLLMAPPING void     initLog    (void);
inline OSG_BASE_DLLMAPPING Log     &osgLog     (void);
inline OSG_BASE_DLLMAPPING ostream &osgStartLog(      bool      logHeader,
                                                      LogLevel  level,
                                                const Char8    *module,
                                                const Char8    *file,
                                                      UInt32    line);
inline OSG_BASE_DLLMAPPING void  indentLog     (UInt32   indent,
                                                ostream &stream);

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
{   \
        osg::initLog(); \
     osg::osgStartLog(true,OSG::LOG_LOG,OSG_LOG_MODULE,__FILE__,__LINE__); \
   osg::osgLogP->doLog par; \
   osg::osgLogP->unlock(); \
}

#define FFATAL( par )                                           \
{                                                                   \
  osg::initLog(); \
  if (osg::osgLogP->checkLevel(osg::LOG_FATAL)) { \
    osg::osgStartLog(true,osg::LOG_FATAL,OSG_LOG_MODULE,__FILE__,__LINE__); \
    osg::osgLogP->doLog par;    \
    osg::osgLogP->unlock(); \
  } \
}

#define FWARNING( par )                                         \
{                                                                   \
  osg::initLog(); \
  if (osg::osgLogP->checkLevel(osg::LOG_WARNING)) { \
    osg::osgStartLog(true,osg::LOG_WARNING,OSG_LOG_MODULE,__FILE__,__LINE__); \
    osg::osgLogP->doLog par;    \
    osg::osgLogP->unlock(); \
  } \
}

#define FNOTICE( par )                                          \
{                                                                   \
  osg::initLog(); \
  if (osg::osgLogP->checkLevel(osg::LOG_NOTICE)) { \
    osg::osgStartLog(true,osg::LOG_NOTICE,OSG_LOG_MODULE,__FILE__,__LINE__); \
    osg::osgLogP->doLog par;    \
    osg::osgLogP->unlock(); \
  } \
}

#define FINFO( par )                                                \
{                                                                   \
  osg::initLog(); \
  if (osg::osgLogP->checkLevel(osg::LOG_INFO)) { \
    osg::osgStartLog(true,osg::LOG_INFO,OSG_LOG_MODULE,__FILE__,__LINE__); \
    osg::osgLogP->doLog par;    \
    osg::osgLogP->unlock(); \
  } \
}

#ifdef OSG_DEBUG
#define FDEBUG( par )                                           \
{                                                                   \
  osg::initLog(); \
  if (osg::osgLogP->checkLevel(osg::LOG_DEBUG)) { \
    osg::osgStartLog(true,osg::LOG_DEBUG,OSG_LOG_MODULE,__FILE__,__LINE__); \
    osg::osgLogP->doLog par;    \
    osg::osgLogP->unlock(); \
  } \
}
#else
#define FDEBUG( par ) ;
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

inline OSG_BASE_DLLMAPPING ostream &endLog(ostream &strm);

OSG_END_NAMESPACE

#include <OSGLog.inl>

#endif /* _OSGLOG_H_ */
