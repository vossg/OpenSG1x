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

// Color4f

template<> inline 
Color3f GeoProperty<GeoColors4fPropertyDesc>::getValue(const UInt32 index)
{
    return Color3f(_field[index].red  (), 
                   _field[index].green(),
                   _field[index].blue ());
}

template<> inline 
Color3f GeoProperty<GeoColors4fPropertyDesc>::getValue( 
    const UInt32 index) const
{
    return Color3f(_field[index].red  (), 
                   _field[index].green(), 
                   _field[index].blue ());
}

template<> inline
void GeoProperty<GeoColors4fPropertyDesc>::getValue(
          Color3f &res,
    const UInt32   index)
{
    res.setValuesRGB(_field[index].red  (), 
                     _field[index].green(), 
                     _field[index].blue ());
}


template<> inline 
void GeoProperty<GeoColors4fPropertyDesc>::getValue(
          Color3f &res,
    const UInt32   index) const
{
    res.setValuesRGB(_field[index].red  (), 
                     _field[index].green(), 
                     _field[index].blue ());
}


template<> inline 
void GeoProperty<GeoColors4fPropertyDesc>::setValue(const Color3f &val,
                                                    const UInt32   index)
{
    _field[index].setValuesRGBA(val.red(), val.green(), val.blue (), 1.f);
}


template<> inline 
void GeoProperty<GeoColors4fPropertyDesc>::addValue(const Color3f &val)
{
    _field.push_back(Color4f(val.red(), val.green(), val.blue (), 1.f));
}

template <> inline
bool GeoProperty<GeoColors4fPropertyDesc>::insertValue(const Color3f &val,
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
                      Color4f(val.red(), val.green(), val.blue (), 1.f));
        return true;
    }
}


// Color3ub

template<> inline
Color3f GeoProperty<GeoColors3ubPropertyDesc>::getValue(const UInt32 index)
{
    return Color3f(_field[index].red  () / 255.f,
                   _field[index].green() / 255.f,
                   _field[index].blue () / 255.f);
}

template<> inline
Color3f GeoProperty<GeoColors3ubPropertyDesc>::getValue(
    const UInt32 index) const
{
    return Color3f(_field[index].red  () / 255.f,
                   _field[index].green() / 255.f,
                   _field[index].blue () / 255.f);
}

template<> inline
void GeoProperty<GeoColors3ubPropertyDesc>::getValue(
          Color3f &res,
    const UInt32   index)
{
    res.setValuesRGB(_field[index].red  () / 255.f,
                     _field[index].green() / 255.f,
                     _field[index].blue () / 255.f);
}

template<> inline
void GeoProperty<GeoColors3ubPropertyDesc>::getValue(
          Color3f &res,
    const UInt32   index) const
{
    res.setValuesRGB(_field[index].red  () / 255.f,
                     _field[index].green() / 255.f,
                     _field[index].blue () / 255.f);
}

template<> inline
void GeoProperty<GeoColors3ubPropertyDesc>::setValue(const Color3f &val,
                                                     const UInt32   index)
{
    _field[index].setValuesRGB(UInt8(val.red  () * 255.f),
                               UInt8(val.green() * 255.f),
                               UInt8(val.blue () * 255.f));
}

template<> inline
void GeoProperty<GeoColors3ubPropertyDesc>::addValue(const Color3f &val)
{
    _field.push_back(Color3ub(UInt8(val.red  () * 255.f),
                              UInt8(val.green() * 255.f),
                              UInt8(val.blue () * 255.f)));
}

template <> inline
bool GeoProperty<GeoColors3ubPropertyDesc>::insertValue(const Color3f &val,
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
                      Color3ub(UInt8(val.red  () * 255.f),
                               UInt8(val.green() * 255.f),
                               UInt8(val.blue () * 255.f)));
        return true;
    }
}


// Color4ub

template<> inline
Color3f GeoProperty<GeoColors4ubPropertyDesc>::getValue(const UInt32 index)
{
    return Color3f(_field[index].red  () / 255.f,
                   _field[index].green() / 255.f,
                   _field[index].blue () / 255.f);
}

template<> inline
Color3f GeoProperty<GeoColors4ubPropertyDesc>::getValue(
    const UInt32 index) const
{
    return Color3f(_field[index].red  () / 255.f, 
                   _field[index].green() / 255.f,
                   _field[index].blue () / 255.f);
}

template<> inline 
void GeoProperty<GeoColors4ubPropertyDesc>::getValue(
          Color3f &res,
    const UInt32   index)
{
    res.setValuesRGB(_field[index].red  () / 255.f, 
                     _field[index].green() / 255.f, 
                     _field[index].blue () / 255.f);
}

template<> inline 
void GeoProperty<GeoColors4ubPropertyDesc>::getValue(
          Color3f &res,
    const UInt32   index) const
{
    res.setValuesRGB(_field[index].red  () / 255.f, 
                     _field[index].green() / 255.f, 
                     _field[index].blue () / 255.f);
}

template<> inline 
void GeoProperty<GeoColors4ubPropertyDesc>::setValue(const Color3f &val,
                                                     const UInt32   index)
{
    _field[index].setValuesRGBA(UInt8(val.red  () * 255.f),
                                UInt8(val.green() * 255.f),
                                UInt8(val.blue () * 255.f),
                                                    255  );
}

template<> inline 
void GeoProperty<GeoColors4ubPropertyDesc>::addValue(const Color3f &val)
{
    _field.push_back(Color4ub(UInt8(val.red  () * 255.f),
                              UInt8(val.green() * 255.f),
                              UInt8(val.blue () * 255.f),
                                                  255  ));
}

template <> inline
bool GeoProperty<GeoColors4ubPropertyDesc>::insertValue(const Color3f &val,
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
        _field.insert(_field.begin() + index, Color4ub(UInt8(val.red  () * 255.f),
                                                       UInt8(val.green() * 255.f),
                                                       UInt8(val.blue () * 255.f),
                                                                           255  ));
        return true;
    }
}

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

OSG_END_NAMESPACE
