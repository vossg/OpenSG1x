/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
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

#include "OSGFieldContainerPtr.h"

#include "OSGFieldContainerType.h"

#include "OSGNode.h"
#include "OSGNodeCore.h"
#include "OSGAttachment.h"

OSG_USING_NAMESPACE

/** \enum OSGVecBase::VectorSizeE
 *  \brief 
 */

/** \var OSGVecBase::VectorSizeE OSGVecBase::_iSize
 * 
 */

/** \fn const char *OSGVecBase::getClassname(void)
 *  \brief Classname
 */

/** \var OSGValueTypeT OSGVecBase::_values[iSize];
 *  \brief Value store
 */


 /***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/* Could not put this in the class declaration, since MS interprets them there
 * as pure virtual functions :-( (GV)
 */

OSG_FC_FIRST_FIELD_IDM_DEF(OSGNode, OSGNameField)

OSG_FC_FIELD_IDM_DEF      (OSGNode, OSGVolumeField,      OSGNameField)
OSG_FC_FIELD_IDM_DEF      (OSGNode, OSGParentField,      OSGVolumeField)
OSG_FC_FIELD_IDM_DEF      (OSGNode, OSGChildrenField,    OSGParentField)
OSG_FC_FIELD_IDM_DEF      (OSGNode, OSGCoreField,        OSGChildrenField)
OSG_FC_FIELD_IDM_DEF      (OSGNode, OSGAttachmentsField, OSGCoreField)

OSG_FC_LAST_FIELD_IDM_DEF (OSGNode, OSGAttachmentsField)

OSGFieldDescription OSGNode::_desc[] = 
{
	OSGFieldDescription(OSGSFString::getClassType(), 
                        "name", 
                        OSG_FC_FIELD_IDM_DESC(OSGNameField),
                        false,
                        (OSGFieldAccessMethod) &OSGNode::getSFName),

	OSGFieldDescription(OSGSFVolume::getClassType(), 
                        "volume", 
                        OSG_FC_FIELD_IDM_DESC(OSGVolumeField),
                        false,
                        (OSGFieldAccessMethod) &OSGNode::getSFVolume),

	OSGFieldDescription(OSGSFNodePtr::getClassType(),
                        "parent", 
                        OSG_FC_FIELD_IDM_DESC(OSGParentField),
                        false,
                        (OSGFieldAccessMethod) &OSGNode::getSFParent),

	OSGFieldDescription(OSGMFNodePtr::getClassType(), 
                        "children", 
                        OSG_FC_FIELD_IDM_DESC(OSGChildrenField),
                        false,
                        (OSGFieldAccessMethod) &OSGNode::getMFChildren),

    OSGFieldDescription(OSGSFNodeCorePtr::getClassType(),
                        "core",
                        OSG_FC_FIELD_IDM_DESC(OSGCoreField),
                        false,	
                        (OSGFieldAccessMethod) &OSGNode::getSFCore),

    OSGFieldDescription(OSGSFAttachmentMap::getClassType(),
                        "attachments",
                        OSG_FC_FIELD_IDM_DESC(OSGAttachmentsField),
                        false,	
                        (OSGFieldAccessMethod) &OSGNode::getSFAttachments)
};

