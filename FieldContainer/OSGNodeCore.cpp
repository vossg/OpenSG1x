/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000,2001 by OpenSG Forum                   *
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

#include "OSGNode.h"
#include "OSGNodeCore.h"
#include "OSGBinaryDataHandler.h"

OSG_USING_NAMESPACE

/*! \class osg::NodeCore
 */

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

/*-------------------------------------------------------------------------*/
/*                              Parents                                    */

MFNodePtr &NodeCore::getParents(void)
{
    return _parents;
}

const MFNodePtr &NodeCore::getParents(void) const
{
    return _parents;
}

MFNodePtr *NodeCore::getMFParents(void)
{
    return &_parents;
}

/*-------------------------------------------------------------------------*/
/*                         Binary Interface                                */

UInt32 NodeCore::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        returnValue += _parents.getBinSize();
    }

    return returnValue;
}

void NodeCore::copyToBin(      BinaryDataHandler &pMem,
                         const BitVector         &whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        _parents.copyToBin(pMem);
    }
}

void NodeCore::copyFromBin(      BinaryDataHandler &pMem,
                           const BitVector         &whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        _parents.copyFromBin(pMem);
    }
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void NodeCore::dump(      UInt32    uiIndent,
                    const BitVector bvFlags) const
{
    UInt32 i;

    indentLog(uiIndent, PLOG);

    PLOG << "Core : " << getType().getName()
         << " "
         << _attachmentMap.getValue().size()
         << " attachments | "
         << this
         << endl;

    indentLog(uiIndent, PLOG);
    PLOG << "[" << endl;

    indentLog(uiIndent + 4, PLOG);
    PLOG << "Parents : " << endl;

    for(i = 0; i < _parents.size(); i++)
    {
        indentLog(uiIndent + 4, PLOG);
        PLOG << "           " << i << ") " << &(*(_parents[i])) << endl;
    }

    indentLog(uiIndent, PLOG);
    PLOG << "]" << endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << endl;

    Inherited::dump(uiIndent, bvFlags);

    indentLog(uiIndent, PLOG);
    PLOG << "}" << endl;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

NodeCore::NodeCore(void) :
     Inherited(),
    _parents  ()
{
}

NodeCore::NodeCore(const NodeCore &obj) :
     Inherited(obj),
    _parents  (   )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

NodeCore::~NodeCore(void)
{
}

/*-------------------------------------------------------------------------*/
/*                          MT Destruction                                 */

void NodeCore::onDestroy(void)
{
}

/*-------------------------------------------------------------------------*/
/*                              Parents                                    */

void NodeCore::addParent(const NodePtr &parent)
{
    _parents.push_back(parent);
}

void NodeCore::subParent(const NodePtr &parent)
{
    MFNodePtr::iterator parentIt = _parents.find(parent);

    if(parentIt != _parents.end())
    {
        _parents.erase(parentIt);
    }
}

/*-------------------------------------------------------------------------*/
/*                              Pointer                                    */

NodeCorePtr NodeCore::getPtr(void)
{
    return NodeCorePtr(*this);
}

/*-------------------------------------------------------------------------*/
/*                                Sync                                     */

void NodeCore::executeSync(      FieldContainer &other,
                           const BitVector      &whichField)
{
    this->executeSyncImpl((NodeCore *) &other, whichField);
}


void NodeCore::executeSyncImpl(      NodeCore  *pOther,
                               const BitVector &whichField)
{
    Inherited::executeSyncImpl(pOther, whichField);

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        _parents.syncWith(pOther->_parents);
    }
}

/*-------------------------------------------------------------------------*/
/*                              Matrix                                     */

void NodeCore::accumulateMatrix(Matrix &)
{
}

/*-------------------------------------------------------------------------*/
/*                              Volume                                     */

void NodeCore::adjustVolume(Volume &)
{
}

void NodeCore::invalidateVolume(void)
{
    for(UInt32 i = 0; i < _parents.size(); i++)
    {
        _parents[i]->invalidateVolume();
    }
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
