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

#include "OSGConfig.h"

#include <stdlib.h>
#include <stdio.h>


#include <iostream>

#include "OSGBarrier.h"
#include "OSGBaseFunctions.h"

#include <OSGThreadManager.h>

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------


/*--------------------------- Constructors --------------------------------*/

BarrierCommonBase::BarrierCommonBase(const Char8  *szName,
                                           UInt32  uiId  ):
     Inherited  (szName),
    _uiBarrierId(uiId  )
{
}

/*---------------------------- Destructor ---------------------------------*/

BarrierCommonBase::~BarrierCommonBase(void)
{
}




#if defined (OSG_USE_PTHREADS)

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*--------------------------- Constructors --------------------------------*/

PThreadBarrierBase::PThreadBarrierBase(const Char8  *szName,
                                             UInt32  uiId  ) :
     Inherited        (szName, 
                       uiId),

    _pLockOne         (),
    _pLockTwo         (),
    _pWakeupCondition (),
    _uiCount          (0)
{
}

/*---------------------------- Destructor ---------------------------------*/

PThreadBarrierBase::~PThreadBarrierBase(void)
{
}

/*--------------------------- Construction --------------------------------*/

bool PThreadBarrierBase::init(void)
{
    pthread_cond_init (&(_pWakeupCondition), NULL);
    pthread_mutex_init(&(_pLockOne),         NULL);
    pthread_mutex_init(&(_pLockTwo),         NULL);

    _uiCount = 0;

    return true;
}

/*---------------------------- Destruction --------------------------------*/

void PThreadBarrierBase::shutdown(void)
{
    pthread_cond_destroy (&(_pWakeupCondition));
    pthread_mutex_destroy(&(_pLockOne));
    pthread_mutex_destroy(&(_pLockTwo));
}

/*------------------------------- Enter -----------------------------------*/

void PThreadBarrierBase::enter(UInt32 uiNumWaitFor)
{
    if(uiNumWaitFor <= 1)
        return;

    pthread_mutex_lock(&(_pLockOne));

    _uiCount++;

    if(_uiCount < uiNumWaitFor)
    {
        /* not enough threads are waiting => wait */

        pthread_cond_wait(&(_pWakeupCondition), &(_pLockOne));
    }
    else
    {
        /* ok, enough threads are waiting
           => wake up all waiting threads
        */

        pthread_cond_broadcast(&(_pWakeupCondition));

    }

    pthread_mutex_lock(&(_pLockTwo));

    if(_uiCount == uiNumWaitFor)
    {
        _uiCount = 0;

        pthread_cond_init(&(_pWakeupCondition), NULL);
    }

    pthread_mutex_unlock(&(_pLockTwo));

    pthread_mutex_unlock(&(_pLockOne));
}

#endif /* OSG_USE_PTHREADS */



#if defined (OSG_USE_SPROC)

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*--------------------------- Constructors --------------------------------*/

SprocBarrierBase::SprocBarrierBase(const Char8  *szName,
                                         UInt32  uiId  ) :
     Inherited(szName, uiId),

    _pBarrier (NULL)
{
}

/*---------------------------- Destructor ---------------------------------*/

SprocBarrierBase::~SprocBarrierBase(void)
{
}

/*--------------------------- Construction --------------------------------*/

bool SprocBarrierBase::init(void)
{
    ThreadManager *pThreadManager = ThreadManager::the();

    if(pThreadManager == NULL)
        return false;

    if(pThreadManager->getArena() == NULL)
        return false;

    _pBarrier = new_barrier(pThreadManager->getArena());

    if(_pBarrier == NULL)
        return false;

    init_barrier(_pBarrier);

    return true;
}

/*---------------------------- Destruction --------------------------------*/

void SprocBarrierBase::shutdown(void)
{
    if(_pBarrier != NULL)
        free_barrier(_pBarrier);
}

/*------------------------------ Enter ------------------------------------*/

void SprocBarrierBase::enter(UInt32 uiNumWaitFor)
{
    if(_pBarrier != NULL)
        barrier(_pBarrier, uiNumWaitFor);
}


#endif /* OSG_USE_SPROC */



#if defined (OSG_USE_WINTHREADS)

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*--------------------------- Constructors --------------------------------*/

WinThreadBarrierBase::WinThreadBarrierBase(const Char8  *szName,
                                                 UInt32  uiId  ) :
     Inherited      (szName, uiId),

    _uiCount        (0),
    _pMutex1        (NULL),
    _pMutex2        (NULL),
    _pConditionEvent(NULL)

