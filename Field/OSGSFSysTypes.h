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


#ifndef _OSGSFSYSTYPES_H_
#define _OSGSFSYSTYPES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBase.h>
#include <OSGSField.h>
#include <OSGSysFieldDataType.h>

/** \file OSGSFSysTypes.h
 *  \ingroup FieldLib
 *  \ingroup SingleFields
 *  \brief OpenSG system single fields
 *
 *  <UL>
 *  <LI> osg::SFBool
 *  <LI> osg::SFInt8
 *  <LI> osg::SFUInt8
 *  <LI> osg::SFInt16
 *  <LI> osg::SFUInt16
 *  <LI> osg::SFInt32
 *  <LI> osg::SFUInt32
 *  <LI> osg::SFInt64
 *  <LI> osg::SFUInt64
 *  <LI> osg::SFReal32
 *  <LI> osg::SFReal64
 *  </UL>
 */

OSG_BEGIN_NAMESPACE


/** \brief SFBool
 */

typedef SField<Bool, 2>   SFBool;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<Bool, 2>::_fieldType

#else

OSG_DLLEXPORT_DECL2(SField, Bool, 2, OSG_BASE_DLLTMPLMAPPING);

#endif
#endif

/** \brief SFInt8
 */

typedef SField<Int8>   SFInt8;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<Int8>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, Int8, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif

/** \brief SFUInt8
 */

typedef SField<UInt8>  SFUInt8;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<UInt8>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, UInt8, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif

/** \brief SFInt16
 */

typedef SField<Int16>  SFInt16;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<Int16>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, Int16, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif

/** \brief SFUInt16
 */

typedef SField<UInt16> SFUInt16;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<UInt16>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, UInt16, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif

/** \brief SFInt32
 */
typedef SField<Int32>  SFInt32;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<Int32>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, Int32, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif

/** \brief SFUInt32
 */

typedef SField<UInt32> SFUInt32;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<UInt32>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, UInt32, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif

/** \brief SFInt64
 */
typedef SField<Int64>  SFInt64;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<Int64>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, Int64, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif

/** \brief SFUInt64
 */

typedef SField<UInt64> SFUInt64;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<UInt64>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, UInt64, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif

/** \brief SFReal32
 */

typedef SField<Real32> SFReal32;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<Real32>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, Real32, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif

/** \brief SFReal64
 */

typedef SField<Real64> SFReal64;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<Real64>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, Real64, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif

OSG_END_NAMESPACE

#endif /* _OSGSFSYSTYPES_H_ */

















