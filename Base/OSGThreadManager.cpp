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

#include <OSGConfig.h>

#include <stdlib.h>
#include <stdio.h>

#include <errno.h>


#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif /* OSG_STREAM_IN_STD_NAMESPACE */ 

#include "OSGThreadManager.h"
#include "OSGThread.h"
#include "OSGBarrier.h"
#include "OSGLock.h"
#include "OSGLog.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char ThreadManager::cvsid[] = "@(#)$Id: $";

ThreadManager ThreadManager::_threadManagerP;

UInt32        ThreadManager::_numAspects   = OSG_NUM_ASPECTS;

#ifdef OSG_RUNTIME_NUM_ASPECTS 
Bool          ThreadManager::_numAspectSet = false;
#endif

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

ThreadManager *ThreadManager::the(void)
{
    return &_threadManagerP;
}

void ThreadManager::setNumAspects(UInt32 numAspects)
{
#if defined(OSG_RUNTIME_NUM_ASPECTS)    
    if(_numAspectSet == false && numAspects > 1)
    {
#if defined(OSG_ASPECT_USE_PTHREADSELF) || \
    defined(OSG_ASPECT_USE_CUSTOMSELF)
        UInt32  i;
        UInt16 *aspectA = new UInt16[numAspects];

        for(i = 0; i < _numAspects; i++)
            aspectA[i] = Thread::_aspectsA[i];

        for(i = _numAspects; i < numAspects; i++)
            Thread::_aspectsA[i] = 0;

        delete [] Thread::_aspectsA;

        Thread::_aspectsA = aspectA;
#endif
        _numAspects   = numAspects;
        _numAspectSet = true;        
    }    
#endif
}

UInt32 ThreadManager::getNumAspects(void)
{
    return _numAspects;
}

ChangeList *ThreadManager::getChangeList(UInt32 aspectId)
{
    ChangeList *returnValue = NULL;

    if(aspectId < _numAspects)
    {
    }
    
    return returnValue;
}

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

void ThreadManager::setThreadCreateFunc(CreateThreadF create)
{
    _createThreadF = create; 
}

void ThreadManager::setBarrierCreateFunc(CreateBarrierF create)
{
    _createBarrierF = create;
}

void ThreadManager::setLockCreateFunc(CreateLockF create)
{
    _createLockF = create;
}

void ThreadManager::setLockPoolCreateFunc(CreateLockPoolF create)
{
    _createLockPoolF = create;
}

void ThreadManager::setThreadDestroyFunc(DestroyThreadF destroy)
{
    _destroyThreadF = destroy;
}

void ThreadManager::setBarrierDestroyFunc(DestroyBarrierF destroy)
{
    _destroyBarrierF = destroy;
}

void ThreadManager::setLockDestroyFunc(DestroyLockF destroy)
{
    _destroyLockF = destroy;
}

void ThreadManager::setLockPoolDestroyFunc(DestroyLockPoolF destroy)
{
    _destroyLockPoolF = destroy;
}


/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

Thread *ThreadManager::getThread(const Char8 *szName)
{
    Thread *returnValue = NULL;

    if(_createThreadF != NULL)
    {
        if(szName == NULL)
        {
            returnValue = _createThreadF(szName);

            if(returnValue != NULL)
            {
                _tableLockP->aquire();
            
                _threadMapM[returnValue->_szName] = returnValue;

                _tableLockP->release();
            }
        }
        else
        {
            _tableLockP->aquire();

            ThreadMapIt gIt = _threadMapM.find(szName);
        
            if(gIt == _threadMapM.end())
            {
                returnValue = _createThreadF(szName);

                if(returnValue != NULL)
                {
                    _threadMapM[returnValue->_szName] = returnValue;
                }
            }
            else
            {
                returnValue = (*gIt).second;
            }

            _tableLockP->release();
        }
    }

    if(returnValue != NULL)
        returnValue->addRef();

    return returnValue;
}

