/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#define OSG_COMPILESYSTEMLIB

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <GL/gl.h>

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
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Viewport
    \ingroup Windows

A Viewport is a part of the Window it is attached to used for rendering. Every Window can hold an arbitrary number of viewports. 	

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char Viewport::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

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

/** \brief initialize the static features of the class, e.g. action callbacks
 */

void Viewport::initMethod (void)
{
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

Viewport::Viewport(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

Viewport::Viewport(const Viewport &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

Viewport::~Viewport(void)
{
}


/** \brief react to field changes
 */

void Viewport::changed(BitVector, ChangeMode)
{
}

/*---------------------------- properties ---------------------------------*/


Int32 Viewport::getPixelLeft( void ) const
{
	if ( getLeft() > 1 )
		return getLeft();

	return getParent()->getWidth() * getLeft();
}

Int32 Viewport::getPixelRight( void ) const
{
	// >1: pixel
	if ( getRight() > 1 )
		return getRight();

	// <=1: partial screen, use 1 less to not overlap other windows
	return getParent()->getWidth() * getRight() - 1;
}

Int32 Viewport::getPixelBottom( void ) const
{
	if ( getBottom() > 1 )
		return getBottom();

	return getParent()->getHeight() * getBottom();
}

Int32 Viewport::getPixelTop( void ) const
{
	// >1: pixel
	if ( getTop() > 1 )
		return getTop();

	// <=1: partial screen, use 1 less to not overlap other windows
	return getParent()->getHeight() * getTop() - 1;
}

Bool Viewport::isFullWindow( void ) const
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
	GLint pw=pr-pl+1,ph=pt-pb+1;
	Bool full = isFullWindow();

	glViewport( pl, pb, pw, ph );
	glScissor( pl, pb, pw, ph );
	
	if ( ! full )
		glEnable( GL_SCISSOR_TEST );

	action->setCamera( getCamera().getCPtr() );
	action->setBackground( getBackground().getCPtr() );
	
	getCamera()->setup( action, *this );
	getBackground()->clear( action, this );

	action->apply( getRoot() );

	if ( ! full )
		glDisable( GL_SCISSOR_TEST );
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void Viewport::dump(      UInt32     uiIndent, 
                         const BitVector &bvFlags) const
{
	SLOG << "Dump Viewport NI" << endl;
}

    

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

