
#include "OSGConfig.h"

#include <stdlib.h>

#include <iostream>
#include <fstream>

#define OSG_LOG_MODULE "LOG-TEST"

#include "OSGLog.h"
#include "OSGBaseFunctions.h"

using OSG::osgLogP;
using OSG::osgLog;
using OSG::initLog;
using OSG::endLog;

void MyLogCallback(const char *pszText, int OSG_CHECK_ARG(size), void
*OSG_CHECK_ARG(pData))
{
    std::cerr << "MyLogCallback: " << pszText << std::endl;
}

int main (int argc, char **argv)
{
    osgLog().setLogLevel ( OSG::LOG_WARNING );

    SLOG     << "log test" << OSG::endLog;
    SFATAL   << "fatal test" << OSG::endLog;
    SWARNING << "warning test" << OSG::endLog;
    SNOTICE  << "notice test" << OSG::endLog;
    SINFO    << "info test" << OSG::endLog;

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

