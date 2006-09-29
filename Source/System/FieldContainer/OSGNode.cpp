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
/*! \file OSGNode.cpp
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include <functional>
#include <algorithm>

#include "OSGConfig.h"
#include "OSGFieldContainerPtr.h"
#include "OSGFieldContainerType.h"
#include "OSGNode.h"
#include "OSGNodeCore.h"
#include "OSGBinaryDataHandler.h"
#include "OSGSFFieldContainerPtr.h"
#include "OSGMFFieldContainerPtr.h"

OSG_USING_NAMESPACE

const BitVector Node::VolumeFieldMask      =
        (TypeTraits<BitVector>::One << Node::VolumeFieldId     );
const BitVector Node::TravMaskFieldMask      =
        (TypeTraits<BitVector>::One << Node::TravMaskFieldId   );
const BitVector Node::ParentFieldMask      =
        (TypeTraits<BitVector>::One << Node::ParentFieldId     );
const BitVector Node::ChildrenFieldMask    =
        (TypeTraits<BitVector>::One << Node::ChildrenFieldId   );
const BitVector Node::CoreFieldMask        =
        (TypeTraits<BitVector>::One << Node::CoreFieldId       );

FieldDescription *Node::_desc[] =
{
    new FieldDescription(SFDynamicVolume::getClassType(),
                         "volume",
                         OSG_FC_FIELD_IDM_DESC(VolumeField),
                         false,
                         (FieldAccessMethod) &Node::getSFVolume),

    // Yes, this is wrong, it should be an UInt32, but changing
    // it now will break all old .osb files, and this info is
    // nearly never necessary to be loaded from files.
    new FieldDescription(SFBool::getClassType(),
                         "travMask",
                         OSG_FC_FIELD_IDM_DESC(TravMaskField),
                         false,
                         (FieldAccessMethod) &Node::getSFTravMask),

    new FieldDescription(SFNodePtr::getClassType(),
                         "parent",
                         OSG_FC_FIELD_IDM_DESC(ParentField),
                         true,
                         (FieldAccessMethod) &Node::getSFParent),

    new FieldDescription(MFNodePtr::getClassType(),
                         "children",
                         OSG_FC_FIELD_IDM_DESC(ChildrenField),
                         false,
                         (FieldAccessMethod) &Node::getMFChildren),

    new FieldDescription(SFNodeCorePtr::getClassType(),
                         "core",
                         OSG_FC_FIELD_IDM_DESC(CoreField),
                         false,
                         (FieldAccessMethod) &Node::getSFCore)
};

FieldContainerType Node::_type(
    "Node",
    "AttachmentContainer",
    0,
    (PrototypeCreateF) &Node::createEmpty,
    0,
    _desc,
    sizeof(_desc));


const NodePtr Node::NullNode(NullFC);

OSG_FIELD_CONTAINER_DEF(Node, NodePtr)

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

void Node::setCore(const NodeCorePtr &core)
{
    NodePtr thisP = getPtr();

    thisP.setParentFieldPos(CoreFieldId);

    addRefCP(core);

    if(_sfCore.getValue() != NullFC)
    {
        beginEditCP(_sfCore.getValue(), NodeCore::ParentsFieldMask);
        {
            _sfCore.getValue()->subParent(thisP);
        }
        endEditCP  (_sfCore.getValue(), NodeCore::ParentsFieldMask);

        subRefCP(_sfCore.getValue());
    }

    _sfCore.setValue(core);

    if(_sfCore.getValue() != NullFC)
    {
        beginEditCP(_sfCore.getValue(), NodeCore::ParentsFieldMask);
        {
            _sfCore.getValue()->addParent(thisP);
        }
        endEditCP  (_sfCore.getValue(), NodeCore::ParentsFieldMask);
    }

    // TODO Check if required (GV)
    invalidateVolume();
}

/*-------------------------------------------------------------------------*/
/*                             Children                                    */

