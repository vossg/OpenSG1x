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

#ifndef DOXYGEN_SHOULD_SKIP_THIS

// Positions2s

template<> inline 
Pnt3f GeoProperty<GeoPositions2sPropertyDesc>::getValue(const UInt32 index)
{
    return Pnt3f(_field[index][0], _field[index][1], 0);
}

template<> inline 
Pnt3f GeoProperty<GeoPositions2sPropertyDesc>::getValue( 
    const UInt32 index) const
{
    return Pnt3f(_field[index][0], _field[index][1], 0);
}

template<> inline 
void GeoProperty<GeoPositions2sPropertyDesc>::getValue(
          Pnt3f   &res,
    const UInt32   index)
{
    res.setValues(_field[index][0], _field[index][1], 0);
}

template<> inline 
void GeoProperty<GeoPositions2sPropertyDesc>::getValue(
          Pnt3f  &res,
    const UInt32  index) const
{
    res.setValues(_field[index][0], _field[index][1], 0);
}

template<> inline 
void GeoProperty<GeoPositions2sPropertyDesc>::setValue(const Pnt3f  &val,
                                                       const UInt32  index)
{
    _field[index].setValues(Int16(val[0]), Int16(val[1]));
}

template<>
inline
void GeoProperty<GeoPositions2sPropertyDesc>::addValue(const Pnt3f &val)
{
    _field.push_back(Pnt2s(Int16(val[0]), Int16(val[1])));
}

template <> inline
bool GeoProperty<GeoPositions2sPropertyDesc>::insertValue(const Pnt3f &val,
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
        _field.insert(_field.begin() + index, Pnt2s(Int16(val[0]), 
                                                    Int16(val[1])));
        return true;
    }
}

// Positions3s

