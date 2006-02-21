/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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
/*! \file OSGRefPtr.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <stdlib.h>
#include <stdio.h>

OSG_BEGIN_NAMESPACE

// RefPtr methods

template< class Ref >
RefPtr<Ref>::RefPtr(void) : _ref(NullFC)
{}

template< class Ref >
RefPtr<Ref>::RefPtr(const Ref& ref) : _ref(ref)
{
    addRefCP(_ref);
}

template< class Ref >
RefPtr<Ref>::RefPtr(const RefPtr<Ref>& ptr) : _ref(ptr._ref)
{
    addRefCP(_ref);
}

template< class Ref >
RefPtr<Ref>::~RefPtr()
{
    if(_ref != NullFC)
        subRefCP(_ref);
}

template< class Ref >
RefPtr<Ref>::operator Ref(void) const
{
    return _ref;
}

template< class Ref >
typename Ref::StoredObjectType* RefPtr<Ref>::operator->(void) const
{
    return &(*_ref);
}

template< class Ref >
typename Ref::StoredObjectType* RefPtr<Ref>::getCPtr(void) const
{
    return &(*_ref);
}

template< class Ref >
Ref RefPtr<Ref>::get(void) const
{
    return _ref;
}

template< class Ref >
RefPtr<Ref>& RefPtr<Ref>::operator =(const Ref& fcp)
{
    setRef(fcp);
    
    return *this;
}

template< class Ref >
RefPtr<Ref>& RefPtr<Ref>::operator =(const RefPtr<Ref>& rcp)
{
    setRef(rcp._ref);
    
    return *this;
}

template< class Ref >
RefPtr<Ref>& RefPtr<Ref>::operator =(const NullFieldContainerPtr&)
{
    setRef(NullFC);
    
    return *this;
}


template< class Ref >
bool RefPtr<Ref>::operator < (const NullFieldContainerPtr&) const
{
    return false;
}

template< class Ref >
bool RefPtr<Ref>::operator ==(const NullFieldContainerPtr&) const
{
    return _ref == NullFC;
}

template< class Ref >
bool RefPtr<Ref>::operator !=(const NullFieldContainerPtr&) const
{
    return _ref != NullFC;
}


template< class Ref >
bool RefPtr<Ref>::operator < (const FieldContainerPtr &other) const
{
    return _ref < other;
}

template< class Ref >
bool RefPtr<Ref>::operator ==(const FieldContainerPtr &other) const
{
    return _ref == other;
}

template< class Ref >
bool RefPtr<Ref>::operator !=(const FieldContainerPtr &other) const
{
    return !(_ref == other);
}


template< class Ref >
bool RefPtr<Ref>::operator < (const RefPtr<Ref> &other) const
{
    return _ref < other._ref;
}

template< class Ref >
bool RefPtr<Ref>::operator ==(const RefPtr<Ref> &other) const
{
    return _ref == other._ref;
}

template< class Ref >
bool RefPtr<Ref>::operator !=(const RefPtr<Ref> &other) const
{
    return !(_ref == other._ref);
}

template< class Ref >
bool RefPtr<Ref>::operator ! (void) const
{
    return _ref == NullFC;
}

template< class Ref >
RefPtr<Ref>::operator typename RefPtr<Ref>::unspecified_bool_type (void) const
{
    return  !*this ? 0 : &RefPtr<Ref>::_ref;
}


template< class Ref >
void RefPtr<Ref>::setRef(const Ref &ref)
{
    if(_ref == ref)
        return;

    if(_ref != NullFC)
        subRefCP(_ref);

    _ref = ref;

    if(_ref != NullFC)
        addRefCP(_ref);
}

OSG_END_NAMESPACE

#define OSGREFPTR_INLINE_CVSID "@(#)$Id: OSGRefPtr.inl,v 1.6 2006/02/21 16:40:08 dirk Exp $"

