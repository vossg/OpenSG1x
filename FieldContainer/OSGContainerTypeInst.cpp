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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#define OSG_COMPILESYSTEMLIB
#define OSG_COMPILECONTAINERFIELDINST

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <OSGField.h>
#include <OSGSField.h>
#include <OSGMField.h>

#include "OSGSFFieldContainerPtr.h"
#include "OSGMFFieldContainerPtr.h"

#include "OSGSFAttachmentContainerPtr.h"
#include "OSGMFAttachmentContainerPtr.h"

#include "OSGSFNodePtr.h"
#include "OSGMFNodePtr.h"

#include "OSGSFNodeCorePtr.h"
#include "OSGMFNodeCorePtr.h"

#include "OSGSFAttachmentPtr.h"
#include "OSGMFAttachmentPtr.h"

#include "OSGSFAttachmentMap.h"
#include "OSGMFAttachmentMap.h"

OSG_BEGIN_NAMESPACE

#if defined(__sgi)

DataType FieldDataTraits<FieldContainerPtr     >::_type(
    "FieldContainerPtr",
    true);

DataType FieldDataTraits<AttachmentContainerPtr>::_type(
    "AttachmenContainertPtr", 
    true);

DataType FieldDataTraits<NodePtr               >::_type(
    "NodePtr",
    true);

DataType FieldDataTraits<NodeCorePtr           >::_type(
    "NodeCorePtr",
    true);

DataType FieldDataTraits<AttachmentPtr         >::_type(
    "AttachmentPtr",
    true);

DataType FieldDataTraits<AttachmentMap         >::_type(
    "AttachmentMap",
    true);

#pragma instantiate SField<FieldContainerPtr     >::_fieldType
#pragma instantiate SField<AttachmentContainerPtr>::_fieldType
#pragma instantiate SField<NodePtr               >::_fieldType
#pragma instantiate SField<NodeCorePtr           >::_fieldType
#pragma instantiate SField<NodeCorePtr           >::_fieldType
#pragma instantiate SField<AttachmentPtr         >::_fieldType
#pragma instantiate SField<AttachmentMap         >::_fieldType

#pragma instantiate MField<FieldContainerPtr     >::_fieldType
#pragma instantiate MField<AttachmentContainerPtr>::_fieldType
#pragma instantiate MField<NodePtr               >::_fieldType
#pragma instantiate MField<NodeCorePtr           >::_fieldType
#pragma instantiate MField<AttachmentPtr         >::_fieldType
#pragma instantiate MField<AttachmentMap         >::_fieldType

#else

OSG_DLLEXPORT_DEF1(SField, FieldContainerPtr,     OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, AttachmentContainerPtr,OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, NodePtr,               OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, NodeCorePtr,           OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, AttachmentPtr,         OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, AttachmentMap,         OSG_SYSTEMLIB_DLLTMPLMAPPING)

OSG_DLLEXPORT_DEF1(MField, FieldContainerPtr,     OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, AttachmentContainerPtr,OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, NodePtr,               OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, NodeCorePtr,           OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, AttachmentPtr,         OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, AttachmentMap,         OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif

OSG_END_NAMESPACE

