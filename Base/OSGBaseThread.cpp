/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGBaseThread.h"
#include "OSGBaseFunctions.h"
#include "OSGThreadManager.h"
#include "OSGLog.h"

#if ! defined (OSG_USE_PTHREADS) && ! defined (OSG_USE_WINTHREADS)
#include <sys/types.h>
#include <sys/prctl.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#endif

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGBASETHREAD_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

bool BaseThreadCommonBase::isInitialized(void)
{
    return _bInitialized;
}


/*! \class osg::BaseThreadCommonBase
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

BaseThreadCommonBase::BaseThreadCommonBase(const Char8  *szName,
                                                 UInt32  uiId  ) :

     Inherited   (szName),
    _uiThreadId  (uiId  ),
    _bInitialized(false )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

BaseThreadCommonBase::~BaseThreadCommonBase(void)
{
}



#if defined (OSG_USE_PTHREADS)

#ifdef OSG_ASPECT_USE_CUSTOMSELF

extern "C"
{
    extern pthread_t gThreadSelf(void);
}

#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class osg::BasePThreadBase
 */

#ifdef OSG_ASPECT_USE_PTHREADKEY
pthread_key_t BasePThreadBase::_threadKey;
#endif

#if defined(OSG_ASPECT_USE_PTHREADSELF) || defined(OSG_ASPECT_USE_CUSTOMSELF)
vector<BaseThread *> BasePThreadBase::_vThreads;
#endif

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

BaseThread *BasePThreadBase::getCurrent(void)
{
#ifdef OSG_ASPECT_USE_PTHREADKEY
    BaseThread **pThread;

    pThread = (BaseThread **) pthread_getspecific(_threadKey);

    return *pThread;
#endif

#ifdef OSG_ASPECT_USE_PTHREADSELF
    pthread_t threadId = pthread_self();

    return _vThreads[threadId & 0x00FF];
#endif

#ifdef OSG_ASPECT_USE_CUSTOMSELF
    pthread_t threadId = gThreadSelf();

    return _vThreads[threadId];
#endif
}

/*-------------------------------------------------------------------------*/
/*                               Join                                      */

void BasePThreadBase::join(BasePThreadBase *pThread)
{
    if(pThread != NULL && pThread->_pThreadDesc != NULL)
    {
        pthread_join(*(pThread->_pThreadDesc), NULL);
    }
}

/*-------------------------------------------------------------------------*/
/*                                Run                                      */

// This workaround was brought to you by gcc 2.95.3

