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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif /* OSG_STREAM_IN_STD_NAMESPACE */

#define OSG_COMPILEBASE

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
#endif

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

UInt32 ThreadCommonBase::_threadCount = 0;

char ThreadCommonBase::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/** \brief Constructor
 */

ThreadCommonBase::ThreadCommonBase(const Char8 *szName):
    _szName(NULL),
    _threadId(_threadCount++),
    _refCount(0),
    _aspectId(0),
    _changeListP(NULL)
{
    if(szName != NULL)
    {
        osgstringDup(szName, _szName);
    }
    else
    {
        _szName = new Char8[16];
        sprintf(_szName, "Thread_%d", _threadId);
    }
}

/** \brief Destructor
 */

ThreadCommonBase::~ThreadCommonBase(void)
{
    delete [] _szName;

    if(_changeListP != NULL)
        _changeListP->subRef();
}

void ThreadCommonBase::addRef(void)
{
    _refCount++;
}

void ThreadCommonBase::subRef(void)
{
    _refCount--;
}

Bool ThreadCommonBase::inUse(void)
{
    return _refCount <= 0;
}

void ThreadCommonBase::setAspect(UInt32 aspectId)
{
    _aspectId = aspectId;
}

void ThreadCommonBase::setChangeList(ChangeList *changeListP)
{
    if(_changeListP != NULL)
        _changeListP->subRef();

    _changeListP = changeListP;

    if(_changeListP != NULL)
        _changeListP->addRef();
}

ChangeList *ThreadCommonBase::getChangeList(void)
{
    return _changeListP;
}


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/




#if defined (OSG_USE_PTHREADS)

#ifdef OSG_ASPECT_USE_CUSTOMSELF
extern "C"
{
extern pthread_t gThreadSelf(void);
}
#endif

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
UInt16      PThreadBase::_aspectsA    [OSG_NUM_ASPECTS];
Thread     *PThreadBase::_threadsA    [OSG_NUM_ASPECTS];
ChangeList *PThreadBase::_changelistsA[OSG_NUM_ASPECTS];
#endif
#ifdef OSG_RUNTIME_NUM_ASPECTS
UInt16      *PThreadBase::_aspectsA     = NULL;
Thread     **PThreadBase::_threadsA     = NULL;
ChangeList **PThreadBase::_changelistsA = NULL;
#endif
#endif

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

UInt32 PThreadBase::getAspect(void)
{
#ifdef OSG_ASPECT_USE_PTHREADKEY
    UInt32 *uintP;

    uintP = (UInt32 *) pthread_getspecific(_aspectKey);

    return *uintP;
#endif

#ifdef OSG_ASPECT_USE_PTHREADSELF
    pthread_t threadId = pthread_self(); 

    return _aspectsA[threadId & 0x00FF];
#endif

#ifdef OSG_ASPECT_USE_CUSTOMSELF
    pthread_t threadId = gThreadSelf(); 

    return _aspectsA[threadId];
#endif
}

Thread *PThreadBase::getCurrent(void)
{
#ifdef OSG_ASPECT_USE_PTHREADKEY
    Thread **threadP;

    threadP = (Thread **) pthread_getspecific(_threadKey);

    return *threadP;
#endif

#ifdef OSG_ASPECT_USE_PTHREADSELF
    pthread_t threadId = pthread_self(); 

    return _threadsA[threadId & 0x00FF];
#endif

#ifdef OSG_ASPECT_USE_CUSTOMSELF
    pthread_t threadId = gThreadSelf(); 

    return _threadsA[threadId];
#endif
}

ChangeList *PThreadBase::getCurrentChangeList(void)
{
#ifdef OSG_ASPECT_USE_PTHREADKEY
    ChangeList **cListP;

    cListP = (ChangeList **) pthread_getspecific(_changeListKey);

    return *cListP;
#endif

#ifdef OSG_ASPECT_USE_PTHREADSELF
    pthread_t threadId = pthread_self(); 

    return _changelistsA[threadId & 0x00FF];
#endif

#ifdef OSG_ASPECT_USE_CUSTOMSELF
    pthread_t threadId = gThreadSelf(); 

    return _changelistsA[threadId];
#endif
}


