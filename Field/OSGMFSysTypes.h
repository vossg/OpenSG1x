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

#ifndef _OSGMFSYSTYPES_H_
#define _OSGMFSYSTYPES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGSystemDef.h>
#include <OSGMField.h>
#include <OSGSysFieldDataType.h>

/** \file OSGMFSysTypes.h
 *  \ingroup FieldLib
 *  \ingroup MultiFields
 *  \brief OpenSG system multi fields
 *
 *  <UL>
 *  <LI> osg::MFBool
 *  <LI> osg::MFInt8
 *  <LI> osg::MFUInt8
 *  <LI> osg::MFInt16
 *  <LI> osg::MFUInt16
 *  <LI> osg::MFInt32
 *  <LI> osg::MFUInt32
 *  <LI> osg::MFInt64
 *  <LI> osg::MFUInt64
 *  <LI> osg::MFReal32
 *  <LI> osg::MFReal64
 *  </UL>
 */

OSG_BEGIN_NAMESPACE

/** \brief MFBool
 */

typedef MField<Bool, 2>   MFBool;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<Bool, 2>::_fieldType

#else

OSG_DLLEXPORT_DECL2(MField, Bool, 2, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

/** \brief MFInt8
 */

typedef MField<Int8>   MFInt8;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<Int8>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, Int8, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

/** \brief MFUInt8
 */

typedef MField<UInt8>  MFUInt8;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<UInt8>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, UInt8, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

/** \brief MFInt16
 */

typedef MField<Int16>  MFInt16;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<Int16>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, Int16, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

/** \brief MFUInt16
 */

typedef MField<UInt16> MFUInt16;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<UInt16>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, UInt16, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

/** \brief MFInt32
 */

typedef MField<Int32>  MFInt32;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<Int32>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, Int32, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

/** \brief MFUInt32
 */

typedef MField<UInt32> MFUInt32;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<UInt32>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, UInt32, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

/** \brief MFInt64
 */

typedef MField<Int64>  MFInt64;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<Int64>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, Int64, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

/** \brief MFUInt64
 */

typedef MField<UInt64> MFUInt64;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<UInt64>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, UInt64, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

/** \brief MFReal32
 */

typedef MField<Real32> MFReal32;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<Real32>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, Real32, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

/** \brief MFReal64
 */

typedef MField<Real64> MFReal64;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<Real64>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, Real64, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

OSG_END_NAMESPACE

#endif /* _OSGSFSYSTYPES_H_ */

