OSGFieldContainerType OSGNode::_type(
    "Node", 
    "FieldContainer", 
    0,
    (OSGPrototypeCreateF) &OSGNode::createEmpty,
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

OSG_FIELD_CONTAINER_DEF(OSGNode, OSGNodePtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

OSGNode::OSGNode (void ) :
    _name(),
    _parent(),
    _children(),
    _core(),
    _attachmentMap()
{
}

/** \brief CopyConstructor, used only by the protoype mechanism
 */

OSGNode::OSGNode(const OSGNode &source) :
    Inherited(),
    _name(source._name),
    _parent(source._parent),
    _children(source._children),
    _core(source._core),
    _attachmentMap(source._attachmentMap)
{
}

/** \brief Destructor
 */

OSGNode::~OSGNode (void )
{
	return;
}


/*------------------------------ access -----------------------------------*/


void OSGNode::setParent(const OSGNodePtr &parent)
{
    _parent.setValue(parent);
}

OSGNodePtr OSGNode::getParent(void)
{
    return _parent.getValue();
}

void OSGNode::addAttachment(const OSGAttachmentPtr &fieldContainerP)
{
    if(fieldContainerP == OSGNullAttachment)
        return;

    _attachmentMap.getValue()[fieldContainerP->getTypeID()] = fieldContainerP;
    _attachmentMap.getValue()[fieldContainerP->getTypeID()]->addParent(
        getPtr());
}

void OSGNode::subAttachment(const OSGAttachmentPtr &fieldContainerP)
{
    OSGAttachmentMap::iterator fcI;

    fcI = _attachmentMap.getValue().find(fieldContainerP->getTypeID());

    if(fcI != _attachmentMap.getValue().end())
    {
        (*fcI).second->subParent(getPtr());
        _attachmentMap.getValue().erase(fcI);
    }  
}

OSGAttachmentPtr OSGNode::findAttachment (int typeID) 
{
    OSGAttachmentMap::iterator fcI = _attachmentMap.getValue().find(typeID);
    
    return (fcI == _attachmentMap.getValue().end()) ? 
        OSGNullAttachment : (*fcI).second;
}

OSGNodeCorePtr OSGNode::getCore(void)     
{
    return _core.getValue(); 
}

void OSGNode::setCore(const OSGNodeCorePtr &core)
{
    OSGNodePtr thisP = getPtr();

    thisP.setParentFieldPos(OSGCoreFieldMask);

	if(_core.getValue() != OSGNullFC)
    {
        _core.getValue()->subParent(thisP);
    }

	_core.setValue(core);
	
	if(_core.getValue() != OSGNullFC) 
    {
        _core.getValue()->addParent(thisP);
	}
}

OSGUInt32 OSGNode::getNChildren(void) const 
{
    return _children.size(); 
}

void OSGNode::addChild(const OSGNodePtr &childP)
{
    if(childP != OSGNullFC)
    {
        beginEdit(OSGChildrenFieldMask, _children);

        _children.addValue(childP);
        _children.back()->setParent(getPtr());

        endEdit(OSGChildrenFieldMask, _children);
    }
}

void OSGNode::insertChild(OSGUInt32 childIndex, const OSGNodePtr &childP)
{    
    OSGMFNodePtr::iterator childIt = _children.begin();

    if(childP != OSGNullFC)
    {
        childIt += childIndex;
        
        (*(_children.insert(childIt, childP)))->setParent(getPtr());
        
    }
}

void OSGNode::replaceChild(OSGUInt32 childIndex, const OSGNodePtr &childP)
{
    if(childP != OSGNullFC)
    {
        _children.getValue(childIndex)->setParent(OSGNullNode);
        _children.getValue(childIndex) = childP;
        _children.getValue(childIndex)->setParent(getPtr());
    }
}

void OSGNode::replaceChildBy(const OSGNodePtr &childP, 
                             const OSGNodePtr &newChildP)
{
    OSGMFNodePtr::iterator childIt = _children.find(childP);

    if(newChildP != OSGNullFC)
    {
        if(childIt != _children.end())
        {
            (*childIt)->setParent(OSGNullNode);
            (*childIt) = newChildP;
            (*childIt)->setParent(getPtr());
        }
    }
}

void OSGNode::subChild(const OSGNodePtr &childP)
{
    OSGMFNodePtr::iterator childIt = _children.find(childP);

    if(childIt != _children.end())
    {
        (*childIt)->setParent(OSGNullNode);

        _children.erase(childIt);
    }

}

void OSGNode::subChild(OSGUInt32  childIndex)
{
    OSGMFNodePtr::iterator childIt = _children.begin();

    childIt += childIndex;

    if(childIt != _children.end())
    {
        (*childIt)->setParent(OSGNullNode);

        _children.erase(childIt);
    }
}

/*---------------------------- properties ---------------------------------*/


OSGNodePtr OSGNode::getChild(OSGUInt32  childIndex)
{
    return _children.getValue(childIndex);
}

OSGSFString *OSGNode::getSFName(void) 
{
    return &_name; 
}

OSGSFVolume *OSGNode::getSFVolume(void) 
{
    return &_volume; 
}

OSGSFNodePtr *OSGNode::getSFParent(void)
{
    return &_parent;
}

OSGSFNodeCorePtr *OSGNode::getSFCore(void)
{
    return &_core;
}

OSGMFNodePtr *OSGNode::getMFChildren(void)
{
    return &_children;
}

OSGSFAttachmentMap *OSGNode::getSFAttachments(void)
{
    return &_attachmentMap;
}


OSGNodePtr OSGNode::getPtr(void)
{
    return Inherited::getPtr<OSGNodePtr>(*this);
}

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

void OSGNode::print(OSGUInt32 indent) const
{
    OSGUInt32 i;

    for(i = 0; i < indent; i++)
    {
        cerr << " ";
    }

    fprintf(stderr, "Node : %d children | %p\n", _children.size(), this);
    
    
    for(i = 0; i < indent; i++)
    {
        cerr << " ";
    }
    cerr << "  Parent : ";

    if(_parent.getValue() != OSGNullNode)
        _parent.getValue().dump();
    else
        cerr << "NULL" << endl;

    for(i = 0; i < indent; i++)
    {
        cerr << " ";
    }
    cerr << "  Core   : ";

    if(_core.getValue() != OSGNullNode)
        _core.getValue().dump();
    else
        cerr << "NULL" << endl;

    for(i = 0; i < indent; i++)
        fprintf(stderr, " ");

    fprintf(stderr, "NAttachments : \n");

    map<OSGUInt32, OSGAttachmentPtr>::const_iterator fcI;

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

    for(i = 0; i < _children.size(); i++)
    {
        _children[i]->print(indent + 4);
    }

    for(i = 0; i < indent; i++)
    {
        cerr << " ";
    }

    cerr << "}" << endl;
}
	
/** Transformations */

OSGMatrix OSGNode::getToWorld( void )
{
	OSGMatrix tmp;
	
	getToWorld( tmp );
	
	return tmp;
}
	
void OSGNode::getToWorld( OSGMatrix & result )
{
	if ( getParent() != OSGNullNode )
		getParent()->getToWorld( result );
	else
		result.setIdentity();

	getCore()->accumulateMatrix( result );
}
	
/** Volumes */
	
void OSGNode::getWorldVolume( OSGVolume & result )
{	
	OSGMatrix m;
	
	if ( getParent() != OSGNullFC )
		getParent()->getToWorld( m );
	else
		m.setIdentity();
		
	updateVolume();
	result = getVolume();
	result.transform( m );
}
	
void OSGNode::updateVolume( void )
{
	OSGVolume & vol = _volume.getValue().getVolume();

	if ( vol.isValid() )
		return;				// still valid, nothing to do

	OSGMFNodePtr::iterator it;

	vol.setEmpty();

	for ( it = _children.begin(); it != _children.end(); it++ )
	{
		(*it)->updateVolume();
		vol.extendBy( (*it)->getVolume() );
	}
	
	getCore()->adjustVolume( vol );
	
	// notify the change
	
	// !!!! the change has to be added to the change list
	// don't know how to do that yet
}

void OSGNode::invalidateVolume(void)
{
    if(_volume.getValue().getVolume().isValid() == true)
    {
        beginEdit(OSGVolumeFieldMask, _volume);
        _volume.getValue().getVolume().setValid(false);
        endEdit(OSGVolumeFieldMask, _volume);

        if(getParent() != OSGNullFC)
        {
            getParent()->invalidateVolume();
        }
    }
}

void OSGNode::changed(OSGBitVector  whichField, 
                      OSGChangeMode from)
{
    if(whichField & (OSGCoreFieldMask | OSGChildrenFieldMask))
    {
        invalidateVolume();
    }
}

/*------------------------------- dump ----------------------------------*/

void OSGNode::dump(void) const
{
    SDEBUG << "Dump OSGNode NI" << endl;
}

/*-------------------------- comparison -----------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


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

