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

#include <iostream>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

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

template<class ChangeListDescT> inline
void ChangedChangeListMixin<ChangeListDescT>::clear(void)
{
    clearChanged();
}

template<class ChangeListDescT> inline
void ChangedChangeListMixin<ChangeListDescT>::merge(
    ChangedChangeListMixin &other)
{
    mergeChanged(other);
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

template<class ChangeListDescT> inline
ChangedChangeListMixin<ChangeListDescT>::ChangedChangeListMixin(void):
	 Inherited          (),
    _vChangedContainerStore()
{
}

template<class ChangeListDescT> inline
ChangedChangeListMixin<ChangeListDescT>::~ChangedChangeListMixin(void)
{
}

/*------------------------------ access -----------------------------------*/

template<class ChangeListDescT> inline
typename ChangedChangeListMixin<ChangeListDescT>::changed_size_type 
    ChangedChangeListMixin<ChangeListDescT>::sizeChanged (void) const
{
    return _vChangedContainerStore.size();
}

template<class ChangeListDescT> inline
typename ChangedChangeListMixin<ChangeListDescT>::changed_const_iterator 
    ChangedChangeListMixin<ChangeListDescT>::beginChanged(void) const
{
    return _vChangedContainerStore.begin();
}

template<class ChangeListDescT> inline
typename ChangedChangeListMixin<ChangeListDescT>::changed_const_iterator 
    ChangedChangeListMixin<ChangeListDescT>::endChanged  (void) const
{
    return _vChangedContainerStore.end();
}

template<class ChangeListDescT> inline
void ChangedChangeListMixin<ChangeListDescT>::addChanged(
    const ContainerId &oContainerId, 
          ChangedMask  oChangedMask)
{
    ChangedEntry tmpEntry;

//    if(_bReadOnly == true)
//        return;
    
    tmpEntry.first  = oContainerId;
    tmpEntry.second = oChangedMask;

    _vChangedContainerStore.push_back(tmpEntry);
}

template<class ChangeListDescT> inline
void ChangedChangeListMixin<ChangeListDescT>::clearChanged(void)
{
    _vChangedContainerStore.clear();
}

template<class ChangeListDescT> inline
void ChangedChangeListMixin<ChangeListDescT>::mergeChanged(
    ChangedChangeListMixin &other)
{
    _vChangedContainerStore.insert(_vChangedContainerStore.end(),
                                    other.beginChanged(), 
                                    other.endChanged());
    
}


OSG_END_NAMESPACE

#define OSG_INLINE_CVSID "@(#)$Id: $"
