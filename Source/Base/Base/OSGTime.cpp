/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#include <iostream>

#ifdef WIN32
  #include <time.h>
#else
  #include <sys/types.h>
  #include <sys/time.h>
#endif

#include "OSGTime.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/


/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

Time getSystemTime (void)
{
    Time time;

#ifdef WIN32

    /*  use _ftime() funktion, is less precise
    struct _timeb timebuffer;
    _ftime(&timebuffer);
    time = double (timebuffer.millitm) / 1000.0 + double (timebuffer.time);
    */

    time = Time(timeGetTime()) / 1000.0;

#else

    struct timeval tv;
    gettimeofday(&tv, 0);
    time = Time(tv.tv_usec) / 1000000.0 + Time(tv.tv_sec);

#endif

    return time;
}

Int64 getPerfCounter(void)
{
#ifdef WIN32
    Int64 iCounter;
    
    QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER *>(&iCounter));

    return iCounter;
#else
#ifdef OSG_LONGLONG_HAS_LL
    return 0LL;
#else
    return 0;
#endif
#endif
}

Int64 getPerfCounterFreq(void)
{
#ifdef WIN32
    Int64 iCounterFreq;
    
    QueryPerformanceFrequency(
        reinterpret_cast<LARGE_INTEGER *>(&iCounterFreq));

    return iCounterFreq;
#else
#ifdef OSG_LONGLONG_HAS_LL
    return 0LL;
#else
    return 0;
#endif
#endif
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

OSG_END_NAMESPACE
