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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

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



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char BaseThreadCommonBase::cvsid[]        = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/** \brief Constructor
 */

BaseThreadCommonBase::BaseThreadCommonBase(const Char8  *szName,
                                                 UInt32  uiId  ) :

     Inherited  (szName),
    _uiThreadId (uiId)
{
}

/** \brief Destructor
 */

BaseThreadCommonBase::~BaseThreadCommonBase(void)
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/



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

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char BasePThreadBase::cvsid[] = "@(#)$Id: $";

#ifdef OSG_ASPECT_USE_PTHREADKEY
pthread_key_t BasePThreadBase::_threadKey;
#endif

#if defined(OSG_ASPECT_USE_PTHREADSELF) || defined(OSG_ASPECT_USE_CUSTOMSELF)
vector<BaseThread *> BasePThreadBase::_vThreads;
#endif

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

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

void BasePThreadBase::init(void)
{
    setupThread    ();
    setupBlockCond ();
}

#ifdef OSG_ASPECT_USE_PTHREADKEY
void BasePThreadBase::freeThread(void *pThread)
{
    BaseThread **pT = (BaseThread **) pThread;

    if(pT != NULL)
        delete pT;
}
#endif

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

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

void BasePThreadBase::join(BasePThreadBase *pThread)
{
    if(pThread != NULL && pThread->_pThreadDesc != NULL)
    {
        pthread_join(*(pThread->_pThreadDesc), NULL);
    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/** \brief Constructor
 */

BasePThreadBase::BasePThreadBase(const Char8  *szName,
                                       UInt32  uiId  ) :
    Inherited   (szName, uiId),

    _pThreadDesc(NULL),
    _pBlockCond (NULL),
    _pBlockMutex(NULL)
{
    _pThreadData[0] = NULL;
    _pThreadData[1] = NULL;
    _pThreadData[2] = NULL;
}

/** \brief Destructor
 */

BasePThreadBase::~BasePThreadBase(void)
{
    delete _pThreadDesc;
}

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

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/*------------------------------ access -----------------------------------*/

Bool BasePThreadBase::run(ThreadFuncF  fThreadFunc,
                          void        *pThreadArg)
{
    Bool  returnValue = true;
    Int32 rc          = 0;

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

void BasePThreadBase::print(void)
{
    fprintf(stderr, "OSGPThreadBase -%s-%d-\n", _szName, _uiThreadId);
}

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

#endif /* OSG_USE_PTHREADS */




#if defined (OSG_USE_SPROC)

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char BaseSprocBase::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

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

void BaseSprocBase::init(void)
{
    setCurrentInternal((BaseThread *) this);
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

BaseThread *BaseSprocBase::getCurrent(void)
{
    return ((ProcessData *) PRDA->usr_prda.fill)->_pThread;
}

void BaseSprocBase::join(BaseSprocBase *pThread)
{
    if(pThread != NULL)
        waitpid(pThread->_pid, NULL, 0);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/** \brief Constructor
 */

BaseSprocBase::BaseSprocBase(const Char8  *szName,
                                   UInt32  uiId) :
    Inherited(szName, uiId),

    _pid(NULL)
{
    _pThreadData[0] = NULL;
    _pThreadData[1] = NULL;
    _pThreadData[2] = NULL;
}

/** \brief Destructor
 */

BaseSprocBase::~BaseSprocBase(void)
{
}

void BaseSprocBase::setPid(void)
{
    _pid = getpid();
}

void BaseSprocBase::setCurrentInternal(BaseThread *pThread)
{
    ((ProcessData *) PRDA->usr_prda.fill)->_pThread  = pThread;
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/*------------------------------ access -----------------------------------*/

Bool BaseSprocBase::run(ThreadFuncF  fThreadFunc,
                        void        *pThreadArg)
{
    Bool  returnValue = true;
    Int32 rc          = 0;

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

void BaseSprocBase::block(void)
{
    blockproc(_pid);
}

void BaseSprocBase::unblock(void)
{
    unblockproc(_pid);
}

Bool BaseSprocBase::exists(void)
{
    Bool returnValue = false;

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

void BaseSprocBase::print(void)
{
    fprintf(stderr, "OSGSprocBase -%s-%d-\n", _szName, _uiThreadId);
}

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

#endif /* OSG_USE_SPROC */


#if defined (OSG_USE_WINTHREADS)

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char BaseWinThreadBase::cvsid[] = "@(#)$Id: $";

#if defined(OSG_ASPECT_USE_LOCALSTORAGE)
UInt32 BaseWinThreadBase::_threadKey = 0;
#endif

#if defined(OSG_ASPECT_USE_DECLSPEC)
__declspec (thread) BaseThread *BaseWinThreadBase::_pThreadLocal     = NULL;
#endif

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

#if defined (OSG_ASPECT_USE_LOCALSTORAGE)
void BaseWinThreadBase::freeThread(void)
{
    BaseThread **pThread;

    pThread = (BaseThread **) TlsGetValue(_threadKey);

    delete pThread;
}
#endif

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

void BaseWinThreadBase::init(void)
{
    setupThread();
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

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

void BaseWinThreadBase::join(BaseWinThreadBase *pThread)
{
    if(pThread != NULL)
        WaitForSingleObject(pThread->_pExternalHandle, INFINITE);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/** \brief Constructor
 */

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

/** \brief Destructor
 */

BaseWinThreadBase::~BaseWinThreadBase(void)
{
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

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/*------------------------------ access -----------------------------------*/

Bool BaseWinThreadBase::run(ThreadFuncF  fThreadFunc,
                            void        *pThreadArg)
{
    Bool   returnValue = true;
    Handle rc          = 0;
    DWord  tmp;

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

void BaseWinThreadBase::block(void)
{
    SuspendThread(_pThreadHandle);
}

void BaseWinThreadBase::unblock(void)
{
    ResumeThread(_pExternalHandle);
}

Bool BaseWinThreadBase::exists(void)
{
    Bool returnValue = false;
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

void BaseWinThreadBase::print(void)
{
    fprintf(stderr, "OSGWinThreadBase -%s-%d-\n", _szName, _uiThreadId);
}

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

#endif /* OSG_USE_WINTHREADS */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char BaseThread::cvsid[] = "@(#)$Id: $";

MPThreadType BaseThread::_type("OSGBaseThread",
                               "OSGMPBase",
                               BaseThread::create,
                               BaseThread::initThreading);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

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

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

BaseThread *BaseThread::get(const Char8 *szName)
{
    return ThreadManager::the()->getThread(szName, "OSGBaseThread");
}

BaseThread *BaseThread::find(const Char8 *szName)
{
    return ThreadManager::the()->findThread(szName);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/** \brief Constructor
 */

BaseThread::BaseThread(const Char8 *szName, UInt32 uiId) :
    Inherited(szName, uiId)
{
}

/** \brief Destructor
 */

BaseThread::~BaseThread(void)
{
    ThreadManager::the()->removeThread(this);

    if(this != ThreadManager::getAppThread())
        terminate();
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/




///---------------------------------------------------------------------------
///  FUNCTION:
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters:
//p:
///
//g: GlobalVars:
//g:
///
//r: Return:
//r:
///
//c: Caution:
//c:
///
//a: Assumptions:
//a:
///
//d: Description:
//d:
///
//s: SeeAlso:
//s:
///---------------------------------------------------------------------------

