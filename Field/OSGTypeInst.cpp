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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#define OSG_COMPILEBASELIB
#define OSG_COMPILEFIELDINST

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <OSGField.h>
#include <OSGSField.h>
#include <OSGMField.h>

#include "OSGSFBaseTypes.h"
#include "OSGMFBaseTypes.h"
#include "OSGSFSysTypes.h"
#include "OSGMFSysTypes.h"
#include "OSGSFVecTypes.h"
#include "OSGMFVecTypes.h"

#include "OSGSFMathTypes.h"
#include "OSGMFMathTypes.h"

OSG_BEGIN_NAMESPACE


DataType FieldDataTraits2<Bool >::_type("Bool"  , true);
DataType FieldDataTraits< Int8 >::_type("Int8"  , true);
DataType FieldDataTraits<UInt8 >::_type("UInt8" , true);
DataType FieldDataTraits< Int16>::_type("Int16" , true);
DataType FieldDataTraits<UInt16>::_type("UInt16", true);
DataType FieldDataTraits< Int32>::_type("Int32" , true);
DataType FieldDataTraits<UInt32>::_type("UInt32", true);
DataType FieldDataTraits< Int64>::_type("Int64" , true);
DataType FieldDataTraits<UInt64>::_type("UInt64", true);
DataType FieldDataTraits<Real32>::_type("Real32", true);
DataType FieldDataTraits<Real64>::_type("Real64", true);

DataType FieldDataTraits<String       >::_type("String"       , true);
DataType FieldDataTraits1<Time        >::_type("Time"         , true);
DataType FieldDataTraits<Color3f      >::_type("Color3f"      , true);
DataType FieldDataTraits<Color4f      >::_type("Color4f"      , true);
DataType FieldDataTraits<Color3ub     >::_type("Color3ub"     , true);
DataType FieldDataTraits<Color4ub     >::_type("Color4ub"     , true);
DataType FieldDataTraits<DynamicVolume>::_type("DynamicVolume", true);
DataType FieldDataTraits1<BitVector   >::_type("BitVector"    , true);

DataType FieldDataTraits<Vec2f>::_type("Vec2f", true);
DataType FieldDataTraits<Vec3f>::_type("Vec3f", true);
DataType FieldDataTraits<Vec4f>::_type("Vec4f", true);
DataType FieldDataTraits<Pnt2f>::_type("Pnt2f", true);
DataType FieldDataTraits<Pnt3f>::_type("Pnt3f", true);
DataType FieldDataTraits<Pnt4f>::_type("Pnt4f", true);

DataType FieldDataTraits<Vec4ub>::_type("Vec4ub", true);

DataType FieldDataTraits<Matrix    >::_type("Matrix"    , true);
DataType FieldDataTraits<Quaternion>::_type("Quaternion", true);

DataType FieldDataTraits<Plane>::_type("Plane", true);

#if defined(__sgi)



#pragma instantiate SField<Bool,2>::_fieldType
#pragma instantiate SField< Int8 >::_fieldType
#pragma instantiate SField<UInt8 >::_fieldType
#pragma instantiate SField< Int16>::_fieldType
#pragma instantiate SField<UInt16>::_fieldType
#pragma instantiate SField< Int32>::_fieldType
#pragma instantiate SField<UInt32>::_fieldType
#pragma instantiate SField< Int64>::_fieldType
#pragma instantiate SField<UInt64>::_fieldType
#pragma instantiate SField<Real32>::_fieldType
#pragma instantiate SField<Real64>::_fieldType

#pragma instantiate MField<Bool,2>::_fieldType
#pragma instantiate MField< Int8 >::_fieldType
#pragma instantiate MField<UInt8 >::_fieldType
#pragma instantiate MField< Int16>::_fieldType
#pragma instantiate MField<UInt16>::_fieldType
#pragma instantiate MField< Int32>::_fieldType
#pragma instantiate MField<UInt32>::_fieldType
#pragma instantiate MField< Int64>::_fieldType
#pragma instantiate MField<UInt64>::_fieldType
#pragma instantiate MField<Real32>::_fieldType
#pragma instantiate MField<Real64>::_fieldType

