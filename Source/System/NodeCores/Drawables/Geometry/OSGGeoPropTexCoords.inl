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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

OSG_BEGIN_NAMESPACE


// TexCoords1f

template<> inline 
Vec2f GeoProperty<GeoTexCoords1fPropertyDesc>::getValue(const UInt32 index)
{
    return Vec2f(_field[index], 0.f);
}

template<> inline 
Vec2f GeoProperty<GeoTexCoords1fPropertyDesc>::getValue(
    const UInt32 index) const
{
    return Vec2f(_field[index], 0.f);
}

template<> inline 
void GeoProperty<GeoTexCoords1fPropertyDesc>::getValue(
          Vec2f  &res,
    const UInt32  index)
{
    res.setValues(_field[index], 0.f);
}

template<> inline 
void GeoProperty<GeoTexCoords1fPropertyDesc>::getValue(
          Vec2f  &res,
    const UInt32  index) const
{
    res.setValues(_field[index], 0.f);
}

template<>
inline void
GeoProperty<GeoTexCoords1fPropertyDesc>::setValue( const Vec2f & val,
    const UInt32 index )
{
    _field[index].setValues(val[0]);
}

template<>
inline void
GeoProperty<GeoTexCoords1fPropertyDesc>::addValue( const Vec2f & val )
{
    _field.push_back(val[0]);
}



// TexCoords3f

template<> inline 
Vec2f GeoProperty<GeoTexCoords3fPropertyDesc>::getValue(const UInt32 index)
{
    return Vec2f(_field[index][0], _field[index][1]);
}

template<> inline 
Vec2f GeoProperty<GeoTexCoords3fPropertyDesc>::getValue(
    const UInt32 index) const
{
    return Vec2f(_field[index][0], _field[index][1]);
}

template<> inline 
void GeoProperty<GeoTexCoords3fPropertyDesc>::getValue(
          Vec2f  &res,
    const UInt32  index)
{
    res.setValues(_field[index][0], _field[index][1]);
}

template<> inline 
void GeoProperty<GeoTexCoords3fPropertyDesc>::getValue(
          Vec2f  &res,
    const UInt32  index) const
{
    res.setValues(_field[index][0], 
                  _field[index][1]);
}

template<>
inline void
GeoProperty<GeoTexCoords3fPropertyDesc>::setValue( const Vec2f & val,
    const UInt32 index )
{
    _field[index].setValues(val[0], val[1], 0.f);
}

template<>
inline void
GeoProperty<GeoTexCoords3fPropertyDesc>::addValue( const Vec2f & val )
{
    _field.push_back(Vec3f( val[0], val[1], 0));
}

OSG_END_NAMESPACE
