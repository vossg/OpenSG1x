

#include <OSGConfig.h>

#include <OSGBaseFunctions.h>
#include <OSGThread.h>
#include <OSGThreadManager.h>

OSG_BEGIN_NAMESPACE

class MyThread : public Thread
{
  private:

    typedef Thread Inherited;

    MyThread(const MyThread &source);
    void operator =(const MyThread &source);

  protected:
  
    static MPThreadType _type;

    static Thread *create(const Char8  *szName, UInt32  uiId);


    MyThread(const Char8 *szName, UInt32 uiId);

    virtual ~MyThread(void);

    void workProc(void);

  public:

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
    Inherited(szName, uiId)
{
}

MyThread::~MyThread(void)
{
}

void MyThread::workProc(void)
{
    fprintf(stderr, "Enter WorkProc\n");

    for(UInt32 i = 0; i < 10; ++i)
    {
        fprintf(stderr, "Processing step %u, aspect %u\n",
                i,
                OSG::Thread::getAspect());
        osgsleep(100);
    }

    fprintf(stderr, "Leave WorkProc\n");
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
    
    OSG::MyThread *pThread = OSG::MyThread::get("My1");

    if(pThread == NULL)
    {
        fprintf(stderr, "Could not create thread\n");
        return 0;
    }

    pThread->run(1);

    OSG::Thread::join(pThread);

    fprintf(stderr, "Derived Thread Test Finished\n");

    return 0;
}
