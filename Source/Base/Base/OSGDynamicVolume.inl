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

#ifndef _OSGDYNAMICVOLUME_INL_
#define _OSGDYNAMICVOLUME_INL_

#include "OSGBaseTypes.h"
#include "OSGBaseFunctions.h"

#include "OSGVector.h"
#include "OSGMatrix.h"
#include "OSGLine.h"

OSG_BEGIN_NAMESPACE

inline
bool
operator !=(const DynamicVolume &lhs, const DynamicVolume &rhs)
{
    return !(lhs == rhs);
}

inline
DynamicVolume::~DynamicVolume(void)
{
}

inline
const Volume &DynamicVolume::getInstance(void) const
{ 
    return *(reinterpret_cast<const OSG::Volume *>(_volumeMem)); 
}

inline
Volume &DynamicVolume::getInstance(void)
{ 
    return *(reinterpret_cast<OSG::Volume *>(_volumeMem)); 
}


inline
DynamicVolume::Type DynamicVolume::getType(void) const 
{
    return static_cast<Type>(_type); 
}

inline
void DynamicVolume::instanceChanged(void) 
{
    _state = getInstance().getState(); 
}

inline
void DynamicVolume::updateInstanceState(void)
{
    getInstance().setState(_state);
}

inline
void DynamicVolume::setValid(const bool value)
{
    Volume::setValid(value);
    updateInstanceState();
}

inline
void DynamicVolume::setEmpty(const bool value)
{
    Volume::setEmpty(value);
    updateInstanceState();
}

inline
void DynamicVolume::setStatic(const bool value)
{
    Volume::setStatic(value);
    updateInstanceState();
}

inline
void DynamicVolume::setInfinite(const bool value)
{
    Volume::setInfinite(value);
    updateInstanceState();
}

OSG_END_NAMESPACE

#endif // _OSGDYNAMICVOLUME_H_

