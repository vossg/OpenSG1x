
#include <OSGThread.h>
#include <OSGLock.h>
#include <OSGBaseFunctions.h>
#include <iostream>
using namespace std;

osg::Thread * thread1 = 0;
osg::Thread * thread2 = 0;
osg::Lock   * lock    = 0;

void thread1_fn (void*)
{
    int count = 0;

    while(true) 
    {
        fprintf(stderr, "Thread 1 try\n");
        lock->aquire();

        fprintf(stderr, "Thread 1 sleep\n");
        OSG::osgsleep(1000);

        lock->release();
        OSG::osgsleep(5);
    }
}

void thread2_fn (void*) 
{
    int count = 0;

    while (true) 
    {
        OSG::osgsleep(10);

        
        fprintf(stderr, "Thread 2 try\n");
        lock->aquire();

        fprintf(stderr, "Thread 2 sleep\n");
        OSG::osgsleep(200);

        lock->release();
        
        OSG::osgsleep(50);
    }
}

int main (int argc, char **argv) 
{
    osg::osgInit(argc, argv);
    lock = osg::Lock::get("Lock");

    thread1 = osg::Thread::get("Thread1");
    thread2 = osg::Thread::get("Thread2");

    thread1->runFunction(thread1_fn, 0, 0);
    thread2->runFunction(thread2_fn, 0, 0);

    osg::Thread::join(thread1);
    osg::Thread::join(thread2);
}
