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

#include "OSGVRMLLimitedNode.h"
#include <OSGDataElementDesc.h>

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

#if 0

template<>
struct VSCDescHolderC<VSCVRMLLimitedNode, 
                      VSCVRMLLimitedNode::VSCBBoxCenterFieldCount, 
                      VSCDataElementDesc> : 
    public VSCDescHolderBaseC<VSCVRMLLimitedNode, 
                              VSCVRMLLimitedNode::VSCBBoxCenterFieldCount, 
                              VSCDataElementDesc>
{
    static VSCDataElementDesc _desc;
};

VSCDataElementDesc VSCDescHolderC<
    VSCVRMLLimitedNode, 
    VSCVRMLLimitedNode::VSCBBoxCenterFieldCount, 
    VSCDataElementDesc                         >::_desc(
        VSCSFPnt3f::getClassType(),
        "bboxCenter",
        VSC_RC_ELEM_IDM_DESC(VSCVRMLLimitedNode::VSCBBoxCenterField),
        false,
        (VSCDataElemGetMethod) &VSCVRMLLimitedNode::getSFBBoxCenter,
        NULL,
        NULL,
        VSCDataElementDesc::VSCDefaultBeginEditFunctor,
        VSCDataElementDesc::VSCDefaultEndEditFunctor,
        VSCDataElementDesc::VSCDefaultSyncFunctor);


template<>
struct VSCDescHolderC<VSCVRMLLimitedNode, 
                      VSCVRMLLimitedNode::VSCBBoxSizeFieldCount, 
                      VSCDataElementDesc> : 
    public VSCDescHolderBaseC<VSCVRMLLimitedNode, 
                              VSCVRMLLimitedNode::VSCBBoxSizeFieldCount, 
                              VSCDataElementDesc>
{
    static VSCDataElementDesc _desc;
};

VSCDataElementDesc VSCDescHolderC<
    VSCVRMLLimitedNode, 
    VSCVRMLLimitedNode::VSCBBoxSizeFieldCount, 
    VSCDataElementDesc                       >::_desc(
        VSCSFPnt3f::getClassType(),
        "bboxSize",
        VSC_RC_ELEM_IDM_DESC(VSCVRMLLimitedNode::VSCBBoxSizeField),
        false,
        (VSCDataElemGetMethod) &VSCVRMLLimitedNode::getSFBBoxSize,
        NULL,
        NULL,
        VSCDataElementDesc::VSCDefaultBeginEditFunctor,
        VSCDataElementDesc::VSCDefaultEndEditFunctor,
        VSCDataElementDesc::VSCDefaultSyncFunctor);
#endif

static void vrmlLNodeDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFPnt3f::getClassType(),
        "bboxCenter",
        OSG_RC_ELEM_IDM_DESC(VRMLLimitedNode::BBoxCenterField),
        false,
        (DataElemGetMethod) &VRMLLimitedNode::getSFBBoxCenter,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFPnt3f::getClassType(),
        "bboxSize",
        OSG_RC_ELEM_IDM_DESC(VRMLLimitedNode::BBoxSizeField),
        false,
        (DataElemGetMethod) &VRMLLimitedNode::getSFBBoxSize,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}

VRMLObjectType VRMLLimitedNode::_type(
    "VRMLLimitedNode",
    "VRMLNode",
    "VRMLNodes",
    NULL, // Proto
    NULL, // Init
/*
    VSCDescHolderC<VSCVRMLLimitedNode, 
                   VSCVRMLLimitedNode::VSCLastElemCount,
                   VSCDataElementDesc            >::
        VSCGetHolder<VSCVRMLLimitedNode::VSCFirstElemId>::getDescVec(),
*/
    vrmlLNodeDescInserter,
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

VRMLLimitedNode::VRMLLimitedNode(void) :
     Inherited   (),
    _sfBBoxCenter(),
    _sfBBoxSize  ()
{
    _sfBBoxCenter.getValue().setValues( 0.f,  0.f,  0.f);          
    _sfBBoxSize  .getValue().setValues(-1.f, -1.f, -1.f);
}

VRMLLimitedNode::VRMLLimitedNode(const VRMLLimitedNode &source) :
     Inherited(source),

    _sfBBoxCenter(source._sfBBoxCenter),
    _sfBBoxSize  (source._sfBBoxSize  )
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_ABSTR_VRMLOBJ_DEF(VRMLLimitedNode, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif


/*------------- constructors & destructors --------------------------------*/

VRMLLimitedNode::~VRMLLimitedNode(void)
{
}

SFPnt3f *VRMLLimitedNode::getSFBBoxCenter(void)
{
    return &_sfBBoxCenter;
}

SFPnt3f *VRMLLimitedNode::getSFBBoxSize(void)
{
    return &_sfBBoxSize;
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
    static Char8 cvsid_hpp[] = OSGVRMLLIMITEDNODE_HEADER_CVSID;
}
