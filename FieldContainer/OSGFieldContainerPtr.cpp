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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGFieldContainerBase.h"
#include "OSGFieldContainerPtr.h"
//#include "OSGFieldContainer.h"

/*
#include "OSGLog.h"
#include "OSGThread.h"
*/

#if defined(OSG_GV_BETA) && defined(OSG_DBG_MEM)
#include "OSGTime.h"
#endif

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE
const NullFieldContainerPtr NullFC;
OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class osg::FieldContainerPtrBase
 */

const UInt16    FieldContainerPtrBase::InvalidParentEPos = 0xFFFF;

      LockPool *FieldContainerPtrBase::_pRefCountLock    = NULL;



/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void FieldContainerPtrBase::dump(      UInt32    uiIndent,
                                 const BitVector bvFlags) const
{
    if(this != NULL && _storeP != NULL)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "FCPtr Dump :" << endl;

        uiIndent += 4;

        indentLog(uiIndent, PLOG);
        PLOG << "Id       : " << (*(getIdP()))   << endl;

        indentLog(uiIndent, PLOG);
        PLOG << "Storage  : " << hex << (UInt32 *)getFirstElemP() << endl;

        if(bvFlags & FCDumpFlags::RefCount)
        {
             indentLog(uiIndent, PLOG);
             PLOG << "RefCount : " << *(getRefCountP()) << endl;
        }

//        dumpContent();
    }
    else
    {
        PLOG << "FCPtr Dump : (NULL)" << endl;
    }
}

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

bool FieldContainerPtrBase::initialize(void)
{
    bool           returnValue = false;
    ThreadManager *pManager    = ThreadManager::the();

    SINFO << "OSGFieldContainerPtrBase init" << endl;

    if(pManager != NULL)
    {
        _pRefCountLock = pManager->getLockPool("DSPTRRefCountLockPool");

        addRefP(_pRefCountLock);

        if(_pRefCountLock != NULL)
            returnValue = true;
    }

    return returnValue;
}

bool FieldContainerPtrBase::terminate(void)
{
    ThreadManager *pManager = ThreadManager::the();

    SINFO << "OSGFieldContainerPtrBase terminate" << endl;

    if(pManager == NULL)
        return false;

    subRefP(_pRefCountLock);

    return true;
}


/*-------------------------------------------------------------------------*/
/*                               Functions                                 */

//! Write FC to the given stream

OSG_SYSTEMLIB_DLLMAPPING
ostream &OSG::operator <<(      ostream            &os,
                          const FieldContainerPtr  &fc)
{
    if(fc == NullFC)
    {
        os << hex << "FieldContainerPtr 0x" << &fc << dec << ":NullFC";
    }
    else
    {
        os << hex << "FieldContainerPtr 0x"
           << &fc << dec << ":" << fc->getType().getName() << "Ptr(0x"
           << hex << (&(*fc)) << dec << ")";
    }

    return os;
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
    static Char8 cvsid_hpp[] = OSGFIELDCONTAINERPTR_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGFIELDCONTAINERPTR_INLINE_CVSID;
}
