/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#ifndef _OSGMFFIELDCONTAINERTYPES_H_
#define _OSGMFFIELDCONTAINERTYPES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGMField.h>
#include <OSGContainerFieldDataType.h>

/** \file OSGMFFieldContainerTypes.h
 *  \ingroup FieldLib
 *  \ingroup MultiFields
 *  \brief OpenSG  field container multi fields
 *
 * <UL>
 * <LI> osg::MFFieldContainerPtr
 * <LI> osg::MFNodePtr
 * <LI> osg::MFNodeCorePtr
 * <LI> osg::MFPropertyPtr
 * <LI> osg::MFAttachmentMap
 * </UL>
 */

OSG_BEGIN_NAMESPACE

/** \brief MFFieldContainerPtr
 */

typedef MField<FieldContainerPtr> MFFieldContainerPtr;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<FieldContainerPtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, FieldContainerPtr, OSG_FIELD_DLLTMPLMAPPING)

#endif
#endif

/** \brief MFNodePtr
 */

typedef MField<NodePtr>           MFNodePtr;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<NodePtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, NodePtr, OSG_FIELD_DLLTMPLMAPPING)

#endif
#endif

/** \brief MFNodeCorePtr
 */

typedef MField<NodeCorePtr>       MFNodeCorePtr;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<NodeCorePtr>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, NodeCorePtr, OSG_FIELD_DLLTMPLMAPPING)

#endif
#endif

/** \brief MFAttachmentMap
 */

typedef MField<AttachmentMap>     MFAttachmentMap;

#ifndef OSG_COMPILEFIELDINST
#if defined(__sgi)

#pragma do_not_instantiate MField<AttachmentMap>::_fieldType

#else

OSG_DLLEXPORT_DECL1(MField, AttachmentMap, OSG_FIELD_DLLTMPLMAPPING)

#endif
#endif


OSG_END_NAMESPACE

#endif /* _OSGMFFIELDCONTAINERTYPES_H_ */






