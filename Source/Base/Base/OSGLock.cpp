/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include "OSGLock.h"

#include "OSGLock.h"

#include "OSGBaseFunctions.h"

#include "OSGThreadManager.h"

#include <errno.h>
#include <OSGLog.h>

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*--------------------------- Constructors --------------------------------*/

LockCommonBase::LockCommonBase(void) :
     Inherited(NULL),
    _uiLockId (0   )
{
}

LockCommonBase::LockCommonBase(const Char8  *szName,
                                     UInt32  uiId  ):
     Inherited(szName),
    _uiLockId (uiId  )
{
}

/*---------------------------- Destructor ---------------------------------*/

LockCommonBase::~LockCommonBase(void)
{
}



#if defined (OSG_USE_PTHREADS)

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*--------------------------- Constructors --------------------------------*/

PThreadLockBase::PThreadLockBase(void):
     Inherited    (),
    _pLowLevelLock()
{
}

PThreadLockBase::PThreadLockBase(const Char8  *szName,
                                       UInt32  uiId  ) :
     Inherited    (szName, uiId),
    _pLowLevelLock()
{
}

/*---------------------------- Destructor ---------------------------------*/

PThreadLockBase::~PThreadLockBase(void)
{
}

/*--------------------------- Construction --------------------------------*/

bool PThreadLockBase::init(void)
{
    pthread_mutexattr_t lockAttr;

    pthread_mutexattr_init(&lockAttr);

    pthread_mutexattr_settype(&lockAttr, PTHREAD_MUTEX_RECURSIVE);
        
    pthread_mutex_init(&(_pLowLevelLock), &lockAttr);

    return true;
}

/*--------------------------- Destruction ---------------------------------*/

void PThreadLockBase::shutdown(void)
{
    pthread_mutex_destroy(&(_pLowLevelLock));
}

/*------------------------------- Lock ------------------------------------*/

void PThreadLockBase::aquire(void)
{
    pthread_mutex_lock(&(_pLowLevelLock));
}

void PThreadLockBase::release(void)
{
    pthread_mutex_unlock(&(_pLowLevelLock));
}

bool PThreadLockBase::request(void)
{
    return (pthread_mutex_trylock(&(_pLowLevelLock)) != EBUSY);
}

#endif /* OSG_USE_PTHREADS */




#if defined (OSG_USE_SPROC)

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*--------------------------- Constructors --------------------------------*/

SprocLockBase::SprocLockBase(void):
     Inherited    (    ),
#ifdef OSG_SPROC_USE_LOCK
    _pLowLevelLock(NULL)
#else
    _pLowLevelSema(NULL)
#endif
{
}

SprocLockBase::SprocLockBase(const Char8  *szName,
                                   UInt32  uiId  ):
     Inherited    (szName, uiId),
#ifdef OSG_SPROC_USE_LOCK
    _pLowLevelLock(NULL        )
#else
    _pLowLevelSema(NULL        )
#endif
{
}

/*---------------------------- Destructor ---------------------------------*/

SprocLockBase::~SprocLockBase(void)
{
}

/*--------------------------- Construction --------------------------------*/

bool SprocLockBase::init(void)
{
    ThreadManager *pThreadManager = ThreadManager::the();

    if(pThreadManager == NULL)
        return false;

    if(pThreadManager->getArena() == NULL)
        return false;

#ifdef OSG_SPROC_USE_LOCK
    _pLowLevelLock = usnewlock(pThreadManager->getArena());

    if(_pLowLevelLock == NULL)
        return false;

    usinitlock(_pLowLevelLock);

#else
    _pLowLevelSema = usnewsema(pThreadManager->getArena(), 1);

    if(_pLowLevelSema == NULL)
        return false;

    usinitsema(_pLowLevelSema, 1);
    usctlsema (_pLowLevelSema, CS_RECURSIVEON, NULL);
#endif

    return true;
}

/*--------------------------- Destruction ---------------------------------*/

void SprocLockBase::shutdown(void)
{
    ThreadManager *pThreadManager = ThreadManager::the();

    if(pThreadManager == NULL)
        return;

    if(pThreadManager->getArena() == NULL)
        return;

#ifdef OSG_SPROC_USE_LOCK
    if(_pLowLevelLock != NULL)
    {
        usfreelock(_pLowLevelLock, pThreadManager->getArena());
    
        _pLowLevelLock = NULL;
    }
#else
    if(_pLowLevelSema != NULL)
    {
        usfreesema(_pLowLevelSema, pThreadManager->getArena());

        _pLowLevelSema = NULL;
    }
#endif

}

