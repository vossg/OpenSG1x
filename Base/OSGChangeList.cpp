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

#define OSG_COMPILEBASE

#include "OSGChangeList.h"
#include "OSGFieldContainerPtr.h"
#include "OSGFieldContainerFactory.h"
#include "OSGThread.h"
#include "OSGLog.h"
#include "OSGAspect.h"
#include "OSGThreadManager.h"

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

/** \brief Constructor
 */

ChangeList::ChangeList(void) :
    Inherited(),
    _bReadOnly(false),
    _aspectId(Thread::getAspect()),
    _listMode(Public),
    _changedFieldContainerV(),
    _addRefdFieldContainerV(),
    _subRefdFieldContainerV()
{
    Aspect::addList(this, _aspectId);
}


//CLASSNAME::CLASSNAME(const CLASSNAME &source) :
//	Inherited(source),
//	  // TODO: initialize members
//{
//}

/** \brief Destructor
 */

ChangeList::~ChangeList(void)
{
}

/*------------------------------ access -----------------------------------*/

ChangeList::changed_size_type ChangeList::sizeChanged(void)
{    
    return _changedFieldContainerV.size();
}

ChangeList::changed_const_iterator ChangeList::beginChanged(void) const
{
    return _changedFieldContainerV.begin();
}

ChangeList::changed_const_iterator ChangeList::endChanged(void) const
{
    return _changedFieldContainerV.end();
}

ChangeList::refd_size_type ChangeList::sizeAddRefd(void)
{
    return _addRefdFieldContainerV.size();
}

ChangeList::refd_const_iterator ChangeList::beginAddRefd(void) const
{
    return _addRefdFieldContainerV.begin();
}

ChangeList::refd_const_iterator ChangeList::endAddRefd(void) const
{
    return _addRefdFieldContainerV.end();
}

ChangeList::refd_size_type ChangeList::sizeSubRefd(void)
{
    return _subRefdFieldContainerV.size();
}

ChangeList::refd_const_iterator ChangeList::beginSubRefd(void) const
{
    return _subRefdFieldContainerV.begin();
}

ChangeList::refd_const_iterator ChangeList::endSubRefd(void) const
{
    return _subRefdFieldContainerV.end();
}

void ChangeList::addChanged(const FieldContainerPtr &fieldP, 
                                  BitVector          whichField)
{
    ChangeEntry tmpEntry;

    if(_bReadOnly == true)
        return;
    
    tmpEntry.first  = fieldP;
    tmpEntry.second = whichField;

    _changedFieldContainerV.push_back(tmpEntry);
}

void ChangeList::addAddRefd(const FieldContainerPtr &fieldP)
{
    if(_bReadOnly == true)
        return;

    _addRefdFieldContainerV.push_back(fieldP);
}

void ChangeList::addSubRefd(const FieldContainerPtr &fieldP)
{
    if(_bReadOnly == true)
        return;

    _subRefdFieldContainerV.push_back(fieldP);
}

void ChangeList::clearAll(void)
{
    _changedFieldContainerV.clear();
    _addRefdFieldContainerV.clear();
    _subRefdFieldContainerV.clear();
}

Bool ChangeList::merge(const ChangeList &list)
{
    Bool returnValue = true;
 
    _changedFieldContainerV.insert(_changedFieldContainerV.end(),
                                   list.beginChanged(), 
                                   list.endChanged());
    

    _addRefdFieldContainerV.insert(_addRefdFieldContainerV.end(),
                                   list.beginAddRefd(), 
                                   list.endAddRefd());
    

    _subRefdFieldContainerV.insert(_subRefdFieldContainerV.end(),
                                   list.beginSubRefd(), 
                                   list.endSubRefd());
    
   

    return returnValue;
}

void ChangeList::applyTo(UInt32 aspectId)
{
    UInt32 i;

    if(aspectId == _aspectId)
    {
        SWARNING << "Sync on the same aspects, ignored " << endl;
        return;
    }

    if(aspectId >= ThreadManager::getNumAspects())
    {
        SWARNING << "Invalid AspectId" << endl;
    }

    _bReadOnly = true;

    for(i = 0; i < _changedFieldContainerV.size(); i++)
    {
        _changedFieldContainerV[i].first.executeSync(
            _aspectId,
             aspectId,
            _changedFieldContainerV[i].second);
    }

    for(i = 0; i < _addRefdFieldContainerV.size(); i++)
    {
        osgAddRefCP(_addRefdFieldContainerV[i]);
    }

    for(i = 0; i < _subRefdFieldContainerV.size(); i++)
    {
        osgSubRefCP(_subRefdFieldContainerV[i]);
    }

    _changedFieldContainerV.clear();
    _addRefdFieldContainerV.clear();
    _subRefdFieldContainerV.clear();

    _bReadOnly = false;
}

void ChangeList::applyToCurrent(void)
{
    applyTo(Thread::getAspect());
}

void ChangeList::setAspect(UInt32 aspectId)
{
    if(_changedFieldContainerV.size() != 0 ||
       _addRefdFieldContainerV.size() != 0 ||
       _subRefdFieldContainerV.size() != 0)
    {
        SWARNING << "Changing aspect on non empty changelist, all currrent "
                 << "entries will be lost" << endl;          
    }

    clearAll();

    Aspect::moveList(this, _aspectId, aspectId);

    _aspectId = aspectId;
}

void ChangeList::setReadOnly(Bool readOnly)
{
    _bReadOnly = readOnly;
}

void ChangeList::dump(void)
{
    UInt32 i;

    fprintf(stderr, "CL: %d\n", _aspectId);
    fprintf(stderr, "CLChanged:\n");

    for(i = 0; i < _changedFieldContainerV.size(); i++)
    {
        fprintf(stderr, "\t%d\n", 
                _changedFieldContainerV[i].first.getContainerId());
    }

    fprintf(stderr, "CLAdd:\n");
    for(i = 0; i < _addRefdFieldContainerV.size(); i++)
    {
        fprintf(stderr, "\t%d\n", 
                _addRefdFieldContainerV[i].getContainerId());
    }

    fprintf(stderr, "CLSub:\n");
    for(i = 0; i < _subRefdFieldContainerV.size(); i++)
    {
        fprintf(stderr, "\t%d\n", 
                _subRefdFieldContainerV[i].getContainerId());
    }
}

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

#if 0

/** \brief assignment
 */

ChangeList& ChangeList::operator = (const ChangeList &source)
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

/** \brief assignment
 */

Bool ChangeList::operator < (const ChangeList &other) const
{
    return this < &other;
}


/** \brief equal
 */

Bool ChangeList::operator == (const ChangeList &other) const
{
}

/** \brief unequal
 */

Bool ChangeList::operator != (const ChangeList &other) const
{
	return ! (*this == other);
}

#endif

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



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

