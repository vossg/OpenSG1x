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

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGMFVecTypes.h
    \ingroup GrpBaseField
    \ingroup GrpBaseFieldMulti
 */
#endif

OSG_BEGIN_NAMESPACE


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec2f> MFVec2f;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(MField, Vec2f, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec3f> MFVec3f;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(MField, Vec3f, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec4f> MFVec4f;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(MField, Vec4f, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec4ub> MFVec4ub;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(MField, Vec4ub, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt2f> MFPnt2f;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(MField, Pnt2f, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt2d> MFPnt2d;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(MField, Pnt2d, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt3f> MFPnt3f;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(MField, Pnt3f, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt3d> MFPnt3d;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(MField, Pnt3d, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt4f> MFPnt4f;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(MField, Pnt4f, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt4d> MFPnt4d;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(MField, Pnt4d, OSG_BASE_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#endif /* _OSGSFVECBASE_H_ */




