/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#define OSG_COMPILEFIELDCONTAINER

#include "OSGFieldContainerPtr.h"

#include "OSGFieldContainerType.h"

#include "OSGNode.h"
#include "OSGNodeCore.h"
#include "OSGAttachment.h"

OSG_USING_NAMESPACE

/** \brief NULL node pointer
 */

OSG_FIELDCONTAINER_DLLMAPPING const NodePtr             OSG::NullNode;



/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/* Could not put this in the class declaration, since MS interprets them there
 * as pure virtual functions :-( (GV)
 */

OSG_FC_FIRST_FIELD_IDM_DEF(Node, VolumeField)

OSG_FC_FIELD_IDM_DEF      (Node, ParentField,      VolumeField)
OSG_FC_FIELD_IDM_DEF      (Node, ChildrenField,    ParentField)
OSG_FC_FIELD_IDM_DEF      (Node, CoreField,        ChildrenField)
OSG_FC_FIELD_IDM_DEF      (Node, AttachmentsField, CoreField)

OSG_FC_LAST_FIELD_IDM_DEF (Node, AttachmentsField)

FieldDescription Node::_desc[] = 
{
	FieldDescription(SFDynamicVolume::getClassType(), 
                        "volume", 
                        OSG_FC_FIELD_IDM_DESC(VolumeField),
                        false,
                        (FieldAccessMethod) &Node::getSFVolume),

	FieldDescription(SFNodePtr::getClassType(),
                        "parent", 
                        OSG_FC_FIELD_IDM_DESC(ParentField),
                        false,
                        (FieldAccessMethod) &Node::getSFParent),

	FieldDescription(MFNodePtr::getClassType(), 
                        "children", 
                        OSG_FC_FIELD_IDM_DESC(ChildrenField),
                        false,
                        (FieldAccessMethod) &Node::getMFChildren),

    FieldDescription(SFNodeCorePtr::getClassType(),
                        "core",
                        OSG_FC_FIELD_IDM_DESC(CoreField),
                        false,	
                        (FieldAccessMethod) &Node::getSFCore),

    FieldDescription(SFAttachmentMap::getClassType(),
                        "attachments",
                        OSG_FC_FIELD_IDM_DESC(AttachmentsField),
                        false,	
                        (FieldAccessMethod) &Node::getSFAttachments)
};

FieldContainerType Node::_type(
    "Node", 
    "FieldContainer", 
    0,
    (PrototypeCreateF) &Node::createEmpty,
    0,
    _desc, 
    sizeof(_desc));



/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*! @name Node Static Type Information
 */

/*@{*/

/*! \fn FieldContainerType &Node::getStaticType(void) 
 *  \brief returns node type
 */

/*! \fn UInt32 Node::getStaticTypeId(void) 
 *  \brief returns node type id
 */

/*@}*/

/*! @name Node Creation
 */

/*@{*/

/*! \fn NodePtr ::Node::create(void) 
 *  \brief creates a clone of the prototype
 */

/*! \fn NodePtr ::Node::createEmpty(void) 
 *  \brief creates a empty node, does not clone the prototype
 */

/*@}*/

OSG_FIELD_CONTAINER_DEF(Node, NodePtr)

/*------------------------------ access -----------------------------------*/

void Node::addAttachment(const AttachmentPtr &fieldContainerP,
                               UInt16         binding)
{
    UInt32 key;

    if(fieldContainerP == NullAttachment)
        return;

	key = (UInt32 (fieldContainerP->getGroupId()) << 16) | binding;

    addRefCP(fieldContainerP);

	AttachmentMap::iterator fcI = _attachmentMap.getValue().find(key);

    beginEditCP(fieldContainerP, Attachment::ParentsFieldMask);
    {
        fieldContainerP->addParent(getPtr());
    }
    endEditCP  (fieldContainerP, Attachment::ParentsFieldMask);

	if(fcI != _attachmentMap.getValue().end())
    {
        subRefCP((*fcI).second);
        (*fcI).second = fieldContainerP;
    }	
    else
    {
        _attachmentMap.getValue()[key] = fieldContainerP;
    }
}

