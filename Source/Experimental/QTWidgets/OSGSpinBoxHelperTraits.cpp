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

#include "OSGSpinBoxHelperTraits.h"


OSG_USING_NAMESPACE
/*-------------------------------------------------------------------------*/
/*    SpinBoxHelperTraits<Int8>                                            */

const Int8 SpinBoxHelperTraits<Int8>::_initLowerBound                =
    TypeTraits<Int8>::getMin();

const Int8 SpinBoxHelperTraits<Int8>::_initUpperBound                =
    TypeTraits<Int8>::getMax();

const Int8 SpinBoxHelperTraits<Int8>::_initDefaultStepSize           =
    TypeTraits<Int8>::getOneElement();

const Int8 SpinBoxHelperTraits<Int8>::_initDefaultPageStepSize       =
    TypeTraits<Int8>::getOneElement() * 10;

Int8 SpinBoxHelperTraits<Int8>::_defaultStepSize                     =
    SpinBoxHelperTraits<Int8>::_initDefaultStepSize;

Int8 SpinBoxHelperTraits<Int8>::_defaultPageStepSize                 =
    SpinBoxHelperTraits<Int8>::_initDefaultPageStepSize;


/*-------------------------------------------------------------------------*/
/*    SpinBoxHelperTraits<Int16>                                           */

const Int16 SpinBoxHelperTraits<Int16>::_initLowerBound              =
    TypeTraits<Int16>::getMin();

const Int16 SpinBoxHelperTraits<Int16>::_initUpperBound              =
    TypeTraits<Int16>::getMax();

const Int16 SpinBoxHelperTraits<Int16>::_initDefaultStepSize         =
    TypeTraits<Int16>::getOneElement();

const Int16 SpinBoxHelperTraits<Int16>::_initDefaultPageStepSize     =
    TypeTraits<Int16>::getOneElement() * 10;

Int16 SpinBoxHelperTraits<Int16>::_defaultStepSize                   =
    SpinBoxHelperTraits<Int16>::_initDefaultStepSize;

Int16 SpinBoxHelperTraits<Int16>::_defaultPageStepSize               =
    SpinBoxHelperTraits<Int16>::_initDefaultPageStepSize;

/*-------------------------------------------------------------------------*/
/*    SpinBoxHelperTraits<Int32>                                           */


const Int32 SpinBoxHelperTraits<Int32>::_initLowerBound              =
    TypeTraits<Int32>::getMin();

const Int32 SpinBoxHelperTraits<Int32>::_initUpperBound              =
    TypeTraits<Int32>::getMax();

const Int32 SpinBoxHelperTraits<Int32>::_initDefaultStepSize         =
    TypeTraits<Int32>::getOneElement();

const Int32 SpinBoxHelperTraits<Int32>::_initDefaultPageStepSize     =
    TypeTraits<Int32>::getOneElement() * 10;

Int32 SpinBoxHelperTraits<Int32>::_defaultStepSize                   =
    SpinBoxHelperTraits<Int32>::_initDefaultStepSize;

Int32 SpinBoxHelperTraits<Int32>::_defaultPageStepSize               =
    SpinBoxHelperTraits<Int32>::_initDefaultPageStepSize;

/*-------------------------------------------------------------------------*/
/*    SpinBoxHelperTraits<Int64>                                           */


const Int64 SpinBoxHelperTraits<Int64>::_initLowerBound              =
    TypeTraits<Int64>::getMin();

const Int64 SpinBoxHelperTraits<Int64>::_initUpperBound              =
    TypeTraits<Int64>::getMax();

const Int64 SpinBoxHelperTraits<Int64>::_initDefaultStepSize         =
    TypeTraits<Int64>::getOneElement();

const Int64 SpinBoxHelperTraits<Int64>::_initDefaultPageStepSize     =
    TypeTraits<Int64>::getOneElement() * 10;

