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

#define OSG_COMPILESYSTEMLIB

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGChangeList.h"
#include "OSGThread.h"
#include "OSGThreadManager.h"
#include "OSGLog.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char ChangeList::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

ChangeList::ChangeList(void) :
	Inherited(),
    _bReadOnly(false),
    _uiAspectId(Thread::getAspect()),
    _listMode(Public),
    _vChangedFieldContainers(),
    _vAddRefdFieldContainers(),
    _vSubRefdFieldContainers(),
    _vCreatedFieldContainers(),
    _vDestroyedFieldContainers()
{
//    Aspect::addList(this, _aspectId);
}


/** \brief Destructor
 */

ChangeList::~ChangeList(void)
{
}

/*------------------------------ access -----------------------------------*/

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

void ChangeList::addChanged(const FieldContainerPtr &pFieldContainer, 
                                  BitVector          bvWhichField)
{
    if(_bReadOnly == true)
        return;

    ChangeEntry tmpEntry(pFieldContainer, bvWhichField);

    _vChangedFieldContainers.push_back(tmpEntry);
}

void ChangeList::addAddRefd(const FieldContainerPtr &pFieldContainer)
{
    if(_bReadOnly == true)
        return;

    _vAddRefdFieldContainers.push_back(pFieldContainer);
}

void ChangeList::addSubRefd(const FieldContainerPtr &pFieldContainer)
{
    if(_bReadOnly == true)
        return;

    _vSubRefdFieldContainers.push_back(pFieldContainer);
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

void ChangeList::clearAll(void)
{
    _vChangedFieldContainers.clear();
    _vAddRefdFieldContainers.clear();
    _vSubRefdFieldContainers.clear();

    _vCreatedFieldContainers  .clear();
    _vDestroyedFieldContainers.clear();
}

Bool ChangeList::merge(const ChangeList &clist)
{
    Bool returnValue = true;
 
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

void ChangeList::applyTo(UInt32 uiAspectId)
{
    UInt32 i;

    if(uiAspectId == _uiAspectId)
    {
        SWARNING << "Sync on the same aspect, ignored " << endl;
        return;
    }

    if(uiAspectId >= ThreadManager::getNumAspects())
    {
        SWARNING << "Invalid AspectId" << endl;
    }

    _bReadOnly = true;

    for(i = 0; i < _vChangedFieldContainers.size(); i++)
    {
        _vChangedFieldContainers[i].first.executeSync(
            _uiAspectId,
             uiAspectId,
            _vChangedFieldContainers[i].second);
    }

    for(i = 0; i < _vAddRefdFieldContainers.size(); i++)
    {
//        osgAddRefCP(_addRefdFieldContainerV[i]);
    }

    for(i = 0; i < _vSubRefdFieldContainers.size(); i++)
    {
//        osgSubRefCP(_subRefdFieldContainerV[i]);
    }

    clearAll();

    _bReadOnly = false;
}

void ChangeList::applyToCurrent(void)
{
    applyTo(Thread::getAspect());
}

void ChangeList::setAspect(UInt32 uiAspectId)
{
    if(_vChangedFieldContainers.size() != 0 ||
       _vAddRefdFieldContainers.size() != 0 ||
       _vSubRefdFieldContainers.size() != 0)
    {
        SWARNING << "Changing aspect on non empty changelist, all currrent "
                    << "entries will be lost" << endl;          
    }

    clearAll();

//    OSGAspect::moveList(this, _aspectId, aspectId);

    _uiAspectId = uiAspectId;
}

void ChangeList::setReadOnly(Bool bReadOnly)
{
    _bReadOnly = bReadOnly;
}

void ChangeList::dump(void)
{
    UInt32 i;

    fprintf(stderr, "CL: %d\n", _uiAspectId);
    fprintf(stderr, "CLChanged:\n");

    for(i = 0; i < _vChangedFieldContainers.size(); i++)
    {
        fprintf(stderr, "\t%d\n", 
                _vChangedFieldContainers[i].first.getFieldContainerId());
    }

    fprintf(stderr, "CLAdd:\n");
    for(i = 0; i < _vAddRefdFieldContainers.size(); i++)
    {
        fprintf(stderr, "\t%d\n", 
                _vAddRefdFieldContainers[i].getFieldContainerId());
    }

    fprintf(stderr, "CLSub:\n");
    for(i = 0; i < _vSubRefdFieldContainers.size(); i++)
    {
        fprintf(stderr, "\t%d\n", 
                _vSubRefdFieldContainers[i].getFieldContainerId());
    }

    fprintf(stderr, "CLCreate:\n");
    for(i = 0; i < _vCreatedFieldContainers.size(); i++)
    {
        fprintf(stderr, "\t%d\n", _vCreatedFieldContainers[i]);
    }
    
    fprintf(stderr, "CLDestroy:\n");
    for(i = 0; i < _vDestroyedFieldContainers.size(); i++)
    {
        fprintf(stderr, "\t%d\n", _vDestroyedFieldContainers[i]);
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

