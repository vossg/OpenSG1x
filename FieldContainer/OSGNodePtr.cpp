/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGNodePtr.h"
#include "OSGThread.h"

#include "OSGNode.h"
#include "OSGNodeCore.h"

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class osg::NodePtr
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

NodePtr::NodePtr(void) :
    Inherited()
{
}

NodePtr::NodePtr(const NodePtr &source) :
    Inherited(source)
{
}

NodePtr::NodePtr(const NullFieldContainerPtr &source) :
    Inherited(source)
{
}

NodePtr::NodePtr(const CNodePtr &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

NodePtr::~NodePtr(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Core                                     */

NodeCore *NodePtr::getCore(void)
{
    return ((Node *) getElemP(Thread::getAspect()))->getCore().getCPtr();
}

NodeCore *NodePtr::getCore(void) const
{
    return ((Node *) getElemP(Thread::getAspect()))->getCore().getCPtr();
}

/*-------------------------------------------------------------------------*/
/*                           Container Access                              */

Node *NodePtr::operator->(void)
{
    return (Node *) getElemP(Thread::getAspect());
}

Node *NodePtr::operator->(void) const
{
    return (Node *) getElemP(Thread::getAspect());
}

Node &NodePtr::operator *(void)
{
    return *((Node *) getElemP(Thread::getAspect()));
}

Node &NodePtr::operator *(void) const
{
    return *((Node *) getElemP(Thread::getAspect()));
}

Node *NodePtr::getCPtr(void)
{
    return (Node *) getElemP(Thread::getAspect());
}

Node *NodePtr::getCPtr(void) const
{
    return (Node *) getElemP(Thread::getAspect());
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

void NodePtr::operator = (const CNodePtr &source)
{
    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;
}

void NodePtr::operator = (const NodePtr &source)
{
    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;
}

void NodePtr::operator = (const NullFieldContainerPtr &source)
{
    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

NodePtr::NodePtr(const Node &source) :
    Inherited(source)
{
}

NodePtr::NodePtr(const Node *source) :
    Inherited(source)
{
}

NodePtr::NodePtr(const Node   *source,
                 const UInt16  uiSize,
                 const UInt16  uiParentPos) :

    Inherited(source, uiSize, uiParentPos)
{
}




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class osg::CNodePtr
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

CNodePtr::CNodePtr(void) :
    Inherited()
{
}

CNodePtr::CNodePtr(const CNodePtr &source) :
    Inherited(source)
{
}

CNodePtr::CNodePtr(const NullFieldContainerPtr &source) :
    Inherited(source)
{
}

CNodePtr::CNodePtr(const NodePtr &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

CNodePtr::~CNodePtr(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */

Node *CNodePtr::getNode(void)
{
    return (Node *) getElemP(Thread::getAspect());
}

Node *CNodePtr::getNode(void) const
{
    return (Node *) getElemP(Thread::getAspect());
}

/*-------------------------------------------------------------------------*/
/*                            Container Access                             */

NodeCore *CNodePtr::operator->(void)
{
    return ((Node *) getElemP(Thread::getAspect()))->getCore().getCPtr();
}

NodeCore *CNodePtr::operator->(void) const
{
    return ((Node *) getElemP(Thread::getAspect()))->getCore().getCPtr();
}

NodeCore &CNodePtr::operator *(void)
{
    return *(((Node *) getElemP(Thread::getAspect()))->getCore().getCPtr());
}

NodeCore &CNodePtr::operator *(void) const
{
    return *(((Node *) getElemP(Thread::getAspect()))->getCore().getCPtr());
}

NodeCore *CNodePtr::getCPtr(void)
{
    return ((Node *) getElemP(Thread::getAspect()))->getCore().getCPtr();
}

NodeCore *CNodePtr::getCPtr(void) const
{
    return ((Node *) getElemP(Thread::getAspect()))->getCore().getCPtr();
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

void CNodePtr::operator = (const NodePtr &source)
{
    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;
}

void CNodePtr::operator = (const CNodePtr &source)
{
    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;
}

void CNodePtr::operator = (const NullFieldContainerPtr &source)
{
    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

CNodePtr::CNodePtr(const Node &source) :
    Inherited(source)
{
}

CNodePtr::CNodePtr(const Node *source) :
    Inherited(source)
{
}

CNodePtr::CNodePtr(const Node   *source,
                   const UInt16  uiSize,
                   const UInt16  uiParentPos) :
    Inherited(source, uiSize, uiParentPos)
{
}

/*-------------------------------------------------------------------------*/
/*                               Functions                                 */

//! Write FC to the given stream

OSG_SYSTEMLIB_DLLMAPPING
ostream &OSG::operator <<(      ostream  &os,
                          const NodePtr  &fc)
{
    if(fc == NullFC)
    {
        os << hex << "NodePtr 0x" << &fc << dec << ":NullFC";
    }
    else
    {
        os << hex << "NodePtr 0x"
           << &fc << dec << ":" << fc->getType().getName() << "Ptr(0x"
           << hex << (&(*fc)) << dec << ")";
    }

    return os;
}

//! Write FC to the given stream

OSG_SYSTEMLIB_DLLMAPPING
ostream &OSG::operator <<(      ostream  &os,
                          const CNodePtr &fc)
{
    if(fc == NullFC)
    {
        os << hex << "NodePtr 0x" << &fc << dec << ":NullFC";
    }
    else
    {
        os << hex << "NodePtr 0x"
           << &fc << dec << ":" << fc->getType().getName() << "Ptr(0x"
           << hex << (&(*fc)) << dec << ")";
    }

    return os;
}


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
    static Char8 cvsid_hpp[] = OSGNODEPTR_HEADER_CVSID;
}




