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

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSGUInt32 OSGBarrierCommonBase::_barrierCount = 0;

char OSGBarrierCommonBase::cvsid[] = "@(#)$Id: $";

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

OSGBarrierCommonBase::OSGBarrierCommonBase(const OSGChar8 *szName):
    _szName(NULL),
    _barrierId(_barrierCount++),
    _refCount(0)
{
    if(szName != NULL)
    {
        stringDup(szName, _szName);
    }
    else
    {
        _szName = new OSGChar8[16];
        sprintf(_szName, "OSGBarrier_%d", _barrierId);
    }
}

/** \brief Destructor
 */

OSGBarrierCommonBase::~OSGBarrierCommonBase(void)
{
    delete [] _szName;
}

void OSGBarrierCommonBase::addRef(void)
{
    _refCount++;
}

void OSGBarrierCommonBase::subRef(void)
{
    _refCount--;
}

OSGBool OSGBarrierCommonBase::inUse(void)
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

OSGPThreadBarrierBase *OSGPThreadBarrierBase::create(const OSGChar8 *szName)
{
    OSGPThreadBarrierBase *returnValue = NULL;

    returnValue = new OSGPThreadBarrierBase(szName);

    if(returnValue->init() == false)
    {
        delete returnValue;
        returnValue = NULL;
    }
    
    return returnValue;
}

void OSGPThreadBarrierBase::destroy(OSGPThreadBarrierBase *barrierP)
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

void OSGPThreadBarrierBase::enter(OSGUInt32 numWaitFor)
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
OSGPThreadBarrierBase::OSGPThreadBarrierBase(const char *szName) :
    Inherited(szName),

    _lockOne         (),
    _lockTwo         (),
    _wakeupCondition (),
    _count           (0)    
{
}

OSGPThreadBarrierBase::~OSGPThreadBarrierBase(void)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

OSGBool OSGPThreadBarrierBase::init(void)
{
    pthread_cond_init (&(_wakeupCondition), NULL);
    pthread_mutex_init(&(_lockOne),         NULL);
    pthread_mutex_init(&(_lockTwo),         NULL);
        
    _count = 0;

    return true;
}

void OSGPThreadBarrierBase::shutdown(void)
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

OSGSprocBarrierBase *OSGSprocBarrierBase::create(const OSGChar8  *szName)
{
    OSGSprocBarrierBase *returnValue = NULL;

    returnValue = new OSGSprocBarrierBase(szName);

    if(returnValue->init() == false)
    {
        delete returnValue;
        returnValue = NULL;
    }
    
    return returnValue;
}

void OSGSprocBarrierBase::destroy(OSGSprocBarrierBase *barrierP)
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

void OSGSprocBarrierBase::enter(OSGUInt32 numWaitFor)
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
OSGSprocBarrierBase::OSGSprocBarrierBase(const OSGChar8  *szName) :
    Inherited(szName),

    _barrierP(NULL)
{
}

OSGSprocBarrierBase::~OSGSprocBarrierBase(void)
{
}


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

OSGBool OSGSprocBarrierBase::init(void)
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

void OSGSprocBarrierBase::shutdown(void)
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

OSGWinThreadBarrierBase *OSGWinThreadBarrierBase::create(
    const OSGChar8  *szName)
{
    OSGWinThreadBarrierBase *returnValue = NULL;

    returnValue = new OSGWinThreadBarrierBase(szName);

    if(returnValue->init() == false)
    {
        delete returnValue;
        returnValue = NULL;
    }
    
    return returnValue;
}

void OSGWinThreadBarrierBase::destroy(OSGWinThreadBarrierBase *barrierP)
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

void OSGWinThreadBarrierBase::enter(OSGUInt32 numWaitFor)
{
    if (numWaitFor <= 1)
        return;
        
    WaitForSingleObject(_mutex1, INFINITE);

	ReleaseMutex(_mutex1);
    
    _count++;

    if(_count < numWaitFor)
    {
        /* not enough threads are waiting => wait */
        WaitForSingleObject(_conditionEvent, INFINITE);
    }
    else
    {
        /* ok, enough threads are waiting
           => wake up all waiting threads 
        */
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
OSGWinThreadBarrierBase::OSGWinThreadBarrierBase(const OSGChar8  *szName) :
    Inherited(szName),

	_count(0),
	_mutex1(NULL),
	_mutex2(NULL),
	_conditionEvent(NULL)

{
    stringDup(szName, _szName);
}

OSGWinThreadBarrierBase::~OSGWinThreadBarrierBase(void)
{
    delete [] _szName;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

OSGBool OSGWinThreadBarrierBase::init(void)
{
    OSGChar8 *pTmp;

    pTmp = new OSGChar8[strlen(_szName) + 5];

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

void OSGWinThreadBarrierBase::shutdown(void)
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