Barrier *ThreadManager::getBarrier(const Char8 *szName)
{
    Barrier *returnValue = NULL;

    if(_createBarrierF != NULL)
    {
        if(szName == NULL)
        {
            returnValue = _createBarrierF(szName);

            if(returnValue != NULL)
            {
                _tableLockP->aquire();
                
                _barrierMapM[returnValue->_szName] = returnValue;
                
                _tableLockP->release();
            }
        }
        else
        {
            _tableLockP->aquire();

            BarrierMapIt gIt = _barrierMapM.find(szName);
        
            if(gIt == _barrierMapM.end())
            {
                returnValue = _createBarrierF(szName);

                if(returnValue != NULL)
                {
                    _barrierMapM[returnValue->_szName] = returnValue;
                }
            }
            else
            {
                returnValue = (*gIt).second;
            }

            _tableLockP->release();
        }
    }

    if(returnValue != NULL)
        returnValue->addRef();

    return returnValue;
}

Lock *ThreadManager::getLock(const Char8 *szName)
{
    Lock *returnValue = NULL;

    if(_createLockF != NULL)
    {
        if(szName == NULL)
        {
            returnValue = _createLockF(szName);

            if(returnValue != NULL)
            {
                _tableLockP->aquire();

                _lockMapM[returnValue->_szName] = returnValue;

                _tableLockP->release();
            }
        }
        else
        {
            _tableLockP->aquire();

            LockMapIt gIt = _lockMapM.find(szName);           
        
            if(gIt == _lockMapM.end())
            {
                returnValue = _createLockF(szName);

                if(returnValue != NULL)
                {
                    _lockMapM[returnValue->_szName] = returnValue;
                }
            }
            else
            {
                returnValue = (*gIt).second;
            }

            _tableLockP->release();
        }
    }

    if(returnValue != NULL)
        returnValue->addRef();

    return returnValue;
}

LockPool *ThreadManager::getLockPool(const Char8 *szName)
{
    LockPool *returnValue = NULL;

    if(_createLockPoolF != NULL)
    {
        if(szName == NULL)
        {
            returnValue = _createLockPoolF(szName);

            if(returnValue != NULL)
            {
                _tableLockP->aquire();
            
                _lockPoolMapM[returnValue->_szName] = returnValue;
                
                _tableLockP->release();
            }
        }
        else
        {
            _tableLockP->aquire();

            LockPoolMapIt gIt = _lockPoolMapM.find(szName);
        
            if(gIt == _lockPoolMapM.end())
            {
                returnValue = _createLockPoolF(szName);

                if(returnValue != NULL)
                {
                    _lockPoolMapM[returnValue->_szName] = returnValue;
                }
            }
            else
            {
                returnValue = (*gIt).second;
            }

            _tableLockP->release();
        }
    }

    if(returnValue != NULL)
        returnValue->addRef();

    return returnValue;
}

void ThreadManager::freeBarrier(Barrier *barrierP)
{
    if(barrierP != NULL)
    {
        _tableLockP->aquire();

        barrierP->subRef();

        if(barrierP->inUse() == false)
            removeBarrier(barrierP);

        _tableLockP->release();
    }
}

void ThreadManager::freeLock(Lock *lockP)
{
    if(lockP != NULL)
    {
        _tableLockP->aquire();

        lockP->subRef();

        if(lockP->inUse())
           removeLock(lockP);

        _tableLockP->release();
    }
}

void ThreadManager::freeLockPool(LockPool *lockPoolP)
{
    if(lockPoolP != NULL)
    {
        _tableLockP->aquire();

        lockPoolP->subRef();
        
        if(lockPoolP->inUse())
            removeLockPool(lockPoolP);

        _tableLockP->release();
    }
}

Thread  *ThreadManager::findThread (const Char8 *szName)
{
    Thread *returnValue = NULL;

    if(szName != NULL)
    {
        ThreadMapIt gIt;

        _tableLockP->aquire();
    
        gIt = _threadMapM.find(szName);

        if(gIt != _threadMapM.end())
            returnValue = (*gIt).second;

        _tableLockP->release();
    }

    return returnValue;
}

