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

#define OSG_COMPILESYSTEMLIB

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGNode.h"
#include "OSGNodeCore.h"
#include "OSGAttachment.h"

OSG_USING_NAMESPACE

const NodeCorePtr OSG::NullNodeCore;

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const BitVector 
	NodeCore::ParentsFieldMask     = (1 << NodeCore::ParentsFieldId    );
const BitVector 
	NodeCore::AttachmentsFieldMask = (1 << NodeCore::AttachmentsFieldId);

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

SFAttachmentMap *NodeCore::getSFAttachments(void)
{
    return &_attachmentMap;
}

void NodeCore::addAttachment(const AttachmentPtr &fieldContainerP,
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

void NodeCore::subAttachment(const AttachmentPtr &fieldContainerP,
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
    return NodeCorePtr(*this);
}

/*-------------------------- your_category---------------------------------*/

void NodeCore::accumulateMatrix(Matrix &)
{
}

void NodeCore::adjustVolume(Volume &)
{
}

/*-------------------------- assignment -----------------------------------*/

void NodeCore::dump(      UInt32     uiIndent, 
                    const BitVector &bvFlags) const
{
    UInt32 i;

    indentLog(uiIndent, PLOG);

    PLOG << "Core : " << getType().getName()
         << "("       << this << ")" << endl;

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

    AttachmentMap::const_iterator fcI;

    fcI = _attachmentMap.getValue().begin();

    while(fcI != _attachmentMap.getValue().end())
    {
        (*fcI).second->dump(uiIndent + 4, bvFlags);
        ++fcI;
    }

    indentLog(uiIndent, PLOG);
    PLOG << "}" << endl;
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
    _attachmentMap()
{
    AttachmentMap::const_iterator fcI = obj._attachmentMap.getValue().begin();

    while(fcI != obj._attachmentMap.getValue().end())
    {
        addAttachment((*fcI).second);

        fcI++;
    }
}

/** \brief Destructor
 */

NodeCore::~NodeCore (void )
{
}

void NodeCore::onDestroy(void)
{
/*
    MFNodePtr::iterator parentIt = _parents.begin();

    while(parentIt != _parents.end())
    {
        subRefCP(*parentIt);
        parentIt++;
    }
*/
}

void NodeCore::addParent(const NodePtr &parent)
{
     addRefCP(parent);
    _parents.addValue(parent);
}

void NodeCore::subParent(const NodePtr &parent)
{
    MFNodePtr::iterator parentIt = _parents.find(parent);

    if(parentIt != _parents.end())
    {
         subRefCP(parent);
        _parents.erase(parentIt);
    }
}

void NodeCore::executeSync(FieldContainer &other,
                           BitVector       whichField)
{
    this->executeSyncImpl((NodeCore *) &other, whichField);
}


void NodeCore::executeSyncImpl(NodeCore  *pOther,
                               BitVector  whichField)
{
    Inherited::executeSyncImpl(pOther, whichField);

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        _parents.syncWith(pOther->_parents);
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
