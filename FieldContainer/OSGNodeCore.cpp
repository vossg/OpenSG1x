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

OSG_FC_FIRST_FIELD_IDM_DEF(OSGNodeCore, OSGParentsField)

OSG_FC_FIELD_IDM_DEF      (OSGNodeCore, OSGAttachmentsField, OSGParentsField)

OSG_FC_LAST_FIELD_IDM_DEF (OSGNodeCore, OSGAttachmentsField)

OSGFieldDescription OSGNodeCore::_desc[] = 
{
	OSGFieldDescription(OSGMFNodePtr::getClassType(), 
                        "parents", 
                        OSG_FC_FIELD_IDM_DESC(OSGParentsField),
                        false,
                        (OSGFieldAccessMethod) &OSGNodeCore::getMFParents),

    OSGFieldDescription(OSGSFAttachmentMap::getClassType(),
                        "attachments", 
                        OSG_FC_FIELD_IDM_DESC(OSGAttachmentsField),
                        false,
                        (OSGFieldAccessMethod) &OSGNodeCore::getSFAttachments)
};

OSGFieldContainerType OSGNodeCore::_type("NodeCore",
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

OSG_ABSTR_FIELD_CONTAINER_DEF(OSGNodeCore, OSGNodeCorePtr)

/*------------------------------ access -----------------------------------*/

OSGMFNodePtr *OSGNodeCore::getMFParents(void)
{
    return &_parents;
}

OSGSFAttachmentMap *OSGNodeCore::getSFAttachments(void)
{
    return &_attachmentMap;
}

void OSGNodeCore::addAttachment(OSGAttachmentPtr &fieldContainerP,
                                OSGUInt16         binding)
{
	OSGUInt32 key;

	if(fieldContainerP == OSGNullAttachment)
        return;

	key = (OSGUInt32 (fieldContainerP->getGroupId()) << 16) | binding;
	
	fieldContainerP->addParent(getPtr());

	_attachmentMap.getValue()[key] = fieldContainerP;
}

void OSGNodeCore::subAttachment(OSGAttachmentPtr &fieldContainerP,
                                OSGUInt16         binding)
{
    OSGUInt32 key;
    OSGAttachmentMap::iterator fcI;

    if(fieldContainerP == OSGNullAttachment)
        return;

    key = (OSGUInt32(fieldContainerP->getGroupId()) << 16) | binding;

    fcI = _attachmentMap.getValue().find(key);

    if(fcI != _attachmentMap.getValue().end())
    {
        (*fcI).second->subParent(getPtr());
        _attachmentMap.getValue().erase(fcI);
    }  
}

OSGAttachmentPtr OSGNodeCore::findAttachment(OSGUInt16 groupId, 
                                             OSGUInt16 binding)
{
	OSGUInt32 key = (OSGUInt32(groupId) << 16) | binding;

	OSGAttachmentMap::iterator fcI = _attachmentMap.getValue().find(key);
	
	return (fcI == _attachmentMap.getValue().end()) ? 
        OSGNullAttachment : fcI->second;
}



/*---------------------------- properties ---------------------------------*/

OSGNodeCorePtr OSGNodeCore::getPtr(void)
{
    OSGNodeCorePtr returnValue(*this);

    return returnValue;
}

/*-------------------------- your_category---------------------------------*/

void OSGNodeCore::accumulateMatrix(OSGMatrix &)
{
}

void OSGNodeCore::adjustVolume(OSGVolume &)
{
}

/*-------------------------- assignment -----------------------------------*/

void OSGNodeCore::print(OSGUInt32 indent)
{
    OSGUInt32 i;
    OSGUInt32 j;

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

    OSGAttachmentMap::iterator fcI;

    fcI = _attachmentMap.getValue().begin();

    while(fcI != _attachmentMap.getValue().end())
    {
        (*fcI).second->print(indent + 2);
        ++fcI;
    }
}

/*------------------------------- dump ----------------------------------*/

void OSGNodeCore::dump(void) const
{
    SDEBUG << "Dump OSGNodeCore NI" << endl;
}

/*-------------------------- comparison -----------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

OSGNodeCore::OSGNodeCore(void) :
    Inherited     (),
    _parents      (),
    _attachmentMap()
{
	return;
}

/** \brief Copy Constructor
 */

OSGNodeCore::OSGNodeCore(const OSGNodeCore &obj) :
    Inherited     (obj),
    _parents      (),
    _attachmentMap(obj._attachmentMap)
{
}

/** \brief Destructor
 */

OSGNodeCore::~OSGNodeCore (void )
{
}

void OSGNodeCore::addParent(const OSGNodePtr &parent)
{
    _parents.addValue(parent);
}

void OSGNodeCore::subParent(const OSGNodePtr &parent)
{
    OSGMFNodePtr::iterator parentIt = _parents.find(parent);

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