{
}

/*---------------------------- Destructor ---------------------------------*/

WinThreadBarrierBase::~WinThreadBarrierBase(void)
{
}

/*--------------------------- Construction --------------------------------*/

bool WinThreadBarrierBase::init(void)
{
    Char8 *pTmp;

    pTmp = new Char8[strlen(_szName) + 5];

    sprintf(pTmp, "%sWE", _szName);

    _pConditionEvent = CreateEvent(NULL, TRUE, FALSE, pTmp);

    if(_pConditionEvent == NULL)
    {
        fprintf(stderr, "Event create failed\n");
        return false;
    }

    sprintf(pTmp, "%sM1", _szName);

    _pMutex1 = CreateMutex(NULL,   // no security attributes
                           FALSE,  // initially not owned
                           pTmp);  // name of mutex

    if(_pMutex1 == NULL)
    {
        CloseHandle(_pConditionEvent);

        fprintf(stderr, "Create mutex1 failed\n");
        return false;
    }


    sprintf(pTmp, "%sM2", _szName);

    _pMutex2 = CreateMutex(NULL,   // no security attributes
                           FALSE,  // initially not owned
                           pTmp);  // name of mutex

    if(_pMutex2 == NULL)
    {
        CloseHandle(_pConditionEvent);
        CloseHandle(_pMutex1);

        fprintf(stderr, "Create mutex2 failed\n");
        return false;
    }

    delete [] pTmp;

    return true;
}

/*---------------------------- Destruction --------------------------------*/

void WinThreadBarrierBase::shutdown(void)
{
    if(_pConditionEvent != NULL)
        CloseHandle(_pConditionEvent);

    if(_pMutex1 != NULL)
        CloseHandle(_pMutex1);

    if(_pMutex2 != NULL)
        CloseHandle(_pMutex2);
}

/*------------------------------ Enter ------------------------------------*/

void WinThreadBarrierBase::enter(UInt32 uiNumWaitFor)
{
    if(uiNumWaitFor <= 1)
        return;

    WaitForSingleObject(_pMutex1, INFINITE);

    _uiCount++;

    if(_uiCount < uiNumWaitFor)
    {
        /* not enough threads are waiting => wait */

        ReleaseMutex(_pMutex1);
        WaitForSingleObject(_pConditionEvent, INFINITE);
    }
    else
    {
        /* ok, enough threads are waiting
           => wake up all waiting threads
        */

        ReleaseMutex(_pMutex1);
        SetEvent(_pConditionEvent);

    }

    WaitForSingleObject(_pMutex2, INFINITE);

    if(_uiCount == uiNumWaitFor)
    {
        _uiCount = 0;
        ResetEvent(_pConditionEvent);
    }

    ReleaseMutex(_pMutex2);
}


#endif /* OSG_USE_WINTHREADS */



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

MPBarrierType Barrier::_type("OSGBarrier", "OSGMPBase", &Barrier::create);


/*-------------------------------- Get ------------------------------------*/

Barrier *Barrier::get(const Char8 *szName)
{
    return ThreadManager::the()->getBarrier(szName, "OSGBarrier");
}

Barrier *Barrier::find(const Char8 *szName)
{
    return ThreadManager::the()->findBarrier(szName);
}

Barrier *Barrier::create(void)
{
    return Barrier::get(NULL);
}

const MPBarrierType &Barrier::getClassType(void)
{
    return _type;
}

/*------------------------------- Enter -----------------------------------*/

void Barrier::enter(UInt32 uiNumWaitFor)
{
    Inherited::enter(uiNumWaitFor);
}

/*--------------------------- Constructors --------------------------------*/

Barrier::Barrier(const Char8  *szName,
                       UInt32  uiId  ) :
    Inherited(szName, uiId)
{
}

/*---------------------------- Destructor ---------------------------------*/

Barrier::~Barrier(void)
{
    ThreadManager::the()->removeBarrier(this);

    shutdown();
}

/*------------------------------ Create -----------------------------------*/

Barrier *Barrier::create (const Char8  *szName,
                                UInt32  uiId  )
{
    Barrier *returnValue = NULL;

    returnValue = new Barrier(szName, uiId);

    if(returnValue->init() == false)
    {
        delete returnValue;
        returnValue = NULL;
    }

    return returnValue;
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
    static Char8 cvsid_hpp[] = OSGBARRIER_HEADER_CVSID;
}

