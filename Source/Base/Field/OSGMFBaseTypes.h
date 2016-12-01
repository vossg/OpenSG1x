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

#ifndef _OSGMFBASETYPES_H_
#define _OSGMFBASETYPES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGBase.h"
#include "OSGMField.h"
#include "OSGBaseFieldDataType.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGMFBaseTypes.h
    \ingroup GrpBaseField
    \ingroup GrpBaseFieldMulti
 */
#endif

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<std::string> MFString;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(MField, std::string, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Time, 1> MFTime;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL2(MField, Time, 1, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Color3f> MFColor3f;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(MField, Color3f, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Color4f> MFColor4f;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(MField, Color4f, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Color3ub> MFColor3ub;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(MField, Color3ub, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Color4ub> MFColor4ub;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(MField, Color4ub, OSG_BASE_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<DynamicVolume> MFVolume;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(MField, DynamicVolume, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<BoxVolume> MFBoxVolume;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(MField, BoxVolume, OSG_BASE_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<BitVector, 1>  MFBitVector;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL2(MField, BitVector, 1, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<GLenum, 1>  MFGLenum;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL2(MField, GLenum, 1, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Plane> MFPlane;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(MField, Plane, OSG_BASE_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#define OSGMFBASETYPES_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGMFBASETYPES_H_ */







