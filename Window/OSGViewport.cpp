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

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <GL/gl.h>

#define OSG_COMPILEWINDOW

#include <OSGField.h>
#include <OSGFieldContainer.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include "OSGBackground.h"
#include "OSGViewport.h"
#include "OSGWindow.h"
#include "OSGCamera.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char Viewport::cvsid[] = "@(#)$Id: $";

OSG_FC_FIRST_FIELD_IDM_DEF(Viewport, LeftField)

OSG_FC_FIELD_IDM_DEF      (Viewport, RightField,      LeftField  )
OSG_FC_FIELD_IDM_DEF      (Viewport, BottomField,     RightField )
OSG_FC_FIELD_IDM_DEF      (Viewport, TopField,        BottomField)
OSG_FC_FIELD_IDM_DEF      (Viewport, ParentField,     TopField   )
OSG_FC_FIELD_IDM_DEF      (Viewport, CameraField,     ParentField)
OSG_FC_FIELD_IDM_DEF      (Viewport, RootField,       CameraField)
OSG_FC_FIELD_IDM_DEF      (Viewport, BackgroundField, RootField  )

OSG_FC_LAST_FIELD_IDM_DEF (Viewport, BackgroundField)

// Static Class Varible implementations: 
FieldDescription Viewport::_desc[] = 
{
        FieldDescription(
            SFReal32::getClassType(), 
            "left", 
            OSG_FC_FIELD_IDM_DESC(LeftField),
            false,
            (FieldAccessMethod) &Viewport::getSFLeft),

        FieldDescription(
            SFReal32::getClassType(), 
            "right", 
            OSG_FC_FIELD_IDM_DESC(RightField),
            false,           
            (FieldAccessMethod) &Viewport::getSFRight),

        FieldDescription(
            SFReal32::getClassType(), 
            "bottom", 
            OSG_FC_FIELD_IDM_DESC(BottomField),
            false,
            (FieldAccessMethod) &Viewport::getSFBottom),

        FieldDescription(
            SFReal32::getClassType(), 
            "top", 
            OSG_FC_FIELD_IDM_DESC(TopField),
            false,
            (FieldAccessMethod) &Viewport::getSFTop),

        FieldDescription(
            SFWindowPtr::getClassType(), 
            "parent", 
            OSG_FC_FIELD_IDM_DESC(ParentField),
            false,
            (FieldAccessMethod) &Viewport::getSFParent),

        FieldDescription(
            SFCameraPtr::getClassType(), 
            "camera", 
            OSG_FC_FIELD_IDM_DESC(CameraField),
            false,
            (FieldAccessMethod) &Viewport::getSFCamera),

        FieldDescription(
            SFNodePtr::getClassType(), 
            "root", 
            OSG_FC_FIELD_IDM_DESC(RootField),
            false,
            (FieldAccessMethod) &Viewport::getSFRoot),

        FieldDescription(
            SFBackgroundPtr::getClassType(), 
            "background", 
            OSG_FC_FIELD_IDM_DESC(BackgroundField),
            false,
            (FieldAccessMethod) &Viewport::getSFBackground),
};

FieldContainerType Viewport::_type(
    "Viewport", 
    "FieldContainer", 
    0,
    (PrototypeCreateF) &Viewport::createEmpty,
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

OSG_FIELD_CONTAINER_DEF(Viewport, ViewportPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

Viewport::Viewport(void) :
	Inherited(), _left(0), _right(1), _bottom(0), _top(1), 
	_camera(), _root(), _background(), _parent()
{
}

Viewport::Viewport( const Viewport& source) :
	Inherited(), _left(source.getLeft()), _right(source.getRight()), 
	_bottom(source.getBottom()), _top(source.getTop()), 
	_camera(source.getCamera()), _root(source.getRoot()), 
	_background(source.getBackground()), _parent(source.getParent())
{
}

/** \brief Destructor
 */

Viewport::~Viewport(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/


Int32 Viewport::getPixelLeft( void )
{
	if ( getLeft() > 1 )
		return getLeft();

	return getParent()->getWidth() * getLeft();
}

Int32 Viewport::getPixelRight( void )
{
	if ( getRight() > 1 )
		return getRight();

	return getParent()->getWidth() * getRight() - 1;
}

Int32 Viewport::getPixelBottom( void )
{
	if ( getBottom() > 1 )
		return getBottom();

	return getParent()->getHeight() * getBottom();
}

Int32 Viewport::getPixelTop( void )
{
	if ( getTop() > 1 )
		return getTop();

	return getParent()->getHeight() * getTop() - 1;
}

Bool Viewport::isFullWindow( void )
{
	return	getPixelBottom() == 0 &&
			getPixelLeft()   == 0 &&
			getPixelTop()    == getParent()->getHeight() - 1 &&
			getPixelRight()  == getParent()->getWidth() - 1;
}

/*-------------------------- your_category---------------------------------*/

void Viewport::draw( DrawAction * action )
{
	if ( getCamera() == NullNode )
	{
		SWARNING << "Viewport::draw: no camera!" << endl;
		return;
	}
	if ( getBackground() == NullNode )
	{
		SWARNING << "Viewport::draw: no background!" << endl;
		return;
	}
	if ( getRoot() == NullNode )
	{
		SWARNING << "Viewport::draw: no root!" << endl;
		return;
	}

	GLint pl=getPixelLeft(), pr=getPixelRight(), pb=getPixelBottom(), 
		  pt=getPixelTop();
	GLint pw=pr-pl,ph=pt-pb;
	Bool full = isFullWindow();

	glViewport( pl, pb, pw, ph );
	glScissor( pl, pb, pw, ph );
	
	if ( ! full )
		glEnable( GL_SCISSOR_TEST );

	action->setCamera( getCamera().getCPtr() );
	action->setBackground( getBackground().getCPtr() );
	
	getCamera()->setup( action, this );
	getBackground()->clear( action, this );

	action->apply( getRoot() );

	if ( ! full )
		glDisable( GL_SCISSOR_TEST );
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

Viewport& Viewport::operator = (const Viewport &source)
{
	if (this == &source)
		return *this;

	// copy parts inherited from parent
	//*(static_cast<Inherited *>(this)) = source;

	// free mem alloced by members of 'this'

	// alloc new mem for members

	// copy 

    return *this;
}

/*-------------------------- comparison -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void Viewport::dump(void) const
{
    SDEBUG << "Dump Viewport NI" << endl;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


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

