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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"
#include "OSGFieldContainerPtr.h"
#include "OSGFieldContainerType.h"
#include "OSGNode.h"
#include "OSGNodeCore.h"
#include "OSGBinaryDataHandler.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static char cvsid_cpp[] = "@(#)$Id: $";
    static char cvsid_hpp[] = OSGNODE_HEADER_CVSID;
    static char cvsid_inl[] = OSGNODE_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/** \brief NULL node pointer
 */

//const NodePtr OSG::NullNode;

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/* Could not put this in the class declaration, since MS interprets them there
 * as pure virtual functions :-( (GV)
 */

const BitVector Node::VolumeFieldMask      = (1 << Node::VolumeFieldId     );
const BitVector Node::ParentFieldMask      = (1 << Node::ParentFieldId     );
const BitVector Node::ChildrenFieldMask    = (1 << Node::ChildrenFieldId   );
const BitVector Node::CoreFieldMask        = (1 << Node::CoreFieldId       );

FieldDescription *Node::_desc[] = 
{
	new FieldDescription(SFDynamicVolume::getClassType(), 
                         "volume", 
                         OSG_FC_FIELD_IDM_DESC(VolumeField),
                         false,
                         (FieldAccessMethod) &Node::getSFVolume),

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
    "FieldContainer", 
    0,
    (PrototypeCreateF) &Node::createEmpty,
    0,
    _desc, 
    sizeof(_desc));


const NodePtr Node::NullNode(NullFC);

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

/*! \fn FieldContainerType &Node::getClassType(void) 
 *  \brief returns node type
 */

/*! \fn UInt32 Node::getClassTypeId(void) 
 *  \brief returns node type id
 */

/*! \fn NodePtr Node::create(void) 
 *  \brief creates a clone of the prototype
 */

/*! \fn NodePtr Node::createEmpty(void) 
 *  \brief creates a empty node, does not clone the prototype
 */

OSG_FIELD_CONTAINER_DEF(Node, NodePtr)

/*------------------------------ access -----------------------------------*/

void Node::setCore(const NodeCorePtr &core)
{
    NodePtr thisP = getPtr();

    thisP.setParentFieldPos(CoreFieldId);

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
		// do the ref early, to prevent destroys on getParent(a)->addChild(a)
		addRefCP(childP);

		// already somebody else's child?
		if ( childP->getParent() != NullFC )
		{
			childP->getParent()->subChild( childP );
		}
		
        _children.addValue(childP);

        beginEditCP(childP, Node::ParentFieldMask);
        {
            childP->setParent(getPtr());
        }
        endEditCP  (childP, Node::ParentFieldMask);

		// TODO Check if required (GV)
		invalidateVolume();
    }
}

void Node::insertChild(UInt32 childIndex, const NodePtr &childP)
{    
    MFNodePtr::iterator childIt = _children.begin();

    if(childP != NullFC)
    {
		// do the ref early, to prevent destroys on getParent(a)->addChild(a)
		addRefCP(childP);

		// already somebody else's child?
		if ( childP->getParent() != NullFC )
		{
			childP->getParent()->subChild( childP );
		}
		
        childIt   += childIndex;

        _children.insert(childIt, childP);

        beginEditCP(childP, Node::ParentFieldMask);
        {
            childP->setParent(getPtr());
        }
        endEditCP  (childP, Node::ParentFieldMask);
    }

    // TODO check if required (GV)
	invalidateVolume();
}