void PThreadBase::join(PThreadBase *threadP)
{
    if(threadP != NULL && threadP->_threadDescP != NULL)
    {
        pthread_join(*(threadP->_threadDescP), NULL);
    }
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void *PThreadBase::threadFunc(void *threadArgP)
{
    void **argsP = (void **) threadArgP;

    if(argsP != NULL)
    {
        if(argsP[2] != NULL)
        {
            init((Thread *) argsP[2]);

            if(argsP[0] != NULL)
            {
                ThreadFuncF threadFuncF = (ThreadFuncF) argsP[0];
                
                threadFuncF(argsP[1]);
            }
        }
    }    

    return NULL;
}

void PThreadBase::init(Thread *thisP)
{
    thisP->setupAspect     ();        
    thisP->setupThreadP    ();        
    thisP->setupChangeListP();        
    thisP->setupBlockCond  ();
}

PThreadBase *PThreadBase::create(const Char8 *szName)
{
    return new PThreadBase(szName);
}

void PThreadBase::destroy(PThreadBase *threadP)
{
    delete threadP;
}

#ifdef OSG_ASPECT_USE_PTHREADKEY
void PThreadBase::freeAspect(void *aspectP)
{
    UInt32 *uintP = (UInt32 *) aspectP;

    if(uintP != NULL)
        delete uintP;
}

void PThreadBase::freeThreadP(void *threadP)
{
    Thread **tP = (Thread **) threadP;

    if(tP != NULL)
        delete tP;    
}

void PThreadBase::freeChangeListP(void *changeListP)
{
    ChangeList **clP = (ChangeList **) changeListP;

    if(clP != NULL)
        delete clP;
}
#endif

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

Bool PThreadBase::run(ThreadFuncF  threadFunc, 
                      UInt32       aspectId,
                      void        *threadArgP)
{
    Bool  returnValue = true;
    Int32 rc          = 0;

    if(aspectId >= ThreadManager::getNumAspects())
    {
        SFATAL << "PTB : invalid aspect id" << endl;
        return false;
    }

    if(threadFunc != NULL)
    {
        if(_threadDescP == NULL)
            _threadDescP = new pthread_t;

        _threadDataA[0] = (void *) threadFunc;
        _threadDataA[1] =          threadArgP;
        _threadDataA[2] = (void *) this;

        Inherited::setAspect(aspectId);

		rc = pthread_create(_threadDescP, 
                            NULL,
                            PThreadBase::threadFunc,
                            (void *) &_threadDataA);

        if(rc != 0)
        {
            SFATAL << "PTB : pthread_create failed" << endl;
            returnValue = false;
        }
        
    }
    else
    {
        SFATAL << "PTB : no thread function given";
        returnValue = false;
    }

    return true;
}

void PThreadBase::block(void)
{
    pthread_mutex_lock  (_blockMutexP);
    pthread_cond_wait   (_blockCondP, _blockMutexP);
    pthread_mutex_unlock(_blockMutexP);
}

void PThreadBase::unblock(void)
{
    pthread_cond_broadcast(_blockCondP);
}

void PThreadBase::print(void)
{
    fprintf(stderr, "PThreadBase -%s-%d-\n", _szName, _threadId);
}

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

PThreadBase::PThreadBase(const Char8 *szName) :
    Inherited(szName),

    _threadDescP(NULL),
    _blockCondP (NULL),
    _blockMutexP(NULL)

{
    _threadDataA[0] = NULL;
    _threadDataA[1] = NULL;
    _threadDataA[2] = NULL;
}

PThreadBase::~PThreadBase(void)
{
    delete    _threadDescP;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void PThreadBase::setupAspect(void)
{
#ifdef OSG_ASPECT_USE_PTHREADKEY
    UInt32 *uintP = new UInt32;

    *uintP = Inherited::_aspectId;

    pthread_setspecific(_aspectKey, (void *) uintP);  
#endif

#ifdef OSG_ASPECT_USE_PTHREADSELF
    pthread_t threadId = pthread_self(); 

    _aspectsA[threadId & 0x00FF] = Inherited::_aspectId;
#endif

#ifdef OSG_ASPECT_USE_CUSTOMSELF
    pthread_t threadId = gThreadSelf(); 

    _aspectsA[threadId] = Inherited::_aspectId;
#endif
}

void PThreadBase::setupThreadP(void)
{
#ifdef OSG_ASPECT_USE_PTHREADKEY
    Thread **threadP = new Thread *;

    *threadP = (Thread *) this;

    pthread_setspecific(_threadKey, (void *) threadP);  
#endif

#ifdef OSG_ASPECT_USE_PTHREADSELF
    pthread_t threadId = pthread_self(); 

    fprintf(stderr, "PSelf(%d) : %d\n", Inherited::_aspectId, threadId);

    _threadsA[threadId & 0x00FF] = (Thread *) this;
#endif

#ifdef OSG_ASPECT_USE_CUSTOMSELF
    pthread_t threadId = gThreadSelf(); 

    _threadsA[threadId] = (Thread *) this;
#endif
}

void PThreadBase::setupChangeListP(void)
{
#ifdef OSG_ASPECT_USE_PTHREADKEY
    ChangeList **changeListPP = new ChangeList *;

    if(Inherited::_changeListP == NULL)
    {
        *changeListPP = new ChangeList;

        Inherited::setChangeList(*changeListPP);
    }
    else
    {
        *changeListPP = Inherited::_changeListP;
        
        (*changeListPP)->clearAll();
    }

    (*changeListPP)->setAspect(Inherited::_aspectId);
    pthread_setspecific(_changeListKey, (void *) changeListPP);  
#endif

#ifdef OSG_ASPECT_USE_PTHREADSELF
    ChangeList *changeListP;
    pthread_t      threadId = pthread_self(); 

    if(Inherited::_changeListP == NULL)
    {
        changeListP = new ChangeList;

        Inherited::setChangeList(changeListP);
    }
    else
    {
        changeListP = Inherited::_changeListP;
        
        changeListP->clearAll();
    }

    changeListP->setAspect(Inherited::_aspectId);
    _changelistsA[threadId & 0x00FF] = changeListP;
#endif

#ifdef OSG_ASPECT_USE_CUSTOMSELF
    ChangeList *changeListP;
    pthread_t      threadId = gThreadSelf(); 

    if(Inherited::_changeListP == NULL)
    {
        changeListP = new ChangeList;

        Inherited::setChangeList(changeListP);
    }
    else
    {
        changeListP = Inherited::_changeListP;
        
        changeListP->clearAll();
    }

    changeListP->setAspect(Inherited::_aspectId);
    _changelistsA[threadId] = changeListP;
#endif
}

void PThreadBase::setupBlockCond(void)
{
    _blockCondP  = new pthread_cond_t;
    _blockMutexP = new pthread_mutex_t;

    pthread_cond_init (_blockCondP, NULL);
    pthread_mutex_init(_blockMutexP, NULL);
}

#endif /* OSG_USE_PTHREADS */

#if defined (OSG_USE_SPROC)

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
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


UInt32 SprocBase::getAspect(void)
{
    return ((ProcessData *) PRDA->usr_prda.fill)->_aspectId;
}

Thread *SprocBase::getCurrent(void)
{
    return ((ProcessData *) PRDA->usr_prda.fill)->_threadP;
}

ChangeList *SprocBase::getCurrentChangeList(void)
{
    return ((ProcessData *) PRDA->usr_prda.fill)->_changeListP;
}

void SprocBase::join(SprocBase *threadP)
{
    if(threadP != NULL)
        waitpid(threadP->_pid, NULL, 0);
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void *SprocBase::runInternal(void *threadP)
{
    SLOG << "run internal : " << threadP << endl;

    if(threadP != NULL)
    {
        ((Thread *) threadP)->threadFunc();
    }

    return NULL;
}

void SprocBase::threadFunc(void *threadArgP)
{
    void **argsP = (void **) threadArgP;

    if(argsP != NULL)
    {
        if(argsP[2] != NULL)
        {
            init((Thread *) argsP[2]);

            ((Thread *) argsP[2])->setPid();

            if(argsP[0] != NULL)
            {
                ThreadFuncF threadFuncF = (ThreadFuncF) argsP[0];

                threadFuncF(argsP[1]);
            }
        }
    }    
}

void SprocBase::init(Thread *thisP)
{
    thisP->setAspectInternal      (thisP->_aspectId);
    thisP->setCurrentInternal     (thisP);
    thisP->setupChangeListInternal();
}

SprocBase *SprocBase::create(const Char8 *szName)
{
    return new SprocBase(szName);
}

void SprocBase::destroy(SprocBase *threadP)
{
    delete threadP;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

Bool SprocBase::run(ThreadFuncF  threadFunc, 
                    UInt32       aspectId,
                    void        *threadArgP)
{
    Bool  returnValue = true;
    Int32 rc          = 0;

    if(aspectId >= ThreadManager::getNumAspects())
    {
        SFATAL << "SPB : invalid aspect id" << endl;
        return false;
    }

    if(threadFunc != NULL)
    {
        _threadDataA[0] = (void *) threadFunc;
        _threadDataA[1] =          threadArgP;
        _threadDataA[2] = (void *) this;

        Inherited::setAspect(aspectId);

		rc = sproc(SprocBase::threadFunc, PR_SALL, (void *) _threadDataA);

        if(rc == -1)
        {
            SFATAL << "SPB : sproc thread failed" << endl;
            returnValue = false;
        }
    }
    else
    {
        SFATAL << "SPB : no thread function given";
        returnValue = false;
    }

    return returnValue;
}

Bool SprocBase::run(UInt32 aspectId)
{
    SLOG << "run : " << this << endl;

    run(SprocBase::runInternal, aspectId, (void *) this);

    return true;
}

void SprocBase::block(void)
{
    blockproc(_pid);
}

void SprocBase::unblock(void)
{
    unblockproc(_pid);
}

void SprocBase::print(void)
{
    fprintf(stderr, "SprocBase -%s-%d-\n", _szName, _threadId);
}

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

SprocBase::SprocBase(const Char8 *szName) :    
    Inherited(szName),

    _pid(NULL)
{
    _threadDataA[0] = NULL;
    _threadDataA[1] = NULL;
    _threadDataA[2] = NULL;    
}

SprocBase::~SprocBase(void)
{
}

void SprocBase::threadFunc(void)
{
    SWARNING << "Default thread function called " << endl;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void SprocBase::setPid(void)
{
    _pid = getpid();
}

void SprocBase::setAspectInternal(UInt32 aspect)
{
    ((ProcessData *) PRDA->usr_prda.fill)->_aspectId = aspect;
}

void SprocBase::setCurrentInternal(Thread *threadP)
{
    ((ProcessData *) PRDA->usr_prda.fill)->_threadP  = threadP;
}

void SprocBase::setupChangeListInternal(void)
{
    if(Inherited::_changeListP == NULL)
    {
        ((ProcessData *) PRDA->usr_prda.fill)->_changeListP = 
            new ChangeList();

        Inherited::setChangeList(
            ((ProcessData *) PRDA->usr_prda.fill)->_changeListP);
    }
    else
    {
        ((ProcessData *) PRDA->usr_prda.fill)->_changeListP = 
            Inherited::_changeListP;

        Inherited::_changeListP->clearAll();
    }

    Inherited::_changeListP->setAspect(Inherited::_aspectId);
}

#endif /* OSG_USE_SPROC */






#if defined (OSG_USE_WINTHREADS)

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
__declspec (thread) UInt32      WinThreadBase::_aspectLocal      = 0;
__declspec (thread) Thread     *WinThreadBase::_threadLocalP     = NULL;
__declspec (thread) ChangeList *WinThreadBase::_changeListLocalP = NULL;
#endif


/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

UInt32 WinThreadBase::getAspect(void)
{
#ifdef OSG_ASPECT_USE_LOCALSTORAGE
    UInt32 *uintP;

    uintP = (UInt32 *) TlsGetValue(_aspectKey);

    return *uintP;
#endif
#ifdef OSG_ASPECT_USE_DECLSPEC
	return _aspectLocal;
#endif
}

Thread *WinThreadBase::getCurrent(void)
{
#ifdef OSG_ASPECT_USE_LOCALSTORAGE
    Thread **threadP;

    threadP = (Thread **) TlsGetValue(_threadKey);

    return *threadP;
#endif
#ifdef OSG_ASPECT_USE_DECLSPEC
	return _threadLocalP;
#endif
}
        
ChangeList *WinThreadBase::getCurrentChangeList(void)
{
#ifdef OSG_ASPECT_USE_LOCALSTORAGE
    ChangeList **cListP;

    cListP = (ChangeList **) TlsGetValue(_changeListKey);

    return *cListP;
#endif
#ifdef OSG_ASPECT_USE_DECLSPEC
	return _changeListLocalP;
#endif
}

void WinThreadBase::join(WinThreadBase *threadP)
{
	if(threadP != NULL)
		WaitForSingleObject(threadP->_externalHandle, INFINITE);
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

#if defined (OSG_ASPECT_USE_LOCALSTORAGE)
void WinThreadBase::freeAspect(void)
{
    UInt32 *uintP;

    uintP = (UInt32 *) TlsGetValue(_aspectKey);

	delete uintP;
}

void WinThreadBase::freeThreadP(void)
{
    Thread **threadPP;

    threadPP = (Thread **) TlsGetValue(_threadKey);

	delete threadPP;
}

void WinThreadBase::freeChangeListP(void)
{
    ChangeList **cListPP;

    cListPP = (ChangeList **) TlsGetValue(_changeListKey);

	delete cListPP;
}
#endif

void WinThreadBase::threadFunc(void *threadArgP)
{
    void **argsP = (void **) threadArgP;

    if(argsP != NULL)
    {
        if(argsP[2] != NULL)
        {
            init((Thread *) argsP[2]);

            ((WinThreadBase *) argsP[2])->setPid();
        }

        if(argsP[0] != NULL)
        {
            ThreadFuncF threadFuncF = (ThreadFuncF) argsP[0];

            threadFuncF(argsP[1]);
        }
    }    
}

void WinThreadBase::init(Thread *thisP)
{
	thisP->setupAspect();
    thisP->setupThreadP(); 
    thisP->setupChangeListP();        
}

WinThreadBase *WinThreadBase::create(const Char8 *szName)
{
	return new WinThreadBase(szName);
}

void WinThreadBase::destroy(WinThreadBase *threadP)
{
    delete threadP;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

Bool WinThreadBase::run(ThreadFuncF  threadFunc, 
                        UInt32       aspectId,  
                        void        *threadArgP)
{
    Bool   returnValue = true;
    Handle rc          = 0;
	DWord  tmp;

    if(aspectId >= ThreadManager::getNumAspects())
    {
        SFATAL << "WTB : invalid aspect id" << endl;
        return false;
    }

    if(threadFunc != NULL)
    {
        _threadDataA[0] = (void *) threadFunc;
        _threadDataA[1] =          threadArgP;
        _threadDataA[2] = (void *) this;

        Inherited::setAspect(aspectId);

		fprintf(stderr, "TF : %x %x %x %x\n", 
				_threadDataA,    _threadDataA[0], 
				_threadDataA[1], _threadDataA[2]);
		
		rc = CreateThread(NULL, 
						  0,    
                          (LPTHREAD_START_ROUTINE) ThreadBase::threadFunc, 
				          _threadDataA, 
						  0,    
						  &tmp);
		
		this->setExternalHandle(rc);

        if(rc == NULL)
        {
            SFATAL << "WTB : sproc thread failed" << endl;
            returnValue = false;
        }
    }
    else
    {
        SFATAL << "WTB : no thread function given";
        returnValue = false;
    }

    return returnValue;
}

void WinThreadBase::block(void)
{
    SuspendThread(_threadHandle);
}

void WinThreadBase::unblock(void)
{
    ResumeThread(_externalHandle);
}

void WinThreadBase::print(void)
{
	fprintf(stderr, "WinThreadBase -%s-%d-\n", _szName, _threadId);
}

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/** \brief Constructor
 */

WinThreadBase::WinThreadBase(const Char8 *szName) :
    Inherited(szName),

	_threadHandle(NULL),
	_externalHandle(NULL),
	_nativeThreadId(0)
{
    _threadDataA[0] = NULL;
    _threadDataA[1] = NULL;
    _threadDataA[2] = NULL;
}

/** \brief Destructor
 */


WinThreadBase::~WinThreadBase(void)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void WinThreadBase::setPid(void)
{
	_threadHandle   = GetCurrentThread();
	_nativeThreadId = GetCurrentThreadId();
}

void WinThreadBase::setExternalHandle(Handle externalHandle)
{
	_externalHandle = externalHandle;
}


void WinThreadBase::setupAspect(void)
{
#ifdef OSG_ASPECT_USE_LOCALSTORAGE
    UInt32 *uintP = new UInt32;

    *uintP = Inherited::_aspectId;

    TlsSetValue(_aspectKey, uintP);
#endif

#ifdef OSG_ASPECT_USE_DECLSPEC
	_aspectLocal = Inherited::_aspectId;
#endif
}

void WinThreadBase::setupThreadP(void)
{
#if defined (OSG_ASPECT_USE_LOCALSTORAGE)
	Thread **threadP = new Thread *;

	*threadP = (Thread *) this;

	TlsSetValue(_threadKey, threadP);
#endif

#if defined (OSG_ASPECT_USE_DECLSPEC)
    _threadLocalP = (Thread *) this;
#endif
}

void WinThreadBase::setupChangeListP(void)
{
#if defined (OSG_ASPECT_USE_LOCALSTORAGE)
	ChangeList **changeListPP = new ChangeList *;

   if(Inherited::_changeListP == NULL)
    {
        *changeListPP = new ChangeList;

        Inherited::setChangeList(*changeListPP);
    }
    else
    {
        *changeListPP = Inherited::_changeListP;
        
        (*changeListPP)->clearAll();
    }

    (*changeListPP)->setAspect(Inherited::_aspectId);
	TlsSetValue(_changeListKey, changeListPP);
#endif

#if defined (OSG_ASPECT_USE_DECLSPEC)
    if(Inherited::_changeListP == NULL)
    {
        _changeListLocalP = new ChangeList;
        Inherited::setChangeList(_changeListLocalP);
    }
    else
    {
        _changeListLocalP = Inherited::_changeListP;

        _changeListLocalP->clearAll();
    }

    _changeListLocalP->setAspect(Inherited::_aspectId);
#endif
}

#endif /* OSG_USE_WINTHREADS */


const UInt32 Thread::InvalidAspect = 
    TypeConstants<UInt32>::getAllSet();


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

