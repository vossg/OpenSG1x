

#include <OSGConfig.h>

#include <OSGBaseFunctions.h>
#include <OSGThread.h>
#include <OSGThreadManager.h>
#include <OSGLock.h>

OSG_BEGIN_NAMESPACE

#if defined(OSG_PTHREAD_ELF_TLS)
__thread int fooCounter = 0;
#endif

class MyThread : public Thread
{
  private:

    typedef Thread Inherited;

    MyThread(const MyThread &source);
    void operator =(const MyThread &source);

  protected:

    Lock *pLock;
  
    static MPThreadType _type;

    static Thread *create(const Char8  *szName, UInt32  uiId);


    MyThread(const Char8 *szName, UInt32 uiId);

    virtual ~MyThread(void);

    void workProc(void);

  public:

    UInt32 _uiThreadId;

    static MyThread *get (Char8 *szName);
    static MyThread *find(Char8 *szName);
};

MPThreadType MyThread::_type("MyThread", 
                             "Thread", 
                             (CreateThreadF) MyThread::create, 
                             NULL);

Thread *MyThread::create(const Char8  *szName, UInt32  uiId)
{
    return new MyThread(szName, uiId);
}

MyThread::MyThread(const Char8 *szName, UInt32  uiId) :
    Inherited(szName, uiId),
    pLock(NULL)
{
    fprintf(stderr, "Create Lock\n");
    fflush(stderr);

    pLock = ThreadManager::the()->getLock(NULL);
}

MyThread::~MyThread(void)
{
}

void MyThread::workProc(void)
{
    fprintf(stderr, "Enter WorkProc\n");

#if defined(OSG_PTHREAD_ELF_TLS)
    fooCounter = _uiThreadId * 100000;
#endif

//    for(UInt32 i = 0; i < 10; ++i)
    while(1)
    {
        fprintf(stderr, "%u Processing step, aspect %u (%d)\n",
                _uiThreadId,
//                i,
                OSG::Thread::getAspect(),
#if defined(OSG_PTHREAD_ELF_TLS)
                fooCounter++);
#else
                0);
#endif
        osgsleep(100);
    }

//  fprintf(stderr, "Leave WorkProc\n");
}

MyThread *MyThread::get(Char8 *szName)
{
    BaseThread *pThread = ThreadManager::the()->getThread(szName,
                                                          "MyThread");

    return dynamic_cast<MyThread *>(pThread);
}

MyThread *MyThread::find(Char8 *szName)
{
    BaseThread *pThread = ThreadManager::the()->findThread(szName);

    return dynamic_cast<MyThread *>(pThread);
}

OSG_END_NAMESPACE

int main(int argc, char **argv)
{
    OSG::osgInit(argc,argv);

    fprintf(stderr, "Derived Thread Test Started\n");
    
    OSG::MyThread *pThread1 = OSG::MyThread::get("My1");
    OSG::MyThread *pThread2 = OSG::MyThread::get("My2");
    OSG::MyThread *pThread3 = OSG::MyThread::get("My3");
    OSG::MyThread *pThread4 = OSG::MyThread::get("My4");

    if(pThread1 == NULL || 
       pThread2 == NULL || 
       pThread3 == NULL || 
       pThread4 == NULL  )
    {
        fprintf(stderr, "Could not create thread\n");
        return 0;
    }

    pThread1->_uiThreadId = 1;
    pThread1->run(1);

    pThread2->_uiThreadId = 2;
    pThread2->run(1);

    pThread3->_uiThreadId = 3;
    pThread3->run(1);

    pThread4->_uiThreadId = 4;
    pThread4->run(1);



    OSG::osgsleep(5000);
    fprintf(stderr, "Kill 1\n");
    pThread1->kill();

    OSG::Thread::join(pThread1);

    OSG::osgsleep(5000);

    fprintf(stderr, "TERM 2\n");
    pThread2->terminate();

    OSG::Thread::join(pThread2);

    OSG::osgsleep(5000);
    fprintf(stderr, "Kill 3\n");
    pThread3->kill();

    OSG::Thread::join(pThread3);

    OSG::osgsleep(5000);
    fprintf(stderr, "TERM 4\n");
    pThread4->terminate();

    OSG::Thread::join(pThread4);

    fprintf(stderr, "Derived Thread Test Finished\n");

    return 0;
}