Barrier *ThreadManager::findBarrier(const Char8 *szName)
{
    Barrier *returnValue = NULL;

    if(szName != NULL)
    {
        BarrierMapIt gIt;

        _tableLockP->aquire();
    
        gIt = _barrierMapM.find(szName);

        if(gIt != _barrierMapM.end())
            returnValue = (*gIt).second;

        _tableLockP->release();
    }

    return returnValue;
}

Lock *ThreadManager::findLock(const Char8 *szName)
{
    Lock *returnValue = NULL;

    if(szName != NULL)
    {
        LockMapIt gIt;

        _tableLockP->aquire();

        gIt = _lockMapM.find(szName);

        if(gIt != _lockMapM.end())
            returnValue = (*gIt).second;

        _tableLockP->release();
    }

    return returnValue;
}

LockPool *ThreadManager::findLockPool(const Char8 *szName)
{
    LockPool *returnValue = NULL;

    if(szName != NULL)
    {
        LockPoolMapIt gIt;

        _tableLockP->aquire();
    
        gIt = _lockPoolMapM.find(szName);

        if(gIt != _lockPoolMapM.end())
            returnValue = (*gIt).second;

        _tableLockP->release();
    }

    return returnValue;
}

#if defined(OSG_USE_SPROC)
usptr_t *ThreadManager::getArena(void)
{
    return _arenaP;
}
#endif


/*-------------------------- assignment -----------------------------------*/


/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

void ThreadManager::removeBarrier(Barrier *barrierP)
{
    BarrierMapIt gIt = _barrierMapM.find(barrierP->_szName);

    if(gIt != _barrierMapM.end())
    {
        _barrierMapM.erase(gIt);
    }

    if(_destroyBarrierF != NULL)
    {
        _destroyBarrierF(barrierP);
    }
    else
    {
        delete barrierP;
    }
        
}

void ThreadManager::removeLock(Lock *lockP)
{
    LockMapIt gIt = _lockMapM.find(lockP->_szName);
    
    if(gIt != _lockMapM.end())
    {
        _lockMapM.erase(gIt);
    }

    if(_destroyLockF != NULL)
    {
        _destroyLockF(lockP);
    }
    else
    {
        delete lockP;
    }    
}

void ThreadManager::removeLockPool(LockPool *lockPoolP)
{
    LockPoolMapIt gIt = _lockPoolMapM.find(lockPoolP->_szName);
    
    if(gIt != _lockPoolMapM.end())
    {
        _lockPoolMapM.erase(gIt);
    }

    if(_destroyLockPoolF != NULL)
    {
        _destroyLockPoolF(lockPoolP);
    }
    else
    {
        delete lockPoolP;
    }
        
}