/*------------------------------- Lock ------------------------------------*/

void SprocLockBase::aquire(void)
{
#ifdef OSG_SPROC_USE_LOCK
    if(_pLowLevelLock != NULL)
        ussetlock(_pLowLevelLock);
#else
    if(_pLowLevelSema != NULL)
        uspsema(_pLowLevelSema);
#endif
}

void SprocLockBase::release(void)
{
#ifdef OSG_SPROC_USE_LOCK
    if(_pLowLevelLock != NULL)
        usunsetlock(_pLowLevelLock);
#else
    if(_pLowLevelSema != NULL)
        usvsema(_pLowLevelSema);
#endif
}

bool SprocLockBase::request(void)
{
    bool  returnValue = false;
    Int32 rc          = 0;

#ifdef OSG_SPROC_USE_LOCK
    if(_pLowLevelLock != NULL)
        rc = uscsetlock(_pLowLevelLock, 0);
#else
    if(_pLowLevelSema != NULL)
        rc = uscpsema(_pLowLevelSema);
#endif

    returnValue = (rc == 1);

    return returnValue;
}

#endif /* OSG_USE_SPROC */



#if defined (OSG_USE_WINTHREADS)

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*--------------------------- Constructors --------------------------------*/

WinThreadLockBase::WinThreadLockBase(void) :
       Inherited(    )
#ifdef OSG_WINLOCK_USE_MUTEX
    , _pMutex   (NULL)
#endif
{
}

WinThreadLockBase::WinThreadLockBase(const Char8  *szName,
                                           UInt32  uiId  ) :
       Inherited(szName, uiId)
#ifdef OSG_WINLOCK_USE_MUTEX
    , _pMutex   (NULL        )
#endif
{
}

/*---------------------------- Destructor ---------------------------------*/

WinThreadLockBase::~WinThreadLockBase(void)
{
}

/*-------------------------- Construction ---------------------------------*/

bool WinThreadLockBase::init(void)
{
#ifdef OSG_WINLOCK_USE_MUTEX
    _pMutex = CreateMutex( NULL,     // no security attributes
                           FALSE,    // initially not owned
                          _szName);  // name of mutex

    if(_pMutex == NULL)
    {
        return false;
    }

    return true;
#else
    InitializeCriticalSection(&_pCriticalSection);

    return true;
#endif
}

/*-------------------------- Destruction ----------------------------------*/

void WinThreadLockBase::shutdown(void)
{
#ifdef OSG_WINLOCK_USE_MUTEX
    if(_pMutex != NULL)
    {
        CloseHandle(_pMutex);
    }
#else
    DeleteCriticalSection(&_pCriticalSection);
#endif
}

/*------------------------------- Lock ------------------------------------*/

void WinThreadLockBase::aquire(void)
{
#if defined(OSG_GV_BETA) && defined(OSG_DBG_LCK)
    fprintf(stderr, "Lock::aquire %p\n", this);
#endif

#ifdef OSG_WINLOCK_USE_MUTEX
    WaitForSingleObject(_pMutex, INFINITE);
#else
    EnterCriticalSection(&_pCriticalSection);
#endif
}

void WinThreadLockBase::release(void)
{
#if defined(OSG_GV_BETA) && defined(OSG_DBG_LCK)
    fprintf(stderr, "Lock::release %p\n", this);
#endif

#ifdef OSG_WINLOCK_USE_MUTEX
    ReleaseMutex(_pMutex);
#else
    LeaveCriticalSection(&_pCriticalSection);
#endif
}

bool WinThreadLockBase::request(void)
{
#ifdef OSG_WINLOCK_USE_MUTEX
    DWORD rc;
    rc = WaitForSingleObject(_pMutex, 0);

    if(rc == WAIT_OBJECT_0)
    {
        return true;
    }
    else
    {
        return false;
    }
#else
    return (TryEnterCriticalSection(&_pCriticalSection) != FALSE);
#endif
}

