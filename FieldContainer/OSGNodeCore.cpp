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

OSG_FC_FIRST_FIELD_IDM_DEF(NodeCore, ParentsField)

OSG_FC_FIELD_IDM_DEF      (NodeCore, AttachmentsField, ParentsField)

OSG_FC_LAST_FIELD_IDM_DEF (NodeCore, AttachmentsField)

FieldDescription NodeCore::_desc[] = 
{
	FieldDescription(MFNodePtr::getClassType(), 
                     "parents", 
                     OSG_FC_FIELD_IDM_DESC(ParentsField),
                     false,
                     (FieldAccessMethod) &NodeCore::getMFParents),
    
    FieldDescription(SFAttachmentMap::getClassType(),
                     "attachments", 
                     OSG_FC_FIELD_IDM_DESC(AttachmentsField),
                     false,
                     (FieldAccessMethod) &NodeCore::getSFAttachments)
};

FieldContainerType NodeCore::_type("NodeCore",
                                   "FieldContainer",
                                   NULL,
                                   NULL,
                                   NULL,
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

OSG_ABSTR_FIELD_CONTAINER_DEF(NodeCore, NodeCorePtr)

/*------------------------------ access -----------------------------------*/

MFNodePtr *NodeCore::getMFParents(void)
{
    return &_parents;
}

SFAttachmentMap *NodeCore::getSFAttachments(void)
{
    return &_attachmentMap;
}

void NodeCore::addAttachment(AttachmentPtr &fieldContainerP,
                                UInt16         binding)
{
	UInt32 key;

	if(fieldContainerP == NullAttachment)
        return;

	key = (UInt32 (fieldContainerP->getGroupId()) << 16) | binding;
	
	fieldContainerP->addParent(getPtr());

	_attachmentMap.getValue()[key] = fieldContainerP;
}

void NodeCore::subAttachment(AttachmentPtr &fieldContainerP,
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
        (*fcI).second->subParent(getPtr());
        _attachmentMap.getValue().erase(fcI);
    }  
}

AttachmentPtr NodeCore::findAttachment(UInt16 groupId, 
                                             UInt16 binding)
{
	UInt32 key = (UInt32(groupId) << 16) | binding;

	AttachmentMap::iterator fcI = _attachmentMap.getValue().find(key);
	
	return (fcI == _attachmentMap.getValue().end()) ? 
        NullAttachment : fcI->second;
}



/*---------------------------- properties ---------------------------------*/

NodeCorePtr NodeCore::getPtr(void)
{
    NodeCorePtr returnValue(*this);

    return returnValue;
}

/*-------------------------- your_category---------------------------------*/

void NodeCore::accumulateMatrix(Matrix &)
{
}

void NodeCore::adjustVolume(Volume &)
{
}

/*-------------------------- assignment -----------------------------------*/

void NodeCore::print(UInt32 indent) const
{
    UInt32 i;
    UInt32 j;

    for(i = 0; i < indent; i++)
        fprintf(stderr, " ");

    fprintf(stderr, "NCParents : \n");

    for(i = 0; i < _parents.size(); i++)
    {
        for(j = 0; j < indent + 1; j++)
            fprintf(stderr, " ");

        _parents[i].dump();
    }

    for(i = 0; i < indent; i++)
        fprintf(stderr, " ");

    fprintf(stderr, "NCAttachments : \n");

    AttachmentMap::const_iterator fcI;

    fcI = _attachmentMap.getValue().begin();

    while(fcI != _attachmentMap.getValue().end())
    {
        (*fcI).second->print(indent + 2);
        ++fcI;
    }
}

/*------------------------------- dump ----------------------------------*/

void NodeCore::dump(void) const
{
    SDEBUG << "Dump NodeCore NI" << endl;
}

/*-------------------------- comparison -----------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

NodeCore::NodeCore(void) :
    Inherited     (),
    _parents      (),
    _attachmentMap()
{
	return;
}

/** \brief Copy Constructor
 */

NodeCore::NodeCore(const NodeCore &obj) :
    Inherited     (obj),
    _parents      (),
    _attachmentMap(obj._attachmentMap)
{
}

/** \brief Destructor
 */

NodeCore::~NodeCore (void )
{
}

void NodeCore::addParent(const NodePtr &parent)
{
    _parents.addValue(parent);
}

void NodeCore::subParent(const NodePtr &parent)
{
    MFNodePtr::iterator parentIt = _parents.find(parent);

    if(parentIt != _parents.end())
    {
        _parents.erase(parentIt);
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