template<> inline 
Pnt3f GeoProperty<GeoPositions3sPropertyDesc>::getValue(const UInt32 index)
{
    return Pnt3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
Pnt3f GeoProperty<GeoPositions3sPropertyDesc>::getValue( 
    const UInt32 index) const
{
    return Pnt3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void GeoProperty<GeoPositions3sPropertyDesc>::getValue(
          Pnt3f   &res,
    const UInt32   index)
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void GeoProperty<GeoPositions3sPropertyDesc>::getValue(
          Pnt3f  &res,
    const UInt32  index) const
{
    res.setValues(Int16(_field[index][0]),
                  Int16(_field[index][1]), 
                  Int16(_field[index][2]));
}

template<> inline 
void GeoProperty<GeoPositions3sPropertyDesc>::setValue(const Pnt3f  &val,
                                                       const UInt32  index)
{
    _field[index].setValues(Int16(val[0]), Int16(val[1]), Int16(val[2]));
}

template<>
inline
void GeoProperty<GeoPositions3sPropertyDesc>::addValue(const Pnt3f &val)
{
    _field.push_back(Pnt3s(Int16(val[0]), Int16(val[1]), Int16(val[2])));
}

template <> inline
bool GeoProperty<GeoPositions3sPropertyDesc>::insertValue(const Pnt3f &val,
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
        _field.insert(_field.begin() + index, 
                      Pnt3s(Int16(val[0]), Int16(val[1]), Int16(val[2])));
        return true;
    }
}

// Positions4s

template<> inline 
Pnt3f GeoProperty<GeoPositions4sPropertyDesc>::getValue(const UInt32 index)
{
    return Pnt3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
Pnt3f GeoProperty<GeoPositions4sPropertyDesc>::getValue( 
    const UInt32 index) const
{
    return Pnt3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void GeoProperty<GeoPositions4sPropertyDesc>::getValue(
          Pnt3f   &res,
    const UInt32   index)
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void GeoProperty<GeoPositions4sPropertyDesc>::getValue(
          Pnt3f  &res,
    const UInt32  index) const
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void GeoProperty<GeoPositions4sPropertyDesc>::setValue(const Pnt3f  &val,
                                                       const UInt32  index)
{
    _field[index].setValues(Int16(val[0]), Int16(val[1]), Int16(val[2]), 1);
}

template<>
inline
void GeoProperty<GeoPositions4sPropertyDesc>::addValue(const Pnt3f &val)
{
    _field.push_back(Pnt4s(Int16(val[0]), Int16(val[1]), Int16(val[2]), 1));
}

template <> inline
bool GeoProperty<GeoPositions4sPropertyDesc>::insertValue(const Pnt3f &val,
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
        _field.insert(_field.begin() + index, 
                      Pnt4s(Int16(val[0]), Int16(val[1]), Int16(val[2]) ,1));
        return true;
    }
}



// Positions2f

template<> inline 
Pnt3f GeoProperty<GeoPositions2fPropertyDesc>::getValue(const UInt32 index)
{
    return Pnt3f(_field[index][0], _field[index][1], 0);
}

template<> inline 
Pnt3f GeoProperty<GeoPositions2fPropertyDesc>::getValue( 
    const UInt32 index) const
{
    return Pnt3f(_field[index][0], _field[index][1], 0);
}

template<> inline 
void GeoProperty<GeoPositions2fPropertyDesc>::getValue(
          Pnt3f   &res,
    const UInt32   index)
{
    res.setValues(_field[index][0], _field[index][1], 0);
}

template<> inline 
void GeoProperty<GeoPositions2fPropertyDesc>::getValue(
          Pnt3f  &res,
    const UInt32  index) const
{
    res.setValues(_field[index][0], _field[index][1], 0);
}

template<> inline 
void GeoProperty<GeoPositions2fPropertyDesc>::setValue(const Pnt3f  &val,
                                                       const UInt32  index)
{
    _field[index].setValues(val[0], val[1]);
}

template<>
inline
void GeoProperty<GeoPositions2fPropertyDesc>::addValue(const Pnt3f &val)
{
    _field.push_back(Pnt2f( val[0], val[1]));
}

template <> inline
bool GeoProperty<GeoPositions2fPropertyDesc>::insertValue(const Pnt3f &val,
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
        _field.insert(_field.begin() + index, Pnt2f(val[0], val[1]));
        return true;
    }
}

// Positions4f

template<> inline 
Pnt3f GeoProperty<GeoPositions4fPropertyDesc>::getValue(const UInt32 index)
{
    return Pnt3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
Pnt3f GeoProperty<GeoPositions4fPropertyDesc>::getValue( 
    const UInt32 index) const
{
    return Pnt3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void GeoProperty<GeoPositions4fPropertyDesc>::getValue(
          Pnt3f   &res,
    const UInt32   index)
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void GeoProperty<GeoPositions4fPropertyDesc>::getValue(
          Pnt3f  &res,
    const UInt32  index) const
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void GeoProperty<GeoPositions4fPropertyDesc>::setValue(const Pnt3f  &val,
                                                       const UInt32  index)
{
    _field[index].setValues(val[0], val[1], val[2], 1);
}

template<>
inline
void GeoProperty<GeoPositions4fPropertyDesc>::addValue(const Pnt3f &val)
{
    _field.push_back(Pnt4f( val[0], val[1], val[2], 1));
}

template <> inline
bool GeoProperty<GeoPositions4fPropertyDesc>::insertValue(const Pnt3f &val,
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
        _field.insert(_field.begin() + index, Pnt4f(val[0],val[1],val[2],1));
        return true;
    }
}



// Positions2d

template<> inline 
Pnt3f GeoProperty<GeoPositions2dPropertyDesc>::getValue(const UInt32 index)
{
    return Pnt3f(Real32(_field[index][0]),
                 Real32(_field[index][1]), 
                 0.f);
}

template<> inline 
Pnt3f GeoProperty<GeoPositions2dPropertyDesc>::getValue( 
    const UInt32 index) const
{
    return Pnt3f(Real32(_field[index][0]), 
                 Real32(_field[index][1]), 
                 0.f);
}

template<> inline 
void GeoProperty<GeoPositions2dPropertyDesc>::getValue(
          Pnt3f   &res,
    const UInt32   index)
{
    res.setValues(Real32(_field[index][0]),
                  Real32(_field[index][1]),
                  0.f);
}

template<> inline 
void GeoProperty<GeoPositions2dPropertyDesc>::getValue(
          Pnt3f  &res,
    const UInt32  index) const
{
    res.setValues(Real32(_field[index][0]), 
                  Real32(_field[index][1]), 
                  0.f);
}

template<> inline 
void GeoProperty<GeoPositions2dPropertyDesc>::setValue(const Pnt3f  &val,
                                                       const UInt32  index)
{
    _field[index].setValues(val[0], val[1]);
}

template<>
inline
void GeoProperty<GeoPositions2dPropertyDesc>::addValue(const Pnt3f &val)
{
    _field.push_back(Pnt2d( val[0], val[1]));
}

template <> inline
bool GeoProperty<GeoPositions2dPropertyDesc>::insertValue(const Pnt3f &val,
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
        _field.insert(_field.begin() + index, Pnt2d(val[0], val[1]));
        return true;
    }
}

// Positions3d

template<> inline 
Pnt3f GeoProperty<GeoPositions3dPropertyDesc>::getValue(const UInt32 index)
{
    return Pnt3f(Real32(_field[index][0]),
                 Real32(_field[index][1]), 
                 Real32(_field[index][2]));
}

template<> inline 
Pnt3f GeoProperty<GeoPositions3dPropertyDesc>::getValue( 
    const UInt32 index) const
{
    return Pnt3f(Real32(_field[index][0]), 
                 Real32(_field[index][1]), 
                 Real32(_field[index][2]));
}

template<> inline 
void GeoProperty<GeoPositions3dPropertyDesc>::getValue(
          Pnt3f   &res,
    const UInt32   index)
{
    res.setValues(Real32(_field[index][0]), 
                  Real32(_field[index][1]), 
                  Real32(_field[index][2]));
}

template<> inline 
void GeoProperty<GeoPositions3dPropertyDesc>::getValue(
          Pnt3f  &res,
    const UInt32  index) const
{
    res.setValues(Real32(_field[index][0]),
                  Real32(_field[index][1]), 
                  Real32(_field[index][2]));
}

template<> inline 
void GeoProperty<GeoPositions3dPropertyDesc>::setValue(const Pnt3f  &val,
                                                       const UInt32  index)
{
    _field[index].setValues(val[0], val[1], val[2]);
}

template<>
inline
void GeoProperty<GeoPositions3dPropertyDesc>::addValue(const Pnt3f &val)
{
    _field.push_back(Pnt3d( val[0], val[1], val[2]));
}

template <> inline
bool GeoProperty<GeoPositions3dPropertyDesc>::insertValue(const Pnt3f &val,
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
        _field.insert(_field.begin() + index, Pnt3d(val[0], val[1], val[2]));
        return true;
    }
}

