
#include <stdio.h>
#include <unistd.h>

//#include <OSGBaseTypes.h>

#include <OSGBaseFunctions.h>
#include <OSGThread.h>
#include <OSGThreadManager.h>

#ifndef WIN32
pthread_key_t     saved_time_key;
#endif

OSG_USING_NAMESPACE

#define NUM_THREADS  4

OSGThread *gThreads[NUM_THREADS];
OSGUInt32  gLocalId[NUM_THREADS];

#if 0
void mapAspect(int id)
{
    OSGThread::setAspect(id);
}

void free_time(void *arg )
{
    struct timeval *gTimeVal = (struct timeval *)arg; 

    printf("(%d), free_time:\n", OSGThread::inqAspect());

    free(gTimeVal);
}

void save_the_time(void)
{
    struct timezone gTimeZone; 
    struct timeval *gTimeVal;

    gTimeVal = (struct timeval *)malloc(sizeof(struct timeval));
    
    gettimeofday(gTimeVal, &gTimeZone);
    
    printf("(%d), save_the_time: \t\t%ld %ld\n",
           G_Thread::inqAspect(), 
           gTimeVal->tv_sec, 
           gTimeVal->tv_usec);
    
    pthread_setspecific(saved_time_key, (void *)gTimeVal);
}

void what_time_did_i_save(void)
{
    int rtn;
    struct timeval *timep;

    timep = (timeval *) pthread_getspecific(saved_time_key);
    
    printf("(%d), what_time_did_i_save: \t%ld %ld\n",
           G_Thread::inqAspect(), timep->tv_sec, timep->tv_usec);

}  

#endif

void *thread_routine(void *arg)
{
    int *my_id = (int *) arg;
    
    printf("thread_routine %d\n", *my_id);

#if 0
    mapAspect(*my_id);
    
    save_the_time();
    
    what_time_did_i_save();
#endif
    
	fprintf(stderr, "BS\n");
#ifdef WIN32
	Sleep(2000);
#else
    sleep(2);
#endif
	fprintf(stderr, "AS\n");

    return(NULL); 
}

int main(void)
{
    fprintf(stderr, "Thread test started %x\n", thread_routine);

    osgInit(0, NULL);

    OSGThreadManager *gThreadManager = OSGThreadManager::the();

    for(OSGUInt32 i = 0; i < NUM_THREADS; i++)
    {
        gThreads[i] = gThreadManager->getThread(NULL);

        gLocalId[i] = i;

        if(gThreads[i] != NULL)
        {
            gThreads[i]->print();
            gThreads[i]->run(thread_routine,
                             1,
                             (void *) &(gLocalId[i]));
        }
        else
        {
            fprintf(stderr, "Thread %d create failed\n", i);
        }
    }

    for(OSGUInt32 j = 0; j < NUM_THREADS; j++)
    {
		fprintf(stderr, "Wait for %d\n", j);
        OSGThread::join(gThreads[j]);
    }

    fprintf(stderr, "Thread test finished\n");
}
