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

#include "OSGVRMLPixelTexture.h"

#include <OSGDataElementDesc.h>
#include <OSGVRMLToOSGAction.h>
#include <OSGTextureChunk.h>

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

VRMLAction::ActionResult osgVRMLPixelTextureToOpenSG(VRMLNode   &oNode,
                                                     VRMLAction *pAction);


OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlImageTextureDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFImagePtr::getClassType(),
        "image",
        OSG_RC_ELEM_IDM_DESC(VRMLPixelTexture::ImageField),
        false,
        (DataElemGetMethod) &VRMLPixelTexture::getSFImage,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}

VRMLObjectType VRMLPixelTexture::_type(
    "PixelTexture",
    "VRMLTexture",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLPixelTexture::createEmpty,
    VRMLPixelTexture::init,
    vrmlImageTextureDescInserter,
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

void VRMLPixelTexture::init(void)
{
    VRMLToOSGAction::registerDefaultTrav(
        VRMLPixelTexture::getClassType(),
        osgTypedFunctionFunctor2Ref<VRMLAction::ActionResult,
                                    VRMLNode,
                                    VRMLAction *>(
                                        osgVRMLPixelTextureToOpenSG));
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

VRMLPixelTexture::VRMLPixelTexture(void) :
    Inherited(    ),
    _sfImage (Image::create())
{
}


VRMLPixelTexture::VRMLPixelTexture(const VRMLPixelTexture &source) :
    Inherited(source           ),

    _sfImage()
{
    if(_sfImage.getValue() == NullFC)
        _sfImage.setValue(Image::create());
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLPixelTexture, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLPixelTexture::~VRMLPixelTexture(void)
{
}

/*------------------------------ access -----------------------------------*/

SFImagePtr *VRMLPixelTexture::getSFImage(void)
{
    return &_sfImage;
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

VRMLPixelTextureBinder::VRMLPixelTextureBinder(void) :
    Inherited()
{
}

VRMLPixelTextureBinder::~VRMLPixelTextureBinder(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLPixelTextureBinder::init(VRMLToOSGAction *)
{
    if(_pNode == NULL)
        return;

    VRMLPixelTexture *pNode = dynamic_cast<VRMLPixelTexture *>(_pNode);

    if(pNode == NULL)
        return;

    if(pNode->getSFImage()->getValue() == NullFC)
        return;

    TextureChunkPtr  pTexture = TextureChunk::create();

    ImagePtr         pImage   = pNode->getSFImage()->getValue();

    beginEditCP(pTexture);
    {
        pTexture->setImage(pImage);
        
        if(pNode->getSFRepeatS()->getValue() == true)
        {
            pTexture->setWrapS(GL_REPEAT);
        }
        else
        {
            pTexture->setWrapS(GL_CLAMP);
        }
        
        if(pNode->getSFRepeatT()->getValue() == true)
        {
            pTexture->setWrapT(GL_REPEAT);
        }
        else
        {
            pTexture->setWrapS(GL_CLAMP);
        }
    }
    endEditCP   (pTexture);

    _pFieldContainer = pTexture;
}

void VRMLPixelTextureBinder::finish(VRMLToOSGAction *)
{
}


VRMLAction::ActionResult OSG::osgVRMLPixelTextureToOpenSG(
    VRMLNode   &oNode,
    VRMLAction *pAction)
{
    fprintf(stderr, "Visit PixelTexture : %s\n", oNode.getName().str());

    VRMLToOSGAction  *pConvAction = 
        dynamic_cast<VRMLToOSGAction  *>(pAction);

    VRMLPixelTexture *pTex        = 
        dynamic_cast<VRMLPixelTexture *>(&oNode );

    if(pConvAction != NULL && pTex != NULL)
    {
        VRMLPixelTextureBinder *pBinder     = 
            new VRMLPixelTextureBinder();

        VRMLNodeBinder         *pNodeBinder = NULL;

        pBinder->setNode(pTex);
        pBinder->init   (pConvAction);

        pBinder->finish(pConvAction);
        oNode.setBinder(pBinder);
    }

    return VRMLAction::Continue;
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGVRMLPixelTexture.cpp,v 1.1 2004/03/05 14:29:09 a-m-z Exp $";
    static Char8 cvsid_hpp[] = OSGVRMLPIXELTEXTURE_HEADER_CVSID;
}