void Node::subAttachment(const AttachmentPtr &fieldContainerP,
                               UInt16         binding)
{
    UInt32 key;

    AttachmentMap::iterator fcI;

    if(fieldContainerP == NullAttachment)
        return;

    key = (UInt32(fieldContainerP->getGroupId()) << 16) | binding;

    fcI = _attachmentMap.getValue().find(key);

    if(fcI != _attachmentMap.getValue().end())
    {
        beginEditCP(fieldContainerP, Attachment::ParentsFieldMask);
        {
            (*fcI).second->subParent(getPtr());
        }
        endEditCP  (fieldContainerP, Attachment::ParentsFieldMask);

        subRefCP((*fcI).second);

        _attachmentMap.getValue().erase(fcI);
    }  
}

AttachmentPtr Node::findAttachment(UInt32 groupId, 
                                   UInt16 binding) 
{
    UInt32 key = (UInt32(groupId) << 16) | binding;

    AttachmentMap::iterator fcI = _attachmentMap.getValue().find(key);
    
    return (fcI == _attachmentMap.getValue().end()) ? 
        NullAttachment : (*fcI).second;
}

void Node::setCore(const NodeCorePtr &core)
{
    NodePtr thisP = getPtr();

    thisP.setParentFieldPos(CoreFieldMask);

	if(_core.getValue() != NullFC)
    {
        beginEditCP(_core.getValue(), NodeCore::ParentsFieldMask);
        {
            _core.getValue()->subParent(thisP);
        }
        endEditCP  (_core.getValue(), NodeCore::ParentsFieldMask);

        subRefCP(_core.getValue());
    }

	_core.setValue(core);
	
	if(_core.getValue() != NullFC) 
    {
        beginEditCP(_core.getValue(), NodeCore::ParentsFieldMask);
        {
            _core.getValue()->addParent(thisP);
        }
        endEditCP  (_core.getValue(), NodeCore::ParentsFieldMask);

        addRefCP(_core.getValue());
	}

    // TODO Check if required (GV)
	invalidateVolume();
}

void Node::addChild(const NodePtr &childP)
{
    if(childP != NullFC)
    {
        _children.addValue(childP);

        beginEditCP(childP, Node::ParentFieldMask);
        {
            childP->setParent(getPtr());
        }
        endEditCP  (childP, Node::ParentFieldMask);

        addRefCP(childP);
    }

    // TODO Check if required (GV)
	invalidateVolume();
}

void Node::insertChild(UInt32 childIndex, const NodePtr &childP)
{    
    MFNodePtr::iterator childIt = _children.begin();

    if(childP != NullFC)
    {
        childIt   += childIndex;

        _children.insert(childIt, childP);

        beginEditCP(childP, Node::ParentFieldMask);
        {
            childP->setParent(getPtr());
        }
        endEditCP  (childP, Node::ParentFieldMask);

        addRefCP(childP);
    }

    // TODO check if required (GV)
	invalidateVolume();
}

void Node::replaceChild(UInt32 childIndex, const NodePtr &childP)
{
    if(childP != NullFC)
    {
        addRefCP(childP);

        beginEditCP(_children.getValue(childIndex), Node::ParentFieldMask);
        {
            _children.getValue(childIndex)->setParent(NullNode);
        }
        endEditCP  (_children.getValue(childIndex), Node::ParentFieldMask);

        subRefCP(_children.getValue(childIndex));


        _children.getValue(childIndex) = childP;


        beginEditCP(childP, Node::ParentFieldMask);
        {
            childP->setParent(getPtr());
        }
        endEditCP  (childP, Node::ParentFieldMask);
    }

    // TODO check if required (GV)
	invalidateVolume();
}

void Node::replaceChildBy(const NodePtr &childP, 
                          const NodePtr &newChildP)
{
    MFNodePtr::iterator childIt = _children.find(childP);

    if(newChildP != NullFC)
    {
        if(childIt != _children.end())
        {
            addRefCP(newChildP);

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
        }
    }

    // TODO check if required (GV)
	invalidateVolume();
}