void Node::addChild(const NodePtr &childP)
{
    if(childP != NullFC)
    {
        // do the ref early, to prevent destroys on getParent(a)->addChild(a)
        addRefCP(childP);

        // already somebody else's child?
        NodePtr parent = childP->getParent();
        if(parent != NullFC)
        {
            beginEditCP(parent, Node::ChildrenFieldMask);
            parent->subChild(childP);
            endEditCP  (parent, Node::ChildrenFieldMask);
        }

        _mfChildren.push_back(childP);

        beginEditCP(childP, Node::ParentFieldMask);
        {
            childP->setParent(getPtr());
        }
        endEditCP  (childP, Node::ParentFieldMask);

        // TODO Check if required (GV)
#ifndef OSG_GV_BETA
        invalidateVolume();
#endif
    }
}

void Node::insertChild(UInt32 childIndex, const NodePtr &childP)
{
    MFNodePtr::iterator childIt = _mfChildren.begin();

    if(childP != NullFC)
    {
        // do the ref early, to prevent destroys on getParent(a)->addChild(a)
        addRefCP(childP);

        // already somebody else's child?
        NodePtr parent = childP->getParent();
        if(parent != NullFC)
        {
            beginEditCP(parent, Node::ChildrenFieldMask);
            parent->subChild(childP);
            endEditCP  (parent, Node::ChildrenFieldMask);
        }

        childIt += childIndex;

        _mfChildren.insert(childIt, childP);

        beginEditCP(childP, Node::ParentFieldMask);
        {
            childP->setParent(getPtr());
        }
        endEditCP  (childP, Node::ParentFieldMask);
    }

    // TODO check if required (GV)
#ifndef OSG_GV_BETA
    invalidateVolume();
#endif
}

void Node::replaceChild(UInt32 childIndex, const NodePtr &childP)
{
    if(childP != NullFC && childIndex < _mfChildren.size())
    {
        // do the ref early, to prevent destroys on getParent(a)->addChild(a)
        addRefCP(childP);
        // already somebody else's child?
        // moved it up could be a child of childIndex.
        NodePtr parent = childP->getParent();
        if(parent != NullFC)
        {
            beginEditCP(parent, Node::ChildrenFieldMask);
            parent->subChild(childP);
            endEditCP  (parent, Node::ChildrenFieldMask);
        }

        // remove the current child
        beginEditCP(_mfChildren[childIndex], Node::ParentFieldMask);
        {
            _mfChildren[childIndex]->setParent(NullNode);
        }
        endEditCP  (_mfChildren[childIndex], Node::ParentFieldMask);

        subRefCP(_mfChildren[childIndex]);

        // set the new child
        _mfChildren[childIndex] = childP;

        beginEditCP(childP, Node::ParentFieldMask);
        {
            childP->setParent(getPtr());
        }
        endEditCP  (childP, Node::ParentFieldMask);
    }

    // TODO check if required (GV)
#ifndef OSG_GV_BETA
    invalidateVolume();
#endif
}

//! return true on success, false on child not found

bool Node::replaceChildBy(const NodePtr &childP,
                          const NodePtr &newChildP)
{
    MFNodePtr::iterator childIt = _mfChildren.find(childP);

    if(newChildP != NullFC)
    {
        if(childIt != _mfChildren.end())
        {
            // do the ref early, to prevent destroys on
            // getParent(a)->addChild(a)

            addRefCP(newChildP);
            // already somebody else's child?
            // moved it up could be a child of childP.
            NodePtr parent = newChildP->getParent();
            if(parent != NullFC)
            {
                beginEditCP(parent, Node::ChildrenFieldMask);
                parent->subChild(newChildP);
                endEditCP  (parent, Node::ChildrenFieldMask);
            }

            beginEditCP(childP, Node::ParentFieldMask);
            {
                childP->setParent(NullNode);
            }
            endEditCP  (childP, Node::ParentFieldMask);

            subRefCP(childP);

            (*childIt) = newChildP;

            beginEditCP(newChildP, Node::ParentFieldMask);
            {
                newChildP->setParent(getPtr());
            }
            endEditCP  (newChildP, Node::ParentFieldMask);

            // TODO check if required (GV)
#ifndef OSG_GV_BETA
            invalidateVolume();
#endif

            return true;
        }
    }

    return false;
}

