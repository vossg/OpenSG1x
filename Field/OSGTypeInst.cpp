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

#include "OSGSFieldTypeDef.inl"
#include "OSGMFieldTypeDef.inl"

OSG_BEGIN_NAMESPACE

DataType FieldDataTraits2<bool >::_type("bool"  , "IntegralType");
DataType FieldDataTraits< Int8 >::_type("Int8"  , "IntegralType");
DataType FieldDataTraits<UInt8 >::_type("UInt8" , "IntegralType");
DataType FieldDataTraits< Int16>::_type("Int16" , "IntegralType");
DataType FieldDataTraits<UInt16>::_type("UInt16", "IntegralType");
DataType FieldDataTraits< Int32>::_type("Int32" , "IntegralType");
DataType FieldDataTraits<UInt32>::_type("UInt32", "IntegralType");
DataType FieldDataTraits< Int64>::_type("Int64" , "IntegralType");
DataType FieldDataTraits<UInt64>::_type("UInt64", "IntegralType");
DataType FieldDataTraits<Real32>::_type("Real32", "IntegralType");
DataType FieldDataTraits<Real64>::_type("Real64", "IntegralType");

DataType FieldDataTraits<string       >::_type("string", 
                                               "BaseType");
DataType FieldDataTraits1<Time        >::_type("Time",
                                               "BaseType");
DataType FieldDataTraits<Color3f      >::_type("Color3f",
                                               "BaseType");
DataType FieldDataTraits<Color4f      >::_type("Color4f",
                                               "BaseType");
DataType FieldDataTraits<Color3ub     >::_type("Color3ub",
                                               "BaseType");
DataType FieldDataTraits<Color4ub     >::_type("Color4ub",
                                               "BaseType");
DataType FieldDataTraits<DynamicVolume>::_type("DynamicVolume",
                                               "BaseType");
DataType FieldDataTraits1<BitVector   >::_type("BitVector",
                                               "BaseType");

DataType FieldDataTraits<Vec2f>::_type("Vec2f", "BaseType");
DataType FieldDataTraits<Vec3f>::_type("Vec3f", "BaseType");
DataType FieldDataTraits<Vec4f>::_type("Vec4f", "BaseType");
DataType FieldDataTraits<Pnt2f>::_type("Pnt2f", "BaseType");
DataType FieldDataTraits<Pnt2d>::_type("Pnt2d", "BaseType");
DataType FieldDataTraits<Pnt3f>::_type("Pnt3f", "BaseType");
DataType FieldDataTraits<Pnt3d>::_type("Pnt3d", "BaseType");
DataType FieldDataTraits<Pnt4f>::_type("Pnt4f", "BaseType");
DataType FieldDataTraits<Pnt4d>::_type("Pnt4d", "BaseType");

DataType FieldDataTraits<Vec4ub>::_type("Vec4ub", "BaseType");

DataType FieldDataTraits<Matrix    >::_type("Matrix"    , "BaseType");
DataType FieldDataTraits<Quaternion>::_type("Quaternion", "BaseType");

DataType FieldDataTraits<Plane>::_type("Plane", "BaseType");

#if defined(OSG_SGI_EXPLICIT_INSTANTIATION)

#pragma instantiate SField<bool,2>::_fieldType
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

#pragma instantiate MField<bool,2>::_fieldType
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

#pragma instantiate SField<string       >::_fieldType
#pragma instantiate SField<Time, 1      >::_fieldType
#pragma instantiate SField<Color3f      >::_fieldType
#pragma instantiate SField<Color4f      >::_fieldType
#pragma instantiate SField<Color3ub     >::_fieldType
#pragma instantiate SField<Color4ub     >::_fieldType
#pragma instantiate SField<DynamicVolume>::_fieldType
#pragma instantiate SField<BitVector, 1 >::_fieldType

#pragma instantiate MField<string       >::_fieldType
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
#pragma instantiate SField<Pnt2d>::_fieldType
#pragma instantiate SField<Pnt3f>::_fieldType
#pragma instantiate SField<Pnt3d>::_fieldType
#pragma instantiate SField<Pnt4f>::_fieldType
#pragma instantiate SField<Pnt4d>::_fieldType

