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
	FieldDescription(SFVolume::getClassType(), 
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

void Node::addAttachment(const AttachmentPtr &fieldContainerP)
{
    if(fieldContainerP == NullAttachment)
        return;

    _attachmentMap.getValue()[fieldContainerP->getTypeId()] = fieldContainerP;
    _attachmentMap.getValue()[fieldContainerP->getTypeId()]->addParent(
        getPtr());
}

void Node::subAttachment(const AttachmentPtr &fieldContainerP)
{
    AttachmentMap::iterator fcI;

    fcI = _attachmentMap.getValue().find(fieldContainerP->getTypeId());

    if(fcI != _attachmentMap.getValue().end())
    {
        (*fcI).second->subParent(getPtr());
        _attachmentMap.getValue().erase(fcI);
    }  
}

AttachmentPtr Node::findAttachment(UInt32 typeID) 
{
    AttachmentMap::iterator fcI = _attachmentMap.getValue().find(typeID);
    
    return (fcI == _attachmentMap.getValue().end()) ? 
        NullAttachment : (*fcI).second;
}

void Node::setCore(const NodeCorePtr &core)
{
    NodePtr thisP = getPtr();

    thisP.setParentFieldPos(CoreFieldMask);

	if(_core.getValue() != NullFC)
    {
        _core.getValue()->subParent(thisP);
    }

	_core.setValue(core);
	
	if(_core.getValue() != NullFC) 
    {
        _core.getValue()->addParent(thisP);
	}
}

void Node::addChild(const NodePtr &childP)
{
    if(childP != NullFC)
    {
        beginEdit(ChildrenFieldMask, _children);

        _children.addValue(childP);
        _children.back()->setParent(getPtr());

        endEdit(ChildrenFieldMask, _children);
    }
}

void Node::insertChild(UInt32 childIndex, const NodePtr &childP)
{    
    MFNodePtr::iterator childIt = _children.begin();

    if(childP != NullFC)
    {
        childIt += childIndex;
        
        (*(_children.insert(childIt, childP)))->setParent(getPtr());
        
    }
}

void Node::replaceChild(UInt32 childIndex, const NodePtr &childP)
{
    if(childP != NullFC)
    {
        _children.getValue(childIndex)->setParent(NullNode);
        _children.getValue(childIndex) = childP;
        _children.getValue(childIndex)->setParent(getPtr());
    }
}

void Node::replaceChildBy(const NodePtr &childP, 
                          const NodePtr &newChildP)
{
    MFNodePtr::iterator childIt = _children.find(childP);

    if(newChildP != NullFC)
    {
        if(childIt != _children.end())
        {
            (*childIt)->setParent(NullNode);
            (*childIt) = newChildP;
            (*childIt)->setParent(getPtr());
        }
    }
}

void Node::subChild(const NodePtr &childP)
{
    MFNodePtr::iterator childIt = _children.find(childP);

    if(childIt != _children.end())
    {
        (*childIt)->setParent(NullNode);

        _children.erase(childIt);
    }

}

void Node::subChild(UInt32  childIndex)
{
    MFNodePtr::iterator childIt = _children.begin();

    childIt += childIndex;

    if(childIt != _children.end())
    {
        (*childIt)->setParent(NullNode);

        _children.erase(childIt);
    }
}

NodePtr Node::getChild(UInt32  childIndex)
{
    return _children.getValue(childIndex);
}

/*---------------------------- properties ---------------------------------*/

SFVolume *Node::getSFVolume(void) 
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

void Node::getWorldVolume(Volume &result)
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
	Volume & vol = _volume.getValue().getVolume();

	if(vol.isValid())
		return;				// still valid, nothing to do

	MFNodePtr::iterator it;

	vol.setEmpty();

	for(it = _children.begin(); it != _children.end(); it++)
	{
		(*it)->updateVolume();
		vol.extendBy((*it)->getVolume());
	}
	
	getCore()->adjustVolume(vol);
	
	// notify the change
	
	// !!!! the change has to be added to the change list
	// don't know how to do that yet
}

void Node::invalidateVolume(void)
{
    if(_volume.getValue().getVolume().isValid() == true)
    {
        beginEdit(VolumeFieldMask, _volume);

        _volume.getValue().getVolume().setValid(false);

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

void Node::print(UInt32 indent) const
{
    UInt32 i;

    indentLog(indent, PLOG);
    
    PLOG << "Node : " << _children.size() << " children | "
         << _attachmentMap.getValue().size() << " attachments | "
         << "Parent : ";

    if(_parent.getValue() != NullNode)
        PLOG << &(*(_parent.getValue())) << " | ";
    else
        PLOG << "NULL | ";

    PLOG << this << endl;
    
    indentLog(indent, PLOG);

    PLOG << "[" << endl;

    if(_core.getValue() != NullNode)
    {
        _core.getValue()->print(indent + 4);
    }
    else
    {
        indentLog(indent + 4, PLOG);
        PLOG << "Core : " << "NULL" << endl;
    }

    indentLog(indent, PLOG);

    PLOG << "]" << endl;

    indentLog(indent, PLOG);

    PLOG << "{" << endl;


    for(i = 0; i < _children.size(); i++)
    {
        _children[i]->print(indent + 4);
        PLOG << endl;
    }


    indentLog(indent, PLOG);

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
        (*fcI).second->print(indent + 2);
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

void Node::dump(void) const
{
    print(0);
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
    _parent       (source._parent),
    _children     (source._children),
    _core         (source._core),
    _attachmentMap(source._attachmentMap)
{
}

/** \brief Destructor
 */

Node::~Node (void )
{
}

/*------------------------------ access -----------------------------------*/

void Node::setParent(const NodePtr &parent)
{
    _parent.setValue(parent);
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

