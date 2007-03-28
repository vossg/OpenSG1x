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

#include <stdlib.h>
#include <assert.h>

#ifndef WIN32
#include <unistd.h>
#endif

#include "OSGVector.h"

OSG_BEGIN_NAMESPACE

template <class ValueTypeT>
const Color3<ValueTypeT> Color3<ValueTypeT>::Null;


template <class ValueTypeT> inline
void Color3<ValueTypeT>::convertFromHSV(      ValueType *rgbP,
                                        const Real32     h,
                                        const Real32     s,
                                        const Real32     v)
{
    if(rgbP == NULL)
        return;

    Int32  i;
    Real32 f;
    Real32 p;
    Real32 q;
    Real32 t;

    if(s)
    {
        f = (h == 360) ? 0.0 : (h / 60.0);
        i = Int32(f);

        f = f - Real32(i);

        p = v * (1.0 -  s           );
        q = v * (1.0 - (s *      f) );
        t = v * (1.0 - (s * (1 - f)));

        switch (i)
        {
            case 0:
                rgbP[0] = TypeTraits<ValueTypeT>::getPortion(v);
                rgbP[1] = TypeTraits<ValueTypeT>::getPortion(t);
                rgbP[2] = TypeTraits<ValueTypeT>::getPortion(p);
                break;
            case 1:
                rgbP[0] = TypeTraits<ValueTypeT>::getPortion(q);
                rgbP[1] = TypeTraits<ValueTypeT>::getPortion(v);
                rgbP[2] = TypeTraits<ValueTypeT>::getPortion(p);
                break;
            case 2:
                rgbP[0] = TypeTraits<ValueTypeT>::getPortion(p);
                rgbP[1] = TypeTraits<ValueTypeT>::getPortion(v);
                rgbP[2] = TypeTraits<ValueTypeT>::getPortion(t);
                break;
            case 3:
                rgbP[0] = TypeTraits<ValueTypeT>::getPortion(p);
                rgbP[1] = TypeTraits<ValueTypeT>::getPortion(q);
                rgbP[2] = TypeTraits<ValueTypeT>::getPortion(v);
                break;
            case 4:
                rgbP[0] = TypeTraits<ValueTypeT>::getPortion(t);
                rgbP[1] = TypeTraits<ValueTypeT>::getPortion(p);
                rgbP[2] = TypeTraits<ValueTypeT>::getPortion(v);
                break;
            case 5:
                rgbP[0] = TypeTraits<ValueTypeT>::getPortion(v);
                rgbP[1] = TypeTraits<ValueTypeT>::getPortion(p);
                rgbP[2] = TypeTraits<ValueTypeT>::getPortion(q);
                break;
            default:
                std::cerr << "ERROR i not in [0, 5] in Color::setHSV()!"
                     << std::endl;
                break;
        }
    }
    else
    {
        rgbP[0] = rgbP[1] = rgbP[2] =
            TypeTraits<ValueTypeT>::getPortion(v);
    }
}


template <class ValueTypeT> inline
void Color3<ValueTypeT>::convertToHSV(const ValueType *rgbP,
                                            Real32    &h,
                                            Real32    &s,
                                            Real32    &v)
{
    if(rgbP == NULL)
        return;

    const Real32 r        = TypeTraits<ValueTypeT>::getFraction(rgbP[0]);
    const Real32 g        = TypeTraits<ValueTypeT>::getFraction(rgbP[1]);
    const Real32 b        = TypeTraits<ValueTypeT>::getFraction(rgbP[2]);

    const Int32  maxIndex = maxPart(rgbP);
    const Int32  minIndex = minPart(rgbP);

    const Real32 max      = TypeTraits<ValueTypeT>::getFraction(
        rgbP[maxIndex]);

    const Real32 min      = TypeTraits<ValueTypeT>::getFraction(
        rgbP[minIndex]);

    const Real32 delta    = max - min;

    v = max;
    s = max ? (max - min) / max : 0.0;

    if(s)
    {
        switch(maxIndex)
        {
            case 0: // red part is max;
                h = (( g - b) / delta) * 60.0;
                break;
            case 1: // green part is max;
                h = (2.0 + (( b - r) / delta)) * 60.0;
                break;
            case 2: // blue part is max
                h = (4.0 + (( r - g) / delta)) * 60.0;
                break;
        }

        if(h < 0.0)
            h += 360.0;
    }
    else
    {
        h = 0.0;
    }
}