#pragma instantiate SField<String       >::_fieldType
#pragma instantiate SField<Time, 1      >::_fieldType
#pragma instantiate SField<Color3f      >::_fieldType
#pragma instantiate SField<Color4f      >::_fieldType
#pragma instantiate SField<Color3ub     >::_fieldType
#pragma instantiate SField<Color4ub     >::_fieldType
#pragma instantiate SField<DynamicVolume>::_fieldType
#pragma instantiate SField<BitVector, 1 >::_fieldType

#pragma instantiate MField<String       >::_fieldType
#pragma instantiate MField<Time, 1      >::_fieldType
#pragma instantiate MField<Color3f      >::_fieldType
#pragma instantiate MField<Color4f      >::_fieldType
#pragma instantiate MField<Color3ub     >::_fieldType
#pragma instantiate MField<Color4ub     >::_fieldType
#pragma instantiate MField<DynamicVolume>::_fieldType
#pragma instantiate MField<BitVector, 1 >::_fieldType

#pragma instantiate SField<Vec2f>::_fieldType
#pragma instantiate SField<Vec3f>::_fieldType
#pragma instantiate SField<Vec4f>::_fieldType
#pragma instantiate SField<Pnt2f>::_fieldType
#pragma instantiate SField<Pnt3f>::_fieldType
#pragma instantiate SField<Pnt4f>::_fieldType

#pragma instantiate MField<Vec2f>::_fieldType
#pragma instantiate MField<Vec3f>::_fieldType
#pragma instantiate MField<Vec4f>::_fieldType
#pragma instantiate MField<Pnt2f>::_fieldType
#pragma instantiate MField<Pnt3f>::_fieldType
#pragma instantiate MField<Pnt4f>::_fieldType

#pragma instantiate MField<Vec4ub>::_fieldType

#pragma instantiate SField<Matrix    >::_fieldType
#pragma instantiate SField<Quaternion>::_fieldType

#pragma instantiate MField<Matrix    >::_fieldType
#pragma instantiate MField<Quaternion>::_fieldType

#pragma instantiate SField<Plane>::_fieldType
#pragma instantiate MField<Plane>::_fieldType

#else


OSG_DLLEXPORT_DEF2(SField, Bool  , 2, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField,  Int8 , OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, UInt8 , OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField,  Int16, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, UInt16, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField,  Int32, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, UInt32, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField,  Int64, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, UInt64, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, Real32, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, Real64, OSG_BASE_DLLTMPLMAPPING)

OSG_DLLEXPORT_DEF2(MField, Bool  , 2, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField,  Int8 , OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, UInt8 , OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField,  Int16, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, UInt16, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField,  Int32, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, UInt32, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField,  Int64, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, UInt64, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Real32, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Real64, OSG_BASE_DLLTMPLMAPPING)

OSG_DLLEXPORT_DEF1(SField, String,        OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF2(SField, Time, 1,       OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, Color3f,       OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, Color4f,       OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, Color3ub,      OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, Color4ub,      OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, DynamicVolume, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF2(SField, BitVector, 1,  OSG_BASE_DLLTMPLMAPPING)

OSG_DLLEXPORT_DEF1(MField, String,        OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF2(MField, Time, 1,       OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Color3f,       OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Color4f,       OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Color3ub,      OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Color4ub,      OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, DynamicVolume, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF2(MField, BitVector, 1,  OSG_BASE_DLLTMPLMAPPING)

OSG_DLLEXPORT_DEF1(SField, Vec2f, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, Vec3f, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, Vec4f, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, Pnt2f, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, Pnt3f, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, Pnt4f, OSG_BASE_DLLTMPLMAPPING)

OSG_DLLEXPORT_DEF1(MField, Vec2f, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Vec3f, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Vec4f, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Pnt2f, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Pnt3f, OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Pnt4f, OSG_BASE_DLLTMPLMAPPING)

OSG_DLLEXPORT_DEF1(MField, Vec4ub, OSG_BASE_DLLTMPLMAPPING)


OSG_DLLEXPORT_DEF1(SField, Matrix,     OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, Quaternion, OSG_BASE_DLLTMPLMAPPING)

OSG_DLLEXPORT_DEF1(MField, Matrix,     OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Quaternion, OSG_BASE_DLLTMPLMAPPING)

OSG_DLLEXPORT_DEF1(SField, Plane,	OSG_BASE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Plane,	OSG_BASE_DLLTMPLMAPPING)

#endif

OSG_END_NAMESPACE

