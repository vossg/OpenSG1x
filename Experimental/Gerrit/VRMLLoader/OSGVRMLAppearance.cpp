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

#include "OSGVRMLAppearance.h"
#include "OSGDataElementDesc.h"

#include "OSGChunkMaterial.h"
#include "OSGVRMLToOSGAction.h"
#include "OSGBlendChunk.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGVRMLAPPEARANCE_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_BEGIN_NAMESPACE

VRMLAction::ActionResult osgVRMLAppearanceToOpenSG(VRMLNode   &oNode,
                                                   VRMLAction *pAction);

OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlAppearanceDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFVRMLNode::getClassType(),
        "material",
        OSG_RC_ELEM_IDM_DESC(VRMLAppearance::MaterialField),
        false,
        (DataElemGetMethod) &VRMLAppearance::getSFMaterial,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFVRMLNode::getClassType(),
        "texture",
        OSG_RC_ELEM_IDM_DESC(VRMLAppearance::TextureField),
        false,
        (DataElemGetMethod) &VRMLAppearance::getSFTexture,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFVRMLNode::getClassType(),
        "textureTransform",
        OSG_RC_ELEM_IDM_DESC(VRMLAppearance::TextureTransformField),
        false,
        (DataElemGetMethod) &VRMLAppearance::getSFTextureTransform,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}

