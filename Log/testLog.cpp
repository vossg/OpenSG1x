
#include "OSGConfig.h"

#define __EXTENSIONS__	// ??? what's this ???
#include <stdlib.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif

#define OSG_LOG_MODULE "LOG-TEST"

#include "OSGLog.h"
#include "OSGBaseFunctions.h"

using OSG::osgLogP;
using OSG::osgLog;
using OSG::initLog;
using OSG::endLog;

int main (int argc, char **argv)
{
	osgLog().setLogLevel ( OSG::LOG_WARNING );

	OSG::SLOG     << "log test" << OSG::endLog;
	OSG::SFATAL   << "fatal test" << OSG::endLog;
	OSG::SWARNING << "warning test" << OSG::endLog;
	OSG::SNOTICE  << "notice test" << OSG::endLog;
	OSG::SINFO    << "info test" << OSG::endLog;

	// C-style log test

	FLOG(( "C-log test: %d\n", OSG::LOG_LOG ));
	FFATAL(( "C-fatal test: %d\n", OSG::LOG_FATAL ));
	FWARNING(( "C-warning test: %d\n", OSG::LOG_WARNING ));
	FNOTICE(( "C-notice test: %d\n", OSG::LOG_NOTICE ));
	FINFO(( "C-into test: %d\n", OSG::LOG_INFO ));
	FDEBUG(( "C-debug test: %d\n", OSG::LOG_DEBUG ));

	// Envvar test:

	cerr << endl << "OSG_LOG_LEVEL=3 test" << endl;
	OSG::putenv("OSG_LOG_LEVEL=3");
	osgLog().setLogLevel ( OSG::LOG_FATAL );

	FLOG(( "C-log test: %d\n", OSG::LOG_LOG ));
	FFATAL(( "C-fatal test: %d\n", OSG::LOG_FATAL ));
	FWARNING(( "C-warning test: %d\n", OSG::LOG_WARNING ));
	FNOTICE(( "C-notice test: %d\n", OSG::LOG_NOTICE ));
	FINFO(( "C-into test: %d\n", OSG::LOG_INFO ));
	FDEBUG(( "C-debug test: %d\n", OSG::LOG_DEBUG ));

	cerr << endl << "OSG_LOG_LEVEL=info test" << endl;
	OSG::putenv("OSG_LOG_LEVEL=info");
	osgLog().setLogLevel ( OSG::LOG_WARNING );

	FLOG(( "C-log test: %d\n", OSG::LOG_LOG ));
	FFATAL(( "C-fatal test: %d\n", OSG::LOG_FATAL ));
	FWARNING(( "C-warning test: %d\n", OSG::LOG_WARNING ));
	FNOTICE(( "C-notice test: %d\n", OSG::LOG_NOTICE ));
	FINFO(( "C-into test: %d\n", OSG::LOG_INFO ));
	FDEBUG(( "C-debug test: %d\n", OSG::LOG_DEBUG ));

	cerr << endl << "OSG_LOG_LEVEL=gargl test" << endl;
	OSG::putenv("OSG_LOG_LEVEL=gargl");
	osgLog().setLogLevel ( OSG::LOG_WARNING );

	FLOG(( "C-log test: %d\n", OSG::LOG_LOG ));
	FFATAL(( "C-fatal test: %d\n", OSG::LOG_FATAL ));
	FWARNING(( "C-warning test: %d\n", OSG::LOG_WARNING ));
	FNOTICE(( "C-notice test: %d\n", OSG::LOG_NOTICE ));
	FINFO(( "C-into test: %d\n", OSG::LOG_INFO ));
	FDEBUG(( "C-debug test: %d\n", OSG::LOG_DEBUG ));
	
	FASSERT ( 0, true );
 
	return 0;
}

