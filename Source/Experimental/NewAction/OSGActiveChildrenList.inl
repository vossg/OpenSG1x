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

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*    NOTE NOTE                                                            */
/* ActiveChildrenList::ChildrenListEntry must be defined first, because    */
/* the rest depends on the definition for inlining.                        */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/*    PRIVATE Types                                                        */

inline
ActiveChildrenList::ChildrenListEntry::ChildrenListEntry(void)
    : _bActive (true                                      ),
      _priority(TypeTraits<PriorityType>::getZeroElement())
{
}

inline
ActiveChildrenList::ChildrenListEntry::ChildrenListEntry(bool         bActive,
                                                         PriorityType priority)
    : _bActive (bActive ),
      _priority(priority)
{
}

inline bool
ActiveChildrenList::ChildrenListEntry::getActive(void) const
{
    return _bActive;
}

inline void
ActiveChildrenList::ChildrenListEntry::setActive(bool bActive)
{
    _bActive = bActive;
}

inline ActiveChildrenList::PriorityType
ActiveChildrenList::ChildrenListEntry::getPriority(void) const
{
    return _priority;
}

inline void
ActiveChildrenList::ChildrenListEntry::setPriority(PriorityType priority)
{
    _priority = priority;
}

/*-------------------------------------------------------------------------*/
/*    NOTE NOTE                                                            */
/* The following four methods must be defined first, because the other     */
/* ones depend on the definition for inlining.                             */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/*    Children Iterator Access                                             */

inline ActiveChildrenList::MFNodePtrConstIt
ActiveChildrenList::beginChildren(void) const
{
    return _pParentNode->getMFChildren()->begin();
}

inline ActiveChildrenList::MFNodePtrIt
ActiveChildrenList::beginChildren(void)
{
    return _pParentNode->getMFChildren()->begin();
}

inline ActiveChildrenList::MFNodePtrConstIt
ActiveChildrenList::endChildren(void) const
{
    return _pParentNode->getMFChildren()->end();
}

inline ActiveChildrenList::MFNodePtrIt
ActiveChildrenList::endChildren(void)
{
    return _pParentNode->getMFChildren()->end();
}

/*-------------------------------------------------------------------------*/
/*    Constructors                                                         */

inline
ActiveChildrenList::ActiveChildrenList(void)
    : _pParentNode(NullFC),
      _uiNumActive(0     ),
      _children   (      )
{
}

inline
ActiveChildrenList::ActiveChildrenList(const NodePtr &pParentNode)
    : _pParentNode(pParentNode                ),
      _uiNumActive(pParentNode->getNChildren()),
      _children   (pParentNode->getNChildren())
{
}

/*-------------------------------------------------------------------------*/
/*    Destructor                                                           */

inline
ActiveChildrenList::~ActiveChildrenList(void)
{
}

/*-------------------------------------------------------------------------*/
/*    Parent Access                                                        */

inline void
ActiveChildrenList::buildList(void)
{
    _uiNumActive = _pParentNode->getNChildren();

    _children.assign(_pParentNode->getNChildren(), ChildrenListEntry());
}

inline NodePtr
ActiveChildrenList::getParentNode(void) const
{
    return _pParentNode;
}

inline void
ActiveChildrenList::setParentNode(const NodePtr &pParentNode)
{
    _pParentNode = pParentNode;
}

inline UInt32
ActiveChildrenList::getNumActive(void) const
{
    return _uiNumActive;
}

/*-------------------------------------------------------------------------*/
/*    Children Active Access                                               */

inline bool
ActiveChildrenList::getActive(MFNodePtrConstIt itChild) const
{
    return _children[itChild - beginChildren()].getActive();
}

inline bool
ActiveChildrenList::getActive(UInt32 uiIndex) const
{
    return _children[uiIndex].getActive();
}

inline void
ActiveChildrenList::setActive(MFNodePtrConstIt itChild, bool bActive)
{
    if((_children[itChild - beginChildren()].getActive() == true ) &&
       (bActive                                          == false)   )
    {
        --_uiNumActive;
    }
    else if((_children[itChild - beginChildren()].getActive() == false) &&
            (bActive                                          == true )   )
    {
        ++_uiNumActive;
    }

    _children[itChild - beginChildren()].setActive(bActive);
}

inline void
ActiveChildrenList::setActive(UInt32 uiIndex, bool bActive)
{
    if((_children[uiIndex].getActive() == true ) &&
       (bActive                        == false)   )
    {
        --_uiNumActive;
    }
    else if((_children[uiIndex].getActive() == false) &&
            (bActive                        == true )   )
    {
        ++_uiNumActive;
    }

    _children[uiIndex].setActive(bActive);
}

/*-------------------------------------------------------------------------*/
/*    Children Priority Access                                             */

inline ActiveChildrenList::PriorityType
ActiveChildrenList::getPriority(MFNodePtrConstIt itChild) const
{
    return _children[itChild - beginChildren()].getPriority();
}

inline ActiveChildrenList::PriorityType
ActiveChildrenList::getPriority(UInt32 uiIndex) const
{
    return _children[uiIndex].getPriority();
}

inline void
ActiveChildrenList::setPriority(
    MFNodePtrConstIt itChild, PriorityType priority)
{
    _children[itChild - beginChildren()].setPriority(priority);
}

inline void
ActiveChildrenList::setPriority(
    UInt32 uiIndex, PriorityType priority)
{
    _children[uiIndex].setPriority(priority);
}

OSG_END_NAMESPACE

#define OSGACTIVECHILDRENLIST_INLINE_CVSID "@(#)$Id: OSGActiveChildrenList.inl,v 1.1 2004/04/20 13:47:08 neumannc Exp $"
