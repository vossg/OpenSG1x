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

#include "OSGBarrier.h"
#include "OSGBaseFunctions.h"

#if defined(OSG_USE_SPROC)
#include <OSGThreadManager.h>
#endif

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

UInt32 BarrierCommonBase::_barrierCount = 0;

char BarrierCommonBase::cvsid[] = "@(#)$Id: $";

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

BarrierCommonBase::BarrierCommonBase(const Char8 *szName):
    _szName(NULL),
    _barrierId(_barrierCount++),
    _refCount(0)
{
    if(szName != NULL)
    {
        osgstringDup(szName, _szName);
    }
    else
    {
        _szName = new Char8[16];
        sprintf(_szName, "Barrier_%d", _barrierId);
    }
}

/** \brief Destructor
 */

BarrierCommonBase::~BarrierCommonBase(void)
{
    delete [] _szName;
}

void BarrierCommonBase::addRef(void)
{
    _refCount++;
}

void BarrierCommonBase::subRef(void)
{
    _refCount--;
}

Bool BarrierCommonBase::inUse(void)
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

char PThreadBarrierBase::cvsid[] = "@(#)$Id: $";

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

PThreadBarrierBase *PThreadBarrierBase::create(const Char8 *szName)
{
    PThreadBarrierBase *returnValue = NULL;

    returnValue = new PThreadBarrierBase(szName);

    if(returnValue->init() == false)
    {
        delete returnValue;
        returnValue = NULL;
    }
    
    return returnValue;
}

