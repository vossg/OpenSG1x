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
#endif

#include "OSGLock.h"

#include "OSGBaseFunctions.h"

#if defined (OSG_USE_SPROC)
#include <OSGThreadManager.h>
#endif

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSGUInt32 OSGLockCommonBase::_lockCount = 0;

char OSGLockCommonBase::cvsid[] = "@(#)$Id: $";

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

OSGLockCommonBase::OSGLockCommonBase(void) :
    _szName(NULL),
    _lockId(_lockCount++),
    _refCount(0)
{
}

OSGLockCommonBase::OSGLockCommonBase(const OSGChar8 *szName):
    _szName(NULL),
    _lockId(_lockCount++),
    _refCount(0)
{
    if(szName != NULL)
    {
        stringDup(szName, _szName);
    }
    else
    {
        _szName = new OSGChar8[16];
        sprintf(_szName, "OSGLock_%d", _lockId);
    }
}

/** \brief Destructor
 */

OSGLockCommonBase::~OSGLockCommonBase(void)
{
    delete [] _szName;
}

void OSGLockCommonBase::addRef(void)
{
    _refCount++;
}

void OSGLockCommonBase::subRef(void)
{
    _refCount--;
}

OSGBool OSGLockCommonBase::inUse(void)
{
    return _refCount <= 0;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



#if defined (OSG_USE_PTHREADS)

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGPThreadLockBase::cvsid[] = "@(#)$Id: $";

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

OSGPThreadLockBase *OSGPThreadLockBase::create(const OSGChar8 *szName)
{
    OSGPThreadLockBase *returnValue = NULL;

    returnValue = new OSGPThreadLockBase(szName);

    if(returnValue->init() == false)
    {
        delete returnValue;
        returnValue = NULL;
    }
    
    return returnValue;
}

void OSGPThreadLockBase::destroy(OSGPThreadLockBase *lockP)
{
    if(lockP != NULL)
    {
        lockP->shutdown();
        delete lockP;
    }
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

void OSGPThreadLockBase::aquire(void)
{
    pthread_mutex_lock  (&(_lowLevelLock));         
}

void OSGPThreadLockBase::release(void)
{
    pthread_mutex_unlock(&(_lowLevelLock));               
}

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

OSGPThreadLockBase::OSGPThreadLockBase(void):
    Inherited(),
    _lowLevelLock()
{
}

OSGPThreadLockBase::OSGPThreadLockBase(const OSGChar8 *szName) :
    Inherited(szName),
    _lowLevelLock()
{
}

OSGPThreadLockBase::~OSGPThreadLockBase(void)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

OSGBool OSGPThreadLockBase::init(void)
{
    pthread_mutex_init(&(_lowLevelLock), NULL);

    return true;
}

void OSGPThreadLockBase::shutdown(void)
{
    pthread_mutex_destroy(&(_lowLevelLock));
}

#endif /* OSG_USE_PTHREADS */




#if defined (OSG_USE_SPROC)

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGSprocLockBase::cvsid[] = "@(#)$Id: $";

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

OSGSprocLockBase *OSGSprocLockBase::create(const OSGChar8 *szName)
{
    OSGSprocLockBase *returnValue = NULL;

    returnValue = new OSGSprocLockBase(szName);

    if(returnValue->init() == false)
    {
        delete returnValue;
        returnValue = NULL;
    }
    
    return returnValue;
}

void OSGSprocLockBase::destroy(OSGSprocLockBase *lockP)
{
    if(lockP != NULL)
    {
        lockP->shutdown();

        delete lockP;
    }
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

void OSGSprocLockBase::aquire(void)
{
    if(_lowLevelLock != NULL)
        ussetlock(_lowLevelLock);
}

void OSGSprocLockBase::release(void)
{
    if(_lowLevelLock != NULL)
        usunsetlock(_lowLevelLock);
}

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

OSGSprocLockBase::OSGSprocLockBase(void):
    Inherited(),
    _lowLevelLock(NULL)
{
}

OSGSprocLockBase::OSGSprocLockBase(const OSGChar8 *szName):
    Inherited(szName),
    _lowLevelLock(NULL)
{
}

OSGSprocLockBase::~OSGSprocLockBase(void)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

OSGBool OSGSprocLockBase::init(void)
{
    OSGThreadManager *pThreadManager = OSGThreadManager::the();

    if(pThreadManager == NULL)
        return false;

    if(pThreadManager->getArena() == NULL)
        return false;

    _lowLevelLock = usnewlock(pThreadManager->getArena());

    if(_lowLevelLock == NULL)
        return false;

    usinitlock(_lowLevelLock);

    return true;
}

void OSGSprocLockBase::shutdown(void)
{
    OSGThreadManager *pThreadManager = OSGThreadManager::the();

    if(pThreadManager == NULL)
        return;

    if(pThreadManager->getArena() == NULL)
        return;

    if(_lowLevelLock != NULL)
    {
        usfreelock(_lowLevelLock, pThreadManager->getArena());

        _lowLevelLock = NULL;
    }
}

#endif /* OSG_USE_SPROC */




#if defined (OSG_USE_WINTHREADS)

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGWinThreadLockBase::cvsid[] = "@(#)$Id: $";

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

OSGWinThreadLockBase *OSGWinThreadLockBase::create(const OSGChar8  *szName)
{
    OSGWinThreadLockBase *returnValue = NULL;

    returnValue = new OSGWinThreadLockBase(szName);

    if(returnValue->init() == false)
    {
        delete returnValue;
        returnValue = NULL;
    }
    
    return returnValue;
}

void OSGWinThreadLockBase::destroy(OSGWinThreadLockBase *lockP)
{
    if(lockP != NULL)
    {
        lockP->shutdown();
        delete lockP();
    }
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

void OSGWinThreadLockBase::aquire(void)
{
    WaitForSingleObject(_mutex, INFINITE);
}

void OSGWinThreadLockBase::release(void)
{
	ReleaseMutex(_mutex);
}

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

OSGWinThreadLockBase::OOSGWinThreadLockBase(void) :
    Inherited(),
	_mutex(NULL)
{
}

OSGWinThreadLockBase::OSGWinThreadLockBase(const OSGChar8 *szName) :
    Inherited(szName),
	_mutex(NULL)
{
}

OSGWinThreadLockBase::~OSGWinThreadLockBase(void)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

OSGBool OSGWinThreadLockBase::init(void)
{    
	_mutex = CreateMutex(NULL,      // no security attributes
						 FALSE,     // initially not owned
						 _szName);  // name of mutex
	
	if(_mutex == NULL) 
	{
		return false;
    }

    return true;
}

void OSGWinThreadBase::shutdown(void)
{
    if(_mutex != NULL)
    {
        closeHandle(_mutex);
    }
}

#endif /* OSG_USE_WINTHREADS */




/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGLockPool::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

OSGLockPool *OSGLockPool::create(const OSGChar8 *szName)
{
    OSGLockPool *returnValue = NULL;

    returnValue = new OSGLockPool(szName);

    if(returnValue->init() == false)
    {
        delete returnValue;
        returnValue = NULL;
    }
    
    return returnValue;
}

void OSGLockPool::destroy(OSGLockPool *lockP)
{
    if(lockP != NULL)
    {
        lockP->shutdown();

        delete lockP;
    }
}

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

void OSGLockPool::aquire(void *keyP)
{
    fprintf(stderr, "A Key : %04x, Lock %04x\n", 
            keyP, (((OSGUInt32) keyP) & uiLockPoolMask) >> 7);

    _locksA[(((OSGUInt32) keyP) & uiLockPoolMask) >> 7].aquire();
}
void OSGLockPool::release(void *keyP)
{
    fprintf(stderr, "R Key : %04x, Lock %04x\n", keyP, 
            (((OSGUInt32) keyP) & uiLockPoolMask) >> 7);

    _locksA[(((OSGUInt32) keyP) & uiLockPoolMask) >> 7].release();
}

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/** \brief Constructor
 */

OSGLockPool::OSGLockPool(const OSGChar8 *szName) :
    Inherited(szName)
{
}

/** \brief Destructor
 */

OSGLockPool::~OSGLockPool(void)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

OSGBool OSGLockPool::init(void)
{
    OSGBool   returnValue = true;
    OSGChar8 *pTmp;

    pTmp = new OSGChar8[strlen(_szName) + 6];

    for(OSGUInt32 i = 0; i < uiLockPoolSize; i++)
    {
#ifdef OSG_DEBUG_LOCK_STAT
        _lockStatA[i] = 0;
#endif
        sprintf(pTmp, "%s%d\n", _szName, i);

        stringDup(pTmp, _locksA[i]._szName);

        returnValue &= _locksA[i].init();
    }

    delete [] pTmp;
        
    return returnValue;
}

void OSGLockPool::shutdown(void)
{
    for(OSGUInt32 i = 0; i < uiLockPoolSize; i++)
    {
        _locksA[i].shutdown();
    }
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

