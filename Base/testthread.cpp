
#include <stdio.h>

#ifdef WIN32
#include <windows.h>
#endif

#include <OSGThread.h>
#include <OSGThreadManager.h>
#include <OSGLock.h>
#include <OSGBaseFunctions.h>

#ifndef WIN32
pthread_key_t     saved_time_key;
#include <unistd.h>
#endif

OSG_USING_NAMESPACE

#define NUM_THREADS  4

Thread *gThreads[NUM_THREADS];
UInt32  gLocalId[NUM_THREADS];

Lock *pLock;


void *thread_routine(void *arg)
{
    int *my_id = (int *) arg;
    
    printf("thread_routine %d\n", *my_id);

#if 0
    mapAspect(*my_id);
    
    save_the_time();
    
    what_time_did_i_save();
#endif

    Thread::getCurrent()->block();
    
	fprintf(stderr, "Try Lock %d\n", *my_id);

    if(pLock->request() == true)
    {
        fprintf(stderr, "Got Lock %d\n", *my_id);
        osgsleep(3000);

        pLock->release();

        fprintf(stderr, "Release Lock %d\n", *my_id);
    }
    else
    {
        fprintf(stderr, "No Lock %d\n", *my_id);

        pLock->aquire();

        fprintf(stderr, "Got Lock %d\n", *my_id);
        osgsleep(3000);

        pLock->release();

        fprintf(stderr, "Release Lock %d\n", *my_id);
    }

//    exit(1);

    return(NULL); 
}

class MyThread : public Thread
{
  public:

    int id;
    
    MyThread(const Char8 *szName) : Thread(szName) 
    {
        fprintf(stderr, "My Create\n");
    }

    ~MyThread(void) {}

    static MyThread *createInt(const Char8 *szName) 
    {
        return new MyThread(szName);
    };

    static MyThread *create(void) 
    {
        ThreadManager::the()->setThreadCreateFunc(
            (ThreadManager::CreateThreadF) createInt);

        return (MyThread *) ThreadManager::the()->getThread(NULL);
    };

    void threadFunc(void) { thread_routine(&id); }
};

int main(int argc, char **argv)
{
    UInt32 j;

    fprintf(stderr, "Thread test started %x\n", thread_routine);

    osgInit(argc, argv);

    ThreadManager *gThreadManager = ThreadManager::the();

//	pthread_key_create(&saved_time_key, free_time);

    pLock = gThreadManager->getLock(NULL);

    for(UInt32 i = 0; i < NUM_THREADS; i++)
    {
        gThreads[i] = MyThread::create();

            //gThreadManager->getThread(NULL);

        gLocalId[i] = i;

        if(gThreads[i] != NULL)
        {
            gThreads[i]->print();

            ((MyThread *) gThreads[i])->id = i;
            gThreads[i]->run(1);
/*
            gThreads[i]->run(thread_routine,
                             1,
                             (void *) &(gLocalId[i]));
*/

        }
        else
        {
            fprintf(stderr, "Thread %d create failed\n", i);
        }
    }

    fprintf(stderr, "After create \n");

    osgsleep(2000);

    for(j = 0; j < NUM_THREADS; j++)
    {
		fprintf(stderr, "Unblock for %d\n", j);
        gThreads[j]->unblock();
    }

    for(j = 0; j < NUM_THREADS; j++)
    {
		fprintf(stderr, "Wait for %d\n", j);
        Thread::join(gThreads[j]);
    }

    osgsleep(20000);

    fprintf(stderr, "Thread test finished\n");
}
