/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
 *                                                                           *
 *                            www.opensg.org                                 *
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

#define OSG_COMPILEVRMLNODEINST

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGVRMLNode.h"
#include "OSGVRMLObjectFactory.h"

#include <OSGVRMLNodeAttachmentMap.h>


OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGVRMLNODE_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

template class OSG_VRML_DLLMAPPING
    AttachmentContainerMixin<VRMLNodeAttachmentContainerDesc>;

void VRMLNodeAttachmentContainerDesc::descInserter(
    ReflexiveContainerType *pType)
{
    typedef AttachmentContainerMixin<VRMLNodeAttachmentContainerDesc> AC;
    
    if(pType == NULL)
        return;
    
    DataElementDesc *pDesc = NULL;
    
    pDesc = new DataElementDesc(
        AC::SFAttachmentObjMap::getClassType(),
        "attachments",
        OSG_RC_ELEM_IDM_DESC(AC::AttachmentsField),
        false,
        (DataElemGetMethod) &AC::getSFAttachments,
        NULL,
        NULL);
    
    pType->addInitialDesc(pDesc);
}

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

VRMLObjectType VRMLNode::_type(
    "VRMLNode",
    "VRMLNodeAttachmentContainer",
    "VRMLNodes",
    NULL,
    NULL,
    NULL,
    false);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

VRMLNode::VRMLNode(void) :
	 Inherited( ),
    _szName   ( ),
    _pBinder  (VRMLBindings::getNullNodeBinder())
{
}

VRMLNode::VRMLNode(const VRMLNode &source) :
     Inherited(source),
    _szName   (      ),
    _pBinder  (source._pBinder)
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#ifdef WIN32
#pragma warning (disable : 424)
#endif

OSG_ABSTR_VRMLOBJ_DEF(VRMLNode, Ptr);

#ifdef WIN32
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLNode::~VRMLNode(void)
{
}


void VRMLNode::setName(const Char8 *szName)
{
    _szName.set(szName);
}
 
const IDString &VRMLNode::getName(void) const
{
    return _szName;
}

const Char8 *VRMLNode::getCName(void) const
{
    return _szName.str();
}

VRMLNode::NodeBinderPtr VRMLNode::getBinder(void)
{
    return _pBinder;
}

void VRMLNode::setBinder(NodeBinderPtr pBinder)
{
    _pBinder = pBinder;
}

void VRMLNode::beginEdit(BitVector bWhichField)
{
    VRMLObjectFactory::the()->beginEdit(this, bWhichField);
}

void VRMLNode::endEdit(BitVector bWhichField)
{
    VRMLObjectFactory::the()->endEdit(this, bWhichField);
}


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

VRMLNodeBinder::VRMLNodeBinder(void) :
    _pFieldContainer(NullFC),
    _pNode          (NULL  )
{
}

VRMLNodeBinder::~VRMLNodeBinder(void)
{
}

FieldContainerPtr VRMLNodeBinder::getFCPtr(void)
{
    return _pFieldContainer;
}

void VRMLNodeBinder::setNode(VRMLNode *pNode)
{
    _pNode = pNode;
}