VRMLObjectType VRMLAppearance::_type(
    "Appearance",
    "VRMLUnlimitedNode",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLAppearance::createEmpty,
    VRMLAppearance::init,
    vrmlAppearanceDescInserter,
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

void VRMLAppearance::init(void)
{
    VRMLToOSGAction::registerDefaultTrav(
        VRMLAppearance::getClassType(),
        osgTypedFunctionFunctor2Ref<VRMLAction::ActionResult,
                                    VRMLNode,
                                    VRMLAction *>(osgVRMLAppearanceToOpenSG));
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

VRMLAppearance::VRMLAppearance(void) :
	 Inherited         (),
    _sfMaterial        (NULL),
    _sfTexture         (NULL),
    _sfTextureTransform(NULL)
{
}


VRMLAppearance::VRMLAppearance(const VRMLAppearance &source) :
	 Inherited         (source                    ),
    _sfMaterial        (source._sfMaterial        ),
    _sfTexture         (source._sfTexture         ),
    _sfTextureTransform(source._sfTextureTransform)
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#ifdef WIN32
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLAppearance, Ptr);

#ifdef WIN32
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLAppearance::~VRMLAppearance(void)
{
}

SFVRMLNode *VRMLAppearance::getSFMaterial(void)
{
    return &_sfMaterial;
}

SFVRMLNode *VRMLAppearance::getSFTexture(void)
{
    return &_sfTexture;
}

SFVRMLNode *VRMLAppearance::getSFTextureTransform(void)
{
    return &_sfTextureTransform;
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

VRMLAppearanceBinder::VRMLAppearanceBinder(void) :
	Inherited()
{
}


VRMLAppearanceBinder::~VRMLAppearanceBinder(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLAppearanceBinder::init(VRMLToOSGAction *)
{
    _pFieldContainer = ChunkMaterial::create();
}
    
void VRMLAppearanceBinder::setMaterial(MaterialChunkPtr pMat)
{
    if(pMat == NullFC)
        return;

    ChunkMaterialPtr pChunkMat = 
        ChunkMaterialPtr::dcast(_pFieldContainer);

    if(pChunkMat != NullFC)
    {
        pChunkMat->addChunk(pMat);
    }
}

void VRMLAppearanceBinder::setTexture(TextureChunkPtr pTex)
{
    if(pTex == NullFC)
        return;

    ChunkMaterialPtr pChunkMat = 
        ChunkMaterialPtr::dcast(_pFieldContainer);

    if(pChunkMat != NullFC)
    {
        pChunkMat->addChunk(pTex);
    }
}

void VRMLAppearanceBinder::setTextureTransform(
    TextureTransformChunkPtr pTexTrans)
{
    if(pTexTrans == NullFC)
        return;

    ChunkMaterialPtr pChunkMat = 
        ChunkMaterialPtr::dcast(_pFieldContainer);

    if(pChunkMat != NullFC)
    {
        pChunkMat->addChunk(pTexTrans);
    }
}

void VRMLAppearanceBinder::finish(VRMLToOSGAction *)
{
    BlendChunkPtr pBlendChunk = OSG::BlendChunk::create();

    ChunkMaterialPtr pChunkMat = 
        ChunkMaterialPtr::dcast(_pFieldContainer);

    pBlendChunk->setSrcFactor (GL_SRC_ALPHA);
    pBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
    
    if(pChunkMat != NullFC)
    {
        pChunkMat->addChunk(pBlendChunk);
    }
}


VRMLAction::ActionResult OSG::osgVRMLAppearanceToOpenSG(
    VRMLNode   &oNode,
    VRMLAction *pAction)
{
    VRMLAction::ActionResult returnValue = VRMLAction::Continue;
    
    fprintf(stderr, "Visit Appearance : %s\n", oNode.getName().str());

    VRMLToOSGAction *pConvAction = 
        dynamic_cast<VRMLToOSGAction *>(pAction);

    VRMLAppearance  *pApp        = 
        dynamic_cast<VRMLAppearance  *>(&oNode );

    if(pConvAction != NULL && pApp != NULL)
    {
        VRMLAppearanceBinder *pBinder     = new VRMLAppearanceBinder();
        VRMLNodeBinder       *pNodeBinder = NULL;

        MaterialChunkPtr         pMat        = NullFC;
        TextureChunkPtr          pTex        = NullFC;
        TextureTransformChunkPtr pTexTrans   = OSG::NullFC;

        pBinder->setNode(pApp);
        pBinder->init   (pConvAction);

        returnValue = pConvAction->apply(pApp->getSFMaterial()->getValue());

        if(pApp->getSFMaterial()->getValue() != NULL)
        {
            pNodeBinder = pApp->getSFMaterial()->getValue()->getBinder();
            
            if(pNodeBinder != NULL)
            {
                pMat = MaterialChunkPtr::dcast(pNodeBinder->getFCPtr());
                
                if(pMat != NullFC)
                {
                    pBinder->setMaterial(pMat);
                }
                else
                {
                    fprintf(stderr, "A2OSG : Error no mat\n");
                }
            } 
            else
            {
                fprintf(stderr, "A2OSG : error no mat binder\n");
            }
        }
            

        if(returnValue == VRMLAction::Continue)
        {
            returnValue = pConvAction->apply(pApp->getSFTexture()->getValue());
        }

        if(pApp->getSFTexture()->getValue() != NULL)
        {
            pNodeBinder = pApp->getSFTexture()->getValue()->getBinder();
            
            if(pNodeBinder != NULL)
            {
                pTex = TextureChunkPtr::dcast(pNodeBinder->getFCPtr());
                
                if(pTex != NullFC)
                {
                    pBinder->setTexture(pTex);
                }
                else
                {
                    fprintf(stderr, "A2OSG : Error no texture\n");
                }
            } 
            else
            {
                fprintf(stderr, "A2OSG : error no texture binder\n");
            }
        }


        if(returnValue == VRMLAction::Continue)
        {
            returnValue = 
                pConvAction->apply(pApp->getSFTextureTransform()->getValue());
        }

        if(pApp->getSFTextureTransform()->getValue() != NULL)
        {
            pNodeBinder = 
                pApp->getSFTextureTransform()->getValue()->getBinder();
            
            if(pNodeBinder != NULL)
            {
                pTexTrans = TextureTransformChunkPtr::dcast(
                    pNodeBinder->getFCPtr());
                
                if(pTex != NullFC)
                {
                    pBinder->setTextureTransform(pTexTrans);
                }
                else
                {
                    fprintf(stderr, "A2OSG : Error no texture transform\n");
                }
            } 
            else
            {
                fprintf(stderr, "A2OSG : error no texture transform binder\n");
            }
        }

        pBinder->finish(pConvAction);
        oNode.setBinder(pBinder);
    }

    return VRMLAction::Continue;
}
