#ifndef OSGTIME_CLASS_DECLARATION
#define OSGTIME_CLASS_DECLARATION

/* Time (msec).
 *
 * used mostly for runtime measurements and timestamps
 *
 *
 * @author jbehr, Mon Dec 22 11:32:31 1997
 */

#include <OSGConfig.h>

OSG_BEGIN_NAMESPACE

typedef double OSGTime;

typedef OSGTime* OSGTimeP;

OSGTime getSystemTime(void);

OSG_END_NAMESPACE

#endif // OSGTIME_CLASS_DECLARATION
