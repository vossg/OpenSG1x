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

#include "OSGVRMLInline.h"

#include "OSGVRMLToOSGAction.h"
#include "OSGVRMLLoader.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGVRMLINLINE_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_BEGIN_NAMESPACE

VRMLAction::ActionResult osgVRMLInlineToOpenSG(VRMLNode   &oNode,
                                               VRMLAction *pAction);

OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlInlineDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        MFString::getClassType(),
        "url",
        OSG_RC_ELEM_IDM_DESC(VRMLInline::UrlField),
        false,
        (DataElemGetMethod) &VRMLInline::getMFUrl,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLInline::_type(
    "Inline",
    "VRMLLimitedNode",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLInline::createEmpty,
    &VRMLInline::init,
    vrmlInlineDescInserter,
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

void VRMLInline::init(void)
{
    VRMLToOSGAction::registerDefaultTrav(
        VRMLInline::getClassType(),
        osgTypedFunctionFunctor2Ref<VRMLAction::ActionResult,
                                    VRMLNode,
                                    VRMLAction *>(osgVRMLInlineToOpenSG));
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

VRMLInline::VRMLInline(void) :
	 Inherited(),
    _mfUrl    ()
{
}


VRMLInline::VRMLInline(const VRMLInline &source) :
	 Inherited(source       ),
    _mfUrl    (source._mfUrl)
{
}


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#ifdef WIN32
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLInline, Ptr);

#ifdef WIN32
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLInline::~VRMLInline(void)
{
}

/*------------------------------ access -----------------------------------*/

MFString *VRMLInline::getMFUrl(void)
{
    return &_mfUrl;
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

VRMLInlineBinder::VRMLInlineBinder(void) :
	Inherited()
{
}

VRMLInlineBinder::~VRMLInlineBinder(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLInlineBinder::init(VRMLToOSGAction *pAction)
{
}

void VRMLInlineBinder::finish(VRMLToOSGAction *pAction)
{
    if(_pNode == NULL)
        return;

    VRMLInline *pNode = dynamic_cast<VRMLInline *>(_pNode);

    if(pNode == NULL)
        return;

    if(pNode->getMFUrl()->getValue(0).empty() == true)
        return;


    VRMLLoader *pFile = new VRMLLoader;

    pFile->scanFile(pNode->getMFUrl()->getValue(0).c_str(), 0);

    VRMLToOSGAction aVRMLToOSG;

    VRMLBindings::NodeBinderPtr pNodeBinder = NULL;

    fprintf(stderr, "Resnode %p\n", pFile->getFileTree());
    
    aVRMLToOSG.setNameNodeMap(pFile->getNameNodeMap());
    
    aVRMLToOSG.apply(pFile->getFileTree());
    
    pNodeBinder = (pFile->getFileTree())->getBinder();
    
    if(pNodeBinder != NULL)
    {
        _pFieldContainer = pNodeBinder->getFCPtr();  
    }
    else
    {
        fprintf(stderr, "Binder NULL\n");
    }

    delete pFile;
}


VRMLAction::ActionResult OSG::osgVRMLInlineToOpenSG(
    VRMLNode   &oNode,
    VRMLAction *pAction)
{
    fprintf(stderr, "Visit Inline : %s\n", oNode.getName().str());

    VRMLToOSGAction *pConvAction = 
        dynamic_cast<VRMLToOSGAction *>(pAction);

    VRMLInline      *pInline     = 
        dynamic_cast<VRMLInline      *>(&oNode );

    if(pConvAction != NULL && pInline != NULL)
    {
        VRMLInlineBinder *pBinder = new VRMLInlineBinder();

        pBinder->setNode(pInline    );
        pBinder->init   (pConvAction);

        pBinder->finish (pConvAction);
        oNode.setBinder (pBinder);
    }

    return VRMLAction::Continue;
}
