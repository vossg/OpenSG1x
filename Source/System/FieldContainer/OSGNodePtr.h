/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000-2002,2002 by the OpenSG Forum                *
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

#ifndef _OSGNODEPTR_H_
#define _OSGNODEPTR_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGNodePtrImpl.h>
#include <OSGCNodePtrImpl.h>

#include <OSGNode.h>

#include <OSGNodePtrImpl.inl>
#include <OSGCNodePtrImpl.inl>

#include <OSGRefPtr.h>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemFieldContainerFuncs
 */

typedef RefPtr<NodePtr> NodeRefPtr;

template <class Core> inline 
NodePtr makeCoredNode(typename Core::Ptr *coreP = NULL);

template <class Core> inline 
NodePtr makeCoredNode(typename Core::Ptr *coreP)
{
    NodePtr            n = Node::create();
    typename Core::Ptr c = Core::create();

    beginEditCP(n, Node::CoreFieldMask);
    n->setCore(c);
    endEditCP(n, Node::CoreFieldMask);

    if(coreP != NULL)
        *coreP = c;
        
    return n;
}

OSG_END_NAMESPACE

#endif /* _OSGNODEPTR_H_ */
