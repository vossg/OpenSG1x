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

#define OSG_COMPILESYSTEMLIB
#define OSG_COMPILEFIELDINST

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <map>
#include <OSGAttachment.h>

#include "OSGSFBaseTypes.h"
#include "OSGMFBaseTypes.h"
#include "OSGSFSysTypes.h"
#include "OSGMFSysTypes.h"
#include "OSGSFVecTypes.h"
#include "OSGMFVecTypes.h"
#include "OSGSFFieldContainerTypes.h"
#include "OSGMFFieldContainerTypes.h"
#include "OSGSFMathTypes.h"
#include "OSGMFMathTypes.h"

OSG_BEGIN_NAMESPACE

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


#pragma instantiate SField<FieldContainerPtr>::_fieldType
#pragma instantiate SField<NodePtr          >::_fieldType
#pragma instantiate SField<NodeCorePtr      >::_fieldType
#pragma instantiate SField<AttachmentMap    >::_fieldType

#pragma instantiate MField<FieldContainerPtr>::_fieldType
#pragma instantiate MField<NodePtr          >::_fieldType
#pragma instantiate MField<NodeCorePtr      >::_fieldType
#pragma instantiate MField<AttachmentMap    >::_fieldType


#pragma instantiate SField<Matrix    >::_fieldType
#pragma instantiate SField<Quaternion>::_fieldType

#pragma instantiate MField<Matrix    >::_fieldType
#pragma instantiate MField<Quaternion>::_fieldType

#pragma instantiate SField<Plane>::_fieldType
#pragma instantiate MField<Plane>::_fieldType

#else

OSG_DLLEXPORT_DEF2(SField, Bool  , 2, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField,  Int8 , OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, UInt8 , OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField,  Int16, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, UInt16, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField,  Int32, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, UInt32, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField,  Int64, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, UInt64, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, Real32, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, Real64, OSG_SYSTEMLIB_DLLTMPLMAPPING)

OSG_DLLEXPORT_DEF2(MField, Bool  , 2, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField,  Int8 , OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, UInt8 , OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField,  Int16, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, UInt16, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField,  Int32, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, UInt32, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField,  Int64, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, UInt64, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Real32, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Real64, OSG_SYSTEMLIB_DLLTMPLMAPPING)




OSG_DLLEXPORT_DEF1(SField, String,        OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF2(SField, Time, 1,       OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, Color3f,       OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, Color4f,       OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, Color3ub,      OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, Color4ub,      OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, DynamicVolume, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF2(SField, BitVector, 1,  OSG_SYSTEMLIB_DLLTMPLMAPPING)

OSG_DLLEXPORT_DEF1(MField, String,        OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF2(MField, Time, 1,       OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Color3f,       OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Color4f,       OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Color3ub,      OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Color4ub,      OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, DynamicVolume, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF2(MField, BitVector, 1,  OSG_SYSTEMLIB_DLLTMPLMAPPING)



OSG_DLLEXPORT_DEF1(SField, Vec2f, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, Vec3f, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, Vec4f, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, Pnt2f, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, Pnt3f, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, Pnt4f, OSG_SYSTEMLIB_DLLTMPLMAPPING)

OSG_DLLEXPORT_DEF1(MField, Vec2f, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Vec3f, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Vec4f, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Pnt2f, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Pnt3f, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Pnt4f, OSG_SYSTEMLIB_DLLTMPLMAPPING)

OSG_DLLEXPORT_DEF1(MField, Vec4ub, OSG_SYSTEMLIB_DLLTMPLMAPPING)



OSG_DLLEXPORT_DEF1(SField, FieldContainerPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, NodePtr,           OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, NodeCorePtr,       OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, AttachmentMap,     OSG_SYSTEMLIB_DLLTMPLMAPPING)

OSG_DLLEXPORT_DEF1(MField, FieldContainerPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, NodePtr,           OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, NodeCorePtr,       OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, AttachmentMap,     OSG_SYSTEMLIB_DLLTMPLMAPPING)


OSG_DLLEXPORT_DEF1(SField, Matrix,     OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, Quaternion, OSG_SYSTEMLIB_DLLTMPLMAPPING)

OSG_DLLEXPORT_DEF1(MField, Matrix,     OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Quaternion, OSG_SYSTEMLIB_DLLTMPLMAPPING)

OSG_DLLEXPORT_DEF1(SField, Plane,	OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Plane,	OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif


OSG_END_NAMESPACE