Int32 Node::findChild(const NodePtr &childP) const
{
	UInt32 index;

	for(index = 0; index < _children.size(); index++)
    {
		if( _children[index] == childP)
			break;
    }

	if(index < _children.size())
		return index;
	else
		return -1;
}

void Node::subChild(const NodePtr &childP)
{
    MFNodePtr::iterator childIt = _children.find(childP);

    if(childIt != _children.end())
    {
        beginEditCP(childP, Node::ParentFieldMask);
        {
            childP->setParent(NullNode);
        }
        endEditCP  (childP, Node::ParentFieldMask);

        subRefCP(childP);

        _children.erase(childIt);
    }

    // TODO check if required (GV)
	invalidateVolume();
}

void Node::subChild(UInt32 childIndex)
{
    MFNodePtr::iterator childIt = _children.begin();

    childIt += childIndex;

    if(childIt != _children.end())
    {
        beginEditCP(*childIt, Node::ParentFieldMask);
        {
            (*childIt)->setParent(NullNode);
        }
        endEditCP  (*childIt, Node::ParentFieldMask);

        subRefCP(*childIt);

        _children.erase(childIt);
    }

    // TODO check if required (GV)
	invalidateVolume();
}

NodePtr Node::getChild(UInt32 childIndex)
{
    return _children.getValue(childIndex);
}

/*---------------------------- properties ---------------------------------*/

SFDynamicVolume *Node::getSFVolume(void) 
{
    return &_volume; 
}

SFNodePtr *Node::getSFParent(void)
{
    return &_parent;
}

SFNodeCorePtr *Node::getSFCore(void)
{
    return &_core;
}

MFNodePtr *Node::getMFChildren(void)
{
    return &_children;
}

SFAttachmentMap *Node::getSFAttachments(void)
{
    return &_attachmentMap;
}

NodePtr Node::getPtr(void)
{
    return Inherited::getPtr<NodePtr>(*this);
}

/*-------------------------- your_category---------------------------------*/

Matrix Node::getToWorld(void)
{
	Matrix tmp;
	
	getToWorld(tmp);
	
	return tmp;
}
	
void Node::getToWorld(Matrix &result)
{
	if(getParent() != NullNode)
    {
		getParent()->getToWorld(result);
    }
	else
    {
		result.setIdentity();
    }

	getCore()->accumulateMatrix(result);
}

/*-------------------------- assignment -----------------------------------*/

void Node::getWorldVolume(DynamicVolume &result)
{	
	Matrix m;
	
	if(getParent() != NullFC)
		getParent()->getToWorld(m);
	else
		m.setIdentity();
		
	updateVolume();
	result = getVolume();
	result.transform(m);
}
	
void Node::updateVolume(void)
{
	Volume & vol = _volume.getValue().getInstance();

	if(vol.isValid())
		return;				// still valid, nothing to do

	MFNodePtr::iterator it;

    beginEdit(VolumeFieldMask, _volume);

	vol.setEmpty();

	for(it = _children.begin(); it != _children.end(); it++)
	{
		(*it)->updateVolume();
		vol.extendBy((*it)->getVolume());
	}

	// test for null core. Shouldn't happen, but just in case...
	if(getCore() != NullFC) 
		getCore()->adjustVolume(vol);

    endEdit(VolumeFieldMask, _volume);
}

void Node::invalidateVolume(void)
{
    if(_volume.getValue().getInstance().isValid() == true)
    {
        beginEdit(VolumeFieldMask, _volume);

        _volume.getValue().getInstance().setValid(false);

        endEdit(VolumeFieldMask, _volume);

        if(getParent() != NullFC)
        {
            getParent()->invalidateVolume();
        }
    }
}

void Node::changed(BitVector  whichField, 
                   ChangeMode from)
{
    if(whichField & (CoreFieldMask | ChildrenFieldMask))
    {
        invalidateVolume();
    }
}

/*------------------------------- dump ----------------------------------*/