#endif /* OSG_USE_WINTHREADS */



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

MPLockType Lock::_type("OSGLock", "OSGMPBase", &Lock::create);

/*------------------------------- Get -------------------------------------*/

Lock *Lock::get(const Char8 *szName)
{
    return ThreadManager::the()->getLock(szName, "OSGLock");
}

Lock *Lock::find(const Char8 *szName)
{
    return ThreadManager::the()->findLock(szName);
}

Lock *Lock::create(void)
{
    return Lock::get(NULL);
}

const MPLockType &Lock::getClassType(void)
{
    return _type;
}

/*------------------------------- Lock ------------------------------------*/

void Lock::aquire(void)
{
    Inherited::aquire();
}

void Lock::release(void)
{
    Inherited::release();
}

bool Lock::request(void)
{
    return Inherited::request();
}

/*------------------------------ Create -----------------------------------*/

Lock *Lock::create(const Char8 *szName, UInt32 uiId)
{
    Lock *returnValue = NULL;

    returnValue = new Lock(szName, uiId);

    if(returnValue->init() == false)
    {
        delete returnValue;
        returnValue = NULL;
    }

    return returnValue;
}

/*--------------------------- Constructors --------------------------------*/

Lock::Lock(void) :
    Inherited()
{
}

Lock::Lock(const Char8 *szName, UInt32 uiId) :
    Inherited(szName, uiId)
{
}

/*---------------------------- Destructor ---------------------------------*/

Lock::~Lock(void)
{
    ThreadManager::the()->removeLock(this);

    shutdown();
}



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

MPLockPoolType LockPool::_type("OSGLockPool", "OSGMPBase", &LockPool::create);

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

LockPool *LockPool::get(const Char8 *szName)
{
    return ThreadManager::the()->getLockPool(szName, "OSGLockPool");
}

LockPool *LockPool::find(const Char8 *szName)
{
    return ThreadManager::the()->findLockPool(szName);
}

LockPool *LockPool::create(void)
{
    return LockPool::get(NULL);
}

/*------------------------------ Lock -------------------------------------*/

#ifdef OSG_WIN32_ICL
#pragma warning (disable : 171)
#endif

void LockPool::aquire(void *keyP)
{
    _pLocks[(UInt64(keyP) & uiLockPoolMask) >> 7].aquire();
}

void LockPool::release(void *keyP)
{
    _pLocks[(UInt64(keyP) & uiLockPoolMask) >> 7].release();
}

bool LockPool::request(void *keyP)
{
    return _pLocks[(UInt64(keyP) & uiLockPoolMask) >> 7].request();
}

#ifdef OSG_WIN32_ICL
#pragma warning (error : 171)
#endif

/*------------------------------ Create -----------------------------------*/

LockPool *LockPool::create(const Char8 *szName, UInt32 uiId)
{
    LockPool *returnValue = NULL;

    returnValue = new LockPool(szName, uiId);

    if(returnValue->init() == false)
    {
        delete returnValue;
        returnValue = NULL;
    }

    return returnValue;
}

/*--------------------------- Constructors --------------------------------*/

LockPool::LockPool(const Char8  *szName,
                         UInt32  uiId  ) :
    Inherited(szName, uiId)
{
}

/*---------------------------- Destructor ---------------------------------*/

LockPool::~LockPool(void)
{
    ThreadManager::the()->removeLockPool(this);

    shutdown();
}

/*--------------------------- Construction --------------------------------*/

bool LockPool::init(void)
{
    bool   returnValue = true;
    Char8 *pTmp;

    pTmp = new Char8[strlen(_szName) + 6];

    for(UInt32 i = 0; i < uiLockPoolSize; i++)
    {
#ifdef OSG_DEBUG_LOCK_STAT
        _pLockStats[i] = 0;
#endif
        sprintf(pTmp, "%s%u\n", _szName, i);

        stringDup(pTmp, _pLocks[i]._szName);

        returnValue &= _pLocks[i].init();
    }

    delete [] pTmp;

    return returnValue;
}

/*--------------------------- Destruction ---------------------------------*/

void LockPool::shutdown(void)
{
    for(UInt32 i = 0; i < uiLockPoolSize; i++)
    {
        _pLocks[i].shutdown();
    }
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGLOCK_HEADER_CVSID;
}