Int32 Node::findChild(const NodePtr &childP) const
{
    UInt32 index;

    for(index = 0; index < _mfChildren.size(); index++)
    {
        if( _mfChildren[index] == childP)
            break;
    }

    if(index < _mfChildren.size())
        return index;
    else
        return -1;
}

void Node::subChild(const NodePtr &childP)
{
    MFNodePtr::iterator childIt = _mfChildren.find(childP);

    if(childIt != _mfChildren.end())
    {
        beginEditCP(childP, Node::ParentFieldMask);
        {
            childP->setParent(NullNode);
        }
        endEditCP  (childP, Node::ParentFieldMask);

        subRefCP(childP);

        _mfChildren.erase(childIt);
    }
    else
    {
        SWARNING << "Node(" << this << ")::subChild: " << childP
                 << " is not one of my children!" << std::endl;
    }

    // TODO check if required (GV)
#ifndef OSG_GV_BETA
    invalidateVolume();
#endif
}

void Node::subChild(UInt32 childIndex)
{
    MFNodePtr::iterator childIt = _mfChildren.begin();

    childIt += childIndex;

    if(childIt != _mfChildren.end())
    {
        beginEditCP(*childIt, Node::ParentFieldMask);
        {
            (*childIt)->setParent(NullNode);
        }
        endEditCP  (*childIt, Node::ParentFieldMask);

        subRefCP(*childIt);

        _mfChildren.erase(childIt);
    }

    // TODO check if required (GV)
#ifndef OSG_GV_BETA
    invalidateVolume();
#endif
}


/*-------------------------------------------------------------------------*/
/*                           Get Transformation                            */

Matrix Node::getToWorld(void)
{
    Matrix tmp;

    getToWorld(tmp);

    return tmp;
}

void Node::getToWorld(Matrix &result)
{
    if(getParent() != NullFC)
    {
        getParent()->getToWorld(result);
    }
    else
    {
        result.setIdentity();
    }

    if(getCore() != NullFC)
        getCore()->accumulateMatrix(result);
}

/*-------------------------------------------------------------------------*/
/*                           Volume                                        */

void Node::getWorldVolume(DynamicVolume &result)
{
    Matrix m;

    if(getParent() != NullFC)
    {
        getParent()->getToWorld(m);
    }
    else
    {
        m.setIdentity();
    }

    updateVolume();

    result = getVolume();
    result.transform(m);
/*
Pnt3f low,high;
result.getBounds(low,high);
fprintf(stderr,"%p: node 0x%p gwv (%f %f %f  %f %f %f)\n",
            Thread::getCurrent(), this,
            low[0], low[1], low[2],
            high[0], high[1], high[2] );
*/
}

void Node::updateVolume(void)
{
    if(_sfVolume.getValue().getInstance().isValid() == true ||
       getTravMask()                                == 0x0000)
    {
        return;             // still valid, nothing to do
    }

    // be careful to not change the real volume. If two threads
    // are updating the same aspect this will lead to chaos

    DynamicVolume vol = _sfVolume.getValue();

//fprintf(stderr,"%p: node 0x%p update needed\n", Thread::getCurrent(), this);

    MFNodePtr::iterator it;

    vol.getInstance().setEmpty();

    for(it = _mfChildren.begin(); it != _mfChildren.end(); ++it)
    {
        if((*it)->getTravMask())
        {
            (*it)->updateVolume();
            vol.getInstance().extendBy((*it)->getVolume());
        }
    }

    // test for null core. Shouldn't happen, but just in case...
    if(getCore() != NullFC)
        getCore()->adjustVolume(vol.getInstance());

    NodePtr thisP = getPtr();

    beginEditCP(thisP, VolumeFieldMask);

    vol.instanceChanged();

    _sfVolume.setValue(vol);

    endEditCP(thisP, VolumeFieldMask);
}

