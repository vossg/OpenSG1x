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

#ifndef _OSGSFVECTYPES_H_
#define _OSGSFVECTYPES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBase.h>
#include <OSGSField.h>
#include <OSGVecFieldDataType.h>

/** \file OSGSFVecTypes.h
 *  \ingroup FieldLib
 *  \ingroup SingleFields
 *  \brief OpenSG vector and point single fields
 * 
 *  <UL>
 *  <LI> osg::SFVec2f
 *  <LI> osg::SFVec3f
 *  <LI> osg::SFVec4f
 *  <LI> osg::SFPnt2f
 *  <LI> osg::SFPnt3f
 *  <LI> osg::SFPnt3d
 *  <LI> osg::SFPnt4f
 *  </UL>
 */

OSG_BEGIN_NAMESPACE

/** \brief SFVec2f
 */

typedef SField<Vec2f> SFVec2f;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<Vec2f>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, Vec2f, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif

/** \brief SFVec3f
 */

typedef SField<Vec3f> SFVec3f;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<Vec3f>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, Vec3f, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif

/** \brief SFVec4f
 */

typedef SField<Vec4f> SFVec4f;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<Vec4f>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, Vec4f, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif

/** \brief SFPnt2f
 */

typedef SField<Pnt2f> SFPnt2f;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<Pnt2f>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, Pnt2f, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif

/** \brief SFPnt3f
 */

typedef SField<Pnt3f> SFPnt3f;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<Pnt3f>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, Pnt3f, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif


/** \brief SFPnt3d
 */

typedef SField<Pnt3d> SFPnt3d;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<Pnt3d>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, Pnt3d, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif

/** \brief SFPnt4f
 */

typedef SField<Pnt4f> SFPnt4f;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate SField<Pnt4f>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, Pnt4f, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif

OSG_END_NAMESPACE

#endif /* _OSGSFVECBASE_H_ */

