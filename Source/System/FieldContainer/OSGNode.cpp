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

#include "OSGConfig.h"
#include "OSGFieldContainerPtr.h"
#include "OSGFieldContainerType.h"
#include "OSGNode.h"
#include "OSGNodeCore.h"
#include "OSGBinaryDataHandler.h"

OSG_USING_NAMESPACE

const BitVector Node::VolumeFieldMask      =
        (TypeTraits<BitVector>::One << Node::VolumeFieldId     );
const BitVector Node::ActiveFieldMask      = 
        (TypeTraits<BitVector>::One << Node::ActiveFieldId     );
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

    new FieldDescription(SFBool::getClassType(),
                         "active",
                         OSG_FC_FIELD_IDM_DESC(ActiveField),
                         false,
                         (FieldAccessMethod) &Node::getSFActive),

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
        if(childP->getParent() != NullFC)
        {
            childP->getParent()->subChild(childP);
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
        if(childP->getParent() != NullFC)
        {
            childP->getParent()->subChild(childP);
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

        // remove the current child
        beginEditCP(_mfChildren[childIndex], Node::ParentFieldMask);
        {
            _mfChildren[childIndex]->setParent(NullNode);
        }
        endEditCP  (_mfChildren[childIndex], Node::ParentFieldMask);

        subRefCP(_mfChildren[childIndex]);

        // already somebody else's child?
        if(childP->getParent() != NullNode)
        {
            childP->getParent()->subChild(childP);
        }

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

            beginEditCP(childP, Node::ParentFieldMask);
            {
                childP->setParent(NullNode);
            }
            endEditCP  (childP, Node::ParentFieldMask);

            subRefCP(childP);

            // already somebody else's child?
            if(newChildP->getParent() != NullFC)
            {
                newChildP->getParent()->subChild(newChildP);
            }

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

#if 0
void Node::updateVolume(void)
{
    Volume &vol = _sfVolume.getValue().getInstance();

    if(vol.isValid() == true)
        return;             // still valid, nothing to do

// fprintf(stderr,"%p: node 0x%p update needed\n", Thread::getCurrent(), this);

    MFNodePtr::iterator it;

    beginEdit(VolumeFieldMask, _sfVolume);

    vol.setEmpty();

    for(it = _mfChildren.begin(); it != _mfChildren.end(); ++it)
    {
        (*it)->updateVolume();
        vol.extendBy((*it)->getVolume());
    }

    // test for null core. Shouldn't happen, but just in case...
    if(getCore() != NullFC)
        getCore()->adjustVolume(vol);
   
    _sfVolume.getValue().instanceChanged();
    
    endEdit(VolumeFieldMask, _sfVolume);
}
#else // test version using DVol instance instead of reference
void Node::updateVolume(void)
{
    if(_sfVolume.getValue().getInstance().isValid() == true)
        return;             // still valid, nothing to do

    // be careful to not change the real volume. If two threads
    // are updating the same aspect this will lead to chaos
    
    DynamicVolume vol = _sfVolume.getValue();

//fprintf(stderr,"%p: node 0x%p update needed\n", Thread::getCurrent(), this);

    MFNodePtr::iterator it;

    vol.getInstance().setEmpty();

    if(getActive())
    {
        for(it = _mfChildren.begin(); it != _mfChildren.end(); ++it)
        {
            (*it)->updateVolume();
            vol.getInstance().extendBy((*it)->getVolume());
        }

        // test for null core. Shouldn't happen, but just in case...
        if(getCore() != NullFC)
            getCore()->adjustVolume(vol.getInstance());
    }
    
    beginEdit(VolumeFieldMask, _sfVolume);
   
    vol.instanceChanged();
    
    _sfVolume.setValue(vol);
    
    endEdit(VolumeFieldMask, _sfVolume);
}
#endif

void Node::invalidateVolume(void)
{
    Volume &vol=_sfVolume.getValue().getInstance();
    
    if(vol.isValid() == true && vol.isStatic() == false)
    {
        beginEdit(VolumeFieldMask, _sfVolume);

        vol.setValid(false);
        _sfVolume.getValue().instanceChanged();
        
        endEdit(VolumeFieldMask, _sfVolume);

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
     Inherited  (),
    _sfVolume   (),
    _sfActive   (true),
    _sfParent   (),
    _mfChildren (),
    _sfCore     ()
{
}

Node::Node(const Node &source) :
     Inherited  (source),
    _sfVolume   (source._sfVolume),
    _sfActive   (source._sfActive),
    _sfParent   (),
    _mfChildren (),
    _sfCore     ()
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

NodePtr OSG::cloneTree(NodePtr pRootNode)
{
    NodePtr returnValue = NullFC;

    if(pRootNode != NullFC)
    {
        NodePtr pChildClone = NullFC;

        returnValue = Node::create();

        beginEditCP(returnValue);
        {
            returnValue->setActive(pRootNode->getActive());
            returnValue->setCore  (pRootNode->getCore());
            
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
