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

inline float glShortToFloat(GLshort b)
{
    return (2.0f * b + 1.0f) / 65535.0f;
}

inline GLshort glFloatToShort(float f)
{
    // Round?
    return GLshort((f * 65535.0 - 1.0f) / 2.0f);
}

inline Vec3f glShortVecToFloatVec(const Vec3s& v)
{
    return Vec3f(
        glShortToFloat(v[0]),
        glShortToFloat(v[1]),
        glShortToFloat(v[2]));
}

inline Vec3s glFloatVecToShortVec(const Vec3f& v)
{
    return Vec3s(
        glFloatToShort(v[0]),
        glFloatToShort(v[1]),
        glFloatToShort(v[2]));
}

template<> inline
Vec3f GeoProperty<GeoNormals3sPropertyDesc>::getValue(const UInt32 index)
{
    return glShortVecToFloatVec(_field[index]);
}

template<> inline
Vec3f GeoProperty<GeoNormals3sPropertyDesc>::getValue(
    const UInt32 index) const
{
    return glShortVecToFloatVec(_field[index]);
}

template<> inline 
void GeoProperty<GeoNormals3sPropertyDesc>::getValue(
          Vec3f  &res,
    const UInt32  index)
{
    res.setValues(glShortToFloat(_field[index][0]),
                  glShortToFloat(_field[index][1]),
                  glShortToFloat(_field[index][2]));
}

template<> inline 
void GeoProperty<GeoNormals3sPropertyDesc>::getValue(
          Vec3f  &res,
    const UInt32  index) const
{
    res.setValues(glShortToFloat(_field[index][0]),
                  glShortToFloat(_field[index][1]),
                  glShortToFloat(_field[index][2]));
}

template<>
inline void
GeoProperty<GeoNormals3sPropertyDesc>::setValue( const Vec3f & val,
    const UInt32 index )
{
    _field[index].setValues(glFloatToShort(val[0]), 
                            glFloatToShort(val[1]), 
                            glFloatToShort(val[2]));
}

template<>
inline void
GeoProperty<GeoNormals3sPropertyDesc>::addValue( const Vec3f & val )
{
    _field.push_back(glFloatVecToShortVec(val));
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
        _field.insert(_field.begin() + index, glFloatVecToShortVec(val));
        return true;
    }
}

// Normals3b

inline float glByteToFloat(GLbyte b)
{
    return (2.0f * b + 1.0f) / 255.0f;
}

inline GLbyte glFloatToByte(float f)
{
    // Round?
    return GLbyte((f * 255.0 - 1.0f) / 2.0f);
}

#ifndef OSG_NO_INT8_PNT
inline Vec3f glByteVecToFloatVec(const Vec3b& v)
{
    return Vec3f(
        glByteToFloat(v[0]),
        glByteToFloat(v[1]),
        glByteToFloat(v[2]));
}

inline Vec3b glFloatVecToByteVec(const Vec3f& v)
{
    return Vec3b(
        glFloatToByte(v[0]),
        glFloatToByte(v[1]),
        glFloatToByte(v[2]));
}

template<> inline
Vec3f GeoProperty<GeoNormals3bPropertyDesc>::getValue(const UInt32 index)
{
    return glByteVecToFloatVec(_field[index]);
}

template<> inline
Vec3f GeoProperty<GeoNormals3bPropertyDesc>::getValue(
    const UInt32 index) const
{
    return glByteVecToFloatVec(_field[index]);
}

template<> inline 
void GeoProperty<GeoNormals3bPropertyDesc>::getValue(
          Vec3f  &res,
    const UInt32  index)
{
    res.setValues(glByteToFloat(_field[index][0]),
                  glByteToFloat(_field[index][1]),
                  glByteToFloat(_field[index][2]));
}

template<> inline 
void GeoProperty<GeoNormals3bPropertyDesc>::getValue(
          Vec3f  &res,
    const UInt32  index) const
{
    res.setValues(glByteToFloat(_field[index][0]),
                  glByteToFloat(_field[index][1]),
                  glByteToFloat(_field[index][2]));
}

template<>
inline void
GeoProperty<GeoNormals3bPropertyDesc>::setValue( const Vec3f & val,
    const UInt32 index )
{
    _field[index].setValues(glFloatToByte(val[0]),
                            glFloatToByte(val[1]),
                            glFloatToByte(val[2]));
}

template<>
inline void
GeoProperty<GeoNormals3bPropertyDesc>::addValue( const Vec3f & val )
{
    _field.push_back(glFloatVecToByteVec(val));
}

template <> inline
bool GeoProperty<GeoNormals3bPropertyDesc>::insertValue(const Vec3f & val,
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
        _field.insert(_field.begin() + index, glFloatVecToByteVec(val));
        return true;
    }
}
#endif

OSG_END_NAMESPACE