Int64 SpinBoxHelperTraits<Int64>::_defaultStepSize                   =
    SpinBoxHelperTraits<Int64>::_initDefaultStepSize;

Int64 SpinBoxHelperTraits<Int64>::_defaultPageStepSize               =
    SpinBoxHelperTraits<Int64>::_initDefaultPageStepSize;

/*-------------------------------------------------------------------------*/
/*    SpinBoxHelperTraits<UInt8>                                           */


const UInt8 SpinBoxHelperTraits<UInt8>::_initLowerBound              =
    TypeTraits<UInt8>::getMin();

const UInt8 SpinBoxHelperTraits<UInt8>::_initUpperBound              =
    TypeTraits<UInt8>::getMax();

const UInt8 SpinBoxHelperTraits<UInt8>::_initDefaultStepSize         =
    TypeTraits<UInt8>::getOneElement();

const UInt8 SpinBoxHelperTraits<UInt8>::_initDefaultPageStepSize     =
    TypeTraits<UInt8>::getOneElement() * 10;

UInt8 SpinBoxHelperTraits<UInt8>::_defaultStepSize                   =
    SpinBoxHelperTraits<UInt8>::_initDefaultStepSize;

UInt8 SpinBoxHelperTraits<UInt8>::_defaultPageStepSize               =
    SpinBoxHelperTraits<UInt8>::_initDefaultPageStepSize;

/*-------------------------------------------------------------------------*/
/*    SpinBoxHelperTraits<UInt16>                                          */


const UInt16 SpinBoxHelperTraits<UInt16>::_initLowerBound            =
    TypeTraits<UInt16>::getMin();

const UInt16 SpinBoxHelperTraits<UInt16>::_initUpperBound            =
    TypeTraits<UInt16>::getMax();

const UInt16 SpinBoxHelperTraits<UInt16>::_initDefaultStepSize       =
    TypeTraits<UInt16>::getOneElement();

const UInt16 SpinBoxHelperTraits<UInt16>::_initDefaultPageStepSize   =
    TypeTraits<UInt16>::getOneElement() * 10;

UInt16 SpinBoxHelperTraits<UInt16>::_defaultStepSize                 =
    SpinBoxHelperTraits<UInt16>::_initDefaultStepSize;

UInt16 SpinBoxHelperTraits<UInt16>::_defaultPageStepSize             =
    SpinBoxHelperTraits<UInt16>::_initDefaultPageStepSize;

/*-------------------------------------------------------------------------*/
/*    SpinBoxHelperTraits<UInt32>                                          */


const UInt32 SpinBoxHelperTraits<UInt32>::_initLowerBound            =
    TypeTraits<UInt32>::getMin();

const UInt32 SpinBoxHelperTraits<UInt32>::_initUpperBound            =
    TypeTraits<UInt32>::getMax();

const UInt32 SpinBoxHelperTraits<UInt32>::_initDefaultStepSize       =
    TypeTraits<UInt32>::getOneElement();

const UInt32 SpinBoxHelperTraits<UInt32>::_initDefaultPageStepSize   =
    TypeTraits<UInt32>::getOneElement() * 10;

UInt32 SpinBoxHelperTraits<UInt32>::_defaultStepSize                 =
    SpinBoxHelperTraits<UInt32>::_initDefaultStepSize;

UInt32 SpinBoxHelperTraits<UInt32>::_defaultPageStepSize             =
    SpinBoxHelperTraits<UInt32>::_initDefaultPageStepSize;

/*-------------------------------------------------------------------------*/
/*    SpinBoxHelperTraits<UInt64>                                          */


const UInt64 SpinBoxHelperTraits<UInt64>::_initLowerBound            =
    TypeTraits<UInt64>::getMin();

const UInt64 SpinBoxHelperTraits<UInt64>::_initUpperBound            =
    TypeTraits<UInt64>::getMax();

