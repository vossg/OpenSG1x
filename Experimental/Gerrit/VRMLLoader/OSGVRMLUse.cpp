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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGVRMLUse.h"
#include "OSGDataElementDesc.h"

#include <OSGFieldContainer.h>
#include <OSGNode.h>
#include <OSGVRMLToOSGAction.h>

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGVRMLUSE_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif


OSG_BEGIN_NAMESPACE

VRMLAction::ActionResult osgVRMLUseToOpenSG(VRMLNode   &oNode,
                                            VRMLAction *pAction);

OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlUseDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFString::getClassType(),
        "name",
        OSG_RC_ELEM_IDM_DESC(VRMLUse::NameField),
        false,
        (DataElemGetMethod) &VRMLUse::getSFName,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLUse::_type(
    "Use",
    "VRMLUnlimitedNode",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLUse::createEmpty,
    VRMLUse::init,
    vrmlUseDescInserter,
    true);

#endif

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

void VRMLUse::init(void)
{
    VRMLToOSGAction::registerDefaultTrav(
        VRMLUse::getClassType(),
        osgTypedFunctionFunctor2Ref<VRMLAction::ActionResult,
                                    VRMLNode,
                                    VRMLAction *>(osgVRMLUseToOpenSG));
}


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

VRMLUse::VRMLUse(void) :
	 Inherited(),
    _sfName   ()
{
}

VRMLUse::VRMLUse(const VRMLUse &source) :
 	 Inherited(source),

    _sfName   (source._sfName)
{
}


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#ifdef WIN32
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLUse, Ptr);

#ifdef WIN32
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLUse::~VRMLUse(void)
{
}

/*------------------------------ access -----------------------------------*/

SFString *VRMLUse::getSFName(void)
{
    return &_sfName;
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

VRMLUseBinder::VRMLUseBinder(void) :
	Inherited()
{
}

VRMLUseBinder::~VRMLUseBinder(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLUseBinder::init(VRMLToOSGAction *pAction)
{
    typedef VRMLToOSGAction::NameNodeMap NameNodeMap;

    if(pAction == NULL)
        return;

    if(_pNode == NULL)
        return;

    VRMLUse *pNode = dynamic_cast<VRMLUse *>(_pNode);

    if(pNode == NULL)
        return;

    NameNodeMap *pNameNodeMap = pAction->getNameNodeMap();

    if(pNameNodeMap == NULL)
        return;

    IDStringLink szNodeName(pNode->getSFName()->getValue().c_str());

    if(szNodeName.str() == NULL)
        return;

    NameNodeMap::iterator mapIt = pNameNodeMap->find(szNodeName);

    if(mapIt != pNameNodeMap->end())
    {
        VRMLNodeBinder *pUsedBinder = mapIt->second->getBinder();

        if(pUsedBinder != NULL)
        {
            FieldContainerPtr pUsedFC = pUsedBinder->getFCPtr();

            if(pUsedFC->getType().isNode() == true)
            {
                NodePtr pUsedNode = NodePtr::dcast(pUsedFC);

                _pFieldContainer = cloneTree(pUsedNode);
            }
            else
            {
                _pFieldContainer = pUsedFC;
            }
        }
        else
        {
            fprintf(stderr, "Found unbound node %s\n", szNodeName.str());
        }
    }
    else
    {
        fprintf(stderr, 
                "Could not find node named %s\n", 
                szNodeName.str());
    }
}

void VRMLUseBinder::finish(VRMLToOSGAction *)
{
}


VRMLAction::ActionResult OSG::osgVRMLUseToOpenSG(
    VRMLNode   &oNode,
    VRMLAction *pAction)
{
    fprintf(stderr,
            "Visit Use : %s\n", 
            oNode.getName().str());

    VRMLToOSGAction *pConvAction = 
        dynamic_cast<VRMLToOSGAction *>(pAction);

    VRMLUse         *pUse        = 
        dynamic_cast<VRMLUse         *>(&oNode );

    if(pConvAction != NULL && pUse != NULL)
    {
        VRMLUseBinder *pBinder = new VRMLUseBinder();

        pBinder->setNode(pUse);
        pBinder->init   (pConvAction);

        pBinder->finish (pConvAction);
        oNode.setBinder (pBinder);
    }

    return VRMLAction::Continue;
}
