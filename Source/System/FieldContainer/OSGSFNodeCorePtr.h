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

#ifndef _OSGSFNODECOREPTR_H_
#define _OSGSFNODECOREPTR_H_
#ifdef __sgi
#pragma once
#endif

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGSFNodeCorePtr.h
    \ingroup GrpSystemField
    \ingroup GrpSystemFieldSingle
*/
#endif

#include <OSGSystemDef.h>
#include <OSGSField.h>
#include <OSGNodeCoreFieldDataType.h>

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpSystemFieldSingle */

typedef SField<NodeCorePtr> SFNodeCorePtr;
#endif

#ifndef OSG_COMPILECONTAINERFIELDINST

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 444 )
#endif

OSG_DLLEXPORT_DECL1(SField, NodeCorePtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#ifdef OSG_LINUX_ICC
#pragma warning( default : 444 )
#endif

#endif

OSG_END_NAMESPACE

#define OSGSFNODECOREPTR_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGSFNODECOREPTR_H_ */

