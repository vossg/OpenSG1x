/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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
/*! \file OSGCoredNodePtr.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <stdlib.h>
#include <stdio.h>

OSG_BEGIN_NAMESPACE


inline
CoredNodePtrBase::CoredNodePtrBase(void) : _node(NullFC)
{}

inline
CoredNodePtrBase::CoredNodePtrBase(NodePtr node)
{
    setNode(node);
}

inline
CoredNodePtrBase::~CoredNodePtrBase()
{
    setNode(NullFC);
}

inline
NodePtr CoredNodePtrBase::node(void) const
{ 
    return _node; 
}

inline
void CoredNodePtrBase::setNode(const NodePtr &node)
{
    if(_node == node)
        return;

    if(_node != NullFC)
        subRefCP(_node);

    _node = node;

    if(_node != NullFC)
        addRefCP(_node);
}

inline
void CoredNodePtrBase::setNode(const NullFieldContainerPtr &)
{
    if(_node != NullFC)
        subRefCP(_node);

    _node = NullFC;
}

// CoredNodePtr methods

template< class Core > inline
CoredNodePtr<Core>::CoredNodePtr(void) : 
    CoredNodePtrBase(NullFC), _core(NullFC)
{}

template< class Core > inline
CoredNodePtr<Core>::CoredNodePtr(const NodePtr& node) : 
    CoredNodePtrBase(node)
{
    setCore(Core::Ptr::dcast(CoredNodePtrBase::node()->getCore()));
}

template< class Core > inline
CoredNodePtr<Core>::CoredNodePtr(const NodeCorePtr& core) : 
    CoredNodePtrBase()
{
    setCore(Core::Ptr::dcast(core));
    updateNode();
}

template< class Core > inline
CoredNodePtr<Core>::CoredNodePtr(const typename Core::Ptr& core) : 
    CoredNodePtrBase()
{
    setCore(core);
    updateNode();
}

template< class Core > inline
CoredNodePtr<Core>::CoredNodePtr(const CoredNodePtr<Core>& ptr) : 
    CoredNodePtrBase()
{
    setCore(ptr._core);
    setNode(ptr.node());
}

template< class Core > inline
CoredNodePtr<Core>::~CoredNodePtr()
{
    setCore(NullFC);
    setNode(NullFC);
}

template< class Core > inline
CoredNodePtr<Core> CoredNodePtr<Core>::create(void)
{
    return CoredNodePtr<Core>(Core::create());
}

template< class Core > inline
void CoredNodePtr<Core>::coreChanged(void)
{
    setCore(node()->getCore());
}

template< class Core > inline
typename Core::Ptr CoredNodePtr<Core>::core(void) const
{
#ifdef OSG_DEBUG
    FFASSERT((node()->getCore() == _core), false, 
              ("CoredNodePtr::core: core changed!"););
#endif
    return _core;
}

template< class Core > inline
typename Core::Ptr& CoredNodePtr<Core>::operator->(void)
{
#ifdef OSG_DEBUG
    FFASSERT((node()->getCore() == _core), false, 
              ("CoredNodePtr::operator ->: core changed!"););
#endif
    return _core;
}

template< class Core > inline
CoredNodePtr<Core>::operator NodePtr()
{
#ifdef OSG_DEBUG
    FFASSERT((node()->getCore() == _core), false, 
              ("CoredNodePtr::operator NodePtr: core changed!"););
#endif
    return node();
}

template< class Core > inline
CoredNodePtr<Core>::operator typename Core::Ptr()
{
#ifdef OSG_DEBUG
    FFASSERT((node()->getCore() == _core), false, 
              ("CoredNodePtr::operator Core::Ptr: core changed!"););
#endif
    return _core;
}

/* Assignment. Create a new CNP if necessary */

template< class Core > inline
CoredNodePtr<Core>& CoredNodePtr<Core>::operator =(const NodePtr& node)
{
    setNode(node);
    setCore(Core::Ptr::dcast(node->getCore()));
    return *this;
}

template< class Core > inline
CoredNodePtr<Core>& CoredNodePtr<Core>::operator =(const typename Core::Ptr& core)
{
    setCore(core);
    updateNode();

    return *this;
}

template< class Core > inline
CoredNodePtr<Core>& CoredNodePtr<Core>::operator =(const CoredNodePtr<Core>& cnp)
{
    setNode(cnp.node());
    setCore(cnp._core);
    return *this;
}

template< class Core > inline
CoredNodePtr<Core>& CoredNodePtr<Core>::operator =(const NullFieldContainerPtr &)
{
    setNode(NullFC);
    setCore(NullFC);
    return *this;
}

template< class Core > inline
NodeCorePtr CoredNodePtr<Core>::getCoreV(void) const
{
    return _core;
}

template< class Core > inline
void CoredNodePtr<Core>::setCore(const NodeCorePtr &core)
{
    setCore(Core::Ptr::dcast(core));
}

template< class Core > inline
void CoredNodePtr<Core>::setCore(const typename Core::Ptr &core)
{
    if(_core == core)
        return;

    if(_core != NullFC)
        subRefCP(_core);

    _core = core;

    if(_core != NullFC)
        addRefCP(_core);
}

template< class Core > inline
void CoredNodePtr<Core>::setCore(const NullFieldContainerPtr&)
{
    if(_core != NullFC)
        subRefCP(_core);

    _core = NullFC;
}

template< class Core > inline
void CoredNodePtr<Core>::updateNode(void)
{
    if(node() == NullFC)
    {
        setNode(Node::create());
    }

    beginEditCP(node(), Node::CoreFieldMask);
    node()->setCore(_core);
    endEditCP(node(), Node::CoreFieldMask); 
}


// begin/endEdit functions. 

template< class Core > inline
void beginEditCP(const CoredNodePtr<Core> &objectP, 
                       BitVector         whichField,
                       UInt32            origin)
{
    beginEditCP(objectP.node(), whichField, origin);
    beginEditCP(objectP.core(), whichField, origin);   
}

template< class Core > inline
void endEditCP  (const CoredNodePtr<Core> &objectP, 
                       BitVector         whichField,
                       UInt32            origin)
{
    endEditCP(objectP.node(), whichField, origin);
    endEditCP(objectP.core(), whichField, origin);   
}


// Output operator

template< class Core >
inline std::ostream &operator << (std::ostream &str, 
                                  const CoredNodePtr<Core>& cnp)
{
    str << "CoredNodePtr<" << Core::getClassType().getName()
        << ">: Node: ";
    if(cnp.node())
    {
        str << cnp.node();
    }
    else
    {
        str << "(unset)";
    }
    
    str << " Core: ";
    if(cnp.node() && cnp.core())
    {
        str << cnp.core();
    }
    else
    {
        str << "(unset)";
    }
    
    return str;
}

OSG_END_NAMESPACE

#define OSGCOREDNODEPTR_INLINE_CVSID "@(#)$Id: OSGCoredNodePtr.inl,v 1.5 2005/05/31 19:53:45 dirk Exp $"

