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

#ifndef _OSGMFBASETYPES_H_
#define _OSGMFBASETYPES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBase.h>
#include <OSGMField.h>
#include <OSGBaseFieldDataType.h>

/** \file OSGMFBaseTypes.h
 *  \ingroup FieldLib
 *  \ingroup MultiFields
 *  \brief OpenSG base multi fields
 *
 * <UL>
 * <LI> osg::MFString
 * <LI> osg::MFTime
 * <LI> osg::MFColor3f
 * <LI> osg::MFColor4f
 * <LI> osg::MFVolume
 * </UL>
 */

OSG_BEGIN_NAMESPACE

/** \brief MFString
 */

typedef MField<string> MFString;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<string>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, string, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif

/** \brief MFTime
 */

typedef MField<Time, 1> MFTime;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<Time, 1>::_fieldType

#else

OSG_DLLEXPORT_DECL2(MField, Time, 1, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif

/** \brief MFColor3f
 */

typedef MField<Color3f> MFColor3f;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<Color3f>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, Color3f, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif

/** \brief MFColor4f
 */

typedef MField<Color4f> MFColor4f;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<Color4f>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, Color4f, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif

/** \brief MFColor3ub
 */

typedef MField<Color3ub> MFColor3ub;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<Color3ub>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, Color3ub, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif

/** \brief MFColor4ub
 */

typedef MField<Color4ub> MFColor4ub;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<Color4ub>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, Color4ub, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif


/** \brief MFVolume
 */

typedef MField<DynamicVolume> MFVolume;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<DynamicVolume>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, DynamicVolume, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif

/** \brief MFBitVector
 */

typedef MField<BitVector, 1>  MFBitVector;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<BitVector>::_fieldType

#else

OSG_DLLEXPORT_DECL2(MField, BitVector, 1, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif

/** \brief MFPlane
 */

typedef MField<Plane> MFPlane;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<Plane>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, Plane, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif

OSG_END_NAMESPACE

#define OSGMFBASETYPES_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGMFBASETYPES_H_ */







