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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGMPBase.h"
#include <OSGTypeFactory.h>
#include <OSGBaseFunctions.h>
#include <OSGThreadManager.h>

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGMPBASE_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class osg::MPType
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

MPType::MPType(const Char8 *szName, 
               const Char8 *szParentName) :
    Inherited(szName, szParentName)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

MPType::~MPType(void)
{
}



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class osg::MPThreadType
 */

UInt32 MPThreadType::_uiThreadCount = 0;

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

MPThreadType::MPThreadType(const Char8          *szName, 
                           const Char8          *szParentName,
                                 CreateThreadF   fCreateThread,
                                 InitThreadingF  fInitThreading) :
     Inherited    (szName, szParentName),

    _fCreateThread(fCreateThread)
{
    ThreadManager::the()->registerThreadType(this);

    if(fInitThreading != NULL)
        fInitThreading();
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

MPThreadType::~MPThreadType(void)
{
}

/*-------------------------------------------------------------------------*/
/*                            Construction                                 */

BaseThread *MPThreadType::create(const Char8 *szName)
{
    Char8  *szTmp;
    UInt32  uiNewId = _uiThreadCount++;

    if(szName == NULL)
    {
        szTmp = new Char8[16];
        sprintf(szTmp, "OSGThread_%u", uiNewId);
    }
    else
    {
        szTmp = const_cast<Char8 *>(szName);
    }

    if(_fCreateThread != NULL)
        return _fCreateThread(szTmp, uiNewId);
    else
        return NULL;
}



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class osg::MPBarrierType
 */

UInt32 MPBarrierType::_uiBarrierCount = 0;

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

MPBarrierType::MPBarrierType(const Char8          *szName, 
                             const Char8          *szParentName,
                                   CreateBarrierF  fCreateBarrier) :
     Inherited     (szName, szParentName),
    _fCreateBarrier(fCreateBarrier)
{
    ThreadManager::the()->registerBarrierType(this);
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

MPBarrierType::~MPBarrierType(void)
{
}

/*-------------------------------------------------------------------------*/
/*                            Construction                                 */

Barrier *MPBarrierType::create(const Char8 *szName)
{
    UInt32 uiNewId = _uiBarrierCount++;

    if(_fCreateBarrier != NULL)
        return _fCreateBarrier(szName, uiNewId);
    else
        return NULL;
}



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class osg::MPLockType
 */

UInt32 MPLockType::_uiLockCount = 0;

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

MPLockType::MPLockType(const Char8       *szName, 
                       const Char8       *szParentName,
                             CreateLockF  fCreateLock) :
    Inherited(szName, szParentName),
    _fCreateLock(fCreateLock)
{
    ThreadManager::the()->registerLockType(this);
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

MPLockType::~MPLockType(void)
{
}

/*-------------------------------------------------------------------------*/
/*                            Construction                                 */

Lock *MPLockType::create(const Char8 *szName)
{
    UInt32 uiNewId = _uiLockCount++;

    if(_fCreateLock != NULL)
        return _fCreateLock(szName, uiNewId);
    else
        return NULL;
}



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class osg::MPLockPoolType
 */

UInt32 MPLockPoolType::_uiLockPoolCount = 0;

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

MPLockPoolType::MPLockPoolType(
    const Char8           *szName, 
    const Char8           *szParentName,
          CreateLockPoolF  fCreateLockPool) :

    Inherited(szName, szParentName),
    _fCreateLockPool(fCreateLockPool)
{
    ThreadManager::the()->registerLockPoolType(this);
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

MPLockPoolType::~MPLockPoolType(void)
{
}

/*-------------------------------------------------------------------------*/
/*                            Construction                                 */

LockPool *MPLockPoolType::create(const Char8 *szName)
{
    UInt32 uiNewId = _uiLockPoolCount++;

    if(_fCreateLockPool != NULL)
        return _fCreateLockPool(szName, uiNewId);
    else
        return NULL;
}



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class osg::MPBase
 */

MPType MPBase::_type("OSGMPBase", NULL);

/*-------------------------------------------------------------------------*/
/*                            Class Get                                    */

const MPType &MPBase::getStaticType(void)
{
    return _type;
}

UInt32 MPBase::getStaticTypeId(void)
{
    return 0;
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

MPType &MPBase::getType(void)
{
    return _type;
}

const MPType &MPBase::getType(void) const
{
    return _type;
}

UInt32 MPBase::getTypeId(void)
{
    return getType().getId();
}

const Char8 *MPBase::getCName(void) const
{
    return _szName;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

MPBase::MPBase(const Char8 *szName) :
     Inherited(),
    
    _szName   (NULL)
{
    stringDup(szName, _szName);
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

MPBase::~MPBase(void)
{
    delete [] _szName;
}