void Node::dump(      UInt32     uiIndent, 
                const BitVector &bvFlags) const
{
    UInt32 i;

    indentLog(uiIndent, PLOG);
    
    PLOG << "Node : " << _children.size() << " children | "
         << _attachmentMap.getValue().size() << " attachments | "
         << "Parent : ";

    if(_parent.getValue() != NullNode)
        PLOG << &(*(_parent.getValue())) << " | ";
    else
        PLOG << "NULL | ";

    PLOG << this << endl;
    
    indentLog(uiIndent, PLOG);

    PLOG << "[" << endl;

    if(_core.getValue() != NullNode)
    {
        _core.getValue()->dump(uiIndent + 4, bvFlags);
    }
    else
    {
        indentLog(uiIndent + 4, PLOG);
        PLOG << "Core : " << "NULL" << endl;
    }

    AttachmentMap::const_iterator fcI;

    fcI = _attachmentMap.getValue().begin();

    while(fcI != _attachmentMap.getValue().end())
    {
        (*fcI).second->dump(uiIndent + 4, bvFlags);
        ++fcI;
    }

    indentLog(uiIndent, PLOG);
    PLOG << "]" << endl;

    indentLog(uiIndent, PLOG);

    PLOG << "{" << endl;

    for(i = 0; i < _children.size(); i++)
    {
        _children[i]->dump(uiIndent + 4, bvFlags);
        PLOG << endl;
    }


    indentLog(uiIndent, PLOG);

    PLOG << "}" << endl;

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
    
    cerr << "{" << endl;


    for(i = 0; i < indent; i++)
    {
        cerr << " ";
    }

    cerr << "}" << endl;
*/
}

/*-------------------------- comparison -----------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

Node::Node(void) :
    Inherited     (),
    _parent       (),
    _children     (),
    _core         (),
    _attachmentMap()
{
}

/** \brief CopyConstructor, used only by the protoype mechanism
 */

Node::Node(const Node &source) :
    Inherited     (source),
    _parent       (),
    _children     (),
    _core         (),
    _attachmentMap()
{
}

/** \brief Destructor
 */

Node::~Node (void )
{
    // TODO Unlink Tree
}

/*------------------------------ access -----------------------------------*/

void Node::setParent(const NodePtr &parent)
{ 
    addRefCP(parent);

    subRefCP(_parent.getValue());

    _parent.setValue(parent);
}

void Node::onCreate(void)
{
}

void Node::onCreate(const Node &source)
{
    setCore(source.getCore());

    AttachmentMap::const_iterator fcI=source._attachmentMap.getValue().begin();

    while(fcI != source._attachmentMap.getValue().end())
    {
        addAttachment((*fcI).second);

        fcI++;
    }
}

void Node::executeSync(FieldContainer &other,
                       BitVector       whichField)
{
    this->executeSyncImpl((Node *) &other, whichField);
}

void Node::executeSyncImpl(Node      *pOther,
                           BitVector  whichField)
{
    Inherited::executeSyncImpl(pOther, whichField);

    if(FieldBits::NoField != (VolumeFieldMask & whichField))
    {
        _volume.syncWith(pOther->_volume);
    }

    if(FieldBits::NoField != (ParentFieldMask & whichField))
    {
        _parent.syncWith(pOther->_parent);
    }

    if(FieldBits::NoField != (ChildrenFieldMask & whichField))
    {
        _children.syncWith(pOther->_children);
    }

    if(FieldBits::NoField != (CoreFieldMask & whichField))
    {
        _core.syncWith(pOther->_core);
    }

    if(FieldBits::NoField != (AttachmentsFieldMask & whichField))
    {
        _attachmentMap.syncWith(pOther->_attachmentMap);
    }
}



/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

///---------------------------------------------------------------------------
///  FUNCTION: 
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters: 
//p: 
///
//g: GlobalVars:
//g: 
///
//r: Return:
//r: 
///
//c: Caution:
//c: 
///
//a: Assumptions:
//a: 
///
//d: Description:
//d: 
///
//s: SeeAlso:
//s: 
///---------------------------------------------------------------------------

