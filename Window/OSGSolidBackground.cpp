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

#include <OSGConfig.h>

#include <GL/gl.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#define OSG_COMPILEWINDOW
#define OSG_COMPILEBACKGROUNDINST

#include <OSGFieldContainer.h>
#include <OSGNode.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGBackground.h"
#include "OSGSolidBackground.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SolidBackground
    \ingroup Backgrounds

The SolidBackground class.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

OSG_BEGIN_NAMESPACE

#if defined(__sgi)

#pragma instantiate SField<SolidBackgroundPtr>::_fieldType
//#pragma instantiate MField<SolidBackgroundPtr>::_fieldType

#else

OSG_DLLEXPORT_DEF1(SField, SolidBackgroundPtr, OSG_WINDOW_DLLTMPLMAPPING)
//OSG_DLLEXPORT_DEF1(MField, BackgroundPtr, OSG_WINDOW_DLLTMPLMAPPING)

#endif

OSG_END_NAMESPACE


/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char SolidBackground::cvsid[] = "@(#)$Id: OSGSolidBackground.cpp,v 1.4 2001/04/06 16:28:59 jbehr Exp $";

OSG_FC_FIRST_FIELD_IDM_DEF(SolidBackground, ColorField)
OSG_FC_LAST_FIELD_IDM_DEF (SolidBackground, ColorField)

// Static Class Varible implementations: 
FieldDescription SolidBackground::_desc[] = 
{
        FieldDescription(SFColor3f::getClassType(), 
                            "color", 
                            OSG_FC_FIELD_IDM_DESC(ColorField),
                            false,
                            (FieldAccessMethod) &SolidBackground::getColor),
};

FieldContainerType SolidBackground::_type(
    "SolidBackground", 
    "FieldContainer", 
    0,
    (PrototypeCreateF) &SolidBackground::createEmpty,
    0,
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

OSG_FIELD_CONTAINER_DEF(SolidBackground, SolidBackgroundPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

SolidBackground::SolidBackground(void) //:
//	Inherited()
	  // TODO: initialize members
{
}

SolidBackground::SolidBackground(const SolidBackground &source) //:
//	Inherited()
	  // TODO: initialize members
{
}

/** \brief Destructor
 */

SolidBackground::~SolidBackground(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

void SolidBackground::clear(DrawAction *, ViewportP)
{
	Color3f col = getColor();
	glClearColor( col[0], col[1], col[2], 1.0);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

SolidBackground &SolidBackground::operator = (const SolidBackground &source)
{
	if (this == &source)
		return *this;

	// copy parts inherited from parent
	// *(static_cast<Inherited *>(this)) = source;

	// free mem alloced by members of 'this'

	// alloc new mem for members

	// copy 

    return *this;
}

/*-------------------------- comparison -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void SolidBackground::dump(      UInt32     uiIndent, 
                           const BitVector &bvFlags) const
{
	SLOG << "Dump SolidBackground NI" << endl;
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

