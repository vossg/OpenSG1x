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

#ifndef _OSGSPINBOXHELPERTRAITS_H_
#define _OSGSPINBOXHELPERTRAITS_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGWindowQTDef.h>

#include <OSGBaseTypes.h>

OSG_BEGIN_NAMESPACE

template <class ValueTypeT>
class OSG_WINDOWQTLIB_DLLMAPPING SpinBoxHelperTraits
{
};

template <>
class SpinBoxHelperTraits<Int8>
{
  public:
    typedef Int8      SignedType;
    typedef UInt8     UnsignedType;

    typedef UInt8     DeltaType;
    typedef Real32    RealType;

    static const Int8 _initLowerBound;
    static const Int8 _initUpperBound;

    static const Int8 _initDefaultStepSize;
    static const Int8 _initDefaultPageStepSize;

    static       Int8 _defaultStepSize;
    static       Int8 _defaultPageStepSize;
};

template <>
class SpinBoxHelperTraits<Int16>
{
  public:
    typedef Int16      SignedType;
    typedef UInt16     UnsignedType;

    typedef UInt16     DeltaType;
    typedef Real32     RealType;

    static const Int16 _initLowerBound;
    static const Int16 _initUpperBound;

    static const Int16 _initDefaultStepSize;
    static const Int16 _initDefaultPageStepSize;

    static       Int16 _defaultStepSize;
    static       Int16 _defaultPageStepSize;
};

template <>
class SpinBoxHelperTraits<Int32>
{
  public:
    typedef Int32      SignedType;
    typedef UInt32     UnsignedType;

    typedef UInt32     DeltaType;
    typedef Real32     RealType;

    static const Int32 _initLowerBound;
    static const Int32 _initUpperBound;

    static const Int32 _initDefaultStepSize;
    static const Int32 _initDefaultPageStepSize;

    static       Int32 _defaultStepSize;
    static       Int32 _defaultPageStepSize;
};

template <>
class SpinBoxHelperTraits<Int64>
{
  public:
    typedef Int64      SignedType;
    typedef UInt64     UnsignedType;

    typedef UInt64     DeltaType;
    typedef Real32     RealType;

    static const Int64 _initLowerBound;
    static const Int64 _initUpperBound;

    static const Int64 _initDefaultStepSize;
    static const Int64 _initDefaultPageStepSize;

    static       Int64 _defaultStepSize;
    static       Int64 _defaultPageStepSize;
};

template <>
class SpinBoxHelperTraits<UInt8>
{
  public:
    typedef Int8       SignedType;
    typedef UInt8      UnsignedType;

    typedef UInt8      DeltaType;
    typedef Real32     RealType;

    static const UInt8 _initLowerBound;
    static const UInt8 _initUpperBound;

    static const UInt8 _initDefaultStepSize;
    static const UInt8 _initDefaultPageStepSize;

    static       UInt8 _defaultStepSize;
    static       UInt8 _defaultPageStepSize;
};

template <>
class SpinBoxHelperTraits<UInt16>
{
  public:
    typedef Int16       SignedType;
    typedef UInt16      UnsignedType;

    typedef UInt16      DeltaType;
    typedef Real32      RealType;

    static const UInt16 _initLowerBound;
    static const UInt16 _initUpperBound;

    static const UInt16 _initDefaultStepSize;
    static const UInt16 _initDefaultPageStepSize;

    static       UInt16 _defaultStepSize;
    static       UInt16 _defaultPageStepSize;
};

template <>
class SpinBoxHelperTraits<UInt32>
{
  public:
    typedef Int32       SignedType;
    typedef UInt32      UnsignedType;

    typedef UInt32      DeltaType;
    typedef Real32      RealType;

    static const UInt32 _initLowerBound;
    static const UInt32 _initUpperBound;

    static const UInt32 _initDefaultStepSize;
    static const UInt32 _initDefaultPageStepSize;

    static       UInt32 _defaultStepSize;
    static       UInt32 _defaultPageStepSize;
};

template <>
class SpinBoxHelperTraits<UInt64>
{
  public:
    typedef Int64       SignedType;
    typedef UInt64      UnsignedType;

    typedef UInt64      DeltaType;
    typedef Real32      RealType;

    static const UInt64 _initLowerBound;
    static const UInt64 _initUpperBound;

    static const UInt64 _initDefaultStepSize;
    static const UInt64 _initDefaultPageStepSize;

    static       UInt64 _defaultStepSize;
    static       UInt64 _defaultPageStepSize;
};

template <>
class SpinBoxHelperTraits<Real32>
{
  public:
    typedef Real32      SignedType;
    typedef Real32      UnsignedType;

    typedef Real64      DeltaType;
    typedef Real32      RealType;

    static const Real32 _initLowerBound;
    static const Real32 _initUpperBound;

    static const Real32 _initDefaultStepSize;
    static const Real32 _initDefaultPageStepSize;

    static       Real32 _defaultStepSize;
    static       Real32 _defaultPageStepSize;
};

template <>
class SpinBoxHelperTraits<Real64>
{
  public:
    typedef Real64      SignedType;
    typedef Real64      UnsignedType;

    typedef Real128     DeltaType;
    typedef Real64      RealType;

    static const Real64 _initLowerBound;
    static const Real64 _initUpperBound;

    static const Real64 _initDefaultStepSize;
    static const Real64 _initDefaultPageStepSize;

    static       Real64 _defaultStepSize;
    static       Real64 _defaultPageStepSize;
};

template <>
class SpinBoxHelperTraits<Real128>
{
  public:
    typedef Real128      SignedType;
    typedef Real128      UnsignedType;

    typedef Real128      DeltaType;
    typedef Real128      RealType;

    static const Real128 _initLowerBound;
    static const Real128 _initUpperBound;

    static const Real128 _initDefaultStepSize;
    static const Real128 _initDefaultPageStepSize;

    static       Real128 _defaultStepSize;
    static       Real128 _defaultPageStepSize;
};

OSG_END_NAMESPACE

#define OSGSPINBOXHELPERTRAITS_HEADER_CVSID "@(#)$Id: OSGSpinBoxHelperTraits.h,v 1.1 2004/07/30 15:32:15 neumannc Exp $"

#endif /* _OSGSPINBOXHELPERTRAITS_H_ */
