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

#ifndef _OSGMFVECTYPES_H_
#define _OSGMFVECTYPES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBase.h>
#include <OSGMField.h>
#include <OSGVecFieldDataType.h>

/*! \file OSGMFVecTypes.h
    \ingroup FieldLib
    \ingroup MultiFields
    \brief OpenSG vector and point multi fields
 */

OSG_BEGIN_NAMESPACE


/*! \brief MFVec2f
    \ingroup MultiFields
*/

typedef MField<Vec2f> MFVec2f;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<Vec2f>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, Vec2f, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif


/*! \brief MFVec3f
    \ingroup MultiFields
*/

typedef MField<Vec3f> MFVec3f;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<Vec3f>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, Vec3f, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif


/*! \brief MFVec4f
    \ingroup MultiFields
*/

typedef MField<Vec4f> MFVec4f;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<Vec4f>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, Vec4f, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif


/*! \brief MFVec4ub
    \ingroup MultiFields
*/

typedef MField<Vec4ub> MFVec4ub;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<Vec4ub>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, Vec4ub, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif


/*! \brief MFPnt2f
    \ingroup MultiFields
*/

typedef MField<Pnt2f> MFPnt2f;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<Pnt2f>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, Pnt2f, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif


/*! \brief MFPnt2d
    \ingroup MultiFields
*/

typedef MField<Pnt2d> MFPnt2d;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<Pnt2d>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, Pnt2d, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif


/*! \brief MFPnt3f
    \ingroup MultiFields
*/

typedef MField<Pnt3f> MFPnt3f;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<Pnt3f>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, Pnt3f, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif


/*! \brief MFPnt3d
    \ingroup MultiFields
*/

typedef MField<Pnt3d> MFPnt3d;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<Pnt3d>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, Pnt3d, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif


/*! \brief MFPnt4f
    \ingroup MultiFields
*/

typedef MField<Pnt4f> MFPnt4f;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<Pnt4f>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, Pnt4f, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif


/*! \brief MFPnt4d
    \ingroup MultiFields
*/

typedef MField<Pnt4d> MFPnt4d;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<Pnt4d>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, Pnt4d, OSG_BASE_DLLTMPLMAPPING)

#endif
#endif

OSG_END_NAMESPACE

#endif /* _OSGSFVECBASE_H_ */




