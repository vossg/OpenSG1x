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

#define OSG_COMPILEFIELDCONTAINER

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGThreadManager.h"

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

char ThreadManager::cvsid[] = "@(#)$Id: $";

ThreadManager *ThreadManager::_pThreadManager      = NULL;
Thread        *ThreadManager::_pAppThread          = NULL;

Bool           ThreadManager::_bShutdownInProgress = false;
UInt32         ThreadManager::_uiNumAspects        = OSG_NUM_ASPECTS;

#ifdef OSG_RUNTIME_NUM_ASPECTS 
Bool           ThreadManager::_bNumAspectSet       = false;
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

Bool ThreadManager::initialize(Int32 &argc, Char8 **argv)
{
    return the()->init();
}

Bool ThreadManager::terminate (void)
{
    return the()->shutdown();
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

ThreadManager *ThreadManager::the(void)
{
    if(_pThreadManager == NULL)
        _pThreadManager = new ThreadManager();

    
    return _pThreadManager;
}

Thread *ThreadManager::getAppThread(void)
{
    return _pAppThread;
}

void ThreadManager::setNumAspects(UInt32 uiNumAspects)
{
#if defined(OSG_RUNTIME_NUM_ASPECTS)    
    if(_bNumAspectSet == false && uiNumAspects > 1)
    {
#if defined(OSG_ASPECT_USE_PTHREADSELF) || \
    defined(OSG_ASPECT_USE_CUSTOMSELF)
        UInt32  i;
        UInt16 *pAspect = new UInt16[uiNumAspects];

        for(i = 0; i < _uiNumAspects; i++)
            pAspect[i] = Thread::_pAspects[i];

        for(i = _uiNumAspects; i < uiNumAspects; i++)
            Thread::_pAspects[i] = 0;

        delete [] Thread::_pAspects;

        Thread::_pAspectsA = pAspect;
#endif
        _uiNumAspects   = uiNumAspects;
        _bNumAspectSet = true;        
    }    
#endif
}

UInt32 ThreadManager::getNumAspects(void)
{
    return _uiNumAspects;
}

ChangeList *ThreadManager::getChangeList(UInt32 uiAspectId)
{
    ChangeList *returnValue = NULL;

    if(uiAspectId < _uiNumAspects)
    {
    }
    
    return returnValue;
}

#if defined(OSG_USE_SPROC)
usptr_t *ThreadManager::getArena(void)
{
    return _pArena;
}
#endif

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

void ThreadManager::removeThread(Thread *pThread)
{
    if(_bShutdownInProgress == true)
        return;

    _storePLock->aquire();

    _sThreadStore.removeMPField(pThread);
    
    _storePLock->release();
}

void ThreadManager::removeBarrier(Barrier *pBarrier)
{
    if(_bShutdownInProgress == true)
        return;

    _storePLock->aquire();

    _sBarrierStore.removeMPField(pBarrier);
    
    _storePLock->release();
}

void ThreadManager::removeLock(Lock *pLock)
{
    if(_bShutdownInProgress == true)
        return;

    _storePLock->aquire();

    _sLockStore.removeMPField(pLock);
    
    _storePLock->release();
}

void ThreadManager::removeLockPool(LockPool *pLockPool)
{
    if(_bShutdownInProgress == true)
        return;

    _storePLock->aquire();

    _sLockPoolStore.removeMPField(pLockPool);
    
    _storePLock->release();
}

UInt32 ThreadManager::registerThreadType  (MPThreadType   *pType)
{
    return _sThreadStore.registerMPType(pType);
}

UInt32 ThreadManager::registerBarrierType (MPBarrierType  *pType)
{
    return _sBarrierStore.registerMPType(pType);
}

UInt32 ThreadManager::registerLockType    (MPLockType     *pType)
{
    return _sLockStore.registerMPType(pType);
}

UInt32 ThreadManager::registerLockPoolType(MPLockPoolType *pType)
{
    return _sLockPoolStore.registerMPType(pType);
}

Bool ThreadManager::init(void)
{
    Bool returnValue = true;

    SINFO << "OSGThreadManager init" << endl;

#ifdef OSG_ASPECT_USE_PTHREADKEY
    int rc; 

    rc = pthread_key_create(&(Thread::_aspectKey), 
                              Thread::freeAspect);

    rc = pthread_key_create(&(Thread::_threadKey), 
                              Thread::freeThread);

    rc = pthread_key_create(&(Thread::_changeListKey), 
                              Thread::freeChangeList);
#endif

#ifdef OSG_ASPECT_USE_PTHREADSELF
#ifdef OSG_RUNTIME_NUM_ASPECTS
    Thread::_pAspects     = new UInt16      [_uiNumAspects];
    Thread::_pThreads     = new Thread     *[_uiNumAspects];
    Thread::_pChangelists = new ChangeList *[_uiNumAspects];
#endif

   for(UInt32 i = 0; i < _uiNumAspects; i++)
    {
        Thread::_pAspects[i]     = 0;
        Thread::_pThreads[i]     = NULL;
        Thread::_pChangelists[i] = NULL;
    }
#endif

#if defined (OSG_ASPECT_USE_LOCALSTORAGE)		
	Thread::_aspectKey     = TlsAlloc();
	Thread::_threadKey     = TlsAlloc();
	Thread::_changeListKey = TlsAlloc();

	if(Thread::_aspectKey == 0xFFFFFFFF) 
		fprintf(stderr, "Local alloc failed\n");

	if(Thread::_threadKey == 0xFFFFFFFF) 
		fprintf(stderr, "Local alloc failed\n");

	if(Thread::_changeListKey == 0xFFFFFFFF) 
		fprintf(stderr, "Local alloc failed\n");
#endif

#if defined(OSG_USE_SPROC)
    usconfig(CONF_AUTOGROW,   1);
    usconfig(CONF_INITUSERS, 20);
    usconfig(CONF_INITSIZE, 10 * 1048576);
    usconfig(CONF_CHMOD, 0666);

    _pArena = usinit("/dev/zero");

    if(_pArena == NULL)
    {
        SFATAL << "OSGTM : could not initialize arena " << errno << endl;
        returnValue = false;
    }
    else
    {
        SINFO << "OSGTM : got arena " << _pArena << endl;
    }
#endif

    _storePLock = _sLockStore.getMPField("OSGTMStoreLock", "OSGLock");
    
    if(_storePLock == NULL)
    {
        SFATAL << "OSGTM : could not get table lock" << endl;

        returnValue = false;
    }
    else
    {
        SINFO << "OSGTM : got table lock " << _storePLock << endl;
    }

    _pAppThread = getThread("OSGApp");
    Thread::init(_pAppThread);

    if(_pAppThread == NULL)
    {
        SFATAL << "OSGTM : could not get application thread " << endl;

        returnValue = false;
    }
    else
    {
        SINFO << "OSGTM : got application thread " << _pAppThread << endl;
    }

    return returnValue;
}

Bool ThreadManager::shutdown(void)
{
    _bShutdownInProgress = true;

    _sThreadStore.clear();
    _sBarrierStore.clear();
    _sLockStore.clear();
    _sLockPoolStore.clear();

#if defined (OSG_ASPECT_USE_LOCALSTORAGE)		
    Thread::freeAspect();
    Thread::freeThread();
    Thread::freeChangeList();
#endif

#if defined(OSG_USE_SPROC)
    if(_pArena != NULL)
        usdetach(_pArena);
#endif

    return true;
}

ThreadManager::ThreadManager(void) :
    _sThreadStore  (),
    _sBarrierStore (),
    _sLockStore    (),
    _sLockPoolStore(),

    _storePLock    (NULL)
{
#if defined(_OSG_USE_SPROC_)
    _pArena = NULL;
#endif

    addMPInitFunction(initialize);
    addMPExitFunction(terminate);
}

ThreadManager::~ThreadManager(void)
{
}


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

/** \brief Destructor
 */

/*------------------------------ access -----------------------------------*/

Thread *ThreadManager::getThread(const Char8 *szName,
                                       const Char8 *szTypeName)
{
    Thread *returnValue = NULL;

    _storePLock->aquire();

    returnValue = _sThreadStore.getMPField(szName, szTypeName);

    _storePLock->release();

    return returnValue;
}

Barrier *ThreadManager::getBarrier(const Char8 *szName,
                                         const Char8 *szTypeName)
{
    Barrier *returnValue = NULL;

    _storePLock->aquire();

    returnValue = _sBarrierStore.getMPField(szName, szTypeName);

    _storePLock->release();

    return returnValue;
}

Lock *ThreadManager::getLock(const Char8 *szName,
                                   const Char8 *szTypeName)
{
    Lock *returnValue = NULL;

    _storePLock->aquire();

    returnValue = _sLockStore.getMPField(szName, szTypeName);

    _storePLock->release();

    return returnValue;
}

LockPool *ThreadManager::getLockPool(const Char8 *szName,
                                           const Char8 *szTypeName)
{
    LockPool *returnValue = NULL;

    _storePLock->aquire();

    returnValue = _sLockPoolStore.getMPField(szName, szTypeName);

    _storePLock->release();

    return returnValue;
}

Thread  *ThreadManager::findThread (const Char8 *szName)
{
    Thread *returnValue = NULL;

    _storePLock->aquire();
    
    returnValue = _sThreadStore.findMPField(szName);

    _storePLock->release();

    return returnValue;
}

Barrier *ThreadManager::findBarrier(const Char8 *szName)
{
    Barrier *returnValue = NULL;

    _storePLock->aquire();
    
    returnValue = _sBarrierStore.findMPField(szName);

    _storePLock->release();

    return returnValue;
}

Lock *ThreadManager::findLock(const Char8 *szName)
{
    Lock *returnValue = NULL;

    _storePLock->aquire();
    
    returnValue = _sLockStore.findMPField(szName);

    _storePLock->release();

    return returnValue;
}

LockPool *ThreadManager::findLockPool(const Char8 *szName)
{
    LockPool *returnValue = NULL;

    _storePLock->aquire();
    
    returnValue = _sLockPoolStore.findMPField(szName);

    _storePLock->release();

    return returnValue;
}


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

