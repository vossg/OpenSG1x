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

#include "OSGVRMLFontStyle.h"

#include <OSGDataElementDesc.h>

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlFontStyleDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFString::getClassType(),
        "family",
        OSG_RC_ELEM_IDM_DESC(VRMLFontStyle::FamilyField),
        false,
        (DataElemGetMethod) &VRMLFontStyle::getSFFamily,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "horizontal",
        OSG_RC_ELEM_IDM_DESC(VRMLFontStyle::HorizontalField),
        false,
        (DataElemGetMethod) &VRMLFontStyle::getSFHorizontal,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFString::getClassType(),
        "justify",
        OSG_RC_ELEM_IDM_DESC(VRMLFontStyle::JustifyField),
        false,
        (DataElemGetMethod) &VRMLFontStyle::getMFJustify,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFString::getClassType(),
        "language",
        OSG_RC_ELEM_IDM_DESC(VRMLFontStyle::LanguageField),
        false,
        (DataElemGetMethod) &VRMLFontStyle::getSFLanguage,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "leftToRight",
        OSG_RC_ELEM_IDM_DESC(VRMLFontStyle::LeftToRightField),
        false,
        (DataElemGetMethod) &VRMLFontStyle::getSFLeftToRight,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "size",
        OSG_RC_ELEM_IDM_DESC(VRMLFontStyle::SizeField),
        false,
        (DataElemGetMethod) &VRMLFontStyle::getSFSize,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "spacing",
        OSG_RC_ELEM_IDM_DESC(VRMLFontStyle::SpacingField),
        false,
        (DataElemGetMethod) &VRMLFontStyle::getSFSpacing,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFString::getClassType(),
        "style",
        OSG_RC_ELEM_IDM_DESC(VRMLFontStyle::StyleField),
        false,
        (DataElemGetMethod) &VRMLFontStyle::getSFStyle,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "topToBottom",
        OSG_RC_ELEM_IDM_DESC(VRMLFontStyle::TopToBottomField),
        false,
        (DataElemGetMethod) &VRMLFontStyle::getSFTopToBottom,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLFontStyle::_type(
    "FontStyle",
    "VRMLUnlimitedNode",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLFontStyle::createEmpty,
    NULL, // Init
    vrmlFontStyleDescInserter,
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

VRMLFontStyle::VRMLFontStyle(void) :
	Inherited(),

    _sfFamily     (    ),
    _sfHorizontal (true),
    _mfJustify    (    ),
    _sfLanguage   (    ),
    _sfLeftToRight(true),
    _sfSize       (1.0f),
    _sfSpacing    (1.0f),
    _sfStyle      (    ),
    _sfTopToBottom(true)
{
    string szJustify("BEGIN");
    
    _sfFamily.getValue().assign("SERIF");
    _sfStyle .getValue().assign("PLAIN");

    _mfJustify.push_back(szJustify);
}


VRMLFontStyle::VRMLFontStyle(const VRMLFontStyle &source) :
	Inherited(source),

    _sfFamily     (source._sfFamily     ),
    _sfHorizontal (source._sfHorizontal ),
    _mfJustify    (source._mfJustify    ),
    _sfLanguage   (source._sfLanguage   ),
    _sfLeftToRight(source._sfLeftToRight),
    _sfSize       (source._sfSize       ),
    _sfSpacing    (source._sfSpacing    ),
    _sfStyle      (source._sfStyle      ),
    _sfTopToBottom(source._sfTopToBottom)
{
}


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLFontStyle, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLFontStyle::~VRMLFontStyle(void)
{
}

/*------------------------------ access -----------------------------------*/

SFString *VRMLFontStyle::getSFFamily(void)
{
    return &_sfFamily;
}

SFBool *VRMLFontStyle::getSFHorizontal(void)
{
    return &_sfHorizontal;
}

MFString *VRMLFontStyle::getMFJustify(void)
{
    return &_mfJustify;
}

SFString *VRMLFontStyle::getSFLanguage(void)
{
    return &_sfLanguage;
}

SFBool *VRMLFontStyle::getSFLeftToRight(void)
{
    return &_sfLeftToRight;
}

SFReal32 *VRMLFontStyle::getSFSize(void)
{
    return &_sfSize;
}

SFReal32 *VRMLFontStyle::getSFSpacing(void)
{
    return &_sfSpacing;
}

SFString *VRMLFontStyle::getSFStyle(void)
{
    return &_sfStyle;
}

SFBool *VRMLFontStyle::getSFTopToBottom(void)
{
    return &_sfTopToBottom;
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
    static Char8 cvsid_hpp[] = OSGVRMLFONTSTYLE_HEADER_CVSID;
}
