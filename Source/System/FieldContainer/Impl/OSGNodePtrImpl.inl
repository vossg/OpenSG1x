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

#ifndef _OSGNODEPTRIMPL_INL_
#define _OSGNODEPTRIMPL_INL_

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGNodePtrImpl.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

inline
NodePtr::NodePtr(void) : 
    Inherited()
{
}

inline
NodePtr::NodePtr(const NodePtr &source) :
    Inherited(source)
{
}

inline
NodePtr::NodePtr(const NullFieldContainerPtr &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

inline
NodePtr::~NodePtr(void)
{
}

/*-------------------------------------------------------------------------*/
/*                           Container Access                              */

inline
Node *NodePtr::operator->(void)
{
#if 0
    return (Node *) getElemP(Thread::getAspect());
#else
    return reinterpret_cast<Node *>(Inherited::operator ->());
#endif
}

inline
Node *NodePtr::operator->(void) const
{
#if 0
    return (Node *) getElemP(Thread::getAspect());
#else
    return reinterpret_cast<Node *>(Inherited::operator ->());
#endif
}

inline
Node &NodePtr::operator *(void)
{
#if 0
    return *((Node *) getElemP(Thread::getAspect()));
#else
    return *(reinterpret_cast<Node *>(Inherited::operator ->()));
#endif
}

inline
Node &NodePtr::operator *(void) const
{
#if 0
    return *((Node *) getElemP(Thread::getAspect()));
#else
    return *(reinterpret_cast<Node *>(Inherited::operator ->()));
#endif
}

inline
Node *NodePtr::getCPtr(void)
{
#if 0
    return (Node *) getElemP(Thread::getAspect());
#else
    return reinterpret_cast<Node *>(Inherited::getCPtr());
#endif
}

inline
Node *NodePtr::getCPtr(void) const
{
#if 0
    return (Node *) getElemP(Thread::getAspect());
#else
    return reinterpret_cast<Node *>(Inherited::getCPtr());
#endif
}


/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

inline
void NodePtr::operator = (const NodePtr &source)
{
    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;
}

inline
void NodePtr::operator = (const NullFieldContainerPtr &source)
{
    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;
}


OSG_END_NAMESPACE

#define OSGNODEPTR_INLINE_CVSID "@(#)$Id: $"

#endif /* _OSGNODEPTRIMPL_INL_ */