void Node::invalidateVolume(void)
{
    Volume &vol=_sfVolume.getValue().getInstance();

    if(vol.isValid() == true && vol.isStatic() == false)
    {
        NodePtr thisP = getPtr();

        beginEditCP(thisP, VolumeFieldMask);

        vol.setValid(false);
        _sfVolume.getValue().instanceChanged();

        endEditCP(thisP, VolumeFieldMask);

        if(getParent() != NullFC)
        {
            getParent()->invalidateVolume();
        }
    }
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void Node::dump(      UInt32    uiIndent,
                const BitVector bvFlags) const
{
    UInt32 i;

    NodePtr thisP = getPtr();

    indentLog(uiIndent, PLOG);

    PLOG << "Node"
         << "("
         << thisP.getFieldContainerId()
         << ") : "
         << _mfChildren.size()
         << " children | "
         << _attachmentMap.getValue().size()
         << " attachments | "
         << "Parent : " << std::hex;

    if(_sfParent.getValue() != NullFC)
        PLOG << "0x" << &(*(_sfParent.getValue())) << " | ";
    else
        PLOG << "NULL | ";

    PLOG << "0x" << this << std::dec << std::endl;

    indentLog(uiIndent, PLOG);

    PLOG << "[" << std::endl;

    if(_sfCore.getValue() != NullFC)
    {
        _sfCore.getValue()->dump(uiIndent + 4, bvFlags);
    }
    else
    {
        indentLog(uiIndent + 4, PLOG);
        PLOG << "Core : " << "NULL" << std::endl;
    }

    Inherited::dump(uiIndent, bvFlags);

    indentLog(uiIndent, PLOG);
    PLOG << "]" << std::endl;

    indentLog(uiIndent, PLOG);

    PLOG << "{" << std::endl;

    for(i = 0; i < _mfChildren.size(); i++)
    {
        _mfChildren[i]->dump(uiIndent + 4, bvFlags);
        PLOG << std::endl;
    }


    indentLog(uiIndent, PLOG);

    PLOG << "}" << std::endl;

/*
    for(i = 0; i < indent; i++)
    {
        cerr << " ";
    }
    cerr << "  Parent : ";


    for(i = 0; i < indent; i++)
    {
        cerr << " ";
    }

    for(i = 0; i < indent; i++)
        fprintf(stderr, " ");

    fprintf(stderr, "NAttachments : \n");

    map<UInt32, AttachmentPtr>::const_iterator fcI;

    fcI = _attachmentMap.getValue().begin();

    while(fcI != _attachmentMap.getValue().end())
    {
        (*fcI).second->dump(indent + 2);
        ++fcI;
    }

    for(i = 0; i < indent; i++)
    {
        cerr << " ";
    }

    cerr << "{" << std::endl;


    for(i = 0; i < indent; i++)
    {
        cerr << " ";
    }

    cerr << "}" << std::endl;
*/
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

Node::Node(void) :
     Inherited    (),
    _sfVolume     (),
    _sfTravMask   (TypeTraits<UInt32>::getMax()),
    _sfParent     (),
    _mfChildren   (),
    _sfCore       (),
    _occlusionMask(0)
{
}

Node::Node(const Node &source) :
     Inherited       (source),
    _sfVolume        (source._sfVolume),
    _sfTravMask      (source._sfTravMask),
    _sfParent        (),
    _mfChildren      (),
    _sfCore          (),
    _occlusionMask   (source._occlusionMask)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

Node::~Node(void)
{
    if(_sfCore.getValue() != NullFC)
    {
        NodePtr thisP = getPtr();

        beginEditCP(_sfCore.getValue(), NodeCore::ParentsFieldMask);
        {
            _sfCore.getValue()->subParent(thisP);
        }
        endEditCP  (_sfCore.getValue(), NodeCore::ParentsFieldMask);

        subRefCP(_sfCore.getValue());
    }

    MFNodePtr::iterator       vChildIt    = _mfChildren.begin();
    MFNodePtr::const_iterator endChildren = _mfChildren.end  ();

    while(vChildIt != endChildren)
    {
        beginEditCP(*vChildIt, Node::ParentFieldMask);
        {
            (*vChildIt)->setParent(NullNode);
        }
        endEditCP  (*vChildIt, Node::ParentFieldMask);

        subRefCP(*vChildIt);

        ++vChildIt;
    }
}

#if defined(OSG_FIXED_MFIELDSYNC)
void Node::onDestroyAspect(UInt32 uiId, UInt32 uiAspect)
{
    _mfChildren.terminateShare(uiAspect, this->getContainerSize());
}
#endif

NodePtr OSG::cloneTree(const NodePtr &pRootNode)
{
    NodePtr returnValue = NullFC;

    if(pRootNode != NullFC)
    {
        NodePtr pChildClone = NullFC;

        returnValue = Node::create();

        beginEditCP(returnValue);
        {
            returnValue->setTravMask(pRootNode->getTravMask());
            returnValue->setCore    (pRootNode->getCore());

            for(UInt32 i = 0; i < pRootNode->getNChildren(); i++)
            {
                pChildClone = cloneTree(pRootNode->getChild(i));

                returnValue->addChild(pChildClone);
            }
        }
        endEditCP  (returnValue);
    }

    return returnValue;
}

// deep clone of a fieldcontainer.
// we should move this into OSGFieldContainer.cpp?
FieldContainerPtr OSG::deepClone(const FieldContainerPtr &src,
                                 const std::vector<std::string> &share)
{
    if(src == NullFC)
        return NullFC;

    const FieldContainerType &type = src->getType();

    //FDEBUG(("deepClone: fieldcontainertype = %s\n", type.getCName()));

    FieldContainerPtr dst = FieldContainerFactory::the()->createFieldContainer(type.getName().str());

    //UInt32 fcount = type.getNumFieldDescs();
    // ignore dynamic fields.
    UInt32 fcount = osgMin(type.getNumFieldDescs(), dst->getType().getNumFieldDescs());


    for(UInt32 i=1;i <= fcount;++i)
    {
        const FieldDescription* fdesc = type.getFieldDescription(i);

        if(fdesc->isInternal())
            continue;

        BitVector mask = fdesc->getFieldMask();

        Field *src_field = src->getField(i);
        Field *dst_field = dst->getField(i);

        const FieldType &ftype = src_field->getType();

        std::string fieldType = ftype.getName().str();

        // attachements
        if(strcmp(fdesc->getCName(), "attachments") == 0)
        {
            SFAttachmentMap *amap = (SFAttachmentMap *) src_field;

            AttachmentMap::const_iterator   mapIt = amap->getValue().begin();
            AttachmentMap::const_iterator   mapEnd = amap->getValue().end();

            beginEditCP(dst, mask);
            for(; mapIt != mapEnd; ++mapIt)
            {
                FieldContainerPtr fc = mapIt->second;

                bool shareit = false;
                for(UInt32 k=0;k<share.size();++k)
                {
                    FieldContainerType *fct = FieldContainerFactory::the()
                                            ->findType(share[k].c_str());
                    if(fc != NullFC && fct != NULL &&
                       fc->getType().isDerivedFrom(*fct))
                    {
                        shareit = true;
                        break;
                    }
                }

                if(!shareit)
                    fc = OSG::deepClone(fc, share);

                if(fc != NullFC)
                    AttachmentContainerPtr::dcast(dst)->addAttachment(AttachmentPtr::dcast(fc));
            }
            endEditCP(dst, mask);
            continue;
        }

        // field
        if(strstr(ftype.getCName(), "Ptr") == NULL)
        {
            //FDEBUG(("deepClone: fieldname = %s fieldType = %s\n", fdesc->getCName(), fieldType.c_str()));
            beginEditCP(dst, mask);
                dst_field->setAbstrValue(*src_field);
            endEditCP(dst, mask);
        }
        else // field with pointer
        {
            if(src_field->getCardinality() == FieldType::SINGLE_FIELD)
            {
                FieldContainerPtr fc = ((SFFieldContainerPtr *) src_field)->getValue();

                bool shareit = false;
                for(UInt32 k=0;k<share.size();++k)
                {
                    FieldContainerType *fct = FieldContainerFactory::the()
                                            ->findType(share[k].c_str());
                    if(fc != NullFC && fct != NULL &&
                       fc->getType().isDerivedFrom(*fct))
                    {
                        shareit = true;
                        break;
                    }
                }

                if(!shareit)
                    fc = OSG::deepClone(fc, share);

                if(fc != NullFC)
                {
                    // increment reference counter!
                    addRefCP(fc);
                    beginEditCP(dst);
                        ((SFFieldContainerPtr *) dst_field)->setValue(fc);
                    endEditCP(dst);
                }
            }
            else if(src_field->getCardinality() == FieldType::MULTI_FIELD)
            {
                beginEditCP(dst, mask);
                    for(UInt32 j=0;j < ((MFFieldContainerPtr*)src_field)->size();++j)
                    {
                        FieldContainerPtr fc = (*(((MFFieldContainerPtr *)src_field)))[j];

                        bool shareit = false;
                        for(UInt32 k=0;k<share.size();++k)
                        {
                            FieldContainerType *fct = FieldContainerFactory::the()
                                            ->findType(share[k].c_str());
                            if(fc != NullFC && fct != NULL &&
                               fc->getType().isDerivedFrom(*fct))
                            {
                                shareit = true;
                                break;
                            }
                        }

                        if(!shareit)
                            fc = OSG::deepClone(fc, share);

                        if(fc != NullFC)
                        {
                            // increment reference counter!
                            addRefCP(fc);
                            ((MFFieldContainerPtr *) dst_field)->push_back(fc);
                        }
                    }
                endEditCP(dst, mask);
            }
        }
    }
    return dst;
}

FieldContainerPtr OSG::deepClone(const FieldContainerPtr &src,
                                 const std::vector<UInt16> &shareGroupIds)
{
    std::vector<std::string> share;
    share.reserve(shareGroupIds.size());
    for(UInt32 i=0;i<shareGroupIds.size();++i)
    {
        const char *name = FieldContainerFactory::the()->findGroupName(shareGroupIds[i]);
        if(name != NULL)
            share.push_back(name);
    }
    return OSG::deepClone(src, share);
}

// shareString is a comma separated FieldContainer type list
// e.g. "Material, Geometry"
FieldContainerPtr OSG::deepClone(const FieldContainerPtr &src,
                                 const std::string &shareString)
{
    std::vector<std::string> share;

    // parse comma separated names.
    std::string::const_iterator nextComma;
    std::string::const_iterator curPos = shareString.begin();
    while(curPos < shareString.end())
    {
        nextComma = std::find(curPos, shareString.end(), ',');
        // strip leading spaces
        curPos = std::find_if(curPos, nextComma, std::not1(std::ptr_fun(isspace)));
        share.push_back(std::string(curPos, nextComma));
        if(nextComma != shareString.end())
            curPos = ++nextComma;
        else
            break;
    }

    return OSG::deepClone(src, share);
}

// deep clone of attachements.
void OSG::deepCloneAttachments(const AttachmentContainerPtr &src,
                               AttachmentContainerPtr dst,
                               const std::vector<std::string> &share)
{
    SFAttachmentMap *amap = (SFAttachmentMap *) src->getSFAttachments();

    AttachmentMap::const_iterator   mapIt = amap->getValue().begin();
    AttachmentMap::const_iterator   mapEnd = amap->getValue().end();

    beginEditCP(dst, AttachmentContainer::AttachmentsFieldMask);
    for(; mapIt != mapEnd; ++mapIt)
    {
        FieldContainerPtr fc = mapIt->second;

        bool shareit = false;
        for(UInt32 k=0;k<share.size();++k)
        {
            FieldContainerType *fct = FieldContainerFactory::the()
                                      ->findType(share[k].c_str());
            if(fc != NullFC && fct != NULL &&
               fc->getType().isDerivedFrom(*fct))
            {
                shareit = true;
                break;
            }
        }

        if(!shareit)
            fc = OSG::deepClone(fc, share);

        if(fc != NullFC)
            dst->addAttachment(AttachmentPtr::dcast(fc));
    }
    endEditCP(dst, AttachmentContainer::AttachmentsFieldMask);
}

void OSG::deepCloneAttachments(const AttachmentContainerPtr &src,
                               AttachmentContainerPtr dst,
                               const std::vector<UInt16> &shareGroupIds)
{
    std::vector<std::string> share;
    share.reserve(shareGroupIds.size());
    for(UInt32 i=0;i<shareGroupIds.size();++i)
    {
        const char *name = FieldContainerFactory::the()
                           ->findGroupName(shareGroupIds[i]);
        if(name != NULL)
            share.push_back(name);
    }
    OSG::deepCloneAttachments(src, dst, share);
}

// shareString is a comma separated FieldContainer type list
// e.g. "Material, Geometry"
void OSG::deepCloneAttachments(const NodePtr &src, NodePtr &dst,
                               const std::string &shareString)
{
    std::vector<std::string> share;

    // parse comma separated names.
    std::string::const_iterator nextComma;
    std::string::const_iterator curPos = shareString.begin();
    while(curPos < shareString.end())
    {
        nextComma = std::find(curPos, shareString.end(), ',');
        // strip leading spaces
        curPos = std::find_if(curPos, nextComma, std::not1(std::ptr_fun(isspace)));
        share.push_back(std::string(curPos, nextComma));
        if(nextComma != shareString.end())
            curPos = ++nextComma;
        else
            break;
    }

    OSG::deepCloneAttachments(src, dst, share);
}

// deep clone of nodes.
NodePtr OSG::deepCloneTree(const NodePtr &src,
                           const std::vector<std::string> &share)
{
    NodePtr dst = NullFC;

    if(src != NullFC)
    {
        dst = Node::create();
        deepCloneAttachments(src, dst, share);

        beginEditCP(dst);
        {
            dst->setActive(src->getActive());
            dst->setTravMask(src->getTravMask());
            dst->setCore(NodeCorePtr::dcast(OSG::deepClone(src->getCore(), share)));

            for(UInt32 i = 0; i < src->getNChildren(); i++)
                dst->addChild(deepCloneTree(src->getChild(i), share));
        }
        endEditCP  (dst);
    }

    return dst;
}

NodePtr OSG::deepCloneTree(const NodePtr &src,
                           const std::vector<UInt16> &shareGroupIds)
{
    std::vector<std::string> share;
    share.reserve(shareGroupIds.size());
    for(UInt32 i=0;i<shareGroupIds.size();++i)
    {
        const char *name = FieldContainerFactory::the()->findGroupName(shareGroupIds[i]);
        if(name != NULL)
            share.push_back(name);
    }
    return OSG::deepCloneTree(src, share);
}

// shareString is a comma separated FieldContainer type list
// e.g. "Material, Geometry"
NodePtr OSG::deepCloneTree(const NodePtr &src,
                           const std::string &shareString)
{
    std::vector<std::string> share;

    // parse comma separated names.
    std::string::const_iterator nextComma;
    std::string::const_iterator curPos = shareString.begin();
    while(curPos < shareString.end())
    {
        nextComma = std::find(curPos, shareString.end(), ',');
        // strip leading spaces
        curPos = std::find_if(curPos, nextComma, std::not1(std::ptr_fun(isspace)));
        share.push_back(std::string(curPos, nextComma));
        if(nextComma != shareString.end())
            curPos = ++nextComma;
        else
            break;
    }

    return OSG::deepCloneTree(src, share);
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
    static Char8 cvsid_hpp[] = OSGNODE_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGNODE_INLINE_CVSID;
}
