
#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#ifdef WIN32
  #include <winsock.h>
  #include <time.h>
#else
  #include <sys/types.h>
  #include <sys/time.h>
#endif      
 
#include "OSGTime.h"

using OSG::OSGTime;
  
//----------------------------------------------------------------------
// Function: getSystemTime
// Author:   jbehr
// Date:     Thu Dec 11 23:58:38 1997
// Description:
//           Class Copy Constructor
//----------------------------------------------------------------------
OSGTime getSystemTime (void)
{
	OSGTime time;

#ifdef WIN32
	
	/*  use _ftime() funktion, is less precise  
	struct _timeb timebuffer;
	_ftime(&timebuffer);
	time = double (timebuffer.millitm) / 1000.0 + double (timebuffer.time);
	*/

	time = double(timeGetTime()) / 1000.0;

#else

	struct timeval tv;
	gettimeofday(&tv, 0);
	time = double(tv.tv_usec) / 1000000.0 + double(tv.tv_sec);

#endif

	return time;
}
