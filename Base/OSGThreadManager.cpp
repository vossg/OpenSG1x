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
#include <OSGLog.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/



/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGThreadManager::cvsid[] = "@(#)$Id: $";

OSGThreadManager OSGThreadManager::_threadManagerP;

OSGUInt32        OSGThreadManager::_numAspects   = OSG_NUM_ASPECTS;

#ifdef OSG_RUNTIME_NUM_ASPECTS 
OSGBool          OSGThreadManager::_numAspectSet = false;
#endif

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

void OSGThreadManager::setThreadCreateFunc(OSGCreateThreadF create)
{
    _createThreadF = create; 
}

void OSGThreadManager::setBarrierCreateFunc(OSGCreateBarrierF create)
{
    _createBarrierF = create;
}

void OSGThreadManager::setLockCreateFunc(OSGCreateLockF create)
{
    _createLockF = create;
}

void OSGThreadManager::setLockPoolCreateFunc(OSGCreateLockPoolF create)
{
    _createLockPoolF = create;
}

void OSGThreadManager::setThreadDestroyFunc(OSGDestroyThreadF destroy)
{
    _destroyThreadF = destroy;
}

void OSGThreadManager::setBarrierDestroyFunc(OSGDestroyBarrierF destroy)
{
    _destroyBarrierF = destroy;
}

void OSGThreadManager::setLockDestroyFunc(OSGDestroyLockF destroy)
{
    _destroyLockF = destroy;
}

void OSGThreadManager::setLockPoolDestroyFunc(OSGDestroyLockPoolF destroy)
{
    _destroyLockPoolF = destroy;
}

OSGThreadManager *OSGThreadManager::the(void)
{
    return &_threadManagerP;
}

void OSGThreadManager::setNumAspects(OSGUInt32 numAspects)
{
#if defined(OSG_RUNTIME_NUM_ASPECTS)    
    if(_numAspectSet == false && numAspects > 1)
    {
#if defined(OSG_ASPECT_USE_PTHREADSELF) || \
    defined(OSG_ASPECT_USE_CUSTOMSELF)
        OSGUInt32  i;
        OSGUInt16 *aspectA = new OSGUInt16[numAspects];

        for(i = 0; i < _numAspects; i++)
            aspectA[i] = OSGThread::_aspectsA[i];

        for(i = _numAspects; i < numAspects; i++)
            OSGThread::_aspectsA[i] = 0;

        delete [] OSGThread::_aspectsA;

        OSGThread::_aspectsA = aspectA;
#endif
        _numAspects   = numAspects;
        _numAspectSet = true;        
    }    
#endif
}

OSGUInt32 OSGThreadManager::getNumAspects(void)
{
    return _numAspects;
}

OSGChangeList *OSGThreadManager::getChangeList(OSGUInt32 aspectId)
{
    OSGChangeList *returnValue = NULL;

    if(aspectId < _numAspects)
    {
    }
    
    return returnValue;
}

#if defined(OSG_USE_SPROC)
usptr_t *OSGThreadManager::getArena(void)
{
    return _arenaP;
}
#endif

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

OSGThread *OSGThreadManager::getThread(const OSGChar8 *szName)
{
    OSGThread *returnValue = NULL;

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

            OSGThreadMapIt gIt = _threadMapM.find(szName);
        
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

    return returnValue;
}

