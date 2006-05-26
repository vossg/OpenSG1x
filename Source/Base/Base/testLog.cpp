
#include "OSGConfig.h"

#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <string>

#define OSG_LOG_MODULE "LOG-TEST"

#include "OSGLog.h"
#include "OSGBaseFunctions.h"

using OSG::osgLogP;
using OSG::osgLog;
using OSG::initLog;
using OSG::endLog;

void MyLogCallback(const char *pszText, int size, void
*OSG_CHECK_ARG(pData))
{
    std::string str(pszText, size);
    std::cerr << "MyLogCallback: " << str << std::endl;
}

int main (int argc, char **argv)
{
    osgLog().setHeaderElem ( osg::LOG_TYPE_HEADER | 
                             osg::LOG_MODULE_HEADER |
                             osg::LOG_TAB_HEADER |
                             osg::LOG_COLOR_HEADER, 
                             false );
    osgLog().setLogLevel ( OSG::LOG_WARNING );

    SLOG     << "log test" << OSG::endLog;
    SFATAL   << "fatal test" << OSG::endLog;
    SWARNING << "warning test" << OSG::endLog;
    SNOTICE  << "notice test" << OSG::endLog;
    SINFO    << "info test" << OSG::endLog;

    // Long log
    
    SLOG << "This is a very long log test that makes no sense at all, but "
            "it is long and that's the point of making "
            "a very long log test that makes no sense at all, but "
            "it is long and that's the point of making "
            "a very long log test that makes no sense at all, but "
            "it is long and that's the point of making "
            "a very long log test that makes no sense at all, but "
            "it is long and that's the point of making "
            "a very long log test that makes no sense at all, but "
            "it is long and that's the point!" << OSG::endLog;
   
    // C-style log test

    FLOG(( "C-log test: %d\n", OSG::LOG_LOG ));
    FFATAL(( "C-fatal test: %d\n", OSG::LOG_FATAL ));
    FWARNING(( "C-warning test: %d\n", OSG::LOG_WARNING ));
    FNOTICE(( "C-notice test: %d\n", OSG::LOG_NOTICE ));
    FINFO(( "C-into test: %d\n", OSG::LOG_INFO ));
    FDEBUG(( "C-debug test: %d\n", OSG::LOG_DEBUG ));

    // Envvar test:

    std::cerr << std::endl << "OSG_LOG_LEVEL=3 test" << std::endl;
    OSG::putenv("OSG_LOG_LEVEL=3");
    osgLog().setLogLevel ( OSG::LOG_FATAL );

    FLOG(( "C-log test: %d\n", OSG::LOG_LOG ));
    FFATAL(( "C-fatal test: %d\n", OSG::LOG_FATAL ));
    FWARNING(( "C-warning test: %d\n", OSG::LOG_WARNING ));
    FNOTICE(( "C-notice test: %d\n", OSG::LOG_NOTICE ));
    FINFO(( "C-into test: %d\n", OSG::LOG_INFO ));
    FDEBUG(( "C-debug test: %d\n", OSG::LOG_DEBUG ));

    std::cerr << std::endl << "OSG_LOG_LEVEL=info test" << std::endl;
    OSG::putenv("OSG_LOG_LEVEL=info");
    osgLog().setLogLevel ( OSG::LOG_WARNING );

    FLOG(( "C-log test: %d\n", OSG::LOG_LOG ));
    FFATAL(( "C-fatal test: %d\n", OSG::LOG_FATAL ));
    FWARNING(( "C-warning test: %d\n", OSG::LOG_WARNING ));
    FNOTICE(( "C-notice test: %d\n", OSG::LOG_NOTICE ));
    FINFO(( "C-into test: %d\n", OSG::LOG_INFO ));
    FDEBUG(( "C-debug test: %d\n", OSG::LOG_DEBUG ));

    std::cerr << std::endl << "OSG_LOG_LEVEL=gargl test" << std::endl;
    OSG::putenv("OSG_LOG_LEVEL=gargl");
    osgLog().setLogLevel ( OSG::LOG_WARNING );

    FLOG(( "C-log test: %d\n", OSG::LOG_LOG ));
    FFATAL(( "C-fatal test: %d\n", OSG::LOG_FATAL ));
    FWARNING(( "C-warning test: %d\n", OSG::LOG_WARNING ));
    FNOTICE(( "C-notice test: %d\n", OSG::LOG_NOTICE ));
    FINFO(( "C-into test: %d\n", OSG::LOG_INFO ));
    FDEBUG(( "C-debug test: %d\n", OSG::LOG_DEBUG ));
    
    // Check callback
    
    std::cerr << std::endl << "Callback test" << std::endl;
    OSG::osgLog().getLogBuf().setCallback(MyLogCallback, 0, true);
    OSG::osgLog().setLogType(OSG::LOG_BUFFER);
    SLOG << "test" << OSG::endLog;
    OSG::osgLog().setLogType(OSG::LOG_STDERR);
    
    FASSERT ( 0, true );
 
    return 0;
}

