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

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGChangeList.cpp
    \ingroup GrpSystemMultithreading
 */
#endif

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGChangeList.h"
#include "OSGThread.h"
#include "OSGThreadManager.h"
#include "OSGLog.h"
#include "OSGFieldContainerFactory.h"
#include <OSGFieldContainerPtr.h>
#include "OSGRemoteAspect.h"

OSG_USING_NAMESPACE

bool ChangeList::_bReadWriteDefault = false;

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

ChangeList::ChangeList(void) :
     Inherited                (                   ),
    _bReadOnly                (!_bReadWriteDefault),
    _uiAspectId               (Thread::getAspect()),
    _listMode                 (Public             ),
    _vChangedFieldContainers  (                   ),
    _vAddRefdFieldContainers  (                   ),
    _vSubRefdFieldContainers  (                   ),
    _vCreatedFieldContainers  (                   ),
    _vDestroyedFieldContainers(                   )
{
//    Aspect::addList(this, _aspectId);
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

ChangeList::~ChangeList(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

ChangeList::changed_size_type ChangeList::sizeChanged(void)
{    
    return _vChangedFieldContainers.size();
}

ChangeList::changed_const_iterator ChangeList::beginChanged(void) const
{
    return _vChangedFieldContainers.begin();
}

ChangeList::changed_const_iterator ChangeList::endChanged(void) const
{
    return _vChangedFieldContainers.end();
}

ChangeList::refd_size_type ChangeList::sizeAddRefd(void)
{
    return _vAddRefdFieldContainers.size();
}

ChangeList::refd_const_iterator ChangeList::beginAddRefd(void) const
{
    return _vAddRefdFieldContainers.begin();
}

ChangeList::refd_const_iterator ChangeList::endAddRefd(void) const
{
    return _vAddRefdFieldContainers.end();
}

ChangeList::refd_size_type ChangeList::sizeSubRefd(void)
{
    return _vSubRefdFieldContainers.size();
}

ChangeList::refd_const_iterator ChangeList::beginSubRefd(void) const
{
    return _vSubRefdFieldContainers.begin();
}

ChangeList::refd_const_iterator ChangeList::endSubRefd(void) const
{
    return _vSubRefdFieldContainers.end();
}

ChangeList::idrefd_const_iterator ChangeList::beginCreated(void) const
{
    return _vCreatedFieldContainers.begin();
}

ChangeList::idrefd_const_iterator ChangeList::endCreated(void) const
{
    return _vCreatedFieldContainers.end();
}

ChangeList::idrefd_size_type ChangeList::sizeCreated(void) const
{
    return _vCreatedFieldContainers.size();
}

ChangeList::idrefd_const_iterator ChangeList::beginDestroyed(void) const
{
    return _vDestroyedFieldContainers.begin();
}

ChangeList::idrefd_const_iterator ChangeList::endDestroyed(void) const
{
    return _vDestroyedFieldContainers.end();
}

ChangeList::idrefd_size_type ChangeList::sizeDestroyed(void) const
{
    return _vDestroyedFieldContainers.size();
}

/*-------------------------------------------------------------------------*/
/*                                Add                                      */

void ChangeList::addChanged(const FieldContainerPtr &pFieldContainer, 
                                  BitVector          bvWhichField)
{
    if(_bReadOnly == true)
        return;

    UInt32      uiContainerId(pFieldContainer.getFieldContainerId());

    ChangeEntry tmpEntry     (uiContainerId, bvWhichField);

    try
    {
        _vChangedFieldContainers.push_back(tmpEntry);
    }
    
    // std::bad_alloc doesn't work.
    catch(...)
    {
        // on windows the maximum vector size is 16777216 well
        // vector.max_size() returns 268435455 ????
        // to save some memory we recreate a more compact changelist.
        std::vector<ChangeEntry>::size_type oldSize = _vChangedFieldContainers.size();
        SWARNING << "Compacting ChangeList ..." << std::endl;
        // should move store/restore in this class, better wait for release 1.5.0
        RemoteAspect::storeChangeList(this);
        clearAll();
        RemoteAspect::restoreChangeList(this);
        SWARNING << "Compacted ChangeList from " << oldSize
                 << " to " << _vChangedFieldContainers.size() << " entries." << std::endl;
        _vChangedFieldContainers.push_back(tmpEntry);
    }
}

void ChangeList::addAddRefd(const FieldContainerPtr &pFieldContainer)
{
    if(_bReadOnly == true)
        return;

    UInt32 uiContainerId = pFieldContainer.getFieldContainerId();

    _vAddRefdFieldContainers.push_back(uiContainerId);
}

void ChangeList::addSubRefd(const FieldContainerPtr &pFieldContainer)
{
#if !defined(OSG_FIXED_MFIELDSYNC)
    if(_bReadOnly == true)
        return;
#endif

    UInt32 uiContainerId = pFieldContainer.getFieldContainerId();

    _vSubRefdFieldContainers.push_back(uiContainerId);
}

void ChangeList::addCreated  (const UInt32 uiContainerId)
{
    if(_bReadOnly == true)
        return;

    _vCreatedFieldContainers.push_back(uiContainerId);
}

void ChangeList::addDestroyed(const UInt32 uiContainerId)
{
    if(_bReadOnly == true)
        return;

    _vDestroyedFieldContainers.push_back(uiContainerId);
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void ChangeList::clearAll(void)
{
    _vChangedFieldContainers.clear();
    _vAddRefdFieldContainers.clear();
    _vSubRefdFieldContainers.clear();

    _vCreatedFieldContainers  .clear();
    _vDestroyedFieldContainers.clear();
}

void ChangeList::swap(ChangeList &clist)
{
    _vChangedFieldContainers.swap(clist._vChangedFieldContainers);
    _vAddRefdFieldContainers.swap(clist._vAddRefdFieldContainers);
    _vSubRefdFieldContainers.swap(clist._vSubRefdFieldContainers);
    _vCreatedFieldContainers.swap(clist._vCreatedFieldContainers);
    _vDestroyedFieldContainers.swap(clist._vDestroyedFieldContainers);
}

bool ChangeList::merge(const ChangeList &clist)
{
    bool returnValue = true;
 
    _vChangedFieldContainers.insert(_vChangedFieldContainers.end(),
                                    clist.beginChanged(), 
                                    clist.endChanged());
    
    
    _vAddRefdFieldContainers.insert(_vAddRefdFieldContainers.end(),
                                    clist.beginAddRefd(), 
                                    clist.endAddRefd());
    
    
    _vSubRefdFieldContainers.insert(_vSubRefdFieldContainers.end(),
                                    clist.beginSubRefd(), 
                                    clist.endSubRefd());

    _vCreatedFieldContainers.insert(_vCreatedFieldContainers.end(),
                                    clist.beginCreated(),
                                    clist.endCreated());

    _vDestroyedFieldContainers.insert(_vDestroyedFieldContainers.end(),
                                      clist.beginDestroyed(),
                                      clist.endDestroyed());

    return returnValue;
}

bool ChangeList::empty() const
{
    return _vChangedFieldContainers.empty() &&
           _vAddRefdFieldContainers.empty() &&
           _vSubRefdFieldContainers.empty() &&
           _vCreatedFieldContainers.empty() &&
           _vDestroyedFieldContainers.empty();
}

void ChangeList::setAspect(UInt32 uiAspectId)
{
    if(_vChangedFieldContainers.size() != 0 ||
       _vAddRefdFieldContainers.size() != 0 ||
       _vSubRefdFieldContainers.size() != 0)
    {
        SWARNING << "Changing aspect on non empty changelist, all currrent "
                    << "entries will be lost" << std::endl;          
    }

    clearAll();

//    OSGAspect::moveList(this, _aspectId, aspectId);

    _uiAspectId = uiAspectId;
}

void ChangeList::setReadOnly(bool bReadOnly)
{
    _bReadOnly = bReadOnly;
}

/*! Define whether ChangeLists are created read only by default or not. 
Per default they are created read only, to not have a memory leak in applications that
don't use multiple threads and don't clear the ChangeList. Thus if you want to use the
ChangeLists, multiple threads and/or the cluster you have to call
ChangeList::setReadOnlyDefault(true).

This function should only be called before osgInit.
*/
void ChangeList::setReadWriteDefault(bool bReadWrite)
{
    if(GlobalSystemState != Startup)
        FWARNING(("setReadWriteDefault: called after startup!\n"));
        
    _bReadWriteDefault = bReadWrite;
}

/*-------------------------------------------------------------------------*/
/*                               Apply                                     */

#ifndef OSG_DISABLE_DEPRECATED

void ChangeList::applyTo(UInt32 uiAspectId)
{
    UInt32 i;

    if(uiAspectId == _uiAspectId)
    {
        SWARNING << "Sync on the same aspect, ignored " << std::endl;
        return;
    }

    if(uiAspectId >= ThreadManager::getNumAspects())
    {
        SWARNING << "Invalid AspectId" << std::endl;
    }

    _bReadOnly = true;
    OSG::Thread::getCurrentChangeList()->setReadOnly(true);

    FieldContainerPtr pTmp;

    for(i = 0; i < _vChangedFieldContainers.size(); i++)
    {
        pTmp = FieldContainerFactory::the()->getContainer(
            _vChangedFieldContainers[i].first);

        if(pTmp == NullFC)
            continue;

        pTmp.executeSync(_uiAspectId,
                          uiAspectId,
                         _vChangedFieldContainers[i].second);
    }

    for(i = 0; i < _vAddRefdFieldContainers.size(); i++)
    {
        pTmp = FieldContainerFactory::the()->getContainer(
            _vAddRefdFieldContainers[i]);

        if(pTmp == NullFC)
            continue;

        addRefCP(pTmp);
    }

    for(i = 0; i < _vSubRefdFieldContainers.size(); i++)
    {
        pTmp = FieldContainerFactory::the()->getContainer(
            _vSubRefdFieldContainers[i]);

        if(pTmp == NullFC)
            continue;

        subRefCP(pTmp);
    }

    clearAll();

    _bReadOnly = false;
    OSG::Thread::getCurrentChangeList()->setReadOnly(false);

}

void ChangeList::applyToCurrent(void)
{
    applyTo(Thread::getAspect());
}

#endif

void ChangeList::apply(void)
{
    UInt32 i;

    if(OSG::Thread::getCurrentChangeList() == this)
    {
        SWARNING << "try to apply current changelist : ignored" << std::endl;
    }

    _bReadOnly = true;

    OSG::Thread::getCurrentChangeList()->setReadOnly(true);

    FieldContainerPtr pTmp;

    for(i = 0; i < _vChangedFieldContainers.size(); i++)
    {
        pTmp = FieldContainerFactory::the()->getContainer(
            _vChangedFieldContainers[i].first);

        if(pTmp == NullFC)
            continue;

        pTmp.executeSync(_uiAspectId,
                          Thread::getAspect(),
                         _vChangedFieldContainers[i].second);
    }

#if !defined(OSG_FIXED_MFIELDSYNC)
    for(i = 0; i < _vAddRefdFieldContainers.size(); i++)
    {
        pTmp = FieldContainerFactory::the()->getContainer(
            _vAddRefdFieldContainers[i]);

        if(pTmp == NullFC)
            continue;

        addRefCP(pTmp);
    }

    for(i = 0; i < _vSubRefdFieldContainers.size(); i++)
    {
        pTmp = FieldContainerFactory::the()->getContainer(
            _vSubRefdFieldContainers[i]);

        if(pTmp == NullFC)
            continue;

        subRefCP(pTmp);
    }
#endif

    _bReadOnly = false;

     OSG::Thread::getCurrentChangeList()->setReadOnly(false);
}

#if defined(OSG_FIXED_MFIELDSYNC)
void ChangeList::applySubRefs(void)
{
    _bReadOnly = false;

    OSG::Thread::getCurrentChangeList()->setReadOnly(false);

    FieldContainerPtr pTmp;

    std::vector<IdRefEntry>  tmpList;

    tmpList.swap(_vSubRefdFieldContainers);

    while(tmpList.size() != 0)
    {
        _vSubRefdFieldContainers.clear();

        for(UInt32 i = 0; i < tmpList.size(); i++)
        {
//            fprintf(stderr, "subref %d\n", tmpList[i]);

            pTmp = FieldContainerFactory::the()->getContainer(
                tmpList[i]);
            
            if(pTmp == NullFC)
                continue;
            
            pTmp.doSubRef();
        }
        
        tmpList.clear();
        tmpList.swap(_vSubRefdFieldContainers);
    }

    _bReadOnly = false;

     OSG::Thread::getCurrentChangeList()->setReadOnly(false);
}
#endif

void ChangeList::applyAndClear(void)
{
    apply   ();
    clearAll();
}

/*-------------------------------------------------------------------------*/
/*                              Dump                                       */

void ChangeList::dump(void)
{
    UInt32 i;

    fprintf(stderr, "CL: %u\n", _uiAspectId);
#if 0
    fprintf(stderr, "CLChanged:\n");

    for(i = 0; i < _vChangedFieldContainers.size(); i++)
    {
//        fprintf(stderr, "\t%d\n", 
//                _vChangedFieldContainers[i].first.getFieldContainerId());
        fprintf(stderr, "\t%u\n", 
                _vChangedFieldContainers[i].first);
    }
#endif

    fprintf(stderr, "CLAdd:\n");
    for(i = 0; i < _vAddRefdFieldContainers.size(); i++)
    {
//        fprintf(stderr, "\t%d\n", 
//                _vAddRefdFieldContainers[i].getFieldContainerId());
        fprintf(stderr, "\t%u\n", 
                _vAddRefdFieldContainers[i]);
    }

    fprintf(stderr, "CLSub:\n");
    for(i = 0; i < _vSubRefdFieldContainers.size(); i++)
    {
//        fprintf(stderr, "\t%d\n", 
//                _vSubRefdFieldContainers[i].getFieldContainerId());
        fprintf(stderr, "\t%u\n", 
                _vSubRefdFieldContainers[i]);
    }

    fprintf(stderr, "CLCreate:\n");
    for(i = 0; i < _vCreatedFieldContainers.size(); i++)
    {
        fprintf(stderr, "\t%u | ", _vCreatedFieldContainers[i]);

        FieldContainerPtr pTmp = FieldContainerFactory::the()->getContainer(
            _vCreatedFieldContainers[i]);
            
        if(pTmp != NullFC)
        {
            fprintf(stderr, "%s\n", pTmp->getType().getCName());
        }
        else
        {
            fprintf(stderr, "\n");
        }
    }
    
    fprintf(stderr, "CLDestroy:\n");
    for(i = 0; i < _vDestroyedFieldContainers.size(); i++)
    {
        fprintf(stderr, "\t%u\n", _vDestroyedFieldContainers[i]);
    }
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
    static Char8 cvsid_hpp[] = OSGCHANGELIST_HEADER_CVSID;
}
