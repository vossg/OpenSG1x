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

OSGPThreadLockBase *OSGPThreadLockBase::create(const char *szName, 
                                               OSGUInt32   lockId)
{
    OSGPThreadLockBase *returnValue = NULL;

    returnValue = new OSGPThreadLockBase(szName, lockId);

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

OSGPThreadLockBase::~OSGPThreadLockBase(void)
{
    delete [] _szName;
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

void OSGPThreadLockBase::aquire(void)
{
//    fprintf(stderr, "aquire try Lock \n");
    pthread_mutex_lock  (&(_lowLevelLock));         
//    fprintf(stderr, "aquire got Lock \n");
}

void OSGPThreadLockBase::release(void)
{
//    fprintf(stderr, "release Lock \n");
    pthread_mutex_unlock(&(_lowLevelLock));               
}

/*-------------------------- assignment -----------------------------------*/

#if 0
CLASSNAME& CLASSNAME::operator = (const CLASSNAME &source)
{
	if (this == &source)
		return *this;

	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;

	// free mem alloced by members of 'this'

	// alloc new mem for members

	// copy 
}

/*-------------------------- comparison -----------------------------------*/

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
#endif

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

OSGPThreadLockBase::OSGPThreadLockBase(const char *szName, OSGUInt32 lockId):
    _szName(NULL),
    _lockId(lockId),
    _lowLevelLock()
{
    stringDup(szName, _szName);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

bool OSGPThreadLockBase::init(void)
{
    pthread_mutex_init(&(_lowLevelLock), NULL);

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

OSGSprocLockBase *OSGSprocLockBase::create(const char *szName, 
                                           OSGUInt32   lockId)
{
    OSGSprocLockBase *returnValue = NULL;

    returnValue = new OSGSprocLockBase(szName, lockId);

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

OSGSprocLockBase::~OSGSprocLockBase(void)
{
    OSGThreadManager *pThreadManager = OSGThreadManager::the();

    delete [] _szName;

    if(pThreadManager == NULL)
        return;

    if(pThreadManager->getArena() == NULL && _lowLevelLock != NULL)
        usfreelock(_lowLevelLock, pThreadManager->getArena());

}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

void OSGSprocLockBase::aquire(void)
{
//    fprintf(stderr, "aquire try Lock \n");
    
    if(_lowLevelLock != NULL)
        ussetlock(_lowLevelLock);
    
//    fprintf(stderr, "aquire got Lock \n");
}

void OSGSprocLockBase::release(void)
{
//    fprintf(stderr, "release Lock \n");

    if(_lowLevelLock != NULL)
        usunsetlock(_lowLevelLock);
}

/*-------------------------- assignment -----------------------------------*/

#if 0
CLASSNAME& CLASSNAME::operator = (const CLASSNAME &source)
{
	if (this == &source)
		return *this;

	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;

	// free mem alloced by members of 'this'

	// alloc new mem for members

	// copy 
}

/*-------------------------- comparison -----------------------------------*/

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
#endif

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

OSGSprocLockBase::OSGSprocLockBase(const char *szName, OSGUInt32 lockId):
    _szName(NULL),
    _lockId(lockId),
    _lowLevelLock(NULL)
{
    stringDup(szName, _szName);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

bool OSGSprocLockBase::init(void)
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

OSGWinThreadLockBase *OSGWinThreadLockBase::create(const char *szName, 
                                                   OSGUInt32   lockId)
{
    OSGWinThreadLockBase *returnValue = NULL;

    returnValue = new OSGWinThreadLockBase(szName, lockId);

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

OSGWinThreadLockBase::~OSGWinThreadLockBase(void)
{
	delete [] _szName;
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

void OSGWinThreadLockBase::aquire(void)
{
//    fprintf(stderr, "aquire try Lock \n");
    
    WaitForSingleObject(_mutex, INFINITE);

//    fprintf(stderr, "aquire got Lock \n");
}

void OSGWinThreadLockBase::release(void)
{
//    fprintf(stderr, "release Lock \n");

	ReleaseMutex(_mutex);
}

/*-------------------------- assignment -----------------------------------*/

#if 0
CLASSNAME& CLASSNAME::operator = (const CLASSNAME &source)
{
	if (this == &source)
		return *this;

	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;

	// free mem alloced by members of 'this'

	// alloc new mem for members

	// copy 
}

/*-------------------------- comparison -----------------------------------*/

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
#endif

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

OSGWinThreadLockBase::OSGWinThreadLockBase(const char *szName, OSGUInt32 lockId):
    _szName(NULL),
    _lockId(lockId),
	_mutex(NULL)
{
    stringDup(szName, _szName);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

bool OSGWinThreadLockBase::init(void)
{
	_mutex = CreateMutex(NULL,   // no security attributes
						 FALSE,  // initially not owned
						 "xx");  // name of mutex
	
	if(_mutex == NULL) 
	{
		fprintf(stderr, "Create mutex failed\n");
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

