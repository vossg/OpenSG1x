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

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGContainerTypeInst.cpp
    \ingroup GrpSystemField
 */
#endif

#define OSG_COMPILECONTAINERFIELDINST

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <OSGField.h>
#include <OSGSField.h>
#include <OSGMField.h>

#include <OSGAttachmentContainerPtr.h>
#include <OSGNodePtr.h>

#include "OSGFieldContainer.h"

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

#include "OSGMFieldTypeDef.inl"
#include "OSGSFieldTypeDef.inl"

OSG_BEGIN_NAMESPACE

DataType FieldDataTraits<FieldContainerPtr     >::_type(
    "FieldContainerPtr",
    NULL);

DataType FieldDataTraits<AttachmentContainerPtr>::_type(
    "AttachmentContainerPtr", 
    "FieldContainerPtr");

DataType FieldDataTraits<NodePtr               >::_type(
    "NodePtr",
    "AttachmentContainerPtr");

DataType FieldDataTraits<NodeCorePtr           >::_type(
    "NodeCorePtr",
    "AttachmentContainerPtr");

DataType FieldDataTraits<AttachmentPtr         >::_type(
    "AttachmentPtr",
    "FieldContainerPtr");

DataType FieldDataTraits<AttachmentMap         >::_type(
    "AttachmentMap",
    NULL);

OSG_DLLEXPORT_SFIELD_DEF1(FieldContainerPtr,     OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(AttachmentContainerPtr,OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(NodePtr,               OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(NodeCorePtr,           OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(AttachmentPtr,         OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(AttachmentMap,         OSG_SYSTEMLIB_DLLTMPLMAPPING);

OSG_DLLEXPORT_MFIELD_DEF1(FieldContainerPtr,     OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(AttachmentContainerPtr,OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(NodePtr,               OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(NodeCorePtr,           OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(AttachmentPtr,         OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(AttachmentMap,         OSG_SYSTEMLIB_DLLTMPLMAPPING);

OSG_END_NAMESPACE

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif


namespace 
{
   static Char8 cvsid_cpp[] = "@(#)$Id: $";

   static Char8 cvsid_sffcptr_hpp[] = OSGSFFIELDCONTAINERPTR_HEADER_CVSID;
   static Char8 cvsid_mffcptr_hpp[] = OSGMFFIELDCONTAINERPTR_HEADER_CVSID;

   static Char8 cvsid_sfacptr_hpp[] = OSGSFATTACHMENTCONTAINERPTR_HEADER_CVSID;
   static Char8 cvsid_mfacptr_hpp[] = OSGMFATTACHMENTCONTAINERPTR_HEADER_CVSID;

   static Char8 cvsid_sfndptr_hpp[] = OSGSFNODEPTR_HEADER_CVSID;
   static Char8 cvsid_mfndptr_hpp[] = OSGMFNODEPTR_HEADER_CVSID;

   static Char8 cvsid_sfncptr_hpp[] = OSGSFNODECOREPTR_HEADER_CVSID;
   static Char8 cvsid_mfncptr_hpp[] = OSGMFNODECOREPTR_HEADER_CVSID;

   static Char8 cvsid_sfatptr_hpp[] = OSGSFATTACHMENTPTR_HEADER_CVSID;
   static Char8 cvsid_mfatptr_hpp[] = OSGMFATTACHMENTPTR_HEADER_CVSID;

   static Char8 cvsid_sfattma_hpp[] = OSGSFATTACHMENTMAP_HEADER_CVSID;
   static Char8 cvsid_mfattma_hpp[] = OSGMFATTACHMENTMAP_HEADER_CVSID;
}