const UInt64 SpinBoxHelperTraits<UInt64>::_initDefaultStepSize       =
    TypeTraits<UInt64>::getOneElement();

const UInt64 SpinBoxHelperTraits<UInt64>::_initDefaultPageStepSize   =
    TypeTraits<UInt64>::getOneElement() * 10;

UInt64 SpinBoxHelperTraits<UInt64>::_defaultStepSize                 =
    SpinBoxHelperTraits<UInt64>::_initDefaultStepSize;

UInt64 SpinBoxHelperTraits<UInt64>::_defaultPageStepSize             =
    SpinBoxHelperTraits<UInt64>::_initDefaultPageStepSize;

/*-------------------------------------------------------------------------*/
/*    SpinBoxHelperTraits<Real32>                                          */


const Real32 SpinBoxHelperTraits<Real32>::_initLowerBound            =
    - TypeTraits<Real32>::getMax();

const Real32 SpinBoxHelperTraits<Real32>::_initUpperBound            =
    TypeTraits<Real32>::getMax();

const Real32 SpinBoxHelperTraits<Real32>::_initDefaultStepSize       =
    TypeTraits<Real32>::getOneElement();

const Real32 SpinBoxHelperTraits<Real32>::_initDefaultPageStepSize   =
    TypeTraits<Real32>::getOneElement() * 10;

Real32 SpinBoxHelperTraits<Real32>::_defaultStepSize                 =
    SpinBoxHelperTraits<Real32>::_initDefaultStepSize;

Real32 SpinBoxHelperTraits<Real32>::_defaultPageStepSize             =
    SpinBoxHelperTraits<Real32>::_initDefaultPageStepSize;

/*-------------------------------------------------------------------------*/
/*    SpinBoxHelperTraits<Real64>                                          */


const Real64 SpinBoxHelperTraits<Real64>::_initLowerBound            =
    - TypeTraits<Real64>::getMax();

const Real64 SpinBoxHelperTraits<Real64>::_initUpperBound            =
    TypeTraits<Real64>::getMax();

const Real64 SpinBoxHelperTraits<Real64>::_initDefaultStepSize       =
    TypeTraits<Real64>::getOneElement();

const Real64 SpinBoxHelperTraits<Real64>::_initDefaultPageStepSize   =
    TypeTraits<Real64>::getOneElement() * 10;

Real64 SpinBoxHelperTraits<Real64>::_defaultStepSize                 =
    SpinBoxHelperTraits<Real64>::_initDefaultStepSize;

Real64 SpinBoxHelperTraits<Real64>::_defaultPageStepSize             =
    SpinBoxHelperTraits<Real64>::_initDefaultPageStepSize;

/*-------------------------------------------------------------------------*/
/*    SpinBoxHelperTraits<Real128>                                         */


const Real128 SpinBoxHelperTraits<Real128>::_initLowerBound          =
    - TypeTraits<Real128>::getMax();

const Real128 SpinBoxHelperTraits<Real128>::_initUpperBound          =
    TypeTraits<Real128>::getMax();

const Real128 SpinBoxHelperTraits<Real128>::_initDefaultStepSize     =
    TypeTraits<Real128>::getOneElement();

const Real128 SpinBoxHelperTraits<Real128>::_initDefaultPageStepSize =
    TypeTraits<Real128>::getOneElement() * 10;

Real128 SpinBoxHelperTraits<Real128>::_defaultStepSize               =
    SpinBoxHelperTraits<Real128>::_initDefaultStepSize;

Real128 SpinBoxHelperTraits<Real128>::_defaultPageStepSize           =
    SpinBoxHelperTraits<Real128>::_initDefaultPageStepSize;

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGSpinBoxHelperTraits.cpp,v 1.2 2004/08/17 13:37:21 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGSPINBOXHELPERTRAITS_HEADER_CVSID;
//    static Char8 cvsid_inl       [] = OSGSPINBOXHELPERTRAITS_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
