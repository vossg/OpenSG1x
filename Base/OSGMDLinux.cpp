
#include <OSGConfig.h>

#ifdef OSG_USE_PTHREADS
#include <pthread.h>
#endif

extern "C"
{
    pthread_t gThreadSelf(void)
    {
        return pthread_self();
    }
}
