/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

char OSGPThreadBase::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

void OSGPThreadBase::setAspect(OSGUInt32 aspect)
{
#ifdef OSG_ASPECT_USE_PTHREADKEY
    OSGUInt32 *uintP;

    uintP  = (OSGUInt32 *) pthread_getspecific(_aspectKey);

    *uintP = aspect;
#endif

#ifdef OSG_ASPECT_USE_PTHREADSELF
    pthread_t threadId = pthread_self(); 

    _aspectsA[threadId & 0x00FF] = aspect;
#endif

#ifdef OSG_ASPECT_USE_CUSTOMSELF
    pthread_t threadId = gThreadSelf(); 

    _aspectsA[threadId] = aspect;
#endif
}

OSGUInt32 OSGPThreadBase::getAspect(void)
{
#ifdef OSG_ASPECT_USE_PTHREADKEY
    OSGUInt32 *uintP;

    uintP = (OSGUInt32 *) pthread_getspecific(_aspectKey);

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

OSGThread *OSGPThreadBase::getCurrent(void)
{
#ifdef OSG_ASPECT_USE_PTHREADKEY
    OSGThread **threadP;

    threadP = (OSGThread **) pthread_getspecific(_threadKey);

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

OSGChangeList *OSGPThreadBase::getCurrentChangeList(void)
{
#ifdef OSG_ASPECT_USE_PTHREADKEY
    OSGChangeList **cListP;

    cListP = (OSGChangeList *) pthread_getspecific(_changelistKey);

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


void OSGPThreadBase::join(OSGPThreadBase *threadP)
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

#ifdef OSG_ASPECT_USE_PTHREADKEY
pthread_key_t OSGPThreadBase::_aspectKey;
pthread_key_t OSGPThreadBase::_threadKey;
pthread_key_t OSGPThreadBase::_changelistKey;
#endif

#if defined(OSG_ASPECT_USE_PTHREADSELF) || \
    defined(OSG_ASPECT_USE_CUSTOMSELF)
#ifdef OSG_COMPILETIME_NUM_ASPECTS
OSGUInt16      OSGPThreadBase::_aspectsA[OSG_NUM_ASPECTS];
OSGThread     *OSGPThreadBase::_threadsA[OSG_NUM_ASPECTS];
OSGChangeList *OSGPThreadBase::_changelistsA[OSG_NUM_ASPECTS];
#endif
#ifdef OSG_RUNTIME_NUM_ASPECTS
OSGUInt16      *OSGPThreadBase::_aspectsA = NULL;
OSGThread     **OSGPThreadBase::_threadsA = NULL;
OSGChangeList **OSGPThreadBase::_changelistsA = NULL;
#endif
#endif

void *OSGPThreadBase::threadFunc(void *threadArgP)
{
    void **argsP = (void **) threadArgP;

    if(argsP != NULL)
    {
        init((OSGThread *) argsP[2]);

        if(argsP[0] != NULL)
        {
            OSGThreadFuncF threadFuncF = (OSGThreadFuncF) argsP[0];

            threadFuncF(argsP[1]);
        }
    }    

    return NULL;
}

void OSGPThreadBase::createAspect(void)
{
#ifdef OSG_ASPECT_USE_PTHREADKEY
    OSGUInt32 *uintP = new OSGUInt32;

    *uintP = 0;

    pthread_setspecific(_aspectKey, (void *) uintP);  
#endif

#ifdef OSG_ASPECT_USE_PTHREADSELF
    pthread_t threadId = pthread_self(); 

    _aspectsA[threadId & 0x00FF] = 0;
#endif

#ifdef OSG_ASPECT_USE_CUSTOMSELF
    pthread_t threadId = gThreadSelf(); 

    _aspectsA[threadId] = 0;
#endif
}

void OSGPThreadBase::createThreadP(void)
{
#ifdef OSG_ASPECT_USE_PTHREADKEY
    OSGThread **threadP = new OSGThread *;

    *threadP = 0;

    pthread_setspecific(_threadKey, (void *) threadP);  
#endif

#ifdef OSG_ASPECT_USE_PTHREADSELF
    pthread_t threadId = pthread_self(); 

    _threadsA[threadId & 0x00FF] = NULL;
#endif

#ifdef OSG_ASPECT_USE_CUSTOMSELF
    pthread_t threadId = gThreadSelf(); 

    _threadsA[threadId] = NULL;
#endif
}

void OSGPThreadBase::createChangeListP(void)
{
#ifdef OSG_ASPECT_USE_PTHREADKEY
    OSGChangeList **changelistP = new OSGChangeList *;

    *changelistP = new OSGChangeList;

    pthread_setspecific(_changelistKey, (void *) changelistP);  
#endif

#ifdef OSG_ASPECT_USE_PTHREADSELF
    pthread_t threadId = pthread_self(); 

    _changelistsA[threadId & 0x00FF] = new OSGChangeList;
#endif

#ifdef OSG_ASPECT_USE_CUSTOMSELF
    pthread_t threadId = gThreadSelf(); 

    _changelistsA[threadId] = new OSGChangeList;
#endif
}

#ifdef OSG_ASPECT_USE_PTHREADKEY
void OSGPThreadBase::freeAspect(void *aspectP)
{
    OSGUInt32 *uintP = (OSGUInt32 *) aspectP;

    if(uintP != NULL)
        delete uintP;
}

void OSGPThreadBase::freeThreadP(void *threadP)
{
    OSGThread *tP = (OSGThread *) threadP;

    if(tP != NULL)
        delete tP;    
}

void OSGPThreadBase::freeChangeListP(void *changelistP)
{
    OSGChangeList *clP = (OSGChangeList *) changelistP;

    if(clP != NULL)
        delete clP;
}
#endif

void OSGPThreadBase::setCurrent(OSGThread *threadP)
{
#ifdef OSG_ASPECT_USE_PTHREADKEY
    OSGThread **threadPP;

    threadPP = (OSGThread **) pthread_getspecific(_threadKey);

    *threadPP = threadP;
#endif

#ifdef OSG_ASPECT_USE_PTHREADSELF
    pthread_t threadId = pthread_self(); 

    _threadsA[threadId & 0x00FF] = threadP;
#endif

#ifdef OSG_ASPECT_USE_CUSTOMSELF
    pthread_t threadId = gThreadSelf(); 

    _threadsA[threadId] = threadP;
#endif
}

void OSGPThreadBase::init(OSGThread *thisP)
{
    createAspect();        
    createThreadP();        
    setCurrent(thisP);
    createChangeListP();        
}

OSGPThreadBase *OSGPThreadBase::create(const char *szName, 
                                       OSGUInt32 threadId)
{
    return new OSGPThreadBase(szName, threadId);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

OSGPThreadBase::~OSGPThreadBase(void)
{
    delete [] _szName;

    delete    _threadDescP;
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

OSGBool OSGPThreadBase::run(OSGThreadFuncF threadFunc, void *threadArgP)
{
    if(threadFunc != NULL)
    {
        if(_threadDescP == NULL)
            _threadDescP = new pthread_t;

        _threadDataA[0] = (void *) threadFunc;
        _threadDataA[1] =          threadArgP;
        _threadDataA[2] = (void *) this;

		pthread_create(_threadDescP, 
                        NULL,
                        OSGPThreadBase::threadFunc,
                        (void *) &_threadDataA);
    }
}

void OSGPThreadBase::print(void)
{
    fprintf(stderr, "OSGPThreadBase -%s-%d-\n", _szName, _threadId);
}

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

OSGPThreadBase::OSGPThreadBase(const char *szName, OSGUInt32 threadId) :
    _szName(NULL),
    _threadId(threadId),
    _threadDescP(NULL)
{
    stringDup(szName, _szName);

    _threadDataA[0] = NULL;
    _threadDataA[1] = NULL;
    _threadDataA[2] = NULL;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

#endif /* OSG_USE_PTHREADS */

#if defined (OSG_USE_SPROC)

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGSprocBase::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


OSGUInt32 OSGSprocBase::getAspect(void)
{
    return ((ProcessData *) PRDA->usr_prda.fill)->aspectId;
}

OSGThread *OSGSprocBase::getCurrent(void)
{
    return ((ProcessData *) PRDA->usr_prda.fill)->threadP;
}

OSGChangeList *OSGSprocBase::getCurrentChangeList(void)
{
    return ((ProcessData *) PRDA->usr_prda.fill)->changelistP;
}

void OSGSprocBase::join(OSGSprocBase *threadP)
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

void OSGSprocBase::setCurrent(OSGThread *threadP)
{
    ((ProcessData *) PRDA->usr_prda.fill)->threadP     = threadP;
}

void OSGSprocBase::threadFunc(void *threadArgP)
{
    void **argsP = (void **) threadArgP;

    if(argsP != NULL)
    {
        init((OSGThread *) argsP[2]);

        if(argsP[2] != NULL)
            ((OSGThread *) argsP[2])->setPid();

        if(argsP[0] != NULL)
        {
            OSGSprocFuncF threadFuncF = (OSGSprocFuncF) argsP[0];

            threadFuncF(argsP[1]);
        }
    }    
}

void OSGSprocBase::init(OSGThread *thisP)
{
    ((ProcessData *) PRDA->usr_prda.fill)->aspectId    = thisP->_aspectId;
    ((ProcessData *) PRDA->usr_prda.fill)->threadP     = thisP;

    if(thisP->_changeListP == NULL)
    {
        thisP->_changeListP = new OSGChangeList();

        ((ProcessData *) PRDA->usr_prda.fill)->changelistP = 
            thisP->_changeListP;
    }
    else
    {
        thisP->_changeListP->clearAll();
        thisP->_changeListP->setAspect(thisP->_aspectId);
    }
}

OSGSprocBase *OSGSprocBase::create(const char *szName, 
                                   OSGUInt32 threadId)
{
    return new OSGSprocBase(szName, threadId);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

OSGSprocBase::~OSGSprocBase(void)
{
    delete [] _szName;
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

OSGBool OSGSprocBase::run(OSGSprocFuncF  threadFunc, 
                          OSGUInt32      aspectId,
                          void          *threadArgP)
{
    OSGBool returnValue = true;
    int     rc          = 0;

    if(aspectId >= OSGThreadManager::getNumAspects())
    {
        SWARNING << "invalid aspect id" << endl;
        return false;
    }

    if(threadFunc != NULL)
    {
        _threadDataA[0] = (void *) threadFunc;
        _threadDataA[1] =          threadArgP;
        _threadDataA[2] = (void *) this;

        _aspectId = aspectId;

		rc = sproc(OSGSprocBase::threadFunc, PR_SALL, (void *) _threadDataA);

        if(rc == -1)
        {
            SFATAL << "run thread failed" << endl;
            returnValue = false;
        }
    }

    return returnValue;
}

OSGChangeList *OSGSprocBase::getChangeList(void)
{
    return _changeListP;
}

void OSGSprocBase::print(void)
{
    fprintf(stderr, "OSGSprocBase -%s-%d-\n", _szName, _threadId);
}

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

OSGSprocBase::OSGSprocBase(const char *szName, OSGUInt32 threadId) :    
    _szName(NULL),
    _threadId(threadId),
    _aspectId(0),
    _changeListP(NULL),
    _pid(NULL)
{
    stringDup(szName, _szName);
    
    _threadDataA[0] = NULL;
    _threadDataA[1] = NULL;
    _threadDataA[2] = NULL;    
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void OSGSprocBase::setPid(void)
{
    _pid = getpid();
}

void OSGSprocBase::setAspectInternal(OSGUInt32 aspect)
{
    ((ProcessData *) PRDA->usr_prda.fill)->aspectId = aspect;
}

#endif /* OSG_USE_SPROC */



#if defined (OSG_USE_WINTHREADS)

#if defined(OSG_ASPECT_USE_LOCALSTORAGE)
OSGUInt32 OSGWinThreadBase::_aspectKey = 0;
OSGUInt32 OSGWinThreadBase::_threadKey = 0;
OSGUInt32 OSGWinThreadBase::_changelistKey = 0;
#endif

#if defined(OSG_ASPECT_USE_DECLSPEC)
__declspec (thread) OSGUInt32      OSGWinThreadBase::_aspectKey   = 0;
__declspec (thread) OSGThread     *OSGWinThreadBase::_threadP     = NULL;
__declspec (thread) OSGChangeList *OSGWinThreadBase::_changelistP = NULL;
#endif

void OSGWinThreadBase::setAspect(OSGUInt32 aspect)
{
#ifdef OSG_ASPECT_USE_LOCALSTORAGE
    OSGUInt32 *uintP;

    uintP = (OSGUInt32 *) TlsGetValue(_aspectKey);

    *uintP = aspect;
#endif
#ifdef OSG_ASPECT_USE_DECLSPEC
	_aspectKey = aspect;
#endif
}

OSGUInt32 OSGWinThreadBase::getAspect(void)
{
#ifdef OSG_ASPECT_USE_LOCALSTORAGE
    OSGUInt32 *uintP;

    uintP = (OSGUInt32 *) TlsGetValue(_aspectKey);

    return *uintP;
#endif
#ifdef OSG_ASPECT_USE_DECLSPEC
	return _aspectKey;
#endif
}

OSGThread *OSGWinThreadBase::getCurrent(void)
{
#ifdef OSG_ASPECT_USE_LOCALSTORAGE
    OSGThread **threadP;

    threadP = (OSGThread **) TlsGetValue(_threadKey);

    return *threadP;
#endif
#ifdef OSG_ASPECT_USE_DECLSPEC
	return _threadP;
#endif
}
        
OSGChangeList *OSGWinThreadBase::getCurrentChangeList(void)
{
#ifdef OSG_ASPECT_USE_LOCALSTORAGE
    OSGChangeList **cListP;

    cListP = (OSGChangeList **) TlsGetValue(_changelistKey);

    return *cListP;
#endif
#ifdef OSG_ASPECT_USE_DECLSPEC
	return _changelistP;
#endif
}

void OSGWinThreadBase::join(OSGWinThreadBase *threadP)
{
	if(threadP != NULL)
		WaitForSingleObject(threadP->_externalHandle, INFINITE);
}

OSGWinThreadBase::~OSGWinThreadBase(void)
{
	delete [] _szName;
}

OSGBool OSGWinThreadBase::run(OSGWinThreadFuncF threadFunc, void *threadArgP)
{
    OSGHandle rc = 0;
	OSGDWord  tmp;

    if(threadFunc != NULL)
    {
        _threadDataA[0] = (void *) threadFunc;
        _threadDataA[1] =          threadArgP;
        _threadDataA[2] = (void *) this;

		fprintf(stderr, "TF : %x %x %x %x\n", 
				_threadDataA,    _threadDataA[0], 
				_threadDataA[1], _threadDataA[2]);
		
		rc = CreateThread(NULL, 
						  0,    
                          (LPTHREAD_START_ROUTINE) OSGWinThreadBase::threadFunc, 
				          _threadDataA, 
						  0,    
						  &tmp);
		
		this->setExternalHandle(rc);

        if(rc == NULL)
        {
            fprintf(stderr, "create thread failed \n");
        }
    }

    return true;
}

void OSGWinThreadBase::print(void)
{
	fprintf(stderr, "OSGWinThreadBase -%s-%d-\n", _szName, _threadId);
}

OSGWinThreadBase::OSGWinThreadBase(const char *szName, OSGUInt32 threadId) :
	_szName(NULL),
	_threadId(threadId),
	_threadHandle(NULL),
	_externalHandle(NULL),
	_nativeThreadId(0)
{
    stringDup(szName, _szName);

    _threadDataA[0] = NULL;
    _threadDataA[1] = NULL;
    _threadDataA[2] = NULL;
}

void OSGWinThreadBase::threadFunc(void *threadArgP)
{
    void **argsP = (void **) threadArgP;

    if(argsP != NULL)
    {
        init((OSGThread *) argsP[2]);

        if(argsP[2] != NULL)
            ((OSGWinThreadBase *) argsP[2])->setPid();

        if(argsP[0] != NULL)
        {
            OSGWinThreadFuncF threadFuncF = (OSGWinThreadFuncF) argsP[0];

            threadFuncF(argsP[1]);
        }
    }    
}

void OSGWinThreadBase::init(OSGThread *thisP)
{
	createAspect();
    createThreadP(); 
    setCurrent(thisP);
    createChangeListP();        
}

void OSGWinThreadBase::createAspect(void)
{
#if defined (OSG_ASPECT_USE_LOCALSTORAGE)
	OSGUInt32 *uintP = new OSGUInt32;

	*uintP = 0;

	TlsSetValue(_aspectKey, uintP);
#endif

#if defined (OSG_ASPECT_USE_DECLSPEC)
	_aspectKey = 0;
#endif
}

void OSGWinThreadBase::createThreadP(void)
{
#if defined (OSG_ASPECT_USE_LOCALSTORAGE)
	OSGThread **threadP = new OSGThread *;

	*threadP = 0;

	TlsSetValue(_threadKey, threadP);
#endif

#if defined (OSG_ASPECT_USE_DECLSPEC)
	_aspectKey = 0;
    _threadP   = NULL;
#endif
}

void OSGWinThreadBase::createChangeListP(void)
{
#if defined (OSG_ASPECT_USE_LOCALSTORAGE)
	OSGChangeList **cListP = new OSGChangeList *;

	*cListP = new OSGChangeList;

	TlsSetValue(_changelistKey, cListP);
#endif

#if defined (OSG_ASPECT_USE_DECLSPEC)
	_changelistP = new OSGChangeList;
#endif
}

#if defined (OSG_ASPECT_USE_LOCALSTORAGE)
void OSGWinThreadBase::freeAspect(void *aspectP)
{
    OSGUInt32 *uintP;

    uintP = (OSGUInt32 *) TlsGetValue(_aspectKey);

	delete uintP;
}

void OSGWinThreadBase::freeThreadP(void *threadP)
{
//    OSGThread *threadP;

//    threadP = (OSGThread *) TlsGetValue(_threadKey);

//	delete threadP;
}

void OSGWinThreadBase::freeChangeListP(void *changelistP)
{
    OSGChangeList *cListP;

    cListP = (OSGChangeList *) TlsGetValue(_changelistKey);

	delete cListP;
}
#endif

void OSGWinThreadBase::setCurrent(OSGThread *threadP)
{
#ifdef OSG_ASPECT_USE_LOCALSTORAGE
    OSGThread **threadPP;

    threadPP = (OSGThread **) TlsGetValue(_threadKey);

    *threadPP = threadP;
#endif
#ifdef OSG_ASPECT_USE_DECLSPEC
	_threadP = threadP;
#endif
}

OSGWinThreadBase *OSGWinThreadBase::create(const char *szName, 
                                           OSGUInt32 threadId)
{
	return new OSGWinThreadBase(szName, threadId);
}

void OSGWinThreadBase::setPid(void)
{
	_threadHandle   = GetCurrentThread();
	_nativeThreadId = GetCurrentThreadId();
}

void OSGWinThreadBase::setExternalHandle(OSGHandle externalHandle)
{
	_externalHandle = externalHandle;
}

#endif /* OSG_USE_WINTHREADS */


const OSGUInt32 OSGThread::OSGInvalidAspect = 
    OSGTypeConstants<OSGUInt32>::getAllSet();


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