template <class ValueTypeT> inline
UInt32 Color3<ValueTypeT>::maxPart(const ValueType *rgbP)
{
    if(rgbP[0] > rgbP[1])
    {
        if(rgbP[2] > rgbP[0])
        {
            return 2;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if (rgbP[2] > rgbP[1])
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }
}


template <class ValueTypeT> inline
UInt32 Color3<ValueTypeT>::minPart(const ValueType *rgbP)
{
    if(rgbP[0] < rgbP[1])
    {
        if(rgbP[2] < rgbP[0])
        {
            return 2;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if(rgbP[2] < rgbP[1])
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }
}


template <class ValueTypeT> inline
Color3<ValueTypeT>::Color3(void)
{
    _rgb[0] = TypeTraits<ValueTypeT>::getZeroElement();
    _rgb[1] = TypeTraits<ValueTypeT>::getZeroElement();
    _rgb[2] = TypeTraits<ValueTypeT>::getZeroElement();
}


template <class ValueTypeT> inline
Color3<ValueTypeT>::Color3(const Color3 &source)
{
    _rgb[0] = source._rgb[0];
    _rgb[1] = source._rgb[1];
    _rgb[2] = source._rgb[2];
}


template <class ValueTypeT> inline
Color3<ValueTypeT>::Color3(ValueType r,
                           ValueType g,
                           ValueType b)
{
    _rgb[0] = r;
    _rgb[1] = g;
    _rgb[2] = b;
}


template <class ValueTypeT> inline
Color3<ValueTypeT>::~Color3(void)
{
}


template <class ValueTypeT> inline
void Color3<ValueTypeT>::clear(void)
{
    _rgb[0] = TypeTraits<ValueTypeT>::getZeroElement();
    _rgb[1] = TypeTraits<ValueTypeT>::getZeroElement();
    _rgb[2] = TypeTraits<ValueTypeT>::getZeroElement();
}


template <class ValueTypeT> inline
void Color3<ValueTypeT>::setValuesRGB(const ValueType red,
                                      const ValueType green,
                                      const ValueType blue)
{
    _rgb[0] = red;
    _rgb[1] = green;
    _rgb[2] = blue;
}


template <class ValueTypeT> inline
void Color3<ValueTypeT>::setValuesHSV(const Real32 h,
                                      const Real32 s,
                                      const Real32 v)
{
    convertFromHSV(_rgb, h, s, v);
}


template <class ValueTypeT> inline
void Color3<ValueTypeT>::setRandom(void)
{
    Real32 rf = 1.0 / Real32(RAND_MAX);

    setValuesRGB(TypeTraits<ValueTypeT>::getPortion(rf * rand()),
                 TypeTraits<ValueTypeT>::getPortion(rf * rand()),
                 TypeTraits<ValueTypeT>::getPortion(rf * rand()));
}

/*! method to set the rgb values (BBGGRR)
 */

template <class ValueTypeT> inline
void Color3<ValueTypeT>::setRGB(UInt32 rgbPack)
{
    for(Int32 i = 0; i < 3; ++i)
    {
        Real32 rTmp = Real32(rgbPack & 255) / 255.0f;

        _rgb[i] = TypeTraits<ValueTypeT>::getPortion(rTmp);

        rgbPack >>= 8;
    }
}


template <class ValueTypeT> inline
void Color3<ValueTypeT>::setValue(const Char8 *szString)
{
    // this is the easiest way, not the most efficient...

    Vec3f v;

    v.setValueFromCString(szString);

    _rgb[0] = ValueTypeT(v[0]);
    _rgb[1] = ValueTypeT(v[1]);
    _rgb[2] = ValueTypeT(v[2]);
}


template <class ValueTypeT> inline
void Color3<ValueTypeT>::setValue(Char8 *szString)
{
    setValue(static_cast<const Char8 *>(szString));
}


/*! method to get a packed rgb value (BBGGRR)
 */

template <class ValueTypeT> inline
UInt32 Color3<ValueTypeT>::getRGB(void) const
{
    UInt32 pack = 0;

    for(Int32 i = 2; i >= 0; --i)
    {
        pack = (pack << 8) | 
            Int32(TypeTraits<ValueTypeT>::getFraction(_rgb[i]) *
                  255.0f                                          +
                  0.5f                                            );
    }

    return pack;
}


template <class ValueTypeT> inline
void Color3<ValueTypeT>::getValuesRGB(ValueType &red,
                                      ValueType &green,
                                      ValueType &blue) const
{
    red   = _rgb[0];
    green = _rgb[1];
    blue  = _rgb[2];
}


template <class ValueTypeT> inline
void Color3<ValueTypeT>::getValuesHSV(Real32 &h,
                                      Real32 &s,
                                      Real32 &v) const
{
    convertToHSV(_rgb, h, s, v);
}


template <class ValueTypeT> inline
typename Color3<ValueTypeT>::ValueType
    Color3<ValueTypeT>::red(void) const
{
    return _rgb[0];
}

template <class ValueTypeT> inline
typename Color3<ValueTypeT>::ValueType
    Color3<ValueTypeT>::green(void) const
{
    return _rgb[1];
}

template <class ValueTypeT> inline
typename Color3<ValueTypeT>::ValueType
    Color3<ValueTypeT>::blue(void) const
{
    return _rgb[2];
}


template <class ValueTypeT> inline
typename Color3<ValueTypeT>::ValueType *
    Color3<ValueTypeT>::getValuesRGB(void)
{
    return _rgb;
}

template <class ValueTypeT> inline
const typename Color3<ValueTypeT>::ValueType *
    Color3<ValueTypeT>::getValuesRGB(void) const
{
    return _rgb;
}


template <class ValueTypeT> inline
Color3<ValueTypeT> Color3<ValueTypeT>::operator *(const ValueType val)
{
    Color3<ValueTypeT> returnValue;

    returnValue._rgb[0] = _rgb[0] * val;
    returnValue._rgb[1] = _rgb[1] * val;
    returnValue._rgb[2] = _rgb[2] * val;

    return returnValue;
}

template <class ValueTypeT> inline
Color3<ValueTypeT> Color3<ValueTypeT>::operator /(const ValueType val)
{
    Color3<ValueTypeT> returnValue;

    returnValue._rgb[0] = _rgb[0] / val;
    returnValue._rgb[1] = _rgb[1] / val;
    returnValue._rgb[2] = _rgb[2] / val;

    return returnValue;
}

template <class ValueTypeT> inline
Color3<ValueTypeT> Color3<ValueTypeT>::operator +(const ValueType val)
{
    Color3<ValueTypeT> returnValue;

    returnValue._rgb[0] = _rgb[0] + val;
    returnValue._rgb[1] = _rgb[1] + val;
    returnValue._rgb[2] = _rgb[2] + val;

    return returnValue;
}

template <class ValueTypeT> inline
Color3<ValueTypeT> Color3<ValueTypeT>::operator -(const ValueType val)
{
    Color3<ValueTypeT> returnValue;

    returnValue._rgb[0] = _rgb[0] - val;
    returnValue._rgb[1] = _rgb[1] - val;
    returnValue._rgb[2] = _rgb[2] - val;

    return returnValue;
}

template <class ValueTypeT> inline
void Color3<ValueTypeT>::operator *=(const ValueType val)
{
    _rgb[0] *= val;
    _rgb[1] *= val;
    _rgb[2] *= val;
}

template <class ValueTypeT> inline
void Color3<ValueTypeT>::operator /=(const ValueType val)
{
    _rgb[0] /= val;
    _rgb[1] /= val;
    _rgb[2] /= val;
}

template <class ValueTypeT> inline
void Color3<ValueTypeT>::operator +=(const ValueType val)
{
    _rgb[0] += val;
    _rgb[1] += val;
    _rgb[2] += val;
}

template <class ValueTypeT> inline
void Color3<ValueTypeT>::operator -=(const ValueType val)
{
    _rgb[0] -= val;
    _rgb[1] -= val;
    _rgb[2] -= val;
}

template <class ValueTypeT> inline
Color3<ValueTypeT> Color3<ValueTypeT>::operator *(const Color3<ValueTypeT> &other) const
{
    Color3<ValueTypeT> returnValue;

    returnValue._rgb[0] = _rgb[0] * other._rgb[0];
    returnValue._rgb[1] = _rgb[1] * other._rgb[1];
    returnValue._rgb[2] = _rgb[2] * other._rgb[2];

    return returnValue;
}

template <class ValueTypeT> inline
Color3<ValueTypeT> Color3<ValueTypeT>::operator /(const Color3<ValueTypeT> &other) const
{
    Color3<ValueTypeT> returnValue;

    returnValue._rgb[0] = _rgb[0] / other._rgb[0];
    returnValue._rgb[1] = _rgb[1] / other._rgb[1];
    returnValue._rgb[2] = _rgb[2] / other._rgb[2];

    return returnValue;
}

template <class ValueTypeT> inline
Color3<ValueTypeT> Color3<ValueTypeT>::operator +(const Color3<ValueTypeT> &other) const
{
    Color3<ValueTypeT> returnValue;

    returnValue._rgb[0] = _rgb[0] + other._rgb[0];
    returnValue._rgb[1] = _rgb[1] + other._rgb[1];
    returnValue._rgb[2] = _rgb[2] + other._rgb[2];

    return returnValue;
}

template <class ValueTypeT> inline
Color3<ValueTypeT> Color3<ValueTypeT>::operator -(const Color3<ValueTypeT> &other) const
{
    Color3<ValueTypeT> returnValue;

    returnValue._rgb[0] = _rgb[0] - other._rgb[0];
    returnValue._rgb[1] = _rgb[1] - other._rgb[1];
    returnValue._rgb[2] = _rgb[2] - other._rgb[2];

    return returnValue;
}

template <class ValueTypeT> inline
void Color3<ValueTypeT>::operator *=(const Color3<ValueTypeT> &other)
{
    _rgb[0] *= other._rgb[0];
    _rgb[1] *= other._rgb[1];
    _rgb[2] *= other._rgb[2];
}

template <class ValueTypeT> inline
void Color3<ValueTypeT>::operator /=(const Color3<ValueTypeT> &other)
{
    _rgb[0] /= other._rgb[0];
    _rgb[1] /= other._rgb[1];
    _rgb[2] /= other._rgb[2];
}

template <class ValueTypeT> inline
void Color3<ValueTypeT>::operator +=(const Color3<ValueTypeT> &other)
{
    _rgb[0] += other._rgb[0];
    _rgb[1] += other._rgb[1];
    _rgb[2] += other._rgb[2];
}

template <class ValueTypeT> inline
void Color3<ValueTypeT>::operator -=(const Color3<ValueTypeT> &other)
{
    _rgb[0] -= other._rgb[0];
    _rgb[1] -= other._rgb[1];
    _rgb[2] -= other._rgb[2];
}


template <class ValueTypeT> inline
typename Color3<ValueTypeT>::ValueType &Color3<ValueTypeT>::operator[] (
    const UInt32 uiIndex)
{
    return _rgb[uiIndex];
}


template <class ValueTypeT> inline
const typename  Color3<ValueTypeT>::ValueType &Color3<ValueTypeT>::operator[](
    const UInt32 uiIndex) const
{
    return _rgb[uiIndex];
}


template <class ValueTypeT> inline
Color3<ValueTypeT> &Color3<ValueTypeT>::operator =(const Color3 &other)
{
    if (this == &other)
        return *this;

    _rgb[0] = other._rgb[0];
    _rgb[1] = other._rgb[1];
    _rgb[2] = other._rgb[2];

    return *this;
}


template <class ValueTypeT> inline
bool Color3<ValueTypeT>::equals(const Color3    &other, 
                                const ValueType  tolerance) const
{
    bool returnValue = true;

    for(UInt32 i = 0; i < 3; i++)
    {
        returnValue &= ( (      _rgb[i] - other._rgb[i] <= tolerance) &&
                         (other._rgb[i] -       _rgb[i] <= tolerance));
    }

    return returnValue;
}


template <class ValueTypeT> inline
bool Color3<ValueTypeT>::operator < (const Color3 &other) const
{
    bool ret = false;

    for(UInt32 i = 0; i < 3; ++i)
    {
        if(_rgb[i] > other._rgb[i])
        {
            break;
        }
        if(_rgb[i] < other._rgb[i])
        {
            ret = true;
            break;
        }
    }

    return ret;
}

template <class ValueTypeT> inline
bool Color3<ValueTypeT>::operator ==(const Color3 &other) const
{
    bool returnValue = true;

    for(UInt32 i = 0; i < 3; i++)
    {
        returnValue &= ( (      _rgb[i] - other._rgb[i] <= Eps) &&
                         (other._rgb[i] -       _rgb[i] <= Eps));
    }

    return returnValue;
}


template <class ValueTypeT> inline
bool Color3<ValueTypeT>::operator != (const Color3 &other) const
{
    return ! (*this == other);
}




template <class ValueTypeT>
const Color4<ValueTypeT> Color4<ValueTypeT>::Null;



template <class ValueTypeT> inline
Color4<ValueTypeT>::Color4(void)
{
    _rgba[0] = TypeTraits<ValueTypeT>::getZeroElement();
    _rgba[1] = TypeTraits<ValueTypeT>::getZeroElement();
    _rgba[2] = TypeTraits<ValueTypeT>::getZeroElement();
    _rgba[3] = TypeTraits<ValueTypeT>::getZeroElement();
}


template <class ValueTypeT> inline
Color4<ValueTypeT>::Color4(const Color4 &source)
{
    _rgba[0] = source._rgba[0];
    _rgba[1] = source._rgba[1];
    _rgba[2] = source._rgba[2];
    _rgba[3] = source._rgba[3];
}


template <class ValueTypeT> inline
Color4<ValueTypeT>::Color4(const ValueType red,
                           const ValueType green,
                           const ValueType blue,
                           const ValueType alpha)
{
    _rgba[0] = red;
    _rgba[1] = green;
    _rgba[2] = blue;
    _rgba[3] = alpha;
}


template <class ValueTypeT> inline
Color4<ValueTypeT>::~Color4(void)
{
}


template <class ValueTypeT> inline
void Color4<ValueTypeT>::clear(void)
{
    _rgba[0] = TypeTraits<ValueTypeT>::getZeroElement();
    _rgba[1] = TypeTraits<ValueTypeT>::getZeroElement();
    _rgba[2] = TypeTraits<ValueTypeT>::getZeroElement();
    _rgba[3] = TypeTraits<ValueTypeT>::getZeroElement();
}


template <class ValueTypeT> inline
void Color4<ValueTypeT>::setValuesRGBA(const ValueType red,
                                       const ValueType green,
                                       const ValueType blue,
                                       const ValueType alpha)
{
    _rgba[0] = red;
    _rgba[1] = green;
    _rgba[2] = blue;
    _rgba[3] = alpha;
}

template <class ValueTypeT> inline
void Color4<ValueTypeT>::setValuesHSV(const Real32 h,
                                      const Real32 s,
                                      const Real32 v)
{
    Color3<ValueType>::convertFromHSV(_rgba, h, s, v);

    _rgba[3] = TypeTraits<ValueTypeT>::getOneElement();
}


template <class ValueTypeT> inline
void Color4<ValueTypeT>::setRandom(void)
{
    Real32 rf = 1.0 / Real32(RAND_MAX);

    setValuesRGBA(TypeTraits<ValueTypeT>::getPortion(rf * rand()),
                  TypeTraits<ValueTypeT>::getPortion(rf * rand()),
                  TypeTraits<ValueTypeT>::getPortion(rf * rand()),
                  TypeTraits<ValueTypeT>::getPortion(rf * rand()));
}

/*! method to set the rgb values (ABGGRR)
 */

template <class ValueTypeT> inline
void Color4<ValueTypeT>::setRGBA(UInt32 rgbPack)
{
    for(Int32 i = 0; i < 4; ++i)
    {
        Real32 rTmp = Real32(rgbPack & 255) / 255.0f;

        _rgba[i] = TypeTraits<ValueTypeT>::getPortion(rTmp);

        rgbPack >>= 8;
    }
}


template <class ValueTypeT> inline
void Color4<ValueTypeT>::setValue(const Char8 *szString)
{
    // this is the easiest way, not the most efficient...
    Vec4f v;

    v.setValueFromCString(szString);

    _rgba[0] = ValueTypeT(v[0]);
    _rgba[1] = ValueTypeT(v[1]);
    _rgba[2] = ValueTypeT(v[2]);
    _rgba[3] = ValueTypeT(v[3]);
}


template <class ValueTypeT> inline
void Color4<ValueTypeT>::setValue(Char8 *szString)
{
    setValue(static_cast<const Char8 *>(szString));
}

/*! method to get a packed rgb value (ABGGRR)
 */

template <class ValueTypeT> inline
UInt32 Color4<ValueTypeT>::getRGBA(void) const
{
    UInt32 pack = 0;

    for(Int32 i = 3; i >= 0; --i)
    {
        pack = (pack << 8) | 
            Int32(TypeTraits<ValueTypeT>::getFraction(_rgba[i]) *
                  255.0f                                        +
                  0.5f                                           );
    }

    return pack;
}


template <class ValueTypeT> inline
void Color4<ValueTypeT>::getValuesRGBA(ValueType &red,
                                       ValueType &green,
                                       ValueType &blue,
                                       ValueType &alpha) const
{
    red   = _rgba[0];
    green = _rgba[1];
    blue  = _rgba[2];
    alpha = _rgba[3];
}


template <class ValueTypeT> inline
void Color4<ValueTypeT>::getValuesHSV(Real32 &h,
                                      Real32 &s,
                                      Real32 &v) const
{
    Color3<ValueType>::convertToHSV(_rgba, h, s, v);
}


template <class ValueTypeT> inline
typename Color4<ValueTypeT>::ValueType
    Color4<ValueTypeT>::red(void) const
{
    return _rgba[0];
}


template <class ValueTypeT> inline
typename Color4<ValueTypeT>::ValueType
    Color4<ValueTypeT>::green(void) const
{
    return _rgba[1];
}


template <class ValueTypeT> inline
typename Color4<ValueTypeT>::ValueType
    Color4<ValueTypeT>::blue(void) const
{
    return _rgba[2];
}


template <class ValueTypeT> inline
typename Color4<ValueTypeT>::ValueType
    Color4<ValueTypeT>::alpha(void) const
{
    return _rgba[3];
}


template <class ValueTypeT> inline
typename Color4<ValueTypeT>::ValueType *
    Color4<ValueTypeT>::getValuesRGBA(void)
{
    return _rgba;
}


template <class ValueTypeT> inline
const typename Color4<ValueTypeT>::ValueType *
    Color4<ValueTypeT>::getValuesRGBA(void) const
{
    return _rgba;
}


template <class ValueTypeT> inline
Color4<ValueTypeT> Color4<ValueTypeT>::operator *(const ValueType val)
{
    Color4<ValueTypeT> returnValue;

    returnValue._rgba[0] = _rgba[0] * val;
    returnValue._rgba[1] = _rgba[1] * val;
    returnValue._rgba[2] = _rgba[2] * val;
    returnValue._rgba[3] = _rgba[3] * val;

    return returnValue;
}

template <class ValueTypeT> inline
Color4<ValueTypeT> Color4<ValueTypeT>::operator /(const ValueType val)
{
    Color4<ValueTypeT> returnValue;

    returnValue._rgba[0] = _rgba[0] / val;
    returnValue._rgba[1] = _rgba[1] / val;
    returnValue._rgba[2] = _rgba[2] / val;
    returnValue._rgba[3] = _rgba[3] / val;

    return returnValue;
}

template <class ValueTypeT> inline
Color4<ValueTypeT> Color4<ValueTypeT>::operator +(const ValueType val)
{
    Color4<ValueTypeT> returnValue;

    returnValue._rgba[0] = _rgba[0] + val;
    returnValue._rgba[1] = _rgba[1] + val;
    returnValue._rgba[2] = _rgba[2] + val;
    returnValue._rgba[3] = _rgba[3] + val;

    return returnValue;
}

template <class ValueTypeT> inline
Color4<ValueTypeT> Color4<ValueTypeT>::operator -(const ValueType val)
{
    Color4<ValueTypeT> returnValue;

    returnValue._rgba[0] = _rgba[0] - val;
    returnValue._rgba[1] = _rgba[1] - val;
    returnValue._rgba[2] = _rgba[2] - val;
    returnValue._rgba[3] = _rgba[3] - val;

    return returnValue;
}

template <class ValueTypeT> inline
void Color4<ValueTypeT>::operator *=(const ValueType val)
{
    _rgba[0] *= val;
    _rgba[1] *= val;
    _rgba[2] *= val;
    _rgba[3] *= val;
}

template <class ValueTypeT> inline
void Color4<ValueTypeT>::operator /=(const ValueType val)
{
    _rgba[0] /= val;
    _rgba[1] /= val;
    _rgba[2] /= val;
    _rgba[3] /= val;
}

template <class ValueTypeT> inline
void Color4<ValueTypeT>::operator +=(const ValueType val)
{
    _rgba[0] += val;
    _rgba[1] += val;
    _rgba[2] += val;
    _rgba[3] += val;
}

template <class ValueTypeT> inline
void Color4<ValueTypeT>::operator -=(const ValueType val)
{
    _rgba[0] -= val;
    _rgba[1] -= val;
    _rgba[2] -= val;
    _rgba[3] -= val;
}


template <class ValueTypeT> inline
Color4<ValueTypeT> Color4<ValueTypeT>::operator *(const Color4<ValueTypeT> &other) const
{
    Color4<ValueTypeT> returnValue;

    returnValue._rgba[0] = _rgba[0] * other._rgba[0];
    returnValue._rgba[1] = _rgba[1] * other._rgba[1];
    returnValue._rgba[2] = _rgba[2] * other._rgba[2];
    returnValue._rgba[3] = _rgba[3] * other._rgba[3];

    return returnValue;
}

template <class ValueTypeT> inline
Color4<ValueTypeT> Color4<ValueTypeT>::operator /(const Color4<ValueTypeT> &other) const
{
    Color4<ValueTypeT> returnValue;

    returnValue._rgba[0] = _rgba[0] / other._rgba[0];
    returnValue._rgba[1] = _rgba[1] / other._rgba[1];
    returnValue._rgba[2] = _rgba[2] / other._rgba[2];
    returnValue._rgba[3] = _rgba[3] / other._rgba[3];

    return returnValue;
}

template <class ValueTypeT> inline
Color4<ValueTypeT> Color4<ValueTypeT>::operator +(const Color4<ValueTypeT> &other) const
{
    Color4<ValueTypeT> returnValue;

    returnValue._rgba[0] = _rgba[0] + other._rgba[0];
    returnValue._rgba[1] = _rgba[1] + other._rgba[1];
    returnValue._rgba[2] = _rgba[2] + other._rgba[2];
    returnValue._rgba[3] = _rgba[3] + other._rgba[3];

    return returnValue;
}

template <class ValueTypeT> inline
Color4<ValueTypeT> Color4<ValueTypeT>::operator -(const Color4<ValueTypeT> &other) const
{
    Color4<ValueTypeT> returnValue;

    returnValue._rgba[0] = _rgba[0] - other._rgba[0];
    returnValue._rgba[1] = _rgba[1] - other._rgba[1];
    returnValue._rgba[2] = _rgba[2] - other._rgba[2];
    returnValue._rgba[3] = _rgba[3] - other._rgba[3];

    return returnValue;
}

template <class ValueTypeT> inline
void Color4<ValueTypeT>::operator *=(const Color4<ValueTypeT> &other)
{
    _rgba[0] *= other._rgba[0];
    _rgba[1] *= other._rgba[1];
    _rgba[2] *= other._rgba[2];
    _rgba[3] *= other._rgba[3];
}

template <class ValueTypeT> inline
void Color4<ValueTypeT>::operator /=(const Color4<ValueTypeT> &other)
{
    _rgba[0] /= other._rgba[0];
    _rgba[1] /= other._rgba[1];
    _rgba[2] /= other._rgba[2];
    _rgba[3] /= other._rgba[3];
}

template <class ValueTypeT> inline
void Color4<ValueTypeT>::operator +=(const Color4<ValueTypeT> &other)
{
    _rgba[0] += other._rgba[0];
    _rgba[1] += other._rgba[1];
    _rgba[2] += other._rgba[2];
    _rgba[3] += other._rgba[3];
}

template <class ValueTypeT> inline
void Color4<ValueTypeT>::operator -=(const Color4<ValueTypeT> &other)
{
    _rgba[0] -= other._rgba[0];
    _rgba[1] -= other._rgba[1];
    _rgba[2] -= other._rgba[2];
    _rgba[3] -= other._rgba[3];
}

template <class ValueTypeT> inline
typename Color4<ValueTypeT>::ValueType &Color4<ValueTypeT>::operator[] (
   const UInt32 uiIndex)
{
    return _rgba[uiIndex];
}


template <class ValueTypeT> inline
const typename Color4<ValueTypeT>::ValueType &Color4<ValueTypeT>::operator[] (
    const UInt32 uiIndex) const
{
    return _rgba[uiIndex];
}

/*-------------------------- assignment -----------------------------------*/

template <class ValueTypeT> inline
Color4<ValueTypeT> &Color4<ValueTypeT>::operator = (
     const Color4 &other)
{
    if (this == &other)
        return *this;

    _rgba[0] = other._rgba[0];
    _rgba[1] = other._rgba[1];
    _rgba[2] = other._rgba[2];
    _rgba[3] = other._rgba[3];

    return *this;
}


/*! equal within tolerance
 */

template <class ValueTypeT> inline
bool Color4<ValueTypeT>::equals(const Color4    &other, 
                                const ValueType  tolerance) const
{
    bool returnValue = true;

    for(UInt32 i = 0; i < 4; i++)
    {
        returnValue &= ( (      _rgba[i] - other._rgba[i] <= tolerance) &&
                         (other._rgba[i] -       _rgba[i] <= tolerance));
    }

    return returnValue;
}

template <class ValueTypeT> inline
bool Color4<ValueTypeT>::operator < (const Color4 &other) const
{
    bool ret = false;

    for(UInt32 i = 0; i < 4; ++i)
    {
        if(_rgba[i] > other._rgba[i])
        {
            break;
        }
        if(_rgba[i] < other._rgba[i])
        {
            ret = true;
            break;
        }
    }

    return ret;
}

template <class ValueTypeT> inline
bool Color4<ValueTypeT>::operator ==(const Color4 &other) const
{
    bool returnValue = true;

    for(UInt32 i = 0; i < 4; i++)
    {
        returnValue &= ( (      _rgba[i] - other._rgba[i] <= Eps) &&
                         (other._rgba[i] -       _rgba[i] <= Eps));
    }

    return returnValue;
}


template <class ValueTypeT> inline
bool Color4<ValueTypeT>::operator !=(const Color4 &other) const
{
    return ! (*this == other);
}


template <class ValueTypeT> inline
std::ostream &operator <<(      std::ostream       &outStream,
                          const Color3<ValueTypeT> &color)
{
    return outStream << color.red()   << ' '
                     << color.green() << ' '
                     << color.blue();
}


template <class ValueTypeT> inline
std::ostream &operator <<(      std::ostream       &outStream,
                          const Color4<ValueTypeT> &color)
{
    return outStream << color.red()   << ' '
                     << color.green() << ' '
                     << color.blue()  << ' '
                     << color.alpha();
}

OSG_END_NAMESPACE

#define OSGCOLOR_INLINE_CVSID "@(#)$Id: $"
