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
#endif

#define OSG_COMPILEBASE

#include "OSGLock.h"

#include "OSGBaseFunctions.h"

#if defined (OSG_USE_SPROC)
#include <OSGThreadManager.h>
#endif

#include <errno.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

UInt32 LockCommonBase::_lockCount = 0;

char LockCommonBase::cvsid[] = "@(#)$Id: $";

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

LockCommonBase::LockCommonBase(void) :
    _szName(NULL),
    _lockId(_lockCount++),
    _refCount(0)
{
}

LockCommonBase::LockCommonBase(const Char8 *szName):
    _szName(NULL),
    _lockId(_lockCount++),
    _refCount(0)
{
    if(szName != NULL)
    {
        osgstringDup(szName, _szName);
    }
    else
    {
        _szName = new Char8[16];
        sprintf(_szName, "Lock_%d", _lockId);
    }
}

/** \brief Destructor
 */

LockCommonBase::~LockCommonBase(void)
{
    delete [] _szName;
}

void LockCommonBase::addRef(void)
{
    _refCount++;
}

void LockCommonBase::subRef(void)
{
    _refCount--;
}

Bool LockCommonBase::inUse(void)
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

char PThreadLockBase::cvsid[] = "@(#)$Id: $";

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

PThreadLockBase *PThreadLockBase::create(const Char8 *szName)
{
    PThreadLockBase *returnValue = NULL;

    returnValue = new PThreadLockBase(szName);

    if(returnValue->init() == false)
    {
        delete returnValue;
        returnValue = NULL;
    }
    
    return returnValue;
}

void PThreadLockBase::destroy(PThreadLockBase *lockP)
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

void PThreadLockBase::aquire(void)
{
    pthread_mutex_lock  (&(_lowLevelLock));         
}

void PThreadLockBase::release(void)
{
    pthread_mutex_unlock(&(_lowLevelLock));               
}

Bool PThreadLockBase::request(void)
{
    return (pthread_mutex_trylock(&(_lowLevelLock)) != EBUSY); 
}

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

PThreadLockBase::PThreadLockBase(void):
    Inherited(),
    _lowLevelLock()
{
}

PThreadLockBase::PThreadLockBase(const Char8 *szName) :
    Inherited(szName),
    _lowLevelLock()
{
}

PThreadLockBase::~PThreadLockBase(void)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

Bool PThreadLockBase::init(void)
{
    pthread_mutex_init(&(_lowLevelLock), NULL);

    return true;
}

void PThreadLockBase::shutdown(void)
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

char SprocLockBase::cvsid[] = "@(#)$Id: $";

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

SprocLockBase *SprocLockBase::create(const Char8 *szName)
{
    SprocLockBase *returnValue = NULL;

    returnValue = new SprocLockBase(szName);

    if(returnValue->init() == false)
    {
        delete returnValue;
        returnValue = NULL;
    }
    
    return returnValue;
}

void SprocLockBase::destroy(SprocLockBase *lockP)
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

void SprocLockBase::aquire(void)
{
    if(_lowLevelLock != NULL)
        ussetlock(_lowLevelLock);
}

void SprocLockBase::release(void)
{
    if(_lowLevelLock != NULL)
        usunsetlock(_lowLevelLock);
}

Bool SprocLockBase::request(void)
{
    Bool  returnValue = false;
    Int32 rc          = 0;

    if(_lowLevelLock != NULL)
        rc = uscsetlock(_lowLevelLock, 0);

    returnValue = (rc == 1);

    return returnValue;
}

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

SprocLockBase::SprocLockBase(void):
    Inherited(),
    _lowLevelLock(NULL)
{
}

SprocLockBase::SprocLockBase(const Char8 *szName):
    Inherited(szName),
    _lowLevelLock(NULL)
{
}

SprocLockBase::~SprocLockBase(void)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

Bool SprocLockBase::init(void)
{
    ThreadManager *pThreadManager = ThreadManager::the();

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

void SprocLockBase::shutdown(void)
{
    ThreadManager *pThreadManager = ThreadManager::the();

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

char WinThreadLockBase::cvsid[] = "@(#)$Id: $";

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

WinThreadLockBase *WinThreadLockBase::create(const Char8  *szName)
{
    WinThreadLockBase *returnValue = NULL;

    returnValue = new WinThreadLockBase(szName);

    if(returnValue->init() == false)
    {
        delete returnValue;
        returnValue = NULL;
    }
    
    return returnValue;
}

void WinThreadLockBase::destroy(WinThreadLockBase *lockP)
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

void WinThreadLockBase::aquire(void)
{
    WaitForSingleObject(_mutex, INFINITE);
}

void WinThreadLockBase::release(void)
{
	ReleaseMutex(_mutex);
}

Bool WinThreadLockBase::request(void)
{
    DWORD rc = WaitForSingleObject(_mutex, 0);

    if(rc == WAIT_OBJECT_0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

WinThreadLockBase::WinThreadLockBase(void) :
    Inherited(),
	_mutex(NULL)
{
}

WinThreadLockBase::WinThreadLockBase(const Char8 *szName) :
    Inherited(szName),
	_mutex(NULL)
{
}

WinThreadLockBase::~WinThreadLockBase(void)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

Bool WinThreadLockBase::init(void)
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

void WinThreadLockBase::shutdown(void)
{
    if(_mutex != NULL)
    {
        CloseHandle(_mutex);
    }
}

#endif /* OSG_USE_WINTHREADS */




/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char LockPool::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

LockPool *LockPool::create(const Char8 *szName)
{
    LockPool *returnValue = NULL;

    returnValue = new LockPool(szName);

    if(returnValue->init() == false)
    {
        delete returnValue;
        returnValue = NULL;
    }
    
    return returnValue;
}

void LockPool::destroy(LockPool *lockP)
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

void LockPool::aquire(void *keyP)
{
    _locksA[(((UInt32) keyP) & uiLockPoolMask) >> uiLockPoolShift].aquire();
}
void LockPool::release(void *keyP)
{
    _locksA[(((UInt32) keyP) & uiLockPoolMask) >> uiLockPoolShift].release();
}

Bool LockPool::request(void *keyP)
{
    return _locksA[(((UInt32) keyP) & uiLockPoolMask) >> uiLockPoolShift].request();
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

LockPool::LockPool(const Char8 *szName) :
    Inherited(szName)
{
}

/** \brief Destructor
 */

LockPool::~LockPool(void)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

Bool LockPool::init(void)
{
    Bool   returnValue = true;
    Char8 *pTmp;

    pTmp = new Char8[strlen(_szName) + 6];

    for(UInt32 i = 0; i < uiLockPoolSize; i++)
    {
#ifdef OSG_DEBUG_LOCK_STAT
        _lockStatA[i] = 0;
#endif
        sprintf(pTmp, "%s%d\n", _szName, i);

        osgstringDup(pTmp, _locksA[i]._szName);

        returnValue &= _locksA[i].init();
    }

    delete [] pTmp;
        
    return returnValue;
}

void LockPool::shutdown(void)
{
    for(UInt32 i = 0; i < uiLockPoolSize; i++)
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

