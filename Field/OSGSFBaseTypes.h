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

#ifndef _OSGSFBASETYPES_H_
#define _OSGSFBASETYPES_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBase.h>
#include <OSGSField.h>
#include <OSGBaseFieldDataType.h>

/*! \file OSGSFBaseTypes.h
    \ingroup FieldLib
    \ingroup SingleFields
    \brief OpenSG base single fields
*/

OSG_BEGIN_NAMESPACE


/*! \brief SFString
    \ingroup SingleFields
*/

typedef SField<string> SFString;

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(SField, string, OSG_BASE_DLLTMPLMAPPING)
#endif


/*! \brief SFTime
    \ingroup SingleFields
*/

typedef SField<Time, 1> SFTime;

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL2(SField,Time, 1, OSG_BASE_DLLTMPLMAPPING)
#endif


/*! \brief SFColor3f
    \ingroup SingleFields
*/

typedef SField<Color3f> SFColor3f;

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(SField, Color3f, OSG_BASE_DLLTMPLMAPPING)
#endif


/*! \brief SFColor4f
    \ingroup SingleFields
*/

typedef SField<Color4f> SFColor4f;

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(SField, Color4f, OSG_BASE_DLLTMPLMAPPING)
#endif


/*! \brief SFColor3ub
    \ingroup SingleFields
*/

typedef SField<Color3ub> SFColor3ub;

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(SField, Color3ub, OSG_BASE_DLLTMPLMAPPING)
#endif


/*! \brief SFColor4ub
    \ingroup SingleFields
*/

typedef SField<Color4ub> SFColor4ub;

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(SField, Color4ub, OSG_BASE_DLLTMPLMAPPING)
#endif


/*! \brief SFDynamicVolume
    \ingroup SingleFields
*/

typedef SField<DynamicVolume> SFDynamicVolume;

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(SField, DynamicVolume, OSG_BASE_DLLTMPLMAPPING)
#endif


/*! \brief SFBitVector
    \ingroup SingleFields
*/

typedef SField<BitVector, 1>  SFBitVector;

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL2(SField, BitVector, 1, OSG_BASE_DLLTMPLMAPPING)
#endif


/*! \brief SFPlane
    \ingroup SingleFields
*/

typedef SField<Plane> SFPlane;

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(SField, Plane, OSG_BASE_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#define OSGSFBASETYPES_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGSFBASETYPES_H_ */
