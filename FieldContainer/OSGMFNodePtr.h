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

#ifndef _OSGMFNODEPTR_H_
#define _OSGMFNODEPTR_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGSystemDef.h>
#include <OSGMField.h>
#include <OSGNodeFieldDataType.h>

/*! \file OSGMFNodePtr.h
    \ingroup FieldLib
    \ingroup MultiFields
    \brief OpenSG field container multi fields
*/

OSG_BEGIN_NAMESPACE

/*! \brief MFNodePtr
    \ingroup MultiFields
*/

typedef MField<NodePtr> MFNodePtr;

#ifndef OSG_COMPILECONTAINERFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<NodePtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, NodePtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

OSG_END_NAMESPACE

#define OSGMFNODEPTR_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGMFNODEPTR_H_ */

