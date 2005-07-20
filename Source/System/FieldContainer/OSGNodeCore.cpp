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
/*! \file OSGNodeCore.cpp
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGNode.h"
#include "OSGNodeCore.h"
#include "OSGBinaryDataHandler.h"

OSG_USING_NAMESPACE

const BitVector
    NodeCore::ParentsFieldMask     = (1 << NodeCore::ParentsFieldId    );

FieldDescription *NodeCore::_desc[] =
{
    new FieldDescription(MFNodePtr::getClassType(),
                         "parents",
                         OSG_FC_FIELD_IDM_DESC(ParentsField),
                         true,
                         (FieldAccessMethod) &NodeCore::getMFParents)
};

FieldContainerType NodeCore::_type("NodeCore",
                                   "AttachmentContainer",
                                   NULL,
                                   NULL,
                                   NULL,
                                   _desc,
                                   sizeof(_desc));


OSG_ABSTR_FIELD_CONTAINER_DEF(NodeCore, NodeCorePtr)

#if defined(OSG_FIXED_MFIELDSYNC)
void NodeCore::onDestroyAspect(UInt32 uiId, UInt32 uiAspect)
{
    _parents.terminateShare(uiAspect, this->getContainerSize());
}
#endif

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void NodeCore::dump(      UInt32    uiIndent,
                    const BitVector bvFlags) const
{
    UInt32 i;

    NodeCorePtr thisP = getPtr();

//    thisP.dump(0, FCDumpFlags::RefCount);

    indentLog(uiIndent, PLOG);

    PLOG << "Core"
         << "("
         << std::dec
         << thisP.getFieldContainerId()
         << ") : " << getType().getName()
         << " "
         << _attachmentMap.getValue().size()
         << " attachments | "
         << this
         << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "[" << std::endl;

    indentLog(uiIndent + 4, PLOG);
    PLOG << "Parents : " << std::endl;

    for(i = 0; i < _parents.size(); i++)
    {
        indentLog(uiIndent + 4, PLOG);
        PLOG << "           " << i << ") " << &(*(_parents[i])) << std::endl;
    }

    indentLog(uiIndent, PLOG);
    PLOG << "]" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    Inherited::dump(uiIndent, bvFlags);

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;
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
    static Char8 cvsid_hpp[] = OSGNODECORE_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGNODECORE_INLINE_CVSID;
}
