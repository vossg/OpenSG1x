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

#ifndef _OSGFIELDCONTAINERPTRFORWARD_H_
#define _OSGFIELDCONTAINERPTRFORWARD_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBaseTypes.h>

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC)       

class FieldContainerPtrBase;

class FieldContainerPtr;

class NodePtr;
class CNodePtr;

template <class BasePtrTypeT, class FieldContainerTypeT> 
class FCPtr;

class AttachmentContainerPtr;

class NodeCore;
typedef FCPtr<AttachmentContainerPtr, NodeCore> NodeCorePtr;

class AttachmentPtr;

#endif

OSG_END_NAMESPACE

#define OSGFIELDCONTAINERPTRFORWARD_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGFIELDCONTAINERPTRFORWARD_H_ */