#pragma instantiate MField<Vec2f>::_fieldType
#pragma instantiate MField<Vec3f>::_fieldType
#pragma instantiate MField<Vec4f>::_fieldType
#pragma instantiate MField<Pnt2f>::_fieldType
#pragma instantiate MField<Pnt2d>::_fieldType
#pragma instantiate MField<Pnt3f>::_fieldType
#pragma instantiate MField<Pnt3d>::_fieldType
#pragma instantiate MField<Pnt4f>::_fieldType
#pragma instantiate MField<Pnt4d>::_fieldType

#pragma instantiate MField<Vec4ub>::_fieldType

#pragma instantiate SField<Matrix    >::_fieldType
#pragma instantiate SField<Quaternion>::_fieldType

#pragma instantiate MField<Matrix    >::_fieldType
#pragma instantiate MField<Quaternion>::_fieldType

#pragma instantiate SField<Plane>::_fieldType
#pragma instantiate MField<Plane>::_fieldType

#else

OSG_DLLEXPORT_SFIELD_DEF2(bool  , 2, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1( Int8 , OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(UInt8 , OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1( Int16, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(UInt16, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1( Int32, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(UInt32, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1( Int64, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(UInt64, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Real32, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Real64, OSG_BASE_DLLTMPLMAPPING);

OSG_DLLEXPORT_MFIELD_DEF2(bool  , 2, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1( Int8 , OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(UInt8 , OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1( Int16, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(UInt16, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1( Int32, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(UInt32, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1( Int64, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(UInt64, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Real32, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Real64, OSG_BASE_DLLTMPLMAPPING);

OSG_DLLEXPORT_SFIELD_DEF1(string,        OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF2(Time, 1,       OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Color3f,       OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Color4f,       OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Color3ub,      OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Color4ub,      OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(DynamicVolume, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF2(BitVector, 1,  OSG_BASE_DLLTMPLMAPPING);

OSG_DLLEXPORT_MFIELD_DEF1(string,        OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF2(Time, 1,       OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Color3f,       OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Color4f,       OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Color3ub,      OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Color4ub,      OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(DynamicVolume, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF2(BitVector, 1,  OSG_BASE_DLLTMPLMAPPING);

OSG_DLLEXPORT_SFIELD_DEF1(Vec2f, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Vec3f, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Vec4f, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Pnt2f, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Pnt2d, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Pnt3f, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Pnt3d, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Pnt4f, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Pnt4d, OSG_BASE_DLLTMPLMAPPING);

OSG_DLLEXPORT_MFIELD_DEF1(Vec2f, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Vec3f, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Vec4f, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Pnt2f, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Pnt2d, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Pnt3f, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Pnt3d, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Pnt4f, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Pnt4d, OSG_BASE_DLLTMPLMAPPING);

OSG_DLLEXPORT_MFIELD_DEF1(Vec4ub, OSG_BASE_DLLTMPLMAPPING);


OSG_DLLEXPORT_SFIELD_DEF1(Matrix,     OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Quaternion, OSG_BASE_DLLTMPLMAPPING);

OSG_DLLEXPORT_MFIELD_DEF1(Matrix,     OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Quaternion, OSG_BASE_DLLTMPLMAPPING);

OSG_DLLEXPORT_SFIELD_DEF1(Plane,       OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Plane,       OSG_BASE_DLLTMPLMAPPING);

#endif

OSG_END_NAMESPACE


OSG_USING_NAMESPACE

//template const FieldType MField<Quaternion>::_fieldType;
///template const FieldType &MField<Quaternion>::getClassType(void);

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";

    static Char8 cvsid_sfbt_hpp[] = OSGSFBASETYPES_HEADER_CVSID;
    static Char8 cvsid_mfbt_hpp[] = OSGMFBASETYPES_HEADER_CVSID;
    static Char8 cvsid_bfdt_hpp[] = OSGBASEFIELDDATATYPE_HEADER_CVSID;
}