void PThreadBarrierBase::destroy(PThreadBarrierBase *barrierP)
{
    if(barrierP != NULL)
    {
        barrierP->shutdown();
        delete barrierP;
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

void PThreadBarrierBase::enter(UInt32 numWaitFor)
{
    if (numWaitFor <= 1)
        return;
        
    pthread_mutex_lock(&(_lockOne));

    _count++;

    if(_count < numWaitFor)
    {
        /* not enough threads are waiting => wait */
        pthread_cond_wait(&(_wakeupCondition), &(_lockOne));
    }
    else
    {
        /* ok, enough threads are waiting
           => wake up all waiting threads 
        */
        pthread_cond_broadcast(&(_wakeupCondition));
        
    }

    pthread_mutex_lock(&(_lockTwo));         
    
    if(_count == numWaitFor)
    {
        _count = 0;
        pthread_cond_init(&(_wakeupCondition), NULL);
        
    }
    
    pthread_mutex_unlock(&(_lockTwo));               
    
    pthread_mutex_unlock(&(_lockOne));
}

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

    /// Constructor used by the create function
PThreadBarrierBase::PThreadBarrierBase(const char *szName) :
    Inherited(szName),

    _lockOne         (),
    _lockTwo         (),
    _wakeupCondition (),
    _count           (0)    
{
}

PThreadBarrierBase::~PThreadBarrierBase(void)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

Bool PThreadBarrierBase::init(void)
{
    pthread_cond_init (&(_wakeupCondition), NULL);
    pthread_mutex_init(&(_lockOne),         NULL);
    pthread_mutex_init(&(_lockTwo),         NULL);
        
    _count = 0;

    return true;
}

void PThreadBarrierBase::shutdown(void)
{
    pthread_cond_destroy (&(_wakeupCondition));
    pthread_mutex_destroy(&(_lockOne));
    pthread_mutex_destroy(&(_lockTwo));
}

#endif /* OSG_USE_PTHREADS */

#if defined (OSG_USE_SPROC)

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char SprocBarrierBase::cvsid[] = "@(#)$Id: $";

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

SprocBarrierBase *SprocBarrierBase::create(const Char8  *szName)
{
    SprocBarrierBase *returnValue = NULL;

    returnValue = new SprocBarrierBase(szName);

    if(returnValue->init() == false)
    {
        delete returnValue;
        returnValue = NULL;
    }
    
    return returnValue;
}

void SprocBarrierBase::destroy(SprocBarrierBase *barrierP)
{
    if(barrierP != NULL)
    {
        barrierP->shutdown();
        delete barrierP;
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

void SprocBarrierBase::enter(UInt32 numWaitFor)
{
    if(_barrierP != NULL)
        barrier(_barrierP, numWaitFor);
}

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/// Constructor used by the create function
SprocBarrierBase::SprocBarrierBase(const Char8  *szName) :
    Inherited(szName),

    _barrierP(NULL)
{
}

SprocBarrierBase::~SprocBarrierBase(void)
{
}


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

Bool SprocBarrierBase::init(void)
{
    ThreadManager *pThreadManager = ThreadManager::the();

    if(pThreadManager == NULL)
        return false;

    if(pThreadManager->getArena() == NULL)
        return false;

    _barrierP = new_barrier(pThreadManager->getArena());

    if(_barrierP == NULL)
        return false;

    init_barrier(_barrierP);

    return true;

}

void SprocBarrierBase::shutdown(void)
{
    if(_barrierP != NULL)
        free_barrier(_barrierP);   
}

#endif /* OSG_USE_SPROC */



#if defined (OSG_USE_WINTHREADS)

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char WinThreadBarrierBase::cvsid[] = "@(#)$Id: $";

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

WinThreadBarrierBase *WinThreadBarrierBase::create(
    const Char8  *szName)
{
    WinThreadBarrierBase *returnValue = NULL;

    returnValue = new WinThreadBarrierBase(szName);

    if(returnValue->init() == false)
    {
        delete returnValue;
        returnValue = NULL;
    }
    
    return returnValue;
}

void WinThreadBarrierBase::destroy(WinThreadBarrierBase *barrierP)
{
    if(barrierP != NULL)
    {
        barrierP->shutdown();
        delete [] barrierP;
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

void WinThreadBarrierBase::enter(UInt32 numWaitFor)
{
    if (numWaitFor <= 1)
        return;
        
    WaitForSingleObject(_mutex1, INFINITE);

    _count++;

    if(_count < numWaitFor)
    {
        /* not enough threads are waiting => wait */

        ReleaseMutex(_mutex1);
        WaitForSingleObject(_conditionEvent, INFINITE);
    }
    else
    {
        /* ok, enough threads are waiting
           => wake up all waiting threads 
        */

        ReleaseMutex(_mutex1);
        SetEvent(_conditionEvent);        
    }

	WaitForSingleObject(_mutex2, INFINITE);
    
    if(_count == numWaitFor)
    {
        _count = 0;
        ResetEvent(_conditionEvent);
        
    }

	ReleaseMutex(_mutex2);
}

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/// Constructor used by the create function
WinThreadBarrierBase::WinThreadBarrierBase(const Char8  *szName) :
    Inherited(szName),

	_count(0),
	_mutex1(NULL),
	_mutex2(NULL),
	_conditionEvent(NULL)

{
}

WinThreadBarrierBase::~WinThreadBarrierBase(void)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

Bool WinThreadBarrierBase::init(void)
{
    Char8 *pTmp;

    pTmp = new Char8[strlen(_szName) + 5];

    sprintf(pTmp, "%sWE", _szName);

	_conditionEvent = CreateEvent(NULL,
								  TRUE,
								  FALSE,
								  pTmp); 

    if(_conditionEvent == NULL) 
	{
		fprintf(stderr, "Event create failed\n");
		return false;
    }

    sprintf(pTmp, "%sM1", _szName);

	_mutex1 = CreateMutex(NULL,   // no security attributes
		 				  FALSE,  // initially not owned
						  pTmp);  // name of mutex
	
	if(_mutex1 == NULL) 
	{
        CloseHandle(_conditionEvent);

		fprintf(stderr, "Create mutex1 failed\n");
		return false;
    }


    sprintf(pTmp, "%sM2", _szName);

	_mutex2 = CreateMutex(NULL,   // no security attributes
		 				  FALSE,  // initially not owned
						  pTmp);  // name of mutex
	
	if(_mutex2 == NULL) 
	{
        CloseHandle(_conditionEvent);
        CloseHandle(_mutex1);

		fprintf(stderr, "Create mutex2 failed\n");
		return false;
    }

    delete [] pTmp;

    return true;
}

void WinThreadBarrierBase::shutdown(void)
{
    if(_conditionEvent != NULL)
        CloseHandle(_conditionEvent);

    if(_mutex1 != NULL)
        CloseHandle(_mutex1);

    if(_mutex2 != NULL)
        CloseHandle(_mutex2);
}

#endif /* OSG_USE_WINTHREADS */

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

