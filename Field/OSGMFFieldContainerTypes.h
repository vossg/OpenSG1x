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

/** \brief MFNodePtr
 */

typedef MField<NodePtr>           MFNodePtr;

/** \brief MFNodeCorePtr
 */

typedef MField<NodeCorePtr>       MFNodeCorePtr;

/** \brief MFAttachmentMap
 */

typedef MField<AttachmentMap>     MFAttachmentMap;

OSG_END_NAMESPACE

#endif /* _OSGMFFIELDCONTAINERTYPES_H_ */
