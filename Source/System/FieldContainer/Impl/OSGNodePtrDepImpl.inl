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

#ifndef _OSGNODEPTRDEPIMPL_INL_
#define _OSGNODEPTRDEPIMPL_INL_

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGNodePtrDepImpl.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

inline
NodePtr::NodePtr(const CNodePtr &source) :
    Inherited(source)
{
}

inline
NodePtr::NodePtr(const Node *source) :
    Inherited(source)
{
}

inline
NodePtr::NodePtr(const Node   *source,
                 const UInt16  uiSize,
                 const UInt16  uiParentPos) :

    Inherited(source, uiSize, uiParentPos)
{
}

template <class InTypeT> inline
NodePtr NodePtr::dcast(const InTypeT oIn)
{
    return NodePtr(
        (dynamic_cast<const Node *>(oIn.getCPtr())),
        oIn.getContainerSize(),
        oIn.getParentFieldPos());
}

inline
void NodePtr::operator = (const CNodePtr &source)
{
    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;
}

/*-------------------------------------------------------------------------*/
/*                              Pointer                                    */

inline
NodePtr::NodePtr(const Node &source) :
    Inherited(source)
{
}

inline
NodePtr Node::getPtr(void) const
{
    return NodePtr(*this);
}

inline
NodeCorePtr Node::getCore(void)
{
    return _sfCore.getValue();
}

inline
NodeCorePtr Node::getCore(void) const
{
    return _sfCore.getValue();
}

/*-------------------------------------------------------------------------*/
/*                                Core                                     */

inline
NodeCore *NodePtr::getCore(void)
{
    return ((Node *) getElemP(Thread::getAspect()))->getCore().getCPtr();
}

inline
NodeCore *NodePtr::getCore(void) const
{
    return ((Node *) getElemP(Thread::getAspect()))->getCore().getCPtr();
}

inline
void Node::onCreate(const Node *source)
{
    if(source == NULL)
        return;

    setCore(source->getCore());

    AttachmentMap::const_iterator fcI = 
        source->_attachmentMap.getValue().begin();
    AttachmentMap::const_iterator fcEnd = 
        source->_attachmentMap.getValue().end();

    while(fcI != fcEnd)
    {
        addAttachment((*fcI).second);

        ++fcI;
    }
}

OSG_FIELD_CONTAINER_INL_DEF(Node, NodePtr)

inline
NodePtr Node::clone(void)
{
    return cloneTree(getPtr());
}

OSG_END_NAMESPACE

#define OSGNODEPTRDEP_INLINE_CVSID "@(#)$Id: $"

#endif /* _OSGNODEPTRIMPL_INL_ */
