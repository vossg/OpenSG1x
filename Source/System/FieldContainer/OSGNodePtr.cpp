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

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGNodePtr.cpp
    \ingroup GrpSystemFieldContainer
 */
#endif

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

/*-------------------------------------------------------------------------*/
/*                               Functions                                 */

// Write FC to the given stream

OSG_SYSTEMLIB_DLLMAPPING
std::ostream &OSG::operator <<(      std::ostream &os,
                               const NodePtr      &fc)
{
    if(fc == NullFC)
    {
        os << std::hex << "NodePtr 0x" << &fc << std::dec << ":NullFC";
    }
    else
    {
        os << std::hex
           << "NodePtr 0x"
           << &fc 
           << std::dec
           << ":" 
           << fc->getType().getName() 
           << "Ptr(0x"
           << std::hex 
           << (&(*fc))
           << std::dec
           << ")";
    }

    return os;
}

// Write FC to the given stream

OSG_SYSTEMLIB_DLLMAPPING
std::ostream &OSG::operator <<(      std::ostream  &os,
                               const CNodePtr &fc)
{
    if(fc == NullFC)
    {
        os << std::hex << "NodePtr 0x" << &fc << std::dec << ":NullFC";
    }
    else
    {
        os << std::hex
           << "NodePtr 0x"
           << &fc
           << std::dec
           << ":" << fc->getType().getName()
           << "Ptr(0x"
           << std::hex
           << (&(*fc)) 
           << std::dec
           << ")";
    }

    return os;
}


// create a Node around the given core

OSG_SYSTEMLIB_DLLMAPPING
NodePtr OSG::makeNodeFor(NodeCorePtr core)
{
    NodePtr n = Node::create();
    
    beginEditCP(n, Node::CoreFieldMask);
    
    n->setCore(core);
    
    endEditCP(n, Node::CoreFieldMask);
    
    return n;
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
    static Char8 cvsid_inl[] = OSGNODEPTR_INLINE_CVSID;
    static Char8 cvsid_hpp[] = OSGNODEPTR_HEADER_CVSID;
}




