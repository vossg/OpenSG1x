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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGSystemDef.h>
#include <OSGSField.h>
#include <OSGBaseFieldDataType.h>

/** \file OSGSFBaseTypes.h
 *  \ingroup FieldLib
 *  \ingroup SingleFields
 *  \brief OpenSG base single fields
 *
 * <UL>
 * <LI> osg::SFString
 * <LI> osg::SFTime
 * <LI> osg::SFColor3f
 * <LI> osg::SFColor4f
 * <LI> osg::SFColor3ub
 * <LI> osg::SFColor4ub
 * <LI> osg::SFDynamicVolume
 * </UL>
 */

OSG_BEGIN_NAMESPACE

/** \brief SFString
 */

typedef SField<String>        SFString;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<String>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, String, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

/** \brief SFTime
 */

typedef SField<Time, 1>       SFTime;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<Time, 1>::_fieldType

#else

OSG_DLLEXPORT_DECL2(SField,Time, 1, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

/** \brief SFColor3f
 */

typedef SField<Color3f>       SFColor3f;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<Color3f>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, Color3f, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

/** \brief SFColor4f
 */

typedef SField<Color4f>       SFColor4f;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<Color4f>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, Color4f, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

/** \brief SFColor3ub
 */

typedef SField<Color3ub>       SFColor3ub;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<Color3ub>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, Color3ub, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

/** \brief SFColor4ub
 */

typedef SField<Color4ub>       SFColor4ub;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<Color4ub>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, Color4ub, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

/** \brief SFDynamicVolume
 */

typedef SField<DynamicVolume> SFDynamicVolume;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<DynamicVolume>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, DynamicVolume, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

/** \brief SFBitVector
 */

typedef SField<BitVector, 1>  SFBitVector;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<BitVector, 1>::_fieldType

#else

OSG_DLLEXPORT_DECL2(SField, BitVector, 1, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

/** \brief SFPlane
 */

typedef SField<Plane> SFPlane;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<Plane>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, Plane, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

OSG_END_NAMESPACE

#endif /* _OSGSFVECBASE_H_ */
