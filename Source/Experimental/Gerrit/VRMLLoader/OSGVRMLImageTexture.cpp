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

#include "OSGVRMLImageTexture.h"

#include <OSGDataElementDesc.h>
#include <OSGVRMLToOSGAction.h>
#include <OSGTextureChunk.h>
#include <OSGImage.h>

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

VRMLAction::ActionResult osgVRMLImageTextureToOpenSG(VRMLNode   &oNode,
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
        MFString::getClassType(),
        "url",
        OSG_RC_ELEM_IDM_DESC(VRMLImageTexture::UrlField),
        false,
        (DataElemGetMethod) &VRMLImageTexture::getMFUrl,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}

VRMLObjectType VRMLImageTexture::_type(
    "ImageTexture",
    "VRMLTexture",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLImageTexture::createEmpty,
    VRMLImageTexture::init,
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

void VRMLImageTexture::init(void)
{
    VRMLToOSGAction::registerDefaultTrav(
        VRMLImageTexture::getClassType(),
        osgTypedFunctionFunctor2Ref<VRMLAction::ActionResult,
                                    VRMLNode,
                                    VRMLAction *>(
                                        osgVRMLImageTextureToOpenSG));
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

VRMLImageTexture::VRMLImageTexture(void) :
	 Inherited(    ),
    
    _mfUrl    (    )
{
}


VRMLImageTexture::VRMLImageTexture(const VRMLImageTexture &source) :
	 Inherited(source           ),

    _mfUrl    (source._mfUrl    )
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLImageTexture, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLImageTexture::~VRMLImageTexture(void)
{
}

/*------------------------------ access -----------------------------------*/

MFString *VRMLImageTexture::getMFUrl(void)
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

VRMLImageTextureBinder::VRMLImageTextureBinder(void) :
	Inherited()
{
}

VRMLImageTextureBinder::~VRMLImageTextureBinder(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLImageTextureBinder::init(VRMLToOSGAction *)
{
    if(_pNode == NULL)
        return;

    VRMLImageTexture *pNode = dynamic_cast<VRMLImageTexture *>(_pNode);

    if(pNode == NULL)
        return;

    if((*(pNode->getMFUrl()))[0].c_str() == NULL)
        return;

    TextureChunkPtr  pTexture = TextureChunk::create();

    ImagePtr         pImage   = Image::create();


    if(pImage->read((*(pNode->getMFUrl()))[0].c_str()))
    {
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
    }
    else
    {
        subRefCP(pImage);
    }

    _pFieldContainer = pTexture;
}

void VRMLImageTextureBinder::finish(VRMLToOSGAction *)
{
}


VRMLAction::ActionResult OSG::osgVRMLImageTextureToOpenSG(
    VRMLNode   &oNode,
    VRMLAction *pAction)
{
  fprintf(stderr, "Visit ImageTexture : %s\n", oNode.getName().str());

    VRMLToOSGAction  *pConvAction = 
        dynamic_cast<VRMLToOSGAction  *>(pAction);

    VRMLImageTexture *pTex        = 
        dynamic_cast<VRMLImageTexture *>(&oNode );

    if(pConvAction != NULL && pTex != NULL)
    {
        VRMLImageTextureBinder *pBinder     = 
            new VRMLImageTextureBinder();

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
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGVRMLIMAGETEXTURE_HEADER_CVSID;
}