bool BasePThreadBase::runFunction(ThreadFuncF  fThreadFunc,
                                  void        *pThreadArg)
{
    bool  returnValue = true;
    Int32 rc          = 0;

    _bInitialized     = false;

    if(fThreadFunc != NULL)
    {
        if(_pThreadDesc == NULL)
            _pThreadDesc = new pthread_t;

        _pThreadData[0] = (void *) fThreadFunc;
        _pThreadData[1] =          pThreadArg;
        _pThreadData[2] = (void *) this;

        rc = pthread_create(_pThreadDesc,
                            NULL,
                            BasePThreadBase::threadFunc,
                            (void *) &_pThreadData);

        if(rc != 0)
        {
            SFATAL << "OSGPTB : pthread_create failed" << endl;
            returnValue = false;
        }

    }
    else
    {
        SFATAL << "OSGPTB : no thread function given";
        returnValue = false;
    }

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                             Blocking                                    */

void BasePThreadBase::block(void)
{
    pthread_mutex_lock  (_pBlockMutex);
    pthread_cond_wait   (_pBlockCond, _pBlockMutex);
    pthread_mutex_unlock(_pBlockMutex);
}

void BasePThreadBase::unblock(void)
{
    pthread_cond_broadcast(_pBlockCond);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void BasePThreadBase::print(void)
{
    fprintf(stderr, "OSGPThreadBase -%s-%d-\n", _szName, _uiThreadId);
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void *BasePThreadBase::threadFunc(void *pThreadArg)
{
    void **pArgs = (void **) pThreadArg;

    if(pArgs != NULL)
    {
        if(pArgs[2] != NULL)
        {
            ((BaseThread *) pArgs[2])->init();

            if(pArgs[0] != NULL)
            {
                ThreadFuncF fThreadFunc = (ThreadFuncF) pArgs[0];

                fThreadFunc(pArgs[1]);
            }
        }
    }

    return NULL;
}

#ifdef OSG_ASPECT_USE_PTHREADKEY
void BasePThreadBase::freeThread(void *pThread)
{
    BaseThread **pT = (BaseThread **) pThread;

    if(pT != NULL)
        delete pT;
}
#endif

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

BasePThreadBase::BasePThreadBase(const Char8  *szName,
                                       UInt32  uiId  ) :
     Inherited  (szName, uiId),

    _pThreadDesc(NULL),
    _pBlockCond (NULL),
    _pBlockMutex(NULL)
{
    _pThreadData[0] = NULL;
    _pThreadData[1] = NULL;
    _pThreadData[2] = NULL;
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

BasePThreadBase::~BasePThreadBase(void)
{
    delete _pThreadDesc;
}

/*-------------------------------------------------------------------------*/
/*                            Construction                                 */

void BasePThreadBase::setupThread(void)
{
#ifdef OSG_ASPECT_USE_PTHREADKEY
    BaseThread **pThread = new BaseThread *;

    *pThread = (BaseThread *) this;

    pthread_setspecific(_threadKey, (void *) pThread);
#endif

#ifdef OSG_ASPECT_USE_PTHREADSELF
    pthread_t threadId = pthread_self();

    _vThreads.resize((threadId & 0x00FF) + 1);

    _vThreads[threadId & 0x00FF] = (BaseThread *) this;
#endif

#ifdef OSG_ASPECT_USE_CUSTOMSELF
    pthread_t threadId = gThreadSelf();

    _vThreads.resize(threadId + 1);

    _vThreadsA[threadId] = (BaseThread *) this;
#endif
}

void BasePThreadBase::setupBlockCond(void)
{
    _pBlockCond  = new pthread_cond_t;
    _pBlockMutex = new pthread_mutex_t;

    pthread_cond_init (_pBlockCond, NULL);
    pthread_mutex_init(_pBlockMutex, NULL);
}

void BasePThreadBase::init(void)
{
    if(_bInitialized == true)
        return;

    setupThread    ();
    setupBlockCond ();

    _bInitialized = true;
}

#endif /* OSG_USE_PTHREADS */




#if defined (OSG_USE_SPROC)

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class osg::BaseSprocBase
 */

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

BaseThread *BaseSprocBase::getCurrent(void)
{
    return ((ProcessData *) PRDA->usr_prda.fill)->_pThread;
}

/*-------------------------------------------------------------------------*/
/*                               Join                                      */

void BaseSprocBase::join(BaseSprocBase *pThread)
{
    if(pThread != NULL)
        waitpid(pThread->_pid, NULL, 0);
}

/*-------------------------------------------------------------------------*/
/*                                Run                                      */

// This workaround was brought to you by gcc 2.95.3

bool BaseSprocBase::runFunction(ThreadFuncF  fThreadFunc,
                                void        *pThreadArg)
{
    bool  returnValue = true;
    Int32 rc          = 0;

    _bInitialized     = false;

    if(fThreadFunc != NULL)
    {
        _pThreadData[0] = (void *) fThreadFunc;
        _pThreadData[1] =          pThreadArg;
        _pThreadData[2] = (void *) this;

        rc = sproc(BaseSprocBase::threadFunc, PR_SALL, (void *) _pThreadData);

        if(rc == -1)
        {
            SFATAL << "OSGSPB : sproc thread failed" << endl;
            returnValue = false;
        }
    }
    else
    {
        SFATAL << "OSGSPB : no thread function given";
        returnValue = false;
    }

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                             Blocking                                    */

void BaseSprocBase::block(void)
{
    blockproc(_pid);
}

void BaseSprocBase::unblock(void)
{
    unblockproc(_pid);
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

bool BaseSprocBase::exists(void)
{
    bool returnValue = false;

    returnValue = (prctl(PR_ISBLOCKED, _pid) != -1);

    return returnValue;
}


void BaseSprocBase::terminate(void)
{
    ::kill(_pid, SIGTERM);
}

void BaseSprocBase::kill(void)
{
    ::kill(_pid, SIGKILL);
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void BaseSprocBase::print(void)
{
    fprintf(stderr, "OSGSprocBase -%s-%d-\n", _szName, _uiThreadId);
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void BaseSprocBase::threadFunc(void *pThreadArg)
{
    void **pArgs = (void **) pThreadArg;

    if(pArgs != NULL)
    {
        if(pArgs[2] != NULL)
        {
            ((BaseThread *) pArgs[2])->init();

            ((BaseThread *) pArgs[2])->setPid();

            if(pArgs[0] != NULL)
            {
                ThreadFuncF threadFuncF = (ThreadFuncF) pArgs[0];

                threadFuncF(pArgs[1]);
            }
        }
    }
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

BaseSprocBase::BaseSprocBase(const Char8  *szName,
                                   UInt32  uiId  ) :
    Inherited(szName, uiId),

    _pid     (NULL)
{
    _pThreadData[0] = NULL;
    _pThreadData[1] = NULL;
    _pThreadData[2] = NULL;
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

BaseSprocBase::~BaseSprocBase(void)
{
}

/*-------------------------------------------------------------------------*/
/*                            Construction                                 */

void BaseSprocBase::init(void)
{
    if(_bInitialized == true)
        return;

    setCurrentInternal((BaseThread *) this);

    _bInitialized = true;
}

void BaseSprocBase::setPid(void)
{
    _pid = getpid();
}

void BaseSprocBase::setCurrentInternal(BaseThread *pThread)
{
    ((ProcessData *) PRDA->usr_prda.fill)->_pThread  = pThread;
}

#endif /* OSG_USE_SPROC */


#if defined (OSG_USE_WINTHREADS)

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class osg::BaseWinThreadBase
 */

#if defined(OSG_ASPECT_USE_LOCALSTORAGE)
UInt32 BaseWinThreadBase::_threadKey = 0;
#endif

#if defined(OSG_ASPECT_USE_DECLSPEC)
__declspec (thread) BaseThread *BaseWinThreadBase::_pThreadLocal     = NULL;
#endif

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

BaseThread *BaseWinThreadBase::getCurrent(void)
{
#ifdef OSG_ASPECT_USE_LOCALSTORAGE
    BaseThread **pThread;

    pThread = (BaseThread **) TlsGetValue(_threadKey);

    return *pThread;
#endif
#ifdef OSG_ASPECT_USE_DECLSPEC
    return _pThreadLocal;
#endif
}

/*-------------------------------------------------------------------------*/
/*                               Join                                      */

void BaseWinThreadBase::join(BaseWinThreadBase *pThread)
{
    if(pThread != NULL)
        WaitForSingleObject(pThread->_pExternalHandle, INFINITE);
}

/*-------------------------------------------------------------------------*/
/*                                Run                                      */

// This workaround was brought to you by gcc 2.95.3

bool BaseWinThreadBase::runFunction(ThreadFuncF  fThreadFunc,
                                    void        *pThreadArg)
{
    bool   returnValue = true;
    Handle rc          = 0;
    DWord  tmp;

    _bInitialized     = false;

    if(fThreadFunc != NULL)
    {
        _pThreadData[0] = (void *) fThreadFunc;
        _pThreadData[1] =          pThreadArg;
        _pThreadData[2] = (void *) this;

        rc = CreateThread(NULL,
                          0,
                          (LPTHREAD_START_ROUTINE) BaseThreadBase::threadFunc,
                          _pThreadData,
                          0,
                          &tmp);

        this->setExternalHandle(rc);

        if(rc == NULL)
        {
            SFATAL << "OSGWTB : sproc thread failed" << endl;
            returnValue = false;
        }
    }
    else
    {
        SFATAL << "OSGWTB : no thread function given";
        returnValue = false;
    }

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                              Blocking                                   */

void BaseWinThreadBase::block(void)
{
    SuspendThread(_pThreadHandle);
}

void BaseWinThreadBase::unblock(void)
{
    ResumeThread(_pExternalHandle);
}

/*-------------------------------------------------------------------------*/
/*                              Helper                                     */

bool BaseWinThreadBase::exists(void)
{
    bool returnValue = false;
    DWORD   rc          = 0;

    if(BaseThread::getCurrent() == this)
    {
        GetExitCodeThread(_pThreadHandle,
                          &rc);
    }
    else
    {
        GetExitCodeThread(_pExternalHandle,
                          &rc);
    }

    returnValue = (rc == STILL_ACTIVE);

    return returnValue;
}


void BaseWinThreadBase::terminate(void)
{
    if(BaseThread::getCurrent() == this)
    {
        TerminateThread(_pThreadHandle, 0);
    }
    else
    {
        TerminateThread(_pExternalHandle, 0);
    }
}

void BaseWinThreadBase::kill(void)
{
    if(BaseThread::getCurrent() == this)
    {
        TerminateThread(_pThreadHandle, 0);
    }
    else
    {
        TerminateThread(_pExternalHandle, 0);
    }
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void BaseWinThreadBase::print(void)
{
    fprintf(stderr, "OSGWinThreadBase -%s-%u-\n", _szName, _uiThreadId);
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void BaseWinThreadBase::threadFunc(void *pThreadArg)
{
    void **pArgs = (void **) pThreadArg;

    if(pArgs != NULL)
    {
        if(pArgs[2] != NULL)
        {
            ((BaseThread *) pArgs[2])->init();

            ((BaseWinThreadBase *) pArgs[2])->setPid();
        }

        if(pArgs[0] != NULL)
        {
            ThreadFuncF threadFuncF = (ThreadFuncF) pArgs[0];

            threadFuncF(pArgs[1]);
        }
    }
}

#if defined (OSG_ASPECT_USE_LOCALSTORAGE)
void BaseWinThreadBase::freeThread(void)
{
    BaseThread **pThread;

    pThread = (BaseThread **) TlsGetValue(_threadKey);

    delete pThread;
}
#endif

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

BaseWinThreadBase::BaseWinThreadBase(const Char8  *szName,
                                           UInt32  uiId) :
    Inherited(szName, uiId),

    _pThreadHandle(NULL),
    _pExternalHandle(NULL),
    _uiNativeThreadId(0)
{
    _pThreadData[0] = NULL;
    _pThreadData[1] = NULL;
    _pThreadData[2] = NULL;
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

BaseWinThreadBase::~BaseWinThreadBase(void)
{
}

/*-------------------------------------------------------------------------*/
/*                            Construction                                 */

void BaseWinThreadBase::init(void)
{
    if(_bInitialized == true)
        return;

    setupThread();

    _bInitialized = true;
}

void BaseWinThreadBase::setPid(void)
{
    _pThreadHandle   = GetCurrentThread();
    _uiNativeThreadId = GetCurrentThreadId();
}

void BaseWinThreadBase::setExternalHandle(Handle pExternalHandle)
{
    _pExternalHandle = pExternalHandle;
}


void BaseWinThreadBase::setupThread(void)
{
#if defined (OSG_ASPECT_USE_LOCALSTORAGE)
    BaseThread **pThread = new BaseThread *;

    *pThread = (BaseThread *) this;

    TlsSetValue(_threadKey, pThread);
#endif

#if defined (OSG_ASPECT_USE_DECLSPEC)
    _pThreadLocal = (BaseThread *) this;
#endif
}

#endif /* OSG_USE_WINTHREADS */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class osg::BaseThread
 */

MPThreadType BaseThread::_type("OSGBaseThread",
                               "OSGMPBase",
                               BaseThread::create,
                               BaseThread::initThreading);

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

BaseThread *BaseThread::get(const Char8 *szName)
{
    return ThreadManager::the()->getThread(szName, "OSGBaseThread");
}

BaseThread *BaseThread::find(const Char8 *szName)
{
    return ThreadManager::the()->findThread(szName);
}

/*-------------------------------------------------------------------------*/
/*                                Run                                      */

void BaseThread::run(void)
{
    Inherited::runFunction(runWorkProc, this);
}


/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

BaseThread *BaseThread::create(const Char8 *szName, UInt32 uiId)
{
    return new BaseThread(szName, uiId);
}

void BaseThread::initThreading(void)
{
    FINFO(("BaseThread::initThreading\n"))

#ifdef OSG_ASPECT_USE_PTHREADKEY
    int rc;

    rc = pthread_key_create(&(BaseThread::_threadKey),
                              BaseThread::freeThread);

    FFASSERT((rc == 0), 1, ("Failed to create pthread thread key\n");)
#endif

#ifdef OSG_ASPECT_USE_PTHREADSELF
    BaseThread::_vThreads.resize(16);

    for(UInt32 i = 0; i < 16; i++)
    {
        BaseThread::_vThreads[i]     = NULL;
    }
#endif

#if defined (OSG_ASPECT_USE_LOCALSTORAGE)
    BaseThread::_threadKey     = TlsAlloc();

    FFASSERT((BaseThread::_threadKey != 0xFFFFFFFF), 1,
             ("Failed to alloc thread key local storage\n");)
#endif
}

void *BaseThread::runWorkProc(void  *pThread)
{
    if(pThread != NULL)
    {
        static_cast<BaseThread *>(pThread)->workProc();
    }
    
    return NULL;
}


/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

BaseThread::BaseThread(const Char8 *szName, UInt32 uiId) :
    Inherited(szName, uiId)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

BaseThread::~BaseThread(void)
{
    ThreadManager::the()->removeThread(this);

    if(this != ThreadManager::getAppThread())
        terminate();
}

void BaseThread::workProc(void)
{
}
