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


OSGThreadManager::~OSGThreadManager(void)
{
    OSGThreadMapIt gTIt  = _threadMapM.begin();
    OSGLockMapIt   gLIt  = _lockMapM.begin();
    OSGBarrierMapIt gBIt = _barrierMapM.begin();

    while(gTIt != _threadMapM.end())
    {
		// must cast it because of the MS compiler
        delete [] (char *) (*gTIt).first;
        delete    (*gTIt).second;

        gTIt++;
    }

    _threadMapM.clear();

    while(gLIt != _lockMapM.end())
    {
        delete [] (char *) (*gLIt).first;
        delete    (*gLIt).second;
        
        gLIt++;
    }
    
    _lockMapM.clear();

    while(gBIt != _barrierMapM.end())
    {
        delete [] (char *) (*gBIt).first;
        delete    (*gBIt).second;
        
        gBIt++;
    }

    _barrierMapM.clear();

    _threadStoreV.clear();
    _lockStoreV.clear();
    _barrierStoreV.clear();
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

OSGThread *OSGThreadManager::createThread(const char *szName)
{
    OSGThread *returnValue = NULL;

    if(_createThreadF != NULL)
    {
        if(szName == NULL)
        {
            char *szTmpName = new char[11];
            
            sprintf(szTmpName, "Thread%d", _threadStoreV.size());
            
            OSGThreadMapIt gIt = _threadMapM.find(szTmpName);
        
            if(gIt == _threadMapM.end())
            {
                returnValue = _createThreadF(szTmpName, _threadStoreV.size());
                
                _threadStoreV.push_back (returnValue);
                _threadMapM[szTmpName] = returnValue;
            }
            else
                (*gIt).second->print();
        }
        else
        {
            OSGThreadMapIt gIt = _threadMapM.find(szName);
        
            if(gIt == _threadMapM.end())
            {
                char *szTmpName = NULL;

                stringDup(szName, szTmpName);

                returnValue = _createThreadF(szName, _threadStoreV.size());
                
                _threadStoreV.push_back (returnValue);
                _threadMapM[szTmpName] = returnValue;
            }
        }
    }

    return returnValue;
}

OSGBarrier *OSGThreadManager::createBarrier(const char *szName)
{
    OSGBarrier *returnValue = NULL;

    if(_createBarrierF != NULL)
    {
        if(szName == NULL)
        {
            char *szTmpName = new char[11];
            
            sprintf(szTmpName, "Barrier%d", _barrierStoreV.size());
            
            OSGBarrierMapIt gIt = _barrierMapM.find(szTmpName);
        
            if(gIt == _barrierMapM.end())
            {
                returnValue = _createBarrierF(szTmpName, 
                                              _barrierStoreV.size());
                
                _barrierStoreV.push_back (returnValue);
                _barrierMapM[szTmpName] = returnValue;
            }
        }
        else
        {
            OSGBarrierMapIt gIt = _barrierMapM.find(szName);
        
            if(gIt == _barrierMapM.end())
            {
                char *szTmpName = NULL;

                stringDup(szName, szTmpName);

                returnValue = _createBarrierF(szName, _barrierStoreV.size());
                
                _barrierStoreV.push_back (returnValue);
                _barrierMapM[szTmpName] = returnValue;
            }
        }
    }

    return returnValue;
}

OSGLock *OSGThreadManager::createLock(const char *szName)
{
    OSGLock *returnValue = NULL;

    if(_createLockF != NULL)
    {
        if(szName == NULL)
        {
            char *szTmpName = new char[11];
            
            sprintf(szTmpName, "Lock%d", _lockStoreV.size());
            
            OSGLockMapIt gIt = _lockMapM.find(szTmpName);
        
            if(gIt == _lockMapM.end())
            {
                returnValue = _createLockF(szTmpName, _lockStoreV.size());
                
                _lockStoreV.push_back (returnValue);
                _lockMapM[szTmpName] = returnValue;
            }
        }
        else
        {
            OSGLockMapIt gIt = _lockMapM.find(szName);
        
            if(gIt == _lockMapM.end())
            {
                char *szTmpName = NULL;

                stringDup(szName, szTmpName);

                returnValue = _createLockF(szName, _lockStoreV.size());
                
                _lockStoreV.push_back (returnValue);
                _lockMapM[szTmpName] = returnValue;
            }
        }
    }

    return returnValue;
}

void OSGThreadManager::destroyBarrier(OSGBarrier *barrierP)
{
    if(barrierP != NULL)
    {
        OSGBarrierMapIt gIt = _barrierMapM.find(barrierP->_szName);

        if(gIt != _barrierMapM.end())
        {
            delete [] (char *) (*gIt).first;
            delete    (*gIt).second;

            _barrierMapM.erase(gIt);
        }
    }
}

void OSGThreadManager::destroyLock(OSGLock *lockP)
{
    if(lockP != NULL)
    {
        OSGLockMapIt gIt = _lockMapM.find(lockP->_szName);

        if(gIt != _lockMapM.end())
        {
            delete [] (char *) (*gIt).first;
            delete    (*gIt).second;

            _lockMapM.erase(gIt);
        }
    }
}

OSGThread  *OSGThreadManager::findThread (const char *szName)
{
    OSGThread *returnValue = NULL;

    if(szName != NULL)
    {
        OSGThreadMapIt gIt;
    
        gIt = _threadMapM.find(szName);

        if(gIt != _threadMapM.end())
            returnValue = (*gIt).second;
    }

    return returnValue;
}

OSGBarrier *OSGThreadManager::findBarrier(const char *szName)
{
    OSGBarrier *returnValue = NULL;

    if(szName != NULL)
    {
        OSGBarrierMapIt gIt;
    
        gIt = _barrierMapM.find(szName);

        if(gIt != _barrierMapM.end())
            returnValue = (*gIt).second;
    }

    return returnValue;
}

OSGLock *OSGThreadManager::findLock   (const char *szName)
{
    OSGLock *returnValue = NULL;

    if(szName != NULL)
    {
        OSGLockMapIt gIt;
    
        gIt = _lockMapM.find(szName);

        if(gIt != _lockMapM.end())
            returnValue = (*gIt).second;
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

bool OSGThreadManager::init(void)
{
    SDEBUG << "init" << endl;

#ifdef OSG_ASPECT_USE_PTHREADKEY
    int rc; 

    rc = pthread_key_create(&(OSGThread::_aspectKey), 
                            OSGThread::freeAspect);

    rc = pthread_key_create(&(OSGThread::_threadKey), 
                            OSGThread::freeThreadP);

    rc = pthread_key_create(&(OSGThread::_changelistKey), 
                            OSGThread::freeChangelistP);
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
	OSGThread::_changelistKey = TlsAlloc();

	if (OSGThread::_aspectKey == 0xFFFFFFFF) 
		fprintf(stderr, "Local alloc failed\n");

	if (OSGThread::_threadKey == 0xFFFFFFFF) 
		fprintf(stderr, "Local alloc failed\n");

	if (OSGThread::_changelistKey == 0xFFFFFFFF) 
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
        SFATAL << "Could not initialize arena " << errno << endl;
    }

    SDEBUG << "Got arena " << _arenaP << endl;
#endif

    OSGThread *pApp = createThread("OSGApp");

    OSGThread::init(pApp);

    return true;
}

OSGThreadManager::OSGThreadManager(void) :
    _createThreadF ((OSGCreateThreadF)  OSGThread::create),
    _createBarrierF((OSGCreateBarrierF) OSGBarrier::create),
    _createLockF   ((OSGCreateLockF)    OSGLock::create),
    _threadStoreV(),
    _threadMapM(),
    _lockStoreV(),
    _lockMapM(),
    _barrierStoreV(),
    _barrierMapM()
{
#if defined(_OSG_USE_SPROC_)
    _arenaP = NULL;
#endif
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

