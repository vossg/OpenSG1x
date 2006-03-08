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

#ifndef _OSGSFMATHTYPES_H_
#define _OSGSFMATHTYPES_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBase.h>
#include <OSGSField.h>
#include <OSGMathFieldDataType.h>

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGSFMathTypes.h
    \ingroup GrpBaseField
    \ingroup GrpBaseFieldSingle
 */
#endif

OSG_BEGIN_NAMESPACE


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Matrix>     SFMatrix;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(SField, Matrix, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Matrix4d>     SFMatrix4d;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(SField, Matrix4d, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Quaternion> SFQuaternion;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(SField, Quaternion, OSG_BASE_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#define OSGSFMATHTYPES_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGSFMATHTYPES_H_ */