OSGBarrier *OSGThreadManager::getBarrier(const OSGChar8 *szName)
{
    OSGBarrier *returnValue = NULL;

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

            OSGBarrierMapIt gIt = _barrierMapM.find(szName);
        
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

OSGLock *OSGThreadManager::getLock(const OSGChar8 *szName)
{
    OSGLock *returnValue = NULL;

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

            OSGLockMapIt gIt = _lockMapM.find(szName);           
        
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

OSGLockPool *OSGThreadManager::getLockPool(const OSGChar8 *szName)
{
    OSGLockPool *returnValue = NULL;

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

            OSGLockPoolMapIt gIt = _lockPoolMapM.find(szName);
        
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

void OSGThreadManager::freeBarrier(OSGBarrier *barrierP)
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

void OSGThreadManager::freeLock(OSGLock *lockP)
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

void OSGThreadManager::freeLockPool(OSGLockPool *lockPoolP)
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

OSGThread  *OSGThreadManager::findThread (const char *szName)
{
    OSGThread *returnValue = NULL;

    if(szName != NULL)
    {
        OSGThreadMapIt gIt;

        _tableLockP->aquire();
    
        gIt = _threadMapM.find(szName);

        if(gIt != _threadMapM.end())
            returnValue = (*gIt).second;

        _tableLockP->release();
    }

    return returnValue;
}

OSGBarrier *OSGThreadManager::findBarrier(const char *szName)
{
    OSGBarrier *returnValue = NULL;

    if(szName != NULL)
    {
        OSGBarrierMapIt gIt;

        _tableLockP->aquire();
    
        gIt = _barrierMapM.find(szName);

        if(gIt != _barrierMapM.end())
            returnValue = (*gIt).second;

        _tableLockP->release();
    }

    return returnValue;
}

OSGLock *OSGThreadManager::findLock(const char *szName)
{
    OSGLock *returnValue = NULL;

    if(szName != NULL)
    {
        OSGLockMapIt gIt;

        _tableLockP->aquire();

        gIt = _lockMapM.find(szName);

        if(gIt != _lockMapM.end())
            returnValue = (*gIt).second;

        _tableLockP->release();
    }

    return returnValue;
}

OSGLockPool *OSGThreadManager::findLockPool(const char *szName)
{
    OSGLockPool *returnValue = NULL;

    if(szName != NULL)
    {
        OSGLockPoolMapIt gIt;

        _tableLockP->aquire();
    
        gIt = _lockPoolMapM.find(szName);

        if(gIt != _lockPoolMapM.end())
            returnValue = (*gIt).second;

        _tableLockP->release();
    }

    return returnValue;
}

/*-------------------------- assignment -----------------------------------*/


/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void OSGThreadManager::removeBarrier(OSGBarrier *barrierP)
{
    OSGBarrierMapIt gIt = _barrierMapM.find(barrierP->_szName);

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

void OSGThreadManager::removeLock(OSGLock *lockP)
{
    OSGLockMapIt gIt = _lockMapM.find(lockP->_szName);
    
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

void OSGThreadManager::removeLockPool(OSGLockPool *lockPoolP)
{
    OSGLockPoolMapIt gIt = _lockPoolMapM.find(lockPoolP->_szName);
    
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

OSGBool OSGThreadManager::init(void)
{
    OSGBool returnValue = true;

    SINFO << "ThreadManager init" << endl;

#ifdef OSG_ASPECT_USE_PTHREADKEY
    int rc; 

    rc = pthread_key_create(&(OSGThread::_aspectKey), 
                            OSGThread::freeAspect);

    rc = pthread_key_create(&(OSGThread::_threadKey), 
                            OSGThread::freeThreadP);

    rc = pthread_key_create(&(OSGThread::_changeListKey), 
                            OSGThread::freeChangeListP);
#endif

#ifdef OSG_ASPECT_USE_PTHREADSELF
#ifdef OSG_RUNTIME_NUM_ASPECTS
    OSGThread::_aspectsA     = new OSGUInt16      [_numAspects];
    OSGThread::_threadsA     = new OSGThread     *[_numAspects];
    OSGThread::_changelistsA = new OSGChangeList *[_numAspects];
#endif

   for(OSGUInt32 i = 0; i < _numAspects; i++)
    {
        OSGThread::_aspectsA[i]     = 0;
        OSGThread::_threadsA[i]     = NULL;
        OSGThread::_changelistsA[i] = NULL;
    }
#endif

#if defined (OSG_ASPECT_USE_LOCALSTORAGE)		
	OSGThread::_aspectKey     = TlsAlloc();
	OSGThread::_threadKey     = TlsAlloc();
	OSGThread::_changeListKey = TlsAlloc();

	if (OSGThread::_aspectKey == 0xFFFFFFFF) 
		fprintf(stderr, "Local alloc failed\n");

	if (OSGThread::_threadKey == 0xFFFFFFFF) 
		fprintf(stderr, "Local alloc failed\n");

	if (OSGThread::_changeListKey == 0xFFFFFFFF) 
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
        SFATAL << "OSGTM : could not initialize arena " << errno << endl;
        returnValue = false;
    }
    else
    {
        SINFO << "OSGTM : got arena " << _arenaP << endl;
    }
#endif

    _tableLockP = _createLockF("OSGTMTableLock");
    
    if(_tableLockP == NULL)
    {
        SFATAL << "OSGTM : could not get table lock" << endl;

        returnValue = false;
    }
    else
    {
        SINFO << "OSGTM : got table lock " << _tableLockP << endl;
    }

    OSGThread *pApp = getThread("OSGApp");
    OSGThread::init(pApp);

    if(pApp == NULL)
    {
        SFATAL << "OSGTM : could not get application thread " << endl;

        returnValue = false;
    }
    else
    {
        SINFO << "OSGTM : got application thread " << pApp << endl;
    }

    return returnValue;
}

void OSGThreadManager::shutdown(void)
{
    _tableLockP->aquire();

    OSGThreadMapIt   gTIt  = _threadMapM.begin();
    OSGLockMapIt     gLIt  = _lockMapM.begin();
    OSGLockPoolMapIt gLPIt = _lockPoolMapM.begin();
    OSGBarrierMapIt  gBIt  = _barrierMapM.begin();

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
    OSGThread::freeAspect();
    OSGThread::freeThreadP();
    OSGThread::freeChangeListP();
#endif
}

OSGThreadManager::OSGThreadManager(void) :
    _createThreadF   ((OSGCreateThreadF)   OSGThread::create),
    _createBarrierF  ((OSGCreateBarrierF)  OSGBarrier::create),
    _createLockF     ((OSGCreateLockF)     OSGLock::create),
    _createLockPoolF ((OSGCreateLockPoolF) OSGLockPool::create),

    _destroyThreadF  ((OSGDestroyThreadF)   OSGThread::destroy),
    _destroyBarrierF ((OSGDestroyBarrierF)  OSGBarrier::destroy),
    _destroyLockF    ((OSGDestroyLockF)     OSGLock::destroy),
    _destroyLockPoolF((OSGDestroyLockPoolF) OSGLockPool::destroy),

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

OSGThreadManager::~OSGThreadManager(void)
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