void Node::replaceChild(UInt32 childIndex, const NodePtr &childP)
{
    if(childP != NullFC)
    {		
		// do the ref early, to prevent destroys on getParent(a)->addChild(a)
        addRefCP(childP);

		// remove the current child
        beginEditCP(_children.getValue(childIndex), Node::ParentFieldMask);
        {
            _children.getValue(childIndex)->setParent(NullNode);
        }
        endEditCP  (_children.getValue(childIndex), Node::ParentFieldMask);

        subRefCP(_children.getValue(childIndex));

		// already somebody else's child?
		if ( childP->getParent() != NullNode )
		{
			childP->getParent()->subChild( childP );
		}

		// set the new child
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

//! return true on success, false on child not found

Bool Node::replaceChildBy(const NodePtr &childP, 
                          const NodePtr &newChildP)
{
    MFNodePtr::iterator childIt = _children.find(childP);

    if(newChildP != NullFC)
    {
        if(childIt != _children.end())
        {
			// do the ref early, to prevent destroys on getParent(a)->addChild(a)
			addRefCP(newChildP);

            beginEditCP(childP, Node::ParentFieldMask);
            {
                childP->setParent(NullNode);
            }
            endEditCP  (childP, Node::ParentFieldMask);

            subRefCP(childP);

			// already somebody else's child?
			if ( newChildP->getParent() != NullFC )
			{
				newChildP->getParent()->subChild( newChildP );
			}

            (*childIt) = newChildP;

            beginEditCP(newChildP, Node::ParentFieldMask);
            {
                newChildP->setParent(getPtr());
            }
            endEditCP  (newChildP, Node::ParentFieldMask);
		
			// TODO check if required (GV)
			invalidateVolume();
			
			return true;
        }
    }

	return false;
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

NodePtr Node::getPtr(void)
{
    return NodePtr(*this);
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

UInt32 Node::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (VolumeFieldMask & whichField))
    {
        returnValue += _volume       .getBinSize();
    }

    if(FieldBits::NoField != (ParentFieldMask & whichField))
    {
        returnValue += _parent       .getBinSize();
    }

    if(FieldBits::NoField != (ChildrenFieldMask & whichField))
    {
        returnValue += _children     .getBinSize();
    }

    if(FieldBits::NoField != (CoreFieldMask & whichField))
    {
        returnValue += _core         .getBinSize();
    }
    
    return returnValue;
}

void Node::copyToBin  (      BinaryDataHandler &pMem, 
                       const BitVector         &whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (VolumeFieldMask & whichField))
    {
        _volume.copyToBin(pMem);
    }

    if(FieldBits::NoField != (ParentFieldMask & whichField))
    {
        _parent.copyToBin(pMem);
    }

    if(FieldBits::NoField != (ChildrenFieldMask & whichField))
    {
        _children.copyToBin(pMem);
    }

    if(FieldBits::NoField != (CoreFieldMask & whichField))
    {
        _core.copyToBin(pMem);
    }
}

void Node::copyFromBin(      BinaryDataHandler &pMem, 
                       const BitVector         &whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (VolumeFieldMask & whichField))
    {
        _volume.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (ParentFieldMask & whichField))
    {
        _parent.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (ChildrenFieldMask & whichField))
    {
        _children.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (CoreFieldMask & whichField))
    {
        _core.copyFromBin(pMem);
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

    if(_parent.getValue() != NullFC)
        PLOG << &(*(_parent.getValue())) << " | ";
    else
        PLOG << "NULL | ";

    PLOG << this << endl;
    
    indentLog(uiIndent, PLOG);

    PLOG << "[" << endl;

    if(_core.getValue() != NullFC)
    {
        _core.getValue()->dump(uiIndent + 4, bvFlags);
    }
    else
    {
        indentLog(uiIndent + 4, PLOG);
        PLOG << "Core : " << "NULL" << endl;
    }

    Inherited::dump(uiIndent, bvFlags);

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
    _core         ()
{
}

/** \brief CopyConstructor, used only by the protoype mechanism
 */

Node::Node(const Node &source) :
    Inherited     (source),
    _parent       (),
    _children     (),
    _core         ()
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
	if ( parent != NullFC )
	    addRefCP(parent);

	if ( _parent.getValue() != NullFC )
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

void Node::executeSync(      FieldContainer &other,
                       const BitVector      &whichField)
{
    this->executeSyncImpl((Node *) &other, whichField);
}

void Node::executeSyncImpl(      Node      *pOther,
                           const BitVector &whichField)
{
    Inherited::executeSyncImpl(pOther, whichField);

    if (FieldBits::NoField != (VolumeFieldMask & whichField))
    {
        _volume.syncWith(pOther->_volume);
    }

    if (FieldBits::NoField != (ParentFieldMask & whichField))
    {
        _parent.syncWith(pOther->_parent);
    }

    if (FieldBits::NoField != (ChildrenFieldMask & whichField))
    {
        _children.syncWith(pOther->_children);
    }

    if (FieldBits::NoField != (CoreFieldMask & whichField))
    {
        _core.syncWith(pOther->_core);
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

