
#include "OSGConfig.h"

#define __EXTENSIONS__
#include <stdlib.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif

#include "OSGLog.h"

using OSG::osgLogP;
using OSG::osgLog;
using OSG::initLog;

int main (int argc, char **argv)
{
	osgLog().setLogLevel ( OSG::LOG_WARNING );

	SLOG     << "log test" << endl;
	SFATAL   << "fatal test" << endl;
	SWARNING << "warning test" << endl;
	SNOTICE  << "notice test" << endl;
	SINFO    << "info test" << endl;
	SDEBUG   << "debug test" << endl;

	// C-style log test

	FLOG(( "C-log test: %d\n", OSG::LOG_LOG ));
	FFATAL(( "C-fatal test: %d\n", OSG::LOG_FATAL ));
	FWARNING(( "C-warning test: %d\n", OSG::LOG_WARNING ));
	FNOTICE(( "C-notice test: %d\n", OSG::LOG_NOTICE ));
	FINFO(( "C-into test: %d\n", OSG::LOG_INFO ));
	FDEBUG(( "C-debug test: %d\n", OSG::LOG_DEBUG ));

	// Envvar test:

	cerr << endl << "OSG_LOG_LEVEL=3 test" << endl;
	_putenv("OSG_LOG_LEVEL=3");
	osgLog().setLogLevel ( OSG::LOG_FATAL );

	FLOG(( "C-log test: %d\n", OSG::LOG_LOG ));
	FFATAL(( "C-fatal test: %d\n", OSG::LOG_FATAL ));
	FWARNING(( "C-warning test: %d\n", OSG::LOG_WARNING ));
	FNOTICE(( "C-notice test: %d\n", OSG::LOG_NOTICE ));
	FINFO(( "C-into test: %d\n", OSG::LOG_INFO ));
	FDEBUG(( "C-debug test: %d\n", OSG::LOG_DEBUG ));

	cerr << endl << "OSG_LOG_LEVEL=info test" << endl;
	_putenv("OSG_LOG_LEVEL=info");
	osgLog().setLogLevel ( OSG::LOG_WARNING );

	FLOG(( "C-log test: %d\n", OSG::LOG_LOG ));
	FFATAL(( "C-fatal test: %d\n", OSG::LOG_FATAL ));
	FWARNING(( "C-warning test: %d\n", OSG::LOG_WARNING ));
	FNOTICE(( "C-notice test: %d\n", OSG::LOG_NOTICE ));
	FINFO(( "C-into test: %d\n", OSG::LOG_INFO ));
	FDEBUG(( "C-debug test: %d\n", OSG::LOG_DEBUG ));

	cerr << endl << "OSG_LOG_LEVEL=gargl test" << endl;
	_putenv("OSG_LOG_LEVEL=gargl");
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

