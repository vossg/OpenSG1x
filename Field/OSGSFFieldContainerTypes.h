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

#ifndef _OSGSFFIELDCONTAINERTYPES_H_
#define _OSGSFFIELDCONTAINERTYPES_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGSField.h>
#include <OSGContainerFieldDataType.h>

/** \file OSGSFFieldContainerTypes.h
 *  \ingroup FieldLib
 *  \ingroup SingleFields
 *  \brief OpenSG field container single fields
 *
 * <UL>
 * <LI> osg::SFFieldContainerPtr
 * <LI> osg::SFNodePtr
 * <LI> osg::SFNodeCorePtr
 * <LI> osg::SFPropertyPtr
 * <LI> osg::SFAttachmentMap;
 * </UL>
 */

OSG_BEGIN_NAMESPACE

/** \brief SFFieldContainerPtr
 */

typedef SField<FieldContainerPtr> SFFieldContainerPtr;

/** \brief SFNodePtr
 */

typedef SField<NodePtr>           SFNodePtr;

/** \brief SFNodeCorePtr
 */

typedef SField<NodeCorePtr>       SFNodeCorePtr;

/** \brief SFAttachmentMap
 */

typedef SField<AttachmentMap>     SFAttachmentMap;


OSG_END_NAMESPACE

#endif /* _OSGSFFIELDCONTAINERTYPES_H_ */
