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

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

DataType FieldDataTraits2<bool >::_type("bool"  , "IntegralType");
DataType FieldDataTraits< Int8 >::_type("Int8"  , "IntegralType");
DataType FieldDataTraits<UInt8 >::_type("UInt8" , "IntegralType");
DataType FieldDataTraits< Int16>::_type("Int16" , "IntegralType");
DataType FieldDataTraits<UInt16>::_type("UInt16", "IntegralType");
DataType FieldDataTraits< Int32>::_type("Int32" , "IntegralType");
DataType FieldDataTraits<UInt32>::_type("UInt32", "IntegralType");
DataType FieldDataTraits< Int64>::_type("Int64" , "IntegralType");
DataType FieldDataTraits<UInt64>::_type("UInt64", "IntegralType");
DataType FieldDataTraits<Real16>::_type("Real16", "IntegralType");
DataType FieldDataTraits<Real32>::_type("Real32", "IntegralType");
DataType FieldDataTraits<Real64>::_type("Real64", "IntegralType");
DataType FieldDataTraits<void *>::_type("VoidP" , "IntegralType");

DataType FieldDataTraits<std::string  >::_type("string", 
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
DataType FieldDataTraits1<GLenum      >::_type("GLenum",
                                               "BaseType");

DataType FieldDataTraits<Vec2ub>::_type("Vec2ub", "BaseType");
#ifndef OSG_NO_INT8_PNT
DataType FieldDataTraits<Vec2b >::_type("Vec2b" , "BaseType");
#endif
DataType FieldDataTraits<Vec2us>::_type("Vec2us", "BaseType");
DataType FieldDataTraits<Vec2s >::_type("Vec2s" , "BaseType");
DataType FieldDataTraits<Vec2f >::_type("Vec2f" , "BaseType");
DataType FieldDataTraits<Vec2d >::_type("Vec2d" , "BaseType");
DataType FieldDataTraits<Vec2ld>::_type("Vec2ld", "BaseType");
DataType FieldDataTraits<Vec3ub>::_type("Vec3ub", "BaseType");
#ifndef OSG_NO_INT8_PNT
DataType FieldDataTraits<Vec3b >::_type("Vec3b" , "BaseType");
#endif
DataType FieldDataTraits<Vec3us>::_type("Vec3us", "BaseType");
DataType FieldDataTraits<Vec3s >::_type("Vec3s" , "BaseType");
DataType FieldDataTraits<Vec3f >::_type("Vec3f" , "BaseType");
DataType FieldDataTraits<Vec3d >::_type("Vec3d" , "BaseType");
DataType FieldDataTraits<Vec3ld>::_type("Vec3ld", "BaseType");
DataType FieldDataTraits<Vec4ub>::_type("Vec4ub", "BaseType");
#ifndef OSG_NO_INT8_PNT
DataType FieldDataTraits<Vec4b >::_type("Vec4b" , "BaseType");
#endif
DataType FieldDataTraits<Vec4us>::_type("Vec4us", "BaseType");
DataType FieldDataTraits<Vec4s >::_type("Vec4s" , "BaseType");
DataType FieldDataTraits<Vec4f >::_type("Vec4f" , "BaseType");
DataType FieldDataTraits<Vec4d >::_type("Vec4d" , "BaseType");
DataType FieldDataTraits<Vec4ld>::_type("Vec4ld", "BaseType");
DataType FieldDataTraits<Pnt2ub>::_type("Pnt2ub", "BaseType");
#ifndef OSG_NO_INT8_PNT
DataType FieldDataTraits<Pnt2b >::_type("Pnt2b" , "BaseType");
#endif
DataType FieldDataTraits<Pnt2us>::_type("Pnt2us", "BaseType");
DataType FieldDataTraits<Pnt2s >::_type("Pnt2s" , "BaseType");
DataType FieldDataTraits<Pnt2f >::_type("Pnt2f" , "BaseType");
DataType FieldDataTraits<Pnt2d >::_type("Pnt2d" , "BaseType");
DataType FieldDataTraits<Pnt2ld>::_type("Pnt2ld", "BaseType");
DataType FieldDataTraits<Pnt3ub>::_type("Pnt3ub", "BaseType");
#ifndef OSG_NO_INT8_PNT
DataType FieldDataTraits<Pnt3b >::_type("Pnt3b" , "BaseType");
#endif
DataType FieldDataTraits<Pnt3us>::_type("Pnt3us", "BaseType");
DataType FieldDataTraits<Pnt3s >::_type("Pnt3s" , "BaseType");
DataType FieldDataTraits<Pnt3f >::_type("Pnt3f" , "BaseType");
DataType FieldDataTraits<Pnt3d >::_type("Pnt3d" , "BaseType");
DataType FieldDataTraits<Pnt3ld>::_type("Pnt3ld", "BaseType");
DataType FieldDataTraits<Pnt4ub>::_type("Pnt4ub", "BaseType");
#ifndef OSG_NO_INT8_PNT
DataType FieldDataTraits<Pnt4b >::_type("Pnt4b" , "BaseType");
#endif
DataType FieldDataTraits<Pnt4us>::_type("Pnt4us", "BaseType");
DataType FieldDataTraits<Pnt4s >::_type("Pnt4s" , "BaseType");
DataType FieldDataTraits<Pnt4f >::_type("Pnt4f" , "BaseType");
DataType FieldDataTraits<Pnt4d >::_type("Pnt4d" , "BaseType");
DataType FieldDataTraits<Pnt4ld>::_type("Pnt4ld", "BaseType");

DataType FieldDataTraits<Matrix    >::_type("Matrix"    , "BaseType");
DataType FieldDataTraits<Matrix4d  >::_type("Matrix4d"  , "BaseType");
DataType FieldDataTraits<Quaternion>::_type("Quaternion", "BaseType");

DataType FieldDataTraits<Plane>::_type("Plane", "BaseType");

#endif //!defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

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
OSG_DLLEXPORT_SFIELD_DEF1(void *, OSG_BASE_DLLTMPLMAPPING);

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
OSG_DLLEXPORT_MFIELD_DEF1(void *, OSG_BASE_DLLTMPLMAPPING);

OSG_DLLEXPORT_SFIELD_DEF1(std::string,   OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF2(Time, 1,       OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Color3f,       OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Color4f,       OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Color3ub,      OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Color4ub,      OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(DynamicVolume, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF2(BitVector, 1,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF2(GLenum,    1,  OSG_BASE_DLLTMPLMAPPING);

OSG_DLLEXPORT_MFIELD_DEF1(std::string,   OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF2(Time, 1,       OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Color3f,       OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Color4f,       OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Color3ub,      OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Color4ub,      OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(DynamicVolume, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF2(BitVector, 1,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF2(GLenum,    1,  OSG_BASE_DLLTMPLMAPPING);


OSG_DLLEXPORT_SFIELD_DEF1(Vec2ub, OSG_BASE_DLLTMPLMAPPING);
#ifndef OSG_NO_INT8_PNT
OSG_DLLEXPORT_SFIELD_DEF1(Vec2b,  OSG_BASE_DLLTMPLMAPPING);
#endif
OSG_DLLEXPORT_SFIELD_DEF1(Vec2us, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Vec2s,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Vec2f,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Vec2d,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Vec2ld, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Vec3ub, OSG_BASE_DLLTMPLMAPPING);
#ifndef OSG_NO_INT8_PNT
OSG_DLLEXPORT_SFIELD_DEF1(Vec3b,  OSG_BASE_DLLTMPLMAPPING);
#endif
OSG_DLLEXPORT_SFIELD_DEF1(Vec3us, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Vec3s,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Vec3f,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Vec3d,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Vec3ld, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Vec4ub, OSG_BASE_DLLTMPLMAPPING);
#ifndef OSG_NO_INT8_PNT
OSG_DLLEXPORT_SFIELD_DEF1(Vec4b,  OSG_BASE_DLLTMPLMAPPING);
#endif
OSG_DLLEXPORT_SFIELD_DEF1(Vec4us, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Vec4s,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Vec4f,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Vec4d,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Vec4ld, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Pnt2ub, OSG_BASE_DLLTMPLMAPPING);
#ifndef OSG_NO_INT8_PNT
OSG_DLLEXPORT_SFIELD_DEF1(Pnt2b,  OSG_BASE_DLLTMPLMAPPING);
#endif
OSG_DLLEXPORT_SFIELD_DEF1(Pnt2us, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Pnt2s,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Pnt2f,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Pnt2d,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Pnt2ld, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Pnt3ub, OSG_BASE_DLLTMPLMAPPING);
#ifndef OSG_NO_INT8_PNT
OSG_DLLEXPORT_SFIELD_DEF1(Pnt3b,  OSG_BASE_DLLTMPLMAPPING);
#endif
OSG_DLLEXPORT_SFIELD_DEF1(Pnt3us, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Pnt3s,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Pnt3f,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Pnt3d,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Pnt3ld, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Pnt4ub, OSG_BASE_DLLTMPLMAPPING);
#ifndef OSG_NO_INT8_PNT
OSG_DLLEXPORT_SFIELD_DEF1(Pnt4b,  OSG_BASE_DLLTMPLMAPPING);
#endif
OSG_DLLEXPORT_SFIELD_DEF1(Pnt4us, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Pnt4s,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Pnt4f,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Pnt4d,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Pnt4ld, OSG_BASE_DLLTMPLMAPPING);

OSG_DLLEXPORT_MFIELD_DEF1(Vec2ub, OSG_BASE_DLLTMPLMAPPING);
#ifndef OSG_NO_INT8_PNT
OSG_DLLEXPORT_MFIELD_DEF1(Vec2b,  OSG_BASE_DLLTMPLMAPPING);
#endif
OSG_DLLEXPORT_MFIELD_DEF1(Vec2us, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Vec2s,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Vec2f,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Vec2d,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Vec2ld, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Vec3ub, OSG_BASE_DLLTMPLMAPPING);
#ifndef OSG_NO_INT8_PNT
OSG_DLLEXPORT_MFIELD_DEF1(Vec3b,  OSG_BASE_DLLTMPLMAPPING);
#endif
OSG_DLLEXPORT_MFIELD_DEF1(Vec3us, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Vec3s,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Vec3f,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Vec3d,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Vec3ld, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Vec4ub, OSG_BASE_DLLTMPLMAPPING);
#ifndef OSG_NO_INT8_PNT
OSG_DLLEXPORT_MFIELD_DEF1(Vec4b,  OSG_BASE_DLLTMPLMAPPING);
#endif
OSG_DLLEXPORT_MFIELD_DEF1(Vec4us, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Vec4s,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Vec4f,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Vec4d,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Vec4ld, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Pnt2ub, OSG_BASE_DLLTMPLMAPPING);
#ifndef OSG_NO_INT8_PNT
OSG_DLLEXPORT_MFIELD_DEF1(Pnt2b,  OSG_BASE_DLLTMPLMAPPING);
#endif
OSG_DLLEXPORT_MFIELD_DEF1(Pnt2us, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Pnt2s,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Pnt2f,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Pnt2d,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Pnt2ld, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Pnt3ub, OSG_BASE_DLLTMPLMAPPING);
#ifndef OSG_NO_INT8_PNT
OSG_DLLEXPORT_MFIELD_DEF1(Pnt3b,  OSG_BASE_DLLTMPLMAPPING);
#endif
OSG_DLLEXPORT_MFIELD_DEF1(Pnt3us, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Pnt3s,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Pnt3f,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Pnt3d,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Pnt3ld, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Pnt4ub, OSG_BASE_DLLTMPLMAPPING);
#ifndef OSG_NO_INT8_PNT
OSG_DLLEXPORT_MFIELD_DEF1(Pnt4b,  OSG_BASE_DLLTMPLMAPPING);
#endif
OSG_DLLEXPORT_MFIELD_DEF1(Pnt4us, OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Pnt4s,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Pnt4f,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Pnt4d,  OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Pnt4ld, OSG_BASE_DLLTMPLMAPPING);


OSG_DLLEXPORT_SFIELD_DEF1(Matrix,     OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Matrix4d,   OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(Quaternion, OSG_BASE_DLLTMPLMAPPING);

OSG_DLLEXPORT_MFIELD_DEF1(Matrix,     OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Matrix4d,   OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Quaternion, OSG_BASE_DLLTMPLMAPPING);

OSG_DLLEXPORT_SFIELD_DEF1(Plane,       OSG_BASE_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(Plane,       OSG_BASE_DLLTMPLMAPPING);

OSG_END_NAMESPACE


OSG_USING_NAMESPACE

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