// Positions4d

template<> inline 
Pnt3f GeoProperty<GeoPositions4dPropertyDesc>::getValue(const UInt32 index)
{
    return Pnt3f(Real32(_field[index][0]),
                 Real32(_field[index][1]),
                 Real32(_field[index][2]));
}

template<> inline 
Pnt3f GeoProperty<GeoPositions4dPropertyDesc>::getValue( 
    const UInt32 index) const
{
    return Pnt3f(Real32(_field[index][0]),
                 Real32(_field[index][1]),
                 Real32(_field[index][2]));
}

template<> inline 
void GeoProperty<GeoPositions4dPropertyDesc>::getValue(
          Pnt3f   &res,
    const UInt32   index)
{
    res.setValues(Real32(_field[index][0]), 
                  Real32(_field[index][1]), 
                  Real32(_field[index][2]));
}

template<> inline 
void GeoProperty<GeoPositions4dPropertyDesc>::getValue(
          Pnt3f  &res,
    const UInt32  index) const
{
    res.setValues(Real32(_field[index][0]), 
                  Real32(_field[index][1]),
                  Real32(_field[index][2]));
}

template<> inline 
void GeoProperty<GeoPositions4dPropertyDesc>::setValue(const Pnt3f  &val,
                                                       const UInt32  index)
{
    _field[index].setValues(val[0], val[1], val[2], 1);
}

template<>
inline
void GeoProperty<GeoPositions4dPropertyDesc>::addValue(const Pnt3f &val)
{
    _field.push_back(Pnt4d( val[0], val[1], val[2], 1));
}

template <> inline
bool GeoProperty<GeoPositions4dPropertyDesc>::insertValue(const Pnt3f &val,
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
        _field.insert(_field.begin() + index, Pnt4d(val[0],val[1],val[2],1));
        return true;
    }
}



#endif /* DOXYGEN_SHOULD_SKIP_THIS */

OSG_END_NAMESPACE


