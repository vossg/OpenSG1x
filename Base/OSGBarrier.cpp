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

#include "OSGBarrier.h"
#include "OSGBaseFunctions.h"

#if defined(OSG_USE_SPROC)
#include <OSGThreadManager.h>
#endif

OSG_USING_NAMESPACE

#if defined (OSG_USE_PTHREADS)

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGPThreadBarrierBase::cvsid[] = "@(#)$Id: $";

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

OSGPThreadBarrierBase *OSGPThreadBarrierBase::create(const char *szName, 
                                                     OSGUInt32   barrierId)
{
    OSGPThreadBarrierBase *returnValue = NULL;

    returnValue = new OSGPThreadBarrierBase(szName, barrierId);

    if(returnValue->init() == false)
    {
        delete returnValue;
        returnValue = NULL;
    }
    
    return returnValue;
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

OSGPThreadBarrierBase::~OSGPThreadBarrierBase(void)
{
    delete [] _szName;
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

void OSGPThreadBarrierBase::enter(OSGUInt32 numWaitFor)
{
    if (numWaitFor <= 1)
        return;
        
    pthread_mutex_lock(&(_lockOne));

    fprintf(stderr, "entered barrier\n");
    
    _count++;

    if(_count < numWaitFor)
    {
        /* not enough threads are waiting => wait */
        fprintf(stderr, "wait for cond\n");
        pthread_cond_wait(&(_wakeupCondition), &(_lockOne));
        fprintf(stderr, "after cond\n");
    }
    else
    {
        /* ok, enough threads are waiting
           => wake up all waiting threads 
        */
        fprintf(stderr, "before broadcast\n");
        pthread_cond_broadcast(&(_wakeupCondition));
        fprintf(stderr, "after broadcast\n");               
        
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

/*
bool CLASSNAME::operator < (const CLASSNAME &other)
{
    return this < &other;
}

bool CLASSNAME::operator == (const CLASSNAME &other)
{
}

bool CLASSNAME::operator != (const CLASSNAME &other)
{
	return ! (*this == other);
}
*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

    /// Constructor used by the create function
OSGPThreadBarrierBase::OSGPThreadBarrierBase(const char *szName, 
                                             OSGUInt32   barrierId) :
    _szName     (NULL),
    _barrierId(barrierId),
    _lockOne         (),
    _lockTwo         (),
    _wakeupCondition (),
    _count           (0)    
{
    stringDup(szName, _szName);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

bool OSGPThreadBarrierBase::init(void)
{
    pthread_cond_init (&(_wakeupCondition), NULL);
    pthread_mutex_init(&(_lockOne),         NULL);
    pthread_mutex_init(&(_lockTwo),         NULL);
        
    _count = 0;

    return true;
}

#endif /* OSG_USE_PTHREADS */

#if defined (OSG_USE_SPROC)

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGSprocBarrierBase::cvsid[] = "@(#)$Id: $";

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

OSGSprocBarrierBase *OSGSprocBarrierBase::create(const char *szName, 
                                                 OSGUInt32   barrierId)
{
    OSGSprocBarrierBase *returnValue = NULL;

    returnValue = new OSGSprocBarrierBase(szName, barrierId);

    if(returnValue->init() == false)
    {
        delete returnValue;
        returnValue = NULL;
    }
    
    return returnValue;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

OSGSprocBarrierBase::~OSGSprocBarrierBase(void)
{
    delete [] _szName;

    if(_barrierP != NULL)
        free_barrier(_barrierP);
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

void OSGSprocBarrierBase::enter(OSGUInt32 numWaitFor)
{
    fprintf(stderr, "Enter\n");
    if(_barrierP != NULL)
        barrier(_barrierP, numWaitFor);
    fprintf(stderr, "Leave\n");
}

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*
bool CLASSNAME::operator < (const CLASSNAME &other)
{
    return this < &other;
}

bool CLASSNAME::operator == (const CLASSNAME &other)
{
}

bool CLASSNAME::operator != (const CLASSNAME &other)
{
	return ! (*this == other);
}
*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/// Constructor used by the create function
OSGSprocBarrierBase::OSGSprocBarrierBase(const char *szName, 
                                         OSGUInt32   barrierId) :
    _szName     (NULL),
    _barrierId(barrierId),
    _barrierP(NULL)
{
    stringDup(szName, _szName);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

bool OSGSprocBarrierBase::init(void)
{
    OSGThreadManager *pThreadManager = OSGThreadManager::the();

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

#endif /* OSG_USE_SPROC */



#if defined (OSG_USE_WINTHREADS)

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGWinThreadBarrierBase::cvsid[] = "@(#)$Id: $";

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

OSGWinThreadBarrierBase *OSGWinThreadBarrierBase::create(const char *szName, 
											             OSGUInt32   barrierId)
{
    OSGWinThreadBarrierBase *returnValue = NULL;

    returnValue = new OSGWinThreadBarrierBase(szName, barrierId);

    if(returnValue->init() == false)
    {
        delete returnValue;
        returnValue = NULL;
    }
    
    return returnValue;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

OSGWinThreadBarrierBase::~OSGWinThreadBarrierBase(void)
{
    delete [] _szName;
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

void OSGWinThreadBarrierBase::enter(OSGUInt32 numWaitFor)
{
    fprintf(stderr, "Enter\n");

    if (numWaitFor <= 1)
        return;
        
    WaitForSingleObject(_mutex1, INFINITE);

    fprintf(stderr, "entered barrier\n");

	ReleaseMutex(_mutex1);
    
    _count++;

    if(_count < numWaitFor)
    {
        /* not enough threads are waiting => wait */
        fprintf(stderr, "wait for cond\n");
        WaitForSingleObject(_conditionEvent, INFINITE);
        fprintf(stderr, "after cond\n");
    }
    else
    {
        /* ok, enough threads are waiting
           => wake up all waiting threads 
        */
        fprintf(stderr, "before broadcast\n");
        SetEvent(_conditionEvent);
        fprintf(stderr, "after broadcast\n");               
        
    }

	WaitForSingleObject(_mutex2, INFINITE);
    
    if(_count == numWaitFor)
    {
        _count = 0;
        ResetEvent(_conditionEvent);
        
    }

	ReleaseMutex(_mutex2);

    fprintf(stderr, "Leave\n");
}

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*
bool CLASSNAME::operator < (const CLASSNAME &other)
{
    return this < &other;
}

bool CLASSNAME::operator == (const CLASSNAME &other)
{
}

bool CLASSNAME::operator != (const CLASSNAME &other)
{
	return ! (*this == other);
}
*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/// Constructor used by the create function
OSGWinThreadBarrierBase::OSGWinThreadBarrierBase(const char *szName, 
											     OSGUInt32   barrierId) :
    _szName     (NULL),
    _barrierId(barrierId),
	_count(0),
	_mutex1(NULL),
	_mutex2(NULL),
	_conditionEvent(NULL)

{
    stringDup(szName, _szName);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

bool OSGWinThreadBarrierBase::init(void)
{
	_conditionEvent = CreateEvent(NULL,
								  TRUE,
								  FALSE,
								  "WriteEvent"); 

    if(_conditionEvent == NULL) 
	{
		fprintf(stderr, "Event create failed\n");
		return false;
    }

	_mutex1 = CreateMutex(NULL,   // no security attributes
		 				  FALSE,  // initially not owned
						  "xx");  // name of mutex
	
	if(_mutex1 == NULL) 
	{
		fprintf(stderr, "Create mutex1 failed\n");
		return false;
    }

	_mutex2 = CreateMutex(NULL,   // no security attributes
		 				  FALSE,  // initially not owned
						  "xx");  // name of mutex
	
	if(_mutex2 == NULL) 
	{
		fprintf(stderr, "Create mutex2 failed\n");
		return false;
    }

    return true;
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

