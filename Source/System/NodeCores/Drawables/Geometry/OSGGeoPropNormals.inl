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


// Normals3s

template<> inline
Vec3f GeoProperty<GeoNormals3sPropertyDesc>::getValue(const UInt32 index)
{
    return Vec3f(_field[index][0] / 32767.f, 
                 _field[index][1] / 32767.f, 
                 _field[index][2] / 32767.f);
}

template<> inline
Vec3f GeoProperty<GeoNormals3sPropertyDesc>::getValue(
    const UInt32 index) const
{
    return Vec3f(_field[index][0] / 32767.f, 
                 _field[index][1] / 32767.f, 
                 _field[index][2] / 32767.f);
}

template<> inline 
void GeoProperty<GeoNormals3sPropertyDesc>::getValue(
          Vec3f  &res,
    const UInt32  index)
{
    res.setValues(_field[index][0] / 32767.f, 
                  _field[index][1] / 32767.f, 
                  _field[index][2] / 32767.f);
}

template<> inline 
void GeoProperty<GeoNormals3sPropertyDesc>::getValue(
          Vec3f  &res,
    const UInt32  index) const
{
    res.setValues(_field[index][0] / 32767.f, 
                  _field[index][1] / 32767.f, 
                  _field[index][2] / 32767.f);
}

template<>
inline void
GeoProperty<GeoNormals3sPropertyDesc>::setValue( const Vec3f & val,
    const UInt32 index )
{
    _field[index].setValues(Int16(val[0] * 32767.f), 
                            Int16(val[1] * 32767.f), 
                            Int16(val[2] * 32767.f));
}

template<>
inline void
GeoProperty<GeoNormals3sPropertyDesc>::addValue( const Vec3f & val )
{
    _field.push_back(Vec3s(Int16(val[0] * 32767.f), 
                           Int16(val[1] * 32767.f), 
                           Int16(val[2] * 32767.f)));
}

template <> inline
bool GeoProperty<GeoNormals3sPropertyDesc>::insertValue(const Vec3f & val,
                                                          const UInt32 index)
{
    if(_field.size() < index)
    {
        return false;
    }
    else if(_field.size() == index)
    {
        addValue(val);
        return true;
    }
    else
    {
        _field.insert(_field.begin() + index, Vec3s(Int16(val[0] * 32767.f), 
                                                    Int16(val[1] * 32767.f), 
                                                    Int16(val[2] * 32767.f)));
        return true;
    }
}

OSG_END_NAMESPACE