Bool ThreadManager::init(void)
{
    Bool returnValue = true;

    SINFO << "ThreadManager init" << endl;

#ifdef OSG_ASPECT_USE_PTHREADKEY
    int rc; 

    rc = pthread_key_create(&(Thread::_aspectKey), 
                            Thread::freeAspect);

    rc = pthread_key_create(&(Thread::_threadKey), 
                            Thread::freeThreadP);

    rc = pthread_key_create(&(Thread::_changeListKey), 
                            Thread::freeChangeListP);
#endif

#ifdef OSG_ASPECT_USE_PTHREADSELF
#ifdef OSG_RUNTIME_NUM_ASPECTS
    Thread::_aspectsA     = new UInt16      [_numAspects];
    Thread::_threadsA     = new Thread     *[_numAspects];
    Thread::_changelistsA = new ChangeList *[_numAspects];
#endif

   for(UInt32 i = 0; i < _numAspects; i++)
    {
        Thread::_aspectsA[i]     = 0;
        Thread::_threadsA[i]     = NULL;
        Thread::_changelistsA[i] = NULL;
    }
#endif

#if defined (OSG_ASPECT_USE_LOCALSTORAGE)		
	Thread::_aspectKey     = TlsAlloc();
	Thread::_threadKey     = TlsAlloc();
	Thread::_changeListKey = TlsAlloc();

	if (Thread::_aspectKey == 0xFFFFFFFF) 
		fprintf(stderr, "Local alloc failed\n");

	if (Thread::_threadKey == 0xFFFFFFFF) 
		fprintf(stderr, "Local alloc failed\n");

	if (Thread::_changeListKey == 0xFFFFFFFF) 
		fprintf(stderr, "Local alloc failed\n");
#endif

#if defined(OSG_USE_SPROC)
    usconfig(CONF_AUTOGROW,   1);
    usconfig(CONF_INITUSERS, 20);
    usconfig(CONF_INITSIZE, 10 * 1048576);
    usconfig(CONF_CHMOD, 0666);

    _arenaP = usinit("/dev/zero");

    if(_arenaP == NULL)
    {
        SFATAL << "TM : could not initialize arena " << errno << endl;
        returnValue = false;
    }
    else
    {
        SINFO << "TM : got arena " << _arenaP << endl;
    }
#endif

    _tableLockP = _createLockF("TMTableLock");
    
    if(_tableLockP == NULL)
    {
        SFATAL << "TM : could not get table lock" << endl;

        returnValue = false;
    }
    else
    {
        SINFO << "TM : got table lock " << _tableLockP << endl;
    }

    Thread *pApp = getThread("App");
    Thread::init(pApp);

    if(pApp == NULL)
    {
        SFATAL << "TM : could not get application thread " << endl;

        returnValue = false;
    }
    else
    {
        SINFO << "TM : got application thread " << pApp << endl;
    }

    return returnValue;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void ThreadManager::shutdown(void)
{
    _tableLockP->aquire();

    ThreadMapIt   gTIt  = _threadMapM.begin();
    LockMapIt     gLIt  = _lockMapM.begin();
    LockPoolMapIt gLPIt = _lockPoolMapM.begin();
    BarrierMapIt  gBIt  = _barrierMapM.begin();

    while(gTIt != _threadMapM.end())
    {
        if(_destroyThreadF != NULL)
        {
            _destroyThreadF((*gTIt).second);
        }
        else
        {
            delete    (*gTIt).second;
        }

        gTIt++;
    }

    _threadMapM.clear();

    while(gLIt != _lockMapM.end())
    {
        if(_destroyLockF != NULL)
        {
            _destroyLockF((*gLIt).second);
        }
        else
        {
            delete    (*gLIt).second;
        }
        
        gLIt++;
    }
    
    _lockMapM.clear();

    while(gLPIt != _lockPoolMapM.end())
    {
        if(_destroyLockPoolF != NULL)
        {
            _destroyLockPoolF((*gLPIt).second);
        }
        else
        {
            delete    (*gLPIt).second;
        }
        
        gLPIt++;
    }
    
    _lockPoolMapM.clear();

    while(gBIt != _barrierMapM.end())
    {
        if(_destroyBarrierF != NULL)
        {
            _destroyBarrierF((*gBIt).second);
        }
        else
        {
            delete    (*gBIt).second;
        }
        
        gBIt++;
    }

    _barrierMapM.clear();

    _tableLockP->release();

    if(_destroyLockF != NULL)
    {
        _destroyLockF(_tableLockP);
    }
    else
    {
        delete _tableLockP;
    }

#if defined (OSG_ASPECT_USE_LOCALSTORAGE)		
    Thread::freeAspect();
    Thread::freeThreadP();
    Thread::freeChangeListP();
#endif
}

ThreadManager::ThreadManager(void) :
    _createThreadF   ((CreateThreadF)   Thread::create),
    _createBarrierF  ((CreateBarrierF)  Barrier::create),
    _createLockF     ((CreateLockF)     Lock::create),
    _createLockPoolF ((CreateLockPoolF) LockPool::create),

    _destroyThreadF  ((DestroyThreadF)   Thread::destroy),
    _destroyBarrierF ((DestroyBarrierF)  Barrier::destroy),
    _destroyLockF    ((DestroyLockF)     Lock::destroy),
    _destroyLockPoolF((DestroyLockPoolF) LockPool::destroy),

    _threadMapM    (),

    _lockMapM      (),

    _lockPoolMapM  (),

    _barrierMapM   (),

    _tableLockP    (NULL)
{
#if defined(_OSG_USE_SPROC_)
    _arenaP = NULL;
#endif
}

ThreadManager::~ThreadManager(void)
{
}


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

