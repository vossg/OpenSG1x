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

OSG_BEGIN_NAMESPACE


// Positions3d

template<>
inline Pnt3f
GeoProperty<GeoPositions3dPropertyDesc>::getValue( const UInt32 index )
{
    const Pnt3d &val = _field.getValue( index );
    return Pnt3f( val[0], val[1], val[2] );
}

template<>
inline Pnt3f
GeoProperty<GeoPositions3dPropertyDesc>::getValue( const UInt32 index ) const
{
    const Pnt3d &val = _field.getValue( index );
    return Pnt3f( val[0], val[1], val[2] );
}

template<>
inline void
GeoProperty<GeoPositions3dPropertyDesc>::getValue(
    Pnt3f & res,
    const UInt32 index )
{
    const Pnt3d &val = _field.getValue( index );
    res.setValues( val[0], val[1], val[2] );
}

template<>
inline void
GeoProperty<GeoPositions3dPropertyDesc>::getValue(
    Pnt3f & res,
    const UInt32 index ) const
{
    const Pnt3d &val = _field.getValue( index );
    res.setValues( val[0], val[1], val[2] );
}

template<>
inline void
GeoProperty<GeoPositions3dPropertyDesc>::setValue( const Pnt3f & val,
    const UInt32 index )
{
    _field.setValue( Pnt3d( val[0], val[1], val[2]), index );
}

template<>
inline void
GeoProperty<GeoPositions3dPropertyDesc>::addValue( const Pnt3f & val )
{
    _field.addValue(Pnt3d( val[0], val[1], val[2]));
}


OSG_END_NAMESPACE
