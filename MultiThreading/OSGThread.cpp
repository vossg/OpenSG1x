/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#define OSG_COMPILEMULTITHREADING

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGThread.h"
#include "OSGBaseFunctions.h"
#include "OSGChangeList.h"
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

char      ThreadCommonBase::cvsid[]        = "@(#)$Id: $";

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

ThreadCommonBase::ThreadCommonBase(const Char8 *szName,
                                               UInt32 uiId) :
    
    Inherited(szName),

    _uiThreadId (uiId),

    _uiAspectId (0),
    _pChangeList(NULL)
{
}

/** \brief Destructor
 */

ThreadCommonBase::~ThreadCommonBase(void)
{
    subRefP(_pChangeList);
}

void ThreadCommonBase::setAspect(UInt32 uiAspectId)
{
    _uiAspectId = uiAspectId;
}

void ThreadCommonBase::setChangeList(ChangeList *pChangeList)
{
    setRefP(_pChangeList, pChangeList);
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/*------------------------------ access -----------------------------------*/

ChangeList *ThreadCommonBase::getChangeList(void)
{
    return _pChangeList;
}

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

char PThreadBase::cvsid[] = "@(#)$Id: $";

#ifdef OSG_ASPECT_USE_PTHREADKEY
pthread_key_t PThreadBase::_aspectKey;
pthread_key_t PThreadBase::_threadKey;
pthread_key_t PThreadBase::_changeListKey;
#endif

#if defined(OSG_ASPECT_USE_PTHREADSELF) || \
    defined(OSG_ASPECT_USE_CUSTOMSELF)
#ifdef OSG_COMPILETIME_NUM_ASPECTS
UInt16      PThreadBase::_pAspects    [OSG_NUM_ASPECTS];
Thread     *PThreadBase::_pThreads    [OSG_NUM_ASPECTS];
ChangeList *PThreadBase::_pChangelists[OSG_NUM_ASPECTS];
#endif
#ifdef OSG_RUNTIME_NUM_ASPECTS
UInt16      *PThreadBase::_pAspects     = NULL;
Thread     **PThreadBase::_pThreads     = NULL;
ChangeList **PThreadBase::_pChangelists = NULL;
#endif
#endif

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void *PThreadBase::threadFunc(void *pThreadArg)
{
    void **pArgs = (void **) pThreadArg;

    if(pArgs != NULL)
    {
        if(pArgs[2] != NULL)
        {
            init((Thread *) pArgs[2]);

            if(pArgs[0] != NULL)
            {
                ThreadFuncF fThreadFunc = (ThreadFuncF) pArgs[0];
                
                fThreadFunc(pArgs[1]);
            }
        }
    }    

    return NULL;
}

void PThreadBase::init(Thread *pThis)
{
    pThis->setupAspect    ();        
    pThis->setupThread    ();        
    pThis->setupChangeList();        
    pThis->setupBlockCond ();
}

#ifdef OSG_ASPECT_USE_PTHREADKEY
void PThreadBase::freeAspect(void *pAspect)
{
    UInt32 *pUint = (UInt32 *) pAspect;

    if(pUint != NULL)
        delete pUint;
}

void PThreadBase::freeThread(void *pThread)
{
    Thread **pT = (Thread **) pThread;

    if(pT != NULL)
        delete pT;    
}

void PThreadBase::freeChangeList(void *pChangeList)
{
    ChangeList **pCl = (ChangeList **) pChangeList;

    if(pCl != NULL)
        delete pCl;
}
#endif

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

UInt32 PThreadBase::getAspect(void)
{
#ifdef OSG_ASPECT_USE_PTHREADKEY
    UInt32 *pUint;

    pUint = (UInt32 *) pthread_getspecific(_aspectKey);

    return *pUint;
#endif

#ifdef OSG_ASPECT_USE_PTHREADSELF
    pthread_t threadId = pthread_self(); 

    return _pAspects[threadId & 0x00FF];
#endif

#ifdef OSG_ASPECT_USE_CUSTOMSELF
    pthread_t threadId = gThreadSelf(); 

    return _pAspects[threadId];
#endif
}

Thread *PThreadBase::getCurrent(void)
{
#ifdef OSG_ASPECT_USE_PTHREADKEY
    Thread **pThread;

    pThread = (Thread **) pthread_getspecific(_threadKey);

    return *pThread;
#endif

#ifdef OSG_ASPECT_USE_PTHREADSELF
    pthread_t threadId = pthread_self(); 

    return _pThreads[threadId & 0x00FF];
#endif

#ifdef OSG_ASPECT_USE_CUSTOMSELF
    pthread_t threadId = gThreadSelf(); 

    return _pThreads[threadId];
#endif
}

ChangeList *PThreadBase::getCurrentChangeList(void)
{
#ifdef OSG_ASPECT_USE_PTHREADKEY
    ChangeList **pCList;

    pCList = (ChangeList **) pthread_getspecific(_changeListKey);

    return *pCList;
#endif

#ifdef OSG_ASPECT_USE_PTHREADSELF
    pthread_t threadId = pthread_self(); 

    return _pChangelists[threadId & 0x00FF];
#endif

#ifdef OSG_ASPECT_USE_CUSTOMSELF
    pthread_t threadId = gThreadSelf(); 

    return _pChangelistsA[threadId];
#endif
}


void PThreadBase::join(PThreadBase *pThread)
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

void PThreadBase::setupAspect(void)
{
#ifdef OSG_ASPECT_USE_PTHREADKEY
    UInt32 *pUint = new UInt32;

    *pUint = Inherited::_uiAspectId;

    pthread_setspecific(_aspectKey, (void *) pUint);  
#endif

#ifdef OSG_ASPECT_USE_PTHREADSELF
    pthread_t threadId = pthread_self(); 

    _pAspects[threadId & 0x00FF] = Inherited::_uiAspectId;
#endif

#ifdef OSG_ASPECT_USE_CUSTOMSELF
    pthread_t threadId = gThreadSelf(); 

    _pAspects[threadId] = Inherited::_uiAspectId;
#endif
}

void PThreadBase::setupThread(void)
{
#ifdef OSG_ASPECT_USE_PTHREADKEY
    Thread **pThread = new Thread *;

    *pThread = (Thread *) this;

    pthread_setspecific(_threadKey, (void *) pThread);  
#endif

#ifdef OSG_ASPECT_USE_PTHREADSELF
    pthread_t threadId = pthread_self(); 

    _pThreads[threadId & 0x00FF] = (Thread *) this;
#endif

#ifdef OSG_ASPECT_USE_CUSTOMSELF
    pthread_t threadId = gThreadSelf(); 

    _pThreadsA[threadId] = (Thread *) this;
#endif
}

void PThreadBase::setupChangeList(void)
{
#ifdef OSG_ASPECT_USE_PTHREADKEY
    ChangeList **pChangeList = new ChangeList *;

    if(Inherited::_pChangeList == NULL)
    {
        *pChangeList = new ChangeList;

        Inherited::setChangeList(*pChangeList);
    }
    else
    {
        *pChangeList = Inherited::_pChangeList;
        
        (*pChangeList)->clearAll();
    }

    (*pChangeList)->setAspect(Inherited::_uiApectId);
    pthread_setspecific(_changeListKey, (void *) pChangeList);  
#endif

#ifdef OSG_ASPECT_USE_PTHREADSELF
    ChangeList *pChangeList;
    pthread_t      threadId = pthread_self(); 

    if(Inherited::_pChangeList == NULL)
    {
        pChangeList = new ChangeList;

        Inherited::setChangeList(pChangeList);
    }
    else
    {
        pChangeList = Inherited::_pChangeList;
        
        pChangeList->clearAll();
    }

    pChangeList->setAspect(Inherited::_uiAspectId);
    _pChangelists[threadId & 0x00FF] = pChangeList;
#endif

#ifdef OSG_ASPECT_USE_CUSTOMSELF
    ChangeList *pChangeList;
    pthread_t      threadId = gThreadSelf(); 

    if(Inherited::_pChangeList == NULL)
    {
        pChangeList = new ChangeList;

        Inherited::setChangeList(pChangeList);
    }
    else
    {
        pChangeList = Inherited::_pChangeList;
        
        pChangeList->clearAll();
    }

    pChangeList->setAspect(Inherited::_uiAspectId);
    _pChangelists[threadId] = pChangeList;
#endif
}

void PThreadBase::setupBlockCond(void)
{
    _pBlockCond  = new pthread_cond_t;
    _pBlockMutex = new pthread_mutex_t;

    pthread_cond_init (_pBlockCond, NULL);
    pthread_mutex_init(_pBlockMutex, NULL);
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/** \brief Constructor
 */

PThreadBase::PThreadBase(const Char8 *szName, 
                                     UInt32 uiId) :
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

PThreadBase::~PThreadBase(void)
{
    delete _pThreadDesc;
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/*------------------------------ access -----------------------------------*/

Bool PThreadBase::run(ThreadFuncF fThreadFunc, 
                            UInt32      uiAspectId,
                            void          *pThreadArg)
{
    Bool  returnValue = true;
    Int32 rc          = 0;

    if(uiAspectId >= ThreadManager::getNumAspects())
    {
        SFATAL << "OSGPTB : invalid aspect id" << endl;
        return false;
    }

    if(fThreadFunc != NULL)
    {
        if(_pThreadDesc == NULL)
            _pThreadDesc = new pthread_t;

        _pThreadData[0] = (void *) fThreadFunc;
        _pThreadData[1] =          pThreadArg;
        _pThreadData[2] = (void *) this;

        Inherited::setAspect(uiAspectId);

		rc = pthread_create(_pThreadDesc, 
                            NULL,
                            PThreadBase::threadFunc,
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

    return true;
}

void PThreadBase::block(void)
{
    fprintf(stderr, "block\n");
    
    pthread_mutex_lock  (_pBlockMutex);
    pthread_cond_wait   (_pBlockCond, _pBlockMutex);
    pthread_mutex_unlock(_pBlockMutex);
}

void PThreadBase::unblock(void)
{
    fprintf(stderr, "unblock\n");

    pthread_cond_broadcast(_pBlockCond);
}

void PThreadBase::print(void)
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

char SprocBase::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void SprocBase::threadFunc(void *pThreadArg)
{
    void **pArgs = (void **) pThreadArg;

    if(pArgs != NULL)
    {
        if(pArgs[2] != NULL)
        {
            init((Thread *) pArgs[2]);

            ((Thread *) pArgs[2])->setPid();

            if(pArgs[0] != NULL)
            {
                ThreadFuncF threadFuncF = (ThreadFuncF) pArgs[0];

                threadFuncF(pArgs[1]);
            }
        }
    }    
}

void SprocBase::init(Thread *pThis)
{
    pThis->setAspectInternal      (pThis->_uiAspectId);
    pThis->setCurrentInternal     (pThis);
    pThis->setupChangeListInternal();
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

UInt32 SprocBase::getAspect(void)
{
    return ((ProcessData *) PRDA->usr2_prda.fill)->_uiAspectId;
}

Thread *SprocBase::getCurrent(void)
{
    return ((ProcessData *) PRDA->usr2_prda.fill)->_pThread;
}

ChangeList *SprocBase::getCurrentChangeList(void)
{
    return ((ProcessData *) PRDA->usr2_prda.fill)->_pChangeList;
}

void SprocBase::join(SprocBase *pThread)
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

void SprocBase::setPid(void)
{
    _pid = getpid();
}

void SprocBase::setAspectInternal(UInt32 uiAspect)
{
    ((ProcessData *) PRDA->usr2_prda.fill)->_uiAspectId = uiAspect;
}

void SprocBase::setCurrentInternal(Thread *pThread)
{
    ((ProcessData *) PRDA->usr2_prda.fill)->_pThread  = pThread;
}

void SprocBase::setupChangeListInternal(void)
{
    if(Inherited::_pChangeList == NULL)
    {
        ((ProcessData *) PRDA->usr2_prda.fill)->_pChangeList = 
            new ChangeList();

        Inherited::setChangeList(
            ((ProcessData *) PRDA->usr2_prda.fill)->_pChangeList);
    }
    else
    {
        ((ProcessData *) PRDA->usr2_prda.fill)->_pChangeList = 
            Inherited::_pChangeList;

        Inherited::_pChangeList->clearAll();
    }

    Inherited::_pChangeList->setAspect(Inherited::_uiAspectId);
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/** \brief Constructor
 */

SprocBase::SprocBase(const Char8 *szName,
                                 UInt32 uiId) :    
    Inherited(szName, uiId),

    _pid(NULL)
{
    _pThreadData[0] = NULL;
    _pThreadData[1] = NULL;
    _pThreadData[2] = NULL;    
}

/** \brief Destructor
 */

SprocBase::~SprocBase(void)
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/*------------------------------ access -----------------------------------*/

Bool SprocBase::run(ThreadFuncF fThreadFunc, 
                          UInt32      uiAspectId,
                          void          *pThreadArg)
{
    Bool  returnValue = true;
    Int32 rc          = 0;

    if(uiAspectId >= ThreadManager::getNumAspects())
    {
        SFATAL << "OSGSPB : invalid aspect id" << endl;
        return false;
    }

    if(fThreadFunc != NULL)
    {
        _pThreadData[0] = (void *) fThreadFunc;
        _pThreadData[1] =          pThreadArg;
        _pThreadData[2] = (void *) this;

        Inherited::setAspect(uiAspectId);

		rc = sproc(SprocBase::threadFunc, PR_SALL, (void *) _pThreadData);

        if(rc == -1)
        {
            SFATAL << "OSGSPB : sproc thread failed" << endl;
            returnValue = false;
            perror("");
        }
    }
    else
    {
        SFATAL << "OSGSPB : no thread function given";
        returnValue = false;
    }

    return returnValue;
}

void SprocBase::block(void)
{
    fprintf(stderr, 
            "Blocking Proc %d %d\n", 
            _uiThreadId,
            _pid);

    blockproc(_pid);
}

void SprocBase::unblock(void)
{
    fprintf(stderr, 
            "UnBlocking Proc %d %d\n", 
            _uiThreadId,
            _pid);

    unblockproc(_pid);
}

Bool SprocBase::exists(void)
{
    Bool returnValue = false;

    returnValue = (prctl(PR_ISBLOCKED, _pid) != -1);

    return returnValue;
}


void SprocBase::terminate(void)
{
    fprintf(stderr, "kill : %d\n", ::kill(_pid, SIGTERM));
    perror("term");
}

void SprocBase::kill(void)
{
    fprintf(stderr, "kill : %d\n", ::kill(_pid, SIGKILL));
    perror("kill");
}

void SprocBase::print(void)
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

char WinThreadBase::cvsid[] = "@(#)$Id: $";

#if defined(OSG_ASPECT_USE_LOCALSTORAGE)
UInt32 WinThreadBase::_aspectKey = 0;
UInt32 WinThreadBase::_threadKey = 0;
UInt32 WinThreadBase::_changeListKey = 0;
#endif

#if defined(OSG_ASPECT_USE_DECLSPEC)
__declspec (thread) UInt32      WinThreadBase::_uiAspectLocal    = 0;
__declspec (thread) Thread     *WinThreadBase::_pThreadLocal     = NULL;
__declspec (thread) ChangeList *WinThreadBase::_pChangeListLocal = NULL;
#endif

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

#if defined (OSG_ASPECT_USE_LOCALSTORAGE)
void WinThreadBase::freeAspect(void)
{
    UInt32 *pUint;

    pUint = (UInt32 *) TlsGetValue(_aspectKey);

	delete pUint;
}

void WinThreadBase::freeThread(void)
{
    Thread **pThread;

    pThread = (Thread **) TlsGetValue(_threadKey);

	delete pThread;
}

void WinThreadBase::freeChangeList(void)
{
    ChangeList **pCList;

    pCList = (ChangeList **) TlsGetValue(_changeListKey);

	delete pCList;
}
#endif

void WinThreadBase::threadFunc(void *pThreadArg)
{
    void **pArgs = (void **) pThreadArg;

    if(pArgs != NULL)
    {
        if(pArgs[2] != NULL)
        {
            init((Thread *) pArgs[2]);

            ((WinThreadBase *) pArgs[2])->setPid();
        }

        if(pArgs[0] != NULL)
        {
            ThreadFuncF threadFuncF = (ThreadFuncF) pArgs[0];

            threadFuncF(pArgs[1]);
        }
    }    
}

void WinThreadBase::init(Thread *pThis)
{
	pThis->setupAspect();
    pThis->setupThread(); 
    pThis->setupChangeList();        
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

UInt32 WinThreadBase::getAspect(void)
{
#ifdef OSG_ASPECT_USE_LOCALSTORAGE
    UInt32 *pUint;

    pUint = (UInt32 *) TlsGetValue(_aspectKey);

    return *pUint;
#endif
#ifdef OSG_ASPECT_USE_DECLSPEC
	return _uiAspectLocal;
#endif
}

Thread *WinThreadBase::getCurrent(void)
{
#ifdef OSG_ASPECT_USE_LOCALSTORAGE
    Thread **pThread;

    pThread = (Thread **) TlsGetValue(_threadKey);

    return *pThread;
#endif
#ifdef OSG_ASPECT_USE_DECLSPEC
	return _pThreadLocal;
#endif
}
        
ChangeList *WinThreadBase::getCurrentChangeList(void)
{
#ifdef OSG_ASPECT_USE_LOCALSTORAGE
    ChangeList **pCList;

    pCList = (ChangeList **) TlsGetValue(_changeListKey);

    return *pCList;
#endif
#ifdef OSG_ASPECT_USE_DECLSPEC
	return _pChangeListLocal;
#endif
}

void WinThreadBase::join(WinThreadBase *pThread)
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

void WinThreadBase::setPid(void)
{
	_pThreadHandle   = GetCurrentThread();
	_uiNativeThreadId = GetCurrentThreadId();
}

void WinThreadBase::setExternalHandle(Handle pExternalHandle)
{
	_pExternalHandle = pExternalHandle;
}


void WinThreadBase::setupAspect(void)
{
#ifdef OSG_ASPECT_USE_LOCALSTORAGE
    UInt32 *pUint = new UInt32;

    *pUint = Inherited::_uiAspectId;

    TlsSetValue(_aspectKey, pUint);
#endif

#ifdef OSG_ASPECT_USE_DECLSPEC
	_uiAspectLocal = Inherited::_uiAspectId;
#endif
}

void WinThreadBase::setupThread(void)
{
#if defined (OSG_ASPECT_USE_LOCALSTORAGE)
	Thread **pThread = new Thread *;

	*pThread = (Thread *) this;

	TlsSetValue(_threadKey, pThread);
#endif

#if defined (OSG_ASPECT_USE_DECLSPEC)
    _pThreadLocal = (Thread *) this;
#endif
}

void WinThreadBase::setupChangeList(void)
{
#if defined (OSG_ASPECT_USE_LOCALSTORAGE)
	ChangeList **pChangeList = new ChangeList *;

   if(Inherited::_pChangeList == NULL)
    {
        *pChangeList = new ChangeList;

        Inherited::setChangeList(*pChangeList);
    }
    else
    {
        *pChangeList = Inherited::_pChangeList;
        
        (*pChangeList)->clearAll();
    }

    (*pChangeList)->setAspect(Inherited::_uiAspectId);
	TlsSetValue(_changeListKey, pChangeList);
#endif

#if defined (OSG_ASPECT_USE_DECLSPEC)
    if(Inherited::_pChangeList == NULL)
    {
        _pChangeListLocal = new ChangeList;
        Inherited::setChangeList(_pChangeListLocal);
    }
    else
    {
        _pChangeListLocal = Inherited::_pChangeList;

        _pChangeListLocal->clearAll();
    }

    _pChangeListLocal->setAspect(Inherited::_uiAspectId);
#endif
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/** \brief Constructor
 */

WinThreadBase::WinThreadBase(const Char8  *szName,
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

WinThreadBase::~WinThreadBase(void)
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/*------------------------------ access -----------------------------------*/

Bool WinThreadBase::run(ThreadFuncF  fThreadFunc, 
                              UInt32       uiAspectId,  
                              void           *pThreadArg)
{
    Bool   returnValue = true;
    Handle rc          = 0;
	DWord  tmp;

    if(uiAspectId >= ThreadManager::getNumAspects())
    {
        SFATAL << "OSGWTB : invalid aspect id" << endl;
        return false;
    }

    if(fThreadFunc != NULL)
    {
        _pThreadData[0] = (void *) fThreadFunc;
        _pThreadData[1] =          pThreadArg;
        _pThreadData[2] = (void *) this;

        Inherited::setAspect(uiAspectId);

		fprintf(stderr, "TF : %x %x %x %x\n", 
				_pThreadData,    _pThreadData[0], 
				_pThreadData[1], _pThreadData[2]);
		
		rc = CreateThread(NULL, 
						  0,    
                          (LPTHREAD_START_ROUTINE) ThreadBase::threadFunc, 
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

void WinThreadBase::block(void)
{
    SuspendThread(_pThreadHandle);
}

void WinThreadBase::unblock(void)
{
    ResumeThread(_pExternalHandle);
}

Bool WinThreadBase::exists(void)
{
    Bool returnValue = false;
    DWORD   rc          = 0;

    if(Thread::getCurrent() == this)
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


void WinThreadBase::terminate(void)
{
    if(Thread::getCurrent() == this)
    {
        TerminateThread(_pThreadHandle, 0);
    }
    else
    {
        TerminateThread(_pExternalHandle, 0);
    }
}

void WinThreadBase::kill(void)
{
    if(Thread::getCurrent() == this)
    {
        TerminateThread(_pThreadHandle, 0);
    }
    else
    {
        TerminateThread(_pExternalHandle, 0);
    }
}

void WinThreadBase::print(void)
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

char Thread::cvsid[] = "@(#)$Id: $";

MPThreadType Thread::_type("OSGThread", 
                                 "OSGMPBase", 
                                 Thread::create);

const UInt32 Thread::InvalidAspect = 
    TypeConstants<UInt32>::getAllSet();

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

Thread *Thread::create(const Char8 *szName, UInt32 uiId)
{
    return new Thread(szName, uiId);
}

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

Thread::Thread(const Char8 *szName, UInt32 uiId) :
    Inherited(szName, uiId)
{
}

/** \brief Destructor
 */

Thread::~Thread(void)
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

